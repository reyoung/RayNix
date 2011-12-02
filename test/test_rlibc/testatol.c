#include "atol.h"
int main(){
	if(atoi("123")!=123||atoi("a")!=0){
		return 1;
	}
	if(atol("12345678")!=12345678 || atol("b")!=0){
		return 2;
	}
	return 0;
}