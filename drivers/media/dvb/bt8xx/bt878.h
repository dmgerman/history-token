multiline_comment|/* &n;    bt878.h - Bt878 audio module (register offsets)&n;&n;    Copyright (C) 2002 Peter Hettkamp &lt;peter.hettkamp@t-online.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _BT878_H_
DECL|macro|_BT878_H_
mdefine_line|#define _BT878_H_
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &quot;bt848.h&quot;
macro_line|#include &quot;bttv.h&quot;
DECL|macro|BT878_VERSION_CODE
mdefine_line|#define BT878_VERSION_CODE 0x000000
DECL|macro|BT878_AINT_STAT
mdefine_line|#define BT878_AINT_STAT&t;&t;0x100
DECL|macro|BT878_ARISCS
mdefine_line|#define BT878_ARISCS&t;&t;(0xf&lt;&lt;28)
DECL|macro|BT878_ARISC_EN
mdefine_line|#define BT878_ARISC_EN&t;&t;(1&lt;&lt;27)
DECL|macro|BT878_ASCERR
mdefine_line|#define BT878_ASCERR&t;&t;(1&lt;&lt;19)
DECL|macro|BT878_AOCERR
mdefine_line|#define BT878_AOCERR&t;&t;(1&lt;&lt;18)
DECL|macro|BT878_APABORT
mdefine_line|#define BT878_APABORT&t;&t;(1&lt;&lt;17)
DECL|macro|BT878_ARIPERR
mdefine_line|#define BT878_ARIPERR&t;&t;(1&lt;&lt;16)
DECL|macro|BT878_APPERR
mdefine_line|#define BT878_APPERR&t;&t;(1&lt;&lt;15)
DECL|macro|BT878_AFDSR
mdefine_line|#define BT878_AFDSR&t;&t;(1&lt;&lt;14)
DECL|macro|BT878_AFTRGT
mdefine_line|#define BT878_AFTRGT&t;&t;(1&lt;&lt;13)
DECL|macro|BT878_AFBUS
mdefine_line|#define BT878_AFBUS&t;&t;(1&lt;&lt;12)
DECL|macro|BT878_ARISCI
mdefine_line|#define BT878_ARISCI&t;&t;(1&lt;&lt;11)
DECL|macro|BT878_AOFLOW
mdefine_line|#define BT878_AOFLOW&t;&t;(1&lt;&lt;3)
DECL|macro|BT878_AINT_MASK
mdefine_line|#define BT878_AINT_MASK&t;&t;0x104
DECL|macro|BT878_AGPIO_DMA_CTL
mdefine_line|#define BT878_AGPIO_DMA_CTL&t;0x10c
DECL|macro|BT878_A_GAIN
mdefine_line|#define BT878_A_GAIN&t;&t;(0xf&lt;&lt;28)
DECL|macro|BT878_A_G2X
mdefine_line|#define BT878_A_G2X&t;&t;(1&lt;&lt;27)
DECL|macro|BT878_A_PWRDN
mdefine_line|#define BT878_A_PWRDN&t;&t;(1&lt;&lt;26)
DECL|macro|BT878_A_SEL
mdefine_line|#define BT878_A_SEL&t;&t;(3&lt;&lt;24)
DECL|macro|BT878_DA_SCE
mdefine_line|#define BT878_DA_SCE&t;&t;(1&lt;&lt;23)
DECL|macro|BT878_DA_LRI
mdefine_line|#define BT878_DA_LRI&t;&t;(1&lt;&lt;22)
DECL|macro|BT878_DA_MLB
mdefine_line|#define BT878_DA_MLB&t;&t;(1&lt;&lt;21)
DECL|macro|BT878_DA_LRD
mdefine_line|#define BT878_DA_LRD&t;&t;(0x1f&lt;&lt;16)
DECL|macro|BT878_DA_DPM
mdefine_line|#define BT878_DA_DPM&t;&t;(1&lt;&lt;15)
DECL|macro|BT878_DA_SBR
mdefine_line|#define BT878_DA_SBR&t;&t;(1&lt;&lt;14)
DECL|macro|BT878_DA_ES2
mdefine_line|#define BT878_DA_ES2&t;&t;(1&lt;&lt;13)
DECL|macro|BT878_DA_LMT
mdefine_line|#define BT878_DA_LMT&t;&t;(1&lt;&lt;12)
DECL|macro|BT878_DA_SDR
mdefine_line|#define BT878_DA_SDR&t;&t;(0xf&lt;&lt;8)
DECL|macro|BT878_DA_IOM
mdefine_line|#define BT878_DA_IOM&t;&t;(3&lt;&lt;6)
DECL|macro|BT878_DA_APP
mdefine_line|#define BT878_DA_APP&t;&t;(1&lt;&lt;5)
DECL|macro|BT878_ACAP_EN
mdefine_line|#define BT878_ACAP_EN&t;&t;(1&lt;&lt;4)
DECL|macro|BT878_PKTP
mdefine_line|#define BT878_PKTP&t;&t;(3&lt;&lt;2)
DECL|macro|BT878_RISC_EN
mdefine_line|#define BT878_RISC_EN&t;&t;(1&lt;&lt;1)
DECL|macro|BT878_FIFO_EN
mdefine_line|#define BT878_FIFO_EN&t;&t;1
DECL|macro|BT878_APACK_LEN
mdefine_line|#define BT878_APACK_LEN&t;&t;0x110
DECL|macro|BT878_AFP_LEN
mdefine_line|#define BT878_AFP_LEN&t;&t;(0xff&lt;&lt;16)
DECL|macro|BT878_ALP_LEN
mdefine_line|#define BT878_ALP_LEN&t;&t;0xfff
DECL|macro|BT878_ARISC_START
mdefine_line|#define BT878_ARISC_START&t;0x114
DECL|macro|BT878_ARISC_PC
mdefine_line|#define BT878_ARISC_PC&t;&t;0x120
multiline_comment|/* BT878 FUNCTION 0 REGISTERS */
DECL|macro|BT878_GPIO_DMA_CTL
mdefine_line|#define BT878_GPIO_DMA_CTL&t;0x10c
multiline_comment|/* Interrupt register */
DECL|macro|BT878_INT_STAT
mdefine_line|#define BT878_INT_STAT&t;&t;0x100
DECL|macro|BT878_INT_MASK
mdefine_line|#define BT878_INT_MASK&t;&t;0x104
DECL|macro|BT878_I2CRACK
mdefine_line|#define BT878_I2CRACK&t;&t;(1&lt;&lt;25)
DECL|macro|BT878_I2CDONE
mdefine_line|#define BT878_I2CDONE&t;&t;(1&lt;&lt;8)
DECL|macro|BT878_MAX
mdefine_line|#define BT878_MAX 4
DECL|macro|BT878_RISC_SYNC_MASK
mdefine_line|#define BT878_RISC_SYNC_MASK&t;(1 &lt;&lt; 15)
r_extern
r_int
id|bt878_num
suffix:semicolon
r_extern
r_struct
id|bt878
id|bt878
(braket
id|BT878_MAX
)braket
suffix:semicolon
DECL|struct|bt878
r_struct
id|bt878
(brace
DECL|member|gpio_lock
r_struct
id|semaphore
id|gpio_lock
suffix:semicolon
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
DECL|member|bttv_nr
r_int
r_int
id|bttv_nr
suffix:semicolon
DECL|member|adapter
r_struct
id|i2c_adapter
op_star
id|adapter
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|TS_Size
r_int
r_int
id|TS_Size
suffix:semicolon
DECL|member|revision
r_int
r_char
id|revision
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|bt878_adr
r_int
r_int
id|bt878_adr
suffix:semicolon
DECL|member|bt878_mem
r_volatile
r_void
id|__iomem
op_star
id|bt878_mem
suffix:semicolon
multiline_comment|/* function 1 */
DECL|member|finished_block
r_volatile
id|u32
id|finished_block
suffix:semicolon
DECL|member|last_block
r_volatile
id|u32
id|last_block
suffix:semicolon
DECL|member|block_count
id|u32
id|block_count
suffix:semicolon
DECL|member|block_bytes
id|u32
id|block_bytes
suffix:semicolon
DECL|member|line_bytes
id|u32
id|line_bytes
suffix:semicolon
DECL|member|line_count
id|u32
id|line_count
suffix:semicolon
DECL|member|buf_size
id|u32
id|buf_size
suffix:semicolon
DECL|member|buf_cpu
id|u8
op_star
id|buf_cpu
suffix:semicolon
DECL|member|buf_dma
id|dma_addr_t
id|buf_dma
suffix:semicolon
DECL|member|risc_size
id|u32
id|risc_size
suffix:semicolon
DECL|member|risc_cpu
id|u32
op_star
id|risc_cpu
suffix:semicolon
DECL|member|risc_dma
id|dma_addr_t
id|risc_dma
suffix:semicolon
DECL|member|risc_pos
id|u32
id|risc_pos
suffix:semicolon
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
DECL|member|shutdown
r_int
id|shutdown
suffix:semicolon
)brace
suffix:semicolon
r_void
id|bt878_start
c_func
(paren
r_struct
id|bt878
op_star
id|bt
comma
id|u32
id|controlreg
comma
id|u32
id|op_sync_orin
comma
id|u32
id|irq_err_ignore
)paren
suffix:semicolon
r_void
id|bt878_stop
c_func
(paren
r_struct
id|bt878
op_star
id|bt
)paren
suffix:semicolon
macro_line|#if defined(__powerpc__)&t;/* big-endian */
DECL|function|io_st_le32
r_extern
id|__inline__
r_void
id|io_st_le32
c_func
(paren
r_volatile
r_int
id|__iomem
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stwbrx %1,0,%2&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;eieio&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|bmtwrite
mdefine_line|#define bmtwrite(dat,adr)  io_st_le32((adr),(dat))
DECL|macro|bmtread
mdefine_line|#define bmtread(adr)       ld_le32((adr))
macro_line|#else
DECL|macro|bmtwrite
mdefine_line|#define bmtwrite(dat,adr)  writel((dat), (adr))
DECL|macro|bmtread
mdefine_line|#define bmtread(adr)       readl(adr)
macro_line|#endif
macro_line|#endif
eof
