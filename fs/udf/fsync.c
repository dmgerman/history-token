multiline_comment|/*&n; * fsync.c&n; *&n; * PURPOSE&n; *  Fsync handling routines for the OSTA-UDF(tm) filesystem.&n; *&n; * CONTACTS&n; *  E-mail regarding any portion of the Linux UDF file system should be&n; *  directed to the development team mailing list (run by majordomo):&n; *      linux_udf@hpesjro.fc.hp.com&n; *&n; * COPYRIGHT&n; *  This file is distributed under the terms of the GNU General Public&n; *  License (GPL). Copies of the GPL can be obtained from:&n; *      ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *  Each contributing author retains all rights to their own work.&n; *&n; *  (C) 1999-2001 Ben Fennema&n; *  (C) 1999-2000 Stelias Computing Inc&n; *&n; * HISTORY&n; *&n; *  05/22/99 blf  Created.&n; */
macro_line|#include &quot;udfdecl.h&quot;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/*&n; *&t;File may be NULL when we are called. Perhaps we shouldn&squot;t&n; *&t;even pass file to fsync ?&n; */
DECL|function|udf_fsync_file
r_int
id|udf_fsync_file
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
r_return
id|udf_fsync_inode
c_func
(paren
id|inode
comma
id|datasync
)paren
suffix:semicolon
)brace
DECL|function|udf_fsync_inode
r_int
id|udf_fsync_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|datasync
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|fsync_inode_buffers
c_func
(paren
id|inode
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
id|udf_sync_inode
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
