multiline_comment|/* $Id: chafsr.h,v 1.1 2001/03/28 10:56:34 davem Exp $ */
macro_line|#ifndef _SPARC64_CHAFSR_H
DECL|macro|_SPARC64_CHAFSR_H
mdefine_line|#define _SPARC64_CHAFSR_H
multiline_comment|/* Cheetah Asynchronous Fault Status register, ASI=0x4C VA&lt;63:0&gt;=0x0 */
multiline_comment|/* All bits of this register except M_SYNDROME and E_SYNDROME are&n; * read, write 1 to clear.  M_SYNDROME and E_SYNDROME are read-only.&n; */
multiline_comment|/* Multiple errors of the same type have occurred.  This bit is set when&n; * an uncorrectable error or a SW correctable error occurs and the status&n; * bit to report that error is already set.  When multiple errors of&n; * different types are indicated by setting multiple status bits.&n; *&n; * This bit is not set if multiple HW corrected errors with the same&n; * status bit occur, only uncorrectable and SW correctable ones have&n; * this behavior.&n; *&n; * This bit is not set when multiple ECC errors happen within a single&n; * 64-byte system bus transaction.  Only the first ECC error in a 16-byte&n; * subunit will be logged.  All errors in subsequent 16-byte subunits&n; * from the same 64-byte transaction are ignored.&n; */
DECL|macro|CHAFSR_ME
mdefine_line|#define CHAFSR_ME&t;&t;0x0020000000000000
multiline_comment|/* Privileged state error has occurred.  This is a capture of PSTATE.PRIV&n; * at the time the error is detected.&n; */
DECL|macro|CHAFSR_PRIV
mdefine_line|#define CHAFSR_PRIV&t;&t;0x0010000000000000
multiline_comment|/* The following bits 51 (CHAFSR_PERR) to 33 (CHAFSR_CE) are sticky error&n; * bits and record the most recently detected errors.  Bits accumulate&n; * errors that have been detected since the last write to clear the bit.&n; */
multiline_comment|/* System interface protocol error.  The processor asserts its&squot; ERROR&n; * pin when this event occurs and it also logs a specific cause code&n; * into a JTAG scannable flop.&n; */
DECL|macro|CHAFSR_PERR
mdefine_line|#define CHAFSR_PERR&t;&t;0x0008000000000000
multiline_comment|/* Internal processor error.  The processor asserts its&squot; ERROR&n; * pin when this event occurs and it also logs a specific cause code&n; * into a JTAG scannable flop.&n; */
DECL|macro|CHAFSR_IERR
mdefine_line|#define CHAFSR_IERR&t;&t;0x0004000000000000
multiline_comment|/* System request parity error on incoming address */
DECL|macro|CHAFSR_ISAP
mdefine_line|#define CHAFSR_ISAP&t;&t;0x0002000000000000
multiline_comment|/* HW Corrected system bus MTAG ECC error */
DECL|macro|CHAFSR_EMC
mdefine_line|#define CHAFSR_EMC&t;&t;0x0001000000000000
multiline_comment|/* Uncorrectable system bus MTAG ECC error */
DECL|macro|CHAFSR_EMU
mdefine_line|#define CHAFSR_EMU&t;&t;0x0000800000000000
multiline_comment|/* HW Corrected system bus data ECC error for read of interrupt vector */
DECL|macro|CHAFSR_IVC
mdefine_line|#define CHAFSR_IVC&t;&t;0x0000400000000000
multiline_comment|/* Uncorrectable system bus data ECC error for read of interrupt vector */
DECL|macro|CHAFSR_IVU
mdefine_line|#define CHAFSR_IVU&t;&t;0x0000200000000000
multiline_comment|/* Unmappeed error from system bus */
DECL|macro|CHAFSR_TO
mdefine_line|#define CHAFSR_TO&t;&t;0x0000100000000000
multiline_comment|/* Bus error response from system bus */
DECL|macro|CHAFSR_BERR
mdefine_line|#define CHAFSR_BERR&t;&t;0x0000080000000000
multiline_comment|/* SW Correctable E-cache ECC error for instruction fetch or data access&n; * other than block load.&n; */
DECL|macro|CHAFSR_UCC
mdefine_line|#define CHAFSR_UCC&t;&t;0x0000040000000000
multiline_comment|/* Uncorrectable E-cache ECC error for instruction fetch or data access&n; * other than block load.&n; */
DECL|macro|CHAFSR_UCU
mdefine_line|#define CHAFSR_UCU&t;&t;0x0000020000000000
multiline_comment|/* Copyout HW Corrected ECC error */
DECL|macro|CHAFSR_CPC
mdefine_line|#define CHAFSR_CPC&t;&t;0x0000010000000000
multiline_comment|/* Copyout Uncorrectable ECC error */
DECL|macro|CHAFSR_CPU
mdefine_line|#define CHAFSR_CPU&t;&t;0x0000008000000000
multiline_comment|/* HW Corrected ECC error from E-cache for writeback */
DECL|macro|CHAFSR_WDC
mdefine_line|#define CHAFSR_WDC&t;&t;0x0000004000000000
multiline_comment|/* Uncorrectable ECC error from E-cache for writeback */
DECL|macro|CHAFSR_WDU
mdefine_line|#define CHAFSR_WDU&t;&t;0x0000002000000000
multiline_comment|/* HW Corrected ECC error from E-cache for store merge or block load */
DECL|macro|CHAFSR_EDC
mdefine_line|#define CHAFSR_EDC&t;&t;0x0000001000000000
multiline_comment|/* Uncorrectable ECC error from E-cache for store merge or block load */
DECL|macro|CHAFSR_EDU
mdefine_line|#define CHAFSR_EDU&t;&t;0x0000000800000000
multiline_comment|/* Uncorrectable system bus data ECC error for read of memory or I/O */
DECL|macro|CHAFSR_UE
mdefine_line|#define CHAFSR_UE&t;&t;0x0000000400000000
multiline_comment|/* HW Corrected system bus data ECC error for read of memory or I/O */
DECL|macro|CHAFSR_CE
mdefine_line|#define CHAFSR_CE&t;&t;0x0000000200000000
DECL|macro|CHAFSR_ERRORS
mdefine_line|#define CHAFSR_ERRORS&t;&t;(CHAFSR_PERR | CHAFSR_IERR | CHAFSR_ISAP | CHAFSR_EMC | &bslash;&n;&t;&t;&t;&t; CHAFSR_EMU | CHAFSR_IVC | CHAFSR_IVU | CHAFSR_TO | &bslash;&n;&t;&t;&t;&t; CHAFSR_BERR | CHAFSR_UCC | CHAFSR_UCU | CHAFSR_CPC | &bslash;&n;&t;&t;&t;&t; CHAFSR_CPU | CHAFSR_WDC | CHAFSR_WDU | CHAFSR_EDC | &bslash;&n;&t;&t;&t;&t; CHAFSR_EDU | CHAFSR_UE | CHAFSR_CE)
multiline_comment|/* System bus MTAG ECC syndrome.  This field captures the status of the&n; * first occurrence of the highest-priority error according to the M_SYND&n; * overwrite policy.  After the AFSR sticky bit, corresponding to the error&n; * for which the M_SYND is reported, is cleared, the contents of the M_SYND&n; * field will be unchanged by will be unfrozen for further error capture.&n; */
DECL|macro|CHAFSR_M_SYNDROME
mdefine_line|#define CHAFSR_M_SYNDROME&t;0x00000000000f0000
DECL|macro|CHAFSR_M_SYNDROME_SHIFT
mdefine_line|#define CHAFSR_M_SYNDROME_SHIFT&t;16
multiline_comment|/* System bus or E-cache data ECC syndrome.  This field captures the status&n; * of the first occurrence of the highest-priority error according to the&n; * E_SYND overwrite policy.  After the AFSR sticky bit, corresponding to the&n; * error for which the E_SYND is reported, is cleare, the contents of the E_SYND&n; * field will be unchanged but will be unfrozen for further error capture.&n; */
DECL|macro|CHAFSR_E_SYNDROME
mdefine_line|#define CHAFSR_E_SYNDROME&t;0x00000000000001ff
DECL|macro|CHAFSR_E_SYNDROME_SHIFT
mdefine_line|#define CHAFSR_E_SYNDROME_SHIFT&t;0
multiline_comment|/* The AFSR must be explicitly cleared by software, it is not cleared automatically&n; * by a read.  Writes to bits &lt;51:33&gt; with bits set will clear the corresponding&n; * bits in the AFSR.  Bits assosciated with disrupting traps must be cleared before&n; * interrupts are re-enabled to prevent multiple traps for the same error.  I.e.&n; * PSTATE.IE and AFSR bits control delivery of disrupting traps.&n; *&n; * Since there is only one AFAR, when multiple events have been logged by the&n; * bits in the AFSR, at most one of these events will have its status captured&n; * in the AFAR.  The highest priority of those event bits will get AFAR logging.&n; * The AFAR will be unlocked and available to capture the address of another event&n; * as soon as the one bit in AFSR that corresponds to the event logged in AFAR is&n; * cleared.  For example, if AFSR.CE is detected, then AFSR.UE (which overwrites&n; * the AFAR), and AFSR.UE is cleared by not AFSR.CE, then the AFAR will be unlocked&n; * and ready for another event, even though AFSR.CE is still set.  The same rules&n; * also apply to the M_SYNDROME and E_SYNDROME fields of the AFSR.&n; */
multiline_comment|/* Software bit set by linux trap handlers to indicate that the trap was&n; * signalled at %tl &gt;= 1.&n; */
DECL|macro|CHAFSR_TL1
mdefine_line|#define CHAFSR_TL1&t;&t;0x8000000000000000
macro_line|#endif /* _SPARC64_CHAFSR_H */
eof
