multiline_comment|/* ip_mp_alg.h: IPV4 multipath algorithm support, user-visible values.&n; *&n; * Copyright (C) 2004, 2005 Einar Lueck &lt;elueck@de.ibm.com&gt;&n; * Copyright (C) 2005 David S. Miller &lt;davem@davemloft.net&gt;&n; */
macro_line|#ifndef _LINUX_IP_MP_ALG_H
DECL|macro|_LINUX_IP_MP_ALG_H
mdefine_line|#define _LINUX_IP_MP_ALG_H
DECL|enum|ip_mp_alg
r_enum
id|ip_mp_alg
(brace
DECL|enumerator|IP_MP_ALG_NONE
id|IP_MP_ALG_NONE
comma
DECL|enumerator|IP_MP_ALG_RR
id|IP_MP_ALG_RR
comma
DECL|enumerator|IP_MP_ALG_DRR
id|IP_MP_ALG_DRR
comma
DECL|enumerator|IP_MP_ALG_RANDOM
id|IP_MP_ALG_RANDOM
comma
DECL|enumerator|IP_MP_ALG_WRANDOM
id|IP_MP_ALG_WRANDOM
comma
DECL|enumerator|__IP_MP_ALG_MAX
id|__IP_MP_ALG_MAX
)brace
suffix:semicolon
DECL|macro|IP_MP_ALG_MAX
mdefine_line|#define IP_MP_ALG_MAX (__IP_MP_ALG_MAX - 1)
macro_line|#endif /* _LINUX_IP_MP_ALG_H */
eof
