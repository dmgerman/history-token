multiline_comment|/* &n; * Copyright (C) 2000 - 2003 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_ARCHPARAM_I386_H
DECL|macro|__UM_ARCHPARAM_I386_H
mdefine_line|#define __UM_ARCHPARAM_I386_H
multiline_comment|/********* Bits for asm-um/elf.h ************/
macro_line|#include &quot;user.h&quot;
r_extern
r_char
op_star
id|elf_aux_platform
suffix:semicolon
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM (elf_aux_platform)
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE (2 * TASK_SIZE / 3)
DECL|typedef|elf_fpregset_t
r_typedef
r_struct
id|user_i387_struct
id|elf_fpregset_t
suffix:semicolon
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof (struct user_regs_struct) / sizeof(elf_greg_t))
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA        ELFDATA2LSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH        EM_386
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(regs, load_addr) do { &bslash;&n;&t;PT_REGS_EBX(regs) = 0; &bslash;&n;&t;PT_REGS_ECX(regs) = 0; &bslash;&n;&t;PT_REGS_EDX(regs) = 0; &bslash;&n;&t;PT_REGS_ESI(regs) = 0; &bslash;&n;&t;PT_REGS_EDI(regs) = 0; &bslash;&n;&t;PT_REGS_EBP(regs) = 0; &bslash;&n;&t;PT_REGS_EAX(regs) = 0; &bslash;&n;} while(0)
multiline_comment|/* Shamelessly stolen from include/asm-i386/elf.h */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs) do {&t;&bslash;&n;&t;pr_reg[0] = PT_REGS_EBX(regs);&t;&t;&bslash;&n;&t;pr_reg[1] = PT_REGS_ECX(regs);&t;&t;&bslash;&n;&t;pr_reg[2] = PT_REGS_EDX(regs);&t;&t;&bslash;&n;&t;pr_reg[3] = PT_REGS_ESI(regs);&t;&t;&bslash;&n;&t;pr_reg[4] = PT_REGS_EDI(regs);&t;&t;&bslash;&n;&t;pr_reg[5] = PT_REGS_EBP(regs);&t;&t;&bslash;&n;&t;pr_reg[6] = PT_REGS_EAX(regs);&t;&t;&bslash;&n;&t;pr_reg[7] = PT_REGS_DS(regs);&t;&t;&bslash;&n;&t;pr_reg[8] = PT_REGS_ES(regs);&t;&t;&bslash;&n;&t;/* fake once used fs and gs selectors? */&t;&bslash;&n;&t;pr_reg[9] = PT_REGS_DS(regs);&t;&t;&bslash;&n;&t;pr_reg[10] = PT_REGS_DS(regs);&t;&t;&bslash;&n;&t;pr_reg[11] = PT_REGS_SYSCALL_NR(regs);&t;&bslash;&n;&t;pr_reg[12] = PT_REGS_IP(regs);&t;&t;&bslash;&n;&t;pr_reg[13] = PT_REGS_CS(regs);&t;&t;&bslash;&n;&t;pr_reg[14] = PT_REGS_EFLAGS(regs);&t;&bslash;&n;&t;pr_reg[15] = PT_REGS_SP(regs);&t;&t;&bslash;&n;&t;pr_reg[16] = PT_REGS_SS(regs);&t;&t;&bslash;&n;} while(0);
r_extern
r_int
r_int
id|vsyscall_ehdr
suffix:semicolon
r_extern
r_int
r_int
id|vsyscall_end
suffix:semicolon
r_extern
r_int
r_int
id|__kernel_vsyscall
suffix:semicolon
DECL|macro|VSYSCALL_BASE
mdefine_line|#define VSYSCALL_BASE vsyscall_ehdr
DECL|macro|VSYSCALL_END
mdefine_line|#define VSYSCALL_END vsyscall_end
multiline_comment|/*&n; * Architecture-neutral AT_ values in 0-17, leave some room&n; * for more of them, start the x86-specific ones at 32.&n; */
DECL|macro|AT_SYSINFO
mdefine_line|#define AT_SYSINFO&t;&t;32
DECL|macro|AT_SYSINFO_EHDR
mdefine_line|#define AT_SYSINFO_EHDR&t;&t;33
DECL|macro|ARCH_DLINFO
mdefine_line|#define ARCH_DLINFO&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( vsyscall_ehdr ) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;NEW_AUX_ENT(AT_SYSINFO,&t;__kernel_vsyscall);&t;&bslash;&n;&t;&t;NEW_AUX_ENT(AT_SYSINFO_EHDR, vsyscall_ehdr);&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * These macros parameterize elf_core_dump in fs/binfmt_elf.c to write out&n; * extra segments containing the vsyscall DSO contents.  Dumping its&n; * contents makes post-mortem fully interpretable later without matching up&n; * the same kernel and hardware config to see what PC values meant.&n; * Dumping its extra ELF program headers includes all the other information&n; * a debugger needs to easily find how the vsyscall DSO was being used.&n; */
DECL|macro|ELF_CORE_EXTRA_PHDRS
mdefine_line|#define ELF_CORE_EXTRA_PHDRS&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;(vsyscall_ehdr ? (((struct elfhdr *)vsyscall_ehdr)-&gt;e_phnum) : 0 )
DECL|macro|ELF_CORE_WRITE_EXTRA_PHDRS
mdefine_line|#define ELF_CORE_WRITE_EXTRA_PHDRS&t;&t;&t;&t;&t;      &bslash;&n;if ( vsyscall_ehdr ) {&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;const struct elfhdr *const ehdrp = (struct elfhdr *)vsyscall_ehdr;    &bslash;&n;&t;const struct elf_phdr *const phdrp =&t;&t;&t;&t;      &bslash;&n;&t;&t;(const struct elf_phdr *) (vsyscall_ehdr + ehdrp-&gt;e_phoff);   &bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;Elf32_Off ofs = 0;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;for (i = 0; i &lt; ehdrp-&gt;e_phnum; ++i) {&t;&t;&t;&t;      &bslash;&n;&t;&t;struct elf_phdr phdr = phdrp[i];&t;&t;&t;      &bslash;&n;&t;&t;if (phdr.p_type == PT_LOAD) {&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;ofs = phdr.p_offset = offset;&t;&t;&t;      &bslash;&n;&t;&t;&t;offset += phdr.p_filesz;&t;&t;&t;      &bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;phdr.p_offset += ofs;&t;&t;&t;&t;      &bslash;&n;&t;&t;phdr.p_paddr = 0; /* match other core phdrs */&t;&t;      &bslash;&n;&t;&t;DUMP_WRITE(&amp;phdr, sizeof(phdr));&t;&t;&t;      &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;}
DECL|macro|ELF_CORE_WRITE_EXTRA_DATA
mdefine_line|#define ELF_CORE_WRITE_EXTRA_DATA&t;&t;&t;&t;&t;      &bslash;&n;if ( vsyscall_ehdr ) {&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;const struct elfhdr *const ehdrp = (struct elfhdr *)vsyscall_ehdr;    &bslash;&n;&t;const struct elf_phdr *const phdrp =&t;&t;&t;&t;      &bslash;&n;&t;&t;(const struct elf_phdr *) (vsyscall_ehdr + ehdrp-&gt;e_phoff);   &bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;for (i = 0; i &lt; ehdrp-&gt;e_phnum; ++i) {&t;&t;&t;&t;      &bslash;&n;&t;&t;if (phdrp[i].p_type == PT_LOAD)&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;DUMP_WRITE((void *) phdrp[i].p_vaddr,&t;&t;      &bslash;&n;&t;&t;&t;&t;   phdrp[i].p_filesz);&t;&t;&t;      &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;}
DECL|macro|R_386_NONE
mdefine_line|#define R_386_NONE&t;0
DECL|macro|R_386_32
mdefine_line|#define R_386_32&t;1
DECL|macro|R_386_PC32
mdefine_line|#define R_386_PC32&t;2
DECL|macro|R_386_GOT32
mdefine_line|#define R_386_GOT32&t;3
DECL|macro|R_386_PLT32
mdefine_line|#define R_386_PLT32&t;4
DECL|macro|R_386_COPY
mdefine_line|#define R_386_COPY&t;5
DECL|macro|R_386_GLOB_DAT
mdefine_line|#define R_386_GLOB_DAT&t;6
DECL|macro|R_386_JMP_SLOT
mdefine_line|#define R_386_JMP_SLOT&t;7
DECL|macro|R_386_RELATIVE
mdefine_line|#define R_386_RELATIVE&t;8
DECL|macro|R_386_GOTOFF
mdefine_line|#define R_386_GOTOFF&t;9
DECL|macro|R_386_GOTPC
mdefine_line|#define R_386_GOTPC&t;10
DECL|macro|R_386_NUM
mdefine_line|#define R_386_NUM&t;11
multiline_comment|/********* Nothing for asm-um/hardirq.h **********/
multiline_comment|/********* Nothing for asm-um/hw_irq.h **********/
multiline_comment|/********* Nothing for asm-um/string.h **********/
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
