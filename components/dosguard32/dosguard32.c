#include "dosguard32.h"
#include "esp_log.h"

static const char *TAG = "dosguard32";

dosguard32_config_t config_dosguard32;

void dosguard32_init(dosguard32_config_t cfg) {
    ESP_LOGE(TAG, "Initializing dosguard32");
    config_dosguard32 = cfg;
}

err_t dosguard32_run(struct ip_hdr *iphdr, struct tcp_hdr *tcphdr, struct netif *inp) {
    
    switch (config_dosguard32.mode) {
        case UDP:
            if (IPH_PROTO(iphdr) != IP_PROTO_UDP) {
                ESP_LOGE(TAG, "IS_NOT_A_UDP_PACKET");
                return ERR_OK;
            }
            return config_dosguard32.dense_nn(iphdr, tcphdr);
        case TCP:
            if (IPH_PROTO(iphdr) != IP_PROTO_TCP) {
                ESP_LOGE(TAG, "IS_NOT_A_TCP_PACKET");
                return ERR_OK;
            }
            return config_dosguard32.dense_nn(iphdr, tcphdr);
        case UDP_AND_TCP:
            return config_dosguard32.dense_nn(iphdr, tcphdr);
    }

    return ERR_OK;
}
