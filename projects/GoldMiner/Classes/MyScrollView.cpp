#include "MyScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

MyScrollView::MyScrollView(int _type)
{
	type = _type;
	initById();
	autorelease();
}


MyScrollView::~MyScrollView(void)
{
	CCLOG("MyScrollView::~MyScrollView");
}

void MyScrollView::initById(void)
{
	tableView = CCTableView::create(this, CCSizeMake(374, 229));
	tableView->setDirection(kCCScrollViewDirectionHorizontal);
	tableView->setDelegate(this);
	this->addChild(tableView);
	tableView->reloadData();
}

//bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
//{
//
//}
//
//void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
//{
//
//}
//
//void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
//{
//
//}

void MyScrollView::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
	CCLog("getContentOffset.x = %f, getContentOffset.y = %f", tableView->getContentOffset().x, tableView->getContentOffset().y);
}

void MyScrollView::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx());
}

void MyScrollView::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
	CCLOG("cell Highlight at index: %i", cell->getIdx());
}

void MyScrollView::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
	CCLOG("cell Unhighlight at index: %i", cell->getIdx());
}

void MyScrollView::tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell)
{
	CCLOG("cell Recycle at index: %i", cell->getIdx());
}

CCSize MyScrollView::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(374, 229);
}

CCTableViewCell* MyScrollView::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCLOG("idx = %d", idx);
	CCTableViewCell *cell = table->dequeueCell();
	CCSprite *sprite;
	switch(idx)
	{
	case 0:
		sprite = CCSprite::create("bangzhuguanyu/1.png");
		break;
	case 1:
		sprite = CCSprite::create("bangzhuguanyu/2.png");
		break;
	case 2:
		sprite = CCSprite::create("bangzhuguanyu/3.png");
		break;
	case 3:
		sprite = CCSprite::create("bangzhuguanyu/4.png");
		break;
	case 4:
		sprite = CCSprite::create("bangzhuguanyu/5.png");
		break;
	case 5:
		sprite = CCSprite::create("bangzhuguanyu/6.png");
		break;
	case 6:
		sprite = CCSprite::create("bangzhuguanyu/7.png");
		break;
	default:
		break;
	}
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(ccp(0, 0));
		sprite->setTag(123);
		cell->addChild(sprite);
	}
	else
	{
		cell->removeChildByTag(123);
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(ccp(0, 0));
		sprite->setTag(123);
		cell->addChild(sprite);
	}
	return cell;
}

unsigned int MyScrollView::numberOfCellsInTableView(CCTableView *table)
{
	return 7;
}