#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR ((F_CPU / (16UL * BAUD)) - 1)

/* ... Register Definitions ... */

// --- FUNCTION DEFINITIONS (Must be above main) ---

void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << 3); 
    UCSR0C = (3 << 1); 
}

void uart_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << 5)));
    UDR0 = data;
}

void uart_print(const char* str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

void delay_1000ms() {
    TCNT1 = 0;
    TCCR1B = (1 << 2) | (1 << 0);
    while (TCNT1 < 15625);  
    TCCR1B = 0;
}

// --- MAIN (At the bottom) ---

int main(void) {
    uart_init(MYUBRR);

    while (1) {
        uart_print("Hello from UART\r\n");
        delay_1000ms();
    }
    return 0;
}
