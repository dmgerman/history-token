multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
multiline_comment|/*&n; * Written by Steve Lord, Jim Mostek, Russell Cattelan at SGI&n; */
macro_line|#ifndef __PAGE_BUF_H__
DECL|macro|__PAGE_BUF_H__
mdefine_line|#define __PAGE_BUF_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
multiline_comment|/*&n; * Turn this on to get pagebuf lock ownership&n;#define PAGEBUF_LOCK_TRACKING&n;*/
multiline_comment|/*&n; *&t;Base types&n; */
multiline_comment|/* daddr must be signed since -1 is used for bmaps that are not yet allocated */
DECL|typedef|page_buf_daddr_t
r_typedef
id|loff_t
id|page_buf_daddr_t
suffix:semicolon
DECL|macro|PAGE_BUF_DADDR_NULL
mdefine_line|#define PAGE_BUF_DADDR_NULL ((page_buf_daddr_t) (-1LL))
DECL|typedef|page_buf_dsize_t
r_typedef
r_int
id|page_buf_dsize_t
suffix:semicolon
multiline_comment|/* size of buffer in blocks */
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
r_typedef
r_enum
(brace
multiline_comment|/* pbm_flags values */
DECL|enumerator|PBMF_EOF
id|PBMF_EOF
op_assign
l_int|0x01
comma
multiline_comment|/* mapping contains EOF&t;&t;*/
DECL|enumerator|PBMF_HOLE
id|PBMF_HOLE
op_assign
l_int|0x02
comma
multiline_comment|/* mapping covers a hole&t;*/
DECL|enumerator|PBMF_DELAY
id|PBMF_DELAY
op_assign
l_int|0x04
comma
multiline_comment|/* mapping covers delalloc region  */
DECL|enumerator|PBMF_UNWRITTEN
id|PBMF_UNWRITTEN
op_assign
l_int|0x20
comma
multiline_comment|/* mapping covers allocated&t;*/
multiline_comment|/* but uninitialized file data&t;*/
DECL|enumerator|PBMF_NEW
id|PBMF_NEW
op_assign
l_int|0x40
multiline_comment|/* just allocated&t;&t;*/
DECL|typedef|bmap_flags_t
)brace
id|bmap_flags_t
suffix:semicolon
r_typedef
r_enum
(brace
multiline_comment|/* base extent manipulation calls */
DECL|enumerator|BMAP_READ
id|BMAP_READ
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* read extents */
DECL|enumerator|BMAP_WRITE
id|BMAP_WRITE
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* create extents */
DECL|enumerator|BMAP_ALLOCATE
id|BMAP_ALLOCATE
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* delayed allocate to real extents */
DECL|enumerator|BMAP_UNWRITTEN
id|BMAP_UNWRITTEN
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
multiline_comment|/* unwritten extents to real extents */
multiline_comment|/* modifiers */
DECL|enumerator|BMAP_IGNSTATE
id|BMAP_IGNSTATE
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
multiline_comment|/* ignore unwritten state on read */
DECL|enumerator|BMAP_DIRECT
id|BMAP_DIRECT
op_assign
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
multiline_comment|/* direct instead of buffered write */
DECL|enumerator|BMAP_MMAP
id|BMAP_MMAP
op_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
multiline_comment|/* allocate for mmap write */
DECL|enumerator|BMAP_SYNC
id|BMAP_SYNC
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
comma
multiline_comment|/* sync write */
DECL|enumerator|BMAP_TRYLOCK
id|BMAP_TRYLOCK
op_assign
(paren
l_int|1
op_lshift
l_int|8
)paren
comma
multiline_comment|/* non-blocking request */
DECL|enumerator|BMAP_DEVICE
id|BMAP_DEVICE
op_assign
(paren
l_int|1
op_lshift
l_int|9
)paren
comma
multiline_comment|/* we only want to know the device */
DECL|typedef|bmapi_flags_t
)brace
id|bmapi_flags_t
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
DECL|enumerator|PBF_FREED
id|PBF_FREED
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
comma
multiline_comment|/* buffer has been freed and is invalid    */
DECL|enumerator|PBF_SYNC
id|PBF_SYNC
op_assign
(paren
l_int|1
op_lshift
l_int|8
)paren
comma
multiline_comment|/* force updates to disk                   */
DECL|enumerator|PBF_MAPPABLE
id|PBF_MAPPABLE
op_assign
(paren
l_int|1
op_lshift
l_int|9
)paren
comma
multiline_comment|/* use directly-addressable pages          */
DECL|enumerator|PBF_STALE
id|PBF_STALE
op_assign
(paren
l_int|1
op_lshift
l_int|10
)paren
comma
multiline_comment|/* buffer has been staled, do not find it  */
DECL|enumerator|PBF_FS_MANAGED
id|PBF_FS_MANAGED
op_assign
(paren
l_int|1
op_lshift
l_int|11
)paren
comma
multiline_comment|/* filesystem controls freeing memory  */
DECL|enumerator|PBF_FS_DATAIOD
id|PBF_FS_DATAIOD
op_assign
(paren
l_int|1
op_lshift
l_int|12
)paren
comma
multiline_comment|/* schedule IO completion on fs datad  */
multiline_comment|/* flags used only as arguments to access routines */
DECL|enumerator|PBF_LOCK
id|PBF_LOCK
op_assign
(paren
l_int|1
op_lshift
l_int|13
)paren
comma
multiline_comment|/* lock requested&t;&t;&t;   */
DECL|enumerator|PBF_TRYLOCK
id|PBF_TRYLOCK
op_assign
(paren
l_int|1
op_lshift
l_int|14
)paren
comma
multiline_comment|/* lock requested, but do not wait&t;   */
DECL|enumerator|PBF_DONT_BLOCK
id|PBF_DONT_BLOCK
op_assign
(paren
l_int|1
op_lshift
l_int|15
)paren
comma
multiline_comment|/* do not block in current thread&t;   */
multiline_comment|/* flags used only internally */
DECL|enumerator|_PBF_LOCKABLE
id|_PBF_LOCKABLE
op_assign
(paren
l_int|1
op_lshift
l_int|16
)paren
comma
multiline_comment|/* page_buf_t may be locked&t;&t;   */
DECL|enumerator|_PBF_PRIVATE_BH
id|_PBF_PRIVATE_BH
op_assign
(paren
l_int|1
op_lshift
l_int|17
)paren
comma
multiline_comment|/* do not use public buffer heads&t;   */
DECL|enumerator|_PBF_ALL_PAGES_MAPPED
id|_PBF_ALL_PAGES_MAPPED
op_assign
(paren
l_int|1
op_lshift
l_int|18
)paren
comma
multiline_comment|/* all pages in range mapped&t;   */
DECL|enumerator|_PBF_ADDR_ALLOCATED
id|_PBF_ADDR_ALLOCATED
op_assign
(paren
l_int|1
op_lshift
l_int|19
)paren
comma
multiline_comment|/* pb_addr space was allocated&t;   */
DECL|enumerator|_PBF_MEM_ALLOCATED
id|_PBF_MEM_ALLOCATED
op_assign
(paren
l_int|1
op_lshift
l_int|20
)paren
comma
multiline_comment|/* pb_mem+underlying pages alloc&squot;d */
DECL|enumerator|PBF_FORCEIO
id|PBF_FORCEIO
op_assign
(paren
l_int|1
op_lshift
l_int|21
)paren
comma
DECL|enumerator|PBF_FLUSH
id|PBF_FLUSH
op_assign
(paren
l_int|1
op_lshift
l_int|22
)paren
comma
multiline_comment|/* flush disk write cache&t;&t;   */
DECL|enumerator|PBF_READ_AHEAD
id|PBF_READ_AHEAD
op_assign
(paren
l_int|1
op_lshift
l_int|23
)paren
comma
DECL|enumerator|PBF_RUN_QUEUES
id|PBF_RUN_QUEUES
op_assign
(paren
l_int|1
op_lshift
l_int|24
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
DECL|macro|PBR_SECTOR_ONLY
mdefine_line|#define PBR_SECTOR_ONLY&t;1&t;/* only use sector size buffer heads */
DECL|macro|PBR_ALIGNED_ONLY
mdefine_line|#define PBR_ALIGNED_ONLY 2&t;/* only use aligned I/O */
DECL|struct|pb_target
r_typedef
r_struct
id|pb_target
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
DECL|typedef|pb_target_t
)brace
id|pb_target_t
suffix:semicolon
multiline_comment|/*&n; *&t;page_buf_bmap_t:  File system I/O map&n; *&n; * The pbm_bn, pbm_offset and pbm_length fields are expressed in disk blocks.&n; * The pbm_length field specifies the size of the underlying backing store&n; * for the particular mapping.&n; *&n; * The pbm_bsize, pbm_size and pbm_delta fields are in bytes and indicate&n; * the size of the mapping, the number of bytes that are valid to access&n; * (read or write), and the offset into the mapping, given the offset&n; * supplied to the file I/O map routine.  pbm_delta is the offset of the&n; * desired data from the beginning of the mapping.&n; *&n; * When a request is made to read beyond the logical end of the object,&n; * pbm_size may be set to 0, but pbm_offset and pbm_length should be set to&n; * the actual amount of underlying storage that has been allocated, if any.&n; */
DECL|struct|page_buf_bmap_s
r_typedef
r_struct
id|page_buf_bmap_s
(brace
DECL|member|pbm_bn
id|page_buf_daddr_t
id|pbm_bn
suffix:semicolon
multiline_comment|/* block number in file system&t;    */
DECL|member|pbm_target
id|pb_target_t
op_star
id|pbm_target
suffix:semicolon
multiline_comment|/* device to do I/O to&t;&t;    */
DECL|member|pbm_offset
id|loff_t
id|pbm_offset
suffix:semicolon
multiline_comment|/* byte offset of mapping in file   */
DECL|member|pbm_delta
r_int
id|pbm_delta
suffix:semicolon
multiline_comment|/* offset of request into bmap&t;    */
DECL|member|pbm_bsize
r_int
id|pbm_bsize
suffix:semicolon
multiline_comment|/* size of this mapping in bytes    */
DECL|member|pbm_flags
id|bmap_flags_t
id|pbm_flags
suffix:semicolon
multiline_comment|/* options flags for mapping&t;    */
DECL|typedef|page_buf_bmap_t
)brace
id|page_buf_bmap_t
suffix:semicolon
DECL|typedef|pb_bmap_t
r_typedef
id|page_buf_bmap_t
id|pb_bmap_t
suffix:semicolon
multiline_comment|/*&n; *&t;page_buf_t:  Buffer structure for page cache-based buffers&n; *&n; * This buffer structure is used by the page cache buffer management routines&n; * to refer to an assembly of pages forming a logical buffer.  The actual&n; * I/O is performed with buffer_head or bio structures, as required by drivers,&n; * for drivers which do not understand this structure.  The buffer structure is&n; * used on temporary basis only, and discarded when released.&n; *&n; * The real data storage is recorded in the page cache.  Metadata is&n; * hashed to the inode for the block device on which the file system resides.&n; * File data is hashed to the inode for the file.  Pages which are only&n; * partially filled with data have bits set in their block_map entry&n; * to indicate which disk blocks in the page are not valid.&n; */
r_struct
id|page_buf_s
suffix:semicolon
DECL|typedef|page_buf_iodone_t
r_typedef
r_void
(paren
op_star
id|page_buf_iodone_t
)paren
(paren
r_struct
id|page_buf_s
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
id|page_buf_s
op_star
)paren
suffix:semicolon
multiline_comment|/* call-back function on I/O completion */
DECL|typedef|page_buf_bdstrat_t
r_typedef
r_int
(paren
op_star
id|page_buf_bdstrat_t
)paren
(paren
r_struct
id|page_buf_s
op_star
)paren
suffix:semicolon
DECL|macro|PB_PAGES
mdefine_line|#define PB_PAGES&t;4
DECL|struct|page_buf_s
r_typedef
r_struct
id|page_buf_s
(brace
DECL|member|pb_sema
r_struct
id|semaphore
id|pb_sema
suffix:semicolon
multiline_comment|/* semaphore for lockables  */
DECL|member|pb_flushtime
r_int
r_int
id|pb_flushtime
suffix:semicolon
multiline_comment|/* time to flush pagebuf    */
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
DECL|member|pb_target
r_struct
id|pb_target
op_star
id|pb_target
suffix:semicolon
multiline_comment|/* logical object */
DECL|member|pb_hold
id|atomic_t
id|pb_hold
suffix:semicolon
multiline_comment|/* reference count */
DECL|member|pb_bn
id|page_buf_daddr_t
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
DECL|member|pb_locked
r_int
r_char
id|pb_locked
suffix:semicolon
multiline_comment|/* page array is locked */
DECL|member|pb_hash_index
r_int
r_char
id|pb_hash_index
suffix:semicolon
multiline_comment|/* hash table index&t;*/
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
DECL|typedef|page_buf_t
)brace
id|page_buf_t
suffix:semicolon
multiline_comment|/* Finding and Reading Buffers */
r_extern
id|page_buf_t
op_star
id|pagebuf_find
c_func
(paren
multiline_comment|/* find buffer for block if&t;*/
multiline_comment|/* the block is in memory&t;*/
r_struct
id|pb_target
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
)paren
suffix:semicolon
multiline_comment|/* PBF_LOCK&t;&t;&t;*/
r_extern
id|page_buf_t
op_star
id|pagebuf_get
c_func
(paren
multiline_comment|/* allocate a buffer&t;&t;*/
r_struct
id|pb_target
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
r_extern
id|page_buf_t
op_star
id|pagebuf_lookup
c_func
(paren
r_struct
id|pb_target
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
multiline_comment|/* PBF_FORCEIO, _PBF_LOCKABLE&t;*/
r_extern
id|page_buf_t
op_star
id|pagebuf_get_empty
c_func
(paren
multiline_comment|/* allocate pagebuf struct with&t;*/
multiline_comment|/*  no memory or disk address&t;*/
r_int
id|len
comma
r_struct
id|pb_target
op_star
)paren
suffix:semicolon
multiline_comment|/* mount point &quot;fake&quot; inode&t;*/
r_extern
id|page_buf_t
op_star
id|pagebuf_get_no_daddr
c_func
(paren
multiline_comment|/* allocate pagebuf struct&t;*/
multiline_comment|/* without disk address&t;&t;*/
r_int
id|len
comma
r_struct
id|pb_target
op_star
)paren
suffix:semicolon
multiline_comment|/* mount point &quot;fake&quot; inode&t;*/
r_extern
r_int
id|pagebuf_associate_memory
c_func
(paren
id|page_buf_t
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
id|page_buf_t
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
r_struct
id|pb_target
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
op_star
comma
multiline_comment|/* buffer to mark&t;&t;*/
r_int
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
id|page_buf_t
op_star
comma
multiline_comment|/* buffer to start&t;&t;*/
id|page_buf_flags_t
)paren
suffix:semicolon
multiline_comment|/* PBF_LOCK, PBF_ASYNC,&t;&t;*/
multiline_comment|/* PBF_READ, PBF_WRITE,&t;&t;*/
multiline_comment|/* PBF_DELWRI, PBF_SYNC&t;&t;*/
r_extern
r_int
id|pagebuf_iorequest
c_func
(paren
multiline_comment|/* start real I/O&t;&t;*/
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
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
id|page_buf_t
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer to check&t;&t;*/
multiline_comment|/* Delayed Write Buffer Routines */
DECL|macro|PBDF_WAIT
mdefine_line|#define PBDF_WAIT    0x01
DECL|macro|PBDF_TRYLOCK
mdefine_line|#define PBDF_TRYLOCK 0x02
r_extern
r_void
id|pagebuf_delwri_flush
c_func
(paren
id|pb_target_t
op_star
comma
r_int
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pagebuf_delwri_dequeue
c_func
(paren
id|page_buf_t
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
macro_line|#endif /* __PAGE_BUF_H__ */
eof
