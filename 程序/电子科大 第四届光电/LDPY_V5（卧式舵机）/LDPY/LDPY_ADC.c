#include "LDPY_ADC.h"
	
/*************************************************************************
*					零		度		偏		移                           
*
*  函数名称:LDPY_ADC0_Init
*  功能说明:ADC0初始化
*  参数说明:
*  函数返回:
*  修改时间:2014-05-09
*  备    注: 
*************************************************************************/
void LDPY_ADC0_Init(void)
{
	PORTB->PCR[3]=PORT_PCR_MUX(0);		//配置IO口为模拟
	PORTB->PCR[0]=PORT_PCR_MUX(0);		//配置IO口为模拟
	
	SIM->SCGC6|=SIM_SCGC6_ADC0_MASK;		//开启ADC0模块时钟
	
	ADC0->CFG1=0x65;					//功耗，时钟分频，采样时间，转换模式，时钟源
	ADC0->CFG2=0X00;
	
	ADC0->SC2=0x00;					//触发源，比较，DMA，参考电压
	
}

/*************************************************************************
*					零		度		偏		移                           
*
*  函数名称:LDPY_ADC1_Init
*  功能说明:ADC1初始化
*  参数说明:
*  函数返回:
*  修改时间:2014-05-09
*  备    注: 
*************************************************************************/	
void LDPY_ADC1_Init(void)
{
	PORTB->PCR[10]=PORT_PCR_MUX(0);		//配置IO口为模拟
	PORTB->PCR[6]=PORT_PCR_MUX(0);		//配置IO口为模拟
	PORTE->PCR[1]=PORT_PCR_MUX(0);		//配置IO口为模拟
	
	SIM->SCGC3|=SIM_SCGC3_ADC1_MASK;		//开启ADC0模块时钟
	
	ADC1->CFG1=0x65;					//功耗，时钟分频，采样时间，转换模式，时钟源
	ADC1->CFG2=0X00;
	
	ADC1->SC2=0x00;					//触发源，比较，DMA，参考电压
	
}

/*************************************************************************
*					零		度		偏		移                          
*
*  函数名称:LDPY_ADC0_GetValue
*  功能说明:ADC0采集CCD电压
*  参数说明:
*  函数返回:
*  修改时间:2014-05-09
*  备    注: 
*************************************************************************/
uint16_t LDPY_ADC0_GetValue(uint8_t Channel)
{
	switch(Channel)
	{
		case 3: 	ADC0->SC1[0]=0x0D;	//启动ADC，x代表通道
				break;
		case 4: 	ADC0->SC1[0]=0x08;
				break;
		default:
				break;
	}
	
	while ((ADC0->SC1[0]&0x80)==0);		//检查COCO是否转换完成
	
	return(ADC0->R[0]);         			//读取AD值
	

}
/*************************************************************************
*					零		度		偏		移                            
*
*  函数名称:LDPY_ADC1_GetValue
*  功能说明:ADC1采集CCD电压
*  参数说明:
*  函数返回:
*  修改时间:2014-05-09
*  备    注: 
*************************************************************************/ 	
uint16_t LDPY_ADC1_GetValue(uint8_t Channel)
{
	switch(Channel)
	{
		case 1: 	ADC1->SC1[0]=0x0E;	//启动ADC，F代表通道
				break;
		case 2: 	ADC1->SC1[0]=0x0C;
				break;
		default:
				break;
	}
	
	while ((ADC1->SC1[0]&0x80)==0);		//检查COCO是否转换完成
	
	return(ADC1->R[0]);         			//读取AD值
}

/*************************************************************************
*					零		度		偏		移                             
*
*  函数名称:LDPY_ADC1_GetValue
*  功能说明:ADC1采集CCD电压
*  参数说明:
*  函数返回:
*  修改时间:2014-05-09
*  备    注: 
*************************************************************************/ 	
uint16_t LDPY_ADC1_ENC(void)
{

	ADC1->SC1[0]=0x05;	//启动ADC，0x05代表通道

	while ((ADC1->SC1[0]&0x80)==0);		//检查COCO是否转换完成,此处可能与CCD采集冲突

	return(ADC1->R[0]);         			//读取AD值
}

/*------------------------end of LDPY_ADC.c-----------------------------*/

	
	
	
	
	
	
