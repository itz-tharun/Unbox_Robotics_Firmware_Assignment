#define MY_DDRB   ((volatile unsigned char*)0x24)
#define MY_PORTB  ((volatile unsigned char*)0x25)

// Timer 1 Registers (Addresses from the extended I/O map)
#define TCCR1B_REG ((volatile unsigned char*)0x81)
#define TCNT1_REG  ((volatile unsigned int*)0x84)

int main(void) {
    *MY_DDRB |= (1 << 5); // Pin 13 as Output

    while (1) {
        *MY_PORTB ^= (1 << 5); // Toggle LED

        // 1. Reset the Clock Counter to Zero
        *TCNT1_REG = 0;

        /* 2. Start the Clock with a Prescaler of 1024
           By setting the bits in TCCR1B, we tell the hardware:
           "Start counting every 1024 clock pulses." */
        *TCCR1B_REG = (1 << 0) | (1 << 2); 

        /* 3. Wait for the exact number of ticks.
           Math: 16MHz / 1024 = 15,625 ticks per second.
           For 500ms (0.5s): 15,625 * 0.5 = 7,812 ticks. */
        while (*TCNT1_REG < 7812) {
            // Do nothing, just watch the hardware counter box
        }

        // 4. Stop the Clock (set prescaler to 0)
        *TCCR1B_REG = 0;
    }
}
