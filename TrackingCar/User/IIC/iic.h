#ifndef _IIC_H_
#define _IIC_H_

/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */
#define GPIO_PORT_I2C	GPIOB			/* GPIO�˿� */
#define RCC_I2C_PORT 	RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define I2C_SCL_PIN		GPIO_Pin_10			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define I2C_SDA_PIN		GPIO_Pin_11			/* ���ӵ�SDA�����ߵ�GPIO */

#define I2C_SCL_1()  GPIO_SetBits(GPIO_PORT_I2C, I2C_SCL_PIN)		/* SCL = 1 */
#define I2C_SCL_0()  GPIO_ResetBits(GPIO_PORT_I2C, I2C_SCL_PIN)		/* SCL = 0 */

#define I2C_SDA_1()  GPIO_SetBits(GPIO_PORT_I2C, I2C_SDA_PIN)		/* SDA = 1 */
#define I2C_SDA_0()  GPIO_ResetBits(GPIO_PORT_I2C, I2C_SDA_PIN)		/* SDA = 0 */

#define I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIO_PORT_I2C, I2C_SDA_PIN)	/* ��SDA����״̬ */

#include "stm32f10x.h"

#define I2C_WR	0		/* д����bit */
#define I2C_RD	1		/* ������bit */

extern void i2c_Start(void);
extern void i2c_Stop(void);
extern void i2c_SendByte(uint8_t _ucByte);
extern uint8_t i2c_ReadByte(uint8_t ack);
extern uint8_t i2c_WaitAck(void);
extern void i2c_Ack(void);
extern void i2c_NAck(void);
extern uint8_t i2c_CheckDevice(uint8_t _Address);
extern void i2c_GPIO_Config(void);

#endif 
