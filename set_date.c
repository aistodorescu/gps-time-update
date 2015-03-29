#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Set date: date -u -s "2013/10/05 12:48:00" */

#define IN_BUFF_SIZE    100
#define OUT_BUFF_SIZE   60
#define START_COMMAND   "date -u -s \""
#define END_COMMAND     "\""

FILE *fp;
uint8_t idx;
uint32_t timeRaw, dateRaw;
uint32_t speedRaw;
uint8_t tempStr[10];
uint8_t tempStr1[10];
uint32_t temp32;
uint8_t temp8;
int result;
int error = 0;

uint8_t hour;
uint8_t minute;
uint8_t second;
uint8_t day;
uint8_t month;
uint16_t year;
uint8_t century;

int main(int argc, char* argv[])
{
    uint8_t buffIn[IN_BUFF_SIZE];
    uint8_t buffOut[OUT_BUFF_SIZE];
    
    /* Clear buffers */
    memset(buffIn, 0, IN_BUFF_SIZE);
    memset(buffOut, 0, IN_BUFF_SIZE);
    
#if 0
    printf("%d\n", argc);
    idx=0;
    while(idx<argc)
    {
        printf("%s\n", argv[idx]);
        idx++;
    }
#endif

    /* If we got at least one argument beside the program name */
    if(argc >= 3)
    {
        //printf("text: %s\n", buffIn);
    
        /* Start processing input data to get needed vars */
        /* $GPRMC,174857.000,A,4425.1133,N,02602.8283,E,0.00,131.2,051013,,*3C */
        result = sscanf(argv[2] + 6, ",%ld.%d,%c,%d.%d,%c,%d.%d,%c,%d.%d,%d.%d,%d,,%s",
            &timeRaw,
            &temp32,
            &temp8,
            &temp32,
            &temp32,
            &temp8,
            &temp32,
            &temp32,
            &temp8,
            &speedRaw,
            &temp32,
            &temp32,
            &temp32,
            &dateRaw,
            tempStr
            );
        
        /* Check if sscanf went OK for GPRMC(15 params) */
        if(result == 15)
        {
            hour = timeRaw / 10000;
            minute = (timeRaw % 10000) / 100;
            second = (timeRaw % 10000) % 100;
            
            century = atoi(argv[1]);
            day = dateRaw / 10000;
            month = (dateRaw % 10000) / 100;
            year = (century - 1) * 100 + (dateRaw % 10000) % 100;

            //printf("%d-%d-%d %d:%d:%d\n", day, month, year, hour, minute, second);
            
            sprintf(buffOut, "%s%d/%d/%d %d:%d:%d%s",
                START_COMMAND,
                year, month, day,
                hour, minute, second,
                END_COMMAND);
            
            //printf("%s\n", buffOut);
            
            /* Call system command */
            system(buffOut);
            
            error = 0;
        }
        else
        {
            printf("Wrong input data\n");
            error = 1;
        }
    }
    else
    {
        printf("GPS read error\n");
        error = 1;
    }
    
    return error;
}
