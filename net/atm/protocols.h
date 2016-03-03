multiline_comment|/* net/atm/protocols.h - ATM protocol handler entry points */
multiline_comment|/* Written 1995-1997 by Werner Almesberger, EPFL LRC */
macro_line|#ifndef NET_ATM_PROTOCOLS_H
DECL|macro|NET_ATM_PROTOCOLS_H
mdefine_line|#define NET_ATM_PROTOCOLS_H
r_int
id|atm_init_aal0
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
multiline_comment|/* &quot;raw&quot; AAL0 */
r_int
id|atm_init_aal34
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
multiline_comment|/* &quot;raw&quot; AAL3/4 transport */
r_int
id|atm_init_aal5
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
multiline_comment|/* &quot;raw&quot; AAL5 transport */
macro_line|#endif
eof
