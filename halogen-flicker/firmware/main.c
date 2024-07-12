#include <avr/io.h>
#include <util/delay.h>

#define FLICK_SLOW 1000
#define FLICK_FAST 200

#define FLICK_MODE_SLOW 0
#define FLICK_MODE_FAST 1

#define FLICK_FN _delay_ms
#define FLICK_MAX_CNT   6

static uint8_t flick_mode, flick_count;

int main(void)
{
    // CONTROL PIN
    DDRB |= 1<<3;
    PORTB &= ~(1<<3);

    flick_mode = FLICK_MODE_FAST;
    flick_count = 0;

    while (1) {
        if(flick_mode==FLICK_MODE_FAST) FLICK_FN(FLICK_FAST);
        else if(flick_mode==FLICK_MODE_SLOW) FLICK_FN(FLICK_SLOW);

        PORTB ^= 1<<3;
        flick_count++;

        if(flick_count==FLICK_MAX_CNT){
            if(flick_mode==FLICK_MODE_FAST) flick_mode=FLICK_MODE_SLOW;
            else if(flick_mode==FLICK_MODE_SLOW) flick_mode=FLICK_FAST;
            flick_count=0;
        }
    }
    return 0;
}

