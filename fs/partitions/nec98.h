multiline_comment|/*&n; *  NEC PC-9800 series partition supports&n; *&n; *  Copyright (C) 1998-2000&t;Kyoto University Microcomputer Club&n; */
DECL|macro|NEC98_PTABLE_MAGIC
mdefine_line|#define NEC98_PTABLE_MAGIC&t;0xAA55
r_extern
r_int
id|nec98_partition
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
)paren
suffix:semicolon
eof
