multiline_comment|/*  ntfstypes.h - This file defines four things:&n; *   - Generic platform independent fixed-size types (e.g. ntfs_u32).&n; *   - Specific fixed-size types (e.g. ntfs_offset_t).&n; *   - Macros that read and write those types from and to byte arrays.&n; *   - Types derived from OS specific ones.&n; *&n; *  Copyright (C) 1996, 1998, 1999 Martin von L&#xfffd;wis&n; *  Copyright (C) 2001 Anton Altaparmakov (AIA)&n; */
macro_line|#include &lt;linux/fs.h&gt;
multiline_comment|/* We don&squot;t need to define __LITTLE_ENDIAN, as we use&n;   &lt;asm/byteorder&gt;. */
macro_line|#include &quot;ntfsendian.h&quot;
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* Integral types */
macro_line|#ifndef NTFS_INTEGRAL_TYPES
DECL|macro|NTFS_INTEGRAL_TYPES
mdefine_line|#define NTFS_INTEGRAL_TYPES
DECL|typedef|ntfs_u8
r_typedef
id|u8
id|ntfs_u8
suffix:semicolon
DECL|typedef|ntfs_u16
r_typedef
id|u16
id|ntfs_u16
suffix:semicolon
DECL|typedef|ntfs_u32
r_typedef
id|u32
id|ntfs_u32
suffix:semicolon
DECL|typedef|ntfs_u64
r_typedef
id|u64
id|ntfs_u64
suffix:semicolon
DECL|typedef|ntfs_s8
r_typedef
id|s8
id|ntfs_s8
suffix:semicolon
DECL|typedef|ntfs_s16
r_typedef
id|s16
id|ntfs_s16
suffix:semicolon
DECL|typedef|ntfs_s32
r_typedef
id|s32
id|ntfs_s32
suffix:semicolon
DECL|typedef|ntfs_s64
r_typedef
id|s64
id|ntfs_s64
suffix:semicolon
macro_line|#endif
multiline_comment|/* Unicode character type */
macro_line|#ifndef NTFS_WCHAR_T
DECL|macro|NTFS_WCHAR_T
mdefine_line|#define NTFS_WCHAR_T
DECL|typedef|ntfs_wchar_t
r_typedef
id|u16
id|ntfs_wchar_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* File offset */
macro_line|#ifndef NTFS_OFFSET_T
DECL|macro|NTFS_OFFSET_T
mdefine_line|#define NTFS_OFFSET_T
DECL|typedef|ntfs_offset_t
r_typedef
id|u64
id|ntfs_offset_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* UTC */
macro_line|#ifndef NTFS_TIME64_T
DECL|macro|NTFS_TIME64_T
mdefine_line|#define NTFS_TIME64_T
DECL|typedef|ntfs_time64_t
r_typedef
id|u64
id|ntfs_time64_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* This is really unsigned long long. So we support only volumes up to 2Tb. */
macro_line|#ifndef NTFS_CLUSTER_T
DECL|macro|NTFS_CLUSTER_T
mdefine_line|#define NTFS_CLUSTER_T
DECL|typedef|ntfs_cluster_t
r_typedef
id|u32
id|ntfs_cluster_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef MAX_CLUSTER_T
DECL|macro|MAX_CLUSTER_T
mdefine_line|#define MAX_CLUSTER_T (~((ntfs_cluster_t)0))
macro_line|#endif
multiline_comment|/* Architecture independent macros. */
multiline_comment|/* PUTU32 would not clear all bytes. */
DECL|macro|NTFS_PUTINUM
mdefine_line|#define NTFS_PUTINUM(p,i)    NTFS_PUTU64(p, i-&gt;i_number); &bslash;&n;                             NTFS_PUTU16(((char*)p) + 6, i-&gt;sequence_number)
multiline_comment|/* System dependent types. */
macro_line|#include &lt;asm/posix_types.h&gt;
macro_line|#ifndef NTMODE_T
DECL|macro|NTMODE_T
mdefine_line|#define NTMODE_T
DECL|typedef|ntmode_t
r_typedef
id|__kernel_mode_t
id|ntmode_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_UID_T
DECL|macro|NTFS_UID_T
mdefine_line|#define NTFS_UID_T
DECL|typedef|ntfs_uid_t
r_typedef
id|uid_t
id|ntfs_uid_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_GID_T
DECL|macro|NTFS_GID_T
mdefine_line|#define NTFS_GID_T
DECL|typedef|ntfs_gid_t
r_typedef
id|gid_t
id|ntfs_gid_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_SIZE_T
DECL|macro|NTFS_SIZE_T
mdefine_line|#define NTFS_SIZE_T
DECL|typedef|ntfs_size_t
r_typedef
id|__kernel_size_t
id|ntfs_size_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_TIME_T
DECL|macro|NTFS_TIME_T
mdefine_line|#define NTFS_TIME_T
DECL|typedef|ntfs_time_t
r_typedef
id|__kernel_time_t
id|ntfs_time_t
suffix:semicolon
macro_line|#endif
eof
