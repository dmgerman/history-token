macro_line|#ifndef __COW_H__
DECL|macro|__COW_H__
mdefine_line|#define __COW_H__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#if __BYTE_ORDER == __BIG_ENDIAN
DECL|macro|ntohll
macro_line|# define ntohll(x) (x)
DECL|macro|htonll
macro_line|# define htonll(x) (x)
macro_line|#elif __BYTE_ORDER == __LITTLE_ENDIAN
DECL|macro|ntohll
macro_line|# define ntohll(x)  bswap_64(x)
DECL|macro|htonll
macro_line|# define htonll(x)  bswap_64(x)
macro_line|#else
macro_line|#error &quot;__BYTE_ORDER not defined&quot;
macro_line|#endif
r_extern
r_int
id|init_cow_file
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|cow_file
comma
r_char
op_star
id|backing_file
comma
r_int
id|sectorsize
comma
r_int
id|alignment
comma
r_int
op_star
id|bitmap_offset_out
comma
r_int
r_int
op_star
id|bitmap_len_out
comma
r_int
op_star
id|data_offset_out
)paren
suffix:semicolon
r_extern
r_int
id|file_reader
c_func
(paren
id|__u64
id|offset
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|read_cow_header
c_func
(paren
r_int
(paren
op_star
id|reader
)paren
(paren
id|__u64
comma
r_char
op_star
comma
r_int
comma
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
id|__u32
op_star
id|version_out
comma
r_char
op_star
op_star
id|backing_file_out
comma
id|time_t
op_star
id|mtime_out
comma
r_int
r_int
r_int
op_star
id|size_out
comma
r_int
op_star
id|sectorsize_out
comma
id|__u32
op_star
id|align_out
comma
r_int
op_star
id|bitmap_offset_out
)paren
suffix:semicolon
r_extern
r_int
id|write_cow_header
c_func
(paren
r_char
op_star
id|cow_file
comma
r_int
id|fd
comma
r_char
op_star
id|backing_file
comma
r_int
id|sectorsize
comma
r_int
id|alignment
comma
r_int
r_int
r_int
op_star
id|size
)paren
suffix:semicolon
r_extern
r_void
id|cow_sizes
c_func
(paren
r_int
id|version
comma
id|__u64
id|size
comma
r_int
id|sectorsize
comma
r_int
id|align
comma
r_int
id|bitmap_offset
comma
r_int
r_int
op_star
id|bitmap_len_out
comma
r_int
op_star
id|data_offset_out
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
