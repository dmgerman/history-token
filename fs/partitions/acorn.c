multiline_comment|/*&n; *  linux/fs/partitions/acorn.c&n; *&n; *  Copyright (c) 1996-2000 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Scan ADFS partitions on hard disk drives.  Unfortunately, there&n; *  isn&squot;t a standard for partitioning drives on Acorn machines, so&n; *  every single manufacturer of SCSI and IDE cards created their own&n; *  method.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/adfs_fs.h&gt;
macro_line|#include &quot;check.h&quot;
macro_line|#include &quot;acorn.h&quot;
multiline_comment|/*&n; * Partition types. (Oh for reusability)&n; */
DECL|macro|PARTITION_RISCIX_MFM
mdefine_line|#define PARTITION_RISCIX_MFM&t;1
DECL|macro|PARTITION_RISCIX_SCSI
mdefine_line|#define PARTITION_RISCIX_SCSI&t;2
DECL|macro|PARTITION_LINUX
mdefine_line|#define PARTITION_LINUX&t;&t;9
r_static
r_struct
id|adfs_discrecord
op_star
DECL|function|adfs_partition
id|adfs_partition
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_char
op_star
id|name
comma
r_char
op_star
id|data
comma
r_int
r_int
id|first_sector
comma
r_int
id|slot
)paren
(brace
r_struct
id|adfs_discrecord
op_star
id|dr
suffix:semicolon
r_int
r_int
id|nr_sects
suffix:semicolon
r_if
c_cond
(paren
id|adfs_checkbblk
c_func
(paren
id|data
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|dr
op_assign
(paren
r_struct
id|adfs_discrecord
op_star
)paren
(paren
id|data
op_plus
l_int|0x1c0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dr-&gt;disc_size
op_eq
l_int|0
op_logical_and
id|dr-&gt;disc_size_high
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|nr_sects
op_assign
(paren
id|le32_to_cpu
c_func
(paren
id|dr-&gt;disc_size_high
)paren
op_lshift
l_int|23
)paren
op_or
(paren
id|le32_to_cpu
c_func
(paren
id|dr-&gt;disc_size
)paren
op_rshift
l_int|9
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
id|printk
c_func
(paren
l_string|&quot; [%s]&quot;
comma
id|name
)paren
suffix:semicolon
id|put_partition
c_func
(paren
id|state
comma
id|slot
comma
id|first_sector
comma
id|nr_sects
)paren
suffix:semicolon
r_return
id|dr
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACORN_PARTITION_RISCIX
DECL|struct|riscix_part
r_struct
id|riscix_part
(brace
DECL|member|start
id|__u32
id|start
suffix:semicolon
DECL|member|length
id|__u32
id|length
suffix:semicolon
DECL|member|one
id|__u32
id|one
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|riscix_record
r_struct
id|riscix_record
(brace
DECL|member|magic
id|__u32
id|magic
suffix:semicolon
DECL|macro|RISCIX_MAGIC
mdefine_line|#define RISCIX_MAGIC&t;cpu_to_le32(0x4a657320)
DECL|member|date
id|__u32
id|date
suffix:semicolon
DECL|member|part
r_struct
id|riscix_part
id|part
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
DECL|function|riscix_partition
id|riscix_partition
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
r_int
r_int
id|first_sect
comma
r_int
id|slot
comma
r_int
r_int
id|nr_sects
)paren
(brace
id|Sector
id|sect
suffix:semicolon
r_struct
id|riscix_record
op_star
id|rr
suffix:semicolon
id|rr
op_assign
(paren
r_struct
id|riscix_record
op_star
)paren
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|first_sect
comma
op_amp
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rr
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; [RISCiX]&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rr-&gt;magic
op_eq
id|RISCIX_MAGIC
)paren
(brace
r_int
r_int
id|size
op_assign
id|nr_sects
OG
l_int|2
ques
c_cond
l_int|2
suffix:colon
id|nr_sects
suffix:semicolon
r_int
id|part
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &lt;&quot;
)paren
suffix:semicolon
id|put_partition
c_func
(paren
id|state
comma
id|slot
op_increment
comma
id|first_sect
comma
id|size
)paren
suffix:semicolon
r_for
c_loop
(paren
id|part
op_assign
l_int|0
suffix:semicolon
id|part
OL
l_int|8
suffix:semicolon
id|part
op_increment
)paren
(brace
r_if
c_cond
(paren
id|rr-&gt;part
(braket
id|part
)braket
dot
id|one
op_logical_and
id|memcmp
c_func
(paren
id|rr-&gt;part
(braket
id|part
)braket
dot
id|name
comma
l_string|&quot;All&bslash;0&quot;
comma
l_int|4
)paren
)paren
(brace
id|put_partition
c_func
(paren
id|state
comma
id|slot
op_increment
comma
id|le32_to_cpu
c_func
(paren
id|rr-&gt;part
(braket
id|part
)braket
dot
id|start
)paren
comma
id|le32_to_cpu
c_func
(paren
id|rr-&gt;part
(braket
id|part
)braket
dot
id|length
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(%s)&quot;
comma
id|rr-&gt;part
(braket
id|part
)braket
dot
id|name
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|put_partition
c_func
(paren
id|state
comma
id|slot
op_increment
comma
id|first_sect
comma
id|nr_sects
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
id|slot
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|LINUX_NATIVE_MAGIC
mdefine_line|#define LINUX_NATIVE_MAGIC 0xdeafa1de
DECL|macro|LINUX_SWAP_MAGIC
mdefine_line|#define LINUX_SWAP_MAGIC   0xdeafab1e
DECL|struct|linux_part
r_struct
id|linux_part
(brace
DECL|member|magic
id|__u32
id|magic
suffix:semicolon
DECL|member|start_sect
id|__u32
id|start_sect
suffix:semicolon
DECL|member|nr_sects
id|__u32
id|nr_sects
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
DECL|function|linux_partition
id|linux_partition
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
r_int
r_int
id|first_sect
comma
r_int
id|slot
comma
r_int
r_int
id|nr_sects
)paren
(brace
id|Sector
id|sect
suffix:semicolon
r_struct
id|linux_part
op_star
id|linuxp
suffix:semicolon
r_int
r_int
id|size
op_assign
id|nr_sects
OG
l_int|2
ques
c_cond
l_int|2
suffix:colon
id|nr_sects
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; [Linux]&quot;
)paren
suffix:semicolon
id|put_partition
c_func
(paren
id|state
comma
id|slot
op_increment
comma
id|first_sect
comma
id|size
)paren
suffix:semicolon
id|linuxp
op_assign
(paren
r_struct
id|linux_part
op_star
)paren
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|first_sect
comma
op_amp
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|linuxp
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &lt;&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|linuxp-&gt;magic
op_eq
id|cpu_to_le32
c_func
(paren
id|LINUX_NATIVE_MAGIC
)paren
op_logical_or
id|linuxp-&gt;magic
op_eq
id|cpu_to_le32
c_func
(paren
id|LINUX_SWAP_MAGIC
)paren
)paren
(brace
r_if
c_cond
(paren
id|slot
op_eq
id|state-&gt;limit
)paren
r_break
suffix:semicolon
id|put_partition
c_func
(paren
id|state
comma
id|slot
op_increment
comma
id|first_sect
op_plus
id|le32_to_cpu
c_func
(paren
id|linuxp-&gt;start_sect
)paren
comma
id|le32_to_cpu
c_func
(paren
id|linuxp-&gt;nr_sects
)paren
)paren
suffix:semicolon
id|linuxp
op_increment
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; &gt;&quot;
)paren
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
id|slot
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACORN_PARTITION_CUMANA
r_int
DECL|function|adfspart_check_CUMANA
id|adfspart_check_CUMANA
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
r_int
id|first_sector
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|start_blk
op_assign
l_int|0
suffix:semicolon
id|Sector
id|sect
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_char
op_star
id|name
op_assign
l_string|&quot;CUMANA/ADFS&quot;
suffix:semicolon
r_int
id|first
op_assign
l_int|1
suffix:semicolon
r_int
id|slot
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Try Cumana style partitions - sector 6 contains ADFS boot block&n;&t; * with pointer to next &squot;drive&squot;.&n;&t; *&n;&t; * There are unknowns in this code - is the &squot;cylinder number&squot; of the&n;&t; * next partition relative to the start of this one - I&squot;m assuming&n;&t; * it is.&n;&t; *&n;&t; * Also, which ID did Cumana use?&n;&t; *&n;&t; * This is totally unfinished, and will require more work to get it&n;&t; * going. Hence it is totally untested.&n;&t; */
r_do
(brace
r_struct
id|adfs_discrecord
op_star
id|dr
suffix:semicolon
r_int
r_int
id|nr_sects
suffix:semicolon
id|data
op_assign
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|start_blk
op_star
l_int|2
op_plus
l_int|6
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
id|slot
op_eq
id|state-&gt;limit
)paren
r_break
suffix:semicolon
id|dr
op_assign
id|adfs_partition
c_func
(paren
id|state
comma
id|name
comma
id|data
comma
id|first_sector
comma
id|slot
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dr
)paren
r_break
suffix:semicolon
id|name
op_assign
l_int|NULL
suffix:semicolon
id|nr_sects
op_assign
(paren
id|data
(braket
l_int|0x1fd
)braket
op_plus
(paren
id|data
(braket
l_int|0x1fe
)braket
op_lshift
l_int|8
)paren
)paren
op_star
(paren
id|dr-&gt;heads
op_plus
(paren
id|dr-&gt;lowsector
op_amp
l_int|0x40
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
)paren
op_star
id|dr-&gt;secspertrack
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_sects
)paren
r_break
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
id|first_sector
op_add_assign
id|nr_sects
suffix:semicolon
id|start_blk
op_add_assign
id|nr_sects
op_rshift
(paren
id|BLOCK_SIZE_BITS
op_minus
l_int|9
)paren
suffix:semicolon
id|nr_sects
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* hmm - should be partition size */
r_switch
c_cond
(paren
id|data
(braket
l_int|0x1fc
)braket
op_amp
l_int|15
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* No partition / ADFS? */
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_ACORN_PARTITION_RISCIX
r_case
id|PARTITION_RISCIX_SCSI
suffix:colon
multiline_comment|/* RISCiX - we don&squot;t know how to find the next one. */
id|slot
op_assign
id|riscix_partition
c_func
(paren
id|state
comma
id|bdev
comma
id|first_sector
comma
id|slot
comma
id|nr_sects
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|PARTITION_LINUX
suffix:colon
id|slot
op_assign
id|linux_partition
c_func
(paren
id|state
comma
id|bdev
comma
id|first_sector
comma
id|slot
comma
id|nr_sects
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
id|first
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_ADFS
multiline_comment|/*&n; * Purpose: allocate ADFS partitions.&n; *&n; * Params : hd&t;&t;- pointer to gendisk structure to store partition info.&n; *&t;    dev&t;&t;- device number to access.&n; *&n; * Returns: -1 on error, 0 for no ADFS boot sector, 1 for ok.&n; *&n; * Alloc  : hda  = whole drive&n; *&t;    hda1 = ADFS partition on first drive.&n; *&t;    hda2 = non-ADFS partition.&n; */
r_int
DECL|function|adfspart_check_ADFS
id|adfspart_check_ADFS
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
r_int
id|start_sect
comma
id|nr_sects
comma
id|sectscyl
comma
id|heads
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
id|adfs_discrecord
op_star
id|dr
suffix:semicolon
r_int
r_char
id|id
suffix:semicolon
r_int
id|slot
op_assign
l_int|1
suffix:semicolon
id|data
op_assign
id|read_dev_sector
c_func
(paren
id|bdev
comma
l_int|6
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
id|dr
op_assign
id|adfs_partition
c_func
(paren
id|state
comma
l_string|&quot;ADFS&quot;
comma
id|data
comma
l_int|0
comma
id|slot
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dr
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
id|heads
op_assign
id|dr-&gt;heads
op_plus
(paren
(paren
id|dr-&gt;lowsector
op_rshift
l_int|6
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|sectscyl
op_assign
id|dr-&gt;secspertrack
op_star
id|heads
suffix:semicolon
id|start_sect
op_assign
(paren
(paren
id|data
(braket
l_int|0x1fe
)braket
op_lshift
l_int|8
)paren
op_plus
id|data
(braket
l_int|0x1fd
)braket
)paren
op_star
id|sectscyl
suffix:semicolon
id|id
op_assign
id|data
(braket
l_int|0x1fc
)braket
op_amp
l_int|15
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_MFM
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|bdev-&gt;bd_dev
)paren
op_eq
id|MFM_ACORN_MAJOR
)paren
(brace
r_extern
r_void
id|xd_set_geometry
c_func
(paren
r_struct
id|block_device
op_star
comma
r_int
r_char
comma
r_int
r_char
comma
r_int
r_int
)paren
suffix:semicolon
id|xd_set_geometry
c_func
(paren
id|bdev
comma
id|dr-&gt;secspertrack
comma
id|heads
comma
l_int|1
)paren
suffix:semicolon
id|invalidate_bdev
c_func
(paren
id|bdev
comma
l_int|1
)paren
suffix:semicolon
id|truncate_inode_pages
c_func
(paren
id|bdev-&gt;bd_inode-&gt;i_mapping
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Work out start of non-adfs partition.&n;&t; */
id|nr_sects
op_assign
(paren
id|bdev-&gt;bd_inode-&gt;i_size
op_rshift
l_int|9
)paren
op_minus
id|start_sect
suffix:semicolon
r_if
c_cond
(paren
id|start_sect
)paren
(brace
r_switch
c_cond
(paren
id|id
)paren
(brace
macro_line|#ifdef CONFIG_ACORN_PARTITION_RISCIX
r_case
id|PARTITION_RISCIX_SCSI
suffix:colon
r_case
id|PARTITION_RISCIX_MFM
suffix:colon
id|slot
op_assign
id|riscix_partition
c_func
(paren
id|state
comma
id|bdev
comma
id|start_sect
comma
id|slot
comma
id|nr_sects
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|PARTITION_LINUX
suffix:colon
id|slot
op_assign
id|linux_partition
c_func
(paren
id|state
comma
id|bdev
comma
id|start_sect
comma
id|slot
comma
id|nr_sects
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_ICS
DECL|struct|ics_part
r_struct
id|ics_part
(brace
DECL|member|start
id|__u32
id|start
suffix:semicolon
DECL|member|size
id|__s32
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|function|adfspart_check_ICSLinux
r_static
r_int
id|adfspart_check_ICSLinux
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
r_int
id|block
)paren
(brace
id|Sector
id|sect
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|block
comma
op_amp
id|sect
)paren
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|data
comma
l_string|&quot;LinuxPart&quot;
comma
l_int|9
)paren
op_eq
l_int|0
)paren
id|result
op_assign
l_int|1
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Check for a valid ICS partition using the checksum.&n; */
DECL|function|valid_ics_sector
r_static
r_inline
r_int
id|valid_ics_sector
c_func
(paren
r_const
r_int
r_char
op_star
id|data
)paren
(brace
r_int
r_int
id|sum
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|sum
op_assign
l_int|0x50617274
suffix:semicolon
id|i
OL
l_int|508
suffix:semicolon
id|i
op_increment
)paren
id|sum
op_add_assign
id|data
(braket
id|i
)braket
suffix:semicolon
id|sum
op_sub_assign
id|le32_to_cpu
c_func
(paren
op_star
(paren
id|__u32
op_star
)paren
(paren
op_amp
id|data
(braket
l_int|508
)braket
)paren
)paren
suffix:semicolon
r_return
id|sum
op_eq
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Purpose: allocate ICS partitions.&n; * Params : hd&t;&t;- pointer to gendisk structure to store partition info.&n; *&t;    dev&t;&t;- device number to access.&n; * Returns: -1 on error, 0 for no ICS table, 1 for partitions ok.&n; * Alloc  : hda  = whole drive&n; *&t;    hda1 = ADFS partition 0 on first drive.&n; *&t;    hda2 = ADFS partition 1 on first drive.&n; *&t;&t;..etc..&n; */
r_int
DECL|function|adfspart_check_ICS
id|adfspart_check_ICS
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
r_const
r_int
r_char
op_star
id|data
suffix:semicolon
r_const
r_struct
id|ics_part
op_star
id|p
suffix:semicolon
r_int
id|slot
suffix:semicolon
id|Sector
id|sect
suffix:semicolon
multiline_comment|/*&n;&t; * Try ICS style partitions - sector 0 contains partition info.&n;&t; */
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
id|valid_ics_sector
c_func
(paren
id|data
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
id|printk
c_func
(paren
l_string|&quot; [ICS]&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|1
comma
id|p
op_assign
(paren
r_const
r_struct
id|ics_part
op_star
)paren
id|data
suffix:semicolon
id|p-&gt;size
suffix:semicolon
id|p
op_increment
)paren
(brace
id|u32
id|start
op_assign
id|le32_to_cpu
c_func
(paren
id|p-&gt;start
)paren
suffix:semicolon
id|s32
id|size
op_assign
id|le32_to_cpu
c_func
(paren
id|p-&gt;size
)paren
suffix:semicolon
multiline_comment|/* yes, it&squot;s signed. */
r_if
c_cond
(paren
id|slot
op_eq
id|state-&gt;limit
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Negative sizes tell the RISC OS ICS driver to ignore&n;&t;&t; * this partition - in effect it says that this does not&n;&t;&t; * contain an ADFS filesystem.&n;&t;&t; */
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
(brace
id|size
op_assign
op_minus
id|size
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Our own extension - We use the first sector&n;&t;&t;&t; * of the partition to identify what type this&n;&t;&t;&t; * partition is.  We must not make this visible&n;&t;&t;&t; * to the filesystem.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|size
OG
l_int|1
op_logical_and
id|adfspart_check_ICSLinux
c_func
(paren
id|bdev
comma
id|start
)paren
)paren
(brace
id|start
op_add_assign
l_int|1
suffix:semicolon
id|size
op_sub_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|size
)paren
id|put_partition
c_func
(paren
id|state
comma
id|slot
op_increment
comma
id|start
comma
id|size
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
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_POWERTEC
DECL|struct|ptec_part
r_struct
id|ptec_part
(brace
DECL|member|unused1
id|__u32
id|unused1
suffix:semicolon
DECL|member|unused2
id|__u32
id|unused2
suffix:semicolon
DECL|member|start
id|__u32
id|start
suffix:semicolon
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|unused5
id|__u32
id|unused5
suffix:semicolon
DECL|member|type
r_char
id|type
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|valid_ptec_sector
r_static
r_inline
r_int
id|valid_ptec_sector
c_func
(paren
r_const
r_int
r_char
op_star
id|data
)paren
(brace
r_int
r_char
id|checksum
op_assign
l_int|0x2a
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * If it looks like a PC/BIOS partition, then it&n;&t; * probably isn&squot;t PowerTec.&n;&t; */
r_if
c_cond
(paren
id|data
(braket
l_int|510
)braket
op_eq
l_int|0x55
op_logical_and
id|data
(braket
l_int|511
)braket
op_eq
l_int|0xaa
)paren
r_return
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
l_int|511
suffix:semicolon
id|i
op_increment
)paren
id|checksum
op_add_assign
id|data
(braket
id|i
)braket
suffix:semicolon
r_return
id|checksum
op_eq
id|data
(braket
l_int|511
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Purpose: allocate ICS partitions.&n; * Params : hd&t;&t;- pointer to gendisk structure to store partition info.&n; *&t;    dev&t;&t;- device number to access.&n; * Returns: -1 on error, 0 for no ICS table, 1 for partitions ok.&n; * Alloc  : hda  = whole drive&n; *&t;    hda1 = ADFS partition 0 on first drive.&n; *&t;    hda2 = ADFS partition 1 on first drive.&n; *&t;&t;..etc..&n; */
r_int
DECL|function|adfspart_check_POWERTEC
id|adfspart_check_POWERTEC
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
id|Sector
id|sect
suffix:semicolon
r_const
r_int
r_char
op_star
id|data
suffix:semicolon
r_const
r_struct
id|ptec_part
op_star
id|p
suffix:semicolon
r_int
id|slot
op_assign
l_int|1
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
id|valid_ptec_sector
c_func
(paren
id|data
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
id|printk
c_func
(paren
l_string|&quot; [POWERTEC]&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|p
op_assign
(paren
r_const
r_struct
id|ptec_part
op_star
)paren
id|data
suffix:semicolon
id|i
OL
l_int|12
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
id|u32
id|start
op_assign
id|le32_to_cpu
c_func
(paren
id|p-&gt;start
)paren
suffix:semicolon
id|u32
id|size
op_assign
id|le32_to_cpu
c_func
(paren
id|p-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
id|put_partition
c_func
(paren
id|state
comma
id|slot
op_increment
comma
id|start
comma
id|size
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
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_EESOX
DECL|struct|eesox_part
r_struct
id|eesox_part
(brace
DECL|member|magic
r_char
id|magic
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|start
id|u32
id|start
suffix:semicolon
DECL|member|unused6
id|u32
id|unused6
suffix:semicolon
DECL|member|unused7
id|u32
id|unused7
suffix:semicolon
DECL|member|unused8
id|u32
id|unused8
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Guess who created this format?&n; */
DECL|variable|eesox_name
r_static
r_const
r_char
id|eesox_name
(braket
)braket
op_assign
(brace
l_char|&squot;N&squot;
comma
l_char|&squot;e&squot;
comma
l_char|&squot;i&squot;
comma
l_char|&squot;l&squot;
comma
l_char|&squot; &squot;
comma
l_char|&squot;C&squot;
comma
l_char|&squot;r&squot;
comma
l_char|&squot;i&squot;
comma
l_char|&squot;t&squot;
comma
l_char|&squot;c&squot;
comma
l_char|&squot;h&squot;
comma
l_char|&squot;e&squot;
comma
l_char|&squot;l&squot;
comma
l_char|&squot;l&squot;
comma
l_char|&squot; &squot;
comma
l_char|&squot; &squot;
)brace
suffix:semicolon
multiline_comment|/*&n; * EESOX SCSI partition format.&n; *&n; * This is a goddamned awful partition format.  We don&squot;t seem to store&n; * the size of the partition in this table, only the start addresses.&n; *&n; * There are two possibilities where the size comes from:&n; *  1. The individual ADFS boot block entries that are placed on the disk.&n; *  2. The start address of the next entry.&n; */
r_int
DECL|function|adfspart_check_EESOX
id|adfspart_check_EESOX
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
id|Sector
id|sect
suffix:semicolon
r_const
r_int
r_char
op_star
id|data
suffix:semicolon
r_int
r_char
id|buffer
(braket
l_int|256
)braket
suffix:semicolon
r_struct
id|eesox_part
op_star
id|p
suffix:semicolon
id|sector_t
id|start
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|slot
op_assign
l_int|1
suffix:semicolon
id|data
op_assign
id|read_dev_sector
c_func
(paren
id|bdev
comma
l_int|7
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
multiline_comment|/*&n;&t; * &quot;Decrypt&quot; the partition table.  God knows why...&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
id|buffer
(braket
id|i
)braket
op_assign
id|data
(braket
id|i
)braket
op_xor
id|eesox_name
(braket
id|i
op_amp
l_int|15
)braket
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|p
op_assign
(paren
r_struct
id|eesox_part
op_star
)paren
id|buffer
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
id|sector_t
id|next
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|p-&gt;magic
comma
l_string|&quot;Eesox&quot;
comma
l_int|6
)paren
)paren
r_break
suffix:semicolon
id|next
op_assign
id|le32_to_cpu
c_func
(paren
id|p-&gt;start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|put_partition
c_func
(paren
id|state
comma
id|slot
op_increment
comma
id|start
comma
id|next
op_minus
id|start
)paren
suffix:semicolon
id|start
op_assign
id|next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ne
l_int|0
)paren
(brace
id|sector_t
id|size
suffix:semicolon
id|size
op_assign
id|get_capacity
c_func
(paren
id|bdev-&gt;bd_disk
)paren
suffix:semicolon
id|put_partition
c_func
(paren
id|state
comma
id|slot
op_increment
comma
id|start
comma
id|size
op_minus
id|start
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|i
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
