multiline_comment|/*&n; * mf_proc.c&n; * Copyright (C) 2001 Kyle A. Lucke  IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/iSeries/mf.h&gt;
DECL|variable|mf_proc_root
r_static
r_struct
id|proc_dir_entry
op_star
id|mf_proc_root
op_assign
l_int|NULL
suffix:semicolon
DECL|function|proc_mf_dump_cmdline
r_static
r_int
id|proc_mf_dump_cmdline
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|count
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
id|len
op_assign
id|mf_getCmdLine
c_func
(paren
id|page
comma
op_amp
id|len
comma
(paren
id|u64
)paren
id|data
)paren
suffix:semicolon
id|p
op_assign
id|page
op_plus
id|len
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|p
OG
id|page
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|p
op_eq
l_int|0
)paren
op_logical_or
(paren
op_star
id|p
op_eq
l_char|&squot; &squot;
)paren
)paren
op_decrement
id|p
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|p
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
op_increment
id|p
suffix:semicolon
op_star
id|p
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
op_increment
id|p
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|p
op_minus
id|page
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|count
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
id|len
op_assign
id|count
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_int
id|proc_mf_dump_vmlinux
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|sizeToGet
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|mf_getVmlinuxChunk
c_func
(paren
id|page
comma
op_amp
id|sizeToGet
comma
id|off
comma
(paren
id|u64
)paren
id|data
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|sizeToGet
op_ne
l_int|0
)paren
(brace
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
id|sizeToGet
suffix:semicolon
)brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|proc_mf_dump_side
r_static
r_int
id|proc_mf_dump_side
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
suffix:semicolon
r_char
id|mf_current_side
op_assign
id|mf_getSide
c_func
(paren
)paren
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%c&bslash;n&quot;
comma
id|mf_current_side
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
(paren
id|off
op_plus
id|count
)paren
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|proc_mf_change_side
r_static
r_int
id|proc_mf_change_side
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_char
id|stkbuf
(braket
l_int|10
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
(paren
r_sizeof
(paren
id|stkbuf
)paren
op_minus
l_int|1
)paren
)paren
id|count
op_assign
r_sizeof
(paren
id|stkbuf
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|stkbuf
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|stkbuf
(braket
id|count
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|stkbuf
op_ne
l_char|&squot;A&squot;
)paren
op_logical_and
(paren
op_star
id|stkbuf
op_ne
l_char|&squot;B&squot;
)paren
op_logical_and
(paren
op_star
id|stkbuf
op_ne
l_char|&squot;C&squot;
)paren
op_logical_and
(paren
op_star
id|stkbuf
op_ne
l_char|&squot;D&squot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mf_proc.c: proc_mf_change_side: invalid side&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|mf_setSide
c_func
(paren
op_star
id|stkbuf
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|proc_mf_dump_src
r_static
r_int
id|proc_mf_dump_src
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
suffix:semicolon
id|mf_getSrcHistory
c_func
(paren
id|page
comma
id|count
)paren
suffix:semicolon
id|len
op_assign
id|count
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|count
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
id|len
op_assign
id|count
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|proc_mf_change_src
r_static
r_int
id|proc_mf_change_src
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_char
id|stkbuf
(braket
l_int|10
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
OL
l_int|4
)paren
op_logical_and
(paren
id|count
op_ne
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mf_proc: invalid src&bslash;n&quot;
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
id|count
OG
(paren
r_sizeof
(paren
id|stkbuf
)paren
op_minus
l_int|1
)paren
)paren
id|count
op_assign
r_sizeof
(paren
id|stkbuf
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|stkbuf
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
op_eq
l_int|1
)paren
op_logical_and
(paren
op_star
id|stkbuf
op_eq
l_char|&squot;&bslash;0&squot;
)paren
)paren
id|mf_clearSrc
c_func
(paren
)paren
suffix:semicolon
r_else
id|mf_displaySrc
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|stkbuf
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|proc_mf_change_cmdline
r_static
r_int
id|proc_mf_change_cmdline
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|mf_setCmdLine
c_func
(paren
id|buffer
comma
id|count
comma
(paren
id|u64
)paren
id|data
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|proc_mf_change_vmlinux
r_static
r_int
id|proc_mf_change_vmlinux
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|mf_setVmlinuxChunk
c_func
(paren
id|buffer
comma
id|count
comma
id|file-&gt;f_pos
comma
(paren
id|u64
)paren
id|data
)paren
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|mf_proc_init
r_void
id|mf_proc_init
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|iSeries_proc
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|mf
suffix:semicolon
r_char
id|name
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|mf_proc_root
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;mf&quot;
comma
id|iSeries_proc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mf_proc_root
)paren
r_return
suffix:semicolon
id|name
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|name
(braket
l_int|0
)braket
op_assign
l_char|&squot;A&squot;
op_plus
id|i
suffix:semicolon
id|mf
op_assign
id|proc_mkdir
c_func
(paren
id|name
comma
id|mf_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mf
)paren
r_return
suffix:semicolon
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;cmdline&quot;
comma
id|S_IFREG
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|mf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
suffix:semicolon
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;data
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|i
suffix:semicolon
id|ent-&gt;read_proc
op_assign
id|proc_mf_dump_cmdline
suffix:semicolon
id|ent-&gt;write_proc
op_assign
id|proc_mf_change_cmdline
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|3
)paren
multiline_comment|/* no vmlinux entry for &squot;D&squot; */
r_continue
suffix:semicolon
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;vmlinux&quot;
comma
id|S_IFREG
op_or
id|S_IWUSR
comma
id|mf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
suffix:semicolon
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;data
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|i
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|i
op_eq
l_int|3
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * if we had a &squot;D&squot; vmlinux entry, it would only&n;&t;&t;&t; * be readable.&n;&t;&t;&t; */
id|ent-&gt;read_proc
op_assign
id|proc_mf_dump_vmlinux
suffix:semicolon
id|ent-&gt;write_proc
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
id|ent-&gt;write_proc
op_assign
id|proc_mf_change_vmlinux
suffix:semicolon
id|ent-&gt;read_proc
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;side&quot;
comma
id|S_IFREG
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|mf_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
suffix:semicolon
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;data
op_assign
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
id|ent-&gt;read_proc
op_assign
id|proc_mf_dump_side
suffix:semicolon
id|ent-&gt;write_proc
op_assign
id|proc_mf_change_side
suffix:semicolon
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;src&quot;
comma
id|S_IFREG
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|mf_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
suffix:semicolon
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;data
op_assign
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
id|ent-&gt;read_proc
op_assign
id|proc_mf_dump_src
suffix:semicolon
id|ent-&gt;write_proc
op_assign
id|proc_mf_change_src
suffix:semicolon
)brace
eof
