multiline_comment|/*&n; *  linux/drivers/video/68328fb.c -- Low level implementation of the&n; *                                   mc68x328 LCD frame buffer device&n; *&n; *&t;Copyright (C) 2003 Georges Menie&n; *&n; *  This driver assumes an already configured controller (e.g. from config.c)&n; *  Keep the code clean of board specific initialization.&n; *&n; *  This code has not been tested with colors, colormap management functions&n; *  are minimal (no colormap data written to the 68328 registers...)&n; *&n; *  initial version of this driver:&n; *    Copyright (C) 1998,1999 Kenneth Albanowski &lt;kjahds@kjahds.com&gt;,&n; *                            The Silver Hammer Group, Ltd.&n; *&n; *  this version is based on :&n; *&n; *  linux/drivers/video/vfb.c -- Virtual frame buffer device&n; *&n; *      Copyright (C) 2002 James Simmons&n; *&n; *&t;Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#if defined(CONFIG_M68VZ328)
macro_line|#include &lt;asm/MC68VZ328.h&gt;
macro_line|#elif defined(CONFIG_M68EZ328)
macro_line|#include &lt;asm/MC68EZ328.h&gt;
macro_line|#elif defined(CONFIG_M68328)
macro_line|#include &lt;asm/MC68328.h&gt;
macro_line|#else
macro_line|#error wrong architecture for the MC68x328 frame buffer device
macro_line|#endif
macro_line|#if defined(CONFIG_FB_68328_INVERT)
DECL|macro|MC68X328FB_MONO_VISUAL
mdefine_line|#define MC68X328FB_MONO_VISUAL FB_VISUAL_MONO01
macro_line|#else
DECL|macro|MC68X328FB_MONO_VISUAL
mdefine_line|#define MC68X328FB_MONO_VISUAL FB_VISUAL_MONO10
macro_line|#endif
DECL|variable|videomemory
r_static
id|u_long
id|videomemory
suffix:semicolon
DECL|variable|videomemorysize
r_static
id|u_long
id|videomemorysize
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|variable|mc68x328fb_pseudo_palette
r_static
id|u32
id|mc68x328fb_pseudo_palette
(braket
l_int|17
)braket
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|fb_var_screeninfo
id|mc68x328fb_default
id|__initdata
op_assign
(brace
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
dot
id|green
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|blue
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|activate
op_assign
id|FB_ACTIVATE_TEST
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
id|pixclock
op_assign
l_int|20000
comma
dot
id|left_margin
op_assign
l_int|64
comma
dot
id|right_margin
op_assign
l_int|64
comma
dot
id|upper_margin
op_assign
l_int|32
comma
dot
id|lower_margin
op_assign
l_int|32
comma
dot
id|hsync_len
op_assign
l_int|64
comma
dot
id|vsync_len
op_assign
l_int|2
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
id|mc68x328fb_fix
id|__initdata
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;68328fb&quot;
comma
dot
id|type
op_assign
id|FB_TYPE_PACKED_PIXELS
comma
dot
id|xpanstep
op_assign
l_int|1
comma
dot
id|ypanstep
op_assign
l_int|1
comma
dot
id|ywrapstep
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
multiline_comment|/*&n;     *  Interface used by the world&n;     */
r_int
id|mc68x328fb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|mc68x328fb_setup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_static
r_int
id|mc68x328fb_check_var
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
id|mc68x328fb_set_par
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|mc68x328fb_setcolreg
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
id|mc68x328fb_pan_display
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
id|mc68x328fb_mmap
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
DECL|variable|mc68x328fb_ops
r_static
r_struct
id|fb_ops
id|mc68x328fb_ops
op_assign
(brace
dot
id|fb_check_var
op_assign
id|mc68x328fb_check_var
comma
dot
id|fb_set_par
op_assign
id|mc68x328fb_set_par
comma
dot
id|fb_setcolreg
op_assign
id|mc68x328fb_setcolreg
comma
dot
id|fb_pan_display
op_assign
id|mc68x328fb_pan_display
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
id|soft_cursor
comma
dot
id|fb_mmap
op_assign
id|mc68x328fb_mmap
comma
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Internal routines&n;     */
DECL|function|get_line_length
r_static
id|u_long
id|get_line_length
c_func
(paren
r_int
id|xres_virtual
comma
r_int
id|bpp
)paren
(brace
id|u_long
id|length
suffix:semicolon
id|length
op_assign
id|xres_virtual
op_star
id|bpp
suffix:semicolon
id|length
op_assign
(paren
id|length
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
suffix:semicolon
id|length
op_rshift_assign
l_int|3
suffix:semicolon
r_return
(paren
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Setting the video mode has been split into two parts.&n;     *  First part, xxxfb_check_var, must not write anything&n;     *  to hardware, it should only verify and adjust var.&n;     *  This means it doesn&squot;t alter par but it does use hardware&n;     *  data from it to check this var. &n;     */
DECL|function|mc68x328fb_check_var
r_static
r_int
id|mc68x328fb_check_var
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
id|u_long
id|line_length
suffix:semicolon
multiline_comment|/*&n;&t; *  FB_VMODE_CONUPDATE and FB_VMODE_SMOOTH_XPAN are equal!&n;&t; *  as FB_VMODE_SMOOTH_XPAN is only used internally&n;&t; */
r_if
c_cond
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_CONUPDATE
)paren
(brace
id|var-&gt;vmode
op_or_assign
id|FB_VMODE_YWRAP
suffix:semicolon
id|var-&gt;xoffset
op_assign
id|info-&gt;var.xoffset
suffix:semicolon
id|var-&gt;yoffset
op_assign
id|info-&gt;var.yoffset
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Some very basic checks&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|var-&gt;xres
)paren
id|var-&gt;xres
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|var-&gt;yres
)paren
id|var-&gt;yres
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;xres
OG
id|var-&gt;xres_virtual
)paren
id|var-&gt;xres_virtual
op_assign
id|var-&gt;xres
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;yres
OG
id|var-&gt;yres_virtual
)paren
id|var-&gt;yres_virtual
op_assign
id|var-&gt;yres
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|1
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|8
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|8
suffix:semicolon
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|16
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|16
suffix:semicolon
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|24
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|24
suffix:semicolon
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|32
)paren
id|var-&gt;bits_per_pixel
op_assign
l_int|32
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;xres_virtual
OL
id|var-&gt;xoffset
op_plus
id|var-&gt;xres
)paren
id|var-&gt;xres_virtual
op_assign
id|var-&gt;xoffset
op_plus
id|var-&gt;xres
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;yres_virtual
OL
id|var-&gt;yoffset
op_plus
id|var-&gt;yres
)paren
id|var-&gt;yres_virtual
op_assign
id|var-&gt;yoffset
op_plus
id|var-&gt;yres
suffix:semicolon
multiline_comment|/*&n;&t; *  Memory limit&n;&t; */
id|line_length
op_assign
id|get_line_length
c_func
(paren
id|var-&gt;xres_virtual
comma
id|var-&gt;bits_per_pixel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line_length
op_star
id|var-&gt;yres_virtual
OG
id|videomemorysize
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/*&n;&t; * Now that we checked it we alter var. The reason being is that the video&n;&t; * mode passed in might not work but slight changes to it might make it &n;&t; * work. This way we let the user know what is acceptable.&n;&t; */
r_switch
c_cond
(paren
id|var-&gt;bits_per_pixel
)paren
(brace
r_case
l_int|1
suffix:colon
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|1
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|1
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|1
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
multiline_comment|/* RGBA 5551 */
r_if
c_cond
(paren
id|var-&gt;transp.length
)paren
(brace
id|var-&gt;red.offset
op_assign
l_int|0
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
l_int|5
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|10
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|15
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* RGB 565 */
id|var-&gt;red.offset
op_assign
l_int|0
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
l_int|11
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
)brace
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
multiline_comment|/* RGB 888 */
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
l_int|8
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|16
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
l_int|32
suffix:colon
multiline_comment|/* RGBA 8888 */
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
l_int|8
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|16
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|24
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
id|var-&gt;red.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.msb_right
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This routine actually sets the video mode. It&squot;s in here where we&n; * the hardware state info-&gt;par and fix which can be affected by the &n; * change in par. For this driver it doesn&squot;t do much. &n; */
DECL|function|mc68x328fb_set_par
r_static
r_int
id|mc68x328fb_set_par
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|info-&gt;fix.line_length
op_assign
id|get_line_length
c_func
(paren
id|info-&gt;var.xres_virtual
comma
id|info-&gt;var.bits_per_pixel
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Set a single color register. The values supplied are already&n;     *  rounded down to the hardware&squot;s capabilities (according to the&n;     *  entries in the var structure). Return != 0 for invalid regno.&n;     */
DECL|function|mc68x328fb_setcolreg
r_static
r_int
id|mc68x328fb_setcolreg
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
r_if
c_cond
(paren
id|regno
op_ge
l_int|256
)paren
multiline_comment|/* no. of hw registers */
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Program hardware... do anything you want with transp&n;&t; */
multiline_comment|/* grayscale works only partially under directcolor */
r_if
c_cond
(paren
id|info-&gt;var.grayscale
)paren
(brace
multiline_comment|/* grayscale = 0.30*R + 0.59*G + 0.11*B */
id|red
op_assign
id|green
op_assign
id|blue
op_assign
(paren
id|red
op_star
l_int|77
op_plus
id|green
op_star
l_int|151
op_plus
id|blue
op_star
l_int|28
)paren
op_rshift
l_int|8
suffix:semicolon
)brace
multiline_comment|/* Directcolor:&n;&t; *   var-&gt;{color}.offset contains start of bitfield&n;&t; *   var-&gt;{color}.length contains length of bitfield&n;&t; *   {hardwarespecific} contains width of RAMDAC&n;&t; *   cmap[X] is programmed to (X &lt;&lt; red.offset) | (X &lt;&lt; green.offset) | (X &lt;&lt; blue.offset)&n;&t; *   RAMDAC[X] is programmed to (red, green, blue)&n;&t; * &n;&t; * Pseudocolor:&n;&t; *    uses offset = 0 &amp;&amp; length = RAMDAC register width.&n;&t; *    var-&gt;{color}.offset is 0&n;&t; *    var-&gt;{color}.length contains widht of DAC&n;&t; *    cmap is not used&n;&t; *    RAMDAC[X] is programmed to (red, green, blue)&n;&t; * Truecolor:&n;&t; *    does not use DAC. Usually 3 are present.&n;&t; *    var-&gt;{color}.offset contains start of bitfield&n;&t; *    var-&gt;{color}.length contains length of bitfield&n;&t; *    cmap is programmed to (red &lt;&lt; red.offset) | (green &lt;&lt; green.offset) |&n;&t; *                      (blue &lt;&lt; blue.offset) | (transp &lt;&lt; transp.offset)&n;&t; *    RAMDAC does not exist&n;&t; */
DECL|macro|CNVT_TOHW
mdefine_line|#define CNVT_TOHW(val,width) ((((val)&lt;&lt;(width))+0x7FFF-(val))&gt;&gt;16)
r_switch
c_cond
(paren
id|info-&gt;fix.visual
)paren
(brace
r_case
id|FB_VISUAL_TRUECOLOR
suffix:colon
r_case
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|red
op_assign
id|CNVT_TOHW
c_func
(paren
id|red
comma
id|info-&gt;var.red.length
)paren
suffix:semicolon
id|green
op_assign
id|CNVT_TOHW
c_func
(paren
id|green
comma
id|info-&gt;var.green.length
)paren
suffix:semicolon
id|blue
op_assign
id|CNVT_TOHW
c_func
(paren
id|blue
comma
id|info-&gt;var.blue.length
)paren
suffix:semicolon
id|transp
op_assign
id|CNVT_TOHW
c_func
(paren
id|transp
comma
id|info-&gt;var.transp.length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FB_VISUAL_DIRECTCOLOR
suffix:colon
id|red
op_assign
id|CNVT_TOHW
c_func
(paren
id|red
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* expect 8 bit DAC */
id|green
op_assign
id|CNVT_TOHW
c_func
(paren
id|green
comma
l_int|8
)paren
suffix:semicolon
id|blue
op_assign
id|CNVT_TOHW
c_func
(paren
id|blue
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* hey, there is bug in transp handling... */
id|transp
op_assign
id|CNVT_TOHW
c_func
(paren
id|transp
comma
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
DECL|macro|CNVT_TOHW
macro_line|#undef CNVT_TOHW
multiline_comment|/* Truecolor has hardware independent palette */
r_if
c_cond
(paren
id|info-&gt;fix.visual
op_eq
id|FB_VISUAL_TRUECOLOR
)paren
(brace
id|u32
id|v
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_ge
l_int|16
)paren
r_return
l_int|1
suffix:semicolon
id|v
op_assign
(paren
id|red
op_lshift
id|info-&gt;var.red.offset
)paren
op_or
(paren
id|green
op_lshift
id|info-&gt;var.green.offset
)paren
op_or
(paren
id|blue
op_lshift
id|info-&gt;var.blue.offset
)paren
op_or
(paren
id|transp
op_lshift
id|info-&gt;var.transp.offset
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|info-&gt;var.bits_per_pixel
)paren
(brace
r_case
l_int|8
suffix:colon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
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
id|regno
)braket
op_assign
id|v
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
r_case
l_int|32
suffix:colon
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
id|regno
)braket
op_assign
id|v
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Pan or Wrap the Display&n;     *&n;     *  This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag&n;     */
DECL|function|mc68x328fb_pan_display
r_static
r_int
id|mc68x328fb_pan_display
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
id|var-&gt;vmode
op_amp
id|FB_VMODE_YWRAP
)paren
(brace
r_if
c_cond
(paren
id|var-&gt;yoffset
OL
l_int|0
op_logical_or
id|var-&gt;yoffset
op_ge
id|info-&gt;var.yres_virtual
op_logical_or
id|var-&gt;xoffset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|var-&gt;xoffset
op_plus
id|var-&gt;xres
OG
id|info-&gt;var.xres_virtual
op_logical_or
id|var-&gt;yoffset
op_plus
id|var-&gt;yres
OG
id|info-&gt;var.yres_virtual
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|info-&gt;var.xoffset
op_assign
id|var-&gt;xoffset
suffix:semicolon
id|info-&gt;var.yoffset
op_assign
id|var-&gt;yoffset
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_YWRAP
)paren
id|info-&gt;var.vmode
op_or_assign
id|FB_VMODE_YWRAP
suffix:semicolon
r_else
id|info-&gt;var.vmode
op_and_assign
op_complement
id|FB_VMODE_YWRAP
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Most drivers don&squot;t need their own mmap function &n;     */
DECL|function|mc68x328fb_mmap
r_static
r_int
id|mc68x328fb_mmap
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
macro_line|#ifndef MMU
multiline_comment|/* this is uClinux (no MMU) specific code */
id|vma-&gt;vm_flags
op_or_assign
id|VM_RESERVED
suffix:semicolon
id|vma-&gt;vm_start
op_assign
id|videomemory
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#else
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
)brace
DECL|function|mc68x328fb_setup
r_int
id|__init
id|mc68x328fb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
macro_line|#if 0
r_char
op_star
id|this_opt
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|options
op_logical_or
op_logical_neg
op_star
id|options
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#if 0
r_while
c_loop
(paren
(paren
id|this_opt
op_assign
id|strsep
c_func
(paren
op_amp
id|options
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|this_opt
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|this_opt
comma
l_string|&quot;disable&quot;
comma
l_int|7
)paren
)paren
id|mc68x328fb_enable
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Initialisation&n;     */
DECL|function|mc68x328fb_init
r_int
id|__init
id|mc68x328fb_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef MODULE
r_char
op_star
id|option
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|fb_get_options
c_func
(paren
l_string|&quot;68328fb&quot;
comma
op_amp
id|option
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|mc68x328fb_setup
c_func
(paren
id|option
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  initialize the default mode from the LCD controller registers&n;&t; */
id|mc68x328fb_default.xres
op_assign
id|LXMAX
suffix:semicolon
id|mc68x328fb_default.yres
op_assign
id|LYMAX
op_plus
l_int|1
suffix:semicolon
id|mc68x328fb_default.xres_virtual
op_assign
id|mc68x328fb_default.xres
suffix:semicolon
id|mc68x328fb_default.yres_virtual
op_assign
id|mc68x328fb_default.yres
suffix:semicolon
id|mc68x328fb_default.bits_per_pixel
op_assign
l_int|1
op_plus
(paren
id|LPICF
op_amp
l_int|0x01
)paren
suffix:semicolon
id|videomemory
op_assign
id|LSSA
suffix:semicolon
id|videomemorysize
op_assign
(paren
id|mc68x328fb_default.xres_virtual
op_plus
l_int|7
)paren
op_div
l_int|8
op_star
id|mc68x328fb_default.yres_virtual
op_star
id|mc68x328fb_default.bits_per_pixel
suffix:semicolon
id|fb_info.screen_base
op_assign
(paren
r_void
op_star
)paren
id|videomemory
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|mc68x328fb_ops
suffix:semicolon
id|fb_info.var
op_assign
id|mc68x328fb_default
suffix:semicolon
id|fb_info.fix
op_assign
id|mc68x328fb_fix
suffix:semicolon
id|fb_info.fix.smem_start
op_assign
id|videomemory
suffix:semicolon
id|fb_info.fix.smem_len
op_assign
id|videomemorysize
suffix:semicolon
id|fb_info.fix.line_length
op_assign
id|get_line_length
c_func
(paren
id|mc68x328fb_default.xres_virtual
comma
id|mc68x328fb_default.bits_per_pixel
)paren
suffix:semicolon
id|fb_info.fix.visual
op_assign
(paren
id|mc68x328fb_default.bits_per_pixel
)paren
op_eq
l_int|1
ques
c_cond
id|MC68X328FB_MONO_VISUAL
suffix:colon
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
r_if
c_cond
(paren
id|fb_info.var.bits_per_pixel
op_eq
l_int|1
)paren
(brace
id|fb_info.var.red.length
op_assign
id|fb_info.var.green.length
op_assign
id|fb_info.var.blue.length
op_assign
l_int|1
suffix:semicolon
id|fb_info.var.red.offset
op_assign
id|fb_info.var.green.offset
op_assign
id|fb_info.var.blue.offset
op_assign
l_int|0
suffix:semicolon
)brace
id|fb_info.pseudo_palette
op_assign
op_amp
id|mc68x328fb_pseudo_palette
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_DEFAULT
op_or
id|FBINFO_HWACCEL_YPAN
suffix:semicolon
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb_info.cmap
comma
l_int|256
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
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|fb_info.node
comma
id|fb_info.fix.id
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: %dx%dx%d at 0x%08lx&bslash;n&quot;
comma
id|fb_info.node
comma
id|mc68x328fb_default.xres_virtual
comma
id|mc68x328fb_default.yres_virtual
comma
l_int|1
op_lshift
id|mc68x328fb_default.bits_per_pixel
comma
id|videomemory
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mc68x328fb_init
id|module_init
c_func
(paren
id|mc68x328fb_init
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|mc68x328fb_cleanup
r_static
r_void
id|__exit
id|mc68x328fb_cleanup
c_func
(paren
r_void
)paren
(brace
id|unregister_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
suffix:semicolon
)brace
DECL|variable|mc68x328fb_cleanup
id|module_exit
c_func
(paren
id|mc68x328fb_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* MODULE */
eof
