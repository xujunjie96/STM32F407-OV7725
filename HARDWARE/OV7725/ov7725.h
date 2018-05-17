#ifndef _OV7725_H
#define _OV7725_H
#include "sys.h"
#include "sccb.h"

#define OV7725_PWDN  	PGout(9)			//POWER DOWN控制信号 
#define OV7725_RST  	PGout(15)			//复位控制信号 
////////////////////////////////////////////////////////////////////////////////// 
#define OV7725_MID				0X7FA2    
#define OV7725_PID				0X7721
													  					 
#define OV7725_DATA   GPIO_ReadInputData(GPIOC,0x00FF) 					//数据输入端口
//GPIOC->IDR&0x00FF 
/////////////////////////////////////////
	    				 
u8   OV7725_Init(void);		  	   		 

void OV7725_Window_QVGA_Set(u16 sx,u16 sy,u16 width,u16 height);
void OV7725_Window_VGA_Set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);
void set_cif(void);
void AutoSet_Enable(char AE,char AW,char AG);
void Exposure_Set(u16 exp_value);
void Bright_Set(int bright);
#endif





















