multiline_comment|/*&n; * Copyright (C) 1996 Paul Mackerras.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/pmu.h&gt;
macro_line|#include &lt;linux/cuda.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/xmon.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/bootx.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/btext.h&gt;
DECL|variable|sccc
DECL|variable|sccd
r_static
r_volatile
r_int
r_char
op_star
id|sccc
comma
op_star
id|sccd
suffix:semicolon
DECL|variable|TXRDY
DECL|variable|RXRDY
DECL|variable|DLAB
r_int
r_int
id|TXRDY
comma
id|RXRDY
comma
id|DLAB
suffix:semicolon
r_static
r_int
id|xmon_expect
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
r_int
id|timeout
)paren
suffix:semicolon
DECL|variable|use_serial
r_static
r_int
id|use_serial
suffix:semicolon
DECL|variable|use_screen
r_static
r_int
id|use_screen
suffix:semicolon
DECL|variable|via_modem
r_static
r_int
id|via_modem
suffix:semicolon
DECL|variable|xmon_use_sccb
r_static
r_int
id|xmon_use_sccb
suffix:semicolon
DECL|variable|channel_node
r_static
r_struct
id|device_node
op_star
id|channel_node
suffix:semicolon
DECL|macro|TB_SPEED
mdefine_line|#define TB_SPEED&t;25000000
DECL|function|readtb
r_static
r_inline
r_int
r_int
id|readtb
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mftb %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|buf_access
r_void
id|buf_access
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|DLAB
)paren
id|sccd
(braket
l_int|3
)braket
op_and_assign
op_complement
id|DLAB
suffix:semicolon
multiline_comment|/* reset DLAB */
)brace
r_extern
r_int
id|adb_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_CHRP
multiline_comment|/*&n; * This looks in the &quot;ranges&quot; property for the primary PCI host bridge&n; * to find the physical address of the start of PCI/ISA I/O space.&n; * It is basically a cut-down version of pci_process_bridge_OF_ranges.&n; */
DECL|function|chrp_find_phys_io_base
r_static
r_int
r_int
id|chrp_find_phys_io_base
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|node
suffix:semicolon
r_int
r_int
op_star
id|ranges
suffix:semicolon
r_int
r_int
id|base
op_assign
id|CHRP_ISA_IO_BASE
suffix:semicolon
r_int
id|rlen
op_assign
l_int|0
suffix:semicolon
r_int
id|np
suffix:semicolon
id|node
op_assign
id|find_devices
c_func
(paren
l_string|&quot;isa&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
op_ne
l_int|NULL
)paren
(brace
id|node
op_assign
id|node-&gt;parent
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
l_int|NULL
op_logical_or
id|node-&gt;type
op_eq
l_int|NULL
op_logical_or
id|strcmp
c_func
(paren
id|node-&gt;type
comma
l_string|&quot;pci&quot;
)paren
op_ne
l_int|0
)paren
id|node
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|node
op_eq
l_int|NULL
)paren
id|node
op_assign
id|find_devices
c_func
(paren
l_string|&quot;pci&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
l_int|NULL
)paren
r_return
id|base
suffix:semicolon
id|ranges
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|node
comma
l_string|&quot;ranges&quot;
comma
op_amp
id|rlen
)paren
suffix:semicolon
id|np
op_assign
id|prom_n_addr_cells
c_func
(paren
id|node
)paren
op_plus
l_int|5
suffix:semicolon
r_while
c_loop
(paren
(paren
id|rlen
op_sub_assign
id|np
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|ranges
(braket
l_int|0
)braket
op_rshift
l_int|24
)paren
op_eq
l_int|1
op_logical_and
id|ranges
(braket
l_int|2
)braket
op_eq
l_int|0
)paren
(brace
multiline_comment|/* I/O space starting at 0, grab the phys base */
id|base
op_assign
id|ranges
(braket
id|np
op_minus
l_int|3
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ranges
op_add_assign
id|np
suffix:semicolon
)brace
r_return
id|base
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_CHRP */
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|function|sysrq_handle_xmon
r_static
r_void
id|sysrq_handle_xmon
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|xmon
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
DECL|variable|sysrq_xmon_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_xmon_op
op_assign
(brace
dot
id|handler
op_assign
id|sysrq_handle_xmon
comma
dot
id|help_msg
op_assign
l_string|&quot;Xmon&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Entering xmon&bslash;n&quot;
comma
)brace
suffix:semicolon
macro_line|#endif
r_void
DECL|function|xmon_map_scc
id|xmon_map_scc
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PPC_MULTIPLATFORM
r_volatile
r_int
r_char
op_star
id|base
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
macro_line|#ifdef CONFIG_BOOTX_TEXT
r_if
c_cond
(paren
op_logical_neg
id|use_screen
op_logical_and
op_logical_neg
id|use_serial
op_logical_and
op_logical_neg
id|machine_is_compatible
c_func
(paren
l_string|&quot;iMac&quot;
)paren
)paren
(brace
multiline_comment|/* see if there is a keyboard in the device tree&n;&t;&t;&t;   with a parent of type &quot;adb&quot; */
r_for
c_loop
(paren
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;keyboard&quot;
)paren
suffix:semicolon
id|np
suffix:semicolon
id|np
op_assign
id|np-&gt;next
)paren
r_if
c_cond
(paren
id|np-&gt;parent
op_logical_and
id|np-&gt;parent-&gt;type
op_logical_and
id|strcmp
c_func
(paren
id|np-&gt;parent-&gt;type
comma
l_string|&quot;adb&quot;
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* needs to be hacked if xmon_printk is to be used&n;&t;&t;&t;   from within find_via_pmu() */
macro_line|#ifdef CONFIG_ADB_PMU
r_if
c_cond
(paren
id|np
op_ne
l_int|NULL
op_logical_and
id|boot_text_mapped
op_logical_and
id|find_via_pmu
c_func
(paren
)paren
)paren
id|use_screen
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ADB_CUDA
r_if
c_cond
(paren
id|np
op_ne
l_int|NULL
op_logical_and
id|boot_text_mapped
op_logical_and
id|find_via_cuda
c_func
(paren
)paren
)paren
id|use_screen
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
op_logical_neg
id|use_screen
op_logical_and
(paren
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;escc&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * look for the device node for the serial port&n;&t;&t;&t; * we&squot;re using and see if it says it has a modem&n;&t;&t;&t; */
r_char
op_star
id|name
op_assign
id|xmon_use_sccb
ques
c_cond
l_string|&quot;ch-b&quot;
suffix:colon
l_string|&quot;ch-a&quot;
suffix:semicolon
r_char
op_star
id|slots
suffix:semicolon
r_int
id|l
suffix:semicolon
id|np
op_assign
id|np-&gt;child
suffix:semicolon
r_while
c_loop
(paren
id|np
op_ne
l_int|NULL
op_logical_and
id|strcmp
c_func
(paren
id|np-&gt;name
comma
id|name
)paren
op_ne
l_int|0
)paren
id|np
op_assign
id|np-&gt;sibling
suffix:semicolon
r_if
c_cond
(paren
id|np
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* XXX should parse this properly */
id|channel_node
op_assign
id|np
suffix:semicolon
id|slots
op_assign
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;slot-names&quot;
comma
op_amp
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slots
op_ne
l_int|NULL
op_logical_and
id|l
op_ge
l_int|10
op_logical_and
id|strcmp
c_func
(paren
id|slots
op_plus
l_int|4
comma
l_string|&quot;Modem&quot;
)paren
op_eq
l_int|0
)paren
id|via_modem
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|btext_drawstring
c_func
(paren
l_string|&quot;xmon uses &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_screen
)paren
id|btext_drawstring
c_func
(paren
l_string|&quot;screen and keyboard&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|via_modem
)paren
id|btext_drawstring
c_func
(paren
l_string|&quot;modem on &quot;
)paren
suffix:semicolon
id|btext_drawstring
c_func
(paren
id|xmon_use_sccb
ques
c_cond
l_string|&quot;printer&quot;
suffix:colon
l_string|&quot;modem&quot;
)paren
suffix:semicolon
id|btext_drawstring
c_func
(paren
l_string|&quot; port&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BOOTX_TEXT */
macro_line|#ifdef CHRP_ESCC
id|addr
op_assign
l_int|0xc1013020
suffix:semicolon
macro_line|#else
id|addr
op_assign
l_int|0xf3013020
suffix:semicolon
macro_line|#endif
id|TXRDY
op_assign
l_int|4
suffix:semicolon
id|RXRDY
op_assign
l_int|1
suffix:semicolon
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;mac-io&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_logical_and
id|np-&gt;n_addrs
)paren
id|addr
op_assign
id|np-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
op_plus
l_int|0x13020
suffix:semicolon
id|base
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ioremap
c_func
(paren
id|addr
op_amp
id|PAGE_MASK
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|sccc
op_assign
id|base
op_plus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|sccd
op_assign
id|sccc
op_plus
l_int|0x10
suffix:semicolon
)brace
r_else
(brace
id|base
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|isa_io_base
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_chrp
)paren
id|base
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ioremap
c_func
(paren
id|chrp_find_phys_io_base
c_func
(paren
)paren
comma
l_int|0x1000
)paren
suffix:semicolon
id|sccc
op_assign
id|base
op_plus
l_int|0x3fd
suffix:semicolon
id|sccd
op_assign
id|base
op_plus
l_int|0x3f8
suffix:semicolon
r_if
c_cond
(paren
id|xmon_use_sccb
)paren
(brace
id|sccc
op_sub_assign
l_int|0x100
suffix:semicolon
id|sccd
op_sub_assign
l_int|0x100
suffix:semicolon
)brace
id|TXRDY
op_assign
l_int|0x20
suffix:semicolon
id|RXRDY
op_assign
l_int|1
suffix:semicolon
id|DLAB
op_assign
l_int|0x80
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_GEMINI)
multiline_comment|/* should already be mapped by the kernel boot */
id|sccc
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
l_int|0xffeffb0d
suffix:semicolon
id|sccd
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
l_int|0xffeffb08
suffix:semicolon
id|TXRDY
op_assign
l_int|0x20
suffix:semicolon
id|RXRDY
op_assign
l_int|1
suffix:semicolon
id|DLAB
op_assign
l_int|0x80
suffix:semicolon
macro_line|#elif defined(CONFIG_405GP)
id|sccc
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
l_int|0xef600305
suffix:semicolon
id|sccd
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
l_int|0xef600300
suffix:semicolon
id|TXRDY
op_assign
l_int|0x20
suffix:semicolon
id|RXRDY
op_assign
l_int|1
suffix:semicolon
id|DLAB
op_assign
l_int|0x80
suffix:semicolon
macro_line|#endif /* platform */
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
id|__sysrq_put_key_op
c_func
(paren
l_char|&squot;x&squot;
comma
op_amp
id|sysrq_xmon_op
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|scc_initialized
r_static
r_int
id|scc_initialized
op_assign
l_int|0
suffix:semicolon
r_void
id|xmon_init_scc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cuda_poll
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|do_poll_adb
r_static
r_inline
r_void
id|do_poll_adb
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ADB_PMU
r_if
c_cond
(paren
id|sys_ctrler
op_eq
id|SYS_CTRLER_PMU
)paren
id|pmu_poll_adb
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ADB_PMU */
macro_line|#ifdef CONFIG_ADB_CUDA
r_if
c_cond
(paren
id|sys_ctrler
op_eq
id|SYS_CTRLER_CUDA
)paren
id|cuda_poll
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ADB_CUDA */
)brace
r_int
DECL|function|xmon_write
id|xmon_write
c_func
(paren
r_void
op_star
id|handle
comma
r_void
op_star
id|ptr
comma
r_int
id|nb
)paren
(brace
r_char
op_star
id|p
op_assign
id|ptr
suffix:semicolon
r_int
id|i
comma
id|c
comma
id|ct
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_static
r_int
r_int
id|xmon_write_lock
suffix:semicolon
r_int
id|lock_wait
op_assign
l_int|1000000
suffix:semicolon
r_int
id|locked
suffix:semicolon
r_while
c_loop
(paren
(paren
id|locked
op_assign
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|xmon_write_lock
)paren
)paren
op_ne
l_int|0
)paren
r_if
c_cond
(paren
op_decrement
id|lock_wait
op_eq
l_int|0
)paren
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BOOTX_TEXT
r_if
c_cond
(paren
id|use_screen
)paren
(brace
multiline_comment|/* write it on the screen */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nb
suffix:semicolon
op_increment
id|i
)paren
id|btext_drawchar
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|scc_initialized
)paren
id|xmon_init_scc
c_func
(paren
)paren
suffix:semicolon
id|ct
op_assign
l_int|0
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
id|nb
suffix:semicolon
op_increment
id|i
)paren
(brace
r_while
c_loop
(paren
(paren
op_star
id|sccc
op_amp
id|TXRDY
)paren
op_eq
l_int|0
)paren
id|do_poll_adb
c_func
(paren
)paren
suffix:semicolon
id|c
op_assign
id|p
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
op_logical_neg
id|ct
)paren
(brace
id|c
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
id|ct
op_assign
l_int|1
suffix:semicolon
op_decrement
id|i
suffix:semicolon
)brace
r_else
(brace
id|ct
op_assign
l_int|0
suffix:semicolon
)brace
id|buf_access
c_func
(paren
)paren
suffix:semicolon
op_star
id|sccd
op_assign
id|c
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|locked
)paren
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|xmon_write_lock
)paren
suffix:semicolon
macro_line|#endif
r_return
id|nb
suffix:semicolon
)brace
DECL|variable|xmon_wants_key
r_int
id|xmon_wants_key
suffix:semicolon
DECL|variable|xmon_adb_keycode
r_int
id|xmon_adb_keycode
suffix:semicolon
macro_line|#ifdef CONFIG_BOOTX_TEXT
DECL|variable|xmon_adb_shiftstate
r_static
r_int
id|xmon_adb_shiftstate
suffix:semicolon
DECL|variable|xmon_keytab
r_static
r_int
r_char
id|xmon_keytab
(braket
l_int|128
)braket
op_assign
l_string|&quot;asdfhgzxcv&bslash;000bqwer&quot;
multiline_comment|/* 0x00 - 0x0f */
l_string|&quot;yt123465=97-80]o&quot;
multiline_comment|/* 0x10 - 0x1f */
l_string|&quot;u[ip&bslash;rlj&squot;k;&bslash;&bslash;,/nm.&quot;
multiline_comment|/* 0x20 - 0x2f */
l_string|&quot;&bslash;t `&bslash;177&bslash;0&bslash;033&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
multiline_comment|/* 0x30 - 0x3f */
l_string|&quot;&bslash;0.&bslash;0*&bslash;0+&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0/&bslash;r&bslash;0-&bslash;0&quot;
multiline_comment|/* 0x40 - 0x4f */
l_string|&quot;&bslash;0&bslash;0000123456789&bslash;0&bslash;0&bslash;0&quot;
suffix:semicolon
multiline_comment|/* 0x50 - 0x5f */
DECL|variable|xmon_shift_keytab
r_static
r_int
r_char
id|xmon_shift_keytab
(braket
l_int|128
)braket
op_assign
l_string|&quot;ASDFHGZXCV&bslash;000BQWER&quot;
multiline_comment|/* 0x00 - 0x0f */
l_string|&quot;YT!@#$^%+(&amp;_*)}O&quot;
multiline_comment|/* 0x10 - 0x1f */
l_string|&quot;U{IP&bslash;rLJ&bslash;&quot;K:|&lt;?NM&gt;&quot;
multiline_comment|/* 0x20 - 0x2f */
l_string|&quot;&bslash;t ~&bslash;177&bslash;0&bslash;033&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
multiline_comment|/* 0x30 - 0x3f */
l_string|&quot;&bslash;0.&bslash;0*&bslash;0+&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0/&bslash;r&bslash;0-&bslash;0&quot;
multiline_comment|/* 0x40 - 0x4f */
l_string|&quot;&bslash;0&bslash;0000123456789&bslash;0&bslash;0&bslash;0&quot;
suffix:semicolon
multiline_comment|/* 0x50 - 0x5f */
r_static
r_int
DECL|function|xmon_get_adb_key
id|xmon_get_adb_key
c_func
(paren
r_void
)paren
(brace
r_int
id|k
comma
id|t
comma
id|on
suffix:semicolon
id|xmon_wants_key
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|xmon_adb_keycode
op_assign
op_minus
l_int|1
suffix:semicolon
id|t
op_assign
l_int|0
suffix:semicolon
id|on
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_decrement
id|t
OL
l_int|0
)paren
(brace
id|on
op_assign
l_int|1
op_minus
id|on
suffix:semicolon
id|btext_drawchar
c_func
(paren
id|on
ques
c_cond
l_int|0xdb
suffix:colon
l_int|0x20
)paren
suffix:semicolon
id|btext_drawchar
c_func
(paren
l_char|&squot;&bslash;b&squot;
)paren
suffix:semicolon
id|t
op_assign
l_int|200000
suffix:semicolon
)brace
id|do_poll_adb
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|xmon_adb_keycode
op_eq
op_minus
l_int|1
)paren
suffix:semicolon
id|k
op_assign
id|xmon_adb_keycode
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
id|btext_drawstring
c_func
(paren
l_string|&quot; &bslash;b&quot;
)paren
suffix:semicolon
multiline_comment|/* test for shift keys */
r_if
c_cond
(paren
(paren
id|k
op_amp
l_int|0x7f
)paren
op_eq
l_int|0x38
op_logical_or
(paren
id|k
op_amp
l_int|0x7f
)paren
op_eq
l_int|0x7b
)paren
(brace
id|xmon_adb_shiftstate
op_assign
(paren
id|k
op_amp
l_int|0x80
)paren
op_eq
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|k
op_ge
l_int|0x80
)paren
r_continue
suffix:semicolon
multiline_comment|/* ignore up transitions */
id|k
op_assign
(paren
id|xmon_adb_shiftstate
ques
c_cond
id|xmon_shift_keytab
suffix:colon
id|xmon_keytab
)paren
(braket
id|k
)braket
suffix:semicolon
r_if
c_cond
(paren
id|k
op_ne
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|xmon_wants_key
op_assign
l_int|0
suffix:semicolon
r_return
id|k
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BOOTX_TEXT */
r_int
DECL|function|xmon_read
id|xmon_read
c_func
(paren
r_void
op_star
id|handle
comma
r_void
op_star
id|ptr
comma
r_int
id|nb
)paren
(brace
r_char
op_star
id|p
op_assign
id|ptr
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_BOOTX_TEXT
r_if
c_cond
(paren
id|use_screen
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
id|nb
suffix:semicolon
op_increment
id|i
)paren
op_star
id|p
op_increment
op_assign
id|xmon_get_adb_key
c_func
(paren
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|scc_initialized
)paren
id|xmon_init_scc
c_func
(paren
)paren
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
id|nb
suffix:semicolon
op_increment
id|i
)paren
(brace
r_while
c_loop
(paren
(paren
op_star
id|sccc
op_amp
id|RXRDY
)paren
op_eq
l_int|0
)paren
id|do_poll_adb
c_func
(paren
)paren
suffix:semicolon
id|buf_access
c_func
(paren
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
op_star
id|sccd
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
r_int
DECL|function|xmon_read_poll
id|xmon_read_poll
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|sccc
op_amp
id|RXRDY
)paren
op_eq
l_int|0
)paren
(brace
id|do_poll_adb
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|buf_access
c_func
(paren
)paren
suffix:semicolon
r_return
op_star
id|sccd
suffix:semicolon
)brace
DECL|variable|scc_inittab
r_static
r_int
r_char
id|scc_inittab
(braket
)braket
op_assign
(brace
l_int|13
comma
l_int|0
comma
multiline_comment|/* set baud rate divisor */
l_int|12
comma
l_int|1
comma
l_int|14
comma
l_int|1
comma
multiline_comment|/* baud rate gen enable, src=rtxc */
l_int|11
comma
l_int|0x50
comma
multiline_comment|/* clocks = br gen */
l_int|5
comma
l_int|0xea
comma
multiline_comment|/* tx 8 bits, assert DTR &amp; RTS */
l_int|4
comma
l_int|0x46
comma
multiline_comment|/* x16 clock, 1 stop */
l_int|3
comma
l_int|0xc1
comma
multiline_comment|/* rx enable, 8 bits */
)brace
suffix:semicolon
r_void
DECL|function|xmon_init_scc
id|xmon_init_scc
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_chrp
)paren
(brace
id|sccd
(braket
l_int|3
)braket
op_assign
l_int|0x83
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* LCR = 8N1 + DLAB */
id|sccd
(braket
l_int|0
)braket
op_assign
l_int|12
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* DLL = 9600 baud */
id|sccd
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|sccd
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* FCR = 0 */
id|sccd
(braket
l_int|3
)braket
op_assign
l_int|3
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* LCR = 8N1 */
id|sccd
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* IER = 0 */
)brace
r_else
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
(brace
r_int
id|i
comma
id|x
suffix:semicolon
r_if
c_cond
(paren
id|channel_node
op_ne
l_int|0
)paren
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_SCC_ENABLE
comma
id|channel_node
comma
id|PMAC_SCC_ASYNC
op_or
id|PMAC_SCC_FLAG_XMON
comma
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Serial port locked ON by debugger !&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|via_modem
op_logical_and
id|channel_node
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|t0
suffix:semicolon
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_MODEM_ENABLE
comma
id|channel_node
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Modem powered up by debugger !&bslash;n&quot;
)paren
suffix:semicolon
id|t0
op_assign
id|readtb
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|readtb
c_func
(paren
)paren
op_minus
id|t0
OL
l_int|3
op_star
id|TB_SPEED
)paren
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* use the B channel if requested */
r_if
c_cond
(paren
id|xmon_use_sccb
)paren
(brace
id|sccc
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|sccc
op_amp
op_complement
l_int|0x20
)paren
suffix:semicolon
id|sccd
op_assign
id|sccc
op_plus
l_int|0x10
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|20000
suffix:semicolon
id|i
op_ne
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
(brace
id|x
op_assign
op_star
id|sccc
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
op_star
id|sccc
op_assign
l_int|9
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* reset A or B side */
op_star
id|sccc
op_assign
(paren
(paren
r_int
r_int
)paren
id|sccc
op_amp
l_int|0x20
)paren
ques
c_cond
l_int|0x80
suffix:colon
l_int|0x40
suffix:semicolon
id|eieio
c_func
(paren
)paren
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
r_sizeof
(paren
id|scc_inittab
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
op_star
id|sccc
op_assign
id|scc_inittab
(braket
id|i
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|scc_initialized
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|via_modem
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|xmon_write
c_func
(paren
l_int|NULL
comma
l_string|&quot;ATE1V1&bslash;r&quot;
comma
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xmon_expect
c_func
(paren
l_string|&quot;OK&quot;
comma
l_int|5
)paren
)paren
(brace
id|xmon_write
c_func
(paren
l_int|NULL
comma
l_string|&quot;ATA&bslash;r&quot;
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xmon_expect
c_func
(paren
l_string|&quot;CONNECT&quot;
comma
l_int|40
)paren
)paren
r_break
suffix:semicolon
)brace
id|xmon_write
c_func
(paren
l_int|NULL
comma
l_string|&quot;+++&quot;
comma
l_int|3
)paren
suffix:semicolon
id|xmon_expect
c_func
(paren
l_string|&quot;OK&quot;
comma
l_int|3
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#if 0
r_extern
r_int
(paren
op_star
id|prom_entry
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
r_int
id|xmon_exit
c_func
(paren
r_void
)paren
(brace
r_struct
id|prom_args
(brace
r_char
op_star
id|service
suffix:semicolon
)brace
id|args
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|args.service
op_assign
l_string|&quot;exit&quot;
suffix:semicolon
(paren
op_star
id|prom_entry
)paren
(paren
op_amp
id|args
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|variable|xmon_stdin
r_void
op_star
id|xmon_stdin
suffix:semicolon
DECL|variable|xmon_stdout
r_void
op_star
id|xmon_stdout
suffix:semicolon
DECL|variable|xmon_stderr
r_void
op_star
id|xmon_stderr
suffix:semicolon
r_void
DECL|function|xmon_init
id|xmon_init
c_func
(paren
r_void
)paren
(brace
)brace
r_int
DECL|function|xmon_putc
id|xmon_putc
c_func
(paren
r_int
id|c
comma
r_void
op_star
id|f
)paren
(brace
r_char
id|ch
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|xmon_putc
c_func
(paren
l_char|&squot;&bslash;r&squot;
comma
id|f
)paren
suffix:semicolon
r_return
id|xmon_write
c_func
(paren
id|f
comma
op_amp
id|ch
comma
l_int|1
)paren
op_eq
l_int|1
ques
c_cond
id|c
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|xmon_putchar
id|xmon_putchar
c_func
(paren
r_int
id|c
)paren
(brace
r_return
id|xmon_putc
c_func
(paren
id|c
comma
id|xmon_stdout
)paren
suffix:semicolon
)brace
r_int
DECL|function|xmon_fputs
id|xmon_fputs
c_func
(paren
r_char
op_star
id|str
comma
r_void
op_star
id|f
)paren
(brace
r_int
id|n
op_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
r_return
id|xmon_write
c_func
(paren
id|f
comma
id|str
comma
id|n
)paren
op_eq
id|n
ques
c_cond
l_int|0
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|xmon_readchar
id|xmon_readchar
c_func
(paren
r_void
)paren
(brace
r_char
id|ch
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_switch
c_cond
(paren
id|xmon_read
c_func
(paren
id|xmon_stdin
comma
op_amp
id|ch
comma
l_int|1
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
id|ch
suffix:semicolon
r_case
op_minus
l_int|1
suffix:colon
id|xmon_printf
c_func
(paren
l_string|&quot;read(stdin) returned -1&bslash;r&bslash;n&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
DECL|variable|line
r_static
r_char
id|line
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|lineptr
r_static
r_char
op_star
id|lineptr
suffix:semicolon
DECL|variable|lineleft
r_static
r_int
id|lineleft
suffix:semicolon
DECL|function|xmon_expect
r_int
id|xmon_expect
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
r_int
id|timeout
)paren
(brace
r_int
id|c
suffix:semicolon
r_int
r_int
id|t0
suffix:semicolon
id|timeout
op_mul_assign
id|TB_SPEED
suffix:semicolon
id|t0
op_assign
id|readtb
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|lineptr
op_assign
id|line
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|c
op_assign
id|xmon_read_poll
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|readtb
c_func
(paren
)paren
op_minus
id|t0
OG
id|timeout
)paren
r_return
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;&bslash;r&squot;
op_logical_and
id|lineptr
OL
op_amp
id|line
(braket
r_sizeof
(paren
id|line
)paren
op_minus
l_int|1
)braket
)paren
op_star
id|lineptr
op_increment
op_assign
id|c
suffix:semicolon
)brace
op_star
id|lineptr
op_assign
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|strstr
c_func
(paren
id|line
comma
id|str
)paren
op_eq
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|xmon_getchar
id|xmon_getchar
c_func
(paren
r_void
)paren
(brace
r_int
id|c
suffix:semicolon
r_if
c_cond
(paren
id|lineleft
op_eq
l_int|0
)paren
(brace
id|lineptr
op_assign
id|line
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|c
op_assign
id|xmon_readchar
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
op_minus
l_int|1
op_logical_or
id|c
op_eq
l_int|4
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;r&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
op_star
id|lineptr
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_int|0177
suffix:colon
r_case
l_char|&squot;&bslash;b&squot;
suffix:colon
r_if
c_cond
(paren
id|lineptr
OG
id|line
)paren
(brace
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;b&squot;
)paren
suffix:semicolon
id|xmon_putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;b&squot;
)paren
suffix:semicolon
op_decrement
id|lineptr
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;U&squot;
op_amp
l_int|0x1F
suffix:colon
r_while
c_loop
(paren
id|lineptr
OG
id|line
)paren
(brace
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;b&squot;
)paren
suffix:semicolon
id|xmon_putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;b&squot;
)paren
suffix:semicolon
op_decrement
id|lineptr
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|lineptr
op_ge
op_amp
id|line
(braket
r_sizeof
(paren
id|line
)paren
op_minus
l_int|1
)braket
)paren
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;a&squot;
)paren
suffix:semicolon
r_else
(brace
id|xmon_putchar
c_func
(paren
id|c
)paren
suffix:semicolon
op_star
id|lineptr
op_increment
op_assign
id|c
suffix:semicolon
)brace
)brace
)brace
id|lineleft
op_assign
id|lineptr
op_minus
id|line
suffix:semicolon
id|lineptr
op_assign
id|line
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lineleft
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_decrement
id|lineleft
suffix:semicolon
r_return
op_star
id|lineptr
op_increment
suffix:semicolon
)brace
r_char
op_star
DECL|function|xmon_fgets
id|xmon_fgets
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|nb
comma
r_void
op_star
id|f
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_int
id|c
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|str
suffix:semicolon
id|p
OL
id|str
op_plus
id|nb
op_minus
l_int|1
suffix:semicolon
)paren
(brace
id|c
op_assign
id|xmon_getchar
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|p
op_eq
id|str
)paren
r_return
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
)brace
op_star
id|p
op_assign
l_int|0
suffix:semicolon
r_return
id|str
suffix:semicolon
)brace
r_void
DECL|function|xmon_enter
id|xmon_enter
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ADB_PMU
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
(brace
id|pmu_suspend
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_void
DECL|function|xmon_leave
id|xmon_leave
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ADB_PMU
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
(brace
id|pmu_resume
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
