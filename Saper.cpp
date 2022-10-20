#include<iostream>
#include<ctime>
#include<iomanip>
#include<fstream>
#include<string>
#include<Windows.h>
#include<conio.h>
#include<vector>
using namespace std;
struct pole
{
    int wartosc;
    bool odkryte;

};
pole plansza[10][10];
bool generuj_plansze()
{

    for (int x = 0; x < 10; x++)
        for (int y = 0; y < 10; y++)
        {

            plansza[x][y].wartosc = 0;
            plansza[x][y].odkryte = false;
        }
    return true;

}

bool ustaw_mine(int poz_x, int poz_y)
{
    if (plansza[poz_x][poz_y].wartosc != 9)
    {
        plansza[poz_x][poz_y].wartosc = 9; //ustawiamy mine

        for (int k = -1; k < 2; k++)
            for (int l = -1; l < 2; l++)
            {
                if ((poz_x + l) < 0 || (poz_y + k) < 0) continue;
                if ((poz_x + l) > 9 || (poz_y + k) > 9) continue;

                if (plansza[poz_x + l][poz_y + k].wartosc == 9) continue; //wyjdz bo mina
                plansza[poz_x + l][poz_y + k].wartosc += 1; //zwieksz o 1
            }
    }

    return true;
}
void losuj_pozycje()
{
    time_t t;
    int poz_x, poz_y;
    int ilosc = 10;

    srand((unsigned)time(&t));

    while (ilosc > 0)
    {
        poz_x = rand() % 10;
        poz_y = rand() % 10;

        if (plansza[poz_x][poz_y].wartosc != 9)
        {
            ustaw_mine(poz_x, poz_y);
            ilosc--;
        }
    }
}
#define strzalka_lewo 0x25
#define strzalka_prawo 0x27
#define strzalka_dol 0x28
#define strzalka_gora 0x26
#define enter 0x0D

int poz_x = 0, poz_y = 0, o_poz_x = 1, o_poz_y = 1;
int koniec = 0;

void pokaz_plansze()
{
    system("cls");

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (j == poz_x && i == poz_y) //aktualkna pozycja kursora
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
                cout << "#";
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                if (plansza[j][i].odkryte == true)
                {
                    if (plansza[j][i].wartosc == 0)   //wartosc = 0
                        cout << " ";                //wyswietl spacje
                    else
                        cout << plansza[j][i].wartosc; //wyswietl wartosc 1-8

                }
                if (plansza[j][i].odkryte == false) //pole nie odkryte
                    cout << "#"; //wyswietl #
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        cout << endl;
    }

    cout << "\npozycja kursora:\n";
    cout << "X: " << poz_x << endl;  //aktualkna pozycja kursora
    cout << "Y: " << poz_y << endl;
}
void odkryj_plansze(int x, int y)
{
    if (x < 0 || x>9) return; // 
    if (y < 0 || y>9) return; // poza tablicą wyjście
    if (plansza[x][y].odkryte == true) return;  // już odkryte wyjście

    if (plansza[x][y].wartosc != 9 && plansza[x][y].odkryte == false)
        plansza[x][y].odkryte = true;   // odkryj!

    if (plansza[x][y].wartosc != 0) return; // wartość > 0 wyjście

    odkryj_plansze(x - 1, y - 1);
    odkryj_plansze(x - 1, y);
    odkryj_plansze(x - 1, y + 1);
    odkryj_plansze(x + 1, y - 1);
    odkryj_plansze(x + 1, y);
    odkryj_plansze(x + 1, y + 1);
    odkryj_plansze(x, y - 1);
    odkryj_plansze(x, y);
    odkryj_plansze(x, y + 1);
}

void sterowanie()
{
    if ((GetKeyState(enter) & 0x8000))
    {
        if (plansza[poz_x][poz_y].wartosc == 9) //trafiles na mine
            koniec = 2;

        odkryj_plansze(poz_x, poz_y); //odkrywanie pól
        pokaz_plansze(); // wyswietl plansze
    }

    if ((GetKeyState(strzalka_prawo) & 0x8000) && poz_x < 9) poz_x++;
    if ((GetKeyState(strzalka_lewo) & 0x8000) && poz_x > 0) poz_x--;
    if ((GetKeyState(strzalka_dol) & 0x8000) && poz_y < 9) poz_y++;
    if ((GetKeyState(strzalka_gora) & 0x8000) && poz_y > 0) poz_y--;

    if (o_poz_y == poz_y && o_poz_x == poz_x) return; //jeżeli nie ma ruchu wyjdz

    o_poz_y = poz_y; //zmienne pomocnicza do warunku wyżej
    o_poz_x = poz_x;

    pokaz_plansze(); // wyswietl plansze
}
bool sprawdz_czy_wygrana()
{
    int miny = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (plansza[j][i].odkryte == false)
                miny++;
        }
    }
    if (miny == 10) return true;
    return false;
}
pole plansza16x16[16][16];
bool generuj16x16()
{
    for (int x = 0; x < 16; x++)
        for (int y = 0; y < 16; y++)
        {

            plansza16x16[x][y].wartosc = 0;
            plansza16x16[x][y].odkryte = false;
        }
    return true;
}
bool ustawMine16x16(int pozX, int pozY)
{
    if (plansza16x16[pozX][pozY].wartosc != 15)
    {
        plansza16x16[pozX][pozY].wartosc = 15; //ustawiamy mine

        for (int k = -1; k < 2; k++)
            for (int l = -1; l < 2; l++)
            {
                if ((pozX + l) < 0 || (pozY + k) < 0) continue; //wyjdz bo krawedz
                if ((pozX + l) > 15 || (pozY + k) > 15) continue; //wyjdz bo krawedz

                if (plansza16x16[pozX + l][pozY + k].wartosc == 15) continue; //wyjdz bo mina
                plansza16x16[pozX + l][pozY + k].wartosc += 1; //zwieksz o 1
            }
    }

    return true;
}
void losuj_pozycje16x16()
{
    time_t t2;
    int pozX, pozY;
    int ilosc2 = 16;

    srand((unsigned)time(&t2));

    while (ilosc2 > 0)
    {
        pozX = rand() % 16;
        pozY = rand() % 16;

        if (plansza16x16[pozX][pozY].wartosc != 15)
        {
            ustawMine16x16(pozX, pozY);
            ilosc2--;
        }
    }

}
int pozX = 0, pozY = 0, o_pozX = 1, o_pozY = 1;
int koniec2 = 0;
void pokaz_plansze16x16()
{
    system("cls");

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (j == pozX && i == pozY) //aktualkna pozycja kursora
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
                cout << "#";
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                if (plansza16x16[j][i].odkryte == true) // pole odkryte
                {
                    if (plansza16x16[j][i].wartosc == 0)
                        cout << " ";
                    else
                        cout << plansza16x16[j][i].wartosc;

                }
                if (plansza16x16[j][i].odkryte == false)
                    cout << "#";
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        cout << endl;
    }

    cout << "\npozycja kursora:\n";  //aktualkna pozycja kursora
    cout << "X: " << pozX << endl;
    cout << "Y: " << pozY << endl;
}
void odkryj_plansze16x16(int x, int y)
{
    if (x < 0 || x>15) return;
    if (y < 0 || y>15) return;
    if (plansza16x16[x][y].odkryte == true) return;

    if (plansza16x16[x][y].wartosc != 15 && plansza16x16[x][y].odkryte == false)
        plansza16x16[x][y].odkryte = true;

    if (plansza16x16[x][y].wartosc != 0) return;


    odkryj_plansze16x16(x - 1, y - 1);
    odkryj_plansze16x16(x - 1, y);
    odkryj_plansze16x16(x - 1, y + 1);
    odkryj_plansze16x16(x + 1, y - 1);
    odkryj_plansze16x16(x + 1, y);
    odkryj_plansze16x16(x + 1, y + 1);
    odkryj_plansze16x16(x, y - 1);
    odkryj_plansze16x16(x, y);
    odkryj_plansze16x16(x, y + 1);

}
void sterowanie16x16()
{
    if ((GetKeyState(enter) & 0x8000))
    {
        if (plansza16x16[pozX][pozY].wartosc == 15) //trafiles na mine
            koniec2 = 2;

        odkryj_plansze16x16(pozX, pozY);
        pokaz_plansze16x16();
    }

    if ((GetKeyState(strzalka_prawo) & 0x8000) && pozX < 15) pozX++;
    if ((GetKeyState(strzalka_lewo) & 0x8000) && pozX > 0) pozX--;
    if ((GetKeyState(strzalka_dol) & 0x8000) && pozY < 15) pozY++;
    if ((GetKeyState(strzalka_gora) & 0x8000) && pozY > 0) pozY--;

    if (o_pozY == pozY && o_pozX == pozX) return; //jeżeli nie ma ruchu wyjdz

    o_pozY = pozY; //zmienne pomocnicza do warunku wyżej
    o_pozX = pozX;

    pokaz_plansze16x16();
}
bool sprawdz_czy_wygrana16x16()
{
    int miny = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (plansza16x16[j][i].odkryte == false)
                miny++;
        }
    }
    if (miny == 16) return true;
    return false;
}
int main()
{

    cout << "Witaj w grze SAPER" << endl;
    int akcja;
    do
    {
        cout << "[1] Nowa gra" << endl;
        cout << "[2] Pokaz wyniki graczy" << endl;
        cout << "[3] Zakoncz dzialanie" << endl;
        cout << " Twoj wybor: ";
        cin >> akcja;
        switch (akcja)
        {
        case 1:
        {
            int plansze;
            system("cls");
            do
            {
                cout << "[1] Plansza 10x10" << endl;
                cout << "[2] Plansza 16x16" << endl;
                cout << "[3] Plansza Wlasna" << endl;
                cout << "[4] Zakoncz dzialanie" << endl;
                cout << "Twoj wybor: ";
                cin >> plansze;
                switch (plansze)
                {
                case 1:
                {
                    generuj_plansze();
                    losuj_pozycje();
                    Sleep(200);

                    while (koniec == 0)
                    {
                        Sleep(60);
                        sterowanie();
                        if (sprawdz_czy_wygrana() == true) koniec = 1;
                    }

                    if (koniec == 2) cout << endl << "Trafiles na mine!! Przegrywasz :(" << endl;
                    if (koniec == 2) cout << "Twoj wynik to: " << 0 << endl;
                    break;
                    if (koniec == 1) cout << endl << "Wygrales!!! :) :)" << endl;
                    if (koniec == 1) cout << "Twoj wynik to: " << 2 * 10 * 10 << endl;
                    break;

                }
                case 2:
                {
                    generuj16x16();
                    losuj_pozycje16x16();
                    Sleep(200);

                    while (koniec2 == 0)
                    {
                        Sleep(60);
                        sterowanie16x16();
                        if (sprawdz_czy_wygrana16x16() == true) koniec2 = 1;
                    }

                    if (koniec2 == 2) cout << "Trafiles na mine!! Przegrywasz :(" << endl;
                    if (koniec2 == 2) cout << "Twoj wynik to: " << 0 << endl;
                    break;
                    if (koniec2 == 1) cout << "Wygrales!!! :) :)" << endl;
                    if (koniec2 == 1) cout << "Twoj wynik to: " << 2 * 16 * 16 << endl;
                    break;
                }
                case 3:
                {
                    break;

                }
                case 4:
                {
                    break;
                }
                break;
                }
            } while (plansze != 4);
            break;
        }
        case 2:
        {
            ifstream wyniki;
            wyniki.open("wyniki.txt");
            string linia;
            do
            {
                getline(wyniki, linia);
                cout << linia << endl;

            } while (linia != "");
            wyniki.close();
            break;
        }
        case 3:
        {
            break;
        }
        break;
        }
    } while (akcja != 3);





    return 0;
}

