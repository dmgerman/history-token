multiline_comment|/* zlib_fs.h -- A compatability file mapping the zlib functions to zlib_fs&n;   functions.   This will go away. */
macro_line|#ifndef _ZLIB_FS_H
DECL|macro|_ZLIB_FS_H
mdefine_line|#define _ZLIB_FS_H
macro_line|#include &lt;linux/zlib.h&gt;
DECL|macro|zlib_fs_inflate_workspacesize
mdefine_line|#define zlib_fs_inflate_workspacesize zlib_inflate_workspacesize
DECL|macro|zlib_fs_deflate_workspacesize
mdefine_line|#define zlib_fs_deflate_workspacesize zlib_deflate_workspacesize
DECL|macro|zlib_fs_zlibVersion
mdefine_line|#define zlib_fs_zlibVersion zlib_zlibVersion
DECL|macro|zlib_fs_deflate
mdefine_line|#define zlib_fs_deflate zlib_deflate
DECL|macro|zlib_fs_deflateEnd
mdefine_line|#define zlib_fs_deflateEnd zlib_deflateEnd
DECL|macro|zlib_fs_inflate
mdefine_line|#define zlib_fs_inflate zlib_inflate
DECL|macro|zlib_fs_inflateEnd
mdefine_line|#define zlib_fs_inflateEnd zlib_inflateEnd
DECL|macro|zlib_fs_deflateSetDictionary
mdefine_line|#define zlib_fs_deflateSetDictionary zlib_deflateSetDictionary
DECL|macro|zlib_fs_deflateCopy
mdefine_line|#define zlib_fs_deflateCopy zlib_deflateCopy
DECL|macro|zlib_fs_deflateReset
mdefine_line|#define zlib_fs_deflateReset zlib_deflateReset
DECL|macro|zlib_fs_deflateParams
mdefine_line|#define zlib_fs_deflateParams zlib_deflateParams
DECL|macro|zlib_fs_inflateIncomp
mdefine_line|#define zlib_fs_inflateIncomp zlib_inflateIncomp
DECL|macro|zlib_fs_inflateSetDictionary
mdefine_line|#define zlib_fs_inflateSetDictionary zlib_inflateSetDictionary
DECL|macro|zlib_fs_inflateSync
mdefine_line|#define zlib_fs_inflateSync zlib_inflateSync
DECL|macro|zlib_fs_inflateReset
mdefine_line|#define zlib_fs_inflateReset zlib_inflateReset
DECL|macro|zlib_fs_adler32
mdefine_line|#define zlib_fs_adler32 zlib_adler32
DECL|macro|zlib_fs_crc32
mdefine_line|#define zlib_fs_crc32 zlib_crc32
DECL|macro|zlib_fs_deflateInit
mdefine_line|#define zlib_fs_deflateInit(strm, level) &bslash;&n;        zlib_deflateInit_((strm), (level), ZLIB_VERSION, sizeof(z_stream))
DECL|macro|zlib_fs_inflateInit
mdefine_line|#define zlib_fs_inflateInit(strm) &bslash;&n;        zlib_inflateInit_((strm), ZLIB_VERSION, sizeof(z_stream))
DECL|macro|zlib_fs_deflateInit2
mdefine_line|#define zlib_fs_deflateInit2(strm, level, method, windowBits, memLevel, strategy)&bslash;&n;        zlib_deflateInit2_((strm),(level),(method),(windowBits),(memLevel),&bslash;&n;&t;&t;              (strategy), ZLIB_VERSION, sizeof(z_stream))
DECL|macro|zlib_fs_inflateInit2
mdefine_line|#define zlib_fs_inflateInit2(strm, windowBits) &bslash;&n;        zlib_inflateInit2_((strm), (windowBits), ZLIB_VERSION, &bslash;&n;                              sizeof(z_stream))
macro_line|#endif /* _ZLIB_FS_H */
eof
