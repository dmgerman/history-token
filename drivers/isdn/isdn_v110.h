multiline_comment|/* $Id: isdn_v110.h,v 1.4.6.1 2001/09/23 22:24:32 kai Exp $&n; *&n; * Linux ISDN subsystem, V.110 related functions (linklevel).&n; *&n; * Copyright by Thomas Pfeiffer (pfeiffer@pds.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef _isdn_v110_h_
DECL|macro|_isdn_v110_h_
mdefine_line|#define _isdn_v110_h_
multiline_comment|/* &n; * isdn_v110_encode will take raw data and encode it using V.110 &n; */
r_extern
r_struct
id|sk_buff
op_star
id|isdn_v110_encode
c_func
(paren
id|isdn_v110_stream
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* &n; * isdn_v110_decode receives V.110 coded data from the stream and rebuilds&n; * frames from them. The source stream doesn&squot;t need to be framed.&n; */
r_extern
r_struct
id|sk_buff
op_star
id|isdn_v110_decode
c_func
(paren
id|isdn_v110_stream
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_v110_stat_callback
c_func
(paren
r_int
comma
id|isdn_ctrl
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_v110_close
c_func
(paren
id|isdn_v110_stream
op_star
id|v
)paren
suffix:semicolon
macro_line|#endif
eof
