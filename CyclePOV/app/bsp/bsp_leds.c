#define   BSP_LEDS_C
#include  <bsp_leds.h>
#include  <bsp_image.h>

CPU_INT32U counter;
CPU_INT32U current_animation;
CPU_INT32U current_image;
CPU_INT32U current_spoke;
uint8_t ledBuffer[NUM_GROUPS][LED_BUFFER_SIZE];

////////////////////////////////////////////////////////////
// BIT ARRAY HELPER FUNCTION
////////////////////////////////////////////////////////////
void LedBuffer_SetBit(uint8_t group, uint16_t bit, uint8_t value)
{
	uint16_t num_bit = bit * BITS_PER_RGB_BIT + 1;

	uint16_t num_byte = (num_bit >> 3) + 1;
	uint8_t mask = 1 << (7 - (num_bit & 7));

	ledBuffer[group][num_byte] ^= (-value ^ ledBuffer[group][num_byte]) & mask;
}

////////////////////////////////////////////////////////////
// DEVICE INITIALIZATION PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////
void BSP_Leds_GPIOInit(uint32_t RCC_AHB1Periph, GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOx, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOx, GPIO_PinSource, GPIO_AF);
}

void BSP_Leds_SPIInit(uint8_t APBn, uint32_t RCC_APBPeriph, SPI_TypeDef* SPIx)
{
	SPI_InitTypeDef SPI_InitStruct;

	switch(APBn)
	{
		case 1:
			RCC_APB1PeriphClockCmd(RCC_APBPeriph, ENABLE);
			break;
		case 2:
			RCC_APB2PeriphClockCmd(RCC_APBPeriph, ENABLE);
			break;
		default:
			return;
	}

	SPI_I2S_DeInit(SPIx);

	SPI_StructInit(&SPI_InitStruct);
	SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 0;
	SPI_Init(SPIx, &SPI_InitStruct);

	SPI_I2S_DMACmd(SPIx, SPI_DMAReq_Tx, ENABLE);

	SPI_Cmd(SPIx, ENABLE);
}

void BSP_Leds_DMAInit(uint32_t RCC_AHB1Periph, uint8_t NVIC_IRQChannel, DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_Channel, SPI_TypeDef* SPIx, void *DMA_Memory0BaseAddr)
{
	NVIC_InitTypeDef NVICInit;
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph, ENABLE);

	NVICInit.NVIC_IRQChannel = NVIC_IRQChannel;
	NVICInit.NVIC_IRQChannelPreemptionPriority = 0;
	NVICInit.NVIC_IRQChannelSubPriority = 0;
	NVICInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICInit);

	DMA_DeInit(DMAy_Streamx);

	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_Channel = DMA_Channel;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(SPIx->DR));
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)DMA_Memory0BaseAddr;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;

	DMA_Init(DMAy_Streamx, &DMA_InitStructure);
}

////////////////////////////////////////////////////////////
// BSP FUNCTIONS
////////////////////////////////////////////////////////////
void BSP_Leds_Init()
{
	BSP_Leds_GPIOInit(RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_12, GPIO_PinSource12, GPIO_AF_SPI3);
	BSP_Leds_SPIInit(1, RCC_APB1Periph_SPI3, SPI3);
	BSP_Leds_DMAInit(RCC_AHB1Periph_DMA1, DMA1_Stream5_IRQn, DMA1_Stream5, DMA_Channel_0, SPI3, &ledBuffer[0]);

	BSP_Leds_GPIOInit(RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_5, GPIO_PinSource5, GPIO_AF_SPI1);
	BSP_Leds_SPIInit(2, RCC_APB2Periph_SPI1, SPI1);
	BSP_Leds_DMAInit(RCC_AHB1Periph_DMA2, DMA2_Stream5_IRQn, DMA2_Stream5, DMA_Channel_3, SPI1, &ledBuffer[1]);

	BSP_Leds_ClearBuffers();
}

void BSP_Leds_NextImage()
{
	CPU_INT16U loop  = counter / animations[current_animation].num_images;

	if(loop >= animations[current_animation].duration)
	{
		current_animation = (current_animation + 1) % NUM_ANIMATIONS;

		counter = 0;
	}

	current_image = animations[current_animation].index + (counter % animations[current_animation].num_images);
	counter++;
}

void BSP_Leds_ResetSpokes()
{
	current_spoke = 0;
}

CPU_INT08U BSP_Leds_NextSpoke()
{
	uint32_t num_bit, led, color, byte0, byte1, bit;

	num_bit = 0;

	for(led = 0; led < NUM_LEDS; led++)
	for(color = 0; color < 3; color++)
	{
		byte0 = images[current_image][(current_spoke + 0 * (NUM_SPOKES / NUM_GROUPS)) % NUM_SPOKES][led][color];
		byte1 = images[current_image][(current_spoke + 1 * (NUM_SPOKES / NUM_GROUPS)) % NUM_SPOKES][led][color];

		for(bit = 0; bit < 8; bit++)
		{
			LedBuffer_SetBit(0, num_bit, (byte0 >> (7 - bit)) & 1);
			LedBuffer_SetBit(1, num_bit, (byte1 >> (7 - bit)) & 1);

			num_bit++;
		}
	}

	current_spoke++;

	return current_spoke < (int)(NUM_SPOKES * PROPORTION);
}

void BSP_Leds_ClearBuffers()
{
	int i, group;

	for(group = 0; group < NUM_GROUPS; group++)
	{
		for(i = 1; i < LED_BUFFER_SIZE; i += 3)
		{
			ledBuffer[group][i + 0] = 0x92;
			ledBuffer[group][i + 1] = 0x49;
			ledBuffer[group][i + 2] = 0x24;
		}

		ledBuffer[group][0]						= 0x00;
		ledBuffer[group][LED_BUFFER_SIZE - 2] 	= 0x00;
		ledBuffer[group][LED_BUFFER_SIZE - 1] 	= 0x00;
	}
}

void BSP_Leds_DMAEnable()
{
	DMA_SetCurrDataCounter(DMA1_Stream5, LED_BUFFER_SIZE);
	DMA_SetCurrDataCounter(DMA2_Stream5, LED_BUFFER_SIZE);

	DMA_ITConfig(DMA1_Stream5, DMA_IT_TC, ENABLE);
	DMA_ITConfig(DMA2_Stream5, DMA_IT_TC, ENABLE);

	DMA_Cmd(DMA1_Stream5, ENABLE);
	DMA_Cmd(DMA2_Stream5, ENABLE);
}

void BSP_Leds_DMA1Disable()
{
	DMA_Cmd(DMA1_Stream5, DISABLE);
	DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);
}

void BSP_Leds_DMA2Disable()
{
	DMA_Cmd(DMA2_Stream5, DISABLE);
	DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_TCIF5);
}

void BSP_Leds_Switch()
{
	CPU_INT32U dma1_m0ar = DMA1_Stream5->M0AR;
	CPU_INT32U dma2_m0ar = DMA2_Stream5->M0AR;

	DMA1_Stream5->M0AR = dma2_m0ar;
	DMA2_Stream5->M0AR = dma1_m0ar;
}

