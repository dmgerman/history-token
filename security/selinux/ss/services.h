multiline_comment|/*&n; * Implementation of the security services.&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
macro_line|#ifndef _SS_SERVICES_H_
DECL|macro|_SS_SERVICES_H_
mdefine_line|#define _SS_SERVICES_H_
macro_line|#include &quot;policydb.h&quot;
macro_line|#include &quot;sidtab.h&quot;
multiline_comment|/*&n; * The security server uses two global data structures&n; * when providing its services:  the SID table (sidtab)&n; * and the policy database (policydb).&n; */
r_extern
r_struct
id|sidtab
id|sidtab
suffix:semicolon
r_extern
r_struct
id|policydb
id|policydb
suffix:semicolon
macro_line|#endif&t;/* _SS_SERVICES_H_ */
eof
