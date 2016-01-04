#ifndef											__GM_JSON_H__
#define											__GM_JSON_H__

#include "cocos2d.h"

class GMJson
{
public:
	GMJson(void);
	~GMJson(void);

	void getSelfInformation(std::string _response);
	void getChallengeDate(std::string _response);

};


#endif
