multiline_comment|/*&n; * Driver for Digigram miXart soundcards&n; *&n; * definitions and makros for basic card access&n; *&n; * Copyright (c) 2003 by Digigram &lt;alsa@digigram.com&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __SOUND_MIXART_HWDEP_H
DECL|macro|__SOUND_MIXART_HWDEP_H
mdefine_line|#define __SOUND_MIXART_HWDEP_H
macro_line|#include &lt;sound/hwdep.h&gt;
DECL|macro|readl_be
mdefine_line|#define readl_be(x) be32_to_cpu(__raw_readl(x))
DECL|macro|writel_be
mdefine_line|#define writel_be(data,addr) __raw_writel(cpu_to_be32(data),addr)
DECL|macro|readl_le
mdefine_line|#define readl_le(x) le32_to_cpu(__raw_readl(x))
DECL|macro|writel_le
mdefine_line|#define writel_le(data,addr) __raw_writel(cpu_to_le32(data),addr)
DECL|macro|MIXART_MEM
mdefine_line|#define MIXART_MEM(mgr,x)&t;((mgr)-&gt;mem[0].virt + (x))
DECL|macro|MIXART_REG
mdefine_line|#define MIXART_REG(mgr,x)&t;((mgr)-&gt;mem[1].virt + (x))
multiline_comment|/* Daughter board Type */
DECL|macro|DAUGHTER_TYPE_MASK
mdefine_line|#define DAUGHTER_TYPE_MASK     0x0F 
DECL|macro|DAUGHTER_VER_MASK
mdefine_line|#define DAUGHTER_VER_MASK      0xF0 
DECL|macro|DAUGHTER_TYPEVER_MASK
mdefine_line|#define DAUGHTER_TYPEVER_MASK  (DAUGHTER_TYPE_MASK|DAUGHTER_VER_MASK)
DECL|macro|MIXART_DAUGHTER_TYPE_NONE
mdefine_line|#define MIXART_DAUGHTER_TYPE_NONE     0x00 
DECL|macro|MIXART_DAUGHTER_TYPE_COBRANET
mdefine_line|#define MIXART_DAUGHTER_TYPE_COBRANET 0x08 
DECL|macro|MIXART_DAUGHTER_TYPE_AES
mdefine_line|#define MIXART_DAUGHTER_TYPE_AES      0x0E
DECL|macro|MIXART_BA0_SIZE
mdefine_line|#define MIXART_BA0_SIZE &t;(16 * 1024 * 1024) /* 16M */
DECL|macro|MIXART_BA1_SIZE
mdefine_line|#define MIXART_BA1_SIZE &t;(4  * 1024)        /* 4k */
multiline_comment|/*&n; * -----------BAR 0 --------------------------------------------------------------------------------------------------------&n; */
DECL|macro|MIXART_PSEUDOREG
mdefine_line|#define  MIXART_PSEUDOREG                          0x2000                    /* base address for pseudoregister */
DECL|macro|MIXART_PSEUDOREG_BOARDNUMBER
mdefine_line|#define  MIXART_PSEUDOREG_BOARDNUMBER              MIXART_PSEUDOREG+0        /* board number */
multiline_comment|/* perfmeter (available when elf loaded)*/
DECL|macro|MIXART_PSEUDOREG_PERF_STREAM_LOAD_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_PERF_STREAM_LOAD_OFFSET  MIXART_PSEUDOREG+0x70     /* streaming load */
DECL|macro|MIXART_PSEUDOREG_PERF_SYSTEM_LOAD_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_PERF_SYSTEM_LOAD_OFFSET  MIXART_PSEUDOREG+0x78     /* system load (reference)*/
DECL|macro|MIXART_PSEUDOREG_PERF_MAILBX_LOAD_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_PERF_MAILBX_LOAD_OFFSET  MIXART_PSEUDOREG+0x7C     /* mailbox load */
DECL|macro|MIXART_PSEUDOREG_PERF_INTERR_LOAD_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_PERF_INTERR_LOAD_OFFSET  MIXART_PSEUDOREG+0x74     /* interrupt handling  load */
multiline_comment|/* motherboard xilinx loader info */
DECL|macro|MIXART_PSEUDOREG_MXLX_BASE_ADDR_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_MXLX_BASE_ADDR_OFFSET    MIXART_PSEUDOREG+0x9C     /* 0x00600000 */ 
DECL|macro|MIXART_PSEUDOREG_MXLX_SIZE_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_MXLX_SIZE_OFFSET         MIXART_PSEUDOREG+0xA0     /* xilinx size in bytes */ 
DECL|macro|MIXART_PSEUDOREG_MXLX_STATUS_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_MXLX_STATUS_OFFSET       MIXART_PSEUDOREG+0xA4     /* status = EMBEBBED_STAT_XXX */ 
multiline_comment|/* elf loader info */
DECL|macro|MIXART_PSEUDOREG_ELF_STATUS_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_ELF_STATUS_OFFSET        MIXART_PSEUDOREG+0xB0     /* status = EMBEBBED_STAT_XXX */ 
multiline_comment|/* &n;*  after the elf code is loaded, and the flowtable info was passed to it,&n;*  the driver polls on this address, until it shows 1 (presence) or 2 (absence)&n;*  once it is non-zero, the daughter board type may be read&n;*/
DECL|macro|MIXART_PSEUDOREG_DBRD_PRESENCE_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_DBRD_PRESENCE_OFFSET     MIXART_PSEUDOREG+0x990   
multiline_comment|/* Global info structure */
DECL|macro|MIXART_PSEUDOREG_DBRD_TYPE_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_DBRD_TYPE_OFFSET         MIXART_PSEUDOREG+0x994    /* Type and version of daughterboard  */
multiline_comment|/* daughterboard xilinx loader info */
DECL|macro|MIXART_PSEUDOREG_DXLX_BASE_ADDR_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_DXLX_BASE_ADDR_OFFSET    MIXART_PSEUDOREG+0x998    /* get the address here where to write the file */ 
DECL|macro|MIXART_PSEUDOREG_DXLX_SIZE_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_DXLX_SIZE_OFFSET         MIXART_PSEUDOREG+0x99C    /* xilinx size in bytes */ 
DECL|macro|MIXART_PSEUDOREG_DXLX_STATUS_OFFSET
mdefine_line|#define  MIXART_PSEUDOREG_DXLX_STATUS_OFFSET       MIXART_PSEUDOREG+0x9A0    /* status = EMBEBBED_STAT_XXX */ 
multiline_comment|/*  */
DECL|macro|MIXART_FLOWTABLE_PTR
mdefine_line|#define  MIXART_FLOWTABLE_PTR                      0x3000                    /* pointer to flow table */
multiline_comment|/* mailbox addresses  */
multiline_comment|/* message DRV -&gt; EMB */
DECL|macro|MSG_INBOUND_POST_HEAD
mdefine_line|#define MSG_INBOUND_POST_HEAD       0x010008&t;/* DRV posts MF + increment4 */
DECL|macro|MSG_INBOUND_POST_TAIL
mdefine_line|#define&t;MSG_INBOUND_POST_TAIL       0x01000C&t;/* EMB gets MF + increment4 */
multiline_comment|/* message EMB -&gt; DRV */
DECL|macro|MSG_OUTBOUND_POST_TAIL
mdefine_line|#define&t;MSG_OUTBOUND_POST_TAIL      0x01001C&t;/* DRV gets MF + increment4 */
DECL|macro|MSG_OUTBOUND_POST_HEAD
mdefine_line|#define&t;MSG_OUTBOUND_POST_HEAD      0x010018&t;/* EMB posts MF + increment4 */
multiline_comment|/* Get Free Frames */
DECL|macro|MSG_INBOUND_FREE_TAIL
mdefine_line|#define MSG_INBOUND_FREE_TAIL       0x010004&t;/* DRV gets MFA + increment4 */
DECL|macro|MSG_OUTBOUND_FREE_TAIL
mdefine_line|#define MSG_OUTBOUND_FREE_TAIL      0x010014&t;/* EMB gets MFA + increment4 */
multiline_comment|/* Put Free Frames */
DECL|macro|MSG_OUTBOUND_FREE_HEAD
mdefine_line|#define MSG_OUTBOUND_FREE_HEAD      0x010010&t;/* DRV puts MFA + increment4 */
DECL|macro|MSG_INBOUND_FREE_HEAD
mdefine_line|#define MSG_INBOUND_FREE_HEAD       0x010000    /* EMB puts MFA + increment4 */
multiline_comment|/* firmware addresses of the message fifos */
DECL|macro|MSG_BOUND_STACK_SIZE
mdefine_line|#define MSG_BOUND_STACK_SIZE        0x004000    /* size of each following stack */
multiline_comment|/* posted messages */
DECL|macro|MSG_OUTBOUND_POST_STACK
mdefine_line|#define MSG_OUTBOUND_POST_STACK     0x108000    /* stack of messages to the DRV */
DECL|macro|MSG_INBOUND_POST_STACK
mdefine_line|#define MSG_INBOUND_POST_STACK      0x104000    /* stack of messages to the EMB */
multiline_comment|/* available empty messages */
DECL|macro|MSG_OUTBOUND_FREE_STACK
mdefine_line|#define MSG_OUTBOUND_FREE_STACK     0x10C000    /* stack of free enveloped for EMB */
DECL|macro|MSG_INBOUND_FREE_STACK
mdefine_line|#define MSG_INBOUND_FREE_STACK      0x100000    /* stack of free enveloped for DRV */
multiline_comment|/* defines for mailbox message frames */
DECL|macro|MSG_FRAME_OFFSET
mdefine_line|#define MSG_FRAME_OFFSET            0x64
DECL|macro|MSG_FRAME_SIZE
mdefine_line|#define MSG_FRAME_SIZE              0x6400
DECL|macro|MSG_FRAME_NUMBER
mdefine_line|#define MSG_FRAME_NUMBER            32
DECL|macro|MSG_FROM_AGENT_ITMF_OFFSET
mdefine_line|#define MSG_FROM_AGENT_ITMF_OFFSET  (MSG_FRAME_OFFSET + (MSG_FRAME_SIZE * MSG_FRAME_NUMBER))
DECL|macro|MSG_TO_AGENT_ITMF_OFFSET
mdefine_line|#define MSG_TO_AGENT_ITMF_OFFSET    (MSG_FROM_AGENT_ITMF_OFFSET + MSG_FRAME_SIZE)
DECL|macro|MSG_HOST_RSC_PROTECTION
mdefine_line|#define MSG_HOST_RSC_PROTECTION     (MSG_TO_AGENT_ITMF_OFFSET + MSG_FRAME_SIZE)
DECL|macro|MSG_AGENT_RSC_PROTECTION
mdefine_line|#define MSG_AGENT_RSC_PROTECTION    (MSG_HOST_RSC_PROTECTION + 4)
multiline_comment|/*&n; * -----------BAR 1 --------------------------------------------------------------------------------------------------------&n; */
multiline_comment|/* interrupt addresses and constants */
DECL|macro|MIXART_PCI_OMIMR_OFFSET
mdefine_line|#define MIXART_PCI_OMIMR_OFFSET                 0x34    /* outbound message interrupt mask register */
DECL|macro|MIXART_PCI_OMISR_OFFSET
mdefine_line|#define MIXART_PCI_OMISR_OFFSET                 0x30    /* outbound message interrupt status register */
DECL|macro|MIXART_PCI_ODBR_OFFSET
mdefine_line|#define MIXART_PCI_ODBR_OFFSET                  0x60    /* outbound doorbell register */
DECL|macro|MIXART_BA1_BRUTAL_RESET_OFFSET
mdefine_line|#define MIXART_BA1_BRUTAL_RESET_OFFSET          0x68    /* write 1 in LSBit to reset board */
DECL|macro|MIXART_HOST_ALL_INTERRUPT_MASKED
mdefine_line|#define MIXART_HOST_ALL_INTERRUPT_MASKED        0x02B   /* 0000 0010 1011 */
DECL|macro|MIXART_ALLOW_OUTBOUND_DOORBELL
mdefine_line|#define MIXART_ALLOW_OUTBOUND_DOORBELL          0x023   /* 0000 0010 0011 */
DECL|macro|MIXART_OIDI
mdefine_line|#define MIXART_OIDI                             0x008   /* 0000 0000 1000 */
r_int
id|snd_mixart_setup_firmware
c_func
(paren
id|mixart_mgr_t
op_star
id|mgr
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_MIXART_HWDEP_H */
eof
