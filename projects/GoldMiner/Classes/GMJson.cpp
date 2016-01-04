#include "GMJson.h"

#include "json_lib.h"

#include "Global.h"

#include "Player.h"


GMJson::GMJson(void)
{
}


GMJson::~GMJson(void)
{
}

void GMJson::getSelfInformation(std::string _response)
{
	Json::Reader reader; 
	Json::Value myjson;
	//��ʼ����
	if(reader.parse(_response, myjson)){
		//����ʧ��
	}
	int index = 1;
	//�����±��ȡValueֵ
	Json::Value val = myjson["goldenMiner2Vos"];
	//��ȡjson����
	int count = val.size();

	if (count == 0)
	{
		Player::getInstance()->setChallengeAppendName(true);
	}
	else
	{
		//�������ƻ�ȡValueֵ
		ChallengeRecord newRecord = Player::getInstance()->getChallengeById();
		newRecord.level = val[0]["challengeLevel"].asInt();
		newRecord.score = val[0]["highestScore"].asLargestInt();
		newRecord.name = val[0]["playerName"].asString();
		newRecord.roleId = val[0]["roleId"].asInt();
		Player::getInstance()->updateChallenge(newRecord);
		Player::getInstance()->setChallengeAppendName(false);
	}
}

void GMJson::getChallengeDate(std::string _response)
{
	Json::Reader reader; 
	Json::Value myjson;
	//��ʼ����
	if(reader.parse(_response, myjson)){
		//����ʧ��
	}
	int index = 1;
	//�����±��ȡValueֵ
	Json::Value val = myjson["goldenMiner2Vos"];
	//��ȡjson����
	Global::getInstance()->recordsNum = val.size();
	//�������ƻ�ȡValueֵ
	for(int i = 0; i < Global::getInstance()->recordsNum; i++)
	{
		Global::getInstance()->records[i].index = val[i]["order"].asInt();
		Global::getInstance()->records[i].level = val[i]["challengeLevel"].asInt();
		Global::getInstance()->records[i].name = val[i]["playerName"].asString();
		Global::getInstance()->records[i].roleId = val[i]["roleId"].asInt();
		Global::getInstance()->records[i].score = val[i]["highestScore"].asInt();

		CCLOG("%d   %d   %s   %d   %d",
			Global::getInstance()->records[i].index ,
		Global::getInstance()->records[i].level,
		Global::getInstance()->records[i].name.c_str(),
		Global::getInstance()->records[i].roleId,
		Global::getInstance()->records[i].score);

		if (strcpy(Player::getInstance()->getImeiStr(), val[i]["imei"].asString().c_str()) == 0)
		{
			Global::getInstance()->myRecordIndex = i;
		}
	}
}