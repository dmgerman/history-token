multiline_comment|/* $Id: chafsr.h,v 1.1 2001/03/28 10:56:34 davem Exp $ */
macro_line|#ifndef _SPARC64_CHAFSR_H
DECL|macro|_SPARC64_CHAFSR_H
mdefine_line|#define _SPARC64_CHAFSR_H
multiline_comment|/* Cheetah Asynchronous Fault Status register, ASI=0x4C VA&lt;63:0&gt;=0x0 */
multiline_comment|/* Comments indicate which processor variants on which the bit definition&n; * is valid.  Codes are:&n; * ch&t;--&gt;&t;cheetah&n; * ch+&t;--&gt;&t;cheetah plus&n; * jp&t;--&gt;&t;jalapeno&n; */
multiline_comment|/* All bits of this register except M_SYNDROME and E_SYNDROME are&n; * read, write 1 to clear.  M_SYNDROME and E_SYNDROME are read-only.&n; */
multiline_comment|/* Software bit set by linux trap handlers to indicate that the trap was&n; * signalled at %tl &gt;= 1.&n; */
DECL|macro|CHAFSR_TL1
mdefine_line|#define CHAFSR_TL1&t;&t;(1UL &lt;&lt; 63UL) /* n/a */
multiline_comment|/* Unmapped error from system bus for prefetch queue or&n; * store queue read operation&n; */
DECL|macro|CHPAFSR_DTO
mdefine_line|#define CHPAFSR_DTO&t;&t;(1UL &lt;&lt; 59UL) /* ch+ */
multiline_comment|/* Bus error from system bus for prefetch queue or store queue&n; * read operation&n; */
DECL|macro|CHPAFSR_DBERR
mdefine_line|#define CHPAFSR_DBERR&t;&t;(1UL &lt;&lt; 58UL) /* ch+ */
multiline_comment|/* Hardware corrected E-cache Tag ECC error */
DECL|macro|CHPAFSR_THCE
mdefine_line|#define CHPAFSR_THCE&t;&t;(1UL &lt;&lt; 57UL) /* ch+ */
multiline_comment|/* System interface protocol error, hw timeout caused */
DECL|macro|JPAFSR_JETO
mdefine_line|#define JPAFSR_JETO&t;&t;(1UL &lt;&lt; 57UL) /* jp */
multiline_comment|/* SW handled correctable E-cache Tag ECC error */
DECL|macro|CHPAFSR_TSCE
mdefine_line|#define CHPAFSR_TSCE&t;&t;(1UL &lt;&lt; 56UL) /* ch+ */
multiline_comment|/* Parity error on system snoop results */
DECL|macro|JPAFSR_SCE
mdefine_line|#define JPAFSR_SCE&t;&t;(1UL &lt;&lt; 56UL) /* jp */
multiline_comment|/* Uncorrectable E-cache Tag ECC error */
DECL|macro|CHPAFSR_TUE
mdefine_line|#define CHPAFSR_TUE&t;&t;(1UL &lt;&lt; 55UL) /* ch+ */
multiline_comment|/* System interface protocol error, illegal command detected */
DECL|macro|JPAFSR_JEIC
mdefine_line|#define JPAFSR_JEIC&t;&t;(1UL &lt;&lt; 55UL) /* jp */
multiline_comment|/* Uncorrectable system bus data ECC error due to prefetch&n; * or store fill request&n; */
DECL|macro|CHPAFSR_DUE
mdefine_line|#define CHPAFSR_DUE&t;&t;(1UL &lt;&lt; 54UL) /* ch+ */
multiline_comment|/* System interface protocol error, illegal ADTYPE detected */
DECL|macro|JPAFSR_JEIT
mdefine_line|#define JPAFSR_JEIT&t;&t;(1UL &lt;&lt; 54UL) /* jp */
multiline_comment|/* Multiple errors of the same type have occurred.  This bit is set when&n; * an uncorrectable error or a SW correctable error occurs and the status&n; * bit to report that error is already set.  When multiple errors of&n; * different types are indicated by setting multiple status bits.&n; *&n; * This bit is not set if multiple HW corrected errors with the same&n; * status bit occur, only uncorrectable and SW correctable ones have&n; * this behavior.&n; *&n; * This bit is not set when multiple ECC errors happen within a single&n; * 64-byte system bus transaction.  Only the first ECC error in a 16-byte&n; * subunit will be logged.  All errors in subsequent 16-byte subunits&n; * from the same 64-byte transaction are ignored.&n; */
DECL|macro|CHAFSR_ME
mdefine_line|#define CHAFSR_ME&t;&t;(1UL &lt;&lt; 53UL) /* ch,ch+,jp */
multiline_comment|/* Privileged state error has occurred.  This is a capture of PSTATE.PRIV&n; * at the time the error is detected.&n; */
DECL|macro|CHAFSR_PRIV
mdefine_line|#define CHAFSR_PRIV&t;&t;(1UL &lt;&lt; 52UL) /* ch,ch+,jp */
multiline_comment|/* The following bits 51 (CHAFSR_PERR) to 33 (CHAFSR_CE) are sticky error&n; * bits and record the most recently detected errors.  Bits accumulate&n; * errors that have been detected since the last write to clear the bit.&n; */
multiline_comment|/* System interface protocol error.  The processor asserts its&squot; ERROR&n; * pin when this event occurs and it also logs a specific cause code&n; * into a JTAG scannable flop.&n; */
DECL|macro|CHAFSR_PERR
mdefine_line|#define CHAFSR_PERR&t;&t;(1UL &lt;&lt; 51UL) /* ch,ch+,jp */
multiline_comment|/* Internal processor error.  The processor asserts its&squot; ERROR&n; * pin when this event occurs and it also logs a specific cause code&n; * into a JTAG scannable flop.&n; */
DECL|macro|CHAFSR_IERR
mdefine_line|#define CHAFSR_IERR&t;&t;(1UL &lt;&lt; 50UL) /* ch,ch+,jp */
multiline_comment|/* System request parity error on incoming address */
DECL|macro|CHAFSR_ISAP
mdefine_line|#define CHAFSR_ISAP&t;&t;(1UL &lt;&lt; 49UL) /* ch,ch+,jp */
multiline_comment|/* HW Corrected system bus MTAG ECC error */
DECL|macro|CHAFSR_EMC
mdefine_line|#define CHAFSR_EMC&t;&t;(1UL &lt;&lt; 48UL) /* ch,ch+ */
multiline_comment|/* Parity error on L2 cache tag SRAM */
DECL|macro|JPAFSR_ETP
mdefine_line|#define JPAFSR_ETP&t;&t;(1UL &lt;&lt; 48UL) /* jp */
multiline_comment|/* Uncorrectable system bus MTAG ECC error */
DECL|macro|CHAFSR_EMU
mdefine_line|#define CHAFSR_EMU&t;&t;(1UL &lt;&lt; 47UL) /* ch,ch+ */
multiline_comment|/* Out of range memory error has occurred */
DECL|macro|JPAFSR_OM
mdefine_line|#define JPAFSR_OM&t;&t;(1UL &lt;&lt; 47UL) /* jp */
multiline_comment|/* HW Corrected system bus data ECC error for read of interrupt vector */
DECL|macro|CHAFSR_IVC
mdefine_line|#define CHAFSR_IVC&t;&t;(1UL &lt;&lt; 46UL) /* ch,ch+ */
multiline_comment|/* Error due to unsupported store */
DECL|macro|JPAFSR_UMS
mdefine_line|#define JPAFSR_UMS&t;&t;(1UL &lt;&lt; 46UL) /* jp */
multiline_comment|/* Uncorrectable system bus data ECC error for read of interrupt vector */
DECL|macro|CHAFSR_IVU
mdefine_line|#define CHAFSR_IVU&t;&t;(1UL &lt;&lt; 45UL) /* ch,ch+,jp */
multiline_comment|/* Unmapped error from system bus */
DECL|macro|CHAFSR_TO
mdefine_line|#define CHAFSR_TO&t;&t;(1UL &lt;&lt; 44UL) /* ch,ch+,jp */
multiline_comment|/* Bus error response from system bus */
DECL|macro|CHAFSR_BERR
mdefine_line|#define CHAFSR_BERR&t;&t;(1UL &lt;&lt; 43UL) /* ch,ch+,jp */
multiline_comment|/* SW Correctable E-cache ECC error for instruction fetch or data access&n; * other than block load.&n; */
DECL|macro|CHAFSR_UCC
mdefine_line|#define CHAFSR_UCC&t;&t;(1UL &lt;&lt; 42UL) /* ch,ch+,jp */
multiline_comment|/* Uncorrectable E-cache ECC error for instruction fetch or data access&n; * other than block load.&n; */
DECL|macro|CHAFSR_UCU
mdefine_line|#define CHAFSR_UCU&t;&t;(1UL &lt;&lt; 41UL) /* ch,ch+,jp */
multiline_comment|/* Copyout HW Corrected ECC error */
DECL|macro|CHAFSR_CPC
mdefine_line|#define CHAFSR_CPC&t;&t;(1UL &lt;&lt; 40UL) /* ch,ch+,jp */
multiline_comment|/* Copyout Uncorrectable ECC error */
DECL|macro|CHAFSR_CPU
mdefine_line|#define CHAFSR_CPU&t;&t;(1UL &lt;&lt; 39UL) /* ch,ch+,jp */
multiline_comment|/* HW Corrected ECC error from E-cache for writeback */
DECL|macro|CHAFSR_WDC
mdefine_line|#define CHAFSR_WDC&t;&t;(1UL &lt;&lt; 38UL) /* ch,ch+,jp */
multiline_comment|/* Uncorrectable ECC error from E-cache for writeback */
DECL|macro|CHAFSR_WDU
mdefine_line|#define CHAFSR_WDU&t;&t;(1UL &lt;&lt; 37UL) /* ch,ch+,jp */
multiline_comment|/* HW Corrected ECC error from E-cache for store merge or block load */
DECL|macro|CHAFSR_EDC
mdefine_line|#define CHAFSR_EDC&t;&t;(1UL &lt;&lt; 36UL) /* ch,ch+,jp */
multiline_comment|/* Uncorrectable ECC error from E-cache for store merge or block load */
DECL|macro|CHAFSR_EDU
mdefine_line|#define CHAFSR_EDU&t;&t;(1UL &lt;&lt; 35UL) /* ch,ch+,jp */
multiline_comment|/* Uncorrectable system bus data ECC error for read of memory or I/O */
DECL|macro|CHAFSR_UE
mdefine_line|#define CHAFSR_UE&t;&t;(1UL &lt;&lt; 34UL) /* ch,ch+,jp */
multiline_comment|/* HW Corrected system bus data ECC error for read of memory or I/O */
DECL|macro|CHAFSR_CE
mdefine_line|#define CHAFSR_CE&t;&t;(1UL &lt;&lt; 33UL) /* ch,ch+,jp */
multiline_comment|/* Uncorrectable ECC error from remote cache/memory */
DECL|macro|JPAFSR_RUE
mdefine_line|#define JPAFSR_RUE&t;&t;(1UL &lt;&lt; 32UL) /* jp */
multiline_comment|/* Correctable ECC error from remote cache/memory */
DECL|macro|JPAFSR_RCE
mdefine_line|#define JPAFSR_RCE&t;&t;(1UL &lt;&lt; 31UL) /* jp */
multiline_comment|/* JBUS parity error on returned read data */
DECL|macro|JPAFSR_BP
mdefine_line|#define JPAFSR_BP&t;&t;(1UL &lt;&lt; 30UL) /* jp */
multiline_comment|/* JBUS parity error on data for writeback or block store */
DECL|macro|JPAFSR_WBP
mdefine_line|#define JPAFSR_WBP&t;&t;(1UL &lt;&lt; 29UL) /* jp */
multiline_comment|/* Foreign read to DRAM incurring correctable ECC error */
DECL|macro|JPAFSR_FRC
mdefine_line|#define JPAFSR_FRC&t;&t;(1UL &lt;&lt; 28UL) /* jp */
multiline_comment|/* Foreign read to DRAM incurring uncorrectable ECC error */
DECL|macro|JPAFSR_FRU
mdefine_line|#define JPAFSR_FRU&t;&t;(1UL &lt;&lt; 27UL) /* jp */
DECL|macro|CHAFSR_ERRORS
mdefine_line|#define CHAFSR_ERRORS&t;&t;(CHAFSR_PERR | CHAFSR_IERR | CHAFSR_ISAP | CHAFSR_EMC | &bslash;&n;&t;&t;&t;&t; CHAFSR_EMU | CHAFSR_IVC | CHAFSR_IVU | CHAFSR_TO | &bslash;&n;&t;&t;&t;&t; CHAFSR_BERR | CHAFSR_UCC | CHAFSR_UCU | CHAFSR_CPC | &bslash;&n;&t;&t;&t;&t; CHAFSR_CPU | CHAFSR_WDC | CHAFSR_WDU | CHAFSR_EDC | &bslash;&n;&t;&t;&t;&t; CHAFSR_EDU | CHAFSR_UE | CHAFSR_CE)
DECL|macro|CHPAFSR_ERRORS
mdefine_line|#define CHPAFSR_ERRORS&t;&t;(CHPAFSR_DTO | CHPAFSR_DBERR | CHPAFSR_THCE | &bslash;&n;&t;&t;&t;&t; CHPAFSR_TSCE | CHPAFSR_TUE | CHPAFSR_DUE | &bslash;&n;&t;&t;&t;&t; CHAFSR_PERR | CHAFSR_IERR | CHAFSR_ISAP | CHAFSR_EMC | &bslash;&n;&t;&t;&t;&t; CHAFSR_EMU | CHAFSR_IVC | CHAFSR_IVU | CHAFSR_TO | &bslash;&n;&t;&t;&t;&t; CHAFSR_BERR | CHAFSR_UCC | CHAFSR_UCU | CHAFSR_CPC | &bslash;&n;&t;&t;&t;&t; CHAFSR_CPU | CHAFSR_WDC | CHAFSR_WDU | CHAFSR_EDC | &bslash;&n;&t;&t;&t;&t; CHAFSR_EDU | CHAFSR_UE | CHAFSR_CE)
DECL|macro|JPAFSR_ERRORS
mdefine_line|#define JPAFSR_ERRORS&t;&t;(JPAFSR_JETO | JPAFSR_SCE | JPAFSR_JEIC | &bslash;&n;&t;&t;&t;&t; JPAFSR_JEIT | CHAFSR_PERR | CHAFSR_IERR | &bslash;&n;&t;&t;&t;&t; CHAFSR_ISAP | JPAFSR_ETP | JPAFSR_OM | &bslash;&n;&t;&t;&t;&t; JPAFSR_UMS | CHAFSR_IVU | CHAFSR_TO | &bslash;&n;&t;&t;&t;&t; CHAFSR_BERR | CHAFSR_UCC | CHAFSR_UCU | &bslash;&n;&t;&t;&t;&t; CHAFSR_CPC | CHAFSR_CPU | CHAFSR_WDC | &bslash;&n;&t;&t;&t;&t; CHAFSR_WDU | CHAFSR_EDC | CHAFSR_EDU | &bslash;&n;&t;&t;&t;&t; CHAFSR_UE | CHAFSR_CE | JPAFSR_RUE | &bslash;&n;&t;&t;&t;&t; JPAFSR_RCE | JPAFSR_BP | JPAFSR_WBP | &bslash;&n;&t;&t;&t;&t; JPAFSR_FRC | JPAFSR_FRU)
multiline_comment|/* Active JBUS request signal when error occurred */
DECL|macro|JPAFSR_JBREQ
mdefine_line|#define JPAFSR_JBREQ&t;&t;(0x7UL &lt;&lt; 24UL) /* jp */
DECL|macro|JPAFSR_JBREQ_SHIFT
mdefine_line|#define JPAFSR_JBREQ_SHIFT&t;24UL
multiline_comment|/* L2 cache way information */
DECL|macro|JPAFSR_ETW
mdefine_line|#define JPAFSR_ETW&t;&t;(0x3UL &lt;&lt; 22UL) /* jp */
DECL|macro|JPAFSR_ETW_SHIFT
mdefine_line|#define JPAFSR_ETW_SHIFT&t;22UL
multiline_comment|/* System bus MTAG ECC syndrome.  This field captures the status of the&n; * first occurrence of the highest-priority error according to the M_SYND&n; * overwrite policy.  After the AFSR sticky bit, corresponding to the error&n; * for which the M_SYND is reported, is cleared, the contents of the M_SYND&n; * field will be unchanged by will be unfrozen for further error capture.&n; */
DECL|macro|CHAFSR_M_SYNDROME
mdefine_line|#define CHAFSR_M_SYNDROME&t;(0xfUL &lt;&lt; 16UL) /* ch,ch+,jp */
DECL|macro|CHAFSR_M_SYNDROME_SHIFT
mdefine_line|#define CHAFSR_M_SYNDROME_SHIFT&t;16UL
multiline_comment|/* Agenid Id of the foreign device causing the UE/CE errors */
DECL|macro|JPAFSR_AID
mdefine_line|#define JPAFSR_AID&t;&t;(0x1fUL &lt;&lt; 9UL) /* jp */
DECL|macro|JPAFSR_AID_SHIFT
mdefine_line|#define JPAFSR_AID_SHIFT&t;9UL
multiline_comment|/* System bus or E-cache data ECC syndrome.  This field captures the status&n; * of the first occurrence of the highest-priority error according to the&n; * E_SYND overwrite policy.  After the AFSR sticky bit, corresponding to the&n; * error for which the E_SYND is reported, is cleare, the contents of the E_SYND&n; * field will be unchanged but will be unfrozen for further error capture.&n; */
DECL|macro|CHAFSR_E_SYNDROME
mdefine_line|#define CHAFSR_E_SYNDROME&t;(0x1ffUL &lt;&lt; 0UL) /* ch,ch+,jp */
DECL|macro|CHAFSR_E_SYNDROME_SHIFT
mdefine_line|#define CHAFSR_E_SYNDROME_SHIFT&t;0UL
multiline_comment|/* The AFSR must be explicitly cleared by software, it is not cleared automatically&n; * by a read.  Writes to bits &lt;51:33&gt; with bits set will clear the corresponding&n; * bits in the AFSR.  Bits associated with disrupting traps must be cleared before&n; * interrupts are re-enabled to prevent multiple traps for the same error.  I.e.&n; * PSTATE.IE and AFSR bits control delivery of disrupting traps.&n; *&n; * Since there is only one AFAR, when multiple events have been logged by the&n; * bits in the AFSR, at most one of these events will have its status captured&n; * in the AFAR.  The highest priority of those event bits will get AFAR logging.&n; * The AFAR will be unlocked and available to capture the address of another event&n; * as soon as the one bit in AFSR that corresponds to the event logged in AFAR is&n; * cleared.  For example, if AFSR.CE is detected, then AFSR.UE (which overwrites&n; * the AFAR), and AFSR.UE is cleared by not AFSR.CE, then the AFAR will be unlocked&n; * and ready for another event, even though AFSR.CE is still set.  The same rules&n; * also apply to the M_SYNDROME and E_SYNDROME fields of the AFSR.&n; */
macro_line|#endif /* _SPARC64_CHAFSR_H */
eof
