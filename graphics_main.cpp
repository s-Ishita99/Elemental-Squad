// ============================================================================
//  ELEMENTAL SQUAD  -  graphics_main.cpp  (Raylib)
//  All three levels live in this one program now (no separate level3 exe).
//
//  Build (add the extra .cpp files shown):
//    g++ graphics_main.cpp Grid.cpp Character.cpp Rocky.cpp Sprinty.cpp Blaze.cpp Splash.cpp grid3.cpp
//        -o elemental_squad_graphics -lraylib   (plus the link flags you already use)
//
//  Keys everywhere: 1 Rocky, 2 Sprinty, 3 Blaze, 4 Splash, F11 full screen.
// ============================================================================
#include "raylib.h"
#include "Grid.h"
#include "grid3.h"
#include "Rocky.h"
#include "Sprinty.h"
#include "blaze.h"
#include "splash.h"
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <cstdio>

using namespace std;

// ---- Hero + tile art reused from your original graphics_main.cpp ----

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
//  CONSTANTS, PALETTE, HERO DATA
// ============================================================================
static const int VW = 1280, VH = 720;                 // virtual canvas (scaled to any window)
static const int ROWS = 10, COLS = 14, TILE = 50, GX = 30, GY = 96;

static const Color BG       = {14, 17, 40, 255};
static const Color PANEL    = {26, 31, 62, 255};
static const Color PANEL_HI = {38, 46, 88, 255};
static const Color TXT      = {240, 244, 252, 255};
static const Color MUTED    = {178, 188, 214, 255};
static const Color GOLDEN   = {250, 205, 115, 255};
static const Color ACCENT   = {110, 200, 255, 255};
static const Color GOOD     = {110, 225, 150, 255};
static const Color BAD      = {255, 120, 120, 255};
static const Color BORDER   = {70, 80, 120, 255};
static const Color BLUE_BT  = {44, 105, 153, 255};
static const Color PURP_BT  = {91, 63, 133, 255};
static const Color RED_BT   = {150, 63, 53, 255};

static const char* HERO_NAME[4] = {"Rocky", "Sprinty", "Blaze", "Splash"};
static const char* HERO_ROLE[4] = {"Strength", "Agility", "Fire", "Water"};
static const char* HERO_DESC[4] = {"Pushes heavy boulders and smashes cracked walls with the hammer.",
                                   "Leaps across gaps and jumps two tiles at once.",
                                   "Melts ice, collects potions, lights torches and reads coded walls.",
                                   "Crosses water and fire, and can reveal hidden maps."};
static const Color HERO_COL[4]  = {{181, 218, 164, 255}, {220, 205, 255, 255},
                                   {255, 180, 125, 255}, {160, 235, 218, 255}};
static const float HERO_SCALE[4] = {0.85f, 1.1f, 1.1f, 1.1f};
static const float HERO_YOFF[4]  = {0.0f, 4.5f, 4.5f, 4.5f};

static void (*drawHeroFn[4])(float, float, float) = {drawRocky, drawSprinty, drawBlaze, drawSplash};
static void drawHeroAt(int p, float cx, float cy, float m)
{
    drawHeroFn[p](cx, cy + HERO_YOFF[p] * m, HERO_SCALE[p] * m);
}

// ============================================================================
//  APP + LEVEL STATE
// ============================================================================
enum Screen { LOGIN, MENU, LEVEL_SELECT, HOW_TO_PLAY, HERO_SELECT, GAME, RESULT };

static int screen = LOGIN, curLevel = 1, hero = 0, heroPick = -1, pendingLevel = 1;
static bool showGuide = false, quitGame = false, resWin = false;
static int resLevel = 1;
static string msg;
static Vector2 gMouse = {0, 0};
static bool gClick = false;
static float tokX = 0, tokY = 0;          // smooth on-screen position of the party token (tiles)

// ---- Level 1 ----
static Grid g1;
static Rocky rocky;
static Sprinty sprinty;
static Blaze blaze;
static Splash splash;
static Character* roster[4];
static bool l1Key = false;
static int l1Moves = 0;

// ---- Level 2 ----
static const char* L2_INIT[10] = {
    "..#...########", "..#..#......##", ".####.F....P..", ".I.##.........", ".#..F###.V####",
    ".#.#F.WW.V#...", ".##...WW.V..#.", "..#.####..#.#.", "..#.#.....#.#.", ".##.#..T..##.E"};
static char l2Map[ROWS][COLS + 1];
static int l2R, l2C, l2Lives, l2FaceR, l2FaceC;
static bool l2Potion, l2Torch;

// ---- Level 3 ----
static const int L3_START_R[4] = {0, 2, 5, 8};
static const int L3_START_C[4] = {0, 7, 9, 6};
static Grid3 l3Grid;
static int l3Stage, l3R, l3C, l3Lives, l3FaceR, l3FaceC, l3RevealUses;
static bool l3Hammer, l3RockyKey, l3Switch, l3WrongSwitch, l3Potion, l3Torch, l3CodeSolved, l3SplashKey;
static bool l3Reveal, l3CodePad, l3Over, l3Won;
static bool l3Codes[3], l3Done[4];
static double l3RevealStart;
static string l3Input;
static vector<string> l3Inv;
struct MoveState { int stage, row, col; bool pushed; int fromR, fromC, toR, toC; };
static stack<MoveState> l3Undo;
static float flash = 0.0f;

// ============================================================================
//  FONTS + TEXT HELPERS
// ============================================================================
static Font fontReg, fontBold;

static bool tryFont(Font& f, const char* const* paths, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (!FileExists(paths[i])) continue;
        Font t = LoadFontEx(paths[i], 72, nullptr, 0);
        if (t.texture.id == 0) continue;
        SetTextureFilter(t.texture, TEXTURE_FILTER_BILINEAR);
        f = t;
        return true;
    }
    return false;
}

static void loadFonts()
{
    const char* reg[] = {"assets/DejaVuSans.ttf", "assets/font.ttf",
                         "/System/Library/Fonts/Supplemental/Arial.ttf", "/Library/Fonts/Arial.ttf",
                         "C:/Windows/Fonts/segoeui.ttf", "C:/Windows/Fonts/arial.ttf",
                         "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", "/usr/share/fonts/TTF/DejaVuSans.ttf"};
    const char* bold[] = {"assets/DejaVuSans-Bold.ttf", "assets/font-bold.ttf",
                          "/System/Library/Fonts/Supplemental/Arial Bold.ttf", "/Library/Fonts/Arial Bold.ttf",
                          "C:/Windows/Fonts/segoeuib.ttf", "C:/Windows/Fonts/arialbd.ttf",
                          "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf"};
    fontReg = GetFontDefault();
    if (!tryFont(fontReg, reg, 8)) fontReg = GetFontDefault();
    fontBold = fontReg;
    tryFont(fontBold, bold, 8);
}

static float sp(float sz) { return sz * 0.05f; }
static Vector2 meas(const char* s, float sz, bool b = false) { return MeasureTextEx(b ? fontBold : fontReg, s, sz, sp(sz)); }
static void txt(const char* s, float x, float y, float sz, Color c, bool b = false)
{
    Font f = b ? fontBold : fontReg;
    DrawTextEx(f, s, {x + 1.5f, y + 1.5f}, sz, sp(sz), {0, 0, 0, 110});   // soft shadow = easier to read
    DrawTextEx(f, s, {x, y}, sz, sp(sz), c);
}
static void ctr(const char* s, float cx, float y, float sz, Color c, bool b = false)
{
    txt(s, cx - meas(s, sz, b).x / 2, y, sz, c, b);
}
// word-wrapped text; returns number of lines drawn
static int wrapText(const string& s, float x, float y, float w, float sz, Color c, float lh, bool b = false)
{
    string line;
    int n = 0;
    size_t i = 0;
    while (i <= s.size())
    {
        size_t j = s.find(' ', i);
        if (j == string::npos) j = s.size();
        string word = s.substr(i, j - i);
        string t = line.empty() ? word : line + " " + word;
        if (!line.empty() && meas(t.c_str(), sz, b).x > w)
        {
            txt(line.c_str(), x, y + n * lh, sz, c, b);
            n++;
            line = word;
        }
        else line = t;
        i = j + 1;
    }
    if (!line.empty()) { txt(line.c_str(), x, y + n * lh, sz, c, b); n++; }
    return n;
}

static bool hover(Rectangle r) { return CheckCollisionPointRec(gMouse, r); }

// immediate-mode button: draws itself and returns true when clicked
static bool btn(Rectangle r, const char* label, Color fill, float sz, bool enabled = true)
{
    bool h = enabled && hover(r);
    Color f = !enabled ? Color{50, 54, 78, 255}
                       : (h ? Color{(unsigned char)(fill.r + 28), (unsigned char)(fill.g + 28), (unsigned char)(fill.b + 28), 255} : fill);
    DrawRectangleRounded({r.x, r.y + 3, r.width, r.height}, 0.2f, 8, {0, 0, 0, 90});
    DrawRectangleRounded(r, 0.2f, 8, f);
    DrawRectangleRoundedLinesEx(r, 0.2f, 8, h ? 3.0f : 2.0f, enabled ? GOLDEN : BORDER);
    ctr(label, r.x + r.width / 2, r.y + (r.height - sz) / 2 - 1, sz, enabled ? TXT : MUTED, true);
    return h && gClick;
}

static void panel(Rectangle r, Color fill = PANEL, Color edge = BORDER)
{
    DrawRectangleRounded(r, 0.04f, 8, fill);
    DrawRectangleRoundedLinesEx(r, 0.04f, 8, 1.5f, edge);
}

static void section(float x, float y, float w, const char* title)
{
    txt(title, x, y, 16, GOLDEN, true);
    DrawRectangleRec({x, y + 24, w, 2}, {70, 80, 120, 255});
}

static void heart(float cx, float cy, float s, bool full)
{
    Color c = full ? Color{236, 72, 96, 255} : Color{64, 68, 92, 255};
    DrawCircle((int)(cx - s * 0.5f), (int)(cy - s * 0.2f), s * 0.56f, c);
    DrawCircle((int)(cx + s * 0.5f), (int)(cy - s * 0.2f), s * 0.56f, c);
    DrawTriangle({cx - s * 1.03f, cy}, {cx, cy + s * 1.2f}, {cx + s * 1.03f, cy}, c);
}

// state: 0 pending, 1 current, 2 done
static void checkRow(float x, float y, const char* title, const string& sub, int state)
{
    float cx = x + 14, cy = y + 14;
    if (state == 2)
    {
        DrawCircle((int)cx, (int)cy, 13, {40, 160, 95, 255});
        DrawLineEx({cx - 6, cy}, {cx - 2, cy + 5}, 3, RAYWHITE);
        DrawLineEx({cx - 2, cy + 5}, {cx + 7, cy - 5}, 3, RAYWHITE);
    }
    else if (state == 1)
    {
        DrawCircle((int)cx, (int)cy, 13, Fade(GOLDEN, 0.25f));
        DrawCircleLines((int)cx, (int)cy, 13, GOLDEN);
        DrawCircle((int)cx, (int)cy, 5, GOLDEN);
    }
    else DrawCircleLines((int)cx, (int)cy, 13, {90, 100, 140, 255});
    Color tc = state == 2 ? GOOD : (state == 1 ? TXT : MUTED);
    txt(title, x + 38, y - 1, 19, tc, true);
    if (!sub.empty()) txt(sub.c_str(), x + 38, y + 22, 15, state == 2 ? GOOD : MUTED);
}

// ============================================================================
//  SMALL SHARED LOGIC
// ============================================================================
static bool inGrid(int r, int c) { return r >= 0 && r < ROWS && c >= 0 && c < COLS; }
static int quadOf(int r, int c) { return r < 5 ? (c < 7 ? 0 : 1) : (c < 7 ? 3 : 2); }
static string need(int h, const char* what)
{
    return string("Only ") + HERO_NAME[h] + " can " + what + ". Press " + to_string(h + 1) + " to switch to " + HERO_NAME[h] + ".";
}
static bool torchOn() { return curLevel == 2 ? l2Torch : l3Torch; }
static bool exitLockedAt(int r, int c)
{
    if (curLevel == 1) return !l1Key;
    if (curLevel == 2) return !l2Torch;
    int q = quadOf(r, c);
    if (l3Done[q]) return false;
    if (q == 0) return !l3RockyKey;
    if (q == 1) return !l3Switch;
    if (q == 2) return !l3CodeSolved;
    return !l3SplashKey;
}
static Color floorFor(int r, int c, bool legend)
{
    static const Color Q[4] = {{36, 31, 32, 255}, {27, 24, 48, 255}, {44, 28, 28, 255}, {18, 36, 46, 255}};
    if (legend || r < 0) return {24, 29, 56, 255};
    if (curLevel == 1) return {24, 30, 58, 255};
    if (curLevel == 2) return l2Torch ? Color{48, 38, 32, 255} : Color{22, 26, 44, 255};
    return Q[quadOf(r, c)];
}


// ============================================================================
//  TILE ART  (one function draws every tile of every level)
//  codes: . # CW C#  B H K P T E BO SW 0 GAP F W I V
// ============================================================================
static void drawTileArt(const string& t, int r, int c, float x, float y, float z, bool legend = false)
{
    float cx = x + z / 2, cy = y + z / 2, k = z / 40.0f;
    float tm = (float)GetTime();
    float bob = sinf(tm * 3.0f + x * 0.07f) * 1.5f;
    bool wall = (t == "#" || t == "CW" || t == "C#");
    bool potionTorch = !legend && curLevel == 3 && l3Potion && l3Torch;
    Color fl = floorFor(r, c, legend);

    if (!wall)
    {
        DrawRectangleRec({x, y, z, z}, fl);
        DrawRectangleLinesEx({x, y, z, z}, 1, BORDER);
    }

    if (t == "#") drawBrickWall((int)x, (int)y, (int)z);
    else if (t == "GAP") drawGap((int)x, (int)y, (int)z);
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
        if (!legend && idx >= 0 && l3Codes[idx])
        {
            DrawRectangleRec({x + 4, y + 4, z - 8, z - 8}, {30, 24, 50, 255});
            char d[2] = {(char)('1' + idx), 0};
            ctr(d, cx, cy - 16, 32, GOLDEN, true);
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
        DrawCircle((int)(cx - 8 * k), (int)(cy - 4 * k + bob), 2.5f * k, fl);
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
        bool lit = legend ? true : torchOn();
        float fy = y + z * 0.28f;
        DrawLineEx({cx, y + z * 0.86f}, {cx, y + z * 0.36f}, 4 * k, {121, 73, 43, 255});
        if (lit)
        {
            float f2 = sinf(tm * 12.0f + x) * 1.2f;
            DrawCircle((int)cx, (int)fy, 17 * k, Fade(ORANGE, 0.22f));
            DrawCircle((int)cx, (int)fy, (7 + f2) * k, {255, 171, 54, 255});
            DrawCircle((int)cx, (int)fy, 3.5f * k, {255, 237, 153, 255});
        }
        else DrawCircle((int)cx, (int)fy, 6.5f * k, {106, 67, 44, 255});
    }
    else if (t == "E")
    {
        bool locked = !legend && exitLockedAt(r, c);
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
        if (!legend && curLevel == 3)
        {
            if (r == 3 && c == 8 && l3Switch) st = 1;
            else if (r == 2 && c == 11 && l3WrongSwitch) st = 2;
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
    else if (t == "F")   // fire
    {
        float f2 = sinf(tm * 9.0f + x * 0.3f) * 2.0f;
        DrawEllipse((int)cx, (int)(cy + 6 * k), 11 * k, 12 * k, {200, 55, 35, 255});
        DrawPoly({cx, cy - 4 * k}, 3, (13 + f2) * k, -90, {225, 80, 40, 255});
        DrawEllipse((int)cx, (int)(cy + 8 * k), 7 * k, 8 * k, {255, 150, 55, 255});
        DrawPoly({cx, cy}, 3, (8 + f2 * 0.6f) * k, -90, {255, 170, 70, 255});
        DrawEllipse((int)cx, (int)(cy + 10 * k), 3.5f * k, 4.5f * k, {255, 235, 150, 255});
    }
    else if (t == "W")   // water
    {
        DrawRectangleRounded({x + 2, y + 2, z - 4, z - 4}, 0.2f, 6, {24, 104, 156, 255});
        for (int row = 0; row < 3; row++)
        {
            float by = y + z * (0.28f + 0.26f * row);
            for (int i = 0; i < 7; i++)
            {
                float x1 = x + 5 + i * (z - 10) / 7.0f, x2 = x + 5 + (i + 1) * (z - 10) / 7.0f;
                float y1 = by + sinf(tm * 2.0f + i + row) * 2.5f, y2 = by + sinf(tm * 2.0f + i + 1 + row) * 2.5f;
                DrawLineEx({x1, y1}, {x2, y2}, 2.0f, {140, 215, 245, 255});
            }
        }
    }
    else if (t == "I")   // ice
    {
        DrawRectangleRounded({x + 3, y + 3, z - 6, z - 6}, 0.22f, 6, {146, 216, 240, 255});
        DrawRectangleRoundedLinesEx({x + 3, y + 3, z - 6, z - 6}, 0.22f, 6, 2, {220, 245, 255, 255});
        DrawLineEx({x + 10 * k, y + 10 * k}, {x + 20 * k, y + 6 * k}, 2.5f, RAYWHITE);
        DrawLineEx({cx - 2 * k, cy + 2 * k}, {cx + 9 * k, cy - 6 * k}, 2.0f, {235, 250, 255, 255});
    }
    else if (t == "V")   // darkness gate
    {
        bool open = legend ? false : l2Torch;
        DrawRectangleRec({x + 2, y + 2, z - 4, z - 4}, open ? Color{70, 52, 36, 255} : Color{14, 12, 28, 255});
        for (int i = 0; i < 4; i++)
            DrawLineEx({x + 8 * k + i * 8 * k, y + 4 * k}, {x + 8 * k + i * 8 * k, y + z - 4 * k}, 2.5f,
                       open ? Color{150, 120, 70, 255} : Color{70, 60, 110, 255});
        if (!open) DrawRectangleLinesEx({x + 2, y + 2, z - 4, z - 4}, 2, {110, 90, 170, 255});
    }
}

// the party token (the hero you currently control)
static void drawToken(float tx, float ty, bool active)
{
    float cx = GX + tx * TILE + TILE / 2.0f - 1;
    float cy = GY + ty * TILE + TILE / 2.0f + 1;
    if (active) { cy += sinf((float)GetTime() * 4.0f) * 1.5f; DrawEllipseLines((int)cx, (int)(cy + 18), 16, 5, GOLDEN); }
    drawHeroAt(hero, cx, cy, 1.0f);
}


// ============================================================================
//  RESULT / FLOW HELPERS
// ============================================================================
static void showResult(bool win, int level) { resWin = win; resLevel = level; screen = RESULT; showGuide = false; }
static void goHeroSelect(int level) { pendingLevel = level; heroPick = -1; screen = HERO_SELECT; }

// ============================================================================
//  LEVEL 1  (Rocky pushes boulders, Sprinty crosses gaps)
// ============================================================================
static bool l1Extra(int r, int c) { return (r == 9 && c == 3) || (r == 8 && c == 7); }   // the two added walls
static int l1Tile(int r, int c) { return l1Extra(r, c) ? 1 : g1.getTile(r, c); }

static void startLevel1()
{
    g1 = Grid();
    rocky = Rocky(); sprinty = Sprinty(); blaze = Blaze(); splash = Splash();
    roster[0] = &rocky; roster[1] = &sprinty; roster[2] = &blaze; roster[3] = &splash;
    for (int i = 0; i < 4; i++) roster[i]->setPosition(0, 0);
    l1Key = false;
    l1Moves = 0;
    tokX = 0; tokY = 0;
    msg = "Collect the key, then reach the exit.";
}

static void l1Move(int dr, int dc)
{
    Character* cur = roster[hero];
    int nx = cur->getX() + dc, ny = cur->getY() + dr;
    int t = l1Tile(ny, nx);
    if (t == -1) { msg = "That is the edge of the map."; return; }
    if (t == 1)  { msg = "A wall blocks the way."; return; }
    if (t == 2)
    {
        if (hero != 0) { msg = need(0, "push boulders"); return; }
        int bt = l1Tile(ny + dr, nx + dc);
        if (bt == -1 || bt == 1 || bt == 2) { msg = "The boulder cannot be pushed that way."; return; }
        if (bt == 4 || bt == 5) { msg = "That would block the key or exit. Push the boulder another way."; return; }
    }
    if (t == 3 && hero != 1) { msg = need(1, "cross the gap"); return; }

    char d = dr < 0 ? 'w' : dr > 0 ? 's' : dc < 0 ? 'a' : 'd';
    if (!g1.moveCharacter(*cur, d)) { msg = "You cannot move there."; return; }
    for (int i = 0; i < 4; i++) roster[i]->setPosition(cur->getX(), cur->getY());
    l1Moves++;
    msg = t == 2 ? "Rocky pushed the boulder!" : t == 3 ? "Sprinty leapt across the gap!" : "";
    if (g1.collectKey(*cur)) { l1Key = true; msg = "Key collected! Now reach the exit."; }
    if (g1.reachedExit(*cur))
    {
        if (l1Key) showResult(true, 1);
        else msg = "The exit is locked. Find the key first.";
    }
}

static void l1Ability()
{
    msg = string(HERO_NAME[hero]) + ": " + HERO_DESC[hero];
}

// ============================================================================
//  LEVEL 2  (Blaze: ice / potion / torch.  Splash: water + fire)
// ============================================================================
static void startLevel2()
{
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c <= COLS; c++) l2Map[r][c] = L2_INIT[r][c];
    l2R = 0; l2C = 0; l2Lives = 3; l2FaceR = 0; l2FaceC = 1;
    l2Potion = false; l2Torch = false;
    tokX = 0; tokY = 0;
    msg = "Find the potion, then light the torch.";
}

static void l2Hurt(const string& what, const string& tip)
{
    l2Lives--;
    flash = 1.0f;
    if (l2Lives <= 0) { l2Lives = 0; msg = "No lives left!"; showResult(false, 2); return; }
    msg = what + " Lives left: " + to_string(l2Lives) + "." + tip;
}

static void l2Move(int dr, int dc)
{
    l2FaceR = dr; l2FaceC = dc;
    int nr = l2R + dr, nc = l2C + dc;
    if (!inGrid(nr, nc)) { msg = "The cave wall blocks your path."; return; }
    char t = l2Map[nr][nc];
    if (t == '#') { msg = "A wall blocks the way."; return; }
    if (t == 'V' && !l2Torch) { msg = "The gate is sealed by darkness. Blaze must light the torch first."; return; }
    if (t == 'F')
    {
        if (hero == 2) { l2Hurt("Blaze touched the fire!", " Switch to Splash (4)."); return; }
        if (hero != 3) { msg = "Fire blocks the way. Only Splash can pass it. Press 4 to switch."; return; }
    }
    if (t == 'W' && hero != 3)
    {
        msg = hero == 2 ? "Blaze cannot cross water. Press 4 to switch to Splash."
                        : "Water blocks the way. Only Splash can cross it. Press 4 to switch.";
        return;
    }
    if (t == 'I')
    {
        if (hero == 3) { l2Hurt("Splash slipped on the ice!", " Blaze (3) can melt it."); return; }
        if (hero != 2) { msg = "Ice blocks the way. Only Blaze can melt it. Press 3 to switch."; return; }
        l2Map[nr][nc] = '.';
        msg = "Blaze melted the ice.";
    }
    if (t == 'E' && !l2Torch) { msg = "The exit is locked. Light the torch first."; return; }

    l2R = nr; l2C = nc;
    if (l2Map[nr][nc] == 'P')
    {
        if (hero == 2) { l2Potion = true; l2Map[nr][nc] = '.'; msg = "Blaze collected the potion! Now find the torch."; }
        else msg = "A potion! Only Blaze can collect it. Press 3 to switch.";
    }
    if (l2Map[nr][nc] == 'E' && l2Torch) showResult(true, 2);
}

static void l2Interact()
{
    char t = l2Map[l2R][l2C];
    if (t == 'P')
    {
        if (hero == 2) { l2Potion = true; l2Map[l2R][l2C] = '.'; msg = "Blaze collected the potion!"; }
        else msg = need(2, "collect the potion");
    }
    else if (t == 'T')
    {
        if (hero != 2) msg = need(2, "light the torch");
        else if (!l2Potion) msg = "Collect the potion first.";
        else if (!l2Torch) { l2Torch = true; msg = "Torch lit! The cave is now visible."; }
        else msg = "The torch is already lit.";
    }
    else msg = "Nothing to interact with here.";
}

// ============================================================================
//  LEVEL 3  (four trials; any hero can be chosen, abilities decide what works)
// ============================================================================
static void startLevel3()
{
    l3Grid = Grid3();
    l3Stage = 0; l3Lives = 3; l3R = L3_START_R[0]; l3C = L3_START_C[0]; l3FaceR = 0; l3FaceC = 1;
    l3Hammer = l3RockyKey = l3Switch = l3WrongSwitch = l3Potion = l3Torch = l3CodeSolved = l3SplashKey = false;
    l3Reveal = l3CodePad = l3Over = l3Won = false;
    for (int i = 0; i < 3; i++) l3Codes[i] = false;
    for (int i = 0; i < 4; i++) l3Done[i] = false;
    l3RevealUses = 0; l3RevealStart = 0; l3Input.clear(); l3Inv.clear();
    l3Undo = stack<MoveState>();
    tokX = (float)l3C; tokY = (float)l3R;
    msg = "Find your way through all four puzzles. Use 1-4 to switch heroes.";
}

static bool l3Inside(int r, int c) { return inGrid(r, c) && quadOf(r, c) == l3Stage; }
static bool l3Wall(const string& t) { return t == "#" || t == "CW" || t == "C#"; }
static void l3AddItem(const string& s) { for (const string& i : l3Inv) if (i == s) return; l3Inv.push_back(s); }

static void l3Save(int os, int orow, int ocol, bool pushed = false, int fr = 0, int fc = 0, int tr = 0, int tc = 0)
{
    l3Undo.push({os, orow, ocol, pushed, fr, fc, tr, tc});
}
static void l3UndoMove()
{
    if (l3Undo.empty()) { msg = "No moves available to undo."; return; }
    MoveState p = l3Undo.top();
    l3Undo.pop();
    if (p.pushed) { l3Grid.tiles[p.fromR][p.fromC] = "B"; l3Grid.tiles[p.toR][p.toC] = "."; }
    l3Stage = p.stage; l3R = p.row; l3C = p.col;
    msg = "Undo successful! Previous position restored.";
}

static void l3Hurt(const string& reason)
{
    flash = 1.0f;
    l3Lives--;
    if (l3Lives <= 0) { l3Over = true; msg = "Game over! No lives remaining."; return; }
    msg = reason + " Lives remaining: " + to_string(l3Lives);
    l3R = L3_START_R[l3Stage];
    l3C = L3_START_C[l3Stage];
}

static void l3Activate(int r, int c)
{
    if (r == 3 && c == 8)       { l3Switch = true; msg = "Correct switch! The exit is now unlocked."; }
    else if (r == 2 && c == 11) { l3WrongSwitch = true; msg = "Wrong switch! The exit is still locked."; }
    else                        msg = "This switch does not open the exit.";
}

static void l3Collect(const string& tile, int r, int c)
{
    if (tile == "H")
    {
        if (hero != 0) { msg = need(0, "pick up the hammer"); return; }
        l3Hammer = true; l3AddItem("Hammer"); l3Grid.tiles[r][c] = ".";
        msg = "Rocky collected the hammer!";
    }
    else if (tile == "K")
    {
        if (l3Stage == 0)
        {
            if (hero != 0) { msg = need(0, "pick up this key"); return; }
            l3RockyKey = true; l3AddItem("Rocky key"); msg = "Rocky collected the key!";
        }
        else
        {
            if (hero != 3) { msg = need(3, "pick up this key"); return; }
            l3SplashKey = true; l3AddItem("Splash key"); msg = "Splash collected the key!";
        }
        l3Grid.tiles[r][c] = ".";
    }
    else if (tile == "P")
    {
        if (hero != 2) { msg = need(2, "collect the potion"); return; }
        l3Potion = true; l3AddItem("Potion"); l3Grid.tiles[r][c] = ".";
        msg = "Blaze collected the potion!";
    }
    else if (tile == "SW")
    {
        if (hero != 1) { msg = need(1, "press the switches"); return; }
        l3Activate(r, c);
    }
    else if (tile == "BO") { l3Grid.tiles[r][c] = "."; l3Hurt("You stepped on a bomb!"); }
    else if (tile == "0")  { l3Grid.tiles[r][c] = "."; l3Hurt("You fell into a pit! It collapsed."); }
}

static void l3Next()
{
    l3Done[l3Stage] = true;
    l3Undo = stack<MoveState>();
    if (l3Stage == 3) { l3Won = true; msg = "Congratulations! You completed Level 3!"; return; }
    l3Stage++;
    l3R = L3_START_R[l3Stage]; l3C = L3_START_C[l3Stage]; l3FaceR = 0; l3FaceC = 1;
    msg = "Trial complete! On to the next one.";
}

static void l3Exit()
{
    if (l3Stage == 0)      { if (l3RockyKey) l3Next(); else msg = "The exit is locked. Find the hidden key."; }
    else if (l3Stage == 1) { if (l3Switch) l3Next(); else msg = "The exit is locked. Activate the correct switch."; }
    else if (l3Stage == 2)
    {
        if (l3CodeSolved) l3Next();
        else if (!l3Potion || !l3Torch) msg = "Collect the potion and light the torch first.";
        else if (!(l3Codes[0] && l3Codes[1] && l3Codes[2])) msg = "Reveal all three wall codes first.";
        else { l3CodePad = true; l3Input.clear(); msg = "Enter the three-digit code."; }
    }
    else { if (l3SplashKey) l3Next(); else msg = "The exit is locked. Find Splash's key."; }
}

static void l3Interact()
{
    int tr = l3R + l3FaceR, tc = l3C + l3FaceC;
    string tile = inGrid(tr, tc) ? l3Grid.tiles[tr][tc] : "";
    if (tile == "E") { l3Exit(); return; }

    if (l3Stage == 3)   // Splash's hidden maze: reveal the map
    {
        if (hero != 3) { msg = need(3, "reveal the hidden map"); return; }
        if (l3RevealUses >= 2) { msg = "No map reveals remaining for Splash."; return; }
        l3Reveal = true; l3RevealUses++; l3RevealStart = GetTime();
        msg = "Map revealed for 5 seconds! Uses remaining: " + to_string(2 - l3RevealUses);
        return;
    }
    if (l3Stage == 2 && l3Grid.tiles[l3R][l3C] == "T")
    {
        if (hero != 2) { msg = need(2, "light the torch"); return; }
        if (!l3Potion) { msg = "Collect the potion before lighting the torch."; return; }
        if (!l3Torch) { l3Torch = true; msg = "Torch lit! You can now reveal the wall codes."; }
        else msg = "The torch is already lit.";
        return;
    }
    if (tile == "CW")
    {
        if (hero != 0) { msg = need(0, "smash cracked walls"); return; }
        if (!l3Hammer) { msg = "Rocky needs the hammer to crack this wall."; return; }
        if (tr == 0 && tc == 5) { l3Grid.tiles[tr][tc] = "K"; msg = "You cracked the wall! A key is revealed."; }
        else                    { l3Grid.tiles[tr][tc] = ".";  msg = "You cracked the wall."; }
    }
    else if (tile == "SW") { if (hero != 1) msg = need(1, "press the switches"); else l3Activate(tr, tc); }
    else if (tile == "T")
    {
        if (hero != 2) msg = need(2, "light the torch");
        else if (!l3Potion) msg = "Collect the potion before lighting the torch.";
        else if (!l3Torch) { l3Torch = true; msg = "Torch lit! You can now reveal the wall codes."; }
        else msg = "The torch is already lit.";
    }
    else if (tile == "C#")
    {
        if (hero != 2) { msg = need(2, "read the coded walls"); return; }
        if (!l3Potion || !l3Torch) { msg = "Collect the potion and light the torch first."; return; }
        if (tr == 6 && tc == 8)       { l3Codes[0] = true; msg = "First wall code revealed: 1"; }
        else if (tr == 7 && tc == 10) { l3Codes[1] = true; msg = "Second wall code revealed: 2"; }
        else if (tr == 8 && tc == 11) { l3Codes[2] = true; msg = "Third wall code revealed: 3"; }
        else msg = "This coded wall has no code.";
    }
    else msg = "Nothing to interact with here.";
}

static void l3Step(int dr, int dc)
{
    l3FaceR = dr; l3FaceC = dc;
    int oldR = l3R, oldC = l3C, oldStage = l3Stage, oldLives = l3Lives;
    int nr = l3R + dr, nc = l3C + dc;
    if (!l3Inside(nr, nc)) { msg = "You cannot leave this puzzle area."; return; }
    string tile = l3Grid.tiles[nr][nc];
    if (tile == "CW") { msg = "A cracked wall. Rocky can smash it with the hammer (face it and press E)."; return; }
    if (l3Wall(tile)) { msg = "A wall blocks the way."; return; }
    if (tile == "E")  { msg = "You are facing the exit. Press E to use it."; return; }

    bool pushed = false;
    int bR = 0, bC = 0;
    if (tile == "B")
    {
        if (hero != 0) { msg = need(0, "push boulders"); return; }
        int br = nr + dr, bc = nc + dc;
        if (!l3Inside(br, bc) || l3Grid.tiles[br][bc] != ".") { msg = "The boulder cannot be pushed further."; return; }
        l3Grid.tiles[br][bc] = "B"; l3Grid.tiles[nr][nc] = ".";
        pushed = true; bR = br; bC = bc;
    }
    l3R = nr; l3C = nc;
    l3Collect(tile, nr, nc);
    if (l3Lives == oldLives && l3R == nr && l3C == nc) l3Save(oldStage, oldR, oldC, pushed, nr, nc, bR, bC);
}

static void l3Jump(int dr, int dc)
{
    if (hero != 1) { msg = need(1, "jump two tiles"); return; }
    l3FaceR = dr; l3FaceC = dc;
    int oldR = l3R, oldC = l3C, oldStage = l3Stage, oldLives = l3Lives;
    int nr = l3R + 2 * dr, nc = l3C + 2 * dc;
    if (!l3Inside(nr, nc)) { msg = "Sprinty cannot jump outside this puzzle area."; return; }
    string tile = l3Grid.tiles[nr][nc];
    if (l3Wall(tile)) { msg = "Sprinty cannot land on a wall."; return; }
    if (tile == "E")  { msg = "Sprinty is facing the exit. Press E to use it."; return; }
    if (tile == "B")  { msg = "Sprinty cannot push boulders."; return; }
    l3R = nr; l3C = nc;
    l3Collect(tile, nr, nc);
    if (l3Lives == oldLives && l3R == nr && l3C == nc)
    {
        l3Save(oldStage, oldR, oldC);
        if (tile == ".") msg = "Sprinty jumped two tiles!";
    }
}

// ============================================================================
//  START / SWITCH
// ============================================================================
static void startLevel(int lv)
{
    curLevel = lv;
    hero = heroPick < 0 ? 0 : heroPick;
    flash = 0.0f;
    showGuide = true;                 // short guide first so the player knows the symbols
    if (lv == 1) startLevel1(); else if (lv == 2) startLevel2(); else startLevel3();
    screen = GAME;
}

static void switchHero(int h)
{
    if (h == hero) return;
    hero = h;
    msg = string("Switched to ") + HERO_NAME[h] + " - " + HERO_ROLE[h] + ".";
}


// ============================================================================
//  SHARED LEVEL UI
// ============================================================================
static void drawHeader(const char* title, const char* sub)
{
    txt(title, 30, 8, 36, GOLDEN, true);
    txt(sub, 32, 56, 17, MUTED);
    txt("F11: full screen", 1110, 26, 14, MUTED);
}

static void drawMsgBar(const char* hint)
{
    panel({30, 624, 700, 82});
    wrapText(msg, 46, 632, 668, 20, TXT, 25, true);
    txt(hint, 46, 684, 14, MUTED);
}

static void heroCards(float x0, float y0)
{
    for (int i = 0; i < 4; i++)
    {
        Rectangle r = {x0 + i * 118, y0, 105, 150};
        bool act = (i == hero), hov = hover(r);
        DrawRectangleRounded(r, 0.12f, 8, act ? PANEL_HI : (hov ? Color{30, 36, 72, 255} : Color{20, 24, 50, 255}));
        DrawRectangleRoundedLinesEx(r, 0.12f, 8, act ? 3.0f : 1.5f, act ? GOLDEN : BORDER);
        if (act) DrawRectangleRec({r.x + 8, r.y + 120, 89, 3}, HERO_COL[i]);
        drawHeroAt(i, r.x + r.width / 2, r.y + 64, 1.0f);
        ctr(HERO_NAME[i], r.x + r.width / 2, r.y + 98, 18, act ? HERO_COL[i] : TXT, true);
        ctr(HERO_ROLE[i], r.x + r.width / 2, r.y + 124, 14, MUTED);
        DrawCircle((int)(r.x + 15), (int)(r.y + 15), 11, act ? GOLDEN : Color{50, 58, 96, 255});
        char n[2] = {(char)('1' + i), 0};
        ctr(n, r.x + 15, r.y + 6, 15, act ? BG : TXT, true);
        if (hov && gClick) switchHero(i);
    }
}

static void hearts(float x, float y, int lives)
{
    txt("Lives", x, y + 4, 18, MUTED);
    for (int i = 0; i < 3; i++) heart(x + 100 + i * 44, y + 12, 13, i < lives);
}

static void tipLine(float x, float y, int h, const char* text)
{
    DrawCircle((int)x + 6, (int)y + 10, 6, HERO_COL[h]);
    txt(text, x + 20, y, 16, TXT);
}

static void sidePanelBase()
{
    panel({756, 64, 500, 642});
    section(776, 76, 460, "YOUR SQUAD");
    heroCards(776, 108);
}

// ============================================================================
//  LEVEL 1 SCREEN
// ============================================================================
static void drawLevel1()
{
    drawHeader("LEVEL 1: THE BEGINNING", "Collect the key, then reach the exit. Choose the right hero for each obstacle.");
    DrawRectangleRounded({GX - 8, GY - 8, COLS * TILE + 14, ROWS * TILE + 14}, 0.02f, 8, {10, 13, 32, 255});
    const float z = TILE - 2;
    static const char* code[6] = {".", "#", "B", "GAP", "K", "E"};
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
        {
            int t = l1Tile(r, c);
            drawTileArt(code[t < 0 || t > 5 ? 0 : t], r, c, (float)(GX + c * TILE), (float)(GY + r * TILE), z);
        }
    drawToken(tokX, tokY, true);

    sidePanelBase();
    section(776, 270, 460, "STATUS");
    txt("Moves", 776, 306, 18, MUTED);
    txt(to_string(l1Moves).c_str(), 860, 298, 30, TXT, true);
    drawTileArt("K", -1, -1, 1000, 296, 40, true);
    txt(l1Key ? "Key collected" : "Key not found", 1048, 306, 18, l1Key ? GOOD : GOLDEN, true);
    section(776, 356, 460, "OBJECTIVES");
    checkRow(776, 392, "Collect the golden key", "Hidden somewhere on the map", l1Key ? 2 : 1);
    checkRow(776, 438, "Reach the exit door", l1Key ? "The door is unlocked" : "Locked until you hold the key", l1Key ? 1 : 0);
    section(776, 540, 460, "HERO TIPS");
    tipLine(776, 574, 0, "Rocky pushes boulders");
    tipLine(776, 600, 1, "Sprinty leaps across gaps");
    tipLine(776, 626, 2, "Blaze: no special power here");
    tipLine(776, 652, 3, "Splash: no special power here");

    drawMsgBar("W A S D / arrows: move    1-4: switch hero    E: ability    R: restart    H: guide    ESC: menu");
}

// ============================================================================
//  LEVEL 2 SCREEN
// ============================================================================
static void drawLevel2()
{
    drawHeader("LEVEL 2: THE DARK CAVE", "Find the potion, light the torch, then escape through the cave.");
    DrawRectangleRounded({GX - 8, GY - 8, COLS * TILE + 14, ROWS * TILE + 14}, 0.02f, 8, {10, 13, 32, 255});
    const float z = TILE - 2;
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
        {
            char ch = l2Map[r][c];
            float x = (float)(GX + c * TILE), y = (float)(GY + r * TILE);
            string code(1, ch);
            drawTileArt(code, r, c, x, y, z);
            bool dark = (c >= 10 && r >= 4 && ch != 'V');   // cave interior hides until the torch is lit
            if (dark && !l2Torch)
            {
                DrawRectangleRec({x, y, z, z}, {6, 8, 20, 245});
                ctr("?", x + z / 2, y + z / 2 - 10, 20, Fade(ACCENT, 0.25f));
            }
        }
    int fr = l2R + l2FaceR, fc = l2C + l2FaceC;
    if (inGrid(fr, fc))
        DrawRectangleLinesEx({(float)(GX + fc * TILE), (float)(GY + fr * TILE), z, z}, 2, Fade(GOLDEN, 0.45f + 0.3f * sinf((float)GetTime() * 6.0f)));
    drawToken(tokX, tokY, true);

    sidePanelBase();
    section(776, 270, 460, "STATUS");
    hearts(776, 300, l2Lives);
    drawTileArt("P", -1, -1, 1000, 296, 40, true);
    txt(l2Potion ? "Potion: yes" : "Potion: no", 1044, 306, 18, l2Potion ? GOOD : MUTED, true);
    section(776, 356, 460, "OBJECTIVES");
    checkRow(776, 392, "Collect the potion", "Only Blaze can pick it up", l2Potion ? 2 : 1);
    checkRow(776, 438, "Light the torch", "Blaze lights it (press E on the torch)", l2Torch ? 2 : (l2Potion ? 1 : 0));
    checkRow(776, 484, "Reach the exit", l2Torch ? "The exit is unlocked" : "Locked until the torch is lit", l2Torch ? 1 : 0);
    section(776, 540, 460, "HERO TIPS");
    tipLine(776, 574, 2, "Blaze melts ice, lights the torch");
    tipLine(776, 600, 3, "Splash crosses water and fire");
    tipLine(776, 626, 0, "Rocky: no special power here");
    tipLine(776, 652, 1, "Sprinty: no special power here");

    drawMsgBar("W A S D / arrows: move    1-4: switch hero    E: interact    R: restart    H: guide    ESC: menu");
}

// ============================================================================
//  LEVEL 3 SCREEN
// ============================================================================
static const char* L3_TRIAL[4] = {"ROCKY'S TRIAL", "SPRINTY'S TRIAL", "BLAZE'S TRIAL", "SPLASH'S TRIAL"};

static void drawLevel3()
{
    drawHeader("LEVEL 3: THE FOUR TRIALS", "Solve the four areas clockwise. Pick the hero whose power the puzzle needs.");
    const float z = TILE - 2;
    bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
    bool fog = (l3Stage == 3 && !l3Reveal && !l3Won);
    float t = (float)GetTime();
    DrawRectangleRounded({GX - 8, GY - 8, COLS * TILE + 14, ROWS * TILE + 14}, 0.02f, 8, {10, 13, 32, 255});

    for (int q = 0; q < 4; q++)
    {
        float lx = (float)(GX + ((q == 0 || q == 3) ? 0 : 7) * TILE);
        float ly = (q < 2) ? (float)(GY - 26) : (float)(GY + ROWS * TILE + 2);
        string s = L3_TRIAL[q];
        if (l3Done[q]) s += "  - DONE";
        txt(s.c_str(), lx, ly, 15, l3Done[q] ? GOOD : (q == l3Stage ? GOLDEN : MUTED), true);
    }
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
        {
            float x = (float)(GX + c * TILE), y = (float)(GY + r * TILE);
            int q = quadOf(r, c);
            if (q == 3 && fog)
            {
                DrawRectangleRec({x, y, z, z}, {10, 14, 28, 255});
                DrawRectangleLinesEx({x, y, z, z}, 1, {26, 34, 58, 255});
                ctr("?", x + z / 2, y + z / 2 - 11, 22, Fade(ACCENT, 0.30f + 0.22f * sinf(t * 2.0f + r + c)));
            }
            else drawTileArt(l3Grid.tiles[r][c], r, c, x, y, z);
            if (q != l3Stage && !l3Done[q]) DrawRectangleRec({x, y, z, z}, {8, 10, 24, 140});
            if (l3Done[q]) DrawRectangleRec({x, y, z, z}, {40, 160, 90, 26});
        }
    for (int q = 0; q < 4; q++)
    {
        float x0 = (float)(GX + ((q == 0 || q == 3) ? 0 : 7) * TILE), y0 = (float)(GY + (q < 2 ? 0 : 5) * TILE);
        DrawRectangleLinesEx({x0 - 1, y0 - 1, 7.0f * TILE, 5.0f * TILE}, q == l3Stage ? 3.0f : 1.0f,
                             q == l3Stage ? GOLDEN : Color{80, 90, 125, 255});
    }
    int fr = l3R + l3FaceR, fc = l3C + l3FaceC;
    if (l3Inside(fr, fc))
        DrawRectangleLinesEx({(float)(GX + fc * TILE), (float)(GY + fr * TILE), z, z}, 2, Fade(GOLDEN, 0.45f + 0.3f * sinf(t * 6.0f)));
    if (hero == 1 && shift)   // Sprinty jump preview
    {
        const int dR[4] = {-1, 1, 0, 0}, dC[4] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++)
        {
            int lr = l3R + 2 * dR[i], lc = l3C + 2 * dC[i];
            if (!l3Inside(lr, lc)) continue;
            const string& lt = l3Grid.tiles[lr][lc];
            if (l3Wall(lt) || lt == "B" || lt == "E") continue;
            DrawRectangleLinesEx({(float)(GX + lc * TILE), (float)(GY + lr * TILE), z, z}, 3, Fade(ACCENT, 0.9f));
        }
    }
    drawToken(tokX, tokY, true);

    sidePanelBase();
    section(776, 270, 460, "STATUS");
    hearts(776, 300, l3Lives);
    int doneCount = 0;
    for (int i = 0; i < 4; i++) if (l3Done[i]) doneCount++;
    txt(TextFormat("Trials done: %d / 4", doneCount), 1010, 306, 18, GOLDEN, true);

    section(776, 346, 460, "THE FOUR TRIALS");
    char pb[4][96];
    snprintf(pb[0], 96, "Hammer: %s   Key: %s", l3Hammer ? "yes" : "no", l3RockyKey ? "yes" : "no");
    snprintf(pb[1], 96, "%s", l3Switch ? "Correct switch pressed" : "Find the correct switch");
    int codes = (int)l3Codes[0] + (int)l3Codes[1] + (int)l3Codes[2];
    snprintf(pb[2], 96, "Potion: %s  Torch: %s  Codes: %d/3", l3Potion ? "yes" : "no", l3Torch ? "lit" : "unlit", codes);
    snprintf(pb[3], 96, "Key: %s   Map reveals left: %d", l3SplashKey ? "yes" : "no", 2 - l3RevealUses);
    static const char* tn[4] = {"Rocky: hammer + boulders", "Sprinty: jump + switch", "Blaze: torch + code", "Splash: hidden maze"};
    for (int i = 0; i < 4; i++) checkRow(776, 382 + i * 50, tn[i], pb[i], l3Done[i] ? 2 : (i == l3Stage ? 1 : 0));

    section(776, 586, 460, "INVENTORY");
    for (int i = 0; i < 4; i++)
    {
        float x = 776.0f + i * 80;
        DrawRectangleRounded({x, 616, 54, 54}, 0.15f, 6, {18, 20, 48, 255});
        DrawRectangleRoundedLinesEx({x, 616, 54, 54}, 0.15f, 6, 1, BORDER);
        if (i < (int)l3Inv.size())
        {
            const string& it = l3Inv[i];
            drawTileArt(it == "Hammer" ? "H" : it == "Potion" ? "P" : "K", -1, -1, x + 3, 619, 48, true);
            ctr(it.c_str(), x + 27, 672, 12, MUTED);
        }
    }
    txt(TextFormat("Undo available: %d", (int)l3Undo.size()), 1110, 640, 14, MUTED);

    drawMsgBar(hero == 1 ? "W A S D: move   SHIFT + direction: jump 2   E: interact   U: undo   R: restart   H: guide"
                         : "W A S D: move   1-4: switch hero   E: interact   U: undo   R: restart   H: guide   ESC: menu");
    if (l3Reveal)
    {
        float left = 5.0f - (float)(GetTime() - l3RevealStart);
        if (left < 0) left = 0;
        DrawRectangleRec({46, 712, 668, 6}, {18, 20, 48, 255});
        DrawRectangleRec({46, 712, 668 * (left / 5.0f), 6}, ACCENT);
    }
}

static void drawCodePad()
{
    DrawRectangle(0, 0, VW, VH, {8, 10, 26, 190});
    panel({400, 230, 480, 270}, PANEL, GOLDEN);
    ctr("BLAZE'S EXIT: ENTER THE CODE", 640, 252, 26, GOLDEN, true);
    for (int i = 0; i < 3; i++)
    {
        float x = 640.0f - 116 + i * 84;
        DrawRectangleRounded({x, 306, 64, 82}, 0.15f, 6, {18, 20, 48, 255});
        DrawRectangleRoundedLinesEx({x, 306, 64, 82}, 0.15f, 6, 2, (int)l3Input.size() == i ? GOLDEN : BORDER);
        if (i < (int)l3Input.size()) { char d[2] = {l3Input[i], 0}; ctr(d, x + 32, 320, 50, TXT, true); }
    }
    ctr("Type the digits shown on the glowing coded walls", 640, 410, 17, TXT);
    ctr("ENTER: confirm     BACKSPACE: delete     ESC: cancel", 640, 442, 15, MUTED);
}

// ============================================================================
//  GUIDE OVERLAY (symbols drawn with the real tile art)
// ============================================================================
struct GuideItem { const char* code; const char* text; };

static void drawGuide()
{
    DrawRectangle(0, 0, VW, VH, {8, 10, 26, 215});
    panel({150, 50, 980, 620}, PANEL, GOLDEN);
    const char* names[3] = {"LEVEL 1 GUIDE", "LEVEL 2 GUIDE", "LEVEL 3 GUIDE"};
    ctr(names[curLevel - 1], 640, 66, 38, GOLDEN, true);
    ctr("Press H, ENTER or ESC to close", 640, 114, 16, MUTED);

    static const GuideItem g1i[] = {{"#", "Wall - blocks everyone"}, {"B", "Boulder - only Rocky can push it"},
                                    {"GAP", "Gap - only Sprinty can cross"}, {"K", "Key - collect it first"},
                                    {"E", "Exit - needs the key"}};
    static const GuideItem g2i[] = {{"#", "Wall - blocks everyone"}, {"F", "Fire - Splash passes, Blaze is hurt"},
                                    {"W", "Water - only Splash can cross"}, {"I", "Ice - Blaze melts it, Splash slips"},
                                    {"P", "Potion - Blaze collects it"}, {"T", "Torch - Blaze lights it (E)"},
                                    {"V", "Dark gate - opens when torch is lit"}, {"E", "Exit - needs the torch lit"}};
    static const GuideItem g3i[] = {{"#", "Wall"}, {"B", "Boulder - Rocky pushes"}, {"CW", "Cracked wall - Rocky + hammer"},
                                    {"H", "Hammer - Rocky picks up"}, {"K", "Key - Rocky / Splash"}, {"BO", "Bomb - lose a life"},
                                    {"SW", "Switch - Sprinty (one is right)"}, {"0", "Pit - lose a life"}, {"P", "Potion - Blaze"},
                                    {"T", "Torch - Blaze lights (E)"}, {"C#", "Coded wall - Blaze reads it"}, {"E", "Exit"}};
    const GuideItem* items = curLevel == 1 ? g1i : curLevel == 2 ? g2i : g3i;
    int n = curLevel == 1 ? 5 : curLevel == 2 ? 8 : 12;
    int perCol = (n + 1) / 2;
    for (int i = 0; i < n; i++)
    {
        float x = 190.0f + (i / perCol) * 470, y = 150.0f + (i % perCol) * 56;
        drawTileArt(items[i].code, -1, -1, x, y, 44, true);
        txt(items[i].text, x + 58, y + 11, 18, TXT);
    }
    DrawRectangleRec({190, 500, 900, 2}, {70, 80, 120, 255});
    txt("Switch heroes any time with keys 1-4. If the wrong hero tries something, nothing happens and you're told who to pick.", 190, 516, 16, TXT);
    txt("W A S D / arrows: move     E: interact     R: restart level     ESC: back to menu", 190, 546, 16, MUTED);
    if (curLevel == 3) txt("SHIFT + direction (Sprinty): jump two tiles     U: undo", 190, 574, 16, MUTED);
    if (btn({540, 606, 200, 46}, "GOT IT", BLUE_BT, 21)) showGuide = false;
}


// ============================================================================
//  MENU SCREENS
// ============================================================================
static string loginUser, loginPass;
static bool passActive = false;

static void drawLogin()
{
    ctr("ELEMENTAL", 640, 50, 76, GOLDEN, true);
    ctr("SQUAD", 640, 130, 70, ACCENT, true);
    panel({410, 250, 460, 380});
    ctr("PLAYER LOGIN", 640, 270, 28, TXT, true);
    Rectangle uf = {450, 340, 380, 52}, pf = {450, 430, 380, 52};
    txt("USERNAME", 452, 316, 16, MUTED, true);
    txt("PASSWORD", 452, 406, 16, MUTED, true);
    if (gClick) { if (hover(uf)) passActive = false; else if (hover(pf)) passActive = true; }
    DrawRectangleRounded(uf, 0.15f, 8, {18, 22, 50, 255});
    DrawRectangleRoundedLinesEx(uf, 0.15f, 8, 2, passActive ? BORDER : GOLDEN);
    DrawRectangleRounded(pf, 0.15f, 8, {18, 22, 50, 255});
    DrawRectangleRoundedLinesEx(pf, 0.15f, 8, 2, passActive ? GOLDEN : BORDER);
    if (loginUser.empty()) txt("Type your username...", uf.x + 16, uf.y + 14, 20, {120, 130, 160, 255});
    else txt(loginUser.c_str(), uf.x + 16, uf.y + 13, 22, TXT);
    if (loginPass.empty()) txt("Type your password...", pf.x + 16, pf.y + 14, 20, {120, 130, 160, 255});
    else txt(string(loginPass.size(), '*').c_str(), pf.x + 16, pf.y + 17, 22, TXT);
    if (btn({500, 520, 280, 60}, "CONTINUE", BLUE_BT, 24)) screen = MENU;
    ctr("Demo login - accounts are not saved yet.  TAB switches field, ENTER continues.", 640, 650, 16, MUTED);
}

static void drawMenu()
{
    ctr("ELEMENTAL", 640, 40, 92, GOLDEN, true);
    ctr("SQUAD", 640, 135, 84, ACCENT, true);
    ctr("FOUR ELEMENTS  -  ONE TEAM", 640, 240, 24, TXT, true);
    for (int i = 0; i < 4; i++)
    {
        float cx = 400.0f + i * 160;
        DrawRectangleRounded({cx - 62, 290, 124, 170}, 0.12f, 8, {22, 27, 58, 255});
        DrawRectangleRoundedLinesEx({cx - 62, 290, 124, 170}, 0.12f, 8, 1.5f, BORDER);
        drawHeroAt(i, cx, 365, 1.7f);
        ctr(HERO_NAME[i], cx, 424, 20, HERO_COL[i], true);
    }
    if (btn({490, 500, 300, 70}, "START GAME", BLUE_BT, 30)) screen = LEVEL_SELECT;
    if (btn({490, 590, 145, 54}, "HOW TO PLAY", PURP_BT, 17)) screen = HOW_TO_PLAY;
    if (btn({645, 590, 145, 54}, "QUIT", PURP_BT, 22)) quitGame = true;
    ctr("Choose your hero. Solve the puzzle. Save the squad.", 640, 668, 18, MUTED);
    txt("F11: full screen", 1110, 690, 14, MUTED);
}

static void drawLevelSelect()
{
    ctr("CHOOSE YOUR LEVEL", 640, 60, 52, GOLDEN, true);
    ctr("Every level brings a new challenge. You pick your hero before each one.", 640, 128, 20, TXT);
    static const char* title[3] = {"The Beginning", "The Dark Cave", "The Four Trials"};
    static const char* desc[3] = {"Find the key and reach the exit. Boulders and gaps block the way.",
                                  "Find the potion, light the torch and escape the cave. Fire, water and ice.",
                                  "Four connected puzzle areas, one for each hero. Solve them clockwise."};
    static const Color col[3] = {BLUE_BT, PURP_BT, RED_BT};
    for (int i = 0; i < 3; i++)
    {
        Rectangle r = {75.0f + i * 390, 190, 350, 400};
        bool h = hover(r);
        DrawRectangleRounded({r.x, r.y + 4, r.width, r.height}, 0.06f, 8, {0, 0, 0, 90});
        DrawRectangleRounded(r, 0.06f, 8, h ? PANEL_HI : PANEL);
        DrawRectangleRoundedLinesEx(r, 0.06f, 8, h ? 3.0f : 1.5f, h ? GOLDEN : BORDER);
        DrawRectangleRounded({r.x + 20, r.y + 20, 90, 34}, 0.4f, 8, col[i]);
        ctr(TextFormat("LEVEL %d", i + 1), r.x + 65, r.y + 26, 18, TXT, true);
        txt(title[i], r.x + 22, r.y + 74, 30, GOLDEN, true);
        wrapText(desc[i], r.x + 22, r.y + 130, r.width - 44, 19, TXT, 26);
        DrawRectangleRec({r.x + 22, r.y + 290, r.width - 44, 2}, {70, 80, 120, 255});
        for (int k = 0; k < 4; k++) drawHeroAt(k, r.x + 62 + k * 75, r.y + 340, 0.9f);
        if (h && gClick) goHeroSelect(i + 1);
    }
    ctr("Click a level (or press 1, 2 or 3)", 640, 620, 18, MUTED);
    if (btn({30, 30, 130, 46}, "< BACK", PURP_BT, 19)) screen = MENU;
}

static void drawHowTo()
{
    ctr("HOW TO PLAY", 640, 40, 52, GOLDEN, true);
    panel({90, 120, 520, 520});
    txt("CONTROLS", 120, 140, 24, ACCENT, true);
    static const char* keys[8] = {"W A S D / arrows", "1  2  3  4", "E", "SHIFT + direction", "U", "R", "H", "F11"};
    static const char* what[8] = {"Move", "Switch hero", "Interact / use ability", "Sprinty jumps 2 tiles (Level 3)",
                                  "Undo last move (Level 3)", "Restart the level", "Show the symbol guide", "Toggle full screen"};
    for (int i = 0; i < 8; i++)
    {
        txt(keys[i], 120, 190 + i * 52, 20, GOLDEN, true);
        txt(what[i], 330, 190 + i * 52, 19, TXT);
    }
    panel({650, 120, 540, 520});
    txt("THE SQUAD", 680, 140, 24, ACCENT, true);
    for (int i = 0; i < 4; i++)
    {
        float y = 190.0f + i * 110;
        drawHeroAt(i, 725, y + 40, 1.2f);
        txt(HERO_NAME[i], 780, y + 2, 24, HERO_COL[i], true);
        wrapText(HERO_DESC[i], 780, y + 36, 380, 17, TXT, 22);
    }
    ctr("You choose a hero before every level and can switch any time. If the wrong hero tries something, it simply won't work.", 640, 656, 16, MUTED);
    if (btn({30, 30, 130, 46}, "< BACK", PURP_BT, 19)) screen = MENU;
}

static void drawHeroSelect()
{
    static const char* lvName[3] = {"LEVEL 1 - THE BEGINNING", "LEVEL 2 - THE DARK CAVE", "LEVEL 3 - THE FOUR TRIALS"};
    ctr("CHOOSE YOUR HERO", 640, 40, 52, GOLDEN, true);
    ctr(lvName[pendingLevel - 1], 640, 106, 24, ACCENT, true);
    ctr("Any hero is allowed. You can switch to another one at any time with keys 1-4.", 640, 146, 18, TXT);
    for (int i = 0; i < 4; i++)
    {
        Rectangle r = {95.0f + i * 280, 190, 250, 390};
        bool sel = (heroPick == i), h = hover(r);
        DrawRectangleRounded({r.x, r.y + 4, r.width, r.height}, 0.06f, 8, {0, 0, 0, 90});
        DrawRectangleRounded(r, 0.06f, 8, sel ? PANEL_HI : (h ? Color{32, 38, 76, 255} : PANEL));
        DrawRectangleRoundedLinesEx(r, 0.06f, 8, sel ? 4.0f : (h ? 2.5f : 1.5f), sel ? GOLDEN : (h ? HERO_COL[i] : BORDER));
        DrawCircle((int)(r.x + 28), (int)(r.y + 28), 16, sel ? GOLDEN : Color{50, 58, 96, 255});
        ctr(TextFormat("%d", i + 1), r.x + 28, r.y + 16, 22, sel ? BG : TXT, true);
        drawHeroAt(i, r.x + r.width / 2, r.y + 130, 2.3f);
        ctr(HERO_NAME[i], r.x + r.width / 2, r.y + 218, 32, HERO_COL[i], true);
        ctr(HERO_ROLE[i], r.x + r.width / 2, r.y + 258, 18, MUTED, true);
        wrapText(HERO_DESC[i], r.x + 22, r.y + 292, r.width - 44, 16, TXT, 21);
        if (sel) ctr("SELECTED", r.x + r.width / 2, r.y + 358, 16, GOLDEN, true);
        if (h && gClick) heroPick = i;
    }
    if (heroPick < 0) ctr("Pick a hero to begin.", 640, 598, 18, MUTED);
    else ctr(TextFormat("%s will start. Press ENTER or click START.", HERO_NAME[heroPick]), 640, 598, 18, TXT);
    if (btn({490, 630, 300, 62}, "START LEVEL", BLUE_BT, 26, heroPick >= 0)) startLevel(pendingLevel);
    if (btn({30, 30, 130, 46}, "< BACK", PURP_BT, 19)) screen = LEVEL_SELECT;
}

static void drawResult()
{
    DrawRectangle(0, 0, VW, VH, {8, 10, 26, 255});
    panel({240, 120, 800, 470}, PANEL, GOLDEN);
    if (resWin)
    {
        ctr(resLevel == 3 ? "THE SQUAD SAVED THE DAY!" : TextFormat("LEVEL %d COMPLETE!", resLevel), 640, 150, 50, GOLDEN, true);
        ctr(resLevel == 3 ? "All four trials solved. You finished Elemental Squad!" : "Great teamwork. Ready for the next challenge?", 640, 224, 22, GOOD, true);
        if (resLevel == 1) ctr(TextFormat("Total moves: %d", l1Moves), 640, 270, 20, TXT);
    }
    else
    {
        ctr("GAME OVER", 640, 150, 56, BAD, true);
        ctr("The squad ran out of lives. Try again!", 640, 224, 22, TXT, true);
    }
    for (int i = 0; i < 4; i++) drawHeroAt(i, 420 + i * 147, 380, 1.7f);
    if (btn({290, 480, 220, 62}, "PLAY AGAIN", BLUE_BT, 21)) goHeroSelect(resLevel);
    if (btn({530, 480, 220, 62}, "LEVEL SELECT", PURP_BT, 21)) screen = LEVEL_SELECT;
    if (resWin && resLevel < 3) { if (btn({770, 480, 220, 62}, "NEXT LEVEL", RED_BT, 21)) goHeroSelect(resLevel + 1); }
    else if (resWin) { if (btn({770, 480, 220, 62}, "MAIN MENU", RED_BT, 21)) screen = MENU; }
    else { if (btn({770, 480, 220, 62}, "MAIN MENU", RED_BT, 21)) screen = MENU; }
}

static void drawGameScreen()
{
    bool saved = gClick;
    if (showGuide || (curLevel == 3 && l3CodePad)) gClick = false;     // overlays block clicks underneath
    if (curLevel == 1) drawLevel1(); else if (curLevel == 2) drawLevel2(); else drawLevel3();
    gClick = saved;
    if (flash > 0) DrawRectangle(0, 0, VW, VH, Fade(RED, flash * 0.3f));
    if (curLevel == 3 && l3CodePad) drawCodePad();
    if (showGuide) drawGuide();
}


// ============================================================================
//  INPUT
// ============================================================================
static bool numKey(int n)   // n = 0..3  ->  keys 1..4
{
    int k = KEY_ONE + n, kp = KEY_KP_1 + n;
    return IsKeyPressed(k) || IsKeyPressed(kp);
}

static void handleLogin()
{
    int ch = GetCharPressed();
    while (ch > 0)
    {
        if (ch >= 32 && ch <= 125)
        {
            if (passActive) { if (loginPass.size() < 24) loginPass += (char)ch; }
            else if (loginUser.size() < 24) loginUser += (char)ch;
        }
        ch = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (passActive && !loginPass.empty()) loginPass.pop_back();
        else if (!passActive && !loginUser.empty()) loginUser.pop_back();
    }
    if (IsKeyPressed(KEY_TAB)) passActive = !passActive;
    if (IsKeyPressed(KEY_ENTER)) screen = MENU;
}

static void handleCodePad()
{
    int ch = GetCharPressed();
    while (ch > 0)
    {
        if (ch >= '0' && ch <= '9' && l3Input.size() < 3) l3Input += (char)ch;
        ch = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && !l3Input.empty()) l3Input.pop_back();
    if (IsKeyPressed(KEY_ESCAPE)) { l3CodePad = false; l3Input.clear(); msg = "Code entry cancelled."; }
    else if (IsKeyPressed(KEY_ENTER))
    {
        if (l3Input.size() < 3) msg = "Type all three digits first.";
        else
        {
            if (l3Input == "123") { l3CodeSolved = true; msg = "Correct code! Face the exit and press E."; }
            else msg = "Incorrect code. Try again at the exit.";
            l3CodePad = false;
            l3Input.clear();
        }
    }
}

static void handleGame()
{
    if (showGuide)
    {
        if (IsKeyPressed(KEY_H) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_SPACE)) showGuide = false;
        return;
    }
    if (curLevel == 3 && l3CodePad) { handleCodePad(); return; }
    if (IsKeyPressed(KEY_ESCAPE)) { screen = LEVEL_SELECT; return; }
    if (IsKeyPressed(KEY_H)) { showGuide = true; return; }
    if (IsKeyPressed(KEY_R)) { heroPick = hero; startLevel(curLevel); showGuide = false; msg = "Level restarted."; return; }
    for (int i = 0; i < 4; i++) if (numKey(i)) switchHero(i);

    int dr = 0, dc = 0;
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) dr = -1;
    else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) dr = 1;
    else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) dc = -1;
    else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) dc = 1;
    if (dr != 0 || dc != 0)
    {
        if (curLevel == 1) l1Move(dr, dc);
        else if (curLevel == 2) l2Move(dr, dc);
        else if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) l3Jump(dr, dc);
        else l3Step(dr, dc);
    }
    if (IsKeyPressed(KEY_E))
    {
        if (curLevel == 1) l1Ability(); else if (curLevel == 2) l2Interact(); else l3Interact();
    }
    if (curLevel == 3 && IsKeyPressed(KEY_U)) l3UndoMove();
}

static void update(float dt)
{
    if (flash > 0) flash -= dt * 1.6f;
    if (screen == LOGIN) handleLogin();
    else if (screen == LEVEL_SELECT)
    {
        if (IsKeyPressed(KEY_ESCAPE)) screen = MENU;
        for (int i = 0; i < 3; i++) if (numKey(i)) goHeroSelect(i + 1);
    }
    else if (screen == HOW_TO_PLAY) { if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER)) screen = MENU; }
    else if (screen == HERO_SELECT)
    {
        for (int i = 0; i < 4; i++) if (numKey(i)) heroPick = i;
        if (IsKeyPressed(KEY_ENTER) && heroPick >= 0) startLevel(pendingLevel);
        if (IsKeyPressed(KEY_ESCAPE)) screen = LEVEL_SELECT;
    }
    else if (screen == RESULT) { if (IsKeyPressed(KEY_ESCAPE)) screen = LEVEL_SELECT; }
    else if (screen == GAME)
    {
        handleGame();
        if (curLevel == 3 && l3Stage == 3 && l3Reveal && GetTime() - l3RevealStart >= 5.0)
        {
            l3Reveal = false;
            msg = "Time is up! Splash's map is hidden again.";
        }
        if (screen == GAME && curLevel == 3)
        {
            if (l3Won) showResult(true, 3);
            else if (l3Over) showResult(false, 3);
        }
        // glide the token toward its tile
        float tx = 0, ty = 0;
        if (curLevel == 1) { tx = (float)roster[hero]->getX(); ty = (float)roster[hero]->getY(); }
        else if (curLevel == 2) { tx = (float)l2C; ty = (float)l2R; }
        else { tx = (float)l3C; ty = (float)l3R; }
        float f = 16.0f * dt;
        if (f > 1.0f) f = 1.0f;
        tokX += (tx - tokX) * f;
        tokY += (ty - tokY) * f;
    }
}

// ============================================================================
//  MAIN  (virtual 1280x720 canvas scaled to ANY window size / full screen)
// ============================================================================
int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(VW, VH, "Elemental Squad");
    SetExitKey(KEY_NULL);                 // ESC = go back, not "close the program"
    SetWindowMinSize(640, 360);
    SetTargetFPS(60);
    loadFonts();
    ToggleBorderlessWindowed();           // start full screen (F11 switches back)
    startLevel1();

    while (!WindowShouldClose() && !quitGame)
    {
        // scale + centre the virtual canvas inside whatever size the window is
        int sw = GetScreenWidth(), sh = GetScreenHeight();
        float sc = fminf(sw / (float)VW, sh / (float)VH);
        float ox = (sw - VW * sc) / 2.0f, oy = (sh - VH * sc) / 2.0f;
        Camera2D cam = {{ox, oy}, {0, 0}, 0.0f, sc};
        SetMouseOffset((int)-ox, (int)-oy);
        SetMouseScale(1.0f / sc, 1.0f / sc);
        gMouse = GetMousePosition();
        gClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (IsKeyPressed(KEY_F11)) ToggleBorderlessWindowed();
        update(GetFrameTime());

        BeginDrawing();
        ClearBackground(BG);
        BeginMode2D(cam);
        if (screen == LOGIN) drawLogin();
        else if (screen == MENU) drawMenu();
        else if (screen == LEVEL_SELECT) drawLevelSelect();
        else if (screen == HOW_TO_PLAY) drawHowTo();
        else if (screen == HERO_SELECT) drawHeroSelect();
        else if (screen == GAME) drawGameScreen();
        else drawResult();
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
