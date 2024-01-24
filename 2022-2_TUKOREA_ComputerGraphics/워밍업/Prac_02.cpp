#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::string filename;

	while (true) {
		std::cout << "Input data file name: ";
		std::cin >> filename;
		if (std::cin.fail()) {
			std::cout << "please try";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
			break;
	}

	std::ifstream ifs{ filename };

	std::cout << std::endl;

	if (!ifs) {
		std::cerr << "Cannot open file!" << std::endl;
	}
	else {
		int numCount{ };
		int allWordCount{ };
		int capitalCount{ };

		while (ifs) {
			std::string str;
			bool flag{ false };
			bool numCountFlag{ false };
			bool isSpecial{ false };
			bool isDigit{ false };
			bool spaceFlag{ false };
			int spaceCount{ };
			std::getline(ifs, str); // 한 줄 읽기

			// numCount 

			// 1. 줄에 숫자가 있는지 체크 
			// 2. 만약, 줄에 특수 문자가 있으면 숫자 한 개로 계산
			// 3. 그렇지 않다면 숫자 개수만큼 count

			for (int i = 0; i < str.length(); ++i) {
				if (isdigit(str[i])) {
					isDigit = true;
					break;
				}
			}
			// capitalCount
			//  해당 문자가 대문자면, capitalCount++;
			for (int i = 0; i < str.length(); ++i) {
				if (isupper(str[i]))
					capitalCount++;
			}

			if (isDigit) {
				for (int i = 0; i < str.length(); ++i) {
					if ('-' == str[i] || '_' == str[i] || '*' == str[i] || '/' == str[i] || ',' == str[i])
						isSpecial = true;
				}

				if (isSpecial) {
					for (int i = 0; i < str.length(); ++i) {
						if (isdigit(str[i])) {
							numCount++;
							break;
						}
					}
				}
				// 여기 카운트를 다시 해줘야함 (10을 1,0으로 계산하고 있음)
				// 숫자 개수만큼 count
				else {
					for (int i = 0; i < str.length(); ++i) {
						if (isdigit(str[i]))
							numCount++;
						if (i != 0 && (isdigit(str[i - 1])) && isdigit(str[i]))
							numCount--;
					}
				}
			}
			// wordCount
			// wordCount = allWordCount - numCount;

			// 전체 단어 개수 - 숫자 개수

			// 문장에 띄어쓰기가 있는경우 단어의 개수는 띄어쓰기 + 1
			// 만약, 띄어쓰기가 없는경우 단어의 개수는 1개이다.

			for (int i = 0; i < str.length(); ++i) {
				if (' ' == str[i]) {
					spaceCount++;
					spaceFlag = true;
				}
			}

			if (!spaceFlag) {
				allWordCount++;
			}
			else {
				allWordCount += (spaceCount + 1);
			}

			std::cout << str << std::endl;
		}
		std::cout << "=================" << std::endl;
		std::cout << "word count: " << allWordCount - 1 - numCount << std::endl;
		std::cout << "number count: " << numCount << std::endl;
		std::cout << "Capital word: " << capitalCount << std::endl;
		std::cout << "=================" << std::endl;;
	}
}