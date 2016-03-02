multiline_comment|/*&n; * Non-machine dependent bootinfo structure.  Basic idea&n; * borrowed from the m68k.&n; *&n; * Copyright (C) 1999 Cort Dougan &lt;cort@ppc.kernel.org&gt;&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_BOOTINFO_H
DECL|macro|_PPC_BOOTINFO_H
mdefine_line|#define _PPC_BOOTINFO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#if defined(CONFIG_APUS) &amp;&amp; !defined(__BOOTER__)
macro_line|#include &lt;asm-m68k/bootinfo.h&gt;
macro_line|#else
DECL|struct|bi_record
r_struct
id|bi_record
(brace
DECL|member|tag
r_int
r_int
id|tag
suffix:semicolon
multiline_comment|/* tag ID */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of record (in bytes) */
DECL|member|data
r_int
r_int
id|data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* data */
)brace
suffix:semicolon
DECL|macro|BI_FIRST
mdefine_line|#define BI_FIRST&t;&t;0x1010  /* first record - marker */
DECL|macro|BI_LAST
mdefine_line|#define BI_LAST&t;&t;&t;0x1011&t;/* last record - marker */
DECL|macro|BI_CMD_LINE
mdefine_line|#define BI_CMD_LINE&t;&t;0x1012
DECL|macro|BI_BOOTLOADER_ID
mdefine_line|#define BI_BOOTLOADER_ID&t;0x1013
DECL|macro|BI_INITRD
mdefine_line|#define BI_INITRD&t;&t;0x1014
DECL|macro|BI_SYSMAP
mdefine_line|#define BI_SYSMAP&t;&t;0x1015
DECL|macro|BI_MACHTYPE
mdefine_line|#define BI_MACHTYPE&t;&t;0x1016
DECL|macro|BI_MEMSIZE
mdefine_line|#define BI_MEMSIZE&t;&t;0x1017
DECL|macro|BI_BOARD_INFO
mdefine_line|#define BI_BOARD_INFO&t;&t;0x1018
r_extern
r_struct
id|bi_record
op_star
id|find_bootinfo
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|bootinfo_init
c_func
(paren
r_struct
id|bi_record
op_star
id|rec
)paren
suffix:semicolon
r_extern
r_void
id|bootinfo_append
c_func
(paren
r_int
r_int
id|tag
comma
r_int
r_int
id|size
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|parse_bootinfo
c_func
(paren
r_struct
id|bi_record
op_star
id|rec
)paren
suffix:semicolon
r_extern
r_int
r_int
id|boot_mem_size
suffix:semicolon
r_static
r_inline
r_struct
id|bi_record
op_star
DECL|function|bootinfo_addr
id|bootinfo_addr
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
r_return
(paren
r_struct
id|bi_record
op_star
)paren
id|_ALIGN
c_func
(paren
(paren
id|offset
)paren
op_plus
(paren
l_int|1
op_lshift
l_int|20
)paren
op_minus
l_int|1
comma
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_APUS */
macro_line|#endif /* _PPC_BOOTINFO_H */
macro_line|#endif /* __KERNEL__ */
eof
