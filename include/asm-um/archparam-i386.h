multiline_comment|/* &n; * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_ARCHPARAM_I386_H
DECL|macro|__UM_ARCHPARAM_I386_H
mdefine_line|#define __UM_ARCHPARAM_I386_H
multiline_comment|/********* Bits for asm-um/elf.h ************/
macro_line|#include &quot;user.h&quot;
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM &quot;i586&quot;
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
multiline_comment|/********* Bits for asm-um/delay.h **********/
DECL|typedef|um_udelay_t
r_typedef
r_int
r_int
id|um_udelay_t
suffix:semicolon
multiline_comment|/********* Nothing for asm-um/hardirq.h **********/
multiline_comment|/********* Nothing for asm-um/hw_irq.h **********/
multiline_comment|/********* Nothing for asm-um/string.h **********/
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
