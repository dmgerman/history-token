multiline_comment|/*&n; *  IBM/3270 Driver -- Copyright (C) 2000 UTS Global LLC&n; *&n; *  tuball.c -- Initialization, termination, irq lookup&n; *&n; *&n; *&n; *&n; *&n; *  Author:  Richard Hitt&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;tubio.h&quot;
macro_line|#ifndef MODULE
macro_line|#include &lt;linux/init.h&gt;
macro_line|#if (LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0))
macro_line|#include &lt;asm/cpcmd.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#else
macro_line|#include &quot;../../../../arch/s390/kernel/cpcmd.h&quot;
macro_line|#endif
macro_line|#endif
multiline_comment|/* Module parameters */
DECL|variable|tubdebug
r_int
id|tubdebug
suffix:semicolon
DECL|variable|tubscrolltime
r_int
id|tubscrolltime
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|tubxcorrect
r_int
id|tubxcorrect
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Do correct ebc&lt;-&gt;asc tables */
macro_line|#ifdef MODULE
id|MODULE_PARM
c_func
(paren
id|tubdebug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|tubscrolltime
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|tubxcorrect
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Values for tubdebug and their effects:&n; * 1 - print in hex on console the first 16 bytes received&n; * 2 - print address at which array tubminors is allocated&n; * 4 - attempt to register tty3270_driver&n; */
DECL|variable|tubnummins
r_int
id|tubnummins
suffix:semicolon
DECL|variable|tubminors
id|tub_t
op_star
(paren
op_star
id|tubminors
)paren
(braket
id|TUBMAXMINS
)braket
suffix:semicolon
DECL|variable|tubirqs
id|tub_t
op_star
(paren
op_star
(paren
op_star
id|tubirqs
)paren
(braket
l_int|256
)braket
)paren
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|tub_ascebc
r_int
r_char
id|tub_ascebc
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|tub_ebcasc
r_int
r_char
id|tub_ebcasc
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|tubinitminors
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|tubfiniminors
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|tubint
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* Lookup-by-irq functions */
r_int
id|tubaddbyirq
c_func
(paren
id|tub_t
op_star
comma
r_int
)paren
suffix:semicolon
id|tub_t
op_star
id|tubfindbyirq
c_func
(paren
r_int
)paren
suffix:semicolon
r_void
id|tubdelbyirq
c_func
(paren
id|tub_t
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|tubfiniirqs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|fs3270_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fs3270_fini
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|tty3270_fini
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|tub_ebcgraf
r_int
r_char
id|tub_ebcgraf
(braket
l_int|64
)braket
op_assign
(brace
l_int|0x40
comma
l_int|0xc1
comma
l_int|0xc2
comma
l_int|0xc3
comma
l_int|0xc4
comma
l_int|0xc5
comma
l_int|0xc6
comma
l_int|0xc7
comma
l_int|0xc8
comma
l_int|0xc9
comma
l_int|0x4a
comma
l_int|0x4b
comma
l_int|0x4c
comma
l_int|0x4d
comma
l_int|0x4e
comma
l_int|0x4f
comma
l_int|0x50
comma
l_int|0xd1
comma
l_int|0xd2
comma
l_int|0xd3
comma
l_int|0xd4
comma
l_int|0xd5
comma
l_int|0xd6
comma
l_int|0xd7
comma
l_int|0xd8
comma
l_int|0xd9
comma
l_int|0x5a
comma
l_int|0x5b
comma
l_int|0x5c
comma
l_int|0x5d
comma
l_int|0x5e
comma
l_int|0x5f
comma
l_int|0x60
comma
l_int|0x61
comma
l_int|0xe2
comma
l_int|0xe3
comma
l_int|0xe4
comma
l_int|0xe5
comma
l_int|0xe6
comma
l_int|0xe7
comma
l_int|0xe8
comma
l_int|0xe9
comma
l_int|0x6a
comma
l_int|0x6b
comma
l_int|0x6c
comma
l_int|0x6d
comma
l_int|0x6e
comma
l_int|0x6f
comma
l_int|0xf0
comma
l_int|0xf1
comma
l_int|0xf2
comma
l_int|0xf3
comma
l_int|0xf4
comma
l_int|0xf5
comma
l_int|0xf6
comma
l_int|0xf7
comma
l_int|0xf8
comma
l_int|0xf9
comma
l_int|0x7a
comma
l_int|0x7b
comma
l_int|0x7c
comma
l_int|0x7d
comma
l_int|0x7e
comma
l_int|0x7f
)brace
suffix:semicolon
r_int
id|tub3270_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifndef MODULE
multiline_comment|/*&n; * Can&squot;t have this driver a module &amp; support console at the same time&n; */
macro_line|#ifdef CONFIG_TN3270_CONSOLE
r_static
id|kdev_t
id|tub3270_con_device
c_func
(paren
r_struct
id|console
op_star
)paren
suffix:semicolon
r_static
r_void
id|tub3270_con_unblank
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|tub3270_con_write
c_func
(paren
r_struct
id|console
op_star
comma
r_const
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|variable|tub3270_con
r_static
r_struct
id|console
id|tub3270_con
op_assign
(brace
l_string|&quot;tub3270&quot;
comma
multiline_comment|/* name */
id|tub3270_con_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* read */
id|tub3270_con_device
comma
multiline_comment|/* device */
l_int|NULL
comma
multiline_comment|/* wait_key */
id|tub3270_con_unblank
comma
multiline_comment|/* unblank */
l_int|NULL
comma
multiline_comment|/* setup */
id|CON_PRINTBUFFER
comma
multiline_comment|/* flags */
l_int|0
comma
multiline_comment|/* index */
l_int|0
comma
multiline_comment|/* cflag */
l_int|NULL
multiline_comment|/* next */
)brace
suffix:semicolon
DECL|variable|tub3270_con_bcb
id|bcb_t
id|tub3270_con_bcb
suffix:semicolon
multiline_comment|/* Buffer that receives con writes */
DECL|variable|tub3270_con_bcblock
id|spinlock_t
id|tub3270_con_bcblock
suffix:semicolon
multiline_comment|/* Lock for the buffer */
DECL|variable|tub3270_con_irq
r_int
id|tub3270_con_irq
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* set nonneg by _activate() */
DECL|variable|tub3270_con_tubp
id|tub_t
op_star
id|tub3270_con_tubp
suffix:semicolon
multiline_comment|/* set nonzero by _activate() */
DECL|variable|tty3270_con_driver
r_struct
id|tty_driver
id|tty3270_con_driver
suffix:semicolon
multiline_comment|/* for /dev/console at 4, 64 */
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0))
DECL|variable|tub3270_con_devno
r_int
id|tub3270_con_devno
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* set by tub3270_con_setup() */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|tub3270_con_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
)paren
(brace
r_int
id|vdev
suffix:semicolon
id|vdev
op_assign
id|simple_strtoul
c_func
(paren
id|str
comma
l_int|0
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vdev
op_ge
l_int|0
op_logical_and
id|vdev
OL
l_int|65536
)paren
id|tub3270_con_devno
op_assign
id|vdev
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
(paren
r_int
id|tub3270_con_init
c_func
(paren
r_int
id|kmem_start
comma
r_int
id|kmem_end
)paren
)paren
(brace
id|tub3270_con_bcb.bc_len
op_assign
l_int|65536
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_IS_VM
op_logical_and
op_logical_neg
id|MACHINE_IS_P390
)paren
r_return
id|kmem_start
suffix:semicolon
id|tub3270_con_bcb.bc_buf
op_assign
(paren
r_void
op_star
)paren
id|kmem_start
suffix:semicolon
id|kmem_start
op_add_assign
id|tub3270_con_bcb.bc_len
suffix:semicolon
id|register_console
c_func
(paren
op_amp
id|tub3270_con
)paren
suffix:semicolon
r_return
id|kmem_start
suffix:semicolon
)brace
macro_line|#else
DECL|macro|tub3270_con_devno
mdefine_line|#define tub3270_con_devno console_device
DECL|function|tub3270_con_init
r_void
id|__init
id|tub3270_con_init
c_func
(paren
r_void
)paren
(brace
id|tub3270_con_bcb.bc_len
op_assign
l_int|65536
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|CONSOLE_IS_3270
)paren
r_return
suffix:semicolon
id|tub3270_con_bcb.bc_buf
op_assign
(paren
r_void
op_star
)paren
id|alloc_bootmem_low
c_func
(paren
id|tub3270_con_bcb.bc_len
)paren
suffix:semicolon
id|register_console
c_func
(paren
op_amp
id|tub3270_con
)paren
suffix:semicolon
)brace
macro_line|#endif
r_static
id|kdev_t
DECL|function|tub3270_con_device
id|tub3270_con_device
c_func
(paren
r_struct
id|console
op_star
id|conp
)paren
(brace
r_return
id|MKDEV
c_func
(paren
id|IBM_TTY3270_MAJOR
comma
id|conp-&gt;index
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|tub3270_con_unblank
id|tub3270_con_unblank
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* flush everything:  panic has occurred */
)brace
DECL|variable|tub3270_con_write_deadlock_ct
r_int
id|tub3270_con_write_deadlock_ct
suffix:semicolon
DECL|variable|tub3270_con_write_deadlock_bytes
r_int
id|tub3270_con_write_deadlock_bytes
suffix:semicolon
r_static
r_void
DECL|function|tub3270_con_write
id|tub3270_con_write
c_func
(paren
r_struct
id|console
op_star
id|conp
comma
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_int
id|flags
suffix:semicolon
id|tub_t
op_star
id|tubp
op_assign
id|tub3270_con_tubp
suffix:semicolon
r_void
id|tty3270_sched_bh
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|bcb_t
id|obcb
suffix:semicolon
id|obcb.bc_buf
op_assign
(paren
r_char
op_star
)paren
id|buf
suffix:semicolon
id|obcb.bc_len
op_assign
id|obcb.bc_cnt
op_assign
id|obcb.bc_wr
op_assign
id|MIN
c_func
(paren
id|count
comma
id|tub3270_con_bcb.bc_len
)paren
suffix:semicolon
id|obcb.bc_rd
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tub3270_con_bcblock
comma
id|flags
)paren
suffix:semicolon
id|rc
op_assign
id|tub3270_movedata
c_func
(paren
op_amp
id|obcb
comma
op_amp
id|tub3270_con_bcb
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tub3270_con_bcblock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tubp
op_logical_and
id|rc
op_logical_and
id|TUBTRYLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
)paren
(brace
id|tty3270_sched_bh
c_func
(paren
id|tubp
)paren
suffix:semicolon
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|tub3270_con_copy
r_int
id|tub3270_con_copy
c_func
(paren
id|tub_t
op_star
id|tubp
)paren
(brace
r_int
id|flags
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tub3270_con_bcblock
comma
id|flags
)paren
suffix:semicolon
id|rc
op_assign
id|tub3270_movedata
c_func
(paren
op_amp
id|tub3270_con_bcb
comma
op_amp
id|tubp-&gt;tty_bcb
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tub3270_con_bcblock
comma
id|flags
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_TN3270_CONSOLE */
macro_line|#else /* If generated as a MODULE */
multiline_comment|/*&n; * module init:  find tubes; get a major nbr&n; */
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|tubnummins
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EEEK!!  Tube driver cobbigling!!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|tub3270_init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * remove driver:  unregister the major number&n; */
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|fs3270_fini
c_func
(paren
)paren
suffix:semicolon
id|tty3270_fini
c_func
(paren
)paren
suffix:semicolon
id|tubfiniminors
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* Not a MODULE or a MODULE */
r_void
DECL|function|tub_inc_use_count
id|tub_inc_use_count
c_func
(paren
r_void
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
r_void
DECL|function|tub_dec_use_count
id|tub_dec_use_count
c_func
(paren
r_void
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*&n; * tub3270_init() called by kernel or module initialization&n; */
r_int
DECL|function|tub3270_init
id|tub3270_init
c_func
(paren
r_void
)paren
(brace
id|s390_dev_info_t
id|d
suffix:semicolon
r_int
id|i
comma
id|rc
suffix:semicolon
multiline_comment|/*&n;&t; * Copy and correct ebcdic - ascii translate tables&n;&t; */
id|memcpy
c_func
(paren
id|tub_ascebc
comma
id|_ascebc
comma
r_sizeof
id|tub_ascebc
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|tub_ebcasc
comma
id|_ebcasc
comma
r_sizeof
id|tub_ebcasc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tubxcorrect
)paren
(brace
multiline_comment|/* correct brackets and circumflex */
id|tub_ascebc
(braket
l_char|&squot;[&squot;
)braket
op_assign
l_int|0xad
suffix:semicolon
id|tub_ascebc
(braket
l_char|&squot;]&squot;
)braket
op_assign
l_int|0xbd
suffix:semicolon
id|tub_ebcasc
(braket
l_int|0xad
)braket
op_assign
l_char|&squot;[&squot;
suffix:semicolon
id|tub_ebcasc
(braket
l_int|0xbd
)braket
op_assign
l_char|&squot;]&squot;
suffix:semicolon
id|tub_ascebc
(braket
l_char|&squot;^&squot;
)braket
op_assign
l_int|0xb0
suffix:semicolon
id|tub_ebcasc
(braket
l_int|0x5f
)braket
op_assign
l_char|&squot;^&squot;
suffix:semicolon
)brace
id|rc
op_assign
id|tubinitminors
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_return
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|fs3270_init
c_func
(paren
)paren
op_logical_or
id|tty3270_init
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fs3270_init() or tty3270_init() failed&bslash;n&quot;
)paren
suffix:semicolon
id|fs3270_fini
c_func
(paren
)paren
suffix:semicolon
id|tty3270_fini
c_func
(paren
)paren
suffix:semicolon
id|tubfiniminors
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|get_irq_first
c_func
(paren
)paren
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_assign
id|get_irq_next
c_func
(paren
id|i
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|get_dev_info_by_irq
c_func
(paren
id|i
comma
op_amp
id|d
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|d.status
)paren
r_continue
suffix:semicolon
macro_line|#ifdef CONFIG_TN3270_CONSOLE
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0))
r_if
c_cond
(paren
id|d.sid_data.cu_type
op_eq
l_int|0x3215
op_logical_and
id|MACHINE_IS_VM
)paren
(brace
id|cpcmd
c_func
(paren
l_string|&quot;TERM CONMODE 3270&quot;
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|d.sid_data.cu_type
op_assign
l_int|0x3270
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|d.sid_data.cu_type
op_eq
l_int|0x3215
op_logical_and
id|CONSOLE_IS_3270
)paren
(brace
id|cpcmd
c_func
(paren
l_string|&quot;TERM CONMODE 3270&quot;
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|d.sid_data.cu_type
op_assign
l_int|0x3270
suffix:semicolon
)brace
macro_line|#endif /* LINUX_VERSION_CODE */
macro_line|#endif /* CONFIG_TN3270_CONSOLE */
r_if
c_cond
(paren
(paren
id|d.sid_data.cu_type
op_amp
l_int|0xfff0
)paren
op_ne
l_int|0x3270
)paren
r_continue
suffix:semicolon
id|rc
op_assign
id|tubmakemin
c_func
(paren
id|i
comma
op_amp
id|d
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;3270 tube registration ran out of memory&quot;
l_string|&quot; after %d devices&bslash;n&quot;
comma
id|tubnummins
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;3270: %.4x on sch %d, minor %d&bslash;n&quot;
comma
id|d.devno
comma
id|d.irq
comma
id|rc
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * tub3270_movedata(bcb_t *, bcb_t *) -- Move data stream&n; */
r_int
DECL|function|tub3270_movedata
id|tub3270_movedata
c_func
(paren
id|bcb_t
op_star
id|ib
comma
id|bcb_t
op_star
id|ob
comma
r_int
id|fromuser
)paren
(brace
r_int
id|count
suffix:semicolon
multiline_comment|/* Total move length */
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|count
op_assign
id|MIN
c_func
(paren
id|ib-&gt;bc_cnt
comma
id|ob-&gt;bc_len
op_minus
id|ob-&gt;bc_cnt
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_int
id|len1
suffix:semicolon
multiline_comment|/* Contig bytes avail in ib */
r_if
c_cond
(paren
id|ib-&gt;bc_wr
OG
id|ib-&gt;bc_rd
)paren
id|len1
op_assign
id|ib-&gt;bc_wr
op_minus
id|ib-&gt;bc_rd
suffix:semicolon
r_else
id|len1
op_assign
id|ib-&gt;bc_len
op_minus
id|ib-&gt;bc_rd
suffix:semicolon
r_if
c_cond
(paren
id|len1
OG
id|count
)paren
id|len1
op_assign
id|count
suffix:semicolon
r_while
c_loop
(paren
id|len1
OG
l_int|0
)paren
(brace
r_int
id|len2
suffix:semicolon
multiline_comment|/* Contig space avail in ob */
r_if
c_cond
(paren
id|ob-&gt;bc_rd
OG
id|ob-&gt;bc_wr
)paren
id|len2
op_assign
id|ob-&gt;bc_rd
op_minus
id|ob-&gt;bc_wr
suffix:semicolon
r_else
id|len2
op_assign
id|ob-&gt;bc_len
op_minus
id|ob-&gt;bc_wr
suffix:semicolon
r_if
c_cond
(paren
id|len2
OG
id|len1
)paren
id|len2
op_assign
id|len1
suffix:semicolon
r_if
c_cond
(paren
id|fromuser
)paren
(brace
id|len2
op_sub_assign
id|copy_from_user
c_func
(paren
id|ob-&gt;bc_buf
op_plus
id|ob-&gt;bc_wr
comma
id|ib-&gt;bc_buf
op_plus
id|ib-&gt;bc_rd
comma
id|len2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len2
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
id|memcpy
c_func
(paren
id|ob-&gt;bc_buf
op_plus
id|ob-&gt;bc_wr
comma
id|ib-&gt;bc_buf
op_plus
id|ib-&gt;bc_rd
comma
id|len2
)paren
suffix:semicolon
id|ib-&gt;bc_rd
op_add_assign
id|len2
suffix:semicolon
r_if
c_cond
(paren
id|ib-&gt;bc_rd
op_eq
id|ib-&gt;bc_len
)paren
id|ib-&gt;bc_rd
op_assign
l_int|0
suffix:semicolon
id|ib-&gt;bc_cnt
op_sub_assign
id|len2
suffix:semicolon
id|ob-&gt;bc_wr
op_add_assign
id|len2
suffix:semicolon
r_if
c_cond
(paren
id|ob-&gt;bc_wr
op_eq
id|ob-&gt;bc_len
)paren
id|ob-&gt;bc_wr
op_assign
l_int|0
suffix:semicolon
id|ob-&gt;bc_cnt
op_add_assign
id|len2
suffix:semicolon
id|len1
op_sub_assign
id|len2
suffix:semicolon
id|count
op_sub_assign
id|len2
suffix:semicolon
)brace
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * receive an interrupt&n; */
r_void
DECL|function|tubint
id|tubint
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|ipp
comma
r_struct
id|pt_regs
op_star
id|prp
)paren
(brace
id|devstat_t
op_star
id|dsp
op_assign
id|ipp
suffix:semicolon
id|tub_t
op_star
id|tubp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tubp
op_assign
id|IRQ2TUB
c_func
(paren
id|irq
)paren
)paren
op_logical_and
(paren
id|tubp-&gt;intv
)paren
)paren
(paren
id|tubp-&gt;intv
)paren
(paren
id|tubp
comma
id|dsp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize array of pointers to minor structures tub_t.&n; * Returns 0 or -ENOMEM.&n; */
r_int
DECL|function|tubinitminors
id|tubinitminors
c_func
(paren
r_void
)paren
(brace
id|tubminors
op_assign
(paren
id|tub_t
op_star
(paren
op_star
)paren
(braket
id|TUBMAXMINS
)braket
)paren
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|tubminors
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tubminors
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|tubminors
comma
l_int|0
comma
r_sizeof
op_star
id|tubminors
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a minor 327x device.  Argument is an irq value.&n; *&n; * Point elements of two arrays to the newly created tub_t:&n; * 1. (*tubminors)[minor]&n; * 2. (*(*tubirqs)[irqhi])[irqlo]&n; * The first looks up from minor number at context time; the second&n; * looks up from irq at interrupt time.&n; */
r_int
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0))
DECL|function|tubmakemin
id|tubmakemin
c_func
(paren
r_int
id|irq
comma
id|dev_info_t
op_star
id|dp
)paren
macro_line|#else
id|tubmakemin
c_func
(paren
r_int
id|irq
comma
id|s390_dev_info_t
op_star
id|dp
)paren
macro_line|#endif
(brace
id|tub_t
op_star
id|tubp
suffix:semicolon
r_int
id|minor
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|minor
op_assign
op_increment
id|tubnummins
)paren
op_eq
id|TUBMAXMINS
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|tubp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|tub_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tubp
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tubaddbyirq
c_func
(paren
id|tubp
comma
id|irq
)paren
op_ne
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|tubp
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|tubp
comma
l_int|0
comma
r_sizeof
(paren
id|tub_t
)paren
)paren
suffix:semicolon
id|tubp-&gt;minor
op_assign
id|minor
suffix:semicolon
id|tubp-&gt;irq
op_assign
id|irq
suffix:semicolon
id|TUBLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
id|tubp-&gt;devno
op_assign
id|dp-&gt;devno
suffix:semicolon
id|tubp-&gt;geom_rows
op_assign
id|_GEOM_ROWS
suffix:semicolon
id|tubp-&gt;geom_cols
op_assign
id|_GEOM_COLS
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|tubp-&gt;waitq
)paren
suffix:semicolon
id|tubp-&gt;tty_bcb.bc_len
op_assign
id|TTY_OUTPUT_SIZE
suffix:semicolon
id|tubp-&gt;tty_bcb.bc_buf
op_assign
(paren
r_void
op_star
)paren
id|kmalloc
c_func
(paren
id|tubp-&gt;tty_bcb.bc_len
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tubp-&gt;tty_bcb.bc_buf
op_eq
l_int|NULL
)paren
(brace
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
id|tubdelbyirq
c_func
(paren
id|tubp
comma
id|irq
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tubp
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|tubp-&gt;tty_bcb.bc_cnt
op_assign
l_int|0
suffix:semicolon
id|tubp-&gt;tty_bcb.bc_wr
op_assign
l_int|0
suffix:semicolon
id|tubp-&gt;tty_bcb.bc_rd
op_assign
l_int|0
suffix:semicolon
(paren
op_star
id|tubminors
)paren
(braket
id|minor
)braket
op_assign
id|tubp
suffix:semicolon
macro_line|#ifdef CONFIG_TN3270_CONSOLE
r_if
c_cond
(paren
id|CONSOLE_IS_3270
)paren
(brace
r_if
c_cond
(paren
id|tub3270_con_tubp
op_eq
l_int|NULL
op_logical_and
id|tub3270_con_bcb.bc_buf
op_ne
l_int|NULL
op_logical_and
(paren
id|tub3270_con_devno
op_eq
op_minus
l_int|1
op_logical_or
id|tub3270_con_devno
op_eq
id|dp-&gt;devno
)paren
)paren
(brace
r_extern
r_void
id|tty3270_int
c_func
(paren
id|tub_t
op_star
comma
id|devstat_t
op_star
)paren
suffix:semicolon
id|tub3270_con_devno
op_assign
id|dp-&gt;devno
suffix:semicolon
id|tubp-&gt;cmd
op_assign
id|TBC_CONOPEN
suffix:semicolon
id|tubp-&gt;flags
op_or_assign
id|TUB_OPEN_STET
op_or
id|TUB_INPUT_HACK
suffix:semicolon
id|tty3270_size
c_func
(paren
id|tubp
comma
op_amp
id|flags
)paren
suffix:semicolon
id|tty3270_aid_init
c_func
(paren
id|tubp
)paren
suffix:semicolon
id|tty3270_scl_init
c_func
(paren
id|tubp
)paren
suffix:semicolon
id|tub3270_con_irq
op_assign
id|tubp-&gt;irq
suffix:semicolon
id|tub3270_con_tubp
op_assign
id|tubp
suffix:semicolon
id|tubp-&gt;intv
op_assign
id|tty3270_int
suffix:semicolon
id|tubp-&gt;cmd
op_assign
id|TBC_UPDSTAT
suffix:semicolon
id|tty3270_build
c_func
(paren
id|tubp
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_TN3270_CONSOLE */
macro_line|#ifdef CONFIG_DEVFS_FS
id|fs3270_devfs_register
c_func
(paren
id|tubp
)paren
suffix:semicolon
macro_line|#endif
id|TUBUNLOCK
c_func
(paren
id|tubp-&gt;irq
comma
id|flags
)paren
suffix:semicolon
r_return
id|minor
suffix:semicolon
)brace
multiline_comment|/*&n; * Release array of pointers to minor structures tub_t, but first&n; * release any storage pointed to by them.&n; */
r_void
DECL|function|tubfiniminors
id|tubfiniminors
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|tub_t
op_star
op_star
id|tubpp
comma
op_star
id|tubp
suffix:semicolon
r_if
c_cond
(paren
id|tubminors
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TUBMAXMINS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tubpp
op_assign
op_amp
(paren
op_star
id|tubminors
)paren
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tubp
op_assign
op_star
id|tubpp
)paren
)paren
(brace
macro_line|#ifdef CONFIG_DEVFS_FS
id|fs3270_devfs_unregister
c_func
(paren
id|tubp
)paren
suffix:semicolon
macro_line|#endif
id|tubdelbyirq
c_func
(paren
id|tubp
comma
id|tubp-&gt;irq
)paren
suffix:semicolon
id|tty3270_rcl_fini
c_func
(paren
id|tubp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tubp-&gt;tty_bcb.bc_buf
)paren
suffix:semicolon
id|tubp-&gt;tty_bcb.bc_buf
op_assign
l_int|NULL
suffix:semicolon
id|tubp-&gt;ttyscreen
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|tubp
)paren
suffix:semicolon
op_star
id|tubpp
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|tubminors
)paren
suffix:semicolon
id|tubminors
op_assign
l_int|NULL
suffix:semicolon
id|tubfiniirqs
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * tubaddbyirq() -- Add tub_t for irq lookup in tubint()&n; */
r_int
DECL|function|tubaddbyirq
id|tubaddbyirq
c_func
(paren
id|tub_t
op_star
id|tubp
comma
r_int
id|irq
)paren
(brace
r_int
id|irqhi
op_assign
(paren
id|irq
op_rshift
l_int|8
)paren
op_amp
l_int|255
suffix:semicolon
r_int
id|irqlo
op_assign
id|irq
op_amp
l_int|255
suffix:semicolon
id|tub_t
op_star
(paren
op_star
id|itubpp
)paren
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* Allocate array (*tubirqs)[] if first time */
r_if
c_cond
(paren
id|tubirqs
op_eq
l_int|NULL
)paren
(brace
id|tubirqs
op_assign
(paren
id|tub_t
op_star
(paren
op_star
(paren
op_star
)paren
(braket
l_int|256
)braket
)paren
(braket
l_int|256
)braket
)paren
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|tubirqs
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tubirqs
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|tubirqs
comma
l_int|0
comma
r_sizeof
op_star
id|tubirqs
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate subarray (*(*tubirqs)[])[] if first use */
r_if
c_cond
(paren
(paren
id|itubpp
op_assign
(paren
op_star
id|tubirqs
)paren
(braket
id|irqhi
)braket
)paren
op_eq
l_int|NULL
)paren
(brace
id|itubpp
op_assign
(paren
id|tub_t
op_star
(paren
op_star
)paren
(braket
l_int|256
)braket
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|itubpp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|itubpp
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|tubnummins
op_eq
l_int|1
)paren
(brace
multiline_comment|/* if first time */
id|kfree
c_func
(paren
id|tubirqs
)paren
suffix:semicolon
id|tubirqs
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_else
(brace
id|memset
c_func
(paren
id|itubpp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|itubpp
)paren
)paren
suffix:semicolon
(paren
op_star
id|tubirqs
)paren
(braket
id|irqhi
)braket
op_assign
id|itubpp
suffix:semicolon
)brace
)brace
multiline_comment|/* Request interrupt service */
r_if
c_cond
(paren
(paren
id|tubp-&gt;irqrc
op_assign
id|request_irq
c_func
(paren
id|irq
comma
id|tubint
comma
id|SA_INTERRUPT
comma
l_string|&quot;3270 tube driver&quot;
comma
op_amp
id|tubp-&gt;devstat
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|tubp-&gt;irqrc
suffix:semicolon
multiline_comment|/* Fill in the proper subarray element */
(paren
op_star
id|itubpp
)paren
(braket
id|irqlo
)braket
op_assign
id|tubp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * tubfindbyirq(irq)&n; */
id|tub_t
op_star
DECL|function|tubfindbyirq
id|tubfindbyirq
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|irqhi
op_assign
(paren
id|irq
op_rshift
l_int|8
)paren
op_amp
l_int|255
suffix:semicolon
r_int
id|irqlo
op_assign
id|irq
op_amp
l_int|255
suffix:semicolon
id|tub_t
op_star
id|tubp
suffix:semicolon
r_if
c_cond
(paren
id|tubirqs
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|tubirqs
)paren
(braket
id|irqhi
)braket
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|tubp
op_assign
(paren
op_star
(paren
op_star
id|tubirqs
)paren
(braket
id|irqhi
)braket
)paren
(braket
id|irqlo
)braket
suffix:semicolon
r_if
c_cond
(paren
id|tubp-&gt;irq
op_eq
id|irq
)paren
r_return
id|tubp
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * tubdelbyirq(tub_t*, irq)&n; */
r_void
DECL|function|tubdelbyirq
id|tubdelbyirq
c_func
(paren
id|tub_t
op_star
id|tubp
comma
r_int
id|irq
)paren
(brace
r_int
id|irqhi
op_assign
(paren
id|irq
op_rshift
l_int|8
)paren
op_amp
l_int|255
suffix:semicolon
r_int
id|irqlo
op_assign
id|irq
op_amp
l_int|255
suffix:semicolon
id|tub_t
op_star
(paren
op_star
id|itubpp
)paren
(braket
l_int|256
)braket
comma
op_star
id|itubp
suffix:semicolon
r_if
c_cond
(paren
id|tubirqs
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;tubirqs is NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|itubpp
op_assign
(paren
op_star
id|tubirqs
)paren
(braket
id|irqhi
)braket
suffix:semicolon
r_if
c_cond
(paren
id|itubpp
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;tubirqs[%d] is NULL&bslash;n&quot;
comma
id|irqhi
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|itubp
op_assign
(paren
op_star
id|itubpp
)paren
(braket
id|irqlo
)braket
suffix:semicolon
r_if
c_cond
(paren
id|itubp
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;tubirqs[%d][%d] is NULL&bslash;n&quot;
comma
id|irqhi
comma
id|irqlo
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|itubp-&gt;irqrc
op_eq
l_int|0
)paren
id|free_irq
c_func
(paren
id|irq
comma
op_amp
id|itubp-&gt;devstat
)paren
suffix:semicolon
(paren
op_star
id|itubpp
)paren
(braket
id|irqlo
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * tubfiniirqs() -- clean up storage in tub_t *(*(*tubirqs)[256])[256]&n; */
r_void
DECL|function|tubfiniirqs
id|tubfiniirqs
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|tub_t
op_star
(paren
op_star
id|itubpp
)paren
(braket
l_int|256
)braket
suffix:semicolon
r_if
c_cond
(paren
id|tubirqs
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|itubpp
op_assign
(paren
op_star
id|tubirqs
)paren
(braket
id|i
)braket
)paren
)paren
(brace
id|kfree
c_func
(paren
id|itubpp
)paren
suffix:semicolon
(paren
op_star
id|tubirqs
)paren
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|tubirqs
)paren
suffix:semicolon
id|tubirqs
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
eof
