#include "string.h"
int strlen(const char* str){
	int count=0;
	while(*str++){
		++count;
	}
	return count;
}