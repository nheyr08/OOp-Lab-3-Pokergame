
#include "PokerGame.h" 
#include <algorithm>

void PokerGame::Distribute(bool usedCards[52])
{
	int temp;
	// Random generate ﬁve cards to player 
	for (int i = 0; i < 5; i++) 
	{
	temp = rand() % 52;       
	if (usedCards[temp])
	{
	// card is already distributed 
		i--;
	}
  else
    {
 // add cardd to player's hand 
	Pcards.push_back(temp);
    }
  }
}

void PokerGame::set(vector<int>& cards)
{
	// Set the cards to player
	for (int i = 0; i < cards.size(); i++) {
		Pcards.push_back(cards.at(i));
	}
}

void PokerGame::printCards()
{
	string cards[52] = { "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "CJ", "CQ", "CK",
	"D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10", "DJ", "DQ", "DK",
		"H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "H10", "HJ", "HQ", "HK",
		"S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "S10", "SJ", "SQ", "SK"
};

cout << "Player cards: "; 
for (int i = 0; i < 5; i++)
{
	// Print the player's cards.

	cout << cards[Pcards.at(i)] << " ";
}
cout << endl;

}

void PokerGame::sortCards()
{
	sort(Pcards.begin(), Pcards.end());
}

void PokerGame::evaluate()
{
	sortCards();
	if (this->isStraight() && this->isFlush())
	{
		Type = StraightFlush;
	}
	else if (this->isFourOfaKind())
	{
		Type = FourOfaKind;
	}
	else if (this->isFullHouse())
	{
		Type = FullHouse;
	}
	else if (this->isFlush())
	{
		Type = Flush;
	}
	else if (this->isStraight())
	{
		Type = Straight;
	}
	else if (this->isThreeOfaKind())
	{
		Type = ThreeOfaKind;
	}
	else if (this->isTwoPairs())
	{
		Type = TwoPairs;

	}
	else if (this->isOnePair())
	{
		Type = OnePair;
	}
	else
	{
		Type = Highcard;
	}
}

int PokerGame::getType()
{
	return Type;
}

void PokerGame::compare(int type)
{

	// player with higher card type is winner
	if (this->Type > type) {
	cout << "Player 1 is the Winner!" << endl;
}
else if (this->Type < type) {
cout << "Player 2 is the Winner!" << endl;
}
else {
// both player have same card type
		cout << "\nIts a draw folks!!\n";
  }
}

bool PokerGame::isStraight()
{int first = Pcards.at(0)%13;
	// check remaining cards 
	for (int i = 1; i < 5; i++) 
   { 
    if (first > (Pcards.at(i) % 13)) 
	{
	 first = Pcards.at(i) % 13;
   }
}
bool isNextFound = false;    // if next card with face value i higher than ﬁrst card found
for (int i = 1; i < 5; i++) {
isNextFound = false; for (int j = 0; j < 5; j++) {
	int next = (Pcards.at(j) % 13) - i; if (first == next) {
		isNextFound = true; break;
	}
}
// in all cards if next straight value not found, return false
if (!isNextFound) {
return false;
}
}
return isNextFound;
}

bool PokerGame::isFlush()
{
	// Check whether the hand of cards is Flush or not
	
	int suit = Pcards.at(0) / 13;
	// check suit of remaining cards 
	for (int i = 1; i < 5; i++) {
	if (suit != (Pcards.at(i) / 13)) {
		// card with different suit is found 
		return false;
	}
}
// all cards are checked and have same suit 
	return true;
}

bool PokerGame::isFourOfaKind()
{
	// Check whether the hand of cards is FourOfaKind or not
	
	int occurance[13] = { 0 }; // initialize all cards as no occurance
	// check all 5 cards

	for (int i = 0; i < 5; i++) {
		// put cards in occurance 
		occurance[(Pcards.at(i) % 13)]++;
	}
	// now check all occurance if any occurance is 4 return true
		for (int i = 0; i < 13; i++) {
	if (occurance[i] == 4) {
		return true;
	}
}
// no occurance of 4 found 
		return false;
}

bool PokerGame::isFullHouse()
{
	// Check whether the hand of cards is FullHouse or not
	// if player have both three of a kind and one pair its full house 
	if (isThreeOfaKind() && isOnePair()) {
	return true;
}
return false;
}

bool PokerGame::isThreeOfaKind()
{
	int occurance[13] = { 0 }; 
	for (int i = 0; i < 5; i++) {
	occurance[(Pcards.at(i) % 13)]++;
	}
	for (int i = 0; i < 13; i++) {
	if (occurance[i] == 3) {
		return true;
	}
}
// no occurance of 3 found 
	return false;
}

bool PokerGame::isTwoPairs()
{
// Check whether the hand of cards is TwoPairs or not 
	int pairs = 0;
	
	int occurance[13] = { 0 };
	
	for (int i = 0; i < 5; i++) {
		// put cards in occurance 
		occurance[(Pcards.at(i) % 13)]++;
	}
	// check all occurances if any is 2 add a pair
	for (int i = 0; i < 13; i++) {
	if (occurance[i] == 2) {
		pairs++;
	}
}
// check for two pairs 
	if (pairs == 2) {
return true;
}
return false;
}

bool PokerGame::isOnePair()
{
	int occurance[13] = { 0 }; 
	for (int i = 0; i < 5; i++) {
		// put cards in occurance
		occurance[(Pcards.at(i) % 13)]++;
	}
	//check all occurance if any is 2 return true
	for (int i = 0; i < 13; i++) {
	if (occurance[i] == 2) {
		return true;
	}
}
// no occurance of 2 found
	return false;
}
