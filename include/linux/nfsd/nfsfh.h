multiline_comment|/*&n; * include/linux/nfsd/nfsfh.h&n; *&n; * This file describes the layout of the file handles as passed&n; * over the wire.&n; *&n; * Earlier versions of knfsd used to sign file handles using keyed MD5&n; * or SHA. I&squot;ve removed this code, because it doesn&squot;t give you more&n; * security than blocking external access to port 2049 on your firewall.&n; *&n; * Copyright (C) 1995, 1996, 1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_NFSD_FH_H
DECL|macro|_LINUX_NFSD_FH_H
mdefine_line|#define _LINUX_NFSD_FH_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|# include &lt;linux/config.h&gt;
macro_line|# include &lt;linux/types.h&gt;
macro_line|# include &lt;linux/string.h&gt;
macro_line|# include &lt;linux/fs.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/nfsd/const.h&gt;
macro_line|#include &lt;linux/nfsd/debug.h&gt;
multiline_comment|/*&n; * This is the old &quot;dentry style&quot; Linux NFSv2 file handle.&n; *&n; * The xino and xdev fields are currently used to transport the&n; * ino/dev of the exported inode.&n; */
DECL|struct|nfs_fhbase_old
r_struct
id|nfs_fhbase_old
(brace
DECL|member|fb_dcookie
id|__u32
id|fb_dcookie
suffix:semicolon
multiline_comment|/* dentry cookie - always 0xfeebbaca */
DECL|member|fb_ino
id|__u32
id|fb_ino
suffix:semicolon
multiline_comment|/* our inode number */
DECL|member|fb_dirino
id|__u32
id|fb_dirino
suffix:semicolon
multiline_comment|/* dir inode number, 0 for directories */
DECL|member|fb_dev
id|__u32
id|fb_dev
suffix:semicolon
multiline_comment|/* our device */
DECL|member|fb_xdev
id|__u32
id|fb_xdev
suffix:semicolon
DECL|member|fb_xino
id|__u32
id|fb_xino
suffix:semicolon
DECL|member|fb_generation
id|__u32
id|fb_generation
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the new flexible, extensible style NFSv2/v3 file handle.&n; * by Neil Brown &lt;neilb@cse.unsw.edu.au&gt; - March 2000&n; *&n; * The file handle is seens as a list of 4byte words.&n; * The first word contains a version number (1) and four descriptor bytes&n; * that tell how the remaining 3 variable length fields should be handled.&n; * These three bytes are auth_type, fsid_type and fileid_type.&n; *&n; * All 4byte values are in host-byte-order.&n; *&n; * The auth_type field specifies how the filehandle can be authenticated&n; * This might allow a file to be confirmed to be in a writable part of a&n; * filetree without checking the path from it upto the root.&n; * Current values:&n; *     0  - No authentication.  fb_auth is 0 bytes long&n; * Possible future values:&n; *     1  - 4 bytes taken from MD5 hash of the remainer of the file handle&n; *          prefixed by a secret and with the important export flags.&n; *&n; * The fsid_type identifies how the filesystem (or export point) is&n; *    encoded.&n; *  Current values:&n; *     0  - 4 byte device id (ms-2-bytes major, ls-2-bytes minor), 4byte inode number&n; *        NOTE: we cannot use the kdev_t device id value, because kdev_t.h&n; *              says we mustn&squot;t.  We must break it up and reassemble.&n; *  Possible future encodings:&n; *     1  - 4 byte user specified identifier&n; *&n; * The fileid_type identified how the file within the filesystem is encoded.&n; * This is (will be) passed to, and set by, the underlying filesystem if it supports&n; * filehandle operations.  The filesystem must not use the value &squot;0&squot; or &squot;0xff&squot; and may&n; * only use the values 1 and 2 as defined below:&n; *  Current values:&n; *    0   - The root, or export point, of the filesystem.  fb_fileid is 0 bytes.&n; *    1   - 32bit inode number, 32 bit generation number.&n; *    2   - 32bit inode number, 32 bit generation number, 32 bit parent directory inode number.&n; *&n; */
DECL|struct|nfs_fhbase_new
r_struct
id|nfs_fhbase_new
(brace
DECL|member|fb_version
id|__u8
id|fb_version
suffix:semicolon
multiline_comment|/* == 1, even =&gt; nfs_fhbase_old */
DECL|member|fb_auth_type
id|__u8
id|fb_auth_type
suffix:semicolon
DECL|member|fb_fsid_type
id|__u8
id|fb_fsid_type
suffix:semicolon
DECL|member|fb_fileid_type
id|__u8
id|fb_fileid_type
suffix:semicolon
DECL|member|fb_auth
id|__u32
id|fb_auth
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*&t;__u32&t;&t;fb_fsid[0]; floating */
multiline_comment|/*&t;__u32&t;&t;fb_fileid[0]; floating */
)brace
suffix:semicolon
DECL|struct|knfsd_fh
r_struct
id|knfsd_fh
(brace
DECL|member|fh_size
r_int
r_int
id|fh_size
suffix:semicolon
multiline_comment|/* significant for NFSv3.&n;&t;&t;&t;&t;&t; * Points to the current size while building&n;&t;&t;&t;&t;&t; * a new file handle&n;&t;&t;&t;&t;&t; */
r_union
(brace
DECL|member|fh_old
r_struct
id|nfs_fhbase_old
id|fh_old
suffix:semicolon
DECL|member|fh_pad
id|__u32
id|fh_pad
(braket
id|NFS4_FHSIZE
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|fh_new
r_struct
id|nfs_fhbase_new
id|fh_new
suffix:semicolon
DECL|member|fh_base
)brace
id|fh_base
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ofh_dcookie
mdefine_line|#define ofh_dcookie&t;&t;fh_base.fh_old.fb_dcookie
DECL|macro|ofh_ino
mdefine_line|#define ofh_ino&t;&t;&t;fh_base.fh_old.fb_ino
DECL|macro|ofh_dirino
mdefine_line|#define ofh_dirino&t;&t;fh_base.fh_old.fb_dirino
DECL|macro|ofh_dev
mdefine_line|#define ofh_dev&t;&t;&t;fh_base.fh_old.fb_dev
DECL|macro|ofh_xdev
mdefine_line|#define ofh_xdev&t;&t;fh_base.fh_old.fb_xdev
DECL|macro|ofh_xino
mdefine_line|#define ofh_xino&t;&t;fh_base.fh_old.fb_xino
DECL|macro|ofh_generation
mdefine_line|#define ofh_generation&t;&t;fh_base.fh_old.fb_generation
DECL|macro|fh_version
mdefine_line|#define&t;fh_version&t;&t;fh_base.fh_new.fb_version
DECL|macro|fh_fsid_type
mdefine_line|#define&t;fh_fsid_type&t;&t;fh_base.fh_new.fb_fsid_type
DECL|macro|fh_auth_type
mdefine_line|#define&t;fh_auth_type&t;&t;fh_base.fh_new.fb_auth_type
DECL|macro|fh_fileid_type
mdefine_line|#define&t;fh_fileid_type&t;&t;fh_base.fh_new.fb_fileid_type
DECL|macro|fh_auth
mdefine_line|#define&t;fh_auth&t;&t;&t;fh_base.fh_new.fb_auth
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Conversion macros for the filehandle fields.&n; *&n; * Keep the device numbers in &quot;backwards compatible&n; * format&quot;, ie the low 16 bits contain the low 8 bits&n; * of the 20-bit minor and the 12-bit major number.&n; *&n; * The high 16 bits contain the rest (4 bits major&n; * and 12 bits minor),&n; */
DECL|function|u32_to_dev_t
r_static
r_inline
id|dev_t
id|u32_to_dev_t
c_func
(paren
id|__u32
id|udev
)paren
(brace
r_int
r_int
id|minor
comma
id|major
suffix:semicolon
id|minor
op_assign
(paren
id|udev
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|udev
op_rshift
l_int|8
)paren
op_amp
l_int|0xfff00
)paren
suffix:semicolon
id|major
op_assign
(paren
(paren
id|udev
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|udev
op_rshift
l_int|20
)paren
op_amp
l_int|0xf00
)paren
suffix:semicolon
r_return
id|MKDEV
c_func
(paren
id|major
comma
id|minor
)paren
suffix:semicolon
)brace
DECL|function|ino_t_to_u32
r_static
r_inline
id|__u32
id|ino_t_to_u32
c_func
(paren
id|ino_t
id|ino
)paren
(brace
r_return
(paren
id|__u32
)paren
id|ino
suffix:semicolon
)brace
DECL|function|u32_to_ino_t
r_static
r_inline
id|ino_t
id|u32_to_ino_t
c_func
(paren
id|__u32
id|uino
)paren
(brace
r_return
(paren
id|ino_t
)paren
id|uino
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the internal representation of an NFS handle used in knfsd.&n; * pre_mtime/post_version will be used to support wcc_attr&squot;s in NFSv3.&n; */
DECL|struct|svc_fh
r_typedef
r_struct
id|svc_fh
(brace
DECL|member|fh_handle
r_struct
id|knfsd_fh
id|fh_handle
suffix:semicolon
multiline_comment|/* FH data */
DECL|member|fh_dentry
r_struct
id|dentry
op_star
id|fh_dentry
suffix:semicolon
multiline_comment|/* validated dentry */
DECL|member|fh_export
r_struct
id|svc_export
op_star
id|fh_export
suffix:semicolon
multiline_comment|/* export pointer */
DECL|member|fh_maxsize
r_int
id|fh_maxsize
suffix:semicolon
multiline_comment|/* max size for fh_handle */
DECL|member|fh_locked
r_int
r_char
id|fh_locked
suffix:semicolon
multiline_comment|/* inode locked by us */
macro_line|#ifdef CONFIG_NFSD_V3
DECL|member|fh_post_saved
r_int
r_char
id|fh_post_saved
suffix:semicolon
multiline_comment|/* post-op attrs saved */
DECL|member|fh_pre_saved
r_int
r_char
id|fh_pre_saved
suffix:semicolon
multiline_comment|/* pre-op attrs saved */
multiline_comment|/* Pre-op attributes saved during fh_lock */
DECL|member|fh_pre_size
id|__u64
id|fh_pre_size
suffix:semicolon
multiline_comment|/* size before operation */
DECL|member|fh_pre_mtime
r_struct
id|timespec
id|fh_pre_mtime
suffix:semicolon
multiline_comment|/* mtime before oper */
DECL|member|fh_pre_ctime
r_struct
id|timespec
id|fh_pre_ctime
suffix:semicolon
multiline_comment|/* ctime before oper */
multiline_comment|/* Post-op attributes saved in fh_unlock */
DECL|member|fh_post_mode
id|umode_t
id|fh_post_mode
suffix:semicolon
multiline_comment|/* i_mode */
DECL|member|fh_post_nlink
id|nlink_t
id|fh_post_nlink
suffix:semicolon
multiline_comment|/* i_nlink */
DECL|member|fh_post_uid
id|uid_t
id|fh_post_uid
suffix:semicolon
multiline_comment|/* i_uid */
DECL|member|fh_post_gid
id|gid_t
id|fh_post_gid
suffix:semicolon
multiline_comment|/* i_gid */
DECL|member|fh_post_size
id|__u64
id|fh_post_size
suffix:semicolon
multiline_comment|/* i_size */
DECL|member|fh_post_blocks
r_int
r_int
id|fh_post_blocks
suffix:semicolon
multiline_comment|/* i_blocks */
DECL|member|fh_post_blksize
r_int
r_int
id|fh_post_blksize
suffix:semicolon
multiline_comment|/* i_blksize */
DECL|member|fh_post_rdev
id|__u32
id|fh_post_rdev
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* i_rdev */
DECL|member|fh_post_atime
r_struct
id|timespec
id|fh_post_atime
suffix:semicolon
multiline_comment|/* i_atime */
DECL|member|fh_post_mtime
r_struct
id|timespec
id|fh_post_mtime
suffix:semicolon
multiline_comment|/* i_mtime */
DECL|member|fh_post_ctime
r_struct
id|timespec
id|fh_post_ctime
suffix:semicolon
multiline_comment|/* i_ctime */
macro_line|#endif /* CONFIG_NFSD_V3 */
DECL|typedef|svc_fh
)brace
id|svc_fh
suffix:semicolon
DECL|function|mk_fsid_v0
r_static
r_inline
r_void
id|mk_fsid_v0
c_func
(paren
id|u32
op_star
id|fsidv
comma
id|dev_t
id|dev
comma
id|ino_t
id|ino
)paren
(brace
id|fsidv
(braket
l_int|0
)braket
op_assign
id|htonl
c_func
(paren
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
op_lshift
l_int|16
)paren
op_or
id|MINOR
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|fsidv
(braket
l_int|1
)braket
op_assign
id|ino_t_to_u32
c_func
(paren
id|ino
)paren
suffix:semicolon
)brace
DECL|function|mk_fsid_v1
r_static
r_inline
r_void
id|mk_fsid_v1
c_func
(paren
id|u32
op_star
id|fsidv
comma
id|u32
id|fsid
)paren
(brace
id|fsidv
(braket
l_int|0
)braket
op_assign
id|fsid
suffix:semicolon
)brace
multiline_comment|/*&n; * Shorthand for dprintk()&squot;s&n; */
DECL|function|SVCFH_fmt
r_inline
r_static
r_char
op_star
id|SVCFH_fmt
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_struct
id|knfsd_fh
op_star
id|fh
op_assign
op_amp
id|fhp-&gt;fh_handle
suffix:semicolon
r_static
r_char
id|buf
(braket
l_int|80
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d: %08x %08x %08x %08x %08x %08x&quot;
comma
id|fh-&gt;fh_size
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|0
)braket
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|1
)braket
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|2
)braket
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|3
)braket
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|4
)braket
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/*&n; * Function prototypes&n; */
id|u32
id|fh_verify
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|fh_compose
c_func
(paren
r_struct
id|svc_fh
op_star
comma
r_struct
id|svc_export
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|svc_fh
op_star
)paren
suffix:semicolon
r_int
id|fh_update
c_func
(paren
r_struct
id|svc_fh
op_star
)paren
suffix:semicolon
r_void
id|fh_put
c_func
(paren
r_struct
id|svc_fh
op_star
)paren
suffix:semicolon
r_static
id|__inline__
r_struct
id|svc_fh
op_star
DECL|function|fh_copy
id|fh_copy
c_func
(paren
r_struct
id|svc_fh
op_star
id|dst
comma
r_struct
id|svc_fh
op_star
id|src
)paren
(brace
r_if
c_cond
(paren
id|src-&gt;fh_dentry
op_logical_or
id|src-&gt;fh_locked
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|src-&gt;fh_dentry
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_copy: copying %s/%s, already verified!&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
)brace
op_star
id|dst
op_assign
op_star
id|src
suffix:semicolon
r_return
id|dst
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|fh_dup2
id|fh_dup2
c_func
(paren
r_struct
id|svc_fh
op_star
id|dst
comma
r_struct
id|svc_fh
op_star
id|src
)paren
(brace
id|fh_put
c_func
(paren
id|dst
)paren
suffix:semicolon
id|dget
c_func
(paren
id|src-&gt;fh_dentry
)paren
suffix:semicolon
op_star
id|dst
op_assign
op_star
id|src
suffix:semicolon
)brace
r_static
id|__inline__
r_struct
id|svc_fh
op_star
DECL|function|fh_init
id|fh_init
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
comma
r_int
id|maxsize
)paren
(brace
id|memset
c_func
(paren
id|fhp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|fhp
)paren
)paren
suffix:semicolon
id|fhp-&gt;fh_maxsize
op_assign
id|maxsize
suffix:semicolon
r_return
id|fhp
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NFSD_V3
multiline_comment|/*&n; * Fill in the pre_op attr for the wcc data&n; */
r_static
r_inline
r_void
DECL|function|fill_pre_wcc
id|fill_pre_wcc
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|inode
op_assign
id|fhp-&gt;fh_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fhp-&gt;fh_pre_saved
)paren
(brace
id|fhp-&gt;fh_pre_mtime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
id|fhp-&gt;fh_pre_ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
id|fhp-&gt;fh_pre_size
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|fhp-&gt;fh_pre_saved
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Fill in the post_op attr for the wcc data&n; */
r_static
r_inline
r_void
DECL|function|fill_post_wcc
id|fill_post_wcc
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|fhp-&gt;fh_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|fhp-&gt;fh_post_saved
)paren
id|printk
c_func
(paren
l_string|&quot;nfsd: inode locked twice during operation.&bslash;n&quot;
)paren
suffix:semicolon
id|fhp-&gt;fh_post_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|fhp-&gt;fh_post_nlink
op_assign
id|inode-&gt;i_nlink
suffix:semicolon
id|fhp-&gt;fh_post_uid
op_assign
id|inode-&gt;i_uid
suffix:semicolon
id|fhp-&gt;fh_post_gid
op_assign
id|inode-&gt;i_gid
suffix:semicolon
id|fhp-&gt;fh_post_size
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_blksize
)paren
(brace
id|fhp-&gt;fh_post_blksize
op_assign
id|inode-&gt;i_blksize
suffix:semicolon
id|fhp-&gt;fh_post_blocks
op_assign
id|inode-&gt;i_blocks
suffix:semicolon
)brace
r_else
(brace
id|fhp-&gt;fh_post_blksize
op_assign
id|BLOCK_SIZE
suffix:semicolon
multiline_comment|/* how much do we care for accuracy with MinixFS? */
id|fhp-&gt;fh_post_blocks
op_assign
(paren
id|inode-&gt;i_size
op_plus
l_int|511
)paren
op_rshift
l_int|9
suffix:semicolon
)brace
id|fhp-&gt;fh_post_rdev
(braket
l_int|0
)braket
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|imajor
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
id|fhp-&gt;fh_post_rdev
(braket
l_int|1
)braket
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|iminor
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
id|fhp-&gt;fh_post_atime
op_assign
id|inode-&gt;i_atime
suffix:semicolon
id|fhp-&gt;fh_post_mtime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
id|fhp-&gt;fh_post_ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
id|fhp-&gt;fh_post_saved
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#else
DECL|macro|fill_pre_wcc
mdefine_line|#define&t;fill_pre_wcc(ignored)
DECL|macro|fill_post_wcc
mdefine_line|#define fill_post_wcc(notused)
macro_line|#endif /* CONFIG_NFSD_V3 */
multiline_comment|/*&n; * Lock a file handle/inode&n; * NOTE: both fh_lock and fh_unlock are done &quot;by hand&quot; in&n; * vfs.c:nfsd_rename as it needs to grab 2 i_sem&squot;s at once&n; * so, any changes here should be reflected there.&n; */
r_static
r_inline
r_void
DECL|function|fh_lock
id|fh_lock
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|fhp-&gt;fh_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|dfprintk
c_func
(paren
id|FILEOP
comma
l_string|&quot;nfsd: fh_lock(%s) locked = %d&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
id|fhp
)paren
comma
id|fhp-&gt;fh_locked
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fhp-&gt;fh_dentry
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_lock: fh not verified!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fhp-&gt;fh_locked
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;fh_lock: %s/%s already locked!&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|fill_pre_wcc
c_func
(paren
id|fhp
)paren
suffix:semicolon
id|fhp-&gt;fh_locked
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Unlock a file handle/inode&n; */
r_static
r_inline
r_void
DECL|function|fh_unlock
id|fh_unlock
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fhp-&gt;fh_dentry
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_unlock: fh not verified!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fhp-&gt;fh_locked
)paren
(brace
id|fill_post_wcc
c_func
(paren
id|fhp
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|fhp-&gt;fh_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|fhp-&gt;fh_locked
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_NFSD_FH_H */
eof
