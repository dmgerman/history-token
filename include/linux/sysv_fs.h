macro_line|#ifndef _LINUX_SYSV_FS_H
DECL|macro|_LINUX_SYSV_FS_H
mdefine_line|#define _LINUX_SYSV_FS_H
multiline_comment|/*&n; * The SystemV/Coherent filesystem constants/structures/macros&n; */
multiline_comment|/* This code assumes&n;   - sizeof(short) = 2, sizeof(int) = 4, sizeof(long) = 4,&n;   - alignof(short) = 2, alignof(long) = 4.&n;*/
macro_line|#ifdef __GNUC__
DECL|macro|__packed2__
mdefine_line|#define __packed2__  __attribute__ ((packed, aligned(2)))
macro_line|#else
macro_line|#error I want gcc!
macro_line|#endif
macro_line|#include &lt;linux/stat.h&gt;&t;&t;/* declares S_IFLNK etc. */
macro_line|#include &lt;linux/sched.h&gt;&t;/* declares wake_up() */
macro_line|#include &lt;linux/sysv_fs_sb.h&gt;&t;/* defines the sv_... shortcuts */
multiline_comment|/* Layout on disk */
multiline_comment|/* ============== */
DECL|function|PDP_swab
r_static
r_inline
id|u32
id|PDP_swab
c_func
(paren
id|u32
id|x
)paren
(brace
macro_line|#ifdef __LITTLE_ENDIAN
r_return
(paren
(paren
id|x
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0xffff0000
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
macro_line|#else
macro_line|#ifdef __BIG_ENDIAN
r_return
(paren
(paren
id|x
op_amp
l_int|0xff00ff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0xff00ff00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
macro_line|#else
macro_line|#error BYTESEX
macro_line|#endif
macro_line|#endif
)brace
multiline_comment|/* inode numbers are 16 bit */
DECL|typedef|sysv_ino_t
r_typedef
id|u16
id|sysv_ino_t
suffix:semicolon
multiline_comment|/* Block numbers are 24 bit, sometimes stored in 32 bit.&n;   On Coherent FS, they are always stored in PDP-11 manner: the least&n;   significant 16 bits come last.&n;*/
DECL|typedef|sysv_zone_t
r_typedef
id|u32
id|sysv_zone_t
suffix:semicolon
multiline_comment|/* Among the blocks ... */
multiline_comment|/* Xenix FS, Coherent FS: block 0 is the boot block, block 1 the super-block.&n;   SystemV FS: block 0 contains both the boot sector and the super-block. */
multiline_comment|/* The first inode zone is sb-&gt;sv_firstinodezone (1 or 2). */
multiline_comment|/* Among the inodes ... */
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
multiline_comment|/* SystemV FS comes in two variants:&n; * sysv2: System V Release 2 (e.g. Microport), structure elements aligned(2).&n; * sysv4: System V Release 4 (e.g. Consensys), structure elements aligned(4).&n; */
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
r_union
(brace
multiline_comment|/* directories, regular files, ... */
DECL|member|i_addb
r_int
r_char
id|i_addb
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
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* zone numbers: max. 10 data blocks,&n;&t;&t;&t;&t;&t;      * then 1 indirection block,&n;&t;&t;&t;&t;&t;      * then 1 double indirection block,&n;&t;&t;&t;&t;&t;      * then 1 triple indirection block.&n;&t;&t;&t;&t;&t;      * Then maybe a &quot;file generation number&quot; ??&n;&t;&t;&t;&t;&t;      */
multiline_comment|/* named pipes on Coherent */
r_struct
(brace
DECL|member|p_addp
r_char
id|p_addp
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|p_pnc
id|s16
id|p_pnc
suffix:semicolon
DECL|member|p_prx
id|s16
id|p_prx
suffix:semicolon
DECL|member|p_pwx
id|s16
id|p_pwx
suffix:semicolon
DECL|member|i_p
)brace
id|i_p
suffix:semicolon
DECL|member|i_a
)brace
id|i_a
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
multiline_comment|/* The admissible values for i_mode are listed in &lt;linux/stat.h&gt; :&n; * #define S_IFMT  00170000  mask for type&n; * #define S_IFREG  0100000  type = regular file&n; * #define S_IFBLK  0060000  type = block device&n; * #define S_IFDIR  0040000  type = directory&n; * #define S_IFCHR  0020000  type = character device&n; * #define S_IFIFO  0010000  type = named pipe&n; * #define S_ISUID  0004000  set user id&n; * #define S_ISGID  0002000  set group id&n; * #define S_ISVTX  0001000  save swapped text even after use&n; * Additionally for SystemV:&n; * #define S_IFLNK  0120000  type = symbolic link&n; * #define S_IFNAM  0050000  type = XENIX special named file ??&n; * Additionally for Coherent:&n; * #define S_IFMPB  0070000  type = multiplexed block device ??&n; * #define S_IFMPC  0030000  type = multiplexed character device ??&n; *&n; * Since Coherent doesn&squot;t know about symbolic links, we use a kludgey&n; * implementation of symbolic links: i_mode = COH_KLUDGE_SYMLINK_MODE&n; * denotes a symbolic link. When a regular file should get this mode by&n; * accident, it is automatically converted to COH_KLUDGE_NOT_SYMLINK.&n; * We use S_IFREG because only regular files (and Coherent pipes...) can have&n; * data blocks with arbitrary contents associated with them, and S_ISVTX&n; * (&quot;save swapped text after use&quot;) because it is unused on both Linux and&n; * Coherent: Linux does much more intelligent paging, and Coherent hasn&squot;t&n; * virtual memory at all.&n; * Same trick for Xenix.&n; */
DECL|macro|COH_KLUDGE_SYMLINK_MODE
mdefine_line|#define COH_KLUDGE_SYMLINK_MODE&t;(S_IFREG | S_ISVTX)
DECL|macro|COH_KLUDGE_NOT_SYMLINK
mdefine_line|#define COH_KLUDGE_NOT_SYMLINK&t;(S_IFREG | S_ISVTX | S_IRUSR) /* force read access */
DECL|function|from_coh_imode
r_static
r_inline
id|mode_t
id|from_coh_imode
c_func
(paren
r_int
r_int
id|mode
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
id|COH_KLUDGE_SYMLINK_MODE
)paren
r_return
(paren
id|S_IFLNK
op_or
l_int|0777
)paren
suffix:semicolon
r_else
r_return
id|mode
suffix:semicolon
)brace
DECL|function|to_coh_imode
r_static
r_inline
r_int
r_int
id|to_coh_imode
c_func
(paren
id|mode_t
id|mode
)paren
(brace
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
r_return
id|COH_KLUDGE_SYMLINK_MODE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mode
op_eq
id|COH_KLUDGE_SYMLINK_MODE
)paren
r_return
id|COH_KLUDGE_NOT_SYMLINK
suffix:semicolon
r_else
r_return
id|mode
suffix:semicolon
)brace
multiline_comment|/* Admissible values for i_nlink: 0.._LINK_MAX */
r_enum
(brace
DECL|enumerator|XENIX_LINK_MAX
id|XENIX_LINK_MAX
op_assign
l_int|126
comma
multiline_comment|/* ?? */
DECL|enumerator|SYSV_LINK_MAX
id|SYSV_LINK_MAX
op_assign
l_int|126
comma
multiline_comment|/* 127? 251? */
DECL|enumerator|V7_LINK_MAX
id|V7_LINK_MAX
op_assign
l_int|126
comma
multiline_comment|/* ?? */
DECL|enumerator|COH_LINK_MAX
id|COH_LINK_MAX
op_assign
l_int|10000
comma
)brace
suffix:semicolon
multiline_comment|/* The number of inodes per block is&n;   sb-&gt;sv_inodes_per_block = block_size / sizeof(struct sysv_inode) */
multiline_comment|/* The number of indirect pointers per block is&n;   sb-&gt;sv_ind_per_block = block_size / sizeof(u32) */
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
multiline_comment|/* Operations */
multiline_comment|/* ========== */
multiline_comment|/* identify the FS in memory */
r_enum
(brace
DECL|enumerator|FSTYPE_NONE
id|FSTYPE_NONE
op_assign
l_int|0
comma
DECL|enumerator|FSTYPE_XENIX
id|FSTYPE_XENIX
comma
DECL|enumerator|FSTYPE_SYSV4
id|FSTYPE_SYSV4
comma
DECL|enumerator|FSTYPE_SYSV2
id|FSTYPE_SYSV2
comma
DECL|enumerator|FSTYPE_COH
id|FSTYPE_COH
comma
DECL|enumerator|FSTYPE_V7
id|FSTYPE_V7
comma
DECL|enumerator|FSTYPE_AFS
id|FSTYPE_AFS
comma
DECL|enumerator|FSTYPE_END
id|FSTYPE_END
comma
)brace
suffix:semicolon
DECL|macro|SYSV_MAGIC_BASE
mdefine_line|#define SYSV_MAGIC_BASE&t;&t;0x012FF7B3
DECL|macro|XENIX_SUPER_MAGIC
mdefine_line|#define XENIX_SUPER_MAGIC&t;(SYSV_MAGIC_BASE+FSTYPE_XENIX)
DECL|macro|SYSV4_SUPER_MAGIC
mdefine_line|#define SYSV4_SUPER_MAGIC&t;(SYSV_MAGIC_BASE+FSTYPE_SYSV4)
DECL|macro|SYSV2_SUPER_MAGIC
mdefine_line|#define SYSV2_SUPER_MAGIC&t;(SYSV_MAGIC_BASE+FSTYPE_SYSV2)
DECL|macro|COH_SUPER_MAGIC
mdefine_line|#define COH_SUPER_MAGIC&t;&t;(SYSV_MAGIC_BASE+FSTYPE_COH)
macro_line|#ifdef __KERNEL__
r_enum
(brace
DECL|enumerator|BYTESEX_LE
id|BYTESEX_LE
comma
DECL|enumerator|BYTESEX_PDP
id|BYTESEX_PDP
comma
DECL|enumerator|BYTESEX_BE
id|BYTESEX_BE
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Function prototypes&n; */
r_extern
r_struct
id|inode
op_star
id|sysv_new_inode
c_func
(paren
r_const
r_struct
id|inode
op_star
comma
id|mode_t
)paren
suffix:semicolon
r_extern
r_void
id|sysv_free_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sysv_count_free_inodes
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
id|u32
id|sysv_new_block
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sysv_free_block
c_func
(paren
r_struct
id|super_block
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sysv_count_free_blocks
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sysv_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sysv_write_inode
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sysv_sync_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysv_sync_file
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sysv_notify_change
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sysv_set_inode
c_func
(paren
r_struct
id|inode
op_star
comma
id|dev_t
)paren
suffix:semicolon
r_extern
r_struct
id|sysv_dir_entry
op_star
id|sysv_find_entry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|page
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysv_add_link
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysv_delete_entry
c_func
(paren
r_struct
id|sysv_dir_entry
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysv_make_empty
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysv_empty_dir
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sysv_set_link
c_func
(paren
r_struct
id|sysv_dir_entry
op_star
comma
r_struct
id|page
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|sysv_dir_entry
op_star
id|sysv_dotdot
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|page
op_star
op_star
)paren
suffix:semicolon
r_extern
id|ino_t
id|sysv_inode_by_name
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|sysv_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|sysv_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|sysv_fast_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|sysv_file_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|sysv_dir_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|sysv_aops
suffix:semicolon
r_extern
r_struct
id|super_operations
id|sysv_sops
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|sysv_dentry_operations
suffix:semicolon
r_extern
r_struct
id|sysv_inode
op_star
id|sysv_raw_inode
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
DECL|function|dirty_sb
r_static
r_inline
r_void
id|dirty_sb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;sv_bh1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_bh1
op_ne
id|sb-&gt;sv_bh2
)paren
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;sv_bh2
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|fs32_to_cpu
r_static
r_inline
id|u32
id|fs32_to_cpu
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u32
id|n
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_eq
id|BYTESEX_PDP
)paren
r_return
id|PDP_swab
c_func
(paren
id|n
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_eq
id|BYTESEX_LE
)paren
r_return
id|le32_to_cpu
c_func
(paren
id|n
)paren
suffix:semicolon
r_else
r_return
id|be32_to_cpu
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_fs32
r_static
r_inline
id|u32
id|cpu_to_fs32
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u32
id|n
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_eq
id|BYTESEX_PDP
)paren
r_return
id|PDP_swab
c_func
(paren
id|n
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_eq
id|BYTESEX_LE
)paren
r_return
id|cpu_to_le32
c_func
(paren
id|n
)paren
suffix:semicolon
r_else
r_return
id|cpu_to_be32
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
DECL|function|fs32_add
r_static
r_inline
id|u32
id|fs32_add
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u32
op_star
id|n
comma
r_int
id|d
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_eq
id|BYTESEX_PDP
)paren
r_return
op_star
id|n
op_assign
id|PDP_swab
c_func
(paren
id|PDP_swab
c_func
(paren
op_star
id|n
)paren
op_plus
id|d
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_eq
id|BYTESEX_LE
)paren
r_return
op_star
id|n
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
op_star
id|n
)paren
op_plus
id|d
)paren
suffix:semicolon
r_else
r_return
op_star
id|n
op_assign
id|cpu_to_be32
c_func
(paren
id|be32_to_cpu
c_func
(paren
op_star
id|n
)paren
op_plus
id|d
)paren
suffix:semicolon
)brace
DECL|function|fs16_to_cpu
r_static
r_inline
id|u16
id|fs16_to_cpu
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u16
id|n
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_ne
id|BYTESEX_BE
)paren
r_return
id|le16_to_cpu
c_func
(paren
id|n
)paren
suffix:semicolon
r_else
r_return
id|be16_to_cpu
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_fs16
r_static
r_inline
id|u16
id|cpu_to_fs16
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u16
id|n
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_ne
id|BYTESEX_BE
)paren
r_return
id|cpu_to_le16
c_func
(paren
id|n
)paren
suffix:semicolon
r_else
r_return
id|cpu_to_be16
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
DECL|function|fs16_add
r_static
r_inline
id|u16
id|fs16_add
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u16
op_star
id|n
comma
r_int
id|d
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;sv_bytesex
op_ne
id|BYTESEX_BE
)paren
r_return
op_star
id|n
op_assign
id|cpu_to_le16
c_func
(paren
id|le16_to_cpu
c_func
(paren
op_star
id|n
)paren
op_plus
id|d
)paren
suffix:semicolon
r_else
r_return
op_star
id|n
op_assign
id|cpu_to_be16
c_func
(paren
id|be16_to_cpu
c_func
(paren
op_star
id|n
)paren
op_plus
id|d
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
