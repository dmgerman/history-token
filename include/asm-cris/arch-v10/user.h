macro_line|#ifndef __ASM_CRIS_ARCH_USER_H
DECL|macro|__ASM_CRIS_ARCH_USER_H
mdefine_line|#define __ASM_CRIS_ARCH_USER_H
multiline_comment|/* User mode registers, used for core dumps. In order to keep ELF_NGREG&n;   sensible we let all registers be 32 bits. The csr registers are included&n;   for future use. */
DECL|struct|user_regs_struct
r_struct
id|user_regs_struct
(brace
DECL|member|r0
r_int
r_int
id|r0
suffix:semicolon
multiline_comment|/* General registers. */
DECL|member|r1
r_int
r_int
id|r1
suffix:semicolon
DECL|member|r2
r_int
r_int
id|r2
suffix:semicolon
DECL|member|r3
r_int
r_int
id|r3
suffix:semicolon
DECL|member|r4
r_int
r_int
id|r4
suffix:semicolon
DECL|member|r5
r_int
r_int
id|r5
suffix:semicolon
DECL|member|r6
r_int
r_int
id|r6
suffix:semicolon
DECL|member|r7
r_int
r_int
id|r7
suffix:semicolon
DECL|member|r8
r_int
r_int
id|r8
suffix:semicolon
DECL|member|r9
r_int
r_int
id|r9
suffix:semicolon
DECL|member|r10
r_int
r_int
id|r10
suffix:semicolon
DECL|member|r11
r_int
r_int
id|r11
suffix:semicolon
DECL|member|r12
r_int
r_int
id|r12
suffix:semicolon
DECL|member|r13
r_int
r_int
id|r13
suffix:semicolon
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
multiline_comment|/* Stack pointer. */
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* Program counter. */
DECL|member|p0
r_int
r_int
id|p0
suffix:semicolon
multiline_comment|/* Constant zero (only 8 bits). */
DECL|member|vr
r_int
r_int
id|vr
suffix:semicolon
multiline_comment|/* Version register (only 8 bits). */
DECL|member|p2
r_int
r_int
id|p2
suffix:semicolon
multiline_comment|/* Reserved. */
DECL|member|p3
r_int
r_int
id|p3
suffix:semicolon
multiline_comment|/* Reserved. */
DECL|member|p4
r_int
r_int
id|p4
suffix:semicolon
multiline_comment|/* Constant zero (only 16 bits). */
DECL|member|ccr
r_int
r_int
id|ccr
suffix:semicolon
multiline_comment|/* Condition code register (only 16 bits). */
DECL|member|p6
r_int
r_int
id|p6
suffix:semicolon
multiline_comment|/* Reserved. */
DECL|member|mof
r_int
r_int
id|mof
suffix:semicolon
multiline_comment|/* Multiply overflow register. */
DECL|member|p8
r_int
r_int
id|p8
suffix:semicolon
multiline_comment|/* Constant zero. */
DECL|member|ibr
r_int
r_int
id|ibr
suffix:semicolon
multiline_comment|/* Not accessible. */
DECL|member|irp
r_int
r_int
id|irp
suffix:semicolon
multiline_comment|/* Not accessible. */
DECL|member|srp
r_int
r_int
id|srp
suffix:semicolon
multiline_comment|/* Subroutine return pointer. */
DECL|member|bar
r_int
r_int
id|bar
suffix:semicolon
multiline_comment|/* Not accessible. */
DECL|member|dccr
r_int
r_int
id|dccr
suffix:semicolon
multiline_comment|/* Dword condition code register. */
DECL|member|brp
r_int
r_int
id|brp
suffix:semicolon
multiline_comment|/* Not accessible. */
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
multiline_comment|/* User-mode stack pointer. Same as sp when &n;                                   in user mode. */
DECL|member|csrinstr
r_int
r_int
id|csrinstr
suffix:semicolon
multiline_comment|/* Internal status registers. */
DECL|member|csraddr
r_int
r_int
id|csraddr
suffix:semicolon
DECL|member|csrdata
r_int
r_int
id|csrdata
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
