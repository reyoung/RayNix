#include "ctype.h"

extern void exit(int);
int main(){
	if((!isupper('A'))||isupper('a')){
		exit(1);
	}
	if(islower('A')||(!islower('a'))){
		exit(2);
	}
	if(isalpha('1')||(!isalpha('m'))){
		exit(3);
	}
	if(isdigit('a')||(!isdigit('2'))){
		exit(4);
	}
	if(isalnum('\t')||(!isalnum('2'))){
		exit(5);
	}
	return 0;
}