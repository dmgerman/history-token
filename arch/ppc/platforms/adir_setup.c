multiline_comment|/*&n; * arch/ppc/platforms/adir_setup.c&n; *&n; * Board setup routines for SBS Adirondack&n; *&n; * By Michael Sokolov &lt;msokolov@ivan.Harhan.ORG&gt;&n; * based on the K2 version by Matt Porter &lt;mporter@mvista.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &quot;adir.h&quot;
r_extern
r_void
id|adir_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|adir_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|adir_find_bridges
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
DECL|variable|cpu_750cx
r_static
r_int
r_int
id|cpu_750cx
(braket
l_int|16
)braket
op_assign
(brace
l_int|5
comma
l_int|15
comma
l_int|14
comma
l_int|0
comma
l_int|4
comma
l_int|13
comma
l_int|0
comma
l_int|9
comma
l_int|6
comma
l_int|11
comma
l_int|8
comma
l_int|10
comma
l_int|16
comma
l_int|12
comma
l_int|7
comma
l_int|0
)brace
suffix:semicolon
r_static
r_int
DECL|function|adir_get_bus_speed
id|adir_get_bus_speed
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
(paren
(paren
id|u_char
op_star
)paren
id|ADIR_CLOCK_REG
)paren
op_amp
id|ADIR_CLOCK_REG_SEL133
)paren
)paren
r_return
l_int|100000000
suffix:semicolon
r_else
r_return
l_int|133333333
suffix:semicolon
)brace
r_static
r_int
DECL|function|adir_get_cpu_speed
id|adir_get_cpu_speed
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|hid1
suffix:semicolon
r_int
id|cpu_speed
suffix:semicolon
id|hid1
op_assign
id|mfspr
c_func
(paren
id|HID1
)paren
op_rshift
l_int|28
suffix:semicolon
id|hid1
op_assign
id|cpu_750cx
(braket
id|hid1
)braket
suffix:semicolon
id|cpu_speed
op_assign
id|adir_get_bus_speed
c_func
(paren
)paren
op_star
id|hid1
op_div
l_int|2
suffix:semicolon
r_return
id|cpu_speed
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|adir_calibrate_decr
id|adir_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
id|freq
comma
id|divisor
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* determine processor bus speed */
id|freq
op_assign
id|adir_get_bus_speed
c_func
(paren
)paren
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|freq
op_div
id|HZ
op_div
id|divisor
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|freq
op_div
id|divisor
comma
l_int|1000000
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|adir_show_cpuinfo
id|adir_show_cpuinfo
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
l_string|&quot;vendor&bslash;t&bslash;t: SBS&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: Adirondack&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu speed&bslash;t: %dMhz&bslash;n&quot;
comma
id|adir_get_cpu_speed
c_func
(paren
)paren
op_div
l_int|1000000
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;bus speed&bslash;t: %dMhz&bslash;n&quot;
comma
id|adir_get_bus_speed
c_func
(paren
)paren
op_div
l_int|1000000
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;memory type&bslash;t: SDRAM&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_char
id|cmd_line
(braket
)braket
suffix:semicolon
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|adir_setup_arch
id|adir_setup_arch
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cpu
suffix:semicolon
multiline_comment|/* Setup TODC access */
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_MC146818
comma
id|ADIR_NVRAM_RTC_ADDR
comma
l_int|0
comma
id|ADIR_NVRAM_RTC_DATA
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
suffix:semicolon
multiline_comment|/* Setup PCI host bridges */
id|adir_find_bridges
c_func
(paren
)paren
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
macro_line|#ifdef CONFIG_ROOT_NFS
id|ROOT_DEV
op_assign
id|Root_NFS
suffix:semicolon
macro_line|#else
id|ROOT_DEV
op_assign
id|Root_SDA1
suffix:semicolon
macro_line|#endif
multiline_comment|/* Identify the system */
id|printk
c_func
(paren
l_string|&quot;System Identification: SBS Adirondack - PowerPC 750CXe @ %d Mhz&bslash;n&quot;
comma
id|adir_get_cpu_speed
c_func
(paren
)paren
op_div
l_int|1000000
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SBS Adirondack port (C) 2001 SBS Technologies, Inc.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Identify the CPU manufacturer */
id|cpu
op_assign
id|mfspr
c_func
(paren
id|PVR
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU manufacturer: IBM [rev=%04x]&bslash;n&quot;
comma
(paren
id|cpu
op_amp
l_int|0xffff
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|adir_restart
id|adir_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* SRR0 has system reset vector, SRR1 has default MSR value */
multiline_comment|/* rfi restores MSR from SRR1 and sets the PC to the SRR0 value */
id|__asm__
id|__volatile__
(paren
l_string|&quot;lis&t;3,0xfff0&bslash;n&bslash;t&quot;
l_string|&quot;ori&t;3,3,0x0100&bslash;n&bslash;t&quot;
l_string|&quot;mtspr&t;26,3&bslash;n&bslash;t&quot;
l_string|&quot;li&t;3,0&bslash;n&bslash;t&quot;
l_string|&quot;mtspr&t;27,3&bslash;n&bslash;t&quot;
l_string|&quot;rfi&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|adir_power_off
id|adir_power_off
c_func
(paren
r_void
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|adir_halt
id|adir_halt
c_func
(paren
r_void
)paren
(brace
id|adir_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
id|__init
DECL|function|adir_find_end_of_memory
id|adir_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
r_return
id|boot_mem_size
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|adir_map_io
id|adir_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
id|ADIR_PCI32_VIRT_IO_BASE
comma
id|ADIR_PCI32_IO_BASE
comma
id|ADIR_PCI32_VIRT_IO_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
id|ADIR_PCI64_VIRT_IO_BASE
comma
id|ADIR_PCI64_IO_BASE
comma
id|ADIR_PCI64_VIRT_IO_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t; * On the Adirondack we use bi_recs and pass the pointer to them in R3.&n;&t; */
id|parse_bootinfo
c_func
(paren
(paren
r_struct
id|bi_record
op_star
)paren
(paren
id|r3
op_plus
id|KERNELBASE
)paren
)paren
suffix:semicolon
multiline_comment|/* Remember, isa_io_base is virtual but isa_mem_base is physical! */
id|isa_io_base
op_assign
id|ADIR_PCI32_VIRT_IO_BASE
suffix:semicolon
id|isa_mem_base
op_assign
id|ADIR_PCI32_MEM_BASE
suffix:semicolon
id|pci_dram_offset
op_assign
id|ADIR_PCI_SYS_MEM_BASE
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|adir_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|adir_show_cpuinfo
suffix:semicolon
id|ppc_md.irq_cannonicalize
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|adir_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|adir_get_irq
suffix:semicolon
id|ppc_md.init
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|adir_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|adir_map_io
suffix:semicolon
id|ppc_md.restart
op_assign
id|adir_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|adir_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|adir_halt
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
id|ppc_md.nvram_read_val
op_assign
id|todc_mc146818_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_mc146818_write_val
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|adir_calibrate_decr
suffix:semicolon
)brace
eof
