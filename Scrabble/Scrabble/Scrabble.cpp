#include <iostream>
#include <fstream>
#include <random>
using namespace std;
unsigned constexpr SIZE = 100;
//String management
int strLen(const char* str) {
	if (!str)
		return 0;

	int count = 0;
	while (*str) {
		count++;
		str++;
	}
	return count;
}
bool checkIfTwoStringsAreTheSame(const char* wordOne, const char* wordTwo) {
	if (!wordOne || !wordTwo)
		return false;

	if (strLen(wordOne) != strLen(wordTwo))
		return false;

	while (*wordOne && *wordTwo) {
		if (*wordOne != *wordTwo)
			return false;
		wordOne++;
		wordTwo++;
	}
	return true;

}
int strToNumber(const char* str) {
	if (!str)
		return false;

	int number = 0;
	while (*str) {
		number = number * 10 + (*str - '0');
		str++;
	}
	return number;

}
bool checkIfContainsLetter(const char ch, const char* letters) {
	if (!letters)
		return false;

	while (*letters)
	{
		if (*letters == ch)
			return true;
		letters++;
	}
	return false;
}
bool checkIfWordContainsLettersGiven(const char* letters, const char* word) {

	if (!letters || !word)
		return false;
	while (*word)
	{
		if (!checkIfContainsLetter(*word, letters))
			return false;
		word++;
	}
	return true;
}
//Char management
bool isNumber(const char* str) {
	if (!str)
		return false;
	while (*str) {
		if (*str < '0' || *str > '9')
			return false;
		str++;
	}
	return true;

}
char numberToSymbol(const int num) {
	return num;
}
char getVowel(const int num) {
	switch (num)
	{
	case 1: return 'a';
	case 2: return 'e';
	case 3: return 'i';
	case 4: return 'o';
	case 5: return 'u';
	case 6: return 'y';
	}
}
//Print function
void printMenu() {
	cout << "Choose number:" << std::endl
		<< "1. Start game" << std::endl
		<< "2. Settings" << std::endl
		<< "   a. Change letter count" << std::endl
		<< "   b. Change round count" << std::endl
		<< "3. Entering a new word" << std::endl
		<< "4. Exit" << endl;
}
//Working with files
bool checkForWord(const char* word) {
	fstream file("C:\\Users\\Adi\\Desktop\\FMI\\Introduction to programming Practicum\\Scrabble\\Scrabble\\Dictionary.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		cout << "Error opening dictionary: " << endl;
		return false;
	}

	char line[100];

	while (file >> line) {
		if (checkIfTwoStringsAreTheSame(line, word))
			return true;
	}
	return false;
}
void enterWord(const char* word) {
	fstream file("C:\\Users\\Adi\\Desktop\\FMI\\Introduction to programming Practicum\\Scrabble\\Scrabble\\Dictionary.txt", ios::in | ios::out | ios::app);

	if (!file.is_open()) {
		cout << "Error opening file for writing: " << endl;
		return;
	}

	file << word << endl;

	cout << "Added a new word to the dictionary!" << endl;

	file.close();
}
//Working with random
int generateRandomNumber(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution(min, max);
	int randomNumber = distribution(gen);
	return randomNumber;
}
//Settings
void settingsA(int& letterCount) {
	cout << "Enter new letter count:" << endl;
	char lc[SIZE];
	cin >> lc;
	while (!isNumber(lc)) {
		cout << "Enter new valid letter count:" << endl;
		cin >> lc;
	}
	letterCount = strToNumber(lc);

	if (letterCount < 0) {
		cout << "Letters count is made to a 3, which is the minimum." << endl;
		letterCount = 3;
	}
	if (letterCount > 100) {
		cout << "Letters count is made to a 100, which is the maximum." << endl;
		letterCount = 100;
	}
}
void settingsB(int& roundCount) {
	cout << "Enter new letter count:" << endl;
	char rc[SIZE];
	cin >> rc;
	while (!isNumber(rc)) {
		cout << "Enter new valid letter count:" << endl;
		cin >> rc;
	}
	roundCount = strToNumber(rc);

	if (roundCount < 1) {
		cout << "Rounds count is made to a 1, which is the minimum." << endl;
		roundCount = 1;
	}
	if (roundCount > 25) {
		cout << "Round count is made to a 25, which is the maximum." << endl;
		roundCount = 25;
	}
}
void openSettings(int& letterCount, int& roundCount) {
	char letter;
	cout << "Enter a letter: " << endl;
	cin >> letter;
	while (letter != 'a' && letter != 'b') {
		cout << "Sorry this is not an option! Enter a valid letter:";
		cin >> letter;
	}
	switch (letter)
	{
	case'a':
		settingsA(letterCount);
		break;
	case 'b':
		settingsB(roundCount);
		break;
	}
}
//Play
void playRound(unsigned const letterCount, unsigned& points) {
	char* letters = new char[letterCount + 1] {'\0'};
	for (size_t i = 0; i < letterCount; i++) {
		if (i % 2 == 0)
			letters[i] = numberToSymbol(generateRandomNumber('a', 'z'));
		else
			letters[i] = getVowel(generateRandomNumber(1, 6));
	}
	cout << letters;
	cout << " Enter word:" << endl;
	char word[SIZE];
	cin >> word;

	while (!checkForWord(word) || !checkIfWordContainsLettersGiven(letters, word)) {
		cout << "Invalid word. Try again with: " << letters << endl;
		cin >> word;

	}
	points += strLen(word);
	delete[] letters;
}
void play(int const letterCount, int const roundCount, unsigned& points) {
	for (size_t i = 1; i <= roundCount; i++)
	{
		cout << "Round " << i << " Available letters : ";
		playRound(letterCount, points);
	}
	cout << "Your total points are: " << points << endl;

}
//Main start function
void start(int& letterCount, int& roundCount) {

	printMenu();

	char word[SIZE];
	char number;
	unsigned points = 0;
	while (true) {
		cout << "Enter a number: " << endl;
		cin >> number;
		switch (number)
		{
		case '1':
			play(letterCount, roundCount, points);
			printMenu();
			points = 0;
			break;
		case '2':
			openSettings(letterCount, roundCount);
			break;
		case '3':
			cout << "Enter a new word:" << endl;
			cin >> word;
			enterWord(word);
			break;
		case '4':
			exit(0);
			break;
		default:
			cout << "Sorry this is not an option!" << endl;
			break;
		}
	}
}

int main()
{
	int letterCount = 10;
	int roundCount = 10;
	start(letterCount, roundCount);
}

