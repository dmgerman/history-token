multiline_comment|/*&n; * drivers/mtd/maps/svme182.c&n; * &n; * Flash map driver for the Dy4 SVME182 board&n; * &n; * $Id: dmv182.c,v 1.5 2004/11/04 13:24:14 gleixner Exp $&n; *&n; * Copyright 2003-2004, TimeSys Corporation&n; *&n; * Based on the SVME181 flash map, by Tom Nelson, Dot4, Inc. for TimeSys Corp.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/*&n; * This driver currently handles only the 16MiB user flash bank 1 on the&n; * board.  It does not provide access to bank 0 (contains the Dy4 FFW), bank 2&n; * (VxWorks boot), or the optional 48MiB expansion flash.&n; *&n; * scott.wood@timesys.com: On the newer boards with 128MiB flash, it&n; * now supports the first 96MiB (the boot flash bank containing FFW&n; * is excluded).  The VxWorks loader is in partition 1.&n; */
DECL|macro|FLASH_BASE_ADDR
mdefine_line|#define FLASH_BASE_ADDR 0xf0000000
DECL|macro|FLASH_BANK_SIZE
mdefine_line|#define FLASH_BANK_SIZE (128*1024*1024)
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Scott Wood, TimeSys Corporation &lt;scott.wood@timesys.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;User-programmable flash device on the Dy4 SVME182 board&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|svme182_map
r_static
r_struct
id|map_info
id|svme182_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Dy4 SVME182&quot;
comma
dot
id|bankwidth
op_assign
l_int|32
comma
dot
id|size
op_assign
l_int|128
op_star
l_int|1024
op_star
l_int|1024
)brace
suffix:semicolon
DECL|macro|BOOTIMAGE_PART_SIZE
mdefine_line|#define BOOTIMAGE_PART_SIZE&t;&t;((6*1024*1024)-RESERVED_PART_SIZE)
singleline_comment|// Allow 6MiB for the kernel
DECL|macro|NEW_BOOTIMAGE_PART_SIZE
mdefine_line|#define NEW_BOOTIMAGE_PART_SIZE  (6 * 1024 * 1024)
singleline_comment|// Allow 1MiB for the bootloader
DECL|macro|NEW_BOOTLOADER_PART_SIZE
mdefine_line|#define NEW_BOOTLOADER_PART_SIZE (1024 * 1024)
singleline_comment|// Use the remaining 9MiB at the end of flash for the RFS
DECL|macro|NEW_RFS_PART_SIZE
mdefine_line|#define NEW_RFS_PART_SIZE        (0x01000000 - NEW_BOOTLOADER_PART_SIZE - &bslash;&n;                                  NEW_BOOTIMAGE_PART_SIZE)
DECL|variable|svme182_partitions
r_static
r_struct
id|mtd_partition
id|svme182_partitions
(braket
)braket
op_assign
(brace
singleline_comment|// The Lower PABS is only 128KiB, but the partition code doesn&squot;t
singleline_comment|// like partitions that don&squot;t end on the largest erase block
singleline_comment|// size of the device, even if all of the erase blocks in the
singleline_comment|// partition are small ones.  The hardware should prevent
singleline_comment|// writes to the actual PABS areas.
(brace
id|name
suffix:colon
l_string|&quot;Lower PABS and CPU 0 bootloader or kernel&quot;
comma
id|size
suffix:colon
l_int|6
op_star
l_int|1024
op_star
l_int|1024
comma
id|offset
suffix:colon
l_int|0
comma
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;Root Filesystem&quot;
comma
id|size
suffix:colon
l_int|10
op_star
l_int|1024
op_star
l_int|1024
comma
id|offset
suffix:colon
id|MTDPART_OFS_NXTBLK
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;CPU1 Bootloader&quot;
comma
id|size
suffix:colon
l_int|1024
op_star
l_int|1024
comma
id|offset
suffix:colon
id|MTDPART_OFS_NXTBLK
comma
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;Extra&quot;
comma
id|size
suffix:colon
l_int|110
op_star
l_int|1024
op_star
l_int|1024
comma
id|offset
suffix:colon
id|MTDPART_OFS_NXTBLK
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;Foundation Firmware and Upper PABS&quot;
comma
id|size
suffix:colon
l_int|1024
op_star
l_int|1024
comma
id|offset
suffix:colon
id|MTDPART_OFS_NXTBLK
comma
id|mask_flags
suffix:colon
id|MTD_WRITEABLE
singleline_comment|// read-only
)brace
)brace
suffix:semicolon
DECL|variable|this_mtd
r_static
r_struct
id|mtd_info
op_star
id|this_mtd
suffix:semicolon
DECL|function|init_svme182
r_static
r_int
id|__init
id|init_svme182
c_func
(paren
r_void
)paren
(brace
r_struct
id|mtd_partition
op_star
id|partitions
suffix:semicolon
r_int
id|num_parts
op_assign
r_sizeof
(paren
id|svme182_partitions
)paren
op_div
r_sizeof
(paren
r_struct
id|mtd_partition
)paren
suffix:semicolon
id|partitions
op_assign
id|svme182_partitions
suffix:semicolon
id|svme182_map.virt
op_assign
id|ioremap
c_func
(paren
id|FLASH_BASE_ADDR
comma
id|svme182_map.size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|svme182_map.virt
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to ioremap FLASH memory area.&bslash;n&quot;
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
id|svme182_map
)paren
suffix:semicolon
id|this_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|svme182_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this_mtd
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|svme182_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;SVME182 flash device: %dMiB at 0x%08x&bslash;n&quot;
comma
id|this_mtd-&gt;size
op_rshift
l_int|20
comma
id|FLASH_BASE_ADDR
)paren
suffix:semicolon
id|this_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|this_mtd
comma
id|partitions
comma
id|num_parts
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_svme182
r_static
r_void
id|__exit
id|cleanup_svme182
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|this_mtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|this_mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|this_mtd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|svme182_map.virt
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|svme182_map.virt
)paren
suffix:semicolon
id|svme182_map.virt
op_assign
l_int|0
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|variable|init_svme182
id|module_init
c_func
(paren
id|init_svme182
)paren
suffix:semicolon
DECL|variable|cleanup_svme182
id|module_exit
c_func
(paren
id|cleanup_svme182
)paren
suffix:semicolon
eof
