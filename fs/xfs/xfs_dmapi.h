multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DMAPI_H__
DECL|macro|__XFS_DMAPI_H__
mdefine_line|#define __XFS_DMAPI_H__
macro_line|#ifdef CONFIG_XFS_DMAPI
macro_line|#include &lt;dmapi/dmapi.h&gt;
macro_line|#include &lt;dmapi/dmapi_kern.h&gt;
multiline_comment|/*&t;Values used to define the on-disk version of dm_attrname_t. All&n; *&t;on-disk attribute names start with the 8-byte string &quot;SGI_DMI_&quot;.&n; *&n; *&t;In the on-disk inode, DMAPI attribute names consist of the user-provided&n; *&t;name with the DMATTR_PREFIXSTRING pre-pended.  This string must NEVER be&n; *&t;changed.&n; */
DECL|macro|DMATTR_PREFIXLEN
mdefine_line|#define DMATTR_PREFIXLEN&t;8
DECL|macro|DMATTR_PREFIXSTRING
mdefine_line|#define DMATTR_PREFIXSTRING&t;&quot;SGI_DMI_&quot;
multiline_comment|/* Defines for determining if an event message should be sent. */
DECL|macro|DM_EVENT_ENABLED
mdefine_line|#define DM_EVENT_ENABLED(vfsp, ip, event) ( &bslash;&n;&t;unlikely ((vfsp)-&gt;vfs_flag &amp; VFS_DMI) &amp;&amp; &bslash;&n;&t;&t;( ((ip)-&gt;i_d.di_dmevmask &amp; (1 &lt;&lt; event)) || &bslash;&n;&t;&t;  ((ip)-&gt;i_mount-&gt;m_dmevmask &amp; (1 &lt;&lt; event)) ) &bslash;&n;&t;)
DECL|macro|DM_EVENT_ENABLED_IO
mdefine_line|#define DM_EVENT_ENABLED_IO(vfsp, io, event) ( &bslash;&n;&t;unlikely ((vfsp)-&gt;vfs_flag &amp; VFS_DMI) &amp;&amp; &bslash;&n;&t;&t;( ((io)-&gt;io_dmevmask &amp; (1 &lt;&lt; event)) || &bslash;&n;&t;&t;  ((io)-&gt;io_mount-&gt;m_dmevmask &amp; (1 &lt;&lt; event)) ) &bslash;&n;&t;)
multiline_comment|/*&n; *&t;Macros to turn caller specified delay/block flags into&n; *&t;dm_send_xxxx_event flag DM_FLAGS_NDELAY.&n; */
DECL|macro|FILP_DELAY_FLAG
mdefine_line|#define FILP_DELAY_FLAG(filp) ((filp-&gt;f_flags&amp;(O_NDELAY|O_NONBLOCK)) ? &bslash;&n;&t;&t;&t;DM_FLAGS_NDELAY : 0)
DECL|macro|AT_DELAY_FLAG
mdefine_line|#define AT_DELAY_FLAG(f) ((f&amp;ATTR_NONBLOCK) ? DM_FLAGS_NDELAY : 0)
multiline_comment|/* events valid in dm_set_eventlist() when called with a filesystem handle.&n;   These events are not persistent.&n;*/
DECL|macro|DM_XFS_VALID_FS_EVENTS
mdefine_line|#define DM_XFS_VALID_FS_EVENTS&t;&t;( &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_PREUNMOUNT)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_UNMOUNT)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_NOSPACE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_DEBUT)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_CREATE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTCREATE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_REMOVE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTREMOVE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_RENAME)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTRENAME)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_LINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_SYMLINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTSYMLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_ATTRIBUTE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_DESTROY)&t;&t;)
multiline_comment|/* Events valid in dm_set_eventlist() when called with a file handle for&n;   a regular file or a symlink.&t; These events are persistent.&n;*/
DECL|macro|DM_XFS_VALID_FILE_EVENTS
mdefine_line|#define DM_XFS_VALID_FILE_EVENTS&t;( &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_ATTRIBUTE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_DESTROY)&t;&t;)
multiline_comment|/* Events valid in dm_set_eventlist() when called with a file handle for&n;   a directory.&t; These events are persistent.&n;*/
DECL|macro|DM_XFS_VALID_DIRECTORY_EVENTS
mdefine_line|#define DM_XFS_VALID_DIRECTORY_EVENTS&t;( &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_CREATE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTCREATE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_REMOVE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTREMOVE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_RENAME)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTRENAME)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_LINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_SYMLINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTSYMLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_ATTRIBUTE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_DESTROY)&t;&t;)
multiline_comment|/* Events supported by the XFS filesystem. */
DECL|macro|DM_XFS_SUPPORTED_EVENTS
mdefine_line|#define DM_XFS_SUPPORTED_EVENTS&t;&t;( &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_MOUNT)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_PREUNMOUNT)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_UNMOUNT)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_NOSPACE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_CREATE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTCREATE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_REMOVE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTREMOVE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_RENAME)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTRENAME)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_LINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_SYMLINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTSYMLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_READ)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_WRITE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_TRUNCATE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_ATTRIBUTE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_DESTROY)&t;&t;)
r_extern
r_int
id|xfs_dm_get_fsys_vector
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
comma
id|caddr_t
id|vecrq
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dm_send_data_event
c_func
(paren
id|dm_eventtype_t
id|event
comma
id|bhv_desc_t
op_star
id|bdp
comma
id|xfs_off_t
id|offset
comma
r_int
id|length
comma
r_int
id|flags
comma
id|vrwlock_t
op_star
id|locktype
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dm_send_mmap_event
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|wantflag
)paren
suffix:semicolon
macro_line|#else /* CONFIG_XFS_DMAPI */
multiline_comment|/*&n; *&t;Flags needed to build with dmapi disabled.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|DM_EVENT_INVALID
id|DM_EVENT_INVALID
op_assign
op_minus
l_int|1
comma
DECL|enumerator|DM_EVENT_CANCEL
id|DM_EVENT_CANCEL
op_assign
l_int|0
comma
multiline_comment|/* not supported */
DECL|enumerator|DM_EVENT_MOUNT
id|DM_EVENT_MOUNT
op_assign
l_int|1
comma
DECL|enumerator|DM_EVENT_PREUNMOUNT
id|DM_EVENT_PREUNMOUNT
op_assign
l_int|2
comma
DECL|enumerator|DM_EVENT_UNMOUNT
id|DM_EVENT_UNMOUNT
op_assign
l_int|3
comma
DECL|enumerator|DM_EVENT_DEBUT
id|DM_EVENT_DEBUT
op_assign
l_int|4
comma
multiline_comment|/* not supported */
DECL|enumerator|DM_EVENT_CREATE
id|DM_EVENT_CREATE
op_assign
l_int|5
comma
DECL|enumerator|DM_EVENT_CLOSE
id|DM_EVENT_CLOSE
op_assign
l_int|6
comma
multiline_comment|/* not supported */
DECL|enumerator|DM_EVENT_POSTCREATE
id|DM_EVENT_POSTCREATE
op_assign
l_int|7
comma
DECL|enumerator|DM_EVENT_REMOVE
id|DM_EVENT_REMOVE
op_assign
l_int|8
comma
DECL|enumerator|DM_EVENT_POSTREMOVE
id|DM_EVENT_POSTREMOVE
op_assign
l_int|9
comma
DECL|enumerator|DM_EVENT_RENAME
id|DM_EVENT_RENAME
op_assign
l_int|10
comma
DECL|enumerator|DM_EVENT_POSTRENAME
id|DM_EVENT_POSTRENAME
op_assign
l_int|11
comma
DECL|enumerator|DM_EVENT_LINK
id|DM_EVENT_LINK
op_assign
l_int|12
comma
DECL|enumerator|DM_EVENT_POSTLINK
id|DM_EVENT_POSTLINK
op_assign
l_int|13
comma
DECL|enumerator|DM_EVENT_SYMLINK
id|DM_EVENT_SYMLINK
op_assign
l_int|14
comma
DECL|enumerator|DM_EVENT_POSTSYMLINK
id|DM_EVENT_POSTSYMLINK
op_assign
l_int|15
comma
DECL|enumerator|DM_EVENT_READ
id|DM_EVENT_READ
op_assign
l_int|16
comma
DECL|enumerator|DM_EVENT_WRITE
id|DM_EVENT_WRITE
op_assign
l_int|17
comma
DECL|enumerator|DM_EVENT_TRUNCATE
id|DM_EVENT_TRUNCATE
op_assign
l_int|18
comma
DECL|enumerator|DM_EVENT_ATTRIBUTE
id|DM_EVENT_ATTRIBUTE
op_assign
l_int|19
comma
DECL|enumerator|DM_EVENT_DESTROY
id|DM_EVENT_DESTROY
op_assign
l_int|20
comma
DECL|enumerator|DM_EVENT_NOSPACE
id|DM_EVENT_NOSPACE
op_assign
l_int|21
comma
DECL|enumerator|DM_EVENT_USER
id|DM_EVENT_USER
op_assign
l_int|22
comma
DECL|enumerator|DM_EVENT_MAX
id|DM_EVENT_MAX
op_assign
l_int|23
DECL|typedef|dm_eventtype_t
)brace
id|dm_eventtype_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|DM_RIGHT_NULL
id|DM_RIGHT_NULL
comma
DECL|enumerator|DM_RIGHT_SHARED
id|DM_RIGHT_SHARED
comma
DECL|enumerator|DM_RIGHT_EXCL
id|DM_RIGHT_EXCL
DECL|typedef|dm_right_t
)brace
id|dm_right_t
suffix:semicolon
multiline_comment|/*&n; *&t;Defines for determining if an event message should be sent.&n; */
DECL|macro|DM_EVENT_ENABLED
mdefine_line|#define DM_EVENT_ENABLED(vfsp, ip, event)&t;0
DECL|macro|DM_EVENT_ENABLED_IO
mdefine_line|#define DM_EVENT_ENABLED_IO(vfsp, io, event)&t;0
multiline_comment|/*&n; *&t;Stubbed out DMAPI delay macros.&n; */
DECL|macro|FILP_DELAY_FLAG
mdefine_line|#define FILP_DELAY_FLAG(filp)&t;&t;&t;0
DECL|macro|AT_DELAY_FLAG
mdefine_line|#define AT_DELAY_FLAG(f)&t;&t;&t;0
multiline_comment|/*&n; *&t;Events supported by the XFS filesystem.&n; */
DECL|macro|DM_XFS_VALID_FS_EVENTS
mdefine_line|#define DM_XFS_VALID_FS_EVENTS&t;&t;&t;0
DECL|macro|DM_XFS_VALID_FILE_EVENTS
mdefine_line|#define DM_XFS_VALID_FILE_EVENTS&t;&t;0
DECL|macro|DM_XFS_VALID_DIRECTORY_EVENTS
mdefine_line|#define DM_XFS_VALID_DIRECTORY_EVENTS&t;&t;0
DECL|macro|DM_XFS_SUPPORTED_EVENTS
mdefine_line|#define DM_XFS_SUPPORTED_EVENTS&t;&t;&t;0
multiline_comment|/*&n; *&t;Dummy definitions used for the flags field on dm_send_*_event().&n; */
DECL|macro|DM_FLAGS_NDELAY
mdefine_line|#define DM_FLAGS_NDELAY&t;&t;0x001&t;/* return EAGAIN after dm_pending() */
DECL|macro|DM_FLAGS_UNWANTED
mdefine_line|#define DM_FLAGS_UNWANTED&t;0x002&t;/* event not in fsys dm_eventset_t */
multiline_comment|/*&n; *&t;Stubs for XFS DMAPI utility routines.&n; */
r_static
id|__inline
r_int
DECL|function|xfs_dm_send_data_event
id|xfs_dm_send_data_event
c_func
(paren
id|dm_eventtype_t
id|event
comma
id|bhv_desc_t
op_star
id|bdp
comma
id|xfs_off_t
id|offset
comma
r_int
id|length
comma
r_int
id|flags
comma
id|vrwlock_t
op_star
id|locktype
)paren
(brace
r_return
id|ENOSYS
suffix:semicolon
)brace
r_static
id|__inline
r_int
DECL|function|xfs_dm_send_mmap_event
id|xfs_dm_send_mmap_event
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|wantflag
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Stubs for routines needed for the X/Open version of DMAPI.&n; */
r_static
id|__inline
r_int
DECL|function|dm_send_destroy_event
id|dm_send_destroy_event
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
comma
id|dm_right_t
id|vp_right
)paren
(brace
r_return
id|ENOSYS
suffix:semicolon
)brace
r_static
id|__inline
r_int
DECL|function|dm_send_namesp_event
id|dm_send_namesp_event
c_func
(paren
id|dm_eventtype_t
id|event
comma
id|bhv_desc_t
op_star
id|bdp1
comma
id|dm_right_t
id|vp1_right
comma
id|bhv_desc_t
op_star
id|bdp2
comma
id|dm_right_t
id|vp2_right
comma
r_char
op_star
id|name1
comma
r_char
op_star
id|name2
comma
id|mode_t
id|mode
comma
r_int
id|retcode
comma
r_int
id|flags
)paren
(brace
r_return
id|ENOSYS
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|dm_send_unmount_event
id|dm_send_unmount_event
c_func
(paren
id|vfs_t
op_star
id|vfsp
comma
id|vnode_t
op_star
id|vp
comma
id|dm_right_t
id|vfsp_right
comma
id|mode_t
id|mode
comma
r_int
id|retcode
comma
r_int
id|flags
)paren
(brace
)brace
macro_line|#endif&t;/* CONFIG_XFS_DMAPI */
macro_line|#endif&t;/* __XFS_DMAPI_H__ */
eof
