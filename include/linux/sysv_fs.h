macro_line|#ifndef _LINUX_SYSV_FS_H
DECL|macro|_LINUX_SYSV_FS_H
mdefine_line|#define _LINUX_SYSV_FS_H
macro_line|#if defined(__GNUC__)
DECL|macro|__packed2__
macro_line|# define __packed2__&t;__attribute__((packed, aligned(2)))
macro_line|#else
op_rshift
id|I
id|want
id|to
id|scream
op_logical_neg
op_lshift
macro_line|#endif
multiline_comment|/* inode numbers are 16 bit */
DECL|typedef|sysv_ino_t
r_typedef
id|u16
id|sysv_ino_t
suffix:semicolon
multiline_comment|/* Block numbers are 24 bit, sometimes stored in 32 bit.&n;   On Coherent FS, they are always stored in PDP-11 manner: the least&n;   significant 16 bits come last. */
DECL|typedef|sysv_zone_t
r_typedef
id|u32
id|sysv_zone_t
suffix:semicolon
multiline_comment|/* 0 is non-existent */
DECL|macro|SYSV_BADBL_INO
mdefine_line|#define SYSV_BADBL_INO&t;1&t;/* inode of bad blocks file */
DECL|macro|SYSV_ROOT_INO
mdefine_line|#define SYSV_ROOT_INO&t;2&t;/* inode of root directory */
multiline_comment|/* Xenix super-block data on disk */
DECL|macro|XENIX_NICINOD
mdefine_line|#define XENIX_NICINOD&t;100&t;/* number of inode cache entries */
DECL|macro|XENIX_NICFREE
mdefine_line|#define XENIX_NICFREE&t;100&t;/* number of free block list chunk entries */
DECL|struct|xenix_super_block
r_struct
id|xenix_super_block
(brace
DECL|member|s_isize
id|u16
id|s_isize
suffix:semicolon
multiline_comment|/* index of first data zone */
DECL|member|__packed2__
id|u32
id|s_fsize
id|__packed2__
suffix:semicolon
multiline_comment|/* total number of zones of this fs */
multiline_comment|/* the start of the free block list: */
DECL|member|s_nfree
id|u16
id|s_nfree
suffix:semicolon
multiline_comment|/* number of free blocks in s_free, &lt;= XENIX_NICFREE */
DECL|member|s_free
id|u32
id|s_free
(braket
id|XENIX_NICFREE
)braket
suffix:semicolon
multiline_comment|/* first free block list chunk */
multiline_comment|/* the cache of free inodes: */
DECL|member|s_ninode
id|u16
id|s_ninode
suffix:semicolon
multiline_comment|/* number of free inodes in s_inode, &lt;= XENIX_NICINOD */
DECL|member|s_inode
id|sysv_ino_t
id|s_inode
(braket
id|XENIX_NICINOD
)braket
suffix:semicolon
multiline_comment|/* some free inodes */
multiline_comment|/* locks, not used by Linux: */
DECL|member|s_flock
r_char
id|s_flock
suffix:semicolon
multiline_comment|/* lock during free block list manipulation */
DECL|member|s_ilock
r_char
id|s_ilock
suffix:semicolon
multiline_comment|/* lock during inode cache manipulation */
DECL|member|s_fmod
r_char
id|s_fmod
suffix:semicolon
multiline_comment|/* super-block modified flag */
DECL|member|s_ronly
r_char
id|s_ronly
suffix:semicolon
multiline_comment|/* flag whether fs is mounted read-only */
DECL|member|__packed2__
id|u32
id|s_time
id|__packed2__
suffix:semicolon
multiline_comment|/* time of last super block update */
DECL|member|__packed2__
id|u32
id|s_tfree
id|__packed2__
suffix:semicolon
multiline_comment|/* total number of free zones */
DECL|member|s_tinode
id|u16
id|s_tinode
suffix:semicolon
multiline_comment|/* total number of free inodes */
DECL|member|s_dinfo
id|s16
id|s_dinfo
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* device information ?? */
DECL|member|s_fname
r_char
id|s_fname
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system volume name */
DECL|member|s_fpack
r_char
id|s_fpack
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system pack name */
DECL|member|s_clean
r_char
id|s_clean
suffix:semicolon
multiline_comment|/* set to 0x46 when filesystem is properly unmounted */
DECL|member|s_fill
r_char
id|s_fill
(braket
l_int|371
)braket
suffix:semicolon
DECL|member|s_magic
id|s32
id|s_magic
suffix:semicolon
multiline_comment|/* version of file system */
DECL|member|s_type
id|s32
id|s_type
suffix:semicolon
multiline_comment|/* type of file system: 1 for 512 byte blocks&n;&t;&t;&t;&t;&t;&t;&t;&t;2 for 1024 byte blocks&n;&t;&t;&t;&t;&t;&t;&t;&t;3 for 2048 byte blocks */
)brace
suffix:semicolon
multiline_comment|/*&n; * SystemV FS comes in two variants:&n; * sysv2: System V Release 2 (e.g. Microport), structure elements aligned(2).&n; * sysv4: System V Release 4 (e.g. Consensys), structure elements aligned(4).&n; */
DECL|macro|SYSV_NICINOD
mdefine_line|#define SYSV_NICINOD&t;100&t;/* number of inode cache entries */
DECL|macro|SYSV_NICFREE
mdefine_line|#define SYSV_NICFREE&t;50&t;/* number of free block list chunk entries */
multiline_comment|/* SystemV4 super-block data on disk */
DECL|struct|sysv4_super_block
r_struct
id|sysv4_super_block
(brace
DECL|member|s_isize
id|u16
id|s_isize
suffix:semicolon
multiline_comment|/* index of first data zone */
DECL|member|s_pad0
id|u16
id|s_pad0
suffix:semicolon
DECL|member|s_fsize
id|u32
id|s_fsize
suffix:semicolon
multiline_comment|/* total number of zones of this fs */
multiline_comment|/* the start of the free block list: */
DECL|member|s_nfree
id|u16
id|s_nfree
suffix:semicolon
multiline_comment|/* number of free blocks in s_free, &lt;= SYSV_NICFREE */
DECL|member|s_pad1
id|u16
id|s_pad1
suffix:semicolon
DECL|member|s_free
id|u32
id|s_free
(braket
id|SYSV_NICFREE
)braket
suffix:semicolon
multiline_comment|/* first free block list chunk */
multiline_comment|/* the cache of free inodes: */
DECL|member|s_ninode
id|u16
id|s_ninode
suffix:semicolon
multiline_comment|/* number of free inodes in s_inode, &lt;= SYSV_NICINOD */
DECL|member|s_pad2
id|u16
id|s_pad2
suffix:semicolon
DECL|member|s_inode
id|sysv_ino_t
id|s_inode
(braket
id|SYSV_NICINOD
)braket
suffix:semicolon
multiline_comment|/* some free inodes */
multiline_comment|/* locks, not used by Linux: */
DECL|member|s_flock
r_char
id|s_flock
suffix:semicolon
multiline_comment|/* lock during free block list manipulation */
DECL|member|s_ilock
r_char
id|s_ilock
suffix:semicolon
multiline_comment|/* lock during inode cache manipulation */
DECL|member|s_fmod
r_char
id|s_fmod
suffix:semicolon
multiline_comment|/* super-block modified flag */
DECL|member|s_ronly
r_char
id|s_ronly
suffix:semicolon
multiline_comment|/* flag whether fs is mounted read-only */
DECL|member|s_time
id|u32
id|s_time
suffix:semicolon
multiline_comment|/* time of last super block update */
DECL|member|s_dinfo
id|s16
id|s_dinfo
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* device information ?? */
DECL|member|s_tfree
id|u32
id|s_tfree
suffix:semicolon
multiline_comment|/* total number of free zones */
DECL|member|s_tinode
id|u16
id|s_tinode
suffix:semicolon
multiline_comment|/* total number of free inodes */
DECL|member|s_pad3
id|u16
id|s_pad3
suffix:semicolon
DECL|member|s_fname
r_char
id|s_fname
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system volume name */
DECL|member|s_fpack
r_char
id|s_fpack
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system pack name */
DECL|member|s_fill
id|s32
id|s_fill
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|s_state
id|s32
id|s_state
suffix:semicolon
multiline_comment|/* file system state: 0x7c269d38-s_time means clean */
DECL|member|s_magic
id|s32
id|s_magic
suffix:semicolon
multiline_comment|/* version of file system */
DECL|member|s_type
id|s32
id|s_type
suffix:semicolon
multiline_comment|/* type of file system: 1 for 512 byte blocks&n;&t;&t;&t;&t;&t;&t;&t;&t;2 for 1024 byte blocks */
)brace
suffix:semicolon
multiline_comment|/* SystemV2 super-block data on disk */
DECL|struct|sysv2_super_block
r_struct
id|sysv2_super_block
(brace
DECL|member|s_isize
id|u16
id|s_isize
suffix:semicolon
multiline_comment|/* index of first data zone */
DECL|member|__packed2__
id|u32
id|s_fsize
id|__packed2__
suffix:semicolon
multiline_comment|/* total number of zones of this fs */
multiline_comment|/* the start of the free block list: */
DECL|member|s_nfree
id|u16
id|s_nfree
suffix:semicolon
multiline_comment|/* number of free blocks in s_free, &lt;= SYSV_NICFREE */
DECL|member|s_free
id|u32
id|s_free
(braket
id|SYSV_NICFREE
)braket
suffix:semicolon
multiline_comment|/* first free block list chunk */
multiline_comment|/* the cache of free inodes: */
DECL|member|s_ninode
id|u16
id|s_ninode
suffix:semicolon
multiline_comment|/* number of free inodes in s_inode, &lt;= SYSV_NICINOD */
DECL|member|s_inode
id|sysv_ino_t
id|s_inode
(braket
id|SYSV_NICINOD
)braket
suffix:semicolon
multiline_comment|/* some free inodes */
multiline_comment|/* locks, not used by Linux: */
DECL|member|s_flock
r_char
id|s_flock
suffix:semicolon
multiline_comment|/* lock during free block list manipulation */
DECL|member|s_ilock
r_char
id|s_ilock
suffix:semicolon
multiline_comment|/* lock during inode cache manipulation */
DECL|member|s_fmod
r_char
id|s_fmod
suffix:semicolon
multiline_comment|/* super-block modified flag */
DECL|member|s_ronly
r_char
id|s_ronly
suffix:semicolon
multiline_comment|/* flag whether fs is mounted read-only */
DECL|member|__packed2__
id|u32
id|s_time
id|__packed2__
suffix:semicolon
multiline_comment|/* time of last super block update */
DECL|member|s_dinfo
id|s16
id|s_dinfo
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* device information ?? */
DECL|member|__packed2__
id|u32
id|s_tfree
id|__packed2__
suffix:semicolon
multiline_comment|/* total number of free zones */
DECL|member|s_tinode
id|u16
id|s_tinode
suffix:semicolon
multiline_comment|/* total number of free inodes */
DECL|member|s_fname
r_char
id|s_fname
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system volume name */
DECL|member|s_fpack
r_char
id|s_fpack
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system pack name */
DECL|member|s_fill
id|s32
id|s_fill
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|s_state
id|s32
id|s_state
suffix:semicolon
multiline_comment|/* file system state: 0xcb096f43 means clean */
DECL|member|s_magic
id|s32
id|s_magic
suffix:semicolon
multiline_comment|/* version of file system */
DECL|member|s_type
id|s32
id|s_type
suffix:semicolon
multiline_comment|/* type of file system: 1 for 512 byte blocks&n;&t;&t;&t;&t;&t;&t;&t;&t;2 for 1024 byte blocks */
)brace
suffix:semicolon
multiline_comment|/* V7 super-block data on disk */
DECL|macro|V7_NICINOD
mdefine_line|#define V7_NICINOD     100     /* number of inode cache entries */
DECL|macro|V7_NICFREE
mdefine_line|#define V7_NICFREE     50      /* number of free block list chunk entries */
DECL|struct|v7_super_block
r_struct
id|v7_super_block
(brace
DECL|member|s_isize
id|u16
id|s_isize
suffix:semicolon
multiline_comment|/* index of first data zone */
DECL|member|__packed2__
id|u32
id|s_fsize
id|__packed2__
suffix:semicolon
multiline_comment|/* total number of zones of this fs */
multiline_comment|/* the start of the free block list: */
DECL|member|s_nfree
id|u16
id|s_nfree
suffix:semicolon
multiline_comment|/* number of free blocks in s_free, &lt;= V7_NICFREE */
DECL|member|s_free
id|u32
id|s_free
(braket
id|V7_NICFREE
)braket
suffix:semicolon
multiline_comment|/* first free block list chunk */
multiline_comment|/* the cache of free inodes: */
DECL|member|s_ninode
id|u16
id|s_ninode
suffix:semicolon
multiline_comment|/* number of free inodes in s_inode, &lt;= V7_NICINOD */
DECL|member|s_inode
id|sysv_ino_t
id|s_inode
(braket
id|V7_NICINOD
)braket
suffix:semicolon
multiline_comment|/* some free inodes */
multiline_comment|/* locks, not used by Linux or V7: */
DECL|member|s_flock
r_char
id|s_flock
suffix:semicolon
multiline_comment|/* lock during free block list manipulation */
DECL|member|s_ilock
r_char
id|s_ilock
suffix:semicolon
multiline_comment|/* lock during inode cache manipulation */
DECL|member|s_fmod
r_char
id|s_fmod
suffix:semicolon
multiline_comment|/* super-block modified flag */
DECL|member|s_ronly
r_char
id|s_ronly
suffix:semicolon
multiline_comment|/* flag whether fs is mounted read-only */
DECL|member|__packed2__
id|u32
id|s_time
id|__packed2__
suffix:semicolon
multiline_comment|/* time of last super block update */
multiline_comment|/* the following fields are not maintained by V7: */
DECL|member|__packed2__
id|u32
id|s_tfree
id|__packed2__
suffix:semicolon
multiline_comment|/* total number of free zones */
DECL|member|s_tinode
id|u16
id|s_tinode
suffix:semicolon
multiline_comment|/* total number of free inodes */
DECL|member|s_m
id|u16
id|s_m
suffix:semicolon
multiline_comment|/* interleave factor */
DECL|member|s_n
id|u16
id|s_n
suffix:semicolon
multiline_comment|/* interleave factor */
DECL|member|s_fname
r_char
id|s_fname
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system name */
DECL|member|s_fpack
r_char
id|s_fpack
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system pack name */
)brace
suffix:semicolon
multiline_comment|/* Coherent super-block data on disk */
DECL|macro|COH_NICINOD
mdefine_line|#define COH_NICINOD&t;100&t;/* number of inode cache entries */
DECL|macro|COH_NICFREE
mdefine_line|#define COH_NICFREE&t;64&t;/* number of free block list chunk entries */
DECL|struct|coh_super_block
r_struct
id|coh_super_block
(brace
DECL|member|s_isize
id|u16
id|s_isize
suffix:semicolon
multiline_comment|/* index of first data zone */
DECL|member|__packed2__
id|u32
id|s_fsize
id|__packed2__
suffix:semicolon
multiline_comment|/* total number of zones of this fs */
multiline_comment|/* the start of the free block list: */
DECL|member|s_nfree
id|u16
id|s_nfree
suffix:semicolon
multiline_comment|/* number of free blocks in s_free, &lt;= COH_NICFREE */
DECL|member|__packed2__
id|u32
id|s_free
(braket
id|COH_NICFREE
)braket
id|__packed2__
suffix:semicolon
multiline_comment|/* first free block list chunk */
multiline_comment|/* the cache of free inodes: */
DECL|member|s_ninode
id|u16
id|s_ninode
suffix:semicolon
multiline_comment|/* number of free inodes in s_inode, &lt;= COH_NICINOD */
DECL|member|s_inode
id|sysv_ino_t
id|s_inode
(braket
id|COH_NICINOD
)braket
suffix:semicolon
multiline_comment|/* some free inodes */
multiline_comment|/* locks, not used by Linux: */
DECL|member|s_flock
r_char
id|s_flock
suffix:semicolon
multiline_comment|/* lock during free block list manipulation */
DECL|member|s_ilock
r_char
id|s_ilock
suffix:semicolon
multiline_comment|/* lock during inode cache manipulation */
DECL|member|s_fmod
r_char
id|s_fmod
suffix:semicolon
multiline_comment|/* super-block modified flag */
DECL|member|s_ronly
r_char
id|s_ronly
suffix:semicolon
multiline_comment|/* flag whether fs is mounted read-only */
DECL|member|__packed2__
id|u32
id|s_time
id|__packed2__
suffix:semicolon
multiline_comment|/* time of last super block update */
DECL|member|__packed2__
id|u32
id|s_tfree
id|__packed2__
suffix:semicolon
multiline_comment|/* total number of free zones */
DECL|member|s_tinode
id|u16
id|s_tinode
suffix:semicolon
multiline_comment|/* total number of free inodes */
DECL|member|s_interleave_m
id|u16
id|s_interleave_m
suffix:semicolon
multiline_comment|/* interleave factor */
DECL|member|s_interleave_n
id|u16
id|s_interleave_n
suffix:semicolon
DECL|member|s_fname
r_char
id|s_fname
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system volume name */
DECL|member|s_fpack
r_char
id|s_fpack
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system pack name */
DECL|member|s_unique
id|u32
id|s_unique
suffix:semicolon
multiline_comment|/* zero, not used */
)brace
suffix:semicolon
multiline_comment|/* SystemV/Coherent inode data on disk */
DECL|struct|sysv_inode
r_struct
id|sysv_inode
(brace
DECL|member|i_mode
id|u16
id|i_mode
suffix:semicolon
DECL|member|i_nlink
id|u16
id|i_nlink
suffix:semicolon
DECL|member|i_uid
id|u16
id|i_uid
suffix:semicolon
DECL|member|i_gid
id|u16
id|i_gid
suffix:semicolon
DECL|member|i_size
id|u32
id|i_size
suffix:semicolon
DECL|member|i_data
id|u8
id|i_data
(braket
l_int|3
op_star
(paren
l_int|10
op_plus
l_int|1
op_plus
l_int|1
op_plus
l_int|1
)paren
)braket
suffix:semicolon
DECL|member|i_gen
id|u8
id|i_gen
suffix:semicolon
DECL|member|i_atime
id|u32
id|i_atime
suffix:semicolon
multiline_comment|/* time of last access */
DECL|member|i_mtime
id|u32
id|i_mtime
suffix:semicolon
multiline_comment|/* time of last modification */
DECL|member|i_ctime
id|u32
id|i_ctime
suffix:semicolon
multiline_comment|/* time of creation */
)brace
suffix:semicolon
multiline_comment|/* SystemV/Coherent directory entry on disk */
DECL|macro|SYSV_NAMELEN
mdefine_line|#define SYSV_NAMELEN&t;14&t;/* max size of name in struct sysv_dir_entry */
DECL|struct|sysv_dir_entry
r_struct
id|sysv_dir_entry
(brace
DECL|member|inode
id|sysv_ino_t
id|inode
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|SYSV_NAMELEN
)braket
suffix:semicolon
multiline_comment|/* up to 14 characters, the rest are zeroes */
)brace
suffix:semicolon
DECL|macro|SYSV_DIRSIZE
mdefine_line|#define SYSV_DIRSIZE&t;sizeof(struct sysv_dir_entry)&t;/* size of every directory entry */
macro_line|#endif /* _LINUX_SYSV_FS_H */
eof
