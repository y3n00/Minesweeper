#include <array>
#include <cstdint>

constexpr static auto flag_png = std::to_array<uint8_t>({
    0x89,
    0x50,
    0x4e,
    0x47,
    0xd,
    0xa,
    0x1a,
    0xa,
    0x0,
    0x0,
    0x0,
    0xd,
    0x49,
    0x48,
    0x44,
    0x52,
    0x0,
    0x0,
    0x0,
    0x1c,
    0x0,
    0x0,
    0x0,
    0x1c,
    0x8,
    0x6,
    0x0,
    0x0,
    0x0,
    0x72,
    0xd,
    0xdf,
    0x94,
    0x0,
    0x0,
    0x0,
    0x9,
    0x70,
    0x48,
    0x59,
    0x73,
    0x0,
    0x0,
    0xb,
    0x13,
    0x0,
    0x0,
    0xb,
    0x13,
    0x1,
    0x0,
    0x9a,
    0x9c,
    0x18,
    0x0,
    0x0,
    0x0,
    0x1,
    0x73,
    0x52,
    0x47,
    0x42,
    0x0,
    0xae,
    0xce,
    0x1c,
    0xe9,
    0x0,
    0x0,
    0x0,
    0x4,
    0x67,
    0x41,
    0x4d,
    0x41,
    0x0,
    0x0,
    0xb1,
    0x8f,
    0xb,
    0xfc,
    0x61,
    0x5,
    0x0,
    0x0,
    0x1,
    0xe,
    0x49,
    0x44,
    0x41,
    0x54,
    0x78,
    0x1,
    0xed,
    0x95,
    0x3f,
    0xe,
    0x82,
    0x30,
    0x14,
    0xc6,
    0x3f,
    0x8d,
    0x89,
    0x93,
    0x86,
    0xc1,
    0x3,
    0x30,
    0xba,
    0xe1,
    0xe4,
    0x66,
    0x62,
    0xa2,
    0x7,
    0xd0,
    0x49,
    0x27,
    0xff,
    0xec,
    0xe,
    0xde,
    0x40,
    0x6e,
    0xc0,
    0x11,
    0xc0,
    0x93,
    0xe8,
    0xd,
    0x70,
    0x63,
    0x84,
    0x3b,
    0x70,
    0x80,
    0xfa,
    0x5e,
    0x49,
    0xd,
    0x61,
    0xa1,
    0x5,
    0x21,
    0xd1,
    0xf0,
    0x4b,
    0xbe,
    0x1,
    0x2,
    0xfd,
    0xf5,
    0xbd,
    0x96,
    0x2,
    0xe8,
    0xe1,
    0x51,
    0x2c,
    0xb4,
    0x88,
    0xa0,
    0xc4,
    0x14,
    0x1b,
    0x2d,
    0x21,
    0x72,
    0xb9,
    0xa2,
    0x5,
    0x44,
    0x21,
    0x3e,
    0x1a,
    0xae,
    0x56,
    0x8a,
    0xfc,
    0xd5,
    0x4a,
    0xd8,
    0xa3,
    0x91,
    0x92,
    0x72,
    0x8b,
    0x97,
    0x68,
    0x8,
    0x29,
    0x11,
    0x97,
    0x8b,
    0x88,
    0xf,
    0x7,
    0x31,
    0x9b,
    0x4c,
    0xf2,
    0xd5,
    0xba,
    0x6,
    0xe3,
    0xa0,
    0xf,
    0x43,
    0xec,
    0xf1,
    0x18,
    0xe1,
    0x7e,
    0xf,
    0x77,
    0x3e,
    0x57,
    0xb7,
    0x6e,
    0x30,
    0xd8,
    0x50,
    0xc6,
    0xc2,
    0x8f,
    0x85,
    0x84,
    0x2c,
    0xa6,
    0x16,
    0xcb,
    0x79,
    0x50,
    0x42,
    0xca,
    0xb1,
    0xec,
    0xbd,
    0xca,
    0x42,
    0x86,
    0x5a,
    0x8b,
    0xc7,
    0x76,
    0x8b,
    0xe3,
    0x74,
    0xca,
    0x97,
    0xfc,
    0x9d,
    0x6,
    0xc8,
    0x36,
    0x94,
    0xd5,
    0x88,
    0x90,
    0xe1,
    0x16,
    0x7,
    0xeb,
    0x35,
    0xbc,
    0xc5,
    0x2,
    0xd6,
    0x70,
    0xc8,
    0xb7,
    0x4e,
    0xc8,
    0xaa,
    0xb5,
    0x1b,
    0x11,
    0x2a,
    0xae,
    0x8e,
    0x83,
    0x70,
    0xb7,
    0xcb,
    0xb7,
    0x98,
    0xd7,
    0xd5,
    0x2d,
    0x3e,
    0xd7,
    0x83,
    0x1e,
    0xbc,
    0x1b,
    0xe5,
    0xba,
    0xe9,
    0x70,
    0x8f,
    0x22,
    0x24,
    0x69,
    0xaa,
    0x2e,
    0x9f,
    0x94,
    0x33,
    0x25,
    0x81,
    0x1,
    0xa2,
    0x66,
    0xb8,
    0xda,
    0xd,
    0xf,
    0x34,
    0x80,
    0x19,
    0x2e,
    0xaa,
    0xe3,
    0x50,
    0x5e,
    0xba,
    0xf,
    0xab,
    0x99,
    0xd6,
    0xe6,
    0x6b,
    0x9b,
    0xa6,
    0x13,
    0x76,
    0xc2,
    0x4e,
    0xf8,
    0x3b,
    0xc2,
    0xb2,
    0xc3,
    0x5b,
    0xe7,
    0x74,
    0xd1,
    0xfd,
    0x1,
    0x48,
    0x5a,
    0xaf,
    0xf0,
    0xff,
    0x79,
    0x3,
    0x60,
    0x8f,
    0x4f,
    0xfe,
    0x51,
    0xb0,
    0xdd,
    0x8b,
    0x0,
    0x0,
    0x0,
    0x0,
    0x49,
    0x45,
    0x4e,
    0x44,
    0xae,
    0x42,
    0x60,
    0x82,
});

constexpr static auto mine_png = std::to_array<uint8_t>({
    0x89,
    0x50,
    0x4e,
    0x47,
    0xd,
    0xa,
    0x1a,
    0xa,
    0x0,
    0x0,
    0x0,
    0xd,
    0x49,
    0x48,
    0x44,
    0x52,
    0x0,
    0x0,
    0x0,
    0x1c,
    0x0,
    0x0,
    0x0,
    0x1c,
    0x8,
    0x6,
    0x0,
    0x0,
    0x0,
    0x72,
    0xd,
    0xdf,
    0x94,
    0x0,
    0x0,
    0x0,
    0x9,
    0x70,
    0x48,
    0x59,
    0x73,
    0x0,
    0x0,
    0xb,
    0x13,
    0x0,
    0x0,
    0xb,
    0x13,
    0x1,
    0x0,
    0x9a,
    0x9c,
    0x18,
    0x0,
    0x0,
    0x0,
    0x1,
    0x73,
    0x52,
    0x47,
    0x42,
    0x0,
    0xae,
    0xce,
    0x1c,
    0xe9,
    0x0,
    0x0,
    0x0,
    0x4,
    0x67,
    0x41,
    0x4d,
    0x41,
    0x0,
    0x0,
    0xb1,
    0x8f,
    0xb,
    0xfc,
    0x61,
    0x5,
    0x0,
    0x0,
    0x1,
    0x50,
    0x49,
    0x44,
    0x41,
    0x54,
    0x78,
    0x1,
    0xbd,
    0x95,
    0x81,
    0x6d,
    0x83,
    0x30,
    0x10,
    0x45,
    0x7f,
    0xa3,
    0xe,
    0xc0,
    0x6,
    0xf5,
    0x8,
    0xdd,
    0x20,
    0x6c,
    0x50,
    0x36,
    0x80,
    0xd,
    0xc8,
    0x6,
    0xb0,
    0x9,
    0xdd,
    0x20,
    0xd9,
    0x0,
    0x36,
    0x68,
    0x3b,
    0x1,
    0xd9,
    0x20,
    0x6c,
    0x90,
    0xda,
    0x9,
    0x16,
    0xd7,
    0xb3,
    0xb,
    0xc6,
    0x5c,
    0xf2,
    0xa5,
    0x2f,
    0x19,
    0x73,
    0xf6,
    0xb3,
    0xcf,
    0x27,
    0x1b,
    0x58,
    0xaf,
    0x5e,
    0xfb,
    0xaa,
    0xdd,
    0x62,
    0xa3,
    0x94,
    0xf6,
    0x65,
    0x74,
    0x3a,
    0x13,
    0x73,
    0x25,
    0xde,
    0xa4,
    0x82,
    0x4d,
    0x96,
    0xb,
    0x0,
    0x53,
    0xed,
    0xec,
    0xbf,
    0x9f,
    0x9,
    0xa6,
    0x74,
    0x59,
    0xbf,
    0x6f,
    0x0,
    0xd2,
    0xd8,
    0x6a,
    0x2e,
    0x88,
    0x43,
    0xf,
    0xe3,
    0x62,
    0x4a,
    0xdc,
    0xcf,
    0x8d,
    0xfe,
    0x33,
    0xb1,
    0x47,
    0xb8,
    0xd9,
    0xe0,
    0xf3,
    0x34,
    0x58,
    0x58,
    0x19,
    0x87,
    0x5e,
    0xd8,
    0xb7,
    0xcf,
    0x3d,
    0x1,
    0xb7,
    0xac,
    0x5f,
    0x61,
    0x41,
    0x3e,
    0x68,
    0xa8,
    0x79,
    0x16,
    0x32,
    0x4,
    0xaa,
    0x8e,
    0x4,
    0x52,
    0x57,
    0x81,
    0x2c,
    0xa7,
    0x62,
    0x63,
    0xdc,
    0x60,
    0x85,
    0x7a,
    0x1,
    0xa0,
    0x39,
    0xf7,
    0x24,
    0x4,
    0x56,
    0x8,
    0xc0,
    0xac,
    0x4b,
    0x3e,
    0xf9,
    0x2b,
    0xee,
    0x5,
    0x92,
    0x60,
    0x5a,
    0x4d,
    0xe,
    0x39,
    0x99,
    0x82,
    0xf9,
    0x21,
    0xdf,
    0xdd,
    0xb,
    0xc2,
    0x6e,
    0xc,
    0x29,
    0x9d,
    0x9f,
    0xd,
    0xbc,
    0xa5,
    0xf4,
    0xd1,
    0xea,
    0x48,
    0xfb,
    0x64,
    0x1b,
    0xe6,
    0xce,
    0xdc,
    0x6b,
    0xbf,
    0x41,
    0xa6,
    0x42,
    0xad,
    0xbf,
    0x38,
    0xdd,
    0xee,
    0xf0,
    0x9b,
    0xf4,
    0x99,
    0xb6,
    0x82,
    0x8c,
    0xce,
    0xbc,
    0x63,
    0xe7,
    0x9,
    0xea,
    0x20,
    0xa7,
    0x53,
    0x48,
    0xd0,
    0x27,
    0x64,
    0xd2,
    0xd9,
    0x87,
    0xc0,
    0x6a,
    0x21,
    0x98,
    0x5,
    0xa6,
    0x73,
    0xb0,
    0x2,
    0xee,
    0x81,
    0x4b,
    0x80,
    0x73,
    0x1f,
    0x4c,
    0xe1,
    0xef,
    0x9b,
    0xd7,
    0x8c,
    0xfd,
    0x55,
    0x4,
    0xa0,
    0x81,
    0xfb,
    0x7e,
    0xd6,
    0x1c,
    0x78,
    0x64,
    0xa9,
    0x50,
    0x6c,
    0xe7,
    0x7d,
    0x0,
    0xc8,
    0x40,
    0x32,
    0xb2,
    0x1,
    0x3e,
    0xa6,
    0x5,
    0xb9,
    0xcc,
    0xf,
    0x64,
    0x90,
    0x82,
    0x5f,
    0x5,
    0x5b,
    0x98,
    0x5d,
    0x9c,
    0xe9,
    0x2b,
    0xe1,
    0xbe,
    0xc,
    0xca,
    0x3,
    0xfd,
    0xa0,
    0x1,
    0x7b,
    0x2c,
    0x3f,
    0x27,
    0xa,
    0xeb,
    0xaa,
    0xd0,
    0xcc,
    0xd7,
    0xc0,
    0x9f,
    0xb9,
    0x20,
    0xa9,
    0x95,
    0x40,
    0xa,
    0xbe,
    0x69,
    0x87,
    0xe7,
    0x68,
    0x88,
    0x5,
    0xe,
    0x98,
    0x6,
    0xf,
    0x88,
    0xd0,
    0x2f,
    0x7f,
    0xa7,
    0x2e,
    0xb,
    0x5f,
    0x20,
    0x41,
    0x26,
    0x0,
    0x0,
    0x0,
    0x0,
    0x49,
    0x45,
    0x4e,
    0x44,
    0xae,
    0x42,
    0x60,
    0x82,
});