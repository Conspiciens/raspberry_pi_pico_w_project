#include <stdio.h> 

#include "hardware/flash.h"
#include "pico/stdlib.h"

/* Defines the offset of the flash target */
#define FLASH_TARGET_OFFSET (256 * 1024)
#define MAX_SIZE 200 

struct wifi_auth {
    char *username; 
    char *password;
};

struct wifi_auth wifi_ssid[MAX_SIZE];
const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

void init_wifi_auth(){
    addr = XIP_BASE + FLASH_TARGET_OFFSET 
    p = (struct wifi_auth *)(addr); 
    wifi_ssid = p; 
}

void add_wifi(char *username, char* password){
    size_t sizeOfStruct = sizeof(wifi_ssid) / sizeof(wifi_ssid[0]);

    for (int i = 0; i < MAX_SIZE; i += ){
        if (wifi_ssid[i] == null){
            wifi_ssid[i].username = username;
            wifi_ssid[i].password = password;
            return;
        }
    }
}

void erase_flash(){

}

void update_flash(){
    flash_range_program(FLASH_TARGET_OFFSET, (const uint8_t *)wifi_ssid, FLASH_PAGE_SIZE);
    printf("Updated Flash"); 
}

void print_buf(const uint8_t *buf, size_t len){
    for (size_t i = 0; i < len; i++){
        printf("%02x", buf[i]);
    }
}