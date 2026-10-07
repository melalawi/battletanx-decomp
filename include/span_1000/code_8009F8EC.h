#ifndef UNBAKE_SPAN_1000_CODE_8009F8EC_H
#define UNBAKE_SPAN_1000_CODE_8009F8EC_H
struct Shape_func_80092734_us;

struct Shape_func_80092734_us {
    unsigned char padding_0[36];
    float field_24;
    unsigned char padding_28[4];
    float field_2C;
    unsigned char padding_30[944];
    float field_3E0;
    float field_3E4;
};

struct Shape_func_800A0218_us;

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

struct Shape_func_800E3CF0_us;

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

extern float func_8009F8EC_us(struct Shape_func_80092734_us * arg0, float arg1, float arg2);

extern int func_8009FB8C_us(struct Shape_func_800E3CF0_us * arg0);

extern int func_8009FC0C_us(void * arg0);

extern int func_8009FCD0_us(void * arg0);

extern int func_800A0218_us(struct Shape_func_800A0218_us * arg0);

extern int func_800A0380_us();

extern int func_800A0400_us(int arg0, void * arg1, int arg2, int arg3, int arg4, unsigned char arg5);

extern int func_800A04F0_us(void * arg0, void * arg1);

extern int func_800A0AD4_us(void * arg0);
#endif
