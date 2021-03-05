/**
 * @brief Пример получения дампа при аварийном завершении программы
 * @author Yanikeev-VS
 */
#include <thread>
#include <iostream>
#include <chrono>
#include <backtrace.h>

using VoidFunction = void (*)();

bt_accessor_t acc;
bt_accessor_t acc_sighandler1;
bt_addr_t pc_sighandler1[10];
int cnt_sighandler1;
bt_memmap_t memmap;

void sigfaultHandler (int sig_number)
{
    char out[512];
    std::cout << "sigfault!" << std::endl;

    cnt_sighandler1 =
            bt_get_backtrace(&acc_sighandler1, pc_sighandler1,
                             sizeof(pc_sighandler1)/sizeof(bt_addr_t));

//   bt_sprnf_addrs(&memmap, pc_sighandler1, cnt_sighandler1, "%a",
//                  out, sizeof(out), 0);

    bt_sprn_memmap(&memmap, out, sizeof(out));

    puts(out);

    bt_release_accessor(&acc);

    exit(-1);
}


class CrashThread
{
    void execCrash ()
    {
        std::cout << "Prepare for crash..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        VoidFunction f{nullptr};
        f();
    }

public:

    void start ()
    {
        std::thread t1 (&CrashThread::execCrash, this);
        t1.join();

    }
};

int main( )
{
    //signal(SIGSEGV, sigfaultHandler );

    bt_init_accessor(&acc, BT_SELF);
    bt_load_memmap(&acc, &memmap);

    CrashThread test;

    test.start();

    return 0;
}
