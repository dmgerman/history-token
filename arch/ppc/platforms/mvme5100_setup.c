multiline_comment|/*&n; * arch/ppc/platforms/mvme5100_setup.c&n; *&n; * Board setup routines for the Motorola MVME5100.&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &lt;platforms/mvme5100.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/pplus.h&gt;
r_extern
r_char
id|cmd_line
(braket
)braket
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_char
id|mvme5100_openpic_initsenses
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* 16: i8259 cascade (active high) */
l_int|1
comma
multiline_comment|/* 17: TL16C550 UART 1,2 */
l_int|1
comma
multiline_comment|/* 18: Enet 1 (front panel or P2) */
l_int|1
comma
multiline_comment|/* 19: Hawk Watchdog 1,2 */
l_int|1
comma
multiline_comment|/* 20: DS1621 thermal alarm */
l_int|1
comma
multiline_comment|/* 21: Universe II LINT0# */
l_int|1
comma
multiline_comment|/* 22: Universe II LINT1# */
l_int|1
comma
multiline_comment|/* 23: Universe II LINT2# */
l_int|1
comma
multiline_comment|/* 24: Universe II LINT3# */
l_int|1
comma
multiline_comment|/* 25: PMC1 INTA#, PMC2 INTB# */
l_int|1
comma
multiline_comment|/* 26: PMC1 INTB#, PMC2 INTC# */
l_int|1
comma
multiline_comment|/* 27: PMC1 INTC#, PMC2 INTD# */
l_int|1
comma
multiline_comment|/* 28: PMC1 INTD#, PMC2 INTA# */
l_int|1
comma
multiline_comment|/* 29: Enet 2 (front panel) */
l_int|1
comma
multiline_comment|/* 30: Abort Switch */
l_int|1
comma
multiline_comment|/* 31: RTC Alarm */
)brace
suffix:semicolon
r_static
r_void
id|__init
DECL|function|mvme5100_setup_arch
id|mvme5100_setup_arch
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
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;mvme5100_setup_arch: enter&quot;
comma
l_int|0
)paren
suffix:semicolon
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
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
macro_line|#ifdef&t;CONFIG_ROOT_NFS
id|ROOT_DEV
op_assign
id|Root_NFS
suffix:semicolon
macro_line|#else
id|ROOT_DEV
op_assign
id|Root_SDA2
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
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
l_string|&quot;mvme5100_setup_arch: find_bridges&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Setup PCI host bridge */
id|mvme5100_setup_bridge
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Find and map our OpenPIC */
id|pplus_mpic_init
c_func
(paren
id|MVME5100_PCI_MEM_OFFSET
)paren
suffix:semicolon
id|OpenPIC_InitSenses
op_assign
id|mvme5100_openpic_initsenses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
r_sizeof
(paren
id|mvme5100_openpic_initsenses
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;MVME5100 port (C) 2001 MontaVista Software, Inc. (source@mvista.com)&bslash;n&quot;
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
l_string|&quot;mvme5100_setup_arch: exit&quot;
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|mvme5100_init2
id|mvme5100_init2
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_MVME5100_IPMC761_PRESENT
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
l_int|0xc0
comma
l_int|0x20
comma
l_string|&quot;dma2&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Interrupt setup and service.&n; * Have MPIC on HAWK and cascaded 8259s on Winbond cascaded to MPIC.&n; */
r_static
r_void
id|__init
DECL|function|mvme5100_init_IRQ
id|mvme5100_init_IRQ
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_MVME5100_IPMC761_PRESENT
r_int
id|i
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
l_string|&quot;init_irq: enter&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MVME5100_IPMC761_PRESENT
id|openpic_init
c_func
(paren
l_int|1
comma
id|NUM_8259_INTERRUPTS
comma
l_int|NULL
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
(brace
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
)brace
id|i8259_init
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
macro_line|#else
id|openpic_init
c_func
(paren
l_int|1
comma
l_int|0
comma
l_int|NULL
comma
op_minus
l_int|1
)paren
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
l_string|&quot;init_irq: exit&quot;
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Set BAT 3 to map 0xf0000000 to end of physical memory space.&n; */
r_static
id|__inline__
r_void
DECL|function|mvme5100_set_bat
id|mvme5100_set_bat
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|bat3u
comma
id|bat3l
suffix:semicolon
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot; lis %0,0xf000&bslash;n &bslash;&n;&t;&t;  ori %1,%0,0x002a&bslash;n &bslash;&n;&t;&t;  ori %0,%0,0x1ffe&bslash;n &bslash;&n;&t;&t;  mtspr 0x21e,%0&bslash;n &bslash;&n;&t;&t;  mtspr 0x21f,%1&bslash;n &bslash;&n;&t;&t;  isync&bslash;n &bslash;&n;&t;&t;  sync &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|bat3u
)paren
comma
l_string|&quot;=r&quot;
(paren
id|bat3l
)paren
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
r_static
r_int
r_int
id|__init
DECL|function|mvme5100_find_end_of_memory
id|mvme5100_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
id|mvme5100_set_bat
c_func
(paren
)paren
suffix:semicolon
r_return
id|pplus_get_mem_size
c_func
(paren
id|MVME5100_HAWK_SMC_BASE
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|mvme5100_map_io
id|mvme5100_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
l_int|0xfe000000
comma
l_int|0xfe000000
comma
l_int|0x02000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|ioremap_base
op_assign
l_int|0xfe000000
suffix:semicolon
)brace
r_static
r_void
DECL|function|mvme5100_reset_board
id|mvme5100_reset_board
c_func
(paren
r_void
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Set exception prefix high - to the firmware */
id|_nmask_and_or_msr
c_func
(paren
l_int|0
comma
id|MSR_IP
)paren
suffix:semicolon
id|out_8
c_func
(paren
(paren
id|u_char
op_star
)paren
id|MVME5100_BOARD_MODRST_REG
comma
l_int|0x01
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|mvme5100_restart
id|mvme5100_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
r_volatile
id|ulong
id|i
op_assign
l_int|10000000
suffix:semicolon
id|mvme5100_reset_board
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
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
DECL|function|mvme5100_halt
id|mvme5100_halt
c_func
(paren
r_void
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|mvme5100_power_off
id|mvme5100_power_off
c_func
(paren
r_void
)paren
(brace
id|mvme5100_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|mvme5100_show_cpuinfo
id|mvme5100_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;vendor&bslash;t&bslash;t: Motorola&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: MVME5100&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
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
id|isa_io_base
op_assign
id|MVME5100_ISA_IO_BASE
suffix:semicolon
id|isa_mem_base
op_assign
id|MVME5100_ISA_MEM_BASE
suffix:semicolon
id|pci_dram_offset
op_assign
id|MVME5100_PCI_DRAM_OFFSET
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|mvme5100_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|mvme5100_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|mvme5100_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
id|ppc_md.init
op_assign
id|mvme5100_init2
suffix:semicolon
id|ppc_md.restart
op_assign
id|mvme5100_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|mvme5100_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|mvme5100_halt
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|mvme5100_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|mvme5100_map_io
suffix:semicolon
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_MK48T37
comma
id|MVME5100_NVRAM_AS0
comma
id|MVME5100_NVRAM_AS1
comma
id|MVME5100_NVRAM_DATA
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
id|ppc_md.progress
op_assign
l_int|NULL
suffix:semicolon
)brace
eof
