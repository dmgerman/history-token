multiline_comment|/*&n; * UHCI-specific debugging code. Invaluable when something&n; * goes wrong, but don&squot;t get in my face.&n; *&n; * Kernel visible pointers are surrounded in []&squot;s and bus&n; * visible pointers are surrounded in ()&squot;s&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; * (C) Copyright 1999-2001 Johannes Erdfelt&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;uhci-hcd.h&quot;
multiline_comment|/* Handle REALLY large printk&squot;s so we don&squot;t overflow buffers */
DECL|function|lprintk
r_static
r_inline
r_void
id|lprintk
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
multiline_comment|/* Just write one line at a time */
r_while
c_loop
(paren
id|buf
)paren
(brace
id|p
op_assign
id|strchr
c_func
(paren
id|buf
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
id|buf
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|buf
)paren
id|buf
op_increment
suffix:semicolon
)brace
)brace
DECL|function|uhci_is_skeleton_qh
r_static
r_inline
r_int
id|uhci_is_skeleton_qh
c_func
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
comma
r_struct
id|uhci_qh
op_star
id|qh
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
id|UHCI_NUM_SKELQH
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|qh
op_eq
id|uhci-&gt;skelqh
(braket
id|i
)braket
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|uhci_show_td
r_static
r_int
id|uhci_show_td
c_func
(paren
r_struct
id|uhci_td
op_star
id|td
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|space
)paren
(brace
r_char
op_star
id|out
op_assign
id|buf
suffix:semicolon
r_char
op_star
id|spid
suffix:semicolon
id|u32
id|status
comma
id|token
suffix:semicolon
multiline_comment|/* Try to make sure there&squot;s enough memory */
r_if
c_cond
(paren
id|len
OL
l_int|160
)paren
r_return
l_int|0
suffix:semicolon
id|status
op_assign
id|td_status
c_func
(paren
id|td
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%*s[%p] link (%08x) &quot;
comma
id|space
comma
l_string|&quot;&quot;
comma
id|td
comma
id|le32_to_cpu
c_func
(paren
id|td-&gt;link
)paren
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;e%d %s%s%s%s%s%s%s%s%s%sLength=%x &quot;
comma
(paren
(paren
id|status
op_rshift
l_int|27
)paren
op_amp
l_int|3
)paren
comma
(paren
id|status
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
id|status
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
id|status
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
id|status
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
id|status
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
id|status
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
id|status
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
id|status
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
id|status
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
id|status
op_amp
id|TD_CTRL_BITSTUFF
)paren
ques
c_cond
l_string|&quot;BitStuff &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|status
op_amp
l_int|0x7ff
)paren
suffix:semicolon
id|token
op_assign
id|td_token
c_func
(paren
id|td
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|uhci_packetid
c_func
(paren
id|token
)paren
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
l_string|&quot;OUT&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_PID_IN
suffix:colon
id|spid
op_assign
l_string|&quot;IN&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|spid
op_assign
l_string|&quot;?&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;MaxLen=%x DT%d EndPt=%x Dev=%x, PID=%x(%s) &quot;
comma
id|token
op_rshift
l_int|21
comma
(paren
(paren
id|token
op_rshift
l_int|19
)paren
op_amp
l_int|1
)paren
comma
(paren
id|token
op_rshift
l_int|15
)paren
op_amp
l_int|15
comma
(paren
id|token
op_rshift
l_int|8
)paren
op_amp
l_int|127
comma
(paren
id|token
op_amp
l_int|0xff
)paren
comma
id|spid
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;(buf=%08x)&bslash;n&quot;
comma
id|le32_to_cpu
c_func
(paren
id|td-&gt;buffer
)paren
)paren
suffix:semicolon
r_return
id|out
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|uhci_show_qh
r_static
r_int
id|uhci_show_qh
c_func
(paren
r_struct
id|uhci_qh
op_star
id|qh
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|space
)paren
(brace
r_char
op_star
id|out
op_assign
id|buf
suffix:semicolon
r_struct
id|urb_priv
op_star
id|urbp
suffix:semicolon
r_struct
id|list_head
op_star
id|head
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|uhci_td
op_star
id|td
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|checked
op_assign
l_int|0
comma
id|prevactive
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Try to make sure there&squot;s enough memory */
r_if
c_cond
(paren
id|len
OL
l_int|80
op_star
l_int|6
)paren
r_return
l_int|0
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%*s[%p] link (%08x) element (%08x)&bslash;n&quot;
comma
id|space
comma
l_string|&quot;&quot;
comma
id|qh
comma
id|le32_to_cpu
c_func
(paren
id|qh-&gt;link
)paren
comma
id|le32_to_cpu
c_func
(paren
id|qh-&gt;element
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qh-&gt;element
op_amp
id|UHCI_PTR_QH
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%*s  Element points to QH (bug?)&bslash;n&quot;
comma
id|space
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qh-&gt;element
op_amp
id|UHCI_PTR_DEPTH
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%*s  Depth traverse&bslash;n&quot;
comma
id|space
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qh-&gt;element
op_amp
id|cpu_to_le32
c_func
(paren
l_int|8
)paren
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%*s  Bit 3 set (bug?)&bslash;n&quot;
comma
id|space
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|qh-&gt;element
op_amp
op_complement
(paren
id|UHCI_PTR_QH
op_or
id|UHCI_PTR_DEPTH
)paren
)paren
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%*s  Element is NULL (bug?)&bslash;n&quot;
comma
id|space
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|qh-&gt;urbp
)paren
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%*s  urbp == NULL&bslash;n&quot;
comma
id|space
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|urbp
op_assign
id|qh-&gt;urbp
suffix:semicolon
id|head
op_assign
op_amp
id|urbp-&gt;td_list
suffix:semicolon
id|tmp
op_assign
id|head-&gt;next
suffix:semicolon
id|td
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|uhci_td
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_to_le32
c_func
(paren
id|td-&gt;dma_handle
)paren
op_ne
(paren
id|qh-&gt;element
op_amp
op_complement
id|UHCI_PTR_BITS
)paren
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%*s Element != First TD&bslash;n&quot;
comma
id|space
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tmp
op_ne
id|head
)paren
(brace
r_struct
id|uhci_td
op_star
id|td
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|uhci_td
comma
id|list
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%*s%d: &quot;
comma
id|space
op_plus
l_int|2
comma
l_string|&quot;&quot;
comma
id|i
op_increment
)paren
suffix:semicolon
id|out
op_add_assign
id|uhci_show_td
c_func
(paren
id|td
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|10
op_logical_and
op_logical_neg
id|checked
op_logical_and
id|prevactive
op_logical_and
id|tmp
op_ne
id|head
op_logical_and
id|debug
op_le
l_int|2
)paren
(brace
r_struct
id|list_head
op_star
id|ntmp
op_assign
id|tmp
suffix:semicolon
r_struct
id|uhci_td
op_star
id|ntd
op_assign
id|td
suffix:semicolon
r_int
id|active
op_assign
l_int|1
comma
id|ni
op_assign
id|i
suffix:semicolon
id|checked
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|ntmp
op_ne
id|head
op_logical_and
id|ntmp-&gt;next
op_ne
id|head
op_logical_and
id|active
)paren
(brace
id|ntd
op_assign
id|list_entry
c_func
(paren
id|ntmp
comma
r_struct
id|uhci_td
comma
id|list
)paren
suffix:semicolon
id|ntmp
op_assign
id|ntmp-&gt;next
suffix:semicolon
id|active
op_assign
id|td_status
c_func
(paren
id|ntd
)paren
op_amp
id|TD_CTRL_ACTIVE
suffix:semicolon
id|ni
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|active
op_logical_and
id|ni
OG
id|i
)paren
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%*s[skipped %d active TD&squot;s]&bslash;n&quot;
comma
id|space
comma
l_string|&quot;&quot;
comma
id|ni
op_minus
id|i
)paren
suffix:semicolon
id|tmp
op_assign
id|ntmp
suffix:semicolon
id|td
op_assign
id|ntd
suffix:semicolon
id|i
op_assign
id|ni
suffix:semicolon
)brace
)brace
id|prevactive
op_assign
id|td_status
c_func
(paren
id|td
)paren
op_amp
id|TD_CTRL_ACTIVE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|urbp-&gt;queue_list
)paren
op_logical_or
id|urbp-&gt;queued
)paren
r_goto
id|out
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%*sQueued QH&squot;s:&bslash;n&quot;
comma
op_minus
id|space
comma
l_string|&quot;--&quot;
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|urbp-&gt;queue_list
suffix:semicolon
id|tmp
op_assign
id|head-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|tmp
op_ne
id|head
)paren
(brace
r_struct
id|urb_priv
op_star
id|nurbp
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|urb_priv
comma
id|queue_list
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
id|out
op_add_assign
id|uhci_show_qh
c_func
(paren
id|nurbp-&gt;qh
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
comma
id|space
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|out
op_minus
id|buf
suffix:semicolon
)brace
DECL|macro|show_frame_num
mdefine_line|#define show_frame_num()&t;&bslash;&n;&t;if (!shown) {&t;&t;&bslash;&n;&t;  shown = 1;&t;&t;&bslash;&n;&t;  out += sprintf(out, &quot;- Frame %d&bslash;n&quot;, i); &bslash;&n;&t;}
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|qh_names
r_static
r_const
r_char
op_star
id|qh_names
(braket
)braket
op_assign
(brace
l_string|&quot;skel_int128_qh&quot;
comma
l_string|&quot;skel_int64_qh&quot;
comma
l_string|&quot;skel_int32_qh&quot;
comma
l_string|&quot;skel_int16_qh&quot;
comma
l_string|&quot;skel_int8_qh&quot;
comma
l_string|&quot;skel_int4_qh&quot;
comma
l_string|&quot;skel_int2_qh&quot;
comma
l_string|&quot;skel_int1_qh&quot;
comma
l_string|&quot;skel_ls_control_qh&quot;
comma
l_string|&quot;skel_hs_control_qh&quot;
comma
l_string|&quot;skel_bulk_qh&quot;
comma
l_string|&quot;skel_term_qh&quot;
)brace
suffix:semicolon
DECL|macro|show_qh_name
mdefine_line|#define show_qh_name()&t;&t;&bslash;&n;&t;if (!shown) {&t;&t;&bslash;&n;&t;  shown = 1;&t;&t;&bslash;&n;&t;  out += sprintf(out, &quot;- %s&bslash;n&quot;, qh_names[i]); &bslash;&n;&t;}
DECL|function|uhci_show_sc
r_static
r_int
id|uhci_show_sc
c_func
(paren
r_int
id|port
comma
r_int
r_int
id|status
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_char
op_star
id|out
op_assign
id|buf
suffix:semicolon
multiline_comment|/* Try to make sure there&squot;s enough memory */
r_if
c_cond
(paren
id|len
OL
l_int|160
)paren
r_return
l_int|0
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;  stat%d     =     %04x  %s%s%s%s%s%s%s%s%s%s&bslash;n&quot;
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
l_string|&quot; Suspend&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|USBPORTSC_OCC
)paren
ques
c_cond
l_string|&quot; OverCurrentChange&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|USBPORTSC_OC
)paren
ques
c_cond
l_string|&quot; OverCurrent&quot;
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
l_string|&quot; Reset&quot;
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
l_string|&quot; LowSpeed&quot;
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
l_string|&quot; ResumeDetect&quot;
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
l_string|&quot; EnableChange&quot;
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
l_string|&quot; Enabled&quot;
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
l_string|&quot; ConnectChange&quot;
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
l_string|&quot; Connected&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
id|out
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|uhci_show_status
r_static
r_int
id|uhci_show_status
c_func
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_char
op_star
id|out
op_assign
id|buf
suffix:semicolon
r_int
r_int
id|io_addr
op_assign
id|uhci-&gt;io_addr
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
multiline_comment|/* Try to make sure there&squot;s enough memory */
r_if
c_cond
(paren
id|len
OL
l_int|80
op_star
l_int|6
)paren
r_return
l_int|0
suffix:semicolon
id|usbcmd
op_assign
id|inw
c_func
(paren
id|io_addr
op_plus
l_int|0
)paren
suffix:semicolon
id|usbstat
op_assign
id|inw
c_func
(paren
id|io_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|usbint
op_assign
id|inw
c_func
(paren
id|io_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|usbfrnum
op_assign
id|inw
c_func
(paren
id|io_addr
op_plus
l_int|6
)paren
suffix:semicolon
id|flbaseadd
op_assign
id|inl
c_func
(paren
id|io_addr
op_plus
l_int|8
)paren
suffix:semicolon
id|sof
op_assign
id|inb
c_func
(paren
id|io_addr
op_plus
l_int|12
)paren
suffix:semicolon
id|portsc1
op_assign
id|inw
c_func
(paren
id|io_addr
op_plus
l_int|16
)paren
suffix:semicolon
id|portsc2
op_assign
id|inw
c_func
(paren
id|io_addr
op_plus
l_int|18
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;  usbcmd    =     %04x   %s%s%s%s%s%s%s%s&bslash;n&quot;
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
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;  usbstat   =     %04x   %s%s%s%s%s%s&bslash;n&quot;
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
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;  usbint    =     %04x&bslash;n&quot;
comma
id|usbint
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;  usbfrnum  =   (%d)%03x&bslash;n&quot;
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
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;  flbaseadd = %08x&bslash;n&quot;
comma
id|flbaseadd
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;  sof       =       %02x&bslash;n&quot;
comma
id|sof
)paren
suffix:semicolon
id|out
op_add_assign
id|uhci_show_sc
c_func
(paren
l_int|1
comma
id|portsc1
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
)paren
suffix:semicolon
id|out
op_add_assign
id|uhci_show_sc
c_func
(paren
l_int|2
comma
id|portsc2
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
)paren
suffix:semicolon
r_return
id|out
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|uhci_show_urbp
r_static
r_int
id|uhci_show_urbp
c_func
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
comma
r_struct
id|urb_priv
op_star
id|urbp
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_char
op_star
id|out
op_assign
id|buf
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|200
)paren
r_return
l_int|0
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;urb_priv [%p] &quot;
comma
id|urbp
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;urb [%p] &quot;
comma
id|urbp-&gt;urb
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;qh [%p] &quot;
comma
id|urbp-&gt;qh
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Dev=%d &quot;
comma
id|usb_pipedevice
c_func
(paren
id|urbp-&gt;urb-&gt;pipe
)paren
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;EP=%x(%s) &quot;
comma
id|usb_pipeendpoint
c_func
(paren
id|urbp-&gt;urb-&gt;pipe
)paren
comma
(paren
id|usb_pipein
c_func
(paren
id|urbp-&gt;urb-&gt;pipe
)paren
ques
c_cond
l_string|&quot;IN&quot;
suffix:colon
l_string|&quot;OUT&quot;
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|usb_pipetype
c_func
(paren
id|urbp-&gt;urb-&gt;pipe
)paren
)paren
(brace
r_case
id|PIPE_ISOCHRONOUS
suffix:colon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;ISO &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIPE_INTERRUPT
suffix:colon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;INT &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIPE_BULK
suffix:colon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;BLK &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIPE_CONTROL
suffix:colon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;CTL &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%s&quot;
comma
(paren
id|urbp-&gt;fsbr
ques
c_cond
l_string|&quot;FSBR &quot;
suffix:colon
l_string|&quot;&quot;
)paren
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%s&quot;
comma
(paren
id|urbp-&gt;fsbr_timeout
ques
c_cond
l_string|&quot;FSBR_TO &quot;
suffix:colon
l_string|&quot;&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urbp-&gt;urb-&gt;status
op_ne
op_minus
id|EINPROGRESS
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Status=%d &quot;
comma
id|urbp-&gt;urb-&gt;status
)paren
suffix:semicolon
singleline_comment|//out += sprintf(out, &quot;Inserttime=%lx &quot;,urbp-&gt;inserttime);
singleline_comment|//out += sprintf(out, &quot;FSBRtime=%lx &quot;,urbp-&gt;fsbrtime);
id|spin_lock
c_func
(paren
op_amp
id|urbp-&gt;urb-&gt;lock
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|urbp-&gt;td_list
)paren
id|count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|urbp-&gt;urb-&gt;lock
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;TDs=%d &quot;
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urbp-&gt;queued
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;queued&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|spin_lock
c_func
(paren
op_amp
id|uhci-&gt;frame_list_lock
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|urbp-&gt;queue_list
)paren
id|count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|uhci-&gt;frame_list_lock
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;queued URBs=%d&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
)brace
r_return
id|out
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|uhci_show_lists
r_static
r_int
id|uhci_show_lists
c_func
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_char
op_star
id|out
op_assign
id|buf
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|head
comma
op_star
id|tmp
suffix:semicolon
r_int
id|count
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Main list URBs:&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|uhci-&gt;urb_list
)paren
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot; Empty&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|head
op_assign
op_amp
id|uhci-&gt;urb_list
suffix:semicolon
id|tmp
op_assign
id|head-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|tmp
op_ne
id|head
)paren
(brace
r_struct
id|urb_priv
op_star
id|urbp
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|urb_priv
comma
id|urb_list
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;  %d: &quot;
comma
op_increment
id|count
)paren
suffix:semicolon
id|out
op_add_assign
id|uhci_show_urbp
c_func
(paren
id|uhci
comma
id|urbp
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Remove list URBs:&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|uhci-&gt;urb_remove_list_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|uhci-&gt;urb_remove_list
)paren
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot; Empty&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|head
op_assign
op_amp
id|uhci-&gt;urb_remove_list
suffix:semicolon
id|tmp
op_assign
id|head-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|tmp
op_ne
id|head
)paren
(brace
r_struct
id|urb_priv
op_star
id|urbp
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|urb_priv
comma
id|urb_list
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;  %d: &quot;
comma
op_increment
id|count
)paren
suffix:semicolon
id|out
op_add_assign
id|uhci_show_urbp
c_func
(paren
id|uhci
comma
id|urbp
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|uhci-&gt;urb_remove_list_lock
comma
id|flags
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Complete list URBs:&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|uhci-&gt;complete_list_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|uhci-&gt;complete_list
)paren
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot; Empty&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|head
op_assign
op_amp
id|uhci-&gt;complete_list
suffix:semicolon
id|tmp
op_assign
id|head-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|tmp
op_ne
id|head
)paren
(brace
r_struct
id|urb_priv
op_star
id|urbp
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|urb_priv
comma
id|urb_list
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;  %d: &quot;
comma
op_increment
id|count
)paren
suffix:semicolon
id|out
op_add_assign
id|uhci_show_urbp
c_func
(paren
id|uhci
comma
id|urbp
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|uhci-&gt;complete_list_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|out
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|uhci_sprint_schedule
r_static
r_int
id|uhci_sprint_schedule
c_func
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_char
op_star
id|out
op_assign
id|buf
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_struct
id|uhci_qh
op_star
id|qh
suffix:semicolon
r_struct
id|uhci_td
op_star
id|td
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
comma
op_star
id|head
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|uhci-&gt;frame_list_lock
comma
id|flags
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;HC status&bslash;n&quot;
)paren
suffix:semicolon
id|out
op_add_assign
id|uhci_show_status
c_func
(paren
id|uhci
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Frame List&bslash;n&quot;
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
id|UHCI_NUMFRAMES
suffix:semicolon
op_increment
id|i
)paren
(brace
r_int
id|shown
op_assign
l_int|0
suffix:semicolon
id|td
op_assign
id|uhci-&gt;fl-&gt;frame_cpu
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|td
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|td-&gt;dma_handle
op_ne
(paren
id|dma_addr_t
)paren
id|uhci-&gt;fl-&gt;frame
(braket
id|i
)braket
)paren
(brace
id|show_frame_num
c_func
(paren
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;    frame list does not match td-&gt;dma_handle!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|show_frame_num
c_func
(paren
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|td-&gt;fl_list
suffix:semicolon
id|tmp
op_assign
id|head
suffix:semicolon
r_do
(brace
id|td
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|uhci_td
comma
id|fl_list
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
id|out
op_add_assign
id|uhci_show_td
c_func
(paren
id|td
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
comma
l_int|4
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tmp
op_ne
id|head
)paren
suffix:semicolon
)brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Skeleton QH&squot;s&bslash;n&quot;
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
id|UHCI_NUM_SKELQH
suffix:semicolon
op_increment
id|i
)paren
(brace
r_int
id|shown
op_assign
l_int|0
suffix:semicolon
id|qh
op_assign
id|uhci-&gt;skelqh
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|debug
OG
l_int|1
)paren
(brace
id|show_qh_name
c_func
(paren
)paren
suffix:semicolon
id|out
op_add_assign
id|uhci_show_qh
c_func
(paren
id|qh
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
comma
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/* Last QH is the Terminating QH, it&squot;s different */
r_if
c_cond
(paren
id|i
op_eq
id|UHCI_NUM_SKELQH
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|qh-&gt;link
op_ne
id|UHCI_PTR_TERM
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;    bandwidth reclamation on!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qh-&gt;element
op_ne
id|cpu_to_le32
c_func
(paren
id|uhci-&gt;term_td-&gt;dma_handle
)paren
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;    skel_term_qh element is not set to term_td!&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|j
op_assign
(paren
id|i
OL
l_int|7
)paren
ques
c_cond
l_int|7
suffix:colon
id|i
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Next skeleton */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|qh-&gt;list
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
OL
id|UHCI_NUM_SKELQH
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|qh-&gt;link
op_ne
(paren
id|cpu_to_le32
c_func
(paren
id|uhci-&gt;skelqh
(braket
id|j
)braket
op_member_access_from_pointer
id|dma_handle
)paren
op_or
id|UHCI_PTR_QH
)paren
)paren
(brace
id|show_qh_name
c_func
(paren
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;    skeleton QH not linked to next skeleton QH!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_continue
suffix:semicolon
)brace
id|show_qh_name
c_func
(paren
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|qh-&gt;list
suffix:semicolon
id|tmp
op_assign
id|head-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|tmp
op_ne
id|head
)paren
(brace
id|qh
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|uhci_qh
comma
id|list
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
id|out
op_add_assign
id|uhci_show_qh
c_func
(paren
id|qh
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
comma
l_int|4
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|UHCI_NUM_SKELQH
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|qh-&gt;link
op_ne
(paren
id|cpu_to_le32
c_func
(paren
id|uhci-&gt;skelqh
(braket
id|j
)braket
op_member_access_from_pointer
id|dma_handle
)paren
op_or
id|UHCI_PTR_QH
)paren
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;    last QH not linked to next skeleton!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|uhci-&gt;frame_list_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
OG
l_int|2
)paren
id|out
op_add_assign
id|uhci_show_lists
c_func
(paren
id|uhci
comma
id|out
comma
id|len
op_minus
(paren
id|out
op_minus
id|buf
)paren
)paren
suffix:semicolon
r_return
id|out
op_minus
id|buf
suffix:semicolon
)brace
DECL|macro|MAX_OUTPUT
mdefine_line|#define MAX_OUTPUT&t;(64 * 1024)
DECL|variable|uhci_proc_root
r_static
r_struct
id|proc_dir_entry
op_star
id|uhci_proc_root
op_assign
l_int|NULL
suffix:semicolon
DECL|struct|uhci_proc
r_struct
id|uhci_proc
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|uhci
r_struct
id|uhci_hcd
op_star
id|uhci
suffix:semicolon
)brace
suffix:semicolon
DECL|function|uhci_proc_open
r_static
r_int
id|uhci_proc_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_const
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|uhci_hcd
op_star
id|uhci
op_assign
id|dp-&gt;data
suffix:semicolon
r_struct
id|uhci_proc
op_star
id|up
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|up
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|up
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|up
)paren
r_goto
id|out
suffix:semicolon
id|up-&gt;data
op_assign
id|kmalloc
c_func
(paren
id|MAX_OUTPUT
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|up-&gt;data
)paren
(brace
id|kfree
c_func
(paren
id|up
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|up-&gt;size
op_assign
id|uhci_sprint_schedule
c_func
(paren
id|uhci
comma
id|up-&gt;data
comma
id|MAX_OUTPUT
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
id|up
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|uhci_proc_lseek
r_static
id|loff_t
id|uhci_proc_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|off
comma
r_int
id|whence
)paren
(brace
r_struct
id|uhci_proc
op_star
id|up
suffix:semicolon
id|loff_t
r_new
op_assign
op_minus
l_int|1
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|up
op_assign
id|file-&gt;private_data
suffix:semicolon
r_switch
c_cond
(paren
id|whence
)paren
(brace
r_case
l_int|0
suffix:colon
r_new
op_assign
id|off
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_new
op_assign
id|file-&gt;f_pos
op_plus
id|off
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
r_new
template_param
id|up-&gt;size
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|file-&gt;f_pos
op_assign
r_new
)paren
suffix:semicolon
)brace
DECL|function|uhci_proc_read
r_static
id|ssize_t
id|uhci_proc_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|uhci_proc
op_star
id|up
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|pos
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
id|size
op_assign
id|up-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_ge
id|size
)paren
id|nbytes
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|nbytes
OG
id|size
)paren
id|nbytes
op_assign
id|size
op_minus
id|pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|nbytes
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|up-&gt;data
op_plus
id|pos
comma
id|nbytes
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|ppos
op_add_assign
id|nbytes
suffix:semicolon
r_return
id|nbytes
suffix:semicolon
)brace
DECL|function|uhci_proc_release
r_static
r_int
id|uhci_proc_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|uhci_proc
op_star
id|up
op_assign
id|file-&gt;private_data
suffix:semicolon
id|kfree
c_func
(paren
id|up-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|up
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|uhci_proc_operations
r_static
r_struct
id|file_operations
id|uhci_proc_operations
op_assign
(brace
dot
id|open
op_assign
id|uhci_proc_open
comma
dot
id|llseek
op_assign
id|uhci_proc_lseek
comma
dot
id|read
op_assign
id|uhci_proc_read
comma
singleline_comment|//&t;write:&t;&t;uhci_proc_write,
dot
id|release
op_assign
id|uhci_proc_release
comma
)brace
suffix:semicolon
macro_line|#endif
eof
