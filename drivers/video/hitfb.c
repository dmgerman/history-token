multiline_comment|/*&n; * $Id: hitfb.c,v 1.2 2000/07/04 06:24:46 yaegashi Exp $&n; * linux/drivers/video/hitfb.c -- Hitachi LCD frame buffer device&n; * (C) 1999 Mihai Spatar&n; * (C) 2000 YAEGASHI Takeshi&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/nubus.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hd64461.h&gt;
DECL|variable|__initdata
r_static
r_struct
id|fb_var_screeninfo
id|hitfb_var
id|__initdata
op_assign
(brace
dot
id|activate
op_assign
id|FB_ACTIVATE_NOW
comma
dot
id|height
op_assign
op_minus
l_int|1
comma
dot
id|width
op_assign
op_minus
l_int|1
comma
dot
id|vmode
op_assign
id|FB_VMODE_NONINTERLACED
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|fb_fix_screeninfo
id|hitfb_fix
id|__initdata
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;Hitachi HD64461&quot;
comma
dot
id|type
op_assign
id|FB_TYPE_PACKED_PIXELS
comma
dot
id|visual
op_assign
id|FB_VISUAL_TRUECOLOR
comma
dot
id|accel_flags
op_assign
id|FB_ACCEL_NONE
comma
)brace
suffix:semicolon
DECL|variable|pseudo_palette
r_static
id|u16
id|pseudo_palette
(braket
l_int|17
)braket
suffix:semicolon
DECL|variable|fb_info
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|function|hitfb_check_var
r_static
r_int
id|hitfb_check_var
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
id|var-&gt;xres_virtual
op_assign
id|var-&gt;xres
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
id|var-&gt;yres
suffix:semicolon
r_switch
c_cond
(paren
id|var-&gt;bits_per_pixel
)paren
(brace
r_case
l_int|8
suffix:colon
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
multiline_comment|/* RGB 565 */
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
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hitfb_set_par
r_static
r_int
id|hitfb_set_par
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|info-&gt;fix.visual
op_assign
(paren
id|info-&gt;var.bits_per_pixel
op_eq
l_int|8
)paren
ques
c_cond
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
r_switch
c_cond
(paren
id|info-&gt;var.bits_per_pixel
)paren
(brace
r_default
suffix:colon
r_case
l_int|8
suffix:colon
id|info-&gt;fix.line_length
op_assign
id|info-&gt;var.xres
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|info-&gt;fix.line_length
op_assign
id|info-&gt;var.xres
op_star
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hitfb_setcolreg
r_static
r_int
id|hitfb_setcolreg
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
id|outw
c_func
(paren
id|regno
op_lshift
l_int|8
comma
id|HD64461_CPTWAR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|red
op_rshift
l_int|10
comma
id|HD64461_CPTWDR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|green
op_rshift
l_int|10
comma
id|HD64461_CPTWDR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|blue
op_rshift
l_int|10
comma
id|HD64461_CPTWDR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regno
OL
l_int|16
)paren
(brace
r_switch
c_cond
(paren
id|info-&gt;var.bits_per_pixel
)paren
(brace
macro_line|#ifdef FBCON_HAS_CFB16
r_case
l_int|16
suffix:colon
(paren
(paren
id|u16
op_star
)paren
(paren
id|info-&gt;pseudo_palette
)paren
)paren
(braket
id|regno
)braket
op_assign
(paren
(paren
id|red
op_amp
l_int|0xf800
)paren
)paren
op_or
(paren
(paren
id|green
op_amp
l_int|0xfc00
)paren
op_rshift
l_int|5
)paren
op_or
(paren
(paren
id|blue
op_amp
l_int|0xf800
)paren
op_rshift
l_int|11
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hitfb_ops
r_static
r_struct
id|fb_ops
id|hitfb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_set_var
op_assign
id|gen_set_var
comma
dot
id|fb_check_var
op_assign
id|hitfb_check_var
comma
dot
id|fb_set_par
op_assign
id|hitfb_set_par
comma
dot
id|fb_setcolreg
op_assign
id|hitfb_setcolreg
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
)brace
suffix:semicolon
DECL|function|hitfb_init
r_int
id|__init
id|hitfb_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|lcdclor
comma
id|ldr3
comma
id|ldvntr
suffix:semicolon
id|hitfb_fix.smem_start
op_assign
id|CONFIG_HD64461_IOBASE
op_plus
l_int|0x02000000
suffix:semicolon
id|hitfb_fix.smem_len
op_assign
(paren
id|MACH_HP680
op_logical_or
id|MACH_HP690
)paren
ques
c_cond
l_int|1024
op_star
l_int|1024
suffix:colon
l_int|512
op_star
l_int|1024
suffix:semicolon
id|lcdclor
op_assign
id|inw
c_func
(paren
id|HD64461_LCDCLOR
)paren
suffix:semicolon
id|ldvntr
op_assign
id|inw
c_func
(paren
id|HD64461_LDVNTR
)paren
suffix:semicolon
id|ldr3
op_assign
id|inw
c_func
(paren
id|HD64461_LDR3
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ldr3
op_amp
l_int|15
)paren
(brace
r_default
suffix:colon
r_case
l_int|4
suffix:colon
id|hitfb_var.bits_per_pixel
op_assign
l_int|8
suffix:semicolon
id|hitfb_var.xres
op_assign
id|lcdclor
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|hitfb_var.bits_per_pixel
op_assign
l_int|16
suffix:semicolon
id|hitfb_var.xres
op_assign
id|lcdclor
op_div
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
id|hitfb_var.yres
op_assign
id|ldvntr
op_plus
l_int|1
suffix:semicolon
id|fb_info.node
op_assign
id|NODEV
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|hitfb_ops
suffix:semicolon
id|fb_info.var
op_assign
id|hitfb_var
suffix:semicolon
id|fb_info.fix
op_assign
id|hitfb_fix
suffix:semicolon
id|fb_info.pseudo_palette
op_assign
id|pseudo_palette
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|fb_info.currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.updatevar
op_assign
id|gen_update_var
suffix:semicolon
id|fb_info.screen_base
op_assign
(paren
r_void
op_star
)paren
id|hitfb_fix.smem_start
suffix:semicolon
id|size
op_assign
(paren
id|fb_info.var.bits_per_pixel
op_eq
l_int|8
)paren
ques
c_cond
l_int|256
suffix:colon
l_int|16
suffix:semicolon
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb_info.cmap
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
id|gen_set_var
c_func
(paren
op_amp
id|fb_info.var
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
id|KERN_INFO
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.node
)paren
comma
id|fb_info.fix.id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hitfb_cleanup
r_void
id|hitfb_cleanup
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|unregister_framebuffer
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
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
id|hitfb_init
c_func
(paren
)paren
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
id|hitfb_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 4&n; * End:&n; */
eof
