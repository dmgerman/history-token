multiline_comment|/*&n; *  font.h -- `Soft&squot; font definitions&n; *&n; *  Created 1995 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _VIDEO_FONT_H
DECL|macro|_VIDEO_FONT_H
mdefine_line|#define _VIDEO_FONT_H
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|fbcon_font_desc
r_struct
id|fbcon_font_desc
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|width
DECL|member|height
r_int
id|width
comma
id|height
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|pref
r_int
id|pref
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|VGA8x8_IDX
mdefine_line|#define VGA8x8_IDX&t;0
DECL|macro|VGA8x16_IDX
mdefine_line|#define VGA8x16_IDX&t;1
DECL|macro|PEARL8x8_IDX
mdefine_line|#define PEARL8x8_IDX&t;2
DECL|macro|VGA6x11_IDX
mdefine_line|#define VGA6x11_IDX&t;3
DECL|macro|SUN8x16_IDX
mdefine_line|#define SUN8x16_IDX&t;4
DECL|macro|SUN12x22_IDX
mdefine_line|#define SUN12x22_IDX&t;5
DECL|macro|ACORN8x8_IDX
mdefine_line|#define ACORN8x8_IDX&t;6
r_extern
r_struct
id|fbcon_font_desc
id|font_vga_8x8
comma
id|font_vga_8x16
comma
id|font_pearl_8x8
comma
id|font_vga_6x11
comma
id|font_sun_8x16
comma
id|font_sun_12x22
comma
id|font_acorn_8x8
suffix:semicolon
multiline_comment|/* Find a font with a specific name */
r_extern
r_struct
id|fbcon_font_desc
op_star
id|fbcon_find_font
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* Get the default font for a specific screen size */
r_extern
r_struct
id|fbcon_font_desc
op_star
id|fbcon_get_default_font
c_func
(paren
r_int
id|xres
comma
r_int
id|yres
)paren
suffix:semicolon
multiline_comment|/* Max. length for the name of a predefined font */
DECL|macro|MAX_FONT_NAME
mdefine_line|#define MAX_FONT_NAME&t;32
macro_line|#endif /* _VIDEO_FONT_H */
eof
