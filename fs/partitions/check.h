macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
multiline_comment|/*&n; * add_gd_partition adds a partitions details to the devices partition&n; * description.&n; */
DECL|enumerator|MAX_PART
r_enum
(brace
id|MAX_PART
op_assign
l_int|256
)brace
suffix:semicolon
DECL|struct|parsed_partitions
r_struct
id|parsed_partitions
(brace
DECL|member|name
r_char
id|name
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
r_struct
(brace
DECL|member|from
id|sector_t
id|from
suffix:semicolon
DECL|member|size
id|sector_t
id|size
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|parts
)brace
id|parts
(braket
id|MAX_PART
)braket
suffix:semicolon
DECL|member|next
r_int
id|next
suffix:semicolon
DECL|member|limit
r_int
id|limit
suffix:semicolon
)brace
suffix:semicolon
r_static
r_inline
r_void
DECL|function|put_partition
id|put_partition
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|p
comma
r_int
id|n
comma
id|sector_t
id|from
comma
id|sector_t
id|size
)paren
(brace
r_if
c_cond
(paren
id|n
OL
id|p-&gt;limit
)paren
(brace
id|p-&gt;parts
(braket
id|n
)braket
dot
id|from
op_assign
id|from
suffix:semicolon
id|p-&gt;parts
(braket
id|n
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %s%d&quot;
comma
id|p-&gt;name
comma
id|n
)paren
suffix:semicolon
)brace
)brace
r_extern
r_int
id|warn_no_part
suffix:semicolon
r_extern
r_void
id|parse_bsd
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
comma
id|u32
id|offset
comma
id|u32
id|size
comma
r_int
id|origin
comma
r_char
op_star
id|flavour
comma
r_int
id|max_partitions
)paren
suffix:semicolon
eof
