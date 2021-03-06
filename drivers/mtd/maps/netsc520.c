multiline_comment|/* netsc520.c -- MTD map driver for AMD NetSc520 Demonstration Board&n; *&n; * Copyright (C) 2001 Mark Langsdorf (mark.langsdorf@amd.com)&n; *&t;based on sc520cdp.c by Sysgo Real-Time Solutions GmbH&n; *&n; * $Id: netsc520.c,v 1.13 2004/11/28 09:40:40 dwmw2 Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA&n; *&n; * The NetSc520 is a demonstration board for the Elan Sc520 processor available&n; * from AMD.  It has a single back of 16 megs of 32-bit Flash ROM and another&n; * 16 megs of SDRAM.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
multiline_comment|/*&n;** The single, 16 megabyte flash bank is divided into four virtual&n;** partitions.  The first partition is 768 KiB and is intended to&n;** store the kernel image loaded by the bootstrap loader.  The second&n;** partition is 256 KiB and holds the BIOS image.  The third &n;** partition is 14.5 MiB and is intended for the flash file system&n;** image.  The last partition is 512 KiB and contains another copy&n;** of the BIOS image and the reset vector.&n;**&n;** Only the third partition should be mounted.  The first partition&n;** should not be mounted, but it can erased and written to using the&n;** MTD character routines.  The second and fourth partitions should&n;** not be touched - it is possible to corrupt the BIOS image by&n;** mounting these partitions, and potentially the board will not be&n;** recoverable afterwards.&n;*/
multiline_comment|/* partition_info gives details on the logical partitions that the split the &n; * single flash device into. If the size if zero we use up to the end of the&n; * device. */
DECL|variable|partition_info
r_static
r_struct
id|mtd_partition
id|partition_info
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|macro|NUM_PARTITIONS
mdefine_line|#define NUM_PARTITIONS (sizeof(partition_info)/sizeof(partition_info[0]))
DECL|macro|WINDOW_SIZE
mdefine_line|#define WINDOW_SIZE&t;0x00100000
DECL|macro|WINDOW_ADDR
mdefine_line|#define WINDOW_ADDR&t;0x00200000
DECL|variable|netsc520_map
r_static
r_struct
id|map_info
id|netsc520_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;netsc520 Flash Bank&quot;
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
DECL|macro|NUM_FLASH_BANKS
mdefine_line|#define NUM_FLASH_BANKS&t;(sizeof(netsc520_map)/sizeof(struct map_info))
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
DECL|function|init_netsc520
r_static
r_int
id|__init
id|init_netsc520
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;NetSc520 flash device: 0x%lx at 0x%lx&bslash;n&quot;
comma
id|netsc520_map.size
comma
id|netsc520_map.phys
)paren
suffix:semicolon
id|netsc520_map.virt
op_assign
id|ioremap_nocache
c_func
(paren
id|netsc520_map.phys
comma
id|netsc520_map.size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|netsc520_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to ioremap_nocache&bslash;n&quot;
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
id|netsc520_map
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
id|netsc520_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
(brace
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;map_ram&quot;
comma
op_amp
id|netsc520_map
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
(brace
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;map_rom&quot;
comma
op_amp
id|netsc520_map
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
(brace
id|iounmap
c_func
(paren
id|netsc520_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|mymtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
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
DECL|function|cleanup_netsc520
r_static
r_void
id|__exit
id|cleanup_netsc520
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
id|netsc520_map.virt
)paren
(brace
id|iounmap
c_func
(paren
id|netsc520_map.virt
)paren
suffix:semicolon
id|netsc520_map.virt
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|variable|init_netsc520
id|module_init
c_func
(paren
id|init_netsc520
)paren
suffix:semicolon
DECL|variable|cleanup_netsc520
id|module_exit
c_func
(paren
id|cleanup_netsc520
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
l_string|&quot;Mark Langsdorf &lt;mark.langsdorf@amd.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for AMD NetSc520 Demonstration Board&quot;
)paren
suffix:semicolon
eof
