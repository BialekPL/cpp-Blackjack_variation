//by Mateusz Bia³ecki, 18.01.2020 14:23 GMT+1

#include <iostream>
#include "funkcje.h"
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    setlocale(LC_ALL,"");
	srand((unsigned)time(0));
	string nick;
	int cash=0;
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
    char menu_choice = menu();
    if (menu_choice=='3')
    {
        return 0;
    }
    if (menu_choice=='4')
	{
	    if (load(&nick, &cash)==false)
        {
            player_info(&nick, &cash);
        }
	}
	if (menu_choice=='1') player_info(&nick, &cash);
    string bidding = "O jaka stawkê gramy?: ";
	int bids[4] {5, 15, 50, 100};

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
            cout<<"Nie mo¿esz postawiæ wiêcej ni¿ posiadasz!\n";
            bid = amount(bidding, bids);
        }
		bool playing = true;
		rozdanie(talia, &pHand, &cHand);
		table(pHand, cHand, cash, bid, 400, nick);
		if (!is_there_a_blackjack(pHand, cHand, &cash, bid))
        {
            if(cash>=(bid*2)) double_bid(&bid);
            table(pHand, cHand, cash, bid, 0, nick);
        }
		else playing = false;
		while (playing)
		{
			switch (stoi(decision())) {
			case 1:
				hit(&card_nr, &pHand, talia, &cash, bid);
				table(pHand, cHand, cash, bid, 0, nick);
				if (value(pHand) > 21)
				{
					lose(&cash, bid);
					playing = false;
				}
				break;
			case 2:
				stand(&card_nr, &pHand, &cHand, talia, &cash, bid, nick);
				playing = false;
				break;
			default:
				cout << "Wybierz poprawna opcjê!\n";
			}

		};
        if (cash<5) break;

	} while (gramy());
	save(nick, cash);

	cout << "Wychodzisz z kasyna majac "<<cash<<" dolarów!\n\tZapraszamy ponownie!\n";
	return 0;
};

