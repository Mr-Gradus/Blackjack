#include <iostream>
#include <locale>
#include <string>
#include <vector>

using namespace std;

class Card {
public:
	enum suit {
		SPADES,
		HEARTS,
		DIAMONDS,
		CLUBS
	};
	enum rank {
		ACE = 1,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING,
	};

	Card(rank r = ACE, suit s = SPADES, bool ifu = true);

	/*
	ѕерегружаем оператор << чтобы отправл€ть объекты типа Card
	в стандартный поток вывода
	*/
	
	friend ostream& operator<< (ostream& os, const Card& aCard);

	int GetValue() const;

	void Flip();

private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};
	
Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu)
{}

int Card::GetValue() const
{
	int value = 0; //карта картинкой вниз
	if (m_IsFaceUp)
	{
		value = m_Rank; // значение карты соответственно пор€дку в списке enum rank,
		// а с этого пр€м кайфанул )) просто но эффективно, значение 10 дл€ дам, королей, вальтов
		if (value > 10)
		{
			value = 10;
		}
	}
	return value;
}
	void Card::Flip()
	{
		m_IsFaceUp = !(m_IsFaceUp); // интересно через сколько мес€цев/лет опыта такие решени€ сами приход€т в голову?

	}

	

class Hand {

};

class Deck : private Hand {

};

class GenericPlayer : private Hand {

};

class Player : private GenericPlayer {

};

class House : private GenericPlayer {

};

class Game {

};

int main()
{
	Card c("spades", 5, 0);
	c.flip();
	cout << c.flip() << endl;



	return 0;
}