#include <cstdio>
#include <fcntl.h>
#include <sys/procfs.h>

struct dinfo_s {
    procfs_debuginfo    info;
    char                pathbuffer[PATH_MAX]; /* 1st byte is
                                                 info.path[0] */
};

int main( )
{
    struct dinfo_s  dinfo;

    auto fd = open ("/proc/968134700/as", O_RDONLY|O_NONBLOCK);
    auto status = devctl(fd, DCMD_PROC_MAPDEBUG_BASE, &dinfo,
                    sizeof(dinfo), NULL);

    printf("name is %s status: %d\n", dinfo.info.path, status);

    return 0;
}
