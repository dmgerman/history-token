multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/*&n; * MCA driver support functions for sysfs.&n; *&n; * (C) 2002 James Bottomley &lt;James.Bottomley@HansenPartnership.com&gt;&n; *&n;**-----------------------------------------------------------------------------&n;**  &n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/mca.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|function|mca_register_driver
r_int
id|mca_register_driver
c_func
(paren
r_struct
id|mca_driver
op_star
id|mca_drv
)paren
(brace
r_int
id|r
suffix:semicolon
r_if
c_cond
(paren
id|MCA_bus
)paren
(brace
id|mca_drv-&gt;driver.bus
op_assign
op_amp
id|mca_bus_type
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|driver_register
c_func
(paren
op_amp
id|mca_drv-&gt;driver
)paren
)paren
OL
l_int|0
)paren
r_return
id|r
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mca_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|mca_register_driver
)paren
suffix:semicolon
DECL|function|mca_unregister_driver
r_void
id|mca_unregister_driver
c_func
(paren
r_struct
id|mca_driver
op_star
id|mca_drv
)paren
(brace
r_if
c_cond
(paren
id|MCA_bus
)paren
id|driver_unregister
c_func
(paren
op_amp
id|mca_drv-&gt;driver
)paren
suffix:semicolon
)brace
DECL|variable|mca_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|mca_unregister_driver
)paren
suffix:semicolon
eof
