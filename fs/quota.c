multiline_comment|/*&n; * Quota code necessary even when VFS quota support is not compiled&n; * into the kernel.  The interesting stuff is over in dquot.c, here&n; * we have symbols for initial quotactl(2) handling, the sysctl(2)&n; * variables, etc - things needed even when quota support disabled.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
multiline_comment|/* Check validity of quotactl */
DECL|function|check_quotactl_valid
r_static
r_int
id|check_quotactl_valid
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
id|cmd
comma
id|qid_t
id|id
)paren
(brace
r_if
c_cond
(paren
id|type
op_ge
id|MAXQUOTAS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
op_logical_and
id|cmd
op_ne
id|Q_SYNC
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Is operation supported? */
r_if
c_cond
(paren
id|sb
op_logical_and
op_logical_neg
id|sb-&gt;s_qcop
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|Q_GETFMT
suffix:colon
r_break
suffix:semicolon
r_case
id|Q_QUOTAON
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_qcop-&gt;quota_on
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_QUOTAOFF
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_qcop-&gt;quota_off
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_SETINFO
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_qcop-&gt;set_info
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_GETINFO
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_qcop-&gt;get_info
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_SETQUOTA
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_qcop-&gt;set_dqblk
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_GETQUOTA
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_qcop-&gt;get_dqblk
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_SYNC
suffix:colon
r_if
c_cond
(paren
id|sb
op_logical_and
op_logical_neg
id|sb-&gt;s_qcop-&gt;quota_sync
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_XQUOTAON
suffix:colon
r_case
id|Q_XQUOTAOFF
suffix:colon
r_case
id|Q_XQUOTARM
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_qcop-&gt;set_xstate
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_XGETQSTAT
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_qcop-&gt;get_xstate
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_XSETQLIM
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_qcop-&gt;set_xquota
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_XGETQUOTA
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_qcop-&gt;get_xquota
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Is quota turned on for commands which need it? */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|Q_GETFMT
suffix:colon
r_case
id|Q_GETINFO
suffix:colon
r_case
id|Q_QUOTAOFF
suffix:colon
r_case
id|Q_SETINFO
suffix:colon
r_case
id|Q_SETQUOTA
suffix:colon
r_case
id|Q_GETQUOTA
suffix:colon
multiline_comment|/* This is just informative test so we are satisfied without a lock */
r_if
c_cond
(paren
op_logical_neg
id|sb_has_quota_enabled
c_func
(paren
id|sb
comma
id|type
)paren
)paren
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
multiline_comment|/* Check privileges */
r_if
c_cond
(paren
id|cmd
op_eq
id|Q_GETQUOTA
op_logical_or
id|cmd
op_eq
id|Q_XGETQUOTA
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|type
op_eq
id|USRQUOTA
op_logical_and
id|current-&gt;euid
op_ne
id|id
)paren
op_logical_or
(paren
id|type
op_eq
id|GRPQUOTA
op_logical_and
op_logical_neg
id|in_egroup_p
c_func
(paren
id|id
)paren
)paren
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd
op_ne
id|Q_GETFMT
op_logical_and
id|cmd
op_ne
id|Q_SYNC
op_logical_and
id|cmd
op_ne
id|Q_GETINFO
op_logical_and
id|cmd
op_ne
id|Q_XGETQSTAT
)paren
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
id|security_quotactl
(paren
id|cmd
comma
id|type
comma
id|id
comma
id|sb
)paren
suffix:semicolon
)brace
DECL|function|get_super_to_sync
r_static
r_struct
id|super_block
op_star
id|get_super_to_sync
c_func
(paren
r_int
id|type
)paren
(brace
r_struct
id|list_head
op_star
id|head
suffix:semicolon
r_int
id|cnt
comma
id|dirty
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
id|list_for_each
c_func
(paren
id|head
comma
op_amp
id|super_blocks
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|list_entry
c_func
(paren
id|head
comma
r_struct
id|super_block
comma
id|s_list
)paren
suffix:semicolon
multiline_comment|/* This test just improves performance so it needn&squot;t be reliable... */
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
comma
id|dirty
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
(paren
id|type
op_eq
id|cnt
op_logical_or
id|type
op_eq
op_minus
l_int|1
)paren
op_logical_and
id|sb_has_quota_enabled
c_func
(paren
id|sb
comma
id|cnt
)paren
op_logical_and
id|info_any_dirty
c_func
(paren
op_amp
id|sb_dqopt
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|info
(braket
id|cnt
)braket
)paren
)paren
id|dirty
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dirty
)paren
r_continue
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
DECL|function|quota_sync_sb
r_static
r_void
id|quota_sync_sb
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
(brace
r_int
id|cnt
suffix:semicolon
r_struct
id|inode
op_star
id|discard
(braket
id|MAXQUOTAS
)braket
suffix:semicolon
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|quota_sync
c_func
(paren
id|sb
comma
id|type
)paren
suffix:semicolon
multiline_comment|/* This is not very clever (and fast) but currently I don&squot;t know about&n;&t; * any other simple way of getting quota data to disk and we must get&n;&t; * them there for userspace to be visible... */
r_if
c_cond
(paren
id|sb-&gt;s_op-&gt;sync_fs
)paren
id|sb-&gt;s_op
op_member_access_from_pointer
id|sync_fs
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
multiline_comment|/* Now when everything is written we can discard the pagecache so&n;&t; * that userspace sees the changes. We need i_sem and so we could&n;&t; * not do it inside dqonoff_sem. Moreover we need to be carefull&n;&t; * about races with quotaoff() (that is the reason why we have own&n;&t; * reference to inode). */
id|down
c_func
(paren
op_amp
id|sb_dqopt
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dqonoff_sem
)paren
suffix:semicolon
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
(brace
id|discard
(braket
id|cnt
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
op_minus
l_int|1
op_logical_and
id|cnt
op_ne
id|type
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb_has_quota_enabled
c_func
(paren
id|sb
comma
id|cnt
)paren
)paren
r_continue
suffix:semicolon
id|discard
(braket
id|cnt
)braket
op_assign
id|igrab
c_func
(paren
id|sb_dqopt
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|files
(braket
id|cnt
)braket
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|sb_dqopt
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dqonoff_sem
)paren
suffix:semicolon
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
(brace
r_if
c_cond
(paren
id|discard
(braket
id|cnt
)braket
)paren
(brace
id|down
c_func
(paren
op_amp
id|discard
(braket
id|cnt
)braket
op_member_access_from_pointer
id|i_sem
)paren
suffix:semicolon
id|truncate_inode_pages
c_func
(paren
op_amp
id|discard
(braket
id|cnt
)braket
op_member_access_from_pointer
id|i_data
comma
l_int|0
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|discard
(braket
id|cnt
)braket
op_member_access_from_pointer
id|i_sem
)paren
suffix:semicolon
id|iput
c_func
(paren
id|discard
(braket
id|cnt
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|sync_dquots
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
(brace
r_if
c_cond
(paren
id|sb
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;s_qcop-&gt;quota_sync
)paren
id|quota_sync_sb
c_func
(paren
id|sb
comma
id|type
)paren
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
(paren
id|sb
op_assign
id|get_super_to_sync
c_func
(paren
id|type
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;s_qcop-&gt;quota_sync
)paren
id|quota_sync_sb
c_func
(paren
id|sb
comma
id|type
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
multiline_comment|/* Copy parameters and call proper function */
DECL|function|do_quotactl
r_static
r_int
id|do_quotactl
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
id|cmd
comma
id|qid_t
id|id
comma
r_void
id|__user
op_star
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|Q_QUOTAON
suffix:colon
(brace
r_char
op_star
id|pathname
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|pathname
op_assign
id|getname
c_func
(paren
id|addr
)paren
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|pathname
)paren
suffix:semicolon
id|ret
op_assign
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|quota_on
c_func
(paren
id|sb
comma
id|type
comma
id|id
comma
id|pathname
)paren
suffix:semicolon
id|putname
c_func
(paren
id|pathname
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_case
id|Q_QUOTAOFF
suffix:colon
r_return
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|quota_off
c_func
(paren
id|sb
comma
id|type
)paren
suffix:semicolon
r_case
id|Q_GETFMT
suffix:colon
(brace
id|__u32
id|fmt
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|sb_dqopt
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dqptr_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb_has_quota_enabled
c_func
(paren
id|sb
comma
id|type
)paren
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|sb_dqopt
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dqptr_sem
)paren
suffix:semicolon
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
id|fmt
op_assign
id|sb_dqopt
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|info
(braket
id|type
)braket
dot
id|dqi_format-&gt;qf_fmt_id
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|sb_dqopt
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dqptr_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|fmt
comma
r_sizeof
(paren
id|fmt
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|Q_GETINFO
suffix:colon
(brace
r_struct
id|if_dqinfo
id|info
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|get_info
c_func
(paren
id|sb
comma
id|type
comma
op_amp
id|info
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|Q_SETINFO
suffix:colon
(brace
r_struct
id|if_dqinfo
id|info
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|info
comma
id|addr
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|set_info
c_func
(paren
id|sb
comma
id|type
comma
op_amp
id|info
)paren
suffix:semicolon
)brace
r_case
id|Q_GETQUOTA
suffix:colon
(brace
r_struct
id|if_dqblk
id|idq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|get_dqblk
c_func
(paren
id|sb
comma
id|type
comma
id|id
comma
op_amp
id|idq
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|idq
comma
r_sizeof
(paren
id|idq
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|Q_SETQUOTA
suffix:colon
(brace
r_struct
id|if_dqblk
id|idq
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|idq
comma
id|addr
comma
r_sizeof
(paren
id|idq
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|set_dqblk
c_func
(paren
id|sb
comma
id|type
comma
id|id
comma
op_amp
id|idq
)paren
suffix:semicolon
)brace
r_case
id|Q_SYNC
suffix:colon
id|sync_dquots
c_func
(paren
id|sb
comma
id|type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|Q_XQUOTAON
suffix:colon
r_case
id|Q_XQUOTAOFF
suffix:colon
r_case
id|Q_XQUOTARM
suffix:colon
(brace
id|__u32
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|flags
comma
id|addr
comma
r_sizeof
(paren
id|flags
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|set_xstate
c_func
(paren
id|sb
comma
id|flags
comma
id|cmd
)paren
suffix:semicolon
)brace
r_case
id|Q_XGETQSTAT
suffix:colon
(brace
r_struct
id|fs_quota_stat
id|fqs
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|get_xstate
c_func
(paren
id|sb
comma
op_amp
id|fqs
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|fqs
comma
r_sizeof
(paren
id|fqs
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|Q_XSETQLIM
suffix:colon
(brace
r_struct
id|fs_disk_quota
id|fdq
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|fdq
comma
id|addr
comma
r_sizeof
(paren
id|fdq
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|set_xquota
c_func
(paren
id|sb
comma
id|type
comma
id|id
comma
op_amp
id|fdq
)paren
suffix:semicolon
)brace
r_case
id|Q_XGETQUOTA
suffix:colon
(brace
r_struct
id|fs_disk_quota
id|fdq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|sb-&gt;s_qcop
op_member_access_from_pointer
id|get_xquota
c_func
(paren
id|sb
comma
id|type
comma
id|id
comma
op_amp
id|fdq
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|fdq
comma
r_sizeof
(paren
id|fdq
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We never reach here unless validity check is broken */
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the system call interface. This communicates with&n; * the user-level programs. Currently this only supports diskquota&n; * calls. Maybe we need to add the process quotas etc. in the future,&n; * but we probably should use rlimits for that.&n; */
DECL|function|sys_quotactl
id|asmlinkage
r_int
id|sys_quotactl
c_func
(paren
r_int
r_int
id|cmd
comma
r_const
r_char
id|__user
op_star
id|special
comma
id|qid_t
id|id
comma
r_void
id|__user
op_star
id|addr
)paren
(brace
id|uint
id|cmds
comma
id|type
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|cmds
op_assign
id|cmd
op_rshift
id|SUBCMDSHIFT
suffix:semicolon
id|type
op_assign
id|cmd
op_amp
id|SUBCMDMASK
suffix:semicolon
r_if
c_cond
(paren
id|cmds
op_ne
id|Q_SYNC
op_logical_or
id|special
)paren
(brace
id|tmp
op_assign
id|getname
c_func
(paren
id|special
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|tmp
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|bdev
op_assign
id|lookup_bdev
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|putname
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|bdev
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|sb
op_assign
id|get_super
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|bdput
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|ret
op_assign
id|check_quotactl_valid
c_func
(paren
id|sb
comma
id|type
comma
id|cmds
comma
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
)paren
id|ret
op_assign
id|do_quotactl
c_func
(paren
id|sb
comma
id|type
comma
id|cmds
comma
id|id
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb
)paren
id|drop_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
