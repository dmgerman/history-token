multiline_comment|/*&n;    lm75.h - Part of lm_sensors, Linux kernel modules for hardware&n;             monitoring&n;    Copyright (c) 2003 Mark M. Hoffman &lt;mhoffman@lightlink.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;    This file contains common code for encoding/decoding LM75 type&n;    temperature readings, which are emulated by many of the chips&n;    we support.  As the user is unlikely to load more than one driver&n;    which contains this code, we don&squot;t worry about the wasted space.&n;*/
macro_line|#include &lt;linux/i2c-sensor.h&gt;
multiline_comment|/* straight from the datasheet */
DECL|macro|LM75_TEMP_MIN
mdefine_line|#define LM75_TEMP_MIN (-55000)
DECL|macro|LM75_TEMP_MAX
mdefine_line|#define LM75_TEMP_MAX 125000
multiline_comment|/* TEMP: 0.001C/bit (-55C to +125C)&n;   REG: (0.5C/bit, two&squot;s complement) &lt;&lt; 7 */
DECL|function|LM75_TEMP_TO_REG
r_static
r_inline
id|u16
id|LM75_TEMP_TO_REG
c_func
(paren
r_int
id|temp
)paren
(brace
r_int
id|ntemp
op_assign
id|SENSORS_LIMIT
c_func
(paren
id|temp
comma
id|LM75_TEMP_MIN
comma
id|LM75_TEMP_MAX
)paren
suffix:semicolon
id|ntemp
op_add_assign
(paren
id|ntemp
OL
l_int|0
ques
c_cond
op_minus
l_int|250
suffix:colon
l_int|250
)paren
suffix:semicolon
r_return
(paren
id|u16
)paren
(paren
(paren
id|ntemp
op_div
l_int|500
)paren
op_lshift
l_int|7
)paren
suffix:semicolon
)brace
DECL|function|LM75_TEMP_FROM_REG
r_static
r_inline
r_int
id|LM75_TEMP_FROM_REG
c_func
(paren
id|u16
id|reg
)paren
(brace
multiline_comment|/* use integer division instead of equivalent right shift to&n;&t;   guarantee arithmetic shift and preserve the sign */
r_return
(paren
(paren
id|s16
)paren
id|reg
op_div
l_int|128
)paren
op_star
l_int|500
suffix:semicolon
)brace
eof
