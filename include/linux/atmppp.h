multiline_comment|/* atmppp.h - RFC2364 PPPoATM */
multiline_comment|/* Written 2000 by Mitchell Blank Jr */
macro_line|#ifndef _LINUX_ATMPPP_H
DECL|macro|_LINUX_ATMPPP_H
mdefine_line|#define _LINUX_ATMPPP_H
macro_line|#include &lt;linux/atm.h&gt;
DECL|macro|PPPOATM_ENCAPS_AUTODETECT
mdefine_line|#define PPPOATM_ENCAPS_AUTODETECT&t;(0)
DECL|macro|PPPOATM_ENCAPS_VC
mdefine_line|#define PPPOATM_ENCAPS_VC&t;&t;(1)
DECL|macro|PPPOATM_ENCAPS_LLC
mdefine_line|#define PPPOATM_ENCAPS_LLC&t;&t;(2)
multiline_comment|/*&n; * This is for the ATM_SETBACKEND call - these are like socket families:&n; * the first element of the structure is the backend number and the rest&n; * is per-backend specific&n; */
DECL|struct|atm_backend_ppp
r_struct
id|atm_backend_ppp
(brace
DECL|member|backend_num
id|atm_backend_t
id|backend_num
suffix:semicolon
multiline_comment|/* ATM_BACKEND_PPP */
DECL|member|encaps
r_int
id|encaps
suffix:semicolon
multiline_comment|/* PPPOATM_ENCAPS_* */
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_ATMPPP_H */
eof
