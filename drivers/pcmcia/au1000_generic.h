multiline_comment|/*&n; * Alchemy Semi Au1000 pcmcia driver include file&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; */
macro_line|#ifndef __ASM_AU1000_PCMCIA_H
DECL|macro|__ASM_AU1000_PCMCIA_H
mdefine_line|#define __ASM_AU1000_PCMCIA_H
multiline_comment|/* include the world */
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;pcmcia/bulkmem.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &quot;cs_internal.h&quot;
DECL|macro|AU1000_PCMCIA_POLL_PERIOD
mdefine_line|#define AU1000_PCMCIA_POLL_PERIOD    (2*HZ)
DECL|macro|AU1000_PCMCIA_IO_SPEED
mdefine_line|#define AU1000_PCMCIA_IO_SPEED       (255)
DECL|macro|AU1000_PCMCIA_MEM_SPEED
mdefine_line|#define AU1000_PCMCIA_MEM_SPEED      (300)
DECL|macro|AU1X_SOCK0_IO
mdefine_line|#define AU1X_SOCK0_IO        0xF00000000
DECL|macro|AU1X_SOCK0_PHYS_ATTR
mdefine_line|#define AU1X_SOCK0_PHYS_ATTR 0xF40000000
DECL|macro|AU1X_SOCK0_PHYS_MEM
mdefine_line|#define AU1X_SOCK0_PHYS_MEM  0xF80000000
multiline_comment|/* pseudo 32 bit phys addresses, which get fixed up to the&n; * real 36 bit address in fixup_bigphys_addr() */
DECL|macro|AU1X_SOCK0_PSEUDO_PHYS_ATTR
mdefine_line|#define AU1X_SOCK0_PSEUDO_PHYS_ATTR 0xF4000000
DECL|macro|AU1X_SOCK0_PSEUDO_PHYS_MEM
mdefine_line|#define AU1X_SOCK0_PSEUDO_PHYS_MEM  0xF8000000
multiline_comment|/* pcmcia socket 1 needs external glue logic so the memory map&n; * differs from board to board.&n; */
macro_line|#if defined(CONFIG_MIPS_PB1000) || defined(CONFIG_MIPS_PB1100) || defined(CONFIG_MIPS_PB1500) || defined(CONFIG_MIPS_PB1550)
DECL|macro|AU1X_SOCK1_IO
mdefine_line|#define AU1X_SOCK1_IO        0xF08000000
DECL|macro|AU1X_SOCK1_PHYS_ATTR
mdefine_line|#define AU1X_SOCK1_PHYS_ATTR 0xF48000000
DECL|macro|AU1X_SOCK1_PHYS_MEM
mdefine_line|#define AU1X_SOCK1_PHYS_MEM  0xF88000000
DECL|macro|AU1X_SOCK1_PSEUDO_PHYS_ATTR
mdefine_line|#define AU1X_SOCK1_PSEUDO_PHYS_ATTR 0xF4800000
DECL|macro|AU1X_SOCK1_PSEUDO_PHYS_MEM
mdefine_line|#define AU1X_SOCK1_PSEUDO_PHYS_MEM  0xF8800000
macro_line|#elif defined(CONFIG_MIPS_DB1000) || defined(CONFIG_MIPS_DB1100) || defined(CONFIG_MIPS_DB1500) || defined(CONFIG_MIPS_DB1550)
DECL|macro|AU1X_SOCK1_IO
mdefine_line|#define AU1X_SOCK1_IO        0xF04000000
DECL|macro|AU1X_SOCK1_PHYS_ATTR
mdefine_line|#define AU1X_SOCK1_PHYS_ATTR 0xF44000000
DECL|macro|AU1X_SOCK1_PHYS_MEM
mdefine_line|#define AU1X_SOCK1_PHYS_MEM  0xF84000000
DECL|macro|AU1X_SOCK1_PSEUDO_PHYS_ATTR
mdefine_line|#define AU1X_SOCK1_PSEUDO_PHYS_ATTR 0xF4400000
DECL|macro|AU1X_SOCK1_PSEUDO_PHYS_MEM
mdefine_line|#define AU1X_SOCK1_PSEUDO_PHYS_MEM  0xF8400000
macro_line|#endif
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
DECL|member|wrprot
id|wrprot
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
DECL|struct|au1000_pcmcia_socket
r_struct
id|au1000_pcmcia_socket
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
DECL|member|phys_io
id|ioaddr_t
id|phys_io
suffix:semicolon
DECL|member|phys_attr
r_int
r_int
id|phys_attr
suffix:semicolon
DECL|member|phys_mem
r_int
r_int
id|phys_mem
suffix:semicolon
DECL|member|speed_io
DECL|member|speed_attr
DECL|member|speed_mem
r_int
r_int
id|speed_io
comma
id|speed_attr
comma
id|speed_mem
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
DECL|member|hw_init
r_int
(paren
op_star
id|hw_init
)paren
(paren
r_struct
id|au1000_pcmcia_socket
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
id|au1000_pcmcia_socket
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
id|au1000_pcmcia_socket
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
id|au1000_pcmcia_socket
op_star
comma
r_struct
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
id|au1000_pcmcia_socket
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
id|au1000_pcmcia_socket
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|au1x_board_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif /* __ASM_AU1000_PCMCIA_H */
eof
