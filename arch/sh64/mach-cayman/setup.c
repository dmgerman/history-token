multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * arch/sh64/mach-cayman/setup.c&n; *&n; * SH5 Cayman support&n; *&n; * This file handles the architecture-dependent parts of initialization&n; *&n; * Copyright David J. Mckay.&n; * Needs major work!&n; *&n; * benedict.gaster@superh.com:&t; 3rd May 2002&n; *    Added support for ramdisk, removing statically linked romfs at the same time.&n; *&n; * lethal@linux-sh.org:          15th May 2003&n; *    Use the generic procfs cpuinfo interface, just return a valid board name.&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/platform.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
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
multiline_comment|/* Setup for the SMSC FDC37C935 */
DECL|macro|SMSC_SUPERIO_BASE
mdefine_line|#define SMSC_SUPERIO_BASE&t;0x04000000
DECL|macro|SMSC_CONFIG_PORT_ADDR
mdefine_line|#define SMSC_CONFIG_PORT_ADDR&t;0x3f0
DECL|macro|SMSC_INDEX_PORT_ADDR
mdefine_line|#define SMSC_INDEX_PORT_ADDR&t;SMSC_CONFIG_PORT_ADDR
DECL|macro|SMSC_DATA_PORT_ADDR
mdefine_line|#define SMSC_DATA_PORT_ADDR&t;0x3f1
DECL|macro|SMSC_ENTER_CONFIG_KEY
mdefine_line|#define SMSC_ENTER_CONFIG_KEY&t;0x55
DECL|macro|SMSC_EXIT_CONFIG_KEY
mdefine_line|#define SMSC_EXIT_CONFIG_KEY&t;0xaa
DECL|macro|SMCS_LOGICAL_DEV_INDEX
mdefine_line|#define SMCS_LOGICAL_DEV_INDEX&t;0x07
DECL|macro|SMSC_DEVICE_ID_INDEX
mdefine_line|#define SMSC_DEVICE_ID_INDEX&t;0x20
DECL|macro|SMSC_DEVICE_REV_INDEX
mdefine_line|#define SMSC_DEVICE_REV_INDEX&t;0x21
DECL|macro|SMSC_ACTIVATE_INDEX
mdefine_line|#define SMSC_ACTIVATE_INDEX&t;0x30
DECL|macro|SMSC_PRIMARY_BASE_INDEX
mdefine_line|#define SMSC_PRIMARY_BASE_INDEX  0x60
DECL|macro|SMSC_SECONDARY_BASE_INDEX
mdefine_line|#define SMSC_SECONDARY_BASE_INDEX 0x62
DECL|macro|SMSC_PRIMARY_INT_INDEX
mdefine_line|#define SMSC_PRIMARY_INT_INDEX&t;0x70
DECL|macro|SMSC_SECONDARY_INT_INDEX
mdefine_line|#define SMSC_SECONDARY_INT_INDEX 0x72
DECL|macro|SMSC_IDE1_DEVICE
mdefine_line|#define SMSC_IDE1_DEVICE&t;1
DECL|macro|SMSC_KEYBOARD_DEVICE
mdefine_line|#define SMSC_KEYBOARD_DEVICE&t;7
DECL|macro|SMSC_CONFIG_REGISTERS
mdefine_line|#define SMSC_CONFIG_REGISTERS&t;8
DECL|macro|SMSC_SUPERIO_READ_INDEXED
mdefine_line|#define SMSC_SUPERIO_READ_INDEXED(index) ({ &bslash;&n;&t;outb((index), SMSC_INDEX_PORT_ADDR); &bslash;&n;&t;inb(SMSC_DATA_PORT_ADDR); })
DECL|macro|SMSC_SUPERIO_WRITE_INDEXED
mdefine_line|#define SMSC_SUPERIO_WRITE_INDEXED(val, index) ({ &bslash;&n;&t;outb((index), SMSC_INDEX_PORT_ADDR); &bslash;&n;&t;outb((val),   SMSC_DATA_PORT_ADDR); })
DECL|macro|IDE1_PRIMARY_BASE
mdefine_line|#define IDE1_PRIMARY_BASE&t;0x01f0
DECL|macro|IDE1_SECONDARY_BASE
mdefine_line|#define IDE1_SECONDARY_BASE&t;0x03f6
DECL|variable|smsc_superio_virt
r_int
r_int
id|smsc_superio_virt
suffix:semicolon
multiline_comment|/*&n; * Platform dependent structures: maps and parms block.&n; */
DECL|variable|io_resources
r_struct
id|resource
id|io_resources
(braket
)braket
op_assign
(brace
multiline_comment|/* To be updated with external devices */
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
multiline_comment|/* To be updated with external devices */
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
multiline_comment|/* To be updated with external devices */
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
id|io_res_p
op_assign
id|io_resources
comma
dot
id|io_res_count
op_assign
id|ARRAY_SIZE
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
id|ARRAY_SIZE
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
id|ARRAY_SIZE
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
id|ARRAY_SIZE
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
id|NR_INTC_IRQS
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
DECL|function|smsc_superio_setup
r_static
r_int
id|__init
id|smsc_superio_setup
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|devid
comma
id|devrev
suffix:semicolon
id|smsc_superio_virt
op_assign
id|onchip_remap
c_func
(paren
id|SMSC_SUPERIO_BASE
comma
l_int|1024
comma
l_string|&quot;SMSC SuperIO&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|smsc_superio_virt
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Unable to remap SMSC SuperIO&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Initially the chip is in run state */
multiline_comment|/* Put it into configuration state */
id|outb
c_func
(paren
id|SMSC_ENTER_CONFIG_KEY
comma
id|SMSC_CONFIG_PORT_ADDR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|SMSC_ENTER_CONFIG_KEY
comma
id|SMSC_CONFIG_PORT_ADDR
)paren
suffix:semicolon
multiline_comment|/* Read device ID info */
id|devid
op_assign
id|SMSC_SUPERIO_READ_INDEXED
c_func
(paren
id|SMSC_DEVICE_ID_INDEX
)paren
suffix:semicolon
id|devrev
op_assign
id|SMSC_SUPERIO_READ_INDEXED
c_func
(paren
id|SMSC_DEVICE_REV_INDEX
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SMSC SuperIO devid %02x rev %02x&bslash;n&quot;
comma
id|devid
comma
id|devrev
)paren
suffix:semicolon
multiline_comment|/* Select the keyboard device */
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
id|SMSC_KEYBOARD_DEVICE
comma
id|SMCS_LOGICAL_DEV_INDEX
)paren
suffix:semicolon
multiline_comment|/* enable it */
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
l_int|1
comma
id|SMSC_ACTIVATE_INDEX
)paren
suffix:semicolon
multiline_comment|/* Select the interrupts */
multiline_comment|/* On a PC keyboard is IRQ1, mouse is IRQ12 */
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
l_int|1
comma
id|SMSC_PRIMARY_INT_INDEX
)paren
suffix:semicolon
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
l_int|12
comma
id|SMSC_SECONDARY_INT_INDEX
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IDE
multiline_comment|/*&n;&t; * Only IDE1 exists on the Cayman&n;&t; */
multiline_comment|/* Power it on */
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
l_int|1
op_lshift
id|SMSC_IDE1_DEVICE
comma
l_int|0x22
)paren
suffix:semicolon
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
id|SMSC_IDE1_DEVICE
comma
id|SMCS_LOGICAL_DEV_INDEX
)paren
suffix:semicolon
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
l_int|1
comma
id|SMSC_ACTIVATE_INDEX
)paren
suffix:semicolon
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
id|IDE1_PRIMARY_BASE
op_rshift
l_int|8
comma
id|SMSC_PRIMARY_BASE_INDEX
op_plus
l_int|0
)paren
suffix:semicolon
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
id|IDE1_PRIMARY_BASE
op_amp
l_int|0xff
comma
id|SMSC_PRIMARY_BASE_INDEX
op_plus
l_int|1
)paren
suffix:semicolon
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
id|IDE1_SECONDARY_BASE
op_rshift
l_int|8
comma
id|SMSC_SECONDARY_BASE_INDEX
op_plus
l_int|0
)paren
suffix:semicolon
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
id|IDE1_SECONDARY_BASE
op_amp
l_int|0xff
comma
id|SMSC_SECONDARY_BASE_INDEX
op_plus
l_int|1
)paren
suffix:semicolon
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
l_int|14
comma
id|SMSC_PRIMARY_INT_INDEX
)paren
suffix:semicolon
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
id|SMSC_CONFIG_REGISTERS
comma
id|SMCS_LOGICAL_DEV_INDEX
)paren
suffix:semicolon
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
l_int|0x00
comma
l_int|0xc2
)paren
suffix:semicolon
multiline_comment|/* GP42 = nIDE1_OE */
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
l_int|0x01
comma
l_int|0xc5
)paren
suffix:semicolon
multiline_comment|/* GP45 = IDE1_IRQ */
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
l_int|0x00
comma
l_int|0xc6
)paren
suffix:semicolon
multiline_comment|/* GP46 = nIOROP */
id|SMSC_SUPERIO_WRITE_INDEXED
c_func
(paren
l_int|0x00
comma
l_int|0xc7
)paren
suffix:semicolon
multiline_comment|/* GP47 = nIOWOP */
macro_line|#endif
multiline_comment|/* Exit the configuraton state */
id|outb
c_func
(paren
id|SMSC_EXIT_CONFIG_KEY
comma
id|SMSC_CONFIG_PORT_ADDR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This is grotty, but, because kernel is always referenced on the link line&n; * before any devices, this is safe.&n; */
DECL|variable|smsc_superio_setup
id|__initcall
c_func
(paren
id|smsc_superio_setup
)paren
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
multiline_comment|/* Cayman platform leaves the decision to head.S, for now */
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
l_string|&quot;Hitachi Cayman&quot;
suffix:semicolon
)brace
eof
