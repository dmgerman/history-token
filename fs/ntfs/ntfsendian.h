multiline_comment|/*&n; *  ntfsendian.h&n; *&n; *  Copyright (C) 1998, 1999 Martin von L&#xfffd;wis&n; *  Copyright (C) 1998 Joseph Malicki&n; *  Copyright (C) 1999 Werner Seiler&n; */
macro_line|#ifdef __linux__
multiline_comment|/* This defines __cpu_to_le16 on Linux 2.1 and higher. */
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#endif
macro_line|#ifdef __cpu_to_le16
DECL|macro|CPU_TO_LE16
mdefine_line|#define CPU_TO_LE16(a) __cpu_to_le16(a)
DECL|macro|CPU_TO_LE32
mdefine_line|#define CPU_TO_LE32(a) __cpu_to_le32(a)
DECL|macro|CPU_TO_LE64
mdefine_line|#define CPU_TO_LE64(a) __cpu_to_le64(a)
DECL|macro|LE16_TO_CPU
mdefine_line|#define LE16_TO_CPU(a) __cpu_to_le16(a)
DECL|macro|LE32_TO_CPU
mdefine_line|#define LE32_TO_CPU(a) __cpu_to_le32(a)
DECL|macro|LE64_TO_CPU
mdefine_line|#define LE64_TO_CPU(a) __cpu_to_le64(a)
macro_line|#else
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|CPU_TO_LE16
mdefine_line|#define CPU_TO_LE16(a) (a)
DECL|macro|CPU_TO_LE32
mdefine_line|#define CPU_TO_LE32(a) (a)
DECL|macro|CPU_TO_LE64
mdefine_line|#define CPU_TO_LE64(a) (a)
DECL|macro|LE16_TO_CPU
mdefine_line|#define LE16_TO_CPU(a) (a)
DECL|macro|LE32_TO_CPU
mdefine_line|#define LE32_TO_CPU(a) (a)
DECL|macro|LE64_TO_CPU
mdefine_line|#define LE64_TO_CPU(a) (a)
macro_line|#else
multiline_comment|/* Routines for big-endian machines */
macro_line|#ifdef __BIG_ENDIAN
multiline_comment|/* We hope its big-endian, not PDP-endian :) */
DECL|macro|CPU_TO_LE16
mdefine_line|#define CPU_TO_LE16(a) ((((a)&amp;0xFF) &lt;&lt; 8)|((a) &gt;&gt; 8))
DECL|macro|CPU_TO_LE32
mdefine_line|#define CPU_TO_LE32(a) ((((a) &amp; 0xFF) &lt;&lt; 24) | (((a) &amp; 0xFF00) &lt;&lt; 8) | &bslash;&n;&t;&t;&t;(((a) &amp; 0xFF0000) &gt;&gt; 8) | ((a) &gt;&gt; 24))
DECL|macro|CPU_TO_LE64
mdefine_line|#define CPU_TO_LE64(a) ((CPU_TO_LE32(a)&lt;&lt;32)|CPU_TO_LE32((a)&gt;&gt;32)
DECL|macro|LE16_TO_CPU
mdefine_line|#define LE16_TO_CPU(a) CPU_TO_LE16(a)
DECL|macro|LE32_TO_CPU
mdefine_line|#define LE32_TO_CPU(a) CPU_TO_LE32(a)
DECL|macro|LE64_TO_CPU
mdefine_line|#define LE64_TO_CPU(a) CPU_TO_LE64(a)
macro_line|#else
macro_line|#error Please define Endianness - __BIG_ENDIAN or __LITTLE_ENDIAN or add OS-specific macros
macro_line|#endif /* __BIG_ENDIAN */
macro_line|#endif /* __LITTLE_ENDIAN */
macro_line|#endif /* __cpu_to_le16 */
DECL|macro|NTFS_GETU8
mdefine_line|#define NTFS_GETU8(p)      (*(ntfs_u8*)(p))
DECL|macro|NTFS_GETU16
mdefine_line|#define NTFS_GETU16(p)     ((ntfs_u16)LE16_TO_CPU(*(ntfs_u16*)(p)))
DECL|macro|NTFS_GETU24
mdefine_line|#define NTFS_GETU24(p)     ((ntfs_u32)NTFS_GETU16(p) | ((ntfs_u32)NTFS_GETU8(((char*)(p))+2)&lt;&lt;16))
DECL|macro|NTFS_GETU32
mdefine_line|#define NTFS_GETU32(p)     ((ntfs_u32)LE32_TO_CPU(*(ntfs_u32*)(p)))
DECL|macro|NTFS_GETU40
mdefine_line|#define NTFS_GETU40(p)     ((ntfs_u64)NTFS_GETU32(p)|(((ntfs_u64)NTFS_GETU8(((char*)(p))+4))&lt;&lt;32))
DECL|macro|NTFS_GETU48
mdefine_line|#define NTFS_GETU48(p)     ((ntfs_u64)NTFS_GETU32(p)|(((ntfs_u64)NTFS_GETU16(((char*)(p))+4))&lt;&lt;32))
DECL|macro|NTFS_GETU56
mdefine_line|#define NTFS_GETU56(p)     ((ntfs_u64)NTFS_GETU32(p)|(((ntfs_u64)NTFS_GETU24(((char*)(p))+4))&lt;&lt;32))
DECL|macro|NTFS_GETU64
mdefine_line|#define NTFS_GETU64(p)     ((ntfs_u64)LE64_TO_CPU(*(ntfs_u64*)(p)))
multiline_comment|/* Macros writing unsigned integers */
DECL|macro|NTFS_PUTU8
mdefine_line|#define NTFS_PUTU8(p,v)      ((*(ntfs_u8*)(p))=(v))
DECL|macro|NTFS_PUTU16
mdefine_line|#define NTFS_PUTU16(p,v)     ((*(ntfs_u16*)(p))=CPU_TO_LE16(v))
DECL|macro|NTFS_PUTU24
mdefine_line|#define NTFS_PUTU24(p,v)     NTFS_PUTU16(p,(v) &amp; 0xFFFF);&bslash;&n;                             NTFS_PUTU8(((char*)(p))+2,(v)&gt;&gt;16)
DECL|macro|NTFS_PUTU32
mdefine_line|#define NTFS_PUTU32(p,v)     ((*(ntfs_u32*)(p))=CPU_TO_LE32(v))
DECL|macro|NTFS_PUTU64
mdefine_line|#define NTFS_PUTU64(p,v)     ((*(ntfs_u64*)(p))=CPU_TO_LE64(v))
multiline_comment|/* Macros reading signed integers */
DECL|macro|NTFS_GETS8
mdefine_line|#define NTFS_GETS8(p)        ((*(ntfs_s8*)(p)))
DECL|macro|NTFS_GETS16
mdefine_line|#define NTFS_GETS16(p)       ((ntfs_s16)LE16_TO_CPU(*(short*)(p)))
DECL|macro|NTFS_GETS24
mdefine_line|#define NTFS_GETS24(p)       (NTFS_GETU24(p) &lt; 0x800000 ? (int)NTFS_GETU24(p) : (int)(NTFS_GETU24(p) - 0x1000000))
DECL|macro|NTFS_GETS32
mdefine_line|#define NTFS_GETS32(p)       ((ntfs_s32)LE32_TO_CPU(*(int*)(p)))
DECL|macro|NTFS_GETS40
mdefine_line|#define NTFS_GETS40(p)       (((ntfs_s64)NTFS_GETU32(p)) | (((ntfs_s64)NTFS_GETS8(((char*)(p))+4)) &lt;&lt; 32))
DECL|macro|NTFS_GETS48
mdefine_line|#define NTFS_GETS48(p)       (((ntfs_s64)NTFS_GETU32(p)) | (((ntfs_s64)NTFS_GETS16(((char*)(p))+4)) &lt;&lt; 32))
DECL|macro|NTFS_GETS56
mdefine_line|#define NTFS_GETS56(p)       (((ntfs_s64)NTFS_GETU32(p)) | (((ntfs_s64)NTFS_GETS24(((char*)(p))+4)) &lt;&lt; 32))
DECL|macro|NTFS_GETS64
mdefine_line|#define NTFS_GETS64(p)&t;     ((ntfs_s64)NTFS_GETU64(p))
DECL|macro|NTFS_PUTS8
mdefine_line|#define NTFS_PUTS8(p,v)      NTFS_PUTU8(p,v)
DECL|macro|NTFS_PUTS16
mdefine_line|#define NTFS_PUTS16(p,v)     NTFS_PUTU16(p,v)
DECL|macro|NTFS_PUTS24
mdefine_line|#define NTFS_PUTS24(p,v)     NTFS_PUTU24(p,v)
DECL|macro|NTFS_PUTS32
mdefine_line|#define NTFS_PUTS32(p,v)     NTFS_PUTU32(p,v)
eof
