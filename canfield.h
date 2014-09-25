/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     canfield.h
  Last updated:  September 2014
  Description:   Implementation of the card game of Canfield using 
                 stacks and queues.
**********************************************************************/

#ifndef CANFIELD_H
#define CANFIELD_H

const int NUM_CARDS = 52, NUM_SUITS = 4, NUM_RANKS = 13;
// The main loop of the game.
void canfield();

// Starting a new game. It must reset all the data structures,
// generate a new set of 52 random cards and place them in the
// appropriate places in the game.
void newGame();

// Empty all the data structures
void emptyAll();

// swap two integers
void swap(int &a, int &b);

// creates a new pack of cards and shuffles them
void newShuffledPack(int *newDeck);

// Prints the choices of actions for the player.
void printMenu();

// Performs an action based on the user's choice.
void performAction(char answer);

// Displays the entire content of the game.
void printGame();

// Deals one card from the deck.
void deal();

// Performs one move.
void move();

// Adds the card or the entire tableau to its new destination.
void addCard(int card);

// Checks if the proposed movement is possible.
bool checkMove(int card);

// Removes the card to be moved.
void removeCard();

// Determines what card is to be moved.
int getCard();

// Clears the terminal screen.
void clearScreen();

// Repeats player's last move
void repeatMove();

// Check to see if player won the game
int wonGame();

#endif
