multiline_comment|/*&n; *  setup.c, Setup for the CASIO CASSIOPEIA E-11/15/55/65.&n; *&n; *  Copyright (C) 2002-2003  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/vr41xx/e55.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_extern
r_int
r_int
id|initrd_start
comma
id|initrd_end
suffix:semicolon
r_extern
r_void
op_star
id|__rd_start
comma
op_star
id|__rd_end
suffix:semicolon
macro_line|#endif
DECL|function|casio_e55_setup
r_static
r_void
id|__init
id|casio_e55_setup
c_func
(paren
r_void
)paren
(brace
id|set_io_port_base
c_func
(paren
id|IO_PORT_BASE
)paren
suffix:semicolon
id|ioport_resource.start
op_assign
id|IO_PORT_RESOURCE_START
suffix:semicolon
id|ioport_resource.end
op_assign
id|IO_PORT_RESOURCE_END
suffix:semicolon
id|iomem_resource.start
op_assign
id|IO_MEM_RESOURCE_START
suffix:semicolon
id|iomem_resource.end
op_assign
id|IO_MEM_RESOURCE_END
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__rd_start
suffix:semicolon
id|initrd_end
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__rd_end
suffix:semicolon
macro_line|#endif
id|board_time_init
op_assign
id|vr41xx_time_init
suffix:semicolon
id|board_timer_setup
op_assign
id|vr41xx_timer_setup
suffix:semicolon
id|vr41xx_bcu_init
c_func
(paren
)paren
suffix:semicolon
id|vr41xx_cmu_init
c_func
(paren
)paren
suffix:semicolon
id|vr41xx_pmu_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_8250
id|vr41xx_siu_init
c_func
(paren
id|SIU_RS232C
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|casio_e55_setup
id|early_initcall
c_func
(paren
id|casio_e55_setup
)paren
suffix:semicolon
eof
