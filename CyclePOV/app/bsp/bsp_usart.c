#define   BSP_USART_C
#include  <bsp_usart.h>

void BSP_USART_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//Inicializamos el buffer circulares de transmisi�n
	//cb_init(&txBuffer);
	//cb_init(&rxBuffer);

	/* Enable UART clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure USART Tx, Rx as alternate function  */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);

	// USART3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = USART_BAUD_RATE;
	USART_InitStructure.USART_WordLength = USART_WORD_LENGTH;
	USART_InitStructure.USART_StopBits = USART_STOP_BIT;
	USART_InitStructure.USART_Parity = USART_PARITY;
	USART_InitStructure.USART_HardwareFlowControl = USART_FLOW_CONTROL;
	USART_InitStructure.USART_Mode = USART_MODE;

	/* USART configuration */
	USART_Init(USART3, &USART_InitStructure);

	USART_Cmd(USART3, ENABLE);

	// Habilitamos las interrupciones
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;		 // we want to configure the USART3 interrupts
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART3 interrupts
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		 // this sets the subpriority inside the group
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			 // the USART3 interrupts are globally enabled
	NVIC_Init(&NVIC_InitStructure);

	//Interrupciones
	//USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}

int BSP_USART_Is_Tx_ISR()
{
	return USART_GetFlagStatus(USART3, USART_FLAG_TXE);
}

int BSP_USART_Is_Rx_ISR()
{
	return USART_GetFlagStatus(USART3, USART_FLAG_RXNE);
}

/*void BSP_USART_Tx(){
	uint8_t byte2send;*/
	/* Este if es necesario porque nada m�s enviar en byte,
	 * se vuelve a activar al interrupci�n, y en la siguiente
	 * llamada, env�a basura.
	 *//*
	if(cb_get(&txBuffer, &byte2send, 1) == 1)
		USART_SendData(USART3, byte2send);

	if(cb_isEmpty(&txBuffer))
		USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
}*/

uint8_t BSP_USART_Rx()
{
	return (uint8_t)USART_ReceiveData(USART3);
}

/*
 * FUNCIONES QUE UTILIZAN EL BUFFER CIRCULAR.
 * Pueden ser necesarias para la transmisi�n.
 */
/**
 * @brief  Encola para enviar "length" bytes del buffer que
 * se pasa como par�metro
 * @param  buffer: puntero a los datos que se quieren enviar.
 * @param  length: n�mero de bytes del buffer a enviar.
 * @retval Devuelve el n�mero de bytes que se ha conseguido encolar.
 */
/*
int send(uint8_t* buffer, int length) {
	int addedBytes = cb_add(&txBuffer, buffer, length);
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);

	return addedBytes;
}
*/
/**
 * @brief  Lee los length bytes del buffer de recepci�n
 * @param  buffer: puero al que se copiaran los bytes recividos.
 * @param  length: n�mero de bytes que se quieren leer.
 * @retval Devuelve el n�mero de bytes que se han conseguido leer.
 */
/*
int receive(uint8_t* buffer, int length) {
	int receivedBytes = cb_get(&rxBuffer, buffer, length);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	return receivedBytes;
}
*/
/**
 * @brief  Env�o bloqueante. No retorna hasta haber enviado todo el buffer.
 * @param  buffer: puntero a los datos que se quieren enviar.
 * @param  length: n�mero de bytes del buffer a enviar.
 */
/*
void sendAll(uint8_t* buffer, int length){
	int sentBytes = 0;

	while(length){
		sentBytes = send(buffer, length);
		buffer += sentBytes;
		length -= sentBytes;
	};
}
*/
/**
 * @brief  Env�o bloqueante. No retorna hasta haber enviado todo el buffer.
 * @param  buffer: puero al que se copiaran los bytes recividos.
 * @param  length: n�mero de bytes que se quieren leer.
 */
/*
void receiveAll(uint8_t* buffer, int length){
	int receivedBytes = 0;

	while(length){
		receivedBytes = receive(buffer, length);
		buffer += receivedBytes;
		length -= receivedBytes;
	};
}

char inline digitToChar(int digit){
	return (char)(((int)'0')+digit);
}

void print(uint8_t* string){
	int length;
	for(length=0 ; string[length] != '\0' && length < CB_SIZE ; ++length);
	sendAll(string, length);
}
void printLine(uint8_t* string){
	uint8_t sl = '\n';
	print(string);
	sendAll(&sl,1);
}
void printChar(uint8_t character){
	sendAll(&character, 1);
}
void printInt(int32_t number){
	//Con un entero de 32b solo se consigen n�meros de 10 d�gitos
	uint8_t buffer[11];
	int length=0, shifter=number;

	//A�adimos el signo
	if(number < 0){
		number *= -1;
		buffer[length++] = '-';
	}

	//Contamos el n�mero de d�gitos que va a tener
	do{
		++length;
		shifter = shifter/10;
	}while(shifter && length < 11);

	//A�adimos los d�gitos
	int i = length;
	do{
		buffer[--i] = digitToChar(number%10);
		number /= 10;
	}while(number);

	sendAll(&buffer[0], length);
}

void printFloat(double number){
	//Separamos la parte entera de la decimal
	int integer = (int)number;
	int decimal = (number-integer)*USART_NDECIMALS;

	printInt(integer);
	printChar('.');
	printInt(decimal);
}
*/
