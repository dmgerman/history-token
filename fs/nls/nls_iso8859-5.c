multiline_comment|/*&n; * linux/fs/nls_iso8859-5.c&n; *&n; * Charset iso8859-5 translation tables.&n; * Generated automatically from the Unicode and charset&n; * tables from the Unicode Organization (www.unicode.org).&n; * The Unicode to charset table has only exact mappings.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/nls.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|variable|charset2uni
r_static
m_wchar_t
id|charset2uni
(braket
l_int|256
)braket
op_assign
(brace
multiline_comment|/* 0x00*/
l_int|0x0000
comma
l_int|0x0001
comma
l_int|0x0002
comma
l_int|0x0003
comma
l_int|0x0004
comma
l_int|0x0005
comma
l_int|0x0006
comma
l_int|0x0007
comma
l_int|0x0008
comma
l_int|0x0009
comma
l_int|0x000a
comma
l_int|0x000b
comma
l_int|0x000c
comma
l_int|0x000d
comma
l_int|0x000e
comma
l_int|0x000f
comma
multiline_comment|/* 0x10*/
l_int|0x0010
comma
l_int|0x0011
comma
l_int|0x0012
comma
l_int|0x0013
comma
l_int|0x0014
comma
l_int|0x0015
comma
l_int|0x0016
comma
l_int|0x0017
comma
l_int|0x0018
comma
l_int|0x0019
comma
l_int|0x001a
comma
l_int|0x001b
comma
l_int|0x001c
comma
l_int|0x001d
comma
l_int|0x001e
comma
l_int|0x001f
comma
multiline_comment|/* 0x20*/
l_int|0x0020
comma
l_int|0x0021
comma
l_int|0x0022
comma
l_int|0x0023
comma
l_int|0x0024
comma
l_int|0x0025
comma
l_int|0x0026
comma
l_int|0x0027
comma
l_int|0x0028
comma
l_int|0x0029
comma
l_int|0x002a
comma
l_int|0x002b
comma
l_int|0x002c
comma
l_int|0x002d
comma
l_int|0x002e
comma
l_int|0x002f
comma
multiline_comment|/* 0x30*/
l_int|0x0030
comma
l_int|0x0031
comma
l_int|0x0032
comma
l_int|0x0033
comma
l_int|0x0034
comma
l_int|0x0035
comma
l_int|0x0036
comma
l_int|0x0037
comma
l_int|0x0038
comma
l_int|0x0039
comma
l_int|0x003a
comma
l_int|0x003b
comma
l_int|0x003c
comma
l_int|0x003d
comma
l_int|0x003e
comma
l_int|0x003f
comma
multiline_comment|/* 0x40*/
l_int|0x0040
comma
l_int|0x0041
comma
l_int|0x0042
comma
l_int|0x0043
comma
l_int|0x0044
comma
l_int|0x0045
comma
l_int|0x0046
comma
l_int|0x0047
comma
l_int|0x0048
comma
l_int|0x0049
comma
l_int|0x004a
comma
l_int|0x004b
comma
l_int|0x004c
comma
l_int|0x004d
comma
l_int|0x004e
comma
l_int|0x004f
comma
multiline_comment|/* 0x50*/
l_int|0x0050
comma
l_int|0x0051
comma
l_int|0x0052
comma
l_int|0x0053
comma
l_int|0x0054
comma
l_int|0x0055
comma
l_int|0x0056
comma
l_int|0x0057
comma
l_int|0x0058
comma
l_int|0x0059
comma
l_int|0x005a
comma
l_int|0x005b
comma
l_int|0x005c
comma
l_int|0x005d
comma
l_int|0x005e
comma
l_int|0x005f
comma
multiline_comment|/* 0x60*/
l_int|0x0060
comma
l_int|0x0061
comma
l_int|0x0062
comma
l_int|0x0063
comma
l_int|0x0064
comma
l_int|0x0065
comma
l_int|0x0066
comma
l_int|0x0067
comma
l_int|0x0068
comma
l_int|0x0069
comma
l_int|0x006a
comma
l_int|0x006b
comma
l_int|0x006c
comma
l_int|0x006d
comma
l_int|0x006e
comma
l_int|0x006f
comma
multiline_comment|/* 0x70*/
l_int|0x0070
comma
l_int|0x0071
comma
l_int|0x0072
comma
l_int|0x0073
comma
l_int|0x0074
comma
l_int|0x0075
comma
l_int|0x0076
comma
l_int|0x0077
comma
l_int|0x0078
comma
l_int|0x0079
comma
l_int|0x007a
comma
l_int|0x007b
comma
l_int|0x007c
comma
l_int|0x007d
comma
l_int|0x007e
comma
l_int|0x007f
comma
multiline_comment|/* 0x80*/
l_int|0x0080
comma
l_int|0x0081
comma
l_int|0x0082
comma
l_int|0x0083
comma
l_int|0x0084
comma
l_int|0x0085
comma
l_int|0x0086
comma
l_int|0x0087
comma
l_int|0x0088
comma
l_int|0x0089
comma
l_int|0x008a
comma
l_int|0x008b
comma
l_int|0x008c
comma
l_int|0x008d
comma
l_int|0x008e
comma
l_int|0x008f
comma
multiline_comment|/* 0x90*/
l_int|0x0090
comma
l_int|0x0091
comma
l_int|0x0092
comma
l_int|0x0093
comma
l_int|0x0094
comma
l_int|0x0095
comma
l_int|0x0096
comma
l_int|0x0097
comma
l_int|0x0098
comma
l_int|0x0099
comma
l_int|0x009a
comma
l_int|0x009b
comma
l_int|0x009c
comma
l_int|0x009d
comma
l_int|0x009e
comma
l_int|0x009f
comma
multiline_comment|/* 0xa0*/
l_int|0x00a0
comma
l_int|0x0401
comma
l_int|0x0402
comma
l_int|0x0403
comma
l_int|0x0404
comma
l_int|0x0405
comma
l_int|0x0406
comma
l_int|0x0407
comma
l_int|0x0408
comma
l_int|0x0409
comma
l_int|0x040a
comma
l_int|0x040b
comma
l_int|0x040c
comma
l_int|0x00ad
comma
l_int|0x040e
comma
l_int|0x040f
comma
multiline_comment|/* 0xb0*/
l_int|0x0410
comma
l_int|0x0411
comma
l_int|0x0412
comma
l_int|0x0413
comma
l_int|0x0414
comma
l_int|0x0415
comma
l_int|0x0416
comma
l_int|0x0417
comma
l_int|0x0418
comma
l_int|0x0419
comma
l_int|0x041a
comma
l_int|0x041b
comma
l_int|0x041c
comma
l_int|0x041d
comma
l_int|0x041e
comma
l_int|0x041f
comma
multiline_comment|/* 0xc0*/
l_int|0x0420
comma
l_int|0x0421
comma
l_int|0x0422
comma
l_int|0x0423
comma
l_int|0x0424
comma
l_int|0x0425
comma
l_int|0x0426
comma
l_int|0x0427
comma
l_int|0x0428
comma
l_int|0x0429
comma
l_int|0x042a
comma
l_int|0x042b
comma
l_int|0x042c
comma
l_int|0x042d
comma
l_int|0x042e
comma
l_int|0x042f
comma
multiline_comment|/* 0xd0*/
l_int|0x0430
comma
l_int|0x0431
comma
l_int|0x0432
comma
l_int|0x0433
comma
l_int|0x0434
comma
l_int|0x0435
comma
l_int|0x0436
comma
l_int|0x0437
comma
l_int|0x0438
comma
l_int|0x0439
comma
l_int|0x043a
comma
l_int|0x043b
comma
l_int|0x043c
comma
l_int|0x043d
comma
l_int|0x043e
comma
l_int|0x043f
comma
multiline_comment|/* 0xe0*/
l_int|0x0440
comma
l_int|0x0441
comma
l_int|0x0442
comma
l_int|0x0443
comma
l_int|0x0444
comma
l_int|0x0445
comma
l_int|0x0446
comma
l_int|0x0447
comma
l_int|0x0448
comma
l_int|0x0449
comma
l_int|0x044a
comma
l_int|0x044b
comma
l_int|0x044c
comma
l_int|0x044d
comma
l_int|0x044e
comma
l_int|0x044f
comma
multiline_comment|/* 0xf0*/
l_int|0x2116
comma
l_int|0x0451
comma
l_int|0x0452
comma
l_int|0x0453
comma
l_int|0x0454
comma
l_int|0x0455
comma
l_int|0x0456
comma
l_int|0x0457
comma
l_int|0x0458
comma
l_int|0x0459
comma
l_int|0x045a
comma
l_int|0x045b
comma
l_int|0x045c
comma
l_int|0x00a7
comma
l_int|0x045e
comma
l_int|0x045f
comma
)brace
suffix:semicolon
DECL|variable|page00
r_static
r_int
r_char
id|page00
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x03
comma
l_int|0x04
comma
l_int|0x05
comma
l_int|0x06
comma
l_int|0x07
comma
multiline_comment|/* 0x00-0x07 */
l_int|0x08
comma
l_int|0x09
comma
l_int|0x0a
comma
l_int|0x0b
comma
l_int|0x0c
comma
l_int|0x0d
comma
l_int|0x0e
comma
l_int|0x0f
comma
multiline_comment|/* 0x08-0x0f */
l_int|0x10
comma
l_int|0x11
comma
l_int|0x12
comma
l_int|0x13
comma
l_int|0x14
comma
l_int|0x15
comma
l_int|0x16
comma
l_int|0x17
comma
multiline_comment|/* 0x10-0x17 */
l_int|0x18
comma
l_int|0x19
comma
l_int|0x1a
comma
l_int|0x1b
comma
l_int|0x1c
comma
l_int|0x1d
comma
l_int|0x1e
comma
l_int|0x1f
comma
multiline_comment|/* 0x18-0x1f */
l_int|0x20
comma
l_int|0x21
comma
l_int|0x22
comma
l_int|0x23
comma
l_int|0x24
comma
l_int|0x25
comma
l_int|0x26
comma
l_int|0x27
comma
multiline_comment|/* 0x20-0x27 */
l_int|0x28
comma
l_int|0x29
comma
l_int|0x2a
comma
l_int|0x2b
comma
l_int|0x2c
comma
l_int|0x2d
comma
l_int|0x2e
comma
l_int|0x2f
comma
multiline_comment|/* 0x28-0x2f */
l_int|0x30
comma
l_int|0x31
comma
l_int|0x32
comma
l_int|0x33
comma
l_int|0x34
comma
l_int|0x35
comma
l_int|0x36
comma
l_int|0x37
comma
multiline_comment|/* 0x30-0x37 */
l_int|0x38
comma
l_int|0x39
comma
l_int|0x3a
comma
l_int|0x3b
comma
l_int|0x3c
comma
l_int|0x3d
comma
l_int|0x3e
comma
l_int|0x3f
comma
multiline_comment|/* 0x38-0x3f */
l_int|0x40
comma
l_int|0x41
comma
l_int|0x42
comma
l_int|0x43
comma
l_int|0x44
comma
l_int|0x45
comma
l_int|0x46
comma
l_int|0x47
comma
multiline_comment|/* 0x40-0x47 */
l_int|0x48
comma
l_int|0x49
comma
l_int|0x4a
comma
l_int|0x4b
comma
l_int|0x4c
comma
l_int|0x4d
comma
l_int|0x4e
comma
l_int|0x4f
comma
multiline_comment|/* 0x48-0x4f */
l_int|0x50
comma
l_int|0x51
comma
l_int|0x52
comma
l_int|0x53
comma
l_int|0x54
comma
l_int|0x55
comma
l_int|0x56
comma
l_int|0x57
comma
multiline_comment|/* 0x50-0x57 */
l_int|0x58
comma
l_int|0x59
comma
l_int|0x5a
comma
l_int|0x5b
comma
l_int|0x5c
comma
l_int|0x5d
comma
l_int|0x5e
comma
l_int|0x5f
comma
multiline_comment|/* 0x58-0x5f */
l_int|0x60
comma
l_int|0x61
comma
l_int|0x62
comma
l_int|0x63
comma
l_int|0x64
comma
l_int|0x65
comma
l_int|0x66
comma
l_int|0x67
comma
multiline_comment|/* 0x60-0x67 */
l_int|0x68
comma
l_int|0x69
comma
l_int|0x6a
comma
l_int|0x6b
comma
l_int|0x6c
comma
l_int|0x6d
comma
l_int|0x6e
comma
l_int|0x6f
comma
multiline_comment|/* 0x68-0x6f */
l_int|0x70
comma
l_int|0x71
comma
l_int|0x72
comma
l_int|0x73
comma
l_int|0x74
comma
l_int|0x75
comma
l_int|0x76
comma
l_int|0x77
comma
multiline_comment|/* 0x70-0x77 */
l_int|0x78
comma
l_int|0x79
comma
l_int|0x7a
comma
l_int|0x7b
comma
l_int|0x7c
comma
l_int|0x7d
comma
l_int|0x7e
comma
l_int|0x7f
comma
multiline_comment|/* 0x78-0x7f */
l_int|0x80
comma
l_int|0x81
comma
l_int|0x82
comma
l_int|0x83
comma
l_int|0x84
comma
l_int|0x85
comma
l_int|0x86
comma
l_int|0x87
comma
multiline_comment|/* 0x80-0x87 */
l_int|0x88
comma
l_int|0x89
comma
l_int|0x8a
comma
l_int|0x8b
comma
l_int|0x8c
comma
l_int|0x8d
comma
l_int|0x8e
comma
l_int|0x8f
comma
multiline_comment|/* 0x88-0x8f */
l_int|0x90
comma
l_int|0x91
comma
l_int|0x92
comma
l_int|0x93
comma
l_int|0x94
comma
l_int|0x95
comma
l_int|0x96
comma
l_int|0x97
comma
multiline_comment|/* 0x90-0x97 */
l_int|0x98
comma
l_int|0x99
comma
l_int|0x9a
comma
l_int|0x9b
comma
l_int|0x9c
comma
l_int|0x9d
comma
l_int|0x9e
comma
l_int|0x9f
comma
multiline_comment|/* 0x98-0x9f */
l_int|0xa0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xfd
comma
multiline_comment|/* 0xa0-0xa7 */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xad
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xa8-0xaf */
)brace
suffix:semicolon
DECL|variable|page04
r_static
r_int
r_char
id|page04
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0xa1
comma
l_int|0xa2
comma
l_int|0xa3
comma
l_int|0xa4
comma
l_int|0xa5
comma
l_int|0xa6
comma
l_int|0xa7
comma
multiline_comment|/* 0x00-0x07 */
l_int|0xa8
comma
l_int|0xa9
comma
l_int|0xaa
comma
l_int|0xab
comma
l_int|0xac
comma
l_int|0x00
comma
l_int|0xae
comma
l_int|0xaf
comma
multiline_comment|/* 0x08-0x0f */
l_int|0xb0
comma
l_int|0xb1
comma
l_int|0xb2
comma
l_int|0xb3
comma
l_int|0xb4
comma
l_int|0xb5
comma
l_int|0xb6
comma
l_int|0xb7
comma
multiline_comment|/* 0x10-0x17 */
l_int|0xb8
comma
l_int|0xb9
comma
l_int|0xba
comma
l_int|0xbb
comma
l_int|0xbc
comma
l_int|0xbd
comma
l_int|0xbe
comma
l_int|0xbf
comma
multiline_comment|/* 0x18-0x1f */
l_int|0xc0
comma
l_int|0xc1
comma
l_int|0xc2
comma
l_int|0xc3
comma
l_int|0xc4
comma
l_int|0xc5
comma
l_int|0xc6
comma
l_int|0xc7
comma
multiline_comment|/* 0x20-0x27 */
l_int|0xc8
comma
l_int|0xc9
comma
l_int|0xca
comma
l_int|0xcb
comma
l_int|0xcc
comma
l_int|0xcd
comma
l_int|0xce
comma
l_int|0xcf
comma
multiline_comment|/* 0x28-0x2f */
l_int|0xd0
comma
l_int|0xd1
comma
l_int|0xd2
comma
l_int|0xd3
comma
l_int|0xd4
comma
l_int|0xd5
comma
l_int|0xd6
comma
l_int|0xd7
comma
multiline_comment|/* 0x30-0x37 */
l_int|0xd8
comma
l_int|0xd9
comma
l_int|0xda
comma
l_int|0xdb
comma
l_int|0xdc
comma
l_int|0xdd
comma
l_int|0xde
comma
l_int|0xdf
comma
multiline_comment|/* 0x38-0x3f */
l_int|0xe0
comma
l_int|0xe1
comma
l_int|0xe2
comma
l_int|0xe3
comma
l_int|0xe4
comma
l_int|0xe5
comma
l_int|0xe6
comma
l_int|0xe7
comma
multiline_comment|/* 0x40-0x47 */
l_int|0xe8
comma
l_int|0xe9
comma
l_int|0xea
comma
l_int|0xeb
comma
l_int|0xec
comma
l_int|0xed
comma
l_int|0xee
comma
l_int|0xef
comma
multiline_comment|/* 0x48-0x4f */
l_int|0x00
comma
l_int|0xf1
comma
l_int|0xf2
comma
l_int|0xf3
comma
l_int|0xf4
comma
l_int|0xf5
comma
l_int|0xf6
comma
l_int|0xf7
comma
multiline_comment|/* 0x50-0x57 */
l_int|0xf8
comma
l_int|0xf9
comma
l_int|0xfa
comma
l_int|0xfb
comma
l_int|0xfc
comma
l_int|0x00
comma
l_int|0xfe
comma
l_int|0xff
comma
multiline_comment|/* 0x58-0x5f */
)brace
suffix:semicolon
DECL|variable|page21
r_static
r_int
r_char
id|page21
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x00-0x07 */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x08-0x0f */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xf0
comma
l_int|0x00
comma
multiline_comment|/* 0x10-0x17 */
)brace
suffix:semicolon
DECL|variable|page_uni2charset
r_static
r_int
r_char
op_star
id|page_uni2charset
(braket
l_int|256
)braket
op_assign
(brace
id|page00
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|page04
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|page21
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|charset2lower
r_static
r_int
r_char
id|charset2lower
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x03
comma
l_int|0x04
comma
l_int|0x05
comma
l_int|0x06
comma
l_int|0x07
comma
multiline_comment|/* 0x00-0x07 */
l_int|0x08
comma
l_int|0x09
comma
l_int|0x0a
comma
l_int|0x0b
comma
l_int|0x0c
comma
l_int|0x0d
comma
l_int|0x0e
comma
l_int|0x0f
comma
multiline_comment|/* 0x08-0x0f */
l_int|0x10
comma
l_int|0x11
comma
l_int|0x12
comma
l_int|0x13
comma
l_int|0x14
comma
l_int|0x15
comma
l_int|0x16
comma
l_int|0x17
comma
multiline_comment|/* 0x10-0x17 */
l_int|0x18
comma
l_int|0x19
comma
l_int|0x1a
comma
l_int|0x1b
comma
l_int|0x1c
comma
l_int|0x1d
comma
l_int|0x1e
comma
l_int|0x1f
comma
multiline_comment|/* 0x18-0x1f */
l_int|0x20
comma
l_int|0x21
comma
l_int|0x22
comma
l_int|0x23
comma
l_int|0x24
comma
l_int|0x25
comma
l_int|0x26
comma
l_int|0x27
comma
multiline_comment|/* 0x20-0x27 */
l_int|0x28
comma
l_int|0x29
comma
l_int|0x2a
comma
l_int|0x2b
comma
l_int|0x2c
comma
l_int|0x2d
comma
l_int|0x2e
comma
l_int|0x2f
comma
multiline_comment|/* 0x28-0x2f */
l_int|0x30
comma
l_int|0x31
comma
l_int|0x32
comma
l_int|0x33
comma
l_int|0x34
comma
l_int|0x35
comma
l_int|0x36
comma
l_int|0x37
comma
multiline_comment|/* 0x30-0x37 */
l_int|0x38
comma
l_int|0x39
comma
l_int|0x3a
comma
l_int|0x3b
comma
l_int|0x3c
comma
l_int|0x3d
comma
l_int|0x3e
comma
l_int|0x3f
comma
multiline_comment|/* 0x38-0x3f */
l_int|0x40
comma
l_int|0x61
comma
l_int|0x62
comma
l_int|0x63
comma
l_int|0x64
comma
l_int|0x65
comma
l_int|0x66
comma
l_int|0x67
comma
multiline_comment|/* 0x40-0x47 */
l_int|0x68
comma
l_int|0x69
comma
l_int|0x6a
comma
l_int|0x6b
comma
l_int|0x6c
comma
l_int|0x6d
comma
l_int|0x6e
comma
l_int|0x6f
comma
multiline_comment|/* 0x48-0x4f */
l_int|0x70
comma
l_int|0x71
comma
l_int|0x72
comma
l_int|0x73
comma
l_int|0x74
comma
l_int|0x75
comma
l_int|0x76
comma
l_int|0x77
comma
multiline_comment|/* 0x50-0x57 */
l_int|0x78
comma
l_int|0x79
comma
l_int|0x7a
comma
l_int|0x5b
comma
l_int|0x5c
comma
l_int|0x5d
comma
l_int|0x5e
comma
l_int|0x5f
comma
multiline_comment|/* 0x58-0x5f */
l_int|0x60
comma
l_int|0x61
comma
l_int|0x62
comma
l_int|0x63
comma
l_int|0x64
comma
l_int|0x65
comma
l_int|0x66
comma
l_int|0x67
comma
multiline_comment|/* 0x60-0x67 */
l_int|0x68
comma
l_int|0x69
comma
l_int|0x6a
comma
l_int|0x6b
comma
l_int|0x6c
comma
l_int|0x6d
comma
l_int|0x6e
comma
l_int|0x6f
comma
multiline_comment|/* 0x68-0x6f */
l_int|0x70
comma
l_int|0x71
comma
l_int|0x72
comma
l_int|0x73
comma
l_int|0x74
comma
l_int|0x75
comma
l_int|0x76
comma
l_int|0x77
comma
multiline_comment|/* 0x70-0x77 */
l_int|0x78
comma
l_int|0x79
comma
l_int|0x7a
comma
l_int|0x7b
comma
l_int|0x7c
comma
l_int|0x7d
comma
l_int|0x7e
comma
l_int|0x7f
comma
multiline_comment|/* 0x78-0x7f */
l_int|0x80
comma
l_int|0x81
comma
l_int|0x82
comma
l_int|0x83
comma
l_int|0x84
comma
l_int|0x85
comma
l_int|0x86
comma
l_int|0x87
comma
multiline_comment|/* 0x80-0x87 */
l_int|0x88
comma
l_int|0x89
comma
l_int|0x8a
comma
l_int|0x8b
comma
l_int|0x8c
comma
l_int|0x8d
comma
l_int|0x8e
comma
l_int|0x8f
comma
multiline_comment|/* 0x88-0x8f */
l_int|0x90
comma
l_int|0x91
comma
l_int|0x92
comma
l_int|0x93
comma
l_int|0x94
comma
l_int|0x95
comma
l_int|0x96
comma
l_int|0x97
comma
multiline_comment|/* 0x90-0x97 */
l_int|0x98
comma
l_int|0x99
comma
l_int|0x9a
comma
l_int|0x9b
comma
l_int|0x9c
comma
l_int|0x9d
comma
l_int|0x9e
comma
l_int|0x9f
comma
multiline_comment|/* 0x98-0x9f */
l_int|0xa0
comma
l_int|0xf1
comma
l_int|0xf2
comma
l_int|0xf3
comma
l_int|0xf4
comma
l_int|0xf5
comma
l_int|0xf6
comma
l_int|0xf7
comma
multiline_comment|/* 0xa0-0xa7 */
l_int|0xf8
comma
l_int|0xf9
comma
l_int|0xfa
comma
l_int|0xfb
comma
l_int|0xfc
comma
l_int|0xad
comma
l_int|0xfe
comma
l_int|0xff
comma
multiline_comment|/* 0xa8-0xaf */
l_int|0xd0
comma
l_int|0xd1
comma
l_int|0xd2
comma
l_int|0xd3
comma
l_int|0xd4
comma
l_int|0xd5
comma
l_int|0xd6
comma
l_int|0xd7
comma
multiline_comment|/* 0xb0-0xb7 */
l_int|0xd8
comma
l_int|0xd9
comma
l_int|0xda
comma
l_int|0xdb
comma
l_int|0xdc
comma
l_int|0xdd
comma
l_int|0xde
comma
l_int|0xdf
comma
multiline_comment|/* 0xb8-0xbf */
l_int|0xe0
comma
l_int|0xe1
comma
l_int|0xe2
comma
l_int|0xe3
comma
l_int|0xe4
comma
l_int|0xe5
comma
l_int|0xe6
comma
l_int|0xe7
comma
multiline_comment|/* 0xc0-0xc7 */
l_int|0xe8
comma
l_int|0xe9
comma
l_int|0xea
comma
l_int|0xeb
comma
l_int|0xec
comma
l_int|0xed
comma
l_int|0xee
comma
l_int|0xef
comma
multiline_comment|/* 0xc8-0xcf */
l_int|0xd0
comma
l_int|0xd1
comma
l_int|0xd2
comma
l_int|0xd3
comma
l_int|0xd4
comma
l_int|0xd5
comma
l_int|0xd6
comma
l_int|0xd7
comma
multiline_comment|/* 0xd0-0xd7 */
l_int|0xd8
comma
l_int|0xd9
comma
l_int|0xda
comma
l_int|0xdb
comma
l_int|0xdc
comma
l_int|0xdd
comma
l_int|0xde
comma
l_int|0xdf
comma
multiline_comment|/* 0xd8-0xdf */
l_int|0xe0
comma
l_int|0xe1
comma
l_int|0xe2
comma
l_int|0xe3
comma
l_int|0xe4
comma
l_int|0xe5
comma
l_int|0xe6
comma
l_int|0xe7
comma
multiline_comment|/* 0xe0-0xe7 */
l_int|0xe8
comma
l_int|0xe9
comma
l_int|0xea
comma
l_int|0xeb
comma
l_int|0xec
comma
l_int|0xed
comma
l_int|0xee
comma
l_int|0xef
comma
multiline_comment|/* 0xe8-0xef */
l_int|0xf0
comma
l_int|0xf1
comma
l_int|0xf2
comma
l_int|0xf3
comma
l_int|0xf4
comma
l_int|0xf5
comma
l_int|0xf6
comma
l_int|0xf7
comma
multiline_comment|/* 0xf0-0xf7 */
l_int|0xf8
comma
l_int|0xf9
comma
l_int|0xfa
comma
l_int|0xfb
comma
l_int|0xfc
comma
l_int|0xfd
comma
l_int|0xfe
comma
l_int|0xff
comma
multiline_comment|/* 0xf8-0xff */
)brace
suffix:semicolon
DECL|variable|charset2upper
r_static
r_int
r_char
id|charset2upper
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x03
comma
l_int|0x04
comma
l_int|0x05
comma
l_int|0x06
comma
l_int|0x07
comma
multiline_comment|/* 0x00-0x07 */
l_int|0x08
comma
l_int|0x09
comma
l_int|0x0a
comma
l_int|0x0b
comma
l_int|0x0c
comma
l_int|0x0d
comma
l_int|0x0e
comma
l_int|0x0f
comma
multiline_comment|/* 0x08-0x0f */
l_int|0x10
comma
l_int|0x11
comma
l_int|0x12
comma
l_int|0x13
comma
l_int|0x14
comma
l_int|0x15
comma
l_int|0x16
comma
l_int|0x17
comma
multiline_comment|/* 0x10-0x17 */
l_int|0x18
comma
l_int|0x19
comma
l_int|0x1a
comma
l_int|0x1b
comma
l_int|0x1c
comma
l_int|0x1d
comma
l_int|0x1e
comma
l_int|0x1f
comma
multiline_comment|/* 0x18-0x1f */
l_int|0x20
comma
l_int|0x21
comma
l_int|0x22
comma
l_int|0x23
comma
l_int|0x24
comma
l_int|0x25
comma
l_int|0x26
comma
l_int|0x27
comma
multiline_comment|/* 0x20-0x27 */
l_int|0x28
comma
l_int|0x29
comma
l_int|0x2a
comma
l_int|0x2b
comma
l_int|0x2c
comma
l_int|0x2d
comma
l_int|0x2e
comma
l_int|0x2f
comma
multiline_comment|/* 0x28-0x2f */
l_int|0x30
comma
l_int|0x31
comma
l_int|0x32
comma
l_int|0x33
comma
l_int|0x34
comma
l_int|0x35
comma
l_int|0x36
comma
l_int|0x37
comma
multiline_comment|/* 0x30-0x37 */
l_int|0x38
comma
l_int|0x39
comma
l_int|0x3a
comma
l_int|0x3b
comma
l_int|0x3c
comma
l_int|0x3d
comma
l_int|0x3e
comma
l_int|0x3f
comma
multiline_comment|/* 0x38-0x3f */
l_int|0x40
comma
l_int|0x41
comma
l_int|0x42
comma
l_int|0x43
comma
l_int|0x44
comma
l_int|0x45
comma
l_int|0x46
comma
l_int|0x47
comma
multiline_comment|/* 0x40-0x47 */
l_int|0x48
comma
l_int|0x49
comma
l_int|0x4a
comma
l_int|0x4b
comma
l_int|0x4c
comma
l_int|0x4d
comma
l_int|0x4e
comma
l_int|0x4f
comma
multiline_comment|/* 0x48-0x4f */
l_int|0x50
comma
l_int|0x51
comma
l_int|0x52
comma
l_int|0x53
comma
l_int|0x54
comma
l_int|0x55
comma
l_int|0x56
comma
l_int|0x57
comma
multiline_comment|/* 0x50-0x57 */
l_int|0x58
comma
l_int|0x59
comma
l_int|0x5a
comma
l_int|0x5b
comma
l_int|0x5c
comma
l_int|0x5d
comma
l_int|0x5e
comma
l_int|0x5f
comma
multiline_comment|/* 0x58-0x5f */
l_int|0x60
comma
l_int|0x41
comma
l_int|0x42
comma
l_int|0x43
comma
l_int|0x44
comma
l_int|0x45
comma
l_int|0x46
comma
l_int|0x47
comma
multiline_comment|/* 0x60-0x67 */
l_int|0x48
comma
l_int|0x49
comma
l_int|0x4a
comma
l_int|0x4b
comma
l_int|0x4c
comma
l_int|0x4d
comma
l_int|0x4e
comma
l_int|0x4f
comma
multiline_comment|/* 0x68-0x6f */
l_int|0x50
comma
l_int|0x51
comma
l_int|0x52
comma
l_int|0x53
comma
l_int|0x54
comma
l_int|0x55
comma
l_int|0x56
comma
l_int|0x57
comma
multiline_comment|/* 0x70-0x77 */
l_int|0x58
comma
l_int|0x59
comma
l_int|0x5a
comma
l_int|0x7b
comma
l_int|0x7c
comma
l_int|0x7d
comma
l_int|0x7e
comma
l_int|0x7f
comma
multiline_comment|/* 0x78-0x7f */
l_int|0x80
comma
l_int|0x81
comma
l_int|0x82
comma
l_int|0x83
comma
l_int|0x84
comma
l_int|0x85
comma
l_int|0x86
comma
l_int|0x87
comma
multiline_comment|/* 0x80-0x87 */
l_int|0x88
comma
l_int|0x89
comma
l_int|0x8a
comma
l_int|0x8b
comma
l_int|0x8c
comma
l_int|0x8d
comma
l_int|0x8e
comma
l_int|0x8f
comma
multiline_comment|/* 0x88-0x8f */
l_int|0x90
comma
l_int|0x91
comma
l_int|0x92
comma
l_int|0x93
comma
l_int|0x94
comma
l_int|0x95
comma
l_int|0x96
comma
l_int|0x97
comma
multiline_comment|/* 0x90-0x97 */
l_int|0x98
comma
l_int|0x99
comma
l_int|0x9a
comma
l_int|0x9b
comma
l_int|0x9c
comma
l_int|0x9d
comma
l_int|0x9e
comma
l_int|0x9f
comma
multiline_comment|/* 0x98-0x9f */
l_int|0xa0
comma
l_int|0xa1
comma
l_int|0xa2
comma
l_int|0xa3
comma
l_int|0xa4
comma
l_int|0xa5
comma
l_int|0xa6
comma
l_int|0xa7
comma
multiline_comment|/* 0xa0-0xa7 */
l_int|0xa8
comma
l_int|0xa9
comma
l_int|0xaa
comma
l_int|0xab
comma
l_int|0xac
comma
l_int|0xad
comma
l_int|0xae
comma
l_int|0xaf
comma
multiline_comment|/* 0xa8-0xaf */
l_int|0xb0
comma
l_int|0xb1
comma
l_int|0xb2
comma
l_int|0xb3
comma
l_int|0xb4
comma
l_int|0xb5
comma
l_int|0xb6
comma
l_int|0xb7
comma
multiline_comment|/* 0xb0-0xb7 */
l_int|0xb8
comma
l_int|0xb9
comma
l_int|0xba
comma
l_int|0xbb
comma
l_int|0xbc
comma
l_int|0xbd
comma
l_int|0xbe
comma
l_int|0xbf
comma
multiline_comment|/* 0xb8-0xbf */
l_int|0xc0
comma
l_int|0xc1
comma
l_int|0xc2
comma
l_int|0xc3
comma
l_int|0xc4
comma
l_int|0xc5
comma
l_int|0xc6
comma
l_int|0xc7
comma
multiline_comment|/* 0xc0-0xc7 */
l_int|0xc8
comma
l_int|0xc9
comma
l_int|0xca
comma
l_int|0xcb
comma
l_int|0xcc
comma
l_int|0xcd
comma
l_int|0xce
comma
l_int|0xcf
comma
multiline_comment|/* 0xc8-0xcf */
l_int|0xb0
comma
l_int|0xb1
comma
l_int|0xb2
comma
l_int|0xb3
comma
l_int|0xb4
comma
l_int|0xb5
comma
l_int|0xb6
comma
l_int|0xb7
comma
multiline_comment|/* 0xd0-0xd7 */
l_int|0xb8
comma
l_int|0xb9
comma
l_int|0xba
comma
l_int|0xbb
comma
l_int|0xbc
comma
l_int|0xbd
comma
l_int|0xbe
comma
l_int|0xbf
comma
multiline_comment|/* 0xd8-0xdf */
l_int|0xc0
comma
l_int|0xc1
comma
l_int|0xc2
comma
l_int|0xc3
comma
l_int|0xc4
comma
l_int|0xc5
comma
l_int|0xc6
comma
l_int|0xc7
comma
multiline_comment|/* 0xe0-0xe7 */
l_int|0xc8
comma
l_int|0xc9
comma
l_int|0xca
comma
l_int|0xcb
comma
l_int|0xcc
comma
l_int|0xcd
comma
l_int|0xce
comma
l_int|0xcf
comma
multiline_comment|/* 0xe8-0xef */
l_int|0xf0
comma
l_int|0xa1
comma
l_int|0xa2
comma
l_int|0xa3
comma
l_int|0xa4
comma
l_int|0xa5
comma
l_int|0xa6
comma
l_int|0xa7
comma
multiline_comment|/* 0xf0-0xf7 */
l_int|0xa8
comma
l_int|0xa9
comma
l_int|0xaa
comma
l_int|0xab
comma
l_int|0xac
comma
l_int|0xfd
comma
l_int|0xae
comma
l_int|0xaf
comma
multiline_comment|/* 0xf8-0xff */
)brace
suffix:semicolon
DECL|function|uni2char
r_static
r_int
id|uni2char
c_func
(paren
m_wchar_t
id|uni
comma
r_int
r_char
op_star
id|out
comma
r_int
id|boundlen
)paren
(brace
r_int
r_char
op_star
id|uni2charset
suffix:semicolon
r_int
r_char
id|cl
op_assign
id|uni
op_amp
l_int|0x00ff
suffix:semicolon
r_int
r_char
id|ch
op_assign
(paren
id|uni
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|boundlen
op_le
l_int|0
)paren
r_return
op_minus
id|ENAMETOOLONG
suffix:semicolon
id|uni2charset
op_assign
id|page_uni2charset
(braket
id|ch
)braket
suffix:semicolon
r_if
c_cond
(paren
id|uni2charset
op_logical_and
id|uni2charset
(braket
id|cl
)braket
)paren
id|out
(braket
l_int|0
)braket
op_assign
id|uni2charset
(braket
id|cl
)braket
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|char2uni
r_static
r_int
id|char2uni
c_func
(paren
r_const
r_int
r_char
op_star
id|rawstring
comma
r_int
id|boundlen
comma
m_wchar_t
op_star
id|uni
)paren
(brace
op_star
id|uni
op_assign
id|charset2uni
(braket
op_star
id|rawstring
)braket
suffix:semicolon
r_if
c_cond
(paren
op_star
id|uni
op_eq
l_int|0x0000
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|table
r_static
r_struct
id|nls_table
id|table
op_assign
(brace
dot
id|charset
op_assign
l_string|&quot;iso8859-5&quot;
comma
dot
id|uni2char
op_assign
id|uni2char
comma
dot
id|char2uni
op_assign
id|char2uni
comma
dot
id|charset2lower
op_assign
id|charset2lower
comma
dot
id|charset2upper
op_assign
id|charset2upper
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|init_nls_iso8859_5
r_static
r_int
id|__init
id|init_nls_iso8859_5
c_func
(paren
r_void
)paren
(brace
r_return
id|register_nls
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
)brace
DECL|function|exit_nls_iso8859_5
r_static
r_void
id|__exit
id|exit_nls_iso8859_5
c_func
(paren
r_void
)paren
(brace
id|unregister_nls
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_nls_iso8859_5
)paren
id|module_exit
c_func
(paren
id|exit_nls_iso8859_5
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual BSD/GPL&quot;
)paren
suffix:semicolon
eof
