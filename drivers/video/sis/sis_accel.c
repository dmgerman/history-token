multiline_comment|/*&n; * SiS 300/630/730/540/315/550/65x/74x/330/760 frame buffer driver&n; * for Linux kernels 2.4.x and 2.6.x&n; *&n; * 2D acceleration part&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the named License,&n; * or any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA&n; *&n; * Based on the XFree86 driver&squot;s sis300_accel.c which is&n; *     Copyright (C) 2001-2004 by Thomas Winischhofer, Vienna, Austria&n; * and sis310_accel.c which is&n; *     Copyright (C) 2001-2004 by Thomas Winischhofer, Vienna, Austria&n; *&n; * Author: Thomas Winischhofer &lt;thomas@winischhofer.net&gt;&n; *&t;&t;&t;(see http://www.winischhofer.net/&n; *&t;&t;&t;for more information and updates)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)
macro_line|#include &lt;linux/sisfb.h&gt;
macro_line|#else
macro_line|#include &lt;video/sisfb.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_MTRR
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &lt;video/fbcon-cfb16.h&gt;
macro_line|#include &lt;video/fbcon-cfb24.h&gt;
macro_line|#include &lt;video/fbcon-cfb32.h&gt;
macro_line|#endif
macro_line|#include &quot;osdef.h&quot;
macro_line|#include &quot;vgatypes.h&quot;
macro_line|#include &quot;vstruct.h&quot;
macro_line|#include &quot;sis_accel.h&quot;
macro_line|#include &quot;sis.h&quot;
r_extern
r_struct
id|video_info
id|ivideo
suffix:semicolon
r_extern
id|VGA_ENGINE
id|sisvga_engine
suffix:semicolon
r_extern
r_int
id|sisfb_accel
suffix:semicolon
DECL|variable|sisALUConv
r_static
r_const
r_int
id|sisALUConv
(braket
)braket
op_assign
(brace
l_int|0x00
comma
multiline_comment|/* dest = 0;            0,      GXclear,        0 */
l_int|0x88
comma
multiline_comment|/* dest &amp;= src;         DSa,    GXand,          0x1 */
l_int|0x44
comma
multiline_comment|/* dest = src &amp; ~dest;  SDna,   GXandReverse,   0x2 */
l_int|0xCC
comma
multiline_comment|/* dest = src;          S,      GXcopy,         0x3 */
l_int|0x22
comma
multiline_comment|/* dest &amp;= ~src;        DSna,   GXandInverted,  0x4 */
l_int|0xAA
comma
multiline_comment|/* dest = dest;         D,      GXnoop,         0x5 */
l_int|0x66
comma
multiline_comment|/* dest = ^src;         DSx,    GXxor,          0x6 */
l_int|0xEE
comma
multiline_comment|/* dest |= src;         DSo,    GXor,           0x7 */
l_int|0x11
comma
multiline_comment|/* dest = ~src &amp; ~dest; DSon,   GXnor,          0x8 */
l_int|0x99
comma
multiline_comment|/* dest ^= ~src ;       DSxn,   GXequiv,        0x9 */
l_int|0x55
comma
multiline_comment|/* dest = ~dest;        Dn,     GXInvert,       0xA */
l_int|0xDD
comma
multiline_comment|/* dest = src|~dest ;   SDno,   GXorReverse,    0xB */
l_int|0x33
comma
multiline_comment|/* dest = ~src;         Sn,     GXcopyInverted, 0xC */
l_int|0xBB
comma
multiline_comment|/* dest |= ~src;        DSno,   GXorInverted,   0xD */
l_int|0x77
comma
multiline_comment|/* dest = ~src|~dest;   DSan,   GXnand,         0xE */
l_int|0xFF
comma
multiline_comment|/* dest = 0xFF;         1,      GXset,          0xF */
)brace
suffix:semicolon
multiline_comment|/* same ROP but with Pattern as Source */
DECL|variable|sisPatALUConv
r_static
r_const
r_int
id|sisPatALUConv
(braket
)braket
op_assign
(brace
l_int|0x00
comma
multiline_comment|/* dest = 0;            0,      GXclear,        0 */
l_int|0xA0
comma
multiline_comment|/* dest &amp;= src;         DPa,    GXand,          0x1 */
l_int|0x50
comma
multiline_comment|/* dest = src &amp; ~dest;  PDna,   GXandReverse,   0x2 */
l_int|0xF0
comma
multiline_comment|/* dest = src;          P,      GXcopy,         0x3 */
l_int|0x0A
comma
multiline_comment|/* dest &amp;= ~src;        DPna,   GXandInverted,  0x4 */
l_int|0xAA
comma
multiline_comment|/* dest = dest;         D,      GXnoop,         0x5 */
l_int|0x5A
comma
multiline_comment|/* dest = ^src;         DPx,    GXxor,          0x6 */
l_int|0xFA
comma
multiline_comment|/* dest |= src;         DPo,    GXor,           0x7 */
l_int|0x05
comma
multiline_comment|/* dest = ~src &amp; ~dest; DPon,   GXnor,          0x8 */
l_int|0xA5
comma
multiline_comment|/* dest ^= ~src ;       DPxn,   GXequiv,        0x9 */
l_int|0x55
comma
multiline_comment|/* dest = ~dest;        Dn,     GXInvert,       0xA */
l_int|0xF5
comma
multiline_comment|/* dest = src|~dest ;   PDno,   GXorReverse,    0xB */
l_int|0x0F
comma
multiline_comment|/* dest = ~src;         Pn,     GXcopyInverted, 0xC */
l_int|0xAF
comma
multiline_comment|/* dest |= ~src;        DPno,   GXorInverted,   0xD */
l_int|0x5F
comma
multiline_comment|/* dest = ~src|~dest;   DPan,   GXnand,         0xE */
l_int|0xFF
comma
multiline_comment|/* dest = 0xFF;         1,      GXset,          0xF */
)brace
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,34)
DECL|variable|myrops
r_static
r_const
r_int
r_char
id|myrops
(braket
)braket
op_assign
(brace
l_int|3
comma
l_int|10
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* 300 series ----------------------------------------------------- */
macro_line|#ifdef CONFIG_FB_SIS_300
r_static
r_void
DECL|function|SiS300Sync
id|SiS300Sync
c_func
(paren
r_void
)paren
(brace
id|SiS300Idle
)brace
r_static
r_void
DECL|function|SiS300SetupForScreenToScreenCopy
id|SiS300SetupForScreenToScreenCopy
c_func
(paren
r_int
id|xdir
comma
r_int
id|ydir
comma
r_int
id|rop
comma
r_int
r_int
id|planemask
comma
r_int
id|trans_color
)paren
(brace
id|SiS300SetupDSTColorDepth
c_func
(paren
id|ivideo.DstColor
)paren
suffix:semicolon
id|SiS300SetupSRCPitch
c_func
(paren
id|ivideo.video_linelength
)paren
id|SiS300SetupDSTRect
c_func
(paren
id|ivideo.video_linelength
comma
op_minus
l_int|1
)paren
r_if
c_cond
(paren
id|trans_color
op_ne
op_minus
l_int|1
)paren
(brace
id|SiS300SetupROP
c_func
(paren
l_int|0x0A
)paren
id|SiS300SetupSRCTrans
c_func
(paren
id|trans_color
)paren
id|SiS300SetupCMDFlag
c_func
(paren
id|TRANSPARENT_BITBLT
)paren
)brace
r_else
(brace
id|SiS300SetupROP
c_func
(paren
id|sisALUConv
(braket
id|rop
)braket
)paren
)brace
r_if
c_cond
(paren
id|xdir
OG
l_int|0
)paren
(brace
id|SiS300SetupCMDFlag
c_func
(paren
id|X_INC
)paren
)brace
r_if
c_cond
(paren
id|ydir
OG
l_int|0
)paren
(brace
id|SiS300SetupCMDFlag
c_func
(paren
id|Y_INC
)paren
)brace
)brace
r_static
r_void
DECL|function|SiS300SubsequentScreenToScreenCopy
id|SiS300SubsequentScreenToScreenCopy
c_func
(paren
r_int
id|src_x
comma
r_int
id|src_y
comma
r_int
id|dst_x
comma
r_int
id|dst_y
comma
r_int
id|width
comma
r_int
id|height
)paren
(brace
r_int
id|srcbase
comma
id|dstbase
suffix:semicolon
id|srcbase
op_assign
id|dstbase
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|src_y
op_ge
l_int|2048
)paren
(brace
id|srcbase
op_assign
id|ivideo.video_linelength
op_star
id|src_y
suffix:semicolon
id|src_y
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dst_y
op_ge
l_int|2048
)paren
(brace
id|dstbase
op_assign
id|ivideo.video_linelength
op_star
id|dst_y
suffix:semicolon
id|dst_y
op_assign
l_int|0
suffix:semicolon
)brace
id|SiS300SetupSRCBase
c_func
(paren
id|srcbase
)paren
suffix:semicolon
id|SiS300SetupDSTBase
c_func
(paren
id|dstbase
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ivideo.CommandReg
op_amp
id|X_INC
)paren
)paren
(brace
id|src_x
op_add_assign
id|width
op_minus
l_int|1
suffix:semicolon
id|dst_x
op_add_assign
id|width
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ivideo.CommandReg
op_amp
id|Y_INC
)paren
)paren
(brace
id|src_y
op_add_assign
id|height
op_minus
l_int|1
suffix:semicolon
id|dst_y
op_add_assign
id|height
op_minus
l_int|1
suffix:semicolon
)brace
id|SiS300SetupRect
c_func
(paren
id|width
comma
id|height
)paren
id|SiS300SetupSRCXY
c_func
(paren
id|src_x
comma
id|src_y
)paren
id|SiS300SetupDSTXY
c_func
(paren
id|dst_x
comma
id|dst_y
)paren
id|SiS300DoCMD
)brace
r_static
r_void
DECL|function|SiS300SetupForSolidFill
id|SiS300SetupForSolidFill
c_func
(paren
r_int
id|color
comma
r_int
id|rop
comma
r_int
r_int
id|planemask
)paren
(brace
id|SiS300SetupPATFG
c_func
(paren
id|color
)paren
id|SiS300SetupDSTRect
c_func
(paren
id|ivideo.video_linelength
comma
op_minus
l_int|1
)paren
id|SiS300SetupDSTColorDepth
c_func
(paren
id|ivideo.DstColor
)paren
suffix:semicolon
id|SiS300SetupROP
c_func
(paren
id|sisPatALUConv
(braket
id|rop
)braket
)paren
id|SiS300SetupCMDFlag
c_func
(paren
id|PATFG
)paren
)brace
r_static
r_void
DECL|function|SiS300SubsequentSolidFillRect
id|SiS300SubsequentSolidFillRect
c_func
(paren
r_int
id|x
comma
r_int
id|y
comma
r_int
id|w
comma
r_int
id|h
)paren
(brace
r_int
id|dstbase
suffix:semicolon
id|dstbase
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|y
op_ge
l_int|2048
)paren
(brace
id|dstbase
op_assign
id|ivideo.video_linelength
op_star
id|y
suffix:semicolon
id|y
op_assign
l_int|0
suffix:semicolon
)brace
id|SiS300SetupDSTBase
c_func
(paren
id|dstbase
)paren
id|SiS300SetupDSTXY
c_func
(paren
id|x
comma
id|y
)paren
id|SiS300SetupRect
c_func
(paren
id|w
comma
id|h
)paren
id|SiS300SetupCMDFlag
c_func
(paren
id|X_INC
op_or
id|Y_INC
op_or
id|BITBLT
)paren
id|SiS300DoCMD
)brace
macro_line|#endif
multiline_comment|/* 315/330 series ------------------------------------------------- */
macro_line|#ifdef CONFIG_FB_SIS_315
r_static
r_void
DECL|function|SiS310Sync
id|SiS310Sync
c_func
(paren
r_void
)paren
(brace
id|SiS310Idle
)brace
r_static
r_void
DECL|function|SiS310SetupForScreenToScreenCopy
id|SiS310SetupForScreenToScreenCopy
c_func
(paren
r_int
id|xdir
comma
r_int
id|ydir
comma
r_int
id|rop
comma
r_int
r_int
id|planemask
comma
r_int
id|trans_color
)paren
(brace
id|SiS310SetupDSTColorDepth
c_func
(paren
id|ivideo.DstColor
)paren
suffix:semicolon
id|SiS310SetupSRCPitch
c_func
(paren
id|ivideo.video_linelength
)paren
id|SiS310SetupDSTRect
c_func
(paren
id|ivideo.video_linelength
comma
op_minus
l_int|1
)paren
r_if
c_cond
(paren
id|trans_color
op_ne
op_minus
l_int|1
)paren
(brace
id|SiS310SetupROP
c_func
(paren
l_int|0x0A
)paren
id|SiS310SetupSRCTrans
c_func
(paren
id|trans_color
)paren
id|SiS310SetupCMDFlag
c_func
(paren
id|TRANSPARENT_BITBLT
)paren
)brace
r_else
(brace
id|SiS310SetupROP
c_func
(paren
id|sisALUConv
(braket
id|rop
)braket
)paren
multiline_comment|/* Set command - not needed, both 0 */
multiline_comment|/* SiSSetupCMDFlag(BITBLT | SRCVIDEO) */
)brace
id|SiS310SetupCMDFlag
c_func
(paren
id|ivideo.SiS310_AccelDepth
)paren
multiline_comment|/* The 315 series is smart enough to know the direction */
)brace
r_static
r_void
DECL|function|SiS310SubsequentScreenToScreenCopy
id|SiS310SubsequentScreenToScreenCopy
c_func
(paren
r_int
id|src_x
comma
r_int
id|src_y
comma
r_int
id|dst_x
comma
r_int
id|dst_y
comma
r_int
id|width
comma
r_int
id|height
)paren
(brace
r_int
id|srcbase
comma
id|dstbase
suffix:semicolon
r_int
id|mymin
comma
id|mymax
suffix:semicolon
id|srcbase
op_assign
id|dstbase
op_assign
l_int|0
suffix:semicolon
id|mymin
op_assign
id|min
c_func
(paren
id|src_y
comma
id|dst_y
)paren
suffix:semicolon
id|mymax
op_assign
id|max
c_func
(paren
id|src_y
comma
id|dst_y
)paren
suffix:semicolon
multiline_comment|/* Although the chip knows the direction to use&n;&t; * if the source and destination areas overlap, &n;&t; * that logic fails if we fiddle with the bitmap&n;&t; * addresses. Therefore, we check if the source&n;&t; * and destination blitting areas overlap and &n;&t; * adapt the bitmap addresses synchronously &n;&t; * if the coordinates exceed the valid range.&n;&t; * The the areas do not overlap, we do our &n;&t; * normal check.&n;&t; */
r_if
c_cond
(paren
(paren
id|mymax
op_minus
id|mymin
)paren
OL
id|height
)paren
(brace
r_if
c_cond
(paren
(paren
id|src_y
op_ge
l_int|2048
)paren
op_logical_or
(paren
id|dst_y
op_ge
l_int|2048
)paren
)paren
(brace
id|srcbase
op_assign
id|ivideo.video_linelength
op_star
id|mymin
suffix:semicolon
id|dstbase
op_assign
id|ivideo.video_linelength
op_star
id|mymin
suffix:semicolon
id|src_y
op_sub_assign
id|mymin
suffix:semicolon
id|dst_y
op_sub_assign
id|mymin
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|src_y
op_ge
l_int|2048
)paren
(brace
id|srcbase
op_assign
id|ivideo.video_linelength
op_star
id|src_y
suffix:semicolon
id|src_y
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dst_y
op_ge
l_int|2048
)paren
(brace
id|dstbase
op_assign
id|ivideo.video_linelength
op_star
id|dst_y
suffix:semicolon
id|dst_y
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|SiS310SetupSRCBase
c_func
(paren
id|srcbase
)paren
suffix:semicolon
id|SiS310SetupDSTBase
c_func
(paren
id|dstbase
)paren
suffix:semicolon
id|SiS310SetupRect
c_func
(paren
id|width
comma
id|height
)paren
id|SiS310SetupSRCXY
c_func
(paren
id|src_x
comma
id|src_y
)paren
id|SiS310SetupDSTXY
c_func
(paren
id|dst_x
comma
id|dst_y
)paren
id|SiS310DoCMD
)brace
r_static
r_void
DECL|function|SiS310SetupForSolidFill
id|SiS310SetupForSolidFill
c_func
(paren
r_int
id|color
comma
r_int
id|rop
comma
r_int
r_int
id|planemask
)paren
(brace
id|SiS310SetupPATFG
c_func
(paren
id|color
)paren
id|SiS310SetupDSTRect
c_func
(paren
id|ivideo.video_linelength
comma
op_minus
l_int|1
)paren
id|SiS310SetupDSTColorDepth
c_func
(paren
id|ivideo.DstColor
)paren
suffix:semicolon
id|SiS310SetupROP
c_func
(paren
id|sisPatALUConv
(braket
id|rop
)braket
)paren
id|SiS310SetupCMDFlag
c_func
(paren
id|PATFG
op_or
id|ivideo.SiS310_AccelDepth
)paren
)brace
r_static
r_void
DECL|function|SiS310SubsequentSolidFillRect
id|SiS310SubsequentSolidFillRect
c_func
(paren
r_int
id|x
comma
r_int
id|y
comma
r_int
id|w
comma
r_int
id|h
)paren
(brace
r_int
id|dstbase
suffix:semicolon
id|dstbase
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|y
op_ge
l_int|2048
)paren
(brace
id|dstbase
op_assign
id|ivideo.video_linelength
op_star
id|y
suffix:semicolon
id|y
op_assign
l_int|0
suffix:semicolon
)brace
id|SiS310SetupDSTBase
c_func
(paren
id|dstbase
)paren
id|SiS310SetupDSTXY
c_func
(paren
id|x
comma
id|y
)paren
id|SiS310SetupRect
c_func
(paren
id|w
comma
id|h
)paren
id|SiS310SetupCMDFlag
c_func
(paren
id|BITBLT
)paren
id|SiS310DoCMD
)brace
macro_line|#endif
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/* The exported routines */
DECL|function|sisfb_initaccel
r_int
id|sisfb_initaccel
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef SISFB_USE_SPINLOCKS
id|spin_lock_init
c_func
(paren
op_amp
id|ivideo.lockaccel
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sisfb_syncaccel
r_void
id|sisfb_syncaccel
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|sisvga_engine
op_eq
id|SIS_300_VGA
)paren
(brace
macro_line|#ifdef CONFIG_FB_SIS_300
id|SiS300Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
macro_line|#ifdef CONFIG_FB_SIS_315
id|SiS310Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)  /* --------------- 2.5 --------------- */
DECL|function|fbcon_sis_sync
r_int
id|fbcon_sis_sync
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|CRITFLAGS
r_if
c_cond
(paren
op_logical_neg
id|ivideo.accel
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sisvga_engine
op_eq
id|SIS_300_VGA
)paren
(brace
macro_line|#ifdef CONFIG_FB_SIS_300
id|SiS300Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
macro_line|#ifdef CONFIG_FB_SIS_315
id|SiS310Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
id|CRITEND
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fbcon_sis_fillrect
r_void
id|fbcon_sis_fillrect
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_fillrect
op_star
id|rect
)paren
(brace
r_int
id|col
op_assign
l_int|0
suffix:semicolon
id|CRITFLAGS
id|TWDEBUG
c_func
(paren
l_string|&quot;Inside sis_fillrect&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rect-&gt;width
op_logical_or
op_logical_neg
id|rect-&gt;height
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ivideo.accel
)paren
(brace
id|cfb_fillrect
c_func
(paren
id|info
comma
id|rect
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|info-&gt;var.bits_per_pixel
)paren
(brace
r_case
l_int|8
suffix:colon
id|col
op_assign
id|rect-&gt;color
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|col
op_assign
(paren
(paren
id|u32
op_star
)paren
(paren
id|info-&gt;pseudo_palette
)paren
)paren
(braket
id|rect-&gt;color
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|col
op_assign
(paren
(paren
id|u32
op_star
)paren
(paren
id|info-&gt;pseudo_palette
)paren
)paren
(braket
id|rect-&gt;color
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sisvga_engine
op_eq
id|SIS_300_VGA
)paren
(brace
macro_line|#ifdef CONFIG_FB_SIS_300
id|CRITBEGIN
id|SiS300SetupForSolidFill
c_func
(paren
id|col
comma
id|myrops
(braket
id|rect-&gt;rop
)braket
comma
l_int|0
)paren
suffix:semicolon
id|SiS300SubsequentSolidFillRect
c_func
(paren
id|rect-&gt;dx
comma
id|rect-&gt;dy
comma
id|rect-&gt;width
comma
id|rect-&gt;height
)paren
suffix:semicolon
id|CRITEND
id|SiS300Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
macro_line|#ifdef CONFIG_FB_SIS_315
id|CRITBEGIN
id|SiS310SetupForSolidFill
c_func
(paren
id|col
comma
id|myrops
(braket
id|rect-&gt;rop
)braket
comma
l_int|0
)paren
suffix:semicolon
id|SiS310SubsequentSolidFillRect
c_func
(paren
id|rect-&gt;dx
comma
id|rect-&gt;dy
comma
id|rect-&gt;width
comma
id|rect-&gt;height
)paren
suffix:semicolon
id|CRITEND
id|SiS310Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|fbcon_sis_copyarea
r_void
id|fbcon_sis_copyarea
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_copyarea
op_star
id|area
)paren
(brace
r_int
id|xdir
comma
id|ydir
suffix:semicolon
id|CRITFLAGS
id|TWDEBUG
c_func
(paren
l_string|&quot;Inside sis_copyarea&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ivideo.accel
)paren
(brace
id|cfb_copyarea
c_func
(paren
id|info
comma
id|area
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|area-&gt;width
op_logical_or
op_logical_neg
id|area-&gt;height
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|area-&gt;sx
OL
id|area-&gt;dx
)paren
(brace
id|xdir
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|xdir
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|area-&gt;sy
OL
id|area-&gt;dy
)paren
(brace
id|ydir
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|ydir
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sisvga_engine
op_eq
id|SIS_300_VGA
)paren
(brace
macro_line|#ifdef CONFIG_FB_SIS_300
id|CRITBEGIN
id|SiS300SetupForScreenToScreenCopy
c_func
(paren
id|xdir
comma
id|ydir
comma
l_int|3
comma
l_int|0
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|SiS300SubsequentScreenToScreenCopy
c_func
(paren
id|area-&gt;sx
comma
id|area-&gt;sy
comma
id|area-&gt;dx
comma
id|area-&gt;dy
comma
id|area-&gt;width
comma
id|area-&gt;height
)paren
suffix:semicolon
id|CRITEND
id|SiS300Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
macro_line|#ifdef CONFIG_FB_SIS_315
id|CRITBEGIN
id|SiS310SetupForScreenToScreenCopy
c_func
(paren
id|xdir
comma
id|ydir
comma
l_int|3
comma
l_int|0
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|SiS310SubsequentScreenToScreenCopy
c_func
(paren
id|area-&gt;sx
comma
id|area-&gt;sy
comma
id|area-&gt;dx
comma
id|area-&gt;dy
comma
id|area-&gt;width
comma
id|area-&gt;height
)paren
suffix:semicolon
id|CRITEND
id|SiS310Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)  /* -------------- 2.4 --------------- */
DECL|function|fbcon_sis_bmove
r_void
id|fbcon_sis_bmove
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|srcy
comma
r_int
id|srcx
comma
r_int
id|dsty
comma
r_int
id|dstx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
r_int
id|xdir
comma
id|ydir
suffix:semicolon
id|CRITFLAGS
r_if
c_cond
(paren
op_logical_neg
id|ivideo.accel
)paren
(brace
r_switch
c_cond
(paren
id|ivideo.video_bpp
)paren
(brace
r_case
l_int|8
suffix:colon
macro_line|#ifdef FBCON_HAS_CFB8
id|fbcon_cfb8_bmove
c_func
(paren
id|p
comma
id|srcy
comma
id|srcx
comma
id|dsty
comma
id|dstx
comma
id|height
comma
id|width
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
macro_line|#ifdef FBCON_HAS_CFB16
id|fbcon_cfb16_bmove
c_func
(paren
id|p
comma
id|srcy
comma
id|srcx
comma
id|dsty
comma
id|dstx
comma
id|height
comma
id|width
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
macro_line|#ifdef FBCON_HAS_CFB32
id|fbcon_cfb32_bmove
c_func
(paren
id|p
comma
id|srcy
comma
id|srcx
comma
id|dsty
comma
id|dstx
comma
id|height
comma
id|width
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|srcx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|srcy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|dstx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|dsty
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
r_if
c_cond
(paren
id|srcx
OL
id|dstx
)paren
(brace
id|xdir
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|xdir
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|srcy
OL
id|dsty
)paren
(brace
id|ydir
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|ydir
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sisvga_engine
op_eq
id|SIS_300_VGA
)paren
(brace
macro_line|#ifdef CONFIG_FB_SIS_300
id|CRITBEGIN
id|SiS300SetupForScreenToScreenCopy
c_func
(paren
id|xdir
comma
id|ydir
comma
l_int|3
comma
l_int|0
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|SiS300SubsequentScreenToScreenCopy
c_func
(paren
id|srcx
comma
id|srcy
comma
id|dstx
comma
id|dsty
comma
id|width
comma
id|height
)paren
suffix:semicolon
id|CRITEND
id|SiS300Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
macro_line|#ifdef CONFIG_FB_SIS_315
id|CRITBEGIN
id|SiS310SetupForScreenToScreenCopy
c_func
(paren
id|xdir
comma
id|ydir
comma
l_int|3
comma
l_int|0
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|SiS310SubsequentScreenToScreenCopy
c_func
(paren
id|srcx
comma
id|srcy
comma
id|dstx
comma
id|dsty
comma
id|width
comma
id|height
)paren
suffix:semicolon
id|CRITEND
id|SiS310Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sis_bmove sx %d sy %d dx %d dy %d w %d h %d&bslash;n&quot;
comma
id|srcx
comma
id|srcy
comma
id|dstx
comma
id|dsty
comma
id|width
comma
id|height
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
)brace
)brace
DECL|function|fbcon_sis_clear
r_static
r_void
id|fbcon_sis_clear
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
id|srcy
comma
r_int
id|srcx
comma
r_int
id|height
comma
r_int
id|width
comma
r_int
id|color
)paren
(brace
id|CRITFLAGS
id|srcx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|srcy
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
r_if
c_cond
(paren
id|sisvga_engine
op_eq
id|SIS_300_VGA
)paren
(brace
macro_line|#ifdef CONFIG_FB_SIS_300
id|CRITBEGIN
id|SiS300SetupForSolidFill
c_func
(paren
id|color
comma
l_int|3
comma
l_int|0
)paren
suffix:semicolon
id|SiS300SubsequentSolidFillRect
c_func
(paren
id|srcx
comma
id|srcy
comma
id|width
comma
id|height
)paren
suffix:semicolon
id|CRITEND
id|SiS300Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
macro_line|#ifdef CONFIG_FB_SIS_315
id|CRITBEGIN
id|SiS310SetupForSolidFill
c_func
(paren
id|color
comma
l_int|3
comma
l_int|0
)paren
suffix:semicolon
id|SiS310SubsequentSolidFillRect
c_func
(paren
id|srcx
comma
id|srcy
comma
id|width
comma
id|height
)paren
suffix:semicolon
id|CRITEND
id|SiS310Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|fbcon_sis_clear8
r_void
id|fbcon_sis_clear8
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
id|srcy
comma
r_int
id|srcx
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
r_if
c_cond
(paren
op_logical_neg
id|ivideo.accel
)paren
(brace
macro_line|#ifdef FBCON_HAS_CFB8
id|fbcon_cfb8_clear
c_func
(paren
id|conp
comma
id|p
comma
id|srcy
comma
id|srcx
comma
id|height
comma
id|width
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
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
id|fbcon_sis_clear
c_func
(paren
id|conp
comma
id|p
comma
id|srcy
comma
id|srcx
comma
id|height
comma
id|width
comma
id|bgx
)paren
suffix:semicolon
)brace
DECL|function|fbcon_sis_clear16
r_void
id|fbcon_sis_clear16
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
id|srcy
comma
r_int
id|srcx
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
r_if
c_cond
(paren
op_logical_neg
id|ivideo.accel
)paren
(brace
macro_line|#ifdef FBCON_HAS_CFB16
id|fbcon_cfb16_clear
c_func
(paren
id|conp
comma
id|p
comma
id|srcy
comma
id|srcx
comma
id|height
comma
id|width
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
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
id|fbcon_sis_clear
c_func
(paren
id|conp
comma
id|p
comma
id|srcy
comma
id|srcx
comma
id|height
comma
id|width
comma
id|bgx
)paren
suffix:semicolon
)brace
DECL|function|fbcon_sis_clear32
r_void
id|fbcon_sis_clear32
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
id|srcy
comma
r_int
id|srcx
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
r_if
c_cond
(paren
op_logical_neg
id|ivideo.accel
)paren
(brace
macro_line|#ifdef FBCON_HAS_CFB32
id|fbcon_cfb32_clear
c_func
(paren
id|conp
comma
id|p
comma
id|srcy
comma
id|srcx
comma
id|height
comma
id|width
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
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
id|fbcon_sis_clear
c_func
(paren
id|conp
comma
id|p
comma
id|srcy
comma
id|srcx
comma
id|height
comma
id|width
comma
id|bgx
)paren
suffix:semicolon
)brace
DECL|function|fbcon_sis_revc
r_void
id|fbcon_sis_revc
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|srcx
comma
r_int
id|srcy
)paren
(brace
id|CRITFLAGS
r_if
c_cond
(paren
op_logical_neg
id|ivideo.accel
)paren
(brace
r_switch
c_cond
(paren
id|ivideo.video_bpp
)paren
(brace
r_case
l_int|16
suffix:colon
macro_line|#ifdef FBCON_HAS_CFB16
id|fbcon_cfb16_revc
c_func
(paren
id|p
comma
id|srcx
comma
id|srcy
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
macro_line|#ifdef FBCON_HAS_CFB32
id|fbcon_cfb32_revc
c_func
(paren
id|p
comma
id|srcx
comma
id|srcy
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|srcx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|srcy
op_mul_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sisvga_engine
op_eq
id|SIS_300_VGA
)paren
(brace
macro_line|#ifdef CONFIG_FB_SIS_300
id|CRITBEGIN
id|SiS300SetupForSolidFill
c_func
(paren
l_int|0
comma
l_int|0x0a
comma
l_int|0
)paren
suffix:semicolon
id|SiS300SubsequentSolidFillRect
c_func
(paren
id|srcx
comma
id|srcy
comma
id|fontwidth
c_func
(paren
id|p
)paren
comma
id|fontheight
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
id|CRITEND
id|SiS300Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
macro_line|#ifdef CONFIG_FB_SIS_315
id|CRITBEGIN
id|SiS310SetupForSolidFill
c_func
(paren
l_int|0
comma
l_int|0x0a
comma
l_int|0
)paren
suffix:semicolon
id|SiS310SubsequentSolidFillRect
c_func
(paren
id|srcx
comma
id|srcy
comma
id|fontwidth
c_func
(paren
id|p
)paren
comma
id|fontheight
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
id|CRITEND
id|SiS310Sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
macro_line|#ifdef FBCON_HAS_CFB8
DECL|variable|fbcon_sis8
r_struct
id|display_switch
id|fbcon_sis8
op_assign
(brace
dot
id|setup
op_assign
id|fbcon_cfb8_setup
comma
dot
id|bmove
op_assign
id|fbcon_sis_bmove
comma
dot
id|clear
op_assign
id|fbcon_sis_clear8
comma
dot
id|putc
op_assign
id|fbcon_cfb8_putc
comma
dot
id|putcs
op_assign
id|fbcon_cfb8_putcs
comma
dot
id|revc
op_assign
id|fbcon_cfb8_revc
comma
dot
id|clear_margins
op_assign
id|fbcon_cfb8_clear_margins
comma
dot
id|fontwidthmask
op_assign
id|FONTWIDTH
c_func
(paren
l_int|4
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|8
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|12
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|16
)paren
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB16
DECL|variable|fbcon_sis16
r_struct
id|display_switch
id|fbcon_sis16
op_assign
(brace
dot
id|setup
op_assign
id|fbcon_cfb16_setup
comma
dot
id|bmove
op_assign
id|fbcon_sis_bmove
comma
dot
id|clear
op_assign
id|fbcon_sis_clear16
comma
dot
id|putc
op_assign
id|fbcon_cfb16_putc
comma
dot
id|putcs
op_assign
id|fbcon_cfb16_putcs
comma
dot
id|revc
op_assign
id|fbcon_sis_revc
comma
dot
id|clear_margins
op_assign
id|fbcon_cfb16_clear_margins
comma
dot
id|fontwidthmask
op_assign
id|FONTWIDTH
c_func
(paren
l_int|4
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|8
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|12
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|16
)paren
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
DECL|variable|fbcon_sis32
r_struct
id|display_switch
id|fbcon_sis32
op_assign
(brace
dot
id|setup
op_assign
id|fbcon_cfb32_setup
comma
dot
id|bmove
op_assign
id|fbcon_sis_bmove
comma
dot
id|clear
op_assign
id|fbcon_sis_clear32
comma
dot
id|putc
op_assign
id|fbcon_cfb32_putc
comma
dot
id|putcs
op_assign
id|fbcon_cfb32_putcs
comma
dot
id|revc
op_assign
id|fbcon_sis_revc
comma
dot
id|clear_margins
op_assign
id|fbcon_cfb32_clear_margins
comma
dot
id|fontwidthmask
op_assign
id|FONTWIDTH
c_func
(paren
l_int|4
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|8
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|12
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|16
)paren
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif /* KERNEL VERSION */
eof
