macro_line|#ifndef __UM_ARCHPARAM_PPC_H
DECL|macro|__UM_ARCHPARAM_PPC_H
mdefine_line|#define __UM_ARCHPARAM_PPC_H
multiline_comment|/********* Bits for asm-um/elf.h ************/
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM (0)
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE (0x08000000)
multiline_comment|/* the following stolen from asm-ppc/elf.h */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG&t;48&t;/* includes nip, msr, lr, etc. */
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG&t;33&t;/* includes fpscr */
multiline_comment|/* General registers */
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
multiline_comment|/* Floating point registers */
DECL|typedef|elf_fpreg_t
r_typedef
r_float
id|elf_fpreg_t
suffix:semicolon
DECL|typedef|elf_fpregset_t
r_typedef
id|elf_fpreg_t
id|elf_fpregset_t
(braket
id|ELF_NFPREG
)braket
suffix:semicolon
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA        ELFDATA2MSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_PPC
multiline_comment|/********* Bits for asm-um/hw_irq.h **********/
r_struct
id|hw_interrupt_type
suffix:semicolon
multiline_comment|/********* Bits for asm-um/hardirq.h **********/
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu, irq) hardirq_enter(cpu)
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu, irq) hardirq_exit(cpu)
multiline_comment|/********* Bits for asm-um/string.h **********/
DECL|macro|__HAVE_ARCH_STRRCHR
mdefine_line|#define __HAVE_ARCH_STRRCHR
macro_line|#endif
eof
