multiline_comment|/*&n; *  fs/partitions/msdos.h&n; */
DECL|macro|MSDOS_LABEL_MAGIC
mdefine_line|#define MSDOS_LABEL_MAGIC&t;&t;0xAA55
r_int
id|msdos_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_struct
id|block_device
op_star
id|bdev
comma
r_int
r_int
id|first_sector
comma
r_int
id|first_part_minor
)paren
suffix:semicolon
eof
