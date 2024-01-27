#include <stdio.h> 
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define MAX 20

using namespace std; 

char ssid[MAX] = "Watching-you-guest"; 
char password[MAX] = "T3st1ng1=!"; 

void turn_led_on(){
    cyw43_arch_gpio_put(
        CYW43_WL_GPIO_LED_PIN, 
        1
    ); 
}

void turn_led_off(){
    cyw43_arch_gpio_put(
        CYW43_WL_GPIO_LED_PIN, 
        0 
    );
}

int main() {
    FILE *fp; 
    size_t charCount; 

    /* Begin trasfering USB data over serial */
    stdio_init_all(); 

    
    if (cyw43_arch_init_with_country(CYW_43_COUNTRY_USA)){
        prinf("Failed to initialized"); 
        return; 
    }

    cyw43_arch_enable_sta_mode(); 

    if (cyw43_arch_init_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Failed to connect"); 
        return; 
    }

    printf("Connceted"); 

} 
