multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlan_filter.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Fri Jan 29 15:24:08 1999&n; * Modified at:   Sun Feb  7 23:35:31 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef IRLAN_FILTER_H
DECL|macro|IRLAN_FILTER_H
mdefine_line|#define IRLAN_FILTER_H
r_void
id|irlan_check_command_param
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_char
op_star
id|param
comma
r_char
op_star
id|value
)paren
suffix:semicolon
r_void
id|irlan_filter_request
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|irlan_print_filter
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_int
id|filter_type
)paren
suffix:semicolon
macro_line|#endif /* IRLAN_FILTER_H */
eof
