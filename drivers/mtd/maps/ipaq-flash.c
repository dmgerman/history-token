multiline_comment|/*&n; * Flash memory access on iPAQ Handhelds (either SA1100 or PXA250 based)&n; * &n; * (C) 2000 Nicolas Pitre &lt;nico@cam.org&gt;&n; * (C) 2002 Hewlett-Packard Company &lt;jamey.hicks@hp.com&gt;&n; * (C) 2003 Christian Pellegrin &lt;chri@ascensit.com&gt;, &lt;chri@infis.univ.ts.it&gt;: concatenation of multiple flashes&n; * &n; * $Id: ipaq-flash.c,v 1.3 2004/11/04 13:24:15 gleixner Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#ifdef CONFIG_MTD_CONCAT
macro_line|#include &lt;linux/mtd/concat.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/arch-sa1100/h3600.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifndef CONFIG_IPAQ_HANDHELD
macro_line|#error This is for iPAQ Handhelds only
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_JORNADA56X
DECL|function|jornada56x_set_vpp
r_static
r_void
id|jornada56x_set_vpp
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
id|vpp
)paren
(brace
r_if
c_cond
(paren
id|vpp
)paren
id|GPSR
op_assign
id|GPIO_GPIO26
suffix:semicolon
r_else
id|GPCR
op_assign
id|GPIO_GPIO26
suffix:semicolon
id|GPDR
op_or_assign
id|GPIO_GPIO26
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_JORNADA720
DECL|function|jornada720_set_vpp
r_static
r_void
id|jornada720_set_vpp
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
id|vpp
)paren
(brace
r_if
c_cond
(paren
id|vpp
)paren
id|PPSR
op_or_assign
l_int|0x80
suffix:semicolon
r_else
id|PPSR
op_and_assign
op_complement
l_int|0x80
suffix:semicolon
id|PPDR
op_or_assign
l_int|0x80
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|MAX_IPAQ_CS
mdefine_line|#define MAX_IPAQ_CS 2&t;&t;/* Number of CS we are going to test */
DECL|macro|IPAQ_MAP_INIT
mdefine_line|#define IPAQ_MAP_INIT(X) &bslash;&n;&t;{ &bslash;&n;&t;&t;name:&t;&t;&quot;IPAQ flash &quot; X, &bslash;&n;&t;}
DECL|variable|ipaq_map
r_static
r_struct
id|map_info
id|ipaq_map
(braket
id|MAX_IPAQ_CS
)braket
op_assign
(brace
id|IPAQ_MAP_INIT
c_func
(paren
l_string|&quot;bank 1&quot;
)paren
comma
id|IPAQ_MAP_INIT
c_func
(paren
l_string|&quot;bank 2&quot;
)paren
)brace
suffix:semicolon
DECL|variable|my_sub_mtd
r_static
r_struct
id|mtd_info
op_star
id|my_sub_mtd
(braket
id|MAX_IPAQ_CS
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; * Here are partition information for all known IPAQ-based devices.&n; * See include/linux/mtd/partitions.h for definition of the mtd_partition&n; * structure.&n; *&n; * The *_max_flash_size is the maximum possible mapped flash size which&n; * is not necessarily the actual flash size.  It must be no more than&n; * the value specified in the &quot;struct map_desc *_io_desc&quot; mapping&n; * definition for the corresponding machine.&n; *&n; * Please keep these in alphabetical order, and formatted as per existing&n; * entries.  Thanks.&n; */
macro_line|#ifdef CONFIG_IPAQ_HANDHELD
DECL|variable|h3xxx_max_flash_size
r_static
r_int
r_int
id|h3xxx_max_flash_size
op_assign
l_int|0x04000000
suffix:semicolon
DECL|variable|h3xxx_partitions
r_static
r_struct
id|mtd_partition
id|h3xxx_partitions
(braket
)braket
op_assign
(brace
(brace
id|name
suffix:colon
l_string|&quot;H3XXX boot firmware&quot;
comma
macro_line|#ifndef CONFIG_LAB
id|size
suffix:colon
l_int|0x00040000
comma
macro_line|#else
id|size
suffix:colon
l_int|0x00080000
comma
macro_line|#endif
id|offset
suffix:colon
l_int|0
comma
macro_line|#ifndef CONFIG_LAB
id|mask_flags
suffix:colon
id|MTD_WRITEABLE
comma
multiline_comment|/* force read-only */
macro_line|#endif
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;H3XXX root jffs2&quot;
comma
macro_line|#ifndef CONFIG_LAB
id|size
suffix:colon
l_int|0x2000000
op_minus
l_int|2
op_star
l_int|0x40000
comma
multiline_comment|/* Warning, this is fixed later */
id|offset
suffix:colon
l_int|0x00040000
comma
macro_line|#else
id|size
suffix:colon
l_int|0x2000000
op_minus
l_int|0x40000
op_minus
l_int|0x80000
comma
multiline_comment|/* Warning, this is fixed later */
id|offset
suffix:colon
l_int|0x00080000
comma
macro_line|#endif
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;asset&quot;
comma
id|size
suffix:colon
l_int|0x40000
comma
id|offset
suffix:colon
l_int|0x2000000
op_minus
l_int|0x40000
comma
multiline_comment|/* Warning, this is fixed later */
id|mask_flags
suffix:colon
id|MTD_WRITEABLE
comma
multiline_comment|/* force read-only */
)brace
)brace
suffix:semicolon
macro_line|#ifndef CONFIG_MTD_CONCAT
DECL|variable|h3xxx_partitions_bank2
r_static
r_struct
id|mtd_partition
id|h3xxx_partitions_bank2
(braket
)braket
op_assign
(brace
multiline_comment|/* this is used only on 2 CS machines when concat is not present */
(brace
id|name
suffix:colon
l_string|&quot;second H3XXX root jffs2&quot;
comma
id|size
suffix:colon
l_int|0x1000000
op_minus
l_int|0x40000
comma
multiline_comment|/* Warning, this is fixed later */
id|offset
suffix:colon
l_int|0x00000000
comma
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;second asset&quot;
comma
id|size
suffix:colon
l_int|0x40000
comma
id|offset
suffix:colon
l_int|0x1000000
op_minus
l_int|0x40000
comma
multiline_comment|/* Warning, this is fixed later */
id|mask_flags
suffix:colon
id|MTD_WRITEABLE
comma
multiline_comment|/* force read-only */
)brace
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|ipaq_vpp_lock
r_static
id|spinlock_t
id|ipaq_vpp_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|h3xxx_set_vpp
r_static
r_void
id|h3xxx_set_vpp
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
id|vpp
)paren
(brace
r_static
r_int
id|nest
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ipaq_vpp_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vpp
)paren
id|nest
op_increment
suffix:semicolon
r_else
id|nest
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|nest
)paren
id|assign_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_VPP_ON
comma
l_int|1
)paren
suffix:semicolon
r_else
id|assign_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_VPP_ON
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ipaq_vpp_lock
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_SA1100_JORNADA56X) || defined(CONFIG_SA1100_JORNADA720)
DECL|variable|jornada_max_flash_size
r_static
r_int
r_int
id|jornada_max_flash_size
op_assign
l_int|0x02000000
suffix:semicolon
DECL|variable|jornada_partitions
r_static
r_struct
id|mtd_partition
id|jornada_partitions
(braket
)braket
op_assign
(brace
(brace
id|name
suffix:colon
l_string|&quot;Jornada boot firmware&quot;
comma
id|size
suffix:colon
l_int|0x00040000
comma
id|offset
suffix:colon
l_int|0
comma
id|mask_flags
suffix:colon
id|MTD_WRITEABLE
comma
multiline_comment|/* force read-only */
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;Jornada root jffs2&quot;
comma
id|size
suffix:colon
id|MTDPART_SIZ_FULL
comma
id|offset
suffix:colon
l_int|0x00040000
comma
)brace
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|parsed_parts
r_static
r_struct
id|mtd_partition
op_star
id|parsed_parts
suffix:semicolon
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
DECL|variable|cs_phys
r_static
r_int
r_int
id|cs_phys
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_ARCH_SA1100
id|SA1100_CS0_PHYS
comma
id|SA1100_CS1_PHYS
comma
id|SA1100_CS2_PHYS
comma
id|SA1100_CS3_PHYS
comma
id|SA1100_CS4_PHYS
comma
id|SA1100_CS5_PHYS
comma
macro_line|#else 
id|PXA_CS0_PHYS
comma
id|PXA_CS1_PHYS
comma
id|PXA_CS2_PHYS
comma
id|PXA_CS3_PHYS
comma
id|PXA_CS4_PHYS
comma
id|PXA_CS5_PHYS
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|part_probes
r_static
r_const
r_char
op_star
id|part_probes
(braket
)braket
op_assign
(brace
l_string|&quot;cmdlinepart&quot;
comma
l_string|&quot;RedBoot&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_static
r_int
id|__init
id|h1900_special_case
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|ipaq_mtd_init
r_int
id|__init
id|ipaq_mtd_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|mtd_partition
op_star
id|parts
op_assign
l_int|NULL
suffix:semicolon
r_int
id|nb_parts
op_assign
l_int|0
suffix:semicolon
r_int
id|parsed_nr_parts
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|part_type
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* used when we have &gt;1 flash chips */
r_int
r_int
id|tot_flashsize
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* used when we have &gt;1 flash chips */
multiline_comment|/* Default flash bankwidth */
singleline_comment|// ipaq_map.bankwidth = (MSC0 &amp; MSC_RBW) ? 2 : 4;
r_if
c_cond
(paren
id|machine_is_h1900
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* For our intents, the h1900 is not a real iPAQ, so we special-case it. */
r_return
id|h1900_special_case
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|machine_is_h3100
c_func
(paren
)paren
op_logical_or
id|machine_is_h1900
c_func
(paren
)paren
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_IPAQ_CS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ipaq_map
(braket
id|i
)braket
dot
id|bankwidth
op_assign
l_int|2
suffix:semicolon
)brace
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_IPAQ_CS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ipaq_map
(braket
id|i
)braket
dot
id|bankwidth
op_assign
l_int|4
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Static partition definition selection&n;&t; */
id|part_type
op_assign
l_string|&quot;static&quot;
suffix:semicolon
id|simple_map_init
c_func
(paren
op_amp
id|ipaq_map
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|simple_map_init
c_func
(paren
op_amp
id|ipaq_map
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IPAQ_HANDHELD
r_if
c_cond
(paren
id|machine_is_ipaq
c_func
(paren
)paren
)paren
(brace
id|parts
op_assign
id|h3xxx_partitions
suffix:semicolon
id|nb_parts
op_assign
id|ARRAY_SIZE
c_func
(paren
id|h3xxx_partitions
)paren
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
id|MAX_IPAQ_CS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ipaq_map
(braket
id|i
)braket
dot
id|size
op_assign
id|h3xxx_max_flash_size
suffix:semicolon
id|ipaq_map
(braket
id|i
)braket
dot
id|set_vpp
op_assign
id|h3xxx_set_vpp
suffix:semicolon
id|ipaq_map
(braket
id|i
)braket
dot
id|phys
op_assign
id|cs_phys
(braket
id|i
)braket
suffix:semicolon
id|ipaq_map
(braket
id|i
)braket
dot
id|virt
op_assign
id|__ioremap
c_func
(paren
id|cs_phys
(braket
id|i
)braket
comma
l_int|0x04000000
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_h3100
(paren
)paren
op_logical_or
id|machine_is_h1900
c_func
(paren
)paren
)paren
id|ipaq_map
(braket
id|i
)braket
dot
id|bankwidth
op_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|machine_is_h3600
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* No asset partition here */
id|h3xxx_partitions
(braket
l_int|1
)braket
dot
id|size
op_add_assign
l_int|0x40000
suffix:semicolon
id|nb_parts
op_decrement
suffix:semicolon
)brace
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_H5400
r_if
c_cond
(paren
id|machine_is_h5400
c_func
(paren
)paren
)paren
(brace
id|ipaq_map
(braket
l_int|0
)braket
dot
id|size
op_assign
l_int|0x02000000
suffix:semicolon
id|ipaq_map
(braket
l_int|1
)braket
dot
id|size
op_assign
l_int|0x02000000
suffix:semicolon
id|ipaq_map
(braket
l_int|1
)braket
dot
id|phys
op_assign
l_int|0x02000000
suffix:semicolon
id|ipaq_map
(braket
l_int|1
)braket
dot
id|virt
op_assign
id|ipaq_map
(braket
l_int|0
)braket
dot
id|virt
op_plus
l_int|0x02000000
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_H1900
r_if
c_cond
(paren
id|machine_is_h1900
c_func
(paren
)paren
)paren
(brace
id|ipaq_map
(braket
l_int|0
)braket
dot
id|size
op_assign
l_int|0x00400000
suffix:semicolon
id|ipaq_map
(braket
l_int|1
)braket
dot
id|size
op_assign
l_int|0x02000000
suffix:semicolon
id|ipaq_map
(braket
l_int|1
)braket
dot
id|phys
op_assign
l_int|0x00080000
suffix:semicolon
id|ipaq_map
(braket
l_int|1
)braket
dot
id|virt
op_assign
id|ipaq_map
(braket
l_int|0
)braket
dot
id|virt
op_plus
l_int|0x00080000
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_JORNADA56X
r_if
c_cond
(paren
id|machine_is_jornada56x
c_func
(paren
)paren
)paren
(brace
id|parts
op_assign
id|jornada_partitions
suffix:semicolon
id|nb_parts
op_assign
id|ARRAY_SIZE
c_func
(paren
id|jornada_partitions
)paren
suffix:semicolon
id|ipaq_map
(braket
l_int|0
)braket
dot
id|size
op_assign
id|jornada_max_flash_size
suffix:semicolon
id|ipaq_map
(braket
l_int|0
)braket
dot
id|set_vpp
op_assign
id|jornada56x_set_vpp
suffix:semicolon
id|ipaq_map
(braket
l_int|0
)braket
dot
id|virt
op_assign
(paren
id|__u32
)paren
id|__ioremap
c_func
(paren
l_int|0x0
comma
l_int|0x04000000
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_JORNADA720
r_if
c_cond
(paren
id|machine_is_jornada720
c_func
(paren
)paren
)paren
(brace
id|parts
op_assign
id|jornada_partitions
suffix:semicolon
id|nb_parts
op_assign
id|ARRAY_SIZE
c_func
(paren
id|jornada_partitions
)paren
suffix:semicolon
id|ipaq_map
(braket
l_int|0
)braket
dot
id|size
op_assign
id|jornada_max_flash_size
suffix:semicolon
id|ipaq_map
(braket
l_int|0
)braket
dot
id|set_vpp
op_assign
id|jornada720_set_vpp
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|machine_is_ipaq
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* for iPAQs only */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_IPAQ_CS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;iPAQ flash: probing %d-bit flash bus, window=%lx with CFI.&bslash;n&quot;
comma
id|ipaq_map
(braket
id|i
)braket
dot
id|bankwidth
op_star
l_int|8
comma
id|ipaq_map
(braket
id|i
)braket
dot
id|virt
)paren
suffix:semicolon
id|my_sub_mtd
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
id|ipaq_map
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|my_sub_mtd
(braket
id|i
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;iPAQ flash: probing %d-bit flash bus, window=%lx with JEDEC.&bslash;n&quot;
comma
id|ipaq_map
(braket
id|i
)braket
dot
id|bankwidth
op_star
l_int|8
comma
id|ipaq_map
(braket
id|i
)braket
dot
id|virt
)paren
suffix:semicolon
id|my_sub_mtd
(braket
id|i
)braket
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;jedec_probe&quot;
comma
op_amp
id|ipaq_map
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|my_sub_mtd
(braket
id|i
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;iPAQ flash: failed to find flash.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_break
suffix:semicolon
r_else
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;iPAQ flash: found %d bytes&bslash;n&quot;
comma
id|my_sub_mtd
(braket
id|i
)braket
op_member_access_from_pointer
id|size
)paren
suffix:semicolon
multiline_comment|/* do we really need this debugging? --joshua 20030703 */
singleline_comment|// printk(&quot;my_sub_mtd[%d]=%p&bslash;n&quot;, i, my_sub_mtd[i]);
id|my_sub_mtd
(braket
id|i
)braket
op_member_access_from_pointer
id|owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|tot_flashsize
op_add_assign
id|my_sub_mtd
(braket
id|i
)braket
op_member_access_from_pointer
id|size
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MTD_CONCAT
multiline_comment|/* fix the asset location */
macro_line|#&t;ifdef CONFIG_LAB
id|h3xxx_partitions
(braket
l_int|1
)braket
dot
id|size
op_assign
id|tot_flashsize
op_minus
l_int|0x40000
op_minus
l_int|0x80000
multiline_comment|/* extra big boot block */
suffix:semicolon
macro_line|#&t;else
id|h3xxx_partitions
(braket
l_int|1
)braket
dot
id|size
op_assign
id|tot_flashsize
op_minus
l_int|2
op_star
l_int|0x40000
suffix:semicolon
macro_line|#&t;endif
id|h3xxx_partitions
(braket
l_int|2
)braket
dot
id|offset
op_assign
id|tot_flashsize
op_minus
l_int|0x40000
suffix:semicolon
multiline_comment|/* and concat the devices */
id|mymtd
op_assign
id|mtd_concat_create
c_func
(paren
op_amp
id|my_sub_mtd
(braket
l_int|0
)braket
comma
id|i
comma
l_string|&quot;ipaq&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Cannot create iPAQ concat device&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
macro_line|#else
id|mymtd
op_assign
id|my_sub_mtd
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* &n;&t;&t; *In the very near future, command line partition parsing&n;&t;&t; * will use the device name as &squot;mtd-id&squot; instead of a value&n;&t;&t; * passed to the parse_cmdline_partitions() routine. Since&n;&t;&t; * the bootldr says &squot;ipaq&squot;, make sure it continues to work. &n;&t;&t; */
id|mymtd-&gt;name
op_assign
l_string|&quot;ipaq&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|machine_is_h3600
c_func
(paren
)paren
)paren
)paren
(brace
macro_line|#&t;ifdef CONFIG_LAB
id|h3xxx_partitions
(braket
l_int|1
)braket
dot
id|size
op_assign
id|my_sub_mtd
(braket
l_int|0
)braket
op_member_access_from_pointer
id|size
op_minus
l_int|0x80000
suffix:semicolon
macro_line|#&t;else
id|h3xxx_partitions
(braket
l_int|1
)braket
dot
id|size
op_assign
id|my_sub_mtd
(braket
l_int|0
)braket
op_member_access_from_pointer
id|size
op_minus
l_int|0x40000
suffix:semicolon
macro_line|#&t;endif
id|nb_parts
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
macro_line|#&t;ifdef CONFIG_LAB
id|h3xxx_partitions
(braket
l_int|1
)braket
dot
id|size
op_assign
id|my_sub_mtd
(braket
l_int|0
)braket
op_member_access_from_pointer
id|size
op_minus
l_int|0x40000
op_minus
l_int|0x80000
suffix:semicolon
multiline_comment|/* extra big boot block */
macro_line|#&t;else
id|h3xxx_partitions
(braket
l_int|1
)braket
dot
id|size
op_assign
id|my_sub_mtd
(braket
l_int|0
)braket
op_member_access_from_pointer
id|size
op_minus
l_int|2
op_star
l_int|0x40000
suffix:semicolon
macro_line|#&t;endif
id|h3xxx_partitions
(braket
l_int|2
)braket
dot
id|offset
op_assign
id|my_sub_mtd
(braket
l_int|0
)braket
op_member_access_from_pointer
id|size
op_minus
l_int|0x40000
suffix:semicolon
)brace
r_if
c_cond
(paren
id|my_sub_mtd
(braket
l_int|1
)braket
)paren
(brace
macro_line|#&t;ifdef CONFIG_LAB
id|h3xxx_partitions_bank2
(braket
l_int|0
)braket
dot
id|size
op_assign
id|my_sub_mtd
(braket
l_int|1
)braket
op_member_access_from_pointer
id|size
op_minus
l_int|0x80000
suffix:semicolon
macro_line|#&t;else
id|h3xxx_partitions_bank2
(braket
l_int|0
)braket
dot
id|size
op_assign
id|my_sub_mtd
(braket
l_int|1
)braket
op_member_access_from_pointer
id|size
op_minus
l_int|0x40000
suffix:semicolon
macro_line|#&t;endif
id|h3xxx_partitions_bank2
(braket
l_int|1
)braket
dot
id|offset
op_assign
id|my_sub_mtd
(braket
l_int|1
)braket
op_member_access_from_pointer
id|size
op_minus
l_int|0x40000
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Now let&squot;s probe for the actual flash.  Do it here since&n;&t;&t; * specific machine settings might have been set above.&n;&t;&t; */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;IPAQ flash: probing %d-bit flash bus, window=%lx&bslash;n&quot;
comma
id|ipaq_map
(braket
l_int|0
)braket
dot
id|bankwidth
op_star
l_int|8
comma
id|ipaq_map
(braket
l_int|0
)braket
dot
id|virt
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
id|ipaq_map
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|mymtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Dynamic partition selection stuff (might override the static ones)&n;&t; */
id|i
op_assign
id|parse_mtd_partitions
c_func
(paren
id|mymtd
comma
id|part_probes
comma
op_amp
id|parsed_parts
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
id|nb_parts
op_assign
id|parsed_nr_parts
op_assign
id|i
suffix:semicolon
id|parts
op_assign
id|parsed_parts
suffix:semicolon
id|part_type
op_assign
l_string|&quot;dynamic&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|parts
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;IPAQ flash: no partition info available, registering whole flash at once&bslash;n&quot;
)paren
suffix:semicolon
id|add_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_MTD_CONCAT
r_if
c_cond
(paren
id|my_sub_mtd
(braket
l_int|1
)braket
)paren
id|add_mtd_device
c_func
(paren
id|my_sub_mtd
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Using %s partition definition&bslash;n&quot;
comma
id|part_type
)paren
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|mymtd
comma
id|parts
comma
id|nb_parts
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_MTD_CONCAT
r_if
c_cond
(paren
id|my_sub_mtd
(braket
l_int|1
)braket
)paren
id|add_mtd_partitions
c_func
(paren
id|my_sub_mtd
(braket
l_int|1
)braket
comma
id|h3xxx_partitions_bank2
comma
id|ARRAY_SIZE
c_func
(paren
id|h3xxx_partitions_bank2
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipaq_mtd_cleanup
r_static
r_void
id|__exit
id|ipaq_mtd_cleanup
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
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
macro_line|#ifndef CONFIG_MTD_CONCAT
r_if
c_cond
(paren
id|my_sub_mtd
(braket
l_int|1
)braket
)paren
id|del_mtd_partitions
c_func
(paren
id|my_sub_mtd
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#endif
id|map_destroy
c_func
(paren
id|mymtd
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MTD_CONCAT
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_IPAQ_CS
suffix:semicolon
id|i
op_increment
)paren
macro_line|#else
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|MAX_IPAQ_CS
suffix:semicolon
id|i
op_increment
)paren
macro_line|#endif&t;&t;  
(brace
r_if
c_cond
(paren
id|my_sub_mtd
(braket
id|i
)braket
)paren
id|map_destroy
c_func
(paren
id|my_sub_mtd
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|parsed_parts
)paren
id|kfree
c_func
(paren
id|parsed_parts
)paren
suffix:semicolon
)brace
)brace
DECL|function|h1900_special_case
r_static
r_int
id|__init
id|h1900_special_case
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* The iPAQ h1900 is a special case - it has weird ROM. */
id|simple_map_init
c_func
(paren
op_amp
id|ipaq_map
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ipaq_map
(braket
l_int|0
)braket
dot
id|size
op_assign
l_int|0x80000
suffix:semicolon
id|ipaq_map
(braket
l_int|0
)braket
dot
id|set_vpp
op_assign
id|h3xxx_set_vpp
suffix:semicolon
id|ipaq_map
(braket
l_int|0
)braket
dot
id|phys
op_assign
l_int|0x0
suffix:semicolon
id|ipaq_map
(braket
l_int|0
)braket
dot
id|virt
op_assign
id|__ioremap
c_func
(paren
l_int|0x0
comma
l_int|0x04000000
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|ipaq_map
(braket
l_int|0
)braket
dot
id|bankwidth
op_assign
l_int|2
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;iPAQ flash: probing %d-bit flash bus, window=%lx with JEDEC.&bslash;n&quot;
comma
id|ipaq_map
(braket
l_int|0
)braket
dot
id|bankwidth
op_star
l_int|8
comma
id|ipaq_map
(braket
l_int|0
)braket
dot
id|virt
)paren
suffix:semicolon
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;jedec_probe&quot;
comma
op_amp
id|ipaq_map
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|add_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;iPAQ flash: registered h1910 flash&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ipaq_mtd_init
id|module_init
c_func
(paren
id|ipaq_mtd_init
)paren
suffix:semicolon
DECL|variable|ipaq_mtd_cleanup
id|module_exit
c_func
(paren
id|ipaq_mtd_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jamey Hicks&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IPAQ CFI map driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;MIT&quot;
)paren
suffix:semicolon
eof
