multiline_comment|/* Postprocess module symbol versions&n; *&n; * Copyright 2003       Kai Germaschewski&n; *           2002-2003  Rusty Russell, IBM Corporation&n; *&n; * Based in part on module-init-tools/depmod.c,file2alias&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Usage: modpost vmlinux module1.o module2.o ...&n; */
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &quot;modpost.h&quot;
multiline_comment|/* Are we using CONFIG_MODVERSIONS? */
DECL|variable|modversions
r_int
id|modversions
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Warn about undefined symbols? (do so if we have vmlinux) */
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
DECL|function|find_module
id|find_module
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
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|mod-&gt;name
comma
id|modname
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_return
id|mod
suffix:semicolon
)brace
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
comma
op_star
id|s
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
id|p
op_assign
id|NOFAIL
c_func
(paren
id|strdup
c_func
(paren
id|modname
)paren
)paren
suffix:semicolon
multiline_comment|/* strip trailing .o */
r_if
c_cond
(paren
(paren
id|s
op_assign
id|strrchr
c_func
(paren
id|p
comma
l_char|&squot;.&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|s
comma
l_string|&quot;.o&quot;
)paren
op_eq
l_int|0
)paren
op_star
id|s
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* add to list */
id|mod-&gt;name
op_assign
id|p
suffix:semicolon
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
comma
r_struct
id|symbol
op_star
id|next
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
id|s-&gt;next
op_assign
id|next
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
suffix:semicolon
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
op_assign
id|symbolhash
(braket
id|hash
)braket
op_assign
id|alloc_symbol
c_func
(paren
id|name
comma
id|symbolhash
(braket
id|hash
)braket
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
id|module
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
op_logical_or
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
r_return
l_int|NULL
suffix:semicolon
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
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_eq
id|MAP_FAILED
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|map
suffix:semicolon
)brace
multiline_comment|/*&n;   Return a copy of the next line in a mmap&squot;ed file.&n;   spaces in the beginning of the line is trimmed away.&n;   Return a pointer to a static buffer.&n;*/
r_char
op_star
DECL|function|get_next_line
id|get_next_line
c_func
(paren
r_int
r_int
op_star
id|pos
comma
r_void
op_star
id|file
comma
r_int
r_int
id|size
)paren
(brace
r_static
r_char
id|line
(braket
l_int|4096
)braket
suffix:semicolon
r_int
id|skip
op_assign
l_int|1
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|p
op_assign
(paren
r_char
op_star
)paren
id|file
op_plus
op_star
id|pos
suffix:semicolon
r_char
op_star
id|s
op_assign
id|line
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_star
id|pos
OL
id|size
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
)paren
(brace
r_if
c_cond
(paren
id|skip
op_logical_and
id|isspace
c_func
(paren
op_star
id|p
)paren
)paren
(brace
id|p
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|skip
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_ne
l_char|&squot;&bslash;n&squot;
op_logical_and
(paren
op_star
id|pos
OL
id|size
)paren
)paren
(brace
id|len
op_increment
suffix:semicolon
op_star
id|s
op_increment
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|4095
)paren
r_break
suffix:semicolon
multiline_comment|/* Too long, stop */
)brace
r_else
(brace
multiline_comment|/* End of string */
op_star
id|s
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|line
suffix:semicolon
)brace
)brace
multiline_comment|/* End of buffer */
r_return
l_int|NULL
suffix:semicolon
)brace
r_void
DECL|function|release_file
id|release_file
c_func
(paren
r_void
op_star
id|file
comma
r_int
r_int
id|size
)paren
(brace
id|munmap
c_func
(paren
id|file
comma
id|size
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|hdr
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
id|hdr-&gt;e_machine
op_assign
id|TO_NATIVE
c_func
(paren
id|hdr-&gt;e_machine
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
id|sechdrs
(braket
id|i
)braket
dot
id|sh_name
op_assign
id|TO_NATIVE
c_func
(paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_name
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
r_const
r_char
op_star
id|secstrings
op_assign
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|sechdrs
(braket
id|hdr-&gt;e_shstrndx
)braket
dot
id|sh_offset
suffix:semicolon
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
id|strcmp
c_func
(paren
id|secstrings
op_plus
id|sechdrs
(braket
id|i
)braket
dot
id|sh_name
comma
l_string|&quot;.modinfo&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|info-&gt;modinfo
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
id|info-&gt;modinfo_len
op_assign
id|sechdrs
(braket
id|i
)braket
dot
id|sh_size
suffix:semicolon
)brace
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
id|release_file
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
multiline_comment|/* ignore __this_module, it will be resolved shortly */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|symname
comma
id|MODULE_SYMBOL_PREFIX
l_string|&quot;__this_module&quot;
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
macro_line|#ifdef STT_REGISTER
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
macro_line|#endif
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
id|mod-&gt;unres
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
comma
id|mod-&gt;unres
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|symname
comma
id|MODULE_SYMBOL_PREFIX
l_string|&quot;init_module&quot;
)paren
op_eq
l_int|0
)paren
id|mod-&gt;has_init
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|symname
comma
id|MODULE_SYMBOL_PREFIX
l_string|&quot;cleanup_module&quot;
)paren
op_eq
l_int|0
)paren
id|mod-&gt;has_cleanup
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_int
DECL|function|is_vmlinux
id|is_vmlinux
c_func
(paren
r_const
r_char
op_star
id|modname
)paren
(brace
r_const
r_char
op_star
id|myname
suffix:semicolon
r_if
c_cond
(paren
(paren
id|myname
op_assign
id|strrchr
c_func
(paren
id|modname
comma
l_char|&squot;/&squot;
)paren
)paren
)paren
id|myname
op_increment
suffix:semicolon
r_else
id|myname
op_assign
id|modname
suffix:semicolon
r_return
id|strcmp
c_func
(paren
id|myname
comma
l_string|&quot;vmlinux&quot;
)paren
op_eq
l_int|0
suffix:semicolon
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
id|Elf_Sym
op_star
id|sym
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
multiline_comment|/* When there&squot;s no vmlinux, don&squot;t print warnings about&n;&t; * unresolved symbols (since there&squot;ll be too many ;) */
r_if
c_cond
(paren
id|is_vmlinux
c_func
(paren
id|modname
)paren
)paren
(brace
r_int
r_int
id|fake_crc
op_assign
l_int|0
suffix:semicolon
id|have_vmlinux
op_assign
l_int|1
suffix:semicolon
id|add_exported_symbol
c_func
(paren
l_string|&quot;struct_module&quot;
comma
id|mod
comma
op_amp
id|fake_crc
)paren
suffix:semicolon
id|mod-&gt;skip
op_assign
l_int|1
suffix:semicolon
)brace
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
id|maybe_frob_version
c_func
(paren
id|modname
comma
id|info.modinfo
comma
id|info.modinfo_len
comma
(paren
r_void
op_star
)paren
id|info.modinfo
op_minus
(paren
r_void
op_star
)paren
id|info.hdr
)paren
suffix:semicolon
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
id|mod-&gt;unres
op_assign
id|alloc_symbol
c_func
(paren
l_string|&quot;struct_module&quot;
comma
id|mod-&gt;unres
)paren
suffix:semicolon
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
comma
r_struct
id|module
op_star
id|mod
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
l_string|&quot;MODULE_INFO(vermagic, VERMAGIC_STRING);&bslash;n&quot;
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
l_string|&quot;#undef unix&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* We have a module called &quot;unix&quot; */
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;struct module __this_module&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;__attribute__((section(&bslash;&quot;.gnu.linkonce.this_module&bslash;&quot;))) = {&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot; .name = __stringify(KBUILD_MODNAME),&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mod-&gt;has_init
)paren
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot; .init = init_module,&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mod-&gt;has_cleanup
)paren
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;#ifdef CONFIG_MODULE_UNLOAD&bslash;n&quot;
l_string|&quot; .exit = cleanup_module,&bslash;n&quot;
l_string|&quot;#endif&bslash;n&quot;
)paren
suffix:semicolon
id|buf_printf
c_func
(paren
id|b
comma
l_string|&quot;};&bslash;n&quot;
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
l_string|&quot;__attribute_used__&bslash;n&quot;
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
id|m-&gt;seen
op_assign
id|is_vmlinux
c_func
(paren
id|m-&gt;name
)paren
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
r_void
DECL|function|read_dump
id|read_dump
c_func
(paren
r_const
r_char
op_star
id|fname
)paren
(brace
r_int
r_int
id|size
comma
id|pos
op_assign
l_int|0
suffix:semicolon
r_void
op_star
id|file
op_assign
id|grab_file
c_func
(paren
id|fname
comma
op_amp
id|size
)paren
suffix:semicolon
r_char
op_star
id|line
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
multiline_comment|/* No symbol versions, silently ignore */
r_return
suffix:semicolon
r_while
c_loop
(paren
(paren
id|line
op_assign
id|get_next_line
c_func
(paren
op_amp
id|pos
comma
id|file
comma
id|size
)paren
)paren
)paren
(brace
r_char
op_star
id|symname
comma
op_star
id|modname
comma
op_star
id|d
suffix:semicolon
r_int
r_int
id|crc
suffix:semicolon
r_struct
id|module
op_star
id|mod
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|symname
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&bslash;t&squot;
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
op_star
id|symname
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|modname
op_assign
id|strchr
c_func
(paren
id|symname
comma
l_char|&squot;&bslash;t&squot;
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
op_star
id|modname
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|modname
comma
l_char|&squot;&bslash;t&squot;
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|crc
op_assign
id|strtoul
c_func
(paren
id|line
comma
op_amp
id|d
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|symname
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
op_star
id|modname
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
op_star
id|d
op_ne
l_char|&squot;&bslash;0&squot;
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mod
op_assign
id|find_module
c_func
(paren
id|modname
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|is_vmlinux
c_func
(paren
id|modname
)paren
)paren
(brace
id|have_vmlinux
op_assign
l_int|1
suffix:semicolon
)brace
id|mod
op_assign
id|new_module
c_func
(paren
id|NOFAIL
c_func
(paren
id|strdup
c_func
(paren
id|modname
)paren
)paren
)paren
suffix:semicolon
id|mod-&gt;skip
op_assign
l_int|1
suffix:semicolon
)brace
id|add_exported_symbol
c_func
(paren
id|symname
comma
id|mod
comma
op_amp
id|crc
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
id|fail
suffix:colon
id|fatal
c_func
(paren
l_string|&quot;parse error in symbol dump file&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_void
DECL|function|write_dump
id|write_dump
c_func
(paren
r_const
r_char
op_star
id|fname
)paren
(brace
r_struct
id|buffer
id|buf
op_assign
(brace
)brace
suffix:semicolon
r_struct
id|symbol
op_star
id|symbol
suffix:semicolon
r_int
id|n
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|SYMBOL_HASH_SIZE
suffix:semicolon
id|n
op_increment
)paren
(brace
id|symbol
op_assign
id|symbolhash
(braket
id|n
)braket
suffix:semicolon
r_while
c_loop
(paren
id|symbol
)paren
(brace
id|symbol
op_assign
id|symbol-&gt;next
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|SYMBOL_HASH_SIZE
suffix:semicolon
id|n
op_increment
)paren
(brace
id|symbol
op_assign
id|symbolhash
(braket
id|n
)braket
suffix:semicolon
r_while
c_loop
(paren
id|symbol
)paren
(brace
id|buf_printf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;0x%08x&bslash;t%s&bslash;t%s&bslash;n&quot;
comma
id|symbol-&gt;crc
comma
id|symbol-&gt;name
comma
id|symbol-&gt;module-&gt;name
)paren
suffix:semicolon
id|symbol
op_assign
id|symbol-&gt;next
suffix:semicolon
)brace
)brace
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
r_char
op_star
id|dump_read
op_assign
l_int|NULL
comma
op_star
id|dump_write
op_assign
l_int|NULL
suffix:semicolon
r_int
id|opt
suffix:semicolon
r_while
c_loop
(paren
(paren
id|opt
op_assign
id|getopt
c_func
(paren
id|argc
comma
id|argv
comma
l_string|&quot;i:mo:&quot;
)paren
)paren
op_ne
op_minus
l_int|1
)paren
(brace
r_switch
c_cond
(paren
id|opt
)paren
(brace
r_case
l_char|&squot;i&squot;
suffix:colon
id|dump_read
op_assign
id|optarg
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;m&squot;
suffix:colon
id|modversions
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;o&squot;
suffix:colon
id|dump_write
op_assign
id|optarg
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dump_read
)paren
id|read_dump
c_func
(paren
id|dump_read
)paren
suffix:semicolon
r_while
c_loop
(paren
id|optind
OL
id|argc
)paren
(brace
id|read_symbols
c_func
(paren
id|argv
(braket
id|optind
op_increment
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
id|mod-&gt;skip
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
comma
id|mod
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
r_if
c_cond
(paren
id|dump_write
)paren
id|write_dump
c_func
(paren
id|dump_write
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
