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
r_void
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
r_void
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
r_void
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
r_void
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
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
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
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
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
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_QUOTAINIT
c_func
(paren
id|inode
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|drop
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* Ops must be set when there&squot;s any quota... */
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
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
id|lock_kernel
c_func
(paren
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
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
id|unlock_kernel
c_func
(paren
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
id|lock_kernel
c_func
(paren
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
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
id|unlock_kernel
c_func
(paren
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
id|lock_kernel
c_func
(paren
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
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
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
id|lock_kernel
c_func
(paren
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
id|unlock_kernel
c_func
(paren
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
id|lock_kernel
c_func
(paren
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
id|unlock_kernel
c_func
(paren
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
id|lock_kernel
c_func
(paren
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
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
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
id|unlock_kernel
c_func
(paren
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
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|inode_add_bytes
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
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
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|inode_add_bytes
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
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
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|inode_sub_bytes
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
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
