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
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;&t;&t;/* for fsync_bdev() */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
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
dot
id|handler
op_assign
id|sysrq_handle_loglevel
comma
dot
id|help_msg
op_assign
l_string|&quot;loglevel0-8&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Changing Loglevel&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_LOG
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
id|vc_cons
(braket
id|fg_console
)braket
dot
id|d
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
dot
id|handler
op_assign
id|sysrq_handle_SAK
comma
dot
id|help_msg
op_assign
l_string|&quot;saK&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;SAK&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_KEYBOARD
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
dot
id|handler
op_assign
id|sysrq_handle_unraw
comma
dot
id|help_msg
op_assign
l_string|&quot;unRaw&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Keyboard mode set to XLATE&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_KEYBOARD
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
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
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
dot
id|handler
op_assign
id|sysrq_handle_reboot
comma
dot
id|help_msg
op_assign
l_string|&quot;reBoot&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Resetting&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_BOOT
comma
)brace
suffix:semicolon
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
id|emergency_sync
c_func
(paren
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
dot
id|handler
op_assign
id|sysrq_handle_sync
comma
dot
id|help_msg
op_assign
l_string|&quot;Sync&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Emergency Sync&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_SYNC
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
id|emergency_remount
c_func
(paren
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
dot
id|handler
op_assign
id|sysrq_handle_mountro
comma
dot
id|help_msg
op_assign
l_string|&quot;Unmount&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Emergency Remount R/O&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_REMOUNT
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
dot
id|handler
op_assign
id|sysrq_handle_showregs
comma
dot
id|help_msg
op_assign
l_string|&quot;showPc&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Show Regs&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_DUMP
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
dot
id|handler
op_assign
id|sysrq_handle_showstate
comma
dot
id|help_msg
op_assign
l_string|&quot;showTasks&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Show State&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_DUMP
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
dot
id|handler
op_assign
id|sysrq_handle_showmem
comma
dot
id|help_msg
op_assign
l_string|&quot;showMem&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Show Memory&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_DUMP
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
dot
id|handler
op_assign
id|sysrq_handle_term
comma
dot
id|help_msg
op_assign
l_string|&quot;tErm&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Terminate All Tasks&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_SIGNAL
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
dot
id|handler
op_assign
id|sysrq_handle_kill
comma
dot
id|help_msg
op_assign
l_string|&quot;kIll&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Kill All Tasks&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_SIGNAL
comma
)brace
suffix:semicolon
multiline_comment|/* END SIGNAL SYSRQ HANDLERS BLOCK */
DECL|function|sysrq_handle_unrt
r_static
r_void
id|sysrq_handle_unrt
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
id|normalize_rt_tasks
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|sysrq_unrt_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_unrt_op
op_assign
(brace
dot
id|handler
op_assign
id|sysrq_handle_unrt
comma
dot
id|help_msg
op_assign
l_string|&quot;Nice&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Nice All RT Tasks&quot;
comma
dot
id|enable_mask
op_assign
id|SYSRQ_ENABLE_RTNICE
comma
)brace
suffix:semicolon
multiline_comment|/* Key Operations table and lock */
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|sysrq_key_table_lock
)paren
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
multiline_comment|/* Don&squot;t use for system provided sysrqs,&n;&t;&t; it is handled specially on the sparc&n;&t;&t; and will never arrive */
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
op_amp
id|sysrq_unrt_op
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
multiline_comment|/* May be assigned at init time by SMP VOYAGER */
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
op_logical_and
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
op_logical_and
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
multiline_comment|/*&n; * This is the non-locking version of handle_sysrq&n; * It must/can only be called by sysrq key handlers,&n; * as they are inside of the lock&n; */
DECL|function|__handle_sysrq
r_void
id|__handle_sysrq
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
comma
r_int
id|check_mask
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
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sysrq_key_table_lock
comma
id|flags
)paren
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
multiline_comment|/* Should we check for enabled operations (/proc/sysrq-trigger should not)&n;&t;&t; * and is the invoked operation enabled? */
r_if
c_cond
(paren
op_logical_neg
id|check_mask
op_logical_or
id|sysrq_enabled
op_eq
l_int|1
op_logical_or
(paren
id|sysrq_enabled
op_amp
id|op_p-&gt;enable_mask
)paren
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
id|printk
c_func
(paren
l_string|&quot;This sysrq operation is disabled.&bslash;n&quot;
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sysrq_key_table_lock
comma
id|flags
)paren
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
id|__handle_sysrq
c_func
(paren
id|key
comma
id|pt_regs
comma
id|tty
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|__sysrq_swap_key_ops
r_int
id|__sysrq_swap_key_ops
c_func
(paren
r_int
id|key
comma
r_struct
id|sysrq_key_op
op_star
id|insert_op_p
comma
r_struct
id|sysrq_key_op
op_star
id|remove_op_p
)paren
(brace
r_int
id|retval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sysrq_key_table_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__sysrq_get_key_op
c_func
(paren
id|key
)paren
op_eq
id|remove_op_p
)paren
(brace
id|__sysrq_put_key_op
c_func
(paren
id|key
comma
id|insert_op_p
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sysrq_key_table_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|register_sysrq_key
r_int
id|register_sysrq_key
c_func
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
r_return
id|__sysrq_swap_key_ops
c_func
(paren
id|key
comma
id|op_p
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|unregister_sysrq_key
r_int
id|unregister_sysrq_key
c_func
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
r_return
id|__sysrq_swap_key_ops
c_func
(paren
id|key
comma
l_int|NULL
comma
id|op_p
)paren
suffix:semicolon
)brace
DECL|variable|handle_sysrq
id|EXPORT_SYMBOL
c_func
(paren
id|handle_sysrq
)paren
suffix:semicolon
DECL|variable|register_sysrq_key
id|EXPORT_SYMBOL
c_func
(paren
id|register_sysrq_key
)paren
suffix:semicolon
DECL|variable|unregister_sysrq_key
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_sysrq_key
)paren
suffix:semicolon
eof
