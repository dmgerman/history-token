multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001, 2002 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&n; *&n; * The original JFFS, from which the design for JFFS2 was derived,&n; * was designed and implemented by Axis Communications AB.&n; *&n; * The contents of this file are subject to the Red Hat eCos Public&n; * License Version 1.1 (the &quot;Licence&quot;); you may not use this file&n; * except in compliance with the Licence.  You may obtain a copy of&n; * the Licence at http://www.redhat.com/&n; *&n; * Software distributed under the Licence is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.&n; * See the Licence for the specific language governing rights and&n; * limitations under the Licence.&n; *&n; * The Original Code is JFFS2 - Journalling Flash File System, version 2&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in&n; * which case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use your&n; * version of this file under the RHEPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the RHEPL or the GPL.&n; *&n; * $Id: jffs2.h,v 1.23 2002/02/21 17:03:45 dwmw2 Exp $&n; *&n; */
macro_line|#ifndef __LINUX_JFFS2_H__
DECL|macro|__LINUX_JFFS2_H__
mdefine_line|#define __LINUX_JFFS2_H__
DECL|macro|JFFS2_SUPER_MAGIC
mdefine_line|#define JFFS2_SUPER_MAGIC 0x72b6
multiline_comment|/* Values we may expect to find in the &squot;magic&squot; field */
DECL|macro|JFFS2_OLD_MAGIC_BITMASK
mdefine_line|#define JFFS2_OLD_MAGIC_BITMASK 0x1984
DECL|macro|JFFS2_MAGIC_BITMASK
mdefine_line|#define JFFS2_MAGIC_BITMASK 0x1985
DECL|macro|KSAMTIB_CIGAM_2SFFJ
mdefine_line|#define KSAMTIB_CIGAM_2SFFJ 0x5981 /* For detecting wrong-endian fs */
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
DECL|struct|jffs2_unknown_node
r_struct
id|jffs2_unknown_node
(brace
multiline_comment|/* All start like this */
DECL|member|magic
r_uint16
id|magic
suffix:semicolon
DECL|member|nodetype
r_uint16
id|nodetype
suffix:semicolon
DECL|member|totlen
r_uint32
id|totlen
suffix:semicolon
multiline_comment|/* So we can skip over nodes we don&squot;t grok */
DECL|member|hdr_crc
r_uint32
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
r_uint16
id|magic
suffix:semicolon
DECL|member|nodetype
r_uint16
id|nodetype
suffix:semicolon
multiline_comment|/* == JFFS_NODETYPE_DIRENT */
DECL|member|totlen
r_uint32
id|totlen
suffix:semicolon
DECL|member|hdr_crc
r_uint32
id|hdr_crc
suffix:semicolon
DECL|member|pino
r_uint32
id|pino
suffix:semicolon
DECL|member|version
r_uint32
id|version
suffix:semicolon
DECL|member|ino
r_uint32
id|ino
suffix:semicolon
multiline_comment|/* == zero for unlink */
DECL|member|mctime
r_uint32
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
r_uint32
id|node_crc
suffix:semicolon
DECL|member|name_crc
r_uint32
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
r_uint16
id|magic
suffix:semicolon
multiline_comment|/* A constant magic number.  */
DECL|member|nodetype
r_uint16
id|nodetype
suffix:semicolon
multiline_comment|/* == JFFS_NODETYPE_INODE */
DECL|member|totlen
r_uint32
id|totlen
suffix:semicolon
multiline_comment|/* Total length of this node (inc data, etc.) */
DECL|member|hdr_crc
r_uint32
id|hdr_crc
suffix:semicolon
DECL|member|ino
r_uint32
id|ino
suffix:semicolon
multiline_comment|/* Inode number.  */
DECL|member|version
r_uint32
id|version
suffix:semicolon
multiline_comment|/* Version number.  */
DECL|member|mode
r_uint32
id|mode
suffix:semicolon
multiline_comment|/* The file&squot;s type or mode.  */
DECL|member|uid
r_uint16
id|uid
suffix:semicolon
multiline_comment|/* The file&squot;s owner.  */
DECL|member|gid
r_uint16
id|gid
suffix:semicolon
multiline_comment|/* The file&squot;s group.  */
DECL|member|isize
r_uint32
id|isize
suffix:semicolon
multiline_comment|/* Total resultant size of this inode (used for truncations)  */
DECL|member|atime
r_uint32
id|atime
suffix:semicolon
multiline_comment|/* Last access time.  */
DECL|member|mtime
r_uint32
id|mtime
suffix:semicolon
multiline_comment|/* Last modification time.  */
DECL|member|ctime
r_uint32
id|ctime
suffix:semicolon
multiline_comment|/* Change time.  */
DECL|member|offset
r_uint32
id|offset
suffix:semicolon
multiline_comment|/* Where to begin to write.  */
DECL|member|csize
r_uint32
id|csize
suffix:semicolon
multiline_comment|/* (Compressed) data size */
DECL|member|dsize
r_uint32
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
r_uint16
id|flags
suffix:semicolon
multiline_comment|/* See JFFS2_INO_FLAG_* */
DECL|member|data_crc
r_uint32
id|data_crc
suffix:semicolon
multiline_comment|/* CRC for the (compressed) data.  */
DECL|member|node_crc
r_uint32
id|node_crc
suffix:semicolon
multiline_comment|/* CRC for the raw inode (excluding data)  */
singleline_comment|//&t;uint8_t data[dsize];
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
