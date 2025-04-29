#include "esp8266.h"
#include "tim.h"
#include "stdlib.h"
#include "oled.h"
#include "gpio.h"


bool device_connect = false;


static  void handle_wifi_data(void);
bool start_esp8266(void)
{ 
	
			HAL_UART_Transmit(&huart3,(uint8_t*)(AT_MODE2),13,0xffff);
			HAL_Delay(1000);
      HAL_UART_Transmit(&huart3,(uint8_t*)(AT_SET),38,0xffff);
				HAL_Delay(1000);
			
			HAL_UART_Transmit(&huart3,(uint8_t*)(AT_RST),8,0xffff);
			HAL_Delay(4000);
			
			HAL_UART_Transmit(&huart3,(uint8_t*)(AT_CIPMUX),13,0xffff);
			HAL_Delay(1000);
			
		  HAL_UART_Transmit(&huart3,(uint8_t*)(AT_CIPSERVER),21,0xffff);
			HAL_Delay(1000);
			
				__HAL_UART_ENABLE_IT(&huart3,UART_IT_IDLE);  
			HAL_UART_Receive_DMA(&huart3,uart3_rx,1000);   
			
			 return true;
			 
}

void handle_esp8266(void)
{
	static int i=0;
//	char *send = "hello\r\n";
	char *wifi_connect = "0,CONNECT";

	char *lay1on = "\r\n+IPD,0,6:lay1on";
	char *lay1off = "\r\n+IPD,0,7:lay1off";	
	
	char *lay2on = "\r\n+IPD,0,6:lay2on";
	char *lay2off = "\r\n+IPD,0,7:lay2off";		
	
	char *fanon = "\r\n+IPD,0,5:fanon";
	char *fanoff = "\r\n+IPD,0,6:fanoff";
	
	
//	char *layon = "\r\n+IPD,0,5:layon";
//	char *timeset2 = "\r\n+IPD,0,7:water01";  //\r\n+IPD,0,5:water02这里的02表示阈值
//	char *timeset3 = "\r\n+IPD,0,7:water02";  //\r\n+IPD,0,5:water02这里的02表示阈值
//	char *timeset4 = "\r\n+IPD,0,7:water03";  //\r\n+IPD,0,5:water02这里的02表示阈值
//	
//	
//	char *tmp1 = "\r\n+IPD,0,5:tmp10";  //\r\n+IPD,0,5:water02这里的02表示阈值
//	char *tmp2 = "\r\n+IPD,0,5:tmp20";  //\r\n+IPD,0,5:water02这里的02表示阈值
//	char *tmp3 = "\r\n+IPD,0,5:tmp40";  //\r\n+IPD,0,5:water02这里的02表示阈值
//		char *tmp4 = "\r\n+IPD,0,5:tmp40";  //\r\n+IPD,0,5:water02这里的02表示阈值
//	char *tmp5 = "\r\n+IPD,0,5:tmp50";  //\r\n+IPD,0,5:water02这里的02表示阈值
//	char *tmp6 = "\r\n+IPD,0,5:tmp60";  //\r\n+IPD,0,5:water02这里的02表示阈值
//		char *tmp7 = "\r\n+IPD,0,5:tmp70";  //\r\n+IPD,0,5:water02这里的02表示阈值
//	char *tmp8 = "\r\n+IPD,0,5:tmp80";  //\r\n+IPD,0,5:water02这里的02表示阈值
//		char *tmp9 = "\r\n+IPD,0,5:tmp90";  //\r\n+IPD,0,5:water02这里的02表示阈值
	
	
	
//	char *timeset3 = "\r\n+IPD,0,5:tmp";    //\r\n+IPD,0,5:tmp03，这里的03表示阈值

	if(rx3_end_flag)
	{
			rx3_end_flag = false;
		  if(memcmp(uart3_rx,wifi_connect,9)==0)  //wifi已连接
			{
						//printf("yes\r\n");
						device_connect=true;
			}
			
		  if(memcmp(uart3_rx,lay1on,17)==0)  //水深的阈值
			{
						HAL_GPIO_WritePin(LAY1_GPIO_Port,LAY1_Pin,GPIO_PIN_RESET);
			}
			
		  if(memcmp(uart3_rx,lay1off,18)==0)  //水深的阈值
			{
						HAL_GPIO_WritePin(LAY1_GPIO_Port,LAY1_Pin,GPIO_PIN_SET);
			}
			
		  if(memcmp(uart3_rx,lay2on,17)==0)  //水深的阈值
			{
						HAL_GPIO_WritePin(LAY2_GPIO_Port,LAY2_Pin,GPIO_PIN_RESET);
			}
			
		  if(memcmp(uart3_rx,lay2off,18)==0)  //水深的阈值
			{
						HAL_GPIO_WritePin(LAY2_GPIO_Port,LAY2_Pin,GPIO_PIN_SET);
			}
			
		  if(memcmp(uart3_rx,fanon,16)==0)  //水深的阈值
			{
					HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
					__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_3,300);
			}
			
		  if(memcmp(uart3_rx,fanoff,17)==0)  //水深的阈值
			{
					 HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_3);
			}
			
			
//			
//		  if(memcmp(uart1_rx,timeset3,18)==0)  //温度的阈值
//			{
//						water_ban= 2;
//			}
//			
//			if(memcmp(uart1_rx,timeset4,18)==0)  //温度的阈值
//			{
//						water_ban= 3;
//			}
//			
//			
//			if(memcmp(uart1_rx,tmp1,16)==0)  //温度的阈值
//			{
//						temp_ban= 10;
//			}
//			
//						if(memcmp(uart1_rx,tmp2,16)==0)  //温度的阈值
//			{
//						temp_ban= 20;
//			}
//			
//						if(memcmp(uart1_rx,tmp3,16)==0)  //温度的阈值
//			{
//						temp_ban= 30;
//			}
//			
//						if(memcmp(uart1_rx,tmp4,16)==0)  //温度的阈值
//			{
//						temp_ban= 40;
//			}
//			
//						if(memcmp(uart1_rx,tmp5,16)==0)  //温度的阈值
//			{
//						temp_ban= 50;
//			}
//			
//									if(memcmp(uart1_rx,tmp6,16)==0)  //温度的阈值
//			{
//						temp_ban= 60;
//			}
//			
//			
//									if(memcmp(uart1_rx,tmp7,16)==0)  //温度的阈值
//			{
//						temp_ban= 70;
//			}
//			
//			
//									if(memcmp(uart1_rx,tmp8,16)==0)  //温度的阈值
//			{
//						temp_ban= 80;
//			}

//												if(memcmp(uart1_rx,tmp9,16)==0)  //温度的阈值
//			{
//						temp_ban= 90;
//			}
//			
			rx3_count=0;
			memset(uart3_rx,0,1000);
			HAL_UART_Receive_DMA(&huart3,uart3_rx,1000);  //需要重新启动DMA
	} 
				
}

void send_wifi(char *data,int size)
{
	  int send_size=0;
	  if(size<10)
		{
			 send_size=1; 
		}
		
		if(size>10&&size<100)
		{
				send_size=2;
		}
		
			
	  if(device_connect)
		{
			char send_data[50]={0};
			char send_data1[50]={0};
			sprintf(send_data,"AT+CIPSEND=0,%d\r\n",size);
			HAL_UART_Transmit(&huart3,(uint8_t*)(send_data),15+send_size,0xffff);

			HAL_Delay(100);
			HAL_UART_Transmit(&huart3,(uint8_t*)data,size,0xffff);
		}


}


