#ifndef __JEWELSKILLSPRITE_H__
#define __JEWELSKILLSPRITE_H__

#include "cocos2d.h"
#include "Global.h"


#define SKILL_ID_JEWEL_BALL_COUNT					4// 球 碰撞3次
#define SKILL_ID_JEWEL_BALL_SPEED					10// 球 速度

class GameControl;
class Hanger;

enum
{
	JEWEL_SKILL_SPRITE_STATUS_NORMAL,// 技能待触发状态
	JEWEL_SKILL_SPRITE_STATUS_DOING,// 技能正在触发状态
	JEWEL_SKILL_SPRITE_STATUS_FINISH// 技能释放完毕
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
	int ballCollideCount;// 技能球碰撞的次数
	double currX;
	double currY;
	double startY;
	double vectorX;
	double vectorY;
};

#define SKILL_ID_JEWEL_MAGNET_DEGREE				60// 吸铁石30°   // 7.16 更新技能为吸收区域的所有东西 并且范围为60°
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

	int jewelSkillTime;// 宝石技能的持续时间
#ifdef								GOLDEN_MINER_2_VERSION_TIME
	float jewelSkillTimeCount;// 宝石技能释放时间计时
#else
	int jewelSkillTimeCount;// 宝石技能释放时间计时
#endif

	float speed;
};


#define SKILL_ID_JEWEL_GOURD_DEGREE					45// 葫芦60° // 7.16 更新技能为葫芦娃技能
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

	int jewelSkillTime;// 宝石技能的持续时间
#ifdef								GOLDEN_MINER_2_VERSION_TIME
	float jewelSkillTimeCount;// 宝石技能释放时间计时
#else
	int jewelSkillTimeCount;// 宝石技能释放时间计时
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

	int jewelSkillTime;// 宝石技能的持续时间
#ifdef								GOLDEN_MINER_2_VERSION_TIME
	float jewelSkillTimeCount;// 宝石技能释放时间计时
#else
	int jewelSkillTimeCount;// 宝石技能释放时间计时
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
	int jewelSkillTime;// 宝石技能的持续时间
#ifdef								GOLDEN_MINER_2_VERSION_TIME
	float jewelSkillTimeCount;// 宝石技能释放时间计时
	float jewelSkillVoiceTime;
#else
	int jewelSkillTimeCount;// 宝石技能释放时间计时
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
	int jewelSkillTime;// 宝石技能的持续时间
	int jewelSkillTimeCount;// 宝石技能释放时间计时

	cocos2d::CCParticleSystemQuad* mSystem ;

	cocos2d::CCArray * hangers;
};

#endif