multiline_comment|/*&n; * include/asm-alpha/sysinfo.h&n; */
macro_line|#ifndef __ASM_ALPHA_SYSINFO_H
DECL|macro|__ASM_ALPHA_SYSINFO_H
mdefine_line|#define __ASM_ALPHA_SYSINFO_H
multiline_comment|/* This defines the subset of the OSF/1 getsysinfo/setsysinfo calls&n;   that we support.  */
DECL|macro|GSI_UACPROC
mdefine_line|#define GSI_UACPROC&t;&t;&t;8
DECL|macro|GSI_IEEE_FP_CONTROL
mdefine_line|#define GSI_IEEE_FP_CONTROL&t;&t;45
DECL|macro|GSI_IEEE_STATE_AT_SIGNAL
mdefine_line|#define GSI_IEEE_STATE_AT_SIGNAL&t;46
DECL|macro|GSI_PROC_TYPE
mdefine_line|#define GSI_PROC_TYPE&t;&t;&t;60
DECL|macro|GSI_GET_HWRPB
mdefine_line|#define GSI_GET_HWRPB&t;&t;&t;101
DECL|macro|SSI_NVPAIRS
mdefine_line|#define SSI_NVPAIRS&t;&t;&t;1
DECL|macro|SSI_IEEE_FP_CONTROL
mdefine_line|#define SSI_IEEE_FP_CONTROL&t;&t;14
DECL|macro|SSI_IEEE_STATE_AT_SIGNAL
mdefine_line|#define SSI_IEEE_STATE_AT_SIGNAL&t;15
DECL|macro|SSI_IEEE_IGNORE_STATE_AT_SIGNAL
mdefine_line|#define SSI_IEEE_IGNORE_STATE_AT_SIGNAL&t;16
DECL|macro|SSIN_UACPROC
mdefine_line|#define SSIN_UACPROC&t;&t;&t;6
DECL|macro|UAC_BITMASK
mdefine_line|#define UAC_BITMASK&t;&t;&t;7
DECL|macro|UAC_NOPRINT
mdefine_line|#define UAC_NOPRINT&t;&t;&t;1
DECL|macro|UAC_NOFIX
mdefine_line|#define UAC_NOFIX&t;&t;&t;2
DECL|macro|UAC_SIGBUS
mdefine_line|#define UAC_SIGBUS&t;&t;&t;4
macro_line|#ifdef __KERNEL__
multiline_comment|/* This is the shift that is applied to the UAC bits as stored in the&n;   per-thread flags.  See thread_info.h.  */
DECL|macro|UAC_SHIFT
mdefine_line|#define UAC_SHIFT&t;&t;&t;6
macro_line|#endif
macro_line|#endif /* __ASM_ALPHA_SYSINFO_H */
eof
