multiline_comment|/*&n; * fs/fs-writeback.c&n; *&n; * Copyright (C) 2002, Linus Torvalds.&n; *&n; * Contains all the functions related to writing back and waiting&n; * upon dirty inodes against superblocks, and writing back dirty&n; * pages against inodes.  ie: data writeback.  Writeout of the&n; * inode itself is not handled here.&n; *&n; * 10Apr2002&t;akpm@zip.com.au&n; *&t;&t;Split out of fs/inode.c&n; *&t;&t;Additions for address_space-based writeback&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
multiline_comment|/**&n; *&t;__mark_inode_dirty -&t;internal function&n; *&t;@inode: inode to mark&n; *&t;@flags: what kind of dirty (i.e. I_DIRTY_SYNC)&n; *&t;Mark an inode as dirty. Callers should use mark_inode_dirty or&n; *  &t;mark_inode_dirty_sync.&n; *&n; * Put the inode on the super block&squot;s dirty list.&n; *&n; * CAREFUL! We mark it dirty unconditionally, but move it onto the&n; * dirty list only if it is hashed or if it refers to a blockdev.&n; * If it was not hashed, it will never be added to the dirty list&n; * even if it is later hashed, as it will have been marked dirty already.&n; *&n; * In short, make sure you hash any inodes _before_ you start marking&n; * them dirty.&n; *&n; * This function *must* be atomic for the I_DIRTY_PAGES case -&n; * set_page_dirty() is called under spinlock in several places.&n; */
DECL|function|__mark_inode_dirty
r_void
id|__mark_inode_dirty
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|flags
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
r_return
suffix:semicolon
multiline_comment|/* swapper_space */
multiline_comment|/*&n;&t; * Don&squot;t do this for I_DIRTY_PAGES - that doesn&squot;t actually&n;&t; * dirty the inode itself&n;&t; */
r_if
c_cond
(paren
id|flags
op_amp
(paren
id|I_DIRTY_SYNC
op_or
id|I_DIRTY_DATASYNC
)paren
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;s_op
op_logical_and
id|sb-&gt;s_op-&gt;dirty_inode
)paren
id|sb-&gt;s_op
op_member_access_from_pointer
id|dirty_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/* avoid the locking if we can */
r_if
c_cond
(paren
(paren
id|inode-&gt;i_state
op_amp
id|flags
)paren
op_eq
id|flags
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inode-&gt;i_state
op_amp
id|flags
)paren
op_ne
id|flags
)paren
(brace
id|inode-&gt;i_state
op_or_assign
id|flags
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the inode is locked, just update its dirty state. &n;&t;&t; * The unlocker will place the inode on the appropriate&n;&t;&t; * superblock list, based upon its state.&n;&t;&t; */
r_if
c_cond
(paren
id|inode-&gt;i_state
op_amp
id|I_LOCK
)paren
r_goto
id|same_list
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Only add valid (hashed) inode to the superblock&squot;s&n;&t;&t; * dirty list.  Add blockdev inodes as well.&n;&t;&t; */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
op_logical_and
op_logical_neg
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_goto
id|same_list
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_mapping-&gt;dirtied_when
op_eq
l_int|0
)paren
id|inode-&gt;i_mapping-&gt;dirtied_when
op_assign
id|jiffies
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|inode-&gt;i_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|sb-&gt;s_dirty
)paren
suffix:semicolon
)brace
id|same_list
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
DECL|function|write_inode
r_static
r_inline
r_void
id|write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|sync
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;s_op
op_logical_and
id|inode-&gt;i_sb-&gt;s_op-&gt;write_inode
op_logical_and
op_logical_neg
id|is_bad_inode
c_func
(paren
id|inode
)paren
)paren
id|inode-&gt;i_sb-&gt;s_op
op_member_access_from_pointer
id|write_inode
c_func
(paren
id|inode
comma
id|sync
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write a single inode&squot;s dirty pages and inode data out to disk.&n; * If `sync&squot; is set, wait on the writeout.&n; * If `nr_to_write&squot; is not NULL, subtract the number of written pages&n; * from *nr_to_write.&n; *&n; * Normally it is not legal for a single process to lock more than one&n; * page at a time, due to ab/ba deadlock problems.  But writeback_mapping()&n; * does want to lock a large number of pages, without immediately submitting&n; * I/O against them (starting I/O is a &quot;deferred unlock_page&quot;).&n; *&n; * However it *is* legal to lock multiple pages, if this is only ever performed&n; * by a single process.  We provide that exclusion via locking in the&n; * filesystem&squot;s -&gt;writeback_mapping a_op. This ensures that only a single&n; * process is locking multiple pages against this inode.  And as I/O is&n; * submitted against all those locked pages, there is no deadlock.&n; *&n; * Called under inode_lock.&n; */
DECL|function|__sync_single_inode
r_static
r_void
id|__sync_single_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|wait
comma
r_int
op_star
id|nr_to_write
)paren
(brace
r_int
id|dirty
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|inode-&gt;i_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|inode-&gt;i_sb-&gt;s_locked_inodes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_state
op_amp
id|I_LOCK
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Set I_LOCK, reset I_DIRTY */
id|dirty
op_assign
id|inode-&gt;i_state
op_amp
id|I_DIRTY
suffix:semicolon
id|inode-&gt;i_state
op_or_assign
id|I_LOCK
suffix:semicolon
id|inode-&gt;i_state
op_and_assign
op_complement
id|I_DIRTY
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|filemap_fdatawait
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapping-&gt;a_ops-&gt;writeback_mapping
)paren
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|writeback_mapping
c_func
(paren
id|mapping
comma
id|nr_to_write
)paren
suffix:semicolon
r_else
id|generic_writeback_mapping
c_func
(paren
id|mapping
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t write the inode if only I_DIRTY_PAGES was set */
r_if
c_cond
(paren
id|dirty
op_amp
(paren
id|I_DIRTY_SYNC
op_or
id|I_DIRTY_DATASYNC
)paren
)paren
id|write_inode
c_func
(paren
id|inode
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|filemap_fdatawait
c_func
(paren
id|mapping
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * For non-blocking writeout (wait == 0), we still&n;&t; * count the inode as being clean.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Did we write back all the pages?&n;&t; */
r_if
c_cond
(paren
id|nr_to_write
op_logical_and
op_star
id|nr_to_write
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Maybe not&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|mapping-&gt;dirty_pages
)paren
)paren
multiline_comment|/* No lock needed */
id|inode-&gt;i_state
op_or_assign
id|I_DIRTY_PAGES
suffix:semicolon
)brace
id|inode-&gt;i_state
op_and_assign
op_complement
id|I_LOCK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_state
op_amp
id|I_FREEING
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|to
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY
)paren
id|to
op_assign
op_amp
id|inode-&gt;i_sb-&gt;s_dirty
suffix:semicolon
r_else
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
)paren
id|to
op_assign
op_amp
id|inode_in_use
suffix:semicolon
r_else
id|to
op_assign
op_amp
id|inode_unused
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|inode-&gt;i_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
id|to
)paren
suffix:semicolon
)brace
id|wake_up
c_func
(paren
op_amp
id|inode-&gt;i_wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write out an inode&squot;s dirty pages.  Called under inode_lock.&n; */
r_static
r_void
DECL|function|__writeback_single_inode
id|__writeback_single_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|sync
comma
r_int
op_star
id|nr_to_write
)paren
(brace
r_while
c_loop
(paren
id|inode-&gt;i_state
op_amp
id|I_LOCK
)paren
(brace
id|__iget
c_func
(paren
id|inode
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|__wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
id|__sync_single_inode
c_func
(paren
id|inode
comma
id|sync
comma
id|nr_to_write
)paren
suffix:semicolon
)brace
DECL|function|writeback_single_inode
r_void
id|writeback_single_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|sync
comma
r_int
op_star
id|nr_to_write
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|__writeback_single_inode
c_func
(paren
id|inode
comma
id|sync
comma
id|nr_to_write
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write out a list of inodes&squot; pages, and the inode itself.&n; *&n; * If `sync&squot; is true, wait on writeout of the last mapping&n; * which we write.&n; *&n; * If older_than_this is non-NULL, then only write out mappings which&n; * had their first dirtying at a time earlier than *older_than_this.&n; *&n; * Called under inode_lock.&n; *&n; * FIXME: putting all the inodes on a local list could introduce a&n; * race with umount.  Bump the superblock refcount?&n; */
DECL|function|__sync_list
r_static
r_void
id|__sync_list
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_int
id|sync_mode
comma
r_int
op_star
id|nr_to_write
comma
r_int
r_int
op_star
id|older_than_this
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
id|LIST_HEAD
c_func
(paren
id|hold
)paren
suffix:semicolon
multiline_comment|/* Unready inodes go here */
r_while
c_loop
(paren
(paren
id|tmp
op_assign
id|head-&gt;prev
)paren
op_ne
id|head
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inode
comma
id|i_list
)paren
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
r_int
id|really_sync
suffix:semicolon
r_if
c_cond
(paren
id|older_than_this
op_logical_and
op_star
id|older_than_this
)paren
(brace
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|mapping-&gt;dirtied_when
comma
op_star
id|older_than_this
)paren
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|inode-&gt;i_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|hold
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|really_sync
op_assign
(paren
id|sync_mode
op_eq
id|WB_SYNC_ALL
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sync_mode
op_eq
id|WB_SYNC_LAST
)paren
op_logical_and
(paren
id|head-&gt;prev
op_eq
id|head
)paren
)paren
id|really_sync
op_assign
l_int|1
suffix:semicolon
id|__writeback_single_inode
c_func
(paren
id|inode
comma
id|really_sync
comma
id|nr_to_write
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_to_write
op_logical_and
op_star
id|nr_to_write
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Put the not-ready inodes back&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|hold
)paren
)paren
id|list_splice
c_func
(paren
op_amp
id|hold
comma
id|head
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Start writeback of dirty pagecache data against all unlocked inodes.&n; *&n; * Note:&n; * We don&squot;t need to grab a reference to superblock here. If it has non-empty&n; * -&gt;s_dirty it&squot;s hadn&squot;t been killed yet and kill_super() won&squot;t proceed&n; * past sync_inodes_sb() until both -&gt;s_dirty and -&gt;s_locked_inodes are&n; * empty. Since __sync_single_inode() regains inode_lock before it finally moves&n; * inode from superblock lists we are OK.&n; *&n; * If `older_than_this&squot; is non-zero then only flush inodes which have a&n; * flushtime older than *older_than_this.  Unless *older_than_this is&n; * zero.  In which case we flush everything, like the old (dumb) wakeup_bdflush.&n; */
DECL|function|writeback_unlocked_inodes
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
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_static
r_int
r_int
id|writeback_gen
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We could get into livelock here if someone is dirtying&n;&t; * inodes fast enough.  writeback_gen is used to avoid that.&n;&t; */
id|writeback_gen
op_increment
suffix:semicolon
id|sb
op_assign
id|sb_entry
c_func
(paren
id|super_blocks.prev
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|sb
op_ne
id|sb_entry
c_func
(paren
op_amp
id|super_blocks
)paren
suffix:semicolon
id|sb
op_assign
id|sb_entry
c_func
(paren
id|sb-&gt;s_list.prev
)paren
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;s_writeback_gen
op_eq
id|writeback_gen
)paren
r_continue
suffix:semicolon
id|sb-&gt;s_writeback_gen
op_assign
id|writeback_gen
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_FLUSHER
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_FLUSHING
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * There&squot;s no point in two pdflush threads&n;&t;&t;&t;&t; * flushing the same device.  But for other&n;&t;&t;&t;&t; * callers, we want to perform the flush&n;&t;&t;&t;&t; * because the fdatasync is how we implement&n;&t;&t;&t;&t; * writer throttling.&n;&t;&t;&t;&t; */
r_continue
suffix:semicolon
)brace
id|sb-&gt;s_flags
op_or_assign
id|MS_FLUSHING
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|sb-&gt;s_dirty
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|__sync_list
c_func
(paren
op_amp
id|sb-&gt;s_dirty
comma
id|sync_mode
comma
id|nr_to_write
comma
id|older_than_this
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_FLUSHER
)paren
id|sb-&gt;s_flags
op_and_assign
op_complement
id|MS_FLUSHING
suffix:semicolon
r_if
c_cond
(paren
id|nr_to_write
op_logical_and
op_star
id|nr_to_write
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called under inode_lock&n; */
DECL|function|__try_to_writeback_unused_list
r_static
r_int
id|__try_to_writeback_unused_list
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_int
id|nr_inodes
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
op_assign
id|head
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_while
c_loop
(paren
id|nr_inodes
op_logical_and
(paren
id|tmp
op_assign
id|tmp-&gt;prev
)paren
op_ne
id|head
)paren
(brace
id|inode
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inode
comma
id|i_list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
)paren
(brace
id|__sync_single_inode
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|nr_inodes
op_decrement
suffix:semicolon
multiline_comment|/* &n;&t;&t;&t; * __sync_single_inode moved the inode to another list,&n;&t;&t;&t; * so we have to start looking from the list head.&n;&t;&t;&t; */
id|tmp
op_assign
id|head
suffix:semicolon
)brace
)brace
r_return
id|nr_inodes
suffix:semicolon
)brace
DECL|function|__wait_on_locked
r_static
r_void
id|__wait_on_locked
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_assign
id|head-&gt;prev
)paren
op_ne
id|head
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inode
comma
id|i_list
)paren
suffix:semicolon
id|__iget
c_func
(paren
id|inode
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|__wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * writeback and wait upon the filesystem&squot;s dirty inodes.&n; * We do it in two passes - one to write, and one to wait.&n; */
DECL|function|sync_inodes_sb
r_void
id|sync_inodes_sb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|sb-&gt;s_dirty
)paren
op_logical_or
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|sb-&gt;s_locked_inodes
)paren
)paren
(brace
id|__sync_list
c_func
(paren
op_amp
id|sb-&gt;s_dirty
comma
id|WB_SYNC_NONE
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|__sync_list
c_func
(paren
op_amp
id|sb-&gt;s_dirty
comma
id|WB_SYNC_ALL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|__wait_on_locked
c_func
(paren
op_amp
id|sb-&gt;s_locked_inodes
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * writeback the dirty inodes for this filesystem&n; */
DECL|function|writeback_inodes_sb
r_void
id|writeback_inodes_sb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|sb-&gt;s_dirty
)paren
)paren
id|__sync_list
c_func
(paren
op_amp
id|sb-&gt;s_dirty
comma
id|WB_SYNC_NONE
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Find a superblock with inodes that need to be synced&n; */
DECL|function|get_super_to_sync
r_static
r_struct
id|super_block
op_star
id|get_super_to_sync
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|restart
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|super_blocks
)paren
(brace
r_struct
id|super_block
op_star
id|s
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|super_block
comma
id|s_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|s-&gt;s_dirty
)paren
op_logical_and
id|list_empty
c_func
(paren
op_amp
id|s-&gt;s_locked_inodes
)paren
)paren
r_continue
suffix:semicolon
id|s-&gt;s_count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_root
)paren
(brace
id|drop_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sync_inodes&n; *&t;@dev: device to sync the inodes from.&n; *&n; *&t;sync_inodes goes through the super block&squot;s dirty list, &n; *&t;writes them out, waits on the writeout and puts the inodes&n; *&t;back on the normal list.&n; */
DECL|function|sync_inodes
r_void
id|sync_inodes
c_func
(paren
r_void
)paren
(brace
r_struct
id|super_block
op_star
id|s
suffix:semicolon
multiline_comment|/*&n;&t; * Search the super_blocks array for the device(s) to sync.&n;&t; */
r_while
c_loop
(paren
(paren
id|s
op_assign
id|get_super_to_sync
c_func
(paren
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|sync_inodes_sb
c_func
(paren
id|s
)paren
suffix:semicolon
id|drop_super
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
)brace
DECL|function|try_to_writeback_unused_inodes
r_void
id|try_to_writeback_unused_inodes
c_func
(paren
r_int
r_int
id|pexclusive
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
id|nr_inodes
op_assign
id|inodes_stat.nr_unused
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|sb
op_assign
id|sb_entry
c_func
(paren
id|super_blocks.next
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|nr_inodes
op_logical_and
id|sb
op_ne
id|sb_entry
c_func
(paren
op_amp
id|super_blocks
)paren
suffix:semicolon
id|sb
op_assign
id|sb_entry
c_func
(paren
id|sb-&gt;s_list.next
)paren
)paren
(brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|sb-&gt;s_dirty
)paren
)paren
r_continue
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|nr_inodes
op_assign
id|__try_to_writeback_unused_list
c_func
(paren
op_amp
id|sb-&gt;s_dirty
comma
id|nr_inodes
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
(paren
r_int
r_int
op_star
)paren
id|pexclusive
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;write_inode_now&t;-&t;write an inode to disk&n; *&t;@inode: inode to write to disk&n; *&t;@sync: whether the write should be synchronous or not&n; *&n; *&t;This function commits an inode to disk immediately if it is&n; *&t;dirty. This is primarily needed by knfsd.&n; */
DECL|function|write_inode_now
r_void
id|write_inode_now
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|sync
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|__writeback_single_inode
c_func
(paren
id|inode
comma
id|sync
comma
l_int|NULL
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sync
)paren
id|wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * generic_osync_inode - flush all dirty data for a given inode to disk&n; * @inode: inode to write&n; * @what:  what to write and wait upon&n; *&n; * This can be called by file_write functions for files which have the&n; * O_SYNC flag set, to flush dirty writes to disk.&n; *&n; * @what is a bitmask, specifying which part of the inode&squot;s data should be&n; * written and waited upon:&n; *&n; *    OSYNC_DATA:     i_mapping&squot;s dirty data&n; *    OSYNC_METADATA: the buffers at i_mapping-&gt;private_list&n; *    OSYNC_INODE:    the inode itself&n; */
DECL|function|generic_osync_inode
r_int
id|generic_osync_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|what
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|need_write_inode_now
op_assign
l_int|0
suffix:semicolon
r_int
id|err2
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|OSYNC_DATA
)paren
id|err
op_assign
id|filemap_fdatawrite
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
(paren
id|OSYNC_METADATA
op_or
id|OSYNC_DATA
)paren
)paren
(brace
id|err2
op_assign
id|sync_mapping_buffers
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|err2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|what
op_amp
id|OSYNC_DATA
)paren
(brace
id|err2
op_assign
id|filemap_fdatawait
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|err2
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY
)paren
op_logical_and
(paren
(paren
id|what
op_amp
id|OSYNC_INODE
)paren
op_logical_or
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY_DATASYNC
)paren
)paren
)paren
id|need_write_inode_now
op_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_write_inode_now
)paren
id|write_inode_now
c_func
(paren
id|inode
comma
l_int|1
)paren
suffix:semicolon
r_else
id|wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
