multiline_comment|/*&n; * hvconsole.c&n; * Copyright (C) 2004 Hollis Blanchard, IBM Corporation&n; *&n; * LPAR console support.&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/hvcall.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/hvconsole.h&gt;
DECL|function|hvc_get_chars
r_int
id|hvc_get_chars
c_func
(paren
r_int
id|index
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|got
suffix:semicolon
r_if
c_cond
(paren
id|plpar_hcall
c_func
(paren
id|H_GET_TERM_CHAR
comma
id|index
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|got
comma
(paren
r_int
r_int
op_star
)paren
id|buf
comma
(paren
r_int
r_int
op_star
)paren
id|buf
op_plus
l_int|1
)paren
op_eq
id|H_Success
)paren
(brace
multiline_comment|/*&n;&t;&t; * Work around a HV bug where it gives us a null&n;&t;&t; * after every &bslash;r.  -- paulus&n;&t;&t; */
r_if
c_cond
(paren
id|got
OG
l_int|0
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|got
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_eq
l_int|0
op_logical_and
id|buf
(braket
id|i
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;r&squot;
)paren
(brace
op_decrement
id|got
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|got
)paren
id|memmove
c_func
(paren
op_amp
id|buf
(braket
id|i
)braket
comma
op_amp
id|buf
(braket
id|i
op_plus
l_int|1
)braket
comma
id|got
op_minus
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|got
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hvc_put_chars
r_int
id|hvc_put_chars
c_func
(paren
r_int
id|index
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
op_star
id|lbuf
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|plpar_hcall_norets
c_func
(paren
id|H_PUT_TERM_CHAR
comma
id|index
comma
id|count
comma
id|lbuf
(braket
l_int|0
)braket
comma
id|lbuf
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|H_Success
)paren
r_return
id|count
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|H_Busy
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* return the number of client vterms present */
multiline_comment|/* XXX this requires an interface change to handle multiple discontiguous&n; * vterms */
DECL|function|hvc_count
r_int
id|hvc_count
c_func
(paren
r_int
op_star
id|start_termno
)paren
(brace
r_struct
id|device_node
op_star
id|vty
suffix:semicolon
r_int
id|num_found
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* consider only the first vty node.&n;&t; * we should _always_ be able to find one. */
id|vty
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;vty&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vty
op_logical_and
id|device_is_compatible
c_func
(paren
id|vty
comma
l_string|&quot;hvterm1&quot;
)paren
)paren
(brace
id|u32
op_star
id|termno
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|vty
comma
l_string|&quot;reg&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|termno
op_logical_and
id|start_termno
)paren
op_star
id|start_termno
op_assign
op_star
id|termno
suffix:semicolon
id|num_found
op_assign
l_int|1
suffix:semicolon
id|of_node_put
c_func
(paren
id|vty
)paren
suffix:semicolon
)brace
r_return
id|num_found
suffix:semicolon
)brace
eof
