multiline_comment|/*&n; *  Convert a logo in ASCII PNM format to C source suitable for inclusion in&n; *  the Linux kernel&n; *&n; *  (C) Copyright 2001-2003 by Geert Uytterhoeven &lt;geert@linux-m68k.org&gt;&n; *&n; *  --------------------------------------------------------------------------&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of the Linux&n; *  distribution for more details.&n; */
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;unistd.h&gt;
DECL|variable|programname
r_static
r_const
r_char
op_star
id|programname
suffix:semicolon
DECL|variable|filename
r_static
r_const
r_char
op_star
id|filename
suffix:semicolon
DECL|variable|logoname
r_static
r_const
r_char
op_star
id|logoname
op_assign
l_string|&quot;linux_logo&quot;
suffix:semicolon
DECL|variable|outputname
r_static
r_const
r_char
op_star
id|outputname
suffix:semicolon
DECL|variable|out
r_static
id|FILE
op_star
id|out
suffix:semicolon
DECL|macro|LINUX_LOGO_MONO
mdefine_line|#define LINUX_LOGO_MONO&t;&t;1&t;/* monochrome black/white */
DECL|macro|LINUX_LOGO_VGA16
mdefine_line|#define LINUX_LOGO_VGA16&t;2&t;/* 16 colors VGA text palette */
DECL|macro|LINUX_LOGO_CLUT224
mdefine_line|#define LINUX_LOGO_CLUT224&t;3&t;/* 224 colors */
DECL|macro|LINUX_LOGO_GRAY256
mdefine_line|#define LINUX_LOGO_GRAY256&t;4&t;/* 256 levels grayscale */
DECL|variable|logo_types
r_static
r_const
r_char
op_star
id|logo_types
(braket
id|LINUX_LOGO_GRAY256
op_plus
l_int|1
)braket
op_assign
(brace
(braket
id|LINUX_LOGO_MONO
)braket
op_assign
l_string|&quot;LINUX_LOGO_MONO&quot;
comma
(braket
id|LINUX_LOGO_VGA16
)braket
op_assign
l_string|&quot;LINUX_LOGO_VGA16&quot;
comma
(braket
id|LINUX_LOGO_CLUT224
)braket
op_assign
l_string|&quot;LINUX_LOGO_CLUT224&quot;
comma
(braket
id|LINUX_LOGO_GRAY256
)braket
op_assign
l_string|&quot;LINUX_LOGO_GRAY256&quot;
)brace
suffix:semicolon
DECL|macro|MAX_LINUX_LOGO_COLORS
mdefine_line|#define MAX_LINUX_LOGO_COLORS&t;224
DECL|struct|color
r_struct
id|color
(brace
DECL|member|red
r_int
r_char
id|red
suffix:semicolon
DECL|member|green
r_int
r_char
id|green
suffix:semicolon
DECL|member|blue
r_int
r_char
id|blue
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|clut_vga16
r_static
r_const
r_struct
id|color
id|clut_vga16
(braket
l_int|16
)braket
op_assign
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0xaa
)brace
comma
(brace
l_int|0x00
comma
l_int|0xaa
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0xaa
comma
l_int|0xaa
)brace
comma
(brace
l_int|0xaa
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0xaa
comma
l_int|0x00
comma
l_int|0xaa
)brace
comma
(brace
l_int|0xaa
comma
l_int|0x55
comma
l_int|0x00
)brace
comma
(brace
l_int|0xaa
comma
l_int|0xaa
comma
l_int|0xaa
)brace
comma
(brace
l_int|0x55
comma
l_int|0x55
comma
l_int|0x55
)brace
comma
(brace
l_int|0x55
comma
l_int|0x55
comma
l_int|0xff
)brace
comma
(brace
l_int|0x55
comma
l_int|0xff
comma
l_int|0x55
)brace
comma
(brace
l_int|0x55
comma
l_int|0xff
comma
l_int|0xff
)brace
comma
(brace
l_int|0xff
comma
l_int|0x55
comma
l_int|0x55
)brace
comma
(brace
l_int|0xff
comma
l_int|0x55
comma
l_int|0xff
)brace
comma
(brace
l_int|0xff
comma
l_int|0xff
comma
l_int|0x55
)brace
comma
(brace
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
)brace
comma
)brace
suffix:semicolon
DECL|variable|logo_type
r_static
r_int
id|logo_type
op_assign
id|LINUX_LOGO_CLUT224
suffix:semicolon
DECL|variable|logo_width
r_static
r_int
r_int
id|logo_width
suffix:semicolon
DECL|variable|logo_height
r_static
r_int
r_int
id|logo_height
suffix:semicolon
DECL|variable|logo_data
r_static
r_struct
id|color
op_star
op_star
id|logo_data
suffix:semicolon
DECL|variable|logo_clut
r_static
r_struct
id|color
id|logo_clut
(braket
id|MAX_LINUX_LOGO_COLORS
)braket
suffix:semicolon
DECL|variable|logo_clutsize
r_static
r_int
r_int
id|logo_clutsize
op_assign
l_int|0
suffix:semicolon
r_static
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|noreturn
)paren
)paren
id|__attribute
(paren
(paren
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
r_static
r_void
id|usage
c_func
(paren
r_void
)paren
id|__attribute
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
DECL|function|get_number
r_static
r_int
r_int
id|get_number
c_func
(paren
id|FILE
op_star
id|fp
)paren
(brace
r_int
id|c
comma
id|val
suffix:semicolon
multiline_comment|/* Skip leading whitespace */
r_do
(brace
id|c
op_assign
id|fgetc
c_func
(paren
id|fp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|EOF
)paren
id|die
c_func
(paren
l_string|&quot;%s: end of file&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;#&squot;
)paren
(brace
multiline_comment|/* Ignore comments &squot;till end of line */
r_do
(brace
id|c
op_assign
id|fgetc
c_func
(paren
id|fp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|EOF
)paren
id|die
c_func
(paren
l_string|&quot;%s: end of file&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|c
op_ne
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|c
)paren
)paren
suffix:semicolon
multiline_comment|/* Parse decimal number */
id|val
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|isdigit
c_func
(paren
id|c
)paren
)paren
(brace
id|val
op_assign
l_int|10
op_star
id|val
op_plus
id|c
op_minus
l_char|&squot;0&squot;
suffix:semicolon
id|c
op_assign
id|fgetc
c_func
(paren
id|fp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|EOF
)paren
id|die
c_func
(paren
l_string|&quot;%s: end of file&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|function|read_image
r_static
r_void
id|read_image
c_func
(paren
r_void
)paren
(brace
id|FILE
op_star
id|fp
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|magic
suffix:semicolon
r_int
r_int
id|maxval
suffix:semicolon
multiline_comment|/* open image file */
id|fp
op_assign
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
id|die
c_func
(paren
l_string|&quot;Cannot open file %s: %s&bslash;n&quot;
comma
id|filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
multiline_comment|/* check file type and read file header */
id|magic
op_assign
id|fgetc
c_func
(paren
id|fp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|magic
op_ne
l_char|&squot;P&squot;
)paren
id|die
c_func
(paren
l_string|&quot;%s is not a PNM file&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
id|magic
op_assign
id|fgetc
c_func
(paren
id|fp
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|magic
)paren
(brace
r_case
l_char|&squot;1&squot;
suffix:colon
r_case
l_char|&squot;2&squot;
suffix:colon
r_case
l_char|&squot;3&squot;
suffix:colon
multiline_comment|/* Plain PBM/PGM/PPM */
r_break
suffix:semicolon
r_case
l_char|&squot;4&squot;
suffix:colon
r_case
l_char|&squot;5&squot;
suffix:colon
r_case
l_char|&squot;6&squot;
suffix:colon
multiline_comment|/* Binary PBM/PGM/PPM */
id|die
c_func
(paren
l_string|&quot;%s: Binary PNM is not supported.&bslash;n&quot;
l_string|&quot;Use pnmnoraw(1) to convert it to ASCII.&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;%s is not a PNM file&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
)brace
id|logo_width
op_assign
id|get_number
c_func
(paren
id|fp
)paren
suffix:semicolon
id|logo_height
op_assign
id|get_number
c_func
(paren
id|fp
)paren
suffix:semicolon
multiline_comment|/* allocate image data */
id|logo_data
op_assign
(paren
r_struct
id|color
op_star
op_star
)paren
id|malloc
c_func
(paren
id|logo_height
op_star
r_sizeof
(paren
r_struct
id|color
op_star
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|logo_data
)paren
id|die
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
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
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
(brace
id|logo_data
(braket
id|i
)braket
op_assign
id|malloc
c_func
(paren
id|logo_width
op_star
r_sizeof
(paren
r_struct
id|color
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|logo_data
(braket
id|i
)braket
)paren
id|die
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* read image data */
r_switch
c_cond
(paren
id|magic
)paren
(brace
r_case
l_char|&squot;1&squot;
suffix:colon
multiline_comment|/* Plain PBM */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|logo_width
suffix:semicolon
id|j
op_increment
)paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|red
op_assign
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|green
op_assign
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|blue
op_assign
l_int|255
op_star
(paren
l_int|1
op_minus
id|get_number
c_func
(paren
id|fp
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;2&squot;
suffix:colon
multiline_comment|/* Plain PGM */
id|maxval
op_assign
id|get_number
c_func
(paren
id|fp
)paren
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
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|logo_width
suffix:semicolon
id|j
op_increment
)paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|red
op_assign
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|green
op_assign
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|blue
op_assign
l_int|255
op_star
id|get_number
c_func
(paren
id|fp
)paren
op_div
id|maxval
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;3&squot;
suffix:colon
multiline_comment|/* Plain PPM */
id|maxval
op_assign
id|get_number
c_func
(paren
id|fp
)paren
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
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|logo_width
suffix:semicolon
id|j
op_increment
)paren
(brace
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|red
op_assign
l_int|255
op_star
id|get_number
c_func
(paren
id|fp
)paren
op_div
id|maxval
suffix:semicolon
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|green
op_assign
l_int|255
op_star
id|get_number
c_func
(paren
id|fp
)paren
op_div
id|maxval
suffix:semicolon
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|blue
op_assign
l_int|255
op_star
id|get_number
c_func
(paren
id|fp
)paren
op_div
id|maxval
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/* close file */
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
)brace
DECL|function|is_black
r_static
r_inline
r_int
id|is_black
c_func
(paren
r_struct
id|color
id|c
)paren
(brace
r_return
id|c.red
op_eq
l_int|0
op_logical_and
id|c.green
op_eq
l_int|0
op_logical_and
id|c.blue
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|is_white
r_static
r_inline
r_int
id|is_white
c_func
(paren
r_struct
id|color
id|c
)paren
(brace
r_return
id|c.red
op_eq
l_int|255
op_logical_and
id|c.green
op_eq
l_int|255
op_logical_and
id|c.blue
op_eq
l_int|255
suffix:semicolon
)brace
DECL|function|is_gray
r_static
r_inline
r_int
id|is_gray
c_func
(paren
r_struct
id|color
id|c
)paren
(brace
r_return
id|c.red
op_eq
id|c.green
op_logical_and
id|c.red
op_eq
id|c.blue
suffix:semicolon
)brace
DECL|function|is_equal
r_static
r_inline
r_int
id|is_equal
c_func
(paren
r_struct
id|color
id|c1
comma
r_struct
id|color
id|c2
)paren
(brace
r_return
id|c1.red
op_eq
id|c2.red
op_logical_and
id|c1.green
op_eq
id|c2.green
op_logical_and
id|c1.blue
op_eq
id|c2.blue
suffix:semicolon
)brace
DECL|function|write_header
r_static
r_void
id|write_header
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* open logo file */
r_if
c_cond
(paren
id|outputname
)paren
(brace
id|out
op_assign
id|fopen
c_func
(paren
id|outputname
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out
)paren
id|die
c_func
(paren
l_string|&quot;Cannot create file %s: %s&bslash;n&quot;
comma
id|outputname
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|out
op_assign
id|stdout
suffix:semicolon
)brace
id|fputs
c_func
(paren
l_string|&quot;/*&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot; *  DO NOT EDIT THIS FILE!&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot; *&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot; *  It was automatically generated from %s&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot; *&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot; *  Linux logo %s&bslash;n&quot;
comma
id|logoname
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot; */&bslash;n&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;#include &lt;linux/linux_logo.h&gt;&bslash;n&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;static const unsigned char %s_data[] __initdata = {&bslash;n&quot;
comma
id|logoname
)paren
suffix:semicolon
)brace
DECL|function|write_footer
r_static
r_void
id|write_footer
c_func
(paren
r_void
)paren
(brace
id|fputs
c_func
(paren
l_string|&quot;&bslash;n};&bslash;n&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;const struct linux_logo %s __initdata = {&bslash;n&quot;
comma
id|logoname
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;    .type&bslash;t= %s,&bslash;n&quot;
comma
id|logo_types
(braket
id|logo_type
)braket
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;    .width&bslash;t= %d,&bslash;n&quot;
comma
id|logo_width
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;    .height&bslash;t= %d,&bslash;n&quot;
comma
id|logo_height
)paren
suffix:semicolon
r_if
c_cond
(paren
id|logo_type
op_eq
id|LINUX_LOGO_CLUT224
)paren
(brace
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;    .clutsize&bslash;t= %d,&bslash;n&quot;
comma
id|logo_clutsize
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;    .clut&bslash;t= %s_clut,&bslash;n&quot;
comma
id|logoname
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;    .data&bslash;t= %s_data&bslash;n&quot;
comma
id|logoname
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;};&bslash;n&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
multiline_comment|/* close logo file */
r_if
c_cond
(paren
id|outputname
)paren
id|fclose
c_func
(paren
id|out
)paren
suffix:semicolon
)brace
DECL|variable|write_hex_cnt
r_static
r_int
id|write_hex_cnt
op_assign
l_int|0
suffix:semicolon
DECL|function|write_hex
r_static
r_void
id|write_hex
c_func
(paren
r_int
r_char
id|byte
)paren
(brace
r_if
c_cond
(paren
id|write_hex_cnt
op_mod
l_int|12
)paren
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;, 0x%02x&quot;
comma
id|byte
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|write_hex_cnt
)paren
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;,&bslash;n&bslash;t0x%02x&quot;
comma
id|byte
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;t0x%02x&quot;
comma
id|byte
)paren
suffix:semicolon
id|write_hex_cnt
op_increment
suffix:semicolon
)brace
DECL|function|write_logo_mono
r_static
r_void
id|write_logo_mono
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_char
id|val
comma
id|bit
suffix:semicolon
multiline_comment|/* validate image */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|logo_width
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|is_black
c_func
(paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
)paren
op_logical_and
op_logical_neg
id|is_white
c_func
(paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Image must be monochrome&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* write file header */
id|write_header
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* write logo data */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|logo_width
suffix:semicolon
)paren
(brace
r_for
c_loop
(paren
id|val
op_assign
l_int|0
comma
id|bit
op_assign
l_int|0x80
suffix:semicolon
id|bit
op_logical_and
id|j
OL
id|logo_width
suffix:semicolon
id|j
op_increment
comma
id|bit
op_rshift_assign
l_int|1
)paren
r_if
c_cond
(paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|red
)paren
id|val
op_or_assign
id|bit
suffix:semicolon
id|write_hex
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* write logo structure and file footer */
id|write_footer
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|write_logo_vga16
r_static
r_void
id|write_logo_vga16
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
comma
id|k
suffix:semicolon
r_int
r_char
id|val
suffix:semicolon
multiline_comment|/* validate image */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|logo_width
suffix:semicolon
id|j
op_increment
)paren
(brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|16
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|is_equal
c_func
(paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
comma
id|clut_vga16
(braket
id|k
)braket
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|k
op_eq
l_int|16
)paren
id|die
c_func
(paren
l_string|&quot;Image must use the 16 console colors only&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* write file header */
id|write_header
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* write logo data */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|logo_width
suffix:semicolon
id|j
op_increment
)paren
(brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|16
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|is_equal
c_func
(paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
comma
id|clut_vga16
(braket
id|k
)braket
)paren
)paren
r_break
suffix:semicolon
id|val
op_assign
id|k
op_lshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|j
OL
id|logo_width
)paren
(brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|16
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|is_equal
c_func
(paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
comma
id|clut_vga16
(braket
id|k
)braket
)paren
)paren
r_break
suffix:semicolon
id|val
op_or_assign
id|k
suffix:semicolon
)brace
id|write_hex
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
multiline_comment|/* write logo structure and file footer */
id|write_footer
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|write_logo_clut224
r_static
r_void
id|write_logo_clut224
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
comma
id|k
suffix:semicolon
multiline_comment|/* validate image */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|logo_width
suffix:semicolon
id|j
op_increment
)paren
(brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|logo_clutsize
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|is_equal
c_func
(paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
comma
id|logo_clut
(braket
id|k
)braket
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|k
op_eq
id|logo_clutsize
)paren
(brace
r_if
c_cond
(paren
id|logo_clutsize
op_eq
id|MAX_LINUX_LOGO_COLORS
)paren
id|die
c_func
(paren
l_string|&quot;Image has more than %d colors&bslash;n&quot;
comma
id|MAX_LINUX_LOGO_COLORS
)paren
suffix:semicolon
id|logo_clut
(braket
id|logo_clutsize
op_increment
)braket
op_assign
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/* write file header */
id|write_header
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* write logo data */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|logo_width
suffix:semicolon
id|j
op_increment
)paren
(brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|logo_clutsize
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|is_equal
c_func
(paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
comma
id|logo_clut
(braket
id|k
)braket
)paren
)paren
r_break
suffix:semicolon
id|write_hex
c_func
(paren
id|k
op_plus
l_int|32
)paren
suffix:semicolon
)brace
id|fputs
c_func
(paren
l_string|&quot;&bslash;n};&bslash;n&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
multiline_comment|/* write logo clut */
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;static const unsigned char %s_clut[] __initdata = {&bslash;n&quot;
comma
id|logoname
)paren
suffix:semicolon
id|write_hex_cnt
op_assign
l_int|0
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
id|logo_clutsize
suffix:semicolon
id|i
op_increment
)paren
(brace
id|write_hex
c_func
(paren
id|logo_clut
(braket
id|i
)braket
dot
id|red
)paren
suffix:semicolon
id|write_hex
c_func
(paren
id|logo_clut
(braket
id|i
)braket
dot
id|green
)paren
suffix:semicolon
id|write_hex
c_func
(paren
id|logo_clut
(braket
id|i
)braket
dot
id|blue
)paren
suffix:semicolon
)brace
multiline_comment|/* write logo structure and file footer */
id|write_footer
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|write_logo_gray256
r_static
r_void
id|write_logo_gray256
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
multiline_comment|/* validate image */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|logo_width
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|is_gray
c_func
(paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Image must be grayscale&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* write file header */
id|write_header
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* write logo data */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|logo_height
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|logo_width
suffix:semicolon
id|j
op_increment
)paren
id|write_hex
c_func
(paren
id|logo_data
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|red
)paren
suffix:semicolon
multiline_comment|/* write logo structure and file footer */
id|write_footer
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|die
r_static
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|vfprintf
c_func
(paren
id|stderr
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|usage
r_static
r_void
id|usage
c_func
(paren
r_void
)paren
(brace
id|die
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;Usage: %s [options] &lt;filename&gt;&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;Valid options:&bslash;n&quot;
l_string|&quot;    -h          : display this usage information&bslash;n&quot;
l_string|&quot;    -n &lt;name&gt;   : specify logo name (default: linux_logo)&bslash;n&quot;
l_string|&quot;    -o &lt;output&gt; : output to file &lt;output&gt; instead of stdout&bslash;n&quot;
l_string|&quot;    -t &lt;type&gt;   : specify logo type, one of&bslash;n&quot;
l_string|&quot;                      mono    : monochrome black/white&bslash;n&quot;
l_string|&quot;                      vga16   : 16 colors VGA text palette&bslash;n&quot;
l_string|&quot;                      clut224 : 224 colors (default)&bslash;n&quot;
l_string|&quot;                      gray256 : 256 levels grayscale&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
comma
id|programname
)paren
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
r_int
id|opt
suffix:semicolon
id|programname
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|opterr
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|opt
op_assign
id|getopt
c_func
(paren
id|argc
comma
id|argv
comma
l_string|&quot;hn:o:t:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_eq
op_minus
l_int|1
)paren
r_break
suffix:semicolon
r_switch
c_cond
(paren
id|opt
)paren
(brace
r_case
l_char|&squot;h&squot;
suffix:colon
id|usage
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
id|logoname
op_assign
id|optarg
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;o&squot;
suffix:colon
id|outputname
op_assign
id|optarg
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;t&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|optarg
comma
l_string|&quot;mono&quot;
)paren
)paren
id|logo_type
op_assign
id|LINUX_LOGO_MONO
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|optarg
comma
l_string|&quot;vga16&quot;
)paren
)paren
id|logo_type
op_assign
id|LINUX_LOGO_VGA16
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|optarg
comma
l_string|&quot;clut224&quot;
)paren
)paren
id|logo_type
op_assign
id|LINUX_LOGO_CLUT224
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|optarg
comma
l_string|&quot;gray256&quot;
)paren
)paren
id|logo_type
op_assign
id|LINUX_LOGO_GRAY256
suffix:semicolon
r_else
id|usage
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|optind
op_ne
id|argc
op_minus
l_int|1
)paren
id|usage
c_func
(paren
)paren
suffix:semicolon
id|filename
op_assign
id|argv
(braket
id|optind
)braket
suffix:semicolon
id|read_image
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|logo_type
)paren
(brace
r_case
id|LINUX_LOGO_MONO
suffix:colon
id|write_logo_mono
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LINUX_LOGO_VGA16
suffix:colon
id|write_logo_vga16
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LINUX_LOGO_CLUT224
suffix:colon
id|write_logo_clut224
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LINUX_LOGO_GRAY256
suffix:colon
id|write_logo_gray256
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
