multiline_comment|/* generated from cwc4630.osp DO NOT MODIFY */
macro_line|#ifndef __HEADER_cwc4630_H__
DECL|macro|__HEADER_cwc4630_H__
mdefine_line|#define __HEADER_cwc4630_H__
DECL|variable|cwc4630_symbols
r_static
id|symbol_entry_t
id|cwc4630_symbols
(braket
)braket
op_assign
(brace
(brace
l_int|0x0000
comma
l_string|&quot;BEGINADDRESS&quot;
comma
l_int|0x00
)brace
comma
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
l_int|0x0070
comma
l_string|&quot;SPOSCB&quot;
comma
l_int|0x02
)brace
comma
(brace
l_int|0x0107
comma
l_string|&quot;TASKTREETHREAD&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x013c
comma
l_string|&quot;TASKTREEHEADERCODE&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0145
comma
l_string|&quot;FGTASKTREEHEADERCODE&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0169
comma
l_string|&quot;NULLALGORITHM&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x016d
comma
l_string|&quot;HFGEXECCHILD&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x016e
comma
l_string|&quot;HFGEXECCHILD_98&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0170
comma
l_string|&quot;HFGEXECCHILD_PUSH1IND&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0173
comma
l_string|&quot;HFGEXECSIBLING&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0175
comma
l_string|&quot;HFGEXECSIBLING_298&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0176
comma
l_string|&quot;HFGEXECSIBLING_2IND1&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0179
comma
l_string|&quot;S16_CODECOUTPUTTASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0194
comma
l_string|&quot;#CODE_END&quot;
comma
l_int|0x00
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* cwc4630 symbols */
DECL|variable|cwc4630_code
r_static
id|u32
id|cwc4630_code
(braket
)braket
op_assign
(brace
multiline_comment|/* BEGINADDRESS */
multiline_comment|/* 0000 */
l_int|0x00040730
comma
l_int|0x00001002
comma
l_int|0x000f619e
comma
l_int|0x00001003
comma
multiline_comment|/* 0002 */
l_int|0x00001705
comma
l_int|0x00001400
comma
l_int|0x000a411e
comma
l_int|0x00001003
comma
multiline_comment|/* 0004 */
l_int|0x00040730
comma
l_int|0x00001002
comma
l_int|0x000f619e
comma
l_int|0x00001003
comma
multiline_comment|/* 0006 */
l_int|0x00009705
comma
l_int|0x00001400
comma
l_int|0x000a411e
comma
l_int|0x00001003
comma
multiline_comment|/* 0008 */
l_int|0x00040730
comma
l_int|0x00001002
comma
l_int|0x000f619e
comma
l_int|0x00001003
comma
multiline_comment|/* 000A */
l_int|0x00011705
comma
l_int|0x00001400
comma
l_int|0x000a411e
comma
l_int|0x00001003
comma
multiline_comment|/* 000C */
l_int|0x00040730
comma
l_int|0x00001002
comma
l_int|0x000f619e
comma
l_int|0x00001003
comma
multiline_comment|/* 000E */
l_int|0x00019705
comma
l_int|0x00001400
comma
l_int|0x000a411e
comma
l_int|0x00001003
comma
multiline_comment|/* 0010 */
l_int|0x00040730
comma
l_int|0x00001002
comma
l_int|0x000f619e
comma
l_int|0x00001003
comma
multiline_comment|/* 0012 */
l_int|0x00021705
comma
l_int|0x00001400
comma
l_int|0x000a411e
comma
l_int|0x00001003
comma
multiline_comment|/* 0014 */
l_int|0x00040730
comma
l_int|0x00001002
comma
l_int|0x000f619e
comma
l_int|0x00001003
comma
multiline_comment|/* 0016 */
l_int|0x00029705
comma
l_int|0x00001400
comma
l_int|0x000a411e
comma
l_int|0x00001003
comma
multiline_comment|/* 0018 */
l_int|0x00040730
comma
l_int|0x00001002
comma
l_int|0x000f619e
comma
l_int|0x00001003
comma
multiline_comment|/* 001A */
l_int|0x00031705
comma
l_int|0x00001400
comma
l_int|0x000a411e
comma
l_int|0x00001003
comma
multiline_comment|/* 001C */
l_int|0x00040730
comma
l_int|0x00001002
comma
l_int|0x000f619e
comma
l_int|0x00001003
comma
multiline_comment|/* 001E */
l_int|0x00039705
comma
l_int|0x00001400
comma
l_int|0x000a411e
comma
l_int|0x00001003
comma
multiline_comment|/* 0020 */
l_int|0x000fe19e
comma
l_int|0x00001003
comma
l_int|0x0009c730
comma
l_int|0x00001003
comma
multiline_comment|/* 0022 */
l_int|0x0008e19c
comma
l_int|0x00001003
comma
l_int|0x000083c1
comma
l_int|0x00093040
comma
multiline_comment|/* 0024 */
l_int|0x00098730
comma
l_int|0x00001002
comma
l_int|0x000ee19e
comma
l_int|0x00001003
comma
multiline_comment|/* 0026 */
l_int|0x00009705
comma
l_int|0x00001400
comma
l_int|0x000a211e
comma
l_int|0x00001003
comma
multiline_comment|/* 0028 */
l_int|0x00098730
comma
l_int|0x00001002
comma
l_int|0x000ee19e
comma
l_int|0x00001003
comma
multiline_comment|/* 002A */
l_int|0x00011705
comma
l_int|0x00001400
comma
l_int|0x000a211e
comma
l_int|0x00001003
comma
multiline_comment|/* 002C */
l_int|0x00098730
comma
l_int|0x00001002
comma
l_int|0x000ee19e
comma
l_int|0x00001003
comma
multiline_comment|/* 002E */
l_int|0x00019705
comma
l_int|0x00001400
comma
l_int|0x000a211e
comma
l_int|0x00001003
comma
multiline_comment|/* 0030 */
l_int|0x00098730
comma
l_int|0x00001002
comma
l_int|0x000ee19e
comma
l_int|0x00001003
comma
multiline_comment|/* 0032 */
l_int|0x00021705
comma
l_int|0x00001400
comma
l_int|0x000a211e
comma
l_int|0x00001003
comma
multiline_comment|/* 0034 */
l_int|0x00098730
comma
l_int|0x00001002
comma
l_int|0x000ee19e
comma
l_int|0x00001003
comma
multiline_comment|/* 0036 */
l_int|0x00029705
comma
l_int|0x00001400
comma
l_int|0x000a211e
comma
l_int|0x00001003
comma
multiline_comment|/* 0038 */
l_int|0x00098730
comma
l_int|0x00001002
comma
l_int|0x000ee19e
comma
l_int|0x00001003
comma
multiline_comment|/* 003A */
l_int|0x00031705
comma
l_int|0x00001400
comma
l_int|0x000a211e
comma
l_int|0x00001003
comma
multiline_comment|/* 003C */
l_int|0x00098730
comma
l_int|0x00001002
comma
l_int|0x000ee19e
comma
l_int|0x00001003
comma
multiline_comment|/* 003E */
l_int|0x00039705
comma
l_int|0x00001400
comma
l_int|0x000a211e
comma
l_int|0x00001003
comma
multiline_comment|/* 0040 */
l_int|0x0001a730
comma
l_int|0x00001008
comma
l_int|0x000e2730
comma
l_int|0x00001002
comma
multiline_comment|/* 0042 */
l_int|0x0000a731
comma
l_int|0x00001002
comma
l_int|0x0000a731
comma
l_int|0x00001002
comma
multiline_comment|/* 0044 */
l_int|0x0000a731
comma
l_int|0x00001002
comma
l_int|0x0000a731
comma
l_int|0x00001002
comma
multiline_comment|/* 0046 */
l_int|0x0000a731
comma
l_int|0x00001002
comma
l_int|0x0000a731
comma
l_int|0x00001002
comma
multiline_comment|/* 0048 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x000f619c
comma
l_int|0x00001003
comma
multiline_comment|/* 004A */
l_int|0x0007f801
comma
l_int|0x000c0000
comma
l_int|0x00000037
comma
l_int|0x00001000
comma
multiline_comment|/* 004C */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 004E */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0050 */
l_int|0x00000000
comma
l_int|0x000c0000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0052 */
l_int|0x0000373c
comma
l_int|0x00001000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0054 */
l_int|0x000ee19c
comma
l_int|0x00001003
comma
l_int|0x0007f801
comma
l_int|0x000c0000
comma
multiline_comment|/* 0056 */
l_int|0x00000037
comma
l_int|0x00001000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0058 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 005A */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x0000273c
comma
l_int|0x00001000
comma
multiline_comment|/* 005C */
l_int|0x00000033
comma
l_int|0x00001000
comma
l_int|0x000e679e
comma
l_int|0x00001003
comma
multiline_comment|/* 005E */
l_int|0x00007705
comma
l_int|0x00001400
comma
l_int|0x000ac71e
comma
l_int|0x00001003
comma
multiline_comment|/* 0060 */
l_int|0x00087fc1
comma
l_int|0x000c3be0
comma
l_int|0x0007f801
comma
l_int|0x000c0000
comma
multiline_comment|/* 0062 */
l_int|0x00000037
comma
l_int|0x00001000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0064 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0066 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x0000a730
comma
l_int|0x00001003
comma
multiline_comment|/* 0068 */
l_int|0x00000033
comma
l_int|0x00001000
comma
l_int|0x0007f801
comma
l_int|0x000c0000
comma
multiline_comment|/* 006A */
l_int|0x00000037
comma
l_int|0x00001000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 006C */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 006E */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x000c0000
comma
multiline_comment|/* 0070 */
l_int|0x00000032
comma
l_int|0x00001000
comma
l_int|0x0000273d
comma
l_int|0x00001000
comma
multiline_comment|/* 0072 */
l_int|0x0004a730
comma
l_int|0x00001003
comma
l_int|0x00000f41
comma
l_int|0x00097140
comma
multiline_comment|/* 0074 */
l_int|0x0000a841
comma
l_int|0x0009b240
comma
l_int|0x0000a0c1
comma
l_int|0x0009f040
comma
multiline_comment|/* 0076 */
l_int|0x0001c641
comma
l_int|0x00093540
comma
l_int|0x0001cec1
comma
l_int|0x0009b5c0
comma
multiline_comment|/* 0078 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x0001bf05
comma
l_int|0x0003fc40
comma
multiline_comment|/* 007A */
l_int|0x00002725
comma
l_int|0x000aa400
comma
l_int|0x00013705
comma
l_int|0x00093a00
comma
multiline_comment|/* 007C */
l_int|0x0000002e
comma
l_int|0x0009d6c0
comma
l_int|0x0002ef8a
comma
l_int|0x00000000
comma
multiline_comment|/* 007E */
l_int|0x00040630
comma
l_int|0x00001004
comma
l_int|0x0004ef0a
comma
l_int|0x000eb785
comma
multiline_comment|/* 0080 */
l_int|0x0003fc8a
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x000c70e0
comma
multiline_comment|/* 0082 */
l_int|0x0007d182
comma
l_int|0x0002c640
comma
l_int|0x00008630
comma
l_int|0x00001004
comma
multiline_comment|/* 0084 */
l_int|0x000799b8
comma
l_int|0x0002c6c0
comma
l_int|0x00031705
comma
l_int|0x00092240
comma
multiline_comment|/* 0086 */
l_int|0x00039f05
comma
l_int|0x000932c0
comma
l_int|0x0003520a
comma
l_int|0x00000000
comma
multiline_comment|/* 0088 */
l_int|0x00070731
comma
l_int|0x0000100b
comma
l_int|0x00010705
comma
l_int|0x000b20c0
comma
multiline_comment|/* 008A */
l_int|0x00000000
comma
l_int|0x000eba44
comma
l_int|0x00032108
comma
l_int|0x000c60c4
comma
multiline_comment|/* 008C */
l_int|0x00065208
comma
l_int|0x000c2917
comma
l_int|0x000486b0
comma
l_int|0x00001007
comma
multiline_comment|/* 008E */
l_int|0x00012f05
comma
l_int|0x00036880
comma
l_int|0x0002818e
comma
l_int|0x000c0000
comma
multiline_comment|/* 0090 */
l_int|0x0004410a
comma
l_int|0x00000000
comma
l_int|0x00048630
comma
l_int|0x00001007
comma
multiline_comment|/* 0092 */
l_int|0x00029705
comma
l_int|0x000c0000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0094 */
l_int|0x00003fc1
comma
l_int|0x0003fc40
comma
l_int|0x000037c1
comma
l_int|0x00091b40
comma
multiline_comment|/* 0096 */
l_int|0x00003fc1
comma
l_int|0x000911c0
comma
l_int|0x000037c1
comma
l_int|0x000957c0
comma
multiline_comment|/* 0098 */
l_int|0x00003fc1
comma
l_int|0x000951c0
comma
l_int|0x000037c1
comma
l_int|0x00000000
comma
multiline_comment|/* 009A */
l_int|0x00003fc1
comma
l_int|0x000991c0
comma
l_int|0x000037c1
comma
l_int|0x00000000
comma
multiline_comment|/* 009C */
l_int|0x00003fc1
comma
l_int|0x0009d1c0
comma
l_int|0x000037c1
comma
l_int|0x00000000
comma
multiline_comment|/* 009E */
l_int|0x0001ccc1
comma
l_int|0x000915c0
comma
l_int|0x0001c441
comma
l_int|0x0009d800
comma
multiline_comment|/* 00A0 */
l_int|0x0009cdc1
comma
l_int|0x00091240
comma
l_int|0x0001c541
comma
l_int|0x00091d00
comma
multiline_comment|/* 00A2 */
l_int|0x0009cfc1
comma
l_int|0x00095240
comma
l_int|0x0001c741
comma
l_int|0x00095c80
comma
multiline_comment|/* 00A4 */
l_int|0x000e8ca9
comma
l_int|0x00099240
comma
l_int|0x000e85ad
comma
l_int|0x00095640
comma
multiline_comment|/* 00A6 */
l_int|0x00069ca9
comma
l_int|0x00099d80
comma
l_int|0x000e952d
comma
l_int|0x00099640
comma
multiline_comment|/* 00A8 */
l_int|0x000eaca9
comma
l_int|0x0009d6c0
comma
l_int|0x000ea5ad
comma
l_int|0x00091a40
comma
multiline_comment|/* 00AA */
l_int|0x0006bca9
comma
l_int|0x0009de80
comma
l_int|0x000eb52d
comma
l_int|0x00095a40
comma
multiline_comment|/* 00AC */
l_int|0x000ecca9
comma
l_int|0x00099ac0
comma
l_int|0x000ec5ad
comma
l_int|0x0009da40
comma
multiline_comment|/* 00AE */
l_int|0x000edca9
comma
l_int|0x0009d300
comma
l_int|0x000a6e0a
comma
l_int|0x00001000
comma
multiline_comment|/* 00B0 */
l_int|0x000ed52d
comma
l_int|0x00091e40
comma
l_int|0x000eeca9
comma
l_int|0x00095ec0
comma
multiline_comment|/* 00B2 */
l_int|0x000ee5ad
comma
l_int|0x00099e40
comma
l_int|0x0006fca9
comma
l_int|0x00002500
comma
multiline_comment|/* 00B4 */
l_int|0x000fb208
comma
l_int|0x000c59a0
comma
l_int|0x000ef52d
comma
l_int|0x0009de40
comma
multiline_comment|/* 00B6 */
l_int|0x00068ca9
comma
l_int|0x000912c1
comma
l_int|0x000683ad
comma
l_int|0x00095241
comma
multiline_comment|/* 00B8 */
l_int|0x00020f05
comma
l_int|0x000991c1
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 00BA */
l_int|0x00086f88
comma
l_int|0x00001000
comma
l_int|0x0009cf81
comma
l_int|0x000b5340
comma
multiline_comment|/* 00BC */
l_int|0x0009c701
comma
l_int|0x000b92c0
comma
l_int|0x0009de81
comma
l_int|0x000bd300
comma
multiline_comment|/* 00BE */
l_int|0x0009d601
comma
l_int|0x000b1700
comma
l_int|0x0001fd81
comma
l_int|0x000b9d80
comma
multiline_comment|/* 00C0 */
l_int|0x0009f501
comma
l_int|0x000b57c0
comma
l_int|0x000a0f81
comma
l_int|0x000bd740
comma
multiline_comment|/* 00C2 */
l_int|0x00020701
comma
l_int|0x000b5c80
comma
l_int|0x000a1681
comma
l_int|0x000b97c0
comma
multiline_comment|/* 00C4 */
l_int|0x00021601
comma
l_int|0x00002500
comma
l_int|0x000a0701
comma
l_int|0x000b9b40
comma
multiline_comment|/* 00C6 */
l_int|0x000a0f81
comma
l_int|0x000b1bc0
comma
l_int|0x00021681
comma
l_int|0x00002d00
comma
multiline_comment|/* 00C8 */
l_int|0x00020f81
comma
l_int|0x000bd800
comma
l_int|0x000a0701
comma
l_int|0x000b5bc0
comma
multiline_comment|/* 00CA */
l_int|0x00021601
comma
l_int|0x00003500
comma
l_int|0x000a0f81
comma
l_int|0x000b5f40
comma
multiline_comment|/* 00CC */
l_int|0x000a0701
comma
l_int|0x000bdbc0
comma
l_int|0x00021681
comma
l_int|0x00003d00
comma
multiline_comment|/* 00CE */
l_int|0x00020f81
comma
l_int|0x000b1d00
comma
l_int|0x000a0701
comma
l_int|0x000b1fc0
comma
multiline_comment|/* 00D0 */
l_int|0x00021601
comma
l_int|0x00020500
comma
l_int|0x00020f81
comma
l_int|0x000b1341
comma
multiline_comment|/* 00D2 */
l_int|0x000a0701
comma
l_int|0x000b9fc0
comma
l_int|0x00021681
comma
l_int|0x00020d00
comma
multiline_comment|/* 00D4 */
l_int|0x00020f81
comma
l_int|0x000bde80
comma
l_int|0x000a0701
comma
l_int|0x000bdfc0
comma
multiline_comment|/* 00D6 */
l_int|0x00021601
comma
l_int|0x00021500
comma
l_int|0x00020f81
comma
l_int|0x000b9341
comma
multiline_comment|/* 00D8 */
l_int|0x00020701
comma
l_int|0x000b53c1
comma
l_int|0x00021681
comma
l_int|0x00021d00
comma
multiline_comment|/* 00DA */
l_int|0x000a0f81
comma
l_int|0x000d0380
comma
l_int|0x0000b601
comma
l_int|0x000b15c0
comma
multiline_comment|/* 00DC */
l_int|0x00007b01
comma
l_int|0x00000000
comma
l_int|0x00007b81
comma
l_int|0x000bd1c0
comma
multiline_comment|/* 00DE */
l_int|0x00007b01
comma
l_int|0x00000000
comma
l_int|0x00007b81
comma
l_int|0x000b91c0
comma
multiline_comment|/* 00E0 */
l_int|0x00007b01
comma
l_int|0x000b57c0
comma
l_int|0x00007b81
comma
l_int|0x000b51c0
comma
multiline_comment|/* 00E2 */
l_int|0x00007b01
comma
l_int|0x000b1b40
comma
l_int|0x00007b81
comma
l_int|0x000b11c0
comma
multiline_comment|/* 00E4 */
l_int|0x00087b01
comma
l_int|0x000c3dc0
comma
l_int|0x0007e488
comma
l_int|0x000d7e45
comma
multiline_comment|/* 00E6 */
l_int|0x00000000
comma
l_int|0x000d7a44
comma
l_int|0x0007e48a
comma
l_int|0x00000000
comma
multiline_comment|/* 00E8 */
l_int|0x00011f05
comma
l_int|0x00084080
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 00EA */
l_int|0x00001705
comma
l_int|0x000b3540
comma
l_int|0x00008a01
comma
l_int|0x000bf040
comma
multiline_comment|/* 00EC */
l_int|0x00007081
comma
l_int|0x000bb5c0
comma
l_int|0x00055488
comma
l_int|0x00000000
comma
multiline_comment|/* 00EE */
l_int|0x0000d482
comma
l_int|0x0003fc40
comma
l_int|0x0003fc88
comma
l_int|0x00000000
comma
multiline_comment|/* 00F0 */
l_int|0x0001e401
comma
l_int|0x000b3a00
comma
l_int|0x0001ec81
comma
l_int|0x000bd6c0
comma
multiline_comment|/* 00F2 */
l_int|0x0002ef88
comma
l_int|0x000e7784
comma
l_int|0x00056f08
comma
l_int|0x00000000
comma
multiline_comment|/* 00F4 */
l_int|0x000d86b0
comma
l_int|0x00001007
comma
l_int|0x00008281
comma
l_int|0x000bb240
comma
multiline_comment|/* 00F6 */
l_int|0x0000b801
comma
l_int|0x000b7140
comma
l_int|0x00007888
comma
l_int|0x00000000
comma
multiline_comment|/* 00F8 */
l_int|0x0000073c
comma
l_int|0x00001000
comma
l_int|0x0007f188
comma
l_int|0x000c0000
comma
multiline_comment|/* 00FA */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00055288
comma
l_int|0x000c555c
comma
multiline_comment|/* 00FC */
l_int|0x0005528a
comma
l_int|0x000c0000
comma
l_int|0x0009fa88
comma
l_int|0x000c5d00
comma
multiline_comment|/* 00FE */
l_int|0x0000fa88
comma
l_int|0x00000000
comma
l_int|0x00000032
comma
l_int|0x00001000
comma
multiline_comment|/* 0100 */
l_int|0x0000073d
comma
l_int|0x00001000
comma
l_int|0x0007f188
comma
l_int|0x000c0000
comma
multiline_comment|/* 0102 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x0008c01c
comma
l_int|0x00001003
comma
multiline_comment|/* 0104 */
l_int|0x00002705
comma
l_int|0x00001008
comma
l_int|0x0008b201
comma
l_int|0x000c1392
comma
multiline_comment|/* 0106 */
l_int|0x0000ba01
comma
l_int|0x00000000
comma
multiline_comment|/* TASKTREETHREAD */
multiline_comment|/* 0107 */
l_int|0x00008731
comma
l_int|0x00001400
comma
l_int|0x0004c108
comma
l_int|0x000fe0c4
comma
multiline_comment|/* 0109 */
l_int|0x00057488
comma
l_int|0x00000000
comma
l_int|0x000a6388
comma
l_int|0x00001001
comma
multiline_comment|/* 010B */
l_int|0x0008b334
comma
l_int|0x000bc141
comma
l_int|0x0003020e
comma
l_int|0x00000000
comma
multiline_comment|/* 010D */
l_int|0x000986b0
comma
l_int|0x00001008
comma
l_int|0x00003625
comma
l_int|0x000c5dfa
comma
multiline_comment|/* 010F */
l_int|0x000a638a
comma
l_int|0x00001001
comma
l_int|0x0008020e
comma
l_int|0x00001002
comma
multiline_comment|/* 0111 */
l_int|0x0009a6b0
comma
l_int|0x00001008
comma
l_int|0x0007f301
comma
l_int|0x00000000
comma
multiline_comment|/* 0113 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00002725
comma
l_int|0x000a8c40
comma
multiline_comment|/* 0115 */
l_int|0x000000ae
comma
l_int|0x00000000
comma
l_int|0x000e8630
comma
l_int|0x00001008
comma
multiline_comment|/* 0117 */
l_int|0x00000000
comma
l_int|0x000c74e0
comma
l_int|0x0007d182
comma
l_int|0x0002d640
comma
multiline_comment|/* 0119 */
l_int|0x000b8630
comma
l_int|0x00001008
comma
l_int|0x000799b8
comma
l_int|0x0002d6c0
comma
multiline_comment|/* 011B */
l_int|0x0000748a
comma
l_int|0x000c3ec5
comma
l_int|0x0007420a
comma
l_int|0x000c0000
comma
multiline_comment|/* 011D */
l_int|0x00062208
comma
l_int|0x000c4117
comma
l_int|0x000a0630
comma
l_int|0x00001009
comma
multiline_comment|/* 011F */
l_int|0x00000000
comma
l_int|0x000c0000
comma
l_int|0x0001022e
comma
l_int|0x00000000
comma
multiline_comment|/* 0121 */
l_int|0x0006a630
comma
l_int|0x00001009
comma
l_int|0x00000032
comma
l_int|0x00001000
comma
multiline_comment|/* 0123 */
l_int|0x000ca21c
comma
l_int|0x00001003
comma
l_int|0x00005a02
comma
l_int|0x00000000
comma
multiline_comment|/* 0125 */
l_int|0x0001a630
comma
l_int|0x00001009
comma
l_int|0x00000000
comma
l_int|0x000c0000
comma
multiline_comment|/* 0127 */
l_int|0x00000036
comma
l_int|0x00001000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0129 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 012B */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x0003a730
comma
l_int|0x00001008
comma
multiline_comment|/* 012D */
l_int|0x0007f801
comma
l_int|0x000c0000
comma
l_int|0x00000037
comma
l_int|0x00001000
comma
multiline_comment|/* 012F */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0131 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0133 */
l_int|0x0003a730
comma
l_int|0x00001008
comma
l_int|0x00000033
comma
l_int|0x00001000
comma
multiline_comment|/* 0135 */
l_int|0x0003a705
comma
l_int|0x00001008
comma
l_int|0x00007a01
comma
l_int|0x000c0000
comma
multiline_comment|/* 0137 */
l_int|0x000e6288
comma
l_int|0x000d550a
comma
l_int|0x0006428a
comma
l_int|0x00000000
comma
multiline_comment|/* 0139 */
l_int|0x00090730
comma
l_int|0x0000100a
comma
l_int|0x00000000
comma
l_int|0x000c0000
comma
multiline_comment|/* 013B */
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* TASKTREEHEADERCODE */
multiline_comment|/* 013C */
l_int|0x0007aab0
comma
l_int|0x00034880
comma
l_int|0x000a8fb0
comma
l_int|0x0000100b
comma
multiline_comment|/* 013E */
l_int|0x00057488
comma
l_int|0x00000000
comma
l_int|0x00033b94
comma
l_int|0x00081140
comma
multiline_comment|/* 0140 */
l_int|0x000183ae
comma
l_int|0x00000000
comma
l_int|0x000a86b0
comma
l_int|0x0000100b
comma
multiline_comment|/* 0142 */
l_int|0x00022f05
comma
l_int|0x000c3545
comma
l_int|0x0000eb8a
comma
l_int|0x00000000
comma
multiline_comment|/* 0144 */
l_int|0x00042731
comma
l_int|0x00001003
comma
multiline_comment|/* FGTASKTREEHEADERCODE */
multiline_comment|/* 0145 */
l_int|0x0007aab0
comma
l_int|0x00034880
comma
l_int|0x00078fb0
comma
l_int|0x0000100a
comma
multiline_comment|/* 0147 */
l_int|0x00057488
comma
l_int|0x00000000
comma
l_int|0x00033b94
comma
l_int|0x00081140
comma
multiline_comment|/* 0149 */
l_int|0x000183ae
comma
l_int|0x00000000
comma
l_int|0x000b06b0
comma
l_int|0x0000100b
comma
multiline_comment|/* 014B */
l_int|0x00022f05
comma
l_int|0x00000000
comma
l_int|0x00007401
comma
l_int|0x00091140
comma
multiline_comment|/* 014D */
l_int|0x00048f05
comma
l_int|0x000951c0
comma
l_int|0x00042731
comma
l_int|0x00001003
comma
multiline_comment|/* 014F */
l_int|0x0000473d
comma
l_int|0x00001000
comma
l_int|0x000f19b0
comma
l_int|0x000bbc47
comma
multiline_comment|/* 0151 */
l_int|0x00080000
comma
l_int|0x000bffc7
comma
l_int|0x000fe19e
comma
l_int|0x00001003
comma
multiline_comment|/* 0153 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x0008e19c
comma
l_int|0x00001003
comma
multiline_comment|/* 0155 */
l_int|0x000083c1
comma
l_int|0x00093040
comma
l_int|0x00000f41
comma
l_int|0x00097140
comma
multiline_comment|/* 0157 */
l_int|0x0000a841
comma
l_int|0x0009b240
comma
l_int|0x0000a0c1
comma
l_int|0x0009f040
comma
multiline_comment|/* 0159 */
l_int|0x0001c641
comma
l_int|0x00093540
comma
l_int|0x0001cec1
comma
l_int|0x0009b5c0
comma
multiline_comment|/* 015B */
l_int|0x00000000
comma
l_int|0x000fdc44
comma
l_int|0x00055208
comma
l_int|0x00000000
comma
multiline_comment|/* 015D */
l_int|0x00010705
comma
l_int|0x000a2880
comma
l_int|0x0000a23a
comma
l_int|0x00093a00
comma
multiline_comment|/* 015F */
l_int|0x0003fc8a
comma
l_int|0x000df6c5
comma
l_int|0x0004ef0a
comma
l_int|0x000c0000
comma
multiline_comment|/* 0161 */
l_int|0x00012f05
comma
l_int|0x00036880
comma
l_int|0x00065308
comma
l_int|0x000c2997
comma
multiline_comment|/* 0163 */
l_int|0x000086b0
comma
l_int|0x0000100b
comma
l_int|0x0004410a
comma
l_int|0x000d40c7
comma
multiline_comment|/* 0165 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00088730
comma
l_int|0x00001004
comma
multiline_comment|/* 0167 */
l_int|0x00056f0a
comma
l_int|0x000ea105
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* NULLALGORITHM */
multiline_comment|/* 0169 */
l_int|0x0000473d
comma
l_int|0x00001000
comma
l_int|0x000f19b0
comma
l_int|0x000bbc47
comma
multiline_comment|/* 016B */
l_int|0x00080000
comma
l_int|0x000bffc7
comma
l_int|0x0000273d
comma
l_int|0x00001000
comma
multiline_comment|/* HFGEXECCHILD */
multiline_comment|/* 016D */
l_int|0x00000000
comma
l_int|0x000eba44
comma
multiline_comment|/* HFGEXECCHILD_98 */
multiline_comment|/* 016E */
l_int|0x00048f05
comma
l_int|0x0000f440
comma
l_int|0x00007401
comma
l_int|0x0000f7c0
comma
multiline_comment|/* HFGEXECCHILD_PUSH1IND */
multiline_comment|/* 0170 */
l_int|0x00000734
comma
l_int|0x00001000
comma
l_int|0x00010705
comma
l_int|0x000a6880
comma
multiline_comment|/* 0172 */
l_int|0x00006a88
comma
l_int|0x000c75c4
comma
multiline_comment|/* HFGEXECSIBLING */
multiline_comment|/* 0173 */
l_int|0x00000000
comma
l_int|0x000e5084
comma
l_int|0x00000000
comma
l_int|0x000eba44
comma
multiline_comment|/* HFGEXECSIBLING_298 */
multiline_comment|/* 0175 */
l_int|0x00087401
comma
l_int|0x000e4782
comma
multiline_comment|/* HFGEXECSIBLING_2IND1 */
multiline_comment|/* 0176 */
l_int|0x00000734
comma
l_int|0x00001000
comma
l_int|0x00010705
comma
l_int|0x000a6880
comma
multiline_comment|/* 0178 */
l_int|0x00006a88
comma
l_int|0x000c75c4
comma
multiline_comment|/* S16_CODECOUTPUTTASK */
multiline_comment|/* 0179 */
l_int|0x0007c108
comma
l_int|0x000c0000
comma
l_int|0x0007e721
comma
l_int|0x000bed40
comma
multiline_comment|/* 017B */
l_int|0x00005f25
comma
l_int|0x000badc0
comma
l_int|0x0003ba97
comma
l_int|0x000beb80
comma
multiline_comment|/* 017D */
l_int|0x00065590
comma
l_int|0x000b2e00
comma
l_int|0x00033217
comma
l_int|0x00003ec0
comma
multiline_comment|/* 017F */
l_int|0x00065590
comma
l_int|0x000b8e40
comma
l_int|0x0003ed80
comma
l_int|0x000491c0
comma
multiline_comment|/* 0181 */
l_int|0x00073fb0
comma
l_int|0x00074c80
comma
l_int|0x000583a0
comma
l_int|0x0000100c
comma
multiline_comment|/* 0183 */
l_int|0x000ee388
comma
l_int|0x00042970
comma
l_int|0x00008301
comma
l_int|0x00021ef2
comma
multiline_comment|/* 0185 */
l_int|0x000b8f14
comma
l_int|0x0000000f
comma
l_int|0x000c4d8d
comma
l_int|0x0000001b
comma
multiline_comment|/* 0187 */
l_int|0x000d6dc2
comma
l_int|0x000e06c6
comma
l_int|0x000032ac
comma
l_int|0x000c3916
comma
multiline_comment|/* 0189 */
l_int|0x0004edc2
comma
l_int|0x00074c80
comma
l_int|0x00078898
comma
l_int|0x00001000
comma
multiline_comment|/* 018B */
l_int|0x00038894
comma
l_int|0x00000032
comma
l_int|0x000c4d8d
comma
l_int|0x00092e1b
comma
multiline_comment|/* 018D */
l_int|0x000d6dc2
comma
l_int|0x000e06c6
comma
l_int|0x0004edc2
comma
l_int|0x000c1956
comma
multiline_comment|/* 018F */
l_int|0x0000722c
comma
l_int|0x00034a00
comma
l_int|0x00041705
comma
l_int|0x0009ed40
comma
multiline_comment|/* 0191 */
l_int|0x00058730
comma
l_int|0x00001400
comma
l_int|0x000d7488
comma
l_int|0x000c3a00
comma
multiline_comment|/* 0193 */
l_int|0x00048f05
comma
l_int|0x00000000
)brace
suffix:semicolon
multiline_comment|/* #CODE_END */
DECL|variable|cwc4630_parameter
r_static
id|u32
id|cwc4630_parameter
(braket
)braket
op_assign
(brace
multiline_comment|/* 0000 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0004 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0008 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 000C */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0010 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0014 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0018 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 001C */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0020 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0024 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0028 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 002C */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0030 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0034 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0038 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 003C */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0040 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0044 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0048 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 004C */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0050 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0054 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0058 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 005C */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0060 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0064 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0068 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 006C */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0070 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0074 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 0078 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 007C */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
)brace
suffix:semicolon
multiline_comment|/* #PARAMETER_END */
DECL|variable|cwc4630_segments
r_static
id|segment_desc_t
id|cwc4630_segments
(braket
)braket
op_assign
(brace
(brace
id|SEGTYPE_SP_PROGRAM
comma
l_int|0x00000000
comma
l_int|0x00000328
comma
id|cwc4630_code
)brace
comma
(brace
id|SEGTYPE_SP_PARAMETER
comma
l_int|0x00000000
comma
l_int|0x00000080
comma
id|cwc4630_parameter
)brace
comma
)brace
suffix:semicolon
DECL|variable|cwc4630_module
r_static
id|dsp_module_desc_t
id|cwc4630_module
op_assign
(brace
l_string|&quot;cwc4630&quot;
comma
(brace
l_int|38
comma
id|cwc4630_symbols
)brace
comma
l_int|2
comma
id|cwc4630_segments
comma
)brace
suffix:semicolon
macro_line|#endif /* __HEADER_cwc4630_H__ */
eof
