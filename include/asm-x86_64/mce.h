macro_line|#ifndef _ASM_MCE_H
DECL|macro|_ASM_MCE_H
mdefine_line|#define _ASM_MCE_H 1
macro_line|#include &lt;asm/ioctls.h&gt;
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* &n; * Machine Check support for x86&n; */
DECL|macro|MCG_CTL_P
mdefine_line|#define MCG_CTL_P        (1UL&lt;&lt;8)   /* MCG_CAP register available */
DECL|macro|MCG_STATUS_RIPV
mdefine_line|#define MCG_STATUS_RIPV  (1UL&lt;&lt;0)   /* restart ip valid */
DECL|macro|MCG_STATUS_EIPV
mdefine_line|#define MCG_STATUS_EIPV  (1UL&lt;&lt;1)   /* eip points to correct instruction */
DECL|macro|MCG_STATUS_MCIP
mdefine_line|#define MCG_STATUS_MCIP  (1UL&lt;&lt;2)   /* machine check in progress */
DECL|macro|MCI_STATUS_VAL
mdefine_line|#define MCI_STATUS_VAL   (1UL&lt;&lt;63)  /* valid error */
DECL|macro|MCI_STATUS_OVER
mdefine_line|#define MCI_STATUS_OVER  (1UL&lt;&lt;62)  /* previous errors lost */
DECL|macro|MCI_STATUS_UC
mdefine_line|#define MCI_STATUS_UC    (1UL&lt;&lt;61)  /* uncorrected error */
DECL|macro|MCI_STATUS_EN
mdefine_line|#define MCI_STATUS_EN    (1UL&lt;&lt;60)  /* error enabled */
DECL|macro|MCI_STATUS_MISCV
mdefine_line|#define MCI_STATUS_MISCV (1UL&lt;&lt;59)  /* misc error reg. valid */
DECL|macro|MCI_STATUS_ADDRV
mdefine_line|#define MCI_STATUS_ADDRV (1UL&lt;&lt;58)  /* addr reg. valid */
DECL|macro|MCI_STATUS_PCC
mdefine_line|#define MCI_STATUS_PCC   (1UL&lt;&lt;57)  /* processor context corrupt */
multiline_comment|/* Fields are zero when not available */
DECL|struct|mce
r_struct
id|mce
(brace
DECL|member|status
id|__u64
id|status
suffix:semicolon
DECL|member|misc
id|__u64
id|misc
suffix:semicolon
DECL|member|addr
id|__u64
id|addr
suffix:semicolon
DECL|member|mcgstatus
id|__u64
id|mcgstatus
suffix:semicolon
DECL|member|rip
id|__u64
id|rip
suffix:semicolon
DECL|member|tsc
id|__u64
id|tsc
suffix:semicolon
multiline_comment|/* cpu time stamp counter */
DECL|member|res1
id|__u64
id|res1
suffix:semicolon
multiline_comment|/* for future extension */
DECL|member|res2
id|__u64
id|res2
suffix:semicolon
multiline_comment|/* dito. */
DECL|member|cs
id|__u8
id|cs
suffix:semicolon
multiline_comment|/* code segment */
DECL|member|bank
id|__u8
id|bank
suffix:semicolon
multiline_comment|/* machine check bank */
DECL|member|cpu
id|__u8
id|cpu
suffix:semicolon
multiline_comment|/* cpu that raised the error */
DECL|member|finished
id|__u8
id|finished
suffix:semicolon
multiline_comment|/* entry is valid */
DECL|member|pad
id|__u32
id|pad
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * This structure contains all data related to the MCE log.&n; * Also carries a signature to make it easier to find from external debugging tools.&n; * Each entry is only valid when its finished flag is set.&n; */
DECL|macro|MCE_LOG_LEN
mdefine_line|#define MCE_LOG_LEN 32
DECL|struct|mce_log
r_struct
id|mce_log
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* &quot;MACHINECHECK&quot; */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* = MCE_LOG_LEN */
DECL|member|next
r_int
id|next
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|pad0
r_int
id|pad0
suffix:semicolon
DECL|member|entry
r_struct
id|mce
id|entry
(braket
id|MCE_LOG_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MCE_OVERFLOW
mdefine_line|#define MCE_OVERFLOW 0&t;&t;/* bit 0 in flags means overflow */
DECL|macro|MCE_LOG_SIGNATURE
mdefine_line|#define MCE_LOG_SIGNATURE &t;&quot;MACHINECHECK&quot;
DECL|macro|MCE_GET_RECORD_LEN
mdefine_line|#define MCE_GET_RECORD_LEN   _IOR(&squot;M&squot;, 1, int)
DECL|macro|MCE_GET_LOG_LEN
mdefine_line|#define MCE_GET_LOG_LEN      _IOR(&squot;M&squot;, 2, int)
DECL|macro|MCE_GETCLEAR_FLAGS
mdefine_line|#define MCE_GETCLEAR_FLAGS   _IOR(&squot;M&squot;, 3, int)
multiline_comment|/* Software defined banks */
DECL|macro|MCE_EXTENDED_BANK
mdefine_line|#define MCE_EXTENDED_BANK&t;128
DECL|macro|MCE_THERMAL_BANK
mdefine_line|#define MCE_THERMAL_BANK&t;MCE_EXTENDED_BANK + 0
r_void
id|mce_log
c_func
(paren
r_struct
id|mce
op_star
id|m
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_MCE_INTEL
r_void
id|mce_intel_feature_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
suffix:semicolon
macro_line|#else
DECL|function|mce_intel_feature_init
r_static
r_inline
r_void
id|mce_intel_feature_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
)brace
macro_line|#endif
macro_line|#endif
eof
