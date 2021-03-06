multiline_comment|/*&n; * $Id: lubbock-flash.c,v 1.19 2004/11/04 13:24:15 gleixner Exp $&n; *&n; * Map driver for the Lubbock developer platform.&n; *&n; * Author:&t;Nicolas Pitre&n; * Copyright:&t;(C) 2001 MontaVista Software Inc.&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/arch/pxa-regs.h&gt;
macro_line|#include &lt;asm/arch/lubbock.h&gt;
DECL|macro|ROM_ADDR
mdefine_line|#define ROM_ADDR&t;0x00000000
DECL|macro|FLASH_ADDR
mdefine_line|#define FLASH_ADDR&t;0x04000000
DECL|macro|WINDOW_SIZE
mdefine_line|#define WINDOW_SIZE &t;64*1024*1024
DECL|function|lubbock_map_inval_cache
r_static
r_void
id|lubbock_map_inval_cache
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|from
comma
id|ssize_t
id|len
)paren
(brace
id|consistent_sync
c_func
(paren
(paren
r_char
op_star
)paren
id|map-&gt;cached
op_plus
id|from
comma
id|len
comma
id|DMA_FROM_DEVICE
)paren
suffix:semicolon
)brace
DECL|variable|lubbock_maps
r_static
r_struct
id|map_info
id|lubbock_maps
(braket
l_int|2
)braket
op_assign
(brace
(brace
dot
id|size
op_assign
id|WINDOW_SIZE
comma
dot
id|phys
op_assign
l_int|0x00000000
comma
dot
id|inval_cache
op_assign
id|lubbock_map_inval_cache
comma
)brace
comma
(brace
dot
id|size
op_assign
id|WINDOW_SIZE
comma
dot
id|phys
op_assign
l_int|0x04000000
comma
dot
id|inval_cache
op_assign
id|lubbock_map_inval_cache
comma
)brace
)brace
suffix:semicolon
DECL|variable|lubbock_partitions
r_static
r_struct
id|mtd_partition
id|lubbock_partitions
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;Bootloader&quot;
comma
dot
id|size
op_assign
l_int|0x00040000
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
multiline_comment|/* force read-only */
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
l_int|0x00100000
comma
dot
id|offset
op_assign
l_int|0x00040000
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Filesystem&quot;
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
comma
dot
id|offset
op_assign
l_int|0x00140000
)brace
)brace
suffix:semicolon
DECL|variable|mymtds
r_static
r_struct
id|mtd_info
op_star
id|mymtds
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|parsed_parts
r_static
r_struct
id|mtd_partition
op_star
id|parsed_parts
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|nr_parsed_parts
r_static
r_int
id|nr_parsed_parts
(braket
l_int|2
)braket
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
l_string|&quot;RedBoot&quot;
comma
l_string|&quot;cmdlinepart&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|init_lubbock
r_static
r_int
id|__init
id|init_lubbock
c_func
(paren
r_void
)paren
(brace
r_int
id|flashboot
op_assign
(paren
id|LUB_CONF_SWITCHES
op_amp
l_int|1
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
comma
id|i
suffix:semicolon
id|lubbock_maps
(braket
l_int|0
)braket
dot
id|bankwidth
op_assign
id|lubbock_maps
(braket
l_int|1
)braket
dot
id|bankwidth
op_assign
(paren
id|BOOT_DEF
op_amp
l_int|1
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Compensate for the nROMBT switch which swaps the flash banks */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Lubbock configured to boot from %s (bank %d)&bslash;n&quot;
comma
id|flashboot
ques
c_cond
l_string|&quot;Flash&quot;
suffix:colon
l_string|&quot;ROM&quot;
comma
id|flashboot
)paren
suffix:semicolon
id|lubbock_maps
(braket
id|flashboot
op_xor
l_int|1
)braket
dot
id|name
op_assign
l_string|&quot;Lubbock Application Flash&quot;
suffix:semicolon
id|lubbock_maps
(braket
id|flashboot
)braket
dot
id|name
op_assign
l_string|&quot;Lubbock Boot ROM&quot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|lubbock_maps
(braket
id|i
)braket
dot
id|virt
op_assign
id|ioremap
c_func
(paren
id|lubbock_maps
(braket
id|i
)braket
dot
id|phys
comma
id|WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lubbock_maps
(braket
id|i
)braket
dot
id|virt
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Failed to ioremap %s&bslash;n&quot;
comma
id|lubbock_maps
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|lubbock_maps
(braket
id|i
)braket
dot
id|cached
op_assign
id|ioremap_cached
c_func
(paren
id|lubbock_maps
(braket
id|i
)braket
dot
id|phys
comma
id|WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lubbock_maps
(braket
id|i
)braket
dot
id|cached
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Failed to ioremap cached %s&bslash;n&quot;
comma
id|lubbock_maps
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|simple_map_init
c_func
(paren
op_amp
id|lubbock_maps
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Probing %s at physical address 0x%08lx (%d-bit bankwidth)&bslash;n&quot;
comma
id|lubbock_maps
(braket
id|i
)braket
dot
id|name
comma
id|lubbock_maps
(braket
id|i
)braket
dot
id|phys
comma
id|lubbock_maps
(braket
id|i
)braket
dot
id|bankwidth
op_star
l_int|8
)paren
suffix:semicolon
id|mymtds
(braket
id|i
)braket
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|lubbock_maps
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mymtds
(braket
id|i
)braket
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|lubbock_maps
(braket
id|i
)braket
dot
id|virt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lubbock_maps
(braket
id|i
)braket
dot
id|cached
)paren
id|iounmap
c_func
(paren
id|lubbock_maps
(braket
id|i
)braket
dot
id|cached
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|mymtds
(braket
id|i
)braket
op_member_access_from_pointer
id|owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|ret
op_assign
id|parse_mtd_partitions
c_func
(paren
id|mymtds
(braket
id|i
)braket
comma
id|probes
comma
op_amp
id|parsed_parts
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
id|nr_parsed_parts
(braket
id|i
)braket
op_assign
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mymtds
(braket
l_int|0
)braket
op_logical_and
op_logical_neg
id|mymtds
(braket
l_int|1
)braket
)paren
r_return
id|ret
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mymtds
(braket
id|i
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s is absent. Skipping&bslash;n&quot;
comma
id|lubbock_maps
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nr_parsed_parts
(braket
id|i
)braket
)paren
(brace
id|add_mtd_partitions
c_func
(paren
id|mymtds
(braket
id|i
)braket
comma
id|parsed_parts
(braket
id|i
)braket
comma
id|nr_parsed_parts
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Using static partitions on %s&bslash;n&quot;
comma
id|lubbock_maps
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|mymtds
(braket
id|i
)braket
comma
id|lubbock_partitions
comma
id|ARRAY_SIZE
c_func
(paren
id|lubbock_partitions
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Registering %s as whole device&bslash;n&quot;
comma
id|lubbock_maps
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|add_mtd_device
c_func
(paren
id|mymtds
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_lubbock
r_static
r_void
id|__exit
id|cleanup_lubbock
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mymtds
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|nr_parsed_parts
(braket
id|i
)braket
op_logical_or
op_logical_neg
id|i
)paren
id|del_mtd_partitions
c_func
(paren
id|mymtds
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|del_mtd_device
c_func
(paren
id|mymtds
(braket
id|i
)braket
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|mymtds
(braket
id|i
)braket
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|lubbock_maps
(braket
id|i
)braket
dot
id|virt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lubbock_maps
(braket
id|i
)braket
dot
id|cached
)paren
id|iounmap
c_func
(paren
id|lubbock_maps
(braket
id|i
)braket
dot
id|cached
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parsed_parts
(braket
id|i
)braket
)paren
id|kfree
c_func
(paren
id|parsed_parts
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|variable|init_lubbock
id|module_init
c_func
(paren
id|init_lubbock
)paren
suffix:semicolon
DECL|variable|cleanup_lubbock
id|module_exit
c_func
(paren
id|cleanup_lubbock
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
l_string|&quot;Nicolas Pitre &lt;nico@cam.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for Intel Lubbock&quot;
)paren
suffix:semicolon
eof
