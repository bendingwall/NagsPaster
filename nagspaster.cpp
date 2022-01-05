#include <iostream>
#include "windows.h"
#include <vector>
#include <sstream>

void RepasteList(std::vector<std::string>& myHorses);
void insertList(std::vector<std::string>& myHorses);
void pasteHorse(std::vector<std::string>& myHorses);
void PasteToClipboard(const std::string& text);

bool getKeysState()
{
	if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x56)) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void PasteToClipboard(const std::string& text)
{
	if (HANDLE clipdata = GlobalAlloc(GMEM_FIXED, text.length() + 1))
	{
		std::memcpy(clipdata, text.data(), text.length() + 1);

		if (OpenClipboard(NULL))
		{
			if (EmptyClipboard() && SetClipboardData(CF_TEXT, clipdata))

			CloseClipboard();
		}
	}
}

void RepasteList(std::vector<std::string>& myHorses)
{
	std::cout << "Press 1 to repaste the list or 2 to exit." << std::endl;

	std::string line;

	while (true)
	{
		std::getline(std::cin, line);

		if (line == "1")
		{
			pasteHorse(myHorses);
		}
		else if (line == "2")
		{
			exit(3);
		}
	}
}

void pasteHorse(std::vector<std::string>& myHorses)
{
	int i = 1;

	std::cout << "Ready to Paste." << std::endl;

	while (true)
	{
		if (getKeysState())
		{
			if (i < myHorses.size())
			{
				Sleep(500);
				PasteToClipboard(myHorses[i] + " Each Way");
				i++;
				while (getKeysState()) { getKeysState(); }
			}
			else
			{
				PasteToClipboard("No more horses.");
				RepasteList(myHorses);
			}
		}
	}
}

void insertList(std::vector<std::string>& myHorses)
{
	std::string line;

	myHorses.push_back("Start");

	while (std::getline(std::cin, line))
	{
		if (line.empty()) 
		{
			break;
		}
		else
		{
			myHorses.push_back(line);
		}
	}

	myHorses.push_back("End");
}

int main()
{
	std::string tmp;
	std::vector<std::string> myHorses;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	std::cout << R"(
 _   _          _____  _____     _____         _____ _______ ______ _____  
| \ | |   /\   / ____|/ ____|   |  __ \ /\    / ____|__   __|  ____|  __ \ 
|  \| |  /  \ | |  __| (___     | |__) /  \  | (___    | |  | |__  | |__) |
| . ` | / /\ \| | |_ |\___ \    |  ___/ /\ \  \___ \   | |  |  __| |  _  / 
| |\  |/ ____ \ |__| |____) |   | |  / ____ \ ____) |  | |  | |____| | \ \ 
|_| \_/_/    \_\_____|_____/    |_| /_/    \_\_____/   |_|  |______|_|  \_\
)";
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 15);

	std::cout << "Paste nags here from the Discord channel horses" << std::endl;
	std::cout << "CTRL + v will change your clipboard to the next horse" << std::endl;
	std::cout << "Press enter twice once you have input your list" << std::endl;

	insertList(myHorses);

	pasteHorse(myHorses);
}
