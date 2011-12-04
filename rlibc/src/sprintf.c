#include "sprintf.h"

int sprintf(char* str, const char* fmt , ...){
	va_list args;
	int res;
	va_start(args,fmt);
	res = vsprintf(str,fmt,args);
	va_end(args);
	return res;
}

int vsprintf(char* str,const char* fmt,va_list args){
	char ch;
	char* start = str;
	
	while((ch=*fmt++)!=0){
		if(ch!='%'){
			*str++=ch;
		} else {
			// TODO Complete Special Chars.
		}
	}
	*str=0;
	return (int)(str-start);
}


