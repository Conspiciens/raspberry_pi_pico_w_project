#include <stdio.h> 
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/sockets.h"

#define LEDLIGHT 25

const char ssid[] = ""; 
const char password[] = ""; 

void turn_led_on(){
    gpio_put(
        15, 
        1
    ); 
}

void turn_led_off(){
    gpio_put(
        15, 
        0 
    );
} 

int main() {
    /* Begin trasfering USB data over serial */
    stdio_init_all(); 

    gpio_init(15); 
    gpio_set_dir(15, GPIO_OUT); 
    
    turn_led_on(); 
    if (cyw43_arch_init_with_country(CYW43_COUNTRY_USA)){
        printf("Failed to initialized"); 
        return 0; 
    }

    cyw43_arch_enable_sta_mode(); 

    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Failed to connect"); 
        return 0; 
    }

    printf("Connceted"); 
    turn_led_on(); 
    sleep_ms(2000);
    turn_led_off(); 
    sleep_ms(2000);
    turn_led_on(); 
    sleep_ms(2000); 
    turn_led_off();
} 
