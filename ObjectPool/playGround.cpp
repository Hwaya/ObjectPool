#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 해라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
HRESULT playGround::init()
{
	gameNode::init(true);
	angle = 3.14;
	cnt = 0;
	
	ObjectPool->Init(10000);
	//tagBullet* tempBullet = ObjectPool->getNode();
	//ObjectPool->returnNode(tempBullet);
	IMAGEMANAGER->addImage("배경", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("총알", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy", "ufo.bmp", 0, 0, 530, 32, 10, 1, true, RGB(255, 0, 255));


	return S_OK;
}

//메모리 해제는 여기다 해라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::release()
{
	gameNode::release();

	//init에서 동적할당 해줬으니 릴리즈함수에서 동적할당 해제 
	SAFE_DELETE(_ship);

}

//연산은 여기다 해라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::update()
{
	gameNode::update();
	if (KEYMANAGER->isStayKeyDown(VK_SPACE)) {
		for (int i = 0; i < 100; i++) {
			angle -= 2.5f;
			tagBullet* tempBullet = ObjectPool->getObject();

			tempBullet->bulletImage = IMAGEMANAGER->findImage("총알");
			tempBullet->speed = 10;
			tempBullet->radius = tempBullet->bulletImage->getWidth() / 2;
			tempBullet->x = tempBullet->fireX = BULLETX;
			tempBullet->y = tempBullet->fireY = BULLETY;
			tempBullet->angle = angle;

			tempBullet->rc = RectMakeCenter(tempBullet->x, tempBullet->y,
				tempBullet->bulletImage->getWidth(),
				tempBullet->bulletImage->getHeight());

			bvec.push_back(tempBullet);
			cnt++;
		}
	}

	bvitr bitr = bvec.begin();
	for (; bitr != bvec.end();/*++bitr*/)
	{
		(*bitr)->x += cosf((*bitr)->angle) * (*bitr)->speed;
		(*bitr)->y += -sinf((*bitr)->angle) * (*bitr)->speed;

		(*bitr)->rc = RectMakeCenter((*bitr)->x, (*bitr)->y,
			(*bitr)->bulletImage->getWidth(),
			(*bitr)->bulletImage->getHeight());

		if ((*bitr)->x <0 || (*bitr)->x > WINSIZEX || (*bitr)->y < 0 || (*bitr)->y > WINSIZEY)
		{
			(*bitr)->angle = 0;
			(*bitr)->count = 0;
			(*bitr)->fireX = 0;
			(*bitr)->fireY = 0;
			(*bitr)->isFire = false;
			(*bitr)->radius = 0;
			(*bitr)->speed = 0;

			ObjectPool->returnObject((*bitr));
			bitr = bvec.erase(bitr);
		}

		else ++bitr;
		
		
	}
	
}

//여기다 그려라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================

	IMAGEMANAGER->findImage("배경")->render(getMemDC());


	
	bvitr bitr = bvec.begin();
	for (; bitr != bvec.end(); ++bitr)
	{
		(*bitr)->bulletImage->render(getMemDC(),
			(*bitr)->rc.left,
			(*bitr)->rc.top, 0, 0,
			(*bitr)->bulletImage->getWidth(),
			(*bitr)->bulletImage->getHeight());
	}
	char t[10000];
	sprintf_s(t, "Bullet Counter : %d",cnt);
	TextOut(getMemDC(), WINSIZEX / 2, 50, t, strlen(t));

	char poollistsize[100];
	sprintf_s(poollistsize, "Pool Size : %d", ObjectPool->GetPoolSize());
	TextOut(getMemDC(), WINSIZEX / 2, 150, poollistsize, strlen(poollistsize));

	char listsize[100];
	sprintf_s(listsize, "lock Size : %d", ObjectPool->GetLockSize());
	TextOut(getMemDC(), WINSIZEX / 2, 200, listsize, strlen(listsize));

	char vectorsize[100];
	sprintf_s(vectorsize, "Bulletvector size : %d", bvec.size());
	TextOut(getMemDC(), WINSIZEX / 2, 100, vectorsize, strlen(vectorsize));

	char actualpoolsize[100];
	sprintf_s(actualpoolsize, "Actual Pool Size : %d", ObjectPool->ActualPoolSize());
	TextOut(getMemDC(), WINSIZEX / 2, 250, actualpoolsize, strlen(actualpoolsize));

	char actuallocksize[100];
	sprintf_s(actuallocksize, "Actual Lock Size : %d", ObjectPool->ActualLockSize());
	TextOut(getMemDC(), WINSIZEX / 2, 300, actuallocksize, strlen(actuallocksize));
	//===================================================
	//딱 말했다
	_backBuffer->render(getHDC(), 0, 0);
}

