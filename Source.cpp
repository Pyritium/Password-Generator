#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>		/* time */
#include <fstream>

typedef std::string string;
template <typename T>

bool Contains(std::vector<T> Types, T Type) {
	if (std::find(Types.begin(), Types.end(), Type) != Types.end())
	{
		return true;
	};

	return false;
};

class PasswordHandler
{
public:

	std::vector<string> Types = { "Complex", "Simple", "SimpleNoNumbersNoCaps", "SimpleNoNumbers", "NumbersOnly", "SymbolsOnly"};


	void GeneratePassword()
	{
		string Type;
		std::cin >> Type;

		bool TypeDefined = Contains(Types, Type);

		if (TypeDefined) {
			/* To add password generating algorithms, you'll have to manually add these here! I made it as dynamic as possible, but it can only go to an extent.*/
			/* Yes, I'm also aware of how shitty the "else if" chains look, however I'm really new to C++ so I'm unaware on how to go about a better method, if there is*/
			/* By chance a better method, please let me know on my github page!!! THANKS! */
			srand(time(NULL));
			int i = rand() % 20 + 5;
			int x = rand() % 3 + 1;
			int Complexity = 68; /* Number to stop at (Alphanumerically), e.g if I input 10 then only numbers 0-9*/
			int Begin = 0;
			if (Type == "Complex") {
				i = i * 4;
			}
			else if (Type == "Simple") {
				Complexity = 42;
			}
			else if (Type == "SimpleNoNumbersNoCaps") {
				Begin = 16;
				Complexity = 26;
			}
			else if (Type == "SimpleNoNumbers") {
				Begin = 10;
				Complexity = 58;
			}
			else if (Type == "NumbersOnly") {
				Complexity = 10;
			}
			else if (Type == "SymbolsOnly") {
				Begin = 10;
				Complexity = 6;
			};

			string Password = GenerateString(i, Begin, Complexity);
			std::cout << Password << std::endl;

			std::cout << "Password generated, save to file? Y|N\n";

			string Input;
			std::cin >> Input;

			if (Input == "Y" || Input == "y") {
				AppendToFile(Password);
			}
			else
			{
				std::cout << "Insert a new password type!\n";
				GeneratePassword();
			}
		}
		else if (Type == "List") {
			int ArrSize = std::size(Types);
			std::cout << "---------------------\n";
			for (int i = 0; i < ArrSize; i++) {
				std::cout << Types[i] << std::endl;
			};
			std::cout << "---------------------\n";

			GeneratePassword();
		}
		else
		{
			std::cout << "Error: Type not specified!\n";
			GeneratePassword();
		};
	};

	void AppendToFile(string Password)
	{
		std::ofstream outfile("GeneratedPasswords.txt", std::ios::app);

		if (!outfile.fail()) {
			outfile << Password << std::endl;
			std::cout << "Saved to file!\n";
			GeneratePassword();
		}
	}

private:
	const string AlphaNumeric =
		"0123456789"
		"!@#$%&"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	string GenerateString(int Length, int Begin, int Complexity)
	{
		string TransformedAN = AlphaNumeric.substr(Begin, Complexity);
		string String;
		for (int i = 0; i < Length; i++) {
			int x = rand() % Complexity + Begin;
			char r = AlphaNumeric.at(x);

			String.insert(String.length(), 1, r);
			/*String.append(r)*/
		}
		return String;
	};
};


int main() {
	PasswordHandler Passwords;


	std::cout << "Insert a type for a password generation! Alternatively, type 'List' to list off current types!" << std::endl;
	Passwords.GeneratePassword();
}
