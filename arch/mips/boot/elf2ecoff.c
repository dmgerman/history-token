multiline_comment|/*&n; * Copyright (c) 1995&n; *&t;Ted Lemon (hereinafter referred to as the author)&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; * 3. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE&n; * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
multiline_comment|/* elf2ecoff.c&n;&n;   This program converts an elf executable to an ECOFF executable.&n;   No symbol table is retained.   This is useful primarily in building&n;   net-bootable kernels for machines (e.g., DECstation and Alpha) which&n;   only support the ECOFF object file format. */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;elf.h&gt;
macro_line|#include &lt;limits.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &quot;ecoff.h&quot;
multiline_comment|/*&n; * Some extra ELF definitions&n; */
DECL|macro|PT_MIPS_REGINFO
mdefine_line|#define PT_MIPS_REGINFO 0x70000000&t;/* Register usage information */
multiline_comment|/* -------------------------------------------------------------------- */
DECL|struct|sect
r_struct
id|sect
(brace
DECL|member|vaddr
r_int
r_int
id|vaddr
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|symTypeTable
r_int
op_star
id|symTypeTable
suffix:semicolon
DECL|variable|must_convert_endian
r_int
id|must_convert_endian
op_assign
l_int|0
suffix:semicolon
DECL|variable|format_bigendian
r_int
id|format_bigendian
op_assign
l_int|0
suffix:semicolon
DECL|function|copy
r_static
r_void
id|copy
c_func
(paren
r_int
id|out
comma
r_int
id|in
comma
id|off_t
id|offset
comma
id|off_t
id|size
)paren
(brace
r_char
id|ibuf
(braket
l_int|4096
)braket
suffix:semicolon
r_int
id|remaining
comma
id|cur
comma
id|count
suffix:semicolon
multiline_comment|/* Go to the start of the ELF symbol table... */
r_if
c_cond
(paren
id|lseek
c_func
(paren
id|in
comma
id|offset
comma
id|SEEK_SET
)paren
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;copy: lseek&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|remaining
op_assign
id|size
suffix:semicolon
r_while
c_loop
(paren
id|remaining
)paren
(brace
id|cur
op_assign
id|remaining
suffix:semicolon
r_if
c_cond
(paren
id|cur
OG
r_sizeof
id|ibuf
)paren
id|cur
op_assign
r_sizeof
id|ibuf
suffix:semicolon
id|remaining
op_sub_assign
id|cur
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
op_assign
id|read
c_func
(paren
id|in
comma
id|ibuf
comma
id|cur
)paren
)paren
op_ne
id|cur
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;copy: read: %s&bslash;n&quot;
comma
id|count
ques
c_cond
id|strerror
c_func
(paren
id|errno
)paren
suffix:colon
l_string|&quot;premature end of file&quot;
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
(paren
id|count
op_assign
id|write
c_func
(paren
id|out
comma
id|ibuf
comma
id|cur
)paren
)paren
op_ne
id|cur
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;copy: write&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Combine two segments, which must be contiguous.   If pad is true, it&squot;s&n; * okay for there to be padding between.&n; */
DECL|function|combine
r_static
r_void
id|combine
c_func
(paren
r_struct
id|sect
op_star
id|base
comma
r_struct
id|sect
op_star
r_new
comma
r_int
id|pad
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|base-&gt;len
)paren
op_star
id|base
op_assign
op_star
r_new
suffix:semicolon
r_else
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|len
)paren
(brace
r_if
c_cond
(paren
id|base-&gt;vaddr
op_plus
id|base-&gt;len
op_ne
r_new
op_member_access_from_pointer
id|vaddr
)paren
(brace
r_if
c_cond
(paren
id|pad
)paren
id|base-&gt;len
op_assign
r_new
op_member_access_from_pointer
id|vaddr
op_minus
id|base-&gt;vaddr
suffix:semicolon
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Non-contiguous data can&squot;t be converted.&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|base-&gt;len
op_add_assign
r_new
op_member_access_from_pointer
id|len
suffix:semicolon
)brace
)brace
DECL|function|phcmp
r_static
r_int
id|phcmp
c_func
(paren
r_const
r_void
op_star
id|v1
comma
r_const
r_void
op_star
id|v2
)paren
(brace
r_const
id|Elf32_Phdr
op_star
id|h1
op_assign
id|v1
suffix:semicolon
r_const
id|Elf32_Phdr
op_star
id|h2
op_assign
id|v2
suffix:semicolon
r_if
c_cond
(paren
id|h1-&gt;p_vaddr
OG
id|h2-&gt;p_vaddr
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|h1-&gt;p_vaddr
OL
id|h2-&gt;p_vaddr
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saveRead
r_static
r_char
op_star
id|saveRead
c_func
(paren
r_int
id|file
comma
id|off_t
id|offset
comma
id|off_t
id|len
comma
r_char
op_star
id|name
)paren
(brace
r_char
op_star
id|tmp
suffix:semicolon
r_int
id|count
suffix:semicolon
id|off_t
id|off
suffix:semicolon
r_if
c_cond
(paren
(paren
id|off
op_assign
id|lseek
c_func
(paren
id|file
comma
id|offset
comma
id|SEEK_SET
)paren
)paren
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: fseek: %s&bslash;n&quot;
comma
id|name
comma
id|strerror
c_func
(paren
id|errno
)paren
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
op_logical_neg
(paren
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|malloc
c_func
(paren
id|len
)paren
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: Can&squot;t allocate %ld bytes.&bslash;n&quot;
comma
id|name
comma
id|len
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|count
op_assign
id|read
c_func
(paren
id|file
comma
id|tmp
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
id|len
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: read: %s.&bslash;n&quot;
comma
id|name
comma
id|count
ques
c_cond
id|strerror
c_func
(paren
id|errno
)paren
suffix:colon
l_string|&quot;End of file reached&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
id|tmp
suffix:semicolon
)brace
DECL|macro|swab16
mdefine_line|#define swab16(x) &bslash;&n;&t;((unsigned short)( &bslash;&n;&t;&t;(((unsigned short)(x) &amp; (unsigned short)0x00ffU) &lt;&lt; 8) | &bslash;&n;&t;&t;(((unsigned short)(x) &amp; (unsigned short)0xff00U) &gt;&gt; 8) ))
DECL|macro|swab32
mdefine_line|#define swab32(x) &bslash;&n;&t;((unsigned int)( &bslash;&n;&t;&t;(((unsigned int)(x) &amp; (unsigned int)0x000000ffUL) &lt;&lt; 24) | &bslash;&n;&t;&t;(((unsigned int)(x) &amp; (unsigned int)0x0000ff00UL) &lt;&lt;  8) | &bslash;&n;&t;&t;(((unsigned int)(x) &amp; (unsigned int)0x00ff0000UL) &gt;&gt;  8) | &bslash;&n;&t;&t;(((unsigned int)(x) &amp; (unsigned int)0xff000000UL) &gt;&gt; 24) ))
DECL|function|convert_elf_hdr
r_static
r_void
id|convert_elf_hdr
c_func
(paren
id|Elf32_Ehdr
op_star
id|e
)paren
(brace
id|e-&gt;e_type
op_assign
id|swab16
c_func
(paren
id|e-&gt;e_type
)paren
suffix:semicolon
id|e-&gt;e_machine
op_assign
id|swab16
c_func
(paren
id|e-&gt;e_machine
)paren
suffix:semicolon
id|e-&gt;e_version
op_assign
id|swab32
c_func
(paren
id|e-&gt;e_version
)paren
suffix:semicolon
id|e-&gt;e_entry
op_assign
id|swab32
c_func
(paren
id|e-&gt;e_entry
)paren
suffix:semicolon
id|e-&gt;e_phoff
op_assign
id|swab32
c_func
(paren
id|e-&gt;e_phoff
)paren
suffix:semicolon
id|e-&gt;e_shoff
op_assign
id|swab32
c_func
(paren
id|e-&gt;e_shoff
)paren
suffix:semicolon
id|e-&gt;e_flags
op_assign
id|swab32
c_func
(paren
id|e-&gt;e_flags
)paren
suffix:semicolon
id|e-&gt;e_ehsize
op_assign
id|swab16
c_func
(paren
id|e-&gt;e_ehsize
)paren
suffix:semicolon
id|e-&gt;e_phentsize
op_assign
id|swab16
c_func
(paren
id|e-&gt;e_phentsize
)paren
suffix:semicolon
id|e-&gt;e_phnum
op_assign
id|swab16
c_func
(paren
id|e-&gt;e_phnum
)paren
suffix:semicolon
id|e-&gt;e_shentsize
op_assign
id|swab16
c_func
(paren
id|e-&gt;e_shentsize
)paren
suffix:semicolon
id|e-&gt;e_shnum
op_assign
id|swab16
c_func
(paren
id|e-&gt;e_shnum
)paren
suffix:semicolon
id|e-&gt;e_shstrndx
op_assign
id|swab16
c_func
(paren
id|e-&gt;e_shstrndx
)paren
suffix:semicolon
)brace
DECL|function|convert_elf_phdrs
r_static
r_void
id|convert_elf_phdrs
c_func
(paren
id|Elf32_Phdr
op_star
id|p
comma
r_int
id|num
)paren
(brace
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
id|num
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
id|p-&gt;p_type
op_assign
id|swab32
c_func
(paren
id|p-&gt;p_type
)paren
suffix:semicolon
id|p-&gt;p_offset
op_assign
id|swab32
c_func
(paren
id|p-&gt;p_offset
)paren
suffix:semicolon
id|p-&gt;p_vaddr
op_assign
id|swab32
c_func
(paren
id|p-&gt;p_vaddr
)paren
suffix:semicolon
id|p-&gt;p_paddr
op_assign
id|swab32
c_func
(paren
id|p-&gt;p_paddr
)paren
suffix:semicolon
id|p-&gt;p_filesz
op_assign
id|swab32
c_func
(paren
id|p-&gt;p_filesz
)paren
suffix:semicolon
id|p-&gt;p_memsz
op_assign
id|swab32
c_func
(paren
id|p-&gt;p_memsz
)paren
suffix:semicolon
id|p-&gt;p_flags
op_assign
id|swab32
c_func
(paren
id|p-&gt;p_flags
)paren
suffix:semicolon
id|p-&gt;p_align
op_assign
id|swab32
c_func
(paren
id|p-&gt;p_align
)paren
suffix:semicolon
)brace
)brace
DECL|function|convert_elf_shdrs
r_static
r_void
id|convert_elf_shdrs
c_func
(paren
id|Elf32_Shdr
op_star
id|s
comma
r_int
id|num
)paren
(brace
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
id|num
suffix:semicolon
id|i
op_increment
comma
id|s
op_increment
)paren
(brace
id|s-&gt;sh_name
op_assign
id|swab32
c_func
(paren
id|s-&gt;sh_name
)paren
suffix:semicolon
id|s-&gt;sh_type
op_assign
id|swab32
c_func
(paren
id|s-&gt;sh_type
)paren
suffix:semicolon
id|s-&gt;sh_flags
op_assign
id|swab32
c_func
(paren
id|s-&gt;sh_flags
)paren
suffix:semicolon
id|s-&gt;sh_addr
op_assign
id|swab32
c_func
(paren
id|s-&gt;sh_addr
)paren
suffix:semicolon
id|s-&gt;sh_offset
op_assign
id|swab32
c_func
(paren
id|s-&gt;sh_offset
)paren
suffix:semicolon
id|s-&gt;sh_size
op_assign
id|swab32
c_func
(paren
id|s-&gt;sh_size
)paren
suffix:semicolon
id|s-&gt;sh_link
op_assign
id|swab32
c_func
(paren
id|s-&gt;sh_link
)paren
suffix:semicolon
id|s-&gt;sh_info
op_assign
id|swab32
c_func
(paren
id|s-&gt;sh_info
)paren
suffix:semicolon
id|s-&gt;sh_addralign
op_assign
id|swab32
c_func
(paren
id|s-&gt;sh_addralign
)paren
suffix:semicolon
id|s-&gt;sh_entsize
op_assign
id|swab32
c_func
(paren
id|s-&gt;sh_entsize
)paren
suffix:semicolon
)brace
)brace
DECL|function|convert_ecoff_filehdr
r_static
r_void
id|convert_ecoff_filehdr
c_func
(paren
r_struct
id|filehdr
op_star
id|f
)paren
(brace
id|f-&gt;f_magic
op_assign
id|swab16
c_func
(paren
id|f-&gt;f_magic
)paren
suffix:semicolon
id|f-&gt;f_nscns
op_assign
id|swab16
c_func
(paren
id|f-&gt;f_nscns
)paren
suffix:semicolon
id|f-&gt;f_timdat
op_assign
id|swab32
c_func
(paren
id|f-&gt;f_timdat
)paren
suffix:semicolon
id|f-&gt;f_symptr
op_assign
id|swab32
c_func
(paren
id|f-&gt;f_symptr
)paren
suffix:semicolon
id|f-&gt;f_nsyms
op_assign
id|swab32
c_func
(paren
id|f-&gt;f_nsyms
)paren
suffix:semicolon
id|f-&gt;f_opthdr
op_assign
id|swab16
c_func
(paren
id|f-&gt;f_opthdr
)paren
suffix:semicolon
id|f-&gt;f_flags
op_assign
id|swab16
c_func
(paren
id|f-&gt;f_flags
)paren
suffix:semicolon
)brace
DECL|function|convert_ecoff_aouthdr
r_static
r_void
id|convert_ecoff_aouthdr
c_func
(paren
r_struct
id|aouthdr
op_star
id|a
)paren
(brace
id|a-&gt;magic
op_assign
id|swab16
c_func
(paren
id|a-&gt;magic
)paren
suffix:semicolon
id|a-&gt;vstamp
op_assign
id|swab16
c_func
(paren
id|a-&gt;vstamp
)paren
suffix:semicolon
id|a-&gt;tsize
op_assign
id|swab32
c_func
(paren
id|a-&gt;tsize
)paren
suffix:semicolon
id|a-&gt;dsize
op_assign
id|swab32
c_func
(paren
id|a-&gt;dsize
)paren
suffix:semicolon
id|a-&gt;bsize
op_assign
id|swab32
c_func
(paren
id|a-&gt;bsize
)paren
suffix:semicolon
id|a-&gt;entry
op_assign
id|swab32
c_func
(paren
id|a-&gt;entry
)paren
suffix:semicolon
id|a-&gt;text_start
op_assign
id|swab32
c_func
(paren
id|a-&gt;text_start
)paren
suffix:semicolon
id|a-&gt;data_start
op_assign
id|swab32
c_func
(paren
id|a-&gt;data_start
)paren
suffix:semicolon
id|a-&gt;bss_start
op_assign
id|swab32
c_func
(paren
id|a-&gt;bss_start
)paren
suffix:semicolon
id|a-&gt;gprmask
op_assign
id|swab32
c_func
(paren
id|a-&gt;gprmask
)paren
suffix:semicolon
id|a-&gt;cprmask
(braket
l_int|0
)braket
op_assign
id|swab32
c_func
(paren
id|a-&gt;cprmask
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|a-&gt;cprmask
(braket
l_int|1
)braket
op_assign
id|swab32
c_func
(paren
id|a-&gt;cprmask
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|a-&gt;cprmask
(braket
l_int|2
)braket
op_assign
id|swab32
c_func
(paren
id|a-&gt;cprmask
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|a-&gt;cprmask
(braket
l_int|3
)braket
op_assign
id|swab32
c_func
(paren
id|a-&gt;cprmask
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|a-&gt;gp_value
op_assign
id|swab32
c_func
(paren
id|a-&gt;gp_value
)paren
suffix:semicolon
)brace
DECL|function|convert_ecoff_esecs
r_static
r_void
id|convert_ecoff_esecs
c_func
(paren
r_struct
id|scnhdr
op_star
id|s
comma
r_int
id|num
)paren
(brace
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
id|num
suffix:semicolon
id|i
op_increment
comma
id|s
op_increment
)paren
(brace
id|s-&gt;s_paddr
op_assign
id|swab32
c_func
(paren
id|s-&gt;s_paddr
)paren
suffix:semicolon
id|s-&gt;s_vaddr
op_assign
id|swab32
c_func
(paren
id|s-&gt;s_vaddr
)paren
suffix:semicolon
id|s-&gt;s_size
op_assign
id|swab32
c_func
(paren
id|s-&gt;s_size
)paren
suffix:semicolon
id|s-&gt;s_scnptr
op_assign
id|swab32
c_func
(paren
id|s-&gt;s_scnptr
)paren
suffix:semicolon
id|s-&gt;s_relptr
op_assign
id|swab32
c_func
(paren
id|s-&gt;s_relptr
)paren
suffix:semicolon
id|s-&gt;s_lnnoptr
op_assign
id|swab32
c_func
(paren
id|s-&gt;s_lnnoptr
)paren
suffix:semicolon
id|s-&gt;s_nreloc
op_assign
id|swab16
c_func
(paren
id|s-&gt;s_nreloc
)paren
suffix:semicolon
id|s-&gt;s_nlnno
op_assign
id|swab16
c_func
(paren
id|s-&gt;s_nlnno
)paren
suffix:semicolon
id|s-&gt;s_flags
op_assign
id|swab32
c_func
(paren
id|s-&gt;s_flags
)paren
suffix:semicolon
)brace
)brace
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
id|Elf32_Ehdr
id|ex
suffix:semicolon
id|Elf32_Phdr
op_star
id|ph
suffix:semicolon
id|Elf32_Shdr
op_star
id|sh
suffix:semicolon
r_char
op_star
id|shstrtab
suffix:semicolon
r_int
id|i
comma
id|pad
suffix:semicolon
r_struct
id|sect
id|text
comma
id|data
comma
id|bss
suffix:semicolon
r_struct
id|filehdr
id|efh
suffix:semicolon
r_struct
id|aouthdr
id|eah
suffix:semicolon
r_struct
id|scnhdr
id|esecs
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|infile
comma
id|outfile
suffix:semicolon
r_int
r_int
id|cur_vma
op_assign
id|ULONG_MAX
suffix:semicolon
r_int
id|addflag
op_assign
l_int|0
suffix:semicolon
r_int
id|nosecs
suffix:semicolon
id|text.len
op_assign
id|data.len
op_assign
id|bss.len
op_assign
l_int|0
suffix:semicolon
id|text.vaddr
op_assign
id|data.vaddr
op_assign
id|bss.vaddr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Check args... */
r_if
c_cond
(paren
id|argc
template_param
l_int|4
)paren
(brace
id|usage
suffix:colon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;usage: elf2ecoff &lt;elf executable&gt; &lt;ecoff executable&gt; [-a]&bslash;n&quot;
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
id|argc
op_eq
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|argv
(braket
l_int|3
)braket
comma
l_string|&quot;-a&quot;
)paren
)paren
r_goto
id|usage
suffix:semicolon
id|addflag
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Try the input file... */
r_if
c_cond
(paren
(paren
id|infile
op_assign
id|open
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|O_RDONLY
)paren
)paren
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Can&squot;t open %s for read: %s&bslash;n&quot;
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
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Read the header, which is at the beginning of the file... */
id|i
op_assign
id|read
c_func
(paren
id|infile
comma
op_amp
id|ex
comma
r_sizeof
id|ex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
r_sizeof
id|ex
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;ex: %s: %s.&bslash;n&quot;
comma
id|argv
(braket
l_int|1
)braket
comma
id|i
ques
c_cond
id|strerror
c_func
(paren
id|errno
)paren
suffix:colon
l_string|&quot;End of file reached&quot;
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
id|ex.e_ident
(braket
id|EI_DATA
)braket
op_eq
id|ELFDATA2MSB
)paren
id|format_bigendian
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
l_int|0xaa55
)paren
op_eq
l_int|0xaa55
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|format_bigendian
)paren
id|must_convert_endian
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|format_bigendian
)paren
id|must_convert_endian
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|must_convert_endian
)paren
id|convert_elf_hdr
c_func
(paren
op_amp
id|ex
)paren
suffix:semicolon
multiline_comment|/* Read the program headers... */
id|ph
op_assign
(paren
id|Elf32_Phdr
op_star
)paren
id|saveRead
c_func
(paren
id|infile
comma
id|ex.e_phoff
comma
id|ex.e_phnum
op_star
r_sizeof
(paren
id|Elf32_Phdr
)paren
comma
l_string|&quot;ph&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|must_convert_endian
)paren
id|convert_elf_phdrs
c_func
(paren
id|ph
comma
id|ex.e_phnum
)paren
suffix:semicolon
multiline_comment|/* Read the section headers... */
id|sh
op_assign
(paren
id|Elf32_Shdr
op_star
)paren
id|saveRead
c_func
(paren
id|infile
comma
id|ex.e_shoff
comma
id|ex.e_shnum
op_star
r_sizeof
(paren
id|Elf32_Shdr
)paren
comma
l_string|&quot;sh&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|must_convert_endian
)paren
id|convert_elf_shdrs
c_func
(paren
id|sh
comma
id|ex.e_shnum
)paren
suffix:semicolon
multiline_comment|/* Read in the section string table. */
id|shstrtab
op_assign
id|saveRead
c_func
(paren
id|infile
comma
id|sh
(braket
id|ex.e_shstrndx
)braket
dot
id|sh_offset
comma
id|sh
(braket
id|ex.e_shstrndx
)braket
dot
id|sh_size
comma
l_string|&quot;shstrtab&quot;
)paren
suffix:semicolon
multiline_comment|/* Figure out if we can cram the program header into an ECOFF&n;&t;   header...  Basically, we can&squot;t handle anything but loadable&n;&t;   segments, but we can ignore some kinds of segments.  We can&squot;t&n;&t;   handle holes in the address space.  Segments may be out of order,&n;&t;   so we sort them first. */
id|qsort
c_func
(paren
id|ph
comma
id|ex.e_phnum
comma
r_sizeof
(paren
id|Elf32_Phdr
)paren
comma
id|phcmp
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
id|ex.e_phnum
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Section types we can ignore... */
r_if
c_cond
(paren
id|ph
(braket
id|i
)braket
dot
id|p_type
op_eq
id|PT_NULL
op_logical_or
id|ph
(braket
id|i
)braket
dot
id|p_type
op_eq
id|PT_NOTE
op_logical_or
id|ph
(braket
id|i
)braket
dot
id|p_type
op_eq
id|PT_PHDR
op_logical_or
id|ph
(braket
id|i
)braket
dot
id|p_type
op_eq
id|PT_MIPS_REGINFO
)paren
r_continue
suffix:semicolon
multiline_comment|/* Section types we can&squot;t handle... */
r_else
r_if
c_cond
(paren
id|ph
(braket
id|i
)braket
dot
id|p_type
op_ne
id|PT_LOAD
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Program header %d type %d can&squot;t be converted.&bslash;n&quot;
comma
id|ex.e_phnum
comma
id|ph
(braket
id|i
)braket
dot
id|p_type
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Writable (data) segment? */
r_if
c_cond
(paren
id|ph
(braket
id|i
)braket
dot
id|p_flags
op_amp
id|PF_W
)paren
(brace
r_struct
id|sect
id|ndata
comma
id|nbss
suffix:semicolon
id|ndata.vaddr
op_assign
id|ph
(braket
id|i
)braket
dot
id|p_vaddr
suffix:semicolon
id|ndata.len
op_assign
id|ph
(braket
id|i
)braket
dot
id|p_filesz
suffix:semicolon
id|nbss.vaddr
op_assign
id|ph
(braket
id|i
)braket
dot
id|p_vaddr
op_plus
id|ph
(braket
id|i
)braket
dot
id|p_filesz
suffix:semicolon
id|nbss.len
op_assign
id|ph
(braket
id|i
)braket
dot
id|p_memsz
op_minus
id|ph
(braket
id|i
)braket
dot
id|p_filesz
suffix:semicolon
id|combine
c_func
(paren
op_amp
id|data
comma
op_amp
id|ndata
comma
l_int|0
)paren
suffix:semicolon
id|combine
c_func
(paren
op_amp
id|bss
comma
op_amp
id|nbss
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|sect
id|ntxt
suffix:semicolon
id|ntxt.vaddr
op_assign
id|ph
(braket
id|i
)braket
dot
id|p_vaddr
suffix:semicolon
id|ntxt.len
op_assign
id|ph
(braket
id|i
)braket
dot
id|p_filesz
suffix:semicolon
id|combine
c_func
(paren
op_amp
id|text
comma
op_amp
id|ntxt
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Remember the lowest segment start address. */
r_if
c_cond
(paren
id|ph
(braket
id|i
)braket
dot
id|p_vaddr
OL
id|cur_vma
)paren
id|cur_vma
op_assign
id|ph
(braket
id|i
)braket
dot
id|p_vaddr
suffix:semicolon
)brace
multiline_comment|/* Sections must be in order to be converted... */
r_if
c_cond
(paren
id|text.vaddr
OG
id|data.vaddr
op_logical_or
id|data.vaddr
OG
id|bss.vaddr
op_logical_or
id|text.vaddr
op_plus
id|text.len
OG
id|data.vaddr
op_logical_or
id|data.vaddr
op_plus
id|data.len
OG
id|bss.vaddr
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Sections ordering prevents a.out conversion.&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* If there&squot;s a data section but no text section, then the loader&n;&t;   combined everything into one section.   That needs to be the&n;&t;   text section, so just make the data section zero length following&n;&t;   text. */
r_if
c_cond
(paren
id|data.len
op_logical_and
op_logical_neg
id|text.len
)paren
(brace
id|text
op_assign
id|data
suffix:semicolon
id|data.vaddr
op_assign
id|text.vaddr
op_plus
id|text.len
suffix:semicolon
id|data.len
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* If there is a gap between text and data, we&squot;ll fill it when we copy&n;&t;   the data, so update the length of the text segment as represented in&n;&t;   a.out to reflect that, since a.out doesn&squot;t allow gaps in the program&n;&t;   address space. */
r_if
c_cond
(paren
id|text.vaddr
op_plus
id|text.len
OL
id|data.vaddr
)paren
id|text.len
op_assign
id|data.vaddr
op_minus
id|text.vaddr
suffix:semicolon
multiline_comment|/* We now have enough information to cons up an a.out header... */
id|eah.magic
op_assign
id|OMAGIC
suffix:semicolon
id|eah.vstamp
op_assign
l_int|200
suffix:semicolon
id|eah.tsize
op_assign
id|text.len
suffix:semicolon
id|eah.dsize
op_assign
id|data.len
suffix:semicolon
id|eah.bsize
op_assign
id|bss.len
suffix:semicolon
id|eah.entry
op_assign
id|ex.e_entry
suffix:semicolon
id|eah.text_start
op_assign
id|text.vaddr
suffix:semicolon
id|eah.data_start
op_assign
id|data.vaddr
suffix:semicolon
id|eah.bss_start
op_assign
id|bss.vaddr
suffix:semicolon
id|eah.gprmask
op_assign
l_int|0xf3fffffe
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|eah.cprmask
comma
l_char|&squot;&bslash;0&squot;
comma
r_sizeof
id|eah.cprmask
)paren
suffix:semicolon
id|eah.gp_value
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* unused. */
r_if
c_cond
(paren
id|format_bigendian
)paren
id|efh.f_magic
op_assign
id|MIPSEBMAGIC
suffix:semicolon
r_else
id|efh.f_magic
op_assign
id|MIPSELMAGIC
suffix:semicolon
r_if
c_cond
(paren
id|addflag
)paren
id|nosecs
op_assign
l_int|6
suffix:semicolon
r_else
id|nosecs
op_assign
l_int|3
suffix:semicolon
id|efh.f_nscns
op_assign
id|nosecs
suffix:semicolon
id|efh.f_timdat
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* bogus */
id|efh.f_symptr
op_assign
l_int|0
suffix:semicolon
id|efh.f_nsyms
op_assign
l_int|0
suffix:semicolon
id|efh.f_opthdr
op_assign
r_sizeof
id|eah
suffix:semicolon
id|efh.f_flags
op_assign
l_int|0x100f
suffix:semicolon
multiline_comment|/* Stripped, not sharable. */
id|memset
c_func
(paren
id|esecs
comma
l_int|0
comma
r_sizeof
id|esecs
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|esecs
(braket
l_int|0
)braket
dot
id|s_name
comma
l_string|&quot;.text&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|esecs
(braket
l_int|1
)braket
dot
id|s_name
comma
l_string|&quot;.data&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|esecs
(braket
l_int|2
)braket
dot
id|s_name
comma
l_string|&quot;.bss&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addflag
)paren
(brace
id|strcpy
c_func
(paren
id|esecs
(braket
l_int|3
)braket
dot
id|s_name
comma
l_string|&quot;.rdata&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|esecs
(braket
l_int|4
)braket
dot
id|s_name
comma
l_string|&quot;.sdata&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|esecs
(braket
l_int|5
)braket
dot
id|s_name
comma
l_string|&quot;.sbss&quot;
)paren
suffix:semicolon
)brace
id|esecs
(braket
l_int|0
)braket
dot
id|s_paddr
op_assign
id|esecs
(braket
l_int|0
)braket
dot
id|s_vaddr
op_assign
id|eah.text_start
suffix:semicolon
id|esecs
(braket
l_int|1
)braket
dot
id|s_paddr
op_assign
id|esecs
(braket
l_int|1
)braket
dot
id|s_vaddr
op_assign
id|eah.data_start
suffix:semicolon
id|esecs
(braket
l_int|2
)braket
dot
id|s_paddr
op_assign
id|esecs
(braket
l_int|2
)braket
dot
id|s_vaddr
op_assign
id|eah.bss_start
suffix:semicolon
r_if
c_cond
(paren
id|addflag
)paren
(brace
id|esecs
(braket
l_int|3
)braket
dot
id|s_paddr
op_assign
id|esecs
(braket
l_int|3
)braket
dot
id|s_vaddr
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|4
)braket
dot
id|s_paddr
op_assign
id|esecs
(braket
l_int|4
)braket
dot
id|s_vaddr
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|5
)braket
dot
id|s_paddr
op_assign
id|esecs
(braket
l_int|5
)braket
dot
id|s_vaddr
op_assign
l_int|0
suffix:semicolon
)brace
id|esecs
(braket
l_int|0
)braket
dot
id|s_size
op_assign
id|eah.tsize
suffix:semicolon
id|esecs
(braket
l_int|1
)braket
dot
id|s_size
op_assign
id|eah.dsize
suffix:semicolon
id|esecs
(braket
l_int|2
)braket
dot
id|s_size
op_assign
id|eah.bsize
suffix:semicolon
r_if
c_cond
(paren
id|addflag
)paren
(brace
id|esecs
(braket
l_int|3
)braket
dot
id|s_size
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|4
)braket
dot
id|s_size
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|5
)braket
dot
id|s_size
op_assign
l_int|0
suffix:semicolon
)brace
id|esecs
(braket
l_int|0
)braket
dot
id|s_scnptr
op_assign
id|N_TXTOFF
c_func
(paren
id|efh
comma
id|eah
)paren
suffix:semicolon
id|esecs
(braket
l_int|1
)braket
dot
id|s_scnptr
op_assign
id|N_DATOFF
c_func
(paren
id|efh
comma
id|eah
)paren
suffix:semicolon
DECL|macro|ECOFF_SEGMENT_ALIGNMENT
mdefine_line|#define ECOFF_SEGMENT_ALIGNMENT(a) 0x10
DECL|macro|ECOFF_ROUND
mdefine_line|#define ECOFF_ROUND(s,a) (((s)+(a)-1)&amp;~((a)-1))
id|esecs
(braket
l_int|2
)braket
dot
id|s_scnptr
op_assign
id|esecs
(braket
l_int|1
)braket
dot
id|s_scnptr
op_plus
id|ECOFF_ROUND
c_func
(paren
id|esecs
(braket
l_int|1
)braket
dot
id|s_size
comma
id|ECOFF_SEGMENT_ALIGNMENT
c_func
(paren
op_amp
id|eah
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addflag
)paren
(brace
id|esecs
(braket
l_int|3
)braket
dot
id|s_scnptr
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|4
)braket
dot
id|s_scnptr
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|5
)braket
dot
id|s_scnptr
op_assign
l_int|0
suffix:semicolon
)brace
id|esecs
(braket
l_int|0
)braket
dot
id|s_relptr
op_assign
id|esecs
(braket
l_int|1
)braket
dot
id|s_relptr
op_assign
id|esecs
(braket
l_int|2
)braket
dot
id|s_relptr
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|0
)braket
dot
id|s_lnnoptr
op_assign
id|esecs
(braket
l_int|1
)braket
dot
id|s_lnnoptr
op_assign
id|esecs
(braket
l_int|2
)braket
dot
id|s_lnnoptr
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|0
)braket
dot
id|s_nreloc
op_assign
id|esecs
(braket
l_int|1
)braket
dot
id|s_nreloc
op_assign
id|esecs
(braket
l_int|2
)braket
dot
id|s_nreloc
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|0
)braket
dot
id|s_nlnno
op_assign
id|esecs
(braket
l_int|1
)braket
dot
id|s_nlnno
op_assign
id|esecs
(braket
l_int|2
)braket
dot
id|s_nlnno
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|addflag
)paren
(brace
id|esecs
(braket
l_int|3
)braket
dot
id|s_relptr
op_assign
id|esecs
(braket
l_int|4
)braket
dot
id|s_relptr
op_assign
id|esecs
(braket
l_int|5
)braket
dot
id|s_relptr
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|3
)braket
dot
id|s_lnnoptr
op_assign
id|esecs
(braket
l_int|4
)braket
dot
id|s_lnnoptr
op_assign
id|esecs
(braket
l_int|5
)braket
dot
id|s_lnnoptr
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|3
)braket
dot
id|s_nreloc
op_assign
id|esecs
(braket
l_int|4
)braket
dot
id|s_nreloc
op_assign
id|esecs
(braket
l_int|5
)braket
dot
id|s_nreloc
op_assign
l_int|0
suffix:semicolon
id|esecs
(braket
l_int|3
)braket
dot
id|s_nlnno
op_assign
id|esecs
(braket
l_int|4
)braket
dot
id|s_nlnno
op_assign
id|esecs
(braket
l_int|5
)braket
dot
id|s_nlnno
op_assign
l_int|0
suffix:semicolon
)brace
id|esecs
(braket
l_int|0
)braket
dot
id|s_flags
op_assign
l_int|0x20
suffix:semicolon
id|esecs
(braket
l_int|1
)braket
dot
id|s_flags
op_assign
l_int|0x40
suffix:semicolon
id|esecs
(braket
l_int|2
)braket
dot
id|s_flags
op_assign
l_int|0x82
suffix:semicolon
r_if
c_cond
(paren
id|addflag
)paren
(brace
id|esecs
(braket
l_int|3
)braket
dot
id|s_flags
op_assign
l_int|0x100
suffix:semicolon
id|esecs
(braket
l_int|4
)braket
dot
id|s_flags
op_assign
l_int|0x200
suffix:semicolon
id|esecs
(braket
l_int|5
)braket
dot
id|s_flags
op_assign
l_int|0x400
suffix:semicolon
)brace
multiline_comment|/* Make the output file... */
r_if
c_cond
(paren
(paren
id|outfile
op_assign
id|open
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
id|O_WRONLY
op_or
id|O_CREAT
comma
l_int|0777
)paren
)paren
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Unable to create %s: %s&bslash;n&quot;
comma
id|argv
(braket
l_int|2
)braket
comma
id|strerror
c_func
(paren
id|errno
)paren
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
id|must_convert_endian
)paren
id|convert_ecoff_filehdr
c_func
(paren
op_amp
id|efh
)paren
suffix:semicolon
multiline_comment|/* Write the headers... */
id|i
op_assign
id|write
c_func
(paren
id|outfile
comma
op_amp
id|efh
comma
r_sizeof
id|efh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
r_sizeof
id|efh
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;efh: write&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
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
id|nosecs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printf
(paren
l_string|&quot;Section %d: %s phys %lx  size %lx  file offset %lx&bslash;n&quot;
comma
id|i
comma
id|esecs
(braket
id|i
)braket
dot
id|s_name
comma
id|esecs
(braket
id|i
)braket
dot
id|s_paddr
comma
id|esecs
(braket
id|i
)braket
dot
id|s_size
comma
id|esecs
(braket
id|i
)braket
dot
id|s_scnptr
)paren
suffix:semicolon
)brace
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;wrote %d byte file header.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|must_convert_endian
)paren
id|convert_ecoff_aouthdr
c_func
(paren
op_amp
id|eah
)paren
suffix:semicolon
id|i
op_assign
id|write
c_func
(paren
id|outfile
comma
op_amp
id|eah
comma
r_sizeof
id|eah
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
r_sizeof
id|eah
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;eah: write&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;wrote %d byte a.out header.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|must_convert_endian
)paren
id|convert_ecoff_esecs
c_func
(paren
op_amp
id|esecs
(braket
l_int|0
)braket
comma
id|nosecs
)paren
suffix:semicolon
id|i
op_assign
id|write
c_func
(paren
id|outfile
comma
op_amp
id|esecs
comma
id|nosecs
op_star
r_sizeof
(paren
r_struct
id|scnhdr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|nosecs
op_star
r_sizeof
(paren
r_struct
id|scnhdr
)paren
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;esecs: write&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;wrote %d bytes of section headers.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|pad
op_assign
(paren
r_sizeof
(paren
id|efh
)paren
op_plus
r_sizeof
(paren
id|eah
)paren
op_plus
id|nosecs
op_star
r_sizeof
(paren
r_struct
id|scnhdr
)paren
)paren
op_amp
l_int|15
suffix:semicolon
r_if
c_cond
(paren
id|pad
)paren
(brace
id|pad
op_assign
l_int|16
op_minus
id|pad
suffix:semicolon
id|i
op_assign
id|write
c_func
(paren
id|outfile
comma
l_string|&quot;&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
comma
id|pad
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;ipad: write&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;wrote %d byte pad.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Copy the loadable sections.   Zero-fill any gaps less than 64k;&n;&t; * complain about any zero-filling, and die if we&squot;re asked to zero-fill&n;&t; * more than 64k.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ex.e_phnum
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Unprocessable sections were handled above, so just verify that&n;&t;&t;   the section can be loaded before copying. */
r_if
c_cond
(paren
id|ph
(braket
id|i
)braket
dot
id|p_type
op_eq
id|PT_LOAD
op_logical_and
id|ph
(braket
id|i
)braket
dot
id|p_filesz
)paren
(brace
r_if
c_cond
(paren
id|cur_vma
op_ne
id|ph
(braket
id|i
)braket
dot
id|p_vaddr
)paren
(brace
r_int
r_int
id|gap
op_assign
id|ph
(braket
id|i
)braket
dot
id|p_vaddr
op_minus
id|cur_vma
suffix:semicolon
r_char
id|obuf
(braket
l_int|1024
)braket
suffix:semicolon
r_if
c_cond
(paren
id|gap
OG
l_int|65536
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Intersegment gap (%ld bytes) too large.&bslash;n&quot;
comma
id|gap
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Warning: %ld byte intersegment gap.&bslash;n&quot;
comma
id|gap
)paren
suffix:semicolon
id|memset
c_func
(paren
id|obuf
comma
l_int|0
comma
r_sizeof
id|obuf
)paren
suffix:semicolon
r_while
c_loop
(paren
id|gap
)paren
(brace
r_int
id|count
op_assign
id|write
c_func
(paren
id|outfile
comma
id|obuf
comma
(paren
id|gap
OG
r_sizeof
id|obuf
ques
c_cond
r_sizeof
id|obuf
suffix:colon
id|gap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Error writing gap: %s&bslash;n&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|gap
op_sub_assign
id|count
suffix:semicolon
)brace
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;writing %d bytes...&bslash;n&quot;
comma
id|ph
(braket
id|i
)braket
dot
id|p_filesz
)paren
suffix:semicolon
id|copy
c_func
(paren
id|outfile
comma
id|infile
comma
id|ph
(braket
id|i
)braket
dot
id|p_offset
comma
id|ph
(braket
id|i
)braket
dot
id|p_filesz
)paren
suffix:semicolon
id|cur_vma
op_assign
id|ph
(braket
id|i
)braket
dot
id|p_vaddr
op_plus
id|ph
(braket
id|i
)braket
dot
id|p_filesz
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Write a page of padding for boot PROMS that read entire pages.&n;&t; * Without this, they may attempt to read past the end of the&n;&t; * data section, incur an error, and refuse to boot.&n;&t; */
(brace
r_char
id|obuf
(braket
l_int|4096
)braket
suffix:semicolon
id|memset
c_func
(paren
id|obuf
comma
l_int|0
comma
r_sizeof
id|obuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|outfile
comma
id|obuf
comma
r_sizeof
(paren
id|obuf
)paren
)paren
op_ne
r_sizeof
(paren
id|obuf
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Error writing PROM padding: %s&bslash;n&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Looks like we won... */
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
