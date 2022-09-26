/*
 * display.c
 *
 *  Created on: 15 sept. 2022
 *      Author: marco
 */
//################################################################################################### archivo display.c
#include "display.h"



extern volatile struct digit digits_struct[DIGITOS]; // BUFFER
extern int aux;

void display( float val )// val es la lectura de la IMU
{
	  digits_struct[0].number = (int)(val*10) % 10;
	  digits_struct[1].number = (int)(val) % 10;
	  digits_struct[2].number = (int)(val/10) % 10;
	  digits_struct[3].number = (int)(val / 100) % 10;
	  digits_struct[1].point = TRUE;
	  digits_struct[0].point = FALSE;
	  digits_struct[2].point = FALSE;
	  digits_struct[3].point = FALSE;
}


void set_led(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
}

void barrido_display( void ) //llamarla en el handler del timer
{
	uint8_t codigo;
	static uint8_t parte = 0, digito = 0;
	// pongo cada digito alto, para que se apague todo
	set_led( digito_0, HIGH );
	set_led( digito_1, HIGH );
	set_led( digito_2, HIGH );
	set_led( digito_3, HIGH );

	switch (digits_struct[digito].number)
	{
	case 0:
		if( digito != 1 )
			codigo = CODIGO_0;
		else
			codigo = CODIGO_0p;
		break;
	case 1:
		if( digito != 1 )
			codigo = CODIGO_1;
		else
			codigo = CODIGO_1p;
		break;
	case 2:
		if( digito != 1 )
			codigo = CODIGO_2;
		else
			codigo = CODIGO_2p;
		break;
	case 3:
		if( digito != 1 )
			codigo = CODIGO_3;
		else
			codigo = CODIGO_3p;
		break;
	case 4:
		if( digito != 1 )
			codigo = CODIGO_4;
		else
			codigo = CODIGO_4p;
		break;
	case 5:
		if( digito != 1 )
			codigo = CODIGO_5;
		else
			codigo = CODIGO_5p;
		break;
	case 6:
		if( digito != 1 )
			codigo = CODIGO_6;
		else
			codigo = CODIGO_6p;
		break;
	case 7:
		if( digito != 1 )
			codigo = CODIGO_7;
		else
			codigo = CODIGO_7p;
		break;
	case 8:
		if( digito != 1 )
			codigo = CODIGO_8;
		else
			codigo = CODIGO_8p;
		break;
	case 9:
		if( digito != 1 )
			codigo = CODIGO_9;
		else
			codigo = CODIGO_9p;
		break;
	default:
		break;
	}

	switch ( parte )
	{
	case LOW:
		set_led( segmento_e, LOW );
		set_led( segmento_f, LOW );
		set_led( segmento_g, LOW );
		set_led( segmento_dp, LOW );
		set_led( segmento_a, ((codigo >> 0) & (uint8_t)0x01) );
		set_led( segmento_b, ((codigo >> 1) & (uint8_t)0x01) );
		set_led( segmento_c, ((codigo >> 2) & (uint8_t)0x01) );
		set_led( segmento_d, ((codigo >> 3) & (uint8_t)0x01) );
		break;
	case HIGH:
		set_led( segmento_a, LOW );
		set_led( segmento_b, LOW );
		set_led( segmento_c, LOW );
		set_led( segmento_d, LOW );
		set_led( segmento_e, ((codigo >> 4) & (uint8_t)0x01) );
		set_led( segmento_f, ((codigo >> 5) & (uint8_t)0x01) );
		set_led( segmento_g, ((codigo >> 6) & (uint8_t)0x01) );
		set_led( segmento_dp, ((codigo >> 7) & (uint8_t)0x01) );
		break;
	default:
		break;
	}

	switch ( digito )
	{
	case DIGITO_0:
		set_led(digito_0, LOW);
		break;
	case DIGITO_1:
		set_led(digito_1, LOW);
		break;
	case DIGITO_2:
		set_led(digito_2, LOW);
		break;
	case DIGITO_3:
		set_led(digito_3, LOW);
		break;
	}

	// Incremento el indice del display
    parte++;
    parte %= 2;
    if( !parte )
    {
		digito++;
		digito %= DIGITOS;
    }
}
