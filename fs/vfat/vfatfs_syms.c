multiline_comment|/*&n; * linux/fs/msdos/vfatfs_syms.c&n; *&n; * Exported kernel symbols for the VFAT filesystem.&n; * These symbols are used by dmsdos.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
DECL|function|vfat_get_sb
r_static
r_struct
id|super_block
op_star
id|vfat_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_bdev
c_func
(paren
id|fs_type
comma
id|flags
comma
id|dev_name
comma
id|data
comma
id|vfat_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|vfat_fs_type
r_static
r_struct
id|file_system_type
id|vfat_fs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;vfat&quot;
comma
dot
id|get_sb
op_assign
id|vfat_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_block_super
comma
dot
id|fs_flags
op_assign
id|FS_REQUIRES_DEV
comma
)brace
suffix:semicolon
DECL|variable|vfat_create
id|EXPORT_SYMBOL
c_func
(paren
id|vfat_create
)paren
suffix:semicolon
DECL|variable|vfat_unlink
id|EXPORT_SYMBOL
c_func
(paren
id|vfat_unlink
)paren
suffix:semicolon
DECL|variable|vfat_mkdir
id|EXPORT_SYMBOL
c_func
(paren
id|vfat_mkdir
)paren
suffix:semicolon
DECL|variable|vfat_rmdir
id|EXPORT_SYMBOL
c_func
(paren
id|vfat_rmdir
)paren
suffix:semicolon
DECL|variable|vfat_rename
id|EXPORT_SYMBOL
c_func
(paren
id|vfat_rename
)paren
suffix:semicolon
DECL|variable|vfat_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|vfat_lookup
)paren
suffix:semicolon
DECL|function|init_vfat_fs
r_static
r_int
id|__init
id|init_vfat_fs
c_func
(paren
r_void
)paren
(brace
r_return
id|register_filesystem
c_func
(paren
op_amp
id|vfat_fs_type
)paren
suffix:semicolon
)brace
DECL|function|exit_vfat_fs
r_static
r_void
id|__exit
id|exit_vfat_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|vfat_fs_type
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_vfat_fs
)paren
id|module_exit
c_func
(paren
id|exit_vfat_fs
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
