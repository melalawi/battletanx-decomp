#include "span_1000/code_800ABFD0.h"
#include "abi.h"
#include "bt_gbi.h"
#include "common/types_d507c48987bb.h"
#include "types.h"
#include "gfx.h"
#include "menu_render.h"
#include "gbi.h"

extern Gfx *D_803276D4;
extern u8 D_803276E0;
extern u8 D_80327B20;
extern u8 D_80327B21;
extern s32 D_80327B34;
extern char D_800731C0[];
extern char D_800731CC[];
extern s32 D_80125794;
extern char D_801326C4[];
extern char D_80132704[];
extern char D_8013273C[];
extern char D_80132754[];
extern char D_801329C8[];
extern char D_80132A04[];
extern char D_80132A34[];
extern char D_80132A78[];
extern char D_80132AA8[];
extern u8 D_803276E1;
extern s32 D_803276F0;
extern s32 D_80327708;
extern u8 D_8032770C;
extern s32 D_80327718;
extern s32 D_80327730;
extern s32 D_80327734;
extern s32 D_80327760;
extern s32 D_80327764;
extern s32 D_80327790;
extern u8 D_80327794;
extern u8 D_80327795;
extern u8 D_80327796;
extern u8 D_803277C8;
extern u8 D_803277C9;
extern u8 D_803277CA;
extern u8 D_803277CB;
extern s32 D_803277CC;
extern s32 D_803277DC;
extern u8 D_80327808;
extern u8 D_80327809;
extern u8 D_8032780A;
extern u8 D_8032780B;
extern s32 D_8032780C;
extern s32 D_80327810;
extern s32 D_80327814;
extern s32 D_80327818;
extern u8 D_80327848;
extern u8 D_80327849;
extern u8 D_8032784A;
extern u8 D_8032784B;
extern s32 D_8032784C;
extern s32 D_80327850;
extern s32 D_80327854;
extern s32 D_80327858;
extern s32 D_80327878;
extern s32 D_8032787C;
extern s32 D_80327880;
extern u8 D_803278B8;
extern u8 D_803278B9;
extern u8 D_803278BA;
extern u8 D_803278BB;
extern s32 D_803278BC;
extern s32 D_803278D8;
extern s32 D_803278F0;
extern s32 D_803278F4;
extern s32 D_803278F8;
extern u8 D_80327920;
extern u8 D_80327921;
extern u8 D_80327922;
extern u8 D_80327923;
extern s32 D_80327948;
extern s32 D_8032794C;
extern s32 D_80327950;
extern u8 D_80327970;
extern u8 D_80327971;
extern u8 D_80327972;
extern s32 D_80327974;
extern s32 D_80327978;
extern u8 D_803279D8;
extern u8 D_803279D9;
extern u8 D_803279DA;
extern u8 D_803279DB;
extern u8 D_803279DC;
extern s32 D_803279E0;
extern s32 D_803279E4;
extern u8 D_803279E8;
extern u8 D_803279E9;
extern s32 D_80327A08;
extern s32 D_80327A0C;
extern s32 D_80327A10;
extern u64 D_80327A38;
extern s32 D_80327A50;
extern s32 D_80327A68;
extern s32 D_80327A6C;
extern s32 D_80327A70;
extern u8 D_80327A90;
extern u8 D_80327A91;
extern u8 D_80327A92;
extern u8 D_80327AA0;
extern u8 D_80327AA1;
extern s32 D_80327AB0;
extern u8 D_80327AD8;
extern u8 D_80327AD9;
extern u8 D_80327ADA;
extern s32 D_80327AF8;
extern s32 D_80327AFC;
extern s32 D_80327B00;
extern s32 D_80327B04;
extern s32 D_80327B08;
extern u8 D_80327B22;
extern u8 D_80327B23;
extern u8 D_80327B24;
extern s32 D_80327B30;
extern s32 D_80327B38;
extern u64 D_80145DA0;
extern u64 D_80327B28;
extern u64 D_80327AE8;
extern u64 D_80327AC0;
extern u64 D_80327B18;
extern u64 D_80327AD0;
extern u64 D_80327AF0;
extern u64 D_80327B10;
extern u64 D_80327AC8;
extern u64 D_803279F0;
extern u64 D_80327A20;
extern u64 D_80327990;
extern u64 D_80327A98;
extern u64 D_80327A28;
extern u64 D_80327AB8;
extern u64 D_80327A00;
extern u64 D_80327700;
extern u64 D_80327AA8;
extern u64 D_803279F8;
extern u64 D_803276E8;
extern u64 D_80327AE0;
extern u64 D_80327988;
extern u64 D_803276F8;
extern u64 D_80327A18;
extern u64 D_803277B8;
extern u64 D_803279B0;
extern u64 D_803278B0;
extern u64 D_80327840;
extern u64 D_80327770;
extern u64 D_803279A8;
extern u64 D_80327958;
extern u64 D_80327930;
extern u64 D_803278A0;
extern u64 D_80327828;
extern u64 D_80327798;
extern u64 D_80327740;
extern u64 D_80327870;
extern u64 D_80327758;
extern u64 D_803279D0;
extern u64 D_803279C8;
extern u64 D_803279B8;
extern u64 D_80327838;
extern u64 D_80327968;
extern u64 D_80327750;
extern u64 D_80327778;
extern u64 D_80327780;
extern u64 D_80327980;
extern u64 D_80327868;
extern u64 D_80327820;
extern u64 D_80327830;
extern u64 D_803278A8;
extern u64 D_803277B0;
extern u64 D_80327998;
extern u64 D_803279A0;
extern u64 D_80327860;
extern u64 D_80327890;
extern u64 D_803277A8;
extern u64 D_80327748;
extern u64 D_80327788;
extern u64 D_80327928;
extern u64 D_80327940;
extern u64 D_803277C0;
extern u64 D_80327888;
extern u64 D_80327898;
extern u64 D_80327938;
extern u64 D_80327768;
extern u64 D_80327960;
extern u64 D_803279C0;
extern u64 D_80327720;
extern u64 D_80327710;
extern u64 D_80327728;
extern u64 D_80327738;
extern u64 D_80327800;
extern u64 D_803277E8;
extern u64 D_803277F0;
extern u64 D_803277F8;
extern u64 D_80327918;
extern u64 D_803278E8;
extern u64 D_80327A60;
extern u64 D_803277E0;
extern u64 D_803278E0;
extern u64 D_80327900;
extern u64 D_80327908;
extern u64 D_80327910;
extern u64 D_80327A58;
extern u64 D_80327A78;
extern u64 D_80327A80;
extern u64 D_80327A88;

void func_800B1520_us(void) {
    char *text;
    u64 now;
    u64 delta;
    f32 ratio;
    f32 fade;
    f32 magnitude;
    s32 temp_f2_11;
    s32 temp_f2_14;
    s32 temp_f2_15;
    s32 temp_f2_18;
    s32 temp_f2_4;
    s32 temp_f2_5;
    s32 temp_f2_6;
    s32 temp_f2_7;
    s32 temp_f2_8;
    s32 temp_f2_9;
    u64 temp_ret_102;
    u64 temp_ret_120;
    u64 temp_ret_122;
    u64 temp_ret_132;
    u64 temp_ret_142;
    u64 temp_ret_14;
    u64 temp_ret_28;
    u64 temp_ret_38;
    u64 temp_ret_48;
    u64 temp_ret_58;
    u64 temp_ret_66;
    u64 temp_ret_80;
    s32 var_a0;
    s32 var_a0_10;
    s32 var_a0_11;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_6;
    s32 var_a0_7;
    s32 var_a0_8;
    s32 var_a0_9;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v1_4;

    func_800F4DFC((struct Shape_func_800B8804_us *)&D_803276D4, 0, 0, 0x140, 0xF0, 0, 0, 0, 0xFF);
    gDPPipeSync(D_803276D4++);
    gDPSetCycleType(D_803276D4++, G_CYC_1CYCLE);
    gDPSetCombineLERP(D_803276D4++, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0);
    gDPSetRenderMode(D_803276D4++, 0x0F0A4000, 0);
    gDPSetTexturePersp(D_803276D4++, G_TP_NONE);
    gDPSetTextureLOD(D_803276D4++, G_TL_TILE);
    gDPSetTextureFilter(D_803276D4++, G_TF_POINT);
    gDPSetTextureConvert(D_803276D4++, G_TC_FILT);
    gDPSetTextureLUT(D_803276D4++, G_TT_RGBA16);
    now = (func_801120A0_us() * 1000000ULL / D_80145DA0);
    func_801054E0(3);
    switch ((u8) D_803276E0) {
    case 0x0:
        if (D_803276E8 < now) {
            D_803276E1 = 0xFF;
        } else {
            delta = D_803276E8 - now;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 2000000.0f;
            ratio = 1.0f - ratio;
            fade = ratio * 255.0f;
            D_803276E1 = (u8) fade;
        }
        if (D_80327700 < now) {
            delta = now - D_80327700;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 2000000.0f;
            D_80327708 = (s32) (ratio * 255.0f);
        }
        if (D_803276F8 < now || D_80327B21 != 0) {
block_50:
block_51:
        D_803276E0 = 1;
        D_80327730 = 0;
        D_8032770C = 0xFF;
        D_80327718 = 0;
        D_80327720 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0xE4E1C0ULL;
        D_80327710 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_80327728 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0xB71B00ULL;
        func_80079BD4_us();
        func_80079BB4_us(0xE);
        func_80079BF4_us((s32) (s16) (D_80125794 << 0xC));
        return;
        } else {
            func_8010698C(&D_803276D4);
            func_8010555C(0xC8, 0xC8, 0xC8, D_803276E1);
            func_8010552C(0, 0x46);
            func_80105A50(&D_803276D4, D_800731C0, 0, 0x140);
            func_800F4DFC((struct Shape_func_800B8804_us *)&D_803276D4, 0, 0, 0x140, 0xF0, 0, 0, 0, D_80327708);
            return;
        }
    case 0x1:
        if (D_80327710 < now) {
            D_8032770C = 0xFF;
        } else {
            delta = D_80327710 - now;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 3000000.0f;
            ratio = 1.0f - ratio;
            fade = ratio * 255.0f;
            D_8032770C = (u8) fade;
        }
        if (D_80327728 < now) {
            delta = now - D_80327728;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 3000000.0f;
            D_80327730 = (s32) (ratio * 255.0f);
        }
        if (D_80327720 < now || D_80327B21 != 0) {
block_77:
block_78:
        D_803276E0 = 2;
        D_80327740 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x4C4B40ULL;
        D_80327748 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x1E8480ULL;
        temp_ret_14 = func_801120A0_us();
        D_80327760 = 0;
        temp_ret_14 = temp_ret_14 * 1000000ULL / D_80145DA0;
        D_80327750 = temp_ret_14 + 0x1E8480ULL;
        D_80327764 = 0xFF;
        D_80327758 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
        func_80079BD4_us();
        func_80079BB4_us(0xD);
        func_80079BF4_us((s32) (s16) (D_80125794 << 0xC));
        return;
        } else {
            func_800AD340_us();
            return;
        }
    case 0x2:
        if (now >= D_80327750) {
            D_80327764 = 0;
        } else {
            delta = D_80327750 - now;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 2000000.0f;
            D_80327764 = (s32) (ratio * 255.0f);
        }
        if (D_80327740 < now || D_80327B21 != 0) {
block_92:
block_93:
        D_803276E0 = 3;
        D_80327790 = 0;
        D_80327768 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x895440ULL;
        D_80327778 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
        D_80327780 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_80327788 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
        temp_ret_28 = func_801120A0_us();
        D_80327734 = 0;
        D_80327796 = 0;
        D_80327795 = 0;
        D_80327794 = 0;
        temp_ret_28 = temp_ret_28 * 1000000ULL / D_80145DA0;
        D_80327770 = temp_ret_28 + 0x5B8D80ULL;
        return;
        } else {
            if (D_80327748 < now) {
                delta = now - D_80327748;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 3000000.0f;
                D_80327760 = (s32) (ratio * 255.0f);
            }
            if (D_80327758 < now) {
                D_80327758 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0xF4240ULL;
                func_800B9C34_us(0x29, 0x3800);
            }
            {
                u64 unused_delta = D_80327738 - now;
                D_80327B28 = unused_delta;
                magnitude = (f32) unused_delta;
            }
            func_800AD5A0_us();
            return;
        }
    case 0x3:
        if (D_80327768 < now || D_80327B21 != 0) {
block_110:
block_111:
        D_803276E0 = 4;
        D_803277CC = 0;
        D_80327798 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x895440ULL;
        D_803277A8 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
        D_803277B0 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_803277B8 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
        temp_ret_38 = func_801120A0_us();
        D_803277CB = 0;
        D_803277CA = 0;
        D_803277C9 = 0;
        D_803277C8 = 0;
        D_803277DC = 0;
        temp_ret_38 = temp_ret_38 * 1000000ULL / D_80145DA0;
        D_803277C0 = temp_ret_38 + 0x5B8D80ULL;
        D_80327B20 = 1;
        D_80327B22 = 1;
        func_80079BD4_us();
        func_80079BB4_us(8);
        func_80079BF4_us((s32) (s16) (D_80125794 << 0xC));
        return;
        } else {
            if (D_80327778 < now) {
                D_80327794 = 0xFF;
            }
            if (D_80327780 < now) {
                D_80327790 = 1;
                D_80327795 = 0xFF;
            }
            if (D_80327788 < now) {
                D_80327790 = 2;
                D_80327796 = 0xFF;
            }
            if (D_80327770 < now) {
                delta = now - D_80327770;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 3000000.0f;
                D_80327734 = (s32) (ratio * 255.0f);
                ratio = (f32) (1.0 - (f64) ratio);
                func_80079BF4_us((s32) (s16) (s32) (ratio * (f32) (D_80125794 << 0xC)));
            }
            func_800AD828_us();
            return;
        }
    case 0x5:
        if (D_803277E0 < now || (D_80327B21 != 0)) {
            D_80327820 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0xB71B00ULL;
            D_80327828 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
            D_80327830 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x3D0900ULL;
            D_80327838 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x7A1200ULL;
            temp_ret_48 = func_801120A0_us();
            D_80327849 = 0;
            D_8032784A = 0;
            D_8032784B = 0;
            temp_ret_48 = temp_ret_48 * 1000000ULL / D_80145DA0;
            D_80327840 = temp_ret_48 + 0x895440ULL;
            D_80327848 = 0xFF;
            D_80327850 = func_800B9C0C_us(D_801326C4);
            D_80327854 = func_800B9C0C_us(D_80132704);
            D_80327858 = func_800B9C0C_us(D_8013273C);
            D_803276E0 = 6;
            D_8032784C = 0;
            D_80327B30 = 0;
            if (D_80327B38 != -1) {
                func_800798C0(D_80327B38);
                D_80327B38 = -1;
            }
            if (D_80327B34 != -1) {
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            func_800B9C34_us(0x27, 0x7000);
            D_80327B38 = func_800B9C34_us(0x28, 0x7000);
            D_80327B34 = func_800B9C34_us(0x24, 0x7000);
            return;
        }
        if (D_80327800 < now) {
            delta = now - D_80327800;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 3000000.0f;
            fade = ratio * 255.0f;
            D_8032780B = (u8) fade;
        }
        if (D_803277E8 < now) {
            D_80327808 = 0xFF;
            delta = now - D_803277E8;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            var_a0_2 = D_80327810;
            temp_f2_4 = (s32) (magnitude / 66666.0f);
            D_80327B30 = temp_f2_4;
            if (temp_f2_4 < var_a0_2) {
                var_a0_2 = temp_f2_4;
            }
            D_80327B30 = var_a0_2;
            if ((D_8032780C == 0) && (var_a0_2 == D_80327810) && (D_80327B34 != -1)) {
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            var_v0 = D_80327B30;
            if (var_v0 <= 0) {
                var_v0 = 1;
            }
            D_80327B30 = var_v0;
        }
        if (D_803277F0 < now) {
            if (D_8032780C == 0) {
                D_80327B34 = func_800B9C34_us(0x24, 0x7000);
                D_8032780C = 1;
            }
            D_80327809 = 0xFF;
            delta = now - D_803277F0;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            var_a0_3 = D_80327814;
            temp_f2_5 = (s32) (magnitude / 66666.0f);
            D_80327B30 = temp_f2_5;
            if (temp_f2_5 < var_a0_3) {
                var_a0_3 = temp_f2_5;
            }
            D_80327B30 = var_a0_3;
            if ((D_8032780C == 1) && (var_a0_3 == D_80327814) && (D_80327B34 != -1)) {
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            var_v0_2 = D_80327B30;
            if (var_v0_2 <= 0) {
                var_v0_2 = 1;
            }
            D_80327B30 = var_v0_2;
        }
        if (D_803277F8 < now) {
            if (D_8032780C == 1) {
                D_80327B34 = func_800B9C34_us(0x24, 0x7000);
            }
            D_8032780C = 2;
            D_8032780A = 0xFF;
            delta = now - D_803277F8;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            var_a0_4 = D_80327818;
            temp_f2_6 = (s32) (magnitude / 66666.0f);
            D_80327B30 = temp_f2_6;
            if (temp_f2_6 < var_a0_4) {
                var_a0_4 = temp_f2_6;
            }
            D_80327B30 = var_a0_4;
            if ((var_a0_4 == D_80327818) && (D_80327B34 != -1)) {
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            var_v0_3 = D_80327B30;
            if (var_v0_3 <= 0) {
                var_v0_3 = 1;
            }
            D_80327B30 = var_v0_3;
        }
        func_800ADD70_us();
        return;
    case 0x6:
        if (D_80327820 < now || (D_80327B21 != 0)) {
            D_80327868 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
            D_80327860 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x4C4B40ULL;
            D_80327870 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
            D_80327878 = func_800B9C0C_us(D_80132754);
            D_803276E0 = 7;
            if (D_80327B34 != -1) {
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            if (D_80327B38 != -1) {
                func_800798C0(D_80327B38);
                D_80327B38 = -1;
            }
            func_80079BD4_us();
            func_80079BB4_us(0xD);
            func_80079BF4_us((s32) (s16) (D_80125794 << 0xC));
            return;
        }
        if (D_80327828 < now) {
            D_80327848 = 0xFF;
            delta = now - D_80327828;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            var_a0_5 = D_80327850;
            temp_f2_7 = (s32) (magnitude / 66666.0f);
            D_80327B30 = temp_f2_7;
            if (temp_f2_7 < var_a0_5) {
                var_a0_5 = temp_f2_7;
            }
            D_80327B30 = var_a0_5;
            var_v1_4 = var_a0_5;
            if (var_v1_4 <= 0) {
                var_v1_4 = 1;
            }
            D_80327B30 = var_v1_4;
            if ((D_8032784C == 0) && (var_v1_4 == D_80327850) && (D_80327B34 != -1)) {
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
        }
        if (D_80327830 < now) {
            if (D_8032784C == 0) {
                func_800B9C34_us(0x27, 0x7000);
                D_80327B34 = func_800B9C34_us(0x24, 0x7000);
                D_8032784C = 1;
            }
            D_80327849 = 0xFF;
            delta = now - D_80327830;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            var_a0_6 = D_80327854;
            temp_f2_8 = (s32) (magnitude / 66666.0f);
            D_80327B30 = temp_f2_8;
            if (temp_f2_8 < var_a0_6) {
                var_a0_6 = temp_f2_8;
            }
            D_80327B30 = var_a0_6;
            if (var_a0_6 <= 0) {
                var_a0_6 = 1;
            }
            D_80327B30 = var_a0_6;
            if ((D_8032784C == 1) && (var_a0_6 == D_80327854) && (D_80327B34 != -1)) {
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
        }
        if (D_80327838 < now) {
            if (D_8032784C == 1) {
                if (D_80327B38 != -1) {
                    func_800798C0(D_80327B38);
                    D_80327B38 = -1;
                }
                D_80327B34 = func_800B9C34_us(0x24, 0x7000);
                D_8032784C = 2;
            }
            D_8032784A = 0xFF;
            delta = now - D_80327838;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            var_a0_7 = D_80327858;
            temp_f2_9 = (s32) (magnitude / 66666.0f);
            D_80327B30 = temp_f2_9;
            if (temp_f2_9 < var_a0_7) {
                var_a0_7 = temp_f2_9;
            }
            D_80327B30 = var_a0_7;
            if (var_a0_7 <= 0) {
                var_a0_7 = 1;
            }
            D_80327B30 = var_a0_7;
            if ((D_8032784C == 2) && (var_a0_7 == D_80327858) && (D_80327B34 != -1)) {
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
        }
        if (D_80327840 < now) {
            delta = now - D_80327840;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 3000000.0f;
            fade = ratio * 255.0f;
            D_8032784B = (u8) fade;
        }
        func_800AE2B8_us();
        return;
    case 0x7:
        if (D_80327860 < now || (D_80327B21 != 0)) {
            D_80327890 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
            temp_ret_58 = func_801120A0_us();
            D_803278BC = 0;
            temp_ret_58 = temp_ret_58 * 1000000ULL / D_80145DA0;
            D_80327888 = temp_ret_58 + 0x895440ULL;
            D_803276E0 = 8;
            D_80327898 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
            D_803278A0 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
            D_803278A8 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
            temp_ret_66 = func_801120A0_us();
            D_803278B9 = 0;
            D_803278BA = 0;
            temp_ret_66 = temp_ret_66 * 1000000ULL / D_80145DA0;
            D_803278B0 = temp_ret_66 + 0x5B8D80ULL;
            D_803278B8 = 0xFF;
            return;
        }
        if (D_80327870 < now) {
            D_80327880 = 0;
        } else {
            delta = D_80327870 - now;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 3000000.0f;
            D_80327880 = (s32) (ratio * 255.0f);
        }
        delta = now - D_80327868;
        D_80327B28 = delta;
        magnitude = (f32) delta;
        var_a0_8 = D_80327878;
        temp_f2_11 = (s32) (magnitude / 66666.0f);
        D_8032787C = temp_f2_11;
        if (temp_f2_11 < var_a0_8) {
            var_a0_8 = temp_f2_11;
        }
        D_8032787C = var_a0_8;
        var_v0_4 = var_a0_8;
        if (var_v0_4 <= 0) {
            var_v0_4 = 1;
        }
        D_8032787C = var_v0_4;
        func_800AE800_us();
        return;
    case 0x8:
        if (D_80327888 < now || D_80327B21 != 0) {
block_297:
block_298:
        D_803276E0 = 9;
        D_80327B23 = 1;
        D_80327B20 = 1;
        D_803278D8 = 0;
        func_80079BD4_us();
        func_80079BB4_us(8);
        func_80079BF4_us((s32) (s16) (D_80125794 << 0xC));
        return;
        } else {
            if (D_803278B0 < now) {
                delta = now - D_803278B0;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 3000000.0f;
                fade = ratio * 255.0f;
                D_803278BB = (u8) fade;
                ratio = (f32) (1.0 - (f64) ratio);
                func_80079BF4_us((s32) (s16) (s32) (ratio * (f32) (D_80125794 << 0xC)));
            }
            if (D_80327898 < now) {
                D_803278B8 = 0xFF;
            }
            if (D_803278A0 < now) {
                D_803278BC = 1;
                D_803278B9 = 0xFF;
            }
            if (D_803278A8 < now) {
                D_803278BC = 2;
                D_803278BA = 0xFF;
            }
            func_800AEA50_us();
            return;
        }
    case 0xA:
        if (D_803278E0 < now || (D_80327B21 != 0)) {
            D_803276E0 = 0xB;
            D_8032794C = func_800B9C0C_us(D_80132A34);
            D_80327930 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
            D_80327928 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x895440ULL;
            D_80327958 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
            D_80327960 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
            D_80327968 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
            D_80327938 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
            temp_ret_80 = func_801120A0_us();
            D_80327970 = 0;
            D_80327971 = 0;
            D_80327972 = 0;
            D_80327948 = 0;
            temp_ret_80 = temp_ret_80 * 1000000ULL / D_80145DA0;
            D_80327940 = temp_ret_80 + 0x5B8D80ULL;
            return;
        }
        if (D_80327918 < now) {
            delta = now - D_80327918;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 3000000.0f;
            fade = ratio * 255.0f;
            D_80327923 = (u8) fade;
        }
        if (D_80327900 < now) {
            D_80327920 = 0xFF;
        }
        if (D_80327908 < now) {
            if (D_803278F0 == 0) {
                D_803278F4 = func_800B9C0C_us(D_801329C8);
                D_803278E8 = now;
                D_803278F0 = 1;
            }
            D_80327921 = 0xFF;
        }
        if (D_80327910 < now) {
            if (D_803278F0 == 1) {
                D_803278F4 = func_800B9C0C_us(D_80132A04);
                D_803278E8 = now;
                D_803278F0 = 2;
            }
            D_80327922 = 0xFF;
        }
        delta = now - D_803278E8;
        D_80327B28 = delta;
        magnitude = (f32) delta;
        var_a0_9 = D_803278F4;
        temp_f2_14 = (s32) (magnitude / 66666.0f);
        D_803278F8 = temp_f2_14;
        if (temp_f2_14 < var_a0_9) {
            var_a0_9 = temp_f2_14;
        }
        D_803278F8 = var_a0_9;
        var_v0_5 = var_a0_9;
        if (var_v0_5 <= 0) {
            var_v0_5 = 1;
        }
        D_803278F8 = var_v0_5;
        func_800AEF98_us();
        return;
    case 0xB:
        if (D_80327928 < now || D_80327B21 != 0) {
block_369:
block_370:
        D_803276E0 = 0xC;
        D_80327980 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0xE4E1C0ULL;
        D_80327998 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_803279A0 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
        D_803279C0 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
        D_803279A8 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x895440ULL;
        D_803279C8 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_803279B0 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0xB71B00ULL;
        D_803279D0 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
        D_803279B8 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x895440ULL;
        D_80327988 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x014FB180ULL;
        temp_ret_102 = func_801120A0_us();
        D_803279D8 = 0;
        D_803279DC = 0;
        D_803279DB = 0;
        D_803279DA = 0;
        D_803279D9 = 0;
        D_803279E8 = 0;
        temp_ret_102 = temp_ret_102 * 1000000ULL / D_80145DA0;
        D_80327990 = temp_ret_102 + 0x1E8480ULL;
        D_803279E9 = 1;
        func_80079BD4_us();
        func_80079BB4_us(0xF);
        func_80079BF4_us((s32) (s16) (D_80125794 << 0xC));
        return;
        } else {
            if (D_80327940 < now) {
                delta = now - D_80327940;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 3000000.0f;
                D_80327978 = (s32) (ratio * 255.0f);
            }
            if (D_80327938 < now) {
                D_80327974 = 0;
            } else {
                delta = D_80327938 - now;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 3000000.0f;
                D_80327974 = (s32) (ratio * 255.0f);
            }
            if (D_80327958 < now) {
                D_80327970 = 0xFF;
            }
            if (D_80327960 < now) {
                if (D_80327948 == 0) {
                    D_8032794C = func_800B9C0C_us(D_80132A78);
                    D_80327930 = now;
                    D_80327948 = 1;
                }
                D_80327971 = 0xFF;
            }
            if (D_80327968 < now) {
                if (D_80327948 == 1) {
                    D_8032794C = func_800B9C0C_us(D_80132AA8);
                    D_80327930 = now;
                    D_80327948 = 2;
                }
                D_80327972 = 0xFF;
            }
            delta = now - D_80327930;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            var_a0_10 = D_8032794C;
            temp_f2_15 = (s32) (magnitude / 66666.0f);
            D_80327950 = temp_f2_15;
            if (temp_f2_15 < var_a0_10) {
                var_a0_10 = temp_f2_15;
            }
            D_80327950 = var_a0_10;
            var_v0_6 = var_a0_10;
            if (var_v0_6 <= 0) {
                var_v0_6 = 1;
            }
            D_80327950 = var_v0_6;
            func_800AF534_us();
            return;
        }
    case 0xC:
        if (D_80327980 < now || D_80327B21 != 0) {
block_415:
block_416:
        D_803276E0 = -1;
        D_80327708 = 0;
        D_803276E1 = 0xFF;
        D_803276F0 = 0;
        D_803276F8 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x6ACFC0ULL;
        D_803276E8 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x1E8480ULL;
        D_80327700 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x4C4B40ULL;
        return;
        } else {
            if (D_80327990 < now) {
                D_803279E4 = 0;
            } else {
                delta = D_80327990 - now;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 2000000.0f;
                D_803279E4 = (s32) (ratio * 255.0f);
            }
            if (D_80327998 < now) {
                D_803279D8 = 0;
            } else {
                delta = D_80327998 - now;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 3000000.0f;
                fade = ratio * 255.0f;
                D_803279D8 = (u8) fade;
            }
            if ((D_803279D9 != 0) && (D_803279E9 != 0)) {
                D_803279E8 = 1;
                func_800B9C34_us(0xB, 0x7000);
            }
            if (D_803279A0 < now || now < D_803279C0) {
                D_803279D9 = 0;
            } else {
                delta = now - D_803279C0;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 6000000.0f;
                if ((f64) ratio < 0.5) {
                    D_803279D9 = (u8) (ratio * 255.0f);
                } else {
                    D_803279D9 = (u8) ((1.0f - ratio) * 255.0f);
                }
            }
            if (D_803279A8 < now || now < D_803279C8) {
                D_803279DA = 0;
            } else {
                delta = now - D_803279C8;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 6000000.0f;
                if ((f64) ratio < 0.5) {
                    D_803279DA = (u8) (ratio * 255.0f);
                } else {
                    D_803279DA = (u8) ((1.0f - ratio) * 255.0f);
                }
            }
            if (D_803279B0 < now || now < D_803279D0) {
                D_803279DB = 0;
            } else {
                delta = now - D_803279D0;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 6000000.0f;
                if ((f64) ratio < 0.5) {
                    D_803279DB = (u8) (ratio * 255.0f);
                } else {
                    D_803279DB = (u8) ((1.0f - ratio) * 255.0f);
                }
            }
            if (D_80327988 < now) {
                delta = now - D_80327988;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / -7000000.0f;
                D_803279E0 = (s32) (ratio * 255.0f);
            }
            func_800AFB08_us();
            return;
        }
    case 0xFF:
        if (D_803276E8 < now) {
            D_803276E1 = 0xFF;
        } else {
            delta = D_803276E8 - now;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 2000000.0f;
            ratio = 1.0f - ratio;
            fade = ratio * 255.0f;
            D_803276E1 = (u8) fade;
        }
        if (D_80327700 < now) {
            delta = now - D_80327700;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 2000000.0f;
            D_80327708 = (s32) (ratio * 255.0f);
        }
        if (D_803276F8 < now || D_80327B21 != 0) {
block_530:
block_531:
        D_803276E0 = 0xD;
        D_803279F0 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x895440ULL;
        D_80327A00 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x1E8480ULL;
        D_803279F8 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x5B8D80ULL;
        D_80327A18 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
        D_80327A20 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x1E8480ULL;
        temp_ret_120 = func_801120A0_us();
        D_80327A08 = 0;
        D_80327A0C = 0;
        temp_ret_120 = temp_ret_120 * 1000000ULL / D_80145DA0;
        D_80327A28 = temp_ret_120 + 0x3D0900ULL;
        return;
        } else {
            func_8010698C(&D_803276D4);
            func_8010555C(0xC8, 0xC8, 0xC8, D_803276E1);
            func_8010552C(0, 0x46);
            func_80105A50(&D_803276D4, D_800731CC, 0, 0x140);

            func_800F4DFC((struct Shape_func_800B8804_us *)&D_803276D4, 0, 0, 0x140, 0xF0, 0, 0, 0, D_80327708);
            return;
        }
    case 0xD:
        if (now >= D_80327A00) {
            D_80327764 = 0;
        } else {
            delta = D_80327A00 - now;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 2000000.0f;
            D_80327A10 = (s32) (ratio * 255.0f);
        }
        if (D_803279F0 < now || D_80327B21 != 0) {
block_546:
block_547:
        D_803276E0 = 0xE;
        D_80327B24 = 1;
        D_80327B20 = 1;
        D_80327A50 = 0;
        D_80327A38 = 6000000ULL;
        return;
        } else {
            if (D_803279F8 < now) {
                delta = now - D_803279F8;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 3000000.0f;
                D_80327A0C = (s32) (ratio * 255.0f);
                ratio = (f32) (1.0 - (f64) ratio);
                func_80079BF4_us((s32) (s16) (s32) (ratio * (f32) (D_80125794 << 0xC)));
            }
            if (D_80327A20 < now) {
                D_80327A08 = 1;
            }
            if (D_80327A28 < now) {
                D_80327A08 = 2;
            }
            func_800B0210_us();
            return;
        }
    case 0xF:
        if (D_80327A58 < now || D_80327B21 != 0) {
block_568:
block_569:
        D_803276E0 = 0x10;
        temp_ret_122 = func_801120A0_us();
        D_80327AA1 = 0;
        temp_ret_122 = temp_ret_122 * 1000000ULL / D_80145DA0;
        D_80327A98 = temp_ret_122 + 0x2DC6C0ULL;
        D_80327AA0 = 0xFF;
        return;
        } else {
            if (D_80327A78 < now) {
                D_80327A90 = 0xFF;
            }
            if (D_80327A80 < now) {
                D_80327A68 = 1;
                D_80327A91 = 0xFF;
            }
            if (D_80327A88 < now) {
                D_80327A68 = 2;
                D_80327A92 = 0xFF;
            }
            delta = now - D_80327A60;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            var_a0_11 = D_80327A6C;
            temp_f2_18 = (s32) (magnitude / 66666.0f);
            D_80327A70 = temp_f2_18;
            if (temp_f2_18 < var_a0_11) {
                var_a0_11 = temp_f2_18;
            }
            D_80327A70 = var_a0_11;
            var_v0_7 = var_a0_11;
            if (var_v0_7 <= 0) {
                var_v0_7 = 1;
            }
            D_80327A70 = var_v0_7;
            func_800B0440_us();
            return;
        }
    case 0x10:
        if (D_80327A98 < now || D_80327B21 != 0) {
block_594:
block_595:
        D_803276E0 = 0x11;
        D_80327AB0 = 0;
        D_80327AA8 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0xA7D8C0ULL;
        D_80327AB8 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
        D_80327AC0 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x2DC6C0ULL;
        D_80327AD0 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x3D0900ULL;
        temp_ret_132 = func_801120A0_us();
        D_80327ADA = 0;
        D_80327AD9 = 0;
        D_80327AD8 = 0;
        temp_ret_132 = temp_ret_132 * 1000000ULL / D_80145DA0;
        D_80327AC8 = temp_ret_132 + 0x5B8D80ULL;
        return;
        } else {
            if (now & 0x1111ULL) {
                D_80327AA0 = 0;
                D_80327AA1 = 0xFF;
            } else {
                D_80327AA0 = 0xFF;
                D_80327AA1 = 0;
            }
            func_800B098C_us();
            return;
        }
    case 0x11:
        if (D_80327AA8 < now || D_80327B21 != 0) {
block_605:
block_606:
        D_80327B20 = 1;
        D_803276E0 = 0x12;
        D_80327AE0 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0xB71B00ULL;
        D_80327AF0 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x1E8480ULL;
        D_80327AE8 = (func_801120A0_us() * 1000000ULL / D_80145DA0) + 0x989680ULL;
        D_80327B10 = (func_801120A0_us() * 1000000ULL / D_80145DA0);
        temp_ret_142 = func_801120A0_us();
        D_80327AF8 = 0;
        D_80327AFC = 0;
        temp_ret_142 = temp_ret_142 * 1000000ULL / D_80145DA0;
        D_80327B18 = temp_ret_142 + 0x5B8D80ULL;
        return;
        } else {
            if (D_80327AC0 < now) {
                D_80327AB0 = 1;
                D_80327AD9 = 0xFF;
            }
            if (D_80327AC8 < now) {
                D_80327AB0 = 2;
                D_80327ADA = 0xFF;
            }
            if (now >= D_80327AC0 && D_80327AD0 >= now) {
                delta = D_80327AD0 - now;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 1000000.0f;
                ratio = 1.0f - ratio;
                fade = ratio * 255.0f;
                D_80327AD9 = (u8) fade;
            }
            func_800B0D1C_us();
            return;
        }
    case 0x12:
        if (D_80327B21 != 0) {
            D_80327AF8 += 1;
        }
        if (now >= D_80327AF0) {
            D_80327B00 = 0;
        } else {
            delta = D_80327AF0 - now;
            D_80327B28 = delta;
            magnitude = (f32) delta;
            ratio = magnitude / 2000000.0f;
            D_80327B00 = (s32) (ratio * 255.0f);
        }
        if (D_80327AE0 < now || D_80327AF8 >= 2) {
            D_80327B20 = 1;
            return;
        } else {
            if (D_80327AE8 < now) {
                delta = now - D_80327AE8;
                D_80327B28 = delta;
                magnitude = (f32) delta;
                ratio = magnitude / 2000000.0f;
                D_80327AFC = (s32) (ratio * 255.0f);
            }
            if (D_80327B10 < now) {
                D_80327B04 = 0xFF;
            }
            if (D_80327B18 < now) {
                D_80327AF8 = 1;
                D_80327B08 = 0xFF;
            }
            func_800B1264_us();
            return;
        }
    }
}
