multiline_comment|/*&n; *  fs/partitions/osf.h&n; */
DECL|macro|DISKLABELMAGIC
mdefine_line|#define DISKLABELMAGIC (0x82564557UL)
r_int
id|osf_partition
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
id|current_minor
)paren
suffix:semicolon
eof
