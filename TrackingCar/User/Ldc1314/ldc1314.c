#include "ldc1314.h"

uint16_t CH0, CH1, CH2, CH3;

static void EvmWriteReg(u8 reg_add, u16 reg_dat)
{
		i2c_Start();
		i2c_SendByte(EVM_SLAVE_ADDRESS);
		i2c_WaitAck();
		i2c_SendByte(reg_add);
		i2c_WaitAck();
		i2c_SendByte((u8)((reg_dat >> 8) & 0xFF));							//写高位
		i2c_WaitAck();
		i2c_SendByte((u8)(reg_dat & 0xFF));											//写低位
		i2c_WaitAck();
		i2c_Stop();
}

void EvmReadData(u8 reg_add, u16 *Read, u8 num)
{
		unsigned char i;
		
		i2c_Start();
		i2c_SendByte(EVM_SLAVE_ADDRESS);
		i2c_WaitAck();
		i2c_SendByte(reg_add);
		i2c_WaitAck();
		
		i2c_Start();
		i2c_SendByte(EVM_SLAVE_ADDRESS + 1);
		i2c_WaitAck();
		
		for(i=0; i < num; i++)
		{
				*Read = i2c_ReadByte(1);														//读高位
				*Read = (*Read) << 8;
				*Read += i2c_ReadByte(0);														//读低位
				Read++;
		}
		
		i2c_Stop();
}

uint8_t EvmInit(void)
{
		uint16_t DevID, i, buf[4], temp[4];
		
		i2c_GPIO_Config();	
	
		EvmReadData(LDC13xx16xx_CMD_DEVID, &DevID, 1);
		if(0x3054 != DevID){ return ERROR; }

		EvmWriteReg(LDC13xx16xx_CMD_REF_COUNT_CH0, 0x04D6);					//0x0000-0x0004:保留位
		EvmWriteReg(LDC13xx16xx_CMD_REF_COUNT_CH1, 0x04D6);					//0x0005-0xFFFF:转换时间,Conversion Time(T = CH_COUTN * 16 / f)
		EvmWriteReg(LDC13xx16xx_CMD_REF_COUNT_CH2, 0x04D6);					//时间 = 计数值/频率
		EvmWriteReg(LDC13xx16xx_CMD_REF_COUNT_CH3, 0x04D6);
		EvmWriteReg(LDC13xx16xx_CMD_OFFSET_CH0, 0x2FF0);					
		EvmWriteReg(LDC13xx16xx_CMD_OFFSET_CH1, 0x2FF0);						
		EvmWriteReg(LDC13xx16xx_CMD_OFFSET_CH2, 0x2FF0);
		EvmWriteReg(LDC13xx16xx_CMD_OFFSET_CH3, 0x2FF0);
		EvmWriteReg(LDC13xx16xx_CMD_SETTLE_COUNT_CH0, 0x000A);
		EvmWriteReg(LDC13xx16xx_CMD_SETTLE_COUNT_CH1, 0x000A);
		EvmWriteReg(LDC13xx16xx_CMD_SETTLE_COUNT_CH2, 0x000A);
		EvmWriteReg(LDC13xx16xx_CMD_SETTLE_COUNT_CH3, 0x000A);
		EvmWriteReg(LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH0, 0x1005);		//分频系数
		EvmWriteReg(LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH1, 0x1005);
		EvmWriteReg(LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH2, 0x1005);
		EvmWriteReg(LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH3, 0x1005);
//		EvmWriteReg(LDC13xx16xx_CMD_STATUS, 0x0001);								
//		EvmWriteReg(LDC13xx16xx_CMD_ERROR_CONFIG, 0x0000);  
		EvmWriteReg(LDC13xx16xx_CMD_CONFIG, 0x1601);							
		EvmWriteReg(LDC13xx16xx_CMD_MUX_CONFIG, 0xC20C);						
		EvmWriteReg(LDC13xx16xx_CMD_RESET_DEVICE, 0x0600);		
//		EvmWriteReg(LDC13xx16xx_CMD_SYSTEM_CLOCK_CONFIG, 0x0200);		
		EvmWriteReg(LDC13xx16xx_CMD_DRIVE_CURRENT_CH0, 0x6000);
		EvmWriteReg(LDC13xx16xx_CMD_DRIVE_CURRENT_CH1, 0x6000);
		EvmWriteReg(LDC13xx16xx_CMD_DRIVE_CURRENT_CH2, 0x6000);
		EvmWriteReg(LDC13xx16xx_CMD_DRIVE_CURRENT_CH3, 0x6000);
		
		EvmGetData(buf);
		for(i = 0; i < 30; i++)
		{
				EvmGetData(temp);
				buf[0] = (buf[0] + temp[0]) / 2;
				buf[1] = (buf[1] + temp[1]) / 2;
				buf[2] = (buf[2] + temp[2]) / 2;
				buf[3] = (buf[3] + temp[3]) / 2;
		}
		
		CH0 = buf[0];
		CH1 = buf[1];
		CH2 = buf[2];
		CH3 = buf[3];
			
		return SUCCE;
}

void EvmGetData(uint16_t *rxbuf)
{
// 		uint16_t Status;
// 	
// 		while(!(Status & 0x000F))
// 		{
// 				EvmReadData(LDC13xx16xx_CMD_STATUS, &Status, 1);
// 		}
		
		EvmReadData(LDC13xx16xx_CMD_DATA_MSB_CH0, rxbuf++, 1);
		//DelayMs(1);
		EvmReadData(LDC13xx16xx_CMD_DATA_MSB_CH1, rxbuf++, 1);
		//DelayMs(1);
		EvmReadData(LDC13xx16xx_CMD_DATA_MSB_CH2, rxbuf++, 1);
		//DelayMs(1);
		EvmReadData(LDC13xx16xx_CMD_DATA_MSB_CH3, rxbuf++, 1);
		//DelayMs(1);
}

		uint16_t buf[4];		
int8_t EvmGetPosition(void)
{
		static int8_t position = 0;
	  	

		uint16_t data = 0;
		EvmGetData(buf);
	  //硬币检测
	  if((CH0 - buf[0] > coinDet) || (CH0 - buf[0] < -1*coinDet) || 
			(CH1 - buf[1] > coinDet) || (CH1 - buf[1] < -1*coinDet) ||
			(CH2 - buf[2] > coinDet) || (CH2 - buf[2] < -1*coinDet) || 
		  (CH3 - buf[3] > coinDet) || (CH3 - buf[3] < -1*coinDet))
		{
			  BEEP = !BEEP;
			  DelayMs(10);
			 
			  return position;//返回上一次的动作
    }
		else
		{
			  BEEP = BEEP;
    }
	
		if(CH0 - buf[0] > defaultMax){ data |= 0x0001; }
		else{ data &= 0xFFFE; }
		if(CH1 - buf[1] > defaultMax){ data |= 0x0002; }
		else { data &= 0xFFFD; }
		if(CH2 - buf[2] > defaultMax){ data |= 0x0004; }
		else { data &= 0xFFFB; }
		if(CH3 - buf[3] > defaultMax){ data |= 0x0008; }
		else { data &= 0xFFF7; }
	
		switch(data)
		{	
				case 0x0000: 
				{
						if(3 == position) { position = 4; }
						else if(-3 == position) { position = -4; }
						else if(1 == position){position = 0;}
						else if(-1 == position) {position = 0;}
						break;	
				}
				case 0x0001: position = -3; break;
				case 0x0002: position = -1; break;
				case 0x0003: position = -2; break;
				case 0x0004: position = 1; break;
				case 0x0008: position = 3; break;
				case 0x000C: position = 2; break;
				case 0x000F: position = 0; break;
				default : break;
		}
		return position;
}


