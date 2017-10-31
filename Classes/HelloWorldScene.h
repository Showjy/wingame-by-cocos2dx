#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	//float velocity;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void start_Callback(cocos2d::Ref* pSender);
	void set_Callback(cocos2d::Ref* pSender);
	void about_Callback(cocos2d::Ref* pSender);
	HelloWorld(){ Velocity = 2.0; }
	float getVelocity();
	void changeVelocity(float v);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	float Velocity;

};

#endif // __HELLOWORLD_SCENE_H__
