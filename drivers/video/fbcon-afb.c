multiline_comment|/*&n; *  linux/drivers/video/afb.c -- Low level frame buffer operations for&n; *&t;&t;&t;&t; bitplanes &#xfffd; la Amiga&n; *&n; *&t;Created 5 Apr 1997 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-afb.h&gt;
multiline_comment|/*&n;     *  Bitplanes &#xfffd; la Amiga&n;     */
DECL|variable|expand_table
r_static
id|u8
id|expand_table
(braket
l_int|1024
)braket
op_assign
(brace
multiline_comment|/*  bg = fg = 0 */
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
multiline_comment|/* bg = 0, fg = 1 */
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
multiline_comment|/* bg = 1, fg = 0 */
l_int|0xff
comma
l_int|0xfe
comma
l_int|0xfd
comma
l_int|0xfc
comma
l_int|0xfb
comma
l_int|0xfa
comma
l_int|0xf9
comma
l_int|0xf8
comma
l_int|0xf7
comma
l_int|0xf6
comma
l_int|0xf5
comma
l_int|0xf4
comma
l_int|0xf3
comma
l_int|0xf2
comma
l_int|0xf1
comma
l_int|0xf0
comma
l_int|0xef
comma
l_int|0xee
comma
l_int|0xed
comma
l_int|0xec
comma
l_int|0xeb
comma
l_int|0xea
comma
l_int|0xe9
comma
l_int|0xe8
comma
l_int|0xe7
comma
l_int|0xe6
comma
l_int|0xe5
comma
l_int|0xe4
comma
l_int|0xe3
comma
l_int|0xe2
comma
l_int|0xe1
comma
l_int|0xe0
comma
l_int|0xdf
comma
l_int|0xde
comma
l_int|0xdd
comma
l_int|0xdc
comma
l_int|0xdb
comma
l_int|0xda
comma
l_int|0xd9
comma
l_int|0xd8
comma
l_int|0xd7
comma
l_int|0xd6
comma
l_int|0xd5
comma
l_int|0xd4
comma
l_int|0xd3
comma
l_int|0xd2
comma
l_int|0xd1
comma
l_int|0xd0
comma
l_int|0xcf
comma
l_int|0xce
comma
l_int|0xcd
comma
l_int|0xcc
comma
l_int|0xcb
comma
l_int|0xca
comma
l_int|0xc9
comma
l_int|0xc8
comma
l_int|0xc7
comma
l_int|0xc6
comma
l_int|0xc5
comma
l_int|0xc4
comma
l_int|0xc3
comma
l_int|0xc2
comma
l_int|0xc1
comma
l_int|0xc0
comma
l_int|0xbf
comma
l_int|0xbe
comma
l_int|0xbd
comma
l_int|0xbc
comma
l_int|0xbb
comma
l_int|0xba
comma
l_int|0xb9
comma
l_int|0xb8
comma
l_int|0xb7
comma
l_int|0xb6
comma
l_int|0xb5
comma
l_int|0xb4
comma
l_int|0xb3
comma
l_int|0xb2
comma
l_int|0xb1
comma
l_int|0xb0
comma
l_int|0xaf
comma
l_int|0xae
comma
l_int|0xad
comma
l_int|0xac
comma
l_int|0xab
comma
l_int|0xaa
comma
l_int|0xa9
comma
l_int|0xa8
comma
l_int|0xa7
comma
l_int|0xa6
comma
l_int|0xa5
comma
l_int|0xa4
comma
l_int|0xa3
comma
l_int|0xa2
comma
l_int|0xa1
comma
l_int|0xa0
comma
l_int|0x9f
comma
l_int|0x9e
comma
l_int|0x9d
comma
l_int|0x9c
comma
l_int|0x9b
comma
l_int|0x9a
comma
l_int|0x99
comma
l_int|0x98
comma
l_int|0x97
comma
l_int|0x96
comma
l_int|0x95
comma
l_int|0x94
comma
l_int|0x93
comma
l_int|0x92
comma
l_int|0x91
comma
l_int|0x90
comma
l_int|0x8f
comma
l_int|0x8e
comma
l_int|0x8d
comma
l_int|0x8c
comma
l_int|0x8b
comma
l_int|0x8a
comma
l_int|0x89
comma
l_int|0x88
comma
l_int|0x87
comma
l_int|0x86
comma
l_int|0x85
comma
l_int|0x84
comma
l_int|0x83
comma
l_int|0x82
comma
l_int|0x81
comma
l_int|0x80
comma
l_int|0x7f
comma
l_int|0x7e
comma
l_int|0x7d
comma
l_int|0x7c
comma
l_int|0x7b
comma
l_int|0x7a
comma
l_int|0x79
comma
l_int|0x78
comma
l_int|0x77
comma
l_int|0x76
comma
l_int|0x75
comma
l_int|0x74
comma
l_int|0x73
comma
l_int|0x72
comma
l_int|0x71
comma
l_int|0x70
comma
l_int|0x6f
comma
l_int|0x6e
comma
l_int|0x6d
comma
l_int|0x6c
comma
l_int|0x6b
comma
l_int|0x6a
comma
l_int|0x69
comma
l_int|0x68
comma
l_int|0x67
comma
l_int|0x66
comma
l_int|0x65
comma
l_int|0x64
comma
l_int|0x63
comma
l_int|0x62
comma
l_int|0x61
comma
l_int|0x60
comma
l_int|0x5f
comma
l_int|0x5e
comma
l_int|0x5d
comma
l_int|0x5c
comma
l_int|0x5b
comma
l_int|0x5a
comma
l_int|0x59
comma
l_int|0x58
comma
l_int|0x57
comma
l_int|0x56
comma
l_int|0x55
comma
l_int|0x54
comma
l_int|0x53
comma
l_int|0x52
comma
l_int|0x51
comma
l_int|0x50
comma
l_int|0x4f
comma
l_int|0x4e
comma
l_int|0x4d
comma
l_int|0x4c
comma
l_int|0x4b
comma
l_int|0x4a
comma
l_int|0x49
comma
l_int|0x48
comma
l_int|0x47
comma
l_int|0x46
comma
l_int|0x45
comma
l_int|0x44
comma
l_int|0x43
comma
l_int|0x42
comma
l_int|0x41
comma
l_int|0x40
comma
l_int|0x3f
comma
l_int|0x3e
comma
l_int|0x3d
comma
l_int|0x3c
comma
l_int|0x3b
comma
l_int|0x3a
comma
l_int|0x39
comma
l_int|0x38
comma
l_int|0x37
comma
l_int|0x36
comma
l_int|0x35
comma
l_int|0x34
comma
l_int|0x33
comma
l_int|0x32
comma
l_int|0x31
comma
l_int|0x30
comma
l_int|0x2f
comma
l_int|0x2e
comma
l_int|0x2d
comma
l_int|0x2c
comma
l_int|0x2b
comma
l_int|0x2a
comma
l_int|0x29
comma
l_int|0x28
comma
l_int|0x27
comma
l_int|0x26
comma
l_int|0x25
comma
l_int|0x24
comma
l_int|0x23
comma
l_int|0x22
comma
l_int|0x21
comma
l_int|0x20
comma
l_int|0x1f
comma
l_int|0x1e
comma
l_int|0x1d
comma
l_int|0x1c
comma
l_int|0x1b
comma
l_int|0x1a
comma
l_int|0x19
comma
l_int|0x18
comma
l_int|0x17
comma
l_int|0x16
comma
l_int|0x15
comma
l_int|0x14
comma
l_int|0x13
comma
l_int|0x12
comma
l_int|0x11
comma
l_int|0x10
comma
l_int|0x0f
comma
l_int|0x0e
comma
l_int|0x0d
comma
l_int|0x0c
comma
l_int|0x0b
comma
l_int|0x0a
comma
l_int|0x09
comma
l_int|0x08
comma
l_int|0x07
comma
l_int|0x06
comma
l_int|0x05
comma
l_int|0x04
comma
l_int|0x03
comma
l_int|0x02
comma
l_int|0x01
comma
l_int|0x00
comma
multiline_comment|/* bg = fg = 1 */
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
DECL|function|fbcon_afb_setup
r_void
id|fbcon_afb_setup
c_func
(paren
r_struct
id|display
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;fb_info-&gt;fix.line_length
)paren
id|p-&gt;next_line
op_assign
id|p-&gt;fb_info-&gt;fix.line_length
suffix:semicolon
r_else
id|p-&gt;next_line
op_assign
id|p-&gt;var.xres_virtual
op_rshift
l_int|3
suffix:semicolon
id|p-&gt;next_plane
op_assign
id|p-&gt;var.yres_virtual
op_star
id|p-&gt;next_line
suffix:semicolon
)brace
DECL|function|fbcon_afb_bmove
r_void
id|fbcon_afb_bmove
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
id|u8
op_star
id|src
comma
op_star
id|dest
comma
op_star
id|src0
comma
op_star
id|dest0
suffix:semicolon
id|u_short
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|sx
op_eq
l_int|0
op_logical_and
id|dx
op_eq
l_int|0
op_logical_and
id|width
op_eq
id|p-&gt;next_line
)paren
(brace
id|src
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|width
suffix:semicolon
id|dest
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|dy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|width
suffix:semicolon
id|i
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_do
(brace
id|fb_memmove
c_func
(paren
id|dest
comma
id|src
comma
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|width
)paren
suffix:semicolon
id|src
op_add_assign
id|p-&gt;next_plane
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_plane
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dy
op_le
id|sy
)paren
(brace
id|src0
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
id|dest0
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|dy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|dx
suffix:semicolon
id|i
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_do
(brace
id|src
op_assign
id|src0
suffix:semicolon
id|dest
op_assign
id|dest0
suffix:semicolon
id|j
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_do
(brace
id|fb_memmove
c_func
(paren
id|dest
comma
id|src
comma
id|width
)paren
suffix:semicolon
id|src
op_add_assign
id|p-&gt;next_line
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|j
)paren
suffix:semicolon
id|src0
op_add_assign
id|p-&gt;next_plane
suffix:semicolon
id|dest0
op_add_assign
id|p-&gt;next_plane
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
)brace
r_else
(brace
id|src0
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
(paren
id|sy
op_plus
id|height
)paren
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
id|dest0
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
(paren
id|dy
op_plus
id|height
)paren
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|dx
suffix:semicolon
id|i
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_do
(brace
id|src
op_assign
id|src0
suffix:semicolon
id|dest
op_assign
id|dest0
suffix:semicolon
id|j
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_do
(brace
id|src
op_sub_assign
id|p-&gt;next_line
suffix:semicolon
id|dest
op_sub_assign
id|p-&gt;next_line
suffix:semicolon
id|fb_memmove
c_func
(paren
id|dest
comma
id|src
comma
id|width
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|j
)paren
suffix:semicolon
id|src0
op_add_assign
id|p-&gt;next_plane
suffix:semicolon
id|dest0
op_add_assign
id|p-&gt;next_plane
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_afb_clear
r_void
id|fbcon_afb_clear
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
id|u8
op_star
id|dest
comma
op_star
id|dest0
suffix:semicolon
id|u_short
id|i
comma
id|j
suffix:semicolon
r_int
id|bg
suffix:semicolon
id|dest0
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
id|bg
op_assign
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|i
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_do
(brace
id|dest
op_assign
id|dest0
suffix:semicolon
id|j
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|bg
op_amp
l_int|1
)paren
id|fb_memset255
c_func
(paren
id|dest
comma
id|width
)paren
suffix:semicolon
r_else
id|fb_memclear
c_func
(paren
id|dest
comma
id|width
)paren
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|j
)paren
suffix:semicolon
id|bg
op_rshift_assign
l_int|1
suffix:semicolon
id|dest0
op_add_assign
id|p-&gt;next_plane
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
)brace
DECL|function|fbcon_afb_putc
r_void
id|fbcon_afb_putc
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|c
comma
r_int
id|yy
comma
r_int
id|xx
)paren
(brace
id|u8
op_star
id|dest
comma
op_star
id|dest0
comma
op_star
id|cdat
comma
op_star
id|cdat0
comma
op_star
id|expand
suffix:semicolon
id|u_short
id|i
comma
id|j
suffix:semicolon
r_int
id|fg
comma
id|bg
suffix:semicolon
id|dest0
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|xx
suffix:semicolon
id|cdat0
op_assign
id|p-&gt;fontdata
op_plus
(paren
id|c
op_amp
id|p-&gt;charmask
)paren
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|fg
op_assign
id|attr_fgcol
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
id|bg
op_assign
id|attr_bgcol
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
id|i
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_do
(brace
id|dest
op_assign
id|dest0
suffix:semicolon
id|cdat
op_assign
id|cdat0
suffix:semicolon
id|expand
op_assign
id|expand_table
suffix:semicolon
r_if
c_cond
(paren
id|bg
op_amp
l_int|1
)paren
id|expand
op_add_assign
l_int|512
suffix:semicolon
r_if
c_cond
(paren
id|fg
op_amp
l_int|1
)paren
id|expand
op_add_assign
l_int|256
suffix:semicolon
id|j
op_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_do
(brace
op_star
id|dest
op_assign
id|expand
(braket
op_star
id|cdat
op_increment
)braket
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|j
)paren
suffix:semicolon
id|bg
op_rshift_assign
l_int|1
suffix:semicolon
id|fg
op_rshift_assign
l_int|1
suffix:semicolon
id|dest0
op_add_assign
id|p-&gt;next_plane
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  I&squot;ve split the console character loop in two parts&n;     *  (cfr. fbcon_putcs_ilbm())&n;     */
DECL|function|fbcon_afb_putcs
r_void
id|fbcon_afb_putcs
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_const
r_int
r_int
op_star
id|s
comma
r_int
id|count
comma
r_int
id|yy
comma
r_int
id|xx
)paren
(brace
id|u8
op_star
id|dest
comma
op_star
id|dest0
comma
op_star
id|dest1
comma
op_star
id|expand
suffix:semicolon
id|u8
op_star
id|cdat1
comma
op_star
id|cdat2
comma
op_star
id|cdat3
comma
op_star
id|cdat4
comma
op_star
id|cdat10
comma
op_star
id|cdat20
comma
op_star
id|cdat30
comma
op_star
id|cdat40
suffix:semicolon
id|u_short
id|i
comma
id|j
suffix:semicolon
id|u16
id|c1
comma
id|c2
comma
id|c3
comma
id|c4
suffix:semicolon
r_int
id|fg0
comma
id|bg0
comma
id|fg
comma
id|bg
suffix:semicolon
id|dest0
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|xx
suffix:semicolon
id|c1
op_assign
id|scr_readw
c_func
(paren
id|s
)paren
suffix:semicolon
id|fg0
op_assign
id|attr_fgcol
c_func
(paren
id|p
comma
id|c1
)paren
suffix:semicolon
id|bg0
op_assign
id|attr_bgcol
c_func
(paren
id|p
comma
id|c1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
r_if
c_cond
(paren
id|xx
op_amp
l_int|3
op_logical_or
id|count
OL
l_int|3
)paren
(brace
multiline_comment|/* Slow version */
id|c1
op_assign
id|scr_readw
c_func
(paren
id|s
op_increment
)paren
op_amp
id|p-&gt;charmask
suffix:semicolon
id|dest1
op_assign
id|dest0
op_increment
suffix:semicolon
id|xx
op_increment
suffix:semicolon
id|cdat10
op_assign
id|p-&gt;fontdata
op_plus
id|c1
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|fg
op_assign
id|fg0
suffix:semicolon
id|bg
op_assign
id|bg0
suffix:semicolon
id|i
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_do
(brace
id|dest
op_assign
id|dest1
suffix:semicolon
id|cdat1
op_assign
id|cdat10
suffix:semicolon
id|expand
op_assign
id|expand_table
suffix:semicolon
r_if
c_cond
(paren
id|bg
op_amp
l_int|1
)paren
id|expand
op_add_assign
l_int|512
suffix:semicolon
r_if
c_cond
(paren
id|fg
op_amp
l_int|1
)paren
id|expand
op_add_assign
l_int|256
suffix:semicolon
id|j
op_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_do
(brace
op_star
id|dest
op_assign
id|expand
(braket
op_star
id|cdat1
op_increment
)braket
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|j
)paren
suffix:semicolon
id|bg
op_rshift_assign
l_int|1
suffix:semicolon
id|fg
op_rshift_assign
l_int|1
suffix:semicolon
id|dest1
op_add_assign
id|p-&gt;next_plane
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Fast version */
id|c1
op_assign
id|scr_readw
c_func
(paren
op_amp
id|s
(braket
l_int|0
)braket
)paren
op_amp
id|p-&gt;charmask
suffix:semicolon
id|c2
op_assign
id|scr_readw
c_func
(paren
op_amp
id|s
(braket
l_int|1
)braket
)paren
op_amp
id|p-&gt;charmask
suffix:semicolon
id|c3
op_assign
id|scr_readw
c_func
(paren
op_amp
id|s
(braket
l_int|2
)braket
)paren
op_amp
id|p-&gt;charmask
suffix:semicolon
id|c4
op_assign
id|scr_readw
c_func
(paren
op_amp
id|s
(braket
l_int|3
)braket
)paren
op_amp
id|p-&gt;charmask
suffix:semicolon
id|dest1
op_assign
id|dest0
suffix:semicolon
id|cdat10
op_assign
id|p-&gt;fontdata
op_plus
id|c1
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|cdat20
op_assign
id|p-&gt;fontdata
op_plus
id|c2
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|cdat30
op_assign
id|p-&gt;fontdata
op_plus
id|c3
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|cdat40
op_assign
id|p-&gt;fontdata
op_plus
id|c4
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|fg
op_assign
id|fg0
suffix:semicolon
id|bg
op_assign
id|bg0
suffix:semicolon
id|i
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_do
(brace
id|dest
op_assign
id|dest1
suffix:semicolon
id|cdat1
op_assign
id|cdat10
suffix:semicolon
id|cdat2
op_assign
id|cdat20
suffix:semicolon
id|cdat3
op_assign
id|cdat30
suffix:semicolon
id|cdat4
op_assign
id|cdat40
suffix:semicolon
id|expand
op_assign
id|expand_table
suffix:semicolon
r_if
c_cond
(paren
id|bg
op_amp
l_int|1
)paren
id|expand
op_add_assign
l_int|512
suffix:semicolon
r_if
c_cond
(paren
id|fg
op_amp
l_int|1
)paren
id|expand
op_add_assign
l_int|256
suffix:semicolon
id|j
op_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_do
(brace
macro_line|#if defined(__BIG_ENDIAN)
op_star
(paren
id|u32
op_star
)paren
id|dest
op_assign
id|expand
(braket
op_star
id|cdat1
op_increment
)braket
op_lshift
l_int|24
op_or
id|expand
(braket
op_star
id|cdat2
op_increment
)braket
op_lshift
l_int|16
op_or
id|expand
(braket
op_star
id|cdat3
op_increment
)braket
op_lshift
l_int|8
op_or
id|expand
(braket
op_star
id|cdat4
op_increment
)braket
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN)
op_star
(paren
id|u32
op_star
)paren
id|dest
op_assign
id|expand
(braket
op_star
id|cdat1
op_increment
)braket
op_or
id|expand
(braket
op_star
id|cdat2
op_increment
)braket
op_lshift
l_int|8
op_or
id|expand
(braket
op_star
id|cdat3
op_increment
)braket
op_lshift
l_int|16
op_or
id|expand
(braket
op_star
id|cdat4
op_increment
)braket
op_lshift
l_int|24
suffix:semicolon
macro_line|#else
macro_line|#error FIXME: No endianness??
macro_line|#endif
id|dest
op_add_assign
id|p-&gt;next_line
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|j
)paren
suffix:semicolon
id|bg
op_rshift_assign
l_int|1
suffix:semicolon
id|fg
op_rshift_assign
l_int|1
suffix:semicolon
id|dest1
op_add_assign
id|p-&gt;next_plane
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
id|s
op_add_assign
l_int|4
suffix:semicolon
id|dest0
op_add_assign
l_int|4
suffix:semicolon
id|xx
op_add_assign
l_int|4
suffix:semicolon
id|count
op_sub_assign
l_int|3
suffix:semicolon
)brace
)brace
DECL|function|fbcon_afb_revc
r_void
id|fbcon_afb_revc
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|xx
comma
r_int
id|yy
)paren
(brace
id|u8
op_star
id|dest
comma
op_star
id|dest0
suffix:semicolon
id|u_short
id|i
comma
id|j
suffix:semicolon
r_int
id|mask
suffix:semicolon
id|dest0
op_assign
id|p-&gt;fb_info-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|p-&gt;next_line
op_plus
id|xx
suffix:semicolon
id|mask
op_assign
id|p-&gt;fgcol
op_xor
id|p-&gt;bgcol
suffix:semicolon
multiline_comment|/*&n;     *  This should really obey the individual character&squot;s&n;     *  background and foreground colors instead of simply&n;     *  inverting.&n;     */
id|i
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
(brace
id|dest
op_assign
id|dest0
suffix:semicolon
id|j
op_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_do
(brace
op_star
id|dest
op_assign
op_complement
op_star
id|dest
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|j
)paren
suffix:semicolon
)brace
id|mask
op_rshift_assign
l_int|1
suffix:semicolon
id|dest0
op_add_assign
id|p-&gt;next_plane
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  `switch&squot; for the low level operations&n;     */
DECL|variable|fbcon_afb
r_struct
id|display_switch
id|fbcon_afb
op_assign
(brace
id|setup
suffix:colon
id|fbcon_afb_setup
comma
id|bmove
suffix:colon
id|fbcon_afb_bmove
comma
id|clear
suffix:colon
id|fbcon_afb_clear
comma
id|putc
suffix:colon
id|fbcon_afb_putc
comma
id|putcs
suffix:colon
id|fbcon_afb_putcs
comma
id|revc
suffix:colon
id|fbcon_afb_revc
comma
id|fontwidthmask
suffix:colon
id|FONTWIDTH
c_func
(paren
l_int|8
)paren
)brace
suffix:semicolon
macro_line|#ifdef MODULE
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* MODULE */
multiline_comment|/*&n;     *  Visible symbols for modules&n;     */
DECL|variable|fbcon_afb
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_afb
)paren
suffix:semicolon
DECL|variable|fbcon_afb_setup
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_afb_setup
)paren
suffix:semicolon
DECL|variable|fbcon_afb_bmove
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_afb_bmove
)paren
suffix:semicolon
DECL|variable|fbcon_afb_clear
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_afb_clear
)paren
suffix:semicolon
DECL|variable|fbcon_afb_putc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_afb_putc
)paren
suffix:semicolon
DECL|variable|fbcon_afb_putcs
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_afb_putcs
)paren
suffix:semicolon
DECL|variable|fbcon_afb_revc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_afb_revc
)paren
suffix:semicolon
eof
