multiline_comment|/*&n; * Zoran ZR36016 basic configuration functions - header file&n; *&n; * Copyright (C) 2001 Wolfgang Scherr &lt;scherr@net4you.at&gt;&n; *&n; * $Id: zr36016.h,v 1.1.2.3 2003/01/14 21:18:07 rbultje Exp $&n; *&n; * ------------------------------------------------------------------------&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * ------------------------------------------------------------------------&n; */
macro_line|#ifndef ZR36016_H
DECL|macro|ZR36016_H
mdefine_line|#define ZR36016_H
multiline_comment|/* data stored for each zoran jpeg codec chip */
DECL|struct|zr36016
r_struct
id|zr36016
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|num
r_int
id|num
suffix:semicolon
multiline_comment|/* io datastructure */
DECL|member|codec
r_struct
id|videocodec
op_star
id|codec
suffix:semicolon
singleline_comment|// coder status
DECL|member|version
id|__u8
id|version
suffix:semicolon
singleline_comment|// actual coder setup
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|xoff
id|__u16
id|xoff
suffix:semicolon
DECL|member|yoff
id|__u16
id|yoff
suffix:semicolon
DECL|member|width
id|__u16
id|width
suffix:semicolon
DECL|member|height
id|__u16
id|height
suffix:semicolon
DECL|member|xdec
id|__u16
id|xdec
suffix:semicolon
DECL|member|ydec
id|__u16
id|ydec
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* direct  register addresses */
DECL|macro|ZR016_GOSTOP
mdefine_line|#define ZR016_GOSTOP      0x00
DECL|macro|ZR016_MODE
mdefine_line|#define ZR016_MODE        0x01
DECL|macro|ZR016_IADDR
mdefine_line|#define ZR016_IADDR       0x02
DECL|macro|ZR016_IDATA
mdefine_line|#define ZR016_IDATA       0x03
multiline_comment|/* indirect  register addresses */
DECL|macro|ZR016I_SETUP1
mdefine_line|#define ZR016I_SETUP1     0x00
DECL|macro|ZR016I_SETUP2
mdefine_line|#define ZR016I_SETUP2     0x01
DECL|macro|ZR016I_NAX_LO
mdefine_line|#define ZR016I_NAX_LO     0x02
DECL|macro|ZR016I_NAX_HI
mdefine_line|#define ZR016I_NAX_HI     0x03
DECL|macro|ZR016I_PAX_LO
mdefine_line|#define ZR016I_PAX_LO     0x04
DECL|macro|ZR016I_PAX_HI
mdefine_line|#define ZR016I_PAX_HI     0x05
DECL|macro|ZR016I_NAY_LO
mdefine_line|#define ZR016I_NAY_LO     0x06
DECL|macro|ZR016I_NAY_HI
mdefine_line|#define ZR016I_NAY_HI     0x07
DECL|macro|ZR016I_PAY_LO
mdefine_line|#define ZR016I_PAY_LO     0x08
DECL|macro|ZR016I_PAY_HI
mdefine_line|#define ZR016I_PAY_HI     0x09
DECL|macro|ZR016I_NOL_LO
mdefine_line|#define ZR016I_NOL_LO     0x0a
DECL|macro|ZR016I_NOL_HI
mdefine_line|#define ZR016I_NOL_HI     0x0b
multiline_comment|/* possible values for mode register */
DECL|macro|ZR016_RGB444_YUV444
mdefine_line|#define ZR016_RGB444_YUV444  0x00
DECL|macro|ZR016_RGB444_YUV422
mdefine_line|#define ZR016_RGB444_YUV422  0x01
DECL|macro|ZR016_RGB444_YUV411
mdefine_line|#define ZR016_RGB444_YUV411  0x02
DECL|macro|ZR016_RGB444_Y400
mdefine_line|#define ZR016_RGB444_Y400    0x03
DECL|macro|ZR016_RGB444_RGB444
mdefine_line|#define ZR016_RGB444_RGB444  0x04
DECL|macro|ZR016_YUV444_YUV444
mdefine_line|#define ZR016_YUV444_YUV444  0x08
DECL|macro|ZR016_YUV444_YUV422
mdefine_line|#define ZR016_YUV444_YUV422  0x09
DECL|macro|ZR016_YUV444_YUV411
mdefine_line|#define ZR016_YUV444_YUV411  0x0a
DECL|macro|ZR016_YUV444_Y400
mdefine_line|#define ZR016_YUV444_Y400    0x0b
DECL|macro|ZR016_YUV444_RGB444
mdefine_line|#define ZR016_YUV444_RGB444  0x0c
DECL|macro|ZR016_YUV422_YUV422
mdefine_line|#define ZR016_YUV422_YUV422  0x11
DECL|macro|ZR016_YUV422_YUV411
mdefine_line|#define ZR016_YUV422_YUV411  0x12
DECL|macro|ZR016_YUV422_Y400
mdefine_line|#define ZR016_YUV422_Y400    0x13
DECL|macro|ZR016_YUV411_YUV411
mdefine_line|#define ZR016_YUV411_YUV411  0x16
DECL|macro|ZR016_YUV411_Y400
mdefine_line|#define ZR016_YUV411_Y400    0x17
DECL|macro|ZR016_4444_4444
mdefine_line|#define ZR016_4444_4444      0x19
DECL|macro|ZR016_100_100
mdefine_line|#define ZR016_100_100        0x1b
DECL|macro|ZR016_RGB444
mdefine_line|#define ZR016_RGB444         0x00
DECL|macro|ZR016_YUV444
mdefine_line|#define ZR016_YUV444         0x20
DECL|macro|ZR016_YUV422
mdefine_line|#define ZR016_YUV422         0x40
DECL|macro|ZR016_COMPRESSION
mdefine_line|#define ZR016_COMPRESSION    0x80
DECL|macro|ZR016_EXPANSION
mdefine_line|#define ZR016_EXPANSION      0x80
multiline_comment|/* possible values for setup 1 register */
DECL|macro|ZR016_CKRT
mdefine_line|#define ZR016_CKRT           0x80
DECL|macro|ZR016_VERT
mdefine_line|#define ZR016_VERT           0x40
DECL|macro|ZR016_HORZ
mdefine_line|#define ZR016_HORZ           0x20
DECL|macro|ZR016_HRFL
mdefine_line|#define ZR016_HRFL           0x10
DECL|macro|ZR016_DSFL
mdefine_line|#define ZR016_DSFL           0x08
DECL|macro|ZR016_SBFL
mdefine_line|#define ZR016_SBFL           0x04
DECL|macro|ZR016_RSTR
mdefine_line|#define ZR016_RSTR           0x02
DECL|macro|ZR016_CNTI
mdefine_line|#define ZR016_CNTI           0x01
multiline_comment|/* possible values for setup 2 register */
DECL|macro|ZR016_SYEN
mdefine_line|#define ZR016_SYEN           0x40
DECL|macro|ZR016_CCIR
mdefine_line|#define ZR016_CCIR           0x04
DECL|macro|ZR016_SIGN
mdefine_line|#define ZR016_SIGN           0x02
DECL|macro|ZR016_YMCS
mdefine_line|#define ZR016_YMCS           0x01
macro_line|#endif&t;&t;&t;&t;/*fndef ZR36016_H */
eof
