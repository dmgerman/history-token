multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997, 1999 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SIGCONTEXT_H
DECL|macro|_ASM_SIGCONTEXT_H
mdefine_line|#define _ASM_SIGCONTEXT_H
macro_line|#include &lt;asm/sgidefs.h&gt;
macro_line|#if _MIPS_SIM == _MIPS_SIM_ABI32
multiline_comment|/*&n; * Keep this struct definition in sync with the sigcontext fragment&n; * in arch/mips/tools/offset.c&n; */
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|sc_regmask
r_int
r_int
id|sc_regmask
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_status
r_int
r_int
id|sc_status
suffix:semicolon
DECL|member|sc_pc
r_int
r_int
r_int
id|sc_pc
suffix:semicolon
DECL|member|sc_regs
r_int
r_int
r_int
id|sc_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sc_fpregs
r_int
r_int
r_int
id|sc_fpregs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sc_ownedfp
r_int
r_int
id|sc_ownedfp
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_fpc_csr
r_int
r_int
id|sc_fpc_csr
suffix:semicolon
DECL|member|sc_fpc_eir
r_int
r_int
id|sc_fpc_eir
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_used_math
r_int
r_int
id|sc_used_math
suffix:semicolon
DECL|member|sc_ssflags
r_int
r_int
id|sc_ssflags
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_mdhi
r_int
r_int
r_int
id|sc_mdhi
suffix:semicolon
DECL|member|sc_mdlo
r_int
r_int
r_int
id|sc_mdlo
suffix:semicolon
DECL|member|sc_cause
r_int
r_int
id|sc_cause
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_badvaddr
r_int
r_int
id|sc_badvaddr
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_sigset
r_int
r_int
id|sc_sigset
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* kernel&squot;s sigset_t */
)brace
suffix:semicolon
macro_line|#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */
macro_line|#if _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32
multiline_comment|/*&n; * Keep this struct definition in sync with the sigcontext fragment&n; * in arch/mips/tools/offset.c&n; *&n; * Warning: this structure illdefined with sc_badvaddr being just an unsigned&n; * int so it was changed to unsigned long in 2.6.0-test1.  This may break&n; * binary compatibility - no prisoners.&n; */
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|sc_regs
r_int
r_int
id|sc_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sc_fpregs
r_int
r_int
id|sc_fpregs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sc_mdhi
r_int
r_int
id|sc_mdhi
suffix:semicolon
DECL|member|sc_mdlo
r_int
r_int
id|sc_mdlo
suffix:semicolon
DECL|member|sc_pc
r_int
r_int
id|sc_pc
suffix:semicolon
DECL|member|sc_badvaddr
r_int
r_int
id|sc_badvaddr
suffix:semicolon
DECL|member|sc_status
r_int
r_int
id|sc_status
suffix:semicolon
DECL|member|sc_fpc_csr
r_int
r_int
id|sc_fpc_csr
suffix:semicolon
DECL|member|sc_fpc_eir
r_int
r_int
id|sc_fpc_eir
suffix:semicolon
DECL|member|sc_used_math
r_int
r_int
id|sc_used_math
suffix:semicolon
DECL|member|sc_cause
r_int
r_int
id|sc_cause
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/posix_types.h&gt;
DECL|struct|sigcontext32
r_struct
id|sigcontext32
(brace
DECL|member|sc_regmask
id|__u32
id|sc_regmask
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_status
id|__u32
id|sc_status
suffix:semicolon
DECL|member|sc_pc
id|__u64
id|sc_pc
suffix:semicolon
DECL|member|sc_regs
id|__u64
id|sc_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sc_fpregs
id|__u64
id|sc_fpregs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sc_ownedfp
id|__u32
id|sc_ownedfp
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_fpc_csr
id|__u32
id|sc_fpc_csr
suffix:semicolon
DECL|member|sc_fpc_eir
id|__u32
id|sc_fpc_eir
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_used_math
id|__u32
id|sc_used_math
suffix:semicolon
DECL|member|sc_ssflags
id|__u32
id|sc_ssflags
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_mdhi
id|__u64
id|sc_mdhi
suffix:semicolon
DECL|member|sc_mdlo
id|__u64
id|sc_mdlo
suffix:semicolon
DECL|member|sc_cause
id|__u32
id|sc_cause
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_badvaddr
id|__u32
id|sc_badvaddr
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_sigset
id|__u32
id|sc_sigset
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* kernel&squot;s sigset_t */
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */
macro_line|#endif /* _ASM_SIGCONTEXT_H */
eof
