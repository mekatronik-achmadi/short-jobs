#include <avr/io.h>
#include <util/delay.h>

#define USE_INPUT   0
#define USE_CTRL    1

static void io_init(void){
    DDRB |= 1<<3;
    DDRB &= ~(1<<4);

    PORTB |= 1<<3;
    PORTB |= 1<< 4;

}

#if USE_CTRL
static void lamp_ctrl(void){
        PORTB |= 1<<3;
        _delay_ms(50);

        PORTB &= ~(1<<3);
        _delay_ms(50);
}
#endif

int main(void)
{
    io_init();

    while (1) {
#if USE_INPUT
        if(PINB & (1 << 4)) PORTB |= 1<<3;
        else PORTB &= ~(1<<3);
#else
  #if USE_CTRL
        lamp_ctrl();
  #else
        PORTB |= 1<<3;
  #endif
#endif
        _delay_us(500);
    }
    return 0;
}

