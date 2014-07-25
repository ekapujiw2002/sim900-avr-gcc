/*
* sim900_lib_tes.c
*
* Created: 7/25/2014 11:57:32 AM
*  Author: EX4
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "lib/sim900.h"
#include "lib/lcd_lib.h"

int main(void)
{
	//var
	uint8_t answer;
	uint8_t http_respon_data[64];

	//init pa sbg in
	DDRA = 0;
	PORTA = 0xff;

	//init lcd
	LCDinit();

	LCDclr();
	LCDcursorOFF();
	LCDhome();
	
	//init uart
	sim900_init_uart(38400);
	
	//enable isr
	sei();

	LCDGotoXY(0, 0);
	fprintf(&LCDInputOutputStream, "setup modem = %d", sim900_setup(SETUP_WAIT_INFINITE));
	_delay_ms(1000);
	
	while(1)
	{
		//krm sms pa0
		if (bit_is_clear(PINA, PA0))
		{
			_delay_ms(100);
			loop_until_bit_is_set(PINA, PA0);
			
			LCDclr();
			LCDhome();
			fprintf(&LCDInputOutputStream, "open gprs = %d", sim900_gprs_open_connection(
			(const uint8_t*)"internet", (const uint8_t*)" ", (const uint8_t*)" "));
		}
		
		//open gprs
		if (bit_is_clear(PINA, PA1))
		{
			_delay_ms(100);
			loop_until_bit_is_set(PINA, PA1);

			//answer = sim900_gprs_open_bearer((const uint8_t*)"internet", (const uint8_t*)" ", (const uint8_t*)" ");
			//answer = sim900_gprs_open_bearer("internet", " ", " ");
			//answer = sim900_gprs_is_opened();
			//answer = sim900_gprs_closed();
			//answer = sim900_http_get((const uint8_t*)
			//"http://ex4-tech.id.or.id/sim900/data.php", (const uint8_t*)"c=1", 64,
			//http_respon_data);
			answer = sim900_http_send_data(
			HTTP_POST,
			(const uint8_t*)"http://ex4-tech.id.or.id/sim900/data.php",
			(const uint8_t*)"c=1",
			64,
			http_respon_data);
			LCDclr();
			LCDhome();
			fprintf(&LCDInputOutputStream, "post = %d", answer);
			LCDGotoXY(0, 1);
			fprintf(&LCDInputOutputStream, "%s", http_respon_data);
			_delay_ms(5000);
		}


		if (bit_is_clear(PINA, PA2))
		{
			_delay_ms(100);
			loop_until_bit_is_set(PINA, PA2);

			answer = sim900_gprs_close_connection();
			LCDclr();
			LCDhome();
			fprintf(&LCDInputOutputStream, "close gprs = %d", answer);
		}
	}
}
