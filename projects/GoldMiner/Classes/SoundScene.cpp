#include "SoundScene.h"
#include "PageControl.h"

USING_NS_CC;


static void onPageClicked(CCPageControl* pageControl, int index, void* data) {
	/*CCPageControlTestLayer* layer = (CCPageControlTestLayer*)data;
	char buf[64];
	sprintf(buf, "page clicked: %d", index);
	layer->m_hint->setString(buf);*/
}

static void onPageChanged(CCPageControl* pageControl, int index, void* data) {
	/*CCPageControlTestLayer* layer = (CCPageControlTestLayer*)data;
	char buf[64];
	sprintf(buf, "page changed: %d", index);
	layer->m_hint->setString(buf);*/
}

static void onPagePositionChanged(CCPageControl* pageControl, CCNode* page, float offset, void* data) {
	float rate = fabs(offset) / (pageControl->getContentSize().width / 2); // change to CCDevice::winHeight if vertical
	page->setScale(1 + 1.0f * (1 - MIN(1, rate)));
	page->setPosition(page->getPositionX(), pageControl->getContentSize().height / 2 + 80 * (1 - MIN(1, rate)));
}
// on "init" you need to initialize your instance
bool SoundScene::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		CC_BREAK_IF(! CCScene::init());
		/* Create an autorelease CCNodeLoaderLibrary. */
		/*CCNode * node  = CoCosBuilderfactory::getNode("02sound.ccbi","soundLayer", SoundLoader::loader());
		if(node != NULL) {
			SetScale(node);
			node->setAnchorPoint(ccp(0,0));
			node->setPosition(ccp(0, 0));
			node->setTag(5000);
			this->addChild(node);
		}*/

		CCPageControl* pageControl = CCPageControl::make();
		
		CCLayerColor* page1 = CCLayerColor::create(ccc4(0,255,0,255));
		page1->setContentSize(CCSize(100,100));
		CCLayerColor* page2 = CCLayerColor::create(ccc4(255,255,0,255));
		CCLayerColor* page3 = CCLayerColor::create(ccc4(255,0,255,255));
		page2->setContentSize(CCSize(100,100));
		page3->setContentSize(CCSize(100,100));
		// page control
		// call setCallback first so that you won't miss some callback
		CCPageControlCallback callback = {
			onPageClicked,
			onPageChanged,
			onPagePositionChanged
		};
		pageControl->setVertical(false);
		pageControl->setCenterY(0);
		pageControl->setCenterX(0);
		pageControl->setCallback(&callback, this);
		pageControl->setPageSpacing(100);
		pageControl->addPage(page1);
		pageControl->addPage(page2);
		pageControl->addPage(page3);
		pageControl->setInitialPage(1);
		//pageControl->setPosition(400,0);
	//	pageControl->setContentSize(CCSize(400,400));
		addChild(pageControl);
		/*pageControl->setTouchEnabled(true);
		pageControl->setVertical(false);
		pageControl->release();*/


		// create a hint label
	/*	m_hint = CCLabel::make("try scroll and click");
		m_hint->setPosition(CCDevice::winWidth / 2, 100);
		addChildLocked(m_hint);*/
	/*	char buff[1024]; 
		std::string a ="ÖÐ¹ú";
		GBKToUTF8(a,"gb2312", "utf-8");
		CCLabelTTF* skillInfo = CCLabelTTF::create(a.c_str(), "Marker Felt", 30);
		skillInfo->setPosition(ccp(200,200));

		addChild(skillInfo);*/
		bRet = true;
	} while (0);

	return bRet;
}





void SoundScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	//CCDirector::sharedDirector()->end();
}

void SoundScene::openTest(const char * pCCBFileName, const char * pCCNodeName, CCNodeLoader * pCCNodeLoader) {
	
}




