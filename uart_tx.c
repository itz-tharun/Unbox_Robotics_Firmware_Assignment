/* Register Addresses - UART */
#define UBRR0H  (*(volatile unsigned char*)(0xC5))
#define UBRR0L  (*(volatile unsigned char*)(0xC4))
#define UCSR0A  (*(volatile unsigned char*)(0xC0))
#define UCSR0B  (*(volatile unsigned char*)(0xC1))
#define UCSR0C  (*(volatile unsigned char*)(0xC2))
#define UDR0    (*(volatile unsigned char*)(0xC6))

/* Register Addresses - Timer1 (for 1000ms delay) */
#define TCCR1B  (*(volatile unsigned char*)(0x81))
#define TCNT1   (*(volatile unsigned short*)(0x84)) // 16-bit access

/* Bit Definitions */
#define TXEN0   3    // Transmitter Enable
#define UDRE0   5    // Data Register Empty
#define CS12    2    // Timer1 Prescaler bit 2
#define CS10    0    // Timer1 Prescaler bit 0

void uart_init(unsigned int ubrr) {
    /* 1. Set Baud Rate: 103 for 9600 baud at 16MHz */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    /* 2. Enable Transmitter */
    UCSR0B = (1 << TXEN0);

    /* 3. Set 8-N-1 Configuration: 8 data bits, no parity, 1 stop bit */
    // ASYNCHRONOUS mode, No Parity (00), 1 Stop Bit (0), 8-bit size (011)
    UCSR0C = (3 << 1); 
}

void uart_transmit(unsigned char data) {
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_print(const char* str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

void delay_1000ms() {
    TCNT1 = 0;              // Reset counter
    TCCR1B = (1 << CS12) | (1 << CS10); // Start Timer1 with 1024 prescaler
    
    /* 16MHz / 1024 = 15,625 ticks per second. 
       For 1000ms, wait for 15,625 ticks. */
    while (TCNT1 < 15625);  
    
    TCCR1B = 0;             // Stop Timer1
}

int main(void) {
    /* Initialize UART at 9600 Baud */
    uart_init(103);

    while (1) {
        uart_print("Hello from UART\r\n");
        delay_1000ms(); // Periodical 1000ms interval
    }
}
