multiline_comment|/************************************************************&n; * EFI GUID Partition Table&n; * Per Intel EFI Specification v1.02&n; * http://developer.intel.com/technology/efi/efi.htm&n; *&n; * By Matt Domsch &lt;Matt_Domsch@dell.com&gt;  Fri Sep 22 22:15:56 CDT 2000  &n; *   Copyright 2000,2001 Dell Computer Corporation&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; * &n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; * &n; ************************************************************/
macro_line|#ifndef FS_PART_EFI_H_INCLUDED
DECL|macro|FS_PART_EFI_H_INCLUDED
mdefine_line|#define FS_PART_EFI_H_INCLUDED
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
multiline_comment|/*&n; * Yes, specifying asm-ia64 is ugly, but this lets it build on&n; * other platforms too, until efi.h moves to include/linux.&n; */
macro_line|#include &lt;asm-ia64/efi.h&gt;
DECL|macro|MSDOS_MBR_SIGNATURE
mdefine_line|#define MSDOS_MBR_SIGNATURE 0xaa55
DECL|macro|EFI_PMBR_OSTYPE_EFI
mdefine_line|#define EFI_PMBR_OSTYPE_EFI 0xEF
DECL|macro|EFI_PMBR_OSTYPE_EFI_GPT
mdefine_line|#define EFI_PMBR_OSTYPE_EFI_GPT 0xEE
DECL|macro|GPT_BLOCK_SIZE
mdefine_line|#define GPT_BLOCK_SIZE 512
DECL|macro|GPT_HEADER_SIGNATURE
mdefine_line|#define GPT_HEADER_SIGNATURE 0x5452415020494645L
DECL|macro|GPT_HEADER_REVISION_V1
mdefine_line|#define GPT_HEADER_REVISION_V1 0x00010000
DECL|macro|GPT_PRIMARY_PARTITION_TABLE_LBA
mdefine_line|#define GPT_PRIMARY_PARTITION_TABLE_LBA 1
DECL|macro|PARTITION_SYSTEM_GUID
mdefine_line|#define PARTITION_SYSTEM_GUID &bslash;&n;    EFI_GUID( 0xC12A7328, 0xF81F, 0x11d2, &bslash;&n;              0xBA, 0x4B, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B) 
DECL|macro|LEGACY_MBR_PARTITION_GUID
mdefine_line|#define LEGACY_MBR_PARTITION_GUID &bslash;&n;    EFI_GUID( 0x024DEE41, 0x33E7, 0x11d3, &bslash;&n;              0x9D, 0x69, 0x00, 0x08, 0xC7, 0x81, 0xF3, 0x9F)
DECL|macro|PARTITION_MSFT_RESERVED_GUID
mdefine_line|#define PARTITION_MSFT_RESERVED_GUID &bslash;&n;    EFI_GUID( 0xE3C9E316, 0x0B5C, 0x4DB8, &bslash;&n;              0x81, 0x7D, 0xF9, 0x2D, 0xF0, 0x02, 0x15, 0xAE)
DECL|macro|PARTITION_BASIC_DATA_GUID
mdefine_line|#define PARTITION_BASIC_DATA_GUID &bslash;&n;    EFI_GUID( 0xEBD0A0A2, 0xB9E5, 0x4433, &bslash;&n;              0x87, 0xC0, 0x68, 0xB6, 0xB7, 0x26, 0x99, 0xC7)
DECL|macro|PARTITION_LINUX_RAID_GUID
mdefine_line|#define PARTITION_LINUX_RAID_GUID &bslash;&n;    EFI_GUID( 0xa19d880f, 0x05fc, 0x4d3b, &bslash;&n;              0xa0, 0x06, 0x74, 0x3f, 0x0f, 0x84, 0x91, 0x1e)
DECL|macro|PARTITION_LINUX_SWAP_GUID
mdefine_line|#define PARTITION_LINUX_SWAP_GUID &bslash;&n;    EFI_GUID( 0x0657fd6d, 0xa4ab, 0x43c4, &bslash;&n;              0x84, 0xe5, 0x09, 0x33, 0xc8, 0x4b, 0x4f, 0x4f)
DECL|macro|PARTITION_LINUX_LVM_GUID
mdefine_line|#define PARTITION_LINUX_LVM_GUID &bslash;&n;    EFI_GUID( 0xe6d6d379, 0xf507, 0x44c2, &bslash;&n;              0xa2, 0x3c, 0x23, 0x8f, 0x2a, 0x3d, 0xf9, 0x28)
DECL|struct|_gpt_header
r_typedef
r_struct
id|_gpt_header
(brace
DECL|member|signature
id|u64
id|signature
suffix:semicolon
DECL|member|revision
id|u32
id|revision
suffix:semicolon
DECL|member|header_size
id|u32
id|header_size
suffix:semicolon
DECL|member|header_crc32
id|u32
id|header_crc32
suffix:semicolon
DECL|member|reserved1
id|u32
id|reserved1
suffix:semicolon
DECL|member|my_lba
id|u64
id|my_lba
suffix:semicolon
DECL|member|alternate_lba
id|u64
id|alternate_lba
suffix:semicolon
DECL|member|first_usable_lba
id|u64
id|first_usable_lba
suffix:semicolon
DECL|member|last_usable_lba
id|u64
id|last_usable_lba
suffix:semicolon
DECL|member|disk_guid
id|efi_guid_t
id|disk_guid
suffix:semicolon
DECL|member|partition_entry_lba
id|u64
id|partition_entry_lba
suffix:semicolon
DECL|member|num_partition_entries
id|u32
id|num_partition_entries
suffix:semicolon
DECL|member|sizeof_partition_entry
id|u32
id|sizeof_partition_entry
suffix:semicolon
DECL|member|partition_entry_array_crc32
id|u32
id|partition_entry_array_crc32
suffix:semicolon
DECL|member|reserved2
id|u8
id|reserved2
(braket
id|GPT_BLOCK_SIZE
op_minus
l_int|92
)braket
suffix:semicolon
DECL|typedef|gpt_header
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|gpt_header
suffix:semicolon
DECL|struct|_gpt_entry_attributes
r_typedef
r_struct
id|_gpt_entry_attributes
(brace
DECL|member|required_to_function
id|u64
id|required_to_function
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u64
id|reserved
suffix:colon
l_int|47
suffix:semicolon
DECL|member|type_guid_specific
id|u64
id|type_guid_specific
suffix:colon
l_int|16
suffix:semicolon
DECL|typedef|gpt_entry_attributes
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|gpt_entry_attributes
suffix:semicolon
DECL|struct|_gpt_entry
r_typedef
r_struct
id|_gpt_entry
(brace
DECL|member|partition_type_guid
id|efi_guid_t
id|partition_type_guid
suffix:semicolon
DECL|member|unique_partition_guid
id|efi_guid_t
id|unique_partition_guid
suffix:semicolon
DECL|member|starting_lba
id|u64
id|starting_lba
suffix:semicolon
DECL|member|ending_lba
id|u64
id|ending_lba
suffix:semicolon
DECL|member|attributes
id|gpt_entry_attributes
id|attributes
suffix:semicolon
DECL|member|partition_name
id|efi_char16_t
id|partition_name
(braket
l_int|72
op_div
r_sizeof
(paren
id|efi_char16_t
)paren
)braket
suffix:semicolon
DECL|typedef|gpt_entry
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|gpt_entry
suffix:semicolon
DECL|struct|_legacy_mbr
r_typedef
r_struct
id|_legacy_mbr
(brace
DECL|member|boot_code
id|u8
id|boot_code
(braket
l_int|440
)braket
suffix:semicolon
DECL|member|unique_mbr_signature
id|u32
id|unique_mbr_signature
suffix:semicolon
DECL|member|unknown
id|u16
id|unknown
suffix:semicolon
DECL|member|partition_record
r_struct
id|partition
id|partition_record
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|signature
id|u16
id|signature
suffix:semicolon
DECL|typedef|legacy_mbr
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|legacy_mbr
suffix:semicolon
multiline_comment|/* Functions */
r_extern
r_int
id|efi_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_struct
id|block_device
op_star
id|bdev
comma
r_int
r_int
id|first_sector
comma
r_int
id|first_part_minor
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * --------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
