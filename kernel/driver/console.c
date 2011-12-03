#include "console.h"
#include "io.h"
#define LINE_COUNT 25
#define COLUMN_COUNT 80
static char * VideoRam = 0x000b8000;
static uint8_t X;
static uint8_t Y;
static char Color;


boolean Console_Init(){
	int i=0;
	X=0;
	Y=0;
	Color=0x07;
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
	// TODO Check Special Chars.

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
			// TODO Scroll Page.
		}
	}
	Console_GotoXY(X,Y);
	return True;
}

