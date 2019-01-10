#include "stdafx.h"
#include "Math.h"

const float Math::PI = 3.14159265459f;
const float Math::PI_2 = 6.28318530718f;
const float Math::PI_DIV_2 =1.57079632679f;
const float Math::PI_DIV_4 = 0.78539816339f;
const float Math::TO_DEG = 180.f / PI;
const float Math::TO_RAD =  PI / 180.0f;

const float Math::Random(const float & min, const float & max)
{
	//return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (max - min)); 

	float random = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
	float diff = max - min;
	float val = random * diff;
	
	return min + val;
	//1107숙제 이거 만들고 CLAMP찾아보고 구현 abs,random           ceil,floor,round<-정리
}

const int Math::Random(const int & min, const int & max)
{
	return rand() % (max - min + 1) + min; //민부터 맥스사이의 랜덤값리턴

}




