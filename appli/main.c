/**
  ******************************************************************************
  * @file    main.c
  * @author  Timothe
  * @date    03-July-2019
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"


uint32_t wind_speed;
uint32_t *valeur_BMP180;
uint8_t humidity;
uint32_t *moyenneTIP;

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}


int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la première étape de la fonction main().
	HAL_Init();

	//Initialisation de l'UART2 à la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reliées jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirigées vers la sonde de débogage, la liaison UART étant ensuite encapsulée sur l'USB vers le PC de développement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le périphérique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms à la liste des fonctions appelées automatiquement chaque ms par la routine d'interruption du périphérique SYSTICK
	Systick_add_callback_function(&process_ms);
	//EPAPER_demo();
	//Vent_init();
	ADC_init(); //Pour la moyenne de tension, intensité et puissance

	while(1)	//boucle de tâche de fond
	{

		//printf("BMP180 : \n\n");
		//valeur_BMP180 = BMP180_demo();
		//printf("(main)Temp: %2ld degrees\nPressure: %6ld hePascals\n\n",valeur_BMP180[0],valeur_BMP180[1]);
		//printf("DTH_11 : \n\n");
		//humidity = humidite_valeur();
		//printf("(main) DHT11 humidité=%d%%",humidity);
		//printf("Vitesse du vent : \n\n");
		//wind_speed = Vent_vitesse(); // ATTENTION NECESSITE L'ACTIVATION DE VENT_INIT()
		//printf("vent : | vitesse = %d km/h\n", wind_speed);
		//printf("Mesure tension intensité et puissance : \n\n");
		//if (vitesse != 0)
		//tension();
		moyenneTIP = moyenne(); // ATENTION activer ADC_init() avec
		printf(" (main) La tension moyenne est : %d.%02dV\nL'intensité moyenne est : %dmA\nLa puissance moyenne générée est : %dmW\n", moyenneTIP[0], moyenneTIP[1], moyenneTIP[2], moyenneTIP[3]);
		//if refresh_dealy //mise a jour de l'écran toutes les 10min
		HAL_Delay(1500);

	}
}
