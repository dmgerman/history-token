multiline_comment|/*&n; * include/linux/writeback.h.&n; *&n; * These declarations are private to fs/ and mm/.&n; * Declarations which are exported to filesystems do not&n; * get placed here.&n; */
macro_line|#ifndef WRITEBACK_H
DECL|macro|WRITEBACK_H
mdefine_line|#define WRITEBACK_H
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
DECL|macro|WB_SYNC_NONE
mdefine_line|#define WB_SYNC_NONE&t;0&t;/* Don&squot;t wait on anything */
DECL|macro|WB_SYNC_LAST
mdefine_line|#define WB_SYNC_LAST&t;1&t;/* Wait on the last-written mapping */
DECL|macro|WB_SYNC_ALL
mdefine_line|#define WB_SYNC_ALL&t;2&t;/* Wait on every mapping */
DECL|macro|WB_SYNC_HOLD
mdefine_line|#define WB_SYNC_HOLD&t;3&t;/* Hold the inode on sb_dirty for sys_sync() */
r_void
id|writeback_unlocked_inodes
c_func
(paren
r_int
op_star
id|nr_to_write
comma
r_int
id|sync_mode
comma
r_int
r_int
op_star
id|older_than_this
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
r_void
id|balance_dirty_pages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
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
r_int
op_star
id|nr_to_write
)paren
suffix:semicolon
macro_line|#endif&t;&t;/* WRITEBACK_H */
eof
