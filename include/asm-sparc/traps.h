multiline_comment|/* $Id: traps.h,v 1.9 1998/03/09 14:04:53 jj Exp $&n; * traps.h:  Format of entries for the Sparc trap table.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_TRAPS_H
DECL|macro|_SPARC_TRAPS_H
mdefine_line|#define _SPARC_TRAPS_H
DECL|macro|NUM_SPARC_TRAPS
mdefine_line|#define NUM_SPARC_TRAPS  255
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* This is for V8 compliant Sparc CPUS */
DECL|struct|tt_entry
r_struct
id|tt_entry
(brace
DECL|member|inst_one
r_int
r_int
id|inst_one
suffix:semicolon
DECL|member|inst_two
r_int
r_int
id|inst_two
suffix:semicolon
DECL|member|inst_three
r_int
r_int
id|inst_three
suffix:semicolon
DECL|member|inst_four
r_int
r_int
id|inst_four
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* We set this to _start in system setup. */
r_extern
r_struct
id|tt_entry
op_star
id|sparc_ttable
suffix:semicolon
DECL|function|get_tbr
r_extern
id|__inline__
r_int
r_int
id|get_tbr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tbr
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%tbr, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tbr
)paren
)paren
suffix:semicolon
r_return
id|tbr
suffix:semicolon
)brace
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* For patching the trap table at boot time, we need to know how to&n; * form various common Sparc instructions.  Thus these macros...&n; */
DECL|macro|SPARC_MOV_CONST_L3
mdefine_line|#define SPARC_MOV_CONST_L3(const) (0xa6102000 | (const&amp;0xfff))
multiline_comment|/* The following assumes that the branch lies before the place we&n; * are branching to.  This is the case for a trap vector...&n; * You have been warned.&n; */
DECL|macro|SPARC_BRANCH
mdefine_line|#define SPARC_BRANCH(dest_addr, inst_addr) &bslash;&n;          (0x10800000 | (((dest_addr-inst_addr)&gt;&gt;2)&amp;0x3fffff))
DECL|macro|SPARC_RD_PSR_L0
mdefine_line|#define SPARC_RD_PSR_L0  (0xa1480000)
DECL|macro|SPARC_RD_WIM_L3
mdefine_line|#define SPARC_RD_WIM_L3  (0xa7500000)
DECL|macro|SPARC_NOP
mdefine_line|#define SPARC_NOP (0x01000000)
multiline_comment|/* Various interesting trap levels. */
multiline_comment|/* First, hardware traps. */
DECL|macro|SP_TRAP_TFLT
mdefine_line|#define SP_TRAP_TFLT    0x1          /* Text fault */
DECL|macro|SP_TRAP_II
mdefine_line|#define SP_TRAP_II      0x2          /* Illegal Instruction */
DECL|macro|SP_TRAP_PI
mdefine_line|#define SP_TRAP_PI      0x3          /* Privileged Instruction */
DECL|macro|SP_TRAP_FPD
mdefine_line|#define SP_TRAP_FPD     0x4          /* Floating Point Disabled */
DECL|macro|SP_TRAP_WOVF
mdefine_line|#define SP_TRAP_WOVF    0x5          /* Window Overflow */
DECL|macro|SP_TRAP_WUNF
mdefine_line|#define SP_TRAP_WUNF    0x6          /* Window Underflow */
DECL|macro|SP_TRAP_MNA
mdefine_line|#define SP_TRAP_MNA     0x7          /* Memory Address Unaligned */
DECL|macro|SP_TRAP_FPE
mdefine_line|#define SP_TRAP_FPE     0x8          /* Floating Point Exception */
DECL|macro|SP_TRAP_DFLT
mdefine_line|#define SP_TRAP_DFLT    0x9          /* Data Fault */
DECL|macro|SP_TRAP_TOF
mdefine_line|#define SP_TRAP_TOF     0xa          /* Tag Overflow */
DECL|macro|SP_TRAP_WDOG
mdefine_line|#define SP_TRAP_WDOG    0xb          /* Watchpoint Detected */
DECL|macro|SP_TRAP_IRQ1
mdefine_line|#define SP_TRAP_IRQ1    0x11         /* IRQ level 1 */
DECL|macro|SP_TRAP_IRQ2
mdefine_line|#define SP_TRAP_IRQ2    0x12         /* IRQ level 2 */
DECL|macro|SP_TRAP_IRQ3
mdefine_line|#define SP_TRAP_IRQ3    0x13         /* IRQ level 3 */
DECL|macro|SP_TRAP_IRQ4
mdefine_line|#define SP_TRAP_IRQ4    0x14         /* IRQ level 4 */
DECL|macro|SP_TRAP_IRQ5
mdefine_line|#define SP_TRAP_IRQ5    0x15         /* IRQ level 5 */
DECL|macro|SP_TRAP_IRQ6
mdefine_line|#define SP_TRAP_IRQ6    0x16         /* IRQ level 6 */
DECL|macro|SP_TRAP_IRQ7
mdefine_line|#define SP_TRAP_IRQ7    0x17         /* IRQ level 7 */
DECL|macro|SP_TRAP_IRQ8
mdefine_line|#define SP_TRAP_IRQ8    0x18         /* IRQ level 8 */
DECL|macro|SP_TRAP_IRQ9
mdefine_line|#define SP_TRAP_IRQ9    0x19         /* IRQ level 9 */
DECL|macro|SP_TRAP_IRQ10
mdefine_line|#define SP_TRAP_IRQ10   0x1a         /* IRQ level 10 */
DECL|macro|SP_TRAP_IRQ11
mdefine_line|#define SP_TRAP_IRQ11   0x1b         /* IRQ level 11 */
DECL|macro|SP_TRAP_IRQ12
mdefine_line|#define SP_TRAP_IRQ12   0x1c         /* IRQ level 12 */
DECL|macro|SP_TRAP_IRQ13
mdefine_line|#define SP_TRAP_IRQ13   0x1d         /* IRQ level 13 */
DECL|macro|SP_TRAP_IRQ14
mdefine_line|#define SP_TRAP_IRQ14   0x1e         /* IRQ level 14 */
DECL|macro|SP_TRAP_IRQ15
mdefine_line|#define SP_TRAP_IRQ15   0x1f         /* IRQ level 15 Non-maskable */
DECL|macro|SP_TRAP_RACC
mdefine_line|#define SP_TRAP_RACC    0x20         /* Register Access Error ??? */
DECL|macro|SP_TRAP_IACC
mdefine_line|#define SP_TRAP_IACC    0x21         /* Instruction Access Error */
DECL|macro|SP_TRAP_CPDIS
mdefine_line|#define SP_TRAP_CPDIS   0x24         /* Co-Processor Disabled */
DECL|macro|SP_TRAP_BADFL
mdefine_line|#define SP_TRAP_BADFL   0x25         /* Unimplemented Flush Instruction */
DECL|macro|SP_TRAP_CPEXP
mdefine_line|#define SP_TRAP_CPEXP   0x28         /* Co-Processor Exception */
DECL|macro|SP_TRAP_DACC
mdefine_line|#define SP_TRAP_DACC    0x29         /* Data Access Error */
DECL|macro|SP_TRAP_DIVZ
mdefine_line|#define SP_TRAP_DIVZ    0x2a         /* Divide By Zero */
DECL|macro|SP_TRAP_DSTORE
mdefine_line|#define SP_TRAP_DSTORE  0x2b         /* Data Store Error ??? */
DECL|macro|SP_TRAP_DMM
mdefine_line|#define SP_TRAP_DMM     0x2c         /* Data Access MMU Miss ??? */
DECL|macro|SP_TRAP_IMM
mdefine_line|#define SP_TRAP_IMM     0x3c         /* Instruction Access MMU Miss ??? */
multiline_comment|/* Now the Software Traps... */
DECL|macro|SP_TRAP_SUNOS
mdefine_line|#define SP_TRAP_SUNOS   0x80         /* SunOS System Call */
DECL|macro|SP_TRAP_SBPT
mdefine_line|#define SP_TRAP_SBPT    0x81         /* Software Breakpoint */
DECL|macro|SP_TRAP_SDIVZ
mdefine_line|#define SP_TRAP_SDIVZ   0x82         /* Software Divide-by-Zero trap */
DECL|macro|SP_TRAP_FWIN
mdefine_line|#define SP_TRAP_FWIN    0x83         /* Flush Windows */
DECL|macro|SP_TRAP_CWIN
mdefine_line|#define SP_TRAP_CWIN    0x84         /* Clean Windows */
DECL|macro|SP_TRAP_RCHK
mdefine_line|#define SP_TRAP_RCHK    0x85         /* Range Check */
DECL|macro|SP_TRAP_FUNA
mdefine_line|#define SP_TRAP_FUNA    0x86         /* Fix Unaligned Access */
DECL|macro|SP_TRAP_IOWFL
mdefine_line|#define SP_TRAP_IOWFL   0x87         /* Integer Overflow */
DECL|macro|SP_TRAP_SOLARIS
mdefine_line|#define SP_TRAP_SOLARIS 0x88         /* Solaris System Call */
DECL|macro|SP_TRAP_NETBSD
mdefine_line|#define SP_TRAP_NETBSD  0x89         /* NetBSD System Call */
DECL|macro|SP_TRAP_LINUX
mdefine_line|#define SP_TRAP_LINUX   0x90         /* Linux System Call */
multiline_comment|/* Names used for compatibility with SunOS */
DECL|macro|ST_SYSCALL
mdefine_line|#define ST_SYSCALL              0x00
DECL|macro|ST_BREAKPOINT
mdefine_line|#define ST_BREAKPOINT           0x01
DECL|macro|ST_DIV0
mdefine_line|#define ST_DIV0                 0x02
DECL|macro|ST_FLUSH_WINDOWS
mdefine_line|#define ST_FLUSH_WINDOWS        0x03
DECL|macro|ST_CLEAN_WINDOWS
mdefine_line|#define ST_CLEAN_WINDOWS        0x04
DECL|macro|ST_RANGE_CHECK
mdefine_line|#define ST_RANGE_CHECK          0x05
DECL|macro|ST_FIX_ALIGN
mdefine_line|#define ST_FIX_ALIGN            0x06
DECL|macro|ST_INT_OVERFLOW
mdefine_line|#define ST_INT_OVERFLOW         0x07
multiline_comment|/* Special traps... */
DECL|macro|SP_TRAP_KBPT1
mdefine_line|#define SP_TRAP_KBPT1   0xfe         /* KADB/PROM Breakpoint one */
DECL|macro|SP_TRAP_KBPT2
mdefine_line|#define SP_TRAP_KBPT2   0xff         /* KADB/PROM Breakpoint two */
multiline_comment|/* Handy Macros */
multiline_comment|/* Is this a trap we never expect to get? */
DECL|macro|BAD_TRAP_P
mdefine_line|#define BAD_TRAP_P(level) &bslash;&n;        ((level &gt; SP_TRAP_WDOG &amp;&amp; level &lt; SP_TRAP_IRQ1) || &bslash;&n;&t; (level &gt; SP_TRAP_IACC &amp;&amp; level &lt; SP_TRAP_CPDIS) || &bslash;&n;&t; (level &gt; SP_TRAP_BADFL &amp;&amp; level &lt; SP_TRAP_CPEXP) || &bslash;&n;&t; (level &gt; SP_TRAP_DMM &amp;&amp; level &lt; SP_TRAP_IMM) || &bslash;&n;&t; (level &gt; SP_TRAP_IMM &amp;&amp; level &lt; SP_TRAP_SUNOS) || &bslash;&n;&t; (level &gt; SP_TRAP_LINUX &amp;&amp; level &lt; SP_TRAP_KBPT1))
multiline_comment|/* Is this a Hardware trap? */
DECL|macro|HW_TRAP_P
mdefine_line|#define HW_TRAP_P(level) ((level &gt; 0) &amp;&amp; (level &lt; SP_TRAP_SUNOS))
multiline_comment|/* Is this a Software trap? */
DECL|macro|SW_TRAP_P
mdefine_line|#define SW_TRAP_P(level) ((level &gt;= SP_TRAP_SUNOS) &amp;&amp; (level &lt;= SP_TRAP_KBPT2))
multiline_comment|/* Is this a system call for some OS we know about? */
DECL|macro|SCALL_TRAP_P
mdefine_line|#define SCALL_TRAP_P(level) ((level == SP_TRAP_SUNOS) || &bslash;&n;&t;&t;&t;     (level == SP_TRAP_SOLARIS) || &bslash;&n;&t;&t;&t;     (level == SP_TRAP_NETBSD) || &bslash;&n;&t;&t;&t;     (level == SP_TRAP_LINUX))
macro_line|#endif /* !(_SPARC_TRAPS_H) */
eof
