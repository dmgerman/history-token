multiline_comment|/*======================================================================&n;&n;  Device driver for the PCMCIA control functionality of PXA2xx&n;  microprocessors.&n;&n;    The contents of this file may be used under the&n;    terms of the GNU Public License version 2 (the &quot;GPL&quot;)&n;&n;    (c) Ian Molton (spyro@f2s.com) 2003&n;    (c) Stefan Eletzhofer (stefan.eletzhofer@inquant.de) 2003,4&n;&n;    derived from sa11xx_base.c&n;&n;     Portions created by John G. Dorsey are&n;     Copyright (C) 1999 John G. Dorsey.&n;&n;  ======================================================================*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;pcmcia/bulkmem.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &quot;cs_internal.h&quot;
macro_line|#include &quot;soc_common.h&quot;
macro_line|#include &quot;pxa2xx_base.h&quot;
DECL|macro|MCXX_SETUP_MASK
mdefine_line|#define MCXX_SETUP_MASK     (0x7f)
DECL|macro|MCXX_ASST_MASK
mdefine_line|#define MCXX_ASST_MASK      (0x1f)
DECL|macro|MCXX_HOLD_MASK
mdefine_line|#define MCXX_HOLD_MASK      (0x3f)
DECL|macro|MCXX_SETUP_SHIFT
mdefine_line|#define MCXX_SETUP_SHIFT    (0)
DECL|macro|MCXX_ASST_SHIFT
mdefine_line|#define MCXX_ASST_SHIFT     (7)
DECL|macro|MCXX_HOLD_SHIFT
mdefine_line|#define MCXX_HOLD_SHIFT     (14)
DECL|function|pxa2xx_mcxx_hold
r_static
r_inline
id|u_int
id|pxa2xx_mcxx_hold
c_func
(paren
id|u_int
id|pcmcia_cycle_ns
comma
id|u_int
id|mem_clk_10khz
)paren
(brace
id|u_int
id|code
op_assign
id|pcmcia_cycle_ns
op_star
id|mem_clk_10khz
suffix:semicolon
r_return
(paren
id|code
op_div
l_int|300000
)paren
op_plus
(paren
(paren
id|code
op_mod
l_int|300000
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|pxa2xx_mcxx_asst
r_static
r_inline
id|u_int
id|pxa2xx_mcxx_asst
c_func
(paren
id|u_int
id|pcmcia_cycle_ns
comma
id|u_int
id|mem_clk_10khz
)paren
(brace
id|u_int
id|code
op_assign
id|pcmcia_cycle_ns
op_star
id|mem_clk_10khz
suffix:semicolon
r_return
(paren
id|code
op_div
l_int|300000
)paren
op_plus
(paren
(paren
id|code
op_mod
l_int|300000
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|pxa2xx_mcxx_setup
r_static
r_inline
id|u_int
id|pxa2xx_mcxx_setup
c_func
(paren
id|u_int
id|pcmcia_cycle_ns
comma
id|u_int
id|mem_clk_10khz
)paren
(brace
id|u_int
id|code
op_assign
id|pcmcia_cycle_ns
op_star
id|mem_clk_10khz
suffix:semicolon
r_return
(paren
id|code
op_div
l_int|100000
)paren
op_plus
(paren
(paren
id|code
op_mod
l_int|100000
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* This function returns the (approximate) command assertion period, in&n; * nanoseconds, for a given CPU clock frequency and MCXX_ASST value:&n; */
DECL|function|pxa2xx_pcmcia_cmd_time
r_static
r_inline
id|u_int
id|pxa2xx_pcmcia_cmd_time
c_func
(paren
id|u_int
id|mem_clk_10khz
comma
id|u_int
id|pcmcia_mcxx_asst
)paren
(brace
r_return
(paren
l_int|300000
op_star
(paren
id|pcmcia_mcxx_asst
op_plus
l_int|1
)paren
op_div
id|mem_clk_10khz
)paren
suffix:semicolon
)brace
DECL|function|pxa2xx_pcmcia_set_mcmem
r_static
r_int
id|pxa2xx_pcmcia_set_mcmem
c_func
(paren
r_int
id|sock
comma
r_int
id|speed
comma
r_int
id|clock
)paren
(brace
id|MCMEM
c_func
(paren
id|sock
)paren
op_assign
(paren
(paren
id|pxa2xx_mcxx_setup
c_func
(paren
id|speed
comma
id|clock
)paren
op_amp
id|MCXX_SETUP_MASK
)paren
op_lshift
id|MCXX_SETUP_SHIFT
)paren
op_or
(paren
(paren
id|pxa2xx_mcxx_asst
c_func
(paren
id|speed
comma
id|clock
)paren
op_amp
id|MCXX_ASST_MASK
)paren
op_lshift
id|MCXX_ASST_SHIFT
)paren
op_or
(paren
(paren
id|pxa2xx_mcxx_hold
c_func
(paren
id|speed
comma
id|clock
)paren
op_amp
id|MCXX_HOLD_MASK
)paren
op_lshift
id|MCXX_HOLD_SHIFT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pxa2xx_pcmcia_set_mcio
r_static
r_int
id|pxa2xx_pcmcia_set_mcio
c_func
(paren
r_int
id|sock
comma
r_int
id|speed
comma
r_int
id|clock
)paren
(brace
id|MCIO
c_func
(paren
id|sock
)paren
op_assign
(paren
(paren
id|pxa2xx_mcxx_setup
c_func
(paren
id|speed
comma
id|clock
)paren
op_amp
id|MCXX_SETUP_MASK
)paren
op_lshift
id|MCXX_SETUP_SHIFT
)paren
op_or
(paren
(paren
id|pxa2xx_mcxx_asst
c_func
(paren
id|speed
comma
id|clock
)paren
op_amp
id|MCXX_ASST_MASK
)paren
op_lshift
id|MCXX_ASST_SHIFT
)paren
op_or
(paren
(paren
id|pxa2xx_mcxx_hold
c_func
(paren
id|speed
comma
id|clock
)paren
op_amp
id|MCXX_HOLD_MASK
)paren
op_lshift
id|MCXX_HOLD_SHIFT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pxa2xx_pcmcia_set_mcatt
r_static
r_int
id|pxa2xx_pcmcia_set_mcatt
c_func
(paren
r_int
id|sock
comma
r_int
id|speed
comma
r_int
id|clock
)paren
(brace
id|MCATT
c_func
(paren
id|sock
)paren
op_assign
(paren
(paren
id|pxa2xx_mcxx_setup
c_func
(paren
id|speed
comma
id|clock
)paren
op_amp
id|MCXX_SETUP_MASK
)paren
op_lshift
id|MCXX_SETUP_SHIFT
)paren
op_or
(paren
(paren
id|pxa2xx_mcxx_asst
c_func
(paren
id|speed
comma
id|clock
)paren
op_amp
id|MCXX_ASST_MASK
)paren
op_lshift
id|MCXX_ASST_SHIFT
)paren
op_or
(paren
(paren
id|pxa2xx_mcxx_hold
c_func
(paren
id|speed
comma
id|clock
)paren
op_amp
id|MCXX_HOLD_MASK
)paren
op_lshift
id|MCXX_HOLD_SHIFT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pxa2xx_pcmcia_set_mcxx
r_static
r_int
id|pxa2xx_pcmcia_set_mcxx
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
comma
r_int
r_int
id|clk
)paren
(brace
r_struct
id|soc_pcmcia_timing
id|timing
suffix:semicolon
r_int
id|sock
op_assign
id|skt-&gt;nr
suffix:semicolon
id|soc_common_pcmcia_get_timing
c_func
(paren
id|skt
comma
op_amp
id|timing
)paren
suffix:semicolon
id|pxa2xx_pcmcia_set_mcmem
c_func
(paren
id|sock
comma
id|timing.mem
comma
id|clk
)paren
suffix:semicolon
id|pxa2xx_pcmcia_set_mcatt
c_func
(paren
id|sock
comma
id|timing.attr
comma
id|clk
)paren
suffix:semicolon
id|pxa2xx_pcmcia_set_mcio
c_func
(paren
id|sock
comma
id|timing.io
comma
id|clk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pxa2xx_pcmcia_set_timing
r_static
r_int
id|pxa2xx_pcmcia_set_timing
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
r_int
r_int
id|clk
op_assign
id|get_memclk_frequency_10khz
c_func
(paren
)paren
suffix:semicolon
r_return
id|pxa2xx_pcmcia_set_mcxx
c_func
(paren
id|skt
comma
id|clk
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_CPU_FREQ
r_static
r_int
DECL|function|pxa2xx_pcmcia_frequency_change
id|pxa2xx_pcmcia_frequency_change
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
comma
r_int
r_int
id|val
comma
r_struct
id|cpufreq_freqs
op_star
id|freqs
)paren
(brace
macro_line|#warning &quot;it&squot;s not clear if this is right since the core CPU (N) clock has no effect on the memory (L) clock&quot;
r_switch
c_cond
(paren
id|val
)paren
(brace
r_case
id|CPUFREQ_PRECHANGE
suffix:colon
r_if
c_cond
(paren
id|freqs
op_member_access_from_pointer
r_new
OG
id|freqs-&gt;old
)paren
(brace
id|debug
c_func
(paren
id|skt
comma
l_int|2
comma
l_string|&quot;new frequency %u.%uMHz &gt; %u.%uMHz, &quot;
l_string|&quot;pre-updating&bslash;n&quot;
comma
id|freqs
op_member_access_from_pointer
r_new
op_div
l_int|1000
comma
(paren
id|freqs
op_member_access_from_pointer
r_new
op_div
l_int|100
)paren
op_mod
l_int|10
comma
id|freqs-&gt;old
op_div
l_int|1000
comma
(paren
id|freqs-&gt;old
op_div
l_int|100
)paren
op_mod
l_int|10
)paren
suffix:semicolon
id|pxa2xx_pcmcia_set_mcxx
c_func
(paren
id|skt
comma
id|freqs
op_member_access_from_pointer
r_new
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CPUFREQ_POSTCHANGE
suffix:colon
r_if
c_cond
(paren
id|freqs
op_member_access_from_pointer
r_new
OL
id|freqs-&gt;old
)paren
(brace
id|debug
c_func
(paren
id|skt
comma
l_int|2
comma
l_string|&quot;new frequency %u.%uMHz &lt; %u.%uMHz, &quot;
l_string|&quot;post-updating&bslash;n&quot;
comma
id|freqs
op_member_access_from_pointer
r_new
op_div
l_int|1000
comma
(paren
id|freqs
op_member_access_from_pointer
r_new
op_div
l_int|100
)paren
op_mod
l_int|10
comma
id|freqs-&gt;old
op_div
l_int|1000
comma
(paren
id|freqs-&gt;old
op_div
l_int|100
)paren
op_mod
l_int|10
)paren
suffix:semicolon
id|pxa2xx_pcmcia_set_mcxx
c_func
(paren
id|skt
comma
id|freqs
op_member_access_from_pointer
r_new
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|pxa2xx_drv_pcmcia_probe
r_int
id|pxa2xx_drv_pcmcia_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|pcmcia_low_level
op_star
id|ops
suffix:semicolon
r_int
id|first
comma
id|nr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|dev-&gt;platform_data
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ops
op_assign
(paren
r_struct
id|pcmcia_low_level
op_star
)paren
id|dev-&gt;platform_data
suffix:semicolon
id|first
op_assign
id|ops-&gt;first
suffix:semicolon
id|nr
op_assign
id|ops-&gt;nr
suffix:semicolon
multiline_comment|/* Provide our PXA2xx specific timing routines. */
id|ops-&gt;set_timing
op_assign
id|pxa2xx_pcmcia_set_timing
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ
id|ops-&gt;frequency_change
op_assign
id|pxa2xx_pcmcia_frequency_change
suffix:semicolon
macro_line|#endif
id|ret
op_assign
id|soc_common_drv_pcmcia_probe
c_func
(paren
id|dev
comma
id|ops
comma
id|first
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * We have at least one socket, so set MECR:CIT&n;&t;&t; * (Card Is There)&n;&t;&t; */
id|MECR
op_or_assign
id|MECR_CIT
suffix:semicolon
multiline_comment|/* Set MECR:NOS (Number Of Sockets) */
r_if
c_cond
(paren
id|nr
OG
l_int|1
)paren
id|MECR
op_or_assign
id|MECR_NOS
suffix:semicolon
r_else
id|MECR
op_and_assign
op_complement
id|MECR_NOS
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|pxa2xx_drv_pcmcia_probe
id|EXPORT_SYMBOL
c_func
(paren
id|pxa2xx_drv_pcmcia_probe
)paren
suffix:semicolon
DECL|function|pxa2xx_drv_pcmcia_suspend
r_static
r_int
id|pxa2xx_drv_pcmcia_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
comma
id|u32
id|level
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|SUSPEND_SAVE_STATE
)paren
id|ret
op_assign
id|pcmcia_socket_dev_suspend
c_func
(paren
id|dev
comma
id|state
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pxa2xx_drv_pcmcia_resume
r_static
r_int
id|pxa2xx_drv_pcmcia_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|level
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|RESUME_RESTORE_STATE
)paren
id|ret
op_assign
id|pcmcia_socket_dev_resume
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|pxa2xx_pcmcia_driver
r_static
r_struct
id|device_driver
id|pxa2xx_pcmcia_driver
op_assign
(brace
dot
id|probe
op_assign
id|pxa2xx_drv_pcmcia_probe
comma
dot
id|remove
op_assign
id|soc_common_drv_pcmcia_remove
comma
dot
id|suspend
op_assign
id|pxa2xx_drv_pcmcia_suspend
comma
dot
id|resume
op_assign
id|pxa2xx_drv_pcmcia_resume
comma
dot
id|name
op_assign
l_string|&quot;pxa2xx-pcmcia&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
)brace
suffix:semicolon
DECL|function|pxa2xx_pcmcia_init
r_static
r_int
id|__init
id|pxa2xx_pcmcia_init
c_func
(paren
r_void
)paren
(brace
r_return
id|driver_register
c_func
(paren
op_amp
id|pxa2xx_pcmcia_driver
)paren
suffix:semicolon
)brace
DECL|function|pxa2xx_pcmcia_exit
r_static
r_void
id|__exit
id|pxa2xx_pcmcia_exit
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|pxa2xx_pcmcia_driver
)paren
suffix:semicolon
)brace
DECL|variable|pxa2xx_pcmcia_init
id|module_init
c_func
(paren
id|pxa2xx_pcmcia_init
)paren
suffix:semicolon
DECL|variable|pxa2xx_pcmcia_exit
id|module_exit
c_func
(paren
id|pxa2xx_pcmcia_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Stefan Eletzhofer &lt;stefan.eletzhofer@inquant.de&gt; and Ian Molton &lt;spyro@f2s.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Linux PCMCIA Card Services: PXA2xx core socket driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
