multiline_comment|/************************************************************&n; * EFI GUID Partition Table handling&n; * Per Intel EFI Specification v1.02&n; * http://developer.intel.com/technology/efi/efi.htm&n; * efi.[ch] by Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *   Copyright 2000,2001,2002 Dell Computer Corporation&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *&n; * TODO:&n; *&n; * Changelog:&n; * Tue  Mar 26 2002 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Ported to 2.5.7-pre1 and 2.5.7-dj2&n; * - Applied patch to avoid fault in alternate header handling&n; * - cleaned up find_valid_gpt&n; * - On-disk structure and copy in memory is *always* LE now - &n; *   swab fields as needed&n; * - remove print_gpt_header()&n; * - only use first max_p partition entries, to keep the kernel minor number&n; *   and partition numbers tied.&n; *&n; * Mon  Feb 04 2002 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Removed __PRIPTR_PREFIX - not being used&n; *&n; * Mon  Jan 14 2002 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Ported to 2.5.2-pre11 + library crc32 patch Linus applied&n; *&n; * Thu Dec 6 2001 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Added compare_gpts().&n; * - moved le_efi_guid_to_cpus() back into this file.  GPT is the only&n; *   thing that keeps EFI GUIDs on disk.&n; * - Changed gpt structure names and members to be simpler and more Linux-like.&n; * &n; * Wed Oct 17 2001 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Removed CONFIG_DEVFS_VOLUMES_UUID code entirely per Martin Wilck&n; *&n; * Wed Oct 10 2001 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Changed function comments to DocBook style per Andreas Dilger suggestion.&n; *&n; * Mon Oct 08 2001 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Change read_lba() to use the page cache per Al Viro&squot;s work.&n; * - print u64s properly on all architectures&n; * - fixed debug_printk(), now Dprintk()&n; *&n; * Mon Oct 01 2001 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Style cleanups&n; * - made most functions static&n; * - Endianness addition&n; * - remove test for second alternate header, as it&squot;s not per spec,&n; *   and is unnecessary.  There&squot;s now a method to read/write the last&n; *   sector of an odd-sized disk from user space.  No tools have ever&n; *   been released which used this code, so it&squot;s effectively dead.&n; * - Per Asit Mallick of Intel, added a test for a valid PMBR.&n; * - Added kernel command line option &squot;gpt&squot; to override valid PMBR test.&n; *&n; * Wed Jun  6 2001 Martin Wilck &lt;Martin.Wilck@Fujitsu-Siemens.com&gt;&n; * - added devfs volume UUID support (/dev/volumes/uuids) for&n; *   mounting file systems by the partition GUID. &n; *&n; * Tue Dec  5 2000 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Moved crc32() to linux/lib, added efi_crc32().&n; *&n; * Thu Nov 30 2000 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Replaced Intel&squot;s CRC32 function with an equivalent&n; *   non-license-restricted version.&n; *&n; * Wed Oct 25 2000 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Fixed the last_lba() call to return the proper last block&n; *&n; * Thu Oct 12 2000 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; * - Thanks to Andries Brouwer for his debugging assistance.&n; * - Code works, detects all the partitions.&n; *&n; ************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/crc32.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;check.h&quot;
macro_line|#include &quot;efi.h&quot;
macro_line|#if CONFIG_BLK_DEV_MD
r_extern
r_void
id|md_autodetect_dev
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Handle printing of 64-bit values */
multiline_comment|/* Borrowed from /usr/include/inttypes.h */
macro_line|# if BITS_PER_LONG == 64 
DECL|macro|__PRI64_PREFIX
macro_line|#  define __PRI64_PREFIX&t;&quot;l&quot;
macro_line|# else
DECL|macro|__PRI64_PREFIX
macro_line|#  define __PRI64_PREFIX&t;&quot;ll&quot;
macro_line|# endif
DECL|macro|PRIx64
macro_line|# define PRIx64&t;&t;__PRI64_PREFIX &quot;x&quot;
DECL|macro|EFI_DEBUG
macro_line|#undef EFI_DEBUG
macro_line|#ifdef EFI_DEBUG
DECL|macro|Dprintk
mdefine_line|#define Dprintk(x...) printk(KERN_DEBUG x)
macro_line|#else
DECL|macro|Dprintk
mdefine_line|#define Dprintk(x...)
macro_line|#endif
multiline_comment|/* This allows a kernel command line option &squot;gpt&squot; to override&n; * the test for invalid PMBR.  Not __initdata because reloading&n; * the partition tables happens after init too.&n; */
DECL|variable|force_gpt
r_static
r_int
id|force_gpt
suffix:semicolon
r_static
r_int
id|__init
DECL|function|force_gpt_fn
id|force_gpt_fn
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|force_gpt
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;gpt&quot;
comma
id|force_gpt_fn
)paren
suffix:semicolon
multiline_comment|/**&n; * efi_crc32() - EFI version of crc32 function&n; * @buf: buffer to calculate crc32 of&n; * @len - length of buf&n; *&n; * Description: Returns EFI-style CRC32 value for @buf&n; * &n; * This function uses the little endian Ethernet polynomial&n; * but seeds the function with ~0, and xor&squot;s with ~0 at the end.&n; * Note, the EFI Specification, v1.02, has a reference to&n; * Dr. Dobbs Journal, May 1994 (actually it&squot;s in May 1992).&n; */
r_static
r_inline
id|u32
DECL|function|efi_crc32
id|efi_crc32
c_func
(paren
r_const
r_void
op_star
id|buf
comma
r_int
r_int
id|len
)paren
(brace
r_return
(paren
id|crc32
c_func
(paren
op_complement
l_int|0L
comma
id|buf
comma
id|len
)paren
op_xor
op_complement
l_int|0L
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * is_pmbr_valid(): test Protective MBR for validity&n; * @mbr: pointer to a legacy mbr structure&n; *&n; * Description: Returns 1 if PMBR is valid, 0 otherwise.&n; * Validity depends on two things:&n; *  1) MSDOS signature is in the last two bytes of the MBR&n; *  2) One partition of type 0xEE is found&n; */
r_static
r_int
DECL|function|is_pmbr_valid
id|is_pmbr_valid
c_func
(paren
id|legacy_mbr
op_star
id|mbr
)paren
(brace
r_int
id|i
comma
id|found
op_assign
l_int|0
comma
id|signature
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mbr
)paren
r_return
l_int|0
suffix:semicolon
id|signature
op_assign
(paren
id|le16_to_cpu
c_func
(paren
id|mbr-&gt;signature
)paren
op_eq
id|MSDOS_MBR_SIGNATURE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|signature
op_logical_and
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mbr-&gt;partition_record
(braket
id|i
)braket
dot
id|sys_ind
op_eq
id|EFI_PMBR_OSTYPE_EFI_GPT
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
(paren
id|signature
op_logical_and
id|found
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * last_lba(): return number of last logical block of device&n; * @hd: gendisk with partition list&n; * @bdev: block device&n; * &n; * Description: Returns last LBA value on success, 0 on error.&n; * This is stored (by sd and ide-geometry) in&n; *  the part[0] entry for this disk, and is the number of&n; *  physical sectors available on the disk.&n; */
r_static
id|u64
DECL|function|last_lba
id|last_lba
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
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hd
op_logical_or
op_logical_neg
id|hd-&gt;part
op_logical_or
op_logical_neg
id|bdev
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|hd-&gt;part
(braket
id|minor
c_func
(paren
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
)paren
)paren
)braket
dot
id|nr_sects
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * read_lba(): Read bytes from disk, starting at given LBA&n; * @hd&n; * @bdev&n; * @lba&n; * @buffer&n; * @size_t&n; *&n; * Description:  Reads @count bytes from @bdev into @buffer.&n; * Returns number of bytes read on success, 0 on error.&n; */
r_static
r_int
DECL|function|read_lba
id|read_lba
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
id|u64
id|lba
comma
id|u8
op_star
id|buffer
comma
r_int
id|count
)paren
(brace
r_int
id|totalreadcount
op_assign
l_int|0
comma
id|bytesread
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|blocksize
suffix:semicolon
r_int
id|i
suffix:semicolon
id|Sector
id|sect
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hd
op_logical_or
op_logical_neg
id|bdev
op_logical_or
op_logical_neg
id|buffer
op_logical_or
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
id|blocksize
op_assign
id|bdev_hardsect_size
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blocksize
)paren
id|blocksize
op_assign
l_int|512
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|count
OG
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
id|data
op_assign
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|lba
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
id|totalreadcount
suffix:semicolon
id|bytesread
op_assign
id|PAGE_CACHE_SIZE
op_minus
(paren
id|data
op_minus
(paren
r_int
r_char
op_star
)paren
id|page_address
c_func
(paren
id|sect.v
)paren
)paren
suffix:semicolon
id|bytesread
op_assign
id|min
c_func
(paren
id|bytesread
comma
id|count
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|data
comma
id|bytesread
)paren
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
id|buffer
op_add_assign
id|bytesread
suffix:semicolon
id|totalreadcount
op_add_assign
id|bytesread
suffix:semicolon
id|count
op_sub_assign
id|bytesread
suffix:semicolon
id|lba
op_add_assign
(paren
id|bytesread
op_div
id|blocksize
)paren
suffix:semicolon
)brace
r_return
id|totalreadcount
suffix:semicolon
)brace
multiline_comment|/**&n; * alloc_read_gpt_entries(): reads partition entries from disk&n; * @hd&n; * @bdev&n; * @gpt - GPT header&n; * &n; * Description: Returns ptes on success,  NULL on error.&n; * Allocates space for PTEs based on information found in @gpt.&n; * Notes: remember to free pte when you&squot;re done!&n; */
r_static
id|gpt_entry
op_star
DECL|function|alloc_read_gpt_entries
id|alloc_read_gpt_entries
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
id|gpt_header
op_star
id|gpt
)paren
(brace
r_int
id|count
suffix:semicolon
id|gpt_entry
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hd
op_logical_or
op_logical_neg
id|bdev
op_logical_or
op_logical_neg
id|gpt
)paren
r_return
l_int|NULL
suffix:semicolon
id|count
op_assign
id|le32_to_cpu
c_func
(paren
id|gpt-&gt;num_partition_entries
)paren
op_star
id|le32_to_cpu
c_func
(paren
id|gpt-&gt;sizeof_partition_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|NULL
suffix:semicolon
id|pte
op_assign
id|kmalloc
c_func
(paren
id|count
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|pte
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_lba
c_func
(paren
id|hd
comma
id|bdev
comma
id|le64_to_cpu
c_func
(paren
id|gpt-&gt;partition_entry_lba
)paren
comma
(paren
id|u8
op_star
)paren
id|pte
comma
id|count
)paren
OL
id|count
)paren
(brace
id|kfree
c_func
(paren
id|pte
)paren
suffix:semicolon
id|pte
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/**&n; * alloc_read_gpt_header(): Allocates GPT header, reads into it from disk&n; * @hd&n; * @bdev&n; * @lba is the Logical Block Address of the partition table&n; * &n; * Description: returns GPT header on success, NULL on error.   Allocates&n; * and fills a GPT header starting at @ from @bdev.&n; * Note: remember to free gpt when finished with it.&n; */
r_static
id|gpt_header
op_star
DECL|function|alloc_read_gpt_header
id|alloc_read_gpt_header
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
id|u64
id|lba
)paren
(brace
id|gpt_header
op_star
id|gpt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hd
op_logical_or
op_logical_neg
id|bdev
)paren
r_return
l_int|NULL
suffix:semicolon
id|gpt
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|gpt_header
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gpt
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|gpt
comma
l_int|0
comma
r_sizeof
(paren
id|gpt_header
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_lba
c_func
(paren
id|hd
comma
id|bdev
comma
id|lba
comma
(paren
id|u8
op_star
)paren
id|gpt
comma
r_sizeof
(paren
id|gpt_header
)paren
)paren
OL
r_sizeof
(paren
id|gpt_header
)paren
)paren
(brace
id|kfree
c_func
(paren
id|gpt
)paren
suffix:semicolon
id|gpt
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|gpt
suffix:semicolon
)brace
multiline_comment|/**&n; * is_gpt_valid() - tests one GPT header and PTEs for validity&n; * @hd&n; * @bdev&n; * @lba is the logical block address of the GPT header to test&n; * @gpt is a GPT header ptr, filled on return.&n; * @ptes is a PTEs ptr, filled on return.&n; *&n; * Description: returns 1 if valid,  0 on error.&n; * If valid, returns pointers to newly allocated GPT header and PTEs.&n; */
r_static
r_int
DECL|function|is_gpt_valid
id|is_gpt_valid
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
id|u64
id|lba
comma
id|gpt_header
op_star
op_star
id|gpt
comma
id|gpt_entry
op_star
op_star
id|ptes
)paren
(brace
id|u32
id|crc
comma
id|origcrc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hd
op_logical_or
op_logical_neg
id|bdev
op_logical_or
op_logical_neg
id|gpt
op_logical_or
op_logical_neg
id|ptes
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|gpt
op_assign
id|alloc_read_gpt_header
c_func
(paren
id|hd
comma
id|bdev
comma
id|lba
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Check the GUID Partition Table signature */
r_if
c_cond
(paren
id|le64_to_cpu
c_func
(paren
(paren
op_star
id|gpt
)paren
op_member_access_from_pointer
id|signature
)paren
op_ne
id|GPT_HEADER_SIGNATURE
)paren
(brace
id|Dprintk
c_func
(paren
l_string|&quot;GUID Partition Table Header signature is wrong: %&quot;
id|PRIx64
l_string|&quot; != %&quot;
id|PRIx64
l_string|&quot;&bslash;n&quot;
comma
id|le64_to_cpu
c_func
(paren
(paren
op_star
id|gpt
)paren
op_member_access_from_pointer
id|signature
)paren
comma
id|GPT_HEADER_SIGNATURE
)paren
suffix:semicolon
id|kfree
c_func
(paren
op_star
id|gpt
)paren
suffix:semicolon
op_star
id|gpt
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Check the GUID Partition Table CRC */
id|origcrc
op_assign
id|le32_to_cpu
c_func
(paren
(paren
op_star
id|gpt
)paren
op_member_access_from_pointer
id|header_crc32
)paren
suffix:semicolon
(paren
op_star
id|gpt
)paren
op_member_access_from_pointer
id|header_crc32
op_assign
l_int|0
suffix:semicolon
id|crc
op_assign
id|efi_crc32
c_func
(paren
(paren
r_const
r_int
r_char
op_star
)paren
(paren
op_star
id|gpt
)paren
comma
id|le32_to_cpu
c_func
(paren
(paren
op_star
id|gpt
)paren
op_member_access_from_pointer
id|header_size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|crc
op_ne
id|origcrc
)paren
(brace
id|Dprintk
(paren
l_string|&quot;GUID Partition Table Header CRC is wrong: %x != %x&bslash;n&quot;
comma
id|crc
comma
id|origcrc
)paren
suffix:semicolon
id|kfree
c_func
(paren
op_star
id|gpt
)paren
suffix:semicolon
op_star
id|gpt
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
(paren
op_star
id|gpt
)paren
op_member_access_from_pointer
id|header_crc32
op_assign
id|cpu_to_le32
c_func
(paren
id|origcrc
)paren
suffix:semicolon
multiline_comment|/* Check that the my_lba entry points to the LBA that contains&n;&t; * the GUID Partition Table */
r_if
c_cond
(paren
id|le64_to_cpu
c_func
(paren
(paren
op_star
id|gpt
)paren
op_member_access_from_pointer
id|my_lba
)paren
op_ne
id|lba
)paren
(brace
id|Dprintk
c_func
(paren
l_string|&quot;GPT my_lba incorrect: %&quot;
id|PRIx64
l_string|&quot; != %&quot;
id|PRIx64
l_string|&quot;&bslash;n&quot;
comma
id|le64_to_cpu
c_func
(paren
(paren
op_star
id|gpt
)paren
op_member_access_from_pointer
id|my_lba
)paren
comma
id|lba
)paren
suffix:semicolon
id|kfree
c_func
(paren
op_star
id|gpt
)paren
suffix:semicolon
op_star
id|gpt
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|ptes
op_assign
id|alloc_read_gpt_entries
c_func
(paren
id|hd
comma
id|bdev
comma
op_star
id|gpt
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
op_star
id|gpt
)paren
suffix:semicolon
op_star
id|gpt
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Check the GUID Partition Entry Array CRC */
id|crc
op_assign
id|efi_crc32
c_func
(paren
(paren
r_const
r_int
r_char
op_star
)paren
(paren
op_star
id|ptes
)paren
comma
id|le32_to_cpu
c_func
(paren
(paren
op_star
id|gpt
)paren
op_member_access_from_pointer
id|num_partition_entries
)paren
op_star
id|le32_to_cpu
c_func
(paren
(paren
op_star
id|gpt
)paren
op_member_access_from_pointer
id|sizeof_partition_entry
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|crc
op_ne
id|le32_to_cpu
c_func
(paren
(paren
op_star
id|gpt
)paren
op_member_access_from_pointer
id|partition_entry_array_crc32
)paren
)paren
(brace
id|Dprintk
c_func
(paren
l_string|&quot;GUID Partitition Entry Array CRC check failed.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
op_star
id|gpt
)paren
suffix:semicolon
op_star
id|gpt
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
op_star
id|ptes
)paren
suffix:semicolon
op_star
id|ptes
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We&squot;re done, all&squot;s well */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * compare_gpts() - Search disk for valid GPT headers and PTEs&n; * @pgpt is the primary GPT header&n; * @agpt is the alternate GPT header&n; * @lastlba is the last LBA number&n; * Description: Returns nothing.  Sanity checks pgpt and agpt fields&n; * and prints warnings on discrepancies.&n; * &n; */
r_static
r_void
DECL|function|compare_gpts
id|compare_gpts
c_func
(paren
id|gpt_header
op_star
id|pgpt
comma
id|gpt_header
op_star
id|agpt
comma
id|u64
id|lastlba
)paren
(brace
r_int
id|error_found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgpt
op_logical_or
op_logical_neg
id|agpt
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|le64_to_cpu
c_func
(paren
id|pgpt-&gt;my_lba
)paren
op_ne
id|le64_to_cpu
c_func
(paren
id|agpt-&gt;alternate_lba
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:Primary header LBA != Alt. header alternate_lba&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:%&quot;
id|PRIx64
l_string|&quot; != %&quot;
id|PRIx64
l_string|&quot;&bslash;n&quot;
comma
id|le64_to_cpu
c_func
(paren
id|pgpt-&gt;my_lba
)paren
comma
id|le64_to_cpu
c_func
(paren
id|agpt-&gt;alternate_lba
)paren
)paren
suffix:semicolon
id|error_found
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le64_to_cpu
c_func
(paren
id|pgpt-&gt;alternate_lba
)paren
op_ne
id|le64_to_cpu
c_func
(paren
id|agpt-&gt;my_lba
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:Primary header alternate_lba != Alt. header my_lba&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:%&quot;
id|PRIx64
l_string|&quot; != %&quot;
id|PRIx64
l_string|&quot;&bslash;n&quot;
comma
id|le64_to_cpu
c_func
(paren
id|pgpt-&gt;alternate_lba
)paren
comma
id|le64_to_cpu
c_func
(paren
id|agpt-&gt;my_lba
)paren
)paren
suffix:semicolon
id|error_found
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le64_to_cpu
c_func
(paren
id|pgpt-&gt;first_usable_lba
)paren
op_ne
id|le64_to_cpu
c_func
(paren
id|agpt-&gt;first_usable_lba
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:first_usable_lbas don&squot;t match.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:%&quot;
id|PRIx64
l_string|&quot; != %&quot;
id|PRIx64
l_string|&quot;&bslash;n&quot;
comma
id|le64_to_cpu
c_func
(paren
id|pgpt-&gt;first_usable_lba
)paren
comma
id|le64_to_cpu
c_func
(paren
id|agpt-&gt;first_usable_lba
)paren
)paren
suffix:semicolon
id|error_found
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le64_to_cpu
c_func
(paren
id|pgpt-&gt;last_usable_lba
)paren
op_ne
id|le64_to_cpu
c_func
(paren
id|agpt-&gt;last_usable_lba
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:last_usable_lbas don&squot;t match.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:%&quot;
id|PRIx64
l_string|&quot; != %&quot;
id|PRIx64
l_string|&quot;&bslash;n&quot;
comma
id|le64_to_cpu
c_func
(paren
id|pgpt-&gt;last_usable_lba
)paren
comma
id|le64_to_cpu
c_func
(paren
id|agpt-&gt;last_usable_lba
)paren
)paren
suffix:semicolon
id|error_found
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|efi_guidcmp
c_func
(paren
id|pgpt-&gt;disk_guid
comma
id|agpt-&gt;disk_guid
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:disk_guids don&squot;t match.&bslash;n&quot;
)paren
suffix:semicolon
id|error_found
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|pgpt-&gt;num_partition_entries
)paren
op_ne
id|le32_to_cpu
c_func
(paren
id|agpt-&gt;num_partition_entries
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:num_partition_entries don&squot;t match: &quot;
l_string|&quot;0x%x != 0x%x&bslash;n&quot;
comma
id|le32_to_cpu
c_func
(paren
id|pgpt-&gt;num_partition_entries
)paren
comma
id|le32_to_cpu
c_func
(paren
id|agpt-&gt;num_partition_entries
)paren
)paren
suffix:semicolon
id|error_found
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|pgpt-&gt;sizeof_partition_entry
)paren
op_ne
id|le32_to_cpu
c_func
(paren
id|agpt-&gt;sizeof_partition_entry
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:sizeof_partition_entry values don&squot;t match: &quot;
l_string|&quot;0x%x != 0x%x&bslash;n&quot;
comma
id|le32_to_cpu
c_func
(paren
id|pgpt-&gt;sizeof_partition_entry
)paren
comma
id|le32_to_cpu
c_func
(paren
id|agpt-&gt;sizeof_partition_entry
)paren
)paren
suffix:semicolon
id|error_found
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|pgpt-&gt;partition_entry_array_crc32
)paren
op_ne
id|le32_to_cpu
c_func
(paren
id|agpt-&gt;partition_entry_array_crc32
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:partition_entry_array_crc32 values don&squot;t match: &quot;
l_string|&quot;0x%x != 0x%x&bslash;n&quot;
comma
id|le32_to_cpu
c_func
(paren
id|pgpt-&gt;partition_entry_array_crc32
)paren
comma
id|le32_to_cpu
c_func
(paren
id|agpt-&gt;partition_entry_array_crc32
)paren
)paren
suffix:semicolon
id|error_found
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le64_to_cpu
c_func
(paren
id|pgpt-&gt;alternate_lba
)paren
op_ne
id|lastlba
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:Primary header thinks Alt. header is not at the end of the disk.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:%&quot;
id|PRIx64
l_string|&quot; != %&quot;
id|PRIx64
l_string|&quot;&bslash;n&quot;
comma
id|le64_to_cpu
c_func
(paren
id|pgpt-&gt;alternate_lba
)paren
comma
id|lastlba
)paren
suffix:semicolon
id|error_found
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le64_to_cpu
c_func
(paren
id|agpt-&gt;my_lba
)paren
op_ne
id|lastlba
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:Alternate GPT header not at the end of the disk.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT:%&quot;
id|PRIx64
l_string|&quot; != %&quot;
id|PRIx64
l_string|&quot;&bslash;n&quot;
comma
id|le64_to_cpu
c_func
(paren
id|agpt-&gt;my_lba
)paren
comma
id|lastlba
)paren
suffix:semicolon
id|error_found
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error_found
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GPT: Use GNU Parted to correct GPT errors.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * find_valid_gpt() - Search disk for valid GPT headers and PTEs&n; * @hd&n; * @bdev&n; * @gpt is a GPT header ptr, filled on return.&n; * @ptes is a PTEs ptr, filled on return.&n; * Description: Returns 1 if valid, 0 on error.&n; * If valid, returns pointers to newly allocated GPT header and PTEs.&n; * Validity depends on finding either the Primary GPT header and PTEs valid,&n; * or the Alternate GPT header and PTEs valid, and the PMBR valid.&n; */
r_static
r_int
DECL|function|find_valid_gpt
id|find_valid_gpt
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
id|gpt_header
op_star
op_star
id|gpt
comma
id|gpt_entry
op_star
op_star
id|ptes
)paren
(brace
r_int
id|good_pgpt
op_assign
l_int|0
comma
id|good_agpt
op_assign
l_int|0
comma
id|good_pmbr
op_assign
l_int|0
suffix:semicolon
id|gpt_header
op_star
id|pgpt
op_assign
l_int|NULL
comma
op_star
id|agpt
op_assign
l_int|NULL
suffix:semicolon
id|gpt_entry
op_star
id|pptes
op_assign
l_int|NULL
comma
op_star
id|aptes
op_assign
l_int|NULL
suffix:semicolon
id|legacy_mbr
op_star
id|legacymbr
op_assign
l_int|NULL
suffix:semicolon
id|u64
id|lastlba
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hd
op_logical_or
op_logical_neg
id|bdev
op_logical_or
op_logical_neg
id|gpt
op_logical_or
op_logical_neg
id|ptes
)paren
r_return
l_int|0
suffix:semicolon
id|lastlba
op_assign
id|last_lba
c_func
(paren
id|hd
comma
id|bdev
)paren
suffix:semicolon
id|good_pgpt
op_assign
id|is_gpt_valid
c_func
(paren
id|hd
comma
id|bdev
comma
id|GPT_PRIMARY_PARTITION_TABLE_LBA
comma
op_amp
id|pgpt
comma
op_amp
id|pptes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|good_pgpt
)paren
(brace
id|good_agpt
op_assign
id|is_gpt_valid
c_func
(paren
id|hd
comma
id|bdev
comma
id|le64_to_cpu
c_func
(paren
id|pgpt-&gt;alternate_lba
)paren
comma
op_amp
id|agpt
comma
op_amp
id|aptes
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|good_agpt
)paren
(brace
id|good_agpt
op_assign
id|is_gpt_valid
c_func
(paren
id|hd
comma
id|bdev
comma
id|lastlba
comma
op_amp
id|agpt
comma
op_amp
id|aptes
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|good_agpt
op_assign
id|is_gpt_valid
c_func
(paren
id|hd
comma
id|bdev
comma
id|lastlba
comma
op_amp
id|agpt
comma
op_amp
id|aptes
)paren
suffix:semicolon
)brace
multiline_comment|/* The obviously unsuccessful case */
r_if
c_cond
(paren
op_logical_neg
id|good_pgpt
op_logical_and
op_logical_neg
id|good_agpt
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
multiline_comment|/* This will be added to the EFI Spec. per Intel after v1.02. */
id|legacymbr
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|legacymbr
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|legacymbr
)paren
(brace
id|memset
c_func
(paren
id|legacymbr
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|legacymbr
)paren
)paren
suffix:semicolon
id|read_lba
c_func
(paren
id|hd
comma
id|bdev
comma
l_int|0
comma
(paren
id|u8
op_star
)paren
id|legacymbr
comma
r_sizeof
(paren
op_star
id|legacymbr
)paren
)paren
suffix:semicolon
id|good_pmbr
op_assign
id|is_pmbr_valid
c_func
(paren
id|legacymbr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|legacymbr
)paren
suffix:semicolon
id|legacymbr
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Failure due to bad PMBR */
r_if
c_cond
(paren
(paren
id|good_pgpt
op_logical_or
id|good_agpt
)paren
op_logical_and
op_logical_neg
id|good_pmbr
op_logical_and
op_logical_neg
id|force_gpt
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  Warning: Disk has a valid GPT signature &quot;
l_string|&quot;but invalid PMBR.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  Assuming this disk is *not* a GPT disk anymore.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  Use gpt kernel option to override.  &quot;
l_string|&quot;Use GNU Parted to correct disk.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
multiline_comment|/* Would fail due to bad PMBR, but force GPT anyhow */
r_if
c_cond
(paren
(paren
id|good_pgpt
op_logical_or
id|good_agpt
)paren
op_logical_and
op_logical_neg
id|good_pmbr
op_logical_and
id|force_gpt
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  Warning: Disk has a valid GPT signature but &quot;
l_string|&quot;invalid PMBR.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  Use GNU Parted to correct disk.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  gpt option taken, disk treated as GPT.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|compare_gpts
c_func
(paren
id|pgpt
comma
id|agpt
comma
id|lastlba
)paren
suffix:semicolon
multiline_comment|/* The good cases */
r_if
c_cond
(paren
id|good_pgpt
op_logical_and
(paren
id|good_pmbr
op_logical_or
id|force_gpt
)paren
)paren
(brace
op_star
id|gpt
op_assign
id|pgpt
suffix:semicolon
op_star
id|ptes
op_assign
id|pptes
suffix:semicolon
r_if
c_cond
(paren
id|agpt
)paren
(brace
id|kfree
c_func
(paren
id|agpt
)paren
suffix:semicolon
id|agpt
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aptes
)paren
(brace
id|kfree
c_func
(paren
id|aptes
)paren
suffix:semicolon
id|aptes
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|good_agpt
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Alternate GPT is invalid, &quot;
l_string|&quot;using primary GPT.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|good_agpt
op_logical_and
(paren
id|good_pmbr
op_logical_or
id|force_gpt
)paren
)paren
(brace
op_star
id|gpt
op_assign
id|agpt
suffix:semicolon
op_star
id|ptes
op_assign
id|aptes
suffix:semicolon
r_if
c_cond
(paren
id|pgpt
)paren
(brace
id|kfree
c_func
(paren
id|pgpt
)paren
suffix:semicolon
id|pgpt
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pptes
)paren
(brace
id|kfree
c_func
(paren
id|pptes
)paren
suffix:semicolon
id|pptes
op_assign
l_int|NULL
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Primary GPT is invalid, using alternate GPT.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|fail
suffix:colon
r_if
c_cond
(paren
id|pgpt
)paren
(brace
id|kfree
c_func
(paren
id|pgpt
)paren
suffix:semicolon
id|pgpt
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|agpt
)paren
(brace
id|kfree
c_func
(paren
id|agpt
)paren
suffix:semicolon
id|agpt
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pptes
)paren
(brace
id|kfree
c_func
(paren
id|pptes
)paren
suffix:semicolon
id|pptes
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aptes
)paren
(brace
id|kfree
c_func
(paren
id|aptes
)paren
suffix:semicolon
id|aptes
op_assign
l_int|NULL
suffix:semicolon
)brace
op_star
id|gpt
op_assign
l_int|NULL
suffix:semicolon
op_star
id|ptes
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * add_gpt_partitions(struct gendisk *hd, struct block_device *bdev,&n; * @hd&n; * @bdev&n; *&n; * Description: Create devices for each entry in the GUID Partition Table&n; * Entries.&n; *&n; * We do not create a Linux partition for GPT, but&n; * only for the actual data partitions.&n; * Returns:&n; * -1 if unable to read the partition table&n; *  0 if this isn&squot;t our partition table&n; *  1 if successful&n; *&n; */
r_static
r_int
DECL|function|add_gpt_partitions
id|add_gpt_partitions
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
id|nextminor
)paren
(brace
id|gpt_header
op_star
id|gpt
op_assign
l_int|NULL
suffix:semicolon
id|gpt_entry
op_star
id|ptes
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|i
suffix:semicolon
r_int
id|max_p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hd
op_logical_or
op_logical_neg
id|bdev
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|find_valid_gpt
c_func
(paren
id|hd
comma
id|bdev
comma
op_amp
id|gpt
comma
op_amp
id|ptes
)paren
op_logical_or
op_logical_neg
id|gpt
op_logical_or
op_logical_neg
id|ptes
)paren
(brace
r_if
c_cond
(paren
id|gpt
)paren
(brace
id|kfree
c_func
(paren
id|gpt
)paren
suffix:semicolon
id|gpt
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ptes
)paren
(brace
id|kfree
c_func
(paren
id|ptes
)paren
suffix:semicolon
id|ptes
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|Dprintk
c_func
(paren
l_string|&quot;GUID Partition Table is valid!  Yea!&bslash;n&quot;
)paren
suffix:semicolon
id|max_p
op_assign
(paren
l_int|1
op_lshift
id|hd-&gt;minor_shift
)paren
op_minus
l_int|1
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
id|le32_to_cpu
c_func
(paren
id|gpt-&gt;num_partition_entries
)paren
op_logical_and
id|i
OL
id|max_p
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|efi_guidcmp
c_func
(paren
id|ptes
(braket
id|i
)braket
dot
id|partition_type_guid
comma
id|NULL_GUID
)paren
)paren
r_continue
suffix:semicolon
id|add_gd_partition
c_func
(paren
id|hd
comma
id|nextminor
op_plus
id|i
comma
id|le64_to_cpu
c_func
(paren
id|ptes
(braket
id|i
)braket
dot
id|starting_lba
)paren
comma
(paren
id|le64_to_cpu
c_func
(paren
id|ptes
(braket
id|i
)braket
dot
id|ending_lba
)paren
op_minus
id|le64_to_cpu
c_func
(paren
id|ptes
(braket
id|i
)braket
dot
id|starting_lba
)paren
op_plus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* If there&squot;s this is a RAID volume, tell md */
macro_line|#if CONFIG_BLK_DEV_MD
r_if
c_cond
(paren
op_logical_neg
id|efi_guidcmp
c_func
(paren
id|ptes
(braket
id|i
)braket
dot
id|partition_type_guid
comma
id|PARTITION_LINUX_RAID_GUID
)paren
)paren
(brace
id|md_autodetect_dev
c_func
(paren
id|mk_kdev
c_func
(paren
id|hd-&gt;major
comma
id|nextminor
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
id|kfree
c_func
(paren
id|ptes
)paren
suffix:semicolon
id|ptes
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|gpt
)paren
suffix:semicolon
id|gpt
op_assign
l_int|NULL
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
multiline_comment|/**&n; * efi_partition(): EFI GPT partition handling entry function&n; * @hd&n; * @bdev&n; * @first_sector: unused&n; * @first_part_minor: minor number assigned to first GPT partition found&n; *&n; * Description: called from check.c, if the disk contains GPT&n; * partitions, sets up partition entries in the kernel.&n; *&n; * If the first block on the disk is a legacy MBR,&n; * it will get handled by msdos_partition().&n; * If it&squot;s a Protective MBR, we&squot;ll handle it here.&n; *&n; * set_blocksize() calls are necessary to be able to read&n; * a disk with an odd number of 512-byte sectors, as the&n; * default BLOCK_SIZE of 1024 bytes won&squot;t let that last&n; * sector be read otherwise.&n; *&n; * Returns:&n; * -1 if unable to read the partition table&n; *  0 if this isn&squot;t our partitoin table&n; *  1 if successful&n; */
r_int
DECL|function|efi_partition
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
(brace
id|kdev_t
id|dev
op_assign
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
)paren
suffix:semicolon
r_int
id|hardblocksize
op_assign
id|bdev_hardsect_size
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_int
id|orig_blksize_size
op_assign
id|block_size
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Need to change the block size that the block layer uses */
r_if
c_cond
(paren
id|orig_blksize_size
op_ne
id|hardblocksize
)paren
id|set_blocksize
c_func
(paren
id|dev
comma
id|hardblocksize
)paren
suffix:semicolon
id|rc
op_assign
id|add_gpt_partitions
c_func
(paren
id|hd
comma
id|bdev
comma
id|first_part_minor
)paren
suffix:semicolon
multiline_comment|/* change back */
r_if
c_cond
(paren
id|orig_blksize_size
op_ne
id|hardblocksize
)paren
id|set_blocksize
c_func
(paren
id|dev
comma
id|orig_blksize_size
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
