multiline_comment|/*&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * Eicon File Revision :    1.10  &n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/sched.h&gt;
DECL|macro|N_DATA
macro_line|#undef N_DATA
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
r_struct
id|pt_regs
suffix:semicolon
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &quot;sys.h&quot;
macro_line|#include &quot;divas.h&quot;
macro_line|#include &quot;adapter.h&quot;
macro_line|#include &quot;divalog.h&quot;
macro_line|#include &quot;uxio.h&quot;
DECL|function|Divas4BRIInitPCI
r_int
id|Divas4BRIInitPCI
c_func
(paren
id|card_t
op_star
id|card
comma
id|dia_card_t
op_star
id|cfg
)paren
(brace
multiline_comment|/* Use UxPciConfigWrite&t;routines to initialise PCI config space */
multiline_comment|/*&t;wPCIcommand = 0x03;&n;&t;cm_write_devconfig16(CMKey, PCI_COMMAND, &amp;wPCIcommand);&n;&n;&t;wPCIcommand = 0x280;&n;&t;cm_write_devconfig16(CMKey, PCI_STATUS, &amp;wPCIcommand);&n;&n;&t;bPCIcommand = 0x30;&n;&t;cm_write_devconfig16(CMKey, PCI_STATUS, &amp;wPCIcommand);&n;*/
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DivasPRIInitPCI
r_int
id|DivasPRIInitPCI
c_func
(paren
id|card_t
op_star
id|card
comma
id|dia_card_t
op_star
id|cfg
)paren
(brace
multiline_comment|/* Use UxPciConfigWrite&t;routines to initialise PCI config space */
multiline_comment|/*&t;&t;wPCIcommand = 0x03;&n;&t;cm_write_devconfig16(CMKey, PCI_COMMAND, &amp;wPCIcommand);&n;&t;&n;&t;wPCIcommand = 0x280;&n;&t;cm_write_devconfig16(CMKey, PCI_STATUS, &amp;wPCIcommand);&n;&t;&n;&t;bPCIcommand = 0x30;&n;&t;cm_write_devconfig8(CMKey, PCI_LATENCY, &amp;bPCIcommand);*/
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DivasBRIInitPCI
r_int
id|DivasBRIInitPCI
c_func
(paren
id|card_t
op_star
id|card
comma
id|dia_card_t
op_star
id|cfg
)paren
(brace
multiline_comment|/* Need to set these platform dependent values after patching */
id|card-&gt;hw-&gt;reset_base
op_assign
id|card-&gt;cfg.reset_base
suffix:semicolon
id|card-&gt;hw-&gt;io_base
op_assign
id|card-&gt;cfg.io_base
suffix:semicolon
id|request_region
c_func
(paren
id|card-&gt;hw-&gt;reset_base
comma
l_int|0x80
comma
l_string|&quot;Divas&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|card-&gt;hw-&gt;io_base
comma
l_int|0x20
comma
l_string|&quot;Divas&quot;
)paren
suffix:semicolon
multiline_comment|/* Same as for PRI */
r_return
id|DivasPRIInitPCI
c_func
(paren
id|card
comma
id|cfg
)paren
suffix:semicolon
)brace
multiline_comment|/* ######################### Stubs of routines that are not done yet ################## */
multiline_comment|/*void DivasLogIdi(card_t *card, ENTITY *e, int request)&n;{&n;}&n;*/
DECL|function|DivasDpcSchedule
r_int
id|DivasDpcSchedule
c_func
(paren
r_void
)paren
(brace
r_static
r_struct
id|work_struct
id|DivasTask
suffix:semicolon
id|INIT_WORK
c_func
(paren
op_amp
id|DivasTask
comma
id|DivasDoDpc
comma
l_int|NULL
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|DivasTask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DivasScheduleRequestDpc
r_int
id|DivasScheduleRequestDpc
c_func
(paren
r_void
)paren
(brace
r_static
r_struct
id|work_struct
id|DivasTask
suffix:semicolon
id|INIT_WORK
c_func
(paren
op_amp
id|DivasTask
comma
id|DivasDoRequestDpc
comma
l_int|NULL
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|DivasTask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DivasLogAdd
r_void
id|DivasLogAdd
c_func
(paren
r_void
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
r_static
id|boolean_t
id|overflow
op_assign
id|FALSE
suffix:semicolon
r_static
id|boolean_t
id|busy
op_assign
id|FALSE
suffix:semicolon
multiline_comment|/* make sure we&squot;re not interrupting ourselves */
r_if
c_cond
(paren
id|busy
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Divas: Logging interrupting self !&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|busy
op_assign
id|TRUE
suffix:semicolon
multiline_comment|/* ignore call if daemon isn&squot;t running and we&squot;ve reached limit */
r_if
c_cond
(paren
id|DivasLogFifoFull
c_func
(paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|overflow
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Divas: Trace buffer full&bslash;n&quot;
)paren
suffix:semicolon
id|overflow
op_assign
id|TRUE
suffix:semicolon
)brace
id|busy
op_assign
id|FALSE
suffix:semicolon
r_return
suffix:semicolon
)brace
id|DivasLogFifoWrite
c_func
(paren
id|buffer
comma
id|length
)paren
suffix:semicolon
id|busy
op_assign
id|FALSE
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* #################################################################################### */
eof
