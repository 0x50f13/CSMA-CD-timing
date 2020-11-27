#ifndef STATION_H
#define STATION_H

#include "channel.h"

#include <stdint.h>

typedef struct{
  channel_t* channel;
  uint32_t _id;
  uint64_t attempt; //Number of attempts
  uint64_t maxAttempt; //After which attempt station stops trying to send frame
  uint64_t sizeRemaining; //How many we need to send
  uint64_t frameSize; //Initial frame size
  uint64_t wait; //time to wait
  uint32_t lastCurrent; // Measured current on a channel by station
  uint64_t sentAt; //At which epoch frame was sent
  bool isTransmitting; // Is station sending something to channel?
} station_t;

station_t* make_station(uint32_t _id,uint64_t maxAttempt, uint64_t frameSize, channel_t* channel);
void station_begin(station_t* station,uint64_t t);
void station_end(station_t* station, uint64_t t);
#endif
