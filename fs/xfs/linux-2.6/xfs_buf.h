multiline_comment|/*&n; * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
multiline_comment|/*&n; * Written by Steve Lord, Jim Mostek, Russell Cattelan at SGI&n; */
macro_line|#ifndef __XFS_BUF_H__
DECL|macro|__XFS_BUF_H__
mdefine_line|#define __XFS_BUF_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
multiline_comment|/*&n; *&t;Base types&n; */
DECL|macro|XFS_BUF_DADDR_NULL
mdefine_line|#define XFS_BUF_DADDR_NULL ((xfs_daddr_t) (-1LL))
DECL|macro|page_buf_ctob
mdefine_line|#define page_buf_ctob(pp)&t;((pp) * PAGE_CACHE_SIZE)
DECL|macro|page_buf_btoc
mdefine_line|#define page_buf_btoc(dd)&t;(((dd) + PAGE_CACHE_SIZE - 1) &gt;&gt; PAGE_CACHE_SHIFT)
DECL|macro|page_buf_btoct
mdefine_line|#define page_buf_btoct(dd)&t;((dd) &gt;&gt; PAGE_CACHE_SHIFT)
DECL|macro|page_buf_poff
mdefine_line|#define page_buf_poff(aa)&t;((aa) &amp; ~PAGE_CACHE_MASK)
DECL|enum|page_buf_rw_e
r_typedef
r_enum
id|page_buf_rw_e
(brace
DECL|enumerator|PBRW_READ
id|PBRW_READ
op_assign
l_int|1
comma
multiline_comment|/* transfer into target memory */
DECL|enumerator|PBRW_WRITE
id|PBRW_WRITE
op_assign
l_int|2
comma
multiline_comment|/* transfer from target memory */
DECL|enumerator|PBRW_ZERO
id|PBRW_ZERO
op_assign
l_int|3
multiline_comment|/* Zero target memory */
DECL|typedef|page_buf_rw_t
)brace
id|page_buf_rw_t
suffix:semicolon
DECL|enum|page_buf_flags_e
r_typedef
r_enum
id|page_buf_flags_e
(brace
multiline_comment|/* pb_flags values */
DECL|enumerator|PBF_READ
id|PBF_READ
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* buffer intended for reading from device */
DECL|enumerator|PBF_WRITE
id|PBF_WRITE
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* buffer intended for writing to device   */
DECL|enumerator|PBF_MAPPED
id|PBF_MAPPED
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* buffer mapped (pb_addr valid)           */
DECL|enumerator|PBF_PARTIAL
id|PBF_PARTIAL
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
multiline_comment|/* buffer partially read                   */
DECL|enumerator|PBF_ASYNC
id|PBF_ASYNC
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
multiline_comment|/* initiator will not wait for completion  */
DECL|enumerator|PBF_NONE
id|PBF_NONE
op_assign
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
multiline_comment|/* buffer not read at all                  */
DECL|enumerator|PBF_DELWRI
id|PBF_DELWRI
op_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
multiline_comment|/* buffer has dirty pages                  */
DECL|enumerator|PBF_STALE
id|PBF_STALE
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
comma
multiline_comment|/* buffer has been staled, do not find it  */
DECL|enumerator|PBF_FS_MANAGED
id|PBF_FS_MANAGED
op_assign
(paren
l_int|1
op_lshift
l_int|8
)paren
comma
multiline_comment|/* filesystem controls freeing memory  */
DECL|enumerator|PBF_FS_DATAIOD
id|PBF_FS_DATAIOD
op_assign
(paren
l_int|1
op_lshift
l_int|9
)paren
comma
multiline_comment|/* schedule IO completion on fs datad  */
DECL|enumerator|PBF_FORCEIO
id|PBF_FORCEIO
op_assign
(paren
l_int|1
op_lshift
l_int|10
)paren
comma
multiline_comment|/* ignore any cache state&t;&t;   */
DECL|enumerator|PBF_FLUSH
id|PBF_FLUSH
op_assign
(paren
l_int|1
op_lshift
l_int|11
)paren
comma
multiline_comment|/* flush disk write cache&t;&t;   */
DECL|enumerator|PBF_READ_AHEAD
id|PBF_READ_AHEAD
op_assign
(paren
l_int|1
op_lshift
l_int|12
)paren
comma
multiline_comment|/* asynchronous read-ahead&t;&t;   */
multiline_comment|/* flags used only as arguments to access routines */
DECL|enumerator|PBF_LOCK
id|PBF_LOCK
op_assign
(paren
l_int|1
op_lshift
l_int|14
)paren
comma
multiline_comment|/* lock requested&t;&t;&t;   */
DECL|enumerator|PBF_TRYLOCK
id|PBF_TRYLOCK
op_assign
(paren
l_int|1
op_lshift
l_int|15
)paren
comma
multiline_comment|/* lock requested, but do not wait&t;   */
DECL|enumerator|PBF_DONT_BLOCK
id|PBF_DONT_BLOCK
op_assign
(paren
l_int|1
op_lshift
l_int|16
)paren
comma
multiline_comment|/* do not block in current thread&t;   */
multiline_comment|/* flags used only internally */
DECL|enumerator|_PBF_PAGE_CACHE
id|_PBF_PAGE_CACHE
op_assign
(paren
l_int|1
op_lshift
l_int|17
)paren
comma
multiline_comment|/* backed by pagecache&t;&t;   */
DECL|enumerator|_PBF_KMEM_ALLOC
id|_PBF_KMEM_ALLOC
op_assign
(paren
l_int|1
op_lshift
l_int|18
)paren
comma
multiline_comment|/* backed by kmem_alloc()&t;&t;   */
DECL|enumerator|_PBF_RUN_QUEUES
id|_PBF_RUN_QUEUES
op_assign
(paren
l_int|1
op_lshift
l_int|19
)paren
comma
multiline_comment|/* run block device task queue&t;   */
DECL|typedef|page_buf_flags_t
)brace
id|page_buf_flags_t
suffix:semicolon
DECL|macro|PBF_UPDATE
mdefine_line|#define PBF_UPDATE (PBF_READ | PBF_WRITE)
DECL|macro|PBF_NOT_DONE
mdefine_line|#define PBF_NOT_DONE(pb) (((pb)-&gt;pb_flags &amp; (PBF_PARTIAL|PBF_NONE)) != 0)
DECL|macro|PBF_DONE
mdefine_line|#define PBF_DONE(pb) (((pb)-&gt;pb_flags &amp; (PBF_PARTIAL|PBF_NONE)) == 0)
DECL|struct|xfs_bufhash
r_typedef
r_struct
id|xfs_bufhash
(brace
DECL|member|bh_list
r_struct
id|list_head
id|bh_list
suffix:semicolon
DECL|member|bh_lock
id|spinlock_t
id|bh_lock
suffix:semicolon
DECL|typedef|xfs_bufhash_t
)brace
id|xfs_bufhash_t
suffix:semicolon
DECL|struct|xfs_buftarg
r_typedef
r_struct
id|xfs_buftarg
(brace
DECL|member|pbr_dev
id|dev_t
id|pbr_dev
suffix:semicolon
DECL|member|pbr_bdev
r_struct
id|block_device
op_star
id|pbr_bdev
suffix:semicolon
DECL|member|pbr_mapping
r_struct
id|address_space
op_star
id|pbr_mapping
suffix:semicolon
DECL|member|pbr_bsize
r_int
r_int
id|pbr_bsize
suffix:semicolon
DECL|member|pbr_sshift
r_int
r_int
id|pbr_sshift
suffix:semicolon
DECL|member|pbr_smask
r_int
id|pbr_smask
suffix:semicolon
multiline_comment|/* per-device buffer hash table */
DECL|member|bt_hashmask
id|uint
id|bt_hashmask
suffix:semicolon
DECL|member|bt_hashshift
id|uint
id|bt_hashshift
suffix:semicolon
DECL|member|bt_hash
id|xfs_bufhash_t
op_star
id|bt_hash
suffix:semicolon
DECL|typedef|xfs_buftarg_t
)brace
id|xfs_buftarg_t
suffix:semicolon
multiline_comment|/*&n; *&t;xfs_buf_t:  Buffer structure for page cache-based buffers&n; *&n; * This buffer structure is used by the page cache buffer management routines&n; * to refer to an assembly of pages forming a logical buffer.  The actual I/O&n; * is performed with buffer_head structures, as required by drivers.&n; * &n; * The buffer structure is used on temporary basis only, and discarded when&n; * released.  The real data storage is recorded in the page cache.  Metadata is&n; * hashed to the block device on which the file system resides.&n; */
r_struct
id|xfs_buf
suffix:semicolon
multiline_comment|/* call-back function on I/O completion */
DECL|typedef|page_buf_iodone_t
r_typedef
r_void
(paren
op_star
id|page_buf_iodone_t
)paren
(paren
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
multiline_comment|/* call-back function on I/O completion */
DECL|typedef|page_buf_relse_t
r_typedef
r_void
(paren
op_star
id|page_buf_relse_t
)paren
(paren
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
multiline_comment|/* pre-write function */
DECL|typedef|page_buf_bdstrat_t
r_typedef
r_int
(paren
op_star
id|page_buf_bdstrat_t
)paren
(paren
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
DECL|macro|PB_PAGES
mdefine_line|#define PB_PAGES&t;2
DECL|struct|xfs_buf
r_typedef
r_struct
id|xfs_buf
(brace
DECL|member|pb_sema
r_struct
id|semaphore
id|pb_sema
suffix:semicolon
multiline_comment|/* semaphore for lockables  */
DECL|member|pb_queuetime
r_int
r_int
id|pb_queuetime
suffix:semicolon
multiline_comment|/* time buffer was queued   */
DECL|member|pb_pin_count
id|atomic_t
id|pb_pin_count
suffix:semicolon
multiline_comment|/* pin count&t;&t;    */
DECL|member|pb_waiters
id|wait_queue_head_t
id|pb_waiters
suffix:semicolon
multiline_comment|/* unpin waiters&t;    */
DECL|member|pb_list
r_struct
id|list_head
id|pb_list
suffix:semicolon
DECL|member|pb_flags
id|page_buf_flags_t
id|pb_flags
suffix:semicolon
multiline_comment|/* status flags */
DECL|member|pb_hash_list
r_struct
id|list_head
id|pb_hash_list
suffix:semicolon
multiline_comment|/* hash table list */
DECL|member|pb_hash
id|xfs_bufhash_t
op_star
id|pb_hash
suffix:semicolon
multiline_comment|/* hash table list start */
DECL|member|pb_target
id|xfs_buftarg_t
op_star
id|pb_target
suffix:semicolon
multiline_comment|/* buffer target (device) */
DECL|member|pb_hold
id|atomic_t
id|pb_hold
suffix:semicolon
multiline_comment|/* reference count */
DECL|member|pb_bn
id|xfs_daddr_t
id|pb_bn
suffix:semicolon
multiline_comment|/* block number for I/O */
DECL|member|pb_file_offset
id|loff_t
id|pb_file_offset
suffix:semicolon
multiline_comment|/* offset in file */
DECL|member|pb_buffer_length
r_int
id|pb_buffer_length
suffix:semicolon
multiline_comment|/* size of buffer in bytes */
DECL|member|pb_count_desired
r_int
id|pb_count_desired
suffix:semicolon
multiline_comment|/* desired transfer size */
DECL|member|pb_addr
r_void
op_star
id|pb_addr
suffix:semicolon
multiline_comment|/* virtual address of buffer */
DECL|member|pb_iodone_work
r_struct
id|work_struct
id|pb_iodone_work
suffix:semicolon
DECL|member|pb_io_remaining
id|atomic_t
id|pb_io_remaining
suffix:semicolon
multiline_comment|/* #outstanding I/O requests */
DECL|member|pb_iodone
id|page_buf_iodone_t
id|pb_iodone
suffix:semicolon
multiline_comment|/* I/O completion function */
DECL|member|pb_relse
id|page_buf_relse_t
id|pb_relse
suffix:semicolon
multiline_comment|/* releasing function */
DECL|member|pb_strat
id|page_buf_bdstrat_t
id|pb_strat
suffix:semicolon
multiline_comment|/* pre-write function */
DECL|member|pb_iodonesema
r_struct
id|semaphore
id|pb_iodonesema
suffix:semicolon
multiline_comment|/* Semaphore for I/O waiters */
DECL|member|pb_fspriv
r_void
op_star
id|pb_fspriv
suffix:semicolon
DECL|member|pb_fspriv2
r_void
op_star
id|pb_fspriv2
suffix:semicolon
DECL|member|pb_fspriv3
r_void
op_star
id|pb_fspriv3
suffix:semicolon
DECL|member|pb_error
r_int
r_int
id|pb_error
suffix:semicolon
multiline_comment|/* error code on I/O */
DECL|member|pb_locked
r_int
r_int
id|pb_locked
suffix:semicolon
multiline_comment|/* page array is locked */
DECL|member|pb_page_count
r_int
r_int
id|pb_page_count
suffix:semicolon
multiline_comment|/* size of page array */
DECL|member|pb_offset
r_int
r_int
id|pb_offset
suffix:semicolon
multiline_comment|/* page offset in first page */
DECL|member|pb_pages
r_struct
id|page
op_star
op_star
id|pb_pages
suffix:semicolon
multiline_comment|/* array of page pointers */
DECL|member|pb_page_array
r_struct
id|page
op_star
id|pb_page_array
(braket
id|PB_PAGES
)braket
suffix:semicolon
multiline_comment|/* inline pages */
macro_line|#ifdef PAGEBUF_LOCK_TRACKING
DECL|member|pb_last_holder
r_int
id|pb_last_holder
suffix:semicolon
macro_line|#endif
DECL|typedef|xfs_buf_t
)brace
id|xfs_buf_t
suffix:semicolon
multiline_comment|/* Finding and Reading Buffers */
r_extern
id|xfs_buf_t
op_star
id|_pagebuf_find
c_func
(paren
multiline_comment|/* find buffer for block if&t;*/
multiline_comment|/* the block is in memory&t;*/
id|xfs_buftarg_t
op_star
comma
multiline_comment|/* inode for block&t;&t;*/
id|loff_t
comma
multiline_comment|/* starting offset of range&t;*/
r_int
comma
multiline_comment|/* length of range&t;&t;*/
id|page_buf_flags_t
comma
multiline_comment|/* PBF_LOCK&t;&t;&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* newly allocated buffer&t;*/
DECL|macro|xfs_incore
mdefine_line|#define xfs_incore(buftarg,blkno,len,lockit) &bslash;&n;&t;_pagebuf_find(buftarg, blkno ,len, lockit, NULL)
r_extern
id|xfs_buf_t
op_star
id|xfs_buf_get_flags
c_func
(paren
multiline_comment|/* allocate a buffer&t;&t;*/
id|xfs_buftarg_t
op_star
comma
multiline_comment|/* inode for buffer&t;&t;*/
id|loff_t
comma
multiline_comment|/* starting offset of range     */
r_int
comma
multiline_comment|/* length of range              */
id|page_buf_flags_t
)paren
suffix:semicolon
multiline_comment|/* PBF_LOCK, PBF_READ,&t;&t;*/
multiline_comment|/* PBF_ASYNC&t;&t;&t;*/
DECL|macro|xfs_buf_get
mdefine_line|#define xfs_buf_get(target, blkno, len, flags) &bslash;&n;&t;xfs_buf_get_flags((target), (blkno), (len), PBF_LOCK | PBF_MAPPED)
r_extern
id|xfs_buf_t
op_star
id|xfs_buf_read_flags
c_func
(paren
multiline_comment|/* allocate and read a buffer&t;*/
id|xfs_buftarg_t
op_star
comma
multiline_comment|/* inode for buffer&t;&t;*/
id|loff_t
comma
multiline_comment|/* starting offset of range&t;*/
r_int
comma
multiline_comment|/* length of range&t;&t;*/
id|page_buf_flags_t
)paren
suffix:semicolon
multiline_comment|/* PBF_LOCK, PBF_ASYNC&t;&t;*/
DECL|macro|xfs_buf_read
mdefine_line|#define xfs_buf_read(target, blkno, len, flags) &bslash;&n;&t;xfs_buf_read_flags((target), (blkno), (len), PBF_LOCK | PBF_MAPPED)
r_extern
id|xfs_buf_t
op_star
id|pagebuf_lookup
c_func
(paren
id|xfs_buftarg_t
op_star
comma
id|loff_t
comma
multiline_comment|/* starting offset of range&t;*/
r_int
comma
multiline_comment|/* length of range&t;&t;*/
id|page_buf_flags_t
)paren
suffix:semicolon
multiline_comment|/* PBF_READ, PBF_WRITE,&t;&t;*/
multiline_comment|/* PBF_FORCEIO, &t;&t;*/
r_extern
id|xfs_buf_t
op_star
id|pagebuf_get_empty
c_func
(paren
multiline_comment|/* allocate pagebuf struct with&t;*/
multiline_comment|/*  no memory or disk address&t;*/
r_int
id|len
comma
id|xfs_buftarg_t
op_star
)paren
suffix:semicolon
multiline_comment|/* mount point &quot;fake&quot; inode&t;*/
r_extern
id|xfs_buf_t
op_star
id|pagebuf_get_no_daddr
c_func
(paren
multiline_comment|/* allocate pagebuf struct&t;*/
multiline_comment|/* without disk address&t;&t;*/
r_int
id|len
comma
id|xfs_buftarg_t
op_star
)paren
suffix:semicolon
multiline_comment|/* mount point &quot;fake&quot; inode&t;*/
r_extern
r_int
id|pagebuf_associate_memory
c_func
(paren
id|xfs_buf_t
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pagebuf_hold
c_func
(paren
multiline_comment|/* increment reference count&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to hold&t;&t;*/
r_extern
r_void
id|pagebuf_readahead
c_func
(paren
multiline_comment|/* read ahead into cache&t;*/
id|xfs_buftarg_t
op_star
comma
multiline_comment|/* target for buffer (or NULL)&t;*/
id|loff_t
comma
multiline_comment|/* starting offset of range     */
r_int
comma
multiline_comment|/* length of range              */
id|page_buf_flags_t
)paren
suffix:semicolon
multiline_comment|/* additional read flags&t;*/
multiline_comment|/* Releasing Buffers */
r_extern
r_void
id|pagebuf_free
c_func
(paren
multiline_comment|/* deallocate a buffer&t;&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to deallocate&t;&t;*/
r_extern
r_void
id|pagebuf_rele
c_func
(paren
multiline_comment|/* release hold on a buffer&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to release&t;&t;*/
multiline_comment|/* Locking and Unlocking Buffers */
r_extern
r_int
id|pagebuf_cond_lock
c_func
(paren
multiline_comment|/* lock buffer, if not locked&t;*/
multiline_comment|/* (returns -EBUSY if locked)&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to lock&t;&t;*/
r_extern
r_int
id|pagebuf_lock_value
c_func
(paren
multiline_comment|/* return count on lock&t;&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to check              */
r_extern
r_int
id|pagebuf_lock
c_func
(paren
multiline_comment|/* lock buffer                  */
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to lock               */
r_extern
r_void
id|pagebuf_unlock
c_func
(paren
multiline_comment|/* unlock buffer&t;&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to unlock&t;&t;*/
multiline_comment|/* Buffer Read and Write Routines */
r_extern
r_void
id|pagebuf_iodone
c_func
(paren
multiline_comment|/* mark buffer I/O complete&t;*/
id|xfs_buf_t
op_star
comma
multiline_comment|/* buffer to mark&t;&t;*/
r_int
comma
multiline_comment|/* use data/log helper thread.&t;*/
r_int
)paren
suffix:semicolon
multiline_comment|/* run completion locally, or in&n;&t;&t;&t;&t;&t; * a helper thread.&t;&t;*/
r_extern
r_void
id|pagebuf_ioerror
c_func
(paren
multiline_comment|/* mark buffer in error&t;(or not) */
id|xfs_buf_t
op_star
comma
multiline_comment|/* buffer to mark&t;&t;*/
r_int
)paren
suffix:semicolon
multiline_comment|/* error to store (0 if none)&t;*/
r_extern
r_int
id|pagebuf_iostart
c_func
(paren
multiline_comment|/* start I/O on a buffer&t;*/
id|xfs_buf_t
op_star
comma
multiline_comment|/* buffer to start&t;&t;*/
id|page_buf_flags_t
)paren
suffix:semicolon
multiline_comment|/* PBF_LOCK, PBF_ASYNC,&t;&t;*/
multiline_comment|/* PBF_READ, PBF_WRITE,&t;&t;*/
multiline_comment|/* PBF_DELWRI&t;&t;&t;*/
r_extern
r_int
id|pagebuf_iorequest
c_func
(paren
multiline_comment|/* start real I/O&t;&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to convey to device&t;*/
r_extern
r_int
id|pagebuf_iowait
c_func
(paren
multiline_comment|/* wait for buffer I/O done&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to wait on&t;&t;*/
r_extern
r_void
id|pagebuf_iomove
c_func
(paren
multiline_comment|/* move data in/out of pagebuf&t;*/
id|xfs_buf_t
op_star
comma
multiline_comment|/* buffer to manipulate&t;&t;*/
r_int
comma
multiline_comment|/* starting buffer offset&t;*/
r_int
comma
multiline_comment|/* length in buffer&t;&t;*/
id|caddr_t
comma
multiline_comment|/* data pointer&t;&t;&t;*/
id|page_buf_rw_t
)paren
suffix:semicolon
multiline_comment|/* direction&t;&t;&t;*/
DECL|function|pagebuf_iostrategy
r_static
r_inline
r_int
id|pagebuf_iostrategy
c_func
(paren
id|xfs_buf_t
op_star
id|pb
)paren
(brace
r_return
id|pb-&gt;pb_strat
ques
c_cond
id|pb
op_member_access_from_pointer
id|pb_strat
c_func
(paren
id|pb
)paren
suffix:colon
id|pagebuf_iorequest
c_func
(paren
id|pb
)paren
suffix:semicolon
)brace
DECL|function|pagebuf_geterror
r_static
r_inline
r_int
id|pagebuf_geterror
c_func
(paren
id|xfs_buf_t
op_star
id|pb
)paren
(brace
r_return
id|pb
ques
c_cond
id|pb-&gt;pb_error
suffix:colon
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* Buffer Utility Routines */
r_extern
id|caddr_t
id|pagebuf_offset
c_func
(paren
multiline_comment|/* pointer at offset in buffer&t;*/
id|xfs_buf_t
op_star
comma
multiline_comment|/* buffer to offset into&t;*/
r_int
)paren
suffix:semicolon
multiline_comment|/* offset&t;&t;&t;*/
multiline_comment|/* Pinning Buffer Storage in Memory */
r_extern
r_void
id|pagebuf_pin
c_func
(paren
multiline_comment|/* pin buffer in memory&t;&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to pin&t;&t;*/
r_extern
r_void
id|pagebuf_unpin
c_func
(paren
multiline_comment|/* unpin buffered data&t;&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to unpin&t;&t;*/
r_extern
r_int
id|pagebuf_ispin
c_func
(paren
multiline_comment|/* check if buffer is pinned&t;*/
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to check&t;&t;*/
multiline_comment|/* Delayed Write Buffer Routines */
r_extern
r_void
id|pagebuf_delwri_dequeue
c_func
(paren
id|xfs_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Buffer Daemon Setup Routines */
r_extern
r_int
id|pagebuf_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pagebuf_terminate
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef PAGEBUF_TRACE
r_extern
id|ktrace_t
op_star
id|pagebuf_trace_buf
suffix:semicolon
r_extern
r_void
id|pagebuf_trace
c_func
(paren
id|xfs_buf_t
op_star
comma
multiline_comment|/* buffer being traced&t;&t;*/
r_char
op_star
comma
multiline_comment|/* description of operation&t;*/
r_void
op_star
comma
multiline_comment|/* arbitrary diagnostic value&t;*/
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* return address&t;&t;*/
macro_line|#else
DECL|macro|pagebuf_trace
macro_line|# define pagebuf_trace(pb, id, ptr, ra)&t;do { } while (0)
macro_line|#endif
DECL|macro|pagebuf_target_name
mdefine_line|#define pagebuf_target_name(target)&t;&bslash;&n;&t;({ char __b[BDEVNAME_SIZE]; bdevname((target)-&gt;pbr_bdev, __b); __b; })
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
mdefine_line|#define XFS_BUF_ZEROFLAGS(x)&t;&bslash;&n;&t;((x)-&gt;pb_flags &amp;= ~(PBF_READ|PBF_WRITE|PBF_ASYNC|PBF_DELWRI))
DECL|macro|XFS_BUF_STALE
mdefine_line|#define XFS_BUF_STALE(x)&t;((x)-&gt;pb_flags |= XFS_B_STALE)
DECL|macro|XFS_BUF_UNSTALE
mdefine_line|#define XFS_BUF_UNSTALE(x)&t;((x)-&gt;pb_flags &amp;= ~XFS_B_STALE)
DECL|macro|XFS_BUF_ISSTALE
mdefine_line|#define XFS_BUF_ISSTALE(x)&t;((x)-&gt;pb_flags &amp; XFS_B_STALE)
DECL|macro|XFS_BUF_SUPER_STALE
mdefine_line|#define XFS_BUF_SUPER_STALE(x)&t;do {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XFS_BUF_STALE(x);&t;&bslash;&n;&t;&t;&t;&t;&t;pagebuf_delwri_dequeue(x);&t;&bslash;&n;&t;&t;&t;&t;&t;XFS_BUF_DONE(x);&t;&bslash;&n;&t;&t;&t;&t;} while (0)
DECL|macro|XFS_BUF_MANAGE
mdefine_line|#define XFS_BUF_MANAGE&t;&t;PBF_FS_MANAGED
DECL|macro|XFS_BUF_UNMANAGE
mdefine_line|#define XFS_BUF_UNMANAGE(x)&t;((x)-&gt;pb_flags &amp;= ~PBF_FS_MANAGED)
DECL|macro|XFS_BUF_DELAYWRITE
mdefine_line|#define XFS_BUF_DELAYWRITE(x)&t; ((x)-&gt;pb_flags |= PBF_DELWRI)
DECL|macro|XFS_BUF_UNDELAYWRITE
mdefine_line|#define XFS_BUF_UNDELAYWRITE(x)&t; pagebuf_delwri_dequeue(x)
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
id|xfs_buf_t
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
mdefine_line|#define XFS_BUF_SET_ADDR(bp, blk)&t;&t;&bslash;&n;&t;&t;&t;((bp)-&gt;pb_bn = (xfs_daddr_t)(blk))
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
mdefine_line|#define XFS_BUF_ISPINNED(bp)&t;pagebuf_ispin(bp)
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
mdefine_line|#define XFS_BUF_SET_TARGET(bp, target)&t;&bslash;&n;&t;&t;(bp)-&gt;pb_target = (target)
DECL|macro|XFS_BUF_TARGET
mdefine_line|#define XFS_BUF_TARGET(bp)&t;((bp)-&gt;pb_target)
DECL|macro|XFS_BUFTARG_NAME
mdefine_line|#define XFS_BUFTARG_NAME(target)&t;&bslash;&n;&t;&t;pagebuf_target_name(target)
DECL|macro|XFS_BUF_SET_VTYPE_REF
mdefine_line|#define XFS_BUF_SET_VTYPE_REF(bp, type, ref)
DECL|macro|XFS_BUF_SET_VTYPE
mdefine_line|#define XFS_BUF_SET_VTYPE(bp, type)
DECL|macro|XFS_BUF_SET_REF
mdefine_line|#define XFS_BUF_SET_REF(bp, ref)
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
id|xfs_buf_t
op_star
id|bp
)paren
(brace
id|bp-&gt;pb_fspriv3
op_assign
id|mp
suffix:semicolon
id|bp-&gt;pb_strat
op_assign
id|xfs_bdstrat_cb
suffix:semicolon
id|pagebuf_delwri_dequeue
c_func
(paren
id|bp
)paren
suffix:semicolon
r_return
id|pagebuf_iostart
c_func
(paren
id|bp
comma
id|PBF_WRITE
op_or
id|PBF_ASYNC
op_or
id|_PBF_RUN_QUEUES
)paren
suffix:semicolon
)brace
DECL|function|xfs_buf_relse
r_static
r_inline
r_void
id|xfs_buf_relse
c_func
(paren
id|xfs_buf_t
op_star
id|bp
)paren
(brace
r_if
c_cond
(paren
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
DECL|macro|xfs_buftrace
mdefine_line|#define xfs_buftrace(id, bp)&t;&bslash;&n;&t;    pagebuf_trace(bp, id, NULL, (void *)__builtin_return_address(0))
DECL|macro|xfs_biodone
mdefine_line|#define xfs_biodone(pb)&t;&t;    &bslash;&n;&t;    pagebuf_iodone(pb, (pb-&gt;pb_flags &amp; PBF_FS_DATAIOD), 0)
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
id|xfs_buf_t
op_star
id|pb
)paren
(brace
r_int
id|iowait
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
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iowait
)paren
id|pb-&gt;pb_flags
op_or_assign
id|_PBF_RUN_QUEUES
suffix:semicolon
id|pagebuf_delwri_dequeue
c_func
(paren
id|pb
)paren
suffix:semicolon
id|pagebuf_iostrategy
c_func
(paren
id|pb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iowait
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
id|xfs_buf_t
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
DECL|macro|xfs_baread
mdefine_line|#define xfs_baread(target, rablkno, ralen)  &bslash;&n;&t;pagebuf_readahead((target), (rablkno), (ralen), PBF_DONT_BLOCK)
DECL|macro|xfs_buf_get_empty
mdefine_line|#define xfs_buf_get_empty(len, target)&t;pagebuf_get_empty((len), (target))
DECL|macro|xfs_buf_get_noaddr
mdefine_line|#define xfs_buf_get_noaddr(len, target)&t;pagebuf_get_no_daddr((len), (target))
DECL|macro|xfs_buf_free
mdefine_line|#define xfs_buf_free(bp)&t;&t;pagebuf_free(bp)
multiline_comment|/*&n; *&t;Handling of buftargs.&n; */
r_extern
id|xfs_buftarg_t
op_star
id|xfs_alloc_buftarg
c_func
(paren
r_struct
id|block_device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xfs_free_buftarg
c_func
(paren
id|xfs_buftarg_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xfs_wait_buftarg
c_func
(paren
id|xfs_buftarg_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_setsize_buftarg
c_func
(paren
id|xfs_buftarg_t
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xfs_incore_relse
c_func
(paren
id|xfs_buftarg_t
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_flush_buftarg
c_func
(paren
id|xfs_buftarg_t
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|xfs_getsize_buftarg
mdefine_line|#define xfs_getsize_buftarg(buftarg) &bslash;&n;&t;block_size((buftarg)-&gt;pbr_bdev)
DECL|macro|xfs_readonly_buftarg
mdefine_line|#define xfs_readonly_buftarg(buftarg) &bslash;&n;&t;bdev_read_only((buftarg)-&gt;pbr_bdev)
DECL|macro|xfs_binval
mdefine_line|#define xfs_binval(buftarg) &bslash;&n;&t;xfs_flush_buftarg(buftarg, 1)
DECL|macro|XFS_bflush
mdefine_line|#define XFS_bflush(buftarg) &bslash;&n;&t;xfs_flush_buftarg(buftarg, 1)
macro_line|#endif&t;/* __XFS_BUF_H__ */
eof
