multiline_comment|/*&n; * $Id: physmap.c,v 1.37 2004/11/28 09:40:40 dwmw2 Exp $&n; *&n; * Normal mappings of chips in physical memory&n; *&n; * Copyright (C) 2003 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * 031022 - [jsun] add run-time configure and partition setup&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
DECL|variable|physmap_map
r_struct
id|map_info
id|physmap_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;phys_mapped_flash&quot;
comma
dot
id|phys
op_assign
id|CONFIG_MTD_PHYSMAP_START
comma
dot
id|size
op_assign
id|CONFIG_MTD_PHYSMAP_LEN
comma
dot
id|bankwidth
op_assign
id|CONFIG_MTD_PHYSMAP_BANKWIDTH
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_MTD_PARTITIONS
DECL|variable|mtd_parts
r_static
r_struct
id|mtd_partition
op_star
id|mtd_parts
suffix:semicolon
DECL|variable|mtd_parts_nb
r_static
r_int
id|mtd_parts_nb
suffix:semicolon
DECL|variable|num_physmap_partitions
r_static
r_int
id|num_physmap_partitions
suffix:semicolon
DECL|variable|physmap_partitions
r_static
r_struct
id|mtd_partition
op_star
id|physmap_partitions
suffix:semicolon
DECL|variable|__initdata
r_static
r_const
r_char
op_star
id|part_probes
(braket
)braket
id|__initdata
op_assign
(brace
l_string|&quot;cmdlinepart&quot;
comma
l_string|&quot;RedBoot&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|physmap_set_partitions
r_void
id|physmap_set_partitions
c_func
(paren
r_struct
id|mtd_partition
op_star
id|parts
comma
r_int
id|num_parts
)paren
(brace
id|physmap_partitions
op_assign
id|parts
suffix:semicolon
id|num_physmap_partitions
op_assign
id|num_parts
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MTD_PARTITIONS */
DECL|function|init_physmap
r_static
r_int
id|__init
id|init_physmap
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
(brace
l_string|&quot;cfi_probe&quot;
comma
l_string|&quot;jedec_probe&quot;
comma
l_string|&quot;map_rom&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_const
r_char
op_star
op_star
id|type
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;physmap flash device: %lx at %lx&bslash;n&quot;
comma
id|physmap_map.size
comma
id|physmap_map.phys
)paren
suffix:semicolon
id|physmap_map.virt
op_assign
id|ioremap
c_func
(paren
id|physmap_map.phys
comma
id|physmap_map.size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|physmap_map.virt
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
id|physmap_map
)paren
suffix:semicolon
id|mymtd
op_assign
l_int|NULL
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
id|physmap_map
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
id|part_probes
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
id|mtd_parts_nb
OG
l_int|0
)paren
(brace
id|add_mtd_partitions
(paren
id|mymtd
comma
id|mtd_parts
comma
id|mtd_parts_nb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|num_physmap_partitions
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Using physmap partition definition&bslash;n&quot;
)paren
suffix:semicolon
id|add_mtd_partitions
(paren
id|mymtd
comma
id|physmap_partitions
comma
id|num_physmap_partitions
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
id|add_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|physmap_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|cleanup_physmap
r_static
r_void
id|__exit
id|cleanup_physmap
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_MTD_PARTITIONS
r_if
c_cond
(paren
id|mtd_parts_nb
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|mymtd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mtd_parts
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|num_physmap_partitions
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|mymtd
)paren
suffix:semicolon
)brace
r_else
(brace
id|del_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
)brace
macro_line|#else
id|del_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
macro_line|#endif
id|map_destroy
c_func
(paren
id|mymtd
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|physmap_map.virt
)paren
suffix:semicolon
id|physmap_map.virt
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|init_physmap
id|module_init
c_func
(paren
id|init_physmap
)paren
suffix:semicolon
DECL|variable|cleanup_physmap
id|module_exit
c_func
(paren
id|cleanup_physmap
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
l_string|&quot;David Woodhouse &lt;dwmw2@infradead.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Generic configurable MTD map driver&quot;
)paren
suffix:semicolon
eof
