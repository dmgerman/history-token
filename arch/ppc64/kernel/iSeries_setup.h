multiline_comment|/*&n; *    Copyright (c) 2000 Mike Corrigan &lt;mikejc@us.ibm.com&gt;&n; *    Copyright (c) 1999-2000 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: as400_setup.h&n; *&n; *    Description:&n; *      Architecture- / platform-specific boot-time initialization code for&n; *      the IBM AS/400 LPAR. Adapted from original code by Grant Erickson and&n; *      code by Gary Thomas, Cort Dougan &lt;cort@cs.nmt.edu&gt;, and Dan Malek&n; *      &lt;dan@netx4.com&gt;.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef&t;__ISERIES_SETUP_H__
DECL|macro|__ISERIES_SETUP_H__
mdefine_line|#define&t;__ISERIES_SETUP_H__
macro_line|#include &lt;linux/seq_file.h&gt;
r_extern
r_void
id|iSeries_init_early
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|ird_start
comma
r_int
r_int
id|ird_end
comma
r_int
r_int
id|cline_start
comma
r_int
r_int
id|cline_end
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_setup_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_setup_residual
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_int
r_int
id|cpu_id
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_get_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|iSeries_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_get_boot_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|tm
)paren
suffix:semicolon
r_extern
r_int
id|iSeries_set_rtc_time
c_func
(paren
r_int
r_int
id|now
)paren
suffix:semicolon
r_extern
r_int
r_int
id|iSeries_get_rtc_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_progress
c_func
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* __ISERIES_SETUP_H__ */
eof