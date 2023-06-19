/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ws2812.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "ws2812.h"

/* USER CODE BEGIN 0 */
#include "delay.h"
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/*********************************************************************************************************
*	�� �� ��: RGB_GPIO_Init
*	����˵��: ��ʼ��RGB���IO�����á�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void RGB_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RGB_GPIO_Port, RGB_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = RGB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(RGB_GPIO_Port, &GPIO_InitStruct);
  
}

/* USER CODE BEGIN 2 */
/*********************************************************************************************************
*	�� �� ��: RGB_LED_Write0
*	����˵��: ��ws2812������д0����
*	��    ��: ��
*	�� �� ֵ: ��
* ��    ע: ��ͬ��Ƶ��__nop()��ʱ��̫һ��������168M��Ƶ����С��ʱӦ���ǣ�1/168000000=5.95ns����ʾ�����Ļ������Բ�һ��ʱ��
*********************************************************************************************************
*/
void RGB_LED_Write0(void)
{
  RGB_LED_HIGH;     //��ע����Լ320ns
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();//1
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();
   RGB_LED_LOW;     //��ע����Լ960ns
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();//1
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();//6
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();//11
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();//16

}

/*********************************************************************************************************
*	�� �� ��: RGB_LED_Write1
*	����˵��: ��ws2812������д1����
*	��    ��: ��
*	�� �� ֵ: ��
* ��    ע: ��ͬ��Ƶ��__nop()��ʱ��̫һ��������168M��Ƶ����С��ʱӦ���ǣ�1/168000000=5.95ns����ʾ�����Ļ������Բ�һ��ʱ��
*********************************************************************************************************
*/
void RGB_LED_Write1(void)
{
  RGB_LED_HIGH;     //��ע����Լ960ns
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();//1
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();//6
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();//11
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();//16

  RGB_LED_LOW;      //��ע����Լ320ns
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();//1
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  __nop();__nop();__nop();
}
/*********************************************************************************************************
*	�� �� ��: RGB_LED_Reset
*	����˵��: ��ws2812�����ݸ�λ����
*	��    ��: ��
*	�� �� ֵ: ��
* ��    ע: ��
*********************************************************************************************************
*/
void RGB_LED_Reset(void)
{
  RGB_LED_LOW;
  delay_us(280);
}
/*********************************************************************************************************
*	�� �� ��: RGB_LED_Write_Byte
*	����˵��: ��ws2812��д��һ���ֽ�(8λ)�����ݣ�����ws2812���ݽṹ��Ҫ�ȷ��͸�λ��
*	��    ��: ��
*	�� �� ֵ: ��
* ��    ע: 24bit���ݽṹΪ��8��8��8�����ȷ���λ������RGB��˳��������(G7->G6->������...B0)
*********************************************************************************************************
*/

void RGB_LED_Write_Byte(uint8_t byte)
{
  uint8_t i;
  //
  for(i=0;i<8;i++)
  {
    //���ж����λΪ0����1�������1�͵��÷�������1�ĺ�������֮�����÷�������0�ĺ�����
    if(byte&0x80)
    {
      RGB_LED_Write1();
    }
    else
    {
      RGB_LED_Write0();
    }
    byte <<= 1;//���͸�λ��ͨ����λ�������ʹθ�λ��֪�����������λ��
  }
}
/*********************************************************************************************************
*	�� �� ��: RGB_LED_Write_24Bits
*	����˵��: ���д��RGB��ԭɫ��Ӧ��16��������
*	��    ��: ���磺	Ҫ���Ƶ���ɫΪ����������	��Ӧ��16����Ϊ��0x9932CC ��Ӧ��ʮ����RGBΪ��153,50,204
*           uint8_t green:0x32
*           uint8_t red:0x99
*           uint8_t blue:0xCC
*	�� �� ֵ: ��
* ��    ע: 24bit���ݽṹΪ��8��8��8������λ�ȷ�������RGB��˳��������(G7->G6->������...B0)
*           RGB��ɫ��16������ɫ��ת����ַ��https://www.sioe.cn/yingyong/yanse-rgb-16/
*********************************************************************************************************
*/
void RGB_LED_Write_24Bits(uint8_t green, uint8_t red, uint8_t blue)
{
  RGB_LED_Write_Byte(green);    //�ȷ�����ɫ��Ӧ8λ
  RGB_LED_Write_Byte(red);      //�ٷ��ͺ�ɫ��Ӧ8λ
  RGB_LED_Write_Byte(blue);     //�������ɫ��Ӧ8λ
}

/*********************************************************************************************************
*	�� �� ��: RGB_LED_Write_24Bits_Hex
*	����˵��: ֱ��д��RGB��ԭɫ��Ӧ��16�������֣����ò�⡣
*	��    ��: uint32_t color��16������ɫ��
*	�� �� ֵ: ��
* ��    ע: 24bit���ݽṹΪ��8��8��8������λ�ȷ�������RGB��˳��������(G7->G6->������...B0)
*           RGB��ɫ��16������ɫ��ת����ַ��https://www.sioe.cn/yingyong/yanse-rgb-16/
*********************************************************************************************************
*/
void RGB_LED_Write_24Bits_Hex(uint32_t color)
{
  RGB_LED_Write_Byte(color>>8);     //�ȷ�����ɫ��Ӧ8λ
  RGB_LED_Write_Byte(color>>16);    //�ٷ��ͺ�ɫ��Ӧ8λ
  RGB_LED_Write_Byte(color);        //�������ɫ��Ӧ8λ
}

/*********************************************************************************************************
*	�� �� ��: RGB_LED_Red
*	����˵��: ������ɫ�趨��������ɫ�Դ����ơ�
*	��    ��: 
*	�� �� ֵ: 
* ��    ע: 24bit���ݽṹΪ��8��8��8������λ�ȷ�������RGB��˳��������(G7->G6->������...B0)
*           RGB��ɫ��16������ɫ��ת����ַ��https://www.sioe.cn/yingyong/yanse-rgb-16/
*********************************************************************************************************
*/
void RGB_LED_Red(void)
{
  uint8_t i;
  //7��LEDȫ�ʵ�
  for(i=0;i<RGB_NUM;i++)
  {
    RGB_LED_Write_24Bits(0, 0xff, 0);
  }
}

void RGB_LED_Green(void)
{
  uint8_t i;

  for(i=0;i<RGB_NUM;i++)
  {
    RGB_LED_Write_24Bits(0xff, 0, 0);
  }
}

void RGB_LED_Blue(void)
{
  uint8_t i;

  for(i=0;i<RGB_NUM;i++)
  {
    RGB_LED_Write_24Bits(0, 0, 0xff);
  }
}

/*********************************************************************************************************
*	�� �� ��: RGB_LED_Color
*	����˵��: ������ɫ�趨����������ɫ��
*	��    ��: uint32_t color��16������ɫ��
*	�� �� ֵ: 
* ��    ע: 24bit���ݽṹΪ��8��8��8������λ�ȷ�������RGB��˳��������(G7->G6->������...B0)
*           RGB��ɫ��16������ɫ��ת����ַ��https://www.sioe.cn/yingyong/yanse-rgb-16/
*********************************************************************************************************
*/
void RGB_LED_Color(uint8_t num, uint32_t color)
{
  uint8_t i;
  for(i=0;i<RGB_NUM;i++)
  {
    if(i < num)
      RGB_LED_Write_24Bits_Hex(color);
    else
      RGB_LED_Write_24Bits_Hex(0);
  }
  RGB_LED_Reset();
}

/*********************************************************************************************************
*	�� �� ��: RGB_LED_Color_One_By_One
*	����˵��: ������ɫ�趨����������ɫ��
*	��    ��: uint32_t color��16������ɫ��
*	�� �� ֵ: 
* ��    ע: 24bit���ݽṹΪ��8��8��8������λ�ȷ�������RGB��˳��������(G7->G6->������...B0)
*           RGB��ɫ��16������ɫ��ת����ַ��https://www.sioe.cn/yingyong/yanse-rgb-16/
*********************************************************************************************************
*/
void RGB_LED_Color_One_By_One(uint32_t color)
{
  uint8_t i;
  for(i=0;i<RGB_WANT_NUM-1;++i)
  {
    RGB_LED_Write_24Bits_Hex(0);
//    HAL_Delay(1000);
  }
  
}

/* USER CODE END 2 */
