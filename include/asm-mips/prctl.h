multiline_comment|/*&n; * IRIX prctl interface&n; *&n; * The IRIX kernel maps a page at PRDA_ADDRESS with the&n; * contents of prda and fills it the bits on prda_sys.&n; * $Id$&n; */
macro_line|#ifndef __PRCTL_H__
DECL|macro|__PRCTL_H__
mdefine_line|#define __PRCTL_H__
DECL|macro|PRDA_ADDRESS
mdefine_line|#define PRDA_ADDRESS 0x200000L
DECL|macro|PRDA
mdefine_line|#define PRDA ((struct prda *) PRDA_ADDRESS)
DECL|struct|prda_sys
r_struct
id|prda_sys
(brace
DECL|member|t_pid
id|pid_t
id|t_pid
suffix:semicolon
DECL|member|t_hint
id|u32
id|t_hint
suffix:semicolon
DECL|member|t_dlactseq
id|u32
id|t_dlactseq
suffix:semicolon
DECL|member|t_fpflags
id|u32
id|t_fpflags
suffix:semicolon
DECL|member|t_prid
id|u32
id|t_prid
suffix:semicolon
multiline_comment|/* processor type, $prid CP0 register */
DECL|member|t_dlendseq
id|u32
id|t_dlendseq
suffix:semicolon
DECL|member|t_unused1
id|u64
id|t_unused1
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|t_rpid
id|pid_t
id|t_rpid
suffix:semicolon
DECL|member|t_resched
id|s32
id|t_resched
suffix:semicolon
DECL|member|t_unused
id|u32
id|t_unused
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|t_cpu
id|u32
id|t_cpu
suffix:semicolon
multiline_comment|/* current/last cpu */
multiline_comment|/* FIXME: The signal information, not supported by Linux now */
DECL|member|t_flags
id|u32
id|t_flags
suffix:semicolon
multiline_comment|/* if true, then the sigprocmask is in userspace */
DECL|member|t_sigprocmask
id|u32
id|t_sigprocmask
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* the sigprocmask */
)brace
suffix:semicolon
DECL|struct|prda
r_struct
id|prda
(brace
DECL|member|fill
r_char
id|fill
(braket
l_int|0xe00
)braket
suffix:semicolon
DECL|member|prda_sys
r_struct
id|prda_sys
id|prda_sys
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|t_sys
mdefine_line|#define t_sys           prda_sys
r_int
id|prctl
(paren
r_int
id|op
comma
r_int
id|v1
comma
r_int
id|v2
)paren
suffix:semicolon
macro_line|#endif
eof
