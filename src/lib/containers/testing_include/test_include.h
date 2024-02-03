//
// Created by pinkod on 7/31/25.
//

#ifndef TEST_INCLUDE_H
#define TEST_INCLUDE_H

#define UTIL_BEGIN _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wunused-result\"")

#define UTIL_END _Pragma("GCC diagnostic pop")

// Convenience macro to suppress warning around a single statement:
#define UTIL(stmt)                                                                                                               \
    do {                                                                                                                         \
        UTIL_BEGIN;                                                                                                              \
        stmt;                                                                                                                    \
        UTIL_END;                                                                                                                \
    } while(0)

#endif // TEST_INCLUDE_H
