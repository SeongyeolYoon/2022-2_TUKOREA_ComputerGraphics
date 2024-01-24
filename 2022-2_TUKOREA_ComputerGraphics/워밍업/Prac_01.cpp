#include <iostream>
#include <random>
#include <cctype>
#include <cstdlib>

void MakeMatrix(int**,int**,int **,const int& ,const int&);
void PrintMatrix(int**,int**, const int&, const int&);
void PrintMatrix(int**, const int&, const int&);
void PrintDet(int**, int**);
void ResetTemp(int**, const int&, const int&);

std::mt19937_64 mersenne{ std::random_device{}() };
std::uniform_int_distribution<int> uiNum{ 0,2 };

int main()
{
	const int row{ 3 };
	const int col{ 3 };

	int** mat1 = new int* [row];
	int** mat2 = new int* [row];
	int** tempMat = new int* [row];

	MakeMatrix(mat1,mat2,tempMat,row,col);
	
	char command;

	while (true) {
		system("cls");
		std::cout << "=================" << std::endl;
		PrintMatrix(mat1, mat2, row, col);
		std::cout << "=================" << std::endl;

		std::cout << "m: Print multiplication of matrix" << std::endl;
		std::cout << "a: Print addition of a matrix" << std::endl;
		std::cout << "d: Print subtraction of a matrix" << std::endl;
		std::cout << "r: Print Value of Determinant" << std::endl;
		std::cout << "t: Print Transposed matrix and print Value of Determinant" << std::endl;
		std::cout << "h: Change 3X3 to 4X4 and print Value of Determinant" << std::endl;
		std::cout << "s: Setting random matrix number" << std::endl;
		std::cout << "q: EXIT" << std::endl;
		std::cout << "Input command:";

		while (true) {
			std::cin >> command;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}
			else
				break;
		}

		switch (tolower(command))
		{
		case 'm':
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					for (int k = 0; k < col; k++) {
						tempMat[i][j] += mat1[i][k] * mat2[k][j];
					}
				}
			}
			PrintMatrix(tempMat, row, col);
			ResetTemp(tempMat, row, col);
			system("pause");
			break;
		case 'a':
			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j) {
					tempMat[i][j] = mat1[i][j] + mat2[i][j];
				
				}
			}
			PrintMatrix(tempMat, row, col);
			ResetTemp(tempMat, row, col);
			system("pause");
			break;
		case 'd':
			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j) {
					tempMat[i][j] = mat1[i][j] - mat2[i][j];
				}
			}
			PrintMatrix(tempMat, row, col);
			ResetTemp(tempMat, row, col);
			system("pause");
			break;
		case 'r':
		{
			PrintDet(mat1,mat2);
			system("pause");
			break;
		}
		case 't':
		{
			int** transpose1 = new int* [row];
			int** transpose2 = new int* [row];

			for (int i = 0; i < row; ++i) {
				transpose1[i] = new int[col];
				transpose2[i] = new int[col];
			}

			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j) {
					transpose1[i][j] = 0;
					transpose2[i][j] = 0;
				}
			}

			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++) {
					transpose1[i][j] = mat1[j][i];
					transpose2[i][j] = mat2[j][i];
				}
			PrintMatrix(transpose1, transpose2, row, col);
			
			std::cout << std::endl;
			PrintDet(transpose1, transpose2);

			system("pause");
			break;
		}
		case 'h':
		{
			int temp1[row + 1][col + 1];
			int temp2[row + 1][col + 1];

			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < row; ++j) {
					temp1[i][j] = mat1[i][j];
					temp2[i][j] = mat2[i][j];
				}
			}
			temp1[3][3] = 1;
			temp2[3][3] = 1;

			for (int i = 0; i < row; ++i) {
				temp1[3][i] = 0;
				temp2[3][i] = 0;
				temp1[i][3] = 0;
				temp2[i][3] = 0;
			}

			for (int i = 0; i < row + 1; ++i) {
				for (int j = 0; j < col + 1; ++j) {
					if (0 == j) {
						std::cout << "|";
					}
					if (col != j)
						std::cout << temp1[i][j] << " ";
					else
						std::cout << temp1[i][j];
					if (col == j) {
						std::cout << "|";
					}
					if (col == j) {
						std::cout << "\t";
						for (int k = 0; k < col + 1; ++k) {
							if (0 == k) {
								std::cout << "|";
							}
							if (col != k)
								std::cout << temp2[i][k] << " ";
							else
								std::cout << temp2[i][k];
							if (col == k) {
								std::cout << "|";
							}
						}
					}
				}
				std::cout << std::endl;
			}


			PrintDet(mat1, mat2);
			system("pause");
			break;
		}
		case 's':
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j) {
					mat1[i][j] = uiNum(mersenne);
					mat2[i][j] = uiNum(mersenne);
				}
			PrintMatrix(mat1, mat2, row, col);
			break;
		case 'q':
			exit(1);
			break;
		default:
			break;
		}
	}
}

void MakeMatrix(int** mat1, int** mat2, int** tempMat, const int& row, const int& col)
{
	for (int i = 0; i < col; ++i) {
		mat1[i] = new int[col];
		mat2[i] = new int[col];
		tempMat[i] = new int[col];
	}

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j) {
			mat1[i][j] = uiNum(mersenne);
			mat2[i][j] = uiNum(mersenne);
			tempMat[i][j] = 0;
		}
}

void PrintMatrix(int** mat1,int** mat2, const int& row, const int& col)
{
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (0 == j) {
				std::cout << "|";
			}
			if (col - 1 != j)
				std::cout << mat1[i][j] << " ";
			else
				std::cout << mat1[i][j];
			if (col - 1 == j) {
				std::cout << "|";
			}
			if (col - 1 == j) {
				std::cout << "\t";
				for (int k = 0; k < 3; ++k) {
					if (0 == k) {
						std::cout << "|";
					}
					if (col - 1 != k)
						std::cout << mat2[i][k] << " ";
					else
						std::cout << mat2[i][k];
					if (col - 1 == k) {
						std::cout << "|";
					}
				}
			}
		}
		std::cout << std::endl;
	}
}
void PrintMatrix(int** mat, const int& row, const int& col)
{
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (0 == j) {
				std::cout << "|";
			}
			if (col - 1 != j)
				std::cout << mat[i][j] << " ";
			else
				std::cout << mat[i][j];
			if (col - 1 == j) {
				std::cout << "|";
			}
		}
		std::cout << std::endl;
	}
}

void ResetTemp(int** mat, const int& row, const int& col)
{
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j) {
			mat[i][j] = 0;
		}
}

void PrintDet(int** mat1, int** mat2)
{
	int det1{ };
	int det2{ };

	det1 = mat1[0][0] * (mat1[1][1] * mat1[2][2] - mat1[2][1] * mat1[1][2])

		- mat1[0][1] * (mat1[1][0] * mat1[2][2] - mat1[1][2] * mat1[2][0])

		+ mat1[0][2] * (mat1[1][0] * mat1[2][1] - mat1[1][1] * mat1[2][0]);

	det2 = mat2[0][0] * (mat2[1][1] * mat2[2][2] - mat2[2][1] * mat2[1][2])

		- mat2[0][1] * (mat2[1][0] * mat2[2][2] - mat2[1][2] * mat2[2][0])

		+ mat2[0][2] * (mat2[1][0] * mat2[2][1] - mat2[1][1] * mat2[2][0]);

	std::cout << det1 << ", " << det2 << std::endl;
}