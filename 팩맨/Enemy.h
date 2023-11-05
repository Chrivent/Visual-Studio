#pragma once

#include "GridObject.h"
#include "AStar.h"
#include "State.h"

enum Direction;

class Enemy : public GridObject
{
public:
    Enemy();
    ~Enemy() override;

    void Draw(HDC hdc) override;

    void SetEndGridPosition(Position endGridPosition) { this->endGridPosition = endGridPosition; }
    void SetStartGridPosition(Position startGridPosition) { this->startGridPosition = startGridPosition; }
    void SetIndex(int index) { this->index = index; }
    void SetHunter(bool hunter) { this->hunter = hunter; }
    void SetHunted(bool hunted) { this->hunted = hunted; }
    void SetEaten(bool eaten) { this->eaten = eaten; }
    void SetDebug(bool debug) { this->debug = debug; }

    AStar* GetAStar() const { return aStar; }
    int GetIndex() const { return index; }
    int GetDetectRange() const { return detectRange; }
    bool GetHunter() const { return hunter; }
    bool GetHunted() const { return hunted; }
    float GetHuntedSpeedRate() const { return huntedSpeedRate; }
    bool GetEaten() const { return eaten; }
    float GetEatenSpeedRate() const { return eatenSpeedRate; }
    bool GetDebug() const { return debug; }

    void Step();
    void Move(Pacman* pacman);
    void SetStayPositions(Position startPosition, Scale cellScale);
    void MoveInBox(Pacman* pacman);
    void MoveHunter(Pacman* pacman);
    void MoveHunted(Pacman* pacman);
    void MoveEaten(Pacman* pacman);
    void ResetHuntedTimer();
    void GridUpdateEvent(Pacman* pacman);
    void AStarMoveEvent(Pacman* pacman);
    void ChangeState(State* state, Pacman* pacman);
    void Sparkle();
    bool DetectedPlayer(Pacman* pacman) const;
    bool GridPositionIsPath(Position gridPosition, Pacman* pacman);
    bool GridPositionIsAroundPlayer(Position gridPosition, Pacman* pacman) const;

private:
    AStar* aStar;
    state* state;

    Position endGridPosition;
    Position stayPositions[2];
    Position startGridPosition;

    int index;
    int detectRange;
    bool stepOrigin;
    bool randFlag;
    bool hunter;
    bool hunted;
    int huntedTime;
    int huntedTimer;
    float huntedSpeedRate;
    bool eaten;
    float eatenSpeedRate;
    bool sparkle;
    int sparkleTime;
    int sparkleTimer;
    int score;

    bool debug;
};

