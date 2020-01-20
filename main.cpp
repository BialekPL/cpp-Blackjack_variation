//by Mateusz Bia³ecki, 18.01.2020 14:23 GMT+1

#include <iostream>
#include "funkcje.h"
#include <Windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	srand((unsigned)time(0));

	string talia[52] = { "2", "2", "2", "2",
		"3", "3", "3", "3",
		"4", "4", "4", "4",
		"5", "5", "5", "5",
		"6", "6", "6", "6",
		"7", "7", "7", "7",
		"8", "8", "8", "8",
		"9", "9", "9", "9",
		"D", "D", "D", "D",
		"J", "J", "J", "J",
		"Q", "Q", "Q", "Q",
		"K", "K", "K", "K",
		"A", "A", "A", "A" };

    string bidding = "O jaka stawke gramy?: ";
    string greeting = "Witaj! Ile pieniedzy chcesz wplacic?: ";
	int deposits[4] {50, 100, 250, 500};
	int bids[4] {5, 10, 25, 50};
	int cash = amount(greeting, deposits);
	system("cls");
	do {
		shuffle(talia);
		string pHand;
		string cHand;
		int card_nr = 4;
		int pPoints = 0;
        cout<<"Kasa: "<<cash<<"$\n";
		int bid = amount(bidding, bids);
		while (bid>cash)
        {
            system("cls");
            cout<<"Kasa: "<<cash<<"$\n";
            cout<<"Nie mozesz postawic wiecej niz posiadasz!\n";
            bid = amount(bidding, bids);
        }
		bool playing = true;
		rozdanie(talia, &pHand, &cHand);
		table(pHand, cHand, cash, bid, 500);
		if (!is_there_a_blackjack(pHand, cHand, &cash, bid))
        {
            double_bid(&bid);
            table(pHand, cHand, cash, bid, 0);
        }
		else playing = false;
		while (playing)
		{
			switch (stoi(decision())) {
			case 1:
				hit(&card_nr, &pHand, talia, &cash, bid);
				table(pHand, cHand, cash, bid, 0);
				if (value(pHand) > 21)
				{
					lose(&cash, bid);
					playing = false;
				}
				break;
			case 2:
				stand(&card_nr, &pHand, &cHand, talia, &cash, bid);
				playing = false;
				break;
			default:
				cout << "Wybierz poprawna opcje!\n";
			}


		};
        if (cash<5) break;

	} while (gramy());

	cout << "Wychodzisz z kasyna majac "<<cash<<" dolarow!\n\n";
	return 0;
};

