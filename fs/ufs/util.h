multiline_comment|/*&n; *  linux/fs/ufs/util.h&n; *&n; * Copyright (C) 1998 &n; * Daniel Pirkl &lt;daniel.pirkl@email.cz&gt;&n; * Charles University, Faculty of Mathematics and Physics&n; */
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;swab.h&quot;
multiline_comment|/*&n; * some useful macros&n; */
DECL|macro|in_range
mdefine_line|#define in_range(b,first,len)&t;((b)&gt;=(first)&amp;&amp;(b)&lt;(first)+(len))
multiline_comment|/*&n; * macros used for retyping&n; */
DECL|macro|UCPI_UBH
mdefine_line|#define UCPI_UBH ((struct ufs_buffer_head *)ucpi)
DECL|macro|USPI_UBH
mdefine_line|#define USPI_UBH ((struct ufs_buffer_head *)uspi)
multiline_comment|/*&n; * macros used for accessing structures&n; */
r_static
r_inline
id|s32
DECL|function|ufs_get_fs_state
id|ufs_get_fs_state
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_super_block_first
op_star
id|usb1
comma
r_struct
id|ufs_super_block_third
op_star
id|usb3
)paren
(brace
r_switch
c_cond
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_ST_MASK
)paren
(brace
r_case
id|UFS_ST_SUN
suffix:colon
r_return
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|usb3-&gt;fs_u2.fs_sun.fs_state
)paren
suffix:semicolon
r_case
id|UFS_ST_SUNx86
suffix:colon
r_return
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|usb1-&gt;fs_u1.fs_sunx86.fs_state
)paren
suffix:semicolon
r_case
id|UFS_ST_44BSD
suffix:colon
r_default
suffix:colon
r_return
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|usb3-&gt;fs_u2.fs_44.fs_state
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|ufs_set_fs_state
id|ufs_set_fs_state
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_super_block_first
op_star
id|usb1
comma
r_struct
id|ufs_super_block_third
op_star
id|usb3
comma
id|s32
id|value
)paren
(brace
r_switch
c_cond
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_ST_MASK
)paren
(brace
r_case
id|UFS_ST_SUN
suffix:colon
id|usb3-&gt;fs_u2.fs_sun.fs_state
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UFS_ST_SUNx86
suffix:colon
id|usb1-&gt;fs_u1.fs_sunx86.fs_state
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UFS_ST_44BSD
suffix:colon
id|usb3-&gt;fs_u2.fs_44.fs_state
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_inline
id|u32
DECL|function|ufs_get_fs_npsect
id|ufs_get_fs_npsect
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_super_block_first
op_star
id|usb1
comma
r_struct
id|ufs_super_block_third
op_star
id|usb3
)paren
(brace
r_if
c_cond
(paren
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_ST_MASK
)paren
op_eq
id|UFS_ST_SUNx86
)paren
r_return
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|usb3-&gt;fs_u2.fs_sunx86.fs_npsect
)paren
suffix:semicolon
r_else
r_return
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|usb1-&gt;fs_u1.fs_sun.fs_npsect
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u64
DECL|function|ufs_get_fs_qbmask
id|ufs_get_fs_qbmask
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_super_block_third
op_star
id|usb3
)paren
(brace
id|__fs64
id|tmp
suffix:semicolon
r_switch
c_cond
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_ST_MASK
)paren
(brace
r_case
id|UFS_ST_SUN
suffix:colon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|0
)braket
op_assign
id|usb3-&gt;fs_u2.fs_sun.fs_qbmask
(braket
l_int|0
)braket
suffix:semicolon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|1
)braket
op_assign
id|usb3-&gt;fs_u2.fs_sun.fs_qbmask
(braket
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UFS_ST_SUNx86
suffix:colon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|0
)braket
op_assign
id|usb3-&gt;fs_u2.fs_sunx86.fs_qbmask
(braket
l_int|0
)braket
suffix:semicolon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|1
)braket
op_assign
id|usb3-&gt;fs_u2.fs_sunx86.fs_qbmask
(braket
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UFS_ST_44BSD
suffix:colon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|0
)braket
op_assign
id|usb3-&gt;fs_u2.fs_44.fs_qbmask
(braket
l_int|0
)braket
suffix:semicolon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|1
)braket
op_assign
id|usb3-&gt;fs_u2.fs_44.fs_qbmask
(braket
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|tmp
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u64
DECL|function|ufs_get_fs_qfmask
id|ufs_get_fs_qfmask
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_super_block_third
op_star
id|usb3
)paren
(brace
id|__fs64
id|tmp
suffix:semicolon
r_switch
c_cond
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_ST_MASK
)paren
(brace
r_case
id|UFS_ST_SUN
suffix:colon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|0
)braket
op_assign
id|usb3-&gt;fs_u2.fs_sun.fs_qfmask
(braket
l_int|0
)braket
suffix:semicolon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|1
)braket
op_assign
id|usb3-&gt;fs_u2.fs_sun.fs_qfmask
(braket
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UFS_ST_SUNx86
suffix:colon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|0
)braket
op_assign
id|usb3-&gt;fs_u2.fs_sunx86.fs_qfmask
(braket
l_int|0
)braket
suffix:semicolon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|1
)braket
op_assign
id|usb3-&gt;fs_u2.fs_sunx86.fs_qfmask
(braket
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UFS_ST_44BSD
suffix:colon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|0
)braket
op_assign
id|usb3-&gt;fs_u2.fs_44.fs_qfmask
(braket
l_int|0
)braket
suffix:semicolon
(paren
(paren
id|__fs32
op_star
)paren
op_amp
id|tmp
)paren
(braket
l_int|1
)braket
op_assign
id|usb3-&gt;fs_u2.fs_44.fs_qfmask
(braket
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|fs64_to_cpu
c_func
(paren
id|sb
comma
id|tmp
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u16
DECL|function|ufs_get_de_namlen
id|ufs_get_de_namlen
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_dir_entry
op_star
id|de
)paren
(brace
r_if
c_cond
(paren
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_DE_MASK
)paren
op_eq
id|UFS_DE_OLD
)paren
r_return
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|de-&gt;d_u.d_namlen
)paren
suffix:semicolon
r_else
r_return
id|de-&gt;d_u.d_44.d_namlen
suffix:semicolon
multiline_comment|/* XXX this seems wrong */
)brace
r_static
r_inline
r_void
DECL|function|ufs_set_de_namlen
id|ufs_set_de_namlen
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_dir_entry
op_star
id|de
comma
id|u16
id|value
)paren
(brace
r_if
c_cond
(paren
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_DE_MASK
)paren
op_eq
id|UFS_DE_OLD
)paren
id|de-&gt;d_u.d_namlen
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|value
)paren
suffix:semicolon
r_else
id|de-&gt;d_u.d_44.d_namlen
op_assign
id|value
suffix:semicolon
multiline_comment|/* XXX this seems wrong */
)brace
r_static
r_inline
r_void
DECL|function|ufs_set_de_type
id|ufs_set_de_type
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_dir_entry
op_star
id|de
comma
r_int
id|mode
)paren
(brace
r_if
c_cond
(paren
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_DE_MASK
)paren
op_ne
id|UFS_DE_44BSD
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * TODO turn this into a table lookup&n;&t; */
r_switch
c_cond
(paren
id|mode
op_amp
id|S_IFMT
)paren
(brace
r_case
id|S_IFSOCK
suffix:colon
id|de-&gt;d_u.d_44.d_type
op_assign
id|DT_SOCK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFLNK
suffix:colon
id|de-&gt;d_u.d_44.d_type
op_assign
id|DT_LNK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFREG
suffix:colon
id|de-&gt;d_u.d_44.d_type
op_assign
id|DT_REG
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFBLK
suffix:colon
id|de-&gt;d_u.d_44.d_type
op_assign
id|DT_BLK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFDIR
suffix:colon
id|de-&gt;d_u.d_44.d_type
op_assign
id|DT_DIR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFCHR
suffix:colon
id|de-&gt;d_u.d_44.d_type
op_assign
id|DT_CHR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFIFO
suffix:colon
id|de-&gt;d_u.d_44.d_type
op_assign
id|DT_FIFO
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|de-&gt;d_u.d_44.d_type
op_assign
id|DT_UNKNOWN
suffix:semicolon
)brace
)brace
r_static
r_inline
id|u32
DECL|function|ufs_get_inode_uid
id|ufs_get_inode_uid
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_inode
op_star
id|inode
)paren
(brace
r_switch
c_cond
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_UID_MASK
)paren
(brace
r_case
id|UFS_UID_EFT
suffix:colon
r_return
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;ui_u3.ui_sun.ui_uid
)paren
suffix:semicolon
r_case
id|UFS_UID_44BSD
suffix:colon
r_return
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;ui_u3.ui_44.ui_uid
)paren
suffix:semicolon
r_default
suffix:colon
r_return
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;ui_u1.oldids.ui_suid
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|ufs_set_inode_uid
id|ufs_set_inode_uid
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_inode
op_star
id|inode
comma
id|u32
id|value
)paren
(brace
r_switch
c_cond
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_UID_MASK
)paren
(brace
r_case
id|UFS_UID_EFT
suffix:colon
id|inode-&gt;ui_u3.ui_sun.ui_uid
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UFS_UID_44BSD
suffix:colon
id|inode-&gt;ui_u3.ui_44.ui_uid
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|inode-&gt;ui_u1.oldids.ui_suid
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
DECL|function|ufs_get_inode_gid
id|ufs_get_inode_gid
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_inode
op_star
id|inode
)paren
(brace
r_switch
c_cond
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_UID_MASK
)paren
(brace
r_case
id|UFS_UID_EFT
suffix:colon
r_return
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;ui_u3.ui_sun.ui_gid
)paren
suffix:semicolon
r_case
id|UFS_UID_44BSD
suffix:colon
r_return
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;ui_u3.ui_44.ui_gid
)paren
suffix:semicolon
r_default
suffix:colon
r_return
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|inode-&gt;ui_u1.oldids.ui_sgid
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|ufs_set_inode_gid
id|ufs_set_inode_gid
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_inode
op_star
id|inode
comma
id|u32
id|value
)paren
(brace
r_switch
c_cond
(paren
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_flags
op_amp
id|UFS_UID_MASK
)paren
(brace
r_case
id|UFS_UID_EFT
suffix:colon
id|inode-&gt;ui_u3.ui_sun.ui_gid
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UFS_UID_44BSD
suffix:colon
id|inode-&gt;ui_u3.ui_44.ui_gid
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|inode-&gt;ui_u1.oldids.ui_sgid
op_assign
id|cpu_to_fs16
c_func
(paren
id|sb
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These functions manipulate ufs buffers&n; */
DECL|macro|ubh_bread
mdefine_line|#define ubh_bread(sb,fragment,size) _ubh_bread_(uspi,sb,fragment,size)  
r_extern
r_struct
id|ufs_buffer_head
op_star
id|_ubh_bread_
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
comma
r_struct
id|super_block
op_star
comma
id|u64
comma
id|u64
)paren
suffix:semicolon
r_extern
r_struct
id|ufs_buffer_head
op_star
id|ubh_bread_uspi
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
comma
r_struct
id|super_block
op_star
comma
id|u64
comma
id|u64
)paren
suffix:semicolon
r_extern
r_void
id|ubh_brelse
(paren
r_struct
id|ufs_buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ubh_brelse_uspi
(paren
r_struct
id|ufs_sb_private_info
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ubh_mark_buffer_dirty
(paren
r_struct
id|ufs_buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ubh_mark_buffer_uptodate
(paren
r_struct
id|ufs_buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ubh_ll_rw_block
(paren
r_int
comma
r_int
comma
r_struct
id|ufs_buffer_head
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ubh_wait_on_buffer
(paren
r_struct
id|ufs_buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ubh_max_bcount
(paren
r_struct
id|ufs_buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ubh_bforget
(paren
r_struct
id|ufs_buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ubh_buffer_dirty
(paren
r_struct
id|ufs_buffer_head
op_star
)paren
suffix:semicolon
DECL|macro|ubh_ubhcpymem
mdefine_line|#define ubh_ubhcpymem(mem,ubh,size) _ubh_ubhcpymem_(uspi,mem,ubh,size)
r_extern
r_void
id|_ubh_ubhcpymem_
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
comma
r_int
r_char
op_star
comma
r_struct
id|ufs_buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|ubh_memcpyubh
mdefine_line|#define ubh_memcpyubh(ubh,mem,size) _ubh_memcpyubh_(uspi,ubh,mem,size)
r_extern
r_void
id|_ubh_memcpyubh_
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
comma
r_struct
id|ufs_buffer_head
op_star
comma
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * macros to get important structures from ufs_buffer_head&n; */
DECL|macro|ubh_get_usb_first
mdefine_line|#define ubh_get_usb_first(ubh) &bslash;&n;&t;((struct ufs_super_block_first *)((ubh)-&gt;bh[0]-&gt;b_data))
DECL|macro|ubh_get_usb_second
mdefine_line|#define ubh_get_usb_second(ubh) &bslash;&n;&t;((struct ufs_super_block_second *)(ubh)-&gt; &bslash;&n;&t;bh[UFS_SECTOR_SIZE &gt;&gt; uspi-&gt;s_fshift]-&gt;b_data + (UFS_SECTOR_SIZE &amp; ~uspi-&gt;s_fmask))
DECL|macro|ubh_get_usb_third
mdefine_line|#define ubh_get_usb_third(ubh) &bslash;&n;&t;((struct ufs_super_block_third *)((ubh)-&gt; &bslash;&n;&t;bh[UFS_SECTOR_SIZE*2 &gt;&gt; uspi-&gt;s_fshift]-&gt;b_data + (UFS_SECTOR_SIZE*2 &amp; ~uspi-&gt;s_fmask)))
DECL|macro|ubh_get_ucg
mdefine_line|#define ubh_get_ucg(ubh) &bslash;&n;&t;((struct ufs_cylinder_group *)((ubh)-&gt;bh[0]-&gt;b_data))
multiline_comment|/*&n; * Extract byte from ufs_buffer_head&n; * Extract the bits for a block from a map inside ufs_buffer_head&n; */
DECL|macro|ubh_get_addr8
mdefine_line|#define ubh_get_addr8(ubh,begin) &bslash;&n;&t;((u8*)(ubh)-&gt;bh[(begin) &gt;&gt; uspi-&gt;s_fshift]-&gt;b_data + &bslash;&n;&t;((begin) &amp; ~uspi-&gt;s_fmask))
DECL|macro|ubh_get_addr16
mdefine_line|#define ubh_get_addr16(ubh,begin) &bslash;&n;&t;(((__fs16*)((ubh)-&gt;bh[(begin) &gt;&gt; (uspi-&gt;s_fshift-1)]-&gt;b_data)) + &bslash;&n;&t;((begin) &amp; (uspi-&gt;fsize&gt;&gt;1) - 1)))
DECL|macro|ubh_get_addr32
mdefine_line|#define ubh_get_addr32(ubh,begin) &bslash;&n;&t;(((__fs32*)((ubh)-&gt;bh[(begin) &gt;&gt; (uspi-&gt;s_fshift-2)]-&gt;b_data)) + &bslash;&n;&t;((begin) &amp; ((uspi-&gt;s_fsize&gt;&gt;2) - 1)))
DECL|macro|ubh_get_addr
mdefine_line|#define ubh_get_addr ubh_get_addr8
DECL|macro|ubh_blkmap
mdefine_line|#define ubh_blkmap(ubh,begin,bit) &bslash;&n;&t;((*ubh_get_addr(ubh, (begin) + ((bit) &gt;&gt; 3)) &gt;&gt; ((bit) &amp; 7)) &amp; (0xff &gt;&gt; (UFS_MAXFRAG - uspi-&gt;s_fpb)))
multiline_comment|/*&n; * Macros for access to superblock array structures&n; */
DECL|macro|ubh_postbl
mdefine_line|#define ubh_postbl(ubh,cylno,i) &bslash;&n;&t;((uspi-&gt;s_postblformat != UFS_DYNAMICPOSTBLFMT) &bslash;&n;&t;? (*(__s16*)(ubh_get_addr(ubh, &bslash;&n;&t;(unsigned)(&amp;((struct ufs_super_block *)0)-&gt;fs_opostbl) &bslash;&n;&t;+ (((cylno) * 16 + (i)) &lt;&lt; 1) ) )) &bslash;&n;&t;: (*(__s16*)(ubh_get_addr(ubh, &bslash;&n;&t;uspi-&gt;s_postbloff + (((cylno) * uspi-&gt;s_nrpos + (i)) &lt;&lt; 1) ))))
DECL|macro|ubh_rotbl
mdefine_line|#define ubh_rotbl(ubh,i) &bslash;&n;&t;((uspi-&gt;s_postblformat != UFS_DYNAMICPOSTBLFMT) &bslash;&n;&t;? (*(__u8*)(ubh_get_addr(ubh, &bslash;&n;&t;(unsigned)(&amp;((struct ufs_super_block *)0)-&gt;fs_space) + (i)))) &bslash;&n;&t;: (*(__u8*)(ubh_get_addr(ubh, uspi-&gt;s_rotbloff + (i)))))
multiline_comment|/*&n; * Determine the number of available frags given a&n; * percentage to hold in reserve.&n; */
DECL|macro|ufs_freespace
mdefine_line|#define ufs_freespace(usb, percentreserved) &bslash;&n;&t;(ufs_blkstofrags(fs32_to_cpu(sb, (usb)-&gt;fs_cstotal.cs_nbfree)) + &bslash;&n;&t;fs32_to_cpu(sb, (usb)-&gt;fs_cstotal.cs_nffree) - (uspi-&gt;s_dsize * (percentreserved) / 100))
multiline_comment|/*&n; * Macros to access cylinder group array structures&n; */
DECL|macro|ubh_cg_blktot
mdefine_line|#define ubh_cg_blktot(ucpi,cylno) &bslash;&n;&t;(*((__fs32*)ubh_get_addr(UCPI_UBH, (ucpi)-&gt;c_btotoff + ((cylno) &lt;&lt; 2))))
DECL|macro|ubh_cg_blks
mdefine_line|#define ubh_cg_blks(ucpi,cylno,rpos) &bslash;&n;&t;(*((__fs16*)ubh_get_addr(UCPI_UBH, &bslash;&n;&t;(ucpi)-&gt;c_boff + (((cylno) * uspi-&gt;s_nrpos + (rpos)) &lt;&lt; 1 ))))
multiline_comment|/*&n; * Bitmap operations&n; * These functions work like classical bitmap operations.&n; * The difference is that we don&squot;t have the whole bitmap&n; * in one contiguous chunk of memory, but in several buffers.&n; * The parameters of each function are super_block, ufs_buffer_head and&n; * position of the beginning of the bitmap.&n; */
DECL|macro|ubh_setbit
mdefine_line|#define ubh_setbit(ubh,begin,bit) &bslash;&n;&t;(*ubh_get_addr(ubh, (begin) + ((bit) &gt;&gt; 3)) |= (1 &lt;&lt; ((bit) &amp; 7)))
DECL|macro|ubh_clrbit
mdefine_line|#define ubh_clrbit(ubh,begin,bit) &bslash;&n;&t;(*ubh_get_addr (ubh, (begin) + ((bit) &gt;&gt; 3)) &amp;= ~(1 &lt;&lt; ((bit) &amp; 7)))
DECL|macro|ubh_isset
mdefine_line|#define ubh_isset(ubh,begin,bit) &bslash;&n;&t;(*ubh_get_addr (ubh, (begin) + ((bit) &gt;&gt; 3)) &amp; (1 &lt;&lt; ((bit) &amp; 7)))
DECL|macro|ubh_isclr
mdefine_line|#define ubh_isclr(ubh,begin,bit) (!ubh_isset(ubh,begin,bit))
DECL|macro|ubh_find_first_zero_bit
mdefine_line|#define ubh_find_first_zero_bit(ubh,begin,size) _ubh_find_next_zero_bit_(uspi,ubh,begin,size,0)
DECL|macro|ubh_find_next_zero_bit
mdefine_line|#define ubh_find_next_zero_bit(ubh,begin,size,offset) _ubh_find_next_zero_bit_(uspi,ubh,begin,size,offset)
DECL|function|_ubh_find_next_zero_bit_
r_static
r_inline
r_int
id|_ubh_find_next_zero_bit_
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
id|uspi
comma
r_struct
id|ufs_buffer_head
op_star
id|ubh
comma
r_int
id|begin
comma
r_int
id|size
comma
r_int
id|offset
)paren
(brace
r_int
id|base
comma
id|count
comma
id|pos
suffix:semicolon
id|size
op_sub_assign
id|offset
suffix:semicolon
id|begin
op_lshift_assign
l_int|3
suffix:semicolon
id|offset
op_add_assign
id|begin
suffix:semicolon
id|base
op_assign
id|offset
op_rshift
id|uspi-&gt;s_bpfshift
suffix:semicolon
id|offset
op_and_assign
id|uspi-&gt;s_bpfmask
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|count
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|size
op_plus
id|offset
comma
id|uspi-&gt;s_bpf
)paren
suffix:semicolon
id|size
op_sub_assign
id|count
op_minus
id|offset
suffix:semicolon
id|pos
op_assign
id|ext2_find_next_zero_bit
(paren
id|ubh-&gt;bh
(braket
id|base
)braket
op_member_access_from_pointer
id|b_data
comma
id|count
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|count
op_logical_or
op_logical_neg
id|size
)paren
r_break
suffix:semicolon
id|base
op_increment
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
r_return
(paren
id|base
op_lshift
id|uspi-&gt;s_bpfshift
)paren
op_plus
id|pos
op_minus
id|begin
suffix:semicolon
)brace
DECL|function|find_last_zero_bit
r_static
r_inline
r_int
id|find_last_zero_bit
(paren
r_int
r_char
op_star
id|bitmap
comma
r_int
id|size
comma
r_int
id|offset
)paren
(brace
r_int
id|bit
comma
id|i
suffix:semicolon
r_int
r_char
op_star
id|mapp
suffix:semicolon
r_int
r_char
id|map
suffix:semicolon
id|mapp
op_assign
id|bitmap
op_plus
(paren
id|size
op_rshift
l_int|3
)paren
suffix:semicolon
id|map
op_assign
op_star
id|mapp
op_decrement
suffix:semicolon
id|bit
op_assign
l_int|1
op_lshift
(paren
id|size
op_amp
l_int|7
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|size
suffix:semicolon
id|i
OG
id|offset
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
(paren
id|map
op_amp
id|bit
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_amp
l_int|7
)paren
op_ne
l_int|0
)paren
(brace
id|bit
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|map
op_assign
op_star
id|mapp
op_decrement
suffix:semicolon
id|bit
op_assign
l_int|1
op_lshift
l_int|7
suffix:semicolon
)brace
)brace
r_return
id|i
suffix:semicolon
)brace
DECL|macro|ubh_find_last_zero_bit
mdefine_line|#define ubh_find_last_zero_bit(ubh,begin,size,offset) _ubh_find_last_zero_bit_(uspi,ubh,begin,size,offset)
DECL|function|_ubh_find_last_zero_bit_
r_static
r_inline
r_int
id|_ubh_find_last_zero_bit_
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
id|uspi
comma
r_struct
id|ufs_buffer_head
op_star
id|ubh
comma
r_int
id|begin
comma
r_int
id|start
comma
r_int
id|end
)paren
(brace
r_int
id|base
comma
id|count
comma
id|pos
comma
id|size
suffix:semicolon
id|size
op_assign
id|start
op_minus
id|end
suffix:semicolon
id|begin
op_lshift_assign
l_int|3
suffix:semicolon
id|start
op_add_assign
id|begin
suffix:semicolon
id|base
op_assign
id|start
op_rshift
id|uspi-&gt;s_bpfshift
suffix:semicolon
id|start
op_and_assign
id|uspi-&gt;s_bpfmask
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|count
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|size
op_plus
(paren
id|uspi-&gt;s_bpf
op_minus
id|start
)paren
comma
id|uspi-&gt;s_bpf
)paren
op_minus
(paren
id|uspi-&gt;s_bpf
op_minus
id|start
)paren
suffix:semicolon
id|size
op_sub_assign
id|count
suffix:semicolon
id|pos
op_assign
id|find_last_zero_bit
(paren
id|ubh-&gt;bh
(braket
id|base
)braket
op_member_access_from_pointer
id|b_data
comma
id|start
comma
id|start
op_minus
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|start
op_minus
id|count
op_logical_or
op_logical_neg
id|size
)paren
r_break
suffix:semicolon
id|base
op_decrement
suffix:semicolon
id|start
op_assign
id|uspi-&gt;s_bpf
suffix:semicolon
)brace
r_return
(paren
id|base
op_lshift
id|uspi-&gt;s_bpfshift
)paren
op_plus
id|pos
op_minus
id|begin
suffix:semicolon
)brace
DECL|macro|ubh_isblockclear
mdefine_line|#define ubh_isblockclear(ubh,begin,block) (!_ubh_isblockset_(uspi,ubh,begin,block))
DECL|macro|ubh_isblockset
mdefine_line|#define ubh_isblockset(ubh,begin,block) _ubh_isblockset_(uspi,ubh,begin,block)
DECL|function|_ubh_isblockset_
r_static
r_inline
r_int
id|_ubh_isblockset_
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
id|uspi
comma
r_struct
id|ufs_buffer_head
op_star
id|ubh
comma
r_int
id|begin
comma
r_int
id|block
)paren
(brace
r_switch
c_cond
(paren
id|uspi-&gt;s_fpb
)paren
(brace
r_case
l_int|8
suffix:colon
r_return
(paren
op_star
id|ubh_get_addr
(paren
id|ubh
comma
id|begin
op_plus
id|block
)paren
op_eq
l_int|0xff
)paren
suffix:semicolon
r_case
l_int|4
suffix:colon
r_return
(paren
op_star
id|ubh_get_addr
(paren
id|ubh
comma
id|begin
op_plus
(paren
id|block
op_rshift
l_int|1
)paren
)paren
op_eq
(paren
l_int|0x0f
op_lshift
(paren
(paren
id|block
op_amp
l_int|0x01
)paren
op_lshift
l_int|2
)paren
)paren
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
(paren
op_star
id|ubh_get_addr
(paren
id|ubh
comma
id|begin
op_plus
(paren
id|block
op_rshift
l_int|2
)paren
)paren
op_eq
(paren
l_int|0x03
op_lshift
(paren
(paren
id|block
op_amp
l_int|0x03
)paren
op_lshift
l_int|1
)paren
)paren
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
(paren
op_star
id|ubh_get_addr
(paren
id|ubh
comma
id|begin
op_plus
(paren
id|block
op_rshift
l_int|3
)paren
)paren
op_eq
(paren
l_int|0x01
op_lshift
(paren
id|block
op_amp
l_int|0x07
)paren
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|ubh_clrblock
mdefine_line|#define ubh_clrblock(ubh,begin,block) _ubh_clrblock_(uspi,ubh,begin,block)
DECL|function|_ubh_clrblock_
r_static
r_inline
r_void
id|_ubh_clrblock_
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
id|uspi
comma
r_struct
id|ufs_buffer_head
op_star
id|ubh
comma
r_int
id|begin
comma
r_int
id|block
)paren
(brace
r_switch
c_cond
(paren
id|uspi-&gt;s_fpb
)paren
(brace
r_case
l_int|8
suffix:colon
op_star
id|ubh_get_addr
(paren
id|ubh
comma
id|begin
op_plus
id|block
)paren
op_assign
l_int|0x00
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|ubh_get_addr
(paren
id|ubh
comma
id|begin
op_plus
(paren
id|block
op_rshift
l_int|1
)paren
)paren
op_and_assign
op_complement
(paren
l_int|0x0f
op_lshift
(paren
(paren
id|block
op_amp
l_int|0x01
)paren
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|ubh_get_addr
(paren
id|ubh
comma
id|begin
op_plus
(paren
id|block
op_rshift
l_int|2
)paren
)paren
op_and_assign
op_complement
(paren
l_int|0x03
op_lshift
(paren
(paren
id|block
op_amp
l_int|0x03
)paren
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|1
suffix:colon
op_star
id|ubh_get_addr
(paren
id|ubh
comma
id|begin
op_plus
(paren
id|block
op_rshift
l_int|3
)paren
)paren
op_and_assign
op_complement
(paren
l_int|0x01
op_lshift
(paren
(paren
id|block
op_amp
l_int|0x07
)paren
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|macro|ubh_setblock
mdefine_line|#define ubh_setblock(ubh,begin,block) _ubh_setblock_(uspi,ubh,begin,block)
DECL|function|_ubh_setblock_
r_static
r_inline
r_void
id|_ubh_setblock_
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
id|uspi
comma
r_struct
id|ufs_buffer_head
op_star
id|ubh
comma
r_int
id|begin
comma
r_int
id|block
)paren
(brace
r_switch
c_cond
(paren
id|uspi-&gt;s_fpb
)paren
(brace
r_case
l_int|8
suffix:colon
op_star
id|ubh_get_addr
c_func
(paren
id|ubh
comma
id|begin
op_plus
id|block
)paren
op_assign
l_int|0xff
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|ubh_get_addr
c_func
(paren
id|ubh
comma
id|begin
op_plus
(paren
id|block
op_rshift
l_int|1
)paren
)paren
op_or_assign
(paren
l_int|0x0f
op_lshift
(paren
(paren
id|block
op_amp
l_int|0x01
)paren
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|ubh_get_addr
c_func
(paren
id|ubh
comma
id|begin
op_plus
(paren
id|block
op_rshift
l_int|2
)paren
)paren
op_or_assign
(paren
l_int|0x03
op_lshift
(paren
(paren
id|block
op_amp
l_int|0x03
)paren
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|1
suffix:colon
op_star
id|ubh_get_addr
c_func
(paren
id|ubh
comma
id|begin
op_plus
(paren
id|block
op_rshift
l_int|3
)paren
)paren
op_or_assign
(paren
l_int|0x01
op_lshift
(paren
(paren
id|block
op_amp
l_int|0x07
)paren
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|ufs_fragacct
r_static
r_inline
r_void
id|ufs_fragacct
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|blockmap
comma
id|__fs32
op_star
id|fraglist
comma
r_int
id|cnt
)paren
(brace
r_struct
id|ufs_sb_private_info
op_star
id|uspi
suffix:semicolon
r_int
id|fragsize
comma
id|pos
suffix:semicolon
id|uspi
op_assign
id|UFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_uspi
suffix:semicolon
id|fragsize
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|pos
op_assign
l_int|0
suffix:semicolon
id|pos
OL
id|uspi-&gt;s_fpb
suffix:semicolon
id|pos
op_increment
)paren
(brace
r_if
c_cond
(paren
id|blockmap
op_amp
(paren
l_int|1
op_lshift
id|pos
)paren
)paren
(brace
id|fragsize
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fragsize
OG
l_int|0
)paren
(brace
id|fs32_add
c_func
(paren
id|sb
comma
op_amp
id|fraglist
(braket
id|fragsize
)braket
comma
id|cnt
)paren
suffix:semicolon
id|fragsize
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|fragsize
OG
l_int|0
op_logical_and
id|fragsize
OL
id|uspi-&gt;s_fpb
)paren
id|fs32_add
c_func
(paren
id|sb
comma
op_amp
id|fraglist
(braket
id|fragsize
)braket
comma
id|cnt
)paren
suffix:semicolon
)brace
DECL|macro|ubh_scanc
mdefine_line|#define ubh_scanc(ubh,begin,size,table,mask) _ubh_scanc_(uspi,ubh,begin,size,table,mask)
DECL|function|_ubh_scanc_
r_static
r_inline
r_int
id|_ubh_scanc_
c_func
(paren
r_struct
id|ufs_sb_private_info
op_star
id|uspi
comma
r_struct
id|ufs_buffer_head
op_star
id|ubh
comma
r_int
id|begin
comma
r_int
id|size
comma
r_int
r_char
op_star
id|table
comma
r_int
r_char
id|mask
)paren
(brace
r_int
id|rest
comma
id|offset
suffix:semicolon
r_int
r_char
op_star
id|cp
suffix:semicolon
id|offset
op_assign
id|begin
op_amp
op_complement
id|uspi-&gt;s_fmask
suffix:semicolon
id|begin
op_rshift_assign
id|uspi-&gt;s_fshift
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
(paren
id|offset
op_plus
id|size
)paren
OL
id|uspi-&gt;s_fsize
)paren
id|rest
op_assign
id|size
suffix:semicolon
r_else
id|rest
op_assign
id|uspi-&gt;s_fsize
op_minus
id|offset
suffix:semicolon
id|size
op_sub_assign
id|rest
suffix:semicolon
id|cp
op_assign
id|ubh-&gt;bh
(braket
id|begin
)braket
op_member_access_from_pointer
id|b_data
op_plus
id|offset
suffix:semicolon
r_while
c_loop
(paren
(paren
id|table
(braket
op_star
id|cp
op_increment
)braket
op_amp
id|mask
)paren
op_eq
l_int|0
op_logical_and
op_decrement
id|rest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rest
op_logical_or
op_logical_neg
id|size
)paren
r_break
suffix:semicolon
id|begin
op_increment
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
r_return
(paren
id|size
op_plus
id|rest
)paren
suffix:semicolon
)brace
eof
