multiline_comment|/*&n; *  ncplib_kernel.h&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *  Modified for big endian by J.F. Chadima and David S. Miller&n; *  Modified 1997 Peter Waltenberg, Bill Hawes, David Woodhouse for 2.1 dcache&n; *  Modified 1998, 1999 Wolfram Pienkoss for NLS&n; *  Modified 1999 Wolfram Pienkoss for directory caching&n; *&n; */
macro_line|#ifndef _NCPLIB_H
DECL|macro|_NCPLIB_H
mdefine_line|#define _NCPLIB_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;asm/string.h&gt;
macro_line|#ifdef CONFIG_NCPFS_NLS
macro_line|#include &lt;linux/nls.h&gt;
macro_line|#else
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#endif /* CONFIG_NCPFS_NLS */
macro_line|#include &lt;linux/ncp_fs.h&gt;
DECL|macro|NCP_MIN_SYMLINK_SIZE
mdefine_line|#define NCP_MIN_SYMLINK_SIZE&t;8
DECL|macro|NCP_MAX_SYMLINK_SIZE
mdefine_line|#define NCP_MAX_SYMLINK_SIZE&t;512
DECL|macro|NCP_BLOCK_SHIFT
mdefine_line|#define NCP_BLOCK_SHIFT&t;&t;9
DECL|macro|NCP_BLOCK_SIZE
mdefine_line|#define NCP_BLOCK_SIZE&t;&t;(1 &lt;&lt; (NCP_BLOCK_SHIFT))
r_int
id|ncp_negotiate_buffersize
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|ncp_negotiate_size_and_options
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_int
id|size
comma
r_int
id|options
comma
r_int
op_star
id|ret_size
comma
r_int
op_star
id|ret_options
)paren
suffix:semicolon
r_int
id|ncp_get_volume_info_with_number
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_int
id|n
comma
r_struct
id|ncp_volume_info
op_star
id|target
)paren
suffix:semicolon
r_int
id|ncp_get_directory_info
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
id|__u8
id|dirhandle
comma
r_struct
id|ncp_volume_info
op_star
id|target
)paren
suffix:semicolon
r_int
id|ncp_close_file
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|function|ncp_read_bounce_size
r_static
r_inline
r_int
id|ncp_read_bounce_size
c_func
(paren
id|__u32
id|size
)paren
(brace
r_return
r_sizeof
(paren
r_struct
id|ncp_reply_header
)paren
op_plus
l_int|2
op_plus
l_int|2
op_plus
id|size
op_plus
l_int|8
suffix:semicolon
)brace
suffix:semicolon
r_int
id|ncp_read_bounce
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_const
r_char
op_star
comma
id|__u32
comma
id|__u16
comma
r_char
id|__user
op_star
comma
r_int
op_star
comma
r_void
op_star
id|bounce
comma
id|__u32
id|bouncelen
)paren
suffix:semicolon
r_int
id|ncp_read_kernel
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_const
r_char
op_star
comma
id|__u32
comma
id|__u16
comma
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|ncp_write_kernel
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_const
r_char
op_star
comma
id|__u32
comma
id|__u16
comma
r_const
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|function|ncp_inode_close
r_static
r_inline
r_void
id|ncp_inode_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|opened
)paren
suffix:semicolon
)brace
r_void
id|ncp_extract_file_info
c_func
(paren
r_void
op_star
id|src
comma
r_struct
id|nw_info_struct
op_star
id|target
)paren
suffix:semicolon
r_int
id|ncp_obtain_info
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_struct
id|inode
op_star
comma
r_char
op_star
comma
r_struct
id|nw_info_struct
op_star
id|target
)paren
suffix:semicolon
r_int
id|ncp_obtain_nfs_info
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_struct
id|nw_info_struct
op_star
id|target
)paren
suffix:semicolon
r_int
id|ncp_get_volume_root
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_const
r_char
op_star
id|volname
comma
id|__u32
op_star
id|volume
comma
id|__u32
op_star
id|dirent
comma
id|__u32
op_star
id|dosdirent
)paren
suffix:semicolon
r_int
id|ncp_lookup_volume
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_const
r_char
op_star
comma
r_struct
id|nw_info_struct
op_star
)paren
suffix:semicolon
r_int
id|ncp_modify_file_or_subdir_dos_info
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_struct
id|inode
op_star
comma
id|__u32
comma
r_const
r_struct
id|nw_modify_dos_info
op_star
id|info
)paren
suffix:semicolon
r_int
id|ncp_modify_file_or_subdir_dos_info_path
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
id|path
comma
id|__u32
comma
r_const
r_struct
id|nw_modify_dos_info
op_star
id|info
)paren
suffix:semicolon
r_int
id|ncp_modify_nfs_info
c_func
(paren
r_struct
id|ncp_server
op_star
comma
id|__u8
id|volnum
comma
id|__u32
id|dirent
comma
id|__u32
id|mode
comma
id|__u32
id|rdev
)paren
suffix:semicolon
r_int
id|ncp_del_file_or_subdir2
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_int
id|ncp_del_file_or_subdir
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_struct
id|inode
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_int
id|ncp_open_create_file_or_subdir
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_struct
id|inode
op_star
comma
r_char
op_star
comma
r_int
comma
id|__u32
comma
r_int
comma
r_struct
id|ncp_entry_info
op_star
)paren
suffix:semicolon
r_int
id|ncp_initialize_search
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|nw_search_sequence
op_star
id|target
)paren
suffix:semicolon
r_int
id|ncp_search_for_file_or_subdir
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_struct
id|nw_search_sequence
op_star
id|seq
comma
r_struct
id|nw_info_struct
op_star
id|target
)paren
suffix:semicolon
r_int
id|ncp_search_for_fileset
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_struct
id|nw_search_sequence
op_star
id|seq
comma
r_int
op_star
id|more
comma
r_int
op_star
id|cnt
comma
r_char
op_star
id|buffer
comma
r_int
id|bufsize
comma
r_char
op_star
op_star
id|rbuf
comma
r_int
op_star
id|rsize
)paren
suffix:semicolon
r_int
id|ncp_ren_or_mov_file_or_subdir
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_struct
id|inode
op_star
comma
r_char
op_star
comma
r_struct
id|inode
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_int
id|ncp_LogPhysicalRecord
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_const
r_char
op_star
id|file_id
comma
id|__u8
id|locktype
comma
id|__u32
id|offset
comma
id|__u32
id|length
comma
id|__u16
id|timeout
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NCPFS_IOCTL_LOCKING
r_int
id|ncp_ClearPhysicalRecord
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_const
r_char
op_star
id|file_id
comma
id|__u32
id|offset
comma
id|__u32
id|length
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_NCPFS_IOCTL_LOCKING */
r_int
id|ncp_mount_subdir
c_func
(paren
r_struct
id|ncp_server
op_star
comma
id|__u8
comma
id|__u8
comma
id|__u32
comma
id|__u32
op_star
id|volume
comma
id|__u32
op_star
id|dirent
comma
id|__u32
op_star
id|dosdirent
)paren
suffix:semicolon
r_int
id|ncp_dirhandle_alloc
c_func
(paren
r_struct
id|ncp_server
op_star
comma
id|__u8
id|vol
comma
id|__u32
id|dirent
comma
id|__u8
op_star
id|dirhandle
)paren
suffix:semicolon
r_int
id|ncp_dirhandle_free
c_func
(paren
r_struct
id|ncp_server
op_star
comma
id|__u8
id|dirhandle
)paren
suffix:semicolon
r_int
id|ncp_create_new
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
comma
id|dev_t
id|rdev
comma
r_int
id|attributes
)paren
suffix:semicolon
DECL|function|ncp_is_nfs_extras
r_static
r_inline
r_int
id|ncp_is_nfs_extras
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_int
r_int
id|volnum
)paren
(brace
macro_line|#ifdef CONFIG_NCPFS_NFS_NS
r_return
(paren
id|server-&gt;m.flags
op_amp
id|NCP_MOUNT_NFS_EXTRAS
)paren
op_logical_and
(paren
id|server-&gt;name_space
(braket
id|volnum
)braket
op_eq
id|NW_NS_NFS
)paren
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_NCPFS_NLS
r_int
id|ncp__io2vol
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_int
r_char
op_star
comma
r_int
r_int
op_star
comma
r_const
r_int
r_char
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|ncp__vol2io
c_func
(paren
r_struct
id|ncp_server
op_star
comma
r_int
r_char
op_star
comma
r_int
r_int
op_star
comma
r_const
r_int
r_char
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|NCP_ESC
mdefine_line|#define NCP_ESC&t;&t;&t;&squot;:&squot;
DECL|macro|NCP_IO_TABLE
mdefine_line|#define NCP_IO_TABLE(dentry)&t;(NCP_SERVER((dentry)-&gt;d_inode)-&gt;nls_io)
DECL|macro|ncp_tolower
mdefine_line|#define ncp_tolower(t, c)&t;nls_tolower(t, c)
DECL|macro|ncp_toupper
mdefine_line|#define ncp_toupper(t, c)&t;nls_toupper(t, c)
DECL|macro|ncp_strnicmp
mdefine_line|#define ncp_strnicmp(t, s1, s2, len) &bslash;&n;&t;nls_strnicmp(t, s1, s2, len)
DECL|macro|ncp_io2vol
mdefine_line|#define ncp_io2vol(S,m,i,n,k,U)&t;ncp__io2vol(S,m,i,n,k,U)
DECL|macro|ncp_vol2io
mdefine_line|#define ncp_vol2io(S,m,i,n,k,U)&t;ncp__vol2io(S,m,i,n,k,U)
macro_line|#else
r_int
id|ncp__io2vol
c_func
(paren
r_int
r_char
op_star
comma
r_int
r_int
op_star
comma
r_const
r_int
r_char
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|ncp__vol2io
c_func
(paren
r_int
r_char
op_star
comma
r_int
r_int
op_star
comma
r_const
r_int
r_char
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|NCP_IO_TABLE
mdefine_line|#define NCP_IO_TABLE(dentry)&t;NULL
DECL|macro|ncp_tolower
mdefine_line|#define ncp_tolower(t, c)&t;tolower(c)
DECL|macro|ncp_toupper
mdefine_line|#define ncp_toupper(t, c)&t;toupper(c)
DECL|macro|ncp_io2vol
mdefine_line|#define ncp_io2vol(S,m,i,n,k,U)&t;ncp__io2vol(m,i,n,k,U)
DECL|macro|ncp_vol2io
mdefine_line|#define ncp_vol2io(S,m,i,n,k,U)&t;ncp__vol2io(m,i,n,k,U)
DECL|function|ncp_strnicmp
r_static
r_inline
r_int
id|ncp_strnicmp
c_func
(paren
r_struct
id|nls_table
op_star
id|t
comma
r_const
r_int
r_char
op_star
id|s1
comma
r_const
r_int
r_char
op_star
id|s2
comma
r_int
id|len
)paren
(brace
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|tolower
c_func
(paren
op_star
id|s1
op_increment
)paren
op_ne
id|tolower
c_func
(paren
op_star
id|s2
op_increment
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NCPFS_NLS */
DECL|macro|NCP_GET_AGE
mdefine_line|#define NCP_GET_AGE(dentry)&t;(jiffies - (dentry)-&gt;d_time)
DECL|macro|NCP_MAX_AGE
mdefine_line|#define NCP_MAX_AGE(server)&t;((server)-&gt;dentry_ttl)
DECL|macro|NCP_TEST_AGE
mdefine_line|#define NCP_TEST_AGE(server,dentry)&t;(NCP_GET_AGE(dentry) &lt; NCP_MAX_AGE(server))
r_static
r_inline
r_void
DECL|function|ncp_age_dentry
id|ncp_age_dentry
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|dentry-&gt;d_time
op_assign
id|jiffies
op_minus
id|server-&gt;dentry_ttl
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ncp_new_dentry
id|ncp_new_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|dentry-&gt;d_time
op_assign
id|jiffies
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ncp_renew_dentries
id|ncp_renew_dentries
c_func
(paren
r_struct
id|dentry
op_star
id|parent
)paren
(brace
r_struct
id|ncp_server
op_star
id|server
op_assign
id|NCP_SERVER
c_func
(paren
id|parent-&gt;d_inode
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|next
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|next
op_assign
id|parent-&gt;d_subdirs.next
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
op_amp
id|parent-&gt;d_subdirs
)paren
(brace
id|dentry
op_assign
id|list_entry
c_func
(paren
id|next
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_fsdata
op_eq
l_int|NULL
)paren
id|ncp_age_dentry
c_func
(paren
id|server
comma
id|dentry
)paren
suffix:semicolon
r_else
id|ncp_new_dentry
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ncp_invalidate_dircache_entries
id|ncp_invalidate_dircache_entries
c_func
(paren
r_struct
id|dentry
op_star
id|parent
)paren
(brace
r_struct
id|ncp_server
op_star
id|server
op_assign
id|NCP_SERVER
c_func
(paren
id|parent-&gt;d_inode
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|next
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|next
op_assign
id|parent-&gt;d_subdirs.next
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
op_amp
id|parent-&gt;d_subdirs
)paren
(brace
id|dentry
op_assign
id|list_entry
c_func
(paren
id|next
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
id|dentry-&gt;d_fsdata
op_assign
l_int|NULL
suffix:semicolon
id|ncp_age_dentry
c_func
(paren
id|server
comma
id|dentry
)paren
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
)brace
DECL|struct|ncp_cache_head
r_struct
id|ncp_cache_head
(brace
DECL|member|mtime
id|time_t
id|mtime
suffix:semicolon
DECL|member|time
r_int
r_int
id|time
suffix:semicolon
multiline_comment|/* cache age */
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
multiline_comment|/* last valid fpos in cache */
DECL|member|eof
r_int
id|eof
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NCP_DIRCACHE_SIZE
mdefine_line|#define NCP_DIRCACHE_SIZE&t;((int)(PAGE_CACHE_SIZE/sizeof(struct dentry *)))
DECL|union|ncp_dir_cache
r_union
id|ncp_dir_cache
(brace
DECL|member|head
r_struct
id|ncp_cache_head
id|head
suffix:semicolon
DECL|member|dentry
r_struct
id|dentry
op_star
id|dentry
(braket
id|NCP_DIRCACHE_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NCP_FIRSTCACHE_SIZE
mdefine_line|#define NCP_FIRSTCACHE_SIZE&t;((int)((NCP_DIRCACHE_SIZE * &bslash;&n;&t;sizeof(struct dentry *) - sizeof(struct ncp_cache_head)) / &bslash;&n;&t;sizeof(struct dentry *)))
DECL|macro|NCP_DIRCACHE_START
mdefine_line|#define NCP_DIRCACHE_START&t;(NCP_DIRCACHE_SIZE - NCP_FIRSTCACHE_SIZE)
DECL|struct|ncp_cache_control
r_struct
id|ncp_cache_control
(brace
DECL|member|head
r_struct
id|ncp_cache_head
id|head
suffix:semicolon
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
DECL|member|cache
r_union
id|ncp_dir_cache
op_star
id|cache
suffix:semicolon
DECL|member|fpos
DECL|member|ofs
r_int
r_int
id|fpos
comma
id|ofs
suffix:semicolon
DECL|member|filled
DECL|member|valid
DECL|member|idx
r_int
id|filled
comma
id|valid
comma
id|idx
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _NCPLIB_H */
eof
