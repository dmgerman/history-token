macro_line|#include &lt;linux/pagemap.h&gt;
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
DECL|member|v
DECL|typedef|Sector
r_typedef
r_struct
(brace
r_struct
id|page
op_star
id|v
suffix:semicolon
)brace
id|Sector
suffix:semicolon
r_int
r_char
op_star
id|read_dev_sector
c_func
(paren
r_struct
id|block_device
op_star
comma
r_int
r_int
comma
id|Sector
op_star
)paren
suffix:semicolon
DECL|function|put_dev_sector
r_static
r_inline
r_void
id|put_dev_sector
c_func
(paren
id|Sector
id|p
)paren
(brace
id|page_cache_release
c_func
(paren
id|p.v
)paren
suffix:semicolon
)brace
r_extern
r_int
id|warn_no_part
suffix:semicolon
eof
