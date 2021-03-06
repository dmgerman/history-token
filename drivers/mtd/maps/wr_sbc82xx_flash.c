multiline_comment|/*&n; * $Id: wr_sbc82xx_flash.c,v 1.7 2004/11/04 13:24:15 gleixner Exp $&n; *&n; * Map for flash chips on Wind River PowerQUICC II SBC82xx board.&n; *&n; * Copyright (C) 2004 Red Hat, Inc.&n; *&n; * Author: David Woodhouse &lt;dwmw2@infradead.org&gt;&n; *&n; */
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
macro_line|#include &lt;asm/immap_cpm2.h&gt;
DECL|variable|sbcmtd
r_static
r_struct
id|mtd_info
op_star
id|sbcmtd
(braket
l_int|3
)braket
suffix:semicolon
DECL|variable|sbcmtd_parts
r_static
r_struct
id|mtd_partition
op_star
id|sbcmtd_parts
(braket
l_int|3
)braket
suffix:semicolon
DECL|variable|sbc82xx_flash_map
r_struct
id|map_info
id|sbc82xx_flash_map
(braket
l_int|3
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;Boot flash&quot;
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Alternate boot flash&quot;
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;User flash&quot;
)brace
)brace
suffix:semicolon
DECL|variable|smallflash_parts
r_static
r_struct
id|mtd_partition
id|smallflash_parts
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;space&quot;
comma
dot
id|size
op_assign
l_int|0x100000
comma
dot
id|offset
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;bootloader&quot;
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
comma
)brace
)brace
suffix:semicolon
DECL|variable|bigflash_parts
r_static
r_struct
id|mtd_partition
id|bigflash_parts
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;bootloader&quot;
comma
dot
id|size
op_assign
l_int|0x00100000
comma
dot
id|offset
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;file system&quot;
comma
dot
id|size
op_assign
l_int|0x01f00000
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;boot config&quot;
comma
dot
id|size
op_assign
l_int|0x00100000
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;space&quot;
comma
dot
id|size
op_assign
l_int|0x01f00000
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
)brace
)brace
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
DECL|macro|init_sbc82xx_one_flash
mdefine_line|#define init_sbc82xx_one_flash(map, br, or)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(map).phys = (br &amp; 1) ? (br &amp; 0xffff8000) : 0;&t;&t;&bslash;&n;&t;(map).size = (br &amp; 1) ? (~(or &amp; 0xffff8000) + 1) : 0;&t;&bslash;&n;&t;switch (br &amp; 0x00001800) {&t;&t;&t;&t;&bslash;&n;&t;case 0x00000000:&t;&t;&t;&t;&t;&bslash;&n;&t;case 0x00000800:&t;(map).bankwidth = 1;&t;break;&t;&bslash;&n;&t;case 0x00001000:&t;(map).bankwidth = 2;&t;break;&t;&bslash;&n;&t;case 0x00001800:&t;(map).bankwidth = 4;&t;break;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0);
DECL|function|init_sbc82xx_flash
r_int
id|__init
id|init_sbc82xx_flash
c_func
(paren
r_void
)paren
(brace
r_volatile
id|memctl_cpm2_t
op_star
id|mc
op_assign
op_amp
id|cpm2_immr-&gt;im_memctl
suffix:semicolon
r_int
id|bigflash
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_SBC8560
id|mc
op_assign
id|ioremap
c_func
(paren
l_int|0xff700000
op_plus
l_int|0x5000
comma
r_sizeof
(paren
id|memctl_cpm2_t
)paren
)paren
suffix:semicolon
macro_line|#else
id|mc
op_assign
op_amp
id|cpm2_immr-&gt;im_memctl
suffix:semicolon
macro_line|#endif
id|bigflash
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mc-&gt;memc_br0
op_amp
l_int|0x00001800
)paren
op_eq
l_int|0x00001800
)paren
id|bigflash
op_assign
l_int|0
suffix:semicolon
id|init_sbc82xx_one_flash
c_func
(paren
id|sbc82xx_flash_map
(braket
l_int|0
)braket
comma
id|mc-&gt;memc_br0
comma
id|mc-&gt;memc_or0
)paren
suffix:semicolon
id|init_sbc82xx_one_flash
c_func
(paren
id|sbc82xx_flash_map
(braket
l_int|1
)braket
comma
id|mc-&gt;memc_br6
comma
id|mc-&gt;memc_or6
)paren
suffix:semicolon
id|init_sbc82xx_one_flash
c_func
(paren
id|sbc82xx_flash_map
(braket
l_int|2
)braket
comma
id|mc-&gt;memc_br1
comma
id|mc-&gt;memc_or1
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SBC8560
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|mc
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int8
id|flashcs
(braket
l_int|3
)braket
op_assign
(brace
l_int|0
comma
l_int|6
comma
l_int|1
)brace
suffix:semicolon
r_int
id|nr_parts
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;PowerQUICC II %s (%ld MiB on CS%d&quot;
comma
id|sbc82xx_flash_map
(braket
id|i
)braket
dot
id|name
comma
(paren
id|sbc82xx_flash_map
(braket
id|i
)braket
dot
id|size
op_rshift
l_int|20
)paren
comma
id|flashcs
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbc82xx_flash_map
(braket
id|i
)braket
dot
id|phys
)paren
(brace
multiline_comment|/* We know it can&squot;t be at zero. */
id|printk
c_func
(paren
l_string|&quot;): disabled by bootloader.&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; at %08lx)&bslash;n&quot;
comma
id|sbc82xx_flash_map
(braket
id|i
)braket
dot
id|phys
)paren
suffix:semicolon
id|sbc82xx_flash_map
(braket
id|i
)braket
dot
id|virt
op_assign
id|ioremap
c_func
(paren
id|sbc82xx_flash_map
(braket
id|i
)braket
dot
id|phys
comma
id|sbc82xx_flash_map
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
id|sbc82xx_flash_map
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
l_string|&quot;Failed to ioremap&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|simple_map_init
c_func
(paren
op_amp
id|sbc82xx_flash_map
(braket
id|i
)braket
)paren
suffix:semicolon
id|sbcmtd
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
id|sbc82xx_flash_map
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbcmtd
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|sbcmtd
(braket
id|i
)braket
op_member_access_from_pointer
id|owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|nr_parts
op_assign
id|parse_mtd_partitions
c_func
(paren
id|sbcmtd
(braket
id|i
)braket
comma
id|part_probes
comma
op_amp
id|sbcmtd_parts
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
id|nr_parts
OG
l_int|0
)paren
(brace
id|add_mtd_partitions
(paren
id|sbcmtd
(braket
id|i
)braket
comma
id|sbcmtd_parts
(braket
id|i
)braket
comma
id|nr_parts
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* No partitioning detected. Use default */
r_if
c_cond
(paren
id|i
op_eq
l_int|2
)paren
(brace
id|add_mtd_device
c_func
(paren
id|sbcmtd
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
id|i
op_eq
id|bigflash
)paren
(brace
id|add_mtd_partitions
(paren
id|sbcmtd
(braket
id|i
)braket
comma
id|bigflash_parts
comma
id|ARRAY_SIZE
c_func
(paren
id|bigflash_parts
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|add_mtd_partitions
(paren
id|sbcmtd
(braket
id|i
)braket
comma
id|smallflash_parts
comma
id|ARRAY_SIZE
c_func
(paren
id|smallflash_parts
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_sbc82xx_flash
r_static
r_void
id|__exit
id|cleanup_sbc82xx_flash
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sbcmtd
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|2
op_logical_or
id|sbcmtd_parts
(braket
id|i
)braket
)paren
id|del_mtd_partitions
c_func
(paren
id|sbcmtd
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|del_mtd_device
c_func
(paren
id|sbcmtd
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sbcmtd_parts
(braket
id|i
)braket
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|sbcmtd
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
id|sbc82xx_flash_map
(braket
id|i
)braket
dot
id|virt
)paren
suffix:semicolon
id|sbc82xx_flash_map
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
DECL|variable|init_sbc82xx_flash
id|module_init
c_func
(paren
id|init_sbc82xx_flash
)paren
suffix:semicolon
DECL|variable|cleanup_sbc82xx_flash
id|module_exit
c_func
(paren
id|cleanup_sbc82xx_flash
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
l_string|&quot;Flash map driver for WindRiver PowerQUICC II&quot;
)paren
suffix:semicolon
eof
