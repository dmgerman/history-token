multiline_comment|/*&n;** atariints.h -- Atari Linux interrupt handling structs and prototypes&n;**&n;** Copyright 1994 by Bj&#xfffd;rn Brauel&n;**&n;** 5/2/94 Roman Hodek:&n;**   TT interrupt definitions added.&n;**&n;** 12/02/96: (Roman)&n;**   Adapted to new int handling scheme (see ataints.c); revised numbering&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;*/
macro_line|#ifndef _LINUX_ATARIINTS_H_
DECL|macro|_LINUX_ATARIINTS_H_
mdefine_line|#define _LINUX_ATARIINTS_H_
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/atarihw.h&gt;
multiline_comment|/*&n;** Atari Interrupt sources.&n;**&n;*/
DECL|macro|STMFP_SOURCE_BASE
mdefine_line|#define STMFP_SOURCE_BASE  8
DECL|macro|TTMFP_SOURCE_BASE
mdefine_line|#define TTMFP_SOURCE_BASE  24
DECL|macro|SCC_SOURCE_BASE
mdefine_line|#define SCC_SOURCE_BASE    40
DECL|macro|VME_SOURCE_BASE
mdefine_line|#define VME_SOURCE_BASE    56
DECL|macro|VME_MAX_SOURCES
mdefine_line|#define VME_MAX_SOURCES    16
DECL|macro|NUM_ATARI_SOURCES
mdefine_line|#define NUM_ATARI_SOURCES   (VME_SOURCE_BASE+VME_MAX_SOURCES-STMFP_SOURCE_BASE)
multiline_comment|/* convert vector number to int source number */
DECL|macro|IRQ_VECTOR_TO_SOURCE
mdefine_line|#define IRQ_VECTOR_TO_SOURCE(v)&t;((v) - ((v) &lt; 0x20 ? 0x18 : (0x40-8)))
multiline_comment|/* convert irq_handler index to vector number */
DECL|macro|IRQ_SOURCE_TO_VECTOR
mdefine_line|#define IRQ_SOURCE_TO_VECTOR(i)&t;((i) + ((i) &lt; 8 ? 0x18 : (0x40-8)))
multiline_comment|/* interrupt service types */
DECL|macro|IRQ_TYPE_SLOW
mdefine_line|#define IRQ_TYPE_SLOW     0
DECL|macro|IRQ_TYPE_FAST
mdefine_line|#define IRQ_TYPE_FAST     1
DECL|macro|IRQ_TYPE_PRIO
mdefine_line|#define IRQ_TYPE_PRIO     2
DECL|macro|IRQ_SPURIOUS
mdefine_line|#define&t;IRQ_SPURIOUS      (0)
multiline_comment|/* auto-vector interrupts */
DECL|macro|IRQ_AUTO_1
mdefine_line|#define IRQ_AUTO_1        (1)
DECL|macro|IRQ_AUTO_2
mdefine_line|#define IRQ_AUTO_2        (2)
DECL|macro|IRQ_AUTO_3
mdefine_line|#define IRQ_AUTO_3        (3)
DECL|macro|IRQ_AUTO_4
mdefine_line|#define IRQ_AUTO_4        (4)
DECL|macro|IRQ_AUTO_5
mdefine_line|#define IRQ_AUTO_5        (5)
DECL|macro|IRQ_AUTO_6
mdefine_line|#define IRQ_AUTO_6        (6)
DECL|macro|IRQ_AUTO_7
mdefine_line|#define IRQ_AUTO_7        (7)
multiline_comment|/* ST-MFP interrupts */
DECL|macro|IRQ_MFP_BUSY
mdefine_line|#define IRQ_MFP_BUSY      (8)
DECL|macro|IRQ_MFP_DCD
mdefine_line|#define IRQ_MFP_DCD       (9)
DECL|macro|IRQ_MFP_CTS
mdefine_line|#define IRQ_MFP_CTS  &t;  (10)
DECL|macro|IRQ_MFP_GPU
mdefine_line|#define IRQ_MFP_GPU &t;  (11)
DECL|macro|IRQ_MFP_TIMD
mdefine_line|#define IRQ_MFP_TIMD      (12)
DECL|macro|IRQ_MFP_TIMC
mdefine_line|#define IRQ_MFP_TIMC&t;  (13)
DECL|macro|IRQ_MFP_ACIA
mdefine_line|#define IRQ_MFP_ACIA&t;  (14)
DECL|macro|IRQ_MFP_FDC
mdefine_line|#define IRQ_MFP_FDC       (15)
DECL|macro|IRQ_MFP_ACSI
mdefine_line|#define IRQ_MFP_ACSI      IRQ_MFP_FDC
DECL|macro|IRQ_MFP_FSCSI
mdefine_line|#define IRQ_MFP_FSCSI     IRQ_MFP_FDC
DECL|macro|IRQ_MFP_IDE
mdefine_line|#define IRQ_MFP_IDE       IRQ_MFP_FDC
DECL|macro|IRQ_MFP_TIMB
mdefine_line|#define IRQ_MFP_TIMB      (16)
DECL|macro|IRQ_MFP_SERERR
mdefine_line|#define IRQ_MFP_SERERR    (17)
DECL|macro|IRQ_MFP_SEREMPT
mdefine_line|#define IRQ_MFP_SEREMPT   (18)
DECL|macro|IRQ_MFP_RECERR
mdefine_line|#define IRQ_MFP_RECERR    (19)
DECL|macro|IRQ_MFP_RECFULL
mdefine_line|#define IRQ_MFP_RECFULL   (20)
DECL|macro|IRQ_MFP_TIMA
mdefine_line|#define IRQ_MFP_TIMA      (21)
DECL|macro|IRQ_MFP_RI
mdefine_line|#define IRQ_MFP_RI        (22)
DECL|macro|IRQ_MFP_MMD
mdefine_line|#define IRQ_MFP_MMD       (23)
multiline_comment|/* TT-MFP interrupts */
DECL|macro|IRQ_TT_MFP_IO0
mdefine_line|#define IRQ_TT_MFP_IO0       (24)
DECL|macro|IRQ_TT_MFP_IO1
mdefine_line|#define IRQ_TT_MFP_IO1       (25)
DECL|macro|IRQ_TT_MFP_SCC
mdefine_line|#define IRQ_TT_MFP_SCC&t;     (26)
DECL|macro|IRQ_TT_MFP_RI
mdefine_line|#define IRQ_TT_MFP_RI &t;     (27)
DECL|macro|IRQ_TT_MFP_TIMD
mdefine_line|#define IRQ_TT_MFP_TIMD      (28)
DECL|macro|IRQ_TT_MFP_TIMC
mdefine_line|#define IRQ_TT_MFP_TIMC&t;     (29)
DECL|macro|IRQ_TT_MFP_DRVRDY
mdefine_line|#define IRQ_TT_MFP_DRVRDY    (30)
DECL|macro|IRQ_TT_MFP_SCSIDMA
mdefine_line|#define IRQ_TT_MFP_SCSIDMA   (31)
DECL|macro|IRQ_TT_MFP_TIMB
mdefine_line|#define IRQ_TT_MFP_TIMB      (32)
DECL|macro|IRQ_TT_MFP_SERERR
mdefine_line|#define IRQ_TT_MFP_SERERR    (33)
DECL|macro|IRQ_TT_MFP_SEREMPT
mdefine_line|#define IRQ_TT_MFP_SEREMPT   (34)
DECL|macro|IRQ_TT_MFP_RECERR
mdefine_line|#define IRQ_TT_MFP_RECERR    (35)
DECL|macro|IRQ_TT_MFP_RECFULL
mdefine_line|#define IRQ_TT_MFP_RECFULL   (36)
DECL|macro|IRQ_TT_MFP_TIMA
mdefine_line|#define IRQ_TT_MFP_TIMA      (37)
DECL|macro|IRQ_TT_MFP_RTC
mdefine_line|#define IRQ_TT_MFP_RTC       (38)
DECL|macro|IRQ_TT_MFP_SCSI
mdefine_line|#define IRQ_TT_MFP_SCSI      (39)
multiline_comment|/* SCC interrupts */
DECL|macro|IRQ_SCCB_TX
mdefine_line|#define IRQ_SCCB_TX&t;     (40)
DECL|macro|IRQ_SCCB_STAT
mdefine_line|#define IRQ_SCCB_STAT&t;     (42)
DECL|macro|IRQ_SCCB_RX
mdefine_line|#define IRQ_SCCB_RX&t;     (44)
DECL|macro|IRQ_SCCB_SPCOND
mdefine_line|#define IRQ_SCCB_SPCOND&t;     (46)
DECL|macro|IRQ_SCCA_TX
mdefine_line|#define IRQ_SCCA_TX&t;     (48)
DECL|macro|IRQ_SCCA_STAT
mdefine_line|#define IRQ_SCCA_STAT&t;     (50)
DECL|macro|IRQ_SCCA_RX
mdefine_line|#define IRQ_SCCA_RX&t;     (52)
DECL|macro|IRQ_SCCA_SPCOND
mdefine_line|#define IRQ_SCCA_SPCOND&t;     (54)
DECL|macro|INT_CLK
mdefine_line|#define INT_CLK   24576&t;    /* CLK while int_clk =2.456MHz and divide = 100 */
DECL|macro|INT_TICKS
mdefine_line|#define INT_TICKS 246&t;    /* to make sched_time = 99.902... HZ */
DECL|macro|MFP_ENABLE
mdefine_line|#define MFP_ENABLE&t;0
DECL|macro|MFP_PENDING
mdefine_line|#define MFP_PENDING&t;1
DECL|macro|MFP_SERVICE
mdefine_line|#define MFP_SERVICE&t;2
DECL|macro|MFP_MASK
mdefine_line|#define MFP_MASK&t;3
multiline_comment|/* Utility functions for setting/clearing bits in the interrupt registers of&n; * the MFP. &squot;type&squot; should be constant, if &squot;irq&squot; is constant, too, code size is&n; * reduced. set_mfp_bit() is nonsense for PENDING and SERVICE registers. */
DECL|function|get_mfp_bit
r_static
r_inline
r_int
id|get_mfp_bit
c_func
(paren
r_int
id|irq
comma
r_int
id|type
)paren
(brace
r_int
r_char
id|mask
comma
op_star
id|reg
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|reg
op_assign
(paren
r_int
r_char
op_star
)paren
op_amp
id|mfp.int_en_a
op_plus
id|type
op_star
l_int|4
op_plus
(paren
(paren
id|irq
op_amp
l_int|8
)paren
op_rshift
l_int|2
)paren
op_plus
(paren
(paren
(paren
id|irq
op_minus
l_int|8
)paren
op_amp
l_int|16
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
r_return
op_star
id|reg
op_amp
id|mask
suffix:semicolon
)brace
DECL|function|set_mfp_bit
r_static
r_inline
r_void
id|set_mfp_bit
c_func
(paren
r_int
id|irq
comma
r_int
id|type
)paren
(brace
r_int
r_char
id|mask
comma
op_star
id|reg
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|reg
op_assign
(paren
r_int
r_char
op_star
)paren
op_amp
id|mfp.int_en_a
op_plus
id|type
op_star
l_int|4
op_plus
(paren
(paren
id|irq
op_amp
l_int|8
)paren
op_rshift
l_int|2
)paren
op_plus
(paren
(paren
(paren
id|irq
op_minus
l_int|8
)paren
op_amp
l_int|16
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;orb %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;di&quot;
(paren
id|mask
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|reg
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|clear_mfp_bit
r_static
r_inline
r_void
id|clear_mfp_bit
c_func
(paren
r_int
id|irq
comma
r_int
id|type
)paren
(brace
r_int
r_char
id|mask
comma
op_star
id|reg
suffix:semicolon
id|mask
op_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|reg
op_assign
(paren
r_int
r_char
op_star
)paren
op_amp
id|mfp.int_en_a
op_plus
id|type
op_star
l_int|4
op_plus
(paren
(paren
id|irq
op_amp
l_int|8
)paren
op_rshift
l_int|2
)paren
op_plus
(paren
(paren
(paren
id|irq
op_minus
l_int|8
)paren
op_amp
l_int|16
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|MFP_PENDING
op_logical_or
id|type
op_eq
id|MFP_SERVICE
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;moveb %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;di&quot;
(paren
id|mask
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|reg
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
(paren
l_string|&quot;andb %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;di&quot;
(paren
id|mask
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|reg
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * {en,dis}able_irq have the usual semantics of temporary blocking the&n; * interrupt, but not loosing requests that happen between disabling and&n; * enabling. This is done with the MFP mask registers.&n; */
DECL|function|atari_enable_irq
r_static
r_inline
r_void
id|atari_enable_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
OL
id|STMFP_SOURCE_BASE
op_logical_or
id|irq
op_ge
id|SCC_SOURCE_BASE
)paren
r_return
suffix:semicolon
id|set_mfp_bit
c_func
(paren
id|irq
comma
id|MFP_MASK
)paren
suffix:semicolon
)brace
DECL|function|atari_disable_irq
r_static
r_inline
r_void
id|atari_disable_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
OL
id|STMFP_SOURCE_BASE
op_logical_or
id|irq
op_ge
id|SCC_SOURCE_BASE
)paren
r_return
suffix:semicolon
id|clear_mfp_bit
c_func
(paren
id|irq
comma
id|MFP_MASK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * In opposite to {en,dis}able_irq, requests between turn{off,on}_irq are not&n; * &quot;stored&quot;&n; */
DECL|function|atari_turnon_irq
r_extern
r_inline
r_void
id|atari_turnon_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
OL
id|STMFP_SOURCE_BASE
op_logical_or
id|irq
op_ge
id|SCC_SOURCE_BASE
)paren
r_return
suffix:semicolon
id|set_mfp_bit
c_func
(paren
id|irq
comma
id|MFP_ENABLE
)paren
suffix:semicolon
)brace
DECL|function|atari_turnoff_irq
r_extern
r_inline
r_void
id|atari_turnoff_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
OL
id|STMFP_SOURCE_BASE
op_logical_or
id|irq
op_ge
id|SCC_SOURCE_BASE
)paren
r_return
suffix:semicolon
id|clear_mfp_bit
c_func
(paren
id|irq
comma
id|MFP_ENABLE
)paren
suffix:semicolon
id|clear_mfp_bit
c_func
(paren
id|irq
comma
id|MFP_PENDING
)paren
suffix:semicolon
)brace
DECL|function|atari_clear_pending_irq
r_extern
r_inline
r_void
id|atari_clear_pending_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
OL
id|STMFP_SOURCE_BASE
op_logical_or
id|irq
op_ge
id|SCC_SOURCE_BASE
)paren
r_return
suffix:semicolon
id|clear_mfp_bit
c_func
(paren
id|irq
comma
id|MFP_PENDING
)paren
suffix:semicolon
)brace
DECL|function|atari_irq_pending
r_extern
r_inline
r_int
id|atari_irq_pending
c_func
(paren
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
OL
id|STMFP_SOURCE_BASE
op_logical_or
id|irq
op_ge
id|SCC_SOURCE_BASE
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|get_mfp_bit
c_func
(paren
id|irq
comma
id|MFP_PENDING
)paren
suffix:semicolon
)brace
r_int
r_int
id|atari_register_vme_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|atari_unregister_vme_int
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* linux/atariints.h */
eof
