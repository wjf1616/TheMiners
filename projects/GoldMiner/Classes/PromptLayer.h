#ifndef		__PROMPTLAYER_H__
#define		__PROMPTLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class PromptLayer :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	PromptLayer(void);
	~PromptLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PromptLayer, create);

	virtual void onExit(void);
	virtual void onEnter(void);

	virtual void keyBackClicked(void);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void onMenuItemOffClicked(cocos2d::CCObject * pSender);
	void onMenuItemConfirmClicked(cocos2d::CCObject * pSender);

	void setForwardLayer(cocos2d::CCLayer *_ccLayer, int _type);

	void doGuideAward(int _guideId);// �������������ʾ

	void doGamingTip(int _tipId);// �������������ʾ

	void doGuideWin(void);// �������������ʾ

	void miaoZhunXianInformation(void);// ��׼����ʾ

	void miaoBuddahaInformation(void);// �����ʾ

	void bigGateNotOpen(void);// ��ؿ�û�п���

	void simleGateNotOpen(void);// С�ؿ�û�п���

	void hideGateNotOpen(int _hideGateId, cocos2d::CCArray * _array);// ����û�п���

	void notOpen(void); // ��δ����

	void challengeGateNotOpen(void); // ��սģʽû�п���

	void challengeGateOpen(void); // ��սģʽû�п���

	void challengeGateOut(void);// ��սģʽ�Ƴ���ʾ

	void challengeGateReplay(void);// ��սģʽ������ʾ

	void addNewRole(void);// �����µ������ɫ

	void payRoleIsHaving(void);// �Ʒѵ������Ѿ�ӵ��

	void addNewGate(int _mapId);// �����µ������ɫ

	void addNewHideGate(int _hideGateId);// ��ʼ���عؿ�

	void targetInformationByTargetId(int targetId);// ���߽���

	void specailFood(void);// �Ƿ�Ҫ��������ʾ
	
	void isCheer(void);// �Ƿ�������ʾ

	void isChallengeShopBack(void);

	void isBack(void);// �Ƿ�ȷ������

	void isReplay(void);// �Ƿ�ȷ������

	void jewelInformation(void);// ��ʯ������Ϣ
	void moonLightInformation(void);// ��ʯ������Ϣ
	void roleIntruduceById(int _roleId);

	void petParkInformation(void);// ���������˵��

	void drawOpenCost(const char _cost[]);// ��������ʾ

	void doAnimationCompleted(void);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ����������
	cocos2d::CCLayer * forwardLayer;
	int forwardType;

	int type;

	bool isAward;
	float timeCount;
};

#endif

