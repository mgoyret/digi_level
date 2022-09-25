/*
 * display.h
 *
 *  Created on: 16 sept. 2022
 *      Author: marco
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"

// DISPLAY 8seg y 4dig
#define DIGITOS 4 // cantidad de digitos del display
#define DIGITOS_DIV DIGITOS*2
#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 1

#define PIN1_Pin GPIO_PIN_8
#define PIN1_GPIO_Port GPIOC
#define PIN2_Pin GPIO_PIN_6
#define PIN2_GPIO_Port GPIOC
#define PIN3_Pin GPIO_PIN_5
#define PIN3_GPIO_Port GPIOC
#define PIN4_Pin GPIO_PIN_1
#define PIN4_GPIO_Port GPIOB
#define PIN5_Pin GPIO_PIN_4
#define PIN5_GPIO_Port GPIOC
#define PIN6_Pin GPIO_PIN_5
#define PIN6_GPIO_Port GPIOB
#define PIN7_Pin GPIO_PIN_2
#define PIN7_GPIO_Port GPIOD
#define PIN8_Pin GPIO_PIN_8
#define PIN8_GPIO_Port GPIOB
#define PIN9_Pin GPIO_PIN_11
#define PIN9_GPIO_Port GPIOC
#define PIN10_Pin GPIO_PIN_10
#define PIN10_GPIO_Port GPIOC
#define PIN11_Pin GPIO_PIN_12
#define PIN11_GPIO_Port GPIOC
#define PIN12_Pin GPIO_PIN_7
#define PIN12_GPIO_Port GPIOB

#define PIN_DISPLAY1 PIN1_GPIO_Port, PIN1_Pin
#define PIN_DISPLAY2 PIN2_GPIO_Port, PIN2_Pin
#define PIN_DISPLAY3 PIN3_GPIO_Port, PIN3_Pin
#define PIN_DISPLAY4 PIN4_GPIO_Port, PIN4_Pin
#define PIN_DISPLAY5 PIN5_GPIO_Port, PIN5_Pin
#define PIN_DISPLAY6 PIN6_GPIO_Port, PIN6_Pin
#define PIN_DISPLAY7 PIN7_GPIO_Port, PIN7_Pin
#define PIN_DISPLAY8 PIN8_GPIO_Port, PIN8_Pin
#define PIN_DISPLAY9 PIN9_GPIO_Port, PIN9_Pin
#define PIN_DISPLAY10 PIN10_GPIO_Port, PIN10_Pin
#define PIN_DISPLAY11 PIN11_GPIO_Port, PIN11_Pin
#define PIN_DISPLAY12 PIN12_GPIO_Port, PIN12_Pin

#define digito_0 PIN_DISPLAY6 //!< Display 7 Segmentos
#define digito_1 PIN_DISPLAY8
#define digito_2 PIN_DISPLAY9
#define digito_3 PIN_DISPLAY12

#define segmento_a PIN_DISPLAY11
#define segmento_b PIN_DISPLAY7
#define segmento_c PIN_DISPLAY4
#define segmento_d PIN_DISPLAY2
#define segmento_e PIN_DISPLAY1
#define segmento_f PIN_DISPLAY10
#define segmento_g PIN_DISPLAY5
#define segmento_dp PIN_DISPLAY3

							// pgfe dcba
#define CODIGO_OFF	0x00 	// 0000 0000
#define CODIGO_0	0x3F	// 0011 1111
#define CODIGO_0p	0xBF	// 1011 1111
#define CODIGO_1	0x06	// 0000 0110
#define CODIGO_1p	0x86	// 1000 0110
#define CODIGO_2	0x5B	// 0101 1011
#define CODIGO_2p	0xDB	// 1101 1011
#define CODIGO_3	0x4F	// 0100 1111
#define CODIGO_3p	0xCF	// 1100 1111
#define CODIGO_4	0x66	// 0110 0110
#define CODIGO_4p	0xE6	// 1110 0110
#define CODIGO_5	0x6D	// 0110 1101
#define CODIGO_5p	0xED	// 1110 1101
#define CODIGO_6	0x7D	// 0111 1101
#define CODIGO_6p	0xFD	// 1111 1101
#define CODIGO_7	0x07	// 0000 0111
#define CODIGO_7p	0x87	// 1000 0111
#define CODIGO_8	0x7F	// 0111 1111
#define CODIGO_8p	0xFF	// 1111 1111
#define CODIGO_9	0x6F	// 0110 1111
#define CODIGO_9p	0xEF	// 1110 1111

#define DIGITO_0_0	0 //!< Numero de Digito
#define DIGITO_0_1	1
#define DIGITO_1_0	2
#define DIGITO_1_1	3
#define DIGITO_2_0	4
#define DIGITO_2_1	5
#define DIGITO_3_0	6
#define DIGITO_3_1	7

#define DIGITO_0	0
#define DIGITO_1	1
#define DIGITO_2	2
#define DIGITO_3	3

#define LOW		0
#define HIGH	1
#define TRUE	1
#define FALSE	0
typedef _Bool bool;

/*
1- La IMU lee y pone el float valor en un buffer "msg_buffer".
2- A partir del buffer, llamamos a display(), que carga el digits_struct[], con cada digito y si tiene o no punto
    si el digito tiene punto, quiere decir que luego de el hay un punto. Es decir, en el
    numero '1.234', el punto lo asociamos al '1'.
3- barrido_display() corre periodicamente en el sistyck (ver donde), mostrando lo que este en digits_struct[]
*/

void display( float val );
void set_led(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void barrido_display( void );

// float a array de structs con int y bool si tiene punto
// la IMU mide, y el float me lo pasan como un array de structs, cada posicion tiene el numero, y si tiene o no punto
typedef struct digit {
  int	number;
  bool	point;
}digit;


#endif /* INC_DISPLAY_H_ */
