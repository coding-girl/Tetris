#include "TetrisGame.h"


TetrisGame::TetrisGame()
{
	StartNewGame();
}

void TetrisGame::KeyPressed(int btnCode)
{
}

void TetrisGame::UpdateF(float deltaTime)
{
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
	RedrawGame();
}

void TetrisGame::ClearLines()
{
}

void TetrisGame::SpawnTetro()
{
}

void TetrisGame::RedrawGame()
{
	Coord boardLoc(0, 0);
	Coord nextShapeViewLoc(boardSize.x + 1, 0);
	Coord scoreViewLoc(0, boardSize.y + 1);

	DrawRect(boardLoc, boardSize + Coord(1, 1), '#');
	DrawRect(nextShapeViewLoc, Coord(6, boardSize.y + 1), '#');
	DrawRect(scoreViewLoc, Coord(boardSize.x + 7, 5), '#');
}

bool TetrisGame::CanFit(const Shape *, Coord, int)
{
	return false;
}

void TetrisGame::Draw(bool clear)
{
}

bool TetrisGame::IsInBorder(Coord c)
{
	return c.x >= 0 && c.y >= 0 && c.x < board.get_width() && c.y < board.get_height();
}




