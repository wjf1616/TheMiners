#ifndef		__SELECTCHALLENGE_H__
#define		__SELECTCHALLENGE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class SelectChallenge :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	SelectChallenge(void);
	~SelectChallenge(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectChallenge, create);

	virtual void onEnter(void);
	void onEnterTransitionDidFinish(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	virtual void keyBackClicked(void);

	void doAction(float _f);
	
	void reBackBackClicked(bool _b);

	void onMenuItemShopClicked(cocos2d::CCObject * pSender);
	void onMenuItemBackClicked(cocos2d::CCObject * pSender);
	void onMenuItemPlayClicked(cocos2d::CCObject * pSender);
	void onMenuItemPlusClicked(cocos2d::CCObject * pSender);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void doAnimationCompleted(void);

	void reBack(int _type, bool _b);

	void reBackWithVisiable(void);

	void startSelf(void);
	void setLoadingLayer(cocos2d::CCLayer * _layer);

	void setCurrProp(bool _isXiangZuo);
private:
	cocos2d::CCLayer * loadingLayer;

	bool isBackGround;
	cocos2d::CCLayerColor * greyLayer;// ��ɫ��

	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ����������

	bool isFristPropPage;
	int currPropIndex;

	int currButtonIndex;

	cocos2d::CCLabelAtlas * ingotNum;// Ԫ��ֵ��ʾ

	cocos2d::CCArray * selectPropSprites;// ��������
	cocos2d::CCArray * selectPropName;//
	cocos2d::CCArray * selectPropId;

	cocos2d::CCArray * pointPropSprites;

	cocos2d::CCSprite * pointIndexSprite;// ����С��
	cocos2d::CCArray * currSelectSprites;// ��ǰnode�ľ���
	cocos2d::CCArray * currSelectPropName;// 

	cocos2d::CCArray * currSelectPropFrameSprites;// ��ǰ���߿�ܵľ��� illusioncui

	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	cocos2d::CCPoint m_touchBeginPos; // ��ʼ������λ��
	cocos2d::CCPoint m_touchEndPos;// ����������λ��
	bool m_touchMove;// �Ƿ񻬶���

	void setNodeBySelectIndex(bool _isXiangZuo);
	void initSprites(void);
	void setBackGround(bool _b);

	bool costChallenge(void);
};

#endif
