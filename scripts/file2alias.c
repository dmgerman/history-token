multiline_comment|/* Simple code to turn various tables in an ELF file into alias definitions.&n;   This deals with kernel datastructures where they should be&n;   dealt with: in the kernel source.&n;   (C) 2002 Rusty Russell IBM Corporation.&n;*/
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;elf.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;stdint.h&gt;
macro_line|#include &lt;endian.h&gt;
macro_line|#include &quot;elfconfig.h&quot;
multiline_comment|/* We use the ELF typedefs, since we can&squot;t rely on stdint.h being present. */
macro_line|#if KERNEL_ELFCLASS == ELFCLASS32
DECL|typedef|kernel_ulong_t
r_typedef
id|Elf32_Addr
id|kernel_ulong_t
suffix:semicolon
macro_line|#else
DECL|typedef|kernel_ulong_t
r_typedef
id|Elf64_Addr
id|kernel_ulong_t
suffix:semicolon
macro_line|#endif
DECL|typedef|__u32
r_typedef
id|Elf32_Word
id|__u32
suffix:semicolon
DECL|typedef|__u16
r_typedef
id|Elf32_Half
id|__u16
suffix:semicolon
DECL|typedef|__u8
r_typedef
r_int
r_char
id|__u8
suffix:semicolon
multiline_comment|/* Big exception to the &quot;don&squot;t include kernel headers into userspace, which&n; * even potentially has different endianness and word sizes, since &n; * we handle those differences explicitly below */
macro_line|#include &quot;../include/linux/mod_devicetable.h&quot;
macro_line|#if KERNEL_ELFCLASS == ELFCLASS32
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr Elf32_Ehdr 
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr Elf32_Shdr 
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym  Elf32_Sym
macro_line|#else
DECL|macro|Elf_Ehdr
mdefine_line|#define Elf_Ehdr Elf64_Ehdr 
DECL|macro|Elf_Shdr
mdefine_line|#define Elf_Shdr Elf64_Shdr 
DECL|macro|Elf_Sym
mdefine_line|#define Elf_Sym  Elf64_Sym
macro_line|#endif
macro_line|#if KERNEL_ELFDATA != HOST_ELFDATA
DECL|function|__endian
r_static
r_void
id|__endian
c_func
(paren
r_const
r_void
op_star
id|src
comma
r_void
op_star
id|dest
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
(paren
(paren
r_int
r_char
op_star
)paren
id|dest
)paren
(braket
id|i
)braket
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|src
)paren
(braket
id|size
op_minus
id|i
op_minus
l_int|1
)braket
suffix:semicolon
)brace
DECL|macro|TO_NATIVE
mdefine_line|#define TO_NATIVE(x)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;typeof(x) __x;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__endian(&amp;(x), &amp;(__x), sizeof(__x));&t;&t;&t;&bslash;&n;&t;__x;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#else /* endianness matches */
DECL|macro|TO_NATIVE
mdefine_line|#define TO_NATIVE(x) (x)
macro_line|#endif
DECL|macro|ADD
mdefine_line|#define ADD(str, sep, cond, field)                              &bslash;&n;do {                                                            &bslash;&n;        strcat(str, sep);                                       &bslash;&n;        if (cond)                                               &bslash;&n;                sprintf(str + strlen(str),                      &bslash;&n;                        sizeof(field) == 1 ? &quot;%02X&quot; :           &bslash;&n;                        sizeof(field) == 2 ? &quot;%04X&quot; :           &bslash;&n;                        sizeof(field) == 4 ? &quot;%08X&quot; : &quot;&quot;,       &bslash;&n;                        field);                                 &bslash;&n;        else                                                    &bslash;&n;                sprintf(str + strlen(str), &quot;*&quot;);                &bslash;&n;} while(0)
multiline_comment|/* Looks like &quot;usb:vNpNdlNdhNdcNdscNdpNicNiscNipN&quot; */
DECL|function|do_usb_entry
r_static
r_int
id|do_usb_entry
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_struct
id|usb_device_id
op_star
id|id
comma
r_char
op_star
id|alias
)paren
(brace
id|id-&gt;match_flags
op_assign
id|TO_NATIVE
c_func
(paren
id|id-&gt;match_flags
)paren
suffix:semicolon
id|id-&gt;idVendor
op_assign
id|TO_NATIVE
c_func
(paren
id|id-&gt;idVendor
)paren
suffix:semicolon
id|id-&gt;idProduct
op_assign
id|TO_NATIVE
c_func
(paren
id|id-&gt;idProduct
)paren
suffix:semicolon
id|id-&gt;bcdDevice_lo
op_assign
id|TO_NATIVE
c_func
(paren
id|id-&gt;bcdDevice_lo
)paren
suffix:semicolon
id|id-&gt;bcdDevice_hi
op_assign
id|TO_NATIVE
c_func
(paren
id|id-&gt;bcdDevice_hi
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|alias
comma
l_string|&quot;usb:&quot;
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;v&quot;
comma
id|id-&gt;match_flags
op_amp
id|USB_DEVICE_ID_MATCH_VENDOR
comma
id|id-&gt;idVendor
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;p&quot;
comma
id|id-&gt;match_flags
op_amp
id|USB_DEVICE_ID_MATCH_PRODUCT
comma
id|id-&gt;idProduct
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;dl&quot;
comma
id|id-&gt;match_flags
op_amp
id|USB_DEVICE_ID_MATCH_DEV_LO
comma
id|id-&gt;bcdDevice_lo
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;dh&quot;
comma
id|id-&gt;match_flags
op_amp
id|USB_DEVICE_ID_MATCH_DEV_HI
comma
id|id-&gt;bcdDevice_hi
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;dc&quot;
comma
id|id-&gt;match_flags
op_amp
id|USB_DEVICE_ID_MATCH_DEV_CLASS
comma
id|id-&gt;bDeviceClass
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;dsc&quot;
comma
id|id-&gt;match_flags
op_amp
id|USB_DEVICE_ID_MATCH_DEV_SUBCLASS
comma
id|id-&gt;bDeviceSubClass
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;dp&quot;
comma
id|id-&gt;match_flags
op_amp
id|USB_DEVICE_ID_MATCH_DEV_PROTOCOL
comma
id|id-&gt;bDeviceProtocol
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;ic&quot;
comma
id|id-&gt;match_flags
op_amp
id|USB_DEVICE_ID_MATCH_INT_CLASS
comma
id|id-&gt;bInterfaceClass
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;isc&quot;
comma
id|id-&gt;match_flags
op_amp
id|USB_DEVICE_ID_MATCH_INT_SUBCLASS
comma
id|id-&gt;bInterfaceSubClass
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;ip&quot;
comma
id|id-&gt;match_flags
op_amp
id|USB_DEVICE_ID_MATCH_INT_PROTOCOL
comma
id|id-&gt;bInterfaceProtocol
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Looks like: pci:vNdNsvNsdNcN. */
DECL|function|do_pci_entry
r_static
r_int
id|do_pci_entry
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_struct
id|pci_device_id
op_star
id|id
comma
r_char
op_star
id|alias
)paren
(brace
id|id-&gt;vendor
op_assign
id|TO_NATIVE
c_func
(paren
id|id-&gt;vendor
)paren
suffix:semicolon
id|id-&gt;device
op_assign
id|TO_NATIVE
c_func
(paren
id|id-&gt;device
)paren
suffix:semicolon
id|id-&gt;subvendor
op_assign
id|TO_NATIVE
c_func
(paren
id|id-&gt;subvendor
)paren
suffix:semicolon
id|id-&gt;subdevice
op_assign
id|TO_NATIVE
c_func
(paren
id|id-&gt;subdevice
)paren
suffix:semicolon
id|id
op_member_access_from_pointer
r_class
op_assign
id|TO_NATIVE
c_func
(paren
id|id
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
id|id-&gt;class_mask
op_assign
id|TO_NATIVE
c_func
(paren
id|id-&gt;class_mask
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|alias
comma
l_string|&quot;pci:&quot;
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;v&quot;
comma
id|id-&gt;vendor
op_ne
id|PCI_ANY_ID
comma
id|id-&gt;vendor
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;d&quot;
comma
id|id-&gt;device
op_ne
id|PCI_ANY_ID
comma
id|id-&gt;device
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;sv&quot;
comma
id|id-&gt;subvendor
op_ne
id|PCI_ANY_ID
comma
id|id-&gt;subvendor
)paren
suffix:semicolon
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;sd&quot;
comma
id|id-&gt;subdevice
op_ne
id|PCI_ANY_ID
comma
id|id-&gt;subdevice
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;class_mask
op_ne
l_int|0
op_logical_and
id|id-&gt;class_mask
op_ne
op_complement
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;file2alias: Can&squot;t handle class_mask in %s:%04X&bslash;n&quot;
comma
id|filename
comma
id|id-&gt;class_mask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ADD
c_func
(paren
id|alias
comma
l_string|&quot;c&quot;
comma
id|id-&gt;class_mask
op_eq
op_complement
l_int|0
comma
id|id
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Ignore any prefix, eg. v850 prepends _ */
DECL|function|sym_is
r_static
r_inline
r_int
id|sym_is
c_func
(paren
r_const
r_char
op_star
id|symbol
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_const
r_char
op_star
id|match
suffix:semicolon
id|match
op_assign
id|strstr
c_func
(paren
id|symbol
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|match
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|match
(braket
id|strlen
c_func
(paren
id|symbol
)paren
)braket
op_eq
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
multiline_comment|/* Returns 1 if we output anything. */
DECL|function|do_table
r_static
r_int
id|do_table
c_func
(paren
r_void
op_star
id|symval
comma
r_int
r_int
id|size
comma
r_int
r_int
id|id_size
comma
r_void
op_star
id|function
comma
r_const
r_char
op_star
id|filename
comma
r_int
op_star
id|first
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_char
id|alias
(braket
l_int|500
)braket
suffix:semicolon
r_int
(paren
op_star
id|do_entry
)paren
(paren
r_const
r_char
op_star
comma
r_void
op_star
id|entry
comma
r_char
op_star
id|alias
)paren
op_assign
id|function
suffix:semicolon
r_int
id|wrote
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|size
op_mod
id|id_size
op_logical_or
id|size
OL
id|id_size
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;WARNING: %s ids %lu bad size (each on %lu)&bslash;n&quot;
comma
id|filename
comma
id|size
comma
id|id_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Leave last one: it&squot;s the terminator. */
id|size
op_sub_assign
id|id_size
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_add_assign
id|id_size
)paren
(brace
r_if
c_cond
(paren
id|do_entry
c_func
(paren
id|filename
comma
id|symval
op_plus
id|i
comma
id|alias
)paren
)paren
(brace
multiline_comment|/* Always end in a wildcard, for future extension */
r_if
c_cond
(paren
id|alias
(braket
id|strlen
c_func
(paren
id|alias
)paren
op_minus
l_int|1
)braket
op_ne
l_char|&squot;*&squot;
)paren
id|strcat
c_func
(paren
id|alias
comma
l_string|&quot;*&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|first
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;#include &lt;linux/module.h&gt;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|first
op_assign
l_int|0
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;MODULE_ALIAS(&bslash;&quot;%s&bslash;&quot;);&bslash;n&quot;
comma
id|alias
)paren
suffix:semicolon
id|wrote
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|wrote
suffix:semicolon
)brace
multiline_comment|/* This contains the cookie-cutter code for ELF handling (32 v 64). */
DECL|function|analyze_file
r_static
r_void
id|analyze_file
c_func
(paren
id|Elf_Ehdr
op_star
id|hdr
comma
r_int
r_int
id|size
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
comma
id|num_syms
op_assign
l_int|0
suffix:semicolon
id|Elf_Shdr
op_star
id|sechdrs
suffix:semicolon
id|Elf_Sym
op_star
id|syms
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|secstrings
comma
op_star
id|strtab
op_assign
l_int|NULL
suffix:semicolon
r_int
id|first
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
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
id|sechdrs
op_assign
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|TO_NATIVE
c_func
(paren
id|hdr-&gt;e_shoff
)paren
suffix:semicolon
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
id|size
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
op_eq
id|SHT_SYMTAB
)paren
(brace
id|syms
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
id|num_syms
op_assign
id|sechdrs
(braket
id|i
)braket
dot
id|sh_size
op_div
r_sizeof
(paren
id|syms
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_type
op_eq
id|SHT_STRTAB
)paren
id|strtab
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
)brace
r_if
c_cond
(paren
op_logical_neg
id|strtab
op_logical_or
op_logical_neg
id|syms
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;table2alias: %s no symtab?&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
m_abort
(paren
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_syms
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|symname
suffix:semicolon
r_void
op_star
id|symval
suffix:semicolon
id|syms
(braket
id|i
)braket
dot
id|st_shndx
op_assign
id|TO_NATIVE
c_func
(paren
id|syms
(braket
id|i
)braket
dot
id|st_shndx
)paren
suffix:semicolon
id|syms
(braket
id|i
)braket
dot
id|st_name
op_assign
id|TO_NATIVE
c_func
(paren
id|syms
(braket
id|i
)braket
dot
id|st_name
)paren
suffix:semicolon
id|syms
(braket
id|i
)braket
dot
id|st_value
op_assign
id|TO_NATIVE
c_func
(paren
id|syms
(braket
id|i
)braket
dot
id|st_value
)paren
suffix:semicolon
id|syms
(braket
id|i
)braket
dot
id|st_size
op_assign
id|TO_NATIVE
c_func
(paren
id|syms
(braket
id|i
)braket
dot
id|st_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|syms
(braket
id|i
)braket
dot
id|st_shndx
op_logical_or
id|syms
(braket
id|i
)braket
dot
id|st_shndx
op_ge
id|hdr-&gt;e_shnum
)paren
r_continue
suffix:semicolon
id|symname
op_assign
id|strtab
op_plus
id|syms
(braket
id|i
)braket
dot
id|st_name
suffix:semicolon
id|symval
op_assign
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|sechdrs
(braket
id|syms
(braket
id|i
)braket
dot
id|st_shndx
)braket
dot
id|sh_offset
op_plus
id|syms
(braket
id|i
)braket
dot
id|st_value
suffix:semicolon
r_if
c_cond
(paren
id|sym_is
c_func
(paren
id|symname
comma
l_string|&quot;__mod_pci_device_table&quot;
)paren
)paren
id|do_table
c_func
(paren
id|symval
comma
id|syms
(braket
id|i
)braket
dot
id|st_size
comma
r_sizeof
(paren
r_struct
id|pci_device_id
)paren
comma
id|do_pci_entry
comma
id|filename
comma
op_amp
id|first
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sym_is
c_func
(paren
id|symname
comma
l_string|&quot;__mod_usb_device_table&quot;
)paren
)paren
id|do_table
c_func
(paren
id|symval
comma
id|syms
(braket
id|i
)braket
dot
id|st_size
comma
r_sizeof
(paren
r_struct
id|usb_device_id
)paren
comma
id|do_usb_entry
comma
id|filename
comma
op_amp
id|first
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
l_string|&quot;table2alias: %s is truncated.&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
m_abort
(paren
)paren
suffix:semicolon
)brace
DECL|function|grab_file
r_static
r_void
op_star
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
r_return
l_int|NULL
suffix:semicolon
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
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|NULL
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
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|NULL
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
multiline_comment|/* Look through files for __mod_*_device_table: emit alias definitions&n;   for compiling in. */
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
r_void
op_star
id|file
suffix:semicolon
r_int
r_int
id|size
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
id|file
op_assign
id|grab_file
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;file2alias: opening %s: %s&bslash;n&quot;
comma
id|argv
(braket
l_int|1
)braket
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
m_abort
(paren
)paren
suffix:semicolon
)brace
id|analyze_file
c_func
(paren
id|file
comma
id|size
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|munmap
c_func
(paren
id|file
comma
id|size
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
