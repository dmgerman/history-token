multiline_comment|/*&n; *  fs/partitions/osf.c&n; *&n; *  Code extracted from drivers/block/genhd.c&n; *&n; *  Copyright (C) 1991-1998  Linus Torvalds&n; *  Re-organised Feb 1998 Russell King&n; */
macro_line|#include &quot;check.h&quot;
macro_line|#include &quot;osf.h&quot;
DECL|function|osf_partition
r_int
id|osf_partition
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
id|i
suffix:semicolon
r_int
id|slot
op_assign
l_int|1
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
id|disklabel
(brace
id|u32
id|d_magic
suffix:semicolon
id|u16
id|d_type
comma
id|d_subtype
suffix:semicolon
id|u8
id|d_typename
(braket
l_int|16
)braket
suffix:semicolon
id|u8
id|d_packname
(braket
l_int|16
)braket
suffix:semicolon
id|u32
id|d_secsize
suffix:semicolon
id|u32
id|d_nsectors
suffix:semicolon
id|u32
id|d_ntracks
suffix:semicolon
id|u32
id|d_ncylinders
suffix:semicolon
id|u32
id|d_secpercyl
suffix:semicolon
id|u32
id|d_secprtunit
suffix:semicolon
id|u16
id|d_sparespertrack
suffix:semicolon
id|u16
id|d_sparespercyl
suffix:semicolon
id|u32
id|d_acylinders
suffix:semicolon
id|u16
id|d_rpm
comma
id|d_interleave
comma
id|d_trackskew
comma
id|d_cylskew
suffix:semicolon
id|u32
id|d_headswitch
comma
id|d_trkseek
comma
id|d_flags
suffix:semicolon
id|u32
id|d_drivedata
(braket
l_int|5
)braket
suffix:semicolon
id|u32
id|d_spare
(braket
l_int|5
)braket
suffix:semicolon
id|u32
id|d_magic2
suffix:semicolon
id|u16
id|d_checksum
suffix:semicolon
id|u16
id|d_npartitions
suffix:semicolon
id|u32
id|d_bbsize
comma
id|d_sbsize
suffix:semicolon
r_struct
id|d_partition
(brace
id|u32
id|p_size
suffix:semicolon
id|u32
id|p_offset
suffix:semicolon
id|u32
id|p_fsize
suffix:semicolon
id|u8
id|p_fstype
suffix:semicolon
id|u8
id|p_frag
suffix:semicolon
id|u16
id|p_cpg
suffix:semicolon
)brace
id|d_partitions
(braket
l_int|8
)braket
suffix:semicolon
)brace
op_star
id|label
suffix:semicolon
r_struct
id|d_partition
op_star
id|partition
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
id|label
op_assign
(paren
r_struct
id|disklabel
op_star
)paren
(paren
id|data
op_plus
l_int|64
)paren
suffix:semicolon
id|partition
op_assign
id|label-&gt;d_partitions
suffix:semicolon
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|label-&gt;d_magic
)paren
op_ne
id|DISKLABELMAGIC
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
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|label-&gt;d_magic2
)paren
op_ne
id|DISKLABELMAGIC
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|le16_to_cpu
c_func
(paren
id|label-&gt;d_npartitions
)paren
suffix:semicolon
id|i
op_increment
comma
id|partition
op_increment
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
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|partition-&gt;p_size
)paren
)paren
id|put_partition
c_func
(paren
id|state
comma
id|slot
comma
id|le32_to_cpu
c_func
(paren
id|partition-&gt;p_offset
)paren
comma
id|le32_to_cpu
c_func
(paren
id|partition-&gt;p_size
)paren
)paren
suffix:semicolon
id|slot
op_increment
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
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
