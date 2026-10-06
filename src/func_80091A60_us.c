#ifdef NON_MATCHING
#include "span_1000/code_80091A60.h"
#include "types.h"
#include "n64sdk.h"


extern void *func_801106A0_us(s32, void *, s32);
void func_80091A60_us(s32 fraction, void *first_arg,
                     s32 second_word, s32 output_word)
{
    Gfx *first = (Gfx *)first_arg;
    Gfx *second = (Gfx *)second_word;
    Gfx *command;
    Gfx *other_command;
    InterpVertex *a;
    InterpVertex *b;
    InterpVertex *out;
    s32 source_word;
    s32 offset;
    u16 count;
    s32 i;
    if (fraction == 0) {
        for (command = first;
             command->words.w0 != ((u32)0xB8 << 24); command++) {
            if ((command->words.w0 >> 24) == 0x04) {
                source_word = command->words.w1;
                offset = source_word - (s32)first;
                count = (command->words.w0 & 0xFFFF) >> 10;
                func_801106A0_us(source_word, (void *)(output_word + offset),
                                 count * sizeof(InterpVertex));
            }
        }
    } else if (fraction == 0x100) {
        for (command = first, other_command = second;
             command->words.w0 != ((u32)0xB8 << 24);
             command++, other_command++) {
            if ((other_command->words.w0 >> 24) == 0x04) {
                source_word = other_command->words.w1;
                offset = source_word - second_word;
                count = (other_command->words.w0 & 0xFFFF) >> 10;
                func_801106A0_us(source_word, (void *)(output_word + offset),
                                 count * sizeof(InterpVertex));
            }
        }
    } else {
        for (command = first;
             command->words.w0 != ((u32)0xB8 << 24); command++) {
            if ((command->words.w0 >> 24) == 0x04) {
                source_word = command->words.w1;
                offset = source_word - (s32)first;
                count = (command->words.w0 & 0xFFFF) >> 10;
                a = (InterpVertex *)source_word;
                b = (InterpVertex *)(second_word + offset);
                out = (InterpVertex *)(output_word + offset);
                for (i = 0; i < count; i++) {
                    out->v.position[0] = a->v.position[0] +
                        (((b->v.position[0] - a->v.position[0]) * fraction) >> 8);
                    out->v.position[1] = a->v.position[1] +
                        (((b->v.position[1] - a->v.position[1]) * fraction) >> 8);
                    out->v.position[2] = a->v.position[2] +
                        (((b->v.position[2] - a->v.position[2]) * fraction) >> 8);
                    out->v.color[0] = a->v.color[0] +
                        (((b->v.color[0] - a->v.color[0]) * fraction) >> 8);
                    out->v.color[1] = a->v.color[1] +
                        (((b->v.color[1] - a->v.color[1]) * fraction) >> 8);
                    out->v.color[2] = a->v.color[2] +
                        (((b->v.color[2] - a->v.color[2]) * fraction) >> 8);
                    a++;
                    b++;
                    out++;
                }
            }
        }
    }
}
#endif /* NON_MATCHING */
