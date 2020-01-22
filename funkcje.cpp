#include "funkcje.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;

char menu()
{

    cout<<"---------Blakjack---------\n";
    cout<<" [1] Graj\n";
    cout<<" [2] Zasady\n";
    cout<<" [3] WyjdŸ\n";
    cout<<" [4] Wczytaj gre\n";
    string choice;
	do {
        cin.clear();
        cout<<"> ";
        getline(cin, choice);
	} while (choice != "1" && choice != "2" && choice != "3" && choice != "4");

	switch (stoi(choice))
	{
        case 1:
            return '1';
            break;
        case 2:
            {
                ifstream plik;
                plik.open("zasady.txt");
                if (plik.is_open())
                {
                    system("cls");

                    string linia;
                    while(!plik.eof())
                    {
                        getline(plik, linia);
                        cout<<linia<<endl;
                    }
                    plik.close();
                    cin.get();
                    system("cls");
                    return menu();
                }else cout<<"Brak pliku \"zasady.txt\" w folderze gry!\n";

                break;
            }
        case 3:
            {
                cout<<"\n\tZaprzaszamy ponownie!\n\n\n";
                return '3';
                break;
            }
        case 4: return'4';
	}
	return '3';
}

int amount(string tekst, int stawki[]) {
	cout << tekst <<endl;
	for (int i = 0; i < 4; i++)
	{
		cout << "[" << i + 1 << "]" << stawki[i] << "$ ";
	}
	cout<<endl;
	string choice;
	do {
            cout  << '>';
		    cin.clear();
			getline(cin, choice);

	} while (choice != "1" && choice != "2" && choice != "3" && choice != "4");
	return stawki[stoi(choice) - 1];
}

bool gramy() {
	string wybor = "T";
	cout << "Czy chcesz graæ dalej[T/n]?\n";
	do {
            cin.clear();
			getline(cin, wybor);

	} while (wybor != "n" && wybor != "T");
	system("cls");
	return (wybor == "T" ? true : false);
}

void shuffle(string* ptr) {
	for (int i = 0; i < 150; i++)
	{
		int los1 = rand() % 52;
		int los2 = rand() % 52;
		//skopiowanie wskaznika
		string* ptr2 = ptr;
		//ustawienie jednego wskaznika na adres pierwszej wylosowanej karty
		//i drugiego na adres drugiej wylosowanej karty
		ptr += los1;
		ptr2 += los2;
		string bufor = *ptr;
		//zamiana miejscami dwoch kart
		*ptr = *ptr2;
		*ptr2 = bufor;
		//powrót wskaznika na poczatek talii
		ptr -= los1;
	}
}

void rozdanie(string talia[], string* pHand, string* cHand) {
	// Rozdanie graczowi i krupierowi po dwie karty.
	*pHand += talia[0];
	*pHand += talia[1];
	*cHand += talia[2];
	*cHand += talia[3];
}

void table(string pHand, string cHand, int cash, int bid, int delay, string nick) {
	system("cls");
	cout << "Kasa: " << cash << "$, stawka: "<<bid<<"$\n";
	Sleep(delay);
	cout << "Karty krupiera: ";
	print_hand(cHand, delay);
	Sleep(delay);
	cout << "Punkty: " << value(cHand) << endl;
	Sleep(delay);
	cout << "\nKarty gracza "<<nick<<": ";
	print_hand(pHand, delay);
	Sleep(delay);
	cout << "Punkty: " << value(pHand) << endl << endl;
}

bool is_there_a_blackjack(string pHand, string cHand,int* cash, int bid)
{
    if(pHand=="AA" && cHand == "AA")
    {
        cout<<"PODWOJNY BLACKJACK! REMIS! NIEBYWA£E!\n";
        draw();
        return true;
    }
    else if(pHand=="AA")
    {
        cout<<"GRACZ WYCI¥GA DWA ASY! BLACKJACK!\n";
        win(cash, bid);
        return true;
    }
    else if(cHand=="AA")
    {
        cout<<"KRUPIER WYCI¥GA DWA ASY! BLACKJACK!\n";
        lose(cash, bid);
        return true;
    }
    return false;
}

void double_bid(int* bid)
{
    string choice;
    cout << "Czy chcesz podwoiæ stawkê [T/n]?\n";
    do
    {
        cout<<">";
        cin.clear();
        getline(cin, choice);
    }while(choice!="n" && choice!="T");
    if (choice=="T") *bid*=2;
}

string decision() {
	string choice;
	cout << "Co chcesz zrobiæ?\n";

	do {
			cout << "1.Hit 2.Stand \n>";
			cin.clear();
			getline(cin, choice);
	} while (choice != "1" && choice != "2");
	return choice;
};

void print_hand(string hand, int delay) {
	for (int i = 0; i < (int)hand.length(); i++)
    {
         Sleep(delay);
         cout << "[" << hand[i] << "] ";
    }
}


void hit(int* card_nr, string* hand, string talia[], int* cash, int bid)
{
	*hand += talia[*card_nr];
	*card_nr += 1;
}
int value(string hand) {
	int sum = 0;
	bool as = false;
	if (hand=="AA") return 22;
	for (int i = 0; i < (int)hand.length(); i++)
	{
		char card = hand[i];
		if (card == 'K' || card == 'Q' || card == 'J' || card == 'D') sum += 10;
		else if (card == 'A') as = true;
		else sum += card - '0';
	}
	if (as)
	{
		sum += (sum > 11 ? 1 : 10);
	}
	return sum;
}

void stand(int* card_nr, string* pHand, string* cHand, string talia[], int* cash, int bid, string nick)
{
	int c = value(*cHand);
	int p = value(*pHand);
	while (c < 12 || c < p)
	{
		cout << "Krupier dobiera kartê...";
		Sleep(600);
		cout << " [" << talia[*card_nr] << "] ";
		Sleep(600);
		hit(card_nr, cHand, talia, cash, bid);
		table(*pHand, *cHand, *cash, bid, 0, nick);
		if (c > 21) break;
		p = value(*pHand);		c = value(*cHand);
	}
	if (p > c || c > 21) win(cash, bid);
	else if (p == c) draw();
	else lose(cash, bid);
}

void lose(int* cash, int bid)
{
	cout << "\tPRZEGRA£EŒ!\n";
	*cash -= bid;
};

void win(int* cash, int bid)
{
	cout << "\tWYGRA£EŒ!\n";
	*cash += bid;
};

void draw()
{
	cout << "\tREMIS!\n";
};

void save(string nick, int cash)
{
    ofstream savefile;
    savefile.open("zapis");
    if (savefile.is_open())
    {
        savefile << nick << endl << cash;
        savefile.close();
    }else cout<<"\nNie uda³o siê zapisaæ gry!";
}

bool load(string* nick, int* cash)
{
    ifstream loadfile;
    loadfile.open("zapis");
    if(loadfile.is_open())
    {
        string line;
        try
        {
            getline(loadfile, line);
            *nick = line;
            getline(loadfile, line);
            if (line == "0")
            {
                cout<<"Na koncie mia³eœ 0$, lecz znalaz³eœ na ziemi ¿eton o wartoœci 5$!\n";
                Sleep(1200);
                line="5";
            }
            *cash = stoi(line);
            cout<<"\nWczytano zapis!\nNick: "<<*nick<<"\nKasa: "<<*cash<<"$.";
            Sleep(1500);
            return true;
        }catch(...)
        {
             cout<<"B³¹d odczytu!";
             Sleep(1000);
             system("cls");
             return false;
        }
    }else
    {
        cout<<"Brak pliku \"zapis\" w folderze gry!";
        Sleep(1000);
        system("cls");
        return false;
    }
}

void player_info(string* nick, int* cash)
{
    cout<<"Podaj swój nick: ";
    cin.clear();
    getline(cin, *nick);
    cout<<"\nNick> "<<*nick;
    Sleep(1000);
    system("cls");
    string greeting = "Witaj! Ile pieniêdzy chcesz wp³aciæ?: ";
    int deposits[4] {50, 100, 250, 500};
    *cash = amount(greeting, deposits);
}
