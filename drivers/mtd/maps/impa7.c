multiline_comment|/*&n; * $Id: impa7.c,v 1.9 2003/06/23 11:47:43 dwmw2 Exp $&n; *&n; * Handle mapping of the NOR flash on implementa A7 boards&n; *&n; * Copyright 2002 SYSGO Real-Time Solutions GmbH&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
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
DECL|macro|WINDOW_ADDR0
mdefine_line|#define WINDOW_ADDR0 0x00000000      /* physical properties of flash */
DECL|macro|WINDOW_SIZE0
mdefine_line|#define WINDOW_SIZE0 0x00800000
DECL|macro|WINDOW_ADDR1
mdefine_line|#define WINDOW_ADDR1 0x10000000      /* physical properties of flash */
DECL|macro|WINDOW_SIZE1
mdefine_line|#define WINDOW_SIZE1 0x00800000
DECL|macro|NUM_FLASHBANKS
mdefine_line|#define NUM_FLASHBANKS 2
DECL|macro|BUSWIDTH
mdefine_line|#define BUSWIDTH     4
multiline_comment|/* can be { &quot;cfi_probe&quot;, &quot;jedec_probe&quot;, &quot;map_rom&quot;, 0 }; */
DECL|macro|PROBETYPES
mdefine_line|#define PROBETYPES { &quot;jedec_probe&quot;, 0 }
DECL|macro|MSG_PREFIX
mdefine_line|#define MSG_PREFIX &quot;impA7:&quot;   /* prefix for our printk()&squot;s */
DECL|macro|MTDID
mdefine_line|#define MTDID      &quot;impa7-%d&quot;  /* for mtdparts= partitioning */
DECL|variable|impa7_mtd
r_static
r_struct
id|mtd_info
op_star
id|impa7_mtd
(braket
id|NUM_FLASHBANKS
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|impa7_map
r_static
r_struct
id|map_info
id|impa7_map
(braket
id|NUM_FLASHBANKS
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;impA7 NOR Flash Bank #0&quot;
comma
dot
id|size
op_assign
id|WINDOW_SIZE0
comma
dot
id|buswidth
op_assign
id|BUSWIDTH
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;impA7 NOR Flash Bank #1&quot;
comma
dot
id|size
op_assign
id|WINDOW_SIZE1
comma
dot
id|buswidth
op_assign
id|BUSWIDTH
comma
)brace
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
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;FileSystem&quot;
comma
dot
id|size
op_assign
l_int|0x800000
comma
dot
id|offset
op_assign
l_int|0x00000000
)brace
comma
)brace
suffix:semicolon
DECL|variable|mtd_parts_nb
r_static
r_int
id|mtd_parts_nb
(braket
id|NUM_FLASHBANKS
)braket
suffix:semicolon
DECL|variable|mtd_parts
r_static
r_struct
id|mtd_partition
op_star
id|mtd_parts
(braket
id|NUM_FLASHBANKS
)braket
suffix:semicolon
macro_line|#endif
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
DECL|function|init_impa7
r_int
id|__init
id|init_impa7
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
r_int
id|i
suffix:semicolon
r_static
r_struct
(brace
id|u_long
id|addr
suffix:semicolon
id|u_long
id|size
suffix:semicolon
)brace
id|pt
(braket
id|NUM_FLASHBANKS
)braket
op_assign
(brace
(brace
id|WINDOW_ADDR0
comma
id|WINDOW_SIZE0
)brace
comma
(brace
id|WINDOW_ADDR1
comma
id|WINDOW_SIZE1
)brace
comma
)brace
suffix:semicolon
r_int
id|devicesfound
op_assign
l_int|0
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
id|NUM_FLASHBANKS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
id|MSG_PREFIX
l_string|&quot;probing 0x%08lx at 0x%08lx&bslash;n&quot;
comma
id|pt
(braket
id|i
)braket
dot
id|size
comma
id|pt
(braket
id|i
)braket
dot
id|addr
)paren
suffix:semicolon
id|impa7_map
(braket
id|i
)braket
dot
id|phys
op_assign
id|pt
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
id|impa7_map
(braket
id|i
)braket
dot
id|virt
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|pt
(braket
id|i
)braket
dot
id|addr
comma
id|pt
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|impa7_map
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
id|impa7_map
(braket
id|i
)braket
)paren
suffix:semicolon
id|impa7_mtd
(braket
id|i
)braket
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
id|impa7_mtd
(braket
id|i
)braket
op_logical_and
op_star
id|type
suffix:semicolon
id|type
op_increment
)paren
(brace
id|impa7_mtd
(braket
id|i
)braket
op_assign
id|do_map_probe
c_func
(paren
op_star
id|type
comma
op_amp
id|impa7_map
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|impa7_mtd
(braket
id|i
)braket
)paren
(brace
id|impa7_mtd
(braket
id|i
)braket
op_member_access_from_pointer
id|owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|devicesfound
op_increment
suffix:semicolon
macro_line|#ifdef CONFIG_MTD_PARTITIONS
id|mtd_parts_nb
(braket
id|i
)braket
op_assign
id|parse_mtd_partitions
c_func
(paren
id|impa7_mtd
(braket
id|i
)braket
comma
id|probes
comma
op_amp
id|mtd_parts
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
id|mtd_parts_nb
(braket
id|i
)braket
OG
l_int|0
)paren
(brace
id|part_type
op_assign
l_string|&quot;command line&quot;
suffix:semicolon
)brace
r_else
(brace
id|mtd_parts
(braket
id|i
)braket
op_assign
id|static_partitions
suffix:semicolon
id|mtd_parts_nb
(braket
id|i
)braket
op_assign
id|ARRAY_SIZE
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
id|impa7_mtd
(braket
id|i
)braket
comma
id|mtd_parts
(braket
id|i
)braket
comma
id|mtd_parts_nb
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#else
id|add_mtd_device
c_func
(paren
id|impa7_mtd
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|impa7_map
(braket
id|i
)braket
dot
id|virt
)paren
suffix:semicolon
)brace
r_return
id|devicesfound
op_eq
l_int|0
ques
c_cond
op_minus
id|ENXIO
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_impa7
r_static
r_void
id|__exit
id|cleanup_impa7
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
id|NUM_FLASHBANKS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|impa7_mtd
(braket
id|i
)braket
)paren
(brace
macro_line|#ifdef CONFIG_MTD_PARTITIONS
id|del_mtd_partitions
c_func
(paren
id|impa7_mtd
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#else
id|del_mtd_device
c_func
(paren
id|impa7_mtd
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
id|map_destroy
c_func
(paren
id|impa7_mtd
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
id|impa7_map
(braket
id|i
)braket
dot
id|virt
)paren
suffix:semicolon
id|impa7_map
(braket
id|i
)braket
dot
id|virt
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
DECL|variable|init_impa7
id|module_init
c_func
(paren
id|init_impa7
)paren
suffix:semicolon
DECL|variable|cleanup_impa7
id|module_exit
c_func
(paren
id|cleanup_impa7
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
l_string|&quot;Pavel Bartusek &lt;pba@sysgo.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for implementa impA7&quot;
)paren
suffix:semicolon
eof
