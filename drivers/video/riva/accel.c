multiline_comment|/*&n; * linux/drivers/video/accel.c - nVidia RIVA 128/TNT/TNT2 fb driver&n; *&n; * Copyright 2000 Jindrich Makovicka, Ani Joshi&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &quot;rivafb.h&quot;
multiline_comment|/* acceleration routines */
DECL|function|wait_for_idle
r_inline
r_void
id|wait_for_idle
c_func
(paren
r_struct
id|rivafb_info
op_star
id|rinfo
)paren
(brace
r_while
c_loop
(paren
id|rinfo-&gt;riva
dot
id|Busy
c_func
(paren
op_amp
id|rinfo-&gt;riva
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* set copy ROP, no mask */
DECL|function|riva_setup_ROP
r_static
r_void
id|riva_setup_ROP
c_func
(paren
r_struct
id|rivafb_info
op_star
id|rinfo
)paren
(brace
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Patt
comma
l_int|5
)paren
suffix:semicolon
id|rinfo-&gt;riva.Patt-&gt;Shape
op_assign
l_int|0
suffix:semicolon
id|rinfo-&gt;riva.Patt-&gt;Color0
op_assign
l_int|0xffffffff
suffix:semicolon
id|rinfo-&gt;riva.Patt-&gt;Color1
op_assign
l_int|0xffffffff
suffix:semicolon
id|rinfo-&gt;riva.Patt-&gt;Monochrome
(braket
l_int|0
)braket
op_assign
l_int|0xffffffff
suffix:semicolon
id|rinfo-&gt;riva.Patt-&gt;Monochrome
(braket
l_int|1
)braket
op_assign
l_int|0xffffffff
suffix:semicolon
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Rop
comma
l_int|1
)paren
suffix:semicolon
id|rinfo-&gt;riva.Rop-&gt;Rop3
op_assign
l_int|0xCC
suffix:semicolon
)brace
DECL|function|riva_setup_accel
r_void
id|riva_setup_accel
c_func
(paren
r_struct
id|rivafb_info
op_star
id|rinfo
)paren
(brace
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Clip
comma
l_int|2
)paren
suffix:semicolon
id|rinfo-&gt;riva.Clip-&gt;TopLeft
op_assign
l_int|0x0
suffix:semicolon
id|rinfo-&gt;riva.Clip-&gt;WidthHeight
op_assign
l_int|0x80008000
suffix:semicolon
id|riva_setup_ROP
c_func
(paren
id|rinfo
)paren
suffix:semicolon
id|wait_for_idle
c_func
(paren
id|rinfo
)paren
suffix:semicolon
)brace
DECL|function|riva_rectfill
r_static
r_void
id|riva_rectfill
c_func
(paren
r_struct
id|rivafb_info
op_star
id|rinfo
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
comma
id|u_int
id|color
)paren
(brace
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Bitmap
comma
l_int|1
)paren
suffix:semicolon
id|rinfo-&gt;riva.Bitmap-&gt;Color1A
op_assign
id|color
suffix:semicolon
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Bitmap
comma
l_int|2
)paren
suffix:semicolon
id|rinfo-&gt;riva.Bitmap-&gt;UnclippedRectangle
(braket
l_int|0
)braket
dot
id|TopLeft
op_assign
(paren
id|sx
op_lshift
l_int|16
)paren
op_or
id|sy
suffix:semicolon
id|rinfo-&gt;riva.Bitmap-&gt;UnclippedRectangle
(braket
l_int|0
)braket
dot
id|WidthHeight
op_assign
(paren
id|width
op_lshift
l_int|16
)paren
op_or
id|height
suffix:semicolon
)brace
DECL|function|fbcon_riva_bmove
r_static
r_void
id|fbcon_riva_bmove
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
r_struct
id|rivafb_info
op_star
id|rinfo
op_assign
(paren
r_struct
id|rivafb_info
op_star
)paren
(paren
id|p-&gt;fb_info
)paren
suffix:semicolon
id|sx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|sy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|dx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|dy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|width
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|height
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Blt
comma
l_int|3
)paren
suffix:semicolon
id|rinfo-&gt;riva.Blt-&gt;TopLeftSrc
op_assign
(paren
id|sy
op_lshift
l_int|16
)paren
op_or
id|sx
suffix:semicolon
id|rinfo-&gt;riva.Blt-&gt;TopLeftDst
op_assign
(paren
id|dy
op_lshift
l_int|16
)paren
op_or
id|dx
suffix:semicolon
id|rinfo-&gt;riva.Blt-&gt;WidthHeight
op_assign
(paren
id|height
op_lshift
l_int|16
)paren
op_or
id|width
suffix:semicolon
)brace
DECL|function|riva_clear_margins
r_static
r_void
id|riva_clear_margins
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
id|bottom_only
comma
id|u32
id|bgx
)paren
(brace
r_struct
id|rivafb_info
op_star
id|rinfo
op_assign
(paren
r_struct
id|rivafb_info
op_star
)paren
(paren
id|p-&gt;fb_info
)paren
suffix:semicolon
r_int
r_int
id|right_start
op_assign
id|conp-&gt;vc_cols
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
r_int
r_int
id|bottom_start
op_assign
id|conp-&gt;vc_rows
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_int
r_int
id|right_width
comma
id|bottom_width
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bottom_only
op_logical_and
(paren
id|right_width
op_assign
id|p-&gt;var.xres
op_minus
id|right_start
)paren
)paren
id|riva_rectfill
c_func
(paren
id|rinfo
comma
l_int|0
comma
id|right_start
comma
id|p-&gt;var.yres_virtual
comma
id|right_width
comma
id|bgx
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bottom_width
op_assign
id|p-&gt;var.yres
op_minus
id|bottom_start
)paren
)paren
id|riva_rectfill
c_func
(paren
id|rinfo
comma
id|p-&gt;var.yoffset
op_plus
id|bottom_start
comma
l_int|0
comma
id|bottom_width
comma
id|right_start
comma
id|bgx
)paren
suffix:semicolon
)brace
DECL|variable|byte_rev
r_static
id|u8
id|byte_rev
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x80
comma
l_int|0x40
comma
l_int|0xc0
comma
l_int|0x20
comma
l_int|0xa0
comma
l_int|0x60
comma
l_int|0xe0
comma
l_int|0x10
comma
l_int|0x90
comma
l_int|0x50
comma
l_int|0xd0
comma
l_int|0x30
comma
l_int|0xb0
comma
l_int|0x70
comma
l_int|0xf0
comma
l_int|0x08
comma
l_int|0x88
comma
l_int|0x48
comma
l_int|0xc8
comma
l_int|0x28
comma
l_int|0xa8
comma
l_int|0x68
comma
l_int|0xe8
comma
l_int|0x18
comma
l_int|0x98
comma
l_int|0x58
comma
l_int|0xd8
comma
l_int|0x38
comma
l_int|0xb8
comma
l_int|0x78
comma
l_int|0xf8
comma
l_int|0x04
comma
l_int|0x84
comma
l_int|0x44
comma
l_int|0xc4
comma
l_int|0x24
comma
l_int|0xa4
comma
l_int|0x64
comma
l_int|0xe4
comma
l_int|0x14
comma
l_int|0x94
comma
l_int|0x54
comma
l_int|0xd4
comma
l_int|0x34
comma
l_int|0xb4
comma
l_int|0x74
comma
l_int|0xf4
comma
l_int|0x0c
comma
l_int|0x8c
comma
l_int|0x4c
comma
l_int|0xcc
comma
l_int|0x2c
comma
l_int|0xac
comma
l_int|0x6c
comma
l_int|0xec
comma
l_int|0x1c
comma
l_int|0x9c
comma
l_int|0x5c
comma
l_int|0xdc
comma
l_int|0x3c
comma
l_int|0xbc
comma
l_int|0x7c
comma
l_int|0xfc
comma
l_int|0x02
comma
l_int|0x82
comma
l_int|0x42
comma
l_int|0xc2
comma
l_int|0x22
comma
l_int|0xa2
comma
l_int|0x62
comma
l_int|0xe2
comma
l_int|0x12
comma
l_int|0x92
comma
l_int|0x52
comma
l_int|0xd2
comma
l_int|0x32
comma
l_int|0xb2
comma
l_int|0x72
comma
l_int|0xf2
comma
l_int|0x0a
comma
l_int|0x8a
comma
l_int|0x4a
comma
l_int|0xca
comma
l_int|0x2a
comma
l_int|0xaa
comma
l_int|0x6a
comma
l_int|0xea
comma
l_int|0x1a
comma
l_int|0x9a
comma
l_int|0x5a
comma
l_int|0xda
comma
l_int|0x3a
comma
l_int|0xba
comma
l_int|0x7a
comma
l_int|0xfa
comma
l_int|0x06
comma
l_int|0x86
comma
l_int|0x46
comma
l_int|0xc6
comma
l_int|0x26
comma
l_int|0xa6
comma
l_int|0x66
comma
l_int|0xe6
comma
l_int|0x16
comma
l_int|0x96
comma
l_int|0x56
comma
l_int|0xd6
comma
l_int|0x36
comma
l_int|0xb6
comma
l_int|0x76
comma
l_int|0xf6
comma
l_int|0x0e
comma
l_int|0x8e
comma
l_int|0x4e
comma
l_int|0xce
comma
l_int|0x2e
comma
l_int|0xae
comma
l_int|0x6e
comma
l_int|0xee
comma
l_int|0x1e
comma
l_int|0x9e
comma
l_int|0x5e
comma
l_int|0xde
comma
l_int|0x3e
comma
l_int|0xbe
comma
l_int|0x7e
comma
l_int|0xfe
comma
l_int|0x01
comma
l_int|0x81
comma
l_int|0x41
comma
l_int|0xc1
comma
l_int|0x21
comma
l_int|0xa1
comma
l_int|0x61
comma
l_int|0xe1
comma
l_int|0x11
comma
l_int|0x91
comma
l_int|0x51
comma
l_int|0xd1
comma
l_int|0x31
comma
l_int|0xb1
comma
l_int|0x71
comma
l_int|0xf1
comma
l_int|0x09
comma
l_int|0x89
comma
l_int|0x49
comma
l_int|0xc9
comma
l_int|0x29
comma
l_int|0xa9
comma
l_int|0x69
comma
l_int|0xe9
comma
l_int|0x19
comma
l_int|0x99
comma
l_int|0x59
comma
l_int|0xd9
comma
l_int|0x39
comma
l_int|0xb9
comma
l_int|0x79
comma
l_int|0xf9
comma
l_int|0x05
comma
l_int|0x85
comma
l_int|0x45
comma
l_int|0xc5
comma
l_int|0x25
comma
l_int|0xa5
comma
l_int|0x65
comma
l_int|0xe5
comma
l_int|0x15
comma
l_int|0x95
comma
l_int|0x55
comma
l_int|0xd5
comma
l_int|0x35
comma
l_int|0xb5
comma
l_int|0x75
comma
l_int|0xf5
comma
l_int|0x0d
comma
l_int|0x8d
comma
l_int|0x4d
comma
l_int|0xcd
comma
l_int|0x2d
comma
l_int|0xad
comma
l_int|0x6d
comma
l_int|0xed
comma
l_int|0x1d
comma
l_int|0x9d
comma
l_int|0x5d
comma
l_int|0xdd
comma
l_int|0x3d
comma
l_int|0xbd
comma
l_int|0x7d
comma
l_int|0xfd
comma
l_int|0x03
comma
l_int|0x83
comma
l_int|0x43
comma
l_int|0xc3
comma
l_int|0x23
comma
l_int|0xa3
comma
l_int|0x63
comma
l_int|0xe3
comma
l_int|0x13
comma
l_int|0x93
comma
l_int|0x53
comma
l_int|0xd3
comma
l_int|0x33
comma
l_int|0xb3
comma
l_int|0x73
comma
l_int|0xf3
comma
l_int|0x0b
comma
l_int|0x8b
comma
l_int|0x4b
comma
l_int|0xcb
comma
l_int|0x2b
comma
l_int|0xab
comma
l_int|0x6b
comma
l_int|0xeb
comma
l_int|0x1b
comma
l_int|0x9b
comma
l_int|0x5b
comma
l_int|0xdb
comma
l_int|0x3b
comma
l_int|0xbb
comma
l_int|0x7b
comma
l_int|0xfb
comma
l_int|0x07
comma
l_int|0x87
comma
l_int|0x47
comma
l_int|0xc7
comma
l_int|0x27
comma
l_int|0xa7
comma
l_int|0x67
comma
l_int|0xe7
comma
l_int|0x17
comma
l_int|0x97
comma
l_int|0x57
comma
l_int|0xd7
comma
l_int|0x37
comma
l_int|0xb7
comma
l_int|0x77
comma
l_int|0xf7
comma
l_int|0x0f
comma
l_int|0x8f
comma
l_int|0x4f
comma
l_int|0xcf
comma
l_int|0x2f
comma
l_int|0xaf
comma
l_int|0x6f
comma
l_int|0xef
comma
l_int|0x1f
comma
l_int|0x9f
comma
l_int|0x5f
comma
l_int|0xdf
comma
l_int|0x3f
comma
l_int|0xbf
comma
l_int|0x7f
comma
l_int|0xff
comma
)brace
suffix:semicolon
DECL|function|fbcon_reverse_order
r_static
r_inline
r_void
id|fbcon_reverse_order
c_func
(paren
id|u32
op_star
id|l
)paren
(brace
id|u8
op_star
id|a
op_assign
(paren
id|u8
op_star
)paren
id|l
suffix:semicolon
op_star
id|a
op_increment
op_assign
id|byte_rev
(braket
op_star
id|a
)braket
suffix:semicolon
multiline_comment|/*&t;*a++ = byte_rev[*a];&n;&t;*a++ = byte_rev[*a];*/
op_star
id|a
op_assign
id|byte_rev
(braket
op_star
id|a
)braket
suffix:semicolon
)brace
DECL|function|fbcon_riva_writechr
r_static
r_void
id|fbcon_riva_writechr
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
id|fgx
comma
r_int
id|bgx
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
id|cdat
suffix:semicolon
r_struct
id|rivafb_info
op_star
id|rinfo
op_assign
(paren
r_struct
id|rivafb_info
op_star
)paren
(paren
id|p-&gt;fb_info
)paren
suffix:semicolon
r_int
id|w
comma
id|h
suffix:semicolon
r_volatile
id|u32
op_star
id|d
suffix:semicolon
id|u32
id|cdat2
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|cnt
suffix:semicolon
id|w
op_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|h
op_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|w
op_le
l_int|8
)paren
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
(paren
id|c
op_amp
id|p-&gt;charmask
)paren
op_star
id|h
suffix:semicolon
r_else
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
(paren
(paren
id|c
op_amp
id|p-&gt;charmask
)paren
op_star
id|h
op_lshift
l_int|1
)paren
suffix:semicolon
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Bitmap
comma
l_int|7
)paren
suffix:semicolon
id|rinfo-&gt;riva.Bitmap-&gt;ClipE.TopLeft
op_assign
(paren
id|yy
op_lshift
l_int|16
)paren
op_or
(paren
id|xx
op_amp
l_int|0xFFFF
)paren
suffix:semicolon
id|rinfo-&gt;riva.Bitmap-&gt;ClipE.BottomRight
op_assign
(paren
(paren
id|yy
op_plus
id|h
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|xx
op_plus
id|w
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|rinfo-&gt;riva.Bitmap-&gt;Color0E
op_assign
id|bgx
suffix:semicolon
id|rinfo-&gt;riva.Bitmap-&gt;Color1E
op_assign
id|fgx
suffix:semicolon
id|rinfo-&gt;riva.Bitmap-&gt;WidthHeightInE
op_assign
(paren
id|h
op_lshift
l_int|16
)paren
op_or
l_int|32
suffix:semicolon
id|rinfo-&gt;riva.Bitmap-&gt;WidthHeightOutE
op_assign
(paren
id|h
op_lshift
l_int|16
)paren
op_or
l_int|32
suffix:semicolon
id|rinfo-&gt;riva.Bitmap-&gt;PointE
op_assign
(paren
id|yy
op_lshift
l_int|16
)paren
op_or
(paren
id|xx
op_amp
l_int|0xFFFF
)paren
suffix:semicolon
id|d
op_assign
op_amp
id|rinfo-&gt;riva.Bitmap-&gt;MonochromeData01E
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|h
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_sub_assign
l_int|16
)paren
(brace
r_if
c_cond
(paren
id|i
op_ge
l_int|16
)paren
id|cnt
op_assign
l_int|16
suffix:semicolon
r_else
id|cnt
op_assign
id|i
suffix:semicolon
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Bitmap
comma
id|cnt
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|w
op_le
l_int|8
)paren
id|cdat2
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
r_else
id|cdat2
op_assign
op_star
(paren
(paren
id|u16
op_star
)paren
id|cdat
)paren
op_increment
suffix:semicolon
id|fbcon_reverse_order
c_func
(paren
op_amp
id|cdat2
)paren
suffix:semicolon
id|d
(braket
id|j
)braket
op_assign
id|cdat2
suffix:semicolon
)brace
)brace
)brace
macro_line|#ifdef FBCON_HAS_CFB8
DECL|function|fbcon_riva8_setup
r_void
id|fbcon_riva8_setup
c_func
(paren
r_struct
id|display
op_star
id|p
)paren
(brace
id|p-&gt;next_line
op_assign
id|p-&gt;line_length
ques
c_cond
id|p-&gt;line_length
suffix:colon
id|p-&gt;var.xres_virtual
suffix:semicolon
id|p-&gt;next_plane
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|fbcon_riva8_clear
r_static
r_void
id|fbcon_riva8_clear
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
id|u32
id|bgx
suffix:semicolon
r_struct
id|rivafb_info
op_star
id|rinfo
op_assign
(paren
r_struct
id|rivafb_info
op_star
)paren
(paren
id|p-&gt;fb_info
)paren
suffix:semicolon
id|bgx
op_assign
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|sx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|sy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|width
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|height
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|riva_rectfill
c_func
(paren
id|rinfo
comma
id|sy
comma
id|sx
comma
id|height
comma
id|width
comma
id|bgx
)paren
suffix:semicolon
)brace
DECL|function|fbcon_riva8_putc
r_static
r_void
id|fbcon_riva8_putc
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
id|u32
id|fgx
comma
id|bgx
suffix:semicolon
id|fgx
op_assign
id|attr_fgcol
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
id|bgx
op_assign
id|attr_bgcol
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
id|xx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|yy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|fbcon_riva_writechr
c_func
(paren
id|conp
comma
id|p
comma
id|c
comma
id|fgx
comma
id|bgx
comma
id|yy
comma
id|xx
)paren
suffix:semicolon
)brace
DECL|function|fbcon_riva8_putcs
r_static
r_void
id|fbcon_riva8_putcs
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
id|u16
id|c
suffix:semicolon
id|u32
id|fgx
comma
id|bgx
suffix:semicolon
id|xx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|yy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|c
op_assign
id|scr_readw
c_func
(paren
id|s
)paren
suffix:semicolon
id|fgx
op_assign
id|attr_fgcol
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
id|bgx
op_assign
id|attr_bgcol
c_func
(paren
id|p
comma
id|c
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|c
op_assign
id|scr_readw
c_func
(paren
id|s
op_increment
)paren
suffix:semicolon
id|fbcon_riva_writechr
c_func
(paren
id|conp
comma
id|p
comma
id|c
comma
id|fgx
comma
id|bgx
comma
id|yy
comma
id|xx
)paren
suffix:semicolon
id|xx
op_add_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_riva8_revc
r_static
r_void
id|fbcon_riva8_revc
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
r_struct
id|rivafb_info
op_star
id|rinfo
op_assign
(paren
r_struct
id|rivafb_info
op_star
)paren
(paren
id|p-&gt;fb_info
)paren
suffix:semicolon
id|xx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|yy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Rop
comma
l_int|1
)paren
suffix:semicolon
id|rinfo-&gt;riva.Rop-&gt;Rop3
op_assign
l_int|0x66
suffix:semicolon
singleline_comment|// XOR
id|riva_rectfill
c_func
(paren
id|rinfo
comma
id|yy
comma
id|xx
comma
id|fontheight
c_func
(paren
id|p
)paren
comma
id|fontwidth
c_func
(paren
id|p
)paren
comma
l_int|0x0f
)paren
suffix:semicolon
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Rop
comma
l_int|1
)paren
suffix:semicolon
id|rinfo-&gt;riva.Rop-&gt;Rop3
op_assign
l_int|0xCC
suffix:semicolon
singleline_comment|// back to COPY
)brace
DECL|function|fbcon_riva8_clear_margins
r_static
r_void
id|fbcon_riva8_clear_margins
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
id|bottom_only
)paren
(brace
id|riva_clear_margins
c_func
(paren
id|conp
comma
id|p
comma
id|bottom_only
comma
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
)paren
suffix:semicolon
)brace
DECL|variable|fbcon_riva8
r_struct
id|display_switch
id|fbcon_riva8
op_assign
(brace
id|setup
suffix:colon
id|fbcon_riva8_setup
comma
id|bmove
suffix:colon
id|fbcon_riva_bmove
comma
id|clear
suffix:colon
id|fbcon_riva8_clear
comma
id|putc
suffix:colon
id|fbcon_riva8_putc
comma
id|putcs
suffix:colon
id|fbcon_riva8_putcs
comma
id|revc
suffix:colon
id|fbcon_riva8_revc
comma
id|clear_margins
suffix:colon
id|fbcon_riva8_clear_margins
comma
id|fontwidthmask
suffix:colon
id|FONTWIDTHRANGE
c_func
(paren
l_int|4
comma
l_int|16
)paren
)brace
suffix:semicolon
macro_line|#endif
macro_line|#if defined(FBCON_HAS_CFB16) || defined(FBCON_HAS_CFB32)
DECL|function|fbcon_riva1632_revc
r_static
r_void
id|fbcon_riva1632_revc
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
r_struct
id|rivafb_info
op_star
id|rinfo
op_assign
(paren
r_struct
id|rivafb_info
op_star
)paren
(paren
id|p-&gt;fb_info
)paren
suffix:semicolon
id|xx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|yy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Rop
comma
l_int|1
)paren
suffix:semicolon
id|rinfo-&gt;riva.Rop-&gt;Rop3
op_assign
l_int|0x66
suffix:semicolon
singleline_comment|// XOR
id|riva_rectfill
c_func
(paren
id|rinfo
comma
id|yy
comma
id|xx
comma
id|fontheight
c_func
(paren
id|p
)paren
comma
id|fontwidth
c_func
(paren
id|p
)paren
comma
l_int|0xffffffff
)paren
suffix:semicolon
id|RIVA_FIFO_FREE
c_func
(paren
id|rinfo-&gt;riva
comma
id|Rop
comma
l_int|1
)paren
suffix:semicolon
id|rinfo-&gt;riva.Rop-&gt;Rop3
op_assign
l_int|0xCC
suffix:semicolon
singleline_comment|// back to COPY
)brace
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB16
DECL|function|fbcon_riva16_setup
r_void
id|fbcon_riva16_setup
c_func
(paren
r_struct
id|display
op_star
id|p
)paren
(brace
id|p-&gt;next_line
op_assign
id|p-&gt;line_length
ques
c_cond
id|p-&gt;line_length
suffix:colon
id|p-&gt;var.xres_virtual
op_lshift
l_int|1
suffix:semicolon
id|p-&gt;next_plane
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|fbcon_riva16_clear
r_static
r_void
id|fbcon_riva16_clear
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
id|u32
id|bgx
suffix:semicolon
r_struct
id|rivafb_info
op_star
id|rinfo
op_assign
(paren
r_struct
id|rivafb_info
op_star
)paren
(paren
id|p-&gt;fb_info
)paren
suffix:semicolon
id|bgx
op_assign
(paren
(paren
id|u_int16_t
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
)braket
suffix:semicolon
id|sx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|sy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|width
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|height
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|riva_rectfill
c_func
(paren
id|rinfo
comma
id|sy
comma
id|sx
comma
id|height
comma
id|width
comma
id|bgx
)paren
suffix:semicolon
)brace
DECL|function|convert_bgcolor_16
r_static
r_inline
r_void
id|convert_bgcolor_16
c_func
(paren
id|u32
op_star
id|col
)paren
(brace
op_star
id|col
op_assign
(paren
(paren
op_star
id|col
op_amp
l_int|0x00007C00
)paren
op_lshift
l_int|9
)paren
op_or
(paren
(paren
op_star
id|col
op_amp
l_int|0x000003E0
)paren
op_lshift
l_int|6
)paren
op_or
(paren
(paren
op_star
id|col
op_amp
l_int|0x0000001F
)paren
op_lshift
l_int|3
)paren
op_or
l_int|0xFF000000
suffix:semicolon
)brace
DECL|function|fbcon_riva16_putc
r_static
r_void
id|fbcon_riva16_putc
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
id|u32
id|fgx
comma
id|bgx
suffix:semicolon
id|fgx
op_assign
(paren
(paren
id|u16
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_fgcol
c_func
(paren
id|p
comma
id|c
)paren
)braket
suffix:semicolon
id|bgx
op_assign
(paren
(paren
id|u16
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol
c_func
(paren
id|p
comma
id|c
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;var.green.length
op_eq
l_int|6
)paren
id|convert_bgcolor_16
c_func
(paren
op_amp
id|bgx
)paren
suffix:semicolon
id|xx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|yy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|fbcon_riva_writechr
c_func
(paren
id|conp
comma
id|p
comma
id|c
comma
id|fgx
comma
id|bgx
comma
id|yy
comma
id|xx
)paren
suffix:semicolon
)brace
DECL|function|fbcon_riva16_putcs
r_static
r_void
id|fbcon_riva16_putcs
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
id|u16
id|c
suffix:semicolon
id|u32
id|fgx
comma
id|bgx
suffix:semicolon
id|xx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|yy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|c
op_assign
id|scr_readw
c_func
(paren
id|s
)paren
suffix:semicolon
id|fgx
op_assign
(paren
(paren
id|u16
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_fgcol
c_func
(paren
id|p
comma
id|c
)paren
)braket
suffix:semicolon
id|bgx
op_assign
(paren
(paren
id|u16
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol
c_func
(paren
id|p
comma
id|c
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;var.green.length
op_eq
l_int|6
)paren
id|convert_bgcolor_16
c_func
(paren
op_amp
id|bgx
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|c
op_assign
id|scr_readw
c_func
(paren
id|s
op_increment
)paren
suffix:semicolon
id|fbcon_riva_writechr
c_func
(paren
id|conp
comma
id|p
comma
id|c
comma
id|fgx
comma
id|bgx
comma
id|yy
comma
id|xx
)paren
suffix:semicolon
id|xx
op_add_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_riva16_clear_margins
r_static
r_void
id|fbcon_riva16_clear_margins
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
id|bottom_only
)paren
(brace
id|riva_clear_margins
c_func
(paren
id|conp
comma
id|p
comma
id|bottom_only
comma
(paren
(paren
id|u16
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
)braket
)paren
suffix:semicolon
)brace
DECL|variable|fbcon_riva16
r_struct
id|display_switch
id|fbcon_riva16
op_assign
(brace
id|setup
suffix:colon
id|fbcon_riva16_setup
comma
id|bmove
suffix:colon
id|fbcon_riva_bmove
comma
id|clear
suffix:colon
id|fbcon_riva16_clear
comma
id|putc
suffix:colon
id|fbcon_riva16_putc
comma
id|putcs
suffix:colon
id|fbcon_riva16_putcs
comma
id|revc
suffix:colon
id|fbcon_riva1632_revc
comma
id|clear_margins
suffix:colon
id|fbcon_riva16_clear_margins
comma
id|fontwidthmask
suffix:colon
id|FONTWIDTHRANGE
c_func
(paren
l_int|4
comma
l_int|16
)paren
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
DECL|function|fbcon_riva32_setup
r_void
id|fbcon_riva32_setup
c_func
(paren
r_struct
id|display
op_star
id|p
)paren
(brace
id|p-&gt;next_line
op_assign
id|p-&gt;line_length
ques
c_cond
id|p-&gt;line_length
suffix:colon
id|p-&gt;var.xres_virtual
op_lshift
l_int|2
suffix:semicolon
id|p-&gt;next_plane
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|fbcon_riva32_clear
r_static
r_void
id|fbcon_riva32_clear
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
id|u32
id|bgx
suffix:semicolon
r_struct
id|rivafb_info
op_star
id|rinfo
op_assign
(paren
r_struct
id|rivafb_info
op_star
)paren
(paren
id|p-&gt;fb_info
)paren
suffix:semicolon
id|bgx
op_assign
(paren
(paren
id|u_int32_t
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
)braket
suffix:semicolon
id|sx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|sy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|width
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|height
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|riva_rectfill
c_func
(paren
id|rinfo
comma
id|sy
comma
id|sx
comma
id|height
comma
id|width
comma
id|bgx
)paren
suffix:semicolon
)brace
DECL|function|fbcon_riva32_putc
r_static
r_void
id|fbcon_riva32_putc
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
id|u32
id|fgx
comma
id|bgx
suffix:semicolon
id|fgx
op_assign
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_fgcol
c_func
(paren
id|p
comma
id|c
)paren
)braket
suffix:semicolon
id|bgx
op_assign
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol
c_func
(paren
id|p
comma
id|c
)paren
)braket
suffix:semicolon
id|xx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|yy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|fbcon_riva_writechr
c_func
(paren
id|conp
comma
id|p
comma
id|c
comma
id|fgx
comma
id|bgx
comma
id|yy
comma
id|xx
)paren
suffix:semicolon
)brace
DECL|function|fbcon_riva32_putcs
r_static
r_void
id|fbcon_riva32_putcs
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
id|u16
id|c
suffix:semicolon
id|u32
id|fgx
comma
id|bgx
suffix:semicolon
id|xx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|yy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|c
op_assign
id|scr_readw
c_func
(paren
id|s
)paren
suffix:semicolon
id|fgx
op_assign
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_fgcol
c_func
(paren
id|p
comma
id|c
)paren
)braket
suffix:semicolon
id|bgx
op_assign
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol
c_func
(paren
id|p
comma
id|c
)paren
)braket
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|c
op_assign
id|scr_readw
c_func
(paren
id|s
op_increment
)paren
suffix:semicolon
id|fbcon_riva_writechr
c_func
(paren
id|conp
comma
id|p
comma
id|c
comma
id|fgx
comma
id|bgx
comma
id|yy
comma
id|xx
)paren
suffix:semicolon
id|xx
op_add_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_riva32_clear_margins
r_static
r_void
id|fbcon_riva32_clear_margins
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
id|bottom_only
)paren
(brace
id|riva_clear_margins
c_func
(paren
id|conp
comma
id|p
comma
id|bottom_only
comma
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
)braket
)paren
suffix:semicolon
)brace
DECL|variable|fbcon_riva32
r_struct
id|display_switch
id|fbcon_riva32
op_assign
(brace
id|setup
suffix:colon
id|fbcon_riva32_setup
comma
id|bmove
suffix:colon
id|fbcon_riva_bmove
comma
id|clear
suffix:colon
id|fbcon_riva32_clear
comma
id|putc
suffix:colon
id|fbcon_riva32_putc
comma
id|putcs
suffix:colon
id|fbcon_riva32_putcs
comma
id|revc
suffix:colon
id|fbcon_riva1632_revc
comma
id|clear_margins
suffix:colon
id|fbcon_riva32_clear_margins
comma
id|fontwidthmask
suffix:colon
id|FONTWIDTHRANGE
c_func
(paren
l_int|4
comma
l_int|16
)paren
)brace
suffix:semicolon
macro_line|#endif
eof
