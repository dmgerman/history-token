multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * arch/sh64/mach-sim/setup.c&n; *&n; * ST50 Simulator Platform Support&n; *&n; * This file handles the architecture-dependent parts of initialization&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; *&n; * lethal@linux-sh.org:          15th May 2003&n; *    Use the generic procfs cpuinfo interface, just return a valid board name.&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/platform.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &quot;../rootfs/rootfs.h&quot;
macro_line|#endif
r_static
id|__init
r_void
id|platform_monitor
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|__init
r_void
id|platform_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|__init
r_void
id|platform_reserve
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|PHYS_MEMORY
mdefine_line|#define&t;PHYS_MEMORY&t;CONFIG_MEMORY_SIZE_IN_MB*1024*1024
macro_line|#if (PHYS_MEMORY &lt; P1SEG_FOOTPRINT_RAM)
macro_line|#error &quot;Invalid kernel configuration. Physical memory below footprint requirements.&quot;
macro_line|#endif
DECL|macro|RAM_DISK_START
mdefine_line|#define RAM_DISK_START&t;CONFIG_MEMORY_START+P1SEG_INITRD_BLOCK&t;/* Top of 4MB */
macro_line|#ifdef PLATFORM_ROMFS_SIZE
DECL|macro|RAM_DISK_SIZE
mdefine_line|#define&t;RAM_DISK_SIZE&t;(PAGE_ALIGN(PLATFORM_ROMFS_SIZE))     /* Variable Top */
macro_line|#if ((RAM_DISK_START + RAM_DISK_SIZE) &gt; (CONFIG_MEMORY_START + PHYS_MEMORY))
macro_line|#error &quot;Invalid kernel configuration. ROM RootFS exceeding physical memory.&quot;
macro_line|#endif
macro_line|#else
DECL|macro|RAM_DISK_SIZE
mdefine_line|#define RAM_DISK_SIZE&t;P1SEG_INITRD_BLOCK_SIZE&t;&t;&t;/* Top of 4MB */
macro_line|#endif
DECL|macro|RES_COUNT
mdefine_line|#define RES_COUNT(res) ((sizeof((res))/sizeof(struct resource)))
multiline_comment|/*&n; * Platform Dependent Interrupt Priorities.&n; */
multiline_comment|/* Using defaults defined in irq.h */
DECL|macro|RES
mdefine_line|#define&t;RES NO_PRIORITY&t;&t;/* Disabled */
DECL|macro|IR0
mdefine_line|#define IR0 IRL0_PRIORITY&t;/* IRLs */
DECL|macro|IR1
mdefine_line|#define IR1 IRL1_PRIORITY
DECL|macro|IR2
mdefine_line|#define IR2 IRL2_PRIORITY
DECL|macro|IR3
mdefine_line|#define IR3 IRL3_PRIORITY
DECL|macro|PCA
mdefine_line|#define PCA INTA_PRIORITY&t;/* PCI Ints */
DECL|macro|PCB
mdefine_line|#define PCB INTB_PRIORITY
DECL|macro|PCC
mdefine_line|#define PCC INTC_PRIORITY
DECL|macro|PCD
mdefine_line|#define PCD INTD_PRIORITY
DECL|macro|SER
mdefine_line|#define SER TOP_PRIORITY
DECL|macro|ERR
mdefine_line|#define ERR TOP_PRIORITY
DECL|macro|PW0
mdefine_line|#define PW0 TOP_PRIORITY
DECL|macro|PW1
mdefine_line|#define PW1 TOP_PRIORITY
DECL|macro|PW2
mdefine_line|#define PW2 TOP_PRIORITY
DECL|macro|PW3
mdefine_line|#define PW3 TOP_PRIORITY
DECL|macro|DM0
mdefine_line|#define DM0 NO_PRIORITY&t;&t;/* DMA Ints */
DECL|macro|DM1
mdefine_line|#define DM1 NO_PRIORITY
DECL|macro|DM2
mdefine_line|#define DM2 NO_PRIORITY
DECL|macro|DM3
mdefine_line|#define DM3 NO_PRIORITY
DECL|macro|DAE
mdefine_line|#define DAE NO_PRIORITY
DECL|macro|TU0
mdefine_line|#define TU0 TIMER_PRIORITY&t;/* TMU Ints */
DECL|macro|TU1
mdefine_line|#define TU1 NO_PRIORITY
DECL|macro|TU2
mdefine_line|#define TU2 NO_PRIORITY
DECL|macro|TI2
mdefine_line|#define TI2 NO_PRIORITY
DECL|macro|ATI
mdefine_line|#define ATI NO_PRIORITY&t;&t;/* RTC Ints */
DECL|macro|PRI
mdefine_line|#define PRI NO_PRIORITY
DECL|macro|CUI
mdefine_line|#define CUI RTC_PRIORITY
DECL|macro|ERI
mdefine_line|#define ERI SCIF_PRIORITY&t;/* SCIF Ints */
DECL|macro|RXI
mdefine_line|#define RXI SCIF_PRIORITY
DECL|macro|BRI
mdefine_line|#define BRI SCIF_PRIORITY
DECL|macro|TXI
mdefine_line|#define TXI SCIF_PRIORITY
DECL|macro|ITI
mdefine_line|#define ITI TOP_PRIORITY&t;/* WDT Ints */
multiline_comment|/*&n; * Platform dependent structures: maps and parms block.&n; */
DECL|variable|io_resources
r_struct
id|resource
id|io_resources
(braket
)braket
op_assign
(brace
multiline_comment|/* Nothing yet .. */
)brace
suffix:semicolon
DECL|variable|kram_resources
r_struct
id|resource
id|kram_resources
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;Kernel code&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* These must be last in the array */
(brace
l_string|&quot;Kernel data&quot;
comma
l_int|0
comma
l_int|0
)brace
multiline_comment|/* These must be last in the array */
)brace
suffix:semicolon
DECL|variable|xram_resources
r_struct
id|resource
id|xram_resources
(braket
)braket
op_assign
(brace
multiline_comment|/* Nothing yet .. */
)brace
suffix:semicolon
DECL|variable|rom_resources
r_struct
id|resource
id|rom_resources
(braket
)braket
op_assign
(brace
multiline_comment|/* Nothing yet .. */
)brace
suffix:semicolon
DECL|variable|platform_parms
r_struct
id|sh64_platform
id|platform_parms
op_assign
(brace
dot
id|readonly_rootfs
op_assign
l_int|1
comma
dot
id|initial_root_dev
op_assign
l_int|0x0100
comma
dot
id|loader_type
op_assign
l_int|1
comma
dot
id|initrd_start
op_assign
id|RAM_DISK_START
comma
dot
id|initrd_size
op_assign
id|RAM_DISK_SIZE
comma
dot
id|io_res_p
op_assign
id|io_resources
comma
dot
id|io_res_count
op_assign
id|RES_COUNT
c_func
(paren
id|io_resources
)paren
comma
dot
id|kram_res_p
op_assign
id|kram_resources
comma
dot
id|kram_res_count
op_assign
id|RES_COUNT
c_func
(paren
id|kram_resources
)paren
comma
dot
id|xram_res_p
op_assign
id|xram_resources
comma
dot
id|xram_res_count
op_assign
id|RES_COUNT
c_func
(paren
id|xram_resources
)paren
comma
dot
id|rom_res_p
op_assign
id|rom_resources
comma
dot
id|rom_res_count
op_assign
id|RES_COUNT
c_func
(paren
id|rom_resources
)paren
comma
)brace
suffix:semicolon
DECL|variable|platform_int_priority
r_int
id|platform_int_priority
(braket
id|NR_IRQS
)braket
op_assign
(brace
id|IR0
comma
id|IR1
comma
id|IR2
comma
id|IR3
comma
id|PCA
comma
id|PCB
comma
id|PCC
comma
id|PCD
comma
multiline_comment|/* IRQ  0- 7 */
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|SER
comma
id|ERR
comma
id|PW3
comma
id|PW2
comma
multiline_comment|/* IRQ  8-15 */
id|PW1
comma
id|PW0
comma
id|DM0
comma
id|DM1
comma
id|DM2
comma
id|DM3
comma
id|DAE
comma
id|RES
comma
multiline_comment|/* IRQ 16-23 */
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
multiline_comment|/* IRQ 24-31 */
id|TU0
comma
id|TU1
comma
id|TU2
comma
id|TI2
comma
id|ATI
comma
id|PRI
comma
id|CUI
comma
id|ERI
comma
multiline_comment|/* IRQ 32-39 */
id|RXI
comma
id|BRI
comma
id|TXI
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
multiline_comment|/* IRQ 40-47 */
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
multiline_comment|/* IRQ 48-55 */
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|RES
comma
id|ITI
comma
multiline_comment|/* IRQ 56-63 */
)brace
suffix:semicolon
DECL|function|platform_setup
r_void
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Simulator platform leaves the decision to head.S */
id|platform_parms.fpu_flags
op_assign
id|fpu_in_use
suffix:semicolon
)brace
DECL|function|platform_monitor
r_void
id|__init
id|platform_monitor
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing yet .. */
)brace
DECL|function|platform_reserve
r_void
id|__init
id|platform_reserve
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing yet .. */
)brace
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;SH-5 Simulator&quot;
suffix:semicolon
)brace
eof
