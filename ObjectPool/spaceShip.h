#pragma once
#include "gameNode.h"
#include "bullets.h"

class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;
	missile* _missile;
	littleBoy* _boy;

	enemyManager* _em;

public:
	spaceShip();
	~spaceShip();
	//함수 모두 드래그 후에 ALT + ENTER C C ENTER
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision();

	image* getShipImage() { return _ship; }

	void setMemoryAddressLink(enemyManager* em) { _em = em; }
};

