macro_line|#ifdef CONFIG_DEVFS_FS
r_void
id|devfs_add_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
)paren
suffix:semicolon
r_void
id|devfs_add_partitioned
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
)paren
suffix:semicolon
r_void
id|devfs_remove_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
)paren
suffix:semicolon
macro_line|#else
DECL|macro|devfs_add_disk
macro_line|# define devfs_add_disk(disk)&t;&t;&t;do { } while (0)
DECL|macro|devfs_add_partitioned
macro_line|# define devfs_add_partitioned(disk)&t;&t;do { } while (0)
DECL|macro|devfs_remove_disk
macro_line|# define devfs_remove_disk(disk)&t;&t;do { } while (0)
macro_line|#endif
eof
