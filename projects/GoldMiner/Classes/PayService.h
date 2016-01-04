#ifndef _PAYSERVICE_H_

#define _PAYSERVICE_H_
#include "cocos2d.h"
USING_NS_CC;

class PayService : public cocos2d::CCObject{
public:
	static PayService* getInstance();

	static void setCheckTrue(void);
	static void pay(int id, bool isRepeated, CCCallFunc* successFc = NULL,CCCallFunc* filedFc =NULL);
	static void exitGame(CCCallFunc* onConfirmExit = NULL);
	static bool isMusicEnabled(void);
	static void getMoreGames(void);
	
	void callSuccessFc();
	void callfailFc();
	void callOnConfirmExitFc();
private:
	static CCCallFunc* successFc;
	static CCCallFunc* failFc;
	static CCCallFunc* onConfirmExitFc;

private:
	static PayService* instance;
};

#endif