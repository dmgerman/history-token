multiline_comment|/*&n; * $Id: edb7312.c,v 1.8 2003/05/21 12:45:18 dwmw2 Exp $&n; *&n; * Handle mapping of the NOR flash on Cogent EDB7312 boards&n; *&n; * Copyright 2002 SYSGO Real-Time Solutions GmbH&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_MTD_PARTITIONS
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#endif
DECL|macro|WINDOW_ADDR
mdefine_line|#define WINDOW_ADDR 0x00000000      /* physical properties of flash */
DECL|macro|WINDOW_SIZE
mdefine_line|#define WINDOW_SIZE 0x01000000
DECL|macro|BUSWIDTH
mdefine_line|#define BUSWIDTH    2
DECL|macro|FLASH_BLOCKSIZE_MAIN
mdefine_line|#define FLASH_BLOCKSIZE_MAIN&t;0x20000
DECL|macro|FLASH_NUMBLOCKS_MAIN
mdefine_line|#define FLASH_NUMBLOCKS_MAIN&t;128
multiline_comment|/* can be &quot;cfi_probe&quot;, &quot;jedec_probe&quot;, &quot;map_rom&quot;, 0 }; */
DECL|macro|PROBETYPES
mdefine_line|#define PROBETYPES { &quot;cfi_probe&quot;, 0 }
DECL|macro|MSG_PREFIX
mdefine_line|#define MSG_PREFIX &quot;EDB7312-NOR:&quot;   /* prefix for our printk()&squot;s */
DECL|macro|MTDID
mdefine_line|#define MTDID      &quot;edb7312-nor&quot;    /* for mtdparts= partitioning */
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
DECL|variable|edb7312nor_map
r_struct
id|map_info
id|edb7312nor_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;NOR flash on EDB7312&quot;
comma
dot
id|size
op_assign
id|WINDOW_SIZE
comma
dot
id|buswidth
op_assign
id|BUSWIDTH
comma
dot
id|phys
op_assign
id|WINDOW_ADDR
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_MTD_PARTITIONS
multiline_comment|/*&n; * MTD partitioning stuff &n; */
DECL|variable|static_partitions
r_static
r_struct
id|mtd_partition
id|static_partitions
(braket
l_int|3
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;ARMboot&quot;
comma
dot
id|size
op_assign
l_int|0x40000
comma
dot
id|offset
op_assign
l_int|0
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
l_int|0x200000
comma
dot
id|offset
op_assign
l_int|0x40000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;RootFS&quot;
comma
dot
id|size
op_assign
l_int|0xDC0000
comma
dot
id|offset
op_assign
l_int|0x240000
)brace
comma
)brace
suffix:semicolon
DECL|macro|NB_OF
mdefine_line|#define NB_OF(x) (sizeof (x) / sizeof (x[0]))
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
macro_line|#endif
DECL|variable|mtd_parts_nb
r_static
r_int
id|mtd_parts_nb
op_assign
l_int|0
suffix:semicolon
DECL|variable|mtd_parts
r_static
r_struct
id|mtd_partition
op_star
id|mtd_parts
op_assign
l_int|0
suffix:semicolon
DECL|function|init_edb7312nor
r_int
id|__init
id|init_edb7312nor
c_func
(paren
r_void
)paren
(brace
r_static
r_const
r_char
op_star
id|rom_probe_types
(braket
)braket
op_assign
id|PROBETYPES
suffix:semicolon
r_const
r_char
op_star
op_star
id|type
suffix:semicolon
r_const
r_char
op_star
id|part_type
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
id|MSG_PREFIX
l_string|&quot;0x%08x at 0x%08x&bslash;n&quot;
comma
id|WINDOW_SIZE
comma
id|WINDOW_ADDR
)paren
suffix:semicolon
id|edb7312nor_map.virt
op_assign
(paren
r_int
r_int
)paren
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
id|edb7312nor_map.virt
)paren
(brace
id|printk
c_func
(paren
id|MSG_PREFIX
l_string|&quot;failed to ioremap&bslash;n&quot;
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
id|edb7312nor_map
)paren
suffix:semicolon
id|mymtd
op_assign
l_int|0
suffix:semicolon
id|type
op_assign
id|rom_probe_types
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_logical_neg
id|mymtd
op_logical_and
op_star
id|type
suffix:semicolon
id|type
op_increment
)paren
(brace
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
op_star
id|type
comma
op_amp
id|edb7312nor_map
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
id|mtd_parts_nb
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
id|MTDID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtd_parts_nb
OG
l_int|0
)paren
id|part_type
op_assign
l_string|&quot;detected&quot;
suffix:semicolon
r_if
c_cond
(paren
id|mtd_parts_nb
op_eq
l_int|0
)paren
(brace
id|mtd_parts
op_assign
id|static_partitions
suffix:semicolon
id|mtd_parts_nb
op_assign
id|NB_OF
c_func
(paren
id|static_partitions
)paren
suffix:semicolon
id|part_type
op_assign
l_string|&quot;static&quot;
suffix:semicolon
)brace
macro_line|#endif
id|add_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtd_parts_nb
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_NOTICE
id|MSG_PREFIX
l_string|&quot;no partition info available&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
id|MSG_PREFIX
l_string|&quot;using %s partition definition&bslash;n&quot;
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
id|mtd_parts_nb
)paren
suffix:semicolon
)brace
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
id|edb7312nor_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|cleanup_edb7312nor
r_static
r_void
id|__exit
id|cleanup_edb7312nor
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
id|del_mtd_device
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
id|edb7312nor_map.virt
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|edb7312nor_map.virt
)paren
suffix:semicolon
id|edb7312nor_map.virt
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|init_edb7312nor
id|module_init
c_func
(paren
id|init_edb7312nor
)paren
suffix:semicolon
DECL|variable|cleanup_edb7312nor
id|module_exit
c_func
(paren
id|cleanup_edb7312nor
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
l_string|&quot;Marius Groeger &lt;mag@sysgo.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Generic configurable MTD map driver&quot;
)paren
suffix:semicolon
eof
