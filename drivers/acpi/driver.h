multiline_comment|/*&n; *  driver.h - ACPI driver&n; *&n; *  Copyright (C) 2000 Andrew Henroid&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __DRIVER_H
DECL|macro|__DRIVER_H
mdefine_line|#define __DRIVER_H
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|ACPI_MAX_THROTTLE
mdefine_line|#define ACPI_MAX_THROTTLE 10
DECL|macro|ACPI_INVALID
mdefine_line|#define ACPI_INVALID ~0UL
DECL|macro|ACPI_INFINITE
mdefine_line|#define ACPI_INFINITE ~0UL
multiline_comment|/*&n; * cpu.c&n; */
r_int
id|acpi_cpu_init
c_func
(paren
r_void
)paren
suffix:semicolon
id|u32
id|acpi_read_pm_timer
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|acpi_c2_exit_latency
suffix:semicolon
r_extern
r_int
r_int
id|acpi_c3_exit_latency
suffix:semicolon
r_extern
r_int
r_int
id|acpi_c2_enter_latency
suffix:semicolon
r_extern
r_int
r_int
id|acpi_c3_enter_latency
suffix:semicolon
multiline_comment|/*&n; * driver.c&n; */
r_int
id|acpi_run
c_func
(paren
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|context
)paren
suffix:semicolon
multiline_comment|/*&n; * ec.c&n; */
r_int
id|acpi_ec_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * power.c&n; */
r_int
id|acpi_power_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * sys.c&n; */
r_int
id|acpi_sys_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|acpi_enter_sx
c_func
(paren
id|acpi_sstate_t
id|state
)paren
suffix:semicolon
r_extern
r_volatile
id|acpi_sstate_t
id|acpi_sleep_state
suffix:semicolon
multiline_comment|/*&n; * table.c&n; */
r_extern
id|FADT_DESCRIPTOR
id|acpi_fadt
suffix:semicolon
r_int
id|acpi_find_and_load_tables
c_func
(paren
id|u64
id|rsdp
)paren
suffix:semicolon
macro_line|#endif /* __DRIVER_H */
eof
