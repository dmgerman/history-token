multiline_comment|/*&n;    sensors.c - Part of lm_sensors, Linux kernel modules for hardware&n;                monitoring&n;    Copyright (c) 1998, 1999  Frodo Looijaard &lt;frodol@dds.nl&gt; &n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/* Not configurable as a module */
macro_line|#include &lt;linux/init.h&gt;
r_extern
r_int
id|sensors_adm1021_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sensors_lm75_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|sensors_init_all
r_int
id|__init
id|sensors_init_all
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SENSORS_ADM1021
id|sensors_adm1021_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SENSORS_LM75
id|sensors_lm75_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
