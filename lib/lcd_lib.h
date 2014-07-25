/*
 * lcd_lib.h
 *
 * Created: 9/5/2012 10:45:43 AM
 *  Author: EX4
 */ 


#ifndef LCD_LIB_H_
#define LCD_LIB_H_

//used lib
#include <inttypes.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>

//lcd port and pin
//lcd d4-d7 is on bit 4-7
#define LCD_PORT	PORTB
#define LCD_DDR		DDRB
#define LCD_PIN		PINB
#define LCD_RS		0
#define LCD_RW		1
#define LCD_EN		2

//delay const
#define LCD_EN_DELAY		1	//delay for enable in us
#define LCD_CMD_DELAY		2	//delay cmd dlm ms, ADJUST WITH YOUR OWN LCD!!!

//use busy flag or not
//if not using busy flag then tied RW pin to GND
#define USE_BUSY_FLAG		1	//set to 0 for not using busy flag

//lcd command list
#define LCD_CLR             0	//DB0: clear display
#define LCD_HOME            1	//DB1: return to home position
#define LCD_ENTRY_MODE      2	//DB2: set entry mode
#define LCD_ENTRY_INC       1	//DB1: increment
#define LCD_ENTRY_SHIFT     0	//DB2: shift
#define LCD_ON_CTRL         3	//DB3: turn lcd/cursor on
#define LCD_ON_DISPLAY      2	//DB2: turn display on
#define LCD_ON_CURSOR       1	//DB1: turn cursor on
#define LCD_ON_BLINK        0	//DB0: blinking cursor
#define LCD_MOVE            4	//DB4: move cursor/display
#define LCD_MOVE_DISP       3	//DB3: move display (0-> move cursor)
#define LCD_MOVE_RIGHT      2	//DB2: move right (0-> left)
#define LCD_FUNCTION        5	//DB5: function set
#define LCD_FUNCTION_8BIT   4	//DB4: set 8BIT mode (0->4BIT mode)
#define LCD_FUNCTION_2LINES 3	//DB3: two lines (0->one line)
#define LCD_FUNCTION_10DOTS 2	//DB2: 5x10 font (0->5x7 font)
#define LCD_CGRAM           6	//DB6: set CG RAM address
#define LCD_DDRAM           7	//DB7: set DD RAM address

// reading:
#define LCD_BUSY            7	//DB7: LCD is busy
#define LCD_LINES			2	//visible lines
#define LCD_LINE_LENGTH		16	//line length (in characters)

// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54

// progress bar defines
#define PROGRESSPIXELS_PER_CHAR	6

//lcd as file stream. use it with fprintf or any other io stream
//#define LCDasOutputStream FDEV_SETUP_STREAM(LCDsendCharStream,NULL,_FDEV_SETUP_WRITE)
extern FILE LCDInputOutputStream;

//proto
////toggle enable pin
//static void LCDtoggleEn();
////wait until bf=0
//static void LCDwaitUntilNotBusy();
//init lcd pin setting
void LCDinit();
//go to a lcd position cursor
void LCDGotoXY(uint8_t x, uint8_t y);
//send command to lcd
void LCDsendCommand(uint8_t aCmd);
//send char to lcd
void LCDsendChar(uint8_t aData);
//stream io lcd
int LCDsendCharStream(char ch, FILE *stream);
//show string
void LCDstring(uint8_t* aStr,uint8_t Len);
//clear screen
void LCDclr();
//back to home cursor
void LCDhome();
//copy pgm string to lcd
void CopyStringtoLCD(const uint8_t*, uint8_t, uint8_t);//copies flash string to LCD at x,y
//define custom char
void LCDdefinechar(const uint8_t *,uint8_t);//write char to LCD CGRAM
//define progress bar char as char0-5
void LCDDefineProgressBarChar();
//shift display right
void LCDshiftRight(uint8_t);	//shift by n characters Right
//shift display left
void LCDshiftLeft(uint8_t);	//shift by n characters Left
//cursor on
void LCDcursorOn();		//Underline cursor ON
//cursor on blink
void LCDcursorOnBlink();	//Underline blinking cursor ON
//cursor off
void LCDcursorOFF();		//Cursor OFF
void LCDblank();			//LCD blank but not cleared
void LCDvisible();			//LCD visible
void LCDcursorLeft(uint8_t);	//Shift cursor left by n
void LCDcursorRight(uint8_t);	//shif cursor right by n
// displays a horizontal progress bar at the current cursor location
// <progress> is the value the bargraph should indicate
// <maxprogress> is the value at the end of the bargraph
// <length> is the number of LCD characters that the bargraph should cover
//adapted from AVRLIB - displays progress only for 8 bit variables
void LCDprogressBar(uint8_t progress, uint8_t maxprogress, uint8_t length);

#endif /* LCD_LIB_H_ */