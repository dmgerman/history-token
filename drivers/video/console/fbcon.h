multiline_comment|/*&n; *  linux/drivers/video/console/fbcon.h -- Low level frame buffer based console driver&n; *&n; *&t;Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _VIDEO_FBCON_H
DECL|macro|_VIDEO_FBCON_H
mdefine_line|#define _VIDEO_FBCON_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/vt_buffer.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_struct
id|display
suffix:semicolon
multiline_comment|/*                                  &n;     *  `switch&squot; for the Low Level Operations&n;     */
DECL|struct|display_switch
r_struct
id|display_switch
(brace
DECL|member|setup
r_void
(paren
op_star
id|setup
)paren
(paren
r_struct
id|display
op_star
id|p
)paren
suffix:semicolon
DECL|member|bmove
r_void
(paren
op_star
id|bmove
)paren
(paren
r_struct
id|display
op_star
id|p
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
multiline_comment|/* for clear, conp may be NULL, which means use a blanking (black) color */
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
id|conp
comma
r_struct
id|display
op_star
id|p
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
DECL|member|putc
r_void
(paren
op_star
id|putc
)paren
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|c
comma
r_int
id|yy
comma
r_int
id|xx
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
id|conp
comma
r_struct
id|display
op_star
id|p
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
)paren
suffix:semicolon
DECL|member|revc
r_void
(paren
op_star
id|revc
)paren
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|xx
comma
r_int
id|yy
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
id|display
op_star
id|p
comma
r_int
id|flags
comma
r_int
id|xx
comma
r_int
id|yy
)paren
suffix:semicolon
DECL|member|set_font
r_int
(paren
op_star
id|set_font
)paren
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|width
comma
r_int
id|height
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
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|bottom_only
)paren
suffix:semicolon
DECL|member|fontwidthmask
r_int
r_int
id|fontwidthmask
suffix:semicolon
multiline_comment|/* 1 at (1 &lt;&lt; (width - 1)) if width is supported */
)brace
suffix:semicolon
r_extern
r_struct
id|display_switch
id|fbcon_dummy
suffix:semicolon
multiline_comment|/*&n;    *    This is the interface between the low-level console driver and the&n;    *    low-level frame buffer device&n;    */
DECL|struct|display
r_struct
id|display
(brace
multiline_comment|/* Filled in by the frame buffer device */
DECL|member|can_soft_blank
id|u_short
id|can_soft_blank
suffix:semicolon
multiline_comment|/* zero if no hardware blanking */
DECL|member|inverse
id|u_short
id|inverse
suffix:semicolon
multiline_comment|/* != 0 text black on white as default */
DECL|member|dispsw
r_struct
id|display_switch
op_star
id|dispsw
suffix:semicolon
multiline_comment|/* low level operations */
DECL|member|dispsw_data
r_void
op_star
id|dispsw_data
suffix:semicolon
multiline_comment|/* optional dispsw helper data */
multiline_comment|/* Filled in by the low-level console driver */
DECL|member|conp
r_struct
id|vc_data
op_star
id|conp
suffix:semicolon
multiline_comment|/* pointer to console data */
DECL|member|fb_info
r_struct
id|fb_info
op_star
id|fb_info
suffix:semicolon
multiline_comment|/* frame buffer for this console */
DECL|member|vrows
r_int
id|vrows
suffix:semicolon
multiline_comment|/* number of virtual rows */
DECL|member|cursor_x
r_int
r_int
id|cursor_x
suffix:semicolon
multiline_comment|/* current cursor position */
DECL|member|cursor_y
r_int
r_int
id|cursor_y
suffix:semicolon
DECL|member|cursor_pos
r_int
r_int
id|cursor_pos
suffix:semicolon
DECL|member|fgcol
r_int
id|fgcol
suffix:semicolon
multiline_comment|/* text colors */
DECL|member|bgcol
r_int
id|bgcol
suffix:semicolon
DECL|member|next_line
id|u_long
id|next_line
suffix:semicolon
multiline_comment|/* offset to one line below */
DECL|member|next_plane
id|u_long
id|next_plane
suffix:semicolon
multiline_comment|/* offset to next plane */
DECL|member|fontname
r_char
id|fontname
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* Font associated to this display */
DECL|member|fontdata
id|u_char
op_star
id|fontdata
suffix:semicolon
DECL|member|_fontheightlog
r_int
r_int
id|_fontheightlog
suffix:semicolon
DECL|member|_fontwidthlog
r_int
r_int
id|_fontwidthlog
suffix:semicolon
DECL|member|_fontheight
r_int
r_int
id|_fontheight
suffix:semicolon
DECL|member|_fontwidth
r_int
r_int
id|_fontwidth
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
DECL|member|fgshift
DECL|member|bgshift
r_int
r_char
id|fgshift
comma
id|bgshift
suffix:semicolon
DECL|member|charmask
r_int
r_int
id|charmask
suffix:semicolon
multiline_comment|/* 0xff or 0x1ff */
)brace
suffix:semicolon
multiline_comment|/* drivers/video/console/fbcon.c */
r_extern
r_struct
id|display
id|fb_display
(braket
id|MAX_NR_CONSOLES
)braket
suffix:semicolon
r_extern
r_char
id|con2fb_map
(braket
id|MAX_NR_CONSOLES
)braket
suffix:semicolon
r_extern
r_void
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
DECL|macro|fontheight
mdefine_line|#define fontheight(p) ((p)-&gt;_fontheight)
DECL|macro|fontheightlog
mdefine_line|#define fontheightlog(p) ((p)-&gt;_fontheightlog)
macro_line|#ifdef CONFIG_FBCON_FONTWIDTH8_ONLY
multiline_comment|/* fontwidth w is supported by dispsw */
DECL|macro|FONTWIDTH
mdefine_line|#define FONTWIDTH(w)&t;(1 &lt;&lt; ((8) - 1))
multiline_comment|/* fontwidths w1-w2 inclusive are supported by dispsw */
DECL|macro|FONTWIDTHRANGE
mdefine_line|#define FONTWIDTHRANGE(w1,w2)&t;FONTWIDTH(8)
DECL|macro|fontwidth
mdefine_line|#define fontwidth(p) (8)
DECL|macro|fontwidthlog
mdefine_line|#define fontwidthlog(p) (0)
macro_line|#else
multiline_comment|/* fontwidth w is supported by dispsw */
DECL|macro|FONTWIDTH
mdefine_line|#define FONTWIDTH(w)&t;(1 &lt;&lt; ((w) - 1))
multiline_comment|/* fontwidths w1-w2 inclusive are supported by dispsw */
DECL|macro|FONTWIDTHRANGE
mdefine_line|#define FONTWIDTHRANGE(w1,w2)&t;(FONTWIDTH(w2+1) - FONTWIDTH(w1))
DECL|macro|fontwidth
mdefine_line|#define fontwidth(p) ((p)-&gt;_fontwidth)
DECL|macro|fontwidthlog
mdefine_line|#define fontwidthlog(p) ((p)-&gt;_fontwidthlog)
macro_line|#endif
multiline_comment|/*&n;     *  Attribute Decoding&n;     */
multiline_comment|/* Color */
DECL|macro|attr_fgcol
mdefine_line|#define attr_fgcol(p,s)    &bslash;&n;&t;(((s) &gt;&gt; ((p)-&gt;fgshift)) &amp; 0x0f)
DECL|macro|attr_bgcol
mdefine_line|#define attr_bgcol(p,s)    &bslash;&n;&t;(((s) &gt;&gt; ((p)-&gt;bgshift)) &amp; 0x0f)
DECL|macro|attr_bgcol_ec
mdefine_line|#define&t;attr_bgcol_ec(p,conp) &bslash;&n;&t;((conp) ? (((conp)-&gt;vc_video_erase_char &gt;&gt; ((p)-&gt;bgshift)) &amp; 0x0f) : 0)
DECL|macro|attr_fgcol_ec
mdefine_line|#define attr_fgcol_ec(p,vc) &bslash;&n;&t;((vc) ? (((vc)-&gt;vc_video_erase_char &gt;&gt; ((p)-&gt;fgshift)) &amp; 0x0f) : 0)
multiline_comment|/* Monochrome */
DECL|macro|attr_bold
mdefine_line|#define attr_bold(p,s) &bslash;&n;&t;((s) &amp; 0x200)
DECL|macro|attr_reverse
mdefine_line|#define attr_reverse(p,s) &bslash;&n;&t;(((s) &amp; 0x800) ^ ((p)-&gt;inverse ? 0x800 : 0))
DECL|macro|attr_underline
mdefine_line|#define attr_underline(p,s) &bslash;&n;&t;((s) &amp; 0x400)
DECL|macro|attr_blink
mdefine_line|#define attr_blink(p,s) &bslash;&n;&t;((s) &amp; 0x8000)
multiline_comment|/*&n;     *  Scroll Method&n;     */
multiline_comment|/* Internal flags */
DECL|macro|__SCROLL_YPAN
mdefine_line|#define __SCROLL_YPAN&t;&t;0x001
DECL|macro|__SCROLL_YWRAP
mdefine_line|#define __SCROLL_YWRAP&t;&t;0x002
DECL|macro|__SCROLL_YMOVE
mdefine_line|#define __SCROLL_YMOVE&t;&t;0x003
DECL|macro|__SCROLL_YREDRAW
mdefine_line|#define __SCROLL_YREDRAW&t;0x004
DECL|macro|__SCROLL_YMASK
mdefine_line|#define __SCROLL_YMASK&t;&t;0x00f
DECL|macro|__SCROLL_YFIXED
mdefine_line|#define __SCROLL_YFIXED&t;&t;0x010
DECL|macro|__SCROLL_YNOMOVE
mdefine_line|#define __SCROLL_YNOMOVE&t;0x020
DECL|macro|__SCROLL_YPANREDRAW
mdefine_line|#define __SCROLL_YPANREDRAW&t;0x040
DECL|macro|__SCROLL_YNOPARTIAL
mdefine_line|#define __SCROLL_YNOPARTIAL&t;0x080
multiline_comment|/* Only these should be used by the drivers */
multiline_comment|/* Which one should you use? If you have a fast card and slow bus,&n;   then probably just 0 to indicate fbcon should choose between&n;   YWRAP/YPAN+MOVE/YMOVE. On the other side, if you have a fast bus&n;   and even better if your card can do fonting (1-&gt;8/32bit painting),&n;   you should consider either SCROLL_YREDRAW (if your card is&n;   able to do neither YPAN/YWRAP), or SCROLL_YNOMOVE.&n;   The best is to test it with some real life scrolling (usually, not&n;   all lines on the screen are filled completely with non-space characters,&n;   and REDRAW performs much better on such lines, so don&squot;t cat a file&n;   with every line covering all screen columns, it would not be the right&n;   benchmark).&n; */
DECL|macro|SCROLL_YREDRAW
mdefine_line|#define SCROLL_YREDRAW&t;&t;(__SCROLL_YFIXED|__SCROLL_YREDRAW)
DECL|macro|SCROLL_YNOMOVE
mdefine_line|#define SCROLL_YNOMOVE&t;&t;(__SCROLL_YNOMOVE|__SCROLL_YPANREDRAW)
multiline_comment|/* SCROLL_YNOPARTIAL, used in combination with the above, is for video&n;   cards which can not handle using panning to scroll a portion of the&n;   screen without excessive flicker.  Panning will only be used for&n;   whole screens.&n; */
multiline_comment|/* Namespace consistency */
DECL|macro|SCROLL_YNOPARTIAL
mdefine_line|#define SCROLL_YNOPARTIAL&t;__SCROLL_YNOPARTIAL
r_extern
r_void
id|fbcon_redraw_clear
c_func
(paren
r_struct
id|vc_data
op_star
comma
r_struct
id|display
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|fbcon_redraw_bmove
c_func
(paren
r_struct
id|vc_data
op_star
comma
r_struct
id|display
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* _VIDEO_FBCON_H */
eof
