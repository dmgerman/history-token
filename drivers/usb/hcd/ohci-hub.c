multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; * &n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2002 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * &n; * This file is licenced under GPL&n; * $Id: ohci-hub.c,v 1.3 2002/03/22 16:04:54 dbrownell Exp $&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * OHCI Root Hub ... the nonsharable stuff&n; *&n; * Registers don&squot;t need cpu_to_le32, that happens transparently&n; */
multiline_comment|/* AMD-756 (D2 rev) reports corrupt register contents in some cases.&n; * The erratum (#4) description is incorrect.  AMD&squot;s workaround waits&n; * till some bits (mostly reserved) are clear; ok for all revs.&n; */
DECL|macro|read_roothub
mdefine_line|#define read_roothub(hc, register, mask) ({ &bslash;&n;&t;u32 temp = readl (&amp;hc-&gt;regs-&gt;roothub.register); &bslash;&n;&t;if (hc-&gt;flags &amp; OHCI_QUIRK_AMD756) &bslash;&n;&t;&t;while (temp &amp; mask) &bslash;&n;&t;&t;&t;temp = readl (&amp;hc-&gt;regs-&gt;roothub.register); &bslash;&n;&t;temp; })
DECL|function|roothub_a
r_static
id|u32
id|roothub_a
(paren
r_struct
id|ohci_hcd
op_star
id|hc
)paren
(brace
r_return
id|read_roothub
(paren
id|hc
comma
id|a
comma
l_int|0xfc0fe000
)paren
suffix:semicolon
)brace
DECL|function|roothub_b
r_static
r_inline
id|u32
id|roothub_b
(paren
r_struct
id|ohci_hcd
op_star
id|hc
)paren
(brace
r_return
id|readl
(paren
op_amp
id|hc-&gt;regs-&gt;roothub.b
)paren
suffix:semicolon
)brace
DECL|function|roothub_status
r_static
r_inline
id|u32
id|roothub_status
(paren
r_struct
id|ohci_hcd
op_star
id|hc
)paren
(brace
r_return
id|readl
(paren
op_amp
id|hc-&gt;regs-&gt;roothub.status
)paren
suffix:semicolon
)brace
DECL|function|roothub_portstatus
r_static
id|u32
id|roothub_portstatus
(paren
r_struct
id|ohci_hcd
op_star
id|hc
comma
r_int
id|i
)paren
(brace
r_return
id|read_roothub
(paren
id|hc
comma
id|portstatus
(braket
id|i
)braket
comma
l_int|0xffe0fce0
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|macro|dbg_port
mdefine_line|#define dbg_port(hc,label,num,value) &bslash;&n;&t;dbg (&quot;%s: %s roothub.portstatus [%d] &quot; &bslash;&n;&t;&t;&quot;= 0x%08x%s%s%s%s%s%s%s%s%s%s%s%s&quot;, &bslash;&n;&t;&t;hc-&gt;hcd.bus_name, label, num, temp, &bslash;&n;&t;&t;(temp &amp; RH_PS_PRSC) ? &quot; PRSC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_OCIC) ? &quot; OCIC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_PSSC) ? &quot; PSSC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_PESC) ? &quot; PESC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_CSC) ? &quot; CSC&quot; : &quot;&quot;, &bslash;&n; &t;&t;&bslash;&n;&t;&t;(temp &amp; RH_PS_LSDA) ? &quot; LSDA&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_PPS) ? &quot; PPS&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_PRS) ? &quot; PRS&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_POCI) ? &quot; POCI&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_PSS) ? &quot; PSS&quot; : &quot;&quot;, &bslash;&n; &t;&t;&bslash;&n;&t;&t;(temp &amp; RH_PS_PES) ? &quot; PES&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_CCS) ? &quot; CCS&quot; : &quot;&quot; &bslash;&n;&t;&t;);
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* build &quot;status change&quot; packet (one or two bytes) from HC registers */
r_static
r_int
DECL|function|ohci_hub_status_data
id|ohci_hub_status_data
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
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
r_int
id|ports
comma
id|i
comma
id|changed
op_assign
l_int|0
comma
id|length
op_assign
l_int|1
suffix:semicolon
id|ports
op_assign
id|roothub_a
(paren
id|ohci
)paren
op_amp
id|RH_A_NDP
suffix:semicolon
r_if
c_cond
(paren
id|ports
OG
id|MAX_ROOT_PORTS
)paren
(brace
id|err
(paren
l_string|&quot;%s: bogus NDP=%d&quot;
comma
id|hcd-&gt;bus_name
comma
id|ports
)paren
suffix:semicolon
id|err
(paren
l_string|&quot;rereads as NDP=%d&quot;
comma
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;roothub.a
)paren
op_amp
id|RH_A_NDP
)paren
suffix:semicolon
multiline_comment|/* retry later; &quot;should not happen&quot; */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* init status */
r_if
c_cond
(paren
id|roothub_status
(paren
id|ohci
)paren
op_amp
(paren
id|RH_HS_LPSC
op_or
id|RH_HS_OCIC
)paren
)paren
id|buf
(braket
l_int|0
)braket
op_assign
id|changed
op_assign
l_int|1
suffix:semicolon
r_else
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0
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
id|length
op_increment
suffix:semicolon
)brace
multiline_comment|/* look at each port */
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
id|u32
id|status
op_assign
id|roothub_portstatus
(paren
id|ohci
comma
id|i
)paren
suffix:semicolon
id|status
op_and_assign
id|RH_PS_CSC
op_or
id|RH_PS_PESC
op_or
id|RH_PS_PSSC
op_or
id|RH_PS_OCIC
op_or
id|RH_PS_PRSC
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|changed
op_assign
l_int|1
suffix:semicolon
id|set_bit
(paren
id|i
op_plus
l_int|1
comma
id|buf
)paren
suffix:semicolon
)brace
)brace
r_return
id|changed
ques
c_cond
id|length
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
r_static
r_void
DECL|function|ohci_hub_descriptor
id|ohci_hub_descriptor
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_struct
id|usb_hub_descriptor
op_star
id|desc
)paren
(brace
id|u32
id|rh
op_assign
id|roothub_a
(paren
id|ohci
)paren
suffix:semicolon
r_int
id|ports
op_assign
id|rh
op_amp
id|RH_A_NDP
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
(paren
id|rh
op_amp
id|RH_A_POTPGT
)paren
op_rshift
l_int|24
suffix:semicolon
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
id|temp
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rh
op_amp
id|RH_A_PSM
)paren
multiline_comment|/* per-port power switching? */
id|temp
op_or_assign
l_int|0x0001
suffix:semicolon
r_if
c_cond
(paren
id|rh
op_amp
id|RH_A_NOCP
)paren
multiline_comment|/* no overcurrent reporting? */
id|temp
op_or_assign
l_int|0x0010
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rh
op_amp
id|RH_A_OCPM
)paren
multiline_comment|/* per-port overcurrent reporting? */
id|temp
op_or_assign
l_int|0x0008
suffix:semicolon
id|desc-&gt;wHubCharacteristics
op_assign
id|cpu_to_le16
(paren
id|temp
)paren
suffix:semicolon
multiline_comment|/* two bitmaps:  ports removable, and usb 1.0 legacy PortPwrCtrlMask */
id|rh
op_assign
id|roothub_b
(paren
id|ohci
)paren
suffix:semicolon
id|desc-&gt;bitmap
(braket
l_int|0
)braket
op_assign
id|rh
op_amp
id|RH_B_DR
suffix:semicolon
r_if
c_cond
(paren
id|ports
OG
l_int|7
)paren
(brace
id|desc-&gt;bitmap
(braket
l_int|1
)braket
op_assign
(paren
id|rh
op_amp
id|RH_B_DR
)paren
op_rshift
l_int|8
suffix:semicolon
id|desc-&gt;bitmap
(braket
l_int|2
)braket
op_assign
id|desc-&gt;bitmap
(braket
l_int|3
)braket
op_assign
l_int|0xff
suffix:semicolon
)brace
r_else
id|desc-&gt;bitmap
(braket
l_int|1
)braket
op_assign
l_int|0xff
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|ohci_hub_control
r_static
r_int
id|ohci_hub_control
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
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
r_int
id|ports
suffix:semicolon
id|u32
id|temp
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
singleline_comment|// if (port request)
id|ports
op_assign
id|roothub_a
(paren
id|ohci
)paren
op_amp
id|RH_A_NDP
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
id|C_HUB_OVER_CURRENT
suffix:colon
id|writel
(paren
id|RH_HS_OCIC
comma
op_amp
id|ohci-&gt;regs-&gt;roothub.status
)paren
suffix:semicolon
r_case
id|C_HUB_LOCAL_POWER
suffix:colon
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
r_switch
c_cond
(paren
id|wValue
)paren
(brace
r_case
id|USB_PORT_FEAT_ENABLE
suffix:colon
id|temp
op_assign
id|RH_PS_CCS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_ENABLE
suffix:colon
id|temp
op_assign
id|RH_PS_PESC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_SUSPEND
suffix:colon
id|temp
op_assign
id|RH_PS_POCI
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_SUSPEND
suffix:colon
id|temp
op_assign
id|RH_PS_PSSC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_POWER
suffix:colon
id|temp
op_assign
id|RH_PS_LSDA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_CONNECTION
suffix:colon
id|temp
op_assign
id|RH_PS_CSC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_OVER_CURRENT
suffix:colon
id|temp
op_assign
id|RH_PS_OCIC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_RESET
suffix:colon
id|temp
op_assign
id|RH_PS_PRSC
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|error
suffix:semicolon
)brace
id|writel
(paren
id|temp
comma
op_amp
id|ohci-&gt;regs-&gt;roothub.portstatus
(braket
id|wIndex
)braket
)paren
suffix:semicolon
singleline_comment|// readl (&amp;ohci-&gt;regs-&gt;roothub.portstatus [wIndex]);
r_break
suffix:semicolon
r_case
id|GetHubDescriptor
suffix:colon
id|ohci_hub_descriptor
(paren
id|ohci
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
id|temp
op_assign
id|roothub_status
(paren
id|ohci
)paren
op_amp
op_complement
(paren
id|RH_HS_CRWE
op_or
id|RH_HS_DRWE
)paren
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|buf
op_assign
id|cpu_to_le32
(paren
id|temp
)paren
suffix:semicolon
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
id|temp
op_assign
id|roothub_portstatus
(paren
id|ohci
comma
id|wIndex
)paren
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|buf
op_assign
id|cpu_to_le32
(paren
id|temp
)paren
suffix:semicolon
macro_line|#ifndef&t;OHCI_VERBOSE_DEBUG
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
id|ohci
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
id|C_HUB_OVER_CURRENT
suffix:colon
singleline_comment|// FIXME:  this can be cleared, yes?
r_case
id|C_HUB_LOCAL_POWER
suffix:colon
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
id|RH_PS_PSS
comma
op_amp
id|ohci-&gt;regs-&gt;roothub.portstatus
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
id|writel
(paren
id|RH_PS_PPS
comma
op_amp
id|ohci-&gt;regs-&gt;roothub.portstatus
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
id|temp
op_assign
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;roothub.portstatus
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
id|RH_PS_CCS
)paren
id|writel
(paren
id|RH_PS_PRS
comma
op_amp
id|ohci-&gt;regs-&gt;roothub.portstatus
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
r_break
suffix:semicolon
r_default
suffix:colon
id|error
suffix:colon
multiline_comment|/* &quot;protocol stall&quot; on error */
id|retval
op_assign
op_minus
id|EPIPE
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
eof
