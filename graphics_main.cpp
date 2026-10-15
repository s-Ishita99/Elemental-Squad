#include "raylib.h"
#include "Grid.h"
#include "Rocky.h"
#include "Sprinty.h"
#include <string>
#include <cstdlib>

using namespace std;

enum Screen
{
    LOGIN,
    MENU,
    LEVEL_SELECT,
    HOW_TO_PLAY,
    LEVEL1_GAME,
    LEVEL_COMPLETE,
    LEVEL2_GAME,
    LEVEL2_COMPLETE,
    LEVEL2_PLACEHOLDER,
    LEVEL3_PLACEHOLDER,
    LEVEL3_GAME,
    GAME_COMPLETE
};

const int L2ROWS = 10;
const int L2COLS = 14;

char level2Map[L2ROWS][L2COLS] =
{
    {'.', '.', '#', '.', '.', '.', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'.', '.', '#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '#'},
    {'.', '#', '#', '#', '#', '.', 'F', '.', '.', '.', '.', 'P', '.', '.'},
    {'.', 'I', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '#', '.', '.', 'F', '#', '#', '#', '.', 'V', '#', '#', '#', '#'},
    {'.', '#', '.', '#', 'F', '.', 'W', 'W', '.', 'V', '#', '.', '.', '.'},
    {'.', '#', '#', '.', '.', '.', 'W', 'W', '.', 'V', '.', '.', '#', '.'},
    {'.', '.', '#', '.', '#', '#', '#', '#', '.', '.', '#', '.', '#', '.'},
    {'.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '#', '.', '#', '.'},
    {'.', '#', '#', '.', '#', '.', '.', 'T', '.', '.', '#', '#', '.', 'E'}
};

// Blaze character
void drawBlaze(float cx, float cy, float s)
{
    Color orange = {224, 91, 47, 255};
    Color bright = {255, 157, 69, 255};
    Color dark = {104, 43, 38, 255};

    DrawEllipse(cx, cy + 14*s, 12*s, 3*s, {0, 0, 0, 100});

    DrawLineEx({cx-5*s, cy+4*s}, {cx-7*s, cy+14*s}, 4*s, dark);
    DrawLineEx({cx+5*s, cy+4*s}, {cx+7*s, cy+14*s}, 4*s, dark);

    DrawLineEx({cx-6*s, cy-2*s}, {cx-12*s, cy+4*s}, 4*s, orange);
    DrawLineEx({cx+6*s, cy-2*s}, {cx+12*s, cy+2*s}, 4*s, orange);

    DrawPoly({cx, cy+1*s}, 6, 8*s, 0, dark);
    DrawPoly({cx, cy}, 6, 6.5f*s, 0, orange);

    DrawCircle(cx, cy-9*s, 6.5f*s, {245, 190, 151, 255});
    DrawPoly({cx-2*s, cy-15*s}, 3, 7*s, 0, bright);
    DrawPoly({cx+3*s, cy-16*s}, 3, 5*s, 0, {255, 203, 87, 255});

    DrawCircle(cx-2*s, cy-9*s, 1.1f*s, dark);
    DrawCircle(cx+2*s, cy-9*s, 1.1f*s, dark);
    DrawLineEx({cx-2*s, cy-5*s}, {cx+2*s, cy-5*s}, 1.2f*s, dark);
    DrawCircle(cx+9*s, cy-1*s, 2*s, bright);
}

// Splash character
void drawSplash(float cx, float cy, float s)
{
    Color teal = {35, 145, 155, 255};
    Color light = {106, 222, 216, 255};
    Color dark = {22, 73, 102, 255};
    Color skin = {245, 207, 185, 255};

    DrawEllipse(cx, cy+14*s, 12*s, 3*s, {0, 0, 0, 100});

    DrawLineEx({cx-4*s, cy+4*s}, {cx-9*s, cy+14*s}, 4*s, dark);
    DrawLineEx({cx+4*s, cy+4*s}, {cx+8*s, cy+13*s}, 4*s, dark);

    DrawLineEx({cx-6*s, cy-2*s}, {cx-12*s, cy+3*s}, 4*s, teal);
    DrawLineEx({cx+6*s, cy-2*s}, {cx+12*s, cy-7*s}, 4*s, teal);

    DrawPoly({cx, cy+1*s}, 6, 8*s, 0, dark);
    DrawPoly({cx, cy}, 6, 6.5f*s, 0, teal);

    DrawCircle(cx, cy-9*s, 6.5f*s, skin);
    DrawEllipse(cx-2*s, cy-14*s, 6*s, 4*s, dark);
    DrawEllipse(cx+4*s, cy-10*s, 4*s, 7*s, {29, 109, 135, 255});

    DrawCircle(cx-2*s, cy-9*s, 1.1f*s, dark);
    DrawCircle(cx+2*s, cy-9*s, 1.1f*s, dark);
    DrawLineEx({cx-1*s, cy-5*s}, {cx+3*s, cy-5*s}, 1.2f*s, dark);

    DrawCircle(cx+14*s, cy-13*s, 4*s, {69, 184, 206, 255});
    DrawTriangle(
        {cx+10*s, cy-14*s},
        {cx+18*s, cy-14*s},
        {cx+14*s, cy-21*s},
        light
    );
    DrawCircle(cx+13*s, cy-14*s, 1.2f*s, RAYWHITE);
}

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "Elemental Squad");
    SetTargetFPS(60);

    Color background = {18, 20, 48, 255};
    Color gold = {245, 196, 104, 255};
    Color paleText = {218, 224, 239, 255};
    Color floorColor = {15, 20, 39, 255};
    Color floorBorder = {38, 47, 73, 255};
    Color purple = {91, 63, 133, 255};
    Color blue = {44, 105, 153, 255};

    Font gameFont = GetFontDefault();
    bool customFontLoaded = false;

    if (FileExists("assets/DejaVuSans.ttf"))
    {
        gameFont = LoadFont("assets/DejaVuSans.ttf");
        customFontLoaded = true;
    }

    Screen screen = LOGIN;

    // Login UI prototype only: account validation/storage will be added later.
    string loginUsername = "";
    string loginPassword = "";
    bool passwordFieldActive = false;
    string loginMessage = "Enter any username and password to continue.";
    Rectangle usernameField = {330, 285, 340, 48};
    Rectangle passwordField = {330, 350, 340, 48};
    Rectangle loginButton = {390, 425, 220, 55};

    // LEVEL 1 STATE
    Rocky rocky;
    Sprinty sprinty;
    Grid grid;

    Character* current = &rocky;

    bool hasKey = false;
    bool levelWon = false;
    int moves = 0;

    string status = "Collect the key, then reach the exit.";

    // LEVEL 2 STATE
    int l2Row = 0;
    int l2Col = 0;
    int l2Lives = 3;

    // C = Blaze, S = Splash
    char l2Character = 'C';

    bool l2HasPotion = false;
    bool l2TorchLit = false;
    bool l2Won = false;
    bool l2GameOver = false;

    int l2FacingRow = 0;
    int l2FacingCol = 1;

    string l2Status = "Find the potion, then light the torch.";

    // LEVEL 3 GRAPHICAL STATE (Sprinty's trial)
    const int l3Rows = 5, l3Cols = 7;
    char l3Map[l3Rows][l3Cols] = {
        {'#','#','#','#','#','#','#'},
        {'#','#','#','.','.','B','#'},
        {'.','B','.','B','S','.','#'},
        {'B','S','.','.','.','.','#'},
        {'#','.','E','#','#','#','#'}
    };
    int l3Row = 2, l3Col = 0;
    int l3Lives = 3;
    int l3FacingRow = 0, l3FacingCol = 1;
    char l3PendingDirection = '\0';
    bool l3Won = false;
    bool l3GameOver = false;
    bool l3ShowGuide = true;
    string l3Status = "Use W/A/S/D to choose a direction.";

    auto resetLevel3 = [&]()
    {
        char freshMap[l3Rows][l3Cols] = {
            {'#','#','#','#','#','#','#'},
            {'#','#','#','.','.','B','#'},
            {'.','B','.','B','S','.','#'},
            {'B','S','.','.','.','.','#'},
            {'#','.','E','#','#','#','#'}
        };
        for (int r=0; r<l3Rows; r++)
            for (int c=0; c<l3Cols; c++) l3Map[r][c] = freshMap[r][c];
        l3Row=2; l3Col=0; l3Lives=3; l3PendingDirection='\0';
        l3Won=false; l3GameOver=false;
        l3FacingRow=0; l3FacingCol=1;
        l3Status="Use W/A/S/D to choose a direction.";
        l3ShowGuide=true;
        screen=LEVEL3_GAME;
    };

    auto resetLevel2 = [&]()
    {
        char freshMap[L2ROWS][L2COLS] =
        {
            {'.', '.', '#', '.', '.', '.', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'.', '.', '#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '#'},
            {'.', '#', '#', '#', '#', '.', 'F', '.', '.', '.', '.', 'P', '.', '.'},
            {'.', 'I', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
            {'.', '#', '.', '.', 'F', '#', '#', '#', '.', 'V', '#', '#', '#', '#'},
            {'.', '#', '.', '#', 'F', '.', 'W', 'W', '.', 'V', '#', '.', '.', '.'},
            {'.', '#', '#', '.', '.', '.', 'W', 'W', '.', 'V', '.', '.', '#', '.'},
            {'.', '.', '#', '.', '#', '#', '#', '#', '.', '.', '#', '.', '#', '.'},
            {'.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '#', '.', '#', '.'},
            {'.', '#', '#', '.', '#', '.', '.', 'T', '.', '.', '#', '#', '.', 'E'}
        };

        for (int r = 0; r < L2ROWS; r++)
        {
            for (int c = 0; c < L2COLS; c++)
            {
                level2Map[r][c] = freshMap[r][c];
            }
        }

        l2Row = 0;
        l2Col = 0;
        l2Lives = 3;
        l2Character = 'C';

        l2HasPotion = false;
        l2TorchLit = false;
        l2Won = false;
        l2GameOver = false;

        l2FacingRow = 0;
        l2FacingCol = 1;

        l2Status = "Find the potion, then light the torch.";
        screen = LEVEL2_GAME;
    };

    // LAYOUT
    const int tileSize = 39;
    const int gridX = 218;
    const int gridY = 145;

    Rectangle startButton = {350, 405, 300, 62};
    Rectangle helpButton = {350, 485, 145, 48};
    Rectangle quitButton = {505, 485, 145, 48};

    Rectangle level1Button = {250, 285, 500, 58};
    Rectangle level2Button = {250, 360, 500, 58};
    Rectangle level3Button = {250, 435, 500, 58};
    Rectangle backButton = {35, 35, 125, 45};
    bool showLevel1Info = false;
    bool showLevel2Info = false;

    Rectangle replayButton = {100, 445, 235, 58};
    Rectangle selectButton = {382, 445, 235, 58};
    Rectangle nextButton = {665, 445, 235, 58};

    auto drawText = [&](const char* text, float x, float y,
                        float size, Color color)
    {
        DrawTextEx(gameFont, text, {x, y}, size, 1.0f, color);
    };

    auto centeredText = [&](const char* text, float centerX, float y,
                            float size, Color color)
    {
        Vector2 textSize = MeasureTextEx(gameFont, text, size, 1.0f);
        drawText(text, centerX - textSize.x / 2, y, size, color);
    };

    auto button = [&](Rectangle rect, const char* label,
                      Color fill, float fontSize)
    {
        DrawRectangleRounded(rect, 0.16f, 8, fill);
        DrawRectangleRoundedLinesEx(rect, 0.16f, 8, 2, gold);

        centeredText(label,
                     rect.x + rect.width / 2,
                     rect.y + (rect.height - fontSize) / 2,
                     fontSize, RAYWHITE);
    };

    auto resetLevel1 = [&]()
    {
        rocky = Rocky();
        sprinty = Sprinty();
        grid = Grid();

        current = &rocky;
        hasKey = false;
        levelWon = false;
        moves = 0;

        status = "Collect the key, then reach the exit.";
        screen = LEVEL1_GAME;
    };

    // LEVEL 1 ART
    auto drawBrickWall = [&](int x, int y, int size)
    {
        DrawRectangle(x, y, size, size, {77, 73, 88, 255});
        DrawRectangle(x + 2, y + 2, size - 4, size - 4,
                      {105, 98, 110, 255});

        DrawLine(x, y + size / 2, x + size, y + size / 2,
                 {45, 44, 58, 255});

        DrawLine(x + size / 2, y, x + size / 2,
                 y + size / 2, {45, 44, 58, 255});

        DrawLine(x + size / 4, y + size / 2,
                 x + size / 4, y + size, {45, 44, 58, 255});

        DrawLine(x + size * 3 / 4, y + size / 2,
                 x + size * 3 / 4, y + size, {45, 44, 58, 255});

        DrawLine(x + 3, y + 3, x + size - 3, y + 3,
                 {135, 127, 139, 255});

        DrawRectangleLines(x, y, size, size, {37, 37, 51, 255});
    };

    auto drawGap = [&](int x, int y, int size)
    {
        DrawRectangle(x, y, size, size, {5, 8, 20, 255});

        for (int stripe = 0; stripe < 3; stripe++)
        {
            int stripeY = y + 8 + stripe * 10;
            DrawLine(x + 5, stripeY, x + size - 5, stripeY,
                     {76, 94, 126, 255});
        }

        DrawRectangleLines(x, y, size, size, {48, 57, 81, 255});
    };

    auto drawRocky = [&](float cx, float cy, float s)
    {
        Color stone = {153, 137, 111, 255};
        Color lightStone = {192, 171, 135, 255};
        Color darkStone = {83, 75, 66, 255};
        Color moss = {83, 133, 58, 255};
        Color leaf = {133, 179, 75, 255};

        DrawEllipse(cx, cy + 21*s, 15*s, 4*s, {5, 7, 15, 120});

        DrawLineEx({cx - 5*s, cy + 3*s},
                   {cx - 7*s, cy + 19*s}, 7*s, darkStone);
        DrawLineEx({cx + 5*s, cy + 3*s},
                   {cx + 8*s, cy + 19*s}, 7*s, darkStone);

        DrawEllipse(cx - 8*s, cy + 20*s, 7*s, 4*s, stone);
        DrawEllipse(cx + 8*s, cy + 20*s, 7*s, 4*s, stone);

        DrawLineEx({cx - 8*s, cy - 7*s},
                   {cx - 15*s, cy + 5*s}, 8*s, darkStone);
        DrawLineEx({cx + 8*s, cy - 7*s},
                   {cx + 15*s, cy + 5*s}, 8*s, darkStone);

        DrawCircle(cx - 16*s, cy + 7*s, 5*s, stone);
        DrawCircle(cx + 16*s, cy + 7*s, 5*s, stone);

        DrawPoly({cx, cy - 5*s}, 6, 12*s, 0, darkStone);
        DrawPoly({cx, cy - 6*s}, 6, 10*s, 0, stone);

        DrawCircle(cx - 8*s, cy - 10*s, 4.5f*s, moss);
        DrawCircle(cx + 8*s, cy - 10*s, 4.5f*s, moss);
        DrawCircle(cx - 8*s, cy - 12*s, 2*s, leaf);

        DrawPoly({cx, cy - 14*s}, 6, 9*s, 0, darkStone);
        DrawPoly({cx, cy - 15*s}, 6, 7.5f*s, 0, lightStone);

        DrawCircle(cx - 3*s, cy - 15*s, 1.8f*s, RAYWHITE);
        DrawCircle(cx + 3*s, cy - 15*s, 1.8f*s, RAYWHITE);

        DrawCircle(cx - 3*s, cy - 15*s, 0.9f*s, {80, 145, 67, 255});
        DrawCircle(cx + 3*s, cy - 15*s, 0.9f*s, {80, 145, 67, 255});

        DrawEllipse(cx + 3*s, cy - 23*s, 3*s, 5*s, moss);
        DrawLine((int)(cx + 3*s), (int)(cy - 20*s),
                 (int)(cx + 3*s), (int)(cy - 25*s), leaf);
    };

    auto drawSprinty = [&](float cx, float cy, float s)
    {
        Color outfit = {94, 67, 153, 255};
        Color lightPurple = {188, 158, 240, 255};
        Color hair = {121, 78, 177, 255};
        Color skin = {245, 211, 190, 255};

        DrawEllipse(cx, cy + 15*s, 12*s, 3*s, {5, 7, 15, 100});

        DrawLineEx({cx - 3*s, cy - 5*s},
                   {cx - 17*s, cy - 10*s}, 4*s, lightPurple);
        DrawLineEx({cx - 17*s, cy - 10*s},
                   {cx - 22*s, cy - 15*s}, 2*s, lightPurple);

        DrawLineEx({cx - 3*s, cy + 4*s},
                   {cx - 11*s, cy + 14*s}, 4*s, outfit);
        DrawLineEx({cx + 3*s, cy + 4*s},
                   {cx + 11*s, cy + 10*s}, 4*s, outfit);

        DrawLineEx({cx - 11*s, cy + 14*s},
                   {cx - 16*s, cy + 14*s}, 4*s, lightPurple);
        DrawLineEx({cx + 11*s, cy + 10*s},
                   {cx + 16*s, cy + 10*s}, 4*s, lightPurple);

        DrawPoly({cx, cy - 2*s}, 6, 7*s, 0, outfit);

        DrawLineEx({cx - 5*s, cy - 4*s},
                   {cx - 10*s, cy + 2*s}, 3.5f*s, outfit);
        DrawLineEx({cx + 5*s, cy - 4*s},
                   {cx + 11*s, cy - 9*s}, 3.5f*s, outfit);

        DrawCircle(cx, cy - 11*s, 6.5f*s, skin);
        DrawCircle(cx - 2*s, cy - 15*s, 6*s, hair);

        DrawEllipse(cx + 4*s, cy - 15*s,
                    4*s, 2.5f*s, lightPurple);

        DrawCircle(cx + 2*s, cy - 11*s, 1.1f*s,
                   {67, 48, 99, 255});

        DrawLineEx({cx + 12*s, cy - 18*s},
                   {cx + 17*s, cy - 20*s}, 1.5f*s, lightPurple);
        DrawLineEx({cx + 15*s, cy - 15*s},
                   {cx + 21*s, cy - 15*s}, 1.5f*s, lightPurple);
    };

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        // Login UI input. This is a visual prototype; credentials are not saved.
        if (screen == LOGIN)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if (key >= 32 && key <= 125)
                {
                    if (passwordFieldActive)
                    {
                        if (loginPassword.length() < 24)
                            loginPassword += (char)key;
                    }
                    else
                    {
                        if (loginUsername.length() < 24)
                            loginUsername += (char)key;
                    }
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (passwordFieldActive && !loginPassword.empty())
                    loginPassword.pop_back();
                else if (!passwordFieldActive && !loginUsername.empty())
                    loginUsername.pop_back();
            }

            if (IsKeyPressed(KEY_TAB))
                passwordFieldActive = !passwordFieldActive;

            if (IsKeyPressed(KEY_ENTER))
            {
                screen = MENU;
            }
        }

        // Toggle the guide for the currently active level.
        if (screen == LEVEL1_GAME && IsKeyPressed(KEY_H))
            showLevel1Info = !showLevel1Info;

        if (screen == LEVEL2_GAME && IsKeyPressed(KEY_H))
            showLevel2Info = !showLevel2Info;

        // LEVEL 1 INPUT
        if (screen == LEVEL1_GAME && !levelWon)
        {
            char direction = '\0';

            if (IsKeyPressed(KEY_W))
                direction = 'w';
            else if (IsKeyPressed(KEY_S))
                direction = 's';
            else if (IsKeyPressed(KEY_A))
                direction = 'a';
            else if (IsKeyPressed(KEY_D))
                direction = 'd';

            if (direction != '\0')
            {
                // Extra wall at row 10, column 4 (zero-based: row 9, column 3).
                int targetX = current->getX();
                int targetY = current->getY();
                if (direction == 'w') targetY--;
                else if (direction == 's') targetY++;
                else if (direction == 'a') targetX--;
                else if (direction == 'd') targetX++;

                bool extraWall = (targetY == 9 && targetX == 3);
                bool moved = false;
                if (!extraWall)
                    moved = grid.moveCharacter(*current, direction);

                if (moved)
                {
                    moves++;

                    if (grid.collectKey(*current))
                    {
                        hasKey = true;
                        status = "Key collected! Reach the exit.";
                    }

                    if (grid.reachedExit(*current))
                    {
                        if (hasKey)
                        {
                            levelWon = true;
                            status = "LEVEL 1 COMPLETED!";
                            screen = LEVEL_COMPLETE;
                        }
                        else
                        {
                            status = "Exit locked! Find the key first.";
                        }
                    }
                }
                else
                {
                    status = "Cannot move there. Try another direction.";
                }
            }

            if (IsKeyPressed(KEY_ONE) && current != &rocky)
            {
                rocky.setPosition(current->getX(), current->getY());
                current = &rocky;
                status = "Switched to Rocky.";
            }

            if (IsKeyPressed(KEY_TWO) && current != &sprinty)
            {
                sprinty.setPosition(current->getX(), current->getY());
                current = &sprinty;
                status = "Switched to Sprinty.";
            }

            if (IsKeyPressed(KEY_E))
            {
                status = current->getName() + " uses " +
                         current->getAbility() + "!";
            }

            if (IsKeyPressed(KEY_R))
                resetLevel1();
        }

        if (screen == LEVEL1_GAME &&
            (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE)))
        {
            screen = LEVEL_SELECT;
        }

        // LEVEL 2 INPUT
        if (screen == LEVEL2_GAME && !l2Won && !l2GameOver)
        {
            if (IsKeyPressed(KEY_ONE))
            {
                l2Character = 'C';
                l2Status = "Blaze selected.";
            }

            if (IsKeyPressed(KEY_TWO))
            {
                l2Character = 'S';
                l2Status = "Splash selected.";
            }

            if (IsKeyPressed(KEY_R))
                resetLevel2();

            if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE))
                screen = LEVEL_SELECT;

            int dr = 0;
            int dc = 0;

            if (IsKeyPressed(KEY_W))
                dr = -1;
            else if (IsKeyPressed(KEY_S))
                dr = 1;
            else if (IsKeyPressed(KEY_A))
                dc = -1;
            else if (IsKeyPressed(KEY_D))
                dc = 1;

            if (dr != 0 || dc != 0)
            {
                l2FacingRow = dr;
                l2FacingCol = dc;

                int nr = l2Row + dr;
                int nc = l2Col + dc;

                if (nr < 0 || nr >= L2ROWS ||
                    nc < 0 || nc >= L2COLS)
                {
                    l2Status = "The cave wall blocks your path.";
                }
                else if (level2Map[nr][nc] == '#')
                {
                    l2Status = "A wall blocks the way.";
                }
                else if (level2Map[nr][nc] == 'V' && !l2TorchLit)
                {
                    l2Status = "The gate is locked by darkness. Light the torch first.";
                }
                // FIX: Blaze loses one life when trying to enter fire.
                else if (level2Map[nr][nc] == 'F' &&
                         l2Character == 'C')
                {
                    l2Lives--;

                    l2Status = "Blaze touched fire! Lives left: " +
                               to_string(l2Lives);

                    if (l2Lives <= 0)
                    {
                        l2Lives = 0;
                        l2GameOver = true;
                        l2Status = "Blaze lost all three lives!";
                    }
                    else
                    {
                        l2Status += " Switch to Splash.";
                    }
                }
                else if (level2Map[nr][nc] == 'W' &&
                         l2Character == 'C')
                {
                    l2Status = "Blaze cannot pass through water. Switch to Splash.";
                }
                else if (level2Map[nr][nc] == 'I' &&
                         l2Character == 'S')
                {
                    l2Lives--;

                    l2Status = "Splash slipped on the ice! Lives left: " +
                               to_string(l2Lives);

                    if (l2Lives <= 0)
                    {
                        l2Lives = 0;
                        l2GameOver = true;
                    }
                }
                else if (level2Map[nr][nc] == 'E' && !l2TorchLit)
                {
                    l2Status = "The exit is locked. Light the torch first.";
                }
                else
                {
                    if (level2Map[nr][nc] == 'I' &&
                        l2Character == 'C')
                    {
                        level2Map[nr][nc] = '.';
                        l2Status = "Blaze melted the ice.";
                    }

                    l2Row = nr;
                    l2Col = nc;

                    if (level2Map[l2Row][l2Col] == 'P' &&
                        l2Character == 'C')
                    {
                        l2HasPotion = true;
                        level2Map[l2Row][l2Col] = '.';
                        l2Status = "Blaze collected the potion! Find the torch.";
                    }

                    if (level2Map[l2Row][l2Col] == 'E' &&
                        l2TorchLit)
                    {
                        l2Won = true;
                        l2Status = "LEVEL 2 COMPLETED!";
                        screen = LEVEL2_COMPLETE;
                    }
                }
            }

            if (IsKeyPressed(KEY_E))
            {
                if (level2Map[l2Row][l2Col] == 'P')
                {
                    if (l2Character == 'C')
                    {
                        l2HasPotion = true;
                        level2Map[l2Row][l2Col] = '.';
                        l2Status = "Blaze collected the potion!";
                    }
                    else
                    {
                        l2Status = "Blaze must collect the potion.";
                    }
                }
                else if (level2Map[l2Row][l2Col] == 'T')
                {
                    if (l2Character != 'C')
                    {
                        l2Status = "Only Blaze can light the torch.";
                    }
                    else if (!l2HasPotion)
                    {
                        l2Status = "Collect the potion first.";
                    }
                    else if (!l2TorchLit)
                    {
                        l2TorchLit = true;
                        l2Status = "Torch lit! The cave is now visible.";
                    }
                    else
                    {
                        l2Status = "The torch is already lit.";
                    }
                }
                else
                {
                    l2Status = "Nothing to interact with here.";
                }
            }
        }

        if (screen == LEVEL2_GAME && l2GameOver)
            screen = LEVEL2_PLACEHOLDER;

        // LEVEL 3 GRAPHICAL INPUT: choose direction, then one or two cells.
        if (screen == LEVEL3_GAME && !l3ShowGuide && !l3Won && !l3GameOver)
        {
            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_Q))
            {
                screen = LEVEL_SELECT;
                l3PendingDirection = '\0';
            }
            else if (l3PendingDirection == '\0')
            {
                if (IsKeyPressed(KEY_W)) { l3PendingDirection='w'; l3FacingRow=-1; l3FacingCol=0; }
                else if (IsKeyPressed(KEY_S)) { l3PendingDirection='s'; l3FacingRow=1; l3FacingCol=0; }
                else if (IsKeyPressed(KEY_A)) { l3PendingDirection='a'; l3FacingRow=0; l3FacingCol=-1; }
                else if (IsKeyPressed(KEY_D)) { l3PendingDirection='d'; l3FacingRow=0; l3FacingCol=1; }
                if (l3PendingDirection != '\0') l3Status = "Direction selected. Press 1 or 2.";
            }
            else
            {
                int steps=0;
                if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) steps=1;
                else if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)) steps=2;
                if (steps)
                {
                    int nr=l3Row+l3FacingRow*steps, nc=l3Col+l3FacingCol*steps;
                    if (nr<0 || nr>=l3Rows || nc<0 || nc>=l3Cols) l3Status="That move is outside the grid.";
                    else if (l3Map[nr][nc]=='#') l3Status="A wall blocks the landing cell.";
                    else if (l3Map[nr][nc]=='B') l3Status="Sprinty cannot push a boulder.";
                    else if (l3Map[nr][nc]=='E') { l3Row=nr; l3Col=nc; l3Won=true; l3Status="Exit reached! Level 3 trial complete."; }
                    else if (l3Map[nr][nc]=='S')
                    {
                        l3Map[nr][nc]='.'; l3Lives--;
                        if (l3Lives<=0) { l3GameOver=true; l3Status="Game over! Sprinty ran out of lives."; }
                        else { l3Row=2; l3Col=0; l3Status="Bomb! Lost one life and returned to start."; }
                    }
                    else { l3Row=nr; l3Col=nc; l3Status=(steps==1 ? "Moved one block." : "Jumped two blocks."); }
                    l3PendingDirection='\0';
                }
            }
        }

        // DRAW
        BeginDrawing();
        ClearBackground(background);

        if (screen == LOGIN)
        {
            centeredText("ELEMENTAL", 500, 82, 58, gold);
            centeredText("SQUAD", 500, 142, 54, SKYBLUE);
            centeredText("PLAYER LOGIN", 500, 215, 27, RAYWHITE);

            DrawText("USERNAME", 330, 262, 17, paleText);
            DrawRectangleRec(usernameField, {29, 34, 66, 255});
            DrawRectangleLinesEx(usernameField, 2,
                passwordFieldActive ? floorBorder : gold);
            DrawText(loginUsername.c_str(), 345, 299, 21, RAYWHITE);
            if (loginUsername.empty() && !passwordFieldActive)
                DrawText("Type your username...", 345, 299, 18,
                         {135, 143, 166, 255});

            DrawText("PASSWORD", 330, 327, 17, paleText);
            DrawRectangleRec(passwordField, {29, 34, 66, 255});
            DrawRectangleLinesEx(passwordField, 2,
                passwordFieldActive ? gold : floorBorder);
            string hiddenPassword(loginPassword.length(), '*');
            DrawText(hiddenPassword.c_str(), 345, 364, 21, RAYWHITE);
            if (loginPassword.empty() && passwordFieldActive)
                DrawText("Type your password...", 345, 364, 18,
                         {135, 143, 166, 255});

            button(loginButton, "CONTINUE", blue, 23);
            centeredText("UI DEMO  |  ACCOUNT SAVING COMES LATER",
                         500, 505, 15, paleText);
            centeredText("Click a field to type. Press Enter to continue.",
                         500, 545, 16, paleText);
        }
        else if (screen == MENU)
        {
            centeredText("ELEMENTAL", 500, 62, 65, gold);
            centeredText("SQUAD", 500, 130, 61, SKYBLUE);

            centeredText("FOUR ELEMENTS - ONE TEAM",
                         500, 221, 20, RAYWHITE);
            centeredText("ENDLESS PUZZLES", 500, 258, 19, paleText);

            drawRocky(290, 343, 1.0f);
            centeredText("ROCKY", 290, 385, 18, {181, 218, 164, 255});

            drawSprinty(430, 343, 1.0f);
            centeredText("SPRINTY", 430, 385, 18, {220, 205, 255, 255});

            drawBlaze(570, 343, 1.0f);
            centeredText("BLAZE", 570, 385, 18, {255, 180, 125, 255});

            drawSplash(710, 343, 1.0f);
            centeredText("SPLASH", 710, 385, 18, {160, 235, 218, 255});

            button(startButton, "START GAME", blue, 26);
            button(helpButton, "HOW TO PLAY", purple, 15);
            button(quitButton, "QUIT", purple, 20);

            centeredText(
                "CHOOSE YOUR HERO. SOLVE THE PUZZLE. SAVE THE SQUAD.",
                500, 575, 17, paleText);
        }
        else if (screen == LEVEL_SELECT)
        {
            centeredText("CHOOSE YOUR LEVEL", 500, 100, 43, gold);
            centeredText("Every level brings a new challenge.",
                         500, 165, 20, paleText);

            button(level1Button, "LEVEL 1 - THE BEGINNING", blue, 24);
            button(level2Button, "LEVEL 2 - THE DARK CAVE", purple, 24);
            button(level3Button, "LEVEL 3 - THE FOUR TRIALS",
                   {150, 63, 53, 255}, 24);
            button(backButton, "< BACK", purple, 18);
        }
        else if (screen == HOW_TO_PLAY)
        {
            centeredText("HOW TO PLAY", 500, 100, 46, gold);
            centeredText("W A S D - Move", 500, 210, 22, RAYWHITE);
            centeredText("1 - Switch to first character", 500, 250, 22, paleText);
            centeredText("2 - Switch to second character", 500, 290, 22, paleText);
            centeredText("E - Interact / use ability", 500, 330, 22, paleText);
            centeredText("R - Restart level", 500, 370, 22, paleText);
            centeredText("Q or ESC - Return to level menu", 500, 410, 22, paleText);
            button(backButton, "< BACK", purple, 18);
        }
        else if (screen == LEVEL1_GAME)
        {
            centeredText("LEVEL 1: THE BEGINNING", 500, 25, 30, gold);

            drawText(TextFormat("Character: %s",
                     current->getName().c_str()),
                     190, 70, 20, RAYWHITE);

            drawText(TextFormat("Moves: %d", moves),
                     190, 100, 18, paleText);

            drawText(hasKey ? "KEY: COLLECTED" : "KEY: NOT COLLECTED",
                     590, 70, 18, hasKey ? GREEN : gold);

            for (int row = 0; row < 10; row++)
            {
                for (int col = 0; col < 14; col++)
                {
                    int tile = grid.getTile(row, col);
                    // Render the added walls at row 10, column 4 and row 9, column 8.
                    if ((row == 9 && col == 3) || (row == 8 && col == 7))
                        tile = 1;
                    int x = gridX + col * tileSize;
                    int y = gridY + row * tileSize;
                    int size = tileSize - 2;

                    if (tile == 1)
                    {
                        drawBrickWall(x, y, size);
                    }
                    else if (tile == 3)
                    {
                        drawGap(x, y, size);
                    }
                    else
                    {
                        DrawRectangle(x, y, size, size, floorColor);
                        DrawRectangleLines(x, y, size, size, floorBorder);

                        if (tile == 2)
                        {
                            DrawCircle(x + size / 2, y + size / 2,
                                       13, {135, 112, 83, 255});
                            DrawCircle(x + size / 2 - 3, y + size / 2 - 4,
                                       5, {180, 151, 111, 255});
                        }
                        else if (tile == 4)
                        {
                            DrawCircle(x + 12, y + 12, 5, gold);
                            DrawRectangle(x + 15, y + 10, 13, 4, gold);
                            DrawRectangle(x + 23, y + 10, 3, 9, gold);
                        }
                        else if (tile == 5)
                        {
                            DrawRectangle(x + 8, y + 3, 22, 31,
                                          {105, 70, 47, 255});
                            DrawRectangle(x + 12, y + 7, 14, 25,
                                          {37, 116, 85, 255});
                        }
                    }
                }
            }

            float heroX = gridX + current->getX() * tileSize +
                          tileSize / 2.0f - 1;
            float heroY = gridY + current->getY() * tileSize +
                          tileSize / 2.0f + 1;

            if (current == &rocky)
                drawRocky(heroX, heroY, 0.65f);
            else
                drawSprinty(heroX, heroY, 0.65f);

            if (showLevel1Info)
            {
                DrawRectangleRounded(
                    {250, 165, 500, 330}, 0.08f, 8,
                    {27, 31, 57, 250}
                );
                DrawRectangleLinesEx({250, 165, 500, 330}, 2, gold);

                centeredText("LEVEL 1 GUIDE", 500, 178, 25, gold);
                drawText("ROCKY - Strong; can push boulders", 275, 215, 16,
                         {181, 218, 164, 255});
                drawText("SPRINTY - Fast character", 275, 240, 16,
                         {220, 205, 255, 255});

                // Draw visual symbols so the guide matches the game tiles.
                DrawRectangle(278, 275, 18, 18, {85, 82, 96, 255});
                DrawRectangleLines(278, 275, 18, 18, {170, 165, 180, 255});
                drawText("Wall - Blocks movement", 310, 275, 15, RAYWHITE);

                DrawCircle(287, 312, 9, {128, 132, 143, 255});
                DrawCircle(284, 309, 3, {180, 183, 190, 255});
                drawText("Boulder - Rocky can push it", 310, 302, 15, RAYWHITE);

                // Match the line-like gap symbol used on the Level 1 map.
                DrawRectangle(278, 332, 18, 16, {5, 8, 20, 255});
                DrawLine(281, 336, 293, 336, {76, 94, 126, 255});
                DrawLine(281, 340, 293, 340, {76, 94, 126, 255});
                DrawLine(281, 344, 293, 344, {76, 94, 126, 255});
                DrawRectangleLines(278, 332, 18, 16, {48, 57, 81, 255});
                drawText("Gap - Cross carefully", 310, 330, 15, RAYWHITE);

                DrawCircle(283, 369, 5, gold);
                DrawRectangle(286, 367, 13, 4, gold);
                DrawRectangle(294, 367, 3, 8, gold);
                drawText("Key - Collect before exiting", 310, 358, 15, RAYWHITE);

                DrawRectangleLinesEx({278, 388, 18, 20}, 2, {112, 210, 151, 255});
                DrawRectangle(283, 395, 8, 13, {112, 210, 151, 255});
                DrawCircle(287, 397, 2, {27, 31, 57, 255});
                drawText("Exit - Reach after collecting key", 310, 387, 15, RAYWHITE);

                centeredText("Press H to close the guide", 500, 455, 16, gold);
            }

            DrawRectangleRounded({160, 548, 680, 78}, 0.12f, 8,
                                 {27, 31, 57, 255});
            DrawRectangleLinesEx({160, 548, 680, 78}, 1, gold);

            centeredText("W A S D: MOVE    1: ROCKY    2: SPRINTY",
                         500, 558, 17, RAYWHITE);
            centeredText("E: ABILITY    H: GUIDE    R: RESTART    Q / ESC: MENU",
                         500, 581, 13, paleText);
            centeredText(status.c_str(), 500, 605, 14,
                         levelWon ? GREEN : gold);
        }
        else if (screen == LEVEL_COMPLETE)
        {
            DrawCircle(500, 145, 50, {43, 76, 70, 255});
            DrawCircleLines(500, 145, 50, gold);

            DrawLineEx({475, 145}, {493, 163}, 6, GREEN);
            DrawLineEx({493, 163}, {528, 125}, 6, GREEN);

            centeredText("LEVEL 1 COMPLETED!", 500, 225, 42, gold);
            centeredText("The key is yours. The exit is open!",
                         500, 285, 21, paleText);
            centeredText(TextFormat("Total moves: %d", moves),
                         500, 335, 25, RAYWHITE);
            centeredText("Ready for the next challenge?",
                         500, 380, 20, paleText);

            button(replayButton, "REPLAY LEVEL", purple, 18);
            button(selectButton, "LEVEL SELECT", blue, 18);
            button(nextButton, "NEXT LEVEL", {38, 112, 81, 255}, 18);
        }
        else if (screen == LEVEL2_GAME)
        {
            centeredText("LEVEL 2: THE DARK CAVE", 500, 18, 29, gold);

            drawText(TextFormat("Hero: %s",
                     l2Character == 'C' ? "Blaze" : "Splash"),
                     35, 58, 18, RAYWHITE);

            drawText(TextFormat("Lives: %d", l2Lives),
                     35, 83, 17, paleText);

            drawText(l2HasPotion ? "POTION: COLLECTED" :
                     "POTION: NOT COLLECTED",
                     300, 58, 16, l2HasPotion ? GREEN : gold);

            drawText(l2TorchLit ? "TORCH: LIT" : "TORCH: UNLIT",
                     650, 58, 16, l2TorchLit ? ORANGE : paleText);

            const int l2Tile = 40;
            const int l2GridX = 220;
            const int l2GridY = 105;

            for (int r = 0; r < L2ROWS; r++)
            {
                for (int c = 0; c < L2COLS; c++)
                {
                    int x = l2GridX + c * l2Tile;
                    int y = l2GridY + r * l2Tile;
                    char tile = level2Map[r][c];

                    bool gateTile = (tile == 'V');
                    bool caveTile = (c >= 10 && r >= 4);
                    bool currentTile = (r == l2Row && c == l2Col);

                    bool tileAhead =
                        (r == l2Row + l2FacingRow &&
                         c == l2Col + l2FacingCol);

                    bool visible = true;

                    if (caveTile && !gateTile)
                    {
                        visible = l2TorchLit &&
                                  (currentTile || tileAhead);
                    }

                    if (!visible)
                    {
                        DrawRectangle(x, y, l2Tile - 2, l2Tile - 2,
                                      {3, 4, 12, 255});
                        DrawRectangleLines(x, y, l2Tile - 2, l2Tile - 2,
                                           {8, 10, 22, 255});
                        continue;
                    }

                    Color floor = l2TorchLit
                        ? Color{40, 31, 25, 255}
                        : Color{17, 20, 31, 255};

                    DrawRectangle(x, y, l2Tile - 2, l2Tile - 2, floor);
                    DrawRectangleLines(x, y, l2Tile - 2, l2Tile - 2,
                        l2TorchLit
                            ? Color{126, 78, 39, 255}
                            : Color{45, 48, 62, 255});

                    if (tile == '#')
                    {
                        DrawRectangle(x + 1, y + 1, l2Tile - 4, l2Tile - 4,
                                      {65, 63, 77, 255});
                        DrawRectangleLines(x + 1, y + 1, l2Tile - 4,
                                           l2Tile - 4, {30, 31, 43, 255});
                        DrawLine(x + 3, y + 12, x + l2Tile - 5, y + 12,
                                 {37, 37, 49, 255});
                        DrawLine(x + 18, y + 2, x + 18, y + 12,
                                 {37, 37, 49, 255});
                        DrawLine(x + 10, y + 13, x + 10, y + l2Tile - 4,
                                 {37, 37, 49, 255});
                    }
                    else if (tile == 'F')
                    {
                        // A more recognizable flame silhouette instead of an orange dot.
                        DrawTriangle(
                            {(float)x + 19, (float)y + 3},
                            {(float)x + 7, (float)y + 25},
                            {(float)x + 12, (float)y + 31},
                            {190, 48, 30, 255});
                        DrawTriangle(
                            {(float)x + 19, (float)y + 7},
                            {(float)x + 31, (float)y + 25},
                            {(float)x + 26, (float)y + 31},
                            {190, 48, 30, 255});
                        DrawTriangle(
                            {(float)x + 19, (float)y + 10},
                            {(float)x + 9, (float)y + 28},
                            {(float)x + 29, (float)y + 28},
                            {255, 119, 35, 255});
                        DrawTriangle(
                            {(float)x + 20, (float)y + 19},
                            {(float)x + 15, (float)y + 30},
                            {(float)x + 25, (float)y + 30},
                            {255, 230, 125, 255});
                    }
                    else if (tile == 'P')
                    {
                        DrawRectangleRounded(
                            {(float)x + 12, (float)y + 11, 15, 22},
                            0.2f, 4, {126, 185, 96, 255});
                        DrawRectangle(x + 15, y + 7, 9, 5,
                                      {198, 208, 171, 255});
                        DrawCircle(x + 20, y + 22, 4,
                                   {224, 246, 170, 255});
                    }
                    else if (tile == 'I')
                    {
                        DrawRectangle(x + 6, y + 6, 26, 26,
                                      {139, 213, 239, 255});
                        DrawLine(x + 9, y + 11, x + 25, y + 25, RAYWHITE);
                        DrawLine(x + 25, y + 8, x + 15, y + 27,
                                 {201, 245, 255, 255});
                    }
                    else if (tile == 'V')
                    {
                        DrawRectangle(x + 8, y + 3, 24, 34,
                                      {28, 22, 23, 255});
                        DrawRectangleLines(x + 8, y + 3, 24, 34,
                            l2TorchLit
                                ? Color{255, 175, 82, 255}
                                : Color{105, 77, 54, 255});
                        DrawLine(x + 13, y + 7, x + 13, y + 32,
                                 {75, 58, 48, 255});
                        DrawLine(x + 27, y + 7, x + 27, y + 32,
                                 {75, 58, 48, 255});
                    }
                    else if (tile == 'W')
                    {
                        DrawRectangle(x + 2, y + 2, l2Tile - 6, l2Tile - 6,
                                      {17, 93, 135, 255});
                        DrawLine(x + 5, y + 12, x + 20, y + 8,
                                 {91, 213, 226, 255});
                        DrawLine(x + 19, y + 25, x + 32, y + 21,
                                 {91, 213, 226, 255});
                    }
                    else if (tile == 'T')
                    {
                        DrawLineEx({(float)x + 19, (float)y + 31},
                                   {(float)x + 19, (float)y + 12},
                                   4, {121, 73, 43, 255});

                        DrawCircle(x + 19, y + 10, 7,
                            l2TorchLit
                                ? Color{255, 171, 54, 255}
                                : Color{106, 67, 44, 255});

                        if (l2TorchLit)
                        {
                            DrawCircle(x + 19, y + 10, 3,
                                       {255, 237, 153, 255});
                        }
                    }
                    else if (tile == 'E')
                    {
                        DrawRectangle(x + 8, y + 4, 24, 32,
                                      {105, 70, 47, 255});
                        DrawRectangle(x + 12, y + 8, 16, 24,
                                      {29, 95, 77, 255});
                        DrawCircle(x + 24, y + 20, 2, gold);
                    }
                }
            }

            float hx = l2GridX + l2Col * l2Tile + l2Tile / 2.0f;
            float hy = l2GridY + l2Row * l2Tile + l2Tile / 2.0f;

            if (l2Character == 'C')
                drawBlaze(hx, hy, 0.78f);
            else
                drawSplash(hx, hy, 0.78f);

            if (showLevel2Info)
            {
                DrawRectangleRounded(
                    {225, 145, 550, 355}, 0.08f, 8,
                    {27, 31, 57, 250}
                );
                DrawRectangleLinesEx({225, 145, 550, 355}, 2, gold);

                centeredText("LEVEL 2 GUIDE - THE DARK CAVE",
                             500, 160, 22, gold);
                drawText("BLAZE - Melts ice; collects potion", 250, 198, 15,
                         {255, 180, 125, 255});
                drawText("SPLASH - Can cross water", 250, 222, 15,
                         {160, 235, 218, 255});
                // Visual symbols replace the letter codes in the guide.
                DrawRectangle(252, 258, 18, 18, {85, 82, 96, 255});
                DrawRectangleLines(252, 258, 18, 18, {145, 139, 157, 255});
                drawText("Wall - Blocks movement", 282, 258, 15, RAYWHITE);

                DrawTriangle({261, 282}, {251, 300}, {271, 300}, {255, 126, 43, 255});
                DrawTriangle({261, 289}, {255, 299}, {267, 299}, {255, 226, 116, 255});
                drawText("Fire - Dangerous to Blaze", 282, 283, 15, RAYWHITE);

                DrawEllipse(261, 321, 11, 7, {31, 137, 190, 255});
                DrawLine(253, 319, 260, 316, {137, 230, 246, 255});
                DrawLine(262, 325, 269, 322, {137, 230, 246, 255});
                drawText("Water - Blocks Blaze", 282, 308, 15, RAYWHITE);

                DrawRectangle(252, 333, 18, 18, {139, 213, 239, 255});
                DrawLine(254, 336, 267, 348, RAYWHITE);
                DrawLine(267, 335, 258, 349, RAYWHITE);
                drawText("Ice - Blaze can melt it", 282, 333, 15, RAYWHITE);

                DrawRectangleRounded({254, 359, 14, 18}, 0.2f, 4, {126, 185, 96, 255});
                DrawRectangle(257, 355, 8, 5, {198, 208, 171, 255});
                DrawCircle(261, 368, 3, {224, 246, 170, 255});
                drawText("Potion - Collect with Blaze", 282, 358, 15, RAYWHITE);

                DrawLineEx({261, 405}, {261, 386}, 3, {121, 73, 43, 255});
                DrawTriangle({261, 390}, {254, 400}, {268, 400}, {255, 157, 54, 255});
                drawText("Torch - Light after potion", 282, 383, 15, RAYWHITE);

                DrawRectangle(252, 408, 18, 18, {35, 29, 30, 255});
                DrawRectangleLines(252, 408, 18, 18, {255, 175, 82, 255});
                drawText("Gate - Opens after torch is lit", 282, 408, 15, RAYWHITE);

                DrawRectangle(254, 433, 14, 18, {29, 95, 77, 255});
                DrawRectangleLines(254, 433, 14, 18, {145, 197, 163, 255});
                DrawCircle(265, 442, 1.5f, gold);
                drawText("Exit - Reach after lighting torch", 282, 433, 15, RAYWHITE);
                centeredText("Press H to close the guide", 500, 470, 15, gold);
            }

            DrawRectangleRounded({125, 525, 750, 94},
                                 0.12f, 8, {27, 31, 57, 255});
            DrawRectangleLinesEx({125, 525, 750, 94}, 1, gold);

            centeredText("W A S D: MOVE     1: BLAZE     2: SPLASH",
                         500, 535, 16, RAYWHITE);
            centeredText("E: INTERACT    H: GUIDE    R: RESTART    Q / ESC: LEVEL SELECT",
                         500, 558, 12, paleText);
            centeredText(l2Status.c_str(), 500, 584, 14,
                         l2TorchLit ? Color{255, 190, 106, 255} : gold);
        }
        else if (screen == LEVEL2_COMPLETE)
        {
            DrawCircle(500, 145, 50, {43, 76, 70, 255});
            DrawCircleLines(500, 145, 50, gold);

            DrawLineEx({475, 145}, {493, 163}, 6, GREEN);
            DrawLineEx({493, 163}, {528, 125}, 6, GREEN);

            centeredText("LEVEL 2 COMPLETED!", 500, 225, 40, gold);
            centeredText("The dark cave has been conquered.",
                         500, 285, 21, paleText);
            centeredText("Blaze lit the way for the squad!",
                         500, 325, 20, RAYWHITE);

            button({350, 410, 300, 58}, "LEVEL SELECT", blue, 20);
        }
        else if (screen == LEVEL2_PLACEHOLDER)
        {
            centeredText("LEVEL 2 FAILED", 500, 170, 45, gold);
            centeredText("The cave has claimed all three lives.",
                         500, 240, 21, paleText);

            button({350, 350, 300, 58}, "RETRY LEVEL 2", purple, 20);
            button({350, 425, 300, 58}, "LEVEL SELECT", blue, 20);
        }
        else if (screen == LEVEL3_PLACEHOLDER)
        {
            centeredText("LEVEL 3", 500, 155, 48, gold);
            centeredText("THE FOUR TRIALS", 500, 215, 30, paleText);
            centeredText("Play Sprinty's graphical trial", 500, 290, 21, RAYWHITE);
            button(backButton, "< BACK", purple, 18);
            button({350, 410, 300, 58}, "START LEVEL 3", blue, 20);
        }
        else if (screen == LEVEL3_GAME)
        {
            centeredText("LEVEL 3", 500, 22, 32, gold);
            if (l3ShowGuide)
            {
                centeredText("CHARACTERS & SYMBOL GUIDE", 500, 82, 26, gold);
                DrawText("1  ROCKY    - strength / boulder pushing", 100, 130, 18, RAYWHITE);
                DrawText("2  SPRINTY  - speed / jump 1 or 2 blocks", 100, 162, 18, RAYWHITE);
                DrawText("3  SPLASH   - water abilities", 100, 194, 18, RAYWHITE);
                DrawText("4  BLAZE    - fire / torch abilities", 100, 226, 18, RAYWHITE);
                DrawText("# Wall   B Boulder   ! Bomb   SW Switch", 100, 280, 18, paleText);
                DrawText("C# Coded wall   0 Pit   K Key   P Potion", 100, 312, 18, paleText);
                DrawText("T Torch   E Exit   . Empty floor", 100, 344, 18, paleText);
                button({350, 430, 300, 58}, "CONTINUE", blue, 20);
                button(backButton, "< BACK", purple, 18);
            }
            else
            {
                drawText(TextFormat("Lives: %d", l3Lives), 45, 55, 18, paleText);
                drawText("Move: W A S D", 45, 82, 17, paleText);
                drawText(l3PendingDirection!='\0' ? "Now press 1 or 2" : "Choose direction, then distance", 45, 106, 17, gold);
                const int t=66, gx=269, gy=145;
                for (int r=0; r<l3Rows; r++) for (int c=0; c<l3Cols; c++)
                {
                    int x=gx+c*t, y=gy+r*t; char tile=l3Map[r][c];
                    DrawRectangle(x,y,t-4,t-4,{23,29,53,255});
                    DrawRectangleLines(x,y,t-4,t-4,{57,67,99,255});
                    if(tile=='#') { DrawRectangle(x+3,y+3,t-10,t-10,{70,75,97,255}); DrawRectangleLines(x+3,y+3,t-10,t-10,{106,111,132,255}); }
                    else if(tile=='B') { DrawCircle(x+t/2-2,y+t/2-2,17,{176,94,83,255}); DrawCircleLines(x+t/2-2,y+t/2-2,17,{237,157,130,255}); }
                    else if(tile=='S') { DrawCircle(x+t/2-2,y+t/2-2,16,{225,76,76,255}); DrawText("!",x+t/2-8,y+t/2-15,28,RAYWHITE); }
                    else if(tile=='E') { DrawRectangle(x+11,y+8,t-26,t-15,{65,147,103,255}); DrawRectangleLines(x+11,y+8,t-26,t-15,LIME); }
                    if(r==l3Row && c==l3Col) drawSprinty(x+t/2-2,y+t/2+8,1.05f);
                }
                DrawRectangleRounded({80,505,840,104},0.08f,8,{27,31,57,255});
                DrawRectangleLinesEx({80,505,840,104},1,gold);
                centeredText(l3Status.c_str(),500,520,18,RAYWHITE);
                centeredText(l3PendingDirection!='\0' ? "Press 1 or 2 to confirm" : "W/A/S/D: direction   Q/ESC: level select",500,555,16,gold);
                if (l3Won || l3GameOver)
                {
                    DrawRectangleRounded({260,235,480,125},0.12f,8,{18,20,48,245});
                    DrawRectangleLinesEx({260,235,480,125},2,gold);
                    centeredText(l3Won ? "TRIAL COMPLETE!" : "GAME OVER",500,255,29,gold);
                    button({350,305,300,45},"RETRY LEVEL 3",blue,17);
                }
            }
        }
        else if (screen == GAME_COMPLETE)
        {
            centeredText("ELEMENTAL SQUAD", 500, 150, 45, gold);
            centeredText("THE SQUAD HAS SAVED THE DAY!",
                         500, 235, 28, GREEN);
            centeredText("Congratulations, hero!",
                         500, 300, 24, RAYWHITE);
            button({350, 410, 300, 58}, "RETURN TO MENU", blue, 20);
        }

        EndDrawing();

        // BUTTON INPUT
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (screen == LOGIN)
            {
                if (CheckCollisionPointRec(mouse, usernameField))
                    passwordFieldActive = false;
                else if (CheckCollisionPointRec(mouse, passwordField))
                    passwordFieldActive = true;
                else if (CheckCollisionPointRec(mouse, loginButton))
                    screen = MENU;
            }
            else if (screen == MENU)
            {
                if (CheckCollisionPointRec(mouse, startButton))
                    screen = LEVEL_SELECT;
                else if (CheckCollisionPointRec(mouse, helpButton))
                    screen = HOW_TO_PLAY;
                else if (CheckCollisionPointRec(mouse, quitButton))
                    break;
            }
            else if (screen == LEVEL_SELECT)
            {
                if (CheckCollisionPointRec(mouse, backButton))
                    screen = MENU;
                else if (CheckCollisionPointRec(mouse, level1Button))
                    resetLevel1();
                else if (CheckCollisionPointRec(mouse, level2Button))
                    resetLevel2();
                else if (CheckCollisionPointRec(mouse, level3Button))
                {
                    // Launch the newer standalone four-character Level 3.
                    // Build level3_graphics in this same project folder first.
                    int result = system("./level3_graphics");
                    (void)result;
                    screen = LEVEL_SELECT;
                }
            }
            else if (screen == HOW_TO_PLAY)
            {
                if (CheckCollisionPointRec(mouse, backButton))
                    screen = MENU;
            }
            else if (screen == LEVEL_COMPLETE)
            {
                if (CheckCollisionPointRec(mouse, replayButton))
                    resetLevel1();
                else if (CheckCollisionPointRec(mouse, selectButton))
                    screen = LEVEL_SELECT;
                else if (CheckCollisionPointRec(mouse, nextButton))
                    resetLevel2();
            }
            else if (screen == LEVEL2_COMPLETE)
            {
                if (CheckCollisionPointRec(mouse, {350, 410, 300, 58}))
                    screen = LEVEL_SELECT;
            }
            else if (screen == LEVEL2_PLACEHOLDER)
            {
                if (CheckCollisionPointRec(mouse, {350, 350, 300, 58}))
                    resetLevel2();
                else if (CheckCollisionPointRec(mouse, {350, 425, 300, 58}) ||
                         CheckCollisionPointRec(mouse, backButton))
                    screen = LEVEL_SELECT;
            }
            else if (screen == LEVEL3_PLACEHOLDER)
            {
                if (CheckCollisionPointRec(mouse, backButton)) screen = LEVEL_SELECT;
                else if (CheckCollisionPointRec(mouse, {350, 410, 300, 58})) resetLevel3();
            }
            else if (screen == LEVEL3_GAME && l3ShowGuide)
            {
                if (CheckCollisionPointRec(mouse, backButton)) screen = LEVEL_SELECT;
                else if (CheckCollisionPointRec(mouse, {350,430,300,58}))
                {
                    l3ShowGuide = false;
                    l3Status = "Use W/A/S/D to choose a direction.";
                }
            }
            else if (screen == LEVEL3_GAME && (l3Won || l3GameOver))
            {
                if (CheckCollisionPointRec(mouse, {350,305,300,45})) resetLevel3();
            }
            else if (screen == GAME_COMPLETE)
            {
                if (CheckCollisionPointRec(mouse, {350, 410, 300, 58}))
                    screen = MENU;
            }
        }
    }

    if (customFontLoaded)
        UnloadFont(gameFont);

    CloseWindow();
    return 0;
}