multiline_comment|/* $Id: capifunc.h,v 1.11.4.1 2004/08/28 20:03:53 armin Exp $&n; *&n; * ISDN interface module for Eicon active cards DIVA.&n; * CAPI Interface common functions&n; * &n; * Copyright 2000-2003 by Armin Schindler (mac@melware.de) &n; * Copyright 2000-2003 Cytronics &amp; Melware (info@melware.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#ifndef __CAPIFUNC_H__
DECL|macro|__CAPIFUNC_H__
mdefine_line|#define __CAPIFUNC_H__
DECL|macro|DRRELMAJOR
mdefine_line|#define DRRELMAJOR  2
DECL|macro|DRRELMINOR
mdefine_line|#define DRRELMINOR  0
DECL|macro|DRRELEXTRA
mdefine_line|#define DRRELEXTRA  &quot;&quot;
DECL|macro|M_COMPANY
mdefine_line|#define M_COMPANY &quot;Eicon Networks&quot;
r_extern
r_char
id|DRIVERRELEASE_CAPI
(braket
)braket
suffix:semicolon
DECL|struct|_diva_card
r_typedef
r_struct
id|_diva_card
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|remove_in_progress
r_int
id|remove_in_progress
suffix:semicolon
DECL|member|Id
r_int
id|Id
suffix:semicolon
DECL|member|capi_ctrl
r_struct
id|capi_ctr
id|capi_ctrl
suffix:semicolon
DECL|member|adapter
id|DIVA_CAPI_ADAPTER
op_star
id|adapter
suffix:semicolon
DECL|member|d
id|DESCRIPTOR
id|d
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|typedef|diva_card
)brace
id|diva_card
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
r_int
id|init_capifunc
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|finit_capifunc
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __CAPIFUNC_H__ */
eof
