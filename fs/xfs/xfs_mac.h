multiline_comment|/*&n; * Copyright (c) 2001-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_MAC_H__
DECL|macro|__XFS_MAC_H__
mdefine_line|#define __XFS_MAC_H__
multiline_comment|/*&n; * Mandatory Access Control&n; *&n; * Layout of a composite MAC label:&n; * ml_list contains the list of categories (MSEN) followed by the list of&n; * divisions (MINT). This is actually a header for the data structure which&n; * will have an ml_list with more than one element.&n; *&n; *&t;-------------------------------&n; *&t;| ml_msen_type | ml_mint_type |&n; *&t;-------------------------------&n; *&t;| ml_level     | ml_grade     |&n; *&t;-------------------------------&n; *&t;| ml_catcount&t;&t;      |&n; *&t;-------------------------------&n; *&t;| ml_divcount&t;&t;      |&n; *&t;-------------------------------&n; *&t;| category 1&t;&t;      |&n; *&t;| . . .&t;&t;&t;      |&n; *&t;| category N&t;&t;      | (where N = ml_catcount)&n; *&t;-------------------------------&n; *&t;| division 1&t;&t;      |&n; *&t;| . . .&t;&t;&t;      |&n; *&t;| division M&t;&t;      | (where M = ml_divcount)&n; *&t;-------------------------------&n; */
DECL|macro|XFS_MAC_MAX_SETS
mdefine_line|#define XFS_MAC_MAX_SETS&t;250
DECL|struct|xfs_mac_label
r_typedef
r_struct
id|xfs_mac_label
(brace
DECL|member|ml_msen_type
id|__uint8_t
id|ml_msen_type
suffix:semicolon
multiline_comment|/* MSEN label type */
DECL|member|ml_mint_type
id|__uint8_t
id|ml_mint_type
suffix:semicolon
multiline_comment|/* MINT label type */
DECL|member|ml_level
id|__uint8_t
id|ml_level
suffix:semicolon
multiline_comment|/* Hierarchical level */
DECL|member|ml_grade
id|__uint8_t
id|ml_grade
suffix:semicolon
multiline_comment|/* Hierarchical grade */
DECL|member|ml_catcount
id|__uint16_t
id|ml_catcount
suffix:semicolon
multiline_comment|/* Category count */
DECL|member|ml_divcount
id|__uint16_t
id|ml_divcount
suffix:semicolon
multiline_comment|/* Division count */
multiline_comment|/* Category set, then Division set */
DECL|member|ml_list
id|__uint16_t
id|ml_list
(braket
id|XFS_MAC_MAX_SETS
)braket
suffix:semicolon
DECL|typedef|xfs_mac_label_t
)brace
id|xfs_mac_label_t
suffix:semicolon
multiline_comment|/* MSEN label type names. Choose an upper case ASCII character.&t; */
DECL|macro|XFS_MSEN_ADMIN_LABEL
mdefine_line|#define XFS_MSEN_ADMIN_LABEL&t;&squot;A&squot;&t;/* Admin: low&lt;admin != tcsec&lt;high */
DECL|macro|XFS_MSEN_EQUAL_LABEL
mdefine_line|#define XFS_MSEN_EQUAL_LABEL&t;&squot;E&squot;&t;/* Wildcard - always equal */
DECL|macro|XFS_MSEN_HIGH_LABEL
mdefine_line|#define XFS_MSEN_HIGH_LABEL&t;&squot;H&squot;&t;/* System High - always dominates */
DECL|macro|XFS_MSEN_MLD_HIGH_LABEL
mdefine_line|#define XFS_MSEN_MLD_HIGH_LABEL &squot;I&squot;&t;/* System High, multi-level dir */
DECL|macro|XFS_MSEN_LOW_LABEL
mdefine_line|#define XFS_MSEN_LOW_LABEL&t;&squot;L&squot;&t;/* System Low - always dominated */
DECL|macro|XFS_MSEN_MLD_LABEL
mdefine_line|#define XFS_MSEN_MLD_LABEL&t;&squot;M&squot;&t;/* TCSEC label on a multi-level dir */
DECL|macro|XFS_MSEN_MLD_LOW_LABEL
mdefine_line|#define XFS_MSEN_MLD_LOW_LABEL&t;&squot;N&squot;&t;/* System Low, multi-level dir */
DECL|macro|XFS_MSEN_TCSEC_LABEL
mdefine_line|#define XFS_MSEN_TCSEC_LABEL&t;&squot;T&squot;&t;/* TCSEC label */
DECL|macro|XFS_MSEN_UNKNOWN_LABEL
mdefine_line|#define XFS_MSEN_UNKNOWN_LABEL&t;&squot;U&squot;&t;/* unknown label */
multiline_comment|/* MINT label type names. Choose a lower case ASCII character.&t;*/
DECL|macro|XFS_MINT_BIBA_LABEL
mdefine_line|#define XFS_MINT_BIBA_LABEL&t;&squot;b&squot;&t;/* Dual of a TCSEC label */
DECL|macro|XFS_MINT_EQUAL_LABEL
mdefine_line|#define XFS_MINT_EQUAL_LABEL&t;&squot;e&squot;&t;/* Wildcard - always equal */
DECL|macro|XFS_MINT_HIGH_LABEL
mdefine_line|#define XFS_MINT_HIGH_LABEL&t;&squot;h&squot;&t;/* High Grade - always dominates */
DECL|macro|XFS_MINT_LOW_LABEL
mdefine_line|#define XFS_MINT_LOW_LABEL&t;&squot;l&squot;&t;/* Low Grade - always dominated */
multiline_comment|/* On-disk XFS extended attribute names */
DECL|macro|SGI_MAC_FILE
mdefine_line|#define SGI_MAC_FILE&t;&quot;SGI_MAC_FILE&quot;
DECL|macro|SGI_MAC_FILE_SIZE
mdefine_line|#define SGI_MAC_FILE_SIZE&t;(sizeof(SGI_MAC_FILE)-1)
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_FS_POSIX_MAC
multiline_comment|/* NOT YET IMPLEMENTED */
DECL|macro|MACEXEC
mdefine_line|#define MACEXEC&t;&t;00100
DECL|macro|MACWRITE
mdefine_line|#define MACWRITE&t;00200
DECL|macro|MACREAD
mdefine_line|#define MACREAD&t;&t;00400
r_struct
id|xfs_inode
suffix:semicolon
r_extern
r_int
id|xfs_mac_iaccess
c_func
(paren
r_struct
id|xfs_inode
op_star
comma
id|mode_t
comma
id|cred_t
op_star
)paren
suffix:semicolon
DECL|macro|_MAC_XFS_IACCESS
mdefine_line|#define _MAC_XFS_IACCESS(i,m,c) (xfs_mac_iaccess(i,m,c))
DECL|macro|_MAC_VACCESS
mdefine_line|#define _MAC_VACCESS(v,c,m)&t;(xfs_mac_vaccess(v,c,m))
DECL|macro|_MAC_EXISTS
mdefine_line|#define _MAC_EXISTS&t;&t;xfs_mac_vhaslabel
macro_line|#else
DECL|macro|_MAC_XFS_IACCESS
mdefine_line|#define _MAC_XFS_IACCESS(i,m,c) (0)
DECL|macro|_MAC_VACCESS
mdefine_line|#define _MAC_VACCESS(v,c,m)&t;(0)
DECL|macro|_MAC_EXISTS
mdefine_line|#define _MAC_EXISTS&t;&t;(NULL)
macro_line|#endif
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_MAC_H__ */
eof
