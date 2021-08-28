
#include "stdafx.h"
#include "TicTacToe.h"


//---------------------------------
/// Crear console
inline void clearScr()
{
	std::system("cls");
}
//---------------------------------
int main()
{
	TIC_TAC_TOE tttGame;

	InitGame(tttGame);
	clearScr();
	DrawGame(tttGame);

#ifndef TEST
#else
	/**
	int TestCoord[][2] = 
	{
		{0, 0},
		{1, 2},//
		{1, 1},
		{1, 2},//
		{2, 2},
	};
	/**/
	int TestCoord[][2] =
	{
		{ 0, 2 },
		{ 1, 0 },//
		{ 1, 2 },
		{ 1, 1 },//
		{ 2, 2 },
	};
	/**
	int TestCoord[][2] =
	{
		{ 0, 0 },
		{ 0, 1 },//
		{ 0, 2 },
		{ 1, 0 },//
		{ 1, 1 },
		{ 1, 2 },//
		{ 2, 0 },
		{ 2, 1 },//
		{ 2, 2 },
	};
	/**
	int TestCoord[][2] =
	{
		{ 0, 0 },
		{ 0, 1 },//
		{ 1, 1 },
		{ 1, 2 },//
		{ 2, 1 },
		{ 2, 0 },//
		{ 1, 0 },
		{ 2, 2 },//
		{ 0, 2 },
	};
	/**/
	int nCountStep = 0;

	int aTestSumX[FIELD_TOE + 1]{ 0 };
	int aTestSumY[FIELD_TOE + 1]{ 0 };
#endif

	do {

		Coord c;
#ifndef TEST
#else
		c.x = TestCoord[nCountStep][0];
		c.y = TestCoord[nCountStep][1];
		nCountStep++;
#endif
		char cCharacter = '_';
		if (tttGame.m_nStep & 1)
		{
			// Step first player
#ifndef TEST
			c = getCoord(tttGame);
#endif
			tttGame.m_ppField[c.y][c.x] = tttGame.m_tttGamerOne;

			cCharacter = tttGame.m_tttGamerOne;
		}
		else
		{
#ifndef TEST
			// Two player
			//c = getCoord(tttGame);
			// AI
			c = getCoordAi(tttGame);
#endif
			// Step second player
			tttGame.m_ppField[c.y][c.x] = tttGame.m_tttGamerTwo;

			cCharacter = tttGame.m_tttGamerTwo;
		}


#ifndef TEST
		tttGame.stepUp(c, cCharacter);
#else
		// the sum elements by line
		aTestSumX[c.x] += cCharacter;
		// the sum elements by diagonal
		if (c.x == c.y)
			aTestSumX[tttGame.m_Size] += cCharacter;

		// the sum elements by colomn
		aTestSumY[c.y] += cCharacter;
		// the sum elements by diagonal
		if ((c.x + c.y) == (tttGame.m_Size - 1))
			aTestSumY[tttGame.m_Size] += cCharacter;
#endif
		
		clearScr();
		DrawGame(tttGame);
		tttGame.m_nStep++;

		// Check winner
		tttGame.m_Progress = getWon(tttGame);

	} while (tttGame.m_Progress == IN_PROGRESS);

	// Congratation winner
	Congrats(tttGame);

	DeinitGame(tttGame);
	system("pause");
	return 0;
}