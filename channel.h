#ifndef CHANNEL_H
#define CHANNEL_H

#include <stdint.h>
#include <stdbool.h>

typedef struct{
  uint32_t current;//Channel amperage divided by 24mA  
} channel_t;

channel_t* create_channel(void);
void channel_begin(channel_t* channel);
void channel_transmit(channel_t* channel);
#endif 
