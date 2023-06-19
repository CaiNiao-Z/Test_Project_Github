/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    key.c
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
#include "key.h"

/* USER CODE BEGIN 0 */
#include "stdio.h"
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
#define HARD_KEY_NUM	    4	   				/* 实体按键个数 */
static KEY_T      s_tBtn[HARD_KEY_NUM] = {0};
static KEY_FIFO_T s_tKey;						/* 按键FIFO变量,结构体 */

static void KEY_FIFO_Init(void);
static void KEY_GPIO_Init(void);
static uint8_t IsKey1Down(void);
static uint8_t IsKey2Down(void);
static uint8_t IsKey3Down(void);
static uint8_t IsKey4Down(void);

static void KEY_Detect(uint8_t i);
/* USER CODE END 1 */
/*
*********************************************************************************************************
*	函 数 名: KEY_Init
*	功能说明: 初始化按键. 该函数在主函数的开头被调用。
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void KEY_Init(void)
{
	KEY_FIFO_Init();		/* 初始化按键变量 */
	KEY_GPIO_Init();		/* 初始化按键硬件 */
}
/*
*********************************************************************************************************
*	函 数 名: KEY_FIFO_Init
*	功能说明: 初始化按键变量
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
static void KEY_FIFO_Init(void)
{
	uint8_t i;

	/* 对按键FIFO读写指针清零 */
	s_tKey.Read = 0;
	s_tKey.Write = 0;

	/* 给每个按键结构体成员变量赋一组缺省值 */
	for (i = 0; i < HARD_KEY_NUM; i++)
	{
		s_tBtn[i].LongTime = KEY_LONG_TIME;			/* 长按时间 0 表示不检测长按键事件 */
		s_tBtn[i].Count = KEY_FILTER_TIME / 2;		/* 计数器设置为滤波时间的一半 */
		s_tBtn[i].State = 0;							/* 按键缺省状态，0为未按下 */
		s_tBtn[i].RepeatSpeed = 0;						/* 按键连发的速度，0表示不支持连发 */
		s_tBtn[i].RepeatCount = 0;						/* 连发计数器 */
	}
	/* 判断按键按下的函数 */
	s_tBtn[0].IsKeyDownFunc = IsKey1Down;
	s_tBtn[1].IsKeyDownFunc = IsKey2Down;
	s_tBtn[2].IsKeyDownFunc = IsKey3Down;
  s_tBtn[3].IsKeyDownFunc = IsKey4Down;
}
/*
*********************************************************************************************************
*	函 数 名: KEY_GPIO_Config
*	功能说明: 配置按键对应的GPIO
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
static void KEY_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();


  /*Configure GPIO pins : PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = KEY2_Pin|KEY3_Pin|KEY4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(KEY1_GPIO_Port, &GPIO_InitStruct);

}

/*
*********************************************************************************************************
*	函 数 名: IsKeyDownFunc
*	功能说明: 判断按键是否按下。单键和组合键区分。单键事件不允许有其他键按下。
*	形    参: 无
*	返 回 值: 返回值1 表示按下(导通），0表示未按下（释放）
*********************************************************************************************************
*/
static uint8_t IsKey1Down(void) 
{
	if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_SET) 
		return 1;
	else 
		return 0;
}
static uint8_t IsKey2Down(void) 
{
	if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET) 
		return 1;
	else 
		return 0;
}

static uint8_t IsKey3Down(void) 
{
	if (HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET) 
		return 1;
	else 
		return 0;
}

static uint8_t IsKey4Down(void) 
{
	if (HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin) == GPIO_PIN_RESET) 
		return 1;
	else 
		return 0;
}

/*
*********************************************************************************************************
*	函 数 名: KEY_FIFO_Put
*	功能说明: 将1个键值压入按键FIFO缓冲区。可用于模拟一个按键。
*	形    参:  _KeyCode : 按键代码
*	返 回 值: 无
*********************************************************************************************************
*/
void KEY_FIFO_Put(uint8_t _KeyCode)
{
	s_tKey.Buf[s_tKey.Write] = _KeyCode;

	if (++s_tKey.Write  >= KEY_FIFO_SIZE)
	{
		s_tKey.Write = 0;
	}
}

/*
*********************************************************************************************************
*	函 数 名: KEY_FIFO_Get
*	功能说明: 从按键FIFO缓冲区读取一个键值。
*	形    参: 无
*	返 回 值: 按键代码
*********************************************************************************************************
*/
uint8_t KEY_FIFO_Get(void)
{
	uint8_t ret;

	if (s_tKey.Read == s_tKey.Write)
	{
		return KEY_NONE;
	}
	else
	{
		ret = s_tKey.Buf[s_tKey.Read];

		if (++s_tKey.Read >= KEY_FIFO_SIZE)
		{
			s_tKey.Read = 0;
		}
		return ret;
	}
}



/*
*********************************************************************************************************
*	函 数 名: KEY_GetState
*	功能说明: 读取按键的状态
*	形    参:  _ucKeyID : 按键ID，从0开始
*	返 回 值: 1 表示按下， 0 表示未按下
*********************************************************************************************************
*/
uint8_t KEY_GetState(KEY_ID_E _ucKeyID)
{
	return s_tBtn[_ucKeyID].State;
}

/*
*********************************************************************************************************
*	函 数 名: KEY_SetParam
*	功能说明: 设置按键参数
*	形    参：_ucKeyID : 按键ID，从0开始
*			_LongTime : 长按事件时间
*			 _RepeatSpeed : 连发速度
*	返 回 值: 无
*********************************************************************************************************
*/
void KEY_SetParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t  _RepeatSpeed)
{
	s_tBtn[_ucKeyID].LongTime = _LongTime;			/* 长按时间 0 表示不检测长按键事件 */
	s_tBtn[_ucKeyID].RepeatSpeed = _RepeatSpeed;			/* 按键连发的速度，0表示不支持连发 */
	s_tBtn[_ucKeyID].RepeatCount = 0;						/* 连发计数器 */
}

/*
*********************************************************************************************************
*	函 数 名: KEY_FIFO_Clear
*	功能说明: 清空按键FIFO缓冲区
*	形    参：无
*	返 回 值: 按键代码
*********************************************************************************************************
*/
void KEY_FIFO_Clear(void)
{
	s_tKey.Read = s_tKey.Write;
}
/*
*********************************************************************************************************
*	函 数 名: bsp_KeyScan10ms
*	功能说明: 扫描所有按键。非阻塞，被systick中断周期性的调用，10ms一次
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void KEY_Scan(void)
{
	uint8_t i;

	for (i = 0; i < HARD_KEY_NUM; i++)
	{
		KEY_Detect(i);
	}
}
/*
*********************************************************************************************************
*	函 数 名: KEY_Detect
*	功能说明: 检测一个按键。非阻塞状态，必须被周期性的调用。
*	形    参: IO的id， 从0开始编码
*	返 回 值: 无
*********************************************************************************************************
*/
static void KEY_Detect(uint8_t i)
{
	KEY_T *pBtn;

	pBtn = &s_tBtn[i];/*读取相应按键的结构体地址，程序里面每个按键都有自己的结构体。*/
	if (pBtn->IsKeyDownFunc())
	{/*这个里面执行的是按键按下的处理*/
		if (pBtn->Count < KEY_FILTER_TIME)/*用于按键滤波前给 Count 设置一个初值*/
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count < 2 * KEY_FILTER_TIME)/*这里实现 KEY_FILTER_TIME 时间长度的延迟*/
		{
			pBtn->Count++;
		}
		else
		{
			if (pBtn->State == 0)
			{
				pBtn->State = 1;/*如果按键按下了，这里就将其设置为 1*/

				/* 发送按钮按下的消息 */
				KEY_FIFO_Put((uint8_t)(3 * i + 1));
			}

			if (pBtn->LongTime > 0) /*LongTime初始值是100。单位10ms，持续1秒，认为长按事件*/
			{
				if (pBtn->LongCount < pBtn->LongTime) /*LongCount长按计数器。单位10ms，持续1秒，认为长按事件*/
				{
					/* 发送按钮持续按下的消息 */
					if (++pBtn->LongCount == pBtn->LongTime)/*LongCount等于LongTime(100),10ms进来一次，进来了100次也就是说按下时间为于1s*/
					{
						/* 键值放入按键FIFO */
						KEY_FIFO_Put((uint8_t)(3 * i + 3));
					}
				}
				else/*LongCount大于LongTime(100),也就是说按下时间大于1s*/
				{
					if (pBtn->RepeatSpeed > 0)/* RepeatSpeed连续按键周期 */
					{
						if (++pBtn->RepeatCount >= pBtn->RepeatSpeed)
						{
							pBtn->RepeatCount = 0;
							/* 长按键后，每隔10ms发送1个按键。因为长按也是要发送键值得，10ms发送一次。*/
							KEY_FIFO_Put((uint8_t)(3 * i + 1));
						}
					}
				}
			}
		}
	}
	else
	{/*这个里面执行的是按键松手的处理或者按键没有按下的处理*/
		if(pBtn->Count > KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count != 0)
		{
			pBtn->Count--;
		}
		else
		{
			if (pBtn->State == 1)
			{
				pBtn->State = 0;

				/* 发送按钮弹起的消息 */
				KEY_FIFO_Put((uint8_t)(3 * i + 2));
			}
		}

		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}


/* USER CODE BEGIN 2 */
//uint8_t Key_Scanf(uint8_t mode)
//{
//  static uint8_t key_up = 1;  /* 按键按松开标志 */
//  uint8_t key_value=0;
//  if(mode) key_up = 1;          /* 支持连按 */
//  
//  if(key_up && (KEY1 == 1 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0))
//  {
//    HAL_Delay(10);
//    key_up = 0;
//    if(KEY1 == 1) key_value = KEY1_PRESS;
//    if(KEY2 == 0) key_value = KEY2_PRESS;
//    if(KEY3 == 0) key_value = KEY3_PRESS;
//    if(KEY4 == 0) key_value = KEY4_PRESS;  
//  }else if(KEY1 == 0 || KEY2 == 1 || KEY3 == 1 || KEY4 == 1)
//  {
//    /* 没有任何按键按下, 标记按键松开 */
//    key_up = 1;
//  }
//  return key_value; //返回按键值
//}



/* USER CODE END 2 */
