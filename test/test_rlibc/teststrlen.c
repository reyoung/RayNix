#include "string.h"
extern void exit(int);
int main(){
	char* str_test="123";
	if(strlen(str_test)!=3){
		exit(1);
	}
	return 0;
}