multiline_comment|/**&n; * ldm - Part of the Linux-NTFS project.&n; *&n; * Copyright (C) 2001,2002 Richard Russon &lt;ldm@flatcap.org&gt;&n; * Copyright (C) 2001      Anton Altaparmakov &lt;aia21@cantab.net&gt;&n; * Copyright (C) 2001,2002 Jakob Kemi &lt;jakob.kemi@telia.com&gt;&n; *&n; * Documentation is available at http://linux-ntfs.sf.net/ldm&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS source&n; * in the file COPYING); if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _FS_PT_LDM_H_
DECL|macro|_FS_PT_LDM_H_
mdefine_line|#define _FS_PT_LDM_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
r_struct
id|parsed_partitions
suffix:semicolon
multiline_comment|/* Magic numbers in CPU format. */
DECL|macro|MAGIC_VMDB
mdefine_line|#define MAGIC_VMDB&t;0x564D4442&t;&t;/* VMDB */
DECL|macro|MAGIC_VBLK
mdefine_line|#define MAGIC_VBLK&t;0x56424C4B&t;&t;/* VBLK */
DECL|macro|MAGIC_PRIVHEAD
mdefine_line|#define MAGIC_PRIVHEAD&t;0x5052495648454144ULL&t;/* PRIVHEAD */
DECL|macro|MAGIC_TOCBLOCK
mdefine_line|#define MAGIC_TOCBLOCK&t;0x544F43424C4F434BULL&t;/* TOCBLOCK */
multiline_comment|/* The defined vblk types. */
DECL|macro|VBLK_VOL5
mdefine_line|#define VBLK_VOL5&t;&t;0x51&t;&t;/* Volume,     version 5 */
DECL|macro|VBLK_CMP3
mdefine_line|#define VBLK_CMP3&t;&t;0x32&t;&t;/* Component,  version 3 */
DECL|macro|VBLK_PRT3
mdefine_line|#define VBLK_PRT3&t;&t;0x33&t;&t;/* Partition,  version 3 */
DECL|macro|VBLK_DSK3
mdefine_line|#define VBLK_DSK3&t;&t;0x34&t;&t;/* Disk,       version 3 */
DECL|macro|VBLK_DSK4
mdefine_line|#define VBLK_DSK4&t;&t;0x44&t;&t;/* Disk,       version 4 */
DECL|macro|VBLK_DGR3
mdefine_line|#define VBLK_DGR3&t;&t;0x35&t;&t;/* Disk Group, version 3 */
DECL|macro|VBLK_DGR4
mdefine_line|#define VBLK_DGR4&t;&t;0x45&t;&t;/* Disk Group, version 4 */
multiline_comment|/* vblk flags indicating extra information will be present */
DECL|macro|VBLK_FLAG_COMP_STRIPE
mdefine_line|#define&t;VBLK_FLAG_COMP_STRIPE&t;0x10
DECL|macro|VBLK_FLAG_PART_INDEX
mdefine_line|#define&t;VBLK_FLAG_PART_INDEX&t;0x08
DECL|macro|VBLK_FLAG_DGR3_IDS
mdefine_line|#define&t;VBLK_FLAG_DGR3_IDS&t;0x08
DECL|macro|VBLK_FLAG_DGR4_IDS
mdefine_line|#define&t;VBLK_FLAG_DGR4_IDS&t;0x08
DECL|macro|VBLK_FLAG_VOLU_ID1
mdefine_line|#define&t;VBLK_FLAG_VOLU_ID1&t;0x08
DECL|macro|VBLK_FLAG_VOLU_ID2
mdefine_line|#define&t;VBLK_FLAG_VOLU_ID2&t;0x20
DECL|macro|VBLK_FLAG_VOLU_SIZE
mdefine_line|#define&t;VBLK_FLAG_VOLU_SIZE&t;0x80
DECL|macro|VBLK_FLAG_VOLU_DRIVE
mdefine_line|#define&t;VBLK_FLAG_VOLU_DRIVE&t;0x02
multiline_comment|/* size of a vblk&squot;s static parts */
DECL|macro|VBLK_SIZE_HEAD
mdefine_line|#define VBLK_SIZE_HEAD&t;&t;16
DECL|macro|VBLK_SIZE_CMP3
mdefine_line|#define VBLK_SIZE_CMP3&t;&t;22&t;&t;/* Name and version */
DECL|macro|VBLK_SIZE_DGR3
mdefine_line|#define VBLK_SIZE_DGR3&t;&t;12
DECL|macro|VBLK_SIZE_DGR4
mdefine_line|#define VBLK_SIZE_DGR4&t;&t;44
DECL|macro|VBLK_SIZE_DSK3
mdefine_line|#define VBLK_SIZE_DSK3&t;&t;12
DECL|macro|VBLK_SIZE_DSK4
mdefine_line|#define VBLK_SIZE_DSK4&t;&t;45
DECL|macro|VBLK_SIZE_PRT3
mdefine_line|#define VBLK_SIZE_PRT3&t;&t;28
DECL|macro|VBLK_SIZE_VOL5
mdefine_line|#define VBLK_SIZE_VOL5&t;&t;59
multiline_comment|/* component types */
DECL|macro|COMP_STRIPE
mdefine_line|#define COMP_STRIPE&t;&t;0x01&t;&t;/* Stripe-set */
DECL|macro|COMP_BASIC
mdefine_line|#define COMP_BASIC&t;&t;0x02&t;&t;/* Basic disk */
DECL|macro|COMP_RAID
mdefine_line|#define COMP_RAID&t;&t;0x03&t;&t;/* Raid-set */
multiline_comment|/* Other constants. */
DECL|macro|LDM_DB_SIZE
mdefine_line|#define LDM_DB_SIZE&t;&t;2048&t;&t;/* Size in sectors (= 1MiB). */
DECL|macro|OFF_PRIV1
mdefine_line|#define OFF_PRIV1&t;&t;6&t;&t;/* Offset of the first privhead&n;&t;&t;&t;&t;&t;&t;   relative to the start of the&n;&t;&t;&t;&t;&t;&t;   device in sectors */
multiline_comment|/* Offsets to structures within the LDM Database in sectors. */
DECL|macro|OFF_PRIV2
mdefine_line|#define OFF_PRIV2&t;&t;1856&t;&t;/* Backup private headers. */
DECL|macro|OFF_PRIV3
mdefine_line|#define OFF_PRIV3&t;&t;2047
DECL|macro|OFF_TOCB1
mdefine_line|#define OFF_TOCB1&t;&t;1&t;&t;/* Tables of contents. */
DECL|macro|OFF_TOCB2
mdefine_line|#define OFF_TOCB2&t;&t;2
DECL|macro|OFF_TOCB3
mdefine_line|#define OFF_TOCB3&t;&t;2045
DECL|macro|OFF_TOCB4
mdefine_line|#define OFF_TOCB4&t;&t;2046
DECL|macro|OFF_VMDB
mdefine_line|#define OFF_VMDB&t;&t;17&t;&t;/* List of partitions. */
DECL|macro|WIN2K_DYNAMIC_PARTITION
mdefine_line|#define WIN2K_DYNAMIC_PARTITION&t;0x42&t;&t;/* Formerly SFS (Landis). */
DECL|macro|TOC_BITMAP1
mdefine_line|#define TOC_BITMAP1&t;&t;&quot;config&quot;&t;/* Names of the two defined */
DECL|macro|TOC_BITMAP2
mdefine_line|#define TOC_BITMAP2&t;&t;&quot;log&quot;&t;&t;/* bitmaps in the TOCBLOCK. */
multiline_comment|/* Most numbers we deal with are big-endian and won&squot;t be aligned. */
DECL|macro|BE16
mdefine_line|#define BE16(x)&t;&t;&t;((u16)be16_to_cpu(get_unaligned((u16*)(x))))
DECL|macro|BE32
mdefine_line|#define BE32(x)&t;&t;&t;((u32)be32_to_cpu(get_unaligned((u32*)(x))))
DECL|macro|BE64
mdefine_line|#define BE64(x)&t;&t;&t;((u64)be64_to_cpu(get_unaligned((u64*)(x))))
multiline_comment|/* Borrowed from msdos.c */
DECL|macro|SYS_IND
mdefine_line|#define SYS_IND(p)&t;&t;(get_unaligned(&amp;(p)-&gt;sys_ind))
DECL|struct|frag
r_struct
id|frag
(brace
multiline_comment|/* VBLK Fragment handling */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|group
id|u32
id|group
suffix:semicolon
DECL|member|num
id|u8
id|num
suffix:semicolon
multiline_comment|/* Total number of records */
DECL|member|rec
id|u8
id|rec
suffix:semicolon
multiline_comment|/* This is record number n */
DECL|member|map
id|u8
id|map
suffix:semicolon
multiline_comment|/* Which portions are in use */
DECL|member|data
id|u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* In memory LDM database structures. */
DECL|macro|GUID_SIZE
mdefine_line|#define GUID_SIZE&t;&t;16
DECL|struct|privhead
r_struct
id|privhead
(brace
multiline_comment|/* Offsets and sizes are in sectors. */
DECL|member|ver_major
id|u16
id|ver_major
suffix:semicolon
DECL|member|ver_minor
id|u16
id|ver_minor
suffix:semicolon
DECL|member|logical_disk_start
id|u64
id|logical_disk_start
suffix:semicolon
DECL|member|logical_disk_size
id|u64
id|logical_disk_size
suffix:semicolon
DECL|member|config_start
id|u64
id|config_start
suffix:semicolon
DECL|member|config_size
id|u64
id|config_size
suffix:semicolon
DECL|member|disk_id
id|u8
id|disk_id
(braket
id|GUID_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tocblock
r_struct
id|tocblock
(brace
multiline_comment|/* We have exactly two bitmaps. */
DECL|member|bitmap1_name
id|u8
id|bitmap1_name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|bitmap1_start
id|u64
id|bitmap1_start
suffix:semicolon
DECL|member|bitmap1_size
id|u64
id|bitmap1_size
suffix:semicolon
DECL|member|bitmap2_name
id|u8
id|bitmap2_name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|bitmap2_start
id|u64
id|bitmap2_start
suffix:semicolon
DECL|member|bitmap2_size
id|u64
id|bitmap2_size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vmdb
r_struct
id|vmdb
(brace
multiline_comment|/* VMDB: The database header */
DECL|member|ver_major
id|u16
id|ver_major
suffix:semicolon
DECL|member|ver_minor
id|u16
id|ver_minor
suffix:semicolon
DECL|member|vblk_size
id|u32
id|vblk_size
suffix:semicolon
DECL|member|vblk_offset
id|u32
id|vblk_offset
suffix:semicolon
DECL|member|last_vblk_seq
id|u32
id|last_vblk_seq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vblk_comp
r_struct
id|vblk_comp
(brace
multiline_comment|/* VBLK Component */
DECL|member|state
id|u8
id|state
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|parent_id
id|u64
id|parent_id
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|children
id|u8
id|children
suffix:semicolon
DECL|member|chunksize
id|u16
id|chunksize
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vblk_dgrp
r_struct
id|vblk_dgrp
(brace
multiline_comment|/* VBLK Disk Group */
DECL|member|disk_id
id|u8
id|disk_id
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vblk_disk
r_struct
id|vblk_disk
(brace
multiline_comment|/* VBLK Disk */
DECL|member|disk_id
id|u8
id|disk_id
(braket
id|GUID_SIZE
)braket
suffix:semicolon
DECL|member|alt_name
id|u8
id|alt_name
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vblk_part
r_struct
id|vblk_part
(brace
multiline_comment|/* VBLK Partition */
DECL|member|start
id|u64
id|start
suffix:semicolon
DECL|member|size
id|u64
id|size
suffix:semicolon
multiline_comment|/* start, size and vol_off in sectors */
DECL|member|volume_offset
id|u64
id|volume_offset
suffix:semicolon
DECL|member|parent_id
id|u64
id|parent_id
suffix:semicolon
DECL|member|disk_id
id|u64
id|disk_id
suffix:semicolon
DECL|member|partnum
id|u8
id|partnum
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vblk_volu
r_struct
id|vblk_volu
(brace
multiline_comment|/* VBLK Volume */
DECL|member|volume_type
id|u8
id|volume_type
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|volume_state
id|u8
id|volume_state
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|guid
id|u8
id|guid
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|drive_hint
id|u8
id|drive_hint
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|size
id|u64
id|size
suffix:semicolon
DECL|member|partition_type
id|u8
id|partition_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vblk_head
r_struct
id|vblk_head
(brace
multiline_comment|/* VBLK standard header */
DECL|member|group
id|u32
id|group
suffix:semicolon
DECL|member|rec
id|u16
id|rec
suffix:semicolon
DECL|member|nrec
id|u16
id|nrec
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vblk
r_struct
id|vblk
(brace
multiline_comment|/* Generalised VBLK */
DECL|member|name
id|u8
id|name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|obj_id
id|u64
id|obj_id
suffix:semicolon
DECL|member|sequence
id|u32
id|sequence
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
r_union
(brace
DECL|member|comp
r_struct
id|vblk_comp
id|comp
suffix:semicolon
DECL|member|dgrp
r_struct
id|vblk_dgrp
id|dgrp
suffix:semicolon
DECL|member|disk
r_struct
id|vblk_disk
id|disk
suffix:semicolon
DECL|member|part
r_struct
id|vblk_part
id|part
suffix:semicolon
DECL|member|volu
r_struct
id|vblk_volu
id|volu
suffix:semicolon
DECL|member|vblk
)brace
id|vblk
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ldmdb
r_struct
id|ldmdb
(brace
multiline_comment|/* Cache of the database */
DECL|member|ph
r_struct
id|privhead
id|ph
suffix:semicolon
DECL|member|toc
r_struct
id|tocblock
id|toc
suffix:semicolon
DECL|member|vm
r_struct
id|vmdb
id|vm
suffix:semicolon
DECL|member|v_dgrp
r_struct
id|list_head
id|v_dgrp
suffix:semicolon
DECL|member|v_disk
r_struct
id|list_head
id|v_disk
suffix:semicolon
DECL|member|v_volu
r_struct
id|list_head
id|v_volu
suffix:semicolon
DECL|member|v_comp
r_struct
id|list_head
id|v_comp
suffix:semicolon
DECL|member|v_part
r_struct
id|list_head
id|v_part
suffix:semicolon
)brace
suffix:semicolon
r_int
id|ldm_partition
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
suffix:semicolon
macro_line|#endif /* _FS_PT_LDM_H_ */
eof
