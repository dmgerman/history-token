multiline_comment|/*&n; *  linux/fs/ext2/fsync.c&n; *&n; *  Copyright (C) 1993  Stephen Tweedie (sct@dcs.ed.ac.uk)&n; *  from&n; *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)&n; *                      Laboratoire MASI - Institut Blaise Pascal&n; *                      Universite Pierre et Marie Curie (Paris VI)&n; *  from&n; *  linux/fs/minix/truncate.c   Copyright (C) 1991, 1992  Linus Torvalds&n; * &n; *  ext2fs fsync primitive&n; *&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; * &n; *  Removed unnecessary code duplication for little endian machines&n; *  and excessive __inline__s. &n; *        Andi Kleen, 1997&n; *&n; * Major simplications and cleanup - we only need to do the metadata, because&n; * we can depend on generic_block_fdatasync() to sync the data blocks.&n; */
macro_line|#include &quot;ext2.h&quot;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/*&n; *&t;File may be NULL when we are called. Perhaps we shouldn&squot;t&n; *&t;even pass file to fsync ?&n; */
DECL|function|ext2_sync_file
r_int
id|ext2_sync_file
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
id|err
suffix:semicolon
id|err
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
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY
)paren
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|datasync
op_logical_and
op_logical_neg
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY_DATASYNC
)paren
)paren
r_return
id|err
suffix:semicolon
id|err
op_or_assign
id|ext2_sync_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|err
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
