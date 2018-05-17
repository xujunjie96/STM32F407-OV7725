#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "usart2.h"  
#include "timer.h" 
#include "ov7725.h" 
#include "dcmi.h"  
void MCO1_Init(void);
char finish_fiag=0;
u16 img[120][160]={0};
u8 key;
int main(void)
{ 
	u32 i ;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(256000);		//初始化串口波特率为115200
	usart2_init(42,115200);		//初始化串口2波特率为115200
	MCO1_Init();
	LED_Init();					//初始化LED 
 	LCD_Init();					//LCD初始化  
 	KEY_Init();					//按键初始化 
 	POINT_COLOR=RED;//设置字体为红色 	 
	while(OV7725_Init())//初始化OV7725
	{
		LCD_ShowString(30,130,240,16,16,"OV7725 ERR");
		delay_ms(200);
	    LCD_Fill(30,130,239,170,WHITE);
		delay_ms(200);
	}
	OV7725_Window_QVGA_Set(0,0,160,120);//OV7725设置输出窗口
	//OV7725_Window_VGA_Set(160,120,320,240);
	AutoSet_Enable(0,0,0);//自动曝光、自动白平衡、自动增益开关
	Exposure_Set(0x0110);//手动曝光值
	Bright_Set(0x00);//亮度
	LCD_ShowString(30,130,200,16,16,"OV7725 OK"); 
	delay_ms(500);	
	My_DCMI_Init();			//DCMI配置
//DCMI_DMA_Init((u32)img,160*120,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Enable);//DCMI DMA配置 
	DCMI_DMA_Init((u32)&LCD->LCD_RAM,1,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Disable);//DCMI DMA配置  
	DCMI_Start(); 		//启动传输
	LCD_Scan_Dir(L2R_U2D);		   //从上到下,从左到右	
	LCD_Set_Window(0,0,160,120); //LCD设置显示窗口，如果OV7725输出分辨率改变了，这里也要该表
	LCD_SetCursor(0,0);   
	LCD_WriteRAM_Prepare();		//开始写入GRAM
	
	

	
	DMA_Cmd(DMA2_Stream1, ENABLE);//开启DMA2,Stream1 
	DCMI_CaptureCmd(ENABLE);//DCMI捕获使能 
 	while(1)
	{	

	}
}




void MCO1_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;        
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//使能GPIOA的时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //选择管脚号  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// 设置管脚的速度为100M  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //设置管脚位复用功能  
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//设置管脚位推完输出  
  GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化管脚  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_MCO);//打开GPIOA_Pin_9的MCO功能  
  RCC_MCO1Config(RCC_MCO1Source_HSE,RCC_MCO2Div_1);//设置GPIOA_Pin_8输出外部高速晶振HSE的频率  
	//RCC_MCO1Config(RCC_MCO1Source_HSE,RCC_MCO1Div_2);//设置GPIOA_Pin_8输出外部高速晶振HSE的频率 

}


void DMA2_Stream1_IRQHandler(void)
{   u32 a,b;     
	if(DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1)==SET)//DMA2_Steam1,传输完成标志
	{  
		 DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_TCIF1);//清除传输完成中断
		finish_fiag=1;
//		    DCMI_Stop();
//	
//      uart_putbuff(USART1, cmdf, sizeof(cmdf));    //先发送命令
//      for(a=0;a<120;a++)
//		{
//			for(b=0;b<160;b++)
//			{
//////      uart_putbuff(USART1, img[a], 1); //再发送图像
////			printf("%c",img[a][b]>>24);
////				printf("%c",img[a][b]>>16);
//				printf("%c",img[a][b]>>8);
//				printf("%c",img[a][b]);
//			}
//		}
//      uart_putbuff(USART1, cmdr, sizeof(cmdr));    //先发送命令
//		LED0=!LED0;
//			datanum++;
//		DCMI_Start();	
	}    											 
} 

























