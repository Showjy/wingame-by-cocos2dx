#ifndef __STARTGAME_SCENE_H__
#define __STARTGAME_SCENE_H__

#include "cocos2d.h"
#include<vector>
USING_NS_CC;
class StartGame : public Layer
{public:
	static Scene* createScene();
	virtual bool init();
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void moveBackgroud(float dt);
	void removeObstacle(Sprite* s);
	void removeSun(Sprite* s);
	void collisionPlayerAndObstacle(float dt);
	void collisionPlayerAndSun(float dt);
	void obstacleMove(float dt);
	void initObstacle(float dt);
	void initSun(float dt);
	void back_Callback(Ref* pSender);
	float getVelocity();
	int gettimeConsumed();
	void addtimeConsumed(float dt);
	void changeVelocity(float v);
	void ChangeisCollision(float dt);
	void setPhyWorld(PhysicsWorld* world){ m_world = world; }
	CREATE_FUNC(StartGame);
	StartGame(){ Velocity = 0; timeConsumed = 0; sunNum = 0; isCollision = true; }
private:
	Label* ScoreLabel,* SunLabel;
	Sprite* player;
	Vector<Sprite*> team;
	Sprite* backgroud1, *backgroud2;
	Sprite* sun;
	Size size;
	float Velocity;
	int timeConsumed;
	int sunNum;
	bool isCollision;
	MoveBy* moveby;
	PhysicsWorld* m_world;
};

#endif