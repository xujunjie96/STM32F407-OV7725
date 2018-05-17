# STM32F407-OV7725
1.stm32f407正点原子探索者开发板采集ov7725摄像头/直接显示在lcd或者存储在数组中/stm32提供时钟xclk给ov7725<br>
2.A8脚分频系统时钟给xclk<br>
3.<br>
```c
//DCMI_DMA_Init((u32)img,160*120,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Enable);//DCMI DMA配置 
```c
DCMI_DMA_Init((u32)&LCD->LCD_RAM,1,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Disable);//DCMI DMA配置  
上一句是图像存储在img数组中，下一句是直接显示在lcd上<br>
4.采集分辨率为120*160 考虑到stm32f4的ram大小<br>
