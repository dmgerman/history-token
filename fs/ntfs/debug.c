multiline_comment|/*&n; * debug.c - NTFS kernel debug support. Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001-2004 Anton Altaparmakov&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;debug.h&quot;
multiline_comment|/*&n; * A static buffer to hold the error string being displayed and a spinlock&n; * to protect concurrent accesses to it.&n; */
DECL|variable|err_buf
r_static
r_char
id|err_buf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|variable|err_buf_lock
r_static
id|spinlock_t
id|err_buf_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/**&n; * __ntfs_warning - output a warning to the syslog&n; * @function:&t;name of function outputting the warning&n; * @sb:&t;&t;super block of mounted ntfs filesystem&n; * @fmt:&t;warning string containing format specifications&n; * @...:&t;a variable number of arguments specified in @fmt&n; *&n; * Outputs a warning to the syslog for the mounted ntfs filesystem described&n; * by @sb.&n; *&n; * @fmt and the corresponding @... is printf style format string containing&n; * the warning string and the corresponding format arguments, respectively.&n; *&n; * @function is the name of the function from which __ntfs_warning is being&n; * called.&n; *&n; * Note, you should be using debug.h::ntfs_warning(@sb, @fmt, @...) instead&n; * as this provides the @function parameter automatically.&n; */
DECL|function|__ntfs_warning
r_void
id|__ntfs_warning
c_func
(paren
r_const
r_char
op_star
id|function
comma
r_const
r_struct
id|super_block
op_star
id|sb
comma
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
id|args
suffix:semicolon
r_int
id|flen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|function
)paren
id|flen
op_assign
id|strlen
c_func
(paren
id|function
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|err_buf_lock
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsnprintf
c_func
(paren
id|err_buf
comma
r_sizeof
(paren
id|err_buf
)paren
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NTFS-fs warning (device %s): %s(): %s&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|flen
ques
c_cond
id|function
suffix:colon
l_string|&quot;&quot;
comma
id|err_buf
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NTFS-fs warning: %s(): %s&bslash;n&quot;
comma
id|flen
ques
c_cond
id|function
suffix:colon
l_string|&quot;&quot;
comma
id|err_buf
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|err_buf_lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * __ntfs_error - output an error to the syslog&n; * @function:&t;name of function outputting the error&n; * @sb:&t;&t;super block of mounted ntfs filesystem&n; * @fmt:&t;error string containing format specifications&n; * @...:&t;a variable number of arguments specified in @fmt&n; *&n; * Outputs an error to the syslog for the mounted ntfs filesystem described&n; * by @sb.&n; *&n; * @fmt and the corresponding @... is printf style format string containing&n; * the error string and the corresponding format arguments, respectively.&n; *&n; * @function is the name of the function from which __ntfs_error is being&n; * called.&n; *&n; * Note, you should be using debug.h::ntfs_error(@sb, @fmt, @...) instead&n; * as this provides the @function parameter automatically.&n; */
DECL|function|__ntfs_error
r_void
id|__ntfs_error
c_func
(paren
r_const
r_char
op_star
id|function
comma
r_const
r_struct
id|super_block
op_star
id|sb
comma
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
id|args
suffix:semicolon
r_int
id|flen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|function
)paren
id|flen
op_assign
id|strlen
c_func
(paren
id|function
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|err_buf_lock
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsnprintf
c_func
(paren
id|err_buf
comma
r_sizeof
(paren
id|err_buf
)paren
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NTFS-fs error (device %s): %s(): %s&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|flen
ques
c_cond
id|function
suffix:colon
l_string|&quot;&quot;
comma
id|err_buf
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NTFS-fs error: %s(): %s&bslash;n&quot;
comma
id|flen
ques
c_cond
id|function
suffix:colon
l_string|&quot;&quot;
comma
id|err_buf
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|err_buf_lock
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
multiline_comment|/* If 1, output debug messages, and if 0, don&squot;t. */
DECL|variable|debug_msgs
r_int
id|debug_msgs
op_assign
l_int|0
suffix:semicolon
DECL|function|__ntfs_debug
r_void
id|__ntfs_debug
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_const
r_char
op_star
id|function
comma
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
id|args
suffix:semicolon
r_int
id|flen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|debug_msgs
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|function
)paren
id|flen
op_assign
id|strlen
c_func
(paren
id|function
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|err_buf_lock
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsnprintf
c_func
(paren
id|err_buf
comma
r_sizeof
(paren
id|err_buf
)paren
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;NTFS-fs DEBUG (%s, %d): %s: %s&bslash;n&quot;
comma
id|file
comma
id|line
comma
id|flen
ques
c_cond
id|function
suffix:colon
l_string|&quot;&quot;
comma
id|err_buf
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|err_buf_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Dump a run list. Caller has to provide synchronisation for @rl. */
DECL|function|ntfs_debug_dump_runlist
r_void
id|ntfs_debug_dump_runlist
c_func
(paren
r_const
id|run_list_element
op_star
id|rl
)paren
(brace
r_int
id|i
suffix:semicolon
r_const
r_char
op_star
id|lcn_str
(braket
l_int|5
)braket
op_assign
(brace
l_string|&quot;LCN_HOLE         &quot;
comma
l_string|&quot;LCN_RL_NOT_MAPPED&quot;
comma
l_string|&quot;LCN_ENOENT       &quot;
comma
l_string|&quot;LCN_EINVAL       &quot;
comma
l_string|&quot;LCN_unknown      &quot;
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|debug_msgs
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;NTFS-fs DEBUG: Dumping run list (values &quot;
l_string|&quot;in hex):&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rl
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Run list not present.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;VCN              LCN               Run length&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|i
op_increment
)paren
(brace
id|LCN
id|lcn
op_assign
(paren
id|rl
op_plus
id|i
)paren
op_member_access_from_pointer
id|lcn
suffix:semicolon
r_if
c_cond
(paren
id|lcn
OL
(paren
id|LCN
)paren
l_int|0
)paren
(brace
r_int
id|index
op_assign
op_minus
id|lcn
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|index
OG
op_minus
id|LCN_EINVAL
op_minus
l_int|1
)paren
id|index
op_assign
l_int|4
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%-16Lx %s %-16Lx%s&bslash;n&quot;
comma
(paren
id|rl
op_plus
id|i
)paren
op_member_access_from_pointer
id|vcn
comma
id|lcn_str
(braket
id|index
)braket
comma
(paren
id|rl
op_plus
id|i
)paren
op_member_access_from_pointer
id|length
comma
(paren
id|rl
op_plus
id|i
)paren
op_member_access_from_pointer
id|length
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; (run list end)&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%-16Lx %-16Lx  %-16Lx%s&bslash;n&quot;
comma
(paren
id|rl
op_plus
id|i
)paren
op_member_access_from_pointer
id|vcn
comma
(paren
id|rl
op_plus
id|i
)paren
op_member_access_from_pointer
id|lcn
comma
(paren
id|rl
op_plus
id|i
)paren
op_member_access_from_pointer
id|length
comma
(paren
id|rl
op_plus
id|i
)paren
op_member_access_from_pointer
id|length
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; (run list end)&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rl
op_plus
id|i
)paren
op_member_access_from_pointer
id|length
)paren
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
