multiline_comment|/*&n; * linux/fs/partitions/acorn.h&n; *&n; * Copyright (C) 1996-2001 Russell King.&n; *&n; *  I _hate_ this partitioning mess - why can&squot;t we have one defined&n; *  format, and everyone stick to it?&n; */
r_int
id|adfspart_check_CUMANA
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
r_int
id|adfspart_check_ADFS
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
r_int
id|adfspart_check_ICS
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
r_int
id|adfspart_check_POWERTEC
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
r_int
id|adfspart_check_EESOX
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
