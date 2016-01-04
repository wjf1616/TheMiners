#ifndef __GATE_H__
#define __GATE_H__

#include "cocos2d.h"
#include "Global.h"
#include "Target.h"
#include "DynamicTarget.h"
#include "Role.h"
#include "Carrier.h"

class GameControl;

class Gate
{
public:
	~Gate(void);
	/*
		gameIdΪ0��ʱ��ȷ�����ǲ��Թؿ��Ĺ̶�����ֵ
		ͨ��gameId��ȷ����ȡtxm���ļ�
	*/
	static Gate * getInstance(int _gateId, GameControl * _gameControl);

	cocos2d::CCArray * getTargets(void);//Ŀ��ָ�뼯��
	cocos2d::CCArray * getDynamicTargets(void);//Ŀ��ָ�뼯��
	cocos2d::CCArray * getCarriers(void);
	//cocos2d::CCTMXTiledMap * getMap(void);
	//void setIsTiming(bool _isTiming);
	void setIsDynamicTargetMoving(bool _isDynamicTargetMoving);
	void setIsCarrierMoving(bool _isCarrierMoving);
	int getGoldenNum(void);
	int getTargetTotalNum(void);
	int getCanGoundDynamicTargetNum(void);
	//int * getCarriersLines(void);
	bool addHideTarget(Target * _target);
	bool addHideDynamicTarget(DynamicTarget * _dynamicTarget);

	void doAction(float _f, GameControl * _gameControl);

private:

	Gate(void);

	//Global * global;
	int gateId;// �ؿ���Ӧ��id��
	//cocos2d::CCTMXTiledMap * map;//���صĶ�Ӧ��tmx�ļ�
	cocos2d::CCArray * carriers;// �ƶ�ļ���
	cocos2d::CCArray * targets;//Ŀ��ָ�뼯��
	cocos2d::CCArray * dynamicTargets;//Ŀ��ָ�뼯��

	cocos2d::CCArray * hideTarget;// ���صľ�̬Ŀ�������
	cocos2d::CCArray * hideDynamicTarget;// ���صľ�̬Ŀ�������

	bool isCarrierMoving;// �ƶ��Ƿ��ƶ�
	bool isDynamicTargetMoving;// �ƶ��Ĺ����ܷ��ƶ�
	int goldenNum;// ʣ����ӵ�����
	int targetTotalNum;// ��̬�Ͷ�̬�ܹ���Ŀ�������
	int dynamicTargetNum;// ���Ա���«��ȡ���������
	int needValue;
	//int carriersLines[50];
	DynamicTargetControl * dynamicTargetControl;

	void initSelf(GameControl * _gameControl, cocos2d::CCTMXTiledMap * map);

};

#endif

