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

	ostream& operator<<(ostream& os, const Card& aCard) // перегрузка << дл€ отправки объектов типа Card в поток cout
	{
		const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
		const string SUITS[] = { "s", "h", "d", "c" };

		if (aCard.m_IsFaceUp)
		{
			os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
		}
		else
		{
			os << "XX";
		}

		return os;
	};

class Hand {
public:
	Hand();
	virtual ~Hand(); // виртуальный деструктор

	void Add(Card* pCard); // добавл€ет карту в руку

	void Clear(); // очищает руку от карт

	int GetTotal() const; // получаем сумму карт на руках, присваива€ тузу 1 или 11 

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

void Hand::Clear() //проходит по вектору освобожда€ всю пам€ть в куче
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

	if (m_Cards[0]->GetValue() == 0) //если перва€ карта со значением 0 то она рубашкой вверх, возврат 0
	{
		return 0;
	}

	int total = 0; // находим сумму очков карт в руке при туз = 1
	vector<Card*>::const_iterator iter;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		total += (*iter)->GetValue();
	}

	bool containsAce = false; // определ€ем есть ли туз в руке
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
protected:
	string m_Name;
	
	friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
public:
	GenericPlayer(const string& name = "") : m_Name(name) {};

	virtual ~GenericPlayer() {};

	virtual bool IsHitting() const = 0; // реализовать в классах игрок/компьютер 

	bool IsBusted() const;
	{
		return (GetTotal() > 21);
	}

	void Bust() const; // объ€вл€ет перебор очков
	{
		cout << m_Name << " BUSTED.\n";
	}

	
};

ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer)
{
	os << aGenericPlayer.m_Name << ":\t";

	vector<Card*>::const_iterator pCard;
	if (!aGenericPlayer.m_Cards.empty())
	{
		for (pCard = aGenericPlayer.m_Cards.begin();
			pCard != aGenericPlayer.m_Cards.end();
			++pCard)
		{
			os << *(*pCard) << "\t";
		}


		if (aGenericPlayer.GetTotal() != 0)
		{
			cout << "(" << aGenericPlayer.GetTotal() << ")";
		}
	}
	else
	{
		os << "<empty>";
	}

	return os;
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