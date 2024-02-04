#include <stdio.h> 
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/sockets.h"

#define LEDPIN 25

const char ssid[] = ""; 
const char password[] = ""; 

void turn_led_on(){
    gpio_put(
        LEDPIN, 
        1
    ); 
}

void turn_led_off(){
    gpio_put(
        LEDPIN, 
        0 
    );
} 

void scanner(){
    cyw43_wifi_scan_options_t wifi_options; 
    cyw43_t wifi_data; 
    cyw43_ev_scan_result_t scan_result; 
    int wifi_scan; 
    
    cyw43_init(&wifi_data); 

    /* Start the wifi scan */
    wifi_scan = cyw43_wifi_scan(&wifi_data, &wifi_options, *void, &scan_result)
    if (wifi_scan < 0){
        print("Failed to start scanning"); 
        return; 
    }

    /* Scan for any local wifi and wait till complete */
    while (cyw43_wifi_scan_active(wifi_data)) {
        print("Scanning..."); 
    }

    print(scan_result.bssid[0]); 
}

void connect_to_wifi(){
    uint32_t country = CYW43_COUNTRY_USA; 

    if (cyw43_arch_init_with_country(country)){
        printf("Failed to intialized"); 
        return; 
    }

    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 10000)){
        printf("Failed to connect"); 
        return; 
    }

    printf("Connected to wifi"); 
}

void check_wifi_strength(){
    cy43_t wifi; 
    int32_t rssi; 

    int int_rssi = cyw43_wifi_get_rssi(&wifi, &rssi); 

    if (int_rssi){
        printf("Failed to get rssi value"); 
        return; 
    }

    if (rssi <= -85){
       disconnect_from_wifi();  
    }

    return; 
}

void disconnect_from_wifi(){
    

}

int main() {
    /* Begin trasfering USB data over serial */
    stdio_init_all(); 

    gpio_init(LEDPIN); 
    gpio_set_dir(LEDPIN, GPIO_OUT); 
    
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
