#include "MusicControl.h"
#include "SimpleAudioEngine.h"
#include "Global.h"
#include "PayService.h"

#define		MUSICCONTROL_BACKGROUND_MAIN				"music/sound001.mp3"	// 循环播放
#define		MUSICCONTROL_BACKGROUND_BAOXIANGGUO			"music/sound002.mp3"	// 循环播放
#define		MUSICCONTROL_BACKGROUND_TONGTIANHE			"music/sound003.mp3"	// 循环播放
#define		MUSICCONTROL_BACKGROUND_NVERGUO				"music/sound004.mp3"	// 循环播放
#define		MUSICCONTROL_BACKGROUND_HUOYANSHAN			"music/sound005.mp3"	// 循环播放
#define		MUSICCONTROL_BACKGROUND_LINGSHAN			"music/sound006.mp3"	// 循环播放

#define		MUSICCONTROL_EFFECT_CARRY_TARGET			"music/sound007.mp3"
#define		MUSICCONTROL_EFFECT_GET_TARGET				"music/sound008.mp3"
#define		MUSICCONTROL_EFFECT_BOMB					"music/sound009.mp3"
#define		MUSICCONTROL_EFFECT_BUTTON					"music/sound010.mp3"
#define		MUSICCONTROL_EFFECT_BUY_FINISH				"music/sound012.mp3"
#define		MUSICCONTROL_EFFECT_BUY_FAILED				"music/sound013.mp3"
#define		MUSICCONTROL_EFFECT_THROW					"music/sound015.mp3"	
#define		MUSICCONTROL_EFFECT_PULL					"music/sound014.mp3"	// 循环播放
#define		MUSICCONTROL_EFFECT_PEAL_OPEN				"music/sound016.mp3"
#define		MUSICCONTROL_EFFECT_WIN						"music/sound018.mp3"
#define		MUSICCONTROL_EFFECT_FAILED					"music/sound017.mp3"
#define		MUSICCONTROL_EFFECT_MONEY_FINISH			"music/sound019.mp3"
#define		MUSICCONTROL_EFFECT_SKILL					"music/sound020.mp3"
#define		MUSICCONTROL_EFFECT_PROP					"music/sound021.mp3"
#define		MUSICCONTROL_EFFECT_ABSORB					"music/sound022.mp3"
#define		MUSICCONTROL_EFFECT_DROP					"music/sound023.mp3"
#define		MUSICCONTROL_EFFECT_BALL					"music/sound024.mp3"
#define		MUSICCONTROL_EFFECT_SHOP					"music/sound025.mp3"
#define		MUSICCONTROL_EFFECT_BUY_THING				"music/sound026.mp3"
#define		MUSICCONTROL_EFFECT_BUY_NOTHING				"music/sound027.mp3"
#define		MUSICCONTROL_EFFECT_TIME_START				"music/sound028.mp3"
#define		MUSICCONTROL_EFFECT_TIME_OUT				"music/sound029.mp3"
#define		MUSICCONTROL_EFFECT_TIME_LAST				"music/sound030.mp3"
#define		MUSICCONTROL_EFFECT_START_ONE				"music/sound031.mp3"
#define		MUSICCONTROL_EFFECT_START_TWO				"music/sound032.mp3"
#define		MUSICCONTROL_EFFECT_START_THREE				"music/sound033.mp3"
#define		MUSICCONTROL_EFFECT_JINGXIGUI_CARRIED		"music/sound034.mp3"
//#define		MUSICCONTROL_EFFECT_JINGXIGUI_BABY			"music/sound035.mp3"
//#define		MUSICCONTROL_EFFECT_JINGXIGUI_PET			"music/sound036.mp3"
#define		MUSICCONTROL_EFFECT_LINGGANDAWANG_CARRIED	"music/sound037.mp3"
//#define		MUSICCONTROL_EFFECT_LINGGANDAWANG_BABY		"music/sound038.mp3"
//#define		MUSICCONTROL_EFFECT_LINGGANDAWANG_PET		"music/sound039.mp3"
#define		MUSICCONTROL_EFFECT_YUMIANGONGZHU_CARRIED	"music/sound040.mp3"
//#define		MUSICCONTROL_EFFECT_YUMIANGONGZHU_BABY		"music/sound041.mp3"
//#define		MUSICCONTROL_EFFECT_YUMIANGONGZHU_PET		"music/sound042.mp3"
#define		MUSICCONTROL_EFFECT_NIUMOWANG_CARRIED		"music/sound043.mp3"
//#define		MUSICCONTROL_EFFECT_NIUMOWANG_BABY			"music/sound044.mp3"
//#define		MUSICCONTROL_EFFECT_NIUMOWANG_PET			"music/sound045.mp3"
#define		MUSICCONTROL_EFFECT_XIAOCHOUYU_CARRIED		"music/sound046.mp3"
#define		MUSICCONTROL_EFFECT_BRID_CARRIED			"music/sound047.mp3"
#define		MUSICCONTROL_EFFECT_BAT_CARRIED				"music/sound048.mp3"
#define		MUSICCONTROL_EFFECT_STAR_CARRIED			"music/sound049.mp3"
#define		MUSICCONTROL_EFFECT_PET_GROW				"music/sound050.mp3"
#define		MUSICCONTROL_EFFECT_SHAHESHANG_LINE			"music/sound051.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_1_1				"music/sound052.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_1_2				"music/sound053.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_1_3				"music/sound054.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_1_4				"music/sound055.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_2_1				"music/sound056.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_2_2				"music/sound057.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_3_1				"music/sound058.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_3_2				"music/sound059.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_4_2				"music/sound061.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_4_3				"music/sound062.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_4_4				"music/sound063.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_5_2				"music/sound064.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_5_3				"music/sound065.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_6_1				"music/sound066.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_6_3				"music/sound067.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_6_4				"music/sound060.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_7_1				"music/sound068.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_7_3				"music/sound069.mp3"
//#define		MUSICCONTROL_EFFECT_CARTOON_7_5				"music/sound070.mp3"


USING_NS_CC;
USING_NS_CC_EXT;

MusicControl::MusicControl(bool _isBackGround, bool _isEffect)
{
	isPlatformMusicEnabled = true;
#ifndef				 		GOLDEN_MINER_2_VERSION_PAY
	isPlatformMusicEnabled = PayService::getInstance()->isMusicEnabled();
#endif

	lastBackGround = -2;
	isBackGround = _isBackGround;
	isEffect = _isEffect;
	lastIsBackGround = isBackGround;
	lastIsEffect = isEffect;

	beforeMusicVolume = 1;
	beforeEffectVolume = 1;

	memset(effectId, 0, MUSICCONTROL_EFFECT_ID_COUNT*sizeof(unsigned int));
	//memset(effectId, 0, MUSICCONTROL_EFFECT_ID_COUNT*sizeof(int));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARRY_TARGET);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_GET_TARGET);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BOMB);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BUTTON);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BUY_FINISH);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BUY_FAILED);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_THROW);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_PULL);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_PEAL_OPEN);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_WIN);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_FAILED);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_MONEY_FINISH);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_SKILL);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_PROP);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_ABSORB);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_DROP);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BALL);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_SHOP);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BUY_THING);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BUY_NOTHING);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_TIME_START);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_TIME_OUT);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_TIME_LAST);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_START_ONE);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_START_TWO);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_START_THREE);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_JINGXIGUI_CARRIED);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_JINGXIGUI_BABY);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_JINGXIGUI_PET);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_LINGGANDAWANG_CARRIED);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_LINGGANDAWANG_BABY);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_LINGGANDAWANG_PET);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_YUMIANGONGZHU_CARRIED);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_YUMIANGONGZHU_BABY);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_YUMIANGONGZHU_PET);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_NIUMOWANG_CARRIED);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_NIUMOWANG_BABY);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_NIUMOWANG_PET);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_XIAOCHOUYU_CARRIED);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BRID_CARRIED);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BAT_CARRIED);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_STAR_CARRIED);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_PET_GROW);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_SHAHESHANG_LINE);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_1_1);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_1_2);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_1_3);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_1_4);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_2_1);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_2_2);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_3_1);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_3_2);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_4_2);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_4_3);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_4_4);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_5_2);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_5_3);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_6_1);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_6_3);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_6_4);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_7_1);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_7_3);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_7_5);
}


MusicControl::~MusicControl(void)
{
}

void MusicControl::setBackGround(bool _b)
{
	lastIsBackGround = isBackGround;
	if (isBackGround)
	{
		if (!_b)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		}

		isBackGround = _b;
	}
	else
	{
		isBackGround = _b;

		playGameBackGround(lastBackGround);
	}
}

void MusicControl::setEffect(bool _b)
{
	lastIsEffect = isEffect;
	isEffect = _b;

	if (!isEffect)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	}
}

void MusicControl::playOtherBackGround(void)
{
	if (lastIsBackGround && lastBackGround == -1)
	{
		return;
	}
	lastBackGround = -1;

	//if (!isBackGround)
	//{
	//	return;
	//}

	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSICCONTROL_BACKGROUND_MAIN);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSICCONTROL_BACKGROUND_MAIN,true);
}

void MusicControl::playGameBackGround(int _mapId)
{
	if (lastIsBackGround && lastBackGround == _mapId)
	{
		return;
	}

	lastBackGround = _mapId;

	//if (!isBackGround)
	//{
	//	return;
	//}

	switch(_mapId)
	{
	case BIG_GATE_TYPE_BAOXIANGGUO:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSICCONTROL_BACKGROUND_BAOXIANGGUO);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSICCONTROL_BACKGROUND_BAOXIANGGUO,true);
		break;
	case BIG_GATE_TYPE_TONGYIANHE:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSICCONTROL_BACKGROUND_TONGTIANHE);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSICCONTROL_BACKGROUND_TONGTIANHE,true);
		break;
	case BIG_GATE_TYPE_NVERGUO:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSICCONTROL_BACKGROUND_NVERGUO);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSICCONTROL_BACKGROUND_NVERGUO,true);
		break;
	case BIG_GATE_TYPE_HUOYANSHAN:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSICCONTROL_BACKGROUND_HUOYANSHAN);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSICCONTROL_BACKGROUND_HUOYANSHAN,true);
		break;
	case BIG_GATE_TYPE_LINGSHAN:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSICCONTROL_BACKGROUND_LINGSHAN);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSICCONTROL_BACKGROUND_LINGSHAN,true);
		break;
	default:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSICCONTROL_BACKGROUND_MAIN);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSICCONTROL_BACKGROUND_MAIN,true);
		break;
	}
}

void MusicControl::playEffect(int _effectId)
{
	//if (!isEffect)
	//{
	//	return;
	//}

	switch(_effectId)
	{
	case MUSICCONTROL_EFFECT_ID_CARRY_TARGET:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARRY_TARGET);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARRY_TARGET,false);
		break;
	case MUSICCONTROL_EFFECT_ID_GET_TARGET:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_GET_TARGET);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_GET_TARGET,false);
		break;
	case MUSICCONTROL_EFFECT_ID_BOMB:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BOMB);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_BOMB,false);
		break;
	case MUSICCONTROL_EFFECT_ID_BUTTON:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BUTTON);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_BUTTON,false);
		break;
	case MUSICCONTROL_EFFECT_ID_BUY_FINISH:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BUY_FINISH);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_BUY_FINISH,false);
		break;
	case MUSICCONTROL_EFFECT_ID_BUY_FAILED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BUY_FAILED);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_BUY_FAILED,false);
		break;
	case MUSICCONTROL_EFFECT_ID_THROW:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_THROW);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_THROW,false);
		break;
	case MUSICCONTROL_EFFECT_ID_PULL:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_PULL);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_PULL,true);
		break;
	case MUSICCONTROL_EFFECT_ID_PEAL_OPEN:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_PEAL_OPEN);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_PEAL_OPEN,false);
		break;
	case MUSICCONTROL_EFFECT_ID_WIN:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_WIN);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_WIN,false);
		break;
	case MUSICCONTROL_EFFECT_ID_FAILED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_FAILED);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_FAILED,false);
		break;
	case MUSICCONTROL_EFFECT_ID_MONEY_FINISH:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_MONEY_FINISH);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_MONEY_FINISH,false);
		break;
	case MUSICCONTROL_EFFECT_ID_SKILL:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_SKILL);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_SKILL,false);
		break;
	case MUSICCONTROL_EFFECT_ID_PROP:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_PROP);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_PROP,false);
		break;
	case MUSICCONTROL_EFFECT_ID_ABSORB:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_ABSORB);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_ABSORB,false);
		break;
	case MUSICCONTROL_EFFECT_ID_DROP:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_DROP);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_DROP,false);
		break;
	case MUSICCONTROL_EFFECT_ID_BALL:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BALL);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_BALL,false);
		break;
	case MUSICCONTROL_EFFECT_ID_SHOP:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_SHOP);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_SHOP,false);
		break;
	case MUSICCONTROL_EFFECT_ID_BUY_THING:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BUY_THING);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_BUY_THING,false);
		break;
	case MUSICCONTROL_EFFECT_ID_BUY_NOTHING:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BUY_NOTHING);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_BUY_NOTHING,false);
		break;
	case MUSICCONTROL_EFFECT_ID_TIME_START:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_TIME_START);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_TIME_START,false);
		break;
	case MUSICCONTROL_EFFECT_ID_TIME_OUT:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_TIME_OUT);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_TIME_OUT,false);
		break;
	case MUSICCONTROL_EFFECT_ID_TIME_LAST:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_TIME_LAST);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_TIME_LAST,false);
		break;
	case MUSICCONTROL_EFFECT_ID_START_ONE:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_START_ONE);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_START_ONE,false);
		break;
	case MUSICCONTROL_EFFECT_ID_START_TWO:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_START_TWO);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_START_TWO,false);
		break;
	case MUSICCONTROL_EFFECT_ID_START_THREE:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_START_THREE);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_START_THREE,false);
		break;
	case MUSICCONTROL_EFFECT_ID_JINGXIGUI_CARRIED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_JINGXIGUI_CARRIED);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_JINGXIGUI_CARRIED,false);
		break;
	//case MUSICCONTROL_EFFECT_ID_JINGXIGUI_BABY:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_JINGXIGUI_BABY);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_JINGXIGUI_BABY,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_JINGXIGUI_PET:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_JINGXIGUI_PET);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_JINGXIGUI_PET,false);
	//	break;
	case MUSICCONTROL_EFFECT_ID_LINGGANDAWANG_CARRIED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_LINGGANDAWANG_CARRIED);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_LINGGANDAWANG_CARRIED,false);
		break;
	//case MUSICCONTROL_EFFECT_ID_LINGGANDAWANG_BABY:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_LINGGANDAWANG_BABY);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_LINGGANDAWANG_BABY,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_LINGGANDAWANG_PET:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_LINGGANDAWANG_PET);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_LINGGANDAWANG_PET,false);
	//	break;
	case MUSICCONTROL_EFFECT_ID_YUMIANGONGZHU_CARRIED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_YUMIANGONGZHU_CARRIED);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_YUMIANGONGZHU_CARRIED,false);
		break;
	//case MUSICCONTROL_EFFECT_ID_YUMIANGONGZHU_BABY:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_YUMIANGONGZHU_BABY);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_YUMIANGONGZHU_BABY,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_YUMIANGONGZHU_PET:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_YUMIANGONGZHU_PET);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_YUMIANGONGZHU_PET,false);
	//	break;
	case MUSICCONTROL_EFFECT_ID_NIUMOWANG_CARRIED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_NIUMOWANG_CARRIED);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_NIUMOWANG_CARRIED,false);
		break;
	//case MUSICCONTROL_EFFECT_ID_NIUMOWANG_BABY:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_NIUMOWANG_BABY);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_NIUMOWANG_BABY,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_NIUMOWANG_PET:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_NIUMOWANG_PET);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_NIUMOWANG_PET,false);
	//	break;
	case MUSICCONTROL_EFFECT_ID_XIAOCHOUYU_CARRIED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_XIAOCHOUYU_CARRIED);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_XIAOCHOUYU_CARRIED,false);
		break;
	case MUSICCONTROL_EFFECT_ID_BRID_CARRIED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BRID_CARRIED);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_BRID_CARRIED,false);
		break;
	case MUSICCONTROL_EFFECT_ID_BAT_CARRIED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_BAT_CARRIED);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_BAT_CARRIED,false);
		break;
	case MUSICCONTROL_EFFECT_ID_STAR_CARRIED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_STAR_CARRIED);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_STAR_CARRIED,false);
		break;
	case MUSICCONTROL_EFFECT_ID_PET_GROW:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_PET_GROW);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_PET_GROW,false);
		break;
	case MUSICCONTROL_EFFECT_ID_SHAHESHANG_LINE:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_SHAHESHANG_LINE);
		effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_SHAHESHANG_LINE,false);
		break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_1_1:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_1_1);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_1_1,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_1_2:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_1_2);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_1_1,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_1_3:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_1_3);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_1_3,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_1_4:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_1_4);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_1_4,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_2_1:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_2_1);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_2_1,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_2_2:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_2_2);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_2_2,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_3_1:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_3_1);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_3_1,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_3_2:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_3_2);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_3_2,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_4_2:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_4_2);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_4_2,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_4_3:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_4_3);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_4_3,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_4_4:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_4_4);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_4_4,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_5_2:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_5_2);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_5_2,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_5_3:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_5_3);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_5_3,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_6_1:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_6_1);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_6_1,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_6_3:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_6_3);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_6_3,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_6_4:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_6_4);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_6_4,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_7_1:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_7_1);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_7_1,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_7_3:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_7_3);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_7_3,false);
	//	break;
	//case MUSICCONTROL_EFFECT_ID_CARTOON_7_5:
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(MUSICCONTROL_EFFECT_CARTOON_7_5);
	//	effectId[_effectId] = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSICCONTROL_EFFECT_CARTOON_7_5,false);
	//	break;
	default:
		break;
	}
}

void MusicControl::stopEffect(int _effectId)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(effectId[_effectId]);
	effectId[_effectId] = 0;
}

void MusicControl::stopLoopEffect(void)
{
	CCLOG("music MusicControl stopLoopEffect");
	if (effectId[MUSICCONTROL_EFFECT_ID_PULL] != 0)
	{
		stopEffect(MUSICCONTROL_EFFECT_ID_PULL);
	}
}

void MusicControl::pauseLoopEffect(void)
{
	CCLOG("music MusicControl pauseLoopEffect");
	if (effectId[MUSICCONTROL_EFFECT_ID_PULL] != 0)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(effectId[MUSICCONTROL_EFFECT_ID_PULL]);
	}
	//if (effectId[MUSICCONTROL_EFFECT_ID_PULL] != 0)
	//{
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseEffect(effectId[MUSICCONTROL_EFFECT_ID_PULL]);
	//}
}

void MusicControl::recoverLoopEffect(void)
{
	CCLOG("music MusicControl recoverLoopEffect");
	if (effectId[MUSICCONTROL_EFFECT_ID_PULL] != 0)
	{
		playEffect(MUSICCONTROL_EFFECT_ID_PULL);
	}
	//if (effectId[MUSICCONTROL_EFFECT_ID_PULL] != 0)
	//{
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeEffect(effectId[MUSICCONTROL_EFFECT_ID_PULL]);
	//}
}

void MusicControl::setBackgroundMusicVolume(bool _b)
{
	if (isPlatformMusicEnabled)
	{
		if (_b)
		{
			CCLOG("music MusicControl setBackgroundMusicVolume  isPlatformMusicEnabled = true _b = true");
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(beforeMusicVolume);
		}
		else
		{
			CCLOG("music MusicControl setBackgroundMusicVolume  isPlatformMusicEnabled = true _b = false");
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0);
		}
	}
	else
	{
		CCLOG("music MusicControl setBackgroundMusicVolume  isPlatformMusicEnabled = false");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0);
	}
}

void MusicControl::setEffectsVolume(bool _b)
{
	if (isPlatformMusicEnabled)
	{
		if (_b)
		{
			CCLOG("music MusicControl setEffectsVolume  isPlatformMusicEnabled = true _b = true");
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(beforeEffectVolume);
		}
		else
		{
			CCLOG("music MusicControl setEffectsVolume  isPlatformMusicEnabled = true _b = false");
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0);
		}
	}
	else
	{
		CCLOG("music MusicControl setEffectsVolume  isPlatformMusicEnabled = false");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0);
	}
}

void MusicControl::recoverBackgroundMusic(void)
{
	CCLOG("music MusicControl recoverBackgroundMusic");
	setBackGround(lastIsBackGround);
}

void MusicControl::recoverEffects(void)
{
	CCLOG("music MusicControl recoverEffects");
	setEffect(lastIsEffect);
}

void MusicControl::resumeVoice(void)
{
	CCLOG("music   MusicControl resumeVoice");
	if (isCanResume)
	{
		CCLOG("music true");
		setEffectsVolume(isEffect);
		setBackgroundMusicVolume(isBackGround);
		//playGameBackGround(lastBackGround);
	}
}

void MusicControl::setIsCanResume(bool _b)
{
	if (_b)
	{
		CCLOG("music   MusicControl setIsCanResume _b = true");
	}
	else
	{
		CCLOG("music   MusicControl setIsCanResume _b = fasle");
	}
	isCanResume = _b;
}