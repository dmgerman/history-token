multiline_comment|/*&n; * Copyright (C) 2002-2003  David McCullough &lt;davidm@snapgear.com&gt;&n; * Copyright (C) 1998       Kenneth Albanowski &lt;kjahds@kjahds.com&gt;&n; *                          The Silver Hammer Group, Ltd.&n; *&n; * This file provides the definitions and structures needed to&n; * support uClinux flat-format executables.&n; */
macro_line|#ifndef _LINUX_FLAT_H
DECL|macro|_LINUX_FLAT_H
mdefine_line|#define _LINUX_FLAT_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/flat.h&gt;
macro_line|#endif
DECL|macro|FLAT_VERSION
mdefine_line|#define&t;FLAT_VERSION&t;&t;&t;0x00000004L
macro_line|#ifdef CONFIG_BINFMT_SHARED_FLAT
DECL|macro|MAX_SHARED_LIBS
mdefine_line|#define&t;MAX_SHARED_LIBS&t;&t;&t;(4)
macro_line|#else
DECL|macro|MAX_SHARED_LIBS
mdefine_line|#define&t;MAX_SHARED_LIBS&t;&t;&t;(1)
macro_line|#endif
multiline_comment|/*&n; * To make everything easier to port and manage cross platform&n; * development,  all fields are in network byte order.&n; */
DECL|struct|flat_hdr
r_struct
id|flat_hdr
(brace
DECL|member|magic
r_char
id|magic
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|rev
r_int
r_int
id|rev
suffix:semicolon
multiline_comment|/* version (as above) */
DECL|member|entry
r_int
r_int
id|entry
suffix:semicolon
multiline_comment|/* Offset of first executable instruction&n;&t;                               with text segment from beginning of file */
DECL|member|data_start
r_int
r_int
id|data_start
suffix:semicolon
multiline_comment|/* Offset of data segment from beginning of&n;&t;                               file */
DECL|member|data_end
r_int
r_int
id|data_end
suffix:semicolon
multiline_comment|/* Offset of end of data segment&n;&t;                               from beginning of file */
DECL|member|bss_end
r_int
r_int
id|bss_end
suffix:semicolon
multiline_comment|/* Offset of end of bss segment from beginning&n;&t;                               of file */
multiline_comment|/* (It is assumed that data_end through bss_end forms the bss segment.) */
DECL|member|stack_size
r_int
r_int
id|stack_size
suffix:semicolon
multiline_comment|/* Size of stack, in bytes */
DECL|member|reloc_start
r_int
r_int
id|reloc_start
suffix:semicolon
multiline_comment|/* Offset of relocation records from&n;&t;                               beginning of file */
DECL|member|reloc_count
r_int
r_int
id|reloc_count
suffix:semicolon
multiline_comment|/* Number of relocation records */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|build_date
r_int
r_int
id|build_date
suffix:semicolon
multiline_comment|/* When the program/library was built */
DECL|member|filler
r_int
r_int
id|filler
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Reservered, set to zero */
)brace
suffix:semicolon
DECL|macro|FLAT_FLAG_RAM
mdefine_line|#define FLAT_FLAG_RAM    0x0001 /* load program entirely into RAM */
DECL|macro|FLAT_FLAG_GOTPIC
mdefine_line|#define FLAT_FLAG_GOTPIC 0x0002 /* program is PIC with GOT */
DECL|macro|FLAT_FLAG_GZIP
mdefine_line|#define FLAT_FLAG_GZIP   0x0004 /* all but the header is compressed */
DECL|macro|FLAT_FLAG_GZDATA
mdefine_line|#define FLAT_FLAG_GZDATA 0x0008 /* only data/relocs are compressed (for XIP) */
DECL|macro|FLAT_FLAG_KTRACE
mdefine_line|#define FLAT_FLAG_KTRACE 0x0010 /* output useful kernel trace for debugging */
macro_line|#ifdef __KERNEL__ /* so systems without linux headers can compile the apps */
multiline_comment|/*&n; * While it would be nice to keep this header clean,  users of older&n; * tools still need this support in the kernel.  So this section is&n; * purely for compatibility with old tool chains.&n; *&n; * DO NOT make changes or enhancements to the old format please,  just work&n; *        with the format above,  except to fix bugs with old format support.&n; */
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|OLD_FLAT_VERSION
mdefine_line|#define&t;OLD_FLAT_VERSION&t;&t;&t;0x00000002L
DECL|macro|OLD_FLAT_RELOC_TYPE_TEXT
mdefine_line|#define OLD_FLAT_RELOC_TYPE_TEXT&t;0
DECL|macro|OLD_FLAT_RELOC_TYPE_DATA
mdefine_line|#define OLD_FLAT_RELOC_TYPE_DATA&t;1
DECL|macro|OLD_FLAT_RELOC_TYPE_BSS
mdefine_line|#define OLD_FLAT_RELOC_TYPE_BSS&t;&t;2
r_typedef
r_union
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
r_struct
(brace
macro_line|# if defined(mc68000) &amp;&amp; !defined(CONFIG_COLDFIRE)
DECL|member|offset
r_int
r_int
id|offset
suffix:colon
l_int|30
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:colon
l_int|2
suffix:semicolon
DECL|macro|OLD_FLAT_FLAG_RAM
macro_line|#   &t;define OLD_FLAT_FLAG_RAM    0x1 /* load program entirely into RAM */
macro_line|# elif defined(__BIG_ENDIAN_BITFIELD)
r_int
r_int
id|type
suffix:colon
l_int|2
suffix:semicolon
r_int
r_int
id|offset
suffix:colon
l_int|30
suffix:semicolon
macro_line|#   &t;define OLD_FLAT_FLAG_RAM    0x1 /* load program entirely into RAM */
macro_line|# elif defined(__LITTLE_ENDIAN_BITFIELD)
r_int
r_int
id|offset
suffix:colon
l_int|30
suffix:semicolon
r_int
r_int
id|type
suffix:colon
l_int|2
suffix:semicolon
macro_line|#   &t;define OLD_FLAT_FLAG_RAM    0x1 /* load program entirely into RAM */
macro_line|# else
macro_line|#   &t;error &quot;Unknown bitfield order for flat files.&quot;
macro_line|# endif
DECL|member|reloc
)brace
id|reloc
suffix:semicolon
DECL|typedef|flat_v2_reloc_t
)brace
id|flat_v2_reloc_t
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_FLAT_H */
eof
