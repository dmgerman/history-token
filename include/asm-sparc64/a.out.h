multiline_comment|/* $Id: a.out.h,v 1.7 2001/04/24 01:09:12 davem Exp $ */
macro_line|#ifndef __SPARC64_A_OUT_H__
DECL|macro|__SPARC64_A_OUT_H__
mdefine_line|#define __SPARC64_A_OUT_H__
DECL|macro|SPARC_PGSIZE
mdefine_line|#define SPARC_PGSIZE    0x2000        /* Thanks to the sun4 architecture... */
DECL|macro|SEGMENT_SIZE
mdefine_line|#define SEGMENT_SIZE    SPARC_PGSIZE  /* whee... */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|exec
r_struct
id|exec
(brace
DECL|member|a_dynamic
r_int
r_char
id|a_dynamic
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A __DYNAMIC is in this image */
DECL|member|a_toolversion
r_int
r_char
id|a_toolversion
suffix:colon
l_int|7
suffix:semicolon
DECL|member|a_machtype
r_int
r_char
id|a_machtype
suffix:semicolon
DECL|member|a_info
r_int
r_int
id|a_info
suffix:semicolon
DECL|member|a_text
r_int
r_int
id|a_text
suffix:semicolon
multiline_comment|/* length of text, in bytes */
DECL|member|a_data
r_int
r_int
id|a_data
suffix:semicolon
multiline_comment|/* length of data, in bytes */
DECL|member|a_bss
r_int
r_int
id|a_bss
suffix:semicolon
multiline_comment|/* length of bss, in bytes */
DECL|member|a_syms
r_int
r_int
id|a_syms
suffix:semicolon
multiline_comment|/* length of symbol table, in bytes */
DECL|member|a_entry
r_int
r_int
id|a_entry
suffix:semicolon
multiline_comment|/* where program begins */
DECL|member|a_trsize
r_int
r_int
id|a_trsize
suffix:semicolon
DECL|member|a_drsize
r_int
r_int
id|a_drsize
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* Where in the file does the text information begin? */
DECL|macro|N_TXTOFF
mdefine_line|#define N_TXTOFF(x)     (N_MAGIC(x) == ZMAGIC ? 0 : sizeof (struct exec))
multiline_comment|/* Where do the Symbols start? */
DECL|macro|N_SYMOFF
mdefine_line|#define N_SYMOFF(x)     (N_TXTOFF(x) + (x).a_text +   &bslash;&n;                         (x).a_data + (x).a_trsize +  &bslash;&n;                         (x).a_drsize)
multiline_comment|/* Where does text segment go in memory after being loaded? */
DECL|macro|N_TXTADDR
mdefine_line|#define N_TXTADDR(x)    (unsigned long)(((N_MAGIC(x) == ZMAGIC) &amp;&amp;      &bslash;&n;&t;                 ((x).a_entry &lt; SPARC_PGSIZE)) ?   &t;&t;&bslash;&n;                          0 : SPARC_PGSIZE)
multiline_comment|/* And same for the data segment.. */
DECL|macro|N_DATADDR
mdefine_line|#define N_DATADDR(x) (N_MAGIC(x)==OMAGIC ?         &bslash;&n;                      (N_TXTADDR(x) + (x).a_text)  &bslash;&n;                       : (unsigned long)(_N_SEGMENT_ROUND (_N_TXTENDADDR(x))))
DECL|macro|N_TRSIZE
mdefine_line|#define N_TRSIZE(a)&t;((a).a_trsize)
DECL|macro|N_DRSIZE
mdefine_line|#define N_DRSIZE(a)&t;((a).a_drsize)
DECL|macro|N_SYMSIZE
mdefine_line|#define N_SYMSIZE(a)&t;((a).a_syms)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Sparc relocation types&n; */
DECL|enum|reloc_type
r_enum
id|reloc_type
(brace
DECL|enumerator|RELOC_8
id|RELOC_8
comma
DECL|enumerator|RELOC_16
id|RELOC_16
comma
DECL|enumerator|RELOC_32
id|RELOC_32
comma
multiline_comment|/* simplest relocs */
DECL|enumerator|RELOC_DISP8
id|RELOC_DISP8
comma
DECL|enumerator|RELOC_DISP16
id|RELOC_DISP16
comma
DECL|enumerator|RELOC_DISP32
id|RELOC_DISP32
comma
multiline_comment|/* Disp&squot;s (pc-rel) */
DECL|enumerator|RELOC_WDISP30
id|RELOC_WDISP30
comma
DECL|enumerator|RELOC_WDISP22
id|RELOC_WDISP22
comma
multiline_comment|/* SR word disp&squot;s */
DECL|enumerator|RELOC_HI22
id|RELOC_HI22
comma
DECL|enumerator|RELOC_22
id|RELOC_22
comma
multiline_comment|/* SR 22-bit relocs */
DECL|enumerator|RELOC_13
id|RELOC_13
comma
DECL|enumerator|RELOC_LO10
id|RELOC_LO10
comma
multiline_comment|/* SR 13&amp;10-bit relocs */
DECL|enumerator|RELOC_SFA_BASE
id|RELOC_SFA_BASE
comma
DECL|enumerator|RELOC_SFA_OFF13
id|RELOC_SFA_OFF13
comma
multiline_comment|/* SR S.F.A. relocs */
DECL|enumerator|RELOC_BASE10
id|RELOC_BASE10
comma
DECL|enumerator|RELOC_BASE13
id|RELOC_BASE13
comma
DECL|enumerator|RELOC_BASE22
id|RELOC_BASE22
comma
multiline_comment|/* base_relative pic */
DECL|enumerator|RELOC_PC10
id|RELOC_PC10
comma
DECL|enumerator|RELOC_PC22
id|RELOC_PC22
comma
multiline_comment|/* special pc-rel pic */
DECL|enumerator|RELOC_JMP_TBL
id|RELOC_JMP_TBL
comma
multiline_comment|/* jmp_tbl_rel in pic */
DECL|enumerator|RELOC_SEGOFF16
id|RELOC_SEGOFF16
comma
multiline_comment|/* ShLib offset-in-seg */
DECL|enumerator|RELOC_GLOB_DAT
id|RELOC_GLOB_DAT
comma
DECL|enumerator|RELOC_JMP_SLOT
id|RELOC_JMP_SLOT
comma
DECL|enumerator|RELOC_RELATIVE
id|RELOC_RELATIVE
multiline_comment|/* rtld relocs */
)brace
suffix:semicolon
multiline_comment|/*&n; * Format of a relocation datum.&n; */
DECL|struct|relocation_info
r_struct
id|relocation_info
multiline_comment|/* used when header.a_machtype == M_SPARC */
(brace
DECL|member|r_address
r_int
r_int
id|r_address
suffix:semicolon
multiline_comment|/* relocation addr */
DECL|member|r_index
r_int
r_int
id|r_index
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* segment index or symbol index */
DECL|member|r_extern
r_int
r_int
id|r_extern
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* if F, r_index==SEG#; if T, SYM idx */
DECL|member|r_pad
r_int
id|r_pad
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* &lt;unused&gt; */
DECL|member|r_type
r_enum
id|reloc_type
id|r_type
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* type of relocation to perform */
DECL|member|r_addend
r_int
id|r_addend
suffix:semicolon
multiline_comment|/* addend for relocation value */
)brace
suffix:semicolon
DECL|macro|N_RELOCATION_INFO_DECLARED
mdefine_line|#define N_RELOCATION_INFO_DECLARED 1
macro_line|#ifdef __KERNEL__
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP (current-&gt;thread.flags &amp; SPARC_FLAG_32BIT ? 0xf0000000 : 0x80000000000L)
macro_line|#endif
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__SPARC64_A_OUT_H__) */
eof
