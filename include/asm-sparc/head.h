multiline_comment|/* $Id: head.h,v 1.39 2000/05/26 22:18:45 ecd Exp $ */
macro_line|#ifndef __SPARC_HEAD_H
DECL|macro|__SPARC_HEAD_H
mdefine_line|#define __SPARC_HEAD_H
DECL|macro|KERNBASE
mdefine_line|#define KERNBASE        0xf0000000  /* First address the kernel will eventually be */
DECL|macro|LOAD_ADDR
mdefine_line|#define LOAD_ADDR       0x4000      /* prom jumps to us here unless this is elf /boot */
DECL|macro|SUN4C_SEGSZ
mdefine_line|#define SUN4C_SEGSZ     (1 &lt;&lt; 18)
DECL|macro|SRMMU_L1_KBASE_OFFSET
mdefine_line|#define SRMMU_L1_KBASE_OFFSET ((KERNBASE&gt;&gt;24)&lt;&lt;2)  /* Used in boot remapping. */
DECL|macro|INTS_ENAB
mdefine_line|#define INTS_ENAB        0x01           /* entry.S uses this. */
DECL|macro|SUN4_PROM_VECTOR
mdefine_line|#define SUN4_PROM_VECTOR 0xFFE81000     /* SUN4 PROM needs to be hardwired */
DECL|macro|WRITE_PAUSE
mdefine_line|#define WRITE_PAUSE      nop; nop; nop; /* Have to do this after %wim/%psr chg */
DECL|macro|NOP_INSN
mdefine_line|#define NOP_INSN         0x01000000     /* Used to patch sparc_save_state */
multiline_comment|/* Here are some trap goodies */
multiline_comment|/* Generic trap entry. */
DECL|macro|TRAP_ENTRY
mdefine_line|#define TRAP_ENTRY(type, label) &bslash;&n;&t;rd %psr, %l0; b label; rd %wim, %l3; nop;
multiline_comment|/* Data/text faults. Defaults to sun4c version at boot time. */
DECL|macro|SPARC_TFAULT
mdefine_line|#define SPARC_TFAULT rd %psr, %l0; rd %wim, %l3; b sun4c_fault; mov 1, %l7;
DECL|macro|SPARC_DFAULT
mdefine_line|#define SPARC_DFAULT rd %psr, %l0; rd %wim, %l3; b sun4c_fault; mov 0, %l7;
DECL|macro|SRMMU_TFAULT
mdefine_line|#define SRMMU_TFAULT rd %psr, %l0; rd %wim, %l3; b C_LABEL(srmmu_fault); mov 1, %l7;
DECL|macro|SRMMU_DFAULT
mdefine_line|#define SRMMU_DFAULT rd %psr, %l0; rd %wim, %l3; b C_LABEL(srmmu_fault); mov 0, %l7;
multiline_comment|/* This is for traps we should NEVER get. */
DECL|macro|BAD_TRAP
mdefine_line|#define BAD_TRAP(num) &bslash;&n;        rd %psr, %l0; mov num, %l7; b bad_trap_handler; rd %wim, %l3;
multiline_comment|/* This is for traps when we want just skip the instruction which caused it */
DECL|macro|SKIP_TRAP
mdefine_line|#define SKIP_TRAP(type, name) &bslash;&n;&t;jmpl %l2, %g0; rett %l2 + 4; nop; nop;
multiline_comment|/* Notice that for the system calls we pull a trick.  We load up a&n; * different pointer to the system call vector table in %l7, but call&n; * the same generic system call low-level entry point.  The trap table&n; * entry sequences are also HyperSparc pipeline friendly ;-)&n; */
multiline_comment|/* Software trap for Linux system calls. */
DECL|macro|LINUX_SYSCALL_TRAP
mdefine_line|#define LINUX_SYSCALL_TRAP &bslash;&n;        sethi %hi(C_LABEL(sys_call_table)), %l7; &bslash;&n;        or %l7, %lo(C_LABEL(sys_call_table)), %l7; &bslash;&n;        b linux_sparc_syscall; &bslash;&n;        rd %psr, %l0;
multiline_comment|/* Software trap for SunOS4.1.x system calls. */
DECL|macro|SUNOS_SYSCALL_TRAP
mdefine_line|#define SUNOS_SYSCALL_TRAP &bslash;&n;        rd %psr, %l0; &bslash;&n;        sethi %hi(C_LABEL(sunos_sys_table)), %l7; &bslash;&n;        b linux_sparc_syscall; &bslash;&n;        or %l7, %lo(C_LABEL(sunos_sys_table)), %l7;
DECL|macro|SUNOS_NO_SYSCALL_TRAP
mdefine_line|#define SUNOS_NO_SYSCALL_TRAP &bslash;&n;        b sunos_syscall; &bslash;&n;        rd %psr, %l0; &bslash;&n;        nop; &bslash;&n;        nop;
multiline_comment|/* Software trap for Slowaris system calls. */
DECL|macro|SOLARIS_SYSCALL_TRAP
mdefine_line|#define SOLARIS_SYSCALL_TRAP &bslash;&n;        b solaris_syscall; &bslash;&n;        rd %psr, %l0; &bslash;&n;        nop; &bslash;&n;        nop;
DECL|macro|INDIRECT_SOLARIS_SYSCALL
mdefine_line|#define INDIRECT_SOLARIS_SYSCALL(x) &bslash;&n;&t;mov x, %g1; &bslash;&n;&t;b solaris_syscall; &bslash;&n;&t;rd %psr, %l0; &bslash;&n;&t;nop;
DECL|macro|BREAKPOINT_TRAP
mdefine_line|#define BREAKPOINT_TRAP &bslash;&n;&t;b breakpoint_trap; &bslash;&n;&t;rd %psr,%l0; &bslash;&n;&t;nop; &bslash;&n;&t;nop;
multiline_comment|/* Software trap for Sparc-netbsd system calls. */
DECL|macro|NETBSD_SYSCALL_TRAP
mdefine_line|#define NETBSD_SYSCALL_TRAP &bslash;&n;        sethi %hi(C_LABEL(sys_call_table)), %l7; &bslash;&n;        or %l7, %lo(C_LABEL(sys_call_table)), %l7; &bslash;&n;        b bsd_syscall; &bslash;&n;        rd %psr, %l0;
multiline_comment|/* The Get Condition Codes software trap for userland. */
DECL|macro|GETCC_TRAP
mdefine_line|#define GETCC_TRAP &bslash;&n;        b getcc_trap_handler; mov %psr, %l0; nop; nop;
multiline_comment|/* The Set Condition Codes software trap for userland. */
DECL|macro|SETCC_TRAP
mdefine_line|#define SETCC_TRAP &bslash;&n;        b setcc_trap_handler; mov %psr, %l0; nop; nop;
multiline_comment|/* The Get PSR software trap for userland. */
DECL|macro|GETPSR_TRAP
mdefine_line|#define GETPSR_TRAP &bslash;&n;&t;mov %psr, %i0; jmp %l2; rett %l2 + 4; nop;
multiline_comment|/* This is for hard interrupts from level 1-14, 15 is non-maskable (nmi) and&n; * gets handled with another macro.&n; */
DECL|macro|TRAP_ENTRY_INTERRUPT
mdefine_line|#define TRAP_ENTRY_INTERRUPT(int_level) &bslash;&n;        mov int_level, %l7; rd %psr, %l0; b real_irq_entry; rd %wim, %l3;
multiline_comment|/* NMI&squot;s (Non Maskable Interrupts) are special, you can&squot;t keep them&n; * from coming in, and basically if you get one, the shows over. ;(&n; * On the sun4c they are usually asynchronous memory errors, on the&n; * the sun4m they could be either due to mem errors or a software&n; * initiated interrupt from the prom/kern on an SMP box saying &quot;I&n; * command you to do CPU tricks, read your mailbox for more info.&quot;&n; */
DECL|macro|NMI_TRAP
mdefine_line|#define NMI_TRAP &bslash;&n;        rd %wim, %l3; b linux_trap_nmi_sun4c; mov %psr, %l0; nop;
multiline_comment|/* Window overflows/underflows are special and we need to try to be as&n; * efficient as possible here....&n; */
DECL|macro|WINDOW_SPILL
mdefine_line|#define WINDOW_SPILL &bslash;&n;        rd %psr, %l0; rd %wim, %l3; b spill_window_entry; andcc %l0, PSR_PS, %g0;
DECL|macro|WINDOW_FILL
mdefine_line|#define WINDOW_FILL &bslash;&n;        rd %psr, %l0; rd %wim, %l3; b fill_window_entry; andcc %l0, PSR_PS, %g0;
macro_line|#endif /* __SPARC_HEAD_H */
eof
