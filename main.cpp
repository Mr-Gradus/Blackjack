#include <iostream>
#include <locale>
#include <string>

using namespace std;

class Card {
private:
	string m_suit; //масть
	int m_value;  //значение 
	bool m_face;   // вверх или вниз рубашкой/лицом
public:
	Card(string suit, int value, bool face) : m_suit(suit), m_value(value), m_face(face) {}
	
	enum class SuitType {
		spades,
		hearts,
		diamonds,
		clubs
	};

	enum class ValueType { 
		two, three, four, 
		five, six, seven,
		eight, nine, ten,
		jack, queen, king,
		ace
	};
	bool flip() {
		if ()
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




	return 0;
}