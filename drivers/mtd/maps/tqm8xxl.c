multiline_comment|/*&n; * Handle mapping of the flash memory access routines &n; * on TQM8xxL based devices.&n; *&n; * $Id: tqm8xxl.c,v 1.9 2003/06/23 11:48:18 dwmw2 Exp $&n; *&n; * based on rpxlite.c&n; *&n; * Copyright(C) 2001 Kirk Lee &lt;kirk@hpc.ee.ntu.edu.tw&gt;&n; *&n; * This code is GPLed&n; * &n; */
multiline_comment|/*&n; * According to TQM8xxL hardware manual, TQM8xxL series have&n; * following flash memory organisations:&n; *&t;| capacity |&t;| chip type |&t;| bank0 |&t;| bank1 |&n; *&t;    2MiB&t;   512Kx16&t;  2MiB&t;&t;   0&n; *&t;    4MiB&t;   1Mx16&t;  4MiB&t;&t;   0&n; *&t;    8MiB&t;   1Mx16&t;  4MiB&t;&t;   4MiB&n; * Thus, we choose CONFIG_MTD_CFI_I2 &amp; CONFIG_MTD_CFI_B4 at &n; * kernel configuration.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
DECL|macro|FLASH_ADDR
mdefine_line|#define FLASH_ADDR 0x40000000
DECL|macro|FLASH_SIZE
mdefine_line|#define FLASH_SIZE 0x00800000
DECL|macro|FLASH_BANK_MAX
mdefine_line|#define FLASH_BANK_MAX 4
singleline_comment|// trivial struct to describe partition information
DECL|struct|mtd_part_def
r_struct
id|mtd_part_def
(brace
DECL|member|nums
r_int
id|nums
suffix:semicolon
DECL|member|type
r_int
r_char
op_star
id|type
suffix:semicolon
DECL|member|mtd_part
r_struct
id|mtd_partition
op_star
id|mtd_part
suffix:semicolon
)brace
suffix:semicolon
singleline_comment|//static struct mtd_info *mymtd;
DECL|variable|mtd_banks
r_static
r_struct
id|mtd_info
op_star
id|mtd_banks
(braket
id|FLASH_BANK_MAX
)braket
suffix:semicolon
DECL|variable|map_banks
r_static
r_struct
id|map_info
op_star
id|map_banks
(braket
id|FLASH_BANK_MAX
)braket
suffix:semicolon
DECL|variable|part_banks
r_static
r_struct
id|mtd_part_def
id|part_banks
(braket
id|FLASH_BANK_MAX
)braket
suffix:semicolon
DECL|variable|num_banks
r_static
r_int
r_int
id|num_banks
suffix:semicolon
DECL|variable|start_scan_addr
r_static
r_int
r_int
id|start_scan_addr
suffix:semicolon
multiline_comment|/*&n; * Here are partition information for all known TQM8xxL series devices.&n; * See include/linux/mtd/partitions.h for definition of the mtd_partition&n; * structure.&n; * &n; * The *_max_flash_size is the maximum possible mapped flash size which&n; * is not necessarily the actual flash size.  It must correspond to the &n; * value specified in the mapping definition defined by the&n; * &quot;struct map_desc *_io_desc&quot; for the corresponding machine.&n; */
macro_line|#ifdef CONFIG_MTD_PARTITIONS
multiline_comment|/* Currently, TQM8xxL has upto 8MiB flash */
DECL|variable|tqm8xxl_max_flash_size
r_static
r_int
r_int
id|tqm8xxl_max_flash_size
op_assign
l_int|0x00800000
suffix:semicolon
multiline_comment|/* partition definition for first flash bank&n; * (cf. &quot;drivers/char/flash_config.c&quot;)&n; */
DECL|variable|tqm8xxl_partitions
r_static
r_struct
id|mtd_partition
id|tqm8xxl_partitions
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;ppcboot&quot;
comma
dot
id|offset
op_assign
l_int|0x00000000
comma
dot
id|size
op_assign
l_int|0x00020000
comma
multiline_comment|/* 128KB           */
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
comma
multiline_comment|/* force read-only */
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;kernel&quot;
comma
multiline_comment|/* default kernel image */
dot
id|offset
op_assign
l_int|0x00020000
comma
dot
id|size
op_assign
l_int|0x000e0000
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
comma
multiline_comment|/* force read-only */
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;user&quot;
comma
dot
id|offset
op_assign
l_int|0x00100000
comma
dot
id|size
op_assign
l_int|0x00100000
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;initrd&quot;
comma
dot
id|offset
op_assign
l_int|0x00200000
comma
dot
id|size
op_assign
l_int|0x00200000
comma
)brace
)brace
suffix:semicolon
multiline_comment|/* partition definition for second flash bank */
DECL|variable|tqm8xxl_fs_partitions
r_static
r_struct
id|mtd_partition
id|tqm8xxl_fs_partitions
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;cramfs&quot;
comma
dot
id|offset
op_assign
l_int|0x00000000
comma
dot
id|size
op_assign
l_int|0x00200000
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;jffs&quot;
comma
dot
id|offset
op_assign
l_int|0x00200000
comma
dot
id|size
op_assign
l_int|0x00200000
comma
dot
singleline_comment|//size = MTDPART_SIZ_FULL,
)brace
)brace
suffix:semicolon
macro_line|#endif
DECL|function|init_tqm_mtd
r_int
id|__init
id|init_tqm_mtd
c_func
(paren
r_void
)paren
(brace
r_int
id|idx
op_assign
l_int|0
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flash_addr
comma
id|flash_size
comma
id|mtd_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* pointer to TQM8xxL board info data */
id|bd_t
op_star
id|bd
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
id|flash_addr
op_assign
id|bd-&gt;bi_flashstart
suffix:semicolon
id|flash_size
op_assign
id|bd-&gt;bi_flashsize
suffix:semicolon
singleline_comment|//request maximum flash size address space
id|start_scan_addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|flash_addr
comma
id|flash_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|start_scan_addr
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s:Failed to ioremap address:0x%x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|flash_addr
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|FLASH_BANK_MAX
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mtd_size
op_ge
id|flash_size
)paren
(brace
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: chip probing count %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|idx
)paren
suffix:semicolon
id|map_banks
(braket
id|idx
)braket
op_assign
(paren
r_struct
id|map_info
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|map_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map_banks
(braket
id|idx
)braket
op_eq
l_int|NULL
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* FIXME: What if some MTD devices were probed already? */
r_goto
id|error_mem
suffix:semicolon
)brace
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|map_banks
(braket
id|idx
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|map_info
)paren
)paren
suffix:semicolon
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|name
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
l_int|16
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|name
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* FIXME: What if some MTD devices were probed already? */
r_goto
id|error_mem
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|name
comma
l_string|&quot;TQM8xxL%d&quot;
comma
id|idx
)paren
suffix:semicolon
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|size
op_assign
id|flash_size
suffix:semicolon
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|buswidth
op_assign
l_int|4
suffix:semicolon
id|simple_map_init
c_func
(paren
id|map_banks
(braket
id|idx
)braket
)paren
suffix:semicolon
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|virt
op_assign
id|start_scan_addr
suffix:semicolon
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|phys
op_assign
id|flash_addr
suffix:semicolon
multiline_comment|/* FIXME: This looks utterly bogus, but I&squot;m trying to&n;&t;&t;   preserve the behaviour of the original (shown here)...&n;&n;&t;&t;map_banks[idx]-&gt;map_priv_1 =&n;&t;&t;start_scan_addr + ((idx &gt; 0) ?&n;&t;&t;(mtd_banks[idx-1] ? mtd_banks[idx-1]-&gt;size : 0) : 0);&n;&t;&t;*/
r_if
c_cond
(paren
id|idx
op_logical_and
id|mtd_banks
(braket
id|idx
op_minus
l_int|1
)braket
)paren
(brace
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|virt
op_add_assign
id|mtd_banks
(braket
id|idx
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|size
suffix:semicolon
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|phys
op_add_assign
id|mtd_banks
(braket
id|idx
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|size
suffix:semicolon
)brace
singleline_comment|//start to probe flash chips
id|mtd_banks
(braket
id|idx
)braket
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
id|map_banks
(braket
id|idx
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtd_banks
(braket
id|idx
)braket
)paren
(brace
id|mtd_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|mtd_size
op_add_assign
id|mtd_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|size
suffix:semicolon
id|num_banks
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: bank%d, name:%s, size:%dbytes &bslash;n&quot;
comma
id|__FUNCTION__
comma
id|num_banks
comma
id|mtd_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|name
comma
id|mtd_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|size
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* no supported flash chips found */
r_if
c_cond
(paren
op_logical_neg
id|num_banks
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;TQM8xxL: No support flash chips found!&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_goto
id|error_mem
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MTD_PARTITIONS
multiline_comment|/*&n;&t; * Select Static partition definitions&n;&t; */
id|part_banks
(braket
l_int|0
)braket
dot
id|mtd_part
op_assign
id|tqm8xxl_partitions
suffix:semicolon
id|part_banks
(braket
l_int|0
)braket
dot
id|type
op_assign
l_string|&quot;Static image&quot;
suffix:semicolon
id|part_banks
(braket
l_int|0
)braket
dot
id|nums
op_assign
id|ARRAY_SIZE
c_func
(paren
id|tqm8xxl_partitions
)paren
suffix:semicolon
id|part_banks
(braket
l_int|1
)braket
dot
id|mtd_part
op_assign
id|tqm8xxl_fs_partitions
suffix:semicolon
id|part_banks
(braket
l_int|1
)braket
dot
id|type
op_assign
l_string|&quot;Static file system&quot;
suffix:semicolon
id|part_banks
(braket
l_int|1
)braket
dot
id|nums
op_assign
id|ARRAY_SIZE
c_func
(paren
id|tqm8xxl_fs_partitions
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|num_banks
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|part_banks
(braket
id|idx
)braket
dot
id|nums
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;TQM flash%d: no partition info available, registering whole flash at once&bslash;n&quot;
comma
id|idx
)paren
suffix:semicolon
id|add_mtd_device
c_func
(paren
id|mtd_banks
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;TQM flash%d: Using %s partition definition&bslash;n&quot;
comma
id|idx
comma
id|part_banks
(braket
id|idx
)braket
dot
id|type
)paren
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|mtd_banks
(braket
id|idx
)braket
comma
id|part_banks
(braket
id|idx
)braket
dot
id|mtd_part
comma
id|part_banks
(braket
id|idx
)braket
dot
id|nums
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;TQM flash: registering %d whole flash banks at once&bslash;n&quot;
comma
id|num_banks
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|num_banks
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|add_mtd_device
c_func
(paren
id|mtd_banks
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
id|error_mem
suffix:colon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|FLASH_BANK_MAX
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|map_banks
(braket
id|idx
)braket
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|name
op_ne
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|name
op_assign
l_int|NULL
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|map_banks
(braket
id|idx
)braket
)paren
suffix:semicolon
id|map_banks
(braket
id|idx
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|error
suffix:colon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|start_scan_addr
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cleanup_tqm_mtd
r_static
r_void
id|__exit
id|cleanup_tqm_mtd
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|idx
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|num_banks
suffix:semicolon
id|idx
op_increment
)paren
(brace
multiline_comment|/* destroy mtd_info previously allocated */
r_if
c_cond
(paren
id|mtd_banks
(braket
id|idx
)braket
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|mtd_banks
(braket
id|idx
)braket
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|mtd_banks
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* release map_info not used anymore */
id|kfree
c_func
(paren
id|map_banks
(braket
id|idx
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|map_banks
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|start_scan_addr
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|start_scan_addr
)paren
suffix:semicolon
id|start_scan_addr
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|init_tqm_mtd
id|module_init
c_func
(paren
id|init_tqm_mtd
)paren
suffix:semicolon
DECL|variable|cleanup_tqm_mtd
id|module_exit
c_func
(paren
id|cleanup_tqm_mtd
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
l_string|&quot;Kirk Lee &lt;kirk@hpc.ee.ntu.edu.tw&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for TQM8xxL boards&quot;
)paren
suffix:semicolon
eof
