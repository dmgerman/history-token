multiline_comment|/* $Id: irq.h,v 1.20 2001/03/09 01:31:40 davem Exp $&n; * irq.h: IRQ registers on the 64-bit Sparc.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998 Jakub Jelinek (jj@ultra.linux.cz)&n; */
macro_line|#ifndef _SPARC64_IRQ_H
DECL|macro|_SPARC64_IRQ_H
mdefine_line|#define _SPARC64_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|struct|devid_cookie
r_struct
id|devid_cookie
(brace
DECL|member|dummy
r_int
id|dummy
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* You should not mess with this directly. That&squot;s the job of irq.c.&n; *&n; * If you make changes here, please update hand coded assembler of&n; * SBUS/floppy interrupt handler in entry.S -DaveM&n; *&n; * This is currently one DCACHE line, two buckets per L2 cache&n; * line.  Keep this in mind please.&n; */
DECL|struct|ino_bucket
r_struct
id|ino_bucket
(brace
multiline_comment|/* Next handler in per-CPU PIL worklist.  We know that&n;&t; * bucket pointers have the high 32-bits clear, so to&n;&t; * save space we only store the bits we need.&n;&t; */
DECL|member|irq_chain
multiline_comment|/*0x00*/
r_int
r_int
id|irq_chain
suffix:semicolon
multiline_comment|/* PIL to schedule this IVEC at. */
DECL|member|pil
multiline_comment|/*0x04*/
r_int
r_char
id|pil
suffix:semicolon
multiline_comment|/* If an IVEC arrives while irq_info is NULL, we&n;&t; * set this to notify request_irq() about the event.&n;&t; */
DECL|member|pending
multiline_comment|/*0x05*/
r_int
r_char
id|pending
suffix:semicolon
multiline_comment|/* Miscellaneous flags. */
DECL|member|flags
multiline_comment|/*0x06*/
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* This is used to deal with IBF_DMA_SYNC on&n;&t; * Sabre systems.&n;&t; */
DECL|member|synctab_ent
multiline_comment|/*0x07*/
r_int
r_char
id|synctab_ent
suffix:semicolon
multiline_comment|/* Reference to handler for this IRQ.  If this is&n;&t; * non-NULL this means it is active and should be&n;&t; * serviced.  Else the pending member is set to one&n;&t; * and later registry of the interrupt checks for&n;&t; * this condition.&n;&t; *&n;&t; * Normally this is just an irq_action structure.&n;&t; * But, on PCI, if multiple interrupt sources behind&n;&t; * a bridge have multiple interrupt sources that share&n;&t; * the same INO bucket, this points to an array of&n;&t; * pointers to four IRQ action structures.&n;&t; */
DECL|member|irq_info
multiline_comment|/*0x08*/
r_void
op_star
id|irq_info
suffix:semicolon
multiline_comment|/* Sun5 Interrupt Clear Register. */
DECL|member|iclr
multiline_comment|/*0x10*/
r_int
r_int
id|iclr
suffix:semicolon
multiline_comment|/* Sun5 Interrupt Mapping Register. */
DECL|member|imap
multiline_comment|/*0x18*/
r_int
r_int
id|imap
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
r_int
id|pci_dma_wsync
suffix:semicolon
r_extern
r_int
r_int
id|dma_sync_reg_table
(braket
l_int|256
)braket
suffix:semicolon
r_extern
r_int
r_char
id|dma_sync_reg_table_entry
suffix:semicolon
macro_line|#endif
multiline_comment|/* IMAP/ICLR register defines */
DECL|macro|IMAP_VALID
mdefine_line|#define IMAP_VALID&t;&t;0x80000000&t;/* IRQ Enabled&t;&t;*/
DECL|macro|IMAP_TID_UPA
mdefine_line|#define IMAP_TID_UPA&t;&t;0x7c000000&t;/* UPA TargetID&t;&t;*/
DECL|macro|IMAP_AID_SAFARI
mdefine_line|#define IMAP_AID_SAFARI&t;&t;0x7c000000&t;/* Safari AgentID&t;*/
DECL|macro|IMAP_NID_SAFARI
mdefine_line|#define IMAP_NID_SAFARI&t;&t;0x03e00000&t;/* Safari NodeID&t;*/
DECL|macro|IMAP_IGN
mdefine_line|#define IMAP_IGN&t;&t;0x000007c0&t;/* IRQ Group Number&t;*/
DECL|macro|IMAP_INO
mdefine_line|#define IMAP_INO&t;&t;0x0000003f&t;/* IRQ Number&t;&t;*/
DECL|macro|IMAP_INR
mdefine_line|#define IMAP_INR&t;&t;0x000007ff&t;/* Full interrupt number*/
DECL|macro|ICLR_IDLE
mdefine_line|#define ICLR_IDLE&t;&t;0x00000000&t;/* Idle state&t;&t;*/
DECL|macro|ICLR_TRANSMIT
mdefine_line|#define ICLR_TRANSMIT&t;&t;0x00000001&t;/* Transmit state&t;*/
DECL|macro|ICLR_PENDING
mdefine_line|#define ICLR_PENDING&t;&t;0x00000003&t;/* Pending state&t;*/
multiline_comment|/* Only 8-bits are available, be careful.  -DaveM */
DECL|macro|IBF_DMA_SYNC
mdefine_line|#define IBF_DMA_SYNC&t;0x01&t;/* DMA synchronization behind PCI bridge needed. */
DECL|macro|IBF_PCI
mdefine_line|#define IBF_PCI&t;&t;0x02&t;/* Indicates PSYCHO/SABRE/SCHIZO PCI interrupt.&t; */
DECL|macro|IBF_ACTIVE
mdefine_line|#define IBF_ACTIVE&t;0x04&t;/* This interrupt is active and has a handler.&t; */
DECL|macro|IBF_MULTI
mdefine_line|#define IBF_MULTI&t;0x08&t;/* On PCI, indicates shared bucket.&t;&t; */
DECL|macro|NUM_IVECS
mdefine_line|#define NUM_IVECS&t;8192
r_extern
r_struct
id|ino_bucket
id|ivector_table
(braket
id|NUM_IVECS
)braket
suffix:semicolon
DECL|macro|__irq_ino
mdefine_line|#define __irq_ino(irq) &bslash;&n;        (((struct ino_bucket *)(unsigned long)(irq)) - &amp;ivector_table[0])
DECL|macro|__irq_pil
mdefine_line|#define __irq_pil(irq) ((struct ino_bucket *)(unsigned long)(irq))-&gt;pil
DECL|macro|__bucket
mdefine_line|#define __bucket(irq) ((struct ino_bucket *)(unsigned long)(irq))
DECL|macro|__irq
mdefine_line|#define __irq(bucket) ((unsigned int)(unsigned long)(bucket))
DECL|function|__irq_itoa
r_static
id|__inline__
r_char
op_star
id|__irq_itoa
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_static
r_char
id|buff
(braket
l_int|16
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;%d,%x&quot;
comma
id|__irq_pil
c_func
(paren
id|irq
)paren
comma
(paren
r_int
r_int
)paren
id|__irq_ino
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
r_return
id|buff
suffix:semicolon
)brace
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS    15
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|disable_irq_nosync
mdefine_line|#define disable_irq_nosync disable_irq
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|init_timers
c_func
(paren
r_void
(paren
op_star
id|lvl10_irq
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|build_irq
c_func
(paren
r_int
id|pil
comma
r_int
id|inofixup
comma
r_int
r_int
id|iclr
comma
r_int
r_int
id|imap
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sbus_build_irq
c_func
(paren
r_void
op_star
id|sbus
comma
r_int
r_int
id|ino
)paren
suffix:semicolon
r_extern
r_int
r_int
id|psycho_build_irq
c_func
(paren
r_void
op_star
id|psycho
comma
r_int
id|imap_off
comma
r_int
id|ino
comma
r_int
id|need_dma_sync
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|set_cpu_int
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|clear_cpu_int
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|set_irq_udt
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|request_fast_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
id|__const__
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
DECL|function|set_softint
r_extern
id|__inline__
r_void
id|set_softint
c_func
(paren
r_int
r_int
id|bits
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wr&t;%0, 0x0, %%set_softint&quot;
suffix:colon
multiline_comment|/* No outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|bits
)paren
)paren
suffix:semicolon
)brace
DECL|function|clear_softint
r_extern
id|__inline__
r_void
id|clear_softint
c_func
(paren
r_int
r_int
id|bits
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wr&t;%0, 0x0, %%clear_softint&quot;
suffix:colon
multiline_comment|/* No outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|bits
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_softint
r_extern
id|__inline__
r_int
r_int
id|get_softint
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd&t;%%softint, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif
eof
