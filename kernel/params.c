multiline_comment|/* Helpers for initial module or kernel cmdline parsing&n;   Copyright (C) 2001 Rusty Russell.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(fmt, a...)
macro_line|#endif
DECL|function|dash2underscore
r_static
r_inline
r_int
id|dash2underscore
c_func
(paren
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;-&squot;
)paren
r_return
l_char|&squot;_&squot;
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
DECL|function|parameq
r_static
r_inline
r_int
id|parameq
c_func
(paren
r_const
r_char
op_star
id|input
comma
r_const
r_char
op_star
id|paramname
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
id|dash2underscore
c_func
(paren
id|input
(braket
id|i
)braket
)paren
op_eq
id|paramname
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|input
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_one
r_static
r_int
id|parse_one
c_func
(paren
r_char
op_star
id|param
comma
r_char
op_star
id|val
comma
r_struct
id|kernel_param
op_star
id|params
comma
r_int
id|num_params
comma
r_int
(paren
op_star
id|handle_unknown
)paren
(paren
r_char
op_star
id|param
comma
r_char
op_star
id|val
)paren
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Find parameter */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_params
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|parameq
c_func
(paren
id|param
comma
id|params
(braket
id|i
)braket
dot
id|name
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;They are equal!  Calling %p&bslash;n&quot;
comma
id|params
(braket
id|i
)braket
dot
id|set
)paren
suffix:semicolon
r_return
id|params
(braket
id|i
)braket
dot
id|set
c_func
(paren
id|val
comma
op_amp
id|params
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|handle_unknown
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Unknown argument: calling %p&bslash;n&quot;
comma
id|handle_unknown
)paren
suffix:semicolon
r_return
id|handle_unknown
c_func
(paren
id|param
comma
id|val
)paren
suffix:semicolon
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;Unknown argument `%s&squot;&bslash;n&quot;
comma
id|param
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
multiline_comment|/* You can use &quot; around spaces, but can&squot;t escape &quot;. */
multiline_comment|/* Hyphens and underscores equivalent in parameter names. */
DECL|function|next_arg
r_static
r_char
op_star
id|next_arg
c_func
(paren
r_char
op_star
id|args
comma
r_char
op_star
op_star
id|param
comma
r_char
op_star
op_star
id|val
)paren
(brace
r_int
r_int
id|i
comma
id|equals
op_assign
l_int|0
suffix:semicolon
r_int
id|in_quote
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Chew any extra spaces */
r_while
c_loop
(paren
op_star
id|args
op_eq
l_char|&squot; &squot;
)paren
id|args
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|args
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|args
(braket
id|i
)braket
op_eq
l_char|&squot; &squot;
op_logical_and
op_logical_neg
id|in_quote
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|equals
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|args
(braket
id|i
)braket
op_eq
l_char|&squot;=&squot;
)paren
id|equals
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|args
(braket
id|i
)braket
op_eq
l_char|&squot;&quot;&squot;
)paren
id|in_quote
op_assign
op_logical_neg
id|in_quote
suffix:semicolon
)brace
op_star
id|param
op_assign
id|args
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|equals
)paren
op_star
id|val
op_assign
l_int|NULL
suffix:semicolon
r_else
(brace
id|args
(braket
id|equals
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|val
op_assign
id|args
op_plus
id|equals
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Don&squot;t include quotes in value. */
r_if
c_cond
(paren
op_star
op_star
id|val
op_eq
l_char|&squot;&quot;&squot;
)paren
(brace
(paren
op_star
id|val
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|args
(braket
id|i
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&quot;&squot;
)paren
id|args
(braket
id|i
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|args
(braket
id|i
)braket
)paren
(brace
id|args
(braket
id|i
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|args
op_plus
id|i
op_plus
l_int|1
suffix:semicolon
)brace
r_else
r_return
id|args
op_plus
id|i
suffix:semicolon
)brace
multiline_comment|/* Args looks like &quot;foo=bar,bar2 baz=fuz wiz&quot;. */
DECL|function|parse_args
r_int
id|parse_args
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_char
op_star
id|args
comma
r_struct
id|kernel_param
op_star
id|params
comma
r_int
id|num
comma
r_int
(paren
op_star
id|unknown
)paren
(paren
r_char
op_star
id|param
comma
r_char
op_star
id|val
)paren
)paren
(brace
r_char
op_star
id|param
comma
op_star
id|val
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Parsing ARGS: %s&bslash;n&quot;
comma
id|args
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|args
)paren
(brace
r_int
id|ret
suffix:semicolon
id|args
op_assign
id|next_arg
c_func
(paren
id|args
comma
op_amp
id|param
comma
op_amp
id|val
)paren
suffix:semicolon
id|ret
op_assign
id|parse_one
c_func
(paren
id|param
comma
id|val
comma
id|params
comma
id|num
comma
id|unknown
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ret
)paren
(brace
r_case
op_minus
id|ENOENT
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Unknown parameter `%s&squot;&bslash;n&quot;
comma
id|name
comma
id|param
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_case
op_minus
id|ENOSPC
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: `%s&squot; too large for parameter `%s&squot;&bslash;n&quot;
comma
id|name
comma
id|val
ques
c_cond
suffix:colon
l_string|&quot;&quot;
comma
id|param
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: `%s&squot; invalid for parameter `%s&squot;&bslash;n&quot;
comma
id|name
comma
id|val
ques
c_cond
suffix:colon
l_string|&quot;&quot;
comma
id|param
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
multiline_comment|/* All parsed OK. */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Lazy bastard, eh? */
DECL|macro|STANDARD_PARAM_DEF
mdefine_line|#define STANDARD_PARAM_DEF(name, type, format, tmptype, strtolfn)      &t;&bslash;&n;&t;int param_set_##name(const char *val, struct kernel_param *kp)&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;char *endp;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;tmptype l;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!val) return -EINVAL;&t;&t;&t;&t;&bslash;&n;&t;&t;l = strtolfn(val, &amp;endp, 0);&t;&t;&t;&t;&bslash;&n;&t;&t;if (endp == val || ((type)l != l))&t;&t;&t;&bslash;&n;&t;&t;&t;return -EINVAL;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*((type *)kp-&gt;arg) = l;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int param_get_##name(char *buffer, struct kernel_param *kp)&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return sprintf(buffer, format, *((type *)kp-&gt;arg));&t;&bslash;&n;&t;}
id|STANDARD_PARAM_DEF
c_func
(paren
id|byte
comma
r_int
r_char
comma
l_string|&quot;%c&quot;
comma
r_int
r_int
comma
id|simple_strtoul
)paren
suffix:semicolon
id|STANDARD_PARAM_DEF
c_func
(paren
r_int
comma
r_int
comma
l_string|&quot;%hi&quot;
comma
r_int
comma
id|simple_strtol
)paren
suffix:semicolon
id|STANDARD_PARAM_DEF
c_func
(paren
id|ushort
comma
r_int
r_int
comma
l_string|&quot;%hu&quot;
comma
r_int
r_int
comma
id|simple_strtoul
)paren
suffix:semicolon
id|STANDARD_PARAM_DEF
c_func
(paren
r_int
comma
r_int
comma
l_string|&quot;%i&quot;
comma
r_int
comma
id|simple_strtol
)paren
suffix:semicolon
id|STANDARD_PARAM_DEF
c_func
(paren
id|uint
comma
r_int
r_int
comma
l_string|&quot;%u&quot;
comma
r_int
r_int
comma
id|simple_strtoul
)paren
suffix:semicolon
id|STANDARD_PARAM_DEF
c_func
(paren
r_int
comma
r_int
comma
l_string|&quot;%li&quot;
comma
r_int
comma
id|simple_strtol
)paren
suffix:semicolon
id|STANDARD_PARAM_DEF
c_func
(paren
id|ulong
comma
r_int
r_int
comma
l_string|&quot;%lu&quot;
comma
r_int
r_int
comma
id|simple_strtoul
)paren
suffix:semicolon
DECL|function|param_set_charp
r_int
id|param_set_charp
c_func
(paren
r_const
r_char
op_star
id|val
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: string parameter expected&bslash;n&quot;
comma
id|kp-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|val
)paren
OG
l_int|1024
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: string parameter too long&bslash;n&quot;
comma
id|kp-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
op_star
(paren
r_char
op_star
op_star
)paren
id|kp-&gt;arg
op_assign
(paren
r_char
op_star
)paren
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|param_get_charp
r_int
id|param_get_charp
c_func
(paren
r_char
op_star
id|buffer
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s&quot;
comma
op_star
(paren
(paren
r_char
op_star
op_star
)paren
id|kp-&gt;arg
)paren
)paren
suffix:semicolon
)brace
DECL|function|param_set_bool
r_int
id|param_set_bool
c_func
(paren
r_const
r_char
op_star
id|val
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
(brace
multiline_comment|/* No equals means &quot;set&quot;... */
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
id|val
op_assign
l_string|&quot;1&quot;
suffix:semicolon
multiline_comment|/* One of =[yYnN01] */
r_switch
c_cond
(paren
id|val
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;y&squot;
suffix:colon
r_case
l_char|&squot;Y&squot;
suffix:colon
r_case
l_char|&squot;1&squot;
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|kp-&gt;arg
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
r_case
l_char|&squot;N&squot;
suffix:colon
r_case
l_char|&squot;0&squot;
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|kp-&gt;arg
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|param_get_bool
r_int
id|param_get_bool
c_func
(paren
r_char
op_star
id|buffer
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
(brace
multiline_comment|/* Y and N chosen as being relatively non-coder friendly */
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%c&quot;
comma
(paren
op_star
(paren
r_int
op_star
)paren
id|kp-&gt;arg
)paren
ques
c_cond
l_char|&squot;Y&squot;
suffix:colon
l_char|&squot;N&squot;
)paren
suffix:semicolon
)brace
DECL|function|param_set_invbool
r_int
id|param_set_invbool
c_func
(paren
r_const
r_char
op_star
id|val
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
(brace
r_int
id|boolval
comma
id|ret
suffix:semicolon
r_struct
id|kernel_param
id|dummy
op_assign
(brace
dot
id|arg
op_assign
op_amp
id|boolval
)brace
suffix:semicolon
id|ret
op_assign
id|param_set_bool
c_func
(paren
id|val
comma
op_amp
id|dummy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
op_star
(paren
r_int
op_star
)paren
id|kp-&gt;arg
op_assign
op_logical_neg
id|boolval
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|param_get_invbool
r_int
id|param_get_invbool
c_func
(paren
r_char
op_star
id|buffer
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
(brace
r_int
id|val
suffix:semicolon
r_struct
id|kernel_param
id|dummy
op_assign
(brace
dot
id|arg
op_assign
op_amp
id|val
)brace
suffix:semicolon
id|val
op_assign
op_logical_neg
op_star
(paren
r_int
op_star
)paren
id|kp-&gt;arg
suffix:semicolon
r_return
id|param_get_bool
c_func
(paren
id|buffer
comma
op_amp
id|dummy
)paren
suffix:semicolon
)brace
multiline_comment|/* We cheat here and temporarily mangle the string. */
DECL|function|param_array
r_int
id|param_array
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|val
comma
r_int
r_int
id|min
comma
r_int
r_int
id|max
comma
r_void
op_star
id|elem
comma
r_int
id|elemsize
comma
r_int
(paren
op_star
id|set
)paren
(paren
r_const
r_char
op_star
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
comma
r_int
op_star
id|num
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|kernel_param
id|kp
suffix:semicolon
r_char
id|save
suffix:semicolon
multiline_comment|/* Get the name right for errors. */
id|kp.name
op_assign
id|name
suffix:semicolon
id|kp.arg
op_assign
id|elem
suffix:semicolon
multiline_comment|/* No equals sign? */
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: expects arguments&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
op_star
id|num
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* We expect a comma-separated list of values. */
r_do
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_star
id|num
op_eq
id|max
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: can only take %i arguments&bslash;n&quot;
comma
id|name
comma
id|max
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|len
op_assign
id|strcspn
c_func
(paren
id|val
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
multiline_comment|/* nul-terminate and parse */
id|save
op_assign
id|val
(braket
id|len
)braket
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|val
)paren
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|ret
op_assign
id|set
c_func
(paren
id|val
comma
op_amp
id|kp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|kp.arg
op_add_assign
id|elemsize
suffix:semicolon
id|val
op_add_assign
id|len
op_plus
l_int|1
suffix:semicolon
(paren
op_star
id|num
)paren
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|save
op_eq
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|num
OL
id|min
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: needs at least %i arguments&bslash;n&quot;
comma
id|name
comma
id|min
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|param_array_set
r_int
id|param_array_set
c_func
(paren
r_const
r_char
op_star
id|val
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
(brace
r_struct
id|kparam_array
op_star
id|arr
op_assign
id|kp-&gt;arg
suffix:semicolon
r_return
id|param_array
c_func
(paren
id|kp-&gt;name
comma
id|val
comma
l_int|1
comma
id|arr-&gt;max
comma
id|arr-&gt;elem
comma
id|arr-&gt;elemsize
comma
id|arr-&gt;set
comma
id|arr-&gt;num
)paren
suffix:semicolon
)brace
DECL|function|param_array_get
r_int
id|param_array_get
c_func
(paren
r_char
op_star
id|buffer
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
(brace
r_int
id|i
comma
id|off
comma
id|ret
suffix:semicolon
r_struct
id|kparam_array
op_star
id|arr
op_assign
id|kp-&gt;arg
suffix:semicolon
r_struct
id|kernel_param
id|p
suffix:semicolon
id|p
op_assign
op_star
id|kp
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|off
op_assign
l_int|0
suffix:semicolon
id|i
OL
op_star
id|arr-&gt;num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
)paren
id|buffer
(braket
id|off
op_increment
)braket
op_assign
l_char|&squot;,&squot;
suffix:semicolon
id|p.arg
op_assign
id|arr-&gt;elem
op_plus
id|arr-&gt;elemsize
op_star
id|i
suffix:semicolon
id|ret
op_assign
id|arr
op_member_access_from_pointer
id|get
c_func
(paren
id|buffer
op_plus
id|off
comma
op_amp
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|off
op_add_assign
id|ret
suffix:semicolon
)brace
id|buffer
(braket
id|off
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|off
suffix:semicolon
)brace
DECL|function|param_set_copystring
r_int
id|param_set_copystring
c_func
(paren
r_const
r_char
op_star
id|val
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
(brace
r_struct
id|kparam_string
op_star
id|kps
op_assign
id|kp-&gt;arg
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|val
)paren
op_plus
l_int|1
OG
id|kps-&gt;maxlen
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: string doesn&squot;t fit in %u chars.&bslash;n&quot;
comma
id|kp-&gt;name
comma
id|kps-&gt;maxlen
op_minus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|kps-&gt;string
comma
id|val
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|param_get_string
r_int
id|param_get_string
c_func
(paren
r_char
op_star
id|buffer
comma
r_struct
id|kernel_param
op_star
id|kp
)paren
(brace
r_struct
id|kparam_string
op_star
id|kps
op_assign
id|kp-&gt;arg
suffix:semicolon
r_return
id|strlcpy
c_func
(paren
id|buffer
comma
id|kps-&gt;string
comma
id|kps-&gt;maxlen
)paren
suffix:semicolon
)brace
DECL|variable|param_set_byte
id|EXPORT_SYMBOL
c_func
(paren
id|param_set_byte
)paren
suffix:semicolon
DECL|variable|param_get_byte
id|EXPORT_SYMBOL
c_func
(paren
id|param_get_byte
)paren
suffix:semicolon
DECL|variable|param_set_short
id|EXPORT_SYMBOL
c_func
(paren
id|param_set_short
)paren
suffix:semicolon
DECL|variable|param_get_short
id|EXPORT_SYMBOL
c_func
(paren
id|param_get_short
)paren
suffix:semicolon
DECL|variable|param_set_ushort
id|EXPORT_SYMBOL
c_func
(paren
id|param_set_ushort
)paren
suffix:semicolon
DECL|variable|param_get_ushort
id|EXPORT_SYMBOL
c_func
(paren
id|param_get_ushort
)paren
suffix:semicolon
DECL|variable|param_set_int
id|EXPORT_SYMBOL
c_func
(paren
id|param_set_int
)paren
suffix:semicolon
DECL|variable|param_get_int
id|EXPORT_SYMBOL
c_func
(paren
id|param_get_int
)paren
suffix:semicolon
DECL|variable|param_set_uint
id|EXPORT_SYMBOL
c_func
(paren
id|param_set_uint
)paren
suffix:semicolon
DECL|variable|param_get_uint
id|EXPORT_SYMBOL
c_func
(paren
id|param_get_uint
)paren
suffix:semicolon
DECL|variable|param_set_long
id|EXPORT_SYMBOL
c_func
(paren
id|param_set_long
)paren
suffix:semicolon
DECL|variable|param_get_long
id|EXPORT_SYMBOL
c_func
(paren
id|param_get_long
)paren
suffix:semicolon
DECL|variable|param_set_ulong
id|EXPORT_SYMBOL
c_func
(paren
id|param_set_ulong
)paren
suffix:semicolon
DECL|variable|param_get_ulong
id|EXPORT_SYMBOL
c_func
(paren
id|param_get_ulong
)paren
suffix:semicolon
DECL|variable|param_set_charp
id|EXPORT_SYMBOL
c_func
(paren
id|param_set_charp
)paren
suffix:semicolon
DECL|variable|param_get_charp
id|EXPORT_SYMBOL
c_func
(paren
id|param_get_charp
)paren
suffix:semicolon
DECL|variable|param_set_bool
id|EXPORT_SYMBOL
c_func
(paren
id|param_set_bool
)paren
suffix:semicolon
DECL|variable|param_get_bool
id|EXPORT_SYMBOL
c_func
(paren
id|param_get_bool
)paren
suffix:semicolon
DECL|variable|param_set_invbool
id|EXPORT_SYMBOL
c_func
(paren
id|param_set_invbool
)paren
suffix:semicolon
DECL|variable|param_get_invbool
id|EXPORT_SYMBOL
c_func
(paren
id|param_get_invbool
)paren
suffix:semicolon
DECL|variable|param_array_set
id|EXPORT_SYMBOL
c_func
(paren
id|param_array_set
)paren
suffix:semicolon
DECL|variable|param_array_get
id|EXPORT_SYMBOL
c_func
(paren
id|param_array_get
)paren
suffix:semicolon
DECL|variable|param_set_copystring
id|EXPORT_SYMBOL
c_func
(paren
id|param_set_copystring
)paren
suffix:semicolon
DECL|variable|param_get_string
id|EXPORT_SYMBOL
c_func
(paren
id|param_get_string
)paren
suffix:semicolon
eof
