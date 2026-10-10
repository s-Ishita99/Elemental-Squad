#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <sys/select.h>
#include <unistd.h>
#include <cctype>
#include <sstream>

#include "level3.h"
#include "grid3.h"

using namespace std;
using namespace chrono;

class Level3
{
private:
    static const int ROWS = 10;
    static const int COLS = 14;

    Grid3 grid;

    int row, col;
    int stage;
    int lives;

    int playerRows[4];
    int playerCols[4];

    int faceRow, faceCol;

    bool hasHammer;
    bool hasRockyKey;
    bool switchOpened;

    bool hasPotion;
    bool torchLit;
    bool codeRevealed[3];
    bool codeSolved;
    string codeSequence;
    bool codeInputMode;

    bool hasSplashKey;
    bool gridRevealed;
    int revealUses;
    steady_clock::time_point revealStart;

    bool gameOver;
    bool gameWon;

    string message;

    void initialize()
    {
        stage = 0;
        lives = 3;

        playerRows[0] = 0;
        playerCols[0] = 0;

        playerRows[1] = 2;
        playerCols[1] = 7;

        playerRows[2] = 5;
        playerCols[2] = 9;

        playerRows[3] = 8;
        playerCols[3] = 6;

        row = playerRows[0];
        col = playerCols[0];

        faceRow = 0;
        faceCol = 1;

        hasHammer = false;
        hasRockyKey = false;
        switchOpened = false;

        hasPotion = false;
        torchLit = false;

        for (int i = 0; i < 3; i++)
            codeRevealed[i] = false;

        codeSolved = false;
        codeSequence = "123";
        codeInputMode = false;

        hasSplashKey = false;
        gridRevealed = false;
        revealUses = 0;

        gameOver = false;
        gameWon = false;

        message = "Find your way through all four puzzles.";
    }

    bool insideCurrentArea(int r, int c)
    {
        if (stage == 0)
            return r >= 0 && r <= 4 && c >= 0 && c <= 6;

        if (stage == 1)
            return r >= 0 && r <= 4 && c >= 7 && c <= 13;

        if (stage == 2)
            return r >= 5 && r <= 9 && c >= 7 && c <= 13;

        return r >= 5 && r <= 9 && c >= 0 && c <= 6;
    }

    bool isWall(const string& tile)
    {
        return tile == "#" ||
               tile == "CW" ||
               tile == "C#";
    }

    void updatePosition()
    {
        playerRows[stage] = row;
        playerCols[stage] = col;
    }

    void loseLife(const string& reason)
    {
        lives--;

        if (lives <= 0)
        {
            gameOver = true;
            message = "Game over! You have no lives remaining.";
            return;
        }

        message = reason + " Lives remaining: " + to_string(lives);

        if (stage == 0)
        {
            row = 0;
            col = 0;
        }
        else if (stage == 1)
        {
            row = 2;
            col = 7;
        }
        else if (stage == 2)
        {
            row = 5;
            col = 9;
        }
        else
        {
            row = 8;
            col = 6;
        }

        updatePosition();
    }

    void activateSwitch(int r, int c)
    {
        if (r == 3 && c == 8)
        {
            switchOpened = true;
            message = "Right switch! The exit is now unlocked.";
        }
        else if (r == 2 && c == 11)
        {
            message = "Wrong switch! The exit is still locked.";
        }
        else
        {
            message = "This switch does not open the exit.";
        }
    }

    void collectItem(const string& tile, int r, int c)
    {
        if (tile == "H")
        {
            hasHammer = true;
            grid.tiles[r][c] = ".";
            message = "You collected the hammer!";
        }
        else if (tile == "K")
        {
            if (stage == 0)
            {
                hasRockyKey = true;
                message = "You collected Rocky's key!";
            }
            else if (stage == 3)
            {
                hasSplashKey = true;
                message = "You collected Splash's key!";
            }

            grid.tiles[r][c] = ".";
        }
        else if (tile == "P")
        {
            hasPotion = true;
            grid.tiles[r][c] = ".";
            message = "You collected the potion!";
        }
        else if (tile == "SW")
        {
            activateSwitch(r, c);
        }
        else if (tile == "BO")
        {
            grid.tiles[r][c] = ".";
            loseLife("You stepped on a bomb!");
        }
        else if (tile == "0")
        {
            grid.tiles[r][c] = ".";
            loseLife("You fell into a pit! The pit collapsed.");
        }

        updatePosition();
    }

    void nextPuzzle()
    {
        updatePosition();

        if (stage == 0)
        {
            stage = 1;
            message = "Rocky's puzzle is complete. Continue to the next trial.";
        }
        else if (stage == 1)
        {
            stage = 2;
            message = "Sprinty's puzzle is complete. Continue to the next trial.";
        }
        else if (stage == 2)
        {
            stage = 3;
            message = "Blaze's puzzle is complete. Continue to the final trial.";
        }
        else
        {
            gameWon = true;
            message = "Congratulations! You completed Level 3!";
            return;
        }

        row = playerRows[stage];
        col = playerCols[stage];

        faceRow = 0;
        faceCol = 1;
    }

    bool allCodesRevealed()
    {
        return codeRevealed[0] &&
               codeRevealed[1] &&
               codeRevealed[2];
    }

    void revealCodeAt(int r, int c)
    {
        if (!hasPotion || !torchLit)
        {
            message = "Collect the potion and light the torch first.";
            return;
        }

        if (r == 6 && c == 8)
        {
            codeRevealed[0] = true;
            message = "First wall code revealed: 1";
        }
        else if (r == 7 && c == 10)
        {
            codeRevealed[1] = true;
            message = "Second wall code revealed: 2";
        }
        else if (r == 8 && c == 11)
        {
            codeRevealed[2] = true;
            message = "Third wall code revealed: 3";
        }
        else
        {
            message = "This coded wall has no code assigned.";
        }
    }

    void interactWithExit()
    {
        if (stage == 0)
        {
            if (hasRockyKey)
                nextPuzzle();
            else
                message = "The exit is locked. Find the hidden key.";
        }
        else if (stage == 1)
        {
            if (switchOpened)
                nextPuzzle();
            else
                message = "The exit is locked. Activate the correct switch.";
        }
        else if (stage == 2)
        {
            if (codeSolved)
            {
                nextPuzzle();
            }
            else if (!hasPotion || !torchLit)
            {
                message = "Collect the potion and light the torch first.";
            }
            else if (!allCodesRevealed())
            {
                message = "Reveal all three wall codes first.";
            }
            else
            {
                codeInputMode = true;
                message = "Enter the three-digit code and press Enter.";
            }
        }
        else
        {
            if (hasSplashKey)
                nextPuzzle();
            else
                message = "The exit is locked. Find Splash's key.";
        }
    }

    void interact()
    {
        if (stage == 3)
        {
            int tr = row + faceRow;
            int tc = col + faceCol;

            if (tr >= 0 && tr < ROWS &&
                tc >= 0 && tc < COLS &&
                grid.tiles[tr][tc] == "E")
            {
                interactWithExit();
                return;
            }

            if (revealUses >= 2)
            {
                message = "No map reveals remaining for Splash.";
                return;
            }

            gridRevealed = true;
            revealUses++;
            revealStart = steady_clock::now();

            message = "Map revealed for 15 seconds! Uses remaining: " +
                      to_string(2 - revealUses);
            return;
        }

        if (stage == 2 && grid.tiles[row][col] == "T")
        {
            if (!hasPotion)
            {
                message = "Collect the potion before lighting the torch.";
                return;
            }

            torchLit = true;
            message = "Torch lit! You can now reveal the wall codes.";
            return;
        }

        int tr = row + faceRow;
        int tc = col + faceCol;

        if (tr < 0 || tr >= ROWS || tc < 0 || tc >= COLS)
        {
            message = "Nothing to interact with in that direction.";
            return;
        }

        string tile = grid.tiles[tr][tc];

        if (tile == "E")
        {
            interactWithExit();
        }
        else if (stage == 0 && tile == "CW")
        {
            if (!hasHammer)
            {
                message = "You need the hammer to crack this wall.";
                return;
            }

            if (tr == 0 && tc == 5)
            {
                grid.tiles[tr][tc] = "K";
                message = "You cracked the wall! A key is revealed.";
            }
            else
            {
                grid.tiles[tr][tc] = ".";
                message = "You cracked the wall.";
            }
        }
        else if (stage == 1 && tile == "SW")
        {
            activateSwitch(tr, tc);
        }
        else if (stage == 2 && tile == "T")
        {
            if (!hasPotion)
            {
                message = "Collect the potion before lighting the torch.";
            }
            else
            {
                torchLit = true;
                message = "Torch lit! You can now reveal the wall codes.";
            }
        }
        else if (stage == 2 && tile == "C#")
        {
            revealCodeAt(tr, tc);
        }
        else
        {
            message = "Nothing to interact with here.";
        }
    }

    void movePlayer(int dr, int dc)
    {
        faceRow = dr;
        faceCol = dc;

        int nr = row + dr;
        int nc = col + dc;

        if (nr < 0 || nr >= ROWS ||
            nc < 0 || nc >= COLS ||
            !insideCurrentArea(nr, nc))
        {
            message = "You cannot leave this puzzle area.";
            return;
        }

        string tile = grid.tiles[nr][nc];

        if (isWall(tile))
        {
            message = "A wall blocks the way.";
            return;
        }

        if (tile == "E")
        {
            message = "You are facing the exit. Type E and press Enter.";
            return;
        }

        if (tile == "B")
        {
            if (stage != 0)
            {
                message = "This character cannot push the boulder.";
                return;
            }

            int br = nr + dr;
            int bc = nc + dc;

            if (br < 0 || br >= ROWS ||
                bc < 0 || bc >= COLS ||
                !insideCurrentArea(br, bc) ||
                grid.tiles[br][bc] != ".")
            {
                message = "The boulder cannot be pushed further.";
                return;
            }

            grid.tiles[br][bc] = "B";
            grid.tiles[nr][nc] = ".";
        }

        row = nr;
        col = nc;

        updatePosition();
        collectItem(tile, row, col);
    }

    bool readCommand(string& command)
    {
        fd_set inputSet;
        FD_ZERO(&inputSet);
        FD_SET(STDIN_FILENO, &inputSet);

        timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;

        int result = select(
            STDIN_FILENO + 1,
            &inputSet,
            nullptr,
            nullptr,
            &timeout
        );

        if (result > 0)
        {
            if (!getline(cin, command))
                return false;

            return true;
        }

        return false;
    }

    void displayLegend()
    {
        cout << "\nSYMBOL MENU\n";
        cout << "R = Rocky       S = Sprinty\n";
        cout << "BL = Blaze      SP = Splash\n";
        cout << "# = Wall        . = Empty floor\n";
        cout << "B = Boulder     CW = Cracked wall\n";
        cout << "H = Hammer      K = Key\n";
        cout << "BO = Bomb       SW = Switch\n";
        cout << "P = Potion      T = Torch\n";
        cout << "C# = Coded wall  0 = Pit\n";
        cout << "E = Exit\n";
    }

    void displayGrid()
    {
        cout << "\n";

        // CHANGED: Display the symbol menu above the grid.
        displayLegend();

        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                string tile = grid.tiles[r][c];
                bool isCharacter = false;

                for (int p = 0; p < 4; p++)
                {
                    if (playerRows[p] == r && playerCols[p] == c)
                    {
                        isCharacter = true;

                        if (p == 0)
                            tile = "R";
                        else if (p == 1)
                            tile = "S";
                        else if (p == 2)
                            tile = "BL";
                        else
                            tile = "SP";
                    }
                }

                if (stage == 3 && !gridRevealed && !isCharacter)
                    tile = "?";

                cout << setw(4) << tile;

                if (c == 6)
                    cout << " ||";
            }

            cout << '\n';

            if (r == 4)
                cout << string(70, '-') << '\n';
        }

        cout << "\nLives remaining: " << lives << '\n';

        if (stage == 0)
        {
            cout << "Hammer: "
                 << (hasHammer ? "Collected" : "Not collected")
                 << " | Key: "
                 << (hasRockyKey ? "Collected" : "Not collected")
                 << '\n';
        }
        else if (stage == 1)
        {
            cout << "Correct switch activated: "
                 << (switchOpened ? "Yes" : "No") << '\n';
        }
        else if (stage == 2)
        {
            cout << "Potion: "
                 << (hasPotion ? "Collected" : "Not collected")
                 << " | Torch: "
                 << (torchLit ? "Lit" : "Unlit") << '\n';

            cout << "Wall codes found: ";

            for (int i = 0; i < 3; i++)
            {
                if (codeRevealed[i])
                    cout << i + 1 << ' ';
                else
                    cout << "? ";
            }

            cout << "\nCode solved: "
                 << (codeSolved ? "Yes" : "No") << '\n';
        }
        else
        {
            cout << "Splash key: "
                 << (hasSplashKey ? "Collected" : "Not collected") << '\n';

            cout << "Map reveals remaining: "
                 << 2 - revealUses << '\n';

            if (gridRevealed)
            {
                double elapsed = duration<double>(
                    steady_clock::now() - revealStart
                ).count();

                int remaining = 15 - static_cast<int>(elapsed);

                if (remaining < 0)
                    remaining = 0;

                cout << "Reveal time remaining: "
                     << remaining << " seconds\n";
            }
        }

        // The old displayLegend() call here has been removed.

        if (codeInputMode)
            cout << "\nEnter code (123), then press Enter.\n";
        else
            cout << "\nEnter a command and press Enter.\n"
                 << "Examples: D | D 2 | W | E | Q\n";

        cout << "Message: " << message << '\n';
    }

public:
    Level3()
    {
        initialize();
    }

    void run()
    {
        bool redraw = true;
        int previousRemaining = -1;

        while (!gameOver && !gameWon)
        {
            if (stage == 3 && gridRevealed)
            {
                double elapsed = duration<double>(
                    steady_clock::now() - revealStart
                ).count();

                if (elapsed >= 15.0)
                {
                    gridRevealed = false;
                    message = "Time is up! Splash's map is hidden again.";
                    previousRemaining = -1;
                    redraw = true;
                }
                else
                {
                    int remaining = 15 - static_cast<int>(elapsed);

                    if (remaining != previousRemaining)
                    {
                        previousRemaining = remaining;
                        redraw = true;
                    }
                }
            }

            if (redraw)
            {
                cout << "\033[2J\033[H";
                displayGrid();
                cout << "\nCommand: " << flush;
                redraw = false;
            }

            string command;

            if (!readCommand(command))
                continue;

            stringstream input(command);
            string action;
            int steps = 1;

            input >> action;

            if (action.empty())
                continue;

            for (char& ch : action)
                ch = static_cast<char>(
                    toupper(static_cast<unsigned char>(ch))
                );

            if (codeInputMode)
            {
                if (action == codeSequence)
                {
                    codeSolved = true;
                    message = "Correct code! Blaze's exit is unlocked.";
                }
                else
                {
                    message = "Incorrect code. Try again at the exit.";
                }

                codeInputMode = false;
                redraw = true;
                continue;
            }

            if (action == "Q")
            {
                message = "Leaving Level 3.";
                break;
            }

            if (action == "E")
            {
                interact();
                redraw = true;
                continue;
            }

            if (action == "W" || action == "A" ||
                action == "S" || action == "D")
            {
                if (input >> steps)
                {
                    if (steps < 1)
                        steps = 1;

                    if (steps > 20)
                        steps = 20;
                }

                int dr = 0;
                int dc = 0;

                if (action == "W")
                    dr = -1;
                else if (action == "S")
                    dr = 1;
                else if (action == "A")
                    dc = -1;
                else if (action == "D")
                    dc = 1;

                for (int i = 0; i < steps; i++)
                {
                    int oldRow = row;
                    int oldCol = col;
                    int oldLives = lives;
                    int oldStage = stage;

                    movePlayer(dr, dc);

                    if (row == oldRow && col == oldCol)
                        break;

                    if (lives != oldLives ||
                        stage != oldStage ||
                        gameOver || gameWon)
                        break;
                }

                redraw = true;
            }
            else
            {
                message = "Invalid command. Use W, A, S, D, E or Q.";
                redraw = true;
            }
        }

        cout << "\033[2J\033[H";

        if (gameWon)
        {
            cout << "\n====================================\n";
            cout << "       LEVEL 3 COMPLETED!\n";
            cout << "       ELEMENTAL SQUAD WINS!\n";
            cout << "====================================\n";
        }
        else if (gameOver)
        {
            cout << "\nGAME OVER!\n";
        }
        else
        {
            cout << "\nYou left Level 3.\n";
        }

        cout << message << '\n';
    }
};

void level3Intro()
{
    cout << "\n====================================\n";
    cout << "          ELEMENTAL SQUAD\n";
    cout << "              LEVEL 3\n";
    cout << "====================================\n";

    cout << "\nFour puzzle areas form one 10 x 14 map.\n";
    cout << "Complete each area in clockwise order.\n";

    cout << "\nEnter a command, then press Enter:\n";
    cout << "W = Up, S = Down, A = Left, D = Right\n";
    cout << "D 2 = Move right up to two tiles\n";
    cout << "E = Interact\n";
    cout << "Q = Quit Level 3\n";
}

void level3Start()
{
    level3Intro();

    Level3 level;
    level.run();
}
