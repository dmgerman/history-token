multiline_comment|/* &n; * linux/include/linux/hfs_fs.h&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * The source code distribution of the Columbia AppleTalk Package for&n; * UNIX, version 6.0, (CAP) was used as a specification of the&n; * location and format of files used by CAP&squot;s Aufs.  No code from CAP&n; * appears in hfs_fs.  hfs_fs is not a work ``derived&squot;&squot; from CAP in&n; * the sense of intellectual property law.&n; *&n; * The source code distributions of Netatalk, versions 1.3.3b2 and&n; * 1.4b2, were used as a specification of the location and format of&n; * files used by Netatalk&squot;s afpd.  No code from Netatalk appears in&n; * hfs_fs.  hfs_fs is not a work ``derived&squot;&squot; from Netatalk in the&n; * sense of intellectual property law.&n; */
macro_line|#ifndef _LINUX_HFS_FS_H
DECL|macro|_LINUX_HFS_FS_H
mdefine_line|#define _LINUX_HFS_FS_H
macro_line|#include &lt;linux/hfs_sysdep.h&gt;
multiline_comment|/* magic numbers for Apple Double header files */
DECL|macro|HFS_DBL_MAGIC
mdefine_line|#define HFS_DBL_MAGIC&t;&t;0x00051607
DECL|macro|HFS_SNGL_MAGIC
mdefine_line|#define HFS_SNGL_MAGIC&t;&t;0x00051600
DECL|macro|HFS_HDR_VERSION_1
mdefine_line|#define HFS_HDR_VERSION_1&t;0x00010000
DECL|macro|HFS_HDR_VERSION_2
mdefine_line|#define HFS_HDR_VERSION_2&t;0x00020000
multiline_comment|/* magic numbers for various internal structures */
DECL|macro|HFS_INO_MAGIC
mdefine_line|#define HFS_INO_MAGIC&t;&t;0x4821
DECL|macro|HFS_SB_MAGIC
mdefine_line|#define HFS_SB_MAGIC&t;&t;0x4822
multiline_comment|/* The space used for the AppleDouble or AppleSingle headers */
DECL|macro|HFS_DBL_HDR_LEN
mdefine_line|#define HFS_DBL_HDR_LEN&t;&t;1024
multiline_comment|/* The space used for the Netatalk header */
DECL|macro|HFS_NAT_HDR_LEN
mdefine_line|#define HFS_NAT_HDR_LEN&t;&t;1024  /* 589 for an exact match */
multiline_comment|/* Macros to extract CNID and file &quot;type&quot; from the Linux inode number */
DECL|macro|HFS_CNID
mdefine_line|#define HFS_CNID(X)&t;((X) &amp; 0x3FFFFFFF)
DECL|macro|HFS_ITYPE
mdefine_line|#define HFS_ITYPE(X)&t;((X) &amp; 0xC0000000)
multiline_comment|/* Macros to enumerate types */
DECL|macro|HFS_ITYPE_TO_INT
mdefine_line|#define HFS_ITYPE_TO_INT(X)&t;((X) &gt;&gt; 30)
DECL|macro|HFS_INT_TO_ITYPE
mdefine_line|#define HFS_INT_TO_ITYPE(X)&t;((X) &lt;&lt; 30)
multiline_comment|/* generic ITYPEs */
DECL|macro|HFS_ITYPE_0
mdefine_line|#define HFS_ITYPE_0&t;0x00000000
DECL|macro|HFS_ITYPE_1
mdefine_line|#define HFS_ITYPE_1&t;0x40000000
DECL|macro|HFS_ITYPE_2
mdefine_line|#define HFS_ITYPE_2&t;0x80000000
DECL|macro|HFS_ITYPE_3
mdefine_line|#define HFS_ITYPE_3&t;0xC0000000
DECL|macro|HFS_ITYPE_NORM
mdefine_line|#define HFS_ITYPE_NORM&t;HFS_ITYPE_0&t;/* &quot;normal&quot; directory or file */
multiline_comment|/* ITYPEs for CAP */
DECL|macro|HFS_CAP_NORM
mdefine_line|#define HFS_CAP_NORM&t;HFS_ITYPE_0&t;/* data fork or normal directory */
DECL|macro|HFS_CAP_DATA
mdefine_line|#define HFS_CAP_DATA&t;HFS_ITYPE_0&t;/* data fork of file */
DECL|macro|HFS_CAP_NDIR
mdefine_line|#define HFS_CAP_NDIR&t;HFS_ITYPE_0&t;/* normal directory */
DECL|macro|HFS_CAP_FNDR
mdefine_line|#define HFS_CAP_FNDR&t;HFS_ITYPE_1&t;/* finder info for file or dir */
DECL|macro|HFS_CAP_RSRC
mdefine_line|#define HFS_CAP_RSRC&t;HFS_ITYPE_2&t;/* resource fork of file */
DECL|macro|HFS_CAP_RDIR
mdefine_line|#define HFS_CAP_RDIR&t;HFS_ITYPE_2&t;/* .resource directory */
DECL|macro|HFS_CAP_FDIR
mdefine_line|#define HFS_CAP_FDIR&t;HFS_ITYPE_3&t;/* .finderinfo directory */
multiline_comment|/* ITYPEs for Apple Double */
DECL|macro|HFS_DBL_NORM
mdefine_line|#define HFS_DBL_NORM&t;HFS_ITYPE_0&t;/* data fork or directory */
DECL|macro|HFS_DBL_DATA
mdefine_line|#define HFS_DBL_DATA&t;HFS_ITYPE_0&t;/* data fork of file */
DECL|macro|HFS_DBL_DIR
mdefine_line|#define HFS_DBL_DIR&t;HFS_ITYPE_0&t;/* directory */
DECL|macro|HFS_DBL_HDR
mdefine_line|#define HFS_DBL_HDR&t;HFS_ITYPE_1&t;/* AD header of file or dir */
multiline_comment|/* ITYPEs for netatalk */
DECL|macro|HFS_NAT_NORM
mdefine_line|#define HFS_NAT_NORM&t;HFS_ITYPE_0&t;/* data fork or directory */
DECL|macro|HFS_NAT_DATA
mdefine_line|#define HFS_NAT_DATA&t;HFS_ITYPE_0&t;/* data fork of file */
DECL|macro|HFS_NAT_NDIR
mdefine_line|#define HFS_NAT_NDIR&t;HFS_ITYPE_0&t;/* normal directory */
DECL|macro|HFS_NAT_HDR
mdefine_line|#define HFS_NAT_HDR&t;HFS_ITYPE_1&t;/* AD header of file or dir */
DECL|macro|HFS_NAT_HDIR
mdefine_line|#define HFS_NAT_HDIR&t;HFS_ITYPE_2&t;/* directory holding AD headers */
multiline_comment|/* ITYPEs for Apple Single */
DECL|macro|HFS_SGL_NORM
mdefine_line|#define HFS_SGL_NORM&t;HFS_ITYPE_0&t;/* AppleSingle file or directory */
DECL|macro|HFS_SGL_SNGL
mdefine_line|#define HFS_SGL_SNGL&t;HFS_ITYPE_0&t;/* AppleSingle file */
DECL|macro|HFS_SGL_DIR
mdefine_line|#define HFS_SGL_DIR&t;HFS_ITYPE_0&t;/* directory */
DECL|macro|HFS_SGL_DINF
mdefine_line|#define HFS_SGL_DINF&t;HFS_ITYPE_1&t;/* %DirInfo for directory */
multiline_comment|/* IDs for elements of an AppleDouble or AppleSingle header */
DECL|macro|HFS_HDR_DATA
mdefine_line|#define HFS_HDR_DATA&t;1   /* data fork */
DECL|macro|HFS_HDR_RSRC
mdefine_line|#define HFS_HDR_RSRC&t;2   /* resource fork */
DECL|macro|HFS_HDR_FNAME
mdefine_line|#define HFS_HDR_FNAME&t;3   /* full (31-character) name */
DECL|macro|HFS_HDR_COMNT
mdefine_line|#define HFS_HDR_COMNT&t;4   /* comment */
DECL|macro|HFS_HDR_BWICN
mdefine_line|#define HFS_HDR_BWICN&t;5   /* b/w icon */
DECL|macro|HFS_HDR_CICON
mdefine_line|#define HFS_HDR_CICON&t;6   /* color icon info */
DECL|macro|HFS_HDR_OLDI
mdefine_line|#define HFS_HDR_OLDI&t;7   /* old file info */
DECL|macro|HFS_HDR_DATES
mdefine_line|#define HFS_HDR_DATES&t;8   /* file dates info */
DECL|macro|HFS_HDR_FINFO
mdefine_line|#define HFS_HDR_FINFO&t;9   /* Finder info */
DECL|macro|HFS_HDR_MACI
mdefine_line|#define HFS_HDR_MACI&t;10  /* Macintosh info */
DECL|macro|HFS_HDR_PRODOSI
mdefine_line|#define HFS_HDR_PRODOSI 11  /* ProDOS info */
DECL|macro|HFS_HDR_MSDOSI
mdefine_line|#define HFS_HDR_MSDOSI  12  /* MSDOS info */
DECL|macro|HFS_HDR_SNAME
mdefine_line|#define HFS_HDR_SNAME   13  /* short name */
DECL|macro|HFS_HDR_AFPI
mdefine_line|#define HFS_HDR_AFPI    14  /* AFP file info */
DECL|macro|HFS_HDR_DID
mdefine_line|#define HFS_HDR_DID     15  /* directory id */
DECL|macro|HFS_HDR_MAX
mdefine_line|#define HFS_HDR_MAX&t;16
multiline_comment|/*&n; * There are three time systems.  All three are based on seconds since&n; * a particular time/date.&n; *&t;Unix:&t;unsigned lil-endian since 00:00 GMT, Jan. 1, 1970&n; *&t;mac:&t;unsigned big-endian since 00:00 GMT, Jan. 1, 1904&n; *&t;header:&t;  SIGNED big-endian since 00:00 GMT, Jan. 1, 2000&n; *&n; */
DECL|macro|hfs_h_to_mtime
mdefine_line|#define hfs_h_to_mtime(ARG)&t;htonl((hfs_s32)ntohl(ARG)+3029529600U)
DECL|macro|hfs_m_to_htime
mdefine_line|#define hfs_m_to_htime(ARG)&t;((hfs_s32)htonl(ntohl(ARG)-3029529600U))
DECL|macro|hfs_h_to_utime
mdefine_line|#define hfs_h_to_utime(ARG)&t;((hfs_s32)hfs_to_utc(ntohl(ARG)+946684800U))
DECL|macro|hfs_u_to_htime
mdefine_line|#define hfs_u_to_htime(ARG)&t;((hfs_s32)htonl(hfs_from_utc(ARG)-946684800U))
DECL|macro|hfs_u_to_mtime
mdefine_line|#define hfs_u_to_mtime(ARG)&t;htonl(hfs_from_utc(ARG)+2082844800U)
DECL|macro|hfs_m_to_utime
mdefine_line|#define hfs_m_to_utime(ARG)&t;(hfs_to_utc(ntohl(ARG)-2082844800U))
multiline_comment|/*======== Data structures kept in memory ========*/
multiline_comment|/*&n; * A descriptor for a single entry within the header of an&n; * AppleDouble or AppleSingle header file.&n; * An array of these make up a table of contents for the file.&n; */
DECL|struct|hfs_hdr_descr
r_struct
id|hfs_hdr_descr
(brace
DECL|member|id
id|hfs_u32
id|id
suffix:semicolon
multiline_comment|/* The Apple assigned ID for the entry type */
DECL|member|offset
id|hfs_u32
id|offset
suffix:semicolon
multiline_comment|/* The offset to reach the entry */
DECL|member|length
id|hfs_u32
id|length
suffix:semicolon
multiline_comment|/* The length of the entry */
)brace
suffix:semicolon
multiline_comment|/*&n; * The info needed to reconstruct a given header layout&n; */
DECL|struct|hfs_hdr_layout
r_struct
id|hfs_hdr_layout
(brace
DECL|member|magic
id|hfs_u32
id|magic
suffix:semicolon
multiline_comment|/* AppleSingle or AppleDouble */
DECL|member|version
id|hfs_u32
id|version
suffix:semicolon
multiline_comment|/* 0x00010000 or 0x00020000 */
DECL|member|entries
id|hfs_u16
id|entries
suffix:semicolon
multiline_comment|/* How many entries used */
r_struct
id|hfs_hdr_descr
DECL|member|descr
id|descr
(braket
id|HFS_HDR_MAX
)braket
suffix:semicolon
multiline_comment|/* Descriptors */
r_struct
id|hfs_hdr_descr
DECL|member|order
op_star
id|order
(braket
id|HFS_HDR_MAX
)braket
suffix:semicolon
multiline_comment|/* &squot;descr&squot; ordered by offset */
)brace
suffix:semicolon
multiline_comment|/* header layout for netatalk&squot;s v1 appledouble file format */
DECL|struct|hfs_nat_hdr
r_struct
id|hfs_nat_hdr
(brace
DECL|member|magic
id|hfs_lword_t
id|magic
suffix:semicolon
DECL|member|version
id|hfs_lword_t
id|version
suffix:semicolon
DECL|member|homefs
id|hfs_byte_t
id|homefs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|entries
id|hfs_word_t
id|entries
suffix:semicolon
DECL|member|descrs
id|hfs_byte_t
id|descrs
(braket
l_int|12
op_star
l_int|5
)braket
suffix:semicolon
DECL|member|real_name
id|hfs_byte_t
id|real_name
(braket
l_int|255
)braket
suffix:semicolon
multiline_comment|/* id=3 */
DECL|member|comment
id|hfs_byte_t
id|comment
(braket
l_int|200
)braket
suffix:semicolon
multiline_comment|/* id=4 XXX: not yet implemented */
DECL|member|old_info
id|hfs_byte_t
id|old_info
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* id=7 */
DECL|member|finderinfo
id|hfs_u8
id|finderinfo
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* id=9 */
)brace
suffix:semicolon
multiline_comment|/* &n; * Default header layout for Netatalk and AppleDouble&n; */
DECL|struct|hfs_dbl_hdr
r_struct
id|hfs_dbl_hdr
(brace
DECL|member|magic
id|hfs_lword_t
id|magic
suffix:semicolon
DECL|member|version
id|hfs_lword_t
id|version
suffix:semicolon
DECL|member|filler
id|hfs_byte_t
id|filler
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|entries
id|hfs_word_t
id|entries
suffix:semicolon
DECL|member|descrs
id|hfs_byte_t
id|descrs
(braket
l_int|12
op_star
id|HFS_HDR_MAX
)braket
suffix:semicolon
DECL|member|real_name
id|hfs_byte_t
id|real_name
(braket
l_int|255
)braket
suffix:semicolon
multiline_comment|/* id=3 */
DECL|member|comment
id|hfs_byte_t
id|comment
(braket
l_int|200
)braket
suffix:semicolon
multiline_comment|/* id=4 XXX: not yet implemented */
DECL|member|create_time
id|hfs_u32
id|create_time
suffix:semicolon
multiline_comment|/* &bslash;&t;          */
DECL|member|modify_time
id|hfs_u32
id|modify_time
suffix:semicolon
multiline_comment|/*  | id=8 (or 7) */
DECL|member|backup_time
id|hfs_u32
id|backup_time
suffix:semicolon
multiline_comment|/*  |&t;          */
DECL|member|access_time
id|hfs_u32
id|access_time
suffix:semicolon
multiline_comment|/* /  (attributes with id=7) */
DECL|member|finderinfo
id|hfs_u8
id|finderinfo
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* id=9 */
DECL|member|fileinfo
id|hfs_u32
id|fileinfo
suffix:semicolon
multiline_comment|/* id=10 */
DECL|member|cnid
id|hfs_u32
id|cnid
suffix:semicolon
multiline_comment|/* id=15 */
DECL|member|short_name
id|hfs_u8
id|short_name
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* id=13 */
DECL|member|prodosi
id|hfs_u8
id|prodosi
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* id=11 */
)brace
suffix:semicolon
multiline_comment|/* finder metadata for CAP */
DECL|struct|hfs_cap_info
r_struct
id|hfs_cap_info
(brace
DECL|member|fi_fndr
id|hfs_byte_t
id|fi_fndr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Finder&squot;s info */
DECL|member|fi_attr
id|hfs_word_t
id|fi_attr
suffix:semicolon
multiline_comment|/* AFP attributes (f=file/d=dir) */
DECL|macro|HFS_AFP_INV
mdefine_line|#define HFS_AFP_INV             0x001   /* Invisible bit (f/d) */
DECL|macro|HFS_AFP_EXPFOLDER
mdefine_line|#define HFS_AFP_EXPFOLDER       0x002   /* exported folder (d) */
DECL|macro|HFS_AFP_MULTI
mdefine_line|#define HFS_AFP_MULTI           0x002   /* Multiuser bit (f) */
DECL|macro|HFS_AFP_SYS
mdefine_line|#define HFS_AFP_SYS             0x004   /* System bit (f/d) */
DECL|macro|HFS_AFP_DOPEN
mdefine_line|#define HFS_AFP_DOPEN           0x008   /* data fork already open (f) */
DECL|macro|HFS_AFP_MOUNTED
mdefine_line|#define HFS_AFP_MOUNTED         0x008   /* mounted folder (d) */
DECL|macro|HFS_AFP_ROPEN
mdefine_line|#define HFS_AFP_ROPEN           0x010   /* resource fork already open (f) */
DECL|macro|HFS_AFP_INEXPFOLDER
mdefine_line|#define HFS_AFP_INEXPFOLDER     0x010   /* folder in shared area (d) */
DECL|macro|HFS_AFP_WRI
mdefine_line|#define HFS_AFP_WRI&t;&t;0x020&t;/* Write inhibit bit (readonly) (f) */
DECL|macro|HFS_AFP_BACKUP
mdefine_line|#define HFS_AFP_BACKUP          0x040   /* backup needed bit (f/d)  */
DECL|macro|HFS_AFP_RNI
mdefine_line|#define HFS_AFP_RNI&t;&t;0x080&t;/* Rename inhibit bit (f/d) */
DECL|macro|HFS_AFP_DEI
mdefine_line|#define HFS_AFP_DEI&t;&t;0x100&t;/* Delete inhibit bit (f/d) */
DECL|macro|HFS_AFP_NOCOPY
mdefine_line|#define HFS_AFP_NOCOPY          0x400   /* Copy protect bit (f) */
DECL|macro|HFS_AFP_RDONLY
mdefine_line|#define HFS_AFP_RDONLY&t;(&t;HFS_AFP_WRI|HFS_AFP_RNI|HFS_AFP_DEI)
DECL|member|fi_magic1
id|hfs_byte_t
id|fi_magic1
suffix:semicolon
multiline_comment|/* Magic number: */
DECL|macro|HFS_CAP_MAGIC1
mdefine_line|#define HFS_CAP_MAGIC1&t;&t;0xFF
DECL|member|fi_version
id|hfs_byte_t
id|fi_version
suffix:semicolon
multiline_comment|/* Version of this structure: */
DECL|macro|HFS_CAP_VERSION
mdefine_line|#define HFS_CAP_VERSION&t;&t;0x10
DECL|member|fi_magic
id|hfs_byte_t
id|fi_magic
suffix:semicolon
multiline_comment|/* Another magic number: */
DECL|macro|HFS_CAP_MAGIC
mdefine_line|#define HFS_CAP_MAGIC&t;&t;0xDA
DECL|member|fi_bitmap
id|hfs_byte_t
id|fi_bitmap
suffix:semicolon
multiline_comment|/* Bitmap of which names are valid: */
DECL|macro|HFS_CAP_SHORTNAME
mdefine_line|#define HFS_CAP_SHORTNAME&t;0x01
DECL|macro|HFS_CAP_LONGNAME
mdefine_line|#define HFS_CAP_LONGNAME&t;0x02
DECL|member|fi_shortfilename
id|hfs_byte_t
id|fi_shortfilename
(braket
l_int|12
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* &quot;short name&quot; (unused) */
DECL|member|fi_macfilename
id|hfs_byte_t
id|fi_macfilename
(braket
l_int|32
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Original (Macintosh) name */
DECL|member|fi_comln
id|hfs_byte_t
id|fi_comln
suffix:semicolon
multiline_comment|/* Length of comment (always 0) */
DECL|member|fi_comnt
id|hfs_byte_t
id|fi_comnt
(braket
l_int|200
)braket
suffix:semicolon
multiline_comment|/* Finder comment (unused) */
multiline_comment|/* optional: &t;used by aufs only if compiled with USE_MAC_DATES */
DECL|member|fi_datemagic
id|hfs_byte_t
id|fi_datemagic
suffix:semicolon
multiline_comment|/* Magic number for dates extension: */
DECL|macro|HFS_CAP_DMAGIC
mdefine_line|#define HFS_CAP_DMAGIC&t;&t;0xDA
DECL|member|fi_datevalid
id|hfs_byte_t
id|fi_datevalid
suffix:semicolon
multiline_comment|/* Bitmap of which dates are valid: */
DECL|macro|HFS_CAP_MDATE
mdefine_line|#define HFS_CAP_MDATE&t;&t;0x01
DECL|macro|HFS_CAP_CDATE
mdefine_line|#define HFS_CAP_CDATE&t;&t;0x02
DECL|member|fi_ctime
id|hfs_lword_t
id|fi_ctime
suffix:semicolon
multiline_comment|/* Creation date (in AFP format) */
DECL|member|fi_mtime
id|hfs_lword_t
id|fi_mtime
suffix:semicolon
multiline_comment|/* Modify date (in AFP format) */
DECL|member|fi_utime
id|hfs_lword_t
id|fi_utime
suffix:semicolon
multiline_comment|/* Un*x time of last mtime change */
DECL|member|pad
id|hfs_byte_t
id|pad
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|typedef|hfs_rwret_t
r_typedef
id|ssize_t
id|hfs_rwret_t
suffix:semicolon
DECL|typedef|hfs_rwarg_t
r_typedef
r_int
id|hfs_rwarg_t
suffix:semicolon
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* Some forward declarations */
r_struct
id|hfs_fork
suffix:semicolon
r_struct
id|hfs_cat_key
suffix:semicolon
r_struct
id|hfs_cat_entry
suffix:semicolon
r_extern
r_struct
id|hfs_cat_entry
op_star
id|hfs_cat_get
c_func
(paren
r_struct
id|hfs_mdb
op_star
comma
r_const
r_struct
id|hfs_cat_key
op_star
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_int
id|hfs_create
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|hfs_mkdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|hfs_unlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_rmdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_rename
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/* dir_cap.c */
r_extern
r_const
r_struct
id|hfs_name
id|hfs_cap_reserved1
(braket
)braket
suffix:semicolon
r_extern
r_const
r_struct
id|hfs_name
id|hfs_cap_reserved2
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|hfs_cap_ndir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|hfs_cap_fdir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|hfs_cap_rdir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|hfs_cap_dir_operations
suffix:semicolon
r_extern
r_void
id|hfs_cap_drop_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_const
id|ino_t
)paren
suffix:semicolon
multiline_comment|/* dir_dbl.c */
r_extern
r_const
r_struct
id|hfs_name
id|hfs_dbl_reserved1
(braket
)braket
suffix:semicolon
r_extern
r_const
r_struct
id|hfs_name
id|hfs_dbl_reserved2
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|hfs_dbl_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|hfs_dbl_dir_operations
suffix:semicolon
r_extern
r_void
id|hfs_dbl_drop_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_const
id|ino_t
)paren
suffix:semicolon
multiline_comment|/* dir_nat.c */
r_extern
r_const
r_struct
id|hfs_name
id|hfs_nat_reserved1
(braket
)braket
suffix:semicolon
r_extern
r_const
r_struct
id|hfs_name
id|hfs_nat_reserved2
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|hfs_nat_ndir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|hfs_nat_hdir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|hfs_nat_dir_operations
suffix:semicolon
r_extern
r_void
id|hfs_nat_drop_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_const
id|ino_t
)paren
suffix:semicolon
multiline_comment|/* file.c */
r_extern
id|hfs_s32
id|hfs_do_read
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|hfs_fork
op_star
comma
id|hfs_u32
comma
r_char
op_star
comma
id|hfs_u32
comma
r_int
)paren
suffix:semicolon
r_extern
id|hfs_s32
id|hfs_do_write
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|hfs_fork
op_star
comma
id|hfs_u32
comma
r_const
r_char
op_star
comma
id|hfs_u32
)paren
suffix:semicolon
r_extern
r_void
id|hfs_file_fix_mode
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
id|entry
)paren
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|hfs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|hfs_file_operations
suffix:semicolon
multiline_comment|/* file_cap.c */
r_extern
r_struct
id|inode_operations
id|hfs_cap_info_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|hfs_cap_info_operations
suffix:semicolon
multiline_comment|/* file_hdr.c */
r_extern
r_struct
id|inode_operations
id|hfs_hdr_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|hfs_hdr_operations
suffix:semicolon
r_extern
r_const
r_struct
id|hfs_hdr_layout
id|hfs_dbl_fil_hdr_layout
suffix:semicolon
r_extern
r_const
r_struct
id|hfs_hdr_layout
id|hfs_dbl_dir_hdr_layout
suffix:semicolon
r_extern
r_const
r_struct
id|hfs_hdr_layout
id|hfs_nat_hdr_layout
suffix:semicolon
r_extern
r_const
r_struct
id|hfs_hdr_layout
id|hfs_nat2_hdr_layout
suffix:semicolon
r_extern
r_const
r_struct
id|hfs_hdr_layout
id|hfs_sngl_hdr_layout
suffix:semicolon
r_extern
r_void
id|hdr_truncate
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_void
id|hfs_put_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_notify_change
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_notify_change_cap
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_notify_change_hdr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|hfs_iget
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
comma
id|ino_t
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_cap_ifill
c_func
(paren
r_struct
id|inode
op_star
comma
id|ino_t
comma
r_const
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_dbl_ifill
c_func
(paren
r_struct
id|inode
op_star
comma
id|ino_t
comma
r_const
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_nat_ifill
c_func
(paren
r_struct
id|inode
op_star
comma
id|ino_t
comma
r_const
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_sngl_ifill
c_func
(paren
r_struct
id|inode
op_star
comma
id|ino_t
comma
r_const
r_int
)paren
suffix:semicolon
multiline_comment|/* super.c */
r_extern
r_int
id|hfs_fill_super
c_func
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* trans.c */
r_extern
r_void
id|hfs_colon2mac
c_func
(paren
r_struct
id|hfs_name
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_prcnt2mac
c_func
(paren
r_struct
id|hfs_name
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_triv2mac
c_func
(paren
r_struct
id|hfs_name
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_latin2mac
c_func
(paren
r_struct
id|hfs_name
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|hfs_mac2cap
c_func
(paren
r_char
op_star
comma
r_const
r_struct
id|hfs_name
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_mac2nat
c_func
(paren
r_char
op_star
comma
r_const
r_struct
id|hfs_name
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_mac2latin
c_func
(paren
r_char
op_star
comma
r_const
r_struct
id|hfs_name
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_mac2seven
c_func
(paren
r_char
op_star
comma
r_const
r_struct
id|hfs_name
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_mac2eight
c_func
(paren
r_char
op_star
comma
r_const
r_struct
id|hfs_name
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_mac2alpha
c_func
(paren
r_char
op_star
comma
r_const
r_struct
id|hfs_name
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_mac2triv
c_func
(paren
r_char
op_star
comma
r_const
r_struct
id|hfs_name
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_tolower
c_func
(paren
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#include &lt;linux/hfs_fs_i.h&gt;
DECL|function|HFS_I
r_static
r_inline
r_struct
id|hfs_inode_info
op_star
id|HFS_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|inode
comma
r_struct
id|hfs_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|macro|HFS_SB
mdefine_line|#define&t;HFS_SB(X)&t;(&amp;((X)-&gt;u.hfs_sb))
DECL|function|hfs_nameout
r_static
r_inline
r_void
id|hfs_nameout
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|hfs_name
op_star
id|out
comma
r_const
r_char
op_star
id|in
comma
r_int
id|len
)paren
(brace
id|HFS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_nameout
c_func
(paren
id|out
comma
id|in
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|hfs_namein
r_static
r_inline
r_int
id|hfs_namein
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_char
op_star
id|out
comma
r_const
r_struct
id|hfs_name
op_star
id|in
)paren
(brace
r_int
id|len
op_assign
id|HFS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_namein
c_func
(paren
id|out
comma
id|in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HFS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_lowercase
)paren
(brace
id|hfs_tolower
c_func
(paren
id|out
comma
id|len
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
