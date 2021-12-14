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
	Перегружаем оператор << чтобы отправлять объекты типа Card
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
		value = m_Rank; // значение карты соответственно порядку в списке enum rank,
		// а с этого прям кайфанул )) просто но эффективно, значение 10 для дам, королей, вальтов
		if (value > 10)
		{
			value = 10;
		}
	}
	return value;
}
	void Card::Flip()
	{
		m_IsFaceUp = !(m_IsFaceUp); // интересно через сколько месяцев/лет опыта такие решения сами приходят в голову?

	}

	

class Hand {
public:
	Hand();
	virtual ~Hand(); // виртуальный деструктор

	void Add(Card* pCard); // добавляет карту в руку

	void Clear(); // очищает руку от карт

	int GetTotal() const; // получаем сумму карт на руках, присваивая тузу 1 или 11 

protected:
	vector<Card*> m_Cards;
};

Hand::Hand()
{
	m_Cards.reserve(7);
}

Hand::~Hand() // по прежнему виртуальный деструктор
{
	Clear();
}

void Hand::Add(Card* pCard)
{
	m_Cards.push_back(pCard);
}

void Hand::Clear() //проходит по вектору освобождая всю память в куче
{
	vector<Card*>::iterator iter = m_Cards.begin();
	for (; iter != m_Cards.end(); ++iter)
	{
		Card* card = *iter;
		delete card;
		*iter = nullptr;
	}
	m_Cards.clear(); // очистка вектора указателей
}

int Hand::GetTotal() const
{
	if (m_Cards.empty()) // если в руке нет карт возвращаем 0
	{
		return 0;
	}

	if (m_Cards[0]->GetValue() == 0) //если первая карта со значением 0 то она рубашкой вверх, возврат 0
	{
		return 0;
	}

	int total = 0; // находим сумму очков карт в руке при туз = 1
	vector<Card*>::const_iterator iter;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		total += (*iter)->GetValue();
	}

	bool containsAce = false; // определяем есть ли туз в руке
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		if ((*iter)->GetValue() == Card::ACE)
		{
			containsAce = true;
		}
	}

	if (containsAce && total <= 11) // если есть туз и сумма меньше 12 туз дает 11 очков
	{
		total += 10; // очки только за один туз, даже если их в руке больше
	}

	return total;
}









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

	
	return 0;
}