multiline_comment|/*&n; * Universal Host Controller Interface driver for USB.&n; *&n; * Maintainer: Alan Stern &lt;stern@rowland.harvard.edu&gt;&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; * (C) Copyright 1999-2002 Johannes Erdfelt, johannes@erdfelt.com&n; * (C) Copyright 1999 Randy Dunlap&n; * (C) Copyright 1999 Georg Acher, acher@in.tum.de&n; * (C) Copyright 1999 Deti Fliegl, deti@fliegl.de&n; * (C) Copyright 1999 Thomas Sailer, sailer@ife.ee.ethz.ch&n; * (C) Copyright 2004 Alan Stern, stern@rowland.harvard.edu&n; */
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
l_int|0x0a
comma
multiline_comment|/* __u16  wHubCharacteristics; */
l_int|0x00
comma
multiline_comment|/*   (per-port OC, no power switching) */
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
DECL|macro|UHCI_RH_MAXCHILD
mdefine_line|#define&t;UHCI_RH_MAXCHILD&t;7
multiline_comment|/* must write as zeroes */
DECL|macro|WZ_BITS
mdefine_line|#define WZ_BITS&t;&t;(USBPORTSC_RES2 | USBPORTSC_RES3 | USBPORTSC_RES4)
multiline_comment|/* status change bits:  nonzero writes will clear */
DECL|macro|RWC_BITS
mdefine_line|#define RWC_BITS&t;(USBPORTSC_OCC | USBPORTSC_PEC | USBPORTSC_CSC)
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
id|port
suffix:semicolon
op_star
id|buf
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
l_int|0
suffix:semicolon
id|port
OL
id|uhci-&gt;rh_numports
suffix:semicolon
op_increment
id|port
)paren
(brace
r_if
c_cond
(paren
(paren
id|inw
c_func
(paren
id|uhci-&gt;io_addr
op_plus
id|USBPORTSC1
op_plus
id|port
op_star
l_int|2
)paren
op_amp
id|RWC_BITS
)paren
op_logical_or
id|test_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;port_c_suspend
)paren
)paren
op_star
id|buf
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|port
op_plus
l_int|1
)paren
)paren
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
mdefine_line|#define CLR_RH_PORTSTAT(x) &bslash;&n;&t;status = inw(port_addr); &bslash;&n;&t;status &amp;= ~(RWC_BITS|WZ_BITS); &bslash;&n;&t;status &amp;= ~(x); &bslash;&n;&t;status |= RWC_BITS &amp; (x); &bslash;&n;&t;outw(status, port_addr)
DECL|macro|SET_RH_PORTSTAT
mdefine_line|#define SET_RH_PORTSTAT(x) &bslash;&n;&t;status = inw(port_addr); &bslash;&n;&t;status |= (x); &bslash;&n;&t;status &amp;= ~(RWC_BITS|WZ_BITS); &bslash;&n;&t;outw(status, port_addr)
multiline_comment|/* UHCI controllers don&squot;t automatically stop resume signalling after 20 msec,&n; * so we have to poll and check timeouts in order to take care of it.&n; * FIXME:  Synchronize access to these fields by a spinlock.&n; */
DECL|function|uhci_finish_suspend
r_static
r_void
id|uhci_finish_suspend
c_func
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
comma
r_int
id|port
comma
r_int
r_int
id|port_addr
)paren
(brace
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;suspended_ports
)paren
)paren
(brace
id|CLR_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_SUSP
op_or
id|USBPORTSC_RD
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;suspended_ports
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;resuming_ports
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;port_c_suspend
)paren
suffix:semicolon
)brace
)brace
DECL|function|uhci_check_resume
r_static
r_void
id|uhci_check_resume
c_func
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
)paren
(brace
r_int
r_int
id|port
suffix:semicolon
r_int
r_int
id|port_addr
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
l_int|0
suffix:semicolon
id|port
OL
id|uhci-&gt;rh_numports
suffix:semicolon
op_increment
id|port
)paren
(brace
id|port_addr
op_assign
id|uhci-&gt;io_addr
op_plus
id|USBPORTSC1
op_plus
l_int|2
op_star
id|port
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|inw
c_func
(paren
id|port_addr
)paren
op_amp
id|USBPORTSC_RD
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;resuming_ports
)paren
)paren
(brace
multiline_comment|/* Port received a wakeup request */
id|set_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;resuming_ports
)paren
suffix:semicolon
id|uhci-&gt;resume_timeout
op_assign
id|jiffies
op_plus
id|msecs_to_jiffies
c_func
(paren
l_int|20
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|time_after_eq
c_func
(paren
id|jiffies
comma
id|uhci-&gt;resume_timeout
)paren
)paren
(brace
id|uhci_finish_suspend
c_func
(paren
id|uhci
comma
id|port
comma
id|port_addr
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/* size of returned buffer is part of USB spec */
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
id|status
comma
id|lstatus
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
id|port
op_assign
id|wIndex
op_minus
l_int|1
suffix:semicolon
r_int
r_int
id|port_addr
op_assign
id|uhci-&gt;io_addr
op_plus
id|USBPORTSC1
op_plus
l_int|2
op_star
id|port
suffix:semicolon
id|u16
id|wPortChange
comma
id|wPortStatus
suffix:semicolon
r_switch
c_cond
(paren
id|typeReq
)paren
(brace
r_case
id|GetHubStatus
suffix:colon
op_star
(paren
id|__le32
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
r_if
c_cond
(paren
id|port
op_ge
id|uhci-&gt;rh_numports
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
id|uhci-&gt;resuming_ports
)paren
id|uhci_check_resume
c_func
(paren
id|uhci
)paren
suffix:semicolon
id|status
op_assign
id|inw
c_func
(paren
id|port_addr
)paren
suffix:semicolon
multiline_comment|/* Intel controllers report the OverCurrent bit active on.&n;&t;&t; * VIA controllers report it active off, so we&squot;ll adjust the&n;&t;&t; * bit value.  (It&squot;s not standardized in the UHCI spec.)&n;&t;&t; */
r_if
c_cond
(paren
id|to_pci_dev
c_func
(paren
id|hcd-&gt;self.controller
)paren
op_member_access_from_pointer
id|vendor
op_eq
id|PCI_VENDOR_ID_VIA
)paren
id|status
op_xor_assign
id|USBPORTSC_OC
suffix:semicolon
multiline_comment|/* UHCI doesn&squot;t support C_RESET (always false) */
id|wPortChange
op_assign
id|lstatus
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|USBPORTSC_CSC
)paren
id|wPortChange
op_or_assign
id|USB_PORT_STAT_C_CONNECTION
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|USBPORTSC_PEC
)paren
id|wPortChange
op_or_assign
id|USB_PORT_STAT_C_ENABLE
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|USBPORTSC_OCC
)paren
id|wPortChange
op_or_assign
id|USB_PORT_STAT_C_OVERCURRENT
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;port_c_suspend
)paren
)paren
(brace
id|wPortChange
op_or_assign
id|USB_PORT_STAT_C_SUSPEND
suffix:semicolon
id|lstatus
op_or_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;suspended_ports
)paren
)paren
id|lstatus
op_or_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;resuming_ports
)paren
)paren
id|lstatus
op_or_assign
l_int|4
suffix:semicolon
multiline_comment|/* UHCI has no power switching (always on) */
id|wPortStatus
op_assign
id|USB_PORT_STAT_POWER
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|USBPORTSC_CCS
)paren
id|wPortStatus
op_or_assign
id|USB_PORT_STAT_CONNECTION
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|USBPORTSC_PE
)paren
(brace
id|wPortStatus
op_or_assign
id|USB_PORT_STAT_ENABLE
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
(paren
id|USBPORTSC_SUSP
op_or
id|USBPORTSC_RD
)paren
)paren
id|wPortStatus
op_or_assign
id|USB_PORT_STAT_SUSPEND
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|USBPORTSC_OC
)paren
id|wPortStatus
op_or_assign
id|USB_PORT_STAT_OVERCURRENT
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|USBPORTSC_PR
)paren
id|wPortStatus
op_or_assign
id|USB_PORT_STAT_RESET
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|USBPORTSC_LSDA
)paren
id|wPortStatus
op_or_assign
id|USB_PORT_STAT_LOW_SPEED
suffix:semicolon
r_if
c_cond
(paren
id|wPortChange
)paren
id|dev_dbg
c_func
(paren
id|uhci_dev
c_func
(paren
id|uhci
)paren
comma
l_string|&quot;port %d portsc %04x,%02x&bslash;n&quot;
comma
id|wIndex
comma
id|status
comma
id|lstatus
)paren
suffix:semicolon
op_star
(paren
id|__le16
op_star
)paren
id|buf
op_assign
id|cpu_to_le16
c_func
(paren
id|wPortStatus
)paren
suffix:semicolon
op_star
(paren
id|__le16
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
id|wPortChange
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
multiline_comment|/* We don&squot;t implement these */
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
r_case
id|C_HUB_LOCAL_POWER
suffix:colon
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
id|SetPortFeature
suffix:colon
r_if
c_cond
(paren
id|port
op_ge
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
id|set_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;suspended_ports
)paren
suffix:semicolon
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
multiline_comment|/* Reset terminates Resume signalling */
id|uhci_finish_suspend
c_func
(paren
id|uhci
comma
id|port
comma
id|port_addr
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
id|CLR_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_PEC
op_or
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
id|USB_PORT_FEAT_POWER
suffix:colon
multiline_comment|/* UHCI has no power switching */
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
id|port
op_ge
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
multiline_comment|/* Disable terminates Resume signalling */
id|uhci_finish_suspend
c_func
(paren
id|uhci
comma
id|port
comma
id|port_addr
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
id|CLR_RH_PORTSTAT
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
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;suspended_ports
)paren
op_logical_and
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;resuming_ports
)paren
)paren
(brace
id|uhci-&gt;resume_timeout
op_assign
id|jiffies
op_plus
id|msecs_to_jiffies
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|SET_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_RD
)paren
suffix:semicolon
multiline_comment|/* The controller won&squot;t allow RD to be set&n;&t;&t;&t;&t; * if the port is disabled.  When this happens&n;&t;&t;&t;&t; * just skip the Resume signalling.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|inw
c_func
(paren
id|port_addr
)paren
op_amp
id|USBPORTSC_RD
)paren
)paren
id|uhci_finish_suspend
c_func
(paren
id|uhci
comma
id|port
comma
id|port_addr
)paren
suffix:semicolon
)brace
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_SUSPEND
suffix:colon
id|clear_bit
c_func
(paren
id|port
comma
op_amp
id|uhci-&gt;port_c_suspend
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
multiline_comment|/* UHCI has no power switching */
r_goto
id|err
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_CONNECTION
suffix:colon
id|CLR_RH_PORTSTAT
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
id|CLR_RH_PORTSTAT
c_func
(paren
id|USBPORTSC_OCC
)paren
suffix:semicolon
id|OK
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|USB_PORT_FEAT_C_RESET
suffix:colon
multiline_comment|/* this driver won&squot;t report these */
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
r_sizeof
(paren
id|root_hub_hub_des
)paren
comma
id|wLength
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
