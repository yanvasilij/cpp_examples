#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <cstdio>
#include <cstdlib>

#define CODE_TIMER 1

static int chid; /**< @brief Channel id for QNX impulses */
static int coid; /**< @brief Connection id for QNX impulses */

int main( )
{
    //create qnx channel for receiving impulses
    chid = ChannelCreate(0);
    if (chid == -1)
    {
        printf("Unable allocate channel!\n");
        exit(EXIT_FAILURE);
    }


    //Connect to new channel
    coid = ConnectAttach(ND_LOCAL_NODE, 0, chid, 0, 0);

    if (coid == -1)
    {
        printf("Unalbe to coonect to channel\n");
        exit(EXIT_FAILURE);
    }

    struct sigevent     sev;

    SIGEV_PULSE_INIT(&sev, coid, SIGEV_PULSE_PRIO_INHERIT, CODE_TIMER, 0);

    int msg = 0x77777777;
    sev.sigev_value.sival_ptr = (void*)msg;

    printf("creating timer\n");
    timer_t timerid;
    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1)
    {
        printf("timer_create() failure\n");
        exit(EXIT_FAILURE);
    }

    struct itimerspec timer;

    timer.it_value.tv_sec = 1;
    timer.it_value.tv_nsec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_nsec = 0;

    printf("starting timer\n");
    timer_settime(timerid, 0, &timer, NULL);


    printf("starting for timer wait\n");
    while (true)
    {
        struct _pulse pulse;
        auto rcvid = MsgReceivePulse(chid, &pulse, sizeof(pulse), NULL);

        printf("msg: 0x%x\n", pulse.value);
    }

    return 0;
}
