multiline_comment|/* &n;   You may distribute this file under either of the two licenses that&n;   follow at your discretion.&n;*/
multiline_comment|/* BLURB lgpl&n;&n;                           Coda File System&n;                              Release 5&n;&n;          Copyright (c) 1987-1999 Carnegie Mellon University&n;                  Additional copyrights listed below&n;&n;This code is distributed &quot;AS IS&quot; without warranty of any kind under&n;the terms of the GNU Library General Public Licence Version 2, as&n;shown in the file LICENSE, or under the license shown below. The&n;technical and financial contributors to Coda are listed in the file&n;CREDITS.&n;&n;                        Additional copyrights &n;*/
multiline_comment|/*&n;&n;            Coda: an Experimental Distributed File System&n;                             Release 4.0&n;&n;          Copyright (c) 1987-1999 Carnegie Mellon University&n;                         All Rights Reserved&n;&n;Permission  to  use, copy, modify and distribute this software and its&n;documentation is hereby granted,  provided  that  both  the  copyright&n;notice  and  this  permission  notice  appear  in  all  copies  of the&n;software, derivative works or  modified  versions,  and  any  portions&n;thereof, and that both notices appear in supporting documentation, and&n;that credit is given to Carnegie Mellon University  in  all  documents&n;and publicity pertaining to direct or indirect use of this code or its&n;derivatives.&n;&n;CODA IS AN EXPERIMENTAL SOFTWARE SYSTEM AND IS  KNOWN  TO  HAVE  BUGS,&n;SOME  OF  WHICH MAY HAVE SERIOUS CONSEQUENCES.  CARNEGIE MELLON ALLOWS&n;FREE USE OF THIS SOFTWARE IN ITS &quot;AS IS&quot; CONDITION.   CARNEGIE  MELLON&n;DISCLAIMS  ANY  LIABILITY  OF  ANY  KIND  FOR  ANY  DAMAGES WHATSOEVER&n;RESULTING DIRECTLY OR INDIRECTLY FROM THE USE OF THIS SOFTWARE  OR  OF&n;ANY DERIVATIVE WORK.&n;&n;Carnegie  Mellon  encourages  users  of  this  software  to return any&n;improvements or extensions that  they  make,  and  to  grant  Carnegie&n;Mellon the rights to redistribute these changes without encumbrance.&n;*/
multiline_comment|/*&n; *&n; * Based on cfs.h from Mach, but revamped for increased simplicity.&n; * Linux modifications by &n; * Peter Braam, Aug 1996&n; */
macro_line|#ifndef _CODA_HEADER_
DECL|macro|_CODA_HEADER_
mdefine_line|#define _CODA_HEADER_
multiline_comment|/* Catch new _KERNEL defn for NetBSD and DJGPP/__CYGWIN32__ */
macro_line|#if defined(__NetBSD__) || &bslash;&n;  ((defined(DJGPP) || defined(__CYGWIN32__)) &amp;&amp; !defined(KERNEL))
macro_line|#include &lt;sys/types.h&gt;
macro_line|#endif 
macro_line|#ifndef CODA_MAXSYMLINKS
DECL|macro|CODA_MAXSYMLINKS
mdefine_line|#define CODA_MAXSYMLINKS 10
macro_line|#endif
macro_line|#if defined(DJGPP) || defined(__CYGWIN32__)
macro_line|#ifdef KERNEL
DECL|typedef|u_long
r_typedef
r_int
r_int
id|u_long
suffix:semicolon
DECL|typedef|u_int
r_typedef
r_int
r_int
id|u_int
suffix:semicolon
DECL|typedef|u_short
r_typedef
r_int
r_int
id|u_short
suffix:semicolon
DECL|typedef|ino_t
r_typedef
id|u_long
id|ino_t
suffix:semicolon
DECL|typedef|dev_t
r_typedef
id|u_long
id|dev_t
suffix:semicolon
DECL|typedef|caddr_t
r_typedef
r_void
op_star
id|caddr_t
suffix:semicolon
macro_line|#ifdef DOS
DECL|typedef|u_quad_t
r_typedef
r_int
id|__int64
id|u_quad_t
suffix:semicolon
macro_line|#else 
DECL|typedef|u_quad_t
r_typedef
r_int
r_int
r_int
id|u_quad_t
suffix:semicolon
macro_line|#endif
DECL|macro|inline
mdefine_line|#define inline
DECL|struct|timespec
r_struct
id|timespec
(brace
DECL|member|ts_sec
r_int
id|ts_sec
suffix:semicolon
DECL|member|ts_nsec
r_int
id|ts_nsec
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else  /* DJGPP but not KERNEL */
macro_line|#include &lt;sys/time.h&gt;
DECL|typedef|u_quad_t
r_typedef
r_int
r_int
r_int
id|u_quad_t
suffix:semicolon
macro_line|#endif /* !KERNEL */
macro_line|#endif /* !DJGPP */
macro_line|#if defined(__linux__)
macro_line|#include &lt;linux/time.h&gt;
DECL|macro|cdev_t
mdefine_line|#define cdev_t u_quad_t
macro_line|#ifndef __KERNEL__
macro_line|#if !defined(_UQUAD_T_) &amp;&amp; (!defined(__GLIBC__) || __GLIBC__ &lt; 2)
DECL|macro|_UQUAD_T_
mdefine_line|#define _UQUAD_T_ 1
DECL|typedef|u_quad_t
r_typedef
r_int
r_int
r_int
id|u_quad_t
suffix:semicolon
macro_line|#endif
macro_line|#else /*__KERNEL__ */
DECL|typedef|u_quad_t
r_typedef
r_int
r_int
r_int
id|u_quad_t
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#else
DECL|macro|cdev_t
mdefine_line|#define cdev_t dev_t
macro_line|#endif
macro_line|#ifdef __CYGWIN32__
DECL|struct|timespec
r_struct
id|timespec
(brace
DECL|member|tv_sec
id|time_t
id|tv_sec
suffix:semicolon
multiline_comment|/* seconds */
DECL|member|tv_nsec
r_int
id|tv_nsec
suffix:semicolon
multiline_comment|/* nanoseconds */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __BIT_TYPES_DEFINED__
DECL|macro|__BIT_TYPES_DEFINED__
mdefine_line|#define __BIT_TYPES_DEFINED__
DECL|typedef|int8_t
r_typedef
r_int
r_char
r_int8
suffix:semicolon
DECL|typedef|u_int8_t
r_typedef
r_int
r_char
id|u_int8_t
suffix:semicolon
DECL|typedef|int16_t
r_typedef
r_int
r_int16
suffix:semicolon
DECL|typedef|u_int16_t
r_typedef
r_int
r_int
id|u_int16_t
suffix:semicolon
DECL|typedef|int32_t
r_typedef
r_int
r_int32
suffix:semicolon
DECL|typedef|u_int32_t
r_typedef
r_int
r_int
id|u_int32_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Cfs constants&n; */
DECL|macro|CODA_MAXNAMLEN
mdefine_line|#define CODA_MAXNAMLEN   255
DECL|macro|CODA_MAXPATHLEN
mdefine_line|#define CODA_MAXPATHLEN  1024
DECL|macro|CODA_MAXSYMLINK
mdefine_line|#define CODA_MAXSYMLINK  10
multiline_comment|/* these are Coda&squot;s version of O_RDONLY etc combinations&n; * to deal with VFS open modes&n; */
DECL|macro|C_O_READ
mdefine_line|#define&t;C_O_READ&t;0x001
DECL|macro|C_O_WRITE
mdefine_line|#define&t;C_O_WRITE       0x002
DECL|macro|C_O_TRUNC
mdefine_line|#define C_O_TRUNC       0x010
DECL|macro|C_O_EXCL
mdefine_line|#define C_O_EXCL&t;0x100
DECL|macro|C_O_CREAT
mdefine_line|#define C_O_CREAT&t;0x200
multiline_comment|/* these are to find mode bits in Venus */
DECL|macro|C_M_READ
mdefine_line|#define C_M_READ  00400
DECL|macro|C_M_WRITE
mdefine_line|#define C_M_WRITE 00200
multiline_comment|/* for access Venus will use */
DECL|macro|C_A_C_OK
mdefine_line|#define C_A_C_OK    8               /* Test for writing upon create.  */
DECL|macro|C_A_R_OK
mdefine_line|#define C_A_R_OK    4               /* Test for read permission.  */
DECL|macro|C_A_W_OK
mdefine_line|#define C_A_W_OK    2               /* Test for write permission.  */
DECL|macro|C_A_X_OK
mdefine_line|#define C_A_X_OK    1               /* Test for execute permission.  */
DECL|macro|C_A_F_OK
mdefine_line|#define C_A_F_OK    0               /* Test for existence.  */
macro_line|#ifndef _VENUS_DIRENT_T_
DECL|macro|_VENUS_DIRENT_T_
mdefine_line|#define _VENUS_DIRENT_T_ 1
DECL|struct|venus_dirent
r_struct
id|venus_dirent
(brace
DECL|member|d_fileno
r_int
r_int
id|d_fileno
suffix:semicolon
multiline_comment|/* file number of entry */
DECL|member|d_reclen
r_int
r_int
id|d_reclen
suffix:semicolon
multiline_comment|/* length of this record */
DECL|member|d_type
r_int
r_char
id|d_type
suffix:semicolon
multiline_comment|/* file type, see below */
DECL|member|d_namlen
r_int
r_char
id|d_namlen
suffix:semicolon
multiline_comment|/* length of string in d_name */
DECL|member|d_name
r_char
id|d_name
(braket
id|CODA_MAXNAMLEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* name must be no longer than this */
)brace
suffix:semicolon
DECL|macro|DIRSIZ
macro_line|#undef DIRSIZ
DECL|macro|DIRSIZ
mdefine_line|#define DIRSIZ(dp)      ((sizeof (struct venus_dirent) - (CODA_MAXNAMLEN+1)) + &bslash;&n;                         (((dp)-&gt;d_namlen+1 + 3) &amp;~ 3))
multiline_comment|/*&n; * File types&n; */
DECL|macro|CDT_UNKNOWN
mdefine_line|#define&t;CDT_UNKNOWN&t; 0
DECL|macro|CDT_FIFO
mdefine_line|#define&t;CDT_FIFO&t; 1
DECL|macro|CDT_CHR
mdefine_line|#define&t;CDT_CHR&t;&t; 2
DECL|macro|CDT_DIR
mdefine_line|#define&t;CDT_DIR&t;&t; 4
DECL|macro|CDT_BLK
mdefine_line|#define&t;CDT_BLK&t;&t; 6
DECL|macro|CDT_REG
mdefine_line|#define&t;CDT_REG&t;&t; 8
DECL|macro|CDT_LNK
mdefine_line|#define&t;CDT_LNK&t;&t;10
DECL|macro|CDT_SOCK
mdefine_line|#define&t;CDT_SOCK&t;12
DECL|macro|CDT_WHT
mdefine_line|#define&t;CDT_WHT&t;&t;14
multiline_comment|/*&n; * Convert between stat structure types and directory types.&n; */
DECL|macro|IFTOCDT
mdefine_line|#define&t;IFTOCDT(mode)&t;(((mode) &amp; 0170000) &gt;&gt; 12)
DECL|macro|CDTTOIF
mdefine_line|#define&t;CDTTOIF(dirtype)&t;((dirtype) &lt;&lt; 12)
macro_line|#endif
macro_line|#ifndef&t;_FID_T_
DECL|macro|_FID_T_
mdefine_line|#define _FID_T_&t;1
DECL|typedef|VolumeId
r_typedef
id|u_long
id|VolumeId
suffix:semicolon
DECL|typedef|VnodeId
r_typedef
id|u_long
id|VnodeId
suffix:semicolon
DECL|typedef|Unique_t
r_typedef
id|u_long
id|Unique_t
suffix:semicolon
DECL|typedef|FileVersion
r_typedef
id|u_long
id|FileVersion
suffix:semicolon
macro_line|#endif 
macro_line|#ifndef&t;_VICEFID_T_
DECL|macro|_VICEFID_T_
mdefine_line|#define _VICEFID_T_&t;1
DECL|struct|ViceFid
r_typedef
r_struct
id|ViceFid
(brace
DECL|member|Volume
id|VolumeId
id|Volume
suffix:semicolon
DECL|member|Vnode
id|VnodeId
id|Vnode
suffix:semicolon
DECL|member|Unique
id|Unique_t
id|Unique
suffix:semicolon
DECL|typedef|ViceFid
)brace
id|ViceFid
suffix:semicolon
macro_line|#endif&t;/* VICEFID */
macro_line|#ifdef __linux__
DECL|function|coda_f2i
r_static
id|__inline__
id|ino_t
id|coda_f2i
c_func
(paren
r_struct
id|ViceFid
op_star
id|fid
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fid
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fid-&gt;Vnode
op_eq
l_int|0xfffffffe
op_logical_or
id|fid-&gt;Vnode
op_eq
l_int|0xffffffff
)paren
r_return
(paren
(paren
id|fid-&gt;Volume
op_lshift
l_int|20
)paren
op_or
(paren
id|fid-&gt;Unique
op_amp
l_int|0xfffff
)paren
)paren
suffix:semicolon
r_else
r_return
(paren
id|fid-&gt;Unique
op_plus
(paren
id|fid-&gt;Vnode
op_lshift
l_int|10
)paren
op_plus
(paren
id|fid-&gt;Volume
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|coda_f2i
mdefine_line|#define coda_f2i(fid)&bslash;&n;&t;((fid) ? ((fid)-&gt;Unique + ((fid)-&gt;Vnode&lt;&lt;10) + ((fid)-&gt;Volume&lt;&lt;20)) : 0)
macro_line|#endif
macro_line|#ifndef _VUID_T_
DECL|macro|_VUID_T_
mdefine_line|#define _VUID_T_
DECL|typedef|vuid_t
r_typedef
id|u_int32_t
id|vuid_t
suffix:semicolon
DECL|typedef|vgid_t
r_typedef
id|u_int32_t
id|vgid_t
suffix:semicolon
macro_line|#endif /*_VUID_T_ */
macro_line|#ifndef _CODACRED_T_
DECL|macro|_CODACRED_T_
mdefine_line|#define _CODACRED_T_
DECL|struct|coda_cred
r_struct
id|coda_cred
(brace
DECL|member|cr_uid
DECL|member|cr_euid
DECL|member|cr_suid
DECL|member|cr_fsuid
id|vuid_t
id|cr_uid
comma
id|cr_euid
comma
id|cr_suid
comma
id|cr_fsuid
suffix:semicolon
multiline_comment|/* Real, efftve, set, fs uid*/
DECL|member|cr_groupid
DECL|member|cr_egid
DECL|member|cr_sgid
DECL|member|cr_fsgid
id|vgid_t
id|cr_groupid
comma
id|cr_egid
comma
id|cr_sgid
comma
id|cr_fsgid
suffix:semicolon
multiline_comment|/* same for groups */
)brace
suffix:semicolon
macro_line|#endif 
macro_line|#ifndef _VENUS_VATTR_T_
DECL|macro|_VENUS_VATTR_T_
mdefine_line|#define _VENUS_VATTR_T_
multiline_comment|/*&n; * Vnode types.  VNON means no type.&n; */
DECL|enum|coda_vtype
DECL|enumerator|C_VNON
DECL|enumerator|C_VREG
DECL|enumerator|C_VDIR
DECL|enumerator|C_VBLK
DECL|enumerator|C_VCHR
DECL|enumerator|C_VLNK
DECL|enumerator|C_VSOCK
DECL|enumerator|C_VFIFO
DECL|enumerator|C_VBAD
r_enum
id|coda_vtype
(brace
id|C_VNON
comma
id|C_VREG
comma
id|C_VDIR
comma
id|C_VBLK
comma
id|C_VCHR
comma
id|C_VLNK
comma
id|C_VSOCK
comma
id|C_VFIFO
comma
id|C_VBAD
)brace
suffix:semicolon
DECL|struct|coda_vattr
r_struct
id|coda_vattr
(brace
DECL|member|va_type
r_int
id|va_type
suffix:semicolon
multiline_comment|/* vnode type (for create) */
DECL|member|va_mode
id|u_short
id|va_mode
suffix:semicolon
multiline_comment|/* files access mode and type */
DECL|member|va_nlink
r_int
id|va_nlink
suffix:semicolon
multiline_comment|/* number of references to file */
DECL|member|va_uid
id|vuid_t
id|va_uid
suffix:semicolon
multiline_comment|/* owner user id */
DECL|member|va_gid
id|vgid_t
id|va_gid
suffix:semicolon
multiline_comment|/* owner group id */
DECL|member|va_fileid
r_int
id|va_fileid
suffix:semicolon
multiline_comment|/* file id */
DECL|member|va_size
id|u_quad_t
id|va_size
suffix:semicolon
multiline_comment|/* file size in bytes */
DECL|member|va_blocksize
r_int
id|va_blocksize
suffix:semicolon
multiline_comment|/* blocksize preferred for i/o */
DECL|member|va_atime
r_struct
id|timespec
id|va_atime
suffix:semicolon
multiline_comment|/* time of last access */
DECL|member|va_mtime
r_struct
id|timespec
id|va_mtime
suffix:semicolon
multiline_comment|/* time of last modification */
DECL|member|va_ctime
r_struct
id|timespec
id|va_ctime
suffix:semicolon
multiline_comment|/* time file changed */
DECL|member|va_gen
id|u_long
id|va_gen
suffix:semicolon
multiline_comment|/* generation number of file */
DECL|member|va_flags
id|u_long
id|va_flags
suffix:semicolon
multiline_comment|/* flags defined for file */
DECL|member|va_rdev
id|cdev_t
id|va_rdev
suffix:semicolon
multiline_comment|/* device special file represents */
DECL|member|va_bytes
id|u_quad_t
id|va_bytes
suffix:semicolon
multiline_comment|/* bytes of disk space held by file */
DECL|member|va_filerev
id|u_quad_t
id|va_filerev
suffix:semicolon
multiline_comment|/* file modification number */
)brace
suffix:semicolon
macro_line|#endif 
multiline_comment|/* structure used by CODA_STATFS for getting cache information from venus */
DECL|struct|coda_statfs
r_struct
id|coda_statfs
(brace
DECL|member|f_blocks
r_int32
id|f_blocks
suffix:semicolon
DECL|member|f_bfree
r_int32
id|f_bfree
suffix:semicolon
DECL|member|f_bavail
r_int32
id|f_bavail
suffix:semicolon
DECL|member|f_files
r_int32
id|f_files
suffix:semicolon
DECL|member|f_ffree
r_int32
id|f_ffree
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Kernel &lt;--&gt; Venus communications.&n; */
DECL|macro|CODA_ROOT
mdefine_line|#define CODA_ROOT&t;2
DECL|macro|CODA_OPEN_BY_FD
mdefine_line|#define CODA_OPEN_BY_FD&t;3
DECL|macro|CODA_OPEN
mdefine_line|#define CODA_OPEN&t;4
DECL|macro|CODA_CLOSE
mdefine_line|#define CODA_CLOSE&t;5
DECL|macro|CODA_IOCTL
mdefine_line|#define CODA_IOCTL&t;6
DECL|macro|CODA_GETATTR
mdefine_line|#define CODA_GETATTR&t;7
DECL|macro|CODA_SETATTR
mdefine_line|#define CODA_SETATTR&t;8
DECL|macro|CODA_ACCESS
mdefine_line|#define CODA_ACCESS&t;9
DECL|macro|CODA_LOOKUP
mdefine_line|#define CODA_LOOKUP&t;10
DECL|macro|CODA_CREATE
mdefine_line|#define CODA_CREATE&t;11
DECL|macro|CODA_REMOVE
mdefine_line|#define CODA_REMOVE&t;12
DECL|macro|CODA_LINK
mdefine_line|#define CODA_LINK&t;13
DECL|macro|CODA_RENAME
mdefine_line|#define CODA_RENAME&t;14
DECL|macro|CODA_MKDIR
mdefine_line|#define CODA_MKDIR&t;15
DECL|macro|CODA_RMDIR
mdefine_line|#define CODA_RMDIR&t;16
DECL|macro|CODA_SYMLINK
mdefine_line|#define CODA_SYMLINK&t;18
DECL|macro|CODA_READLINK
mdefine_line|#define CODA_READLINK&t;19
DECL|macro|CODA_FSYNC
mdefine_line|#define CODA_FSYNC&t;20
DECL|macro|CODA_VGET
mdefine_line|#define CODA_VGET&t;22
DECL|macro|CODA_SIGNAL
mdefine_line|#define CODA_SIGNAL&t;23
DECL|macro|CODA_REPLACE
mdefine_line|#define CODA_REPLACE&t; 24 /* DOWNCALL */
DECL|macro|CODA_FLUSH
mdefine_line|#define CODA_FLUSH       25 /* DOWNCALL */
DECL|macro|CODA_PURGEUSER
mdefine_line|#define CODA_PURGEUSER   26 /* DOWNCALL */
DECL|macro|CODA_ZAPFILE
mdefine_line|#define CODA_ZAPFILE     27 /* DOWNCALL */
DECL|macro|CODA_ZAPDIR
mdefine_line|#define CODA_ZAPDIR      28 /* DOWNCALL */
DECL|macro|CODA_PURGEFID
mdefine_line|#define CODA_PURGEFID    30 /* DOWNCALL */
DECL|macro|CODA_OPEN_BY_PATH
mdefine_line|#define CODA_OPEN_BY_PATH 31
DECL|macro|CODA_RESOLVE
mdefine_line|#define CODA_RESOLVE     32
DECL|macro|CODA_REINTEGRATE
mdefine_line|#define CODA_REINTEGRATE 33
DECL|macro|CODA_STATFS
mdefine_line|#define CODA_STATFS&t; 34
DECL|macro|CODA_STORE
mdefine_line|#define CODA_STORE&t; 35
DECL|macro|CODA_RELEASE
mdefine_line|#define CODA_RELEASE&t; 36
DECL|macro|CODA_NCALLS
mdefine_line|#define CODA_NCALLS 37
DECL|macro|DOWNCALL
mdefine_line|#define DOWNCALL(opcode) (opcode &gt;= CODA_REPLACE &amp;&amp; opcode &lt;= CODA_PURGEFID)
DECL|macro|VC_MAXDATASIZE
mdefine_line|#define VC_MAXDATASIZE&t;    8192
DECL|macro|VC_MAXMSGSIZE
mdefine_line|#define VC_MAXMSGSIZE      sizeof(union inputArgs)+sizeof(union outputArgs) +&bslash;&n;                            VC_MAXDATASIZE  
DECL|macro|CIOC_KERNEL_VERSION
mdefine_line|#define CIOC_KERNEL_VERSION _IOWR(&squot;c&squot;, 10, sizeof (int))
macro_line|#if 0
mdefine_line|#define CODA_KERNEL_VERSION 0 /* don&squot;t care about kernel version number */
mdefine_line|#define CODA_KERNEL_VERSION 1 /* The old venus 4.6 compatible interface */
macro_line|#endif
DECL|macro|CODA_KERNEL_VERSION
mdefine_line|#define CODA_KERNEL_VERSION 2 /* venus_lookup gets an extra parameter */
multiline_comment|/*&n; *        Venus &lt;-&gt; Coda  RPC arguments&n; */
DECL|struct|coda_in_hdr
r_struct
id|coda_in_hdr
(brace
DECL|member|opcode
r_int
r_int
id|opcode
suffix:semicolon
DECL|member|unique
r_int
r_int
id|unique
suffix:semicolon
multiline_comment|/* Keep multiple outstanding msgs distinct */
DECL|member|pid
id|u_short
id|pid
suffix:semicolon
multiline_comment|/* Common to all */
DECL|member|pgid
id|u_short
id|pgid
suffix:semicolon
multiline_comment|/* Common to all */
DECL|member|sid
id|u_short
id|sid
suffix:semicolon
multiline_comment|/* Common to all */
DECL|member|cred
r_struct
id|coda_cred
id|cred
suffix:semicolon
multiline_comment|/* Common to all */
)brace
suffix:semicolon
multiline_comment|/* Really important that opcode and unique are 1st two fields! */
DECL|struct|coda_out_hdr
r_struct
id|coda_out_hdr
(brace
DECL|member|opcode
r_int
r_int
id|opcode
suffix:semicolon
DECL|member|unique
r_int
r_int
id|unique
suffix:semicolon
DECL|member|result
r_int
r_int
id|result
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_root: NO_IN */
DECL|struct|coda_root_out
r_struct
id|coda_root_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_root_in
r_struct
id|coda_root_in
(brace
DECL|member|in
r_struct
id|coda_in_hdr
id|in
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_open: */
DECL|struct|coda_open_in
r_struct
id|coda_open_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_open_out
r_struct
id|coda_open_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|dev
id|cdev_t
id|dev
suffix:semicolon
DECL|member|inode
id|ino_t
id|inode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_store: */
DECL|struct|coda_store_in
r_struct
id|coda_store_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_store_out
r_struct
id|coda_store_out
(brace
DECL|member|out
r_struct
id|coda_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_release: */
DECL|struct|coda_release_in
r_struct
id|coda_release_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_release_out
r_struct
id|coda_release_out
(brace
DECL|member|out
r_struct
id|coda_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_close: */
DECL|struct|coda_close_in
r_struct
id|coda_close_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_close_out
r_struct
id|coda_close_out
(brace
DECL|member|out
r_struct
id|coda_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_ioctl: */
DECL|struct|coda_ioctl_in
r_struct
id|coda_ioctl_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|rwflag
r_int
id|rwflag
suffix:semicolon
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|coda_ioctl_out
r_struct
id|coda_ioctl_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|data
id|caddr_t
id|data
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
multiline_comment|/* coda_getattr: */
DECL|struct|coda_getattr_in
r_struct
id|coda_getattr_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_getattr_out
r_struct
id|coda_getattr_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_setattr: NO_OUT */
DECL|struct|coda_setattr_in
r_struct
id|coda_setattr_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_setattr_out
r_struct
id|coda_setattr_out
(brace
DECL|member|out
r_struct
id|coda_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_access: NO_OUT */
DECL|struct|coda_access_in
r_struct
id|coda_access_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_access_out
r_struct
id|coda_access_out
(brace
DECL|member|out
r_struct
id|coda_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* lookup flags */
DECL|macro|CLU_CASE_SENSITIVE
mdefine_line|#define CLU_CASE_SENSITIVE     0x01
DECL|macro|CLU_CASE_INSENSITIVE
mdefine_line|#define CLU_CASE_INSENSITIVE   0x02
multiline_comment|/* coda_lookup: */
DECL|struct|coda_lookup_in
r_struct
id|coda_lookup_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|name
r_int
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_lookup_out
r_struct
id|coda_lookup_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|vtype
r_int
id|vtype
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_create: */
DECL|struct|coda_create_in
r_struct
id|coda_create_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|excl
r_int
id|excl
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|name
r_int
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|coda_create_out
r_struct
id|coda_create_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_remove: NO_OUT */
DECL|struct|coda_remove_in
r_struct
id|coda_remove_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|name
r_int
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|coda_remove_out
r_struct
id|coda_remove_out
(brace
DECL|member|out
r_struct
id|coda_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_link: NO_OUT */
DECL|struct|coda_link_in
r_struct
id|coda_link_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|sourceFid
id|ViceFid
id|sourceFid
suffix:semicolon
multiline_comment|/* cnode to link *to* */
DECL|member|destFid
id|ViceFid
id|destFid
suffix:semicolon
multiline_comment|/* Directory in which to place link */
DECL|member|tname
r_int
id|tname
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|coda_link_out
r_struct
id|coda_link_out
(brace
DECL|member|out
r_struct
id|coda_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_rename: NO_OUT */
DECL|struct|coda_rename_in
r_struct
id|coda_rename_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|sourceFid
id|ViceFid
id|sourceFid
suffix:semicolon
DECL|member|srcname
r_int
id|srcname
suffix:semicolon
DECL|member|destFid
id|ViceFid
id|destFid
suffix:semicolon
DECL|member|destname
r_int
id|destname
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_rename_out
r_struct
id|coda_rename_out
(brace
DECL|member|out
r_struct
id|coda_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_mkdir: */
DECL|struct|coda_mkdir_in
r_struct
id|coda_mkdir_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|name
r_int
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|coda_mkdir_out
r_struct
id|coda_mkdir_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_rmdir: NO_OUT */
DECL|struct|coda_rmdir_in
r_struct
id|coda_rmdir_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|name
r_int
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|coda_rmdir_out
r_struct
id|coda_rmdir_out
(brace
DECL|member|out
r_struct
id|coda_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_symlink: NO_OUT */
DECL|struct|coda_symlink_in
r_struct
id|coda_symlink_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
multiline_comment|/* Directory to put symlink in */
DECL|member|srcname
r_int
id|srcname
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|tname
r_int
id|tname
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_symlink_out
r_struct
id|coda_symlink_out
(brace
DECL|member|out
r_struct
id|coda_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_readlink: */
DECL|struct|coda_readlink_in
r_struct
id|coda_readlink_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_readlink_out
r_struct
id|coda_readlink_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|data
id|caddr_t
id|data
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
multiline_comment|/* coda_fsync: NO_OUT */
DECL|struct|coda_fsync_in
r_struct
id|coda_fsync_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_fsync_out
r_struct
id|coda_fsync_out
(brace
DECL|member|out
r_struct
id|coda_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_vget: */
DECL|struct|coda_vget_in
r_struct
id|coda_vget_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_vget_out
r_struct
id|coda_vget_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|vtype
r_int
id|vtype
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* CODA_SIGNAL is out-of-band, doesn&squot;t need data. */
multiline_comment|/* CODA_INVALIDATE is a venus-&gt;kernel call */
multiline_comment|/* CODA_FLUSH is a venus-&gt;kernel call */
multiline_comment|/* coda_purgeuser: */
multiline_comment|/* CODA_PURGEUSER is a venus-&gt;kernel call */
DECL|struct|coda_purgeuser_out
r_struct
id|coda_purgeuser_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|cred
r_struct
id|coda_cred
id|cred
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_zapfile: */
multiline_comment|/* CODA_ZAPFILE is a venus-&gt;kernel call */
DECL|struct|coda_zapfile_out
r_struct
id|coda_zapfile_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|CodaFid
id|ViceFid
id|CodaFid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_zapdir: */
multiline_comment|/* CODA_ZAPDIR is a venus-&gt;kernel call */
DECL|struct|coda_zapdir_out
r_struct
id|coda_zapdir_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|CodaFid
id|ViceFid
id|CodaFid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_zapnode: */
multiline_comment|/* CODA_ZAPVNODE is a venus-&gt;kernel call */
DECL|struct|coda_zapvnode_out
r_struct
id|coda_zapvnode_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|cred
r_struct
id|coda_cred
id|cred
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_purgefid: */
multiline_comment|/* CODA_PURGEFID is a venus-&gt;kernel call */
DECL|struct|coda_purgefid_out
r_struct
id|coda_purgefid_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|CodaFid
id|ViceFid
id|CodaFid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_replace: */
multiline_comment|/* CODA_REPLACE is a venus-&gt;kernel call */
DECL|struct|coda_replace_out
r_struct
id|coda_replace_out
(brace
multiline_comment|/* coda_replace is a venus-&gt;kernel call */
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|NewFid
id|ViceFid
id|NewFid
suffix:semicolon
DECL|member|OldFid
id|ViceFid
id|OldFid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_open_by_fd: */
DECL|struct|coda_open_by_fd_in
r_struct
id|coda_open_by_fd_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_open_by_fd_out
r_struct
id|coda_open_by_fd_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|member|fh
r_struct
id|file
op_star
id|fh
suffix:semicolon
multiline_comment|/* not passed from userspace but used in-kernel only */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* coda_open_by_path: */
DECL|struct|coda_open_by_path_in
r_struct
id|coda_open_by_path_in
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_open_by_path_out
r_struct
id|coda_open_by_path_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|path
r_int
id|path
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* coda_statfs: NO_IN */
DECL|struct|coda_statfs_in
r_struct
id|coda_statfs_in
(brace
DECL|member|in
r_struct
id|coda_in_hdr
id|in
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|coda_statfs_out
r_struct
id|coda_statfs_out
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
DECL|member|stat
r_struct
id|coda_statfs
id|stat
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Occasionally, we don&squot;t cache the fid returned by CODA_LOOKUP. &n; * For instance, if the fid is inconsistent. &n; * This case is handled by setting the top bit of the type result parameter.&n; */
DECL|macro|CODA_NOCACHE
mdefine_line|#define CODA_NOCACHE          0x80000000
DECL|union|inputArgs
r_union
id|inputArgs
(brace
DECL|member|ih
r_struct
id|coda_in_hdr
id|ih
suffix:semicolon
multiline_comment|/* NB: every struct below begins with an ih */
DECL|member|coda_open
r_struct
id|coda_open_in
id|coda_open
suffix:semicolon
DECL|member|coda_store
r_struct
id|coda_store_in
id|coda_store
suffix:semicolon
DECL|member|coda_release
r_struct
id|coda_release_in
id|coda_release
suffix:semicolon
DECL|member|coda_close
r_struct
id|coda_close_in
id|coda_close
suffix:semicolon
DECL|member|coda_ioctl
r_struct
id|coda_ioctl_in
id|coda_ioctl
suffix:semicolon
DECL|member|coda_getattr
r_struct
id|coda_getattr_in
id|coda_getattr
suffix:semicolon
DECL|member|coda_setattr
r_struct
id|coda_setattr_in
id|coda_setattr
suffix:semicolon
DECL|member|coda_access
r_struct
id|coda_access_in
id|coda_access
suffix:semicolon
DECL|member|coda_lookup
r_struct
id|coda_lookup_in
id|coda_lookup
suffix:semicolon
DECL|member|coda_create
r_struct
id|coda_create_in
id|coda_create
suffix:semicolon
DECL|member|coda_remove
r_struct
id|coda_remove_in
id|coda_remove
suffix:semicolon
DECL|member|coda_link
r_struct
id|coda_link_in
id|coda_link
suffix:semicolon
DECL|member|coda_rename
r_struct
id|coda_rename_in
id|coda_rename
suffix:semicolon
DECL|member|coda_mkdir
r_struct
id|coda_mkdir_in
id|coda_mkdir
suffix:semicolon
DECL|member|coda_rmdir
r_struct
id|coda_rmdir_in
id|coda_rmdir
suffix:semicolon
DECL|member|coda_symlink
r_struct
id|coda_symlink_in
id|coda_symlink
suffix:semicolon
DECL|member|coda_readlink
r_struct
id|coda_readlink_in
id|coda_readlink
suffix:semicolon
DECL|member|coda_fsync
r_struct
id|coda_fsync_in
id|coda_fsync
suffix:semicolon
DECL|member|coda_vget
r_struct
id|coda_vget_in
id|coda_vget
suffix:semicolon
DECL|member|coda_open_by_fd
r_struct
id|coda_open_by_fd_in
id|coda_open_by_fd
suffix:semicolon
DECL|member|coda_open_by_path
r_struct
id|coda_open_by_path_in
id|coda_open_by_path
suffix:semicolon
DECL|member|coda_statfs
r_struct
id|coda_statfs_in
id|coda_statfs
suffix:semicolon
)brace
suffix:semicolon
DECL|union|outputArgs
r_union
id|outputArgs
(brace
DECL|member|oh
r_struct
id|coda_out_hdr
id|oh
suffix:semicolon
multiline_comment|/* NB: every struct below begins with an oh */
DECL|member|coda_root
r_struct
id|coda_root_out
id|coda_root
suffix:semicolon
DECL|member|coda_open
r_struct
id|coda_open_out
id|coda_open
suffix:semicolon
DECL|member|coda_ioctl
r_struct
id|coda_ioctl_out
id|coda_ioctl
suffix:semicolon
DECL|member|coda_getattr
r_struct
id|coda_getattr_out
id|coda_getattr
suffix:semicolon
DECL|member|coda_lookup
r_struct
id|coda_lookup_out
id|coda_lookup
suffix:semicolon
DECL|member|coda_create
r_struct
id|coda_create_out
id|coda_create
suffix:semicolon
DECL|member|coda_mkdir
r_struct
id|coda_mkdir_out
id|coda_mkdir
suffix:semicolon
DECL|member|coda_readlink
r_struct
id|coda_readlink_out
id|coda_readlink
suffix:semicolon
DECL|member|coda_vget
r_struct
id|coda_vget_out
id|coda_vget
suffix:semicolon
DECL|member|coda_purgeuser
r_struct
id|coda_purgeuser_out
id|coda_purgeuser
suffix:semicolon
DECL|member|coda_zapfile
r_struct
id|coda_zapfile_out
id|coda_zapfile
suffix:semicolon
DECL|member|coda_zapdir
r_struct
id|coda_zapdir_out
id|coda_zapdir
suffix:semicolon
DECL|member|coda_zapvnode
r_struct
id|coda_zapvnode_out
id|coda_zapvnode
suffix:semicolon
DECL|member|coda_purgefid
r_struct
id|coda_purgefid_out
id|coda_purgefid
suffix:semicolon
DECL|member|coda_replace
r_struct
id|coda_replace_out
id|coda_replace
suffix:semicolon
DECL|member|coda_open_by_fd
r_struct
id|coda_open_by_fd_out
id|coda_open_by_fd
suffix:semicolon
DECL|member|coda_open_by_path
r_struct
id|coda_open_by_path_out
id|coda_open_by_path
suffix:semicolon
DECL|member|coda_statfs
r_struct
id|coda_statfs_out
id|coda_statfs
suffix:semicolon
)brace
suffix:semicolon
DECL|union|coda_downcalls
r_union
id|coda_downcalls
(brace
multiline_comment|/* CODA_INVALIDATE is a venus-&gt;kernel call */
multiline_comment|/* CODA_FLUSH is a venus-&gt;kernel call */
DECL|member|purgeuser
r_struct
id|coda_purgeuser_out
id|purgeuser
suffix:semicolon
DECL|member|zapfile
r_struct
id|coda_zapfile_out
id|zapfile
suffix:semicolon
DECL|member|zapdir
r_struct
id|coda_zapdir_out
id|zapdir
suffix:semicolon
DECL|member|zapvnode
r_struct
id|coda_zapvnode_out
id|zapvnode
suffix:semicolon
DECL|member|purgefid
r_struct
id|coda_purgefid_out
id|purgefid
suffix:semicolon
DECL|member|replace
r_struct
id|coda_replace_out
id|replace
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Used for identifying usage of &quot;Control&quot; and pioctls&n; */
DECL|macro|PIOCPARM_MASK
mdefine_line|#define PIOCPARM_MASK 0x0000ffff
DECL|struct|ViceIoctl
r_struct
id|ViceIoctl
(brace
DECL|member|in
DECL|member|out
id|caddr_t
id|in
comma
id|out
suffix:semicolon
multiline_comment|/* Data to be transferred in, or out */
DECL|member|in_size
r_int
id|in_size
suffix:semicolon
multiline_comment|/* Size of input buffer &lt;= 2K */
DECL|member|out_size
r_int
id|out_size
suffix:semicolon
multiline_comment|/* Maximum size of output buffer, &lt;= 2K */
)brace
suffix:semicolon
DECL|struct|PioctlData
r_struct
id|PioctlData
(brace
DECL|member|path
r_const
r_char
op_star
id|path
suffix:semicolon
DECL|member|follow
r_int
id|follow
suffix:semicolon
DECL|member|vi
r_struct
id|ViceIoctl
id|vi
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CODA_CONTROL
mdefine_line|#define&t;CODA_CONTROL&t;&t;&quot;.CONTROL&quot;
DECL|macro|CODA_CONTROLLEN
mdefine_line|#define CODA_CONTROLLEN           8
DECL|macro|CTL_VOL
mdefine_line|#define&t;CTL_VOL&t;&t;&t;-1
DECL|macro|CTL_VNO
mdefine_line|#define&t;CTL_VNO&t;&t;&t;-1
DECL|macro|CTL_UNI
mdefine_line|#define&t;CTL_UNI&t;&t;&t;-1
DECL|macro|CTL_INO
mdefine_line|#define CTL_INO                 -1
DECL|macro|CTL_FILE
mdefine_line|#define&t;CTL_FILE&t;&t;&quot;/coda/.CONTROL&quot;
DECL|macro|IS_CTL_FID
mdefine_line|#define&t;IS_CTL_FID(fidp)&t;((fidp)-&gt;Volume == CTL_VOL &amp;&amp;&bslash;&n;&t;&t;&t;&t; (fidp)-&gt;Vnode == CTL_VNO &amp;&amp;&bslash;&n;&t;&t;&t;&t; (fidp)-&gt;Unique == CTL_UNI)
multiline_comment|/* Data passed to mount */
DECL|macro|CODA_MOUNT_VERSION
mdefine_line|#define CODA_MOUNT_VERSION 1
DECL|struct|coda_mount_data
r_struct
id|coda_mount_data
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
multiline_comment|/* Opened device */
)brace
suffix:semicolon
macro_line|#endif 
eof
