#include "sensor.h"
#include "ch32v20x_gpio.h"
#include "ch32v20x_adc.h"
#include "ch32v20x_rcc.h"

#define SENSOR_LED_PORT GPIOA
#define SENSOR_LED_PIN GPIO_Pin_5
#define SENSOR_READ_PORT GPIOB
#define SENSOR_READ_PIN GPIO_Pin_0
#define SENSOR_ADC_CHANNEL ADC_Channel_8 // PB0 = ADC1_IN8
     uint8_t last_proximity_state_detected = 0;
void Sensor_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable clocks for GPIOB (sensor input) and ADC1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1, ENABLE);
    // Enable clock for LED port GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // Configure PB0 (ADC1_IN8) as analog input
    GPIO_InitStructure.GPIO_Pin = SENSOR_READ_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(SENSOR_READ_PORT, &GPIO_InitStructure);

    // Configure PA5 (LED) as push-pull output
    GPIO_InitStructure.GPIO_Pin = SENSOR_LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SENSOR_LED_PORT, &GPIO_InitStructure);

    // ADC1 configuration
    ADC_DeInit(ADC1);
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    // ADC calibration
    ADC_Cmd(ADC1, ENABLE);
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1))
        ;
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1))
        ;
    Sensor_LedOn(); // Turn on sensor LED for testing
}

void Sensor_LedOn(void)
{
    GPIO_SetBits(SENSOR_LED_PORT, SENSOR_LED_PIN);
}

void Sensor_LedOff(void)
{
    GPIO_ResetBits(SENSOR_LED_PORT, SENSOR_LED_PIN);
}

int Sensor_ReadValue(void)
{
    // Digital read of sensor input pin
    return GPIO_ReadInputDataBit(SENSOR_READ_PORT, SENSOR_READ_PIN);
}

uint16_t Sensor_ReadAnalog(void)
{
    // Select ADC channel and start conversion
    ADC_RegularChannelConfig(ADC1, SENSOR_ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    // Wait for end-of-conversion
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
        ;
    uint16_t val = ADC_GetConversionValue(ADC1);
    // Clear EOC flag
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
    return val;
}
