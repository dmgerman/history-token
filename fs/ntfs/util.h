multiline_comment|/*&n; *  util.h&n; *  Header file for util.c&n; *&n; *  Copyright (C) 1997 R&#xfffd;gis Duchesne&n; */
multiline_comment|/* Which character set is used for file names */
multiline_comment|/*  Translate everything to UTF-8 */
DECL|macro|nct_utf8
mdefine_line|#define nct_utf8             1
multiline_comment|/*  Translate to 8859-1 */
DECL|macro|nct_iso8859_1
mdefine_line|#define nct_iso8859_1        2
multiline_comment|/*  Quote unprintables with : */
DECL|macro|nct_uni_xlate
mdefine_line|#define nct_uni_xlate        4
multiline_comment|/*  Do that in the vfat way instead of the documented way */
DECL|macro|nct_uni_xlate_vfat
mdefine_line|#define nct_uni_xlate_vfat   8
multiline_comment|/*  Use a mapping table to determine printables */
DECL|macro|nct_map
mdefine_line|#define nct_map              16
multiline_comment|/* The first 11 inodes correspond to special files */
DECL|macro|FILE_MFT
mdefine_line|#define FILE_MFT      0
DECL|macro|FILE_MFTMIRR
mdefine_line|#define FILE_MFTMIRR  1
DECL|macro|FILE_LOGFILE
mdefine_line|#define FILE_LOGFILE  2
DECL|macro|FILE_VOLUME
mdefine_line|#define FILE_VOLUME   3
DECL|macro|FILE_ATTRDEF
mdefine_line|#define FILE_ATTRDEF  4
DECL|macro|FILE_ROOT
mdefine_line|#define FILE_ROOT     5
DECL|macro|FILE_BITMAP
mdefine_line|#define FILE_BITMAP   6
DECL|macro|FILE_BOOT
mdefine_line|#define FILE_BOOT     7
DECL|macro|FILE_BADCLUS
mdefine_line|#define FILE_BADCLUS  8
DECL|macro|FILE_QUOTA
mdefine_line|#define FILE_QUOTA    9
DECL|macro|FILE_UPCASE
mdefine_line|#define FILE_UPCASE  10
multiline_comment|/* Memory management */
r_void
op_star
id|ntfs_calloc
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* String operations */
multiline_comment|/*  Copy Unicode &lt;-&gt; ASCII */
macro_line|#if 0
r_void
id|ntfs_uni2ascii
c_func
(paren
r_char
op_star
id|to
comma
r_char
op_star
id|from
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif
r_void
id|ntfs_ascii2uni
c_func
(paren
r_int
r_int
op_star
id|to
comma
r_char
op_star
id|from
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/*  Comparison */
r_int
id|ntfs_uni_strncmp
c_func
(paren
r_int
r_int
op_star
id|a
comma
r_int
r_int
op_star
id|b
comma
r_int
id|n
)paren
suffix:semicolon
r_int
id|ntfs_ua_strncmp
c_func
(paren
r_int
r_int
op_star
id|a
comma
r_char
op_star
id|b
comma
r_int
id|n
)paren
suffix:semicolon
multiline_comment|/* Same address space copies */
r_void
id|ntfs_put
c_func
(paren
id|ntfs_io
op_star
id|dest
comma
r_void
op_star
id|src
comma
id|ntfs_size_t
id|n
)paren
suffix:semicolon
r_void
id|ntfs_get
c_func
(paren
r_void
op_star
id|dest
comma
id|ntfs_io
op_star
id|src
comma
id|ntfs_size_t
id|n
)paren
suffix:semicolon
multiline_comment|/* Charset conversion */
r_int
id|ntfs_encodeuni
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
id|ntfs_decodeuni
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
multiline_comment|/* Time conversion */
multiline_comment|/*  NT &lt;-&gt; Unix */
id|ntfs_time_t
id|ntfs_ntutc2unixutc
c_func
(paren
id|ntfs_time64_t
id|ntutc
)paren
suffix:semicolon
id|ntfs_time64_t
id|ntfs_unixutc2ntutc
c_func
(paren
id|ntfs_time_t
id|t
)paren
suffix:semicolon
multiline_comment|/* Attribute names */
r_void
id|ntfs_indexname
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|type
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
