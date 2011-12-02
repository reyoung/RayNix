#include "atol.h"
static char BUFFER[512];

int CheckWithBuffer(const char * str){
	int i=0;
	for(;str[i]!=0;++i){
		if(BUFFER[i]!=str[i]){
			return 0;
		}
	}
	if(BUFFER[i]!=0){
		return 0;
	} else {
		return -1;
	}
}

int main(){
	if(atoi("123")!=123||atoi("a")!=0){
		return 1;
	}
	if(atol("12345678")!=12345678 || atol("b")!=0){
		return 2;
	}
	{
		itoa(12,BUFFER,10);
		if(!CheckWithBuffer("12")){
			return 3;
		}
	}
	return 0;
}