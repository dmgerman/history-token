multiline_comment|/* $Id: isurf.c,v 1.10.6.2 2001/09/23 22:24:49 kai Exp $&n; *&n; * low level stuff for Siemens I-Surf/I-Talk cards&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;isar.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &lt;linux/isapnp.h&gt;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|ISurf_revision
r_static
r_const
r_char
op_star
id|ISurf_revision
op_assign
l_string|&quot;$Revision: 1.10.6.2 $&quot;
suffix:semicolon
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
DECL|macro|ISURF_ISAR_RESET
mdefine_line|#define ISURF_ISAR_RESET&t;1
DECL|macro|ISURF_ISAC_RESET
mdefine_line|#define ISURF_ISAC_RESET&t;2
DECL|macro|ISURF_ISAR_EA
mdefine_line|#define ISURF_ISAR_EA&t;&t;4
DECL|macro|ISURF_ARCOFI_RESET
mdefine_line|#define ISURF_ARCOFI_RESET&t;8
DECL|macro|ISURF_RESET
mdefine_line|#define ISURF_RESET (ISURF_ISAR_RESET | ISURF_ISAC_RESET | ISURF_ARCOFI_RESET)
DECL|macro|ISURF_ISAR_OFFSET
mdefine_line|#define ISURF_ISAR_OFFSET&t;0
DECL|macro|ISURF_ISAC_OFFSET
mdefine_line|#define ISURF_ISAC_OFFSET&t;0x100
DECL|macro|ISURF_IOMEM_SIZE
mdefine_line|#define ISURF_IOMEM_SIZE&t;0x400
multiline_comment|/* Interface functions */
r_static
id|u_char
DECL|function|ReadISAC
id|ReadISAC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|offset
)paren
(brace
r_return
(paren
id|readb
c_func
(paren
id|cs-&gt;hw.isurf.isac
op_plus
id|offset
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteISAC
id|WriteISAC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|offset
comma
id|u_char
id|value
)paren
(brace
id|writeb
c_func
(paren
id|value
comma
id|cs-&gt;hw.isurf.isac
op_plus
id|offset
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ReadISACfifo
id|ReadISACfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_register
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
id|size
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
id|i
)braket
op_assign
id|readb
c_func
(paren
id|cs-&gt;hw.isurf.isac
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteISACfifo
id|WriteISACfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_register
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
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|writeb
c_func
(paren
id|data
(braket
id|i
)braket
comma
id|cs-&gt;hw.isurf.isac
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* ISAR access routines&n; * mode = 0 access with IRQ on&n; * mode = 1 access with IRQ off&n; * mode = 2 access with IRQ off and using last offset&n; */
r_static
id|u_char
DECL|function|ReadISAR
id|ReadISAR
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|mode
comma
id|u_char
id|offset
)paren
(brace
r_return
id|readb
c_func
(paren
id|cs-&gt;hw.isurf.isar
op_plus
id|offset
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteISAR
id|WriteISAR
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|mode
comma
id|u_char
id|offset
comma
id|u_char
id|value
)paren
(brace
id|writeb
c_func
(paren
id|value
comma
id|cs-&gt;hw.isurf.isar
op_plus
id|offset
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|isurf_interrupt
id|isurf_interrupt
c_func
(paren
r_int
id|intno
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
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|dev_id
suffix:semicolon
id|u_char
id|val
suffix:semicolon
r_int
id|cnt
op_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ISurf: Spurious interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|val
op_assign
id|readb
c_func
(paren
id|cs-&gt;hw.isurf.isar
op_plus
id|ISAR_IRQBIT
)paren
suffix:semicolon
id|Start_ISAR
suffix:colon
r_if
c_cond
(paren
id|val
op_amp
id|ISAR_IRQSTA
)paren
id|isar_int_main
c_func
(paren
id|cs
)paren
suffix:semicolon
id|val
op_assign
id|readb
c_func
(paren
id|cs-&gt;hw.isurf.isac
op_plus
id|ISAC_ISTA
)paren
suffix:semicolon
id|Start_ISAC
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|isac_interrupt
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|readb
c_func
(paren
id|cs-&gt;hw.isurf.isar
op_plus
id|ISAR_IRQBIT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|val
op_amp
id|ISAR_IRQSTA
)paren
op_logical_and
op_decrement
id|cnt
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAR IntStat after IntRoutine&quot;
)paren
suffix:semicolon
r_goto
id|Start_ISAR
suffix:semicolon
)brace
id|val
op_assign
id|readb
c_func
(paren
id|cs-&gt;hw.isurf.isac
op_plus
id|ISAC_ISTA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_logical_and
op_decrement
id|cnt
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC IntStat after IntRoutine&quot;
)paren
suffix:semicolon
r_goto
id|Start_ISAC
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cnt
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ISurf IRQ LOOP&bslash;n&quot;
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
id|cs-&gt;hw.isurf.isar
op_plus
id|ISAR_IRQBIT
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0xFF
comma
id|cs-&gt;hw.isurf.isac
op_plus
id|ISAC_MASK
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
id|cs-&gt;hw.isurf.isac
op_plus
id|ISAC_MASK
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|ISAR_IRQMSK
comma
id|cs-&gt;hw.isurf.isar
op_plus
id|ISAR_IRQBIT
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|release_io_isurf
id|release_io_isurf
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|release_region
c_func
(paren
id|cs-&gt;hw.isurf.reset
comma
l_int|1
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|cs-&gt;hw.isurf.isar
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|cs-&gt;hw.isurf.phymem
comma
id|ISURF_IOMEM_SIZE
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|reset_isurf
id|reset_isurf
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|chips
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ISurf: resetting card&bslash;n&quot;
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.isurf.reset
comma
id|chips
)paren
suffix:semicolon
multiline_comment|/* Reset On */
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|10
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.isurf.reset
comma
id|ISURF_ISAR_EA
)paren
suffix:semicolon
multiline_comment|/* Reset Off */
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|10
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ISurf_card_msg
id|ISurf_card_msg
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|mt
comma
r_void
op_star
id|arg
)paren
(brace
r_switch
c_cond
(paren
id|mt
)paren
(brace
r_case
id|CARD_RESET
suffix:colon
id|reset_isurf
c_func
(paren
id|cs
comma
id|ISURF_RESET
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_RELEASE
suffix:colon
id|release_io_isurf
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_INIT
suffix:colon
id|clear_pending_isac_ints
c_func
(paren
id|cs
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
id|cs-&gt;hw.isurf.isar
op_plus
id|ISAR_IRQBIT
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|initisac
c_func
(paren
id|cs
)paren
suffix:semicolon
id|initisar
c_func
(paren
id|cs
)paren
suffix:semicolon
multiline_comment|/* Reenable ISAC IRQ */
id|cs
op_member_access_from_pointer
id|writeisac
c_func
(paren
id|cs
comma
id|ISAC_MASK
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* RESET Receiver and Transmitter */
id|cs
op_member_access_from_pointer
id|writeisac
c_func
(paren
id|cs
comma
id|ISAC_CMDR
comma
l_int|0x41
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_TEST
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|isurf_auxcmd
id|isurf_auxcmd
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|isdn_ctrl
op_star
id|ic
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ic-&gt;command
op_eq
id|ISDN_CMD_IOCTL
)paren
op_logical_and
(paren
id|ic-&gt;arg
op_eq
l_int|9
)paren
)paren
(brace
id|ret
op_assign
id|isar_auxcmd
c_func
(paren
id|cs
comma
id|ic
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|reset_isurf
c_func
(paren
id|cs
comma
id|ISURF_ISAR_EA
op_or
id|ISURF_ISAC_RESET
op_or
id|ISURF_ARCOFI_RESET
)paren
suffix:semicolon
id|initisac
c_func
(paren
id|cs
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|writeisac
c_func
(paren
id|cs
comma
id|ISAC_MASK
comma
l_int|0
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|writeisac
c_func
(paren
id|cs
comma
id|ISAC_CMDR
comma
l_int|0x41
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_return
id|isar_auxcmd
c_func
(paren
id|cs
comma
id|ic
)paren
suffix:semicolon
)brace
macro_line|#ifdef __ISAPNP__
DECL|variable|__devinitdata
r_static
r_struct
id|pci_bus
op_star
id|pnp_surf
id|__devinitdata
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
r_int
id|__init
DECL|function|setup_isurf
id|setup_isurf
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
r_int
id|ver
suffix:semicolon
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|card-&gt;cs
suffix:semicolon
r_char
id|tmp
(braket
l_int|64
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|tmp
comma
id|ISurf_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: ISurf driver Rev. %s&bslash;n&quot;
comma
id|HiSax_getrev
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_ISURF
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;para
(braket
l_int|1
)braket
op_logical_and
id|card-&gt;para
(braket
l_int|2
)braket
)paren
(brace
id|cs-&gt;hw.isurf.reset
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
id|cs-&gt;hw.isurf.phymem
op_assign
id|card-&gt;para
(braket
l_int|2
)braket
suffix:semicolon
id|cs-&gt;irq
op_assign
id|card-&gt;para
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef __ISAPNP__
r_struct
id|pci_bus
op_star
id|pb
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pd
suffix:semicolon
r_if
c_cond
(paren
id|isapnp_present
c_func
(paren
)paren
)paren
(brace
id|cs-&gt;subtyp
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pb
op_assign
id|isapnp_find_card
c_func
(paren
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;I&squot;
comma
l_char|&squot;E&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0010
)paren
comma
id|pnp_surf
)paren
)paren
)paren
(brace
id|pnp_surf
op_assign
id|pb
suffix:semicolon
id|pd
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pd
op_assign
id|isapnp_find_dev
c_func
(paren
id|pnp_surf
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;I&squot;
comma
l_char|&squot;E&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0010
)paren
comma
id|pd
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ISurfPnP: PnP error card found, no device&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|pd
op_member_access_from_pointer
id|prepare
c_func
(paren
id|pd
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|pd
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|activate
c_func
(paren
id|pd
)paren
suffix:semicolon
id|cs-&gt;hw.isurf.reset
op_assign
id|pd-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|cs-&gt;hw.isurf.phymem
op_assign
id|pd-&gt;resource
(braket
l_int|1
)braket
dot
id|start
suffix:semicolon
id|cs-&gt;irq
op_assign
id|pd-&gt;irq_resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs-&gt;irq
op_logical_or
op_logical_neg
id|cs-&gt;hw.isurf.reset
op_logical_or
op_logical_neg
id|cs-&gt;hw.isurf.phymem
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ISurfPnP:some resources are missing %d/%x/%lx&bslash;n&quot;
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.isurf.reset
comma
id|cs-&gt;hw.isurf.phymem
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|pd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ISurfPnP: no ISAPnP card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ISurfPnP: no ISAPnP bus found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s port/mem not set&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|cs-&gt;hw.isurf.reset
comma
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s config port %x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|cs-&gt;hw.isurf.reset
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|request_region
c_func
(paren
id|cs-&gt;hw.isurf.reset
comma
l_int|1
comma
l_string|&quot;isurf isdn&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_mem_region
c_func
(paren
id|cs-&gt;hw.isurf.phymem
comma
id|ISURF_IOMEM_SIZE
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s memory region %lx-%lx already in use&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|cs-&gt;hw.isurf.phymem
comma
id|cs-&gt;hw.isurf.phymem
op_plus
id|ISURF_IOMEM_SIZE
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|cs-&gt;hw.isurf.reset
comma
l_int|1
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|request_mem_region
c_func
(paren
id|cs-&gt;hw.isurf.phymem
comma
id|ISURF_IOMEM_SIZE
comma
l_string|&quot;isurf iomem&quot;
)paren
suffix:semicolon
)brace
id|cs-&gt;hw.isurf.isar
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|cs-&gt;hw.isurf.phymem
comma
id|ISURF_IOMEM_SIZE
)paren
suffix:semicolon
id|cs-&gt;hw.isurf.isac
op_assign
id|cs-&gt;hw.isurf.isar
op_plus
id|ISURF_ISAC_OFFSET
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ISurf: defined at 0x%x 0x%lx IRQ %d&bslash;n&quot;
comma
id|cs-&gt;hw.isurf.reset
comma
id|cs-&gt;hw.isurf.phymem
comma
id|cs-&gt;irq
)paren
suffix:semicolon
id|cs-&gt;cardmsg
op_assign
op_amp
id|ISurf_card_msg
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|isurf_interrupt
suffix:semicolon
id|cs-&gt;auxcmd
op_assign
op_amp
id|isurf_auxcmd
suffix:semicolon
id|cs-&gt;readisac
op_assign
op_amp
id|ReadISAC
suffix:semicolon
id|cs-&gt;writeisac
op_assign
op_amp
id|WriteISAC
suffix:semicolon
id|cs-&gt;readisacfifo
op_assign
op_amp
id|ReadISACfifo
suffix:semicolon
id|cs-&gt;writeisacfifo
op_assign
op_amp
id|WriteISACfifo
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|hw.isar.reg
op_assign
op_amp
id|cs-&gt;hw.isurf.isar_r
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|hw.isar.reg
op_assign
op_amp
id|cs-&gt;hw.isurf.isar_r
suffix:semicolon
id|reset_isurf
c_func
(paren
id|cs
comma
id|ISURF_RESET
)paren
suffix:semicolon
id|test_and_set_bit
c_func
(paren
id|HW_ISAR
comma
op_amp
id|cs-&gt;HW_Flags
)paren
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;ISurf:&quot;
)paren
suffix:semicolon
id|cs-&gt;BC_Read_Reg
op_assign
op_amp
id|ReadISAR
suffix:semicolon
id|cs-&gt;BC_Write_Reg
op_assign
op_amp
id|WriteISAR
suffix:semicolon
id|cs-&gt;BC_Send_Data
op_assign
op_amp
id|isar_fill_fifo
suffix:semicolon
id|ver
op_assign
id|ISARVersion
c_func
(paren
id|cs
comma
l_string|&quot;ISurf:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ver
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ISurf: wrong ISAR version (ret = %d)&bslash;n&quot;
comma
id|ver
)paren
suffix:semicolon
id|release_io_isurf
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
