macro_line|#ifndef _ASM_IA64_SN_SAL_H
DECL|macro|_ASM_IA64_SN_SAL_H
mdefine_line|#define _ASM_IA64_SN_SAL_H
multiline_comment|/*&n; * System Abstraction Layer definitions for IA64&n; *&n; *&n; * Copyright (C) 2000, Silicon Graphics.&n; * Copyright (C) 2000. Jack Steiner (steiner@sgi.com)&n; */
macro_line|#include &lt;asm/sal.h&gt;
singleline_comment|// SGI Specific Calls
DECL|macro|SN_SAL_POD_MODE
mdefine_line|#define  SN_SAL_POD_MODE                           0x02000001
DECL|macro|SN_SAL_SYSTEM_RESET
mdefine_line|#define  SN_SAL_SYSTEM_RESET                       0x02000002
DECL|macro|SN_SAL_PROBE
mdefine_line|#define  SN_SAL_PROBE                              0x02000003
id|u64
id|ia64_sn_probe_io_slot
c_func
(paren
r_int
id|paddr
comma
r_int
id|size
comma
r_void
op_star
id|data_ptr
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_SN1_SAL_H */
eof
