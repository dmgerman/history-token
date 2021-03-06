multiline_comment|/*** -*- linux-c -*- **********************************************************&n;&n;     Driver for Atmel at76c502 at76c504 and at76c506 wireless cards.&n;&n;         Copyright 2005 Dan Williams and Red Hat, Inc.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This software is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with Atmel wireless lan drivers; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;&n;******************************************************************************/
macro_line|#ifndef _ATMEL_H
DECL|macro|_ATMEL_H
mdefine_line|#define _ATMEL_H
r_typedef
r_enum
(brace
DECL|enumerator|ATMEL_FW_TYPE_NONE
id|ATMEL_FW_TYPE_NONE
op_assign
l_int|0
comma
DECL|enumerator|ATMEL_FW_TYPE_502
id|ATMEL_FW_TYPE_502
comma
DECL|enumerator|ATMEL_FW_TYPE_502D
id|ATMEL_FW_TYPE_502D
comma
DECL|enumerator|ATMEL_FW_TYPE_502E
id|ATMEL_FW_TYPE_502E
comma
DECL|enumerator|ATMEL_FW_TYPE_502_3COM
id|ATMEL_FW_TYPE_502_3COM
comma
DECL|enumerator|ATMEL_FW_TYPE_504
id|ATMEL_FW_TYPE_504
comma
DECL|enumerator|ATMEL_FW_TYPE_504_2958
id|ATMEL_FW_TYPE_504_2958
comma
DECL|enumerator|ATMEL_FW_TYPE_504A_2958
id|ATMEL_FW_TYPE_504A_2958
comma
DECL|enumerator|ATMEL_FW_TYPE_506
id|ATMEL_FW_TYPE_506
DECL|typedef|AtmelFWType
)brace
id|AtmelFWType
suffix:semicolon
r_struct
id|net_device
op_star
id|init_atmel_card
c_func
(paren
r_int
r_int
comma
r_int
comma
r_const
id|AtmelFWType
comma
r_struct
id|device
op_star
comma
r_int
(paren
op_star
id|present_func
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|stop_atmel_card
c_func
(paren
r_struct
id|net_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|atmel_open
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
