macro_line|#ifndef _LINUX_MODULELOADER_H
DECL|macro|_LINUX_MODULELOADER_H
mdefine_line|#define _LINUX_MODULELOADER_H
multiline_comment|/* The stuff needed for archs to support modules. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
multiline_comment|/* Helper function for arch-specific module loaders */
r_int
r_int
id|find_symbol_internal
c_func
(paren
id|Elf_Shdr
op_star
id|sechdrs
comma
r_int
r_int
id|symindex
comma
r_const
r_char
op_star
id|strtab
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|module
op_star
id|mod
comma
r_struct
id|kernel_symbol_group
op_star
op_star
id|group
)paren
suffix:semicolon
multiline_comment|/* These must be implemented by the specific architecture */
multiline_comment|/* Adjust arch-specific sections.  Return 0 on success.  */
r_int
id|module_frob_arch_sections
c_func
(paren
id|Elf_Ehdr
op_star
id|hdr
comma
id|Elf_Shdr
op_star
id|sechdrs
comma
r_char
op_star
id|secstrings
comma
r_struct
id|module
op_star
id|mod
)paren
suffix:semicolon
multiline_comment|/* Allocator used for allocating struct module, core sections and init&n;   sections.  Returns NULL on failure. */
r_void
op_star
id|module_alloc
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Free memory returned from module_alloc. */
r_void
id|module_free
c_func
(paren
r_struct
id|module
op_star
id|mod
comma
r_void
op_star
id|module_region
)paren
suffix:semicolon
multiline_comment|/* Apply the given relocation to the (simplified) ELF.  Return -error&n;   or 0. */
r_int
id|apply_relocate
c_func
(paren
id|Elf_Shdr
op_star
id|sechdrs
comma
r_const
r_char
op_star
id|strtab
comma
r_int
r_int
id|symindex
comma
r_int
r_int
id|relsec
comma
r_struct
id|module
op_star
id|mod
)paren
suffix:semicolon
multiline_comment|/* Apply the given add relocation to the (simplified) ELF.  Return&n;   -error or 0 */
r_int
id|apply_relocate_add
c_func
(paren
id|Elf_Shdr
op_star
id|sechdrs
comma
r_const
r_char
op_star
id|strtab
comma
r_int
r_int
id|symindex
comma
r_int
r_int
id|relsec
comma
r_struct
id|module
op_star
id|mod
)paren
suffix:semicolon
multiline_comment|/* Any final processing of module before access.  Return -error or 0. */
r_int
id|module_finalize
c_func
(paren
r_const
id|Elf_Ehdr
op_star
id|hdr
comma
r_const
id|Elf_Shdr
op_star
id|sechdrs
comma
r_struct
id|module
op_star
id|mod
)paren
suffix:semicolon
macro_line|#endif
eof
