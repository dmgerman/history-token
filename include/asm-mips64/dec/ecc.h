multiline_comment|/*&n; *&t;include/asm-mips/dec/ecc.h&n; *&n; *&t;ECC handling logic definitions common to DECstation/DECsystem&n; *&t;5000/200 (KN02), 5000/240 (KN03), 5000/260 (KN05) and&n; *&t;DECsystem 5900 (KN03), 5900/260 (KN05) systems.&n; *&n; *&t;Copyright (C) 2003  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_ECC_H
DECL|macro|__ASM_MIPS_DEC_ECC_H
mdefine_line|#define __ASM_MIPS_DEC_ECC_H
multiline_comment|/*&n; * Error Address Register bits.&n; * The register is r/wc -- any write clears it.&n; */
DECL|macro|KN0X_EAR_VALID
mdefine_line|#define KN0X_EAR_VALID&t;&t;(1&lt;&lt;31)&t;&t;/* error data valid, bus IRQ */
DECL|macro|KN0X_EAR_CPU
mdefine_line|#define KN0X_EAR_CPU&t;&t;(1&lt;&lt;30)&t;&t;/* CPU/DMA transaction */
DECL|macro|KN0X_EAR_WRITE
mdefine_line|#define KN0X_EAR_WRITE&t;&t;(1&lt;&lt;29)&t;&t;/* write/read transaction */
DECL|macro|KN0X_EAR_ECCERR
mdefine_line|#define KN0X_EAR_ECCERR&t;&t;(1&lt;&lt;28)&t;&t;/* ECC/timeout or overrun */
DECL|macro|KN0X_EAR_RES_27
mdefine_line|#define KN0X_EAR_RES_27&t;&t;(1&lt;&lt;27)&t;&t;/* unused */
DECL|macro|KN0X_EAR_ADDRESS
mdefine_line|#define KN0X_EAR_ADDRESS&t;(0x7ffffff&lt;&lt;0)&t;/* address involved */
multiline_comment|/*&n; * Error Syndrome Register bits.&n; * The register is frozen when EAR.VALID is set, otherwise it records bits&n; * from the last memory read.  The register is r/wc -- any write clears it.&n; */
DECL|macro|KN0X_ESR_VLDHI
mdefine_line|#define KN0X_ESR_VLDHI&t;&t;(1&lt;&lt;31)&t;&t;/* error data valid hi word */
DECL|macro|KN0X_ESR_CHKHI
mdefine_line|#define KN0X_ESR_CHKHI&t;&t;(0x7f&lt;&lt;24)&t;/* check bits read from mem */
DECL|macro|KN0X_ESR_SNGHI
mdefine_line|#define KN0X_ESR_SNGHI&t;&t;(1&lt;&lt;23)&t;&t;/* single/double bit error */
DECL|macro|KN0X_ESR_SYNHI
mdefine_line|#define KN0X_ESR_SYNHI&t;&t;(0x7f&lt;&lt;16)&t;/* syndrome from ECC logic */
DECL|macro|KN0X_ESR_VLDLO
mdefine_line|#define KN0X_ESR_VLDLO&t;&t;(1&lt;&lt;15)&t;&t;/* error data valid lo word */
DECL|macro|KN0X_ESR_CHKLO
mdefine_line|#define KN0X_ESR_CHKLO&t;&t;(0x7f&lt;&lt;8)&t;/* check bits read from mem */
DECL|macro|KN0X_ESR_SNGLO
mdefine_line|#define KN0X_ESR_SNGLO&t;&t;(1&lt;&lt;7)&t;&t;/* single/double bit error */
DECL|macro|KN0X_ESR_SYNLO
mdefine_line|#define KN0X_ESR_SYNLO&t;&t;(0x7f&lt;&lt;0)&t;/* syndrome from ECC logic */
macro_line|#ifndef __ASSEMBLY__
r_struct
id|pt_regs
suffix:semicolon
r_extern
r_void
id|dec_ecc_be_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|dec_ecc_be_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|is_fixup
)paren
suffix:semicolon
r_extern
r_void
id|dec_ecc_be_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASM_MIPS_DEC_ECC_H */
eof
