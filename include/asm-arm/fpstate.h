multiline_comment|/*&n; *  linux/include/asm-arm/fpstate.h&n; *&n; *  Copyright (C) 1995 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_FPSTATE_H
DECL|macro|__ASM_ARM_FPSTATE_H
mdefine_line|#define __ASM_ARM_FPSTATE_H
DECL|macro|FP_SIZE
mdefine_line|#define FP_SIZE 35
DECL|struct|fp_hard_struct
r_struct
id|fp_hard_struct
(brace
DECL|member|save
r_int
r_int
id|save
(braket
id|FP_SIZE
)braket
suffix:semicolon
multiline_comment|/* as yet undefined */
)brace
suffix:semicolon
DECL|struct|fp_soft_struct
r_struct
id|fp_soft_struct
(brace
DECL|member|save
r_int
r_int
id|save
(braket
id|FP_SIZE
)braket
suffix:semicolon
multiline_comment|/* undefined information */
)brace
suffix:semicolon
DECL|union|fp_state
r_union
id|fp_state
(brace
DECL|member|hard
r_struct
id|fp_hard_struct
id|hard
suffix:semicolon
DECL|member|soft
r_struct
id|fp_soft_struct
id|soft
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
