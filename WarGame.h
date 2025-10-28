#ifndef WARGAME_H
#define WARGAME_H

#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>

class WarGame
{
private:
    struct Card 
    {
        int rank;
        Card(int r = 1) : rank(r) {}
    };

    deque<Card> deck;       // The main deck
    deque<Card> player1;    // Player 1's pile
    deque<Card> player2;    // Player 2's pile
    int cardsPerSuit;            // User-chosen number of cards per suit

    // ---- Helper functions ----

    // Preocondition: Gets user input for cardsPerSuit
    // Postcondition: fill deck with ranks 1...cardsPerSuit
    void createDeck()
    {
        deck.clear();
        for (int suit = 0; suit < 4; suit++)
        {
            for (int rank = 1; rank < cardsPerSuit; ++rank)
            {
                deck.push_back(Card(rank));
            }
        }
    } 

    // Precondition: Deck is full
    // Postcondition: Randomizes deck order
    void shuffleDeck()
    {
        srand(time(0));

        for (size_t i = 0; i < deck.size(); ++i)
        {
            size_t j = rand() % deck.size();
            swap(deck[i], deck[j]);
        }

    }

    // Precondition: Deck is full, deck is shuffled
    // Postcondition: Splits deck between players switching back and forth
    void dealCards()
    {
        shuffleDeck();
        bool toPlayer1 = true;
        while (!deck.empty())
        {
            if (toPlayer1)
            {
                player1.push_back(deck.front());
            }
            else 
            {
                player2.push_back(deck.front());
            }

            deck.pop_front();
            toPlayer1 = !toPlayer1;
        }
    }

    // Precondition: Deck is full, shuffled, and dealt to the players
    // Postcondition: Compares the card ranks of each players cards, 
    // gives spoils to winner; if there's a tie, call resolveWar 
    void playRound()
    {
        deque<Card> spoils;
            Card card1 = player1.front();
            player1.pop_front();

            Card card2 = player2.front();
            player2.pop_front();

            spoils.push_back(card1);
            spoils.push_back(card2);

            cout << "\n\tPlayer1: " << card1.rank << " | Player2: " << card2.rank; 
            if (card1.rank > card2.rank)
            {
                cout << "\n\tPlayer1 wins!";
                for (Card c : spoils)
                {
                    player1.push_back(c);
                }
                spoils.clear();
                cin.get();
            }

            else if (card1.rank < card2.rank)
            {
                cout << "\n\tPlayer2 wins!";
                for (Card c : spoils)
                {
                    player2.push_back(c);
                }
                spoils.clear();
                cin.get();
            }

            else
            {
                cout << "\n\tWar!";
                resolveWar(spoils);
                cin.get();
            }

        }

    

    // Precondition: There is a tie in playRound
    // Postcondition: Resolves the tie, uses 4th card to resolve tie,
    // if one player runs out of cards, player with cards wins,
    // if there is another tie call resolveWar
    void resolveWar(deque<Card>& spoils)
    {
        // If either player has less than 4 cards, they lose automatically
        if (player1.size() < 4)
        {
            cout << "\n\tPlayer 1 cannot continue war - Player 2 wins all spoils!";
            while (!player1.empty()) 
            { 
                spoils.push_back(player1.front()); player1.pop_front(); 
            }
            for (Card c : spoils) player2.push_back(c);
            return;
        }
        if (player2.size() < 4)
        {
            cout << "\n\tPlayer 2 cannot continue war - Player 1 wins all spoils!";
            while (!player2.empty()) 
            { 
                spoils.push_back(player2.front()); player2.pop_front(); 
            }
            for (Card c : spoils) player1.push_back(c);
            return;
        }

        // Draw 3 face-down cards
        for (int i = 0; i < 3; ++i) 
        {
            spoils.push_back(player1.front()); player1.pop_front();
            spoils.push_back(player2.front()); player2.pop_front();
        }

        // Draw the 4th face-up card
        Card warCard1 = player1.front(); player1.pop_front();
        Card warCard2 = player2.front(); player2.pop_front();
        spoils.push_back(warCard1);
        spoils.push_back(warCard2);

        cout << "\n\tWar cards: Player1 " << warCard1.rank << " | Player2 " << warCard2.rank;

        if (warCard1.rank > warCard2.rank)
        {
            cout << "\n\tPlayer1 wins the war!";
            for (Card c : spoils) player1.push_back(c);
        }
        else if (warCard1.rank < warCard2.rank)
        {
            cout << "\n\tPlayer2 wins the war!";
            for (Card c : spoils) player2.push_back(c);
        }
        else
        {
            cout << "\n\tAnother tie! Continuing war...";
            resolveWar(spoils); // call recursively
        }

    }

public:

    // Constructor
    WarGame(int cardsPerSuit)
    {
        this->cardsPerSuit = cardsPerSuit;

        createDeck();   // Fill the deck with cards
        dealCards();
    }

    // Run the game
    void play()
    {
        while (!player1.empty() && !player2.empty())
        {
            playRound();
        }

        cout << "\n\n===== GAME OVER =====\n";
        if (player1.empty() && player2.empty())
            cout << "It's a draw!\n";
        else if (player1.empty())
            cout << "Player 2 wins the game!\n";
        else
            cout << "Player 1 wins the game!\n";
    }
};

#endif
