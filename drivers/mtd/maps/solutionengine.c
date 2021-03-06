multiline_comment|/*&n; * $Id: solutionengine.c,v 1.14 2004/09/16 23:27:14 gleixner Exp $&n; *&n; * Flash and EPROM on Hitachi Solution Engine and similar boards.&n; *&n; * (C) 2001 Red Hat, Inc.&n; *&n; * GPL&squot;d&n; */
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
DECL|variable|flash_mtd
r_static
r_struct
id|mtd_info
op_star
id|flash_mtd
suffix:semicolon
DECL|variable|eprom_mtd
r_static
r_struct
id|mtd_info
op_star
id|eprom_mtd
suffix:semicolon
DECL|variable|parsed_parts
r_static
r_struct
id|mtd_partition
op_star
id|parsed_parts
suffix:semicolon
DECL|variable|soleng_eprom_map
r_struct
id|map_info
id|soleng_eprom_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Solution Engine EPROM&quot;
comma
dot
id|size
op_assign
l_int|0x400000
comma
dot
id|bankwidth
op_assign
l_int|4
comma
)brace
suffix:semicolon
DECL|variable|soleng_flash_map
r_struct
id|map_info
id|soleng_flash_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Solution Engine FLASH&quot;
comma
dot
id|size
op_assign
l_int|0x400000
comma
dot
id|bankwidth
op_assign
l_int|4
comma
)brace
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
macro_line|#ifdef CONFIG_MTD_SUPERH_RESERVE
DECL|variable|superh_se_partitions
r_static
r_struct
id|mtd_partition
id|superh_se_partitions
(braket
)braket
op_assign
(brace
multiline_comment|/* Reserved for boot code, read-only */
(brace
dot
id|name
op_assign
l_string|&quot;flash_boot&quot;
comma
dot
id|offset
op_assign
l_int|0x00000000
comma
dot
id|size
op_assign
id|CONFIG_MTD_SUPERH_RESERVE
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
comma
)brace
comma
multiline_comment|/* All else is writable (e.g. JFFS) */
(brace
dot
id|name
op_assign
l_string|&quot;Flash FS&quot;
comma
dot
id|offset
op_assign
id|MTDPART_OFS_NXTBLK
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_MTD_SUPERH_RESERVE */
DECL|function|init_soleng_maps
r_static
r_int
id|__init
id|init_soleng_maps
c_func
(paren
r_void
)paren
(brace
r_int
id|nr_parts
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* First probe at offset 0 */
id|soleng_flash_map.phys
op_assign
l_int|0
suffix:semicolon
id|soleng_flash_map.virt
op_assign
(paren
r_void
id|__iomem
op_star
)paren
id|P2SEGADDR
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|soleng_eprom_map.phys
op_assign
l_int|0x01000000
suffix:semicolon
id|soleng_eprom_map.virt
op_assign
(paren
r_void
id|__iomem
op_star
)paren
id|P1SEGADDR
c_func
(paren
l_int|0x01000000
)paren
suffix:semicolon
id|simple_map_init
c_func
(paren
op_amp
id|soleng_eprom_map
)paren
suffix:semicolon
id|simple_map_init
c_func
(paren
op_amp
id|soleng_flash_map
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Probing for flash chips at 0x00000000:&bslash;n&quot;
)paren
suffix:semicolon
id|flash_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|soleng_flash_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flash_mtd
)paren
(brace
multiline_comment|/* Not there. Try swapping */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Probing for flash chips at 0x01000000:&bslash;n&quot;
)paren
suffix:semicolon
id|soleng_flash_map.phys
op_assign
l_int|0x01000000
suffix:semicolon
id|soleng_flash_map.virt
op_assign
id|P2SEGADDR
c_func
(paren
l_int|0x01000000
)paren
suffix:semicolon
id|soleng_eprom_map.phys
op_assign
l_int|0
suffix:semicolon
id|soleng_eprom_map.virt
op_assign
id|P1SEGADDR
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|flash_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|soleng_flash_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flash_mtd
)paren
(brace
multiline_comment|/* Eep. */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Flash chips not detected at either possible location.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Solution Engine: Flash at 0x%08lx, EPROM at 0x%08lx&bslash;n&quot;
comma
id|soleng_flash_map.phys
op_amp
l_int|0x1fffffff
comma
id|soleng_eprom_map.phys
op_amp
l_int|0x1fffffff
)paren
suffix:semicolon
id|flash_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|eprom_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;map_rom&quot;
comma
op_amp
id|soleng_eprom_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eprom_mtd
)paren
(brace
id|eprom_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|add_mtd_device
c_func
(paren
id|eprom_mtd
)paren
suffix:semicolon
)brace
id|nr_parts
op_assign
id|parse_mtd_partitions
c_func
(paren
id|flash_mtd
comma
id|probes
comma
op_amp
id|parsed_parts
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MTD_SUPERH_RESERVE
r_if
c_cond
(paren
id|nr_parts
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Using configured partition at 0x%08x.&bslash;n&quot;
comma
id|CONFIG_MTD_SUPERH_RESERVE
)paren
suffix:semicolon
id|parsed_parts
op_assign
id|superh_se_partitions
suffix:semicolon
id|nr_parts
op_assign
r_sizeof
(paren
id|superh_se_partitions
)paren
op_div
r_sizeof
(paren
op_star
id|parsed_parts
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MTD_SUPERH_RESERVE */
r_if
c_cond
(paren
id|nr_parts
OG
l_int|0
)paren
id|add_mtd_partitions
c_func
(paren
id|flash_mtd
comma
id|parsed_parts
comma
id|nr_parts
)paren
suffix:semicolon
r_else
id|add_mtd_device
c_func
(paren
id|flash_mtd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_soleng_maps
r_static
r_void
id|__exit
id|cleanup_soleng_maps
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|eprom_mtd
)paren
(brace
id|del_mtd_device
c_func
(paren
id|eprom_mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|eprom_mtd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|parsed_parts
)paren
id|del_mtd_partitions
c_func
(paren
id|flash_mtd
)paren
suffix:semicolon
r_else
id|del_mtd_device
c_func
(paren
id|flash_mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|flash_mtd
)paren
suffix:semicolon
)brace
DECL|variable|init_soleng_maps
id|module_init
c_func
(paren
id|init_soleng_maps
)paren
suffix:semicolon
DECL|variable|cleanup_soleng_maps
id|module_exit
c_func
(paren
id|cleanup_soleng_maps
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
l_string|&quot;MTD map driver for Hitachi SolutionEngine (and similar) boards&quot;
)paren
suffix:semicolon
eof
