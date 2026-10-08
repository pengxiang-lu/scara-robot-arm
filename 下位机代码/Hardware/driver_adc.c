#include "driver_config.h"
uint16_t inline_current_adc_value[3];
// ADC输入脚:I_A->PA0,I_B->PA1,IC->PA7,这里默认初始化三路电流传感器
void current_sensor_adc_init()
{
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//开启ADC1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		//开启DMA1的时钟
	
	/*设置ADC时钟*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);						//选择时钟6分频，ADCCLK = 72MHz / 6 = 12MHz
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7;;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA0、PA1引脚初始化为模拟输入
	
	/*规则组通道配置*/
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);	//规则组序列0的位置，配置为通道1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);	//规则组序列1的位置，配置为通道2
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 3, ADC_SampleTime_55Cycles5);	//规则组序列7的位置，配置为通道3
	/*ADC初始化*/
	
	ADC_InitTypeDef ADC_InitStructure;											
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;							
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;			
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;							
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;								
	ADC_InitStructure.ADC_NbrOfChannel = 3;										
	ADC_Init(ADC1, &ADC_InitStructure);											
	
	/*DMA初始化*/
	DMA_InitTypeDef DMA_InitStructure;											
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;				
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)inline_current_adc_value;	
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;							
	DMA_InitStructure.DMA_BufferSize = 3;										
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;								
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;						
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);								
		
	/*DMA和ADC使能*/
	DMA_Cmd(DMA1_Channel1, ENABLE);							//DMA1的通道1使能
	ADC_DMACmd(ADC1, ENABLE);								//ADC1触发DMA1的信号使能
	ADC_Cmd(ADC1, ENABLE);									//ADC1使能
	
	/*ADC校准*/
	ADC_ResetCalibration(ADC1);								//固定流程，内部有电路会自动执行校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
	
	/*ADC触发*/
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//软件触发ADC开始工作，由于ADC处于连续转换模式，故触发一次后ADC就可以一直连续不断地工作
}
void battery_adc_init() 
{
    // 使能GPIOB和ADC2时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC2, ENABLE);
    
    // 配置ADC时钟分频，ADC最大时钟不能超过14MHz
    // 这里假设APB2时钟为72MHz，分频为6，得到12MHz
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    // 配置PB0为模拟输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  // 模拟输入，无需上拉下拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    ADC_InitTypeDef ADC_InitStructure;
    // ADC工作在独立模式
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    // 关闭扫描模式（单通道无需扫描）
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    // 关闭连续转换模式（使用单次转换）
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    // 不使用外部触发，采用软件触发
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    // 数据右对齐
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    // 转换通道数量为1
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC2, &ADC_InitStructure);
    
    // 配置ADC2的通道8（PB0），转换顺序为1，采样时间为55.5个周期
    ADC_RegularChannelConfig(ADC2, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
    
    // 使能ADC2
    ADC_Cmd(ADC2, ENABLE);
    
    // ADC校准
    ADC_ResetCalibration(ADC2);
    while(ADC_GetResetCalibrationStatus(ADC2));  // 等待校准寄存器重置完成
    
    ADC_StartCalibration(ADC2);
    while(ADC_GetCalibrationStatus(ADC2));  // 等待校准完成
}
// ADC采集附带均值滤波
uint16_t battery_read_adc_value(uint8_t n)
{
	uint32_t sum = 0;
	for(uint8_t i = 0;i < n;i++)
	{
	    // 启动ADC2软件转换
		ADC_SoftwareStartConvCmd(ADC2, ENABLE);
		// 等待转换完成（轮询方式）
		while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));
		// 清除转换完成标志位
		ADC_ClearFlag(ADC2, ADC_FLAG_EOC);
		sum += ADC_GetConversionValue(ADC2);
	}

    // 返回转换结果
    return sum/n;
}

