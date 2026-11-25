#ifndef WMGR_HPP
#define WMGR_HPP

#ifdef __cplusplus

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <cstdint>
#include <cstddef>
#include <cctype>

#if defined(__unix__)
    #include <sys/stat.h>
    #include <sys/types.h>

    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>

    #include <sys/stat.h>
#elif defined(_WIN32)
    #include <windows.h>
    #include <winSock2.h>
    #include <ws2tcpip.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <io.h>
#endif

namespace wmgr {
    extern "C" {
        #include <wmgr.h>
    }
}

#endif

#endif