#ifndef __SNR9816_H_
#define __SNR9816_H_
#include <stdint.h>
#define  BUSY_STATE			0X4E
#define  FREE_STATE			0X4F
void snr9816_init(void);
void snr9816_sendbyte(uint8_t byte);
uint8_t snr9816tts_say_sentence(const char *sentence);
uint8_t snr9816tts_say_array(uint8_t *buf, uint8_t buf_len);
uint8_t snr9816tts_set_voice(const char * str);
uint8_t ring_1(void);
#endif


