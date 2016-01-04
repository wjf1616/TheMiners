#ifndef __JEWELSKILLSPRITE_H__
#define __JEWELSKILLSPRITE_H__

#include "cocos2d.h"
#include "Global.h"


#define SKILL_ID_JEWEL_BALL_COUNT					4// �� ��ײ3��
#define SKILL_ID_JEWEL_BALL_SPEED					10// �� �ٶ�

class GameControl;
class Hanger;

enum
{
	JEWEL_SKILL_SPRITE_STATUS_NORMAL,// ���ܴ�����״̬
	JEWEL_SKILL_SPRITE_STATUS_DOING,// �������ڴ���״̬
	JEWEL_SKILL_SPRITE_STATUS_FINISH// �����ͷ����
};

class JewelSkillSprite
{
public:
	JewelSkillSprite(void);
	~JewelSkillSprite(void);

	int getStatus(void);
	virtual void doSkill(GameControl * _gameControl);
	virtual void updateSkill(float _f, GameControl * _gameControl);
	virtual void releaseSkill(GameControl * _gameControl);

protected:
	int status;

};

class JewelSkillBall :
	public JewelSkillSprite
	, public cocos2d::CCSprite
{
public:
	JewelSkillBall(GameControl * _gameControl, Hanger * _hanger);
	~JewelSkillBall(void);

	virtual void doSkill(GameControl * _gameControl);
	virtual void updateSkill(float _f, GameControl * _gameControl);
	virtual void releaseSkill(GameControl * _gameControl);

private:

	Hanger * hanger;
	cocos2d::CCParticleSystemQuad * mySystem;
	int ballCollideCount;// ��������ײ�Ĵ���
	double currX;
	double currY;
	double startY;
	double vectorX;
	double vectorY;
};

#define SKILL_ID_JEWEL_MAGNET_DEGREE				60// ����ʯ30��   // 7.16 ���¼���Ϊ������������ж��� ���ҷ�ΧΪ60��
#define SKILL_ID_JEWEL_MAGNET_QUENE_DISTANCE		130
#define SKILL_ID_JEWEL_MAGNET_ABSORB_TIME			180

class JewelSkillMagnet :
	public JewelSkillSprite
	, public cocos2d::CCSprite
{
public:
	JewelSkillMagnet(GameControl * _gameControl, Hanger * _hanger);
	~JewelSkillMagnet(void);

	virtual void doSkill(GameControl * _gameControl);
	virtual void updateSkill(float _f, GameControl * _gameControl);
	virtual void releaseSkill(GameControl * _gameControl);

private:
	cocos2d::CCParticleSystemQuad * mySystem;
	cocos2d::CCSprite *	quene;

	Hanger * hanger;

	int jewelSkillTime;// ��ʯ���ܵĳ���ʱ��
#ifdef								GOLDEN_MINER_2_VERSION_TIME
	float jewelSkillTimeCount;// ��ʯ�����ͷ�ʱ���ʱ
#else
	int jewelSkillTimeCount;// ��ʯ�����ͷ�ʱ���ʱ
#endif

	float speed;
};


#define SKILL_ID_JEWEL_GOURD_DEGREE					45// ��«60�� // 7.16 ���¼���Ϊ��«�޼���
#define SKILL_ID_JEWEL_GOURD_QUENE_DISTANCE			130
#define SKILL_ID_JEWEL_GOURD_ABSORB_TIME			180

class JewelSkillGourd :
	public JewelSkillSprite
	, public cocos2d::CCSprite
{
public:
	JewelSkillGourd(GameControl * _gameControl, Hanger * _hanger);
	~JewelSkillGourd(void);

	virtual void doSkill(GameControl * _gameControl);
	virtual void updateSkill(float _f, GameControl * _gameControl);
	virtual void releaseSkill(GameControl * _gameControl);

private:
	cocos2d::CCParticleSystemQuad * mySystem;
	cocos2d::CCSprite *	quene;

	Hanger * hanger;

	int jewelSkillTime;// ��ʯ���ܵĳ���ʱ��
#ifdef								GOLDEN_MINER_2_VERSION_TIME
	float jewelSkillTimeCount;// ��ʯ�����ͷ�ʱ���ʱ
#else
	int jewelSkillTimeCount;// ��ʯ�����ͷ�ʱ���ʱ
#endif

	float speed;
};

class JewelSkillDizzy :
	public JewelSkillSprite
{
public:
	JewelSkillDizzy(GameControl * _gameControl);
	~JewelSkillDizzy(void);

	virtual void doSkill(GameControl * _gameControl);
	virtual void updateSkill(float _f, GameControl * _gameControl);
	virtual void releaseSkill(GameControl * _gameControl);

private:
	cocos2d::CCParticleSystemQuad * mySystem;

	int jewelSkillTime;// ��ʯ���ܵĳ���ʱ��
#ifdef								GOLDEN_MINER_2_VERSION_TIME
	float jewelSkillTimeCount;// ��ʯ�����ͷ�ʱ���ʱ
#else
	int jewelSkillTimeCount;// ��ʯ�����ͷ�ʱ���ʱ
#endif
};

class JewelSkillDrop :
	public JewelSkillSprite
{
public:
	JewelSkillDrop(GameControl * _gameControl);
	~JewelSkillDrop(void);

	virtual void doSkill(GameControl * _gameControl);
	virtual void updateSkill(float _f, GameControl * _gameControl);
	virtual void releaseSkill(GameControl * _gameControl);

private:

	cocos2d::CCLabelAtlas * awardNum;
	int award;
	int jewelSkillTime;// ��ʯ���ܵĳ���ʱ��
#ifdef								GOLDEN_MINER_2_VERSION_TIME
	float jewelSkillTimeCount;// ��ʯ�����ͷ�ʱ���ʱ
	float jewelSkillVoiceTime;
#else
	int jewelSkillTimeCount;// ��ʯ�����ͷ�ʱ���ʱ
#endif
	cocos2d::CCParticleSystemQuad* mSystem ;

	cocos2d::CCArray * drops;
};

class JewelSkillFiveHanger :
	public JewelSkillSprite
{
public:
	JewelSkillFiveHanger(GameControl * _gameControl);
	~JewelSkillFiveHanger(void);

	virtual void doSkill(GameControl * _gameControl);
	virtual void updateSkill(float _f, GameControl * _gameControl);
	virtual void releaseSkill(GameControl * _gameControl);

private:
	int jewelSkillTime;// ��ʯ���ܵĳ���ʱ��
	int jewelSkillTimeCount;// ��ʯ�����ͷ�ʱ���ʱ

	cocos2d::CCParticleSystemQuad* mSystem ;

	cocos2d::CCArray * hangers;
};

#endif