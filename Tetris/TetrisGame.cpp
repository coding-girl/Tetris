#include "TetrisGame.h"

#include <ctime>

TetrisGame::TetrisGame(): BaseApp(screenWidth, screenHeight),
	board(boardSize), speed(0.7)
{
	srand(time(0));

	StartNewGame();
}

void TetrisGame::KeyPressed(int btnCode)
{
	if (running)
	{
		if (btnCode == 77 || btnCode == 75)
			TryMoveTo(mObjCoord.x + ((btnCode == 77) ? 1 : -1), mObjCoord.y, rot);

		if (btnCode == 32)
			TryMoveTo(mObjCoord.x, mObjCoord.y, (rot + 1) % 4);

		if (btnCode == 80)
		{
			while (TryMoveTo(mObjCoord.x, mObjCoord.y + 1, rot));
			SpawnTetro();
		}
	}
	else
	{
		if (btnCode == 13)
			StartNewGame();
	}
}

void TetrisGame::UpdateF(float deltaTime)
{
	if (running)
	{
		tickTimer -= deltaTime;
		if (tickTimer < 0)
		{
			if (!TryMoveTo(mObjCoord.x, mObjCoord.y + 1, rot))
				SpawnTetro();

			tickTimer = speed;
		}
	}
	RedrawGame();
}

void TetrisGame::SetChar(Coord pt, wchar_t ch)
{
	Parent::SetChar(pt.x, pt.y, ch);
}

void TetrisGame::SetChar(int x, int y, wchar_t ch)
{
	Parent::SetChar(x, y, ch);
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
		SetChar(curr, ch);
		curr[axis]++;
	}
}

void TetrisGame::DrawText(int x, int y, string text)
{
	for (int i = 0; i < text.size(); i++)
		SetChar(x + i, y, text[i]);
}

void TetrisGame::GameOver()
{
	running = false;
}

void TetrisGame::StartNewGame()
{
	mTet = mTetNext = nullptr;
	board.clear();
	SpawnTetro();
	RedrawGame();
	running = true;
	tickTimer = speed;
	score = 0;
}

void TetrisGame::ClearLines()
{
	for (int j = boardSize.y - 1; j >= 0; j--)
	{
		bool anyEmpty = false;
		for (int i = 0; i < boardSize.x && !anyEmpty; i++)
			anyEmpty |= (board.get_cell(i, j) != Cell::Filled);

		if (!anyEmpty)
		{
			board.ClearRow(j);
			score += 4;
			j++;
		}
	}
}

void TetrisGame::SpawnTetro()
{
	if (mTet)
	{
		DrawTetroOnBoard();
		ClearLines();
		mTet = mTetNext;
	}
	else mTet = Shape::GetRandomShape();

	mObjCoord = Coord(4, 0);
	rot = 0;
	if (!CanFit(mTet, mObjCoord, rot))
		GameOver();

	mTetNext = Shape::GetRandomShape();
	tickTimer = speed;
}

bool TetrisGame::TryMoveTo(int x, int y, int rot)
{
	if (CanFit(mTet, Coord(x, y), rot))
	{
		mObjCoord = Coord(x, y);
		this->rot = rot;
		return true;
	}
	return false;
}

void TetrisGame::ClearRect(Rect rect)
{
	for (Coord local; local.y < rect.h; local.y++)
		for (local.x = 0; local.x < rect.w; local.x++)
			SetChar(rect.topLeft + local, ' ');
}

void TetrisGame::RedrawGame()
{
	ClearScreen();

	//Coord boardLoc(screenWidth / 2 - (screenWidth - (boardSize.x + 7)) / 2, 0);
	Coord nextShapeViewLoc = boardLoc + Coord(boardSize.x + 1, 0);
	Coord scoreViewLoc = boardLoc + Coord(0, boardSize.y + 1);

	DrawRect(boardLoc, boardSize + Coord(1, 1), '#');
	DrawRect(nextShapeViewLoc, Coord(6, boardSize.y + 1), '#');
	DrawRect(scoreViewLoc, Coord(boardSize.x + 7, 4), '#');

	RedrawBoard();

	DrawTetro(mTetNext, nextShapeViewLoc + Coord(1, 3) - boardLoc, 0, ' ');

	DrawText(scoreViewLoc.x + 3, scoreViewLoc.y + 2, "Score: " + to_string(score));


	if (!running)
	{
		Rect msgBox(4, boardSize.y * 2 / 3, screenSize.x - 8, 7);
		ClearRect(msgBox);
		DrawText(msgBox.x + 4, msgBox.y + 1, "You lost!");
		DrawText(msgBox.x + 4, msgBox.y + 2, "Your final score: " + to_string(score));
	}
}

void TetrisGame::RedrawBoard()
{
	for (Coord local; local.y < boardSize.y; local.y++)
		for (local.x = 0; local.x < boardSize.x; local.x++)
			DrawCell(local, board.get_cell(local));

	DrawTetro(mTet, mObjCoord, rot);
}

void TetrisGame::DrawCell(Coord pt, Cell cell)
{
	SetChar(pt + boardLoc + 1, cell == Cell::Empty ? '.' : TetroChar);
}

bool TetrisGame::CanFit(const Shape * tet, Coord pt, int rot)
{
	for (Coord local; local.y < 4; local.y++)
		for (local.x = 0; local.x < 4; local.x++)
			if (tet->IsSolid(local, rot) && (!IsInBorder(pt + local) || board[pt + local] == Cell::Filled))
				return false;

	return true;
}

void TetrisGame::DrawTetro(const Shape* shape, Coord coord, int rot, char clearColor)
{
	for (Coord local; local.y < 4; local.y++)
		for (local.x = 0; local.x < 4; local.x++)
			if (shape->IsSolid(local, rot))
				SetChar(coord + local + boardLoc + 1, TetroChar);
			else if (clearColor != 0)
				SetChar(coord + local + boardLoc + 1, clearColor);
}

void TetrisGame::DrawTetroOnBoard()
{
	for (Coord local; local.y < 4; local.y++)
		for (local.x = 0; local.x < 4; local.x++)
			if (mTet->IsSolid(local, rot) && IsInBorder(mObjCoord + local))
				board[mObjCoord + local] = Cell::Filled;
}

bool TetrisGame::IsInBorder(Coord c)
{
	return c.x >= 0 && c.y >= 0 && c.x < board.get_width() && c.y < board.get_height();
}




