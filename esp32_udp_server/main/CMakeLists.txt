idf_component_register(SRCS "udp_server.c"
                    INCLUDE_DIRS "."
                    REQUIRES "protocol_examples_common" "esp_wifi" "nvs_flash" "dosguard32")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
