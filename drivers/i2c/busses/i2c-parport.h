multiline_comment|/* ------------------------------------------------------------------------ *&n; * i2c-parport.h I2C bus over parallel port                                 *&n; * ------------------------------------------------------------------------ *&n;   Copyright (C) 2003-2004 Jean Delvare &lt;khali@linux-fr.org&gt;&n;   &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; * ------------------------------------------------------------------------ */
macro_line|#ifdef DATA
DECL|macro|DATA
macro_line|#undef DATA
macro_line|#endif
DECL|macro|DATA
mdefine_line|#define DATA&t;0
DECL|macro|STAT
mdefine_line|#define STAT&t;1
DECL|macro|CTRL
mdefine_line|#define CTRL&t;2
DECL|struct|lineop
r_struct
id|lineop
(brace
DECL|member|val
id|u8
id|val
suffix:semicolon
DECL|member|port
id|u8
id|port
suffix:semicolon
DECL|member|inverted
id|u8
id|inverted
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|adapter_parm
r_struct
id|adapter_parm
(brace
DECL|member|setsda
r_struct
id|lineop
id|setsda
suffix:semicolon
DECL|member|setscl
r_struct
id|lineop
id|setscl
suffix:semicolon
DECL|member|getsda
r_struct
id|lineop
id|getsda
suffix:semicolon
DECL|member|getscl
r_struct
id|lineop
id|getscl
suffix:semicolon
DECL|member|init
r_struct
id|lineop
id|init
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|adapter_parm
r_static
r_struct
id|adapter_parm
id|adapter_parm
(braket
)braket
op_assign
(brace
multiline_comment|/* type 0: Philips adapter */
(brace
dot
id|setsda
op_assign
(brace
l_int|0x80
comma
id|DATA
comma
l_int|1
)brace
comma
dot
id|setscl
op_assign
(brace
l_int|0x08
comma
id|CTRL
comma
l_int|0
)brace
comma
dot
id|getsda
op_assign
(brace
l_int|0x80
comma
id|STAT
comma
l_int|0
)brace
comma
dot
id|getscl
op_assign
(brace
l_int|0x08
comma
id|STAT
comma
l_int|0
)brace
comma
)brace
comma
multiline_comment|/* type 1: home brew teletext adapter */
(brace
dot
id|setsda
op_assign
(brace
l_int|0x02
comma
id|DATA
comma
l_int|0
)brace
comma
dot
id|setscl
op_assign
(brace
l_int|0x01
comma
id|DATA
comma
l_int|0
)brace
comma
dot
id|getsda
op_assign
(brace
l_int|0x80
comma
id|STAT
comma
l_int|1
)brace
comma
)brace
comma
multiline_comment|/* type 2: Velleman K8000 adapter */
(brace
dot
id|setsda
op_assign
(brace
l_int|0x02
comma
id|CTRL
comma
l_int|1
)brace
comma
dot
id|setscl
op_assign
(brace
l_int|0x08
comma
id|CTRL
comma
l_int|1
)brace
comma
dot
id|getsda
op_assign
(brace
l_int|0x10
comma
id|STAT
comma
l_int|0
)brace
comma
)brace
comma
multiline_comment|/* type 3: ELV adapter */
(brace
dot
id|setsda
op_assign
(brace
l_int|0x02
comma
id|DATA
comma
l_int|1
)brace
comma
dot
id|setscl
op_assign
(brace
l_int|0x01
comma
id|DATA
comma
l_int|1
)brace
comma
dot
id|getsda
op_assign
(brace
l_int|0x40
comma
id|STAT
comma
l_int|1
)brace
comma
dot
id|getscl
op_assign
(brace
l_int|0x08
comma
id|STAT
comma
l_int|1
)brace
comma
)brace
comma
multiline_comment|/* type 4: ADM1032 evaluation board */
(brace
dot
id|setsda
op_assign
(brace
l_int|0x02
comma
id|DATA
comma
l_int|1
)brace
comma
dot
id|setscl
op_assign
(brace
l_int|0x01
comma
id|DATA
comma
l_int|1
)brace
comma
dot
id|getsda
op_assign
(brace
l_int|0x10
comma
id|STAT
comma
l_int|1
)brace
comma
dot
id|init
op_assign
(brace
l_int|0xf0
comma
id|DATA
comma
l_int|0
)brace
comma
)brace
comma
multiline_comment|/* type 5: ADM1025, ADM1030 and ADM1031 evaluation boards */
(brace
dot
id|setsda
op_assign
(brace
l_int|0x02
comma
id|DATA
comma
l_int|1
)brace
comma
dot
id|setscl
op_assign
(brace
l_int|0x01
comma
id|DATA
comma
l_int|1
)brace
comma
dot
id|getsda
op_assign
(brace
l_int|0x10
comma
id|STAT
comma
l_int|1
)brace
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|type
r_static
r_int
id|type
suffix:semicolon
id|module_param
c_func
(paren
id|type
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|type
comma
l_string|&quot;Type of adapter:&bslash;n&quot;
l_string|&quot; 0 = Philips adapter&bslash;n&quot;
l_string|&quot; 1 = home brew teletext adapter&bslash;n&quot;
l_string|&quot; 2 = Velleman K8000 adapter&bslash;n&quot;
l_string|&quot; 3 = ELV adapter&bslash;n&quot;
l_string|&quot; 4 = ADM1032 evaluation board&bslash;n&quot;
l_string|&quot; 5 = ADM1025, ADM1030 and ADM1031 evaluation boards&bslash;n&quot;
)paren
suffix:semicolon
eof
