multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;xfs_types.h&gt;
macro_line|#include &lt;xfs_arch.h&gt;
macro_line|#include &quot;time.h&quot;
macro_line|#include &quot;uuid.h&quot;
macro_line|#include &quot;kmem.h&quot;
macro_line|#include &quot;debug.h&quot;
macro_line|#include &quot;mutex.h&quot;
DECL|variable|uuid_monitor
r_static
id|mutex_t
id|uuid_monitor
suffix:semicolon
DECL|variable|uuid_table_size
r_static
r_int
id|uuid_table_size
suffix:semicolon
DECL|variable|uuid_table
r_static
id|uuid_t
op_star
id|uuid_table
suffix:semicolon
r_void
DECL|function|uuid_init
id|uuid_init
c_func
(paren
r_void
)paren
(brace
id|mutex_init
c_func
(paren
op_amp
id|uuid_monitor
comma
id|MUTEX_DEFAULT
comma
l_string|&quot;uuid_monitor&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * uuid_getnodeuniq - obtain the node unique fields of a UUID.&n; *&n; * This is not in any way a standard or condoned UUID function;&n; * it just something that&squot;s needed for user-level file handles.&n; */
r_void
DECL|function|uuid_getnodeuniq
id|uuid_getnodeuniq
c_func
(paren
id|uuid_t
op_star
id|uuid
comma
r_int
id|fsid
(braket
l_int|2
)braket
)paren
(brace
r_char
op_star
id|uu
op_assign
(paren
r_char
op_star
)paren
id|uuid
suffix:semicolon
multiline_comment|/* on IRIX, this function assumes big-endian fields within&n;&t; * the uuid, so we use INT_GET to get the same result on&n;&t; * little-endian systems&n;&t; */
id|fsid
(braket
l_int|0
)braket
op_assign
(paren
id|INT_GET
c_func
(paren
op_star
(paren
id|u_int16_t
op_star
)paren
(paren
id|uu
op_plus
l_int|8
)paren
comma
id|ARCH_CONVERT
)paren
op_lshift
l_int|16
)paren
op_plus
id|INT_GET
c_func
(paren
op_star
(paren
id|u_int16_t
op_star
)paren
(paren
id|uu
op_plus
l_int|4
)paren
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|fsid
(braket
l_int|1
)braket
op_assign
id|INT_GET
c_func
(paren
op_star
(paren
id|u_int32_t
op_star
)paren
(paren
id|uu
)paren
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
)brace
r_void
DECL|function|uuid_create_nil
id|uuid_create_nil
c_func
(paren
id|uuid_t
op_star
id|uuid
)paren
(brace
id|memset
c_func
(paren
id|uuid
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|uuid
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|uuid_is_nil
id|uuid_is_nil
c_func
(paren
id|uuid_t
op_star
id|uuid
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|cp
op_assign
(paren
r_char
op_star
)paren
id|uuid
suffix:semicolon
r_if
c_cond
(paren
id|uuid
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* implied check of version number here... */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
op_star
id|uuid
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_star
id|cp
op_increment
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* not nil */
r_return
l_int|1
suffix:semicolon
multiline_comment|/* is nil */
)brace
r_int
DECL|function|uuid_equal
id|uuid_equal
c_func
(paren
id|uuid_t
op_star
id|uuid1
comma
id|uuid_t
op_star
id|uuid2
)paren
(brace
r_return
id|memcmp
c_func
(paren
id|uuid1
comma
id|uuid2
comma
r_sizeof
(paren
id|uuid_t
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Given a 128-bit uuid, return a 64-bit value by adding the top and bottom&n; * 64-bit words.  NOTE: This function can not be changed EVER.  Although&n; * brain-dead, some applications depend on this 64-bit value remaining&n; * persistent.  Specifically, DMI vendors store the value as a persistent&n; * filehandle.&n; */
id|__uint64_t
DECL|function|uuid_hash64
id|uuid_hash64
c_func
(paren
id|uuid_t
op_star
id|uuid
)paren
(brace
id|__uint64_t
op_star
id|sp
op_assign
(paren
id|__uint64_t
op_star
)paren
id|uuid
suffix:semicolon
r_return
id|sp
(braket
l_int|0
)braket
op_plus
id|sp
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_int
DECL|function|uuid_table_insert
id|uuid_table_insert
c_func
(paren
id|uuid_t
op_star
id|uuid
)paren
(brace
r_int
id|i
comma
id|hole
suffix:semicolon
id|mutex_lock
c_func
(paren
op_amp
id|uuid_monitor
comma
id|PVFS
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|hole
op_assign
op_minus
l_int|1
suffix:semicolon
id|i
OL
id|uuid_table_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|uuid_is_nil
c_func
(paren
op_amp
id|uuid_table
(braket
id|i
)braket
)paren
)paren
(brace
id|hole
op_assign
id|i
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|uuid_equal
c_func
(paren
id|uuid
comma
op_amp
id|uuid_table
(braket
id|i
)braket
)paren
)paren
(brace
id|mutex_unlock
c_func
(paren
op_amp
id|uuid_monitor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|hole
OL
l_int|0
)paren
(brace
id|uuid_table
op_assign
id|kmem_realloc
c_func
(paren
id|uuid_table
comma
(paren
id|uuid_table_size
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
op_star
id|uuid_table
)paren
comma
id|uuid_table_size
op_star
r_sizeof
(paren
op_star
id|uuid_table
)paren
comma
id|KM_SLEEP
)paren
suffix:semicolon
id|hole
op_assign
id|uuid_table_size
op_increment
suffix:semicolon
)brace
id|uuid_table
(braket
id|hole
)braket
op_assign
op_star
id|uuid
suffix:semicolon
id|mutex_unlock
c_func
(paren
op_amp
id|uuid_monitor
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_void
DECL|function|uuid_table_remove
id|uuid_table_remove
c_func
(paren
id|uuid_t
op_star
id|uuid
)paren
(brace
r_int
id|i
suffix:semicolon
id|mutex_lock
c_func
(paren
op_amp
id|uuid_monitor
comma
id|PVFS
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
id|uuid_table_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|uuid_is_nil
c_func
(paren
op_amp
id|uuid_table
(braket
id|i
)braket
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uuid_equal
c_func
(paren
id|uuid
comma
op_amp
id|uuid_table
(braket
id|i
)braket
)paren
)paren
r_continue
suffix:semicolon
id|uuid_create_nil
c_func
(paren
op_amp
id|uuid_table
(braket
id|i
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|i
OL
id|uuid_table_size
)paren
suffix:semicolon
id|mutex_unlock
c_func
(paren
op_amp
id|uuid_monitor
)paren
suffix:semicolon
)brace
eof
