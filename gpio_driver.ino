/**
 * Unbox Robotics Firmware Assignment: GPIO Bare-Metal Driver
 * Goal: Toggle Pin 13 (PB5) at 500ms without libraries.
 */

// We define the memory addresses as pointers to volatile unsigned chars.
// 'volatile' ensures the compiler doesn't optimize away these hardware writes.
#define DDRB_REG  ((volatile unsigned char*)0x24)
#define PORTB_REG ((volatile unsigned char*)0x25)

void setup() {
    // 1. Set Pin 13 (Port B, Bit 5) as an OUTPUT.
    // We use a Bitwise OR to set only the 5th bit to 1.
    // Binary: 00100000 (which is 1 << 5)
    *DDRB_REG |= (1 << 5); 
}

void loop() {
    // 2. Toggle the state of Pin 13.
    // We use a Bitwise XOR (^) to flip the 5th bit.
    // If it was 1, it becomes 0. If it was 0, it becomes 1.
    *PORTB_REG ^= (1 << 5);

    // 3. Manual Delay Loop (Requirement: 500ms).
    // Since we can't use delay(), we create a loop that does nothing.
    // On a 16MHz processor, this number roughly equals 500ms of CPU time.
    for (volatile long i = 0; i < 200000; i++) {
        // Just spinning the CPU cycles...
    }
}
