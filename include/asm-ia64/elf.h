macro_line|#ifndef _ASM_IA64_ELF_H
DECL|macro|_ASM_IA64_ELF_H
mdefine_line|#define _ASM_IA64_ELF_H
multiline_comment|/*&n; * ELF-specific definitions.&n; *&n; * Copyright (C) 1998-1999, 2002-2004 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_IA_64)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS64
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_IA_64
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
multiline_comment|/* Least-significant four bits of ELF header&squot;s e_flags are OS-specific.  The bits are&n;   interpreted as follows by Linux: */
DECL|macro|EF_IA_64_LINUX_EXECUTABLE_STACK
mdefine_line|#define EF_IA_64_LINUX_EXECUTABLE_STACK&t;0x1&t;/* is stack (&amp; heap) executable by default? */
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;PAGE_SIZE
multiline_comment|/*&n; * This is the location that an ET_DYN program is loaded if exec&squot;ed.&n; * Typical use of this is to invoke &quot;./ld.so someprog&quot; to test out a&n; * new version of the loader.  We need to make sure that it is out of&n; * the way of the program that it will &quot;exec&quot;, and that there is&n; * sufficient room for the brk.&n; */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE&t;&t;(TASK_UNMAPPED_BASE + 0x800000000UL)
DECL|macro|PT_IA_64_UNWIND
mdefine_line|#define PT_IA_64_UNWIND&t;&t;0x70000001
multiline_comment|/* IA-64 relocations: */
DECL|macro|R_IA64_NONE
mdefine_line|#define R_IA64_NONE&t;&t;0x00&t;/* none */
DECL|macro|R_IA64_IMM14
mdefine_line|#define R_IA64_IMM14&t;&t;0x21&t;/* symbol + addend, add imm14 */
DECL|macro|R_IA64_IMM22
mdefine_line|#define R_IA64_IMM22&t;&t;0x22&t;/* symbol + addend, add imm22 */
DECL|macro|R_IA64_IMM64
mdefine_line|#define R_IA64_IMM64&t;&t;0x23&t;/* symbol + addend, mov imm64 */
DECL|macro|R_IA64_DIR32MSB
mdefine_line|#define R_IA64_DIR32MSB&t;&t;0x24&t;/* symbol + addend, data4 MSB */
DECL|macro|R_IA64_DIR32LSB
mdefine_line|#define R_IA64_DIR32LSB&t;&t;0x25&t;/* symbol + addend, data4 LSB */
DECL|macro|R_IA64_DIR64MSB
mdefine_line|#define R_IA64_DIR64MSB&t;&t;0x26&t;/* symbol + addend, data8 MSB */
DECL|macro|R_IA64_DIR64LSB
mdefine_line|#define R_IA64_DIR64LSB&t;&t;0x27&t;/* symbol + addend, data8 LSB */
DECL|macro|R_IA64_GPREL22
mdefine_line|#define R_IA64_GPREL22&t;&t;0x2a&t;/* @gprel(sym+add), add imm22 */
DECL|macro|R_IA64_GPREL64I
mdefine_line|#define R_IA64_GPREL64I&t;&t;0x2b&t;/* @gprel(sym+add), mov imm64 */
DECL|macro|R_IA64_GPREL32MSB
mdefine_line|#define R_IA64_GPREL32MSB&t;0x2c&t;/* @gprel(sym+add), data4 MSB */
DECL|macro|R_IA64_GPREL32LSB
mdefine_line|#define R_IA64_GPREL32LSB&t;0x2d&t;/* @gprel(sym+add), data4 LSB */
DECL|macro|R_IA64_GPREL64MSB
mdefine_line|#define R_IA64_GPREL64MSB&t;0x2e&t;/* @gprel(sym+add), data8 MSB */
DECL|macro|R_IA64_GPREL64LSB
mdefine_line|#define R_IA64_GPREL64LSB&t;0x2f&t;/* @gprel(sym+add), data8 LSB */
DECL|macro|R_IA64_LTOFF22
mdefine_line|#define R_IA64_LTOFF22&t;&t;0x32&t;/* @ltoff(sym+add), add imm22 */
DECL|macro|R_IA64_LTOFF64I
mdefine_line|#define R_IA64_LTOFF64I&t;&t;0x33&t;/* @ltoff(sym+add), mov imm64 */
DECL|macro|R_IA64_PLTOFF22
mdefine_line|#define R_IA64_PLTOFF22&t;&t;0x3a&t;/* @pltoff(sym+add), add imm22 */
DECL|macro|R_IA64_PLTOFF64I
mdefine_line|#define R_IA64_PLTOFF64I&t;0x3b&t;/* @pltoff(sym+add), mov imm64 */
DECL|macro|R_IA64_PLTOFF64MSB
mdefine_line|#define R_IA64_PLTOFF64MSB&t;0x3e&t;/* @pltoff(sym+add), data8 MSB */
DECL|macro|R_IA64_PLTOFF64LSB
mdefine_line|#define R_IA64_PLTOFF64LSB&t;0x3f&t;/* @pltoff(sym+add), data8 LSB */
DECL|macro|R_IA64_FPTR64I
mdefine_line|#define R_IA64_FPTR64I&t;&t;0x43&t;/* @fptr(sym+add), mov imm64 */
DECL|macro|R_IA64_FPTR32MSB
mdefine_line|#define R_IA64_FPTR32MSB&t;0x44&t;/* @fptr(sym+add), data4 MSB */
DECL|macro|R_IA64_FPTR32LSB
mdefine_line|#define R_IA64_FPTR32LSB&t;0x45&t;/* @fptr(sym+add), data4 LSB */
DECL|macro|R_IA64_FPTR64MSB
mdefine_line|#define R_IA64_FPTR64MSB&t;0x46&t;/* @fptr(sym+add), data8 MSB */
DECL|macro|R_IA64_FPTR64LSB
mdefine_line|#define R_IA64_FPTR64LSB&t;0x47&t;/* @fptr(sym+add), data8 LSB */
DECL|macro|R_IA64_PCREL60B
mdefine_line|#define R_IA64_PCREL60B&t;&t;0x48&t;/* @pcrel(sym+add), brl */
DECL|macro|R_IA64_PCREL21B
mdefine_line|#define R_IA64_PCREL21B&t;&t;0x49&t;/* @pcrel(sym+add), ptb, call */
DECL|macro|R_IA64_PCREL21M
mdefine_line|#define R_IA64_PCREL21M&t;&t;0x4a&t;/* @pcrel(sym+add), chk.s */
DECL|macro|R_IA64_PCREL21F
mdefine_line|#define R_IA64_PCREL21F&t;&t;0x4b&t;/* @pcrel(sym+add), fchkf */
DECL|macro|R_IA64_PCREL32MSB
mdefine_line|#define R_IA64_PCREL32MSB&t;0x4c&t;/* @pcrel(sym+add), data4 MSB */
DECL|macro|R_IA64_PCREL32LSB
mdefine_line|#define R_IA64_PCREL32LSB&t;0x4d&t;/* @pcrel(sym+add), data4 LSB */
DECL|macro|R_IA64_PCREL64MSB
mdefine_line|#define R_IA64_PCREL64MSB&t;0x4e&t;/* @pcrel(sym+add), data8 MSB */
DECL|macro|R_IA64_PCREL64LSB
mdefine_line|#define R_IA64_PCREL64LSB&t;0x4f&t;/* @pcrel(sym+add), data8 LSB */
DECL|macro|R_IA64_LTOFF_FPTR22
mdefine_line|#define R_IA64_LTOFF_FPTR22&t;0x52&t;/* @ltoff(@fptr(s+a)), imm22 */
DECL|macro|R_IA64_LTOFF_FPTR64I
mdefine_line|#define R_IA64_LTOFF_FPTR64I&t;0x53&t;/* @ltoff(@fptr(s+a)), imm64 */
DECL|macro|R_IA64_LTOFF_FPTR32MSB
mdefine_line|#define R_IA64_LTOFF_FPTR32MSB&t;0x54&t;/* @ltoff(@fptr(s+a)), 4 MSB */
DECL|macro|R_IA64_LTOFF_FPTR32LSB
mdefine_line|#define R_IA64_LTOFF_FPTR32LSB&t;0x55&t;/* @ltoff(@fptr(s+a)), 4 LSB */
DECL|macro|R_IA64_LTOFF_FPTR64MSB
mdefine_line|#define R_IA64_LTOFF_FPTR64MSB&t;0x56&t;/* @ltoff(@fptr(s+a)), 8 MSB */
DECL|macro|R_IA64_LTOFF_FPTR64LSB
mdefine_line|#define R_IA64_LTOFF_FPTR64LSB&t;0x57&t;/* @ltoff(@fptr(s+a)), 8 LSB */
DECL|macro|R_IA64_SEGREL32MSB
mdefine_line|#define R_IA64_SEGREL32MSB&t;0x5c&t;/* @segrel(sym+add), data4 MSB */
DECL|macro|R_IA64_SEGREL32LSB
mdefine_line|#define R_IA64_SEGREL32LSB&t;0x5d&t;/* @segrel(sym+add), data4 LSB */
DECL|macro|R_IA64_SEGREL64MSB
mdefine_line|#define R_IA64_SEGREL64MSB&t;0x5e&t;/* @segrel(sym+add), data8 MSB */
DECL|macro|R_IA64_SEGREL64LSB
mdefine_line|#define R_IA64_SEGREL64LSB&t;0x5f&t;/* @segrel(sym+add), data8 LSB */
DECL|macro|R_IA64_SECREL32MSB
mdefine_line|#define R_IA64_SECREL32MSB&t;0x64&t;/* @secrel(sym+add), data4 MSB */
DECL|macro|R_IA64_SECREL32LSB
mdefine_line|#define R_IA64_SECREL32LSB&t;0x65&t;/* @secrel(sym+add), data4 LSB */
DECL|macro|R_IA64_SECREL64MSB
mdefine_line|#define R_IA64_SECREL64MSB&t;0x66&t;/* @secrel(sym+add), data8 MSB */
DECL|macro|R_IA64_SECREL64LSB
mdefine_line|#define R_IA64_SECREL64LSB&t;0x67&t;/* @secrel(sym+add), data8 LSB */
DECL|macro|R_IA64_REL32MSB
mdefine_line|#define R_IA64_REL32MSB&t;&t;0x6c&t;/* data 4 + REL */
DECL|macro|R_IA64_REL32LSB
mdefine_line|#define R_IA64_REL32LSB&t;&t;0x6d&t;/* data 4 + REL */
DECL|macro|R_IA64_REL64MSB
mdefine_line|#define R_IA64_REL64MSB&t;&t;0x6e&t;/* data 8 + REL */
DECL|macro|R_IA64_REL64LSB
mdefine_line|#define R_IA64_REL64LSB&t;&t;0x6f&t;/* data 8 + REL */
DECL|macro|R_IA64_LTV32MSB
mdefine_line|#define R_IA64_LTV32MSB&t;&t;0x74&t;/* symbol + addend, data4 MSB */
DECL|macro|R_IA64_LTV32LSB
mdefine_line|#define R_IA64_LTV32LSB&t;&t;0x75&t;/* symbol + addend, data4 LSB */
DECL|macro|R_IA64_LTV64MSB
mdefine_line|#define R_IA64_LTV64MSB&t;&t;0x76&t;/* symbol + addend, data8 MSB */
DECL|macro|R_IA64_LTV64LSB
mdefine_line|#define R_IA64_LTV64LSB&t;&t;0x77&t;/* symbol + addend, data8 LSB */
DECL|macro|R_IA64_PCREL21BI
mdefine_line|#define R_IA64_PCREL21BI&t;0x79&t;/* @pcrel(sym+add), ptb, call */
DECL|macro|R_IA64_PCREL22
mdefine_line|#define R_IA64_PCREL22&t;&t;0x7a&t;/* @pcrel(sym+add), imm22 */
DECL|macro|R_IA64_PCREL64I
mdefine_line|#define R_IA64_PCREL64I&t;&t;0x7b&t;/* @pcrel(sym+add), imm64 */
DECL|macro|R_IA64_IPLTMSB
mdefine_line|#define R_IA64_IPLTMSB&t;&t;0x80&t;/* dynamic reloc, imported PLT, MSB */
DECL|macro|R_IA64_IPLTLSB
mdefine_line|#define R_IA64_IPLTLSB&t;&t;0x81&t;/* dynamic reloc, imported PLT, LSB */
DECL|macro|R_IA64_COPY
mdefine_line|#define R_IA64_COPY&t;&t;0x84&t;/* dynamic reloc, data copy */
DECL|macro|R_IA64_SUB
mdefine_line|#define R_IA64_SUB&t;&t;0x85&t;/* -symbol + addend, add imm22 */
DECL|macro|R_IA64_LTOFF22X
mdefine_line|#define R_IA64_LTOFF22X&t;&t;0x86&t;/* LTOFF22, relaxable.  */
DECL|macro|R_IA64_LDXMOV
mdefine_line|#define R_IA64_LDXMOV&t;&t;0x87&t;/* Use of LTOFF22X.  */
DECL|macro|R_IA64_TPREL14
mdefine_line|#define R_IA64_TPREL14&t;&t;0x91&t;/* @tprel(sym+add), add imm14 */
DECL|macro|R_IA64_TPREL22
mdefine_line|#define R_IA64_TPREL22&t;&t;0x92&t;/* @tprel(sym+add), add imm22 */
DECL|macro|R_IA64_TPREL64I
mdefine_line|#define R_IA64_TPREL64I&t;&t;0x93&t;/* @tprel(sym+add), add imm64 */
DECL|macro|R_IA64_TPREL64MSB
mdefine_line|#define R_IA64_TPREL64MSB&t;0x96&t;/* @tprel(sym+add), data8 MSB */
DECL|macro|R_IA64_TPREL64LSB
mdefine_line|#define R_IA64_TPREL64LSB&t;0x97&t;/* @tprel(sym+add), data8 LSB */
DECL|macro|R_IA64_LTOFF_TPREL22
mdefine_line|#define R_IA64_LTOFF_TPREL22&t;0x9a&t;/* @ltoff(@tprel(s+a)), add imm22 */
DECL|macro|R_IA64_DTPMOD64MSB
mdefine_line|#define R_IA64_DTPMOD64MSB&t;0xa6&t;/* @dtpmod(sym+add), data8 MSB */
DECL|macro|R_IA64_DTPMOD64LSB
mdefine_line|#define R_IA64_DTPMOD64LSB&t;0xa7&t;/* @dtpmod(sym+add), data8 LSB */
DECL|macro|R_IA64_LTOFF_DTPMOD22
mdefine_line|#define R_IA64_LTOFF_DTPMOD22&t;0xaa&t;/* @ltoff(@dtpmod(s+a)), imm22 */
DECL|macro|R_IA64_DTPREL14
mdefine_line|#define R_IA64_DTPREL14&t;&t;0xb1&t;/* @dtprel(sym+add), imm14 */
DECL|macro|R_IA64_DTPREL22
mdefine_line|#define R_IA64_DTPREL22&t;&t;0xb2&t;/* @dtprel(sym+add), imm22 */
DECL|macro|R_IA64_DTPREL64I
mdefine_line|#define R_IA64_DTPREL64I&t;0xb3&t;/* @dtprel(sym+add), imm64 */
DECL|macro|R_IA64_DTPREL32MSB
mdefine_line|#define R_IA64_DTPREL32MSB&t;0xb4&t;/* @dtprel(sym+add), data4 MSB */
DECL|macro|R_IA64_DTPREL32LSB
mdefine_line|#define R_IA64_DTPREL32LSB&t;0xb5&t;/* @dtprel(sym+add), data4 LSB */
DECL|macro|R_IA64_DTPREL64MSB
mdefine_line|#define R_IA64_DTPREL64MSB&t;0xb6&t;/* @dtprel(sym+add), data8 MSB */
DECL|macro|R_IA64_DTPREL64LSB
mdefine_line|#define R_IA64_DTPREL64LSB&t;0xb7&t;/* @dtprel(sym+add), data8 LSB */
DECL|macro|R_IA64_LTOFF_DTPREL22
mdefine_line|#define R_IA64_LTOFF_DTPREL22&t;0xba&t;/* @ltoff(@dtprel(s+a)), imm22 */
multiline_comment|/* IA-64 specific section flags: */
DECL|macro|SHF_IA_64_SHORT
mdefine_line|#define SHF_IA_64_SHORT&t;&t;0x10000000&t;/* section near gp */
multiline_comment|/*&n; * We use (abuse?) this macro to insert the (empty) vm_area that is&n; * used to map the register backing store.  I don&squot;t see any better&n; * place to do this, but we should discuss this with Linus once we can&n; * talk to him...&n; */
r_extern
r_void
id|ia64_init_addr_space
(paren
r_void
)paren
suffix:semicolon
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr)&t;ia64_init_addr_space()
multiline_comment|/* ELF register definitions.  This is needed for core dump support.  */
multiline_comment|/*&n; * elf_gregset_t contains the application-level state in the following order:&n; *&t;r0-r31&n; *&t;NaT bits (for r0-r31; bit N == 1 iff rN is a NaT)&n; *&t;predicate registers (p0-p63)&n; *&t;b0-b7&n; *&t;ip cfm psr&n; *&t;ar.rsc ar.bsp ar.bspstore ar.rnat&n; *&t;ar.ccv ar.unat ar.fpsr ar.pfs ar.lc ar.ec ar.csd ar.ssd&n; */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG&t;128&t;/* we really need just 72 but let&squot;s leave some headroom... */
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG&t;128&t;/* f0 and f1 could be omitted, but so what... */
DECL|typedef|elf_fpxregset_t
r_typedef
r_int
r_int
id|elf_fpxregset_t
suffix:semicolon
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
DECL|typedef|elf_fpreg_t
r_typedef
r_struct
id|ia64_fpreg
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
id|pt_regs
suffix:semicolon
multiline_comment|/* forward declaration... */
r_extern
r_void
id|ia64_elf_core_copy_regs
(paren
r_struct
id|pt_regs
op_star
id|src
comma
id|elf_gregset_t
id|dst
)paren
suffix:semicolon
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(_dest,_regs)&t;ia64_elf_core_copy_regs(_regs, _dest);
multiline_comment|/* This macro yields a bitmask that programs can use to figure out&n;   what instruction set this CPU supports.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP &t;0
multiline_comment|/* This macro yields a string that ld.so will use to load&n;   implementation specific libraries for optimization.  Not terribly&n;   relevant until we have real hardware to play with... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;NULL
multiline_comment|/*&n; * Architecture-neutral AT_ values are in the range 0-17.  Leave some room for more of&n; * them, start the architecture-specific ones at 32.&n; */
DECL|macro|AT_SYSINFO
mdefine_line|#define AT_SYSINFO&t;32
DECL|macro|AT_SYSINFO_EHDR
mdefine_line|#define AT_SYSINFO_EHDR&t;33
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;set_personality(PER_LINUX)
DECL|macro|elf_read_implies_exec
mdefine_line|#define elf_read_implies_exec(ex, executable_stack)&t;&t;&t;&t;&t;&bslash;&n;&t;((executable_stack!=EXSTACK_DISABLE_X) &amp;&amp; ((ex).e_flags &amp; EF_IA_64_LINUX_EXECUTABLE_STACK) != 0)
r_struct
id|task_struct
suffix:semicolon
r_extern
r_int
id|dump_task_regs
c_func
(paren
r_struct
id|task_struct
op_star
comma
id|elf_gregset_t
op_star
)paren
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
DECL|macro|ELF_CORE_COPY_TASK_REGS
mdefine_line|#define ELF_CORE_COPY_TASK_REGS(tsk, elf_gregs) dump_task_regs(tsk, elf_gregs)
DECL|macro|ELF_CORE_COPY_FPREGS
mdefine_line|#define ELF_CORE_COPY_FPREGS(tsk, elf_fpregs) dump_task_fpu(tsk, elf_fpregs)
DECL|macro|GATE_EHDR
mdefine_line|#define GATE_EHDR&t;((const struct elfhdr *) GATE_ADDR)
DECL|macro|ARCH_DLINFO
mdefine_line|#define ARCH_DLINFO&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern char __kernel_syscall_via_epc[];&t;&t;&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_SYSINFO, (unsigned long) __kernel_syscall_via_epc);&t;&bslash;&n;&t;NEW_AUX_ENT(AT_SYSINFO_EHDR, (unsigned long) GATE_EHDR);&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * These macros parameterize elf_core_dump in fs/binfmt_elf.c to write out&n; * extra segments containing the gate DSO contents.  Dumping its&n; * contents makes post-mortem fully interpretable later without matching up&n; * the same kernel and hardware config to see what PC values meant.&n; * Dumping its extra ELF program headers includes all the other information&n; * a debugger needs to easily find how the gate DSO was being used.&n; */
DECL|macro|ELF_CORE_EXTRA_PHDRS
mdefine_line|#define ELF_CORE_EXTRA_PHDRS&t;&t;(GATE_EHDR-&gt;e_phnum)
DECL|macro|ELF_CORE_WRITE_EXTRA_PHDRS
mdefine_line|#define ELF_CORE_WRITE_EXTRA_PHDRS&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const struct elf_phdr *const gate_phdrs =&t;&t;&t;      &bslash;&n;&t;&t;(const struct elf_phdr *) (GATE_ADDR + GATE_EHDR-&gt;e_phoff);   &bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;Elf64_Off ofs = 0;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;for (i = 0; i &lt; GATE_EHDR-&gt;e_phnum; ++i) {&t;&t;&t;&t;&bslash;&n;&t;&t;struct elf_phdr phdr = gate_phdrs[i];&t;&t;&t;      &bslash;&n;&t;&t;if (phdr.p_type == PT_LOAD) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;phdr.p_memsz = PAGE_ALIGN(phdr.p_memsz);&t;      &bslash;&n;&t;&t;&t;phdr.p_filesz = phdr.p_memsz;&t;&t;&t;      &bslash;&n;&t;&t;&t;if (ofs == 0) {&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;&t;ofs = phdr.p_offset = offset;&t;&t;      &bslash;&n;&t;&t;&t;offset += phdr.p_filesz;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;&t;phdr.p_offset = ofs;&t;&t;&t;      &bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;phdr.p_offset += ofs;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;phdr.p_paddr = 0; /* match other core phdrs */&t;&t;&t;&bslash;&n;&t;&t;DUMP_WRITE(&amp;phdr, sizeof(phdr));&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|ELF_CORE_WRITE_EXTRA_DATA
mdefine_line|#define ELF_CORE_WRITE_EXTRA_DATA&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;const struct elf_phdr *const gate_phdrs =&t;&t;&t;      &bslash;&n;&t;&t;(const struct elf_phdr *) (GATE_ADDR + GATE_EHDR-&gt;e_phoff);   &bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (i = 0; i &lt; GATE_EHDR-&gt;e_phnum; ++i) {&t;&t;&t;&bslash;&n;&t;&t;if (gate_phdrs[i].p_type == PT_LOAD) {&t;&t;&t;      &bslash;&n;&t;&t;&t;DUMP_WRITE((void *) gate_phdrs[i].p_vaddr,&t;      &bslash;&n;&t;&t;&t;&t;   PAGE_ALIGN(gate_phdrs[i].p_memsz));&t;      &bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_IA64_ELF_H */
eof
