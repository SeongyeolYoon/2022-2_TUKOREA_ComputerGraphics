#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

struct Data {
	int x{ -1 };
	int y{ -2 };
	int z{ -1 };
	int offset{ };
	bool isInData{ false };
};

bool g_isSort{ false };

void Update(std::vector<Data>&);
void Render(std::vector<Data>&);

void PrintMenu();

void InsertAtTheTop(std::vector<Data>&);
void DeleteAtTheTop(std::vector<Data>&);
void InsertFromTheBottom(std::vector<Data>&);
void DeleteFromTheBottom(std::vector<Data>&);
void PrintNOfPoints(std::vector<Data>&);
void DeleteListAll(std::vector<Data>&);
void PrintFarthestCoor(std::vector<Data>&);
void PrintNearestCoor(std::vector<Data>&);

bool Compare(Data, Data);

int main()
{
	std::vector<Data> data(10);

	while (true) {
		Update(data);
		Render(data);
	}
}

void Update(std::vector<Data>& data)
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
		InsertAtTheTop(data);
		break;
	case '-':
		DeleteAtTheTop(data); // PASS
		break;
	case 'e':
		InsertFromTheBottom(data);
		break;
	case 'd':
		DeleteFromTheBottom(data); // PASS
		break;
	case 'l':
		PrintNOfPoints(data);
		break;
	case 'c':
		DeleteListAll(data);  // PASS
		break;
	case 'm':
		PrintFarthestCoor(data);
		break;
	case 'n':
		PrintNearestCoor(data);
		break;
	case 's':
		g_isSort = !g_isSort;
		break;
	case 'q':
		exit(1);
		break;
	default:
		break;
	}
}

void Render(std::vector<Data>& data)
{
	if (!g_isSort) {
		for (int i = data.size() - 1; i >= 0; --i) {
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
	// TODO : 정렬 알고리즘 만들기
	else {

		std::vector<Data> temp(10);
		for (int i = 0; i < data.size(); ++i)
			temp[i] = data[i];

		std::sort(temp.begin(), temp.end(), Compare);

		//for( int i =0; i < temp.size(); ++i)
		//	std::cout << temp[i].x << " " << temp[i].y << " " << temp[i].z << std::endl;

		for (int i = temp.size() - 1; i >= 0; --i) {
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
	system("pause");
}

void PrintMenu()
{
	system("cls");
	std::cout << "+: x,y,z 좌표 리스트의 맨 위에 입력:" << std::endl;
	std::cout << "-: 리스트의 맨 위에서 삭제" << std::endl;
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

void InsertAtTheTop(std::vector<Data>& data)
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

	for (int i = 0; i < data.size(); ++i) {
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

void DeleteAtTheTop(std::vector<Data>& data)
{
	for (int i = data.size() - 1; i >= 0; --i) {
		if (data[i].isInData) {
			data[i].x = 0;
			data[i].y = 0;
			data[i].z = 0;
			data[i].isInData = false;
			break;
		}
	}
}

void InsertFromTheBottom(std::vector<Data>& data)
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
	Data newData;
	newData.x = x;
	newData.y = y;
	newData.z = z;
	newData.offset += abs(x);
	newData.offset += abs(y);
	newData.offset += abs(z);;
	newData.isInData = true;
	data.insert(data.begin(), newData);
	data.pop_back();
}

void DeleteFromTheBottom(std::vector<Data>& data)
{
	// data.erase(data.begin());
	for (int i = 0; i < data.size(); ++i) {
		if (data[i].isInData) {
			data[i].isInData = false;
			data[i].x = 0;
			data[i].y = 0;
			data[i].z = 0;
			data[i].offset = 0;
			break;
		}
	}
	// Data newData;
	//data.insert(data.end(), newData);
}

void PrintNOfPoints(std::vector<Data>& data)
{
	int count{ };
	for (int i = 0; i < data.size(); ++i) {
		if (data[i].isInData)
			count++;
	}
	std::cout << "The number of Dots is " << count << std::endl;
	system("pause");
}

void DeleteListAll(std::vector<Data>& data)
{
	for (int i = 0; i < data.size(); ++i) {
		if (data[i].isInData) {
			data[i].x = 0;
			data[i].y = 0;
			data[i].z = 0;
			data[i].offset = 0;
			data[i].isInData = false;
		}
	}
}

void PrintFarthestCoor(std::vector<Data>& data)
{
	int tempX{ };
	int tempY{ };
	int tempZ{ };
	int maxSum{ INT_MIN };
	for (int i = 0; i < data.size(); ++i) {
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

	for (int i = 0; i < data.size(); ++i) {
		if (tempX == data[i].x && tempY == data[i].y && tempZ == data[i].z) {
			std::cout << "The coordinates at the farthest point is " << i << "|" << tempX << "," << tempY << "," << tempZ << std::endl;
			break;
		}
	}
}

void PrintNearestCoor(std::vector<Data>& data)
{
	int tempX{ };
	int tempY{ };
	int tempZ{ };

	unsigned int minSum{ UINT_MAX };

	for (int i = 0; i < data.size(); ++i) {
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

	for (int i = 0; i < data.size(); ++i) {
		if (tempX == data[i].x && tempY == data[i].y && tempZ == data[i].z) {
			std::cout << "The coordinates at the nearest point is " << i << "|" << tempX << "," << tempY << "," << tempZ << std::endl;
			break;
		}
	}
}

bool Compare(Data d1, Data d2)
{
	return (d1.offset > d2.offset);
}