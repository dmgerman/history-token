multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#ifdef __sparc__
macro_line|#include &lt;asm/idprom.h&gt;
macro_line|#else
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#endif
macro_line|#include &lt;xfs_types.h&gt;
macro_line|#include &lt;xfs_arch.h&gt;
macro_line|#include &quot;time.h&quot;
macro_line|#include &quot;move.h&quot;
macro_line|#include &quot;uuid.h&quot;
macro_line|#ifndef CONFIG_NET
DECL|macro|dev_get_by_name
mdefine_line|#define dev_get_by_name(x)&t;(NULL)
DECL|macro|dev_put
mdefine_line|#define dev_put(x)&t;&t;do { } while (0)
macro_line|#endif
multiline_comment|/* NODE_SIZE is the number of bytes used for the node identifier portion. */
DECL|macro|NODE_SIZE
mdefine_line|#define NODE_SIZE&t;6
multiline_comment|/*&n; * Total size must be 128 bits.&t; N.B. definition of uuid_t in uuid.h!&n; */
r_typedef
r_struct
(brace
DECL|member|uu_timelow
id|u_int32_t
id|uu_timelow
suffix:semicolon
multiline_comment|/* time &quot;low&quot; */
DECL|member|uu_timemid
id|u_int16_t
id|uu_timemid
suffix:semicolon
multiline_comment|/* time &quot;mid&quot; */
DECL|member|uu_timehi
id|u_int16_t
id|uu_timehi
suffix:semicolon
multiline_comment|/* time &quot;hi&quot; and version */
DECL|member|uu_clockseq
id|u_int16_t
id|uu_clockseq
suffix:semicolon
multiline_comment|/* &quot;reserved&quot; and clock sequence */
DECL|member|uu_node
id|u_int16_t
id|uu_node
(braket
id|NODE_SIZE
op_div
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ethernet hardware address */
DECL|typedef|uu_t
)brace
id|uu_t
suffix:semicolon
multiline_comment|/*&n; * The Time Base Correction is the amount to add on to a UNIX-based&n; * time value (i.e. seconds since 1 Jan. 1970) to convert it to the&n; * time base for UUIDs (15 Oct. 1582).&n; */
DECL|macro|UUID_TBC
mdefine_line|#define UUID_TBC&t;0x01B21DD2138140LL
DECL|variable|uuid_eaddr
r_static
r_int
id|uuid_eaddr
(braket
id|NODE_SIZE
op_div
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ethernet address */
DECL|variable|uuid_time
r_static
id|__int64_t
id|uuid_time
suffix:semicolon
multiline_comment|/* last time basis used */
DECL|variable|uuid_clockseq
r_static
id|u_int16_t
id|uuid_clockseq
suffix:semicolon
multiline_comment|/* boot-time randomizer */
DECL|variable|uuid_lock
id|DECLARE_MUTEX
c_func
(paren
id|uuid_lock
)paren
suffix:semicolon
multiline_comment|/*&n; * uuid_init - called from out of init_tbl[]&n; */
r_void
DECL|function|uuid_init
id|uuid_init
c_func
(paren
r_void
)paren
(brace
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
id|B_TRUE
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
id|B_FALSE
suffix:semicolon
multiline_comment|/* not nil */
r_return
id|B_TRUE
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
id|B_FALSE
suffix:colon
id|B_TRUE
suffix:semicolon
)brace
multiline_comment|/*&n; * Given a 128-bit uuid, return a 64-bit value by adding the top and bottom&n; * 64-bit words.  NOTE: This function can not be changed EVER.&t;Although&n; * brain-dead, some applications depend on this 64-bit value remaining&n; * persistent.&t;Specifically, DMI vendors store the value as a persistent&n; * filehandle.&n; */
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
multiline_comment|/* uuid_hash64 */
r_static
r_void
DECL|function|get_eaddr
id|get_eaddr
c_func
(paren
r_char
op_star
id|junk
)paren
(brace
macro_line|#ifdef __sparc__
id|memcpy
c_func
(paren
id|uuid_eaddr
comma
id|idprom-&gt;id_ethaddr
comma
l_int|6
)paren
suffix:semicolon
macro_line|#else
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|dev_get_by_name
c_func
(paren
l_string|&quot;eth0&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|dev-&gt;addr_len
)paren
(brace
id|get_random_bytes
c_func
(paren
id|uuid_eaddr
comma
r_sizeof
(paren
id|uuid_eaddr
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
id|uuid_eaddr
comma
id|dev-&gt;dev_addr
comma
id|dev-&gt;addr_len
OL
r_sizeof
(paren
id|uuid_eaddr
)paren
ques
c_cond
id|dev-&gt;addr_len
suffix:colon
r_sizeof
(paren
id|uuid_eaddr
)paren
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; * uuid_create - kernel version, does the actual work&n; */
r_void
DECL|function|uuid_create
id|uuid_create
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
id|uu_t
op_star
id|uu
op_assign
(paren
id|uu_t
op_star
)paren
id|uuid
suffix:semicolon
r_static
r_int
id|uuid_have_eaddr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ethernet addr inited? */
r_static
r_int
id|uuid_is_init
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* time/clockseq inited? */
id|down
c_func
(paren
op_amp
id|uuid_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uuid_is_init
)paren
(brace
id|timespec_t
id|ts
suffix:semicolon
id|nanotime
c_func
(paren
op_amp
id|ts
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The clock sequence must be initialized randomly.&n;&t;&t; */
id|uuid_clockseq
op_assign
(paren
(paren
r_int
r_int
)paren
id|jiffies
op_amp
l_int|0xfff
)paren
op_or
l_int|0x8000
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Initialize the uuid time, it&squot;s in 100 nanosecond&n;&t;&t; * units since a time base in 1582.&n;&t;&t; */
id|uuid_time
op_assign
id|ts.tv_sec
op_star
l_int|10000000LL
op_plus
id|ts.tv_nsec
op_div
l_int|100LL
op_plus
id|UUID_TBC
suffix:semicolon
id|uuid_is_init
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|uuid_have_eaddr
)paren
(brace
id|uuid_have_eaddr
op_assign
l_int|1
suffix:semicolon
id|get_eaddr
c_func
(paren
(paren
r_char
op_star
)paren
id|uuid_eaddr
)paren
suffix:semicolon
)brace
id|uuid_time
op_increment
suffix:semicolon
id|uu-&gt;uu_timelow
op_assign
(paren
id|u_int32_t
)paren
(paren
id|uuid_time
op_amp
l_int|0x00000000ffffffffLL
)paren
suffix:semicolon
id|uu-&gt;uu_timemid
op_assign
(paren
id|u_int16_t
)paren
(paren
(paren
id|uuid_time
op_rshift
l_int|32
)paren
op_amp
l_int|0x0000ffff
)paren
suffix:semicolon
id|uu-&gt;uu_timehi
op_assign
(paren
id|u_int16_t
)paren
(paren
(paren
id|uuid_time
op_rshift
l_int|48
)paren
op_amp
l_int|0x00000fff
)paren
op_or
l_int|0x1000
suffix:semicolon
id|up
c_func
(paren
op_amp
id|uuid_lock
)paren
suffix:semicolon
id|uu-&gt;uu_clockseq
op_assign
id|uuid_clockseq
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
(paren
id|NODE_SIZE
op_div
l_int|2
)paren
suffix:semicolon
id|i
op_increment
)paren
id|uu-&gt;uu_node
(braket
id|i
)braket
op_assign
id|uuid_eaddr
(braket
id|i
)braket
suffix:semicolon
)brace
r_int
DECL|function|uuid_compare
id|uuid_compare
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
r_int
id|i
suffix:semicolon
r_char
op_star
id|cp1
op_assign
(paren
r_char
op_star
)paren
id|uuid1
suffix:semicolon
r_char
op_star
id|cp2
op_assign
(paren
r_char
op_star
)paren
id|uuid2
suffix:semicolon
r_if
c_cond
(paren
id|uuid1
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|uuid2
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* equal because both are nil */
)brace
r_else
(brace
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* uuid1 nil, so precedes uuid2 */
)brace
)brace
r_else
r_if
c_cond
(paren
id|uuid2
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
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
(paren
id|uuid_t
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp1
OL
op_star
id|cp2
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp1
op_increment
OG
op_star
id|cp2
op_increment
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* they&squot;re equal */
)brace
eof
