multiline_comment|/*&n; * include/linux/writeback.h.&n; */
macro_line|#ifndef WRITEBACK_H
DECL|macro|WRITEBACK_H
mdefine_line|#define WRITEBACK_H
r_struct
id|backing_dev_info
suffix:semicolon
r_extern
id|spinlock_t
id|inode_lock
suffix:semicolon
r_extern
r_struct
id|list_head
id|inode_in_use
suffix:semicolon
r_extern
r_struct
id|list_head
id|inode_unused
suffix:semicolon
multiline_comment|/*&n; * Yes, writeback.h requires sched.h&n; * No, sched.h is not included from here.&n; */
DECL|function|current_is_pdflush
r_static
r_inline
r_int
id|current_is_pdflush
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;flags
op_amp
id|PF_FLUSHER
suffix:semicolon
)brace
multiline_comment|/*&n; * fs/fs-writeback.c&n; */
DECL|enum|writeback_sync_modes
r_enum
id|writeback_sync_modes
(brace
DECL|enumerator|WB_SYNC_NONE
id|WB_SYNC_NONE
comma
multiline_comment|/* Don&squot;t wait on anything */
DECL|enumerator|WB_SYNC_ALL
id|WB_SYNC_ALL
comma
multiline_comment|/* Wait on every mapping */
DECL|enumerator|WB_SYNC_HOLD
id|WB_SYNC_HOLD
comma
multiline_comment|/* Hold the inode on sb_dirty for sys_sync() */
)brace
suffix:semicolon
multiline_comment|/*&n; * A control structure which tells the writeback code what to do&n; */
DECL|struct|writeback_control
r_struct
id|writeback_control
(brace
DECL|member|bdi
r_struct
id|backing_dev_info
op_star
id|bdi
suffix:semicolon
multiline_comment|/* If !NULL, only write back this&n;&t;&t;&t;&t;&t;   queue */
DECL|member|sync_mode
r_enum
id|writeback_sync_modes
id|sync_mode
suffix:semicolon
DECL|member|older_than_this
r_int
r_int
op_star
id|older_than_this
suffix:semicolon
multiline_comment|/* If !NULL, only write back inodes&n;&t;&t;&t;&t;&t;   older than this */
DECL|member|nr_to_write
r_int
id|nr_to_write
suffix:semicolon
multiline_comment|/* Write this many pages, and decrement&n;&t;&t;&t;&t;&t;   this for each page written */
DECL|member|pages_skipped
r_int
id|pages_skipped
suffix:semicolon
multiline_comment|/* Pages which were not written */
DECL|member|nonblocking
r_int
id|nonblocking
suffix:semicolon
multiline_comment|/* Don&squot;t get stuck on request queues */
DECL|member|encountered_congestion
r_int
id|encountered_congestion
suffix:semicolon
multiline_comment|/* An output: a queue is full */
DECL|member|for_kupdate
r_int
id|for_kupdate
suffix:semicolon
multiline_comment|/* A kupdate writeback */
DECL|member|for_reclaim
r_int
id|for_reclaim
suffix:semicolon
multiline_comment|/* Invoked from the page allocator */
)brace
suffix:semicolon
multiline_comment|/*&n; * -&gt;writepage() return values (make these much larger than a pagesize, in&n; * case some fs is returning number-of-bytes-written from writepage)&n; */
DECL|macro|WRITEPAGE_ACTIVATE
mdefine_line|#define WRITEPAGE_ACTIVATE&t;0x80000&t;/* IO was not started: activate page */
multiline_comment|/*&n; * fs/fs-writeback.c&n; */
r_void
id|writeback_inodes
c_func
(paren
r_struct
id|writeback_control
op_star
id|wbc
)paren
suffix:semicolon
r_void
id|wake_up_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_void
id|__wait_on_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_void
id|sync_inodes_sb
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
id|wait
)paren
suffix:semicolon
r_void
id|sync_inodes
c_func
(paren
r_int
id|wait
)paren
suffix:semicolon
multiline_comment|/* writeback.h requires fs.h; it, too, is not included from here. */
DECL|function|wait_on_inode
r_static
r_inline
r_void
id|wait_on_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_state
op_amp
id|I_LOCK
)paren
id|__wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * mm/page-writeback.c&n; */
r_int
id|wakeup_bdflush
c_func
(paren
r_int
id|nr_pages
)paren
suffix:semicolon
r_void
id|laptop_io_completion
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|laptop_sync_completion
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* These are exported to sysctl. */
r_extern
r_int
id|dirty_background_ratio
suffix:semicolon
r_extern
r_int
id|vm_dirty_ratio
suffix:semicolon
r_extern
r_int
id|dirty_writeback_centisecs
suffix:semicolon
r_extern
r_int
id|dirty_expire_centisecs
suffix:semicolon
r_extern
r_int
id|block_dump
suffix:semicolon
r_extern
r_int
id|laptop_mode
suffix:semicolon
r_struct
id|ctl_table
suffix:semicolon
r_struct
id|file
suffix:semicolon
r_int
id|dirty_writeback_centisecs_handler
c_func
(paren
r_struct
id|ctl_table
op_star
comma
r_int
comma
r_struct
id|file
op_star
comma
r_void
id|__user
op_star
comma
r_int
op_star
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_void
id|page_writeback_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|balance_dirty_pages_ratelimited
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
)paren
suffix:semicolon
r_int
id|pdflush_operation
c_func
(paren
r_void
(paren
op_star
id|fn
)paren
(paren
r_int
r_int
)paren
comma
r_int
r_int
id|arg0
)paren
suffix:semicolon
r_int
id|do_writepages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|writeback_control
op_star
id|wbc
)paren
suffix:semicolon
multiline_comment|/* pdflush.c */
r_extern
r_int
id|nr_pdflush_threads
suffix:semicolon
multiline_comment|/* Global so it can be exported to sysctl&n;&t;&t;&t;&t;   read-only. */
macro_line|#endif&t;&t;/* WRITEBACK_H */
eof
