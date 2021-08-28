#pragma once

#include <iostream>

#include <chrono>
#include <stdlib.h>

#include <random>
#include <ctime>

using namespace std;

/// Размер поля крестики-нолики
/// Default the size  of field tic-tac-toe
#define FIELD_TOE  3

#define ONE_PLAYER "One player"

#define TWO_PLAYER "Two player"

/// Перечисление поля для крестики-нолики
enum eTIC_TAC_TOE {
	eTic   = 'X',
	eTac   = '0',
	eEmpty = '_'
};

enum Progress {
	IN_PROGRESS,
	WON_HUMAN,
	WON_AI,
	DRAW
};


#pragma pack(push, 1)
/// Счёт в игре
struct COUNT_TTT
{
	uint32_t dwFirst  = 0;
	uint32_t dwSecond = 0;
	uint32_t dwDraw   = 0;
};

// Coordinate
struct Coord {
	size_t y{ 0 };
	size_t x{ 0 };

	Coord(size_t yIn = 0, size_t xIn = 0)
	{
		y = yIn;
		x = xIn;
	}
};

/// struct for game to Х/0
struct TIC_TAC_TOE {
	/*
	/// значения полей
	uint8_t m_aucFieldToy[FIELD_TOE][FIELD_TOE] = {
	{ eEmpty, eEmpty, eEmpty },
	{ eEmpty, eEmpty, eEmpty },
	{ eEmpty, eEmpty, eEmpty },
	};
	*/

	eTIC_TAC_TOE **m_ppField;

	/// summary vector for define won of X
	size_t *m_dwSumWonX;
	/// summary vector for define won of Y
	size_t *m_dwSumWonY;

	size_t m_Size = FIELD_TOE;

	/// Счёт в игре
	/// Score in the game
	COUNT_TTT m_Count;

	/// Ход игрока: 0/1 соответственно
	int m_nStep;

	/// Игра в процессе: true/false
	Progress m_Progress;

	/// First gamer by step X or 0, true/false exactly
	//bool m_bSign;
	eTIC_TAC_TOE m_tttGamerOne;
	eTIC_TAC_TOE m_tttGamerTwo;

	// Sum plus
	void stepUp(Coord c, char cCharacter)
	{
		// the sum elements by line
		m_dwSumWonX[c.x] += cCharacter;
		// the sum elements by diagonal
		if (c.x == c.y)
			m_dwSumWonX[m_Size] += cCharacter;

		// the sum elements by colomn
		m_dwSumWonY[c.y] += cCharacter;
		// the sum elements by diagonal
		if ((c.x + c.y) == (m_Size - 1))
			m_dwSumWonY[m_Size] += cCharacter;
	}

	// Sum minus
	void stepDown(Coord c, char cCharacter)
	{
		// the sum elements by line
		m_dwSumWonX[c.x] -= cCharacter;
		// the sum elements by diagonal
		if (c.x == c.y)
			m_dwSumWonX[m_Size] -= cCharacter;

		// the sum elements by colomn
		m_dwSumWonY[c.y] -= cCharacter;
		// the sum elements by diagonal
		if ((c.x + c.y) == (m_Size - 1))
			m_dwSumWonY[m_Size] -= cCharacter;
	}
};
#pragma pack(pop)


//---------------------------------
uint32_t __fastcall getRandomNum(int32_t min, int32_t max);

//---------------------------------
/// Init memory for game
void __fastcall InitGame(TIC_TAC_TOE &game);

//---------------------------------
/// Delete memory for game
void __fastcall DeinitGame(TIC_TAC_TOE &game);

//---------------------------------
/// Draw Game into console
void __fastcall DrawGame(const TIC_TAC_TOE &game);

//---------------------------------
/// Define winner
Progress __fastcall getWon(const TIC_TAC_TOE game);

//---------------------------------
/// Step by player
Coord __fastcall getCoord(TIC_TAC_TOE &tttGame);

//---------------------------------
/// Step by AI
Coord __fastcall getCoordAi(TIC_TAC_TOE &game);

//---------------------------------
/// Congratation
void __fastcall Congrats(const TIC_TAC_TOE &game);