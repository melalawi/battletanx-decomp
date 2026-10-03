#ifndef UNBAKE_TYPEMAP_H
#define UNBAKE_TYPEMAP_H
#include "gbi.h"
#include "n64sdk.h"
#include "shared/abi.h"
#include "shared/acmd.h"
#include "shared/audio_callbacks.h"
#include "types.h"
#include "shared/callback_queue.h"
#include "shared/func_80077930.h"
#include "shared/func_80078d90.h"
#include "shared/func_800793d0.h"
#include "shared/func_80079efc.h"
#include "shared/func_8007aac0.h"
#include "shared/func_8007d1f8.h"
#include "shared/func_8007d384.h"
#include "shared/func_8007ec38.h"
#include "shared/func_8007ece8.h"
#include "shared/func_8007ee48.h"
#include "shared/func_8007ff68.h"
#include "shared/func_800805dc.h"
#include "shared/func_80091608.h"
#include "shared/func_800916b8.h"
#include "shared/func_800917c4.h"
#include "shared/func_800917d8.h"
#include "shared/func_800949b8.h"
#include "shared/func_80096784.h"
#include "shared/func_80097b7c.h"
#include "shared/func_80097c24.h"
#include "shared/func_80099cd8.h"
#include "shared/func_8009e39c.h"
#include "shared/func_800a2ea4.h"
#include "shared/func_800a3d30.h"
#include "shared/func_800a424c.h"
#include "shared/func_800a4254.h"
#include "shared/func_800a42a4.h"
#include "shared/func_800a42bc.h"
#include "shared/func_800a4d1c.h"
#include "shared/func_800a51e8.h"
#include "shared/func_800a52ac.h"
#include "shared/func_800a59e8.h"
#include "shared/func_800a6e10.h"
#include "shared/func_800a72c8.h"
#include "shared/func_800a74ac.h"
#include "shared/func_800a7550.h"
#include "shared/func_800a76a0.h"
#include "shared/func_800a7d10.h"
#include "shared/func_800a979c.h"
#include "shared/func_800aa280.h"
#include "shared/func_800aa328.h"
#include "shared/func_800ab95c.h"
#include "shared/func_800ddca4.h"
#include "shared/func_800e0b00.h"
#include "shared/func_800e3480.h"
#include "shared/func_800e349c.h"
#include "shared/func_800e34b4.h"
#include "shared/func_800e3c18.h"
#include "shared/func_800e4d44.h"
#include "shared/func_800e566c.h"
#include "shared/func_800e6970_us_calls.h"
#include "shared/func_800e6c14.h"
#include "shared/func_800e6ca4.h"
#include "shared/func_800e9894.h"
#include "shared/func_800e99d4.h"
#include "shared/func_800e9da4.h"
#include "shared/func_800ed810.h"
#include "shared/func_800eebec.h"
#include "shared/func_800eeca0.h"
#include "shared/func_800f3014.h"
#include "shared/func_80109354.h"
#include "shared/func_8010dcd0.h"
#include "shared/func_80115474.h"
#include "shared/func_8011588c.h"
#include "shared/func_80115c80.h"
#include "shared/func_8011954c.h"
#include "shared/func_80119b60.h"
#include "shared/func_80119bb4.h"
#include "shared/func_80119c34.h"
#include "shared/func_80119f70.h"
#include "shared/func_8011a134.h"
#include "shared/func_8011b1a0.h"
#include "shared/func_8011b2a4.h"
#include "shared/func_8011b7bc.h"
struct Shape_func_8011B9E0 {
    int field_0;
};
#include "shared/func_8011b9e0.h"
#include "shared/func_8011c150.h"
#include "shared/func_8011c300.h"
#include "shared/func_8011dc98.h"
#include "shared/func_8011e3f0.h"
#include "shared/func_8011e564.h"
#include "shared/func_8011eca4.h"
#include "shared/func_8011f7f0.h"
#include "shared/gfx.h"
struct Shape_D_80146100_2 {
    unsigned char padding_0[16];
    int field_10;
    unsigned char padding_14[14];
    unsigned char field_22;
    unsigned char padding_23[23];
    short field_3A;
    unsigned char padding_3C[384];
    unsigned char field_1BC;
    unsigned char field_1BD;
    unsigned char field_1BE;
};
struct Shape_D_801B6C00 {
    int field_0;
    unsigned char unknown_4[4];
};
struct Shape_D_803276D4 {
    int field_0;
    unsigned char unknown_4[4];
    int field_8;
    unsigned char unknown_C[4];
    int field_10;
    unsigned char unknown_14[4];
    int field_18;
    unsigned char unknown_1C[4];
    int field_20;
    unsigned char unknown_24[4];
    int field_28;
    unsigned char unknown_2C[4];
    int field_30;
    unsigned char unknown_34[4];
    int field_38;
    unsigned char unknown_3C[4];
    int field_40;
    unsigned char unknown_44[4];
    int field_48;
    unsigned char unknown_4C[4];
    int field_50;
    unsigned char unknown_54[4];
    int field_58;
    int field_5C;
    int field_60;
    unsigned char unknown_64[4];
    int field_68;
    unsigned char unknown_6C[4];
    int field_70;
    unsigned char unknown_74[4];
    int field_78;
    unsigned char unknown_7C[4];
    int field_80;
    unsigned char unknown_84[4];
    int field_88;
    unsigned char unknown_8C[4];
};
struct Shape_D_8037A174 {
    int field_0;
    unsigned char unknown_4[4];
    int field_8;
    unsigned char unknown_C[4];
    int field_10;
    unsigned char unknown_14[4];
    int field_18;
    unsigned char unknown_1C[4];
    int field_20;
    unsigned char unknown_24[4];
    int field_28;
    unsigned char unknown_2C[4];
    int field_30;
    unsigned char unknown_34[4];
    int field_38;
    unsigned char unknown_3C[4];
    int field_40;
    unsigned char unknown_44[4];
    int field_48;
    unsigned char unknown_4C[4];
    int field_50;
    unsigned char unknown_54[4];
    int field_58;
    unsigned char unknown_5C[4];
    int field_60;
    unsigned char unknown_64[4];
    int field_68;
    unsigned char unknown_6C[4];
    int field_70;
    unsigned char unknown_74[4];
    int field_78;
    unsigned char unknown_7C[4];
    int field_80;
    unsigned char unknown_84[4];
    int field_88;
    int field_8C;
    int field_90;
    unsigned char unknown_94[4];
    int field_98;
    int field_9C;
    int field_A0;
    int field_A4;
    int field_A8;
    unsigned char unknown_AC[4];
    int field_B0;
    int field_B4;
    int field_B8;
    unsigned char unknown_BC[4];
    int field_C0;
    int field_C4;
    int field_C8;
    unsigned char unknown_CC[4];
    int field_D0;
    int field_D4;
    int field_D8;
    int field_DC;
    int field_E0;
    unsigned char unknown_E4[4];
    int field_E8;
    unsigned char unknown_EC[4];
    int field_F0;
    int field_F4;
    int field_F8;
    unsigned char unknown_FC[4];
    int field_100;
    int field_104;
    int field_108;
    unsigned char unknown_10C[4];
    int field_110;
    int field_114;
    int field_118;
    unsigned char unknown_11C[4];
    int field_120;
    int field_124;
};
struct Shape_D_803AAD98 {
    unsigned char padding_0[4];
    int field_4;
    unsigned char padding_8[4];
    int field_C;
    unsigned char padding_10[4];
    int field_14;
};
struct Shape_func_8007B280_us {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
    unsigned char field_8;
    unsigned char padding_9[3];
    int field_C;
    int field_10;
    short field_14;
    unsigned char field_16;
    unsigned char field_17;
    unsigned char field_18;
    unsigned char unknown_19[1];
    unsigned char field_1A;
    unsigned char field_1B;
    int field_1C;
    int field_20;
};
struct Shape_func_8007BD24_us {
    unsigned char padding_0[16];
    int field_10;
    unsigned char padding_14[38];
    unsigned short field_3A;
    unsigned char padding_3C[468];
    int field_210;
};
/* Shape_func_8007C770_us: partial shape; common base value:func_800A31C0_us:us:33; size unknown; common base is not a global or a known-signature parameter/return */
struct Shape_func_8007D850_us {
    unsigned char padding_0[192];
    short field_C0;
    unsigned char padding_C2[14];
    unsigned short field_D0;
    unsigned char padding_D2[2];
    int field_D4;
    void * field_D8;
    void * field_DC;
    void * field_E0;
    unsigned char unknown_E4[4];
    unsigned char unknown_E8[4];
    unsigned char unknown_EC[2];
    unsigned char unknown_EE[2];
    unsigned char unknown_F0[2];
    unsigned char unknown_F2[2];
    unsigned char unknown_F4[2];
    unsigned char unknown_F6[1];
    unsigned char unknown_F7[1];
    unsigned char unknown_F8[1];
    unsigned char unknown_F9[1];
    unsigned char padding_FA[2];
    unsigned char unknown_FC[4];
    unsigned char unknown_100[4];
    unsigned char unknown_104[2];
};
/* Shape_func_8007D998_us: partial shape; common base value:func_8007D998_us:us:23; size unknown; common base is not a global or a known-signature parameter/return */
struct Shape_func_8007D998_us_2 {
    unsigned char padding_0[4];
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    unsigned char padding_48[4];
    int field_4C;
    unsigned char padding_50[12];
    int field_5C;
    int field_60;
    unsigned char padding_64[4];
    int field_68;
    int field_6C;
    unsigned char padding_70[4];
    int field_74;
};
struct Shape_func_8007E150_us {
    unsigned char padding_0[192];
    short field_C0;
    short field_C2;
    short field_C4;
    short field_C6;
    int field_C8;
    int field_CC;
    unsigned short field_D0;
    unsigned char padding_D2[2];
    int field_D4;
    void * field_D8;
    void * field_DC;
    void * field_E0;
    unsigned char padding_E4[4];
    void * field_E8;
};
struct Shape_func_8007E41C_us {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
};
struct Shape_func_8007E4F4_us {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
};
struct Shape_func_8008001C_us {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
};
/* Shape_func_800827AC_us: partial shape; common base address:address:us:00000000; size unknown; overlapping, negative or inconsistent observed storage intervals */
struct Shape_func_800827AC_us_2 {
    unsigned char padding_0[1380];
    int field_564;
    int field_568;
    unsigned char padding_56C[4];
    int field_570;
    int field_574;
    int field_578;
    int field_57C;
    int field_580;
    unsigned char padding_584[176];
    int field_634;
    int field_638;
};
struct Shape_func_80085470_us {
    unsigned char padding_0[1384];
    int field_568;
    int field_56C;
    int field_570;
};
/* Shape_func_80085470_us_2: partial shape; common base value:func_80092734_us:us:559; size unknown; common base is not a global or a known-signature parameter/return */
struct Shape_func_80085D84_us {
    float field_0;
    float field_4;
    float field_8;
    float field_C;
    unsigned char padding_10[1376];
    int field_570;
};
struct Shape_func_8008785C_us {
    int field_0;
    int field_4;
    unsigned char padding_8[3600];
    int field_E18;
    unsigned char padding_E1C[512];
    int field_101C;
    int field_1020;
    unsigned char padding_1024[4800];
    int field_22E4;
    int field_22E8;
    unsigned char padding_22EC[28800];
    int field_936C;
    unsigned char padding_9370[4096];
    unsigned char unknown_A370[4];
    int field_A374;
    unsigned char padding_A378[28800];
    int field_113F8;
    unsigned char unknown_113FC[4];
    int field_11400;
    int field_11404;
    unsigned char unknown_11408[4];
    unsigned char unknown_1140C[4];
};
struct Shape_func_8008785C_us_2 {
    void * field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    unsigned char unknown_1C[4];
    int field_20;
    unsigned char unknown_24[4];
    void * field_28;
    unsigned char padding_2C[4];
    int field_30;
    unsigned char padding_34[3600];
    int field_E44;
    unsigned char padding_E48[516];
    int field_104C;
    unsigned char padding_1050[4804];
    int field_2314;
    unsigned char padding_2318[28800];
    int field_9398;
    unsigned char padding_939C[4096];
    int field_A39C;
    int field_A3A0;
    unsigned char padding_A3A4[28804];
    int field_11428;
};
struct Shape_func_80088360_us {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
    unsigned char unknown_8[4];
    unsigned char unknown_C[4];
    float field_10;
    float field_14;
    unsigned char unknown_18[4];
    unsigned char unknown_1C[4];
    unsigned char padding_20[164];
    unsigned char unknown_C4[4];
    unsigned char padding_C8[1180];
    int field_564;
    int field_568;
    int field_56C;
    int field_570;
    int field_574;
    int field_578;
    int field_57C;
    int field_580;
    unsigned char padding_584[176];
    int field_634;
    int field_638;
};
struct Shape_func_8008D768_us {
    unsigned char padding_0[68];
    unsigned short field_44;
    unsigned char padding_46[26];
    int field_60;
    unsigned char padding_64[136];
    void * field_EC;
    unsigned char field_F0;
    unsigned char padding_F1[181];
    unsigned char field_1A6;
    unsigned char padding_1A7[25];
    int field_1C0;
    int field_1C4;
};
/* Shape_func_80092534_us: partial shape; common base param:func_80092734_us:r4; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_80092734_us {
    unsigned char padding_0[36];
    float field_24;
    unsigned char padding_28[4];
    float field_2C;
    unsigned char padding_30[944];
    float field_3E0;
    float field_3E4;
};
struct Shape_func_80092734_us_3 {
    unsigned char padding_0[60];
    int field_3C;
    int field_40;
    int field_44;
};
/* Shape_func_80093080_us: partial shape; common base param:func_8009345C_us:stack16; size unknown; common-base owner ABI is incomplete or conflicting */
/* Shape_func_80093590_us: partial shape; common base param:func_80093A5C_us:stack16; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_80093A5C_us_2 {
    unsigned char padding_0[4];
    int field_4;
};
struct Shape_func_80093D50_us {
    unsigned char padding_0[32];
    int field_20;
    unsigned char padding_24[4];
    int field_28;
};
struct Shape_func_80097DD0_us {
    unsigned char padding_0[32];
    unsigned char unknown_20[2];
    unsigned char field_22;
    unsigned char padding_23[1];
    unsigned char unknown_24[1];
    unsigned char unknown_25[1];
    unsigned char padding_26[6];
    int field_2C;
    int field_30;
    unsigned char padding_34[4];
    unsigned char field_38;
    unsigned char padding_39[1];
    short field_3A;
    unsigned char padding_3C[362];
    unsigned char field_1A6;
    unsigned char padding_1A7[7];
    unsigned char field_1AE;
    unsigned char padding_1AF[345];
    unsigned char field_308;
};
/* Shape_func_8009BBC0_us: partial shape; common base field:field:param:func_8009E3A4_us:r4:12:1128; size unknown; common-base owner ABI is incomplete or conflicting */
/* Shape_func_8009BBC0_us_2: partial shape; common base field:field:param:func_8009E3A4_us:r4:12:1140; size unknown; common-base owner ABI is incomplete or conflicting */
/* Shape_func_8009BBC0_us_3: partial shape; common base field:param:func_8009E3A4_us:r4:12; size unknown; common-base owner ABI is incomplete or conflicting */
/* Shape_func_8009D4B4_us: partial shape; common base field:param:func_800EEE58_us:r4:60; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_8009E3A4_us_4 {
    int field_0;
    int field_4;
    unsigned char unknown_8[1];
    unsigned char padding_9[3];
    unsigned char unknown_C[4];
    int field_10;
    unsigned char unknown_14[2];
    unsigned char unknown_16[1];
    unsigned char field_17;
    unsigned char field_18;
    unsigned char unknown_19[1];
    unsigned char field_1A;
    unsigned char field_1B;
    int field_1C;
    int field_20;
};
struct Shape_func_8009E3A4_us_5 {
    unsigned char padding_0[32];
    int field_20;
    unsigned char padding_24[4];
    int field_28;
};
struct Shape_func_8009E3A4_us_6 {
    unsigned char padding_0[1];
    unsigned char field_1;
    unsigned char padding_2[22];
    int field_18;
    unsigned char padding_1C[8];
    float field_24;
    unsigned char padding_28[4];
    float field_2C;
    unsigned char padding_30[4];
    float field_34;
    unsigned char padding_38[1228];
    int field_504;
};
struct Shape_func_800A0134_us {
    unsigned char padding_0[1];
    unsigned char field_1;
    unsigned char padding_2[2];
    unsigned char field_4;
};
struct Shape_func_800A0218_us {
    unsigned char padding_0[1];
    unsigned char field_1;
    unsigned char padding_2[22];
    int field_18;
    unsigned char padding_1C[8];
    float field_24;
    unsigned char padding_28[4];
    float field_2C;
    unsigned char padding_30[4];
    float field_34;
    unsigned char padding_38[1228];
    int field_504;
};
/* Shape_func_800A06F8_us: partial shape; common base param:func_800A0B8C_us:stack16; size unknown; common-base owner ABI is incomplete or conflicting */
/* Shape_func_800A0930_us: partial shape; common base param:func_800A0B8C_us:r4; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_800A0B8C_us_3 {
    unsigned char unknown_0[4];
    int field_4;
    int field_8;
    int field_C;
    unsigned char unknown_10[4];
    unsigned char padding_14[6];
    short field_1A;
};
struct Shape_func_800A0B8C_us_4 {
    unsigned char padding_0[1];
    unsigned char field_1;
    unsigned char padding_2[2];
    unsigned char field_4;
};
struct Shape_func_800A16C0_us {
    unsigned char padding_0[1];
    unsigned char field_1;
    unsigned char padding_2[34];
    float field_24;
    unsigned char padding_28[4];
    float field_2C;
    unsigned char padding_30[796];
    int field_34C;
    unsigned char padding_350[8];
    unsigned char unknown_358[1];
};
/* Shape_func_800A2A44_2: partial shape; common base param:func_800A2EA4:r7; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_800A31C0_us_2 {
    void * field_0;
    void * field_4;
    unsigned char unknown_8[4];
    unsigned char unknown_C[4];
    unsigned char unknown_10[4];
    unsigned char unknown_14[4];
    unsigned char unknown_18[4];
    unsigned char unknown_1C[4];
};
/* Shape_func_800A3DE0_us: partial shape; common base param:func_800A3DE0_us:r4; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_800A4D10_us {
    unsigned char padding_0[35];
    unsigned char field_23;
    unsigned char padding_24[484];
    int field_208;
};
struct Shape_func_800A9850_us {
    int field_0;
};
struct Shape_func_800ABAB8_us {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
    unsigned char unknown_8[4];
    unsigned char unknown_C[4];
    unsigned char unknown_10[4];
    unsigned char unknown_14[4];
    unsigned char unknown_18[4];
    unsigned char unknown_1C[4];
    unsigned char unknown_20[4];
    unsigned char unknown_24[4];
    unsigned char unknown_28[4];
    unsigned char unknown_2C[4];
    unsigned char unknown_30[4];
    unsigned char unknown_34[4];
    unsigned char unknown_38[4];
    unsigned char unknown_3C[4];
    unsigned char unknown_40[4];
    unsigned char unknown_44[4];
    unsigned char unknown_48[4];
    unsigned char unknown_4C[4];
    unsigned char unknown_50[4];
    unsigned char unknown_54[4];
    unsigned char unknown_58[4];
    unsigned char unknown_5C[4];
    unsigned char unknown_60[4];
    unsigned char unknown_64[4];
    unsigned char unknown_68[4];
    unsigned char unknown_6C[4];
    unsigned char unknown_70[4];
    unsigned char unknown_74[4];
    unsigned char unknown_78[4];
    unsigned char unknown_7C[4];
    unsigned char unknown_80[4];
    unsigned char unknown_84[4];
    unsigned char unknown_88[4];
    unsigned char unknown_8C[4];
};
struct Shape_func_800AD340_us {
    unsigned char padding_0[4];
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    unsigned char padding_48[4];
    int field_4C;
    unsigned char padding_50[12];
    int field_5C;
    int field_60;
    unsigned char padding_64[4];
    int field_68;
    int field_6C;
    unsigned char padding_70[4];
    int field_74;
};
struct Shape_func_800B8804_us {
    void * field_0;
};
struct Shape_func_800D1BA0_us {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
    unsigned char unknown_8[4];
    unsigned char unknown_C[4];
    unsigned char unknown_10[4];
    unsigned char unknown_14[4];
    unsigned char unknown_18[4];
    unsigned char unknown_1C[4];
    unsigned char unknown_20[4];
    unsigned char unknown_24[4];
    unsigned char unknown_28[4];
    unsigned char unknown_2C[4];
    unsigned char unknown_30[4];
    unsigned char unknown_34[4];
    unsigned char unknown_38[4];
    unsigned char unknown_3C[4];
    unsigned char unknown_40[4];
    unsigned char unknown_44[4];
    unsigned char unknown_48[4];
    unsigned char unknown_4C[4];
    unsigned char unknown_50[4];
    unsigned char unknown_54[4];
    unsigned char unknown_58[4];
    unsigned char unknown_5C[4];
    unsigned char unknown_60[4];
    unsigned char unknown_64[4];
    unsigned char unknown_68[4];
    unsigned char unknown_6C[4];
    unsigned char unknown_70[4];
    unsigned char unknown_74[4];
    unsigned char unknown_78[4];
    unsigned char unknown_7C[4];
    unsigned char unknown_80[4];
    unsigned char unknown_84[4];
    unsigned char unknown_88[4];
    unsigned char unknown_8C[4];
    unsigned char unknown_90[4];
    unsigned char unknown_94[4];
    unsigned char unknown_98[4];
    unsigned char unknown_9C[4];
    unsigned char unknown_A0[4];
    unsigned char unknown_A4[4];
    unsigned char unknown_A8[4];
    unsigned char unknown_AC[4];
    unsigned char unknown_B0[4];
    unsigned char unknown_B4[4];
    unsigned char unknown_B8[4];
    unsigned char unknown_BC[4];
    unsigned char unknown_C0[4];
    unsigned char unknown_C4[4];
    unsigned char unknown_C8[4];
    unsigned char unknown_CC[4];
    unsigned char unknown_D0[4];
    unsigned char unknown_D4[4];
    unsigned char unknown_D8[4];
    unsigned char unknown_DC[4];
    unsigned char unknown_E0[4];
    unsigned char unknown_E4[4];
    unsigned char unknown_E8[4];
    unsigned char unknown_EC[4];
    unsigned char unknown_F0[4];
    unsigned char unknown_F4[4];
    unsigned char unknown_F8[4];
    unsigned char unknown_FC[4];
    unsigned char unknown_100[4];
    unsigned char unknown_104[4];
    unsigned char unknown_108[4];
    unsigned char unknown_10C[4];
    unsigned char unknown_110[4];
    unsigned char unknown_114[4];
    unsigned char unknown_118[4];
    unsigned char unknown_11C[4];
    unsigned char unknown_120[4];
    unsigned char unknown_124[4];
};
struct Shape_func_800DDA08_us {
    unsigned char unknown_0[4];
    int field_4;
    unsigned short field_8;
    unsigned short field_A;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    void * field_1C;
    unsigned char unknown_20[4];
};
struct Shape_func_800DEE8C_us {
    unsigned char padding_0[72000];
    float field_11940;
    float field_11944;
    void * field_11948;
    int field_1194C;
    int field_11950;
    unsigned short field_11954;
    unsigned short field_11956;
    unsigned short field_11958;
    unsigned char padding_1195A[2];
    void * field_1195C;
    int field_11960;
    int field_11964;
};
struct Shape_func_800DF6F4_us {
    unsigned char padding_0[72000];
    float field_11940;
    float field_11944;
    void * field_11948;
    int field_1194C;
    unsigned char unknown_11950[4];
    unsigned char unknown_11954[2];
    unsigned char unknown_11956[2];
    unsigned char unknown_11958[2];
    unsigned char padding_1195A[2];
    void * field_1195C;
    unsigned char unknown_11960[4];
    unsigned char unknown_11964[4];
};
struct Shape_func_800E3CF0_us {
    unsigned char padding_0[1];
    unsigned char field_1;
    unsigned char padding_2[18];
    unsigned short field_14;
    unsigned char padding_16[130];
    int field_98;
    unsigned char padding_9C[692];
    unsigned char field_350;
};
struct Shape_func_800E3F90_us {
    void * field_0;
    unsigned char padding_4[8];
    void * field_C;
    unsigned char padding_10[8];
    unsigned char unknown_18[2];
};
struct Shape_func_800E4AA4_us {
    unsigned char padding_0[1];
    unsigned char field_1;
    unsigned char padding_2[2];
    unsigned char field_4;
    unsigned char padding_5[843];
    unsigned char field_350;
};
struct Shape_func_800E6970_us {
    unsigned char padding_0[8];
    void * field_8;
    unsigned char padding_C[20];
    float field_20;
};
struct Shape_func_800E6A30_us {
    void * field_0;
    unsigned char padding_4[8];
    void * field_C;
    unsigned char padding_10[8];
    unsigned char unknown_18[2];
};
/* Shape_func_800E6B14_us: partial shape; common base param:func_800EB440_us:r4; size unknown; common-base owner parameter types are incomplete or conflicting */
/* Shape_func_800E73A4_us: partial shape; common base field:param:func_800EBAE0_us:r4:8; size unknown; common-base owner parameter types are incomplete or conflicting */
/* Shape_func_800E73A4_us_2: partial shape; common base param:func_800EBAE0_us:r4; size unknown; common-base owner parameter types are incomplete or conflicting */
struct Shape_func_800E73BC_us {
    unsigned char padding_0[8];
    void * field_8;
};
struct Shape_func_800EB440_us_2 {
    unsigned char padding_0[192];
    unsigned char unknown_C0[2];
    short field_C2;
    short field_C4;
    short field_C6;
    int field_C8;
    int field_CC;
    unsigned char unknown_D0[2];
    unsigned char padding_D2[2];
    unsigned char unknown_D4[4];
    void * field_D8;
    void * field_DC;
    void * field_E0;
    unsigned char padding_E4[4];
    unsigned char unknown_E8[4];
};
/* Shape_func_800ED380_2: partial shape; common base param:func_800ED810:r7; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_800EEE58_us_2 {
    unsigned char padding_0[32];
    unsigned char unknown_20[2];
    unsigned char field_22;
    unsigned char padding_23[1];
    unsigned char unknown_24[1];
    unsigned char unknown_25[1];
    unsigned char padding_26[6];
    int field_2C;
    int field_30;
    unsigned char padding_34[4];
    unsigned char field_38;
    unsigned char padding_39[1];
    short field_3A;
    unsigned char padding_3C[362];
    unsigned char field_1A6;
    unsigned char padding_1A7[7];
    unsigned char field_1AE;
    unsigned char padding_1AF[345];
    unsigned char field_308;
};
/* Shape_func_800EFAD8_us: partial shape; common base param:func_800EFFC8_us:r4; size unknown; common-base owner ABI is incomplete or conflicting */
/* Shape_func_800EFAD8_us_2: partial shape; common base param:func_800EFFC8_us:r7; size unknown; common-base owner ABI is incomplete or conflicting */
/* Shape_func_800EFAD8_us_3: partial shape; common base param:func_800EFFC8_us:stack16; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_800EFFC8_us_4 {
    int field_0;
    int field_4;
    unsigned char padding_8[456];
    int field_1D0;
    unsigned char padding_1D4[48];
    int field_204;
    unsigned char padding_208[12];
    unsigned char field_214;
    unsigned char field_215;
    unsigned char field_216;
    unsigned char unknown_217[1];
    int field_218;
};
/* Shape_func_800F0738_us: partial shape; common base param:func_800F0CF0_us:stack16; size unknown; common-base owner ABI is incomplete or conflicting */
/* Shape_func_800F09D0_us: partial shape; common base param:func_800F0CF0_us:r4; size unknown; common-base owner ABI is incomplete or conflicting */
/* Shape_func_800F09D0_us_2: partial shape; common base param:func_800F0CF0_us:r7; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_800F0CF0_us_4 {
    int field_0;
    unsigned char padding_4[16];
    int field_14;
    unsigned char padding_18[4];
    int field_1C;
    int field_20;
    unsigned char padding_24[8];
    int field_2C;
    unsigned char padding_30[8];
    void * field_38;
    unsigned char padding_3C[8];
    int field_44;
    int field_48;
};
/* Shape_func_800F2270_us: partial shape; common base param:func_800F2478_us:r4; size unknown; common-base owner ABI is incomplete or conflicting */
/* Shape_func_800F2270_us_2: partial shape; common base param:func_800F2478_us:r7; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_800F2478_us_3 {
    unsigned char padding_0[864];
    unsigned char unknown_360[4];
    unsigned char padding_364[408];
    void * field_4FC;
};
struct Shape_func_800F6934_us {
    unsigned char padding_0[16];
    int field_10;
    unsigned char padding_14[14];
    unsigned char field_22;
    unsigned char padding_23[23];
    short field_3A;
    unsigned char padding_3C[384];
    unsigned char field_1BC;
    unsigned char field_1BD;
    unsigned char field_1BE;
};
struct Shape_func_800F8120_us {
    unsigned char padding_0[28];
    int field_1C;
    int field_20;
    unsigned char padding_24[116];
    int field_98;
    unsigned char padding_9C[876];
    unsigned char field_408;
    unsigned char field_409;
    unsigned char padding_40A[94];
    int field_468;
    unsigned char padding_46C[10];
    unsigned short field_476;
};
struct Shape_func_800F8120_us_2 {
    unsigned char padding_0[28];
    int field_1C;
    int field_20;
    unsigned char padding_24[116];
    int field_98;
    unsigned char padding_9C[876];
    unsigned char field_408;
    unsigned char field_409;
    unsigned char padding_40A[94];
    int field_468;
    unsigned char padding_46C[10];
    unsigned short field_476;
};
struct Shape_func_800F8120_us_3 {
    unsigned char padding_0[16];
    int field_10;
    unsigned char padding_14[14];
    unsigned char field_22;
    unsigned char padding_23[23];
    short field_3A;
    unsigned char padding_3C[384];
    unsigned char field_1BC;
    unsigned char field_1BD;
    unsigned char field_1BE;
};
struct Shape_func_800F9F34_us {
    unsigned char padding_0[28];
    int field_1C;
    int field_20;
    unsigned char padding_24[116];
    int field_98;
    unsigned char padding_9C[876];
    unsigned char field_408;
    unsigned char field_409;
    unsigned char padding_40A[94];
    int field_468;
    unsigned char padding_46C[10];
    unsigned short field_476;
};
struct Shape_func_800F9F34_us_2 {
    unsigned char padding_0[16];
    int field_10;
    unsigned char padding_14[14];
    unsigned char field_22;
    unsigned char padding_23[23];
    short field_3A;
    unsigned char padding_3C[384];
    unsigned char field_1BC;
    unsigned char field_1BD;
    unsigned char field_1BE;
};
struct Shape_func_80105584_us {
    void * field_0;
};
struct Shape_func_80106010_us {
    unsigned char padding_0[4];
    int field_4;
    unsigned char padding_8[4];
    int field_C;
    unsigned char padding_10[4];
    int field_14;
};
/* Shape_func_8010BFDC_us: partial shape; common base param:func_8010CAE8_us:r4; size unknown; common-base owner return type is incomplete or conflicting */
struct Shape_func_8010CAE8_us_2 {
    unsigned char padding_0[28];
    int field_1C;
    int field_20;
    unsigned char padding_24[116];
    int field_98;
    unsigned char padding_9C[876];
    unsigned char unknown_408[1];
    unsigned char unknown_409[1];
    unsigned char padding_40A[94];
    int field_468;
    unsigned char padding_46C[10];
    unsigned short field_476;
};
/* Shape_func_8010CE24_us: partial shape; common base param:func_8010D388_us:r4; size unknown; common-base owner return type is incomplete or conflicting */
struct Shape_func_8010D388_us_2 {
    unsigned char padding_0[1384];
    int field_568;
    int field_56C;
    int field_570;
};
struct Shape_func_80111690_us {
    unsigned char padding_0[4];
    int field_4;
};
/* Shape_func_80111690_us_2: partial shape; common base global:D_80146100; size unknown; overlapping, negative or inconsistent observed storage intervals */
struct Shape_func_801125F0_us {
    unsigned char padding_0[5];
    unsigned char field_5;
    unsigned char field_6;
    unsigned char field_7;
    unsigned char field_8;
    unsigned char field_9;
    unsigned char padding_A[2];
    int field_C;
    unsigned char padding_10[4];
    int field_14;
    unsigned short field_18;
    unsigned short field_1A;
    int field_1C;
    unsigned char padding_20[4];
    int field_24;
    unsigned char padding_28[4];
    unsigned char unknown_2C[4];
    unsigned char padding_30[4];
    void * field_34;
    unsigned char padding_38[4];
    int field_3C;
    unsigned char padding_40[20];
    int field_54;
    unsigned char padding_58[4];
    int field_5C;
};
struct Shape_func_801130A0_us {
    unsigned char padding_0[5];
    unsigned char unknown_5[1];
    unsigned char field_6;
    unsigned char field_7;
    unsigned char field_8;
    unsigned char field_9;
    unsigned char padding_A[2];
    int field_C;
    unsigned char padding_10[4];
    int field_14;
    unsigned short field_18;
    unsigned short field_1A;
    int field_1C;
    unsigned char padding_20[4];
    int field_24;
    unsigned char padding_28[4];
    unsigned char unknown_2C[4];
    unsigned char padding_30[4];
    void * field_34;
    unsigned char padding_38[4];
    int field_3C;
    unsigned char padding_40[20];
    int field_54;
    unsigned char padding_58[4];
    int field_5C;
};
struct Shape_func_80118AF0_us {
    unsigned char padding_0[4];
    unsigned char field_4;
    unsigned char padding_5[7];
    int field_C;
    unsigned char padding_10[4];
    int field_14;
    unsigned short field_18;
    unsigned short field_1A;
    unsigned char unknown_1C[4];
    unsigned char padding_20[4];
    int field_24;
    unsigned char padding_28[4];
    int field_2C;
};
/* Shape_func_8011954C: partial shape; common base field:param:func_80119FE0_us:r4:24; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_80119748_us {
    unsigned char unknown_0[4];
    int field_4;
    int field_8;
    int field_C;
    unsigned char unknown_10[4];
    unsigned char padding_14[6];
    short field_1A;
};
/* Shape_func_80119D9C_us: partial shape; common base param:func_80119D9C_us:r5; size unknown; common-base owner parameter types are incomplete or conflicting */
struct Shape_func_80119FE0_us_2 {
    unsigned char padding_0[16];
    int field_10;
    unsigned char padding_14[38];
    unsigned short field_3A;
    unsigned char padding_3C[468];
    int field_210;
};
struct Shape_func_8011BC70_us {
    void * field_0;
    void * field_4;
    unsigned char unknown_8[4];
    unsigned char unknown_C[4];
    int field_10;
    int field_14;
    unsigned char unknown_18[4];
    unsigned char unknown_1C[4];
};
struct Shape_func_8011C210_us {
    unsigned char padding_0[60];
    int field_3C;
    int field_40;
    int field_44;
};
struct Shape_func_8011D450_us {
    int field_0;
    unsigned char padding_4[16];
    int field_14;
    unsigned char padding_18[4];
    int field_1C;
    int field_20;
    unsigned char padding_24[8];
    int field_2C;
    unsigned char padding_30[8];
    void * field_38;
    unsigned char padding_3C[8];
    int field_44;
    int field_48;
};
struct Shape_func_8011D4A0_us {
    unsigned char padding_0[20];
    unsigned char unknown_14[4];
    unsigned char padding_18[4];
    int field_1C;
};
struct Shape_func_8011D6D0 {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
    unsigned char unknown_8[4];
    unsigned char unknown_C[4];
    unsigned char unknown_10[4];
    unsigned char unknown_14[4];
    unsigned char unknown_18[4];
    unsigned char unknown_1C[4];
    unsigned char unknown_20[4];
    int field_24;
    unsigned char unknown_28[4];
    int field_2C;
    int field_30;
    int field_34;
    unsigned char unknown_38[4];
    unsigned char unknown_3C[4];
    unsigned char unknown_40[4];
    unsigned char unknown_44[4];
    unsigned char unknown_48[4];
};
/* Shape_func_8011DCF8_us: partial shape; common base field:param:func_8011F29C_us:r4:60; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_8011E2E0 {
    unsigned char padding_0[20];
    int field_14;
    unsigned char unknown_18[4];
    int field_1C;
};
struct Shape_func_8011E434 {
    unsigned char padding_0[20];
    int field_14;
    unsigned char unknown_18[4];
    int field_1C;
};
/* Shape_func_8011E6B0_us: partial shape; common base field:value:func_8011E750_us:us:118:32; size unknown; common base is not a global or a known-signature parameter/return */
struct Shape_func_8011E750_us_2 {
    unsigned char padding_0[36];
    float field_24;
    unsigned char padding_28[4];
    float field_2C;
    unsigned char padding_30[944];
    float field_3E0;
    float field_3E4;
};
struct Shape_func_8011F29C_us_2 {
    unsigned char padding_0[20];
    int field_14;
    unsigned char unknown_18[4];
    int field_1C;
};
/* Shape_func_80120910_us: partial shape; common base param:func_801210BC_us:r4; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_8012162C_us {
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
};
struct Shape_func_801219B0_us {
    unsigned short field_0;
    unsigned char unknown_2[2];
    int field_4;
    void * field_8;
    int field_C;
    unsigned char unknown_10[4];
    unsigned char unknown_14[4];
    unsigned char padding_18[8];
    int field_20;
    float field_24;
    unsigned short field_28;
    unsigned char padding_2A[2];
    int field_2C;
};
struct Shape_func_80121A20_us {
    unsigned char padding_0[4];
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
};
struct Shape_func_80121A20_us_2 {
    unsigned char padding_0[2];
    unsigned char unknown_2[2];
    int field_4;
};
struct Shape_func_801220C0_us {
    unsigned char padding_0[4];
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
};
/* Shape_func_80122750_us: partial shape; common base param:func_80122750_us:r16; size unknown; common-base owner ABI is incomplete or conflicting */
struct Shape_func_80122750_us_2 {
    unsigned char padding_0[4];
    unsigned char field_4;
    unsigned char padding_5[7];
    int field_C;
    unsigned char padding_10[4];
    int field_14;
    unsigned short field_18;
    unsigned short field_1A;
    unsigned char unknown_1C[4];
    unsigned char padding_20[4];
    int field_24;
    unsigned char padding_28[4];
    int field_2C;
};
struct Shape_typemap {
    unsigned char padding_0[16];
    int field_10;
    unsigned char padding_14[14];
    unsigned char field_22;
    unsigned char padding_23[23];
    short field_3A;
    unsigned char padding_3C[384];
    unsigned char field_1BC;
    unsigned char field_1BD;
    unsigned char field_1BE;
};
struct Shape_typemap_10 {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
    unsigned char unknown_8[4];
    unsigned char unknown_C[4];
    unsigned char unknown_10[4];
    unsigned char unknown_14[4];
    unsigned char unknown_18[4];
    unsigned char unknown_1C[4];
    unsigned char unknown_20[4];
    int field_24;
    void * field_28;
    int field_2C;
    int field_30;
    int field_34;
    unsigned char unknown_38[4];
    unsigned char unknown_3C[4];
    unsigned char unknown_40[4];
    unsigned char unknown_44[4];
    unsigned char unknown_48[4];
};
struct Shape_typemap_11 {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
    unsigned char unknown_8[4];
    unsigned char unknown_C[4];
    float field_10;
    float field_14;
    unsigned char unknown_18[4];
    unsigned char unknown_1C[4];
    unsigned char padding_20[164];
    unsigned char unknown_C4[4];
    unsigned char padding_C8[1180];
    int field_564;
    int field_568;
    int field_56C;
    int field_570;
    int field_574;
    int field_578;
    int field_57C;
    int field_580;
    unsigned char padding_584[176];
    int field_634;
    int field_638;
};
struct Shape_typemap_12 {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
    unsigned char unknown_8[4];
    unsigned char padding_C[8];
    unsigned char unknown_14[4];
    unsigned char unknown_18[4];
    unsigned char unknown_1C[4];
    unsigned char unknown_20[4];
    unsigned char unknown_24[4];
    unsigned char unknown_28[4];
    unsigned char unknown_2C[4];
    unsigned char unknown_30[2];
    unsigned char unknown_32[2];
    unsigned char field_34;
    unsigned char unknown_35[1];
    unsigned char padding_36[2];
    unsigned char unknown_38[2];
    unsigned char padding_3A[34];
    unsigned char unknown_5C[4];
    int field_60;
    unsigned char unknown_64[4];
    unsigned char unknown_68[4];
    int field_6C;
    unsigned char unknown_70[4];
    unsigned char unknown_74[4];
    unsigned char unknown_78[4];
    unsigned char unknown_7C[4];
    unsigned char unknown_80[4];
    unsigned char unknown_84[4];
};
struct Shape_typemap_13 {
    unsigned char padding_0[35];
    unsigned char field_23;
    unsigned char padding_24[484];
    int field_208;
};
struct Shape_typemap_14 {
    unsigned char padding_0[1];
    unsigned char field_1;
    unsigned char padding_2[2];
    unsigned char field_4;
    unsigned char padding_5[843];
    unsigned char field_350;
};
struct Shape_typemap_15 {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
};
struct Shape_typemap_16 {
    unsigned char padding_0[28];
    int field_1C;
    int field_20;
    unsigned char padding_24[116];
    int field_98;
    unsigned char padding_9C[876];
    unsigned char unknown_408[1];
    unsigned char unknown_409[1];
    unsigned char padding_40A[94];
    int field_468;
    unsigned char padding_46C[10];
    unsigned short field_476;
};
struct Shape_typemap_17 {
    unsigned char padding_0[1380];
    int field_564;
    int field_568;
    unsigned char padding_56C[4];
    int field_570;
    int field_574;
    int field_578;
    int field_57C;
    int field_580;
    unsigned char padding_584[176];
    int field_634;
    int field_638;
};
struct Shape_typemap_18 {
    unsigned short field_0;
    unsigned char unknown_2[2];
    int field_4;
    void * field_8;
    int field_C;
    unsigned char unknown_10[4];
    unsigned char unknown_14[4];
    unsigned char padding_18[8];
    int field_20;
    float field_24;
    unsigned short field_28;
    unsigned char padding_2A[2];
    int field_2C;
};
struct Shape_typemap_19 {
    void * field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    unsigned char unknown_1C[4];
    int field_20;
    unsigned char unknown_24[4];
    void * field_28;
    unsigned char padding_2C[4];
    int field_30;
    unsigned char padding_34[3600];
    int field_E44;
    unsigned char padding_E48[516];
    int field_104C;
    unsigned char padding_1050[4804];
    int field_2314;
    unsigned char padding_2318[28800];
    int field_9398;
    unsigned char padding_939C[4096];
    int field_A39C;
    int field_A3A0;
    unsigned char padding_A3A4[28804];
    int field_11428;
};
struct Shape_typemap_2 {
    int field_0;
    int field_4;
    unsigned char padding_8[3600];
    int field_E18;
    unsigned char padding_E1C[512];
    int field_101C;
    int field_1020;
    unsigned char padding_1024[4800];
    int field_22E4;
    int field_22E8;
    unsigned char padding_22EC[28800];
    int field_936C;
    unsigned char padding_9370[4096];
    unsigned char unknown_A370[4];
    int field_A374;
    unsigned char padding_A378[28800];
    int field_113F8;
    unsigned char unknown_113FC[4];
    int field_11400;
    int field_11404;
    unsigned char unknown_11408[4];
    unsigned char unknown_1140C[4];
};
struct Shape_typemap_20 {
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
};
struct Shape_typemap_21 {
    unsigned char padding_0[192];
    short field_C0;
    unsigned char padding_C2[14];
    unsigned short field_D0;
    unsigned char padding_D2[2];
    int field_D4;
    void * field_D8;
    void * field_DC;
    void * field_E0;
    int field_E4;
    unsigned char unknown_E8[4];
    unsigned char unknown_EC[2];
    unsigned char unknown_EE[2];
    unsigned char unknown_F0[2];
    unsigned char unknown_F2[2];
    unsigned char unknown_F4[2];
    unsigned char unknown_F6[1];
    unsigned char unknown_F7[1];
    unsigned char unknown_F8[1];
    unsigned char unknown_F9[1];
    unsigned char padding_FA[2];
    unsigned char unknown_FC[4];
    unsigned char unknown_100[4];
    unsigned char unknown_104[2];
};
struct Shape_typemap_22 {
    unsigned char unknown_0[4];
    int field_4;
    unsigned short field_8;
    unsigned short field_A;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    void * field_1C;
    unsigned char unknown_20[4];
};
struct Shape_typemap_23 {
    unsigned char padding_0[28];
    int field_1C;
    int field_20;
    unsigned char padding_24[116];
    int field_98;
    unsigned char padding_9C[876];
    unsigned char unknown_408[1];
    unsigned char unknown_409[1];
    unsigned char padding_40A[94];
    int field_468;
    unsigned char padding_46C[10];
    unsigned short field_476;
};
struct Shape_typemap_24 {
    unsigned char padding_0[1];
    unsigned char field_1;
    unsigned char padding_2[18];
    unsigned short field_14;
    unsigned char padding_16[130];
    int field_98;
    unsigned char padding_9C[692];
    unsigned char field_350;
};
struct Shape_typemap_25 {
    unsigned char padding_0[1];
    unsigned char field_1;
    unsigned char padding_2[34];
    float field_24;
    unsigned char padding_28[4];
    float field_2C;
    unsigned char padding_30[796];
    int field_34C;
    unsigned char padding_350[8];
    unsigned char unknown_358[1];
};
struct Shape_typemap_3 {
    unsigned char padding_0[16];
    int field_10;
    unsigned char padding_14[14];
    unsigned char field_22;
    unsigned char padding_23[23];
    short field_3A;
    unsigned char padding_3C[384];
    unsigned char field_1BC;
    unsigned char field_1BD;
    unsigned char field_1BE;
};
struct Shape_typemap_4 {
    unsigned char unknown_0[4];
    unsigned char unknown_4[4];
};
struct Shape_typemap_5 {
    float field_0;
    float field_4;
    float field_8;
    float field_C;
    unsigned char padding_10[1376];
    int field_570;
};
struct Shape_typemap_6 {
    unsigned char padding_0[20];
    int field_14;
    unsigned char unknown_18[4];
    int field_1C;
};
struct Shape_typemap_7 {
    unsigned char padding_0[68];
    unsigned short field_44;
    unsigned char padding_46[26];
    int field_60;
    unsigned char padding_64[136];
    void * field_EC;
    unsigned char field_F0;
    unsigned char padding_F1[181];
    unsigned char field_1A6;
    unsigned char padding_1A7[25];
    int field_1C0;
    int field_1C4;
};
struct Shape_typemap_8 {
    unsigned char unknown_0[4];
    unsigned char padding_4[16];
    unsigned char unknown_14[4];
    unsigned char unknown_18[4];
};
struct Shape_typemap_9 {
    unsigned char padding_0[2];
    unsigned char unknown_2[2];
    int field_4;
};
#endif
