macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
multiline_comment|/*&n; * add_gd_partition adds a partitions details to the devices partition&n; * description.&n; */
r_void
id|add_gd_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
id|minor
comma
r_int
id|start
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|warn_no_part
suffix:semicolon
eof
