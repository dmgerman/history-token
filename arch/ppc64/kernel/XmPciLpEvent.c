multiline_comment|/*&n;   * File XmPciLpEvent.h created by Wayne Holm on Mon Jan 15 2001.&n;   *&n;   * This module handles PCI interrupt events sent by the iSeries Hypervisor.&n;*/
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#include &lt;asm/iSeries/HvLpEvent.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
macro_line|#include &lt;asm/iSeries/XmPciLpEvent.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
DECL|variable|Pci_Interrupt_Count
r_int
id|Pci_Interrupt_Count
op_assign
l_int|0
suffix:semicolon
DECL|variable|Pci_Event_Count
r_int
id|Pci_Event_Count
op_assign
l_int|0
suffix:semicolon
DECL|enum|XmPciLpEvent_Subtype
r_enum
id|XmPciLpEvent_Subtype
(brace
DECL|enumerator|XmPciLpEvent_BusCreated
id|XmPciLpEvent_BusCreated
op_assign
l_int|0
comma
singleline_comment|// PHB has been created
DECL|enumerator|XmPciLpEvent_BusFailed
id|XmPciLpEvent_BusFailed
op_assign
l_int|1
comma
singleline_comment|// PHB has failed
DECL|enumerator|XmPciLpEvent_BusRecovered
id|XmPciLpEvent_BusRecovered
op_assign
l_int|12
comma
singleline_comment|// PHB has been recovered
DECL|enumerator|XmPciLpEvent_NodeFailed
id|XmPciLpEvent_NodeFailed
op_assign
l_int|4
comma
singleline_comment|// Multi-adapter bridge has failed
DECL|enumerator|XmPciLpEvent_NodeRecovered
id|XmPciLpEvent_NodeRecovered
op_assign
l_int|5
comma
singleline_comment|// Multi-adapter bridge has recovered
DECL|enumerator|XmPciLpEvent_SlotInterrupt
id|XmPciLpEvent_SlotInterrupt
op_assign
l_int|22
singleline_comment|// Slot interrupt
)brace
suffix:semicolon
DECL|struct|XmPciLpEvent_BusInterrupt
r_struct
id|XmPciLpEvent_BusInterrupt
(brace
DECL|member|busNumber
id|HvBusNumber
id|busNumber
suffix:semicolon
DECL|member|subBusNumber
id|HvSubBusNumber
id|subBusNumber
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|XmPciLpEvent_NodeInterrupt
r_struct
id|XmPciLpEvent_NodeInterrupt
(brace
DECL|member|busNumber
id|HvBusNumber
id|busNumber
suffix:semicolon
DECL|member|subBusNumber
id|HvSubBusNumber
id|subBusNumber
suffix:semicolon
DECL|member|deviceId
id|HvAgentId
id|deviceId
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|XmPciLpEvent
r_struct
id|XmPciLpEvent
(brace
DECL|member|hvLpEvent
r_struct
id|HvLpEvent
id|hvLpEvent
suffix:semicolon
r_union
(brace
DECL|member|alignData
id|u64
id|alignData
suffix:semicolon
singleline_comment|// Align on an 8-byte boundary
r_struct
(brace
DECL|member|fisr
id|u32
id|fisr
suffix:semicolon
DECL|member|busNumber
id|HvBusNumber
id|busNumber
suffix:semicolon
DECL|member|subBusNumber
id|HvSubBusNumber
id|subBusNumber
suffix:semicolon
DECL|member|deviceId
id|HvAgentId
id|deviceId
suffix:semicolon
DECL|member|slotInterrupt
)brace
id|slotInterrupt
suffix:semicolon
DECL|member|busFailed
r_struct
id|XmPciLpEvent_BusInterrupt
id|busFailed
suffix:semicolon
DECL|member|busRecovered
r_struct
id|XmPciLpEvent_BusInterrupt
id|busRecovered
suffix:semicolon
DECL|member|busCreated
r_struct
id|XmPciLpEvent_BusInterrupt
id|busCreated
suffix:semicolon
DECL|member|nodeFailed
r_struct
id|XmPciLpEvent_NodeInterrupt
id|nodeFailed
suffix:semicolon
DECL|member|nodeRecovered
r_struct
id|XmPciLpEvent_NodeInterrupt
id|nodeRecovered
suffix:semicolon
DECL|member|eventData
)brace
id|eventData
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
id|intReceived
c_func
(paren
r_struct
id|XmPciLpEvent
op_star
id|eventParm
comma
r_struct
id|pt_regs
op_star
id|regsParm
)paren
suffix:semicolon
DECL|function|XmPciLpEvent_handler
r_static
r_void
id|XmPciLpEvent_handler
c_func
(paren
r_struct
id|HvLpEvent
op_star
id|eventParm
comma
r_struct
id|pt_regs
op_star
id|regsParm
)paren
(brace
singleline_comment|//PPCDBG(PPCDBG_BUSWALK,&quot;XmPciLpEvent_handler, type 0x%x&bslash;n&quot;,eventParm-&gt;xType );
op_increment
id|Pci_Event_Count
suffix:semicolon
r_if
c_cond
(paren
id|eventParm
op_logical_and
id|eventParm-&gt;xType
op_eq
id|HvLpEvent_Type_PciIo
)paren
(brace
r_switch
c_cond
(paren
id|eventParm-&gt;xFlags.xFunction
)paren
(brace
r_case
id|HvLpEvent_Function_Int
suffix:colon
id|intReceived
c_func
(paren
(paren
r_struct
id|XmPciLpEvent
op_star
)paren
id|eventParm
comma
id|regsParm
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HvLpEvent_Function_Ack
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;XmPciLpEvent.c: unexpected ack received&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;XmPciLpEvent.c: unexpected event function %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|eventParm-&gt;xFlags.xFunction
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|event
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;XmPciLpEvent.c: Unrecognized PCI event type 0x%x&bslash;n&quot;
comma
(paren
r_int
)paren
id|eventParm-&gt;xType
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;XmPciLpEvent.c: NULL event received&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|intReceived
r_static
r_void
id|intReceived
c_func
(paren
r_struct
id|XmPciLpEvent
op_star
id|eventParm
comma
r_struct
id|pt_regs
op_star
id|regsParm
)paren
(brace
r_int
id|irq
suffix:semicolon
op_increment
id|Pci_Interrupt_Count
suffix:semicolon
singleline_comment|//PPCDBG(PPCDBG_BUSWALK,&quot;PCI: XmPciLpEvent.c: intReceived&bslash;n&quot;);
r_switch
c_cond
(paren
id|eventParm-&gt;hvLpEvent.xSubtype
)paren
(brace
r_case
id|XmPciLpEvent_SlotInterrupt
suffix:colon
id|irq
op_assign
id|eventParm-&gt;hvLpEvent.xCorrelationToken
suffix:semicolon
multiline_comment|/* Dispatch the interrupt handlers for this irq */
id|ppc_irq_dispatch_handler
c_func
(paren
id|regsParm
comma
id|irq
)paren
suffix:semicolon
id|HvCallPci_eoi
c_func
(paren
id|eventParm-&gt;eventData.slotInterrupt.busNumber
comma
id|eventParm-&gt;eventData.slotInterrupt.subBusNumber
comma
id|eventParm-&gt;eventData.slotInterrupt.deviceId
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Ignore error recovery events for now */
r_case
id|XmPciLpEvent_BusCreated
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;XmPciLpEvent.c: system bus %d created&bslash;n&quot;
comma
id|eventParm-&gt;eventData.busCreated.busNumber
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XmPciLpEvent_BusFailed
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;XmPciLpEvent.c: system bus %d failed&bslash;n&quot;
comma
id|eventParm-&gt;eventData.busFailed.busNumber
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XmPciLpEvent_BusRecovered
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;XmPciLpEvent.c: system bus %d recovered&bslash;n&quot;
comma
id|eventParm-&gt;eventData.busRecovered.busNumber
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XmPciLpEvent_NodeFailed
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;XmPciLpEvent.c: multi-adapter bridge %d/%d/%d failed&bslash;n&quot;
comma
id|eventParm-&gt;eventData.nodeFailed.busNumber
comma
id|eventParm-&gt;eventData.nodeFailed.subBusNumber
comma
id|eventParm-&gt;eventData.nodeFailed.deviceId
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XmPciLpEvent_NodeRecovered
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;XmPciLpEvent.c: multi-adapter bridge %d/%d/%d recovered&bslash;n&quot;
comma
id|eventParm-&gt;eventData.nodeRecovered.busNumber
comma
id|eventParm-&gt;eventData.nodeRecovered.subBusNumber
comma
id|eventParm-&gt;eventData.nodeRecovered.deviceId
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;XmPciLpEvent.c: unrecognized event subtype 0x%x&bslash;n&quot;
comma
id|eventParm-&gt;hvLpEvent.xSubtype
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
)brace
multiline_comment|/* This should be called sometime prior to buswalk (init_IRQ would be good) */
DECL|function|XmPciLpEvent_init
r_int
id|XmPciLpEvent_init
c_func
(paren
)paren
(brace
r_int
id|xRc
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_BUSWALK
comma
l_string|&quot;XmPciLpEvent_init, Register Event type 0x%04X&bslash;n&quot;
comma
id|HvLpEvent_Type_PciIo
)paren
suffix:semicolon
id|xRc
op_assign
id|HvLpEvent_registerHandler
c_func
(paren
id|HvLpEvent_Type_PciIo
comma
op_amp
id|XmPciLpEvent_handler
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xRc
op_eq
l_int|0
)paren
(brace
id|xRc
op_assign
id|HvLpEvent_openPath
c_func
(paren
id|HvLpEvent_Type_PciIo
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xRc
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;XmPciLpEvent.c: open event path failed with rc 0x%x&bslash;n&quot;
comma
id|xRc
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;XmPciLpEvent.c: register handler failed with rc 0x%x&bslash;n&quot;
comma
id|xRc
)paren
suffix:semicolon
)brace
r_return
id|xRc
suffix:semicolon
)brace
eof
