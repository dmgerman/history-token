multiline_comment|/*&n; * Universal Host Controller Interface driver for USB.&n; *&n; * Maintainer: Johannes Erdfelt &lt;johannes@erdfelt.com&gt;&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; * (C) Copyright 1999-2002 Johannes Erdfelt, johannes@erdfelt.com&n; * (C) Copyright 1999 Randy Dunlap&n; * (C) Copyright 1999 Georg Acher, acher@in.tum.de&n; * (C) Copyright 1999 Deti Fliegl, deti@fliegl.de&n; * (C) Copyright 1999 Thomas Sailer, sailer@ife.ee.ethz.ch&n; */
DECL|variable|root_hub_hub_des
r_static
id|__u8
id|root_hub_hub_des
(braket
)braket
op_assign
(brace
l_int|0x09
comma
multiline_comment|/*  __u8  bLength; */
l_int|0x29
comma
multiline_comment|/*  __u8  bDescriptorType; Hub-descriptor */
l_int|0x02
comma
multiline_comment|/*  __u8  bNbrPorts; */
l_int|0x00
comma
multiline_comment|/* __u16  wHubCharacteristics; */
l_int|0x00
comma
l_int|0x01
comma
multiline_comment|/*  __u8  bPwrOn2pwrGood; 2ms */
l_int|0x00
comma
multiline_comment|/*  __u8  bHubContrCurrent; 0 mA */
l_int|0x00
comma
multiline_comment|/*  __u8  DeviceRemovable; *** 7 Ports max *** */
l_int|0xff
multiline_comment|/*  __u8  PortPwrCtrlMask; *** 7 ports max *** */
)brace
suffix:semicolon
DECL|function|uhci_hub_status_data
r_static
r_int
id|uhci_hub_status_data
c_func
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
id|uhci_hcd
op_star
id|uhci
op_assign
id|hcd_to_uhci
c_func
(paren
id|hcd
)paren
suffix:semicolon
r_int
r_int
id|io_addr
op_assign
id|uhci-&gt;io_addr
suffix:semicolon
r_int
id|i
comma
id|len
op_assign
l_int|1
suffix:semicolon
op_star
id|buf
op_assign
l_int|0
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
id|uhci-&gt;rh_numports
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
id|buf
op_or_assign
(paren
(paren
id|inw
c_func
(paren
id|io_addr
op_plus
id|USBPORTSC1
op_plus
id|i
op_star
l_int|2
)paren
op_amp
l_int|0xa
)paren
OG
l_int|0
ques
c_cond
(paren
l_int|1
op_lshift
(paren
id|i
op_plus
l_int|1
)paren
)paren
suffix:colon
l_int|0
)paren
suffix:semicolon
id|len
op_assign
(paren
id|i
op_plus
l_int|1
)paren
op_div
l_int|8
op_plus
l_int|1
suffix:semicolon
)brace
r_return
op_logical_neg
op_logical_neg
op_star
id|buf
suffix:semicolon
)brace
DECL|macro|OK
mdefine_line|#define OK(x)&t;&t;&t;len = (x); break
DECL|macro|CLR_RH_PORTSTAT
mdefine_line|#define CLR_RH_PORTSTAT(x) &bslash;&n;&t;status = inw(io_addr + USBPORTSC1 + 2 * (wIndex-1)); &bslash;&n;&t;status = (status &amp; 0xfff5) &amp; ~(x); &bslash;&n;&t;outw(status, io_addr + USBPORTSC1 + 2 * (wIndex-1))
DECL|macro|SET_RH_PORTSTAT
mdefine_line|#define SET_RH_PORTSTAT(x) &bslash;&n;&t;status = inw(io_addr + USBPORTSC1 + 2 * (wIndex-1)); &bslash;&n;&t;status = (status &amp; 0xfff5) | (x); &bslash;&n;&t;outw(status, io_addr + USBPORTSC1 + 2 * (wIndex-1))
singleline_comment|// FIXME: Shouldn&squot;t this return the length of the data too?
DECL|function|uhci_hub_control
r_static
r_int
id|uhci_hub_control
c_func
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
id|uhci_hcd
op_star
id|uhci
op_assign
id|hcd_to_uhci
c_func
(paren
id|hcd
)paren
suffix:semicolon
r_int
id|i
comma
id|status
comma
id|retval
op_assign
l_int|0
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|io_addr
op_assign
id|uhci-&gt;io_addr
suffix:semicolon
id|__u16
id|cstatus
suffix:semicolon
r_char
id|c_p_r
(braket
l_int|8
)braket
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|c_p_r
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|typeReq
)paren
(brace
multiline_comment|/* Request Destination:&n;&t;&t;   without flags: Device,&n;&t;&t;   RH_INTERFACE: interface,&n;&t;&t;   RH_ENDPOINT: endpoint,&n;&t;&t;   RH_CLASS means HUB here,&n;&t;&t;   RH_OTHER | RH_CLASS  almost ever means HUB_PORT here&n;&t;&t;*/
r_case
id|GetHubStatus
suffix:colon
op_star
(paren
id|__u32
op_star
)paren
id|buf
op_assign
id|cpu_to_le32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|OK
c_func
(paren
l_int|4
)paren
suffix:semicolon
multiline_comment|/* hub power */
r_case
id|GetPortStatus
suffix:colon
id|status
op_assign
id|inw
c_func
(paren
id|io_addr
op_plus
id|USBPORTSC1
op_plus
l_int|2
op_star
(paren
id|wIndex
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|cstatus
op_assign
(paren
(paren
id|status
op_amp
id|USBPORTSC_CSC
)paren
op_rshift
(paren
l_int|1
op_minus
l_int|0
)paren
)paren
op_or
(paren
(paren
id|status
op_amp
id|USBPORTSC_PEC
)paren
op_rshift
(paren
l_int|3
op_minus
l_int|1
)paren
)paren
op_or
(paren
id|c_p_r
(braket
id|wIndex
op_minus
l_int|1
)braket
op_lshift
(paren
l_int|0
op_plus
l_int|4
)paren
)paren
suffix:semicolon
id|status
op_assign
(paren
id|status
op_amp
id|USBPORTSC_CCS
)paren
op_or
(paren
(paren
id|status
op_amp
id|USBPORTSC_PE
)paren
op_rshift
(paren
l_int|2
op_minus
l_int|1
)paren
)paren
op_or
(paren
(paren
id|status
op_amp
id|USBPORTSC_SUSP
)paren
op_rshift
(paren
l_int|12
op_minus
l_int|2
)paren
)paren
op_or
(paren
(paren
id|status
op_amp
id|USBPORTSC_PR
)paren
op_rshift
(paren
l_int|9
op_minus
l_int|4
)paren
)paren
op_or
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
multiline_comment|/* power on */
(paren
(paren
id|status
op_amp
id|USBPORTSC_LSDA
)paren
op_lshift
(paren
op_minus
l_int|8
op_plus
l_int|9
)paren
)paren
suffix:semicolon
op_star
(paren
id|__u16
op_star
)paren
id|buf
op_assign
id|cpu_to_le16
c_func
(paren
id|status
)paren
suffix:semicolon
op_star
(paren
id|__u16
op_star
)paren
(paren
id|buf
op_plus
l_int|2
)paren
op_assign
id|cpu_to_le16
c_func
(paren
id|cstatus
)paren
suffix:semicolon
id|OK
c_func
(paren
l_int|4
)paren
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
r_case
id|C_HUB_LOCAL_POWER
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|err
suffix:semicolon
)brace
r_break
suffix:semicolon
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
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* hub power over current */
r_default
suffix:colon
r_goto
id|err
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
id|uhci-&gt;rh_numports
)paren
r_goto
id|err
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
id|SET_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_SUSP
)paren
suffix:semicolon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|USB_PORT_FEAT_RESET
suffix:colon
id|SET_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_PR
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
multiline_comment|/* USB v1.1 7.1.7.3 */
id|c_p_r
(braket
id|wIndex
op_minus
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
id|CLR_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_PR
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|SET_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_PE
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|SET_RH_PORTSTAT
c_func
(paren
l_int|0xa
)paren
suffix:semicolon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|USB_PORT_FEAT_POWER
suffix:colon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* port power ** */
r_case
id|USB_PORT_FEAT_ENABLE
suffix:colon
id|SET_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_PE
)paren
suffix:semicolon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_default
suffix:colon
r_goto
id|err
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
id|uhci-&gt;rh_numports
)paren
r_goto
id|err
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
id|CLR_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_PE
)paren
suffix:semicolon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_ENABLE
suffix:colon
id|SET_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_PEC
)paren
suffix:semicolon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|USB_PORT_FEAT_SUSPEND
suffix:colon
id|CLR_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_SUSP
)paren
suffix:semicolon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_SUSPEND
suffix:colon
multiline_comment|/*** WR_RH_PORTSTAT(RH_PS_PSSC); */
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|USB_PORT_FEAT_POWER
suffix:colon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* port power */
r_case
id|USB_PORT_FEAT_C_CONNECTION
suffix:colon
id|SET_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_CSC
)paren
suffix:semicolon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_OVER_CURRENT
suffix:colon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* port power over current */
r_case
id|USB_PORT_FEAT_C_RESET
suffix:colon
id|c_p_r
(braket
id|wIndex
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_default
suffix:colon
r_goto
id|err
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|GetHubDescriptor
suffix:colon
id|len
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|wLength
comma
id|min_t
c_func
(paren
r_int
r_int
comma
r_sizeof
(paren
id|root_hub_hub_des
)paren
comma
id|wLength
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|root_hub_hub_des
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|2
)paren
id|buf
(braket
l_int|2
)braket
op_assign
id|uhci-&gt;rh_numports
suffix:semicolon
id|OK
c_func
(paren
id|len
)paren
suffix:semicolon
r_default
suffix:colon
id|err
suffix:colon
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