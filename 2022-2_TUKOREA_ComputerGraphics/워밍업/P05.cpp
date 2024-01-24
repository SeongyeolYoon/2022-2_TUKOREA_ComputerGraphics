#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>

struct Data {
	int x{};
	int y{};
	int z{};
	bool isInData{ false };
	int offset{ };
};

int dataSize = 10;
bool isSort{ false };

void Update(Data[]);
void Render(Data[]);
void PrintMenu();
void InsertAtTheTop(Data []);
void InsertFromTheBottom(Data []);
void DeleteAtTheTop(Data[]);
void DeleteFromTheBottom(Data[]);
void PrintNOfDots(Data[]);
void DeleteListAll(Data[]);
void PrintFarthestCoor(Data[]);
void PrintNearestCoor(Data[]);

bool Compare(Data[], Data[]);

int main()
{
	Data* data = new Data[dataSize];

	while (true) {
		Update(data);
		Render(data);
	}
}

void Update(Data data[])
{
	PrintMenu();
	char command;

	while (true) {
		std::cin >> command;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
			break;
	}

	switch (command)
	{
	case '+':
		InsertAtTheTop(data); // PASS
		break;
	case '-':
		DeleteAtTheTop(data); // PASS
		break;
	case 'e':
		InsertFromTheBottom(data); // PASS
		break;
	case 'd':
	    DeleteFromTheBottom(data); // PASS
		break;
	case 'l':
		PrintNOfDots(data);  // PASS
		break;
	case 'c':
		DeleteListAll(data);  // PASS
		break;
	case 'm':
		PrintFarthestCoor(data); // PASS
		break;
	case 'n':
		PrintNearestCoor(data); // PASS
		break;
	case 's':
		// TODO : 정렬해야함
		// TODO: 데이터가 덜 채워졌을때 정렬 해야함
		isSort = !isSort;
		break;
	case 'q':
		exit(1);
		break;
	default:
		break;
	}
}

void Render(Data data[])
{
	if (!isSort) {

		std::cout << "-------" << std::endl;
		for (int i = dataSize - 1; i >= 0; --i) {
			std::cout << i << "|";
			if (data[i].isInData) {
				std::cout << data[i].x << " " << data[i].y << " " << data[i].z << std::endl;
				std::cout << "-|-----" << std::endl;
			}
			else {
				std::cout << std::endl;
				if (0 != i)
					std::cout << "-|-----" << std::endl;
				else
					std::cout << "-------" << std::endl;
			}
		}
	}
	else {

		// 1. 만약, 데이터가 모두 들어있을 시 , 그냥 정렬 해주면 됨

		// 2. 문제는 중간 중간에 데이터가 비어 있거나, 데이터가 꽉 차여있지 않을때 
		Data* temp = new Data[dataSize];	

		int count{ };

		for (int i = 0; i < dataSize; ++i) {
			if(data[i].isInData)
				count++;
		}

		// 데이터가 꽉 찬 경우
		if (10 == count) {
			for (int i = 0; i < dataSize; ++i)
				temp[i] = data[i];

			std::sort(temp, temp + 10,Compare);

			//// 배열 오름차순 정렬

			//for (int i = 0; i < dataSize; ++i) {
			//	for (int j = 0; j < dataSize - 1 - i; ++j) {
			//		if (temp[j].offset > temp[j + 1].offset) {
			//			std::swap(temp[j], temp[j + 1]);
			//		}
			//	}
			//}

			std::cout << "-------" << std::endl;
			for (int i = dataSize - 1; i >= 0; --i) {
				std::cout << i << "|";
				if (temp[i].isInData) {
					std::cout << temp[i].x << " " << temp[i].y << " " << temp[i].z << std::endl;
					std::cout << "-|-----" << std::endl;
				}
				else {
					std::cout << std::endl;
					if (0 != i)
						std::cout << "-|-----" << std::endl;
					else
						std::cout << "-------" << std::endl;
				}
			}

		}

		// 데이터가 꽉 차지 않은 경우
		else {

			// 데이터가 꽉 차지 않은 경우에는 어떻게 해야할까
			
			// 우선 data에 저장되어 있는 데이터들의 개수를 세고
			// 순차적으로 담아야게찌 

			int count{ };

			for (int i = 0; i < dataSize; ++i) {
				if (data[i].isInData)
					count++;
			}

			Data* temp = new Data[count];
			int cnt{ };
			for (int i = 0; i < dataSize; ++i) {
				if (data[i].isInData) {
					temp[cnt] = data[i];
					cnt++;
				}
			}
			
			for (int i = 0; i < count; ++i) {
				for (int j = 0; j < count - 1 - i; ++j) {
					if (temp[j].offset > temp[j + 1].offset)
						std::swap(temp[j], temp[j + 1]);
				}
			}

			for (int i = 0; i < count; ++i) {
				std::cout << temp[i].x << " " << temp[i].y << " " << temp[i].z << std::endl;
			}
		}

	//	// 1. 들어있는 데이터 갯수 세기 
	//		// 2. 데이터 10개짜리 배열 생성
	//		// 3. 데이터를 10개짜리 배열에 모두 담고
	//		// 4. Sum값에 따라 오름차순/내림차순 정렬
	//		// 5. 출력


	//	//for (int i = 0; i < dataSize; ++i) {
	//	//	for (int j = 0; j < dataSize - 1 - i; ++j) {
	//	//		
	//	//	}
	//	//}

	//	Data* temp = new Data[dataSize];

	//	for (int i = 0; i < dataSize; ++i) {
	//		temp[i] = data[i];
	//	}

	//	for (int i = 0; i < dataSize; ++i) {
	//		for (int j = 0; j < dataSize - 1 - i; ++j) {
	//			if (temp[i].isInData) {
	//				if (temp[j].offset > temp[j + 1].offset) {
	//					Data t;
	//					t = temp[j];
	//					temp[j] = temp[j + 1];
	//					temp[j + 1] = t;
	//				}
	//			}
	//		}
	//	}
	//	std::cout << "-------" << std::endl;
	//	for (int i = dataSize - 1; i >= 0; --i) {
	//		std::cout << i << "|";
	//		if (temp[i].isInData) {
	//			std::cout << temp[i].x << " " << temp[i].y << " " << temp[i].z << std::endl;
	//			std::cout << "-|-----" << std::endl;
	//		}
	//		else {
	//			std::cout << std::endl;
	//			if (0 != i)
	//				std::cout << "-|-----" << std::endl;
	//			else
	//				std::cout << "-------" << std::endl;
	//		}
	//	}

	//	//int pointCount{ };
	//	//int sequnece = 0;

	//	//for (int i = 0; i < dataSize; ++i) {
	//	//	if (data[i].isInData)
	//	//		pointCount++;
	//	//}

	//	//int* temp = new int[pointCount];

	//	//for (int i = 0; i < dataSize; ++i) {
	//	//	if (data[i].isInData) {
	//	//		temp[sequnece] = data[i].offset;
	//	//		sequnece++;
	//	//	}
	//	//}

	//	//for (int i = 0; i < sequnece + 1; ++i) {
	//	//	for (int j = 0; j < sequnece; ++j) {
	//	//		if (temp[j] > temp[j + 1]) {
	//	//			int t = temp[j];
	//	//			temp[j] = temp[j + 1];
	//	//			temp[j + 1] = t;
	//	//		}
	//	//	}
	//	//}

	//	//int tSequncec = sequnece;

	//	//for (int i = 0; i < dataSize; ++i) {
	//	//	for (int j = 0; j < sequnece - 1; ++j) {
	//	//		if (data[i].isInData) {
	//	//			if (data[i].offset == temp[j]) {
	//	//				std::cout << tSequncec << "|";
	//	//				std::cout << data[i].x << " " << data[i].y << " " << data[i].z << std::endl;
	//	//				std::cout << "-|-----" << std::endl;
	//	//				tSequncec--;
	//	//			}
	//	//		}
	//	//	}
	//	//}

	//	////std::cout << "-------" << std::endl;
	//	////for (int i = dataSize-1; i >= 0; --i) {
	//	////	std::cout << i << "|";
	//	////	if (data[i].isInData) {
	//	////		std::cout << data[i].x << " " << data[i].y << " " << data[i].z << std::endl;
	//	////		std::cout << "-|-----" << std::endl;
	//	////	}
	//	////	else {
	//	////		std::cout << std::endl;
	//	////		if (0 != i)
	//	////			std::cout << "-|-----" << std::endl;
	//	////		else
	//	////			std::cout << "-------" << std::endl;
	//	////	}
	//	////}


	//	//// 데이터 정렬
	//	//int count{ };
	//	//
	//	//for (int i = 0; i < dataSize; ++i) {
	//	//	if (data[i].isInData && data[i].x > 0 && data[i].y > 0 && data[i].z > 0)
	//	//		count++;
	//	//}

	//	//std::cout << "count: " << count << std::endl;

	//	//int* tempOffset = new int[count];

	//	//int t{ };

	//	//for (int i = 0; i < count; ++i) {
	//	//	for (int j = t; j < dataSize; ++j) {
	//	//		tempOffset[i] = data[i].offset;
	//	//		t = t + 1;
	//	//	}
	//	//}



	///*	int* tOffset = new int[count];
	//	int tj{ };

	//	for (int i = 0; i < count; ++i) {
	//		for (int j = tj; j < dataSize; ++j) {
	//			if (data[j].isInData) {
	//				tOffset[i] = data[j].offset;
	//				j = tj;
	//			}
	//		}
	//	}

	//	for (int i = 0; i < count; ++i)
	//		std::cout << tOffset[i] << " ";*/





	}
	system("pause");
}

void PrintMenu()
{
	system("cls");
	std::cout << "+: x,y,z 좌표 리스트의 맨 위에 입력:" << std::endl;
	std::cout << "-: 리스트의 맨 위에서 삭제" << std::endl;;
	std::cout << "e: x,y,z 좌표 리스트의 맨 아래에 입력;" << std::endl;;
	std::cout << "d: 리스트의 맨 아래에서 삭제" << std::endl;;
	std::cout << "l: 리스트에 저장된 점의 개수를 출력" << std::endl;;
	std::cout << "c: 리스트를 비움. 리스트를 비운 후 다시 입력하면 0 번부터 저장" << std::endl;;
	std::cout << "m: 원점에서 가장 먼 거리에 있는 점의 좌표값을 출력" << std::endl;;
	std::cout << "n: 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력" << std::endl;;
	std::cout << "s: 원점과의 거리를 정렬하여 출력. 인덱스 0 번부터 빈 칸없이 저장하여 출력. 다시 s 를 누르면 원래의 인덱스 위치에 출력" << std::endl;
	std::cout << "q: 프로그램 종료" << std::endl;;
	std::cout << "입력: ";
}

void AddData(const char& command, const int& x, const int& y, const int& z, Data data[])
{
	if ('+' == command) {
		for (int i = 0; i < dataSize; ++i) {
			if (!data[i].isInData) {
				data[i].x = x;
				data[i].y = y;
				data[i].z =z;
				data[i].isInData = true;
				break;
			}
		}
	}
}

void InsertAtTheTop(Data data[])
{
	std::cout << "Enter Coorinates x,y,z (Input interger ONLY):";
	int x, y, z;

	while (true) {
		std::cin >> x >> y >> z;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
			break;
	}

	for (int i = 0; i < dataSize; ++i) {
		if (!data[i].isInData) {
			data[i].x = x;
			data[i].y = y;
			data[i].z = z;
			data[i].offset += abs(x);
			data[i].offset += abs(y);
			data[i].offset += abs(z);
			data[i].isInData = true;
			break;
		}
	}
	
}

void DeleteAtTheTop(Data data[])
{
	for (int i = dataSize - 1; i >= 0; --i) {
		if (data[i].isInData) {
			data[i].x = 0;
			data[i].y = 0;
			data[i].z = 0;
			data[i].isInData = false;
			break;
		}
	}
}

void PrintNOfDots(Data data[])
{
	int count{ };
	for (int i = 0; i < dataSize; ++i) {
		if (data[i].isInData)
			count++;
	}
	std::cout << "The number of Dots is " << count << std::endl;
	system("pause");
}

void DeleteListAll(Data data[])
{
	for (int i = 0; i < dataSize; ++i) {
		if (data[i].isInData)
			data[i].isInData = false;
	}
}

void PrintFarthestCoor(Data data[])
{
	int tempX{ };
	int tempY{ };
	int tempZ{ };
	int maxSum{ INT_MIN };
	for (int i = 0; i < dataSize; ++i) {
		int sum{ };
		sum += abs(data[i].x);
		sum += abs(data[i].y);
		sum += abs(data[i].z);

		if (maxSum < sum) {
			tempX = data[i].x;
			tempY = data[i].y;
			tempZ = data[i].z;
			maxSum = sum;
		}
	}

	for (int i = 0; i < dataSize; ++i) {
		if (tempX == data[i].x && tempY == data[i].y && tempZ == data[i].z) {
			std::cout << "The coordinates at the farthest point is " << i << "|" << tempX << "," << tempY << "," << tempZ << std::endl;
			break;
		}
	}
}

void PrintNearestCoor(Data data[])
{
	int tempX{ };
	int tempY{ };
	int tempZ{ };

	 unsigned int minSum{ UINT_MAX };

	for (int i = 0; i < dataSize; ++i) {
		if (data[i].isInData) {
			int sum{ };
			sum += abs(data[i].x);
			sum += abs(data[i].y);
			sum += abs(data[i].z);

			if (minSum > sum) {
				tempX = data[i].x;
				tempY = data[i].y;
				tempZ = data[i].z;
				minSum = sum;
			}
		}
	}

	for (int i = 0; i < dataSize; ++i) {
		if (tempX == data[i].x && tempY == data[i].y && tempZ == data[i].z) {
			std::cout << "The coordinates at the nearest point is " << i << "|" << tempX << "," << tempY << "," << tempZ << std::endl;
			break;
		}
	}
}

void DeleteFromTheBottom(Data data[])
{
	for (int i = 0; i < dataSize; ++i) {
		if (data[i].isInData) {
			data[i].x = 0;
			data[i].y = 0;
			data[i].z = 0;
			data[i].isInData = false;
			break;
		}
	}
}

void InsertFromTheBottom(Data data[])
{
	std::cout << "Enter Coorinates x,y,z (Input interger ONLY):";
	int x, y, z;

	while (true) {
		std::cin >> x >> y >> z;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
			break;
	}

	Data temp = data[dataSize - 1];

	for (int i = dataSize - 2; i >= 0; --i) {
		data[i + 1] = data[i];
		if (data[i + 1].x > 0 && data[i + 1].y > 0 && data[i + 1].z > 0)
			data[i + 1].isInData = true;
	}

	data[0].x = x;
	data[0].y = y;
	data[0].z = z;
	data[0].isInData = true;
}

bool Compare(Data d1[], Data d2[])
{
	if (d1->offset > d2->offset) {
		return d2 < d1;
	}
	else
		d1 < d2;
}