multiline_comment|/*&n; * vrc4171_card.c, NEC VRC4171 Card Controller driver for Socket Services.&n; *&n; * Copyright (C) 2003  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/vr41xx/vrc4171.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &quot;i82365.h&quot;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NEC VRC4171 Card Controllers driver for Socket Services&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|CARD_MAX_SLOTS
mdefine_line|#define CARD_MAX_SLOTS&t;&t;2
DECL|macro|CARD_SLOTA
mdefine_line|#define CARD_SLOTA&t;&t;0
DECL|macro|CARD_SLOTB
mdefine_line|#define CARD_SLOTB&t;&t;1
DECL|macro|CARD_SLOTB_OFFSET
mdefine_line|#define CARD_SLOTB_OFFSET&t;0x40
DECL|macro|CARD_MEM_START
mdefine_line|#define CARD_MEM_START&t;&t;0x10000000
DECL|macro|CARD_MEM_END
mdefine_line|#define CARD_MEM_END&t;&t;0x13ffffff
DECL|macro|CARD_MAX_MEM_OFFSET
mdefine_line|#define CARD_MAX_MEM_OFFSET&t;0x3ffffff
DECL|macro|CARD_MAX_MEM_SPEED
mdefine_line|#define CARD_MAX_MEM_SPEED&t;1000
DECL|macro|CARD_CONTROLLER_INDEX
mdefine_line|#define CARD_CONTROLLER_INDEX&t;0x03e0
DECL|macro|CARD_CONTROLLER_DATA
mdefine_line|#define CARD_CONTROLLER_DATA&t;0x03e1
DECL|macro|CARD_CONTROLLER_SIZE
mdefine_line|#define CARD_CONTROLLER_SIZE&t;2
multiline_comment|/* Power register */
DECL|macro|VPP_GET_VCC
mdefine_line|#define VPP_GET_VCC&t;&t;0x01
DECL|macro|POWER_ENABLE
mdefine_line|#define POWER_ENABLE&t;&t;0x10
DECL|macro|CARD_VOLTAGE_SENSE
mdefine_line|#define CARD_VOLTAGE_SENSE&t;0x1f
DECL|macro|VCC_3VORXV_CAPABLE
mdefine_line|#define VCC_3VORXV_CAPABLE&t;0x00
DECL|macro|VCC_XV_ONLY
mdefine_line|#define VCC_XV_ONLY&t;&t;0x01
DECL|macro|VCC_3V_CAPABLE
mdefine_line|#define VCC_3V_CAPABLE&t;0x02
DECL|macro|VCC_5V_ONLY
mdefine_line|#define VCC_5V_ONLY&t;&t;0x03
DECL|macro|CARD_VOLTAGE_SELECT
mdefine_line|#define CARD_VOLTAGE_SELECT&t;0x2f
DECL|macro|VCC_3V
mdefine_line|#define VCC_3V&t;&t;0x01
DECL|macro|VCC_5V
mdefine_line|#define VCC_5V&t;&t;0x00
DECL|macro|VCC_XV
mdefine_line|#define VCC_XV&t;&t;0x02
DECL|macro|VCC_STATUS_3V
mdefine_line|#define VCC_STATUS_3V&t;&t;0x02
DECL|macro|VCC_STATUS_5V
mdefine_line|#define VCC_STATUS_5V&t;&t;0x01
DECL|macro|VCC_STATUS_XV
mdefine_line|#define VCC_STATUS_XV&t;&t;0x03
DECL|macro|GLOBAL_CONTROL
mdefine_line|#define GLOBAL_CONTROL&t;&t;0x1e
DECL|macro|EXWRBK
mdefine_line|#define EXWRBK&t;&t;0x04
DECL|macro|IRQPM_EN
mdefine_line|#define IRQPM_EN&t;&t;0x08
DECL|macro|CLRPMIRQ
mdefine_line|#define CLRPMIRQ&t;&t;0x10
DECL|macro|IO_MAX_MAPS
mdefine_line|#define IO_MAX_MAPS&t;2
DECL|macro|MEM_MAX_MAPS
mdefine_line|#define MEM_MAX_MAPS&t;5
r_enum
(brace
DECL|enumerator|SLOT_PROBE
id|SLOT_PROBE
op_assign
l_int|0
comma
DECL|enumerator|SLOT_NOPROBE_IO
id|SLOT_NOPROBE_IO
comma
DECL|enumerator|SLOT_NOPROBE_MEM
id|SLOT_NOPROBE_MEM
comma
DECL|enumerator|SLOT_NOPROBE_ALL
id|SLOT_NOPROBE_ALL
)brace
suffix:semicolon
DECL|struct|vrc4171_socket
r_typedef
r_struct
id|vrc4171_socket
(brace
DECL|member|noprobe
r_int
id|noprobe
suffix:semicolon
DECL|member|pcmcia_socket
r_struct
id|pcmcia_socket
id|pcmcia_socket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|csc_irq
r_int
id|csc_irq
suffix:semicolon
DECL|member|io_irq
r_int
id|io_irq
suffix:semicolon
DECL|typedef|vrc4171_socket_t
)brace
id|vrc4171_socket_t
suffix:semicolon
DECL|variable|vrc4171_sockets
r_static
id|vrc4171_socket_t
id|vrc4171_sockets
(braket
id|CARD_MAX_SLOTS
)braket
suffix:semicolon
DECL|variable|vrc4171_slotb
r_static
r_int
id|vrc4171_slotb
op_assign
id|SLOTB_IS_NONE
suffix:semicolon
DECL|variable|vrc4171_irq
r_static
r_int
r_int
id|vrc4171_irq
suffix:semicolon
DECL|variable|vrc4171_irq_mask
r_static
r_uint16
id|vrc4171_irq_mask
op_assign
l_int|0xdeb8
suffix:semicolon
DECL|function|exca_read_byte
r_static
r_inline
r_uint8
id|exca_read_byte
c_func
(paren
r_int
id|slot
comma
r_uint8
id|index
)paren
(brace
r_if
c_cond
(paren
id|slot
op_eq
id|CARD_SLOTB
)paren
id|index
op_add_assign
id|CARD_SLOTB_OFFSET
suffix:semicolon
id|outb
c_func
(paren
id|index
comma
id|CARD_CONTROLLER_INDEX
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|CARD_CONTROLLER_DATA
)paren
suffix:semicolon
)brace
DECL|function|exca_read_word
r_static
r_inline
r_uint16
id|exca_read_word
c_func
(paren
r_int
id|slot
comma
r_uint8
id|index
)paren
(brace
r_uint16
id|data
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
id|CARD_SLOTB
)paren
id|index
op_add_assign
id|CARD_SLOTB_OFFSET
suffix:semicolon
id|outb
c_func
(paren
id|index
op_increment
comma
id|CARD_CONTROLLER_INDEX
)paren
suffix:semicolon
id|data
op_assign
id|inb
c_func
(paren
id|CARD_CONTROLLER_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|index
comma
id|CARD_CONTROLLER_INDEX
)paren
suffix:semicolon
id|data
op_or_assign
(paren
(paren
r_uint16
)paren
id|inb
c_func
(paren
id|CARD_CONTROLLER_DATA
)paren
)paren
op_lshift
l_int|8
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|exca_write_byte
r_static
r_inline
r_uint8
id|exca_write_byte
c_func
(paren
r_int
id|slot
comma
r_uint8
id|index
comma
r_uint8
id|data
)paren
(brace
r_if
c_cond
(paren
id|slot
op_eq
id|CARD_SLOTB
)paren
id|index
op_add_assign
id|CARD_SLOTB_OFFSET
suffix:semicolon
id|outb
c_func
(paren
id|index
comma
id|CARD_CONTROLLER_INDEX
)paren
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|CARD_CONTROLLER_DATA
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|exca_write_word
r_static
r_inline
r_uint16
id|exca_write_word
c_func
(paren
r_int
id|slot
comma
r_uint8
id|index
comma
r_uint16
id|data
)paren
(brace
r_if
c_cond
(paren
id|slot
op_eq
id|CARD_SLOTB
)paren
id|index
op_add_assign
id|CARD_SLOTB_OFFSET
suffix:semicolon
id|outb
c_func
(paren
id|index
op_increment
comma
id|CARD_CONTROLLER_INDEX
)paren
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|CARD_CONTROLLER_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|index
comma
id|CARD_CONTROLLER_INDEX
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
r_uint8
)paren
(paren
id|data
op_rshift
l_int|8
)paren
comma
id|CARD_CONTROLLER_DATA
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|search_nonuse_irq
r_static
r_inline
r_int
id|search_nonuse_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|vrc4171_irq_mask
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|vrc4171_irq_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|pccard_init
r_static
r_int
id|pccard_init
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
)paren
(brace
id|vrc4171_socket_t
op_star
id|socket
suffix:semicolon
r_int
r_int
id|slot
suffix:semicolon
id|sock-&gt;features
op_or_assign
id|SS_CAP_PCCARD
op_or
id|SS_CAP_PAGE_REGS
suffix:semicolon
id|sock-&gt;irq_mask
op_assign
l_int|0
suffix:semicolon
id|sock-&gt;map_size
op_assign
l_int|0x1000
suffix:semicolon
id|sock-&gt;pci_irq
op_assign
id|vrc4171_irq
suffix:semicolon
id|slot
op_assign
id|sock-&gt;sock
suffix:semicolon
id|socket
op_assign
op_amp
id|vrc4171_sockets
(braket
id|slot
)braket
suffix:semicolon
id|socket-&gt;csc_irq
op_assign
id|search_nonuse_irq
c_func
(paren
)paren
suffix:semicolon
id|socket-&gt;io_irq
op_assign
id|search_nonuse_irq
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pccard_suspend
r_static
r_int
id|pccard_suspend
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|pccard_get_status
r_static
r_int
id|pccard_get_status
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
id|u_int
op_star
id|value
)paren
(brace
r_int
r_int
id|slot
suffix:semicolon
r_uint8
id|status
comma
id|sense
suffix:semicolon
id|u_int
id|val
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sock
op_eq
l_int|NULL
op_logical_or
id|sock-&gt;sock
op_ge
id|CARD_MAX_SLOTS
op_logical_or
id|value
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|slot
op_assign
id|sock-&gt;sock
suffix:semicolon
id|status
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_INTCTL
)paren
op_amp
id|I365_PC_IOCARD
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|I365_CS_STSCHG
)paren
id|val
op_or_assign
id|SS_STSCHG
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|I365_CS_BVD1
)paren
)paren
id|val
op_or_assign
id|SS_BATDEAD
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|status
op_amp
(paren
id|I365_CS_BVD1
op_or
id|I365_CS_BVD2
)paren
)paren
op_eq
id|I365_CS_BVD1
)paren
id|val
op_or_assign
id|SS_BATWARN
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|status
op_amp
id|I365_CS_DETECT
)paren
op_eq
id|I365_CS_DETECT
)paren
id|val
op_or_assign
id|SS_DETECT
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|I365_CS_WRPROT
)paren
id|val
op_or_assign
id|SS_WRPROT
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|I365_CS_READY
)paren
id|val
op_or_assign
id|SS_READY
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|I365_CS_POWERON
)paren
id|val
op_or_assign
id|SS_POWERON
suffix:semicolon
id|sense
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|CARD_VOLTAGE_SENSE
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sense
)paren
(brace
r_case
id|VCC_3VORXV_CAPABLE
suffix:colon
id|val
op_or_assign
id|SS_3VCARD
op_or
id|SS_XVCARD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VCC_XV_ONLY
suffix:colon
id|val
op_or_assign
id|SS_XVCARD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VCC_3V_CAPABLE
suffix:colon
id|val
op_or_assign
id|SS_3VCARD
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* 5V only */
r_break
suffix:semicolon
)brace
op_star
id|value
op_assign
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_Vcc_value
r_static
r_inline
id|u_char
id|get_Vcc_value
c_func
(paren
r_uint8
id|voltage
)paren
(brace
r_switch
c_cond
(paren
id|voltage
)paren
(brace
r_case
id|VCC_STATUS_3V
suffix:colon
r_return
l_int|33
suffix:semicolon
r_case
id|VCC_STATUS_5V
suffix:colon
r_return
l_int|50
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
DECL|function|get_Vpp_value
r_static
r_inline
id|u_char
id|get_Vpp_value
c_func
(paren
r_uint8
id|power
comma
id|u_char
id|Vcc
)paren
(brace
r_if
c_cond
(paren
(paren
id|power
op_amp
l_int|0x03
)paren
op_eq
l_int|0x01
op_logical_or
(paren
id|power
op_amp
l_int|0x03
)paren
op_eq
l_int|0x02
)paren
r_return
id|Vcc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pccard_get_socket
r_static
r_int
id|pccard_get_socket
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
id|socket_state_t
op_star
id|state
)paren
(brace
r_int
r_int
id|slot
suffix:semicolon
r_uint8
id|power
comma
id|voltage
comma
id|control
comma
id|cscint
suffix:semicolon
r_if
c_cond
(paren
id|sock
op_eq
l_int|NULL
op_logical_or
id|sock-&gt;sock
op_ge
id|CARD_MAX_SLOTS
op_logical_or
id|state
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|slot
op_assign
id|sock-&gt;sock
suffix:semicolon
id|power
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_POWER
)paren
suffix:semicolon
id|voltage
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|CARD_VOLTAGE_SELECT
)paren
suffix:semicolon
id|state-&gt;Vcc
op_assign
id|get_Vcc_value
c_func
(paren
id|voltage
)paren
suffix:semicolon
id|state-&gt;Vpp
op_assign
id|get_Vpp_value
c_func
(paren
id|power
comma
id|state-&gt;Vcc
)paren
suffix:semicolon
id|state-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|power
op_amp
id|POWER_ENABLE
)paren
id|state-&gt;flags
op_or_assign
id|SS_PWR_AUTO
suffix:semicolon
r_if
c_cond
(paren
id|power
op_amp
id|I365_PWR_OUT
)paren
id|state-&gt;flags
op_or_assign
id|SS_OUTPUT_ENA
suffix:semicolon
id|control
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_INTCTL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|control
op_amp
id|I365_PC_IOCARD
)paren
id|state-&gt;flags
op_or_assign
id|SS_IOCARD
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|control
op_amp
id|I365_PC_RESET
)paren
)paren
id|state-&gt;flags
op_or_assign
id|SS_RESET
suffix:semicolon
id|cscint
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_CSCINT
)paren
suffix:semicolon
id|state-&gt;csc_mask
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|SS_IOCARD
)paren
(brace
r_if
c_cond
(paren
id|cscint
op_amp
id|I365_CSC_STSCHG
)paren
id|state-&gt;flags
op_or_assign
id|SS_STSCHG
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|cscint
op_amp
id|I365_CSC_BVD1
)paren
id|state-&gt;csc_mask
op_or_assign
id|SS_BATDEAD
suffix:semicolon
r_if
c_cond
(paren
id|cscint
op_amp
id|I365_CSC_BVD2
)paren
id|state-&gt;csc_mask
op_or_assign
id|SS_BATWARN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cscint
op_amp
id|I365_CSC_READY
)paren
id|state-&gt;csc_mask
op_or_assign
id|SS_READY
suffix:semicolon
r_if
c_cond
(paren
id|cscint
op_amp
id|I365_CSC_DETECT
)paren
id|state-&gt;csc_mask
op_or_assign
id|SS_DETECT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_Vcc_value
r_static
r_inline
r_uint8
id|set_Vcc_value
c_func
(paren
id|u_char
id|Vcc
)paren
(brace
r_switch
c_cond
(paren
id|Vcc
)paren
(brace
r_case
l_int|33
suffix:colon
r_return
id|VCC_3V
suffix:semicolon
r_case
l_int|50
suffix:colon
r_return
id|VCC_5V
suffix:semicolon
)brace
multiline_comment|/* Small voltage is chosen for safety. */
r_return
id|VCC_3V
suffix:semicolon
)brace
DECL|function|pccard_set_socket
r_static
r_int
id|pccard_set_socket
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
id|socket_state_t
op_star
id|state
)paren
(brace
id|vrc4171_socket_t
op_star
id|socket
suffix:semicolon
r_int
r_int
id|slot
suffix:semicolon
r_uint8
id|voltage
comma
id|power
comma
id|control
comma
id|cscint
suffix:semicolon
r_if
c_cond
(paren
id|sock
op_eq
l_int|NULL
op_logical_or
id|sock-&gt;sock
op_ge
id|CARD_MAX_SLOTS
op_logical_or
(paren
id|state-&gt;Vpp
op_ne
id|state-&gt;Vcc
op_logical_and
id|state-&gt;Vpp
op_ne
l_int|0
)paren
op_logical_or
(paren
id|state-&gt;Vcc
op_ne
l_int|50
op_logical_and
id|state-&gt;Vcc
op_ne
l_int|33
op_logical_and
id|state-&gt;Vcc
op_ne
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|slot
op_assign
id|sock-&gt;sock
suffix:semicolon
id|socket
op_assign
op_amp
id|vrc4171_sockets
(braket
id|slot
)braket
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|sock-&gt;lock
)paren
suffix:semicolon
id|voltage
op_assign
id|set_Vcc_value
c_func
(paren
id|state-&gt;Vcc
)paren
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|CARD_VOLTAGE_SELECT
comma
id|voltage
)paren
suffix:semicolon
id|power
op_assign
id|POWER_ENABLE
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;Vpp
op_eq
id|state-&gt;Vcc
)paren
id|power
op_or_assign
id|VPP_GET_VCC
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|SS_OUTPUT_ENA
)paren
id|power
op_or_assign
id|I365_PWR_OUT
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_POWER
comma
id|power
)paren
suffix:semicolon
id|control
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;io_irq
op_ne
l_int|0
)paren
id|control
op_or_assign
id|socket-&gt;io_irq
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|SS_IOCARD
)paren
id|control
op_or_assign
id|I365_PC_IOCARD
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|SS_RESET
)paren
id|control
op_and_assign
op_complement
id|I365_PC_RESET
suffix:semicolon
r_else
id|control
op_or_assign
id|I365_PC_RESET
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_INTCTL
comma
id|control
)paren
suffix:semicolon
id|cscint
op_assign
l_int|0
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_CSCINT
comma
id|cscint
)paren
suffix:semicolon
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_CSC
)paren
suffix:semicolon
multiline_comment|/* clear CardStatus change */
r_if
c_cond
(paren
id|state-&gt;csc_mask
op_ne
l_int|0
)paren
id|cscint
op_or_assign
id|socket-&gt;csc_irq
op_lshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|SS_IOCARD
)paren
(brace
r_if
c_cond
(paren
id|state-&gt;csc_mask
op_amp
id|SS_STSCHG
)paren
id|cscint
op_or_assign
id|I365_CSC_STSCHG
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|state-&gt;csc_mask
op_amp
id|SS_BATDEAD
)paren
id|cscint
op_or_assign
id|I365_CSC_BVD1
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;csc_mask
op_amp
id|SS_BATWARN
)paren
id|cscint
op_or_assign
id|I365_CSC_BVD2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state-&gt;csc_mask
op_amp
id|SS_READY
)paren
id|cscint
op_or_assign
id|I365_CSC_READY
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;csc_mask
op_amp
id|SS_DETECT
)paren
id|cscint
op_or_assign
id|I365_CSC_DETECT
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_CSCINT
comma
id|cscint
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|sock-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pccard_set_io_map
r_static
r_int
id|pccard_set_io_map
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
r_struct
id|pccard_io_map
op_star
id|io
)paren
(brace
r_int
r_int
id|slot
suffix:semicolon
r_uint8
id|ioctl
comma
id|addrwin
suffix:semicolon
id|u_char
id|map
suffix:semicolon
r_if
c_cond
(paren
id|sock
op_eq
l_int|NULL
op_logical_or
id|sock-&gt;sock
op_ge
id|CARD_MAX_SLOTS
op_logical_or
id|io
op_eq
l_int|NULL
op_logical_or
id|io-&gt;map
op_ge
id|IO_MAX_MAPS
op_logical_or
id|io-&gt;start
OG
l_int|0xffff
op_logical_or
id|io-&gt;stop
OG
l_int|0xffff
op_logical_or
id|io-&gt;start
OG
id|io-&gt;stop
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|slot
op_assign
id|sock-&gt;sock
suffix:semicolon
id|map
op_assign
id|io-&gt;map
suffix:semicolon
id|addrwin
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_ADDRWIN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addrwin
op_amp
id|I365_ENA_IO
c_func
(paren
id|map
)paren
)paren
(brace
id|addrwin
op_and_assign
op_complement
id|I365_ENA_IO
c_func
(paren
id|map
)paren
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_ADDRWIN
comma
id|addrwin
)paren
suffix:semicolon
)brace
id|exca_write_word
c_func
(paren
id|slot
comma
id|I365_IO
c_func
(paren
id|map
)paren
op_plus
id|I365_W_START
comma
id|io-&gt;start
)paren
suffix:semicolon
id|exca_write_word
c_func
(paren
id|slot
comma
id|I365_IO
c_func
(paren
id|map
)paren
op_plus
id|I365_W_STOP
comma
id|io-&gt;stop
)paren
suffix:semicolon
id|ioctl
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;speed
OG
l_int|0
)paren
id|ioctl
op_or_assign
id|I365_IOCTL_WAIT
c_func
(paren
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;flags
op_amp
id|MAP_16BIT
)paren
id|ioctl
op_or_assign
id|I365_IOCTL_16BIT
c_func
(paren
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;flags
op_amp
id|MAP_AUTOSZ
)paren
id|ioctl
op_or_assign
id|I365_IOCTL_IOCS16
c_func
(paren
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;flags
op_amp
id|MAP_0WS
)paren
id|ioctl
op_or_assign
id|I365_IOCTL_0WS
c_func
(paren
id|map
)paren
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_IOCTL
comma
id|ioctl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;flags
op_amp
id|MAP_ACTIVE
)paren
(brace
id|addrwin
op_or_assign
id|I365_ENA_IO
c_func
(paren
id|map
)paren
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_ADDRWIN
comma
id|addrwin
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pccard_set_mem_map
r_static
r_int
id|pccard_set_mem_map
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
r_struct
id|pccard_mem_map
op_star
id|mem
)paren
(brace
r_int
r_int
id|slot
suffix:semicolon
r_uint16
id|start
comma
id|stop
comma
id|offset
suffix:semicolon
r_uint8
id|addrwin
suffix:semicolon
id|u_char
id|map
suffix:semicolon
r_if
c_cond
(paren
id|sock
op_eq
l_int|NULL
op_logical_or
id|sock-&gt;sock
op_ge
id|CARD_MAX_SLOTS
op_logical_or
id|mem
op_eq
l_int|NULL
op_logical_or
id|mem-&gt;map
op_ge
id|MEM_MAX_MAPS
op_logical_or
id|mem-&gt;sys_start
template_param
id|CARD_MEM_END
op_logical_or
id|mem-&gt;sys_stop
template_param
id|CARD_MEM_END
op_logical_or
id|mem-&gt;sys_start
OG
id|mem-&gt;sys_stop
op_logical_or
id|mem-&gt;card_start
OG
id|CARD_MAX_MEM_OFFSET
op_logical_or
id|mem-&gt;speed
OG
id|CARD_MAX_MEM_SPEED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|slot
op_assign
id|sock-&gt;sock
suffix:semicolon
id|map
op_assign
id|mem-&gt;map
suffix:semicolon
id|addrwin
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_ADDRWIN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addrwin
op_amp
id|I365_ENA_MEM
c_func
(paren
id|map
)paren
)paren
(brace
id|addrwin
op_and_assign
op_complement
id|I365_ENA_MEM
c_func
(paren
id|map
)paren
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_ADDRWIN
comma
id|addrwin
)paren
suffix:semicolon
)brace
id|start
op_assign
(paren
id|mem-&gt;sys_start
op_rshift
l_int|12
)paren
op_amp
l_int|0x3fff
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|MAP_16BIT
)paren
id|start
op_or_assign
id|I365_MEM_16BIT
suffix:semicolon
id|exca_write_word
c_func
(paren
id|slot
comma
id|I365_MEM
c_func
(paren
id|map
)paren
op_plus
id|I365_W_START
comma
id|start
)paren
suffix:semicolon
id|stop
op_assign
(paren
id|mem-&gt;sys_stop
op_rshift
l_int|12
)paren
op_amp
l_int|0x3fff
suffix:semicolon
r_switch
c_cond
(paren
id|mem-&gt;speed
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|stop
op_or_assign
id|I365_MEM_WS0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|stop
op_or_assign
id|I365_MEM_WS1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|stop
op_or_assign
id|I365_MEM_WS0
op_or
id|I365_MEM_WS1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|exca_write_word
c_func
(paren
id|slot
comma
id|I365_MEM
c_func
(paren
id|map
)paren
op_plus
id|I365_W_STOP
comma
id|stop
)paren
suffix:semicolon
id|offset
op_assign
(paren
id|mem-&gt;card_start
op_rshift
l_int|12
)paren
op_amp
l_int|0x3fff
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|MAP_ATTRIB
)paren
id|offset
op_or_assign
id|I365_MEM_REG
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|MAP_WRPROT
)paren
id|offset
op_or_assign
id|I365_MEM_WRPROT
suffix:semicolon
id|exca_write_word
c_func
(paren
id|slot
comma
id|I365_MEM
c_func
(paren
id|map
)paren
op_plus
id|I365_W_OFF
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|MAP_ACTIVE
)paren
(brace
id|addrwin
op_or_assign
id|I365_ENA_MEM
c_func
(paren
id|map
)paren
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_ADDRWIN
comma
id|addrwin
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vrc4171_pccard_operations
r_static
r_struct
id|pccard_operations
id|vrc4171_pccard_operations
op_assign
(brace
dot
id|init
op_assign
id|pccard_init
comma
dot
id|suspend
op_assign
id|pccard_suspend
comma
dot
id|get_status
op_assign
id|pccard_get_status
comma
dot
id|get_socket
op_assign
id|pccard_get_socket
comma
dot
id|set_socket
op_assign
id|pccard_set_socket
comma
dot
id|set_io_map
op_assign
id|pccard_set_io_map
comma
dot
id|set_mem_map
op_assign
id|pccard_set_mem_map
comma
)brace
suffix:semicolon
DECL|function|get_events
r_static
r_inline
r_int
r_int
id|get_events
c_func
(paren
r_int
id|slot
)paren
(brace
r_int
r_int
id|events
op_assign
l_int|0
suffix:semicolon
r_uint8
id|status
comma
id|csc
suffix:semicolon
id|status
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_STATUS
)paren
suffix:semicolon
id|csc
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_CSC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_INTCTL
)paren
op_amp
id|I365_PC_IOCARD
)paren
(brace
r_if
c_cond
(paren
(paren
id|csc
op_amp
id|I365_CSC_STSCHG
)paren
op_logical_and
(paren
id|status
op_amp
id|I365_CS_STSCHG
)paren
)paren
id|events
op_or_assign
id|SS_STSCHG
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|csc
op_amp
(paren
id|I365_CSC_BVD1
op_or
id|I365_CSC_BVD2
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|I365_CS_BVD1
)paren
)paren
id|events
op_or_assign
id|SS_BATDEAD
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|status
op_amp
(paren
id|I365_CS_BVD1
op_or
id|I365_CS_BVD2
)paren
)paren
op_eq
id|I365_CS_BVD1
)paren
id|events
op_or_assign
id|SS_BATWARN
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|csc
op_amp
id|I365_CSC_READY
)paren
op_logical_and
(paren
id|status
op_amp
id|I365_CS_READY
)paren
)paren
id|events
op_or_assign
id|SS_READY
suffix:semicolon
r_if
c_cond
(paren
(paren
id|csc
op_amp
id|I365_CSC_DETECT
)paren
op_logical_and
(paren
(paren
id|status
op_amp
id|I365_CS_DETECT
)paren
op_eq
id|I365_CS_DETECT
)paren
)paren
id|events
op_or_assign
id|SS_DETECT
suffix:semicolon
r_return
id|events
suffix:semicolon
)brace
DECL|function|pccard_interrupt
r_static
id|irqreturn_t
id|pccard_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|vrc4171_socket_t
op_star
id|socket
suffix:semicolon
r_int
r_int
id|events
suffix:semicolon
id|irqreturn_t
id|retval
op_assign
id|IRQ_NONE
suffix:semicolon
r_uint16
id|status
suffix:semicolon
id|status
op_assign
id|vrc4171_get_irq_status
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IRQ_A
)paren
(brace
id|socket
op_assign
op_amp
id|vrc4171_sockets
(braket
id|CARD_SLOTA
)braket
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;noprobe
op_eq
id|SLOT_PROBE
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
id|socket-&gt;csc_irq
)paren
)paren
(brace
id|events
op_assign
id|get_events
c_func
(paren
id|CARD_SLOTA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|events
op_ne
l_int|0
)paren
(brace
id|pcmcia_parse_events
c_func
(paren
op_amp
id|socket-&gt;pcmcia_socket
comma
id|events
)paren
suffix:semicolon
id|retval
op_assign
id|IRQ_HANDLED
suffix:semicolon
)brace
)brace
)brace
)brace
r_if
c_cond
(paren
id|status
op_amp
id|IRQ_B
)paren
(brace
id|socket
op_assign
op_amp
id|vrc4171_sockets
(braket
id|CARD_SLOTB
)braket
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;noprobe
op_eq
id|SLOT_PROBE
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
id|socket-&gt;csc_irq
)paren
)paren
(brace
id|events
op_assign
id|get_events
c_func
(paren
id|CARD_SLOTB
)paren
suffix:semicolon
r_if
c_cond
(paren
id|events
op_ne
l_int|0
)paren
(brace
id|pcmcia_parse_events
c_func
(paren
op_amp
id|socket-&gt;pcmcia_socket
comma
id|events
)paren
suffix:semicolon
id|retval
op_assign
id|IRQ_HANDLED
suffix:semicolon
)brace
)brace
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|reserve_using_irq
r_static
r_inline
r_void
id|reserve_using_irq
c_func
(paren
r_int
id|slot
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
id|irq
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_INTCTL
)paren
suffix:semicolon
id|irq
op_and_assign
l_int|0x0f
suffix:semicolon
id|vrc4171_irq_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
id|irq
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_CSCINT
)paren
suffix:semicolon
id|irq
op_assign
(paren
id|irq
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
suffix:semicolon
id|vrc4171_irq_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
DECL|function|vrc4171_add_socket
r_static
r_int
id|__devinit
id|vrc4171_add_socket
c_func
(paren
r_int
id|slot
)paren
(brace
id|vrc4171_socket_t
op_star
id|socket
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_ge
id|CARD_MAX_SLOTS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|socket
op_assign
op_amp
id|vrc4171_sockets
(braket
id|slot
)braket
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;noprobe
op_ne
id|SLOT_PROBE
)paren
(brace
r_uint8
id|addrwin
suffix:semicolon
r_switch
c_cond
(paren
id|socket-&gt;noprobe
)paren
(brace
r_case
id|SLOT_NOPROBE_MEM
suffix:colon
id|addrwin
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_ADDRWIN
)paren
suffix:semicolon
id|addrwin
op_and_assign
l_int|0x1f
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_ADDRWIN
comma
id|addrwin
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SLOT_NOPROBE_IO
suffix:colon
id|addrwin
op_assign
id|exca_read_byte
c_func
(paren
id|slot
comma
id|I365_ADDRWIN
)paren
suffix:semicolon
id|addrwin
op_and_assign
l_int|0xc0
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_ADDRWIN
comma
id|addrwin
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|reserve_using_irq
c_func
(paren
id|slot
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|socket-&gt;name
comma
l_string|&quot;NEC VRC4171 Card Slot %1c&quot;
comma
l_char|&squot;A&squot;
op_plus
id|slot
)paren
suffix:semicolon
id|socket-&gt;pcmcia_socket.ops
op_assign
op_amp
id|vrc4171_pccard_operations
suffix:semicolon
id|retval
op_assign
id|pcmcia_register_socket
c_func
(paren
op_amp
id|socket-&gt;pcmcia_socket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|I365_ADDRWIN
comma
l_int|0
)paren
suffix:semicolon
id|exca_write_byte
c_func
(paren
id|slot
comma
id|GLOBAL_CONTROL
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vrc4171_remove_socket
r_static
r_void
id|vrc4171_remove_socket
c_func
(paren
r_int
id|slot
)paren
(brace
id|vrc4171_socket_t
op_star
id|socket
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_ge
id|CARD_MAX_SLOTS
)paren
r_return
suffix:semicolon
id|socket
op_assign
op_amp
id|vrc4171_sockets
(braket
id|slot
)braket
suffix:semicolon
id|pcmcia_unregister_socket
c_func
(paren
op_amp
id|socket-&gt;pcmcia_socket
)paren
suffix:semicolon
)brace
DECL|function|vrc4171_card_setup
r_static
r_int
id|__devinit
id|vrc4171_card_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
r_if
c_cond
(paren
id|options
op_eq
l_int|NULL
op_logical_or
op_star
id|options
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;irq:&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
r_int
id|irq
suffix:semicolon
id|options
op_add_assign
l_int|4
suffix:semicolon
id|irq
op_assign
id|simple_strtoul
c_func
(paren
id|options
comma
op_amp
id|options
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
l_int|0
op_logical_and
id|irq
OL
id|NR_IRQS
)paren
id|vrc4171_irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
op_star
id|options
op_ne
l_char|&squot;,&squot;
)paren
r_return
l_int|0
suffix:semicolon
id|options
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;slota:&quot;
comma
l_int|6
)paren
op_eq
l_int|0
)paren
(brace
id|options
op_add_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
op_star
id|options
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;memnoprobe&quot;
comma
l_int|10
)paren
op_eq
l_int|0
)paren
(brace
id|vrc4171_sockets
(braket
id|CARD_SLOTA
)braket
dot
id|noprobe
op_assign
id|SLOT_NOPROBE_MEM
suffix:semicolon
id|options
op_add_assign
l_int|10
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;ionoprobe&quot;
comma
l_int|9
)paren
op_eq
l_int|0
)paren
(brace
id|vrc4171_sockets
(braket
id|CARD_SLOTA
)braket
dot
id|noprobe
op_assign
id|SLOT_NOPROBE_IO
suffix:semicolon
id|options
op_add_assign
l_int|9
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;noprobe&quot;
comma
l_int|7
)paren
op_eq
l_int|0
)paren
(brace
id|vrc4171_sockets
(braket
id|CARD_SLOTA
)braket
dot
id|noprobe
op_assign
id|SLOT_NOPROBE_ALL
suffix:semicolon
id|options
op_add_assign
l_int|7
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|options
op_ne
l_char|&squot;,&squot;
)paren
r_return
l_int|0
suffix:semicolon
id|options
op_increment
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;slotb:&quot;
comma
l_int|6
)paren
op_eq
l_int|0
)paren
(brace
id|options
op_add_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
op_star
id|options
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;pccard&quot;
comma
l_int|6
)paren
op_eq
l_int|0
)paren
(brace
id|vrc4171_slotb
op_assign
id|SLOTB_IS_PCCARD
suffix:semicolon
id|options
op_add_assign
l_int|6
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;cf&quot;
comma
l_int|2
)paren
op_eq
l_int|0
)paren
(brace
id|vrc4171_slotb
op_assign
id|SLOTB_IS_CF
suffix:semicolon
id|options
op_add_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;flashrom&quot;
comma
l_int|8
)paren
op_eq
l_int|0
)paren
(brace
id|vrc4171_slotb
op_assign
id|SLOTB_IS_FLASHROM
suffix:semicolon
id|options
op_add_assign
l_int|8
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;none&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
id|vrc4171_slotb
op_assign
id|SLOTB_IS_NONE
suffix:semicolon
id|options
op_add_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|options
op_ne
l_char|&squot;,&squot;
)paren
r_return
l_int|0
suffix:semicolon
id|options
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;memnoprobe&quot;
comma
l_int|10
)paren
op_eq
l_int|0
)paren
id|vrc4171_sockets
(braket
id|CARD_SLOTB
)braket
dot
id|noprobe
op_assign
id|SLOT_NOPROBE_MEM
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;ionoprobe&quot;
comma
l_int|9
)paren
op_eq
l_int|0
)paren
id|vrc4171_sockets
(braket
id|CARD_SLOTB
)braket
dot
id|noprobe
op_assign
id|SLOT_NOPROBE_IO
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|options
comma
l_string|&quot;noprobe&quot;
comma
l_int|7
)paren
op_eq
l_int|0
)paren
id|vrc4171_sockets
(braket
id|CARD_SLOTB
)braket
dot
id|noprobe
op_assign
id|SLOT_NOPROBE_ALL
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;vrc4171_card=&quot;
comma
id|vrc4171_card_setup
)paren
suffix:semicolon
DECL|function|vrc4171_card_init
r_static
r_int
id|__devinit
id|vrc4171_card_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
comma
id|slot
suffix:semicolon
id|vrc4171_set_multifunction_pin
c_func
(paren
id|vrc4171_slotb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_region
c_func
(paren
id|CARD_CONTROLLER_INDEX
comma
id|CARD_CONTROLLER_SIZE
comma
l_string|&quot;NEC VRC4171 Card Controller&quot;
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|0
suffix:semicolon
id|slot
OL
id|CARD_MAX_SLOTS
suffix:semicolon
id|slot
op_increment
)paren
(brace
r_if
c_cond
(paren
id|slot
op_eq
id|CARD_SLOTB
op_logical_and
id|vrc4171_slotb
op_eq
id|SLOTB_IS_NONE
)paren
r_break
suffix:semicolon
id|retval
op_assign
id|vrc4171_add_socket
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
r_return
id|retval
suffix:semicolon
)brace
id|retval
op_assign
id|request_irq
c_func
(paren
id|vrc4171_irq
comma
id|pccard_interrupt
comma
id|SA_SHIRQ
comma
l_string|&quot;NEC VRC4171 Card Controller&quot;
comma
id|vrc4171_sockets
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|slot
op_assign
l_int|0
suffix:semicolon
id|slot
OL
id|CARD_MAX_SLOTS
suffix:semicolon
id|slot
op_increment
)paren
id|vrc4171_remove_socket
c_func
(paren
id|slot
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NEC VRC4171 Card Controller, connected to IRQ %d&bslash;n&quot;
comma
id|vrc4171_irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vrc4171_card_exit
r_static
r_void
id|__devexit
id|vrc4171_card_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|slot
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|0
suffix:semicolon
id|slot
OL
id|CARD_MAX_SLOTS
suffix:semicolon
id|slot
op_increment
)paren
id|vrc4171_remove_socket
c_func
(paren
id|slot
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|CARD_CONTROLLER_INDEX
comma
id|CARD_CONTROLLER_SIZE
)paren
suffix:semicolon
)brace
DECL|variable|vrc4171_card_init
id|module_init
c_func
(paren
id|vrc4171_card_init
)paren
suffix:semicolon
DECL|variable|vrc4171_card_exit
id|module_exit
c_func
(paren
id|vrc4171_card_exit
)paren
suffix:semicolon
eof
