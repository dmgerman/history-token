multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001-2003 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@infradead.org&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in the &n; * jffs2 directory.&n; *&n; * $Id: jffs2.h,v 1.34 2004/11/16 20:36:14 dwmw2 Exp $&n; *&n; */
macro_line|#ifndef __LINUX_JFFS2_H__
DECL|macro|__LINUX_JFFS2_H__
mdefine_line|#define __LINUX_JFFS2_H__
multiline_comment|/* You must include something which defines the C99 uintXX_t types. &n;   We don&squot;t do it from here because this file is used in too many&n;   different environments. */
DECL|macro|JFFS2_SUPER_MAGIC
mdefine_line|#define JFFS2_SUPER_MAGIC 0x72b6
multiline_comment|/* Values we may expect to find in the &squot;magic&squot; field */
DECL|macro|JFFS2_OLD_MAGIC_BITMASK
mdefine_line|#define JFFS2_OLD_MAGIC_BITMASK 0x1984
DECL|macro|JFFS2_MAGIC_BITMASK
mdefine_line|#define JFFS2_MAGIC_BITMASK 0x1985
DECL|macro|KSAMTIB_CIGAM_2SFFJ
mdefine_line|#define KSAMTIB_CIGAM_2SFFJ 0x8519 /* For detecting wrong-endian fs */
DECL|macro|JFFS2_EMPTY_BITMASK
mdefine_line|#define JFFS2_EMPTY_BITMASK 0xffff
DECL|macro|JFFS2_DIRTY_BITMASK
mdefine_line|#define JFFS2_DIRTY_BITMASK 0x0000
multiline_comment|/* We only allow a single char for length, and 0xFF is empty flash so&n;   we don&squot;t want it confused with a real length. Hence max 254.&n;*/
DECL|macro|JFFS2_MAX_NAME_LEN
mdefine_line|#define JFFS2_MAX_NAME_LEN 254
multiline_comment|/* How small can we sensibly write nodes? */
DECL|macro|JFFS2_MIN_DATA_LEN
mdefine_line|#define JFFS2_MIN_DATA_LEN 128
DECL|macro|JFFS2_COMPR_NONE
mdefine_line|#define JFFS2_COMPR_NONE&t;0x00
DECL|macro|JFFS2_COMPR_ZERO
mdefine_line|#define JFFS2_COMPR_ZERO&t;0x01
DECL|macro|JFFS2_COMPR_RTIME
mdefine_line|#define JFFS2_COMPR_RTIME&t;0x02
DECL|macro|JFFS2_COMPR_RUBINMIPS
mdefine_line|#define JFFS2_COMPR_RUBINMIPS&t;0x03
DECL|macro|JFFS2_COMPR_COPY
mdefine_line|#define JFFS2_COMPR_COPY&t;0x04
DECL|macro|JFFS2_COMPR_DYNRUBIN
mdefine_line|#define JFFS2_COMPR_DYNRUBIN&t;0x05
DECL|macro|JFFS2_COMPR_ZLIB
mdefine_line|#define JFFS2_COMPR_ZLIB&t;0x06
DECL|macro|JFFS2_COMPR_LZO
mdefine_line|#define JFFS2_COMPR_LZO         0x07
DECL|macro|JFFS2_COMPR_LZARI
mdefine_line|#define JFFS2_COMPR_LZARI       0x08
multiline_comment|/* Compatibility flags. */
DECL|macro|JFFS2_COMPAT_MASK
mdefine_line|#define JFFS2_COMPAT_MASK 0xc000      /* What do to if an unknown nodetype is found */
DECL|macro|JFFS2_NODE_ACCURATE
mdefine_line|#define JFFS2_NODE_ACCURATE 0x2000
multiline_comment|/* INCOMPAT: Fail to mount the filesystem */
DECL|macro|JFFS2_FEATURE_INCOMPAT
mdefine_line|#define JFFS2_FEATURE_INCOMPAT 0xc000
multiline_comment|/* ROCOMPAT: Mount read-only */
DECL|macro|JFFS2_FEATURE_ROCOMPAT
mdefine_line|#define JFFS2_FEATURE_ROCOMPAT 0x8000
multiline_comment|/* RWCOMPAT_COPY: Mount read/write, and copy the node when it&squot;s GC&squot;d */
DECL|macro|JFFS2_FEATURE_RWCOMPAT_COPY
mdefine_line|#define JFFS2_FEATURE_RWCOMPAT_COPY 0x4000
multiline_comment|/* RWCOMPAT_DELETE: Mount read/write, and delete the node when it&squot;s GC&squot;d */
DECL|macro|JFFS2_FEATURE_RWCOMPAT_DELETE
mdefine_line|#define JFFS2_FEATURE_RWCOMPAT_DELETE 0x0000
DECL|macro|JFFS2_NODETYPE_DIRENT
mdefine_line|#define JFFS2_NODETYPE_DIRENT (JFFS2_FEATURE_INCOMPAT | JFFS2_NODE_ACCURATE | 1)
DECL|macro|JFFS2_NODETYPE_INODE
mdefine_line|#define JFFS2_NODETYPE_INODE (JFFS2_FEATURE_INCOMPAT | JFFS2_NODE_ACCURATE | 2)
DECL|macro|JFFS2_NODETYPE_CLEANMARKER
mdefine_line|#define JFFS2_NODETYPE_CLEANMARKER (JFFS2_FEATURE_RWCOMPAT_DELETE | JFFS2_NODE_ACCURATE | 3)
DECL|macro|JFFS2_NODETYPE_PADDING
mdefine_line|#define JFFS2_NODETYPE_PADDING (JFFS2_FEATURE_RWCOMPAT_DELETE | JFFS2_NODE_ACCURATE | 4)
singleline_comment|// Maybe later...
singleline_comment|//#define JFFS2_NODETYPE_CHECKPOINT (JFFS2_FEATURE_RWCOMPAT_DELETE | JFFS2_NODE_ACCURATE | 3)
singleline_comment|//#define JFFS2_NODETYPE_OPTIONS (JFFS2_FEATURE_RWCOMPAT_COPY | JFFS2_NODE_ACCURATE | 4)
DECL|macro|JFFS2_INO_FLAG_PREREAD
mdefine_line|#define JFFS2_INO_FLAG_PREREAD&t;  1&t;/* Do read_inode() for this one at &n;&t;&t;&t;&t;&t;   mount time, don&squot;t wait for it to &n;&t;&t;&t;&t;&t;   happen later */
DECL|macro|JFFS2_INO_FLAG_USERCOMPR
mdefine_line|#define JFFS2_INO_FLAG_USERCOMPR  2&t;/* User has requested a specific &n;&t;&t;&t;&t;&t;   compression type */
multiline_comment|/* These can go once we&squot;ve made sure we&squot;ve caught all uses without&n;   byteswapping */
r_typedef
r_struct
(brace
DECL|member|v32
r_uint32
id|v32
suffix:semicolon
DECL|typedef|jint32_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|jint32_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|m
r_uint32
id|m
suffix:semicolon
DECL|typedef|jmode_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|jmode_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|v16
r_uint16
id|v16
suffix:semicolon
DECL|typedef|jint16_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|jint16_t
suffix:semicolon
DECL|struct|jffs2_unknown_node
r_struct
id|jffs2_unknown_node
(brace
multiline_comment|/* All start like this */
DECL|member|magic
id|jint16_t
id|magic
suffix:semicolon
DECL|member|nodetype
id|jint16_t
id|nodetype
suffix:semicolon
DECL|member|totlen
id|jint32_t
id|totlen
suffix:semicolon
multiline_comment|/* So we can skip over nodes we don&squot;t grok */
DECL|member|hdr_crc
id|jint32_t
id|hdr_crc
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|jffs2_raw_dirent
r_struct
id|jffs2_raw_dirent
(brace
DECL|member|magic
id|jint16_t
id|magic
suffix:semicolon
DECL|member|nodetype
id|jint16_t
id|nodetype
suffix:semicolon
multiline_comment|/* == JFFS_NODETYPE_DIRENT */
DECL|member|totlen
id|jint32_t
id|totlen
suffix:semicolon
DECL|member|hdr_crc
id|jint32_t
id|hdr_crc
suffix:semicolon
DECL|member|pino
id|jint32_t
id|pino
suffix:semicolon
DECL|member|version
id|jint32_t
id|version
suffix:semicolon
DECL|member|ino
id|jint32_t
id|ino
suffix:semicolon
multiline_comment|/* == zero for unlink */
DECL|member|mctime
id|jint32_t
id|mctime
suffix:semicolon
DECL|member|nsize
r_uint8
id|nsize
suffix:semicolon
DECL|member|type
r_uint8
id|type
suffix:semicolon
DECL|member|unused
r_uint8
id|unused
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|node_crc
id|jint32_t
id|node_crc
suffix:semicolon
DECL|member|name_crc
id|jint32_t
id|name_crc
suffix:semicolon
DECL|member|name
r_uint8
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* The JFFS2 raw inode structure: Used for storage on physical media.  */
multiline_comment|/* The uid, gid, atime, mtime and ctime members could be longer, but &n;   are left like this for space efficiency. If and when people decide&n;   they really need them extended, it&squot;s simple enough to add support for&n;   a new type of raw node.&n;*/
DECL|struct|jffs2_raw_inode
r_struct
id|jffs2_raw_inode
(brace
DECL|member|magic
id|jint16_t
id|magic
suffix:semicolon
multiline_comment|/* A constant magic number.  */
DECL|member|nodetype
id|jint16_t
id|nodetype
suffix:semicolon
multiline_comment|/* == JFFS_NODETYPE_INODE */
DECL|member|totlen
id|jint32_t
id|totlen
suffix:semicolon
multiline_comment|/* Total length of this node (inc data, etc.) */
DECL|member|hdr_crc
id|jint32_t
id|hdr_crc
suffix:semicolon
DECL|member|ino
id|jint32_t
id|ino
suffix:semicolon
multiline_comment|/* Inode number.  */
DECL|member|version
id|jint32_t
id|version
suffix:semicolon
multiline_comment|/* Version number.  */
DECL|member|mode
id|jmode_t
id|mode
suffix:semicolon
multiline_comment|/* The file&squot;s type or mode.  */
DECL|member|uid
id|jint16_t
id|uid
suffix:semicolon
multiline_comment|/* The file&squot;s owner.  */
DECL|member|gid
id|jint16_t
id|gid
suffix:semicolon
multiline_comment|/* The file&squot;s group.  */
DECL|member|isize
id|jint32_t
id|isize
suffix:semicolon
multiline_comment|/* Total resultant size of this inode (used for truncations)  */
DECL|member|atime
id|jint32_t
id|atime
suffix:semicolon
multiline_comment|/* Last access time.  */
DECL|member|mtime
id|jint32_t
id|mtime
suffix:semicolon
multiline_comment|/* Last modification time.  */
DECL|member|ctime
id|jint32_t
id|ctime
suffix:semicolon
multiline_comment|/* Change time.  */
DECL|member|offset
id|jint32_t
id|offset
suffix:semicolon
multiline_comment|/* Where to begin to write.  */
DECL|member|csize
id|jint32_t
id|csize
suffix:semicolon
multiline_comment|/* (Compressed) data size */
DECL|member|dsize
id|jint32_t
id|dsize
suffix:semicolon
multiline_comment|/* Size of the node&squot;s data. (after decompression) */
DECL|member|compr
r_uint8
id|compr
suffix:semicolon
multiline_comment|/* Compression algorithm used */
DECL|member|usercompr
r_uint8
id|usercompr
suffix:semicolon
multiline_comment|/* Compression algorithm requested by the user */
DECL|member|flags
id|jint16_t
id|flags
suffix:semicolon
multiline_comment|/* See JFFS2_INO_FLAG_* */
DECL|member|data_crc
id|jint32_t
id|data_crc
suffix:semicolon
multiline_comment|/* CRC for the (compressed) data.  */
DECL|member|node_crc
id|jint32_t
id|node_crc
suffix:semicolon
multiline_comment|/* CRC for the raw inode (excluding data)  */
DECL|member|data
r_uint8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|union|jffs2_node_union
r_union
id|jffs2_node_union
(brace
DECL|member|i
r_struct
id|jffs2_raw_inode
id|i
suffix:semicolon
DECL|member|d
r_struct
id|jffs2_raw_dirent
id|d
suffix:semicolon
DECL|member|u
r_struct
id|jffs2_unknown_node
id|u
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __LINUX_JFFS2_H__ */
eof
