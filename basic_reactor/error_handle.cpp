//
// Created by parallels on 4/19/18.
//


#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <syslog.h>
#include <cstdarg>

int daemon_proc;

void err_exit(const char *msg) {
    perror(msg);
    exit(1);
}

//static void err_doit(int errnoflag, int level, const char *fmt, va_list ap) {
//    int errno_save, n;
//    char buf[1024+1];
//
//    errno_save = errno;
//
//#ifdef HAVE_VSNPRINTF
//    vsnprintf(buf, 1024, fmt, ap);
//#else
//    vsprintf(buf, fmt, ap);
//#endif
//    n = static_cast<int>(strlen(buf));
//    if (errnoflag)
//        snprintf(buf + n, static_cast<size_t>(1024 - n), ": %s", strerror(errno_save));
//    strcat(buf, "\n");
//
//    if(daemon_proc) {
//        syslog(level, buf);
//    } else {
//        fflush(stdout);
//        fputs(buf, stderr);
//        fflush(stderr);
//    }
//}
//
//void err_msg(const char* fmt) {
//    va_list ap;
//    va_start(ap, fmt);
//    err_doit(0, LOG_INFO, fmt, ap);
//    va_end(ap);
//}