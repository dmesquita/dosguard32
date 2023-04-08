set($ENV{IDF_PATH}/components
    )

idf_component_register(SRCS "dosguard32.c" "neural_network.cc" "model.cc"
                    REQUIRES "esp_netif" "esp_timer"
                    PRIV_REQUIRES tflite-lib spi_flash
                    INCLUDE_DIRS "include")
