multiline_comment|/* -*- linux-c -*-&n; *&n; *&t;$Id: sysrq.c,v 1.15 1998/08/23 14:56:41 mj Exp $&n; *&n; *&t;Linux Magic System Request Key Hacks&n; *&n; *&t;(c) 1997 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; *&t;based on ideas by Pavel Machek &lt;pavel@atrey.karlin.mff.cuni.cz&gt;&n; *&n; *&t;(c) 2000 Crutcher Dunnavant &lt;crutcher+kernel@datastacks.com&gt;&n; *&t;overhauled to use key registration&n; *&t;based upon discusions in irc://irc.openprojects.net/#kernelnewbies&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/kbd_kern.h&gt;
macro_line|#include &lt;linux/quotaops.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;&t;&t;/* for fsync_bdev() */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
r_extern
r_void
id|reset_vc
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|list_head
id|super_blocks
suffix:semicolon
multiline_comment|/* Whether we react on sysrq keys or just ignore them */
DECL|variable|sysrq_enabled
r_int
id|sysrq_enabled
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Machine specific power off function */
DECL|variable|sysrq_power_off
r_void
(paren
op_star
id|sysrq_power_off
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Loglevel sysrq handler */
DECL|function|sysrq_handle_loglevel
r_static
r_void
id|sysrq_handle_loglevel
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_int
id|i
suffix:semicolon
id|i
op_assign
id|key
op_minus
l_char|&squot;0&squot;
suffix:semicolon
id|console_loglevel
op_assign
l_int|7
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Loglevel set to %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|console_loglevel
op_assign
id|i
suffix:semicolon
)brace
DECL|variable|sysrq_loglevel_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_loglevel_op
op_assign
(brace
id|handler
suffix:colon
id|sysrq_handle_loglevel
comma
id|help_msg
suffix:colon
l_string|&quot;loglevel0-8&quot;
comma
id|action_msg
suffix:colon
l_string|&quot;Changing Loglevel&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* SAK sysrq handler */
macro_line|#ifdef CONFIG_VT
DECL|function|sysrq_handle_SAK
r_static
r_void
id|sysrq_handle_SAK
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_if
c_cond
(paren
id|tty
)paren
id|do_SAK
c_func
(paren
id|tty
)paren
suffix:semicolon
id|reset_vc
c_func
(paren
id|fg_console
)paren
suffix:semicolon
)brace
DECL|variable|sysrq_SAK_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_SAK_op
op_assign
(brace
id|handler
suffix:colon
id|sysrq_handle_SAK
comma
id|help_msg
suffix:colon
l_string|&quot;saK&quot;
comma
id|action_msg
suffix:colon
l_string|&quot;SAK&quot;
comma
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
multiline_comment|/* unraw sysrq handler */
DECL|function|sysrq_handle_unraw
r_static
r_void
id|sysrq_handle_unraw
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|kbd_struct
op_star
id|kbd
op_assign
op_amp
id|kbd_table
(braket
id|fg_console
)braket
suffix:semicolon
r_if
c_cond
(paren
id|kbd
)paren
id|kbd-&gt;kbdmode
op_assign
id|VC_XLATE
suffix:semicolon
)brace
DECL|variable|sysrq_unraw_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_unraw_op
op_assign
(brace
id|handler
suffix:colon
id|sysrq_handle_unraw
comma
id|help_msg
suffix:colon
l_string|&quot;unRaw&quot;
comma
id|action_msg
suffix:colon
l_string|&quot;Keyboard mode set to XLATE&quot;
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_VT */
multiline_comment|/* reboot sysrq handler */
DECL|function|sysrq_handle_reboot
r_static
r_void
id|sysrq_handle_reboot
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|machine_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|sysrq_reboot_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_reboot_op
op_assign
(brace
id|handler
suffix:colon
id|sysrq_handle_reboot
comma
id|help_msg
suffix:colon
l_string|&quot;reBoot&quot;
comma
id|action_msg
suffix:colon
l_string|&quot;Resetting&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* SYNC SYSRQ HANDLERS BLOCK */
multiline_comment|/* do_emergency_sync helper function */
multiline_comment|/* Guesses if the device is a local hard drive */
DECL|function|is_local_disk
r_static
r_int
id|is_local_disk
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_switch
c_cond
(paren
id|MAJOR
c_func
(paren
id|bdev-&gt;bd_dev
)paren
)paren
(brace
r_case
id|IDE0_MAJOR
suffix:colon
r_case
id|IDE1_MAJOR
suffix:colon
r_case
id|IDE2_MAJOR
suffix:colon
r_case
id|IDE3_MAJOR
suffix:colon
r_case
id|IDE4_MAJOR
suffix:colon
r_case
id|IDE5_MAJOR
suffix:colon
r_case
id|IDE6_MAJOR
suffix:colon
r_case
id|IDE7_MAJOR
suffix:colon
r_case
id|IDE8_MAJOR
suffix:colon
r_case
id|IDE9_MAJOR
suffix:colon
r_case
id|SCSI_DISK0_MAJOR
suffix:colon
r_case
id|SCSI_DISK1_MAJOR
suffix:colon
r_case
id|SCSI_DISK2_MAJOR
suffix:colon
r_case
id|SCSI_DISK3_MAJOR
suffix:colon
r_case
id|SCSI_DISK4_MAJOR
suffix:colon
r_case
id|SCSI_DISK5_MAJOR
suffix:colon
r_case
id|SCSI_DISK6_MAJOR
suffix:colon
r_case
id|SCSI_DISK7_MAJOR
suffix:colon
r_case
id|XT_DISK_MAJOR
suffix:colon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* do_emergency_sync helper function */
DECL|function|go_sync
r_static
r_void
id|go_sync
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|remount_flag
)paren
(brace
r_int
id|orig_loglevel
suffix:semicolon
id|orig_loglevel
op_assign
id|console_loglevel
suffix:semicolon
id|console_loglevel
op_assign
l_int|7
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%sing device %s ... &quot;
comma
id|remount_flag
ques
c_cond
l_string|&quot;Remount&quot;
suffix:colon
l_string|&quot;Sync&quot;
comma
id|sb-&gt;s_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remount_flag
)paren
(brace
multiline_comment|/* Remount R/O */
r_int
id|ret
comma
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;R/O&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|file_list_lock
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|sb-&gt;s_files.next
suffix:semicolon
id|p
op_ne
op_amp
id|sb-&gt;s_files
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|file
comma
id|f_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_dentry
op_logical_and
id|file_count
c_func
(paren
id|file
)paren
op_logical_and
id|S_ISREG
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
id|file-&gt;f_mode
op_and_assign
op_complement
l_int|2
suffix:semicolon
)brace
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
id|DQUOT_OFF
c_func
(paren
id|sb
)paren
suffix:semicolon
id|fsync_bdev
c_func
(paren
id|sb-&gt;s_bdev
)paren
suffix:semicolon
id|flags
op_assign
id|MS_RDONLY
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_op
op_logical_and
id|sb-&gt;s_op-&gt;remount_fs
)paren
(brace
id|ret
op_assign
id|sb-&gt;s_op
op_member_access_from_pointer
id|remount_fs
c_func
(paren
id|sb
comma
op_amp
id|flags
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|printk
c_func
(paren
l_string|&quot;error %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_else
(brace
id|sb-&gt;s_flags
op_assign
(paren
id|sb-&gt;s_flags
op_amp
op_complement
id|MS_RMT_MASK
)paren
op_or
(paren
id|flags
op_amp
id|MS_RMT_MASK
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;OK&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;nothing to do&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Sync only */
id|fsync_bdev
c_func
(paren
id|sb-&gt;s_bdev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;OK&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|console_loglevel
op_assign
id|orig_loglevel
suffix:semicolon
)brace
multiline_comment|/*&n; * Emergency Sync or Unmount. We cannot do it directly, so we set a special&n; * flag and wake up the bdflush kernel thread which immediately calls this function.&n; * We process all mounted hard drives first to recover from crashed experimental&n; * block devices and malfunctional network filesystems.&n; */
DECL|variable|emergency_sync_scheduled
r_int
id|emergency_sync_scheduled
suffix:semicolon
DECL|function|do_emergency_sync
r_void
id|do_emergency_sync
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
r_int
id|remount_flag
suffix:semicolon
r_int
id|orig_loglevel
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|remount_flag
op_assign
(paren
id|emergency_sync_scheduled
op_eq
id|EMERG_REMOUNT
)paren
suffix:semicolon
id|emergency_sync_scheduled
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|sb
op_assign
id|sb_entry
c_func
(paren
id|super_blocks.next
)paren
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
id|sb-&gt;s_list.next
)paren
)paren
r_if
c_cond
(paren
id|sb-&gt;s_bdev
op_logical_and
id|is_local_disk
c_func
(paren
id|sb-&gt;s_bdev
)paren
)paren
id|go_sync
c_func
(paren
id|sb
comma
id|remount_flag
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sb
op_assign
id|sb_entry
c_func
(paren
id|super_blocks.next
)paren
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
id|sb-&gt;s_list.next
)paren
)paren
r_if
c_cond
(paren
id|sb-&gt;s_bdev
op_logical_and
op_logical_neg
id|is_local_disk
c_func
(paren
id|sb-&gt;s_bdev
)paren
)paren
id|go_sync
c_func
(paren
id|sb
comma
id|remount_flag
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|orig_loglevel
op_assign
id|console_loglevel
suffix:semicolon
id|console_loglevel
op_assign
l_int|7
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Done.&bslash;n&quot;
)paren
suffix:semicolon
id|console_loglevel
op_assign
id|orig_loglevel
suffix:semicolon
)brace
DECL|function|sysrq_handle_sync
r_static
r_void
id|sysrq_handle_sync
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|emergency_sync_scheduled
op_assign
id|EMERG_SYNC
suffix:semicolon
id|wakeup_bdflush
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|sysrq_sync_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_sync_op
op_assign
(brace
id|handler
suffix:colon
id|sysrq_handle_sync
comma
id|help_msg
suffix:colon
l_string|&quot;Sync&quot;
comma
id|action_msg
suffix:colon
l_string|&quot;Emergency Sync&quot;
comma
)brace
suffix:semicolon
DECL|function|sysrq_handle_mountro
r_static
r_void
id|sysrq_handle_mountro
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|emergency_sync_scheduled
op_assign
id|EMERG_REMOUNT
suffix:semicolon
id|wakeup_bdflush
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|sysrq_mountro_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_mountro_op
op_assign
(brace
id|handler
suffix:colon
id|sysrq_handle_mountro
comma
id|help_msg
suffix:colon
l_string|&quot;Unmount&quot;
comma
id|action_msg
suffix:colon
l_string|&quot;Emergency Remount R/O&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* END SYNC SYSRQ HANDLERS BLOCK */
multiline_comment|/* SHOW SYSRQ HANDLERS BLOCK */
DECL|function|sysrq_handle_showregs
r_static
r_void
id|sysrq_handle_showregs
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_if
c_cond
(paren
id|pt_regs
)paren
id|show_regs
c_func
(paren
id|pt_regs
)paren
suffix:semicolon
)brace
DECL|variable|sysrq_showregs_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_showregs_op
op_assign
(brace
id|handler
suffix:colon
id|sysrq_handle_showregs
comma
id|help_msg
suffix:colon
l_string|&quot;showPc&quot;
comma
id|action_msg
suffix:colon
l_string|&quot;Show Regs&quot;
comma
)brace
suffix:semicolon
DECL|function|sysrq_handle_showstate
r_static
r_void
id|sysrq_handle_showstate
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|show_state
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|sysrq_showstate_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_showstate_op
op_assign
(brace
id|handler
suffix:colon
id|sysrq_handle_showstate
comma
id|help_msg
suffix:colon
l_string|&quot;showTasks&quot;
comma
id|action_msg
suffix:colon
l_string|&quot;Show State&quot;
comma
)brace
suffix:semicolon
DECL|function|sysrq_handle_showmem
r_static
r_void
id|sysrq_handle_showmem
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|show_mem
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|sysrq_showmem_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_showmem_op
op_assign
(brace
id|handler
suffix:colon
id|sysrq_handle_showmem
comma
id|help_msg
suffix:colon
l_string|&quot;showMem&quot;
comma
id|action_msg
suffix:colon
l_string|&quot;Show Memory&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* SHOW SYSRQ HANDLERS BLOCK */
multiline_comment|/* SIGNAL SYSRQ HANDLERS BLOCK */
multiline_comment|/* signal sysrq helper function&n; * Sends a signal to all user processes */
DECL|function|send_sig_all
r_static
r_void
id|send_sig_all
c_func
(paren
r_int
id|sig
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|for_each_process
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;mm
op_logical_and
id|p-&gt;pid
op_ne
l_int|1
)paren
multiline_comment|/* Not swapper, init nor kernel thread */
id|force_sig
c_func
(paren
id|sig
comma
id|p
)paren
suffix:semicolon
)brace
)brace
DECL|function|sysrq_handle_term
r_static
r_void
id|sysrq_handle_term
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|send_sig_all
c_func
(paren
id|SIGTERM
)paren
suffix:semicolon
id|console_loglevel
op_assign
l_int|8
suffix:semicolon
)brace
DECL|variable|sysrq_term_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_term_op
op_assign
(brace
id|handler
suffix:colon
id|sysrq_handle_term
comma
id|help_msg
suffix:colon
l_string|&quot;tErm&quot;
comma
id|action_msg
suffix:colon
l_string|&quot;Terminate All Tasks&quot;
comma
)brace
suffix:semicolon
DECL|function|sysrq_handle_kill
r_static
r_void
id|sysrq_handle_kill
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|send_sig_all
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
id|console_loglevel
op_assign
l_int|8
suffix:semicolon
)brace
DECL|variable|sysrq_kill_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_kill_op
op_assign
(brace
id|handler
suffix:colon
id|sysrq_handle_kill
comma
id|help_msg
suffix:colon
l_string|&quot;kIll&quot;
comma
id|action_msg
suffix:colon
l_string|&quot;Kill All Tasks&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* END SIGNAL SYSRQ HANDLERS BLOCK */
multiline_comment|/* Key Operations table and lock */
DECL|variable|sysrq_key_table_lock
r_static
id|spinlock_t
id|sysrq_key_table_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|SYSRQ_KEY_TABLE_LENGTH
mdefine_line|#define SYSRQ_KEY_TABLE_LENGTH 36
DECL|variable|sysrq_key_table
r_static
r_struct
id|sysrq_key_op
op_star
id|sysrq_key_table
(braket
id|SYSRQ_KEY_TABLE_LENGTH
)braket
op_assign
(brace
multiline_comment|/* 0 */
op_amp
id|sysrq_loglevel_op
comma
multiline_comment|/* 1 */
op_amp
id|sysrq_loglevel_op
comma
multiline_comment|/* 2 */
op_amp
id|sysrq_loglevel_op
comma
multiline_comment|/* 3 */
op_amp
id|sysrq_loglevel_op
comma
multiline_comment|/* 4 */
op_amp
id|sysrq_loglevel_op
comma
multiline_comment|/* 5 */
op_amp
id|sysrq_loglevel_op
comma
multiline_comment|/* 6 */
op_amp
id|sysrq_loglevel_op
comma
multiline_comment|/* 7 */
op_amp
id|sysrq_loglevel_op
comma
multiline_comment|/* 8 */
op_amp
id|sysrq_loglevel_op
comma
multiline_comment|/* 9 */
op_amp
id|sysrq_loglevel_op
comma
multiline_comment|/* a */
l_int|NULL
comma
multiline_comment|/* Don&squot;t use for system provided sysrqs,&n;&t;&t; it is handled specially on the spark&n;&t;&t; and will never arive */
multiline_comment|/* b */
op_amp
id|sysrq_reboot_op
comma
multiline_comment|/* c */
l_int|NULL
comma
multiline_comment|/* d */
l_int|NULL
comma
multiline_comment|/* e */
op_amp
id|sysrq_term_op
comma
multiline_comment|/* f */
l_int|NULL
comma
multiline_comment|/* g */
l_int|NULL
comma
multiline_comment|/* h */
l_int|NULL
comma
multiline_comment|/* i */
op_amp
id|sysrq_kill_op
comma
multiline_comment|/* j */
l_int|NULL
comma
macro_line|#ifdef CONFIG_VT
multiline_comment|/* k */
op_amp
id|sysrq_SAK_op
comma
macro_line|#else
multiline_comment|/* k */
l_int|NULL
comma
macro_line|#endif
multiline_comment|/* l */
l_int|NULL
comma
multiline_comment|/* m */
op_amp
id|sysrq_showmem_op
comma
multiline_comment|/* n */
l_int|NULL
comma
multiline_comment|/* o */
l_int|NULL
comma
multiline_comment|/* This will often be registered&n;&t;&t; as &squot;Off&squot; at init time */
multiline_comment|/* p */
op_amp
id|sysrq_showregs_op
comma
multiline_comment|/* q */
l_int|NULL
comma
macro_line|#ifdef CONFIG_VT
multiline_comment|/* r */
op_amp
id|sysrq_unraw_op
comma
macro_line|#else
multiline_comment|/* r */
l_int|NULL
comma
macro_line|#endif
multiline_comment|/* s */
op_amp
id|sysrq_sync_op
comma
multiline_comment|/* t */
op_amp
id|sysrq_showstate_op
comma
multiline_comment|/* u */
op_amp
id|sysrq_mountro_op
comma
multiline_comment|/* v */
l_int|NULL
comma
multiline_comment|/* w */
l_int|NULL
comma
multiline_comment|/* x */
l_int|NULL
comma
multiline_comment|/* y */
l_int|NULL
comma
multiline_comment|/* z */
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* key2index calculation, -1 on invalid index */
DECL|function|sysrq_key_table_key2index
r_static
id|__inline__
r_int
id|sysrq_key_table_key2index
c_func
(paren
r_int
id|key
)paren
(brace
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|key
op_ge
l_char|&squot;0&squot;
)paren
op_amp
(paren
id|key
op_le
l_char|&squot;9&squot;
)paren
)paren
(brace
id|retval
op_assign
id|key
op_minus
l_char|&squot;0&squot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|key
op_ge
l_char|&squot;a&squot;
)paren
op_amp
(paren
id|key
op_le
l_char|&squot;z&squot;
)paren
)paren
(brace
id|retval
op_assign
id|key
op_plus
l_int|10
op_minus
l_char|&squot;a&squot;
suffix:semicolon
)brace
r_else
(brace
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * table lock and unlocking functions, exposed to modules&n; */
DECL|function|__sysrq_lock_table
r_void
id|__sysrq_lock_table
(paren
r_void
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|sysrq_key_table_lock
)paren
suffix:semicolon
)brace
DECL|function|__sysrq_unlock_table
r_void
id|__sysrq_unlock_table
(paren
r_void
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|sysrq_key_table_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * get and put functions for the table, exposed to modules.&n; */
DECL|function|__sysrq_get_key_op
r_struct
id|sysrq_key_op
op_star
id|__sysrq_get_key_op
(paren
r_int
id|key
)paren
(brace
r_struct
id|sysrq_key_op
op_star
id|op_p
suffix:semicolon
r_int
id|i
suffix:semicolon
id|i
op_assign
id|sysrq_key_table_key2index
c_func
(paren
id|key
)paren
suffix:semicolon
id|op_p
op_assign
(paren
id|i
op_eq
op_minus
l_int|1
)paren
ques
c_cond
l_int|NULL
suffix:colon
id|sysrq_key_table
(braket
id|i
)braket
suffix:semicolon
r_return
id|op_p
suffix:semicolon
)brace
DECL|function|__sysrq_put_key_op
r_void
id|__sysrq_put_key_op
(paren
r_int
id|key
comma
r_struct
id|sysrq_key_op
op_star
id|op_p
)paren
(brace
r_int
id|i
suffix:semicolon
id|i
op_assign
id|sysrq_key_table_key2index
c_func
(paren
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
op_minus
l_int|1
)paren
id|sysrq_key_table
(braket
id|i
)braket
op_assign
id|op_p
suffix:semicolon
)brace
multiline_comment|/*&n; * This function is called by the keyboard handler when SysRq is pressed&n; * and any other keycode arrives.&n; */
DECL|function|handle_sysrq
r_void
id|handle_sysrq
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sysrq_enabled
)paren
r_return
suffix:semicolon
id|__sysrq_lock_table
c_func
(paren
)paren
suffix:semicolon
id|__handle_sysrq_nolock
c_func
(paren
id|key
comma
id|pt_regs
comma
id|tty
)paren
suffix:semicolon
id|__sysrq_unlock_table
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the non-locking version of handle_sysrq&n; * It must/can only be called by sysrq key handlers,&n; * as they are inside of the lock&n; */
DECL|function|__handle_sysrq_nolock
r_void
id|__handle_sysrq_nolock
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|sysrq_key_op
op_star
id|op_p
suffix:semicolon
r_int
id|orig_log_level
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sysrq_enabled
)paren
r_return
suffix:semicolon
id|orig_log_level
op_assign
id|console_loglevel
suffix:semicolon
id|console_loglevel
op_assign
l_int|7
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SysRq : &quot;
)paren
suffix:semicolon
id|op_p
op_assign
id|__sysrq_get_key_op
c_func
(paren
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op_p
)paren
(brace
id|printk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|op_p-&gt;action_msg
)paren
suffix:semicolon
id|console_loglevel
op_assign
id|orig_log_level
suffix:semicolon
id|op_p
op_member_access_from_pointer
id|handler
c_func
(paren
id|key
comma
id|pt_regs
comma
id|tty
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;HELP : &quot;
)paren
suffix:semicolon
multiline_comment|/* Only print the help msg once per handler */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SYSRQ_KEY_TABLE_LENGTH
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|sysrq_key_table
(braket
id|i
)braket
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|sysrq_key_table
(braket
id|i
)braket
op_ne
id|sysrq_key_table
(braket
id|j
)braket
suffix:semicolon
id|j
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
id|i
)paren
id|printk
(paren
l_string|&quot;%s &quot;
comma
id|sysrq_key_table
(braket
id|i
)braket
op_member_access_from_pointer
id|help_msg
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|console_loglevel
op_assign
id|orig_log_level
suffix:semicolon
)brace
)brace
DECL|variable|handle_sysrq
id|EXPORT_SYMBOL
c_func
(paren
id|handle_sysrq
)paren
suffix:semicolon
DECL|variable|__handle_sysrq_nolock
id|EXPORT_SYMBOL
c_func
(paren
id|__handle_sysrq_nolock
)paren
suffix:semicolon
DECL|variable|__sysrq_lock_table
id|EXPORT_SYMBOL
c_func
(paren
id|__sysrq_lock_table
)paren
suffix:semicolon
DECL|variable|__sysrq_unlock_table
id|EXPORT_SYMBOL
c_func
(paren
id|__sysrq_unlock_table
)paren
suffix:semicolon
DECL|variable|__sysrq_get_key_op
id|EXPORT_SYMBOL
c_func
(paren
id|__sysrq_get_key_op
)paren
suffix:semicolon
DECL|variable|__sysrq_put_key_op
id|EXPORT_SYMBOL
c_func
(paren
id|__sysrq_put_key_op
)paren
suffix:semicolon
eof
