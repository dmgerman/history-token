multiline_comment|/*&n; * $Id: redwood.c,v 1.10 2004/11/04 13:24:15 gleixner Exp $&n; *&n; * drivers/mtd/maps/redwood.c&n; *&n; * FLASH map for the IBM Redwood 4/5/6 boards.&n; *&n; * Author: MontaVista Software, Inc. &lt;source@mvista.com&gt;&n; *&n; * 2001-2003 (c) MontaVista, Software, Inc. This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#if !defined (CONFIG_REDWOOD_6)
DECL|macro|WINDOW_ADDR
mdefine_line|#define WINDOW_ADDR 0xffc00000
DECL|macro|WINDOW_SIZE
mdefine_line|#define WINDOW_SIZE 0x00400000
DECL|macro|RW_PART0_OF
mdefine_line|#define RW_PART0_OF&t;0
DECL|macro|RW_PART0_SZ
mdefine_line|#define RW_PART0_SZ&t;0x10000
DECL|macro|RW_PART1_OF
mdefine_line|#define RW_PART1_OF&t;RW_PART0_SZ
DECL|macro|RW_PART1_SZ
mdefine_line|#define RW_PART1_SZ&t;0x200000 - 0x10000
DECL|macro|RW_PART2_OF
mdefine_line|#define RW_PART2_OF&t;0x200000
DECL|macro|RW_PART2_SZ
mdefine_line|#define RW_PART2_SZ&t;0x10000
DECL|macro|RW_PART3_OF
mdefine_line|#define RW_PART3_OF&t;0x210000
DECL|macro|RW_PART3_SZ
mdefine_line|#define RW_PART3_SZ&t;0x200000 - (0x10000 + 0x20000)
DECL|macro|RW_PART4_OF
mdefine_line|#define RW_PART4_OF&t;0x3e0000
DECL|macro|RW_PART4_SZ
mdefine_line|#define RW_PART4_SZ&t;0x20000
DECL|variable|redwood_flash_partitions
r_static
r_struct
id|mtd_partition
id|redwood_flash_partitions
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;Redwood OpenBIOS Vital Product Data&quot;
comma
dot
id|offset
op_assign
id|RW_PART0_OF
comma
dot
id|size
op_assign
id|RW_PART0_SZ
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
multiline_comment|/* force read-only */
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Redwood kernel&quot;
comma
dot
id|offset
op_assign
id|RW_PART1_OF
comma
dot
id|size
op_assign
id|RW_PART1_SZ
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Redwood OpenBIOS non-volatile storage&quot;
comma
dot
id|offset
op_assign
id|RW_PART2_OF
comma
dot
id|size
op_assign
id|RW_PART2_SZ
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
multiline_comment|/* force read-only */
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Redwood filesystem&quot;
comma
dot
id|offset
op_assign
id|RW_PART3_OF
comma
dot
id|size
op_assign
id|RW_PART3_SZ
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Redwood OpenBIOS&quot;
comma
dot
id|offset
op_assign
id|RW_PART4_OF
comma
dot
id|size
op_assign
id|RW_PART4_SZ
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
multiline_comment|/* force read-only */
)brace
)brace
suffix:semicolon
macro_line|#else /* CONFIG_REDWOOD_6 */
multiline_comment|/* FIXME: the window is bigger - armin */
DECL|macro|WINDOW_ADDR
mdefine_line|#define WINDOW_ADDR 0xff800000
DECL|macro|WINDOW_SIZE
mdefine_line|#define WINDOW_SIZE 0x00800000
DECL|macro|RW_PART0_OF
mdefine_line|#define RW_PART0_OF&t;0
DECL|macro|RW_PART0_SZ
mdefine_line|#define RW_PART0_SZ&t;0x400000&t;/* 4 MiB data */
DECL|macro|RW_PART1_OF
mdefine_line|#define RW_PART1_OF&t;RW_PART0_OF + RW_PART0_SZ 
DECL|macro|RW_PART1_SZ
mdefine_line|#define RW_PART1_SZ&t;0x10000&t;&t;/* 64K VPD */
DECL|macro|RW_PART2_OF
mdefine_line|#define RW_PART2_OF&t;RW_PART1_OF + RW_PART1_SZ
DECL|macro|RW_PART2_SZ
mdefine_line|#define RW_PART2_SZ&t;0x400000 - (0x10000 + 0x20000)
DECL|macro|RW_PART3_OF
mdefine_line|#define RW_PART3_OF&t;RW_PART2_OF + RW_PART2_SZ
DECL|macro|RW_PART3_SZ
mdefine_line|#define RW_PART3_SZ&t;0x20000
DECL|variable|redwood_flash_partitions
r_static
r_struct
id|mtd_partition
id|redwood_flash_partitions
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;Redwood filesystem&quot;
comma
dot
id|offset
op_assign
id|RW_PART0_OF
comma
dot
id|size
op_assign
id|RW_PART0_SZ
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Redwood OpenBIOS Vital Product Data&quot;
comma
dot
id|offset
op_assign
id|RW_PART1_OF
comma
dot
id|size
op_assign
id|RW_PART1_SZ
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
multiline_comment|/* force read-only */
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Redwood kernel&quot;
comma
dot
id|offset
op_assign
id|RW_PART2_OF
comma
dot
id|size
op_assign
id|RW_PART2_SZ
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Redwood OpenBIOS&quot;
comma
dot
id|offset
op_assign
id|RW_PART3_OF
comma
dot
id|size
op_assign
id|RW_PART3_SZ
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
multiline_comment|/* force read-only */
)brace
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_REDWOOD_6 */
DECL|variable|redwood_flash_map
r_struct
id|map_info
id|redwood_flash_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;IBM Redwood&quot;
comma
dot
id|size
op_assign
id|WINDOW_SIZE
comma
dot
id|bankwidth
op_assign
l_int|2
comma
dot
id|phys
op_assign
id|WINDOW_ADDR
comma
)brace
suffix:semicolon
DECL|macro|NUM_REDWOOD_FLASH_PARTITIONS
mdefine_line|#define NUM_REDWOOD_FLASH_PARTITIONS &bslash;&n;&t;(sizeof(redwood_flash_partitions)/sizeof(redwood_flash_partitions[0]))
DECL|variable|redwood_mtd
r_static
r_struct
id|mtd_info
op_star
id|redwood_mtd
suffix:semicolon
DECL|function|init_redwood_flash
r_int
id|__init
id|init_redwood_flash
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;redwood: flash mapping: %x at %x&bslash;n&quot;
comma
id|WINDOW_SIZE
comma
id|WINDOW_ADDR
)paren
suffix:semicolon
id|redwood_flash_map.virt
op_assign
id|ioremap
c_func
(paren
id|WINDOW_ADDR
comma
id|WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|redwood_flash_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;init_redwood_flash: failed to ioremap&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|simple_map_init
c_func
(paren
op_amp
id|redwood_flash_map
)paren
suffix:semicolon
id|redwood_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|redwood_flash_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|redwood_mtd
)paren
(brace
id|redwood_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_return
id|add_mtd_partitions
c_func
(paren
id|redwood_mtd
comma
id|redwood_flash_partitions
comma
id|NUM_REDWOOD_FLASH_PARTITIONS
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|cleanup_redwood_flash
r_static
r_void
id|__exit
id|cleanup_redwood_flash
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|redwood_mtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|redwood_mtd
)paren
suffix:semicolon
multiline_comment|/* moved iounmap after map_destroy - armin */
id|map_destroy
c_func
(paren
id|redwood_mtd
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|redwood_flash_map.virt
)paren
suffix:semicolon
)brace
)brace
DECL|variable|init_redwood_flash
id|module_init
c_func
(paren
id|init_redwood_flash
)paren
suffix:semicolon
DECL|variable|cleanup_redwood_flash
id|module_exit
c_func
(paren
id|cleanup_redwood_flash
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;MontaVista Software &lt;source@mvista.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for the IBM Redwood reference boards&quot;
)paren
suffix:semicolon
eof
