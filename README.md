# dosguard32 - ESP32 DoS attack filter
This experimental project aims to filter DoS attacks on ESP32 applications using a deep learning model to detect malicious packets. The project closely adheres to the structure established by [T800](https://github.com/c2dc/T800).

## Usage

### Running the UDP Server example
1. Install  [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#installation) and [set up the environment variables](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html#step-4-set-up-the-environment-variables)
2. Run `idf.py menuconfig`, go to Example Connection Configuration and set up your WiFi SSID and password
3. Run `idf.py set-target esp32`, then `idf.py build` and finally `idf.py -p PORT flash monitor`; if you're on linux you can use `ls /dev/tty*` to find the serial USB port name
4. To send traffic to the server run the `legitimate_udp_traffic.py` or the `malicious_udp_traffic.py` scripts

### Using dosguard32 on your ESP32 application
1. Add the components folder to the `set()` of your CMakeLists.txt file
2. On the main .c file add the dosguard32 configuration

    #include "dosguard32.h"
    ...
    dosguard32_config_t config = {
            .dense_nn = nn,
            .mode = UDP
        };
        
    dosguard32_init(config);

## References
[1] Fernandes, Gabriel Victor C., et al. “Implementaçao de um filtro de pacotes inteligente para dispositivos de Internet das Coisas.” _Anais do XL Simpósio Brasileiro de Redes de Computadores e Sistemas Distribuídos_. SBC, 2022.

[2] Sajjad Dadkhah, Hassan Mahdikhani, Priscilla Kyei Danso, Alireza Zohourian, Kevin Anh Truong, Ali A. Ghorbani, “[_Towards the development of a realistic multidimensional IoT profiling dataset_](https://ieeexplore.ieee.org/document/9851966)”, Submitted to: The 19th Annual International Conference on Privacy, Security & Trust (PST2022) August 22–24, 2022, Fredericton, Canada.

[3] Yuan, Xiaoyong, Chuanhuang Li, and Xiaolin Li. “DeepDefense: identifying DDoS attack via deep learning.” 2017 IEEE international conference on smart computing (SMARTCOMP). IEEE, 2017.

[4] Hamza, Ayyoob, Hassan Habibi Gharakheili, and Vijay Sivaraman. “IoT network security: requirements, threats, and countermeasures.” arXiv preprint arXiv:2008.09339 (2020).

