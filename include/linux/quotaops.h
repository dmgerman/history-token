multiline_comment|/*&n; * Definitions for diskquota-operations. When diskquota is configured these&n; * macros expand to the right source-code.&n; *&n; * Author:  Marco van Wieringen &lt;mvw@planets.elm.net&gt;&n; *&n; * Version: $Id: quotaops.h,v 1.2 1998/01/15 16:22:26 ecd Exp $&n; *&n; */
macro_line|#ifndef _LINUX_QUOTAOPS_
DECL|macro|_LINUX_QUOTAOPS_
mdefine_line|#define _LINUX_QUOTAOPS_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#if defined(CONFIG_QUOTA)
multiline_comment|/*&n; * declaration of quota_function calls in kernel.&n; */
r_extern
r_void
id|sync_dquots
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_int
id|dquot_initialize
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_int
id|dquot_drop
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
id|dquot_alloc_space
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|number
comma
r_int
id|prealloc
)paren
suffix:semicolon
r_extern
r_int
id|dquot_alloc_inode
c_func
(paren
r_const
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|number
)paren
suffix:semicolon
r_extern
r_int
id|dquot_free_space
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|number
)paren
suffix:semicolon
r_extern
r_int
id|dquot_free_inode
c_func
(paren
r_const
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|number
)paren
suffix:semicolon
r_extern
r_int
id|dquot_transfer
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|iattr
op_star
id|iattr
)paren
suffix:semicolon
r_extern
r_int
id|dquot_commit
c_func
(paren
r_struct
id|dquot
op_star
id|dquot
)paren
suffix:semicolon
r_extern
r_int
id|dquot_acquire
c_func
(paren
r_struct
id|dquot
op_star
id|dquot
)paren
suffix:semicolon
r_extern
r_int
id|dquot_release
c_func
(paren
r_struct
id|dquot
op_star
id|dquot
)paren
suffix:semicolon
r_extern
r_int
id|dquot_commit_info
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_int
id|dquot_mark_dquot_dirty
c_func
(paren
r_struct
id|dquot
op_star
id|dquot
)paren
suffix:semicolon
r_extern
r_int
id|vfs_quota_on
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
comma
r_int
id|format_id
comma
r_char
op_star
id|path
)paren
suffix:semicolon
r_extern
r_int
id|vfs_quota_on_mount
c_func
(paren
r_int
id|type
comma
r_int
id|format_id
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|vfs_quota_off
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
)paren
suffix:semicolon
DECL|macro|vfs_quota_off_mount
mdefine_line|#define vfs_quota_off_mount(sb, type) vfs_quota_off(sb, type)
r_extern
r_int
id|vfs_quota_sync
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_int
id|vfs_get_dqinfo
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
comma
r_struct
id|if_dqinfo
op_star
id|ii
)paren
suffix:semicolon
r_extern
r_int
id|vfs_set_dqinfo
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
comma
r_struct
id|if_dqinfo
op_star
id|ii
)paren
suffix:semicolon
r_extern
r_int
id|vfs_get_dqblk
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
comma
id|qid_t
id|id
comma
r_struct
id|if_dqblk
op_star
id|di
)paren
suffix:semicolon
r_extern
r_int
id|vfs_set_dqblk
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|type
comma
id|qid_t
id|id
comma
r_struct
id|if_dqblk
op_star
id|di
)paren
suffix:semicolon
multiline_comment|/*&n; * Operations supported for diskquotas.&n; */
r_extern
r_struct
id|dquot_operations
id|dquot_operations
suffix:semicolon
r_extern
r_struct
id|quotactl_ops
id|vfs_quotactl_ops
suffix:semicolon
DECL|macro|sb_dquot_ops
mdefine_line|#define sb_dquot_ops (&amp;dquot_operations)
DECL|macro|sb_quotactl_ops
mdefine_line|#define sb_quotactl_ops (&amp;vfs_quotactl_ops)
multiline_comment|/* It is better to call this function outside of any transaction as it might&n; * need a lot of space in journal for dquot structure allocation. */
DECL|function|DQUOT_INIT
r_static
id|__inline__
r_void
id|DQUOT_INIT
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb_any_quota_enabled
c_func
(paren
id|inode-&gt;i_sb
)paren
op_logical_and
op_logical_neg
id|IS_NOQUOTA
c_func
(paren
id|inode
)paren
)paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|initialize
c_func
(paren
id|inode
comma
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* The same as with DQUOT_INIT */
DECL|function|DQUOT_DROP
r_static
id|__inline__
r_void
id|DQUOT_DROP
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
multiline_comment|/* Here we can get arbitrary inode from clear_inode() so we have&n;&t; * to be careful. OTOH we don&squot;t need locking as quota operations&n;&t; * are allowed to change only at mount time */
r_if
c_cond
(paren
op_logical_neg
id|IS_NOQUOTA
c_func
(paren
id|inode
)paren
op_logical_and
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;dq_op
op_logical_and
id|inode-&gt;i_sb-&gt;dq_op-&gt;drop
)paren
(brace
r_int
id|cnt
suffix:semicolon
multiline_comment|/* Test before calling to rule out calls from proc and such&n;                 * where we are not allowed to block. Note that this is&n;&t;&t; * actually reliable test even without the lock - the caller&n;&t;&t; * must assure that nobody can come after the DQUOT_DROP and&n;&t;&t; * add quota pointers back anyway */
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|MAXQUOTAS
suffix:semicolon
id|cnt
op_increment
)paren
r_if
c_cond
(paren
id|inode-&gt;i_dquot
(braket
id|cnt
)braket
op_ne
id|NODQUOT
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OL
id|MAXQUOTAS
)paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|drop
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* The following allocation/freeing/transfer functions *must* be called inside&n; * a transaction (deadlocks possible otherwise) */
DECL|function|DQUOT_PREALLOC_SPACE_NODIRTY
r_static
id|__inline__
r_int
id|DQUOT_PREALLOC_SPACE_NODIRTY
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
r_if
c_cond
(paren
id|sb_any_quota_enabled
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
(brace
multiline_comment|/* Used space is updated in alloc_space() */
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|alloc_space
c_func
(paren
id|inode
comma
id|nr
comma
l_int|1
)paren
op_eq
id|NO_QUOTA
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
id|inode_add_bytes
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DQUOT_PREALLOC_SPACE
r_static
id|__inline__
r_int
id|DQUOT_PREALLOC_SPACE
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ret
op_assign
id|DQUOT_PREALLOC_SPACE_NODIRTY
c_func
(paren
id|inode
comma
id|nr
)paren
)paren
)paren
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|DQUOT_ALLOC_SPACE_NODIRTY
r_static
id|__inline__
r_int
id|DQUOT_ALLOC_SPACE_NODIRTY
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
r_if
c_cond
(paren
id|sb_any_quota_enabled
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
(brace
multiline_comment|/* Used space is updated in alloc_space() */
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|alloc_space
c_func
(paren
id|inode
comma
id|nr
comma
l_int|0
)paren
op_eq
id|NO_QUOTA
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
id|inode_add_bytes
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DQUOT_ALLOC_SPACE
r_static
id|__inline__
r_int
id|DQUOT_ALLOC_SPACE
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ret
op_assign
id|DQUOT_ALLOC_SPACE_NODIRTY
c_func
(paren
id|inode
comma
id|nr
)paren
)paren
)paren
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|DQUOT_ALLOC_INODE
r_static
id|__inline__
r_int
id|DQUOT_ALLOC_INODE
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
id|sb_any_quota_enabled
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
(brace
id|DQUOT_INIT
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|alloc_inode
c_func
(paren
id|inode
comma
l_int|1
)paren
op_eq
id|NO_QUOTA
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DQUOT_FREE_SPACE_NODIRTY
r_static
id|__inline__
r_void
id|DQUOT_FREE_SPACE_NODIRTY
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
r_if
c_cond
(paren
id|sb_any_quota_enabled
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|free_space
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
r_else
id|inode_sub_bytes
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
)brace
DECL|function|DQUOT_FREE_SPACE
r_static
id|__inline__
r_void
id|DQUOT_FREE_SPACE
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
id|DQUOT_FREE_SPACE_NODIRTY
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|DQUOT_FREE_INODE
r_static
id|__inline__
r_void
id|DQUOT_FREE_INODE
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
id|sb_any_quota_enabled
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|free_inode
c_func
(paren
id|inode
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|DQUOT_TRANSFER
r_static
id|__inline__
r_int
id|DQUOT_TRANSFER
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|iattr
op_star
id|iattr
)paren
(brace
r_if
c_cond
(paren
id|sb_any_quota_enabled
c_func
(paren
id|inode-&gt;i_sb
)paren
op_logical_and
op_logical_neg
id|IS_NOQUOTA
c_func
(paren
id|inode
)paren
)paren
(brace
id|DQUOT_INIT
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|transfer
c_func
(paren
id|inode
comma
id|iattr
)paren
op_eq
id|NO_QUOTA
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The following two functions cannot be called inside a transaction */
DECL|macro|DQUOT_SYNC
mdefine_line|#define DQUOT_SYNC(sb)&t;sync_dquots(sb, -1)
DECL|function|DQUOT_OFF
r_static
id|__inline__
r_int
id|DQUOT_OFF
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_if
c_cond
(paren
id|sb_any_quota_enabled
c_func
(paren
id|sb
)paren
op_logical_and
id|sb-&gt;s_qcop
op_logical_and
id|sb-&gt;s_qcop-&gt;quota_off
)paren
id|ret
op_assign
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|quota_off
c_func
(paren
id|sb
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * NO-OP when quota not configured.&n; */
DECL|macro|sb_dquot_ops
mdefine_line|#define sb_dquot_ops&t;&t;&t;&t;(NULL)
DECL|macro|sb_quotactl_ops
mdefine_line|#define sb_quotactl_ops&t;&t;&t;&t;(NULL)
DECL|macro|sync_dquots_dev
mdefine_line|#define sync_dquots_dev(dev,type)&t;&t;(NULL)
DECL|macro|DQUOT_INIT
mdefine_line|#define DQUOT_INIT(inode)&t;&t;&t;do { } while(0)
DECL|macro|DQUOT_DROP
mdefine_line|#define DQUOT_DROP(inode)&t;&t;&t;do { } while(0)
DECL|macro|DQUOT_ALLOC_INODE
mdefine_line|#define DQUOT_ALLOC_INODE(inode)&t;&t;(0)
DECL|macro|DQUOT_FREE_INODE
mdefine_line|#define DQUOT_FREE_INODE(inode)&t;&t;&t;do { } while(0)
DECL|macro|DQUOT_SYNC
mdefine_line|#define DQUOT_SYNC(sb)&t;&t;&t;&t;do { } while(0)
DECL|macro|DQUOT_OFF
mdefine_line|#define DQUOT_OFF(sb)&t;&t;&t;&t;do { } while(0)
DECL|macro|DQUOT_TRANSFER
mdefine_line|#define DQUOT_TRANSFER(inode, iattr)&t;&t;(0)
DECL|function|DQUOT_PREALLOC_SPACE_NODIRTY
r_extern
id|__inline__
r_int
id|DQUOT_PREALLOC_SPACE_NODIRTY
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
id|inode_add_bytes
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DQUOT_PREALLOC_SPACE
r_extern
id|__inline__
r_int
id|DQUOT_PREALLOC_SPACE
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
id|DQUOT_PREALLOC_SPACE_NODIRTY
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DQUOT_ALLOC_SPACE_NODIRTY
r_extern
id|__inline__
r_int
id|DQUOT_ALLOC_SPACE_NODIRTY
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
id|inode_add_bytes
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DQUOT_ALLOC_SPACE
r_extern
id|__inline__
r_int
id|DQUOT_ALLOC_SPACE
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
id|DQUOT_ALLOC_SPACE_NODIRTY
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DQUOT_FREE_SPACE_NODIRTY
r_extern
id|__inline__
r_void
id|DQUOT_FREE_SPACE_NODIRTY
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
id|inode_sub_bytes
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
)brace
DECL|function|DQUOT_FREE_SPACE
r_extern
id|__inline__
r_void
id|DQUOT_FREE_SPACE
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|qsize_t
id|nr
)paren
(brace
id|DQUOT_FREE_SPACE_NODIRTY
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_QUOTA */
DECL|macro|DQUOT_PREALLOC_BLOCK_NODIRTY
mdefine_line|#define DQUOT_PREALLOC_BLOCK_NODIRTY(inode, nr)&t;DQUOT_PREALLOC_SPACE_NODIRTY(inode, ((qsize_t)(nr)) &lt;&lt; (inode)-&gt;i_sb-&gt;s_blocksize_bits)
DECL|macro|DQUOT_PREALLOC_BLOCK
mdefine_line|#define DQUOT_PREALLOC_BLOCK(inode, nr)&t;DQUOT_PREALLOC_SPACE(inode, ((qsize_t)(nr)) &lt;&lt; (inode)-&gt;i_sb-&gt;s_blocksize_bits)
DECL|macro|DQUOT_ALLOC_BLOCK_NODIRTY
mdefine_line|#define DQUOT_ALLOC_BLOCK_NODIRTY(inode, nr) DQUOT_ALLOC_SPACE_NODIRTY(inode, ((qsize_t)(nr)) &lt;&lt; (inode)-&gt;i_sb-&gt;s_blocksize_bits)
DECL|macro|DQUOT_ALLOC_BLOCK
mdefine_line|#define DQUOT_ALLOC_BLOCK(inode, nr) DQUOT_ALLOC_SPACE(inode, ((qsize_t)(nr)) &lt;&lt; (inode)-&gt;i_sb-&gt;s_blocksize_bits)
DECL|macro|DQUOT_FREE_BLOCK_NODIRTY
mdefine_line|#define DQUOT_FREE_BLOCK_NODIRTY(inode, nr) DQUOT_FREE_SPACE_NODIRTY(inode, ((qsize_t)(nr)) &lt;&lt; (inode)-&gt;i_sb-&gt;s_blocksize_bits)
DECL|macro|DQUOT_FREE_BLOCK
mdefine_line|#define DQUOT_FREE_BLOCK(inode, nr) DQUOT_FREE_SPACE(inode, ((qsize_t)(nr)) &lt;&lt; (inode)-&gt;i_sb-&gt;s_blocksize_bits)
macro_line|#endif /* _LINUX_QUOTAOPS_ */
eof
