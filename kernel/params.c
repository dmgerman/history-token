multiline_comment|/* Helpers for initial module or kernel cmdline parsing&n;   Copyright (C) 2001 Rusty Russell.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/err.h&gt;
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
ques
c_cond
suffix:colon
op_amp
id|arr-&gt;max
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
(paren
id|arr-&gt;num
ques
c_cond
op_star
id|arr-&gt;num
suffix:colon
id|arr-&gt;max
)paren
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
multiline_comment|/* sysfs output in /sys/modules/XYZ/parameters/ */
r_extern
r_struct
id|kernel_param
id|__start___param
(braket
)braket
comma
id|__stop___param
(braket
)braket
suffix:semicolon
DECL|macro|MAX_KBUILD_MODNAME
mdefine_line|#define MAX_KBUILD_MODNAME KOBJ_NAME_LEN
DECL|struct|param_attribute
r_struct
id|param_attribute
(brace
DECL|member|attr
r_struct
id|attribute
id|attr
suffix:semicolon
DECL|member|param
r_struct
id|kernel_param
op_star
id|param
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|param_kobject
r_struct
id|param_kobject
(brace
DECL|member|kobj
r_struct
id|kobject
id|kobj
suffix:semicolon
DECL|member|num_attributes
r_int
r_int
id|num_attributes
suffix:semicolon
DECL|member|attr
r_struct
id|param_attribute
id|attr
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_param_attr
mdefine_line|#define to_param_attr(n) container_of(n, struct param_attribute, attr);
DECL|function|param_attr_show
r_static
id|ssize_t
id|param_attr_show
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|count
suffix:semicolon
r_struct
id|param_attribute
op_star
id|attribute
op_assign
id|to_param_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attribute-&gt;param-&gt;get
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|count
op_assign
id|attribute-&gt;param
op_member_access_from_pointer
id|get
c_func
(paren
id|buf
comma
id|attribute-&gt;param
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
id|strcat
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
op_increment
id|count
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/* sysfs always hands a nul-terminated string in buf.  We rely on that. */
DECL|function|param_attr_store
r_static
id|ssize_t
id|param_attr_store
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|param_attribute
op_star
id|attribute
op_assign
id|to_param_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attribute-&gt;param-&gt;set
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|err
op_assign
id|attribute-&gt;param
op_member_access_from_pointer
id|set
c_func
(paren
id|buf
comma
id|attribute-&gt;param
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
r_return
id|len
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|param_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|param_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
id|param_attr_show
comma
dot
id|store
op_assign
id|param_attr_store
comma
)brace
suffix:semicolon
DECL|function|param_kobj_release
r_static
r_void
id|param_kobj_release
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
id|kfree
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|param_kobject
comma
id|kobj
)paren
)paren
suffix:semicolon
)brace
DECL|variable|param_ktype
r_static
r_struct
id|kobj_type
id|param_ktype
op_assign
(brace
dot
id|sysfs_ops
op_assign
op_amp
id|param_sysfs_ops
comma
dot
id|release
op_assign
op_amp
id|param_kobj_release
comma
)brace
suffix:semicolon
DECL|variable|param_kset
r_static
r_struct
id|kset
id|param_kset
op_assign
(brace
dot
id|subsys
op_assign
op_amp
id|module_subsys
comma
dot
id|ktype
op_assign
op_amp
id|param_ktype
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_MODULES
DECL|macro|__modinit
mdefine_line|#define __modinit
macro_line|#else
DECL|macro|__modinit
mdefine_line|#define __modinit __init
macro_line|#endif
multiline_comment|/*&n; * param_add_attribute - actually adds an parameter to sysfs&n; * @mod: owner of parameter&n; * @pk: param_kobject the attribute shall be assigned to.&n; *      One per module, one per KBUILD_MODNAME.&n; * @kp: kernel_param to be added&n; * @skip: offset where the parameter name start in kp-&gt;name.&n; * Needed for built-in modules&n; *&n; * Fill in data into appropriate &amp;pk-&gt;attr[], and create sysfs file.&n; */
DECL|function|param_add_attribute
r_static
id|__modinit
r_int
id|param_add_attribute
c_func
(paren
r_struct
id|module
op_star
id|mod
comma
r_struct
id|param_kobject
op_star
id|pk
comma
r_struct
id|kernel_param
op_star
id|kp
comma
r_int
r_int
id|skip
)paren
(brace
r_struct
id|param_attribute
op_star
id|a
suffix:semicolon
r_int
id|err
suffix:semicolon
id|a
op_assign
op_amp
id|pk-&gt;attr
(braket
id|pk-&gt;num_attributes
)braket
suffix:semicolon
id|a-&gt;attr.name
op_assign
(paren
r_char
op_star
)paren
op_amp
id|kp-&gt;name
(braket
id|skip
)braket
suffix:semicolon
id|a-&gt;attr.owner
op_assign
id|mod
suffix:semicolon
id|a-&gt;attr.mode
op_assign
id|kp-&gt;perm
suffix:semicolon
id|a-&gt;param
op_assign
id|kp
suffix:semicolon
id|err
op_assign
id|sysfs_create_file
c_func
(paren
op_amp
id|pk-&gt;kobj
comma
op_amp
id|a-&gt;attr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|pk-&gt;num_attributes
op_increment
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * param_sysfs_remove - remove sysfs support for one module or KBUILD_MODNAME&n; * @pk: struct param_kobject which is to be removed&n; *&n; * Called when an error in registration occurs or a module is removed&n; * from the system.&n; */
DECL|function|param_sysfs_remove
r_static
id|__modinit
r_void
id|param_sysfs_remove
c_func
(paren
r_struct
id|param_kobject
op_star
id|pk
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
id|pk-&gt;num_attributes
suffix:semicolon
id|i
op_increment
)paren
id|sysfs_remove_file
c_func
(paren
op_amp
id|pk-&gt;kobj
comma
op_amp
id|pk-&gt;attr
(braket
id|i
)braket
dot
id|attr
)paren
suffix:semicolon
multiline_comment|/* Calls param_kobj_release */
id|kobject_unregister
c_func
(paren
op_amp
id|pk-&gt;kobj
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * param_sysfs_setup - setup sysfs support for one module or KBUILD_MODNAME&n; * @mk: struct module_kobject (contains parent kobject)&n; * @kparam: array of struct kernel_param, the actual parameter definitions&n; * @num_params: number of entries in array&n; * @name_skip: offset where the parameter name start in kparam[].name. Needed for built-in &quot;modules&quot;&n; *&n; * Create a kobject for a (per-module) group of parameters, and create files&n; * in sysfs. A pointer to the param_kobject is returned on success,&n; * NULL if there&squot;s no parameter to export, or other ERR_PTR(err).&n; */
r_static
id|__modinit
r_struct
id|param_kobject
op_star
DECL|function|param_sysfs_setup
id|param_sysfs_setup
c_func
(paren
r_struct
id|module_kobject
op_star
id|mk
comma
r_struct
id|kernel_param
op_star
id|kparam
comma
r_int
r_int
id|num_params
comma
r_int
r_int
id|name_skip
)paren
(brace
r_struct
id|param_kobject
op_star
id|pk
suffix:semicolon
r_int
r_int
id|valid_attrs
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
id|err
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
id|num_params
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|kparam
(braket
id|i
)braket
dot
id|perm
)paren
id|valid_attrs
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|valid_attrs
)paren
r_return
l_int|NULL
suffix:semicolon
id|pk
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|param_kobject
)paren
op_plus
r_sizeof
(paren
r_struct
id|param_attribute
)paren
op_star
id|valid_attrs
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pk
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pk
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|param_kobject
)paren
op_plus
r_sizeof
(paren
r_struct
id|param_attribute
)paren
op_star
id|valid_attrs
)paren
suffix:semicolon
id|err
op_assign
id|kobject_set_name
c_func
(paren
op_amp
id|pk-&gt;kobj
comma
l_string|&quot;parameters&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|pk-&gt;kobj.kset
op_assign
op_amp
id|param_kset
suffix:semicolon
id|pk-&gt;kobj.parent
op_assign
op_amp
id|mk-&gt;kobj
suffix:semicolon
id|err
op_assign
id|kobject_register
c_func
(paren
op_amp
id|pk-&gt;kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
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
id|num_params
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|kparam
(braket
id|i
)braket
dot
id|perm
)paren
(brace
id|err
op_assign
id|param_add_attribute
c_func
(paren
id|mk-&gt;mod
comma
id|pk
comma
op_amp
id|kparam
(braket
id|i
)braket
comma
id|name_skip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_unreg
suffix:semicolon
)brace
)brace
r_return
id|pk
suffix:semicolon
id|out_unreg
suffix:colon
id|param_sysfs_remove
c_func
(paren
id|pk
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|pk
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MODULES
multiline_comment|/*&n; * module_param_sysfs_setup - setup sysfs support for one module&n; * @mod: module&n; * @kparam: module parameters (array)&n; * @num_params: number of module parameters&n; *&n; * Adds sysfs entries for module parameters, and creates a link from&n; * /sys/module/[mod-&gt;name]/parameters to /sys/parameters/[mod-&gt;name]/&n; */
DECL|function|module_param_sysfs_setup
r_int
id|module_param_sysfs_setup
c_func
(paren
r_struct
id|module
op_star
id|mod
comma
r_struct
id|kernel_param
op_star
id|kparam
comma
r_int
r_int
id|num_params
)paren
(brace
r_struct
id|param_kobject
op_star
id|pk
suffix:semicolon
id|pk
op_assign
id|param_sysfs_setup
c_func
(paren
id|mod-&gt;mkobj
comma
id|kparam
comma
id|num_params
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|pk
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|pk
)paren
suffix:semicolon
id|mod-&gt;params_kobject
op_assign
id|pk
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * module_param_sysfs_remove - remove sysfs support for one module&n; * @mod: module&n; *&n; * Remove sysfs entries for module parameters and the corresponding&n; * kobject.&n; */
DECL|function|module_param_sysfs_remove
r_void
id|module_param_sysfs_remove
c_func
(paren
r_struct
id|module
op_star
id|mod
)paren
(brace
r_if
c_cond
(paren
id|mod-&gt;params_kobject
)paren
(brace
id|param_sysfs_remove
c_func
(paren
id|mod-&gt;params_kobject
)paren
suffix:semicolon
id|mod-&gt;params_kobject
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; * kernel_param_sysfs_setup - wrapper for built-in params support&n; */
DECL|function|kernel_param_sysfs_setup
r_static
r_void
id|__init
id|kernel_param_sysfs_setup
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|kernel_param
op_star
id|kparam
comma
r_int
r_int
id|num_params
comma
r_int
r_int
id|name_skip
)paren
(brace
r_struct
id|module_kobject
op_star
id|mk
suffix:semicolon
id|mk
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|module_kobject
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|mk
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|module_kobject
)paren
)paren
suffix:semicolon
id|mk-&gt;mod
op_assign
id|THIS_MODULE
suffix:semicolon
id|kobj_set_kset_s
c_func
(paren
id|mk
comma
id|module_subsys
)paren
suffix:semicolon
id|kobject_set_name
c_func
(paren
op_amp
id|mk-&gt;kobj
comma
id|name
)paren
suffix:semicolon
id|kobject_register
c_func
(paren
op_amp
id|mk-&gt;kobj
)paren
suffix:semicolon
multiline_comment|/* no need to keep the kobject if no parameter is exported */
r_if
c_cond
(paren
op_logical_neg
id|param_sysfs_setup
c_func
(paren
id|mk
comma
id|kparam
comma
id|num_params
comma
id|name_skip
)paren
)paren
id|kobject_unregister
c_func
(paren
op_amp
id|mk-&gt;kobj
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * param_sysfs_builtin - add contents in /sys/parameters for built-in modules&n; *&n; * Add module_parameters to sysfs for &quot;modules&quot; built into the kernel.&n; *&n; * The &quot;module&quot; name (KBUILD_MODNAME) is stored before a dot, the&n; * &quot;parameter&quot; name is stored behind a dot in kernel_param-&gt;name. So,&n; * extract the &quot;module&quot; name for all built-in kernel_param-eters,&n; * and for all who have the same, call kernel_param_sysfs_setup.&n; */
DECL|function|param_sysfs_builtin
r_static
r_void
id|__init
id|param_sysfs_builtin
c_func
(paren
r_void
)paren
(brace
r_struct
id|kernel_param
op_star
id|kp
comma
op_star
id|kp_begin
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|i
comma
id|name_len
comma
id|count
op_assign
l_int|0
suffix:semicolon
r_char
id|modname
(braket
id|MAX_KBUILD_MODNAME
op_plus
l_int|1
)braket
op_assign
l_string|&quot;&quot;
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
id|__stop___param
op_minus
id|__start___param
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
id|dot
suffix:semicolon
id|kp
op_assign
op_amp
id|__start___param
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* We do not handle args without periods. */
id|dot
op_assign
id|memchr
c_func
(paren
id|kp-&gt;name
comma
l_char|&squot;.&squot;
comma
id|MAX_KBUILD_MODNAME
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dot
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;couldn&squot;t find period in %s&bslash;n&quot;
comma
id|kp-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|name_len
op_assign
id|dot
op_minus
id|kp-&gt;name
suffix:semicolon
multiline_comment|/* new kbuild_modname? */
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|modname
)paren
op_ne
id|name_len
op_logical_or
id|strncmp
c_func
(paren
id|modname
comma
id|kp-&gt;name
comma
id|name_len
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* add a new kobject for previous kernel_params. */
r_if
c_cond
(paren
id|count
)paren
id|kernel_param_sysfs_setup
c_func
(paren
id|modname
comma
id|kp_begin
comma
id|count
comma
id|strlen
c_func
(paren
id|modname
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|modname
comma
id|kp-&gt;name
comma
id|name_len
)paren
suffix:semicolon
id|modname
(braket
id|name_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|kp_begin
op_assign
id|kp
suffix:semicolon
)brace
id|count
op_increment
suffix:semicolon
)brace
multiline_comment|/* last kernel_params need to be registered as well */
r_if
c_cond
(paren
id|count
)paren
id|kernel_param_sysfs_setup
c_func
(paren
id|modname
comma
id|kp_begin
comma
id|count
comma
id|strlen
c_func
(paren
id|modname
)paren
op_plus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* module-related sysfs stuff */
macro_line|#ifdef CONFIG_MODULES
DECL|macro|to_module_attr
mdefine_line|#define to_module_attr(n) container_of(n, struct module_attribute, attr);
DECL|macro|to_module_kobject
mdefine_line|#define to_module_kobject(n) container_of(n, struct module_kobject, kobj);
DECL|function|module_attr_show
r_static
id|ssize_t
id|module_attr_show
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|module_attribute
op_star
id|attribute
suffix:semicolon
r_struct
id|module_kobject
op_star
id|mk
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|attribute
op_assign
id|to_module_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
id|mk
op_assign
id|to_module_kobject
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attribute-&gt;show
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|mk-&gt;mod
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ret
op_assign
id|attribute
op_member_access_from_pointer
id|show
c_func
(paren
id|mk-&gt;mod
comma
id|buf
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|mk-&gt;mod
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|module_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|module_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
id|module_attr_show
comma
dot
id|store
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
macro_line|#else
DECL|variable|module_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|module_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
l_int|NULL
comma
dot
id|store
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|module_kobj_release
r_static
r_void
id|module_kobj_release
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
id|kfree
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|module_kobject
comma
id|kobj
)paren
)paren
suffix:semicolon
)brace
DECL|variable|module_ktype
r_static
r_struct
id|kobj_type
id|module_ktype
op_assign
(brace
dot
id|sysfs_ops
op_assign
op_amp
id|module_sysfs_ops
comma
dot
id|release
op_assign
op_amp
id|module_kobj_release
comma
)brace
suffix:semicolon
id|decl_subsys
c_func
(paren
id|module
comma
op_amp
id|module_ktype
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n; * param_sysfs_init - wrapper for built-in params support&n; */
DECL|function|param_sysfs_init
r_static
r_int
id|__init
id|param_sysfs_init
c_func
(paren
r_void
)paren
(brace
id|subsystem_register
c_func
(paren
op_amp
id|module_subsys
)paren
suffix:semicolon
id|kobject_set_name
c_func
(paren
op_amp
id|param_kset.kobj
comma
l_string|&quot;parameters&quot;
)paren
suffix:semicolon
id|kset_init
c_func
(paren
op_amp
id|param_kset
)paren
suffix:semicolon
id|param_sysfs_builtin
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|param_sysfs_init
id|__initcall
c_func
(paren
id|param_sysfs_init
)paren
suffix:semicolon
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
