#ifndef			__SIMLEGATEMENU_H__
#define			__SIMLEGATEMENU_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Global.h"


class SimleGateMenu :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	SimleGateMenu(void);
	~SimleGateMenu(void);
	void onEnterTransitionDidFinish(void);

	virtual void onExit();

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SimleGateMenu, create);
	//static SimleGateMenu * create(int _bigGateIndex) {
	//	SimleGateMenu * ptr = new SimleGateMenu(_bigGateIndex); 
	//	if(ptr != NULL && ptr->init()) { 
	//		ptr->autorelease(); 
	//		return ptr; 
	//	} 
	//	CC_SAFE_DELETE(ptr); 
	//	return NULL;
	//}
	virtual void keyBackClicked(void);

	virtual void onEnter(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);


	void onMenuItemBackClicked(cocos2d::CCObject * pSender);
	void onMenuItemNextClicked(cocos2d::CCObject * pSender);
	void onMenuItemForwardClicked(cocos2d::CCObject * pSender);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void startSelf(void);
	void setLoadingLayer(cocos2d::CCLayer * _layer);

	void setBackGround(bool _b);
private:
	bool isBackGround;

	cocos2d::CCLayer * loadingLayer;

	cocos2d::CCLayerColor * greyLayer;// ��ɫ��
	//bool isStartPosition;// �Ƿ���1-6nodeΪ����ʾ״̬
	bool isFrist;// �Ƿ��Ǹս���

	int currPageIndex;// ��ǰ��ҳ��ֵ
	int smileGateNum;//С������
	int pageNum;// ҳ����

	bool isInitRect;

	cocos2d::CCArray * pointSprites; // ��ɫС��
	cocos2d::CCSprite * pointIndexSprite;// ����С��

	cocos2d::CCArray * smileGateId;//С�ض����gateid
	cocos2d::CCArray * smileGateIdOpen;// С�ض����gateid��Ϣ
	cocos2d::CCArray * smileGateIdStar;// С�ض����gateid��Ϣ

	cocos2d::CCArray * gateNum;
	cocos2d::CCArray * gateOpenItems;	// �ؿ�item��ʾsprite
	cocos2d::CCArray * gateCloseItems;	// �ؿ�item��ʾsprite
	cocos2d::CCArray * gateItemGetStars;// �ؿ�item������ʾsprite
	cocos2d::CCArray * gateItemUnGetStars;// �ؿ�item������ʾsprite
	cocos2d::CCArray * pageSprites;

	//cocos2d::CCArray * hidePets;// ���عؿ���Ҫ�ĳ������

	cocos2d::extension::CCBAnimationManager * mAnimationManager;// ����������

	cocos2d::CCPoint m_touchBeginPos; // ��ʼ������λ��
	cocos2d::CCPoint m_touchEndPos;// ����������λ��
	cocos2d::CCRect mButton[6];//�Լ�button��λ��
	bool m_touchMove;// �Ƿ񻬶���
	int selectSimleGateButtonIndex;

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void initGateIdInformation(void);
	void setCurrPageIndex(bool _isXiangZuo);
	void initItemSprite(void);
	void doAction(float _f);
	void checkButtonEvent(void);
	void initHidePets(void);
};

#endif
