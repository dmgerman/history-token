multiline_comment|/*&n; * Some ECOFF definitions.&n; */
DECL|struct|filehdr
r_typedef
r_struct
id|filehdr
(brace
DECL|member|f_magic
r_int
r_int
id|f_magic
suffix:semicolon
multiline_comment|/* magic number */
DECL|member|f_nscns
r_int
r_int
id|f_nscns
suffix:semicolon
multiline_comment|/* number of sections */
DECL|member|f_timdat
r_int
id|f_timdat
suffix:semicolon
multiline_comment|/* time &amp; date stamp */
DECL|member|f_symptr
r_int
id|f_symptr
suffix:semicolon
multiline_comment|/* file pointer to symbolic header */
DECL|member|f_nsyms
r_int
id|f_nsyms
suffix:semicolon
multiline_comment|/* sizeof(symbolic hdr) */
DECL|member|f_opthdr
r_int
r_int
id|f_opthdr
suffix:semicolon
multiline_comment|/* sizeof(optional hdr) */
DECL|member|f_flags
r_int
r_int
id|f_flags
suffix:semicolon
multiline_comment|/* flags */
DECL|typedef|FILHDR
)brace
id|FILHDR
suffix:semicolon
DECL|macro|FILHSZ
mdefine_line|#define FILHSZ  sizeof(FILHDR)
DECL|macro|OMAGIC
mdefine_line|#define OMAGIC&t;&t;0407
DECL|macro|MIPSEBMAGIC
mdefine_line|#define MIPSEBMAGIC&t;0x160
DECL|macro|MIPSELMAGIC
mdefine_line|#define MIPSELMAGIC&t;0x162
DECL|struct|scnhdr
r_typedef
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
multiline_comment|/* section name */
DECL|member|s_paddr
r_int
id|s_paddr
suffix:semicolon
multiline_comment|/* physical address, aliased s_nlib */
DECL|member|s_vaddr
r_int
id|s_vaddr
suffix:semicolon
multiline_comment|/* virtual address */
DECL|member|s_size
r_int
id|s_size
suffix:semicolon
multiline_comment|/* section size */
DECL|member|s_scnptr
r_int
id|s_scnptr
suffix:semicolon
multiline_comment|/* file ptr to raw data for section */
DECL|member|s_relptr
r_int
id|s_relptr
suffix:semicolon
multiline_comment|/* file ptr to relocation */
DECL|member|s_lnnoptr
r_int
id|s_lnnoptr
suffix:semicolon
multiline_comment|/* file ptr to gp histogram */
DECL|member|s_nreloc
r_int
r_int
id|s_nreloc
suffix:semicolon
multiline_comment|/* number of relocation entries */
DECL|member|s_nlnno
r_int
r_int
id|s_nlnno
suffix:semicolon
multiline_comment|/* number of gp histogram entries */
DECL|member|s_flags
r_int
id|s_flags
suffix:semicolon
multiline_comment|/* flags */
DECL|typedef|SCNHDR
)brace
id|SCNHDR
suffix:semicolon
DECL|macro|SCNHSZ
mdefine_line|#define SCNHSZ&t;&t;sizeof(SCNHDR)
DECL|macro|SCNROUND
mdefine_line|#define SCNROUND&t;((long)16)
DECL|struct|aouthdr
r_typedef
r_struct
id|aouthdr
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* see above                            */
DECL|member|vstamp
r_int
id|vstamp
suffix:semicolon
multiline_comment|/* version stamp                        */
DECL|member|tsize
r_int
id|tsize
suffix:semicolon
multiline_comment|/* text size in bytes, padded to DW bdry*/
DECL|member|dsize
r_int
id|dsize
suffix:semicolon
multiline_comment|/* initialized data &quot;  &quot;                */
DECL|member|bsize
r_int
id|bsize
suffix:semicolon
multiline_comment|/* uninitialized data &quot;   &quot;             */
DECL|member|entry
r_int
id|entry
suffix:semicolon
multiline_comment|/* entry pt.                            */
DECL|member|text_start
r_int
id|text_start
suffix:semicolon
multiline_comment|/* base of text used for this file      */
DECL|member|data_start
r_int
id|data_start
suffix:semicolon
multiline_comment|/* base of data used for this file      */
DECL|member|bss_start
r_int
id|bss_start
suffix:semicolon
multiline_comment|/* base of bss used for this file       */
DECL|member|gprmask
r_int
id|gprmask
suffix:semicolon
multiline_comment|/* general purpose register mask        */
DECL|member|cprmask
r_int
id|cprmask
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* co-processor register masks          */
DECL|member|gp_value
r_int
id|gp_value
suffix:semicolon
multiline_comment|/* the gp value used for this object    */
DECL|typedef|AOUTHDR
)brace
id|AOUTHDR
suffix:semicolon
DECL|macro|AOUTHSZ
mdefine_line|#define AOUTHSZ sizeof(AOUTHDR)
DECL|macro|OMAGIC
mdefine_line|#define OMAGIC&t;&t;0407
DECL|macro|NMAGIC
mdefine_line|#define NMAGIC&t;&t;0410
DECL|macro|ZMAGIC
mdefine_line|#define ZMAGIC&t;&t;0413
DECL|macro|SMAGIC
mdefine_line|#define SMAGIC&t;&t;0411
DECL|macro|LIBMAGIC
mdefine_line|#define LIBMAGIC        0443
DECL|macro|N_TXTOFF
mdefine_line|#define N_TXTOFF(f, a) &bslash;&n; ((a).magic == ZMAGIC || (a).magic == LIBMAGIC ? 0 : &bslash;&n;  ((a).vstamp &lt; 23 ? &bslash;&n;   ((FILHSZ + AOUTHSZ + (f).f_nscns * SCNHSZ + 7) &amp; 0xfffffff8) : &bslash;&n;   ((FILHSZ + AOUTHSZ + (f).f_nscns * SCNHSZ + SCNROUND-1) &amp; ~(SCNROUND-1)) ) )
DECL|macro|N_DATOFF
mdefine_line|#define N_DATOFF(f, a) &bslash;&n;  N_TXTOFF(f, a) + (a).tsize;
eof
