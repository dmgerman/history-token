multiline_comment|/* This file is derived from the GAS 2.1.4 assembler control file.&n;   The GAS product is under the GNU General Public License, version 2 or later.&n;   As such, this file is also under that license.&n;&n;   If the file format changes in the COFF object, this file should be&n;   subsequently updated to reflect the changes.&n;&n;   The actual loader module only uses a few of these structures. The full&n;   set is documented here because I received the full set. If you wish&n;   more information about COFF, then O&squot;Reilly has a very excellent book.&n;*/
DECL|macro|E_SYMNMLEN
mdefine_line|#define  E_SYMNMLEN  8   /* Number of characters in a symbol name         */
DECL|macro|E_FILNMLEN
mdefine_line|#define  E_FILNMLEN 14   /* Number of characters in a file name           */
DECL|macro|E_DIMNUM
mdefine_line|#define  E_DIMNUM    4   /* Number of array dimensions in auxiliary entry */
multiline_comment|/*&n; * These defines are byte order independent. There is no alignment of fields&n; * permitted in the structures. Therefore they are declared as characters&n; * and the values loaded from the character positions. It also makes it&n; * nice to have it &quot;endian&quot; independent.&n; */
multiline_comment|/* Load a short int from the following tables with little-endian formats */
DECL|macro|COFF_SHORT_L
mdefine_line|#define COFF_SHORT_L(ps) ((short)(((unsigned short)((unsigned char)ps[1])&lt;&lt;8)|&bslash;&n;&t;&t;&t;&t;  ((unsigned short)((unsigned char)ps[0]))))
multiline_comment|/* Load a long int from the following tables with little-endian formats */
DECL|macro|COFF_LONG_L
mdefine_line|#define COFF_LONG_L(ps) (((long)(((unsigned long)((unsigned char)ps[3])&lt;&lt;24) |&bslash;&n;&t;&t;&t;&t; ((unsigned long)((unsigned char)ps[2])&lt;&lt;16) |&bslash;&n;&t;&t;&t;&t; ((unsigned long)((unsigned char)ps[1])&lt;&lt;8)  |&bslash;&n;&t;&t;&t;&t; ((unsigned long)((unsigned char)ps[0])))))
multiline_comment|/* Load a short int from the following tables with big-endian formats */
DECL|macro|COFF_SHORT_H
mdefine_line|#define COFF_SHORT_H(ps) ((short)(((unsigned short)((unsigned char)ps[0])&lt;&lt;8)|&bslash;&n;&t;&t;&t;&t;  ((unsigned short)((unsigned char)ps[1]))))
multiline_comment|/* Load a long int from the following tables with big-endian formats */
DECL|macro|COFF_LONG_H
mdefine_line|#define COFF_LONG_H(ps) (((long)(((unsigned long)((unsigned char)ps[0])&lt;&lt;24) |&bslash;&n;&t;&t;&t;&t; ((unsigned long)((unsigned char)ps[1])&lt;&lt;16) |&bslash;&n;&t;&t;&t;&t; ((unsigned long)((unsigned char)ps[2])&lt;&lt;8)  |&bslash;&n;&t;&t;&t;&t; ((unsigned long)((unsigned char)ps[3])))))
multiline_comment|/* These may be overridden later by brain dead implementations which generate&n;   a big-endian header with little-endian data. In that case, generate a&n;   replacement macro which tests a flag and uses either of the two above&n;   as appropriate. */
DECL|macro|COFF_LONG
mdefine_line|#define COFF_LONG(v)   COFF_LONG_L(v)
DECL|macro|COFF_SHORT
mdefine_line|#define COFF_SHORT(v)  COFF_SHORT_L(v)
multiline_comment|/*** coff information for Intel 386/486.  */
multiline_comment|/********************** FILE HEADER **********************/
DECL|struct|COFF_filehdr
r_struct
id|COFF_filehdr
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
multiline_comment|/*&n; *   Bits for f_flags:&n; *&n; *&t;F_RELFLG&t;relocation info stripped from file&n; *&t;F_EXEC&t;&t;file is executable  (i.e. no unresolved external&n; *&t;&t;&t;references)&n; *&t;F_LNNO&t;&t;line numbers stripped from file&n; *&t;F_LSYMS&t;&t;local symbols stripped from file&n; *&t;F_MINMAL&t;this is a minimal object file (&quot;.m&quot;) output of fextract&n; *&t;F_UPDATE&t;this is a fully bound update file, output of ogen&n; *&t;F_SWABD&t;&t;this file has had its bytes swabbed (in names)&n; *&t;F_AR16WR&t;this file has the byte ordering of an AR16WR&n; *&t;&t;&t;(e.g. 11/70) machine&n; *&t;F_AR32WR&t;this file has the byte ordering of an AR32WR machine&n; *&t;&t;&t;(e.g. vax and iNTEL 386)&n; *&t;F_AR32W&t;&t;this file has the byte ordering of an AR32W machine&n; *&t;&t;&t;(e.g. 3b,maxi)&n; *&t;F_PATCH&t;&t;file contains &quot;patch&quot; list in optional header&n; *&t;F_NODF&t;&t;(minimal file only) no decision functions for&n; *&t;&t;&t;replaced functions&n; */
DECL|macro|COFF_F_RELFLG
mdefine_line|#define  COFF_F_RELFLG&t;&t;0000001
DECL|macro|COFF_F_EXEC
mdefine_line|#define  COFF_F_EXEC&t;&t;0000002
DECL|macro|COFF_F_LNNO
mdefine_line|#define  COFF_F_LNNO&t;&t;0000004
DECL|macro|COFF_F_LSYMS
mdefine_line|#define  COFF_F_LSYMS&t;&t;0000010
DECL|macro|COFF_F_MINMAL
mdefine_line|#define  COFF_F_MINMAL&t;&t;0000020
DECL|macro|COFF_F_UPDATE
mdefine_line|#define  COFF_F_UPDATE&t;&t;0000040
DECL|macro|COFF_F_SWABD
mdefine_line|#define  COFF_F_SWABD&t;&t;0000100
DECL|macro|COFF_F_AR16WR
mdefine_line|#define  COFF_F_AR16WR&t;&t;0000200
DECL|macro|COFF_F_AR32WR
mdefine_line|#define  COFF_F_AR32WR&t;&t;0000400
DECL|macro|COFF_F_AR32W
mdefine_line|#define  COFF_F_AR32W&t;&t;0001000
DECL|macro|COFF_F_PATCH
mdefine_line|#define  COFF_F_PATCH&t;&t;0002000
DECL|macro|COFF_F_NODF
mdefine_line|#define  COFF_F_NODF&t;&t;0002000
DECL|macro|COFF_I386MAGIC
mdefine_line|#define&t;COFF_I386MAGIC&t;        0x14c   /* Linux&squot;s system    */
macro_line|#if 0   /* Perhaps, someday, these formats may be used.      */
mdefine_line|#define COFF_I386PTXMAGIC&t;0x154
mdefine_line|#define COFF_I386AIXMAGIC&t;0x175   /* IBM&squot;s AIX system  */
mdefine_line|#define COFF_I386BADMAG(x) ((COFF_SHORT((x).f_magic) != COFF_I386MAGIC) &bslash;&n;&t;&t;&t;  &amp;&amp; COFF_SHORT((x).f_magic) != COFF_I386PTXMAGIC &bslash;&n;&t;&t;&t;  &amp;&amp; COFF_SHORT((x).f_magic) != COFF_I386AIXMAGIC)
macro_line|#else
DECL|macro|COFF_I386BADMAG
mdefine_line|#define COFF_I386BADMAG(x) (COFF_SHORT((x).f_magic) != COFF_I386MAGIC)
macro_line|#endif
DECL|macro|COFF_FILHDR
mdefine_line|#define&t;COFF_FILHDR&t;struct COFF_filehdr
DECL|macro|COFF_FILHSZ
mdefine_line|#define&t;COFF_FILHSZ&t;sizeof(COFF_FILHDR)
multiline_comment|/********************** AOUT &quot;OPTIONAL HEADER&quot; **********************/
multiline_comment|/* Linux COFF must have this &quot;optional&quot; header. Standard COFF has no entry&n;   location for the &quot;entry&quot; point. They normally would start with the first&n;   location of the .text section. This is not a good idea for linux. So,&n;   the use of this &quot;optional&quot; header is not optional. It is required.&n;&n;   Do not be tempted to assume that the size of the optional header is&n;   a constant and simply index the next byte by the size of this structure.&n;   Use the &squot;f_opthdr&squot; field in the main coff header for the size of the&n;   structure actually written to the file!!&n;*/
r_typedef
r_struct
(brace
DECL|member|magic
r_char
id|magic
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* type of file&t;&t;&t;&t; */
DECL|member|vstamp
r_char
id|vstamp
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* version stamp&t;&t;&t; */
DECL|member|tsize
r_char
id|tsize
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* text size in bytes, padded to FW bdry */
DECL|member|dsize
r_char
id|dsize
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* initialized   data &quot;   &quot;&t;&t; */
DECL|member|bsize
r_char
id|bsize
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* uninitialized data &quot;   &quot;&t;&t; */
DECL|member|entry
r_char
id|entry
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* entry pt.&t;&t;&t;&t; */
DECL|member|text_start
r_char
id|text_start
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* base of text used for this file       */
DECL|member|data_start
r_char
id|data_start
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* base of data used for this file       */
)brace
DECL|typedef|COFF_AOUTHDR
id|COFF_AOUTHDR
suffix:semicolon
DECL|macro|COFF_AOUTSZ
mdefine_line|#define COFF_AOUTSZ (sizeof(COFF_AOUTHDR))
DECL|macro|COFF_STMAGIC
mdefine_line|#define COFF_STMAGIC&t;0401
DECL|macro|COFF_OMAGIC
mdefine_line|#define COFF_OMAGIC     0404
DECL|macro|COFF_JMAGIC
mdefine_line|#define COFF_JMAGIC     0407    /* dirty text and data image, can&squot;t share  */
DECL|macro|COFF_DMAGIC
mdefine_line|#define COFF_DMAGIC     0410    /* dirty text segment, data aligned        */
DECL|macro|COFF_ZMAGIC
mdefine_line|#define COFF_ZMAGIC     0413    /* The proper magic number for executables  */
DECL|macro|COFF_SHMAGIC
mdefine_line|#define COFF_SHMAGIC&t;0443&t;/* shared library header                   */
multiline_comment|/********************** SECTION HEADER **********************/
DECL|struct|COFF_scnhdr
r_struct
id|COFF_scnhdr
(brace
DECL|member|s_name
r_char
id|s_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* section name&t;&t;&t;    */
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
multiline_comment|/* virtual address&t;&t;    */
DECL|member|s_size
r_char
id|s_size
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* section size&t;&t;&t;    */
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
multiline_comment|/* file ptr to relocation&t;    */
DECL|member|s_lnnoptr
r_char
id|s_lnnoptr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* file ptr to line numbers&t;    */
DECL|member|s_nreloc
r_char
id|s_nreloc
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* number of relocation entries&t;    */
DECL|member|s_nlnno
r_char
id|s_nlnno
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* number of line number entries    */
DECL|member|s_flags
r_char
id|s_flags
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* flags&t;&t;&t;    */
)brace
suffix:semicolon
DECL|macro|COFF_SCNHDR
mdefine_line|#define&t;COFF_SCNHDR&t;struct COFF_scnhdr
DECL|macro|COFF_SCNHSZ
mdefine_line|#define&t;COFF_SCNHSZ&t;sizeof(COFF_SCNHDR)
multiline_comment|/*&n; * names of &quot;special&quot; sections&n; */
DECL|macro|COFF_TEXT
mdefine_line|#define COFF_TEXT&t;&quot;.text&quot;
DECL|macro|COFF_DATA
mdefine_line|#define COFF_DATA&t;&quot;.data&quot;
DECL|macro|COFF_BSS
mdefine_line|#define COFF_BSS&t;&quot;.bss&quot;
DECL|macro|COFF_COMMENT
mdefine_line|#define COFF_COMMENT    &quot;.comment&quot;
DECL|macro|COFF_LIB
mdefine_line|#define COFF_LIB        &quot;.lib&quot;
DECL|macro|COFF_SECT_TEXT
mdefine_line|#define COFF_SECT_TEXT  0      /* Section for instruction code             */
DECL|macro|COFF_SECT_DATA
mdefine_line|#define COFF_SECT_DATA  1      /* Section for initialized globals          */
DECL|macro|COFF_SECT_BSS
mdefine_line|#define COFF_SECT_BSS   2      /* Section for un-initialized globals       */
DECL|macro|COFF_SECT_REQD
mdefine_line|#define COFF_SECT_REQD  3      /* Minimum number of sections for good file */
DECL|macro|COFF_STYP_REG
mdefine_line|#define COFF_STYP_REG     0x00 /* regular segment                          */
DECL|macro|COFF_STYP_DSECT
mdefine_line|#define COFF_STYP_DSECT   0x01 /* dummy segment                            */
DECL|macro|COFF_STYP_NOLOAD
mdefine_line|#define COFF_STYP_NOLOAD  0x02 /* no-load segment                          */
DECL|macro|COFF_STYP_GROUP
mdefine_line|#define COFF_STYP_GROUP   0x04 /* group segment                            */
DECL|macro|COFF_STYP_PAD
mdefine_line|#define COFF_STYP_PAD     0x08 /* .pad segment                             */
DECL|macro|COFF_STYP_COPY
mdefine_line|#define COFF_STYP_COPY    0x10 /* copy section                             */
DECL|macro|COFF_STYP_TEXT
mdefine_line|#define COFF_STYP_TEXT    0x20 /* .text segment                            */
DECL|macro|COFF_STYP_DATA
mdefine_line|#define COFF_STYP_DATA    0x40 /* .data segment                            */
DECL|macro|COFF_STYP_BSS
mdefine_line|#define COFF_STYP_BSS     0x80 /* .bss segment                             */
DECL|macro|COFF_STYP_INFO
mdefine_line|#define COFF_STYP_INFO   0x200 /* .comment section                         */
DECL|macro|COFF_STYP_OVER
mdefine_line|#define COFF_STYP_OVER   0x400 /* overlay section                          */
DECL|macro|COFF_STYP_LIB
mdefine_line|#define COFF_STYP_LIB    0x800 /* library section                          */
multiline_comment|/*&n; * Shared libraries have the following section header in the data field for&n; * each library.&n; */
DECL|struct|COFF_slib
r_struct
id|COFF_slib
(brace
DECL|member|sl_entsz
r_char
id|sl_entsz
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Size of this entry               */
DECL|member|sl_pathndx
r_char
id|sl_pathndx
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* size of the header field         */
)brace
suffix:semicolon
DECL|macro|COFF_SLIBHD
mdefine_line|#define&t;COFF_SLIBHD&t;struct COFF_slib
DECL|macro|COFF_SLIBSZ
mdefine_line|#define&t;COFF_SLIBSZ&t;sizeof(COFF_SLIBHD)
multiline_comment|/********************** LINE NUMBERS **********************/
multiline_comment|/* 1 line number entry for every &quot;breakpointable&quot; source line in a section.&n; * Line numbers are grouped on a per function basis; first entry in a function&n; * grouping will have l_lnno = 0 and in place of physical address will be the&n; * symbol table index of the function name.&n; */
DECL|struct|COFF_lineno
r_struct
id|COFF_lineno
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
DECL|macro|COFF_LINENO
mdefine_line|#define&t;COFF_LINENO&t;struct COFF_lineno
DECL|macro|COFF_LINESZ
mdefine_line|#define&t;COFF_LINESZ&t;6
multiline_comment|/********************** SYMBOLS **********************/
DECL|macro|COFF_E_SYMNMLEN
mdefine_line|#define COFF_E_SYMNMLEN&t; 8&t;/* # characters in a short symbol name&t;*/
DECL|macro|COFF_E_FILNMLEN
mdefine_line|#define COFF_E_FILNMLEN&t;14&t;/* # characters in a file name&t;&t;*/
DECL|macro|COFF_E_DIMNUM
mdefine_line|#define COFF_E_DIMNUM&t; 4&t;/* # array dimensions in auxiliary entry */
multiline_comment|/*&n; *  All symbols and sections have the following definition&n; */
DECL|struct|COFF_syment
r_struct
id|COFF_syment
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
multiline_comment|/* Symbol name (first 8 characters) */
r_struct
(brace
DECL|member|e_zeroes
r_char
id|e_zeroes
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Leading zeros */
DECL|member|e_offset
r_char
id|e_offset
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Offset if this is a header section */
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
multiline_comment|/* Value (address) of the segment */
DECL|member|e_scnum
r_char
id|e_scnum
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Section number */
DECL|member|e_type
r_char
id|e_type
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Type of section */
DECL|member|e_sclass
r_char
id|e_sclass
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Loader class */
DECL|member|e_numaux
r_char
id|e_numaux
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Number of auxiliary entries which follow */
)brace
suffix:semicolon
DECL|macro|COFF_N_BTMASK
mdefine_line|#define COFF_N_BTMASK&t;(0xf)   /* Mask for important class bits */
DECL|macro|COFF_N_TMASK
mdefine_line|#define COFF_N_TMASK&t;(0x30)  /* Mask for important type bits  */
DECL|macro|COFF_N_BTSHFT
mdefine_line|#define COFF_N_BTSHFT&t;(4)     /* # bits to shift class field   */
DECL|macro|COFF_N_TSHIFT
mdefine_line|#define COFF_N_TSHIFT&t;(2)     /* # bits to shift type field    */
multiline_comment|/*&n; *  Auxiliary entries because the main table is too limiting.&n; */
DECL|union|COFF_auxent
r_union
id|COFF_auxent
(brace
multiline_comment|/*&n; *  Debugger information&n; */
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
multiline_comment|/*&n; *   Source file names (debugger information)&n; */
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
multiline_comment|/*&n; *   Section information&n; */
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
multiline_comment|/*&n; *   Transfer vector (branch table)&n; */
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
)brace
suffix:semicolon
DECL|macro|COFF_SYMENT
mdefine_line|#define&t;COFF_SYMENT&t;struct COFF_syment
DECL|macro|COFF_SYMESZ
mdefine_line|#define&t;COFF_SYMESZ&t;18&t;
DECL|macro|COFF_AUXENT
mdefine_line|#define&t;COFF_AUXENT&t;union COFF_auxent
DECL|macro|COFF_AUXESZ
mdefine_line|#define&t;COFF_AUXESZ&t;18
DECL|macro|COFF_ETEXT
mdefine_line|#define COFF_ETEXT&t;&quot;etext&quot;
multiline_comment|/********************** RELOCATION DIRECTIVES **********************/
DECL|struct|COFF_reloc
r_struct
id|COFF_reloc
(brace
DECL|member|r_vaddr
r_char
id|r_vaddr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Virtual address of item    */
DECL|member|r_symndx
r_char
id|r_symndx
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Symbol index in the symtab */
DECL|member|r_type
r_char
id|r_type
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Relocation type            */
)brace
suffix:semicolon
DECL|macro|COFF_RELOC
mdefine_line|#define COFF_RELOC struct COFF_reloc
DECL|macro|COFF_RELSZ
mdefine_line|#define COFF_RELSZ 10
DECL|macro|COFF_DEF_DATA_SECTION_ALIGNMENT
mdefine_line|#define COFF_DEF_DATA_SECTION_ALIGNMENT  4
DECL|macro|COFF_DEF_BSS_SECTION_ALIGNMENT
mdefine_line|#define COFF_DEF_BSS_SECTION_ALIGNMENT   4
DECL|macro|COFF_DEF_TEXT_SECTION_ALIGNMENT
mdefine_line|#define COFF_DEF_TEXT_SECTION_ALIGNMENT  4
multiline_comment|/* For new sections we haven&squot;t heard of before */
DECL|macro|COFF_DEF_SECTION_ALIGNMENT
mdefine_line|#define COFF_DEF_SECTION_ALIGNMENT       4
eof
