multiline_comment|/*&n; *  linux/fs/ext3/fsync.c&n; *&n; *  Copyright (C) 1993  Stephen Tweedie (sct@redhat.com)&n; *  from&n; *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)&n; *                      Laboratoire MASI - Institut Blaise Pascal&n; *                      Universite Pierre et Marie Curie (Paris VI)&n; *  from&n; *  linux/fs/minix/truncate.c   Copyright (C) 1991, 1992  Linus Torvalds&n; * &n; *  ext3fs fsync primitive&n; *&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; * &n; *  Removed unnecessary code duplication for little endian machines&n; *  and excessive __inline__s. &n; *        Andi Kleen, 1997&n; *&n; * Major simplications and cleanup - we only need to do the metadata, because&n; * we can depend on generic_block_fdatasync() to sync the data blocks.&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/ext3_fs.h&gt;
macro_line|#include &lt;linux/ext3_jbd.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/*&n; * akpm: A new design for ext3_sync_file().&n; *&n; * This is only called from sys_fsync(), sys_fdatasync() and sys_msync().&n; * There cannot be a transaction open by this task. (AKPM: quotas?)&n; * Another task could have dirtied this inode.  Its data can be in any&n; * state in the journalling system.&n; *&n; * What we do is just kick off a commit and wait on it.  This will snapshot the&n; * inode to disk.&n; *&n; * Note that there is a serious optimisation we can make here: if the current&n; * inode is not part of j_running_transaction or j_committing_transaction&n; * then we have nothing to do.  That would require implementation of t_ilist,&n; * which isn&squot;t too hard.&n; */
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
multiline_comment|/*&n;&t; * fsync_inode_buffers() just walks i_dirty_buffers and waits&n;&t; * on them.  It&squot;s a no-op for full data journalling because&n;&t; * i_dirty_buffers will be ampty.&n;&t; * Really, we only need to start I/O on the dirty buffers -&n;&t; * we&squot;ll end up waiting on them in commit.&n;&t; */
id|ret
op_assign
id|fsync_inode_buffers
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ext3_force_commit
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
