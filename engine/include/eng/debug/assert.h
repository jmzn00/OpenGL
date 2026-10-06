#ifndef ASSERT_H
#define ASSERT_H

#include <iostream>
#include <eng/core/config.h>

#if defined(_MSC_VER)
#define ENG_DEBUGBREAK() __debugbreak()
#else
#include <signal.h>
#define ENG_DEBUGBREAK() raise(SIGTRAP)
#endif

#ifdef ENG_DEBUG

#define ENG_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "[ENG_ASSERT] " << (message) \
                      << "\nCondition: " << #condition \
                      << "\nFunction : " << __FUNCTION__ \
                      << "\nFile     : " << __FILE__ \
                      << "\nLine     : " << __LINE__ \
                      << std::endl; \
            ENG_DEBUGBREAK(); \
        } \
    } while (0)

#else

#define ENG_ASSERT(condition, message) ((void)0)

#endif

#endif