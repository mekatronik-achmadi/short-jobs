#include <avr/io.h>
#include <util/delay.h>

#define ON_LIMIT 0

static void io_init(void){
    DDRB |= 1<<3;
    DDRB &= ~(1<<4);

    PORTB |= 1<<3;
    PORTB |= 1<< 4;

}

static void lamp_on(void){
    uint8_t cnt_on;

    for(cnt_on=0;cnt_on<255;cnt_on++){
        PORTB |= 1<<3;
        _delay_us(250);

        PORTB &= ~(1<<3);
        _delay_us(250);
    }
}

static void lamp_con(void){
        lamp_on();
        _delay_ms(100);

        PORTB &= ~(1<<3);
        _delay_ms(200);
}

int main(void)
{
    io_init();

    while (1) {
#if ON_LIMIT
        lamp_on();
#else
        lamp_con();
#endif
    }
    return 0;
}

