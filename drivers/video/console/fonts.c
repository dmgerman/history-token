multiline_comment|/*&n; * linux/drivers/video/fonts.c -- `Soft&squot; font definitions&n; *&n; *    Created 1995 by Geert Uytterhoeven&n; *    Rewritten 1998 by Martin Mares &lt;mj@ucw.cz&gt;&n; *&n; *&t;2001 - Documented with DocBook&n; *&t;- Brad Douglas &lt;brad@neruo.com&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/font.h&gt;
macro_line|#if defined(__mc68000__) || defined(CONFIG_APUS)
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#endif
DECL|macro|NO_FONTS
mdefine_line|#define NO_FONTS
DECL|variable|fonts
r_static
r_struct
id|font_desc
op_star
id|fonts
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_FONT_8x8
DECL|macro|NO_FONTS
macro_line|#undef NO_FONTS
op_amp
id|font_vga_8x8
comma
macro_line|#endif
macro_line|#ifdef CONFIG_FONT_8x16
DECL|macro|NO_FONTS
macro_line|#undef NO_FONTS
op_amp
id|font_vga_8x16
comma
macro_line|#endif
macro_line|#ifdef CONFIG_FONT_6x11
DECL|macro|NO_FONTS
macro_line|#undef NO_FONTS
op_amp
id|font_vga_6x11
comma
macro_line|#endif
macro_line|#ifdef CONFIG_FONT_SUN8x16
DECL|macro|NO_FONTS
macro_line|#undef NO_FONTS
op_amp
id|font_sun_8x16
comma
macro_line|#endif
macro_line|#ifdef CONFIG_FONT_SUN12x22
DECL|macro|NO_FONTS
macro_line|#undef NO_FONTS
op_amp
id|font_sun_12x22
comma
macro_line|#endif
macro_line|#ifdef CONFIG_FONT_ACORN_8x8
DECL|macro|NO_FONTS
macro_line|#undef NO_FONTS
op_amp
id|font_acorn_8x8
comma
macro_line|#endif
macro_line|#ifdef CONFIG_FONT_PEARL_8x8
DECL|macro|NO_FONTS
macro_line|#undef NO_FONTS
op_amp
id|font_pearl_8x8
comma
macro_line|#endif
macro_line|#ifdef CONFIG_FONT_MINI_4x6
DECL|macro|NO_FONTS
macro_line|#undef NO_FONTS
op_amp
id|font_mini_4x6
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|num_fonts
mdefine_line|#define num_fonts (sizeof(fonts)/sizeof(*fonts))
macro_line|#ifdef NO_FONTS
macro_line|#error No fonts configured.
macro_line|#endif
multiline_comment|/**&n; *&t;find_font - find a font&n; *&t;@name: string name of a font&n; *&n; *&t;Find a specified font with string name @name.&n; *&n; *&t;Returns %NULL if no font found, or a pointer to the&n; *&t;specified font.&n; *&n; */
DECL|function|find_font
r_struct
id|font_desc
op_star
id|find_font
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_fonts
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|fonts
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|name
)paren
)paren
r_return
id|fonts
(braket
id|i
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;get_default_font - get default font&n; *&t;@xres: screen size of X&n; *&t;@yres: screen size of Y&n; *&n; *&t;Get the default font for a specified screen size.&n; *&t;Dimensions are in pixels.&n; *&n; *&t;Returns %NULL if no font is found, or a pointer to the&n; *&t;chosen font.&n; *&n; */
DECL|function|get_default_font
r_struct
id|font_desc
op_star
id|get_default_font
c_func
(paren
r_int
id|xres
comma
r_int
id|yres
)paren
(brace
r_int
id|i
comma
id|c
comma
id|cc
suffix:semicolon
r_struct
id|font_desc
op_star
id|f
comma
op_star
id|g
suffix:semicolon
id|g
op_assign
l_int|NULL
suffix:semicolon
id|cc
op_assign
op_minus
l_int|10000
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_fonts
suffix:semicolon
id|i
op_increment
)paren
(brace
id|f
op_assign
id|fonts
(braket
id|i
)braket
suffix:semicolon
id|c
op_assign
id|f-&gt;pref
suffix:semicolon
macro_line|#if defined(__mc68000__) || defined(CONFIG_APUS)
macro_line|#ifdef CONFIG_FONT_PEARL_8x8
r_if
c_cond
(paren
id|MACH_IS_AMIGA
op_logical_and
id|f-&gt;idx
op_eq
id|PEARL8x8_IDX
)paren
id|c
op_assign
l_int|100
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FONT_6x11
r_if
c_cond
(paren
id|MACH_IS_MAC
op_logical_and
id|xres
OL
l_int|640
op_logical_and
id|f-&gt;idx
op_eq
id|VGA6x11_IDX
)paren
id|c
op_assign
l_int|100
suffix:semicolon
macro_line|#endif
macro_line|#endif
r_if
c_cond
(paren
(paren
id|yres
OL
l_int|400
)paren
op_eq
(paren
id|f-&gt;height
op_le
l_int|8
)paren
)paren
id|c
op_add_assign
l_int|1000
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
id|cc
)paren
(brace
id|cc
op_assign
id|c
suffix:semicolon
id|g
op_assign
id|f
suffix:semicolon
)brace
)brace
r_return
id|g
suffix:semicolon
)brace
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
suffix:semicolon
DECL|variable|fonts
id|EXPORT_SYMBOL
c_func
(paren
id|fonts
)paren
suffix:semicolon
DECL|variable|find_font
id|EXPORT_SYMBOL
c_func
(paren
id|find_font
)paren
suffix:semicolon
DECL|variable|get_default_font
id|EXPORT_SYMBOL
c_func
(paren
id|get_default_font
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;James Simmons &lt;jsimmons@users.sf.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Console Fonts&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
