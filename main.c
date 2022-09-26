# include "display.h"

/* USER CODE BEGIN PV */
float count = 0;
uint8_t display_on = FALSE;


volatile struct digit digits_struct[DIGITOS]; // BUFFER

//para debug
//en teoria global ya arranca en 0
uint8_t pin_1 = 0;
uint8_t pin_2 = 0;
uint8_t pin_3 = 0;
uint8_t pin_4 = 0;
uint8_t pin_5 = 0;
uint8_t pin_6 = 0;
uint8_t pin_7 = 0;
uint8_t pin_8 = 0;
uint8_t pin_9 = 0;
uint8_t pin_10 = 0;
uint8_t pin_11 = 0;
uint8_t pin_12 = 0;
/* USER CODE END PV */



/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void init_display_off( void )
{
	//digitos en 1 y segmentos en 0, para asegurar diodos eninersa
	set_led( digito_0, HIGH);
	set_led( digito_1, HIGH);
	set_led( digito_2, HIGH);
	set_led( digito_3, HIGH);

	set_led( segmento_a, LOW);
	set_led( segmento_b, LOW);
	set_led( segmento_c, LOW);
	set_led( segmento_d, LOW);
	set_led( segmento_e, LOW);
	set_led( segmento_f, LOW);
	set_led( segmento_g, LOW);
	set_led( segmento_dp, LOW);

	display_on = TRUE;
	count = 0;

	//para debug
	pin_1 = HAL_GPIO_ReadPin(PIN1_GPIO_Port, PIN1_Pin);
	pin_2 = HAL_GPIO_ReadPin(PIN2_GPIO_Port, PIN2_Pin);
	pin_3 = HAL_GPIO_ReadPin(PIN3_GPIO_Port, PIN3_Pin);
	pin_4 = HAL_GPIO_ReadPin(PIN4_GPIO_Port, PIN4_Pin);
	pin_5 = HAL_GPIO_ReadPin(PIN5_GPIO_Port, PIN5_Pin);
	pin_6 = HAL_GPIO_ReadPin(PIN6_GPIO_Port, PIN6_Pin);
	pin_7 = HAL_GPIO_ReadPin(PIN7_GPIO_Port, PIN7_Pin);
	pin_8 = HAL_GPIO_ReadPin(PIN8_GPIO_Port, PIN8_Pin);
	pin_9 = HAL_GPIO_ReadPin(PIN9_GPIO_Port, PIN9_Pin);
	pin_10 = HAL_GPIO_ReadPin(PIN10_GPIO_Port, PIN10_Pin);
	pin_11 = HAL_GPIO_ReadPin(PIN11_GPIO_Port, PIN11_Pin);
	pin_12 = HAL_GPIO_ReadPin(PIN12_GPIO_Port, PIN12_Pin);
}
/* USER CODE END 0 */


  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);
  init_display_off();
  /* USER CODE END 2 */


/* USER CODE BEGIN 4 */
/*
 Lo que hace esto es que si apreto el blue bton, se apaga todo, queda prendido solo el segmento 'A' del digito 4.
 Es por si hay error o algo, de emergencia, apreto y se que queda solo un segmento prendido. El barrido sigue, pero
 en cada vuelta prende solo el mismo segmento 
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
	if ( display_on )
	{
		set_led( digito_0, LOW);
		set_led( digito_1, HIGH);
		set_led( digito_2, HIGH);
		set_led( digito_3, HIGH);

		set_led( segmento_a, HIGH);
		set_led( segmento_b, LOW);
		set_led( segmento_c, LOW);
		set_led( segmento_d, LOW);
		set_led( segmento_e, LOW);
		set_led( segmento_f, LOW);
		set_led( segmento_g, LOW);
		set_led( segmento_dp, LOW);
		// dejo el display 0 con 'a' prendido
		// para saber que se pauso correctamente
		display_on = FALSE;
	}else
	{
		init_display_off();
		display_on = TRUE;
	}

}

/* USER CODE END 4 */



//################ este es el handler del timer (en mi caso el 2). No se agrega al main, modificarlo en stm32f4xx_it.c
/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  if ( display_on )
	  barrido_display();

  /* USER CODE END TIM2_IRQn 1 */
}