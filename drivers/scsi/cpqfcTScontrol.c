multiline_comment|/* Copyright 2000, Compaq Computer Corporation &n; * Fibre Channel Host Bus Adapter &n; * 64-bit, 66MHz PCI &n; * Originally developed and tested on:&n; * (front): [chip] Tachyon TS HPFC-5166A/1.2  L2C1090 ...&n; *          SP# P225CXCBFIEL6T, Rev XC&n; *          SP# 161290-001, Rev XD&n; * (back): Board No. 010008-001 A/W Rev X5, FAB REV X5&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; * Written by Don Zimmerman&n;*/
multiline_comment|/* These functions control the host bus adapter (HBA) hardware.  The main chip&n;   control takes place in the interrupt handler where we process the IMQ &n;   (Inbound Message Queue).  The IMQ is Tachyon&squot;s way of communicating FC link&n;   events and state information to the driver.  The Single Frame Queue (SFQ)&n;   buffers incoming FC frames for processing by the driver.  References to &n;   &quot;TL/TS UG&quot; are for:&n;   &quot;HP HPFC-5100/5166 Tachyon TL/TS ICs User Guide&quot;, August 16, 1999, 1st Ed.&n;   Hewlitt Packard Manual Part Number 5968-1083E.&n;*/
DECL|macro|LinuxVersionCode
mdefine_line|#define LinuxVersionCode(v, p, s) (((v)&lt;&lt;16)+((p)&lt;&lt;8)+(s))
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;  
singleline_comment|// request_region() prototype
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;  
singleline_comment|// need &quot;kfree&quot; for ext. S/G pages
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/io.h&gt;  
singleline_comment|// struct pt_regs for IRQ handler &amp; Port I/O
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; LinuxVersionCode(2,3,18)
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#else
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#endif
macro_line|#include &quot;sd.h&quot;
macro_line|#include &quot;hosts.h&quot;   
singleline_comment|// Scsi_Host definition for INT handler
macro_line|#include &quot;cpqfcTSchip.h&quot;
macro_line|#include &quot;cpqfcTSstructs.h&quot;
singleline_comment|//#define IMQ_DEBUG 1
r_static
r_void
id|fcParseLinkStatusCounters
c_func
(paren
id|TACHYON
op_star
id|fcChip
)paren
suffix:semicolon
r_static
r_void
id|CpqTsGetSFQEntry
c_func
(paren
id|TACHYON
op_star
id|fcChip
comma
id|USHORT
id|pi
comma
id|ULONG
op_star
id|buffr
comma
id|BOOLEAN
id|UpdateChip
)paren
suffix:semicolon
singleline_comment|// Note special requirements for Q alignment!  (TL/TS UG pg. 190)
singleline_comment|// We place critical index pointers at end of QUE elements to assist
singleline_comment|// in non-symbolic (i.e. memory dump) debugging
singleline_comment|// opcode defines placement of Queues (e.g. local/external RAM)
DECL|function|CpqTsCreateTachLiteQues
r_int
id|CpqTsCreateTachLiteQues
c_func
(paren
r_void
op_star
id|pHBA
comma
r_int
id|opcode
)paren
(brace
id|CPQFCHBA
op_star
id|cpqfcHBAdata
op_assign
(paren
id|CPQFCHBA
op_star
)paren
id|pHBA
suffix:semicolon
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
r_int
id|iStatus
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ulAddr
suffix:semicolon
singleline_comment|// NOTE! fcMemManager() will return system virtual addresses.
singleline_comment|// System (kernel) virtual addresses, though non-paged, still
singleline_comment|// aren&squot;t physical addresses.  Convert to PHYSICAL_ADDRESS for Tachyon&squot;s
singleline_comment|// DMA use.
id|ENTER
c_func
(paren
l_string|&quot;CreateTachLiteQues&quot;
)paren
suffix:semicolon
singleline_comment|// Allocate primary EXCHANGES array...
id|printk
c_func
(paren
l_string|&quot;Allocating %u for %u Exchanges &quot;
comma
(paren
id|ULONG
)paren
r_sizeof
(paren
id|FC_EXCHANGES
)paren
comma
id|TACH_MAX_XID
)paren
suffix:semicolon
id|fcChip-&gt;Exchanges
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|FC_EXCHANGES
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;@ %p&bslash;n&quot;
comma
id|fcChip-&gt;Exchanges
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fcChip-&gt;Exchanges
op_eq
l_int|NULL
)paren
singleline_comment|// fatal error!!
(brace
id|printk
c_func
(paren
l_string|&quot;kmalloc failure on Exchanges: fatal error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
singleline_comment|// zero out the entire EXCHANGE space
id|memset
c_func
(paren
id|fcChip-&gt;Exchanges
comma
l_int|0
comma
r_sizeof
(paren
id|FC_EXCHANGES
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Allocating %u for LinkQ &quot;
comma
(paren
id|ULONG
)paren
r_sizeof
(paren
id|FC_LINK_QUE
)paren
)paren
suffix:semicolon
id|cpqfcHBAdata-&gt;fcLQ
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|FC_LINK_QUE
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;@ %p (%u elements)&bslash;n&quot;
comma
id|cpqfcHBAdata-&gt;fcLQ
comma
id|FC_LINKQ_DEPTH
)paren
suffix:semicolon
id|memset
c_func
(paren
id|cpqfcHBAdata-&gt;fcLQ
comma
l_int|0
comma
r_sizeof
(paren
id|FC_LINK_QUE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpqfcHBAdata-&gt;fcLQ
op_eq
l_int|NULL
)paren
singleline_comment|// fatal error!!
(brace
id|printk
c_func
(paren
l_string|&quot;kmalloc failure on fc Link Que: fatal error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
singleline_comment|// zero out the entire EXCHANGE space
id|memset
c_func
(paren
id|cpqfcHBAdata-&gt;fcLQ
comma
l_int|0
comma
r_sizeof
(paren
id|FC_LINK_QUE
)paren
)paren
suffix:semicolon
singleline_comment|// Verify that basic Tach I/O registers are not NULL  
r_if
c_cond
(paren
op_logical_neg
id|fcChip-&gt;Registers.ReMapMemBase
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HBA base address NULL: fatal error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
singleline_comment|// Initialize the fcMemManager memory pairs (stores allocated/aligned
singleline_comment|// pairs for future freeing)
id|memset
c_func
(paren
id|cpqfcHBAdata-&gt;dynamic_mem
comma
l_int|0
comma
r_sizeof
(paren
id|cpqfcHBAdata-&gt;dynamic_mem
)paren
)paren
suffix:semicolon
singleline_comment|// Allocate Tach&squot;s Exchange Request Queue (each ERQ entry 32 bytes)
id|fcChip-&gt;ERQ
op_assign
id|fcMemManager
c_func
(paren
op_amp
id|cpqfcHBAdata-&gt;dynamic_mem
(braket
l_int|0
)braket
comma
r_sizeof
(paren
id|TachLiteERQ
)paren
comma
l_int|32
op_star
(paren
id|ERQ_LEN
)paren
comma
l_int|0L
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fcChip-&gt;ERQ
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kmalloc/alignment failure on ERQ: fatal error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|fcChip-&gt;ERQ-&gt;length
op_assign
id|ERQ_LEN
op_minus
l_int|1
suffix:semicolon
id|ulAddr
op_assign
id|virt_to_bus
c_func
(paren
id|fcChip-&gt;ERQ
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt; 32
r_if
c_cond
(paren
(paren
id|ulAddr
op_rshift
l_int|32
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; FATAL! ERQ ptr %p exceeds Tachyon&squot;s 32-bit register size&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ulAddr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
singleline_comment|// failed
)brace
macro_line|#endif
id|fcChip-&gt;ERQ-&gt;base
op_assign
(paren
id|ULONG
)paren
id|ulAddr
suffix:semicolon
singleline_comment|// copy for quick reference
singleline_comment|// Allocate Tach&squot;s Inbound Message Queue (32 bytes per entry)
id|fcChip-&gt;IMQ
op_assign
id|fcMemManager
c_func
(paren
op_amp
id|cpqfcHBAdata-&gt;dynamic_mem
(braket
l_int|0
)braket
comma
r_sizeof
(paren
id|TachyonIMQ
)paren
comma
l_int|32
op_star
(paren
id|IMQ_LEN
)paren
comma
l_int|0L
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fcChip-&gt;IMQ
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kmalloc/alignment failure on IMQ: fatal error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|fcChip-&gt;IMQ-&gt;length
op_assign
id|IMQ_LEN
op_minus
l_int|1
suffix:semicolon
id|ulAddr
op_assign
id|virt_to_bus
c_func
(paren
id|fcChip-&gt;IMQ
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt; 32
r_if
c_cond
(paren
(paren
id|ulAddr
op_rshift
l_int|32
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; FATAL! IMQ ptr %p exceeds Tachyon&squot;s 32-bit register size&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ulAddr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
singleline_comment|// failed
)brace
macro_line|#endif
id|fcChip-&gt;IMQ-&gt;base
op_assign
(paren
id|ULONG
)paren
id|ulAddr
suffix:semicolon
singleline_comment|// copy for quick reference
singleline_comment|// Allocate Tach&squot;s  Single Frame Queue (64 bytes per entry)
id|fcChip-&gt;SFQ
op_assign
id|fcMemManager
c_func
(paren
op_amp
id|cpqfcHBAdata-&gt;dynamic_mem
(braket
l_int|0
)braket
comma
r_sizeof
(paren
id|TachLiteSFQ
)paren
comma
l_int|64
op_star
(paren
id|SFQ_LEN
)paren
comma
l_int|0L
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fcChip-&gt;SFQ
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kmalloc/alignment failure on SFQ: fatal error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|fcChip-&gt;SFQ-&gt;length
op_assign
id|SFQ_LEN
op_minus
l_int|1
suffix:semicolon
singleline_comment|// i.e. Que length [# entries -
singleline_comment|// min. 32; max.  4096 (0xffff)]
id|ulAddr
op_assign
id|virt_to_bus
c_func
(paren
id|fcChip-&gt;SFQ
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt; 32
r_if
c_cond
(paren
(paren
id|ulAddr
op_rshift
l_int|32
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; FATAL! SFQ ptr %p exceeds Tachyon&squot;s 32-bit register size&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ulAddr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
singleline_comment|// failed
)brace
macro_line|#endif
id|fcChip-&gt;SFQ-&gt;base
op_assign
(paren
id|ULONG
)paren
id|ulAddr
suffix:semicolon
singleline_comment|// copy for quick reference
singleline_comment|// Allocate SCSI Exchange State Table; aligned nearest @sizeof
singleline_comment|// power-of-2 boundary
singleline_comment|// LIVE DANGEROUSLY!  Assume the boundary for SEST mem will
singleline_comment|// be on physical page (e.g. 4k) boundary.
id|printk
c_func
(paren
l_string|&quot;Allocating %u for TachSEST for %u Exchanges&bslash;n&quot;
comma
(paren
id|ULONG
)paren
r_sizeof
(paren
id|TachSEST
)paren
comma
id|TACH_SEST_LEN
)paren
suffix:semicolon
id|fcChip-&gt;SEST
op_assign
id|fcMemManager
c_func
(paren
op_amp
id|cpqfcHBAdata-&gt;dynamic_mem
(braket
l_int|0
)braket
comma
r_sizeof
(paren
id|TachSEST
)paren
comma
l_int|4
comma
l_int|0L
)paren
suffix:semicolon
singleline_comment|//&t;&t;  sizeof(TachSEST),  64*TACH_SEST_LEN, 0L );
r_if
c_cond
(paren
op_logical_neg
id|fcChip-&gt;SEST
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kmalloc/alignment failure on SEST: fatal error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|fcChip-&gt;SEST-&gt;length
op_assign
id|TACH_SEST_LEN
suffix:semicolon
singleline_comment|// e.g. DON&squot;T subtract one 
singleline_comment|// (TL/TS UG, pg 153)
id|ulAddr
op_assign
id|virt_to_bus
c_func
(paren
id|fcChip-&gt;SEST
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt; 32
r_if
c_cond
(paren
(paren
id|ulAddr
op_rshift
l_int|32
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; FATAL! SFQ ptr %p exceeds Tachyon&squot;s 32-bit register size&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ulAddr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
singleline_comment|// failed
)brace
macro_line|#endif
id|fcChip-&gt;SEST-&gt;base
op_assign
(paren
id|ULONG
)paren
id|ulAddr
suffix:semicolon
singleline_comment|// copy for quick reference
singleline_comment|// Now that structures are defined,
singleline_comment|// fill in Tachyon chip registers...
singleline_comment|// EEEEEEEE  EXCHANGE REQUEST QUEUE
id|writel
c_func
(paren
id|fcChip-&gt;ERQ-&gt;base
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_ERQ_BASE
)paren
)paren
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;ERQ-&gt;length
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_ERQ_LENGTH
)paren
)paren
suffix:semicolon
id|fcChip-&gt;ERQ-&gt;producerIndex
op_assign
l_int|0L
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;ERQ-&gt;producerIndex
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_ERQ_PRODUCER_INDEX
)paren
)paren
suffix:semicolon
singleline_comment|// NOTE! write consumer index last, since the write
singleline_comment|// causes Tachyon to process the other registers
id|ulAddr
op_assign
id|virt_to_bus
c_func
(paren
op_amp
id|fcChip-&gt;ERQ-&gt;consumerIndex
)paren
suffix:semicolon
singleline_comment|// NOTE! Tachyon DMAs to the ERQ consumer Index host
singleline_comment|// address; must be correctly aligned
id|writel
c_func
(paren
(paren
id|ULONG
)paren
id|ulAddr
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_ERQ_CONSUMER_INDEX_ADR
)paren
)paren
suffix:semicolon
singleline_comment|// IIIIIIIIIIIII  INBOUND MESSAGE QUEUE
singleline_comment|// Tell Tachyon where the Que starts
singleline_comment|// set the Host&squot;s pointer for Tachyon to access
id|printk
c_func
(paren
l_string|&quot;  cpqfcTS: writing IMQ BASE %Xh  &quot;
comma
id|fcChip-&gt;IMQ-&gt;base
)paren
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;IMQ-&gt;base
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|IMQ_BASE
)paren
)paren
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;IMQ-&gt;length
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|IMQ_LENGTH
)paren
)paren
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;IMQ-&gt;consumerIndex
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|IMQ_CONSUMER_INDEX
)paren
)paren
suffix:semicolon
singleline_comment|// NOTE: TachLite DMAs to the producerIndex host address
singleline_comment|// must be correctly aligned with address bits 1-0 cleared
singleline_comment|// Writing the BASE register clears the PI register, so write it last
id|ulAddr
op_assign
id|virt_to_bus
c_func
(paren
op_amp
id|fcChip-&gt;IMQ-&gt;producerIndex
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt; 32
r_if
c_cond
(paren
(paren
id|ulAddr
op_rshift
l_int|32
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; FATAL! IMQ ptr %p exceeds Tachyon&squot;s 32-bit register size&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ulAddr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
singleline_comment|// failed
)brace
macro_line|#endif
singleline_comment|//#if DBG
id|printk
c_func
(paren
l_string|&quot;  PI %Xh&bslash;n&quot;
comma
(paren
id|ULONG
)paren
id|ulAddr
)paren
suffix:semicolon
singleline_comment|//#endif
id|writel
c_func
(paren
(paren
id|ULONG
)paren
id|ulAddr
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|IMQ_PRODUCER_INDEX
)paren
)paren
suffix:semicolon
singleline_comment|// SSSSSSSSSSSSSSS SINGLE FRAME SEQUENCE
singleline_comment|// Tell TachLite where the Que starts
id|writel
c_func
(paren
id|fcChip-&gt;SFQ-&gt;base
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_SFQ_BASE
)paren
)paren
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;SFQ-&gt;length
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_SFQ_LENGTH
)paren
)paren
suffix:semicolon
singleline_comment|// tell TachLite where SEST table is &amp; how long
id|writel
c_func
(paren
id|fcChip-&gt;SEST-&gt;base
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_SEST_BASE
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  cpqfcTS: SEST %p(virt): Wrote base %Xh @ %p&bslash;n&quot;
comma
id|fcChip-&gt;SEST
comma
id|fcChip-&gt;SEST-&gt;base
comma
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_SEST_BASE
)paren
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;SEST-&gt;length
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_SEST_LENGTH
)paren
)paren
suffix:semicolon
id|writel
c_func
(paren
(paren
id|TL_EXT_SG_PAGE_COUNT
op_minus
l_int|1
)paren
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_SEST_SG_PAGE
)paren
)paren
suffix:semicolon
id|LEAVE
c_func
(paren
l_string|&quot;CreateTachLiteQues&quot;
)paren
suffix:semicolon
r_return
id|iStatus
suffix:semicolon
)brace
singleline_comment|// function to return TachLite to Power On state
singleline_comment|// 1st - reset tachyon (&squot;SOFT&squot; reset)
singleline_comment|// others - future
DECL|function|CpqTsResetTachLite
r_int
id|CpqTsResetTachLite
c_func
(paren
r_void
op_star
id|pHBA
comma
r_int
id|type
)paren
(brace
id|CPQFCHBA
op_star
id|cpqfcHBAdata
op_assign
(paren
id|CPQFCHBA
op_star
)paren
id|pHBA
suffix:semicolon
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|ULONG
id|ulBuff
comma
id|i
suffix:semicolon
r_int
id|ret_status
op_assign
l_int|0
suffix:semicolon
singleline_comment|// def. success
id|ENTER
c_func
(paren
l_string|&quot;ResetTach&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|CLEAR_FCPORTS
suffix:colon
singleline_comment|// in case he was running previously, mask Tach&squot;s interrupt
id|writeb
c_func
(paren
l_int|0
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|IINTEN
)paren
)paren
suffix:semicolon
singleline_comment|// de-allocate mem for any Logged in ports
singleline_comment|// (e.g., our module is unloading)
singleline_comment|// search the forward linked list, de-allocating
singleline_comment|// the memory we allocated when the port was initially logged in
(brace
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
op_assign
id|fcChip-&gt;fcPorts.pNextPort
suffix:semicolon
id|PFC_LOGGEDIN_PORT
id|ptr
suffix:semicolon
singleline_comment|//        printk(&quot;checking for allocated LoggedInPorts...&bslash;n&quot;);
r_while
c_loop
(paren
id|pLoggedInPort
)paren
(brace
id|ptr
op_assign
id|pLoggedInPort
suffix:semicolon
id|pLoggedInPort
op_assign
id|ptr-&gt;pNextPort
suffix:semicolon
singleline_comment|//&t;  printk(&quot;kfree(%p) on FC LoggedInPort port_id 0x%06lX&bslash;n&quot;,
singleline_comment|//&t;&t;&t;  ptr, ptr-&gt;port_id);
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
)brace
singleline_comment|// (continue resetting hardware...)
r_case
l_int|1
suffix:colon
singleline_comment|// RESTART Tachyon (power-up state)
singleline_comment|// in case he was running previously, mask Tach&squot;s interrupt
id|writeb
c_func
(paren
l_int|0
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|IINTEN
)paren
)paren
suffix:semicolon
singleline_comment|// turn OFF laser (NOTE: laser is turned
singleline_comment|// off during reset, because GPIO4 is cleared
singleline_comment|// to 0 by reset action - see TLUM, sec 7.22)
singleline_comment|// However, CPQ 64-bit HBAs have a &quot;health
singleline_comment|// circuit&quot; which keeps laser ON for a brief
singleline_comment|// period after it is turned off ( &lt; 1s)
id|fcChip
op_member_access_from_pointer
id|LaserControl
c_func
(paren
id|fcChip-&gt;Registers.ReMapMemBase
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// soft reset timing constraints require:
singleline_comment|//   1. set RST to 1
singleline_comment|//   2. read SOFTRST register 
singleline_comment|//      (128 times per R. Callison code)
singleline_comment|//   3. clear PCI ints
singleline_comment|//   4. clear RST to 0
id|writel
c_func
(paren
l_int|0xff000001L
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_SOFTRST
)paren
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
l_int|128
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ulBuff
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_SOFTRST
)paren
suffix:semicolon
)brace
singleline_comment|// clear the soft reset
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
(brace
id|writel
c_func
(paren
l_int|0
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_SOFTRST
)paren
)paren
suffix:semicolon
)brace
singleline_comment|// clear out our copy of Tach regs,
singleline_comment|// because they must be invalid now,
singleline_comment|// since TachLite reset all his regs.
id|CpqTsDestroyTachLiteQues
c_func
(paren
id|cpqfcHBAdata
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// remove Host-based Que structs
id|cpqfcTSClearLinkStatusCounters
c_func
(paren
id|fcChip
)paren
suffix:semicolon
singleline_comment|// clear our s/w accumulators
singleline_comment|// lower bits give GBIC info
id|fcChip-&gt;Registers.TYstatus.value
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.TYstatus.address
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;    case 2:                   // freeze SCSI&n;    case 3:                   // reset Outbound command que (ERQ)&n;    case 4:                   // unfreeze OSM (Outbound Seq. Man.) &squot;er&squot;&n;    case 5:                   // report status&n;&n;    break;&n;*/
r_default
suffix:colon
id|ret_status
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// invalid option passed to RESET function
r_break
suffix:semicolon
)brace
id|LEAVE
c_func
(paren
l_string|&quot;ResetTach&quot;
)paren
suffix:semicolon
r_return
id|ret_status
suffix:semicolon
)brace
singleline_comment|// &squot;addrBase&squot; is IOBaseU for both TachLite and (older) Tachyon
DECL|function|CpqTsLaserControl
r_int
id|CpqTsLaserControl
c_func
(paren
r_void
op_star
id|addrBase
comma
r_int
id|opcode
)paren
(brace
id|ULONG
id|dwBuff
suffix:semicolon
id|dwBuff
op_assign
id|readl
c_func
(paren
(paren
id|addrBase
op_plus
id|TL_MEM_TACH_CONTROL
)paren
)paren
suffix:semicolon
singleline_comment|// read TL Control reg
singleline_comment|// (change only bit 4)
r_if
c_cond
(paren
id|opcode
op_eq
l_int|1
)paren
(brace
id|dwBuff
op_or_assign
op_complement
l_int|0xffffffefL
suffix:semicolon
)brace
singleline_comment|// set - ON
r_else
id|dwBuff
op_and_assign
l_int|0xffffffefL
suffix:semicolon
singleline_comment|// clear - OFF
id|writel
c_func
(paren
id|dwBuff
comma
(paren
id|addrBase
op_plus
id|TL_MEM_TACH_CONTROL
)paren
)paren
suffix:semicolon
singleline_comment|// write TL Control reg
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|// Use controller&squot;s &quot;Options&quot; field to determine loopback mode (if any)
singleline_comment|//   internal loopback (silicon - no GBIC)
singleline_comment|//   external loopback (GBIC - no FC loop)
singleline_comment|//   no loopback: L_PORT, external cable from GBIC required
DECL|function|CpqTsInitializeFrameManager
r_int
id|CpqTsInitializeFrameManager
c_func
(paren
r_void
op_star
id|pChip
comma
r_int
id|opcode
)paren
(brace
id|PTACHYON
id|fcChip
suffix:semicolon
r_int
id|iStatus
suffix:semicolon
id|ULONG
id|wwnLo
comma
id|wwnHi
suffix:semicolon
singleline_comment|// for readback verification
id|ENTER
c_func
(paren
l_string|&quot;InitializeFrameManager&quot;
)paren
suffix:semicolon
id|fcChip
op_assign
(paren
id|PTACHYON
)paren
id|pChip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fcChip-&gt;Registers.ReMapMemBase
)paren
(brace
singleline_comment|// undefined controller?
r_return
op_minus
l_int|1
suffix:semicolon
)brace
singleline_comment|// TL/TS UG, pg. 184
singleline_comment|// 0x0065 = 100ms for RT_TOV
singleline_comment|// 0x01f5 = 500ms for ED_TOV
singleline_comment|// 0x07D1 = 2000ms 
id|fcChip-&gt;Registers.ed_tov.value
op_assign
l_int|0x006507D1
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;Registers.ed_tov.value
comma
(paren
id|fcChip-&gt;Registers.ed_tov.address
)paren
)paren
suffix:semicolon
singleline_comment|// Set LP_TOV to the FC-AL2 specified 2 secs.
singleline_comment|// TL/TS UG, pg. 185
id|writel
c_func
(paren
l_int|0x07d00010
comma
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_FM_TIMEOUT2
)paren
suffix:semicolon
singleline_comment|// Now try to read the WWN from the adapter&squot;s NVRAM
id|iStatus
op_assign
id|CpqTsReadWriteWWN
c_func
(paren
id|fcChip
comma
l_int|1
)paren
suffix:semicolon
singleline_comment|// &squot;1&squot; for READ
r_if
c_cond
(paren
id|iStatus
)paren
singleline_comment|// NVRAM read failed?
(brace
id|printk
c_func
(paren
l_string|&quot; WARNING! HBA NVRAM WWN read failed - make alias&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// make up a WWN.  If NULL or duplicated on loop, FC loop may hang!
id|fcChip-&gt;Registers.wwn_hi
op_assign
(paren
id|__u32
)paren
id|jiffies
suffix:semicolon
id|fcChip-&gt;Registers.wwn_hi
op_or_assign
l_int|0x50000000L
suffix:semicolon
id|fcChip-&gt;Registers.wwn_lo
op_assign
l_int|0x44556677L
suffix:semicolon
)brace
id|writel
c_func
(paren
id|fcChip-&gt;Registers.wwn_hi
comma
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_FM_WWN_HI
)paren
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;Registers.wwn_lo
comma
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_FM_WWN_LO
)paren
suffix:semicolon
singleline_comment|// readback for verification:
id|wwnHi
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_FM_WWN_HI
)paren
suffix:semicolon
id|wwnLo
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_FM_WWN_LO
)paren
suffix:semicolon
singleline_comment|// test for correct chip register WRITE/READ
id|DEBUG_PCI
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;  WWN %08X%08X&bslash;n&quot;
comma
id|fcChip-&gt;Registers.wwn_hi
comma
id|fcChip-&gt;Registers.wwn_lo
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wwnHi
op_ne
id|fcChip-&gt;Registers.wwn_hi
op_logical_or
id|wwnLo
op_ne
id|fcChip-&gt;Registers.wwn_lo
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpqfcTS: WorldWideName register load failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
singleline_comment|// FAILED!
)brace
singleline_comment|// set Frame Manager Initialize command
id|fcChip-&gt;Registers.FMcontrol.value
op_assign
l_int|0x06
suffix:semicolon
singleline_comment|// Note: for test/debug purposes, we may use &quot;Hard&quot; address,
singleline_comment|// but we completely support &quot;soft&quot; addressing, including
singleline_comment|// dynamically changing our address.
r_if
c_cond
(paren
id|fcChip-&gt;Options.intLoopback
op_eq
l_int|1
)paren
(brace
singleline_comment|// internal loopback
id|fcChip-&gt;Registers.FMconfig.value
op_assign
l_int|0x0f002080L
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fcChip-&gt;Options.extLoopback
op_eq
l_int|1
)paren
(brace
singleline_comment|// internal loopback
id|fcChip-&gt;Registers.FMconfig.value
op_assign
l_int|0x0f004080L
suffix:semicolon
)brace
r_else
singleline_comment|// L_Port
id|fcChip-&gt;Registers.FMconfig.value
op_assign
l_int|0x55000100L
suffix:semicolon
singleline_comment|// hard address (55h start)
singleline_comment|//    fcChip-&gt;Registers.FMconfig.value = 0x01000080L; // soft address (can&squot;t pick)
singleline_comment|//    fcChip-&gt;Registers.FMconfig.value = 0x55000100L; // hard address (55h start)
singleline_comment|// write config to FM
r_if
c_cond
(paren
op_logical_neg
id|fcChip-&gt;Options.intLoopback
op_logical_and
op_logical_neg
id|fcChip-&gt;Options.extLoopback
)paren
(brace
singleline_comment|// (also need LASER for real LOOP)
id|fcChip
op_member_access_from_pointer
id|LaserControl
c_func
(paren
id|fcChip-&gt;Registers.ReMapMemBase
comma
l_int|1
)paren
suffix:semicolon
)brace
singleline_comment|// turn on LASER
id|writel
c_func
(paren
id|fcChip-&gt;Registers.FMconfig.value
comma
id|fcChip-&gt;Registers.FMconfig.address
)paren
suffix:semicolon
singleline_comment|// issue INITIALIZE command to FM - ACTION!
id|writel
c_func
(paren
id|fcChip-&gt;Registers.FMcontrol.value
comma
id|fcChip-&gt;Registers.FMcontrol.address
)paren
suffix:semicolon
id|LEAVE
c_func
(paren
l_string|&quot;InitializeFrameManager&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|// This &quot;look ahead&quot; function examines the IMQ for occurence of
singleline_comment|// &quot;type&quot;.  Returns 1 if found, 0 if not.
DECL|function|PeekIMQEntry
r_static
r_int
id|PeekIMQEntry
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|ULONG
id|type
)paren
(brace
id|ULONG
id|CI
op_assign
id|fcChip-&gt;IMQ-&gt;consumerIndex
suffix:semicolon
id|ULONG
id|PI
op_assign
id|fcChip-&gt;IMQ-&gt;producerIndex
suffix:semicolon
singleline_comment|// snapshot of IMQ indexes
r_while
c_loop
(paren
id|CI
op_ne
id|PI
)paren
(brace
singleline_comment|// proceed with search
r_if
c_cond
(paren
(paren
op_increment
id|CI
)paren
op_ge
id|IMQ_LEN
)paren
(brace
id|CI
op_assign
l_int|0
suffix:semicolon
)brace
singleline_comment|// rollover check
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ELS_LILP_FRAME
suffix:colon
(brace
singleline_comment|// first, we need to find an Inbound Completion message,
singleline_comment|// If we find it, check the incoming frame payload (1st word)
singleline_comment|// for LILP frame
r_if
c_cond
(paren
(paren
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|CI
)braket
dot
id|type
op_amp
l_int|0x1FF
)paren
op_eq
l_int|0x104
)paren
(brace
id|TachFCHDR_GCMND
op_star
id|fchs
suffix:semicolon
id|ULONG
id|ulFibreFrame
(braket
l_int|2048
op_div
l_int|4
)braket
suffix:semicolon
singleline_comment|// max DWORDS in incoming FC Frame
id|USHORT
id|SFQpi
op_assign
(paren
id|USHORT
)paren
(paren
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|CI
)braket
dot
id|word
(braket
l_int|0
)braket
op_amp
l_int|0x0fffL
)paren
suffix:semicolon
id|CpqTsGetSFQEntry
c_func
(paren
id|fcChip
comma
id|SFQpi
comma
singleline_comment|// SFQ producer ndx         
id|ulFibreFrame
comma
singleline_comment|// contiguous dest. buffer
id|FALSE
)paren
suffix:semicolon
singleline_comment|// DON&squot;T update chip--this is a &quot;lookahead&quot;
id|fchs
op_assign
(paren
id|TachFCHDR_GCMND
op_star
)paren
op_amp
id|ulFibreFrame
suffix:semicolon
r_if
c_cond
(paren
id|fchs-&gt;pl
(braket
l_int|0
)braket
op_eq
id|ELS_LILP_FRAME
)paren
(brace
r_return
l_int|1
suffix:semicolon
singleline_comment|// found the LILP frame!
)brace
r_else
(brace
singleline_comment|// keep looking...
)brace
)brace
)brace
r_break
suffix:semicolon
r_case
id|OUTBOUND_COMPLETION
suffix:colon
r_if
c_cond
(paren
(paren
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|CI
)braket
dot
id|type
op_amp
l_int|0x1FF
)paren
op_eq
l_int|0x00
)paren
(brace
singleline_comment|// any OCM errors?
r_if
c_cond
(paren
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|CI
)braket
dot
id|word
(braket
l_int|2
)braket
op_amp
l_int|0x7a000000L
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
singleline_comment|// found OCM error
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
singleline_comment|// failed to find &quot;type&quot;
)brace
DECL|function|SetTachTOV
r_static
r_void
id|SetTachTOV
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
singleline_comment|// TL/TS UG, pg. 184
singleline_comment|// 0x0065 = 100ms for RT_TOV
singleline_comment|// 0x01f5 = 500ms for ED_TOV
singleline_comment|// 0x07d1 = 2000ms for ED_TOV
singleline_comment|// SANMark Level 1 requires an &quot;initialization backoff&quot;
singleline_comment|// (See &quot;SANMark Test Suite Level 1&quot;:
singleline_comment|// initialization_timeout.fcal.SANMark-1.fc)
singleline_comment|// We have to use 2sec, 24sec, then 128sec when login/
singleline_comment|// port discovery processes fail to complete.
singleline_comment|// when port discovery completes (logins done), we set
singleline_comment|// ED_TOV to 500ms -- this is the normal operational case
singleline_comment|// On the first Link Down, we&squot;ll move to 2 secs (7D1 ms)
r_if
c_cond
(paren
(paren
id|fcChip-&gt;Registers.ed_tov.value
op_amp
l_int|0xFFFF
)paren
op_le
l_int|0x1f5
)paren
(brace
id|fcChip-&gt;Registers.ed_tov.value
op_assign
l_int|0x006507D1
suffix:semicolon
)brace
singleline_comment|// If we get another LST after we moved TOV to 2 sec,
singleline_comment|// increase to 24 seconds (5DC1 ms) per SANMark!
r_else
r_if
c_cond
(paren
(paren
id|fcChip-&gt;Registers.ed_tov.value
op_amp
l_int|0xFFFF
)paren
op_le
l_int|0x7D1
)paren
(brace
id|fcChip-&gt;Registers.ed_tov.value
op_assign
l_int|0x00655DC1
suffix:semicolon
)brace
singleline_comment|// If we get still another LST, set the max TOV (Tachyon
singleline_comment|// has only 16 bits for ms timer, so the max is 65.5 sec)
r_else
r_if
c_cond
(paren
(paren
id|fcChip-&gt;Registers.ed_tov.value
op_amp
l_int|0xFFFF
)paren
op_le
l_int|0x5DC1
)paren
(brace
id|fcChip-&gt;Registers.ed_tov.value
op_assign
l_int|0x0065FFFF
suffix:semicolon
)brace
id|writel
c_func
(paren
id|fcChip-&gt;Registers.ed_tov.value
comma
(paren
id|fcChip-&gt;Registers.ed_tov.address
)paren
)paren
suffix:semicolon
singleline_comment|// keep the same 2sec LP_TOV 
id|writel
c_func
(paren
l_int|0x07D00010
comma
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_FM_TIMEOUT2
)paren
suffix:semicolon
)brace
singleline_comment|// The IMQ is an array with IMQ_LEN length, each element (QEntry)
singleline_comment|// with eight 32-bit words.  Tachyon PRODUCES a QEntry with each
singleline_comment|// message it wants to send to the host.  The host CONSUMES IMQ entries
singleline_comment|// This function copies the current
singleline_comment|// (or oldest not-yet-processed) QEntry to
singleline_comment|// the caller, clears/ re-enables the interrupt, and updates the
singleline_comment|// (Host) Consumer Index.
singleline_comment|// Return value:
singleline_comment|//  0   message processed, none remain (producer and consumer
singleline_comment|//        indexes match)
singleline_comment|//  1   message processed, more messages remain
singleline_comment|// -1   no message processed - none were available to process
singleline_comment|// Remarks:
singleline_comment|//   TL/TS UG specifices that the following actions for
singleline_comment|//   INTA_L handling:
singleline_comment|//   1. read PCI Interrupt Status register (0xff)
singleline_comment|//   2. all IMQ messages should be processed before writing the
singleline_comment|//      IMQ consumer index.
DECL|function|CpqTsProcessIMQEntry
r_int
id|CpqTsProcessIMQEntry
c_func
(paren
r_void
op_star
id|host
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|HostAdapter
op_assign
(paren
r_struct
id|Scsi_Host
op_star
)paren
id|host
suffix:semicolon
id|CPQFCHBA
op_star
id|cpqfcHBAdata
op_assign
(paren
id|CPQFCHBA
op_star
)paren
id|HostAdapter-&gt;hostdata
suffix:semicolon
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
r_int
id|iStatus
suffix:semicolon
id|USHORT
id|i
comma
id|RPCset
comma
id|DPCset
suffix:semicolon
id|ULONG
id|x_ID
suffix:semicolon
id|ULONG
id|ulBuff
comma
id|dwStatus
suffix:semicolon
id|TachFCHDR_GCMND
op_star
id|fchs
suffix:semicolon
id|ULONG
id|ulFibreFrame
(braket
l_int|2048
op_div
l_int|4
)braket
suffix:semicolon
singleline_comment|// max number of DWORDS in incoming Fibre Frame
id|UCHAR
id|ucInboundMessageType
suffix:semicolon
singleline_comment|// Inbound CM, dword 3 &quot;type&quot; field
id|ENTER
c_func
(paren
l_string|&quot;ProcessIMQEntry&quot;
)paren
suffix:semicolon
singleline_comment|// check TachLite&squot;s IMQ producer index -
singleline_comment|// is a new message waiting for us?
singleline_comment|// equal indexes means empty que
r_if
c_cond
(paren
id|fcChip-&gt;IMQ-&gt;producerIndex
op_ne
id|fcChip-&gt;IMQ-&gt;consumerIndex
)paren
(brace
singleline_comment|// need to process message
macro_line|#ifdef IMQ_DEBUG
id|printk
c_func
(paren
l_string|&quot;PI %X, CI %X  type: %X&bslash;n&quot;
comma
id|fcChip-&gt;IMQ-&gt;producerIndex
comma
id|fcChip-&gt;IMQ-&gt;consumerIndex
comma
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|type
)paren
suffix:semicolon
macro_line|#endif                                
singleline_comment|// Examine Completion Messages in IMQ
singleline_comment|// what CM_Type?
r_switch
c_cond
(paren
(paren
id|UCHAR
)paren
(paren
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|type
op_amp
l_int|0xffL
)paren
)paren
(brace
r_case
id|OUTBOUND_COMPLETION
suffix:colon
singleline_comment|// Remarks:
singleline_comment|// x_IDs (OX_ID, RX_ID) are partitioned by SEST entries
singleline_comment|// (starting at 0), and SFS entries (starting at
singleline_comment|// SEST_LEN -- outside the SEST space).
singleline_comment|// Psuedo code:
singleline_comment|// x_ID (OX_ID or RX_ID) from message is Trans_ID or SEST index
singleline_comment|// range check - x_ID
singleline_comment|//   if x_ID outside &squot;Transactions&squot; length, error - exit
singleline_comment|// if any OCM error, copy error status to Exchange slot
singleline_comment|// if FCP ASSIST transaction (x_ID within SEST),
singleline_comment|//   call fcComplete (to App)
singleline_comment|// ...
id|ulBuff
op_assign
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|1
)braket
suffix:semicolon
id|x_ID
op_assign
id|ulBuff
op_amp
l_int|0x7fffL
suffix:semicolon
singleline_comment|// lower 14 bits SEST_Index/Trans_ID
singleline_comment|// Range check CM OX/RX_ID value...
r_if
c_cond
(paren
id|x_ID
OL
id|TACH_MAX_XID
)paren
singleline_comment|// don&squot;t go beyond array space
(brace
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x20000000L
)paren
(brace
singleline_comment|// RPC -Response Phase Complete?
id|RPCset
op_assign
l_int|1
suffix:semicolon
)brace
singleline_comment|// (SEST transactions only)
r_else
id|RPCset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x40000000L
)paren
(brace
singleline_comment|// DPC -Data Phase Complete?
id|DPCset
op_assign
l_int|1
suffix:semicolon
)brace
singleline_comment|// (SEST transactions only)
r_else
id|DPCset
op_assign
l_int|0
suffix:semicolon
singleline_comment|// set the status for this Outbound transaction&squot;s ID
id|dwStatus
op_assign
l_int|0L
suffix:semicolon
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x10000000L
)paren
(brace
singleline_comment|// SPE? (SEST Programming Error)
id|dwStatus
op_or_assign
id|SESTPROG_ERR
suffix:semicolon
)brace
id|ulBuff
op_assign
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x7a000000L
)paren
singleline_comment|// any other errs?
(brace
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x40000000L
)paren
(brace
id|dwStatus
op_or_assign
id|INV_ENTRY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x20000000L
)paren
(brace
id|dwStatus
op_or_assign
id|FRAME_TO
suffix:semicolon
)brace
singleline_comment|// FTO
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x10000000L
)paren
(brace
id|dwStatus
op_or_assign
id|HOSTPROG_ERR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x08000000L
)paren
(brace
id|dwStatus
op_or_assign
id|LINKFAIL_TX
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x02000000L
)paren
(brace
id|dwStatus
op_or_assign
id|ABORTSEQ_NOTIFY
suffix:semicolon
)brace
singleline_comment|// ASN
)brace
r_if
c_cond
(paren
id|dwStatus
)paren
singleline_comment|// any errors?
(brace
singleline_comment|// set the Outbound Completion status
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_or_assign
id|dwStatus
suffix:semicolon
singleline_comment|// if this Outbound frame was for a SEST entry, automatically
singleline_comment|// reque it in the case of LINKFAIL (it will restart on PDISC)
r_if
c_cond
(paren
id|x_ID
OL
id|TACH_SEST_LEN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; #OCM error %Xh x_ID %X# &quot;
comma
id|dwStatus
comma
id|x_ID
)paren
suffix:semicolon
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|timeOut
op_assign
l_int|30000
suffix:semicolon
singleline_comment|// seconds default
singleline_comment|// We Q ABTS for each exchange.
singleline_comment|// NOTE: We can get FRAME_TO on bad alpa (device gone).  Since
singleline_comment|// bad alpa is reported before FRAME_TO, examine the status
singleline_comment|// flags to see if the device is removed.  If so, DON&squot;T
singleline_comment|// post an ABTS, since it will be terminated by the bad alpa
singleline_comment|// message.
r_if
c_cond
(paren
id|dwStatus
op_amp
id|FRAME_TO
)paren
singleline_comment|// check for device removed...
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|DEVICE_REMOVED
)paren
)paren
(brace
singleline_comment|// presumes device is still there: send ABTS.
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|BLS_ABTS
comma
op_amp
id|x_ID
)paren
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// Abort all other errors
(brace
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|BLS_ABTS
comma
op_amp
id|x_ID
)paren
suffix:semicolon
)brace
singleline_comment|// if the HPE bit is set, we have to CLose the LOOP
singleline_comment|// (see TL/TS UG, pg. 239)
r_if
c_cond
(paren
id|dwStatus
op_and_assign
id|HOSTPROG_ERR
)paren
(brace
singleline_comment|// set CL bit (see TL/TS UG, pg. 172)
id|writel
c_func
(paren
l_int|4
comma
id|fcChip-&gt;Registers.FMcontrol.address
)paren
suffix:semicolon
)brace
)brace
)brace
singleline_comment|// NOTE: we don&squot;t necessarily care about ALL completion messages...
singleline_comment|// SCSI resp. complete OR
r_if
c_cond
(paren
(paren
(paren
id|x_ID
OL
id|TACH_SEST_LEN
)paren
op_logical_and
id|RPCset
)paren
op_logical_or
(paren
id|x_ID
op_ge
id|TACH_SEST_LEN
)paren
)paren
singleline_comment|// non-SCSI command
(brace
singleline_comment|// exchange done; complete to upper levels with status
singleline_comment|// (if necessary) and free the exchange slot
r_if
c_cond
(paren
id|x_ID
op_ge
id|TACH_SEST_LEN
)paren
singleline_comment|// Link Service Outbound frame?
singleline_comment|// A Request or Reply has been sent
(brace
singleline_comment|// signal waiting WorkerThread
id|up
c_func
(paren
id|cpqfcHBAdata-&gt;TYOBcomplete
)paren
suffix:semicolon
singleline_comment|// frame is OUT of Tach
singleline_comment|// WorkerThread will complete Xchng
)brace
r_else
singleline_comment|// X_ID is for FCP assist (SEST)
(brace
singleline_comment|// TBD (target mode)
singleline_comment|//            fcCompleteExchange( fcChip, x_ID); // TRE completed
)brace
)brace
)brace
r_else
singleline_comment|// ERROR CONDITION!  bogus x_ID in completion message
(brace
id|printk
c_func
(paren
l_string|&quot; ProcessIMQ (OBCM) x_id out of range %Xh&bslash;n&quot;
comma
id|x_ID
)paren
suffix:semicolon
)brace
singleline_comment|// Load the Frame Manager&squot;s error counters.  We check them here
singleline_comment|// because presumably the link is up and healthy enough for the
singleline_comment|// counters to be meaningful (i.e., don&squot;t check them while loop
singleline_comment|// is initializing).
id|fcChip-&gt;Registers.FMLinkStatus1.value
op_assign
singleline_comment|// get TL&squot;s counter
id|readl
c_func
(paren
id|fcChip-&gt;Registers.FMLinkStatus1.address
)paren
suffix:semicolon
id|fcChip-&gt;Registers.FMLinkStatus2.value
op_assign
singleline_comment|// get TL&squot;s counter
id|readl
c_func
(paren
id|fcChip-&gt;Registers.FMLinkStatus2.address
)paren
suffix:semicolon
id|fcParseLinkStatusCounters
c_func
(paren
id|fcChip
)paren
suffix:semicolon
singleline_comment|// load into 6 s/w accumulators
r_break
suffix:semicolon
r_case
id|ERROR_IDLE_COMPLETION
suffix:colon
singleline_comment|// TachLite Error Idle...
singleline_comment|// We usually get this when the link goes down during heavy traffic.
singleline_comment|// For now, presume that if SEST Exchanges are open, we will
singleline_comment|// get this as our cue to INVALIDATE all SEST entries
singleline_comment|// (and we OWN all the SEST entries).
singleline_comment|// See TL/TS UG, pg. 53
r_for
c_loop
(paren
id|x_ID
op_assign
l_int|0
suffix:semicolon
id|x_ID
OL
id|TACH_SEST_LEN
suffix:semicolon
id|x_ID
op_increment
)paren
(brace
singleline_comment|// Does this VALid SEST entry need to be invalidated for Abort?
id|fcChip-&gt;SEST-&gt;u
(braket
id|x_ID
)braket
dot
id|IWE.Hdr_Len
op_and_assign
l_int|0x7FFFFFFF
suffix:semicolon
)brace
id|CpqTsUnFreezeTachlite
c_func
(paren
id|fcChip
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// unfreeze Tachyon, if Link OK
r_break
suffix:semicolon
r_case
id|INBOUND_SFS_COMPLETION
suffix:colon
singleline_comment|//0x04
singleline_comment|// NOTE! we must process this SFQ message to avoid SFQ filling
singleline_comment|// up and stopping TachLite.  Incoming commands are placed here,
singleline_comment|// as well as &squot;unknown&squot; frames (e.g. LIP loop position data)
singleline_comment|// write this CM&squot;s producer index to global...
singleline_comment|// TL/TS UG, pg 234:
singleline_comment|// Type: 0 - reserved
singleline_comment|//       1 - Unassisted FCP
singleline_comment|//       2 - BAD FCP
singleline_comment|//       3 - Unkown Frame
singleline_comment|//       4-F reserved
id|fcChip-&gt;SFQ-&gt;producerIndex
op_assign
(paren
id|USHORT
)paren
(paren
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|0
)braket
op_amp
l_int|0x0fffL
)paren
suffix:semicolon
id|ucInboundMessageType
op_assign
l_int|0
suffix:semicolon
singleline_comment|// default to useless frame
singleline_comment|// we can only process two Types: 1, Unassisted FCP, and 3, Unknown
singleline_comment|// Also, we aren&squot;t interested in processing frame fragments
singleline_comment|// so don&squot;t Que anything with &squot;LKF&squot; bit set
r_if
c_cond
(paren
op_logical_neg
(paren
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|2
)braket
op_amp
l_int|0x40000000
)paren
)paren
singleline_comment|// &squot;LKF&squot; link failure bit clear?
(brace
id|ucInboundMessageType
op_assign
(paren
id|UCHAR
)paren
singleline_comment|// ICM DWord3, &quot;Type&quot;
(paren
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|2
)braket
op_amp
l_int|0x0fL
)paren
suffix:semicolon
)brace
r_else
(brace
id|fcChip-&gt;fcStats.linkFailRX
op_increment
suffix:semicolon
singleline_comment|//        printk(&quot;LKF (link failure) bit set on inbound message&bslash;n&quot;);
)brace
singleline_comment|// clears SFQ entry from Tachyon buffer; copies to contiguous ulBuff
id|CpqTsGetSFQEntry
c_func
(paren
id|fcChip
comma
singleline_comment|// i.e. this Device Object
(paren
id|USHORT
)paren
id|fcChip-&gt;SFQ-&gt;producerIndex
comma
singleline_comment|// SFQ producer ndx         
id|ulFibreFrame
comma
id|TRUE
)paren
suffix:semicolon
singleline_comment|// contiguous destination buffer, update chip
singleline_comment|// analyze the incoming frame outside the INT handler...
singleline_comment|// (i.e., Worker)
r_if
c_cond
(paren
id|ucInboundMessageType
op_eq
l_int|1
)paren
(brace
id|fchs
op_assign
(paren
id|TachFCHDR_GCMND
op_star
)paren
id|ulFibreFrame
suffix:semicolon
singleline_comment|// cast to examine IB frame
singleline_comment|// don&squot;t fill up our Q with garbage - only accept FCP-CMND  
singleline_comment|// or XRDY frames
r_if
c_cond
(paren
(paren
id|fchs-&gt;d_id
op_amp
l_int|0xFF000000
)paren
op_eq
l_int|0x06000000
)paren
singleline_comment|// CMND
(brace
singleline_comment|// someone sent us a SCSI command
singleline_comment|//          fcPutScsiQue( cpqfcHBAdata, 
singleline_comment|//                        SFQ_UNASSISTED_FCP, ulFibreFrame); 
)brace
r_else
r_if
c_cond
(paren
(paren
(paren
id|fchs-&gt;d_id
op_amp
l_int|0xFF000000
)paren
op_eq
l_int|0x07000000
)paren
op_logical_or
singleline_comment|// RSP (status)
(paren
id|fchs-&gt;d_id
op_amp
l_int|0xFF000000
)paren
op_eq
l_int|0x05000000
)paren
singleline_comment|// XRDY  
(brace
id|ULONG
id|x_ID
suffix:semicolon
singleline_comment|// Unfortunately, ABTS requires a Freeze on the chip so
singleline_comment|// we can modify the shared memory SEST.  When frozen,
singleline_comment|// any received Exchange frames cannot be processed by
singleline_comment|// Tachyon, so they will be dumped in here.  It is too
singleline_comment|// complex to attempt the reconstruct these frames in
singleline_comment|// the correct Exchange context, so we simply seek to
singleline_comment|// find status or transfer ready frames, and cause the
singleline_comment|// exchange to complete with errors before the timeout
singleline_comment|// expires.  We use a Linux Scsi Cmnd result code that
singleline_comment|// causes immediate retry.
singleline_comment|// Do we have an open exchange that matches this s_id
singleline_comment|// and ox_id?
r_for
c_loop
(paren
id|x_ID
op_assign
l_int|0
suffix:semicolon
id|x_ID
OL
id|TACH_SEST_LEN
suffix:semicolon
id|x_ID
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
op_eq
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|fchs.d_id
op_amp
l_int|0xFFFFFF
)paren
op_logical_and
(paren
id|fchs-&gt;ox_rx_id
op_amp
l_int|0xFFFF0000
)paren
op_eq
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|fchs.ox_rx_id
op_amp
l_int|0xFFFF0000
)paren
)paren
(brace
singleline_comment|//          printk(&quot; #R/X frame x_ID %08X# &quot;, fchs-&gt;ox_rx_id );
singleline_comment|// simulate the anticipated error - since the
singleline_comment|// SEST was frozen, frames were lost...
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_or_assign
id|SFQ_FRAME
suffix:semicolon
singleline_comment|// presumes device is still there: send ABTS.
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|BLS_ABTS
comma
op_amp
id|x_ID
)paren
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// done
)brace
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|ucInboundMessageType
op_eq
l_int|3
)paren
(brace
singleline_comment|// FC Link Service frames (e.g. PLOGI, ACC) come in here.  
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|SFQ_UNKNOWN
comma
id|ulFibreFrame
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ucInboundMessageType
op_eq
l_int|2
)paren
singleline_comment|// &quot;bad FCP&quot;?
(brace
macro_line|#ifdef IMQ_DEBUG
id|printk
c_func
(paren
l_string|&quot;Bad FCP incoming frame discarded&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
singleline_comment|// don&squot;t know this type
(brace
macro_line|#ifdef IMQ_DEBUG 
id|printk
c_func
(paren
l_string|&quot;Incoming frame discarded, type: %Xh&bslash;n&quot;
comma
id|ucInboundMessageType
)paren
suffix:semicolon
macro_line|#endif
)brace
singleline_comment|// Check the Frame Manager&squot;s error counters.  We check them here
singleline_comment|// because presumably the link is up and healthy enough for the
singleline_comment|// counters to be meaningful (i.e., don&squot;t check them while loop
singleline_comment|// is initializing).
id|fcChip-&gt;Registers.FMLinkStatus1.value
op_assign
singleline_comment|// get TL&squot;s counter
id|readl
c_func
(paren
id|fcChip-&gt;Registers.FMLinkStatus1.address
)paren
suffix:semicolon
id|fcChip-&gt;Registers.FMLinkStatus2.value
op_assign
singleline_comment|// get TL&squot;s counter
id|readl
c_func
(paren
id|fcChip-&gt;Registers.FMLinkStatus2.address
)paren
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// We get this CM because we issued a freeze
singleline_comment|// command to stop outbound frames.  We issue the
singleline_comment|// freeze command at Link Up time; when this message
singleline_comment|// is received, the ERQ base can be switched and PDISC
singleline_comment|// frames can be sent.
r_case
id|ERQ_FROZEN_COMPLETION
suffix:colon
singleline_comment|// note: expect ERQ followed immediately
singleline_comment|// by FCP when freezing TL
id|fcChip-&gt;Registers.TYstatus.value
op_assign
singleline_comment|// read what&squot;s frozen
id|readl
c_func
(paren
id|fcChip-&gt;Registers.TYstatus.address
)paren
suffix:semicolon
singleline_comment|// (do nothing; wait for FCP frozen message)
r_break
suffix:semicolon
r_case
id|FCP_FROZEN_COMPLETION
suffix:colon
id|fcChip-&gt;Registers.TYstatus.value
op_assign
singleline_comment|// read what&squot;s frozen
id|readl
c_func
(paren
id|fcChip-&gt;Registers.TYstatus.address
)paren
suffix:semicolon
singleline_comment|// Signal the kernel thread to proceed with SEST modification
id|up
c_func
(paren
id|cpqfcHBAdata-&gt;TachFrozen
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INBOUND_C1_TIMEOUT
suffix:colon
r_case
id|MFS_BUF_WARN
suffix:colon
r_case
id|IMQ_BUF_WARN
suffix:colon
r_break
suffix:semicolon
singleline_comment|// In older Tachyons, we &squot;clear&squot; the internal &squot;core&squot; interrupt state
singleline_comment|// by reading the FMstatus register.  In newer TachLite (Tachyon),
singleline_comment|// we must WRITE the register
singleline_comment|// to clear the condition (TL/TS UG, pg 179)
r_case
id|FRAME_MGR_INTERRUPT
suffix:colon
(brace
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
suffix:semicolon
id|fcChip-&gt;Registers.FMstatus.value
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.FMstatus.address
)paren
suffix:semicolon
singleline_comment|// PROBLEM: It is possible, especially with &quot;dumb&quot; hubs that
singleline_comment|// don&squot;t automatically LIP on by-pass of ports that are going
singleline_comment|// away, for the hub by-pass process to destroy critical 
singleline_comment|// ordered sets of a frame.  The result of this is a hung LPSM
singleline_comment|// (Loop Port State Machine), which on Tachyon results in a
singleline_comment|// (default 2 sec) Loop State Timeout (LST) FM message.  We 
singleline_comment|// want to avoid this relatively huge timeout by detecting
singleline_comment|// likely scenarios which will result in LST.
singleline_comment|// To do this, we could examine FMstatus for Loss of Synchronization
singleline_comment|// and/or Elastic Store (ES) errors.  Of these, Elastic Store is better
singleline_comment|// because we get this indication more quickly than the LOS.
singleline_comment|// Not all ES errors are harmfull, so we don&squot;t want to LIP on every
singleline_comment|// ES.  Instead, on every ES, detect whether our LPSM in in one
singleline_comment|// of the LST states: ARBITRATING, OPEN, OPENED, XMITTED CLOSE,
singleline_comment|// or RECEIVED CLOSE.  (See TL/TS UG, pg. 181)
singleline_comment|// If any of these LPSM states are detected
singleline_comment|// in combination with the LIP while LDn is not set, 
singleline_comment|// send an FM init (LIP F7,F7 for loops)!
singleline_comment|// It is critical to the physical link stability NOT to reset (LIP)
singleline_comment|// more than absolutely necessary; this is a basic premise of the
singleline_comment|// SANMark level 1 spec.
(brace
id|ULONG
id|Lpsm
op_assign
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0xF0
)paren
op_rshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x400
)paren
singleline_comment|// ElasticStore?
op_logical_and
op_logical_neg
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x100
)paren
singleline_comment|// NOT LDn
op_logical_and
op_logical_neg
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x1000
)paren
)paren
singleline_comment|// NOT LF
(brace
r_if
c_cond
(paren
(paren
id|Lpsm
op_ne
l_int|0
)paren
op_logical_or
singleline_comment|// not MONITORING? or
op_logical_neg
(paren
id|Lpsm
op_amp
l_int|0x8
)paren
)paren
singleline_comment|// not already offline?
(brace
singleline_comment|// now check the particular LST states...
r_if
c_cond
(paren
(paren
id|Lpsm
op_eq
id|ARBITRATING
)paren
op_logical_or
(paren
id|Lpsm
op_eq
id|OPEN
)paren
op_logical_or
(paren
id|Lpsm
op_eq
id|OPENED
)paren
op_logical_or
(paren
id|Lpsm
op_eq
id|XMITTD_CLOSE
)paren
op_logical_or
(paren
id|Lpsm
op_eq
id|RCVD_CLOSE
)paren
)paren
(brace
singleline_comment|// re-init the loop before it hangs itself!
id|printk
c_func
(paren
l_string|&quot; #req FMinit on E-S: LPSM %Xh# &quot;
comma
id|Lpsm
)paren
suffix:semicolon
id|fcChip-&gt;fcStats.FMinits
op_increment
suffix:semicolon
id|writel
c_func
(paren
l_int|6
comma
id|fcChip-&gt;Registers.FMcontrol.address
)paren
suffix:semicolon
singleline_comment|// LIP
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x40000
)paren
singleline_comment|// LST?
(brace
id|printk
c_func
(paren
l_string|&quot; #req FMinit on LST, LPSM %Xh# &quot;
comma
id|Lpsm
)paren
suffix:semicolon
id|fcChip-&gt;fcStats.FMinits
op_increment
suffix:semicolon
id|writel
c_func
(paren
l_int|6
comma
id|fcChip-&gt;Registers.FMcontrol.address
)paren
suffix:semicolon
singleline_comment|// LIP
)brace
)brace
singleline_comment|// clear only the &squot;interrupting&squot; type bits for this REG read
id|writel
c_func
(paren
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0xff3fff00L
)paren
comma
id|fcChip-&gt;Registers.FMstatus.address
)paren
suffix:semicolon
singleline_comment|// copy frame manager status to unused ULONG slot
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|0
)braket
op_assign
id|fcChip-&gt;Registers.FMstatus.value
suffix:semicolon
singleline_comment|// (for debugging)
singleline_comment|// Load the Frame Manager&squot;s error counters.  We check them here
singleline_comment|// because presumably the link is up and healthy enough for the
singleline_comment|// counters to be meaningful (i.e., don&squot;t check them while loop
singleline_comment|// is initializing).
id|fcChip-&gt;Registers.FMLinkStatus1.value
op_assign
singleline_comment|// get TL&squot;s counter
id|readl
c_func
(paren
id|fcChip-&gt;Registers.FMLinkStatus1.address
)paren
suffix:semicolon
id|fcChip-&gt;Registers.FMLinkStatus2.value
op_assign
singleline_comment|// get TL&squot;s counter
id|readl
c_func
(paren
id|fcChip-&gt;Registers.FMLinkStatus2.address
)paren
suffix:semicolon
singleline_comment|// Get FM BB_Credit Zero Reg - does not clear on READ
id|fcChip-&gt;Registers.FMBB_CreditZero.value
op_assign
singleline_comment|// get TL&squot;s counter
id|readl
c_func
(paren
id|fcChip-&gt;Registers.FMBB_CreditZero.address
)paren
suffix:semicolon
id|fcParseLinkStatusCounters
c_func
(paren
id|fcChip
)paren
suffix:semicolon
singleline_comment|// load into 6 s/w accumulators
singleline_comment|// LINK DOWN
r_if
c_cond
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x100L
)paren
singleline_comment|// Link DOWN bit
(brace
macro_line|#ifdef IMQ_DEBUG
id|printk
c_func
(paren
l_string|&quot;LinkDn&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot; #LDn# &quot;
)paren
suffix:semicolon
id|fcChip-&gt;fcStats.linkDown
op_increment
suffix:semicolon
id|SetTachTOV
c_func
(paren
id|cpqfcHBAdata
)paren
suffix:semicolon
singleline_comment|// must set according to SANMark
singleline_comment|// Check the ERQ - force it to be &quot;empty&quot; to prevent Tach
singleline_comment|// from sending out frames before we do logins.
r_if
c_cond
(paren
id|fcChip-&gt;ERQ-&gt;producerIndex
op_ne
id|fcChip-&gt;ERQ-&gt;consumerIndex
)paren
(brace
singleline_comment|//&t;  printk(&quot;#ERQ PI != CI#&quot;);
id|CpqTsFreezeTachlite
c_func
(paren
id|fcChip
comma
l_int|1
)paren
suffix:semicolon
singleline_comment|// freeze ERQ only&t;  
id|fcChip-&gt;ERQ-&gt;producerIndex
op_assign
id|fcChip-&gt;ERQ-&gt;consumerIndex
op_assign
l_int|0
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;ERQ-&gt;base
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_ERQ_BASE
)paren
)paren
suffix:semicolon
singleline_comment|// re-writing base forces ERQ PI to equal CI
)brace
singleline_comment|// link down transition occurred -- port_ids can change
singleline_comment|// on next LinkUp, so we must invalidate current logins
singleline_comment|// (and any I/O in progress) until PDISC or PLOGI/PRLI
singleline_comment|// completes
(brace
id|pLoggedInPort
op_assign
op_amp
id|fcChip-&gt;fcPorts
suffix:semicolon
r_while
c_loop
(paren
id|pLoggedInPort
)paren
singleline_comment|// for all ports which are expecting
singleline_comment|// PDISC after the next LIP, set the
singleline_comment|// logoutTimer
(brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;pdisc
)paren
singleline_comment|// expecting PDISC within 2 sec?
(brace
id|pLoggedInPort-&gt;LOGO_timer
op_assign
l_int|3
suffix:semicolon
singleline_comment|// we want 2 seconds
singleline_comment|// but Timer granularity
singleline_comment|// is 1 second
)brace
singleline_comment|// suspend any I/O in progress until
singleline_comment|// PDISC received...
id|pLoggedInPort-&gt;prli
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// block FCP-SCSI commands
id|pLoggedInPort
op_assign
id|pLoggedInPort-&gt;pNextPort
suffix:semicolon
)brace
singleline_comment|// ... all Previously known ports checked
)brace
singleline_comment|// since any hot plugging device may NOT support LILP frames
singleline_comment|// (such as early Tachyon chips), clear this flag indicating
singleline_comment|// we shouldn&squot;t use (our copy of) a LILP map.
singleline_comment|// If we receive an LILP frame, we&squot;ll set it again.
id|fcChip-&gt;Options.LILPin
op_assign
l_int|0
suffix:semicolon
singleline_comment|// our LILPmap is invalid
id|cpqfcHBAdata-&gt;PortDiscDone
op_assign
l_int|0
suffix:semicolon
singleline_comment|// must re-validate FC ports!
singleline_comment|// also, we want to invalidate (i.e. INITIATOR_ABORT) any
singleline_comment|// open Login exchanges, in case the LinkDown happened in the
singleline_comment|// middle of logins.  It&squot;s possible that some ports already
singleline_comment|// ACCepted login commands which we have not processed before
singleline_comment|// another LinkDown occured.  Any accepted Login exhanges are
singleline_comment|// invalidated by LinkDown, even before they are acknowledged.
singleline_comment|// It&squot;s also possible for a port to have a Queued Reply or Request
singleline_comment|// for login which was interrupted by LinkDown; it may come later,
singleline_comment|// but it will be unacceptable to us.
singleline_comment|// we must scan the entire exchange space, find every Login type
singleline_comment|// originated by us, and abort it. This is NOT an abort due to
singleline_comment|// timeout, so we don&squot;t actually send abort to the other port -
singleline_comment|// we just complete it to free up the fcExchange slot.
r_for
c_loop
(paren
id|i
op_assign
id|TACH_SEST_LEN
suffix:semicolon
id|i
OL
id|TACH_MAX_XID
suffix:semicolon
id|i
op_increment
)paren
(brace
singleline_comment|// looking for Extended Link Serv.Exchanges
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
op_eq
id|ELS_PDISC
op_logical_or
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
op_eq
id|ELS_PLOGI
op_logical_or
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
op_eq
id|ELS_PRLI
)paren
(brace
singleline_comment|// ABORT the exchange!
macro_line|#ifdef IMQ_DEBUG
id|printk
c_func
(paren
l_string|&quot;Originator ABORT x_id %Xh, type %Xh, port_id %Xh on LDn&bslash;n&quot;
comma
id|i
comma
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
comma
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|fchs.d_id
)paren
suffix:semicolon
macro_line|#endif
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|status
op_or_assign
id|INITIATOR_ABORT
suffix:semicolon
id|cpqfcTSCompleteExchange
c_func
(paren
id|fcChip
comma
id|i
)paren
suffix:semicolon
singleline_comment|// abort on LDn
)brace
)brace
)brace
singleline_comment|// ################   LINK UP   ##################
r_if
c_cond
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x200L
)paren
singleline_comment|// Link Up bit
(brace
singleline_comment|// AL_PA could have changed
singleline_comment|// We need the following code, duplicated from LinkDn condition,
singleline_comment|// because it&squot;s possible for the Tachyon to re-initialize (hard
singleline_comment|// reset) without ever getting a LinkDn indication.
id|pLoggedInPort
op_assign
op_amp
id|fcChip-&gt;fcPorts
suffix:semicolon
r_while
c_loop
(paren
id|pLoggedInPort
)paren
singleline_comment|// for all ports which are expecting
singleline_comment|// PDISC after the next LIP, set the
singleline_comment|// logoutTimer
(brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;pdisc
)paren
singleline_comment|// expecting PDISC within 2 sec?
(brace
id|pLoggedInPort-&gt;LOGO_timer
op_assign
l_int|3
suffix:semicolon
singleline_comment|// we want 2 seconds
singleline_comment|// but Timer granularity
singleline_comment|// is 1 second
singleline_comment|// suspend any I/O in progress until
singleline_comment|// PDISC received...
)brace
id|pLoggedInPort
op_assign
id|pLoggedInPort-&gt;pNextPort
suffix:semicolon
)brace
singleline_comment|// ... all Previously known ports checked
singleline_comment|// CpqTs acquired AL_PA in register AL_PA (ACQ_ALPA)
id|fcChip-&gt;Registers.rcv_al_pa.value
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.rcv_al_pa.address
)paren
suffix:semicolon
singleline_comment|// Now, if our acquired address is DIFFERENT from our
singleline_comment|// previous one, we are not allow to do PDISC - we
singleline_comment|// must go back to PLOGI, which will terminate I/O in
singleline_comment|// progress for ALL logged in FC devices...
singleline_comment|// (This is highly unlikely).
r_if
c_cond
(paren
(paren
id|fcChip-&gt;Registers.my_al_pa
op_amp
l_int|0xFF
)paren
op_ne
(paren
(paren
id|fcChip-&gt;Registers.rcv_al_pa.value
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
)paren
)paren
(brace
singleline_comment|//&t;  printk(&quot; #our HBA port_id changed!# &quot;); // FC port_id changed!!&t;
id|pLoggedInPort
op_assign
op_amp
id|fcChip-&gt;fcPorts
suffix:semicolon
r_while
c_loop
(paren
id|pLoggedInPort
)paren
singleline_comment|// for all ports which are expecting
singleline_comment|// PDISC after the next LIP, set the
singleline_comment|// logoutTimer
(brace
id|pLoggedInPort-&gt;pdisc
op_assign
id|FALSE
suffix:semicolon
id|pLoggedInPort-&gt;prli
op_assign
id|FALSE
suffix:semicolon
id|pLoggedInPort
op_assign
id|pLoggedInPort-&gt;pNextPort
suffix:semicolon
)brace
singleline_comment|// ... all Previously known ports checked
singleline_comment|// when the port_id changes, we must terminate
singleline_comment|// all open exchanges.
id|cpqfcTSTerminateExchange
c_func
(paren
id|cpqfcHBAdata
comma
l_int|NULL
comma
id|PORTID_CHANGED
)paren
suffix:semicolon
)brace
singleline_comment|// Replace the entire 24-bit port_id.  We only know the
singleline_comment|// lower 8 bits (alpa) from Tachyon; if a FLOGI is done,
singleline_comment|// we&squot;ll get the upper 16-bits from the FLOGI ACC frame.
singleline_comment|// If someone plugs into Fabric switch, we&squot;ll do FLOGI and
singleline_comment|// get full 24-bit port_id; someone could then remove and
singleline_comment|// hot-plug us into a dumb hub.  If we send a 24-bit PLOGI
singleline_comment|// to a &quot;private&quot; loop device, it might blow up.
singleline_comment|// Consequently, we force the upper 16-bits of port_id to
singleline_comment|// be re-set on every LinkUp transition
id|fcChip-&gt;Registers.my_al_pa
op_assign
(paren
id|fcChip-&gt;Registers.rcv_al_pa.value
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
suffix:semicolon
singleline_comment|// copy frame manager status to unused ULONG slot
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|1
)braket
op_assign
id|fcChip-&gt;Registers.my_al_pa
suffix:semicolon
singleline_comment|// (for debugging)
singleline_comment|// for TachLite, we need to write the acquired al_pa
singleline_comment|// back into the FMconfig register, because after
singleline_comment|// first initialization, the AQ (prev. acq.) bit gets
singleline_comment|// set, causing TL FM to use the AL_PA field in FMconfig.
singleline_comment|// (In Tachyon, FM writes the acquired AL_PA for us.)
id|ulBuff
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.FMconfig.address
)paren
suffix:semicolon
id|ulBuff
op_and_assign
l_int|0x00ffffffL
suffix:semicolon
singleline_comment|// mask out current al_pa
id|ulBuff
op_or_assign
(paren
id|fcChip-&gt;Registers.my_al_pa
op_lshift
l_int|24
)paren
suffix:semicolon
singleline_comment|// or in acq. al_pa
id|fcChip-&gt;Registers.FMconfig.value
op_assign
id|ulBuff
suffix:semicolon
singleline_comment|// copy it back
id|writel
c_func
(paren
id|fcChip-&gt;Registers.FMconfig.value
comma
singleline_comment|// put in TachLite
id|fcChip-&gt;Registers.FMconfig.address
)paren
suffix:semicolon
macro_line|#ifdef IMQ_DEBUG
id|printk
c_func
(paren
l_string|&quot;#LUp %Xh, FMstat 0x%08X#&quot;
comma
id|fcChip-&gt;Registers.my_al_pa
comma
id|fcChip-&gt;Registers.FMstatus.value
)paren
suffix:semicolon
macro_line|#endif
singleline_comment|// also set the WRITE-ONLY My_ID Register (for Fabric
singleline_comment|// initialization)
id|writel
c_func
(paren
id|fcChip-&gt;Registers.my_al_pa
comma
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_TACH_My_ID
)paren
suffix:semicolon
id|fcChip-&gt;fcStats.linkUp
op_increment
suffix:semicolon
singleline_comment|// reset TL statistics counters
singleline_comment|// (we ignore these error counters
singleline_comment|// while link is down)
id|ulBuff
op_assign
singleline_comment|// just reset TL&squot;s counter
id|readl
c_func
(paren
id|fcChip-&gt;Registers.FMLinkStatus1.address
)paren
suffix:semicolon
id|ulBuff
op_assign
singleline_comment|// just reset TL&squot;s counter
id|readl
c_func
(paren
id|fcChip-&gt;Registers.FMLinkStatus2.address
)paren
suffix:semicolon
singleline_comment|// for initiator, need to start verifying ports (e.g. PDISC)
id|CpqTsUnFreezeTachlite
c_func
(paren
id|fcChip
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// unfreeze Tachlite, if Link OK
singleline_comment|// Tachyon creates an interesting problem for us on LILP frames.
singleline_comment|// Instead of writing the incoming LILP frame into the SFQ before
singleline_comment|// indicating LINK UP (the actual order of events), Tachyon tells
singleline_comment|// us LINK UP, and later us the LILP.  So we delay, then examine the
singleline_comment|// IMQ for an Inbound CM (x04); if found, we can set
singleline_comment|// LINKACTIVE after processing the LILP.  Otherwise, just proceed.
singleline_comment|// Since Tachyon imposes this time delay (and doesn&squot;t tell us
singleline_comment|// what it is), we have to impose a delay before &quot;Peeking&quot; the IMQ
singleline_comment|// for Tach hardware (DMA) delivery.
singleline_comment|// Processing LILP is required by SANMark
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
singleline_comment|// microsec delay waiting for LILP (if it comes)
r_if
c_cond
(paren
id|PeekIMQEntry
c_func
(paren
id|fcChip
comma
id|ELS_LILP_FRAME
)paren
)paren
(brace
singleline_comment|// found SFQ LILP, which will post LINKACTIVE&t;  
singleline_comment|//&t;  printk(&quot;skipping LINKACTIVE post&bslash;n&quot;);
)brace
r_else
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|LINKACTIVE
comma
id|ulFibreFrame
)paren
suffix:semicolon
)brace
singleline_comment|// ******* Set Fabric Login indication ********
r_if
c_cond
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x2000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; #Fabric# &quot;
)paren
suffix:semicolon
id|fcChip-&gt;Options.fabric
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|fcChip-&gt;Options.fabric
op_assign
l_int|0
suffix:semicolon
singleline_comment|// ******* LIP(F8,x) or BAD AL_PA? ********
r_if
c_cond
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x30000L
)paren
(brace
singleline_comment|// copy the error AL_PAs
id|fcChip-&gt;Registers.rcv_al_pa.value
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.rcv_al_pa.address
)paren
suffix:semicolon
singleline_comment|// Bad AL_PA?
r_if
c_cond
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x10000L
)paren
(brace
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
suffix:semicolon
singleline_comment|// copy &quot;BAD&quot; al_pa field
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|1
)braket
op_assign
(paren
id|fcChip-&gt;Registers.rcv_al_pa.value
op_amp
l_int|0xff00L
)paren
op_rshift
l_int|8
suffix:semicolon
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// DON&squot;T search Scsi Nexus
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|1
)braket
comma
singleline_comment|// port id
l_int|NULL
comma
singleline_comment|// DON&squot;T search linked list for FC WWN
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// DON&squot;T care about end of list
r_if
c_cond
(paren
id|pLoggedInPort
)paren
(brace
singleline_comment|// Just in case we got this BAD_ALPA because a device
singleline_comment|// quietly disappeared (can happen on non-managed hubs such 
singleline_comment|// as the Vixel Rapport 1000),
singleline_comment|// do an Implicit Logout.  We never expect this on a Logged
singleline_comment|// in port (but do expect it on port discovery).
singleline_comment|// (As a reasonable alternative, this could be changed to 
singleline_comment|// simply start the implicit logout timer, giving the device
singleline_comment|// several seconds to &quot;come back&quot;.)
singleline_comment|// 
id|printk
c_func
(paren
l_string|&quot; #BAD alpa %Xh# &quot;
comma
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|cpqfcTSImplicitLogout
c_func
(paren
id|cpqfcHBAdata
comma
id|pLoggedInPort
)paren
suffix:semicolon
)brace
)brace
singleline_comment|// LIP(f8,x)?
r_if
c_cond
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x20000L
)paren
(brace
singleline_comment|// for debugging, copy al_pa field
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|2
)braket
op_assign
(paren
id|fcChip-&gt;Registers.rcv_al_pa.value
op_amp
l_int|0xffL
)paren
suffix:semicolon
singleline_comment|// get the other port&squot;s al_pa
singleline_comment|// (one that sent LIP(F8,?) )
)brace
)brace
singleline_comment|// Elastic store err
r_if
c_cond
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x400L
)paren
(brace
singleline_comment|// don&squot;t count e-s if loop is down!
r_if
c_cond
(paren
op_logical_neg
(paren
id|USHORT
)paren
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x80
)paren
)paren
(brace
id|fcChip-&gt;fcStats.e_stores
op_increment
suffix:semicolon
)brace
)brace
)brace
r_break
suffix:semicolon
r_case
id|INBOUND_FCP_XCHG_COMPLETION
suffix:colon
singleline_comment|// 0x0C
singleline_comment|// Remarks:
singleline_comment|// On Tachlite TL/TS, we get this message when the data phase
singleline_comment|// of a SEST inbound transfer is complete.  For example, if a WRITE command
singleline_comment|// was received with OX_ID 0, we might respond with XFER_RDY with
singleline_comment|// RX_ID 8001.  This would start the SEST controlled data phases.  When
singleline_comment|// all data frames are received, we get this inbound completion. This means
singleline_comment|// we should send a status frame to complete the status phase of the 
singleline_comment|// FCP-SCSI exchange, using the same OX_ID,RX_ID that we used for data
singleline_comment|// frames.
singleline_comment|// See Outbound CM discussion of x_IDs
singleline_comment|// Psuedo Code
singleline_comment|//   Get SEST index (x_ID)
singleline_comment|//     x_ID out of range, return (err condition)
singleline_comment|//   set status bits from 2nd dword
singleline_comment|//   free transactionID &amp; SEST entry
singleline_comment|//   call fcComplete with transactionID &amp; status
id|ulBuff
op_assign
id|fcChip-&gt;IMQ-&gt;QEntry
(braket
id|fcChip-&gt;IMQ-&gt;consumerIndex
)braket
dot
id|word
(braket
l_int|0
)braket
suffix:semicolon
id|x_ID
op_assign
id|ulBuff
op_amp
l_int|0x7fffL
suffix:semicolon
singleline_comment|// lower 14 bits SEST_Index/Trans_ID
singleline_comment|// (mask out MSB &quot;direction&quot; bit)
singleline_comment|// Range check CM OX/RX_ID value...
r_if
c_cond
(paren
id|x_ID
OL
id|TACH_SEST_LEN
)paren
singleline_comment|// don&squot;t go beyond SEST array space
(brace
singleline_comment|//#define FCP_COMPLETION_DBG 1
macro_line|#ifdef FCP_COMPLETION_DBG
id|printk
c_func
(paren
l_string|&quot; FCP_CM x_ID %Xh, status %Xh, Cmnd %p&bslash;n&quot;
comma
id|x_ID
comma
id|ulBuff
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x08000000L
)paren
(brace
singleline_comment|// RPC -Response Phase Complete - or -
singleline_comment|// time to send response frame?
id|RPCset
op_assign
l_int|1
suffix:semicolon
)brace
singleline_comment|// (SEST transaction)
r_else
id|RPCset
op_assign
l_int|0
suffix:semicolon
singleline_comment|// set the status for this Inbound SCSI transaction&squot;s ID
id|dwStatus
op_assign
l_int|0L
suffix:semicolon
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x70000000L
)paren
singleline_comment|// any errs?
(brace
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x40000000L
)paren
(brace
id|dwStatus
op_or_assign
id|LINKFAIL_RX
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x20000000L
)paren
(brace
id|dwStatus
op_or_assign
id|COUNT_ERROR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ulBuff
op_amp
l_int|0x10000000L
)paren
(brace
id|dwStatus
op_or_assign
id|OVERFLOW
suffix:semicolon
)brace
)brace
singleline_comment|// FCP transaction done - copy status
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_assign
id|dwStatus
suffix:semicolon
singleline_comment|// Did the exchange get an FCP-RSP response frame?
singleline_comment|// (Note the little endian/big endian FC payload difference)
r_if
c_cond
(paren
id|RPCset
)paren
singleline_comment|// SEST transaction Response frame rec&squot;d
(brace
singleline_comment|// complete the command in our driver...
id|cpqfcTSCompleteExchange
c_func
(paren
id|fcChip
comma
id|x_ID
)paren
suffix:semicolon
)brace
singleline_comment|// end &quot;RPCset&quot;
r_else
singleline_comment|// (&quot;target&quot; logic)
(brace
singleline_comment|// Tachlite says all data frames have been received - now it&squot;s time
singleline_comment|// to analyze data transfer (successful?), then send a response 
singleline_comment|// frame for this exchange
id|ulFibreFrame
(braket
l_int|0
)braket
op_assign
id|x_ID
suffix:semicolon
singleline_comment|// copy for later reference
singleline_comment|// if this was a TWE, we have to send satus response
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
op_eq
id|SCSI_TWE
)paren
(brace
singleline_comment|//            fcPutScsiQue( cpqfcHBAdata, 
singleline_comment|//                NEED_FCP_RSP, ulFibreFrame);  // (ulFibreFrame not used here)
)brace
)brace
)brace
r_else
singleline_comment|// ERROR CONDITION!  bogus x_ID in completion message
(brace
id|printk
c_func
(paren
l_string|&quot;IN FCP_XCHG: bad x_ID: %Xh&bslash;n&quot;
comma
id|x_ID
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|INBOUND_SCSI_DATA_COMMAND
suffix:colon
r_case
id|BAD_SCSI_FRAME
suffix:colon
r_case
id|INB_SCSI_STATUS_COMPLETION
suffix:colon
r_case
id|BUFFER_PROCESSED_COMPLETION
suffix:colon
r_break
suffix:semicolon
)brace
singleline_comment|// Tachyon is producing;
singleline_comment|// we are consuming
id|fcChip-&gt;IMQ-&gt;consumerIndex
op_increment
suffix:semicolon
singleline_comment|// increment OUR consumerIndex
r_if
c_cond
(paren
id|fcChip-&gt;IMQ-&gt;consumerIndex
op_ge
id|IMQ_LEN
)paren
(brace
singleline_comment|// check for rollover
id|fcChip-&gt;IMQ-&gt;consumerIndex
op_assign
l_int|0L
suffix:semicolon
)brace
singleline_comment|// reset it
r_if
c_cond
(paren
id|fcChip-&gt;IMQ-&gt;producerIndex
op_eq
id|fcChip-&gt;IMQ-&gt;consumerIndex
)paren
(brace
singleline_comment|// all Messages are processed -
id|iStatus
op_assign
l_int|0
suffix:semicolon
singleline_comment|// no more messages to process
)brace
r_else
id|iStatus
op_assign
l_int|1
suffix:semicolon
singleline_comment|// more messages to process
singleline_comment|// update TachLite&squot;s ConsumerIndex... (clears INTA_L)
singleline_comment|// NOTE: according to TL/TS UG, the 
singleline_comment|// &quot;host must return completion messages in sequential order&quot;.
singleline_comment|// Does this mean one at a time, in the order received?  We
singleline_comment|// presume so.
id|writel
c_func
(paren
id|fcChip-&gt;IMQ-&gt;consumerIndex
comma
(paren
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|IMQ_CONSUMER_INDEX
)paren
)paren
suffix:semicolon
macro_line|#if IMQ_DEBUG
id|printk
c_func
(paren
l_string|&quot;Process IMQ: writing consumer ndx %d&bslash;n &quot;
comma
id|fcChip-&gt;IMQ-&gt;consumerIndex
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PI %X, CI %X&bslash;n&quot;
comma
id|fcChip-&gt;IMQ-&gt;producerIndex
comma
id|fcChip-&gt;IMQ-&gt;consumerIndex
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
singleline_comment|// hmmm... why did we get interrupted/called with no message?
id|iStatus
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// nothing to process
macro_line|#if IMQ_DEBUG
id|printk
c_func
(paren
l_string|&quot;Process IMQ: no message PI %Xh  CI %Xh&quot;
comma
id|fcChip-&gt;IMQ-&gt;producerIndex
comma
id|fcChip-&gt;IMQ-&gt;consumerIndex
)paren
suffix:semicolon
macro_line|#endif
)brace
id|LEAVE
c_func
(paren
l_string|&quot;ProcessIMQEntry&quot;
)paren
suffix:semicolon
r_return
id|iStatus
suffix:semicolon
)brace
singleline_comment|// This routine initializes Tachyon according to the following
singleline_comment|// options (opcode1):
singleline_comment|// 1 - RESTART Tachyon, simulate power on condition by shutting
singleline_comment|//     down laser, resetting the hardware, de-allocating all buffers;
singleline_comment|//     continue
singleline_comment|// 2 - Config Tachyon / PCI registers;
singleline_comment|//     continue
singleline_comment|// 3 - Allocating memory and setting Tachyon queues (write Tachyon regs);
singleline_comment|//     continue
singleline_comment|// 4 - Config frame manager registers, initialize, turn on laser
singleline_comment|//
singleline_comment|// Returns:
singleline_comment|//  -1 on fatal error
singleline_comment|//   0 on success
DECL|function|CpqTsInitializeTachLite
r_int
id|CpqTsInitializeTachLite
c_func
(paren
r_void
op_star
id|pHBA
comma
r_int
id|opcode1
comma
r_int
id|opcode2
)paren
(brace
id|CPQFCHBA
op_star
id|cpqfcHBAdata
op_assign
(paren
id|CPQFCHBA
op_star
)paren
id|pHBA
suffix:semicolon
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|ULONG
id|ulBuff
suffix:semicolon
id|UCHAR
id|bBuff
suffix:semicolon
r_int
id|iStatus
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// assume failure
id|ENTER
c_func
(paren
l_string|&quot;InitializeTachLite&quot;
)paren
suffix:semicolon
singleline_comment|// verify board&squot;s base address (sanity check)
r_if
c_cond
(paren
op_logical_neg
id|fcChip-&gt;Registers.ReMapMemBase
)paren
(brace
singleline_comment|// NULL address for card?
r_return
op_minus
l_int|1
suffix:semicolon
)brace
singleline_comment|// FATAL error!
r_switch
c_cond
(paren
id|opcode1
)paren
(brace
r_case
l_int|1
suffix:colon
singleline_comment|// restore hardware to power-on (hard) restart
id|iStatus
op_assign
id|fcChip
op_member_access_from_pointer
id|ResetTachyon
c_func
(paren
id|cpqfcHBAdata
comma
id|opcode2
)paren
suffix:semicolon
singleline_comment|// laser off, reset hardware
singleline_comment|// de-allocate aligned buffers
multiline_comment|/* TBD      // reset FC link Q (producer and consumer = 0)&n;      fcLinkQReset(cpqfcHBAdata); &n;&n;*/
r_if
c_cond
(paren
id|iStatus
)paren
(brace
r_break
suffix:semicolon
)brace
r_case
l_int|2
suffix:colon
singleline_comment|// Config PCI/Tachyon registers
singleline_comment|// NOTE: For Tach TL/TS, bit 31 must be set to 1.  For TS chips, a read
singleline_comment|// of bit 31 indicates state of M66EN signal; if 1, chip may run at 
singleline_comment|// 33-66MHz  (see TL/TS UG, pg 159)
id|ulBuff
op_assign
l_int|0x80000000
suffix:semicolon
singleline_comment|// TachLite Configuration Register
id|writel
c_func
(paren
id|ulBuff
comma
id|fcChip-&gt;Registers.TYconfig.address
)paren
suffix:semicolon
singleline_comment|//      ulBuff = 0x0147L;  // CpqTs PCI CFGCMD register
singleline_comment|//      WritePCIConfiguration( fcChip-&gt;Backplane.bus,
singleline_comment|//                           fcChip-&gt;Backplane.slot, TLCFGCMD, ulBuff, 4);
singleline_comment|//      ulBuff = 0x0L;  // test!
singleline_comment|//      ReadPCIConfiguration( fcChip-&gt;Backplane.bus,
singleline_comment|//                           fcChip-&gt;Backplane.slot, TLCFGCMD, &amp;ulBuff, 4);
singleline_comment|// read back for reference...
id|fcChip-&gt;Registers.TYconfig.value
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.TYconfig.address
)paren
suffix:semicolon
singleline_comment|// what is the PCI bus width?
id|pci_read_config_byte
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
l_int|0x43
comma
singleline_comment|// PCIMCTR offset
op_amp
id|bBuff
)paren
suffix:semicolon
id|fcChip-&gt;Registers.PCIMCTR
op_assign
id|bBuff
suffix:semicolon
singleline_comment|// set string identifying the chip on the circuit board
id|fcChip-&gt;Registers.TYstatus.value
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.TYstatus.address
)paren
suffix:semicolon
(brace
singleline_comment|// Now that we are supporting multiple boards, we need to change
singleline_comment|// this logic to check for PCI vendor/device IDs...
singleline_comment|// for now, quick &amp; dirty is simply checking Chip rev
id|ULONG
id|RevId
op_assign
(paren
id|fcChip-&gt;Registers.TYstatus.value
op_amp
l_int|0x3E0
)paren
op_rshift
l_int|5
suffix:semicolon
id|UCHAR
id|Minor
op_assign
(paren
id|UCHAR
)paren
(paren
id|RevId
op_amp
l_int|0x3
)paren
suffix:semicolon
id|UCHAR
id|Major
op_assign
(paren
id|UCHAR
)paren
(paren
(paren
id|RevId
op_amp
l_int|0x1C
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  HBA Tachyon RevId %d.%d&bslash;n&quot;
comma
id|Major
comma
id|Minor
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|Major
op_eq
l_int|1
)paren
op_logical_and
(paren
id|Minor
op_eq
l_int|2
)paren
)paren
(brace
id|sprintf
c_func
(paren
id|cpqfcHBAdata-&gt;fcChip.Name
comma
id|STACHLITE66_TS12
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|Major
op_eq
l_int|1
)paren
op_logical_and
(paren
id|Minor
op_eq
l_int|3
)paren
)paren
(brace
id|sprintf
c_func
(paren
id|cpqfcHBAdata-&gt;fcChip.Name
comma
id|STACHLITE66_TS13
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|Major
op_eq
l_int|2
)paren
op_logical_and
(paren
id|Minor
op_eq
l_int|1
)paren
)paren
(brace
id|sprintf
c_func
(paren
id|cpqfcHBAdata-&gt;fcChip.Name
comma
id|SAGILENT_XL2_21
)paren
suffix:semicolon
)brace
r_else
id|sprintf
c_func
(paren
id|cpqfcHBAdata-&gt;fcChip.Name
comma
id|STACHLITE_UNKNOWN
)paren
suffix:semicolon
)brace
r_case
l_int|3
suffix:colon
singleline_comment|// allocate mem, set Tachyon Que registers
id|iStatus
op_assign
id|CpqTsCreateTachLiteQues
c_func
(paren
id|cpqfcHBAdata
comma
id|opcode2
)paren
suffix:semicolon
singleline_comment|// now that the Queues exist, Tach can DMA to them, so
singleline_comment|// we can begin processing INTs
singleline_comment|// INTEN register - enable INT (TachLite interrupt)
id|writeb
c_func
(paren
l_int|0x1F
comma
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|IINTEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iStatus
)paren
(brace
r_break
suffix:semicolon
)brace
r_case
l_int|4
suffix:colon
singleline_comment|// Config Fame Manager, Init Loop Command, laser on
singleline_comment|// L_PORT or loopback
singleline_comment|// depending on Options
id|iStatus
op_assign
id|CpqTsInitializeFrameManager
c_func
(paren
id|fcChip
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iStatus
)paren
(brace
singleline_comment|// failed to initialize Frame Manager
r_break
suffix:semicolon
)brace
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|LEAVE
c_func
(paren
l_string|&quot;InitializeTachLite&quot;
)paren
suffix:semicolon
r_return
id|iStatus
suffix:semicolon
)brace
singleline_comment|// Depending on the type of platform memory allocation (e.g. dynamic),
singleline_comment|// it&squot;s probably best to free memory in opposite order as it was allocated.
singleline_comment|// Order of allocation: see other function
DECL|function|CpqTsDestroyTachLiteQues
r_int
id|CpqTsDestroyTachLiteQues
c_func
(paren
r_void
op_star
id|pHBA
comma
r_int
id|opcode
)paren
(brace
id|CPQFCHBA
op_star
id|cpqfcHBAdata
op_assign
(paren
id|CPQFCHBA
op_star
)paren
id|pHBA
suffix:semicolon
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|USHORT
id|i
comma
id|j
comma
id|iStatus
op_assign
l_int|0
suffix:semicolon
r_void
op_star
id|vPtr
suffix:semicolon
singleline_comment|// mem Align manager sets this to the freed address on success
r_int
r_int
id|ulPtr
suffix:semicolon
singleline_comment|// for 64-bit pointer cast (e.g. Alpa machine)
id|ENTER
c_func
(paren
l_string|&quot;DestroyTachLiteQues&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fcChip-&gt;SEST
)paren
(brace
singleline_comment|// search out and free Pool for Extended S/G list pages
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TACH_SEST_LEN
suffix:semicolon
id|i
op_increment
comma
id|j
op_assign
l_int|0
)paren
singleline_comment|// for each exchange
(brace
singleline_comment|// It&squot;s possible that extended S/G pages were allocated and
singleline_comment|// not cleared due to error conditions or O/S driver termination.
singleline_comment|// Make sure they&squot;re all gone.
r_while
c_loop
(paren
id|fcChip-&gt;SEST-&gt;sgPages
(braket
id|i
)braket
dot
id|PoolPage
(braket
id|j
)braket
op_logical_and
(paren
id|j
OL
id|TL_MAX_SGPAGES
)paren
)paren
(brace
id|kfree
c_func
(paren
id|fcChip-&gt;SEST-&gt;sgPages
(braket
id|i
)braket
dot
id|PoolPage
(braket
id|j
op_increment
)braket
)paren
suffix:semicolon
)brace
)brace
id|ulPtr
op_assign
(paren
r_int
r_int
)paren
id|fcChip-&gt;SEST
suffix:semicolon
id|vPtr
op_assign
id|fcMemManager
c_func
(paren
op_amp
id|cpqfcHBAdata-&gt;dynamic_mem
(braket
l_int|0
)braket
comma
l_int|0
comma
l_int|0
comma
(paren
id|ULONG
)paren
id|ulPtr
)paren
suffix:semicolon
singleline_comment|// &squot;free&squot; mem
id|fcChip-&gt;SEST
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// null invalid ptr
r_if
c_cond
(paren
op_logical_neg
id|vPtr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SEST mem not freed&bslash;n&quot;
)paren
suffix:semicolon
id|iStatus
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|fcChip-&gt;SFQ
)paren
(brace
id|ulPtr
op_assign
(paren
r_int
r_int
)paren
id|fcChip-&gt;SFQ
suffix:semicolon
id|vPtr
op_assign
id|fcMemManager
c_func
(paren
op_amp
id|cpqfcHBAdata-&gt;dynamic_mem
(braket
l_int|0
)braket
comma
l_int|0
comma
l_int|0
comma
(paren
id|ULONG
)paren
id|ulPtr
)paren
suffix:semicolon
singleline_comment|// &squot;free&squot; mem
id|fcChip-&gt;SFQ
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// null invalid ptr
r_if
c_cond
(paren
op_logical_neg
id|vPtr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SFQ mem not freed&bslash;n&quot;
)paren
suffix:semicolon
id|iStatus
op_assign
op_minus
l_int|2
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|fcChip-&gt;IMQ
)paren
(brace
singleline_comment|// clear Indexes to show empty Queue
id|fcChip-&gt;IMQ-&gt;producerIndex
op_assign
l_int|0
suffix:semicolon
id|fcChip-&gt;IMQ-&gt;consumerIndex
op_assign
l_int|0
suffix:semicolon
id|ulPtr
op_assign
(paren
r_int
r_int
)paren
id|fcChip-&gt;IMQ
suffix:semicolon
id|vPtr
op_assign
id|fcMemManager
c_func
(paren
op_amp
id|cpqfcHBAdata-&gt;dynamic_mem
(braket
l_int|0
)braket
comma
l_int|0
comma
l_int|0
comma
(paren
id|ULONG
)paren
id|ulPtr
)paren
suffix:semicolon
singleline_comment|// &squot;free&squot; mem
id|fcChip-&gt;IMQ
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// null invalid ptr
r_if
c_cond
(paren
op_logical_neg
id|vPtr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IMQ mem not freed&bslash;n&quot;
)paren
suffix:semicolon
id|iStatus
op_assign
op_minus
l_int|3
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|fcChip-&gt;ERQ
)paren
singleline_comment|// release memory blocks used by the queues
(brace
id|ulPtr
op_assign
(paren
r_int
r_int
)paren
id|fcChip-&gt;ERQ
suffix:semicolon
id|vPtr
op_assign
id|fcMemManager
c_func
(paren
op_amp
id|cpqfcHBAdata-&gt;dynamic_mem
(braket
l_int|0
)braket
comma
l_int|0
comma
l_int|0
comma
(paren
id|ULONG
)paren
id|ulPtr
)paren
suffix:semicolon
singleline_comment|// &squot;free&squot; mem
id|fcChip-&gt;ERQ
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// null invalid ptr
r_if
c_cond
(paren
op_logical_neg
id|vPtr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ERQ mem not freed&bslash;n&quot;
)paren
suffix:semicolon
id|iStatus
op_assign
op_minus
l_int|4
suffix:semicolon
)brace
)brace
singleline_comment|// free up the primary EXCHANGES struct
r_if
c_cond
(paren
id|fcChip-&gt;Exchanges
op_ne
l_int|NULL
)paren
(brace
singleline_comment|//    printk(&quot;kfree() on Exchanges @%p&bslash;n&quot;, fcChip-&gt;Exchanges);
id|kfree
c_func
(paren
id|fcChip-&gt;Exchanges
)paren
suffix:semicolon
)brace
singleline_comment|// free up Link Q
r_if
c_cond
(paren
id|cpqfcHBAdata-&gt;fcLQ
op_ne
l_int|NULL
)paren
(brace
singleline_comment|//    printk(&quot;kfree() on LinkQ @%p&bslash;n&quot;, fcChip-&gt;fcLQ);
id|kfree
c_func
(paren
id|cpqfcHBAdata-&gt;fcLQ
)paren
suffix:semicolon
)brace
id|LEAVE
c_func
(paren
l_string|&quot;DestroyTachLiteQues&quot;
)paren
suffix:semicolon
r_return
id|iStatus
suffix:semicolon
singleline_comment|// non-zero (failed) if any memory not freed
)brace
singleline_comment|// The SFQ is an array with SFQ_LEN length, each element (QEntry)
singleline_comment|// with eight 32-bit words.  TachLite places incoming FC frames (i.e.
singleline_comment|// a valid FC frame with our AL_PA ) in contiguous SFQ entries
singleline_comment|// and sends a completion message telling the host where the frame is
singleline_comment|// in the que.
singleline_comment|// This function copies the current (or oldest not-yet-processed) QEntry to
singleline_comment|// a caller&squot;s contiguous buffer and updates the Tachyon chip&squot;s consumer index
singleline_comment|//
singleline_comment|// NOTE:
singleline_comment|//   An FC frame may consume one or many SFQ entries.  We know the total
singleline_comment|//   length from the completion message.  The caller passes a buffer large
singleline_comment|//   enough for the complete message (max 2k).
DECL|function|CpqTsGetSFQEntry
r_static
r_void
id|CpqTsGetSFQEntry
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|USHORT
id|producerNdx
comma
id|ULONG
op_star
id|ulDestPtr
comma
singleline_comment|// contiguous destination buffer
id|BOOLEAN
id|UpdateChip
)paren
(brace
id|ULONG
id|total_bytes
op_assign
l_int|0
suffix:semicolon
id|ULONG
id|consumerIndex
op_assign
id|fcChip-&gt;SFQ-&gt;consumerIndex
suffix:semicolon
singleline_comment|// check passed copy of SFQ producer index -
singleline_comment|// is a new message waiting for us?
singleline_comment|// equal indexes means SFS is copied
r_while
c_loop
(paren
id|producerNdx
op_ne
id|consumerIndex
)paren
(brace
singleline_comment|// need to process message
id|total_bytes
op_add_assign
l_int|64
suffix:semicolon
singleline_comment|// maintain count to prevent writing past buffer
singleline_comment|// don&squot;t allow copies over Fibre Channel defined length!
r_if
c_cond
(paren
id|total_bytes
op_le
l_int|2048
)paren
(brace
id|memcpy
c_func
(paren
id|ulDestPtr
comma
op_amp
id|fcChip-&gt;SFQ-&gt;QEntry
(braket
id|consumerIndex
)braket
comma
l_int|64
)paren
suffix:semicolon
singleline_comment|// each SFQ entry is 64 bytes
id|ulDestPtr
op_add_assign
l_int|16
suffix:semicolon
singleline_comment|// advance pointer to next 64 byte block
)brace
singleline_comment|// Tachyon is producing,
singleline_comment|// and we are consuming
r_if
c_cond
(paren
op_increment
id|consumerIndex
op_ge
id|SFQ_LEN
)paren
(brace
singleline_comment|// check for rollover
id|consumerIndex
op_assign
l_int|0L
suffix:semicolon
)brace
singleline_comment|// reset it
)brace
singleline_comment|// if specified, update the Tachlite chip ConsumerIndex...
r_if
c_cond
(paren
id|UpdateChip
)paren
(brace
id|fcChip-&gt;SFQ-&gt;consumerIndex
op_assign
id|consumerIndex
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;SFQ-&gt;consumerIndex
comma
id|fcChip-&gt;Registers.SFQconsumerIndex.address
)paren
suffix:semicolon
)brace
)brace
singleline_comment|// TachLite routinely freezes it&squot;s core ques - Outbound FIFO, Inbound FIFO,
singleline_comment|// and Exchange Request Queue (ERQ) on error recover - 
singleline_comment|// (e.g. whenever a LIP occurs).  Here
singleline_comment|// we routinely RESUME by clearing these bits, but only if the loop is up
singleline_comment|// to avoid ERROR IDLE messages forever.
DECL|function|CpqTsUnFreezeTachlite
r_void
id|CpqTsUnFreezeTachlite
c_func
(paren
r_void
op_star
id|pChip
comma
r_int
id|type
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
(paren
id|PTACHYON
)paren
id|pChip
suffix:semicolon
id|fcChip-&gt;Registers.TYcontrol.value
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.TYcontrol.address
)paren
suffix:semicolon
singleline_comment|// (bit 4 of value is GBIC LASER)
singleline_comment|// if we &squot;unfreeze&squot; the core machines before the loop is healthy
singleline_comment|// (i.e. FLT, OS, LS failure bits set in FMstatus)
singleline_comment|// we can get &squot;error idle&squot; messages forever.  Verify that
singleline_comment|// FMstatus (Link Status) is OK before unfreezing.
r_if
c_cond
(paren
op_logical_neg
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x07000000L
)paren
op_logical_and
singleline_comment|// bits clear?
op_logical_neg
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x80
)paren
)paren
singleline_comment|// Active LPSM?
(brace
id|fcChip-&gt;Registers.TYcontrol.value
op_and_assign
op_complement
l_int|0x300L
suffix:semicolon
singleline_comment|// clear FEQ, FFA
r_if
c_cond
(paren
id|type
op_eq
l_int|1
)paren
singleline_comment|// unfreeze ERQ only
(brace
singleline_comment|//      printk(&quot;Unfreezing ERQ&bslash;n&quot;);
id|fcChip-&gt;Registers.TYcontrol.value
op_or_assign
l_int|0x10000L
suffix:semicolon
singleline_comment|// set REQ
)brace
r_else
singleline_comment|// unfreeze both ERQ and FCP-ASSIST (SEST)
(brace
singleline_comment|//      printk(&quot;Unfreezing ERQ &amp; FCP-ASSIST&bslash;n&quot;);
singleline_comment|// set ROF, RIF, REQ - resume Outbound FCP, Inbnd FCP, ERQ
id|fcChip-&gt;Registers.TYcontrol.value
op_or_assign
l_int|0x70000L
suffix:semicolon
singleline_comment|// set ROF, RIF, REQ
)brace
id|writel
c_func
(paren
id|fcChip-&gt;Registers.TYcontrol.value
comma
id|fcChip-&gt;Registers.TYcontrol.address
)paren
suffix:semicolon
)brace
singleline_comment|// readback for verify (TachLite still frozen?)
id|fcChip-&gt;Registers.TYstatus.value
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.TYstatus.address
)paren
suffix:semicolon
)brace
singleline_comment|// Whenever an FC Exchange Abort is required, we must manipulate the
singleline_comment|// Host/Tachyon shared memory SEST table.  Before doing this, we
singleline_comment|// must freeze Tachyon, which flushes certain buffers and ensure we
singleline_comment|// can manipulate the SEST without contention.
singleline_comment|// This freeze function will result in FCP &amp; ERQ FROZEN completion
singleline_comment|// messages (per argument &quot;type&quot;).
DECL|function|CpqTsFreezeTachlite
r_void
id|CpqTsFreezeTachlite
c_func
(paren
r_void
op_star
id|pChip
comma
r_int
id|type
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
(paren
id|PTACHYON
)paren
id|pChip
suffix:semicolon
id|fcChip-&gt;Registers.TYcontrol.value
op_assign
id|readl
c_func
(paren
id|fcChip-&gt;Registers.TYcontrol.address
)paren
suffix:semicolon
singleline_comment|//set FFA, FEQ - freezes SCSI assist and ERQ
r_if
c_cond
(paren
id|type
op_eq
l_int|1
)paren
(brace
singleline_comment|// freeze ERQ only
id|fcChip-&gt;Registers.TYcontrol.value
op_or_assign
l_int|0x100L
suffix:semicolon
)brace
singleline_comment|// (bit 4 is laser)
r_else
singleline_comment|// freeze both FCP assists (SEST) and ERQ
id|fcChip-&gt;Registers.TYcontrol.value
op_or_assign
l_int|0x300L
suffix:semicolon
singleline_comment|// (bit 4 is laser)
id|writel
c_func
(paren
id|fcChip-&gt;Registers.TYcontrol.value
comma
id|fcChip-&gt;Registers.TYcontrol.address
)paren
suffix:semicolon
)brace
singleline_comment|// TL has two Frame Manager Link Status Registers, with three 8-bit
singleline_comment|// fields each. These eight bit counters are cleared after each read,
singleline_comment|// so we define six 32-bit accumulators for these TL counters. This
singleline_comment|// function breaks out each 8-bit field and adds the value to the existing
singleline_comment|// sum.  (s/w counters cleared independently)
DECL|function|fcParseLinkStatusCounters
r_void
id|fcParseLinkStatusCounters
c_func
(paren
id|PTACHYON
id|fcChip
)paren
(brace
id|UCHAR
id|bBuff
suffix:semicolon
id|ULONG
id|ulBuff
suffix:semicolon
singleline_comment|// The BB0 timer usually increments when TL is initialized, resulting
singleline_comment|// in an initially bogus count.  If our own counter is ZERO, it means we
singleline_comment|// are reading this thing for the first time, so we ignore the first count.
singleline_comment|// Also, reading the register does not clear it, so we have to keep an
singleline_comment|// additional static counter to detect rollover (yuk).
r_if
c_cond
(paren
id|fcChip-&gt;fcStats.lastBB0timer
op_eq
l_int|0L
)paren
singleline_comment|// TL was reset? (ignore 1st values)
(brace
singleline_comment|// get TL&squot;s register counter - the &quot;last&quot; count
id|fcChip-&gt;fcStats.lastBB0timer
op_assign
id|fcChip-&gt;Registers.FMBB_CreditZero.value
op_amp
l_int|0x00ffffffL
suffix:semicolon
)brace
r_else
singleline_comment|// subsequent pass - check for rollover
(brace
singleline_comment|// &quot;this&quot; count
id|ulBuff
op_assign
id|fcChip-&gt;Registers.FMBB_CreditZero.value
op_amp
l_int|0x00ffffffL
suffix:semicolon
r_if
c_cond
(paren
id|fcChip-&gt;fcStats.lastBB0timer
OG
id|ulBuff
)paren
singleline_comment|// rollover happened
(brace
singleline_comment|// counter advanced to max...
id|fcChip-&gt;fcStats.BB0_Timer
op_add_assign
(paren
l_int|0x00FFFFFFL
op_minus
id|fcChip-&gt;fcStats.lastBB0timer
)paren
suffix:semicolon
id|fcChip-&gt;fcStats.BB0_Timer
op_add_assign
id|ulBuff
suffix:semicolon
singleline_comment|// plus some more
)brace
r_else
singleline_comment|// no rollover -- more counts or no change
(brace
id|fcChip-&gt;fcStats.BB0_Timer
op_add_assign
(paren
id|ulBuff
op_minus
id|fcChip-&gt;fcStats.lastBB0timer
)paren
suffix:semicolon
)brace
id|fcChip-&gt;fcStats.lastBB0timer
op_assign
id|ulBuff
suffix:semicolon
)brace
id|bBuff
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcChip-&gt;Registers.FMLinkStatus1.value
op_rshift
l_int|24
)paren
suffix:semicolon
id|fcChip-&gt;fcStats.LossofSignal
op_add_assign
id|bBuff
suffix:semicolon
id|bBuff
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcChip-&gt;Registers.FMLinkStatus1.value
op_rshift
l_int|16
)paren
suffix:semicolon
id|fcChip-&gt;fcStats.BadRXChar
op_add_assign
id|bBuff
suffix:semicolon
id|bBuff
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcChip-&gt;Registers.FMLinkStatus1.value
op_rshift
l_int|8
)paren
suffix:semicolon
id|fcChip-&gt;fcStats.LossofSync
op_add_assign
id|bBuff
suffix:semicolon
id|bBuff
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcChip-&gt;Registers.FMLinkStatus2.value
op_rshift
l_int|24
)paren
suffix:semicolon
id|fcChip-&gt;fcStats.Rx_EOFa
op_add_assign
id|bBuff
suffix:semicolon
id|bBuff
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcChip-&gt;Registers.FMLinkStatus2.value
op_rshift
l_int|16
)paren
suffix:semicolon
id|fcChip-&gt;fcStats.Dis_Frm
op_add_assign
id|bBuff
suffix:semicolon
id|bBuff
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcChip-&gt;Registers.FMLinkStatus2.value
op_rshift
l_int|8
)paren
suffix:semicolon
id|fcChip-&gt;fcStats.Bad_CRC
op_add_assign
id|bBuff
suffix:semicolon
)brace
DECL|function|cpqfcTSClearLinkStatusCounters
r_void
id|cpqfcTSClearLinkStatusCounters
c_func
(paren
id|PTACHYON
id|fcChip
)paren
(brace
id|ENTER
c_func
(paren
l_string|&quot;ClearLinkStatusCounters&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|fcChip-&gt;fcStats
comma
l_int|0
comma
r_sizeof
(paren
id|FCSTATS
)paren
)paren
suffix:semicolon
id|LEAVE
c_func
(paren
l_string|&quot;ClearLinkStatusCounters&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// The following function reads the I2C hardware to get the adapter&squot;s
singleline_comment|// World Wide Name (WWN).
singleline_comment|// If the WWN is &quot;500805f1fadb43e8&quot; (as printed on the card), the
singleline_comment|// Tachyon WWN_hi (32-bit) register is 500805f1, and WWN_lo register
singleline_comment|// is fadb43e8.
singleline_comment|// In the NVRAM, the bytes appear as:
singleline_comment|// [2d] ..
singleline_comment|// [2e] .. 
singleline_comment|// [2f] 50
singleline_comment|// [30] 08
singleline_comment|// [31] 05
singleline_comment|// [32] f1
singleline_comment|// [33] fa
singleline_comment|// [34] db
singleline_comment|// [35] 43
singleline_comment|// [36] e8
singleline_comment|//
singleline_comment|// In the Fibre Channel (Big Endian) format, the FC-AL LISM frame will
singleline_comment|// be correctly loaded by Tachyon silicon.  In the login payload, bytes
singleline_comment|// must be correctly swapped for Big Endian format.
DECL|function|CpqTsReadWriteWWN
r_int
id|CpqTsReadWriteWWN
c_func
(paren
id|PVOID
id|pChip
comma
r_int
id|Read
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
(paren
id|PTACHYON
)paren
id|pChip
suffix:semicolon
DECL|macro|NVRAM_SIZE
mdefine_line|#define NVRAM_SIZE 512
r_int
r_int
id|i
comma
id|count
op_assign
id|NVRAM_SIZE
suffix:semicolon
id|UCHAR
id|nvRam
(braket
id|NVRAM_SIZE
)braket
comma
id|WWNbuf
(braket
l_int|8
)braket
suffix:semicolon
id|ULONG
id|ulBuff
suffix:semicolon
r_int
id|iStatus
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// assume failure
r_int
id|WWNoffset
suffix:semicolon
id|ENTER
c_func
(paren
l_string|&quot;ReadWriteWWN&quot;
)paren
suffix:semicolon
singleline_comment|// Now try to read the WWN from the adapter&squot;s NVRAM
r_if
c_cond
(paren
id|Read
)paren
singleline_comment|// READing NVRAM WWN?
(brace
id|ulBuff
op_assign
id|cpqfcTS_ReadNVRAM
c_func
(paren
id|fcChip-&gt;Registers.TYstatus.address
comma
id|fcChip-&gt;Registers.TYcontrol.address
comma
id|count
comma
op_amp
id|nvRam
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ulBuff
)paren
singleline_comment|// NVRAM read successful?
(brace
id|iStatus
op_assign
l_int|0
suffix:semicolon
singleline_comment|// success!
singleline_comment|// for engineering/ prototype boards, the data may be
singleline_comment|// invalid (GIGO, usually all &quot;FF&quot;); this prevents the
singleline_comment|// parse routine from working correctly, which means
singleline_comment|// nothing will be written to our passed buffer.
id|WWNoffset
op_assign
id|cpqfcTS_GetNVRAM_data
c_func
(paren
id|WWNbuf
comma
id|nvRam
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|WWNoffset
)paren
singleline_comment|// uninitialized NVRAM -- copy bytes directly
(brace
id|printk
c_func
(paren
l_string|&quot;CAUTION: Copying NVRAM data on fcChip&bslash;n&quot;
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|WWNbuf
(braket
id|i
)braket
op_assign
id|nvRam
(braket
id|i
op_plus
l_int|0x2f
)braket
suffix:semicolon
)brace
singleline_comment|// dangerous! some formats won&squot;t work
)brace
id|fcChip-&gt;Registers.wwn_hi
op_assign
l_int|0L
suffix:semicolon
id|fcChip-&gt;Registers.wwn_lo
op_assign
l_int|0L
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
singleline_comment|// WWN bytes are big endian in NVRAM
(brace
id|ulBuff
op_assign
l_int|0L
suffix:semicolon
id|ulBuff
op_assign
(paren
id|ULONG
)paren
(paren
id|WWNbuf
(braket
id|i
)braket
)paren
op_lshift
(paren
l_int|8
op_star
(paren
l_int|3
op_minus
id|i
)paren
)paren
suffix:semicolon
id|fcChip-&gt;Registers.wwn_hi
op_or_assign
id|ulBuff
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
singleline_comment|// WWN bytes are big endian in NVRAM
(brace
id|ulBuff
op_assign
l_int|0L
suffix:semicolon
id|ulBuff
op_assign
(paren
id|ULONG
)paren
(paren
id|WWNbuf
(braket
id|i
op_plus
l_int|4
)braket
)paren
op_lshift
(paren
l_int|8
op_star
(paren
l_int|3
op_minus
id|i
)paren
)paren
suffix:semicolon
id|fcChip-&gt;Registers.wwn_lo
op_or_assign
id|ulBuff
suffix:semicolon
)brace
)brace
singleline_comment|// done reading
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;cpqfcTS: NVRAM read failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// WRITE
(brace
singleline_comment|// NOTE: WRITE not supported &amp; not used in released driver.
id|printk
c_func
(paren
l_string|&quot;ReadWriteNRAM: can&squot;t write NVRAM; aborting write&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|LEAVE
c_func
(paren
l_string|&quot;ReadWriteWWN&quot;
)paren
suffix:semicolon
r_return
id|iStatus
suffix:semicolon
)brace
singleline_comment|// The following function reads or writes the entire &quot;NVRAM&quot; contents of 
singleline_comment|// the I2C hardware (i.e. the NM24C03).  Note that HP&squot;s 5121A (TS 66Mhz)
singleline_comment|// adapter does not use the NM24C03 chip, so this function only works on
singleline_comment|// Compaq&squot;s adapters.
DECL|function|CpqTsReadWriteNVRAM
r_int
id|CpqTsReadWriteNVRAM
c_func
(paren
id|PVOID
id|pChip
comma
id|PVOID
id|buf
comma
r_int
id|Read
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
(paren
id|PTACHYON
)paren
id|pChip
suffix:semicolon
DECL|macro|NVRAM_SIZE
mdefine_line|#define NVRAM_SIZE 512
id|ULONG
id|ulBuff
suffix:semicolon
id|UCHAR
op_star
id|ucPtr
op_assign
id|buf
suffix:semicolon
singleline_comment|// cast caller&squot;s void ptr to UCHAR array
r_int
id|iStatus
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// assume failure
r_if
c_cond
(paren
id|Read
)paren
singleline_comment|// READing NVRAM?
(brace
id|ulBuff
op_assign
id|cpqfcTS_ReadNVRAM
c_func
(paren
singleline_comment|// TRUE on success
id|fcChip-&gt;Registers.TYstatus.address
comma
id|fcChip-&gt;Registers.TYcontrol.address
comma
l_int|256
comma
singleline_comment|// bytes to write
id|ucPtr
)paren
suffix:semicolon
singleline_comment|// source ptr
r_if
c_cond
(paren
id|ulBuff
)paren
(brace
id|iStatus
op_assign
l_int|0
suffix:semicolon
)brace
singleline_comment|// success
r_else
(brace
macro_line|#ifdef DBG
id|printk
c_func
(paren
l_string|&quot;CAUTION: NVRAM read failed&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
singleline_comment|// done reading
r_else
singleline_comment|// WRITING NVRAM 
(brace
id|printk
c_func
(paren
l_string|&quot;cpqfcTS: WRITE of FC Controller&squot;s NVRAM disabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|iStatus
suffix:semicolon
)brace
eof
