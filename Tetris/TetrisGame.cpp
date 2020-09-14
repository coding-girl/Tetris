#include "TetrisGame.h"


TetrisGame::TetrisGame() :board(boardSize), speed(0.7)
{
	mTetNext = Shape::GetRandomShape();
	StartNewGame();
}

void TetrisGame::KeyPressed(int btnCode)
{
}

void TetrisGame::UpdateF(float deltaTime)
{
	if (running)
	{
		tickTimer -= deltaTime;
		if (tickTimer < 0)
		{
			Undraw();
			if (CanFit(mTet, mObjCoord + Coord(0, 1), rot))
			{
				mObjCoord.y++;
				Draw();
			}
			else
			{
				Draw();
				ClearLines();
				SpawnTetro();
			}


			tickTimer = speed;
			RedrawBoard();
		}
	}
}

void TetrisGame::DrawRect(Coord coord, Coord size, char ch)
{
	DrawLine(coord, size.x, Axis::Horizontal, ch);
	DrawLine(coord + Coord(0, size.y), size.x, Axis::Horizontal, ch);

	DrawLine(coord, size.y, Axis::Vertical, ch);
	DrawLine(coord + Coord(size.x, 0), size.y + 1, Axis::Vertical, ch);
}

void TetrisGame::DrawLine(Coord topLeft, int length, Axis axis, char ch)
{
	Coord curr = topLeft;
	for (int i = 0; i < length; i++)
	{
		SetChar(curr.x, curr.y, ch);
		curr[axis]++;
	}
}

void TetrisGame::DrawText(int x, int y, string text)
{
}

void TetrisGame::GameOver()
{
}

void TetrisGame::StartNewGame()
{
	board.clear();
	RedrawGame();
	SpawnTetro();
	running = true;
	tickTimer = speed;
}

void TetrisGame::ClearLines()
{
}

void TetrisGame::SpawnTetro()
{
	mTet = mTetNext;
	mTetNext = Shape::GetRandomShape();
	mObjCoord = Coord(4, 0);
	rot = 0;

	Draw();
}

void TetrisGame::RedrawGame()
{
	Coord boardLoc(0, 0);
	Coord nextShapeViewLoc(boardSize.x + 1, 0);
	Coord scoreViewLoc(0, boardSize.y + 1);

	DrawRect(boardLoc, boardSize + Coord(1, 1), '#');
	DrawRect(nextShapeViewLoc, Coord(6, boardSize.y + 1), '#');
	DrawRect(scoreViewLoc, Coord(boardSize.x + 7, 5), '#');

	RedrawBoard();
}

void TetrisGame::RedrawBoard()
{
	for (Coord local; local.y < boardSize.y; local.y++)
		for (local.x = 0; local.x < boardSize.x; local.x++)
			DrawCell(local, board.get_cell(local));
}

void TetrisGame::DrawCell(Coord pt, Cell cell)
{
	SetChar(pt.x + 1, pt.y + 1, cell == Cell::Empty ? '.' : '%');
}

bool TetrisGame::CanFit(const Shape * tet, Coord pt, int rot)
{
	for (Coord local; local.y < 4; local.y++)
		for (local.x = 0; local.x < 4; local.x++)
			if (tet->IsSolid(local, rot) && (!IsInBorder(pt + local) || board[pt + local] == Cell::Filled))
				return false;

	return true;
}

void TetrisGame::Draw(Cell val)
{
	for (Coord local; local.y < 4; local.y++)
		for (local.x = 0; local.x < 4; local.x++)
			if (mTet->IsSolid(local, rot) && IsInBorder(mObjCoord + local))
				board[mObjCoord + local] = val;
}

bool TetrisGame::IsInBorder(Coord c)
{
	return c.x >= 0 && c.y >= 0 && c.x < board.get_width() && c.y < board.get_height();
}




