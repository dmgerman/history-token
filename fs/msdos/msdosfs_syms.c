multiline_comment|/*&n; * linux/fs/msdos/msdosfs_syms.c&n; *&n; * Exported kernel symbols for the MS-DOS filesystem.&n; * These symbols are used by umsdos.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * Support for umsdos fs&n; *&n; * These symbols are _always_ exported, in case someone&n; * wants to install the umsdos module later.&n; */
DECL|variable|msdos_create
id|EXPORT_SYMBOL
c_func
(paren
id|msdos_create
)paren
suffix:semicolon
DECL|variable|msdos_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|msdos_lookup
)paren
suffix:semicolon
DECL|variable|msdos_mkdir
id|EXPORT_SYMBOL
c_func
(paren
id|msdos_mkdir
)paren
suffix:semicolon
DECL|variable|msdos_rename
id|EXPORT_SYMBOL
c_func
(paren
id|msdos_rename
)paren
suffix:semicolon
DECL|variable|msdos_rmdir
id|EXPORT_SYMBOL
c_func
(paren
id|msdos_rmdir
)paren
suffix:semicolon
DECL|variable|msdos_unlink
id|EXPORT_SYMBOL
c_func
(paren
id|msdos_unlink
)paren
suffix:semicolon
DECL|variable|msdos_put_super
id|EXPORT_SYMBOL
c_func
(paren
id|msdos_put_super
)paren
suffix:semicolon
DECL|function|msdos_get_sb
r_static
r_struct
id|super_block
op_star
id|msdos_get_sb
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
id|msdos_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|msdos_fs_type
r_static
r_struct
id|file_system_type
id|msdos_fs_type
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;msdos&quot;
comma
id|get_sb
suffix:colon
id|msdos_get_sb
comma
id|kill_sb
suffix:colon
id|kill_block_super
comma
id|fs_flags
suffix:colon
id|FS_REQUIRES_DEV
comma
)brace
suffix:semicolon
DECL|function|init_msdos_fs
r_static
r_int
id|__init
id|init_msdos_fs
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
id|msdos_fs_type
)paren
suffix:semicolon
)brace
DECL|function|exit_msdos_fs
r_static
r_void
id|__exit
id|exit_msdos_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|msdos_fs_type
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_msdos_fs
)paren
id|module_exit
c_func
(paren
id|exit_msdos_fs
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
