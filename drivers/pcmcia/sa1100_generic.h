multiline_comment|/*&n; * linux/include/asm/arch/pcmcia.h&n; *&n; * Copyright (C) 2000 John G Dorsey &lt;john+@cs.cmu.edu&gt;&n; *&n; * This file contains definitions for the low-level SA-1100 kernel PCMCIA&n; * interface. Please see linux/Documentation/arm/SA1100/PCMCIA for details.&n; */
macro_line|#ifndef _ASM_ARCH_PCMCIA
DECL|macro|_ASM_ARCH_PCMCIA
mdefine_line|#define _ASM_ARCH_PCMCIA
multiline_comment|/* Ideally, we&squot;d support up to MAX_SOCK sockets, but the SA-1100 only&n; * has support for two. This shows up in lots of hardwired ways, such&n; * as the fact that MECR only has enough bits to configure two sockets.&n; * Since it&squot;s so entrenched in the hardware, limiting the software&n; * in this way doesn&squot;t seem too terrible.&n; */
DECL|macro|SA1100_PCMCIA_MAX_SOCK
mdefine_line|#define SA1100_PCMCIA_MAX_SOCK   (2)
DECL|struct|pcmcia_init
r_struct
id|pcmcia_init
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
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
DECL|struct|pcmcia_state_array
r_struct
id|pcmcia_state_array
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|state
r_struct
id|pcmcia_state
op_star
id|state
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcmcia_configure
r_struct
id|pcmcia_configure
(brace
DECL|member|sock
r_int
id|sock
suffix:colon
l_int|8
comma
DECL|member|vcc
id|vcc
suffix:colon
l_int|8
comma
DECL|member|vpp
id|vpp
suffix:colon
l_int|8
comma
DECL|member|output
id|output
suffix:colon
l_int|1
comma
DECL|member|speaker
id|speaker
suffix:colon
l_int|1
comma
DECL|member|reset
id|reset
suffix:colon
l_int|1
comma
DECL|member|irq
id|irq
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcmcia_irq_info
r_struct
id|pcmcia_irq_info
(brace
DECL|member|sock
r_int
r_int
id|sock
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcmcia_low_level
r_struct
id|pcmcia_low_level
(brace
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|pcmcia_init
op_star
)paren
suffix:semicolon
DECL|member|shutdown
r_int
(paren
op_star
id|shutdown
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|socket_state
r_int
(paren
op_star
id|socket_state
)paren
(paren
r_struct
id|pcmcia_state_array
op_star
)paren
suffix:semicolon
DECL|member|get_irq_info
r_int
(paren
op_star
id|get_irq_info
)paren
(paren
r_struct
id|pcmcia_irq_info
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
r_const
r_struct
id|pcmcia_configure
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;   * Enable card status IRQs on (re-)initialisation.  This can&n;   * be called at initialisation, power management event, or&n;   * pcmcia event.&n;   */
DECL|member|socket_init
r_int
(paren
op_star
id|socket_init
)paren
(paren
r_int
id|sock
)paren
suffix:semicolon
multiline_comment|/*&n;   * Disable card status IRQs and PCMCIA bus on suspend.&n;   */
DECL|member|socket_suspend
r_int
(paren
op_star
id|socket_suspend
)paren
(paren
r_int
id|sock
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|sa1100_register_pcmcia
c_func
(paren
r_struct
id|pcmcia_low_level
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sa1100_unregister_pcmcia
c_func
(paren
r_struct
id|pcmcia_low_level
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
