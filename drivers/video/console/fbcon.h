multiline_comment|/*&n; *  linux/drivers/video/console/fbcon.h -- Low level frame buffer based console driver&n; *&n; *&t;Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _VIDEO_FBCON_H
DECL|macro|_VIDEO_FBCON_H
mdefine_line|#define _VIDEO_FBCON_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/vt_buffer.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n;    *    This is the interface between the low-level console driver and the&n;    *    low-level frame buffer device&n;    */
DECL|struct|display
r_struct
id|display
(brace
multiline_comment|/* Filled in by the frame buffer device */
DECL|member|inverse
id|u_short
id|inverse
suffix:semicolon
multiline_comment|/* != 0 text black on white as default */
multiline_comment|/* Filled in by the low-level console driver */
DECL|member|fontdata
id|u_char
op_star
id|fontdata
suffix:semicolon
DECL|member|userfont
r_int
id|userfont
suffix:semicolon
multiline_comment|/* != 0 if fontdata kmalloc()ed */
DECL|member|scrollmode
id|u_short
id|scrollmode
suffix:semicolon
multiline_comment|/* Scroll Method */
DECL|member|yscroll
r_int
id|yscroll
suffix:semicolon
multiline_comment|/* Hardware scrolling */
DECL|member|vrows
r_int
id|vrows
suffix:semicolon
multiline_comment|/* number of virtual rows */
DECL|member|cursor_shape
r_int
id|cursor_shape
suffix:semicolon
DECL|member|xres_virtual
id|u32
id|xres_virtual
suffix:semicolon
DECL|member|yres_virtual
id|u32
id|yres_virtual
suffix:semicolon
DECL|member|height
id|u32
id|height
suffix:semicolon
DECL|member|width
id|u32
id|width
suffix:semicolon
DECL|member|bits_per_pixel
id|u32
id|bits_per_pixel
suffix:semicolon
DECL|member|grayscale
id|u32
id|grayscale
suffix:semicolon
DECL|member|nonstd
id|u32
id|nonstd
suffix:semicolon
DECL|member|accel_flags
id|u32
id|accel_flags
suffix:semicolon
DECL|member|red
r_struct
id|fb_bitfield
id|red
suffix:semicolon
DECL|member|green
r_struct
id|fb_bitfield
id|green
suffix:semicolon
DECL|member|blue
r_struct
id|fb_bitfield
id|blue
suffix:semicolon
DECL|member|transp
r_struct
id|fb_bitfield
id|transp
suffix:semicolon
DECL|member|mode
r_struct
id|fb_videomode
op_star
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fbcon_ops
r_struct
id|fbcon_ops
(brace
DECL|member|bmove
r_void
(paren
op_star
id|bmove
)paren
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
DECL|member|clear
r_void
(paren
op_star
id|clear
)paren
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
DECL|member|putcs
r_void
(paren
op_star
id|putcs
)paren
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_int
r_int
op_star
id|s
comma
r_int
id|count
comma
r_int
id|yy
comma
r_int
id|xx
comma
r_int
id|fg
comma
r_int
id|bg
)paren
suffix:semicolon
DECL|member|clear_margins
r_void
(paren
op_star
id|clear_margins
)paren
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|bottom_only
)paren
suffix:semicolon
DECL|member|cursor
r_void
(paren
op_star
id|cursor
)paren
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|mode
comma
r_int
id|fg
comma
r_int
id|bg
)paren
suffix:semicolon
DECL|member|cursor_timer
r_struct
id|timer_list
id|cursor_timer
suffix:semicolon
multiline_comment|/* Cursor timer */
DECL|member|cursor_state
r_struct
id|fb_cursor
id|cursor_state
suffix:semicolon
DECL|member|currcon
r_int
id|currcon
suffix:semicolon
multiline_comment|/* Current VC. */
DECL|member|cursor_flash
r_int
id|cursor_flash
suffix:semicolon
DECL|member|cursor_reset
r_int
id|cursor_reset
suffix:semicolon
DECL|member|cursor_data
r_char
op_star
id|cursor_data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Attribute Decoding&n;     */
multiline_comment|/* Color */
DECL|macro|attr_fgcol
mdefine_line|#define attr_fgcol(fgshift,s)    &bslash;&n;&t;(((s) &gt;&gt; (fgshift)) &amp; 0x0f)
DECL|macro|attr_bgcol
mdefine_line|#define attr_bgcol(bgshift,s)    &bslash;&n;&t;(((s) &gt;&gt; (bgshift)) &amp; 0x0f)
DECL|macro|attr_bgcol_ec
mdefine_line|#define&t;attr_bgcol_ec(bgshift,vc) &bslash;&n;&t;((vc) ? (((vc)-&gt;vc_video_erase_char &gt;&gt; (bgshift)) &amp; 0x0f) : 0)
DECL|macro|attr_fgcol_ec
mdefine_line|#define attr_fgcol_ec(fgshift,vc) &bslash;&n;&t;((vc) ? (((vc)-&gt;vc_video_erase_char &gt;&gt; (fgshift)) &amp; 0x0f) : 0)
multiline_comment|/* Monochrome */
DECL|macro|attr_bold
mdefine_line|#define attr_bold(s) &bslash;&n;&t;((s) &amp; 0x200)
DECL|macro|attr_reverse
mdefine_line|#define attr_reverse(s) &bslash;&n;&t;((s) &amp; 0x800)
DECL|macro|attr_underline
mdefine_line|#define attr_underline(s) &bslash;&n;&t;((s) &amp; 0x400)
DECL|macro|attr_blink
mdefine_line|#define attr_blink(s) &bslash;&n;&t;((s) &amp; 0x8000)
multiline_comment|/* Font */
DECL|macro|REFCOUNT
mdefine_line|#define REFCOUNT(fd)&t;(((int *)(fd))[-1])
DECL|macro|FNTSIZE
mdefine_line|#define FNTSIZE(fd)&t;(((int *)(fd))[-2])
DECL|macro|FNTCHARCNT
mdefine_line|#define FNTCHARCNT(fd)&t;(((int *)(fd))[-3])
DECL|macro|FNTSUM
mdefine_line|#define FNTSUM(fd)&t;(((int *)(fd))[-4])
DECL|macro|FONT_EXTRA_WORDS
mdefine_line|#define FONT_EXTRA_WORDS 4
multiline_comment|/*&n;     *  Scroll Method&n;     */
multiline_comment|/* There are several methods fbcon can use to move text around the screen:&n; *&n; *                     Operation   Pan    Wrap&n; *---------------------------------------------&n; * SCROLL_MOVE         copyarea    No     No&n; * SCROLL_PAN_MOVE     copyarea    Yes    No&n; * SCROLL_WRAP_MOVE    copyarea    No     Yes&n; * SCROLL_REDRAW       imageblit   No     No&n; * SCROLL_PAN_REDRAW   imageblit   Yes    No&n; * SCROLL_WRAP_REDRAW  imageblit   No     Yes&n; *&n; * (SCROLL_WRAP_REDRAW is not implemented yet)&n; *&n; * In general, fbcon will choose the best scrolling&n; * method based on the rule below:&n; *&n; * Pan/Wrap &gt; accel imageblit &gt; accel copyarea &gt;&n; * soft imageblit &gt; (soft copyarea)&n; *&n; * Exception to the rule: Pan + accel copyarea is&n; * preferred over Pan + accel imageblit.&n; *&n; * The above is typical for PCI/AGP cards. Unless&n; * overridden, fbcon will never use soft copyarea.&n; *&n; * If you need to override the above rule, set the&n; * appropriate flags in fb_info-&gt;flags.  For example,&n; * to prefer copyarea over imageblit, set&n; * FBINFO_READS_FAST.&n; *&n; * Other notes:&n; * + use the hardware engine to move the text&n; *    (hw-accelerated copyarea() and fillrect())&n; * + use hardware-supported panning on a large virtual screen&n; * + amifb can not only pan, but also wrap the display by N lines&n; *    (i.e. visible line i = physical line (i+N) % yres).&n; * + read what&squot;s already rendered on the screen and&n; *     write it in a different place (this is cfb_copyarea())&n; * + re-render the text to the screen&n; *&n; * Whether to use wrapping or panning can only be figured out at&n; * runtime (when we know whether our font height is a multiple&n; * of the pan/wrap step)&n; *&n; */
DECL|macro|SCROLL_MOVE
mdefine_line|#define SCROLL_MOVE&t;   0x001
DECL|macro|SCROLL_PAN_MOVE
mdefine_line|#define SCROLL_PAN_MOVE&t;   0x002
DECL|macro|SCROLL_WRAP_MOVE
mdefine_line|#define SCROLL_WRAP_MOVE   0x003
DECL|macro|SCROLL_REDRAW
mdefine_line|#define SCROLL_REDRAW&t;   0x004
DECL|macro|SCROLL_PAN_REDRAW
mdefine_line|#define SCROLL_PAN_REDRAW  0x005
r_extern
r_int
id|fb_console_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FB_TILEBLITTING
r_extern
r_void
id|fbcon_set_tileops
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|display
op_star
id|p
comma
r_struct
id|fbcon_ops
op_star
id|ops
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|fbcon_set_bitops
c_func
(paren
r_struct
id|fbcon_ops
op_star
id|ops
)paren
suffix:semicolon
macro_line|#endif /* _VIDEO_FBCON_H */
eof
