#include "Role.h"
#include "GameControl.h"
#include "Global.h"
#include "Explosive.h"
#include "Alignment.h"
#include "JewelSkillSprite.h"

USING_NS_CC;
using namespace cs;

#define				SKILL_SPRITE_HEIGHT				55
#define				SKILL_SPRITE_WIDTH				54

#define				NORMAL_DISTANCE_TO_CENTER			32
#define				NORMAL_DISTANCE_TO_ROPE				10//13
#define				TANGSENG_DISTANCE_TO_CENTER			43
#define				TANGSENG_DISTANCE_TO_ROPE			18//21
#define				SUNWUKONG_DISTANCE_TO_CENTER		45
#define				SUNWUKONG_DISTANCE_TO_ROPE			12//15
#define				SHAHESHANG_DISTANCE_TO_CENTER		41
#define				SHAHESHANG_DISTANCE_TO_ROPE			15//17
#define				ZHUBAJIE_DISTANCE_TO_CENTER			59
#define				ZHUBAJIE_DISTANCE_TO_ROPE			20//22
#define				XIAOLONGNV_DISTANCE_TO_CENTER		46
#define				XIAOLONGNV_DISTANCE_TO_ROPE			18//20
#define				HULUWA_ICE_DISTANCE_TO_CENTER		46
#define				HULUWA_ICE_DISTANCE_TO_ROPE			18//20
#define				HULUWA_FIRE_DISTANCE_TO_CENTER		46
#define				HULUWA_FIRE_DISTANCE_TO_ROPE		18//20

#define				TANGSENG_SWAY_SPEED					3//2
#define				SUNWUKONG_SWAY_SPEED				5//3
#define				ZHUBAJIE_SWAY_SPEED					6//4
#define				SHASENG_SWAY_SPEED					3//3
#define				XIAOLONGNV_SWAY_SPEED				4//2
#define				HULUWA_SWAY_SPEED					4//4


//#define				ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME					// 冷却技能时间是否包括释放技能的时间

/*******************************************
	放绳子	0
	收绳子	1
	开心	2
	大哭	3
	待机	4
********************************************/
/************************************************************************/
/*	              Role                                                  */
/************************************************************************/

Role::Role(void)
{
	skillTime = 15 * 60;
	skillTimeCount = 0;
	skillTimeLeftCount = 0;
	happyTimeCount = 0;
	//skillCountTmp = 0;
	hanger = NULL;
	exchangeHangerEffect = NULL;
	
	autorelease();
}


Role::~Role(void)
{
	CC_SAFE_RELEASE(hanger);
	CC_SAFE_RELEASE(skillSprite);
	CC_SAFE_RELEASE(skillSprite2);
	CC_SAFE_RELEASE(liuGuang);
	CC_SAFE_RELEASE(alignment);
}

Role * Role::getInstance(int _type, GameControl * _gameControl, double _x, double _y, double _centreX, double _centreY, double _scale)
{
	Role  * role = NULL;

	switch(_type)
	{
	case ROLE_TYPE_TANGSENG:
		// 加载
		cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tangseng", "", "flash/tangseng/tangseng.png", "flash/tangseng/tangseng.plist", "flash/tangseng/skeleton.xml");
		role = new Tangseng();
		role->setArmature(Armature::create("tangseng"));
		role->type = _type;
		role->initSelf(_x, _y, _centreX, _centreY, _scale);
		role->initSkill(15 * 60, 30 *60, ROLE_SKILL_STATUS_CANSKILL);
		role->hanger = new Hanger(NORMAL_DISTANCE_TO_CENTER, NORMAL_DISTANCE_TO_ROPE, TANGSENG_SWAY_SPEED, 9, Global::getInstance()->getSceneSpeedByMapId(_gameControl->getCurrMapId()), 0);
		role->hanger->initWithFile("youxi/gouzi.png");
		role->liuGuang = new Sensitization(SENSITIZATION_TYPE_CIRCULAR);
		role->skillSprite = CCSprite::create("youxi/dianshicj.png");
		role->skillSprite2 = CCSprite::create("youxi/dianshicj1.png");
		break;
	case ROLE_TYPE_SUNWUKONG:
		cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("wukong", "", "flash/wukong/wukong.png", "flash/wukong/wukong.plist", "flash/wukong/skeleton.xml");
		role = new Sunwukong();
		role->setArmature(Armature::create("wukong"));
		role->type = _type;
		role->initSelf(_x, _y, _centreX, _centreY, _scale);
		role->initSkill(6 * 60, 30 *60, ROLE_SKILL_STATUS_CANSKILL);
		role->hanger = new Hanger(NORMAL_DISTANCE_TO_CENTER, NORMAL_DISTANCE_TO_ROPE, SUNWUKONG_SWAY_SPEED, 18, Global::getInstance()->getSceneSpeedByMapId(_gameControl->getCurrMapId()), 0);
		role->hanger->initWithFile("youxi/gouzi.png");
		role->liuGuang = new Sensitization(SENSITIZATION_TYPE_CIRCULAR);
		role->skillSprite = CCSprite::create("youxi/sjjingzhi.png");
		role->skillSprite2 = CCSprite::create("youxi/sjjingzhi1.png");
		break;
	case ROLE_TYPE_ZHUBAJIE:
		ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("bajie", "", "flash/bajie/bajie.png", "flash/bajie/bajie.plist", "flash/bajie/skeleton.xml");
		role = new Zhubajie();
		role->setArmature(Armature::create("bajie"));
		role->type = _type;
		role->initSelf(_x, _y, _centreX, _centreY, _scale);
		role->initSkill(15 * 60, 50 *60, ROLE_SKILL_STATUS_CANSKILL);
		role->hanger = new Hanger(NORMAL_DISTANCE_TO_CENTER, NORMAL_DISTANCE_TO_ROPE, ZHUBAJIE_SWAY_SPEED, 15, Global::getInstance()->getSceneSpeedByMapId(_gameControl->getCurrMapId()), 0);
		role->hanger->initWithFile("youxi/gouzi.png");
		role->liuGuang = new Sensitization(SENSITIZATION_TYPE_CIRCULAR);
		role->skillSprite = CCSprite::create("youxi/dahai.png");
		role->skillSprite2 = CCSprite::create("youxi/dahai1.png");
		break;
	case ROLE_TYPE_SHAHESHANG:
		ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("shaseng", "", "flash/shaseng/shaseng.png", "flash/shaseng/shaseng.plist", "flash/shaseng/skeleton.xml");
		role = new Shaheshang();
		role->setArmature(Armature::create("shaseng"));
		role->type = _type;
		role->initSelf(_x, _y, _centreX, _centreY, _scale);
		role->initSkill(15 * 60, 30 *60, ROLE_SKILL_STATUS_CANSKILL);
		role->hanger = new Hanger(NORMAL_DISTANCE_TO_CENTER, NORMAL_DISTANCE_TO_ROPE, SHASENG_SWAY_SPEED, 12, Global::getInstance()->getSceneSpeedByMapId(_gameControl->getCurrMapId()), 0);
		role->hanger->initWithFile("youxi/gouzi.png");
		role->liuGuang = new Sensitization(SENSITIZATION_TYPE_CIRCULAR);
		role->skillSprite = CCSprite::create("youxi/jingque.png");
		role->skillSprite2 = CCSprite::create("youxi/jingque1.png");
		break;
	case ROLE_TYPE_XIAOLONGNV:
		ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("xiaolongnv", "", "flash/xiaolongnv/xiaolongnv.png", "flash/xiaolongnv/xiaolongnv.plist", "flash/xiaolongnv/skeleton.xml");
		role = new Xiaolongnv();
		role->setArmature(Armature::create("xiaolongnv"));
		role->type = _type;
		role->initSelf(_x, _y, _centreX, _centreY, _scale);
		role->initSkill(15 * 60, 15 *60, ROLE_SKILL_STATUS_CANSKILL);
		role->hanger = new Hanger(NORMAL_DISTANCE_TO_CENTER, NORMAL_DISTANCE_TO_ROPE, XIAOLONGNV_SWAY_SPEED, 15, Global::getInstance()->getSceneSpeedByMapId(_gameControl->getCurrMapId()), 0);
		role->hanger->initWithFile("youxi/gouzi.png");
		role->liuGuang = new Sensitization(SENSITIZATION_TYPE_CIRCULAR);
		role->skillSprite = CCSprite::create("youxi/haixingshouhu.png");
		role->skillSprite2 = CCSprite::create("youxi/haixingshouhu1.png");
		break;
	case ROLE_TYPE_HULUWA:
#ifdef									GOLDEN_MINER2_FLASH_FRAME
		ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fuluwa", "", "flash/huluwa/huluwa.png", "flash/huluwa/huluwa.plist", "flash/huluwa/skeleton.xml");
		role = new HuLuWa();
		role->setArmature(Armature::create("fuluwa"));
#else
		ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("huluwa", "", "flash/huluwa/huluwa.png", "flash/huluwa/huluwa.plist", "flash/huluwa/skeleton.xml");
		role = new HuLuWa();
		role->setArmature(Armature::create("huluwa"));
#endif
		role->type = _type;
		role->initSelf(_x, _y, _centreX, _centreY, _scale);
		role->initSkill(15 * 60, 50 *60, ROLE_SKILL_STATUS_CANSKILL);
		role->hanger = ((HuLuWa *)role)->initHangers(_gameControl);
		role->liuGuang = new Sensitization(SENSITIZATION_TYPE_CIRCULAR);
		role->skillSprite = CCSprite::create("youxi/baohulu.png");
		role->skillSprite2 = CCSprite::create("youxi/baohulu1.png");
		break;
	default:
		break;
	}
	
	role->alignment = new Alignment();
	role->alignment->retain();
	role->skillSprite->retain();
	role->skillSprite2->retain();
	role->hanger->retain();
	role->liuGuang->retain();

	role->liuGuang->setVisible(true);
	role->liuGuang->setPosition(ccp(734,105));
	_gameControl->addChild(role->liuGuang, LAYER_ORDER_CONTROL + 1);
	role->skillSprite->setPosition(ccp(731,103));
	_gameControl->addChild(role->skillSprite, LAYER_ORDER_CONTROL + 1);
	role->skillSprite2->setPosition(ccp(731,103));
	role->skillSprite2->setVisible(false);
	_gameControl->addChild(role->skillSprite2, LAYER_ORDER_CONTROL + 1);
	_gameControl->addChild(role->armature, LAYER_ORDER_CONTROL);
	_gameControl->addChild(role->alignment, LAYER_ORDER_CONTROL - 1);
#ifdef							GOLDEN_MINER2_FLASH_FRAME
	_gameControl->addChild(role->gunLun, LAYER_ORDER_CONTROL);
	_gameControl->addChild(role->hanger->getRope(), LAYER_ORDER_CONTROL+1);
	_gameControl->addChild(role->hanger, LAYER_ORDER_CONTROL+1);
#else
	_gameControl->addChild(role->hanger->getRope(), LAYER_ORDER_CONTROL);
	_gameControl->addChild(role->hanger, LAYER_ORDER_CONTROL);
#endif
	_gameControl->addChild(role->roleHide, LAYER_ORDER_CONTROL+2);

	if (BIG_GATE_TYPE_LINGSHAN == (_gameControl->getCurrMapId()%10-1))
	{
		// 云朵关人物也要加云
#ifdef							GOLDEN_MINER2_FLASH_FRAME
		CCSprite * spriteDown = CCSprite::create("tmx/yun1.png");
		spriteDown->setPosition(ccp(role->armature->getPositionX() + spriteDown->getContentSize().width/2-65, role->armature->getPositionY() + spriteDown->getContentSize().height/2 - 35));
		CCSprite * spriteUp = CCSprite::create("tmx/yun3.png");
		spriteUp->setPosition(ccp(role->armature->getPositionX() + spriteUp->getContentSize().width/2-65, role->armature->getPositionY() - spriteUp->getContentSize().height/2 - 35)); 
		_gameControl->addChild(spriteDown, LAYER_ORDER_CONTROL-2);// 云朵的下层
		_gameControl->addChild(spriteUp, LAYER_ORDER_CONTROL-2);// 云朵的上层
#else
		CCSprite * spriteDown = CCSprite::create("tmx/yun1.png");
		spriteDown->setPosition(ccp(role->armature->getPositionX() + spriteDown->getContentSize().width/2 + 20, role->armature->getPositionY() + spriteDown->getContentSize().height/2 - 35));
		CCSprite * spriteUp = CCSprite::create("tmx/yun3.png");
		spriteUp->setPosition(ccp(role->armature->getPositionX() + spriteUp->getContentSize().width/2 + 20, role->armature->getPositionY() - spriteUp->getContentSize().height/2 - 35)); 
		_gameControl->addChild(spriteDown, LAYER_ORDER_CONTROL-2);// 云朵的下层
		_gameControl->addChild(spriteUp, LAYER_ORDER_CONTROL-2);// 云朵的上层
#endif
	}

	return role;
}

void Role::doAction(float _f, GameControl * _gameControl)
{
	if(status == ROlE_STATUS_CARTOON)
	{
		// 预留cocosbuilder的动画处理
	}
	else
	{
		hanger->doAction(_f, _gameControl);
		liuGuang->doAction(_f);

		if (Global::getInstance()->getHangerStatus() == HANGER_STATUS_PULL_UNHAVING && status != ROLE_STATUS_PULL_UNHAVING)
		{// 保持拉的的状态相同
			setStatus(ROLE_STATUS_PULL_UNHAVING);
		}

		if (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING)
		{
			if (status == ROLE_STATUS_PULL_HAVING)
			{
				setStatus(ROLE_STATUS_GETTHING);
				happyTimeCount = 0;
			}
			else if (status == ROLE_STATUS_PULL_UNHAVING)
			{
				setStatus(ROLE_STATUS_GETNOTHING);
			}
		}
		if (status == ROLE_STATUS_GETTHING)
		{
#ifdef								GOLDEN_MINER_2_VERSION_TIME 
			happyTimeCount += _f;
			if (happyTimeCount >= 1)
			{
				setStatus(ROLE_STATUS_NORMARL);
			}
#else
			happyTimeCount++;
			if (happyTimeCount == 60)
			{
				setStatus(ROLE_STATUS_NORMARL);
			}
#endif
		}

		if(exchangeHangerEffect != NULL)
		{
			if (exchangeHangerEffect->doAction(_f))
			{
				_gameControl->removeChild(exchangeHangerEffect,true);
				exchangeHangerEffect = NULL;
			}
		}

		doActionSkill(_f, _gameControl);
	}
}

void Role::doActionSkill(float _f, GameControl * _gameControl)
{
	CCRepeat * repeat;
	CCSequence * sequence;
	switch(skillStatus)
	{
	case ROLE_SKILL_STATUS_SKILLING:
		//if (skillCountTmp == 0)
		//{
#ifdef								GOLDEN_MINER_2_VERSION_TIME
		skillTimeCount += _f;
		if ((skillTimeCount*SCHEDULE_TIMES >= (skillTime - 60*3)) && ((skillTimeCount - _f*SCHEDULE_TIMES) <= (skillTime - 60*3)))
		{
			sequence = CCSequence::create(CCFadeTo::create(0.5f, 255*0.3),CCFadeTo::create(0.5f, 255*1),NULL);
			repeat = CCRepeat::create(sequence, skillTime/SCHEDULE_TIMES- skillTimeCount);
			_gameControl->role->getHanger()->runAction(repeat);
		}

#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeCount*SCHEDULE_TIMES)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft-skillTimeCount*SCHEDULE_TIMES)/skillTimeLeft));
#endif
		if (skillTimeCount*SCHEDULE_TIMES >= skillTime)
		{
			skillTimeCount = 0;
#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
			skillTimeLeftCount = skillTimeCount*SCHEDULE_TIMES; 
#else
			skillTimeLeftCount = 0; 
#endif
			releaseSkill(_gameControl);
			skillStatus = ROLE_SKILL_STATUS_COOLING;
			liuGuang->setVisible(false);
			// 冷却动画
			// 技能钩子变化
		}
#else
		skillTimeCount++;
		if (skillTimeCount == skillTime - 60*3)
		{
			sequence = CCSequence::create(CCFadeTo::create(0.5f, 255*0.3),CCFadeTo::create(0.5f, 255*1),NULL);
			repeat = CCRepeat::create(sequence, 3);
			_gameControl->role->getHanger()->runAction(repeat);
		}

#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeCount)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft-skillTimeCount)/skillTimeLeft));
#endif
		if (skillTimeCount >= skillTime)
		{
			skillTimeCount = 0;
#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
			skillTimeLeftCount = skillTime; 
#else
			skillTimeLeftCount = 0; 
#endif
			releaseSkill(_gameControl);
			skillStatus = ROLE_SKILL_STATUS_COOLING;
			liuGuang->setVisible(false);
			// 冷却动画
			// 技能钩子变化
		}
#endif
		//}
		//else
		//{
		//	skillCountTmp--;
		//}

		break;
	case ROLE_SKILL_STATUS_COOLING:
#ifdef								GOLDEN_MINER_2_VERSION_TIME
		skillTimeLeftCount += _f;
		if (skillTimeLeftCount*SCHEDULE_TIMES >= skillTimeLeft)
		{
			skillTimeLeftCount = 0;
			skillStatus = ROLE_SKILL_STATUS_CANSKILL;
			liuGuang->setVisible(true);
		}
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeLeftCount*SCHEDULE_TIMES)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft - skillTimeLeftCount*SCHEDULE_TIMES)/skillTimeLeft));
#else
		skillTimeLeftCount++;
		if (skillTimeLeftCount >= skillTimeLeft)
		{
			skillTimeLeftCount = 0;
			skillStatus = ROLE_SKILL_STATUS_CANSKILL;
			liuGuang->setVisible(true);
		}
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeLeftCount)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft - skillTimeLeftCount)/skillTimeLeft));
#endif
		break;
	case ROLE_SKILL_STATUS_CANSKILL:
		skillSprite2->setVisible(false);
		break;
	default:
		break;
	}
}
	
void Role::throwHanger(GameControl * _gameControl)
{
}

bool Role::canDoExplosive(void)
{
	return true;
}
	
void Role::doExplosive(GameControl * _gameControl)
{
}

void Role::releaseExplosive(GameControl * _gameControl)
{

}

void Role::appendHangerSpeed(int _speed)
{

}

void Role::doSkill(GameControl *gameControl)
{//释放技能   先播动画  等动画播完了才变成释放技能状态
	skillStatus = ROLE_SKILL_STATUS_SKILLING;
	liuGuang->setVisible(false);
	skillSprite2->setVisible(true);
}

void Role::releaseSkill(GameControl *gameControl)
{
	exchangeHangerEffect->toNormal();
}

Hanger * Role::getHanger(void)
{
	return hanger;
}

void Role::setStatus(int _status)
{
	status = _status;

#ifdef					GOLDEN_MINER2_FLASH_FRAME
	switch(status)
	{
	case ROLE_STATUS_NORMARL:
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		CCLOG("ROLE_STATUS_NORMARL");
		break;
	case ROLE_STATUS_THROW:
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		CCLOG("ROLE_STATUS_THROW");
		break;
	case ROLE_STATUS_PULL_HAVING:// 拉到东西
		CCLOG("ROLE_STATUS_PULL_HAVING");
	case ROLE_STATUS_PULL_UNHAVING:
		// 拉的动作
		CCLOG("ROLE_STATUS_PULL_UNHAVING");
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		break;
	case ROLE_STATUS_GETTHING:
		armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		CCLOG("ROLE_STATUS_GETTHING");
		break;
	case ROLE_STATUS_GETNOTHING:// 没有抓到东西
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		CCLOG("ROLE_STATUS_GETNOTHING");
		break;
	case ROLE_STATUS_FAIL:
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		CCLOG("ROLE_STATUS_FAIL");
		break;
	default:
		break;
	}
#else
	switch(status)
	{
	case ROLE_STATUS_NORMARL:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		break;
	case ROLE_STATUS_THROW:
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		break;
	case ROLE_STATUS_PULL_HAVING:// 拉到东西
	case ROLE_STATUS_PULL_UNHAVING:
		// 拉的动作
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		break;
	case ROLE_STATUS_GETTHING:
		armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		break;
	case ROLE_STATUS_GETNOTHING:// 没有抓到东西
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		break;
	case ROLE_STATUS_FAIL:
		armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		break;
	default:
		break;
	}
#endif
}

int Role::getSkillStatus(void)
{
	return skillStatus;
}

int Role::getType(void)
{
	return type;
}

void Role::setSkillVisible(bool _b)
{
	if (_b)
	{
		liuGuang->setVisible(true);
		skillSprite->setVisible(true);
		skillSprite2->setVisible(false);
	}
	else
	{
		liuGuang->setVisible(false);
		skillSprite->setVisible(false);
		skillSprite2->setVisible(false);
	}
}

void Role::setIsHaveAlignment(bool _b)
{
	isHaveAlignment = _b;

	alignment->setVisible(_b);
}

bool Role::getIsHaveAlignment(void)
{
	return isHaveAlignment;
}

Alignment * Role::getAlignment(void)
{
	return alignment;
}

cs::Armature* Role::getArmature(void)
{
	return armature;
}

void Role::setArmature(cs::Armature* _armature)
{
	armature = _armature;
}

void Role::initSelf(double _x, double _y, double _centreX, double _centreY, double _scale)
{
	roleHide = CCSprite::create("youxi/di.png");
	roleHide->setScale(_scale);
#ifdef							GOLDEN_MINER2_FLASH_FRAME
	armature->setScale(_scale);
	//armature->getDisplayRenderNode()->setZOrder(LAYER_ORDER_DYNAMIC_TARGET);
	//armature->getZOrder();
	switch(type)
	{
	case ROLE_TYPE_TANGSENG:
		armature->setPosition(_x + 105 ,_y-8);
		break;
	case ROLE_TYPE_ZHUBAJIE:
		armature->setPosition(_x + 95 ,_y-1);
		break;
	case ROLE_TYPE_SHAHESHANG:
		armature->setPosition(_x + 95 ,_y+5);
		break;
	case ROLE_TYPE_SUNWUKONG:
		armature->setPosition(_x + 102 ,_y-2.5);
		break;
	case ROLE_TYPE_XIAOLONGNV:
		armature->setPosition(_x + 89 ,_y-4.5);
		break;
	case ROLE_TYPE_HULUWA:
		armature->setPosition(_x + 103.5 ,_y-3);
		break;
	}

	gunLun = CCSprite::create("flash/gunlun.png");
	gunLun->setScale(_scale);
	gunLun->setPosition(ccp(_x + 80, _y - 19));
	roleHide->setPosition(ccp(_x + 76.5, _y - 25.5));
#else
	armature->setScale(_scale);
	//armature->getDisplayRenderNode()->setZOrder(LAYER_ORDER_DYNAMIC_TARGET);
	//armature->getZOrder();
	armature->setPosition(_x ,_y);
	roleHide->setPosition(ccp(_x + 76.5, _y - 24.5));
#endif
	Global::getInstance()->setcentreX(_centreX);
	Global::getInstance()->setcentreY(_centreY);

	setStatus(ROLE_STATUS_NORMARL);//拉 不重
}

void Role::initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus)
{
	skillTime = _skillTime;
	skillTimeLeft = _skillTimeLeft;
	skillStatus = _skillStatus;
}

void Role::doJewelSkill(void)
{

}

void Role::releaseJewelSkill(void)
{

}

/************************************************************************/
/*	              Tangseng                                              */
/************************************************************************/
void Tangseng::doAction(float _f, GameControl * _gameControl)
{
	Role::doAction(_f,_gameControl);

	if (isHaveAlignment)
	{
		alignment->doAction(_f, hanger);
	}
}
	
void Tangseng::throwHanger(GameControl * _gameControl)
{
	if(hanger->getCanThrow() && (hanger->getStatus() == HANGER_STATUS_SWAYING))
	{
		hanger->setStatus(HANGER_STATUS_THROW);
#ifndef							GOLDEN_MINER2_FLASH_FRAME
		setStatus(ROLE_STATUS_THROW);
#endif
	}
}

void Tangseng::doSkill(GameControl *gameControl)
{
	Role::doSkill(gameControl);
	hanger->resetHangerBitmap("youxi/tang.png", TANGSENG_DISTANCE_TO_CENTER, TANGSENG_DISTANCE_TO_ROPE, HANGER_FUNCTION_TYPE_STONE_TO_GOLDEN);
	gameControl->setValueTimes(TARGET_TYPE_STONE, 5);// 石头价值变5倍

	if (hanger->carryTargetPoint != NULL)
	{	
		if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
		{
			if (((Target *)hanger->carryTargetPoint)->getTypeById() == TARGET_TYPE_STONE && gameControl->role->getType() == ROLE_TYPE_TANGSENG && gameControl->role->getSkillStatus() == ROLE_SKILL_STATUS_SKILLING)
			{
				((Target *)hanger->carryTargetPoint)->exchangeBitmapAndId(((Target *)hanger->carryTargetPoint)->getId() - 3);
				((Target *)hanger->carryTargetPoint)->addEffect();
				hanger->setSpeedTarget(((Target *)hanger->carryTargetPoint)->getSpeed(), ((Target *)hanger->carryTargetPoint)->getSpeedType());
			}
		}
	}

	exchangeHangerEffect = new ExchangeHangerEffect(hanger);
	gameControl->addChild(exchangeHangerEffect, LAYER_ORDER_CONTROL + 3);
}

void Tangseng::doActionSkill(float _f, GameControl * _gameControl)
{
	Role::doActionSkill(_f, _gameControl);
}

void Tangseng::releaseSkill(GameControl *gameControl)
{
	Role::releaseSkill(gameControl);
	hanger->resetHangerBitmap("youxi/gouzi.png", NORMAL_DISTANCE_TO_CENTER, NORMAL_DISTANCE_TO_ROPE, HANGER_FUNCTION_TYPE_NORMAL);
	gameControl->setValueTimes(TARGET_TYPE_STONE, 1);// 石头价值变1倍
}

void Tangseng::initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus)
{
	Role::initSkill(_skillTime, _skillTimeLeft, _skillStatus);
}

void Tangseng::doJewelSkill(void)
{

}

void Tangseng::releaseJewelSkill(void)
{

}

bool Tangseng::canDoExplosive(void)
{
	if (hanger->carryTargetPoint == NULL)
	{
		return false;
	}

	return true;
}

void Tangseng::doExplosive(GameControl * _gameControl)
{	
	// 移除抓取的目标 并且对钩子的状态更改为没有抓取物的拉回状态 将被抓去物的速度置0
	Explosive * _explosive = new Explosive(hanger);
	_gameControl->addExplosive(_explosive);
}

void Tangseng::releaseExplosive(GameControl * _gameControl)
{
	if(hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
	{
		((Target *)hanger->carryTargetPoint)->intersectByBomb(_gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
	else if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
	{
		((DynamicTarget *)hanger->carryTargetPoint)->intersectWithTarget(TARGET_ID_BOMB, NULL, _gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
}

void Tangseng::appendHangerSpeed(int _speed)
{
	hanger->appendSpeedSelf(_speed);
}
/************************************************************************/
/*	              Sunwukong                                             */
/************************************************************************/
void Sunwukong::doAction(float _f, GameControl * _gameControl)
{
	Role::doAction(_f,_gameControl);

	if (isHaveAlignment)
	{
		alignment->doAction(_f, hanger);
	}
}

void Sunwukong::doActionSkill(float _f, GameControl * _gameControl)
{
	Role::doActionSkill(_f, _gameControl);
}
	
void Sunwukong::throwHanger(GameControl * _gameControl)
{
	if(hanger->getCanThrow() && (hanger->getStatus() == HANGER_STATUS_SWAYING))
	{
		hanger->setStatus(HANGER_STATUS_THROW);
#ifndef							GOLDEN_MINER2_FLASH_FRAME
		setStatus(ROLE_STATUS_THROW);
#endif
	}
}

void Sunwukong::doSkill(GameControl *gameControl)
{
	// 孙悟空 停止移动怪物移动 和 时间的流逝
	hanger->resetHangerBitmap("youxi/wukong.png", SUNWUKONG_DISTANCE_TO_CENTER, SUNWUKONG_DISTANCE_TO_ROPE, HANGER_FUNCTION_TYPE_NORMAL);
	exchangeHangerEffect = new ExchangeHangerEffect(hanger);
	gameControl->addChild(exchangeHangerEffect, LAYER_ORDER_CONTROL + 3);
	Role::doSkill(gameControl);
	if(gameControl->gate->getCarriers() != NULL)
	{
		gameControl->gate->setIsCarrierMoving(false);
	}
	else
	{
		gameControl->setIsDynamicTargetMoving(false);
	}
	gameControl->setIsTiming(false);
	//skillCountTmp = skillTime;

	bingLayer = CCLayer::create();
	CCSprite * sprite = CCSprite::create("texiao/bing.png");
	CCRepeatForever * forever;
	CCSequence * sequence;
	sequence = CCSequence::create(CCFadeTo::create(1.0f, 255*0.3),CCFadeTo::create(1.0f, 255*1),NULL);
	forever = CCRepeatForever::create(sequence);
	sprite->runAction(forever);
	sprite->setPosition(ccp(400,240));
	bingLayer->addChild(sprite);

	Global::getInstance()->s->addLayerToRunningScene(bingLayer);
}

void Sunwukong::releaseSkill(GameControl *gameControl)
{
	// 孙悟空 恢复移动怪物移动 和 时间的流逝
	Role::releaseSkill(gameControl);
	hanger->resetHangerBitmap("youxi/gouzi.png", NORMAL_DISTANCE_TO_CENTER, NORMAL_DISTANCE_TO_ROPE, HANGER_FUNCTION_TYPE_NORMAL);

	if(gameControl->gate->getCarriers() != NULL)
	{
		gameControl->gate->setIsCarrierMoving(true);
	}
	else
	{
		gameControl->setIsDynamicTargetMoving(true);
	}
	gameControl->setIsTiming(true);

	Global::getInstance()->s->removeLayerToRunningScene(bingLayer);
}

void Sunwukong::initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus)
{
	Role::initSkill(_skillTime, _skillTimeLeft, _skillStatus);
}

void Sunwukong::doJewelSkill(void)
{

}

void Sunwukong::releaseJewelSkill(void)
{

}

bool Sunwukong::canDoExplosive(void)
{
	if (hanger->carryTargetPoint == NULL)
	{
		return false;
	}

	return true;
}

void Sunwukong::doExplosive(GameControl * _gameControl)
{
	// 移除抓取的目标 并且对钩子的状态更改为没有抓取物的拉回状态 将被抓去物的速度置0
	Explosive * _explosive = new Explosive(hanger);
	_gameControl->addExplosive(_explosive);
}

void Sunwukong::releaseExplosive(GameControl * _gameControl)
{
	if(hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
	{
		((Target *)hanger->carryTargetPoint)->intersectByBomb(_gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
	else if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
	{
		((DynamicTarget *)hanger->carryTargetPoint)->intersectWithTarget(TARGET_ID_BOMB, NULL, _gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
}

void Sunwukong::appendHangerSpeed(int _speed)
{
	hanger->appendSpeedSelf(_speed);
}
/************************************************************************/
/*	              Zhubajie                                              */
/************************************************************************/
void Zhubajie::doAction(float _f, GameControl * _gameControl)
{
	Role::doAction(_f,_gameControl);

	if (isHaveAlignment)
	{
		alignment->doAction(_f, hanger);
	}
	
	//if (skillStatus == ROLE_SKILL_STATUS_SKILLING && isSkillThrow && hanger->getStatus() == HANGER_STATUS_SWAYING)
	//{
	//	skillTimeLeftCount = skillTimeCount;
	//	skillTimeCount = 0;
	//	releaseSkill(_gameControl);
	//	skillStatus = ROLE_SKILL_STATUS_COOLING;
	//	liuGuang->setVisible(false);
	//	// 冷却动画
	//	// 技能钩子变化
	//}
}

void Zhubajie::doActionSkill(float _f, GameControl * _gameControl)
{
	CCRepeat * repeat;
	CCSequence * sequence;
	switch(skillStatus)
	{
	case ROLE_SKILL_STATUS_SKILLING:
		//if (skillCountTmp == 0)
		//{
#ifdef							GOLDEN_MINER_2_VERSION_TIME
		skillTimeCount += _f;
		if ((skillTimeCount*SCHEDULE_TIMES >= (skillTime - 60*3)) && ((skillTimeCount - _f*SCHEDULE_TIMES) <= (skillTime - 60*3)))
		{
			sequence = CCSequence::create(CCFadeTo::create(0.5f, 255*0.3),CCFadeTo::create(0.5f, 255*1),NULL);
			repeat = CCRepeat::create(sequence, skillTime/SCHEDULE_TIMES- skillTimeCount);
			_gameControl->role->getHanger()->runAction(repeat);
		}

#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeCount*SCHEDULE_TIMES)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft-skillTimeCount*SCHEDULE_TIMES)/skillTimeLeft));
#endif
		if (skillTimeCount*SCHEDULE_TIMES >= skillTime)
		{
			if (!isSkillThrow || (isSkillThrow && hanger->getStatus() == HANGER_STATUS_SWAYING))
			{
#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
				skillTimeLeftCount = skillTimeCount*SCHEDULE_TIMES; 
#else
				skillTimeLeftCount = 0; 
#endif
				skillTimeCount = 0;
				releaseSkill(_gameControl);
				skillStatus = ROLE_SKILL_STATUS_COOLING;
				liuGuang->setVisible(false);
				// 冷却动画
				// 技能钩子变化
			}
		}
		else
		{
			if (isSkillThrow && hanger->getStatus() == HANGER_STATUS_SWAYING)
			{
#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
				skillTimeLeftCount = skillTimeCount*SCHEDULE_TIMES; 
#else
				skillTimeLeftCount = 0; 
#endif
				skillTimeCount = 0;
				releaseSkill(_gameControl);
				skillStatus = ROLE_SKILL_STATUS_COOLING;
				liuGuang->setVisible(false);
				// 冷却动画
				// 技能钩子变化
			}
		}
#else
		skillTimeCount++;
		if (skillTimeCount == skillTime - 60*3)
		{
			sequence = CCSequence::create(CCFadeTo::create(0.5f, 255*0.3),CCFadeTo::create(0.5f, 255*1),NULL);
			repeat = CCRepeat::create(sequence, 3);
			_gameControl->role->getHanger()->runAction(repeat);
		}

#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeCount)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft-skillTimeCount)/skillTimeLeft));
#endif
		if (skillTimeCount >= skillTime)
		{
			if (!isSkillThrow || (isSkillThrow && hanger->getStatus() == HANGER_STATUS_SWAYING))
			{
#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
				skillTimeLeftCount = skillTime; 
#else
				skillTimeLeftCount = 0; 
#endif
				skillTimeCount = 0;
				releaseSkill(_gameControl);
				skillStatus = ROLE_SKILL_STATUS_COOLING;
				liuGuang->setVisible(false);
				// 冷却动画
				// 技能钩子变化
			}
		}
		else
		{
			if (isSkillThrow && hanger->getStatus() == HANGER_STATUS_SWAYING)
			{
#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
				skillTimeLeftCount = skillTime; 
#else
				skillTimeLeftCount = 0; 
#endif
				skillTimeCount = 0;
				releaseSkill(_gameControl);
				skillStatus = ROLE_SKILL_STATUS_COOLING;
				liuGuang->setVisible(false);
				// 冷却动画
				// 技能钩子变化
			}
		}
#endif
		//}
		//else
		//{
		//	skillCountTmp--;
		//}
		break;
	case ROLE_SKILL_STATUS_COOLING:
#ifdef								GOLDEN_MINER_2_VERSION_TIME
		skillTimeLeftCount += _f;
		if (skillTimeLeftCount*SCHEDULE_TIMES >= skillTimeLeft)
		{
			skillTimeLeftCount = 0;
			skillStatus = ROLE_SKILL_STATUS_CANSKILL;
			liuGuang->setVisible(true);
		}
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeLeftCount*SCHEDULE_TIMES)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft - skillTimeLeftCount*SCHEDULE_TIMES)/skillTimeLeft));
#else
		skillTimeLeftCount++;
		if (skillTimeLeftCount >= skillTimeLeft)
		{
			skillTimeLeftCount = 0;
			skillStatus = ROLE_SKILL_STATUS_CANSKILL;
			liuGuang->setVisible(true);
		}
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeLeftCount)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft - skillTimeLeftCount)/skillTimeLeft));
#endif
		break;
	case ROLE_SKILL_STATUS_CANSKILL:
		skillSprite2->setVisible(false);
		break;
	default:
		break;
	}
}
	
void Zhubajie::throwHanger(GameControl * _gameControl)
{
	if(hanger->getCanThrow() && (hanger->getStatus() == HANGER_STATUS_SWAYING))
	{
		hanger->setStatus(HANGER_STATUS_THROW);
#ifndef							GOLDEN_MINER2_FLASH_FRAME
		setStatus(ROLE_STATUS_THROW);
#endif


		if (skillStatus == ROLE_SKILL_STATUS_SKILLING)
		{
			isSkillThrow = true;
		}
	}
}

void Zhubajie::doSkill(GameControl *gameControl)
{
	Role::doSkill(gameControl);
	// 重新换成一个新的钩子图等特性
	hanger->setType(1);
	hanger->setSpeedTimes(1/3.0);
	hanger->resetHangerBitmap("youxi/bajie.png", ZHUBAJIE_DISTANCE_TO_CENTER, ZHUBAJIE_DISTANCE_TO_ROPE, HANGER_FUNCTION_TYPE_THROW);
	exchangeHangerEffect = new ExchangeHangerEffect(hanger);
	gameControl->addChild(exchangeHangerEffect, LAYER_ORDER_CONTROL + 3);
	isSkillThrow = false;


	if (hanger->getStatus() == HANGER_STATUS_THROW)
	{
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
	}
	else if (hanger->getStatus() == HANGER_STATUS_PULL_HAVING)
	{
		if(hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
		{
			hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
			setStatus(ROLE_STATUS_PULL_UNHAVING);
			hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
			Global::getInstance()->setContinuesCount(-1);
		}
		else if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
		{
			hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
			setStatus(ROLE_STATUS_PULL_UNHAVING);
			hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
			Global::getInstance()->setContinuesCount(-1);
		}
	}
}

void Zhubajie::releaseSkill(GameControl *gameControl)
{
	Role::releaseSkill(gameControl);
	// 重新换成一个新的钩子图等特性
	hanger->setType(0);
	hanger->setSpeedTimes(1);
	hanger->resetHangerBitmap("youxi/gouzi.png", NORMAL_DISTANCE_TO_CENTER, NORMAL_DISTANCE_TO_ROPE, HANGER_FUNCTION_TYPE_NORMAL);
}

void Zhubajie::initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus)
{
	Role::initSkill(_skillTime, _skillTimeLeft, _skillStatus);
}

void Zhubajie::doJewelSkill(void)
{

}

void Zhubajie::releaseJewelSkill(void)
{

}

bool Zhubajie::canDoExplosive(void)
{
	if (hanger->carryTargetPoint == NULL)
	{
		return false;
	}

	return true;
}

void Zhubajie::doExplosive(GameControl * _gameControl)
{
	// 移除抓取的目标 并且对钩子的状态更改为没有抓取物的拉回状态 将被抓去物的速度置0
	Explosive * _explosive = new Explosive(hanger);
	_gameControl->addExplosive(_explosive);
}

void Zhubajie::releaseExplosive(GameControl * _gameControl)
{
	if(hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
	{
		((Target *)hanger->carryTargetPoint)->intersectByBomb(_gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
	else if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
	{
		((DynamicTarget *)hanger->carryTargetPoint)->intersectWithTarget(TARGET_ID_BOMB, NULL, _gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
}

void Zhubajie::appendHangerSpeed(int _speed)
{
	hanger->appendSpeedSelf(_speed);
}
/************************************************************************/
/*	              Shaheshang                                            */
/************************************************************************/
void Shaheshang::doAction(float _f, GameControl * _gameControl)
{
	Role::doAction(_f,_gameControl);

	if (isHaveAlignment || skillStatus == ROLE_SKILL_STATUS_SKILLING)
	{
		alignment->doAction(_f, hanger);
	}

	//if (getSkillStatus() == ROLE_SKILL_STATUS_SKILLING)
	//{
	//	if (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING)
	//	{
	//		// 需要多转换一下角度
	//		biaozhunxian->setRotation(angleCenter - Global::getInstance()->getHangerAngle());
	//		changeMiaoZhunXianPosition();
	//	}
	//	if (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING)
	//	{
	//		biaozhunxian->setVisible(false);
	//	}
	//	else
	//	{
	//		biaozhunxian->setVisible(true);
	//	}
	//}
}

void Shaheshang::doActionSkill(float _f, GameControl * _gameControl)
{
	Role::doActionSkill(_f, _gameControl);
}
	
void Shaheshang::throwHanger(GameControl * _gameControl)
{
	if(hanger->getCanThrow() && (hanger->getStatus() == HANGER_STATUS_SWAYING))
	{
		hanger->setStatus(HANGER_STATUS_THROW);
#ifndef							GOLDEN_MINER2_FLASH_FRAME
		setStatus(ROLE_STATUS_THROW);
#endif
	}
}

void Shaheshang::doSkill(GameControl *gameControl)
{
	Role::doSkill(gameControl);

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_SHAHESHANG_LINE);

	//buybiaozhunxian = NULL;
	//biaozhunxian = CCSprite::create("youxi/miaozhunxian.png");
	//biaozhunxian->setScaleX(0.65);

	//if (gameControl->biaozhunxian == NULL)
	//{
	//	buybiaozhunxian = NULL;
	//	gameControl->biaozhunxian = biaozhunxian;
	//}
	//else
	//{
	//	buybiaozhunxian = gameControl->biaozhunxian;
	//	buybiaozhunxian->setVisible(false);
	//	gameControl->biaozhunxian = biaozhunxian;
	//}
	//gameControl->addChild(biaozhunxian, LAYER_ORDER_CONTROL-2);
	alignment->setType(ALIGNMENT_TYPE_SHAHESHANG);
	alignment->setVisible(true);

	hanger->resetHangerBitmap("youxi/shagou.png", SHAHESHANG_DISTANCE_TO_CENTER, SHAHESHANG_DISTANCE_TO_ROPE, HANGER_FUNCTION_TYPE_NORMAL);
	exchangeHangerEffect = new ExchangeHangerEffect(hanger);
	gameControl->addChild(exchangeHangerEffect, LAYER_ORDER_CONTROL + 3);
}

void Shaheshang::releaseSkill(GameControl *gameControl)
{
	Role::releaseSkill(gameControl);
	hanger->resetHangerBitmap("youxi/gouzi.png", NORMAL_DISTANCE_TO_CENTER, NORMAL_DISTANCE_TO_ROPE, HANGER_FUNCTION_TYPE_NORMAL);
	
	alignment->setType(ALIGNMENT_TYPE_NORMAL);
	if (!isHaveAlignment)
	{
		alignment->setVisible(false);
	}
	//gameControl->biaozhunxian = buybiaozhunxian;
	//gameControl->removeChild(biaozhunxian);
}

void Shaheshang::initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus)
{
	Role::initSkill(_skillTime, _skillTimeLeft, _skillStatus);

	//buybiaozhunxian = NULL;
	//biaozhunxian = CCSprite::create("youxi/miaozhunxian.png");
	//biaozhunxian->setScaleX(0.65);
	//CC_SAFE_RETAIN(biaozhunxian);

	//biaozhunxian->setAnchorPoint( ccp(biaozhunxian->getContentSize().width/2, biaozhunxian->getContentSize().height));
	//biaozhunxian->setPosition(ccp(Global::getInstance()->getcentreX(), Global::getInstance()->getcentreY()));
}

void Shaheshang::doJewelSkill(void)
{

}

void Shaheshang::releaseJewelSkill(void)
{

}

//void Shaheshang::changeMiaoZhunXianPosition(void)
//{
//
//	double positionX = Global::getInstance()->getHangerCurrX() + 
//		biaozhunxian->getContentSize().height * 0.8 / 2 * cos(Global::getInstance()->getHangerAngle() / angleChange * pi);
//	double positionY = Global::getInstance()->getHangerCurrY() + 
//		biaozhunxian->getContentSize().height * 0.8 / 2 * sin(Global::getInstance()->getHangerAngle() / angleChange * pi);
//
//	biaozhunxian->setPosition(ccp(positionX, positionY));
//}

bool Shaheshang::canDoExplosive(void)
{
	if (hanger->carryTargetPoint == NULL)
	{
		return false;
	}

	return true;
}

void Shaheshang::doExplosive(GameControl * _gameControl)
{
	// 移除抓取的目标 并且对钩子的状态更改为没有抓取物的拉回状态 将被抓去物的速度置0
	Explosive * _explosive = new Explosive(hanger);
	_gameControl->addExplosive(_explosive);
}

void Shaheshang::releaseExplosive(GameControl * _gameControl)
{
	if(hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
	{
		((Target *)hanger->carryTargetPoint)->intersectByBomb(_gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
	else if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
	{
		((DynamicTarget *)hanger->carryTargetPoint)->intersectWithTarget(TARGET_ID_BOMB, NULL, _gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
}

void Shaheshang::appendHangerSpeed(int _speed)
{
	hanger->appendSpeedSelf(_speed);
}

/************************************************************************/
/*	              Xiaolongnv                                            */
/************************************************************************/
void Xiaolongnv::doAction(float _f, GameControl * _gameControl)
{
	Role::doAction(_f,_gameControl);

	if (isHaveAlignment)
	{
		alignment->doAction(_f, hanger);
	}
}

void Xiaolongnv::doActionSkill(float _f, GameControl * _gameControl)
{
	Role::doActionSkill(_f, _gameControl);
}
	
void Xiaolongnv::throwHanger(GameControl * _gameControl)
{
	if(hanger->getCanThrow() && (hanger->getStatus() == HANGER_STATUS_SWAYING))
	{
		hanger->setStatus(HANGER_STATUS_THROW);
#ifndef							GOLDEN_MINER2_FLASH_FRAME
		setStatus(ROLE_STATUS_THROW);
#endif
	}
}

void Xiaolongnv::doSkill(GameControl *gameControl)
{
	Role::doSkill(gameControl);
	hanger->setSpeedTimes(1.5);
	//gameControl->setValueTimes(TARGET_TYPE_STONE, 2);// 石头价值变5倍
	//gameControl->setValueTimes(TARGET_TYPE_GOLDEN, 2);// 石头价值变5倍
	hanger->resetHangerBitmap("youxi/longnv.png", XIAOLONGNV_DISTANCE_TO_CENTER, XIAOLONGNV_DISTANCE_TO_ROPE, HANGER_FUNCTION_TYPE_EXCHANGE_TO_JEWEL);//HANGER_FUNCTION_TYPE_CARRY_BOMB);
	exchangeHangerEffect = new ExchangeHangerEffect(hanger);
	gameControl->addChild(exchangeHangerEffect, LAYER_ORDER_CONTROL + 3);
}

void Xiaolongnv::releaseSkill(GameControl *gameControl)
{
	Role::releaseSkill(gameControl);
	hanger->setSpeedTimes(1);
	hanger->resetHangerBitmap("youxi/gouzi.png", NORMAL_DISTANCE_TO_CENTER, NORMAL_DISTANCE_TO_ROPE, HANGER_FUNCTION_TYPE_NORMAL);
	//gameControl->setValueTimes(TARGET_TYPE_STONE, 1);// 石头价值变5倍
	//gameControl->setValueTimes(TARGET_TYPE_GOLDEN, 1);// 石头价值变5倍
}

void Xiaolongnv::initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus)
{
	Role::initSkill(_skillTime, _skillTimeLeft, _skillStatus);
}

void Xiaolongnv::doJewelSkill(void)
{

}

void Xiaolongnv::releaseJewelSkill(void)
{

}

bool Xiaolongnv::canDoExplosive(void)
{
	if (hanger->carryTargetPoint == NULL)
	{
		return false;
	}
	
	return true;
}

void Xiaolongnv::doExplosive(GameControl * _gameControl)
{
	// 移除抓取的目标 并且对钩子的状态更改为没有抓取物的拉回状态 将被抓去物的速度置0
	Explosive * _explosive = new Explosive(hanger);
	_gameControl->addExplosive(_explosive);
}

void Xiaolongnv::releaseExplosive(GameControl * _gameControl)
{
	if(hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
	{
		((Target *)hanger->carryTargetPoint)->intersectByBomb(_gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
	else if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
	{
		((DynamicTarget *)hanger->carryTargetPoint)->intersectWithTarget(TARGET_ID_BOMB, NULL, _gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
}

void Xiaolongnv::appendHangerSpeed(int _speed)
{
	hanger->appendSpeedSelf(_speed);
}

/************************************************************************/
/*	              HuLuWa                                            */
/************************************************************************/
HuLuWa::HuLuWa(void)
:Role(){
	jewelSkillSprite = NULL;
	doJewel = false;
	releaseJewel = false;
}

HuLuWa::~HuLuWa(void)
{
	if (isIce)
	{
		CC_SAFE_RELEASE_NULL(hangerFire);
	}
	else
	{
		CC_SAFE_RELEASE_NULL(hangerIce);
	}
}

void HuLuWa::doAction(float _f, GameControl * _gameControl)
{
	Role::doAction(_f,_gameControl);

	if (isExchange && hanger->getStatus() == HANGER_STATUS_SWAYING)
	{
		if (isIce)
		{
			hanger = hangerFire;
			hangerIce->setVisible(false);
			hangerIce->getRope()->setVisible(false);
			hangerFire->setVisible(true);
			hangerFire->getRope()->setVisible(true);
			hangerFire->setAngle(hangerIce->getAngle());
			hangerFire->getRope()->changePosition(hangerFire);
			hangerFire->setSpeedAngle(hangerIce->getSpeedAngle());
			isIce = false;
		}
		else
		{
			hanger = hangerIce;
			hangerFire->setVisible(false);
			hangerFire->getRope()->setVisible(false);
			hangerIce->setVisible(true);
			hangerIce->getRope()->setVisible(true);
			hangerIce->setAngle(hangerFire->getAngle());
			hangerIce->getRope()->changePosition(hangerIce);
			hangerIce->setSpeedAngle(hangerFire->getSpeedAngle());
			isIce = true;
		}
		isExchange = false;
	}

	if (isHaveAlignment)
	{
		alignment->doAction(_f, hanger);
	}
}

void HuLuWa::doActionSkill(float _f, GameControl * _gameControl)
{
	CCRepeat * repeat;
	CCSequence * sequence;
	switch(skillStatus)
	{
	case ROLE_SKILL_STATUS_SKILLING:
		//if (skillCountTmp == 0)
		//{
		if (doJewel)
		{
			if (!getHanger()->isVisible())
			{
				jewelSkillSprite->setVisible(false);
				doJewel = false;
			}
		}
		if (releaseJewel)
		{
			if (getHanger()->isVisible())
			{
				jewelSkillSprite->setVisible(true);
				getHanger()->setVisible(false);
				releaseJewel = false;
			}
		}
#ifdef											GOLDEN_MINER_2_VERSION_TIME
		skillTimeCount += _f;
		if ((skillTimeCount*SCHEDULE_TIMES >= (skillTime - 60*3)) && ((skillTimeCount - _f*SCHEDULE_TIMES) <= (skillTime - 60*3)))
		{
			sequence = CCSequence::create(CCFadeTo::create(0.5f, 255*0.3),CCFadeTo::create(0.5f, 255*1),NULL);
			repeat = CCRepeat::create(sequence, skillTime/SCHEDULE_TIMES- skillTimeCount);
			jewelSkillSprite->runAction(repeat);
		}

#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeCount*SCHEDULE_TIMES)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft-skillTimeCount*SCHEDULE_TIMES)/skillTimeLeft));
#endif
		jewelSkillSprite->updateSkill(_f, _gameControl);
		if (isSkillThrow)
		{
			if (jewelSkillSprite->getStatus() == JEWEL_SKILL_SPRITE_STATUS_FINISH)
			{
#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
				skillTimeLeftCount = skillTimeCount*SCHEDULE_TIMES; 
#else
				skillTimeLeftCount = 0; 
#endif
				skillTimeCount = 0;
				releaseSkill(_gameControl);
				skillStatus = ROLE_SKILL_STATUS_COOLING;
				doJewel = false;
				releaseJewel = false;
				jewelSkillSprite = NULL;
				liuGuang->setVisible(false);
				// 冷却动画
				// 技能钩子变化
			}
		}
		else
		{
			if (skillTimeCount*SCHEDULE_TIMES >= skillTime)
			{
#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
				skillTimeLeftCount = skillTimeCount*SCHEDULE_TIMES; 
#else
				skillTimeLeftCount = 0; 
#endif
				skillTimeCount = 0;
				releaseSkill(_gameControl);
				skillStatus = ROLE_SKILL_STATUS_COOLING;
				doJewel = false;
				releaseJewel = false;
				jewelSkillSprite = NULL;
				liuGuang->setVisible(false);
				// 冷却动画
				// 技能钩子变化
			}
		}
#else
		skillTimeCount++;
		if (skillTimeCount == skillTime - 60*3)
		{
			sequence = CCSequence::create(CCFadeTo::create(0.5f, 255*0.3),CCFadeTo::create(0.5f, 255*1),NULL);
			repeat = CCRepeat::create(sequence, 3);
			jewelSkillSprite->runAction(repeat);
		}

#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeCount)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft-skillTimeCount)/skillTimeLeft));
#endif
		jewelSkillSprite->updateSkill(_f, _gameControl);
		if (isSkillThrow)
		{
			if (jewelSkillSprite->getStatus() == JEWEL_SKILL_SPRITE_STATUS_FINISH)
			{
#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
				skillTimeLeftCount = skillTime; 
#else
				skillTimeLeftCount = 0; 
#endif
				skillTimeCount = 0;
				releaseSkill(_gameControl);
				skillStatus = ROLE_SKILL_STATUS_COOLING;
				doJewel = false;
				releaseJewel = false;
				jewelSkillSprite = NULL;
				liuGuang->setVisible(false);
				// 冷却动画
				// 技能钩子变化
			}
		}
		else
		{
			if (skillTimeCount >= skillTime)
			{
#ifdef											ROLE_SKILL_LEFT_IS_COUNT_SKILLTIME 
				skillTimeLeftCount = skillTime; 
#else
				skillTimeLeftCount = 0; 
#endif
				skillTimeCount = 0;
				releaseSkill(_gameControl);
				skillStatus = ROLE_SKILL_STATUS_COOLING;
				doJewel = false;
				releaseJewel = false;
				jewelSkillSprite = NULL;
				liuGuang->setVisible(false);
				// 冷却动画
				// 技能钩子变化
			}
		}
#endif
		//}
		//else
		//{
		//	skillCountTmp--;
		//}
		break;
	case ROLE_SKILL_STATUS_COOLING:
#ifdef									GOLDEN_MINER_2_VERSION_TIME 
		skillTimeLeftCount += _f;
		if (skillTimeLeftCount*SCHEDULE_TIMES >= skillTimeLeft)
		{
			skillTimeLeftCount = 0;
			skillStatus = ROLE_SKILL_STATUS_CANSKILL;
			liuGuang->setVisible(true);
		}
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeLeftCount*SCHEDULE_TIMES)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft - skillTimeLeftCount*SCHEDULE_TIMES)/skillTimeLeft));
#else
		skillTimeLeftCount++;
		if (skillTimeLeftCount >= skillTimeLeft)
		{
			skillTimeLeftCount = 0;
			skillStatus = ROLE_SKILL_STATUS_CANSKILL;
			liuGuang->setVisible(true);
		}
		skillSprite2->setPositionY(103+ SKILL_SPRITE_HEIGHT*(skillTimeLeftCount)/skillTimeLeft/2);
		skillSprite2->setTextureRect(*new CCRect(0,0,SKILL_SPRITE_WIDTH,SKILL_SPRITE_HEIGHT*(skillTimeLeft - skillTimeLeftCount)/skillTimeLeft));
#endif
		break;
	case ROLE_SKILL_STATUS_CANSKILL:
		skillSprite2->setVisible(false);
		break;
	default:
		break;
	}
}

void HuLuWa::throwHanger(GameControl * _gameControl)
{
	if (skillStatus == ROLE_SKILL_STATUS_SKILLING)
	{
		if (!isSkillThrow && hanger->getCanThrow() && (hanger->getStatus() == HANGER_STATUS_SWAYING))
		{
			jewelSkillSprite->doSkill(_gameControl);
			isSkillThrow = true;
		}
	} 
	else
	{
		if(hanger->getCanThrow() && (hanger->getStatus() == HANGER_STATUS_SWAYING))
		{
			hanger->setStatus(HANGER_STATUS_THROW);
#ifndef							GOLDEN_MINER2_FLASH_FRAME
			setStatus(ROLE_STATUS_THROW);
#endif
			isExchange = true;
		}
	}
}

void HuLuWa::doSkill(GameControl *gameControl)
{
	Role::doSkill(gameControl);
	jewelSkillSprite = new JewelSkillGourd(gameControl, hanger);
	gameControl->addChild(jewelSkillSprite, LAYER_ORDER_CONTROL-1);
	exchangeHangerEffect = new ExchangeHangerEffect(hanger);
	gameControl->addChild(exchangeHangerEffect, LAYER_ORDER_CONTROL + 3);
	isSkillThrow = false;

	if (hanger->getStatus() == HANGER_STATUS_THROW)
	{
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
	}
	else if (hanger->getStatus() == HANGER_STATUS_PULL_HAVING)
	{
		if(hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
		{
			hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
			setStatus(ROLE_STATUS_PULL_UNHAVING);
			hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
			Global::getInstance()->setContinuesCount(-1);
		}
		else if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
		{
			hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
			setStatus(ROLE_STATUS_PULL_UNHAVING);
			hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
			Global::getInstance()->setContinuesCount(-1);
		}
	}
	isExchange = false;
}

void HuLuWa::releaseSkill(GameControl *gameControl)
{
	Role::releaseSkill(gameControl);
	jewelSkillSprite->releaseSkill(gameControl);
	isSkillThrow = false;
	//isExchange = true;
}

void HuLuWa::initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus)
{
	Role::initSkill(_skillTime, _skillTimeLeft, _skillStatus);
}

void HuLuWa::doJewelSkill(void)
{
	if (skillStatus == ROLE_SKILL_STATUS_SKILLING)
	{
		if (jewelSkillSprite != NULL && !getHanger()->isVisible())
		{
			jewelSkillSprite->setVisible(false);
		}
		else
		{
			doJewel = true;
		}
	} 
}

void HuLuWa::releaseJewelSkill(void)
{
	if (skillStatus == ROLE_SKILL_STATUS_SKILLING)
	{
		if (jewelSkillSprite != NULL && getHanger()->isVisible())
		{
			jewelSkillSprite->setVisible(true);
			getHanger()->setVisible(false);
		}
		else
		{
			releaseJewel = true;
		}
	} 
}

bool HuLuWa::canDoExplosive(void)
{
	if (hanger->carryTargetPoint == NULL)
	{
		return false;
	}

	return true;
}

void HuLuWa::doExplosive(GameControl * _gameControl)
{
	// 移除抓取的目标 并且对钩子的状态更改为没有抓取物的拉回状态 将被抓去物的速度置0
	Explosive * _explosive = new Explosive(hanger);
	_gameControl->addExplosive(_explosive);
}

void HuLuWa::releaseExplosive(GameControl * _gameControl)
{
	if(hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
	{
		((Target *)hanger->carryTargetPoint)->intersectByBomb(_gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
	else if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
	{
		((DynamicTarget *)hanger->carryTargetPoint)->intersectWithTarget(TARGET_ID_BOMB, NULL, _gameControl);
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
		setStatus(ROLE_STATUS_PULL_UNHAVING);
		hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		hanger->carryTargetPoint = NULL;
		hanger->carryTargetType = -1;
		Global::getInstance()->setContinuesCount(-1);
	}
}

void HuLuWa::appendHangerSpeed(int _speed)
{
	hangerIce->appendSpeedSelf(_speed);
	hangerFire->appendSpeedSelf(_speed);
}

Hanger * HuLuWa::initHangers(GameControl * _gameControl)
{
	hangerIce = new Hanger(HULUWA_ICE_DISTANCE_TO_CENTER, HULUWA_ICE_DISTANCE_TO_ROPE, HULUWA_SWAY_SPEED, 15, Global::getInstance()->getSceneSpeedByMapId(_gameControl->getCurrMapId()), 0);
	hangerIce->initWithFile("youxi/bing.png");
	hangerIce->setFunctionType(HANGER_FUNCTION_TYPE_CARRY_BOMB);
	hangerFire = new Hanger(HULUWA_FIRE_DISTANCE_TO_CENTER, HULUWA_FIRE_DISTANCE_TO_ROPE, HULUWA_SWAY_SPEED, 18, Global::getInstance()->getSceneSpeedByMapId(_gameControl->getCurrMapId()), 0);
	hangerFire->initWithFile("youxi/huo.png");
	hangerFire->setFunctionType(HANGER_FUNCTION_TYPE_BOMB);
	hangerFire->setVisible(false);
	hangerFire->getRope()->setVisible(false);

	_gameControl->addChild(hangerFire->getRope(), LAYER_ORDER_CONTROL - 1);
	_gameControl->addChild(hangerFire, LAYER_ORDER_CONTROL - 1);
	hangerFire->retain();

	isIce = true;
	isExchange = false;
	isSkillThrow = false;
	return hangerIce;
}