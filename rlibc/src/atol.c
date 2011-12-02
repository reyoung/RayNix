#include "ctype.h"
#include "atol.h"
#include "stddef.h"
int atoi(const char* str){
	size_t i=0;
	int retv = 0;
	for(;str[i]!=0;++i){
		if(isdigit(str[i])){
			retv*=10;
			retv+=str[i]-'0';
		} else {
			return 0;
		}
	}
	return retv;
}
long atol(const char* str){
	size_t i=0;
	long retv = 0;
	for(;str[i]!=0;++i){
		if(isdigit(str[i])){
			retv*=10;
			retv+=str[i]-'0';
		} else {
			return 0;
		}
	}
	return retv;
}