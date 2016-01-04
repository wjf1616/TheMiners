#include "PayService.h"
#include "Player.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#endif
//#include "AccessData.h"

CCCallFunc* PayService::successFc;
CCCallFunc* PayService::failFc;
CCCallFunc* PayService::onConfirmExitFc;

PayService* PayService::instance = NULL;

PayService* PayService::getInstance() {
	if (instance == NULL) {
		instance = new PayService();
	}
	return instance;
}

void PayService::exitGame(CCCallFunc* onConfirmExit)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
	onConfirmExit->retain();

	PayService::onConfirmExitFc = onConfirmExit;

	JniMethodInfo minfo;//����Jni������Ϣ�ṹ��

	//getStaticMethodInfo �κ�������һ��boolֵ��ʾ�Ƿ��ҵ��˺���
	//bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/gamedo/GoldenMiner2/review/PayService","exitGame", "()V");

	//if (!isHave) {
	//	CCLog("jni:�˺���������");
	//}else{
	//	CCLog("jni:�˺�������");

	//	//���ô˺���
	//	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	//}
#endif
}

bool PayService::isMusicEnabled(void)
{

#ifndef				 		GOLDEN_MINER_2_VERSION_PAY
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ��

	//getStaticMethodInfo �κ�������һ��boolֵ��ʾ�Ƿ��ҵ��˺���
	//bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/gamedo/GoldenMiner2/review/PayService","isMusicEnabled", "()Z");

	//if (!isHave) {
	//	CCLog("jni:�˺���������");
	//	return true;
	//}else{
	//	CCLog("jni:�˺�������");

	//	//���ô˺���
	//	return minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID);
	//}
#endif
#endif
	return true;
}

void PayService::getMoreGames(void)
{

#ifndef				 		GOLDEN_MINER_2_VERSION_PAY
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ��

	//getStaticMethodInfo �κ�������һ��boolֵ��ʾ�Ƿ��ҵ��˺���
	//bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/gamedo/GoldenMiner2/review/PayService","getMoreGames", "()Z");

	//if (!isHave) {
	//	CCLog("jni:�˺���������");
	//}else{
	//	CCLog("jni:�˺�������");

	//	//���ô˺���
	//	minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID);
	//}
#endif
#endif
}

static void setResumeSoundFc(CCCallFunc * _resumeSoundFc)
{

}

void PayService::setCheckTrue(void)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ��

	//getStaticMethodInfo �κ�������һ��boolֵ��ʾ�Ƿ��ҵ��˺���
	//bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/gamedo/GoldenMiner2/review/PayService","setCheckTrue", "()V");

	//if (!isHave) {
	//	CCLog("jni:�˺���������");
	//}else{
	//	CCLog("jni:�˺�������");

	//	//���ô˺���
	//	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	//}
#endif
}

void PayService::pay(int id, bool isRepeated, CCCallFunc* successFc,CCCallFunc* failFc)
{
	assert(successFc);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
	successFc->retain();

	if(failFc !=NULL){
		failFc->retain();
	}
	PayService::successFc = successFc;
	PayService::failFc = failFc;

	JniMethodInfo minfo;//����Jni������Ϣ�ṹ��

	//getStaticMethodInfo �κ�������һ��boolֵ��ʾ�Ƿ��ҵ��˺���
	//bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/gamedo/GoldenMiner2/review/PayService","pay", "(IZ)V");

	//if (!isHave) {
	//	CCLog("jni:�˺���������");
	//}else{
	//	CCLog("jni:�˺�������");

	//	//���ô˺���
	//	jint arg1 = id;
	//	jboolean arg2 = isRepeated;

	//	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,arg1, arg2);
	//}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	successFc->execute();
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
extern "C"
{
	//void Java_com_gamedo_GoldenMiner2_review_PayService_sendSuccess(JNIEnv* env, jobject firedragonpzy)
	//{


	//	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(PayService::callSuccessFc), PayService::getInstance(), 0 ,0, 0, false);


	//	//CCDirector::sharedDirector()->end();
	//}

	//void Java_com_gamedo_GoldenMiner2_review_PayService_sendFail(JNIEnv* env, jobject firedragonpzy)
	//{

	//	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(PayService::callfailFc), PayService::getInstance(), 0 ,0, 0, false);


	//	//CCDirector::sharedDirector()->end();
	//}

	//void Java_com_gamedo_GoldenMiner2_review_PayService_resumeSound(JNIEnv* env, jobject firedragonpzy)
	//{
	//	Player::getInstance()->getMusicControl()->setIsCanResume(true);
	//	Player::getInstance()->getMusicControl()->resumeVoice();
	//}

	//void Java_com_gamedo_GoldenMiner2_review_PayService_onConfirmExit(JNIEnv* env, jobject firedragonpzy)
	//{
	//	CCDirector::sharedDirector()->end();
	//	//exit(0);
	//}
	//
	////����һ���ṹ���飬����һ��Ӳ����Ϣ�Ľṹ����
	//void Java_com_gamedo_GoldenMiner2_review_PayService_setIMEI(JNIEnv *env, jobject _obj, jcharArray  jstr)
	//{ 
	//	//int length = (env)->GetStringLength(jstr );
	//	//const jchar* jcstr = (env)->GetStringChars(jstr, 0 );
	//	//char* rtn = (char*)malloc(length*2+1);
	//	//int size = 0;
	//	//size = WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)jcstr, length, rtn,(length*2+1), NULL, NULL );
	//	//if( size <= 0 )
	//	//	return NULL;
	//	//(env)->ReleaseStringChars(jstr, jcstr );
	//	//rtn[size] = 0;
	//	jchar* pba = (env)->GetCharArrayElements(jstr, 0 );
	//	int len = (env)->GetArrayLength(jstr);
	//	char _buff[IMEI_LENGTH];
	//	for(int i=0;i<len;i++)
	//	{
	//		_buff[i] = *(pba+i);
	//	}
	//	CCLog("IMEI      %s", _buff);
	//	(env)->ReleaseCharArrayElements(jstr, pba, 0 );
	//	Player::getInstance()->setImeiStr(_buff, len);
	//}
}
#endif


void PayService::callSuccessFc(){
	PayService::successFc->execute();
	PayService::successFc->release();
	PayService::successFc = NULL;
	if(PayService::failFc!=NULL){
		PayService::failFc->release();
		PayService::failFc = NULL;
	}

}

void PayService::callfailFc(){
	PayService::failFc->execute();
	PayService::failFc->release();
	PayService::failFc = NULL;
	PayService::successFc->release();
	PayService::successFc = NULL;
}

void PayService::callOnConfirmExitFc(){
	PayService::onConfirmExitFc->execute();
	PayService::onConfirmExitFc->release();
	PayService::onConfirmExitFc = NULL;
}