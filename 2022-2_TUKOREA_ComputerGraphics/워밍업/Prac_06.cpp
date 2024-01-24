#include <iostream>
#include <random>
enum class Direction{LEFT  = 0, RIGHT, UP, DOWN};

constexpr unsigned int boardSize = 30;

void PrintBoard(int**);
void MakePath(int**, bool**);
void MovePathToLeft(int**);
void MovePathToRight(int**);

int main()
{
	int** board = new int*[boardSize];
	bool** checkBoard = new bool*[boardSize];

	for (int i = 0; i < boardSize; ++i)
		board[i] = new int[boardSize];

	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j)
			board[i][j] = 0;
	}

	for (int i = 0; i < boardSize; ++i)
		checkBoard[i] = new bool[boardSize];

	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j)
			checkBoard[i][j] = false;
	}

	
	while (true) {
		system("cls");
		PrintBoard(board);

		std::cout << "p: remake path" << std::endl;
		std::cout << "l: move path to left" << std::endl;
		std::cout << "r: move path to right" << std::endl;
		std::cout << "q: exit" << std::endl;
		std::cout << "Input command:";
		char ch;
		std::cin >> ch;

		switch (ch)
		{
		case 'p':
			MakePath(board, checkBoard);
			break;
		case 'l':
			MovePathToLeft(board);
			break;
		case 'r':
			MovePathToRight(board);
			break;
		case 'q':
			exit(1);
			break;
		default:
			break;
		}
		system("pause");
	}

}

void PrintBoard(int** board)
{
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			printf("%3d ", board[i][j]);
		}
		std::cout << std::endl;
	}
}

void MakePath(int** board, bool** checkBoard)
{
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j)
			board[i][j] = 0;
	}

	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j)
			checkBoard[i][j] = false;
	}


	std::mt19937_64 mersenne{ std::random_device{}() };
	std::uniform_int_distribution<int> uiDir{ 0,3 }; // 왼쪽, 오른족, 위, 아래
	std::uniform_int_distribution<int> uiCount{ 1,7 };

	constexpr unsigned int maxMoveCount{ 8 };

	int curRow{ };
	int curCol{ };
	int num{1};
	int moveCount[maxMoveCount] = { 0, };	// LEFT, RIGHT, UP, DOWN
	
	Direction dir = Direction::UP;
	Direction prevDir = Direction::UP;

	board[0][0] = 1;
	checkBoard[0][0] = true;

	while (true) {
		prevDir = dir;

		while (true) {
			dir = static_cast<Direction>((uiDir(mersenne)));
			if (prevDir == dir)
				continue;
			else
				break;
		}

		int count = uiCount(mersenne);

		switch (dir)
		{
		case Direction::LEFT:
			for (int i = 0; i < count; ++i) {
				if (curCol > 0) {
					curCol--;
					if (!checkBoard[curRow][curCol]) {
						num++;
						board[curRow][curCol] = num;
						checkBoard[curRow][curCol] = true;
					}
					else {
						num++;
						board[curRow][curCol] = num;
						// checkBoard[curRow][curCol] = true;
					}
				}
				else
					break;
			}
			break;
		case Direction::RIGHT:
			for (int i = 0; i < count; ++i) {
				if (curCol < boardSize - 1) {
					curCol++;
					if (!checkBoard[curRow][curCol]) {
						num++;
						board[curRow][curCol] = num;
						checkBoard[curRow][curCol] = true;
					}
					else {
						num++;
						board[curRow][curCol] = num;
					}
				}
				else
					break;
			}
			break;
		case Direction::UP:
			for (int i = 0; i < count; ++i) {
				if (curRow > 0) {
						curRow--;
						if (!checkBoard[curRow][curCol]) {
							num++;
							board[curRow][curCol] = num;
							checkBoard[curRow][curCol] = true;
						}
						else {
							num++;
							board[curRow][curCol] = num;
						}
				}
				else
					break;
			}
			break;
		case Direction::DOWN:
			for (int i = 0; i < count; ++i) {
				if (curRow < boardSize - 1) {
					curRow++;
					if (!checkBoard[curRow][curCol]) {
						num++;
						board[curRow][curCol] = num;
						checkBoard[curRow][curCol] = true;
					}
					else {
						num++;
						board[curRow][curCol] = num;
					}
				}
				else
					break;
			}
			break;
		default:
			break;
		}
		if (num > 900)
			break;
		if (curRow == boardSize - 1 || curCol== boardSize - 1)
			break;
	}

	// 안되면 이거라도 내야해ㅠ 
	//while (true) {
	//		Direction dir = static_cast<Direction>(uiDir(mersenne));
	//		Direction prevDir = dir;
	//	switch (dir)
	//	{
	//	case Direction::LEFT:
	//		if (8 == moveCount[0]) {
	//			moveCount[0] = 0;
	//			break;
	//		}
	//		if(col>0)
	//			col--;
	//		else {
	//			int random = uiDir(mersenne);
	//			while (random!= 0) {
	//				random = uiDir(mersenne);
	//			}
	//			continue;
	//		}
	//		if (col >= 0) {
	//			if (!checkBoard[row][col]) {
	//				num++;
	//				moveCount[0]++;
	//				board[row][col] = num;
	//				checkBoard[row][col] = true;
	//			}
	//		}
	//		else
	//			continue;
	//		break;
	//	case Direction::RIGHT:
	//		if (8 == moveCount[1]) {
	//			moveCount[1] = 0;
	//			break;
	//		}
	//		if(col<boardSize-1)
	//			col++;
	//		if (col <= boardSize - 1) {
	//			if (!checkBoard[row][col]) {
	//				num++;
	//				moveCount[1]++;
	//				board[row][col] = num;
	//				checkBoard[row][col] = true;
	//			}
	//		}
	//		else
	//			continue;
	//		break;
	//	case Direction::UP:
	//		if (8 == moveCount[2]) {
	//			moveCount[2] = 0;
	//			break;
	//		}
	//		if(row>0)
	//			row--;
	//		if (row >= 0) {
	//			if (!checkBoard[row][col]) {
	//				num++;
	//				moveCount[2]++;
	//				board[row][col] = num;
	//				checkBoard[row][col] = true;
	//			}
	//		}
	//		break;
	//	case Direction::DOWN:
	//		if (8 == moveCount[3]) {
	//			moveCount[3] = 0;
	//			break;
	//		}
	//		if(row< boardSize-1)
	//			row++;
	//		if (row <= boardSize - 1) {
	//			if (!checkBoard[row][col]) {
	//				num++;
	//				moveCount[3]++;
	//				board[row][col] = num;
	//				checkBoard[row][col] = true;
	//			}
	//		}
	//		break;
	//	default:
	//		break;
	//	}
	//	if (num > 900)
	//		break;
	//	if (row == boardSize - 1 || col == boardSize - 1)
	//		break;
	//	//PrintBoard(board);
	//}
}

void MovePathToLeft(int** board)
{
	int len = boardSize;

	for (int i = 0; i < boardSize; ++i) {
		int temp = board[i][0];
		for (int j = 0; j < boardSize - 1; ++j)
			board[i][j] = board[i][j + 1];
		board[i][len - 1] = temp;
	}
}

void MovePathToRight(int** board)
{
	int len = boardSize;;

	for (int i = 0; i < boardSize; ++i) {
		int temp = board[i][boardSize-1];

		for (int j = boardSize - 2; j >= 0; --j)
			board[i][j + 1] = board[i][j];
		board[i][0] = temp;

	}
}