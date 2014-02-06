#define   BSP_LEDS_C
#include  <bsp_leds.h>

uint8_t		ledBuffer[LED_BUFFER_SIZE];
uint8_t		images[NUM_IMAGES][NUM_SPOKES][NUM_LEDS][3];

uint8_t		current_image = 0;

void bitarray_set(uint16_t bit, uint8_t value)
{
	uint16_t num_bit = bit * BITS_PER_RGB_BIT + 1;

	uint16_t num_byte = (num_bit >> 3) + 1;
	uint8_t mask = 1 << (7 - (num_bit & 7));

	if(value)
	{
		ledBuffer[num_byte] |= mask;
	}
	else
	{
		ledBuffer[num_byte] &= ~mask;
	}
}

void BSP_Leds_Init()
{
	images[0][0][0][0] = 0xFF;
	images[0][0][0][1] = 0x00;
	images[0][0][0][2] = 0x00;

	images[0][1][0][0] = 0x00;
	images[0][1][0][1] = 0xFF;
	images[0][1][0][2] = 0x00;

	images[0][2][0][0] = 0x00;
	images[0][2][0][1] = 0x00;
	images[0][2][0][2] = 0xFF;

	images[0][3][0][0] = 0xFF;
	images[0][3][0][1] = 0xFF;
	images[0][3][0][2] = 0xFF;


	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStruct;
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVICInit;

	// GPIO CONFIG
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);

	// SPI CONFIG
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	SPI_I2S_DeInit(SPI2);

	SPI_StructInit(&SPI_InitStruct);
	SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 0;
	SPI_Init(SPI2, &SPI_InitStruct);

	// DMA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	// Channel 0 Stream 4
	NVICInit.NVIC_IRQChannel = DMA1_Stream4_IRQn;
	NVICInit.NVIC_IRQChannelPreemptionPriority = 0;
	NVICInit.NVIC_IRQChannelSubPriority = 0;
	NVICInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICInit);

	DMA_DeInit(DMA1_Stream4);

	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(SPI2->DR));
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;

	DMA_Init(DMA1_Stream4, &DMA_InitStructure);

	SPI_I2S_DMACmd(SPI2, SPI_DMAReq_Tx, ENABLE);

	BSP_Leds_ClearBuffer();
}

void BSP_Leds_ClearBuffer()
{
	int i;

	for(i = 1; i < LED_BUFFER_SIZE; i += 3)
	{
		ledBuffer[i + 0] = 0x92;
		ledBuffer[i + 1] = 0x49;
		ledBuffer[i + 2] = 0x24;
	}

	ledBuffer[0] = 0x00;
	ledBuffer[LED_BUFFER_SIZE - 2] = 0x00;
	ledBuffer[LED_BUFFER_SIZE - 1] = 0x00;
}

void BSP_Leds_SetBuffer(CPU_INT32U num_spoke)
{
	uint16_t num = 0;
	uint8_t led, color, byte, bit;

	for(led = 0; led < NUM_LEDS; led++)
	for(color = 0; color < 3; color++)
	{
		byte = images[current_image][num_spoke][led][color];

		for(bit = 0; bit < 8; bit++)
		{
			bitarray_set(num++, (byte >> (7 - bit)) & 1);
		}
	}
}

void BSP_Leds_DMAEnable()
{
	SPI_Cmd(SPI2, DISABLE);
	DMA_Cmd(DMA1_Stream4, DISABLE);
	DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);

	DMA_MemoryTargetConfig(DMA1_Stream4, (uint32_t)&ledBuffer, DMA_Memory_0);
	DMA_SetCurrDataCounter(DMA1_Stream4, LED_BUFFER_SIZE);

	// Enable interrupt in Transfer Complete condition
	DMA_ITConfig(DMA1_Stream4, DMA_IT_TC, ENABLE);

	DMA_Cmd(DMA1_Stream4, ENABLE);
	SPI_Cmd(SPI2, ENABLE);
}

void BSP_Leds_DMADisable()
{
	SPI_Cmd(SPI2, DISABLE);
	DMA_Cmd(DMA1_Stream4, DISABLE);
	DMA_ClearITPendingBit(DMA1_Stream4, DMA_IT_TCIF4);
}


