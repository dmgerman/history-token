multiline_comment|/* Copyright (C) 1999,2001&n; *&n; * Author: J.E.J.Bottomley@HansenPartnership.com&n; *&n; * Standard include definitions for the NCR Voyager Interrupt Controller */
multiline_comment|/* The eight CPI vectors.  To activate a CPI, you write a bit mask&n; * corresponding to the processor set to be interrupted into the&n; * relevant register.  That set of CPUs will then be interrupted with&n; * the CPI */
DECL|variable|VIC_CPI_Registers
r_static
r_const
r_int
id|VIC_CPI_Registers
(braket
)braket
op_assign
(brace
l_int|0xFC00
comma
l_int|0xFC01
comma
l_int|0xFC08
comma
l_int|0xFC09
comma
l_int|0xFC10
comma
l_int|0xFC11
comma
l_int|0xFC18
comma
l_int|0xFC19
)brace
suffix:semicolon
DECL|macro|VIC_PROC_WHO_AM_I
mdefine_line|#define VIC_PROC_WHO_AM_I&t;&t;0xfc29
DECL|macro|QUAD_IDENTIFIER
macro_line|#&t;define&t;QUAD_IDENTIFIER&t;&t;0xC0
DECL|macro|EIGHT_SLOT_IDENTIFIER
macro_line|#&t;define  EIGHT_SLOT_IDENTIFIER&t;0xE0
DECL|macro|QIC_EXTENDED_PROCESSOR_SELECT
mdefine_line|#define QIC_EXTENDED_PROCESSOR_SELECT&t;0xFC72
DECL|macro|VIC_CPI_BASE_REGISTER
mdefine_line|#define VIC_CPI_BASE_REGISTER&t;&t;0xFC41
DECL|macro|VIC_PROCESSOR_ID
mdefine_line|#define VIC_PROCESSOR_ID&t;&t;0xFC21
DECL|macro|VIC_CPU_MASQUERADE_ENABLE
macro_line|#&t;define VIC_CPU_MASQUERADE_ENABLE 0x8
DECL|macro|VIC_CLAIM_REGISTER_0
mdefine_line|#define VIC_CLAIM_REGISTER_0&t;&t;0xFC38
DECL|macro|VIC_CLAIM_REGISTER_1
mdefine_line|#define VIC_CLAIM_REGISTER_1&t;&t;0xFC39
DECL|macro|VIC_REDIRECT_REGISTER_0
mdefine_line|#define VIC_REDIRECT_REGISTER_0&t;&t;0xFC60
DECL|macro|VIC_REDIRECT_REGISTER_1
mdefine_line|#define VIC_REDIRECT_REGISTER_1&t;&t;0xFC61
DECL|macro|VIC_PRIORITY_REGISTER
mdefine_line|#define VIC_PRIORITY_REGISTER&t;&t;0xFC20
DECL|macro|VIC_PRIMARY_MC_BASE
mdefine_line|#define VIC_PRIMARY_MC_BASE&t;&t;0xFC48
DECL|macro|VIC_SECONDARY_MC_BASE
mdefine_line|#define VIC_SECONDARY_MC_BASE&t;&t;0xFC49
DECL|macro|QIC_PROCESSOR_ID
mdefine_line|#define QIC_PROCESSOR_ID&t;&t;0xFC71
DECL|macro|QIC_CPUID_ENABLE
macro_line|#&t;define&t;QIC_CPUID_ENABLE&t;0x08
DECL|macro|QIC_VIC_CPI_BASE_REGISTER
mdefine_line|#define QIC_VIC_CPI_BASE_REGISTER&t;0xFC79
DECL|macro|QIC_CPI_BASE_REGISTER
mdefine_line|#define QIC_CPI_BASE_REGISTER&t;&t;0xFC7A
DECL|macro|QIC_MASK_REGISTER0
mdefine_line|#define QIC_MASK_REGISTER0&t;&t;0xFC80
multiline_comment|/* NOTE: these are masked high, enabled low */
DECL|macro|QIC_PERF_TIMER
macro_line|#&t;define QIC_PERF_TIMER&t;&t;0x01
DECL|macro|QIC_LPE
macro_line|#&t;define QIC_LPE&t;&t;&t;0x02
DECL|macro|QIC_SYS_INT
macro_line|#&t;define QIC_SYS_INT&t;&t;0x04
DECL|macro|QIC_CMN_INT
macro_line|#&t;define QIC_CMN_INT&t;&t;0x08
multiline_comment|/* at the moment, just enable CMN_INT, disable SYS_INT */
DECL|macro|QIC_DEFAULT_MASK0
macro_line|#&t;define QIC_DEFAULT_MASK0&t;(~(QIC_CMN_INT /* | VIC_SYS_INT */))
DECL|macro|QIC_MASK_REGISTER1
mdefine_line|#define QIC_MASK_REGISTER1&t;&t;0xFC81
DECL|macro|QIC_BOOT_CPI_MASK
macro_line|#&t;define QIC_BOOT_CPI_MASK&t;0xFE
multiline_comment|/* Enable CPI&squot;s 1-6 inclusive */
DECL|macro|QIC_CPI_ENABLE
macro_line|#&t;define QIC_CPI_ENABLE&t;&t;0x81
DECL|macro|QIC_INTERRUPT_CLEAR0
mdefine_line|#define QIC_INTERRUPT_CLEAR0&t;&t;0xFC8A
DECL|macro|QIC_INTERRUPT_CLEAR1
mdefine_line|#define QIC_INTERRUPT_CLEAR1&t;&t;0xFC8B
multiline_comment|/* this is where we place the CPI vectors */
DECL|macro|VIC_DEFAULT_CPI_BASE
mdefine_line|#define VIC_DEFAULT_CPI_BASE&t;&t;0xC0
multiline_comment|/* this is where we place the QIC CPI vectors */
DECL|macro|QIC_DEFAULT_CPI_BASE
mdefine_line|#define QIC_DEFAULT_CPI_BASE&t;&t;0xD0
DECL|macro|VIC_BOOT_INTERRUPT_MASK
mdefine_line|#define VIC_BOOT_INTERRUPT_MASK&t;&t;0xfe
r_extern
r_void
id|smp_vic_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
eof
