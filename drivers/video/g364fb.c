multiline_comment|/* $Id: g364fb.c,v 1.3 1998/08/28 22:43:00 tsbogend Exp $&n; *&n; * linux/drivers/video/g364fb.c -- Mips Magnum frame buffer device&n; *&n; * (C) 1998 Thomas Bogendoerfer&n; *&n; *  This driver is based on tgafb.c&n; *&n; *&t;Copyright (C) 1997 Geert Uytterhoeven &n; *&t;Copyright (C) 1995  Jay Estabrook&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
multiline_comment|/* &n; * Various defines for the G364&n; */
DECL|macro|G364_MEM_BASE
mdefine_line|#define G364_MEM_BASE   0xe4400000
DECL|macro|G364_PORT_BASE
mdefine_line|#define G364_PORT_BASE  0xe4000000
DECL|macro|ID_REG
mdefine_line|#define ID_REG &t;&t;0xe4000000&t;/* Read only */
DECL|macro|BOOT_REG
mdefine_line|#define BOOT_REG &t;0xe4080000
DECL|macro|TIMING_REG
mdefine_line|#define TIMING_REG &t;0xe4080108&t;/* to 0x080170 - DON&squot;T TOUCH! */
DECL|macro|DISPLAY_REG
mdefine_line|#define DISPLAY_REG &t;0xe4080118
DECL|macro|VDISPLAY_REG
mdefine_line|#define VDISPLAY_REG &t;0xe4080150
DECL|macro|MASK_REG
mdefine_line|#define MASK_REG &t;0xe4080200
DECL|macro|CTLA_REG
mdefine_line|#define CTLA_REG &t;0xe4080300
DECL|macro|CURS_TOGGLE
mdefine_line|#define CURS_TOGGLE &t;0x800000
DECL|macro|BIT_PER_PIX
mdefine_line|#define BIT_PER_PIX&t;0x700000&t;/* bits 22 to 20 of Control A */
DECL|macro|DELAY_SAMPLE
mdefine_line|#define DELAY_SAMPLE    0x080000
DECL|macro|PORT_INTER
mdefine_line|#define PORT_INTER&t;0x040000
DECL|macro|PIX_PIPE_DEL
mdefine_line|#define PIX_PIPE_DEL&t;0x030000&t;/* bits 17 and 16 of Control A */
DECL|macro|PIX_PIPE_DEL2
mdefine_line|#define PIX_PIPE_DEL2&t;0x008000&t;/* same as above - don&squot;t ask me why */
DECL|macro|TR_CYCLE_TOG
mdefine_line|#define TR_CYCLE_TOG&t;0x004000
DECL|macro|VRAM_ADR_INC
mdefine_line|#define VRAM_ADR_INC&t;0x003000&t;/* bits 13 and 12 of Control A */
DECL|macro|BLANK_OFF
mdefine_line|#define BLANK_OFF&t;0x000800
DECL|macro|FORCE_BLANK
mdefine_line|#define FORCE_BLANK&t;0x000400
DECL|macro|BLK_FUN_SWTCH
mdefine_line|#define BLK_FUN_SWTCH&t;0x000200
DECL|macro|BLANK_IO
mdefine_line|#define BLANK_IO&t;0x000100
DECL|macro|BLANK_LEVEL
mdefine_line|#define BLANK_LEVEL&t;0x000080
DECL|macro|A_VID_FORM
mdefine_line|#define A_VID_FORM&t;0x000040
DECL|macro|D_SYNC_FORM
mdefine_line|#define D_SYNC_FORM&t;0x000020
DECL|macro|FRAME_FLY_PAT
mdefine_line|#define FRAME_FLY_PAT&t;0x000010
DECL|macro|OP_MODE
mdefine_line|#define OP_MODE&t;&t;0x000008
DECL|macro|INTL_STAND
mdefine_line|#define INTL_STAND&t;0x000004
DECL|macro|SCRN_FORM
mdefine_line|#define SCRN_FORM&t;0x000002
DECL|macro|ENABLE_VTG
mdefine_line|#define ENABLE_VTG&t;0x000001
DECL|macro|TOP_REG
mdefine_line|#define TOP_REG &t;0xe4080400
DECL|macro|CURS_PAL_REG
mdefine_line|#define CURS_PAL_REG &t;0xe4080508&t;/* to 0x080518 */
DECL|macro|CHKSUM_REG
mdefine_line|#define CHKSUM_REG &t;0xe4080600&t;/* to 0x080610 - unused */
DECL|macro|CURS_POS_REG
mdefine_line|#define CURS_POS_REG &t;0xe4080638
DECL|macro|CLR_PAL_REG
mdefine_line|#define CLR_PAL_REG &t;0xe4080800&t;/* to 0x080ff8 */
DECL|macro|CURS_PAT_REG
mdefine_line|#define CURS_PAT_REG &t;0xe4081000&t;/* to 0x081ff8 */
DECL|macro|MON_ID_REG
mdefine_line|#define MON_ID_REG &t;0xe4100000&t;/* unused */
DECL|macro|RESET_REG
mdefine_line|#define RESET_REG &t;0xe4180000&t;/* Write only */
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|fb_fix_screeninfo
id|fb_fix
id|__initdata
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;G364 8plane&quot;
comma
dot
id|smem_start
op_assign
l_int|0x40000000
comma
multiline_comment|/* physical address */
dot
id|type
op_assign
id|FB_TYPE_PACKED_PIXELS
comma
dot
id|visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
comma
dot
id|ypanstep
op_assign
l_int|1
comma
dot
id|accel
op_assign
id|FB_ACCEL_NONE
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|fb_var_screeninfo
id|fb_var
id|__initdata
op_assign
(brace
dot
id|bits_per_pixel
op_assign
l_int|8
comma
dot
id|red
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
id|green
suffix:colon
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
id|blue
suffix:colon
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
id|activate
suffix:colon
id|FB_ACTIVATE_NOW
comma
id|height
suffix:colon
op_minus
l_int|1
comma
id|width
suffix:colon
op_minus
l_int|1
comma
id|pixclock
suffix:colon
l_int|39722
comma
id|left_margin
suffix:colon
l_int|40
comma
id|right_margin
suffix:colon
l_int|24
comma
id|upper_margin
suffix:colon
l_int|32
comma
id|lower_margin
suffix:colon
l_int|11
comma
id|hsync_len
suffix:colon
l_int|96
comma
id|vsync_len
suffix:colon
l_int|2
comma
id|vmode
suffix:colon
id|FB_VMODE_NONINTERLACED
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *  Interface used by the world&n; */
r_int
id|g364fb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|g364fb_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|g364fb_setcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
id|red
comma
id|u_int
id|green
comma
id|u_int
id|blue
comma
id|u_int
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|g364fb_cursor
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_cursor
op_star
id|cursor
)paren
suffix:semicolon
r_static
r_int
id|g364fb_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
DECL|variable|g364fb_ops
r_static
r_struct
id|fb_ops
id|g364fb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_setcolreg
op_assign
id|g364fb_setcolreg
comma
dot
id|fb_pan_display
op_assign
id|g364fb_pan_display
comma
dot
id|fb_blank
op_assign
id|g364fb_blank
comma
dot
id|fb_fillrect
op_assign
id|cfb_fillrect
comma
dot
id|fb_copyarea
op_assign
id|cfb_copyarea
comma
dot
id|fb_imageblit
op_assign
id|cfb_imageblit
comma
dot
id|fb_cursor
op_assign
id|g364fb_cursor
comma
)brace
suffix:semicolon
DECL|function|g364fb_cursor
r_int
id|g364fb_cursor
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_cursor
op_star
id|cursor
)paren
(brace
r_switch
c_cond
(paren
id|cursor-&gt;enable
)paren
(brace
r_case
id|CM_ERASE
suffix:colon
op_star
(paren
r_int
r_int
op_star
)paren
id|CTLA_REG
op_or_assign
id|CURS_TOGGLE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CM_MOVE
suffix:colon
r_case
id|CM_DRAW
suffix:colon
op_star
(paren
r_int
r_int
op_star
)paren
id|CTLA_REG
op_and_assign
op_complement
id|CURS_TOGGLE
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|CURS_POS_REG
op_assign
(paren
(paren
id|x
op_star
id|fontwidth
c_func
(paren
id|p
)paren
)paren
op_lshift
l_int|12
)paren
op_or
(paren
(paren
id|y
op_star
id|fontheight
c_func
(paren
id|p
)paren
)paren
op_minus
id|info-&gt;var.yoffset
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Pan or Wrap the Display&n; *&n; *  This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag&n; */
DECL|function|g364fb_pan_display
r_static
r_int
id|g364fb_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|var-&gt;xoffset
op_logical_or
id|var-&gt;yoffset
op_plus
id|var-&gt;yres
OG
id|var-&gt;yres_virtual
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|TOP_REG
op_assign
id|var-&gt;yoffset
op_star
id|var-&gt;xres
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Blank the display.&n; */
DECL|function|g364fb_blank
r_static
r_int
id|g364fb_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|blank
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|CTLA_REG
op_or_assign
id|FORCE_BLANK
suffix:semicolon
r_else
op_star
(paren
r_int
r_int
op_star
)paren
id|CTLA_REG
op_and_assign
op_complement
id|FORCE_BLANK
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Set a single color register. Return != 0 for invalid regno.&n; */
DECL|function|g364fb_setcolreg
r_static
r_int
id|g364fb_setcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
id|red
comma
id|u_int
id|green
comma
id|u_int
id|blue
comma
id|u_int
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ptr
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|CLR_PAL_REG
suffix:semicolon
r_if
c_cond
(paren
id|regno
OG
l_int|255
)paren
r_return
l_int|1
suffix:semicolon
id|red
op_rshift_assign
l_int|8
suffix:semicolon
id|green
op_rshift_assign
l_int|8
suffix:semicolon
id|blue
op_rshift_assign
l_int|8
suffix:semicolon
id|ptr
(braket
id|regno
op_lshift
l_int|1
)braket
op_assign
(paren
id|red
op_lshift
l_int|16
)paren
op_or
(paren
id|green
op_lshift
l_int|8
)paren
op_or
id|blue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Initialisation&n; */
DECL|function|g364fb_init
r_int
id|__init
id|g364fb_init
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
op_star
id|pal_ptr
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|CLR_PAL_REG
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|curs_pal_ptr
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|CURS_PAL_REG
suffix:semicolon
r_int
id|mem
comma
id|i
comma
id|j
suffix:semicolon
multiline_comment|/* TBD: G364 detection */
multiline_comment|/* get the resolution set by ARC console */
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|CTLA_REG
op_and_assign
op_complement
id|ENABLE_VTG
suffix:semicolon
id|fb_var.xres
op_assign
(paren
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|DISPLAY_REG
)paren
op_amp
l_int|0x00ffffff
)paren
op_star
l_int|4
suffix:semicolon
id|fb_var.yres
op_assign
(paren
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|VDISPLAY_REG
)paren
op_amp
l_int|0x00ffffff
)paren
op_div
l_int|2
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|CTLA_REG
op_or_assign
id|ENABLE_VTG
suffix:semicolon
multiline_comment|/* setup cursor */
id|curs_pal_ptr
(braket
l_int|0
)braket
op_or_assign
l_int|0x00ffffff
suffix:semicolon
id|curs_pal_ptr
(braket
l_int|2
)braket
op_or_assign
l_int|0x00ffffff
suffix:semicolon
id|curs_pal_ptr
(braket
l_int|4
)braket
op_or_assign
l_int|0x00ffffff
suffix:semicolon
multiline_comment|/*&n;&t; * first set the whole cursor to transparent&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|512
suffix:semicolon
id|i
op_increment
)paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|CURS_PAT_REG
op_plus
id|i
op_star
l_int|8
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * switch the last two lines to cursor palette 3&n;&t; * we assume here, that FONTSIZE_X is 8&n;&t; */
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|CURS_PAT_REG
op_plus
l_int|14
op_star
l_int|64
)paren
op_assign
l_int|0xffff
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|CURS_PAT_REG
op_plus
l_int|15
op_star
l_int|64
)paren
op_assign
l_int|0xffff
suffix:semicolon
id|fb_var.xres_virtual
op_assign
id|fbvar.xres
suffix:semicolon
id|fb_fix.line_length
op_assign
(paren
id|xres
op_div
l_int|8
)paren
op_star
id|fb_var.bits_per_pixel
suffix:semicolon
id|fb_fix.smem_start
op_assign
l_int|0x40000000
suffix:semicolon
multiline_comment|/* physical address */
multiline_comment|/* get size of video memory; this is special for the JAZZ hardware */
id|mem
op_assign
(paren
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CONFIG
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|3
suffix:semicolon
id|fb_fix.smem_len
op_assign
(paren
l_int|1
op_lshift
(paren
id|mem
op_star
l_int|2
)paren
)paren
op_star
l_int|512
op_star
l_int|1024
suffix:semicolon
id|fb_var.yres_virtual
op_assign
id|fb_fix.smem_len
op_div
id|fb_var.xres
suffix:semicolon
id|fb_info.node
op_assign
id|NODEV
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|g364fb_ops
suffix:semicolon
id|fb_info.screen_base
op_assign
(paren
r_char
op_star
)paren
id|G364_MEM_BASE
suffix:semicolon
multiline_comment|/* virtual kernel address */
id|fb_info.var
op_assign
id|fb_var
suffix:semicolon
id|fb_info.fix
op_assign
id|fb_fix
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb_info.cmap
comma
l_int|255
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
