#include "message.h"
#include "station.h"
#include "channel.h"

#include <stdlib.h>
#include <time.h>

#define N 5
#define MAX_ATTEMPT 10
#define FRAME_SIZE 8

int main(){
   set_loglevel(LVL_FULL);
   debug("Program starting...");
   //Variables
   channel_t* channel=create_channel();
   station_t** stations=(station_t**)malloc(sizeof(station_t*)*N);
   //Initialization
   srand(time(NULL));
   for(int i=0; i<N; ++i){
       stations[i]=make_station(i,MAX_ATTEMPT, FRAME_SIZE,channel);
   }
   //Simulation 
   for(int i=0; i<128; ++i){
       debug("Epoch: %d, timing %f µs", i, 51.2*i);
       channel_begin(channel);
       for(int j=0; j<N; ++j){
           station_begin(stations[j]);
       }
       for(int j=0; j<N; ++j){
           station_end(stations[j]);
       } 
    }
    return 0;
}
