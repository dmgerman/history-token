macro_line|#ifndef __ASMPARISC_ELF_H
DECL|macro|__ASMPARISC_ELF_H
mdefine_line|#define __ASMPARISC_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|EM_PARISC
mdefine_line|#define EM_PARISC 15
multiline_comment|/* HPPA specific definitions.  */
multiline_comment|/* Legal values for e_flags field of Elf32_Ehdr.  */
DECL|macro|EF_PARISC_TRAPNIL
mdefine_line|#define EF_PARISC_TRAPNIL&t;0x00010000 /* Trap nil pointer dereference.  */
DECL|macro|EF_PARISC_EXT
mdefine_line|#define EF_PARISC_EXT&t;&t;0x00020000 /* Program uses arch. extensions. */
DECL|macro|EF_PARISC_LSB
mdefine_line|#define EF_PARISC_LSB&t;&t;0x00040000 /* Program expects little endian. */
DECL|macro|EF_PARISC_WIDE
mdefine_line|#define EF_PARISC_WIDE&t;&t;0x00080000 /* Program expects wide mode.  */
DECL|macro|EF_PARISC_NO_KABP
mdefine_line|#define EF_PARISC_NO_KABP&t;0x00100000 /* No kernel assisted branch&n;&t;&t;&t;&t;&t;      prediction.  */
DECL|macro|EF_PARISC_LAZYSWAP
mdefine_line|#define EF_PARISC_LAZYSWAP&t;0x00400000 /* Allow lazy swapping.  */
DECL|macro|EF_PARISC_ARCH
mdefine_line|#define EF_PARISC_ARCH&t;&t;0x0000ffff /* Architecture version.  */
multiline_comment|/* Defined values for `e_flags &amp; EF_PARISC_ARCH&squot; are:  */
DECL|macro|EFA_PARISC_1_0
mdefine_line|#define EFA_PARISC_1_0&t;&t;    0x020b /* PA-RISC 1.0 big-endian.  */
DECL|macro|EFA_PARISC_1_1
mdefine_line|#define EFA_PARISC_1_1&t;&t;    0x0210 /* PA-RISC 1.1 big-endian.  */
DECL|macro|EFA_PARISC_2_0
mdefine_line|#define EFA_PARISC_2_0&t;&t;    0x0214 /* PA-RISC 2.0 big-endian.  */
multiline_comment|/* Additional section indeces.  */
DECL|macro|SHN_PARISC_ANSI_COMMON
mdefine_line|#define SHN_PARISC_ANSI_COMMON&t;0xff00&t;   /* Section for tenatively declared&n;&t;&t;&t;&t;&t;      symbols in ANSI C.  */
DECL|macro|SHN_PARISC_HUGE_COMMON
mdefine_line|#define SHN_PARISC_HUGE_COMMON&t;0xff01&t;   /* Common blocks in huge model.  */
multiline_comment|/* Legal values for sh_type field of Elf32_Shdr.  */
DECL|macro|SHT_PARISC_EXT
mdefine_line|#define SHT_PARISC_EXT&t;&t;0x70000000 /* Contains product specific ext. */
DECL|macro|SHT_PARISC_UNWIND
mdefine_line|#define SHT_PARISC_UNWIND&t;0x70000001 /* Unwind information.  */
DECL|macro|SHT_PARISC_DOC
mdefine_line|#define SHT_PARISC_DOC&t;&t;0x70000002 /* Debug info for optimized code. */
multiline_comment|/* Legal values for sh_flags field of Elf32_Shdr.  */
DECL|macro|SHF_PARISC_SHORT
mdefine_line|#define SHF_PARISC_SHORT&t;0x20000000 /* Section with short addressing. */
DECL|macro|SHF_PARISC_HUGE
mdefine_line|#define SHF_PARISC_HUGE&t;&t;0x40000000 /* Section far from gp.  */
DECL|macro|SHF_PARISC_SBP
mdefine_line|#define SHF_PARISC_SBP&t;&t;0x80000000 /* Static branch prediction code. */
multiline_comment|/* Legal values for ST_TYPE subfield of st_info (symbol type).  */
DECL|macro|STT_PARISC_MILLICODE
mdefine_line|#define STT_PARISC_MILLICODE&t;13&t;/* Millicode function entry point.  */
DECL|macro|STT_HP_OPAQUE
mdefine_line|#define STT_HP_OPAQUE&t;&t;(STT_LOOS + 0x1)
DECL|macro|STT_HP_STUB
mdefine_line|#define STT_HP_STUB&t;&t;(STT_LOOS + 0x2)
multiline_comment|/* HPPA relocs.  */
DECL|macro|R_PARISC_NONE
mdefine_line|#define R_PARISC_NONE&t;&t;0&t;/* No reloc.  */
DECL|macro|R_PARISC_DIR32
mdefine_line|#define R_PARISC_DIR32&t;&t;1&t;/* Direct 32-bit reference.  */
DECL|macro|R_PARISC_DIR21L
mdefine_line|#define R_PARISC_DIR21L&t;&t;2&t;/* Left 21 bits of eff. address.  */
DECL|macro|R_PARISC_DIR17R
mdefine_line|#define R_PARISC_DIR17R&t;&t;3&t;/* Right 17 bits of eff. address.  */
DECL|macro|R_PARISC_DIR17F
mdefine_line|#define R_PARISC_DIR17F&t;&t;4&t;/* 17 bits of eff. address.  */
DECL|macro|R_PARISC_DIR14R
mdefine_line|#define R_PARISC_DIR14R&t;&t;6&t;/* Right 14 bits of eff. address.  */
DECL|macro|R_PARISC_PCREL32
mdefine_line|#define R_PARISC_PCREL32&t;9&t;/* 32-bit rel. address.  */
DECL|macro|R_PARISC_PCREL21L
mdefine_line|#define R_PARISC_PCREL21L&t;10&t;/* Left 21 bits of rel. address.  */
DECL|macro|R_PARISC_PCREL17R
mdefine_line|#define R_PARISC_PCREL17R&t;11&t;/* Right 17 bits of rel. address.  */
DECL|macro|R_PARISC_PCREL17F
mdefine_line|#define R_PARISC_PCREL17F&t;12&t;/* 17 bits of rel. address.  */
DECL|macro|R_PARISC_PCREL14R
mdefine_line|#define R_PARISC_PCREL14R&t;14&t;/* Right 14 bits of rel. address.  */
DECL|macro|R_PARISC_DPREL21L
mdefine_line|#define R_PARISC_DPREL21L&t;18&t;/* Left 21 bits of rel. address.  */
DECL|macro|R_PARISC_DPREL14R
mdefine_line|#define R_PARISC_DPREL14R&t;22&t;/* Right 14 bits of rel. address.  */
DECL|macro|R_PARISC_GPREL21L
mdefine_line|#define R_PARISC_GPREL21L&t;26&t;/* GP-relative, left 21 bits.  */
DECL|macro|R_PARISC_GPREL14R
mdefine_line|#define R_PARISC_GPREL14R&t;30&t;/* GP-relative, right 14 bits.  */
DECL|macro|R_PARISC_LTOFF21L
mdefine_line|#define R_PARISC_LTOFF21L&t;34&t;/* LT-relative, left 21 bits.  */
DECL|macro|R_PARISC_LTOFF14R
mdefine_line|#define R_PARISC_LTOFF14R&t;38&t;/* LT-relative, right 14 bits.  */
DECL|macro|R_PARISC_SECREL32
mdefine_line|#define R_PARISC_SECREL32&t;41&t;/* 32 bits section rel. address.  */
DECL|macro|R_PARISC_SEGBASE
mdefine_line|#define R_PARISC_SEGBASE&t;48&t;/* No relocation, set segment base.  */
DECL|macro|R_PARISC_SEGREL32
mdefine_line|#define R_PARISC_SEGREL32&t;49&t;/* 32 bits segment rel. address.  */
DECL|macro|R_PARISC_PLTOFF21L
mdefine_line|#define R_PARISC_PLTOFF21L&t;50&t;/* PLT rel. address, left 21 bits.  */
DECL|macro|R_PARISC_PLTOFF14R
mdefine_line|#define R_PARISC_PLTOFF14R&t;54&t;/* PLT rel. address, right 14 bits.  */
DECL|macro|R_PARISC_LTOFF_FPTR32
mdefine_line|#define R_PARISC_LTOFF_FPTR32&t;57&t;/* 32 bits LT-rel. function pointer. */
DECL|macro|R_PARISC_LTOFF_FPTR21L
mdefine_line|#define R_PARISC_LTOFF_FPTR21L&t;58&t;/* LT-rel. fct ptr, left 21 bits. */
DECL|macro|R_PARISC_LTOFF_FPTR14R
mdefine_line|#define R_PARISC_LTOFF_FPTR14R&t;62&t;/* LT-rel. fct ptr, right 14 bits. */
DECL|macro|R_PARISC_FPTR64
mdefine_line|#define R_PARISC_FPTR64&t;&t;64&t;/* 64 bits function address.  */
DECL|macro|R_PARISC_PLABEL32
mdefine_line|#define R_PARISC_PLABEL32&t;65&t;/* 32 bits function address.  */
DECL|macro|R_PARISC_PCREL64
mdefine_line|#define R_PARISC_PCREL64&t;72&t;/* 64 bits PC-rel. address.  */
DECL|macro|R_PARISC_PCREL22F
mdefine_line|#define R_PARISC_PCREL22F&t;74&t;/* 22 bits PC-rel. address.  */
DECL|macro|R_PARISC_PCREL14WR
mdefine_line|#define R_PARISC_PCREL14WR&t;75&t;/* PC-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_PCREL14DR
mdefine_line|#define R_PARISC_PCREL14DR&t;76&t;/* PC rel. address, right 14 bits.  */
DECL|macro|R_PARISC_PCREL16F
mdefine_line|#define R_PARISC_PCREL16F&t;77&t;/* 16 bits PC-rel. address.  */
DECL|macro|R_PARISC_PCREL16WF
mdefine_line|#define R_PARISC_PCREL16WF&t;78&t;/* 16 bits PC-rel. address.  */
DECL|macro|R_PARISC_PCREL16DF
mdefine_line|#define R_PARISC_PCREL16DF&t;79&t;/* 16 bits PC-rel. address.  */
DECL|macro|R_PARISC_DIR64
mdefine_line|#define R_PARISC_DIR64&t;&t;80&t;/* 64 bits of eff. address.  */
DECL|macro|R_PARISC_DIR14WR
mdefine_line|#define R_PARISC_DIR14WR&t;83&t;/* 14 bits of eff. address.  */
DECL|macro|R_PARISC_DIR14DR
mdefine_line|#define R_PARISC_DIR14DR&t;84&t;/* 14 bits of eff. address.  */
DECL|macro|R_PARISC_DIR16F
mdefine_line|#define R_PARISC_DIR16F&t;&t;85&t;/* 16 bits of eff. address.  */
DECL|macro|R_PARISC_DIR16WF
mdefine_line|#define R_PARISC_DIR16WF&t;86&t;/* 16 bits of eff. address.  */
DECL|macro|R_PARISC_DIR16DF
mdefine_line|#define R_PARISC_DIR16DF&t;87&t;/* 16 bits of eff. address.  */
DECL|macro|R_PARISC_GPREL64
mdefine_line|#define R_PARISC_GPREL64&t;88&t;/* 64 bits of GP-rel. address.  */
DECL|macro|R_PARISC_GPREL14WR
mdefine_line|#define R_PARISC_GPREL14WR&t;91&t;/* GP-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_GPREL14DR
mdefine_line|#define R_PARISC_GPREL14DR&t;92&t;/* GP-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_GPREL16F
mdefine_line|#define R_PARISC_GPREL16F&t;93&t;/* 16 bits GP-rel. address.  */
DECL|macro|R_PARISC_GPREL16WF
mdefine_line|#define R_PARISC_GPREL16WF&t;94&t;/* 16 bits GP-rel. address.  */
DECL|macro|R_PARISC_GPREL16DF
mdefine_line|#define R_PARISC_GPREL16DF&t;95&t;/* 16 bits GP-rel. address.  */
DECL|macro|R_PARISC_LTOFF64
mdefine_line|#define R_PARISC_LTOFF64&t;96&t;/* 64 bits LT-rel. address.  */
DECL|macro|R_PARISC_LTOFF14WR
mdefine_line|#define R_PARISC_LTOFF14WR&t;99&t;/* LT-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_LTOFF14DR
mdefine_line|#define R_PARISC_LTOFF14DR&t;100&t;/* LT-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_LTOFF16F
mdefine_line|#define R_PARISC_LTOFF16F&t;101&t;/* 16 bits LT-rel. address.  */
DECL|macro|R_PARISC_LTOFF16WF
mdefine_line|#define R_PARISC_LTOFF16WF&t;102&t;/* 16 bits LT-rel. address.  */
DECL|macro|R_PARISC_LTOFF16DF
mdefine_line|#define R_PARISC_LTOFF16DF&t;103&t;/* 16 bits LT-rel. address.  */
DECL|macro|R_PARISC_SECREL64
mdefine_line|#define R_PARISC_SECREL64&t;104&t;/* 64 bits section rel. address.  */
DECL|macro|R_PARISC_SEGREL64
mdefine_line|#define R_PARISC_SEGREL64&t;112&t;/* 64 bits segment rel. address.  */
DECL|macro|R_PARISC_PLTOFF14WR
mdefine_line|#define R_PARISC_PLTOFF14WR&t;115&t;/* PLT-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_PLTOFF14DR
mdefine_line|#define R_PARISC_PLTOFF14DR&t;116&t;/* PLT-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_PLTOFF16F
mdefine_line|#define R_PARISC_PLTOFF16F&t;117&t;/* 16 bits LT-rel. address.  */
DECL|macro|R_PARISC_PLTOFF16WF
mdefine_line|#define R_PARISC_PLTOFF16WF&t;118&t;/* 16 bits PLT-rel. address.  */
DECL|macro|R_PARISC_PLTOFF16DF
mdefine_line|#define R_PARISC_PLTOFF16DF&t;119&t;/* 16 bits PLT-rel. address.  */
DECL|macro|R_PARISC_LTOFF_FPTR64
mdefine_line|#define R_PARISC_LTOFF_FPTR64&t;120&t;/* 64 bits LT-rel. function ptr.  */
DECL|macro|R_PARISC_LTOFF_FPTR14WR
mdefine_line|#define R_PARISC_LTOFF_FPTR14WR&t;123&t;/* LT-rel. fct. ptr., right 14 bits. */
DECL|macro|R_PARISC_LTOFF_FPTR14DR
mdefine_line|#define R_PARISC_LTOFF_FPTR14DR&t;124&t;/* LT-rel. fct. ptr., right 14 bits. */
DECL|macro|R_PARISC_LTOFF_FPTR16F
mdefine_line|#define R_PARISC_LTOFF_FPTR16F&t;125&t;/* 16 bits LT-rel. function ptr.  */
DECL|macro|R_PARISC_LTOFF_FPTR16WF
mdefine_line|#define R_PARISC_LTOFF_FPTR16WF&t;126&t;/* 16 bits LT-rel. function ptr.  */
DECL|macro|R_PARISC_LTOFF_FPTR16DF
mdefine_line|#define R_PARISC_LTOFF_FPTR16DF&t;127&t;/* 16 bits LT-rel. function ptr.  */
DECL|macro|R_PARISC_LORESERVE
mdefine_line|#define R_PARISC_LORESERVE&t;128
DECL|macro|R_PARISC_COPY
mdefine_line|#define R_PARISC_COPY&t;&t;128&t;/* Copy relocation.  */
DECL|macro|R_PARISC_IPLT
mdefine_line|#define R_PARISC_IPLT&t;&t;129&t;/* Dynamic reloc, imported PLT */
DECL|macro|R_PARISC_EPLT
mdefine_line|#define R_PARISC_EPLT&t;&t;130&t;/* Dynamic reloc, exported PLT */
DECL|macro|R_PARISC_TPREL32
mdefine_line|#define R_PARISC_TPREL32&t;153&t;/* 32 bits TP-rel. address.  */
DECL|macro|R_PARISC_TPREL21L
mdefine_line|#define R_PARISC_TPREL21L&t;154&t;/* TP-rel. address, left 21 bits.  */
DECL|macro|R_PARISC_TPREL14R
mdefine_line|#define R_PARISC_TPREL14R&t;158&t;/* TP-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_LTOFF_TP21L
mdefine_line|#define R_PARISC_LTOFF_TP21L&t;162&t;/* LT-TP-rel. address, left 21 bits. */
DECL|macro|R_PARISC_LTOFF_TP14R
mdefine_line|#define R_PARISC_LTOFF_TP14R&t;166&t;/* LT-TP-rel. address, right 14 bits.*/
DECL|macro|R_PARISC_LTOFF_TP14F
mdefine_line|#define R_PARISC_LTOFF_TP14F&t;167&t;/* 14 bits LT-TP-rel. address.  */
DECL|macro|R_PARISC_TPREL64
mdefine_line|#define R_PARISC_TPREL64&t;216&t;/* 64 bits TP-rel. address.  */
DECL|macro|R_PARISC_TPREL14WR
mdefine_line|#define R_PARISC_TPREL14WR&t;219&t;/* TP-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_TPREL14DR
mdefine_line|#define R_PARISC_TPREL14DR&t;220&t;/* TP-rel. address, right 14 bits.  */
DECL|macro|R_PARISC_TPREL16F
mdefine_line|#define R_PARISC_TPREL16F&t;221&t;/* 16 bits TP-rel. address.  */
DECL|macro|R_PARISC_TPREL16WF
mdefine_line|#define R_PARISC_TPREL16WF&t;222&t;/* 16 bits TP-rel. address.  */
DECL|macro|R_PARISC_TPREL16DF
mdefine_line|#define R_PARISC_TPREL16DF&t;223&t;/* 16 bits TP-rel. address.  */
DECL|macro|R_PARISC_LTOFF_TP64
mdefine_line|#define R_PARISC_LTOFF_TP64&t;224&t;/* 64 bits LT-TP-rel. address.  */
DECL|macro|R_PARISC_LTOFF_TP14WR
mdefine_line|#define R_PARISC_LTOFF_TP14WR&t;227&t;/* LT-TP-rel. address, right 14 bits.*/
DECL|macro|R_PARISC_LTOFF_TP14DR
mdefine_line|#define R_PARISC_LTOFF_TP14DR&t;228&t;/* LT-TP-rel. address, right 14 bits.*/
DECL|macro|R_PARISC_LTOFF_TP16F
mdefine_line|#define R_PARISC_LTOFF_TP16F&t;229&t;/* 16 bits LT-TP-rel. address.  */
DECL|macro|R_PARISC_LTOFF_TP16WF
mdefine_line|#define R_PARISC_LTOFF_TP16WF&t;230&t;/* 16 bits LT-TP-rel. address.  */
DECL|macro|R_PARISC_LTOFF_TP16DF
mdefine_line|#define R_PARISC_LTOFF_TP16DF&t;231&t;/* 16 bits LT-TP-rel. address.  */
DECL|macro|R_PARISC_HIRESERVE
mdefine_line|#define R_PARISC_HIRESERVE&t;255
multiline_comment|/* Legal values for p_type field of Elf32_Phdr/Elf64_Phdr.  */
DECL|macro|PT_HP_TLS
mdefine_line|#define PT_HP_TLS&t;&t;(PT_LOOS + 0x0)
DECL|macro|PT_HP_CORE_NONE
mdefine_line|#define PT_HP_CORE_NONE&t;&t;(PT_LOOS + 0x1)
DECL|macro|PT_HP_CORE_VERSION
mdefine_line|#define PT_HP_CORE_VERSION&t;(PT_LOOS + 0x2)
DECL|macro|PT_HP_CORE_KERNEL
mdefine_line|#define PT_HP_CORE_KERNEL&t;(PT_LOOS + 0x3)
DECL|macro|PT_HP_CORE_COMM
mdefine_line|#define PT_HP_CORE_COMM&t;&t;(PT_LOOS + 0x4)
DECL|macro|PT_HP_CORE_PROC
mdefine_line|#define PT_HP_CORE_PROC&t;&t;(PT_LOOS + 0x5)
DECL|macro|PT_HP_CORE_LOADABLE
mdefine_line|#define PT_HP_CORE_LOADABLE&t;(PT_LOOS + 0x6)
DECL|macro|PT_HP_CORE_STACK
mdefine_line|#define PT_HP_CORE_STACK&t;(PT_LOOS + 0x7)
DECL|macro|PT_HP_CORE_SHM
mdefine_line|#define PT_HP_CORE_SHM&t;&t;(PT_LOOS + 0x8)
DECL|macro|PT_HP_CORE_MMF
mdefine_line|#define PT_HP_CORE_MMF&t;&t;(PT_LOOS + 0x9)
DECL|macro|PT_HP_PARALLEL
mdefine_line|#define PT_HP_PARALLEL&t;&t;(PT_LOOS + 0x10)
DECL|macro|PT_HP_FASTBIND
mdefine_line|#define PT_HP_FASTBIND&t;&t;(PT_LOOS + 0x11)
DECL|macro|PT_HP_OPT_ANNOT
mdefine_line|#define PT_HP_OPT_ANNOT&t;&t;(PT_LOOS + 0x12)
DECL|macro|PT_HP_HSL_ANNOT
mdefine_line|#define PT_HP_HSL_ANNOT&t;&t;(PT_LOOS + 0x13)
DECL|macro|PT_HP_STACK
mdefine_line|#define PT_HP_STACK&t;&t;(PT_LOOS + 0x14)
DECL|macro|PT_PARISC_ARCHEXT
mdefine_line|#define PT_PARISC_ARCHEXT&t;0x70000000
DECL|macro|PT_PARISC_UNWIND
mdefine_line|#define PT_PARISC_UNWIND&t;0x70000001
multiline_comment|/* Legal values for p_flags field of Elf32_Phdr/Elf64_Phdr.  */
DECL|macro|PF_PARISC_SBP
mdefine_line|#define PF_PARISC_SBP&t;&t;0x08000000
DECL|macro|PF_HP_PAGE_SIZE
mdefine_line|#define PF_HP_PAGE_SIZE&t;&t;0x00100000
DECL|macro|PF_HP_FAR_SHARED
mdefine_line|#define PF_HP_FAR_SHARED&t;0x00200000
DECL|macro|PF_HP_NEAR_SHARED
mdefine_line|#define PF_HP_NEAR_SHARED&t;0x00400000
DECL|macro|PF_HP_CODE
mdefine_line|#define PF_HP_CODE&t;&t;0x01000000
DECL|macro|PF_HP_MODIFY
mdefine_line|#define PF_HP_MODIFY&t;&t;0x02000000
DECL|macro|PF_HP_LAZYSWAP
mdefine_line|#define PF_HP_LAZYSWAP&t;&t;0x04000000
DECL|macro|PF_HP_SBP
mdefine_line|#define PF_HP_SBP&t;&t;0x08000000
multiline_comment|/*&n; * The following definitions are those for 32-bit ELF binaries on a 32-bit&n; * kernel and for 64-bit binaries on a 64-bit kernel.  To run 32-bit binaries&n; * on a 64-bit kernel, arch/parisc64/kernel/binfmt_elf32.c defines these&n; * macros appropriately and then #includes binfmt_elf.c, which then includes&n; * this file.&n; */
macro_line|#ifndef ELF_CLASS
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; *&n; * Note that this header file is used by default in fs/binfmt_elf.c. So&n; * the following macros are for the default case. However, for the 64&n; * bit kernel we also support 32 bit parisc binaries. To do that&n; * arch/parisc64/kernel/binfmt_elf32.c defines its own set of these&n; * macros, and then it includes fs/binfmt_elf.c to provide an alternate&n; * elf binary handler for 32 bit binaries (on the 64 bit kernel).&n; */
macro_line|#ifdef __LP64__
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS       ELFCLASS64
macro_line|#else
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
macro_line|#endif
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (&quot;PARISC&bslash;0&quot; /*+((boot_cpu_data.x86-3)*5) */)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) &bslash;&n;&t;current-&gt;personality = PER_LINUX
macro_line|#endif
multiline_comment|/*&n; * Fill in general registers in a core dump.  This saves pretty&n; * much the same registers as hp-ux, although in a different order.&n; * Registers marked # below are not currently saved in pt_regs, so&n; * we use their current values here.&n; *&n; * &t;gr0..gr31&n; * &t;sr0..sr7&n; * &t;iaoq0..iaoq1&n; * &t;iasq0..iasq1&n; * &t;cr11 (sar)&n; * &t;cr19 (iir)&n; * &t;cr20 (isr)&n; * &t;cr21 (ior)&n; *  #&t;cr22 (ipsw)&n; *  #&t;cr0 (recovery counter)&n; *  #&t;cr24..cr31 (temporary registers)&n; *  #&t;cr8,9,12,13 (protection IDs)&n; *  #&t;cr10 (scr/ccr)&n; *  #&t;cr15 (ext int enable mask)&n; *&n; */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(dst, pt)&t;&bslash;&n;&t;memset(dst, 0, sizeof(dst));&t;/* don&squot;t leak any &quot;random&quot; bits */ &bslash;&n;&t;memcpy(dst + 0, pt-&gt;gr, 32 * sizeof(elf_greg_t)); &bslash;&n;&t;memcpy(dst + 32, pt-&gt;sr, 8 * sizeof(elf_greg_t)); &bslash;&n;&t;memcpy(dst + 40, pt-&gt;iaoq, 2 * sizeof(elf_greg_t)); &bslash;&n;&t;memcpy(dst + 42, pt-&gt;iasq, 2 * sizeof(elf_greg_t)); &bslash;&n;&t;dst[44] = pt-&gt;sar;   dst[45] = pt-&gt;iir; &bslash;&n;&t;dst[46] = pt-&gt;isr;   dst[47] = pt-&gt;ior; &bslash;&n;&t;dst[48] = mfctl(22); dst[49] = mfctl(0); &bslash;&n;&t;dst[50] = mfctl(24); dst[51] = mfctl(25); &bslash;&n;&t;dst[52] = mfctl(26); dst[53] = mfctl(27); &bslash;&n;&t;dst[54] = mfctl(28); dst[55] = mfctl(29); &bslash;&n;&t;dst[56] = mfctl(30); dst[57] = mfctl(31); &bslash;&n;&t;dst[58] = mfctl( 8); dst[59] = mfctl( 9); &bslash;&n;&t;dst[60] = mfctl(12); dst[61] = mfctl(13); &bslash;&n;&t;dst[62] = mfctl(10); dst[63] = mfctl(15);
macro_line|#endif /* ! ELF_CLASS */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG 80&t;/* We only need 64 at present, but leave space&n;&t;&t;&t;   for expansion. */
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG 32
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
r_struct
id|task_struct
suffix:semicolon
r_extern
r_int
id|dump_task_fpu
(paren
r_struct
id|task_struct
op_star
comma
id|elf_fpregset_t
op_star
)paren
suffix:semicolon
DECL|macro|ELF_CORE_COPY_FPREGS
mdefine_line|#define ELF_CORE_COPY_FPREGS(tsk, elf_fpregs) dump_task_fpu(tsk, elf_fpregs)
r_struct
id|pt_regs
suffix:semicolon
multiline_comment|/* forward declaration... */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_PARISC &amp;&amp; (x)-&gt;e_ident[EI_CLASS] == ELF_CLASS)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_PARISC
multiline_comment|/* %r23 is set by ld.so to a pointer to a function which might be &n;   registered using atexit.  This provides a mean for the dynamic&n;   linker to call DT_FINI functions for shared libraries that have&n;   been loaded before the code runs.&n;&n;   So that we can use the same startup file with static executables,&n;   we start programs with a value of 0 to indicate that there is no&n;   such function.  */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr)       _r-&gt;gr[23] = 0
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.&n;&n;   (2 * TASK_SIZE / 3) turns into something undefined when run through a&n;   32 bit preprocessor and in some cases results in the kernel trying to map&n;   ld.so to the kernel virtual base. Use a sane value instead. /Jes &n;  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_UNMAPPED_BASE + 0x01000000)
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This could be done in user space,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;0
multiline_comment|/* (boot_cpu_data.x86_capability) */
macro_line|#endif
eof
