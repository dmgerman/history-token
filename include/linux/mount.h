multiline_comment|/*&n; *&n; * Definitions for mount interface. This describes the in the kernel build &n; * linkedlist with mounted filesystems.&n; *&n; * Author:  Marco van Wieringen &lt;mvw@planets.elm.net&gt;&n; *&n; * Version: $Id: mount.h,v 2.0 1996/11/17 16:48:14 mvw Exp mvw $&n; *&n; */
macro_line|#ifndef _LINUX_MOUNT_H
DECL|macro|_LINUX_MOUNT_H
mdefine_line|#define _LINUX_MOUNT_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/list.h&gt;
DECL|macro|MNT_NOSUID
mdefine_line|#define MNT_NOSUID&t;1
DECL|macro|MNT_NODEV
mdefine_line|#define MNT_NODEV&t;2
DECL|macro|MNT_NOEXEC
mdefine_line|#define MNT_NOEXEC&t;4
DECL|struct|vfsmount
r_struct
id|vfsmount
(brace
DECL|member|mnt_hash
r_struct
id|list_head
id|mnt_hash
suffix:semicolon
DECL|member|mnt_parent
r_struct
id|vfsmount
op_star
id|mnt_parent
suffix:semicolon
multiline_comment|/* fs we are mounted on */
DECL|member|mnt_mountpoint
r_struct
id|dentry
op_star
id|mnt_mountpoint
suffix:semicolon
multiline_comment|/* dentry of mountpoint */
DECL|member|mnt_root
r_struct
id|dentry
op_star
id|mnt_root
suffix:semicolon
multiline_comment|/* root of the mounted tree */
DECL|member|mnt_sb
r_struct
id|super_block
op_star
id|mnt_sb
suffix:semicolon
multiline_comment|/* pointer to superblock */
DECL|member|mnt_mounts
r_struct
id|list_head
id|mnt_mounts
suffix:semicolon
multiline_comment|/* list of children, anchored here */
DECL|member|mnt_child
r_struct
id|list_head
id|mnt_child
suffix:semicolon
multiline_comment|/* and going through their mnt_child */
DECL|member|mnt_count
id|atomic_t
id|mnt_count
suffix:semicolon
DECL|member|mnt_flags
r_int
id|mnt_flags
suffix:semicolon
DECL|member|mnt_expiry_mark
r_int
id|mnt_expiry_mark
suffix:semicolon
multiline_comment|/* true if marked for expiry */
DECL|member|mnt_devname
r_char
op_star
id|mnt_devname
suffix:semicolon
multiline_comment|/* Name of device e.g. /dev/dsk/hda1 */
DECL|member|mnt_list
r_struct
id|list_head
id|mnt_list
suffix:semicolon
DECL|member|mnt_fslink
r_struct
id|list_head
id|mnt_fslink
suffix:semicolon
multiline_comment|/* link in fs-specific expiry list */
DECL|member|mnt_namespace
r_struct
r_namespace
op_star
id|mnt_namespace
suffix:semicolon
multiline_comment|/* containing namespace */
)brace
suffix:semicolon
DECL|function|mntget
r_static
r_inline
r_struct
id|vfsmount
op_star
id|mntget
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
)paren
(brace
r_if
c_cond
(paren
id|mnt
)paren
id|atomic_inc
c_func
(paren
op_amp
id|mnt-&gt;mnt_count
)paren
suffix:semicolon
r_return
id|mnt
suffix:semicolon
)brace
r_extern
r_void
id|__mntput
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
)paren
suffix:semicolon
DECL|function|_mntput
r_static
r_inline
r_void
id|_mntput
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
)paren
(brace
r_if
c_cond
(paren
id|mnt
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|mnt-&gt;mnt_count
)paren
)paren
id|__mntput
c_func
(paren
id|mnt
)paren
suffix:semicolon
)brace
)brace
DECL|function|mntput
r_static
r_inline
r_void
id|mntput
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
)paren
(brace
r_if
c_cond
(paren
id|mnt
)paren
(brace
id|mnt-&gt;mnt_expiry_mark
op_assign
l_int|0
suffix:semicolon
id|_mntput
c_func
(paren
id|mnt
)paren
suffix:semicolon
)brace
)brace
r_extern
r_void
id|free_vfsmnt
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
)paren
suffix:semicolon
r_extern
r_struct
id|vfsmount
op_star
id|alloc_vfsmnt
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_struct
id|vfsmount
op_star
id|do_kern_mount
c_func
(paren
r_const
r_char
op_star
id|fstype
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_struct
id|nameidata
suffix:semicolon
r_extern
r_int
id|do_add_mount
c_func
(paren
r_struct
id|vfsmount
op_star
id|newmnt
comma
r_struct
id|nameidata
op_star
id|nd
comma
r_int
id|mnt_flags
comma
r_struct
id|list_head
op_star
id|fslist
)paren
suffix:semicolon
r_extern
r_void
id|mark_mounts_for_expiry
c_func
(paren
r_struct
id|list_head
op_star
id|mounts
)paren
suffix:semicolon
r_extern
id|spinlock_t
id|vfsmount_lock
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _LINUX_MOUNT_H */
eof
