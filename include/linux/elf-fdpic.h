multiline_comment|/* elf-fdpic.h: FDPIC ELF load map&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_ELF_FDPIC_H
DECL|macro|_LINUX_ELF_FDPIC_H
mdefine_line|#define _LINUX_ELF_FDPIC_H
macro_line|#include &lt;linux/elf.h&gt;
DECL|macro|PT_GNU_STACK
mdefine_line|#define PT_GNU_STACK    (PT_LOOS + 0x474e551)
multiline_comment|/* segment mappings for ELF FDPIC libraries/executables/interpreters */
DECL|struct|elf32_fdpic_loadseg
r_struct
id|elf32_fdpic_loadseg
(brace
DECL|member|addr
id|Elf32_Addr
id|addr
suffix:semicolon
multiline_comment|/* core address to which mapped */
DECL|member|p_vaddr
id|Elf32_Addr
id|p_vaddr
suffix:semicolon
multiline_comment|/* VMA recorded in file */
DECL|member|p_memsz
id|Elf32_Word
id|p_memsz
suffix:semicolon
multiline_comment|/* allocation size recorded in file */
)brace
suffix:semicolon
DECL|struct|elf32_fdpic_loadmap
r_struct
id|elf32_fdpic_loadmap
(brace
DECL|member|version
id|Elf32_Half
id|version
suffix:semicolon
multiline_comment|/* version of these structures, just in case... */
DECL|member|nsegs
id|Elf32_Half
id|nsegs
suffix:semicolon
multiline_comment|/* number of segments */
DECL|member|segs
r_struct
id|elf32_fdpic_loadseg
id|segs
(braket
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ELF32_FDPIC_LOADMAP_VERSION
mdefine_line|#define ELF32_FDPIC_LOADMAP_VERSION&t;0x0000
multiline_comment|/*&n; * binfmt binary parameters structure&n; */
DECL|struct|elf_fdpic_params
r_struct
id|elf_fdpic_params
(brace
DECL|member|hdr
r_struct
id|elfhdr
id|hdr
suffix:semicolon
multiline_comment|/* ref copy of ELF header */
DECL|member|phdrs
r_struct
id|elf_phdr
op_star
id|phdrs
suffix:semicolon
multiline_comment|/* ref copy of PT_PHDR table */
DECL|member|loadmap
r_struct
id|elf32_fdpic_loadmap
op_star
id|loadmap
suffix:semicolon
multiline_comment|/* loadmap to be passed to userspace */
DECL|member|elfhdr_addr
r_int
r_int
id|elfhdr_addr
suffix:semicolon
multiline_comment|/* mapped ELF header user address */
DECL|member|ph_addr
r_int
r_int
id|ph_addr
suffix:semicolon
multiline_comment|/* mapped PT_PHDR user address */
DECL|member|map_addr
r_int
r_int
id|map_addr
suffix:semicolon
multiline_comment|/* mapped loadmap user address */
DECL|member|entry_addr
r_int
r_int
id|entry_addr
suffix:semicolon
multiline_comment|/* mapped entry user address */
DECL|member|stack_size
r_int
r_int
id|stack_size
suffix:semicolon
multiline_comment|/* stack size requested (PT_GNU_STACK) */
DECL|member|dynamic_addr
r_int
r_int
id|dynamic_addr
suffix:semicolon
multiline_comment|/* mapped PT_DYNAMIC user address */
DECL|member|load_addr
r_int
r_int
id|load_addr
suffix:semicolon
multiline_comment|/* user address at which to map binary */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|ELF_FDPIC_FLAG_ARRANGEMENT
mdefine_line|#define ELF_FDPIC_FLAG_ARRANGEMENT&t;0x0000000f&t;/* PT_LOAD arrangement flags */
DECL|macro|ELF_FDPIC_FLAG_INDEPENDENT
mdefine_line|#define ELF_FDPIC_FLAG_INDEPENDENT&t;0x00000000&t;/* PT_LOADs can be put anywhere */
DECL|macro|ELF_FDPIC_FLAG_HONOURVADDR
mdefine_line|#define ELF_FDPIC_FLAG_HONOURVADDR&t;0x00000001&t;/* PT_LOAD.vaddr must be honoured */
DECL|macro|ELF_FDPIC_FLAG_CONSTDISP
mdefine_line|#define ELF_FDPIC_FLAG_CONSTDISP&t;0x00000002&t;/* PT_LOADs require constant&n;&t;&t;&t;&t;&t;&t;&t; * displacement */
DECL|macro|ELF_FDPIC_FLAG_CONTIGUOUS
mdefine_line|#define ELF_FDPIC_FLAG_CONTIGUOUS&t;0x00000003&t;/* PT_LOADs should be contiguous */
DECL|macro|ELF_FDPIC_FLAG_EXEC_STACK
mdefine_line|#define ELF_FDPIC_FLAG_EXEC_STACK&t;0x00000010&t;/* T if stack to be executable */
DECL|macro|ELF_FDPIC_FLAG_NOEXEC_STACK
mdefine_line|#define ELF_FDPIC_FLAG_NOEXEC_STACK&t;0x00000020&t;/* T if stack not to be executable */
DECL|macro|ELF_FDPIC_FLAG_EXECUTABLE
mdefine_line|#define ELF_FDPIC_FLAG_EXECUTABLE&t;0x00000040&t;/* T if this object is the executable */
DECL|macro|ELF_FDPIC_FLAG_PRESENT
mdefine_line|#define ELF_FDPIC_FLAG_PRESENT&t;&t;0x80000000&t;/* T if this object is present */
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
r_extern
r_void
id|elf_fdpic_arch_lay_out_mm
c_func
(paren
r_struct
id|elf_fdpic_params
op_star
id|exec_params
comma
r_struct
id|elf_fdpic_params
op_star
id|interp_params
comma
r_int
r_int
op_star
id|start_stack
comma
r_int
r_int
op_star
id|start_brk
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _LINUX_ELF_FDPIC_H */
eof
