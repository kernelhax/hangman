#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <map>


std::string emptyWord(int wordCount);

int main(void)
{
	// game variables init
	std::ifstream wordlist; 
	int winning = 0;
	size_t guesses = 0;
	int numberOfWords = 0;
	bool isPlaying = true;
	char choice = ' ';
	std::string line;
	std::vector<std::string> listOfWords;
	std::map<char, bool> usedLetters;

	wordlist.open("wordlist.txt");
	
	while (std::getline(wordlist, line))
	{
		numberOfWords++; 
		listOfWords.push_back(line);
	}

	wordlist.close();

	// generate random number for random word 
	srand((unsigned)time(NULL));
	int randomWordInt = rand() % numberOfWords;
	std::string answer = listOfWords.at(randomWordInt);
	int wordLength = answer.length();
	std::string blankWord = emptyWord(wordLength);

	// game loop
	do
	{
		printf("\033c");
		std::cout << blankWord << std::endl;
		//*********************************************************
		// DEBUG
		//std::cout << "Blank word is " << blankWord << std::endl;
		//std::cout << "Answer is " << answer << std::endl;
		// END DEBUG
		//*********************************************************
		std::cout << "Guess the word!" << std::endl;
		std::cin >> choice;

		if (usedLetters[choice])
		{
			std::cout << "Letter used in previous guess." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			continue;
		}
		else
		{
			usedLetters[choice] = true;
		}

		for (size_t i = 0; i < answer.length(); i++)
		{			
			if (answer[i] == choice)
			{
				blankWord[i] = choice;
				winning++;
			}
		}

		if (winning == answer.length())
		{
			std::cout << answer << std::endl;
			std::cout << "You win!" << std::endl;
			isPlaying = false;
			break;
		}

		guesses++;

		if (guesses > (answer.length() * 2))
		{
			std::cout << "Sorry, you lose..." << std::endl;
			std::cout << "The answer was " << answer << std::endl;
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

// TODO 
// Implement Hangman stick figure drawing 