multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2002-2003 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@infradead.org&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: os-linux.h,v 1.51 2004/11/16 20:36:11 dwmw2 Exp $&n; *&n; */
macro_line|#ifndef __JFFS2_OS_LINUX_H__
DECL|macro|__JFFS2_OS_LINUX_H__
mdefine_line|#define __JFFS2_OS_LINUX_H__
macro_line|#include &lt;linux/version.h&gt;
multiline_comment|/* JFFS2 uses Linux mode bits natively -- no need for conversion */
DECL|macro|os_to_jffs2_mode
mdefine_line|#define os_to_jffs2_mode(x) (x)
DECL|macro|jffs2_to_os_mode
mdefine_line|#define jffs2_to_os_mode(x) (x)
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,73)
DECL|macro|kstatfs
mdefine_line|#define kstatfs statfs
macro_line|#endif
r_struct
id|kstatfs
suffix:semicolon
r_struct
id|kvec
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,5,2)
DECL|macro|JFFS2_INODE_INFO
mdefine_line|#define JFFS2_INODE_INFO(i) (list_entry(i, struct jffs2_inode_info, vfs_inode))
DECL|macro|OFNI_EDONI_2SFFJ
mdefine_line|#define OFNI_EDONI_2SFFJ(f)  (&amp;(f)-&gt;vfs_inode)
DECL|macro|JFFS2_SB_INFO
mdefine_line|#define JFFS2_SB_INFO(sb) (sb-&gt;s_fs_info)
DECL|macro|OFNI_BS_2SFFJ
mdefine_line|#define OFNI_BS_2SFFJ(c)  ((struct super_block *)c-&gt;os_priv)
macro_line|#elif defined(JFFS2_OUT_OF_KERNEL)
DECL|macro|JFFS2_INODE_INFO
mdefine_line|#define JFFS2_INODE_INFO(i) ((struct jffs2_inode_info *) &amp;(i)-&gt;u)
DECL|macro|OFNI_EDONI_2SFFJ
mdefine_line|#define OFNI_EDONI_2SFFJ(f)  ((struct inode *) ( ((char *)f) - ((char *)(&amp;((struct inode *)NULL)-&gt;u)) ) )
DECL|macro|JFFS2_SB_INFO
mdefine_line|#define JFFS2_SB_INFO(sb) ((struct jffs2_sb_info *) &amp;(sb)-&gt;u)
DECL|macro|OFNI_BS_2SFFJ
mdefine_line|#define OFNI_BS_2SFFJ(c)  ((struct super_block *) ( ((char *)c) - ((char *)(&amp;((struct super_block *)NULL)-&gt;u)) ) )
macro_line|#else
DECL|macro|JFFS2_INODE_INFO
mdefine_line|#define JFFS2_INODE_INFO(i) (&amp;i-&gt;u.jffs2_i)
DECL|macro|OFNI_EDONI_2SFFJ
mdefine_line|#define OFNI_EDONI_2SFFJ(f)  ((struct inode *) ( ((char *)f) - ((char *)(&amp;((struct inode *)NULL)-&gt;u)) ) )
DECL|macro|JFFS2_SB_INFO
mdefine_line|#define JFFS2_SB_INFO(sb) (&amp;sb-&gt;u.jffs2_sb)
DECL|macro|OFNI_BS_2SFFJ
mdefine_line|#define OFNI_BS_2SFFJ(c)  ((struct super_block *) ( ((char *)c) - ((char *)(&amp;((struct super_block *)NULL)-&gt;u)) ) )
macro_line|#endif
DECL|macro|JFFS2_F_I_SIZE
mdefine_line|#define JFFS2_F_I_SIZE(f) (OFNI_EDONI_2SFFJ(f)-&gt;i_size)
DECL|macro|JFFS2_F_I_MODE
mdefine_line|#define JFFS2_F_I_MODE(f) (OFNI_EDONI_2SFFJ(f)-&gt;i_mode)
DECL|macro|JFFS2_F_I_UID
mdefine_line|#define JFFS2_F_I_UID(f) (OFNI_EDONI_2SFFJ(f)-&gt;i_uid)
DECL|macro|JFFS2_F_I_GID
mdefine_line|#define JFFS2_F_I_GID(f) (OFNI_EDONI_2SFFJ(f)-&gt;i_gid)
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,5,1)
DECL|macro|JFFS2_F_I_RDEV_MIN
mdefine_line|#define JFFS2_F_I_RDEV_MIN(f) (iminor(OFNI_EDONI_2SFFJ(f)))
DECL|macro|JFFS2_F_I_RDEV_MAJ
mdefine_line|#define JFFS2_F_I_RDEV_MAJ(f) (imajor(OFNI_EDONI_2SFFJ(f)))
macro_line|#else
DECL|macro|JFFS2_F_I_RDEV_MIN
mdefine_line|#define JFFS2_F_I_RDEV_MIN(f) (MINOR(to_kdev_t(OFNI_EDONI_2SFFJ(f)-&gt;i_rdev)))
DECL|macro|JFFS2_F_I_RDEV_MAJ
mdefine_line|#define JFFS2_F_I_RDEV_MAJ(f) (MAJOR(to_kdev_t(OFNI_EDONI_2SFFJ(f)-&gt;i_rdev)))
macro_line|#endif
multiline_comment|/* Urgh. The things we do to keep the 2.4 build working */
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,5,47)
DECL|macro|ITIME
mdefine_line|#define ITIME(sec) ((struct timespec){sec, 0})
DECL|macro|I_SEC
mdefine_line|#define I_SEC(tv) ((tv).tv_sec)
DECL|macro|JFFS2_F_I_CTIME
mdefine_line|#define JFFS2_F_I_CTIME(f) (OFNI_EDONI_2SFFJ(f)-&gt;i_ctime.tv_sec)
DECL|macro|JFFS2_F_I_MTIME
mdefine_line|#define JFFS2_F_I_MTIME(f) (OFNI_EDONI_2SFFJ(f)-&gt;i_mtime.tv_sec)
DECL|macro|JFFS2_F_I_ATIME
mdefine_line|#define JFFS2_F_I_ATIME(f) (OFNI_EDONI_2SFFJ(f)-&gt;i_atime.tv_sec)
macro_line|#else
DECL|macro|ITIME
mdefine_line|#define ITIME(x) (x)
DECL|macro|I_SEC
mdefine_line|#define I_SEC(x) (x)
DECL|macro|JFFS2_F_I_CTIME
mdefine_line|#define JFFS2_F_I_CTIME(f) (OFNI_EDONI_2SFFJ(f)-&gt;i_ctime)
DECL|macro|JFFS2_F_I_MTIME
mdefine_line|#define JFFS2_F_I_MTIME(f) (OFNI_EDONI_2SFFJ(f)-&gt;i_mtime)
DECL|macro|JFFS2_F_I_ATIME
mdefine_line|#define JFFS2_F_I_ATIME(f) (OFNI_EDONI_2SFFJ(f)-&gt;i_atime)
macro_line|#endif
DECL|macro|sleep_on_spinunlock
mdefine_line|#define sleep_on_spinunlock(wq, s)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DECLARE_WAITQUEUE(__wait, current);&t;&t;&bslash;&n;&t;&t;add_wait_queue((wq), &amp;__wait);&t;&t;&t;&bslash;&n;&t;&t;set_current_state(TASK_UNINTERRUPTIBLE);&t;&bslash;&n;&t;&t;spin_unlock(s);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;schedule();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;remove_wait_queue((wq), &amp;__wait);&t;&t;&bslash;&n;&t;} while(0)
DECL|function|jffs2_init_inode_info
r_static
r_inline
r_void
id|jffs2_init_inode_info
c_func
(paren
r_struct
id|jffs2_inode_info
op_star
id|f
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,5,2)
id|f-&gt;highest_version
op_assign
l_int|0
suffix:semicolon
id|f-&gt;fragtree
op_assign
id|RB_ROOT
suffix:semicolon
id|f-&gt;metadata
op_assign
l_int|NULL
suffix:semicolon
id|f-&gt;dents
op_assign
l_int|NULL
suffix:semicolon
id|f-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|f-&gt;usercompr
op_assign
l_int|0
suffix:semicolon
macro_line|#else
id|memset
c_func
(paren
id|f
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|f
)paren
)paren
suffix:semicolon
id|init_MUTEX_LOCKED
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|jffs2_is_readonly
mdefine_line|#define jffs2_is_readonly(c) (OFNI_BS_2SFFJ(c)-&gt;s_flags &amp; MS_RDONLY)
macro_line|#if (!defined CONFIG_JFFS2_FS_NAND &amp;&amp; !defined CONFIG_JFFS2_FS_NOR_ECC)
DECL|macro|jffs2_can_mark_obsolete
mdefine_line|#define jffs2_can_mark_obsolete(c) (1)
DECL|macro|jffs2_cleanmarker_oob
mdefine_line|#define jffs2_cleanmarker_oob(c) (0)
DECL|macro|jffs2_write_nand_cleanmarker
mdefine_line|#define jffs2_write_nand_cleanmarker(c,jeb) (-EIO)
DECL|macro|jffs2_flash_write
mdefine_line|#define jffs2_flash_write(c, ofs, len, retlen, buf) ((c)-&gt;mtd-&gt;write((c)-&gt;mtd, ofs, len, retlen, buf))
DECL|macro|jffs2_flash_read
mdefine_line|#define jffs2_flash_read(c, ofs, len, retlen, buf) ((c)-&gt;mtd-&gt;read((c)-&gt;mtd, ofs, len, retlen, buf))
DECL|macro|jffs2_flush_wbuf_pad
mdefine_line|#define jffs2_flush_wbuf_pad(c) ({ (void)(c), 0; })
DECL|macro|jffs2_flush_wbuf_gc
mdefine_line|#define jffs2_flush_wbuf_gc(c, i) ({ (void)(c), (void) i, 0; })
DECL|macro|jffs2_write_nand_badblock
mdefine_line|#define jffs2_write_nand_badblock(c,jeb,bad_offset) (1)
DECL|macro|jffs2_nand_flash_setup
mdefine_line|#define jffs2_nand_flash_setup(c) (0)
DECL|macro|jffs2_nand_flash_cleanup
mdefine_line|#define jffs2_nand_flash_cleanup(c) do {} while(0)
DECL|macro|jffs2_wbuf_dirty
mdefine_line|#define jffs2_wbuf_dirty(c) (0)
DECL|macro|jffs2_flash_writev
mdefine_line|#define jffs2_flash_writev(a,b,c,d,e,f) jffs2_flash_direct_writev(a,b,c,d,e)
DECL|macro|jffs2_wbuf_timeout
mdefine_line|#define jffs2_wbuf_timeout NULL
DECL|macro|jffs2_wbuf_process
mdefine_line|#define jffs2_wbuf_process NULL
DECL|macro|jffs2_nor_ecc
mdefine_line|#define jffs2_nor_ecc(c) (0)
DECL|macro|jffs2_nor_ecc_flash_setup
mdefine_line|#define jffs2_nor_ecc_flash_setup(c) (0)
DECL|macro|jffs2_nor_ecc_flash_cleanup
mdefine_line|#define jffs2_nor_ecc_flash_cleanup(c) do {} while (0)
macro_line|#else /* NAND and/or ECC&squot;d NOR support present */
DECL|macro|jffs2_can_mark_obsolete
mdefine_line|#define jffs2_can_mark_obsolete(c) ((c-&gt;mtd-&gt;type == MTD_NORFLASH &amp;&amp; !(c-&gt;mtd-&gt;flags &amp; MTD_ECC)) || c-&gt;mtd-&gt;type == MTD_RAM)
DECL|macro|jffs2_cleanmarker_oob
mdefine_line|#define jffs2_cleanmarker_oob(c) (c-&gt;mtd-&gt;type == MTD_NANDFLASH)
DECL|macro|jffs2_flash_write_oob
mdefine_line|#define jffs2_flash_write_oob(c, ofs, len, retlen, buf) ((c)-&gt;mtd-&gt;write_oob((c)-&gt;mtd, ofs, len, retlen, buf))
DECL|macro|jffs2_flash_read_oob
mdefine_line|#define jffs2_flash_read_oob(c, ofs, len, retlen, buf) ((c)-&gt;mtd-&gt;read_oob((c)-&gt;mtd, ofs, len, retlen, buf))
DECL|macro|jffs2_wbuf_dirty
mdefine_line|#define jffs2_wbuf_dirty(c) (!!(c)-&gt;wbuf_len)
multiline_comment|/* wbuf.c */
r_int
id|jffs2_flash_writev
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_const
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|to
comma
r_int
op_star
id|retlen
comma
r_uint32
id|ino
)paren
suffix:semicolon
r_int
id|jffs2_flash_write
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
id|loff_t
id|ofs
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
r_const
id|u_char
op_star
id|buf
)paren
suffix:semicolon
r_int
id|jffs2_flash_read
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
id|loff_t
id|ofs
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
)paren
suffix:semicolon
r_int
id|jffs2_check_oob_empty
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_eraseblock
op_star
id|jeb
comma
r_int
id|mode
)paren
suffix:semicolon
r_int
id|jffs2_check_nand_cleanmarker
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_eraseblock
op_star
id|jeb
)paren
suffix:semicolon
r_int
id|jffs2_write_nand_cleanmarker
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_eraseblock
op_star
id|jeb
)paren
suffix:semicolon
r_int
id|jffs2_write_nand_badblock
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_eraseblock
op_star
id|jeb
comma
r_uint32
id|bad_offset
)paren
suffix:semicolon
r_void
id|jffs2_wbuf_timeout
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
r_void
id|jffs2_wbuf_process
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
r_int
id|jffs2_flush_wbuf_gc
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_uint32
id|ino
)paren
suffix:semicolon
r_int
id|jffs2_flush_wbuf_pad
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
r_int
id|jffs2_nand_flash_setup
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
r_void
id|jffs2_nand_flash_cleanup
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_JFFS2_FS_NOR_ECC
DECL|macro|jffs2_nor_ecc
mdefine_line|#define jffs2_nor_ecc(c) (c-&gt;mtd-&gt;type == MTD_NORFLASH &amp;&amp; (c-&gt;mtd-&gt;flags &amp; MTD_ECC))
r_int
id|jffs2_nor_ecc_flash_setup
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
r_void
id|jffs2_nor_ecc_flash_cleanup
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
macro_line|#else
DECL|macro|jffs2_nor_ecc
mdefine_line|#define jffs2_nor_ecc(c) (0)
DECL|macro|jffs2_nor_ecc_flash_setup
mdefine_line|#define jffs2_nor_ecc_flash_setup(c) (0)
DECL|macro|jffs2_nor_ecc_flash_cleanup
mdefine_line|#define jffs2_nor_ecc_flash_cleanup(c) do {} while (0)
macro_line|#endif /* NOR ECC */
macro_line|#endif /* NAND */
multiline_comment|/* erase.c */
DECL|function|jffs2_erase_pending_trigger
r_static
r_inline
r_void
id|jffs2_erase_pending_trigger
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
(brace
id|OFNI_BS_2SFFJ
c_func
(paren
id|c
)paren
op_member_access_from_pointer
id|s_dirt
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* background.c */
r_int
id|jffs2_start_garbage_collect_thread
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
r_void
id|jffs2_stop_garbage_collect_thread
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
r_void
id|jffs2_garbage_collect_trigger
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_struct
id|file_operations
id|jffs2_dir_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|jffs2_dir_inode_operations
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|file_operations
id|jffs2_file_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|jffs2_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|jffs2_file_address_operations
suffix:semicolon
r_int
id|jffs2_fsync
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|jffs2_do_readpage_unlock
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|pg
)paren
suffix:semicolon
multiline_comment|/* ioctl.c */
r_int
id|jffs2_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* symlink.c */
r_extern
r_struct
id|inode_operations
id|jffs2_symlink_inode_operations
suffix:semicolon
multiline_comment|/* fs.c */
r_int
id|jffs2_setattr
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_void
id|jffs2_read_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|jffs2_clear_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|jffs2_dirty_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|jffs2_new_inode
(paren
r_struct
id|inode
op_star
id|dir_i
comma
r_int
id|mode
comma
r_struct
id|jffs2_raw_inode
op_star
id|ri
)paren
suffix:semicolon
r_int
id|jffs2_statfs
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|kstatfs
op_star
)paren
suffix:semicolon
r_void
id|jffs2_write_super
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_int
id|jffs2_remount_fs
(paren
r_struct
id|super_block
op_star
comma
r_int
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_int
id|jffs2_do_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
suffix:semicolon
r_void
id|jffs2_gc_release_inode
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_info
op_star
id|f
)paren
suffix:semicolon
r_struct
id|jffs2_inode_info
op_star
id|jffs2_gc_fetch_inode
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_int
id|inum
comma
r_int
id|nlink
)paren
suffix:semicolon
r_int
r_char
op_star
id|jffs2_gc_fetch_page
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_info
op_star
id|f
comma
r_int
r_int
id|offset
comma
r_int
r_int
op_star
id|priv
)paren
suffix:semicolon
r_void
id|jffs2_gc_release_page
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_int
r_char
op_star
id|pg
comma
r_int
r_int
op_star
id|priv
)paren
suffix:semicolon
r_void
id|jffs2_flash_cleanup
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
multiline_comment|/* writev.c */
r_int
id|jffs2_flash_direct_writev
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_const
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|to
comma
r_int
op_star
id|retlen
)paren
suffix:semicolon
macro_line|#endif /* __JFFS2_OS_LINUX_H__ */
eof
