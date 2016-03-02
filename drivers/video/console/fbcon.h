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
)brace
suffix:semicolon
multiline_comment|/* drivers/video/console/fbcon.c */
r_extern
r_char
id|con2fb_map
(braket
id|MAX_NR_CONSOLES
)braket
suffix:semicolon
r_extern
r_int
id|set_con2fb_map
c_func
(paren
r_int
id|unit
comma
r_int
id|newidx
)paren
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
mdefine_line|#define attr_reverse(s, inverse) &bslash;&n;&t;(((s) &amp; 0x800) ^ (inverse ? 0x800 : 0))
DECL|macro|attr_underline
mdefine_line|#define attr_underline(s) &bslash;&n;&t;((s) &amp; 0x400)
DECL|macro|attr_blink
mdefine_line|#define attr_blink(s) &bslash;&n;&t;((s) &amp; 0x8000)
multiline_comment|/*&n;     *  Scroll Method&n;     */
multiline_comment|/* There are several methods fbcon can use to move text around the screen:&n; *&n; * + use the hardware engine to move the text&n; *    (hw-accelerated copyarea() and fillrect())&n; * + use hardware-supported panning on a large virtual screen&n; * + amifb can not only pan, but also wrap the display by N lines&n; *    (i.e. visible line i = physical line (i+N) % yres).&n; * + read what&squot;s already rendered on the screen and&n; *     write it in a different place (this is cfb_copyarea())&n; * + re-render the text to the screen&n; *&n; * Whether to use wrapping or panning can only be figured out at&n; * runtime (when we know whether our font height is a multiple&n; * of the pan/wrap step)&n; *&n; */
DECL|macro|SCROLL_ACCEL
mdefine_line|#define SCROLL_ACCEL&t;0x001
DECL|macro|SCROLL_PAN
mdefine_line|#define SCROLL_PAN&t;0x002
DECL|macro|SCROLL_WRAP
mdefine_line|#define SCROLL_WRAP&t;0x003
DECL|macro|SCROLL_REDRAW
mdefine_line|#define SCROLL_REDRAW&t;0x004
r_extern
r_int
id|fb_console_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _VIDEO_FBCON_H */
eof
