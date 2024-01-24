#include <iostream>
#include <random>
#include <Windows.h>

std::mt19937_64 mersenne{ std::random_device{}() };
std::uniform_int_distribution<int> uiAlpha{ 65,90 };
std::uniform_int_distribution<int> uiPos{ 0,3 };

constexpr unsigned int boardSize = 4;
constexpr unsigned int playCount = 8;

void SetBoard(char**, bool**);
void PrintBoard(char**, bool**, int*);
void CheckCard(char**, bool**, const int&, const int&, const int&, const int&, int*);

int main()
{
	char** mainBoard = new char* [boardSize];
	bool** checkBoard = new bool* [boardSize];
	std::string card1, card2;
	int card1Row, card1Col, card2Row, card2Col;
	bool isSame{ false };
	bool isReset{ true };
	int count{ };
	int playerPoint{ };

	while (playCount != count) {
		if (isReset) {
			SetBoard(mainBoard, checkBoard);
		}

		isReset = false;

		int menu;
		std::cout << "1. Choice card" << std::endl;
		std::cout << "2. Game reset" << std::endl;
		std::cout << "3.Show all card" << std::endl;
		std::cout << "4.Exit" << std::endl;
		std::cout << "Input menu: ";
		std::cin >> menu;

		switch (menu)
		{
		case 1:
			system("cls");
			PrintBoard(mainBoard, checkBoard, &playerPoint);
			while (true) {
				while (true) {
					std::cout << "Input card1: ";
					std::cin >> card1;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(32767, '\n');
					}
					else
						break;
				}

				while (true) {
					std::cout << "Input card2: ";
					std::cin >> card2;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(32767, '\n');
					}
					else
						break;
				}

				// TODO : 입력을 잘못 처리했거나, card1과 card2가 같으면 다시 입력 받아야함
				if (card1 != card2)
					break;
				else {
					std::cout << "Two cards are same, please input again" << std::endl;
					continue;
				}
			}
			switch (card1[0])
			{
			case 'a':
				card1Col = 0;
				break;
			case 'b':
				card1Col = 1;
				break;
			case 'c':
				card1Col = 2;
				break;
			case 'd':
				card1Col = 3;
				break;
			default:
				break;
			}
			switch (card1[1])
			{
			case '1':
				card1Row = 0;
				break;
			case '2':
				card1Row = 1;
				break;
			case '3':
				card1Row = 2;
				break;
			case '4':
				card1Row = 3;
				break;
			default:
				break;
			}

			switch (card2[0])
			{
			case 'a':
				card2Col = 0;
				break;
			case 'b':
				card2Col = 1;
				break;
			case 'c':
				card2Col = 2;
				break;
			case 'd':
				card2Col = 3;
				break;
			default:
				break;
			}

			switch (card2[1])
			{
			case '1':
				card2Row = 0;
				break;
			case '2':
				card2Row = 1;
				break;
			case '3':
				card2Row = 2;
				break;
			case '4':
				card2Row = 3;
				break;
			default:
				break;
			}
			CheckCard(mainBoard, checkBoard, card1Row, card1Col, card2Row, card2Col, &playerPoint);
			system("pause");
			PrintBoard(mainBoard, checkBoard, &playerPoint);
			system("pause");
			system("cls");
			count++;
			break;
		case 2:
			isReset = true;
			count = 0;
			playerPoint = 0;
			system("cls");
			break;
		case 3:
			std::cout << "  a b c d" << std::endl;
			for (int i = 0; i < boardSize; ++i) {
				std::cout << i + 1 << " ";
				for (int j = 0; j < boardSize; ++j) {
					std::cout << mainBoard[i][j] << " ";
				}
				std::cout << std::endl;
			}
			system("pause");
			system("cls");
			break;
		case 4:
			exit(1);
			break;
		default:
			break;
		}
	}
	PrintBoard(mainBoard, checkBoard, &playerPoint);
	std::cout << "Game Over!" << std::endl;
	system("pause");
}

void SetBoard(char** mainBoard, bool** checkBoard)
{
	for (int i = 0; i < boardSize; ++i) {
		mainBoard[i] = new char[boardSize];
	}

	for (int i = 0; i < boardSize; ++i) {
		checkBoard[i] = new bool[boardSize];
	}

	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			checkBoard[i][j] = false;
		}
	}

	// 1. 저장할 8개의 대문자 선정
	// 2. mainBoard에 랜덤하게 삽입!

	constexpr unsigned int nAlpha = 8;
	char alphaList[nAlpha];

	for (int i = 0; i < nAlpha; ++i) {
		alphaList[i] = static_cast<char>(uiAlpha(mersenne));
		for (int j = 0; j < i; ++j) {
			if (alphaList[i] == alphaList[j])
				i--;
		}
	}

	mainBoard[0][0] = alphaList[0];
	mainBoard[0][1] = alphaList[0];
	mainBoard[0][2] = alphaList[1];
	mainBoard[0][3] = alphaList[1];
	mainBoard[1][0] = alphaList[2];
	mainBoard[1][1] = alphaList[2];
	mainBoard[1][2] = alphaList[3];
	mainBoard[1][3] = alphaList[3];
	mainBoard[2][0] = alphaList[4];
	mainBoard[2][1] = alphaList[4];
	mainBoard[2][2] = alphaList[5];
	mainBoard[2][3] = alphaList[5];
	mainBoard[3][0] = alphaList[6];
	mainBoard[3][1] = alphaList[6];
	mainBoard[3][2] = alphaList[7];
	mainBoard[3][3] = alphaList[7];

	// shuffle
	for (int i = 0; i < boardSize * 2; i++) {
		int x = rand() % (boardSize * boardSize), y = rand() % (boardSize * boardSize);
		// swap
		char tmp = mainBoard[x / boardSize][x % boardSize];
		mainBoard[x / boardSize][x % boardSize] = mainBoard[y / boardSize][y % boardSize];
		mainBoard[y / boardSize][y % boardSize] = tmp;
	}
}

void PrintBoard(char** mainBoard, bool** checkBoard, int* playerPoint)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  // WHITE
	std::cout << "  a b c d" << std::endl;
	for (int i = 0; i < boardSize; ++i) {
		std::cout << i + 1 << " ";
		for (int j = 0; j < boardSize; ++j) {
			if (!checkBoard[i][j]) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // WHITE
				std::cout << "*" << " ";
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // RED
				std::cout << mainBoard[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "player point: " << (*playerPoint) << std::endl;
}

void CheckCard(char** mainBoard, bool** checkBoard, const int& card1Row,
	const int& card1Col, const int& card2Row, const int& card2Col, int* playerPoint)
{
	if (mainBoard[card1Row][card1Col] == mainBoard[card2Row][card2Col]) {
		checkBoard[card1Row][card1Col] = true;
		checkBoard[card2Row][card2Col] = true;
		(*playerPoint) += 10;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // WHITE
	std::cout << "  a b c d" << std::endl;
	for (int i = 0; i < boardSize; ++i) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // WHITE
		std::cout << i + 1 << " ";
		for (int j = 0; j < boardSize; ++j) {
			if (i == card1Row && j == card1Col) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); // BLUE
				std::cout << mainBoard[i][j] << " ";
			}
			else if (i == card2Row && j == card2Col) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);  // RED
				std::cout << mainBoard[i][j] << " ";
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // WHITE
				std::cout << "*" << " ";
			}
		}
		std::cout << std::endl;
	}
}