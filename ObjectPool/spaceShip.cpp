#include "stdafx.h"
#include "spaceShip.h"
#include "enemyManager.h"

spaceShip::spaceShip()
{
}


spaceShip::~spaceShip()
{
}

HRESULT spaceShip::init()
{
	_ship = IMAGEMANAGER->addImage("플레이어", "rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_ship->setX(WINSIZEX / 2);
	_ship->setY(WINSIZEY / 2 + 200);

	_missile = new missile;
	_missile->init(30, 400);

	_boy = new littleBoy;
	_boy->init(30000, 3000);

	return S_OK;
}

void spaceShip::release()
{
}

void spaceShip::update()
{
	//왼쪽 이동
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _ship->getX() > 0)
	{
		_ship->setX(_ship->getX() - 5);
	}

	//오른쪽 이동
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _ship->getX() + _ship->getWidth() < WINSIZEX)
	{
		_ship->setX(_ship->getX() + 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _ship->getY() > 0)
	{
		_ship->setY(_ship->getY() - 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _ship->getY() + _ship->getHeight() < WINSIZEY)
	{
		_ship->setY(_ship->getY() + 5);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missile->fire(_ship->getCenterX(), _ship->getY() - 20);
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_boy->fire(_ship->getCenterX(), _ship->getY() - 10);
	}

	_missile->update();
	_boy->update();

	collision();
}

void spaceShip::render()
{
	_ship->render(getMemDC(), _ship->getX(), _ship->getY());
	_missile->render();
	_boy->render();
}

void spaceShip::collision()
{
	for (int i = 0; i < _em->getVMinion().size(); i++)
	{
		for (int j = 0; j < _boy->getVBoy().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_boy->getVBoy()[j].rc, &_em->getVMinion()[i]->getRect()))
			{
				_em->removeMinion(i);
				_boy->removeBoy(j);
				break;
			}
		}
	}

}
