multiline_comment|/*&n; * types.h - Defines for NTFS Linux kernel driver specific types.&n; *&t;     Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001,2002 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_TYPES_H
DECL|macro|_LINUX_NTFS_TYPES_H
mdefine_line|#define _LINUX_NTFS_TYPES_H
macro_line|#if __GNUC__ &lt; 2 || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 96)
DECL|macro|SN
mdefine_line|#define SN(X)   X&t;/* Struct Name */
DECL|macro|SC
mdefine_line|#define SC(P,N) P.N&t;/* ShortCut: Prefix, Name */
macro_line|#else
DECL|macro|SN
mdefine_line|#define SN(X)
DECL|macro|SC
mdefine_line|#define SC(P,N) N
macro_line|#endif
multiline_comment|/* 2-byte Unicode character type. */
DECL|typedef|uchar_t
r_typedef
id|u16
id|uchar_t
suffix:semicolon
DECL|macro|UCHAR_T_SIZE_BITS
mdefine_line|#define UCHAR_T_SIZE_BITS 1
multiline_comment|/*&n; * Clusters are signed 64-bit values on NTFS volumes. We define two types, LCN&n; * and VCN, to allow for type checking and better code readability.&n; */
DECL|typedef|VCN
r_typedef
id|s64
id|VCN
suffix:semicolon
DECL|typedef|LCN
r_typedef
id|s64
id|LCN
suffix:semicolon
multiline_comment|/**&n; * run_list_element - in memory vcn to lcn mapping array element&n; * @vcn:&t;starting vcn of the current array element&n; * @lcn:&t;starting lcn of the current array element&n; * @length:&t;length in clusters of the current array element&n; * &n; * The last vcn (in fact the last vcn + 1) is reached when length == 0.&n; * &n; * When lcn == -1 this means that the count vcns starting at vcn are not &n; * physically allocated (i.e. this is a hole / data is sparse).&n; */
r_typedef
r_struct
(brace
multiline_comment|/* In memory vcn to lcn mapping structure element. */
DECL|member|vcn
id|VCN
id|vcn
suffix:semicolon
multiline_comment|/* vcn = Starting virtual cluster number. */
DECL|member|lcn
id|LCN
id|lcn
suffix:semicolon
multiline_comment|/* lcn = Starting logical cluster number. */
DECL|member|length
id|s64
id|length
suffix:semicolon
multiline_comment|/* Run length in clusters. */
DECL|typedef|run_list_element
)brace
id|run_list_element
suffix:semicolon
multiline_comment|/**&n; * run_list - in memory vcn to lcn mapping array including a read/write lock&n; * @rl:&t;&t;pointer to an array of run list elements&n; * @lock:&t;read/write spinlock for serializing access to @rl&n; * &n; */
r_typedef
r_struct
(brace
DECL|member|rl
id|run_list_element
op_star
id|rl
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|typedef|run_list
)brace
id|run_list
suffix:semicolon
DECL|macro|RUN_LIST_INIT
mdefine_line|#define RUN_LIST_INIT&t;&t;{ NULL, RW_LOCK_UNLOCKED }
DECL|macro|RUN_LIST
mdefine_line|#define RUN_LIST(name)&t;&t;run_list name = RUN_LIST_INIT
DECL|macro|INIT_RUN_LIST
mdefine_line|#define INIT_RUN_LIST(runlist)&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;run_list *___rl = runlist;&t;&bslash;&n;&t;&t;&t;&t;&t;___rl-&gt;rl = NULL;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;___rl-&gt;lock = RW_LOCK_UNLOCKED; &bslash;&n;&t;&t;&t;&t;} while (0)
r_typedef
r_enum
(brace
DECL|enumerator|FALSE
id|FALSE
op_assign
l_int|0
comma
DECL|enumerator|TRUE
id|TRUE
op_assign
l_int|1
DECL|typedef|BOOL
)brace
id|BOOL
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|CASE_SENSITIVE
id|CASE_SENSITIVE
op_assign
l_int|0
comma
DECL|enumerator|IGNORE_CASE
id|IGNORE_CASE
op_assign
l_int|1
comma
DECL|typedef|IGNORE_CASE_BOOL
)brace
id|IGNORE_CASE_BOOL
suffix:semicolon
macro_line|#endif /* _LINUX_NTFS_TYPES_H */
eof
