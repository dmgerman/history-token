multiline_comment|/*&n; * arch/ppc/platforms/pplus_setup.c&n; *&n; * Board setup routines for MCG PowerPlus&n; *&n; * Author: Randy Vinson &lt;rvinson@mvista.com&gt;&n; *&n; * Derived from original PowerPlus PReP work by&n; * Cort Dougan, Johnnie Peters, Matt Porter, and&n; * Troy Benjegerdes.&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/mk48t59.h&gt;
macro_line|#include &lt;asm/prep_nvram.h&gt;
macro_line|#include &lt;asm/raven.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;asm/vga.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/pplus.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
DECL|macro|DUMP_DBATS
macro_line|#undef DUMP_DBATS
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_setkeycode
c_func
(paren
r_int
r_int
id|scancode
comma
r_int
r_int
id|keycode
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_translate
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
suffix:semicolon
r_extern
r_char
id|pckbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
suffix:semicolon
r_extern
r_void
id|pckbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|pckbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|pckbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
r_extern
r_void
id|pplus_setup_hose
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pplus_set_VIA_IDE_native
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
r_static
r_int
DECL|function|pplus_show_cpuinfo
id|pplus_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
r_extern
r_char
op_star
id|Motherboard_map_name
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;vendor&bslash;t&bslash;t: Motorola MCG&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: %s&bslash;n&quot;
comma
id|Motherboard_map_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pplus_setup_arch
id|pplus_setup_arch
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|reg
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
l_string|&quot;pplus_setup_arch: enter&bslash;n&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
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
l_string|&quot;pplus_setup_arch: find_bridges&bslash;n&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Setup PCI host bridge */
id|pplus_setup_hose
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Set up floppy in PS/2 mode */
id|outb
c_func
(paren
l_int|0x09
comma
id|SIO_CONFIG_RA
)paren
suffix:semicolon
id|reg
op_assign
id|inb
c_func
(paren
id|SIO_CONFIG_RD
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|reg
op_amp
l_int|0x3F
)paren
op_or
l_int|0x40
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|SIO_CONFIG_RD
)paren
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|SIO_CONFIG_RD
)paren
suffix:semicolon
multiline_comment|/* Have to write twice to change! */
multiline_comment|/* Enable L2.  Assume we don&squot;t need to flush -- Cort*/
op_star
(paren
r_int
r_char
op_star
)paren
(paren
l_int|0x8000081c
)paren
op_or_assign
l_int|3
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_start
)paren
id|ROOT_DEV
op_assign
id|MKDEV
c_func
(paren
id|RAMDISK_MAJOR
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* /dev/ram */
r_else
macro_line|#endif
macro_line|#ifdef CONFIG_ROOT_NFS
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x00ff
)paren
suffix:semicolon
multiline_comment|/* /dev/nfs */
macro_line|#else
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x0802
)paren
suffix:semicolon
multiline_comment|/* /dev/sda2 */
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;PowerPlus port (C) 2001 MontaVista Software, Inc. (source@mvista.com)&bslash;n&quot;
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
l_string|&quot;pplus_setup_arch: raven_init&bslash;n&quot;
comma
l_int|0
)paren
suffix:semicolon
id|raven_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VGA_CONSOLE
multiline_comment|/* remap the VGA memory */
id|vgacon_remap_base
op_assign
l_int|0xf0000000
suffix:semicolon
id|conswitchp
op_assign
op_amp
id|vga_con
suffix:semicolon
macro_line|#elif defined(CONFIG_DUMMY_CONSOLE)
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
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
l_string|&quot;pplus_setup_arch: exit&bslash;n&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|pplus_restart
id|pplus_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
r_int
r_int
id|i
op_assign
l_int|10000
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* set VIA IDE controller into native mode */
id|pplus_set_VIA_IDE_native
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* set exception prefix high - to the prom */
id|_nmask_and_or_msr
c_func
(paren
l_int|0
comma
id|MSR_IP
)paren
suffix:semicolon
multiline_comment|/* make sure bit 0 (reset) is a 0 */
id|outb
c_func
(paren
id|inb
c_func
(paren
l_int|0x92
)paren
op_amp
op_complement
l_int|1L
comma
l_int|0x92
)paren
suffix:semicolon
multiline_comment|/* signal a reset to system control port A - soft reset */
id|outb
c_func
(paren
id|inb
c_func
(paren
l_int|0x92
)paren
op_or
l_int|1
comma
l_int|0x92
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_ne
l_int|0
)paren
id|i
op_increment
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;restart failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|pplus_halt
id|pplus_halt
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* set exception prefix high - to the prom */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
op_or
id|MSR_IP
)paren
suffix:semicolon
multiline_comment|/* make sure bit 0 (reset) is a 0 */
id|outb
c_func
(paren
id|inb
c_func
(paren
l_int|0x92
)paren
op_amp
op_complement
l_int|1L
comma
l_int|0x92
)paren
suffix:semicolon
multiline_comment|/* signal a reset to system control port A - soft reset */
id|outb
c_func
(paren
id|inb
c_func
(paren
l_int|0x92
)paren
op_or
l_int|1
comma
l_int|0x92
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Not reached&n;&t; */
)brace
r_static
r_void
DECL|function|pplus_power_off
id|pplus_power_off
c_func
(paren
r_void
)paren
(brace
id|pplus_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|pplus_irq_cannonicalize
id|pplus_irq_cannonicalize
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
(brace
r_return
l_int|9
suffix:semicolon
)brace
r_else
(brace
r_return
id|irq
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|pplus_get_irq
id|pplus_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
id|i8259_poll
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pplus_init_IRQ
id|pplus_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|OpenPIC_Addr
op_ne
l_int|NULL
)paren
id|openpic_init
c_func
(paren
l_int|1
comma
id|NUM_8259_INTERRUPTS
comma
l_int|0
comma
op_minus
l_int|1
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
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
multiline_comment|/*&n; * IDE stuff.&n; */
r_static
r_int
DECL|function|pplus_ide_default_irq
id|pplus_ide_default_irq
c_func
(paren
id|ide_ioreg_t
id|base
)paren
(brace
r_switch
c_cond
(paren
id|base
)paren
(brace
r_case
l_int|0x1f0
suffix:colon
r_return
l_int|14
suffix:semicolon
r_case
l_int|0x170
suffix:colon
r_return
l_int|15
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_static
id|ide_ioreg_t
DECL|function|pplus_ide_default_io_base
id|pplus_ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_switch
c_cond
(paren
id|index
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|0x1f0
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
l_int|0x170
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_static
r_void
id|__init
DECL|function|pplus_ide_init_hwif_ports
id|pplus_ide_init_hwif_ports
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|data_port
comma
id|ide_ioreg_t
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
id|ide_ioreg_t
id|reg
op_assign
id|data_port
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IDE_DATA_OFFSET
suffix:semicolon
id|i
op_le
id|IDE_STATUS_OFFSET
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|reg
suffix:semicolon
id|reg
op_add_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctrl_port
)paren
(brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|ctrl_port
suffix:semicolon
)brace
r_else
(brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|hw-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_plus
l_int|0x206
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ne
l_int|NULL
)paren
op_star
id|irq
op_assign
id|pplus_ide_default_irq
c_func
(paren
id|data_port
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* PowerPlus (MTX) support */
r_static
r_int
id|__init
DECL|function|smp_pplus_probe
id|smp_pplus_probe
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|mot_multi
suffix:semicolon
r_if
c_cond
(paren
id|mot_multi
)paren
(brace
id|openpic_request_IPIs
c_func
(paren
)paren
suffix:semicolon
id|smp_hw_index
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|smp_pplus_kick_cpu
id|smp_pplus_kick_cpu
c_func
(paren
r_int
id|nr
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|KERNELBASE
op_assign
id|nr
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;dcbf 0,%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|KERNELBASE
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU1 reset, waiting&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|smp_pplus_setup_cpu
id|smp_pplus_setup_cpu
c_func
(paren
r_int
id|cpu_nr
)paren
(brace
r_if
c_cond
(paren
id|OpenPIC_Addr
)paren
id|do_openpic_setup_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|pplus_smp_ops
r_static
r_struct
id|smp_ops_t
id|pplus_smp_ops
op_assign
(brace
id|smp_openpic_message_pass
comma
id|smp_pplus_probe
comma
id|smp_pplus_kick_cpu
comma
id|smp_pplus_setup_cpu
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
macro_line|#ifdef DUMP_DBATS
DECL|function|print_dbat
r_static
r_void
id|print_dbat
c_func
(paren
r_int
id|idx
comma
id|u32
id|bat
)paren
(brace
r_char
id|str
(braket
l_int|64
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;DBAT%c%c = 0x%08x&bslash;n&quot;
comma
(paren
r_char
)paren
(paren
(paren
id|idx
op_minus
id|DBAT0U
)paren
op_div
l_int|2
)paren
op_plus
l_char|&squot;0&squot;
comma
(paren
id|idx
op_amp
l_int|1
)paren
ques
c_cond
l_char|&squot;L&squot;
suffix:colon
l_char|&squot;U&squot;
comma
id|bat
)paren
suffix:semicolon
id|ppc_md
dot
id|progress
c_func
(paren
id|str
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|macro|DUMP_DBAT
mdefine_line|#define DUMP_DBAT(x) &bslash;&n;&t;do { &bslash;&n;&t;u32 __temp = mfspr(x);&bslash;&n;&t;print_dbat(x, __temp); &bslash;&n;&t;} while (0)
DECL|function|dump_dbats
r_static
r_void
id|dump_dbats
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.progress
)paren
(brace
id|DUMP_DBAT
c_func
(paren
id|DBAT0U
)paren
suffix:semicolon
id|DUMP_DBAT
c_func
(paren
id|DBAT0L
)paren
suffix:semicolon
id|DUMP_DBAT
c_func
(paren
id|DBAT1U
)paren
suffix:semicolon
id|DUMP_DBAT
c_func
(paren
id|DBAT1L
)paren
suffix:semicolon
id|DUMP_DBAT
c_func
(paren
id|DBAT2U
)paren
suffix:semicolon
id|DUMP_DBAT
c_func
(paren
id|DBAT2L
)paren
suffix:semicolon
id|DUMP_DBAT
c_func
(paren
id|DBAT3U
)paren
suffix:semicolon
id|DUMP_DBAT
c_func
(paren
id|DBAT3L
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_static
r_int
r_int
id|__init
DECL|function|pplus_find_end_of_memory
id|pplus_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|total
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
l_string|&quot;pplus_find_end_of_memory&bslash;n&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef DUMP_DBATS
id|dump_dbats
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|total
op_assign
id|pplus_get_mem_size
c_func
(paren
l_int|0xfef80000
)paren
suffix:semicolon
r_return
(paren
id|total
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pplus_map_io
id|pplus_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
l_int|0x80000000
comma
l_int|0x80000000
comma
l_int|0x10000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
l_int|0xf0000000
comma
l_int|0xc0000000
comma
l_int|0x08000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pplus_init2
id|pplus_init2
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_NVRAM
id|request_region
c_func
(paren
id|PREP_NVRAM_AS0
comma
l_int|0x8
comma
l_string|&quot;nvram&quot;
)paren
suffix:semicolon
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
)brace
multiline_comment|/*&n; * Set BAT 2 to access 0x8000000 so progress messages will work and set BAT 3&n; * to 0xf0000000 to access Falcon/Raven or Hawk registers&n; */
r_static
id|__inline__
r_void
DECL|function|pplus_set_bat
id|pplus_set_bat
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|mapping_set
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapping_set
)paren
(brace
multiline_comment|/* wait for all outstanding memory accesses to complete */
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* setup DBATs */
id|mtspr
c_func
(paren
id|DBAT2U
comma
l_int|0x80001ffe
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|DBAT2L
comma
l_int|0x8000002a
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|DBAT3U
comma
l_int|0xf0001ffe
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|DBAT3L
comma
l_int|0xf000002a
)paren
suffix:semicolon
multiline_comment|/* wait for updates */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|mapping_set
op_assign
l_int|1
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
DECL|variable|rs_table
r_static
r_struct
id|serial_state
id|rs_table
(braket
id|RS_TABLE_SIZE
)braket
op_assign
(brace
id|SERIAL_PORT_DFNS
multiline_comment|/* Defined in &lt;asm/serial.h&gt; */
)brace
suffix:semicolon
r_void
DECL|function|pplus_progress
id|pplus_progress
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
r_volatile
r_char
id|c
suffix:semicolon
r_volatile
r_int
r_int
id|com_port
suffix:semicolon
id|u16
id|shift
suffix:semicolon
id|com_port
op_assign
id|rs_table
(braket
l_int|0
)braket
dot
id|port
op_plus
id|isa_io_base
suffix:semicolon
id|shift
op_assign
id|rs_table
(braket
l_int|0
)braket
dot
id|iomem_reg_shift
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_int|0
)paren
(brace
r_while
c_loop
(paren
(paren
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_plus
(paren
id|UART_LSR
op_lshift
id|shift
)paren
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
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
(brace
r_while
c_loop
(paren
(paren
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_plus
(paren
id|UART_LSR
op_lshift
id|shift
)paren
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif  /* CONFIG_SERIAL_TEXT_DEBUG */
r_void
id|__init
DECL|function|platform_init
id|platform_init
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
id|parse_bootinfo
c_func
(paren
id|find_bootinfo
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Map in board regs, etc. */
id|pplus_set_bat
c_func
(paren
)paren
suffix:semicolon
id|isa_io_base
op_assign
id|PREP_ISA_IO_BASE
suffix:semicolon
id|isa_mem_base
op_assign
id|PREP_ISA_MEM_BASE
suffix:semicolon
id|pci_dram_offset
op_assign
id|PREP_PCI_DRAM_OFFSET
suffix:semicolon
id|ISA_DMA_THRESHOLD
op_assign
l_int|0x00ffffff
suffix:semicolon
id|DMA_MODE_READ
op_assign
l_int|0x44
suffix:semicolon
id|DMA_MODE_WRITE
op_assign
l_int|0x48
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|pplus_setup_arch
suffix:semicolon
id|ppc_md.show_percpuinfo
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|pplus_show_cpuinfo
suffix:semicolon
id|ppc_md.irq_cannonicalize
op_assign
id|pplus_irq_cannonicalize
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|pplus_init_IRQ
suffix:semicolon
multiline_comment|/* this gets changed later on if we have an OpenPIC -- Cort */
id|ppc_md.get_irq
op_assign
id|pplus_get_irq
suffix:semicolon
id|ppc_md.init
op_assign
id|pplus_init2
suffix:semicolon
id|ppc_md.restart
op_assign
id|pplus_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|pplus_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|pplus_halt
suffix:semicolon
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_MK48T59
comma
id|PREP_NVRAM_AS0
comma
id|PREP_NVRAM_AS1
comma
id|PREP_NVRAM_DATA
comma
l_int|8
)paren
suffix:semicolon
id|ppc_md.time_init
op_assign
id|todc_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|todc_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|todc_get_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|todc_calibrate_decr
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_m48txx_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_m48txx_write_val
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|pplus_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|pplus_map_io
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.progress
op_assign
id|pplus_progress
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
id|ppc_ide_md.default_irq
op_assign
id|pplus_ide_default_irq
suffix:semicolon
id|ppc_ide_md.default_io_base
op_assign
id|pplus_ide_default_io_base
suffix:semicolon
id|ppc_ide_md.ide_init_hwif
op_assign
id|pplus_ide_init_hwif_ports
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
id|ppc_md.kbd_setkeycode
op_assign
id|pckbd_setkeycode
suffix:semicolon
id|ppc_md.kbd_getkeycode
op_assign
id|pckbd_getkeycode
suffix:semicolon
id|ppc_md.kbd_translate
op_assign
id|pckbd_translate
suffix:semicolon
id|ppc_md.kbd_unexpected_up
op_assign
id|pckbd_unexpected_up
suffix:semicolon
id|ppc_md.kbd_leds
op_assign
id|pckbd_leds
suffix:semicolon
id|ppc_md.kbd_init_hw
op_assign
id|pckbd_init_hw
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
id|ppc_md.ppc_kbd_sysrq_xlate
op_assign
id|pckbd_sysrq_xlate
suffix:semicolon
id|SYSRQ_KEY
op_assign
l_int|0x54
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
id|ppc_md.smp_ops
op_assign
op_amp
id|pplus_smp_ops
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
)brace
eof
