multiline_comment|/*&n; *  linux/fs/ext3/fsync.c&n; *&n; *  Copyright (C) 1993  Stephen Tweedie (sct@redhat.com)&n; *  from&n; *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)&n; *                      Laboratoire MASI - Institut Blaise Pascal&n; *                      Universite Pierre et Marie Curie (Paris VI)&n; *  from&n; *  linux/fs/minix/truncate.c   Copyright (C) 1991, 1992  Linus Torvalds&n; * &n; *  ext3fs fsync primitive&n; *&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; * &n; *  Removed unnecessary code duplication for little endian machines&n; *  and excessive __inline__s. &n; *        Andi Kleen, 1997&n; *&n; * Major simplications and cleanup - we only need to do the metadata, because&n; * we can depend on generic_block_fdatasync() to sync the data blocks.&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/ext3_fs.h&gt;
macro_line|#include &lt;linux/ext3_jbd.h&gt;
multiline_comment|/*&n; * akpm: A new design for ext3_sync_file().&n; *&n; * This is only called from sys_fsync(), sys_fdatasync() and sys_msync().&n; * There cannot be a transaction open by this task.&n; * Another task could have dirtied this inode.  Its data can be in any&n; * state in the journalling system.&n; *&n; * What we do is just kick off a commit and wait on it.  This will snapshot the&n; * inode to disk.&n; */
DECL|function|ext3_sync_file
r_int
id|ext3_sync_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|J_ASSERT
c_func
(paren
id|ext3_journal_current_handle
c_func
(paren
)paren
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * data=writeback:&n;&t; *  The caller&squot;s filemap_fdatawrite()/wait will sync the data.&n;&t; *  sync_inode() will sync the metadata&n;&t; *&n;&t; * data=ordered:&n;&t; *  The caller&squot;s filemap_fdatawrite() will write the data and&n;&t; *  sync_inode() will write the inode if it is dirty.  Then the caller&squot;s&n;&t; *  filemap_fdatawait() will wait on the pages.&n;&t; *&n;&t; * data=journal:&n;&t; *  filemap_fdatawrite won&squot;t do anything (the buffers are clean).&n;&t; *  ext3_force_commit will write the file data into the journal and&n;&t; *  will wait on that.&n;&t; *  filemap_fdatawait() will encounter a ton of newly-dirtied pages&n;&t; *  (they were dirtied by commit).  But that&squot;s OK - the blocks are&n;&t; *  safe in-journal, which is all fsync() needs to ensure.&n;&t; */
r_if
c_cond
(paren
id|ext3_should_journal_data
c_func
(paren
id|inode
)paren
)paren
(brace
id|ret
op_assign
id|ext3_force_commit
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The VFS has written the file data.  If the inode is unaltered&n;&t; * then we need not start a commit.&n;&t; */
r_if
c_cond
(paren
id|inode-&gt;i_state
op_amp
(paren
id|I_DIRTY_SYNC
op_or
id|I_DIRTY_DATASYNC
)paren
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
id|WB_SYNC_ALL
comma
dot
id|nr_to_write
op_assign
l_int|0
comma
multiline_comment|/* sys_fsync did this */
)brace
suffix:semicolon
id|ret
op_assign
id|sync_inode
c_func
(paren
id|inode
comma
op_amp
id|wbc
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
eof
