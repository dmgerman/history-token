multiline_comment|/*&n; *  smb_fs.h&n; *&n; *  Copyright (C) 1995 by Paal-Kr. Engstad and Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_SMB_FS_H
DECL|macro|_LINUX_SMB_FS_H
mdefine_line|#define _LINUX_SMB_FS_H
macro_line|#include &lt;linux/smb.h&gt;
multiline_comment|/*&n; * ioctl commands&n; */
DECL|macro|SMB_IOC_GETMOUNTUID
mdefine_line|#define&t;SMB_IOC_GETMOUNTUID&t;&t;_IOR(&squot;u&squot;, 1, __kernel_old_uid_t)
DECL|macro|SMB_IOC_NEWCONN
mdefine_line|#define SMB_IOC_NEWCONN                 _IOW(&squot;u&squot;, 2, struct smb_conn_opt)
multiline_comment|/* __kernel_uid_t can never change, so we have to use __kernel_uid32_t */
DECL|macro|SMB_IOC_GETMOUNTUID32
mdefine_line|#define&t;SMB_IOC_GETMOUNTUID32&t;&t;_IOR(&squot;u&squot;, 3, __kernel_uid32_t)
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/smb_mount.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
multiline_comment|/* macro names are short for word, double-word, long value (?) */
DECL|macro|WVAL
mdefine_line|#define WVAL(buf,pos) &bslash;&n;&t;(le16_to_cpu(get_unaligned((u16 *)((u8 *)(buf) + (pos)))))
DECL|macro|DVAL
mdefine_line|#define DVAL(buf,pos) &bslash;&n;&t;(le32_to_cpu(get_unaligned((u32 *)((u8 *)(buf) + (pos)))))
DECL|macro|LVAL
mdefine_line|#define LVAL(buf,pos) &bslash;&n;&t;(le64_to_cpu(get_unaligned((u64 *)((u8 *)(buf) + (pos)))))
DECL|macro|WSET
mdefine_line|#define WSET(buf,pos,val) &bslash;&n;&t;put_unaligned(cpu_to_le16((u16)(val)), (u16 *)((u8 *)(buf) + (pos)))
DECL|macro|DSET
mdefine_line|#define DSET(buf,pos,val) &bslash;&n;&t;put_unaligned(cpu_to_le32((u32)(val)), (u32 *)((u8 *)(buf) + (pos)))
DECL|macro|LSET
mdefine_line|#define LSET(buf,pos,val) &bslash;&n;&t;put_unaligned(cpu_to_le64((u64)(val)), (u64 *)((u8 *)(buf) + (pos)))
multiline_comment|/* where to find the base of the SMB packet proper */
DECL|macro|smb_base
mdefine_line|#define smb_base(buf) ((u8 *)(((u8 *)(buf))+4))
macro_line|#ifdef DEBUG_SMB_MALLOC
macro_line|#include &lt;linux/slab.h&gt;
r_extern
r_int
id|smb_malloced
suffix:semicolon
r_extern
r_int
id|smb_current_vmalloced
suffix:semicolon
r_extern
r_int
id|smb_current_kmalloced
suffix:semicolon
r_static
r_inline
r_void
op_star
DECL|function|smb_vmalloc
id|smb_vmalloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
id|smb_malloced
op_add_assign
l_int|1
suffix:semicolon
id|smb_current_vmalloced
op_add_assign
l_int|1
suffix:semicolon
r_return
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|smb_vfree
id|smb_vfree
c_func
(paren
r_void
op_star
id|obj
)paren
(brace
id|smb_current_vmalloced
op_sub_assign
l_int|1
suffix:semicolon
id|vfree
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
op_star
DECL|function|smb_kmalloc
id|smb_kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
(brace
id|smb_malloced
op_add_assign
l_int|1
suffix:semicolon
id|smb_current_kmalloced
op_add_assign
l_int|1
suffix:semicolon
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|smb_kfree
id|smb_kfree
c_func
(paren
r_void
op_star
id|obj
)paren
(brace
id|smb_current_kmalloced
op_sub_assign
l_int|1
suffix:semicolon
id|kfree
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
macro_line|#else /* DEBUG_SMB_MALLOC */
DECL|macro|smb_kmalloc
mdefine_line|#define smb_kmalloc(s,p)&t;kmalloc(s,p)
DECL|macro|smb_kfree
mdefine_line|#define smb_kfree(o)&t;&t;kfree(o)
DECL|macro|smb_vmalloc
mdefine_line|#define smb_vmalloc(s)&t;&t;vmalloc(s)
DECL|macro|smb_vfree
mdefine_line|#define smb_vfree(o)&t;&t;vfree(o)
macro_line|#endif /* DEBUG_SMB_MALLOC */
multiline_comment|/*&n; * Flags for the in-memory inode&n; */
DECL|macro|SMB_F_LOCALWRITE
mdefine_line|#define SMB_F_LOCALWRITE&t;0x02&t;/* file modified locally */
multiline_comment|/* NT1 protocol capability bits */
DECL|macro|SMB_CAP_RAW_MODE
mdefine_line|#define SMB_CAP_RAW_MODE         0x0001
DECL|macro|SMB_CAP_MPX_MODE
mdefine_line|#define SMB_CAP_MPX_MODE         0x0002
DECL|macro|SMB_CAP_UNICODE
mdefine_line|#define SMB_CAP_UNICODE          0x0004
DECL|macro|SMB_CAP_LARGE_FILES
mdefine_line|#define SMB_CAP_LARGE_FILES      0x0008
DECL|macro|SMB_CAP_NT_SMBS
mdefine_line|#define SMB_CAP_NT_SMBS          0x0010
DECL|macro|SMB_CAP_RPC_REMOTE_APIS
mdefine_line|#define SMB_CAP_RPC_REMOTE_APIS  0x0020
DECL|macro|SMB_CAP_STATUS32
mdefine_line|#define SMB_CAP_STATUS32         0x0040
DECL|macro|SMB_CAP_LEVEL_II_OPLOCKS
mdefine_line|#define SMB_CAP_LEVEL_II_OPLOCKS 0x0080
DECL|macro|SMB_CAP_LOCK_AND_READ
mdefine_line|#define SMB_CAP_LOCK_AND_READ    0x0100
DECL|macro|SMB_CAP_NT_FIND
mdefine_line|#define SMB_CAP_NT_FIND          0x0200
DECL|macro|SMB_CAP_DFS
mdefine_line|#define SMB_CAP_DFS              0x1000
DECL|macro|SMB_CAP_LARGE_READX
mdefine_line|#define SMB_CAP_LARGE_READX      0x4000
multiline_comment|/*&n; * This is the time we allow an inode, dentry or dir cache to live. It is bad&n; * for performance to have shorter ttl on an inode than on the cache. It can&n; * cause refresh on each inode for a dir listing ... one-by-one&n; */
DECL|macro|SMB_MAX_AGE
mdefine_line|#define SMB_MAX_AGE(server) (((server)-&gt;mnt-&gt;ttl * HZ) / 1000)
r_static
r_inline
r_void
DECL|function|smb_age_dentry
id|smb_age_dentry
c_func
(paren
r_struct
id|smb_sb_info
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
id|SMB_MAX_AGE
c_func
(paren
id|server
)paren
suffix:semicolon
)brace
DECL|struct|smb_cache_head
r_struct
id|smb_cache_head
(brace
DECL|member|mtime
id|time_t
id|mtime
suffix:semicolon
multiline_comment|/* unused */
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
DECL|macro|SMB_DIRCACHE_SIZE
mdefine_line|#define SMB_DIRCACHE_SIZE&t;((int)(PAGE_CACHE_SIZE/sizeof(struct dentry *)))
DECL|union|smb_dir_cache
r_union
id|smb_dir_cache
(brace
DECL|member|head
r_struct
id|smb_cache_head
id|head
suffix:semicolon
DECL|member|dentry
r_struct
id|dentry
op_star
id|dentry
(braket
id|SMB_DIRCACHE_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SMB_FIRSTCACHE_SIZE
mdefine_line|#define SMB_FIRSTCACHE_SIZE&t;((int)((SMB_DIRCACHE_SIZE * &bslash;&n;&t;sizeof(struct dentry *) - sizeof(struct smb_cache_head)) / &bslash;&n;&t;sizeof(struct dentry *)))
DECL|macro|SMB_DIRCACHE_START
mdefine_line|#define SMB_DIRCACHE_START      (SMB_DIRCACHE_SIZE - SMB_FIRSTCACHE_SIZE)
DECL|struct|smb_cache_control
r_struct
id|smb_cache_control
(brace
DECL|member|head
r_struct
id|smb_cache_head
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
id|smb_dir_cache
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
r_static
r_inline
r_int
DECL|function|smb_is_open
id|smb_is_open
c_func
(paren
r_struct
id|inode
op_star
id|i
)paren
(brace
r_return
(paren
id|i-&gt;u.smbfs_i.open
op_eq
id|server_from_inode
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|generation
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SMB_FS_H */
eof
