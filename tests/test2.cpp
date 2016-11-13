// Blackjack
// Plays a simple version of the casino gamr of blackjack; for 1-7 players

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

// --------------------------------------- CARD CLASS

class Card
{
public:
    // rank of card
    enum rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

    // card type
    enum suit {CLUBS, DIAMONDS, HEARTS, SPADES};

    // overloading << operator so we can send Card object to standard output
    friend ostream &operator<<(ostream &os, const Card &aCard);

    // constructor
    Card(rank r = ACE, suit s = SPADES, bool ifu = true);
    
    // returns the value of a card, 1 - 11
    int GetValue() const;

    // flips a card; if face up, becomes face down and vice versa
    void Flip();

private:
    // rank
    rank m_Rank;

    // type
    suit m_Suit;

    // Is Face Up
    bool m_IsFaceUp;
};

// Constructor
Card::Card(rank r, suit s, bool ifu): m_Rank(r), m_Suit(s), m_IsFaceUp(ifu)
{ }

// returns value of card
int Card::GetValue() const
{
    // if a card is face down, its value is 0
    int value = 0;
    if(m_IsFaceUp)
    {
        // value is number showing on card
        value = m_Rank;

        // value is 10 for face cards
        if(value > 10)
        {
            value = 10;
        }
    }
    return value;
}

// flips a card
void Card::Flip()
{
    m_IsFaceUp = !(m_IsFaceUp);
}

// --------------------------------------- HAND CLASS

class Hand
{
public:
    // constructor
    Hand();

    // destructor
    virtual ~Hand();

    // adds a card to the hand vector
    void Add(Card *pCard);

    // clears hand vector of all cards
    void Clear();

    // gets hand total value, intelligently treats aces as 1 or 11
    int GetTotal() const;

protected:
    // collection of cards. stores pointers to card objects
    vector<Card*> m_Cards;
};

// constructor
Hand::Hand()
{
    m_Cards.reserve(7);
}

// destructor
Hand::~Hand()
{
    Clear();
}

// clears hand of cards
void Hand::Clear()
{
    // iterate through vector, freeing all memory on the heap
    vector<Card*>::iterator iter = m_Cards.begin();
    for(iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        delete *iter;
        *iter = 0;
    }

    // clear vector of pointers
    m_Cards.clear();
}

// gets the total value of the hand
int Hand::GetTotal() const
{
    // if no cards in hand, return 0
    if(m_Cards.empty())
    {
        return 0;
    }

    // if a first card has a value of 0, then card is face down; return 0
    if(m_Cards[0]->GetValue() == 0)
    {
        return 0;
    }

    // add up card values, treat each ace as 1
    int total = 0;
    vector<Card*>::const_iterator iter;
    for(iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        total += (*iter)->GetValue();
    }

    // determine if hand contains an ace
    bool containsAce = false;
    for(iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        if((*iter)->GetValue() == Card::ACE)
        {
            containsAce = true;
        }
    }

    // if hand contains ace and total is low enough, treat ace as 11
    if(containsAce && total <= 11)
    {
        // and only 10 since we've already added 1 for the ace
        total += 10;
    }

    return total;
}

// --------------------------------------- GENERIC PLAYER CLASS

class GenericPlayer : public Hand
{
    // << operator overloader
    friend ostream &operator<<(ostream &os, const GenericPlayer &aGenericPlayer);

public:
    // constructor
    GenericPlayer(const string &name = "");

    // destructor
    virtual ~GenericPlayer();

    // indicates whether or not generic player wants to keep hitting
    virtual bool IsHitting() const = 0;

    // returns whether generic player has busted - has a total greater than 21
    bool IsBusted() const;

    // announces that the generic player busts
    void Bust() const;

protected:
    // generic players name
    string m_Name;
};

// constructor
GenericPlayer::GenericPlayer(const string &name) :
    m_Name(name)
{ }

// destructor
GenericPlayer::~GenericPlayer()
{ }

// is busted? function
bool GenericPlayer::IsBusted() const
{
    return (GetTotal() > 21);
}

// announces bust player function
void GenericPlayer::Bust() const
{
    cout << m_Name << " busts.\n";
}

// --------------------------------------- PLAYER CLASS

class Player : public GenericPlayer
{
public:

    // constructor
    Player(const string &name = "");

    // destructor
    virtual ~Player();

    // returns whether or not player wants another hit
    virtual bool IsHitting() const;

    // announces that the player wins
    void Win() const;

    // announces that the player loses
    void Lose() const;

    // announces that the player pushes
    void Push() const;
};

// constructor
Player::Player(const string &name):
    GenericPlayer(name)
{ }

// destructor
Player::~Player()
{ }

// is player wanting another hit? function
bool Player::IsHitting() const
{
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

// player wins function
void Player::Win() const
{
    cout << m_Name << " wins.\n";
}

// player loses function
void Player::Lose() const
{
    cout << m_Name << " loses.\n";
}

// player pushes function
void Player::Push() const
{
    cout << m_Name << " pushes.\n";
}

// --------------------------------------- HOUSE CLASS

class House : public GenericPlayer
{
public:
    //constructor
    House(const string &name = "House");

    // destructor
    virtual ~House();

    // indicates whether house is hitting - will always hit on 16 or less
    virtual bool IsHitting() const;

    // flips first card
    void FlipFirstCard();
};

// constructor
House::House(const string &name):
GenericPlayer(name)
{ }

// destructor
House::~House()
{ }

// is house hitting? function

bool House::IsHitting() const
{
    return (GetTotal() <= 16);
}

// flip first card function
void House::FlipFirstCard()
{
    if(!(m_Cards.empty()))
    {
        m_Cards[0]->Flip();
    }
    else
    {
        cout << "No card to flip!\n";
    }
}

// --------------------------------------- DECK CLASS

class Deck : public Hand
{
public:
    // constructor
    Deck();

    //destructor
    virtual ~Deck();

    // create a standard deck of 52 cards
    void Populate();

    // shuffle cards
    void Shuffle();

    //deal one card to a hand
    void Deal(Hand &aHand);

    // give additional cards to a generic player
    void AdditionalCards(GenericPlayer &aGenericPlayer);
};

// constructor
Deck::Deck()
{
    m_Cards.reserve(52);
    Populate();
}

// destructor
Deck::~Deck()
{ }

// deck population function
void Deck::Populate()
{
    Clear();
    // create standard deck
    // loops through all possible combinations of Card::suit and Card::rank values.
    // it uses static_cast to cast the int loop variables to the proper enumerated types defined in card
    for(int s = Card::CLUBS; s <= Card::SPADES; ++s)
    {
        for(int r = Card::ACE; r <= Card::KING; ++r)
        {
            Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
        }
    }
}

// deck shuffle function
void Deck::Shuffle()
{
    // randomly rearranges the pointers in m_Cards with random_shuffle() from the STL.
    random_shuffle(m_Cards.begin(), m_Cards.end());
}

// deal a card to the player's hand function
void Deck::Deal(Hand &aHand)
{
    // adds a copy of the pointer to the back of m_Cards to the object through the object's Add() member function
    // then it removes the pointer  at the back of m_Cards, effectively transferring the card.
    // the powerful thing about Deal() is that it accepts a reference to a Hand object, and through polymorphism, Deal() can call the object's Add() member function without knowing the type.
    if(!m_Cards.empty())
    {
        aHand.Add(m_Cards.back());
        m_Cards.pop_back();
    }
    else
    {
        cout << "Out of cards. Unable to deal.";
    }
}

// deal additional cards function
void Deck::AdditionalCards(GenericPlayer &aGenericPlayer)
{
    cout << endl;

    //continue to deal a card as long as generic player isn't busted and wants another hit
    // the member function accepts reference to a GenericPlayer object so you can pass a Player or House object to it.
    // can call functions from the House and Player classes
    while(!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
    {
        Deal(aGenericPlayer);
        cout << aGenericPlayer << endl;

        if(aGenericPlayer.IsBusted())
        {
            aGenericPlayer.Bust();
        }
    }
}

// --------------------------------------- GAME CLASS

class Game
{
public:
    //constructor
    Game(const vector<string> &names);

    //destructor
    ~Game();

    // plays the game of blackjack
    void Play();

private:
    // deck data member
    Deck m_Deck;

    // house data member
    House m_House;

    // storing number of players in a vector
    vector<Player> m_Players;
};

// constructor
Game::Game(const vector<string> &names)
{
    // create a vector of players from a vector of names
    vector<string>::const_iterator pName;
    for(pName = names.begin(); pName != names.end(); ++pName)
    {
        m_Players.push_back(Player(*pName));
    }

    // seed the random number generator
    srand(static_cast<unsigned int>(time(0)));
    m_Deck.Populate();
    m_Deck.Shuffle();
}

// destructor
Game::~Game()
{ }

// Play a game of blackjack function
void Game::Play()
{
    // deal initial 2 cards to everyone
    vector<Player>::iterator pPlayer;
    for(int i = 0; i < 2; ++i)
    {
        for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.Deal(*pPlayer);
        }
        m_Deck.Deal(m_House);
    }

    // hide house's first card
    m_House.FlipFirstCard();

    // display everyone's hand
    for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        cout << *pPlayer << endl;
    }
    cout << m_House << endl;

    // deal additional cards to players
    for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        m_Deck.AdditionalCards(*pPlayer);
    }

    // reveal house's first hand
    m_House.FlipFirstCard();
    cout << endl << m_House;

    // deal additional cards to house
    m_Deck.AdditionalCards(m_House);

    if(m_House.IsBusted())
    {
        // everyone still playing wins
        for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            if(!(pPlayer->IsBusted()))
            {
                pPlayer->Win();
            }
        }
    }
    else
    {
        // compare each player still playing to house
        for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            if(!(pPlayer->IsBusted()))
            {
                if(pPlayer->GetTotal() > m_House.GetTotal())
                {
                    pPlayer->Win();
                }
                else if(pPlayer->GetTotal() < m_House.GetTotal())
                {
                    pPlayer->Lose();
                }
                else
                {
                    pPlayer->Push();
                }
            }
        }
    }

    // remove everyone's cards

    for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        pPlayer->Clear();
    }
    m_House.Clear();
}

// --------------------------------------- OPERATOR OVERLOADING FUNCTIONS

// overloads << operator so Card object can be sent to cout
ostream &operator<<(ostream &os, const Card &aCard)
{
    const string RANKS[] = {"0", "A","2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    const string SUITS[] = {"c", "d", "h","s"};

    if(aCard.m_IsFaceUp)
    {
        os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
    }
    else
    {
        os << "XX";
    }

    return os;
}

// overloads << operator so a GenericPlayer object can be sent to cout
ostream &operator<<(ostream &os, const GenericPlayer &aGenericPlayer)
{
    os << aGenericPlayer.m_Name << ":\t";

    vector<Card*>::const_iterator pCard;
    if(!aGenericPlayer.m_Cards.empty())
    {
        for(pCard = aGenericPlayer.m_Cards.begin(); pCard != aGenericPlayer.m_Cards.end(); ++pCard)
        {
            os << *(*pCard) << "\t";
        }

        if(aGenericPlayer.GetTotal() != 0)
        {
            cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else
    {
        os << "<empty>";
    }
    return os;
}

int main()
{
    cout << "\t\tWelcome to Blackjack\n\n";

    int numPlayers = 0;
    while(numPlayers < 1 || numPlayers > 7)
    {
        cout << "How many players? (1 - 7): ";
        cin >> numPlayers;
    }

    vector<string> names;
    string name;
    for(int i = 0; i < numPlayers; ++i)
    {
        cout << "Enter player name: ";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;

    // the game loop
    Game aGame(names);
    char again = 'y';
    while(again != 'n' && again != 'N')
    {
        aGame.Play();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> again;
    }

    return 0;

}