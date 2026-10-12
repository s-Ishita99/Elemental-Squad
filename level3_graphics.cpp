#include "raylib.h"
#include <string>
#include <stack>
#include <cstring>
using namespace std;

// Elemental Squad - Level 3 graphics.
// The 10x14 layout and every tile position are copied from grid3.cpp.
// Controls: WASD/arrows, 1-4 switch characters, E ability, U undo, R restart, ESC menu.
namespace {
constexpr int ROWS = 10, COLS = 14, TILE = 54, TOP = 132;
constexpr int SCREEN_W = COLS * TILE + 40;
constexpr int SCREEN_H = ROWS * TILE + TOP + 86;

const char* names[4] = {"Rocky", "Sprinty", "Blaze", "Splash"};
const char symbols[4] = {'R', 'S', 'F', 'W'};
const char* abilities[4] = {
    "Hammer: cracked walls + boulders",
    "Jump: bombs and switches",
    "Potion + torch: coded walls",
    "Key: pits and water/fire"
};

char board[ROWS][COLS];
int pr[4] = {0, 2, 5, 8}, pc[4] = {0, 7, 9, 6};
int active = 0;
int lives = 3;
bool hasHammer = false, hasRockyKey = false, hasSplashKey = false;
bool hasPotion = false, torchLit = false, switchOpened = false;
bool menuOpen = true, selectionOpen = false, instructionsOpen = false;
bool gameOver = false, gameWon = false;
bool completed[4] = {false, false, false, false};
bool sprintyMovePending = false;
int sprintyDr = 0, sprintyDc = 0;
bool splashMapVisible = false;
float splashRevealStart = 0.0f;
int revealedCodes = 0;
string status = "Choose Play to begin.";

struct Move { int who, r, c; };
stack<Move> undoMoves;

void resetBoard() {
    // Exact tile layout from grid3.cpp. Do not move these tiles.
    const char* rocky[5][7] = {
        {".", ".", "B", ".", ".", "CW", "#"},
        {"#", "B", ".", "B", ".", ".", "#"},
        {".", ".", "B", "CW", ".", ".", "E"},
        {"H", ".", ".", ".", ".", ".", "#"},
        {"#", "#", "#", "#", "#", "#", "#"}
    };
    const char* sprinty[5][7] = {
        {"#", "#", "#", "#", "#", "#", "#"},
        {"#", "#", "#", ".", ".", "BO", "#"},
        {".", "BO", ".", "BO", "SW", ".", "#"},
        {"BO", "SW", ".", ".", ".", ".", "#"},
        {"#", ".", "E", "#", "#", "#", "#"}
    };
    const char* splash[5][7] = {
        {"#", "#", "#", "#", "#", "0", "#"},
        {"#", "K", "#", ".", ".", ".", "#"},
        {"0", ".", "0", ".", "0", ".", "#"},
        {"E", ".", ".", ".", "0", ".", "."},
        {"#", "#", "0", "#", "#", "#", "#"}
    };
    const char* blaze[5][7] = {
        {"#", "#", ".", "#", "#", "#", "#"},
        {"#", "C#", ".", ".", ".", "P", "#"},
        {"#", ".", ".", "C#", ".", "#", "#"},
        {"E", "T", ".", ".", "C#", ".", "#"},
        {"#", "#", "#", "#", "#", "#", "#"}
    };

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 7; c++) {
            // grid3.cpp uses strings for multi-character tiles. Keep those
            // meanings in this graphical version via one-character markers.
            board[r][c] = rocky[r][c][0];
            board[r][c + 7] = sprinty[r][c][0];
            board[r + 5][c] = splash[r][c][0];
            board[r + 5][c + 7] = blaze[r][c][0];
        }
    }
    // Preserve grid3.cpp's four start/opening cells.
    board[0][0] = '.';
    board[2][7] = '.';
    board[5][9] = '.';
    board[8][6] = '.';

    // Multi-character symbols are rendered internally as unique chars.
    board[0][5] = 'X'; board[2][3] = 'X';       // Rocky cracked walls (CW)
    board[1][12] = 'O'; board[2][8] = 'O';
    board[2][10] = 'O'; board[3][7] = 'O';      // Sprinty bombs (BO)
    board[2][11] = 'S'; board[3][8] = 'S';      // Sprinty switches (SW)
    board[6][8] = 'D'; board[7][10] = 'D'; board[8][11] = 'D'; // Blaze coded walls (C#)

    pr[0] = 0; pc[0] = 0;
    pr[1] = 2; pc[1] = 7;
    pr[2] = 5; pc[2] = 9;
    pr[3] = 8; pc[3] = 6;
    active = 0; lives = 3;
    hasHammer = hasRockyKey = hasSplashKey = false;
    hasPotion = torchLit = switchOpened = false;
    gameOver = gameWon = false;
    for (int i = 0; i < 4; ++i) completed[i] = false;
    sprintyMovePending = false; sprintyDr = sprintyDc = 0;
    splashMapVisible = false; splashRevealStart = 0.0f; revealedCodes = 0;
    undoMoves = stack<Move>();
    status = "Choose a character with 1-4. Find items and use E near obstacles.";
}

bool inBounds(int r, int c) {
    return r >= 0 && r < ROWS && c >= 0 && c < COLS;
}
void rememberMove(int who) { undoMoves.push({who, pr[who], pc[who]}); }

void loseLife(const char* reason) {
    --lives;
    if (lives <= 0) {
        lives = 0; gameOver = true;
        status = string(reason) + " No lives left. Press R to restart.";
        return;
    }
    status = string(reason) + " Lives left: " + to_string(lives) + ". Returned to start.";
    if (active == 0) { pr[0] = 0; pc[0] = 0; }
    else if (active == 1) { pr[1] = 2; pc[1] = 7; }
    else if (active == 2) { pr[2] = 5; pc[2] = 9; }
    else { pr[3] = 8; pc[3] = 6; }
}

void movePlayer(int dr, int dc) {
    if (gameOver || gameWon) return;
    int r = pr[active] + dr, c = pc[active] + dc;
    if (!inBounds(r, c)) { status = "You cannot leave the map."; return; }
    char t = board[r][c];

    if (t == '#') { status = "A wall blocks the way."; return; }
    if (t == 'X') {
        status = active == 0 ? (hasHammer ? "Press E to smash this cracked wall." : "Rocky needs to collect the hammer first.")
                             : "Cracked walls belong to Rocky. Switch to Rocky.";
        return;
    }
    if (t == 'D') {
        status = active == 2 ? "Blaze needs the potion and lit torch. Press E beside this coded wall."
                             : "Coded walls belong to Blaze. Switch to Blaze.";
        return;
    }
    if (t == '0') {
        if (active == 1) {
            // Sprinty's two-tile jump can clear a gap if the landing tile is free.
            int jr = r + dr, jc = c + dc;
            if (inBounds(jr, jc) && board[jr][jc] != '#' && board[jr][jc] != '0') {
                rememberMove(active); pr[active] = jr; pc[active] = jc;
                status = "Sprinty jumped over the gap!"; return;
            }
        }
        loseLife("Pit! You lost a life.");
        return;
    }
    if (t == 'B') {
        if (active != 0) { status = "Only Rocky can push boulders."; return; }
        int br = r + dr, bc = c + dc;
        if (!inBounds(br, bc) || board[br][bc] != '.') {
            status = "The boulder needs an empty tile behind it."; return;
        }
        rememberMove(active); board[br][bc] = 'B'; board[r][c] = '.';
    }
    if (t == 'O') {
        if (active != 1) { status = "This bomb belongs to Sprinty. Switch to Sprinty."; return; }
        pr[active] = r; pc[active] = c;
        loseLife("Sprinty stepped on a bomb! The bomb remains in place.");
        return;
    }
    if (t == 'S') {
        status = active == 1 ? "Press E beside this switch." : "This switch belongs to Sprinty. Switch to Sprinty.";
        return;
    }
    if (t == 'H') { hasHammer = true; board[r][c] = '.'; status = "Hammer collected! Rocky can smash cracked walls."; }
    if (t == 'K') {
        if (active == 3) hasSplashKey = true;
        else if (active == 0) hasRockyKey = true;
        board[r][c] = '.';
        status = active == 3 ? "Splash collected the key!" : "Key collected.";
    }
    if (t == 'P') { hasPotion = true; board[r][c] = '.'; status = "Potion collected! Find Blaze's torch."; }
    if (t == 'T') { status = active == 2 ? "Press E beside the torch to light it." : "The torch belongs to Blaze. Switch to Blaze."; return; }
    if (t == 'E') {
        if (active == 3 && !hasSplashKey) { status = "Splash needs the key before exiting."; return; }
        if (active == 2 && !torchLit) { status = "Blaze must light the torch before exiting."; return; }
        if (active == 1 && !switchOpened) { status = "Activate the correct switch before using Sprinty's exit."; return; }
        if (active == 0 && !hasRockyKey) { status = "Rocky needs to find the key before exiting."; return; }
        rememberMove(active);
        pr[active] = r;
        pc[active] = c;

        // Each hero's exit completes only that hero's puzzle.
        // Keep the game running and activate the next character.
        completed[active] = true;
        if (active == 0) {
            active = 1;
            status = "Rocky's puzzle complete! Switch to Sprinty and solve the next area.";
        } else if (active == 1) {
            active = 2;
            status = "Sprinty's puzzle complete! Switch to Blaze and solve the next area.";
        } else if (active == 2) {
            active = 3;
            status = "Blaze's puzzle complete! Switch to Splash for the final area.";
        } else {
            gameWon = true;
            status = "All four puzzles complete! Level 3 complete!";
        }
        return;
    }
    rememberMove(active); pr[active] = r; pc[active] = c;
}

void useAbility() {
    if (gameOver || gameWon) return;
    const int dr[5] = {0, -1, 1, 0, 0}, dc[5] = {0, 0, 0, -1, 1};
    for (int i = 0; i < 5; ++i) {
        int r = pr[active] + dr[i], c = pc[active] + dc[i];
        if (!inBounds(r, c)) continue;
        char t = board[r][c];
        if (active == 0 && t == 'X') {
            if (!hasHammer) { status = "Collect the hammer before smashing cracked walls."; return; }
            rememberMove(active);
            // Match level3.cpp exactly: only the cracked wall at
            // row 1, column 6 (zero-based [0][5]) hides Rocky's key.
            if (r == 0 && c == 5) {
                board[r][c] = 'K';
                status = "Rocky cracked the correct wall! A key is revealed. Move onto it to collect it.";
            } else {
                board[r][c] = '.';
                status = "Rocky cracked the wall. There was no key inside.";
            }
            return;
        }
        if (active == 1 && t == 'O') {
            status = "Bomb ahead! Stepping on it costs one life and removes it.";
            return;
        }
        if (active == 1 && t == 'S') {
            rememberMove(active);
            if (r == 3 && c == 8) { switchOpened = true; status = "Correct switch! Sprinty's exit is unlocked."; }
            else { status = "Wrong switch! Find the correct switch."; }
            board[r][c] = '.'; return;
        }
        if (active == 2 && t == 'T') {
            if (!hasPotion) { status = "Blaze needs the potion first."; return; }
            rememberMove(active); torchLit = true; status = "Blaze lit the torch!"; return;
        }
        if (active == 2 && t == 'D') {
            if (!hasPotion || !torchLit) { status = "Blaze needs the potion and lit torch to reveal the code."; return; }
            if (r == 6 && c == 8) { revealedCodes |= 1; status = "Coded wall reveals: 1"; }
            else if (r == 7 && c == 10) { revealedCodes |= 2; status = "Coded wall reveals: 2"; }
            else if (r == 8 && c == 11) { revealedCodes |= 4; status = "Coded wall reveals: 3"; }
            else status = "No code is assigned to this wall.";
            return;
        }
        if (active == 3 && (t == 'F' || t == '~')) {
            rememberMove(active); board[r][c] = '.'; status = "Splash cleared the water/fire obstacle!"; return;
        }
    }
    status = string(names[active]) + ": no matching obstacle adjacent. Move beside your task and press E.";
}

Color tileColor(char t) {
    switch (t) {
        case '#': return Color{45, 52, 66, 255};
        case 'B': return BROWN;
        case 'X': return Color{169, 104, 72, 255};
        case 'D': return PURPLE;
        case 'O': return ORANGE;
        case 'S': return GOLD;
        case 'E': return GREEN;
        case 'H': return Color{220, 183, 75, 255};
        case '0': return MAROON;
        case 'K': return SKYBLUE;
        case 'P': return PINK;
        case 'T': return RED;
        default: return Color{35, 43, 57, 255};
    }
}
Color heroColor(int p) {
    if (p == 0) return GOLD;
    if (p == 1) return ORANGE;
    if (p == 2) return RED;
    return SKYBLUE;
}
void drawButton(Rectangle r, const char* label, bool hover) {
    DrawRectangleRounded(r, 0.2f, 8, hover ? Color{67, 99, 139, 255} : Color{38, 52, 73, 255});
    DrawRectangleRoundedLines(r, 0.2f, 8, Color{126, 155, 188, 255});
    int w = MeasureText(label, 21);
    DrawText(label, (int)(r.x + (r.width - w) / 2), (int)(r.y + (r.height - 21) / 2), 21, RAYWHITE);
}

// Sticker-like heroes: rounded badge, shine, eyes, and a letter emblem.
void drawHeroSticker(int x, int y, int p, float scale) {
    float radius = 23 * scale;
    DrawCircle(x + 2, y + 4, radius + 3, Color{0, 0, 0, 90});
    DrawCircle(x, y, radius + 3, RAYWHITE);
    DrawCircle(x, y, radius, heroColor(p));
    DrawCircle(x - 7 * scale, y - 9 * scale, 5 * scale, Color{255,255,255,130});
    DrawCircle(x - 7 * scale, y - 2 * scale, 2.6f * scale, BLACK);
    DrawCircle(x + 7 * scale, y - 2 * scale, 2.6f * scale, BLACK);
    DrawLineEx({x - 6 * scale, y + 8 * scale}, {x + 6 * scale, y + 8 * scale}, 2 * scale, BLACK);
    DrawText(TextFormat("%c", symbols[p]), (int)(x - 7 * scale), (int)(y + 11 * scale), (int)(12 * scale), BLACK);
}
void drawMenu() {
    Vector2 m = GetMousePosition();
    BeginDrawing(); ClearBackground(Color{17, 22, 34, 255});
    DrawCircle(SCREEN_W - 90, 95, 60, Color{35, 49, 69, 255});
    DrawCircle(SCREEN_W - 90, 95, 48, Color{48, 66, 88, 255});
    DrawText("ELEMENTAL", 48, 54, 43, GOLD);
    DrawText("SQUAD", 48, 100, 43, RAYWHITE);
    DrawText("LEVEL 3  |  FOUR HEROES, ONE CONNECTED GRID", 51, 160, 18, SKYBLUE);
    DrawText("Choose the right hero. Collect items. Solve each area.", 51, 190, 17, LIGHTGRAY);
    drawHeroSticker(90, 260, 0, 0.9f); drawHeroSticker(175, 260, 1, 0.9f);
    drawHeroSticker(260, 260, 2, 0.9f); drawHeroSticker(345, 260, 3, 0.9f);
    Rectangle play = {SCREEN_W/2.0f-150, 335, 300, 52};
    Rectangle chars = {SCREEN_W/2.0f-150, 401, 300, 52};
    Rectangle info = {SCREEN_W/2.0f-150, 467, 300, 52};
    Rectangle quit = {SCREEN_W/2.0f-150, 533, 300, 52};
    drawButton(play, "PLAY LEVEL 3", CheckCollisionPointRec(m, play));
    drawButton(chars, "CHOOSE CHARACTER", CheckCollisionPointRec(m, chars));
    drawButton(info, "CONTROLS & SYMBOLS", CheckCollisionPointRec(m, info));
    drawButton(quit, "QUIT", CheckCollisionPointRec(m, quit));
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(m, play)) { menuOpen = false; selectionOpen = true; }
        if (CheckCollisionPointRec(m, chars)) { menuOpen = false; selectionOpen = true; }
        if (CheckCollisionPointRec(m, info)) { menuOpen = false; instructionsOpen = true; }
        if (CheckCollisionPointRec(m, quit)) { CloseWindow(); }
    }
    EndDrawing();
}
void drawSelection() {
    Vector2 m = GetMousePosition();
    Rectangle back = {SCREEN_W - 215.0f, SCREEN_H - 76.0f, 175, 42};
    BeginDrawing(); ClearBackground(Color{17, 22, 34, 255});
    DrawText("CHOOSE YOUR HERO", 35, 30, 32, GOLD);
    const char* desc[4] = {"Hammer + cracked walls + boulders", "Choose 1/2 tiles; jump over bombs and gaps", "Potion, torch and coded walls", "Collect the key; avoid pits"};
    for (int i = 0; i < 4; ++i) {
        int y = 105 + i * 112;
        drawHeroSticker(77, y + 25, i, 0.8f);
        DrawText(TextFormat("%d. %s", i + 1, names[i]), 125, y - 2, 22, RAYWHITE);
        DrawText(desc[i], 125, y + 30, 16, LIGHTGRAY);
        DrawText(i == active ? "SELECTED" : "Press number to select", 125, y + 55, 15, i == active ? GOLD : GRAY);
    }
    drawButton(back, "BACK TO MENU", CheckCollisionPointRec(m, back));
    DrawText("Press 1-4 to select, ENTER to play, ESC to return", 35, SCREEN_H - 49, 16, LIGHTGRAY);
    if (IsKeyPressed(KEY_ONE)) active = 0;
    if (IsKeyPressed(KEY_TWO)) active = 1;
    if (IsKeyPressed(KEY_THREE)) active = 2;
    if (IsKeyPressed(KEY_FOUR)) active = 3;
    if (IsKeyPressed(KEY_ENTER)) { selectionOpen = false; menuOpen = false; status = string(names[active]) + " selected. Switch anytime with 1-4."; }
    if (IsKeyPressed(KEY_ESCAPE) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(m, back))) {
        selectionOpen = false; menuOpen = true;
    }
    EndDrawing();
}
void drawInstructions() {
    BeginDrawing(); ClearBackground(Color{17, 22, 34, 255});
    DrawText("CONTROLS & TILE SYMBOLS", 35, 35, 30, GOLD);
    DrawText("WASD / arrows - Move     1-4 - Switch character", 45, 100, 19, RAYWHITE);
    DrawText("E - Use ability     U - Undo     R - Restart     ESC - Menu", 45, 136, 18, RAYWHITE);
    DrawText("# Wall    B Boulder    X Cracked wall (Rocky)", 45, 210, 18, LIGHTGRAY);
    DrawText("O Bomb (costs a life)    S Switch    D Coded wall (Blaze)", 45, 246, 18, LIGHTGRAY);
    DrawText("H Hammer    K Key    P Potion    T Torch    0 Pit    E Exit", 45, 282, 18, LIGHTGRAY);
    DrawText("F Fire / ~ Water are Splash obstacles when present.", 45, 330, 18, SKYBLUE);
    DrawText("Pits cost a life; at zero lives, the game ends.", 45, 368, 18, ORANGE);
    DrawText("Press ENTER or ESC to return to menu", 45, SCREEN_H - 45, 17, LIGHTGRAY);
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE)) { instructionsOpen = false; menuOpen = true; }
    EndDrawing();
}
void drawGame() {
    BeginDrawing(); ClearBackground(Color{17, 22, 34, 255});
    DrawText("ELEMENTAL SQUAD  |  LEVEL 3", 18, 9, 22, RAYWHITE);
    DrawText("Move WASD/arrows | Switch 1-4 | Ability E | Undo U | Restart R | Menu ESC", 18, 38, 14, LIGHTGRAY);
    DrawText(TextFormat("Active: %s (%c)   Lives: %d", names[active], symbols[active], lives), 18, 62, 17, GOLD);
    DrawText(TextFormat("Hammer %s | Rocky key %s | Splash key %s | Potion %s | Torch %s",
        hasHammer ? "yes" : "no", hasRockyKey ? "yes" : "no", hasSplashKey ? "yes" : "no",
        hasPotion ? "yes" : "no", torchLit ? "lit" : "unlit"), 18, 86, 13, LIGHTGRAY);
    int ox = 20, oy = TOP;
    for (int r = 0; r < ROWS; ++r) for (int c = 0; c < COLS; ++c) {
        int x = ox + c*TILE, y = oy + r*TILE;
        Rectangle box = {(float)x, (float)y, (float)TILE-2, (float)TILE-2};
        bool hiddenSplash = (r >= 5 && c <= 6 && !splashMapVisible && !completed[3]);
        DrawRectangleRec(box, hiddenSplash ? Color{22, 27, 39, 255} : tileColor(board[r][c]));
        DrawRectangleLinesEx(box, 1, Color{78, 91, 110, 255});
        char t = hiddenSplash ? '?' : board[r][c];
        const char* label = "";
        switch (t) {
            case 'X': label = "CW"; break; case 'D': label = "C#"; break;
            case 'O': label = "BO"; break; case 'S': label = "SW"; break;
            case '0': label = "0"; break; case '.': label = ""; break;
            default: { static char one[2]; one[0] = t; one[1] = '\0'; label = one; break; }
        }
        if (label[0]) DrawText(label, x + (strlen(label) > 1 ? 7 : 18), y + 15, strlen(label) > 1 ? 18 : 23, RAYWHITE);
        if (t == 'D' && r == 6 && c == 8 && (revealedCodes & 1)) DrawText("1", x + 21, y + 15, 23, YELLOW);
        if (t == 'D' && r == 7 && c == 10 && (revealedCodes & 2)) DrawText("2", x + 21, y + 15, 23, YELLOW);
        if (t == 'D' && r == 8 && c == 11 && (revealedCodes & 4)) DrawText("3", x + 21, y + 15, 23, YELLOW);
        for (int p = 0; p < 4; ++p) {
            // Hide heroes who have already completed their puzzle so they
            // do not appear inside the next character's area.
            if (!completed[p] && pr[p] == r && pc[p] == c) {
                drawHeroSticker(x + TILE/2 - 1, y + TILE/2 - 1, p, 0.52f);
                if (p == active) DrawCircleLines(x + TILE/2 - 1, y + TILE/2 - 1, 19, RAYWHITE);
            }
        }
    }
    if (!splashMapVisible && !completed[3]) {
        float elapsed = GetTime() - splashRevealStart;
        DrawText(TextFormat("Splash maze hidden: %.0f seconds", elapsed < 12.0f ? 12.0f - elapsed : 0.0f), 20, oy + ROWS*TILE + 5, 14, SKYBLUE);
    }
    DrawText(status.c_str(), 20, oy + ROWS*TILE + 24, 14, RAYWHITE);
    if (gameOver) DrawText("GAME OVER - press R to restart", 20, oy + ROWS*TILE + 28, 16, RED);
    if (gameWon) DrawText("LEVEL 3 COMPLETE!", 20, oy + ROWS*TILE + 28, 16, GREEN);
    EndDrawing();
}
}

int main() {
    InitWindow(SCREEN_W, SCREEN_H, "Elemental Squad - Level 3");
    SetTargetFPS(60);
    resetBoard();
    splashRevealStart = GetTime();
    while (!WindowShouldClose()) {
        if (!splashMapVisible && GetTime() - splashRevealStart >= 12.0f) {
            splashMapVisible = true;
            status = "Splash's maze is now revealed.";
        }
        if (menuOpen) { if (IsKeyPressed(KEY_ESCAPE)) break; drawMenu(); continue; }
        if (selectionOpen) { drawSelection(); continue; }
        if (instructionsOpen) { drawInstructions(); continue; }
        if (IsKeyPressed(KEY_ESCAPE)) { menuOpen = true; continue; }
        if (IsKeyPressed(KEY_R)) resetBoard();
        if (sprintyMovePending) {
            if (IsKeyPressed(KEY_ONE)) {
                sprintyMovePending = false;
                active = 1;
                movePlayer(sprintyDr, sprintyDc);
            } else if (IsKeyPressed(KEY_TWO)) {
                sprintyMovePending = false;
                active = 1;
                int oldR = pr[1], oldC = pc[1];
                int nr = oldR + 2 * sprintyDr, nc = oldC + 2 * sprintyDc;
                if (!inBounds(nr, nc)) status = "Sprinty cannot jump outside the grid.";
                else {
                    char landing = board[nr][nc];
                    if (landing == '#' || landing == 'X' || landing == 'D' || landing == 'B' || landing == 'S' || landing == 'T') {
                        status = "Sprinty cannot land on that tile.";
                    } else if (landing == 'O') {
                        pr[1] = nr; pc[1] = nc;
                        loseLife("Sprinty landed on a bomb! The bomb remains in place.");
                    } else if (landing == '0') {
                        pr[1] = nr; pc[1] = nc;
                        loseLife("Sprinty landed in a pit! The pit remains in place.");
                    } else if (landing == 'E' && !switchOpened) status = "Activate the correct switch before using Sprinty's exit.";
                    else {
                        rememberMove(1); pr[1] = nr; pc[1] = nc;
                        if (landing == 'E') { completed[1] = true; active = 2; status = "Sprinty's puzzle complete! Blaze is now active."; }
                        else status = "Sprinty jumped two tiles, skipping the middle tile.";
                    }
                }
            }
            drawGame();
            continue;
        }
        if (IsKeyPressed(KEY_ONE)) { active = 0; status = "Rocky selected."; }
        if (IsKeyPressed(KEY_TWO)) { active = 1; status = "Sprinty selected."; }
        if (IsKeyPressed(KEY_THREE)) { active = 2; status = "Blaze selected."; }
        if (IsKeyPressed(KEY_FOUR)) { active = 3; status = "Splash selected."; }
        if (IsKeyPressed(KEY_U)) {
            if (!undoMoves.empty()) {
                Move m = undoMoves.top(); undoMoves.pop();
                pr[m.who] = m.r; pc[m.who] = m.c; active = m.who;
                status = "Position undone. Collected items and tile effects remain.";
            } else status = "Nothing to undo.";
        }
        if (IsKeyPressed(KEY_E)) useAbility();
        int dr = 0, dc = 0;
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) dr = -1;
        else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) dr = 1;
        else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) dc = -1;
        else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) dc = 1;
        if (dr || dc) {
            if (active == 1) {
                sprintyMovePending = true;
                sprintyDr = dr; sprintyDc = dc;
                status = "Sprinty: choose 1 tile or 2 tiles (press 1 or 2).";
            } else movePlayer(dr, dc);
        }
        drawGame();
    }
    CloseWindow();
    return 0;
}
