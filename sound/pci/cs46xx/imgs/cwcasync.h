multiline_comment|/* generated from cwcasync.osp DO NOT MODIFY */
macro_line|#ifndef __HEADER_cwcasync_H__
DECL|macro|__HEADER_cwcasync_H__
mdefine_line|#define __HEADER_cwcasync_H__
DECL|variable|cwcasync_symbols
r_static
id|symbol_entry_t
id|cwcasync_symbols
(braket
)braket
op_assign
(brace
(brace
l_int|0x8000
comma
l_string|&quot;EXECCHILD&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x8001
comma
l_string|&quot;EXECCHILD_98&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x8003
comma
l_string|&quot;EXECCHILD_PUSH1IND&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x8008
comma
l_string|&quot;EXECSIBLING&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x800a
comma
l_string|&quot;EXECSIBLING_298&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x800b
comma
l_string|&quot;EXECSIBLING_2IND1&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x8010
comma
l_string|&quot;TIMINGMASTER&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x804f
comma
l_string|&quot;S16_CODECINPUTTASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x805e
comma
l_string|&quot;PCMSERIALINPUTTASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x806d
comma
l_string|&quot;S16_MIX_TO_OSTREAM&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x809a
comma
l_string|&quot;S16_MIX&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x80bb
comma
l_string|&quot;S16_UPSRC&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x813b
comma
l_string|&quot;MIX3_EXP&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x8164
comma
l_string|&quot;DECIMATEBYPOW2&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x8197
comma
l_string|&quot;VARIDECIMATE&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x81f2
comma
l_string|&quot;_3DINPUTTASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x820a
comma
l_string|&quot;_3DPRLGCINPTASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x8227
comma
l_string|&quot;_3DSTEREOINPUTTASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x8242
comma
l_string|&quot;_3DOUTPUTTASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x82c4
comma
l_string|&quot;HRTF_MORPH_TASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x82c6
comma
l_string|&quot;WAIT4DATA&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x82fa
comma
l_string|&quot;PROLOGIC&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x8496
comma
l_string|&quot;DECORRELATOR&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x84a4
comma
l_string|&quot;STEREO2MONO&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0000
comma
l_string|&quot;OVERLAYBEGINADDRESS&quot;
comma
l_int|0x00
)brace
comma
(brace
l_int|0x0000
comma
l_string|&quot;SPIOWRITE&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x000d
comma
l_string|&quot;S16_ASYNCCODECINPUTTASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0043
comma
l_string|&quot;SPDIFITASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x007b
comma
l_string|&quot;SPDIFOTASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0097
comma
l_string|&quot;ASYNCHFGTXCODE&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x00be
comma
l_string|&quot;ASYNCHFGRXCODE&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x00db
comma
l_string|&quot;#CODE_END&quot;
comma
l_int|0x00
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* cwcasync symbols */
DECL|variable|cwcasync_code
r_static
id|u32
id|cwcasync_code
(braket
)braket
op_assign
(brace
multiline_comment|/* OVERLAYBEGINADDRESS */
multiline_comment|/* 0000 */
l_int|0x00002731
comma
l_int|0x00001400
comma
l_int|0x00003725
comma
l_int|0x000a8440
comma
multiline_comment|/* 0002 */
l_int|0x000000ae
comma
l_int|0x00000000
comma
l_int|0x00060630
comma
l_int|0x00001000
comma
multiline_comment|/* 0004 */
l_int|0x00000000
comma
l_int|0x000c7560
comma
l_int|0x00075282
comma
l_int|0x0002d640
comma
multiline_comment|/* 0006 */
l_int|0x00021705
comma
l_int|0x00000000
comma
l_int|0x00072ab8
comma
l_int|0x0002d6c0
comma
multiline_comment|/* 0008 */
l_int|0x00020630
comma
l_int|0x00001000
comma
l_int|0x000c74c2
comma
l_int|0x000d4b82
comma
multiline_comment|/* 000A */
l_int|0x000475c2
comma
l_int|0x00000000
comma
l_int|0x0003430a
comma
l_int|0x000c0000
comma
multiline_comment|/* 000C */
l_int|0x00042730
comma
l_int|0x00001400
comma
multiline_comment|/* S16_ASYNCCODECINPUTTASK */
multiline_comment|/* 000D */
l_int|0x0006a108
comma
l_int|0x000cf2c4
comma
l_int|0x0004f4c0
comma
l_int|0x00000000
comma
multiline_comment|/* 000F */
l_int|0x000fa418
comma
l_int|0x0000101f
comma
l_int|0x0005d402
comma
l_int|0x0001c500
comma
multiline_comment|/* 0011 */
l_int|0x000f0630
comma
l_int|0x00001000
comma
l_int|0x00004418
comma
l_int|0x00001380
comma
multiline_comment|/* 0013 */
l_int|0x000e243d
comma
l_int|0x000d394a
comma
l_int|0x00049705
comma
l_int|0x00000000
comma
multiline_comment|/* 0015 */
l_int|0x0007d530
comma
l_int|0x000b4240
comma
l_int|0x000e00f2
comma
l_int|0x00001000
comma
multiline_comment|/* 0017 */
l_int|0x00009134
comma
l_int|0x000ca20a
comma
l_int|0x00004c90
comma
l_int|0x00001000
comma
multiline_comment|/* 0019 */
l_int|0x0005d705
comma
l_int|0x00000000
comma
l_int|0x00004f25
comma
l_int|0x00098240
comma
multiline_comment|/* 001B */
l_int|0x00004725
comma
l_int|0x00000000
comma
l_int|0x0000e48a
comma
l_int|0x00000000
comma
multiline_comment|/* 001D */
l_int|0x00027295
comma
l_int|0x0009c2c0
comma
l_int|0x0003df25
comma
l_int|0x00000000
comma
multiline_comment|/* 001F */
l_int|0x000e8030
comma
l_int|0x00001001
comma
l_int|0x0005f718
comma
l_int|0x000ac600
comma
multiline_comment|/* 0021 */
l_int|0x0007cf30
comma
l_int|0x000c2a01
comma
l_int|0x00082630
comma
l_int|0x00001001
comma
multiline_comment|/* 0023 */
l_int|0x000504a0
comma
l_int|0x00001001
comma
l_int|0x00029314
comma
l_int|0x000bcb80
comma
multiline_comment|/* 0025 */
l_int|0x0003cf25
comma
l_int|0x000b0e00
comma
l_int|0x0004f5c0
comma
l_int|0x00000000
comma
multiline_comment|/* 0027 */
l_int|0x00049118
comma
l_int|0x000d888a
comma
l_int|0x0007dd02
comma
l_int|0x000c6efa
comma
multiline_comment|/* 0029 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x0004f5c0
comma
l_int|0x00069c80
comma
multiline_comment|/* 002B */
l_int|0x0000d402
comma
l_int|0x00000000
comma
l_int|0x000e8630
comma
l_int|0x00001001
comma
multiline_comment|/* 002D */
l_int|0x00079130
comma
l_int|0x00000000
comma
l_int|0x00049118
comma
l_int|0x00090e00
comma
multiline_comment|/* 002F */
l_int|0x0006c10a
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x000c0000
comma
multiline_comment|/* 0031 */
l_int|0x0007cf30
comma
l_int|0x00030580
comma
l_int|0x00005725
comma
l_int|0x00000000
comma
multiline_comment|/* 0033 */
l_int|0x000d84a0
comma
l_int|0x00001001
comma
l_int|0x00029314
comma
l_int|0x000b4780
comma
multiline_comment|/* 0035 */
l_int|0x0003cf25
comma
l_int|0x000b8600
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0037 */
l_int|0x00000000
comma
l_int|0x000c0000
comma
l_int|0x00000000
comma
l_int|0x00042c80
comma
multiline_comment|/* 0039 */
l_int|0x0001dec1
comma
l_int|0x000e488c
comma
l_int|0x00031114
comma
l_int|0x00000000
comma
multiline_comment|/* 003B */
l_int|0x0004f5c2
comma
l_int|0x00000000
comma
l_int|0x0003640a
comma
l_int|0x00000000
comma
multiline_comment|/* 003D */
l_int|0x00000000
comma
l_int|0x000e5084
comma
l_int|0x00000000
comma
l_int|0x000eb844
comma
multiline_comment|/* 003F */
l_int|0x00007001
comma
l_int|0x00000000
comma
l_int|0x00000734
comma
l_int|0x00001000
comma
multiline_comment|/* 0041 */
l_int|0x00010705
comma
l_int|0x000a6880
comma
l_int|0x00006a88
comma
l_int|0x000c75c4
comma
multiline_comment|/* SPDIFITASK */
multiline_comment|/* 0043 */
l_int|0x0006a108
comma
l_int|0x000cf2c4
comma
l_int|0x0004f4c0
comma
l_int|0x000d5384
comma
multiline_comment|/* 0045 */
l_int|0x0007e48a
comma
l_int|0x00000000
comma
l_int|0x00067718
comma
l_int|0x00001000
comma
multiline_comment|/* 0047 */
l_int|0x0007a418
comma
l_int|0x00001000
comma
l_int|0x0007221a
comma
l_int|0x00000000
comma
multiline_comment|/* 0049 */
l_int|0x0005d402
comma
l_int|0x00014500
comma
l_int|0x000b8630
comma
l_int|0x00001002
comma
multiline_comment|/* 004B */
l_int|0x00004418
comma
l_int|0x00001780
comma
l_int|0x000e243d
comma
l_int|0x000d394a
comma
multiline_comment|/* 004D */
l_int|0x00049705
comma
l_int|0x00000000
comma
l_int|0x0007d530
comma
l_int|0x000b4240
comma
multiline_comment|/* 004F */
l_int|0x000ac0f2
comma
l_int|0x00001002
comma
l_int|0x00014414
comma
l_int|0x00000000
comma
multiline_comment|/* 0051 */
l_int|0x00004c90
comma
l_int|0x00001000
comma
l_int|0x0005d705
comma
l_int|0x00000000
comma
multiline_comment|/* 0053 */
l_int|0x00004f25
comma
l_int|0x00098240
comma
l_int|0x00004725
comma
l_int|0x00000000
comma
multiline_comment|/* 0055 */
l_int|0x0000e48a
comma
l_int|0x00000000
comma
l_int|0x00027295
comma
l_int|0x0009c2c0
comma
multiline_comment|/* 0057 */
l_int|0x0007df25
comma
l_int|0x00000000
comma
l_int|0x000ac030
comma
l_int|0x00001003
comma
multiline_comment|/* 0059 */
l_int|0x0005f718
comma
l_int|0x000fe798
comma
l_int|0x00029314
comma
l_int|0x000bcb80
comma
multiline_comment|/* 005B */
l_int|0x00000930
comma
l_int|0x000b0e00
comma
l_int|0x0004f5c0
comma
l_int|0x000de204
comma
multiline_comment|/* 005D */
l_int|0x000884a0
comma
l_int|0x00001003
comma
l_int|0x0007cf25
comma
l_int|0x000e3560
comma
multiline_comment|/* 005F */
l_int|0x00049118
comma
l_int|0x00000000
comma
l_int|0x00049118
comma
l_int|0x000d888a
comma
multiline_comment|/* 0061 */
l_int|0x0007dd02
comma
l_int|0x000c6efa
comma
l_int|0x0000c434
comma
l_int|0x00030040
comma
multiline_comment|/* 0063 */
l_int|0x000fda82
comma
l_int|0x000c2312
comma
l_int|0x000fdc0e
comma
l_int|0x00001001
comma
multiline_comment|/* 0065 */
l_int|0x00083402
comma
l_int|0x000c2b92
comma
l_int|0x000706b0
comma
l_int|0x00001003
comma
multiline_comment|/* 0067 */
l_int|0x00075a82
comma
l_int|0x00000000
comma
l_int|0x0000d625
comma
l_int|0x000b0940
comma
multiline_comment|/* 0069 */
l_int|0x0000840e
comma
l_int|0x00001002
comma
l_int|0x0000aabc
comma
l_int|0x000c511e
comma
multiline_comment|/* 006B */
l_int|0x00078730
comma
l_int|0x00001003
comma
l_int|0x0000aaf4
comma
l_int|0x000e910a
comma
multiline_comment|/* 006D */
l_int|0x0004628a
comma
l_int|0x00000000
comma
l_int|0x00006aca
comma
l_int|0x00000000
comma
multiline_comment|/* 006F */
l_int|0x00000930
comma
l_int|0x00000000
comma
l_int|0x0004f5c0
comma
l_int|0x00069c80
comma
multiline_comment|/* 0071 */
l_int|0x00046ac0
comma
l_int|0x00000000
comma
l_int|0x0003c40a
comma
l_int|0x000fc898
comma
multiline_comment|/* 0073 */
l_int|0x00049118
comma
l_int|0x00090e00
comma
l_int|0x0006c10a
comma
l_int|0x00000000
comma
multiline_comment|/* 0075 */
l_int|0x00000000
comma
l_int|0x000e5084
comma
l_int|0x00000000
comma
l_int|0x000eb844
comma
multiline_comment|/* 0077 */
l_int|0x00007001
comma
l_int|0x00000000
comma
l_int|0x00000734
comma
l_int|0x00001000
comma
multiline_comment|/* 0079 */
l_int|0x00010705
comma
l_int|0x000a6880
comma
l_int|0x00006a88
comma
l_int|0x000c75c4
comma
multiline_comment|/* SPDIFOTASK */
multiline_comment|/* 007B */
l_int|0x0006a108
comma
l_int|0x000c0000
comma
l_int|0x0004f4c0
comma
l_int|0x000c3245
comma
multiline_comment|/* 007D */
l_int|0x0000a418
comma
l_int|0x00001000
comma
l_int|0x0003a20a
comma
l_int|0x00000000
comma
multiline_comment|/* 007F */
l_int|0x00004418
comma
l_int|0x00001380
comma
l_int|0x000e243d
comma
l_int|0x000d394a
comma
multiline_comment|/* 0081 */
l_int|0x000c9705
comma
l_int|0x000def92
comma
l_int|0x0008c030
comma
l_int|0x00001004
comma
multiline_comment|/* 0083 */
l_int|0x0005f718
comma
l_int|0x000fe798
comma
l_int|0x00000000
comma
l_int|0x000c0000
comma
multiline_comment|/* 0085 */
l_int|0x00005725
comma
l_int|0x00000000
comma
l_int|0x000704a0
comma
l_int|0x00001004
comma
multiline_comment|/* 0087 */
l_int|0x00029314
comma
l_int|0x000b4780
comma
l_int|0x0003cf25
comma
l_int|0x000b8600
comma
multiline_comment|/* 0089 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x000c0000
comma
multiline_comment|/* 008B */
l_int|0x00000000
comma
l_int|0x00042c80
comma
l_int|0x0001dec1
comma
l_int|0x000e488c
comma
multiline_comment|/* 008D */
l_int|0x00031114
comma
l_int|0x00000000
comma
l_int|0x0004f5c2
comma
l_int|0x00000000
comma
multiline_comment|/* 008F */
l_int|0x0004a918
comma
l_int|0x00098600
comma
l_int|0x0006c28a
comma
l_int|0x00000000
comma
multiline_comment|/* 0091 */
l_int|0x00000000
comma
l_int|0x000e5084
comma
l_int|0x00000000
comma
l_int|0x000eb844
comma
multiline_comment|/* 0093 */
l_int|0x00007001
comma
l_int|0x00000000
comma
l_int|0x00000734
comma
l_int|0x00001000
comma
multiline_comment|/* 0095 */
l_int|0x00010705
comma
l_int|0x000a6880
comma
l_int|0x00006a88
comma
l_int|0x000c75c4
comma
multiline_comment|/* ASYNCHFGTXCODE */
multiline_comment|/* 0097 */
l_int|0x0002a880
comma
l_int|0x000b4e40
comma
l_int|0x00042214
comma
l_int|0x000e5548
comma
multiline_comment|/* 0099 */
l_int|0x000542bf
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x000481c0
comma
multiline_comment|/* 009B */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000030
comma
multiline_comment|/* 009D */
l_int|0x0000072d
comma
l_int|0x000fbf8a
comma
l_int|0x00077f94
comma
l_int|0x000ea7df
comma
multiline_comment|/* 009F */
l_int|0x0002ac95
comma
l_int|0x000d3145
comma
l_int|0x00002731
comma
l_int|0x00001400
comma
multiline_comment|/* 00A1 */
l_int|0x00006288
comma
l_int|0x000c71c4
comma
l_int|0x00014108
comma
l_int|0x000e6044
comma
multiline_comment|/* 00A3 */
l_int|0x00035408
comma
l_int|0x00000000
comma
l_int|0x00025418
comma
l_int|0x000a0ec0
comma
multiline_comment|/* 00A5 */
l_int|0x0001443d
comma
l_int|0x000ca21e
comma
l_int|0x00046595
comma
l_int|0x000d730c
comma
multiline_comment|/* 00A7 */
l_int|0x0006538e
comma
l_int|0x00000000
comma
l_int|0x00064630
comma
l_int|0x00001005
comma
multiline_comment|/* 00A9 */
l_int|0x000e7b0e
comma
l_int|0x000df782
comma
l_int|0x000746b0
comma
l_int|0x00001005
comma
multiline_comment|/* 00AB */
l_int|0x00036f05
comma
l_int|0x000c0000
comma
l_int|0x00043695
comma
l_int|0x000d598c
comma
multiline_comment|/* 00AD */
l_int|0x0005331a
comma
l_int|0x000f2185
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 00AF */
l_int|0x000007ae
comma
l_int|0x000bdb00
comma
l_int|0x00040630
comma
l_int|0x00001400
comma
multiline_comment|/* 00B1 */
l_int|0x0005e708
comma
l_int|0x000c0000
comma
l_int|0x0007ef30
comma
l_int|0x000b1c00
comma
multiline_comment|/* 00B3 */
l_int|0x000d86a0
comma
l_int|0x00001005
comma
l_int|0x00066408
comma
l_int|0x000c0000
comma
multiline_comment|/* 00B5 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00021843
comma
l_int|0x00000000
comma
multiline_comment|/* 00B7 */
l_int|0x00000cac
comma
l_int|0x00062c00
comma
l_int|0x00001dac
comma
l_int|0x00063400
comma
multiline_comment|/* 00B9 */
l_int|0x00002cac
comma
l_int|0x0006cc80
comma
l_int|0x000db943
comma
l_int|0x000e5ca1
comma
multiline_comment|/* 00BB */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x0006680a
comma
l_int|0x000f3205
comma
multiline_comment|/* 00BD */
l_int|0x00042730
comma
l_int|0x00001400
comma
multiline_comment|/* ASYNCHFGRXCODE */
multiline_comment|/* 00BE */
l_int|0x00014108
comma
l_int|0x000f2204
comma
l_int|0x00025418
comma
l_int|0x000a2ec0
comma
multiline_comment|/* 00C0 */
l_int|0x00015dbd
comma
l_int|0x00038100
comma
l_int|0x00015dbc
comma
l_int|0x00000000
comma
multiline_comment|/* 00C2 */
l_int|0x0005e415
comma
l_int|0x00034880
comma
l_int|0x0001258a
comma
l_int|0x000d730c
comma
multiline_comment|/* 00C4 */
l_int|0x0006538e
comma
l_int|0x000baa40
comma
l_int|0x00060630
comma
l_int|0x00001006
comma
multiline_comment|/* 00C6 */
l_int|0x00067b0e
comma
l_int|0x000ac380
comma
l_int|0x0003ef05
comma
l_int|0x00000000
comma
multiline_comment|/* 00C8 */
l_int|0x0000f734
comma
l_int|0x0001c300
comma
l_int|0x000586b0
comma
l_int|0x00001400
comma
multiline_comment|/* 00CA */
l_int|0x000b6f05
comma
l_int|0x000c3a00
comma
l_int|0x00048f05
comma
l_int|0x00000000
comma
multiline_comment|/* 00CC */
l_int|0x0005b695
comma
l_int|0x0008c380
comma
l_int|0x0002058e
comma
l_int|0x00000000
comma
multiline_comment|/* 00CE */
l_int|0x000500b0
comma
l_int|0x00001400
comma
l_int|0x0002b318
comma
l_int|0x000e998d
comma
multiline_comment|/* 00D0 */
l_int|0x0006430a
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x000ef384
comma
multiline_comment|/* 00D2 */
l_int|0x00004725
comma
l_int|0x000c0000
comma
l_int|0x00000000
comma
l_int|0x000f3204
comma
multiline_comment|/* 00D4 */
l_int|0x00004f25
comma
l_int|0x000c0000
comma
l_int|0x00080000
comma
l_int|0x000e5ca1
comma
multiline_comment|/* 00D6 */
l_int|0x000cb943
comma
l_int|0x000e5ca1
comma
l_int|0x0004b943
comma
l_int|0x00000000
comma
multiline_comment|/* 00D8 */
l_int|0x00040730
comma
l_int|0x00001400
comma
l_int|0x000cb943
comma
l_int|0x000e5ca1
comma
multiline_comment|/* 00DA */
l_int|0x0004b943
comma
l_int|0x00000000
)brace
suffix:semicolon
multiline_comment|/* #CODE_END */
DECL|variable|cwcasync_segments
r_static
id|segment_desc_t
id|cwcasync_segments
(braket
)braket
op_assign
(brace
(brace
id|SEGTYPE_SP_PROGRAM
comma
l_int|0x00000000
comma
l_int|0x000001b6
comma
id|cwcasync_code
)brace
comma
)brace
suffix:semicolon
DECL|variable|cwcasync_module
r_static
id|dsp_module_desc_t
id|cwcasync_module
op_assign
(brace
l_string|&quot;cwcasync&quot;
comma
(brace
l_int|32
comma
id|cwcasync_symbols
)brace
comma
l_int|1
comma
id|cwcasync_segments
comma
)brace
suffix:semicolon
macro_line|#endif /* __HEADER_cwcasync_H__ */
eof
