// ============================================================================
//  Elemental Squad - LEVEL 3: THE FOUR TRIALS  (Raylib graphics)
//
//  Game rules are ported from level3.cpp, and the map comes straight from
//  Grid3 (grid3.cpp), so the console and graphical versions stay identical.
//
//  Build (add grid3.cpp):
//    g++ level3_graphics.cpp grid3.cpp -o level3_graphics -lraylib -lm -lpthread -ldl
//  (use the same raylib link flags you already use for graphics_main.cpp)
// ============================================================================
#include "raylib.h"
#include "grid3.h"
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <cstdio>

using namespace std;

// ---- Art copied from graphics_main.cpp so Level 3 matches Levels 1 and 2 ----

void drawBrickWall(int x, int y, int size)
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
    }

void drawGap(int x, int y, int size)
    {
        DrawRectangle(x, y, size, size, {5, 8, 20, 255});

        for (int stripe = 0; stripe < 3; stripe++)
        {
            int stripeY = y + 8 + stripe * 10;
            DrawLine(x + 5, stripeY, x + size - 5, stripeY,
                     {76, 94, 126, 255});
        }

        DrawRectangleLines(x, y, size, size, {48, 57, 81, 255});
    }

void drawRocky(float cx, float cy, float s)
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
    }

void drawSprinty(float cx, float cy, float s)
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
    }

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


// ============================================================================
//  CONSTANTS
// ============================================================================
static const int ROWS = 10, COLS = 14, TILE = 48, GX = 24, GY = 76;
static const int WIN_W = 1100, WIN_H = 700;
static const int START_R[4] = {0, 2, 5, 8};   // same starts as level3.cpp
static const int START_C[4] = {0, 7, 9, 6};

static const Color BG      = {18, 20, 48, 255};
static const Color GOLDEN  = {245, 196, 104, 255};
static const Color PALE    = {218, 224, 239, 255};
static const Color BLUE_BT = {44, 105, 153, 255};
static const Color PURP_BT = {91, 63, 133, 255};
static const Color BORDER  = {52, 60, 88, 255};

// quadrant / stage order: 0 Rocky (top-left), 1 Sprinty (top-right),
//                         2 Blaze (bottom-right), 3 Splash (bottom-left)
static const char* HERO_NAME[4]  = {"Rocky", "Sprinty", "Blaze", "Splash"};
static const char* TRIAL_NAME[4] = {"ROCKY'S TRIAL", "SPRINTY'S TRIAL", "BLAZE'S TRIAL", "SPLASH'S TRIAL"};
static const char* SKILL_1[4] = {"Strength: pushes boulders and",
                                 "Agility: hold SHIFT with a",
                                 "Fire: lights the torch and",
                                 "Water: the maze is hidden!"};
static const char* SKILL_2[4] = {"smashes cracked walls (hammer).",
                                 "direction to jump two tiles.",
                                 "reveals the coded walls.",
                                 "Press E to reveal it (2 uses)."};
static const Color HERO_COL[4]  = {{181, 218, 164, 255}, {220, 205, 255, 255},
                                   {255, 180, 125, 255}, {160, 235, 218, 255}};
static const Color FLOOR_COL[4] = {{34, 29, 30, 255}, {25, 22, 45, 255},
                                   {42, 26, 26, 255}, {16, 33, 42, 255}};
static const float HERO_SCALE[4] = {0.78f, 1.0f, 1.0f, 1.0f};
static const float HERO_YOFF[4]  = {0.0f, 4.0f, 4.0f, 4.0f};

static void (*drawHeroFn[4])(float, float, float) = {drawRocky, drawSprinty, drawBlaze, drawSplash};

static void drawHeroAt(int p, float cx, float cy, float m)
{
    drawHeroFn[p](cx, cy + HERO_YOFF[p] * m, HERO_SCALE[p] * m);
}

// ============================================================================
//  GAME STATE  (mirrors the Level3 class in level3.cpp)
// ============================================================================
struct MoveState
{
    int stage, row, col;
    bool pushed;
    int fromR, fromC, toR, toC;
};

static Grid3 grid;
static int stage, row, col, lives, faceR, faceC, revealUses;
static int pRow[4], pCol[4];
static bool hasHammer, hasRockyKey, switchOpened, wrongSwitchHit;
static bool hasPotion, torchLit, codeSolved, hasSplashKey;
static bool gridRevealed, codeInputMode, gameOver, gameWon;
static bool codeRevealed[3], stageDone[4];
static double revealStart;
static string message, codeInput;
static vector<string> inventory;
static stack<MoveState> undoStack;
static float flash = 0.0f;
static float vx[4], vy[4];          // smooth on-screen hero positions (in tiles)
static Font gFont;

static void resetGame()
{
    grid = Grid3();
    stage = 0;
    lives = 3;
    for (int i = 0; i < 4; i++)
    {
        pRow[i] = START_R[i];
        pCol[i] = START_C[i];
        vx[i] = (float)pCol[i];
        vy[i] = (float)pRow[i];
        stageDone[i] = false;
    }
    row = pRow[0];
    col = pCol[0];
    faceR = 0;
    faceC = 1;
    hasHammer = hasRockyKey = switchOpened = wrongSwitchHit = false;
    hasPotion = torchLit = codeSolved = hasSplashKey = false;
    gridRevealed = codeInputMode = gameOver = gameWon = false;
    for (int i = 0; i < 3; i++) codeRevealed[i] = false;
    revealUses = 0;
    revealStart = 0;
    inventory.clear();
    undoStack = stack<MoveState>();
    codeInput.clear();
    flash = 0.0f;
    message = "Find your way through all four puzzles.";
}

static bool inGrid(int r, int c) { return r >= 0 && r < ROWS && c >= 0 && c < COLS; }
static int quadOf(int r, int c) { return r < 5 ? (c < 7 ? 0 : 1) : (c < 7 ? 3 : 2); }
static bool insideArea(int r, int c) { return inGrid(r, c) && quadOf(r, c) == stage; }
static bool isWallTile(const string& t) { return t == "#" || t == "CW" || t == "C#"; }
static void syncPos() { pRow[stage] = row; pCol[stage] = col; }

static void addItem(const string& s)
{
    for (const string& i : inventory) if (i == s) return;
    inventory.push_back(s);
}

static bool exitLocked(int q)
{
    if (stageDone[q]) return false;
    if (q == 0) return !hasRockyKey;
    if (q == 1) return !switchOpened;
    if (q == 2) return !codeSolved;
    return !hasSplashKey;
}

// ============================================================================
//  GAME LOGIC  (ported from level3.cpp)
// ============================================================================
static void saveMove(int oldStage, int oldRow, int oldCol, bool pushed = false,
                     int fr = 0, int fc = 0, int tr = 0, int tc = 0)
{
    undoStack.push({oldStage, oldRow, oldCol, pushed, fr, fc, tr, tc});
}

static void undoMove()
{
    if (undoStack.empty()) { message = "No moves available to undo."; return; }
    MoveState p = undoStack.top();
    undoStack.pop();
    if (p.pushed) { grid.tiles[p.fromR][p.fromC] = "B"; grid.tiles[p.toR][p.toC] = "."; }
    stage = p.stage; row = p.row; col = p.col;
    syncPos();
    message = "Undo successful! Previous position restored.";
}

static void loseLife(const string& reason)
{
    flash = 1.0f;
    lives--;
    if (lives <= 0) { gameOver = true; message = "Game over! You have no lives remaining."; return; }
    message = reason + " Lives remaining: " + to_string(lives);
    row = START_R[stage];
    col = START_C[stage];
    syncPos();
}

static void activateSwitch(int r, int c)
{
    if (r == 3 && c == 8)       { switchOpened = true; message = "Correct switch! The exit is now unlocked."; }
    else if (r == 2 && c == 11) { wrongSwitchHit = true; message = "Wrong switch! The exit is still locked."; }
    else                        { message = "This switch does not open the exit."; }
}

static void collectItem(const string& tile, int r, int c)
{
    if (tile == "H")
    {
        hasHammer = true; addItem("Hammer");
        grid.tiles[r][c] = ".";
        message = "You collected the hammer!";
    }
    else if (tile == "K")
    {
        if (stage == 0)      { hasRockyKey = true;  addItem("Rocky key");  message = "You collected Rocky's key!"; }
        else if (stage == 3) { hasSplashKey = true; addItem("Splash key"); message = "You collected Splash's key!"; }
        grid.tiles[r][c] = ".";
    }
    else if (tile == "P")
    {
        hasPotion = true; addItem("Potion");
        grid.tiles[r][c] = ".";
        message = "You collected the potion!";
    }
    else if (tile == "SW") activateSwitch(r, c);
    else if (tile == "BO") { grid.tiles[r][c] = "."; loseLife("You stepped on a bomb!"); }
    else if (tile == "0")  { grid.tiles[r][c] = "."; loseLife("You fell into a pit! The pit collapsed."); }
    syncPos();
}

static void nextPuzzle()
{
    syncPos();
    stageDone[stage] = true;
    undoStack = stack<MoveState>();     // undo only works inside the current trial
    if (stage == 0)      { stage = 1; message = "Rocky's puzzle is complete. Continue to the next trial."; }
    else if (stage == 1) { stage = 2; message = "Sprinty's puzzle is complete. Continue to the next trial."; }
    else if (stage == 2) { stage = 3; message = "Blaze's puzzle is complete. Continue to the final trial."; }
    else                 { gameWon = true; message = "Congratulations! You completed Level 3!"; return; }
    row = pRow[stage];
    col = pCol[stage];
    faceR = 0;
    faceC = 1;
}

static bool allCodesRevealed() { return codeRevealed[0] && codeRevealed[1] && codeRevealed[2]; }

static void revealCodeAt(int r, int c)
{
    if (!hasPotion || !torchLit) { message = "Collect the potion and light the torch first."; return; }
    if (r == 6 && c == 8)        { codeRevealed[0] = true; message = "First wall code revealed: 1"; }
    else if (r == 7 && c == 10)  { codeRevealed[1] = true; message = "Second wall code revealed: 2"; }
    else if (r == 8 && c == 11)  { codeRevealed[2] = true; message = "Third wall code revealed: 3"; }
    else                         { message = "This coded wall has no code assigned."; }
}

static void interactWithExit()
{
    if (stage == 0)
    {
        if (hasRockyKey) nextPuzzle(); else message = "The exit is locked. Find the hidden key.";
    }
    else if (stage == 1)
    {
        if (switchOpened) nextPuzzle(); else message = "The exit is locked. Activate the correct switch.";
    }
    else if (stage == 2)
    {
        if (codeSolved) nextPuzzle();
        else if (!hasPotion || !torchLit) message = "Collect the potion and light the torch first.";
        else if (!allCodesRevealed()) message = "Reveal all three wall codes first.";
        else { codeInputMode = true; codeInput.clear(); message = "Enter the three-digit code."; }
    }
    else
    {
        if (hasSplashKey) nextPuzzle(); else message = "The exit is locked. Find Splash's key.";
    }
}

static void interact()
{
    if (stage == 3)
    {
        int tr = row + faceR, tc = col + faceC;
        if (inGrid(tr, tc) && grid.tiles[tr][tc] == "E") { interactWithExit(); return; }
        if (revealUses >= 2) { message = "No map reveals remaining for Splash."; return; }
        gridRevealed = true;
        revealUses++;
        revealStart = GetTime();
        message = "Map revealed for 5 seconds! Uses remaining: " + to_string(2 - revealUses);
        return;
    }

    if (stage == 2 && grid.tiles[row][col] == "T" && !torchLit)
    {
        if (!hasPotion) { message = "Collect the potion before lighting the torch."; return; }
        torchLit = true;
        message = "Torch lit! You can now reveal the wall codes.";
        return;
    }

    int tr = row + faceR, tc = col + faceC;
    if (!inGrid(tr, tc)) { message = "Nothing to interact with in that direction."; return; }
    string tile = grid.tiles[tr][tc];

    if (tile == "E") interactWithExit();
    else if (stage == 0 && tile == "CW")
    {
        if (!hasHammer) { message = "You need the hammer to crack this wall."; return; }
        if (tr == 0 && tc == 5) { grid.tiles[tr][tc] = "K"; message = "You cracked the wall! A key is revealed."; }
        else                    { grid.tiles[tr][tc] = ".";  message = "You cracked the wall."; }
    }
    else if (stage == 1 && tile == "SW") activateSwitch(tr, tc);
    else if (stage == 2 && tile == "T")
    {
        if (!hasPotion)       message = "Collect the potion before lighting the torch.";
        else if (!torchLit) { torchLit = true; message = "Torch lit! You can now reveal the wall codes."; }
        else                  message = "The torch is already lit. Look for the wall codes.";
    }
    else if (stage == 2 && tile == "C#") revealCodeAt(tr, tc);
    else message = "Nothing to interact with here.";
}

static void stepMove(int dr, int dc)
{
    faceR = dr; faceC = dc;
    int oldR = row, oldC = col, oldStage = stage, oldLives = lives;
    int nr = row + dr, nc = col + dc;

    if (!insideArea(nr, nc)) { message = "You cannot leave this puzzle area."; return; }
    string tile = grid.tiles[nr][nc];
    if (isWallTile(tile))    { message = "A wall blocks the way."; return; }
    if (tile == "E")         { message = "You are facing the exit. Press E to use it."; return; }

    bool pushed = false;
    int bTr = 0, bTc = 0;
    if (tile == "B")
    {
        if (stage != 0) { message = "This character cannot push the boulder."; return; }
        int br = nr + dr, bc = nc + dc;
        if (!insideArea(br, bc) || grid.tiles[br][bc] != ".")
        {
            message = "The boulder cannot be pushed further.";
            return;
        }
        grid.tiles[br][bc] = "B";
        grid.tiles[nr][nc] = ".";
        pushed = true; bTr = br; bTc = bc;
    }

    row = nr; col = nc;
    syncPos();
    collectItem(tile, row, col);

    if (lives == oldLives && row == nr && col == nc)
        saveMove(oldStage, oldR, oldC, pushed, nr, nc, bTr, bTc);
}

static void jumpMove(int dr, int dc)     // Sprinty's two-tile jump
{
    faceR = dr; faceC = dc;
    int oldR = row, oldC = col, oldStage = stage, oldLives = lives;
    int nr = row + 2 * dr, nc = col + 2 * dc;

    if (!insideArea(nr, nc)) { message = "Sprinty cannot jump outside this puzzle area."; return; }
    string tile = grid.tiles[nr][nc];
    if (isWallTile(tile))    { message = "Sprinty cannot land on a wall."; return; }
    if (tile == "E")         { message = "Sprinty is facing the exit. Press E to use it."; return; }
    if (tile == "B")         { message = "Sprinty cannot push boulders."; return; }

    row = nr; col = nc;
    syncPos();
    collectItem(tile, row, col);

    if (lives == oldLives && row == nr && col == nc)
    {
        saveMove(oldStage, oldR, oldC);
        if (tile == ".") message = "Sprinty jumped two tiles!";
    }
}

// ============================================================================
//  DRAWING HELPERS
// ============================================================================
static void txt(const char* s, float x, float y, float sz, Color c) { DrawTextEx(gFont, s, {x, y}, sz, 1.0f, c); }
static void ctr(const char* s, float cx, float y, float sz, Color c)
{
    Vector2 m = MeasureTextEx(gFont, s, sz, 1.0f);
    txt(s, cx - m.x / 2, y, sz, c);
}
static void btn(Rectangle r, const char* label, Color fill, float sz)
{
    DrawRectangleRounded(r, 0.16f, 8, fill);
    DrawRectangleRoundedLinesEx(r, 0.16f, 8, 2, GOLDEN);
    ctr(label, r.x + r.width / 2, r.y + (r.height - sz) / 2, sz, RAYWHITE);
}
static void heart(float cx, float cy, float s, bool full)
{
    Color c = full ? Color{230, 70, 90, 255} : Color{60, 64, 86, 255};
    DrawCircle((int)(cx - s * 0.5f), (int)(cy - s * 0.2f), s * 0.56f, c);
    DrawCircle((int)(cx + s * 0.5f), (int)(cy - s * 0.2f), s * 0.56f, c);
    DrawTriangle({cx - s * 1.03f, cy}, {cx, cy + s * 1.2f}, {cx + s * 1.03f, cy}, c);
}

// One function draws every tile type (also used for the guide + inventory icons).
// legend = true draws a neutral "preview" version with no game-state effects.
static void drawTileArt(const string& t, int r, int c, float x, float y, float z, bool legend = false)
{
    int q = legend ? 0 : quadOf(r, c);
    float cx = x + z / 2, cy = y + z / 2, k = z / 40.0f;
    float tm = (float)GetTime();
    float bob = sinf(tm * 3.0f + x * 0.07f) * 1.5f;
    bool wall = (t == "#" || t == "CW" || t == "C#");
    bool potionTorch = !legend && hasPotion && torchLit;

    if (!wall)
    {
        DrawRectangleRec({x, y, z, z}, FLOOR_COL[q]);
        DrawRectangleLinesEx({x, y, z, z}, 1, BORDER);
    }

    if (t == "#")
    {
        drawBrickWall((int)x, (int)y, (int)z);
    }
    else if (t == "CW")
    {
        drawBrickWall((int)x, (int)y, (int)z);
        Color cr = {255, 170, 90, 255};
        DrawLineEx({cx + 3 * k, y + 2 * k}, {cx - 3 * k, cy - 5 * k}, 2.2f, cr);
        DrawLineEx({cx - 3 * k, cy - 5 * k}, {cx + 4 * k, cy + 3 * k}, 2.2f, cr);
        DrawLineEx({cx + 4 * k, cy + 3 * k}, {cx - 2 * k, y + z - 3 * k}, 2.2f, cr);
        DrawLineEx({cx - 3 * k, cy - 5 * k}, {x + 4 * k, cy - 9 * k}, 1.6f, cr);
    }
    else if (t == "C#")
    {
        DrawRectangleRec({x + 1, y + 1, z - 2, z - 2}, {60, 50, 88, 255});
        DrawRectangleLinesEx({x + 1, y + 1, z - 2, z - 2}, 2, {30, 26, 48, 255});
        if (potionTorch) DrawRectangleRec({x + 3, y + 3, z - 6, z - 6}, Fade(PURPLE, 0.28f));
        Color rune = potionTorch ? Color{200, 150, 255, 255} : Color{110, 98, 140, 255};
        DrawPoly({cx, cy}, 4, z * 0.27f, 0, rune);
        DrawPoly({cx, cy}, 4, z * 0.17f, 0, {60, 50, 88, 255});
        int idx = (r == 6 && c == 8) ? 0 : (r == 7 && c == 10) ? 1 : (r == 8 && c == 11) ? 2 : -1;
        if (!legend && idx >= 0 && codeRevealed[idx])
        {
            DrawRectangleRec({x + 4, y + 4, z - 8, z - 8}, {30, 24, 50, 255});
            char d[2] = {(char)('1' + idx), 0};
            ctr(d, cx, cy - 15, 30, GOLDEN);
        }
    }
    else if (t == "B")
    {
        DrawCircle((int)cx, (int)(cy + 2), 14 * k, {104, 84, 62, 255});
        DrawCircle((int)cx, (int)(cy + 1), 13 * k, {135, 112, 83, 255});
        DrawCircle((int)(cx - 4 * k), (int)(cy - 3 * k), 5 * k, {180, 151, 111, 255});
    }
    else if (t == "H")
    {
        DrawLineEx({cx - 9 * k, cy + 12 * k + bob}, {cx + 5 * k, cy - 6 * k + bob}, 4.5f, {150, 100, 60, 255});
        DrawLineEx({cx - 2 * k, cy - 11.5f * k + bob}, {cx + 12 * k, cy - 0.5f * k + bob}, 8 * k, {200, 205, 215, 255});
    }
    else if (t == "K")
    {
        DrawCircle((int)(cx - 8 * k), (int)(cy - 4 * k + bob), 6 * k, GOLDEN);
        DrawCircle((int)(cx - 8 * k), (int)(cy - 4 * k + bob), 2.5f * k, FLOOR_COL[q]);
        DrawRectangleRec({cx - 3 * k, cy - 6 * k + bob, 16 * k, 4 * k}, GOLDEN);
        DrawRectangleRec({cx + 8 * k, cy - 6 * k + bob, 3 * k, 9 * k}, GOLDEN);
        DrawRectangleRec({cx + 3 * k, cy - 6 * k + bob, 3 * k, 6 * k}, GOLDEN);
    }
    else if (t == "P")
    {
        DrawRectangleRounded({cx - 8 * k, cy - 5 * k + bob, 16 * k, 20 * k}, 0.35f, 4, {126, 185, 96, 255});
        DrawRectangleRec({cx - 4 * k, cy - 12 * k + bob, 8 * k, 8 * k}, {198, 208, 171, 255});
        DrawCircle((int)cx, (int)(cy + 4 * k + bob), 3.5f * k, {224, 246, 170, 255});
    }
    else if (t == "T")
    {
        bool lit = legend ? true : torchLit;
        float fy = y + z * 0.28f;
        DrawLineEx({cx, y + z * 0.86f}, {cx, y + z * 0.36f}, 4 * k, {121, 73, 43, 255});
        if (lit)
        {
            float fl = sinf(tm * 12.0f + x) * 1.2f;
            DrawCircle((int)cx, (int)fy, 17 * k, Fade(ORANGE, 0.22f));
            DrawCircle((int)cx, (int)fy, (7 + fl) * k, {255, 171, 54, 255});
            DrawCircle((int)cx, (int)fy, 3.5f * k, {255, 237, 153, 255});
        }
        else DrawCircle((int)cx, (int)fy, 6.5f * k, {106, 67, 44, 255});
    }
    else if (t == "E")
    {
        bool locked = !legend && exitLocked(q);
        DrawRectangleRec({cx - 12 * k, y + 3 * k, 24 * k, z - 6 * k}, {105, 70, 47, 255});
        DrawRectangleRec({cx - 8 * k, y + 7 * k, 16 * k, z - 14 * k},
                         locked ? Color{29, 95, 77, 255} : Color{52, 190, 120, 255});
        if (locked)
        {
            DrawCircleLines((int)cx, (int)(cy - 2 * k), 4.5f * k, GOLDEN);
            DrawRectangleRounded({cx - 5 * k, cy - 1 * k, 10 * k, 8 * k}, 0.3f, 4, GOLDEN);
        }
        else
        {
            DrawRectangleLinesEx({cx - 12 * k, y + 3 * k, 24 * k, z - 6 * k}, 2, {140, 255, 190, 255});
            DrawCircle((int)(cx + 4 * k), (int)cy, 2 * k, GOLDEN);
        }
    }
    else if (t == "BO")
    {
        DrawCircle((int)cx, (int)(cy + 3 * k), 12 * k, {38, 40, 54, 255});
        DrawCircle((int)(cx - 4 * k), (int)(cy - 1 * k), 3.5f * k, {110, 116, 140, 255});
        DrawLineEx({cx + 3 * k, cy - 7 * k}, {cx + 9 * k, cy - 14 * k}, 2.5f, {190, 150, 90, 255});
        DrawCircle((int)(cx + 9 * k), (int)(cy - 15 * k), (2.5f + sinf(tm * 14.0f) * 1.2f) * k, {255, 214, 90, 255});
    }
    else if (t == "SW")
    {
        int st = 0;
        if (!legend)
        {
            if (r == 3 && c == 8 && switchOpened) st = 1;
            else if (r == 2 && c == 11 && wrongSwitchHit) st = 2;
        }
        Color lc = st == 1 ? Color{90, 220, 140, 255} : st == 2 ? Color{235, 80, 80, 255} : Color{255, 165, 60, 255};
        float tipX = cx + (st ? 9 * k : -9 * k);
        DrawRectangleRounded({cx - 13 * k, cy + 4 * k, 26 * k, 10 * k}, 0.4f, 4, {72, 78, 104, 255});
        DrawLineEx({cx, cy + 8 * k}, {tipX, cy - 9 * k}, 3.5f, {170, 175, 195, 255});
        DrawCircle((int)tipX, (int)(cy - 9 * k), 5 * k, lc);
    }
    else if (t == "0")
    {
        drawGap((int)x, (int)y, (int)z);
        DrawEllipse((int)cx, (int)cy, z * 0.28f, z * 0.17f, {0, 0, 6, 255});
    }
}

// ============================================================================
//  SCENES
// ============================================================================
static const Rectangle GUIDE_BTN  = {400, 604, 300, 56};
static const Rectangle END_RETRY  = {335, 390, 200, 50};
static const Rectangle END_EXIT   = {565, 390, 200, 50};

static void drawGuide(bool started)
{
    DrawRectangle(0, 0, WIN_W, WIN_H, {18, 20, 48, 250});
    ctr("LEVEL 3: THE FOUR TRIALS", 550, 30, 36, GOLDEN);
    ctr("Four heroes, one connected map. Finish the trials clockwise: Rocky, Sprinty, Blaze, Splash.", 550, 82, 16, PALE);

    txt("CONTROLS", 70, 130, 20, SKYBLUE);
    const char* ctl[6] = {"W A S D or Arrow keys - Move",
                          "SHIFT + direction - Sprinty jumps 2 tiles",
                          "E - Interact with the tile you face",
                          "U - Undo your last move",
                          "R - Restart the level",
                          "H - This guide     ESC - Leave Level 3"};
    for (int i = 0; i < 6; i++) txt(ctl[i], 70, 165 + i * 30, 16, PALE);

    txt("THE SQUAD", 70, 370, 20, SKYBLUE);
    for (int i = 0; i < 4; i++)
    {
        drawHeroAt(i, 105 + i * 95, 440, 1.25f);
        ctr(HERO_NAME[i], 105 + i * 95, 485, 15, HERO_COL[i]);
    }

    txt("SYMBOLS", 470, 130, 20, SKYBLUE);
    const char* code[12] = {"#", "B", "CW", "H", "K", "BO", "SW", "0", "P", "T", "C#", "E"};
    const char* desc[12] = {"Wall", "Boulder (Rocky pushes)", "Cracked wall (hammer)", "Hammer",
                            "Key", "Bomb: -1 life", "Switch (only one is right)", "Pit: -1 life",
                            "Potion", "Torch (Blaze lights)", "Coded wall: shows a digit", "Exit"};
    for (int i = 0; i < 12; i++)
    {
        float x = 470.0f + (i / 6) * 300, y = 168.0f + (i % 6) * 62;
        drawTileArt(code[i], -1, -1, x, y, 44, true);
        txt(desc[i], x + 56, y + 13, 15, PALE);
    }

    btn(GUIDE_BTN, started ? "CONTINUE" : "START LEVEL 3", BLUE_BT, 22);
    ctr("ENTER to continue   |   ESC to leave Level 3", 550, 672, 14, PALE);
}

static void drawCodePad()
{
    DrawRectangle(0, 0, WIN_W, WIN_H, {10, 12, 30, 170});
    DrawRectangleRounded({330, 230, 440, 250}, 0.08f, 8, {27, 31, 57, 255});
    DrawRectangleRoundedLinesEx({330, 230, 440, 250}, 0.08f, 8, 2, GOLDEN);
    ctr("BLAZE'S EXIT: ENTER THE CODE", 550, 252, 24, GOLDEN);
    for (int i = 0; i < 3; i++)
    {
        float x = 550.0f - 116 + i * 84;
        DrawRectangleRounded({x, 305, 64, 80}, 0.15f, 6, {18, 20, 48, 255});
        DrawRectangleRoundedLinesEx({x, 305, 64, 80}, 0.15f, 6, 2, (int)codeInput.size() == i ? GOLDEN : BORDER);
        if (i < (int)codeInput.size())
        {
            char d[2] = {codeInput[i], 0};
            ctr(d, x + 32, 321, 46, RAYWHITE);
        }
    }
    ctr("Type the digits from the glowing walls", 550, 405, 15, PALE);
    ctr("ENTER: confirm     BACKSPACE: delete     ESC: cancel", 550, 432, 14, PALE);
}

static void drawEnd()
{
    DrawRectangle(0, 0, WIN_W, WIN_H, {10, 12, 30, 190});
    DrawRectangleRounded({300, 220, 500, 250}, 0.08f, 8, {27, 31, 57, 255});
    DrawRectangleRoundedLinesEx({300, 220, 500, 250}, 0.08f, 8, 2, GOLDEN);
    if (gameWon)
    {
        ctr("LEVEL 3 COMPLETE!", 550, 248, 36, GOLDEN);
        ctr("All four trials solved. The Elemental Squad wins!", 550, 305, 18, GREEN);
        for (int i = 0; i < 4; i++) drawHeroAt(i, 440 + i * 75, 358, 0.8f);
    }
    else
    {
        ctr("GAME OVER", 550, 248, 38, GOLDEN);
        ctr("The squad ran out of lives.", 550, 310, 19, PALE);
    }
    btn(END_RETRY, gameWon ? "PLAY AGAIN" : "TRY AGAIN", BLUE_BT, 19);
    btn(END_EXIT, "EXIT", PURP_BT, 19);
    ctr("R: restart     ESC: exit", 550, 445, 13, PALE);
}

static void drawScene()
{
    float t = (float)GetTime();
    const float z = TILE - 2;
    bool fogOn = (stage == 3 && !gridRevealed && !gameWon);
    bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    txt("LEVEL 3: THE FOUR TRIALS", 24, 10, 28, GOLDEN);

    // ---- area labels ----
    for (int q = 0; q < 4; q++)
    {
        float lx = GX + ((q == 0 || q == 3) ? 0 : 7) * TILE;
        float ly = (q < 2) ? (float)(GY - 22) : (float)(GY + ROWS * TILE + 3);
        Color lc = stageDone[q] ? Color{110, 220, 150, 255} : (q == stage ? GOLDEN : Color{120, 128, 158, 255});
        string s = TRIAL_NAME[q];
        if (stageDone[q]) s += "  - DONE";
        txt(s.c_str(), lx, ly, 15, lc);
    }

    // ---- tiles ----
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
        {
            float x = (float)(GX + c * TILE), y = (float)(GY + r * TILE);
            int q = quadOf(r, c);
            if (q == 3 && fogOn)
            {
                DrawRectangleRec({x, y, z, z}, {10, 14, 28, 255});
                DrawRectangleLinesEx({x, y, z, z}, 1, {26, 34, 58, 255});
                ctr("?", x + z / 2, y + z / 2 - 11, 22, Fade(SKYBLUE, 0.30f + 0.22f * sinf(t * 2.0f + r + c)));
            }
            else drawTileArt(grid.tiles[r][c], r, c, x, y, z);

            if (q != stage && !stageDone[q]) DrawRectangleRec({x, y, z, z}, {8, 10, 24, 135});
            if (stageDone[q]) DrawRectangleRec({x, y, z, z}, {40, 160, 90, 26});
        }

    // ---- area frames ----
    for (int q = 0; q < 4; q++)
    {
        float x0 = (float)(GX + ((q == 0 || q == 3) ? 0 : 7) * TILE);
        float y0 = (float)(GY + (q < 2 ? 0 : 5) * TILE);
        DrawRectangleLinesEx({x0 - 1, y0 - 1, 7 * TILE + 0.0f, 5 * TILE + 0.0f}, q == stage ? 3.0f : 1.0f,
                             q == stage ? GOLDEN : Color{70, 78, 110, 255});
    }

    // ---- facing tile highlight + Sprinty jump preview ----
    if (!gameOver && !gameWon)
    {
        int fr = row + faceR, fc = col + faceC;
        if (insideArea(fr, fc))
            DrawRectangleLinesEx({(float)(GX + fc * TILE), (float)(GY + fr * TILE), z, z}, 2,
                                 Fade(GOLDEN, 0.45f + 0.3f * sinf(t * 6.0f)));
        if (stage == 1 && shift)
        {
            const int dR[4] = {-1, 1, 0, 0}, dC[4] = {0, 0, -1, 1};
            for (int i = 0; i < 4; i++)
            {
                int lr = row + 2 * dR[i], lc = col + 2 * dC[i];
                if (!insideArea(lr, lc)) continue;
                const string& lt = grid.tiles[lr][lc];
                if (isWallTile(lt) || lt == "B" || lt == "E") continue;
                DrawRectangleLinesEx({(float)(GX + lc * TILE), (float)(GY + lr * TILE), z, z}, 3, Fade(SKYBLUE, 0.9f));
            }
        }
    }

    // ---- heroes (active one drawn last, on top) ----
    for (int pass = 0; pass < 2; pass++)
        for (int p = 0; p < 4; p++)
        {
            if ((p == stage) != (pass == 1)) continue;
            float cx = GX + vx[p] * TILE + TILE / 2.0f - 1;
            float cy = GY + vy[p] * TILE + TILE / 2.0f + 2;
            if (p == stage && !gameOver && !gameWon)
            {
                cy += sinf(t * 4.0f) * 1.5f;
                DrawEllipseLines((int)cx, (int)(cy + 16), 15, 5, GOLDEN);
            }
            drawHeroAt(p, cx, cy, 1.0f);
            if (stageDone[p])
            {
                DrawCircle((int)(cx + 12), (int)(cy - 20), 8, {40, 150, 90, 255});
                DrawLineEx({cx + 8, cy - 20}, {cx + 11, cy - 17}, 2, RAYWHITE);
                DrawLineEx({cx + 11, cy - 17}, {cx + 16, cy - 24}, 2, RAYWHITE);
            }
        }

    // ================= right panel =================
    DrawRectangleRounded({716, 56, 360, 632}, 0.03f, 8, {27, 31, 57, 255});
    DrawRectangleRoundedLinesEx({716, 56, 360, 632}, 0.03f, 8, 1, GOLDEN);

    txt("ACTIVE HERO", 736, 70, 15, GOLDEN);
    drawHeroAt(stage, 780, 132, 1.5f);
    txt(HERO_NAME[stage], 840, 96, 26, HERO_COL[stage]);
    txt(SKILL_1[stage], 840, 132, 13, PALE);
    txt(SKILL_2[stage], 840, 151, 13, PALE);

    txt("LIVES", 736, 190, 15, GOLDEN);
    for (int i = 0; i < 3; i++) heart(765 + i * 40, 222, 12, i < lives);

    txt("TRIAL PROGRESS", 736, 262, 15, GOLDEN);
    char pb[4][96];
    int codes = (int)codeRevealed[0] + (int)codeRevealed[1] + (int)codeRevealed[2];
    snprintf(pb[0], 96, "Hammer: %s  |  Key: %s", hasHammer ? "yes" : "no", hasRockyKey ? "yes" : "no");
    snprintf(pb[1], 96, "%s", switchOpened ? "Correct switch pressed" : "Find the correct switch");
    snprintf(pb[2], 96, "Potion: %s | Torch: %s | Codes: %d/3", hasPotion ? "yes" : "no", torchLit ? "lit" : "unlit", codes);
    snprintf(pb[3], 96, "Key: %s  |  Map reveals left: %d", hasSplashKey ? "yes" : "no", 2 - revealUses);
    for (int i = 0; i < 4; i++)
    {
        float y = 288.0f + i * 58;
        if (stageDone[i])
        {
            DrawCircle(744, (int)(y + 12), 11, {40, 150, 90, 255});
            DrawLineEx({738, y + 12}, {742, y + 16}, 2.5f, RAYWHITE);
            DrawLineEx({742, y + 16}, {750, y + 7}, 2.5f, RAYWHITE);
        }
        else if (i == stage)
        {
            DrawCircle(744, (int)(y + 12), 11, Fade(GOLDEN, 0.25f));
            DrawCircleLines(744, (int)(y + 12), 11, GOLDEN);
            DrawCircle(744, (int)(y + 12), 4, GOLDEN);
        }
        else DrawCircleLines(744, (int)(y + 12), 11, {80, 88, 120, 255});
        txt(TextFormat("%s", HERO_NAME[i]), 768, y, 17, i == stage ? RAYWHITE : (stageDone[i] ? Color{110, 220, 150, 255} : Color{130, 138, 165, 255}));
        txt(pb[i], 768, y + 22, 13, stageDone[i] ? Color{110, 220, 150, 255} : PALE);
    }

    txt("INVENTORY", 736, 528, 15, GOLDEN);
    for (int i = 0; i < 4; i++)
    {
        float x = 736.0f + i * 80;
        DrawRectangleRounded({x, 552, 60, 60}, 0.15f, 6, {18, 20, 48, 255});
        DrawRectangleRoundedLinesEx({x, 552, 60, 60}, 0.15f, 6, 1, BORDER);
        if (i < (int)inventory.size())
        {
            const string& it = inventory[i];
            string icon = it == "Hammer" ? "H" : it == "Potion" ? "P" : "K";
            drawTileArt(icon, -1, -1, x + 6, 558, 48, true);
            ctr(it.c_str(), x + 30, 616, 11, PALE);
        }
    }
    txt(TextFormat("Undo moves available: %d", (int)undoStack.size()), 736, 646, 13, PALE);
    txt("Press H for the symbol guide", 736, 664, 13, PALE);

    // ================= bottom panel =================
    DrawRectangleRounded({24, 586, 672, 102}, 0.1f, 8, {27, 31, 57, 255});
    DrawRectangleRoundedLinesEx({24, 586, 672, 102}, 0.1f, 8, 1, GOLDEN);
    ctr(message.c_str(), 360, 600, 17, RAYWHITE);
    ctr(stage == 1 ? "W A S D: move    SHIFT + direction: jump 2 tiles    E: interact"
                   : "W A S D: move    E: interact (face the object first)", 360, 632, 13, PALE);
    ctr("U: undo    R: restart    H: guide    ESC: leave level", 360, 652, 13, PALE);
    if (gridRevealed)
    {
        float left = 5.0f - (float)(GetTime() - revealStart);
        if (left < 0) left = 0;
        DrawRectangleRec({60, 672, 600, 8}, {18, 20, 48, 255});
        DrawRectangleRec({60, 672, 600 * (left / 5.0f), 8}, SKYBLUE);
    }

    if (flash > 0) DrawRectangle(0, 0, WIN_W, WIN_H, Fade(RED, flash * 0.35f));
}

// ============================================================================
//  MAIN
// ============================================================================
int main()
{
    InitWindow(WIN_W, WIN_H, "Elemental Squad - Level 3");
    SetExitKey(KEY_NULL);               // ESC is handled by us (cancel / close / leave)
    SetTargetFPS(60);

    gFont = GetFontDefault();
    bool customFont = false;
    if (FileExists("assets/DejaVuSans.ttf"))
    {
        gFont = LoadFont("assets/DejaVuSans.ttf");
        customFont = true;
    }

    resetGame();
    bool started = false, guide = true, quit = false;

    while (!WindowShouldClose() && !quit)
    {
        float dt = GetFrameTime();
        Vector2 mouse = GetMousePosition();
        bool click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // Splash's map reveal lasts 5 seconds.
        if (stage == 3 && gridRevealed && GetTime() - revealStart >= 5.0)
        {
            gridRevealed = false;
            message = "Time is up! Splash's map is hidden again.";
        }
        if (flash > 0) flash -= dt * 1.6f;

        // ---------------- input ----------------
        if (guide)
        {
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_H) ||
                (click && CheckCollisionPointRec(mouse, GUIDE_BTN)))
            {
                guide = false;
                started = true;
            }
            else if (IsKeyPressed(KEY_ESCAPE))
            {
                if (started) guide = false; else quit = true;
            }
        }
        else if (gameWon || gameOver)
        {
            if (IsKeyPressed(KEY_R) || (click && CheckCollisionPointRec(mouse, END_RETRY))) resetGame();
            else if (IsKeyPressed(KEY_ESCAPE) || (click && CheckCollisionPointRec(mouse, END_EXIT))) quit = true;
        }
        else if (codeInputMode)
        {
            int ch = GetCharPressed();
            while (ch > 0)
            {
                if (ch >= '0' && ch <= '9' && codeInput.size() < 3) codeInput += (char)ch;
                ch = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !codeInput.empty()) codeInput.pop_back();
            if (IsKeyPressed(KEY_ESCAPE)) { codeInputMode = false; codeInput.clear(); message = "Code entry cancelled."; }
            else if (IsKeyPressed(KEY_ENTER))
            {
                if (codeInput.size() < 3) message = "Type all three digits first.";
                else
                {
                    if (codeInput == "123") { codeSolved = true; message = "Correct code! Face the exit and press E."; }
                    else                    { message = "Incorrect code. Try again at the exit."; }
                    codeInputMode = false;
                    codeInput.clear();
                }
            }
        }
        else
        {
            if (IsKeyPressed(KEY_ESCAPE)) quit = true;
            else if (IsKeyPressed(KEY_H)) guide = true;
            else if (IsKeyPressed(KEY_R)) resetGame();
            else if (IsKeyPressed(KEY_U)) undoMove();
            else if (IsKeyPressed(KEY_E)) interact();
            else
            {
                int dr = 0, dc = 0;
                if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) dr = -1;
                else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) dr = 1;
                else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) dc = -1;
                else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) dc = 1;

                if (dr != 0 || dc != 0)
                {
                    bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
                    if (stage == 1 && shift) jumpMove(dr, dc);
                    else stepMove(dr, dc);
                }
            }
        }

        // heroes glide toward their tile
        float f = 16.0f * dt;
        if (f > 1.0f) f = 1.0f;
        for (int i = 0; i < 4; i++)
        {
            vx[i] += ((float)pCol[i] - vx[i]) * f;
            vy[i] += ((float)pRow[i] - vy[i]) * f;
        }

        // ---------------- draw ----------------
        BeginDrawing();
        ClearBackground(BG);
        drawScene();
        if (codeInputMode) drawCodePad();
        if (gameWon || gameOver) drawEnd();
        if (guide) drawGuide(started);
        EndDrawing();
    }

    if (customFont) UnloadFont(gFont);
    CloseWindow();
    return 0;
}
