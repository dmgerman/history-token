macro_line|#ifndef _LINUX_DEVFS_FS_H
DECL|macro|_LINUX_DEVFS_FS_H
mdefine_line|#define _LINUX_DEVFS_FS_H
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|DEVFSD_PROTOCOL_REVISION_KERNEL
mdefine_line|#define DEVFSD_PROTOCOL_REVISION_KERNEL  5
DECL|macro|DEVFSD_IOCTL_BASE
mdefine_line|#define&t;DEVFSD_IOCTL_BASE&t;&squot;d&squot;
multiline_comment|/*  These are the various ioctls  */
DECL|macro|DEVFSDIOC_GET_PROTO_REV
mdefine_line|#define DEVFSDIOC_GET_PROTO_REV         _IOR(DEVFSD_IOCTL_BASE, 0, int)
DECL|macro|DEVFSDIOC_SET_EVENT_MASK
mdefine_line|#define DEVFSDIOC_SET_EVENT_MASK        _IOW(DEVFSD_IOCTL_BASE, 2, int)
DECL|macro|DEVFSDIOC_RELEASE_EVENT_QUEUE
mdefine_line|#define DEVFSDIOC_RELEASE_EVENT_QUEUE   _IOW(DEVFSD_IOCTL_BASE, 3, int)
DECL|macro|DEVFSDIOC_SET_DEBUG_MASK
mdefine_line|#define DEVFSDIOC_SET_DEBUG_MASK        _IOW(DEVFSD_IOCTL_BASE, 4, int)
DECL|macro|DEVFSD_NOTIFY_REGISTERED
mdefine_line|#define DEVFSD_NOTIFY_REGISTERED    0
DECL|macro|DEVFSD_NOTIFY_UNREGISTERED
mdefine_line|#define DEVFSD_NOTIFY_UNREGISTERED  1
DECL|macro|DEVFSD_NOTIFY_ASYNC_OPEN
mdefine_line|#define DEVFSD_NOTIFY_ASYNC_OPEN    2
DECL|macro|DEVFSD_NOTIFY_CLOSE
mdefine_line|#define DEVFSD_NOTIFY_CLOSE         3
DECL|macro|DEVFSD_NOTIFY_LOOKUP
mdefine_line|#define DEVFSD_NOTIFY_LOOKUP        4
DECL|macro|DEVFSD_NOTIFY_CHANGE
mdefine_line|#define DEVFSD_NOTIFY_CHANGE        5
DECL|macro|DEVFSD_NOTIFY_CREATE
mdefine_line|#define DEVFSD_NOTIFY_CREATE        6
DECL|macro|DEVFSD_NOTIFY_DELETE
mdefine_line|#define DEVFSD_NOTIFY_DELETE        7
DECL|macro|DEVFS_PATHLEN
mdefine_line|#define DEVFS_PATHLEN               1024  /*  Never change this otherwise the&n;&t;&t;&t;&t;&t;      binary interface will change   */
DECL|struct|devfsd_notify_struct
r_struct
id|devfsd_notify_struct
(brace
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/*  DEVFSD_NOTIFY_* value                   */
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/*  Mode of the inode or device entry       */
DECL|member|major
r_int
r_int
id|major
suffix:semicolon
multiline_comment|/*  Major number of device entry            */
DECL|member|minor
r_int
r_int
id|minor
suffix:semicolon
multiline_comment|/*  Minor number of device entry            */
DECL|member|uid
r_int
r_int
id|uid
suffix:semicolon
multiline_comment|/*  Uid of process, inode or device entry   */
DECL|member|gid
r_int
r_int
id|gid
suffix:semicolon
multiline_comment|/*  Gid of process, inode or device entry   */
DECL|member|overrun_count
r_int
r_int
id|overrun_count
suffix:semicolon
multiline_comment|/*  Number of lost events                   */
DECL|member|namelen
r_int
r_int
id|namelen
suffix:semicolon
multiline_comment|/*  Number of characters not including &squot;&bslash;0&squot; */
multiline_comment|/*  The device name MUST come last                                       */
DECL|member|devname
r_char
id|devname
(braket
id|DEVFS_PATHLEN
)braket
suffix:semicolon
multiline_comment|/*  This will be &squot;&bslash;0&squot; terminated            */
)brace
suffix:semicolon
macro_line|#endif  /*  _LINUX_DEVFS_FS_H  */
eof
