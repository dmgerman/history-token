multiline_comment|/*&n; *&t;include/asm-mips/dec/kn230.h&n; *&n; *&t;DECsystem 5100 (MIPSmate or KN230) definitions.&n; *&n; *&t;Copyright (C) 2002, 2003  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN230_H
DECL|macro|__ASM_MIPS_DEC_KN230_H
mdefine_line|#define __ASM_MIPS_DEC_KN230_H
multiline_comment|/*&n; * CPU interrupt bits.&n; */
DECL|macro|KN230_CPU_INR_HALT
mdefine_line|#define KN230_CPU_INR_HALT&t;6&t;/* HALT button */
DECL|macro|KN230_CPU_INR_BUS
mdefine_line|#define KN230_CPU_INR_BUS&t;5&t;/* memory, I/O bus read/write errors */
DECL|macro|KN230_CPU_INR_RTC
mdefine_line|#define KN230_CPU_INR_RTC&t;4&t;/* DS1287 RTC */
DECL|macro|KN230_CPU_INR_SII
mdefine_line|#define KN230_CPU_INR_SII&t;3&t;/* SII (DC7061) SCSI */
DECL|macro|KN230_CPU_INR_LANCE
mdefine_line|#define KN230_CPU_INR_LANCE&t;3&t;/* LANCE (Am7990) Ethernet */
DECL|macro|KN230_CPU_INR_DZ11
mdefine_line|#define KN230_CPU_INR_DZ11&t;2&t;/* DZ11 (DC7085) serial */
macro_line|#endif /* __ASM_MIPS_DEC_KN230_H */
eof
