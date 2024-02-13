#include <stdio.h> 
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/sockets.h"

#define LEDPIN 15

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

/* Mini implementation of string cmp */
bool simple_strcmp(const char *string1, const char *string2){
    if (sizeof(string1) == sizeof(string2)){
        for (int i = 0; i < sizeof(string1); i++){
            if (string1[i] == string2[i]){
                continue; 
            } else {
                return false; 
            }
        }
        return true; 
    } else {
        return false; 
    } 
}

/* Check whether the bssid is the same */
int scan_function(void *context, const cyw43_ev_scan_result_t *scan_result){
    printf("SSID: %s", scan_result->ssid);
    if (scan_result){
         printf("ssid: %-32s rssi: %4d chan: %3d mac: %02x:%02x:%02x:%02x:%02x:%02x sec: %u\n",
            scan_result->ssid, scan_result->rssi, scan_result->channel,
            scan_result->bssid[0], scan_result->bssid[1], scan_result->bssid[2], scan_result->bssid[3], scan_result->bssid[4], scan_result->bssid[5],
            scan_result->auth_mode);
    }
    if (simple_strcmp(scan_result->ssid, ssid) == true){
        return 0; 
    } 

    return -1; 
}


void scanner(){
    cyw43_wifi_scan_options_t wifi_options = {0}; 
    cyw43_ev_scan_result_t scan_result; 
    int wifi_scan; 
    

    turn_led_on();  
    printf("Scanning...");
    /* Start the wifi scan (interseting you don't need to initialize cyw43_state )*/
    wifi_scan = cyw43_wifi_scan(&cyw43_state, &wifi_options, NULL, scan_function);
    printf("%d",wifi_scan);
    if (wifi_scan){
        printf("Failed to start scanning"); 
        return; 
    }
    turn_led_off();

    /* Scan for any local wifi and wait till complete */
    while (cyw43_wifi_scan_active(&cyw43_state)){ 
        turn_led_on();
        printf("Scanning..."); 
        turn_led_off(); 
    }

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

void disconnect_from_wifi(cyw43_t *init_wifi){
    int isLeave; 

    isLeave = cyw43_wifi_leave(init_wifi, CYW43_ITF_AP); 
    if (isLeave){
        printf("Failed to leave the wifi");
        return; 
    }

    printf("Disconnected from wifi");
    return; 
}

void check_wifi_strength(cyw43_t *init_wifi){
    int32_t rssi; 

    int int_rssi = cyw43_wifi_get_rssi(init_wifi, &rssi); 

    if (int_rssi){
        printf("Failed to get rssi value"); 
        return; 
    }

    if (rssi <= -85){
       disconnect_from_wifi(init_wifi);  
    }

    return; 
}

int main() {
    cyw43_t init_wifi; 

    /* Initalize I/O */
    stdio_init_all(); 


    gpio_init(LEDPIN); 
    gpio_set_dir(LEDPIN, GPIO_OUT); 

    turn_led_on();
    sleep_ms(5000); 
    turn_led_off(); 

    

    
    turn_led_on(); 
    if (cyw43_arch_init()){
        printf("Failed to intialized"); 
        return 0;
    }

    /* Enable sta mode */
    cyw43_arch_enable_sta_mode(); 

    printf("start");
    scanner();
    printf("end"); 

    if (cyw43_arch_init_with_country(CYW43_COUNTRY_USA)){
        printf("Failed to initialized"); 
        return 0; 
    }

    cyw43_arch_enable_sta_mode(); 

    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Failed to connect"); 
        return 0; 
    }
    turn_led_off();
} 
