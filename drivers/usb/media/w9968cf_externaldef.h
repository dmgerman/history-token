multiline_comment|/***************************************************************************&n; * Various definitions for compatibility with external modules.            *&n; * This file is part of the W996[87]CF driver for Linux.                   *&n; *                                                                         *&n; * Copyright (C) 2002 2003 by Luca Risolia &lt;luca_ing@libero.it&gt;            *&n; *                                                                         *&n; * This program is free software; you can redistribute it and/or modify    *&n; * it under the terms of the GNU General Public License as published by    *&n; * the Free Software Foundation; either version 2 of the License, or       *&n; * (at your option) any later version.                                     *&n; *                                                                         *&n; * This program is distributed in the hope that it will be useful,         *&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of          *&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *&n; * GNU General Public License for more details.                            *&n; *                                                                         *&n; * You should have received a copy of the GNU General Public License       *&n; * along with this program; if not, write to the Free Software             *&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.               *&n; ***************************************************************************/
macro_line|#ifndef _W9968CF_EXTERNALDEF_H_
DECL|macro|_W9968CF_EXTERNALDEF_H_
mdefine_line|#define _W9968CF_EXTERNALDEF_H_
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;asm/ioctl.h&gt;
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* The following values have been copied from the &quot;ovcamchip&quot; module. */
macro_line|#ifndef I2C_DRIVERID_OVCAMCHIP
DECL|macro|I2C_DRIVERID_OVCAMCHIP
macro_line|#&t;define I2C_DRIVERID_OVCAMCHIP   0xf00f
macro_line|#endif
multiline_comment|/* Controls */
r_enum
(brace
DECL|enumerator|OVCAMCHIP_CID_CONT
id|OVCAMCHIP_CID_CONT
comma
multiline_comment|/* Contrast */
DECL|enumerator|OVCAMCHIP_CID_BRIGHT
id|OVCAMCHIP_CID_BRIGHT
comma
multiline_comment|/* Brightness */
DECL|enumerator|OVCAMCHIP_CID_SAT
id|OVCAMCHIP_CID_SAT
comma
multiline_comment|/* Saturation */
DECL|enumerator|OVCAMCHIP_CID_HUE
id|OVCAMCHIP_CID_HUE
comma
multiline_comment|/* Hue */
DECL|enumerator|OVCAMCHIP_CID_EXP
id|OVCAMCHIP_CID_EXP
comma
multiline_comment|/* Exposure */
DECL|enumerator|OVCAMCHIP_CID_FREQ
id|OVCAMCHIP_CID_FREQ
comma
multiline_comment|/* Light frequency */
DECL|enumerator|OVCAMCHIP_CID_BANDFILT
id|OVCAMCHIP_CID_BANDFILT
comma
multiline_comment|/* Banding filter */
DECL|enumerator|OVCAMCHIP_CID_AUTOBRIGHT
id|OVCAMCHIP_CID_AUTOBRIGHT
comma
multiline_comment|/* Auto brightness */
DECL|enumerator|OVCAMCHIP_CID_AUTOEXP
id|OVCAMCHIP_CID_AUTOEXP
comma
multiline_comment|/* Auto exposure */
DECL|enumerator|OVCAMCHIP_CID_BACKLIGHT
id|OVCAMCHIP_CID_BACKLIGHT
comma
multiline_comment|/* Back light compensation */
DECL|enumerator|OVCAMCHIP_CID_MIRROR
id|OVCAMCHIP_CID_MIRROR
comma
multiline_comment|/* Mirror horizontally */
)brace
suffix:semicolon
multiline_comment|/* I2C addresses */
DECL|macro|OV7xx0_SID
mdefine_line|#define OV7xx0_SID   (0x42 &gt;&gt; 1)
DECL|macro|OV6xx0_SID
mdefine_line|#define OV6xx0_SID   (0xC0 &gt;&gt; 1)
multiline_comment|/* Sensor types */
r_enum
(brace
DECL|enumerator|CC_UNKNOWN
id|CC_UNKNOWN
comma
DECL|enumerator|CC_OV76BE
id|CC_OV76BE
comma
DECL|enumerator|CC_OV7610
id|CC_OV7610
comma
DECL|enumerator|CC_OV7620
id|CC_OV7620
comma
DECL|enumerator|CC_OV7620AE
id|CC_OV7620AE
comma
DECL|enumerator|CC_OV6620
id|CC_OV6620
comma
DECL|enumerator|CC_OV6630
id|CC_OV6630
comma
DECL|enumerator|CC_OV6630AE
id|CC_OV6630AE
comma
DECL|enumerator|CC_OV6630AF
id|CC_OV6630AF
comma
)brace
suffix:semicolon
multiline_comment|/* API */
DECL|struct|ovcamchip_control
r_struct
id|ovcamchip_control
(brace
DECL|member|id
id|__u32
id|id
suffix:semicolon
DECL|member|value
id|__s32
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ovcamchip_window
r_struct
id|ovcamchip_window
(brace
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
id|height
suffix:semicolon
DECL|member|format
r_int
id|format
suffix:semicolon
DECL|member|quarter
r_int
id|quarter
suffix:semicolon
multiline_comment|/* Scale width and height down 2x */
multiline_comment|/* This stuff will be removed eventually */
DECL|member|clockdiv
r_int
id|clockdiv
suffix:semicolon
multiline_comment|/* Clock divisor setting */
)brace
suffix:semicolon
multiline_comment|/* Commands. &n;   You must call OVCAMCHIP_CMD_INITIALIZE before any of other commands */
DECL|macro|OVCAMCHIP_CMD_Q_SUBTYPE
mdefine_line|#define OVCAMCHIP_CMD_Q_SUBTYPE  _IOR  (0x88, 0x00, int)
DECL|macro|OVCAMCHIP_CMD_INITIALIZE
mdefine_line|#define OVCAMCHIP_CMD_INITIALIZE _IOW  (0x88, 0x01, int)
DECL|macro|OVCAMCHIP_CMD_S_CTRL
mdefine_line|#define OVCAMCHIP_CMD_S_CTRL     _IOW  (0x88, 0x02, struct ovcamchip_control)
DECL|macro|OVCAMCHIP_CMD_G_CTRL
mdefine_line|#define OVCAMCHIP_CMD_G_CTRL     _IOWR (0x88, 0x03, struct ovcamchip_control)
DECL|macro|OVCAMCHIP_CMD_S_MODE
mdefine_line|#define OVCAMCHIP_CMD_S_MODE     _IOW  (0x88, 0x04, struct ovcamchip_window)
DECL|macro|OVCAMCHIP_MAX_CMD
mdefine_line|#define OVCAMCHIP_MAX_CMD        _IO   (0x88, 0x3f)
macro_line|#endif /* _W9968CF_EXTERNALDEF_H_ */
eof
