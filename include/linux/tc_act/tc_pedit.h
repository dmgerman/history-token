macro_line|#ifndef __LINUX_TC_PED_H
DECL|macro|__LINUX_TC_PED_H
mdefine_line|#define __LINUX_TC_PED_H
macro_line|#include &lt;linux/pkt_cls.h&gt;
DECL|macro|TCA_ACT_PEDIT
mdefine_line|#define TCA_ACT_PEDIT 7
r_enum
(brace
DECL|enumerator|TCA_PEDIT_UNSPEC
id|TCA_PEDIT_UNSPEC
comma
DECL|enumerator|TCA_PEDIT_TM
id|TCA_PEDIT_TM
comma
DECL|enumerator|TCA_PEDIT_PARMS
id|TCA_PEDIT_PARMS
comma
DECL|enumerator|__TCA_PEDIT_MAX
id|__TCA_PEDIT_MAX
)brace
suffix:semicolon
DECL|macro|TCA_PEDIT_MAX
mdefine_line|#define TCA_PEDIT_MAX (__TCA_PEDIT_MAX - 1)
DECL|struct|tc_pedit_key
r_struct
id|tc_pedit_key
(brace
DECL|member|mask
id|__u32
id|mask
suffix:semicolon
multiline_comment|/* AND */
DECL|member|val
id|__u32
id|val
suffix:semicolon
multiline_comment|/*XOR */
DECL|member|off
id|__u32
id|off
suffix:semicolon
multiline_comment|/*offset */
DECL|member|at
id|__u32
id|at
suffix:semicolon
DECL|member|offmask
id|__u32
id|offmask
suffix:semicolon
DECL|member|shift
id|__u32
id|shift
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_pedit_sel
r_struct
id|tc_pedit_sel
(brace
DECL|member|tc_gen
id|tc_gen
suffix:semicolon
DECL|member|nkeys
r_int
r_char
id|nkeys
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|keys
r_struct
id|tc_pedit_key
id|keys
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|tc_pedit
mdefine_line|#define tc_pedit tc_pedit_sel
macro_line|#endif
eof
