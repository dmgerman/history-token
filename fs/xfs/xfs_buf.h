multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_BUF_H__
DECL|macro|__XFS_BUF_H__
mdefine_line|#define __XFS_BUF_H__
multiline_comment|/* These are just for xfs_syncsub... it sets an internal variable&n; * then passes it to VOP_FLUSH_PAGES or adds the flags to a newly gotten buf_t&n; */
DECL|macro|XFS_B_ASYNC
mdefine_line|#define XFS_B_ASYNC&t;&t;PBF_ASYNC
DECL|macro|XFS_B_DELWRI
mdefine_line|#define XFS_B_DELWRI&t;&t;PBF_DELWRI
DECL|macro|XFS_B_READ
mdefine_line|#define XFS_B_READ&t;&t;PBF_READ
DECL|macro|XFS_B_WRITE
mdefine_line|#define XFS_B_WRITE&t;&t;PBF_WRITE
DECL|macro|XFS_B_STALE
mdefine_line|#define XFS_B_STALE&t;&t;PBF_STALE
DECL|macro|XFS_BUF_TRYLOCK
mdefine_line|#define XFS_BUF_TRYLOCK&t;&t;PBF_TRYLOCK
DECL|macro|XFS_INCORE_TRYLOCK
mdefine_line|#define XFS_INCORE_TRYLOCK&t;PBF_TRYLOCK
DECL|macro|XFS_BUF_LOCK
mdefine_line|#define XFS_BUF_LOCK&t;&t;PBF_LOCK
DECL|macro|XFS_BUF_MAPPED
mdefine_line|#define XFS_BUF_MAPPED&t;&t;PBF_MAPPED
DECL|macro|BUF_BUSY
mdefine_line|#define BUF_BUSY&t;&t;PBF_DONT_BLOCK
DECL|macro|XFS_BUF_BFLAGS
mdefine_line|#define XFS_BUF_BFLAGS(x)&t;((x)-&gt;pb_flags)
DECL|macro|XFS_BUF_ZEROFLAGS
mdefine_line|#define XFS_BUF_ZEROFLAGS(x)&t;&bslash;&n;&t;((x)-&gt;pb_flags &amp;= ~(PBF_READ|PBF_WRITE|PBF_ASYNC|PBF_SYNC|PBF_DELWRI))
DECL|macro|XFS_BUF_STALE
mdefine_line|#define XFS_BUF_STALE(x)&t;((x)-&gt;pb_flags |= XFS_B_STALE)
DECL|macro|XFS_BUF_UNSTALE
mdefine_line|#define XFS_BUF_UNSTALE(x)&t;((x)-&gt;pb_flags &amp;= ~XFS_B_STALE)
DECL|macro|XFS_BUF_ISSTALE
mdefine_line|#define XFS_BUF_ISSTALE(x)&t;((x)-&gt;pb_flags &amp; XFS_B_STALE)
DECL|macro|XFS_BUF_SUPER_STALE
mdefine_line|#define XFS_BUF_SUPER_STALE(x)&t;do {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XFS_BUF_STALE(x);&t;&bslash;&n;&t;&t;&t;&t;&t;xfs_buf_undelay(x);&t;&bslash;&n;&t;&t;&t;&t;&t;XFS_BUF_DONE(x);&t;&bslash;&n;&t;&t;&t;&t;} while (0)
DECL|macro|XFS_BUF_MANAGE
mdefine_line|#define XFS_BUF_MANAGE&t;&t;PBF_FS_MANAGED
DECL|macro|XFS_BUF_UNMANAGE
mdefine_line|#define XFS_BUF_UNMANAGE(x)&t;((x)-&gt;pb_flags &amp;= ~PBF_FS_MANAGED)
DECL|function|xfs_buf_undelay
r_static
r_inline
r_void
id|xfs_buf_undelay
c_func
(paren
id|page_buf_t
op_star
id|pb
)paren
(brace
r_if
c_cond
(paren
id|pb-&gt;pb_flags
op_amp
id|PBF_DELWRI
)paren
(brace
r_if
c_cond
(paren
id|pb-&gt;pb_list.next
op_ne
op_amp
id|pb-&gt;pb_list
)paren
(brace
id|pagebuf_delwri_dequeue
c_func
(paren
id|pb
)paren
suffix:semicolon
id|pagebuf_rele
c_func
(paren
id|pb
)paren
suffix:semicolon
)brace
r_else
(brace
id|pb-&gt;pb_flags
op_and_assign
op_complement
id|PBF_DELWRI
suffix:semicolon
)brace
)brace
)brace
DECL|macro|XFS_BUF_DELAYWRITE
mdefine_line|#define XFS_BUF_DELAYWRITE(x)&t; ((x)-&gt;pb_flags |= PBF_DELWRI)
DECL|macro|XFS_BUF_UNDELAYWRITE
mdefine_line|#define XFS_BUF_UNDELAYWRITE(x)&t; xfs_buf_undelay(x)
DECL|macro|XFS_BUF_ISDELAYWRITE
mdefine_line|#define XFS_BUF_ISDELAYWRITE(x)&t; ((x)-&gt;pb_flags &amp; PBF_DELWRI)
DECL|macro|XFS_BUF_ERROR
mdefine_line|#define XFS_BUF_ERROR(x,no)&t; pagebuf_ioerror(x,no)
DECL|macro|XFS_BUF_GETERROR
mdefine_line|#define XFS_BUF_GETERROR(x)&t; pagebuf_geterror(x)
DECL|macro|XFS_BUF_ISERROR
mdefine_line|#define XFS_BUF_ISERROR(x)&t; (pagebuf_geterror(x)?1:0)
DECL|macro|XFS_BUF_DONE
mdefine_line|#define XFS_BUF_DONE(x)&t;&t; ((x)-&gt;pb_flags &amp;= ~(PBF_PARTIAL|PBF_NONE))
DECL|macro|XFS_BUF_UNDONE
mdefine_line|#define XFS_BUF_UNDONE(x)&t; ((x)-&gt;pb_flags |= PBF_PARTIAL|PBF_NONE)
DECL|macro|XFS_BUF_ISDONE
mdefine_line|#define XFS_BUF_ISDONE(x)&t; (!(PBF_NOT_DONE(x)))
DECL|macro|XFS_BUF_BUSY
mdefine_line|#define XFS_BUF_BUSY(x)&t;&t; ((x)-&gt;pb_flags |= PBF_FORCEIO)
DECL|macro|XFS_BUF_UNBUSY
mdefine_line|#define XFS_BUF_UNBUSY(x)&t; ((x)-&gt;pb_flags &amp;= ~PBF_FORCEIO)
DECL|macro|XFS_BUF_ISBUSY
mdefine_line|#define XFS_BUF_ISBUSY(x)&t; (1)
DECL|macro|XFS_BUF_ASYNC
mdefine_line|#define XFS_BUF_ASYNC(x)&t; ((x)-&gt;pb_flags |= PBF_ASYNC)
DECL|macro|XFS_BUF_UNASYNC
mdefine_line|#define XFS_BUF_UNASYNC(x)&t; ((x)-&gt;pb_flags &amp;= ~PBF_ASYNC)
DECL|macro|XFS_BUF_ISASYNC
mdefine_line|#define XFS_BUF_ISASYNC(x)&t; ((x)-&gt;pb_flags &amp; PBF_ASYNC)
DECL|macro|XFS_BUF_FLUSH
mdefine_line|#define XFS_BUF_FLUSH(x)&t; ((x)-&gt;pb_flags |= PBF_FLUSH)
DECL|macro|XFS_BUF_UNFLUSH
mdefine_line|#define XFS_BUF_UNFLUSH(x)&t; ((x)-&gt;pb_flags &amp;= ~PBF_FLUSH)
DECL|macro|XFS_BUF_ISFLUSH
mdefine_line|#define XFS_BUF_ISFLUSH(x)&t; ((x)-&gt;pb_flags &amp; PBF_FLUSH)
DECL|macro|XFS_BUF_SHUT
mdefine_line|#define XFS_BUF_SHUT(x)&t;&t; printk(&quot;XFS_BUF_SHUT not implemented yet&bslash;n&quot;)
DECL|macro|XFS_BUF_UNSHUT
mdefine_line|#define XFS_BUF_UNSHUT(x)&t; printk(&quot;XFS_BUF_UNSHUT not implemented yet&bslash;n&quot;)
DECL|macro|XFS_BUF_ISSHUT
mdefine_line|#define XFS_BUF_ISSHUT(x)&t; (0)
DECL|macro|XFS_BUF_HOLD
mdefine_line|#define XFS_BUF_HOLD(x)&t;&t;pagebuf_hold(x)
DECL|macro|XFS_BUF_READ
mdefine_line|#define XFS_BUF_READ(x)&t;&t;((x)-&gt;pb_flags |= PBF_READ)
DECL|macro|XFS_BUF_UNREAD
mdefine_line|#define XFS_BUF_UNREAD(x)&t;((x)-&gt;pb_flags &amp;= ~PBF_READ)
DECL|macro|XFS_BUF_ISREAD
mdefine_line|#define XFS_BUF_ISREAD(x)&t;((x)-&gt;pb_flags &amp; PBF_READ)
DECL|macro|XFS_BUF_WRITE
mdefine_line|#define XFS_BUF_WRITE(x)&t;((x)-&gt;pb_flags |= PBF_WRITE)
DECL|macro|XFS_BUF_UNWRITE
mdefine_line|#define XFS_BUF_UNWRITE(x)&t;((x)-&gt;pb_flags &amp;= ~PBF_WRITE)
DECL|macro|XFS_BUF_ISWRITE
mdefine_line|#define XFS_BUF_ISWRITE(x)&t;((x)-&gt;pb_flags &amp; PBF_WRITE)
DECL|macro|XFS_BUF_ISUNINITIAL
mdefine_line|#define XFS_BUF_ISUNINITIAL(x)&t; (0)
DECL|macro|XFS_BUF_UNUNINITIAL
mdefine_line|#define XFS_BUF_UNUNINITIAL(x)&t; (0)
DECL|macro|XFS_BUF_BP_ISMAPPED
mdefine_line|#define XFS_BUF_BP_ISMAPPED(bp)&t; 1
DECL|typedef|xfs_buf_t
r_typedef
r_struct
id|page_buf_s
id|xfs_buf_t
suffix:semicolon
DECL|macro|xfs_buf
mdefine_line|#define xfs_buf page_buf_s
DECL|typedef|xfs_buftarg_t
r_typedef
r_struct
id|pb_target
id|xfs_buftarg_t
suffix:semicolon
DECL|macro|xfs_buftarg
mdefine_line|#define xfs_buftarg pb_target
DECL|macro|XFS_BUF_DATAIO
mdefine_line|#define XFS_BUF_DATAIO(x)&t;((x)-&gt;pb_flags |= PBF_FS_DATAIOD)
DECL|macro|XFS_BUF_UNDATAIO
mdefine_line|#define XFS_BUF_UNDATAIO(x)&t;((x)-&gt;pb_flags &amp;= ~PBF_FS_DATAIOD)
DECL|macro|XFS_BUF_IODONE_FUNC
mdefine_line|#define XFS_BUF_IODONE_FUNC(buf)&t;(buf)-&gt;pb_iodone
DECL|macro|XFS_BUF_SET_IODONE_FUNC
mdefine_line|#define XFS_BUF_SET_IODONE_FUNC(buf, func)&t;&bslash;&n;&t;&t;&t;(buf)-&gt;pb_iodone = (func)
DECL|macro|XFS_BUF_CLR_IODONE_FUNC
mdefine_line|#define XFS_BUF_CLR_IODONE_FUNC(buf)&t;&t;&bslash;&n;&t;&t;&t;(buf)-&gt;pb_iodone = NULL
DECL|macro|XFS_BUF_SET_BDSTRAT_FUNC
mdefine_line|#define XFS_BUF_SET_BDSTRAT_FUNC(buf, func)&t;&bslash;&n;&t;&t;&t;(buf)-&gt;pb_strat = (func)
DECL|macro|XFS_BUF_CLR_BDSTRAT_FUNC
mdefine_line|#define XFS_BUF_CLR_BDSTRAT_FUNC(buf)&t;&t;&bslash;&n;&t;&t;&t;(buf)-&gt;pb_strat = NULL
DECL|macro|XFS_BUF_FSPRIVATE
mdefine_line|#define XFS_BUF_FSPRIVATE(buf, type)&t;&t;&bslash;&n;&t;&t;&t;((type)(buf)-&gt;pb_fspriv)
DECL|macro|XFS_BUF_SET_FSPRIVATE
mdefine_line|#define XFS_BUF_SET_FSPRIVATE(buf, value)&t;&bslash;&n;&t;&t;&t;(buf)-&gt;pb_fspriv = (void *)(value)
DECL|macro|XFS_BUF_FSPRIVATE2
mdefine_line|#define XFS_BUF_FSPRIVATE2(buf, type)&t;&t;&bslash;&n;&t;&t;&t;((type)(buf)-&gt;pb_fspriv2)
DECL|macro|XFS_BUF_SET_FSPRIVATE2
mdefine_line|#define XFS_BUF_SET_FSPRIVATE2(buf, value)&t;&bslash;&n;&t;&t;&t;(buf)-&gt;pb_fspriv2 = (void *)(value)
DECL|macro|XFS_BUF_FSPRIVATE3
mdefine_line|#define XFS_BUF_FSPRIVATE3(buf, type)&t;&t;&bslash;&n;&t;&t;&t;((type)(buf)-&gt;pb_fspriv3)
DECL|macro|XFS_BUF_SET_FSPRIVATE3
mdefine_line|#define XFS_BUF_SET_FSPRIVATE3(buf, value)&t;&bslash;&n;&t;&t;&t;(buf)-&gt;pb_fspriv3  = (void *)(value)
DECL|macro|XFS_BUF_SET_START
mdefine_line|#define XFS_BUF_SET_START(buf)
DECL|macro|XFS_BUF_SET_BRELSE_FUNC
mdefine_line|#define XFS_BUF_SET_BRELSE_FUNC(buf, value) &bslash;&n;&t;&t;&t;(buf)-&gt;pb_relse = (value)
DECL|macro|XFS_BUF_PTR
mdefine_line|#define XFS_BUF_PTR(bp)&t;&t;(xfs_caddr_t)((bp)-&gt;pb_addr)
DECL|function|xfs_buf_offset
r_extern
r_inline
id|xfs_caddr_t
id|xfs_buf_offset
c_func
(paren
id|page_buf_t
op_star
id|bp
comma
r_int
id|offset
)paren
(brace
r_if
c_cond
(paren
id|bp-&gt;pb_flags
op_amp
id|PBF_MAPPED
)paren
r_return
id|XFS_BUF_PTR
c_func
(paren
id|bp
)paren
op_plus
id|offset
suffix:semicolon
r_return
(paren
id|xfs_caddr_t
)paren
id|pagebuf_offset
c_func
(paren
id|bp
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|macro|XFS_BUF_SET_PTR
mdefine_line|#define XFS_BUF_SET_PTR(bp, val, count)&t;&t;&bslash;&n;&t;&t;&t;&t;pagebuf_associate_memory(bp, val, count)
DECL|macro|XFS_BUF_ADDR
mdefine_line|#define XFS_BUF_ADDR(bp)&t;((bp)-&gt;pb_bn)
DECL|macro|XFS_BUF_SET_ADDR
mdefine_line|#define XFS_BUF_SET_ADDR(bp, blk)&t;&t;&bslash;&n;&t;&t;&t;((bp)-&gt;pb_bn = (page_buf_daddr_t)(blk))
DECL|macro|XFS_BUF_OFFSET
mdefine_line|#define XFS_BUF_OFFSET(bp)&t;((bp)-&gt;pb_file_offset)
DECL|macro|XFS_BUF_SET_OFFSET
mdefine_line|#define XFS_BUF_SET_OFFSET(bp, off)&t;&t;&bslash;&n;&t;&t;&t;((bp)-&gt;pb_file_offset = (off))
DECL|macro|XFS_BUF_COUNT
mdefine_line|#define XFS_BUF_COUNT(bp)&t;((bp)-&gt;pb_count_desired)
DECL|macro|XFS_BUF_SET_COUNT
mdefine_line|#define XFS_BUF_SET_COUNT(bp, cnt)&t;&t;&bslash;&n;&t;&t;&t;((bp)-&gt;pb_count_desired = (cnt))
DECL|macro|XFS_BUF_SIZE
mdefine_line|#define XFS_BUF_SIZE(bp)&t;((bp)-&gt;pb_buffer_length)
DECL|macro|XFS_BUF_SET_SIZE
mdefine_line|#define XFS_BUF_SET_SIZE(bp, cnt)&t;&t;&bslash;&n;&t;&t;&t;((bp)-&gt;pb_buffer_length = (cnt))
DECL|macro|XFS_BUF_SET_VTYPE_REF
mdefine_line|#define XFS_BUF_SET_VTYPE_REF(bp, type, ref)
DECL|macro|XFS_BUF_SET_VTYPE
mdefine_line|#define XFS_BUF_SET_VTYPE(bp, type)
DECL|macro|XFS_BUF_SET_REF
mdefine_line|#define XFS_BUF_SET_REF(bp, ref)
DECL|macro|XFS_BUF_ISPINNED
mdefine_line|#define XFS_BUF_ISPINNED(bp)   pagebuf_ispin(bp)
DECL|macro|XFS_BUF_VALUSEMA
mdefine_line|#define XFS_BUF_VALUSEMA(bp)&t;pagebuf_lock_value(bp)
DECL|macro|XFS_BUF_CPSEMA
mdefine_line|#define XFS_BUF_CPSEMA(bp)&t;(pagebuf_cond_lock(bp) == 0)
DECL|macro|XFS_BUF_VSEMA
mdefine_line|#define XFS_BUF_VSEMA(bp)&t;pagebuf_unlock(bp)
DECL|macro|XFS_BUF_PSEMA
mdefine_line|#define XFS_BUF_PSEMA(bp,x)&t;pagebuf_lock(bp)
DECL|macro|XFS_BUF_V_IODONESEMA
mdefine_line|#define XFS_BUF_V_IODONESEMA(bp) up(&amp;bp-&gt;pb_iodonesema);
multiline_comment|/* setup the buffer target from a buftarg structure */
DECL|macro|XFS_BUF_SET_TARGET
mdefine_line|#define XFS_BUF_SET_TARGET(bp, target)&t;&bslash;&n;&t;(bp)-&gt;pb_target = (target)
DECL|macro|XFS_BUF_TARGET
mdefine_line|#define XFS_BUF_TARGET(bp)&t;((bp)-&gt;pb_target)
DECL|macro|XFS_BUF_TARGET_DEV
mdefine_line|#define XFS_BUF_TARGET_DEV(bp)&t;((bp)-&gt;pb_target-&gt;pbr_dev)
DECL|macro|XFS_BUF_SET_VTYPE_REF
mdefine_line|#define XFS_BUF_SET_VTYPE_REF(bp, type, ref)
DECL|macro|XFS_BUF_SET_VTYPE
mdefine_line|#define XFS_BUF_SET_VTYPE(bp, type)
DECL|macro|XFS_BUF_SET_REF
mdefine_line|#define XFS_BUF_SET_REF(bp, ref)
DECL|macro|xfs_buf_read
mdefine_line|#define xfs_buf_read(target, blkno, len, flags) &bslash;&n;&t;&t;pagebuf_get((target), (blkno), (len), &bslash;&n;&t;&t;&t;PBF_LOCK | PBF_READ | PBF_MAPPED | PBF_MAPPABLE)
DECL|macro|xfs_buf_get
mdefine_line|#define xfs_buf_get(target, blkno, len, flags) &bslash;&n;&t;&t;pagebuf_get((target), (blkno), (len), &bslash;&n;&t;&t;&t;PBF_LOCK | PBF_MAPPED | PBF_MAPPABLE)
DECL|macro|xfs_buf_read_flags
mdefine_line|#define xfs_buf_read_flags(target, blkno, len, flags) &bslash;&n;&t;&t;pagebuf_get((target), (blkno), (len), &bslash;&n;&t;&t;&t;PBF_READ | PBF_MAPPABLE | flags)
DECL|macro|xfs_buf_get_flags
mdefine_line|#define xfs_buf_get_flags(target, blkno, len, flags) &bslash;&n;&t;&t;pagebuf_get((target), (blkno), (len), &bslash;&n;&t;&t;&t;PBF_MAPPABLE | flags)
DECL|function|xfs_bawrite
r_static
r_inline
r_int
id|xfs_bawrite
c_func
(paren
r_void
op_star
id|mp
comma
id|page_buf_t
op_star
id|bp
)paren
(brace
r_int
id|ret
suffix:semicolon
id|bp-&gt;pb_fspriv3
op_assign
id|mp
suffix:semicolon
id|bp-&gt;pb_strat
op_assign
id|xfs_bdstrat_cb
suffix:semicolon
id|xfs_buf_undelay
c_func
(paren
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|pagebuf_iostart
c_func
(paren
id|bp
comma
id|PBF_WRITE
op_or
id|PBF_ASYNC
)paren
)paren
op_eq
l_int|0
)paren
id|pagebuf_run_queues
c_func
(paren
id|bp
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|xfs_buf_relse
r_static
r_inline
r_void
id|xfs_buf_relse
c_func
(paren
id|page_buf_t
op_star
id|bp
)paren
(brace
r_if
c_cond
(paren
(paren
id|bp-&gt;pb_flags
op_amp
id|_PBF_LOCKABLE
)paren
op_logical_and
op_logical_neg
id|bp-&gt;pb_relse
)paren
id|pagebuf_unlock
c_func
(paren
id|bp
)paren
suffix:semicolon
id|pagebuf_rele
c_func
(paren
id|bp
)paren
suffix:semicolon
)brace
DECL|macro|xfs_bpin
mdefine_line|#define xfs_bpin(bp)&t;&t;pagebuf_pin(bp)
DECL|macro|xfs_bunpin
mdefine_line|#define xfs_bunpin(bp)&t;&t;pagebuf_unpin(bp)
macro_line|#ifdef PAGEBUF_TRACE
DECL|macro|PB_DEFINE_TRACES
macro_line|# define PB_DEFINE_TRACES
macro_line|# include &lt;pagebuf/page_buf_trace.h&gt;
DECL|macro|xfs_buftrace
macro_line|# define xfs_buftrace(id, bp)&t;PB_TRACE(bp, PB_TRACE_REC(external), (void *)id)
macro_line|#else
DECL|macro|xfs_buftrace
macro_line|# define xfs_buftrace(id, bp)&t;do { } while (0)
macro_line|#endif
DECL|macro|xfs_biodone
mdefine_line|#define xfs_biodone(pb)&t;&t;    &bslash;&n;&t;    pagebuf_iodone(pb, (pb-&gt;pb_flags &amp; PBF_FS_DATAIOD), 0)
DECL|macro|xfs_incore
mdefine_line|#define xfs_incore(buftarg,blkno,len,lockit) &bslash;&n;&t;    pagebuf_find(buftarg, blkno ,len, lockit)
DECL|macro|xfs_biomove
mdefine_line|#define xfs_biomove(pb, off, len, data, rw) &bslash;&n;&t;    pagebuf_iomove((pb), (off), (len), (data), &bslash;&n;&t;&t;((rw) == XFS_B_WRITE) ? PBRW_WRITE : PBRW_READ)
DECL|macro|xfs_biozero
mdefine_line|#define xfs_biozero(pb, off, len) &bslash;&n;&t;    pagebuf_iomove((pb), (off), (len), NULL, PBRW_ZERO)
DECL|function|XFS_bwrite
r_static
r_inline
r_int
id|XFS_bwrite
c_func
(paren
id|page_buf_t
op_star
id|pb
)paren
(brace
r_int
id|sync
op_assign
(paren
id|pb-&gt;pb_flags
op_amp
id|PBF_ASYNC
)paren
op_eq
l_int|0
suffix:semicolon
r_int
id|error
suffix:semicolon
id|pb-&gt;pb_flags
op_or_assign
id|PBF_SYNC
suffix:semicolon
id|xfs_buf_undelay
c_func
(paren
id|pb
)paren
suffix:semicolon
id|__pagebuf_iorequest
c_func
(paren
id|pb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sync
)paren
(brace
id|error
op_assign
id|pagebuf_iowait
c_func
(paren
id|pb
)paren
suffix:semicolon
id|xfs_buf_relse
c_func
(paren
id|pb
)paren
suffix:semicolon
)brace
r_else
(brace
id|pagebuf_run_queues
c_func
(paren
id|pb
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|macro|XFS_bdwrite
mdefine_line|#define XFS_bdwrite(pb)&t;&t;     &bslash;&n;&t;    pagebuf_iostart(pb, PBF_DELWRI | PBF_ASYNC)
DECL|function|xfs_bdwrite
r_static
r_inline
r_int
id|xfs_bdwrite
c_func
(paren
r_void
op_star
id|mp
comma
id|page_buf_t
op_star
id|bp
)paren
(brace
id|bp-&gt;pb_strat
op_assign
id|xfs_bdstrat_cb
suffix:semicolon
id|bp-&gt;pb_fspriv3
op_assign
id|mp
suffix:semicolon
r_return
id|pagebuf_iostart
c_func
(paren
id|bp
comma
id|PBF_DELWRI
op_or
id|PBF_ASYNC
)paren
suffix:semicolon
)brace
DECL|macro|XFS_bdstrat
mdefine_line|#define XFS_bdstrat(bp) pagebuf_iorequest(bp)
DECL|macro|xfs_iowait
mdefine_line|#define xfs_iowait(pb)&t;pagebuf_iowait(pb)
multiline_comment|/*&n; * Go through all incore buffers, and release buffers&n; * if they belong to the given device. This is used in&n; * filesystem error handling to preserve the consistency&n; * of its metadata.&n; */
DECL|macro|xfs_binval
mdefine_line|#define xfs_binval(buftarg)&t;xfs_flush_buftarg(buftarg)
DECL|macro|XFS_bflush
mdefine_line|#define XFS_bflush(buftarg)&t;xfs_flush_buftarg(buftarg)
DECL|macro|xfs_incore_relse
mdefine_line|#define xfs_incore_relse(buftarg,delwri_only,wait)&t;&bslash;&n;&t;xfs_relse_buftarg(buftarg)
DECL|macro|xfs_baread
mdefine_line|#define xfs_baread(target, rablkno, ralen)  &bslash;&n;&t;pagebuf_readahead((target), (rablkno), (ralen), PBF_DONT_BLOCK)
DECL|macro|xfs_buf_get_empty
mdefine_line|#define xfs_buf_get_empty(len, target)&t;pagebuf_get_empty((len), (target))
DECL|macro|xfs_buf_get_noaddr
mdefine_line|#define xfs_buf_get_noaddr(len, target)&t;pagebuf_get_no_daddr((len), (target))
DECL|macro|xfs_buf_free
mdefine_line|#define xfs_buf_free(bp)&t;&t;pagebuf_free(bp)
macro_line|#endif
eof
