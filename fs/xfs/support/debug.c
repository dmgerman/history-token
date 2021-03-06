multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;debug.h&quot;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|variable|doass
r_int
id|doass
op_assign
l_int|1
suffix:semicolon
DECL|variable|message
r_static
r_char
id|message
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* keep it off the stack */
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|xfs_err_lock
)paren
suffix:semicolon
multiline_comment|/* Translate from CE_FOO to KERN_FOO, err_level(CE_FOO) == KERN_FOO */
DECL|macro|XFS_MAX_ERR_LEVEL
mdefine_line|#define XFS_MAX_ERR_LEVEL&t;7
DECL|macro|XFS_ERR_MASK
mdefine_line|#define XFS_ERR_MASK&t;&t;((1 &lt;&lt; 3) - 1)
DECL|variable|err_level
r_static
r_char
op_star
id|err_level
(braket
id|XFS_MAX_ERR_LEVEL
op_plus
l_int|1
)braket
op_assign
(brace
id|KERN_EMERG
comma
id|KERN_ALERT
comma
id|KERN_CRIT
comma
id|KERN_ERR
comma
id|KERN_WARNING
comma
id|KERN_NOTICE
comma
id|KERN_INFO
comma
id|KERN_DEBUG
)brace
suffix:semicolon
r_void
DECL|function|assfail
id|assfail
c_func
(paren
r_char
op_star
id|a
comma
r_char
op_star
id|f
comma
r_int
id|l
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XFS assertion failed: %s, file: %s, line: %d&bslash;n&quot;
comma
id|a
comma
id|f
comma
id|l
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if ((defined(DEBUG) || defined(INDUCE_IO_ERRROR)) &amp;&amp; !defined(NO_WANT_RANDOM))
r_int
r_int
DECL|function|random
id|random
c_func
(paren
r_void
)paren
(brace
r_static
r_int
r_int
id|RandomValue
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* cycles pseudo-randomly through all values between 1 and 2^31 - 2 */
r_register
r_int
id|rv
op_assign
id|RandomValue
suffix:semicolon
r_register
r_int
id|lo
suffix:semicolon
r_register
r_int
id|hi
suffix:semicolon
id|hi
op_assign
id|rv
op_div
l_int|127773
suffix:semicolon
id|lo
op_assign
id|rv
op_mod
l_int|127773
suffix:semicolon
id|rv
op_assign
l_int|16807
op_star
id|lo
op_minus
l_int|2836
op_star
id|hi
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_le
l_int|0
)paren
(brace
id|rv
op_add_assign
l_int|2147483647
suffix:semicolon
)brace
r_return
id|RandomValue
op_assign
id|rv
suffix:semicolon
)brace
r_int
DECL|function|get_thread_id
id|get_thread_id
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;pid
suffix:semicolon
)brace
macro_line|#endif /* DEBUG || INDUCE_IO_ERRROR || !NO_WANT_RANDOM */
r_void
DECL|function|cmn_err
id|cmn_err
c_func
(paren
r_register
r_int
id|level
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_char
op_star
id|fp
op_assign
id|fmt
suffix:semicolon
r_int
id|len
suffix:semicolon
id|ulong
id|flags
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
id|level
op_and_assign
id|XFS_ERR_MASK
suffix:semicolon
r_if
c_cond
(paren
id|level
OG
id|XFS_MAX_ERR_LEVEL
)paren
id|level
op_assign
id|XFS_MAX_ERR_LEVEL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|xfs_err_lock
comma
id|flags
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;!&squot;
)paren
id|fp
op_increment
suffix:semicolon
id|len
op_assign
id|vsprintf
c_func
(paren
id|message
comma
id|fp
comma
id|ap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|message
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|strcat
c_func
(paren
id|message
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s%s&quot;
comma
id|err_level
(braket
id|level
)braket
comma
id|message
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|xfs_err_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|CE_PANIC
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|icmn_err
id|icmn_err
c_func
(paren
r_register
r_int
id|level
comma
r_char
op_star
id|fmt
comma
id|va_list
id|ap
)paren
(brace
id|ulong
id|flags
suffix:semicolon
r_int
id|len
suffix:semicolon
id|level
op_and_assign
id|XFS_ERR_MASK
suffix:semicolon
r_if
c_cond
(paren
id|level
OG
id|XFS_MAX_ERR_LEVEL
)paren
(brace
id|level
op_assign
id|XFS_MAX_ERR_LEVEL
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|xfs_err_lock
comma
id|flags
)paren
suffix:semicolon
id|len
op_assign
id|vsprintf
c_func
(paren
id|message
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|message
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|strcat
c_func
(paren
id|message
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|xfs_err_lock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s%s&quot;
comma
id|err_level
(braket
id|level
)braket
comma
id|message
)paren
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|CE_PANIC
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
eof
