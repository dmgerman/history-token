multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; * &n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2004 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * &n; * This file is licenced under GPL&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * OHCI Root Hub ... the nonsharable stuff&n; */
DECL|macro|dbg_port
mdefine_line|#define dbg_port(hc,label,num,value) &bslash;&n;&t;ohci_dbg (hc, &bslash;&n;&t;&t;&quot;%s roothub.portstatus [%d] &quot; &bslash;&n;&t;&t;&quot;= 0x%08x%s%s%s%s%s%s%s%s%s%s%s%s&bslash;n&quot;, &bslash;&n;&t;&t;label, num, temp, &bslash;&n;&t;&t;(temp &amp; RH_PS_PRSC) ? &quot; PRSC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_OCIC) ? &quot; OCIC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_PSSC) ? &quot; PSSC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_PESC) ? &quot; PESC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_CSC) ? &quot; CSC&quot; : &quot;&quot;, &bslash;&n; &t;&t;&bslash;&n;&t;&t;(temp &amp; RH_PS_LSDA) ? &quot; LSDA&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_PPS) ? &quot; PPS&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_PRS) ? &quot; PRS&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_POCI) ? &quot; POCI&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_PSS) ? &quot; PSS&quot; : &quot;&quot;, &bslash;&n; &t;&t;&bslash;&n;&t;&t;(temp &amp; RH_PS_PES) ? &quot; PES&quot; : &quot;&quot;, &bslash;&n;&t;&t;(temp &amp; RH_PS_CCS) ? &quot; CCS&quot; : &quot;&quot; &bslash;&n;&t;&t;);
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#if&t;defined(CONFIG_USB_SUSPEND) || defined(CONFIG_PM)
DECL|macro|OHCI_SCHED_ENABLES
mdefine_line|#define OHCI_SCHED_ENABLES &bslash;&n;&t;(OHCI_CTRL_CLE|OHCI_CTRL_BLE|OHCI_CTRL_PLE|OHCI_CTRL_IE)
r_static
r_void
id|dl_done_list
(paren
r_struct
id|ohci_hcd
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_static
r_void
id|finish_unlinks
(paren
r_struct
id|ohci_hcd
op_star
comma
id|u16
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_static
r_int
id|ohci_restart
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
)paren
suffix:semicolon
DECL|function|ohci_hub_suspend
r_static
r_int
id|ohci_hub_suspend
(paren
r_struct
id|usb_hcd
op_star
id|hcd
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
r_struct
id|usb_device
op_star
id|root
op_assign
id|hcd_to_bus
(paren
op_amp
id|ohci-&gt;hcd
)paren
op_member_access_from_pointer
id|root_hub
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|root-&gt;dev.power.power_state
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|time_before
(paren
id|jiffies
comma
id|ohci-&gt;next_statechange
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|spin_lock_irq
(paren
op_amp
id|ohci-&gt;lock
)paren
suffix:semicolon
id|ohci-&gt;hc_control
op_assign
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ohci-&gt;hc_control
op_amp
id|OHCI_CTRL_HCFS
)paren
(brace
r_case
id|OHCI_USB_RESUME
suffix:colon
id|ohci_dbg
(paren
id|ohci
comma
l_string|&quot;resume/suspend?&bslash;n&quot;
)paren
suffix:semicolon
id|ohci-&gt;hc_control
op_and_assign
op_complement
id|OHCI_CTRL_HCFS
suffix:semicolon
id|ohci-&gt;hc_control
op_or_assign
id|OHCI_USB_RESET
suffix:semicolon
id|writel
(paren
id|ohci-&gt;hc_control
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
(paren
r_void
)paren
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
multiline_comment|/* FALL THROUGH */
r_case
id|OHCI_USB_RESET
suffix:colon
id|status
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|ohci_dbg
(paren
id|ohci
comma
l_string|&quot;needs reinit!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
r_case
id|OHCI_USB_SUSPEND
suffix:colon
id|ohci_dbg
(paren
id|ohci
comma
l_string|&quot;already suspended?&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|succeed
suffix:semicolon
)brace
id|ohci_dbg
(paren
id|ohci
comma
l_string|&quot;suspend root hub&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* First stop any processing */
id|ohci-&gt;hcd.state
op_assign
id|USB_STATE_QUIESCING
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;hc_control
op_amp
id|OHCI_SCHED_ENABLES
)paren
(brace
r_int
id|limit
suffix:semicolon
id|ohci-&gt;hc_control
op_and_assign
op_complement
id|OHCI_SCHED_ENABLES
suffix:semicolon
id|writel
(paren
id|ohci-&gt;hc_control
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
id|ohci-&gt;hc_control
op_assign
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
id|writel
(paren
id|OHCI_INTR_SF
comma
op_amp
id|ohci-&gt;regs-&gt;intrstatus
)paren
suffix:semicolon
multiline_comment|/* sched disables take effect on the next frame,&n;&t;&t; * then the last WDH could take 6+ msec&n;&t;&t; */
id|ohci_dbg
(paren
id|ohci
comma
l_string|&quot;stopping schedules ...&bslash;n&quot;
)paren
suffix:semicolon
id|limit
op_assign
l_int|2000
suffix:semicolon
r_while
c_loop
(paren
id|limit
OG
l_int|0
)paren
(brace
id|udelay
(paren
l_int|250
)paren
suffix:semicolon
id|limit
op_assign
op_minus
l_int|250
suffix:semicolon
r_if
c_cond
(paren
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;intrstatus
)paren
op_amp
id|OHCI_INTR_SF
)paren
r_break
suffix:semicolon
)brace
id|dl_done_list
(paren
id|ohci
comma
l_int|NULL
)paren
suffix:semicolon
id|mdelay
(paren
l_int|7
)paren
suffix:semicolon
)brace
id|dl_done_list
(paren
id|ohci
comma
l_int|NULL
)paren
suffix:semicolon
id|finish_unlinks
(paren
id|ohci
comma
id|OHCI_FRAME_NO
c_func
(paren
id|ohci-&gt;hcca
)paren
comma
l_int|NULL
)paren
suffix:semicolon
id|writel
(paren
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;intrstatus
)paren
comma
op_amp
id|ohci-&gt;regs-&gt;intrstatus
)paren
suffix:semicolon
multiline_comment|/* maybe resume can wake root hub */
r_if
c_cond
(paren
id|ohci-&gt;hcd.remote_wakeup
)paren
id|ohci-&gt;hc_control
op_or_assign
id|OHCI_CTRL_RWE
suffix:semicolon
r_else
id|ohci-&gt;hc_control
op_and_assign
op_complement
id|OHCI_CTRL_RWE
suffix:semicolon
multiline_comment|/* Suspend hub */
id|ohci-&gt;hc_control
op_and_assign
op_complement
id|OHCI_CTRL_HCFS
suffix:semicolon
id|ohci-&gt;hc_control
op_or_assign
id|OHCI_USB_SUSPEND
suffix:semicolon
id|writel
(paren
id|ohci-&gt;hc_control
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
(paren
r_void
)paren
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
multiline_comment|/* no resumes until devices finish suspending */
id|ohci-&gt;next_statechange
op_assign
id|jiffies
op_plus
id|msecs_to_jiffies
(paren
l_int|5
)paren
suffix:semicolon
id|succeed
suffix:colon
multiline_comment|/* it&squot;s not HCD_STATE_SUSPENDED unless access to this&n;&t; * hub from the non-usb side (PCI, SOC, etc) stopped &n;&t; */
id|root-&gt;dev.power.power_state
op_assign
l_int|3
suffix:semicolon
id|usb_set_device_state
(paren
id|root
comma
id|USB_STATE_SUSPENDED
)paren
suffix:semicolon
id|done
suffix:colon
id|spin_unlock_irq
(paren
op_amp
id|ohci-&gt;lock
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|find_head
r_static
r_inline
r_struct
id|ed
op_star
id|find_head
(paren
r_struct
id|ed
op_star
id|ed
)paren
(brace
multiline_comment|/* for bulk and control lists */
r_while
c_loop
(paren
id|ed-&gt;ed_prev
)paren
id|ed
op_assign
id|ed-&gt;ed_prev
suffix:semicolon
r_return
id|ed
suffix:semicolon
)brace
multiline_comment|/* caller has locked the root hub */
DECL|function|ohci_hub_resume
r_static
r_int
id|ohci_hub_resume
(paren
r_struct
id|usb_hcd
op_star
id|hcd
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
r_struct
id|usb_device
op_star
id|root
op_assign
id|hcd_to_bus
(paren
op_amp
id|ohci-&gt;hcd
)paren
op_member_access_from_pointer
id|root_hub
suffix:semicolon
id|u32
id|temp
comma
id|enables
suffix:semicolon
r_int
id|status
op_assign
op_minus
id|EINPROGRESS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root-&gt;dev.power.power_state
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|time_before
(paren
id|jiffies
comma
id|ohci-&gt;next_statechange
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|spin_lock_irq
(paren
op_amp
id|ohci-&gt;lock
)paren
suffix:semicolon
id|ohci-&gt;hc_control
op_assign
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;hc_control
op_amp
(paren
id|OHCI_CTRL_IR
op_or
id|OHCI_SCHED_ENABLES
)paren
)paren
(brace
multiline_comment|/* this can happen after suspend-to-disk */
id|ohci_dbg
(paren
id|ohci
comma
l_string|&quot;BIOS/SMM active, control %03x&bslash;n&quot;
comma
id|ohci-&gt;hc_control
)paren
suffix:semicolon
id|status
op_assign
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
r_switch
c_cond
(paren
id|ohci-&gt;hc_control
op_amp
id|OHCI_CTRL_HCFS
)paren
(brace
r_case
id|OHCI_USB_SUSPEND
suffix:colon
id|ohci-&gt;hc_control
op_and_assign
op_complement
(paren
id|OHCI_CTRL_HCFS
op_or
id|OHCI_SCHED_ENABLES
)paren
suffix:semicolon
id|ohci-&gt;hc_control
op_or_assign
id|OHCI_USB_RESUME
suffix:semicolon
id|writel
(paren
id|ohci-&gt;hc_control
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
(paren
r_void
)paren
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
id|ohci_dbg
(paren
id|ohci
comma
l_string|&quot;resume root hub&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OHCI_USB_RESUME
suffix:colon
multiline_comment|/* HCFS changes sometime after INTR_RD */
id|ohci_info
(paren
id|ohci
comma
l_string|&quot;wakeup&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OHCI_USB_OPER
suffix:colon
id|ohci_dbg
(paren
id|ohci
comma
l_string|&quot;odd resume&bslash;n&quot;
)paren
suffix:semicolon
id|root-&gt;dev.power.power_state
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* RESET, we lost power */
id|ohci_dbg
(paren
id|ohci
comma
l_string|&quot;root hub hardware reset&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
op_minus
id|EBUSY
suffix:semicolon
)brace
id|spin_unlock_irq
(paren
op_amp
id|ohci-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
op_minus
id|EBUSY
)paren
(brace
(paren
r_void
)paren
id|ohci_init
(paren
id|ohci
)paren
suffix:semicolon
r_return
id|ohci_restart
(paren
id|ohci
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_ne
op_minus
id|EINPROGRESS
)paren
r_return
id|status
suffix:semicolon
id|temp
op_assign
id|roothub_a
(paren
id|ohci
)paren
op_amp
id|RH_A_NDP
suffix:semicolon
id|enables
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|temp
op_decrement
)paren
(brace
id|u32
id|stat
op_assign
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;roothub.portstatus
(braket
id|temp
)braket
)paren
suffix:semicolon
multiline_comment|/* force global, not selective, resume */
r_if
c_cond
(paren
op_logical_neg
(paren
id|stat
op_amp
id|RH_PS_PSS
)paren
)paren
r_continue
suffix:semicolon
id|writel
(paren
id|RH_PS_POCI
comma
op_amp
id|ohci-&gt;regs-&gt;roothub.portstatus
(braket
id|temp
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Some controllers (lucent) need extra-long delays */
id|ohci-&gt;hcd.state
op_assign
id|USB_STATE_RESUMING
suffix:semicolon
id|mdelay
(paren
l_int|20
multiline_comment|/* usb 11.5.1.10 */
op_plus
l_int|15
)paren
suffix:semicolon
id|temp
op_assign
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
id|temp
op_and_assign
id|OHCI_CTRL_HCFS
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_ne
id|OHCI_USB_RESUME
)paren
(brace
id|ohci_err
(paren
id|ohci
comma
l_string|&quot;controller won&squot;t resume&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* disable old schedule state, reinit from scratch */
id|writel
(paren
l_int|0
comma
op_amp
id|ohci-&gt;regs-&gt;ed_controlhead
)paren
suffix:semicolon
id|writel
(paren
l_int|0
comma
op_amp
id|ohci-&gt;regs-&gt;ed_controlcurrent
)paren
suffix:semicolon
id|writel
(paren
l_int|0
comma
op_amp
id|ohci-&gt;regs-&gt;ed_bulkhead
)paren
suffix:semicolon
id|writel
(paren
l_int|0
comma
op_amp
id|ohci-&gt;regs-&gt;ed_bulkcurrent
)paren
suffix:semicolon
id|writel
(paren
l_int|0
comma
op_amp
id|ohci-&gt;regs-&gt;ed_periodcurrent
)paren
suffix:semicolon
id|writel
(paren
(paren
id|u32
)paren
id|ohci-&gt;hcca_dma
comma
op_amp
id|ohci-&gt;regs-&gt;hcca
)paren
suffix:semicolon
id|periodic_reinit
(paren
id|ohci
)paren
suffix:semicolon
multiline_comment|/* interrupts might have been disabled */
id|writel
(paren
id|OHCI_INTR_INIT
comma
op_amp
id|ohci-&gt;regs-&gt;intrenable
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;ed_rm_list
)paren
id|writel
(paren
id|OHCI_INTR_SF
comma
op_amp
id|ohci-&gt;regs-&gt;intrenable
)paren
suffix:semicolon
id|writel
(paren
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;intrstatus
)paren
comma
op_amp
id|ohci-&gt;regs-&gt;intrstatus
)paren
suffix:semicolon
multiline_comment|/* Then re-enable operations */
id|writel
(paren
id|OHCI_USB_OPER
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
(paren
r_void
)paren
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
id|msleep
(paren
l_int|3
)paren
suffix:semicolon
id|temp
op_assign
id|OHCI_CONTROL_INIT
op_or
id|OHCI_USB_OPER
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;hcd.can_wakeup
)paren
id|temp
op_or_assign
id|OHCI_CTRL_RWC
suffix:semicolon
id|ohci-&gt;hc_control
op_assign
id|temp
suffix:semicolon
id|writel
(paren
id|temp
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
(paren
r_void
)paren
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
multiline_comment|/* TRSMRCY */
id|msleep
(paren
l_int|10
)paren
suffix:semicolon
id|root-&gt;dev.power.power_state
op_assign
l_int|0
suffix:semicolon
id|usb_set_device_state
(paren
id|root
comma
id|USB_STATE_CONFIGURED
)paren
suffix:semicolon
multiline_comment|/* keep it alive for ~5x suspend + resume costs */
id|ohci-&gt;next_statechange
op_assign
id|jiffies
op_plus
id|msecs_to_jiffies
(paren
l_int|250
)paren
suffix:semicolon
multiline_comment|/* maybe turn schedules back on */
id|enables
op_assign
l_int|0
suffix:semicolon
id|temp
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ohci-&gt;ed_rm_list
)paren
(brace
r_if
c_cond
(paren
id|ohci-&gt;ed_controltail
)paren
(brace
id|writel
(paren
id|find_head
(paren
id|ohci-&gt;ed_controltail
)paren
op_member_access_from_pointer
id|dma
comma
op_amp
id|ohci-&gt;regs-&gt;ed_controlhead
)paren
suffix:semicolon
id|enables
op_or_assign
id|OHCI_CTRL_CLE
suffix:semicolon
id|temp
op_or_assign
id|OHCI_CLF
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ohci-&gt;ed_bulktail
)paren
(brace
id|writel
(paren
id|find_head
(paren
id|ohci-&gt;ed_bulktail
)paren
op_member_access_from_pointer
id|dma
comma
op_amp
id|ohci-&gt;regs-&gt;ed_bulkhead
)paren
suffix:semicolon
id|enables
op_or_assign
id|OHCI_CTRL_BLE
suffix:semicolon
id|temp
op_or_assign
id|OHCI_BLF
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|hcd_to_bus
(paren
op_amp
id|ohci-&gt;hcd
)paren
op_member_access_from_pointer
id|bandwidth_isoc_reqs
op_logical_or
id|hcd_to_bus
(paren
op_amp
id|ohci-&gt;hcd
)paren
op_member_access_from_pointer
id|bandwidth_int_reqs
)paren
id|enables
op_or_assign
id|OHCI_CTRL_PLE
op_or
id|OHCI_CTRL_IE
suffix:semicolon
r_if
c_cond
(paren
id|enables
)paren
(brace
id|ohci_dbg
(paren
id|ohci
comma
l_string|&quot;restarting schedules ... %08x&bslash;n&quot;
comma
id|enables
)paren
suffix:semicolon
id|ohci-&gt;hc_control
op_or_assign
id|enables
suffix:semicolon
id|writel
(paren
id|ohci-&gt;hc_control
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
)paren
id|writel
(paren
id|temp
comma
op_amp
id|ohci-&gt;regs-&gt;cmdstatus
)paren
suffix:semicolon
(paren
r_void
)paren
id|ohci_readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
)brace
id|ohci-&gt;hcd.state
op_assign
id|USB_STATE_RUNNING
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ohci_rh_resume
r_static
r_void
id|ohci_rh_resume
(paren
r_void
op_star
id|_hcd
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|_hcd
suffix:semicolon
id|usb_lock_device
(paren
id|hcd-&gt;self.root_hub
)paren
suffix:semicolon
(paren
r_void
)paren
id|ohci_hub_resume
(paren
id|hcd
)paren
suffix:semicolon
id|usb_unlock_device
(paren
id|hcd-&gt;self.root_hub
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|ohci_rh_resume
r_static
r_void
id|ohci_rh_resume
(paren
r_void
op_star
id|_hcd
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|_hcd
)paren
suffix:semicolon
id|ohci_dbg
c_func
(paren
id|ohci
comma
l_string|&quot;rh_resume ??&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_USB_SUSPEND || CONFIG_PM */
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
r_int
id|can_suspend
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
r_if
c_cond
(paren
op_logical_neg
id|HCD_IS_RUNNING
c_func
(paren
id|ohci-&gt;hcd.state
)paren
)paren
r_return
op_minus
id|ESHUTDOWN
suffix:semicolon
id|ohci_err
(paren
id|ohci
comma
l_string|&quot;bogus NDP=%d, rereads as NDP=%d&bslash;n&quot;
comma
id|ports
comma
id|ohci_readl
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
r_if
c_cond
(paren
id|status
op_amp
(paren
id|RH_PS_CSC
op_or
id|RH_PS_PESC
op_or
id|RH_PS_PSSC
op_or
id|RH_PS_OCIC
op_or
id|RH_PS_PRSC
)paren
)paren
(brace
id|changed
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|7
)paren
id|buf
(braket
l_int|0
)braket
op_or_assign
l_int|1
op_lshift
(paren
id|i
op_plus
l_int|1
)paren
suffix:semicolon
r_else
id|buf
(braket
l_int|1
)braket
op_or_assign
l_int|1
op_lshift
(paren
id|i
op_minus
l_int|7
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* can suspend if no ports are enabled; or if all all&n;&t;&t; * enabled ports are suspended AND remote wakeup is on.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|RH_PS_CCS
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|RH_PS_PSS
)paren
op_logical_and
id|ohci-&gt;hcd.remote_wakeup
)paren
r_continue
suffix:semicolon
id|can_suspend
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
multiline_comment|/* save power by suspending idle root hubs;&n;&t; * INTR_RD wakes us when there&squot;s work&n;&t; */
r_if
c_cond
(paren
id|can_suspend
op_logical_and
op_logical_neg
id|changed
op_logical_and
op_logical_neg
id|ohci-&gt;ed_rm_list
op_logical_and
(paren
(paren
id|OHCI_CTRL_HCFS
op_or
id|OHCI_SCHED_ENABLES
)paren
op_amp
id|ohci-&gt;hc_control
)paren
op_eq
id|OHCI_USB_OPER
op_logical_and
id|usb_trylock_device
(paren
id|hcd-&gt;self.root_hub
)paren
)paren
(brace
id|ohci_vdbg
(paren
id|ohci
comma
l_string|&quot;autosuspend&bslash;n&quot;
)paren
suffix:semicolon
(paren
r_void
)paren
id|ohci_hub_suspend
(paren
op_amp
id|ohci-&gt;hcd
)paren
suffix:semicolon
id|ohci-&gt;hcd.state
op_assign
id|USB_STATE_RUNNING
suffix:semicolon
id|usb_unlock_device
(paren
id|hcd-&gt;self.root_hub
)paren
suffix:semicolon
)brace
macro_line|#endif
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
id|RH_A_NPS
)paren
multiline_comment|/* no power switching? */
id|temp
op_or_assign
l_int|0x0002
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
macro_line|#ifdef&t;CONFIG_USB_OTG
DECL|function|ohci_start_port_reset
r_static
r_int
id|ohci_start_port_reset
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_int
id|port
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
id|u32
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|port
op_decrement
suffix:semicolon
multiline_comment|/* start port reset before HNP protocol times out */
id|status
op_assign
id|ohci_readl
c_func
(paren
op_amp
id|ohci-&gt;regs-&gt;roothub.portstatus
(braket
id|port
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|RH_PS_CCS
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* khubd will finish the reset later */
id|writel
c_func
(paren
id|RH_PS_PRS
comma
op_amp
id|ohci-&gt;regs-&gt;roothub.portstatus
(braket
id|port
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|start_hnp
c_func
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
)paren
suffix:semicolon
macro_line|#else
DECL|macro|ohci_start_port_reset
mdefine_line|#define&t;ohci_start_port_reset&t;&t;NULL
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* See usb 7.1.7.5:  root hubs must issue at least 50 msec reset signaling,&n; * not necessarily continuous ... to guard against resume signaling.&n; * The short timeout is safe for non-root hubs, and is backward-compatible&n; * with earlier Linux hosts.&n; */
macro_line|#ifdef&t;CONFIG_USB_SUSPEND
DECL|macro|PORT_RESET_MSEC
mdefine_line|#define&t;PORT_RESET_MSEC&t;&t;50
macro_line|#else
DECL|macro|PORT_RESET_MSEC
mdefine_line|#define&t;PORT_RESET_MSEC&t;&t;10
macro_line|#endif
multiline_comment|/* this timer value might be vendor-specific ... */
DECL|macro|PORT_RESET_HW_MSEC
mdefine_line|#define&t;PORT_RESET_HW_MSEC&t;10
multiline_comment|/* wrap-aware logic morphed from &lt;linux/jiffies.h&gt; */
DECL|macro|tick_before
mdefine_line|#define tick_before(t1,t2) ((s16)(((s16)(t1))-((s16)(t2))) &lt; 0)
multiline_comment|/* called from some task, normally khubd */
DECL|function|root_port_reset
r_static
r_inline
r_void
id|root_port_reset
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_int
id|port
)paren
(brace
id|u32
id|__iomem
op_star
id|portstat
op_assign
op_amp
id|ohci-&gt;regs-&gt;roothub.portstatus
(braket
id|port
)braket
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|u16
id|now
op_assign
id|readl
c_func
(paren
op_amp
id|ohci-&gt;regs-&gt;fmnumber
)paren
suffix:semicolon
id|u16
id|reset_done
op_assign
id|now
op_plus
id|PORT_RESET_MSEC
suffix:semicolon
multiline_comment|/* build a &quot;continuous enough&quot; reset signal, with up to&n;&t; * 3msec gap between pulses.  scheduler HZ==100 must work;&n;&t; * this might need to be deadline-scheduled.&n;&t; */
r_do
(brace
multiline_comment|/* spin until any current reset finishes */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|temp
op_assign
id|ohci_readl
(paren
id|portstat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|temp
op_amp
id|RH_PS_PRS
)paren
)paren
r_break
suffix:semicolon
id|udelay
(paren
l_int|500
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
id|RH_PS_CCS
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|RH_PS_PRSC
)paren
id|writel
(paren
id|RH_PS_PRSC
comma
id|portstat
)paren
suffix:semicolon
multiline_comment|/* start the next reset, sleep till it&squot;s probably done */
id|writel
(paren
id|RH_PS_PRS
comma
id|portstat
)paren
suffix:semicolon
id|msleep
c_func
(paren
id|PORT_RESET_HW_MSEC
)paren
suffix:semicolon
id|now
op_assign
id|readl
c_func
(paren
op_amp
id|ohci-&gt;regs-&gt;fmnumber
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tick_before
c_func
(paren
id|now
comma
id|reset_done
)paren
)paren
suffix:semicolon
multiline_comment|/* caller synchronizes using PRSC */
)brace
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
op_assign
id|hcd_to_bus
(paren
id|hcd
)paren
op_member_access_from_pointer
id|root_hub-&gt;maxchild
suffix:semicolon
id|u32
id|temp
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
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
r_if
c_cond
(paren
(paren
id|ohci-&gt;hc_control
op_amp
id|OHCI_CTRL_HCFS
)paren
op_ne
id|OHCI_USB_OPER
)paren
id|schedule_work
(paren
op_amp
id|ohci-&gt;rh_resume
)paren
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
singleline_comment|// ohci_readl (&amp;ohci-&gt;regs-&gt;roothub.portstatus [wIndex]);
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
id|__le32
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
id|__le32
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
macro_line|#ifdef&t;CONFIG_USB_OTG
r_if
c_cond
(paren
id|ohci-&gt;hcd.self.otg_port
op_eq
(paren
id|wIndex
op_plus
l_int|1
)paren
op_logical_and
id|ohci-&gt;hcd.self.b_hnp_enable
)paren
id|start_hnp
c_func
(paren
id|ohci
)paren
suffix:semicolon
r_else
macro_line|#endif
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
id|root_port_reset
(paren
id|ohci
comma
id|wIndex
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
