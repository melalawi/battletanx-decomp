#include "span_1000/code_801153B0.h"
#include "types.h"

struct Ctx;
typedef struct Ctx Ctx;
typedef struct Header Header;

struct Header;





struct Ctx {
    char pad_0[4];
    int unk_4;
    int unk_8;
    char pad_c[0x65 - 0xC];
    unsigned char unk_65;
};
struct Header {
    int unk_0;
    int unk_4;
    unsigned long long unk_8;
    unsigned long long unk_10;
    unsigned short unk_18;
    unsigned char unk_1A;
    unsigned char unk_1B;
    short unk_1C;
    short unk_1E;
};

/* Sizes a memory card by writing a marked, inverted page pattern to page after page
 * and reading it back, stops at the first page that does not read back or that
 * aliases page 0, then fills in the caller's header from the template, writes it to
 * four pages and verifies the first 0x20 bytes of the readback.
 * lbu/sb fix 0x65 of the context, 0x1A and 0x1B of the header and both temporary
 * buffers as unsigned bytes; lhu/sh with the andi 0xFFFE mask fixes 0x18 as an
 * unsigned short; every other field is a word. */





extern int func_8011609C(Ctx *ctx);
extern int func_80112130(void);
extern int func_80114190(int a, int b, int mode, unsigned char *buf);
extern int func_80113E10(int a, int b, unsigned short page, void *buf, int mode);
extern void func_8011540C(Header *h, short *a, short *b);

int func_80115474(Ctx *ctx, Header *src, Header *dst) {
    int ret;
    unsigned char work[0x20];
    unsigned char read[0x20];
    char flag;
    int i;
    int page;
    unsigned short cmds[4];

    ret = 0;
    flag = 0;
    if (ctx->unk_65 != 0) {
        ctx->unk_65 = 0;
        ret = func_8011609C(ctx);
        if (ret != 0) {
            return ret;
        }
    }
    dst->unk_0 = -1;
    dst->unk_4 = func_80112130();
    dst->unk_8 = src->unk_8;
    dst->unk_10 = src->unk_10;
    page = 0;
    do {
        ctx->unk_65 = page;
        ret = func_8011609C(ctx);
        if (ret != 0) {
            return ret;
        }
        ret = func_80114190(ctx->unk_4, ctx->unk_8, 0, work);
        if (ret != 0) {
            return ret;
        }
        work[0] = page | 0x80;
        for (i = 1; i < 0x20; i++) {
            work[i] = ~work[i];
        }
        ret = func_80113E10(ctx->unk_4, ctx->unk_8, 0, work, 0);
        if (ret != 0) {
            return ret;
        }
        ret = func_80114190(ctx->unk_4, ctx->unk_8, 0, read);
        if (ret != 0) {
            return ret;
        }
        for (i = 0; i < 0x20; i++) {
            if (read[i] != work[i]) {
                break;
            }
        }
        if (i != 0x20) {
            break;
        }
        if (page > 0) {
            ctx->unk_65 = 0;
            ret = func_8011609C(ctx);
            if (ret != 0) {
                return ret;
            }
            ret = func_80114190(ctx->unk_4, ctx->unk_8, 0, work);
            if (ret != 0) {
                return ret;
            }
            if (work[0] != 0x80) {
                break;
            }
        }
        page++;
    } while (page < 0x3E);
    ctx->unk_65 = 0;
    ret = func_8011609C(ctx);
    if (ret != 0) {
        return ret;
    }
    if (page > 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    dst->unk_18 = (src->unk_18 & 0xFFFE) | flag;
    dst->unk_1A = page;
    dst->unk_1B = src->unk_1B;
    func_8011540C(dst, &dst->unk_1C, &dst->unk_1E);
    cmds[0] = 1;
    cmds[1] = 3;
    cmds[2] = 4;
    cmds[3] = 6;
    for (i = 0; i < 4; i++) {
        ret = func_80113E10(ctx->unk_4, ctx->unk_8, cmds[i], dst, 1);
        if (ret != 0) {
            return ret;
        }
    }
    ret = func_80114190(ctx->unk_4, ctx->unk_8, 1, work);
    if (ret != 0) {
        return ret;
    }
    for (i = 0; i < 0x20; i++) {
        if (work[i] != ((unsigned char *) dst)[i]) {
            return 0xA;
        }
    }
    return 0;
}
