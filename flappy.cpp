#include <iostream>     // Input Output
#include <conio.h>      // Keyboard Interrupt
#include <windows.h>    // Delay
#include <vector>       // Dynamic Array
#include <fstream>      // File Operation
#include <string>       // String Manipulation
#include <algorithm>    // Sorting
#include <cwchar>       // Adjust size

using namespace std;

// Core of the game
void swap(char& a, char& b);
// UI Purposes
void fullscreen();
void decoration();
void spaces(string str);
// Main Program
void intro();
void menu();
void game(bool player);
void map(vector <vector<char>>& area, int& j, int& k, int& playerI, int& playerJ, int& score);
void pixel();
void leaderboard();
void input_leaderboard(string& name, int& score);
void credits();
void instruction();

int main(int argc, char const* argv[])
{
    fullscreen();
    intro();
    return 0;
}

// For swapping index
void swap(char& a, char& b) {
    char temp;
    temp = a;
    a = b;
    b = temp;
}

// To make the terminal become fullscreen
void fullscreen() {
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 25;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

// To center output (adding spaces before the output)
void spaces(int len = 48) {
    string str = "" ;
    int length = len - (str.length() / 4);
    for (int i = 0; i < length; i++) {
        cout << " ";
    }
}

// Instruction before getting into the game
void instruction(){
    system("cls");
    char ch;
    decoration();
    spaces();
    cout << "          HOW TO PLAY" << endl;
    decoration();

    spaces();
    cout << "# GAME" << endl;
    spaces();
    cout << "-Avoid obstacles" << endl;
    spaces();
    cout << "-Press 'W' to go up" << endl;
    cout << endl;
    spaces();
    cout << "# MENU" << endl;
    spaces();
    cout << "-Guest  : Scores is not saved" << endl;
    spaces();
    cout << "-Player : Scores is saved" << endl;

    decoration();
    spaces();
    cout << "           HAVE FUN!";
    ch = _getch();
}

// Intro with moving text
void intro() {
    int j = 0;
    int k = 0;
    char ch;
    vector<char> welcome = {'W','E','L','C','O','M','E',
                            ' ','T','O',' ','X','-','H',
                            'I','T',' ','(','F','L','A',
                            'P','P','Y',' ','B','I','R',
                            'D',' ','R','E','P','L','I',
                            'C','A','T','I','O','N',')',
                            ' ',' ',};
    while (true) {
        system("cls");
        decoration();
        spaces();
        for (j; j < k + 31; j++) {
            cout << welcome[j];
        }
        cout << endl;
        decoration();

        k++;
        j = k;
        welcome.push_back(welcome[k - 1]);

        cout << endl;
        spaces();
        cout << "PRESS ANY KEY TO ENTER THE GAME" << endl;
        cout << endl;
        decoration();
        
        if (_kbhit()) {
            ch = _getch();
            instruction();
            menu();
            break;
        }
        Sleep(1000);
    }
}

// Main Menu
void menu() {
    string menu = "MAIN MENU";
    int distance = 30 - (menu.length() * 2);
    string str = "Thanks for your visit, hope you have a nice day!";
    int strLen = str.length();
    bool player;
    while (true) {
        system("cls");
        decoration();
        for (int i = 1; i < distance; i++) {
            cout << " ";
        }
        spaces();
        cout << "MAIN MENU" << endl;
        decoration();
        spaces();
        cout << "1. Play as Guest" << endl;
        spaces();
        cout << "2. Play as Player" << endl;
        spaces();
        cout << "3. Leaderboard" << endl;
        spaces();
        cout << "4. Credits" << endl;
        spaces();
        cout << "5. Exit" << endl;
        decoration();
        char choice = _getch();
        char color = 1;
        switch (choice) {
        case '1':
            // 1. Guest
            player = false;
            game(player);
            continue;
        case '2':
            // 2. Player
            player = true;
            game(player);
            continue;
        case '3':
            // 3. Leaderboard();
            leaderboard();
            continue;
        case '4':
            credits();
            // 4. Credits();
            continue;
        case '5':
            // 5. Exit
            system("cls");
            spaces(40);
            pixel();
            spaces(40);
            for (int i = 0; i < strLen; i++) {
                cout << "=";
            }
            cout << endl;
            spaces(40);
            cout << str << endl;
            spaces(40);
            for (int i = 0; i < strLen; i++) {
                cout << "=";
            }

            // Changing output color
            while(true) {
                if (color == 9) color = 1;
                string c = "color " + to_string(color);
                system(c.c_str());
                Sleep(500);
                if(_kbhit()) {
                    break;
                }
                color++;
            }
            break;
        default:
            continue;
        }
        break;
    }
}

// Credits showing one by one
void credits () {
    string arr[5][100] = {
        {"Created By"},
        {"Azzakhruf Aryan Nur Ihsan"},
        {"Diki Bagastama"},
        {"Kenneth Christopher Prasetya"},
        {"Nur Aziz Tri Indrawan"},
    };
    system("cls");
    decoration();
    for(int j=0;j<5;j++){
        j == 0 ? spaces(59) : spaces(50);
        for (int i= 0; i < 50; i++) {
            cout<< arr[j][i];
        }
        cout << endl;
        for(int i=0; i< 10; i++) {
            if(_kbhit()) {
                return;
            }
            Sleep(100);
        }
    }
    decoration();
    _getch();
}

// Output for the map
void map(vector <vector<char>>& area, int& j, int& k, int& playerI, int& playerJ, int& score) {
    system("cls");
    for (int i = 0; i < 12; i++) {
        spaces();
        for (j; j < k + 31; j++) {
            if (area[i][j] == 'X') {
                playerI = i;
                playerJ = j;
            }
            cout << area[i][j];
        }
        j = k;
        cout << endl;
    }
    spaces();
    cout << "POINTS : " << score << endl;
    spaces();
    cout << "===============================" << endl;
}

// Game
void game(bool player) {
    string name;
    if(player){
        spaces();
        cout << "        INPUT YOUR NAME" << endl;
        spaces();
        cin >> name;
    }
    repeat:
    srand(time(0));
    int playerI = 0, playerJ = 0;
    int k = 0, j = 0;
    int score = 0;
    bool lose = false;

    // random generator
    vector <int> random;
    for (int i = 0; i < 10000; i++) {
        random.push_back(rand() % 12 + 1);
    }

    // making the maps (including player and random obstacles)
    vector <vector<char>> area;
    for (int i = 0; i < 12; i++) {
        area.push_back(vector<char>());
        for (int j = 0; j < 10000; j++) {
            if (i == 0 || i == 11) {
                area[i].push_back('=');
            }
            else if (i == 5 && j == 1) {
                area[i].push_back('X');
            }
            else if (j == 0) {
                area[i].push_back(' ');
            }
            else {
                area[i].push_back(' ');
            }
            if (j % 4 == 0 && j > 1) {
                if (i > 0 && i < 11) {
                    if (random[j] == 1) {
                        if (i < 2 || i>5) area[i].push_back('|');
                    }
                    else if (random[j] == 2) {
                        if (i > 3) area[i].push_back('|');
                    }
                    else if (random[j] == 3) {
                        if (i < 4 || i>7) area[i].push_back('|');
                    }
                    else if (random[j] == 4) {
                        if (i < 6) area[i].push_back('|');
                    }
                    else if (random[j] == 5) {
                        if (i < 3 || i>6) area[i].push_back('|');
                    }
                    else if (random[j] == 6) {
                        if (i > 3 && i < 7) area[i].push_back('|');
                    }
                    else if (random[j] == 7) {
                        if (i > 5 && i < 9) area[i].push_back('|');
                    }
                    else if (random[j] == 8) {
                        if (i < 5) area[i].push_back('|');
                    }
                    else if (random[j] == 9) {
                        if (i > 2 && i < 8) area[i].push_back('|');
                    }
                    else if (random[j] == 10) {
                        if (i > 4) area[i].push_back('|');
                    }
                    else {
                        area[i].push_back(' ');
                    }
                }
            }
        }
    }

    while (true) {
        map(area, j, k, playerI, playerJ, score);
        char key;
        // Difficulty Mechanism
        Sleep(500 - score);

        // Keyboard interrupt
        if (_kbhit()) {
            key = _getch();
            if ((key == 'w' || key == 'W') && (playerI > 0)) {
                if (area[playerI - 1][playerJ + 1] == '|' || area[playerI - 1][playerJ + 1] == '=') lose = true;
                swap(area[playerI][playerJ], area[playerI-1][playerJ+1]);
                if (area[playerI + 1][playerJ + 1] == '|' && area[playerI][playerJ + 1] == '|') lose = true;
            }else {
            if (area[playerI + 1][playerJ + 1] != ' ') lose = true;
            swap(area[playerI][playerJ], area[playerI+1][playerJ+1]);
            }
        }
        else {
            if (area[playerI + 1][playerJ + 1] != ' ') lose = true;
            swap(area[playerI][playerJ], area[playerI+1][playerJ+1]);
        }

        // Check lose
        if (lose == true) {
            char again;
            // Save score (only on player)
            if(player){
                ofstream outfile;
                outfile.open("leaderboard.txt", std::ofstream::ate| std::ofstream::app);
                outfile << name << " " << score;
                outfile.close();
            }
            while (true) {
                system("cls");
                spaces();
                cout << "=================" << endl << endl;
                spaces();
                cout << "    GAME OVER" << endl << endl;
                spaces();
                cout << "=================" << endl;
                spaces();
                cout << "FINAL POINTS : " << score << endl;
                spaces();
                cout << "=================" << endl;

                // Play again?
                spaces();
                cout << "Play Again? [Y/N]: ";
                again = _getch();
                if (again == 'y' || again == 'Y') {
                    goto repeat;
                }
                else if (again == 'n' || again == 'N') {
                    break;
                }
                else {
                    continue;
                }
            }
            break;
        }
        score++;
        // Core of moving map
        k++;
        j = k;
    }
}

// Decoration purpose (adding '=' multiple times)
void decoration() {
    spaces();
    for (int i = 0; i < 31; i++) {
        cout << "=";
    }
    cout << endl;
}

// Addition for the outro
void pixel() {
    cout << endl;
    spaces(38);
    cout << "              ##################" << endl;
    spaces(38);
    cout << "           ###           #        #" << endl;
    spaces(38);
    cout << "          #            #            #" << endl;
    spaces(38);
    cout << "     #########           #             #" << endl;
    spaces(38);
    cout << "   #          #             #######    #" << endl;
    spaces(38);
    cout << " #             #                   ##############" << endl;
    spaces(38);
    cout << "   #          #                 #                 #" << endl;
    spaces(38);
    cout << "    #########               #	   #############" << endl;
    spaces(38);
    cout << "     #                         ##              #" << endl;
    spaces(38);
    cout << "       #####                      #    ########" << endl;
    spaces(38);
    cout << "            ####################" << endl;
    cout << endl;
}

// Leaderboard mechanism
void leaderboard() {
    struct player {
        string name;
        int score;
        static bool comp(player& a, player& b) {
            return a.score > b.score;
        };
    };
    player* p;

    p = new player[10];

    ifstream infile;
    infile.open("leaderboard.txt");

    // Check leaderboard.txt exist or not
    if (infile.fail()) {
        system("cls");
        decoration();
        spaces();
        cerr << "No scores are saved...yet." << endl;
        decoration();
        spaces();
        cout << "Please play the game first";
        _getch();
    }else{
        int i = 0;
        int count = 0;

        // Insert name and score to leaderboard.txt
        while (!infile.eof()) {
            infile >> p[i].name >> p[i].score;
            i++;
            count++;
        }
        infile.close();

        // Sorting descending
        sort(p, p + count, player::comp);

        // Showing the leaderboard
        system("cls");
        decoration();
        spaces();
        cout << "          LEADERBOARD" << endl << endl;
        spaces();
        cout << "NO.\tNAME\t\tSCORE" << endl;
        decoration();
        for (int i = 0; i < count; i++) {
            spaces();
            cout << i + 1 << ".\t" << p[i].name << "\t\t" << p[i].score << endl;
            if (i == 9) {
                break;
            }
        }
        decoration();
        spaces();
        cout << "Press any key to continue...";
        _getch();
    }
}