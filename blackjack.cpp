// This is the main project file for VC++ application project 
// generated using an Application Wizard.

#include <iostream>
using namespace std;

#include "log.h"
#include "deck.h"
#include "hand.h"

const int BLACK_JACK = 21;

int main()
{
	char entry;
	char ans;

	// create logfile
	Log logfile;

	//create Deck object
	Deck deck;

	// print welcome message
	cout << "Welcome to Blackjack Program" << endl << endl;

	//shuffle cards in the deck	
	deck.shuffle();


	// round loop
	do{

	Hand player;
	Hand bank;

	// deal 2 cards to player
	player.add(deck.deal());
	player.add(deck.deal());


	// deal 2 cards to bank
	bank.add(deck.deal());
	bank.add(deck.deal());

		// play loop
		while (true)
		{

			cout << "bank shows a ";
			bank.printTop();
			cout << endl;

			cout << "Your hand: ";
			player.print();
			cout << endl;

			// check if player/bank blackjack (21) / bust
			if (player.score() >= BLACK_JACK || bank.score() >= BLACK_JACK) break;


			else
			{

				cout << "(S)tick, (T)wist: ";
				cin >> entry;


				// twist- player draws card
				if (entry == 'T' || entry == 't')
				{
					player.add(deck.deal());
				}

				// stick
				else if (entry == 'S' || entry == 's')
				{
					// bank draws until summ is at least 17
					while (bank.score() < 17)
					{
						cout << "Bank draws a card" << endl;
						bank.add(deck.deal());
					}

					break;

				}

			}

		}

		// check who wins
		cout << endl << "banks hand is: ";
		bank.print();
		cout << endl;


		// check for tie game
		if (player.score() == bank.score())
		{
			cout << "tie game" << endl;
			logfile.addTie();
		}

		// check if bank blackjack (21)
		else if (player.score() == BLACK_JACK)
		{
			cout << "blackjack player wins!" << endl;
			logfile.addWon();
		}

		// check if bank blackjack (21)
		else if (bank.score() == 21)
		{
			cout << "blackjack bank wins!" << endl;
			logfile.addLost();
		}

		else  if (player.score() > BLACK_JACK)
		{
			cout << "player busts so bank wins" << endl;
			logfile.addLost();
		}

		else if (bank.score() > BLACK_JACK)
		{
			cout << "bank busts so player wins" << endl;
			logfile.addWon();
		}

		else if (bank.score() > player.score())
		{
			cout << "bank  wins" << endl;
			logfile.addLost();
		}

		else

			cout << "player wins" << endl;
		    logfile.addWon();


	// pause
	cout << "\nDo you want to play another round (Y/N)? ";

	cin >> ans;

} while (ans == 'Y' || ans == 'y');

    logfile.report(); // write report to logfile
	return 0;
}