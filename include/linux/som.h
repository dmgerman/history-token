macro_line|#ifndef _LINUX_SOM_H
DECL|macro|_LINUX_SOM_H
mdefine_line|#define _LINUX_SOM_H
multiline_comment|/* File format definition for SOM executables / shared libraries */
multiline_comment|/* we need struct timespec */
macro_line|#include &lt;linux/time.h&gt;
DECL|macro|SOM_PAGESIZE
mdefine_line|#define SOM_PAGESIZE 4096
multiline_comment|/* this is the SOM header */
DECL|struct|som_hdr
r_struct
id|som_hdr
(brace
DECL|member|system_id
r_int
id|system_id
suffix:semicolon
multiline_comment|/* magic number - system */
DECL|member|a_magic
r_int
id|a_magic
suffix:semicolon
multiline_comment|/* magic number - file type */
DECL|member|version_id
r_int
r_int
id|version_id
suffix:semicolon
multiline_comment|/* versiod ID: YYMMDDHH */
DECL|member|file_time
r_struct
id|timespec
id|file_time
suffix:semicolon
multiline_comment|/* system clock */
DECL|member|entry_space
r_int
r_int
id|entry_space
suffix:semicolon
multiline_comment|/* space for entry point */
DECL|member|entry_subspace
r_int
r_int
id|entry_subspace
suffix:semicolon
multiline_comment|/* subspace for entry point */
DECL|member|entry_offset
r_int
r_int
id|entry_offset
suffix:semicolon
multiline_comment|/* offset of entry point */
DECL|member|aux_header_location
r_int
r_int
id|aux_header_location
suffix:semicolon
multiline_comment|/* auxiliary header location */
DECL|member|aux_header_size
r_int
r_int
id|aux_header_size
suffix:semicolon
multiline_comment|/* auxiliary header size */
DECL|member|som_length
r_int
r_int
id|som_length
suffix:semicolon
multiline_comment|/* length of entire SOM */
DECL|member|presumed_dp
r_int
r_int
id|presumed_dp
suffix:semicolon
multiline_comment|/* compiler&squot;s DP value */
DECL|member|space_location
r_int
r_int
id|space_location
suffix:semicolon
multiline_comment|/* space dictionary location */
DECL|member|space_total
r_int
r_int
id|space_total
suffix:semicolon
multiline_comment|/* number of space entries */
DECL|member|subspace_location
r_int
r_int
id|subspace_location
suffix:semicolon
multiline_comment|/* subspace entries location */
DECL|member|subspace_total
r_int
r_int
id|subspace_total
suffix:semicolon
multiline_comment|/* number of subspace entries */
DECL|member|loader_fixup_location
r_int
r_int
id|loader_fixup_location
suffix:semicolon
multiline_comment|/* MPE/iX loader fixup */
DECL|member|loader_fixup_total
r_int
r_int
id|loader_fixup_total
suffix:semicolon
multiline_comment|/* number of fixup records */
DECL|member|space_strings_location
r_int
r_int
id|space_strings_location
suffix:semicolon
multiline_comment|/* (sub)space names */
DECL|member|space_strings_size
r_int
r_int
id|space_strings_size
suffix:semicolon
multiline_comment|/* size of strings area */
DECL|member|init_array_location
r_int
r_int
id|init_array_location
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|init_array_total
r_int
r_int
id|init_array_total
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|compiler_location
r_int
r_int
id|compiler_location
suffix:semicolon
multiline_comment|/* module dictionary */
DECL|member|compiler_total
r_int
r_int
id|compiler_total
suffix:semicolon
multiline_comment|/* number of modules */
DECL|member|symbol_location
r_int
r_int
id|symbol_location
suffix:semicolon
multiline_comment|/* symbol dictionary */
DECL|member|symbol_total
r_int
r_int
id|symbol_total
suffix:semicolon
multiline_comment|/* number of symbols */
DECL|member|fixup_request_location
r_int
r_int
id|fixup_request_location
suffix:semicolon
multiline_comment|/* fixup requests */
DECL|member|fixup_request_total
r_int
r_int
id|fixup_request_total
suffix:semicolon
multiline_comment|/* number of fixup requests */
DECL|member|symbol_strings_location
r_int
r_int
id|symbol_strings_location
suffix:semicolon
multiline_comment|/* module &amp; symbol names area */
DECL|member|symbol_strings_size
r_int
r_int
id|symbol_strings_size
suffix:semicolon
multiline_comment|/* size of strings area */
DECL|member|unloadable_sp_location
r_int
r_int
id|unloadable_sp_location
suffix:semicolon
multiline_comment|/* unloadable spaces location */
DECL|member|unloadable_sp_size
r_int
r_int
id|unloadable_sp_size
suffix:semicolon
multiline_comment|/* size of data */
DECL|member|checksum
r_int
r_int
id|checksum
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* values for system_id */
DECL|macro|SOM_SID_PARISC_1_0
mdefine_line|#define SOM_SID_PARISC_1_0&t;0x020b
DECL|macro|SOM_SID_PARISC_1_1
mdefine_line|#define SOM_SID_PARISC_1_1&t;0x0210
DECL|macro|SOM_SID_PARISC_2_0
mdefine_line|#define SOM_SID_PARISC_2_0&t;0x0214
multiline_comment|/* values for a_magic */
DECL|macro|SOM_LIB_EXEC
mdefine_line|#define SOM_LIB_EXEC&t;&t;0x0104
DECL|macro|SOM_RELOCATABLE
mdefine_line|#define SOM_RELOCATABLE&t;&t;0x0106
DECL|macro|SOM_EXEC_NONSHARE
mdefine_line|#define SOM_EXEC_NONSHARE&t;0x0107
DECL|macro|SOM_EXEC_SHARE
mdefine_line|#define SOM_EXEC_SHARE&t;&t;0x0108
DECL|macro|SOM_EXEC_DEMAND
mdefine_line|#define SOM_EXEC_DEMAND&t;&t;0x010B
DECL|macro|SOM_LIB_DYN
mdefine_line|#define SOM_LIB_DYN&t;&t;0x010D
DECL|macro|SOM_LIB_SHARE
mdefine_line|#define SOM_LIB_SHARE&t;&t;0x010E
DECL|macro|SOM_LIB_RELOC
mdefine_line|#define SOM_LIB_RELOC&t;&t;0x0619
multiline_comment|/* values for version_id.  Decimal not hex, yes.  Grr. */
DECL|macro|SOM_ID_OLD
mdefine_line|#define SOM_ID_OLD&t;&t;85082112
DECL|macro|SOM_ID_NEW
mdefine_line|#define SOM_ID_NEW&t;&t;87102412
DECL|struct|aux_id
r_struct
id|aux_id
(brace
DECL|member|mandatory
r_int
r_int
id|mandatory
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* the linker must understand this */
DECL|member|copy
r_int
r_int
id|copy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Must be copied by the linker */
DECL|member|append
r_int
r_int
id|append
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Must be merged by the linker */
DECL|member|ignore
r_int
r_int
id|ignore
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Discard section if unknown */
DECL|member|reserved
r_int
r_int
id|reserved
suffix:colon
l_int|12
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* Header type */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* length of _following_ data */
)brace
suffix:semicolon
multiline_comment|/* The Exec Auxiliary Header.  Called The HP-UX Header within HP apparently. */
DECL|struct|som_exec_auxhdr
r_struct
id|som_exec_auxhdr
(brace
DECL|member|som_auxhdr
r_struct
id|aux_id
id|som_auxhdr
suffix:semicolon
DECL|member|exec_tsize
r_int
id|exec_tsize
suffix:semicolon
multiline_comment|/* Text size in bytes */
DECL|member|exec_tmem
r_int
id|exec_tmem
suffix:semicolon
multiline_comment|/* Address to load text at */
DECL|member|exec_tfile
r_int
id|exec_tfile
suffix:semicolon
multiline_comment|/* Location of text in file */
DECL|member|exec_dsize
r_int
id|exec_dsize
suffix:semicolon
multiline_comment|/* Data size in bytes */
DECL|member|exec_dmem
r_int
id|exec_dmem
suffix:semicolon
multiline_comment|/* Address to load data at */
DECL|member|exec_dfile
r_int
id|exec_dfile
suffix:semicolon
multiline_comment|/* Location of data in file */
DECL|member|exec_bsize
r_int
id|exec_bsize
suffix:semicolon
multiline_comment|/* Uninitialised data (bss) */
DECL|member|exec_entry
r_int
id|exec_entry
suffix:semicolon
multiline_comment|/* Address to start executing */
DECL|member|exec_flags
r_int
id|exec_flags
suffix:semicolon
multiline_comment|/* loader flags */
DECL|member|exec_bfill
r_int
id|exec_bfill
suffix:semicolon
multiline_comment|/* initialisation value for bss */
)brace
suffix:semicolon
multiline_comment|/* Oh, the things people do to avoid casts.  Shame it&squot;ll break with gcc&squot;s&n; * new aliasing rules really.&n; */
DECL|union|name_pt
r_union
id|name_pt
(brace
DECL|member|n_name
r_char
op_star
id|n_name
suffix:semicolon
DECL|member|n_strx
r_int
r_int
id|n_strx
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The Space Dictionary */
DECL|struct|space_dictionary_record
r_struct
id|space_dictionary_record
(brace
DECL|member|name
r_union
id|name_pt
id|name
suffix:semicolon
multiline_comment|/* index to subspace name */
DECL|member|is_loadable
r_int
r_int
id|is_loadable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* loadable */
DECL|member|is_defined
r_int
r_int
id|is_defined
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* defined within file */
DECL|member|is_private
r_int
r_int
id|is_private
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* not sharable */
DECL|member|has_intermediate_code
r_int
r_int
id|has_intermediate_code
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* contains intermediate code */
DECL|member|is_tspecific
r_int
r_int
id|is_tspecific
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* thread specific */
DECL|member|reserved
r_int
r_int
id|reserved
suffix:colon
l_int|11
suffix:semicolon
multiline_comment|/* for future expansion */
DECL|member|sort_key
r_int
r_int
id|sort_key
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* for linker */
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* for future expansion */
DECL|member|space_number
r_int
id|space_number
suffix:semicolon
multiline_comment|/* index */
DECL|member|subspace_index
r_int
id|subspace_index
suffix:semicolon
multiline_comment|/* index into subspace dict */
DECL|member|subspace_quantity
r_int
r_int
id|subspace_quantity
suffix:semicolon
multiline_comment|/* number of subspaces */
DECL|member|loader_fix_index
r_int
id|loader_fix_index
suffix:semicolon
multiline_comment|/* for loader */
DECL|member|loader_fix_quantity
r_int
r_int
id|loader_fix_quantity
suffix:semicolon
multiline_comment|/* for loader */
DECL|member|init_pointer_index
r_int
id|init_pointer_index
suffix:semicolon
multiline_comment|/* data pointer array index */
DECL|member|init_pointer_quantity
r_int
r_int
id|init_pointer_quantity
suffix:semicolon
multiline_comment|/* number of data pointers */
)brace
suffix:semicolon
multiline_comment|/* The Subspace Dictionary */
DECL|struct|subspace_dictionary_record
r_struct
id|subspace_dictionary_record
(brace
DECL|member|space_index
r_int
id|space_index
suffix:semicolon
DECL|member|access_control_bits
r_int
r_int
id|access_control_bits
suffix:colon
l_int|7
suffix:semicolon
DECL|member|memory_resident
r_int
r_int
id|memory_resident
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dup_common
r_int
r_int
id|dup_common
suffix:colon
l_int|1
suffix:semicolon
DECL|member|is_common
r_int
r_int
id|is_common
suffix:colon
l_int|1
suffix:semicolon
DECL|member|quadrant
r_int
r_int
id|quadrant
suffix:colon
l_int|2
suffix:semicolon
DECL|member|initially_frozen
r_int
r_int
id|initially_frozen
suffix:colon
l_int|1
suffix:semicolon
DECL|member|is_first
r_int
r_int
id|is_first
suffix:colon
l_int|1
suffix:semicolon
DECL|member|code_only
r_int
r_int
id|code_only
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sort_key
r_int
r_int
id|sort_key
suffix:colon
l_int|8
suffix:semicolon
DECL|member|replicate_init
r_int
r_int
id|replicate_init
suffix:colon
l_int|1
suffix:semicolon
DECL|member|continuation
r_int
r_int
id|continuation
suffix:colon
l_int|1
suffix:semicolon
DECL|member|is_tspecific
r_int
r_int
id|is_tspecific
suffix:colon
l_int|1
suffix:semicolon
DECL|member|is_comdat
r_int
r_int
id|is_comdat
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
suffix:colon
l_int|4
suffix:semicolon
DECL|member|file_loc_init_value
r_int
id|file_loc_init_value
suffix:semicolon
DECL|member|initialization_length
r_int
r_int
id|initialization_length
suffix:semicolon
DECL|member|subspace_start
r_int
r_int
id|subspace_start
suffix:semicolon
DECL|member|subspace_length
r_int
r_int
id|subspace_length
suffix:semicolon
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:colon
l_int|5
suffix:semicolon
DECL|member|alignment
r_int
r_int
id|alignment
suffix:colon
l_int|27
suffix:semicolon
DECL|member|name
r_union
id|name_pt
id|name
suffix:semicolon
DECL|member|fixup_request_index
r_int
id|fixup_request_index
suffix:semicolon
DECL|member|fixup_request_quantity
r_int
r_int
id|fixup_request_quantity
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_SOM_H */
eof
