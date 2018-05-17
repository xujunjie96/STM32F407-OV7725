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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(256000);		//��ʼ�����ڲ�����Ϊ115200
	usart2_init(42,115200);		//��ʼ������2������Ϊ115200
	MCO1_Init();
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ��  
 	KEY_Init();					//������ʼ�� 
 	POINT_COLOR=RED;//��������Ϊ��ɫ 	 
	while(OV7725_Init())//��ʼ��OV7725
	{
		LCD_ShowString(30,130,240,16,16,"OV7725 ERR");
		delay_ms(200);
	    LCD_Fill(30,130,239,170,WHITE);
		delay_ms(200);
	}
	OV7725_Window_QVGA_Set(0,0,160,120);//OV7725�����������
	//OV7725_Window_VGA_Set(160,120,320,240);
	AutoSet_Enable(0,0,0);//�Զ��ع⡢�Զ���ƽ�⡢�Զ����濪��
	Exposure_Set(0x0110);//�ֶ��ع�ֵ
	Bright_Set(0x00);//����
	LCD_ShowString(30,130,200,16,16,"OV7725 OK"); 
	delay_ms(500);	
	My_DCMI_Init();			//DCMI����
//DCMI_DMA_Init((u32)img,160*120,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Enable);//DCMI DMA���� 
	DCMI_DMA_Init((u32)&LCD->LCD_RAM,1,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Disable);//DCMI DMA����  
	DCMI_Start(); 		//��������
	LCD_Scan_Dir(L2R_U2D);		   //���ϵ���,������	
	LCD_Set_Window(0,0,160,120); //LCD������ʾ���ڣ����OV7725����ֱ��ʸı��ˣ�����ҲҪ�ñ�
	LCD_SetCursor(0,0);   
	LCD_WriteRAM_Prepare();		//��ʼд��GRAM
	
	

	
	DMA_Cmd(DMA2_Stream1, ENABLE);//����DMA2,Stream1 
	DCMI_CaptureCmd(ENABLE);//DCMI����ʹ�� 
 	while(1)
	{	

	}
}




void MCO1_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;        
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ��GPIOA��ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //ѡ��ܽź�  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// ���ùܽŵ��ٶ�Ϊ100M  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //���ùܽ�λ���ù���  
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//���ùܽ�λ�������  
  GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ���ܽ�  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_MCO);//��GPIOA_Pin_9��MCO����  
  RCC_MCO1Config(RCC_MCO1Source_HSE,RCC_MCO2Div_1);//����GPIOA_Pin_8����ⲿ���پ���HSE��Ƶ��  
	//RCC_MCO1Config(RCC_MCO1Source_HSE,RCC_MCO1Div_2);//����GPIOA_Pin_8����ⲿ���پ���HSE��Ƶ�� 

}


void DMA2_Stream1_IRQHandler(void)
{   u32 a,b;     
	if(DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1)==SET)//DMA2_Steam1,������ɱ�־
	{  
		 DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_TCIF1);//�����������ж�
		finish_fiag=1;
//		    DCMI_Stop();
//	
//      uart_putbuff(USART1, cmdf, sizeof(cmdf));    //�ȷ�������
//      for(a=0;a<120;a++)
//		{
//			for(b=0;b<160;b++)
//			{
//////      uart_putbuff(USART1, img[a], 1); //�ٷ���ͼ��
////			printf("%c",img[a][b]>>24);
////				printf("%c",img[a][b]>>16);
//				printf("%c",img[a][b]>>8);
//				printf("%c",img[a][b]);
//			}
//		}
//      uart_putbuff(USART1, cmdr, sizeof(cmdr));    //�ȷ�������
//		LED0=!LED0;
//			datanum++;
//		DCMI_Start();	
	}    											 
} 

























