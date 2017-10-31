#ifndef __SETOPTION_SCENE_H__
#define __SETOPTION_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class Setoption : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	void back_Callback(Ref* pSender);
	void class1(Ref* pSender);
	void class2(Ref* pSender);
	CREATE_FUNC(Setoption);
};
#endif