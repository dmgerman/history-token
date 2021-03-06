multiline_comment|/*&n; *&n; *  Copyright (C) 1996 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|macro|VIDMEM
mdefine_line|#define VIDMEM ((char *)0x02000000)
DECL|variable|video_num_columns
DECL|variable|video_num_lines
DECL|variable|video_size_row
r_int
id|video_num_columns
comma
id|video_num_lines
comma
id|video_size_row
suffix:semicolon
DECL|variable|white
DECL|variable|bytes_per_char_h
r_int
id|white
comma
id|bytes_per_char_h
suffix:semicolon
r_extern
r_int
r_int
id|con_charconvtable
(braket
l_int|256
)braket
suffix:semicolon
DECL|struct|param_struct
r_struct
id|param_struct
(brace
DECL|member|page_size
r_int
r_int
id|page_size
suffix:semicolon
DECL|member|nr_pages
r_int
r_int
id|nr_pages
suffix:semicolon
DECL|member|ramdisk_size
r_int
r_int
id|ramdisk_size
suffix:semicolon
DECL|member|mountrootrdonly
r_int
r_int
id|mountrootrdonly
suffix:semicolon
DECL|member|rootdev
r_int
r_int
id|rootdev
suffix:semicolon
DECL|member|video_num_cols
r_int
r_int
id|video_num_cols
suffix:semicolon
DECL|member|video_num_rows
r_int
r_int
id|video_num_rows
suffix:semicolon
DECL|member|video_x
r_int
r_int
id|video_x
suffix:semicolon
DECL|member|video_y
r_int
r_int
id|video_y
suffix:semicolon
DECL|member|memc_control_reg
r_int
r_int
id|memc_control_reg
suffix:semicolon
DECL|member|sounddefault
r_int
r_char
id|sounddefault
suffix:semicolon
DECL|member|adfsdrives
r_int
r_char
id|adfsdrives
suffix:semicolon
DECL|member|bytes_per_char_h
r_int
r_char
id|bytes_per_char_h
suffix:semicolon
DECL|member|bytes_per_char_v
r_int
r_char
id|bytes_per_char_v
suffix:semicolon
DECL|member|unused
r_int
r_int
id|unused
(braket
l_int|256
op_div
l_int|4
op_minus
l_int|11
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|params
r_static
r_struct
id|param_struct
op_star
id|params
op_assign
(paren
r_struct
id|param_struct
op_star
)paren
l_int|0x0207c000
suffix:semicolon
multiline_comment|/*&n; * This does not append a newline&n; */
DECL|function|puts
r_static
r_void
id|puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_extern
r_void
id|ll_write_char
c_func
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|x
comma
id|y
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
r_char
op_star
id|ptr
suffix:semicolon
id|x
op_assign
id|params-&gt;video_x
suffix:semicolon
id|y
op_assign
id|params-&gt;video_y
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|s
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|y
op_ge
id|video_num_lines
)paren
(brace
id|y
op_decrement
suffix:semicolon
)brace
)brace
r_else
(brace
id|ptr
op_assign
id|VIDMEM
op_plus
(paren
(paren
id|y
op_star
id|video_num_columns
op_star
id|params-&gt;bytes_per_char_v
op_plus
id|x
)paren
op_star
id|bytes_per_char_h
)paren
suffix:semicolon
id|ll_write_char
c_func
(paren
id|ptr
comma
id|c
op_or
(paren
id|white
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|x
op_ge
id|video_num_columns
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|y
op_ge
id|video_num_lines
)paren
(brace
id|y
op_decrement
suffix:semicolon
)brace
)brace
)brace
)brace
id|params-&gt;video_x
op_assign
id|x
suffix:semicolon
id|params-&gt;video_y
op_assign
id|y
suffix:semicolon
)brace
r_static
r_void
id|error
c_func
(paren
r_char
op_star
id|x
)paren
suffix:semicolon
multiline_comment|/*&n; * Setup for decompression&n; */
DECL|function|arch_decomp_setup
r_static
r_void
id|arch_decomp_setup
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|video_num_lines
op_assign
id|params-&gt;video_num_rows
suffix:semicolon
id|video_num_columns
op_assign
id|params-&gt;video_num_cols
suffix:semicolon
id|bytes_per_char_h
op_assign
id|params-&gt;bytes_per_char_h
suffix:semicolon
id|video_size_row
op_assign
id|video_num_columns
op_star
id|bytes_per_char_h
suffix:semicolon
r_if
c_cond
(paren
id|bytes_per_char_h
op_eq
l_int|4
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
id|con_charconvtable
(braket
id|i
)braket
op_assign
(paren
id|i
op_amp
l_int|128
ques
c_cond
l_int|1
op_lshift
l_int|0
suffix:colon
l_int|0
)paren
op_or
(paren
id|i
op_amp
l_int|64
ques
c_cond
l_int|1
op_lshift
l_int|4
suffix:colon
l_int|0
)paren
op_or
(paren
id|i
op_amp
l_int|32
ques
c_cond
l_int|1
op_lshift
l_int|8
suffix:colon
l_int|0
)paren
op_or
(paren
id|i
op_amp
l_int|16
ques
c_cond
l_int|1
op_lshift
l_int|12
suffix:colon
l_int|0
)paren
op_or
(paren
id|i
op_amp
l_int|8
ques
c_cond
l_int|1
op_lshift
l_int|16
suffix:colon
l_int|0
)paren
op_or
(paren
id|i
op_amp
l_int|4
ques
c_cond
l_int|1
op_lshift
l_int|20
suffix:colon
l_int|0
)paren
op_or
(paren
id|i
op_amp
l_int|2
ques
c_cond
l_int|1
op_lshift
l_int|24
suffix:colon
l_int|0
)paren
op_or
(paren
id|i
op_amp
l_int|1
ques
c_cond
l_int|1
op_lshift
l_int|28
suffix:colon
l_int|0
)paren
suffix:semicolon
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|con_charconvtable
(braket
id|i
)braket
op_assign
(paren
id|i
op_amp
l_int|8
ques
c_cond
l_int|1
op_lshift
l_int|0
suffix:colon
l_int|0
)paren
op_or
(paren
id|i
op_amp
l_int|4
ques
c_cond
l_int|1
op_lshift
l_int|8
suffix:colon
l_int|0
)paren
op_or
(paren
id|i
op_amp
l_int|2
ques
c_cond
l_int|1
op_lshift
l_int|16
suffix:colon
l_int|0
)paren
op_or
(paren
id|i
op_amp
l_int|1
ques
c_cond
l_int|1
op_lshift
l_int|24
suffix:colon
l_int|0
)paren
suffix:semicolon
id|white
op_assign
id|bytes_per_char_h
op_eq
l_int|8
ques
c_cond
l_int|0xfc
suffix:colon
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;nr_pages
op_star
id|params-&gt;page_size
OL
l_int|4096
op_star
l_int|1024
)paren
id|error
c_func
(paren
l_string|&quot;&lt;4M of mem&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * nothing to do&n; */
DECL|macro|arch_decomp_wdog
mdefine_line|#define arch_decomp_wdog()
eof
