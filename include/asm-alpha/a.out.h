macro_line|#ifndef __ALPHA_A_OUT_H__
DECL|macro|__ALPHA_A_OUT_H__
mdefine_line|#define __ALPHA_A_OUT_H__
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * OSF/1 ECOFF header structs.  ECOFF files consist of:&n; * &t;- a file header (struct filehdr),&n; *&t;- an a.out header (struct aouthdr),&n; *&t;- one or more section headers (struct scnhdr). &n; *&t;  The filhdr&squot;s &quot;f_nscns&quot; field contains the&n; *&t;  number of section headers.&n; */
DECL|struct|filehdr
r_struct
id|filehdr
(brace
multiline_comment|/* OSF/1 &quot;file&quot; header */
DECL|member|f_magic
DECL|member|f_nscns
id|__u16
id|f_magic
comma
id|f_nscns
suffix:semicolon
DECL|member|f_timdat
id|__u32
id|f_timdat
suffix:semicolon
DECL|member|f_symptr
id|__u64
id|f_symptr
suffix:semicolon
DECL|member|f_nsyms
id|__u32
id|f_nsyms
suffix:semicolon
DECL|member|f_opthdr
DECL|member|f_flags
id|__u16
id|f_opthdr
comma
id|f_flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aouthdr
r_struct
id|aouthdr
(brace
DECL|member|info
id|__u64
id|info
suffix:semicolon
multiline_comment|/* after that it looks quite normal.. */
DECL|member|tsize
id|__u64
id|tsize
suffix:semicolon
DECL|member|dsize
id|__u64
id|dsize
suffix:semicolon
DECL|member|bsize
id|__u64
id|bsize
suffix:semicolon
DECL|member|entry
id|__u64
id|entry
suffix:semicolon
DECL|member|text_start
id|__u64
id|text_start
suffix:semicolon
multiline_comment|/* with a few additions that actually make sense */
DECL|member|data_start
id|__u64
id|data_start
suffix:semicolon
DECL|member|bss_start
id|__u64
id|bss_start
suffix:semicolon
DECL|member|gprmask
DECL|member|fprmask
id|__u32
id|gprmask
comma
id|fprmask
suffix:semicolon
multiline_comment|/* bitmask of general &amp; floating point regs used in binary */
DECL|member|gpvalue
id|__u64
id|gpvalue
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|scnhdr
r_struct
id|scnhdr
(brace
DECL|member|s_name
r_char
id|s_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|s_paddr
id|__u64
id|s_paddr
suffix:semicolon
DECL|member|s_vaddr
id|__u64
id|s_vaddr
suffix:semicolon
DECL|member|s_size
id|__u64
id|s_size
suffix:semicolon
DECL|member|s_scnptr
id|__u64
id|s_scnptr
suffix:semicolon
DECL|member|s_relptr
id|__u64
id|s_relptr
suffix:semicolon
DECL|member|s_lnnoptr
id|__u64
id|s_lnnoptr
suffix:semicolon
DECL|member|s_nreloc
id|__u16
id|s_nreloc
suffix:semicolon
DECL|member|s_nlnno
id|__u16
id|s_nlnno
suffix:semicolon
DECL|member|s_flags
id|__u32
id|s_flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|exec
r_struct
id|exec
(brace
multiline_comment|/* OSF/1 &quot;file&quot; header */
DECL|member|fh
r_struct
id|filehdr
id|fh
suffix:semicolon
DECL|member|ah
r_struct
id|aouthdr
id|ah
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Define&squot;s so that the kernel exec code can access the a.out header&n; * fields...&n; */
DECL|macro|a_info
mdefine_line|#define&t;a_info&t;&t;ah.info
DECL|macro|a_text
mdefine_line|#define&t;a_text&t;&t;ah.tsize
DECL|macro|a_data
mdefine_line|#define a_data&t;&t;ah.dsize
DECL|macro|a_bss
mdefine_line|#define a_bss&t;&t;ah.bsize
DECL|macro|a_entry
mdefine_line|#define a_entry&t;&t;ah.entry
DECL|macro|a_textstart
mdefine_line|#define a_textstart&t;ah.text_start
DECL|macro|a_datastart
mdefine_line|#define&t;a_datastart&t;ah.data_start
DECL|macro|a_bssstart
mdefine_line|#define&t;a_bssstart&t;ah.bss_start
DECL|macro|a_gprmask
mdefine_line|#define&t;a_gprmask&t;ah.gprmask
DECL|macro|a_fprmask
mdefine_line|#define a_fprmask&t;ah.fprmask
DECL|macro|a_gpvalue
mdefine_line|#define a_gpvalue&t;ah.gpvalue
DECL|macro|N_TXTADDR
mdefine_line|#define N_TXTADDR(x) ((x).a_textstart)
DECL|macro|N_DATADDR
mdefine_line|#define N_DATADDR(x) ((x).a_datastart)
DECL|macro|N_BSSADDR
mdefine_line|#define N_BSSADDR(x) ((x).a_bssstart)
DECL|macro|N_DRSIZE
mdefine_line|#define N_DRSIZE(x) 0
DECL|macro|N_TRSIZE
mdefine_line|#define N_TRSIZE(x) 0
DECL|macro|N_SYMSIZE
mdefine_line|#define N_SYMSIZE(x) 0
DECL|macro|AOUTHSZ
mdefine_line|#define AOUTHSZ&t;&t;sizeof(struct aouthdr)
DECL|macro|SCNHSZ
mdefine_line|#define SCNHSZ&t;&t;sizeof(struct scnhdr)
DECL|macro|SCNROUND
mdefine_line|#define SCNROUND&t;16
DECL|macro|N_TXTOFF
mdefine_line|#define N_TXTOFF(x) &bslash;&n;  ((long) N_MAGIC(x) == ZMAGIC ? 0 : &bslash;&n;   (sizeof(struct exec) + (x).fh.f_nscns*SCNHSZ + SCNROUND - 1) &amp; ~(SCNROUND - 1))
macro_line|#ifdef __KERNEL__
multiline_comment|/* Assume that start addresses below 4G belong to a TASO application.&n;   Unfortunately, there is no proper bit in the exec header to check.&n;   Worse, we have to notice the start address before swapping to use&n;   /sbin/loader, which of course is _not_ a TASO application.  */
DECL|macro|SET_AOUT_PERSONALITY
mdefine_line|#define SET_AOUT_PERSONALITY(BFPM, EX) &bslash;&n;&t;set_personality (BFPM-&gt;sh_bang || EX.ah.entry &lt; 0x100000000 &bslash;&n;&t;&t;&t; ? PER_LINUX_32BIT : PER_LINUX)
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP &bslash;&n;  (current-&gt;personality &amp; ADDR_LIMIT_32BIT ? 0x80000000 : 0x00120000000UL)
macro_line|#endif
macro_line|#endif /* __A_OUT_GNU_H__ */
eof
