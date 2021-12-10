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
	
Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu)
{}

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