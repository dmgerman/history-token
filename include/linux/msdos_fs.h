macro_line|#ifndef _LINUX_MSDOS_FS_H
DECL|macro|_LINUX_MSDOS_FS_H
mdefine_line|#define _LINUX_MSDOS_FS_H
multiline_comment|/*&n; * The MS-DOS filesystem constants/structures&n; */
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
r_struct
id|statfs
suffix:semicolon
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
DECL|macro|MSDOS_ROOT_INO
mdefine_line|#define MSDOS_ROOT_INO&t;1&t;/* == MINIX_ROOT_INO */
DECL|macro|MSDOS_DIR_BITS
mdefine_line|#define MSDOS_DIR_BITS&t;5&t;/* log2(sizeof(struct msdos_dir_entry)) */
multiline_comment|/* directory limit */
DECL|macro|FAT_MAX_DIR_ENTRIES
mdefine_line|#define FAT_MAX_DIR_ENTRIES&t;(65536)
DECL|macro|FAT_MAX_DIR_SIZE
mdefine_line|#define FAT_MAX_DIR_SIZE&t;(FAT_MAX_DIR_ENTRIES &lt;&lt; MSDOS_DIR_BITS)
DECL|macro|MSDOS_SUPER_MAGIC
mdefine_line|#define MSDOS_SUPER_MAGIC 0x4d44 /* MD */
DECL|macro|ATTR_NONE
mdefine_line|#define ATTR_NONE    0 /* no attribute bits */
DECL|macro|ATTR_RO
mdefine_line|#define ATTR_RO      1  /* read-only */
DECL|macro|ATTR_HIDDEN
mdefine_line|#define ATTR_HIDDEN  2  /* hidden */
DECL|macro|ATTR_SYS
mdefine_line|#define ATTR_SYS     4  /* system */
DECL|macro|ATTR_VOLUME
mdefine_line|#define ATTR_VOLUME  8  /* volume label */
DECL|macro|ATTR_DIR
mdefine_line|#define ATTR_DIR     16 /* directory */
DECL|macro|ATTR_ARCH
mdefine_line|#define ATTR_ARCH    32 /* archived */
DECL|macro|ATTR_UNUSED
mdefine_line|#define ATTR_UNUSED  (ATTR_VOLUME | ATTR_ARCH | ATTR_SYS | ATTR_HIDDEN)
multiline_comment|/* attribute bits that are copied &quot;as is&quot; */
DECL|macro|ATTR_EXT
mdefine_line|#define ATTR_EXT     (ATTR_RO | ATTR_HIDDEN | ATTR_SYS | ATTR_VOLUME)
multiline_comment|/* bits that are used by the Windows 95/Windows NT extended FAT */
DECL|macro|CASE_LOWER_BASE
mdefine_line|#define CASE_LOWER_BASE 8&t;/* base is lower case */
DECL|macro|CASE_LOWER_EXT
mdefine_line|#define CASE_LOWER_EXT  16&t;/* extension is lower case */
DECL|macro|DELETED_FLAG
mdefine_line|#define DELETED_FLAG 0xe5 /* marks file as deleted when in name[0] */
DECL|macro|IS_FREE
mdefine_line|#define IS_FREE(n) (!*(n) || *(const unsigned char *) (n) == DELETED_FLAG)
DECL|macro|MSDOS_VALID_MODE
mdefine_line|#define MSDOS_VALID_MODE (S_IFREG | S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO)
multiline_comment|/* valid file mode bits */
DECL|macro|MSDOS_NAME
mdefine_line|#define MSDOS_NAME 11 /* maximum name length */
DECL|macro|MSDOS_LONGNAME
mdefine_line|#define MSDOS_LONGNAME 256 /* maximum name length */
DECL|macro|MSDOS_SLOTS
mdefine_line|#define MSDOS_SLOTS 21  /* max # of slots needed for short and long names */
DECL|macro|MSDOS_DOT
mdefine_line|#define MSDOS_DOT    &quot;.          &quot; /* &quot;.&quot;, padded to MSDOS_NAME chars */
DECL|macro|MSDOS_DOTDOT
mdefine_line|#define MSDOS_DOTDOT &quot;..         &quot; /* &quot;..&quot;, padded to MSDOS_NAME chars */
DECL|macro|MSDOS_FAT12
mdefine_line|#define MSDOS_FAT12 4084 /* maximum number of clusters in a 12 bit FAT */
multiline_comment|/* media of boot sector */
DECL|macro|FAT_VALID_MEDIA
mdefine_line|#define FAT_VALID_MEDIA(x)&t;((0xF8 &lt;= (x) &amp;&amp; (x) &lt;= 0xFF) || (x) == 0xF0)
DECL|macro|FAT_FIRST_ENT
mdefine_line|#define FAT_FIRST_ENT(s, x)&t;((MSDOS_SB(s)-&gt;fat_bits == 32 ? 0x0FFFFF00 : &bslash;&n;&t;MSDOS_SB(s)-&gt;fat_bits == 16 ? 0xFF00 : 0xF00) | (x))
multiline_comment|/* bad cluster mark */
DECL|macro|BAD_FAT12
mdefine_line|#define BAD_FAT12 0xFF7
DECL|macro|BAD_FAT16
mdefine_line|#define BAD_FAT16 0xFFF7
DECL|macro|BAD_FAT32
mdefine_line|#define BAD_FAT32 0xFFFFFF7
DECL|macro|BAD_FAT
mdefine_line|#define BAD_FAT(s) (MSDOS_SB(s)-&gt;fat_bits == 32 ? BAD_FAT32 : &bslash;&n;&t;MSDOS_SB(s)-&gt;fat_bits == 16 ? BAD_FAT16 : BAD_FAT12)
multiline_comment|/* standard EOF */
DECL|macro|EOF_FAT12
mdefine_line|#define EOF_FAT12 0xFFF
DECL|macro|EOF_FAT16
mdefine_line|#define EOF_FAT16 0xFFFF
DECL|macro|EOF_FAT32
mdefine_line|#define EOF_FAT32 0xFFFFFFF
DECL|macro|EOF_FAT
mdefine_line|#define EOF_FAT(s) (MSDOS_SB(s)-&gt;fat_bits == 32 ? EOF_FAT32 : &bslash;&n;&t;MSDOS_SB(s)-&gt;fat_bits == 16 ? EOF_FAT16 : EOF_FAT12)
DECL|macro|FAT_ENT_FREE
mdefine_line|#define FAT_ENT_FREE&t;(0)
DECL|macro|FAT_ENT_BAD
mdefine_line|#define FAT_ENT_BAD&t;(BAD_FAT32)
DECL|macro|FAT_ENT_EOF
mdefine_line|#define FAT_ENT_EOF&t;(EOF_FAT32)
DECL|macro|FAT_FSINFO_SIG1
mdefine_line|#define FAT_FSINFO_SIG1&t;&t;0x41615252
DECL|macro|FAT_FSINFO_SIG2
mdefine_line|#define FAT_FSINFO_SIG2&t;&t;0x61417272
DECL|macro|IS_FSINFO
mdefine_line|#define IS_FSINFO(x)&t;(CF_LE_L((x)-&gt;signature1) == FAT_FSINFO_SIG1&t;&bslash;&n;&t;&t;&t; &amp;&amp; CF_LE_L((x)-&gt;signature2) == FAT_FSINFO_SIG2)
multiline_comment|/*&n; * ioctl commands&n; */
DECL|macro|VFAT_IOCTL_READDIR_BOTH
mdefine_line|#define&t;VFAT_IOCTL_READDIR_BOTH&t;&t;_IOR(&squot;r&squot;, 1, struct dirent [2])
DECL|macro|VFAT_IOCTL_READDIR_SHORT
mdefine_line|#define&t;VFAT_IOCTL_READDIR_SHORT&t;_IOR(&squot;r&squot;, 2, struct dirent [2])
multiline_comment|/* &n; * vfat shortname flags&n; */
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
multiline_comment|/*&n; * Conversion from and to little-endian byte order. (no-op on i386/i486)&n; *&n; * Naming: Ca_b_c, where a: F = from, T = to, b: LE = little-endian,&n; * BE = big-endian, c: W = word (16 bits), L = longword (32 bits)&n; */
DECL|macro|CF_LE_W
mdefine_line|#define CF_LE_W(v) le16_to_cpu(v)
DECL|macro|CF_LE_L
mdefine_line|#define CF_LE_L(v) le32_to_cpu(v)
DECL|macro|CT_LE_W
mdefine_line|#define CT_LE_W(v) cpu_to_le16(v)
DECL|macro|CT_LE_L
mdefine_line|#define CT_LE_L(v) cpu_to_le32(v)
DECL|struct|fat_boot_sector
r_struct
id|fat_boot_sector
(brace
DECL|member|ignored
id|__s8
id|ignored
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Boot strap short or near jump */
DECL|member|system_id
id|__s8
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
DECL|member|cluster_size
id|__u8
id|cluster_size
suffix:semicolon
multiline_comment|/* sectors/cluster */
DECL|member|reserved
id|__u16
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
id|__u16
id|fat_length
suffix:semicolon
multiline_comment|/* sectors/FAT */
DECL|member|secs_track
id|__u16
id|secs_track
suffix:semicolon
multiline_comment|/* sectors per track */
DECL|member|heads
id|__u16
id|heads
suffix:semicolon
multiline_comment|/* number of heads */
DECL|member|hidden
id|__u32
id|hidden
suffix:semicolon
multiline_comment|/* hidden sectors (unused) */
DECL|member|total_sect
id|__u32
id|total_sect
suffix:semicolon
multiline_comment|/* number of sectors (if sectors == 0) */
multiline_comment|/* The following fields are only used by FAT32 */
DECL|member|fat32_length
id|__u32
id|fat32_length
suffix:semicolon
multiline_comment|/* sectors/FAT */
DECL|member|flags
id|__u16
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
id|__u32
id|root_cluster
suffix:semicolon
multiline_comment|/* first cluster in root directory */
DECL|member|info_sector
id|__u16
id|info_sector
suffix:semicolon
multiline_comment|/* filesystem info sector */
DECL|member|backup_boot
id|__u16
id|backup_boot
suffix:semicolon
multiline_comment|/* backup boot sector */
DECL|member|reserved2
id|__u16
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
id|__u32
id|signature1
suffix:semicolon
multiline_comment|/* 0x41615252L */
DECL|member|reserved1
id|__u32
id|reserved1
(braket
l_int|120
)braket
suffix:semicolon
multiline_comment|/* Nothing as far as I can tell */
DECL|member|signature2
id|__u32
id|signature2
suffix:semicolon
multiline_comment|/* 0x61417272L */
DECL|member|free_clusters
id|__u32
id|free_clusters
suffix:semicolon
multiline_comment|/* Free cluster count.  -1 if unknown */
DECL|member|next_cluster
id|__u32
id|next_cluster
suffix:semicolon
multiline_comment|/* Most recently allocated cluster */
DECL|member|reserved2
id|__u32
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
id|__s8
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
id|__u16
id|ctime
suffix:semicolon
multiline_comment|/* Creation time */
DECL|member|cdate
id|__u16
id|cdate
suffix:semicolon
multiline_comment|/* Creation date */
DECL|member|adate
id|__u16
id|adate
suffix:semicolon
multiline_comment|/* Last access date */
DECL|member|starthi
id|__u16
id|starthi
suffix:semicolon
multiline_comment|/* High 16 bits of cluster in FAT32 */
DECL|member|time
DECL|member|date
DECL|member|start
id|__u16
id|time
comma
id|date
comma
id|start
suffix:semicolon
multiline_comment|/* time, date and first cluster */
DECL|member|size
id|__u32
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
id|__u16
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
multiline_comment|/* Convert attribute bits and a mask to the UNIX mode. */
DECL|macro|MSDOS_MKMODE
mdefine_line|#define MSDOS_MKMODE(a,m) (m &amp; (a &amp; ATTR_RO ? S_IRUGO|S_IXUGO : S_IRWXUGO))
multiline_comment|/* Convert the UNIX mode to MS-DOS attribute bits. */
DECL|macro|MSDOS_MKATTR
mdefine_line|#define MSDOS_MKATTR(m) ((m &amp; S_IWUGO) ? ATTR_NONE : ATTR_RO)
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/nls.h&gt;
macro_line|#include &lt;linux/msdos_fs_i.h&gt;
macro_line|#include &lt;linux/msdos_fs_sb.h&gt;
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
id|__fat_access
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
r_extern
r_void
id|fat_cache_init
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
id|fat_cache_lookup
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
id|f_clu
comma
r_int
op_star
id|d_clu
)paren
suffix:semicolon
r_extern
r_void
id|fat_cache_add
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|f_clu
comma
r_int
id|d_clu
)paren
suffix:semicolon
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
id|fat_free
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|skip
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
id|fat_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
suffix:semicolon
r_extern
r_int
id|fat_dir_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
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
id|fat_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|iblock
comma
r_struct
id|buffer_head
op_star
id|bh_result
comma
r_int
id|create
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
id|fat_hash_init
c_func
(paren
r_void
)paren
suffix:semicolon
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
r_extern
r_void
id|fat_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|fat_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|fat_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
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
r_extern
r_int
id|fat_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|kstatfs
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_void
id|fat_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|wait
)paren
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
r_struct
id|buffer_head
op_star
id|fat_extend_dir
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
r_int
r_int
op_star
id|time
comma
r_int
r_int
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
multiline_comment|/* msdos/namei.c  - these are for Umsdos */
r_extern
r_struct
id|dentry
op_star
id|msdos_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|msdos_create
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|msdos_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|msdos_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|msdos_unlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|msdos_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
suffix:semicolon
r_extern
r_int
id|msdos_fill_super
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
)paren
suffix:semicolon
multiline_comment|/* vfat/namei.c - these are for dmsdos */
r_extern
r_struct
id|dentry
op_star
id|vfat_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|vfat_create
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|vfat_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|vfat_unlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|vfat_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|vfat_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
suffix:semicolon
r_extern
r_int
id|vfat_fill_super
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
)paren
suffix:semicolon
multiline_comment|/* vfat/vfatfs_syms.c */
r_extern
r_struct
id|file_system_type
id|vfat_fs_type
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
