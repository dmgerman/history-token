multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/aux_reg.h&n; *&n; * Copyright (C) 2000 Steve Hill (sjhill@cotw.com)&n; *&n; * Changelog:&n; *   08-02-2000&t;SJH&t;Created file&n; */
macro_line|#ifndef _ASM_ARCH_AUXREG_H
DECL|macro|_ASM_ARCH_AUXREG_H
mdefine_line|#define _ASM_ARCH_AUXREG_H
macro_line|#include &lt;asm/arch/hardware.h&gt;
DECL|macro|l7200aux_reg
mdefine_line|#define l7200aux_reg&t;*((volatile unsigned int *) (AUX_BASE))
multiline_comment|/*&n; * Auxillary register values&n; */
DECL|macro|AUX_CLEAR
mdefine_line|#define AUX_CLEAR&t;&t;0x00000000
DECL|macro|AUX_DIAG_LED_ON
mdefine_line|#define AUX_DIAG_LED_ON&t;&t;0x00000002
DECL|macro|AUX_RTS_UART1
mdefine_line|#define AUX_RTS_UART1&t;&t;0x00000004
DECL|macro|AUX_DTR_UART1
mdefine_line|#define AUX_DTR_UART1&t;&t;0x00000008
DECL|macro|AUX_KBD_COLUMN_12_HIGH
mdefine_line|#define AUX_KBD_COLUMN_12_HIGH&t;0x00000010
DECL|macro|AUX_KBD_COLUMN_12_OFF
mdefine_line|#define AUX_KBD_COLUMN_12_OFF&t;0x00000020
DECL|macro|AUX_KBD_COLUMN_13_HIGH
mdefine_line|#define AUX_KBD_COLUMN_13_HIGH&t;0x00000040
DECL|macro|AUX_KBD_COLUMN_13_OFF
mdefine_line|#define AUX_KBD_COLUMN_13_OFF&t;0x00000080
macro_line|#endif
eof
