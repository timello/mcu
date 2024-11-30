#include "config.h"

#define Baud_rate 9600

void Initialize_UART(void) {
    TRISC6 = 0; // TX Pin set as output
    TRISC7 = 1; // RX Pin set as input
    
    /* Initialise SPBRG register for required 
    baud rate and set BRGH for fast baud_rate */
    SPBRG = ((_XTAL_FREQ/16)/Baud_rate) - 1;
    BRGH  = 1;  // for high baud_rate
    SYNC  = 0;  // Asynchronous
    SPEN  = 1;  // Enable serial port pins
    TXEN  = 1;  // enable transmission
    CREN  = 1;  // enable reception
    TX9   = 0;  // 8-bit reception selected
    RX9   = 0;  // 8-bit reception mode selected
}

void UART_send_char(char bt) { 
    while(!TXIF); // Hold the program till TX buffer is free
    TXREG = bt;   // Load the transmitter buffer with the received value
}

char UART_get_char() {
    if(OERR) {
        CREN = 0; // If error -> Reset 
        CREN = 1; // If error -> Reset 
    }
    
    while(!RCIF); // Hold the program till RX buffer is free
    return RCREG; // Receive the value and send it to main function
}

void UART_send_string(char* st_pt) {
    while(*st_pt) // If there is a char
        UART_send_char(*st_pt++); // Process it as a byte data
}