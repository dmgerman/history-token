macro_line|#ifndef _LINUX_STAT_H
DECL|macro|_LINUX_STAT_H
mdefine_line|#define _LINUX_STAT_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/stat.h&gt;
macro_line|#endif
macro_line|#if defined(__KERNEL__) || !defined(__GLIBC__) || (__GLIBC__ &lt; 2)
DECL|macro|S_IFMT
mdefine_line|#define S_IFMT  00170000
DECL|macro|S_IFSOCK
mdefine_line|#define S_IFSOCK 0140000
DECL|macro|S_IFLNK
mdefine_line|#define S_IFLNK&t; 0120000
DECL|macro|S_IFREG
mdefine_line|#define S_IFREG  0100000
DECL|macro|S_IFBLK
mdefine_line|#define S_IFBLK  0060000
DECL|macro|S_IFDIR
mdefine_line|#define S_IFDIR  0040000
DECL|macro|S_IFCHR
mdefine_line|#define S_IFCHR  0020000
DECL|macro|S_IFIFO
mdefine_line|#define S_IFIFO  0010000
DECL|macro|S_ISUID
mdefine_line|#define S_ISUID  0004000
DECL|macro|S_ISGID
mdefine_line|#define S_ISGID  0002000
DECL|macro|S_ISVTX
mdefine_line|#define S_ISVTX  0001000
DECL|macro|S_ISLNK
mdefine_line|#define S_ISLNK(m)&t;(((m) &amp; S_IFMT) == S_IFLNK)
DECL|macro|S_ISREG
mdefine_line|#define S_ISREG(m)&t;(((m) &amp; S_IFMT) == S_IFREG)
DECL|macro|S_ISDIR
mdefine_line|#define S_ISDIR(m)&t;(((m) &amp; S_IFMT) == S_IFDIR)
DECL|macro|S_ISCHR
mdefine_line|#define S_ISCHR(m)&t;(((m) &amp; S_IFMT) == S_IFCHR)
DECL|macro|S_ISBLK
mdefine_line|#define S_ISBLK(m)&t;(((m) &amp; S_IFMT) == S_IFBLK)
DECL|macro|S_ISFIFO
mdefine_line|#define S_ISFIFO(m)&t;(((m) &amp; S_IFMT) == S_IFIFO)
DECL|macro|S_ISSOCK
mdefine_line|#define S_ISSOCK(m)&t;(((m) &amp; S_IFMT) == S_IFSOCK)
DECL|macro|S_IRWXU
mdefine_line|#define S_IRWXU 00700
DECL|macro|S_IRUSR
mdefine_line|#define S_IRUSR 00400
DECL|macro|S_IWUSR
mdefine_line|#define S_IWUSR 00200
DECL|macro|S_IXUSR
mdefine_line|#define S_IXUSR 00100
DECL|macro|S_IRWXG
mdefine_line|#define S_IRWXG 00070
DECL|macro|S_IRGRP
mdefine_line|#define S_IRGRP 00040
DECL|macro|S_IWGRP
mdefine_line|#define S_IWGRP 00020
DECL|macro|S_IXGRP
mdefine_line|#define S_IXGRP 00010
DECL|macro|S_IRWXO
mdefine_line|#define S_IRWXO 00007
DECL|macro|S_IROTH
mdefine_line|#define S_IROTH 00004
DECL|macro|S_IWOTH
mdefine_line|#define S_IWOTH 00002
DECL|macro|S_IXOTH
mdefine_line|#define S_IXOTH 00001
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|macro|S_IRWXUGO
mdefine_line|#define S_IRWXUGO&t;(S_IRWXU|S_IRWXG|S_IRWXO)
DECL|macro|S_IALLUGO
mdefine_line|#define S_IALLUGO&t;(S_ISUID|S_ISGID|S_ISVTX|S_IRWXUGO)
DECL|macro|S_IRUGO
mdefine_line|#define S_IRUGO&t;&t;(S_IRUSR|S_IRGRP|S_IROTH)
DECL|macro|S_IWUGO
mdefine_line|#define S_IWUGO&t;&t;(S_IWUSR|S_IWGRP|S_IWOTH)
DECL|macro|S_IXUGO
mdefine_line|#define S_IXUGO&t;&t;(S_IXUSR|S_IXGRP|S_IXOTH)
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|kstat
r_struct
id|kstat
(brace
DECL|member|ino
r_int
r_int
id|ino
suffix:semicolon
DECL|member|dev
id|dev_t
id|dev
suffix:semicolon
DECL|member|mode
id|umode_t
id|mode
suffix:semicolon
DECL|member|nlink
id|nlink_t
id|nlink
suffix:semicolon
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
DECL|member|rdev
id|dev_t
id|rdev
suffix:semicolon
DECL|member|size
id|loff_t
id|size
suffix:semicolon
DECL|member|atime
id|time_t
id|atime
suffix:semicolon
DECL|member|mtime
id|time_t
id|mtime
suffix:semicolon
DECL|member|ctime
id|time_t
id|ctime
suffix:semicolon
DECL|member|blksize
r_int
r_int
id|blksize
suffix:semicolon
DECL|member|blocks
r_int
r_int
id|blocks
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
