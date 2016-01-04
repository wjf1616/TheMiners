#include "Rope.h"
#include "Hanger.h"

#define				ROPE_EXCHANGE_CONTROL_THROW					3

double lengthOriginal = 64;// 绳子自身长度(可显示的)

Rope::Rope(Hanger * hanger)
{
	CCSprite();

	initWithFile("youxi/shenzi.png");
	
	setScale(0.8);
	lengthOriginal = getContentSize().height * 0.8;

	setRotation(angleCenter - hanger->getAngle());
	changePosition(hanger);

	autorelease();
}


Rope::~Rope(void)
{
}


void Rope::doAction(float dt, Hanger * hanger)
{
	switch(hanger->getStatus())
	{
		case HANGER_STATUS_SWAYING:
			// 需要多转换一下角度
			setRotation(angleCenter - hanger->getAngle());
			changePosition(hanger);
			break;
		case HANGER_STATUS_THROW:
		case HANGER_STATUS_PULL_HAVING:
		case HANGER_STATUS_PULL_UNHAVING:
			// 放缩和重定义位置
			changePosition(hanger);
			break;
		default:
			break;
	}

	switch(status)
	{
	case ROPE_STATUS_NORMAL:
		break;
	case ROPE_STATUS_THROW:
		scaleExchange--;
		if (scaleExchange == 0)
		{
			scaleExchange = ROPE_EXCHANGE_CONTROL_THROW;
			setScaleX(-getScaleX());
		}
		break;
	case ROPE_STATUS_INTERSECT:
		setScaleX(-getScaleX());
		break;
	case ROPE_STATUS_PULL:
		setScaleX(-getScaleX());
		break;
	default:
		break;
	}
}

void Rope::changePosition(Hanger * hanger)
{
	double width = getContentSize().width;
	double height = getContentSize().height;
	double precent = abs((Global::getInstance()->getcentreY() - hanger->getCurrY()) / (sin(hanger->getAngle() / angleChange * pi)));
	double positionX = (Global::getInstance()->getcentreX() + hanger->getCurrX())/2;
	double positionY = (Global::getInstance()->getcentreY() + hanger->getCurrY())/2;
	setPosition(ccp(positionX,positionY ));
	setTextureRect(*new CCRect(0,(height-precent)/2,width,precent/0.8));
}

void Rope::changeImageByStatus(int _status, Hanger * _hanger)
{
	status = _status;
	CCTexture2D *pTexture;
	CCRect rect;
	// 添加根据状态换图的代码 (注意添加这里width 和 height跟随图片的宽高变换)
	switch(status)
	{
	case ROPE_STATUS_NORMAL:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("youxi/shenzi.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
		}
		lengthOriginal = getContentSize().height * 0.8;
		break;
	case ROPE_STATUS_THROW:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("youxi/shenzi2.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
		}
		lengthOriginal = getContentSize().height * 0.8;
		scaleExchange = ROPE_EXCHANGE_CONTROL_THROW;
		break;
	case ROPE_STATUS_INTERSECT:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("youxi/shenzi3.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
		}
		lengthOriginal = getContentSize().height * 0.8;
		break;
	case ROPE_STATUS_PULL:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("youxi/shenzi4.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
		}
		lengthOriginal = getContentSize().height * 0.8;
		break;
	default:
		break;
	}
	changePosition(_hanger);
}
