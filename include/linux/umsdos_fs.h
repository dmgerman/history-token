macro_line|#ifndef LINUX_UMSDOS_FS_H
DECL|macro|LINUX_UMSDOS_FS_H
mdefine_line|#define LINUX_UMSDOS_FS_H
multiline_comment|/*#define UMS_DEBUG 1&t;// define for check_* functions */
multiline_comment|/*#define UMSDOS_DEBUG 1*/
DECL|macro|UMSDOS_PARANOIA
mdefine_line|#define UMSDOS_PARANOIA 1
DECL|macro|UMSDOS_VERSION
mdefine_line|#define UMSDOS_VERSION&t;0
DECL|macro|UMSDOS_RELEASE
mdefine_line|#define UMSDOS_RELEASE&t;4
DECL|macro|UMSDOS_ROOT_INO
mdefine_line|#define UMSDOS_ROOT_INO 1
multiline_comment|/* This is the file acting as a directory extension */
DECL|macro|UMSDOS_EMD_FILE
mdefine_line|#define UMSDOS_EMD_FILE&t;&t;&quot;--linux-.---&quot;
DECL|macro|UMSDOS_EMD_NAMELEN
mdefine_line|#define UMSDOS_EMD_NAMELEN&t;12
DECL|macro|UMSDOS_PSDROOT_NAME
mdefine_line|#define UMSDOS_PSDROOT_NAME&t;&quot;linux&quot;
DECL|macro|UMSDOS_PSDROOT_LEN
mdefine_line|#define UMSDOS_PSDROOT_LEN&t;5
macro_line|#ifndef _LINUX_TYPES_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
macro_line|#ifndef _LINUX_LIMITS_H
macro_line|#include &lt;linux/limits.h&gt;
macro_line|#endif
macro_line|#ifndef _LINUX_DIRENT_H
macro_line|#include &lt;linux/dirent.h&gt;
macro_line|#endif
macro_line|#ifndef _LINUX_IOCTL_H
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/* #Specification: convention / PRINTK Printk and printk&n; * Here is the convention for the use of printk inside fs/umsdos&n; * &n; * printk carry important message (error or status).&n; * Printk is for debugging (it is a macro defined at the beginning of&n; * most source.&n; * PRINTK is a nulled Printk macro.&n; * &n; * This convention makes the source easier to read, and Printk easier&n; * to shut off.&n; */
DECL|macro|PRINTK
macro_line|#&t;define PRINTK(x)
macro_line|#&t;ifdef UMSDOS_DEBUG
DECL|macro|Printk
macro_line|#&t;&t;define Printk(x) printk x
macro_line|#&t;else
DECL|macro|Printk
macro_line|#&t;&t;define Printk(x)
macro_line|#&t;endif
macro_line|#endif
DECL|struct|umsdos_fake_info
r_struct
id|umsdos_fake_info
(brace
DECL|member|fname
r_char
id|fname
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|UMSDOS_MAXNAME
mdefine_line|#define UMSDOS_MAXNAME&t;220
multiline_comment|/* This structure is 256 bytes large, depending on the name, only part */
multiline_comment|/* of it is written to disk */
multiline_comment|/* nice though it would be, I can&squot;t change this and preserve backward compatibility */
DECL|struct|umsdos_dirent
r_struct
id|umsdos_dirent
(brace
DECL|member|name_len
r_int
r_char
id|name_len
suffix:semicolon
multiline_comment|/* if == 0, then this entry is not used */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* UMSDOS_xxxx */
DECL|member|nlink
r_int
r_int
id|nlink
suffix:semicolon
multiline_comment|/* How many hard links point to this entry */
DECL|member|uid
id|__kernel_uid_t
id|uid
suffix:semicolon
multiline_comment|/* Owner user id */
DECL|member|gid
id|__kernel_gid_t
id|gid
suffix:semicolon
multiline_comment|/* Group id */
DECL|member|atime
id|time_t
id|atime
suffix:semicolon
multiline_comment|/* Access time */
DECL|member|mtime
id|time_t
id|mtime
suffix:semicolon
multiline_comment|/* Last modification time */
DECL|member|ctime
id|time_t
id|ctime
suffix:semicolon
multiline_comment|/* Creation time */
DECL|member|rdev
id|dev_t
id|rdev
suffix:semicolon
multiline_comment|/* major and minor number of a device */
multiline_comment|/* special file */
DECL|member|mode
id|umode_t
id|mode
suffix:semicolon
multiline_comment|/* Standard UNIX permissions bits + type of */
DECL|member|spare
r_char
id|spare
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* unused bytes for future extensions */
multiline_comment|/* file, see linux/stat.h */
DECL|member|name
r_char
id|name
(braket
id|UMSDOS_MAXNAME
)braket
suffix:semicolon
multiline_comment|/* Not &squot;&bslash;0&squot; terminated */
multiline_comment|/* but &squot;&bslash;0&squot; padded, so it will allow */
multiline_comment|/* for adding news fields in this record */
multiline_comment|/* by reducing the size of name[] */
)brace
suffix:semicolon
DECL|macro|UMSDOS_HIDDEN
mdefine_line|#define UMSDOS_HIDDEN&t;1&t;/* Never show this entry in directory search */
DECL|macro|UMSDOS_HLINK
mdefine_line|#define UMSDOS_HLINK&t;2&t;/* It is a (pseudo) hard link */
multiline_comment|/* #Specification: EMD file / record size&n; * Entry are 64 bytes wide in the EMD file. It allows for a 30 characters&n; * name. If a name is longer, contiguous entries are allocated. So a&n; * umsdos_dirent may span multiple records.&n; */
DECL|macro|UMSDOS_REC_SIZE
mdefine_line|#define UMSDOS_REC_SIZE&t;&t;64
multiline_comment|/* Translation between MSDOS name and UMSDOS name */
DECL|struct|umsdos_info
r_struct
id|umsdos_info
(brace
DECL|member|msdos_reject
r_int
id|msdos_reject
suffix:semicolon
multiline_comment|/* Tell if the file name is invalid for MSDOS */
multiline_comment|/* See umsdos_parse */
DECL|member|fake
r_struct
id|umsdos_fake_info
id|fake
suffix:semicolon
DECL|member|entry
r_struct
id|umsdos_dirent
id|entry
suffix:semicolon
DECL|member|f_pos
id|off_t
id|f_pos
suffix:semicolon
multiline_comment|/* offset of the entry in the EMD file&n;&t;&t;&t;&t; * or offset where the entry may be store&n;&t;&t;&t;&t; * if it is a new entry&n;&t;&t;&t;&t; */
DECL|member|recsize
r_int
id|recsize
suffix:semicolon
multiline_comment|/* Record size needed to store entry */
)brace
suffix:semicolon
multiline_comment|/* Definitions for ioctl (number randomly chosen)&n; * The next ioctl commands operate only on the DOS directory&n; * The file umsdos_progs/umsdosio.c contain a string table&n; * based on the order of those definition. Keep it in sync&n; */
DECL|macro|UMSDOS_READDIR_DOS
mdefine_line|#define UMSDOS_READDIR_DOS _IO(0x04,210)&t;/* Do a readdir of the DOS directory */
DECL|macro|UMSDOS_UNLINK_DOS
mdefine_line|#define UMSDOS_UNLINK_DOS  _IO(0x04,211)&t;/* Erase in the DOS directory only */
DECL|macro|UMSDOS_RMDIR_DOS
mdefine_line|#define UMSDOS_RMDIR_DOS   _IO(0x04,212)&t;/* rmdir in the DOS directory only */
DECL|macro|UMSDOS_STAT_DOS
mdefine_line|#define UMSDOS_STAT_DOS    _IO(0x04,213)&t;/* Get info about a file */
multiline_comment|/* The next ioctl commands operate only on the EMD file */
DECL|macro|UMSDOS_CREAT_EMD
mdefine_line|#define UMSDOS_CREAT_EMD   _IO(0x04,214)&t;/* Create a file */
DECL|macro|UMSDOS_UNLINK_EMD
mdefine_line|#define UMSDOS_UNLINK_EMD  _IO(0x04,215)&t;/* unlink (rmdir) a file */
DECL|macro|UMSDOS_READDIR_EMD
mdefine_line|#define UMSDOS_READDIR_EMD _IO(0x04,216)&t;/* read the EMD file only. */
DECL|macro|UMSDOS_GETVERSION
mdefine_line|#define UMSDOS_GETVERSION  _IO(0x04,217)&t;/* Get the release number of UMSDOS */
DECL|macro|UMSDOS_INIT_EMD
mdefine_line|#define UMSDOS_INIT_EMD    _IO(0x04,218)&t;/* Create the EMD file if not there */
DECL|macro|UMSDOS_DOS_SETUP
mdefine_line|#define UMSDOS_DOS_SETUP   _IO(0x04,219)&t;/* Set the defaults of the MS-DOS driver. */
DECL|macro|UMSDOS_RENAME_DOS
mdefine_line|#define UMSDOS_RENAME_DOS  _IO(0x04,220)&t;/* rename a file/directory in the DOS&n;&t;&t;&t;&t;&t;&t; * directory only */
DECL|struct|umsdos_ioctl
r_struct
id|umsdos_ioctl
(brace
DECL|member|dos_dirent
r_struct
id|dirent
id|dos_dirent
suffix:semicolon
DECL|member|umsdos_dirent
r_struct
id|umsdos_dirent
id|umsdos_dirent
suffix:semicolon
multiline_comment|/* The following structure is used to exchange some data&n;&t; * with utilities (umsdos_progs/util/umsdosio.c). The first&n;&t; * releases were using struct stat from &quot;sys/stat.h&quot;. This was&n;&t; * causing some problem for cross compilation of the kernel&n;&t; * Since I am not really using the structure stat, but only some field&n;&t; * of it, I have decided to replicate the structure here&n;&t; * for compatibility with the binaries out there&n;&t; * FIXME PTW 1998, this has probably changed&n;&t; */
r_struct
(brace
DECL|member|st_dev
id|dev_t
id|st_dev
suffix:semicolon
DECL|member|__pad1
r_int
r_int
id|__pad1
suffix:semicolon
DECL|member|st_ino
id|ino_t
id|st_ino
suffix:semicolon
DECL|member|st_mode
id|umode_t
id|st_mode
suffix:semicolon
DECL|member|st_nlink
id|nlink_t
id|st_nlink
suffix:semicolon
DECL|member|st_uid
id|__kernel_uid_t
id|st_uid
suffix:semicolon
DECL|member|st_gid
id|__kernel_gid_t
id|st_gid
suffix:semicolon
DECL|member|st_rdev
id|dev_t
id|st_rdev
suffix:semicolon
DECL|member|__pad2
r_int
r_int
id|__pad2
suffix:semicolon
DECL|member|st_size
id|off_t
id|st_size
suffix:semicolon
DECL|member|st_blksize
r_int
r_int
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
r_int
r_int
id|st_blocks
suffix:semicolon
DECL|member|st_atime
id|time_t
id|st_atime
suffix:semicolon
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
DECL|member|st_mtime
id|time_t
id|st_mtime
suffix:semicolon
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
DECL|member|st_ctime
id|time_t
id|st_ctime
suffix:semicolon
DECL|member|__unused3
r_int
r_int
id|__unused3
suffix:semicolon
DECL|member|st_uid32
id|uid_t
id|st_uid32
suffix:semicolon
DECL|member|st_gid32
id|gid_t
id|st_gid32
suffix:semicolon
DECL|member|stat
)brace
id|stat
suffix:semicolon
DECL|member|version
DECL|member|release
r_char
id|version
comma
id|release
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Different macros to access struct umsdos_dirent */
DECL|macro|EDM_ENTRY_ISUSED
mdefine_line|#define EDM_ENTRY_ISUSED(e) ((e)-&gt;name_len!=0)
macro_line|#ifdef __KERNEL__
macro_line|#ifndef LINUX_FS_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#endif
r_extern
r_struct
id|inode_operations
id|umsdos_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|umsdos_rdir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|umsdos_dir_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|umsdos_rdir_operations
suffix:semicolon
macro_line|#include &lt;linux/umsdos_fs.p&gt;
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif
eof
