#include "usmart.h"
#include "usmart_str.h"
////////////////////////////�û�������///////////////////////////////////////////////
//������Ҫ�������õ��ĺ�����������ͷ�ļ�(�û��Լ�����) 
#include "delay.h"	
#include "ov7725.h"   
#include "dcmi.h"    
#include "sccb.h"  
#include "lcd.h"
//�������б���ʼ��(�û��Լ�����)
//�û�ֱ������������Ҫִ�еĺ�����������Ҵ�

struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//���ʹ���˶�д����
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif		   
	(void*)delay_ms,"void delay_ms(u16 nms)",
 	(void*)delay_us,"void delay_us(u32 nus)",
		
  	(void*)SCCB_WR_Reg,"u8 SCCB_WR_Reg(u8 reg,u8 data)",
  	(void*)SCCB_RD_Reg,"u8 SCCB_RD_Reg(u8 reg)",
		(void*)OV7725_Window_Set,"OV7725_Window_Set(u16 sx,u16 sy,u16 width,u16 height)",	
		(void*)LCD_Set_Window,"LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)",
		(void*)DCMI_CR_Set,"void DCMI_CR_Set(u8 pclk,u8 hsync,u8 vsync)",
//  	(void*)DCMI_Set_Window,"void DCMI_Set_Window(u16 sx,u16 sy,u16 width,u16 height)", 

//	(void*)OV7725_Auto_Exposure,"void OV7725_Auto_Exposure(u8 level)",
//  	(void*)OV7725_Light_Mode,"OV7725_Light_Mode(u8 mode)",
// 	(void*)OV7725_Color_Saturation,"void OV7725_Color_Saturation(u8 sat)",
//	(void*)OV7725_Brightness,"void OV7725_Brightness(u8 bright)",
// 	(void*)OV7725_Contrast,"void OV7725_Contrast(u8 contrast)",
// 	(void*)OV7725_Special_Effects,"void OV7725_Special_Effects(u8 eft)",
// 	(void*)OV7725_Color_Bar,"void OV7725_Color_Bar(u8 sw)",
// 	(void*)OV7725_Window_Set,"void OV7725_Window_Set(u16 sx,u16 sy,u16 width,u16 height)",
// 	(void*)OV7725_OutSize_Set,"u8 OV7725_OutSize_Set(u16 width,u16 height)",
// 	(void*)OV7725_ImageWin_Set,"u8 OV7725_ImageWin_Set(u16 offx,u16 offy,u16 width,u16 height)",
// 	(void*)OV7725_ImageSize_Set,"u8 OV7725_ImageSize_Set(u16 width,u16 height)",  
//		
// 	(void*)OV7725_JPEG_Mode,"void OV7725_JPEG_Mode(void)",  
// 	(void*)OV7725_RGB565_Mode,"void OV7725_RGB565_Mode(void)", 		  	    
};						  
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//�������ƹ�������ʼ��
//�õ������ܿغ���������
//�õ�����������
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//��������
	0,	  	//��������
	0,	 	//����ID
	1,		//������ʾ����,0,10����;1,16����
	0,		//��������.bitx:,0,����;1,�ַ���	    
	0,	  	//ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ��
	0,		//�����Ĳ���,��ҪPARM_LEN��0��ʼ��
};   


















