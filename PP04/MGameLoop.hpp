#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>

using namespace std;

namespace MuSeoun_Engine
{
	void MoveCursor(short x, short y)
	{
		COORD position = { x , y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	}

	void SetCursorState(bool visible)
	{
		CONSOLE_CURSOR_INFO consoleCursorInfo;
		consoleCursorInfo.bVisible = visible;
		consoleCursorInfo.dwSize = 1;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
	}

	struct Transform
	{
		int x, y;
	};

	class Player
	{
	public:
		Transform transform;

		Player()
		{
			transform.x = 10;
			transform.y = 15;
		}

		void draw()
		{
			MoveCursor(transform.x, transform.y);
			cout << "P";
		}
	};

	class MGameLoop
	{
	private :
		bool _isGameRunning;	
		Player *p;

	public :
		MGameLoop() 
		{
			_isGameRunning = false;
		}
		~MGameLoop() {}

		void Run()
		{
			_isGameRunning = true;

			Initialize();

			while (_isGameRunning)
			{
				Input();
				Update();
				Render();
			}

			Release();
		}
		void Stop()
		{
			_isGameRunning = false;
		}

	private :
		
		void Initialize()
		{
			SetCursorState(false);
			p = new Player();
		}
		void Release() 
		{
			delete(p);
		}

		void Input()
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8001)
			{ 
				p->transform.y = 10;
			}
			else 
			{
				p->transform.y = 15;
			}

		}
		void Update()
		{
			
		}
		void Render()
		{		
			chrono::system_clock::time_point startRenderTimePoint = chrono::system_clock::now();
			system("cls");
			//cout << "Rendering...";
			chrono::duration<double> renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			
			p->draw();
			
			MoveCursor(10, 20);
			cout << "Rendering speed : " << renderDuration.count() << "sec" << endl;

			int remainingFrameTime = 100 - (int)(renderDuration.count() * 1000.0);
			if (remainingFrameTime > 0)
				this_thread::sleep_for(chrono::milliseconds(remainingFrameTime));
		}

				
		
	};

	


	

}