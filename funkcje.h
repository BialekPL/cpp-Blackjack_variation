#pragma once
#include <iostream>
#include <string>
using namespace std;

int amount(string tekst, int stawki[]);
bool gramy();
void shuffle(string* ptr);
void rozdanie(string talia[], string* pHand, string* cHand);
void table(string pHand, string cHand, int cash, int bid, int delay, string nick);
bool is_there_a_blackjack(string pHand, string cHand,int* cash, int bid);
void double_bid(int* bid);
string decision();
void print_hand(string hand, int delay);
void hit(int* card_nr, string* Hand, string talia[], int* cash, int bid);
int value(string card);
void stand(int* card_nr, string* pHand, string* cHand, string talia[], int* cash, int bid, string nick);
void lose(int* cash, int bid);
void win(int* cash, int bid);
void draw();
char menu();
void save(string nick, int cash);
bool load(string* nick, int* cash);
void player_info(string* nick, int* cash);
