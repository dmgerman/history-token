macro_line|#ifndef __LINUX_TC_GACT_H
DECL|macro|__LINUX_TC_GACT_H
mdefine_line|#define __LINUX_TC_GACT_H
macro_line|#include &lt;linux/pkt_cls.h&gt;
DECL|macro|TCA_ACT_GACT
mdefine_line|#define TCA_ACT_GACT 5
DECL|struct|tc_gact
r_struct
id|tc_gact
(brace
DECL|member|tc_gen
id|tc_gen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_gact_p
r_struct
id|tc_gact_p
(brace
DECL|macro|PGACT_NONE
mdefine_line|#define PGACT_NONE              0
DECL|macro|PGACT_NETRAND
mdefine_line|#define PGACT_NETRAND           1
DECL|macro|PGACT_DETERM
mdefine_line|#define PGACT_DETERM            2
DECL|macro|MAX_RAND
mdefine_line|#define MAX_RAND                (PGACT_DETERM + 1 )
DECL|member|ptype
id|__u16
id|ptype
suffix:semicolon
DECL|member|pval
id|__u16
id|pval
suffix:semicolon
DECL|member|paction
r_int
id|paction
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|TCA_GACT_UNSPEC
id|TCA_GACT_UNSPEC
comma
DECL|enumerator|TCA_GACT_TM
id|TCA_GACT_TM
comma
DECL|enumerator|TCA_GACT_PARMS
id|TCA_GACT_PARMS
comma
DECL|enumerator|TCA_GACT_PROB
id|TCA_GACT_PROB
comma
DECL|enumerator|__TCA_GACT_MAX
id|__TCA_GACT_MAX
)brace
suffix:semicolon
DECL|macro|TCA_GACT_MAX
mdefine_line|#define TCA_GACT_MAX (__TCA_GACT_MAX - 1)
macro_line|#endif
eof
