multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_LINUX__
DECL|macro|__XFS_LINUX__
mdefine_line|#define __XFS_LINUX__
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/xfs_behavior.h&gt;
macro_line|#include &lt;linux/xfs_vfs.h&gt;
macro_line|#include &lt;linux/xfs_cred.h&gt;
macro_line|#include &lt;linux/xfs_vnode.h&gt;
macro_line|#include &lt;linux/xfs_stats.h&gt;
macro_line|#include &lt;linux/xfs_sysctl.h&gt;
macro_line|#include &lt;linux/xfs_iops.h&gt;
macro_line|#include &lt;linux/xfs_super.h&gt;
macro_line|#include &lt;linux/xfs_globals.h&gt;
macro_line|#include &lt;linux/xfs_fs_subr.h&gt;
macro_line|#include &lt;pagebuf/page_buf.h&gt;
macro_line|#ifndef STATIC
DECL|macro|STATIC
mdefine_line|#define STATIC static
macro_line|#endif
DECL|struct|xfs_dirent
r_typedef
r_struct
id|xfs_dirent
(brace
multiline_comment|/* data from readdir() */
DECL|member|d_ino
id|xfs_ino_t
id|d_ino
suffix:semicolon
multiline_comment|/* inode number of entry */
DECL|member|d_off
id|xfs_off_t
id|d_off
suffix:semicolon
multiline_comment|/* offset of disk directory entry */
DECL|member|d_reclen
r_int
r_int
id|d_reclen
suffix:semicolon
multiline_comment|/* length of this record */
DECL|member|d_name
r_char
id|d_name
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* name of file */
DECL|typedef|xfs_dirent_t
)brace
id|xfs_dirent_t
suffix:semicolon
DECL|macro|DIRENTBASESIZE
mdefine_line|#define DIRENTBASESIZE&t;&t;(((xfs_dirent_t *)0)-&gt;d_name - (char *)0)
DECL|macro|DIRENTSIZE
mdefine_line|#define DIRENTSIZE(namelen)&t;&bslash;&n;&t;((DIRENTBASESIZE + (namelen) + &bslash;&n;&t;&t;sizeof(xfs_off_t)) &amp; ~(sizeof(xfs_off_t) - 1))
DECL|macro|NBPP
mdefine_line|#define NBPP&t;&t;PAGE_SIZE
DECL|macro|DPPSHFT
mdefine_line|#define DPPSHFT&t;&t;(PAGE_SHIFT - 9)
DECL|macro|NDPP
mdefine_line|#define NDPP&t;&t;(1 &lt;&lt; (PAGE_SHIFT - 9))
DECL|macro|dtop
mdefine_line|#define dtop(DD)&t;(((DD) + NDPP - 1) &gt;&gt; DPPSHFT)
DECL|macro|dtopt
mdefine_line|#define dtopt(DD)&t;((DD) &gt;&gt; DPPSHFT)
DECL|macro|dpoff
mdefine_line|#define dpoff(DD)&t;((DD) &amp; (NDPP-1))
DECL|macro|NBBY
mdefine_line|#define NBBY&t;&t;8&t;&t;/* number of bits per byte */
DECL|macro|NBPC
mdefine_line|#define NBPC&t;&t;PAGE_SIZE&t;/* Number of bytes per click */
DECL|macro|BPCSHIFT
mdefine_line|#define BPCSHIFT&t;PAGE_SHIFT&t;/* LOG2(NBPC) if exact */
multiline_comment|/*&n; * Size of block device i/o is parameterized here.&n; * Currently the system supports page-sized i/o.&n; */
DECL|macro|BLKDEV_IOSHIFT
mdefine_line|#define BLKDEV_IOSHIFT&t;&t;BPCSHIFT
DECL|macro|BLKDEV_IOSIZE
mdefine_line|#define BLKDEV_IOSIZE&t;&t;(1&lt;&lt;BLKDEV_IOSHIFT)
multiline_comment|/* number of BB&squot;s per block device block */
DECL|macro|BLKDEV_BB
mdefine_line|#define BLKDEV_BB&t;&t;BTOBB(BLKDEV_IOSIZE)
multiline_comment|/* bytes to clicks */
DECL|macro|btoc
mdefine_line|#define btoc(x)&t;&t;(((__psunsigned_t)(x)+(NBPC-1))&gt;&gt;BPCSHIFT)
DECL|macro|btoct
mdefine_line|#define btoct(x)&t;((__psunsigned_t)(x)&gt;&gt;BPCSHIFT)
DECL|macro|btoc64
mdefine_line|#define btoc64(x)&t;(((__uint64_t)(x)+(NBPC-1))&gt;&gt;BPCSHIFT)
DECL|macro|btoct64
mdefine_line|#define btoct64(x)&t;((__uint64_t)(x)&gt;&gt;BPCSHIFT)
DECL|macro|io_btoc
mdefine_line|#define io_btoc(x)&t;(((__psunsigned_t)(x)+(IO_NBPC-1))&gt;&gt;IO_BPCSHIFT)
DECL|macro|io_btoct
mdefine_line|#define io_btoct(x)&t;((__psunsigned_t)(x)&gt;&gt;IO_BPCSHIFT)
multiline_comment|/* off_t bytes to clicks */
DECL|macro|offtoc
mdefine_line|#define offtoc(x)&t;(((__uint64_t)(x)+(NBPC-1))&gt;&gt;BPCSHIFT)
DECL|macro|offtoct
mdefine_line|#define offtoct(x)&t;((xfs_off_t)(x)&gt;&gt;BPCSHIFT)
multiline_comment|/* clicks to off_t bytes */
DECL|macro|ctooff
mdefine_line|#define ctooff(x)&t;((xfs_off_t)(x)&lt;&lt;BPCSHIFT)
multiline_comment|/* clicks to bytes */
DECL|macro|ctob
mdefine_line|#define ctob(x)&t;&t;((__psunsigned_t)(x)&lt;&lt;BPCSHIFT)
DECL|macro|btoct
mdefine_line|#define btoct(x)&t;((__psunsigned_t)(x)&gt;&gt;BPCSHIFT)
DECL|macro|ctob64
mdefine_line|#define ctob64(x)&t;((__uint64_t)(x)&lt;&lt;BPCSHIFT)
DECL|macro|io_ctob
mdefine_line|#define io_ctob(x)&t;((__psunsigned_t)(x)&lt;&lt;IO_BPCSHIFT)
multiline_comment|/* bytes to clicks */
DECL|macro|btoc
mdefine_line|#define btoc(x)&t;&t;(((__psunsigned_t)(x)+(NBPC-1))&gt;&gt;BPCSHIFT)
macro_line|#ifndef CELL_CAPABLE
DECL|macro|FSC_NOTIFY_NAME_CHANGED
mdefine_line|#define FSC_NOTIFY_NAME_CHANGED(vp)
macro_line|#endif
macro_line|#ifndef ENOATTR
DECL|macro|ENOATTR
mdefine_line|#define ENOATTR&t;&t;ENODATA&t;&t;/* Attribute not found */
macro_line|#endif
multiline_comment|/* Note: EWRONGFS never visible outside the kernel */
DECL|macro|EWRONGFS
mdefine_line|#define EWRONGFS&t;EINVAL&t;&t;/* Mount with wrong filesystem type */
multiline_comment|/*&n; * XXX EFSCORRUPTED needs a real value in errno.h. asm-i386/errno.h won&squot;t&n; *     return codes out of its known range in errno.&n; * XXX Also note: needs to be &lt; 1000 and fairly unique on Linux (mustn&squot;t&n; *     conflict with any code we use already or any code a driver may use)&n; * XXX Some options (currently we do #2):&n; *&t;1/ New error code [&quot;Filesystem is corrupted&quot;, _after_ glibc updated]&n; *&t;2/ 990 [&quot;Unknown error 990&quot;]&n; *&t;3/ EUCLEAN [&quot;Structure needs cleaning&quot;]&n; *&t;4/ Convert EFSCORRUPTED to EIO [just prior to return into userspace]&n; */
DECL|macro|EFSCORRUPTED
mdefine_line|#define EFSCORRUPTED&t;990&t;&t;/* Filesystem is corrupted */
DECL|macro|SYNCHRONIZE
mdefine_line|#define SYNCHRONIZE()&t;barrier()
DECL|macro|lbolt
mdefine_line|#define lbolt&t;&t;jiffies
DECL|macro|rootdev
mdefine_line|#define rootdev&t;&t;ROOT_DEV
DECL|macro|__return_address
mdefine_line|#define __return_address __builtin_return_address(0)
DECL|macro|LONGLONG_MAX
mdefine_line|#define LONGLONG_MAX&t;9223372036854775807LL&t;/* max &quot;long long int&quot; */
DECL|macro|nopkg
mdefine_line|#define nopkg()&t;&t;( ENOSYS )
multiline_comment|/* IRIX uses a dynamic sizing algorithm (ndquot = 200 + numprocs*2) */
multiline_comment|/* we may well need to fine-tune this if it ever becomes an issue.  */
DECL|macro|DQUOT_MAX_HEURISTIC
mdefine_line|#define DQUOT_MAX_HEURISTIC&t;1024&t;/* NR_DQUOTS */
DECL|macro|ndquot
mdefine_line|#define ndquot&t;&t;&t;DQUOT_MAX_HEURISTIC
multiline_comment|/* IRIX uses the current size of the name cache to guess a good value */
multiline_comment|/* - this isn&squot;t the same but is a good enough starting point for now. */
DECL|macro|DQUOT_HASH_HEURISTIC
mdefine_line|#define DQUOT_HASH_HEURISTIC&t;files_stat.nr_files
multiline_comment|/* IRIX inodes maintain the project ID also, zero this field on Linux */
DECL|macro|DEFAULT_PROJID
mdefine_line|#define DEFAULT_PROJID&t;0
DECL|macro|dfltprid
mdefine_line|#define dfltprid&t;DEFAULT_PROJID
DECL|macro|MAXNAMELEN
mdefine_line|#define MAXNAMELEN&t;256
DECL|macro|MAXPATHLEN
mdefine_line|#define MAXPATHLEN&t;1024
DECL|macro|FINVIS
mdefine_line|#define FINVIS&t;&t;0x0100&t;/* don&squot;t update timestamps - XFS */
DECL|macro|MIN
mdefine_line|#define MIN(a,b)&t;(min(a,b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b)&t;(max(a,b))
DECL|macro|howmany
mdefine_line|#define howmany(x, y)&t;(((x)+((y)-1))/(y))
DECL|macro|roundup
mdefine_line|#define roundup(x, y)&t;((((x)+((y)-1))/(y))*(y))
multiline_comment|/* Move the kernel do_div definition off to one side */
macro_line|#if defined __i386__
multiline_comment|/* For ia32 we need to pull some tricks to get past various versions&n; * of the compiler which do not like us using do_div in the middle&n; * of large functions.&n; */
DECL|function|xfs_do_div
r_static
r_inline
id|__u32
id|xfs_do_div
c_func
(paren
r_void
op_star
id|a
comma
id|__u32
id|b
comma
r_int
id|n
)paren
(brace
id|__u32
id|mod
suffix:semicolon
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|4
suffix:colon
id|mod
op_assign
op_star
(paren
id|__u32
op_star
)paren
id|a
op_mod
id|b
suffix:semicolon
op_star
(paren
id|__u32
op_star
)paren
id|a
op_assign
op_star
(paren
id|__u32
op_star
)paren
id|a
op_div
id|b
suffix:semicolon
r_return
id|mod
suffix:semicolon
r_case
l_int|8
suffix:colon
(brace
r_int
r_int
id|__upper
comma
id|__low
comma
id|__high
comma
id|__mod
suffix:semicolon
id|__u64
id|c
op_assign
op_star
(paren
id|__u64
op_star
)paren
id|a
suffix:semicolon
id|__upper
op_assign
id|__high
op_assign
id|c
op_rshift
l_int|32
suffix:semicolon
id|__low
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|__high
)paren
(brace
id|__upper
op_assign
id|__high
op_mod
(paren
id|b
)paren
suffix:semicolon
id|__high
op_assign
id|__high
op_div
(paren
id|b
)paren
suffix:semicolon
)brace
id|asm
c_func
(paren
l_string|&quot;divl %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|__low
)paren
comma
l_string|&quot;=d&quot;
(paren
id|__mod
)paren
suffix:colon
l_string|&quot;rm&quot;
(paren
id|b
)paren
comma
l_string|&quot;0&quot;
(paren
id|__low
)paren
comma
l_string|&quot;1&quot;
(paren
id|__upper
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;&quot;
suffix:colon
l_string|&quot;=A&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|__low
)paren
comma
l_string|&quot;d&quot;
(paren
id|__high
)paren
)paren
suffix:semicolon
op_star
(paren
id|__u64
op_star
)paren
id|a
op_assign
id|c
suffix:semicolon
r_return
id|__mod
suffix:semicolon
)brace
)brace
multiline_comment|/* NOTREACHED */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Side effect free 64 bit mod operation */
DECL|function|xfs_do_mod
r_static
r_inline
id|__u32
id|xfs_do_mod
c_func
(paren
r_void
op_star
id|a
comma
id|__u32
id|b
comma
r_int
id|n
)paren
(brace
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|4
suffix:colon
r_return
op_star
(paren
id|__u32
op_star
)paren
id|a
op_mod
id|b
suffix:semicolon
r_case
l_int|8
suffix:colon
(brace
r_int
r_int
id|__upper
comma
id|__low
comma
id|__high
comma
id|__mod
suffix:semicolon
id|__u64
id|c
op_assign
op_star
(paren
id|__u64
op_star
)paren
id|a
suffix:semicolon
id|__upper
op_assign
id|__high
op_assign
id|c
op_rshift
l_int|32
suffix:semicolon
id|__low
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|__high
)paren
(brace
id|__upper
op_assign
id|__high
op_mod
(paren
id|b
)paren
suffix:semicolon
id|__high
op_assign
id|__high
op_div
(paren
id|b
)paren
suffix:semicolon
)brace
id|asm
c_func
(paren
l_string|&quot;divl %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|__low
)paren
comma
l_string|&quot;=d&quot;
(paren
id|__mod
)paren
suffix:colon
l_string|&quot;rm&quot;
(paren
id|b
)paren
comma
l_string|&quot;0&quot;
(paren
id|__low
)paren
comma
l_string|&quot;1&quot;
(paren
id|__upper
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;&quot;
suffix:colon
l_string|&quot;=A&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|__low
)paren
comma
l_string|&quot;d&quot;
(paren
id|__high
)paren
)paren
suffix:semicolon
r_return
id|__mod
suffix:semicolon
)brace
)brace
multiline_comment|/* NOTREACHED */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|function|xfs_do_div
r_static
r_inline
id|__u32
id|xfs_do_div
c_func
(paren
r_void
op_star
id|a
comma
id|__u32
id|b
comma
r_int
id|n
)paren
(brace
id|__u32
id|mod
suffix:semicolon
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|4
suffix:colon
id|mod
op_assign
op_star
(paren
id|__u32
op_star
)paren
id|a
op_mod
id|b
suffix:semicolon
op_star
(paren
id|__u32
op_star
)paren
id|a
op_assign
op_star
(paren
id|__u32
op_star
)paren
id|a
op_div
id|b
suffix:semicolon
r_return
id|mod
suffix:semicolon
r_case
l_int|8
suffix:colon
id|mod
op_assign
id|do_div
c_func
(paren
op_star
(paren
id|__u64
op_star
)paren
id|a
comma
id|b
)paren
suffix:semicolon
r_return
id|mod
suffix:semicolon
)brace
multiline_comment|/* NOTREACHED */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Side effect free 64 bit mod operation */
DECL|function|xfs_do_mod
r_static
r_inline
id|__u32
id|xfs_do_mod
c_func
(paren
r_void
op_star
id|a
comma
id|__u32
id|b
comma
r_int
id|n
)paren
(brace
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|4
suffix:colon
r_return
op_star
(paren
id|__u32
op_star
)paren
id|a
op_mod
id|b
suffix:semicolon
r_case
l_int|8
suffix:colon
(brace
id|__u64
id|c
op_assign
op_star
(paren
id|__u64
op_star
)paren
id|a
suffix:semicolon
r_return
id|do_div
c_func
(paren
id|c
comma
id|b
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* NOTREACHED */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|do_div
macro_line|#undef do_div
DECL|macro|do_div
mdefine_line|#define do_div(a, b)&t;xfs_do_div(&amp;(a), (b), sizeof(a))
DECL|macro|do_mod
mdefine_line|#define do_mod(a, b)&t;xfs_do_mod(&amp;(a), (b), sizeof(a))
DECL|function|roundup_64
r_static
r_inline
id|__uint64_t
id|roundup_64
c_func
(paren
id|__uint64_t
id|x
comma
id|__uint32_t
id|y
)paren
(brace
id|x
op_add_assign
id|y
op_minus
l_int|1
suffix:semicolon
id|do_div
c_func
(paren
id|x
comma
id|y
)paren
suffix:semicolon
r_return
id|x
op_star
id|y
suffix:semicolon
)brace
macro_line|#endif /* __XFS_LINUX__ */
eof