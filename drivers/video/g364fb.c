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
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
multiline_comment|/* &n; * Various defines for the G364&n; */
DECL|macro|G364_MEM_BASE
mdefine_line|#define G364_MEM_BASE   0xe4400000
DECL|macro|G364_PORT_BASE
mdefine_line|#define G364_PORT_BASE  0xe4000000
DECL|macro|ID_REG
mdefine_line|#define ID_REG &t;&t;0xe4000000  &t;/* Read only */
DECL|macro|BOOT_REG
mdefine_line|#define BOOT_REG &t;0xe4080000
DECL|macro|TIMING_REG
mdefine_line|#define TIMING_REG &t;0xe4080108 &t;/* to 0x080170 - DON&squot;T TOUCH! */
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
mdefine_line|#define ENABLE_VTG&t;0x000001&t;
DECL|macro|TOP_REG
mdefine_line|#define TOP_REG &t;0xe4080400
DECL|macro|CURS_PAL_REG
mdefine_line|#define CURS_PAL_REG &t;0xe4080508 &t;/* to 0x080518 */
DECL|macro|CHKSUM_REG
mdefine_line|#define CHKSUM_REG &t;0xe4080600 &t;/* to 0x080610 - unused */
DECL|macro|CURS_POS_REG
mdefine_line|#define CURS_POS_REG &t;0xe4080638
DECL|macro|CLR_PAL_REG
mdefine_line|#define CLR_PAL_REG &t;0xe4080800&t;/* to 0x080ff8 */
DECL|macro|CURS_PAT_REG
mdefine_line|#define CURS_PAT_REG &t;0xe4081000&t;/* to 0x081ff8 */
DECL|macro|MON_ID_REG
mdefine_line|#define MON_ID_REG &t;0xe4100000 &t;/* unused */
DECL|macro|RESET_REG
mdefine_line|#define RESET_REG &t;0xe4180000  &t;/* Write only */
DECL|variable|currcon
r_static
r_int
id|currcon
op_assign
l_int|0
suffix:semicolon
DECL|variable|disp
r_static
r_struct
id|display
id|disp
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|member|red
DECL|member|green
DECL|member|blue
DECL|member|pad
DECL|variable|palette
r_static
r_struct
(brace
id|u_char
id|red
comma
id|green
comma
id|blue
comma
id|pad
suffix:semicolon
)brace
id|palette
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|fb_fix
r_static
r_struct
id|fb_fix_screeninfo
id|fb_fix
op_assign
(brace
(brace
l_string|&quot;G364 8plane&quot;
comma
)brace
)brace
suffix:semicolon
DECL|variable|fb_var
r_static
r_struct
id|fb_var_screeninfo
id|fb_var
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *  Interface used by the world&n; */
r_static
r_int
id|g364fb_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|g364fb_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|g364fb_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
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
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|g364fb_get_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|g364fb_set_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n; *  Interface to the low level console driver&n; */
r_int
id|g364fb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|g364fbcon_switch
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|g364fbcon_updatevar
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_void
id|g364fbcon_blank
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
multiline_comment|/*&n; *  Internal routines&n; */
r_static
r_int
id|g364fb_getcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
op_star
id|red
comma
id|u_int
op_star
id|green
comma
id|u_int
op_star
id|blue
comma
id|u_int
op_star
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
r_void
id|do_install_cmap
c_func
(paren
r_int
id|con
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
id|owner
suffix:colon
id|THIS_MODULE
comma
id|fb_get_fix
suffix:colon
id|g364fb_get_fix
comma
id|fb_get_var
suffix:colon
id|g364fb_get_var
comma
id|fb_set_var
suffix:colon
id|g364fb_set_var
comma
id|fb_get_cmap
suffix:colon
id|g364fb_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|g364fb_set_cmap
comma
id|fb_pan_display
suffix:colon
id|g364fb_pan_display
comma
)brace
suffix:semicolon
DECL|function|fbcon_g364fb_cursor
r_void
id|fbcon_g364fb_cursor
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|mode
comma
r_int
id|x
comma
r_int
id|y
)paren
(brace
r_switch
c_cond
(paren
id|mode
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
id|p-&gt;var.yoffset
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|variable|fbcon_g364cfb8
r_static
r_struct
id|display_switch
id|fbcon_g364cfb8
op_assign
(brace
id|setup
suffix:colon
id|fbcon_cfb8_setup
comma
id|bmove
suffix:colon
id|fbcon_cfb8_bmove
comma
id|clear
suffix:colon
id|fbcon_cfb8_clear
comma
id|putc
suffix:colon
id|fbcon_cfb8_putc
comma
id|putcs
suffix:colon
id|fbcon_cfb8_putcs
comma
id|revc
suffix:colon
id|fbcon_cfb8_revc
comma
id|cursor
suffix:colon
id|fbcon_g364fb_cursor
comma
id|clear_margins
suffix:colon
id|fbcon_cfb8_clear_margins
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
multiline_comment|/*&n; *  Get the Fixed Part of the Display&n; */
DECL|function|g364fb_get_fix
r_static
r_int
id|g364fb_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|memcpy
c_func
(paren
id|fix
comma
op_amp
id|fb_fix
comma
r_sizeof
(paren
id|fb_fix
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Get the User Defined Part of the Display&n; */
DECL|function|g364fb_get_var
r_static
r_int
id|g364fb_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|memcpy
c_func
(paren
id|var
comma
op_amp
id|fb_var
comma
r_sizeof
(paren
id|fb_var
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Set the User Defined Part of the Display&n; */
DECL|function|g364fb_set_var
r_static
r_int
id|g364fb_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|display
op_star
id|display
suffix:semicolon
r_int
id|oldbpp
op_assign
op_minus
l_int|1
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
id|con
op_ge
l_int|0
)paren
id|display
op_assign
op_amp
id|fb_display
(braket
id|con
)braket
suffix:semicolon
r_else
id|display
op_assign
op_amp
id|disp
suffix:semicolon
multiline_comment|/* used during initialization */
r_if
c_cond
(paren
id|var-&gt;xres
OG
id|fb_var.xres
op_logical_or
id|var-&gt;yres
OG
id|fb_var.yres
op_logical_or
id|var-&gt;xres_virtual
OG
id|fb_var.xres_virtual
op_logical_or
id|var-&gt;yres_virtual
OG
id|fb_var.yres_virtual
op_logical_or
id|var-&gt;bits_per_pixel
OG
id|fb_var.bits_per_pixel
op_logical_or
id|var-&gt;nonstd
op_logical_or
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_MASK
)paren
op_ne
id|FB_VMODE_NONINTERLACED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy
c_func
(paren
id|var
comma
op_amp
id|fb_var
comma
r_sizeof
(paren
id|fb_var
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|var-&gt;activate
op_amp
id|FB_ACTIVATE_MASK
)paren
op_eq
id|FB_ACTIVATE_NOW
)paren
(brace
id|oldbpp
op_assign
id|display-&gt;var.bits_per_pixel
suffix:semicolon
id|display-&gt;var
op_assign
op_star
id|var
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
)brace
r_if
c_cond
(paren
id|oldbpp
op_ne
id|var-&gt;bits_per_pixel
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fb_alloc_cmap
c_func
(paren
op_amp
id|display-&gt;cmap
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|do_install_cmap
c_func
(paren
id|con
comma
id|info
)paren
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
r_int
id|con
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
multiline_comment|/*&n; *  Get the Colormap&n; */
DECL|function|g364fb_get_cmap
r_static
r_int
id|g364fb_get_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
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
id|con
op_eq
id|currcon
)paren
multiline_comment|/* current console? */
r_return
id|fb_get_cmap
c_func
(paren
id|cmap
comma
id|kspc
comma
id|g364fb_getcolreg
comma
id|info
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
multiline_comment|/* non default colormap? */
id|fb_copy_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
r_else
id|fb_copy_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
l_int|1
op_lshift
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
)paren
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Set the Colormap&n; */
DECL|function|g364fb_set_cmap
r_static
r_int
id|g364fb_set_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
(brace
multiline_comment|/* no colormap allocated? */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
l_int|1
op_lshift
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
comma
l_int|0
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|con
op_eq
id|currcon
)paren
(brace
multiline_comment|/* current console? */
r_return
id|fb_set_cmap
c_func
(paren
id|cmap
comma
id|kspc
comma
id|g364fb_setcolreg
comma
id|info
)paren
suffix:semicolon
)brace
r_else
id|fb_copy_cmap
c_func
(paren
id|cmap
comma
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
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
r_int
id|i
comma
id|j
suffix:semicolon
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
r_int
id|xres
comma
id|yres
suffix:semicolon
r_int
id|mem
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
id|xres
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
id|yres
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
multiline_comment|/* initialise color palette */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
id|color_table
(braket
id|i
)braket
suffix:semicolon
id|palette
(braket
id|i
)braket
dot
id|red
op_assign
id|default_red
(braket
id|j
)braket
suffix:semicolon
id|palette
(braket
id|i
)braket
dot
id|green
op_assign
id|default_grn
(braket
id|j
)braket
suffix:semicolon
id|palette
(braket
id|i
)braket
dot
id|blue
op_assign
id|default_blu
(braket
id|j
)braket
suffix:semicolon
id|pal_ptr
(braket
id|i
op_lshift
l_int|1
)braket
op_assign
(paren
id|palette
(braket
id|i
)braket
dot
id|red
op_lshift
l_int|16
)paren
op_or
(paren
id|palette
(braket
id|i
)braket
dot
id|green
op_lshift
l_int|8
)paren
op_or
id|palette
(braket
id|i
)braket
dot
id|blue
suffix:semicolon
)brace
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
multiline_comment|/*&n;     * first set the whole cursor to transparent&n;     */
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
multiline_comment|/*&n;     * switch the last two lines to cursor palette 3&n;     * we assume here, that FONTSIZE_X is 8&n;     */
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
id|fb_var.bits_per_pixel
op_assign
l_int|8
suffix:semicolon
id|fb_var.xres
op_assign
id|fb_var.xres_virtual
op_assign
id|xres
suffix:semicolon
id|fb_var.yres
op_assign
id|yres
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
id|fb_fix.type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fb_fix.type_aux
op_assign
l_int|0
suffix:semicolon
id|fb_fix.visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
id|fb_fix.xpanstep
op_assign
l_int|0
suffix:semicolon
id|fb_fix.ypanstep
op_assign
l_int|1
suffix:semicolon
id|fb_fix.ywrapstep
op_assign
l_int|0
suffix:semicolon
id|fb_fix.mmio_start
op_assign
l_int|0
suffix:semicolon
id|fb_fix.mmio_len
op_assign
l_int|0
suffix:semicolon
id|fb_fix.accel
op_assign
id|FB_ACCEL_NONE
suffix:semicolon
id|fb_var.yres_virtual
op_assign
id|fb_fix.smem_len
op_div
id|xres
suffix:semicolon
id|fb_var.xoffset
op_assign
id|fb_var.yoffset
op_assign
l_int|0
suffix:semicolon
id|fb_var.grayscale
op_assign
l_int|0
suffix:semicolon
id|fb_var.red.offset
op_assign
l_int|0
suffix:semicolon
id|fb_var.green.offset
op_assign
l_int|0
suffix:semicolon
id|fb_var.blue.offset
op_assign
l_int|0
suffix:semicolon
id|fb_var.red.length
op_assign
id|fb_var.green.length
op_assign
id|fb_var.blue.length
op_assign
l_int|8
suffix:semicolon
id|fb_var.red.msb_right
op_assign
id|fb_var.green.msb_right
op_assign
id|fb_var.blue.msb_right
op_assign
l_int|0
suffix:semicolon
id|fb_var.transp.offset
op_assign
id|fb_var.transp.length
op_assign
id|fb_var.transp.msb_right
op_assign
l_int|0
suffix:semicolon
id|fb_var.nonstd
op_assign
l_int|0
suffix:semicolon
id|fb_var.activate
op_assign
l_int|0
suffix:semicolon
id|fb_var.height
op_assign
id|fb_var.width
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_var.accel_flags
op_assign
l_int|0
suffix:semicolon
id|fb_var.pixclock
op_assign
l_int|39722
suffix:semicolon
id|fb_var.left_margin
op_assign
l_int|40
suffix:semicolon
id|fb_var.right_margin
op_assign
l_int|24
suffix:semicolon
id|fb_var.upper_margin
op_assign
l_int|32
suffix:semicolon
id|fb_var.lower_margin
op_assign
l_int|11
suffix:semicolon
id|fb_var.hsync_len
op_assign
l_int|96
suffix:semicolon
id|fb_var.vsync_len
op_assign
l_int|2
suffix:semicolon
id|fb_var.sync
op_assign
l_int|0
suffix:semicolon
id|fb_var.vmode
op_assign
id|FB_VMODE_NONINTERLACED
suffix:semicolon
id|disp.var
op_assign
id|fb_var
suffix:semicolon
id|disp.cmap.start
op_assign
l_int|0
suffix:semicolon
id|disp.cmap.len
op_assign
l_int|0
suffix:semicolon
id|disp.cmap.red
op_assign
id|disp.cmap.green
op_assign
id|disp.cmap.blue
op_assign
id|disp.cmap.transp
op_assign
l_int|NULL
suffix:semicolon
id|disp.screen_base
op_assign
(paren
r_char
op_star
)paren
id|G364_MEM_BASE
suffix:semicolon
multiline_comment|/* virtual kernel address */
id|disp.visual
op_assign
id|fb_fix.visual
suffix:semicolon
id|disp.type
op_assign
id|fb_fix.type
suffix:semicolon
id|disp.type_aux
op_assign
id|fb_fix.type_aux
suffix:semicolon
id|disp.ypanstep
op_assign
id|fb_fix.ypanstep
suffix:semicolon
id|disp.ywrapstep
op_assign
id|fb_fix.ywrapstep
suffix:semicolon
id|disp.line_length
op_assign
id|fb_fix.line_length
suffix:semicolon
id|disp.can_soft_blank
op_assign
l_int|1
suffix:semicolon
id|disp.inverse
op_assign
l_int|0
suffix:semicolon
id|disp.dispsw
op_assign
op_amp
id|fbcon_g364cfb8
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_info.modename
comma
id|fb_fix.id
)paren
suffix:semicolon
id|fb_info.node
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|g364fb_ops
suffix:semicolon
id|fb_info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.fontname
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|fb_info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.switch_con
op_assign
op_amp
id|g364fbcon_switch
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|g364fbcon_updatevar
suffix:semicolon
id|fb_info.blank
op_assign
op_amp
id|g364fbcon_blank
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|g364fb_set_var
c_func
(paren
op_amp
id|fb_var
comma
op_minus
l_int|1
comma
op_amp
id|fb_info
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
id|printk
c_func
(paren
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.node
)paren
comma
id|fb_fix.id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|g364fbcon_switch
r_static
r_int
id|g364fbcon_switch
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/* Do we have to save the colormap? */
r_if
c_cond
(paren
id|fb_display
(braket
id|currcon
)braket
dot
id|cmap.len
)paren
id|fb_get_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|currcon
)braket
dot
id|cmap
comma
l_int|1
comma
id|g364fb_getcolreg
comma
id|info
)paren
suffix:semicolon
id|currcon
op_assign
id|con
suffix:semicolon
multiline_comment|/* Install new colormap */
id|do_install_cmap
c_func
(paren
id|con
comma
id|info
)paren
suffix:semicolon
id|g364fbcon_updatevar
c_func
(paren
id|con
comma
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Update the `var&squot; structure (called by fbcon.c)&n; */
DECL|function|g364fbcon_updatevar
r_static
r_int
id|g364fbcon_updatevar
c_func
(paren
r_int
id|con
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
id|con
op_eq
id|currcon
)paren
(brace
r_struct
id|fb_var_screeninfo
op_star
id|var
op_assign
op_amp
id|fb_display
(braket
id|currcon
)braket
dot
id|var
suffix:semicolon
multiline_comment|/* hardware scrolling */
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Blank the display.&n; */
DECL|function|g364fbcon_blank
r_static
r_void
id|g364fbcon_blank
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
)brace
multiline_comment|/*&n; *  Read a single color register and split it into&n; *  colors/transparent. Return != 0 for invalid regno.&n; */
DECL|function|g364fb_getcolreg
r_static
r_int
id|g364fb_getcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
op_star
id|red
comma
id|u_int
op_star
id|green
comma
id|u_int
op_star
id|blue
comma
id|u_int
op_star
id|transp
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
id|regno
OG
l_int|255
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|red
op_assign
(paren
id|palette
(braket
id|regno
)braket
dot
id|red
op_lshift
l_int|8
)paren
op_or
id|palette
(braket
id|regno
)braket
dot
id|red
suffix:semicolon
op_star
id|green
op_assign
(paren
id|palette
(braket
id|regno
)braket
dot
id|green
op_lshift
l_int|8
)paren
op_or
id|palette
(braket
id|regno
)braket
dot
id|green
suffix:semicolon
op_star
id|blue
op_assign
(paren
id|palette
(braket
id|regno
)braket
dot
id|blue
op_lshift
l_int|8
)paren
op_or
id|palette
(braket
id|regno
)braket
dot
id|blue
suffix:semicolon
op_star
id|transp
op_assign
l_int|0
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
id|palette
(braket
id|regno
)braket
dot
id|red
op_assign
id|red
suffix:semicolon
id|palette
(braket
id|regno
)braket
dot
id|green
op_assign
id|green
suffix:semicolon
id|palette
(braket
id|regno
)braket
dot
id|blue
op_assign
id|blue
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
DECL|function|do_install_cmap
r_static
r_void
id|do_install_cmap
c_func
(paren
r_int
id|con
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
id|con
op_ne
id|currcon
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
id|fb_set_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
l_int|1
comma
id|g364fb_setcolreg
comma
id|info
)paren
suffix:semicolon
r_else
id|fb_set_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
l_int|1
op_lshift
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
)paren
comma
l_int|1
comma
id|g364fb_setcolreg
comma
id|info
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
