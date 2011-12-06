#include "console.h"
#include "string.h"
#include "io.h"
#include "sprintf.h"
#define LINE_COUNT 25
#define COLUMN_COUNT 80
#define BUFFER_MAX 256

static char * VideoRam = 0x000b8000+0xc0000000;
static uint8_t X;
static uint8_t Y;
static char Color;


boolean Console_Init(){
	Color=0x07;
	Console_Clear();
	return True;
}
boolean Console_GotoXY(int x, int y){
	uint16_t position = (y*80)+x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position&0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char )((position>>8)&0xFF));
	
	return True;
}
boolean Console_IsVideoMono(){
	char c=(*(volatile uint16_t*)0x410)&0x30;
	return (c==0x30);
}
boolean Console_PutCharWithColor(char ch, char color){
	volatile uint16_t* where;
	if(ch=='\n'){
		++Y;
		if(Y>=LINE_COUNT){
			Console_ScorllPage();
		}
	} else if(ch=='\r'){
		X=0;
	} else if(ch=='\t'){
	       Console_PutCharWithColor(' ',color);
	       Console_PutCharWithColor(' ',color);
	       Console_PutCharWithColor(' ',color);
	       Console_PutCharWithColor(' ',color);
	} else {
		if(Console_IsVideoMono()) {
			VideoRam[Y*80+X]=ch;
		} else {
			where=(uint16_t*)(VideoRam)+(Y*80+X);
			*where=ch| (((uint16_t)color)<<8);
		}
		++X;
		if(X >= COLUMN_COUNT){
			X=0;
			++Y;
			if(Y>=LINE_COUNT) {
				Console_ScorllPage();
			}
		}
	}
	Console_GotoXY(X,Y);
	return True;
}
boolean Console_SetDefaultColor(char color){
	Color=color;
	return True;
}
boolean Console_PutChar(char ch){
	return Console_PutCharWithColor(ch,Color);
}

boolean Console_PutString(const char* str){
	boolean retv=True;
	while(*str!=0){
		if(!Console_PutChar(*str++))
			retv=False;
	}
	return retv;
}

void Console_Clear(){
	int i=0;
	X=0;
	Y=0;
	if(Console_IsVideoMono()){
		for(i=0;i<LINE_COUNT* COLUMN_COUNT;++i){
			VideoRam[i]=' ';
		}
	} else {
		for(i=0;i<LINE_COUNT* COLUMN_COUNT;++i){
			VideoRam[i*2]=' ';
			VideoRam[i*2+1] = Color;
		}
	}
	Console_GotoXY(X,Y);
}
void Console_ScorllPage(){
	int i=0;
	uint16_t* where;
	--Y;
	if(Console_IsVideoMono()){
		memmove(VideoRam,VideoRam+COLUMN_COUNT,LINE_COUNT* COLUMN_COUNT);
	}else {
		memmove(VideoRam,VideoRam+COLUMN_COUNT*2,LINE_COUNT * COLUMN_COUNT *2 );
		for(i=0;i< COLUMN_COUNT; ++i){
			where=(uint16_t*)(VideoRam)+((LINE_COUNT-1) *80+i);
			*where=' '| (((uint16_t)Color)<<8);
		}
	}
}

int Console_Printf(const char* fmt,...){
	char buffer[BUFFER_MAX];
	va_list args;
	int res;
	va_start(args,fmt);
	res = vsprintf(buffer,fmt,args);
	va_end(args);
	Console_PutString(buffer);
	return res;
}

