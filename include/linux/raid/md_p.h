multiline_comment|/*&n;   md_p.h : physical layout of Linux RAID devices&n;          Copyright (C) 1996-98 Ingo Molnar, Gadi Oxman&n;&t;  &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
macro_line|#ifndef _MD_P_H
DECL|macro|_MD_P_H
mdefine_line|#define _MD_P_H
multiline_comment|/*&n; * RAID superblock.&n; *&n; * The RAID superblock maintains some statistics on each RAID configuration.&n; * Each real device in the RAID set contains it near the end of the device.&n; * Some of the ideas are copied from the ext2fs implementation.&n; *&n; * We currently use 4096 bytes as follows:&n; *&n; *&t;word offset&t;function&n; *&n; *&t;   0  -    31&t;Constant generic RAID device information.&n; *        32  -    63   Generic state information.&n; *&t;  64  -   127&t;Personality specific information.&n; *&t; 128  -   511&t;12 32-words descriptors of the disks in the raid set.&n; *&t; 512  -   911&t;Reserved.&n; *&t; 912  -  1023&t;Disk specific descriptor.&n; */
multiline_comment|/*&n; * If x is the real device size in bytes, we return an apparent size of:&n; *&n; *&t;y = (x &amp; ~(MD_RESERVED_BYTES - 1)) - MD_RESERVED_BYTES&n; *&n; * and place the 4kB superblock at offset y.&n; */
DECL|macro|MD_RESERVED_BYTES
mdefine_line|#define MD_RESERVED_BYTES&t;&t;(64 * 1024)
DECL|macro|MD_RESERVED_SECTORS
mdefine_line|#define MD_RESERVED_SECTORS&t;&t;(MD_RESERVED_BYTES / 512)
DECL|macro|MD_RESERVED_BLOCKS
mdefine_line|#define MD_RESERVED_BLOCKS&t;&t;(MD_RESERVED_BYTES / BLOCK_SIZE)
DECL|macro|MD_NEW_SIZE_SECTORS
mdefine_line|#define MD_NEW_SIZE_SECTORS(x)&t;&t;((x &amp; ~(MD_RESERVED_SECTORS - 1)) - MD_RESERVED_SECTORS)
DECL|macro|MD_NEW_SIZE_BLOCKS
mdefine_line|#define MD_NEW_SIZE_BLOCKS(x)&t;&t;((x &amp; ~(MD_RESERVED_BLOCKS - 1)) - MD_RESERVED_BLOCKS)
DECL|macro|MD_SB_BYTES
mdefine_line|#define MD_SB_BYTES&t;&t;&t;4096
DECL|macro|MD_SB_WORDS
mdefine_line|#define MD_SB_WORDS&t;&t;&t;(MD_SB_BYTES / 4)
DECL|macro|MD_SB_BLOCKS
mdefine_line|#define MD_SB_BLOCKS&t;&t;&t;(MD_SB_BYTES / BLOCK_SIZE)
DECL|macro|MD_SB_SECTORS
mdefine_line|#define MD_SB_SECTORS&t;&t;&t;(MD_SB_BYTES / 512)
multiline_comment|/*&n; * The following are counted in 32-bit words&n; */
DECL|macro|MD_SB_GENERIC_OFFSET
mdefine_line|#define&t;MD_SB_GENERIC_OFFSET&t;&t;0
DECL|macro|MD_SB_PERSONALITY_OFFSET
mdefine_line|#define MD_SB_PERSONALITY_OFFSET&t;64
DECL|macro|MD_SB_DISKS_OFFSET
mdefine_line|#define MD_SB_DISKS_OFFSET&t;&t;128
DECL|macro|MD_SB_DESCRIPTOR_OFFSET
mdefine_line|#define MD_SB_DESCRIPTOR_OFFSET&t;&t;992
DECL|macro|MD_SB_GENERIC_CONSTANT_WORDS
mdefine_line|#define MD_SB_GENERIC_CONSTANT_WORDS&t;32
DECL|macro|MD_SB_GENERIC_STATE_WORDS
mdefine_line|#define MD_SB_GENERIC_STATE_WORDS&t;32
DECL|macro|MD_SB_GENERIC_WORDS
mdefine_line|#define MD_SB_GENERIC_WORDS&t;&t;(MD_SB_GENERIC_CONSTANT_WORDS + MD_SB_GENERIC_STATE_WORDS)
DECL|macro|MD_SB_PERSONALITY_WORDS
mdefine_line|#define MD_SB_PERSONALITY_WORDS&t;&t;64
DECL|macro|MD_SB_DESCRIPTOR_WORDS
mdefine_line|#define MD_SB_DESCRIPTOR_WORDS&t;&t;32
DECL|macro|MD_SB_DISKS
mdefine_line|#define MD_SB_DISKS&t;&t;&t;27
DECL|macro|MD_SB_DISKS_WORDS
mdefine_line|#define MD_SB_DISKS_WORDS&t;&t;(MD_SB_DISKS*MD_SB_DESCRIPTOR_WORDS)
DECL|macro|MD_SB_RESERVED_WORDS
mdefine_line|#define MD_SB_RESERVED_WORDS&t;&t;(1024 - MD_SB_GENERIC_WORDS - MD_SB_PERSONALITY_WORDS - MD_SB_DISKS_WORDS - MD_SB_DESCRIPTOR_WORDS)
DECL|macro|MD_SB_EQUAL_WORDS
mdefine_line|#define MD_SB_EQUAL_WORDS&t;&t;(MD_SB_GENERIC_WORDS + MD_SB_PERSONALITY_WORDS + MD_SB_DISKS_WORDS)
multiline_comment|/*&n; * Device &quot;operational&quot; state bits&n; */
DECL|macro|MD_DISK_FAULTY
mdefine_line|#define MD_DISK_FAULTY&t;&t;0 /* disk is faulty / operational */
DECL|macro|MD_DISK_ACTIVE
mdefine_line|#define MD_DISK_ACTIVE&t;&t;1 /* disk is running or spare disk */
DECL|macro|MD_DISK_SYNC
mdefine_line|#define MD_DISK_SYNC&t;&t;2 /* disk is in sync with the raid set */
DECL|macro|MD_DISK_REMOVED
mdefine_line|#define MD_DISK_REMOVED&t;&t;3 /* disk is in sync with the raid set */
DECL|struct|mdp_device_descriptor_s
r_typedef
r_struct
id|mdp_device_descriptor_s
(brace
DECL|member|number
id|__u32
id|number
suffix:semicolon
multiline_comment|/* 0 Device number in the entire set&t;      */
DECL|member|major
id|__u32
id|major
suffix:semicolon
multiline_comment|/* 1 Device major number&t;&t;      */
DECL|member|minor
id|__u32
id|minor
suffix:semicolon
multiline_comment|/* 2 Device minor number&t;&t;      */
DECL|member|raid_disk
id|__u32
id|raid_disk
suffix:semicolon
multiline_comment|/* 3 The role of the device in the raid set   */
DECL|member|state
id|__u32
id|state
suffix:semicolon
multiline_comment|/* 4 Operational state&t;&t;&t;      */
DECL|member|reserved
id|__u32
id|reserved
(braket
id|MD_SB_DESCRIPTOR_WORDS
op_minus
l_int|5
)braket
suffix:semicolon
DECL|typedef|mdp_disk_t
)brace
id|mdp_disk_t
suffix:semicolon
DECL|macro|MD_SB_MAGIC
mdefine_line|#define MD_SB_MAGIC&t;&t;0xa92b4efc
multiline_comment|/*&n; * Superblock state bits&n; */
DECL|macro|MD_SB_CLEAN
mdefine_line|#define MD_SB_CLEAN&t;&t;0
DECL|macro|MD_SB_ERRORS
mdefine_line|#define MD_SB_ERRORS&t;&t;1
DECL|struct|mdp_superblock_s
r_typedef
r_struct
id|mdp_superblock_s
(brace
multiline_comment|/*&n;&t; * Constant generic information&n;&t; */
DECL|member|md_magic
id|__u32
id|md_magic
suffix:semicolon
multiline_comment|/*  0 MD identifier &t;&t;&t;      */
DECL|member|major_version
id|__u32
id|major_version
suffix:semicolon
multiline_comment|/*  1 major version to which the set conforms */
DECL|member|minor_version
id|__u32
id|minor_version
suffix:semicolon
multiline_comment|/*  2 minor version ...&t;&t;&t;      */
DECL|member|patch_version
id|__u32
id|patch_version
suffix:semicolon
multiline_comment|/*  3 patchlevel version ...&t;&t;      */
DECL|member|gvalid_words
id|__u32
id|gvalid_words
suffix:semicolon
multiline_comment|/*  4 Number of used words in this section    */
DECL|member|set_uuid0
id|__u32
id|set_uuid0
suffix:semicolon
multiline_comment|/*  5 Raid set identifier&t;&t;      */
DECL|member|ctime
id|__u32
id|ctime
suffix:semicolon
multiline_comment|/*  6 Creation time&t;&t;&t;      */
DECL|member|level
id|__u32
id|level
suffix:semicolon
multiline_comment|/*  7 Raid personality&t;&t;&t;      */
DECL|member|size
id|__u32
id|size
suffix:semicolon
multiline_comment|/*  8 Apparent size of each individual disk   */
DECL|member|nr_disks
id|__u32
id|nr_disks
suffix:semicolon
multiline_comment|/*  9 total disks in the raid set&t;      */
DECL|member|raid_disks
id|__u32
id|raid_disks
suffix:semicolon
multiline_comment|/* 10 disks in a fully functional raid set    */
DECL|member|md_minor
id|__u32
id|md_minor
suffix:semicolon
multiline_comment|/* 11 preferred MD minor device number&t;      */
DECL|member|not_persistent
id|__u32
id|not_persistent
suffix:semicolon
multiline_comment|/* 12 does it have a persistent superblock    */
DECL|member|set_uuid1
id|__u32
id|set_uuid1
suffix:semicolon
multiline_comment|/* 13 Raid set identifier #2&t;&t;      */
DECL|member|set_uuid2
id|__u32
id|set_uuid2
suffix:semicolon
multiline_comment|/* 14 Raid set identifier #3&t;&t;      */
DECL|member|set_uuid3
id|__u32
id|set_uuid3
suffix:semicolon
multiline_comment|/* 15 Raid set identifier #4&t;&t;      */
DECL|member|gstate_creserved
id|__u32
id|gstate_creserved
(braket
id|MD_SB_GENERIC_CONSTANT_WORDS
op_minus
l_int|16
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Generic state information&n;&t; */
DECL|member|utime
id|__u32
id|utime
suffix:semicolon
multiline_comment|/*  0 Superblock update time&t;&t;      */
DECL|member|state
id|__u32
id|state
suffix:semicolon
multiline_comment|/*  1 State bits (clean, ...)&t;&t;      */
DECL|member|active_disks
id|__u32
id|active_disks
suffix:semicolon
multiline_comment|/*  2 Number of currently active disks&t;      */
DECL|member|working_disks
id|__u32
id|working_disks
suffix:semicolon
multiline_comment|/*  3 Number of working disks&t;&t;      */
DECL|member|failed_disks
id|__u32
id|failed_disks
suffix:semicolon
multiline_comment|/*  4 Number of failed disks&t;&t;      */
DECL|member|spare_disks
id|__u32
id|spare_disks
suffix:semicolon
multiline_comment|/*  5 Number of spare disks&t;&t;      */
DECL|member|sb_csum
id|__u32
id|sb_csum
suffix:semicolon
multiline_comment|/*  6 checksum of the whole superblock        */
macro_line|#ifdef __BIG_ENDIAN
DECL|member|events_hi
id|__u32
id|events_hi
suffix:semicolon
multiline_comment|/*  7 high-order of superblock update count   */
DECL|member|events_lo
id|__u32
id|events_lo
suffix:semicolon
multiline_comment|/*  8 low-order of superblock update count    */
macro_line|#else
DECL|member|events_lo
id|__u32
id|events_lo
suffix:semicolon
multiline_comment|/*  7 low-order of superblock update count    */
DECL|member|events_hi
id|__u32
id|events_hi
suffix:semicolon
multiline_comment|/*  8 high-order of superblock update count   */
macro_line|#endif
DECL|member|gstate_sreserved
id|__u32
id|gstate_sreserved
(braket
id|MD_SB_GENERIC_STATE_WORDS
op_minus
l_int|9
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Personality information&n;&t; */
DECL|member|layout
id|__u32
id|layout
suffix:semicolon
multiline_comment|/*  0 the array&squot;s physical layout&t;      */
DECL|member|chunk_size
id|__u32
id|chunk_size
suffix:semicolon
multiline_comment|/*  1 chunk size in bytes&t;&t;      */
DECL|member|root_pv
id|__u32
id|root_pv
suffix:semicolon
multiline_comment|/*  2 LV root PV */
DECL|member|root_block
id|__u32
id|root_block
suffix:semicolon
multiline_comment|/*  3 LV root block */
DECL|member|pstate_reserved
id|__u32
id|pstate_reserved
(braket
id|MD_SB_PERSONALITY_WORDS
op_minus
l_int|4
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Disks information&n;&t; */
DECL|member|disks
id|mdp_disk_t
id|disks
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Reserved&n;&t; */
DECL|member|reserved
id|__u32
id|reserved
(braket
id|MD_SB_RESERVED_WORDS
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Active descriptor&n;&t; */
DECL|member|this_disk
id|mdp_disk_t
id|this_disk
suffix:semicolon
DECL|typedef|mdp_super_t
)brace
id|mdp_super_t
suffix:semicolon
DECL|function|md_event
r_static
r_inline
id|__u64
id|md_event
c_func
(paren
id|mdp_super_t
op_star
id|sb
)paren
(brace
id|__u64
id|ev
op_assign
id|sb-&gt;events_hi
suffix:semicolon
r_return
(paren
id|ev
op_lshift
l_int|32
)paren
op_or
id|sb-&gt;events_lo
suffix:semicolon
)brace
macro_line|#endif 
eof
