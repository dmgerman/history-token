multiline_comment|/*&n; * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_CLNT_H__
DECL|macro|__XFS_CLNT_H__
mdefine_line|#define __XFS_CLNT_H__
multiline_comment|/*&n; * XFS arguments structure, constructed from the arguments we&n; * are passed via the mount system call.&n; *&n; * NOTE: The mount system call is handled differently between&n; * Linux and IRIX.  In IRIX we worked work with a binary data&n; * structure coming in across the syscall interface from user&n; * space (the mount userspace knows about each filesystem type&n; * and the set of valid options for it, and converts the users&n; * argument string into a binary structure _before_ making the&n; * system call), and the ABI issues that this implies.&n; *&n; * In Linux, we are passed a comma separated set of options;&n; * ie. a NULL terminated string of characters.  Userspace mount&n; * code does not have any knowledge of mount options expected by&n; * each filesystem type and so each filesystem parses its mount&n; * options in kernel space.&n; *&n; * For the Linux port, we kept this structure pretty much intact&n; * and use it internally (because the existing code groks it).&n; */
DECL|struct|xfs_mount_args
r_struct
id|xfs_mount_args
(brace
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* flags -&gt; see XFSMNT_... macros below */
DECL|member|logbufs
r_int
id|logbufs
suffix:semicolon
multiline_comment|/* Number of log buffers, -1 to default */
DECL|member|logbufsize
r_int
id|logbufsize
suffix:semicolon
multiline_comment|/* Size of log buffers, -1 to default */
DECL|member|fsname
r_char
id|fsname
(braket
id|MAXNAMELEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* data device name */
DECL|member|rtname
r_char
id|rtname
(braket
id|MAXNAMELEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* realtime device filename */
DECL|member|logname
r_char
id|logname
(braket
id|MAXNAMELEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* journal device filename */
DECL|member|mtpt
r_char
id|mtpt
(braket
id|MAXNAMELEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* filesystem mount point */
DECL|member|sunit
r_int
id|sunit
suffix:semicolon
multiline_comment|/* stripe unit (BBs) */
DECL|member|swidth
r_int
id|swidth
suffix:semicolon
multiline_comment|/* stripe width (BBs), multiple of sunit */
DECL|member|iosizelog
id|uchar_t
id|iosizelog
suffix:semicolon
multiline_comment|/* log2 of the preferred I/O size */
DECL|member|ihashsize
r_int
id|ihashsize
suffix:semicolon
multiline_comment|/* inode hash table size (buckets) */
)brace
suffix:semicolon
multiline_comment|/*&n; * XFS mount option flags&n; */
DECL|macro|XFSMNT_CHKLOG
mdefine_line|#define&t;XFSMNT_CHKLOG&t;&t;0x00000001&t;/* check log */
DECL|macro|XFSMNT_WSYNC
mdefine_line|#define&t;XFSMNT_WSYNC&t;&t;0x00000002&t;/* safe mode nfs mount&n;&t;&t;&t;&t;&t;&t; * compatible */
DECL|macro|XFSMNT_INO64
mdefine_line|#define&t;XFSMNT_INO64&t;&t;0x00000004&t;/* move inode numbers up&n;&t;&t;&t;&t;&t;&t; * past 2^32 */
DECL|macro|XFSMNT_UQUOTA
mdefine_line|#define XFSMNT_UQUOTA&t;&t;0x00000008&t;/* user quota accounting */
DECL|macro|XFSMNT_PQUOTA
mdefine_line|#define XFSMNT_PQUOTA&t;&t;0x00000010&t;/* IRIX prj quota accounting */
DECL|macro|XFSMNT_UQUOTAENF
mdefine_line|#define XFSMNT_UQUOTAENF&t;0x00000020&t;/* user quota limit&n;&t;&t;&t;&t;&t;&t; * enforcement */
DECL|macro|XFSMNT_PQUOTAENF
mdefine_line|#define XFSMNT_PQUOTAENF&t;0x00000040&t;/* IRIX project quota limit&n;&t;&t;&t;&t;&t;&t; * enforcement */
DECL|macro|XFSMNT_NOATIME
mdefine_line|#define XFSMNT_NOATIME&t;&t;0x00000100&t;/* don&squot;t modify access&n;&t;&t;&t;&t;&t;&t; * times on reads */
DECL|macro|XFSMNT_NOALIGN
mdefine_line|#define XFSMNT_NOALIGN&t;&t;0x00000200&t;/* don&squot;t allocate at&n;&t;&t;&t;&t;&t;&t; * stripe boundaries*/
DECL|macro|XFSMNT_RETERR
mdefine_line|#define XFSMNT_RETERR&t;&t;0x00000400&t;/* return error to user */
DECL|macro|XFSMNT_NORECOVERY
mdefine_line|#define XFSMNT_NORECOVERY&t;0x00000800&t;/* no recovery, implies&n;&t;&t;&t;&t;&t;&t; * read-only mount */
DECL|macro|XFSMNT_SHARED
mdefine_line|#define XFSMNT_SHARED&t;&t;0x00001000&t;/* shared XFS mount */
DECL|macro|XFSMNT_IOSIZE
mdefine_line|#define XFSMNT_IOSIZE&t;&t;0x00002000&t;/* optimize for I/O size */
DECL|macro|XFSMNT_OSYNCISOSYNC
mdefine_line|#define XFSMNT_OSYNCISOSYNC&t;0x00004000&t;/* o_sync is REALLY o_sync */
multiline_comment|/* (osyncisdsync is now default) */
DECL|macro|XFSMNT_32BITINODES
mdefine_line|#define XFSMNT_32BITINODES&t;0x00200000&t;/* restrict inodes to 32&n;&t;&t;&t;&t;&t;&t; * bits of address space */
DECL|macro|XFSMNT_GQUOTA
mdefine_line|#define XFSMNT_GQUOTA&t;&t;0x00400000&t;/* group quota accounting */
DECL|macro|XFSMNT_GQUOTAENF
mdefine_line|#define XFSMNT_GQUOTAENF&t;0x00800000&t;/* group quota limit&n;&t;&t;&t;&t;&t;&t; * enforcement */
DECL|macro|XFSMNT_NOUUID
mdefine_line|#define XFSMNT_NOUUID&t;&t;0x01000000&t;/* Ignore fs uuid */
DECL|macro|XFSMNT_DMAPI
mdefine_line|#define XFSMNT_DMAPI&t;&t;0x02000000&t;/* enable dmapi/xdsm */
DECL|macro|XFSMNT_NOLOGFLUSH
mdefine_line|#define XFSMNT_NOLOGFLUSH&t;0x04000000&t;/* Don&squot;t flush for log blocks */
DECL|macro|XFSMNT_IDELETE
mdefine_line|#define XFSMNT_IDELETE&t;&t;0x08000000&t;/* inode cluster delete */
DECL|macro|XFSMNT_SWALLOC
mdefine_line|#define XFSMNT_SWALLOC&t;&t;0x10000000&t;/* turn on stripe width&n;&t;&t;&t;&t;&t;&t; * allocation */
macro_line|#endif&t;/* __XFS_CLNT_H__ */
eof
