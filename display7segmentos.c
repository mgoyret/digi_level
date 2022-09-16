/*
La aplicación llama a la primitiva Display(val). Esta primitiva divide al valor en digitos y los
guarda en un buffer global. Luego el driver BarridoDisplay() (invocado en el systick_handler)
consume ese buffer para imprimir cada digito.
Display(val) -> toma el valor, y se fija el valor de cada digito (obteniendo restos y dividiendo). El valor
de un digito equivale a la posicion del array BCD, cuyo valor va en el mensajeAimprimir[indice del digito]
Luego el driver barridoDisplay() desactiva los dígitos del display, activa uno solo, toma el valor que esta
en mensajeAimprimir[digito] y lleva a cada segmento el bit correspondiente
*/

// #include "Regs_LPC176x.h"
// #include "drivers.h"

// EJEMPLO DISPLAY 8seg y 4dig
#define DIGITOS 4 //cantidad de digitos del display

#define PIN_DISPLAY0    0,0
#define PIN_DISPLAY1    0,1
#define PIN_DISPLAY2    0,2
#define PIN_DISPLAY3    0,3
#define PIN_DISPLAY4    0,4
#define PIN_DISPLAY5    0,5
#define PIN_DISPLAY6    0,6
#define PIN_DISPLAY7    0,7
#define PIN_DISPLAY8    0,8
#define PIN_DISPLAY9    0,9
#define PIN_DISPLAY10   0,10
#define PIN_DISPLAY11   0,11

#define	digito0			PIN_DISPLAY0	//PORT2,7		//!< Display 7 Segmentos
#define	digito1			PIN_DISPLAY1	//PORT1,29
#define	digito2			PIN_DISPLAY2	//PORT4,28
#define	digito3			PIN_DISPLAY3	//PORT1,23

#define	segmento_a		PIN_DISPLAY4	//PORT3,26
#define	segmento_b		PIN_DISPLAY5	//PORT1,18
#define	segmento_c		PIN_DISPLAY6	//PORT1,21
#define	segmento_d		PIN_DISPLAY7	//PORT1,24
#define	segmento_e		PIN_DISPLAY8	//PORT1,27
#define	segmento_f		PIN_DISPLAY9	//PORT3,25
#define	segmento_g		PIN_DISPLAY10	//PORT0,20
#define	segmento_dp		PIN_DISPLAY11	//PORT1,19

#define	DIGITO_0			0				//!< Numero de Digito
#define	DIGITO_1			1
#define	DIGITO_2			2
#define	DIGITO_3			3

#define CODIGO_0	0x3f	//011 1111 = gfedcba
#define CODIGO_1	0x06	//000 0110 
#define CODIGO_2	0x5B	//101 1011
#define CODIGO_3	0x4f	//100 1111
#define CODIGO_4	0x66	//110 0110
#define CODIGO_5	0x6D	//110 1101
#define CODIGO_6	0x7C	//111 1011
#define CODIGO_7	0x07	//000 0111
#define CODIGO_8	0x7f	//111 1111
#define CODIGO_9	0x67	//110 0111

//################################################################################################### carpeta primitivas


extern volatile uint8_t msgDisplay[DIGITOS]; //BUFFER

////////////////////////////////////// primitivas display .c
//uint8_t Tabla_Digitos_BCD_7seg[] = { 0x3f, 0x06, 0x5B, 0x4f, 0x66, 0x6D, 0x7C, 0x07, 0x7f, 0x67};
uint8_t Tabla_Digitos_BCD_7seg[] = { CODIGO_0, CODIGO_1, CODIGO_2, CODIGO_3, CODIGO_4, CODIGO_5, CODIGO_6, CODIGO_7, CODIGO_8, CODIGO_9 };

void display(uint16_t Val)
{
	uint8_t i ;

	//en cada posicion del array, pongo el valor con el codigo binario del digito a mostrar
	for(i = 0 ; i<DIGITOS ; i++ )
	{
		msgDisplay[DIGITOS -1 -i] = Tabla_Digitos_BCD_7seg[Val%10];
		Val /= 10; // Val debe ser entre 0 y 9!!
	}
}



//################################################################################################### carpeta drivers

//////////////////////////////////////////////////////////////// initDisplay.c
void initDisp7Seg( void );
void initDisp7Seg( void ) 
{
    setPinsel(PIN_DISPLAY0, PINSEL_GPIO);
    setPinsel(PIN_DISPLAY1, PINSEL_GPIO);
    setPinsel(PIN_DISPLAY2, PINSEL_GPIO);
    setPinsel(PIN_DISPLAY3, PINSEL_GPIO);
    setPinsel(PIN_DISPLAY4, PINSEL_GPIO);
    setPinsel(PIN_DISPLAY5, PINSEL_GPIO);
    setPinsel(PIN_DISPLAY6, PINSEL_GPIO);
    setPinsel(PIN_DISPLAY7, PINSEL_GPIO);
    setPinsel(PIN_DISPLAY8, PINSEL_GPIO);
    setPinsel(PIN_DISPLAY9, PINSEL_GPIO);
    setPinsel(PIN_DISPLAY10, PINSEL_GPIO);
    setPinsel(PIN_DISPLAY11, PINSEL_GPIO);

    setDir(PIN_DISPLAY1, OUT);
    setDir(PIN_DISPLAY2, OUT);
    setDir(PIN_DISPLAY3, OUT);
    setDir(PIN_DISPLAY4, OUT);
    setDir(PIN_DISPLAY5, OUT);
    setDir(PIN_DISPLAY6, OUT);
    setDir(PIN_DISPLAY7, OUT);
    setDir(PIN_DISPLAY8, OUT);
    setDir(PIN_DISPLAY9, OUT);
    setDir(PIN_DISPLAY10, OUT);
    setDir(PIN_DISPLAY11, OUT);
}

/////////////////////////////////////////////////////////// drivers display

//en el systyck:

#define TIME_SCAN	10 //TIME_SCAN = 100 / (CANT_DIGIT * FREC_SYSTICK) si 4digitos y systick cada 2,5 => este resultado
void systick_Handler( void )
{
	uint8_t dummy = STCTRL;
	static uint8_t ctr = TIME_SCAN;
	if(ctr>0)
		ctr--;
	else
	{
		barridoDisplay();
		ctr=TIME_SCAN;
	}
}

void barridoDisplay( void );
void barridoDisplay( void )
{
	uint8_t aux, codigo;
	static uint8_t	digito = 0;

	setPin(digito0,OFF);
	setPin(digito1,OFF);
	setPin(digito2,OFF);
	setPin(digito3,OFF);

	aux = msgDisplay[digito]; //aux es el subindice del array tabla de codigos de 7 seg.
	codigo = Tabla_Digitos_BCD_7seg[aux];

	setPin(segmento_a, (( codigo >> 0 ) & (uint8_t)0x01));
	setPin(segmento_b, (( codigo >> 1 ) & (uint8_t)0x01));
	setPin(segmento_c, (( codigo >> 2 ) & (uint8_t)0x01));
	setPin(segmento_d, (( codigo >> 3 ) & (uint8_t)0x01));
	setPin(segmento_e, (( codigo >> 4 ) & (uint8_t)0x01));
	setPin(segmento_f, (( codigo >> 5 ) & (uint8_t)0x01));
	setPin(segmento_g, (( codigo >> 6 ) & (uint8_t)0x01));
	setPin(segmento_dp,(( codigo >> 7 ) & (uint8_t)0x01));

	switch( digito )
	{
    	case DIGITO_0:
    		setPin(digito0,ON); break;
	    case DIGITO_1:
		    setPin(digito1,ON); break;
	    case DIGITO_2:
		    setPin(digito2,ON); break;
        case DIGITO_3:
		    setPin(digito3,ON); break;
	}

	// Incremento el indice del display
	digito++;
	digito %= DIGITOS;
}

///////////////////////////////////////////////////////////////////////////////////////// inicializacion en main creo
////////////////////////////////DISPLAY
void displayACT( void )
{
	uint8_t Val = temp_actual;
	//en cada posicion del array, pongo el valor con el codigo binario del digito a mostrar
	for(uint8_t i = 0 ; i<DIGITOS ; i++ )
	{
		msgDisplayACT[i] = Tabla_Digitos_BCD_7seg[Val%10];
		Val /= 10; // Val debe ser entre 0 y 9!!
	}
}

void displaySET( void ) // la defino para que compile
{
	uint8_t Val = temp_set;
	//en cada posicion del array, pongo el valor con el codigo binario del digito a mostrar
	for(uint8_t i = 0 ; i<DIGITOS ; i++ )
	{
		msgDisplaySET[i] = Tabla_Digitos_BCD_7seg[Val%10];
		Val /= 10; // Val debe ser entre 0 y 9!!
	}}