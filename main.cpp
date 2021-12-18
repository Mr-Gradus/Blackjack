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
	����������� �������� << ����� ���������� ������� ���� Card
	� ����������� ����� ������
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
	int value = 0; //����� ��������� ����
	if (m_IsFaceUp)
	{
		value = m_Rank; // �������� ����� �������������� ������� � ������ enum rank,
		// � � ����� ���� �������� )) ������ �� ����������, �������� 10 ��� ���, �������, �������
		if (value > 10)
		{
			value = 10;
		}
	}
	return value;
}
void Card::Flip()
	{
		m_IsFaceUp = !(m_IsFaceUp); // ��������� ����� ������� �������/��� ����� ����� ������� ���� �������� � ������?

	}

ostream& operator<<(ostream& os, const Card& aCard) // ���������� << ��� �������� �������� ���� Card � ����� cout
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
	
	virtual ~Hand(); // ����������� ����������

	void Add(Card* pCard); // ��������� ����� � ����

	void Clear(); // ������� ���� �� ����

	int GetTotal() const; // �������� ����� ���� �� �����, ���������� ���� 1 ��� 11 
	
protected:
	vector<Card*> m_Cards;
};

Hand::Hand()
{
	m_Cards.reserve(7);
}

Hand::~Hand() // �� �������� ����������� ����������
{
	Clear();
}

void Hand::Add(Card* pCard)
{
	m_Cards.push_back(pCard);
}

void Hand::Clear() //�������� �� ������� ���������� ��� ������ � ����
{
	vector<Card*>::iterator iter = m_Cards.begin();
	for (; iter != m_Cards.end(); ++iter)
	{
		Card* card = *iter;
		delete card;
		*iter = nullptr;
	}
	m_Cards.clear(); // ������� ������� ����������
}

int Hand::GetTotal() const
{
	if (m_Cards.empty()) // ���� � ���� ��� ���� ���������� 0
	{
		return 0;
	}

	if (m_Cards[0]->GetValue() == 0) //���� ������ ����� �� ��������� 0 �� ��� �������� �����, ������� 0
	{
		return 0;
	}

	int total = 0; // ������� ����� ����� ���� � ���� ��� ��� = 1
	vector<Card*>::const_iterator iter;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		total += (*iter)->GetValue();
	}

	bool containsAce = false; // ���������� ���� �� ��� � ����
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		if ((*iter)->GetValue() == Card::ACE)
		{
			containsAce = true;
		}
	}

	if (containsAce && total <= 11) // ���� ���� ��� � ����� ������ 12 ��� ���� 11 �����
	{
		total += 10; // ���� ������ �� ���� ���, ���� ���� �� � ���� ������
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

	virtual bool IsHitting() const = 0; // ����������� � ������� �����/��������� 

	bool IsBusted() const;

	void Bust() const; // ��������� ������� �����
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

	virtual bool IsHitting() const override;  // ����� �� ���  ����� 
		
	void Win() const; //  ����� �������
	
	void Lose() const;  // ����� ��������
	
	void Push() const; // �����
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
	
	virtual bool IsHitting() const; // ����� ���������� ����� ����� ��� ���

	void FlipFirstCard(); // �������������� ������ �����

};

House::House(const string& name) : GenericPlayer(name){}

House::~House(){}

bool House::IsHitting() const // ������� true ���� <= 16 ����� ���� false
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