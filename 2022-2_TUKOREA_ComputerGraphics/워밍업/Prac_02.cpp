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
			std::getline(ifs, str); // �� �� �б�

			// numCount 

			// 1. �ٿ� ���ڰ� �ִ��� üũ 
			// 2. ����, �ٿ� Ư�� ���ڰ� ������ ���� �� ���� ���
			// 3. �׷��� �ʴٸ� ���� ������ŭ count

			for (int i = 0; i < str.length(); ++i) {
				if (isdigit(str[i])) {
					isDigit = true;
					break;
				}
			}
			// capitalCount
			//  �ش� ���ڰ� �빮�ڸ�, capitalCount++;
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
				// ���� ī��Ʈ�� �ٽ� ������� (10�� 1,0���� ����ϰ� ����)
				// ���� ������ŭ count
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

			// ��ü �ܾ� ���� - ���� ����

			// ���忡 ���Ⱑ �ִ°�� �ܾ��� ������ ���� + 1
			// ����, ���Ⱑ ���°�� �ܾ��� ������ 1���̴�.

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