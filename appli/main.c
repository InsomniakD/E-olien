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
	//Cette ligne doit rester la premi�re �tape de la fonction main().
	HAL_Init();

	//Initialisation de l'UART2 � la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reli�es jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirig�es vers la sonde de d�bogage, la liaison UART �tant ensuite encapsul�e sur l'USB vers le PC de d�veloppement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le p�riph�rique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms � la liste des fonctions appel�es automatiquement chaque ms par la routine d'interruption du p�riph�rique SYSTICK
	Systick_add_callback_function(&process_ms);
	//EPAPER_demo();
	//Vent_init();
	ADC_init(); //Pour la moyenne de tension, intensit� et puissance

	while(1)	//boucle de t�che de fond
	{

		//printf("BMP180 : \n\n");
		//valeur_BMP180 = BMP180_demo();
		//printf("(main)Temp: %2ld degrees\nPressure: %6ld hePascals\n\n",valeur_BMP180[0],valeur_BMP180[1]);
		//printf("DTH_11 : \n\n");
		//humidity = humidite_valeur();
		//printf("(main) DHT11 humidit�=%d%%",humidity);
		//printf("Vitesse du vent : \n\n");
		//wind_speed = Vent_vitesse(); // ATTENTION NECESSITE L'ACTIVATION DE VENT_INIT()
		//printf("vent : | vitesse = %d km/h\n", wind_speed);
		//printf("Mesure tension intensit� et puissance : \n\n");
		//if (vitesse != 0)
		//tension();
		moyenneTIP = moyenne(); // ATENTION activer ADC_init() avec
		printf(" (main) La tension moyenne est : %d.%02dV\nL'intensit� moyenne est : %dmA\nLa puissance moyenne g�n�r�e est : %dmW\n", moyenneTIP[0], moyenneTIP[1], moyenneTIP[2], moyenneTIP[3]);
		//if refresh_dealy //mise a jour de l'�cran toutes les 10min
		HAL_Delay(1500);

	}
}
