multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_EXTFREE_ITEM_H__
DECL|macro|__XFS_EXTFREE_ITEM_H__
mdefine_line|#define __XFS_EXTFREE_ITEM_H__
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|kmem_zone
suffix:semicolon
DECL|struct|xfs_extent
r_typedef
r_struct
id|xfs_extent
(brace
DECL|member|ext_start
id|xfs_dfsbno_t
id|ext_start
suffix:semicolon
DECL|member|ext_len
id|xfs_extlen_t
id|ext_len
suffix:semicolon
DECL|typedef|xfs_extent_t
)brace
id|xfs_extent_t
suffix:semicolon
multiline_comment|/*&n; * This is the structure used to lay out an efi log item in the&n; * log.&t; The efi_extents field is a variable size array whose&n; * size is given by efi_nextents.&n; */
DECL|struct|xfs_efi_log_format
r_typedef
r_struct
id|xfs_efi_log_format
(brace
DECL|member|efi_type
r_int
r_int
id|efi_type
suffix:semicolon
multiline_comment|/* efi log item type */
DECL|member|efi_size
r_int
r_int
id|efi_size
suffix:semicolon
multiline_comment|/* size of this item */
DECL|member|efi_nextents
id|uint
id|efi_nextents
suffix:semicolon
multiline_comment|/* # extents to free */
DECL|member|efi_id
id|__uint64_t
id|efi_id
suffix:semicolon
multiline_comment|/* efi identifier */
DECL|member|efi_extents
id|xfs_extent_t
id|efi_extents
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* array of extents to free */
DECL|typedef|xfs_efi_log_format_t
)brace
id|xfs_efi_log_format_t
suffix:semicolon
multiline_comment|/*&n; * This is the structure used to lay out an efd log item in the&n; * log.&t; The efd_extents array is a variable size array whose&n; * size is given by efd_nextents;&n; */
DECL|struct|xfs_efd_log_format
r_typedef
r_struct
id|xfs_efd_log_format
(brace
DECL|member|efd_type
r_int
r_int
id|efd_type
suffix:semicolon
multiline_comment|/* efd log item type */
DECL|member|efd_size
r_int
r_int
id|efd_size
suffix:semicolon
multiline_comment|/* size of this item */
DECL|member|efd_nextents
id|uint
id|efd_nextents
suffix:semicolon
multiline_comment|/* # of extents freed */
DECL|member|efd_efi_id
id|__uint64_t
id|efd_efi_id
suffix:semicolon
multiline_comment|/* id of corresponding efi */
DECL|member|efd_extents
id|xfs_extent_t
id|efd_extents
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* array of extents freed */
DECL|typedef|xfs_efd_log_format_t
)brace
id|xfs_efd_log_format_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Max number of extents in fast allocation path.&n; */
DECL|macro|XFS_EFI_MAX_FAST_EXTENTS
mdefine_line|#define XFS_EFI_MAX_FAST_EXTENTS&t;16
multiline_comment|/*&n; * Define EFI flags.&n; */
DECL|macro|XFS_EFI_RECOVERED
mdefine_line|#define XFS_EFI_RECOVERED&t;0x1
DECL|macro|XFS_EFI_COMMITTED
mdefine_line|#define XFS_EFI_COMMITTED&t;0x2
DECL|macro|XFS_EFI_CANCELED
mdefine_line|#define XFS_EFI_CANCELED&t;0x4
multiline_comment|/*&n; * This is the &quot;extent free intention&quot; log item.  It is used&n; * to log the fact that some extents need to be free.  It is&n; * used in conjunction with the &quot;extent free done&quot; log item&n; * described below.&n; */
DECL|struct|xfs_efi_log_item
r_typedef
r_struct
id|xfs_efi_log_item
(brace
DECL|member|efi_item
id|xfs_log_item_t
id|efi_item
suffix:semicolon
DECL|member|efi_flags
id|uint
id|efi_flags
suffix:semicolon
multiline_comment|/* misc flags */
DECL|member|efi_next_extent
id|uint
id|efi_next_extent
suffix:semicolon
DECL|member|efi_format
id|xfs_efi_log_format_t
id|efi_format
suffix:semicolon
DECL|typedef|xfs_efi_log_item_t
)brace
id|xfs_efi_log_item_t
suffix:semicolon
multiline_comment|/*&n; * This is the &quot;extent free done&quot; log item.  It is used to log&n; * the fact that some extents earlier mentioned in an efi item&n; * have been freed.&n; */
DECL|struct|xfs_efd_log_item
r_typedef
r_struct
id|xfs_efd_log_item
(brace
DECL|member|efd_item
id|xfs_log_item_t
id|efd_item
suffix:semicolon
DECL|member|efd_efip
id|xfs_efi_log_item_t
op_star
id|efd_efip
suffix:semicolon
DECL|member|efd_next_extent
id|uint
id|efd_next_extent
suffix:semicolon
DECL|member|efd_format
id|xfs_efd_log_format_t
id|efd_format
suffix:semicolon
DECL|typedef|xfs_efd_log_item_t
)brace
id|xfs_efd_log_item_t
suffix:semicolon
multiline_comment|/*&n; * Max number of extents in fast allocation path.&n; */
DECL|macro|XFS_EFD_MAX_FAST_EXTENTS
mdefine_line|#define XFS_EFD_MAX_FAST_EXTENTS&t;16
r_extern
r_struct
id|kmem_zone
op_star
id|xfs_efi_zone
suffix:semicolon
r_extern
r_struct
id|kmem_zone
op_star
id|xfs_efd_zone
suffix:semicolon
id|xfs_efi_log_item_t
op_star
id|xfs_efi_init
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|uint
)paren
suffix:semicolon
id|xfs_efd_log_item_t
op_star
id|xfs_efd_init
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|xfs_efi_log_item_t
op_star
comma
id|uint
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_EXTFREE_ITEM_H__ */
eof
