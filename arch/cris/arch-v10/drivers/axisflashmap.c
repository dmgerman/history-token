multiline_comment|/*&n; * Physical mapping layer for MTD using the Axis partitiontable format&n; *&n; * Copyright (c) 2001, 2002 Axis Communications AB&n; *&n; * This file is under the GPL.&n; *&n; * First partition is always sector 0 regardless of if we find a partitiontable&n; * or not. In the start of the next sector, there can be a partitiontable that&n; * tells us what other partitions to define. If there isn&squot;t, we use a default&n; * partition split defined below.&n; *&n; * $Log: axisflashmap.c,v $&n; * Revision 1.6  2003/07/04 08:27:37  starvik&n; * Merge of Linux 2.5.74&n; *&n; * Revision 1.5  2002/12/11 13:13:57  starvik&n; * Added arch/ to v10 specific includes&n; * Added fix from Linux 2.4 in serial.c (flush_to_flip_buffer)&n; *&n; * Revision 1.4  2002/11/20 11:56:10  starvik&n; * Merge of Linux 2.5.48&n; *&n; * Revision 1.3  2002/11/13 14:54:13  starvik&n; * Copied from linux 2.4&n; *&n; * Revision 1.28  2002/10/01 08:08:43  jonashg&n; * The first partition ends at the start of the partition table.&n; *&n; * Revision 1.27  2002/08/21 09:23:13  jonashg&n; * Speling.&n; *&n; * Revision 1.26  2002/08/21 08:35:20  jonashg&n; * Cosmetic change to printouts.&n; *&n; * Revision 1.25  2002/08/21 08:15:42  jonashg&n; * Made it compile even without CONFIG_MTD_CONCAT defined.&n; *&n; * Revision 1.24  2002/08/20 13:12:35  jonashg&n; * * New approach to probing. Probe cse0 and cse1 separately and (mtd)concat&n; *   the results.&n; * * Removed compile time tests concerning how the mtdram driver has been&n; *   configured. The user will know about the misconfiguration at runtime&n; *   instead. (The old approach made it impossible to use mtdram for anything&n; *   else than RAM boot).&n; *&n; * Revision 1.23  2002/05/13 12:12:28  johana&n; * Allow compile without CONFIG_MTD_MTDRAM but warn at compiletime and&n; * be informative at runtime.&n; *&n; * Revision 1.22  2002/05/13 10:24:44  johana&n; * Added #if checks on MTDRAM CONFIG&n; *&n; * Revision 1.21  2002/05/06 16:05:20  johana&n; * Removed debug printout.&n; *&n; * Revision 1.20  2002/05/06 16:03:00  johana&n; * No more cramfs as root hack in generic code.&n; * It&squot;s handled by axisflashmap using mtdram.&n; *&n; * Revision 1.19  2002/03/15 17:10:28  bjornw&n; * Changed comment about cached access since we changed this before&n; *&n; * Revision 1.18  2002/03/05 17:06:15  jonashg&n; * Try amd_flash probe before cfi_probe since amd_flash driver can handle two&n; * (or more) flash chips of different model and the cfi driver cannot.&n; *&n; * Revision 1.17  2001/11/12 19:42:38  pkj&n; * Fixed compiler warnings.&n; *&n; * Revision 1.16  2001/11/08 11:18:58  jonashg&n; * Always read from uncached address to avoid problems with flushing&n; * cachelines after write and MTD-erase. No performance loss have been&n; * seen yet.&n; *&n; * Revision 1.15  2001/10/19 12:41:04  jonashg&n; * Name of probe has changed in MTD.&n; *&n; * Revision 1.14  2001/09/21 07:14:10  jonashg&n; * Made root filesystem (cramfs) use mtdblock driver when booting from flash.&n; *&n; * Revision 1.13  2001/08/15 13:57:35  jonashg&n; * Entire MTD updated to the linux 2.4.7 version.&n; *&n; * Revision 1.12  2001/06/11 09:50:30  jonashg&n; * Oops, 2MB is 0x200000 bytes.&n; *&n; * Revision 1.11  2001/06/08 11:39:44  jonashg&n; * Changed sizes and offsets in axis_default_partitions to use&n; * CONFIG_ETRAX_PTABLE_SECTOR.&n; *&n; * Revision 1.10  2001/05/29 09:42:03  jonashg&n; * Use macro for end marker length instead of sizeof.&n; *&n; * Revision 1.9  2001/05/29 08:52:52  jonashg&n; * Gave names to the magic fours (size of the ptable end marker).&n; *&n; * Revision 1.8  2001/05/28 15:36:20  jonashg&n; * * Removed old comment about ptable location in flash (it&squot;s a CONFIG_ option).&n; * * Variable ptable was initialized twice to the same value.&n; *&n; * Revision 1.7  2001/04/05 13:41:46  markusl&n; * Updated according to review remarks&n; *&n; * Revision 1.6  2001/03/07 09:21:21  bjornw&n; * No need to waste .data&n; *&n; * Revision 1.5  2001/03/06 16:27:01  jonashg&n; * Probe the entire flash area for flash devices.&n; *&n; * Revision 1.4  2001/02/23 12:47:15  bjornw&n; * Uncached flash in LOW_MAP moved from 0xe to 0x8&n; *&n; * Revision 1.3  2001/02/16 12:11:45  jonashg&n; * MTD driver amd_flash is now included in MTD CVS repository.&n; * (It&squot;s now in drivers/mtd).&n; *&n; * Revision 1.2  2001/02/09 11:12:22  jonashg&n; * Support for AMD compatible non-CFI flash chips.&n; * Only tested with Toshiba TC58FVT160 so far.&n; *&n; * Revision 1.1  2001/01/12 17:01:18  bjornw&n; * * Added axisflashmap.c, a physical mapping for MTD that reads and understands&n; *   Axis partition-table format.&n; *&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mtd/concat.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/mtdram.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/axisflashmap.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/arch/sv_addr_ag.h&gt;
macro_line|#ifdef CONFIG_CRIS_LOW_MAP
DECL|macro|FLASH_UNCACHED_ADDR
mdefine_line|#define FLASH_UNCACHED_ADDR  KSEG_8
DECL|macro|FLASH_CACHED_ADDR
mdefine_line|#define FLASH_CACHED_ADDR    KSEG_5
macro_line|#else
DECL|macro|FLASH_UNCACHED_ADDR
mdefine_line|#define FLASH_UNCACHED_ADDR  KSEG_E
DECL|macro|FLASH_CACHED_ADDR
mdefine_line|#define FLASH_CACHED_ADDR    KSEG_F
macro_line|#endif
multiline_comment|/* From head.S */
r_extern
r_int
r_int
id|romfs_start
comma
id|romfs_length
comma
id|romfs_in_flash
suffix:semicolon
multiline_comment|/* Map driver functions. */
DECL|function|flash_read8
r_static
id|__u8
id|flash_read8
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|ofs
)paren
(brace
r_return
op_star
(paren
id|__u8
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|ofs
)paren
suffix:semicolon
)brace
DECL|function|flash_read16
r_static
id|__u16
id|flash_read16
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|ofs
)paren
(brace
r_return
op_star
(paren
id|__u16
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|ofs
)paren
suffix:semicolon
)brace
DECL|function|flash_read32
r_static
id|__u32
id|flash_read32
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|ofs
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|ofs
)paren
suffix:semicolon
)brace
DECL|function|flash_copy_from
r_static
r_void
id|flash_copy_from
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_void
op_star
id|to
comma
r_int
r_int
id|from
comma
id|ssize_t
id|len
)paren
(brace
id|memcpy
c_func
(paren
id|to
comma
(paren
r_void
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|from
)paren
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|flash_write8
r_static
r_void
id|flash_write8
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u8
id|d
comma
r_int
r_int
id|adr
)paren
(brace
op_star
(paren
id|__u8
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|adr
)paren
op_assign
id|d
suffix:semicolon
)brace
DECL|function|flash_write16
r_static
r_void
id|flash_write16
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u16
id|d
comma
r_int
r_int
id|adr
)paren
(brace
op_star
(paren
id|__u16
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|adr
)paren
op_assign
id|d
suffix:semicolon
)brace
DECL|function|flash_write32
r_static
r_void
id|flash_write32
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u32
id|d
comma
r_int
r_int
id|adr
)paren
(brace
op_star
(paren
id|__u32
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|adr
)paren
op_assign
id|d
suffix:semicolon
)brace
multiline_comment|/*&n; * The map for chip select e0.&n; *&n; * We run into tricky coherence situations if we mix cached with uncached&n; * accesses to we only use the uncached version here.&n; *&n; * The size field is the total size where the flash chips may be mapped on the&n; * chip select. MTD probes should find all devices there and it does not matter&n; * if there are unmapped gaps or aliases (mirrors of flash devices). The MTD&n; * probes will ignore them.&n; *&n; * The start address in map_priv_1 is in virtual memory so we cannot use&n; * MEM_CSE0_START but must rely on that FLASH_UNCACHED_ADDR is the start&n; * address of cse0.&n; */
DECL|variable|map_cse0
r_static
r_struct
id|map_info
id|map_cse0
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;cse0&quot;
comma
dot
id|size
op_assign
id|MEM_CSE0_SIZE
comma
dot
id|buswidth
op_assign
id|CONFIG_ETRAX_FLASH_BUSWIDTH
comma
dot
id|read8
op_assign
id|flash_read8
comma
dot
id|read16
op_assign
id|flash_read16
comma
dot
id|read32
op_assign
id|flash_read32
comma
dot
id|copy_from
op_assign
id|flash_copy_from
comma
dot
id|write8
op_assign
id|flash_write8
comma
dot
id|write16
op_assign
id|flash_write16
comma
dot
id|write32
op_assign
id|flash_write32
comma
dot
id|map_priv_1
op_assign
id|FLASH_UNCACHED_ADDR
)brace
suffix:semicolon
multiline_comment|/*&n; * The map for chip select e1.&n; *&n; * If there was a gap between cse0 and cse1, map_priv_1 would get the wrong&n; * address, but there isn&squot;t.&n; */
DECL|variable|map_cse1
r_static
r_struct
id|map_info
id|map_cse1
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;cse1&quot;
comma
dot
id|size
op_assign
id|MEM_CSE1_SIZE
comma
dot
id|buswidth
op_assign
id|CONFIG_ETRAX_FLASH_BUSWIDTH
comma
dot
id|read8
op_assign
id|flash_read8
comma
dot
id|read16
op_assign
id|flash_read16
comma
dot
id|read32
op_assign
id|flash_read32
comma
dot
id|copy_from
op_assign
id|flash_copy_from
comma
dot
id|write8
op_assign
id|flash_write8
comma
dot
id|write16
op_assign
id|flash_write16
comma
dot
id|write32
op_assign
id|flash_write32
comma
dot
id|map_priv_1
op_assign
id|FLASH_UNCACHED_ADDR
op_plus
id|MEM_CSE0_SIZE
)brace
suffix:semicolon
multiline_comment|/* If no partition-table was found, we use this default-set. */
DECL|macro|MAX_PARTITIONS
mdefine_line|#define MAX_PARTITIONS         7  
DECL|macro|NUM_DEFAULT_PARTITIONS
mdefine_line|#define NUM_DEFAULT_PARTITIONS 3
multiline_comment|/*&n; * Default flash size is 2MB. CONFIG_ETRAX_PTABLE_SECTOR is most likely the&n; * size of one flash block and &quot;filesystem&quot;-partition needs 5 blocks to be able&n; * to use JFFS.&n; */
DECL|variable|axis_default_partitions
r_static
r_struct
id|mtd_partition
id|axis_default_partitions
(braket
id|NUM_DEFAULT_PARTITIONS
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;boot firmware&quot;
comma
dot
id|size
op_assign
id|CONFIG_ETRAX_PTABLE_SECTOR
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
l_string|&quot;kernel&quot;
comma
dot
id|size
op_assign
l_int|0x200000
op_minus
(paren
l_int|6
op_star
id|CONFIG_ETRAX_PTABLE_SECTOR
)paren
comma
dot
id|offset
op_assign
id|CONFIG_ETRAX_PTABLE_SECTOR
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;filesystem&quot;
comma
dot
id|size
op_assign
l_int|5
op_star
id|CONFIG_ETRAX_PTABLE_SECTOR
comma
dot
id|offset
op_assign
l_int|0x200000
op_minus
(paren
l_int|5
op_star
id|CONFIG_ETRAX_PTABLE_SECTOR
)paren
)brace
)brace
suffix:semicolon
multiline_comment|/* Initialize the ones normally used. */
DECL|variable|axis_partitions
r_static
r_struct
id|mtd_partition
id|axis_partitions
(braket
id|MAX_PARTITIONS
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;part0&quot;
comma
dot
id|size
op_assign
id|CONFIG_ETRAX_PTABLE_SECTOR
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
l_string|&quot;part1&quot;
comma
dot
id|size
op_assign
l_int|0
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
l_string|&quot;part2&quot;
comma
dot
id|size
op_assign
l_int|0
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
l_string|&quot;part3&quot;
comma
dot
id|size
op_assign
l_int|0
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
l_string|&quot;part4&quot;
comma
dot
id|size
op_assign
l_int|0
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
l_string|&quot;part5&quot;
comma
dot
id|size
op_assign
l_int|0
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
l_string|&quot;part6&quot;
comma
dot
id|size
op_assign
l_int|0
comma
dot
id|offset
op_assign
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Probe a chip select for AMD-compatible (JEDEC) or CFI-compatible flash&n; * chips in that order (because the amd_flash-driver is faster).&n; */
DECL|function|probe_cs
r_static
r_struct
id|mtd_info
op_star
id|probe_cs
c_func
(paren
r_struct
id|map_info
op_star
id|map_cs
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd_cs
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Probing a 0x%08lx bytes large window at 0x%08lx.&bslash;n&quot;
comma
id|map_cs-&gt;name
comma
id|map_cs-&gt;size
comma
id|map_cs-&gt;map_priv_1
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MTD_AMDSTD
id|mtd_cs
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;amd_flash&quot;
comma
id|map_cs
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI
r_if
c_cond
(paren
op_logical_neg
id|mtd_cs
)paren
(brace
id|mtd_cs
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
id|map_cs
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|mtd_cs
suffix:semicolon
)brace
multiline_comment|/* &n; * Probe each chip select individually for flash chips. If there are chips on&n; * both cse0 and cse1, the mtd_info structs will be concatenated to one struct&n; * so that MTD partitions can cross chip boundries.&n; *&n; * The only known restriction to how you can mount your chips is that each&n; * chip select must hold similar flash chips. But you need external hardware&n; * to do that anyway and you can put totally different chips on cse0 and cse1&n; * so it isn&squot;t really much of a restriction.&n; */
DECL|function|flash_probe
r_static
r_struct
id|mtd_info
op_star
id|flash_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd_cse0
suffix:semicolon
r_struct
id|mtd_info
op_star
id|mtd_cse1
suffix:semicolon
r_struct
id|mtd_info
op_star
id|mtd_cse
suffix:semicolon
id|mtd_cse0
op_assign
id|probe_cs
c_func
(paren
op_amp
id|map_cse0
)paren
suffix:semicolon
id|mtd_cse1
op_assign
id|probe_cs
c_func
(paren
op_amp
id|map_cse1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd_cse0
op_logical_and
op_logical_neg
id|mtd_cse1
)paren
(brace
multiline_comment|/* No chip found. */
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mtd_cse0
op_logical_and
id|mtd_cse1
)paren
(brace
macro_line|#ifdef CONFIG_MTD_CONCAT
r_struct
id|mtd_info
op_star
id|mtds
(braket
)braket
op_assign
(brace
id|mtd_cse0
comma
id|mtd_cse1
)brace
suffix:semicolon
multiline_comment|/* Since the concatenation layer adds a small overhead we&n;&t;&t; * could try to figure out if the chips in cse0 and cse1 are&n;&t;&t; * identical and reprobe the whole cse0+cse1 window. But since&n;&t;&t; * flash chips are slow, the overhead is relatively small.&n;&t;&t; * So we use the MTD concatenation layer instead of further&n;&t;&t; * complicating the probing procedure.&n;&t;&t; */
id|mtd_cse
op_assign
id|mtd_concat_create
c_func
(paren
id|mtds
comma
r_sizeof
(paren
id|mtds
)paren
op_div
r_sizeof
(paren
id|mtds
(braket
l_int|0
)braket
)paren
comma
l_string|&quot;cse0+cse1&quot;
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s and %s: Cannot concatenate due to kernel &quot;
l_string|&quot;(mis)configuration!&bslash;n&quot;
comma
id|map_cse0.name
comma
id|map_cse1.name
)paren
suffix:semicolon
id|mtd_cse
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|mtd_cse
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s and %s: Concatenation failed!&bslash;n&quot;
comma
id|map_cse0.name
comma
id|map_cse1.name
)paren
suffix:semicolon
multiline_comment|/* The best we can do now is to only use what we found&n;&t;&t;&t; * at cse0.&n;&t;&t;&t; */
id|mtd_cse
op_assign
id|mtd_cse0
suffix:semicolon
id|map_destroy
c_func
(paren
id|mtd_cse1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|mtd_cse
op_assign
id|mtd_cse0
ques
c_cond
id|mtd_cse0
suffix:colon
id|mtd_cse1
suffix:semicolon
)brace
r_return
id|mtd_cse
suffix:semicolon
)brace
multiline_comment|/*&n; * Probe the flash chip(s) and, if it succeeds, read the partition-table&n; * and register the partitions with MTD.&n; */
DECL|function|init_axis_flash
r_static
r_int
id|__init
id|init_axis_flash
c_func
(paren
r_void
)paren
(brace
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|pidx
op_assign
l_int|0
suffix:semicolon
r_struct
id|partitiontable_head
op_star
id|ptable_head
suffix:semicolon
r_struct
id|partitiontable_entry
op_star
id|ptable
suffix:semicolon
r_int
id|use_default_ptable
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Until proven otherwise. */
r_const
r_char
op_star
id|pmsg
op_assign
l_string|&quot;  /dev/flash%d at 0x%08x, size 0x%08x&bslash;n&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mymtd
op_assign
id|flash_probe
c_func
(paren
)paren
)paren
)paren
(brace
multiline_comment|/* There&squot;s no reason to use this module if no flash chip can&n;&t;&t; * be identified. Make sure that&squot;s understood.&n;&t;&t; */
id|panic
c_func
(paren
l_string|&quot;axisflashmap found no flash chip!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s: 0x%08x bytes of flash memory.&bslash;n&quot;
comma
id|mymtd-&gt;name
comma
id|mymtd-&gt;size
)paren
suffix:semicolon
id|mymtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|ptable_head
op_assign
(paren
r_struct
id|partitiontable_head
op_star
)paren
(paren
id|FLASH_CACHED_ADDR
op_plus
id|CONFIG_ETRAX_PTABLE_SECTOR
op_plus
id|PARTITION_TABLE_OFFSET
)paren
suffix:semicolon
id|pidx
op_increment
suffix:semicolon
multiline_comment|/* First partition is always set to the default. */
r_if
c_cond
(paren
(paren
id|ptable_head-&gt;magic
op_eq
id|PARTITION_TABLE_MAGIC
)paren
op_logical_and
(paren
id|ptable_head-&gt;size
OL
(paren
id|MAX_PARTITIONS
op_star
r_sizeof
(paren
r_struct
id|partitiontable_entry
)paren
op_plus
id|PARTITIONTABLE_END_MARKER_SIZE
)paren
)paren
op_logical_and
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
(paren
r_void
op_star
)paren
id|ptable_head
op_plus
r_sizeof
(paren
op_star
id|ptable_head
)paren
op_plus
id|ptable_head-&gt;size
op_minus
id|PARTITIONTABLE_END_MARKER_SIZE
)paren
op_eq
id|PARTITIONTABLE_END_MARKER
)paren
)paren
(brace
multiline_comment|/* Looks like a start, sane length and end of a&n;&t;&t; * partition table, lets check csum etc.&n;&t;&t; */
r_int
id|ptable_ok
op_assign
l_int|0
suffix:semicolon
r_struct
id|partitiontable_entry
op_star
id|max_addr
op_assign
(paren
r_struct
id|partitiontable_entry
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|ptable_head
op_plus
r_sizeof
(paren
op_star
id|ptable_head
)paren
op_plus
id|ptable_head-&gt;size
)paren
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|CONFIG_ETRAX_PTABLE_SECTOR
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
r_int
r_int
id|csum
op_assign
l_int|0
suffix:semicolon
id|ptable
op_assign
(paren
r_struct
id|partitiontable_entry
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|ptable_head
op_plus
r_sizeof
(paren
op_star
id|ptable_head
)paren
)paren
suffix:semicolon
multiline_comment|/* Lets be PARANOID, and check the checksum. */
id|p
op_assign
(paren
r_int
r_char
op_star
)paren
id|ptable
suffix:semicolon
r_while
c_loop
(paren
id|p
op_le
(paren
r_int
r_char
op_star
)paren
id|max_addr
)paren
(brace
id|csum
op_add_assign
op_star
id|p
op_increment
suffix:semicolon
id|csum
op_add_assign
op_star
id|p
op_increment
suffix:semicolon
id|csum
op_add_assign
op_star
id|p
op_increment
suffix:semicolon
id|csum
op_add_assign
op_star
id|p
op_increment
suffix:semicolon
)brace
id|ptable_ok
op_assign
(paren
id|csum
op_eq
id|ptable_head-&gt;checksum
)paren
suffix:semicolon
multiline_comment|/* Read the entries and use/show the info.  */
id|printk
c_func
(paren
l_string|&quot; Found a%s partition table at 0x%p-0x%p.&bslash;n&quot;
comma
(paren
id|ptable_ok
ques
c_cond
l_string|&quot; valid&quot;
suffix:colon
l_string|&quot;n invalid&quot;
)paren
comma
id|ptable_head
comma
id|max_addr
)paren
suffix:semicolon
multiline_comment|/* We have found a working bootblock.  Now read the&n;&t;&t; * partition table.  Scan the table.  It ends when&n;&t;&t; * there is 0xffffffff, that is, empty flash.&n;&t;&t; */
r_while
c_loop
(paren
id|ptable_ok
op_logical_and
id|ptable-&gt;offset
op_ne
l_int|0xffffffff
op_logical_and
id|ptable
OL
id|max_addr
op_logical_and
id|pidx
OL
id|MAX_PARTITIONS
)paren
(brace
id|axis_partitions
(braket
id|pidx
)braket
dot
id|offset
op_assign
id|offset
op_plus
id|ptable-&gt;offset
suffix:semicolon
id|axis_partitions
(braket
id|pidx
)braket
dot
id|size
op_assign
id|ptable-&gt;size
suffix:semicolon
id|printk
c_func
(paren
id|pmsg
comma
id|pidx
comma
id|axis_partitions
(braket
id|pidx
)braket
dot
id|offset
comma
id|axis_partitions
(braket
id|pidx
)braket
dot
id|size
)paren
suffix:semicolon
id|pidx
op_increment
suffix:semicolon
id|ptable
op_increment
suffix:semicolon
)brace
id|use_default_ptable
op_assign
op_logical_neg
id|ptable_ok
suffix:semicolon
)brace
r_if
c_cond
(paren
id|romfs_in_flash
)paren
(brace
multiline_comment|/* Add an overlapping device for the root partition (romfs). */
id|axis_partitions
(braket
id|pidx
)braket
dot
id|name
op_assign
l_string|&quot;romfs&quot;
suffix:semicolon
id|axis_partitions
(braket
id|pidx
)braket
dot
id|size
op_assign
id|romfs_length
suffix:semicolon
id|axis_partitions
(braket
id|pidx
)braket
dot
id|offset
op_assign
id|romfs_start
op_minus
id|FLASH_CACHED_ADDR
suffix:semicolon
id|axis_partitions
(braket
id|pidx
)braket
dot
id|mask_flags
op_or_assign
id|MTD_WRITEABLE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; Adding readonly flash partition for romfs image:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|pmsg
comma
id|pidx
comma
id|axis_partitions
(braket
id|pidx
)braket
dot
id|offset
comma
id|axis_partitions
(braket
id|pidx
)braket
dot
id|size
)paren
suffix:semicolon
id|pidx
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|use_default_ptable
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; Using default partition table.&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
id|add_mtd_partitions
c_func
(paren
id|mymtd
comma
id|axis_default_partitions
comma
id|NUM_DEFAULT_PARTITIONS
)paren
suffix:semicolon
)brace
r_else
(brace
id|err
op_assign
id|add_mtd_partitions
c_func
(paren
id|mymtd
comma
id|axis_partitions
comma
id|pidx
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;axisflashmap could not add MTD partitions!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|romfs_in_flash
)paren
(brace
multiline_comment|/* Create an RAM device for the root partition (romfs). */
macro_line|#if !defined(CONFIG_MTD_MTDRAM) || (CONFIG_MTDRAM_TOTAL_SIZE != 0) || (CONFIG_MTDRAM_ABS_POS != 0)
multiline_comment|/* No use trying to boot this kernel from RAM. Panic! */
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;axisflashmap: Cannot create an MTD RAM &quot;
l_string|&quot;device due to kernel (mis)configuration!&bslash;n&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;This kernel cannot boot from RAM!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
r_struct
id|mtd_info
op_star
id|mtd_ram
suffix:semicolon
id|mtd_ram
op_assign
(paren
r_struct
id|mtd_info
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mtd_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd_ram
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;axisflashmap couldn&squot;t allocate memory for &quot;
l_string|&quot;mtd_info!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; Adding RAM partition for romfs image:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|pmsg
comma
id|pidx
comma
id|romfs_start
comma
id|romfs_length
)paren
suffix:semicolon
id|err
op_assign
id|mtdram_init_device
c_func
(paren
id|mtd_ram
comma
(paren
r_void
op_star
)paren
id|romfs_start
comma
id|romfs_length
comma
l_string|&quot;romfs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;axisflashmap could not initialize MTD RAM &quot;
l_string|&quot;device!&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* This adds the above to the kernels init-call chain. */
DECL|variable|init_axis_flash
id|module_init
c_func
(paren
id|init_axis_flash
)paren
suffix:semicolon
eof
