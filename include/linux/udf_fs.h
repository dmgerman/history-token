multiline_comment|/*&n; * udf_fs.h&n; *&n; * PURPOSE&n; *  Included by fs/filesystems.c&n; *&n; * DESCRIPTION&n; *  OSTA-UDF(tm) = Optical Storage Technology Association&n; *  Universal Disk Format.&n; *&n; *  This code is based on version 2.00 of the UDF specification,&n; *  and revision 3 of the ECMA 167 standard [equivalent to ISO 13346].&n; *    http://www.osta.org/ *    http://www.ecma.ch/&n; *    http://www.iso.org/&n; *&n; * CONTACTS&n; *&t;E-mail regarding any portion of the Linux UDF file system should be&n; *&t;directed to the development team mailing list (run by majordomo):&n; *&t;&t;linux_udf@hootie.lvld.hp.com&n; *&n; * COPYRIGHT&n; *&t;This file is distributed under the terms of the GNU General Public&n; *&t;License (GPL). Copies of the GPL can be obtained from:&n; *&t;&t;ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *&t;Each contributing author retains all rights to their own work.&n; *&n; *  (C) 1999-2000 Ben Fennema&n; *  (C) 1999-2000 Stelias Computing Inc&n; *&n; * HISTORY&n; *&n; */
macro_line|#if !defined(_LINUX_UDF_FS_H)
DECL|macro|_LINUX_UDF_FS_H
mdefine_line|#define _LINUX_UDF_FS_H
DECL|macro|UDF_PREALLOCATE
mdefine_line|#define UDF_PREALLOCATE
DECL|macro|UDF_DEFAULT_PREALLOC_BLOCKS
mdefine_line|#define UDF_DEFAULT_PREALLOC_BLOCKS&t;&t;8
DECL|macro|UDFFS_DATE
mdefine_line|#define UDFFS_DATE&t;&t;&quot;2000/02/29&quot;
DECL|macro|UDFFS_VERSION
mdefine_line|#define UDFFS_VERSION&t;&quot;0.9.1&quot;
DECL|macro|UDFFS_DEBUG
mdefine_line|#define UDFFS_DEBUG
macro_line|#ifdef UDFFS_DEBUG
DECL|macro|udf_debug
mdefine_line|#define udf_debug(f, a...) &bslash;&n;&t;{ &bslash;&n;&t;&t;printk (KERN_DEBUG &quot;UDF-fs DEBUG %s:%d:%s: &quot;, &bslash;&n;&t;&t;&t;__FILE__, __LINE__, __FUNCTION__); &bslash;&n;&t;&t;printk (f, ##a); &bslash;&n;&t;}
macro_line|#else
DECL|macro|udf_debug
mdefine_line|#define udf_debug(f, a...) /**/
macro_line|#endif
DECL|macro|udf_info
mdefine_line|#define udf_info(f, a...) &bslash;&n;&t;&t;printk (KERN_INFO &quot;UDF-fs INFO &quot; f, ##a);
macro_line|#endif /* !defined(_LINUX_UDF_FS_H) */
eof
