multiline_comment|/*&n; *  arch/ppc/platforms/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Adapted from &squot;alpha&squot; version by Gary Thomas&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; */
multiline_comment|/*&n; * bootup setup stuff..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/gg2.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hydra.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/btext.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/xmon.h&gt;
r_int
r_int
id|chrp_get_rtc_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|chrp_set_rtc_time
c_func
(paren
r_int
r_int
id|nowtime
)paren
suffix:semicolon
r_void
id|chrp_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|chrp_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|chrp_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|chrp_event_scan
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|rtas_display_progress
c_func
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|rtas_indicator_progress
c_func
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|btext_progress
c_func
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pmac_find_end_of_memory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|of_show_percpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * XXX this should be in xmon.h, but putting it there means xmon.h&n; * has to include &lt;linux/interrupt.h&gt; (to get irqreturn_t), which&n; * causes all sorts of problems.  -- paulus&n; */
r_extern
id|irqreturn_t
id|xmon_irq
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
r_extern
id|dev_t
id|boot_dev
suffix:semicolon
r_extern
id|PTE
op_star
id|Hash
comma
op_star
id|Hash_end
suffix:semicolon
r_extern
r_int
r_int
id|Hash_size
comma
id|Hash_mask
suffix:semicolon
r_extern
r_int
id|probingmem
suffix:semicolon
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|variable|max_width
r_static
r_int
id|max_width
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_struct
id|smp_ops_t
id|chrp_smp_ops
suffix:semicolon
macro_line|#endif
DECL|variable|gg2_memtypes
r_static
r_const
r_char
op_star
id|gg2_memtypes
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;FPM&quot;
comma
l_string|&quot;SDRAM&quot;
comma
l_string|&quot;EDO&quot;
comma
l_string|&quot;BEDO&quot;
)brace
suffix:semicolon
DECL|variable|gg2_cachesizes
r_static
r_const
r_char
op_star
id|gg2_cachesizes
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;256 KB&quot;
comma
l_string|&quot;512 KB&quot;
comma
l_string|&quot;1 MB&quot;
comma
l_string|&quot;Reserved&quot;
)brace
suffix:semicolon
DECL|variable|gg2_cachetypes
r_static
r_const
r_char
op_star
id|gg2_cachetypes
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;Asynchronous&quot;
comma
l_string|&quot;Reserved&quot;
comma
l_string|&quot;Flow-Through Synchronous&quot;
comma
l_string|&quot;Pipelined Synchronous&quot;
)brace
suffix:semicolon
DECL|variable|gg2_cachemodes
r_static
r_const
r_char
op_star
id|gg2_cachemodes
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;Disabled&quot;
comma
l_string|&quot;Write-Through&quot;
comma
l_string|&quot;Copy-Back&quot;
comma
l_string|&quot;Transparent Mode&quot;
)brace
suffix:semicolon
r_int
id|__chrp
DECL|function|chrp_show_cpuinfo
id|chrp_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
r_int
id|i
comma
id|sdramen
suffix:semicolon
r_int
r_int
id|t
suffix:semicolon
r_struct
id|device_node
op_star
id|root
suffix:semicolon
r_const
r_char
op_star
id|model
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|root
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|root
)paren
id|model
op_assign
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: CHRP %s&bslash;n&quot;
comma
id|model
)paren
suffix:semicolon
multiline_comment|/* longtrail (goldengate) stuff */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|model
comma
l_string|&quot;IBM,LongTrail&quot;
comma
l_int|13
)paren
)paren
(brace
multiline_comment|/* VLSI VAS96011/12 `Golden Gate 2&squot; */
multiline_comment|/* Memory banks */
id|sdramen
op_assign
(paren
id|in_le32
c_func
(paren
id|gg2_pci_config_base
op_plus
id|GG2_PCI_DRAM_CTRL
)paren
op_rshift
l_int|31
)paren
op_amp
l_int|1
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
(paren
id|sdramen
ques
c_cond
l_int|4
suffix:colon
l_int|6
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|t
op_assign
id|in_le32
c_func
(paren
id|gg2_pci_config_base
op_plus
id|GG2_PCI_DRAM_BANK0
op_plus
id|i
op_star
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|t
op_amp
l_int|1
)paren
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|t
op_rshift
l_int|8
)paren
op_amp
l_int|0x1f
)paren
(brace
r_case
l_int|0x1f
suffix:colon
id|model
op_assign
l_string|&quot;4 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1e
suffix:colon
id|model
op_assign
l_string|&quot;8 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1c
suffix:colon
id|model
op_assign
l_string|&quot;16 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x18
suffix:colon
id|model
op_assign
l_string|&quot;32 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x10
suffix:colon
id|model
op_assign
l_string|&quot;64 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00
suffix:colon
id|model
op_assign
l_string|&quot;128 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|model
op_assign
l_string|&quot;Reserved&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;memory bank %d&bslash;t: %s %s&bslash;n&quot;
comma
id|i
comma
id|model
comma
id|gg2_memtypes
(braket
id|sdramen
ques
c_cond
l_int|1
suffix:colon
(paren
(paren
id|t
op_rshift
l_int|1
)paren
op_amp
l_int|3
)paren
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* L2 cache */
id|t
op_assign
id|in_le32
c_func
(paren
id|gg2_pci_config_base
op_plus
id|GG2_PCI_CC_CTRL
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;board l2&bslash;t: %s %s (%s)&bslash;n&quot;
comma
id|gg2_cachesizes
(braket
(paren
id|t
op_rshift
l_int|7
)paren
op_amp
l_int|3
)braket
comma
id|gg2_cachetypes
(braket
(paren
id|t
op_rshift
l_int|2
)paren
op_amp
l_int|3
)braket
comma
id|gg2_cachemodes
(braket
id|t
op_amp
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Fixes for the National Semiconductor PC78308VUL SuperI/O&n; *&n; *  Some versions of Open Firmware incorrectly initialize the IRQ settings&n; *  for keyboard and mouse&n; */
DECL|function|sio_write
r_static
r_inline
r_void
id|__init
id|sio_write
c_func
(paren
id|u8
id|val
comma
id|u8
id|index
)paren
(brace
id|outb
c_func
(paren
id|index
comma
l_int|0x15c
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
comma
l_int|0x15d
)paren
suffix:semicolon
)brace
DECL|function|sio_read
r_static
r_inline
id|u8
id|__init
id|sio_read
c_func
(paren
id|u8
id|index
)paren
(brace
id|outb
c_func
(paren
id|index
comma
l_int|0x15c
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
l_int|0x15d
)paren
suffix:semicolon
)brace
DECL|function|sio_fixup_irq
r_static
r_void
id|__init
id|sio_fixup_irq
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|u8
id|device
comma
id|u8
id|level
comma
id|u8
id|type
)paren
(brace
id|u8
id|level0
comma
id|type0
comma
id|active
suffix:semicolon
multiline_comment|/* select logical device */
id|sio_write
c_func
(paren
id|device
comma
l_int|0x07
)paren
suffix:semicolon
id|active
op_assign
id|sio_read
c_func
(paren
l_int|0x30
)paren
suffix:semicolon
id|level0
op_assign
id|sio_read
c_func
(paren
l_int|0x70
)paren
suffix:semicolon
id|type0
op_assign
id|sio_read
c_func
(paren
l_int|0x71
)paren
suffix:semicolon
r_if
c_cond
(paren
id|level0
op_ne
id|level
op_logical_or
id|type0
op_ne
id|type
op_logical_or
op_logical_neg
id|active
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sio: %s irq level %d, type %d, %sactive: &quot;
l_string|&quot;remapping to level %d, type %d, active&bslash;n&quot;
comma
id|name
comma
id|level0
comma
id|type0
comma
op_logical_neg
id|active
ques
c_cond
l_string|&quot;in&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|level
comma
id|type
)paren
suffix:semicolon
id|sio_write
c_func
(paren
l_int|0x01
comma
l_int|0x30
)paren
suffix:semicolon
id|sio_write
c_func
(paren
id|level
comma
l_int|0x70
)paren
suffix:semicolon
id|sio_write
c_func
(paren
id|type
comma
l_int|0x71
)paren
suffix:semicolon
)brace
)brace
DECL|function|sio_init
r_static
r_void
id|__init
id|sio_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|root
suffix:semicolon
r_if
c_cond
(paren
(paren
id|root
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/&quot;
)paren
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
comma
l_string|&quot;IBM,LongTrail&quot;
comma
l_int|13
)paren
)paren
(brace
multiline_comment|/* logical device 0 (KBC/Keyboard) */
id|sio_fixup_irq
c_func
(paren
l_string|&quot;keyboard&quot;
comma
l_int|0
comma
l_int|1
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* select logical device 1 (KBC/Mouse) */
id|sio_fixup_irq
c_func
(paren
l_string|&quot;mouse&quot;
comma
l_int|1
comma
l_int|12
comma
l_int|2
)paren
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|chrp_setup_arch
id|chrp_setup_arch
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|device
suffix:semicolon
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* this is fine for chrp */
id|initrd_below_start_ok
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|initrd_start
)paren
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
r_else
macro_line|#endif
id|ROOT_DEV
op_assign
id|Root_SDA2
suffix:semicolon
multiline_comment|/* sda2 (sda1 is for the kernel) */
multiline_comment|/* Lookup PCI host bridges */
id|chrp_find_bridges
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_PPC64BRIDGE
multiline_comment|/*&n;&t; *  Temporary fixes for PCI devices.&n;&t; *  -- Geert&n;&t; */
id|hydra_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Mac I/O */
macro_line|#endif /* CONFIG_PPC64BRIDGE */
multiline_comment|/*&n;&t; *  Fix the Super I/O configuration&n;&t; */
id|sio_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Get the event scan rate for the rtas so we know how&n;&t; * often it expects a heartbeat. -- Cort&n;&t; */
r_if
c_cond
(paren
id|rtas_data
)paren
(brace
r_struct
id|property
op_star
id|p
suffix:semicolon
id|device
op_assign
id|find_devices
c_func
(paren
l_string|&quot;rtas&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|device-&gt;properties
suffix:semicolon
id|p
op_logical_and
id|strncmp
c_func
(paren
id|p-&gt;name
comma
l_string|&quot;rtas-event-scan-rate&quot;
comma
l_int|20
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_if
c_cond
(paren
id|p
op_logical_and
op_star
(paren
r_int
r_int
op_star
)paren
id|p-&gt;value
)paren
(brace
id|ppc_md.heartbeat
op_assign
id|chrp_event_scan
suffix:semicolon
id|ppc_md.heartbeat_reset
op_assign
(paren
id|HZ
op_div
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|p-&gt;value
)paren
op_star
l_int|30
)paren
op_minus
l_int|1
suffix:semicolon
id|ppc_md.heartbeat_count
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RTAS Event Scan Rate: %lu (%lu jiffies)&bslash;n&quot;
comma
op_star
(paren
r_int
r_int
op_star
)paren
id|p-&gt;value
comma
id|ppc_md.heartbeat_reset
)paren
suffix:semicolon
)brace
)brace
id|pci_create_OF_bus_map
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
id|__chrp
DECL|function|chrp_event_scan
id|chrp_event_scan
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|log
(braket
l_int|1024
)braket
suffix:semicolon
r_int
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX: we should loop until the hardware says no more error logs -- Cort */
id|call_rtas
c_func
(paren
l_string|&quot;event-scan&quot;
comma
l_int|4
comma
l_int|1
comma
op_amp
id|ret
comma
l_int|0xffffffff
comma
l_int|0
comma
id|__pa
c_func
(paren
id|log
)paren
comma
l_int|1024
)paren
suffix:semicolon
id|ppc_md.heartbeat_count
op_assign
id|ppc_md.heartbeat_reset
suffix:semicolon
)brace
r_void
id|__chrp
DECL|function|chrp_restart
id|chrp_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RTAS system-reboot returned %d&bslash;n&quot;
comma
id|call_rtas
c_func
(paren
l_string|&quot;system-reboot&quot;
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
r_void
id|__chrp
DECL|function|chrp_power_off
id|chrp_power_off
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* allow power on only with power button press */
id|printk
c_func
(paren
l_string|&quot;RTAS power-off returned %d&bslash;n&quot;
comma
id|call_rtas
c_func
(paren
l_string|&quot;power-off&quot;
comma
l_int|2
comma
l_int|1
comma
l_int|NULL
comma
l_int|0xffffffff
comma
l_int|0xffffffff
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
r_void
id|__chrp
DECL|function|chrp_halt
id|chrp_halt
c_func
(paren
r_void
)paren
(brace
id|chrp_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
id|u_int
id|__chrp
DECL|function|chrp_irq_canonicalize
id|chrp_irq_canonicalize
c_func
(paren
id|u_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
op_eq
l_int|2
)paren
r_return
l_int|9
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
multiline_comment|/*&n; * Finds the open-pic node and sets OpenPIC_Addr based on its reg property.&n; * Then checks if it has an interrupt-ranges property.  If it does then&n; * we have a distributed open-pic, so call openpic_set_sources to tell&n; * the openpic code where to find the interrupt source registers.&n; */
DECL|function|chrp_find_openpic
r_static
r_void
id|__init
id|chrp_find_openpic
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_int
id|len
comma
id|i
suffix:semicolon
r_int
r_int
op_star
id|iranges
suffix:semicolon
r_void
op_star
id|isu
suffix:semicolon
id|np
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;open-pic&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
op_logical_or
id|np-&gt;n_addrs
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;OpenPIC at %x (size %x)&bslash;n&quot;
comma
id|np-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
id|np-&gt;addrs
(braket
l_int|0
)braket
dot
id|size
)paren
suffix:semicolon
id|OpenPIC_Addr
op_assign
id|ioremap
c_func
(paren
id|np-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
l_int|0x40000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|OpenPIC_Addr
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to map OpenPIC!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|iranges
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;interrupt-ranges&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iranges
op_eq
l_int|NULL
op_logical_or
id|len
OL
l_int|2
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* not distributed */
multiline_comment|/*&n;&t; * The first pair of cells in interrupt-ranges refers to the&n;&t; * IDU; subsequent pairs refer to the ISUs.&n;&t; */
id|len
op_div_assign
l_int|2
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;n_addrs
OL
id|len
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Insufficient addresses for distributed&quot;
l_string|&quot; OpenPIC (%d &lt; %d)&bslash;n&quot;
comma
id|np-&gt;n_addrs
comma
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iranges
(braket
l_int|1
)braket
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;OpenPIC irqs %d..%d in IDU&bslash;n&quot;
comma
id|iranges
(braket
l_int|0
)braket
comma
id|iranges
(braket
l_int|0
)braket
op_plus
id|iranges
(braket
l_int|1
)braket
op_minus
l_int|1
)paren
suffix:semicolon
id|openpic_set_sources
c_func
(paren
id|iranges
(braket
l_int|0
)braket
comma
id|iranges
(braket
l_int|1
)braket
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
op_increment
id|i
)paren
(brace
id|iranges
op_add_assign
l_int|2
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;OpenPIC irqs %d..%d in ISU at %x (%x)&bslash;n&quot;
comma
id|iranges
(braket
l_int|0
)braket
comma
id|iranges
(braket
l_int|0
)braket
op_plus
id|iranges
(braket
l_int|1
)braket
op_minus
l_int|1
comma
id|np-&gt;addrs
(braket
id|i
)braket
dot
id|address
comma
id|np-&gt;addrs
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
id|isu
op_assign
id|ioremap
c_func
(paren
id|np-&gt;addrs
(braket
id|i
)braket
dot
id|address
comma
id|np-&gt;addrs
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isu
op_ne
l_int|NULL
)paren
id|openpic_set_sources
c_func
(paren
id|iranges
(braket
l_int|0
)braket
comma
id|iranges
(braket
l_int|1
)braket
comma
id|isu
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to map OpenPIC ISU at %x!&bslash;n&quot;
comma
id|np-&gt;addrs
(braket
id|i
)braket
dot
id|address
)paren
suffix:semicolon
)brace
)brace
macro_line|#if defined(CONFIG_VT) &amp;&amp; defined(CONFIG_INPUT_ADBHID) &amp;&amp; defined(XMON)
DECL|variable|xmon_irqaction
r_static
r_struct
id|irqaction
id|xmon_irqaction
op_assign
(brace
dot
id|handler
op_assign
id|xmon_irq
comma
dot
id|mask
op_assign
id|CPU_MASK_NONE
comma
dot
id|name
op_assign
l_string|&quot;XMON break&quot;
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|chrp_init_IRQ
r_void
id|__init
id|chrp_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|chrp_int_ack
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|init_senses
(braket
id|NR_IRQS
op_minus
id|NUM_8259_INTERRUPTS
)braket
suffix:semicolon
macro_line|#if defined(CONFIG_VT) &amp;&amp; defined(CONFIG_INPUT_ADBHID) &amp;&amp; defined(XMON)
r_struct
id|device_node
op_star
id|kbd
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;pci&quot;
)paren
suffix:semicolon
id|np
op_ne
l_int|NULL
suffix:semicolon
id|np
op_assign
id|np-&gt;next
)paren
(brace
r_int
r_int
op_star
id|addrp
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;8259-interrupt-acknowledge&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addrp
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|chrp_int_ack
op_assign
id|addrp
(braket
id|prom_n_addr_cells
c_func
(paren
id|np
)paren
op_minus
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Cannot find PCI interrupt acknowledge address&bslash;n&quot;
)paren
suffix:semicolon
id|chrp_find_openpic
c_func
(paren
)paren
suffix:semicolon
id|prom_get_irq_senses
c_func
(paren
id|init_senses
comma
id|NUM_8259_INTERRUPTS
comma
id|NR_IRQS
)paren
suffix:semicolon
id|OpenPIC_InitSenses
op_assign
id|init_senses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
id|NR_IRQS
op_minus
id|NUM_8259_INTERRUPTS
suffix:semicolon
id|openpic_init
c_func
(paren
id|NUM_8259_INTERRUPTS
)paren
suffix:semicolon
multiline_comment|/* We have a cascade on OpenPIC IRQ 0, Linux IRQ 16 */
id|openpic_hookup_cascade
c_func
(paren
id|NUM_8259_INTERRUPTS
comma
l_string|&quot;82c59 cascade&quot;
comma
id|i8259_irq
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
id|NUM_8259_INTERRUPTS
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|i8259_pic
suffix:semicolon
id|i8259_init
c_func
(paren
id|chrp_int_ack
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_VT) &amp;&amp; defined(CONFIG_INPUT_ADBHID) &amp;&amp; defined(XMON)
multiline_comment|/* see if there is a keyboard in the device tree&n;&t;   with a parent of type &quot;adb&quot; */
r_for
c_loop
(paren
id|kbd
op_assign
id|find_devices
c_func
(paren
l_string|&quot;keyboard&quot;
)paren
suffix:semicolon
id|kbd
suffix:semicolon
id|kbd
op_assign
id|kbd-&gt;next
)paren
r_if
c_cond
(paren
id|kbd-&gt;parent
op_logical_and
id|kbd-&gt;parent-&gt;type
op_logical_and
id|strcmp
c_func
(paren
id|kbd-&gt;parent-&gt;type
comma
l_string|&quot;adb&quot;
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|kbd
)paren
id|setup_irq
c_func
(paren
id|HYDRA_INT_ADB_NMI
comma
op_amp
id|xmon_irqaction
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
id|__init
DECL|function|chrp_init2
id|chrp_init2
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_NVRAM
singleline_comment|// XX replace this in a more saner way
singleline_comment|//&t;pmac_nvram_init();
macro_line|#endif
id|request_region
c_func
(paren
l_int|0x20
comma
l_int|0x20
comma
l_string|&quot;pic1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xa0
comma
l_int|0x20
comma
l_string|&quot;pic2&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x00
comma
l_int|0x20
comma
l_string|&quot;dma1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x40
comma
l_int|0x20
comma
l_string|&quot;timer&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x80
comma
l_int|0x10
comma
l_string|&quot;dma page reg&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xc0
comma
l_int|0x20
comma
l_string|&quot;dma2&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;  Have fun!    &quot;
comma
l_int|0x7777
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|chrp_init
id|chrp_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* take care of initrd if we have one */
r_if
c_cond
(paren
id|r6
)paren
(brace
id|initrd_start
op_assign
id|r6
op_plus
id|KERNELBASE
suffix:semicolon
id|initrd_end
op_assign
id|r6
op_plus
id|r7
op_plus
id|KERNELBASE
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
id|ISA_DMA_THRESHOLD
op_assign
op_complement
l_int|0L
suffix:semicolon
id|DMA_MODE_READ
op_assign
l_int|0x44
suffix:semicolon
id|DMA_MODE_WRITE
op_assign
l_int|0x48
suffix:semicolon
id|isa_io_base
op_assign
id|CHRP_ISA_IO_BASE
suffix:semicolon
multiline_comment|/* default value */
id|ppc_md.setup_arch
op_assign
id|chrp_setup_arch
suffix:semicolon
id|ppc_md.show_percpuinfo
op_assign
id|of_show_percpuinfo
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|chrp_show_cpuinfo
suffix:semicolon
id|ppc_md.irq_canonicalize
op_assign
id|chrp_irq_canonicalize
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|chrp_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
id|ppc_md.init
op_assign
id|chrp_init2
suffix:semicolon
id|ppc_md.restart
op_assign
id|chrp_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|chrp_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|chrp_halt
suffix:semicolon
id|ppc_md.time_init
op_assign
id|chrp_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|chrp_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|chrp_get_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|chrp_calibrate_decr
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|pmac_find_end_of_memory
suffix:semicolon
r_if
c_cond
(paren
id|rtas_data
)paren
(brace
r_struct
id|device_node
op_star
id|rtas
suffix:semicolon
r_int
r_int
op_star
id|p
suffix:semicolon
id|rtas
op_assign
id|find_devices
c_func
(paren
l_string|&quot;rtas&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtas
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|get_property
c_func
(paren
id|rtas
comma
l_string|&quot;display-character&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|ppc_md.progress
op_assign
id|rtas_display_progress
suffix:semicolon
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
(paren
id|rtas
comma
l_string|&quot;ibm,display-line-length&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|max_width
op_assign
op_star
id|p
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|get_property
c_func
(paren
id|rtas
comma
l_string|&quot;set-indicator&quot;
comma
l_int|NULL
)paren
)paren
id|ppc_md.progress
op_assign
id|rtas_indicator_progress
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_BOOTX_TEXT
r_if
c_cond
(paren
id|ppc_md.progress
op_eq
l_int|NULL
op_logical_and
id|boot_text_mapped
)paren
id|ppc_md.progress
op_assign
id|btext_progress
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
id|ppc_md.smp_ops
op_assign
op_amp
id|chrp_smp_ops
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/*&n;&t; * Print the banner, then scroll down so boot progress&n;&t; * can be printed.  -- Cort&n;&t; */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;Linux/PPC &quot;
id|UTS_RELEASE
l_string|&quot;&bslash;n&quot;
comma
l_int|0x0
)paren
suffix:semicolon
)brace
r_void
id|__chrp
DECL|function|rtas_display_progress
id|rtas_display_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
(brace
r_int
id|width
suffix:semicolon
r_char
op_star
id|os
op_assign
id|s
suffix:semicolon
r_if
c_cond
(paren
id|call_rtas
c_func
(paren
l_string|&quot;display-character&quot;
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
l_char|&squot;&bslash;r&squot;
)paren
)paren
r_return
suffix:semicolon
id|width
op_assign
id|max_width
suffix:semicolon
r_while
c_loop
(paren
op_star
id|os
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|os
op_eq
l_char|&squot;&bslash;n&squot;
)paren
op_logical_or
(paren
op_star
id|os
op_eq
l_char|&squot;&bslash;r&squot;
)paren
)paren
id|width
op_assign
id|max_width
suffix:semicolon
r_else
id|width
op_decrement
suffix:semicolon
id|call_rtas
c_func
(paren
l_string|&quot;display-character&quot;
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
op_star
id|os
op_increment
)paren
suffix:semicolon
multiline_comment|/* if we overwrite the screen length */
r_if
c_cond
(paren
id|width
op_eq
l_int|0
)paren
r_while
c_loop
(paren
(paren
op_star
id|os
op_ne
l_int|0
)paren
op_logical_and
(paren
op_star
id|os
op_ne
l_char|&squot;&bslash;n&squot;
)paren
op_logical_and
(paren
op_star
id|os
op_ne
l_char|&squot;&bslash;r&squot;
)paren
)paren
id|os
op_increment
suffix:semicolon
)brace
multiline_comment|/*while ( width-- &gt; 0 )*/
id|call_rtas
c_func
(paren
l_string|&quot;display-character&quot;
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
r_void
id|__chrp
DECL|function|rtas_indicator_progress
id|rtas_indicator_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
(brace
id|call_rtas
c_func
(paren
l_string|&quot;set-indicator&quot;
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
l_int|6
comma
l_int|0
comma
id|hex
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BOOTX_TEXT
r_void
DECL|function|btext_progress
id|btext_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
(brace
id|prom_print
c_func
(paren
id|s
)paren
suffix:semicolon
id|prom_print
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BOOTX_TEXT */
eof
