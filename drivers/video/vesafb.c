multiline_comment|/*&n; * framebuffer driver for VBE 2.0 compliant graphic boards&n; *&n; * switching to graphics mode happens at boot time (while&n; * running in real mode, see arch/i386/boot/video.S).&n; *&n; * (c) 1998 Gerd Knorr &lt;kraxel@goldbach.in-berlin.de&gt;&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef __i386__
macro_line|#include &lt;video/edid.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
DECL|macro|dac_reg
mdefine_line|#define dac_reg&t;(0x3c8)
DECL|macro|dac_val
mdefine_line|#define dac_val&t;(0x3c9)
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|__initdata
r_static
r_struct
id|fb_var_screeninfo
id|vesafb_defined
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
id|right_margin
op_assign
l_int|32
comma
dot
id|upper_margin
op_assign
l_int|16
comma
dot
id|lower_margin
op_assign
l_int|4
comma
dot
id|vsync_len
op_assign
l_int|4
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
id|vesafb_fix
id|__initdata
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;VESA VGA&quot;
comma
dot
id|type
op_assign
id|FB_TYPE_PACKED_PIXELS
comma
dot
id|accel
op_assign
id|FB_ACCEL_NONE
comma
)brace
suffix:semicolon
DECL|variable|inverse
r_static
r_int
id|inverse
op_assign
l_int|0
suffix:semicolon
DECL|variable|mtrr
r_static
r_int
id|mtrr
op_assign
l_int|1
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|vram_remap
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set amount of memory to be used */
DECL|variable|__initdata
r_static
r_int
id|vram_total
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set total amount of memory */
DECL|variable|pmi_setpal
r_static
r_int
id|pmi_setpal
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* pmi for palette changes ??? */
DECL|variable|ypan
r_static
r_int
id|ypan
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 0..nothing, 1..ypan, 2..ywrap */
DECL|variable|pmi_base
r_static
r_int
r_int
op_star
id|pmi_base
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pmi_start
r_static
r_void
(paren
op_star
id|pmi_start
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|pmi_pal
r_static
r_void
(paren
op_star
id|pmi_pal
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|depth
r_static
r_int
id|depth
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|vesafb_pan_display
r_static
r_int
id|vesafb_pan_display
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
macro_line|#ifdef __i386__
r_int
id|offset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ypan
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;xoffset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;yoffset
OG
id|var-&gt;yres_virtual
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ypan
op_eq
l_int|1
)paren
op_logical_and
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
id|offset
op_assign
(paren
id|var-&gt;yoffset
op_star
id|info-&gt;fix.line_length
op_plus
id|var-&gt;xoffset
)paren
op_div
l_int|4
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;call *(%%edi)&quot;
suffix:colon
multiline_comment|/* no return value */
suffix:colon
l_string|&quot;a&quot;
(paren
l_int|0x4f07
)paren
comma
multiline_comment|/* EAX */
l_string|&quot;b&quot;
(paren
l_int|0
)paren
comma
multiline_comment|/* EBX */
l_string|&quot;c&quot;
(paren
id|offset
)paren
comma
multiline_comment|/* ECX */
l_string|&quot;d&quot;
(paren
id|offset
op_rshift
l_int|16
)paren
comma
multiline_comment|/* EDX */
l_string|&quot;D&quot;
(paren
op_amp
id|pmi_start
)paren
)paren
suffix:semicolon
multiline_comment|/* EDI */
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vesa_setpalette
r_static
r_void
id|vesa_setpalette
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
)paren
(brace
macro_line|#ifdef __i386__
r_struct
(brace
id|u_char
id|blue
comma
id|green
comma
id|red
comma
id|pad
suffix:semicolon
)brace
id|entry
suffix:semicolon
r_int
id|shift
op_assign
l_int|16
op_minus
id|depth
suffix:semicolon
r_if
c_cond
(paren
id|pmi_setpal
)paren
(brace
id|entry.red
op_assign
id|red
op_rshift
id|shift
suffix:semicolon
id|entry.green
op_assign
id|green
op_rshift
id|shift
suffix:semicolon
id|entry.blue
op_assign
id|blue
op_rshift
id|shift
suffix:semicolon
id|entry.pad
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;call *(%%esi)&quot;
suffix:colon
multiline_comment|/* no return value */
suffix:colon
l_string|&quot;a&quot;
(paren
l_int|0x4f09
)paren
comma
multiline_comment|/* EAX */
l_string|&quot;b&quot;
(paren
l_int|0
)paren
comma
multiline_comment|/* EBX */
l_string|&quot;c&quot;
(paren
l_int|1
)paren
comma
multiline_comment|/* ECX */
l_string|&quot;d&quot;
(paren
id|regno
)paren
comma
multiline_comment|/* EDX */
l_string|&quot;D&quot;
(paren
op_amp
id|entry
)paren
comma
multiline_comment|/* EDI */
l_string|&quot;S&quot;
(paren
op_amp
id|pmi_pal
)paren
)paren
suffix:semicolon
multiline_comment|/* ESI */
)brace
r_else
(brace
multiline_comment|/* without protected mode interface, try VGA registers... */
id|outb_p
c_func
(paren
id|regno
comma
id|dac_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|red
op_rshift
id|shift
comma
id|dac_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|green
op_rshift
id|shift
comma
id|dac_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|blue
op_rshift
id|shift
comma
id|dac_val
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|vesafb_setcolreg
r_static
r_int
id|vesafb_setcolreg
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
multiline_comment|/*&n;&t; *  Set a single color register. The values supplied are&n;&t; *  already rounded down to the hardware&squot;s capabilities&n;&t; *  (according to the entries in the `var&squot; structure). Return&n;&t; *  != 0 for invalid regno.&n;&t; */
r_if
c_cond
(paren
id|regno
op_ge
id|info-&gt;cmap.len
)paren
r_return
l_int|1
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
id|vesa_setpalette
c_func
(paren
id|regno
comma
id|red
comma
id|green
comma
id|blue
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
r_if
c_cond
(paren
id|info-&gt;var.red.offset
op_eq
l_int|10
)paren
(brace
multiline_comment|/* 1:5:5:5 */
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
(paren
(paren
id|red
op_amp
l_int|0xf800
)paren
op_rshift
l_int|1
)paren
op_or
(paren
(paren
id|green
op_amp
l_int|0xf800
)paren
op_rshift
l_int|6
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
)brace
r_else
(brace
multiline_comment|/* 0:5:6:5 */
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
)brace
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
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
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
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
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vesafb_ops
r_static
r_struct
id|fb_ops
id|vesafb_ops
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
id|vesafb_setcolreg
comma
dot
id|fb_pan_display
op_assign
id|vesafb_pan_display
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
)brace
suffix:semicolon
DECL|function|vesafb_setup
r_int
id|__init
id|vesafb_setup
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
l_int|0
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
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;inverse&quot;
)paren
)paren
id|inverse
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;redraw&quot;
)paren
)paren
id|ypan
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;ypan&quot;
)paren
)paren
id|ypan
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;ywrap&quot;
)paren
)paren
id|ypan
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;vgapal&quot;
)paren
)paren
id|pmi_setpal
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;pmipal&quot;
)paren
)paren
id|pmi_setpal
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;mtrr&quot;
)paren
)paren
id|mtrr
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;nomtrr&quot;
)paren
)paren
id|mtrr
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|this_opt
comma
l_string|&quot;vtotal:&quot;
comma
l_int|7
)paren
)paren
id|vram_total
op_assign
id|simple_strtoul
c_func
(paren
id|this_opt
op_plus
l_int|7
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|this_opt
comma
l_string|&quot;vremap:&quot;
comma
l_int|7
)paren
)paren
id|vram_remap
op_assign
id|simple_strtoul
c_func
(paren
id|this_opt
op_plus
l_int|7
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vesafb_probe
r_static
r_int
id|__init
id|vesafb_probe
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
id|i
comma
id|err
suffix:semicolon
r_int
r_int
id|size_vmode
suffix:semicolon
r_int
r_int
id|size_remap
suffix:semicolon
r_int
r_int
id|size_total
suffix:semicolon
r_if
c_cond
(paren
id|screen_info.orig_video_isVGA
op_ne
id|VIDEO_TYPE_VLFB
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|vesafb_fix.smem_start
op_assign
id|screen_info.lfb_base
suffix:semicolon
id|vesafb_defined.bits_per_pixel
op_assign
id|screen_info.lfb_depth
suffix:semicolon
r_if
c_cond
(paren
l_int|15
op_eq
id|vesafb_defined.bits_per_pixel
)paren
id|vesafb_defined.bits_per_pixel
op_assign
l_int|16
suffix:semicolon
id|vesafb_defined.xres
op_assign
id|screen_info.lfb_width
suffix:semicolon
id|vesafb_defined.yres
op_assign
id|screen_info.lfb_height
suffix:semicolon
id|vesafb_fix.line_length
op_assign
id|screen_info.lfb_linelength
suffix:semicolon
id|vesafb_fix.visual
op_assign
(paren
id|vesafb_defined.bits_per_pixel
op_eq
l_int|8
)paren
ques
c_cond
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
multiline_comment|/*   size_vmode -- that is the amount of memory needed for the&n;&t; *                 used video mode, i.e. the minimum amount of&n;&t; *                 memory we need. */
id|size_vmode
op_assign
id|vesafb_defined.yres
op_star
id|vesafb_fix.line_length
suffix:semicolon
multiline_comment|/*   size_total -- all video memory we have. Used for mtrr&n;&t; *                 entries, ressource allocation and bounds&n;&t; *                 checking. */
id|size_total
op_assign
id|screen_info.lfb_size
op_star
l_int|65536
suffix:semicolon
r_if
c_cond
(paren
id|vram_total
)paren
id|size_total
op_assign
id|vram_total
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
r_if
c_cond
(paren
id|size_total
OL
id|size_vmode
)paren
id|size_total
op_assign
id|size_vmode
suffix:semicolon
multiline_comment|/*   size_remap -- the amount of video memory we are going to&n;&t; *                 use for vesafb.  With modern cards it is no&n;&t; *                 option to simply use size_total as that&n;&t; *                 wastes plenty of kernel address space. */
id|size_remap
op_assign
id|size_vmode
op_star
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|vram_remap
)paren
id|size_remap
op_assign
id|vram_remap
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
r_if
c_cond
(paren
id|size_remap
OL
id|size_vmode
)paren
id|size_remap
op_assign
id|size_vmode
suffix:semicolon
r_if
c_cond
(paren
id|size_remap
OG
id|size_total
)paren
id|size_remap
op_assign
id|size_total
suffix:semicolon
id|vesafb_fix.smem_len
op_assign
id|size_remap
suffix:semicolon
macro_line|#ifndef __i386__
id|screen_info.vesapm_seg
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|vesafb_fix.smem_start
comma
id|size_total
comma
l_string|&quot;vesafb&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vesafb: abort, cannot reserve video memory at 0x%lx&bslash;n&quot;
comma
id|vesafb_fix.smem_start
)paren
suffix:semicolon
multiline_comment|/* We cannot make this fatal. Sometimes this comes from magic&n;&t;&t;   spaces our resource handlers simply don&squot;t know about */
)brace
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
(brace
id|release_mem_region
c_func
(paren
id|vesafb_fix.smem_start
comma
id|vesafb_fix.smem_len
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|info-&gt;pseudo_palette
op_assign
id|info-&gt;par
suffix:semicolon
id|info-&gt;par
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;screen_base
op_assign
id|ioremap
c_func
(paren
id|vesafb_fix.smem_start
comma
id|vesafb_fix.smem_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;screen_base
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vesafb: abort, cannot ioremap video memory 0x%x @ 0x%lx&bslash;n&quot;
comma
id|vesafb_fix.smem_len
comma
id|vesafb_fix.smem_start
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: framebuffer at 0x%lx, mapped to 0x%p, &quot;
l_string|&quot;using %dk, total %dk&bslash;n&quot;
comma
id|vesafb_fix.smem_start
comma
id|info-&gt;screen_base
comma
id|size_remap
op_div
l_int|1024
comma
id|size_total
op_div
l_int|1024
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: mode is %dx%dx%d, linelength=%d, pages=%d&bslash;n&quot;
comma
id|vesafb_defined.xres
comma
id|vesafb_defined.yres
comma
id|vesafb_defined.bits_per_pixel
comma
id|vesafb_fix.line_length
comma
id|screen_info.pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|screen_info.vesapm_seg
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: protected mode interface info at %04x:%04x&bslash;n&quot;
comma
id|screen_info.vesapm_seg
comma
id|screen_info.vesapm_off
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|screen_info.vesapm_seg
OL
l_int|0xc000
)paren
id|ypan
op_assign
id|pmi_setpal
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* not available or some DOS TSR ... */
r_if
c_cond
(paren
id|ypan
op_logical_or
id|pmi_setpal
)paren
(brace
id|pmi_base
op_assign
(paren
r_int
r_int
op_star
)paren
id|phys_to_virt
c_func
(paren
(paren
(paren
r_int
r_int
)paren
id|screen_info.vesapm_seg
op_lshift
l_int|4
)paren
op_plus
id|screen_info.vesapm_off
)paren
suffix:semicolon
id|pmi_start
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|pmi_base
op_plus
id|pmi_base
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|pmi_pal
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|pmi_base
op_plus
id|pmi_base
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: pmi: set display start = %p, set palette = %p&bslash;n&quot;
comma
id|pmi_start
comma
id|pmi_pal
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmi_base
(braket
l_int|3
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: pmi: ports = &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pmi_base
(braket
l_int|3
)braket
op_div
l_int|2
suffix:semicolon
id|pmi_base
(braket
id|i
)braket
op_ne
l_int|0xffff
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%x &quot;
comma
id|pmi_base
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmi_base
(braket
id|i
)braket
op_ne
l_int|0xffff
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * memory areas not supported (yet?)&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * Rules are: we have to set up a descriptor for the requested&n;&t;&t;&t;&t; * memory area and pass it in the ES register to the BIOS function.&n;&t;&t;&t;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: can&squot;t handle memory requests, pmi disabled&bslash;n&quot;
)paren
suffix:semicolon
id|ypan
op_assign
id|pmi_setpal
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|vesafb_defined.xres_virtual
op_assign
id|vesafb_defined.xres
suffix:semicolon
id|vesafb_defined.yres_virtual
op_assign
id|vesafb_fix.smem_len
op_div
id|vesafb_fix.line_length
suffix:semicolon
r_if
c_cond
(paren
id|ypan
op_logical_and
id|vesafb_defined.yres_virtual
OG
id|vesafb_defined.yres
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: scrolling: %s using protected mode interface, yres_virtual=%d&bslash;n&quot;
comma
(paren
id|ypan
OG
l_int|1
)paren
ques
c_cond
l_string|&quot;ywrap&quot;
suffix:colon
l_string|&quot;ypan&quot;
comma
id|vesafb_defined.yres_virtual
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: scrolling: redraw&bslash;n&quot;
)paren
suffix:semicolon
id|vesafb_defined.yres_virtual
op_assign
id|vesafb_defined.yres
suffix:semicolon
id|ypan
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* some dummy values for timing to make fbset happy */
id|vesafb_defined.pixclock
op_assign
l_int|10000000
op_div
id|vesafb_defined.xres
op_star
l_int|1000
op_div
id|vesafb_defined.yres
suffix:semicolon
id|vesafb_defined.left_margin
op_assign
(paren
id|vesafb_defined.xres
op_div
l_int|8
)paren
op_amp
l_int|0xf8
suffix:semicolon
id|vesafb_defined.hsync_len
op_assign
(paren
id|vesafb_defined.xres
op_div
l_int|8
)paren
op_amp
l_int|0xf8
suffix:semicolon
id|vesafb_defined.red.offset
op_assign
id|screen_info.red_pos
suffix:semicolon
id|vesafb_defined.red.length
op_assign
id|screen_info.red_size
suffix:semicolon
id|vesafb_defined.green.offset
op_assign
id|screen_info.green_pos
suffix:semicolon
id|vesafb_defined.green.length
op_assign
id|screen_info.green_size
suffix:semicolon
id|vesafb_defined.blue.offset
op_assign
id|screen_info.blue_pos
suffix:semicolon
id|vesafb_defined.blue.length
op_assign
id|screen_info.blue_size
suffix:semicolon
id|vesafb_defined.transp.offset
op_assign
id|screen_info.rsvd_pos
suffix:semicolon
id|vesafb_defined.transp.length
op_assign
id|screen_info.rsvd_size
suffix:semicolon
r_if
c_cond
(paren
id|vesafb_defined.bits_per_pixel
op_le
l_int|8
)paren
(brace
id|depth
op_assign
id|vesafb_defined.green.length
suffix:semicolon
id|vesafb_defined.red.length
op_assign
id|vesafb_defined.green.length
op_assign
id|vesafb_defined.blue.length
op_assign
id|vesafb_defined.bits_per_pixel
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: %s: &quot;
l_string|&quot;size=%d:%d:%d:%d, shift=%d:%d:%d:%d&bslash;n&quot;
comma
(paren
id|vesafb_defined.bits_per_pixel
OG
l_int|8
)paren
ques
c_cond
l_string|&quot;Truecolor&quot;
suffix:colon
l_string|&quot;Pseudocolor&quot;
comma
id|screen_info.rsvd_size
comma
id|screen_info.red_size
comma
id|screen_info.green_size
comma
id|screen_info.blue_size
comma
id|screen_info.rsvd_pos
comma
id|screen_info.red_pos
comma
id|screen_info.green_pos
comma
id|screen_info.blue_pos
)paren
suffix:semicolon
id|vesafb_fix.ypanstep
op_assign
id|ypan
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|vesafb_fix.ywrapstep
op_assign
(paren
id|ypan
OG
l_int|1
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* request failure does not faze us, as vgacon probably has this&n;&t; * region already (FIXME) */
id|request_region
c_func
(paren
l_int|0x3c0
comma
l_int|32
comma
l_string|&quot;vesafb&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtrr
)paren
(brace
r_int
id|temp_size
op_assign
id|size_total
suffix:semicolon
multiline_comment|/* Find the largest power-of-two */
r_while
c_loop
(paren
id|temp_size
op_amp
(paren
id|temp_size
op_minus
l_int|1
)paren
)paren
id|temp_size
op_and_assign
(paren
id|temp_size
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Try and find a power of two to add */
r_while
c_loop
(paren
id|temp_size
op_logical_and
id|mtrr_add
c_func
(paren
id|vesafb_fix.smem_start
comma
id|temp_size
comma
id|MTRR_TYPE_WRCOMB
comma
l_int|1
)paren
op_eq
op_minus
id|EINVAL
)paren
(brace
id|temp_size
op_rshift_assign
l_int|1
suffix:semicolon
)brace
)brace
id|info-&gt;fbops
op_assign
op_amp
id|vesafb_ops
suffix:semicolon
id|info-&gt;var
op_assign
id|vesafb_defined
suffix:semicolon
id|info-&gt;fix
op_assign
id|vesafb_fix
suffix:semicolon
id|info-&gt;flags
op_assign
id|FBINFO_FLAG_DEFAULT
op_or
(paren
id|ypan
)paren
ques
c_cond
id|FBINFO_HWACCEL_YPAN
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
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
OL
l_int|0
)paren
(brace
id|err
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
id|info
)paren
OL
l_int|0
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|fb_dealloc_cmap
c_func
(paren
op_amp
id|info-&gt;cmap
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|info-&gt;node
comma
id|info-&gt;fix.id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
id|framebuffer_release
c_func
(paren
id|info
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|vesafb_fix.smem_start
comma
id|size_total
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|vesafb_driver
r_static
r_struct
id|device_driver
id|vesafb_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;vesafb&quot;
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
id|vesafb_probe
comma
)brace
suffix:semicolon
DECL|variable|vesafb_device
r_static
r_struct
id|platform_device
id|vesafb_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;vesafb&quot;
comma
)brace
suffix:semicolon
DECL|function|vesafb_init
r_int
id|__init
id|vesafb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_char
op_star
id|option
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* ignore error return of fb_get_options */
id|fb_get_options
c_func
(paren
l_string|&quot;vesafb&quot;
comma
op_amp
id|option
)paren
suffix:semicolon
id|vesafb_setup
c_func
(paren
id|option
)paren
suffix:semicolon
id|ret
op_assign
id|driver_register
c_func
(paren
op_amp
id|vesafb_driver
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
id|vesafb_device
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
id|vesafb_driver
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|vesafb_init
id|module_init
c_func
(paren
id|vesafb_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
