multiline_comment|/*&n; * include/asm-ia64/xor.h&n; *&n; * Optimized RAID-5 checksumming functions for IA-64.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * You should have received a copy of the GNU General Public License&n; * (for example /usr/src/linux/COPYING); if not, write to the Free&n; * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
r_extern
r_void
id|xor_ia64_2
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xor_ia64_3
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xor_ia64_4
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xor_ia64_5
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
DECL|variable|xor_block_ia64
r_static
r_struct
id|xor_block_template
id|xor_block_ia64
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ia64&quot;
comma
dot
id|do_2
op_assign
id|xor_ia64_2
comma
dot
id|do_3
op_assign
id|xor_ia64_3
comma
dot
id|do_4
op_assign
id|xor_ia64_4
comma
dot
id|do_5
op_assign
id|xor_ia64_5
comma
)brace
suffix:semicolon
DECL|macro|XOR_TRY_TEMPLATES
mdefine_line|#define XOR_TRY_TEMPLATES&t;xor_speed(&amp;xor_block_ia64)
eof
