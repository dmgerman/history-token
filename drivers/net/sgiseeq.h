multiline_comment|/* $Id: sgiseeq.h,v 1.4 1999/10/09 00:01:24 ralf Exp $&n; * sgiseeq.h: Defines for the Seeq8003 ethernet controller.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#ifndef _SGISEEQ_H
DECL|macro|_SGISEEQ_H
mdefine_line|#define _SGISEEQ_H
DECL|struct|sgiseeq_wregs
r_struct
id|sgiseeq_wregs
(brace
DECL|member|multicase_high
r_volatile
r_int
r_int
id|multicase_high
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|frame_gap
r_volatile
r_int
r_int
id|frame_gap
suffix:semicolon
DECL|member|control
r_volatile
r_int
r_int
id|control
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sgiseeq_rregs
r_struct
id|sgiseeq_rregs
(brace
DECL|member|collision_tx
r_volatile
r_int
r_int
id|collision_tx
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|collision_all
r_volatile
r_int
r_int
id|collision_all
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|_unused0
r_volatile
r_int
r_int
id|_unused0
suffix:semicolon
DECL|member|rflags
r_volatile
r_int
r_int
id|rflags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sgiseeq_regs
r_struct
id|sgiseeq_regs
(brace
r_union
(brace
DECL|member|eth_addr
r_volatile
r_int
r_int
id|eth_addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|multicast_low
r_volatile
r_int
r_int
id|multicast_low
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|wregs
r_struct
id|sgiseeq_wregs
id|wregs
suffix:semicolon
DECL|member|rregs
r_struct
id|sgiseeq_rregs
id|rregs
suffix:semicolon
DECL|member|rw
)brace
id|rw
suffix:semicolon
DECL|member|rstat
r_volatile
r_int
r_int
id|rstat
suffix:semicolon
DECL|member|tstat
r_volatile
r_int
r_int
id|tstat
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Seeq8003 receive status register */
DECL|macro|SEEQ_RSTAT_OVERF
mdefine_line|#define SEEQ_RSTAT_OVERF   0x001 /* Overflow */
DECL|macro|SEEQ_RSTAT_CERROR
mdefine_line|#define SEEQ_RSTAT_CERROR  0x002 /* CRC error */
DECL|macro|SEEQ_RSTAT_DERROR
mdefine_line|#define SEEQ_RSTAT_DERROR  0x004 /* Dribble error */
DECL|macro|SEEQ_RSTAT_SFRAME
mdefine_line|#define SEEQ_RSTAT_SFRAME  0x008 /* Short frame */
DECL|macro|SEEQ_RSTAT_REOF
mdefine_line|#define SEEQ_RSTAT_REOF    0x010 /* Received end of frame */
DECL|macro|SEEQ_RSTAT_FIG
mdefine_line|#define SEEQ_RSTAT_FIG     0x020 /* Frame is good */
DECL|macro|SEEQ_RSTAT_TIMEO
mdefine_line|#define SEEQ_RSTAT_TIMEO   0x040 /* Timeout, or late receive */
DECL|macro|SEEQ_RSTAT_WHICH
mdefine_line|#define SEEQ_RSTAT_WHICH   0x080 /* Which status, 1=old 0=new */
DECL|macro|SEEQ_RSTAT_LITTLE
mdefine_line|#define SEEQ_RSTAT_LITTLE  0x100 /* DMA is done in little endian format */
DECL|macro|SEEQ_RSTAT_SDMA
mdefine_line|#define SEEQ_RSTAT_SDMA    0x200 /* DMA has started */
DECL|macro|SEEQ_RSTAT_ADMA
mdefine_line|#define SEEQ_RSTAT_ADMA    0x400 /* DMA is active */
DECL|macro|SEEQ_RSTAT_ROVERF
mdefine_line|#define SEEQ_RSTAT_ROVERF  0x800 /* Receive buffer overflow */
multiline_comment|/* Seeq8003 receive command register */
DECL|macro|SEEQ_RCMD_RDISAB
mdefine_line|#define SEEQ_RCMD_RDISAB   0x000 /* Disable receiver on the Seeq8003 */
DECL|macro|SEEQ_RCMD_IOVERF
mdefine_line|#define SEEQ_RCMD_IOVERF   0x001 /* IRQ on buffer overflows */
DECL|macro|SEEQ_RCMD_ICRC
mdefine_line|#define SEEQ_RCMD_ICRC     0x002 /* IRQ on CRC errors */
DECL|macro|SEEQ_RCMD_IDRIB
mdefine_line|#define SEEQ_RCMD_IDRIB    0x004 /* IRQ on dribble errors */
DECL|macro|SEEQ_RCMD_ISHORT
mdefine_line|#define SEEQ_RCMD_ISHORT   0x008 /* IRQ on short frames */
DECL|macro|SEEQ_RCMD_IEOF
mdefine_line|#define SEEQ_RCMD_IEOF     0x010 /* IRQ on end of frame */
DECL|macro|SEEQ_RCMD_IGOOD
mdefine_line|#define SEEQ_RCMD_IGOOD    0x020 /* IRQ on good frames */
DECL|macro|SEEQ_RCMD_RANY
mdefine_line|#define SEEQ_RCMD_RANY     0x040 /* Receive any frame */
DECL|macro|SEEQ_RCMD_RBCAST
mdefine_line|#define SEEQ_RCMD_RBCAST   0x080 /* Receive broadcasts */
DECL|macro|SEEQ_RCMD_RBMCAST
mdefine_line|#define SEEQ_RCMD_RBMCAST  0x0c0 /* Receive broadcasts/multicasts */
multiline_comment|/* Seeq8003 transmit status register */
DECL|macro|SEEQ_TSTAT_UFLOW
mdefine_line|#define SEEQ_TSTAT_UFLOW   0x001 /* Transmit buffer underflow */
DECL|macro|SEEQ_TSTAT_CLS
mdefine_line|#define SEEQ_TSTAT_CLS     0x002 /* Collision detected */
DECL|macro|SEEQ_TSTAT_R16
mdefine_line|#define SEEQ_TSTAT_R16     0x004 /* Did 16 retries to tx a frame */
DECL|macro|SEEQ_TSTAT_PTRANS
mdefine_line|#define SEEQ_TSTAT_PTRANS  0x008 /* Packet was transmitted ok */
DECL|macro|SEEQ_TSTAT_LCLS
mdefine_line|#define SEEQ_TSTAT_LCLS    0x010 /* Late collision occurred */
DECL|macro|SEEQ_TSTAT_WHICH
mdefine_line|#define SEEQ_TSTAT_WHICH   0x080 /* Which status, 1=old 0=new */
DECL|macro|SEEQ_TSTAT_TLE
mdefine_line|#define SEEQ_TSTAT_TLE     0x100 /* DMA is done in little endian format */
DECL|macro|SEEQ_TSTAT_SDMA
mdefine_line|#define SEEQ_TSTAT_SDMA    0x200 /* DMA has started */
DECL|macro|SEEQ_TSTAT_ADMA
mdefine_line|#define SEEQ_TSTAT_ADMA    0x400 /* DMA is active */
multiline_comment|/* Seeq8003 transmit command register */
DECL|macro|SEEQ_TCMD_RB0
mdefine_line|#define SEEQ_TCMD_RB0      0x00 /* Register bank zero w/station addr */
DECL|macro|SEEQ_TCMD_IUF
mdefine_line|#define SEEQ_TCMD_IUF      0x01 /* IRQ on tx underflow */
DECL|macro|SEEQ_TCMD_IC
mdefine_line|#define SEEQ_TCMD_IC       0x02 /* IRQ on collisions */
DECL|macro|SEEQ_TCMD_I16
mdefine_line|#define SEEQ_TCMD_I16      0x04 /* IRQ after 16 failed attempts to tx frame */
DECL|macro|SEEQ_TCMD_IPT
mdefine_line|#define SEEQ_TCMD_IPT      0x08 /* IRQ when packet successfully transmitted */
DECL|macro|SEEQ_TCMD_RB1
mdefine_line|#define SEEQ_TCMD_RB1      0x20 /* Register bank one w/multi-cast low byte */ 
DECL|macro|SEEQ_TCMD_RB2
mdefine_line|#define SEEQ_TCMD_RB2      0x40 /* Register bank two w/multi-cast high byte */
multiline_comment|/* Seeq8003 control register */
DECL|macro|SEEQ_CTRL_XCNT
mdefine_line|#define SEEQ_CTRL_XCNT     0x01
DECL|macro|SEEQ_CTRL_ACCNT
mdefine_line|#define SEEQ_CTRL_ACCNT    0x02
DECL|macro|SEEQ_CTRL_SFLAG
mdefine_line|#define SEEQ_CTRL_SFLAG    0x04
DECL|macro|SEEQ_CTRL_EMULTI
mdefine_line|#define SEEQ_CTRL_EMULTI   0x08
DECL|macro|SEEQ_CTRL_ESHORT
mdefine_line|#define SEEQ_CTRL_ESHORT   0x10
DECL|macro|SEEQ_CTRL_ENCARR
mdefine_line|#define SEEQ_CTRL_ENCARR   0x20
multiline_comment|/* Seeq8003 control registers on the SGI Hollywood HPC. */
DECL|macro|SEEQ_HPIO_P1BITS
mdefine_line|#define SEEQ_HPIO_P1BITS  0x00000001 /* cycles to stay in P1 phase for PIO */
DECL|macro|SEEQ_HPIO_P2BITS
mdefine_line|#define SEEQ_HPIO_P2BITS  0x00000060 /* cycles to stay in P2 phase for PIO */
DECL|macro|SEEQ_HPIO_P3BITS
mdefine_line|#define SEEQ_HPIO_P3BITS  0x00000100 /* cycles to stay in P3 phase for PIO */
DECL|macro|SEEQ_HDMA_D1BITS
mdefine_line|#define SEEQ_HDMA_D1BITS  0x00000006 /* cycles to stay in D1 phase for DMA */
DECL|macro|SEEQ_HDMA_D2BITS
mdefine_line|#define SEEQ_HDMA_D2BITS  0x00000020 /* cycles to stay in D2 phase for DMA */
DECL|macro|SEEQ_HDMA_D3BITS
mdefine_line|#define SEEQ_HDMA_D3BITS  0x00000000 /* cycles to stay in D3 phase for DMA */
DECL|macro|SEEQ_HDMA_TIMEO
mdefine_line|#define SEEQ_HDMA_TIMEO   0x00030000 /* cycles for DMA timeout */
DECL|macro|SEEQ_HCTL_NORM
mdefine_line|#define SEEQ_HCTL_NORM    0x00000000 /* Normal operation mode */
DECL|macro|SEEQ_HCTL_RESET
mdefine_line|#define SEEQ_HCTL_RESET   0x00000001 /* Reset Seeq8003 and HPC interface */
DECL|macro|SEEQ_HCTL_IPEND
mdefine_line|#define SEEQ_HCTL_IPEND   0x00000002 /* IRQ is pending for the chip */
DECL|macro|SEEQ_HCTL_IPG
mdefine_line|#define SEEQ_HCTL_IPG     0x00001000 /* Inter-packet gap */
DECL|macro|SEEQ_HCTL_RFIX
mdefine_line|#define SEEQ_HCTL_RFIX    0x00002000 /* At rxdc, clear end-of-packet */
DECL|macro|SEEQ_HCTL_EFIX
mdefine_line|#define SEEQ_HCTL_EFIX    0x00004000 /* fixes intr status bit settings */
DECL|macro|SEEQ_HCTL_IFIX
mdefine_line|#define SEEQ_HCTL_IFIX    0x00008000 /* enable startup timeouts */
macro_line|#endif /* !(_SGISEEQ_H) */
eof
