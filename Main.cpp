#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

std::string emptyWord(int wordCount);

int main(void)
{
	// game variables init
	std::ifstream wordlist; 
	int winning = 0;
	int guess = 0;
	int losing = 0;
	int numberOfWords = 0;
	bool isPlaying = true;
	char choice = ' ';
	std::string line;
	std::vector<std::string> listOfWords;
	wordlist.open("wordlist.txt");
	
	while (std::getline(wordlist, line))
	{
		numberOfWords++; 
		listOfWords.push_back(line);
	}

	wordlist.close();

	// generate random number for random word 
	srand(time(NULL));
	int randomWordInt = rand() % numberOfWords;
	std::string answer = listOfWords.at(randomWordInt);

	// game loop
	do
	{
		int wordLength = answer.length();
		std::string blankWord = emptyWord(wordLength);
		std::cout << "Blank word is " << blankWord << std::endl;
		std::cout << "Answer is " << answer << std::endl;
		std::cout << "Guess the word!" << std::endl;
		std::size_t found = answer.find("o");
		if (found != std::string::npos)
		{
			std::cout << "Guess correctly!" << std::endl;
		}
		std::cin >> choice;

		if (choice == 'y' || choice == 'Y')
		{
			std::cout << "Game Over" << std::endl;
		}
		if (choice == 'n' || choice == 'N')
		{
			isPlaying = false;
		}
	} while (isPlaying);
}

std::string emptyWord(int wordCount)
{
	std::string blankWord = "";
	for (int i = 0; i < wordCount; i++)
	{
		blankWord.append("-");
	}
	return blankWord;
}