multiline_comment|/*&n; *&t;linux/drivers/video/pmag-aa-fb.c&n; *&t;Copyright 2002 Karsten Merker &lt;merker@debian.org&gt;&n; *&n; *&t;PMAG-AA TurboChannel framebuffer card support ... derived from&n; *&t;pmag-ba-fb.c, which is Copyright (C) 1999, 2000, 2001 by&n; *&t;Michael Engel &lt;engel@unix-ag.org&gt;, Karsten Merker &lt;merker@debian.org&gt;&n; *&t;and Harald Koerfgen &lt;hkoerfg@web.de&gt;, which itself is derived from&n; *&t;&quot;HP300 Topcat framebuffer support (derived from macfb of all things)&n; *&t;Phil Blundell &lt;philb@gnu.org&gt; 1998&quot;&n; *&n; *&t;This file is subject to the terms and conditions of the GNU General&n; *&t;Public License.  See the file COPYING in the main directory of this&n; *&t;archive for more details.&n; *&n; *&t;2002-09-28  Karsten Merker &lt;merker@linuxtag.org&gt;&n; *&t;&t;Version 0.01: First try to get a PMAG-AA running.&n; *&n; *&t;2003-02-24  Thiemo Seufer  &lt;seufer@csv.ica.uni-stuttgart.de&gt;&n; *&t;&t;Version 0.02: Major code cleanup.&n; *&n; *&t;2003-09-21  Thiemo Seufer  &lt;seufer@csv.ica.uni-stuttgart.de&gt;&n; *&t;&t;Hardware cursor support.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/dec/machtype.h&gt;
macro_line|#include &lt;asm/dec/tc.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &quot;bt455.h&quot;
macro_line|#include &quot;bt431.h&quot;
multiline_comment|/* Version information */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;0.02&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Karsten Merker &lt;merker@linuxtag.org&gt;&quot;
DECL|macro|DRIVER_DESCRIPTION
mdefine_line|#define DRIVER_DESCRIPTION &quot;PMAG-AA Framebuffer Driver&quot;
multiline_comment|/* Prototypes */
r_static
r_int
id|aafb_set_var
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
multiline_comment|/*&n; * Bt455 RAM DAC register base offset (rel. to TC slot base address).&n; */
DECL|macro|PMAG_AA_BT455_OFFSET
mdefine_line|#define PMAG_AA_BT455_OFFSET&t;&t;0x100000
multiline_comment|/*&n; * Bt431 cursor generator offset (rel. to TC slot base address).&n; */
DECL|macro|PMAG_AA_BT431_OFFSET
mdefine_line|#define PMAG_AA_BT431_OFFSET&t;&t;0x180000
multiline_comment|/*&n; * Begin of PMAG-AA framebuffer memory relative to TC slot address,&n; * resolution is 1280x1024x1 (8 bits deep, but only LSB is used).&n; */
DECL|macro|PMAG_AA_ONBOARD_FBMEM_OFFSET
mdefine_line|#define PMAG_AA_ONBOARD_FBMEM_OFFSET&t;0x200000
DECL|struct|aafb_cursor
r_struct
id|aafb_cursor
(brace
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|enable
r_int
id|enable
suffix:semicolon
DECL|member|on
r_int
id|on
suffix:semicolon
DECL|member|vbl_cnt
r_int
id|vbl_cnt
suffix:semicolon
DECL|member|blink_rate
r_int
id|blink_rate
suffix:semicolon
DECL|member|x
DECL|member|y
DECL|member|width
DECL|member|height
id|u16
id|x
comma
id|y
comma
id|width
comma
id|height
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CURSOR_TIMER_FREQ
mdefine_line|#define CURSOR_TIMER_FREQ&t;(HZ / 50)
DECL|macro|CURSOR_BLINK_RATE
mdefine_line|#define CURSOR_BLINK_RATE&t;(20)
DECL|macro|CURSOR_DRAW_DELAY
mdefine_line|#define CURSOR_DRAW_DELAY&t;(2)
DECL|struct|aafb_info
r_struct
id|aafb_info
(brace
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
DECL|member|disp
r_struct
id|display
id|disp
suffix:semicolon
DECL|member|cursor
r_struct
id|aafb_cursor
id|cursor
suffix:semicolon
DECL|member|bt455
r_struct
id|bt455_regs
op_star
id|bt455
suffix:semicolon
DECL|member|bt431
r_struct
id|bt431_regs
op_star
id|bt431
suffix:semicolon
DECL|member|fb_start
r_int
r_int
id|fb_start
suffix:semicolon
DECL|member|fb_size
r_int
r_int
id|fb_size
suffix:semicolon
DECL|member|fb_line_length
r_int
r_int
id|fb_line_length
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Max 3 TURBOchannel slots -&gt; max 3 PMAG-AA.&n; */
DECL|variable|my_fb_info
r_static
r_struct
id|aafb_info
id|my_fb_info
(braket
l_int|3
)braket
suffix:semicolon
DECL|struct|aafb_par
r_static
r_struct
id|aafb_par
(brace
DECL|variable|current_par
)brace
id|current_par
suffix:semicolon
DECL|variable|currcon
r_static
r_int
id|currcon
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|function|aafb_set_cursor
r_static
r_void
id|aafb_set_cursor
c_func
(paren
r_struct
id|aafb_info
op_star
id|info
comma
r_int
id|on
)paren
(brace
r_struct
id|aafb_cursor
op_star
id|c
op_assign
op_amp
id|info-&gt;cursor
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
(brace
id|bt431_position_cursor
c_func
(paren
id|info-&gt;bt431
comma
id|c-&gt;x
comma
id|c-&gt;y
)paren
suffix:semicolon
id|bt431_enable_cursor
c_func
(paren
id|info-&gt;bt431
)paren
suffix:semicolon
)brace
r_else
id|bt431_erase_cursor
c_func
(paren
id|info-&gt;bt431
)paren
suffix:semicolon
)brace
DECL|function|aafbcon_cursor
r_static
r_void
id|aafbcon_cursor
c_func
(paren
r_struct
id|display
op_star
id|disp
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
r_struct
id|aafb_info
op_star
id|info
op_assign
(paren
r_struct
id|aafb_info
op_star
)paren
id|disp-&gt;fb_info
suffix:semicolon
r_struct
id|aafb_cursor
op_star
id|c
op_assign
op_amp
id|info-&gt;cursor
suffix:semicolon
id|x
op_mul_assign
id|fontwidth
c_func
(paren
id|disp
)paren
suffix:semicolon
id|y
op_mul_assign
id|fontheight
c_func
(paren
id|disp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x
op_eq
id|x
op_logical_and
id|c-&gt;y
op_eq
id|y
op_logical_and
(paren
id|mode
op_eq
id|CM_ERASE
)paren
op_eq
op_logical_neg
id|c-&gt;enable
)paren
r_return
suffix:semicolon
id|c-&gt;enable
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;on
)paren
id|aafb_set_cursor
c_func
(paren
id|info
comma
l_int|0
)paren
suffix:semicolon
id|c-&gt;x
op_assign
id|x
op_minus
id|disp-&gt;var.xoffset
suffix:semicolon
id|c-&gt;y
op_assign
id|y
op_minus
id|disp-&gt;var.yoffset
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|CM_ERASE
suffix:colon
id|c-&gt;on
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CM_DRAW
suffix:colon
r_case
id|CM_MOVE
suffix:colon
r_if
c_cond
(paren
id|c-&gt;on
)paren
id|aafb_set_cursor
c_func
(paren
id|info
comma
id|c-&gt;on
)paren
suffix:semicolon
r_else
id|c-&gt;vbl_cnt
op_assign
id|CURSOR_DRAW_DELAY
suffix:semicolon
id|c-&gt;enable
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|aafbcon_set_font
r_static
r_int
id|aafbcon_set_font
c_func
(paren
r_struct
id|display
op_star
id|disp
comma
r_int
id|width
comma
r_int
id|height
)paren
(brace
r_struct
id|aafb_info
op_star
id|info
op_assign
(paren
r_struct
id|aafb_info
op_star
)paren
id|disp-&gt;fb_info
suffix:semicolon
r_struct
id|aafb_cursor
op_star
id|c
op_assign
op_amp
id|info-&gt;cursor
suffix:semicolon
id|u8
id|fgc
op_assign
op_complement
id|attr_bgcol_ec
c_func
(paren
id|disp
comma
id|disp-&gt;conp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|width
OG
l_int|64
op_logical_or
id|height
OG
l_int|64
op_logical_or
id|width
OL
l_int|0
op_logical_or
id|height
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|c-&gt;height
op_assign
id|height
suffix:semicolon
id|c-&gt;width
op_assign
id|width
suffix:semicolon
id|bt431_set_font
c_func
(paren
id|info-&gt;bt431
comma
id|fgc
comma
id|width
comma
id|height
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|aafb_cursor_timer_handler
r_static
r_void
id|aafb_cursor_timer_handler
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|aafb_info
op_star
id|info
op_assign
(paren
r_struct
id|aafb_info
op_star
)paren
id|data
suffix:semicolon
r_struct
id|aafb_cursor
op_star
id|c
op_assign
op_amp
id|info-&gt;cursor
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;enable
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;vbl_cnt
op_logical_and
op_decrement
id|c-&gt;vbl_cnt
op_eq
l_int|0
)paren
(brace
id|c-&gt;on
op_xor_assign
l_int|1
suffix:semicolon
id|aafb_set_cursor
c_func
(paren
id|info
comma
id|c-&gt;on
)paren
suffix:semicolon
id|c-&gt;vbl_cnt
op_assign
id|c-&gt;blink_rate
suffix:semicolon
)brace
id|out
suffix:colon
id|c-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|CURSOR_TIMER_FREQ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|c-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|aafb_cursor_init
r_static
r_void
id|__init
id|aafb_cursor_init
c_func
(paren
r_struct
id|aafb_info
op_star
id|info
)paren
(brace
r_struct
id|aafb_cursor
op_star
id|c
op_assign
op_amp
id|info-&gt;cursor
suffix:semicolon
id|c-&gt;enable
op_assign
l_int|1
suffix:semicolon
id|c-&gt;on
op_assign
l_int|1
suffix:semicolon
id|c-&gt;x
op_assign
id|c-&gt;y
op_assign
l_int|0
suffix:semicolon
id|c-&gt;width
op_assign
id|c-&gt;height
op_assign
l_int|0
suffix:semicolon
id|c-&gt;vbl_cnt
op_assign
id|CURSOR_DRAW_DELAY
suffix:semicolon
id|c-&gt;blink_rate
op_assign
id|CURSOR_BLINK_RATE
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|c-&gt;timer
)paren
suffix:semicolon
id|c-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|info
suffix:semicolon
id|c-&gt;timer.function
op_assign
id|aafb_cursor_timer_handler
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|c-&gt;timer
comma
id|jiffies
op_plus
id|CURSOR_TIMER_FREQ
)paren
suffix:semicolon
)brace
DECL|function|aafb_cursor_exit
r_static
r_void
id|__exit
id|aafb_cursor_exit
c_func
(paren
r_struct
id|aafb_info
op_star
id|info
)paren
(brace
r_struct
id|aafb_cursor
op_star
id|c
op_assign
op_amp
id|info-&gt;cursor
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|c-&gt;timer
)paren
suffix:semicolon
)brace
DECL|variable|aafb_switch8
r_static
r_struct
id|display_switch
id|aafb_switch8
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
id|fbcon_cfb8_bmove
comma
dot
id|clear
op_assign
id|fbcon_cfb8_clear
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
id|cursor
op_assign
id|aafbcon_cursor
comma
dot
id|set_font
op_assign
id|aafbcon_set_font
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
DECL|function|aafb_get_par
r_static
r_void
id|aafb_get_par
c_func
(paren
r_struct
id|aafb_par
op_star
id|par
)paren
(brace
op_star
id|par
op_assign
id|current_par
suffix:semicolon
)brace
DECL|function|aafb_get_fix
r_static
r_int
id|aafb_get_fix
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
r_struct
id|aafb_info
op_star
id|ip
op_assign
(paren
r_struct
id|aafb_info
op_star
)paren
id|info
suffix:semicolon
id|memset
c_func
(paren
id|fix
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fb_fix_screeninfo
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;PMAG-AA&quot;
)paren
suffix:semicolon
id|fix-&gt;smem_start
op_assign
id|ip-&gt;fb_start
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|ip-&gt;fb_size
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fix-&gt;ypanstep
op_assign
l_int|1
suffix:semicolon
id|fix-&gt;ywrapstep
op_assign
l_int|1
suffix:semicolon
id|fix-&gt;visual
op_assign
id|FB_VISUAL_MONO10
suffix:semicolon
id|fix-&gt;line_length
op_assign
l_int|1280
suffix:semicolon
id|fix-&gt;accel
op_assign
id|FB_ACCEL_NONE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aafb_set_disp
r_static
r_void
id|aafb_set_disp
c_func
(paren
r_struct
id|display
op_star
id|disp
comma
r_int
id|con
comma
r_struct
id|aafb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
id|disp-&gt;fb_info
op_assign
op_amp
id|info-&gt;info
suffix:semicolon
id|aafb_set_var
c_func
(paren
op_amp
id|disp-&gt;var
comma
id|con
comma
op_amp
id|info-&gt;info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disp-&gt;conp
op_logical_and
id|disp-&gt;conp-&gt;vc_sw
op_logical_and
id|disp-&gt;conp-&gt;vc_sw-&gt;con_cursor
)paren
id|disp-&gt;conp-&gt;vc_sw
op_member_access_from_pointer
id|con_cursor
c_func
(paren
id|disp-&gt;conp
comma
id|CM_ERASE
)paren
suffix:semicolon
id|disp-&gt;dispsw
op_assign
op_amp
id|aafb_switch8
suffix:semicolon
id|disp-&gt;dispsw_data
op_assign
l_int|0
suffix:semicolon
id|aafb_get_fix
c_func
(paren
op_amp
id|fix
comma
id|con
comma
op_amp
id|info-&gt;info
)paren
suffix:semicolon
id|disp-&gt;screen_base
op_assign
(paren
id|u8
op_star
)paren
id|fix.smem_start
suffix:semicolon
id|disp-&gt;visual
op_assign
id|fix.visual
suffix:semicolon
id|disp-&gt;type
op_assign
id|fix.type
suffix:semicolon
id|disp-&gt;type_aux
op_assign
id|fix.type_aux
suffix:semicolon
id|disp-&gt;ypanstep
op_assign
id|fix.ypanstep
suffix:semicolon
id|disp-&gt;ywrapstep
op_assign
id|fix.ywrapstep
suffix:semicolon
id|disp-&gt;line_length
op_assign
id|fix.line_length
suffix:semicolon
id|disp-&gt;next_line
op_assign
l_int|2048
suffix:semicolon
id|disp-&gt;can_soft_blank
op_assign
l_int|1
suffix:semicolon
id|disp-&gt;inverse
op_assign
l_int|0
suffix:semicolon
id|disp-&gt;scrollmode
op_assign
id|SCROLL_YREDRAW
suffix:semicolon
id|aafbcon_set_font
c_func
(paren
id|disp
comma
id|fontwidth
c_func
(paren
id|disp
)paren
comma
id|fontheight
c_func
(paren
id|disp
)paren
)paren
suffix:semicolon
)brace
DECL|function|aafb_get_cmap
r_static
r_int
id|aafb_get_cmap
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
r_static
id|u16
id|color
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x000f
)brace
suffix:semicolon
r_static
r_struct
id|fb_cmap
id|aafb_cmap
op_assign
(brace
l_int|0
comma
l_int|2
comma
id|color
comma
id|color
comma
id|color
comma
l_int|NULL
)brace
suffix:semicolon
id|fb_copy_cmap
c_func
(paren
op_amp
id|aafb_cmap
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
DECL|function|aafb_set_cmap
r_static
r_int
id|aafb_set_cmap
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
id|u16
id|color
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x000f
)brace
suffix:semicolon
r_if
c_cond
(paren
id|cmap-&gt;start
op_eq
l_int|0
op_logical_and
id|cmap-&gt;len
op_eq
l_int|2
op_logical_and
id|memcmp
c_func
(paren
id|cmap-&gt;red
comma
id|color
comma
r_sizeof
(paren
id|color
)paren
)paren
op_eq
l_int|0
op_logical_and
id|memcmp
c_func
(paren
id|cmap-&gt;green
comma
id|color
comma
r_sizeof
(paren
id|color
)paren
)paren
op_eq
l_int|0
op_logical_and
id|memcmp
c_func
(paren
id|cmap-&gt;blue
comma
id|color
comma
r_sizeof
(paren
id|color
)paren
)paren
op_eq
l_int|0
op_logical_and
id|cmap-&gt;transp
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|aafb_ioctl
r_static
r_int
id|aafb_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
id|u32
id|cmd
comma
r_int
r_int
id|arg
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
multiline_comment|/* TODO: Not yet implemented */
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
DECL|function|aafb_switch
r_static
r_int
id|aafb_switch
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
r_struct
id|aafb_info
op_star
id|ip
op_assign
(paren
r_struct
id|aafb_info
op_star
)paren
id|info
suffix:semicolon
r_struct
id|display
op_star
id|old
op_assign
(paren
id|currcon
OL
l_int|0
)paren
ques
c_cond
op_amp
id|ip-&gt;disp
suffix:colon
(paren
id|fb_display
op_plus
id|currcon
)paren
suffix:semicolon
r_struct
id|display
op_star
r_new
op_assign
(paren
id|con
OL
l_int|0
)paren
ques
c_cond
op_amp
id|ip-&gt;disp
suffix:colon
(paren
id|fb_display
op_plus
id|con
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old-&gt;conp
op_logical_and
id|old-&gt;conp-&gt;vc_sw
op_logical_and
id|old-&gt;conp-&gt;vc_sw-&gt;con_cursor
)paren
id|old-&gt;conp-&gt;vc_sw
op_member_access_from_pointer
id|con_cursor
c_func
(paren
id|old-&gt;conp
comma
id|CM_ERASE
)paren
suffix:semicolon
multiline_comment|/* Set the current console. */
id|currcon
op_assign
id|con
suffix:semicolon
id|aafb_set_disp
c_func
(paren
r_new
comma
id|con
comma
id|ip
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aafb_encode_var
r_static
r_void
id|aafb_encode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|aafb_par
op_star
id|par
)paren
(brace
id|var-&gt;xres
op_assign
l_int|1280
suffix:semicolon
id|var-&gt;yres
op_assign
l_int|1024
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
l_int|2048
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
l_int|1024
suffix:semicolon
id|var-&gt;xoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;yoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;bits_per_pixel
op_assign
l_int|8
suffix:semicolon
id|var-&gt;grayscale
op_assign
l_int|1
suffix:semicolon
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|1
suffix:semicolon
id|var-&gt;green.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;nonstd
op_assign
l_int|0
suffix:semicolon
id|var-&gt;activate
op_and_assign
op_complement
id|FB_ACTIVATE_MASK
op_amp
id|FB_ACTIVATE_NOW
suffix:semicolon
id|var-&gt;accel_flags
op_assign
l_int|0
suffix:semicolon
id|var-&gt;sync
op_assign
id|FB_SYNC_ON_GREEN
suffix:semicolon
id|var-&gt;vmode
op_and_assign
op_complement
id|FB_VMODE_MASK
op_amp
id|FB_VMODE_NONINTERLACED
suffix:semicolon
)brace
DECL|function|aafb_get_var
r_static
r_int
id|aafb_get_var
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
id|con
OL
l_int|0
)paren
(brace
r_struct
id|aafb_par
id|par
suffix:semicolon
id|memset
c_func
(paren
id|var
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fb_var_screeninfo
)paren
)paren
suffix:semicolon
id|aafb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|aafb_encode_var
c_func
(paren
id|var
comma
op_amp
id|par
)paren
suffix:semicolon
)brace
r_else
op_star
id|var
op_assign
id|info-&gt;var
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aafb_set_var
r_static
r_int
id|aafb_set_var
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
id|aafb_par
id|par
suffix:semicolon
id|aafb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|aafb_encode_var
c_func
(paren
id|var
comma
op_amp
id|par
)paren
suffix:semicolon
id|info-&gt;var
op_assign
op_star
id|var
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aafb_update_var
r_static
r_int
id|aafb_update_var
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
r_struct
id|aafb_info
op_star
id|ip
op_assign
(paren
r_struct
id|aafb_info
op_star
)paren
id|info
suffix:semicolon
r_struct
id|display
op_star
id|disp
op_assign
(paren
id|con
OL
l_int|0
)paren
ques
c_cond
op_amp
id|ip-&gt;disp
suffix:colon
(paren
id|fb_display
op_plus
id|con
)paren
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
id|currcon
)paren
id|aafbcon_cursor
c_func
(paren
id|disp
comma
id|CM_ERASE
comma
id|ip-&gt;cursor.x
comma
id|ip-&gt;cursor.y
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* 0 unblanks, any other blanks. */
DECL|function|aafb_blank
r_static
r_void
id|aafb_blank
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
r_struct
id|aafb_info
op_star
id|ip
op_assign
(paren
r_struct
id|aafb_info
op_star
)paren
id|info
suffix:semicolon
id|u8
id|val
op_assign
id|blank
ques
c_cond
l_int|0x00
suffix:colon
l_int|0x0f
suffix:semicolon
id|bt455_write_cmap_entry
c_func
(paren
id|ip-&gt;bt455
comma
l_int|1
comma
id|val
comma
id|val
comma
id|val
)paren
suffix:semicolon
id|aafbcon_cursor
c_func
(paren
op_amp
id|ip-&gt;disp
comma
id|CM_ERASE
comma
id|ip-&gt;cursor.x
comma
id|ip-&gt;cursor.y
)paren
suffix:semicolon
)brace
DECL|variable|aafb_ops
r_static
r_struct
id|fb_ops
id|aafb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_get_fix
op_assign
id|aafb_get_fix
comma
dot
id|fb_get_var
op_assign
id|aafb_get_var
comma
dot
id|fb_set_var
op_assign
id|aafb_set_var
comma
dot
id|fb_get_cmap
op_assign
id|aafb_get_cmap
comma
dot
id|fb_set_cmap
op_assign
id|aafb_set_cmap
comma
dot
id|fb_ioctl
op_assign
id|aafb_ioctl
)brace
suffix:semicolon
DECL|function|init_one
r_static
r_int
id|__init
id|init_one
c_func
(paren
r_int
id|slot
)paren
(brace
r_int
r_int
id|base_addr
op_assign
id|get_tc_base_addr
c_func
(paren
id|slot
)paren
suffix:semicolon
r_struct
id|aafb_info
op_star
id|ip
op_assign
op_amp
id|my_fb_info
(braket
id|slot
)braket
suffix:semicolon
id|memset
c_func
(paren
id|ip
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|aafb_info
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Framebuffer display memory base address and friends.&n;&t; */
id|ip-&gt;bt455
op_assign
(paren
r_struct
id|bt455_regs
op_star
)paren
(paren
id|base_addr
op_plus
id|PMAG_AA_BT455_OFFSET
)paren
suffix:semicolon
id|ip-&gt;bt431
op_assign
(paren
r_struct
id|bt431_regs
op_star
)paren
(paren
id|base_addr
op_plus
id|PMAG_AA_BT431_OFFSET
)paren
suffix:semicolon
id|ip-&gt;fb_start
op_assign
id|base_addr
op_plus
id|PMAG_AA_ONBOARD_FBMEM_OFFSET
suffix:semicolon
id|ip-&gt;fb_size
op_assign
l_int|2048
op_star
l_int|1024
suffix:semicolon
multiline_comment|/* fb_fix_screeninfo.smem_length&n;&t;&t;&t;&t;      seems to be physical */
id|ip-&gt;fb_line_length
op_assign
l_int|2048
suffix:semicolon
multiline_comment|/*&n;&t; * Let there be consoles..&n;&t; */
id|strcpy
c_func
(paren
id|ip-&gt;info.modename
comma
l_string|&quot;PMAG-AA&quot;
)paren
suffix:semicolon
id|ip-&gt;info.node
op_assign
op_minus
l_int|1
suffix:semicolon
id|ip-&gt;info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|ip-&gt;info.fbops
op_assign
op_amp
id|aafb_ops
suffix:semicolon
id|ip-&gt;info.disp
op_assign
op_amp
id|ip-&gt;disp
suffix:semicolon
id|ip-&gt;info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|ip-&gt;info.switch_con
op_assign
op_amp
id|aafb_switch
suffix:semicolon
id|ip-&gt;info.updatevar
op_assign
op_amp
id|aafb_update_var
suffix:semicolon
id|ip-&gt;info.blank
op_assign
op_amp
id|aafb_blank
suffix:semicolon
id|aafb_set_disp
c_func
(paren
op_amp
id|ip-&gt;disp
comma
id|currcon
comma
id|ip
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Configure the RAM DACs.&n;&t; */
id|bt455_erase_cursor
c_func
(paren
id|ip-&gt;bt455
)paren
suffix:semicolon
multiline_comment|/* Init colormap. */
id|bt455_write_cmap_entry
c_func
(paren
id|ip-&gt;bt455
comma
l_int|0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)paren
suffix:semicolon
id|bt455_write_cmap_entry
c_func
(paren
id|ip-&gt;bt455
comma
l_int|1
comma
l_int|0x0f
comma
l_int|0x0f
comma
l_int|0x0f
)paren
suffix:semicolon
multiline_comment|/* Init hardware cursor. */
id|bt431_init_cursor
c_func
(paren
id|ip-&gt;bt431
)paren
suffix:semicolon
id|aafb_cursor_init
c_func
(paren
id|ip
)paren
suffix:semicolon
multiline_comment|/* Clear the screen. */
id|memset
(paren
(paren
r_void
op_star
)paren
id|ip-&gt;fb_start
comma
l_int|0
comma
id|ip-&gt;fb_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|ip-&gt;info
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
id|KERN_INFO
l_string|&quot;fb%d: %s frame buffer in TC slot %d&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|ip-&gt;info.node
)paren
comma
id|ip-&gt;info.modename
comma
id|slot
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exit_one
r_static
r_int
id|__exit
id|exit_one
c_func
(paren
r_int
id|slot
)paren
(brace
r_struct
id|aafb_info
op_star
id|ip
op_assign
op_amp
id|my_fb_info
(braket
id|slot
)braket
suffix:semicolon
r_if
c_cond
(paren
id|unregister_framebuffer
c_func
(paren
op_amp
id|ip-&gt;info
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
multiline_comment|/*&n; * Initialise the framebuffer.&n; */
DECL|function|pmagaafb_init
r_int
id|__init
id|pmagaafb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|sid
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|sid
op_assign
id|search_tc_card
c_func
(paren
l_string|&quot;PMAG-AA&quot;
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
id|claim_tc_card
c_func
(paren
id|sid
)paren
suffix:semicolon
id|init_one
c_func
(paren
id|sid
)paren
suffix:semicolon
)brace
r_return
id|found
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|pmagaafb_exit
r_static
r_void
id|__exit
id|pmagaafb_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|sid
suffix:semicolon
r_while
c_loop
(paren
(paren
id|sid
op_assign
id|search_tc_card
c_func
(paren
l_string|&quot;PMAG-AA&quot;
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|exit_one
c_func
(paren
id|sid
)paren
suffix:semicolon
id|release_tc_card
c_func
(paren
id|sid
)paren
suffix:semicolon
)brace
)brace
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESCRIPTION
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESCRIPTION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|variable|pmagaafb_init
id|module_init
c_func
(paren
id|pmagaafb_init
)paren
suffix:semicolon
DECL|variable|pmagaafb_exit
id|module_exit
c_func
(paren
id|pmagaafb_exit
)paren
suffix:semicolon
macro_line|#endif
eof
