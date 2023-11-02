#pragma once

#include "GridObject.h"
#include "AStar.h"
#include "State.h"

enum Direction;

class Enemy : public GridObject
{
public:
    Enemy();
    ~Enemy();

	virtual void Draw(HDC hdc) override;

    void SetTargetPosition(Position targetPosition) { this->targetPosition = targetPosition; }
    void SetEndGridPosition(Position endGridPosition) { this->endGridPosition = endGridPosition; }
    void SetState(State* state) { this->state = state; }
    void SetIndex(int index) { this->index = index; }
    void SetRandFlag(bool randFlag) { this->randFlag = randFlag; }
    void SetDebug(bool debug) { this->debug = debug; }

    Position GetTargetPosition() { return targetPosition; }
    Position GetEndGridPosition() { return endGridPosition; }
    AStar* GetAStar() { return aStar; }
    int GetIndex() { return index; }
    int GetDetectRange() { return detectRange; }
    bool GetRandFlag() { return randFlag; }
    bool GetDebug() { return debug; }

    void Step();
    void CreateAStar(int** maps);
    void Update(PacMan* pacMan);
    void SetStayPositions(Position startPosition, Scale cellScale);
    void MoveStay(int distance);
    bool DetectedPlayer(PacMan* pacMan);

private:
    AStar* aStar;
    State* state;

    Position targetPosition;
    Position endGridPosition;
    Position stayPositions[2];

    int index;
    int detectRange;
    bool stepOrigin;
    bool randFlag;

    bool debug;
};

