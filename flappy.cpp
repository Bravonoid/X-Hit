#include <iostream> 
#include <conio.h>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;


void swap(char &a, char &b);
void fullscreen();
void decoration();
void spaces(string str);
void intro();
void menu();
void game();
void map(vector <vector<char>> &area, int &j, int &k, int &playerI, int &playerJ, int &score);
void pixel();
int randomGenerator();
void leaderboard();
void input_leaderboard(string& name, int& score);

// MISSING LINKs
// 1. Guest
// 2. Player --> Save Score
// 3. Difficulty Mechanism
// Wrapping up
// 1. Finishing Intro
// 2. Adding Options(?)
// 3. Finishing Exit
// 4. Credits
// 5. Terminal Colors
// 6. Resizing Interface

int main(int argc, char const *argv[])
{
    fullscreen();
    intro();
    // game();
    return 0;
}

void swap(char &a, char &b){
    char temp;
    temp = a;
    a = b;
    b = temp;
}

void fullscreen(){
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    SendMessage(GetConsoleWindow(),WM_SYSKEYDOWN,VK_RETURN,0x20000000);
}

void spaces(string str = ""){
    int length = 91-(str.length()/4);
    for(int i=0; i<length; i++){
        cout << " ";
    }
}

void intro(){
    int j=0;
    int k=0;
    char ch;
    vector<char> welcome = {'W','E','L','C','O','M','E',
                            ' ','T','O',' ','F','L','A',
                            'P','P','Y',' ','B','I','R',
                            'D',' ','R','E','P','L','I',
                            'C','A','T','I','O','N',' ',
                            ' '};
    while(true){
        system("cls");
        decoration();
        spaces();
        for(j; j<k+31; j++){
            cout << welcome[j];
        }
        cout << endl;
        decoration();

        k++;
        j=k;
        welcome.push_back(welcome[k-1]);

        cout << endl;
        spaces();
        cout << "PRESS ANY KEY TO ENTER THE GAME" << endl;
        cout << endl;
        decoration();

        if(_kbhit()){
            ch = _getch();
            menu();
            break;
        }
        Sleep(1000);
    }
}

void menu(){
    string menu = "MAIN MENU";
    int distance = 30-(menu.length()*2);
    string str = "Thanks for your visit, hope you have a nice day!";
    int strLen = str.length();
    while(true){
        system("cls");
        decoration();
        for(int i=1; i<distance; i++){
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
        switch (choice){
            case '1':
                // 1. Guest
                game();
                continue;
            case '2':
                // 2. Player
                // game();
                continue;
            case '3':
                // 3. Leaderboard();
                leaderboard();
                continue;
            case '4':
                // 4. Credits();
                continue;
            case '5':
                system("cls");
                spaces();
                pixel();
                spaces();
                for(int i=0; i<strLen; i++){
                    cout << "=";
                }
                cout << endl;
                spaces();
                cout << str << endl;
                spaces();
                for(int i=0; i<strLen; i++){
                    cout << "=";
                }
                getchar();
                break;
            default:
                continue;
        }
        break;
    }
}

void map(vector <vector<char>> &area, int &j, int &k, int &playerI, int &playerJ, int &score) {
    system("cls");
    for(int i=0; i<12; i++){
        spaces();
        for(j; j<k+31; j++){
            if(area[i][j]=='X'){
                playerI=i;
                playerJ=j;
            }
            cout << area[i][j];
        }
        j=k;
        cout << endl;
    }
    spaces();
    cout << "POINTS : " << score << endl;
    spaces();
    cout << "===============================" << endl;
}

void game(){
    repeat:
    srand(time(0));
    int playerI = 0, playerJ = 0;
    int k=0, j=0;
    int score = 0;
    bool lose = false;

    vector <int> random;
    for(int i=0; i<10000; i++){
        random.push_back(rand()%12+1);
    }

    // 5. Random Obstacles
    vector <vector<char>> area;
    for (int i = 0; i < 12;i++) {
        area.push_back(vector<char>());
        for(int j = 0; j < 10000; j++) {
            if(i==0 || i==11){
                area[i].push_back('=');
            }else if(i==5 && j==1){
                area[i].push_back('X');
            }else if(j==0){
                area[i].push_back(' ');
            }else{
                area[i].push_back(' ');
            }
            if(j%4==0 && j>1){
                if(i>0 && i<11){
                    if(random[j] == 1){
                        if(i<2 || i>5) area[i].push_back('|');
                    }else if(random[j] == 2){
                        if(i>3) area[i].push_back('|');
                    }else if(random[j] == 3){
                        if(i<4 || i>7) area[i].push_back('|');
                    }else if(random[j] == 4){
                        if(i<6) area[i].push_back('|');
                    }else if(random[j] == 5){
                        if(i<3 || i>6) area[i].push_back('|');
                    }else if(random[j] == 6){
                        if(i>3 && i<7) area[i].push_back('|');
                    }else if(random[j] == 7){
                        if(i>5 && i<9) area[i].push_back('|');
                    }else if(random[j] == 8){
                        if(i<5) area[i].push_back('|');
                    }else if(random[j] == 9){
                        if(i>2 && i<8) area[i].push_back('|');
                    }else if(random[j] == 10){
                        if(i>4) area[i].push_back('|');
                    }else{
                        area[i].push_back(' ');
                    }
                }
            }
        }
    }

    while(true){
        map(area, j, k, playerI, playerJ, score);
        char key;
        // 7. Difficulty Mechanism
        Sleep(500);

        if(_kbhit()){
            key = _getch();
            if ((key=='w' || key=='W') && (playerI>0)){
                if(area[playerI - 1][playerJ + 1] == '|') lose = true;
                swap(area[playerI][playerJ],area[playerI--][playerJ++]);
                if(area[playerI + 1][playerJ + 1] == '|' && area[playerI][playerJ + 1] == '|') lose = true;
            }else{
                if(area[playerI + 1][playerJ + 1] != ' ') lose = true;
                swap(area[playerI][playerJ],area[playerI++][playerJ++]);
            }
        }else{
            if(area[playerI + 1][playerJ + 1] != ' ') lose = true;
            swap(area[playerI][playerJ],area[playerI++][playerJ++]);
        }

        if(lose == true){
            char again;
            // SAVE SCORE
            while(true){
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
                spaces();
                cout << "Play Again? [Y/N]: ";
                again = _getch();

                if(again=='y' || again=='Y'){
                    goto repeat;
                }else if(again=='n' || again=='N'){
                    break;
                }else{
                    continue;
                }
            }
            break;
        }

        score++;
        k++;
        j=k;
    }
}

void decoration(){
    spaces();
    for(int i=0; i<31; i++){
            cout << "=";
    }
    cout << endl;
}

void pixel(){
    cout << endl;
    spaces();
    cout << "              ##################" << endl;
    spaces();
    cout << "           ###           #        #" << endl;
    spaces();
    cout << "          #            #            #" << endl; 
    spaces(); 
    cout << "     #########           #             #" << endl;
    spaces(); 
    cout << "   #          #             #######    #" << endl;
    spaces();
    cout << " #             #                   ##############" << endl;
    spaces();
    cout << "   #          #                 #                 #" << endl;
    spaces();
    cout << "    #########               #	   #############" << endl;
    spaces();
    cout << "     #                         ##              #" << endl;
    spaces();
    cout << "       #####                      #    ########" << endl;
    spaces(); 
    cout << "            ####################" << endl;  
    cout << endl;
}

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

    if (infile.fail()) {
        cerr << "Error Membuka File" << endl;
        exit(1);
    }

    int i = 0;
    int count = 0;
    while (!infile.eof()) {
        infile >> p[i].name >> p[i].score;
        i++;
        count++;
    }
    infile.close();

    sort(p, p + count, player::comp);

    system("cls");
    decoration();
    spaces();
    cout << "          LEADERBOARD" << endl << endl;
    spaces();
    cout << "NO.\tNAME\t\tSCORE" << endl;
    decoration();
    for (int i = 0; i < count; i++) {
        spaces();
        // cout << i + 1 << ". " << p[i].name << right << setw(15) << p[i].score << endl;
        cout << i + 1 << ".\t" << p[i].name << "\t\t" << p[i].score << endl;
        if(i == 9){
            break;
        }
    }
    decoration();
    spaces();
    cout << "Press any key to continue...";
    _getch();
}

// back-up
void input_leaderboard(string& name, int& score) {
    fstream myfile;
    myfile.open("Leaderboard.txt", ios::app);
    if (!myfile.fail()) {
        cerr << "Error Membuka File" << endl;
        exit(1);
    }
    myfile << name << " " << score << endl;
    myfile.close();
}