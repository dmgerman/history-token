macro_line|#ifndef _LINUX_MSDOS_FS_H
DECL|macro|_LINUX_MSDOS_FS_H
mdefine_line|#define _LINUX_MSDOS_FS_H
multiline_comment|/*&n; * The MS-DOS filesystem constants/structures&n; */
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|SECTOR_SIZE
mdefine_line|#define SECTOR_SIZE&t;512&t;&t;/* sector size (bytes) */
DECL|macro|SECTOR_BITS
mdefine_line|#define SECTOR_BITS&t;9&t;&t;/* log2(SECTOR_SIZE) */
DECL|macro|MSDOS_DPB
mdefine_line|#define MSDOS_DPB&t;(MSDOS_DPS)&t;/* dir entries per block */
DECL|macro|MSDOS_DPB_BITS
mdefine_line|#define MSDOS_DPB_BITS&t;4&t;&t;/* log2(MSDOS_DPB) */
DECL|macro|MSDOS_DPS
mdefine_line|#define MSDOS_DPS&t;(SECTOR_SIZE / sizeof(struct msdos_dir_entry))
DECL|macro|MSDOS_DPS_BITS
mdefine_line|#define MSDOS_DPS_BITS&t;4&t;&t;/* log2(MSDOS_DPS) */
DECL|macro|CF_LE_W
mdefine_line|#define CF_LE_W(v)&t;le16_to_cpu(v)
DECL|macro|CF_LE_L
mdefine_line|#define CF_LE_L(v)&t;le32_to_cpu(v)
DECL|macro|CT_LE_W
mdefine_line|#define CT_LE_W(v)&t;cpu_to_le16(v)
DECL|macro|CT_LE_L
mdefine_line|#define CT_LE_L(v)&t;cpu_to_le32(v)
DECL|macro|MSDOS_SUPER_MAGIC
mdefine_line|#define MSDOS_SUPER_MAGIC 0x4d44 /* MD */
DECL|macro|MSDOS_ROOT_INO
mdefine_line|#define MSDOS_ROOT_INO&t;1&t;/* == MINIX_ROOT_INO */
DECL|macro|MSDOS_DIR_BITS
mdefine_line|#define MSDOS_DIR_BITS&t;5&t;/* log2(sizeof(struct msdos_dir_entry)) */
multiline_comment|/* directory limit */
DECL|macro|FAT_MAX_DIR_ENTRIES
mdefine_line|#define FAT_MAX_DIR_ENTRIES&t;(65536)
DECL|macro|FAT_MAX_DIR_SIZE
mdefine_line|#define FAT_MAX_DIR_SIZE&t;(FAT_MAX_DIR_ENTRIES &lt;&lt; MSDOS_DIR_BITS)
DECL|macro|ATTR_NONE
mdefine_line|#define ATTR_NONE&t;0&t;/* no attribute bits */
DECL|macro|ATTR_RO
mdefine_line|#define ATTR_RO&t;&t;1&t;/* read-only */
DECL|macro|ATTR_HIDDEN
mdefine_line|#define ATTR_HIDDEN&t;2&t;/* hidden */
DECL|macro|ATTR_SYS
mdefine_line|#define ATTR_SYS&t;4&t;/* system */
DECL|macro|ATTR_VOLUME
mdefine_line|#define ATTR_VOLUME&t;8&t;/* volume label */
DECL|macro|ATTR_DIR
mdefine_line|#define ATTR_DIR&t;16&t;/* directory */
DECL|macro|ATTR_ARCH
mdefine_line|#define ATTR_ARCH&t;32&t;/* archived */
multiline_comment|/* attribute bits that are copied &quot;as is&quot; */
DECL|macro|ATTR_UNUSED
mdefine_line|#define ATTR_UNUSED&t;(ATTR_VOLUME | ATTR_ARCH | ATTR_SYS | ATTR_HIDDEN)
multiline_comment|/* bits that are used by the Windows 95/Windows NT extended FAT */
DECL|macro|ATTR_EXT
mdefine_line|#define ATTR_EXT&t;(ATTR_RO | ATTR_HIDDEN | ATTR_SYS | ATTR_VOLUME)
DECL|macro|CASE_LOWER_BASE
mdefine_line|#define CASE_LOWER_BASE&t;8&t;/* base is lower case */
DECL|macro|CASE_LOWER_EXT
mdefine_line|#define CASE_LOWER_EXT&t;16&t;/* extension is lower case */
DECL|macro|DELETED_FLAG
mdefine_line|#define DELETED_FLAG&t;0xe5&t;/* marks file as deleted when in name[0] */
DECL|macro|IS_FREE
mdefine_line|#define IS_FREE(n)&t;(!*(n) || *(n) == DELETED_FLAG)
multiline_comment|/* valid file mode bits */
DECL|macro|MSDOS_VALID_MODE
mdefine_line|#define MSDOS_VALID_MODE (S_IFREG | S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO)
multiline_comment|/* Convert attribute bits and a mask to the UNIX mode. */
DECL|macro|MSDOS_MKMODE
mdefine_line|#define MSDOS_MKMODE(a, m) (m &amp; (a &amp; ATTR_RO ? S_IRUGO|S_IXUGO : S_IRWXUGO))
multiline_comment|/* Convert the UNIX mode to MS-DOS attribute bits. */
DECL|macro|MSDOS_MKATTR
mdefine_line|#define MSDOS_MKATTR(m)&t;((m &amp; S_IWUGO) ? ATTR_NONE : ATTR_RO)
DECL|macro|MSDOS_NAME
mdefine_line|#define MSDOS_NAME&t;11&t;/* maximum name length */
DECL|macro|MSDOS_LONGNAME
mdefine_line|#define MSDOS_LONGNAME&t;256&t;/* maximum name length */
DECL|macro|MSDOS_SLOTS
mdefine_line|#define MSDOS_SLOTS&t;21&t;/* max # of slots for short and long names */
DECL|macro|MSDOS_DOT
mdefine_line|#define MSDOS_DOT&t;&quot;.          &quot;&t;/* &quot;.&quot;, padded to MSDOS_NAME chars */
DECL|macro|MSDOS_DOTDOT
mdefine_line|#define MSDOS_DOTDOT&t;&quot;..         &quot;&t;/* &quot;..&quot;, padded to MSDOS_NAME chars */
multiline_comment|/* media of boot sector */
DECL|macro|FAT_VALID_MEDIA
mdefine_line|#define FAT_VALID_MEDIA(x)&t;((0xF8 &lt;= (x) &amp;&amp; (x) &lt;= 0xFF) || (x) == 0xF0)
DECL|macro|FAT_FIRST_ENT
mdefine_line|#define FAT_FIRST_ENT(s, x)&t;((MSDOS_SB(s)-&gt;fat_bits == 32 ? 0x0FFFFF00 : &bslash;&n;&t;MSDOS_SB(s)-&gt;fat_bits == 16 ? 0xFF00 : 0xF00) | (x))
multiline_comment|/* start of data cluster&squot;s entry (number of reserved clusters) */
DECL|macro|FAT_START_ENT
mdefine_line|#define FAT_START_ENT&t;2
multiline_comment|/* maximum number of clusters */
DECL|macro|MAX_FAT12
mdefine_line|#define MAX_FAT12&t;0xFF4
DECL|macro|MAX_FAT16
mdefine_line|#define MAX_FAT16&t;0xFFF4
DECL|macro|MAX_FAT32
mdefine_line|#define MAX_FAT32&t;0x0FFFFFF6
DECL|macro|MAX_FAT
mdefine_line|#define MAX_FAT(s)&t;(MSDOS_SB(s)-&gt;fat_bits == 32 ? MAX_FAT32 : &bslash;&n;&t;MSDOS_SB(s)-&gt;fat_bits == 16 ? MAX_FAT16 : MAX_FAT12)
multiline_comment|/* bad cluster mark */
DECL|macro|BAD_FAT12
mdefine_line|#define BAD_FAT12&t;0xFF7
DECL|macro|BAD_FAT16
mdefine_line|#define BAD_FAT16&t;0xFFF7
DECL|macro|BAD_FAT32
mdefine_line|#define BAD_FAT32&t;0x0FFFFFF7
DECL|macro|BAD_FAT
mdefine_line|#define BAD_FAT(s)&t;(MSDOS_SB(s)-&gt;fat_bits == 32 ? BAD_FAT32 : &bslash;&n;&t;MSDOS_SB(s)-&gt;fat_bits == 16 ? BAD_FAT16 : BAD_FAT12)
multiline_comment|/* standard EOF */
DECL|macro|EOF_FAT12
mdefine_line|#define EOF_FAT12&t;0xFFF
DECL|macro|EOF_FAT16
mdefine_line|#define EOF_FAT16&t;0xFFFF
DECL|macro|EOF_FAT32
mdefine_line|#define EOF_FAT32&t;0x0FFFFFFF
DECL|macro|EOF_FAT
mdefine_line|#define EOF_FAT(s)&t;(MSDOS_SB(s)-&gt;fat_bits == 32 ? EOF_FAT32 : &bslash;&n;&t;MSDOS_SB(s)-&gt;fat_bits == 16 ? EOF_FAT16 : EOF_FAT12)
DECL|macro|FAT_ENT_FREE
mdefine_line|#define FAT_ENT_FREE&t;(0)
DECL|macro|FAT_ENT_BAD
mdefine_line|#define FAT_ENT_BAD&t;(BAD_FAT32)
DECL|macro|FAT_ENT_EOF
mdefine_line|#define FAT_ENT_EOF&t;(EOF_FAT32)
DECL|macro|FAT_FSINFO_SIG1
mdefine_line|#define FAT_FSINFO_SIG1&t;0x41615252
DECL|macro|FAT_FSINFO_SIG2
mdefine_line|#define FAT_FSINFO_SIG2&t;0x61417272
DECL|macro|IS_FSINFO
mdefine_line|#define IS_FSINFO(x)&t;(le32_to_cpu((x)-&gt;signature1) == FAT_FSINFO_SIG1 &bslash;&n;&t;&t;&t; &amp;&amp; le32_to_cpu((x)-&gt;signature2) == FAT_FSINFO_SIG2)
multiline_comment|/*&n; * ioctl commands&n; */
DECL|macro|VFAT_IOCTL_READDIR_BOTH
mdefine_line|#define&t;VFAT_IOCTL_READDIR_BOTH&t;&t;_IOR(&squot;r&squot;, 1, struct dirent [2])
DECL|macro|VFAT_IOCTL_READDIR_SHORT
mdefine_line|#define&t;VFAT_IOCTL_READDIR_SHORT&t;_IOR(&squot;r&squot;, 2, struct dirent [2])
multiline_comment|/*&n; * vfat shortname flags&n; */
DECL|macro|VFAT_SFN_DISPLAY_LOWER
mdefine_line|#define VFAT_SFN_DISPLAY_LOWER&t;0x0001 /* convert to lowercase for display */
DECL|macro|VFAT_SFN_DISPLAY_WIN95
mdefine_line|#define VFAT_SFN_DISPLAY_WIN95&t;0x0002 /* emulate win95 rule for display */
DECL|macro|VFAT_SFN_DISPLAY_WINNT
mdefine_line|#define VFAT_SFN_DISPLAY_WINNT&t;0x0004 /* emulate winnt rule for display */
DECL|macro|VFAT_SFN_CREATE_WIN95
mdefine_line|#define VFAT_SFN_CREATE_WIN95&t;0x0100 /* emulate win95 rule for create */
DECL|macro|VFAT_SFN_CREATE_WINNT
mdefine_line|#define VFAT_SFN_CREATE_WINNT&t;0x0200 /* emulate winnt rule for create */
DECL|struct|fat_boot_sector
r_struct
id|fat_boot_sector
(brace
DECL|member|ignored
id|__u8
id|ignored
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Boot strap short or near jump */
DECL|member|system_id
id|__u8
id|system_id
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Name - can be used to special case&n;&t;&t;&t;&t;   partition manager volumes */
DECL|member|sector_size
id|__u8
id|sector_size
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* bytes per logical sector */
DECL|member|sec_per_clus
id|__u8
id|sec_per_clus
suffix:semicolon
multiline_comment|/* sectors/cluster */
DECL|member|reserved
id|__le16
id|reserved
suffix:semicolon
multiline_comment|/* reserved sectors */
DECL|member|fats
id|__u8
id|fats
suffix:semicolon
multiline_comment|/* number of FATs */
DECL|member|dir_entries
id|__u8
id|dir_entries
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* root directory entries */
DECL|member|sectors
id|__u8
id|sectors
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* number of sectors */
DECL|member|media
id|__u8
id|media
suffix:semicolon
multiline_comment|/* media code */
DECL|member|fat_length
id|__le16
id|fat_length
suffix:semicolon
multiline_comment|/* sectors/FAT */
DECL|member|secs_track
id|__le16
id|secs_track
suffix:semicolon
multiline_comment|/* sectors per track */
DECL|member|heads
id|__le16
id|heads
suffix:semicolon
multiline_comment|/* number of heads */
DECL|member|hidden
id|__le32
id|hidden
suffix:semicolon
multiline_comment|/* hidden sectors (unused) */
DECL|member|total_sect
id|__le32
id|total_sect
suffix:semicolon
multiline_comment|/* number of sectors (if sectors == 0) */
multiline_comment|/* The following fields are only used by FAT32 */
DECL|member|fat32_length
id|__le32
id|fat32_length
suffix:semicolon
multiline_comment|/* sectors/FAT */
DECL|member|flags
id|__le16
id|flags
suffix:semicolon
multiline_comment|/* bit 8: fat mirroring, low 4: active fat */
DECL|member|version
id|__u8
id|version
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* major, minor filesystem version */
DECL|member|root_cluster
id|__le32
id|root_cluster
suffix:semicolon
multiline_comment|/* first cluster in root directory */
DECL|member|info_sector
id|__le16
id|info_sector
suffix:semicolon
multiline_comment|/* filesystem info sector */
DECL|member|backup_boot
id|__le16
id|backup_boot
suffix:semicolon
multiline_comment|/* backup boot sector */
DECL|member|reserved2
id|__le16
id|reserved2
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Unused */
)brace
suffix:semicolon
DECL|struct|fat_boot_fsinfo
r_struct
id|fat_boot_fsinfo
(brace
DECL|member|signature1
id|__le32
id|signature1
suffix:semicolon
multiline_comment|/* 0x41615252L */
DECL|member|reserved1
id|__le32
id|reserved1
(braket
l_int|120
)braket
suffix:semicolon
multiline_comment|/* Nothing as far as I can tell */
DECL|member|signature2
id|__le32
id|signature2
suffix:semicolon
multiline_comment|/* 0x61417272L */
DECL|member|free_clusters
id|__le32
id|free_clusters
suffix:semicolon
multiline_comment|/* Free cluster count.  -1 if unknown */
DECL|member|next_cluster
id|__le32
id|next_cluster
suffix:semicolon
multiline_comment|/* Most recently allocated cluster */
DECL|member|reserved2
id|__le32
id|reserved2
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|msdos_dir_entry
r_struct
id|msdos_dir_entry
(brace
DECL|member|name
DECL|member|ext
id|__u8
id|name
(braket
l_int|8
)braket
comma
id|ext
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* name and extension */
DECL|member|attr
id|__u8
id|attr
suffix:semicolon
multiline_comment|/* attribute bits */
DECL|member|lcase
id|__u8
id|lcase
suffix:semicolon
multiline_comment|/* Case for base and extension */
DECL|member|ctime_ms
id|__u8
id|ctime_ms
suffix:semicolon
multiline_comment|/* Creation time, milliseconds */
DECL|member|ctime
id|__le16
id|ctime
suffix:semicolon
multiline_comment|/* Creation time */
DECL|member|cdate
id|__le16
id|cdate
suffix:semicolon
multiline_comment|/* Creation date */
DECL|member|adate
id|__le16
id|adate
suffix:semicolon
multiline_comment|/* Last access date */
DECL|member|starthi
id|__le16
id|starthi
suffix:semicolon
multiline_comment|/* High 16 bits of cluster in FAT32 */
DECL|member|time
DECL|member|date
DECL|member|start
id|__le16
id|time
comma
id|date
comma
id|start
suffix:semicolon
multiline_comment|/* time, date and first cluster */
DECL|member|size
id|__le32
id|size
suffix:semicolon
multiline_comment|/* file size (in bytes) */
)brace
suffix:semicolon
multiline_comment|/* Up to 13 characters of the name */
DECL|struct|msdos_dir_slot
r_struct
id|msdos_dir_slot
(brace
DECL|member|id
id|__u8
id|id
suffix:semicolon
multiline_comment|/* sequence number for slot */
DECL|member|name0_4
id|__u8
id|name0_4
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* first 5 characters in name */
DECL|member|attr
id|__u8
id|attr
suffix:semicolon
multiline_comment|/* attribute byte */
DECL|member|reserved
id|__u8
id|reserved
suffix:semicolon
multiline_comment|/* always 0 */
DECL|member|alias_checksum
id|__u8
id|alias_checksum
suffix:semicolon
multiline_comment|/* checksum for 8.3 alias */
DECL|member|name5_10
id|__u8
id|name5_10
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* 6 more characters in name */
DECL|member|start
id|__le16
id|start
suffix:semicolon
multiline_comment|/* starting cluster number, 0 in long slots */
DECL|member|name11_12
id|__u8
id|name11_12
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* last 2 characters in name */
)brace
suffix:semicolon
DECL|struct|vfat_slot_info
r_struct
id|vfat_slot_info
(brace
DECL|member|long_slots
r_int
id|long_slots
suffix:semicolon
multiline_comment|/* number of long slots in filename */
DECL|member|longname_offset
id|loff_t
id|longname_offset
suffix:semicolon
multiline_comment|/* dir offset for longname start */
DECL|member|i_pos
id|loff_t
id|i_pos
suffix:semicolon
multiline_comment|/* on-disk position of directory entry */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/nls.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
DECL|struct|fat_mount_options
r_struct
id|fat_mount_options
(brace
DECL|member|fs_uid
id|uid_t
id|fs_uid
suffix:semicolon
DECL|member|fs_gid
id|gid_t
id|fs_gid
suffix:semicolon
DECL|member|fs_fmask
r_int
r_int
id|fs_fmask
suffix:semicolon
DECL|member|fs_dmask
r_int
r_int
id|fs_dmask
suffix:semicolon
DECL|member|codepage
r_int
r_int
id|codepage
suffix:semicolon
multiline_comment|/* Codepage for shortname conversions */
DECL|member|iocharset
r_char
op_star
id|iocharset
suffix:semicolon
multiline_comment|/* Charset used for filename input/display */
DECL|member|shortname
r_int
r_int
id|shortname
suffix:semicolon
multiline_comment|/* flags for shortname display/create rule */
DECL|member|name_check
r_int
r_char
id|name_check
suffix:semicolon
multiline_comment|/* r = relaxed, n = normal, s = strict */
DECL|member|quiet
r_int
id|quiet
suffix:colon
l_int|1
comma
multiline_comment|/* set = fake successful chmods and chowns */
DECL|member|showexec
id|showexec
suffix:colon
l_int|1
comma
multiline_comment|/* set = only set x bit for com/exe/bat */
DECL|member|sys_immutable
id|sys_immutable
suffix:colon
l_int|1
comma
multiline_comment|/* set = system files are immutable */
DECL|member|dotsOK
id|dotsOK
suffix:colon
l_int|1
comma
multiline_comment|/* set = hidden and system files are named &squot;.filename&squot; */
DECL|member|isvfat
id|isvfat
suffix:colon
l_int|1
comma
multiline_comment|/* 0=no vfat long filename support, 1=vfat support */
DECL|member|utf8
id|utf8
suffix:colon
l_int|1
comma
multiline_comment|/* Use of UTF8 character set (Default) */
DECL|member|unicode_xlate
id|unicode_xlate
suffix:colon
l_int|1
comma
multiline_comment|/* create escape sequences for unhandled Unicode */
DECL|member|numtail
id|numtail
suffix:colon
l_int|1
comma
multiline_comment|/* Does first alias have a numeric &squot;~1&squot; type tail? */
DECL|member|atari
id|atari
suffix:colon
l_int|1
comma
multiline_comment|/* Use Atari GEMDOS variation of MS-DOS fs */
DECL|member|nocase
id|nocase
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Does this need case conversion? 0=need case conversion*/
)brace
suffix:semicolon
DECL|macro|FAT_HASH_BITS
mdefine_line|#define FAT_HASH_BITS&t;8
DECL|macro|FAT_HASH_SIZE
mdefine_line|#define FAT_HASH_SIZE&t;(1UL &lt;&lt; FAT_HASH_BITS)
DECL|macro|FAT_HASH_MASK
mdefine_line|#define FAT_HASH_MASK&t;(FAT_HASH_SIZE-1)
multiline_comment|/*&n; * MS-DOS file system in-core superblock data&n; */
DECL|struct|msdos_sb_info
r_struct
id|msdos_sb_info
(brace
DECL|member|sec_per_clus
r_int
r_int
id|sec_per_clus
suffix:semicolon
multiline_comment|/* sectors/cluster */
DECL|member|cluster_bits
r_int
r_int
id|cluster_bits
suffix:semicolon
multiline_comment|/* log2(cluster_size) */
DECL|member|cluster_size
r_int
r_int
id|cluster_size
suffix:semicolon
multiline_comment|/* cluster size */
DECL|member|fats
DECL|member|fat_bits
r_int
r_char
id|fats
comma
id|fat_bits
suffix:semicolon
multiline_comment|/* number of FATs, FAT bits (12 or 16) */
DECL|member|fat_start
r_int
r_int
id|fat_start
suffix:semicolon
DECL|member|fat_length
r_int
r_int
id|fat_length
suffix:semicolon
multiline_comment|/* FAT start &amp; length (sec.) */
DECL|member|dir_start
r_int
r_int
id|dir_start
suffix:semicolon
DECL|member|dir_entries
r_int
r_int
id|dir_entries
suffix:semicolon
multiline_comment|/* root dir start &amp; entries */
DECL|member|data_start
r_int
r_int
id|data_start
suffix:semicolon
multiline_comment|/* first data sector */
DECL|member|max_cluster
r_int
r_int
id|max_cluster
suffix:semicolon
multiline_comment|/* maximum cluster number */
DECL|member|root_cluster
r_int
r_int
id|root_cluster
suffix:semicolon
multiline_comment|/* first cluster of the root directory */
DECL|member|fsinfo_sector
r_int
r_int
id|fsinfo_sector
suffix:semicolon
multiline_comment|/* sector number of FAT32 fsinfo */
DECL|member|fat_lock
r_struct
id|semaphore
id|fat_lock
suffix:semicolon
DECL|member|prev_free
r_int
id|prev_free
suffix:semicolon
multiline_comment|/* previously allocated cluster number */
DECL|member|free_clusters
r_int
id|free_clusters
suffix:semicolon
multiline_comment|/* -1 if undefined */
DECL|member|options
r_struct
id|fat_mount_options
id|options
suffix:semicolon
DECL|member|nls_disk
r_struct
id|nls_table
op_star
id|nls_disk
suffix:semicolon
multiline_comment|/* Codepage used on disk */
DECL|member|nls_io
r_struct
id|nls_table
op_star
id|nls_io
suffix:semicolon
multiline_comment|/* Charset used for input and display */
DECL|member|dir_ops
r_void
op_star
id|dir_ops
suffix:semicolon
multiline_comment|/* Opaque; default directory operations */
DECL|member|dir_per_block
r_int
id|dir_per_block
suffix:semicolon
multiline_comment|/* dir entries per block */
DECL|member|dir_per_block_bits
r_int
id|dir_per_block_bits
suffix:semicolon
multiline_comment|/* log2(dir_per_block) */
DECL|member|inode_hash_lock
id|spinlock_t
id|inode_hash_lock
suffix:semicolon
DECL|member|inode_hashtable
r_struct
id|hlist_head
id|inode_hashtable
(braket
id|FAT_HASH_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FAT_CACHE_VALID
mdefine_line|#define FAT_CACHE_VALID&t;0&t;/* special case for valid cache */
multiline_comment|/*&n; * MS-DOS file system inode data in memory&n; */
DECL|struct|msdos_inode_info
r_struct
id|msdos_inode_info
(brace
DECL|member|cache_lru_lock
id|spinlock_t
id|cache_lru_lock
suffix:semicolon
DECL|member|cache_lru
r_struct
id|list_head
id|cache_lru
suffix:semicolon
DECL|member|nr_caches
r_int
id|nr_caches
suffix:semicolon
multiline_comment|/* for avoiding the race between fat_free() and fat_get_cluster() */
DECL|member|cache_valid_id
r_int
r_int
id|cache_valid_id
suffix:semicolon
DECL|member|mmu_private
id|loff_t
id|mmu_private
suffix:semicolon
DECL|member|i_start
r_int
id|i_start
suffix:semicolon
multiline_comment|/* first cluster or 0 */
DECL|member|i_logstart
r_int
id|i_logstart
suffix:semicolon
multiline_comment|/* logical first cluster */
DECL|member|i_attrs
r_int
id|i_attrs
suffix:semicolon
multiline_comment|/* unused attribute bits */
DECL|member|i_ctime_ms
r_int
id|i_ctime_ms
suffix:semicolon
multiline_comment|/* unused change time in milliseconds */
DECL|member|i_pos
id|loff_t
id|i_pos
suffix:semicolon
multiline_comment|/* on-disk position of directory entry or 0 */
DECL|member|i_fat_hash
r_struct
id|hlist_node
id|i_fat_hash
suffix:semicolon
multiline_comment|/* hash by i_location */
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
DECL|function|MSDOS_SB
r_static
r_inline
r_struct
id|msdos_sb_info
op_star
id|MSDOS_SB
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|sb-&gt;s_fs_info
suffix:semicolon
)brace
DECL|function|MSDOS_I
r_static
r_inline
r_struct
id|msdos_inode_info
op_star
id|MSDOS_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|container_of
c_func
(paren
id|inode
comma
r_struct
id|msdos_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|fat_clus_to_blknr
r_static
r_inline
id|sector_t
id|fat_clus_to_blknr
c_func
(paren
r_struct
id|msdos_sb_info
op_star
id|sbi
comma
r_int
id|clus
)paren
(brace
r_return
(paren
(paren
id|sector_t
)paren
id|clus
op_minus
id|FAT_START_ENT
)paren
op_star
id|sbi-&gt;sec_per_clus
op_plus
id|sbi-&gt;data_start
suffix:semicolon
)brace
DECL|function|fat16_towchar
r_static
r_inline
r_void
id|fat16_towchar
c_func
(paren
m_wchar_t
op_star
id|dst
comma
r_const
id|__u8
op_star
id|src
comma
r_int
id|len
)paren
(brace
macro_line|#ifdef __BIG_ENDIAN
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|src
(braket
l_int|0
)braket
op_or
(paren
id|src
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
id|src
op_add_assign
l_int|2
suffix:semicolon
)brace
macro_line|#else
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|len
op_star
l_int|2
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|fatwchar_to16
r_static
r_inline
r_void
id|fatwchar_to16
c_func
(paren
id|__u8
op_star
id|dst
comma
r_const
m_wchar_t
op_star
id|src
comma
r_int
id|len
)paren
(brace
macro_line|#ifdef __BIG_ENDIAN
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
id|dst
(braket
l_int|0
)braket
op_assign
op_star
id|src
op_amp
l_int|0x00FF
suffix:semicolon
id|dst
(braket
l_int|1
)braket
op_assign
(paren
op_star
id|src
op_amp
l_int|0xFF00
)paren
op_rshift
l_int|8
suffix:semicolon
id|dst
op_add_assign
l_int|2
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
macro_line|#else
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|len
op_star
l_int|2
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* fat/cache.c */
r_extern
r_void
id|fat_cache_inval_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
id|fat_access
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|nr
comma
r_int
id|new_value
)paren
suffix:semicolon
r_extern
r_int
id|fat_get_cluster
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|cluster
comma
r_int
op_star
id|fclus
comma
r_int
op_star
id|dclus
)paren
suffix:semicolon
r_extern
r_int
id|fat_bmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|sector
comma
id|sector_t
op_star
id|phys
)paren
suffix:semicolon
multiline_comment|/* fat/dir.c */
r_extern
r_struct
id|file_operations
id|fat_dir_operations
suffix:semicolon
r_extern
r_int
id|fat_search_long
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_const
r_int
r_char
op_star
id|name
comma
r_int
id|name_len
comma
r_int
id|anycase
comma
id|loff_t
op_star
id|spos
comma
id|loff_t
op_star
id|lpos
)paren
suffix:semicolon
r_extern
r_int
id|fat_add_entries
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
id|slots
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|de
comma
id|loff_t
op_star
id|i_pos
)paren
suffix:semicolon
r_extern
r_int
id|fat_new_dir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|inode
op_star
id|parent
comma
r_int
id|is_vfat
)paren
suffix:semicolon
r_extern
r_int
id|fat_dir_empty
c_func
(paren
r_struct
id|inode
op_star
id|dir
)paren
suffix:semicolon
r_extern
r_int
id|fat_subdirs
c_func
(paren
r_struct
id|inode
op_star
id|dir
)paren
suffix:semicolon
r_extern
r_int
id|fat_scan
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_int
r_char
op_star
id|name
comma
r_struct
id|buffer_head
op_star
op_star
id|res_bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|res_de
comma
id|loff_t
op_star
id|i_pos
)paren
suffix:semicolon
multiline_comment|/* fat/file.c */
r_extern
r_struct
id|file_operations
id|fat_file_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|fat_file_inode_operations
suffix:semicolon
r_extern
r_int
id|fat_notify_change
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
suffix:semicolon
r_extern
r_void
id|fat_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/* fat/inode.c */
r_extern
r_void
id|fat_attach
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|loff_t
id|i_pos
)paren
suffix:semicolon
r_extern
r_void
id|fat_detach
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|fat_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|loff_t
id|i_pos
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|fat_build_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|msdos_dir_entry
op_star
id|de
comma
id|loff_t
id|i_pos
comma
r_int
op_star
id|res
)paren
suffix:semicolon
r_int
id|fat_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
comma
r_struct
id|inode_operations
op_star
id|fs_dir_inode_ops
comma
r_int
id|isvfat
)paren
suffix:semicolon
multiline_comment|/* fat/misc.c */
r_extern
r_void
id|fat_fs_panic
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|lock_fat
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_void
id|unlock_fat
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_void
id|fat_clusters_flush
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_int
id|fat_add_cluster
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
id|date_dos2unix
c_func
(paren
r_int
r_int
id|time
comma
r_int
r_int
id|date
)paren
suffix:semicolon
r_extern
r_void
id|fat_date_unix2dos
c_func
(paren
r_int
id|unix_date
comma
id|__le16
op_star
id|time
comma
id|__le16
op_star
id|date
)paren
suffix:semicolon
r_extern
r_int
id|fat__get_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
id|loff_t
op_star
id|pos
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|de
comma
id|loff_t
op_star
id|i_pos
)paren
suffix:semicolon
DECL|function|fat_get_entry
r_static
id|__inline__
r_int
id|fat_get_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
id|loff_t
op_star
id|pos
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|de
comma
id|loff_t
op_star
id|i_pos
)paren
(brace
multiline_comment|/* Fast stuff first */
r_if
c_cond
(paren
op_star
id|bh
op_logical_and
op_star
id|de
op_logical_and
(paren
op_star
id|de
op_minus
(paren
r_struct
id|msdos_dir_entry
op_star
)paren
(paren
op_star
id|bh
)paren
op_member_access_from_pointer
id|b_data
)paren
OL
id|MSDOS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|dir_per_block
op_minus
l_int|1
)paren
(brace
op_star
id|pos
op_add_assign
r_sizeof
(paren
r_struct
id|msdos_dir_entry
)paren
suffix:semicolon
(paren
op_star
id|de
)paren
op_increment
suffix:semicolon
(paren
op_star
id|i_pos
)paren
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|fat__get_entry
c_func
(paren
id|dir
comma
id|pos
comma
id|bh
comma
id|de
comma
id|i_pos
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
