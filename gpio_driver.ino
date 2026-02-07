/* --- CONTROL PANEL --- */
#define OUTPUT_PIN    4   // Change this to 4 for Pin 12, 0 for Pin 8, etc.
#define OUTPUT_MASK (1 << OUTPUT_PIN) // Reduces the number of times (1 << OUTPUT_PIN) operation is done to one time.
/* --- REGISTER ADDRESSES --- */
#define MY_DDRB    ((volatile unsigned char*)0x24)
#define MY_PORTB   ((volatile unsigned char*)0x25)

// Timer 1 (Clock) Registers
#define TCCR1B_REG ((volatile unsigned char*)0x81)
#define TCNT1_REG  ((volatile unsigned int*)0x84)

int main(void) {
    // Now the code uses 'OUTPUT_MASK' instead of (1 << OUTPUT_PIN) or (1 << 4)
    *MY_DDRB |= OUTPUT_MASK; 

    while (1) {
        *MY_PORTB ^= OUTPUT_MASK; 

        // Reset and Start Timer
        *TCNT1_REG = 0;
        *TCCR1B_REG = (1 << 0) | (1 << 2); // Start Prescaler 1024

        // Wait for 500ms
        while (*TCNT1_REG < 7812) { }

        // Stop Timer
        *TCCR1B_REG = 0;
    }
}
