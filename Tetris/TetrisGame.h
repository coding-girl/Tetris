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

public:
	TetrisGame();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);


private:
};

