multiline_comment|/*&n; * Flash memory access on Hynix GMS30C7201/HMS30C7202 based &n; * evaluation boards&n; * &n; * $Id: h720x-flash.c,v 1.11 2004/11/04 13:24:14 gleixner Exp $&n; *&n; * (C) 2002 Jungjun Kim &lt;jungjun.kim@hynix.com&gt;&n; *     2003 Thomas Gleixner &lt;tglx@linutronix.de&gt;&t;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
DECL|variable|h720x_map
r_static
r_struct
id|map_info
id|h720x_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;H720X&quot;
comma
dot
id|bankwidth
op_assign
l_int|4
comma
dot
id|size
op_assign
id|FLASH_SIZE
comma
dot
id|phys
op_assign
id|FLASH_PHYS
comma
)brace
suffix:semicolon
DECL|variable|h720x_partitions
r_static
r_struct
id|mtd_partition
id|h720x_partitions
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;ArMon&quot;
comma
dot
id|size
op_assign
l_int|0x00080000
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Env&quot;
comma
dot
id|size
op_assign
l_int|0x00040000
comma
dot
id|offset
op_assign
l_int|0x00080000
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Kernel&quot;
comma
dot
id|size
op_assign
l_int|0x00180000
comma
dot
id|offset
op_assign
l_int|0x000c0000
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Ramdisk&quot;
comma
dot
id|size
op_assign
l_int|0x00400000
comma
dot
id|offset
op_assign
l_int|0x00240000
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;jffs2&quot;
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
)brace
)brace
suffix:semicolon
DECL|macro|NUM_PARTITIONS
mdefine_line|#define NUM_PARTITIONS  (sizeof(h720x_partitions)/sizeof(h720x_partitions[0]))
DECL|variable|nr_mtd_parts
r_static
r_int
id|nr_mtd_parts
suffix:semicolon
DECL|variable|mtd_parts
r_static
r_struct
id|mtd_partition
op_star
id|mtd_parts
suffix:semicolon
DECL|variable|probes
r_static
r_const
r_char
op_star
id|probes
(braket
)braket
op_assign
(brace
l_string|&quot;cmdlinepart&quot;
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialize FLASH support&n; */
DECL|function|h720x_mtd_init
r_int
id|__init
id|h720x_mtd_init
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|part_type
op_assign
l_int|NULL
suffix:semicolon
id|h720x_map.virt
op_assign
id|ioremap
c_func
(paren
id|FLASH_PHYS
comma
id|FLASH_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h720x_map.virt
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;H720x-MTD: ioremap failed&bslash;n&quot;
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
id|h720x_map
)paren
suffix:semicolon
singleline_comment|// Probe for flash bankwidth 4
id|printk
(paren
id|KERN_INFO
l_string|&quot;H720x-MTD probing 32bit FLASH&bslash;n&quot;
)paren
suffix:semicolon
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|h720x_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;H720x-MTD probing 16bit FLASH&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// Probe for bankwidth 2
id|h720x_map.bankwidth
op_assign
l_int|2
suffix:semicolon
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|h720x_map
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mymtd
)paren
(brace
id|mymtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
macro_line|#ifdef CONFIG_MTD_PARTITIONS
id|nr_mtd_parts
op_assign
id|parse_mtd_partitions
c_func
(paren
id|mymtd
comma
id|probes
comma
op_amp
id|mtd_parts
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_mtd_parts
OG
l_int|0
)paren
id|part_type
op_assign
l_string|&quot;command line&quot;
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|nr_mtd_parts
op_le
l_int|0
)paren
(brace
id|mtd_parts
op_assign
id|h720x_partitions
suffix:semicolon
id|nr_mtd_parts
op_assign
id|NUM_PARTITIONS
suffix:semicolon
id|part_type
op_assign
l_string|&quot;builtin&quot;
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Using %s partition table&bslash;n&quot;
comma
id|part_type
)paren
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|mymtd
comma
id|mtd_parts
comma
id|nr_mtd_parts
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|h720x_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/*&n; * Cleanup&n; */
DECL|function|h720x_mtd_cleanup
r_static
r_void
id|__exit
id|h720x_mtd_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|mymtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|mymtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|mymtd
)paren
suffix:semicolon
)brace
multiline_comment|/* Free partition info, if commandline partition was used */
r_if
c_cond
(paren
id|mtd_parts
op_logical_and
(paren
id|mtd_parts
op_ne
id|h720x_partitions
)paren
)paren
id|kfree
(paren
id|mtd_parts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h720x_map.virt
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|h720x_map.virt
)paren
suffix:semicolon
id|h720x_map.virt
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|h720x_mtd_init
id|module_init
c_func
(paren
id|h720x_mtd_init
)paren
suffix:semicolon
DECL|variable|h720x_mtd_cleanup
id|module_exit
c_func
(paren
id|h720x_mtd_cleanup
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
l_string|&quot;Thomas Gleixner &lt;tglx@linutronix.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for Hynix evaluation boards&quot;
)paren
suffix:semicolon
eof
