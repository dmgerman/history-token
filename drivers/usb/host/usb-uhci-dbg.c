multiline_comment|/*  &n;    UHCI HCD (Host Controller Driver) for USB, debugging calls&n;   &n;    (c) 1999-2002 &n;    Georg Acher      +    Deti Fliegl    +    Thomas Sailer&n;    georg@acher.org      deti@fliegl.de   sailer@ife.ee.ethz.ch&n;  &n;    $Id: usb-uhci-dbg.c,v 1.2 2002/05/21 21:40:16 acher Exp $&n;*/
macro_line|#ifdef DEBUG
DECL|function|uhci_show_qh
r_static
r_void
id|__attribute__
c_func
(paren
(paren
id|__unused__
)paren
)paren
id|uhci_show_qh
(paren
id|puhci_desc_t
id|qh
)paren
(brace
r_if
c_cond
(paren
id|qh-&gt;type
op_ne
id|QH_TYPE
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;qh has not QH_TYPE&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;QH @ %p/%08llX:&quot;
comma
id|qh
comma
(paren
r_int
r_int
r_int
)paren
id|qh-&gt;dma_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qh-&gt;hw.qh.head
op_amp
id|UHCI_PTR_TERM
)paren
id|dbg
c_func
(paren
l_string|&quot;    Head Terminate&quot;
)paren
suffix:semicolon
r_else
id|dbg
c_func
(paren
l_string|&quot;    Head: %s @ %08X&quot;
comma
(paren
id|qh-&gt;hw.qh.head
op_amp
id|UHCI_PTR_QH
ques
c_cond
l_string|&quot;QH&quot;
suffix:colon
l_string|&quot;TD&quot;
)paren
comma
id|qh-&gt;hw.qh.head
op_amp
op_complement
id|UHCI_PTR_BITS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qh-&gt;hw.qh.element
op_amp
id|UHCI_PTR_TERM
)paren
id|dbg
c_func
(paren
l_string|&quot;    Element Terminate&quot;
)paren
suffix:semicolon
r_else
id|dbg
c_func
(paren
l_string|&quot;    Element: %s @ %08X&quot;
comma
(paren
id|qh-&gt;hw.qh.element
op_amp
id|UHCI_PTR_QH
ques
c_cond
l_string|&quot;QH&quot;
suffix:colon
l_string|&quot;TD&quot;
)paren
comma
id|qh-&gt;hw.qh.element
op_amp
op_complement
id|UHCI_PTR_BITS
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if 0
r_static
r_void
id|uhci_show_td
(paren
id|puhci_desc_t
id|td
)paren
(brace
r_char
op_star
id|spid
suffix:semicolon
r_switch
c_cond
(paren
id|td-&gt;hw.td.info
op_amp
l_int|0xff
)paren
(brace
r_case
id|USB_PID_SETUP
suffix:colon
id|spid
op_assign
l_string|&quot;SETUP&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PID_OUT
suffix:colon
id|spid
op_assign
l_string|&quot; OUT &quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PID_IN
suffix:colon
id|spid
op_assign
l_string|&quot; IN  &quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|spid
op_assign
l_string|&quot;  ?  &quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|warn
c_func
(paren
l_string|&quot;  TD @ %p/%08X, MaxLen=%02x DT%d EP=%x Dev=%x PID=(%s) buf=%08x&quot;
comma
id|td
comma
id|td-&gt;dma_addr
comma
id|td-&gt;hw.td.info
op_rshift
l_int|21
comma
(paren
(paren
id|td-&gt;hw.td.info
op_rshift
l_int|19
)paren
op_amp
l_int|1
)paren
comma
(paren
id|td-&gt;hw.td.info
op_rshift
l_int|15
)paren
op_amp
l_int|15
comma
(paren
id|td-&gt;hw.td.info
op_rshift
l_int|8
)paren
op_amp
l_int|127
comma
id|spid
comma
id|td-&gt;hw.td.buffer
)paren
suffix:semicolon
id|warn
c_func
(paren
l_string|&quot;    Len=%02x e%d %s%s%s%s%s%s%s%s%s%s&quot;
comma
id|td-&gt;hw.td.status
op_amp
l_int|0x7ff
comma
(paren
(paren
id|td-&gt;hw.td.status
op_rshift
l_int|27
)paren
op_amp
l_int|3
)paren
comma
(paren
id|td-&gt;hw.td.status
op_amp
id|TD_CTRL_SPD
)paren
ques
c_cond
l_string|&quot;SPD &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|td-&gt;hw.td.status
op_amp
id|TD_CTRL_LS
)paren
ques
c_cond
l_string|&quot;LS &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|td-&gt;hw.td.status
op_amp
id|TD_CTRL_IOC
)paren
ques
c_cond
l_string|&quot;IOC &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|td-&gt;hw.td.status
op_amp
id|TD_CTRL_ACTIVE
)paren
ques
c_cond
l_string|&quot;Active &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|td-&gt;hw.td.status
op_amp
id|TD_CTRL_STALLED
)paren
ques
c_cond
l_string|&quot;Stalled &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|td-&gt;hw.td.status
op_amp
id|TD_CTRL_DBUFERR
)paren
ques
c_cond
l_string|&quot;DataBufErr &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|td-&gt;hw.td.status
op_amp
id|TD_CTRL_BABBLE
)paren
ques
c_cond
l_string|&quot;Babble &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|td-&gt;hw.td.status
op_amp
id|TD_CTRL_NAK
)paren
ques
c_cond
l_string|&quot;NAK &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|td-&gt;hw.td.status
op_amp
id|TD_CTRL_CRCTIMEO
)paren
ques
c_cond
l_string|&quot;CRC/Timeo &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|td-&gt;hw.td.status
op_amp
id|TD_CTRL_BITSTUFF
)paren
ques
c_cond
l_string|&quot;BitStuff &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|td-&gt;hw.td.link
op_amp
id|UHCI_PTR_TERM
)paren
id|warn
c_func
(paren
l_string|&quot;   TD Link Terminate&quot;
)paren
suffix:semicolon
r_else
id|warn
c_func
(paren
l_string|&quot;    Link points to %s @ %08x, %s&quot;
comma
(paren
id|td-&gt;hw.td.link
op_amp
id|UHCI_PTR_QH
ques
c_cond
l_string|&quot;QH&quot;
suffix:colon
l_string|&quot;TD&quot;
)paren
comma
id|td-&gt;hw.td.link
op_amp
op_complement
id|UHCI_PTR_BITS
comma
(paren
id|td-&gt;hw.td.link
op_amp
id|UHCI_PTR_DEPTH
ques
c_cond
l_string|&quot;Depth first&quot;
suffix:colon
l_string|&quot;Breadth first&quot;
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef DEBUG
DECL|function|uhci_show_sc
r_static
r_void
id|__attribute__
c_func
(paren
(paren
id|__unused__
)paren
)paren
id|uhci_show_sc
(paren
r_int
id|port
comma
r_int
r_int
id|status
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;  stat%d     =     %04x   %s%s%s%s%s%s%s%s&quot;
comma
id|port
comma
id|status
comma
(paren
id|status
op_amp
id|USBPORTSC_SUSP
)paren
ques
c_cond
l_string|&quot;PortSuspend &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|USBPORTSC_PR
)paren
ques
c_cond
l_string|&quot;PortReset &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|USBPORTSC_LSDA
)paren
ques
c_cond
l_string|&quot;LowSpeed &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|USBPORTSC_RD
)paren
ques
c_cond
l_string|&quot;ResumeDetect &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|USBPORTSC_PEC
)paren
ques
c_cond
l_string|&quot;EnableChange &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|USBPORTSC_PE
)paren
ques
c_cond
l_string|&quot;PortEnabled &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|USBPORTSC_CSC
)paren
ques
c_cond
l_string|&quot;ConnectChange &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|USBPORTSC_CCS
)paren
ques
c_cond
l_string|&quot;PortConnected &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
DECL|function|uhci_show_status
r_void
id|uhci_show_status
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
)paren
(brace
r_int
r_int
id|io_addr
op_assign
(paren
r_int
r_int
)paren
id|uhci-&gt;hcd.regs
suffix:semicolon
r_int
r_int
id|usbcmd
comma
id|usbstat
comma
id|usbint
comma
id|usbfrnum
suffix:semicolon
r_int
r_int
id|flbaseadd
suffix:semicolon
r_int
r_char
id|sof
suffix:semicolon
r_int
r_int
id|portsc1
comma
id|portsc2
suffix:semicolon
id|usbcmd
op_assign
id|inw
(paren
id|io_addr
op_plus
l_int|0
)paren
suffix:semicolon
id|usbstat
op_assign
id|inw
(paren
id|io_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|usbint
op_assign
id|inw
(paren
id|io_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|usbfrnum
op_assign
id|inw
(paren
id|io_addr
op_plus
l_int|6
)paren
suffix:semicolon
id|flbaseadd
op_assign
id|inl
(paren
id|io_addr
op_plus
l_int|8
)paren
suffix:semicolon
id|sof
op_assign
id|inb
(paren
id|io_addr
op_plus
l_int|12
)paren
suffix:semicolon
id|portsc1
op_assign
id|inw
(paren
id|io_addr
op_plus
l_int|16
)paren
suffix:semicolon
id|portsc2
op_assign
id|inw
(paren
id|io_addr
op_plus
l_int|18
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;  usbcmd    =     %04x   %s%s%s%s%s%s%s%s&quot;
comma
id|usbcmd
comma
(paren
id|usbcmd
op_amp
id|USBCMD_MAXP
)paren
ques
c_cond
l_string|&quot;Maxp64 &quot;
suffix:colon
l_string|&quot;Maxp32 &quot;
comma
(paren
id|usbcmd
op_amp
id|USBCMD_CF
)paren
ques
c_cond
l_string|&quot;CF &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|usbcmd
op_amp
id|USBCMD_SWDBG
)paren
ques
c_cond
l_string|&quot;SWDBG &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|usbcmd
op_amp
id|USBCMD_FGR
)paren
ques
c_cond
l_string|&quot;FGR &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|usbcmd
op_amp
id|USBCMD_EGSM
)paren
ques
c_cond
l_string|&quot;EGSM &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|usbcmd
op_amp
id|USBCMD_GRESET
)paren
ques
c_cond
l_string|&quot;GRESET &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|usbcmd
op_amp
id|USBCMD_HCRESET
)paren
ques
c_cond
l_string|&quot;HCRESET &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|usbcmd
op_amp
id|USBCMD_RS
)paren
ques
c_cond
l_string|&quot;RS &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;  usbstat   =     %04x   %s%s%s%s%s%s&quot;
comma
id|usbstat
comma
(paren
id|usbstat
op_amp
id|USBSTS_HCH
)paren
ques
c_cond
l_string|&quot;HCHalted &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|usbstat
op_amp
id|USBSTS_HCPE
)paren
ques
c_cond
l_string|&quot;HostControllerProcessError &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|usbstat
op_amp
id|USBSTS_HSE
)paren
ques
c_cond
l_string|&quot;HostSystemError &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|usbstat
op_amp
id|USBSTS_RD
)paren
ques
c_cond
l_string|&quot;ResumeDetect &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|usbstat
op_amp
id|USBSTS_ERROR
)paren
ques
c_cond
l_string|&quot;USBError &quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|usbstat
op_amp
id|USBSTS_USBINT
)paren
ques
c_cond
l_string|&quot;USBINT &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;  usbint    =     %04x&quot;
comma
id|usbint
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;  usbfrnum  =   (%d)%03x&quot;
comma
(paren
id|usbfrnum
op_rshift
l_int|10
)paren
op_amp
l_int|1
comma
l_int|0xfff
op_amp
(paren
l_int|4
op_star
(paren
r_int
r_int
)paren
id|usbfrnum
)paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;  flbaseadd = %08x&quot;
comma
id|flbaseadd
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;  sof       =       %02x&quot;
comma
id|sof
)paren
suffix:semicolon
id|uhci_show_sc
(paren
l_int|1
comma
id|portsc1
)paren
suffix:semicolon
id|uhci_show_sc
(paren
l_int|2
comma
id|portsc2
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
