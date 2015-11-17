#include "rpgpio.h"

#define CLK_PIN 26

int main(int argc, char **argv)
{
    // Set up gpi pointer for direct register access
    setup_io();

    int PINS[] = {
        // bits from least to most significant are mapped to pins numbered
        22, 10, 9, 11, 5, 6, 13, 19,
        CLK_PIN
    };
    int N_PINS = 9;
    for (int i = 0; i < N_PINS; i++) {
        INP_GPIO(PINS[i]); // must use INP_GPIO before we can use OUT_GPIO
        OUT_GPIO(PINS[i]);
    }

    unsigned char color;
    int i;
    while(1) {
        read(STDIN_FILENO, &color, 1);

        GPIO_SET = 1 << CLK_PIN;
        for (i = 0; i < N_PINS - 1; i++) {
            GPIO_CLR = (!(color >> i) & 0b1)<<PINS[i];
            GPIO_SET = ((color >> i) & 0b1)<<PINS[i];
        }
        GPIO_CLR = 1 << CLK_PIN;
    }
    return 0;

} // main


//
// Set up a memory regions to access GPIO
//
void setup_io()
{
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
        printf("can't open /dev/mem \n");
        exit(-1);
    }

    /* mmap GPIO */
    gpio_map = mmap(
            NULL,             //Any adddress in our space will do
            BLOCK_SIZE,       //Map length
            PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
            MAP_SHARED,       //Shared with other processes
            mem_fd,           //File to map
            GPIO_BASE         //Offset to GPIO peripheral
            );

    close(mem_fd); //No need to keep mem_fd open after mmap

    if (gpio_map == MAP_FAILED) {
        printf("mmap error %d\n", (int)gpio_map);//errno also set!
        exit(-1);
    }

    // Always use volatile pointer!
    gpio = (volatile unsigned *)gpio_map;


} // setup_io
