multiline_comment|/* net/atm/protocols.h - ATM protocol handler entry points */
multiline_comment|/* Written 1995-1997 by Werner Almesberger, EPFL LRC */
macro_line|#ifndef NET_ATM_PROTOCOLS_H
DECL|macro|NET_ATM_PROTOCOLS_H
mdefine_line|#define NET_ATM_PROTOCOLS_H
r_void
id|atm_push_raw
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
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
r_int
id|atm_init_atmarp
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
multiline_comment|/* ATM ARP */
macro_line|#endif
eof
