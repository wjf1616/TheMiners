#ifndef									__NET_WORK__
#define									__NET_WORK__

#include "Global.h"

#include "cocos2d.h"

#include "cocos-ext.h"  
//#include "../extensions/network/HttpClient.h"  
//#include "../extensions/network/HttpRequest.h"  
//#include "../extensions/network/HttpResponse.h"  

USING_NS_CC;
USING_NS_CC_EXT;

class NetWork
{
public:
	~NetWork(void);

	static NetWork * getInstance(void);

	void updateSelfChallengeDate(ChallengeRecord _record, CCObject * _pTarget, SEL_CallFuncND _pSelector);

	void isHavingDate(CCObject * _pTarget, SEL_CallFuncND _pSelector);

	void getChallengeDate(CCObject * _pTarget, SEL_CallFuncND _pSelector);
private:
	NetWork(void);
	static NetWork * m_NetWork;
};

#endif

