multiline_comment|/*&n; * arch/ppc/platforms/pal4_setup.c&n; *&n; * Board setup routines for the SBS PalomarIV.&n; *&n; * Author: Dan Cox&n; *&n; * 2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;syslib/cpc700.h&gt;
macro_line|#include &quot;pal4.h&quot;
r_extern
r_void
id|pal4_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|cpc700_irq_assigns
r_int
r_int
id|cpc700_irq_assigns
(braket
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|1
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 0: ECC correctable error */
(brace
l_int|1
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 1: PCI write to memory range */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 2: PCI write to command register */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 3: UART 0 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 4: UART 1 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 5: ICC 0 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 6: ICC 1 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 7: GPT compare 0 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 8: GPT compare 1 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 9: GPT compare 2 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 10: GPT compare 3 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 11: GPT compare 4 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 12: GPT capture 0 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 13: GPT capture 1 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 14: GPT capture 2 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 15: GPT capture 3 */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 16: GPT capture 4 */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 17: reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 18: reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 19: reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 20: reserved */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 21: Ethernet */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 22: reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 23: reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 24: resreved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 25: reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 26: reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 27: reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 28: reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 29: reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 30: reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 31: reserved */
)brace
suffix:semicolon
r_static
r_int
DECL|function|pal4_show_cpuinfo
id|pal4_show_cpuinfo
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
l_string|&quot;board&bslash;t&bslash;t: SBS Palomar IV&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|pal4_restart
id|pal4_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lis  3,0xfff0&bslash;n &bslash;&n;                              ori  3,3,0x100&bslash;n &bslash;&n;                              mtspr 26,3&bslash;n &bslash;&n;                              li   3,0&bslash;n &bslash;&n;                              mtspr 27,3&bslash;n &bslash;&n;                              rfi&quot;
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
DECL|function|pal4_power_off
id|pal4_power_off
c_func
(paren
r_void
)paren
(brace
id|__cli
c_func
(paren
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
DECL|function|pal4_halt
id|pal4_halt
c_func
(paren
r_void
)paren
(brace
id|pal4_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|pal4_setup_arch
id|pal4_setup_arch
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|l2
suffix:semicolon
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_MK48T37
comma
l_int|0
comma
l_int|0
comma
id|ioremap
c_func
(paren
id|PAL4_NVRAM
comma
id|PAL4_NVRAM_SIZE
)paren
comma
l_int|8
)paren
suffix:semicolon
id|pal4_find_bridges
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
id|ROOT_DEV
op_assign
id|Root_NFS
suffix:semicolon
multiline_comment|/* The L2 gets disabled in the bootloader, but all the proper&n;&t;   bits should be present from the fw, so just re-enable it */
id|l2
op_assign
id|_get_L2CR
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|l2
op_amp
id|L2CR_L2E
)paren
)paren
(brace
multiline_comment|/* presume that it was initially set if the size is&n;&t;&t;   still present. */
r_if
c_cond
(paren
id|l2
op_xor
id|L2CR_L2SIZ_MASK
)paren
id|_set_L2CR
c_func
(paren
id|l2
op_or
id|L2CR_L2E
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;L2 not set by firmware; left disabled.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
id|__init
DECL|function|pal4_map_io
id|pal4_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
l_int|0xf0000000
comma
l_int|0xf0000000
comma
l_int|0x10000000
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
l_int|0
multiline_comment|/*PAL4_ISA_IO_BASE*/
suffix:semicolon
id|pci_dram_offset
op_assign
l_int|0
multiline_comment|/*PAL4_PCI_SYS_MEM_BASE*/
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|pal4_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|pal4_show_cpuinfo
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|pal4_map_io
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|cpc700_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|cpc700_get_irq
suffix:semicolon
id|ppc_md.restart
op_assign
id|pal4_restart
suffix:semicolon
id|ppc_md.halt
op_assign
id|pal4_halt
suffix:semicolon
id|ppc_md.power_off
op_assign
id|pal4_power_off
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
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
)brace
eof
