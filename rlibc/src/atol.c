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
void itoa(int value,char* buffer,int radix){
	//! TODO Radix Used.
	int count=0;
	char temp[11];
	if(value<0){
		*buffer++ = '-';
		value = -value;
	}
	do {
		temp[count++]=value%10;
		value/=10;
	} while(value);
	for(--count;count>=0;--count){
		*buffer++=temp[count]+'0';
	}
	*buffer=0;
}