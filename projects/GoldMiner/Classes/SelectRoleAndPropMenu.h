#ifndef		__SELECTROLEANDPROPMENU_H__
#define		__SELECTROLEANDPROPMENU_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Prop.h"


class SelectRoleAndPropMenu :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	SelectRoleAndPropMenu(void);
	~SelectRoleAndPropMenu(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectRoleAndPropMenu, create);

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

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void doAnimationCompleted(void);

	void reBack(int _type, bool _b);

	void startSelf(void);
	void setLoadingLayer(cocos2d::CCLayer * _layer);
private:
	cocos2d::CCLayer * loadingLayer;

	bool isBackGround;
	cocos2d::CCLayerColor * greyLayer;// ��ɫ��

	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ����������
	
	int currButtonIndex;// ��ⰴť��index
	bool isFristRolePage;
	bool isFristPropPage;
	bool isRolePage;// �Ƿ�����ѡ�˵Ľ�����
	bool isCheckButtonIsSelected;// �Ƿ�ȥҪ�ж�button��ѡ����
	int currRoleIndex;
	int currPropIndex;
	Prop * propControl;

	cocos2d::CCSprite * coupletSelect;// ������
	cocos2d::CCSprite * coupletAbout;// δ����
	cocos2d::CCLabelAtlas * ingotNum;// Ԫ��ֵ��ʾ
	cocos2d::CCSprite * rolePageButton;// ����ѡ��ť
	cocos2d::CCSprite * propPageButton;// ����ѡ��ť

	cocos2d::CCArray * selectRoleSpritesName;// ��������
	cocos2d::CCArray * selectRoleSprites;// ��������
	cocos2d::CCArray * selectRoleSpritesIsHaving;// �Ƿ�ӵ�ж���
	cocos2d::CCArray * selectRoleSpritesIsOpen;// �����Ƿ��� illusioncui
	cocos2d::CCArray * selectRoleSpritesSpeed;// �����Ƿ��� illusioncui
	cocos2d::CCArray * selectRoleSpritesPower;// �����Ƿ��� illusioncui
	cocos2d::CCArray * selectRoleSpritesIntroduce;// �����Ƿ��� illusioncui

	cocos2d::CCArray * pointRoleSprites;

	cocos2d::CCArray * selectPropSprites;// ��������
	cocos2d::CCArray * selectPropIntroduce;// ��������
	cocos2d::CCArray * selectPropPrice;//
	cocos2d::CCArray * selectPropName;//
	cocos2d::CCArray * selectPropId;

	cocos2d::CCArray * pointPropSprites;

	cocos2d::CCSprite * pointIndexSprite;// ����С��
	cocos2d::CCArray * currSelectSprites;// ��ǰnode�ľ���
	cocos2d::CCArray * currSelectSpritesIntroduce;// �����Ƿ��� illusioncui
	cocos2d::CCArray * currSelectRoleSpritesIsHaving;// �Ƿ�ӵ�ж���
	cocos2d::CCArray * currSelectRoleSpritesIsOpen;// �����Ƿ��� illusioncui
	cocos2d::CCArray * currSelectPropPrice;// 
	cocos2d::CCArray * currSelectPropName;// 

	cocos2d::CCArray * currSelectYunSprites;// ��ǰ��yun�ľ���
	cocos2d::CCArray * currSelectRoleSpeedBackground;// 
	cocos2d::CCArray * currSelectRolePowerBackground;// 
	cocos2d::CCArray * currSelectRoleSpeed;// 
	cocos2d::CCArray * currSelectRolePower;// 
	cocos2d::CCArray * currSelectPropFrameSprites;// ��ǰ���߿�ܵľ��� illusioncui
	cocos2d::CCArray * currSelectButtonSelectSprites;// ��ǰ������ť�ľ��� illusioncui
	cocos2d::CCArray * currSelectGetSelectSprites;// ��ǰ�Ľ�����ť�ľ���
	cocos2d::CCArray * currSelectAboutSelectSprites;// ��ǰ����ļ��ť�ľ���
	cocos2d::CCArray * currSelectFrameSprites;// ��ǰ��yun�ľ���
	cocos2d::CCArray * currSelectButtonBuySprites;// ��ǰ�Ĺ�����߰�ť�ľ���

	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	cocos2d::CCPoint m_touchBeginPos; // ��ʼ������λ��
	cocos2d::CCPoint m_touchEndPos;// ����������λ��
	bool m_touchMove;// �Ƿ񻬶���

	void changeCurrPage(void);// ѡ�˺͵���ҳ���л�
	void setCurrRole(bool _isXiangZuo);
	void setCurrProp(bool _isXiangZuo);
	void setPageButton(bool _isRolePage);
	void setNodeBySelectIndex(bool _isXiangZuo);
	void checkButtonEvent(void);
	void initSprites(void);
	void setBackGround(bool _b);

	void menuSelect1Callback(cocos2d::CCObject* pSender);
	void menuSelect2Callback(cocos2d::CCObject* pSender);
	void menuSelect3Callback(cocos2d::CCObject* pSender);
	void menuSelect4Callback(cocos2d::CCObject* pSender);
	void menuGet1Callback(cocos2d::CCObject* pSender);
	void menuGet2Callback(cocos2d::CCObject* pSender);
	void menuGet3Callback(cocos2d::CCObject* pSender);
	void menuGet4Callback(cocos2d::CCObject* pSender);
	void menuBuy1Callback(cocos2d::CCObject* pSender);
	void menuBuy2Callback(cocos2d::CCObject* pSender);
	void menuBuy3Callback(cocos2d::CCObject* pSender);
	void menuBuy4Callback(cocos2d::CCObject* pSender);
	void menuAbout1Callback(CCObject* pSender);
	void menuAbout2Callback(CCObject* pSender);
	void menuAbout3Callback(CCObject* pSender);
	void menuAbout4Callback(CCObject* pSender);
};

#endif
