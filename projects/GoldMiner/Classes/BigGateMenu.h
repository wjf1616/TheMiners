#ifndef		__BIGMENU_H__
#define		__BIGMENU_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class BigGateMenu :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	BigGateMenu(void);
	~BigGateMenu(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BigGateMenu, create);

	virtual void onEnter(void);
	void onEnterTransitionDidFinish(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void doAction(float _f);

	void setBackGround(bool _b);

	void reBackWithVisiable(void);

	void reBackBackClicked(bool _b);

	virtual void keyBackClicked(void);

	void onMenuItemBackClicked(CCObject* pSender);
	void onMenuItemShopClicked(CCObject* pSender);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void startSelf(void);
	void setLoadingLayer(cocos2d::CCLayer * _layer);
	void doAnimationCompleted(void);

	void setCurrPageIndex(bool _isXiangZuo);
private:
	bool isDoAction;
	bool isBackGround;
	
	cocos2d::CCLayer * loadingLayer;
	
	cocos2d::CCLayerColor * greyLayer;// ��ɫ��

	int currPageIndex;// ��ǰ��ҳ��ֵ

	cocos2d::CCArray * pointSprites; // ��ɫС��
	cocos2d::CCSprite * pointIndexSprite;// ����С��

	bool isSelectMyButton;

	cocos2d::CCRect * myButton;//���ļ�ⰴť�ľ��� 

	cocos2d::CCArray * selectGateSprites;// ��������
	cocos2d::CCArray * selectFrameSprites;// �������
	cocos2d::CCArray * selectSuoSprites;// �������
	cocos2d::CCSprite * selectGateTitleSprites;// ��������

	cocos2d::CCArray * gateSprites;// �ؿ���Ӧ����ʾ
	cocos2d::CCArray * gateFrameSprites;// �ؿ��������
	cocos2d::CCArray * gateSuoSprites;// �ؿ��������
	cocos2d::CCArray * gateTitleSprites;// ��������

	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ����������

	cocos2d::CCPoint m_touchBeginPos; // ��ʼ������λ��
	cocos2d::CCPoint m_touchEndPos;// ����������λ��
	bool m_touchMove;// �Ƿ񻬶���

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void checkButtonEvent(void);
	void setNodeBySelectIndex(bool _isXiangZuo);
};

#endif

