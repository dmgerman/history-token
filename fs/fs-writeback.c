multiline_comment|/*&n; * fs/fs-writeback.c&n; *&n; * Copyright (C) 2002, Linus Torvalds.&n; *&n; * Contains all the functions related to writing back and waiting&n; * upon dirty inodes against superblocks, and writing back dirty&n; * pages against inodes.  ie: data writeback.  Writeout of the&n; * inode itself is not handled here.&n; *&n; * 10Apr2002&t;akpm@zip.com.au&n; *&t;&t;Split out of fs/inode.c&n; *&t;&t;Additions for address_space-based writeback&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
r_extern
r_struct
id|super_block
op_star
id|blockdev_superblock
suffix:semicolon
multiline_comment|/**&n; *&t;__mark_inode_dirty -&t;internal function&n; *&t;@inode: inode to mark&n; *&t;@flags: what kind of dirty (i.e. I_DIRTY_SYNC)&n; *&t;Mark an inode as dirty. Callers should use mark_inode_dirty or&n; *  &t;mark_inode_dirty_sync.&n; *&n; * Put the inode on the super block&squot;s dirty list.&n; *&n; * CAREFUL! We mark it dirty unconditionally, but move it onto the&n; * dirty list only if it is hashed or if it refers to a blockdev.&n; * If it was not hashed, it will never be added to the dirty list&n; * even if it is later hashed, as it will have been marked dirty already.&n; *&n; * In short, make sure you hash any inodes _before_ you start marking&n; * them dirty.&n; *&n; * This function *must* be atomic for the I_DIRTY_PAGES case -&n; * set_page_dirty() is called under spinlock in several places.&n; *&n; * Note that for blockdevs, inode-&gt;dirtied_when represents the dirtying time of&n; * the block-special inode (/dev/hda1) itself.  And the -&gt;dirtied_when field of&n; * the kernel-internal blockdev inode represents the dirtying time of the&n; * blockdev&squot;s pages.  This is why for I_DIRTY_PAGES we always use&n; * page-&gt;mapping-&gt;host, so the page-dirtying time is recorded in the internal&n; * blockdev inode.&n; */
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
multiline_comment|/*&n;&t; * make sure that changes are seen by all cpus before we test i_state&n;&t; * -- mikulas&n;&t; */
id|smp_mb
c_func
(paren
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|block_dump
)paren
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
l_string|&quot;?&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|inode-&gt;i_dentry
)paren
)paren
(brace
id|dentry
op_assign
id|list_entry
c_func
(paren
id|inode-&gt;i_dentry.next
comma
r_struct
id|dentry
comma
id|d_alias
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry
op_logical_and
id|dentry-&gt;d_name.name
)paren
id|name
op_assign
(paren
r_const
r_char
op_star
)paren
id|dentry-&gt;d_name.name
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_logical_or
id|strcmp
c_func
(paren
id|inode-&gt;i_sb-&gt;s_id
comma
l_string|&quot;bdev&quot;
)paren
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s(%d): dirtied inode %lu (%s) on %s&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|inode-&gt;i_ino
comma
id|name
comma
id|inode-&gt;i_sb-&gt;s_id
)paren
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
id|flags
)paren
op_ne
id|flags
)paren
(brace
r_const
r_int
id|was_dirty
op_assign
id|inode-&gt;i_state
op_amp
id|I_DIRTY
suffix:semicolon
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
id|out
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Only add valid (hashed) inodes to the superblock&squot;s&n;&t;&t; * dirty list.  Add blockdev inodes as well.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|hlist_unhashed
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_state
op_amp
(paren
id|I_FREEING
op_or
id|I_CLEAR
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the inode was already on s_dirty or s_io, don&squot;t&n;&t;&t; * reposition it (that would break s_dirty time-ordering).&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|was_dirty
)paren
(brace
id|inode-&gt;dirtied_when
op_assign
id|jiffies
suffix:semicolon
id|list_move
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
)brace
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
DECL|variable|__mark_inode_dirty
id|EXPORT_SYMBOL
c_func
(paren
id|__mark_inode_dirty
)paren
suffix:semicolon
DECL|function|write_inode
r_static
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
multiline_comment|/*&n; * Write a single inode&squot;s dirty pages and inode data out to disk.&n; * If `wait&squot; is set, wait on the writeout.&n; *&n; * The whole writeout design is quite complex and fragile.  We want to avoid&n; * starvation of particular inodes when others are being redirtied, prevent&n; * livelocks, etc.&n; *&n; * Called under inode_lock.&n; */
r_static
r_int
DECL|function|__sync_single_inode
id|__sync_single_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|writeback_control
op_star
id|wbc
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
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
id|wait
op_assign
id|wbc-&gt;sync_mode
op_eq
id|WB_SYNC_ALL
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|BUG_ON
c_func
(paren
id|inode-&gt;i_state
op_amp
id|I_LOCK
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
id|ret
op_assign
id|do_writepages
c_func
(paren
id|mapping
comma
id|wbc
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
(brace
r_int
id|err
op_assign
id|filemap_fdatawait
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|err
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY
)paren
op_logical_and
id|mapping_tagged
c_func
(paren
id|mapping
comma
id|PAGECACHE_TAG_DIRTY
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We didn&squot;t write back all the pages.  nfs_writepages()&n;&t;&t;&t; * sometimes bales out without doing anything. Redirty&n;&t;&t;&t; * the inode.  It is still on sb-&gt;s_io.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|wbc-&gt;for_kupdate
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * For the kupdate function we leave the inode&n;&t;&t;&t;&t; * at the head of sb_dirty so it will get more&n;&t;&t;&t;&t; * writeout as soon as the queue becomes&n;&t;&t;&t;&t; * uncongested.&n;&t;&t;&t;&t; */
id|inode-&gt;i_state
op_or_assign
id|I_DIRTY_PAGES
suffix:semicolon
id|list_move_tail
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
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Otherwise fully redirty the inode so that&n;&t;&t;&t;&t; * other inodes on this superblock will get some&n;&t;&t;&t;&t; * writeout.  Otherwise heavy writing to one&n;&t;&t;&t;&t; * file would indefinitely suspend writeout of&n;&t;&t;&t;&t; * all the other files.&n;&t;&t;&t;&t; */
id|inode-&gt;i_state
op_or_assign
id|I_DIRTY_PAGES
suffix:semicolon
id|inode-&gt;dirtied_when
op_assign
id|jiffies
suffix:semicolon
id|list_move
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
)brace
r_else
r_if
c_cond
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Someone redirtied the inode while were writing back&n;&t;&t;&t; * the pages.&n;&t;&t;&t; */
id|list_move
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
(brace
multiline_comment|/*&n;&t;&t;&t; * The inode is clean, inuse&n;&t;&t;&t; */
id|list_move
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|inode_in_use
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * The inode is clean, unused&n;&t;&t;&t; */
id|list_move
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|inode_unused
)paren
suffix:semicolon
id|inodes_stat.nr_unused
op_increment
suffix:semicolon
)brace
)brace
id|wake_up_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Write out an inode&squot;s dirty pages.  Called under inode_lock.&n; */
r_static
r_int
DECL|function|__writeback_single_inode
id|__writeback_single_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|writeback_control
op_star
id|wbc
)paren
(brace
r_if
c_cond
(paren
(paren
id|wbc-&gt;sync_mode
op_ne
id|WB_SYNC_ALL
)paren
op_logical_and
(paren
id|inode-&gt;i_state
op_amp
id|I_LOCK
)paren
)paren
(brace
id|list_move
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|inode-&gt;i_sb-&gt;s_dirty
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * It&squot;s a data-integrity sync.  We must wait.&n;&t; */
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
r_return
id|__sync_single_inode
c_func
(paren
id|inode
comma
id|wbc
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write out a superblock&squot;s list of dirty inodes.  A wait will be performed&n; * upon no inodes, all inodes or the final one, depending upon sync_mode.&n; *&n; * If older_than_this is non-NULL, then only write out inodes which&n; * had their first dirtying at a time earlier than *older_than_this.&n; *&n; * If we&squot;re a pdlfush thread, then implement pdflush collision avoidance&n; * against the entire list.&n; *&n; * WB_SYNC_HOLD is a hack for sys_sync(): reattach the inode to sb-&gt;s_dirty so&n; * that it can be located for waiting on in __writeback_single_inode().&n; *&n; * Called under inode_lock.&n; *&n; * If `bdi&squot; is non-zero then we&squot;re being asked to writeback a specific queue.&n; * This function assumes that the blockdev superblock&squot;s inodes are backed by&n; * a variety of queues, so all inodes are searched.  For other superblocks,&n; * assume that all inodes are backed by the same queue.&n; *&n; * FIXME: this linear search could get expensive with many fileystems.  But&n; * how to fix?  We need to go from an address_space to all inodes which share&n; * a queue with that address_space.  (Easy: have a global &quot;dirty superblocks&quot;&n; * list).&n; *&n; * The inodes to be written are parked on sb-&gt;s_io.  They are moved back onto&n; * sb-&gt;s_dirty as they are selected for writing.  This way, none can be missed&n; * on the writer throttling path, and we get decent balancing between many&n; * throttled threads: we don&squot;t want them all piling up on __wait_on_inode.&n; */
r_static
r_void
DECL|function|sync_sb_inodes
id|sync_sb_inodes
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|writeback_control
op_star
id|wbc
)paren
(brace
r_const
r_int
r_int
id|start
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* livelock avoidance */
r_if
c_cond
(paren
op_logical_neg
id|wbc-&gt;for_kupdate
op_logical_or
id|list_empty
c_func
(paren
op_amp
id|sb-&gt;s_io
)paren
)paren
id|list_splice_init
c_func
(paren
op_amp
id|sb-&gt;s_dirty
comma
op_amp
id|sb-&gt;s_io
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
id|sb-&gt;s_io
)paren
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
id|sb-&gt;s_io.prev
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
r_struct
id|backing_dev_info
op_star
id|bdi
op_assign
id|mapping-&gt;backing_dev_info
suffix:semicolon
r_int
id|pages_skipped
suffix:semicolon
r_if
c_cond
(paren
id|bdi-&gt;memory_backed
)paren
(brace
id|list_move
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|sb-&gt;s_dirty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb
op_eq
id|blockdev_superblock
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Dirty memory-backed blockdev: the ramdisk&n;&t;&t;&t;&t; * driver does this.  Skip just this inode&n;&t;&t;&t;&t; */
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Dirty memory-backed inode against a filesystem other&n;&t;&t;&t; * than the kernel-internal bdev filesystem.  Skip the&n;&t;&t;&t; * entire superblock.&n;&t;&t;&t; */
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wbc-&gt;nonblocking
op_logical_and
id|bdi_write_congested
c_func
(paren
id|bdi
)paren
)paren
(brace
id|wbc-&gt;encountered_congestion
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sb
op_ne
id|blockdev_superblock
)paren
r_break
suffix:semicolon
multiline_comment|/* Skip a congested fs */
id|list_move
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|sb-&gt;s_dirty
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* Skip a congested blockdev */
)brace
r_if
c_cond
(paren
id|wbc-&gt;bdi
op_logical_and
id|bdi
op_ne
id|wbc-&gt;bdi
)paren
(brace
r_if
c_cond
(paren
id|sb
op_ne
id|blockdev_superblock
)paren
r_break
suffix:semicolon
multiline_comment|/* fs has the wrong queue */
id|list_move
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|sb-&gt;s_dirty
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* blockdev has wrong queue */
)brace
multiline_comment|/* Was this inode dirtied after sync_sb_inodes was called? */
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|inode-&gt;dirtied_when
comma
id|start
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* Was this inode dirtied too recently? */
r_if
c_cond
(paren
id|wbc-&gt;older_than_this
op_logical_and
id|time_after
c_func
(paren
id|inode-&gt;dirtied_when
comma
op_star
id|wbc-&gt;older_than_this
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* Is another pdflush already flushing this queue? */
r_if
c_cond
(paren
id|current_is_pdflush
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|writeback_acquire
c_func
(paren
id|bdi
)paren
)paren
r_break
suffix:semicolon
id|BUG_ON
c_func
(paren
id|inode-&gt;i_state
op_amp
id|I_FREEING
)paren
suffix:semicolon
id|__iget
c_func
(paren
id|inode
)paren
suffix:semicolon
id|pages_skipped
op_assign
id|wbc-&gt;pages_skipped
suffix:semicolon
id|__writeback_single_inode
c_func
(paren
id|inode
comma
id|wbc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wbc-&gt;sync_mode
op_eq
id|WB_SYNC_HOLD
)paren
(brace
id|inode-&gt;dirtied_when
op_assign
id|jiffies
suffix:semicolon
id|list_move
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
r_if
c_cond
(paren
id|current_is_pdflush
c_func
(paren
)paren
)paren
id|writeback_release
c_func
(paren
id|bdi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wbc-&gt;pages_skipped
op_ne
id|pages_skipped
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * writeback is not making progress due to locked&n;&t;&t;&t; * buffers.  Skip this inode for now.&n;&t;&t;&t; */
id|list_move
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
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
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
r_if
c_cond
(paren
id|wbc-&gt;nr_to_write
op_le
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_return
suffix:semicolon
multiline_comment|/* Leave any unwritten inodes on s_io */
)brace
multiline_comment|/*&n; * Start writeback of dirty pagecache data against all unlocked inodes.&n; *&n; * Note:&n; * We don&squot;t need to grab a reference to superblock here. If it has non-empty&n; * -&gt;s_dirty it&squot;s hadn&squot;t been killed yet and kill_super() won&squot;t proceed&n; * past sync_inodes_sb() until both the -&gt;s_dirty and -&gt;s_io lists are&n; * empty. Since __sync_single_inode() regains inode_lock before it finally moves&n; * inode from superblock lists we are OK.&n; *&n; * If `older_than_this&squot; is non-zero then only flush inodes which have a&n; * flushtime older than *older_than_this.&n; *&n; * If `bdi&squot; is non-zero then we will scan the first inode against each&n; * superblock until we find the matching ones.  One group will be the dirty&n; * inodes against a filesystem.  Then when we hit the dummy blockdev superblock,&n; * sync_sb_inodes will seekout the blockdev which matches `bdi&squot;.  Maybe not&n; * super-efficient but we&squot;re about to do a ton of I/O...&n; */
r_void
DECL|function|writeback_inodes
id|writeback_inodes
c_func
(paren
r_struct
id|writeback_control
op_star
id|wbc
)paren
(brace
r_struct
id|super_block
op_star
id|sb
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
id|restart
suffix:colon
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
id|sb-&gt;s_io
)paren
)paren
(brace
multiline_comment|/* we&squot;re making our own get_super here */
id|sb-&gt;s_count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If we can&squot;t get the readlock, there&squot;s no sense in&n;&t;&t;&t; * waiting around, most of the time the FS is going to&n;&t;&t;&t; * be unmounted by the time it is released.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|down_read_trylock
c_func
(paren
op_amp
id|sb-&gt;s_umount
)paren
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;s_root
)paren
id|sync_sb_inodes
c_func
(paren
id|sb
comma
id|wbc
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|sb-&gt;s_umount
)paren
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__put_super
c_func
(paren
id|sb
)paren
)paren
r_goto
id|restart
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wbc-&gt;nr_to_write
op_le
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
multiline_comment|/*&n; * writeback and wait upon the filesystem&squot;s dirty inodes.  The caller will&n; * do this in two passes - one to write, and one to wait.  WB_SYNC_HOLD is&n; * used to park the written inodes on sb-&gt;s_dirty for the wait pass.&n; *&n; * A finite limit is set on the number of pages which will be written.&n; * To prevent infinite livelock of sys_sync().&n; *&n; * We add in the number of potentially dirty inodes, because each inode write&n; * can dirty pagecache in the underlying blockdev.&n; */
DECL|function|sync_inodes_sb
r_void
id|sync_inodes_sb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|wait
)paren
(brace
r_struct
id|writeback_control
id|wbc
op_assign
(brace
dot
id|sync_mode
op_assign
id|wait
ques
c_cond
id|WB_SYNC_ALL
suffix:colon
id|WB_SYNC_HOLD
comma
)brace
suffix:semicolon
r_int
r_int
id|nr_dirty
op_assign
id|read_page_state
c_func
(paren
id|nr_dirty
)paren
suffix:semicolon
r_int
r_int
id|nr_unstable
op_assign
id|read_page_state
c_func
(paren
id|nr_unstable
)paren
suffix:semicolon
id|wbc.nr_to_write
op_assign
id|nr_dirty
op_plus
id|nr_unstable
op_plus
(paren
id|inodes_stat.nr_inodes
op_minus
id|inodes_stat.nr_unused
)paren
op_plus
id|nr_dirty
op_plus
id|nr_unstable
suffix:semicolon
id|wbc.nr_to_write
op_add_assign
id|wbc.nr_to_write
op_div
l_int|2
suffix:semicolon
multiline_comment|/* Bit more for luck */
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|sync_sb_inodes
c_func
(paren
id|sb
comma
op_amp
id|wbc
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
multiline_comment|/*&n; * Rather lame livelock avoidance.&n; */
DECL|function|set_sb_syncing
r_static
r_void
id|set_sb_syncing
c_func
(paren
r_int
id|val
)paren
(brace
r_struct
id|super_block
op_star
id|sb
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
id|sb-&gt;s_syncing
op_assign
id|val
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
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
id|super_block
op_star
id|sb
suffix:semicolon
id|restart
suffix:colon
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
id|sb-&gt;s_syncing
)paren
r_continue
suffix:semicolon
id|sb-&gt;s_syncing
op_assign
l_int|1
suffix:semicolon
id|sb-&gt;s_count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|sb-&gt;s_umount
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
)paren
(brace
id|drop_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
r_return
id|sb
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|sb_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * sync_inodes&n; *&n; * sync_inodes() goes through each super block&squot;s dirty inode list, writes the&n; * inodes out, waits on the writeout and puts the inodes back on the normal&n; * list.&n; *&n; * This is for sys_sync().  fsync_dev() uses the same algorithm.  The subtle&n; * part of the sync functions is that the blockdev &quot;superblock&quot; is processed&n; * last.  This is because the write_inode() function of a typical fs will&n; * perform no I/O, but will mark buffers in the blockdev mapping as dirty.&n; * What we want to do is to perform all that dirtying first, and then write&n; * back all those inode blocks via the blockdev mapping in one sweep.  So the&n; * additional (somewhat redundant) sync_blockdev() calls here are to make&n; * sure that really happens.  Because if we call sync_inodes_sb(wait=1) with&n; * outstanding dirty inodes, the writeback goes block-at-a-time within the&n; * filesystem&squot;s write_inode().  This is extremely slow.&n; */
DECL|function|sync_inodes
r_void
id|sync_inodes
c_func
(paren
r_int
id|wait
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
id|set_sb_syncing
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|sb
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
id|sb
comma
l_int|0
)paren
suffix:semicolon
id|sync_blockdev
c_func
(paren
id|sb-&gt;s_bdev
)paren
suffix:semicolon
id|drop_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wait
)paren
(brace
id|set_sb_syncing
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|sb
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
id|sb
comma
l_int|1
)paren
suffix:semicolon
id|sync_blockdev
c_func
(paren
id|sb-&gt;s_bdev
)paren
suffix:semicolon
id|drop_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
)brace
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
r_struct
id|writeback_control
id|wbc
op_assign
(brace
dot
id|nr_to_write
op_assign
id|LONG_MAX
comma
dot
id|sync_mode
op_assign
id|WB_SYNC_ALL
comma
)brace
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_mapping-&gt;backing_dev_info-&gt;memory_backed
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
id|__writeback_single_inode
c_func
(paren
id|inode
comma
op_amp
id|wbc
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
DECL|variable|write_inode_now
id|EXPORT_SYMBOL
c_func
(paren
id|write_inode_now
)paren
suffix:semicolon
multiline_comment|/**&n; * sync_inode - write an inode and its pages to disk.&n; * @inode: the inode to sync&n; * @wbc: controls the writeback mode&n; *&n; * sync_inode() will write an inode and its pages to disk.  It will also&n; * correctly update the inode on its superblock&squot;s dirty inode lists and will&n; * update inode-&gt;i_state.&n; *&n; * The caller must have a ref on the inode.&n; */
DECL|function|sync_inode
r_int
id|sync_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|writeback_control
op_star
id|wbc
)paren
(brace
r_int
id|ret
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|ret
op_assign
id|__writeback_single_inode
c_func
(paren
id|inode
comma
id|wbc
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
id|ret
suffix:semicolon
)brace
DECL|variable|sync_inode
id|EXPORT_SYMBOL
c_func
(paren
id|sync_inode
)paren
suffix:semicolon
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
r_struct
id|address_space
op_star
id|mapping
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
id|current-&gt;flags
op_or_assign
id|PF_SYNCWRITE
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
id|mapping
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
id|mapping
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
id|mapping
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
id|current-&gt;flags
op_and_assign
op_complement
id|PF_SYNCWRITE
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
DECL|variable|generic_osync_inode
id|EXPORT_SYMBOL
c_func
(paren
id|generic_osync_inode
)paren
suffix:semicolon
multiline_comment|/**&n; * writeback_acquire: attempt to get exclusive writeback access to a device&n; * @bdi: the device&squot;s backing_dev_info structure&n; *&n; * It is a waste of resources to have more than one pdflush thread blocked on&n; * a single request queue.  Exclusion at the request_queue level is obtained&n; * via a flag in the request_queue&squot;s backing_dev_info.state.&n; *&n; * Non-request_queue-backed address_spaces will share default_backing_dev_info,&n; * unless they implement their own.  Which is somewhat inefficient, as this&n; * may prevent concurrent writeback against multiple devices.&n; */
DECL|function|writeback_acquire
r_int
id|writeback_acquire
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
)paren
(brace
r_return
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|BDI_pdflush
comma
op_amp
id|bdi-&gt;state
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * writeback_in_progress: determine whether there is writeback in progress&n; *                        against a backing device.&n; * @bdi: the device&squot;s backing_dev_info structure.&n; */
DECL|function|writeback_in_progress
r_int
id|writeback_in_progress
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
)paren
(brace
r_return
id|test_bit
c_func
(paren
id|BDI_pdflush
comma
op_amp
id|bdi-&gt;state
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * writeback_release: relinquish exclusive writeback access against a device.&n; * @bdi: the device&squot;s backing_dev_info structure&n; */
DECL|function|writeback_release
r_void
id|writeback_release
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|writeback_in_progress
c_func
(paren
id|bdi
)paren
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|BDI_pdflush
comma
op_amp
id|bdi-&gt;state
)paren
suffix:semicolon
)brace
eof
