#include "channel.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

channel_t* create_channel(void){
    channel_t* channel = (channel_t*)malloc(sizeof(channel_t));
    channel->current=0;
    return channel;
}

void channel_begin(channel_t* channel){
    //Resets current
    channel->current=0;
}
void channel_transmit(channel_t* channel){
    channel->current++;
}
