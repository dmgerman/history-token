multiline_comment|/*&n; * support.h - Header file for specific support.c&n; *&n; * Copyright (C) 1997 R&#xfffd;gis Duchesne&n; * Copyright (c) 2001 Anton Altaparmakov (AIA)&n; */
multiline_comment|/* Debug levels */
DECL|macro|DEBUG_OTHER
mdefine_line|#define DEBUG_OTHER&t;1
DECL|macro|DEBUG_MALLOC
mdefine_line|#define DEBUG_MALLOC&t;2
DECL|macro|DEBUG_BSD
mdefine_line|#define DEBUG_BSD       4
DECL|macro|DEBUG_LINUX
mdefine_line|#define DEBUG_LINUX     8
DECL|macro|DEBUG_DIR1
mdefine_line|#define DEBUG_DIR1     16
DECL|macro|DEBUG_DIR2
mdefine_line|#define DEBUG_DIR2     32
DECL|macro|DEBUG_DIR3
mdefine_line|#define DEBUG_DIR3     64
DECL|macro|DEBUG_FILE1
mdefine_line|#define DEBUG_FILE1   128
DECL|macro|DEBUG_FILE2
mdefine_line|#define DEBUG_FILE2   256
DECL|macro|DEBUG_FILE3
mdefine_line|#define DEBUG_FILE3   512
DECL|macro|DEBUG_NAME1
mdefine_line|#define DEBUG_NAME1  1024
DECL|macro|DEBUG_NAME2
mdefine_line|#define DEBUG_NAME2  2048
r_void
id|ntfs_debug
c_func
(paren
r_int
id|mask
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
DECL|macro|ntfs_malloc
mdefine_line|#define ntfs_malloc(size)  kmalloc(size, GFP_KERNEL)
DECL|macro|ntfs_free
mdefine_line|#define ntfs_free(ptr)     kfree(ptr)
DECL|macro|ntfs_vmalloc
mdefine_line|#define ntfs_vmalloc(size)&t;vmalloc_32(size)
DECL|macro|ntfs_vfree
mdefine_line|#define ntfs_vfree(ptr)&t;&t;vfree(ptr)
r_void
id|ntfs_bzero
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|n
)paren
suffix:semicolon
r_void
id|ntfs_memcpy
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
id|ntfs_size_t
id|n
)paren
suffix:semicolon
r_void
id|ntfs_memmove
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
id|ntfs_size_t
id|n
)paren
suffix:semicolon
r_void
id|ntfs_error
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|ntfs_read_mft_record
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
r_int
id|mftno
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
r_int
id|ntfs_getput_clusters
c_func
(paren
id|ntfs_volume
op_star
id|pvol
comma
r_int
id|cluster
comma
id|ntfs_size_t
id|offs
comma
id|ntfs_io
op_star
id|buf
)paren
suffix:semicolon
id|ntfs_time64_t
id|ntfs_now
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|ntfs_dupuni2map
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
id|ntfs_u16
op_star
id|in
comma
r_int
id|in_len
comma
r_char
op_star
op_star
id|out
comma
r_int
op_star
id|out_len
)paren
suffix:semicolon
r_int
id|ntfs_dupmap2uni
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
r_char
op_star
id|in
comma
r_int
id|in_len
comma
id|ntfs_u16
op_star
op_star
id|out
comma
r_int
op_star
id|out_len
)paren
suffix:semicolon
eof
