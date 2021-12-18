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

	
Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {};
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

ostream& operator<<(ostream& os, const Card& aCard) // перегрузка << для отправки объектов типа Card в поток cout
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
	Hand() {};
	
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

class GenericPlayer : public Hand {
protected:
	string m_Name;
	
	friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
public:
	GenericPlayer(const string& name = "");

	virtual ~GenericPlayer() {};

	virtual bool IsHitting() const = 0; // реализовать в классах игрок/компьютер 

	bool IsBusted() const;

	void Bust() const; // объявляет перебор очков
};

GenericPlayer::GenericPlayer(const string& name) : m_Name(name){}

GenericPlayer::~GenericPlayer(){}

bool GenericPlayer::IsBusted() const
{
	return (GetTotal() > 21);
}

void  GenericPlayer::Bust() const
{
	cout << m_Name << " BUSTED." << endl;
}

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


class Player : public GenericPlayer {
public:
	Player(const string& name = "");

	virtual ~Player() {};

	virtual bool IsHitting() const override;  // брать ли еще  карты 
		
	void Win() const; //  игрок победил
	
	void Lose() const;  // игрок проиграл
	
	void Push() const; // ничья
};

Player::Player(const string& name) : GenericPlayer(name) {};

Player::~Player(){}

bool Player::IsHitting() const
{
	cout << m_Name << ", do you want a hit? (Y/N): ";
	char response;
	cin >> response;
	return (response == 'y' || response == 'Y');
}
void Player::Win() const
{
	cout << m_Name << " WINS." << endl;
}

void Player::Lose() const
{
	cout << m_Name << " LOSE." << endl;
}

void Player::Push() const
{
	cout << m_Name << " PUSH." << endl;
}

class House : public GenericPlayer {
public:
	House(const string& name = "House");

	virtual ~House();
	
	virtual bool IsHitting() const; // дилер продолжает брать карты или нет

	void FlipFirstCard(); // переворачивает первую карту

};

House::House(const string& name) : GenericPlayer(name){}

House::~House(){}

bool House::IsHitting() const // возврат true если <= 16 очков либо false
{
	return (GetTotal() <= 16);
}

void House::FlipFirstCard() 
{
	if (!(m_Cards.empty()))
	{
		m_Cards[0]->Flip();
	}
	else
	{
		cout << "No card to flip!" << endl;
	}
}

class Game {

};


int main()
{

	
	return 0;
}