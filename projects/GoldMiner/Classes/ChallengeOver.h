#ifndef		__ChallengeOver_H__
#define		__ChallengeOver_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "Player.h"

USING_NS_CC_EXT;

class ChallengeOver :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
	, public cocos2d::extension::CCEditBoxDelegate
	, public cocos2d::extension::CCTableViewDataSource
	, public cocos2d::extension::CCTableViewDelegate
{
public:
	ChallengeOver(void);
	~ChallengeOver(void);

	virtual void OnExit(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChallengeOver, create);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void doAnimationCompleted(void);

	void doAction(float _f);

	void onMenuItemConfirmClicked(cocos2d::CCObject * pSender);
	void onMenuItemConfirm1Clicked(cocos2d::CCObject * pSender);


	virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager, int _layerType, cocos2d::CCLayer *_ccLayer);


	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	//Http Response Callback
	void onUpdateChallengeDateCompleted(cocos2d::CCNode *sender, void *data);// 更新数据回填函数
	void onGetChallengeDateCompleted(cocos2d::CCNode *sender, void *data);// 获取排行榜信息会掉函数
private:
	void upDateChallengeDateSuccess(void);

	int forwardType;

	CCLayer * forwardLayer;

	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器

	cocos2d::extension::CCEditBox* m_pEditName;

	CCTableView* tableView;

	cocos2d::CCSprite * scrollBarBackground;
	cocos2d::CCSprite * scrollBarItem;

	ChallengeRecord newRecord;
};

class ChallengeOverCeil :
	public cocos2d::extension::CCTableViewCell
{
	virtual void draw();
};

class ChallengeOverCeilLayer :
	public cocos2d::CCLayer
{
public:
	ChallengeOverCeilLayer(int _index);
	~ChallengeOverCeilLayer();

	void setByIndex(int _index);

private:
	cocos2d::CCLabelTTF * index;
	//cocos2d::extension::CCEditBox* name;
	cocos2d::CCLabelTTF * name;
	cocos2d::CCLabelTTF * level;
	cocos2d::CCLabelTTF * score;

	cocos2d::CCSprite * backGround;
	cocos2d::CCSprite * lineSprite;
};

#endif