multiline_comment|/*&n; * linux/fs/fat/fatfs_syms.c&n; *&n; * Exported kernel symbols for the low-level FAT-based fs support.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/fat_cvf.h&gt;
DECL|variable|fat_new_dir
id|EXPORT_SYMBOL
c_func
(paren
id|fat_new_dir
)paren
suffix:semicolon
DECL|variable|fat_get_block
id|EXPORT_SYMBOL
c_func
(paren
id|fat_get_block
)paren
suffix:semicolon
DECL|variable|fat_clear_inode
id|EXPORT_SYMBOL
c_func
(paren
id|fat_clear_inode
)paren
suffix:semicolon
DECL|variable|fat_date_unix2dos
id|EXPORT_SYMBOL
c_func
(paren
id|fat_date_unix2dos
)paren
suffix:semicolon
DECL|variable|fat_delete_inode
id|EXPORT_SYMBOL
c_func
(paren
id|fat_delete_inode
)paren
suffix:semicolon
DECL|variable|fat__get_entry
id|EXPORT_SYMBOL
c_func
(paren
id|fat__get_entry
)paren
suffix:semicolon
DECL|variable|fat_mark_buffer_dirty
id|EXPORT_SYMBOL
c_func
(paren
id|fat_mark_buffer_dirty
)paren
suffix:semicolon
DECL|variable|fat_notify_change
id|EXPORT_SYMBOL
c_func
(paren
id|fat_notify_change
)paren
suffix:semicolon
DECL|variable|fat_put_super
id|EXPORT_SYMBOL
c_func
(paren
id|fat_put_super
)paren
suffix:semicolon
DECL|variable|fat_attach
id|EXPORT_SYMBOL
c_func
(paren
id|fat_attach
)paren
suffix:semicolon
DECL|variable|fat_detach
id|EXPORT_SYMBOL
c_func
(paren
id|fat_detach
)paren
suffix:semicolon
DECL|variable|fat_build_inode
id|EXPORT_SYMBOL
c_func
(paren
id|fat_build_inode
)paren
suffix:semicolon
DECL|variable|fat_fill_super
id|EXPORT_SYMBOL
c_func
(paren
id|fat_fill_super
)paren
suffix:semicolon
DECL|variable|fat_search_long
id|EXPORT_SYMBOL
c_func
(paren
id|fat_search_long
)paren
suffix:semicolon
DECL|variable|fat_readdir
id|EXPORT_SYMBOL
c_func
(paren
id|fat_readdir
)paren
suffix:semicolon
DECL|variable|fat_scan
id|EXPORT_SYMBOL
c_func
(paren
id|fat_scan
)paren
suffix:semicolon
DECL|variable|fat_statfs
id|EXPORT_SYMBOL
c_func
(paren
id|fat_statfs
)paren
suffix:semicolon
DECL|variable|fat_write_inode
id|EXPORT_SYMBOL
c_func
(paren
id|fat_write_inode
)paren
suffix:semicolon
DECL|variable|register_cvf_format
id|EXPORT_SYMBOL
c_func
(paren
id|register_cvf_format
)paren
suffix:semicolon
DECL|variable|unregister_cvf_format
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_cvf_format
)paren
suffix:semicolon
DECL|variable|fat_get_cluster
id|EXPORT_SYMBOL
c_func
(paren
id|fat_get_cluster
)paren
suffix:semicolon
DECL|variable|fat_dir_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|fat_dir_ioctl
)paren
suffix:semicolon
DECL|variable|fat_add_entries
id|EXPORT_SYMBOL
c_func
(paren
id|fat_add_entries
)paren
suffix:semicolon
DECL|variable|fat_dir_empty
id|EXPORT_SYMBOL
c_func
(paren
id|fat_dir_empty
)paren
suffix:semicolon
DECL|variable|fat_truncate
id|EXPORT_SYMBOL
c_func
(paren
id|fat_truncate
)paren
suffix:semicolon
DECL|variable|fat_brelse
id|EXPORT_SYMBOL
c_func
(paren
id|fat_brelse
)paren
suffix:semicolon
r_int
id|__init
id|fat_init_inodecache
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|__exit
id|fat_destroy_inodecache
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|init_fat_fs
r_static
r_int
id|__init
id|init_fat_fs
c_func
(paren
r_void
)paren
(brace
id|fat_hash_init
c_func
(paren
)paren
suffix:semicolon
r_return
id|fat_init_inodecache
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|exit_fat_fs
r_static
r_void
id|__exit
id|exit_fat_fs
c_func
(paren
r_void
)paren
(brace
id|fat_destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_fat_fs
)paren
id|module_exit
c_func
(paren
id|exit_fat_fs
)paren
eof
