#include "config.h"
#include "uart.h"
#include "lcd.h"

void main(void) {
    int get_value;
    TRISC = 0x00;
    
    Initialize_UART();        

    UART_send_string("UART Module Initialised and active\r\n");
    
    I2C_Master_Init();
    LCD_Init(0x4E); // Initialize LCD module with I2C address = 0x4E
    
    LCD_Set_Cursor(1, 1);
    LCD_Write_String("UART initialised");
   
    while(1) {
      get_value = UART_get_char();
      if (get_value == '1') {
          RC1=1; //Turn on LED
          LCD_Clear();
          LCD_Set_Cursor(1, 1);
          LCD_Write_String("RED LED -> ON");
          UART_send_string("RED LED -> ON\r\n");
      }

      if (get_value == '0') {
          RC1=0; //Turn off LED
          LCD_Clear();
          LCD_Set_Cursor(1, 1);
          LCD_Write_String("RED LED -> OFF");
          UART_send_string("RED LED -> OFF\r\n");
      }
    }
}

