#include "string.h"
int strlen(const char* str){
	int count=0;
	while(*str++){
		++count;
	}
	return count;
}
int strcmp(const char* s1,const char* s2){
	int i=0;
	for(;s1[i]==s2[i]&&s1[i]!=0;++i);
	return s1[i]-s2[i];
}
int strncmp (const char* s1,const char* s2,size_t n){
	size_t i=0;
	for(;i<n && s1[i]==s2[i] && s1[i]!=0 ; ++i);
	return i==n ? 0 : s1[i]-s2[i];
}