multiline_comment|/*&n; *  linux/drivers/cpufreq/cpufreq_powersave.c&n; *&n; *  Copyright (C) 2002 - 2003 Dominik Brodowski &lt;linux@brodo.de&gt;&n; *&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|function|cpufreq_governor_powersave
r_static
r_int
id|cpufreq_governor_powersave
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_int
r_int
id|event
)paren
(brace
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|CPUFREQ_GOV_START
suffix:colon
r_case
id|CPUFREQ_GOV_LIMITS
suffix:colon
id|__cpufreq_driver_target
c_func
(paren
id|policy
comma
id|policy-&gt;min
comma
id|CPUFREQ_RELATION_L
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cpufreq_gov_powersave
r_static
r_struct
id|cpufreq_governor
id|cpufreq_gov_powersave
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;powersave&quot;
comma
dot
id|governor
op_assign
id|cpufreq_governor_powersave
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|cpufreq_gov_powersave_init
r_static
r_int
id|__init
id|cpufreq_gov_powersave_init
c_func
(paren
r_void
)paren
(brace
r_return
id|cpufreq_register_governor
c_func
(paren
op_amp
id|cpufreq_gov_powersave
)paren
suffix:semicolon
)brace
DECL|function|cpufreq_gov_powersave_exit
r_static
r_void
id|__exit
id|cpufreq_gov_powersave_exit
c_func
(paren
r_void
)paren
(brace
id|cpufreq_unregister_governor
c_func
(paren
op_amp
id|cpufreq_gov_powersave
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dominik Brodowski &lt;linux@brodo.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;CPUfreq policy governor &squot;powersave&squot;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|cpufreq_gov_powersave_init
id|module_init
c_func
(paren
id|cpufreq_gov_powersave_init
)paren
suffix:semicolon
DECL|variable|cpufreq_gov_powersave_exit
id|module_exit
c_func
(paren
id|cpufreq_gov_powersave_exit
)paren
suffix:semicolon
eof
