multiline_comment|/*&n; * Copyright 2003 PathScale, Inc.&n; *&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_ARCHPARAM_X86_64_H
DECL|macro|__UM_ARCHPARAM_X86_64_H
mdefine_line|#define __UM_ARCHPARAM_X86_64_H
macro_line|#include &lt;asm/user.h&gt;
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM &quot;x86_64&quot;
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE (2 * TASK_SIZE / 3)
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|typedef|elf_fpregset_t
r_typedef
r_struct
(brace
)brace
id|elf_fpregset_t
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
mdefine_line|#define ELF_ARCH        EM_X86_64
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(regs, load_addr)    do { &bslash;&n;&t;PT_REGS_RBX(regs) = 0; &bslash;&n;&t;PT_REGS_RCX(regs) = 0; &bslash;&n;&t;PT_REGS_RDX(regs) = 0; &bslash;&n;&t;PT_REGS_RSI(regs) = 0; &bslash;&n;&t;PT_REGS_RDI(regs) = 0; &bslash;&n;&t;PT_REGS_RBP(regs) = 0; &bslash;&n;&t;PT_REGS_RAX(regs) = 0; &bslash;&n;&t;PT_REGS_R8(regs) = 0; &bslash;&n;&t;PT_REGS_R9(regs) = 0; &bslash;&n;&t;PT_REGS_R10(regs) = 0; &bslash;&n;&t;PT_REGS_R11(regs) = 0; &bslash;&n;&t;PT_REGS_R12(regs) = 0; &bslash;&n;&t;PT_REGS_R13(regs) = 0; &bslash;&n;&t;PT_REGS_R14(regs) = 0; &bslash;&n;&t;PT_REGS_R15(regs) = 0; &bslash;&n;} while (0)
macro_line|#ifdef TIF_IA32 /* XXX */
DECL|variable|TIF_IA32
id|clear_thread_flag
c_func
(paren
id|TIF_IA32
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* No user-accessible fixmap addresses, i.e. vsyscall */
DECL|macro|FIXADDR_USER_START
mdefine_line|#define FIXADDR_USER_START&t;0
DECL|macro|FIXADDR_USER_END
mdefine_line|#define FIXADDR_USER_END&t;0
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
