multiline_comment|/*&n; * volume.h - Defines for volume structures in NTFS Linux kernel driver. Part&n; *&t;      of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001,2002 Anton Altaparmakov.&n; * Copyright (C) 2002 Richard Russon.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_VOLUME_H
DECL|macro|_LINUX_NTFS_VOLUME_H
mdefine_line|#define _LINUX_NTFS_VOLUME_H
macro_line|#include &quot;types.h&quot;
multiline_comment|/* These are used to determine which inode names are returned by readdir(). */
r_typedef
r_enum
(brace
DECL|enumerator|SHOW_SYSTEM
id|SHOW_SYSTEM
op_assign
l_int|1
comma
DECL|enumerator|SHOW_WIN32
id|SHOW_WIN32
op_assign
l_int|2
comma
DECL|enumerator|SHOW_DOS
id|SHOW_DOS
op_assign
l_int|4
comma
DECL|enumerator|SHOW_POSIX
id|SHOW_POSIX
op_assign
id|SHOW_WIN32
op_or
id|SHOW_DOS
comma
DECL|enumerator|SHOW_ALL
id|SHOW_ALL
op_assign
id|SHOW_SYSTEM
op_or
id|SHOW_POSIX
comma
DECL|typedef|READDIR_OPTIONS
)brace
id|READDIR_OPTIONS
suffix:semicolon
DECL|macro|RHideSystemFiles
mdefine_line|#define RHideSystemFiles(x)&t;(!((x) &amp; SHOW_SYSTEM))
DECL|macro|RHideLongNames
mdefine_line|#define RHideLongNames(x)&t;(!((x) &amp; SHOW_WIN32))
DECL|macro|RHideDosNames
mdefine_line|#define RHideDosNames(x)&t;(!((x) &amp; SHOW_DOS))
multiline_comment|/*&n; * The NTFS in memory super block structure.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*&n;&t; * FIXME: Reorder to have commonly used together element within the&n;&t; * same cache line, aiming at a cache line size of 32 bytes. Aim for&n;&t; * 64 bytes for less commonly used together elements. Put most commonly&n;&t; * used elements to front of structure. Obviously do this only when the&n;&t; * structure has stabilized... (AIA)&n;&t; */
multiline_comment|/* Device specifics. */
DECL|member|sb
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/* Pointer back to the super_block,&n;&t;&t;&t;&t;&t;   so we don&squot;t have to get the offset&n;&t;&t;&t;&t;&t;   every time. */
DECL|member|nr_blocks
id|LCN
id|nr_blocks
suffix:semicolon
multiline_comment|/* Number of NTFS_BLOCK_SIZE bytes&n;&t;&t;&t;&t;&t;   sized blocks on the device. */
multiline_comment|/* Configuration provided by user at mount time. */
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
multiline_comment|/* uid that files will be mounted as. */
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
multiline_comment|/* gid that files will be mounted as. */
DECL|member|fmask
id|mode_t
id|fmask
suffix:semicolon
multiline_comment|/* The mask for file permissions. */
DECL|member|dmask
id|mode_t
id|dmask
suffix:semicolon
multiline_comment|/* The mask for directory&n;&t;&t;&t;&t;&t;   permissions. */
DECL|member|readdir_opts
id|READDIR_OPTIONS
id|readdir_opts
suffix:semicolon
multiline_comment|/* Namespace of inode names to show. */
DECL|member|mft_zone_multiplier
id|u8
id|mft_zone_multiplier
suffix:semicolon
multiline_comment|/* Initial mft zone multiplier. */
DECL|member|on_errors
id|u8
id|on_errors
suffix:semicolon
multiline_comment|/* What to do on file system errors. */
multiline_comment|/* NTFS bootsector provided information. */
DECL|member|sector_size
id|u16
id|sector_size
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|sector_size_bits
id|u8
id|sector_size_bits
suffix:semicolon
multiline_comment|/* log2(sector_size) */
DECL|member|cluster_size
id|u32
id|cluster_size
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|cluster_size_mask
id|u32
id|cluster_size_mask
suffix:semicolon
multiline_comment|/* cluster_size - 1 */
DECL|member|cluster_size_bits
id|u8
id|cluster_size_bits
suffix:semicolon
multiline_comment|/* log2(cluster_size) */
DECL|member|mft_record_size
id|u32
id|mft_record_size
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|mft_record_size_mask
id|u32
id|mft_record_size_mask
suffix:semicolon
multiline_comment|/* mft_record_size - 1 */
DECL|member|mft_record_size_bits
id|u8
id|mft_record_size_bits
suffix:semicolon
multiline_comment|/* log2(mft_record_size) */
DECL|member|index_record_size
id|u32
id|index_record_size
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|index_record_size_mask
id|u32
id|index_record_size_mask
suffix:semicolon
multiline_comment|/* index_record_size - 1 */
DECL|member|index_record_size_bits
id|u8
id|index_record_size_bits
suffix:semicolon
multiline_comment|/* log2(index_record_size) */
r_union
(brace
DECL|member|nr_clusters
id|LCN
id|nr_clusters
suffix:semicolon
multiline_comment|/* Volume size in clusters. */
DECL|member|nr_lcn_bits
id|LCN
id|nr_lcn_bits
suffix:semicolon
multiline_comment|/* Number of bits in lcn bitmap. */
)brace
id|SN
c_func
(paren
id|vcl
)paren
suffix:semicolon
DECL|member|mft_lcn
id|LCN
id|mft_lcn
suffix:semicolon
multiline_comment|/* Cluster location of mft data. */
DECL|member|mftmirr_lcn
id|LCN
id|mftmirr_lcn
suffix:semicolon
multiline_comment|/* Cluster location of copy of mft. */
DECL|member|serial_no
id|u64
id|serial_no
suffix:semicolon
multiline_comment|/* The volume serial number. */
multiline_comment|/* Mount specific NTFS information. */
DECL|member|upcase_len
id|u32
id|upcase_len
suffix:semicolon
multiline_comment|/* Number of entries in upcase[]. */
DECL|member|upcase
id|uchar_t
op_star
id|upcase
suffix:semicolon
multiline_comment|/* The upcase table. */
DECL|member|mft_zone_start
id|LCN
id|mft_zone_start
suffix:semicolon
multiline_comment|/* First cluster of the mft zone. */
DECL|member|mft_zone_end
id|LCN
id|mft_zone_end
suffix:semicolon
multiline_comment|/* First cluster beyond the mft zone. */
DECL|member|mft_ino
r_struct
id|inode
op_star
id|mft_ino
suffix:semicolon
multiline_comment|/* The VFS inode of $MFT. */
DECL|member|mftbmp_lock
r_struct
id|rw_semaphore
id|mftbmp_lock
suffix:semicolon
multiline_comment|/* Lock for serializing accesses to the&n;&t;&t;&t;&t;&t;    mft record bitmap ($MFT/$BITMAP). */
r_union
(brace
DECL|member|nr_mft_records
id|s64
id|nr_mft_records
suffix:semicolon
multiline_comment|/* Number of records in the mft. */
DECL|member|nr_mft_bits
id|s64
id|nr_mft_bits
suffix:semicolon
multiline_comment|/* Number of bits in mft bitmap. */
)brace
id|SN
c_func
(paren
id|vmm
)paren
suffix:semicolon
DECL|member|mftbmp_mapping
r_struct
id|address_space
id|mftbmp_mapping
suffix:semicolon
multiline_comment|/* Page cache for $MFT/$BITMAP. */
DECL|member|mftbmp_rl
id|run_list
id|mftbmp_rl
suffix:semicolon
multiline_comment|/* Run list for $MFT/$BITMAP. */
DECL|member|mftbmp_size
id|s64
id|mftbmp_size
suffix:semicolon
multiline_comment|/* Data size of $MFT/$BITMAP. */
DECL|member|mftbmp_initialized_size
id|s64
id|mftbmp_initialized_size
suffix:semicolon
multiline_comment|/* Initialized size of $MFT/$BITMAP. */
DECL|member|mftbmp_allocated_size
id|s64
id|mftbmp_allocated_size
suffix:semicolon
multiline_comment|/* Allocated size of $MFT/$BITMAP. */
DECL|member|mftmirr_ino
r_struct
id|inode
op_star
id|mftmirr_ino
suffix:semicolon
multiline_comment|/* The VFS inode of $MFTMirr. */
DECL|member|lcnbmp_ino
r_struct
id|inode
op_star
id|lcnbmp_ino
suffix:semicolon
multiline_comment|/* The VFS inode of $Bitmap. */
DECL|member|lcnbmp_lock
r_struct
id|rw_semaphore
id|lcnbmp_lock
suffix:semicolon
multiline_comment|/* Lock for serializing accesses to the&n;&t;&t;&t;&t;&t;    cluster bitmap ($Bitmap/$DATA). */
DECL|member|vol_ino
r_struct
id|inode
op_star
id|vol_ino
suffix:semicolon
multiline_comment|/* The VFS inode of $Volume. */
DECL|member|vol_flags
r_int
r_int
id|vol_flags
suffix:semicolon
multiline_comment|/* Volume flags (VOLUME_*). */
DECL|member|major_ver
id|u8
id|major_ver
suffix:semicolon
multiline_comment|/* Ntfs major version of volume. */
DECL|member|minor_ver
id|u8
id|minor_ver
suffix:semicolon
multiline_comment|/* Ntfs minor version of volume. */
DECL|member|root_ino
r_struct
id|inode
op_star
id|root_ino
suffix:semicolon
multiline_comment|/* The VFS inode of the root&n;&t;&t;&t;&t;&t;   directory. */
DECL|member|secure_ino
r_struct
id|inode
op_star
id|secure_ino
suffix:semicolon
multiline_comment|/* The VFS inode of $Secure (NTFS3.0+&n;&t;&t;&t;&t;&t;   only, otherwise NULL). */
DECL|member|nls_map
r_struct
id|nls_table
op_star
id|nls_map
suffix:semicolon
DECL|typedef|ntfs_volume
)brace
id|ntfs_volume
suffix:semicolon
DECL|macro|_VCL
mdefine_line|#define _VCL(X)  SC(vcl,X)
DECL|macro|_VMM
mdefine_line|#define _VMM(X)  SC(vmm,X)
macro_line|#endif /* _LINUX_NTFS_VOLUME_H */
eof
