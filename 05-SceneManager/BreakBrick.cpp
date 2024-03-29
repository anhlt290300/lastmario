#include "BreakBrick.h"

void BreakBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (GetTickCount64() - effect_start > BREAK_EFFECT_TIME_OUT){
		isDeleted = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void BreakBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void BreakBrick::Render()
{
	int aniId = ID_ANI_BREAK;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

BreakBrick::BreakBrick(float x, float y)
{
	this->ay = BREAK_GRAVTY;
	this->ax = 0;
	this->x = x;
	this->y = y;
}

void BreakBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BREAK_STATE_TOP_RIGHT:
		vx = BREAK_SPEED_X;
		vy = -BREAK_SPEED_Y_HIGH;
		effect_start = GetTickCount64();
		break;
	case BREAK_STATE_TOP_LEFT:
		vx = -BREAK_SPEED_X;
		vy = -BREAK_SPEED_Y_HIGH;
		effect_start = GetTickCount64();
		break;
	case BREAK_STATE_BOTTOM_LEFT:
		vx = -BREAK_SPEED_X;
		vy = -BREAK_SPEED_Y_LOW;
		effect_start = GetTickCount64();
		break;
	case BREAK_STATE_BOTTOM_RIGHT:
		vx = BREAK_SPEED_X;
		vy = -BREAK_SPEED_Y_LOW;
		effect_start = GetTickCount64();
		break;
	}
}
