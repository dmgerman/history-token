multiline_comment|/*&n; * Copyright (c) 1982, 1986 Regents of the University of California.&n; * All rights reserved.&n; *&n; * This code is derived from software contributed to Berkeley by&n; * Robert Elz at The University of Melbourne.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; * 3. All advertising materials mentioning features or use of this software&n; *    must display the following acknowledgement:&n; *   This product includes software developed by the University of&n; *   California, Berkeley and its contributors.&n; * 4. Neither the name of the University nor the names of its contributors&n; *    may be used to endorse or promote products derived from this software&n; *    without specific prior written permission.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; * Version: $Id: quota.h,v 2.0 1996/11/17 16:48:14 mvw Exp mvw $&n; */
macro_line|#ifndef _LINUX_QUOTA_
DECL|macro|_LINUX_QUOTA_
mdefine_line|#define _LINUX_QUOTA_
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|__DQUOT_VERSION__
mdefine_line|#define __DQUOT_VERSION__&t;&quot;dquot_6.5.1&quot;
DECL|macro|__DQUOT_NUM_VERSION__
mdefine_line|#define __DQUOT_NUM_VERSION__&t;6*10000+5*100+1
DECL|typedef|qid_t
r_typedef
id|__kernel_uid32_t
id|qid_t
suffix:semicolon
multiline_comment|/* Type in which we store ids in memory */
DECL|typedef|qsize_t
r_typedef
id|__u64
id|qsize_t
suffix:semicolon
multiline_comment|/* Type in which we store sizes */
multiline_comment|/* Size of blocks in which are counted size limits */
DECL|macro|QUOTABLOCK_BITS
mdefine_line|#define QUOTABLOCK_BITS 10
DECL|macro|QUOTABLOCK_SIZE
mdefine_line|#define QUOTABLOCK_SIZE (1 &lt;&lt; QUOTABLOCK_BITS)
multiline_comment|/* Conversion routines from and to quota blocks */
DECL|macro|qb2kb
mdefine_line|#define qb2kb(x) ((x) &lt;&lt; (QUOTABLOCK_BITS-10))
DECL|macro|kb2qb
mdefine_line|#define kb2qb(x) ((x) &gt;&gt; (QUOTABLOCK_BITS-10))
DECL|macro|toqb
mdefine_line|#define toqb(x) (((x) + QUOTABLOCK_SIZE - 1) &gt;&gt; QUOTABLOCK_BITS)
DECL|macro|MAXQUOTAS
mdefine_line|#define MAXQUOTAS 2
DECL|macro|USRQUOTA
mdefine_line|#define USRQUOTA  0&t;&t;/* element used for user quotas */
DECL|macro|GRPQUOTA
mdefine_line|#define GRPQUOTA  1&t;&t;/* element used for group quotas */
multiline_comment|/*&n; * Definitions for the default names of the quotas files.&n; */
DECL|macro|INITQFNAMES
mdefine_line|#define INITQFNAMES { &bslash;&n;&t;&quot;user&quot;,    /* USRQUOTA */ &bslash;&n;&t;&quot;group&quot;,   /* GRPQUOTA */ &bslash;&n;&t;&quot;undefined&quot;, &bslash;&n;};
DECL|macro|QUOTAFILENAME
mdefine_line|#define QUOTAFILENAME &quot;quota&quot;
DECL|macro|QUOTAGROUP
mdefine_line|#define QUOTAGROUP &quot;staff&quot;
multiline_comment|/*&n; * Command definitions for the &squot;quotactl&squot; system call.&n; * The commands are broken into a main command defined below&n; * and a subcommand that is used to convey the type of&n; * quota that is being manipulated (see above).&n; */
DECL|macro|SUBCMDMASK
mdefine_line|#define SUBCMDMASK  0x00ff
DECL|macro|SUBCMDSHIFT
mdefine_line|#define SUBCMDSHIFT 8
DECL|macro|QCMD
mdefine_line|#define QCMD(cmd, type)  (((cmd) &lt;&lt; SUBCMDSHIFT) | ((type) &amp; SUBCMDMASK))
DECL|macro|Q_SYNC
mdefine_line|#define Q_SYNC     0x0600&t;/* sync disk copy of a filesystems quotas */
multiline_comment|/*&n; * Data for one user/group kept in memory&n; */
DECL|struct|mem_dqblk
r_struct
id|mem_dqblk
(brace
DECL|member|dqb_bhardlimit
id|__u32
id|dqb_bhardlimit
suffix:semicolon
multiline_comment|/* absolute limit on disk blks alloc */
DECL|member|dqb_bsoftlimit
id|__u32
id|dqb_bsoftlimit
suffix:semicolon
multiline_comment|/* preferred limit on disk blks */
DECL|member|dqb_curspace
id|qsize_t
id|dqb_curspace
suffix:semicolon
multiline_comment|/* current used space */
DECL|member|dqb_ihardlimit
id|__u32
id|dqb_ihardlimit
suffix:semicolon
multiline_comment|/* absolute limit on allocated inodes */
DECL|member|dqb_isoftlimit
id|__u32
id|dqb_isoftlimit
suffix:semicolon
multiline_comment|/* preferred inode limit */
DECL|member|dqb_curinodes
id|__u32
id|dqb_curinodes
suffix:semicolon
multiline_comment|/* current # allocated inodes */
DECL|member|dqb_btime
id|time_t
id|dqb_btime
suffix:semicolon
multiline_comment|/* time limit for excessive disk use */
DECL|member|dqb_itime
id|time_t
id|dqb_itime
suffix:semicolon
multiline_comment|/* time limit for excessive inode use */
)brace
suffix:semicolon
multiline_comment|/*&n; * Data for one quotafile kept in memory&n; */
r_struct
id|quota_format_type
suffix:semicolon
DECL|struct|mem_dqinfo
r_struct
id|mem_dqinfo
(brace
DECL|member|dqi_format
r_struct
id|quota_format_type
op_star
id|dqi_format
suffix:semicolon
DECL|member|dqi_flags
r_int
id|dqi_flags
suffix:semicolon
DECL|member|dqi_bgrace
r_int
r_int
id|dqi_bgrace
suffix:semicolon
DECL|member|dqi_igrace
r_int
r_int
id|dqi_igrace
suffix:semicolon
r_union
(brace
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|DQF_MASK
mdefine_line|#define DQF_MASK 0xffff&t;&t;/* Mask for format specific flags */
DECL|macro|DQF_INFO_DIRTY
mdefine_line|#define DQF_INFO_DIRTY 0x10000  /* Is info dirty? */
DECL|function|mark_info_dirty
r_extern
r_inline
r_void
id|mark_info_dirty
c_func
(paren
r_struct
id|mem_dqinfo
op_star
id|info
)paren
(brace
id|info-&gt;dqi_flags
op_or_assign
id|DQF_INFO_DIRTY
suffix:semicolon
)brace
DECL|macro|info_dirty
mdefine_line|#define info_dirty(info) ((info)-&gt;dqi_flags &amp; DQF_INFO_DIRTY)
DECL|macro|sb_dqopt
mdefine_line|#define sb_dqopt(sb) (&amp;(sb)-&gt;s_dquot)
macro_line|#endif  /* __KERNEL__ */
multiline_comment|/*&n; * Shorthand notation.&n; */
DECL|macro|dq_bhardlimit
mdefine_line|#define&t;dq_bhardlimit&t;dq_dqb.dqb_bhardlimit
DECL|macro|dq_bsoftlimit
mdefine_line|#define&t;dq_bsoftlimit&t;dq_dqb.dqb_bsoftlimit
DECL|macro|dq_curspace
mdefine_line|#define&t;dq_curspace&t;dq_dqb.dqb_curspace
DECL|macro|dq_ihardlimit
mdefine_line|#define&t;dq_ihardlimit&t;dq_dqb.dqb_ihardlimit
DECL|macro|dq_isoftlimit
mdefine_line|#define&t;dq_isoftlimit&t;dq_dqb.dqb_isoftlimit
DECL|macro|dq_curinodes
mdefine_line|#define&t;dq_curinodes&t;dq_dqb.dqb_curinodes
DECL|macro|dq_btime
mdefine_line|#define&t;dq_btime&t;dq_dqb.dqb_btime
DECL|macro|dq_itime
mdefine_line|#define&t;dq_itime&t;dq_dqb.dqb_itime
DECL|macro|dqoff
mdefine_line|#define dqoff(UID)      ((loff_t)((UID) * sizeof (struct dqblk)))
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|nr_dquots
comma
id|nr_free_dquots
suffix:semicolon
DECL|struct|dqstats
r_struct
id|dqstats
(brace
DECL|member|lookups
id|__u32
id|lookups
suffix:semicolon
DECL|member|drops
id|__u32
id|drops
suffix:semicolon
DECL|member|reads
id|__u32
id|reads
suffix:semicolon
DECL|member|writes
id|__u32
id|writes
suffix:semicolon
DECL|member|cache_hits
id|__u32
id|cache_hits
suffix:semicolon
DECL|member|allocated_dquots
id|__u32
id|allocated_dquots
suffix:semicolon
DECL|member|free_dquots
id|__u32
id|free_dquots
suffix:semicolon
DECL|member|syncs
id|__u32
id|syncs
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dqstats
id|dqstats
suffix:semicolon
DECL|macro|NR_DQHASH
mdefine_line|#define NR_DQHASH 43            /* Just an arbitrary number */
DECL|macro|DQ_LOCKED
mdefine_line|#define DQ_LOCKED     0x01&t;/* dquot under IO */
DECL|macro|DQ_MOD
mdefine_line|#define DQ_MOD        0x02&t;/* dquot modified since read */
DECL|macro|DQ_BLKS
mdefine_line|#define DQ_BLKS       0x10&t;/* uid/gid has been warned about blk limit */
DECL|macro|DQ_INODES
mdefine_line|#define DQ_INODES     0x20&t;/* uid/gid has been warned about inode limit */
DECL|macro|DQ_FAKE
mdefine_line|#define DQ_FAKE       0x40&t;/* no limits only usage */
DECL|macro|DQ_INVAL
mdefine_line|#define DQ_INVAL      0x80&t;/* dquot is going to be invalidated */
DECL|struct|dquot
r_struct
id|dquot
(brace
DECL|member|dq_hash
r_struct
id|list_head
id|dq_hash
suffix:semicolon
multiline_comment|/* Hash list in memory */
DECL|member|dq_inuse
r_struct
id|list_head
id|dq_inuse
suffix:semicolon
multiline_comment|/* List of all quotas */
DECL|member|dq_free
r_struct
id|list_head
id|dq_free
suffix:semicolon
multiline_comment|/* Free list element */
DECL|member|dq_wait_lock
id|wait_queue_head_t
id|dq_wait_lock
suffix:semicolon
multiline_comment|/* Pointer to waitqueue on dquot lock */
DECL|member|dq_wait_free
id|wait_queue_head_t
id|dq_wait_free
suffix:semicolon
multiline_comment|/* Pointer to waitqueue for quota to be unused */
DECL|member|dq_count
r_int
id|dq_count
suffix:semicolon
multiline_comment|/* Use count */
DECL|member|dq_dup_ref
r_int
id|dq_dup_ref
suffix:semicolon
multiline_comment|/* Number of duplicated refences */
multiline_comment|/* fields after this point are cleared when invalidating */
DECL|member|dq_sb
r_struct
id|super_block
op_star
id|dq_sb
suffix:semicolon
multiline_comment|/* superblock this applies to */
DECL|member|dq_id
r_int
r_int
id|dq_id
suffix:semicolon
multiline_comment|/* ID this applies to (uid, gid) */
DECL|member|dq_type
r_int
id|dq_type
suffix:semicolon
multiline_comment|/* Type of quota */
DECL|member|dq_flags
r_int
id|dq_flags
suffix:semicolon
multiline_comment|/* See DQ_* */
DECL|member|dq_referenced
r_int
r_int
id|dq_referenced
suffix:semicolon
multiline_comment|/* Number of times this dquot was &n;&t;&t;&t;&t;&t;   referenced during its lifetime */
DECL|member|dq_dqb
r_struct
id|mem_dqblk
id|dq_dqb
suffix:semicolon
multiline_comment|/* Diskquota usage */
)brace
suffix:semicolon
DECL|function|mark_dquot_dirty
r_extern
r_inline
r_void
id|mark_dquot_dirty
c_func
(paren
r_struct
id|dquot
op_star
id|dquot
)paren
(brace
id|dquot-&gt;dq_flags
op_or_assign
id|DQ_MOD
suffix:semicolon
)brace
DECL|macro|dquot_dirty
mdefine_line|#define dquot_dirty(dquot) ((dquot)-&gt;dq_flags &amp; DQ_MOD)
DECL|macro|NODQUOT
mdefine_line|#define NODQUOT (struct dquot *)NULL
DECL|macro|QUOTA_OK
mdefine_line|#define QUOTA_OK          0
DECL|macro|NO_QUOTA
mdefine_line|#define NO_QUOTA          1
multiline_comment|/* Operations which must be implemented by each quota format */
DECL|struct|quota_format_ops
r_struct
id|quota_format_ops
(brace
DECL|member|check_quota_file
r_int
(paren
op_star
id|check_quota_file
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
)paren
suffix:semicolon
multiline_comment|/* Detect whether file is in our format */
DECL|member|read_file_info
r_int
(paren
op_star
id|read_file_info
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
)paren
suffix:semicolon
multiline_comment|/* Read main info about file */
DECL|member|write_file_info
r_int
(paren
op_star
id|write_file_info
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
)paren
suffix:semicolon
multiline_comment|/* Write main info about file */
DECL|member|free_file_info
r_int
(paren
op_star
id|free_file_info
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
)paren
suffix:semicolon
multiline_comment|/* Called on quotaoff() */
DECL|member|read_dqblk
r_int
(paren
op_star
id|read_dqblk
)paren
(paren
r_struct
id|dquot
op_star
id|dquot
)paren
suffix:semicolon
multiline_comment|/* Read structure for one user */
DECL|member|commit_dqblk
r_int
(paren
op_star
id|commit_dqblk
)paren
(paren
r_struct
id|dquot
op_star
id|dquot
)paren
suffix:semicolon
multiline_comment|/* Write (or delete) structure for one user */
)brace
suffix:semicolon
DECL|struct|quota_format_type
r_struct
id|quota_format_type
(brace
DECL|member|qf_fmt_id
r_int
id|qf_fmt_id
suffix:semicolon
multiline_comment|/* Quota format id */
DECL|member|qf_ops
r_struct
id|quota_format_ops
op_star
id|qf_ops
suffix:semicolon
multiline_comment|/* Operations of format */
DECL|member|qf_next
r_struct
id|quota_format_type
op_star
id|qf_next
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else
macro_line|# /* nodep */ include &lt;sys/cdefs.h&gt;
id|__BEGIN_DECLS
r_int
id|quotactl
id|__P
(paren
(paren
r_int
comma
r_const
r_char
op_star
comma
r_int
comma
id|caddr_t
)paren
)paren
suffix:semicolon
id|__END_DECLS
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _QUOTA_ */
eof
