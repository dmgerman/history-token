multiline_comment|/*&n; * linux/drivers/pcmcia/soc_common.h&n; *&n; * Copyright (C) 2000 John G Dorsey &lt;john+@cs.cmu.edu&gt;&n; *&n; * This file contains definitions for the PCMCIA support code common to&n; * integrated SOCs like the SA-11x0 and PXA2xx microprocessors.&n; */
macro_line|#ifndef _ASM_ARCH_PCMCIA
DECL|macro|_ASM_ARCH_PCMCIA
mdefine_line|#define _ASM_ARCH_PCMCIA
multiline_comment|/* include the world */
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;pcmcia/bulkmem.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &quot;cs_internal.h&quot;
r_struct
id|device
suffix:semicolon
r_struct
id|pcmcia_low_level
suffix:semicolon
multiline_comment|/*&n; * This structure encapsulates per-socket state which we might need to&n; * use when responding to a Card Services query of some kind.&n; */
DECL|struct|soc_pcmcia_socket
r_struct
id|soc_pcmcia_socket
(brace
DECL|member|socket
r_struct
id|pcmcia_socket
id|socket
suffix:semicolon
multiline_comment|/*&n;&t; * Info from low level handler&n;&t; */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/*&n;&t; * Core PCMCIA state&n;&t; */
DECL|member|ops
r_struct
id|pcmcia_low_level
op_star
id|ops
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
DECL|member|cs_state
id|socket_state_t
id|cs_state
suffix:semicolon
DECL|member|spd_io
r_int
r_int
id|spd_io
(braket
id|MAX_IO_WIN
)braket
suffix:semicolon
DECL|member|spd_mem
r_int
r_int
id|spd_mem
(braket
id|MAX_WIN
)braket
suffix:semicolon
DECL|member|spd_attr
r_int
r_int
id|spd_attr
(braket
id|MAX_WIN
)braket
suffix:semicolon
DECL|member|res_skt
r_struct
id|resource
id|res_skt
suffix:semicolon
DECL|member|res_io
r_struct
id|resource
id|res_io
suffix:semicolon
DECL|member|res_mem
r_struct
id|resource
id|res_mem
suffix:semicolon
DECL|member|res_attr
r_struct
id|resource
id|res_attr
suffix:semicolon
DECL|member|virt_io
r_void
op_star
id|virt_io
suffix:semicolon
DECL|member|irq_state
r_int
r_int
id|irq_state
suffix:semicolon
DECL|member|poll_timer
r_struct
id|timer_list
id|poll_timer
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcmcia_state
r_struct
id|pcmcia_state
(brace
DECL|member|detect
r_int
id|detect
suffix:colon
l_int|1
comma
DECL|member|ready
id|ready
suffix:colon
l_int|1
comma
DECL|member|bvd1
id|bvd1
suffix:colon
l_int|1
comma
DECL|member|bvd2
id|bvd2
suffix:colon
l_int|1
comma
DECL|member|wrprot
id|wrprot
suffix:colon
l_int|1
comma
DECL|member|vs_3v
id|vs_3v
suffix:colon
l_int|1
comma
DECL|member|vs_Xv
id|vs_Xv
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcmcia_low_level
r_struct
id|pcmcia_low_level
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
multiline_comment|/* first socket in system */
DECL|member|first
r_int
id|first
suffix:semicolon
multiline_comment|/* nr of sockets */
DECL|member|nr
r_int
id|nr
suffix:semicolon
DECL|member|hw_init
r_int
(paren
op_star
id|hw_init
)paren
(paren
r_struct
id|soc_pcmcia_socket
op_star
)paren
suffix:semicolon
DECL|member|hw_shutdown
r_void
(paren
op_star
id|hw_shutdown
)paren
(paren
r_struct
id|soc_pcmcia_socket
op_star
)paren
suffix:semicolon
DECL|member|socket_state
r_void
(paren
op_star
id|socket_state
)paren
(paren
r_struct
id|soc_pcmcia_socket
op_star
comma
r_struct
id|pcmcia_state
op_star
)paren
suffix:semicolon
DECL|member|configure_socket
r_int
(paren
op_star
id|configure_socket
)paren
(paren
r_struct
id|soc_pcmcia_socket
op_star
comma
r_const
id|socket_state_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Enable card status IRQs on (re-)initialisation.  This can&n;&t; * be called at initialisation, power management event, or&n;&t; * pcmcia event.&n;&t; */
DECL|member|socket_init
r_void
(paren
op_star
id|socket_init
)paren
(paren
r_struct
id|soc_pcmcia_socket
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable card status IRQs and PCMCIA bus on suspend.&n;&t; */
DECL|member|socket_suspend
r_void
(paren
op_star
id|socket_suspend
)paren
(paren
r_struct
id|soc_pcmcia_socket
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Hardware specific timing routines.&n;&t; * If provided, the get_timing routine overrides the SOC default.&n;&t; */
DECL|member|get_timing
r_int
r_int
(paren
op_star
id|get_timing
)paren
(paren
r_struct
id|soc_pcmcia_socket
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|set_timing
r_int
(paren
op_star
id|set_timing
)paren
(paren
r_struct
id|soc_pcmcia_socket
op_star
)paren
suffix:semicolon
DECL|member|show_timing
r_int
(paren
op_star
id|show_timing
)paren
(paren
r_struct
id|soc_pcmcia_socket
op_star
comma
r_char
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcmcia_irqs
r_struct
id|pcmcia_irqs
(brace
DECL|member|sock
r_int
id|sock
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|str
r_const
r_char
op_star
id|str
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|soc_pcmcia_request_irqs
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
comma
r_struct
id|pcmcia_irqs
op_star
id|irqs
comma
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_void
id|soc_pcmcia_free_irqs
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
comma
r_struct
id|pcmcia_irqs
op_star
id|irqs
comma
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_void
id|soc_pcmcia_disable_irqs
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
comma
r_struct
id|pcmcia_irqs
op_star
id|irqs
comma
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_void
id|soc_pcmcia_enable_irqs
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
comma
r_struct
id|pcmcia_irqs
op_star
id|irqs
comma
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_struct
id|list_head
id|soc_pcmcia_sockets
suffix:semicolon
r_extern
r_struct
id|semaphore
id|soc_pcmcia_sockets_lock
suffix:semicolon
r_extern
r_int
id|soc_common_drv_pcmcia_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|pcmcia_low_level
op_star
id|ops
comma
r_int
id|first
comma
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_int
id|soc_common_drv_pcmcia_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_extern
r_void
id|soc_pcmcia_debug
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
comma
r_const
r_char
op_star
id|func
comma
r_int
id|lvl
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|macro|debug
mdefine_line|#define debug(skt, lvl, fmt, arg...) &bslash;&n;&t;soc_pcmcia_debug(skt, __func__, lvl, fmt , ## arg)
macro_line|#else
DECL|macro|debug
mdefine_line|#define debug(skt, lvl, fmt, arg...) do { } while (0)
macro_line|#endif
multiline_comment|/*&n; * The PC Card Standard, Release 7, section 4.13.4, says that twIORD&n; * has a minimum value of 165ns. Section 4.13.5 says that twIOWR has&n; * a minimum value of 165ns, as well. Section 4.7.2 (describing&n; * common and attribute memory write timing) says that twWE has a&n; * minimum value of 150ns for a 250ns cycle time (for 5V operation;&n; * see section 4.7.4), or 300ns for a 600ns cycle time (for 3.3V&n; * operation, also section 4.7.4). Section 4.7.3 says that taOE&n; * has a maximum value of 150ns for a 300ns cycle time (for 5V&n; * operation), or 300ns for a 600ns cycle time (for 3.3V operation).&n; *&n; * When configuring memory maps, Card Services appears to adopt the policy&n; * that a memory access time of &quot;0&quot; means &quot;use the default.&quot; The default&n; * PCMCIA I/O command width time is 165ns. The default PCMCIA 5V attribute&n; * and memory command width time is 150ns; the PCMCIA 3.3V attribute and&n; * memory command width time is 300ns.&n; */
DECL|macro|SOC_PCMCIA_IO_ACCESS
mdefine_line|#define SOC_PCMCIA_IO_ACCESS&t;&t;(165)
DECL|macro|SOC_PCMCIA_5V_MEM_ACCESS
mdefine_line|#define SOC_PCMCIA_5V_MEM_ACCESS&t;(150)
DECL|macro|SOC_PCMCIA_3V_MEM_ACCESS
mdefine_line|#define SOC_PCMCIA_3V_MEM_ACCESS&t;(300)
DECL|macro|SOC_PCMCIA_ATTR_MEM_ACCESS
mdefine_line|#define SOC_PCMCIA_ATTR_MEM_ACCESS&t;(300)
multiline_comment|/*&n; * The socket driver actually works nicely in interrupt-driven form,&n; * so the (relatively infrequent) polling is &quot;just to be sure.&quot;&n; */
DECL|macro|SOC_PCMCIA_POLL_PERIOD
mdefine_line|#define SOC_PCMCIA_POLL_PERIOD    (2*HZ)
multiline_comment|/* I/O pins replacing memory pins&n; * (PCMCIA System Architecture, 2nd ed., by Don Anderson, p.75)&n; *&n; * These signals change meaning when going from memory-only to&n; * memory-or-I/O interface:&n; */
DECL|macro|iostschg
mdefine_line|#define iostschg bvd1
DECL|macro|iospkr
mdefine_line|#define iospkr   bvd2
macro_line|#endif
eof
