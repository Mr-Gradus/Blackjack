#include <iostream>
#include <locale>
#include <string>

using namespace std;

class Card {
private:
	enum suit  {
		spades,
		hearts,
		diamonds,
		clubs
	};
	enum value {
		two = 2, // ��� ������ �� ������ �� ���� ����������� ��������?
		three = 3,
		four = 4,
		five = 5,
		six = 6,
		seven = 7,
		eight = 8,
		nine = 9,
		ten = 10,
		jack = 10,
		queen = 10,
		king = 10,
		ace = 1
	};

	suit m_suit; //�����
	value m_rank;  //�������� 
	bool m_faceUp;   // ����� ��� ���� ��������/�����
public:
	Card(suit suit, value rank, bool face) : m_suit(suit), m_rank(rank), m_faceUp(face) {}
	

	
	bool flip(bool face) {  // �� ����� ���� ��� ������ ��� ������ ��������
		if (face == 0) {
			return true;
		}
		else
		return false;
	}
	
	};

int getValue(int v) {
	return v;
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
	c.flip(0);
	cout << c.flip(1) << endl;



	return 0;
}