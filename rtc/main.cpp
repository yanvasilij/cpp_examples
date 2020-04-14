#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <errno.h>
#include <string.h>

int main( void )
{
    time_t time_of_day;
    struct timespec stime;
    struct timeval time_to_set;

    struct tm new_year;
    new_year.tm_year  = 2020 - 1900;
    new_year.tm_mon   = 4;
    new_year.tm_mday  = 14;
    new_year.tm_hour  = 10;
    new_year.tm_min   = 26;
    new_year.tm_sec   = 0;
    new_year.tm_isdst = 0;

    time_of_day = mktime(&new_year);

    if (time_of_day == -1)
        printf("mktime: %s\n", strerror(errno) );

    stime.tv_sec = time_of_day;

    printf("time_of_day: %d\n", time_of_day);

    if (clock_settime(CLOCK_REALTIME , &stime) == -1 )
    {
        printf("Somthing is wrong! %s\n", strerror(errno) );
    }

    return EXIT_SUCCESS;
}
