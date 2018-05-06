/**
 * @file debug.h
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 *
 * File containing debbugin macros.
 * They are only compiled if compiler has ICP_DEBUG set.
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

// Perhaps add ICP_COLOR command line option to specify that user wants color
// Almost all of the terminal emulators support them
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Log error(LOGE) is not conditional and is present in every build
// Errors are supposed to be shown in every case
#define LOGE(x)                                                                                                        \
    do {                                                                                                               \
        std::cerr << ANSI_COLOR_RED "ERRO : "                                                                          \
                  << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " ANSI_COLOR_RESET << x    \
                  << std::endl;                                                                                        \
    } while (0)

#ifdef ICP_DEBUG
#define LOGI(x)                                                                                                        \
    do {                                                                                                               \
        std::cerr << ANSI_COLOR_GREEN "INFO : "                                                                        \
                  << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " ANSI_COLOR_RESET << x    \
                  << std::endl;                                                                                        \
    } while (0)
#define LOGD(x)                                                                                                        \
    do {                                                                                                               \
        std::cerr << ANSI_COLOR_BLUE "DEBG : "                                                                         \
                  << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " ANSI_COLOR_RESET << x    \
                  << std::endl;                                                                                        \
    } while (0)
#define DEBUG_COMMAND(x) x

#else /* ifdef ICP_DEBUG */

#define LOGI(x)
#define LOGD(x)
#define DEBUG_COMMAND(x)

#endif /* ICP_DEBUG */

void hexdump(void *ptr, int buflen);
// TODO: Add functions to print basic classes(blocs, schemas,...) to stderr

#endif /* DEBUG_H */
