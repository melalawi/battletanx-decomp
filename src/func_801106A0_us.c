#ifdef NON_MATCHING
#include "span_1000/code_801106A0.h"
#include "types.h"

/* Canonical first argument is the O32 source-address word. Fast paths use
 * measured byte/halfword/word buffer elements only after alignment checks;
 * these are memory-copy arrays, not views of an unknown object layout. */
void *func_801106A0_us(s32 source_word, void *destination, s32 length)
{
    s8 *src = (s8 *)source_word;
    s8 *dst = (s8 *)destination;
    s8 *end;
    s32 alignment;
    s32 *words;
    s16 *halfwords;
    s8 byte;
    s16 half;
    s32 w0, w1, w2, w3, w4, w5, w6, w7;

    if (length == 0 || source_word == (s32)destination) return destination;
    if ((s32)destination < source_word ||
        (s32)destination >= source_word + length) {
        if (length < 16 || ((u32)src & 3) != ((u32)dst & 3))
            goto forward_bytes;
        alignment = (u32)src & 3;
        if (alignment != 0) {
            if (alignment == 1) {
                byte = src[0];
                src++;
                half = *(s16 *)src;
                src += 2;
                dst++;
                halfwords = (s16 *)dst;
                dst += 2;
                length -= 3;
                dst[-3] = byte;
                halfwords[0] = half;
            } else if (alignment == 2) {
                half = *(s16 *)src;
                src += 2;
                halfwords = (s16 *)dst;
                dst += 2;
                length -= 2;
                halfwords[0] = half;
            } else {
                byte = src[0];
                src++;
                dst++;
                length--;
                dst[-1] = byte;
            }
        }
        while (length >= 32) {
            words = (s32 *)src;
            w0 = words[0]; w1 = words[1]; w2 = words[2]; w3 = words[3];
            w4 = words[4]; w5 = words[5]; w6 = words[6]; w7 = words[7];
            src += 32;
            dst += 32;
            length -= 32;
            words = (s32 *)dst;
            words[-8] = w0; words[-7] = w1; words[-6] = w2; words[-5] = w3;
            words[-4] = w4; words[-3] = w5; words[-2] = w6; words[-1] = w7;
        }
        while (length >= 16) {
            words = (s32 *)src;
            w0 = words[0]; w1 = words[1]; w2 = words[2]; w3 = words[3];
            src += 16;
            dst += 16;
            length -= 16;
            words = (s32 *)dst;
            words[-4] = w0; words[-3] = w1; words[-2] = w2; words[-1] = w3;
        }
        while (length >= 4) {
            w0 = *(s32 *)src;
            src += 4;
            dst += 4;
            length -= 4;
            words = (s32 *)dst;
            words[-1] = w0;
        }
forward_bytes:
        if (length != 0) {
            end = src + length;
            do {
                byte = src[0];
                src++;
                dst++;
                dst[-1] = byte;
            } while (src != end);
        }
        return destination;
    }

    src += length;
    dst += length;
    if (length < 16 || ((u32)src & 3) != ((u32)dst & 3))
        goto backward_bytes;
    alignment = (u32)src & 3;
    if (alignment != 0) {
        if (alignment == 3) {
            byte = src[-1];
            src -= 3;
            half = *(s16 *)src;
            dst -= 3;
            length -= 3;
            dst[2] = byte;
            *(s16 *)dst = half;
        } else if (alignment == 2) {
            src -= 2;
            half = *(s16 *)src;
            dst -= 2;
            length -= 2;
            *(s16 *)dst = half;
        } else {
            byte = src[-1];
            src--;
            dst--;
            length--;
            dst[0] = byte;
        }
    }
    while (length >= 32) {
        words = (s32 *)src;
        w0 = words[-1]; w1 = words[-2]; w2 = words[-3]; w3 = words[-4];
        w4 = words[-5]; w5 = words[-6]; w6 = words[-7]; w7 = words[-8];
        src -= 32;
        dst -= 32;
        length -= 32;
        words = (s32 *)dst;
        words[7] = w0; words[6] = w1; words[5] = w2; words[4] = w3;
        words[3] = w4; words[2] = w5; words[1] = w6; words[0] = w7;
    }
    while (length >= 16) {
        words = (s32 *)src;
        w0 = words[-1]; w1 = words[-2]; w2 = words[-3]; w3 = words[-4];
        src -= 16;
        dst -= 16;
        length -= 16;
        words = (s32 *)dst;
        words[3] = w0; words[2] = w1; words[1] = w2; words[0] = w3;
    }
    while (length >= 4) {
        words = (s32 *)src;
        w0 = words[-1];
        src -= 4;
        dst -= 4;
        length -= 4;
        *(s32 *)dst = w0;
    }
backward_bytes:
    if (length != 0) {
        src--;
        dst--;
        end = src - length;
        do {
            byte = src[0];
            src--;
            dst--;
            dst[1] = byte;
        } while (src != end);
    }
    return destination;
}
#endif /* NON_MATCHING */
