macro_line|#ifndef __LINUX_TC_MIR_H
DECL|macro|__LINUX_TC_MIR_H
mdefine_line|#define __LINUX_TC_MIR_H
macro_line|#include &lt;linux/pkt_cls.h&gt;
DECL|macro|TCA_ACT_MIRRED
mdefine_line|#define TCA_ACT_MIRRED 8
DECL|macro|TCA_EGRESS_REDIR
mdefine_line|#define TCA_EGRESS_REDIR 1  /* packet redirect to EGRESS*/
DECL|macro|TCA_EGRESS_MIRROR
mdefine_line|#define TCA_EGRESS_MIRROR 2 /* mirror packet to EGRESS */
DECL|macro|TCA_INGRESS_REDIR
mdefine_line|#define TCA_INGRESS_REDIR 3  /* packet redirect to INGRESS*/
DECL|macro|TCA_INGRESS_MIRROR
mdefine_line|#define TCA_INGRESS_MIRROR 4 /* mirror packet to INGRESS */
DECL|struct|tc_mirred
r_struct
id|tc_mirred
(brace
DECL|member|tc_gen
id|tc_gen
suffix:semicolon
DECL|member|eaction
r_int
id|eaction
suffix:semicolon
multiline_comment|/* one of IN/EGRESS_MIRROR/REDIR */
DECL|member|ifindex
id|__u32
id|ifindex
suffix:semicolon
multiline_comment|/* ifindex of egress port */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|TCA_MIRRED_UNSPEC
id|TCA_MIRRED_UNSPEC
comma
DECL|enumerator|TCA_MIRRED_TM
id|TCA_MIRRED_TM
comma
DECL|enumerator|TCA_MIRRED_PARMS
id|TCA_MIRRED_PARMS
comma
DECL|enumerator|__TCA_MIRRED_MAX
id|__TCA_MIRRED_MAX
)brace
suffix:semicolon
DECL|macro|TCA_MIRRED_MAX
mdefine_line|#define TCA_MIRRED_MAX (__TCA_MIRRED_MAX - 1)
macro_line|#endif
eof
