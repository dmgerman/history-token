multiline_comment|/* $Id: jffs2_fs_sb.h,v 1.25 2002/03/08 15:11:24 dwmw2 Exp $ */
macro_line|#ifndef _JFFS2_FS_SB
DECL|macro|_JFFS2_FS_SB
mdefine_line|#define _JFFS2_FS_SB
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/list.h&gt;
DECL|macro|INOCACHE_HASHSIZE
mdefine_line|#define INOCACHE_HASHSIZE 14
DECL|macro|JFFS2_SB_FLAG_RO
mdefine_line|#define JFFS2_SB_FLAG_RO 1
DECL|macro|JFFS2_SB_FLAG_MOUNTING
mdefine_line|#define JFFS2_SB_FLAG_MOUNTING 2
multiline_comment|/* A struct for the overall file system control.  Pointers to&n;   jffs2_sb_info structs are named `c&squot; in the source code.  &n;   Nee jffs_control&n;*/
DECL|struct|jffs2_sb_info
r_struct
id|jffs2_sb_info
(brace
DECL|member|mtd
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
DECL|member|highest_ino
r_uint32
id|highest_ino
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|gc_task
r_struct
id|task_struct
op_star
id|gc_task
suffix:semicolon
multiline_comment|/* GC task struct */
DECL|member|gc_thread_start
r_struct
id|semaphore
id|gc_thread_start
suffix:semicolon
multiline_comment|/* GC thread start mutex */
DECL|member|gc_thread_exit
r_struct
id|completion
id|gc_thread_exit
suffix:semicolon
multiline_comment|/* GC thread exit completion port */
DECL|member|alloc_sem
r_struct
id|semaphore
id|alloc_sem
suffix:semicolon
multiline_comment|/* Used to protect all the following &n;&t;&t;&t;&t;&t;   fields, and also to protect against&n;&t;&t;&t;&t;&t;   out-of-order writing of nodes.&n;&t;&t;&t;&t;&t;   And GC.&n;&t;&t;&t;&t;&t;*/
DECL|member|flash_size
r_uint32
id|flash_size
suffix:semicolon
DECL|member|used_size
r_uint32
id|used_size
suffix:semicolon
DECL|member|dirty_size
r_uint32
id|dirty_size
suffix:semicolon
DECL|member|free_size
r_uint32
id|free_size
suffix:semicolon
DECL|member|erasing_size
r_uint32
id|erasing_size
suffix:semicolon
DECL|member|bad_size
r_uint32
id|bad_size
suffix:semicolon
DECL|member|sector_size
r_uint32
id|sector_size
suffix:semicolon
DECL|member|nr_free_blocks
r_uint32
id|nr_free_blocks
suffix:semicolon
DECL|member|nr_erasing_blocks
r_uint32
id|nr_erasing_blocks
suffix:semicolon
DECL|member|nr_blocks
r_uint32
id|nr_blocks
suffix:semicolon
DECL|member|blocks
r_struct
id|jffs2_eraseblock
op_star
id|blocks
suffix:semicolon
multiline_comment|/* The whole array of blocks. Used for getting blocks &n;&t;&t;&t;&t;&t;&t; * from the offset (blocks[ofs / sector_size]) */
DECL|member|nextblock
r_struct
id|jffs2_eraseblock
op_star
id|nextblock
suffix:semicolon
multiline_comment|/* The block we&squot;re currently filling */
DECL|member|gcblock
r_struct
id|jffs2_eraseblock
op_star
id|gcblock
suffix:semicolon
multiline_comment|/* The block we&squot;re currently garbage-collecting */
DECL|member|clean_list
r_struct
id|list_head
id|clean_list
suffix:semicolon
multiline_comment|/* Blocks 100% full of clean data */
DECL|member|dirty_list
r_struct
id|list_head
id|dirty_list
suffix:semicolon
multiline_comment|/* Blocks with some dirty space */
DECL|member|erasable_list
r_struct
id|list_head
id|erasable_list
suffix:semicolon
multiline_comment|/* Blocks which are completely dirty, and need erasing */
DECL|member|erasable_pending_wbuf_list
r_struct
id|list_head
id|erasable_pending_wbuf_list
suffix:semicolon
multiline_comment|/* Blocks which need erasing but only after the current wbuf is flushed */
DECL|member|erasing_list
r_struct
id|list_head
id|erasing_list
suffix:semicolon
multiline_comment|/* Blocks which are currently erasing */
DECL|member|erase_pending_list
r_struct
id|list_head
id|erase_pending_list
suffix:semicolon
multiline_comment|/* Blocks which need erasing now */
DECL|member|erase_complete_list
r_struct
id|list_head
id|erase_complete_list
suffix:semicolon
multiline_comment|/* Blocks which are erased and need the clean marker written to them */
DECL|member|free_list
r_struct
id|list_head
id|free_list
suffix:semicolon
multiline_comment|/* Blocks which are free and ready to be used */
DECL|member|bad_list
r_struct
id|list_head
id|bad_list
suffix:semicolon
multiline_comment|/* Bad blocks. */
DECL|member|bad_used_list
r_struct
id|list_head
id|bad_used_list
suffix:semicolon
multiline_comment|/* Bad blocks with valid data in. */
DECL|member|erase_completion_lock
id|spinlock_t
id|erase_completion_lock
suffix:semicolon
multiline_comment|/* Protect free_list and erasing_list &n;&t;&t;&t;&t;&t;&t;   against erase completion handler */
DECL|member|erase_wait
id|wait_queue_head_t
id|erase_wait
suffix:semicolon
multiline_comment|/* For waiting for erases to complete */
DECL|member|inocache_list
r_struct
id|jffs2_inode_cache
op_star
id|inocache_list
(braket
id|INOCACHE_HASHSIZE
)braket
suffix:semicolon
DECL|member|inocache_lock
id|spinlock_t
id|inocache_lock
suffix:semicolon
multiline_comment|/* This _really_ speeds up mounts. */
DECL|member|inocache_last
r_struct
id|jffs2_inode_cache
op_star
id|inocache_last
suffix:semicolon
multiline_comment|/* Sem to allow jffs2_garbage_collect_deletion_dirent to&n;&t;   drop the erase_completion_lock while it&squot;s holding a pointer &n;&t;   to an obsoleted node. I don&squot;t like this. Alternatives welcomed. */
DECL|member|erase_free_sem
r_struct
id|semaphore
id|erase_free_sem
suffix:semicolon
multiline_comment|/* Write-behind buffer for NAND flash */
DECL|member|wbuf
r_int
r_char
op_star
id|wbuf
suffix:semicolon
DECL|member|wbuf_ofs
r_uint32
id|wbuf_ofs
suffix:semicolon
DECL|member|wbuf_len
r_uint32
id|wbuf_len
suffix:semicolon
DECL|member|wbuf_pagesize
r_uint32
id|wbuf_pagesize
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _JFFS2_FB_SB */
eof
