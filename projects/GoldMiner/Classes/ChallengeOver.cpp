#include "ChallengeOver.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "NetWork.h"
#include "GMJson.h"
#include "MainAppendLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define					CHALLENGE_OVER_WIN_SHINE_TAG							10086

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	#define					CHALLENGE_CEIL_FONT_NAME							"Paint Boy"
#else
	#define					CHALLENGE_CEIL_FONT_NAME							"fonts/Paint Boy.ttf"
#endif							

#define					CHALLENGE_CEIL_FONT_SIZE								25			// 字体大小
#define					CHALLENGE_CEIL_HIGH										44			// 单元高度
#define					CHALLENGE_CEIL_WIDTH									550			// 单元宽度
#define					CHALLENGE_CEIL_INDEX_POSITIONX							30			// 名次位置
#define					CHALLENGE_CEIL_NAME_POSITIONX							180			// 名字位置
#define					CHALLENGE_CEIL_LEVEL_POSITIONX							340			// 层数位置
#define					CHALLENGE_CEIL_SCARE_POSITIONX							480			// 得分位置
#define					CHALLENGE_CEIL_LINE_POSITIONX							270			// 得分位置

#define					CHALLENGE_SCROLL_BAR_X									680//280//680			// 滚动条坐标x
#define					CHALLENGE_SCROLL_BAR_Y									225//0//225			// 滚动条坐标y

#define					CHALLENGE_CEIL_NUM_MAX									5			// 最大显示数

#define					CHALLENGE_CELL_NUM_COUNT								20

enum
{
	ChallengeOver_XIAOSHI_TYPE_SHOP = 0,
	ChallengeOver_XIAOSHI_TYPE_MENU,
	ChallengeOver_XIAOSHI_TYPE_REPLAY,
	ChallengeOver_XIAOSHI_TYPE_NEXT
};

static const ccColor3B myWordColor = {110,19,19};
static const std::string words = "player";

ChallengeOver::ChallengeOver(void)
	: mAnimationManager(NULL)
{
	forwardLayer = NULL;
	forwardType = -1;
}

void ChallengeOver::OnExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
	CCLayer::onExit();
}

ChallengeOver::~ChallengeOver(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CCLOG("ChallengeOver::~ChallengeOver");
}

SEL_MenuHandler ChallengeOver::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnConfirm", ChallengeOver::onMenuItemConfirmClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnConfirm1", ChallengeOver::onMenuItemConfirm1Clicked);

	return NULL;
}

cocos2d::SEL_CallFuncN ChallengeOver::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler ChallengeOver::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool ChallengeOver::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void ChallengeOver::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager, int _layerType, cocos2d::CCLayer *_ccLayer)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;

	forwardType = _layerType;
	forwardLayer = _ccLayer;

	if (forwardType != LAYER_ID_MAIN_APPEND && Player::getInstance()->getChallengeAppendName())
	{
		// top
		CCScale9Sprite * _tmp = CCScale9Sprite::create("paihangbang/tiao.png");
		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("paihangbang/tiao.png");
		m_pEditName = CCEditBox::create(pTexture->getContentSize(), _tmp);
		m_pEditName->setFontName(CHALLENGE_CEIL_FONT_NAME);
		m_pEditName->setFontSize(CHALLENGE_CEIL_FONT_SIZE);
		m_pEditName->setFontColor(myWordColor);
		m_pEditName->setPlaceHolder(words.c_str());
		m_pEditName->setPlaceholderFontColor(ccWHITE);
		m_pEditName->setMaxLength(8);
		m_pEditName->setReturnType(kKeyboardReturnTypeDone);
		m_pEditName->setDelegate(this);
		m_pEditName->setPositionY(20);
		getChildByTag(1)->getChildByTag(2)->addChild(m_pEditName);

		// 转光
		CCSprite* sp1 = CCSprite::create("yindao/guang2.png");
		CCRotateBy* rot = CCRotateBy::create(2, 360);
		CCAction* forever = CCRepeatForever::create(rot);
		sp1->runAction(forever);           
		sp1->setPosition(ccp(400,240));   
		addChild(sp1, -1, CHALLENGE_OVER_WIN_SHINE_TAG);

		// 赋值得分情况
		newRecord.level = Global::getInstance()->getChallengeLevel()-1;
		newRecord.score = Global::getInstance()->getChallengeCountSum();
		newRecord.roleId = Global::getInstance()->getSelectRoleId();

		mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	}
	else
	{
		// 进度条
		scrollBarBackground = CCSprite::create("paihangbang/jindu1.png");
		scrollBarBackground->setPosition(ccp(CHALLENGE_SCROLL_BAR_X, CHALLENGE_SCROLL_BAR_Y));
		getChildByTag(2)->addChild(scrollBarBackground);
		//getChildByTag(2)->getChildByTag(2)->addChild(scrollBarBackground);
		scrollBarItem = CCSprite::create("paihangbang/jindu2.png");
		scrollBarItem->setPosition(ccp(CHALLENGE_SCROLL_BAR_X, CHALLENGE_SCROLL_BAR_Y + scrollBarBackground->getContentSize().height/2));
		getChildByTag(2)->addChild(scrollBarItem,1);
		//getChildByTag(2)->getChildByTag(2)->addChild(scrollBarItem,1);
		scrollBarBackground->setVisible(true);
		scrollBarItem->setVisible(true);
		// 更新显示(排行)
		tableView = CCTableView::create(this, CCSizeMake(CHALLENGE_CEIL_WIDTH, CHALLENGE_CEIL_NUM_MAX*CHALLENGE_CEIL_HIGH));
		tableView->setDirection(kCCScrollViewDirectionVertical);
		tableView->setDelegate(this);
		tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
		getChildByTag(2)->getChildByTag(2)->addChild(tableView);
		tableView->setPosition(ccp(-280,-133));
		tableView->reloadData();

		mAnimationManager->runAnimationsForSequenceNamed("tanchu");
	}
	
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(ChallengeOver::doAnimationCompleted));
	
	
	CC_SAFE_RETAIN(mAnimationManager);
}

// 确定
void ChallengeOver::onMenuItemConfirmClicked(cocos2d::CCObject * pSender)
{
	// 添加新的记录
	//Player::getInstance()->setChallengeNum(0);
	//Player::getInstance()->addChallenge(newRecord);

	// 首次提交数据
	Player::getInstance()->updateChallenge(newRecord);
	NetWork::getInstance()->updateSelfChallengeDate(newRecord, this, callfuncND_selector(ChallengeOver::onUpdateChallengeDateCompleted));
}

// 排行
void ChallengeOver::onMenuItemConfirm1Clicked(cocos2d::CCObject * pSender)
{
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi1");
	scrollBarBackground->setVisible(false);
	scrollBarItem->setVisible(false);
}

void ChallengeOver::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi") == 0)
	{	
		mAnimationManager->runAnimationsForSequenceNamed("tanchu");
		tableView->setVisible(true);
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"tanchu") == 0)
	{
		scrollBarBackground->setVisible(true);
		scrollBarItem->setVisible(true);
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi1") == 0)
	{	
		if (forwardType == LAYER_ID_MAIN_APPEND)
		{
			// 回到结算页面
			Global::getInstance()->s->removeLayerToRunningScene(this);
			((MainAppendLayer *)forwardLayer)->reBack();
		}
		else
		{
			// 回到结算页面
			Global::getInstance()->s->removeLayerToRunningScene(this);
			Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getChallengeCountMenu(this));
		}
	}
}

void ChallengeOver::onUpdateChallengeDateCompleted(cocos2d::CCNode *sender, void *data)
{
	CCHttpResponse *response = (CCHttpResponse*)data;

	if (!response || !response->isSucceed())
	{
		if (response == NULL)
		{
			CCLOG("response is NULL");
		}
		else
		{
			CCLog("response failed");
			CCLog("error buffer: %s", response->getErrorBuffer());
		}

		Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getChallengeCountMenu(this));
		return;
	}

	upDateChallengeDateSuccess();
}

void ChallengeOver::upDateChallengeDateSuccess(void)
{
	// 已经上传
	Player::getInstance()->setChallengeUpdate(false);
	Player::getInstance()->setChallengeAppendName(false);

	NetWork::getInstance()->getChallengeDate(this, callfuncND_selector(ChallengeOver::onGetChallengeDateCompleted));

}

void ChallengeOver::onGetChallengeDateCompleted(cocos2d::CCNode *sender, void *data)
{
	removeChildByTag(CHALLENGE_OVER_WIN_SHINE_TAG);
	CCHttpResponse *response = (CCHttpResponse*)data;

	if (!response || !response->isSucceed())
	{
		if (response == NULL)
		{
			CCLOG("response is NULL");
		}
		else
		{
			CCLog("response failed   filedcode = %d", response->getResponseCode());
			CCLog("error buffer: %s", response->getErrorBuffer());
		}

		Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getChallengeCountMenu(this));
		return;
	}

	// 进度条
	scrollBarBackground = CCSprite::create("paihangbang/jindu1.png");
	scrollBarBackground->setPosition(ccp(CHALLENGE_SCROLL_BAR_X, CHALLENGE_SCROLL_BAR_Y));
	scrollBarBackground->setVisible(false);
	getChildByTag(2)->addChild(scrollBarBackground);
	//getChildByTag(2)->getChildByTag(2)->addChild(scrollBarBackground);
	scrollBarItem = CCSprite::create("paihangbang/jindu2.png");
	scrollBarItem->setPosition(ccp(CHALLENGE_SCROLL_BAR_X, CHALLENGE_SCROLL_BAR_Y + scrollBarBackground->getContentSize().height/2));
	scrollBarItem->setVisible(false);
	getChildByTag(2)->addChild(scrollBarItem,1);
	//getChildByTag(2)->getChildByTag(2)->addChild(scrollBarItem,1);
	// 更新显示(排行)
	tableView = CCTableView::create(this, CCSizeMake(CHALLENGE_CEIL_WIDTH, CHALLENGE_CEIL_NUM_MAX*CHALLENGE_CEIL_HIGH));
	tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	getChildByTag(2)->getChildByTag(2)->addChild(tableView);
	tableView->setPosition(ccp(-280,-133));
	tableView->reloadData();
	tableView->setVisible(false);

	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");

	// dump data
	std::vector<char> *buffer = response->getResponseData();
	//把vector转换成std::string
	std::string buf(buffer->begin(),buffer->end()); 
	//buf.c_str()把std::string转换成string;
	GMJson * _json = new GMJson();
	_json->getChallengeDate(buf);
	delete(_json);
}

void ChallengeOver::doAction(float _f)
{

}

void ChallengeOver::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
	CCLog("editBox %p DidBegin !", editBox);
}

void ChallengeOver::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
	CCLog("editBox %p DidEnd !", editBox);
}

void ChallengeOver::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
	CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void ChallengeOver::editBoxReturn(CCEditBox* editBox)
{
	CCLog("editBox %p was returned !");
	// 更新玩家名字
	if (strcmp(editBox->getText(), "") == 0)
	{
		newRecord.name = words;
	}
	else
	{
		newRecord.name = editBox->getText();
	}
}
void ChallengeOver::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize ChallengeOver::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(CHALLENGE_CEIL_WIDTH, CHALLENGE_CEIL_HIGH);
}

void ChallengeOver::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
	//CCLOG("ChallengeOver::scrollViewDidScroll       %f      %f", view->getContentOffset().x, view->getContentOffset().y);
	float _appendY = (0 - view->getContentOffset().y)*scrollBarBackground->getContentSize().height/CHALLENGE_CEIL_HIGH/15;

	if (_appendY < 0)
	{
		_appendY = 0;
	}
	else if (_appendY > scrollBarBackground->getContentSize().height)
	{
		_appendY = scrollBarBackground->getContentSize().height;
	}
	_appendY = _appendY - scrollBarBackground->getContentSize().height/2;
	scrollBarItem->setPosition(ccp(CHALLENGE_SCROLL_BAR_X, CHALLENGE_SCROLL_BAR_Y + _appendY));
}

CCTableViewCell* ChallengeOver::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	//CCLOG("idx = %d", idx);
	//CCLOG("ChallengeOver::tableCellAtIndex %f      %f", table->getContentOffset().x, table->getContentOffset().y);
	ChallengeOverCeil *cell = (ChallengeOverCeil *)table->dequeueCell();
	if (!cell) {
		cell = new ChallengeOverCeil();
		cell->autorelease();
		ChallengeOverCeilLayer * ceilLayer = new ChallengeOverCeilLayer(idx);
		cell->addChild(ceilLayer,0,10086);
	}
	else
	{
		((ChallengeOverCeilLayer *)cell->getChildByTag(10086))->setByIndex(idx);
	}

	return cell;
}

unsigned int ChallengeOver::numberOfCellsInTableView(CCTableView *table)
{
	return Global::getInstance()->recordsNum;
}
/******************************************************************
显示内容单元
*******************************************************************/
void ChallengeOverCeil::draw()
{
	CCTableViewCell::draw();
}
/******************************************************************
显示内容单元内容
*******************************************************************/
ChallengeOverCeilLayer::ChallengeOverCeilLayer(int _index)
{
	ChallengeRecord record = Global::getInstance()->records[_index];
	//record.index = _index;
	//record.level = 99;
	//record.score = 99999999;
	//record.name = "啊啊啊";
	char _s[24];
	sprintf(_s, "%d", record.index);
	index = CCLabelTTF::create(_s, CHALLENGE_CEIL_FONT_NAME, CHALLENGE_CEIL_FONT_SIZE);
	index->setColor(myWordColor);
	index->setAnchorPoint(ccp(0.5,0));
	index->setPosition(ccp(CHALLENGE_CEIL_INDEX_POSITIONX, 1 + 12.5));

	//CCScale9Sprite * _tmp = CCScale9Sprite::create("paihangbang/tiao.png");
	//name = CCEditBox::create(*new CCSize(100,30), _tmp);
	//name->setFontName(CHALLENGE_CEIL_FONT_NAME);
	//name->setFontSize(CHALLENGE_CEIL_FONT_SIZE);
	//name->setFontColor(myWordColor);
	//name->setPlaceHolder(record.name.c_str());
	//name->setPlaceholderFontColor(ccWHITE);
	//name->setMaxLength(8);
	//name->setTouchEnabled(false);
	//name->setReturnType(kKeyboardReturnTypeDone);
	name = CCLabelTTF::create(record.name.c_str(), CHALLENGE_CEIL_FONT_NAME, CHALLENGE_CEIL_FONT_SIZE);
	name->setColor(myWordColor);
	name->setAnchorPoint(ccp(0.5,0));
	name->setPosition(ccp(CHALLENGE_CEIL_NAME_POSITIONX, 1 + 8));
	sprintf(_s, "%d", record.level);
	level = CCLabelTTF::create(_s, CHALLENGE_CEIL_FONT_NAME, CHALLENGE_CEIL_FONT_SIZE);
	level->setColor(myWordColor);
	level->setAnchorPoint(ccp(0.5,0));
	level->setPosition(ccp(CHALLENGE_CEIL_LEVEL_POSITIONX, 1 + 8));
	sprintf(_s, "%d", record.score);
	score = CCLabelTTF::create(_s, CHALLENGE_CEIL_FONT_NAME, CHALLENGE_CEIL_FONT_SIZE);
	score->setColor(myWordColor);
	score->setAnchorPoint(ccp(0.5,0));
	score->setPosition(ccp(CHALLENGE_CEIL_SCARE_POSITIONX, 1 + 8));
	lineSprite = CCSprite::create("paihangbang/xian.png");
	lineSprite->setAnchorPoint(ccp(0.5,0));
	lineSprite->setPosition(ccp(CHALLENGE_CEIL_LINE_POSITIONX, 1.0 + lineSprite->getContentSize().height/2));
	backGround = CCSprite::create("paihangbang/lv.png");
	backGround->setVisible(false);
	
	if (_index == Global::getInstance()->myRecordIndex)
	{
		backGround->setVisible(true);
	}
	addChild(backGround);
	addChild(index);
	addChild(name);
	addChild(level);
	addChild(score);
	addChild(lineSprite);
	//setAnchorPoint(CCPointZero);
	setContentSize(*new CCSize(CHALLENGE_CEIL_WIDTH, CHALLENGE_CEIL_HIGH));

	autorelease();
}

ChallengeOverCeilLayer::~ChallengeOverCeilLayer(void)
{

}

void ChallengeOverCeilLayer::setByIndex(int _index)
{
	ChallengeRecord record = Global::getInstance()->records[_index];
	//record.index = _index;
	//record.level = 99;
	//record.score = 99999999;
	//record.name = "啊啊啊啊啊啊啊啊";

	char _s[24];
	sprintf(_s, "%d", record.index);
	index->setString(_s);
	//name->setPlaceHolder(record.name.c_str());
	name->setString(record.name.c_str());
	sprintf(_s, "%d", record.level);
	level->setString(_s);
	sprintf(_s, "%d", record.score);
	score->setString(_s);
	if (_index == Global::getInstance()->myRecordIndex)
	{
		backGround->setVisible(true);
	}
	else
	{
		backGround->setVisible(false);
	}
}