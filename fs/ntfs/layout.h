multiline_comment|/*&n; * layout.h - All NTFS associated on-disk structures. Part of the Linux-NTFS&n; *&t;      project.&n; *&n; * Copyright (c) 2001,2002 Anton Altaparmakov.&n; * Copyright (C) 2002 Richard Russon.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_LAYOUT_H
DECL|macro|_LINUX_NTFS_LAYOUT_H
mdefine_line|#define _LINUX_NTFS_LAYOUT_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;types.h&quot;
multiline_comment|/*&n; * Constant endianness conversion defines.&n; */
DECL|macro|const_le16_to_cpu
mdefine_line|#define const_le16_to_cpu(x)&t;__constant_le16_to_cpu(x)
DECL|macro|const_le32_to_cpu
mdefine_line|#define const_le32_to_cpu(x)&t;__constant_le32_to_cpu(x)
DECL|macro|const_le64_to_cpu
mdefine_line|#define const_le64_to_cpu(x)&t;__constant_le64_to_cpu(x)
DECL|macro|const_cpu_to_le16
mdefine_line|#define const_cpu_to_le16(x)&t;__constant_cpu_to_le16(x)
DECL|macro|const_cpu_to_le32
mdefine_line|#define const_cpu_to_le32(x)&t;__constant_cpu_to_le32(x)
DECL|macro|const_cpu_to_le64
mdefine_line|#define const_cpu_to_le64(x)&t;__constant_cpu_to_le64(x)
multiline_comment|/* The NTFS oem_id */
DECL|macro|magicNTFS
mdefine_line|#define magicNTFS&t;const_cpu_to_le64(0x202020205346544e) /* &quot;NTFS    &quot; */
multiline_comment|/*&n; * Location of bootsector on partition:&n; * &t;The standard NTFS_BOOT_SECTOR is on sector 0 of the partition.&n; * &t;On NT4 and above there is one backup copy of the boot sector to&n; * &t;be found on the last sector of the partition (not normally accessible&n; * &t;from within Windows as the bootsector contained number of sectors&n; *&t;value is one less than the actual value!).&n; * &t;On versions of NT 3.51 and earlier, the backup copy was located at &n; * &t;number of sectors/2 (integer divide), i.e. in the middle of the volume.&n; */
multiline_comment|/*&n; * BIOS parameter block (bpb) structure.&n; */
r_typedef
r_struct
(brace
DECL|member|bytes_per_sector
id|u16
id|bytes_per_sector
suffix:semicolon
multiline_comment|/* Size of a sector in bytes. */
DECL|member|sectors_per_cluster
id|u8
id|sectors_per_cluster
suffix:semicolon
multiline_comment|/* Size of a cluster in sectors. */
DECL|member|reserved_sectors
id|u16
id|reserved_sectors
suffix:semicolon
multiline_comment|/* zero */
DECL|member|fats
id|u8
id|fats
suffix:semicolon
multiline_comment|/* zero */
DECL|member|root_entries
id|u16
id|root_entries
suffix:semicolon
multiline_comment|/* zero */
DECL|member|sectors
id|u16
id|sectors
suffix:semicolon
multiline_comment|/* zero */
DECL|member|media_type
id|u8
id|media_type
suffix:semicolon
multiline_comment|/* 0xf8 = hard disk */
DECL|member|sectors_per_fat
id|u16
id|sectors_per_fat
suffix:semicolon
multiline_comment|/* zero */
DECL|member|sectors_per_track
id|u16
id|sectors_per_track
suffix:semicolon
multiline_comment|/* irrelevant */
DECL|member|heads
id|u16
id|heads
suffix:semicolon
multiline_comment|/* irrelevant */
DECL|member|hidden_sectors
id|u32
id|hidden_sectors
suffix:semicolon
multiline_comment|/* zero */
DECL|member|large_sectors
id|u32
id|large_sectors
suffix:semicolon
multiline_comment|/* zero */
DECL|typedef|BIOS_PARAMETER_BLOCK
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|BIOS_PARAMETER_BLOCK
suffix:semicolon
multiline_comment|/*&n; * NTFS boot sector structure.&n; */
r_typedef
r_struct
(brace
DECL|member|jump
id|u8
id|jump
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Irrelevant (jump to boot up code).*/
DECL|member|oem_id
id|u64
id|oem_id
suffix:semicolon
multiline_comment|/* Magic &quot;NTFS    &quot;. */
DECL|member|bpb
id|BIOS_PARAMETER_BLOCK
id|bpb
suffix:semicolon
multiline_comment|/* See BIOS_PARAMETER_BLOCK. */
DECL|member|unused
id|u8
id|unused
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* zero, NTFS diskedit.exe states that&n;&t;&t;&t;&t;&t;   this is actually:&n;&t;&t;&t;&t;&t;&t;__u8 physical_drive;&t;// 0x80&n;&t;&t;&t;&t;&t;&t;__u8 current_head;&t;// zero&n;&t;&t;&t;&t;&t;&t;__u8 extended_boot_signature;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;// 0x80&n;&t;&t;&t;&t;&t;&t;__u8 unused;&t;&t;// zero&n;&t;&t;&t;&t;&t; */
DECL|member|number_of_sectors
multiline_comment|/*0x28*/
id|s64
id|number_of_sectors
suffix:semicolon
multiline_comment|/* Number of sectors in volume. Gives&n;&t;&t;&t;&t;&t;   maximum volume size of 2^63 sectors.&n;&t;&t;&t;&t;&t;   Assuming standard sector size of 512&n;&t;&t;&t;&t;&t;   bytes, the maximum byte size is&n;&t;&t;&t;&t;&t;   approx. 4.7x10^21 bytes. (-; */
DECL|member|mft_lcn
id|s64
id|mft_lcn
suffix:semicolon
multiline_comment|/* Cluster location of mft data. */
DECL|member|mftmirr_lcn
id|s64
id|mftmirr_lcn
suffix:semicolon
multiline_comment|/* Cluster location of copy of mft. */
DECL|member|clusters_per_mft_record
id|s8
id|clusters_per_mft_record
suffix:semicolon
multiline_comment|/* Mft record size in clusters. */
DECL|member|reserved0
id|u8
id|reserved0
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* zero */
DECL|member|clusters_per_index_record
id|s8
id|clusters_per_index_record
suffix:semicolon
multiline_comment|/* Index block size in clusters. */
DECL|member|reserved1
id|u8
id|reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* zero */
DECL|member|volume_serial_number
id|u64
id|volume_serial_number
suffix:semicolon
multiline_comment|/* Irrelevant (serial number). */
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
multiline_comment|/* Boot sector checksum. */
DECL|member|bootstrap
multiline_comment|/*0x54*/
id|u8
id|bootstrap
(braket
l_int|426
)braket
suffix:semicolon
multiline_comment|/* Irrelevant (boot up code). */
DECL|member|end_of_sector_marker
id|u16
id|end_of_sector_marker
suffix:semicolon
multiline_comment|/* End of bootsector magic. Always is&n;&t;&t;&t;&t;&t;   0xaa55 in little endian. */
multiline_comment|/* sizeof() = 512 (0x200) bytes */
DECL|typedef|NTFS_BOOT_SECTOR
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|NTFS_BOOT_SECTOR
suffix:semicolon
multiline_comment|/*&n; * Magic identifiers present at the beginning of all ntfs record containing&n; * records (like mft records for example).&n; */
r_typedef
r_enum
(brace
DECL|enumerator|magic_BAAD
id|magic_BAAD
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x44414142
)paren
comma
multiline_comment|/* BAAD == corrupt record */
DECL|enumerator|magic_CHKD
id|magic_CHKD
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x424b4843
)paren
comma
multiline_comment|/* CHKD == chkdsk ??? */
DECL|enumerator|magic_FILE
id|magic_FILE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x454c4946
)paren
comma
multiline_comment|/* FILE == mft entry */
DECL|enumerator|magic_HOLE
id|magic_HOLE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x454c4f48
)paren
comma
multiline_comment|/* HOLE == ? (NTFS 3.0+?) */
DECL|enumerator|magic_INDX
id|magic_INDX
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x58444e49
)paren
comma
multiline_comment|/* INDX == index buffer */
DECL|typedef|NTFS_RECORD_TYPES
)brace
id|NTFS_RECORD_TYPES
suffix:semicolon
multiline_comment|/*&n; * Generic magic comparison macros. Finally found a use for the ## preprocessor&n; * operator! (-8&n; */
DECL|macro|is_magic
mdefine_line|#define is_magic(x, m)&t;&t;(   (u32)(x) == magic_##m )
DECL|macro|is_magicp
mdefine_line|#define is_magicp(p, m) &t;( *(u32*)(p) == magic_##m )
multiline_comment|/*&n; * Specialised magic comparison macros.&n; */
DECL|macro|is_baad_record
mdefine_line|#define is_baad_record(x)&t;( is_magic (x, BAAD) )
DECL|macro|is_baad_recordp
mdefine_line|#define is_baad_recordp(p)&t;( is_magicp(p, BAAD) )
DECL|macro|is_chkd_record
mdefine_line|#define is_chkd_record(x)       ( is_magic (x, CHKD) )
DECL|macro|is_chkd_recordp
mdefine_line|#define is_chkd_recordp(p)      ( is_magicp(p, CHKD) )
DECL|macro|is_file_record
mdefine_line|#define is_file_record(x)&t;( is_magic (x, FILE) )
DECL|macro|is_file_recordp
mdefine_line|#define is_file_recordp(p)&t;( is_magicp(p, FILE) )
DECL|macro|is_hole_record
mdefine_line|#define is_hole_record(x)       ( is_magic (x, HOLE) )
DECL|macro|is_hole_recordp
mdefine_line|#define is_hole_recordp(p)      ( is_magicp(p, HOLE) )
DECL|macro|is_indx_record
mdefine_line|#define is_indx_record(x)       ( is_magic (x, INDX) )
DECL|macro|is_indx_recordp
mdefine_line|#define is_indx_recordp(p)      ( is_magicp(p, INDX) )
DECL|macro|is_mft_record
mdefine_line|#define is_mft_record(x)&t;( is_file_record(x) )
DECL|macro|is_mft_recordp
mdefine_line|#define is_mft_recordp(p)&t;( is_file_recordp(p) )
multiline_comment|/*&n; * The Update Sequence Array (usa) is an array of the u16 values which belong&n; * to the end of each sector protected by the update sequence record in which&n; * this array is contained. Note that the first entry is the Update Sequence&n; * Number (usn), a cyclic counter of how many times the protected record has&n; * been written to disk. The values 0 and -1 (ie. 0xffff) are not used. All&n; * last u16&squot;s of each sector have to be equal to the usn (during reading) or&n; * are set to it (during writing). If they are not, an incomplete multi sector&n; * transfer has occured when the data was written.&n; * The maximum size for the update sequence array is fixed to:&n; * &t;maximum size = usa_ofs + (usa_count * 2) = 510 bytes&n; * The 510 bytes comes from the fact that the last u16 in the array has to&n; * (obviously) finish before the last u16 of the first 512-byte sector.&n; * This formula can be used as a consistency check in that usa_ofs +&n; * (usa_count * 2) has to be less than or equal to 510.&n; */
r_typedef
r_struct
(brace
DECL|member|magic
id|NTFS_RECORD_TYPES
id|magic
suffix:semicolon
multiline_comment|/* A four-byte magic identifying the&n;&t;&t;&t;&t;&t;   record type and/or status. */
DECL|member|usa_ofs
id|u16
id|usa_ofs
suffix:semicolon
multiline_comment|/* Offset to the Update Sequence Array (usa)&n;&t;&t;&t;&t;   from the start of the ntfs record. */
DECL|member|usa_count
id|u16
id|usa_count
suffix:semicolon
multiline_comment|/* Number of u16 sized entries in the usa&n;&t;&t;&t;&t;   including the Update Sequence Number (usn),&n;&t;&t;&t;&t;   thus the number of fixups is the usa_count&n;&t;&t;&t;&t;   minus 1. */
DECL|typedef|NTFS_RECORD
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|NTFS_RECORD
suffix:semicolon
multiline_comment|/*&n; * System files mft record numbers. All these files are always marked as used&n; * in the bitmap attribute of the mft; presumably in order to avoid accidental&n; * allocation for random other mft records. Also, the sequence number for each&n; * of the system files is always equal to their mft record number and it is&n; * never modified.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|FILE_MFT
id|FILE_MFT
op_assign
l_int|0
comma
multiline_comment|/* Master file table (mft). Data attribute&n;&t;&t;&t;&t;   contains the entries and bitmap attribute&n;&t;&t;&t;&t;   records which ones are in use (bit==1). */
DECL|enumerator|FILE_MFTMirr
id|FILE_MFTMirr
op_assign
l_int|1
comma
multiline_comment|/* Mft mirror: copy of first four mft records&n;&t;&t;&t;&t;   in data attribute. If cluster size &gt; 4kiB,&n;&t;&t;&t;&t;   copy of first N mft records, with&n;&t;&t;&t;&t;&t;N = cluster_size / mft_record_size. */
DECL|enumerator|FILE_LogFile
id|FILE_LogFile
op_assign
l_int|2
comma
multiline_comment|/* Journalling log in data attribute. */
DECL|enumerator|FILE_Volume
id|FILE_Volume
op_assign
l_int|3
comma
multiline_comment|/* Volume name attribute and volume information&n;&t;&t;&t;&t;   attribute (flags and ntfs version). Windows&n;&t;&t;&t;&t;   refers to this file as volume DASD (Direct&n;&t;&t;&t;&t;   Access Storage Device). */
DECL|enumerator|FILE_AttrDef
id|FILE_AttrDef
op_assign
l_int|4
comma
multiline_comment|/* Array of attribute definitions in data&n;&t;&t;&t;&t;   attribute. */
DECL|enumerator|FILE_root
id|FILE_root
op_assign
l_int|5
comma
multiline_comment|/* Root directory. */
DECL|enumerator|FILE_Bitmap
id|FILE_Bitmap
op_assign
l_int|6
comma
multiline_comment|/* Allocation bitmap of all clusters (lcns) in&n;&t;&t;&t;&t;   data attribute. */
DECL|enumerator|FILE_Boot
id|FILE_Boot
op_assign
l_int|7
comma
multiline_comment|/* Boot sector (always at cluster 0) in data&n;&t;&t;&t;&t;   attribute. */
DECL|enumerator|FILE_BadClus
id|FILE_BadClus
op_assign
l_int|8
comma
multiline_comment|/* Contains all bad clusters in the non-resident&n;&t;&t;&t;&t;   data attribute. */
DECL|enumerator|FILE_Secure
id|FILE_Secure
op_assign
l_int|9
comma
multiline_comment|/* Shared security descriptors in data attribute&n;&t;&t;&t;&t;   and two indexes into the descriptors.&n;&t;&t;&t;&t;   Appeared in Windows 2000. Before that, this&n;&t;&t;&t;&t;   file was named $Quota but was unused. */
DECL|enumerator|FILE_UpCase
id|FILE_UpCase
op_assign
l_int|10
comma
multiline_comment|/* Uppercase equivalents of all 65536 Unicode&n;&t;&t;&t;&t;   characters in data attribute. */
DECL|enumerator|FILE_Extend
id|FILE_Extend
op_assign
l_int|11
comma
multiline_comment|/* Directory containing other system files (eg.&n;&t;&t;&t;&t;   $ObjId, $Quota, $Reparse and $UsnJrnl). This&n;&t;&t;&t;&t;   is new to NTFS3.0. */
DECL|enumerator|FILE_reserved12
id|FILE_reserved12
op_assign
l_int|12
comma
multiline_comment|/* Reserved for future use (records 12-15). */
DECL|enumerator|FILE_reserved13
id|FILE_reserved13
op_assign
l_int|13
comma
DECL|enumerator|FILE_reserved14
id|FILE_reserved14
op_assign
l_int|14
comma
DECL|enumerator|FILE_reserved15
id|FILE_reserved15
op_assign
l_int|15
comma
DECL|enumerator|FILE_first_user
id|FILE_first_user
op_assign
l_int|16
comma
multiline_comment|/* First user file, used as test limit for&n;&t;&t;&t;&t;   whether to allow opening a file or not. */
DECL|typedef|NTFS_SYSTEM_FILES
)brace
id|NTFS_SYSTEM_FILES
suffix:semicolon
multiline_comment|/*&n; * These are the so far known MFT_RECORD_* flags (16-bit) which contain &n; * information about the mft record in which they are present.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|MFT_RECORD_IN_USE
id|MFT_RECORD_IN_USE
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0001
)paren
comma
DECL|enumerator|MFT_RECORD_IS_DIRECTORY
id|MFT_RECORD_IS_DIRECTORY
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0002
)paren
comma
DECL|enumerator|MFT_REC_SPACE_FILLER
id|MFT_REC_SPACE_FILLER
op_assign
l_int|0xffff
multiline_comment|/* Just to make flags 16-bit. */
DECL|typedef|MFT_RECORD_FLAGS
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|MFT_RECORD_FLAGS
suffix:semicolon
multiline_comment|/*&n; * mft references (aka file references or file record segment references) are&n; * used whenever a structure needs to refer to a record in the mft.&n; * &n; * A reference consists of a 48-bit index into the mft and a 16-bit sequence&n; * number used to detect stale references.&n; *&n; * For error reporting purposes we treat the 48-bit index as a signed quantity.&n; *&n; * The sequence number is a circular counter (skipping 0) describing how many&n; * times the referenced mft record has been (re)used. This has to match the&n; * sequence number of the mft record being referenced, otherwise the reference&n; * is considered stale and removed (FIXME: only ntfsck or the driver itself?).&n; *&n; * If the sequence number is zero it is assumed that no sequence number&n; * consistency checking should be performed.&n; *&n; * FIXME: Since inodes are 32-bit as of now, the driver needs to always check&n; * for high_part being 0 and if not either BUG(), cause a panic() or handle&n; * the situation in some other way. This shouldn&squot;t be a problem as a volume has&n; * to become HUGE in order to need more than 32-bits worth of mft records.&n; * Assuming the standard mft record size of 1kb only the records (never mind&n; * the non-resident attributes, etc.) would require 4Tb of space on their own&n; * for the first 32 bits worth of records. This is only if some strange person&n; * doesn&squot;t decide to foul play and make the mft sparse which would be a really&n; * horrible thing to do as it would trash our current driver implementation. )-:&n; * Do I hear screams &quot;we want 64-bit inodes!&quot; ?!? (-;&n; *&n; * FIXME: The mft zone is defined as the first 12% of the volume. This space is&n; * reserved so that the mft can grow contiguously and hence doesn&squot;t become &n; * fragmented. Volume free space includes the empty part of the mft zone and&n; * when the volume&squot;s free 88% are used up, the mft zone is shrunk by a factor&n; * of 2, thus making more space available for more files/data. This process is&n; * repeated everytime there is no more free space except for the mft zone until&n; * there really is no more free space.&n; */
multiline_comment|/*&n; * Typedef the MFT_REF as a 64-bit value for easier handling.&n; * Also define two unpacking macros to get to the reference (MREF) and&n; * sequence number (MSEQNO) respectively.&n; * The _LE versions are to be applied on little endian MFT_REFs.&n; * Note: The _LE versions will return a CPU endian formatted value!&n; */
r_typedef
r_enum
(brace
DECL|enumerator|MFT_REF_MASK_CPU
id|MFT_REF_MASK_CPU
op_assign
l_int|0x0000ffffffffffffULL
comma
DECL|enumerator|MFT_REF_MASK_LE
id|MFT_REF_MASK_LE
op_assign
id|const_cpu_to_le64
c_func
(paren
l_int|0x0000ffffffffffffULL
)paren
comma
DECL|typedef|MFT_REF_CONSTS
)brace
id|MFT_REF_CONSTS
suffix:semicolon
DECL|typedef|MFT_REF
r_typedef
id|u64
id|MFT_REF
suffix:semicolon
DECL|macro|MREF
mdefine_line|#define MREF(x)&t;&t;((u64)((x) &amp; MFT_REF_MASK_CPU))
DECL|macro|MSEQNO
mdefine_line|#define MSEQNO(x)&t;((u16)(((x) &gt;&gt; 48) &amp; 0xffff))
DECL|macro|MREF_LE
mdefine_line|#define MREF_LE(x)&t;((u64)(le64_to_cpu(x) &amp; MFT_REF_MASK_CPU))
DECL|macro|MSEQNO_LE
mdefine_line|#define MSEQNO_LE(x)&t;((u16)((le64_to_cpu(x) &gt;&gt; 48) &amp; 0xffff))
DECL|macro|IS_ERR_MREF
mdefine_line|#define IS_ERR_MREF(x)&t;(((x) &amp; 0x0000800000000000ULL) ? 1 : 0)
DECL|macro|ERR_MREF
mdefine_line|#define ERR_MREF(x)&t;((u64)((s64)(x)))
DECL|macro|MREF_ERR
mdefine_line|#define MREF_ERR(x)&t;((int)((s64)(x)))
multiline_comment|/*&n; * The mft record header present at the beginning of every record in the mft.&n; * This is followed by a sequence of variable length attribute records which&n; * is terminated by an attribute of type AT_END which is a truncated attribute&n; * in that it only consists of the attribute type code AT_END and none of the&n; * other members of the attribute structure are present.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*Ofs*/
multiline_comment|/*  0*/
id|NTFS_RECORD
id|SN
c_func
(paren
id|mnr
)paren
suffix:semicolon
multiline_comment|/* Usually the magic is &quot;FILE&quot;. */
DECL|member|lsn
multiline_comment|/*  8*/
id|u64
id|lsn
suffix:semicolon
multiline_comment|/* $LogFile sequence number for this record.&n;&t;&t;&t;&t;   Changed every time the record is modified. */
DECL|member|sequence_number
multiline_comment|/* 16*/
id|u16
id|sequence_number
suffix:semicolon
multiline_comment|/* Number of times this mft record has been&n;&t;&t;   &t;&t;   reused. (See description for MFT_REF&n;&t;&t;&t;&t;   above.) NOTE: The increment (skipping zero)&n;&t;&t;&t;&t;   is done when the file is deleted. NOTE: If&n;&t;&t;&t;&t;   this is zero it is left zero. */
DECL|member|link_count
multiline_comment|/* 18*/
id|u16
id|link_count
suffix:semicolon
multiline_comment|/* Number of hard links, i.e. the number of &n;&t;&t;&t;&t;   directory entries referencing this record.&n;&t;&t;&t;&t;   NOTE: Only used in mft base records.&n;&t;&t;&t;&t;   NOTE: When deleting a directory entry we&n;&t;&t;&t;&t;   check the link_count and if it is 1 we&n;&t;&t;&t;&t;   delete the file. Otherwise we delete the&n;&t;&t;&t;&t;   FILE_NAME_ATTR being referenced by the&n;&t;&t;&t;&t;   directory entry from the mft record and&n;&t;&t;&t;&t;   decrement the link_count.&n;&t;&t;&t;&t;   FIXME: Careful with Win32 + DOS names! */
DECL|member|attrs_offset
multiline_comment|/* 20*/
id|u16
id|attrs_offset
suffix:semicolon
multiline_comment|/* Byte offset to the first attribute in this&n;&t;&t;&t;&t;   mft record from the start of the mft record.&n;&t;&t;&t;&t;   NOTE: Must be aligned to 8-byte boundary. */
DECL|member|flags
multiline_comment|/* 22*/
id|MFT_RECORD_FLAGS
id|flags
suffix:semicolon
multiline_comment|/* Bit array of MFT_RECORD_FLAGS. When a file&n;&t;&t;&t;&t;   is deleted, the MFT_RECORD_IN_USE flag is&n;&t;&t;&t;&t;   set to zero. */
DECL|member|bytes_in_use
multiline_comment|/* 24*/
id|u32
id|bytes_in_use
suffix:semicolon
multiline_comment|/* Number of bytes used in this mft record.&n;&t;&t;&t;&t;   NOTE: Must be aligned to 8-byte boundary. */
DECL|member|bytes_allocated
multiline_comment|/* 28*/
id|u32
id|bytes_allocated
suffix:semicolon
multiline_comment|/* Number of bytes allocated for this mft&n;&t;&t;&t;&t;   record. This should be equal to the mft&n;&t;&t;&t;&t;   record size. */
DECL|member|base_mft_record
multiline_comment|/* 32*/
id|MFT_REF
id|base_mft_record
suffix:semicolon
multiline_comment|/* This is zero for base mft records.&n;&t;&t;&t;&t;   When it is not zero it is a mft reference&n;&t;&t;&t;&t;   pointing to the base mft record to which&n;&t;&t;&t;&t;   this record belongs (this is then used to&n;&t;&t;&t;&t;   locate the attribute list attribute present&n;&t;&t;&t;&t;   in the base record which describes this&n;&t;&t;&t;&t;   extension record and hence might need&n;&t;&t;&t;&t;   modification when the extension record&n;&t;&t;&t;&t;   itself is modified, also locating the&n;&t;&t;&t;&t;   attribute list also means finding the other&n;&t;&t;&t;&t;   potential extents, belonging to the non-base&n;&t;&t;&t;&t;   mft record). */
DECL|member|next_attr_instance
multiline_comment|/* 40*/
id|u16
id|next_attr_instance
suffix:semicolon
multiline_comment|/* The instance number that will be&n;&t;&t;&t;&t;   assigned to the next attribute added to this&n;&t;&t;&t;&t;   mft record. NOTE: Incremented each time&n;&t;&t;&t;&t;   after it is used. NOTE: Every time the mft&n;&t;&t;&t;&t;   record is reused this number is set to zero.&n;&t;&t;&t;&t;   NOTE: The first instance number is always 0.&n;&t;&t;&t;&t; */
multiline_comment|/* sizeof() = 42 bytes */
multiline_comment|/* NTFS 3.1+ (Windows XP and above) introduce the following additions. */
multiline_comment|/* 42*/
singleline_comment|//u16 reserved;&t;&t;/* Reserved/alignment. */
multiline_comment|/* 44*/
singleline_comment|//u32 mft_record_number;/* Number of this mft record. */
multiline_comment|/* sizeof() = 48 bytes */
multiline_comment|/*&n; * When (re)using the mft record, we place the update sequence array at this&n; * offset, i.e. before we start with the attributes. This also makes sense,&n; * otherwise we could run into problems with the update sequence array&n; * containing in itself the last two bytes of a sector which would mean that&n; * multi sector transfer protection wouldn&squot;t work. As you can&squot;t protect data&n; * by overwriting it since you then can&squot;t get it back...&n; * When reading we obviously use the data from the ntfs record header.&n; */
DECL|typedef|MFT_RECORD
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|MFT_RECORD
suffix:semicolon
DECL|macro|_MNR
mdefine_line|#define _MNR(X)  SC(mnr,X)
multiline_comment|/*&n; * System defined attributes (32-bit). Each attribute type has a corresponding&n; * attribute name (Unicode string of maximum 64 character length) as described&n; * by the attribute definitions present in the data attribute of the $AttrDef&n; * system file. On NTFS 3.0 volumes the names are just as the types are named&n; * in the below enum exchanging AT_ for the dollar sign ($). If that isn&squot;t a&n; * revealing choice of symbol... (-;&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AT_UNUSED
id|AT_UNUSED
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0
)paren
comma
DECL|enumerator|AT_STANDARD_INFORMATION
id|AT_STANDARD_INFORMATION
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x10
)paren
comma
DECL|enumerator|AT_ATTRIBUTE_LIST
id|AT_ATTRIBUTE_LIST
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x20
)paren
comma
DECL|enumerator|AT_FILE_NAME
id|AT_FILE_NAME
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x30
)paren
comma
DECL|enumerator|AT_OBJECT_ID
id|AT_OBJECT_ID
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x40
)paren
comma
DECL|enumerator|AT_SECURITY_DESCRIPTOR
id|AT_SECURITY_DESCRIPTOR
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x50
)paren
comma
DECL|enumerator|AT_VOLUME_NAME
id|AT_VOLUME_NAME
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x60
)paren
comma
DECL|enumerator|AT_VOLUME_INFORMATION
id|AT_VOLUME_INFORMATION
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x70
)paren
comma
DECL|enumerator|AT_DATA
id|AT_DATA
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x80
)paren
comma
DECL|enumerator|AT_INDEX_ROOT
id|AT_INDEX_ROOT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x90
)paren
comma
DECL|enumerator|AT_INDEX_ALLOCATION
id|AT_INDEX_ALLOCATION
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0xa0
)paren
comma
DECL|enumerator|AT_BITMAP
id|AT_BITMAP
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0xb0
)paren
comma
DECL|enumerator|AT_REPARSE_POINT
id|AT_REPARSE_POINT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0xc0
)paren
comma
DECL|enumerator|AT_EA_INFORMATION
id|AT_EA_INFORMATION
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0xd0
)paren
comma
DECL|enumerator|AT_EA
id|AT_EA
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0xe0
)paren
comma
DECL|enumerator|AT_PROPERTY_SET
id|AT_PROPERTY_SET
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0xf0
)paren
comma
DECL|enumerator|AT_LOGGED_UTILITY_STREAM
id|AT_LOGGED_UTILITY_STREAM
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x100
)paren
comma
DECL|enumerator|AT_FIRST_USER_DEFINED_ATTRIBUTE
id|AT_FIRST_USER_DEFINED_ATTRIBUTE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x1000
)paren
comma
DECL|enumerator|AT_END
id|AT_END
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0xffffffff
)paren
comma
DECL|typedef|ATTR_TYPES
)brace
id|ATTR_TYPES
suffix:semicolon
multiline_comment|/*&n; * The collation rules for sorting views/indexes/etc (32-bit).&n; *&n; * COLLATION_UNICODE_STRING - Collate Unicode strings by comparing their binary&n; *&t;Unicode values, except that when a character can be uppercased, the&n; *&t;upper case value collates before the lower case one.&n; * COLLATION_FILE_NAME - Collate file names as Unicode strings. The collation&n; *&t;is done very much like COLLATION_UNICODE_STRING. In fact I have no idea&n; *&t;what the difference is. Perhaps the difference is that file names&n; *&t;would treat some special characters in an odd way (see&n; *&t;unistr.c::ntfs_collate_names() and unistr.c::legal_ansi_char_array[]&n; *&t;for what I mean but COLLATION_UNICODE_STRING would not give any special&n; *&t;treatment to any characters at all, but this is speculation.&n; * COLLATION_NTOFS_ULONG - Sorting is done according to ascending u32 key&n; * &t;values. E.g. used for $SII index in FILE_Secure, which sorts by&n; * &t;security_id (u32).&n; * COLLATION_NTOFS_SID - Sorting is done according to ascending SID values.&n; * &t;E.g. used for $O index in FILE_Extend/$Quota.&n; * COLLATION_NTOFS_SECURITY_HASH - Sorting is done first by ascending hash&n; * &t;values and second by ascending security_id values. E.g. used for $SDH&n; * &t;index in FILE_Secure.&n; * COLLATION_NTOFS_ULONGS - Sorting is done according to a sequence of ascending&n; *&t;u32 key values. E.g. used for $O index in FILE_Extend/$ObjId, which&n; *&t;sorts by object_id (16-byte), by splitting up the object_id in four&n; *&t;u32 values and using them as individual keys. E.g. take the following&n; *&t;two security_ids, stored as follows on disk:&n; *&t;&t;1st: a1 61 65 b7 65 7b d4 11 9e 3d 00 e0 81 10 42 59&n; *&t;&t;2nd: 38 14 37 d2 d2 f3 d4 11 a5 21 c8 6b 79 b1 97 45&n; *&t;To compare them, they are split into four u32 values each, like so:&n; *&t;&t;1st: 0xb76561a1 0x11d47b65 0xe0003d9e 0x59421081&n; *&t;&t;2nd: 0xd2371438 0x11d4f3d2 0x6bc821a5 0x4597b179&n; *&t;Now, it is apparent why the 2nd object_id collates after the 1st: the&n; *&t;first u32 value of the 1st object_id is less than the first u32 of&n; *&t;the 2nd object_id. If the first u32 values of both object_ids were&n; *&t;equal then the second u32 values would be compared, etc.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|COLLATION_BINARY
id|COLLATION_BINARY
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0
)paren
comma
multiline_comment|/* Collate by binary&n;&t;&t;&t;&t;&t;compare where the first byte is most&n;&t;&t;&t;&t;&t;significant. */
DECL|enumerator|COLLATION_FILE_NAME
id|COLLATION_FILE_NAME
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* Collate file names&n;&t;&t;&t;&t;&t;as Unicode strings. */
DECL|enumerator|COLLATION_UNICODE_STRING
id|COLLATION_UNICODE_STRING
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|2
)paren
comma
multiline_comment|/* Collate Unicode&n;&t;&t;&t;&t;&t;strings by comparing their binary&n;&t;&t;&t;&t;&t;Unicode values, except that when a&n;&t;&t;&t;&t;&t;character can be uppercased, the upper&n;&t;&t;&t;&t;&t;case value collates before the lower&n;&t;&t;&t;&t;&t;case one. */
DECL|enumerator|COLLATION_NTOFS_ULONG
id|COLLATION_NTOFS_ULONG
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|16
)paren
comma
DECL|enumerator|COLLATION_NTOFS_SID
id|COLLATION_NTOFS_SID
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|17
)paren
comma
DECL|enumerator|COLLATION_NTOFS_SECURITY_HASH
id|COLLATION_NTOFS_SECURITY_HASH
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|18
)paren
comma
DECL|enumerator|COLLATION_NTOFS_ULONGS
id|COLLATION_NTOFS_ULONGS
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|19
)paren
comma
DECL|typedef|COLLATION_RULES
)brace
id|COLLATION_RULES
suffix:semicolon
multiline_comment|/*&n; * The flags (32-bit) describing attribute properties in the attribute&n; * definition structure. FIXME: This information is from Regis&squot;s information&n; * and, according to him, it is not certain and probably incomplete.&n; * The INDEXABLE flag is fairly certainly correct as only the file name&n; * attribute has this flag set and this is the only attribute indexed in NT4.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|INDEXABLE
id|INDEXABLE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x02
)paren
comma
multiline_comment|/* Attribute can be&n;&t;&t;&t;&t;&t;&t;&t;   indexed. */
DECL|enumerator|NEED_TO_REGENERATE
id|NEED_TO_REGENERATE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x40
)paren
comma
multiline_comment|/* Need to regenerate&n;&t;&t;&t;&t;&t;&t;&t;   during regeneration&n;&t;&t;&t;&t;&t;&t;&t;   phase. */
DECL|enumerator|CAN_BE_NON_RESIDENT
id|CAN_BE_NON_RESIDENT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x80
)paren
comma
multiline_comment|/* Attribute can be&n;&t;&t;&t;&t;&t;&t;&t;   non-resident. */
DECL|typedef|ATTR_DEF_FLAGS
)brace
id|ATTR_DEF_FLAGS
suffix:semicolon
multiline_comment|/*&n; * The data attribute of FILE_AttrDef contains a sequence of attribute&n; * definitions for the NTFS volume. With this, it is supposed to be safe for an&n; * older NTFS driver to mount a volume containing a newer NTFS version without&n; * damaging it (that&squot;s the theory. In practice it&squot;s: not damaging it too much).&n; * Entries are sorted by attribute type. The flags describe whether the&n; * attribute can be resident/non-resident and possibly other things, but the&n; * actual bits are unknown.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*hex ofs*/
DECL|member|name
multiline_comment|/*  0*/
id|uchar_t
id|name
(braket
l_int|0x40
)braket
suffix:semicolon
multiline_comment|/* Unicode name of the attribute. Zero&n;&t;&t;&t;&t;&t;   terminated. */
DECL|member|type
multiline_comment|/* 80*/
id|ATTR_TYPES
id|type
suffix:semicolon
multiline_comment|/* Type of the attribute. */
DECL|member|display_rule
multiline_comment|/* 84*/
id|u32
id|display_rule
suffix:semicolon
multiline_comment|/* Default display rule.&n;&t;&t;&t;&t;&t;   FIXME: What does it mean? (AIA) */
DECL|member|collation_rule
multiline_comment|/* 88*/
id|COLLATION_RULES
id|collation_rule
suffix:semicolon
multiline_comment|/* Default collation rule. */
DECL|member|flags
multiline_comment|/* 8c*/
id|ATTR_DEF_FLAGS
id|flags
suffix:semicolon
multiline_comment|/* Flags describing the attribute. */
DECL|member|min_size
multiline_comment|/* 90*/
id|u64
id|min_size
suffix:semicolon
multiline_comment|/* Optional minimum attribute size. */
DECL|member|max_size
multiline_comment|/* 98*/
id|u64
id|max_size
suffix:semicolon
multiline_comment|/* Maximum size of attribute. */
multiline_comment|/* sizeof() = 0xa0 or 160 bytes */
DECL|typedef|ATTR_DEF
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ATTR_DEF
suffix:semicolon
multiline_comment|/*&n; * Attribute flags (16-bit). &n; */
r_typedef
r_enum
(brace
DECL|enumerator|ATTR_IS_COMPRESSED
id|ATTR_IS_COMPRESSED
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0001
)paren
comma
DECL|enumerator|ATTR_COMPRESSION_MASK
id|ATTR_COMPRESSION_MASK
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x00ff
)paren
comma
multiline_comment|/* Compression&n;&t;&t;&t;&t;&t;&t;method mask. Also, first&n;&t;&t;&t;&t;&t;&t;illegal value. */
DECL|enumerator|ATTR_IS_ENCRYPTED
id|ATTR_IS_ENCRYPTED
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x4000
)paren
comma
DECL|enumerator|ATTR_IS_SPARSE
id|ATTR_IS_SPARSE
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x8000
)paren
comma
DECL|typedef|ATTR_FLAGS
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ATTR_FLAGS
suffix:semicolon
multiline_comment|/*&n; * Attribute compression.&n; *&n; * Only the data attribute is ever compressed in the current ntfs driver in&n; * Windows. Further, compression is only applied when the data attribute is&n; * non-resident. Finally, to use compression, the maximum allowed cluster size&n; * on a volume is 4kib.&n; *&n; * The compression method is based on independently compressing blocks of X&n; * clusters, where X is determined from the compression_unit value found in the&n; * non-resident attribute record header (more precisely: X = 2^compression_unit&n; * clusters). On Windows NT/2k, X always is 16 clusters (compression_unit = 4).&n; *&n; * There are three different cases of how a compression block of X clusters&n; * can be stored:&n; *&n; *   1) The data in the block is all zero (a sparse block):&n; *&t;  This is stored as a sparse block in the run list, i.e. the run list&n; *&t;  entry has length = X and lcn = -1. The mapping pairs array actually&n; *&t;  uses a delta_lcn value length of 0, i.e. delta_lcn is not present at&n; *&t;  all, which is then interpreted by the driver as lcn = -1.&n; *&t;  NOTE: Even uncompressed files can be sparse on NTFS 3.0 volumes, then&n; *&t;  the same principles apply as above, except that the length is not&n; *&t;  restricted to being any particular value.&n; *&n; *   2) The data in the block is not compressed:&n; *&t;  This happens when compression doesn&squot;t reduce the size of the block&n; *&t;  in clusters. I.e. if compression has a small effect so that the&n; *&t;  compressed data still occupies X clusters, then the uncompressed data&n; *&t;  is stored in the block.&n; *&t;  This case is recognised by the fact that the run list entry has&n; *&t;  length = X and lcn &gt;= 0. The mapping pairs array stores this as&n; *&t;  normal with a run length of X and some specific delta_lcn, i.e.&n; *&t;  delta_lcn has to be present.&n; *&n; *   3) The data in the block is compressed:&n; *&t;  The common case. This case is recognised by the fact that the run&n; *&t;  list entry has length L &lt; X and lcn &gt;= 0. The mapping pairs array&n; *&t;  stores this as normal with a run length of X and some specific&n; *&t;  delta_lcn, i.e. delta_lcn has to be present. This run list entry is&n; *&t;  immediately followed by a sparse entry with length = X - L and&n; *&t;  lcn = -1. The latter entry is to make up the vcn counting to the&n; *&t;  full compression block size X.&n; *&n; * In fact, life is more complicated because adjacent entries of the same type&n; * can be coalesced. This means that one has to keep track of the number of&n; * clusters handled and work on a basis of X clusters at a time being one&n; * block. An example: if length L &gt; X this means that this particular run list&n; * entry contains a block of length X and part of one or more blocks of length&n; * L - X. Another example: if length L &lt; X, this does not necessarily mean that&n; * the block is compressed as it might be that the lcn changes inside the block&n; * and hence the following run list entry describes the continuation of the&n; * potentially compressed block. The block would be compressed if the&n; * following run list entry describes at least X - L sparse clusters, thus&n; * making up the compression block length as described in point 3 above. (Of&n; * course, there can be several run list entries with small lengths so that the&n; * sparse entry does not follow the first data containing entry with&n; * length &lt; X.)&n; *&n; * NOTE: At the end of the compressed attribute value, there most likely is not&n; * just the right amount of data to make up a compression block, thus this data&n; * is not even attempted to be compressed. It is just stored as is, unless&n; * the number of clusters it occupies is reduced when compressed in which case&n; * it is stored as a compressed compression block, complete with sparse&n; * clusters at the end.&n; */
multiline_comment|/*&n; * Flags of resident attributes (8-bit).&n; */
r_typedef
r_enum
(brace
DECL|enumerator|RESIDENT_ATTR_IS_INDEXED
id|RESIDENT_ATTR_IS_INDEXED
op_assign
l_int|0x01
comma
multiline_comment|/* Attribute is referenced in an index&n;&t;&t;&t;&t;&t;    (has implications for deleting and&n;&t;&t;&t;&t;&t;    modifying the attribute). */
DECL|typedef|RESIDENT_ATTR_FLAGS
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|RESIDENT_ATTR_FLAGS
suffix:semicolon
multiline_comment|/*&n; * Attribute record header. Always aligned to 8-byte boundary.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*Ofs*/
DECL|member|type
multiline_comment|/*  0*/
id|ATTR_TYPES
id|type
suffix:semicolon
multiline_comment|/* The (32-bit) type of the attribute. */
DECL|member|length
multiline_comment|/*  4*/
id|u32
id|length
suffix:semicolon
multiline_comment|/* Byte size of the resident part of the&n;&t;&t;&t;&t;   attribute (aligned to 8-byte boundary).&n;&t;&t;&t;&t;   Used to get to the next attribute. */
DECL|member|non_resident
multiline_comment|/*  8*/
id|u8
id|non_resident
suffix:semicolon
multiline_comment|/* If 0, attribute is resident.&n;&t;&t;&t;&t;   If 1, attribute is non-resident. */
DECL|member|name_length
multiline_comment|/*  9*/
id|u8
id|name_length
suffix:semicolon
multiline_comment|/* Unicode character size of name of attribute.&n;&t;&t;&t;&t;   0 if unnamed. */
DECL|member|name_offset
multiline_comment|/* 10*/
id|u16
id|name_offset
suffix:semicolon
multiline_comment|/* If name_length != 0, the byte offset to the&n;&t;&t;&t;&t;   beginning of the name from the attribute&n;&t;&t;&t;&t;   record. Note that the name is stored as a&n;&t;&t;&t;&t;   Unicode string. When creating, place offset&n;&t;&t;&t;&t;   just at the end of the record header. Then,&n;&t;&t;&t;&t;   follow with attribute value or mapping pairs&n;&t;&t;&t;&t;   array, resident and non-resident attributes&n;&t;&t;&t;&t;   respectively, aligning to an 8-byte&n;&t;&t;&t;&t;   boundary. */
DECL|member|flags
multiline_comment|/* 12*/
id|ATTR_FLAGS
id|flags
suffix:semicolon
multiline_comment|/* Flags describing the attribute. */
DECL|member|instance
multiline_comment|/* 14*/
id|u16
id|instance
suffix:semicolon
multiline_comment|/* The instance of this attribute record. This&n;&t;&t;&t;&t;   number is unique within this mft record (see &n;&t;&t;&t;&t;   MFT_RECORD/next_attribute_instance notes in&n;&t;&t;&t;&t;   in mft.h for more details). */
multiline_comment|/* 16*/
r_union
(brace
multiline_comment|/* Resident attributes. */
r_struct
(brace
DECL|member|value_length
multiline_comment|/* 16 */
id|u32
id|value_length
suffix:semicolon
multiline_comment|/* Byte size of attribute value. */
DECL|member|value_offset
multiline_comment|/* 20 */
id|u16
id|value_offset
suffix:semicolon
multiline_comment|/* Byte offset of the attribute&n;&t;&t;&t;&t;&t;     value from the start of the&n;&t;&t;&t;&t;&t;     attribute record. When creating,&n;&t;&t;&t;&t;&t;     align to 8-byte boundary if we &n;&t;&t;&t;&t;&t;     have a name present as this might&n;&t;&t;&t;&t;&t;     not have a length of a multiple&n;&t;&t;&t;&t;&t;     of 8-bytes. */
DECL|member|resident_flags
multiline_comment|/* 22 */
id|RESIDENT_ATTR_FLAGS
id|resident_flags
suffix:semicolon
multiline_comment|/* See above. */
DECL|member|reservedR
multiline_comment|/* 23 */
id|s8
id|reservedR
suffix:semicolon
multiline_comment|/* Reserved/alignment to 8-byte&n;&t;&t;&t;&t;&t;     boundary. */
)brace
id|SN
c_func
(paren
id|ara
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/* Non-resident attributes. */
r_struct
(brace
DECL|member|lowest_vcn
multiline_comment|/* 16*/
id|VCN
id|lowest_vcn
suffix:semicolon
multiline_comment|/* Lowest valid virtual cluster number&n;&t;&t;&t;&t;for this portion of the attribute value or&n;&t;&t;&t;&t;0 if this is the only extent (usually the&n;&t;&t;&t;&t;case). - Only when an attribute list is used&n;&t;&t;&t;&t;does lowest_vcn != 0 ever occur. */
DECL|member|highest_vcn
multiline_comment|/* 24*/
id|VCN
id|highest_vcn
suffix:semicolon
multiline_comment|/* Highest valid vcn of this extent of&n;&t;&t;&t;&t;the attribute value. - Usually there is only one&n;&t;&t;&t;&t;portion, so this usually equals the attribute&n;&t;&t;&t;&t;value size in clusters minus 1. Can be -1 for&n;&t;&t;&t;&t;zero length files. Can be 0 for &quot;single extent&quot;&n;&t;&t;&t;&t;attributes. */
DECL|member|mapping_pairs_offset
multiline_comment|/* 32*/
id|u16
id|mapping_pairs_offset
suffix:semicolon
multiline_comment|/* Byte offset from the&n;&t;&t;&t;&t;beginning of the structure to the mapping pairs&n;&t;&t;&t;&t;array which contains the mappings between the&n;&t;&t;&t;&t;vcns and the logical cluster numbers (lcns).&n;&t;&t;&t;&t;When creating, place this at the end of this&n;&t;&t;&t;&t;record header aligned to 8-byte boundary. */
DECL|member|compression_unit
multiline_comment|/* 34*/
id|u8
id|compression_unit
suffix:semicolon
multiline_comment|/* The compression unit expressed&n;&t;&t;&t;&t;as the log to the base 2 of the number of&n;&t;&t;&t;&t;clusters in a compression unit. 0 means not&n;&t;&t;&t;&t;compressed. (This effectively limits the&n;&t;&t;&t;&t;compression unit size to be a power of two&n;&t;&t;&t;&t;clusters.) WinNT4 only uses a value of 4. */
DECL|member|reserved1
multiline_comment|/* 35*/
id|u8
id|reserved1
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Align to 8-byte boundary. */
multiline_comment|/* The sizes below are only used when lowest_vcn is zero, as otherwise it would&n;   be difficult to keep them up-to-date.*/
DECL|member|allocated_size
multiline_comment|/* 40*/
id|s64
id|allocated_size
suffix:semicolon
multiline_comment|/* Byte size of disk space&n;&t;&t;&t;&t;allocated to hold the attribute value. Always&n;&t;&t;&t;&t;is a multiple of the cluster size. When a file&n;&t;&t;&t;&t;is compressed, this field is a multiple of the&n;&t;&t;&t;&t;compression block size (2^compression_unit) and&n;&t;&t;&t;&t;it represents the logically allocated space&n;&t;&t;&t;&t;rather than the actual on disk usage. For this&n;&t;&t;&t;&t;use the compressed_size (see below). */
DECL|member|data_size
multiline_comment|/* 48*/
id|s64
id|data_size
suffix:semicolon
multiline_comment|/* Byte size of the attribute&n;&t;&t;&t;&t;value. Can be larger than allocated_size if&n;&t;&t;&t;&t;attribute value is compressed or sparse. */
DECL|member|initialized_size
multiline_comment|/* 56*/
id|s64
id|initialized_size
suffix:semicolon
multiline_comment|/* Byte size of initialized&n;&t;&t;&t;&t;portion of the attribute value. Usually equals&n;&t;&t;&t;&t;data_size. */
multiline_comment|/* sizeof(uncompressed attr) = 64*/
DECL|member|compressed_size
multiline_comment|/* 64*/
id|s64
id|compressed_size
suffix:semicolon
multiline_comment|/* Byte size of the attribute&n;&t;&t;&t;&t;value after compression. Only present when&n;&t;&t;&t;&t;compressed. Always is a multiple of the&n;&t;&t;&t;&t;cluster size. Represents the actual amount of&n;&t;&t;&t;&t;disk space being used on the disk. */
multiline_comment|/* sizeof(compressed attr) = 72*/
)brace
id|SN
c_func
(paren
id|anr
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
)brace
id|SN
c_func
(paren
id|aua
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|typedef|ATTR_RECORD
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ATTR_RECORD
suffix:semicolon
DECL|macro|_ARA
mdefine_line|#define _ARA(X)  SC(aua.ara,X)
DECL|macro|_ANR
mdefine_line|#define _ANR(X)  SC(aua.anr,X)
DECL|typedef|ATTR_REC
r_typedef
id|ATTR_RECORD
id|ATTR_REC
suffix:semicolon
multiline_comment|/*&n; * File attribute flags (32-bit).&n; */
r_typedef
r_enum
(brace
multiline_comment|/*&n;&t; * These flags are only present in the STANDARD_INFORMATION attribute&n;&t; * (in the field file_attributes).&n;&t; */
DECL|enumerator|FILE_ATTR_READONLY
id|FILE_ATTR_READONLY
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000001
)paren
comma
DECL|enumerator|FILE_ATTR_HIDDEN
id|FILE_ATTR_HIDDEN
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000002
)paren
comma
DECL|enumerator|FILE_ATTR_SYSTEM
id|FILE_ATTR_SYSTEM
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000004
)paren
comma
multiline_comment|/* Old DOS volid. Unused in NT.&t;= cpu_to_le32(0x00000008), */
DECL|enumerator|FILE_ATTR_DIRECTORY
id|FILE_ATTR_DIRECTORY
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000010
)paren
comma
multiline_comment|/* FILE_ATTR_DIRECTORY is not considered valid in NT. It is reserved&n;&t;   for the DOS SUBDIRECTORY flag. */
DECL|enumerator|FILE_ATTR_ARCHIVE
id|FILE_ATTR_ARCHIVE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000020
)paren
comma
DECL|enumerator|FILE_ATTR_DEVICE
id|FILE_ATTR_DEVICE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000040
)paren
comma
DECL|enumerator|FILE_ATTR_NORMAL
id|FILE_ATTR_NORMAL
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000080
)paren
comma
DECL|enumerator|FILE_ATTR_TEMPORARY
id|FILE_ATTR_TEMPORARY
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000100
)paren
comma
DECL|enumerator|FILE_ATTR_SPARSE_FILE
id|FILE_ATTR_SPARSE_FILE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000200
)paren
comma
DECL|enumerator|FILE_ATTR_REPARSE_POINT
id|FILE_ATTR_REPARSE_POINT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000400
)paren
comma
DECL|enumerator|FILE_ATTR_COMPRESSED
id|FILE_ATTR_COMPRESSED
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000800
)paren
comma
DECL|enumerator|FILE_ATTR_OFFLINE
id|FILE_ATTR_OFFLINE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00001000
)paren
comma
DECL|enumerator|FILE_ATTR_NOT_CONTENT_INDEXED
id|FILE_ATTR_NOT_CONTENT_INDEXED
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00002000
)paren
comma
DECL|enumerator|FILE_ATTR_ENCRYPTED
id|FILE_ATTR_ENCRYPTED
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00004000
)paren
comma
DECL|enumerator|FILE_ATTR_VALID_FLAGS
id|FILE_ATTR_VALID_FLAGS
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00007fb7
)paren
comma
multiline_comment|/* FILE_ATTR_VALID_FLAGS masks out the old DOS VolId and the &n;&t;   FILE_ATTR_DEVICE and preserves everything else. This mask&n;&t;   is used to obtain all flags that are valid for reading. */
DECL|enumerator|FILE_ATTR_VALID_SET_FLAGS
id|FILE_ATTR_VALID_SET_FLAGS
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x000031a7
)paren
comma
multiline_comment|/* FILE_ATTR_VALID_SET_FLAGS masks out the old DOS VolId, the&n;&t;   F_A_DEVICE, F_A_DIRECTORY, F_A_SPARSE_FILE, F_A_REPARSE_POINT,&n;&t;   F_A_COMPRESSED and F_A_ENCRYPTED and preserves the rest. This mask&n;&t;   is used to to obtain all flags that are valid for setting. */
multiline_comment|/*&n;&t; * These flags are only present in the FILE_NAME attribute (in the&n;&t; * field file_attributes).&n;&t; */
DECL|enumerator|FILE_ATTR_DUP_FILE_NAME_INDEX_PRESENT
id|FILE_ATTR_DUP_FILE_NAME_INDEX_PRESENT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x10000000
)paren
comma
multiline_comment|/* This is a copy of the corresponding bit from the mft record, telling&n;&t;   us whether this is a directory or not, i.e. whether it has an&n;&t;   index root attribute or not. */
DECL|enumerator|FILE_ATTR_DUP_VIEW_INDEX_PRESENT
id|FILE_ATTR_DUP_VIEW_INDEX_PRESENT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x20000000
)paren
comma
multiline_comment|/* This is a copy of the corresponding bit from the mft record, telling&n;&t;   us whether this file has a view index present (eg. object id index,&n;&t;   quota index, one of the security indexes or the encrypting file&n;&t;   system related indexes). */
DECL|typedef|FILE_ATTR_FLAGS
)brace
id|FILE_ATTR_FLAGS
suffix:semicolon
multiline_comment|/*&n; * NOTE on times in NTFS: All times are in MS standard time format, i.e. they&n; * are the number of 100-nanosecond intervals since 1st January 1601, 00:00:00&n; * universal coordinated time (UTC). (In Linux time starts 1st January 1970,&n; * 00:00:00 UTC and is stored as the number of 1-second intervals since then.)&n; */
multiline_comment|/*&n; * Attribute: Standard information (0x10).&n; *&n; * NOTE: Always resident.&n; * NOTE: Present in all base file records on a volume.&n; * NOTE: There is conflicting information about the meaning of each of the time&n; * &t; fields but the meaning as defined below has been verified to be&n; * &t; correct by practical experimentation on Windows NT4 SP6a and is hence&n; * &t; assumed to be the one and only correct interpretation.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*Ofs*/
DECL|member|creation_time
multiline_comment|/*  0*/
id|s64
id|creation_time
suffix:semicolon
multiline_comment|/* Time file was created. Updated when&n;&t;&t;&t;&t;&t;   a filename is changed(?). */
DECL|member|last_data_change_time
multiline_comment|/*  8*/
id|s64
id|last_data_change_time
suffix:semicolon
multiline_comment|/* Time the data attribute was last&n;&t;&t;&t;&t;&t;   modified. */
DECL|member|last_mft_change_time
multiline_comment|/* 16*/
id|s64
id|last_mft_change_time
suffix:semicolon
multiline_comment|/* Time this mft record was last&n;&t;&t;&t;&t;&t;   modified. */
DECL|member|last_access_time
multiline_comment|/* 24*/
id|s64
id|last_access_time
suffix:semicolon
multiline_comment|/* Approximate time when the file was&n;&t;&t;&t;&t;&t;   last accessed (obviously this is not&n;&t;&t;&t;&t;&t;   updated on read-only volumes). In&n;&t;&t;&t;&t;&t;   Windows this is only updated when&n;&t;&t;&t;&t;&t;   accessed if some time delta has&n;&t;&t;&t;&t;&t;   passed since the last update. Also,&n;&t;&t;&t;&t;&t;   last access times updates can be&n;&t;&t;&t;&t;&t;   disabled altogether for speed. */
DECL|member|file_attributes
multiline_comment|/* 32*/
id|FILE_ATTR_FLAGS
id|file_attributes
suffix:semicolon
multiline_comment|/* Flags describing the file. */
multiline_comment|/* 36*/
r_union
(brace
multiline_comment|/* NTFS 1.2 (and previous, presumably) */
DECL|member|reserved12
multiline_comment|/* 36 */
id|u8
id|reserved12
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* Reserved/alignment to 8-byte&n;&t;&t;&t;&t;&t;   boundary. */
multiline_comment|/* sizeof() = 48 bytes */
multiline_comment|/* NTFS 3.0 */
r_struct
(brace
multiline_comment|/*&n; * If a volume has been upgraded from a previous NTFS version, then these&n; * fields are present only if the file has been accessed since the upgrade.&n; * Recognize the difference by comparing the length of the resident attribute&n; * value. If it is 48, then the following fields are missing. If it is 72 then&n; * the fields are present. Maybe just check like this:&n; * &t;if (resident.ValueLength &lt; sizeof(STANDARD_INFORMATION)) {&n; * &t;&t;Assume NTFS 1.2- format.&n; * &t;&t;If (volume version is 3.0+)&n; * &t;&t;&t;Upgrade attribute to NTFS 3.0 format.&n; * &t;&t;else&n; * &t;&t;&t;Use NTFS 1.2- format for access.&n; * &t;} else&n; * &t;&t;Use NTFS 3.0 format for access.&n; * Only problem is that it might be legal to set the length of the value to&n; * arbitrarily large values thus spoiling this check. - But chkdsk probably&n; * views that as a corruption, assuming that it behaves like this for all&n; * attributes.&n; */
DECL|member|maximum_versions
multiline_comment|/* 36*/
id|u32
id|maximum_versions
suffix:semicolon
multiline_comment|/* Maximum allowed versions for&n;&t;&t;&t;&t;file. Zero if version numbering is disabled. */
DECL|member|version_number
multiline_comment|/* 40*/
id|u32
id|version_number
suffix:semicolon
multiline_comment|/* This file&squot;s version (if any).&n;&t;&t;&t;&t;Set to zero if maximum_versions is zero. */
DECL|member|class_id
multiline_comment|/* 44*/
id|u32
id|class_id
suffix:semicolon
multiline_comment|/* Class id from bidirectional&n;&t;&t;&t;&t;class id index (?). */
DECL|member|owner_id
multiline_comment|/* 48*/
id|u32
id|owner_id
suffix:semicolon
multiline_comment|/* Owner_id of the user owning&n;&t;&t;&t;&t;the file. Translate via $Q index in FILE_Extend&n;&t;&t;&t;&t;/$Quota to the quota control entry for the user&n;&t;&t;&t;&t;owning the file. Zero if quotas are disabled. */
DECL|member|security_id
multiline_comment|/* 52*/
id|u32
id|security_id
suffix:semicolon
multiline_comment|/* Security_id for the file.&n;&t;&t;&t;&t;Translate via $SII index and $SDS data stream&n;&t;&t;&t;&t;in FILE_Secure to the security descriptor. */
DECL|member|quota_charged
multiline_comment|/* 56*/
id|u64
id|quota_charged
suffix:semicolon
multiline_comment|/* Byte size of the charge to&n;&t;&t;&t;&t;the quota for all streams of the file. Note: Is&n;&t;&t;&t;&t;zero if quotas are disabled. */
DECL|member|usn
multiline_comment|/* 64*/
id|u64
id|usn
suffix:semicolon
multiline_comment|/* Last update sequence number&n;&t;&t;&t;&t;of the file. This is a direct index into the&n;&t;&t;&t;&t;change (aka usn) journal file. It is zero if&n;&t;&t;&t;&t;the usn journal is disabled.&n;&t;&t;&t;&t;NOTE: To disable the journal need to delete&n;&t;&t;&t;&t;the journal file itself and to then walk the&n;&t;&t;&t;&t;whole mft and set all Usn entries in all mft&n;&t;&t;&t;&t;records to zero! (This can take a while!)&n;&t;&t;&t;&t;The journal is FILE_Extend/$UsnJrnl. Win2k&n;&t;&t;&t;&t;will recreate the journal and initiate&n;&t;&t;&t;&t;logging if necessary when mounting the&n;&t;&t;&t;&t;partition. This, in contrast to disabling the&n;&t;&t;&t;&t;journal is a very fast process, so the user&n;&t;&t;&t;&t;won&squot;t even notice it. */
)brace
id|SN
c_func
(paren
id|svs
)paren
suffix:semicolon
)brace
id|SN
c_func
(paren
id|sei
)paren
suffix:semicolon
multiline_comment|/* sizeof() = 72 bytes (NTFS 3.0) */
DECL|typedef|STANDARD_INFORMATION
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|STANDARD_INFORMATION
suffix:semicolon
DECL|macro|_SVS
mdefine_line|#define _SVS(X)  SC(sei.svs,X)
multiline_comment|/*&n; * Attribute: Attribute list (0x20).&n; *&n; * - Can be either resident or non-resident.&n; * - Value consists of a sequence of variable length, 8-byte aligned,&n; * ATTR_LIST_ENTRY records.&n; * - The list is not terminated by anything at all! The only way to know when&n; * the end is reached is to keep track of the current offset and compare it to&n; * the attribute value size.&n; * - The attribute list attribute contains one entry for each attribute of&n; * the file in which the list is located, except for the list attribute&n; * itself. The list is sorted: first by attribute type, second by attribute&n; * name (if present), third by instance number. The extents of one&n; * non-resident attribute (if present) immediately follow after the initial&n; * extent. They are ordered by lowest_vcn and have their instace set to zero. &n; * It is not allowed to have two attributes with all sorting keys equal.&n; * - Further restrictions: &n; * &t;- If not resident, the vcn to lcn mapping array has to fit inside the&n; * &t;  base mft record.&n; * &t;- The attribute list attribute value has a maximum size of 256kb. This&n; * &t;  is imposed by the Windows cache manager.&n; * - Attribute lists are only used when the attributes of mft record do not&n; * fit inside the mft record despite all attributes (that can be made&n; * non-resident) having been made non-resident. This can happen e.g. when:&n; *  &t;- File has a large number of hard links (lots of file name&n; *  &t;  attributes present).&n; *  &t;- The mapping pairs array of some non-resident attribute becomes so&n; *&t;  large due to fragmentation that it overflows the mft record.&n; *  &t;- The security descriptor is very complex (not applicable to&n; *  &t;  NTFS 3.0 volumes).&n; *  &t;- There are many named streams.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*Ofs*/
DECL|member|type
multiline_comment|/*  0*/
id|ATTR_TYPES
id|type
suffix:semicolon
multiline_comment|/* Type of referenced attribute. */
DECL|member|length
multiline_comment|/*  4*/
id|u16
id|length
suffix:semicolon
multiline_comment|/* Byte size of this entry (8-byte aligned). */
DECL|member|name_length
multiline_comment|/*  6*/
id|u8
id|name_length
suffix:semicolon
multiline_comment|/* Size in Unicode chars of the name of the&n;&t;&t;&t;&t;   attribute or 0 if unnamed. */
DECL|member|name_offset
multiline_comment|/*  7*/
id|u8
id|name_offset
suffix:semicolon
multiline_comment|/* Byte offset to beginning of attribute name&n;&t;&t;&t;&t;   (always set this to where the name would&n;&t;&t;&t;&t;   start even if unnamed). */
DECL|member|lowest_vcn
multiline_comment|/*  8*/
id|VCN
id|lowest_vcn
suffix:semicolon
multiline_comment|/* Lowest virtual cluster number of this portion&n;&t;&t;&t;&t;   of the attribute value. This is usually 0. It&n;&t;&t;&t;&t;   is non-zero for the case where one attribute&n;&t;&t;&t;&t;   does not fit into one mft record and thus&n;&t;&t;&t;&t;   several mft records are allocated to hold&n;&t;&t;&t;&t;   this attribute. In the latter case, each mft&n;&t;&t;&t;&t;   record holds one extent of the attribute and&n;&t;&t;&t;&t;   there is one attribute list entry for each&n;&t;&t;&t;&t;   extent. NOTE: This is DEFINITELY a signed&n;&t;&t;&t;&t;   value! The windows driver uses cmp, followed&n;&t;&t;&t;&t;   by jg when comparing this, thus it treats it&n;&t;&t;&t;&t;   as signed. */
DECL|member|mft_reference
multiline_comment|/* 16*/
id|MFT_REF
id|mft_reference
suffix:semicolon
multiline_comment|/* The reference of the mft record holding&n;&t;&t;&t;&t;   the ATTR_RECORD for this portion of the&n;&t;&t;&t;&t;   attribute value. */
DECL|member|instance
multiline_comment|/* 24*/
id|u16
id|instance
suffix:semicolon
multiline_comment|/* If lowest_vcn = 0, the instance of the&n;&t;&t;&t;&t;   attribute being referenced; otherwise 0. */
DECL|member|name
multiline_comment|/* 26*/
id|uchar_t
id|name
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Use when creating only. When reading use&n;&t;&t;&t;&t;   name_offset to determine the location of the&n;&t;&t;&t;&t;   name. */
multiline_comment|/* sizeof() = 26 + (attribute_name_length * 2) bytes */
DECL|typedef|ATTR_LIST_ENTRY
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ATTR_LIST_ENTRY
suffix:semicolon
multiline_comment|/*&n; * The maximum allowed length for a file name.&n; */
DECL|macro|MAXIMUM_FILE_NAME_LENGTH
mdefine_line|#define MAXIMUM_FILE_NAME_LENGTH&t;255
multiline_comment|/*&n; * Possible namespaces for filenames in ntfs (8-bit).&n; */
r_typedef
r_enum
(brace
DECL|enumerator|FILE_NAME_POSIX
id|FILE_NAME_POSIX
op_assign
l_int|0x00
comma
multiline_comment|/* This is the largest namespace. It is case sensitive and &n;&t;&t;   allows all Unicode characters except for: &squot;&bslash;0&squot; and &squot;/&squot;.&n;&t;&t;   Beware that in WinNT/2k files which eg have the same name&n;&t;&t;   except for their case will not be distinguished by the&n;&t;&t;   standard utilities and thus a &quot;del filename&quot; will delete&n;&t;&t;   both &quot;filename&quot; and &quot;fileName&quot; without warning. */
DECL|enumerator|FILE_NAME_WIN32
id|FILE_NAME_WIN32
op_assign
l_int|0x01
comma
multiline_comment|/* The standard WinNT/2k NTFS long filenames. Case insensitive.&n;&t;&t;   All Unicode chars except: &squot;&bslash;0&squot;, &squot;&quot;&squot;, &squot;*&squot;, &squot;/&squot;, &squot;:&squot;, &squot;&lt;&squot;, &n;&t;&t;   &squot;&gt;&squot;, &squot;?&squot;, &squot;&bslash;&squot; and &squot;|&squot;. Further, names cannot end with a &squot;.&squot;&n;&t;&t;   or a space. */
DECL|enumerator|FILE_NAME_DOS
id|FILE_NAME_DOS
op_assign
l_int|0x02
comma
multiline_comment|/* The standard DOS filenames (8.3 format). Uppercase only.&n;&t;&t;   All 8-bit characters greater space, except: &squot;&quot;&squot;, &squot;*&squot;, &squot;+&squot;,&n;&t;&t;   &squot;,&squot;, &squot;/&squot;, &squot;:&squot;, &squot;;&squot;, &squot;&lt;&squot;, &squot;=&squot;, &squot;&gt;&squot;, &squot;?&squot; and &squot;&bslash;&squot;. */
DECL|enumerator|FILE_NAME_WIN32_AND_DOS
id|FILE_NAME_WIN32_AND_DOS
op_assign
l_int|0x03
comma
multiline_comment|/* 3 means that both the Win32 and the DOS filenames are&n;&t;&t;   identical and hence have been saved in this single filename&n;&t;&t;   record. */
DECL|typedef|FILE_NAME_TYPE_FLAGS
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|FILE_NAME_TYPE_FLAGS
suffix:semicolon
multiline_comment|/*&n; * Attribute: Filename (0x30).&n; *&n; * NOTE: Always resident.&n; * NOTE: All fields, except the parent_directory, are only updated when the&n; *&t; filename is changed. Until then, they just become out of sync with&n; *&t; reality and the more up to date values are present in the standard&n; *&t; information attribute.&n; * NOTE: There is conflicting information about the meaning of each of the time&n; * &t; fields but the meaning as defined below has been verified to be&n; * &t; correct by practical experimentation on Windows NT4 SP6a and is hence&n; * &t; assumed to be the one and only correct interpretation.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*hex ofs*/
DECL|member|parent_directory
multiline_comment|/*  0*/
id|MFT_REF
id|parent_directory
suffix:semicolon
multiline_comment|/* Directory this filename is&n;&t;&t;&t;&t;&t;   referenced from. */
DECL|member|creation_time
multiline_comment|/*  8*/
id|s64
id|creation_time
suffix:semicolon
multiline_comment|/* Time file was created. */
DECL|member|last_data_change_time
multiline_comment|/* 10*/
id|s64
id|last_data_change_time
suffix:semicolon
multiline_comment|/* Time the data attribute was last&n;&t;&t;&t;&t;&t;   modified. */
DECL|member|last_mft_change_time
multiline_comment|/* 18*/
id|s64
id|last_mft_change_time
suffix:semicolon
multiline_comment|/* Time this mft record was last&n;&t;&t;&t;&t;&t;   modified. */
DECL|member|last_access_time
multiline_comment|/* 20*/
id|s64
id|last_access_time
suffix:semicolon
multiline_comment|/* Last time this mft record was&n;&t;&t;&t;&t;&t;   accessed. */
DECL|member|allocated_size
multiline_comment|/* 28*/
id|s64
id|allocated_size
suffix:semicolon
multiline_comment|/* Byte size of allocated space for the&n;&t;&t;&t;&t;&t;   data attribute. NOTE: Is a multiple&n;&t;&t;&t;&t;&t;   of the cluster size. */
DECL|member|data_size
multiline_comment|/* 30*/
id|s64
id|data_size
suffix:semicolon
multiline_comment|/* Byte size of actual data in data&n;&t;&t;&t;&t;&t;   attribute. NOTE: Only present when&n;&t;&t;&t;&t;&t;   lowest_vcn is 0. */
DECL|member|file_attributes
multiline_comment|/* 38*/
id|FILE_ATTR_FLAGS
id|file_attributes
suffix:semicolon
multiline_comment|/* Flags describing the file. */
multiline_comment|/* 3c*/
r_union
(brace
multiline_comment|/* 3c*/
r_struct
(brace
DECL|member|packed_ea_size
multiline_comment|/* 3c*/
id|u16
id|packed_ea_size
suffix:semicolon
multiline_comment|/* Size of the buffer needed to&n;&t;&t;&t;&t;&t;&t;   pack the extended attributes&n;&t;&t;&t;&t;&t;&t;   (EAs), if such are present.*/
DECL|member|reserved
multiline_comment|/* 3e*/
id|u16
id|reserved
suffix:semicolon
multiline_comment|/* Reserved for alignment. */
)brace
id|SN
c_func
(paren
id|fea
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|member|reparse_point_tag
multiline_comment|/* 3c*/
id|u32
id|reparse_point_tag
suffix:semicolon
multiline_comment|/* Type of reparse point,&n;&t;&t;&t;&t;&t;&t;   present only in reparse&n;&t;&t;&t;&t;&t;&t;   points and only if there are&n;&t;&t;&t;&t;&t;&t;   no EAs. */
)brace
id|SN
c_func
(paren
id|fer
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|member|file_name_length
multiline_comment|/* 40*/
id|u8
id|file_name_length
suffix:semicolon
multiline_comment|/* Length of file name in&n;&t;&t;&t;&t;&t;&t;   (Unicode) characters. */
DECL|member|file_name_type
multiline_comment|/* 41*/
id|FILE_NAME_TYPE_FLAGS
id|file_name_type
suffix:semicolon
multiline_comment|/* Namespace of the file name.*/
DECL|member|file_name
multiline_comment|/* 42*/
id|uchar_t
id|file_name
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* File name in Unicode. */
DECL|typedef|FILE_NAME_ATTR
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|FILE_NAME_ATTR
suffix:semicolon
DECL|macro|_FEA
mdefine_line|#define _FEA(X)  SC(fer.fea,X)
DECL|macro|_FER
mdefine_line|#define _FER(X)  SC(fer,X)
multiline_comment|/*&n; * GUID structures store globally unique identifiers (GUID). A GUID is a &n; * 128-bit value consisting of one group of eight hexadecimal digits, followed&n; * by three groups of four hexadecimal digits each, followed by one group of&n; * twelve hexadecimal digits. GUIDs are Microsoft&squot;s implementation of the&n; * distributed computing environment (DCE) universally unique identifier (UUID).&n; * Example of a GUID:&n; * &t;1F010768-5A73-BC91-0010A52216A7&n; */
r_typedef
r_struct
(brace
DECL|member|data1
id|u32
id|data1
suffix:semicolon
multiline_comment|/* The first eight hexadecimal digits of the GUID. */
DECL|member|data2
id|u16
id|data2
suffix:semicolon
multiline_comment|/* The first group of four hexadecimal digits. */
DECL|member|data3
id|u16
id|data3
suffix:semicolon
multiline_comment|/* The second group of four hexadecimal digits. */
DECL|member|data4
id|u8
id|data4
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* The first two bytes are the third group of four&n;&t;&t;&t;   hexadecimal digits. The remaining six bytes are the&n;&t;&t;&t;   final 12 hexadecimal digits. */
DECL|typedef|GUID
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|GUID
suffix:semicolon
multiline_comment|/*&n; * FILE_Extend/$ObjId contains an index named $O. This index contains all&n; * object_ids present on the volume as the index keys and the corresponding&n; * mft_record numbers as the index entry data parts. The data part (defined&n; * below) also contains three other object_ids:&n; *&t;birth_volume_id - object_id of FILE_Volume on which the file was first&n; *&t;&t;&t;  created. Optional (i.e. can be zero).&n; *&t;birth_object_id - object_id of file when it was first created. Usually&n; *&t;&t;&t;  equals the object_id. Optional (i.e. can be zero).&n; *&t;domain_id&t;- Reserved (always zero).&n; */
r_typedef
r_struct
(brace
DECL|member|mft_reference
id|MFT_REF
id|mft_reference
suffix:semicolon
multiline_comment|/* Mft record containing the object_id in&n;&t;&t;&t;&t;   the index entry key. */
r_union
(brace
r_struct
(brace
DECL|member|birth_volume_id
id|GUID
id|birth_volume_id
suffix:semicolon
DECL|member|birth_object_id
id|GUID
id|birth_object_id
suffix:semicolon
DECL|member|domain_id
id|GUID
id|domain_id
suffix:semicolon
)brace
id|SN
c_func
(paren
id|obv
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|member|extended_info
id|u8
id|extended_info
(braket
l_int|48
)braket
suffix:semicolon
)brace
id|SN
c_func
(paren
id|oei
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|typedef|OBJ_ID_INDEX_DATA
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|OBJ_ID_INDEX_DATA
suffix:semicolon
multiline_comment|/*&n; * Attribute: Object id (NTFS 3.0+) (0x40).&n; *&n; * NOTE: Always resident.&n; */
r_typedef
r_struct
(brace
DECL|member|object_id
id|GUID
id|object_id
suffix:semicolon
multiline_comment|/* Unique id assigned to the&n;&t;&t;&t;&t;&t;&t;   file.*/
multiline_comment|/* The following fields are optional. The attribute value size is 16&n;&t;   bytes, i.e. sizeof(GUID), if these are not present at all. Note,&n;&t;   the entries can be present but one or more (or all) can be zero&n;&t;   meaning that that particular value(s) is(are) not defined. */
r_union
(brace
r_struct
(brace
DECL|member|birth_volume_id
id|GUID
id|birth_volume_id
suffix:semicolon
multiline_comment|/* Unique id of volume on which&n;&t;&t;&t;&t;&t;&t;   the file was first created.*/
DECL|member|birth_object_id
id|GUID
id|birth_object_id
suffix:semicolon
multiline_comment|/* Unique id of file when it was&n;&t;&t;&t;&t;&t;&t;   first created. */
DECL|member|domain_id
id|GUID
id|domain_id
suffix:semicolon
multiline_comment|/* Reserved, zero. */
)brace
id|SN
c_func
(paren
id|obv
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|member|extended_info
id|u8
id|extended_info
(braket
l_int|48
)braket
suffix:semicolon
)brace
id|SN
c_func
(paren
id|oei
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|typedef|OBJECT_ID_ATTR
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|OBJECT_ID_ATTR
suffix:semicolon
DECL|macro|_OBV
mdefine_line|#define _OBV(X)  SC(oei.obv,X)
multiline_comment|/*&n; * The pre-defined IDENTIFIER_AUTHORITIES used as SID_IDENTIFIER_AUTHORITY in&n; * the SID structure (see below).&n; */
singleline_comment|//typedef enum {&t;&t;&t;&t;&t;/* SID string prefix. */
singleline_comment|//&t;SECURITY_NULL_SID_AUTHORITY&t;= {0, 0, 0, 0, 0, 0},&t;/* S-1-0 */
singleline_comment|//&t;SECURITY_WORLD_SID_AUTHORITY&t;= {0, 0, 0, 0, 0, 1},&t;/* S-1-1 */
singleline_comment|//&t;SECURITY_LOCAL_SID_AUTHORITY &t;= {0, 0, 0, 0, 0, 2},&t;/* S-1-2 */
singleline_comment|//&t;SECURITY_CREATOR_SID_AUTHORITY&t;= {0, 0, 0, 0, 0, 3},&t;/* S-1-3 */
singleline_comment|//&t;SECURITY_NON_UNIQUE_AUTHORITY&t;= {0, 0, 0, 0, 0, 4},&t;/* S-1-4 */
singleline_comment|//&t;SECURITY_NT_SID_AUTHORITY&t;= {0, 0, 0, 0, 0, 5},&t;/* S-1-5 */
singleline_comment|//} IDENTIFIER_AUTHORITIES;
multiline_comment|/*&n; * These relative identifiers (RIDs) are used with the above identifier&n; * authorities to make up universal well-known SIDs.&n; * &t;&n; * Note: The relative identifier (RID) refers to the portion of a SID, which&n; * identifies a user or group in relation to the authority that issued the SID.&n; * For example, the universal well-known SID Creator Owner ID (S-1-3-0) is&n; * made up of the identifier authority SECURITY_CREATOR_SID_AUTHORITY (3) and&n; * the relative identifier SECURITY_CREATOR_OWNER_RID (0).&n; */
r_typedef
r_enum
(brace
multiline_comment|/* Identifier authority. */
DECL|enumerator|SECURITY_NULL_RID
id|SECURITY_NULL_RID
op_assign
l_int|0
comma
multiline_comment|/* S-1-0 */
DECL|enumerator|SECURITY_WORLD_RID
id|SECURITY_WORLD_RID
op_assign
l_int|0
comma
multiline_comment|/* S-1-1 */
DECL|enumerator|SECURITY_LOCAL_RID
id|SECURITY_LOCAL_RID
op_assign
l_int|0
comma
multiline_comment|/* S-1-2 */
DECL|enumerator|SECURITY_CREATOR_OWNER_RID
id|SECURITY_CREATOR_OWNER_RID
op_assign
l_int|0
comma
multiline_comment|/* S-1-3 */
DECL|enumerator|SECURITY_CREATOR_GROUP_RID
id|SECURITY_CREATOR_GROUP_RID
op_assign
l_int|1
comma
multiline_comment|/* S-1-3 */
DECL|enumerator|SECURITY_CREATOR_OWNER_SERVER_RID
id|SECURITY_CREATOR_OWNER_SERVER_RID
op_assign
l_int|2
comma
multiline_comment|/* S-1-3 */
DECL|enumerator|SECURITY_CREATOR_GROUP_SERVER_RID
id|SECURITY_CREATOR_GROUP_SERVER_RID
op_assign
l_int|3
comma
multiline_comment|/* S-1-3 */
DECL|enumerator|SECURITY_DIALUP_RID
id|SECURITY_DIALUP_RID
op_assign
l_int|1
comma
DECL|enumerator|SECURITY_NETWORK_RID
id|SECURITY_NETWORK_RID
op_assign
l_int|2
comma
DECL|enumerator|SECURITY_BATCH_RID
id|SECURITY_BATCH_RID
op_assign
l_int|3
comma
DECL|enumerator|SECURITY_INTERACTIVE_RID
id|SECURITY_INTERACTIVE_RID
op_assign
l_int|4
comma
DECL|enumerator|SECURITY_SERVICE_RID
id|SECURITY_SERVICE_RID
op_assign
l_int|6
comma
DECL|enumerator|SECURITY_ANONYMOUS_LOGON_RID
id|SECURITY_ANONYMOUS_LOGON_RID
op_assign
l_int|7
comma
DECL|enumerator|SECURITY_PROXY_RID
id|SECURITY_PROXY_RID
op_assign
l_int|8
comma
DECL|enumerator|SECURITY_ENTERPRISE_CONTROLLERS_RID
id|SECURITY_ENTERPRISE_CONTROLLERS_RID
op_assign
l_int|9
comma
DECL|enumerator|SECURITY_SERVER_LOGON_RID
id|SECURITY_SERVER_LOGON_RID
op_assign
l_int|9
comma
DECL|enumerator|SECURITY_PRINCIPAL_SELF_RID
id|SECURITY_PRINCIPAL_SELF_RID
op_assign
l_int|0xa
comma
DECL|enumerator|SECURITY_AUTHENTICATED_USER_RID
id|SECURITY_AUTHENTICATED_USER_RID
op_assign
l_int|0xb
comma
DECL|enumerator|SECURITY_RESTRICTED_CODE_RID
id|SECURITY_RESTRICTED_CODE_RID
op_assign
l_int|0xc
comma
DECL|enumerator|SECURITY_TERMINAL_SERVER_RID
id|SECURITY_TERMINAL_SERVER_RID
op_assign
l_int|0xd
comma
DECL|enumerator|SECURITY_LOGON_IDS_RID
id|SECURITY_LOGON_IDS_RID
op_assign
l_int|5
comma
DECL|enumerator|SECURITY_LOGON_IDS_RID_COUNT
id|SECURITY_LOGON_IDS_RID_COUNT
op_assign
l_int|3
comma
DECL|enumerator|SECURITY_LOCAL_SYSTEM_RID
id|SECURITY_LOCAL_SYSTEM_RID
op_assign
l_int|0x12
comma
DECL|enumerator|SECURITY_NT_NON_UNIQUE
id|SECURITY_NT_NON_UNIQUE
op_assign
l_int|0x15
comma
DECL|enumerator|SECURITY_BUILTIN_DOMAIN_RID
id|SECURITY_BUILTIN_DOMAIN_RID
op_assign
l_int|0x20
comma
multiline_comment|/*&n;&t; * Well-known domain relative sub-authority values (RIDs).&n;&t; */
multiline_comment|/* Users. */
DECL|enumerator|DOMAIN_USER_RID_ADMIN
id|DOMAIN_USER_RID_ADMIN
op_assign
l_int|0x1f4
comma
DECL|enumerator|DOMAIN_USER_RID_GUEST
id|DOMAIN_USER_RID_GUEST
op_assign
l_int|0x1f5
comma
DECL|enumerator|DOMAIN_USER_RID_KRBTGT
id|DOMAIN_USER_RID_KRBTGT
op_assign
l_int|0x1f6
comma
multiline_comment|/* Groups. */
DECL|enumerator|DOMAIN_GROUP_RID_ADMINS
id|DOMAIN_GROUP_RID_ADMINS
op_assign
l_int|0x200
comma
DECL|enumerator|DOMAIN_GROUP_RID_USERS
id|DOMAIN_GROUP_RID_USERS
op_assign
l_int|0x201
comma
DECL|enumerator|DOMAIN_GROUP_RID_GUESTS
id|DOMAIN_GROUP_RID_GUESTS
op_assign
l_int|0x202
comma
DECL|enumerator|DOMAIN_GROUP_RID_COMPUTERS
id|DOMAIN_GROUP_RID_COMPUTERS
op_assign
l_int|0x203
comma
DECL|enumerator|DOMAIN_GROUP_RID_CONTROLLERS
id|DOMAIN_GROUP_RID_CONTROLLERS
op_assign
l_int|0x204
comma
DECL|enumerator|DOMAIN_GROUP_RID_CERT_ADMINS
id|DOMAIN_GROUP_RID_CERT_ADMINS
op_assign
l_int|0x205
comma
DECL|enumerator|DOMAIN_GROUP_RID_SCHEMA_ADMINS
id|DOMAIN_GROUP_RID_SCHEMA_ADMINS
op_assign
l_int|0x206
comma
DECL|enumerator|DOMAIN_GROUP_RID_ENTERPRISE_ADMINS
id|DOMAIN_GROUP_RID_ENTERPRISE_ADMINS
op_assign
l_int|0x207
comma
DECL|enumerator|DOMAIN_GROUP_RID_POLICY_ADMINS
id|DOMAIN_GROUP_RID_POLICY_ADMINS
op_assign
l_int|0x208
comma
multiline_comment|/* Aliases. */
DECL|enumerator|DOMAIN_ALIAS_RID_ADMINS
id|DOMAIN_ALIAS_RID_ADMINS
op_assign
l_int|0x220
comma
DECL|enumerator|DOMAIN_ALIAS_RID_USERS
id|DOMAIN_ALIAS_RID_USERS
op_assign
l_int|0x221
comma
DECL|enumerator|DOMAIN_ALIAS_RID_GUESTS
id|DOMAIN_ALIAS_RID_GUESTS
op_assign
l_int|0x222
comma
DECL|enumerator|DOMAIN_ALIAS_RID_POWER_USERS
id|DOMAIN_ALIAS_RID_POWER_USERS
op_assign
l_int|0x223
comma
DECL|enumerator|DOMAIN_ALIAS_RID_ACCOUNT_OPS
id|DOMAIN_ALIAS_RID_ACCOUNT_OPS
op_assign
l_int|0x224
comma
DECL|enumerator|DOMAIN_ALIAS_RID_SYSTEM_OPS
id|DOMAIN_ALIAS_RID_SYSTEM_OPS
op_assign
l_int|0x225
comma
DECL|enumerator|DOMAIN_ALIAS_RID_PRINT_OPS
id|DOMAIN_ALIAS_RID_PRINT_OPS
op_assign
l_int|0x226
comma
DECL|enumerator|DOMAIN_ALIAS_RID_BACKUP_OPS
id|DOMAIN_ALIAS_RID_BACKUP_OPS
op_assign
l_int|0x227
comma
DECL|enumerator|DOMAIN_ALIAS_RID_REPLICATOR
id|DOMAIN_ALIAS_RID_REPLICATOR
op_assign
l_int|0x228
comma
DECL|enumerator|DOMAIN_ALIAS_RID_RAS_SERVERS
id|DOMAIN_ALIAS_RID_RAS_SERVERS
op_assign
l_int|0x229
comma
DECL|enumerator|DOMAIN_ALIAS_RID_PREW2KCOMPACCESS
id|DOMAIN_ALIAS_RID_PREW2KCOMPACCESS
op_assign
l_int|0x22a
comma
DECL|typedef|RELATIVE_IDENTIFIERS
)brace
id|RELATIVE_IDENTIFIERS
suffix:semicolon
multiline_comment|/*&n; * The universal well-known SIDs:&n; *&n; * &t;NULL_SID&t;&t;&t;S-1-0-0&n; * &t;WORLD_SID&t;&t;&t;S-1-1-0&n; * &t;LOCAL_SID&t;&t;&t;S-1-2-0&n; * &t;CREATOR_OWNER_SID&t;&t;S-1-3-0&n; * &t;CREATOR_GROUP_SID&t;&t;S-1-3-1&n; * &t;CREATOR_OWNER_SERVER_SID&t;S-1-3-2&n; * &t;CREATOR_GROUP_SERVER_SID&t;S-1-3-3&n; *&n; * &t;(Non-unique IDs)&t;&t;S-1-4&n; *&n; * NT well-known SIDs:&n; * &n; * &t;NT_AUTHORITY_SID&t;S-1-5&n; * &t;DIALUP_SID&t;&t;S-1-5-1&n; *&n; * &t;NETWORD_SID&t;&t;S-1-5-2&n; * &t;BATCH_SID&t;&t;S-1-5-3&n; * &t;INTERACTIVE_SID&t;&t;S-1-5-4&n; * &t;SERVICE_SID&t;&t;S-1-5-6&n; * &t;ANONYMOUS_LOGON_SID&t;S-1-5-7&t;&t;(aka null logon session)&n; * &t;PROXY_SID&t;&t;S-1-5-8&n; * &t;SERVER_LOGON_SID&t;S-1-5-9&t;&t;(aka domain controller account)&n; * &t;SELF_SID&t;&t;S-1-5-10&t;(self RID)&n; * &t;AUTHENTICATED_USER_SID&t;S-1-5-11&n; * &t;RESTRICTED_CODE_SID&t;S-1-5-12&t;(running restricted code)&n; * &t;TERMINAL_SERVER_SID&t;S-1-5-13&t;(running on terminal server)&n; *&n; * &t;(Logon IDs)&t;&t;S-1-5-5-X-Y&n; *&n; * &t;(NT non-unique IDs)&t;S-1-5-0x15-...&n; *&n; * &t;(Built-in domain)&t;S-1-5-0x20&n; */
multiline_comment|/*&n; * The SID_IDENTIFIER_AUTHORITY is a 48-bit value used in the SID structure.&n; */
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|low_part
id|u32
id|low_part
suffix:semicolon
multiline_comment|/* Low 32-bits. */
DECL|member|high_part
id|u16
id|high_part
suffix:semicolon
multiline_comment|/* High 16-bits. */
)brace
id|SN
c_func
(paren
id|sia
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|member|value
id|u8
id|value
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Value as individual bytes. */
DECL|typedef|SID_IDENTIFIER_AUTHORITY
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|SID_IDENTIFIER_AUTHORITY
suffix:semicolon
DECL|macro|_SIA
mdefine_line|#define _SIA(X)  SC(sia,X)
multiline_comment|/*&n; * The SID structure is a variable-length structure used to uniquely identify&n; * users or groups. SID stands for security identifier.&n; * &n; * The standard textual representation of the SID is of the form:&n; * &t;S-R-I-S-S...&n; * Where:&n; *    - The first &quot;S&quot; is the literal character &squot;S&squot; identifying the following&n; * &t;digits as a SID.&n; *    - R is the revision level of the SID expressed as a sequence of digits&n; *&t;either in decimal or hexadecimal (if the later, prefixed by &quot;0x&quot;).&n; *    - I is the 48-bit identifier_authority, expressed as digits as R above.&n; *    - S... is one or more sub_authority values, expressed as digits as above.&n; *    &n; * Example SID; the domain-relative SID of the local Administrators group on&n; * Windows NT/2k:&n; * &t;S-1-5-32-544&n; * This translates to a SID with:&n; * &t;revision = 1,&n; * &t;sub_authority_count = 2,&n; * &t;identifier_authority = {0,0,0,0,0,5},&t;// SECURITY_NT_AUTHORITY&n; * &t;sub_authority[0] = 32,&t;&t;&t;// SECURITY_BUILTIN_DOMAIN_RID&n; * &t;sub_authority[1] = 544&t;&t;&t;// DOMAIN_ALIAS_RID_ADMINS&n; */
r_typedef
r_struct
(brace
DECL|member|revision
id|u8
id|revision
suffix:semicolon
DECL|member|sub_authority_count
id|u8
id|sub_authority_count
suffix:semicolon
DECL|member|identifier_authority
id|SID_IDENTIFIER_AUTHORITY
id|identifier_authority
suffix:semicolon
DECL|member|sub_authority
id|u32
id|sub_authority
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* At least one sub_authority. */
DECL|typedef|SID
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|SID
suffix:semicolon
multiline_comment|/*&n; * Current constants for SIDs.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SID_REVISION
id|SID_REVISION
op_assign
l_int|1
comma
multiline_comment|/* Current revision level. */
DECL|enumerator|SID_MAX_SUB_AUTHORITIES
id|SID_MAX_SUB_AUTHORITIES
op_assign
l_int|15
comma
multiline_comment|/* Maximum number of those. */
DECL|enumerator|SID_RECOMMENDED_SUB_AUTHORITIES
id|SID_RECOMMENDED_SUB_AUTHORITIES
op_assign
l_int|1
comma
multiline_comment|/* Will change to around 6 in&n;&t;&t;&t;&t;&t;&t;   a future revision. */
DECL|typedef|SID_CONSTANTS
)brace
id|SID_CONSTANTS
suffix:semicolon
multiline_comment|/*&n; * The predefined ACE types (8-bit, see below).&n; */
r_typedef
r_enum
(brace
DECL|enumerator|ACCESS_MIN_MS_ACE_TYPE
id|ACCESS_MIN_MS_ACE_TYPE
op_assign
l_int|0
comma
DECL|enumerator|ACCESS_ALLOWED_ACE_TYPE
id|ACCESS_ALLOWED_ACE_TYPE
op_assign
l_int|0
comma
DECL|enumerator|ACCESS_DENIED_ACE_TYPE
id|ACCESS_DENIED_ACE_TYPE
op_assign
l_int|1
comma
DECL|enumerator|SYSTEM_AUDIT_ACE_TYPE
id|SYSTEM_AUDIT_ACE_TYPE
op_assign
l_int|2
comma
DECL|enumerator|SYSTEM_ALARM_ACE_TYPE
id|SYSTEM_ALARM_ACE_TYPE
op_assign
l_int|3
comma
multiline_comment|/* Not implemented as of Win2k. */
DECL|enumerator|ACCESS_MAX_MS_V2_ACE_TYPE
id|ACCESS_MAX_MS_V2_ACE_TYPE
op_assign
l_int|3
comma
DECL|enumerator|ACCESS_ALLOWED_COMPOUND_ACE_TYPE
id|ACCESS_ALLOWED_COMPOUND_ACE_TYPE
op_assign
l_int|4
comma
DECL|enumerator|ACCESS_MAX_MS_V3_ACE_TYPE
id|ACCESS_MAX_MS_V3_ACE_TYPE
op_assign
l_int|4
comma
multiline_comment|/* The following are Win2k only. */
DECL|enumerator|ACCESS_MIN_MS_OBJECT_ACE_TYPE
id|ACCESS_MIN_MS_OBJECT_ACE_TYPE
op_assign
l_int|5
comma
DECL|enumerator|ACCESS_ALLOWED_OBJECT_ACE_TYPE
id|ACCESS_ALLOWED_OBJECT_ACE_TYPE
op_assign
l_int|5
comma
DECL|enumerator|ACCESS_DENIED_OBJECT_ACE_TYPE
id|ACCESS_DENIED_OBJECT_ACE_TYPE
op_assign
l_int|6
comma
DECL|enumerator|SYSTEM_AUDIT_OBJECT_ACE_TYPE
id|SYSTEM_AUDIT_OBJECT_ACE_TYPE
op_assign
l_int|7
comma
DECL|enumerator|SYSTEM_ALARM_OBJECT_ACE_TYPE
id|SYSTEM_ALARM_OBJECT_ACE_TYPE
op_assign
l_int|8
comma
DECL|enumerator|ACCESS_MAX_MS_OBJECT_ACE_TYPE
id|ACCESS_MAX_MS_OBJECT_ACE_TYPE
op_assign
l_int|8
comma
DECL|enumerator|ACCESS_MAX_MS_V4_ACE_TYPE
id|ACCESS_MAX_MS_V4_ACE_TYPE
op_assign
l_int|8
comma
multiline_comment|/* This one is for WinNT&amp;2k. */
DECL|enumerator|ACCESS_MAX_MS_ACE_TYPE
id|ACCESS_MAX_MS_ACE_TYPE
op_assign
l_int|8
comma
DECL|typedef|ACE_TYPES
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ACE_TYPES
suffix:semicolon
multiline_comment|/*&n; * The ACE flags (8-bit) for audit and inheritance (see below).&n; *&n; * SUCCESSFUL_ACCESS_ACE_FLAG is only used with system audit and alarm ACE&n; * types to indicate that a message is generated (in Windows!) for successful&n; * accesses.&n; *&n; * FAILED_ACCESS_ACE_FLAG is only used with system audit and alarm ACE types&n; * to indicate that a message is generated (in Windows!) for failed accesses.&n; */
r_typedef
r_enum
(brace
multiline_comment|/* The inheritance flags. */
DECL|enumerator|OBJECT_INHERIT_ACE
id|OBJECT_INHERIT_ACE
op_assign
l_int|0x01
comma
DECL|enumerator|CONTAINER_INHERIT_ACE
id|CONTAINER_INHERIT_ACE
op_assign
l_int|0x02
comma
DECL|enumerator|NO_PROPAGATE_INHERIT_ACE
id|NO_PROPAGATE_INHERIT_ACE
op_assign
l_int|0x04
comma
DECL|enumerator|INHERIT_ONLY_ACE
id|INHERIT_ONLY_ACE
op_assign
l_int|0x08
comma
DECL|enumerator|INHERITED_ACE
id|INHERITED_ACE
op_assign
l_int|0x10
comma
multiline_comment|/* Win2k only. */
DECL|enumerator|VALID_INHERIT_FLAGS
id|VALID_INHERIT_FLAGS
op_assign
l_int|0x1f
comma
multiline_comment|/* The audit flags. */
DECL|enumerator|SUCCESSFUL_ACCESS_ACE_FLAG
id|SUCCESSFUL_ACCESS_ACE_FLAG
op_assign
l_int|0x40
comma
DECL|enumerator|FAILED_ACCESS_ACE_FLAG
id|FAILED_ACCESS_ACE_FLAG
op_assign
l_int|0x80
comma
DECL|typedef|ACE_FLAGS
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ACE_FLAGS
suffix:semicolon
multiline_comment|/*&n; * An ACE is an access-control entry in an access-control list (ACL).&n; * An ACE defines access to an object for a specific user or group or defines&n; * the types of access that generate system-administration messages or alarms&n; * for a specific user or group. The user or group is identified by a security&n; * identifier (SID).&n; *&n; * Each ACE starts with an ACE_HEADER structure (aligned on 4-byte boundary),&n; * which specifies the type and size of the ACE. The format of the subsequent&n; * data depends on the ACE type.&n; */
r_typedef
r_struct
(brace
DECL|member|type
id|ACE_TYPES
id|type
suffix:semicolon
multiline_comment|/* Type of the ACE. */
DECL|member|flags
id|ACE_FLAGS
id|flags
suffix:semicolon
multiline_comment|/* Flags describing the ACE. */
DECL|member|size
id|u16
id|size
suffix:semicolon
multiline_comment|/* Size in bytes of the ACE. */
DECL|typedef|ACE_HEADER
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ACE_HEADER
suffix:semicolon
multiline_comment|/*&n; * The access mask (32-bit). Defines the access rights.&n; */
r_typedef
r_enum
(brace
multiline_comment|/*&n;&t; * The specific rights (bits 0 to 15). Depend on the type of the&n;&t; * object being secured by the ACE.&n;&t; */
multiline_comment|/* Specific rights for files and directories are as follows: */
multiline_comment|/* Right to read data from the file. (FILE) */
DECL|enumerator|FILE_READ_DATA
id|FILE_READ_DATA
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000001
)paren
comma
multiline_comment|/* Right to list contents of a directory. (DIRECTORY) */
DECL|enumerator|FILE_LIST_DIRECTORY
id|FILE_LIST_DIRECTORY
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000001
)paren
comma
multiline_comment|/* Right to write data to the file. (FILE) */
DECL|enumerator|FILE_WRITE_DATA
id|FILE_WRITE_DATA
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000002
)paren
comma
multiline_comment|/* Right to create a file in the directory. (DIRECTORY) */
DECL|enumerator|FILE_ADD_FILE
id|FILE_ADD_FILE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000002
)paren
comma
multiline_comment|/* Right to append data to the file. (FILE) */
DECL|enumerator|FILE_APPEND_DATA
id|FILE_APPEND_DATA
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000004
)paren
comma
multiline_comment|/* Right to create a subdirectory. (DIRECTORY) */
DECL|enumerator|FILE_ADD_SUBDIRECTORY
id|FILE_ADD_SUBDIRECTORY
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000004
)paren
comma
multiline_comment|/* Right to read extended attributes. (FILE/DIRECTORY) */
DECL|enumerator|FILE_READ_EA
id|FILE_READ_EA
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000008
)paren
comma
multiline_comment|/* Right to write extended attributes. (FILE/DIRECTORY) */
DECL|enumerator|FILE_WRITE_EA
id|FILE_WRITE_EA
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000010
)paren
comma
multiline_comment|/* Right to execute a file. (FILE) */
DECL|enumerator|FILE_EXECUTE
id|FILE_EXECUTE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000020
)paren
comma
multiline_comment|/* Right to traverse the directory. (DIRECTORY) */
DECL|enumerator|FILE_TRAVERSE
id|FILE_TRAVERSE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000020
)paren
comma
multiline_comment|/*&n;&t; * Right to delete a directory and all the files it contains (its&n;&t; * children), even if the files are read-only. (DIRECTORY)&n;&t; */
DECL|enumerator|FILE_DELETE_CHILD
id|FILE_DELETE_CHILD
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000040
)paren
comma
multiline_comment|/* Right to read file attributes. (FILE/DIRECTORY) */
DECL|enumerator|FILE_READ_ATTRIBUTES
id|FILE_READ_ATTRIBUTES
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000080
)paren
comma
multiline_comment|/* Right to change file attributes. (FILE/DIRECTORY) */
DECL|enumerator|FILE_WRITE_ATTRIBUTES
id|FILE_WRITE_ATTRIBUTES
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000100
)paren
comma
multiline_comment|/*&n;&t; * The standard rights (bits 16 to 23). Are independent of the type of&n;&t; * object being secured.&n;&t; */
multiline_comment|/* Right to delete the object. */
DECL|enumerator|DELETE
id|DELETE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00010000
)paren
comma
multiline_comment|/*&n;&t; * Right to read the information in the object&squot;s security descriptor,&n;&t; * not including the information in the SACL. I.e. right to read the&n;&t; * security descriptor and owner.&n;&t; */
DECL|enumerator|READ_CONTROL
id|READ_CONTROL
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00020000
)paren
comma
multiline_comment|/* Right to modify the DACL in the object&squot;s security descriptor. */
DECL|enumerator|WRITE_DAC
id|WRITE_DAC
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00040000
)paren
comma
multiline_comment|/* Right to change the owner in the object&squot;s security descriptor. */
DECL|enumerator|WRITE_OWNER
id|WRITE_OWNER
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00080000
)paren
comma
multiline_comment|/*&n;&t; * Right to use the object for synchronization. Enables a process to&n;&t; * wait until the object is in the signalled state. Some object types&n;&t; * do not support this access right.&n;&t; */
DECL|enumerator|SYNCHRONIZE
id|SYNCHRONIZE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00100000
)paren
comma
multiline_comment|/*&n;&t; * The following STANDARD_RIGHTS_* are combinations of the above for&n;&t; * convenience and are defined by the Win32 API.&n;&t; */
multiline_comment|/* These are currently defined to READ_CONTROL. */
DECL|enumerator|STANDARD_RIGHTS_READ
id|STANDARD_RIGHTS_READ
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00020000
)paren
comma
DECL|enumerator|STANDARD_RIGHTS_WRITE
id|STANDARD_RIGHTS_WRITE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00020000
)paren
comma
DECL|enumerator|STANDARD_RIGHTS_EXECUTE
id|STANDARD_RIGHTS_EXECUTE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00020000
)paren
comma
multiline_comment|/* Combines DELETE, READ_CONTROL, WRITE_DAC, and WRITE_OWNER access. */
DECL|enumerator|STANDARD_RIGHTS_REQUIRED
id|STANDARD_RIGHTS_REQUIRED
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x000f0000
)paren
comma
multiline_comment|/*&n;&t; * Combines DELETE, READ_CONTROL, WRITE_DAC, WRITE_OWNER, and&n;&t; * SYNCHRONIZE access.&n;&t; */
DECL|enumerator|STANDARD_RIGHTS_ALL
id|STANDARD_RIGHTS_ALL
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x001f0000
)paren
comma
multiline_comment|/*&n;&t; * The access system ACL and maximum allowed access types (bits 24 to&n;&t; * 25, bits 26 to 27 are reserved).&n;&t; */
DECL|enumerator|ACCESS_SYSTEM_SECURITY
id|ACCESS_SYSTEM_SECURITY
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x01000000
)paren
comma
DECL|enumerator|MAXIMUM_ALLOWED
id|MAXIMUM_ALLOWED
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x02000000
)paren
comma
multiline_comment|/*&n;&t; * The generic rights (bits 28 to 31). These map onto the standard and&n;&t; * specific rights.&n;&t; */
multiline_comment|/* Read, write, and execute access. */
DECL|enumerator|GENERIC_ALL
id|GENERIC_ALL
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x10000000
)paren
comma
multiline_comment|/* Execute access. */
DECL|enumerator|GENERIC_EXECUTE
id|GENERIC_EXECUTE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x20000000
)paren
comma
multiline_comment|/*&n;&t; * Write access. For files, this maps onto:&n;&t; *&t;FILE_APPEND_DATA | FILE_WRITE_ATTRIBUTES | FILE_WRITE_DATA |&n;&t; *&t;FILE_WRITE_EA | STANDARD_RIGHTS_WRITE | SYNCHRONIZE&n;&t; * For directories, the mapping has the same numberical value. See&n;&t; * above for the descriptions of the rights granted.&n;&t; */
DECL|enumerator|GENERIC_WRITE
id|GENERIC_WRITE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x40000000
)paren
comma
multiline_comment|/*&n;&t; * Read access. For files, this maps onto:&n;&t; *&t;FILE_READ_ATTRIBUTES | FILE_READ_DATA | FILE_READ_EA |&n;&t; *&t;STANDARD_RIGHTS_READ | SYNCHRONIZE&n;&t; * For directories, the mapping has the same numberical value. See&n;&t; * above for the descriptions of the rights granted.&n;&t; */
DECL|enumerator|GENERIC_READ
id|GENERIC_READ
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x80000000
)paren
comma
DECL|typedef|ACCESS_MASK
)brace
id|ACCESS_MASK
suffix:semicolon
multiline_comment|/*&n; * The generic mapping array. Used to denote the mapping of each generic&n; * access right to a specific access mask.&n; * &n; * FIXME: What exactly is this and what is it for? (AIA)&n; */
r_typedef
r_struct
(brace
DECL|member|generic_read
id|ACCESS_MASK
id|generic_read
suffix:semicolon
DECL|member|generic_write
id|ACCESS_MASK
id|generic_write
suffix:semicolon
DECL|member|generic_execute
id|ACCESS_MASK
id|generic_execute
suffix:semicolon
DECL|member|generic_all
id|ACCESS_MASK
id|generic_all
suffix:semicolon
DECL|typedef|GENERIC_MAPPING
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|GENERIC_MAPPING
suffix:semicolon
multiline_comment|/*&n; * The predefined ACE type structures are as defined below.&n; */
multiline_comment|/*&n; * ACCESS_ALLOWED_ACE, ACCESS_DENIED_ACE, SYSTEM_AUDIT_ACE, SYSTEM_ALARM_ACE&n; */
r_typedef
r_struct
(brace
id|ACE_HEADER
id|SN
c_func
(paren
id|aah
)paren
suffix:semicolon
multiline_comment|/* The ACE header. */
DECL|member|mask
id|ACCESS_MASK
id|mask
suffix:semicolon
multiline_comment|/* Access mask associated with the ACE. */
DECL|member|sid
id|SID
id|sid
suffix:semicolon
multiline_comment|/* The SID associated with the ACE. */
DECL|typedef|ACCESS_ALLOWED_ACE
DECL|typedef|ACCESS_DENIED_ACE
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ACCESS_ALLOWED_ACE
comma
id|ACCESS_DENIED_ACE
comma
DECL|typedef|SYSTEM_AUDIT_ACE
DECL|typedef|SYSTEM_ALARM_ACE
id|SYSTEM_AUDIT_ACE
comma
id|SYSTEM_ALARM_ACE
suffix:semicolon
DECL|macro|_AAH
mdefine_line|#define _AAH(X)  SC(aah,X)
multiline_comment|/*&n; * The object ACE flags (32-bit).&n; */
r_typedef
r_enum
(brace
DECL|enumerator|ACE_OBJECT_TYPE_PRESENT
id|ACE_OBJECT_TYPE_PRESENT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|1
)paren
comma
DECL|enumerator|ACE_INHERITED_OBJECT_TYPE_PRESENT
id|ACE_INHERITED_OBJECT_TYPE_PRESENT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|2
)paren
comma
DECL|typedef|OBJECT_ACE_FLAGS
)brace
id|OBJECT_ACE_FLAGS
suffix:semicolon
r_typedef
r_struct
(brace
id|ACE_HEADER
id|SN
c_func
(paren
id|aah
)paren
suffix:semicolon
multiline_comment|/* The ACE_HEADER. */
DECL|member|mask
id|ACCESS_MASK
id|mask
suffix:semicolon
multiline_comment|/* Access mask associated with the ACE. */
DECL|member|flags
id|OBJECT_ACE_FLAGS
id|flags
suffix:semicolon
multiline_comment|/* Flags describing the object ACE. */
DECL|member|object_type
id|GUID
id|object_type
suffix:semicolon
DECL|member|inherited_object_type
id|GUID
id|inherited_object_type
suffix:semicolon
DECL|member|sid
id|SID
id|sid
suffix:semicolon
multiline_comment|/* The SID associated with the ACE. */
DECL|typedef|ACCESS_ALLOWED_OBJECT_ACE
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ACCESS_ALLOWED_OBJECT_ACE
comma
DECL|typedef|ACCESS_DENIED_OBJECT_ACE
id|ACCESS_DENIED_OBJECT_ACE
comma
DECL|typedef|SYSTEM_AUDIT_OBJECT_ACE
id|SYSTEM_AUDIT_OBJECT_ACE
comma
DECL|typedef|SYSTEM_ALARM_OBJECT_ACE
id|SYSTEM_ALARM_OBJECT_ACE
suffix:semicolon
multiline_comment|/*&n; * An ACL is an access-control list (ACL).&n; * An ACL starts with an ACL header structure, which specifies the size of&n; * the ACL and the number of ACEs it contains. The ACL header is followed by&n; * zero or more access control entries (ACEs). The ACL as well as each ACE&n; * are aligned on 4-byte boundaries.&n; */
r_typedef
r_struct
(brace
DECL|member|revision
id|u8
id|revision
suffix:semicolon
multiline_comment|/* Revision of this ACL. */
DECL|member|alignment1
id|u8
id|alignment1
suffix:semicolon
DECL|member|size
id|u16
id|size
suffix:semicolon
multiline_comment|/* Allocated space in bytes for ACL. Includes this&n;&t;&t;&t;   header, the ACEs and the remaining free space. */
DECL|member|ace_count
id|u16
id|ace_count
suffix:semicolon
multiline_comment|/* Number of ACEs in the ACL. */
DECL|member|alignment2
id|u16
id|alignment2
suffix:semicolon
multiline_comment|/* sizeof() = 8 bytes */
DECL|typedef|ACL
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ACL
suffix:semicolon
multiline_comment|/*&n; * Current constants for ACLs.&n; */
r_typedef
r_enum
(brace
multiline_comment|/* Current revision. */
DECL|enumerator|ACL_REVISION
id|ACL_REVISION
op_assign
l_int|2
comma
DECL|enumerator|ACL_REVISION_DS
id|ACL_REVISION_DS
op_assign
l_int|4
comma
multiline_comment|/* History of revisions. */
DECL|enumerator|ACL_REVISION1
id|ACL_REVISION1
op_assign
l_int|1
comma
DECL|enumerator|MIN_ACL_REVISION
id|MIN_ACL_REVISION
op_assign
l_int|2
comma
DECL|enumerator|ACL_REVISION2
id|ACL_REVISION2
op_assign
l_int|2
comma
DECL|enumerator|ACL_REVISION3
id|ACL_REVISION3
op_assign
l_int|3
comma
DECL|enumerator|ACL_REVISION4
id|ACL_REVISION4
op_assign
l_int|4
comma
DECL|enumerator|MAX_ACL_REVISION
id|MAX_ACL_REVISION
op_assign
l_int|4
comma
DECL|typedef|ACL_CONSTANTS
)brace
id|ACL_CONSTANTS
suffix:semicolon
multiline_comment|/*&n; * The security descriptor control flags (16-bit).&n; *&n; * SE_OWNER_DEFAULTED - This boolean flag, when set, indicates that the&n; *          SID pointed to by the Owner field was provided by a&n; *          defaulting mechanism rather than explicitly provided by the&n; *          original provider of the security descriptor.  This may&n; *          affect the treatment of the SID with respect to inheritence&n; *          of an owner.&n; *&n; * SE_GROUP_DEFAULTED - This boolean flag, when set, indicates that the&n; *          SID in the Group field was provided by a defaulting mechanism&n; *          rather than explicitly provided by the original provider of&n; *          the security descriptor.  This may affect the treatment of&n; *          the SID with respect to inheritence of a primary group.&n; *&n; * SE_DACL_PRESENT - This boolean flag, when set, indicates that the&n; *          security descriptor contains a discretionary ACL.  If this&n; *          flag is set and the Dacl field of the SECURITY_DESCRIPTOR is&n; *          null, then a null ACL is explicitly being specified.&n; *&n; * SE_DACL_DEFAULTED - This boolean flag, when set, indicates that the&n; *          ACL pointed to by the Dacl field was provided by a defaulting&n; *          mechanism rather than explicitly provided by the original&n; *          provider of the security descriptor.  This may affect the&n; *          treatment of the ACL with respect to inheritence of an ACL.&n; *          This flag is ignored if the DaclPresent flag is not set.&n; *&n; * SE_SACL_PRESENT - This boolean flag, when set,  indicates that the&n; *          security descriptor contains a system ACL pointed to by the&n; *          Sacl field.  If this flag is set and the Sacl field of the&n; *          SECURITY_DESCRIPTOR is null, then an empty (but present)&n; *          ACL is being specified.&n; *&n; * SE_SACL_DEFAULTED - This boolean flag, when set, indicates that the&n; *          ACL pointed to by the Sacl field was provided by a defaulting&n; *          mechanism rather than explicitly provided by the original&n; *          provider of the security descriptor.  This may affect the&n; *          treatment of the ACL with respect to inheritence of an ACL.&n; *          This flag is ignored if the SaclPresent flag is not set.&n; *&n; * SE_SELF_RELATIVE - This boolean flag, when set, indicates that the&n; *          security descriptor is in self-relative form.  In this form,&n; *          all fields of the security descriptor are contiguous in memory&n; *          and all pointer fields are expressed as offsets from the&n; *          beginning of the security descriptor.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SE_OWNER_DEFAULTED
id|SE_OWNER_DEFAULTED
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0001
)paren
comma
DECL|enumerator|SE_GROUP_DEFAULTED
id|SE_GROUP_DEFAULTED
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0002
)paren
comma
DECL|enumerator|SE_DACL_PRESENT
id|SE_DACL_PRESENT
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0004
)paren
comma
DECL|enumerator|SE_DACL_DEFAULTED
id|SE_DACL_DEFAULTED
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0008
)paren
comma
DECL|enumerator|SE_SACL_PRESENT
id|SE_SACL_PRESENT
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0010
)paren
comma
DECL|enumerator|SE_SACL_DEFAULTED
id|SE_SACL_DEFAULTED
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0020
)paren
comma
DECL|enumerator|SE_DACL_AUTO_INHERIT_REQ
id|SE_DACL_AUTO_INHERIT_REQ
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0100
)paren
comma
DECL|enumerator|SE_SACL_AUTO_INHERIT_REQ
id|SE_SACL_AUTO_INHERIT_REQ
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0200
)paren
comma
DECL|enumerator|SE_DACL_AUTO_INHERITED
id|SE_DACL_AUTO_INHERITED
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0400
)paren
comma
DECL|enumerator|SE_SACL_AUTO_INHERITED
id|SE_SACL_AUTO_INHERITED
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0800
)paren
comma
DECL|enumerator|SE_DACL_PROTECTED
id|SE_DACL_PROTECTED
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x1000
)paren
comma
DECL|enumerator|SE_SACL_PROTECTED
id|SE_SACL_PROTECTED
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x2000
)paren
comma
DECL|enumerator|SE_RM_CONTROL_VALID
id|SE_RM_CONTROL_VALID
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x4000
)paren
comma
DECL|enumerator|SE_SELF_RELATIVE
id|SE_SELF_RELATIVE
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x8000
)paren
comma
DECL|typedef|SECURITY_DESCRIPTOR_CONTROL
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|SECURITY_DESCRIPTOR_CONTROL
suffix:semicolon
multiline_comment|/*&n; * Self-relative security descriptor. Contains the owner and group SIDs as well&n; * as the sacl and dacl ACLs inside the security descriptor itself.&n; */
r_typedef
r_struct
(brace
DECL|member|revision
id|u8
id|revision
suffix:semicolon
multiline_comment|/* Revision level of the security descriptor. */
DECL|member|alignment
id|u8
id|alignment
suffix:semicolon
DECL|member|control
id|SECURITY_DESCRIPTOR_CONTROL
id|control
suffix:semicolon
multiline_comment|/* Flags qualifying the type of&n;&t;&t;&t;   the descriptor as well as the following fields. */
DECL|member|owner
id|u32
id|owner
suffix:semicolon
multiline_comment|/* Byte offset to a SID representing an object&squot;s&n;&t;&t;&t;   owner. If this is NULL, no owner SID is present in&n;&t;&t;&t;   the descriptor. */
DECL|member|group
id|u32
id|group
suffix:semicolon
multiline_comment|/* Byte offset to a SID representing an object&squot;s&n;&t;&t;&t;   primary group. If this is NULL, no primary group&n;&t;&t;&t;   SID is present in the descriptor. */
DECL|member|sacl
id|u32
id|sacl
suffix:semicolon
multiline_comment|/* Byte offset to a system ACL. Only valid, if&n;&t;&t;&t;   SE_SACL_PRESENT is set in the control field. If&n;&t;&t;&t;   SE_SACL_PRESENT is set but sacl is NULL, a NULL ACL&n;&t;&t;&t;   is specified. */
DECL|member|dacl
id|u32
id|dacl
suffix:semicolon
multiline_comment|/* Byte offset to a discretionary ACL. Only valid, if &n;&t;&t;&t;   SE_DACL_PRESENT is set in the control field. If&n;&t;&t;&t;   SE_DACL_PRESENT is set but dacl is NULL, a NULL ACL&n;&t;&t;&t;   (unconditionally granting access) is specified. */
multiline_comment|/* sizeof() = 0x14 bytes */
DECL|typedef|SECURITY_DESCRIPTOR_RELATIVE
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|SECURITY_DESCRIPTOR_RELATIVE
suffix:semicolon
multiline_comment|/*&n; * Absolute security descriptor. Does not contain the owner and group SIDs, nor&n; * the sacl and dacl ACLs inside the security descriptor. Instead, it contains&n; * pointers to these structures in memory. Obviously, absolute security&n; * descriptors are only useful for in memory representations of security&n; * descriptors. On disk, a self-relative security descriptor is used.&n; */
r_typedef
r_struct
(brace
DECL|member|revision
id|u8
id|revision
suffix:semicolon
multiline_comment|/* Revision level of the security descriptor. */
DECL|member|alignment
id|u8
id|alignment
suffix:semicolon
DECL|member|control
id|SECURITY_DESCRIPTOR_CONTROL
id|control
suffix:semicolon
multiline_comment|/* Flags qualifying the type of &n;&t;&t;&t;   the descriptor as well as the following fields. */
DECL|member|owner
id|SID
op_star
id|owner
suffix:semicolon
multiline_comment|/* Points to a SID representing an object&squot;s owner. If&n;&t;&t;&t;   this is NULL, no owner SID is present in the&n;&t;&t;&t;   descriptor. */
DECL|member|group
id|SID
op_star
id|group
suffix:semicolon
multiline_comment|/* Points to a SID representing an object&squot;s primary&n;&t;&t;&t;   group. If this is NULL, no primary group SID is&n;&t;&t;&t;   present in the descriptor. */
DECL|member|sacl
id|ACL
op_star
id|sacl
suffix:semicolon
multiline_comment|/* Points to a system ACL. Only valid, if&n;&t;&t;&t;   SE_SACL_PRESENT is set in the control field. If&n;&t;&t;&t;   SE_SACL_PRESENT is set but sacl is NULL, a NULL ACL&n;&t;&t;&t;   is specified. */
DECL|member|dacl
id|ACL
op_star
id|dacl
suffix:semicolon
multiline_comment|/* Points to a discretionary ACL. Only valid, if &n;&t;&t;&t;   SE_DACL_PRESENT is set in the control field. If&n;&t;&t;&t;   SE_DACL_PRESENT is set but dacl is NULL, a NULL ACL&n;&t;&t;&t;   (unconditionally granting access) is specified. */
DECL|typedef|SECURITY_DESCRIPTOR
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|SECURITY_DESCRIPTOR
suffix:semicolon
multiline_comment|/*&n; * Current constants for security descriptors.&n; */
r_typedef
r_enum
(brace
multiline_comment|/* Current revision. */
DECL|enumerator|SECURITY_DESCRIPTOR_REVISION
id|SECURITY_DESCRIPTOR_REVISION
op_assign
l_int|1
comma
DECL|enumerator|SECURITY_DESCRIPTOR_REVISION1
id|SECURITY_DESCRIPTOR_REVISION1
op_assign
l_int|1
comma
multiline_comment|/* The sizes of both the absolute and relative security descriptors is&n;&t;   the same as pointers, at least on ia32 architecture are 32-bit. */
DECL|enumerator|SECURITY_DESCRIPTOR_MIN_LENGTH
id|SECURITY_DESCRIPTOR_MIN_LENGTH
op_assign
r_sizeof
(paren
id|SECURITY_DESCRIPTOR
)paren
comma
DECL|typedef|SECURITY_DESCRIPTOR_CONSTANTS
)brace
id|SECURITY_DESCRIPTOR_CONSTANTS
suffix:semicolon
multiline_comment|/*&n; * Attribute: Security descriptor (0x50). A standard self-relative security&n; * descriptor.&n; *&n; * NOTE: Can be resident or non-resident.&n; * NOTE: Not used in NTFS 3.0+, as security descriptors are stored centrally&n; * in FILE_Secure and the correct descriptor is found using the security_id&n; * from the standard information attribute.&n; */
DECL|typedef|SECURITY_DESCRIPTOR_ATTR
r_typedef
id|SECURITY_DESCRIPTOR_RELATIVE
id|SECURITY_DESCRIPTOR_ATTR
suffix:semicolon
multiline_comment|/*&n; * On NTFS 3.0+, all security descriptors are stored in FILE_Secure. Only one&n; * referenced instance of each unique security descriptor is stored.&n; * &n; * FILE_Secure contains no unnamed data attribute, i.e. it has zero length. It&n; * does, however, contain two indexes ($SDH and $SII) as well as a named data&n; * stream ($SDS).&n; * &n; * Every unique security descriptor is assigned a unique security identifier&n; * (security_id, not to be confused with a SID). The security_id is unique for&n; * the NTFS volume and is used as an index into the $SII index, which maps&n; * security_ids to the security descriptor&squot;s storage location within the $SDS&n; * data attribute. The $SII index is sorted by ascending security_id.&n; *&n; * A simple hash is computed from each security descriptor. This hash is used&n; * as an index into the $SDH index, which maps security descriptor hashes to&n; * the security descriptor&squot;s storage location within the $SDS data attribute.&n; * The $SDH index is sorted by security descriptor hash and is stored in a B+&n; * tree. When searching $SDH (with the intent of determining whether or not a&n; * new security descriptor is already present in the $SDS data stream), if a&n; * matching hash is found, but the security descriptors do not match, the&n; * search in the $SDH index is continued, searching for a next matching hash.&n; * &n; * When a precise match is found, the security_id coresponding to the security&n; * descriptor in the $SDS attribute is read from the found $SDH index entry and&n; * is stored in the $STANDARD_INFORMATION attribute of the file/directory to&n; * which the security descriptor is being applied. The $STANDARD_INFORMATION&n; * attribute is present in all base mft records (i.e. in all files and &n; * directories).&n; *&n; * If a match is not found, the security descriptor is assigned a new unique&n; * security_id and is added to the $SDS data attribute. Then, entries&n; * referencing the this security descriptor in the $SDS data attribute are&n; * added to the $SDH and $SII indexes.&n; *&n; * Note: Entries are never deleted from FILE_Secure, even if nothing&n; * references an entry any more.&n; */
multiline_comment|/*&n; * This header precedes each security descriptor in the $SDS data stream.&n; * This is also the index entry data part of both the $SII and $SDH indexes.&n; */
r_typedef
r_struct
(brace
DECL|member|hash
id|u32
id|hash
suffix:semicolon
multiline_comment|/* Hash of the security descriptor. */
DECL|member|security_id
id|u32
id|security_id
suffix:semicolon
multiline_comment|/* The security_id assigned to the descriptor. */
DECL|member|offset
id|u64
id|offset
suffix:semicolon
multiline_comment|/* Byte offset of this entry in the $SDS stream. */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* Size in bytes of this entry in $SDS stream. */
DECL|typedef|SECURITY_DESCRIPTOR_HEADER
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|SECURITY_DESCRIPTOR_HEADER
suffix:semicolon
multiline_comment|/*&n; * The $SDS data stream contains the security descriptors, aligned on 16-byte&n; * boundaries, sorted by security_id in a B+ tree. Security descriptors cannot&n; * cross 256kib boundaries (this restriction is imposed by the Windows cache&n; * manager). Each security descriptor is contained in a SDS_ENTRY structure.&n; * Also, each security descriptor is stored twice in the $SDS stream with a&n; * fixed offset of 0x40000 bytes (256kib, the Windows cache manager&squot;s max size)&n; * between them; i.e. if a SDS_ENTRY specifies an offset of 0x51d0, then the&n; * the first copy of the security descriptor will be at offset 0x51d0 in the&n; * $SDS data stream and the second copy will be at offset 0x451d0.&n; */
r_typedef
r_struct
(brace
id|SECURITY_DESCRIPTOR_HEADER
id|SN
c_func
(paren
id|sdh
)paren
suffix:semicolon
multiline_comment|/* The security descriptor header. */
DECL|member|sid
id|SECURITY_DESCRIPTOR_RELATIVE
id|sid
suffix:semicolon
multiline_comment|/* The self-relative security&n;&t;&t;&t;&t;&t;     descriptor. */
DECL|typedef|SDS_ENTRY
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|SDS_ENTRY
suffix:semicolon
DECL|macro|_SDH
mdefine_line|#define _SDH(X)  SC(sdh,X)
multiline_comment|/*&n; * The index entry key used in the $SII index. The collation type is&n; * COLLATION_NTOFS_ULONG. &n; */
r_typedef
r_struct
(brace
DECL|member|security_id
id|u32
id|security_id
suffix:semicolon
multiline_comment|/* The security_id assigned to the descriptor. */
DECL|typedef|SII_INDEX_KEY
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|SII_INDEX_KEY
suffix:semicolon
multiline_comment|/*&n; * The index entry key used in the $SDH index. The keys are sorted first by&n; * hash and then by security_id. The collation rule is&n; * COLLATION_NTOFS_SECURITY_HASH.&n; */
r_typedef
r_struct
(brace
DECL|member|hash
id|u32
id|hash
suffix:semicolon
multiline_comment|/* Hash of the security descriptor. */
DECL|member|security_id
id|u32
id|security_id
suffix:semicolon
multiline_comment|/* The security_id assigned to the descriptor. */
DECL|typedef|SDH_INDEX_KEY
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|SDH_INDEX_KEY
suffix:semicolon
multiline_comment|/*&n; * Attribute: Volume name (0x60).&n; * &n; * NOTE: Always resident.&n; * NOTE: Present only in FILE_Volume.&n; */
r_typedef
r_struct
(brace
DECL|member|name
id|uchar_t
id|name
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* The name of the volume in Unicode. */
DECL|typedef|VOLUME_NAME
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|VOLUME_NAME
suffix:semicolon
multiline_comment|/*&n; * Possible flags for the volume (16-bit).&n; */
r_typedef
r_enum
(brace
DECL|enumerator|VOLUME_IS_DIRTY
id|VOLUME_IS_DIRTY
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0001
)paren
comma
DECL|enumerator|VOLUME_RESIZE_LOG_FILE
id|VOLUME_RESIZE_LOG_FILE
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0002
)paren
comma
DECL|enumerator|VOLUME_UPGRADE_ON_MOUNT
id|VOLUME_UPGRADE_ON_MOUNT
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0004
)paren
comma
DECL|enumerator|VOLUME_MOUNTED_ON_NT4
id|VOLUME_MOUNTED_ON_NT4
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0008
)paren
comma
DECL|enumerator|VOLUME_DELETE_USN_UNDERWAY
id|VOLUME_DELETE_USN_UNDERWAY
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0010
)paren
comma
DECL|enumerator|VOLUME_REPAIR_OBJECT_ID
id|VOLUME_REPAIR_OBJECT_ID
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x0020
)paren
comma
DECL|enumerator|VOLUME_MODIFIED_BY_CHKDSK
id|VOLUME_MODIFIED_BY_CHKDSK
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x8000
)paren
comma
DECL|enumerator|VOLUME_FLAGS_MASK
id|VOLUME_FLAGS_MASK
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|0x803f
)paren
comma
DECL|typedef|VOLUME_FLAGS
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|VOLUME_FLAGS
suffix:semicolon
multiline_comment|/*&n; * Attribute: Volume information (0x70).&n; *&n; * NOTE: Always resident.&n; * NOTE: Present only in FILE_Volume.&n; * NOTE: Windows 2000 uses NTFS 3.0 while Windows NT4 service pack 6a uses&n; * &t; NTFS 1.2. I haven&squot;t personally seen other values yet.&n; */
r_typedef
r_struct
(brace
DECL|member|reserved
id|u64
id|reserved
suffix:semicolon
multiline_comment|/* Not used (yet?). */
DECL|member|major_ver
id|u8
id|major_ver
suffix:semicolon
multiline_comment|/* Major version of the ntfs format. */
DECL|member|minor_ver
id|u8
id|minor_ver
suffix:semicolon
multiline_comment|/* Minor version of the ntfs format. */
DECL|member|flags
id|VOLUME_FLAGS
id|flags
suffix:semicolon
multiline_comment|/* Bit array of VOLUME_* flags. */
DECL|typedef|VOLUME_INFORMATION
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|VOLUME_INFORMATION
suffix:semicolon
multiline_comment|/*&n; * Attribute: Data attribute (0x80).&n; *&n; * NOTE: Can be resident or non-resident.&n; *&n; * Data contents of a file (i.e. the unnamed stream) or of a named stream.&n; */
r_typedef
r_struct
(brace
DECL|member|data
id|u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* The file&squot;s data contents. */
DECL|typedef|DATA_ATTR
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|DATA_ATTR
suffix:semicolon
multiline_comment|/*&n; * Index header flags (8-bit).&n; */
r_typedef
r_enum
(brace
multiline_comment|/* When index header is in an index root attribute: */
DECL|enumerator|SMALL_INDEX
id|SMALL_INDEX
op_assign
l_int|0
comma
multiline_comment|/* The index is small enough to fit inside the&n;&t;&t;&t;&t;index root attribute and there is no index&n;&t;&t;&t;&t;allocation attribute present. */
DECL|enumerator|LARGE_INDEX
id|LARGE_INDEX
op_assign
l_int|1
comma
multiline_comment|/* The index is too large to fit in the index&n;&t;&t;&t;&t;root attribute and/or an index allocation&n;&t;&t;&t;&t;attribute is present. */
multiline_comment|/*&n;&t; * When index header is in an index block, i.e. is part of index&n;&t; * allocation attribute:&n;&t; */
DECL|enumerator|LEAF_NODE
id|LEAF_NODE
op_assign
l_int|0
comma
multiline_comment|/* This is a leaf node, i.e. there are no more&n;&t;&t;&t;        nodes branching off it. */
DECL|enumerator|INDEX_NODE
id|INDEX_NODE
op_assign
l_int|1
comma
multiline_comment|/* This node indexes other nodes, i.e. is not a&n;&t;&t;&t;&t;leaf node. */
DECL|enumerator|NODE_MASK
id|NODE_MASK
op_assign
l_int|1
comma
multiline_comment|/* Mask for accessing the *_NODE bits. */
DECL|typedef|INDEX_HEADER_FLAGS
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|INDEX_HEADER_FLAGS
suffix:semicolon
multiline_comment|/*&n; * This is the header for indexes, describing the INDEX_ENTRY records, which&n; * follow the INDEX_HEADER. Together the index header and the index entries&n; * make up a complete index.&n; *&n; * IMPORTANT NOTE: The offset, length and size structure members are counted&n; * relative to the start of the index header structure and not relative to the&n; * start of the index root or index allocation structures themselves.&n; */
r_typedef
r_struct
(brace
DECL|member|entries_offset
id|u32
id|entries_offset
suffix:semicolon
multiline_comment|/* Byte offset to first INDEX_ENTRY&n;&t;&t;&t;&t;&t;   aligned to 8-byte boundary. */
DECL|member|index_length
id|u32
id|index_length
suffix:semicolon
multiline_comment|/* Data size of the index in bytes,&n;&t;&t;&t;&t;&t;   i.e. bytes used from allocated&n;&t;&t;&t;&t;&t;   size, aligned to 8-byte boundary. */
DECL|member|allocated_size
id|u32
id|allocated_size
suffix:semicolon
multiline_comment|/* Byte size of this index (block),&n;&t;&t;&t;&t;&t;   multiple of 8 bytes. */
multiline_comment|/* NOTE: For the index root attribute, the above two numbers are always&n;&t;   equal, as the attribute is resident and it is resized as needed. In&n;&t;   the case of the index allocation attribute the attribute is not&n;&t;   resident and hence the allocated_size is a fixed value and must&n;&t;   equal the index_block_size specified by the INDEX_ROOT attribute&n;&t;   corresponding to the INDEX_ALLOCATION attribute this INDEX_BLOCK&n;&t;   belongs to. */
DECL|member|flags
id|INDEX_HEADER_FLAGS
id|flags
suffix:semicolon
multiline_comment|/* Bit field of INDEX_HEADER_FLAGS. */
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved/align to 8-byte boundary. */
DECL|typedef|INDEX_HEADER
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|INDEX_HEADER
suffix:semicolon
multiline_comment|/*&n; * Attribute: Index root (0x90).&n; *&n; * NOTE: Always resident.&n; *&n; * This is followed by a sequence of index entries (INDEX_ENTRY structures)&n; * as described by the index header.&n; *&n; * When a directory is small enough to fit inside the index root then this&n; * is the only attribute describing the directory. When the directory is too&n; * large to fit in the index root, on the other hand, two aditional attributes&n; * are present: an index allocation attribute, containing sub-nodes of the B+&n; * directory tree (see below), and a bitmap attribute, describing which virtual&n; * cluster numbers (vcns) in the index allocation attribute are in use by an&n; * index block.&n; *&n; * NOTE: The root directory (FILE_root) contains an entry for itself. Other&n; * dircetories do not contain entries for themselves, though.&n; */
r_typedef
r_struct
(brace
DECL|member|type
id|ATTR_TYPES
id|type
suffix:semicolon
multiline_comment|/* Type of the indexed attribute. Is&n;&t;&t;&t;&t;&t;   $FILE_NAME for directories, zero&n;&t;&t;&t;&t;&t;   for view indexes. No other values&n;&t;&t;&t;&t;&t;   allowed. */
DECL|member|collation_rule
id|COLLATION_RULES
id|collation_rule
suffix:semicolon
multiline_comment|/* Collation rule used to sort the&n;&t;&t;&t;&t;&t;   index entries. If type is $FILE_NAME,&n;&t;&t;&t;&t;&t;   this must be COLLATION_FILE_NAME. */
DECL|member|index_block_size
id|u32
id|index_block_size
suffix:semicolon
multiline_comment|/* Size of each index block in bytes (in&n;&t;&t;&t;&t;&t;   the index allocation attribute). */
DECL|member|clusters_per_index_block
id|u8
id|clusters_per_index_block
suffix:semicolon
multiline_comment|/* Cluster size of each index block (in&n;&t;&t;&t;&t;&t;   the index allocation attribute), when&n;&t;&t;&t;&t;&t;   an index block is &gt;= than a cluster,&n;&t;&t;&t;&t;&t;   otherwise this will be the log of&n;&t;&t;&t;&t;&t;   the size (like how the encoding of &n;&t;&t;&t;&t;&t;   the mft record size and the index&n;&t;&t;&t;&t;&t;   record size found in the boot sector&n;&t;&t;&t;&t;&t;   work). Has to be a power of 2. */
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved/align to 8-byte boundary. */
DECL|member|index
id|INDEX_HEADER
id|index
suffix:semicolon
multiline_comment|/* Index header describing the&n;&t;&t;&t;&t;&t;   following index entries. */
DECL|typedef|INDEX_ROOT
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|INDEX_ROOT
suffix:semicolon
multiline_comment|/*&n; * Attribute: Index allocation (0xa0).&n; *&n; * NOTE: Always non-resident (doesn&squot;t make sense to be resident anyway!).&n; * &n; * This is an array of index blocks. Each index block starts with an&n; * INDEX_BLOCK structure containing an index header, followed by a sequence of&n; * index entries (INDEX_ENTRY structures), as described by the INDEX_HEADER.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*  0*/
id|NTFS_RECORD
id|SN
c_func
(paren
id|inr
)paren
suffix:semicolon
multiline_comment|/* Magic is &quot;INDX&quot;. */
DECL|member|lsn
multiline_comment|/*  8*/
id|s64
id|lsn
suffix:semicolon
multiline_comment|/* $LogFile sequence number of the last&n;&t;&t;&t;&t;   modification of this index block. */
DECL|member|index_block_vcn
multiline_comment|/* 16*/
id|VCN
id|index_block_vcn
suffix:semicolon
multiline_comment|/* Virtual cluster number of the index block.&n;&t;&t;&t;&t;   If the cluster_size on the volume is &lt;= the&n;&t;&t;&t;&t;   index_block_size of the directory,&n;&t;&t;&t;&t;   index_block_vcn counts in units of clusters,&n;&t;&t;&t;&t;   and in units of sectors otherwise. */
DECL|member|index
multiline_comment|/* 24*/
id|INDEX_HEADER
id|index
suffix:semicolon
multiline_comment|/* Describes the following index entries. */
multiline_comment|/* sizeof()= 40 (0x28) bytes */
multiline_comment|/*&n; * When creating the index block, we place the update sequence array at this&n; * offset, i.e. before we start with the index entries. This also makes sense,&n; * otherwise we could run into problems with the update sequence array&n; * containing in itself the last two bytes of a sector which would mean that&n; * multi sector transfer protection wouldn&squot;t work. As you can&squot;t protect data&n; * by overwriting it since you then can&squot;t get it back...&n; * When reading use the data from the ntfs record header.&n; */
DECL|typedef|INDEX_BLOCK
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|INDEX_BLOCK
suffix:semicolon
DECL|macro|_INR
mdefine_line|#define _INR(X)  SC(inr,X)
DECL|typedef|INDEX_ALLOCATION
r_typedef
id|INDEX_BLOCK
id|INDEX_ALLOCATION
suffix:semicolon
multiline_comment|/*&n; * The system file FILE_Extend/$Reparse contains an index named $R listing&n; * all reparse points on the volume. The index entry keys are as defined&n; * below. Note, that there is no index data associated with the index entries.&n; *&n; * The index entries are sorted by the index key file_id. The collation rule is&n; * COLLATION_NTOFS_ULONGS. FIXME: Verify whether the reparse_tag is not the&n; * primary key / is not a key at all. (AIA)&n; */
r_typedef
r_struct
(brace
DECL|member|reparse_tag
id|u32
id|reparse_tag
suffix:semicolon
multiline_comment|/* Reparse point type (inc. flags). */
DECL|member|file_id
id|MFT_REF
id|file_id
suffix:semicolon
multiline_comment|/* Mft record of the file containing the&n;&t;&t;&t;&t;   reparse point attribute. */
DECL|typedef|REPARSE_INDEX_KEY
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|REPARSE_INDEX_KEY
suffix:semicolon
multiline_comment|/*&n; * Quota flags (32-bit).&n; */
r_typedef
r_enum
(brace
multiline_comment|/* The user quota flags. Names explain meaning. */
DECL|enumerator|QUOTA_FLAG_DEFAULT_LIMITS
id|QUOTA_FLAG_DEFAULT_LIMITS
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000001
)paren
comma
DECL|enumerator|QUOTA_FLAG_LIMIT_REACHED
id|QUOTA_FLAG_LIMIT_REACHED
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000002
)paren
comma
DECL|enumerator|QUOTA_FLAG_ID_DELETED
id|QUOTA_FLAG_ID_DELETED
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000004
)paren
comma
DECL|enumerator|QUOTA_FLAG_USER_MASK
id|QUOTA_FLAG_USER_MASK
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000007
)paren
comma
multiline_comment|/* Bit mask for user quota flags. */
multiline_comment|/* These flags are only present in the quota defaults index entry,&n;&t;   i.e. in the entry where owner_id = QUOTA_DEFAULTS_ID. */
DECL|enumerator|QUOTA_FLAG_TRACKING_ENABLED
id|QUOTA_FLAG_TRACKING_ENABLED
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000010
)paren
comma
DECL|enumerator|QUOTA_FLAG_ENFORCEMENT_ENABLED
id|QUOTA_FLAG_ENFORCEMENT_ENABLED
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000020
)paren
comma
DECL|enumerator|QUOTA_FLAG_TRACKING_REQUESTED
id|QUOTA_FLAG_TRACKING_REQUESTED
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000040
)paren
comma
DECL|enumerator|QUOTA_FLAG_LOG_THRESHOLD
id|QUOTA_FLAG_LOG_THRESHOLD
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000080
)paren
comma
DECL|enumerator|QUOTA_FLAG_LOG_LIMIT
id|QUOTA_FLAG_LOG_LIMIT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000100
)paren
comma
DECL|enumerator|QUOTA_FLAG_OUT_OF_DATE
id|QUOTA_FLAG_OUT_OF_DATE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000200
)paren
comma
DECL|enumerator|QUOTA_FLAG_CORRUPT
id|QUOTA_FLAG_CORRUPT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000400
)paren
comma
DECL|enumerator|QUOTA_FLAG_PENDING_DELETES
id|QUOTA_FLAG_PENDING_DELETES
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000800
)paren
comma
DECL|typedef|QUOTA_FLAGS
)brace
id|QUOTA_FLAGS
suffix:semicolon
multiline_comment|/*&n; * The system file FILE_Extend/$Quota contains two indexes $O and $Q. Quotas&n; * are on a per volume and per user basis.&n; *&n; * The $Q index contains one entry for each existing user_id on the volume. The&n; * index key is the user_id of the user/group owning this quota control entry,&n; * i.e. the key is the owner_id. The user_id of the owner of a file, i.e. the &n; * owner_id, is found in the standard information attribute. The collation rule&n; * for $Q is COLLATION_NTOFS_ULONG.&n; *&n; * The $O index contains one entry for each user/group who has been assigned&n; * a quota on that volume. The index key holds the SID of the user_id the&n; * entry belongs to, i.e. the owner_id. The collation rule for $O is&n; * COLLATION_NTOFS_SID.&n; *&n; * The $O index entry data is the user_id of the user corresponding to the SID.&n; * This user_id is used as an index into $Q to find the quota control entry&n; * associated with the SID.&n; *&n; * The $Q index entry data is the quota control entry and is defined below.&n; */
r_typedef
r_struct
(brace
DECL|member|version
id|u32
id|version
suffix:semicolon
multiline_comment|/* Currently equals 2. */
DECL|member|flags
id|QUOTA_FLAGS
id|flags
suffix:semicolon
multiline_comment|/* Flags describing this quota entry. */
DECL|member|bytes_used
id|u64
id|bytes_used
suffix:semicolon
multiline_comment|/* How many bytes of the quota are in use. */
DECL|member|change_time
id|s64
id|change_time
suffix:semicolon
multiline_comment|/* Last time this quota entry was changed. */
DECL|member|threshold
id|s64
id|threshold
suffix:semicolon
multiline_comment|/* Soft quota (-1 if not limited). */
DECL|member|limit
id|s64
id|limit
suffix:semicolon
multiline_comment|/* Hard quota (-1 if not limited). */
DECL|member|exceeded_time
id|s64
id|exceeded_time
suffix:semicolon
multiline_comment|/* How long the soft quota has been exceeded. */
DECL|member|sid
id|SID
id|sid
suffix:semicolon
multiline_comment|/* The SID of the user/object associated with&n;&t;&t;&t;&t;   this quota entry. Equals zero for the quota&n;&t;&t;&t;&t;   defaults entry. */
DECL|typedef|QUOTA_CONTROL_ENTRY
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|QUOTA_CONTROL_ENTRY
suffix:semicolon
multiline_comment|/*&n; * Predefined owner_id values (32-bit).&n; */
r_typedef
r_enum
(brace
DECL|enumerator|QUOTA_INVALID_ID
id|QUOTA_INVALID_ID
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000000
)paren
comma
DECL|enumerator|QUOTA_DEFAULTS_ID
id|QUOTA_DEFAULTS_ID
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000001
)paren
comma
DECL|enumerator|QUOTA_FIRST_USER_ID
id|QUOTA_FIRST_USER_ID
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000100
)paren
comma
DECL|typedef|PREDEFINED_OWNER_IDS
)brace
id|PREDEFINED_OWNER_IDS
suffix:semicolon
multiline_comment|/*&n; * Index entry flags (16-bit).&n; */
r_typedef
r_enum
(brace
DECL|enumerator|INDEX_ENTRY_NODE
id|INDEX_ENTRY_NODE
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* This entry contains a sub-node,&n;&t;&t;&t;&t;&t;      i.e. a reference to an index&n;&t;&t;&t;&t;&t;      block in form of a virtual&n;&t;&t;&t;&t;&t;      cluster number (see below). */
DECL|enumerator|INDEX_ENTRY_END
id|INDEX_ENTRY_END
op_assign
id|const_cpu_to_le16
c_func
(paren
l_int|2
)paren
comma
multiline_comment|/* This signifies the last entry in&n;&t;&t;&t;&t;&t;      an index block. The index entry&n;&t;&t;&t;&t;&t;      does not represent a file but it&n;&t;&t;&t;&t;&t;      can point to a sub-node. */
DECL|enumerator|INDEX_ENTRY_SPACE_FILLER
id|INDEX_ENTRY_SPACE_FILLER
op_assign
l_int|0xffff
comma
multiline_comment|/* Just to force 16-bit width. */
DECL|typedef|INDEX_ENTRY_FLAGS
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|INDEX_ENTRY_FLAGS
suffix:semicolon
multiline_comment|/*&n; * This the index entry header (see below).&n; */
r_typedef
r_struct
(brace
multiline_comment|/*  0*/
r_union
(brace
multiline_comment|/* Only valid when INDEX_ENTRY_END is not set. */
DECL|member|indexed_file
id|MFT_REF
id|indexed_file
suffix:semicolon
multiline_comment|/* The mft reference of the file&n;&t;&t;&t;&t;&t;&t;   described by this index&n;&t;&t;&t;&t;&t;&t;   entry. Used for directory&n;&t;&t;&t;&t;&t;&t;   indexes. */
r_struct
(brace
multiline_comment|/* Used for views/indexes to find the entry&squot;s data. */
DECL|member|data_offset
id|u16
id|data_offset
suffix:semicolon
multiline_comment|/* Data byte offset from this&n;&t;&t;&t;&t;&t;&t;   INDEX_ENTRY. Follows the&n;&t;&t;&t;&t;&t;&t;   index key. */
DECL|member|data_length
id|u16
id|data_length
suffix:semicolon
multiline_comment|/* Data length in bytes. */
DECL|member|reservedV
id|u32
id|reservedV
suffix:semicolon
multiline_comment|/* Reserved (zero). */
)brace
id|SN
c_func
(paren
id|iev
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
)brace
id|SN
c_func
(paren
id|iif
)paren
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|member|length
multiline_comment|/*  8*/
id|u16
id|length
suffix:semicolon
multiline_comment|/* Byte size of this index entry, multiple of&n;&t;&t;&t;&t;    8-bytes. */
DECL|member|key_length
multiline_comment|/* 10*/
id|u16
id|key_length
suffix:semicolon
multiline_comment|/* Byte size of the key value, which is in the&n;&t;&t;&t;&t;    index entry. It follows field reserved. Not&n;&t;&t;&t;&t;    multiple of 8-bytes. */
DECL|member|flags
multiline_comment|/* 12*/
id|INDEX_ENTRY_FLAGS
id|flags
suffix:semicolon
multiline_comment|/* Bit field of INDEX_ENTRY_* flags. */
DECL|member|reserved
multiline_comment|/* 14*/
id|u16
id|reserved
suffix:semicolon
multiline_comment|/* Reserved/align to 8-byte boundary. */
multiline_comment|/* sizeof() = 16 bytes */
DECL|typedef|INDEX_ENTRY_HEADER
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|INDEX_ENTRY_HEADER
suffix:semicolon
DECL|macro|_IIF
mdefine_line|#define _IIF(X)  SC(ieh.iif,X)
DECL|macro|_IEV
mdefine_line|#define _IEV(X)  SC(iif.iev,X)
multiline_comment|/*&n; * This is an index entry. A sequence of such entries follows each INDEX_HEADER&n; * structure. Together they make up a complete index. The index follows either&n; * an index root attribute or an index allocation attribute.&n; *&n; * NOTE: Before NTFS 3.0 only filename attributes were indexed.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*  0*/
id|INDEX_ENTRY_HEADER
id|SN
c_func
(paren
id|ieh
)paren
suffix:semicolon
multiline_comment|/* The index entry header (see above). */
multiline_comment|/* 16*/
r_union
(brace
multiline_comment|/* The key of the indexed attribute. NOTE: Only present&n;&t;&t;&t;   if INDEX_ENTRY_END bit in flags is not set. NOTE: On&n;&t;&t;&t;   NTFS versions before 3.0 the only valid key is the&n;&t;&t;&t;   FILE_NAME_ATTR. On NTFS 3.0+ the following&n;&t;&t;&t;   additional index keys are defined: */
DECL|member|file_name
id|FILE_NAME_ATTR
id|file_name
suffix:semicolon
multiline_comment|/* $I30 index in directories. */
DECL|member|sii
id|SII_INDEX_KEY
id|sii
suffix:semicolon
multiline_comment|/* $SII index in $Secure. */
DECL|member|sdh
id|SDH_INDEX_KEY
id|sdh
suffix:semicolon
multiline_comment|/* $SDH index in $Secure. */
DECL|member|object_id
id|GUID
id|object_id
suffix:semicolon
multiline_comment|/* $O index in FILE_Extend/$ObjId: The&n;&t;&t;&t;&t;&t;   object_id of the mft record found in&n;&t;&t;&t;&t;&t;   the data part of the index. */
id|REPARSE_INDEX_KEY
id|SN
c_func
(paren
id|iri
)paren
suffix:semicolon
multiline_comment|/* $R index in FILE_Extend/$Reparse. */
DECL|member|sid
id|SID
id|sid
suffix:semicolon
multiline_comment|/* $O index in FILE_Extend/$Quota:&n;&t;&t;&t;&t;&t;   SID of the owner of the user_id. */
DECL|member|owner_id
id|u32
id|owner_id
suffix:semicolon
multiline_comment|/* $Q index in FILE_Extend/$Quota:&n;&t;&t;&t;&t;&t;   user_id of the owner of the quota&n;&t;&t;&t;&t;&t;   control entry in the data part of&n;&t;&t;&t;&t;&t;   the index. */
DECL|member|key
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|key
suffix:semicolon
multiline_comment|/* The (optional) index data is inserted here when creating. */
singleline_comment|// VCN vcn;&t;/* If INDEX_ENTRY_NODE bit in flags is set, the last
singleline_comment|//&t;&t;   eight bytes of this index entry contain the virtual
singleline_comment|//&t;&t;   cluster number of the index block that holds the
singleline_comment|//&t;&t;   entries immediately preceding the current entry (the
singleline_comment|//&t;&t;   vcn references the corresponding cluster in the data
singleline_comment|//&t;&t;   of the non-resident index allocation attribute). If
singleline_comment|//&t;&t;   the key_length is zero, then the vcn immediately
singleline_comment|//&t;&t;   follows the INDEX_ENTRY_HEADER. Regardless of
singleline_comment|//&t;&t;   key_length, the address of the 8-byte boundary
singleline_comment|//&t;&t;   alligned vcn of INDEX_ENTRY{_HEADER} *ie is given by
singleline_comment|//&t;&t;   (char*)ie + le16_to_cpu(ie*)-&gt;length) - sizeof(VCN),
singleline_comment|//&t;&t;   where sizeof(VCN) can be hardcoded as 8 if wanted. */
DECL|typedef|INDEX_ENTRY
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|INDEX_ENTRY
suffix:semicolon
DECL|macro|_IEH
mdefine_line|#define _IEH(X)  SC(ieh,X)
DECL|macro|_IRI
mdefine_line|#define _IRI(X)  SC(key.iri,X)
multiline_comment|/*&n; * Attribute: Bitmap (0xb0).&n; *&n; * Contains an array of bits (aka a bitfield).&n; *&n; * When used in conjunction with the index allocation attribute, each bit&n; * corresponds to one index block within the index allocation attribute. Thus&n; * the number of bits in the bitmap * index block size / cluster size is the&n; * number of clusters in the index allocation attribute.&n; */
r_typedef
r_struct
(brace
DECL|member|bitmap
id|u8
id|bitmap
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Array of bits. */
DECL|typedef|BITMAP_ATTR
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|BITMAP_ATTR
suffix:semicolon
multiline_comment|/*&n; * The reparse point tag defines the type of the reparse point. It also&n; * includes several flags, which further describe the reparse point.&n; *&n; * The reparse point tag is an unsigned 32-bit value divided in three parts:&n; *&n; * 1. The least significant 16 bits (i.e. bits 0 to 15) specifiy the type of&n; *    the reparse point.&n; * 2. The 13 bits after this (i.e. bits 16 to 28) are reserved for future use.&n; * 3. The most significant three bits are flags describing the reparse point.&n; *    They are defined as follows:&n; *&t;bit 29: Name surrogate bit. If set, the filename is an alias for&n; *&t;&t;another object in the system.&n; * &t;bit 30: High-latency bit. If set, accessing the first byte of data will&n; *&t;&t;be slow. (E.g. the data is stored on a tape drive.)&n; * &t;bit 31: Microsoft bit. If set, the tag is owned by Microsoft. User&n; *&t;&t;defined tags have to use zero here.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|IO_REPARSE_TAG_IS_ALIAS
id|IO_REPARSE_TAG_IS_ALIAS
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x20000000
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_IS_HIGH_LATENCY
id|IO_REPARSE_TAG_IS_HIGH_LATENCY
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x40000000
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_IS_MICROSOFT
id|IO_REPARSE_TAG_IS_MICROSOFT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x80000000
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_RESERVED_ZERO
id|IO_REPARSE_TAG_RESERVED_ZERO
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000000
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_RESERVED_ONE
id|IO_REPARSE_TAG_RESERVED_ONE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000001
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_RESERVED_RANGE
id|IO_REPARSE_TAG_RESERVED_RANGE
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x00000001
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_NSS
id|IO_REPARSE_TAG_NSS
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x68000005
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_NSS_RECOVER
id|IO_REPARSE_TAG_NSS_RECOVER
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x68000006
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_SIS
id|IO_REPARSE_TAG_SIS
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x68000007
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_DFS
id|IO_REPARSE_TAG_DFS
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x68000008
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_MOUNT_POINT
id|IO_REPARSE_TAG_MOUNT_POINT
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0x88000003
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_HSM
id|IO_REPARSE_TAG_HSM
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0xa8000004
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_SYMBOLIC_LINK
id|IO_REPARSE_TAG_SYMBOLIC_LINK
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0xe8000000
)paren
comma
DECL|enumerator|IO_REPARSE_TAG_VALID_VALUES
id|IO_REPARSE_TAG_VALID_VALUES
op_assign
id|const_cpu_to_le32
c_func
(paren
l_int|0xe000ffff
)paren
comma
DECL|typedef|PREDEFINED_REPARSE_TAGS
)brace
id|PREDEFINED_REPARSE_TAGS
suffix:semicolon
multiline_comment|/*&n; * Attribute: Reparse point (0xc0).&n; *&n; * NOTE: Can be resident or non-resident.&n; */
r_typedef
r_struct
(brace
DECL|member|reparse_tag
id|u32
id|reparse_tag
suffix:semicolon
multiline_comment|/* Reparse point type (inc. flags). */
DECL|member|reparse_data_length
id|u16
id|reparse_data_length
suffix:semicolon
multiline_comment|/* Byte size of reparse data. */
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
multiline_comment|/* Align to 8-byte boundary. */
DECL|member|reparse_data
id|u8
id|reparse_data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Meaning depends on reparse_tag. */
DECL|typedef|REPARSE_POINT
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|REPARSE_POINT
suffix:semicolon
multiline_comment|/*&n; * Attribute: Extended attribute (EA) information (0xd0).&n; *&n; * NOTE: Always resident. (Is this true???)&n; */
r_typedef
r_struct
(brace
DECL|member|ea_length
id|u16
id|ea_length
suffix:semicolon
multiline_comment|/* Byte size of the packed extended&n;&t;&t;&t;&t;   attributes. */
DECL|member|need_ea_count
id|u16
id|need_ea_count
suffix:semicolon
multiline_comment|/* The number of extended attributes which have&n;&t;&t;&t;&t;   the NEED_EA bit set. */
DECL|member|ea_query_length
id|u32
id|ea_query_length
suffix:semicolon
multiline_comment|/* Byte size of the buffer required to query&n;&t;&t;&t;&t;   the extended attributes when calling&n;&t;&t;&t;&t;   ZwQueryEaFile() in Windows NT/2k. I.e. the&n;&t;&t;&t;&t;   byte size of the unpacked extended&n;&t;&t;&t;&t;   attributes. */
DECL|typedef|EA_INFORMATION
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|EA_INFORMATION
suffix:semicolon
multiline_comment|/*&n; * Extended attribute flags (8-bit).&n; */
r_typedef
r_enum
(brace
DECL|enumerator|NEED_EA
id|NEED_EA
op_assign
l_int|0x80
comma
DECL|typedef|EA_FLAGS
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|EA_FLAGS
suffix:semicolon
multiline_comment|/*&n; * Attribute: Extended attribute (EA) (0xe0).&n; *&n; * NOTE: Always non-resident. (Is this true?)&n; * &n; * Like the attribute list and the index buffer list, the EA attribute value is &n; * a sequence of EA_ATTR variable length records.&n; *&n; * FIXME: It appears weird that the EA name is not unicode. Is it true?&n; */
r_typedef
r_struct
(brace
DECL|member|next_entry_offset
id|u32
id|next_entry_offset
suffix:semicolon
multiline_comment|/* Offset to the next EA_ATTR. */
DECL|member|flags
id|EA_FLAGS
id|flags
suffix:semicolon
multiline_comment|/* Flags describing the EA. */
DECL|member|ea_name_length
id|u8
id|ea_name_length
suffix:semicolon
multiline_comment|/* Length of the name of the EA in bytes. */
DECL|member|ea_value_length
id|u16
id|ea_value_length
suffix:semicolon
multiline_comment|/* Byte size of the EA&squot;s value. */
DECL|member|ea_name
id|u8
id|ea_name
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Name of the EA. */
DECL|member|ea_value
id|u8
id|ea_value
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* The value of the EA. Immediately follows&n;&t;&t;&t;&t;   the name. */
DECL|typedef|EA_ATTR
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|EA_ATTR
suffix:semicolon
multiline_comment|/*&n; * Attribute: Property set (0xf0).&n; *&n; * Intended to support Native Structure Storage (NSS) - a feature removed from&n; * NTFS 3.0 during beta testing.&n; */
r_typedef
r_struct
(brace
multiline_comment|/* Irrelevant as feature unused. */
DECL|typedef|PROPERTY_SET
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|PROPERTY_SET
suffix:semicolon
multiline_comment|/*&n; * Attribute: Logged utility stream (0x100).&n; *&n; * NOTE: Can be resident or non-resident.&n; *&n; * Operations on this attribute are logged to the journal ($LogFile) like&n; * normal metadata changes.&n; *&n; * Used by the Encrypting File System (EFS). All encrypted files have this&n; * attribute with the name $EFS.&n; */
r_typedef
r_struct
(brace
multiline_comment|/* Can be anything the creator chooses. */
multiline_comment|/* EFS uses it as follows: */
singleline_comment|// FIXME: Type this info, verifying it along the way. (AIA)
DECL|typedef|LOGGED_UTILITY_STREAM
DECL|typedef|EFS_ATTR
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|LOGGED_UTILITY_STREAM
comma
id|EFS_ATTR
suffix:semicolon
macro_line|#endif /* _LINUX_NTFS_LAYOUT_H */
eof
