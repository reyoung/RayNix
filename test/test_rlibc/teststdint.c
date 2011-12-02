#include "stdint.h"


#define CheckTypeFail(_type,_sign,_size)\
	(sizeof(_type)!=(_size/8)||(_sign?(_type)(-1)>0:(_type)(-1)<0))

int main(){
	if(CheckTypeFail(int8_t,1,8)){
		return 1;
	}
	if(CheckTypeFail(uint8_t,0,8)){
		return 2;
	}
	if(CheckTypeFail(int16_t,1,16)){
		return 3;
	}
	if(CheckTypeFail(uint16_t,0,16)){
		return 4;
	}
	if(CheckTypeFail(int32_t,1,32)){
		return 5;
	}
	if(CheckTypeFail(uint32_t,0,32)){
		return 6;
	}
	if(CheckTypeFail(int64_t,1,64)){
		return 7;
	}
	if(CheckTypeFail(uint64_t,0,64)){
		return 8;
	}

	return 0;
}