#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

            /*
P8.7   a
P8.8   b
P8.9   c
P8.10  h
P8.11  d
P8.12  e
P8.14  f
P8.16  g    */



#define GPIO_66_P8_7_SEGA       66
#define GPIO_67_P8_8_SEGB       67
#define GPIO_69_P8_9_SEGC       69
#define GPIO_68_P8_10_DP        68
#define GPIO_45_P8_11_SEGD      45
#define GPIO_44_P8_12_SEGE      44
#define GPIO_26_P8_14_SEGF      26
#define GPIO_46_P8_16_SEGG      46


#define HIGH  		1
#define LOW   		0
#define GPIO_DIR_OUT        HIGH
#define GPIO_DIR_IN         LOW
#define GPIO_LOW_VALUE      LOW
#define GPIO_HIGH_VALUE     HIGH
#define SEGMENT_ON          HIGH
#define SEGMENT_OFF         LOW


#define SYS_GPIO_PATH 		"/sys/class/gpio"

#define SOME_BYTES 			100


int gpio_configure_direction(uint32_t gpio_num, uint8_t dir_value){
    int fd;
    char buf[SOME_BYTES];

    snprintf(buf, sizeof(buf), SYS_GPIO_PATH "/gpio%d/direction", gpio_num);

    fd = open(buf, O_WRONLY);

    if (dir_value)
        write(fd, "out", 4); //  out 3 byte +1 boşluk
    else
        write(fd, "in", 3);

    close(fd);
    return 0;
}


int gpio_write_value(uint32_t gpio_num, uint8_t out_value){
    int fd;
    char buf[SOME_BYTES];

    snprintf(buf, sizeof(buf), SYS_GPIO_PATH "/gpio%d/value", gpio_num);

    fd = open(buf, O_WRONLY);

    if (out_value)
        write(fd, "1", 2);
    else
        write(fd, "0", 2);

    close(fd);
    return 0;
}


int initialize_all_gpios(void){

    gpio_configure_direction(66,GPIO_DIR_OUT);
    gpio_write_value(66, GPIO_LOW_VALUE );
    
    gpio_configure_direction(67,GPIO_DIR_OUT);
    gpio_write_value(67, GPIO_LOW_VALUE );
    
    gpio_configure_direction(69,GPIO_DIR_OUT);
    gpio_write_value(69, GPIO_LOW_VALUE );
    
    gpio_configure_direction(68,GPIO_DIR_OUT);
    gpio_write_value(68, GPIO_LOW_VALUE );
    
    gpio_configure_direction(45,GPIO_DIR_OUT);
    gpio_write_value(45, GPIO_LOW_VALUE );
    
    gpio_configure_direction(44,GPIO_DIR_OUT);
    gpio_write_value(44, GPIO_LOW_VALUE );
    
    gpio_configure_direction(26,GPIO_DIR_OUT);
    gpio_write_value(26, GPIO_LOW_VALUE );
    
    gpio_configure_direction(46,GPIO_DIR_OUT);
    gpio_write_value(46, GPIO_LOW_VALUE );

    return 0;
}



void Write_number_to_7segdisplay(uint8_t number){

    switch (number){

    case 0:
        gpio_write_value(GPIO_66_P8_7_SEGA, SEGMENT_ON);
        gpio_write_value(GPIO_67_P8_8_SEGB, SEGMENT_ON);
        gpio_write_value(GPIO_69_P8_9_SEGC, SEGMENT_ON);
        gpio_write_value(GPIO_45_P8_11_SEGD, SEGMENT_ON);
        gpio_write_value(GPIO_44_P8_12_SEGE, SEGMENT_ON);
        gpio_write_value(GPIO_26_P8_14_SEGF, SEGMENT_ON);
        gpio_write_value(GPIO_46_P8_16_SEGG, SEGMENT_OFF);
    break;

    case 1:
        gpio_write_value(GPIO_66_P8_7_SEGA, SEGMENT_OFF);
        gpio_write_value(GPIO_67_P8_8_SEGB, SEGMENT_ON);
        gpio_write_value(GPIO_69_P8_9_SEGC, SEGMENT_ON);
        gpio_write_value(GPIO_45_P8_11_SEGD, SEGMENT_OFF);
        gpio_write_value(GPIO_44_P8_12_SEGE, SEGMENT_OFF);
        gpio_write_value(GPIO_26_P8_14_SEGF, SEGMENT_OFF);
        gpio_write_value(GPIO_46_P8_16_SEGG, SEGMENT_OFF);
    break;

    case 2:
        gpio_write_value(GPIO_66_P8_7_SEGA, SEGMENT_ON);
        gpio_write_value(GPIO_67_P8_8_SEGB, SEGMENT_ON);
        gpio_write_value(GPIO_69_P8_9_SEGC, SEGMENT_OFF);
        gpio_write_value(GPIO_45_P8_11_SEGD, SEGMENT_ON);
        gpio_write_value(GPIO_44_P8_12_SEGE, SEGMENT_ON);
        gpio_write_value(GPIO_26_P8_14_SEGF, SEGMENT_OFF);
        gpio_write_value(GPIO_46_P8_16_SEGG, SEGMENT_ON);
    break;

    case 3:
        gpio_write_value(GPIO_66_P8_7_SEGA, SEGMENT_ON);
        gpio_write_value(GPIO_67_P8_8_SEGB, SEGMENT_ON);
        gpio_write_value(GPIO_69_P8_9_SEGC, SEGMENT_ON);
        gpio_write_value(GPIO_45_P8_11_SEGD, SEGMENT_ON);
        gpio_write_value(GPIO_44_P8_12_SEGE, SEGMENT_OFF);
        gpio_write_value(GPIO_26_P8_14_SEGF, SEGMENT_OFF);
        gpio_write_value(GPIO_46_P8_16_SEGG, SEGMENT_ON);
    break;

    case 4:
        gpio_write_value(GPIO_66_P8_7_SEGA, SEGMENT_OFF);
        gpio_write_value(GPIO_67_P8_8_SEGB, SEGMENT_ON);
        gpio_write_value(GPIO_69_P8_9_SEGC, SEGMENT_ON);
        gpio_write_value(GPIO_45_P8_11_SEGD, SEGMENT_OFF);
        gpio_write_value(GPIO_44_P8_12_SEGE, SEGMENT_OFF);
        gpio_write_value(GPIO_26_P8_14_SEGF, SEGMENT_ON);
        gpio_write_value(GPIO_46_P8_16_SEGG, SEGMENT_ON);
    break;

    case 5:
        gpio_write_value(GPIO_66_P8_7_SEGA, SEGMENT_ON);
        gpio_write_value(GPIO_67_P8_8_SEGB, SEGMENT_OFF);
        gpio_write_value(GPIO_69_P8_9_SEGC, SEGMENT_ON);
        gpio_write_value(GPIO_45_P8_11_SEGD, SEGMENT_ON);
        gpio_write_value(GPIO_44_P8_12_SEGE, SEGMENT_OFF);
        gpio_write_value(GPIO_26_P8_14_SEGF, SEGMENT_ON);
        gpio_write_value(GPIO_46_P8_16_SEGG, SEGMENT_ON);
    break;

    case 6:
        gpio_write_value(GPIO_66_P8_7_SEGA, SEGMENT_ON);
        gpio_write_value(GPIO_67_P8_8_SEGB, SEGMENT_OFF);
        gpio_write_value(GPIO_69_P8_9_SEGC, SEGMENT_ON);
        gpio_write_value(GPIO_45_P8_11_SEGD, SEGMENT_ON);
        gpio_write_value(GPIO_44_P8_12_SEGE, SEGMENT_ON);
        gpio_write_value(GPIO_26_P8_14_SEGF, SEGMENT_ON);
        gpio_write_value(GPIO_46_P8_16_SEGG, SEGMENT_ON);
    break;

    case 7:
        gpio_write_value(GPIO_66_P8_7_SEGA, SEGMENT_ON);
        gpio_write_value(GPIO_67_P8_8_SEGB, SEGMENT_ON);
        gpio_write_value(GPIO_69_P8_9_SEGC, SEGMENT_ON);
        gpio_write_value(GPIO_45_P8_11_SEGD, SEGMENT_OFF);
        gpio_write_value(GPIO_44_P8_12_SEGE, SEGMENT_OFF);
        gpio_write_value(GPIO_26_P8_14_SEGF, SEGMENT_OFF);
        gpio_write_value(GPIO_46_P8_16_SEGG, SEGMENT_OFF);
    break;

    case 8:
        gpio_write_value(GPIO_66_P8_7_SEGA, SEGMENT_ON);
        gpio_write_value(GPIO_67_P8_8_SEGB, SEGMENT_ON);
        gpio_write_value(GPIO_69_P8_9_SEGC, SEGMENT_ON);
        gpio_write_value(GPIO_45_P8_11_SEGD, SEGMENT_ON);
        gpio_write_value(GPIO_44_P8_12_SEGE, SEGMENT_ON);
        gpio_write_value(GPIO_26_P8_14_SEGF, SEGMENT_ON);
        gpio_write_value(GPIO_46_P8_16_SEGG, SEGMENT_ON);
    break;

    case 9:
        gpio_write_value(GPIO_66_P8_7_SEGA, SEGMENT_ON);
        gpio_write_value(GPIO_67_P8_8_SEGB, SEGMENT_ON);
        gpio_write_value(GPIO_69_P8_9_SEGC, SEGMENT_ON);
        gpio_write_value(GPIO_45_P8_11_SEGD, SEGMENT_ON);
        gpio_write_value(GPIO_44_P8_12_SEGE, SEGMENT_OFF);
        gpio_write_value(GPIO_26_P8_14_SEGF, SEGMENT_ON);
        gpio_write_value(GPIO_46_P8_16_SEGG, SEGMENT_ON);
    break;

    case 10:
        gpio_write_value(GPIO_66_P8_7_SEGA, SEGMENT_OFF);
        gpio_write_value(GPIO_67_P8_8_SEGB, SEGMENT_OFF);
        gpio_write_value(GPIO_69_P8_9_SEGC, SEGMENT_OFF);
        gpio_write_value(GPIO_45_P8_11_SEGD, SEGMENT_OFF);
        gpio_write_value(GPIO_44_P8_12_SEGE, SEGMENT_OFF);
        gpio_write_value(GPIO_26_P8_14_SEGF, SEGMENT_OFF);
        gpio_write_value(GPIO_46_P8_16_SEGG, SEGMENT_OFF);
    break;
    }
}


// 0 - 9  arası yazdır
void start_upcounting(int delay){
    uint8_t i =0;
    
    if ( initialize_all_gpios() < 0)
    {
        printf("Error");
    }

    else
    {
        while(1) // döngüde sonsuza kadar 0-9 arası
       {
            for(i=0;i<10;i++)
            {
                Write_number_to_7segdisplay(i);

                usleep(delay * 1250);
            }
       }
    }
}


int main(int argc, char *argv[]) {
    
    printf("Up counter on 7 seg display\n");

    if ( argc != 3 )
    {
        printf( "usage: %s <direction> <delay>\n", argv[0] );
    }

    else
    {
        int delay = atoi(argv[2]); // convert integer
        

        if (! strcmp(argv[1], "up") ){
            start_upcounting(delay);
        }

        else{
            printf("Invalid direction values\n");

        }
    }
}
