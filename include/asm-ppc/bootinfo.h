multiline_comment|/*&n; * BK Id: SCCS/s.bootinfo.h 1.7 05/23/01 00:38:42 cort&n; */
multiline_comment|/*&n; * Non-machine dependent bootinfo structure.  Basic idea&n; * borrowed from the m68k.&n; *&n; * Copyright (C) 1999 Cort Dougan &lt;cort@ppc.kernel.org&gt;&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_BOOTINFO_H
DECL|macro|_PPC_BOOTINFO_H
mdefine_line|#define _PPC_BOOTINFO_H
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#endif /* CONFIG_APUS */
multiline_comment|/*&n; * prom_init() is called very early on, before the kernel text&n; * and data have been mapped to KERNELBASE.  At this point the code&n; * is running at whatever address it has been loaded at, so&n; * references to extern and static variables must be relocated&n; * explicitly.  The procedure reloc_offset() returns the address&n; * we&squot;re currently running at minus the address we were linked at.&n; * (Note that strings count as static variables.)&n; *&n; * Because OF may have mapped I/O devices into the area starting at&n; * KERNELBASE, particularly on CHRP machines, we can&squot;t safely call&n; * OF once the kernel has been mapped to KERNELBASE.  Therefore all&n; * OF calls should be done within prom_init(), and prom_init()&n; * and all routines called within it must be careful to relocate&n; * references as necessary.&n; */
DECL|macro|PTRRELOC
mdefine_line|#define PTRRELOC(x)   ((typeof(x))((unsigned long)(x) + offset))
DECL|macro|PTRUNRELOC
mdefine_line|#define PTRUNRELOC(x) ((typeof(x))((unsigned long)(x) - offset))
DECL|macro|RELOC
mdefine_line|#define RELOC(x)      (*PTRRELOC(&amp;(x)))
macro_line|#endif /* _PPC_BOOTINFO_H */
macro_line|#endif /* __KERNEL__ */
eof
