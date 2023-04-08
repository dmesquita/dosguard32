#pragma once

#include "neural_network.h"

typedef enum _dosguard32_mode {
    UDP,
    TCP,
    UDP_AND_TCP
} dosguard32_mode;

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _dosguard32_config_t {
    err_t (*dense_nn)(struct ip_hdr *, struct tcp_hdr *);
    dosguard32_mode mode;
} dosguard32_config_t;

void dosguard32_init(dosguard32_config_t cfg);

err_t dosguard32_run(struct ip_hdr *iphdr, struct tcp_hdr *tcphdr, struct netif *inp);

#ifdef __cplusplus
}
#endif
