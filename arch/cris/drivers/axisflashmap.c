multiline_comment|/*&n; * Physical mapping layer for MTD using the Axis partitiontable format&n; *&n; * Copyright (c) 2001 Axis Communications AB&n; *&n; * This file is under the GPL.&n; *&n; * First partition is always sector 0 regardless of if we find a partitiontable&n; * or not. In the start of the next sector, there can be a partitiontable that&n; * tells us what other partitions to define. If there isn&squot;t, we use a default&n; * partition split defined below.&n; *&n; * $Log: axisflashmap.c,v $&n; * Revision 1.1  2001/01/12 17:01:18  bjornw&n; * * Added axisflashmap.c, a physical mapping for MTD that reads and understands&n; *   Axis partition-table format.&n; *&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/axisflashmap.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#ifdef CONFIG_CRIS_LOW_MAP
DECL|macro|FLASH_UNCACHED_ADDR
mdefine_line|#define FLASH_UNCACHED_ADDR  KSEG_E
DECL|macro|FLASH_CACHED_ADDR
mdefine_line|#define FLASH_CACHED_ADDR    KSEG_5
macro_line|#else
DECL|macro|FLASH_UNCACHED_ADDR
mdefine_line|#define FLASH_UNCACHED_ADDR  KSEG_E
DECL|macro|FLASH_CACHED_ADDR
mdefine_line|#define FLASH_CACHED_ADDR    KSEG_F
macro_line|#endif
multiline_comment|/*&n; * WINDOW_SIZE is the total size where the flash chips are mapped,&n; * my guess is that this can be the total memory area even if there&n; * are many flash chips inside the area or if they are not all mounted.&n; * So possibly we can get rid of the CONFIG_ here and just write something&n; * like 32 MB always.&n; */
DECL|macro|WINDOW_SIZE
mdefine_line|#define WINDOW_SIZE  (CONFIG_ETRAX_FLASH_LENGTH * 1024 * 1024)
multiline_comment|/* Byte-offset where the partition-table is placed in the first chip&n; */
DECL|macro|PTABLE_SECTOR
mdefine_line|#define PTABLE_SECTOR 65536
multiline_comment|/* &n; * Map driver&n; *&n; * Ok this is the scoop - we need to access the flash both with and without&n; * the cache - without when doing all the fancy flash interfacing, and with&n; * when we do actual copying because otherwise it will be slow like molasses.&n; * I hope this works the way it&squot;s intended, so that there won&squot;t be any cases&n; * of non-synchronicity because of the different access modes below...&n; */
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
id|FLASH_UNCACHED_ADDR
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
id|FLASH_UNCACHED_ADDR
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
id|FLASH_UNCACHED_ADDR
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
id|FLASH_CACHED_ADDR
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
id|FLASH_UNCACHED_ADDR
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
id|FLASH_UNCACHED_ADDR
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
id|FLASH_UNCACHED_ADDR
op_plus
id|adr
)paren
op_assign
id|d
suffix:semicolon
)brace
DECL|function|flash_copy_to
r_static
r_void
id|flash_copy_to
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|to
comma
r_const
r_void
op_star
id|from
comma
id|ssize_t
id|len
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|FLASH_CACHED_ADDR
op_plus
id|to
)paren
comma
id|from
comma
id|len
)paren
suffix:semicolon
)brace
DECL|variable|axis_map
r_static
r_struct
id|map_info
id|axis_map
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Axis flash&quot;
comma
id|size
suffix:colon
id|WINDOW_SIZE
comma
id|buswidth
suffix:colon
id|CONFIG_ETRAX_FLASH_BUSWIDTH
comma
id|read8
suffix:colon
id|flash_read8
comma
id|read16
suffix:colon
id|flash_read16
comma
id|read32
suffix:colon
id|flash_read32
comma
id|copy_from
suffix:colon
id|flash_copy_from
comma
id|write8
suffix:colon
id|flash_write8
comma
id|write16
suffix:colon
id|flash_write16
comma
id|write32
suffix:colon
id|flash_write32
comma
id|copy_to
suffix:colon
id|flash_copy_to
)brace
suffix:semicolon
multiline_comment|/* If no partition-table was found, we use this default-set.&n; */
DECL|macro|MAX_PARTITIONS
mdefine_line|#define MAX_PARTITIONS         7  
DECL|macro|NUM_DEFAULT_PARTITIONS
mdefine_line|#define NUM_DEFAULT_PARTITIONS 3
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
id|name
suffix:colon
l_string|&quot;boot firmware&quot;
comma
id|size
suffix:colon
id|PTABLE_SECTOR
comma
id|offset
suffix:colon
l_int|0
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;kernel&quot;
comma
id|size
suffix:colon
l_int|0x1a0000
comma
id|offset
suffix:colon
id|PTABLE_SECTOR
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;filesystem&quot;
comma
id|size
suffix:colon
l_int|0x50000
comma
id|offset
suffix:colon
(paren
l_int|0x1a0000
op_plus
id|PTABLE_SECTOR
)paren
)brace
)brace
suffix:semicolon
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
id|name
suffix:colon
l_string|&quot;part0&quot;
comma
id|size
suffix:colon
l_int|0
comma
id|offset
suffix:colon
l_int|0
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;part1&quot;
comma
id|size
suffix:colon
l_int|0
comma
id|offset
suffix:colon
l_int|0
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;part2&quot;
comma
id|size
suffix:colon
l_int|0
comma
id|offset
suffix:colon
l_int|0
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;part3&quot;
comma
id|size
suffix:colon
l_int|0
comma
id|offset
suffix:colon
l_int|0
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;part4&quot;
comma
id|size
suffix:colon
l_int|0
comma
id|offset
suffix:colon
l_int|0
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;part5&quot;
comma
id|size
suffix:colon
l_int|0
comma
id|offset
suffix:colon
l_int|0
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;part6&quot;
comma
id|size
suffix:colon
l_int|0
comma
id|offset
suffix:colon
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* &n; * This is the master MTD device for which all the others are just&n; * auto-relocating aliases.&n; */
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
multiline_comment|/* CFI-scan the flash, and if there was a chip, read the partition-table&n; * and register the partitions with MTD.&n; */
r_static
r_int
id|__init
DECL|function|init_axis_flash
id|init_axis_flash
c_func
(paren
r_void
)paren
(brace
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
multiline_comment|/* Until proven otherwise */
r_const
r_char
op_star
id|pmsg
op_assign
l_string|&quot;  /dev/flash%d at 0x%x, size 0x%x&bslash;n&quot;
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Axis flash mapping: %x at %x&bslash;n&quot;
comma
id|WINDOW_SIZE
comma
id|FLASH_CACHED_ADDR
)paren
suffix:semicolon
id|mymtd
op_assign
id|do_cfi_probe
c_func
(paren
op_amp
id|axis_map
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
l_string|&quot;cfi_probe erred %d&bslash;n&quot;
comma
id|mymtd
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|mymtd-&gt;module
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/* The partition-table is at an offset within the second &n;&t; * sector of the flash. We _define_ this to be at offset 64k&n;&t; * even if the actual sector-size in the flash changes.. for&n;&t; * now at least.&n;&t; */
id|ptable_head
op_assign
id|FLASH_CACHED_ADDR
op_plus
id|PTABLE_SECTOR
op_plus
id|PARTITION_TABLE_OFFSET
suffix:semicolon
id|pidx
op_increment
suffix:semicolon
multiline_comment|/* first partition is always set to the default */
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
l_int|4
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
l_int|4
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
id|PTABLE_SECTOR
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
multiline_comment|/* printk(&quot;  total csum: 0x%08X 0x%08X&bslash;n&quot;,&n;&t;&t;   csum, ptable_head-&gt;checksum); */
id|ptable_ok
op_assign
(paren
id|csum
op_eq
id|ptable_head-&gt;checksum
)paren
suffix:semicolon
multiline_comment|/* Read the entries and use/show the info.  */
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
id|printk
c_func
(paren
l_string|&quot; Found %s partition table at 0x%08lX-0x%08lX.&bslash;n&quot;
comma
(paren
id|ptable_ok
ques
c_cond
l_string|&quot;valid&quot;
suffix:colon
l_string|&quot;invalid&quot;
)paren
comma
(paren
r_int
r_int
)paren
id|ptable_head
comma
(paren
r_int
r_int
)paren
id|max_addr
)paren
suffix:semicolon
multiline_comment|/* We have found a working bootblock.  Now read the&n;&t;&t;   partition table.  Scan the table.  It ends when&n;&t;&t;   there is 0xffffffff, that is, empty flash.  */
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
macro_line|#if 0
multiline_comment|/* wait with multi-chip support until we know&n;&t;&t;&t; * how mtd detects multiple chips&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|offset
op_plus
id|ptable-&gt;offset
)paren
op_ge
id|chips
(braket
l_int|0
)braket
dot
id|size
)paren
(brace
id|partitions
(braket
id|pidx
)braket
dot
id|start
op_assign
id|offset
op_plus
id|chips
(braket
l_int|1
)braket
dot
id|start
op_plus
id|ptable-&gt;offset
op_minus
id|chips
(braket
l_int|0
)braket
dot
id|size
suffix:semicolon
)brace
macro_line|#endif
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
id|use_default_ptable
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; Using default partition table&bslash;n&quot;
)paren
suffix:semicolon
r_return
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
r_return
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
)brace
multiline_comment|/* This adds the above to the kernels init-call chain */
DECL|variable|init_axis_flash
id|module_init
c_func
(paren
id|init_axis_flash
)paren
suffix:semicolon
eof
