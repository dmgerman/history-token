multiline_comment|/*&n; *  fs/partitions/sun.h&n; */
DECL|macro|SUN_LABEL_MAGIC
mdefine_line|#define SUN_LABEL_MAGIC          0xDABE
r_int
id|sun_partition
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
