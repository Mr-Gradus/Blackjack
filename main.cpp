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
		two = 2, // или картам до вальта не надо присваивать значени€?
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

	suit m_suit; //масть
	value m_rank;  //значение 
	bool m_faceUp;   // вверх или вниз рубашкой/лицом
public:
	Card(suit suit, value rank, bool face) : m_suit(suit), m_rank(rank), m_faceUp(face) {}
	

	
	void flip() {  
		m_faceUp != m_faceUp;
	}
	
	};

int getValue(int value) {
	value = 0;
	
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