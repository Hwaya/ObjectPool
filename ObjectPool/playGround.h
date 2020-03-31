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

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render();	//�׸��� ���� �Լ�

	

};

