multiline_comment|/* IBM RS/6000 &quot;XCOFF&quot; file definitions for BFD.&n;   Copyright (C) 1990, 1991 Free Software Foundation, Inc.&n;   FIXME: Can someone provide a transliteration of this name into ASCII?&n;   Using the following chars caused a compiler warning on HIUX (so I replaced&n;   them with octal escapes), and isn&squot;t useful without an understanding of what&n;   character set it is.&n;   Written by Mimi Ph&bslash;373&bslash;364ng-Th&bslash;345o V&bslash;365 of IBM&n;   and John Gilmore of Cygnus Support.  */
multiline_comment|/********************** FILE HEADER **********************/
DECL|struct|external_filehdr
r_struct
id|external_filehdr
(brace
DECL|member|f_magic
r_char
id|f_magic
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* magic number&t;&t;&t;*/
DECL|member|f_nscns
r_char
id|f_nscns
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* number of sections&t;&t;*/
DECL|member|f_timdat
r_char
id|f_timdat
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* time &amp; date stamp&t;&t;*/
DECL|member|f_symptr
r_char
id|f_symptr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* file pointer to symtab&t;*/
DECL|member|f_nsyms
r_char
id|f_nsyms
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* number of symtab entries&t;*/
DECL|member|f_opthdr
r_char
id|f_opthdr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* sizeof(optional hdr)&t;&t;*/
DECL|member|f_flags
r_char
id|f_flags
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* flags&t;&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/* IBM RS/6000 */
DECL|macro|U802WRMAGIC
mdefine_line|#define U802WRMAGIC     0730    /* writeable text segments **chh**      */
DECL|macro|U802ROMAGIC
mdefine_line|#define U802ROMAGIC     0735    /* readonly sharable text segments      */
DECL|macro|U802TOCMAGIC
mdefine_line|#define U802TOCMAGIC    0737    /* readonly text segments and TOC       */
DECL|macro|BADMAG
mdefine_line|#define BADMAG(x)&t;&bslash;&n;&t;((x).f_magic != U802ROMAGIC &amp;&amp; (x).f_magic != U802WRMAGIC &amp;&amp; &bslash;&n;&t; (x).f_magic != U802TOCMAGIC)
DECL|macro|FILHDR
mdefine_line|#define&t;FILHDR&t;struct external_filehdr
DECL|macro|FILHSZ
mdefine_line|#define&t;FILHSZ&t;20
multiline_comment|/********************** AOUT &quot;OPTIONAL HEADER&quot; **********************/
r_typedef
r_struct
(brace
DECL|member|magic
r_int
r_char
id|magic
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* type of file&t;&t;&t;*/
DECL|member|vstamp
r_int
r_char
id|vstamp
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* version stamp&t;&t;*/
DECL|member|tsize
r_int
r_char
id|tsize
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* text size in bytes, padded to FW bdry */
DECL|member|dsize
r_int
r_char
id|dsize
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* initialized data &quot;  &quot;&t;*/
DECL|member|bsize
r_int
r_char
id|bsize
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* uninitialized data &quot;   &quot;&t;*/
DECL|member|entry
r_int
r_char
id|entry
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* entry pt.&t;&t;&t;*/
DECL|member|text_start
r_int
r_char
id|text_start
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* base of text used for this file */
DECL|member|data_start
r_int
r_char
id|data_start
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* base of data used for this file */
DECL|member|o_toc
r_int
r_char
id|o_toc
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* address of TOC */
DECL|member|o_snentry
r_int
r_char
id|o_snentry
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* section number of entry point */
DECL|member|o_sntext
r_int
r_char
id|o_sntext
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* section number of .text section */
DECL|member|o_sndata
r_int
r_char
id|o_sndata
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* section number of .data section */
DECL|member|o_sntoc
r_int
r_char
id|o_sntoc
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* section number of TOC */
DECL|member|o_snloader
r_int
r_char
id|o_snloader
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* section number of .loader section */
DECL|member|o_snbss
r_int
r_char
id|o_snbss
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* section number of .bss section */
DECL|member|o_algntext
r_int
r_char
id|o_algntext
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* .text alignment */
DECL|member|o_algndata
r_int
r_char
id|o_algndata
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* .data alignment */
DECL|member|o_modtype
r_int
r_char
id|o_modtype
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* module type (??) */
DECL|member|o_cputype
r_int
r_char
id|o_cputype
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* cpu type */
DECL|member|o_maxstack
r_int
r_char
id|o_maxstack
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* max stack size (??) */
DECL|member|o_maxdata
r_int
r_char
id|o_maxdata
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* max data size (??) */
DECL|member|o_resv2
r_int
r_char
id|o_resv2
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* reserved */
)brace
DECL|typedef|AOUTHDR
id|AOUTHDR
suffix:semicolon
DECL|macro|AOUTSZ
mdefine_line|#define AOUTSZ 72
DECL|macro|SMALL_AOUTSZ
mdefine_line|#define SMALL_AOUTSZ (28)
DECL|macro|AOUTHDRSZ
mdefine_line|#define AOUTHDRSZ 72
DECL|macro|RS6K_AOUTHDR_OMAGIC
mdefine_line|#define&t;RS6K_AOUTHDR_OMAGIC&t;0x0107&t;/* old: text &amp; data writeable */
DECL|macro|RS6K_AOUTHDR_NMAGIC
mdefine_line|#define&t;RS6K_AOUTHDR_NMAGIC&t;0x0108&t;/* new: text r/o, data r/w */
DECL|macro|RS6K_AOUTHDR_ZMAGIC
mdefine_line|#define&t;RS6K_AOUTHDR_ZMAGIC&t;0x010B&t;/* paged: text r/o, both page-aligned */
multiline_comment|/********************** SECTION HEADER **********************/
DECL|struct|external_scnhdr
r_struct
id|external_scnhdr
(brace
DECL|member|s_name
r_char
id|s_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* section name&t;&t;&t;*/
DECL|member|s_paddr
r_char
id|s_paddr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* physical address, aliased s_nlib */
DECL|member|s_vaddr
r_char
id|s_vaddr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* virtual address&t;&t;*/
DECL|member|s_size
r_char
id|s_size
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* section size&t;&t;&t;*/
DECL|member|s_scnptr
r_char
id|s_scnptr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* file ptr to raw data for section */
DECL|member|s_relptr
r_char
id|s_relptr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* file ptr to relocation&t;*/
DECL|member|s_lnnoptr
r_char
id|s_lnnoptr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* file ptr to line numbers&t;*/
DECL|member|s_nreloc
r_char
id|s_nreloc
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* number of relocation entries&t;*/
DECL|member|s_nlnno
r_char
id|s_nlnno
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* number of line number entries*/
DECL|member|s_flags
r_char
id|s_flags
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* flags&t;&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * names of &quot;special&quot; sections&n; */
DECL|macro|_TEXT
mdefine_line|#define _TEXT&t;&quot;.text&quot;
DECL|macro|_DATA
mdefine_line|#define _DATA&t;&quot;.data&quot;
DECL|macro|_BSS
mdefine_line|#define _BSS&t;&quot;.bss&quot;
DECL|macro|_PAD
mdefine_line|#define _PAD&t;&quot;.pad&quot;
DECL|macro|_LOADER
mdefine_line|#define _LOADER&t;&quot;.loader&quot;
DECL|macro|SCNHDR
mdefine_line|#define&t;SCNHDR&t;struct external_scnhdr
DECL|macro|SCNHSZ
mdefine_line|#define&t;SCNHSZ&t;40
multiline_comment|/* XCOFF uses a special .loader section with type STYP_LOADER.  */
DECL|macro|STYP_LOADER
mdefine_line|#define STYP_LOADER 0x1000
multiline_comment|/* XCOFF uses a special .debug section with type STYP_DEBUG.  */
DECL|macro|STYP_DEBUG
mdefine_line|#define STYP_DEBUG 0x2000
multiline_comment|/* XCOFF handles line number or relocation overflow by creating&n;   another section header with STYP_OVRFLO set.  */
DECL|macro|STYP_OVRFLO
mdefine_line|#define STYP_OVRFLO 0x8000
multiline_comment|/********************** LINE NUMBERS **********************/
multiline_comment|/* 1 line number entry for every &quot;breakpointable&quot; source line in a section.&n; * Line numbers are grouped on a per function basis; first entry in a function&n; * grouping will have l_lnno = 0 and in place of physical address will be the&n; * symbol table index of the function name.&n; */
DECL|struct|external_lineno
r_struct
id|external_lineno
(brace
r_union
(brace
DECL|member|l_symndx
r_char
id|l_symndx
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* function name symbol index, iff l_lnno == 0*/
DECL|member|l_paddr
r_char
id|l_paddr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* (physical) address of line number&t;*/
DECL|member|l_addr
)brace
id|l_addr
suffix:semicolon
DECL|member|l_lnno
r_char
id|l_lnno
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* line number&t;&t;*/
)brace
suffix:semicolon
DECL|macro|LINENO
mdefine_line|#define&t;LINENO&t;struct external_lineno
DECL|macro|LINESZ
mdefine_line|#define&t;LINESZ&t;6
multiline_comment|/********************** SYMBOLS **********************/
DECL|macro|E_SYMNMLEN
mdefine_line|#define E_SYMNMLEN&t;8&t;/* # characters in a symbol name&t;*/
DECL|macro|E_FILNMLEN
mdefine_line|#define E_FILNMLEN&t;14&t;/* # characters in a file name&t;&t;*/
DECL|macro|E_DIMNUM
mdefine_line|#define E_DIMNUM&t;4&t;/* # array dimensions in auxiliary entry */
DECL|struct|external_syment
r_struct
id|external_syment
(brace
r_union
(brace
DECL|member|e_name
r_char
id|e_name
(braket
id|E_SYMNMLEN
)braket
suffix:semicolon
r_struct
(brace
DECL|member|e_zeroes
r_char
id|e_zeroes
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|e_offset
r_char
id|e_offset
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|e
)brace
id|e
suffix:semicolon
DECL|member|e
)brace
id|e
suffix:semicolon
DECL|member|e_value
r_char
id|e_value
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|e_scnum
r_char
id|e_scnum
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|e_type
r_char
id|e_type
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|e_sclass
r_char
id|e_sclass
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|e_numaux
r_char
id|e_numaux
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|N_BTMASK
mdefine_line|#define N_BTMASK&t;(017)
DECL|macro|N_TMASK
mdefine_line|#define N_TMASK&t;&t;(060)
DECL|macro|N_BTSHFT
mdefine_line|#define N_BTSHFT&t;(4)
DECL|macro|N_TSHIFT
mdefine_line|#define N_TSHIFT&t;(2)
DECL|union|external_auxent
r_union
id|external_auxent
(brace
r_struct
(brace
DECL|member|x_tagndx
r_char
id|x_tagndx
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* str, un, or enum tag indx */
r_union
(brace
r_struct
(brace
DECL|member|x_lnno
r_char
id|x_lnno
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* declaration line number */
DECL|member|x_size
r_char
id|x_size
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* str/union/array size */
DECL|member|x_lnsz
)brace
id|x_lnsz
suffix:semicolon
DECL|member|x_fsize
r_char
id|x_fsize
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* size of function */
DECL|member|x_misc
)brace
id|x_misc
suffix:semicolon
r_union
(brace
r_struct
(brace
multiline_comment|/* if ISFCN, tag, or .bb */
DECL|member|x_lnnoptr
r_char
id|x_lnnoptr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* ptr to fcn line # */
DECL|member|x_endndx
r_char
id|x_endndx
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* entry ndx past block end */
DECL|member|x_fcn
)brace
id|x_fcn
suffix:semicolon
r_struct
(brace
multiline_comment|/* if ISARY, up to 4 dimen. */
DECL|member|x_dimen
r_char
id|x_dimen
(braket
id|E_DIMNUM
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|x_ary
)brace
id|x_ary
suffix:semicolon
DECL|member|x_fcnary
)brace
id|x_fcnary
suffix:semicolon
DECL|member|x_tvndx
r_char
id|x_tvndx
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* tv index */
DECL|member|x_sym
)brace
id|x_sym
suffix:semicolon
r_union
(brace
DECL|member|x_fname
r_char
id|x_fname
(braket
id|E_FILNMLEN
)braket
suffix:semicolon
r_struct
(brace
DECL|member|x_zeroes
r_char
id|x_zeroes
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|x_offset
r_char
id|x_offset
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|x_n
)brace
id|x_n
suffix:semicolon
DECL|member|x_file
)brace
id|x_file
suffix:semicolon
r_struct
(brace
DECL|member|x_scnlen
r_char
id|x_scnlen
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* section length */
DECL|member|x_nreloc
r_char
id|x_nreloc
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* # relocation entries */
DECL|member|x_nlinno
r_char
id|x_nlinno
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* # line numbers */
DECL|member|x_scn
)brace
id|x_scn
suffix:semicolon
r_struct
(brace
DECL|member|x_tvfill
r_char
id|x_tvfill
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* tv fill value */
DECL|member|x_tvlen
r_char
id|x_tvlen
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* length of .tv */
DECL|member|x_tvran
r_char
id|x_tvran
(braket
l_int|2
)braket
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* tv range */
DECL|member|x_tv
)brace
id|x_tv
suffix:semicolon
multiline_comment|/* info about .tv section (in auxent of symbol .tv)) */
r_struct
(brace
DECL|member|x_scnlen
r_int
r_char
id|x_scnlen
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|x_parmhash
r_int
r_char
id|x_parmhash
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|x_snhash
r_int
r_char
id|x_snhash
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|x_smtyp
r_int
r_char
id|x_smtyp
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|x_smclas
r_int
r_char
id|x_smclas
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|x_stab
r_int
r_char
id|x_stab
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|x_snstab
r_int
r_char
id|x_snstab
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|x_csect
)brace
id|x_csect
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SYMENT
mdefine_line|#define&t;SYMENT&t;struct external_syment
DECL|macro|SYMESZ
mdefine_line|#define&t;SYMESZ&t;18&t;
DECL|macro|AUXENT
mdefine_line|#define&t;AUXENT&t;union external_auxent
DECL|macro|AUXESZ
mdefine_line|#define&t;AUXESZ&t;18
DECL|macro|DBXMASK
mdefine_line|#define DBXMASK 0x80&t;&t;/* for dbx storage mask */
DECL|macro|SYMNAME_IN_DEBUG
mdefine_line|#define SYMNAME_IN_DEBUG(symptr) ((symptr)-&gt;n_sclass &amp; DBXMASK)
multiline_comment|/********************** RELOCATION DIRECTIVES **********************/
DECL|struct|external_reloc
r_struct
id|external_reloc
(brace
DECL|member|r_vaddr
r_char
id|r_vaddr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|r_symndx
r_char
id|r_symndx
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|r_size
r_char
id|r_size
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|r_type
r_char
id|r_type
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RELOC
mdefine_line|#define RELOC struct external_reloc
DECL|macro|RELSZ
mdefine_line|#define RELSZ 10
DECL|macro|DEFAULT_DATA_SECTION_ALIGNMENT
mdefine_line|#define DEFAULT_DATA_SECTION_ALIGNMENT 4
DECL|macro|DEFAULT_BSS_SECTION_ALIGNMENT
mdefine_line|#define DEFAULT_BSS_SECTION_ALIGNMENT 4
DECL|macro|DEFAULT_TEXT_SECTION_ALIGNMENT
mdefine_line|#define DEFAULT_TEXT_SECTION_ALIGNMENT 4
multiline_comment|/* For new sections we havn&squot;t heard of before */
DECL|macro|DEFAULT_SECTION_ALIGNMENT
mdefine_line|#define DEFAULT_SECTION_ALIGNMENT 4
eof
