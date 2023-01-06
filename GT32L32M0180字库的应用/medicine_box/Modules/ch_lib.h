#ifndef __MODULES_CH_LIB_H__
#define __MODULES_CH_LIB_H__

typedef struct
{
    char index[2];
    char mat[32];
}ch_16x16_t;

typedef struct
{
    char index[2];
    char mat[128];
}ch_32x32_t;

//typedef struct
//{

//}

const ch_16x16_t ch_16x16_lib[] = 
{
    {"��",0x40,0x00,0x80,0x00,0xFE,0x7F,0x02,0x40,0x01,0x20,0xF8,0x07,0x00,0x02,0x00,0x01,
        0x80,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xA0,0x00,0x40,0x00},

    {"��",0x80,0x00,0x00,0x01,0xFC,0x7F,0x84,0x00,0x84,0x00,0xFC,0x3F,0x44,0x00,0x24,0x01,
        0x14,0x01,0xF4,0x1F,0x04,0x01,0x04,0x01,0xFA,0x7F,0x02,0x01,0x01,0x01,0x00,0x01},

    {"��",0x00,0x20,0xE4,0x23,0x28,0x22,0x28,0x2A,0xA1,0x2A,0xA2,0x2A,0xA2,0x2A,0xA8,0x2A,
        0xA8,0x2A,0xA4,0x2A,0xA7,0x2A,0x84,0x20,0x44,0x21,0x44,0x22,0x24,0x28,0x10,0x10},

    {"��",0x00,0x14,0x04,0x24,0x08,0x24,0x08,0x04,0xE0,0x7F,0x00,0x04,0x0F,0x04,0xE8,0x07,
        0x88,0x04,0x88,0x08,0x88,0x08,0xA8,0x08,0x98,0x53,0xE8,0x50,0x40,0x60,0x00,0x40},

    {"һ",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x7F,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

};


const ch_32x32_t ch_32x32_lib[] =
{
    {"��",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0xC0,0x00,0x00,
        0x00,0x80,0x01,0x00,0x00,0x80,0x03,0x00,0x20,0x00,0x01,0x08,0xE0,0xFF,0xFF,0x1F,
        0x20,0x00,0x00,0x0C,0x30,0x00,0x00,0x06,0x30,0x00,0x00,0x02,0x18,0x00,0x40,0x00,
        0x80,0xFF,0xFF,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x0C,0x00,
        0x00,0x80,0x02,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x18,0xFC,0xFF,0xFF,0x3F,
        0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,
        0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,
        0x00,0xFC,0x01,0x00,0x00,0xE0,0x01,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00},


    {"��",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x03,0x00,
        0x00,0x00,0x03,0x00,0x20,0x00,0x02,0x0C,0xE0,0xFF,0xFF,0x1F,0x60,0x40,0x00,0x00,
        0x60,0x80,0x01,0x00,0x60,0xC0,0x01,0x00,0x60,0xC0,0x00,0x00,0x60,0xC0,0x00,0x04,
        0xE0,0xFF,0xFF,0x0F,0x60,0x60,0x00,0x00,0x60,0x20,0x0C,0x00,0x60,0x30,0x0C,0x00,
        0x60,0x10,0x0C,0x00,0x60,0x18,0x0C,0x03,0x60,0xFC,0xFF,0x07,0x20,0x08,0x0C,0x00,
        0x20,0x00,0x0C,0x00,0x30,0x00,0x0C,0x00,0x30,0x00,0x0C,0x0C,0xB0,0xFF,0xFF,0x1F,
        0x10,0x00,0x0C,0x00,0x10,0x00,0x0C,0x00,0x08,0x00,0x0C,0x00,0x08,0x00,0x0C,0x00,
        0x04,0x00,0x0C,0x00,0x04,0x00,0x0C,0x00,0x02,0x00,0x04,0x00,0x00,0x00,0x00,0x00},


    {"��",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x08,0x30,0x04,0x00,0x18,
        0x60,0xFC,0x0F,0x18,0xC0,0x0C,0x0C,0x18,0xC0,0x0C,0x0C,0x18,0x00,0x0C,0xCC,0x18,
        0x00,0x4C,0xCC,0x19,0x00,0xCC,0xCD,0x18,0x0C,0xCC,0xCC,0x18,0x18,0xCD,0xCC,0x18,
        0x38,0xCD,0xCC,0x18,0x30,0xCD,0xCC,0x18,0x90,0xCC,0xCC,0x18,0x80,0xCC,0xCC,0x18,
        0x80,0x4C,0xCC,0x18,0x80,0x4C,0xCC,0x18,0x40,0x4C,0xCC,0x18,0x40,0x4C,0xCC,0x18,
        0x60,0x4C,0xCC,0x18,0x7E,0x6C,0xC4,0x18,0x38,0x64,0xC0,0x18,0x30,0xA0,0xC0,0x18,
        0x30,0x30,0x01,0x18,0x30,0x10,0x02,0x18,0x30,0x18,0x0E,0x18,0x30,0x0C,0x0C,0x18,
        0x30,0x06,0x8C,0x0F,0x00,0x01,0x08,0x0E,0x80,0x00,0x00,0x04,0x00,0x00,0x00,0x00},


    {"��",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0xE0,0x03,
        0x30,0x00,0x60,0x0E,0x60,0x00,0x60,0x0C,0xC0,0x00,0x60,0x08,0xC0,0x00,0x60,0x18,
        0xC0,0x00,0x60,0x10,0x00,0xFC,0xFF,0x3F,0x00,0x00,0x60,0x00,0x00,0x00,0x60,0x00,
        0x00,0x00,0x60,0x00,0x80,0x00,0x60,0x00,0xFE,0x01,0x68,0x00,0xC0,0xF8,0x5F,0x00,
        0xC0,0x80,0x41,0x00,0xC0,0x80,0xC1,0x00,0xC0,0x80,0xC1,0x00,0xC0,0x80,0xC1,0x00,
        0xC0,0x80,0x81,0x00,0xC0,0x80,0x81,0x01,0xC0,0x90,0x81,0x01,0xC0,0x88,0x31,0x23,
        0xC0,0x84,0x0F,0x23,0xC0,0xC2,0x03,0x26,0xC0,0x7B,0x00,0x2E,0xC0,0x11,0x00,0x3C,
        0xC0,0x01,0x00,0x38,0x80,0x00,0x00,0x30,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00},

    {"��",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0xF0,0x03,
        0x00,0x80,0xFF,0x07,0xF0,0xFF,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,
        0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x03,0xF0,0xFF,0xFF,0x07,
        0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,
        0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x18,0xFE,0xFF,0xFF,0x3F,0x00,0x80,0x01,0x00,
        0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,
        0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0xC0,0x01,0x00,
        0x00,0xFC,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00},

    {"��",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x03,0x00,
        0x00,0x80,0x31,0x00,0x00,0x80,0xC1,0x01,0x00,0x80,0x81,0x01,0x00,0x80,0x81,0x01,
        0x00,0x80,0x01,0x09,0x00,0x80,0x01,0x1C,0xFC,0xFF,0xFF,0x3F,0x00,0xC0,0x03,0x00,
        0x00,0xE0,0x05,0x00,0x00,0xE0,0x05,0x00,0x00,0xB0,0x05,0x00,0x00,0xB0,0x09,0x00,
        0x00,0x98,0x19,0x00,0x00,0x8C,0x11,0x00,0x00,0x8C,0x31,0x00,0x00,0x86,0x61,0x00,
        0x00,0x83,0xE1,0x00,0x80,0x81,0xC1,0x01,0x80,0x80,0x81,0x03,0x40,0x80,0x01,0x0F,
        0x20,0x80,0x01,0x7E,0x10,0x80,0x01,0x0C,0x0C,0x80,0x01,0x08,0x00,0x80,0x01,0x00,
        0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00},

    {"��",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0xC0,0x01,0x00,
        0x00,0x80,0x01,0x00,0x00,0x00,0x01,0x00,0x20,0x00,0x01,0x08,0xE0,0xFF,0xFF,0x1F,
        0x30,0x00,0x00,0x0C,0x30,0x00,0x00,0x06,0x38,0x00,0x80,0x02,0xC0,0xFF,0xFF,0x01,
        0x00,0xE0,0x00,0x00,0x00,0x30,0x10,0x00,0x00,0x18,0x60,0x00,0x00,0x0C,0xC0,0x00,
        0x00,0x02,0x80,0x01,0x80,0xFF,0xFF,0x03,0x80,0x7F,0x00,0x03,0x00,0x81,0x00,0x01,
        0x00,0x80,0x03,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x81,0x01,0xC0,0xFF,0xFF,0x03,
        0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,
        0x00,0x80,0x01,0x18,0xFC,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},


};


const ch_32x32_t ch_32x32_lib_vertical[] =
{
    {"��",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,
        0xE0,0xFF,0x01,0x20,0xE0,0xFF,0x21,0x20,0x00,0x00,0x20,0x20,0x00,0x00,0x20,0x20,
        0x00,0x00,0x20,0x20,0xFC,0xFF,0x27,0x20,0xF8,0xFF,0xA7,0x21,0x08,0x00,0x21,0x2F,
        0x00,0x00,0x21,0x3E,0x20,0x00,0x21,0x20,0x20,0x80,0x22,0x20,0x60,0x80,0x2E,0x20,
        0xA0,0xC1,0x3C,0x20,0x20,0x46,0x20,0x20,0x20,0x6C,0x20,0x38,0x20,0x38,0x20,0x2E,
        0x20,0x38,0xE0,0x23,0x20,0x6C,0xA0,0x21,0x20,0x67,0x20,0x20,0xA0,0xC3,0x20,0x20,
        0xF0,0xC0,0x38,0x20,0x60,0x80,0x21,0x20,0x00,0x80,0x01,0x30,0x00,0x80,0x03,0x38,
        0x00,0x80,0x01,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

    {"��",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x0E,0x00,0x00,0x02,0x06,0x10,
        0x00,0x02,0x06,0x10,0x00,0x02,0x03,0x30,0x00,0x02,0x01,0x38,0xFC,0xFF,0xFF,0x3F,
        0x08,0x82,0x00,0x00,0x00,0x82,0x00,0x00,0x00,0x43,0x00,0x00,0x00,0x42,0x20,0x00,
        0x00,0x01,0x20,0x00,0x00,0x81,0x20,0x00,0x00,0x81,0x20,0x00,0x00,0x81,0x20,0x00,
        0x00,0x81,0x20,0x00,0xFC,0xFF,0xFF,0x7F,0xF8,0xFF,0xFF,0x3F,0x08,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0x7F,0xF8,0xFF,0xFF,0x3F,
        0x08,0x81,0x20,0x00,0x00,0x81,0x20,0x00,0x00,0x81,0x20,0x00,0x00,0x81,0x20,0x00,
        0x80,0xC1,0x30,0x00,0x00,0x81,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

    {"ŵ",0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,
        0x08,0x20,0x00,0x00,0x70,0x20,0x00,0x00,0xE0,0xF1,0xFF,0x0F,0xC0,0xE0,0xFF,0x0F,
        0x00,0x00,0x00,0x07,0x00,0x00,0x80,0x09,0x80,0x80,0x40,0x04,0x80,0x80,0x20,0x02,
        0x80,0x80,0x00,0x03,0x80,0x80,0x80,0x01,0x80,0x80,0xE0,0x00,0xFC,0x8F,0x30,0x00,
        0xF8,0x8F,0xFC,0x7F,0x88,0x80,0xFF,0x3F,0x80,0xE0,0x13,0x08,0x80,0xFC,0x10,0x08,
        0x80,0x9C,0x10,0x08,0x80,0x88,0x10,0x08,0x80,0x80,0x10,0x08,0xFC,0x8F,0x10,0x08,
        0xF8,0x87,0x10,0x08,0x88,0x80,0xF0,0x7F,0x80,0x80,0xF8,0x3F,0x80,0x80,0x10,0x00,
        0xC0,0xC0,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

    {"��",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x10,
        0x40,0x00,0x00,0x10,0x40,0x10,0x00,0x10,0x40,0xE0,0x00,0x10,0x40,0x80,0x0F,0x10,
        0x40,0x00,0x7F,0x10,0x40,0x00,0x3C,0x10,0x40,0x00,0x00,0x10,0x40,0x00,0x00,0x10,
        0xC0,0xFF,0xFF,0x1F,0xC0,0xFF,0xFF,0x1F,0x40,0x00,0x00,0x10,0x40,0x00,0x00,0x10,
        0x40,0x00,0x00,0x10,0x40,0x00,0x00,0x10,0xC0,0xFF,0xFF,0x1F,0xC0,0xFF,0xFF,0x1F,
        0x40,0x00,0x40,0x10,0x40,0x00,0x30,0x10,0x40,0x00,0x1C,0x10,0x40,0x00,0x07,0x10,
        0x40,0xE0,0x01,0x10,0x60,0xF8,0x00,0x10,0x70,0x30,0x00,0x18,0x60,0x10,0x00,0x1C,
        0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
};
















#endif
