multiline_comment|/*&n; * linux/drivers/video/epson1355fb.c&n; *&t;-- Support for the Epson SED1355 LCD/CRT controller&n; *&n; * Copyright (C) 2000 Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *&n; * based on linux/drivers/video/skeletonfb.c, which was&n; *  Created 28 Dec 1997 by Geert Uytterhoeven&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/* TODO (roughly in order of priority):&n; * 16 bpp support&n; * crt support&n; * hw cursor support&n; * SwivelView&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &lt;video/fbcon-mfb.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
multiline_comment|/* Register defines.  The docs don&squot;t seem to provide nice mnemonic names&n; * so I made them up myself ... */
DECL|macro|E1355_PANEL
mdefine_line|#define E1355_PANEL&t;0x02
DECL|macro|E1355_DISPLAY
mdefine_line|#define E1355_DISPLAY&t;0x0D
DECL|macro|E1355_MISC
mdefine_line|#define E1355_MISC&t;0x1B
DECL|macro|E1355_GPIO
mdefine_line|#define E1355_GPIO&t;0x20
DECL|macro|E1355_LUT_INDEX
mdefine_line|#define E1355_LUT_INDEX 0x24
DECL|macro|E1355_LUT_DATA
mdefine_line|#define E1355_LUT_DATA&t;0x26
macro_line|#ifdef CONFIG_SUPERH
DECL|macro|E1355_REG_BASE
mdefine_line|#define E1355_REG_BASE&t;CONFIG_E1355_REG_BASE
DECL|macro|E1355_FB_BASE
mdefine_line|#define E1355_FB_BASE&t;CONFIG_E1355_FB_BASE
DECL|function|e1355_read_reg
r_static
r_inline
id|u8
id|e1355_read_reg
c_func
(paren
r_int
id|index
)paren
(brace
r_return
id|ctrl_inb
c_func
(paren
id|E1355_REG_BASE
op_plus
id|index
)paren
suffix:semicolon
)brace
DECL|function|e1355_write_reg
r_static
r_inline
r_void
id|e1355_write_reg
c_func
(paren
id|u8
id|data
comma
r_int
id|index
)paren
(brace
id|ctrl_outb
c_func
(paren
id|data
comma
id|E1355_REG_BASE
op_plus
id|index
)paren
suffix:semicolon
)brace
DECL|function|e1355_read_reg16
r_static
r_inline
id|u16
id|e1355_read_reg16
c_func
(paren
r_int
id|index
)paren
(brace
r_return
id|e1355_read_reg
c_func
(paren
id|index
)paren
op_plus
(paren
id|e1355_read_reg
c_func
(paren
id|index
op_plus
l_int|1
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|e1355_write_reg16
r_static
r_inline
r_void
id|e1355_write_reg16
c_func
(paren
id|u16
id|data
comma
r_int
id|index
)paren
(brace
id|e1355_write_reg
c_func
(paren
(paren
id|data
op_amp
l_int|0xff
)paren
comma
id|index
)paren
suffix:semicolon
id|e1355_write_reg
c_func
(paren
(paren
(paren
id|data
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
comma
id|index
op_plus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#else
macro_line|#error unknown architecture
macro_line|#endif
DECL|struct|e1355fb_info
r_struct
id|e1355fb_info
(brace
DECL|member|gen
r_struct
id|fb_info_gen
id|gen
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|current_par_valid
r_static
r_int
id|current_par_valid
op_assign
l_int|0
suffix:semicolon
DECL|variable|disp
r_static
r_struct
id|display
id|disp
suffix:semicolon
DECL|variable|default_var
r_static
r_struct
id|fb_var_screeninfo
id|default_var
suffix:semicolon
r_int
id|e1355fb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|e1355fb_setup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_static
r_int
id|e1355_encode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_const
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* ------------------- chipset specific functions -------------------------- */
DECL|function|disable_hw_cursor
r_static
r_void
id|disable_hw_cursor
c_func
(paren
r_void
)paren
(brace
id|u8
id|curs
suffix:semicolon
id|curs
op_assign
id|e1355_read_reg
c_func
(paren
l_int|0x27
)paren
suffix:semicolon
id|curs
op_and_assign
op_complement
l_int|0xc0
suffix:semicolon
id|e1355_write_reg
c_func
(paren
id|curs
comma
l_int|0x27
)paren
suffix:semicolon
)brace
DECL|function|e1355_detect
r_static
r_void
id|e1355_detect
c_func
(paren
r_void
)paren
(brace
id|u8
id|rev
suffix:semicolon
id|e1355_write_reg
c_func
(paren
l_int|0x00
comma
id|E1355_MISC
)paren
suffix:semicolon
id|rev
op_assign
id|e1355_read_reg
c_func
(paren
l_int|0x00
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rev
op_amp
l_int|0xfc
)paren
op_ne
l_int|0x0c
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Epson 1355 not detected&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX */
id|disable_hw_cursor
c_func
(paren
)paren
suffix:semicolon
id|e1355_encode_var
c_func
(paren
op_amp
id|default_var
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|struct|e1355_par
r_struct
id|e1355_par
(brace
DECL|member|xres
id|u32
id|xres
suffix:semicolon
DECL|member|yres
id|u32
id|yres
suffix:semicolon
DECL|member|bpp
r_int
id|bpp
suffix:semicolon
DECL|member|mem_bpp
r_int
id|mem_bpp
suffix:semicolon
DECL|member|panel_xres
id|u32
id|panel_xres
suffix:semicolon
DECL|member|panel_yres
id|u32
id|panel_yres
suffix:semicolon
DECL|member|panel_width
r_int
id|panel_width
suffix:semicolon
DECL|member|panel_ymul
r_int
id|panel_ymul
suffix:semicolon
)brace
suffix:semicolon
DECL|function|e1355_encode_fix
r_static
r_int
id|e1355_encode_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_const
r_void
op_star
id|raw_par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
r_const
r_struct
id|e1355_par
op_star
id|par
op_assign
id|raw_par
suffix:semicolon
id|memset
c_func
(paren
id|fix
comma
l_int|0
comma
r_sizeof
op_star
id|fix
)paren
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|par
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;bpp
op_eq
l_int|1
)paren
(brace
id|fix-&gt;visual
op_assign
id|FB_VISUAL_MONO10
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|par-&gt;bpp
op_le
l_int|8
)paren
(brace
id|fix-&gt;visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
)brace
r_else
(brace
id|fix-&gt;visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|e1355_set_bpp
r_static
r_int
id|e1355_set_bpp
c_func
(paren
r_struct
id|e1355_par
op_star
id|par
comma
r_int
id|bpp
)paren
(brace
r_int
id|code
suffix:semicolon
id|u8
id|disp
suffix:semicolon
id|u16
id|bytes_per_line
suffix:semicolon
r_switch
c_cond
(paren
id|bpp
)paren
(brace
r_case
l_int|1
suffix:colon
id|code
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|code
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|code
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|code
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|code
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|disp
op_assign
id|e1355_read_reg
c_func
(paren
id|E1355_DISPLAY
)paren
suffix:semicolon
id|disp
op_and_assign
op_complement
l_int|0x1c
suffix:semicolon
id|disp
op_or_assign
id|code
op_lshift
l_int|2
suffix:semicolon
id|e1355_write_reg
c_func
(paren
id|disp
comma
id|E1355_DISPLAY
)paren
suffix:semicolon
id|bytes_per_line
op_assign
(paren
id|par-&gt;xres
op_star
id|bpp
)paren
op_rshift
l_int|3
suffix:semicolon
id|e1355_write_reg16
c_func
(paren
id|bytes_per_line
comma
l_int|0x16
)paren
suffix:semicolon
id|par-&gt;bpp
op_assign
id|bpp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|e1355_decode_var
r_static
r_int
id|e1355_decode_var
c_func
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_void
op_star
id|raw_par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
r_struct
id|e1355_par
op_star
id|par
op_assign
id|raw_par
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|par
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t allow setting any of these yet: xres and yres don&squot;t&n;&t; * make sense for LCD panels; xres_virtual and yres_virtual&n;&t; * should be supported fine by our hardware though.&n;&t; */
r_if
c_cond
(paren
id|var-&gt;xres
op_ne
id|par-&gt;xres
op_logical_or
id|var-&gt;yres
op_ne
id|par-&gt;yres
op_logical_or
id|var-&gt;xres
op_ne
id|var-&gt;xres_virtual
op_logical_or
id|var-&gt;yres
op_ne
id|var-&gt;yres_virtual
op_logical_or
id|var-&gt;xoffset
op_ne
l_int|0
op_logical_or
id|var-&gt;yoffset
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_ne
id|par-&gt;bpp
)paren
(brace
id|ret
op_assign
id|e1355_set_bpp
c_func
(paren
id|par
comma
id|var-&gt;bits_per_pixel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out_err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out_err
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|dump_panel_data
r_static
r_void
id|dump_panel_data
c_func
(paren
r_void
)paren
(brace
id|u8
id|panel
op_assign
id|e1355_read_reg
c_func
(paren
id|E1355_PANEL
)paren
suffix:semicolon
r_int
id|width
(braket
l_int|2
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|4
comma
l_int|8
comma
l_int|16
comma
op_minus
l_int|1
)brace
comma
(brace
l_int|9
comma
l_int|12
comma
l_int|16
comma
op_minus
l_int|1
)brace
)brace
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s %s %s panel, width %d bits&bslash;n&quot;
comma
id|panel
op_amp
l_int|2
ques
c_cond
l_string|&quot;dual&quot;
suffix:colon
l_string|&quot;single&quot;
comma
id|panel
op_amp
l_int|4
ques
c_cond
l_string|&quot;color&quot;
suffix:colon
l_string|&quot;mono&quot;
comma
id|panel
op_amp
l_int|1
ques
c_cond
l_string|&quot;TFT&quot;
suffix:colon
l_string|&quot;passive&quot;
comma
id|width
(braket
id|panel
op_amp
l_int|1
)braket
(braket
(paren
id|panel
op_rshift
l_int|4
)paren
op_amp
l_int|3
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;resolution %d x %d&bslash;n&quot;
comma
(paren
id|e1355_read_reg
c_func
(paren
l_int|0x04
)paren
op_plus
l_int|1
)paren
op_star
l_int|8
comma
(paren
(paren
id|e1355_read_reg16
c_func
(paren
l_int|0x08
)paren
op_plus
l_int|1
)paren
op_star
(paren
l_int|1
op_plus
(paren
(paren
id|panel
op_amp
l_int|3
)paren
op_eq
l_int|2
)paren
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|e1355_bpp_to_var
r_static
r_int
id|e1355_bpp_to_var
c_func
(paren
r_int
id|bpp
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
(brace
r_switch
c_cond
(paren
id|bpp
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|8
suffix:colon
id|var-&gt;bits_per_pixel
op_assign
id|bpp
suffix:semicolon
id|var-&gt;red.offset
op_assign
id|var-&gt;green.offset
op_assign
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
id|var-&gt;green.length
op_assign
id|var-&gt;blue.length
op_assign
id|bpp
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|var-&gt;bits_per_pixel
op_assign
l_int|16
suffix:semicolon
id|var-&gt;red.offset
op_assign
l_int|11
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|5
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|6
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|e1355_encode_var
r_static
r_int
id|e1355_encode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_const
r_void
op_star
id|raw_par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
id|u8
id|panel
comma
id|display
suffix:semicolon
id|u32
id|xres
comma
id|xres_virtual
comma
id|yres
suffix:semicolon
r_static
r_int
id|width
(braket
l_int|2
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|4
comma
l_int|8
comma
l_int|16
comma
op_minus
l_int|1
)brace
comma
(brace
l_int|9
comma
l_int|12
comma
l_int|16
comma
op_minus
l_int|1
)brace
)brace
suffix:semicolon
r_static
r_int
id|bpp_tab
(braket
l_int|8
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|4
comma
l_int|8
comma
l_int|15
comma
l_int|16
)brace
suffix:semicolon
r_int
id|bpp
comma
id|hw_bpp
suffix:semicolon
r_int
id|is_color
comma
id|is_dual
comma
id|is_tft
suffix:semicolon
r_int
id|lcd_enabled
comma
id|crt_enabled
suffix:semicolon
id|panel
op_assign
id|e1355_read_reg
c_func
(paren
id|E1355_PANEL
)paren
suffix:semicolon
id|display
op_assign
id|e1355_read_reg
c_func
(paren
id|E1355_DISPLAY
)paren
suffix:semicolon
id|is_color
op_assign
(paren
id|panel
op_amp
l_int|0x04
)paren
op_ne
l_int|0
suffix:semicolon
id|is_dual
op_assign
(paren
id|panel
op_amp
l_int|0x02
)paren
op_ne
l_int|0
suffix:semicolon
id|is_tft
op_assign
(paren
id|panel
op_amp
l_int|0x01
)paren
op_ne
l_int|0
suffix:semicolon
id|bpp
op_assign
id|bpp_tab
(braket
(paren
id|display
op_rshift
l_int|2
)paren
op_amp
l_int|7
)braket
suffix:semicolon
id|e1355_bpp_to_var
c_func
(paren
id|bpp
comma
id|var
)paren
suffix:semicolon
id|crt_enabled
op_assign
(paren
id|display
op_amp
l_int|0x02
)paren
op_ne
l_int|0
suffix:semicolon
id|lcd_enabled
op_assign
(paren
id|display
op_amp
l_int|0x02
)paren
op_ne
l_int|0
suffix:semicolon
id|hw_bpp
op_assign
id|width
(braket
id|is_tft
)braket
(braket
(paren
id|panel
op_rshift
l_int|4
)paren
op_amp
l_int|3
)braket
suffix:semicolon
id|xres
op_assign
id|e1355_read_reg
c_func
(paren
l_int|0x04
)paren
op_plus
l_int|1
suffix:semicolon
id|yres
op_assign
id|e1355_read_reg16
c_func
(paren
l_int|0x08
)paren
op_plus
l_int|1
suffix:semicolon
id|xres
op_mul_assign
l_int|8
suffix:semicolon
multiline_comment|/* talk about weird hardware .. */
id|yres
op_mul_assign
(paren
id|is_dual
op_logical_and
op_logical_neg
id|crt_enabled
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
id|xres_virtual
op_assign
id|e1355_read_reg16
c_func
(paren
l_int|0x16
)paren
suffix:semicolon
multiline_comment|/* it&squot;s in 2-byte words initially */
id|xres_virtual
op_mul_assign
l_int|16
suffix:semicolon
id|xres_virtual
op_div_assign
id|var-&gt;bits_per_pixel
suffix:semicolon
id|var-&gt;xres
op_assign
id|xres
suffix:semicolon
id|var-&gt;yres
op_assign
id|yres
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
id|xres_virtual
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
id|yres
suffix:semicolon
id|var-&gt;xoffset
op_assign
id|var-&gt;yoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;grayscale
op_assign
op_logical_neg
id|is_color
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|is_dual
mdefine_line|#define is_dual(panel) (((panel)&amp;3)==2)
DECL|function|get_panel_data
r_static
r_void
id|get_panel_data
c_func
(paren
r_struct
id|e1355_par
op_star
id|par
)paren
(brace
id|u8
id|panel
suffix:semicolon
r_int
id|width
(braket
l_int|2
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|4
comma
l_int|8
comma
l_int|16
comma
op_minus
l_int|1
)brace
comma
(brace
l_int|9
comma
l_int|12
comma
l_int|16
comma
op_minus
l_int|1
)brace
)brace
suffix:semicolon
id|panel
op_assign
id|e1355_read_reg
c_func
(paren
id|E1355_PANEL
)paren
suffix:semicolon
id|par-&gt;panel_width
op_assign
id|width
(braket
id|panel
op_amp
l_int|1
)braket
(braket
(paren
id|panel
op_rshift
l_int|4
)paren
op_amp
l_int|3
)braket
suffix:semicolon
id|par-&gt;panel_xres
op_assign
(paren
id|e1355_read_reg
c_func
(paren
l_int|0x04
)paren
op_plus
l_int|1
)paren
op_star
l_int|8
suffix:semicolon
id|par-&gt;panel_ymul
op_assign
id|is_dual
c_func
(paren
id|panel
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
id|par-&gt;panel_yres
op_assign
(paren
(paren
id|e1355_read_reg16
c_func
(paren
l_int|0x08
)paren
op_plus
l_int|1
)paren
op_star
id|par-&gt;panel_ymul
)paren
suffix:semicolon
)brace
DECL|function|e1355_get_par
r_static
r_void
id|e1355_get_par
c_func
(paren
r_void
op_star
id|raw_par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
r_struct
id|e1355_par
op_star
id|par
op_assign
id|raw_par
suffix:semicolon
id|get_panel_data
c_func
(paren
id|par
)paren
suffix:semicolon
)brace
DECL|function|e1355_set_par
r_static
r_void
id|e1355_set_par
c_func
(paren
r_const
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
)brace
DECL|function|e1355_getcolreg
r_static
r_int
id|e1355_getcolreg
c_func
(paren
r_int
id|regno
comma
r_int
op_star
id|red
comma
r_int
op_star
id|green
comma
r_int
op_star
id|blue
comma
r_int
op_star
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|u8
id|r
comma
id|g
comma
id|b
suffix:semicolon
id|e1355_write_reg
c_func
(paren
id|regno
comma
id|E1355_LUT_INDEX
)paren
suffix:semicolon
id|r
op_assign
id|e1355_read_reg
c_func
(paren
id|E1355_LUT_DATA
)paren
suffix:semicolon
id|g
op_assign
id|e1355_read_reg
c_func
(paren
id|E1355_LUT_DATA
)paren
suffix:semicolon
id|b
op_assign
id|e1355_read_reg
c_func
(paren
id|E1355_LUT_DATA
)paren
suffix:semicolon
op_star
id|red
op_assign
id|r
op_lshift
l_int|8
suffix:semicolon
op_star
id|green
op_assign
id|g
op_lshift
l_int|8
suffix:semicolon
op_star
id|blue
op_assign
id|b
op_lshift
l_int|8
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|e1355fb_setcolreg
r_static
r_int
id|e1355fb_setcolreg
c_func
(paren
r_int
id|regno
comma
r_int
id|red
comma
r_int
id|green
comma
r_int
id|blue
comma
r_int
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|u8
id|r
op_assign
(paren
id|red
op_rshift
l_int|8
)paren
op_amp
l_int|0xf0
suffix:semicolon
id|u8
id|g
op_assign
(paren
id|green
op_rshift
l_int|8
)paren
op_amp
l_int|0xf0
suffix:semicolon
id|u8
id|b
op_assign
(paren
id|blue
op_rshift
l_int|8
)paren
op_amp
l_int|0xf0
suffix:semicolon
id|e1355_write_reg
c_func
(paren
id|regno
comma
id|E1355_LUT_INDEX
)paren
suffix:semicolon
id|e1355_write_reg
c_func
(paren
id|r
comma
id|E1355_LUT_DATA
)paren
suffix:semicolon
id|e1355_write_reg
c_func
(paren
id|g
comma
id|E1355_LUT_DATA
)paren
suffix:semicolon
id|e1355_write_reg
c_func
(paren
id|b
comma
id|E1355_LUT_DATA
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|e1355_pan_display
r_static
r_int
id|e1355_pan_display
c_func
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * The AERO_HACKS parts disable/enable the backlight on the Compaq Aero 8000.&n; * I&squot;m not sure they aren&squot;t dangerous to the hardware, so be warned.&n; */
DECL|macro|AERO_HACKS
macro_line|#undef AERO_HACKS
DECL|function|e1355_blank
r_static
r_int
id|e1355_blank
c_func
(paren
r_int
id|blank_mode
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
id|u8
id|disp
suffix:semicolon
r_switch
c_cond
(paren
id|blank_mode
)paren
(brace
r_case
id|VESA_NO_BLANKING
suffix:colon
id|disp
op_assign
id|e1355_read_reg
c_func
(paren
id|E1355_DISPLAY
)paren
suffix:semicolon
id|disp
op_or_assign
l_int|1
suffix:semicolon
id|e1355_write_reg
c_func
(paren
id|disp
comma
id|E1355_DISPLAY
)paren
suffix:semicolon
macro_line|#ifdef AERO_HACKS
id|e1355_write_reg
c_func
(paren
l_int|0x6
comma
l_int|0x20
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
id|VESA_VSYNC_SUSPEND
suffix:colon
r_case
id|VESA_HSYNC_SUSPEND
suffix:colon
r_case
id|VESA_POWERDOWN
suffix:colon
id|disp
op_assign
id|e1355_read_reg
c_func
(paren
id|E1355_DISPLAY
)paren
suffix:semicolon
id|disp
op_and_assign
op_complement
l_int|1
suffix:semicolon
id|e1355_write_reg
c_func
(paren
id|disp
comma
id|E1355_DISPLAY
)paren
suffix:semicolon
macro_line|#ifdef AERO_HACKS
id|e1355_write_reg
c_func
(paren
l_int|0x0
comma
l_int|0x20
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|e1355_dispsw
r_static
r_struct
id|display_switch
id|e1355_dispsw
suffix:semicolon
DECL|function|e1355_set_disp
r_static
r_void
id|e1355_set_disp
c_func
(paren
r_const
r_void
op_star
id|unused
comma
r_struct
id|display
op_star
id|disp
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
r_struct
id|display_switch
op_star
id|d
suffix:semicolon
id|disp-&gt;dispsw
op_assign
op_amp
id|e1355_dispsw
suffix:semicolon
r_switch
c_cond
(paren
id|disp-&gt;var.bits_per_pixel
)paren
(brace
macro_line|#ifdef FBCON_HAS_MFB
r_case
l_int|1
suffix:colon
id|d
op_assign
op_amp
id|fbcon_mfb
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif&t;       
macro_line|#ifdef FBCON_HAS_CFB8
r_case
l_int|8
suffix:colon
id|d
op_assign
op_amp
id|fbcon_cfb8
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|e1355_dispsw
comma
id|d
comma
r_sizeof
op_star
id|d
)paren
suffix:semicolon
multiline_comment|/* reading is terribly slow for us */
macro_line|#if 0 /* XXX: need to work out why this doesn&squot;t work */
id|e1355_dispsw.bmove
op_assign
id|fbcon_redraw_bmove
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* ------------ Interfaces to hardware functions ------------ */
DECL|variable|e1355_switch
r_struct
id|fbgen_hwswitch
id|e1355_switch
op_assign
(brace
id|detect
suffix:colon
id|e1355_detect
comma
id|encode_fix
suffix:colon
id|e1355_encode_fix
comma
id|decode_var
suffix:colon
id|e1355_decode_var
comma
id|encode_var
suffix:colon
id|e1355_encode_var
comma
id|get_par
suffix:colon
id|e1355_get_par
comma
id|set_par
suffix:colon
id|e1355_set_par
comma
id|getcolreg
suffix:colon
id|e1355_getcolreg
comma
id|pan_display
suffix:colon
id|e1355_pan_display
comma
id|blank
suffix:colon
id|e1355_blank
comma
id|set_disp
suffix:colon
id|e1355_set_disp
comma
)brace
suffix:semicolon
multiline_comment|/* ------------ Hardware Independent Functions ------------ */
DECL|variable|e1355fb_ops
r_static
r_struct
id|fb_ops
id|e1355fb_ops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|fb_get_fix
suffix:colon
id|fbgen_get_fix
comma
id|fb_get_var
suffix:colon
id|fbgen_get_var
comma
id|fb_set_var
suffix:colon
id|fbgen_set_var
comma
id|fb_get_cmap
suffix:colon
id|fbgen_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|fbgen_set_cmap
comma
id|fb_setcolreg
suffix:colon
id|e1355fb_setcolreg
comma
id|fb_pan_display
suffix:colon
id|fbgen_pan_display
comma
id|fb_blank
suffix:colon
id|fbgen_blank
comma
)brace
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|e1355fb_info
id|fb_info
suffix:semicolon
DECL|function|e1355fb_setup
r_int
id|__init
id|e1355fb_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|e1355fb_init
r_int
id|__init
id|e1355fb_init
c_func
(paren
r_void
)paren
(brace
id|fb_info.gen.fbhw
op_assign
op_amp
id|e1355_switch
suffix:semicolon
id|fb_info.gen.fbhw
op_member_access_from_pointer
id|detect
c_func
(paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_info.gen.info.modename
comma
l_string|&quot;SED1355&quot;
)paren
suffix:semicolon
id|fb_info.gen.info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.gen.info.node
op_assign
id|NODEV
suffix:semicolon
id|fb_info.gen.info.fbops
op_assign
op_amp
id|e1355fb_ops
suffix:semicolon
id|fb_info.gen.info.screen_base
op_assign
(paren
r_void
op_star
)paren
id|E1355_FB_BASE
suffix:semicolon
id|fb_info.gen.currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.gen.info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.gen.parsize
op_assign
r_sizeof
(paren
r_struct
id|e1355_par
)paren
suffix:semicolon
id|fb_info.gen.info.switch_con
op_assign
op_amp
id|fbgen_switch
suffix:semicolon
id|fb_info.gen.info.updatevar
op_assign
op_amp
id|fbgen_update_var
suffix:semicolon
id|fb_info.gen.info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
multiline_comment|/* This should give a reasonable default video mode */
id|fbgen_get_var
c_func
(paren
op_amp
id|disp.var
comma
op_minus
l_int|1
comma
op_amp
id|fb_info.gen.info
)paren
suffix:semicolon
id|fbgen_do_set_var
c_func
(paren
op_amp
id|disp.var
comma
l_int|1
comma
op_amp
id|fb_info.gen
)paren
suffix:semicolon
id|fbgen_set_disp
c_func
(paren
op_minus
l_int|1
comma
op_amp
id|fb_info.gen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disp.var.bits_per_pixel
OG
l_int|1
)paren
id|fbgen_install_cmap
c_func
(paren
l_int|0
comma
op_amp
id|fb_info.gen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info.gen.info
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
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.gen.info.node
)paren
comma
id|fb_info.gen.info.modename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Cleanup&n;     */
DECL|function|e1355fb_cleanup
r_void
id|e1355fb_cleanup
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;&t; *  If your driver supports multiple boards, you should unregister and&n;&t; *  clean up all instances.&n;&t; */
id|unregister_framebuffer
c_func
(paren
id|info
)paren
suffix:semicolon
multiline_comment|/* ... */
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
