multiline_comment|/*&n; *  linux/include/asm-arm/hardware/clock.h&n; *&n; *  Copyright (C) 2004 ARM Limited.&n; *  Written by Deep Blue Solutions Limited.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef ASMARM_CLOCK_H
DECL|macro|ASMARM_CLOCK_H
mdefine_line|#define ASMARM_CLOCK_H
r_struct
id|device
suffix:semicolon
multiline_comment|/*&n; * The base API.&n; */
multiline_comment|/*&n; * struct clk - an machine class defined object / cookie.&n; */
r_struct
id|clk
suffix:semicolon
multiline_comment|/**&n; * clk_get - lookup and obtain a reference to a clock producer.&n; * @dev: device for clock &quot;consumer&quot;&n; * @id: device ID&n; *&n; * Returns a struct clk corresponding to the clock producer, or&n; * valid IS_ERR() condition containing errno.&n; */
r_struct
id|clk
op_star
id|clk_get
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|id
)paren
suffix:semicolon
multiline_comment|/**&n; * clk_enable - inform the system when the clock source should be running.&n; * @clk: clock source&n; *&n; * If the clock can not be enabled/disabled, this should return success.&n; *&n; * Returns success (0) or negative errno.&n; */
r_int
id|clk_enable
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
suffix:semicolon
multiline_comment|/**&n; * clk_disable - inform the system when the clock source is no longer required.&n; * @clk: clock source&n; */
r_void
id|clk_disable
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
suffix:semicolon
multiline_comment|/**&n; * clk_use - increment the use count&n; * @clk: clock source&n; *&n; * Returns success (0) or negative errno.&n; */
r_int
id|clk_use
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
suffix:semicolon
multiline_comment|/**&n; * clk_unuse - decrement the use count&n; * @clk: clock source&n; */
r_void
id|clk_unuse
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
suffix:semicolon
multiline_comment|/**&n; * clk_get_rate - obtain the current clock rate (in Hz) for a clock source.&n; *&t;&t;  This is only valid once the clock source has been enabled.&n; * @clk: clock source&n; */
r_int
r_int
id|clk_get_rate
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
suffix:semicolon
multiline_comment|/**&n; * clk_put&t;- &quot;free&quot; the clock source&n; * @clk: clock source&n; */
r_void
id|clk_put
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
suffix:semicolon
multiline_comment|/*&n; * The remaining APIs are optional for machine class support.&n; */
multiline_comment|/**&n; * clk_round_rate - adjust a rate to the exact rate a clock can provide&n; * @clk: clock source&n; * @rate: desired clock rate in Hz&n; *&n; * Returns rounded clock rate in Hz, or negative errno.&n; */
r_int
id|clk_round_rate
c_func
(paren
r_struct
id|clk
op_star
id|clk
comma
r_int
r_int
id|rate
)paren
suffix:semicolon
multiline_comment|/**&n; * clk_set_rate - set the clock rate for a clock source&n; * @clk: clock source&n; * @rate: desired clock rate in Hz&n; *&n; * Returns success (0) or negative errno.&n; */
r_int
id|clk_set_rate
c_func
(paren
r_struct
id|clk
op_star
id|clk
comma
r_int
r_int
id|rate
)paren
suffix:semicolon
multiline_comment|/**&n; * clk_set_parent - set the parent clock source for this clock&n; * @clk: clock source&n; * @parent: parent clock source&n; *&n; * Returns success (0) or negative errno.&n; */
r_int
id|clk_set_parent
c_func
(paren
r_struct
id|clk
op_star
id|clk
comma
r_struct
id|clk
op_star
id|parent
)paren
suffix:semicolon
multiline_comment|/**&n; * clk_get_parent - get the parent clock source for this clock&n; * @clk: clock source&n; *&n; * Returns struct clk corresponding to parent clock source, or&n; * valid IS_ERR() condition containing errno.&n; */
r_struct
id|clk
op_star
id|clk_get_parent
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
suffix:semicolon
macro_line|#endif
eof
