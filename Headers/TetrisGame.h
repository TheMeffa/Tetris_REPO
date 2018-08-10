#pragma once
#include "BaseApp.h"
#include "Constants.h"
#include "Point.h"
#include "PerformanceCounter.h"

class TetrisGame : public BaseApp
{
public:

	typedef BaseApp Parent;
	TetrisGame();
	void Rotate(Point centralPoint);
	void MoveDown();
	bool isMovingPossible(int dX, int dY);
	void ClearOldPosition();
	void UpdatePositions();
	void SpawnNewFigure();

	void disableFigure();
	

	void checkLines();
	bool isPointBelongsTo(Point p);
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);



private: 
	bool gameIsGoing;
	float m_delay;
	int m_moveDirection;
	int m_numberOfNextFigure;
	int m_numberOfCurrentFigure;
	int m_score;
	CStopwatch m_clock;
	
	Point m_gameField[GAME_FIELD_HEIGHT*GAME_FIELD_WIDTH];

	Point m_currentFigure[4];
	Point m_previousCurrentFigure[4];
	Point m_nextFigure[4];

};