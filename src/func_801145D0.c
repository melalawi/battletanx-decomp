#include "span_1000/code_80114190.h"
/* func_801145D0 -- eight-bit CRC over 0x20 bytes plus one all-zero flush byte, using the
 * polynomial 0x85. The store widths in the cartridge fix the types: the running value and the
 * polynomial term are single bytes, the byte counter and the bit counter are words.
 */
unsigned char func_801145D0(unsigned char *data) {
    unsigned char crc;
    unsigned char poly;
    int i;
    int bit;

    crc = 0;
    for (i = 0; i < 0x21; i++) {
        for (bit = 7; bit >= 0; bit--) {
            poly = (crc & 0x80) ? 0x85 : 0;
            crc <<= 1;
            if (i == 0x20) {
                crc |= 0;
            } else {
                crc |= (*data & (1 << bit)) ? 1 : 0;
            }
            crc ^= poly;
        }
        data++;
    }
    return crc;
}
