multiline_comment|/*&n; * Copyright (c) 2001 by David Brownell&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* this file is part of ehci-hcd.c */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * EHCI Root Hub ... the nonsharable stuff&n; *&n; * Registers don&squot;t need cpu_to_le32, that happens transparently&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|check_reset_complete
r_static
r_int
id|check_reset_complete
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_int
id|index
comma
r_int
id|port_status
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|port_status
op_amp
id|PORT_CONNECT
)paren
)paren
(brace
id|ehci-&gt;reset_done
(braket
id|index
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|port_status
suffix:semicolon
)brace
multiline_comment|/* if reset finished and it&squot;s still not enabled -- handoff */
r_if
c_cond
(paren
op_logical_neg
(paren
id|port_status
op_amp
id|PORT_PE
)paren
)paren
(brace
id|dbg
(paren
l_string|&quot;%s port %d full speed, give to companion, 0x%x&quot;
comma
id|ehci-&gt;hcd.bus_name
comma
id|index
op_plus
l_int|1
comma
id|port_status
)paren
suffix:semicolon
singleline_comment|// what happens if HCS_N_CC(params) == 0 ?
id|port_status
op_or_assign
id|PORT_OWNER
suffix:semicolon
id|writel
(paren
id|port_status
comma
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|index
)braket
)paren
suffix:semicolon
)brace
r_else
id|dbg
(paren
l_string|&quot;%s port %d high speed&quot;
comma
id|ehci-&gt;hcd.bus_name
comma
id|index
op_plus
l_int|1
)paren
suffix:semicolon
r_return
id|port_status
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* build &quot;status change&quot; packet (one or two bytes) from HC registers */
r_static
r_int
DECL|function|ehci_hub_status_data
id|ehci_hub_status_data
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|ehci_hcd
op_star
id|ehci
op_assign
id|hcd_to_ehci
(paren
id|hcd
)paren
suffix:semicolon
id|u32
id|temp
comma
id|status
op_assign
l_int|0
suffix:semicolon
r_int
id|ports
comma
id|i
comma
id|retval
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* init status to no-changes */
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|temp
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;caps-&gt;hcs_params
)paren
suffix:semicolon
id|ports
op_assign
id|HCS_N_PORTS
(paren
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ports
OG
l_int|7
)paren
(brace
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|retval
op_increment
suffix:semicolon
)brace
multiline_comment|/* no hub change reports (bit 0) for now (power, ...) */
multiline_comment|/* port N changes (bit N)? */
id|spin_lock_irqsave
(paren
op_amp
id|ehci-&gt;lock
comma
id|flags
)paren
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
id|ports
suffix:semicolon
id|i
op_increment
)paren
(brace
id|temp
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_OWNER
)paren
(brace
singleline_comment|// get disconnected ports back if no companion driver
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_CONNECT
)paren
r_continue
suffix:semicolon
id|temp
op_and_assign
op_complement
(paren
id|PORT_OWNER
op_or
id|PORT_CSC
)paren
suffix:semicolon
id|writel
(paren
id|temp
comma
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|temp
op_amp
id|PORT_CONNECT
)paren
)paren
id|ehci-&gt;reset_done
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_amp
(paren
id|PORT_CSC
op_or
id|PORT_PEC
op_or
id|PORT_OCC
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|set_bit
(paren
id|i
comma
id|buf
)paren
suffix:semicolon
id|status
op_assign
id|STS_PCD
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
(paren
op_amp
id|ehci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|status
ques
c_cond
id|retval
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
r_static
r_void
DECL|function|ehci_hub_descriptor
id|ehci_hub_descriptor
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_struct
id|usb_hub_descriptor
op_star
id|desc
)paren
(brace
id|u32
id|params
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;caps-&gt;hcs_params
)paren
suffix:semicolon
r_int
id|ports
op_assign
id|HCS_N_PORTS
(paren
id|params
)paren
suffix:semicolon
id|u16
id|temp
suffix:semicolon
id|desc-&gt;bDescriptorType
op_assign
l_int|0x29
suffix:semicolon
id|desc-&gt;bPwrOn2PwrGood
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME: f(system power) */
id|desc-&gt;bHubContrCurrent
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;bNbrPorts
op_assign
id|ports
suffix:semicolon
id|temp
op_assign
l_int|1
op_plus
(paren
id|ports
op_div
l_int|8
)paren
suffix:semicolon
id|desc-&gt;bDescLength
op_assign
l_int|7
op_plus
l_int|2
op_star
id|temp
suffix:semicolon
multiline_comment|/* two bitmaps:  ports removable, and usb 1.0 legacy PortPwrCtrlMask */
id|memset
(paren
op_amp
id|desc-&gt;bitmap
(braket
l_int|0
)braket
comma
l_int|0
comma
id|temp
)paren
suffix:semicolon
id|memset
(paren
op_amp
id|desc-&gt;bitmap
(braket
id|temp
)braket
comma
l_int|0xff
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
l_int|0x0008
suffix:semicolon
multiline_comment|/* per-port overcurrent reporting */
r_if
c_cond
(paren
id|HCS_PPC
(paren
id|params
)paren
)paren
multiline_comment|/* per-port power control */
id|temp
op_or_assign
l_int|0x0001
suffix:semicolon
r_if
c_cond
(paren
id|HCS_INDICATOR
(paren
id|params
)paren
)paren
multiline_comment|/* per-port indicators (LEDs) */
id|temp
op_or_assign
l_int|0x0080
suffix:semicolon
id|desc-&gt;wHubCharacteristics
op_assign
id|cpu_to_le16
(paren
id|temp
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|ehci_hub_control
r_static
r_int
id|ehci_hub_control
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
id|u16
id|typeReq
comma
id|u16
id|wValue
comma
id|u16
id|wIndex
comma
r_char
op_star
id|buf
comma
id|u16
id|wLength
)paren
(brace
r_struct
id|ehci_hcd
op_star
id|ehci
op_assign
id|hcd_to_ehci
(paren
id|hcd
)paren
suffix:semicolon
id|u32
id|params
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;caps-&gt;hcs_params
)paren
suffix:semicolon
r_int
id|ports
op_assign
id|HCS_N_PORTS
(paren
id|params
)paren
suffix:semicolon
id|u32
id|temp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME:  support SetPortFeatures USB_PORT_FEAT_INDICATOR.&n;&t; * HCS_INDICATOR may say we can change LEDs to off/amber/green.&n;&t; * (track current state ourselves) ... blink for diagnostics,&n;&t; * power, &quot;this is the one&quot;, etc.  EHCI spec supports this.&n;&t; */
id|spin_lock_irqsave
(paren
op_amp
id|ehci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|typeReq
)paren
(brace
r_case
id|ClearHubFeature
suffix:colon
r_switch
c_cond
(paren
id|wValue
)paren
(brace
r_case
id|C_HUB_LOCAL_POWER
suffix:colon
r_case
id|C_HUB_OVER_CURRENT
suffix:colon
multiline_comment|/* no hub-wide feature/status flags */
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|error
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ClearPortFeature
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|wIndex
op_logical_or
id|wIndex
OG
id|ports
)paren
r_goto
id|error
suffix:semicolon
id|wIndex
op_decrement
suffix:semicolon
id|temp
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_OWNER
)paren
r_break
suffix:semicolon
r_switch
c_cond
(paren
id|wValue
)paren
(brace
r_case
id|USB_PORT_FEAT_ENABLE
suffix:colon
id|writel
(paren
id|temp
op_amp
op_complement
id|PORT_PE
comma
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_ENABLE
suffix:colon
id|writel
(paren
id|temp
op_or
id|PORT_PEC
comma
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_SUSPEND
suffix:colon
r_case
id|USB_PORT_FEAT_C_SUSPEND
suffix:colon
multiline_comment|/* ? */
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_POWER
suffix:colon
r_if
c_cond
(paren
id|HCS_PPC
(paren
id|params
)paren
)paren
id|writel
(paren
id|temp
op_amp
op_complement
id|PORT_POWER
comma
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_CONNECTION
suffix:colon
id|writel
(paren
id|temp
op_or
id|PORT_CSC
comma
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_OVER_CURRENT
suffix:colon
id|writel
(paren
id|temp
op_or
id|PORT_OCC
comma
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_RESET
suffix:colon
multiline_comment|/* GetPortStatus clears reset */
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|error
suffix:semicolon
)brace
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;command
)paren
suffix:semicolon
multiline_comment|/* unblock posted write */
r_break
suffix:semicolon
r_case
id|GetHubDescriptor
suffix:colon
id|ehci_hub_descriptor
(paren
id|ehci
comma
(paren
r_struct
id|usb_hub_descriptor
op_star
)paren
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GetHubStatus
suffix:colon
multiline_comment|/* no hub-wide feature/status flags */
id|memset
(paren
id|buf
comma
l_int|0
comma
l_int|4
)paren
suffix:semicolon
singleline_comment|//cpu_to_le32s ((u32 *) buf);
r_break
suffix:semicolon
r_case
id|GetPortStatus
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|wIndex
op_logical_or
id|wIndex
OG
id|ports
)paren
r_goto
id|error
suffix:semicolon
id|wIndex
op_decrement
suffix:semicolon
id|memset
(paren
id|buf
comma
l_int|0
comma
l_int|4
)paren
suffix:semicolon
id|temp
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
singleline_comment|// wPortChange bits
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_CSC
)paren
id|set_bit
(paren
id|USB_PORT_FEAT_C_CONNECTION
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_PEC
)paren
id|set_bit
(paren
id|USB_PORT_FEAT_C_ENABLE
comma
id|buf
)paren
suffix:semicolon
singleline_comment|// USB_PORT_FEAT_C_SUSPEND
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_OCC
)paren
id|set_bit
(paren
id|USB_PORT_FEAT_C_OVER_CURRENT
comma
id|buf
)paren
suffix:semicolon
multiline_comment|/* whoever resets must GetPortStatus to complete it!! */
r_if
c_cond
(paren
(paren
id|temp
op_amp
id|PORT_RESET
)paren
op_logical_and
id|jiffies
OG
id|ehci-&gt;reset_done
(braket
id|wIndex
)braket
)paren
(brace
id|set_bit
(paren
id|USB_PORT_FEAT_C_RESET
comma
id|buf
)paren
suffix:semicolon
multiline_comment|/* force reset to complete */
id|writel
(paren
id|temp
op_amp
op_complement
id|PORT_RESET
comma
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
r_do
(brace
id|temp
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
id|udelay
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|temp
op_amp
id|PORT_RESET
)paren
suffix:semicolon
multiline_comment|/* see what we found out */
id|temp
op_assign
id|check_reset_complete
(paren
id|ehci
comma
id|wIndex
comma
id|temp
)paren
suffix:semicolon
)brace
singleline_comment|// don&squot;t show wPortStatus if it&squot;s owned by a companion hc
r_if
c_cond
(paren
op_logical_neg
(paren
id|temp
op_amp
id|PORT_OWNER
)paren
)paren
(brace
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_CONNECT
)paren
(brace
id|set_bit
(paren
id|USB_PORT_FEAT_CONNECTION
comma
id|buf
)paren
suffix:semicolon
id|set_bit
(paren
id|USB_PORT_FEAT_HIGHSPEED
comma
id|buf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_PE
)paren
id|set_bit
(paren
id|USB_PORT_FEAT_ENABLE
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_SUSPEND
)paren
id|set_bit
(paren
id|USB_PORT_FEAT_SUSPEND
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_OC
)paren
id|set_bit
(paren
id|USB_PORT_FEAT_OVER_CURRENT
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_RESET
)paren
id|set_bit
(paren
id|USB_PORT_FEAT_RESET
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_POWER
)paren
id|set_bit
(paren
id|USB_PORT_FEAT_POWER
comma
id|buf
)paren
suffix:semicolon
)brace
macro_line|#ifndef&t;EHCI_VERBOSE_DEBUG
r_if
c_cond
(paren
op_star
(paren
id|u16
op_star
)paren
(paren
id|buf
op_plus
l_int|2
)paren
)paren
multiline_comment|/* only if wPortChange is interesting */
macro_line|#endif
id|dbg_port
(paren
id|hcd
comma
l_string|&quot;GetStatus&quot;
comma
id|wIndex
op_plus
l_int|1
comma
id|temp
)paren
suffix:semicolon
id|cpu_to_le32s
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SetHubFeature
suffix:colon
r_switch
c_cond
(paren
id|wValue
)paren
(brace
r_case
id|C_HUB_LOCAL_POWER
suffix:colon
r_case
id|C_HUB_OVER_CURRENT
suffix:colon
multiline_comment|/* no hub-wide feature/status flags */
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|error
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SetPortFeature
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|wIndex
op_logical_or
id|wIndex
OG
id|ports
)paren
r_goto
id|error
suffix:semicolon
id|wIndex
op_decrement
suffix:semicolon
id|temp
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|PORT_OWNER
)paren
r_break
suffix:semicolon
r_switch
c_cond
(paren
id|wValue
)paren
(brace
r_case
id|USB_PORT_FEAT_SUSPEND
suffix:colon
id|writel
(paren
id|temp
op_or
id|PORT_SUSPEND
comma
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_POWER
suffix:colon
r_if
c_cond
(paren
id|HCS_PPC
(paren
id|params
)paren
)paren
id|writel
(paren
id|temp
op_or
id|PORT_POWER
comma
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_RESET
suffix:colon
multiline_comment|/* line status bits may report this as low speed */
r_if
c_cond
(paren
(paren
id|temp
op_amp
(paren
id|PORT_PE
op_or
id|PORT_CONNECT
)paren
)paren
op_eq
id|PORT_CONNECT
op_logical_and
id|PORT_USB11
(paren
id|temp
)paren
)paren
(brace
id|dbg
(paren
l_string|&quot;%s port %d low speed, give to companion&quot;
comma
id|hcd-&gt;bus_name
comma
id|wIndex
op_plus
l_int|1
)paren
suffix:semicolon
id|temp
op_or_assign
id|PORT_OWNER
suffix:semicolon
)brace
r_else
(brace
id|vdbg
(paren
l_string|&quot;%s port %d reset&quot;
comma
id|hcd-&gt;bus_name
comma
id|wIndex
op_plus
l_int|1
)paren
suffix:semicolon
id|temp
op_or_assign
id|PORT_RESET
suffix:semicolon
id|temp
op_and_assign
op_complement
id|PORT_PE
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * caller must wait, then call GetPortStatus&n;&t;&t;&t;&t; * usb 2.0 spec says 50 ms resets on root&n;&t;&t;&t;&t; */
id|ehci-&gt;reset_done
(braket
id|wIndex
)braket
op_assign
id|jiffies
op_plus
(paren
(paren
l_int|50
multiline_comment|/* msec */
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
)brace
id|writel
(paren
id|temp
comma
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|wIndex
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|error
suffix:semicolon
)brace
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;command
)paren
suffix:semicolon
multiline_comment|/* unblock posted writes */
r_break
suffix:semicolon
r_default
suffix:colon
id|error
suffix:colon
multiline_comment|/* &quot;stall&quot; on error */
id|retval
op_assign
op_minus
id|EPIPE
suffix:semicolon
)brace
id|spin_unlock_irqrestore
(paren
op_amp
id|ehci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
