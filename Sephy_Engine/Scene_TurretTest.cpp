#include "stdafx.h"
#include "Scene_TurretTest.h"


Scene_TurretTest::Scene_TurretTest()
{
	m_targetX = 0;
	m_targetY = 0;
}


Scene_TurretTest::~Scene_TurretTest()
{
	for (auto iter : m_vBullet)
	{
		SAFE_DELETE(iter->bullet);
		SAFE_DELETE(iter);
	}
	SAFE_DELETE(m_pShip);


	releaseAll();
}

void Scene_TurretTest::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
		

	m_pShip = new CBattle_Ship;
	m_pShip->initialize(this, "Z1");
	m_pShip->setCurrentX(200);
	m_pShip->setCurrentY(600);
	m_pShip->setShipActive(true);
}



void Scene_TurretTest::release()
{
}

void Scene_TurretTest::ai()
{
}

void Scene_TurretTest::collisions()
{
}

void Scene_TurretTest::render()
{
	RECT rc = RectMake(m_targetX, m_targetY, 20, 20);
	graphics->drawRect(rc, 2.0f, graphicsNS::RED);
	m_pShip->render();	
	graphics->spriteBegin();
	for (auto iter : m_vBullet)
	{
		iter->bullet->drawRect();
		iter->bullet->draw();
	}
	graphics->spriteEnd();
}

void Scene_TurretTest::releaseAll()
{

	Game::releaseAll();
	return;
}

void Scene_TurretTest::resetAll()
{

	Game::resetAll();
	return;
}

void Scene_TurretTest::update()
{
	float cameraSpeed = 20;
	if (input->isKeyDown('W'))
	{
		m_pShip->moveY(cameraSpeed);
		for (auto iter : m_vBullet)
		{
			iter->bullet->moveY(cameraSpeed);
			iter->startY += cameraSpeed;
			iter->targetY += cameraSpeed;
		}
		m_targetY += cameraSpeed;
	}
	if (input->isKeyDown('S'))
	{
		m_pShip->moveY(-cameraSpeed);
		for (auto iter : m_vBullet)
		{
			iter->bullet->moveY(-cameraSpeed);
			iter->startY -= cameraSpeed;
			iter->targetY -= cameraSpeed;
		}
		m_targetY -= cameraSpeed;
	}
	if (input->isKeyDown('A'))
	{
		m_pShip->moveX(cameraSpeed);
		for (auto iter : m_vBullet)
		{
			iter->bullet->moveX(cameraSpeed);
			iter->startX += cameraSpeed;
			iter->targetX += cameraSpeed;
		}
		m_targetY += cameraSpeed;
	}
	if (input->isKeyDown('D'))
	{
		m_pShip->moveX(-cameraSpeed);
		for (auto iter : m_vBullet)
		{
			iter->bullet->moveX(-cameraSpeed);
			iter->startX -= cameraSpeed;
			iter->targetX -= cameraSpeed;
		}
		m_targetY -= cameraSpeed;
	}

	if (input->getMouseRButton())
	{
		m_targetX = input->getMouseX();
		m_targetY = input->getMouseY();
	}

	if (input->getMouseLButton())
	{
		std::string bullet = "Bullet_White";
		Bullet* tempBullet = new Bullet;
		tempBullet->startX = m_pShip->getCurrentCenterX();
		tempBullet->startY = m_pShip->getCurrentCenterY();
		tempBullet->currentX = m_pShip->getCurrentCenterX();
		tempBullet->currentY = m_pShip->getCurrentCenterY();
		tempBullet->targetX = m_targetX;
		tempBullet->targetY = m_targetY;
		tempBullet->bullet = new Image;
		tempBullet->bullet->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture(bullet));
		tempBullet->bullet->setX(m_pShip->getCurrentCenterX());
		tempBullet->bullet->setY(m_pShip->getCurrentCenterY());

		tempBullet->PreFunction();

		m_vBullet.emplace_back(tempBullet);
		input->setMouseLButton(false);
	}


	for (auto iter : m_vBullet)
	{
		iter->MoveFunction(frameTime);
		//iter->MoveToAngle(frameTime);
	}
}

void Bullet::PreFunction()
{
	float BulletSpeed = 1000.f; //기준 초구탄속
	fg = 500.0f; //기준 중력

	// 초구탄속 & 중력 & 타겟 좌표를 이용한 각도 계산
	float a = (fg * powf(targetX - startX, 2.0)) / (2 * powf(BulletSpeed, 2.0));
	float b = -(targetX - startX);
	float c = a + (startY - targetY);
	float D = sqrtf(b * b - 4 * a * c);

	float angle1 = 0.f;
	float angle2 = 0.f;

	// 허수제거
	if (D <= 0)
	{
		angle1 = 0.0f;
		angle2 = 0.0f;
	}

	angle1 = fabs(atan2f(-b + D, a + a));
	angle2 = fabs(atan2f(-b - D, a + a));

	// 두 각도중 작은 값 사용
	if (angle1 > angle2)
	{
		D = angle2;
		angle2 = angle1;
		angle1 = D;
	}

	angle1 = fabs(angle1 * 57.2957951); // 45도 이하의 각도값 ex) 1~45
										// END 초구탄속 & 중력 & 타겟 좌표를 이용한 각도 계산

	aimAngle = D3DXToRadian(angle1); //함포 각도

									 //체공 시간
	if (targetX > startX)
	{
		arriveTime = (targetX - startX) / (BulletSpeed * cos(aimAngle));
	}
	else if (targetX < startX)
	{
		arriveTime = fabs(startX - targetX) / (BulletSpeed * cos(aimAngle));
	}

	fV_X = ((targetX - startX) / arriveTime); //x값 변화
	fV_Y = (startY - targetY) / arriveTime + fg * arriveTime / 2.0; //y값 변화

}

bool Bullet::MoveFunction(float frameTime)
{
	deltaTime += frameTime;

	if (deltaTime > arriveTime)
		return true;

	float physicsX = fV_X * deltaTime;
	float physicsY = (fV_Y * deltaTime) - ((fg * deltaTime * deltaTime) / 2);

	bullet->setX(startX + physicsX);
	bullet->setY(startY + -physicsY);

	return false;
}