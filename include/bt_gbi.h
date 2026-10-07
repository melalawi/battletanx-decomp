#ifndef BT_GBI_H
#define BT_GBI_H
#include "gfx.h"

/* Legacy F3D/F3DEX command fields, using the shared eight-byte Gfx ABI.
 * Encoding reference: https://github.com/glankk/n64/blob/master/include/n64/gbi.h
 * These macros expose the commands used by the bitmap text renderer. */
#define G_IM_FMT_IA 3
#define G_IM_SIZ_8b 1
#define G_TX_LOADTILE 7
#define G_TX_RENDERTILE 0
#define G_TX_CLAMP 2
#define G_TX_NOMASK 0
#define G_TX_NOLOD 0
#define BT_GBI_BITS(v, n, s) (((u32)(v) & ((1U << (n)) - 1U)) << (s))
#define BT_GBI_WRITE(pkt, first, second) do { \
    Gfx *bt_gfx = (pkt); \
    bt_gfx->words.w0 = (first); \
    bt_gfx->words.w1 = (second); \
} while (0)
#define gDPSetPrimColor(pkt, m, l, r, g, b, a) \
    BT_GBI_WRITE(pkt, 0xFA000000U | BT_GBI_BITS(m,8,8) | BT_GBI_BITS(l,8,0), \
        BT_GBI_BITS(r,8,24) | BT_GBI_BITS(g,8,16) | BT_GBI_BITS(b,8,8) | BT_GBI_BITS(a,8,0))
#define gDPSetTextureImage(pkt, fmt, siz, width, image) \
    BT_GBI_WRITE(pkt, 0xFD000000U | BT_GBI_BITS(fmt,3,21) | BT_GBI_BITS(siz,2,19) | \
        BT_GBI_BITS((width)-1,12,0), (u32)(image))
#define gDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt, maskt, shiftt, cms, masks, shifts) \
    BT_GBI_WRITE(pkt, 0xF5000000U | BT_GBI_BITS(fmt,3,21) | BT_GBI_BITS(siz,2,19) | \
        BT_GBI_BITS(line,9,9) | BT_GBI_BITS(tmem,9,0), \
        BT_GBI_BITS(tile,3,24) | BT_GBI_BITS(palette,4,20) | BT_GBI_BITS(cmt,2,18) | \
        BT_GBI_BITS(maskt,4,14) | BT_GBI_BITS(shiftt,4,10) | BT_GBI_BITS(cms,2,8) | \
        BT_GBI_BITS(masks,4,4) | BT_GBI_BITS(shifts,4,0))
#define gDPLoadSync(pkt) BT_GBI_WRITE(pkt, 0xE6000000U, 0)
#define gDPPipeSync(pkt) BT_GBI_WRITE(pkt, 0xE7000000U, 0)
#define BT_GBI_TILE_RECT(pkt, op, tile, uls, ult, lrs, lrt) \
    BT_GBI_WRITE(pkt, (op) | BT_GBI_BITS(uls,12,12) | BT_GBI_BITS(ult,12,0), \
        BT_GBI_BITS(tile,3,24) | BT_GBI_BITS(lrs,12,12) | BT_GBI_BITS(lrt,12,0))
#define gDPLoadTile(pkt, tile, uls, ult, lrs, lrt) \
    BT_GBI_TILE_RECT(pkt, 0xF4000000U, tile, uls, ult, lrs, lrt)
#define gDPSetTileSize(pkt, tile, uls, ult, lrs, lrt) \
    BT_GBI_TILE_RECT(pkt, 0xF2000000U, tile, uls, ult, lrs, lrt)
#define gSPTextureRectangle(pkt, ulx, uly, lrx, lry, tile, s, t, dsdx, dtdy) do { \
    Gfx *bt_rect = (pkt); \
    bt_rect[0].words.w0 = 0xE4000000U | BT_GBI_BITS(lrx,12,12) | BT_GBI_BITS(lry,12,0); \
    bt_rect[0].words.w1 = BT_GBI_BITS(tile,3,24) | BT_GBI_BITS(ulx,12,12) | BT_GBI_BITS(uly,12,0); \
    bt_rect[1].words.w0 = 0xB4000000U; \
    bt_rect[1].words.w1 = BT_GBI_BITS(s,16,16) | BT_GBI_BITS(t,16,0); \
    bt_rect[2].words.w0 = 0xB3000000U; \
    bt_rect[2].words.w1 = BT_GBI_BITS(dsdx,16,16) | BT_GBI_BITS(dtdy,16,0); \
} while (0)
#define gTexRect(pkt, ulx, uly, lrx, lry, tile) \
    BT_GBI_WRITE(pkt, 0xE4000000U | BT_GBI_BITS(lrx,12,12) | BT_GBI_BITS(lry,12,0), \
        BT_GBI_BITS(tile,3,24) | BT_GBI_BITS(ulx,12,12) | BT_GBI_BITS(uly,12,0))
#define gDPHalf1(pkt, value) BT_GBI_WRITE(pkt, 0xB4000000U, (u32)(value))
#define gDPHalf2(pkt, value) BT_GBI_WRITE(pkt, 0xB3000000U, (u32)(value))
#endif
