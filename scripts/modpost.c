multiline_comment|/* Postprocess module symbol versions&n; *&n; * Copyright 2003       Kai Germaschewski&n; *           2002-2003  Rusty Russell, IBM Corporation&n; *&n; * Based in part on module-init-tools/depmod.c,file2alias&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Usage: modpost vmlinux module1.o module2.o ...&n; */
macro_line|#include &quot;modpost.h&quot;
multiline_comment|/* Are we using CONFIG_MODVERSIONS? */
DECL|variable|modversions
r_int
id|modversions
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Do we have vmlinux? */
DECL|variable|have_vmlinux
r_int
id|have_vmlinux
op_assign
l_int|0
suffix:semicolon
r_void
DECL|function|fatal
id|fatal
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|arglist
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;FATAL: &quot;
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|arglist
comma
id|fmt
)paren
suffix:semicolon
id|vfprintf
c_func
(paren
id|stderr
comma
id|fmt
comma
id|arglist
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|arglist
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_void
DECL|function|warn
id|warn
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|arglist
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;WARNING: &quot;
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|arglist
comma
id|fmt
)paren
suffix:semicolon
id|vfprintf
c_func
(paren
id|stderr
comma
id|fmt
comma
id|arglist
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|arglist
)paren
suffix:semicolon
)brace
DECL|macro|NOFAIL
mdefine_line|#define NOFAIL(ptr)&t;do_nofail((ptr), __FILE__, __LINE__, #ptr)
DECL|function|do_nofail
r_void
op_star
id|do_nofail
c_func
(paren
r_void
op_star
id|ptr
comma
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_const
r_char
op_star
id|expr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
(brace
id|fatal
c_func
(paren
l_string|&quot;Memory allocation failure %s line %d: %s.&bslash;n&quot;
comma
id|file
comma
id|line
comma
id|expr
)paren
suffix:semicolon
)brace
r_return
id|ptr
suffix:semicolon
)brace
multiline_comment|/* A list of all modules we processed */
DECL|variable|modules
r_static
r_struct
id|module
op_star
id|modules
suffix:semicolon
r_struct
id|module
op_star
DECL|function|new_module
id|new_module
c_func
(paren
r_char
op_star
id|modname
)paren
(brace
r_struct
id|module
op_star
id|mod
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
multiline_comment|/* strip trailing .o */
id|p
op_assign
id|strstr
c_func
(paren
id|modname
comma
l_string|&quot;.o&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|mod
op_assign
id|NOFAIL
c_func
(paren
id|malloc
c_func
(paren
r_sizeof
(paren
op_star
id|mod
)paren
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|mod
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mod
)paren
)paren
suffix:semicolon
id|mod-&gt;name
op_assign
id|modname
suffix:semicolon
multiline_comment|/* add to list */
id|mod-&gt;next
op_assign
id|modules
suffix:semicolon
id|modules
op_assign
id|mod
suffix:semicolon
r_return
id|mod
suffix:semicolon
)brace
multiline_comment|/* A hash of all exported symbols,&n; * struct symbol is also used for lists of unresolved symbols */
DECL|macro|SYMBOL_HASH_SIZE
mdefine_line|#define SYMBOL_HASH_SIZE 1024
DECL|struct|symbol
r_struct
id|symbol
(brace
DECL|member|next
r_struct
id|symbol
op_star
id|next
suffix:semicolon
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|crc
r_int
r_int
id|crc
suffix:semicolon
DECL|member|crc_valid
r_int
id|crc_valid
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|symbolhash
r_static
r_struct
id|symbol
op_star
id|symbolhash
(braket
id|SYMBOL_HASH_SIZE
)braket
suffix:semicolon
multiline_comment|/* This is based on the hash agorithm from gdbm, via tdb */
DECL|function|tdb_hash
r_static
r_inline
r_int
r_int
id|tdb_hash
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|value
suffix:semicolon
multiline_comment|/* Used to compute the hash value.  */
r_int
id|i
suffix:semicolon
multiline_comment|/* Used to cycle through random values. */
multiline_comment|/* Set the initial value from the key size. */
r_for
c_loop
(paren
id|value
op_assign
l_int|0x238F13AF
op_star
id|strlen
c_func
(paren
id|name
)paren
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|name
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
id|value
op_assign
(paren
id|value
op_plus
(paren
(paren
(paren
r_int
r_char
op_star
)paren
id|name
)paren
(braket
id|i
)braket
op_lshift
(paren
id|i
op_star
l_int|5
op_mod
l_int|24
)paren
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|1103515243
op_star
id|value
op_plus
l_int|12345
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate a new symbols for use in the hash of exported symbols or&n; * the list of unresolved symbols per module */
r_struct
id|symbol
op_star
DECL|function|alloc_symbol
id|alloc_symbol
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|symbol
op_star
id|s
op_assign
id|NOFAIL
c_func
(paren
id|malloc
c_func
(paren
r_sizeof
(paren
op_star
id|s
)paren
op_plus
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|s
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|s
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|s-&gt;name
comma
id|name
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
multiline_comment|/* For the hash of exported symbols */
r_void
DECL|function|new_symbol
id|new_symbol
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|module
op_star
id|module
comma
r_int
r_int
op_star
id|crc
)paren
(brace
r_int
r_int
id|hash
suffix:semicolon
r_struct
id|symbol
op_star
r_new
op_assign
id|alloc_symbol
c_func
(paren
id|name
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|module
op_assign
id|module
suffix:semicolon
r_if
c_cond
(paren
id|crc
)paren
(brace
r_new
op_member_access_from_pointer
id|crc
op_assign
op_star
id|crc
suffix:semicolon
r_new
op_member_access_from_pointer
id|crc_valid
op_assign
l_int|1
suffix:semicolon
)brace
id|hash
op_assign
id|tdb_hash
c_func
(paren
id|name
)paren
op_mod
id|SYMBOL_HASH_SIZE
suffix:semicolon
r_new
op_member_access_from_pointer
id|next
op_assign
id|symbolhash
(braket
id|hash
)braket
suffix:semicolon
id|symbolhash
(braket
id|hash
)braket
op_assign
r_new
suffix:semicolon
)brace
r_struct
id|symbol
op_star
DECL|function|find_symbol
id|find_symbol
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|symbol
op_star
id|s
suffix:semicolon
multiline_comment|/* For our purposes, .foo matches foo.  PPC64 needs this. */
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
id|name
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|symbolhash
(braket
id|tdb_hash
c_func
(paren
id|name
)paren
op_mod
id|SYMBOL_HASH_SIZE
)braket
suffix:semicolon
id|s
suffix:semicolon
id|s
op_assign
id|s-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|s-&gt;name
comma
id|name
)paren
op_eq
l_int|0
)paren
r_return
id|s
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Add an exported symbol - it may have already been added without a&n; * CRC, in this case just update the CRC */
r_void
DECL|function|add_exported_symbol
id|add_exported_symbol
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|module
op_star
id|module
comma
r_int
r_int
op_star
id|crc
)paren
(brace
r_struct
id|symbol
op_star
id|s
op_assign
id|find_symbol
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
(brace
id|new_symbol
c_func
(paren
id|name
comma
id|modules
comma
id|crc
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|crc
)paren
(brace
id|s-&gt;crc
op_assign
op_star
id|crc
suffix:semicolon
id|s-&gt;crc_valid
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_void
op_star
DECL|function|grab_file
id|grab_file
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_int
r_int
op_star
id|size
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_void
op_star
id|map
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
id|filename
)paren
suffix:semicolon
m_abort
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
op_ne
l_int|0
)paren
(brace
id|perror
c_func
(paren
id|filename
)paren
suffix:semicolon
m_abort
(paren
)paren
suffix:semicolon
)brace
op_star
id|size
op_assign
id|st.st_size
suffix:semicolon
id|map
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
op_star
id|size
comma
id|PROT_READ
op_or
id|PROT_WRITE
comma
id|MAP_PRIVATE
comma
id|fd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mmap
op_eq
id|MAP_FAILED
)paren
(brace
id|perror
c_func
(paren
id|filename
)paren
suffix:semicolon
m_abort
(paren
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
id|map
suffix:semicolon
)brace
r_void
DECL|function|parse_elf
id|parse_elf
c_func
(paren
r_struct
id|elf_info
op_star
id|info
comma
r_const
r_char
op_star
id|filename
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|Elf_Ehdr
op_star
id|hdr
op_assign
id|info-&gt;hdr
suffix:semicolon
id|Elf_Shdr
op_star
id|sechdrs
suffix:semicolon
id|Elf_Sym
op_star
id|sym
suffix:semicolon
id|hdr
op_assign
id|grab_file
c_func
(paren
id|filename
comma
op_amp
id|info-&gt;size
)paren
suffix:semicolon
id|info-&gt;hdr
op_assign
id|hdr
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;size
OL
r_sizeof
(paren
op_star
id|hdr
)paren
)paren
r_goto
id|truncated
suffix:semicolon
multiline_comment|/* Fix endianness in ELF header */
id|hdr-&gt;e_shoff
op_assign
id|TO_NATIVE
c_func
(paren
id|hdr-&gt;e_shoff
)paren
suffix:semicolon
id|hdr-&gt;e_shstrndx
op_assign
id|TO_NATIVE
c_func
(paren
id|hdr-&gt;e_shstrndx
)paren
suffix:semicolon
id|hdr-&gt;e_shnum
op_assign
id|TO_NATIVE
c_func
(paren
id|hdr-&gt;e_shnum
)paren
suffix:semicolon
id|sechdrs
op_assign
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|hdr-&gt;e_shoff
suffix:semicolon
id|info-&gt;sechdrs
op_assign
id|sechdrs
suffix:semicolon
multiline_comment|/* Fix endianness in section headers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|hdr-&gt;e_shnum
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sechdrs
(braket
id|i
)braket
dot
id|sh_type
op_assign
id|TO_NATIVE
c_func
(paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_type
)paren
suffix:semicolon
id|sechdrs
(braket
id|i
)braket
dot
id|sh_offset
op_assign
id|TO_NATIVE
c_func
(paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_offset
)paren
suffix:semicolon
id|sechdrs
(braket
id|i
)braket
dot
id|sh_size
op_assign
id|TO_NATIVE
c_func
(paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_size
)paren
suffix:semicolon
id|sechdrs
(braket
id|i
)braket
dot
id|sh_link
op_assign
id|TO_NATIVE
c_func
(paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_link
)paren
suffix:semicolon
)brace
multiline_comment|/* Find symbol table. */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|hdr-&gt;e_shnum
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_offset
OG
id|info-&gt;size
)paren
r_goto
id|truncated
suffix:semicolon
r_if
c_cond
(paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_type
op_ne
id|SHT_SYMTAB
)paren
r_continue
suffix:semicolon
id|info-&gt;symtab_start
op_assign
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|sechdrs
(braket
id|i
)braket
dot
id|sh_offset
suffix:semicolon
id|info-&gt;symtab_stop
op_assign
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|sechdrs
(braket
id|i
)braket
dot
id|sh_offset
op_plus
id|sechdrs
(braket
id|i
)braket
dot
id|sh_size
suffix:semicolon
id|info-&gt;strtab
op_assign
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|sechdrs
(braket
id|sechdrs
(braket
id|i
)braket
dot
id|sh_link
)braket
dot
id|sh_offset
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;symtab_start
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;modpost: %s no symtab?&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
m_abort
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Fix endianness in symbols */
r_for
c_loop
(paren
id|sym
op_assign
id|info-&gt;symtab_start
suffix:semicolon
id|sym
OL
id|info-&gt;symtab_stop
suffix:semicolon
id|sym
op_increment
)paren
(brace
id|sym-&gt;st_shndx
op_assign
id|TO_NATIVE
c_func
(paren
id|sym-&gt;st_shndx
)paren
suffix:semicolon
id|sym-&gt;st_name
op_assign
id|TO_NATIVE
c_func
(paren
id|sym-&gt;st_name
)paren
suffix:semicolon
id|sym-&gt;st_value
op_assign
id|TO_NATIVE
c_func
(paren
id|sym-&gt;st_value
)paren
suffix:semicolon
id|sym-&gt;st_size
op_assign
id|TO_NATIVE
c_func
(paren
id|sym-&gt;st_size
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
id|truncated
suffix:colon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;modpost: %s is truncated.&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
m_abort
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|parse_elf_finish
id|parse_elf_finish
c_func
(paren
r_struct
id|elf_info
op_star
id|info
)paren
(brace
id|munmap
c_func
(paren
id|info-&gt;hdr
comma
id|info-&gt;size
)paren
suffix:semicolon
)brace
DECL|macro|CRC_PFX
mdefine_line|#define CRC_PFX     MODULE_SYMBOL_PREFIX &quot;__crc_&quot;
DECL|macro|KSYMTAB_PFX
mdefine_line|#define KSYMTAB_PFX MODULE_SYMBOL_PREFIX &quot;__ksymtab_&quot;
r_void
DECL|function|handle_modversions
id|handle_modversions
c_func
(paren
r_struct
id|module
op_star
id|mod
comma
r_struct
id|elf_info
op_star
id|info
comma
id|Elf_Sym
op_star
id|sym
comma
r_const
r_char
op_star
id|symname
)paren
(brace
r_struct
id|symbol
op_star
id|s
suffix:semicolon
r_int
r_int
id|crc
suffix:semicolon
r_switch
c_cond
(paren
id|sym-&gt;st_shndx
)paren
(brace
r_case
id|SHN_COMMON
suffix:colon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;*** Warning: &bslash;&quot;%s&bslash;&quot; [%s] is COMMON symbol&bslash;n&quot;
comma
id|symname
comma
id|mod-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SHN_ABS
suffix:colon
multiline_comment|/* CRC&squot;d symbol */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|symname
comma
id|CRC_PFX
comma
id|strlen
c_func
(paren
id|CRC_PFX
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|crc
op_assign
(paren
r_int
r_int
)paren
id|sym-&gt;st_value
suffix:semicolon
id|add_exported_symbol
c_func
(paren
id|symname
op_plus
id|strlen
c_func
(paren
id|CRC_PFX
)paren
comma
id|mod
comma
op_amp
id|crc
)paren
suffix:semicolon
id|modversions
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SHN_UNDEF
suffix:colon
multiline_comment|/* undefined symbol */
r_if
c_cond
(paren
id|ELF_ST_BIND
c_func
(paren
id|sym-&gt;st_info
)paren
op_ne
id|STB_GLOBAL
)paren
r_break
suffix:semicolon
multiline_comment|/* ignore global offset table */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|symname
comma
l_string|&quot;_GLOBAL_OFFSET_TABLE_&quot;
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;hdr-&gt;e_machine
op_eq
id|EM_SPARC
op_logical_or
id|info-&gt;hdr-&gt;e_machine
op_eq
id|EM_SPARCV9
)paren
(brace
multiline_comment|/* Ignore register directives. */
r_if
c_cond
(paren
id|ELF_ST_TYPE
c_func
(paren
id|sym-&gt;st_info
)paren
op_eq
id|STT_REGISTER
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|symname
comma
id|MODULE_SYMBOL_PREFIX
comma
id|strlen
c_func
(paren
id|MODULE_SYMBOL_PREFIX
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|s
op_assign
id|alloc_symbol
c_func
(paren
id|symname
op_plus
id|strlen
c_func
(paren
id|MODULE_SYMBOL_PREFIX
)paren
)paren
suffix:semicolon
multiline_comment|/* add to list */
id|s-&gt;next
op_assign
id|mod-&gt;unres
suffix:semicolon
id|mod-&gt;unres
op_assign
id|s
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* All exported symbols */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|symname
comma
id|KSYMTAB_PFX
comma
id|strlen
c_func
(paren
id|KSYMTAB_PFX
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|add_exported_symbol
c_func
(paren
id|symname
op_plus
id|strlen
c_func
(paren
id|KSYMTAB_PFX
)paren
comma
id|mod
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
r_void
DECL|function|read_symbols
id|read_symbols
c_func
(paren
r_char
op_star
id|modname
)paren
(brace
r_const
r_char
op_star
id|symname
suffix:semicolon
r_struct
id|module
op_star
id|mod
suffix:semicolon
r_struct
id|elf_info
id|info
op_assign
(brace
)brace
suffix:semicolon
r_struct
id|symbol
op_star
id|s
suffix:semicolon
id|Elf_Sym
op_star
id|sym
suffix:semicolon
multiline_comment|/* When there&squot;s no vmlinux, don&squot;t print warnings about&n;&t; * unresolved symbols (since there&squot;ll be too many ;) */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|modname
comma
l_string|&quot;vmlinux&quot;
)paren
op_eq
l_int|0
)paren
id|have_vmlinux
op_assign
l_int|1
suffix:semicolon
id|parse_elf
c_func
(paren
op_amp
id|info
comma
id|modname
)paren
suffix:semicolon
id|mod
op_assign
id|new_module
c_func
(paren
id|modname
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sym
op_assign
id|info.symtab_start
suffix:semicolon
id|sym
OL
id|info.symtab_stop
suffix:semicolon
id|sym
op_increment
)paren
(brace
id|symname
op_assign
id|info.strtab
op_plus
id|sym-&gt;st_name
suffix:semicolon
id|handle_modversions
c_func
(paren
id|mod
comma
op_amp
id|info
comma
id|sym
comma
id|symname
)paren
suffix:semicolon
id|handle_moddevtable
c_func
(paren
id|mod
comma
op_amp
id|info
comma
id|sym
comma
id|symname
)paren
suffix:semicolon
)brace
id|parse_elf_finish
c_func
(paren
op_amp
id|info
)paren
suffix:semicolon
multiline_comment|/* Our trick to get versioning for struct_module - it&squot;s&n;&t; * never passed as an argument to an exported function, so&n;&t; * the automatic versioning doesn&squot;t pick it up, but it&squot;s really&n;&t; * important anyhow */
r_if
c_cond
(paren
id|modversions
)paren
(brace
id|s
op_assign
id|alloc_symbol
c_func
(paren
l_string|&quot;struct_module&quot;
)paren
suffix:semicolon
multiline_comment|/* add to list */
id|s-&gt;next
op_assign
id|mod-&gt;unres
suffix:semicolon
id|mod-&gt;unres
op_assign
id|s
suffix:semicolon
)brace
)brace
DECL|macro|SZ
mdefine_line|#define SZ 500
multiline_comment|/* We first write the generated file into memory using the&n; * following helper, then compare to the file on disk and&n; * only update the later if anything changed */
r_void
id|__attribute__
c_func
(paren
(paren
id|format
c_func
(paren
id|printf
comma
l_int|2
comma
l_int|3
)paren
)paren
)paren
DECL|function|buf_printf
id|buf_printf
c_func
(paren
r_struct
id|buffer
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_char
id|tmp
(braket
id|SZ
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|len
op_assign
id|vsnprintf
c_func
(paren
id|tmp
comma
id|SZ
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;size
op_minus
id|buf-&gt;pos
OL
id|len
op_plus
l_int|1
)paren
(brace
id|buf-&gt;size
op_add_assign
l_int|128
suffix:semicolon
id|buf-&gt;p
op_assign
id|realloc
c_func
(paren
id|buf-&gt;p
comma
id|buf-&gt;size
)paren
suffix:semicolon
)brace
id|strncpy
c_func
(paren
id|buf-&gt;p
op_plus
id|buf-&gt;pos
comma
id|tmp
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|buf-&gt;pos
op_add_assign
id|len
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
r_void
DECL|function|buf_write
id|buf_write
c_func
(paren
r_struct
id|buffer
op_star
id|buf
comma
r_const
r_char
op_star
id|s
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|buf-&gt;size
op_minus
id|buf-&gt;pos
OL
id|len
)paren
(brace
id|buf-&gt;size
op_add_assign
id|len
suffix:semicolon
id|buf-&gt;p
op_assign
id|realloc
c_func
(paren
id|buf-&gt;p
comma
id|buf-&gt;size
)paren
suffix:semicolon
)brace
id|strncpy
c_func
(paren
id|buf-&gt;p
op_plus
id|buf-&gt;pos
comma
id|s
comma
id|len
)paren
suffix:semicolon
id|buf-&gt;pos
op_add_assign
id|len
suffix:semicolon
)brace
multiline_comment|/* Header for the generated file */
r_void
DECL|function|add_header
id|add_header
c_func
(paren
r_struct
id|buffer
op_star
id|b
)paren
(brace
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;#include &lt;linux/module.h&gt;&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;#include &lt;linux/vermagic.h&gt;&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;#include &lt;linux/compiler.h&gt;&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;const char vermagic[]&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;__attribute__((section(&bslash;&quot;__vermagic&bslash;&quot;))) =&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;VERMAGIC_STRING;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Record CRCs for unresolved symbols */
r_void
DECL|function|add_versions
id|add_versions
c_func
(paren
r_struct
id|buffer
op_star
id|b
comma
r_struct
id|module
op_star
id|mod
)paren
(brace
r_struct
id|symbol
op_star
id|s
comma
op_star
id|exp
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|mod-&gt;unres
suffix:semicolon
id|s
suffix:semicolon
id|s
op_assign
id|s-&gt;next
)paren
(brace
id|exp
op_assign
id|find_symbol
c_func
(paren
id|s-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exp
op_logical_or
id|exp-&gt;module
op_eq
id|mod
)paren
(brace
r_if
c_cond
(paren
id|have_vmlinux
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;*** Warning: &bslash;&quot;%s&bslash;&quot; [%s.ko] &quot;
l_string|&quot;undefined!&bslash;n&quot;
comma
id|s-&gt;name
comma
id|mod-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|s-&gt;module
op_assign
id|exp-&gt;module
suffix:semicolon
id|s-&gt;crc_valid
op_assign
id|exp-&gt;crc_valid
suffix:semicolon
id|s-&gt;crc
op_assign
id|exp-&gt;crc
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|modversions
)paren
r_return
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;static const struct modversion_info ____versions[]&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;__attribute__((section(&bslash;&quot;__versions&bslash;&quot;))) = {&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|mod-&gt;unres
suffix:semicolon
id|s
suffix:semicolon
id|s
op_assign
id|s-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;module
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;crc_valid
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;*** Warning: &bslash;&quot;%s&bslash;&quot; [%s.ko] &quot;
l_string|&quot;has no CRC!&bslash;n&quot;
comma
id|s-&gt;name
comma
id|mod-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;t{ %#8x, &bslash;&quot;%s&bslash;&quot; },&bslash;n&quot;
comma
id|s-&gt;crc
comma
id|s-&gt;name
)paren
suffix:semicolon
)brace
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;};&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_void
DECL|function|add_depends
id|add_depends
c_func
(paren
r_struct
id|buffer
op_star
id|b
comma
r_struct
id|module
op_star
id|mod
comma
r_struct
id|module
op_star
id|modules
)paren
(brace
r_struct
id|symbol
op_star
id|s
suffix:semicolon
r_struct
id|module
op_star
id|m
suffix:semicolon
r_int
id|first
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|m
op_assign
id|modules
suffix:semicolon
id|m
suffix:semicolon
id|m
op_assign
id|m-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|m-&gt;name
comma
l_string|&quot;vmlinux&quot;
)paren
op_eq
l_int|0
)paren
id|m-&gt;seen
op_assign
l_int|1
suffix:semicolon
r_else
id|m-&gt;seen
op_assign
l_int|0
suffix:semicolon
)brace
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;static const char __module_depends[]&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;__attribute_used__&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;__attribute__((section(&bslash;&quot;.modinfo&bslash;&quot;))) =&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;&quot;depends=&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|mod-&gt;unres
suffix:semicolon
id|s
suffix:semicolon
id|s
op_assign
id|s-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;module
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;module-&gt;seen
)paren
r_continue
suffix:semicolon
id|s-&gt;module-&gt;seen
op_assign
l_int|1
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;%s%s&quot;
comma
id|first
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;,&quot;
comma
id|strrchr
c_func
(paren
id|s-&gt;module-&gt;name
comma
l_char|&squot;/&squot;
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
)brace
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;&quot;;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_void
DECL|function|write_if_changed
id|write_if_changed
c_func
(paren
r_struct
id|buffer
op_star
id|b
comma
r_const
r_char
op_star
id|fname
)paren
(brace
r_char
op_star
id|tmp
suffix:semicolon
id|FILE
op_star
id|file
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
id|file
op_assign
id|fopen
c_func
(paren
id|fname
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|write
suffix:semicolon
r_if
c_cond
(paren
id|fstat
c_func
(paren
id|fileno
c_func
(paren
id|file
)paren
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
r_goto
id|close_write
suffix:semicolon
r_if
c_cond
(paren
id|st.st_size
op_ne
id|b-&gt;pos
)paren
r_goto
id|close_write
suffix:semicolon
id|tmp
op_assign
id|NOFAIL
c_func
(paren
id|malloc
c_func
(paren
id|b-&gt;pos
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fread
c_func
(paren
id|tmp
comma
l_int|1
comma
id|b-&gt;pos
comma
id|file
)paren
op_ne
id|b-&gt;pos
)paren
r_goto
id|free_write
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|tmp
comma
id|b-&gt;p
comma
id|b-&gt;pos
)paren
op_ne
l_int|0
)paren
r_goto
id|free_write
suffix:semicolon
id|free
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
suffix:semicolon
id|free_write
suffix:colon
id|free
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|close_write
suffix:colon
id|fclose
c_func
(paren
id|file
)paren
suffix:semicolon
id|write
suffix:colon
id|file
op_assign
id|fopen
c_func
(paren
id|fname
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
(brace
id|perror
c_func
(paren
id|fname
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fwrite
c_func
(paren
id|b-&gt;p
comma
l_int|1
comma
id|b-&gt;pos
comma
id|file
)paren
op_ne
id|b-&gt;pos
)paren
(brace
id|perror
c_func
(paren
id|fname
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
r_int
DECL|function|main
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_struct
id|module
op_star
id|mod
suffix:semicolon
r_struct
id|buffer
id|buf
op_assign
(brace
)brace
suffix:semicolon
r_char
id|fname
(braket
id|SZ
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|argv
op_increment
)paren
(brace
id|read_symbols
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|mod
op_assign
id|modules
suffix:semicolon
id|mod
suffix:semicolon
id|mod
op_assign
id|mod-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|mod-&gt;name
comma
l_string|&quot;vmlinux&quot;
)paren
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|buf.pos
op_assign
l_int|0
suffix:semicolon
id|add_header
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|add_versions
c_func
(paren
op_amp
id|buf
comma
id|mod
)paren
suffix:semicolon
id|add_depends
c_func
(paren
op_amp
id|buf
comma
id|mod
comma
id|modules
)paren
suffix:semicolon
id|add_moddevtable
c_func
(paren
op_amp
id|buf
comma
id|mod
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|fname
comma
l_string|&quot;%s.mod.c&quot;
comma
id|mod-&gt;name
)paren
suffix:semicolon
id|write_if_changed
c_func
(paren
op_amp
id|buf
comma
id|fname
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
