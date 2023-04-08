#include <cmath>
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/micro_log.h"

#include "esp_log.h"

#include <esp_heap_caps.h>

#include "include/model.h"
#include "include/neural_network.h"

using namespace std;

static const char *TAG = "neural_network";

TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

const tflite::Model* model = ::tflite::GetModel(g_model);
static tflite::AllOpsResolver resolver;

const int kTensorArenaSize = 1300;
uint8_t tensor_arena[kTensorArenaSize];

static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize);
tflite::MicroInterpreter* interpreter = &static_interpreter;

TfLiteStatus allocate_status = interpreter->AllocateTensors();

int64_t init_time = xTaskGetTickCount() * portTICK_PERIOD_MS /1000;

err_t nn(struct ip_hdr *iphdr, struct tcp_hdr *tcphdr) {
  //ESP_LOGE(TAG, "inside nn");
  input = interpreter->input(0);
  output = interpreter->output(0);

  int64_t now = xTaskGetTickCount() * portTICK_PERIOD_MS /1000;
  
  input->data.f[0]  = init_time - now;
  input->data.f[1]  = isnan(iphdr->_v_hl) ? -1 : iphdr->_v_hl;
  input->data.f[2]  = (IPH_OFFSET(iphdr) & IP_DF);
  input->data.f[3]  = IPH_OFFSET(iphdr);
  input->data.f[4]  = IPH_PROTO(iphdr);
  input->data.f[5]  = IPH_TTL(iphdr);
  input->data.f[6]  = htons(tcphdr->wnd);
  input->data.f[7]  = (TCPH_FLAGS(tcphdr) & TCP_SYN) ? 1 : 0;
  input->data.f[8]  = (TCPH_FLAGS(tcphdr) & TCP_URG) ? 1 : 0;
  input->data.f[9]  = TCPH_HDRLEN(tcphdr);
  
  init_time = now; //TODO: I want (init_time - now) to be the delta between packets, check if this is way of doing it is correct

  // Run inference, and report any error
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    MicroPrintf("tflite model invoke failed\n");
    ESP_LOGE(TAG, "Erro tensorflow");
    return ERR_ABRT;
  }

  // Obtain the output from model's output tensor
  double value = output->data.f[0];

  return value > 0.5 ? ERR_ABRT : ERR_OK;
}
