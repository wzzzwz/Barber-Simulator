#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

LARGE_INTEGER t1, t2, tc;
HANDLE hOut;
COORD POS = { 0,0 };
_CONSOLE_CURSOR_INFO cInfo;

int main()
{
	SetConsoleTitleA(LPCSTR("Barber Simulator"));//testtest
	system("chcp 65001");
	system("cls");
	bool b_state = false, flag = false;
	int queue = 0, tick = 0;
	unsigned short passer = 0, lev = 0;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	while (1)
	{
		if (b_state)
			tick++;
		else
			if (queue != 0)
				b_state = true;
		lev <<= 4;
		if (b_state&&tick == 20)
		{
			lev++;
			queue--;
			b_state = false;
			tick = 0;
		}
		passer <<= 1;
		if (passer & 32 && queue != 6)
		{
			queue++;
			passer &= 65503;
		}
		if (flag)
			passer += 1;
		flag = false;
		SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		cout << "    |";
		if (b_state)
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			WriteConsoleW(hOut, L"\u263a", 1, NULL, NULL);
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
			WriteConsoleW(hOut, L"\u263a", 1, NULL, NULL);
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}
		cout << "     |    \n";
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
		for (unsigned short t = 4096; t; t >>= 4)
			if (lev&t)
				WriteConsoleW(hOut, L"\u263a", 1, NULL, NULL);
			else
				cout << " ";
		SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		cout << "|";
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
		for (int t = queue; t; t--)
			WriteConsoleW(hOut, L"\u263a", 1, NULL, NULL);
		for (int t = 6 - queue; t; t--)
			cout << " ";
		SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		cout << "|    \n";
		SetConsoleTextAttribute(hOut, FOREGROUND_RED);
		for (unsigned short t = 32768; t; t >>= 1)
			if (passer&t)
				WriteConsoleW(hOut, L"\u263a", 1, NULL, NULL);
			else
				cout << " ";
		SetConsoleCursorPosition(hOut, POS);
		QueryPerformanceCounter(&t2);
		while ((t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart < 0.25)
		{
			QueryPerformanceCounter(&t2);
			if (_kbhit())
				if (_getch() == 'c')
					flag = true;
		}
		t1 = t2;
	}
}
