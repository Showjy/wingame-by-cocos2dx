#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class About : public Layer
{public:
	static Scene* createScene();
	virtual bool init();
	void back_Callback(Ref* pSender);
	CREATE_FUNC(About);
};
#endif