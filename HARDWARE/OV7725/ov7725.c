#include "sys.h"
#include "ov7725.h"  
#include "delay.h"
#include "usart.h"			 
#include "sccb.h"	
#include "dcmi.h" 

/* OV7725�Ĵ����궨�� */
#define GAIN      0x00
#define BLUE      0x01
#define RED       0x02
#define RED       0x02
#define GREEN     0x03
#define BAVG      0x05
#define GAVG      0x06
#define RAVG      0x07
#define AECH      0x08
#define COM2      0x09
#define PID       0x0A
#define VER       0x0B
#define COM3      0x0C
#define COM4      0x0D
#define COM5      0x0E
#define COM6      0x0F
#define AEC       0x10
#define CLKRC     0x11
#define COM7      0x12
#define COM8      0x13
#define COM9      0x14
#define COM10     0x15
#define REG16     0x16
#define HSTART    0x17
#define HSIZE     0x18
#define VSTRT     0x19
#define VSIZE     0x1A
#define PSHFT     0x1B
#define MIDH      0x1C
#define MIDL      0x1D
#define LAEC      0x1F
#define COM11     0x20
#define BDBase    0x22
#define BDMStep   0x23
#define AEW       0x24
#define AEB       0x25
#define VPT       0x26
#define REG28     0x28
#define HOutSize  0x29
#define EXHCH     0x2A
#define EXHCL     0x2B
#define VOutSize  0x2C
#define ADVFL     0x2D
#define ADVFH     0x2E
#define YAVE      0x2F
#define LumHTh    0x30
#define LumLTh    0x31
#define HREF      0x32
#define DM_LNL    0x33
#define DM_LNH    0x34
#define ADoff_B   0x35
#define ADoff_R   0x36
#define ADoff_Gb  0x37
#define ADoff_Gr  0x38
#define Off_B     0x39
#define Off_R     0x3A
#define Off_Gb    0x3B
#define Off_Gr    0x3C
#define COM12     0x3D
#define COM13     0x3E
#define COM14     0x3F
#define COM16     0x41
#define TGT_B     0x42
#define TGT_R     0x43
#define TGT_Gb    0x44
#define TGT_Gr    0x45
#define LC_CTR    0x46
#define LC_XC     0x47
#define LC_YC     0x48
#define LC_COEF   0x49
#define LC_RADI   0x4A
#define LC_COEFB  0x4B 
#define LC_COEFR  0x4C
#define FixGain   0x4D
#define AREF1     0x4F
#define AREF6     0x54
#define UFix      0x60
#define VFix      0x61
#define AWBb_blk  0x62
#define AWB_Ctrl0 0x63
#define DSP_Ctrl1 0x64
#define DSP_Ctrl2 0x65
#define DSP_Ctrl3 0x66
#define DSP_Ctrl4 0x67
#define AWB_bias  0x68
#define AWBCtrl1  0x69
#define AWBCtrl2  0x6A
#define AWBCtrl3  0x6B
#define AWBCtrl4  0x6C
#define AWBCtrl5  0x6D
#define AWBCtrl6  0x6E
#define AWBCtrl7  0x6F
#define AWBCtrl8  0x70
#define AWBCtrl9  0x71
#define AWBCtrl10 0x72
#define AWBCtrl11 0x73
#define AWBCtrl12 0x74
#define AWBCtrl13 0x75
#define AWBCtrl14 0x76
#define AWBCtrl15 0x77
#define AWBCtrl16 0x78
#define AWBCtrl17 0x79
#define AWBCtrl18 0x7A
#define AWBCtrl19 0x7B
#define AWBCtrl20 0x7C
#define AWBCtrl21 0x7D 
#define GAM1      0x7E
#define GAM2      0x7F
#define GAM3      0x80
#define GAM4      0x81
#define GAM5      0x82
#define GAM6      0x83
#define GAM7      0x84
#define GAM8      0x85
#define GAM9      0x86
#define GAM10     0x87
#define GAM11     0x88
#define GAM12     0x89
#define GAM13     0x8A
#define GAM14     0x8B
#define GAM15     0x8C
#define SLOP      0x8D
#define DNSTh     0x8E
#define EDGE0     0x8F
#define EDGE1     0x90
#define DNSOff    0x91
#define EDGE2     0x92
#define EDGE3     0x93
#define MTX1      0x94
#define MTX2      0x95
#define MTX3      0x96
#define MTX4      0x97
#define MTX5      0x98
#define MTX6      0x99
#define MTX_Ctrl  0x9A
#define BRIGHT    0x9B
#define CNST      0x9C
#define UVADJ0    0x9E
#define UVADJ1    0x9F
#define SCAL0     0xA0
#define SCAL1     0xA1
#define SCAL2     0xA2
#define SDE       0xA6
#define USAT      0xA7
#define VSAT      0xA8
#define HUECOS    0xA9
#define HUESIN    0xAA
#define SIGN      0xAB
#define DSPAuto   0xAC
	


//��ʼ���Ĵ������м����Ӧ��ֵ
const u8 ov7725_init_reg_tbl[][2]= 
{   
	/*�����������*/
	{CLKRC,     0x00}, /*clock config*///�ȷ�Ƶ �ٱ�Ƶ
	{COM7,      0x46}, /*QVGA RGB565 */
	{HSTART,    0x3f},//��ʼλ�õ�����0x3f 252
	{HSIZE,     0x50},//ˮƽ�ߴ�0x50 320
	
	
	{VSTRT,     0x03},//��ʼλ�õ�����0x03 6
	{VSIZE,     0x78},//��ֱ�ߴ�0x78 240
	
	
	{HREF,      0x00},//ͼ����ʼ�ͳߴ����
//	{HOutSize,  0x50},//����ߴ�   0x28 160
//	{VOutSize,  0x78},//����ߴ�   0x3c 120
	{HOutSize,  0x28},//����ߴ�   0x28 160
	{VOutSize,  0x3c},//����ߴ�   0x3c 120
	{EXHCH,     0x00},
	{AEC,     0x00},//�ֶ��ع�
	{AECH,     0x00},

//	{GAIN,     0x00},
	/*DSP control*/
	{TGT_B,     0x7f},
	{FixGain,   0x09},
	{AWB_Ctrl0, 0xe0},
	{DSP_Ctrl1, 0xff},
	{DSP_Ctrl2, 0x20},
	{DSP_Ctrl3,	0x00},
	{DSP_Ctrl4, 0x00},

	/*AGC AEC AWB*/
	{COM8,		0xF0},
	{COM4,		0x41}, /*Pll AEC CONFIG*/
	{COM6,		0xc5},
	{COM9,		0x21},
	{BDBase,	0xFF},
	{BDMStep,	0x01},
	{AEW,		0x34},
	{AEB,		0x3c},
	{VPT,		0xa1},
	{EXHCL,		0x00},
	{AWBCtrl3,0xaa},
	{COM8,		0xff},
	{AWBCtrl1,0x5d},

	{EDGE1,		0x0a},
	{DNSOff,	0x01},
	{EDGE2,		0x01},
	{EDGE3,		0x01},

	{MTX1,		0x5f},
	{MTX2,		0x53},
	{MTX3,		0x11},
	{MTX4,		0x1a},
	{MTX5,		0x3d},
	{MTX6,		0x5a},
	{MTX_Ctrl,0x1e},

	{BRIGHT,	0x00},
	{CNST,		0x25},
	{USAT,		0x65},
	{VSAT,		0x65},
	{UVADJ0,	0x81},
	//{SDE,		  0x20},	//�ڰ�
	{SDE,		  0x06},	//��ɫ	����SDE����Ĵ���������ʵ������Ч��
	
    /*GAMMA config*/
	{GAM1,		0x0c},
	{GAM2,		0x16},
	{GAM3,		0x2a},
	{GAM4,		0x4e},
	{GAM5,		0x61},
	{GAM6,		0x6f},
	{GAM7,		0x7b},
	{GAM8,		0x86},
	{GAM9,		0x8e},
	{GAM10,		0x97},
	{GAM11,		0xa4},
	{GAM12,		0xaf},
	{GAM13,		0xc5},
	{GAM14,		0xd7},
	{GAM15,		0xe8},
	{SLOP,		0x20},

	{HUECOS,	0x80},
	{HUESIN,	0x80},
	{DSPAuto,	0xff},
	{DM_LNL,	0x00},
	{BDBase,	0x99},
	{BDMStep,	0x03},
	{LC_RADI,	0x00},
	{LC_COEF,	0x13},
	{LC_XC,		0x08},
	{LC_COEFB,0x14},
	{LC_COEFR,0x17},
	{LC_CTR,	0x05},
	
	{COM3,		0xE0},/*Horizontal mirror image*/
									//ע��datasheetĬ��0x10,���ı�YUVΪUVY��ʽ����������ͷ����оƬ����ģ��ʱ��
									//Ҫ��0X10�е�1���0��������YUV��ʽ��
	/*night mode auto frame rate control*/
	//{COM5,		0xf5},	 /*��ҹ�ӻ����£��Զ�����֡�ʣ���֤���նȻ�������*/
	{COM5,		0x31},	/*ҹ�ӻ���֡�ʲ���*/
	{COM8,		0xFF},//���� �ع⿪��
	{AEC,     0x10},//�ֶ��ع�ֵ
	{AECH,    0x01},
	
	
	{BRIGHT,	0x00},
	//֡������
	{REG28,    0x00},
	{DM_LNL,   0x00},
	{DM_LNH,   0x00},
}; 



		    			    
//��ʼ��OV7725
//����0:�ɹ�
//��������ֵ:�������
u8 OV7725_Init(void)
{
	u16 i=0;
	u16 reg=0;
	//����IO     	   
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
  //GPIOG9,15��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_15;//PG9,15�������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //�������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��
 
 	OV7725_PWDN=0;	//POWER ON
	delay_ms(10);
	OV7725_RST=0;	//��λOV7725
	delay_ms(10);
	OV7725_RST=1;	//������λ 
  SCCB_Init();        		//��ʼ��SCCB ��IO��	
 	SCCB_WR_Reg(0X12, 0x80);	//��λOV7725
	delay_ms(50); 
	reg=SCCB_RD_Reg(0X1c);	//��ȡ����ID �߰�λ
	reg<<=8;
	reg|=SCCB_RD_Reg(0X1d);	//��ȡ����ID �Ͱ�λ
	if(reg!=OV7725_MID)
	{
		printf("MID:%d\r\n",reg);
		return 1;
	}
	reg=SCCB_RD_Reg(0X0a);	//��ȡ����ID �߰�λ
	reg<<=8;
	reg|=SCCB_RD_Reg(0X0b);	//��ȡ����ID �Ͱ�λ
	if(reg!=OV7725_PID)
	{
		printf("HID:%d\r\n",reg);
		return 2;
	}   
 	//��ʼ�� OV7725,����QVGA�ֱ���(320*240)  
	for(i=0;i<sizeof(ov7725_init_reg_tbl)/sizeof(ov7725_init_reg_tbl[0]);i++)
	{								
	   	SCCB_WR_Reg(ov7725_init_reg_tbl[i][0],ov7725_init_reg_tbl[i][1]);
 	} 
	
	//OV7725_Light_Mode(0);
  	return 0x00; 	//ok
} 


void OV7725_Window_QVGA_Set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
	uint8_t reg_raw,cal_temp;

/*VGA RGB565 */
	SCCB_WR_Reg(COM7,0x46); 
	/***************HSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�HStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	reg_raw=SCCB_RD_Reg(HSTART);
	
	//sxΪ����ƫ�ƣ���8λ�洢��HSTART����2λ��HREF
	cal_temp = (reg_raw + (sx>>2));	
	SCCB_WR_Reg(HSTART,cal_temp ); 
	
	/***************HSIZE*********************/
	//ˮƽ��ȣ���8λ�洢��HSIZE����2λ�洢��HREF
	SCCB_WR_Reg(HSIZE,width>>2);//HSIZE������λ 
	
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�VStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	reg_raw=SCCB_RD_Reg(VSTRT);	
	//syΪ����ƫ�ƣ���8λ�洢��HSTART����1λ��HREF
	cal_temp = (reg_raw + (sy>>1));	
	
	SCCB_WR_Reg(VSTRT,cal_temp);
	
	/***************VSIZE*********************/
	//��ֱ�߶ȣ���8λ�洢��VSIZE����1λ�洢��HREF
	SCCB_WR_Reg(VSIZE,height>>1);//VSIZE����һλ
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ����	
	reg_raw=SCCB_RD_Reg(HREF);	
	//��ˮƽ��ȵĵ�2λ����ֱ�߶ȵĵ�1λ��ˮƽƫ�Ƶĵ�2λ����ֱƫ�Ƶĵ�1λ��������ӵ�HREF
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2)|((sx&0x03)<<4)|((sy&0x01)<<6));	
	
	SCCB_WR_Reg(HREF,cal_temp);
	
	/***************HOUTSIZIE /VOUTSIZE*********************/
	SCCB_WR_Reg(HOutSize,width>>2);
	SCCB_WR_Reg(VOutSize,height>>1);
	
	//��ȡ�Ĵ�����ԭ����	
	reg_raw=SCCB_RD_Reg(EXHCH);	
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2));	

	SCCB_WR_Reg(EXHCH,cal_temp);	
}


void OV7725_Window_VGA_Set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
	
	uint8_t reg_raw,cal_temp;

	/***********QVGA or VGA *************/
	/*VGA RGB565 */
	SCCB_WR_Reg(COM7,0x06); 

	/***************HSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�HStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	reg_raw=SCCB_RD_Reg(HSTART);
	
	//sxΪ����ƫ�ƣ���8λ�洢��HSTART����2λ��HREF
	cal_temp = (reg_raw + (sx>>2));	
	SCCB_WR_Reg(HSTART,cal_temp ); 
	
	/***************HSIZE*********************/
	//ˮƽ��ȣ���8λ�洢��HSIZE����2λ�洢��HREF
	SCCB_WR_Reg(HSIZE,width>>2);//HSIZE������λ 320 
	
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ���ݣ�VStart����ƫ��ֵ����ԭʼƫ��ֲ�Ļ����ϼ��ϴ���ƫ��	
	reg_raw=SCCB_RD_Reg(VSTRT);	
	//syΪ����ƫ�ƣ���8λ�洢��HSTART����1λ��HREF
	cal_temp = (reg_raw + (sy>>1));	
	
	SCCB_WR_Reg(VSTRT,cal_temp);
	
	/***************VSIZE*********************/
	//��ֱ�߶ȣ���8λ�洢��VSIZE����1λ�洢��HREF
	SCCB_WR_Reg(VSIZE,height>>1);//VSIZE����һλ 240
	
	/***************VSTART*********************/
	//��ȡ�Ĵ�����ԭ����	
	reg_raw=SCCB_RD_Reg(HREF);	
	//��ˮƽ��ȵĵ�2λ����ֱ�߶ȵĵ�1λ��ˮƽƫ�Ƶĵ�2λ����ֱƫ�Ƶĵ�1λ��������ӵ�HREF
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2)|((sx&0x03)<<4)|((sy&0x01)<<6));	
	
	SCCB_WR_Reg(VSTRT,cal_temp);
	
	/***************HOUTSIZIE /VOUTSIZE*********************/
	SCCB_WR_Reg(HOutSize,width>>2);
	SCCB_WR_Reg(VOutSize,height>>1);
	
	//��ȡ�Ĵ�����ԭ����	
	reg_raw=SCCB_RD_Reg(EXHCH);	
	
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2));	

	SCCB_WR_Reg(EXHCH,cal_temp);	
}


/*******************************************************/
//�Զ����ƿ���:�Զ��ع⣬�Զ���ƽ�⣬�Զ�����
void AutoSet_Enable(char AE,char AW,char AG)
{
	u8 Value=0xF0;
	
	AE=AE<<0;
	AW=AW<<1;
	AG=AG<<2;
	
	Value=Value|AE|AW|AG;
	SCCB_WR_Reg(COM8,Value);
}

//�ֶ��ع�ֵ
void Exposure_Set(u16 exp_value)
{
	u8 wxp_l,wxp_h;
	
	wxp_l=exp_value&0x00FF;
	wxp_h=(exp_value&0xFF00)>>8;
	SCCB_WR_Reg(AEC,wxp_l);
	SCCB_WR_Reg(AECH,wxp_h);
}

void Bright_Set(int bright)
{
	SCCB_WR_Reg(BRIGHT,bright);
}





