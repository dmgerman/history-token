multiline_comment|/*&n; *  linux/drivers/video/vfb.c -- Virtual frame buffer device&n; *&n; *      Copyright (C) 2002 James Simmons&n; *&n; *&t;Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
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
multiline_comment|/*&n;     *  RAM we reserve for the frame buffer. This defines the maximum screen&n;     *  size&n;     *&n;     *  The default can be overridden if the driver is compiled as a module&n;     */
DECL|macro|VIDEOMEMSIZE
mdefine_line|#define VIDEOMEMSIZE&t;(1*1024*1024)&t;/* 1 MB */
DECL|variable|videomemory
r_static
r_void
op_star
id|videomemory
suffix:semicolon
DECL|variable|videomemorysize
r_static
id|u_long
id|videomemorysize
op_assign
id|VIDEOMEMSIZE
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|videomemorysize
comma
l_string|&quot;l&quot;
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|fb_var_screeninfo
id|vfb_default
id|__initdata
op_assign
(brace
dot
id|xres
op_assign
l_int|640
comma
dot
id|yres
op_assign
l_int|480
comma
dot
id|xres_virtual
op_assign
l_int|640
comma
dot
id|yres_virtual
op_assign
l_int|480
comma
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
id|vfb_fix
id|__initdata
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;Virtual FB&quot;
comma
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
DECL|variable|__initdata
r_static
r_int
id|vfb_enable
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disabled by default */
id|MODULE_PARM
c_func
(paren
id|vfb_enable
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Interface used by the world&n;     */
r_int
id|vfb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|vfb_setup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_static
r_int
id|vfb_check_var
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
id|vfb_set_par
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
id|vfb_setcolreg
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
id|vfb_pan_display
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
id|vfb_mmap
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
DECL|variable|vfb_ops
r_static
r_struct
id|fb_ops
id|vfb_ops
op_assign
(brace
dot
id|fb_check_var
op_assign
id|vfb_check_var
comma
dot
id|fb_set_par
op_assign
id|vfb_set_par
comma
dot
id|fb_setcolreg
op_assign
id|vfb_setcolreg
comma
dot
id|fb_pan_display
op_assign
id|vfb_pan_display
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
id|vfb_mmap
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
DECL|function|vfb_check_var
r_static
r_int
id|vfb_check_var
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
DECL|function|vfb_set_par
r_static
r_int
id|vfb_set_par
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
DECL|function|vfb_setcolreg
r_static
r_int
id|vfb_setcolreg
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
DECL|function|vfb_pan_display
r_static
r_int
id|vfb_pan_display
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
DECL|function|vfb_mmap
r_static
r_int
id|vfb_mmap
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|vfb_setup
r_int
id|__init
id|vfb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
r_char
op_star
id|this_opt
suffix:semicolon
id|vfb_enable
op_assign
l_int|1
suffix:semicolon
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
id|vfb_enable
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Initialisation&n;     */
DECL|function|vfb_platform_release
r_static
r_void
id|vfb_platform_release
c_func
(paren
r_struct
id|device
op_star
id|device
)paren
(brace
singleline_comment|// This is called when the reference count goes to zero.
)brace
DECL|function|vfb_probe
r_static
r_int
id|__init
id|vfb_probe
c_func
(paren
r_struct
id|device
op_star
id|device
)paren
(brace
r_struct
id|platform_device
op_star
id|dev
op_assign
id|to_platform_device
c_func
(paren
id|device
)paren
suffix:semicolon
r_struct
id|fb_info
op_star
id|info
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/*&n;&t; * For real video cards we use ioremap.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|videomemory
op_assign
id|vmalloc
c_func
(paren
id|videomemorysize
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/*&n;&t; * VFB must clear memory to prevent kernel info&n;&t; * leakage into userspace&n;&t; * VGA-based drivers MUST NOT clear memory if&n;&t; * they want to be able to take over vgacon&n;&t; */
id|memset
c_func
(paren
id|videomemory
comma
l_int|0
comma
id|videomemorysize
)paren
suffix:semicolon
id|info
op_assign
id|framebuffer_alloc
c_func
(paren
r_sizeof
(paren
id|u32
)paren
op_star
l_int|256
comma
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
r_goto
id|err
suffix:semicolon
id|info-&gt;screen_base
op_assign
id|videomemory
suffix:semicolon
id|info-&gt;fbops
op_assign
op_amp
id|vfb_ops
suffix:semicolon
id|retval
op_assign
id|fb_find_mode
c_func
(paren
op_amp
id|info-&gt;var
comma
id|info
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_or
(paren
id|retval
op_eq
l_int|4
)paren
)paren
id|info-&gt;var
op_assign
id|vfb_default
suffix:semicolon
id|info-&gt;fix
op_assign
id|vfb_fix
suffix:semicolon
id|info-&gt;pseudo_palette
op_assign
id|info-&gt;par
suffix:semicolon
id|info-&gt;par
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|retval
op_assign
id|fb_alloc_cmap
c_func
(paren
op_amp
id|info-&gt;cmap
comma
l_int|256
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err1
suffix:semicolon
id|retval
op_assign
id|register_framebuffer
c_func
(paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err2
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
op_amp
id|dev-&gt;dev
comma
id|info
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: Virtual frame buffer device, using %ldK of video memory&bslash;n&quot;
comma
id|info-&gt;node
comma
id|videomemorysize
op_rshift
l_int|10
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err2
suffix:colon
id|fb_dealloc_cmap
c_func
(paren
op_amp
id|info-&gt;cmap
)paren
suffix:semicolon
id|err1
suffix:colon
id|framebuffer_release
c_func
(paren
id|info
)paren
suffix:semicolon
id|err
suffix:colon
id|vfree
c_func
(paren
id|videomemory
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|vfb_remove
r_static
r_int
id|vfb_remove
c_func
(paren
r_struct
id|device
op_star
id|device
)paren
(brace
r_struct
id|fb_info
op_star
id|info
op_assign
id|dev_get_drvdata
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
)paren
(brace
id|unregister_framebuffer
c_func
(paren
id|info
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|videomemory
)paren
suffix:semicolon
id|framebuffer_release
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vfb_driver
r_static
r_struct
id|device_driver
id|vfb_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;vfb&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
dot
id|probe
op_assign
id|vfb_probe
comma
dot
id|remove
op_assign
id|vfb_remove
comma
)brace
suffix:semicolon
DECL|variable|vfb_device
r_static
r_struct
id|platform_device
id|vfb_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;vfb&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev
op_assign
(brace
dot
id|release
op_assign
id|vfb_platform_release
comma
)brace
)brace
suffix:semicolon
DECL|function|vfb_init
r_int
id|__init
id|vfb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vfb_enable
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|ret
op_assign
id|driver_register
c_func
(paren
op_amp
id|vfb_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|ret
op_assign
id|platform_device_register
c_func
(paren
op_amp
id|vfb_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|driver_unregister
c_func
(paren
op_amp
id|vfb_driver
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|vfb_exit
r_static
r_void
id|__exit
id|vfb_exit
c_func
(paren
r_void
)paren
(brace
id|platform_device_unregister
c_func
(paren
op_amp
id|vfb_device
)paren
suffix:semicolon
id|driver_unregister
c_func
(paren
op_amp
id|vfb_driver
)paren
suffix:semicolon
)brace
DECL|variable|vfb_init
id|module_init
c_func
(paren
id|vfb_init
)paren
suffix:semicolon
DECL|variable|vfb_exit
id|module_exit
c_func
(paren
id|vfb_exit
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
