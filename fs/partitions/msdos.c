multiline_comment|/*&n; *  fs/partitions/msdos.c&n; *&n; *  Code extracted from drivers/block/genhd.c&n; *  Copyright (C) 1991-1998  Linus Torvalds&n; *&n; *  Thanks to Branko Lankester, lankeste@fwi.uva.nl, who found a bug&n; *  in the early extended-partition checks and added DM partitions&n; *&n; *  Support for DiskManager v6.0x added by Mark Lord,&n; *  with information provided by OnTrack.  This now works for linux fdisk&n; *  and LILO, as well as loadlin and bootln.  Note that disks other than&n; *  /dev/hda *must* have a &quot;DOS&quot; type 0x51 partition in the first slot (hda1).&n; *&n; *  More flexible handling of extended partitions - aeb, 950831&n; *&n; *  Check partition table on IDE disks for common CHS translations&n; *&n; *  Re-organised Feb 1998 Russell King&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;check.h&quot;
macro_line|#include &quot;msdos.h&quot;
macro_line|#include &quot;efi.h&quot;
multiline_comment|/*&n; * Many architectures don&squot;t like unaligned accesses, while&n; * the nr_sects and start_sect partition table entries are&n; * at a 2 (mod 4) address.&n; */
macro_line|#include &lt;asm/unaligned.h&gt;
DECL|macro|SYS_IND
mdefine_line|#define SYS_IND(p)&t;(get_unaligned(&amp;p-&gt;sys_ind))
DECL|macro|NR_SECTS
mdefine_line|#define NR_SECTS(p)&t;({ __typeof__(p-&gt;nr_sects) __a =&t;&bslash;&n;&t;&t;&t;&t;get_unaligned(&amp;p-&gt;nr_sects);&t;&bslash;&n;&t;&t;&t;&t;le32_to_cpu(__a); &bslash;&n;&t;&t;&t;})
DECL|macro|START_SECT
mdefine_line|#define START_SECT(p)&t;({ __typeof__(p-&gt;start_sect) __a =&t;&bslash;&n;&t;&t;&t;&t;get_unaligned(&amp;p-&gt;start_sect);&t;&bslash;&n;&t;&t;&t;&t;le32_to_cpu(__a); &bslash;&n;&t;&t;&t;})
DECL|function|is_extended_partition
r_static
r_inline
r_int
id|is_extended_partition
c_func
(paren
r_struct
id|partition
op_star
id|p
)paren
(brace
r_return
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|DOS_EXTENDED_PARTITION
op_logical_or
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|WIN98_EXTENDED_PARTITION
op_logical_or
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|LINUX_EXTENDED_PARTITION
)paren
suffix:semicolon
)brace
DECL|macro|MSDOS_LABEL_MAGIC1
mdefine_line|#define MSDOS_LABEL_MAGIC1&t;0x55
DECL|macro|MSDOS_LABEL_MAGIC2
mdefine_line|#define MSDOS_LABEL_MAGIC2&t;0xAA
r_static
r_inline
r_int
DECL|function|msdos_magic_present
id|msdos_magic_present
c_func
(paren
r_int
r_char
op_star
id|p
)paren
(brace
r_return
(paren
id|p
(braket
l_int|0
)braket
op_eq
id|MSDOS_LABEL_MAGIC1
op_logical_and
id|p
(braket
l_int|1
)braket
op_eq
id|MSDOS_LABEL_MAGIC2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create devices for each logical partition in an extended partition.&n; * The logical partitions form a linked list, with each entry being&n; * a partition table with two entries.  The first entry&n; * is the real data partition (with a start relative to the partition&n; * table start).  The second is a pointer to the next logical partition&n; * (with a start relative to the entire extended partition).&n; * We do not create a Linux partition for the partition tables, but&n; * only for the actual data partitions.&n; */
r_static
r_void
DECL|function|parse_extended
id|parse_extended
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|u32
id|first_sector
comma
id|u32
id|first_size
)paren
(brace
r_struct
id|partition
op_star
id|p
suffix:semicolon
id|Sector
id|sect
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
id|u32
id|this_sector
comma
id|this_size
suffix:semicolon
r_int
id|sector_size
op_assign
id|bdev_hardsect_size
c_func
(paren
id|bdev
)paren
op_div
l_int|512
suffix:semicolon
r_int
id|loopct
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* number of links followed&n;&t;&t;&t;&t;   without finding a data partition */
r_int
id|i
suffix:semicolon
id|this_sector
op_assign
id|first_sector
suffix:semicolon
id|this_size
op_assign
id|first_size
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_increment
id|loopct
OG
l_int|100
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;next
op_eq
id|state-&gt;limit
)paren
r_return
suffix:semicolon
id|data
op_assign
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|this_sector
comma
op_amp
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|msdos_magic_present
c_func
(paren
id|data
op_plus
l_int|510
)paren
)paren
r_goto
id|done
suffix:semicolon
id|p
op_assign
(paren
r_struct
id|partition
op_star
)paren
(paren
id|data
op_plus
l_int|0x1be
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Usually, the first entry is the real data partition,&n;&t;&t; * the 2nd entry is the next extended partition, or empty,&n;&t;&t; * and the 3rd and 4th entries are unused.&n;&t;&t; * However, DRDOS sometimes has the extended partition as&n;&t;&t; * the first entry (when the data partition is empty),&n;&t;&t; * and OS/2 seems to use all four entries.&n;&t;&t; */
multiline_comment|/* &n;&t;&t; * First process the data partition(s)&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
id|u32
id|offs
comma
id|size
comma
id|next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|NR_SECTS
c_func
(paren
id|p
)paren
op_logical_or
id|is_extended_partition
c_func
(paren
id|p
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Check the 3rd and 4th entries -&n;&t;&t;&t;   these sometimes contain random garbage */
id|offs
op_assign
id|START_SECT
c_func
(paren
id|p
)paren
op_star
id|sector_size
suffix:semicolon
id|size
op_assign
id|NR_SECTS
c_func
(paren
id|p
)paren
op_star
id|sector_size
suffix:semicolon
id|next
op_assign
id|this_sector
op_plus
id|offs
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|offs
op_plus
id|size
OG
id|this_size
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|next
OL
id|first_sector
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|next
op_plus
id|size
OG
id|first_sector
op_plus
id|first_size
)paren
r_continue
suffix:semicolon
)brace
id|put_partition
c_func
(paren
id|state
comma
id|state-&gt;next
comma
id|next
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|LINUX_RAID_PARTITION
)paren
id|state-&gt;parts
(braket
id|state-&gt;next
)braket
dot
id|flags
op_assign
l_int|1
suffix:semicolon
id|loopct
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|state-&gt;next
op_eq
id|state-&gt;limit
)paren
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Next, process the (first) extended partition, if present.&n;&t;&t; * (So far, there seems to be no reason to make&n;&t;&t; *  parse_extended()  recursive and allow a tree&n;&t;&t; *  of extended partitions.)&n;&t;&t; * It should be a link to the next logical partition.&n;&t;&t; */
id|p
op_sub_assign
l_int|4
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
l_int|4
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
r_if
c_cond
(paren
id|NR_SECTS
c_func
(paren
id|p
)paren
op_logical_and
id|is_extended_partition
c_func
(paren
id|p
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|4
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* nothing left to do */
id|this_sector
op_assign
id|first_sector
op_plus
id|START_SECT
c_func
(paren
id|p
)paren
op_star
id|sector_size
suffix:semicolon
id|this_size
op_assign
id|NR_SECTS
c_func
(paren
id|p
)paren
op_star
id|sector_size
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
)brace
id|done
suffix:colon
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
)brace
multiline_comment|/* james@bpgc.com: Solaris has a nasty indicator: 0x82 which also&n;   indicates linux swap.  Be careful before believing this is Solaris. */
r_static
r_void
DECL|function|parse_solaris_x86
id|parse_solaris_x86
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|u32
id|offset
comma
id|u32
id|size
comma
r_int
id|origin
)paren
(brace
macro_line|#ifdef CONFIG_SOLARIS_X86_PARTITION
id|Sector
id|sect
suffix:semicolon
r_struct
id|solaris_x86_vtoc
op_star
id|v
suffix:semicolon
r_int
id|i
suffix:semicolon
id|v
op_assign
(paren
r_struct
id|solaris_x86_vtoc
op_star
)paren
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|offset
op_plus
l_int|1
comma
op_amp
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|v
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|v-&gt;v_sanity
)paren
op_ne
id|SOLARIS_X86_VTOC_SANE
)paren
(brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %s%d: &lt;solaris:&quot;
comma
id|state-&gt;name
comma
id|origin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|v-&gt;v_version
)paren
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;  cannot handle version %d vtoc&gt;&bslash;n&quot;
comma
id|le32_to_cpu
c_func
(paren
id|v-&gt;v_version
)paren
)paren
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SOLARIS_X86_NUMSLICE
op_logical_and
id|state-&gt;next
OL
id|state-&gt;limit
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|solaris_x86_slice
op_star
id|s
op_assign
op_amp
id|v-&gt;v_slice
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_size
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; [s%d]&quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* solaris partitions are relative to current MS-DOS&n;&t;&t; * one; must add the offset of the current partition */
id|put_partition
c_func
(paren
id|state
comma
id|state-&gt;next
op_increment
comma
id|le32_to_cpu
c_func
(paren
id|s-&gt;s_start
)paren
op_plus
id|offset
comma
id|le32_to_cpu
c_func
(paren
id|s-&gt;s_size
)paren
)paren
suffix:semicolon
)brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#if defined(CONFIG_BSD_DISKLABEL) || defined(CONFIG_NEC98_PARTITION)
multiline_comment|/* &n; * Create devices for BSD partitions listed in a disklabel, under a&n; * dos-like partition. See parse_extended() for more information.&n; */
r_void
DECL|function|parse_bsd
id|parse_bsd
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|u32
id|offset
comma
id|u32
id|size
comma
r_int
id|origin
comma
r_char
op_star
id|flavour
comma
r_int
id|max_partitions
)paren
(brace
id|Sector
id|sect
suffix:semicolon
r_struct
id|bsd_disklabel
op_star
id|l
suffix:semicolon
r_struct
id|bsd_partition
op_star
id|p
suffix:semicolon
id|l
op_assign
(paren
r_struct
id|bsd_disklabel
op_star
)paren
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|offset
op_plus
l_int|1
comma
op_amp
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|l-&gt;d_magic
)paren
op_ne
id|BSD_DISKMAGIC
)paren
(brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %s%d: &lt;%s:&quot;
comma
id|state-&gt;name
comma
id|origin
comma
id|flavour
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|l-&gt;d_npartitions
)paren
OL
id|max_partitions
)paren
id|max_partitions
op_assign
id|le16_to_cpu
c_func
(paren
id|l-&gt;d_npartitions
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|l-&gt;d_partitions
suffix:semicolon
id|p
op_minus
id|l-&gt;d_partitions
OL
id|max_partitions
suffix:semicolon
id|p
op_increment
)paren
(brace
id|u32
id|bsd_start
comma
id|bsd_size
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;next
op_eq
id|state-&gt;limit
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;p_fstype
op_eq
id|BSD_FS_UNUSED
)paren
r_continue
suffix:semicolon
id|bsd_start
op_assign
id|le32_to_cpu
c_func
(paren
id|p-&gt;p_offset
)paren
suffix:semicolon
id|bsd_size
op_assign
id|le32_to_cpu
c_func
(paren
id|p-&gt;p_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
id|bsd_start
op_logical_and
id|size
op_eq
id|bsd_size
)paren
multiline_comment|/* full parent partition, we have it already */
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|bsd_start
op_logical_or
id|offset
op_plus
id|size
OL
id|bsd_start
op_plus
id|bsd_size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bad subpartition - ignored&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|put_partition
c_func
(paren
id|state
comma
id|state-&gt;next
op_increment
comma
id|bsd_start
comma
id|bsd_size
)paren
suffix:semicolon
)brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_static
r_void
DECL|function|parse_freebsd
id|parse_freebsd
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|u32
id|offset
comma
id|u32
id|size
comma
r_int
id|origin
)paren
(brace
macro_line|#ifdef CONFIG_BSD_DISKLABEL
id|parse_bsd
c_func
(paren
id|state
comma
id|bdev
comma
id|offset
comma
id|size
comma
id|origin
comma
l_string|&quot;bsd&quot;
comma
id|BSD_MAXPARTITIONS
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_void
DECL|function|parse_netbsd
id|parse_netbsd
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|u32
id|offset
comma
id|u32
id|size
comma
r_int
id|origin
)paren
(brace
macro_line|#ifdef CONFIG_BSD_DISKLABEL
id|parse_bsd
c_func
(paren
id|state
comma
id|bdev
comma
id|offset
comma
id|size
comma
id|origin
comma
l_string|&quot;netbsd&quot;
comma
id|BSD_MAXPARTITIONS
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_void
DECL|function|parse_openbsd
id|parse_openbsd
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|u32
id|offset
comma
id|u32
id|size
comma
r_int
id|origin
)paren
(brace
macro_line|#ifdef CONFIG_BSD_DISKLABEL
id|parse_bsd
c_func
(paren
id|state
comma
id|bdev
comma
id|offset
comma
id|size
comma
id|origin
comma
l_string|&quot;openbsd&quot;
comma
id|OPENBSD_MAXPARTITIONS
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Create devices for Unixware partitions listed in a disklabel, under a&n; * dos-like partition. See parse_extended() for more information.&n; */
r_static
r_void
DECL|function|parse_unixware
id|parse_unixware
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|u32
id|offset
comma
id|u32
id|size
comma
r_int
id|origin
)paren
(brace
macro_line|#ifdef CONFIG_UNIXWARE_DISKLABEL
id|Sector
id|sect
suffix:semicolon
r_struct
id|unixware_disklabel
op_star
id|l
suffix:semicolon
r_struct
id|unixware_slice
op_star
id|p
suffix:semicolon
id|l
op_assign
(paren
r_struct
id|unixware_disklabel
op_star
)paren
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|offset
op_plus
l_int|29
comma
op_amp
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|l-&gt;d_magic
)paren
op_ne
id|UNIXWARE_DISKMAGIC
op_logical_or
id|le32_to_cpu
c_func
(paren
id|l-&gt;vtoc.v_magic
)paren
op_ne
id|UNIXWARE_DISKMAGIC2
)paren
(brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %s%d: &lt;unixware:&quot;
comma
id|state-&gt;name
comma
id|origin
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|l-&gt;vtoc.v_slice
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* I omit the 0th slice as it is the same as whole disk. */
r_while
c_loop
(paren
id|p
op_minus
op_amp
id|l-&gt;vtoc.v_slice
(braket
l_int|0
)braket
OL
id|UNIXWARE_NUMSLICE
)paren
(brace
r_if
c_cond
(paren
id|state-&gt;next
op_eq
id|state-&gt;limit
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;s_label
op_ne
id|UNIXWARE_FS_UNUSED
)paren
id|put_partition
c_func
(paren
id|state
comma
id|state-&gt;next
op_increment
comma
id|START_SECT
c_func
(paren
id|p
)paren
comma
id|NR_SECTS
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Minix 2.0.0/2.0.2 subpartition support.&n; * Anand Krishnamurthy &lt;anandk@wiproge.med.ge.com&gt;&n; * Rajeev V. Pillai    &lt;rajeevvp@yahoo.com&gt;&n; */
r_static
r_void
DECL|function|parse_minix
id|parse_minix
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|u32
id|offset
comma
id|u32
id|size
comma
r_int
id|origin
)paren
(brace
macro_line|#ifdef CONFIG_MINIX_SUBPARTITION
id|Sector
id|sect
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_struct
id|partition
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
id|data
op_assign
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|offset
comma
op_amp
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
suffix:semicolon
id|p
op_assign
(paren
r_struct
id|partition
op_star
)paren
(paren
id|data
op_plus
l_int|0x1be
)paren
suffix:semicolon
multiline_comment|/* The first sector of a Minix partition can have either&n;&t; * a secondary MBR describing its subpartitions, or&n;&t; * the normal boot sector. */
r_if
c_cond
(paren
id|msdos_magic_present
(paren
id|data
op_plus
l_int|510
)paren
op_logical_and
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|MINIX_PARTITION
)paren
(brace
multiline_comment|/* subpartition table present */
id|printk
c_func
(paren
l_string|&quot; %s%d: &lt;minix:&quot;
comma
id|state-&gt;name
comma
id|origin
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
id|MINIX_NR_SUBPARTITIONS
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|state-&gt;next
op_eq
id|state-&gt;limit
)paren
r_break
suffix:semicolon
multiline_comment|/* add each partition in use */
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|MINIX_PARTITION
)paren
id|put_partition
c_func
(paren
id|state
comma
id|state-&gt;next
op_increment
comma
id|START_SECT
c_func
(paren
id|p
)paren
comma
id|NR_SECTS
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_MINIX_SUBPARTITION */
)brace
r_static
r_struct
(brace
DECL|member|id
r_int
r_char
id|id
suffix:semicolon
DECL|member|parse
r_void
(paren
op_star
id|parse
)paren
(paren
r_struct
id|parsed_partitions
op_star
comma
r_struct
id|block_device
op_star
comma
id|u32
comma
id|u32
comma
r_int
)paren
suffix:semicolon
DECL|variable|subtypes
)brace
id|subtypes
(braket
)braket
op_assign
(brace
(brace
id|FREEBSD_PARTITION
comma
id|parse_freebsd
)brace
comma
(brace
id|NETBSD_PARTITION
comma
id|parse_netbsd
)brace
comma
(brace
id|OPENBSD_PARTITION
comma
id|parse_openbsd
)brace
comma
(brace
id|MINIX_PARTITION
comma
id|parse_minix
)brace
comma
(brace
id|UNIXWARE_PARTITION
comma
id|parse_unixware
)brace
comma
(brace
id|SOLARIS_X86_PARTITION
comma
id|parse_solaris_x86
)brace
comma
(brace
l_int|0
comma
l_int|NULL
)brace
comma
)brace
suffix:semicolon
DECL|function|msdos_partition
r_int
id|msdos_partition
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_int
id|sector_size
op_assign
id|bdev_hardsect_size
c_func
(paren
id|bdev
)paren
op_div
l_int|512
suffix:semicolon
id|Sector
id|sect
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_struct
id|partition
op_star
id|p
suffix:semicolon
r_int
id|slot
suffix:semicolon
id|data
op_assign
id|read_dev_sector
c_func
(paren
id|bdev
comma
l_int|0
comma
op_amp
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|msdos_magic_present
c_func
(paren
id|data
op_plus
l_int|510
)paren
)paren
(brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now that the 55aa signature is present, this is probably&n;&t; * either the boot sector of a FAT filesystem or a DOS-type&n;&t; * partition table. Reject this in case the boot indicator&n;&t; * is not 0 or 0x80.&n;&t; */
id|p
op_assign
(paren
r_struct
id|partition
op_star
)paren
(paren
id|data
op_plus
l_int|0x1be
)paren
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|1
suffix:semicolon
id|slot
op_le
l_int|4
suffix:semicolon
id|slot
op_increment
comma
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;boot_ind
op_ne
l_int|0
op_logical_and
id|p-&gt;boot_ind
op_ne
l_int|0x80
)paren
(brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_EFI_PARTITION
id|p
op_assign
(paren
r_struct
id|partition
op_star
)paren
(paren
id|data
op_plus
l_int|0x1be
)paren
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|1
suffix:semicolon
id|slot
op_le
l_int|4
suffix:semicolon
id|slot
op_increment
comma
id|p
op_increment
)paren
(brace
multiline_comment|/* If this is an EFI GPT disk, msdos should ignore it. */
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|EFI_PMBR_OSTYPE_EFI_GPT
)paren
(brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
id|p
op_assign
(paren
r_struct
id|partition
op_star
)paren
(paren
id|data
op_plus
l_int|0x1be
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Look for partitions in two passes:&n;&t; * First find the primary and DOS-type extended partitions.&n;&t; * On the second pass look inside *BSD, Unixware and Solaris partitions.&n;&t; */
id|state-&gt;next
op_assign
id|DOS_EXTENDED_PARTITION
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|1
suffix:semicolon
id|slot
OL
id|DOS_EXTENDED_PARTITION
suffix:semicolon
id|slot
op_increment
comma
id|p
op_increment
)paren
(brace
id|u32
id|start
op_assign
id|START_SECT
c_func
(paren
id|p
)paren
op_star
id|sector_size
suffix:semicolon
id|u32
id|size
op_assign
id|NR_SECTS
c_func
(paren
id|p
)paren
op_star
id|sector_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|is_extended_partition
c_func
(paren
id|p
)paren
)paren
(brace
multiline_comment|/* prevent someone doing mkfs or mkswap on an&n;&t;&t;&t;   extended partition, but leave room for LILO */
id|put_partition
c_func
(paren
id|state
comma
id|slot
comma
id|start
comma
id|size
op_eq
l_int|1
ques
c_cond
l_int|1
suffix:colon
l_int|2
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &lt;&quot;
)paren
suffix:semicolon
id|parse_extended
c_func
(paren
id|state
comma
id|bdev
comma
id|start
comma
id|size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &gt;&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|put_partition
c_func
(paren
id|state
comma
id|slot
comma
id|start
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|LINUX_RAID_PARTITION
)paren
id|state-&gt;parts
(braket
id|slot
)braket
dot
id|flags
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|DM6_PARTITION
)paren
id|printk
c_func
(paren
l_string|&quot;[DM]&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|EZD_PARTITION
)paren
id|printk
c_func
(paren
l_string|&quot;[EZD]&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* second pass - output for each on a separate line */
id|p
op_assign
(paren
r_struct
id|partition
op_star
)paren
(paren
l_int|0x1be
op_plus
id|data
)paren
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|1
suffix:semicolon
id|slot
OL
id|DOS_EXTENDED_PARTITION
suffix:semicolon
id|slot
op_increment
comma
id|p
op_increment
)paren
(brace
r_int
r_char
id|id
op_assign
id|SYS_IND
c_func
(paren
id|p
)paren
suffix:semicolon
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|NR_SECTS
c_func
(paren
id|p
)paren
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|subtypes
(braket
id|n
)braket
dot
id|parse
op_logical_and
id|id
op_ne
id|subtypes
(braket
id|n
)braket
dot
id|id
suffix:semicolon
id|n
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|subtypes
(braket
id|n
)braket
dot
id|parse
)paren
r_continue
suffix:semicolon
id|subtypes
(braket
id|n
)braket
dot
id|parse
c_func
(paren
id|state
comma
id|bdev
comma
id|START_SECT
c_func
(paren
id|p
)paren
op_star
id|sector_size
comma
id|NR_SECTS
c_func
(paren
id|p
)paren
op_star
id|sector_size
comma
id|slot
)paren
suffix:semicolon
)brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
