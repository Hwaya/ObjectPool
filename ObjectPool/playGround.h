#pragma once
#include "gameNode.h"
#include "spaceShip.h"
#include "enemyManager.h"

#define BULLETX WINSIZEX/2
#define BULLETY WINSIZEY/2

class playGround : public gameNode
{
private:
	float angle;
	spaceShip* _ship;
	enemyManager* _em;
	vector<tagBullet*> bvec;
	typedef vector<tagBullet*>::iterator bvitr;
	int cnt;
public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용 함수
	virtual void render();	//그리기 전용 함수

	

};

