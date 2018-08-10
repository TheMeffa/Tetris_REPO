#include "TetrisGame.h"
#include <conio.h>
#include <strsafe.h>
TetrisGame::TetrisGame() : Parent(17, 25)
{
	for (int i = 0; i < POINTS_MAX; i++) {
		m_currentFigure[i].x = 0;
		m_currentFigure[i].y = 0;
	}
	m_numberOfNextFigure = (m_clock.Time() + rand()) % FIGURE_COUNT;
	for (int i = 0; i < GAME_FIELD_WIDTH; i++){
		for (int j = 0; j < GAME_FIELD_HEIGHT; j++){

			//-------Field borders------//
			if (i == 0 || i == GAME_FIELD_WIDTH - 1 ||
				j == 0 || j == GAME_FIELD_HEIGHT - 1){
				m_gameField[j * GAME_FIELD_WIDTH + i].setAll(i, j, BORDER);
				SetChar(i, j, L'+');
			}
			else
				m_gameField[j * GAME_FIELD_WIDTH + i].setAll(i, j, EMPTY_FIELD);
		}

		SpawnNewFigure();
	}
		m_delay = 0;
		m_moveDirection = 0;
		m_score = 0;
}

void TetrisGame::UpdateF(float deltaTime)
{
	if (gameIsGoing){
		m_delay += deltaTime;
		if (m_delay >= MAX_DELAY){
			MoveDown();
			m_delay = 0;
		}
		for (int i = 0; i < POINTS_MAX; i++){
			ClearOldPosition();
			m_currentFigure[i].x += m_moveDirection;
			UpdatePositions();
		}

		for (int i = 0; i < GAME_FIELD_HEIGHT * GAME_FIELD_WIDTH; i++){
			switch (m_gameField[i].pt){
			case EMPTY_FIELD:
				SetChar(m_gameField[i].x, m_gameField[i].y, L' ');
				break;
			case BORDER:
				SetChar(m_gameField[i].x, m_gameField[i].y, L'+');
				break;
			case BLOCK:
				SetChar(m_gameField[i].x, m_gameField[i].y, L'#');
				break;
			case PLAYER_FIGURE:
				SetChar(m_gameField[i].x, m_gameField[i].y, L'#');
				break;
			default:
				SetChar(m_gameField[i].x, m_gameField[i].y, L'?');
				break;
			}
		}

		for (int i = 0; i < POINTS_MAX; i++){
			SetChar(m_nextFigure[i].x, m_nextFigure[i].y, L'#');
		}
		
		TCHAR  buff[15];
		StringCchPrintf(buff, 15, TEXT("Score: %d"), m_score);
		int i = 0;
		while (buff[i] != '\0'){

			SetChar(i, GAME_FIELD_HEIGHT , (wchar_t)buff[i]);
			i++;
		}
		m_moveDirection = 0;
	}
	else {
		TCHAR  buff[30];
		StringCchPrintf(buff, 15, TEXT("GameOver!"), m_score);
		int i = 0;
		while (buff[i] != '\0'){
			SetChar(i, GAME_FIELD_HEIGHT, (wchar_t)buff[i]);
			i++;
		}
		StringCchPrintf(buff, 15, TEXT("Score: %d"), m_score);
		 i = 0;
		while (buff[i] != '\0'){
			SetChar(i, GAME_FIELD_HEIGHT + 1, (wchar_t)buff[i]);
			i++;
		}
		SetConsoleTitle(L"GameOver!");
	}
}



void TetrisGame::KeyPressed(int btnCode)
{
	
	switch (btnCode){
	case BUTTON_DOWN:
		MoveDown();
		break;
	case BUTTON_LEFT:

		for (int i = 0; i < POINTS_MAX; i++) {
			if (m_currentFigure[i].x - 1 > 0 &&
				m_gameField[(m_currentFigure[i].y) * GAME_FIELD_WIDTH + (m_currentFigure[i].x - 1)].pt != BLOCK){
				
				m_moveDirection = -1;
			}
			else {
				m_moveDirection = 0;
				break;
			}
		}
		break;
	case BUTTON_RIGHT:
		for (int i = 0; i < POINTS_MAX; i++) {
			if (m_currentFigure[i].x + 1 < GAME_FIELD_WIDTH - 1 &&
				m_gameField[(m_currentFigure[i].y) * GAME_FIELD_WIDTH + (m_currentFigure[i].x + 1)].pt != BLOCK){

				m_moveDirection = 1;
			}
			else {
				m_moveDirection = 0;
				break;
			}
		}
		break;
	case SPACE:
		if (m_numberOfCurrentFigure != SQUARE)
		Rotate(m_currentFigure[1]);
		break;
	default:
		break;
	}	
	

}

void TetrisGame::Rotate(Point centralPoint)
{
	Point temp[4];
	
	for (int i = 0; i < POINTS_MAX; i++) {
		temp[i] = m_currentFigure[i];
		int xTemp = m_currentFigure[i].y - centralPoint.y;
		int yTemp = m_currentFigure[i].x - centralPoint.x;
		Point p(centralPoint.x - xTemp, centralPoint.y + yTemp);
		if (GetChar(centralPoint.x - xTemp, centralPoint.y + yTemp) == L' ' || isPointBelongsTo(p)) {
			temp[i].x = centralPoint.x - xTemp;
			temp[i].y = centralPoint.y + yTemp;
		}
		else return;
		
	}
	
	for (int i = 0; i < POINTS_MAX; i++){
		ClearOldPosition();
		m_currentFigure[i] = temp[i] ;
		UpdatePositions();
	}
	
	
}

void TetrisGame::UpdatePositions()
{
	for (int i = 0; i < POINTS_MAX; i++) {
		m_gameField[m_currentFigure[i].y * GAME_FIELD_WIDTH + m_currentFigure[i].x].setAll(m_currentFigure[i].x, m_currentFigure[i].y, PLAYER_FIGURE);
	}
}

void TetrisGame::ClearOldPosition()
{
	for (int i = 0; i < POINTS_MAX; i++) {
		m_gameField[m_currentFigure[i].y * GAME_FIELD_WIDTH + m_currentFigure[i].x].setAll(m_currentFigure[i].x, m_currentFigure[i].y, EMPTY_FIELD);
	}
}

void TetrisGame::MoveDown()
{
	
	if (isMovingPossible(0, 1)){
		
		for (int i = 0; i < POINTS_MAX; i++) {
			ClearOldPosition();
			m_currentFigure[i].y++;
			UpdatePositions();
		}
	}
	else {
		disableFigure();
		SpawnNewFigure();
		}
}

bool TetrisGame::isMovingPossible(int dX, int dY)
{
	bool isPossible = false;
	for (int i = 0; i < POINTS_MAX; i++) {
		if (m_gameField[(m_currentFigure[i].y + dY) * GAME_FIELD_WIDTH + (m_currentFigure[i].x + dX)].pt == BORDER ||
			m_gameField[(m_currentFigure[i].y + dY) * GAME_FIELD_WIDTH + (m_currentFigure[i].x + dX)].pt == BLOCK){
			

					isPossible = false;
					break;
		}
		else {
 			isPossible = true;
			
		}
	}
	return isPossible;
}

void TetrisGame::SpawnNewFigure()
{
	
	m_numberOfCurrentFigure = m_numberOfNextFigure;
	for (int i = 0; i < POINTS_MAX; i++){
		//------Creating new figure-----------//
		m_currentFigure[i].x = Figures[m_numberOfNextFigure][i] % 2 + TETRIS_FIELD / 2;
		m_currentFigure[i].y = Figures[m_numberOfNextFigure][i] / 2 + 1;

		//------Cleaning next figure showing place----//
		SetChar(m_nextFigure[i].x, m_nextFigure[i].y, L' ');
	}	
	//UpdatePositions();
	m_numberOfNextFigure = (m_clock.Time() + rand()) % 7;
	for (int i = 0; i < POINTS_MAX; i++){
		////------Creating next figure-----------//

		m_nextFigure[i].x = Figures[m_numberOfNextFigure][i] % 2 + TETRIS_FIELD / 2;
		m_nextFigure[i].y = Figures[m_numberOfNextFigure][i] / 2 + GAME_FIELD_HEIGHT + 1;
	}
		
}

void TetrisGame::disableFigure()
{
	for (int i = 0; i < POINTS_MAX; i++)
	{
		m_gameField[m_currentFigure[i].y * GAME_FIELD_WIDTH + m_currentFigure[i].x].setAll(m_currentFigure[i].x, m_currentFigure[i].y, BLOCK);
		if (m_currentFigure[i].y <= 1)
			gameIsGoing = false;
	}
	checkLines();
}

void TetrisGame::checkLines()
{
	int counter;

	for (int i = 0; i < GAME_FIELD_HEIGHT * GAME_FIELD_WIDTH; i += GAME_FIELD_WIDTH){
		counter = 0; 
		for (int j = 1; j < GAME_FIELD_WIDTH - 1 ; j++){
			if (m_gameField[i + j].pt == BLOCK)
				counter++;
			else continue;

			if (counter == TETRIS_FIELD) {
				m_score += GAME_FIELD_WIDTH;
				for (int k = 1; k < GAME_FIELD_WIDTH - 1; k++) {
					m_gameField[i + k].pt = EMPTY_FIELD;
				}
				for (int c = i; c > 0; c --){
					if (m_gameField[c].pt != BORDER)
						m_gameField[c + GAME_FIELD_WIDTH].pt = m_gameField[c].pt;
				}
			}
		}
	}
}

bool TetrisGame::isPointBelongsTo(Point p)
{
	for (int i = 0; i < POINTS_MAX; i++) {
		if (p == m_currentFigure[i]) {
			return true;
		}
	}
	return false;
}

