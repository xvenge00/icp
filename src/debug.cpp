/**
 * @file debug.cpp
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 */

#include <ctype.h>
#include <stdio.h>

void hexdump(void *ptr, int buflen) {
    unsigned char *buf = (unsigned char *)ptr;
    int i, j;

    for (i = 0; i < buflen; i += 16) {
        fprintf(stderr, "%06x: ", i);

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                fprintf(stderr, "%02x ", buf[i + j]);
            else
                fprintf(stderr, "   ");

        fprintf(stderr, " ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                fprintf(stderr, "%c", isprint(buf[i + j]) ? buf[i + j] : '.');

        fprintf(stderr, "\n");
    }
}
