multiline_comment|/*&n; * $Id: dbox2-flash.c,v 1.13 2004/11/04 13:24:14 gleixner Exp $&n; *&n; * D-Box 2 flash driver&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/* partition_info gives details on the logical partitions that the split the&n; * single flash device into. If the size if zero we use up to the end of the&n; * device. */
DECL|variable|partition_info
r_static
r_struct
id|mtd_partition
id|partition_info
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;BR bootloader&quot;
comma
dot
id|size
op_assign
l_int|128
op_star
l_int|1024
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
l_string|&quot;FLFS (U-Boot)&quot;
comma
dot
id|size
op_assign
l_int|128
op_star
l_int|1024
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
dot
id|mask_flags
op_assign
l_int|0
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Root (SquashFS)&quot;
comma
dot
id|size
op_assign
l_int|7040
op_star
l_int|1024
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
dot
id|mask_flags
op_assign
l_int|0
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;var (JFFS2)&quot;
comma
dot
id|size
op_assign
l_int|896
op_star
l_int|1024
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
dot
id|mask_flags
op_assign
l_int|0
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Flash without bootloader&quot;
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
comma
dot
id|offset
op_assign
l_int|128
op_star
l_int|1024
comma
dot
id|mask_flags
op_assign
l_int|0
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Complete Flash&quot;
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
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
)brace
suffix:semicolon
DECL|macro|NUM_PARTITIONS
mdefine_line|#define NUM_PARTITIONS (sizeof(partition_info) / sizeof(partition_info[0]))
DECL|macro|WINDOW_ADDR
mdefine_line|#define WINDOW_ADDR 0x10000000
DECL|macro|WINDOW_SIZE
mdefine_line|#define WINDOW_SIZE 0x800000
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
DECL|variable|dbox2_flash_map
r_struct
id|map_info
id|dbox2_flash_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;D-Box 2 flash memory&quot;
comma
dot
id|size
op_assign
id|WINDOW_SIZE
comma
dot
id|bankwidth
op_assign
l_int|4
comma
dot
id|phys
op_assign
id|WINDOW_ADDR
comma
)brace
suffix:semicolon
DECL|function|init_dbox2_flash
r_int
id|__init
id|init_dbox2_flash
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;D-Box 2 flash driver (size-&gt;0x%X mem-&gt;0x%X)&bslash;n&quot;
comma
id|WINDOW_SIZE
comma
id|WINDOW_ADDR
)paren
suffix:semicolon
id|dbox2_flash_map.virt
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
id|dbox2_flash_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to ioremap&bslash;n&quot;
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
id|dbox2_flash_map
)paren
suffix:semicolon
singleline_comment|// Probe for dual Intel 28F320 or dual AMD
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|dbox2_flash_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
(brace
singleline_comment|// Probe for single Intel 28F640
id|dbox2_flash_map.bankwidth
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
id|dbox2_flash_map
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
multiline_comment|/* Create MTD devices for each partition. */
id|add_mtd_partitions
c_func
(paren
id|mymtd
comma
id|partition_info
comma
id|NUM_PARTITIONS
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
id|dbox2_flash_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|cleanup_dbox2_flash
r_static
r_void
id|__exit
id|cleanup_dbox2_flash
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
r_if
c_cond
(paren
id|dbox2_flash_map.virt
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|dbox2_flash_map.virt
)paren
suffix:semicolon
id|dbox2_flash_map.virt
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|init_dbox2_flash
id|module_init
c_func
(paren
id|init_dbox2_flash
)paren
suffix:semicolon
DECL|variable|cleanup_dbox2_flash
id|module_exit
c_func
(paren
id|cleanup_dbox2_flash
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
l_string|&quot;K&#xfffd;ri Dav&#xfffd;&#xfffd;sson &lt;kd@flaga.is&gt;, Bastian Blank &lt;waldi@tuxbox.org&gt;, Alexander Wild &lt;wild@te-elektronik.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for D-Box 2 board&quot;
)paren
suffix:semicolon
eof
