multiline_comment|/* $Id: capifunc.h,v 1.1.2.2 2002/10/02 14:38:37 armin Exp $&n; *&n; * ISDN interface module for Eicon active cards DIVA.&n; * CAPI Interface common functions&n; * &n; * Copyright 2000-2002 by Armin Schindler (mac@melware.de) &n; * Copyright 2000-2002 Cytronics &amp; Melware (info@melware.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#ifndef __CAPIFUNC_H__ 
DECL|macro|__CAPIFUNC_H__
mdefine_line|#define __CAPIFUNC_H__
DECL|macro|MAX_DESCRIPTORS
mdefine_line|#define MAX_DESCRIPTORS  32
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
id|DRIVERRELEASE
(braket
)braket
suffix:semicolon
DECL|struct|_diva_card
r_typedef
r_struct
id|_diva_card
(brace
DECL|member|Id
r_int
id|Id
suffix:semicolon
DECL|member|next
r_struct
id|_diva_card
op_star
id|next
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
