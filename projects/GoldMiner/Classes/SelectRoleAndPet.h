#ifndef		__SelectRoleAndPet_H__
#define		__SelectRoleAndPet_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Prop.h"

class SelectPet;

class SelectRoleAndPet :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	SelectRoleAndPet(void);
	~SelectRoleAndPet(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectRoleAndPet, create);

	virtual void onEnter(void);
	void onEnterTransitionDidFinish(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	virtual void keyBackClicked(void);

	void doAction(float _f);

	void onMenuItemShopClicked(cocos2d::CCObject * pSender);
	void onMenuItemBackClicked(cocos2d::CCObject * pSender);
	void onMenuItemPlayClicked(cocos2d::CCObject * pSender);
	void onMenuItemPlusClicked(cocos2d::CCObject * pSender);
	
	void menuBuy1Callback(cocos2d::CCObject* pSender);
	void menuBuy2Callback(cocos2d::CCObject* pSender);
	void menuBuy3Callback(cocos2d::CCObject* pSender);
	void menuBuy4Callback(cocos2d::CCObject* pSender);
	void menuSelect1Callback(cocos2d::CCObject* pSender);
	void menuSelect2Callback(cocos2d::CCObject* pSender);
	void menuSelect3Callback(cocos2d::CCObject* pSender);
	void menuSelect4Callback(cocos2d::CCObject* pSender);
	void menuGet1Callback(cocos2d::CCObject* pSender);
	void menuGet2Callback(cocos2d::CCObject* pSender);
	void menuGet3Callback(cocos2d::CCObject* pSender);
	void menuGet4Callback(cocos2d::CCObject* pSender);
	void menuAbout1Callback(CCObject* pSender);
	void menuAbout2Callback(CCObject* pSender);
	void menuAbout3Callback(CCObject* pSender);
	void menuAbout4Callback(CCObject* pSender);

	void onMenuItemPaySuccess(void);
	void onMenuItemPayFailed(void);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void doAnimationCompleted(void);

	void reBack(int _type, bool _b);

	void startSelf(void);
	void setLoadingLayer(cocos2d::CCLayer * _layer);
	void setForwardLayer(cocos2d::CCLayer * _layer, int _layerType);
	void setBackInformation(cocos2d::CCLayer * _layer, int _layerType);

	void setCurrRole(bool _isXiangZuo);
private:
	bool isSelectMyButton;

	cocos2d::CCRect * myButton;//���ļ�ⰴť�ľ��� 


	cocos2d::CCLayer * forwardLayer;
	int forwardType;

	cocos2d::CCLayer * backLayer;
	int backLayerType;

	cocos2d::CCLayer * loadingLayer;

	bool isPet;
	bool isPetVisiable;
	SelectPet * petLayer;
	int petTouchIndex;

	bool isBackGround;
	cocos2d::CCLayerColor * greyLayer;// ��ɫ��

	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ����������

	cocos2d::CCSprite * introducehuluwa;
	int introducehuluwaindex;

	int currButtonIndex;// ��ⰴť��index
	bool isFristRolePage;
	int currRoleIndex;

	cocos2d::CCSprite * coupletSelect;// ������
	cocos2d::CCSprite * coupletAbout;// δ����
	cocos2d::CCLabelAtlas * ingotNum;// Ԫ��ֵ��ʾ

	cocos2d::CCArray * selectRoleSpritesName;// ��������
	cocos2d::CCArray * selectRoleSpritesTips;// ��������
	cocos2d::CCArray * selectRoleSprites;// ��������
	cocos2d::CCArray * selectRoleSpritesIsHaving;// �Ƿ�ӵ�ж���
	cocos2d::CCArray * selectRoleSpritesIsOpen;// �����Ƿ��� illusioncui
	//cocos2d::CCArray * selectRoleSpritesSpeed;// �����Ƿ��� illusioncui
	//cocos2d::CCArray * selectRoleSpritesPower;// �����Ƿ��� illusioncui
	cocos2d::CCArray * selectRoleSpritesIntroduce;// �����Ƿ��� illusioncui

	cocos2d::CCArray * pointRoleSprites;

	cocos2d::CCSprite * pointIndexSprite;// ����С��
	cocos2d::CCArray * currSelectSprites;// ��ǰnode�ľ���
	cocos2d::CCArray * currSelectSpritesIntroduce;// �����Ƿ��� illusioncui
	cocos2d::CCArray * currSelectRoleSpritesIsHaving;// �Ƿ�ӵ�ж���
	cocos2d::CCArray * currSelectRoleSpritesIsOpen;// �����Ƿ��� illusion

	cocos2d::CCArray * currSelectYunSprites;// ��ǰ��yun�ľ���
	cocos2d::CCArray * currSelectRoleSpeedBackground;// 
	cocos2d::CCArray * currSelectRolePowerBackground;// 
	cocos2d::CCArray * currSelectRoleSpeed;// 
	cocos2d::CCArray * currSelectRolePower;// 
	cocos2d::CCArray * currSelectRoleSpeedInteger;// 
	cocos2d::CCArray * currSelectRolePowerInteger;// 
	cocos2d::CCArray * currSelectButtonSelectSprites;// ��ǰ������ť�ľ��� illusioncui
	cocos2d::CCArray * currSelectGetSelectSprites;// ��ǰ�Ľ�����ť�ľ���
	cocos2d::CCArray * currSelectAboutSelectSprites;// ��ǰ����ļ��ť�ľ���
	cocos2d::CCArray * currSelectButtonBuySprites;// ��ǰ������ť�ľ��� illusioncui
	cocos2d::CCArray * currSelectFrameSprites;// ��ǰ��yun�ľ���

	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	cocos2d::CCPoint m_touchBeginPos; // ��ʼ������λ��
	cocos2d::CCPoint m_touchEndPos;// ����������λ��
	bool m_touchMove;// �Ƿ񻬶���

	void setNodeBySelectIndex(bool _isXiangZuo);
	void initSprites(void);
	void setBackGround(bool _b);
	void setIsPet(bool _b);
};

#endif
