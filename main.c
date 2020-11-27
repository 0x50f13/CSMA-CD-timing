#include "message.h"
#include "station.h"
#include "channel.h"
#include "arguments.h"

#include <stdlib.h>
#include <time.h>

//For compatiablility
#ifndef __VERSION__
#define __VERSION__ "<NOT PROVIDED>"
#endif

int main(int argc, const char * argv[]){
   set_loglevel(LVL_FULL);
   debug("Program starting...");
   arguments_begin();
   info("Built with %s at %s %s",__VERSION__,__DATE__,__TIME__);
   
   //Add arguments
   argument_add("-n","Number of stations(default:5)", ARG_INT, argint(5), true, false);
   argument_add("--frame-size","Size of the frame(default:1518)", ARG_INT, argint(1518), true, false);
   argument_add("--max-attempt","Maximum attempts to retransmit(default:10)", ARG_INT, argint(10), true, false); 
   argument_add("--debug","Enables debug logging",ARG_BOOL, argbool(false), true, false);  
   
   //Parse arguments
   arguments_parse(argc, argv, 1);
   
   //Variables
   uint64_t t=0;//Epoch number
   channel_t* channel=create_channel();
   uint64_t maxAttempt=argument_value_get_s("--max-attempt",ARG_INT).intValue;
   uint64_t frameSize=argument_value_get_s("--frame-size",ARG_INT).intValue;
   int N=argument_value_get_s("-n", ARG_INT).intValue;
   station_t** stations=(station_t**)malloc(sizeof(station_t*)*N);

   //Initialization
   if(!argument_value_get_s("--debug", ARG_BOOL).boolValue){
      set_loglevel(LVL_RELEASE);
   }
   srand(time(NULL));
   for(int i=0; i<N; ++i){
       stations[i]=make_station(i,maxAttempt, frameSize, channel);
   }
   
   //Simulation 
   for(;;){
       debug("Epoch: %d, timing %f µs", t, 51.2*t);
       channel_begin(channel);
       for(int j=0; j<N; ++j){
           station_begin(stations[j],t);
       }
       for(int j=0; j<N; ++j){
           station_end(stations[j],t);
       } 
       int sent=0;
       for(int j=0; j<N; ++j){
           if(stations[j]->sizeRemaining==0){
              ++sent;
           }
        }
        if(sent==N){
           success("Finished simulation successfully.");
           break;
        }
        ++t;
    }
    
    //Print table
    int i=0;
    printf("%-25s%-10s\n", "ID", "Timecode");
    for(i=0;i<N;++i){
        station_t* station=stations[i];
        if(station->sentAt>0){
           printf("%-25u%-8fµs\n", station->_id, 51.2*(station->sentAt-frameSize+1));
        }else{
           printf("%-25uFAILED\n", station->_id);
        }
    }
    return 0;
}
