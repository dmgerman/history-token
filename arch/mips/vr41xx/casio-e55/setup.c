multiline_comment|/*&n; * FILE NAME&n; *&t;arch/mips/vr41xx/casio-e55/setup.c&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Setup for the CASIO CASSIOPEIA E-11/15/55/65.&n; *&n; * Copyright 2002 Yoichi Yuasa&n; *                yuasa@hh.iij4u.or.jp&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
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
macro_line|#ifdef CONFIG_BLK_DEV_IDE
r_extern
r_struct
id|ide_ops
id|e55_ide_ops
suffix:semicolon
macro_line|#endif
DECL|function|casio_e55_setup
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
id|_machine_restart
op_assign
id|vr41xx_restart
suffix:semicolon
id|_machine_halt
op_assign
id|vr41xx_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|vr41xx_power_off
suffix:semicolon
id|board_time_init
op_assign
id|vr41xx_time_init
suffix:semicolon
id|board_timer_setup
op_assign
id|vr41xx_timer_setup
suffix:semicolon
macro_line|#ifdef CONFIG_FB
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDE
id|ide_ops
op_assign
op_amp
id|e55_ide_ops
suffix:semicolon
macro_line|#endif
id|vr41xx_bcu_init
c_func
(paren
)paren
suffix:semicolon
id|vr41xx_cmu_init
c_func
(paren
l_int|0
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
eof
