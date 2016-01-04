#ifndef __CARRIER_H__
#define __CARRIER_H__

#include "cocos2d.h"
#include "Global.h"
#include "Target.h"
#include "DynamicTarget.h"

class GameControl;
//
//#define			CARRIER_STATUS_MOVING						1
//#define			CARRIER_STATUS_STOP							2


class Carrier :
	public cocos2d::CCNode
{
public:
	Carrier(double _x, double _y, int _id, int _direction, int _speed);
	~Carrier(void);

	void doAction(float _f);
	void addSelfToLayer(GameControl * _gameControl);
	void addCarriedTarget(void * _target, bool _isTarget);
	bool isCarried(double _positionX, double _positionY);
	bool isCarried(void * _target);
	bool isCarriedDynamicTarget(void * _target);
	cocos2d::CCSprite * getSpriteDown(void);
	cocos2d::CCSprite * getSpriteMiddle(void);
	cocos2d::CCSprite * getSpriteUp(void);
	cocos2d::CCArray * getCarriedTarget(void);

	//void setStatus(int _status);

	void setCarrierTypeAndIndex(int _yunIndex, int _point1Scale, int _point2Scale, int _point3Scale);

	double getCurrY(void);

private:
	CCSprite * spriteDown;// ����ͼ�� 
	CCSprite * spriteMiddle;// �м�ͼ��
	CCSprite * spriteUp;// ����ͼ��
	CCArray * carriedTarget;
	CCArray * carriedTargetType;

	//int status;// ״̬

	int id;// �ƶ�����
	double currX;// down�����½�����
	double currY;// down���½�����
	double changeX;// x�ı䶯��
	double checkWidth;
	double checkHeight;
	double vectorX;// �ƶ�ֻ�������ƶ�
	int yunIndex;// ����
	int pointType;
	bool isJustChangeDirction;

	void initSelfById(void);

	void upDateSelfPosition(void);// �����Լ���λ��
	void upDateCarriedTarget(void);// ����Я����λ�ú�״̬

	void upDateCarriedStaticTarget(void);
	void upDateCarriedDynamicTarget(void);
	void setTargetPositionByPointIndex(int _pointIndex, void * _target);
	void setDynamicTargetPositionByPointIndex(int _pointIndex, void * _target);
};

#endif