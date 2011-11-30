#include "string.h"
int strlen(const char* str){
	register int count=0;
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

char *strcpy (char *dest, const char *src){
	char* retv = dest;
	while(*dest++=*src++);
	return retv;
}
char *strncpy (char* dest, const char* src, size_t n){
	char* retv = dest;
	size_t count =0;
	while( count++!=n && (*dest++=*src++));
	--count;
	for(;count<n;++count)
		dest[count]=0;
	return retv;
}
void *memcpy (void *dest, const void *src, size_t n){
	size_t i=0;
	char* d = dest;
	const char* s = src;
	for(;i<n;++i){
		d[i]=s[i];
	}
	return dest;
}
void *memmove (void *dest, const void *src, size_t n){
	int i;
	char* d = dest;
	const char* s = src;
	if(dest > src ){
		for(i = n-1;i>=0;--i){
			d[i]=s[i];
		}
	} else {
		for(i = 0;i<(int)n;++i){
			d[i]=s[i];
		}
	}
	return dest;
}