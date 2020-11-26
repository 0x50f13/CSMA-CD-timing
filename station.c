#include "station.h"
#include "channel.h"
#include "message.h"

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define FRAME_SIZE 8
station_t* make_station(uint32_t _id,uint64_t maxAttempt, uint64_t frameSize, channel_t* channel){
    station_t* station=(station_t*)malloc(sizeof(station_t));
    station->_id=_id;
    station->attempt=0;
    station->sizeRemaining=frameSize;
    station->wait=0;
    station->lastCurrent=0;
    station->channel=channel;
    station->sentAt=0;
    station->maxAttempt=maxAttempt;
    station->isTransmitting=false;
    return station;
}

void station_begin(station_t* station){
    if(station->sizeRemaining==0){
       return ; //Already sent frame
    }
    if(station->wait){
       //We are in waiting state
       //Just reduce number of epochs to wait
       station->wait--;
       return;
    }
    assert(station->wait==0);
    uint32_t current;
    if(station->isTransmitting){
       current = 1; //Last time we were transmitting, so 1*24mA it is our current
    }else{
       current = 0; // We are going to transmit
    }
    if(station->lastCurrent==current){
       //Here we assume that it took last iteration of simulation to
       //measure current. If it is 0 we can start transmitting.
       station->isTransmitting = true;
       debug("Station %d is transmitting,remaining=%d",station->_id, station->sizeRemaining);
       channel_transmit(station->channel);
       station->sizeRemaining--;
       if(station->sizeRemaining==0){
          station->isTransmitting=false;
          success("Station with %d has finished transmitting data", station->_id);
       }
    }else{
       //Somebody is transmitting at the moment
       //We simulate measuring current and do nothing
       return ;
   }
}

void station_end(station_t* station){ 
   if(station->sizeRemaining==0){
      return ;
   }
   if(station->wait>0){
      station->lastCurrent=station->channel->current;
      return ; //Station is already in backoff strategy
   }
   if(station->channel->current>1){
      //There is a collision
      //Perform a back-off strategy
      station->attempt++;
      station->isTransmitting=false;
      station->sizeRemaining=FRAME_SIZE;
      if(station->attempt>station->maxAttempt){
         station->sizeRemaining=0;
         info("Station with id %d cancelled data transmition",station->_id);
         return ;
      }
      info("Station with id %d will re-attempt sending data due to collision",station->_id);
      station->wait=1+(rand()%16);//1 iteration to measure current
      debug("wait=%d", station->wait); 
   }
   
   station->lastCurrent=station->channel->current;
}
