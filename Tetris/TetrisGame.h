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
	const Coord boardSize = Coord(9, 16);
	
	const char TetroChar = '%';




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

	void DrawRect(Coord, Coord, char);
	void DrawLine(Coord topLeft, int length, Axis Axis, char);
	void DrawText(int x, int y, string text);

	inline Board* get_board() { return &board; }
	inline const Shape* get_next_shape() { return mTetNext; }
	inline int get_score() { return score; }

private:
	void GameOver();
	void StartNewGame();

	void ClearLines();
	void SpawnTetro();

	bool TryMoveTo(int x, int y, int rot);

	void RedrawGame();
	void RedrawBoard();
	void DrawCell(Coord, Cell);

	bool CanFit(const Shape*, Coord, int);
	void DrawTetro(const Shape* shape, Coord coord, int rot);
	void DrawTetroOnBoard();
	//inline void Undraw() { Draw(Cell::Empty); }




	bool IsInBorder(Coord);
	inline bool IsInBorder(int x, int y) { return IsInBorder(Coord{ x,y }); }
};

