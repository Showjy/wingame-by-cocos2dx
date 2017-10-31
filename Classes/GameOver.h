#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class GameOver : public Layer
{public:
	static Scene* createScene();
	virtual bool init();
	void back_Callback(Ref* pSender);
	void changetimeConsumed(int time);
	GameOver()
	{
		timeConsumed = 0;
	}
	CREATE_FUNC(GameOver);

private:
	int timeConsumed;
};
#endif