macro_line|#ifndef _FS_PT_LDM_H_
DECL|macro|_FS_PT_LDM_H_
mdefine_line|#define _FS_PT_LDM_H_
multiline_comment|/*&n; * $Id: ldm.h,v 1.13 2001/07/23 19:49:49 antona Exp $&n; *&n; * ldm - Part of the Linux-NTFS project.&n; *&n; * Copyright (C) 2001 Richard Russon &lt;ntfs@flatcap.org&gt;&n; * Copyright (C) 2001 Anton Altaparmakov &lt;antona@users.sf.net&gt;&n; *&n; * Documentation is available at http://linux-ntfs.sf.net/ldm&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS source&n; * in the file COPYING); if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
multiline_comment|/* Borrowed from kernel.h. */
DECL|macro|LDM_PREFIX
mdefine_line|#define LDM_PREFIX&t;&quot;LDM: &quot;&t;   /* Prefix our error messages with this. */
DECL|macro|LDM_CRIT
mdefine_line|#define LDM_CRIT&t;KERN_CRIT&t;LDM_PREFIX /* critical conditions */
DECL|macro|LDM_ERR
mdefine_line|#define LDM_ERR&t;&t;KERN_ERR&t;LDM_PREFIX /* error conditions */
DECL|macro|LDM_DEBUG
mdefine_line|#define LDM_DEBUG&t;KERN_DEBUG&t;LDM_PREFIX /* debug-level messages */
multiline_comment|/* Magic numbers in CPU format. */
DECL|macro|MAGIC_VMDB
mdefine_line|#define MAGIC_VMDB&t;0x564D4442&t;&t;/* VMDB */
DECL|macro|MAGIC_VBLK
mdefine_line|#define MAGIC_VBLK&t;0x56424C4B&t;&t;/* VBLK */
DECL|macro|MAGIC_PRIVHEAD
mdefine_line|#define MAGIC_PRIVHEAD&t;0x5052495648454144&t;/* PRIVHEAD */
DECL|macro|MAGIC_TOCBLOCK
mdefine_line|#define MAGIC_TOCBLOCK&t;0x544F43424C4F434B&t;/* TOCBLOCK */
multiline_comment|/* The defined vblk types. */
DECL|macro|VBLK_COMP
mdefine_line|#define VBLK_COMP&t;&t;0x32&t;&t;/* Component */
DECL|macro|VBLK_PART
mdefine_line|#define VBLK_PART&t;&t;0x33&t;&t;/* Partition */
DECL|macro|VBLK_DISK
mdefine_line|#define VBLK_DISK&t;&t;0x34&t;&t;/* Disk */
DECL|macro|VBLK_DGRP
mdefine_line|#define VBLK_DGRP&t;&t;0x45&t;&t;/* Disk Group */
DECL|macro|VBLK_VOLU
mdefine_line|#define VBLK_VOLU&t;&t;0x51&t;&t;/* Volume */
multiline_comment|/* Other constants. */
DECL|macro|LDM_BLOCKSIZE
mdefine_line|#define LDM_BLOCKSIZE&t;&t;1024&t;&t;/* Size of block in bytes. */
DECL|macro|LDM_DB_SIZE
mdefine_line|#define LDM_DB_SIZE&t;&t;2048&t;&t;/* Size in sectors (= 1MiB). */
DECL|macro|LDM_FIRST_PART_OFFSET
mdefine_line|#define LDM_FIRST_PART_OFFSET&t;4&t;&t;/* Add this to first_part_minor&n;&t;&t;&t;&t;&t;&t;   to get to the first data&n;&t;&t;&t;&t;&t;&t;   partition device minor. */
DECL|macro|OFF_PRIVHEAD1
mdefine_line|#define OFF_PRIVHEAD1&t;&t;3&t;&t;/* Offset of the first privhead&n;&t;&t;&t;&t;&t;&t;   relative to the start of the&n;&t;&t;&t;&t;&t;&t;   device in units of&n;&t;&t;&t;&t;&t;&t;   LDM_BLOCKSIZE. */
multiline_comment|/* Offsets to structures within the LDM Database in units of LDM_BLOCKSIZE. */
DECL|macro|OFF_PRIVHEAD2
mdefine_line|#define OFF_PRIVHEAD2&t;&t;928&t;&t;/* Backup private headers. */
DECL|macro|OFF_PRIVHEAD3
mdefine_line|#define OFF_PRIVHEAD3&t;&t;1023
DECL|macro|OFF_TOCBLOCK1
mdefine_line|#define OFF_TOCBLOCK1&t;&t;0&t;&t;/* Tables of contents. */
DECL|macro|OFF_TOCBLOCK2
mdefine_line|#define OFF_TOCBLOCK2&t;&t;1
DECL|macro|OFF_TOCBLOCK3
mdefine_line|#define OFF_TOCBLOCK3&t;&t;1022
DECL|macro|OFF_TOCBLOCK4
mdefine_line|#define OFF_TOCBLOCK4&t;&t;1023
DECL|macro|OFF_VMDB
mdefine_line|#define OFF_VMDB&t;&t;8&t;&t;/* List of partitions. */
DECL|macro|OFF_VBLK
mdefine_line|#define OFF_VBLK&t;&t;9
DECL|macro|WIN2K_DYNAMIC_PARTITION
mdefine_line|#define WIN2K_DYNAMIC_PARTITION&t;&t;0x42&t;/* Formerly SFS (Landis). */
DECL|macro|WIN2K_EXTENDED_PARTITION
mdefine_line|#define WIN2K_EXTENDED_PARTITION&t;0x05&t;/* A standard extended&n;&t;&t;&t;&t;&t;&t;   partition. */
DECL|macro|TOC_BITMAP1
mdefine_line|#define TOC_BITMAP1&t;&t;&quot;config&quot;&t;/* Names of the two defined */
DECL|macro|TOC_BITMAP2
mdefine_line|#define TOC_BITMAP2&t;&t;&quot;log&quot;&t;&t;/* bitmaps in the TOCBLOCK. */
multiline_comment|/* Borrowed from msdos.c */
DECL|macro|SYS_IND
mdefine_line|#define SYS_IND(p)&t;&t;(get_unaligned(&amp;p-&gt;sys_ind))
DECL|macro|NR_SECTS
mdefine_line|#define NR_SECTS(p)&t;&t;({ __typeof__(p-&gt;nr_sects) __a =&t;&bslash;&n;&t;&t;&t;&t;&t;get_unaligned(&amp;p-&gt;nr_sects);&t;&bslash;&n;&t;&t;&t;&t;&t;le32_to_cpu(__a);&t;&t;&bslash;&n;&t;&t;&t;&t;})
DECL|macro|START_SECT
mdefine_line|#define START_SECT(p)&t;&t;({ __typeof__(p-&gt;start_sect) __a =&t;&bslash;&n;&t;&t;&t;&t;&t;get_unaligned(&amp;p-&gt;start_sect);&t;&bslash;&n;&t;&t;&t;&t;&t;le32_to_cpu(__a);&t;&t;&bslash;&n;&t;&t;&t;&t;})
multiline_comment|/* Most numbers we deal with are big-endian and won&squot;t be aligned. */
DECL|macro|BE16
mdefine_line|#define BE16(x)&t;&t;&t;((u16)be16_to_cpu(get_unaligned((u16*)(x))))
DECL|macro|BE32
mdefine_line|#define BE32(x)&t;&t;&t;((u32)be32_to_cpu(get_unaligned((u32*)(x))))
DECL|macro|BE64
mdefine_line|#define BE64(x)&t;&t;&t;((u64)be64_to_cpu(get_unaligned((u64*)(x))))
multiline_comment|/* In memory LDM database structures. */
DECL|macro|DISK_ID_SIZE
mdefine_line|#define DISK_ID_SIZE&t;&t;64&t;/* Size in bytes. */
DECL|struct|ldmdisk
r_struct
id|ldmdisk
(brace
DECL|member|obj_id
id|u64
id|obj_id
suffix:semicolon
DECL|member|disk_id
id|u8
id|disk_id
(braket
id|DISK_ID_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
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
id|DISK_ID_SIZE
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
multiline_comment|/*u64&t;bitmap1_flags;*/
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
multiline_comment|/*u64&t;bitmap2_flags;*/
)brace
suffix:semicolon
DECL|struct|vmdb
r_struct
id|vmdb
(brace
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
DECL|struct|vblk
r_struct
id|vblk
(brace
DECL|member|name
id|u8
id|name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|vblk_type
id|u8
id|vblk_type
suffix:semicolon
DECL|member|obj_id
id|u64
id|obj_id
suffix:semicolon
DECL|member|disk_id
id|u64
id|disk_id
suffix:semicolon
DECL|member|start_sector
id|u64
id|start_sector
suffix:semicolon
DECL|member|num_sectors
id|u64
id|num_sectors
suffix:semicolon
)brace
suffix:semicolon
r_int
id|ldm_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
id|kdev_t
id|dev
comma
r_int
r_int
id|first_sector
comma
r_int
id|first_part_minor
)paren
suffix:semicolon
macro_line|#endif /* _FS_PT_LDM_H_ */
eof
