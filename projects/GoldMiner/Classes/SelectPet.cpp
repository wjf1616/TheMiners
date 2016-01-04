#include "SelectPet.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "RoleInformation.h"
#include "Player.h"
#include "CartoonLayer.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "PromptLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define			SelectPet_YUN_ASIDE						11	
#define			SelectPet_FRAME_ASIDE					111
#define			SelectPet_BUTTON_ASIDE					11
#define			SelectPet_YUN_MIDDLE					21	
#define			SelectPet_FRAME_MIDDLE					121
#define			SelectPet_BUTTON_MIDDLE					21

#define			SelectPet_BUTTON_SELECTED_UP			102
#define			SelectPet_BUTTON_UNSELECTED_DOWN		101


#define		SelectPet_POINT_Y										40
#define		SelectPet_POINT_X										30


static const ccColor3B myGrey={60,60,60};
static const ccColor4B myGrey4 = {0,0,0,200};

SelectPet::SelectPet(void)
	: mAnimationManager(NULL)
{
	isDoAction = false;
}

void SelectPet::onEnter(void)
{
	CCLayer::onEnter();

	if (Player::getInstance()->getSelectPet() <= 0)
	{
		return;
	}


	petsId = new cocos2d::CCArray();
	petsSprite = new cocos2d::CCArray();
	petsHaving = new cocos2d::CCArray();
	petsUnHaving = new cocos2d::CCArray();

	for (int i = PET_ELEMENT_XIAOZUANFENG; i < PET_ELEMENT_COUNT; i++)
	{
		if ((i == PET_ELEMENT_XIAOZUANFENG)
			|| (i == PET_ELEMENT_LINGLICHONG))
		{
			continue;
		}

		if (Player::getInstance()->getSelectPet() == i)
		{
			selectPet = getSpriteByTypeId(i);
			selectPet->setScale(0.8);
			getChildByTag(1)->getChildByTag(5)->addChild(selectPet);
		}
		else
		{
			petsId->addObject(CCInteger::create(i));
			petsSprite->addObject(getSpriteByTypeId(i));
			getChildByTag(1)->getChildByTag(5 + petsSprite->count())->addChild((CCSprite *)petsSprite->lastObject(), 1);
			petsHaving->addObject(CCSprite::create("xuanrenyemian/dianji.png"));
			getChildByTag(1)->getChildByTag(5 + petsSprite->count())->addChild((CCSprite *)petsHaving->lastObject(), 2);
			petsUnHaving->addObject(CCSprite::create("xuanrenyemian/yangcheng.png"));
			getChildByTag(1)->getChildByTag(5 + petsSprite->count())->addChild((CCSprite *)petsUnHaving->lastObject(), 2);

			if (Player::getInstance()->getPetHeart(i) == Global::getInstance()->getPetHeartFull(i))
			{
				((CCSprite *)petsHaving->lastObject())->setVisible(true);
				((CCSprite *)petsUnHaving->lastObject())->setVisible(false);
			}
			else
			{
				((CCSprite *)petsHaving->lastObject())->setVisible(false);
				((CCSprite *)petsUnHaving->lastObject())->setVisible(true);
			}
		}
	}
};

void SelectPet::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

SelectPet::~SelectPet(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CCObject * p = NULL;

	CCARRAY_FOREACH(petsId, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}

	CCARRAY_FOREACH(petsSprite, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}

	CCARRAY_FOREACH(petsHaving, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}

	CCARRAY_FOREACH(petsUnHaving, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}

	CCLOG("SelectPet::~SelectPet");
}

void SelectPet::setForwardLayer(cocos2d::CCLayer * _layer)
{
}

SEL_MenuHandler SelectPet::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {

	return NULL;
}

SEL_CCControlHandler SelectPet::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool SelectPet::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void SelectPet::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->runAnimationsForSequenceNamed("cx");
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(SelectPet::doAnimationCompleted));
	isDoAction = true;
	CC_SAFE_RETAIN(mAnimationManager);
}

void SelectPet::doAnimationCompleted(void)
{
	isDoAction = false;
}

bool SelectPet::selectOtherPet(int _index)
{
	if (isDoAction)
	{
		return false;
	}

	if (((CCSprite *)petsHaving->objectAtIndex(_index-2))->isVisible())
	{
		int id = ((CCInteger *)petsId->objectAtIndex(_index-2))->getValue();

		exchangeSpriteByTypeId(selectPet, id);
		petsId->addObject(CCInteger::create(Player::getInstance()->getSelectPet()));
		exchangeSpriteByTypeId((CCSprite *)petsSprite->objectAtIndex(_index-2), Player::getInstance()->getSelectPet());
		Player::getInstance()->setSelectPet(id);
		petsId->exchangeObjectAtIndex(_index-2, petsId->count()-1);
		petsId->removeLastObject();
	}
	return true;
}

bool SelectPet::outOrBack(bool _out)
{
	if (isDoAction)
	{
		return false;
	}

	if (_out)
	{
		mAnimationManager->runAnimationsForSequenceNamed("chuxian");
		isDoAction = true;
	}
	else
	{
		mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
		isDoAction = true;
	}
	return true;
}

cocos2d::CCSprite * SelectPet::getSpriteByTypeId(int _id)
{
	CCSprite * res = NULL;

	switch(_id)
	{
	case PET_ELEMENT_JINGXIGUI:
		res = CCSprite::create("xuanrenyemian/jingxi.png");
		break;
	case PET_ELEMENT_LINGGANDAWANG:
		res = CCSprite::create("xuanrenyemian/linggan.png");
		break;
	case PET_ELEMENT_YUMIANGONGZHU:
		res = CCSprite::create("xuanrenyemian/yumian.png");
		break;
	case PET_ELEMENT_NIUMOWANG:
		res = CCSprite::create("xuanrenyemian/niumo.png");
		break;
	default:
		break;
	}

	return res;
}

void SelectPet::exchangeSpriteByTypeId(cocos2d::CCSprite * _sprite, int _id)
{
	if (_sprite == NULL)
	{
		return;
	}

	CCTexture2D *pTexture;
	CCRect rect;

	switch(_id)
	{
	case PET_ELEMENT_JINGXIGUI:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("xuanrenyemian/jingxi.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			_sprite->setTexture(pTexture);
			_sprite->setTextureRect(rect);
		}
		break;
	case PET_ELEMENT_LINGGANDAWANG:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("xuanrenyemian/linggan.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			_sprite->setTexture(pTexture);
			_sprite->setTextureRect(rect);
		}
		break;
	case PET_ELEMENT_YUMIANGONGZHU:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("xuanrenyemian/yumian.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			_sprite->setTexture(pTexture);
			_sprite->setTextureRect(rect);
		}
		break;
	case PET_ELEMENT_NIUMOWANG:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("xuanrenyemian/niumo.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			_sprite->setTexture(pTexture);
			_sprite->setTextureRect(rect);
		}
		break;
	default:
		break;
	}
}