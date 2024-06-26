/* 7.12
 * This program will modify Fig 7.16 so that the card-dealing function deals a five-card poker hand. The
 * program will contain functions to determine whether the hand contains a pair, two pairs, three of a kind,
 * four of a kind, a flush, or a straight then display the hand and the results */

// fig07_16.c
// Card shuffling and dealing.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HAND_SIZE 5
#define SUITS 4
#define FACES 13
#define CARDS 52

// function prototypes
void shuffle(int deck[][FACES]);
void deal(int deck[][FACES], const char *face[], const char *suit[], char *faces[], char *suits[]);
int pair(char *faces[]);
int twoPairs(char *faces[]);
int threeKind(char *faces[]);
int fourKind(char *faces[]);
int flush(char *suits[]);
int straight(char *faces[]);


int main(void) {
    // initialize deck array
    int deck[SUITS][FACES] = {0};

    char *faces[5];
    char *suits[5];

    srand(time(NULL)); // seed random-number generator
    shuffle(deck); // shuffle the deck

    // initialize suit array
    const char *suit[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};

    // initialize face array
    const char *face[FACES] = {"Ace", "Deuce", "Three", "Four", "Five",
                               "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

    deal(deck, face, suit, faces, suits); // deal the deck

    // function calls
    if (pair(faces)) {
        puts("\nPair found.");
    }
    if (twoPairs(faces)) {
        puts("Two pairs found.");
    }
    if (threeKind(faces)) {
        puts("Three of a kind found.");
    }
    if (fourKind(faces)) {
        puts("Four of a kind found.");
    }
    if (flush(suits)) {
        puts("Flush found.");
    }
    if (straight(faces)) {
        puts("\nStraight found.");
    }
}  // end main

// shuffle cards in deck
void shuffle(int deck[][FACES]) {
    // for each of the cards, choose slot of deck randomly
    for (size_t card = 1; card <= CARDS; ++card) {
        size_t row = 0; // row number
        size_t column = 0; // column number

        // choose new random location until unoccupied slot found
        do {
            row = rand() % SUITS;
            column = rand() % FACES;
        } while(deck[row][column] != 0);

        deck[row][column] = card; // place card number in chosen slot
    }
}

// deal cards in deck
void deal(int deck[][FACES], const char *face[], const char *suit[], char *faces[], char *suits[]) {
    // deal each of the 5 cards
    for (size_t card = 1; card <= 5; ++card) {
        // loop through rows of deck
        for (size_t row = 0; row < SUITS; ++row) {
            // loop through columns of deck for current row
            for (size_t column = 0; column < FACES; ++column) {
                // if slot contains current card, display card
                if (deck[row][column] == card) {
                    faces[card - 1] = face[column];  // set first elements of faces to first face in deck
                    suits[card - 1] = suit[row];  // set first element of suits to first suit in deck
                    printf("%s of %s  ", faces[card - 1], suits[card -1]);  // display hand
                }
            }
        }
    }
}

// function to check if hand contains a pair
int pair(char *faces[]) {

    // for loop to iterate through hand and compare faces
    for (size_t i = 0; i < HAND_SIZE - 1; ++i) {
        for (size_t j = i + 1; j < HAND_SIZE; ++j) {
            // see if two cards are equal to each other
            if (faces[i] == faces[j]) {
                return 1;  // return true if pair is found
            }
        }
    }
    return 0;
}

int twoPairs(char *faces[]) {

    // array to keep track of pairs
    char pairedValues[HAND_SIZE] = {0};

    // pairs counter to count instances of duplicates
    int count = 0;

    // for loop to iterate through hand and compare faces
    for (size_t i = 0; i < HAND_SIZE; ++i) {
        for (size_t j = i + 1; j < HAND_SIZE; ++j) {
            if (faces[i] == faces[j] && !pairedValues[i]) {

                pairedValues[i] = 1;  // store 1 if pair value is found
                count++;

                if (count == 2) {  // if count is 2, return true
                    return 1;
                }
            }
        }
    }
    return 0;
}

// function to check if hand has 3 of a kind
int threeKind(char *faces[]) {

    // variable to count duplicates
    int count = 0;

    // for loop to iterate through hand and compare faces
    for (size_t i = 0; i < HAND_SIZE - 1; ++i) {
        for (size_t j = i + 1; j < HAND_SIZE; ++j) {
            // compare the face values
            if (faces[i] == faces[j]) {
                count++;  // increment count if duplicate is found
            }
        }
        if (count >= 3) {  // if count at least 3, return true
            return 1;
        }
    }
    return 0;
}

// function to check if hand has four of a kind
int fourKind(char *faces[]) {

    // variable to count duplicates
    int count = 0;

    // for loop to iterate through hand and compare faces
    for (size_t i = 0; i < HAND_SIZE - 1; ++i) {
        for (size_t j = i + 1; j < HAND_SIZE; ++j) {
            // compare the face values
            if (faces[i] == faces[j]) {
                count++;  // increment count if duplicate is found
            }
        }
        if (count == 4) {  // if count is 4, return true
            return 1;
        }
    }
    return 0;
}

// function to check if hand has flush (all 5 the same suit)
int flush(char *suits[]) {

    // variable to count duplicates
    int count = 0;

    // iterate through hand and compare suits
    for (size_t i = 0; i < HAND_SIZE; ++i) {
        if (suits[i] == suits[0]) {
            count++;  // increment count when duplicate is found
        }
        if (count == 5) {  // when 5 of a kind is found, return true
            return 1;
        }
    }
    return 0;
}

// function to check if hand has 5 cards that are consecutive face values (straight)
int straight(char *faces[]) {

    // loop through hand to check for consecutive cards
    for (size_t i = 0; i < HAND_SIZE - 1; ++i) {
        for (size_t j = i + 1; j < HAND_SIZE; ++j) {
            if (faces[i][0] > faces[j][0]) {
                // store greater value in temp variable
                char *temp = faces[i];
                // swap values to sort cards
                faces[i] = faces[j];
                faces[j] = temp;
            }
        }
        for (size_t i = 0; i < HAND_SIZE - 1; ++i) {
            // if the difference between each sorted face is not 1, cards are consecutive (return false)
            if (faces[i + 1][0] - faces[i][0] != 1) {
                return 0;
            }
        }
    }
    return 1;  // return true if cards are consecutive
}
