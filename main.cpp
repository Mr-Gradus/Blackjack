#include <iostream>
#include <locale>
#include <string>

using namespace std;

class Card {
private:
	string m_suit; //�����
	int m_value;  //�������� 
	bool m_face;   // ����� ��� ���� ��������/�����
public:
	Card(string suit, int value, bool face) : m_suit(suit), m_value(value), m_face(face) {}
	
	enum class SuitType {
		spades,
		hearts,
		diamonds,
		clubs
	};

	enum class ValueType { 
		two = 2, // ��� ������ �� ������ �� ���� ����������� ��������?
		three =3,
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
	Card c("clubs", 5, 0);
	c.flip(0);
	cout << c.flip(1) << endl;



	return 0;
}