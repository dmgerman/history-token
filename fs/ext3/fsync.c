multiline_comment|/*&n; *  linux/fs/ext3/fsync.c&n; *&n; *  Copyright (C) 1993  Stephen Tweedie (sct@redhat.com)&n; *  from&n; *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)&n; *                      Laboratoire MASI - Institut Blaise Pascal&n; *                      Universite Pierre et Marie Curie (Paris VI)&n; *  from&n; *  linux/fs/minix/truncate.c   Copyright (C) 1991, 1992  Linus Torvalds&n; * &n; *  ext3fs fsync primitive&n; *&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; * &n; *  Removed unnecessary code duplication for little endian machines&n; *  and excessive __inline__s. &n; *        Andi Kleen, 1997&n; *&n; * Major simplications and cleanup - we only need to do the metadata, because&n; * we can depend on generic_block_fdatasync() to sync the data blocks.&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/ext3_fs.h&gt;
macro_line|#include &lt;linux/ext3_jbd.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/*&n; * akpm: A new design for ext3_sync_file().&n; *&n; * This is only called from sys_fsync(), sys_fdatasync() and sys_msync().&n; * There cannot be a transaction open by this task.&n; * Another task could have dirtied this inode.  Its data can be in any&n; * state in the journalling system.&n; *&n; * What we do is just kick off a commit and wait on it.  This will snapshot the&n; * inode to disk.&n; *&n; * Note that there is a serious optimisation we can make here: if the current&n; * inode is not part of j_running_transaction or j_committing_transaction&n; * then we have nothing to do.  That would require implementation of t_ilist,&n; * which isn&squot;t too hard.&n; */
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
multiline_comment|/*&n;&t; * data=writeback:&n;&t; *  The caller&squot;s filemap_fdatawrite()/wait will sync the data.&n;&t; *  ext3_force_commit() will sync the metadata&n;&t; *&n;&t; * data=ordered:&n;&t; *  The caller&squot;s filemap_fdatawrite() will write the data and&n;&t; *  ext3_force_commit() will wait on the buffers.  Then the caller&squot;s&n;&t; *  filemap_fdatawait() will wait on the pages (but all IO is complete)&n;&t; *  Not pretty, but it works.&n;&t; *&n;&t; * data=journal:&n;&t; *  filemap_fdatawrite won&squot;t do anything (the buffers are clean).&n;&t; *  ext3_force_commit will write the file data into the journal and&n;&t; *  will wait on that.&n;&t; *  filemap_fdatawait() will encounter a ton of newly-dirtied pages&n;&t; *  (they were dirtied by commit).  But that&squot;s OK - the blocks are&n;&t; *  safe in-journal, which is all fsync() needs to ensure.&n;&t; */
id|ext3_force_commit
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
