#pragma once

#include "BaseApp.h"
#include "Board.h"
#include "Shape.h"

#ifdef DrawText
#undef DrawText
#endif


class TetrisGame :
	public BaseApp
{
	typedef BaseApp Parent;

private:
	static const int screenWidth = 40;
	static const int screenHeight = 25;
	const Coord screenSize = Coord(screenWidth, screenHeight);
	const Coord boardSize = Coord(15, 19);

	const Coord boardLoc = Coord((screenWidth - (boardSize.x + 7)) / 2, 1); 
	
	const wchar_t TetroChar = L'◘';




	Board board;

	int score;
	float speed;
	float tickTimer;
	bool running;

	const Shape* mTet;
	Coord mObjCoord;
	int rot;

	const Shape* mTetNext;

public:
	TetrisGame();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);

private:
	void GameOver();
	void StartNewGame();

	void ClearLines();
	void SpawnTetro();

	bool TryMoveTo(int x, int y, int rot);

	inline void ClearScreen() { ClearRect(Rect(Coord(), screenSize)); }
	void ClearRect(Rect);
	void RedrawGame();
	void RedrawBoard();
	void DrawCell(Coord, Cell);

	bool CanFit(const Shape*, Coord, int);
	void DrawTetro(const Shape* shape, Coord coord, int rot, char clearColor = 0);
	void DrawTetroOnBoard();
	//inline void Undraw() { Draw(Cell::Empty); }

	void SetChar(Coord, wchar_t);
	void SetChar(int x, int y, wchar_t);
	void DrawRect(Coord, Coord, char);
	void DrawLine(Coord topLeft, int length, Axis Axis, char);
	void DrawText(int x, int y, string text);




	bool IsInBorder(Coord);
	inline bool IsInBorder(int x, int y) { return IsInBorder(Coord{ x,y }); }
};

