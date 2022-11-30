#include <iostream>
#include <Windows.h>
#include <ctime>
#include<deque>

//#include<conio.h>
const int height = 6;
const int width = 16;



int x = width / 2, y = height / 2;
int z=1;
char qwe[height][width];
std::deque<std::pair<int,int>>telos;
void apl() {
	int rendx=rand()% width, randy=rand() % height;
	while ((qwe[randy][rendx] == '0')||(qwe[randy][rendx] == '#')){
		rendx = rand() % width;
		randy = rand() % height;
	}
	qwe[randy][rendx] = '.';
}
bool gamestart() {
	if ((x < 1) || (x > width - 2) || (y < 1) || (y > height - 2)) return false;
	else {
		if (z != 1)return false;
		else return true;
	};
}
void carta() {
	for (int q = 0; q < height; q++) {
		for (int w = 0; w < width; w++)qwe[q][w] = ' ';
	}
	for (int q = 0; q < height; q++) {
		qwe[q][0] = '#';
		qwe[q][width -1] = '#';
	}
	for (int q = 0; q < width; q++) {
		qwe[0][q] = '#';
		qwe[height - 1][q] = '#';
	}
	apl();
	
}
void anima() {
	std::cout << "sadf";
}



//сложная логика/////////////////////
void log() {
	if (qwe[y][x] == '0')z++;
	if (qwe[y][x] == '.')apl();
	else {
		auto sdf = *telos.begin();
		qwe[sdf.first][sdf.second] = ' ';
		telos.pop_front();
	}
	qwe[y][x] = '0';
}
void dvish() {
	if (GetAsyncKeyState('W') & 0x01) {
		telos.push_back(std::make_pair(y, x));
		y--;
		log();
	}
	if (GetAsyncKeyState('A') & 0x01) {
		telos.push_back(std::make_pair(y, x));
		x--;
		log();
	}
	if (GetAsyncKeyState('D') & 0x01) {
		telos.push_back(std::make_pair(y, x));
		x++;
		log();
	}
	if (GetAsyncKeyState('S') & 0x01) {
		telos.push_back(std::make_pair(y, x));
		y++;
		log();
	}
}
int main()
{
	using namespace std;
	wchar_t* screen = new wchar_t[height * width];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	carta();
	while (gamestart())
	{
		dvish();
		for (int q = 0; q < height; q++) {
			for (int c = 0; c < width; c++)screen[q* width +c] = qwe[q][c];
		}
		WriteConsoleOutputCharacter(hConsole, screen, height * width, { 0,0 }, &dwBytesWritten);
	}
}