macro_line|#ifndef __LINUX_TC_IPT_H
DECL|macro|__LINUX_TC_IPT_H
mdefine_line|#define __LINUX_TC_IPT_H
macro_line|#include &lt;linux/pkt_cls.h&gt;
DECL|macro|TCA_ACT_IPT
mdefine_line|#define TCA_ACT_IPT 6
r_enum
(brace
DECL|enumerator|TCA_IPT_UNSPEC
id|TCA_IPT_UNSPEC
comma
DECL|enumerator|TCA_IPT_TABLE
id|TCA_IPT_TABLE
comma
DECL|enumerator|TCA_IPT_HOOK
id|TCA_IPT_HOOK
comma
DECL|enumerator|TCA_IPT_INDEX
id|TCA_IPT_INDEX
comma
DECL|enumerator|TCA_IPT_CNT
id|TCA_IPT_CNT
comma
DECL|enumerator|TCA_IPT_TM
id|TCA_IPT_TM
comma
DECL|enumerator|TCA_IPT_TARG
id|TCA_IPT_TARG
comma
DECL|enumerator|__TCA_IPT_MAX
id|__TCA_IPT_MAX
)brace
suffix:semicolon
DECL|macro|TCA_IPT_MAX
mdefine_line|#define TCA_IPT_MAX (__TCA_IPT_MAX - 1)
macro_line|#endif
eof
