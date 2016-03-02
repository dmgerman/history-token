multiline_comment|/*&n; * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DMAPI_H__
DECL|macro|__XFS_DMAPI_H__
mdefine_line|#define __XFS_DMAPI_H__
multiline_comment|/*&t;Values used to define the on-disk version of dm_attrname_t. All&n; *&t;on-disk attribute names start with the 8-byte string &quot;SGI_DMI_&quot;.&n; *&n; *      In the on-disk inode, DMAPI attribute names consist of the user-provided&n; *      name with the DMATTR_PREFIXSTRING pre-pended.  This string must NEVER be&n; *      changed.&n; */
DECL|macro|DMATTR_PREFIXLEN
mdefine_line|#define DMATTR_PREFIXLEN&t;8
DECL|macro|DMATTR_PREFIXSTRING
mdefine_line|#define DMATTR_PREFIXSTRING&t;&quot;SGI_DMI_&quot;
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
DECL|macro|HAVE_DM_EVENTTYPE_T
mdefine_line|#define HAVE_DM_EVENTTYPE_T
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
DECL|macro|HAVE_DM_RIGHT_T
mdefine_line|#define HAVE_DM_RIGHT_T
multiline_comment|/* Defines for determining if an event message should be sent. */
DECL|macro|DM_EVENT_ENABLED
mdefine_line|#define&t;DM_EVENT_ENABLED(vfsp, ip, event) ( &bslash;&n;&t;unlikely ((vfsp)-&gt;vfs_flag &amp; VFS_DMI) &amp;&amp; &bslash;&n;&t;&t;( ((ip)-&gt;i_d.di_dmevmask &amp; (1 &lt;&lt; event)) || &bslash;&n;&t;&t;  ((ip)-&gt;i_mount-&gt;m_dmevmask &amp; (1 &lt;&lt; event)) ) &bslash;&n;&t;)
DECL|macro|DM_EVENT_ENABLED_IO
mdefine_line|#define&t;DM_EVENT_ENABLED_IO(vfsp, io, event) ( &bslash;&n;&t;unlikely ((vfsp)-&gt;vfs_flag &amp; VFS_DMI) &amp;&amp; &bslash;&n;&t;&t;( ((io)-&gt;io_dmevmask &amp; (1 &lt;&lt; event)) || &bslash;&n;&t;&t;  ((io)-&gt;io_mount-&gt;m_dmevmask &amp; (1 &lt;&lt; event)) ) &bslash;&n;&t;)
DECL|macro|DM_XFS_VALID_FS_EVENTS
mdefine_line|#define DM_XFS_VALID_FS_EVENTS&t;&t;( &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_PREUNMOUNT)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_UNMOUNT)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_NOSPACE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_DEBUT)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_CREATE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTCREATE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_REMOVE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTREMOVE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_RENAME)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTRENAME)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_LINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_SYMLINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTSYMLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_ATTRIBUTE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_DESTROY)&t;&t;)
multiline_comment|/* Events valid in dm_set_eventlist() when called with a file handle for&n;   a regular file or a symlink.  These events are persistent.&n;*/
DECL|macro|DM_XFS_VALID_FILE_EVENTS
mdefine_line|#define&t;DM_XFS_VALID_FILE_EVENTS&t;( &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_ATTRIBUTE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_DESTROY)&t;&t;)
multiline_comment|/* Events valid in dm_set_eventlist() when called with a file handle for&n;   a directory.  These events are persistent.&n;*/
DECL|macro|DM_XFS_VALID_DIRECTORY_EVENTS
mdefine_line|#define&t;DM_XFS_VALID_DIRECTORY_EVENTS&t;( &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_CREATE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTCREATE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_REMOVE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTREMOVE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_RENAME)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTRENAME)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_LINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_SYMLINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTSYMLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_ATTRIBUTE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_DESTROY)&t;&t;)
multiline_comment|/* Events supported by the XFS filesystem. */
DECL|macro|DM_XFS_SUPPORTED_EVENTS
mdefine_line|#define&t;DM_XFS_SUPPORTED_EVENTS&t;&t;( &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_MOUNT)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_PREUNMOUNT)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_UNMOUNT)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_NOSPACE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_CREATE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTCREATE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_REMOVE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTREMOVE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_RENAME)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTRENAME)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_LINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_SYMLINK)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_POSTSYMLINK)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_READ)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_WRITE)&t;&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_TRUNCATE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_ATTRIBUTE)&t;| &bslash;&n;&t;(1 &lt;&lt; DM_EVENT_DESTROY)&t;&t;)
multiline_comment|/*&n; *&t;Definitions used for the flags field on dm_send_*_event().&n; */
DECL|macro|DM_FLAGS_NDELAY
mdefine_line|#define DM_FLAGS_NDELAY&t;&t;0x001&t;/* return EAGAIN after dm_pending() */
DECL|macro|DM_FLAGS_UNWANTED
mdefine_line|#define DM_FLAGS_UNWANTED&t;0x002&t;/* event not in fsys dm_eventset_t */
DECL|macro|DM_FLAGS_ISEM
mdefine_line|#define DM_FLAGS_ISEM&t;&t;0x004&t;/* thread holds i_sem */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,6,0)
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,4,21)
multiline_comment|/* i_alloc_sem was added in 2.4.22-pre1 */
DECL|macro|DM_FLAGS_IALLOCSEM_RD
mdefine_line|#define DM_FLAGS_IALLOCSEM_RD&t;0x010&t;/* thread holds i_alloc_sem rd */
DECL|macro|DM_FLAGS_IALLOCSEM_WR
mdefine_line|#define DM_FLAGS_IALLOCSEM_WR&t;0x020&t;/* thread holds i_alloc_sem wr */
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; *&t;Based on IO_ISDIRECT, decide which i_ flag is set.&n; */
macro_line|#ifdef DM_FLAGS_IALLOCSEM_RD
DECL|macro|DM_SEM_FLAG_RD
mdefine_line|#define DM_SEM_FLAG_RD(ioflags) (((ioflags) &amp; IO_ISDIRECT) ? &bslash;&n;&t;&t;&t;      DM_FLAGS_IALLOCSEM_RD : DM_FLAGS_ISEM)
DECL|macro|DM_SEM_FLAG_WR
mdefine_line|#define DM_SEM_FLAG_WR&t;(DM_FLAGS_IALLOCSEM_WR | DM_FLAGS_ISEM)
macro_line|#else
DECL|macro|DM_SEM_FLAG_RD
mdefine_line|#define DM_SEM_FLAG_RD(ioflags) (((ioflags) &amp; IO_ISDIRECT) ? &bslash;&n;&t;&t;&t;      0 : DM_FLAGS_ISEM)
DECL|macro|DM_SEM_FLAG_WR
mdefine_line|#define DM_SEM_FLAG_WR&t;(DM_FLAGS_ISEM)
macro_line|#endif
multiline_comment|/*&n; *&t;Macros to turn caller specified delay/block flags into&n; *&t;dm_send_xxxx_event flag DM_FLAGS_NDELAY.&n; */
DECL|macro|FILP_DELAY_FLAG
mdefine_line|#define FILP_DELAY_FLAG(filp) ((filp-&gt;f_flags&amp;(O_NDELAY|O_NONBLOCK)) ? &bslash;&n;&t;&t;&t;DM_FLAGS_NDELAY : 0)
DECL|macro|AT_DELAY_FLAG
mdefine_line|#define AT_DELAY_FLAG(f) ((f&amp;ATTR_NONBLOCK) ? DM_FLAGS_NDELAY : 0)
r_extern
r_struct
id|bhv_vfsops
id|xfs_dmops
suffix:semicolon
macro_line|#ifdef CONFIG_XFS_DMAPI
r_void
id|xfs_dm_init
c_func
(paren
r_struct
id|file_system_type
op_star
)paren
suffix:semicolon
r_void
id|xfs_dm_exit
c_func
(paren
r_struct
id|file_system_type
op_star
)paren
suffix:semicolon
DECL|macro|XFS_DM_INIT
mdefine_line|#define XFS_DM_INIT(fstype)&t;xfs_dm_init(fstype)
DECL|macro|XFS_DM_EXIT
mdefine_line|#define XFS_DM_EXIT(fstype)&t;xfs_dm_exit(fstype)
macro_line|#else
DECL|macro|XFS_DM_INIT
mdefine_line|#define XFS_DM_INIT(fstype)
DECL|macro|XFS_DM_EXIT
mdefine_line|#define XFS_DM_EXIT(fstype)
macro_line|#endif
macro_line|#endif  /* __XFS_DMAPI_H__ */
eof
