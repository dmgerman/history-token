multiline_comment|/*&n; *  fs/partitions/sgi.h&n; */
r_extern
r_int
id|sgi_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
id|kdev_t
id|dev
comma
r_int
r_int
id|first_sector
comma
r_int
id|first_part_minor
)paren
suffix:semicolon
DECL|macro|SGI_LABEL_MAGIC
mdefine_line|#define SGI_LABEL_MAGIC 0x0be5a941
eof
