#include "Pet.h"
#include "Global.h"
#include "Player.h"

USING_NS_CC;
using namespace cs;

// 层次结构
#define					PET_LAYER_ROOM						0
#define					PET_LAYER_SHADOW					1
#define					PET_LAYER_OBJECT					2
#define					PET_LAYER_EFFECT					3
#define					PET_LAYER_CHEER						4
#define					PET_LAYER_TIP						5

// 检测时间
#define					PET_BORN_CHECK_TIME					1.5

// 特效时间
#define					PET_EFFECT_EXCHANGE_BITMAP_TIME					0.5

/*****************************************************
出生特效
*******************************************************/
BornEffect::BornEffect(void)
{
	startTime = 0.0;
	index = 0;
	bitmaps = new CCArray();
	bitmaps->addObject(CCSprite::create("texiao/guaiwu/guaiwu1.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/guaiwu/guaiwu2.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/guaiwu/guaiwu3.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/guaiwu/guaiwu4.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/guaiwu/guaiwu5.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());

	autorelease();
}

bool BornEffect::doAction(float _f)
{
	startTime += _f;
	if (startTime >= PET_EFFECT_EXCHANGE_BITMAP_TIME/bitmaps->count())
	{
		((CCSprite *)bitmaps->objectAtIndex(index++))->setVisible(false);
		if (index == bitmaps->count())
		{
			index = 0;
			return true;
		}
		((CCSprite *)bitmaps->objectAtIndex(index))->setVisible(true);
		startTime = 0;
	}
	return false;
}

BornEffect::~BornEffect(void)
{
	CCObject * p = NULL;
	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
}

/*****************************************************
长大特效
*******************************************************/
GrowEffect::GrowEffect(void)
{
	startTime = 0.0;
	index = 0;
	bitmaps = new CCArray();
	bitmaps->addObject(CCSprite::create("texiao/shengji/shengji1.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/shengji/shengji2.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/shengji/shengji3.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/shengji/shengji4.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/shengji/shengji5.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/shengji/shengji6.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/shengji/shengji7.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());

	autorelease();
}

bool GrowEffect::doAction(float _f)
{
	startTime += _f;
	if (startTime >= PET_EFFECT_EXCHANGE_BITMAP_TIME/bitmaps->count())
	{
		((CCSprite *)bitmaps->objectAtIndex(index++))->setVisible(false);
		if (index == bitmaps->count())
		{
			index = 0;
			return true;
		}
		((CCSprite *)bitmaps->objectAtIndex(index))->setVisible(true);
		startTime = 0;
	}
	return false;
}

GrowEffect::~GrowEffect(void)
{
	CCObject * p = NULL;
	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
}


/*****************************************************
宠物
*******************************************************/
Pet::Pet(void)
{
	elementId = 0;
	timeCount = 0;
	egg = NULL;
	armature = NULL;// flash
	lifeStatus = PET_LIFE_STATUS_EGG;
	room = CCSprite::create("guaiwuwo/wo.png");
	isCheer= CCSprite::create("guaiwuwo/yishangzhen1.png");
	growEffect = NULL;// 长大特效
	bronEffect = NULL;// 出生特效
	frame = NULL;// 话语框
	tip = NULL;// 话语
	system = NULL;

	addChild(room, PET_LAYER_ROOM);
	addChild(isCheer, PET_LAYER_CHEER);
	isCheer->setVisible(false);

	isCheer->setPosition(ccp(-20, 75));
	room->setPosition(ccp(0, 10));

	autorelease();
}


Pet::~Pet(void)
{
}

void Pet::initSelf(void)
{
	if (Player::getInstance()->getPetHaving(elementId))
	{// 拥有怪物
		if (Player::getInstance()->getPetHeart(elementId) == Global::getInstance()->getPetHeartFull(elementId))
		{
			// 长大
			setLifeStatus(PET_LIFE_STATUS_GROW);
			
		}
		else
		{
			// 宝宝
			setLifeStatus(PET_LIFE_STATUS_BABY);
		}

		setTip();
	}
	else
	{// 搜集灵魂状态
		setLifeStatus(PET_LIFE_STATUS_EGG);
	}

	setBeSelected(false);// 影响播放的动作

	if (lifeStatus == PET_LIFE_STATUS_GROW && Player::getInstance()->getSelectPet() == elementId)
	{
		setIsCheer(true);
	}
}

int Pet::doAction(float _f)
{
	timeCount += _f;

	// 特效
	if (growEffect != NULL)
	{
		if (growEffect->doAction(_f))
		{
			finishGrow();
			return 2;
		}		
	}
	else
	{
		// 检测
		if (timeCount > PET_BORN_CHECK_TIME)
		{
			if (Player::getInstance()->getPetBorn(elementId))
			{
				doBorn();
			}			
		}
	}
	if (bronEffect != NULL)
	{
		if (bronEffect->doAction(_f))
		{
			finishBorn();
			return 1;
		}		
	}

	return 0;
}

int Pet::getElementId(void)
{
	return elementId;
}

cs::Armature * Pet::getArmature(void)
{
	return armature;
}

int Pet::getLifeStatus(void)
{
	return lifeStatus;
}

bool Pet::isBeSelected(void)
{
	return beSelected;
}

void Pet::setBeSelected(bool _b)
{
	if (beSelected == _b)
	{
		return;
	}

	beSelected = _b;

	exchangeAction();
}

void Pet::setIsCheer(bool _b)
{
	if (_b == !isCheer->isVisible())
	{
		if (_b)
		{
			Player::getInstance()->setSelectPet(elementId);
		}
		else
		{
			Player::getInstance()->setSelectPet(-1);
		}
	}

	isCheer->setVisible(_b);
}

bool Pet::getIsCheer(void)
{
	return isCheer->isVisible();
}

float Pet::getWidth(void)
{
	return width;
}

float Pet::getHeight(void)
{
	return height;
}

bool Pet::addHeart(int _num, int _type)
{
	if (system != NULL)
	{
		removeChild(system);
	}

	if (_type == PET_APPEND_TYPE_TEACH)
	{
		system = CCParticleSystemQuad::create("lizitexiao/yinfu/yinfu.plist");
		system->setPosition(ccp(0,60));//设置位置  
		addChild(system, LAYER_ORDER_CONTROL+1);
	}
	else
	{
		system = CCParticleSystemQuad::create("lizitexiao/jiaaixin/jiaaixin.plist");
		system->setPosition(ccp(0,60));//设置位置  
		addChild(system, LAYER_ORDER_CONTROL+1);
		//CCFadeTo * sequence = CCFadeTo::create(3, 255*0);
		//systemNode->runAction(sequence);
	}

	Player::getInstance()->appendPetHeart(elementId, _num);

	if (Player::getInstance()->getPetHeart(elementId) == Global::getInstance()->getPetHeartFull(elementId))
	{// 长大
		doGrow();
		return true;
	}
	return false;
}

void Pet::doBorn(void)
{
	bronEffect = new BornEffect();
	addChild(bronEffect, PET_LAYER_EFFECT);
	bronEffect->setPositionY(70);

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_PET_GROW);

	Player::getInstance()->setPetBorn(elementId, false);
	Player::getInstance()->setPetHaving(elementId, true);
}

void Pet::finishBorn(void)
{
	removeChild(bronEffect, true);
	bronEffect = NULL;
	Player::getInstance()->setPetBorn(elementId, false);
	setLifeStatus(PET_LIFE_STATUS_BABY);
	setTip();
	exchangeAction();
}

void Pet::doGrow(void)
{
	growEffect = new GrowEffect();	
	addChild(growEffect, PET_LAYER_EFFECT);

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_PET_GROW);
	frame->setVisible(false);
	//tip->setVisible(false);
}

void Pet::finishGrow(void)
{
	removeChild(growEffect, true);
	growEffect = NULL;
	setLifeStatus(PET_LIFE_STATUS_GROW);
	setTip();
	exchangeAction();
}

void Pet::exchangeAction(void)
{

}

void Pet::setLifeStatus(int _status)
{
	lifeStatus = _status;
	if (lifeStatus == PET_LIFE_STATUS_EGG)
	{
		egg->setVisible(true);
		armature->setVisible(false);
	}
	else if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		egg->setVisible(false);
		armature->setVisible(true);
		armature->setScale(0.7);
	}
	else
	{
		egg->setVisible(false);
		armature->setVisible(true);
		armature->setScale(0.9);
	}
}

void Pet::setTip(void)
{
	frame->setVisible(true);
	//tip->setVisible(true);
}

/*********************************************
精细鬼
**********************************************/
PetJingXiGui::PetJingXiGui(void)
	:Pet()
{
}

PetJingXiGui::~PetJingXiGui(void)
{

}

void PetJingXiGui::initSelf(void)
{
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("jingxigui", "", "flash/jingxigui/jingxigui.png", "flash/jingxigui/jingxigui.plist", "flash/jingxigui/skeleton.xml");
	armature = Armature::create("jingxigui");
	addChild(armature, PET_LAYER_OBJECT);
	egg = CCSprite::create("guaiwuwo/dan3.png");
	addChild(egg, PET_LAYER_OBJECT);

	elementId = PET_ELEMENT_JINGXIGUI;
	
	Pet::initSelf();
}

int PetJingXiGui::doAction(float _f)
{
	return Pet::doAction(_f);
}

void PetJingXiGui::setTip(void)
{
	if (frame == NULL)
	{
		//frame = CCSprite::create("guaiwuwo/maopao.png");
		//addChild(frame, PET_LAYER_TIP);
		//frame->setPosition(ccp(75,105));
		//if (lifeStatus == PET_LIFE_STATUS_EGG)
		//{
		//	tip = CCSprite::create("duihuakuang/28.png");
		//}
		//else
		//{
		//	tip = CCSprite::create("duihuakuang/32.png");
		//}
		//frame->addChild(tip);
		//tip->setPosition(ccp(60,80));
		if (lifeStatus == PET_LIFE_STATUS_BABY)
		{
			frame = CCSprite::create("duihuakuang/32.png");
		}
		else
		{
			frame = CCSprite::create("duihuakuang/28.png");
		}
		addChild(frame, PET_LAYER_TIP);
		frame->setPosition(ccp(75,105));
	}
	else
	{	
		CCTexture2D *pTexture;
		CCRect rect;
		if (lifeStatus == PET_LIFE_STATUS_BABY)
		{
			pTexture = CCTextureCache::sharedTextureCache()->addImage("duihuakuang/32.png");
			if (pTexture)
			{
				rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				frame->setTexture(pTexture);
				frame->setTextureRect(rect);
			}
		}
		else
		{
			pTexture = CCTextureCache::sharedTextureCache()->addImage("duihuakuang/28.png");
			if (pTexture)
			{
				rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				frame->setTexture(pTexture);
				frame->setTextureRect(rect);
			}
		}
		//CCTexture2D *pTexture;
		//CCRect rect;
		//if (lifeStatus == PET_LIFE_STATUS_EGG)
		//{
		//	pTexture = CCTextureCache::sharedTextureCache()->addImage("duihuakuang/28.png");
		//	if (pTexture)
		//	{
		//		rect = CCRectZero;
		//		rect.size = pTexture->getContentSize();
		//		tip->setTexture(pTexture);
		//		tip->setTextureRect(rect);
		//	}
		//}
		//else
		//{
		//	pTexture = CCTextureCache::sharedTextureCache()->addImage("duihuakuang/32.png");
		//	if (pTexture)
		//	{
		//		rect = CCRectZero;
		//		rect.size = pTexture->getContentSize();
		//		tip->setTexture(pTexture);
		//		tip->setTextureRect(rect);
		//	}
		//}
	}
	Pet::setTip();
}

void PetJingXiGui::setLifeStatus(int _status)
{
	Pet::setLifeStatus(_status);

#ifdef									GOLDEN_MINER2_FLASH_FRAME
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		armature->setPosition(ccp(-5, -22));
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		armature->setPosition(ccp(-10, -15));
	} 
#else
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		armature->setPosition(ccp(8, -15));
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		armature->setPosition(ccp(20, -10));
	} 
#endif
}

void PetJingXiGui::exchangeAction(void)
{
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		// baby动作
#ifdef								GOLDEN_MINER2_FLASH_FRAME
		armature->getAnimation()->play("jxgnaizui", 0, 60, 1, TWEEN_EASING_MAX);
#else
		armature->getAnimation()->play("jingxiguimaimeng0", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		frame->setVisible(isBeSelected());

		width = armature->getContentSize().width;
		height = armature->getContentSize().height;
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		if (isBeSelected())
		{
			// 选中动作
#ifdef								GOLDEN_MINER2_FLASH_FRAME
			armature->getAnimation()->play("jxgmaimeng", 0, 60, 1, TWEEN_EASING_MAX);
#else
			armature->getAnimation()->play("jingxiguibangbangtang", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		}
		else
		{
			// 为选中动作
#ifdef								GOLDEN_MINER2_FLASH_FRAME
			armature->getAnimation()->play("jxgmaimeng", 0, 60, 1, TWEEN_EASING_MAX);
#else
			armature->getAnimation()->play("jingxiguimaimeng", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		}
		frame->setVisible(isBeSelected());
		width = armature->getContentSize().width;
		height = armature->getContentSize().height;
	}
	else
	{
		width = egg->getContentSize().width;
		height = egg->getContentSize().height;

		if (isBeSelected())
		{
			// 选中动作
			CCRepeatForever * forever;
			forever = CCRepeatForever::create(CCJumpTo::create(0.3, egg->getPosition(), height/4, 1));
			egg->runAction(forever);
		}
		else
		{
			egg->stopAllActions();
			egg->setPosition(ccp(0,0));
		}
	}
}
/*********************************************
牛魔王
**********************************************/
PetNiuMoWang::PetNiuMoWang(void)
	:Pet()
{
}

PetNiuMoWang::~PetNiuMoWang(void)
{

}

void PetNiuMoWang::initSelf(void)
{
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("niumowang", "", "flash/niumowang/niumowang.png", "flash/niumowang/niumowang.plist", "flash/niumowang/skeleton.xml");
	armature = Armature::create("niumowang");
	addChild(armature, PET_LAYER_OBJECT);
	egg = CCSprite::create("guaiwuwo/dan1.png");
	addChild(egg, PET_LAYER_OBJECT);

	elementId = PET_ELEMENT_NIUMOWANG;

	Pet::initSelf();
}

int PetNiuMoWang::doAction(float _f)
{
	return Pet::doAction(_f);
}

void PetNiuMoWang::setTip(void)
{
	if (frame == NULL)
	{
		//frame = CCSprite::create("guaiwuwo/maopao.png");
		//addChild(frame, PET_LAYER_TIP);
		//frame->setPosition(ccp(75,105));
		//if (lifeStatus == PET_LIFE_STATUS_EGG)
		//{
		//	tip = CCSprite::create("guaiwuwo/31.png");
		//}
		//else
		//{
		//	tip = CCSprite::create("guaiwuwo/35.png");
		//}
		//frame->addChild(tip);
		//tip->setPosition(ccp(60,80));
		if (lifeStatus == PET_LIFE_STATUS_BABY)
		{
			frame = CCSprite::create("duihuakuang/35.png");
		}
		else
		{
			frame = CCSprite::create("duihuakuang/31.png");
		}
		addChild(frame, PET_LAYER_TIP);
		frame->setPosition(ccp(75,105));
	}
	else
	{	
		CCTexture2D *pTexture;
		CCRect rect;
		if (lifeStatus == PET_LIFE_STATUS_BABY)
		{
			pTexture = CCTextureCache::sharedTextureCache()->addImage("duihuakuang/35.png");
			if (pTexture)
			{
				rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				frame->setTexture(pTexture);
				frame->setTextureRect(rect);
			}
		}
		else
		{
			pTexture = CCTextureCache::sharedTextureCache()->addImage("duihuakuang/31.png");
			if (pTexture)
			{
				rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				frame->setTexture(pTexture);
				frame->setTextureRect(rect);
			}
		}
		//CCTexture2D *pTexture;
		//CCRect rect;
		//if (lifeStatus == PET_LIFE_STATUS_EGG)
		//{
		//	pTexture = CCTextureCache::sharedTextureCache()->addImage("guaiwuwo/31.png");
		//	if (pTexture)
		//	{
		//		rect = CCRectZero;
		//		rect.size = pTexture->getContentSize();
		//		tip->setTexture(pTexture);
		//		tip->setTextureRect(rect);
		//	}
		//}
		//else
		//{
		//	pTexture = CCTextureCache::sharedTextureCache()->addImage("guaiwuwo/35.png");
		//	if (pTexture)
		//	{
		//		rect = CCRectZero;
		//		rect.size = pTexture->getContentSize();
		//		tip->setTexture(pTexture);
		//		tip->setTextureRect(rect);
		//	}
		//}
	}
	Pet::setTip();
}

void PetNiuMoWang::setLifeStatus(int _status)
{
	Pet::setLifeStatus(_status);

#ifdef									GOLDEN_MINER2_FLASH_FRAME
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		armature->setPosition(ccp(-22, -20));
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		armature->setPosition(ccp(-33, -20));
	} 
#else
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		armature->setPosition(ccp(-28, -8));
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		armature->setPosition(ccp(-35, 2));
	} 
#endif
}

void PetNiuMoWang::exchangeAction(void)
{
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		// baby动作
#ifdef							GOLDEN_MINER2_FLASH_FRAME
		armature->getAnimation()->play("nmwnaizui", 0, 50, 1, TWEEN_EASING_MAX);
#else
		armature->getAnimation()->play("niunaizui", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		frame->setVisible(isBeSelected());

		width = armature->getContentSize().width;
		height = armature->getContentSize().height;
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		if (isBeSelected())
		{
			// 选中动作
#ifdef							GOLDEN_MINER2_FLASH_FRAME
			armature->getAnimation()->play("nmwmaimeng", 0, 50, 1, TWEEN_EASING_MAX);
#else
			armature->getAnimation()->play("niuwabi", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		}
		else
		{
			// 为选中动作
#ifdef							GOLDEN_MINER2_FLASH_FRAME
			armature->getAnimation()->play("nmwmaimeng", 0, 50, 1, TWEEN_EASING_MAX);
#else
			armature->getAnimation()->play("niumaimeng", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		}
		frame->setVisible(isBeSelected());
		width = armature->getContentSize().width;
		height = armature->getContentSize().height;
	}
	else
	{

		width = egg->getContentSize().width;
		height = egg->getContentSize().height;

		if (isBeSelected())
		{
			// 选中动作
			CCRepeatForever * forever;
			forever = CCRepeatForever::create(CCJumpTo::create(0.3, egg->getPosition(), height/4, 1));
			egg->runAction(forever);
		}
		else
		{
			egg->stopAllActions();
			egg->setPosition(ccp(0,0));
		}
	}
}

/*********************************************
玉面公主
**********************************************/
PetYuMianGongZhu::PetYuMianGongZhu(void)
	:Pet()
{

}

PetYuMianGongZhu::~PetYuMianGongZhu(void)
{

}

void PetYuMianGongZhu::initSelf(void)
{
#ifdef									GOLDEN_MINER2_FLASH_FRAME
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("yumiangongzhu", "", "flash/yumiangongzhu/yumiangongzhu.png", "flash/yumiangongzhu/yumiangongzhu.plist", "flash/yumiangongzhu/skeleton.xml");
	armature = Armature::create("yumiangongzhu");
#else
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("yumian", "", "flash/yumiangongzhu/yumiangongzhu.png", "flash/yumiangongzhu/yumiangongzhu.plist", "flash/yumiangongzhu/skeleton.xml");
	armature = Armature::create("yumian");
#endif
	addChild(armature, PET_LAYER_OBJECT);
	egg = CCSprite::create("guaiwuwo/dan2.png");
	addChild(egg, PET_LAYER_OBJECT);

	elementId = PET_ELEMENT_YUMIANGONGZHU;

	Pet::initSelf();
}

int PetYuMianGongZhu::doAction(float _f)
{
	return Pet::doAction(_f);
}

void PetYuMianGongZhu::setTip(void)
{
	if (frame == NULL)
	{
		//frame = CCSprite::create("guaiwuwo/maopao.png");
		//addChild(frame, PET_LAYER_TIP);
		//frame->setPosition(ccp(75,105));
		//if (lifeStatus == PET_LIFE_STATUS_EGG)
		//{
		//	tip = CCSprite::create("guaiwuwo/30.png");
		//}
		//else
		//{
		//	tip = CCSprite::create("guaiwuwo/34.png");
		//}
		//frame->addChild(tip);
		//tip->setPosition(ccp(60,80));
		if (lifeStatus == PET_LIFE_STATUS_BABY)
		{
			frame = CCSprite::create("duihuakuang/34.png");
		}
		else
		{
			frame = CCSprite::create("duihuakuang/30.png");
		}
		addChild(frame, PET_LAYER_TIP);
		frame->setPosition(ccp(75,105));
	}
	else
	{	
		CCTexture2D *pTexture;
		CCRect rect;
		if (lifeStatus == PET_LIFE_STATUS_BABY)
		{
			pTexture = CCTextureCache::sharedTextureCache()->addImage("duihuakuang/34.png");
			if (pTexture)
			{
				rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				frame->setTexture(pTexture);
				frame->setTextureRect(rect);
			}
		}
		else
		{
			pTexture = CCTextureCache::sharedTextureCache()->addImage("duihuakuang/30.png");
			if (pTexture)
			{
				rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				frame->setTexture(pTexture);
				frame->setTextureRect(rect);
			}
		}
		//CCTexture2D *pTexture;
		//CCRect rect;
		//if (lifeStatus == PET_LIFE_STATUS_EGG)
		//{
		//	pTexture = CCTextureCache::sharedTextureCache()->addImage("guaiwuwo/30.png");
		//	if (pTexture)
		//	{
		//		rect = CCRectZero;
		//		rect.size = pTexture->getContentSize();
		//		tip->setTexture(pTexture);
		//		tip->setTextureRect(rect);
		//	}
		//}
		//else
		//{
		//	pTexture = CCTextureCache::sharedTextureCache()->addImage("guaiwuwo/34.png");
		//	if (pTexture)
		//	{
		//		rect = CCRectZero;
		//		rect.size = pTexture->getContentSize();
		//		tip->setTexture(pTexture);
		//		tip->setTextureRect(rect);
		//	}
		//}
	}
	Pet::setTip();
}

void PetYuMianGongZhu::setLifeStatus(int _status)
{
	Pet::setLifeStatus(_status);

#ifdef									GOLDEN_MINER2_FLASH_FRAME
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		armature->setPosition(ccp(-18, -28));
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		armature->setPosition(ccp(-25, -30));
	} 
#else
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		armature->setPosition(ccp(-22, -22));
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		armature->setPosition(ccp(-25, -18));
	} 
#endif
}

void PetYuMianGongZhu::exchangeAction(void)
{
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		// baby动作
#ifdef										GOLDEN_MINER2_FLASH_FRAME
		armature->getAnimation()->play("ymnaizui", 0, 50, 1, TWEEN_EASING_MAX);
#else
		armature->getAnimation()->play("yumiannaizui", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		frame->setVisible(isBeSelected());
		width = armature->getContentSize().width;
		height = armature->getContentSize().height;
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		if (isBeSelected())
		{
			// 选中动作
#ifdef										GOLDEN_MINER2_FLASH_FRAME
			armature->getAnimation()->play("ymmaimeng", 0, 50, 1, TWEEN_EASING_MAX);
#else
			armature->getAnimation()->play("yumianzhaojingzi", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		}
		else
		{
			// 为选中动作
#ifdef										GOLDEN_MINER2_FLASH_FRAME
			armature->getAnimation()->play("ymmaimeng", 0, 50, 1, TWEEN_EASING_MAX);
#else
			armature->getAnimation()->play("yumianmaimeng", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		}
		frame->setVisible(isBeSelected());
		width = armature->getContentSize().width;
		height = armature->getContentSize().height;
	}
	else
	{

		width = egg->getContentSize().width;
		height = egg->getContentSize().height;

		if (isBeSelected())
		{
			// 选中动作
			CCRepeatForever * forever;
			forever = CCRepeatForever::create(CCJumpTo::create(0.3, egg->getPosition(), height/4, 1));
			egg->runAction(forever);
		}
		else
		{
			egg->stopAllActions();
			egg->setPosition(ccp(0,0));
		}
	}
}

/*********************************************
灵感大王
**********************************************/
PetLingGanDaWang::PetLingGanDaWang(void)
:Pet()
{

}

PetLingGanDaWang::~PetLingGanDaWang(void)
{

}

void PetLingGanDaWang::initSelf(void)
{
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("linggandawang", "", "flash/linggandawang/linggandawang.png", "flash/linggandawang/linggandawang.plist", "flash/linggandawang/skeleton.xml");
	armature = Armature::create("linggandawang");
	addChild(armature, PET_LAYER_OBJECT);
	egg = CCSprite::create("guaiwuwo/dan4.png");
	addChild(egg, PET_LAYER_OBJECT);

	elementId = PET_ELEMENT_LINGGANDAWANG;

	Pet::initSelf();
}

int PetLingGanDaWang::doAction(float _f)
{
	return Pet::doAction(_f);
}

void PetLingGanDaWang::setTip(void)
{
	if (frame == NULL)
	{
		//frame = CCSprite::create("guaiwuwo/maopao.png");
		//addChild(frame, PET_LAYER_TIP);
		//frame->setPosition(ccp(75,105));
		//if (lifeStatus == PET_LIFE_STATUS_EGG)
		//{
		//	tip = CCSprite::create("guaiwuwo/29.png");
		//}
		//else
		//{
		//	tip = CCSprite::create("guaiwuwo/33.png");
		//}
		//frame->addChild(tip);
		//tip->setPosition(ccp(60,80));
		if (lifeStatus == PET_LIFE_STATUS_BABY)
		{
			frame = CCSprite::create("duihuakuang/33.png");
		}
		else
		{
			frame = CCSprite::create("duihuakuang/29.png");
		}
		addChild(frame, PET_LAYER_TIP);
		frame->setPosition(ccp(75,105));
	}
	else
	{	
		CCTexture2D *pTexture;
		CCRect rect;
		if (lifeStatus == PET_LIFE_STATUS_BABY)
		{
			pTexture = CCTextureCache::sharedTextureCache()->addImage("duihuakuang/33.png");
			if (pTexture)
			{
				rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				frame->setTexture(pTexture);
				frame->setTextureRect(rect);
			}
		}
		else
		{
			pTexture = CCTextureCache::sharedTextureCache()->addImage("duihuakuang/29.png");
			if (pTexture)
			{
				rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				frame->setTexture(pTexture);
				frame->setTextureRect(rect);
			}
		}
		//CCTexture2D *pTexture;
		//CCRect rect;
		//if (lifeStatus == PET_LIFE_STATUS_EGG)
		//{
		//	pTexture = CCTextureCache::sharedTextureCache()->addImage("guaiwuwo/29.png");
		//	if (pTexture)
		//	{
		//		rect = CCRectZero;
		//		rect.size = pTexture->getContentSize();
		//		tip->setTexture(pTexture);
		//		tip->setTextureRect(rect);
		//	}
		//}
		//else
		//{
		//	pTexture = CCTextureCache::sharedTextureCache()->addImage("guaiwuwo/33.png");
		//	if (pTexture)
		//	{
		//		rect = CCRectZero;
		//		rect.size = pTexture->getContentSize();
		//		tip->setTexture(pTexture);
		//		tip->setTextureRect(rect);
		//	}
		//}
	}
	Pet::setTip();
}

void PetLingGanDaWang::setLifeStatus(int _status)
{
	Pet::setLifeStatus(_status);
#ifdef								GOLDEN_MINER2_FLASH_FRAME
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		armature->setPosition(ccp(-28, -32));
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		armature->setPosition(ccp(-40, -30));
	} 
#else
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		armature->setPosition(ccp(-24, -15));
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		armature->setPosition(ccp(-30, -10));
	} 
#endif
}

void PetLingGanDaWang::exchangeAction(void)
{
	if (lifeStatus == PET_LIFE_STATUS_BABY)
	{
		// baby动作
#ifdef					GOLDEN_MINER2_FLASH_FRAME
		armature->getAnimation()->play("lgdwnaizui", 0, 50, 1, TWEEN_EASING_MAX);
#else
		armature->getAnimation()->play("lgdwnaizui", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		frame->setVisible(isBeSelected());

		width = armature->getContentSize().width;
		height = armature->getContentSize().height;
	}
	else if (lifeStatus == PET_LIFE_STATUS_GROW)
	{
		if (isBeSelected())
		{
			// 选中动作
#ifdef					GOLDEN_MINER2_FLASH_FRAME
			armature->getAnimation()->play("lgdwmaimeng", 0, 50, 1, TWEEN_EASING_MAX);
#else
			armature->getAnimation()->play("lgdwtupaopao", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		}
		else
		{
			// 为选中动作
#ifdef					GOLDEN_MINER2_FLASH_FRAME
			armature->getAnimation()->play("lgdwmaimeng", 0, 50, 1, TWEEN_EASING_MAX);
#else
			armature->getAnimation()->play("lgdwmaimeng", 0, 50, 1, TWEEN_EASING_MAX);
#endif
		}
		frame->setVisible(isBeSelected());
		width = armature->getContentSize().width;
		height = armature->getContentSize().height;
	}
	else
	{

		width = egg->getContentSize().width;
		height = egg->getContentSize().height;

		if (isBeSelected())
		{
			// 选中动作
			CCRepeatForever * forever;
			forever = CCRepeatForever::create(CCJumpTo::create(0.3, egg->getPosition(), height/4, 1));
			egg->runAction(forever);
		}
		else
		{
			egg->stopAllActions();
			egg->setPosition(ccp(0,0));
		}
	}
}

/*********************************************************
怪物管理者
*********************************************************/
PetManager::PetManager(void)
{

}

PetManager::~PetManager(void)
{

}

Pet * PetManager::getPetByElementId(int _elementId)
{
	Pet * pet = NULL;

	switch(_elementId)
	{
	case PET_ELEMENT_JINGXIGUI:
		pet = new PetJingXiGui();
		pet->initSelf();
		pet->exchangeAction();
		break;
	case PET_ELEMENT_NIUMOWANG:
		pet = new PetNiuMoWang();
		pet->initSelf();
		pet->exchangeAction();
		break;
	case PET_ELEMENT_YUMIANGONGZHU:
		pet = new PetYuMianGongZhu();
		pet->initSelf();
		pet->exchangeAction();
		break;
	case PET_ELEMENT_LINGGANDAWANG:
		pet = new PetLingGanDaWang();
		pet->initSelf();
		pet->exchangeAction();
		break;
	default:
		break;
	}

	return pet;
}