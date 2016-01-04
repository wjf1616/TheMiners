#include "NetWork.h"
#include "Player.h"

#define					GOLDEN_MINER2_GAMEID					111

NetWork * NetWork::m_NetWork = NULL;

NetWork::NetWork(void)
{
}


NetWork::~NetWork(void)
{
}

NetWork * NetWork::getInstance(void)
{
	if (m_NetWork == NULL)
	{
		m_NetWork = new NetWork();
	}

	return m_NetWork;
}

void NetWork::updateSelfChallengeDate(ChallengeRecord _record, CCObject * _pTarget, SEL_CallFuncND _pSelector)
{
	CCHttpRequest* request = new CCHttpRequest();

	char _s[256];
	//printf(_s, "http://192.168.0.238/GameDoSDK/updateRecordGoldenMiner2?imei=%ld&gameId=%d&playerName=%s&roleId=%d&challengeLevel=%d&highestScore=%d"
	//	, Player::getInstance()->getImei()
	//	, GOLDEN_MINER2_GAMEID
	//	, _record.name.c_str()
	//	, _record.roleId
	//	, _record.level
	//	, _record.score);
	sprintf(_s, "http://192.168.0.238/GameDoSDK/updateRecordGoldenMiner2?imei=%ld&gameId=%d&playerName=%s&roleId=%d&challengeLevel=%d&highestScore=%d"
		, 55555555
		, GOLDEN_MINER2_GAMEID
		, "aaa"
		, 1
		, 10
		, 1000);
	request->setUrl(_s);
	CCLog("setUrl: %s", _s);
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(_pTarget, _pSelector);

	CCHttpClient::getInstance()->send(request);
	request->release();
}

void NetWork::isHavingDate(CCObject * _pTarget, SEL_CallFuncND _pSelector)
{
	CCHttpRequest* request = new CCHttpRequest();


	char _s[256];
	//sprintf(_s, "http://192.168.0.238/GameDoSDK/getRecordGoldenMiner2Mine?imei=%ld&gameId=%d"
	//	, Player::getInstance()->getImei()
	//	, GOLDEN_MINER2_GAMEID);
	//request->setUrl(_s);
	sprintf(_s, "http://192.168.0.238/GameDoSDK/getRecordGoldenMiner2Mine?imei=%ld&gameId=%d"
		, 22222222
		, GOLDEN_MINER2_GAMEID);
	CCLog("setUrl: %s", _s);
	request->setUrl(_s);
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(_pTarget, _pSelector);

	CCHttpClient::getInstance()->send(request);
	request->release();
}

void NetWork::getChallengeDate(CCObject * _pTarget, SEL_CallFuncND _pSelector)
{
	CCHttpRequest* request = new CCHttpRequest();

	char _s[256];
	//sprintf(_s, "http://192.168.0.238/GameDoSDK/getRecordGoldenMiner2?imei=%ld&gameId=%d"
	//	, Player::getInstance()->getImei()
	//	, GOLDEN_MINER2_GAMEID);
	sprintf(_s, "http://192.168.0.238/GameDoSDK/getRecordGoldenMiner2?imei=%ld&gameId=%d"
		, 55555555
		, GOLDEN_MINER2_GAMEID);
	CCLog("setUrl: %s", _s);
	request->setUrl(_s);
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(_pTarget, _pSelector);

	CCHttpClient::getInstance()->send(request);
	request->release();
}