multiline_comment|/*&n; * include/asm-sparc64/xor.h&n; *&n; * High speed xor_block operation for RAID4/5 utilizing the&n; * UltraSparc Visual Instruction Set.&n; *&n; * Copyright (C) 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * You should have received a copy of the GNU General Public License&n; * (for example /usr/src/linux/COPYING); if not, write to the Free&n; * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;asm/pstate.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
r_extern
r_void
id|xor_vis_2
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
id|xor_vis_3
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
id|xor_vis_4
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
id|xor_vis_5
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
multiline_comment|/* XXX Ugh, write cheetah versions... -DaveM */
DECL|variable|xor_block_VIS
r_static
r_struct
id|xor_block_template
id|xor_block_VIS
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;VIS&quot;
comma
dot
id|do_2
op_assign
id|xor_vis_2
comma
dot
id|do_3
op_assign
id|xor_vis_3
comma
dot
id|do_4
op_assign
id|xor_vis_4
comma
dot
id|do_5
op_assign
id|xor_vis_5
comma
)brace
suffix:semicolon
DECL|macro|XOR_TRY_TEMPLATES
mdefine_line|#define XOR_TRY_TEMPLATES       xor_speed(&amp;xor_block_VIS)
eof
