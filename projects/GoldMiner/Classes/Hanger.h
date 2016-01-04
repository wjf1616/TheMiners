#ifndef __HANGER_H__
#define __HANGER_H__

#include "cocos2d.h"
#include "Global.h"

class Rope;
class GameControl;

using namespace cocos2d;

#define				HANGER_FUNCTION_TYPE_NORMAL					1 // ��ͨ
#define				HANGER_FUNCTION_TYPE_THROW					2 // �ᴮ
#define				HANGER_FUNCTION_TYPE_CARRY_BOMB				3 // ץը��
#define				HANGER_FUNCTION_TYPE_BOMB					4 // ը��������Ʒ
#define				HANGER_FUNCTION_TYPE_EXCHANGE_TO_JEWEL		5 // �任������ı�ʯ
#define				HANGER_FUNCTION_TYPE_STONE_TO_GOLDEN		6 // ʯͷ�����

#define				HANGER_SPEED_PULL_NORMAL			45

enum
{
	HANGER_GET_TARFET = 10,
	HANGER_GET_NOTHING,
};



class Hanger :
	public cocos2d::CCSprite
{
public:
	Hanger(double _distanceToCentre, double _distanceToRope, double _speedAngle, int _speedSelf, int _speedScene, int _type);//, const char _name[]);//, const cocos2d::CCRect &_ccRect);
	~Hanger(void);

	virtual void onExit(void);
	Rope * getRope(void);
	void setSpeedTimes(float _times);
	int setSpeedTarget(int _speedTarget, int _speedTargetType);//����Ŀ��Թ����ٶȵ�Ӱ��
	int getStatus(void);//���ع���״̬
	int setStatus(int _status);//���ù���״̬
	//int setPullSpeed(int _pullSpeed);
	double getAngle(void);// ��ù��ӵ�ǰ�ĽǶ�
	void setAngle(double _angle);// ��ù��ӵ�ǰ�ĽǶ�
	double getCurrX(void);// ��ù��ӵĵ�ǰx
	double getCurrY(void);// ��ù��ӵĵ�ǰy
	double getDistanceToRope(void);
	double getDistanceToCentre(void);
	void resetHangerBitmap(const char _name[], double _distanceToCentre, double _distanceToRope, int _functionType);
	//unsigned char setIsHaveTarget(unsigned char _isHaveTarget);//�����Ƿ����Ŀ��
	//cocos2d::CCSprite * getHanger(void);//��ù��Ӷ���
	void doAction(float _f, GameControl * _gameControl);//���Ӷ���ִ��
	void intersectCheck(GameControl * _gameControl);
	bool getCanThrow(void);
	void appendSpeedSelf(int _append);
	int getFunctionType(void);
	void setFunctionType(int _functionType);
	void setType(int _type);

	void setPetSpeed(int _speed);
	void setSpeedAngle(double _s);
	double getSpeedAngle(void);


	// test��
	int getSpeedSelf(void);
	int getSpeedScene(void);
	void setSpeedSelf(int _s);
	void setSpeedScene(int _s);

	//void getCanThrow(void);
	int carryTargetType;// ��ǰ��ץȡ��������ͣ�û��ץȡΪ0��
	void * carryTargetPoint;// ��ǰ��ץȡ����ĵ�ַ����
private:
	Rope * rope;//���ӵ�ָ��
	cocos2d::CCSprite * zhaDanSprite;
#ifdef				GOLDEN_MINER_2_VERSION_TIME
	float tmpStatusTimeCount;
#else
	int tmpStatusTimeCount;
#endif

	bool canThrow;

	float speedTimes;
	double speedAngle;//���ٶ�
	//int pullSpeed; // ���ϵ��ٶ�
	int speedSelf;//�����Լ����ٶ�
	int speedScene;//�������ٶ�
	int speedTarget;//Ŀ��������ٶ�
	int speedTargetType;//Ŀ��������ٶ�
	int speedPet;
	int status;//״̬
	int lastStatus;// ��һ�ε�״̬
	int type;
	int functionType;
	double angle;//�Ƕ�
	double x;//��ʼx����
	double y;//��ʼy����
	double currX;//��ǰx����
	double currY;//��ǰy����
	double distanceToCentre;//���ĵ����������ʵ��ľ���
	double distanceToRope;//���ĵ�������ӽӿڵ�ľ���

	void changeAngle(void);
	void changeBitmap(void);
	void setMovePostion(GameControl * _gameControl);
	void setSwayPostion(void);
	float getSpeed(void);
};

#endif

