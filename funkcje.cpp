#include "funkcje.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

int amount(string tekst, int stawki[]) {
	cout << tekst <<endl;
	for (int i = 0; i < 4; i++)
	{
		cout << "[" << i + 1 << "] " << stawki[i] << "$ ";
	}
	cout << endl << '>';
	string choice;
	do {
		try
		{
			getline(cin, choice);
		}
		catch (...)
		{
			cout << "try again";
		};
	} while (choice != "1" && choice != "2" && choice != "3" && choice != "4");
	return stawki[stoi(choice) - 1];
}

bool gramy() {
	string wybor = "T";
	cout << "Czy chcesz grac dalej[T/n]?\n";
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

void table(string pHand, string cHand, int cash, int bid, int delay) {
	system("cls");
	cout << "Kasa: " << cash << "$, stawka: "<<bid<<"$\n";
	Sleep(delay);
	cout << "Karty krupiera: ";
	print_hand(cHand, delay);
	Sleep(delay);
	cout << "Punkty: " << value(cHand) << endl;
	Sleep(delay);
	cout << "\nTwoje karty: ";
	print_hand(pHand, delay);
	Sleep(delay);
	cout << "Punkty: " << value(pHand) << endl << endl;
}

bool is_there_a_blackjack(string pHand, string cHand,int* cash, int bid)
{
    if(pHand=="AA" && cHand == "AA")
    {
        cout<<"PODWOJNY BLACKJACK! REMIS! NIEBYWALE!\n";
        draw();
        return true;
    }
    else if(pHand=="AA")
    {
        cout<<"GRACZ WYCIAGA DWA ASY! BLACKJACK!\n";
        win(cash, bid);
        return true;
    }
    else if(cHand=="AA")
    {
        cout<<"KRUPIER WYCIAGA DWA ASY! BLACKJACK!\n";
        lose(cash, bid);
        return true;
    }
    return false;
}

void double_bid(int* bid)
{
    string choice;
    cout << "Czy chcesz podwoic stawke [T/n]?\n";
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
	cout << "Co chcesz zrobic?\n";

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

void stand(int* card_nr, string* pHand, string* cHand, string talia[], int* cash, int bid)
{
	int c = value(*cHand);
	int p = value(*pHand);
	while (c < 12 || c < p)
	{
		cout << "Krupier dobiera karte...";
		Sleep(800);
		cout << " [" << talia[*card_nr] << "] ";
		Sleep(800);
		hit(card_nr, cHand, talia, cash, bid);
		table(*pHand, *cHand, *cash, bid, 0);
		if (c > 21) break;
		p = value(*pHand);		c = value(*cHand);
	}
	if (p > c || c > 21) win(cash, bid);
	else if (p == c) draw();
	else lose(cash, bid);
}

void lose(int* cash, int bid)
{
	cout << "PRZEGRALES!\n";
	*cash -= bid;
};

void win(int* cash, int bid)
{
	cout << "WYGRALES!\n";
	*cash += bid;
};

void draw()
{
	cout << "REMIS!\n";
};
