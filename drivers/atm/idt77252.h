multiline_comment|/******************************************************************* &n; * ident &quot;$Id: idt77252.h,v 1.1 2001/11/05 21:52:22 ecd Exp $&quot;&n; *&n; * $Author: ecd $&n; * $Date: 2001/11/05 21:52:22 $&n; *&n; * Copyright (c) 2000 ATecoM GmbH &n; *&n; * The author may be reached at ecd@atecom.com.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; * WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; * NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; * USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *******************************************************************/
macro_line|#ifndef _IDT77252_H
DECL|macro|_IDT77252_H
mdefine_line|#define _IDT77252_H 1
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/* Makros                                                                    */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|VPCI2VC
mdefine_line|#define VPCI2VC(card, vpi, vci) &bslash;&n;        (((vpi) &lt;&lt; card-&gt;vcibits) | ((vci) &amp; card-&gt;vcimask))
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   DEBUGGING definitions                                                   */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|DBG_TINY
mdefine_line|#define DBG_TINY&t;0x00000200
DECL|macro|DBG_GENERAL
mdefine_line|#define DBG_GENERAL     0x00000100
DECL|macro|DBG_XGENERAL
mdefine_line|#define DBG_XGENERAL    0x00000080
DECL|macro|DBG_INIT
mdefine_line|#define DBG_INIT        0x00000040
DECL|macro|DBG_DEINIT
mdefine_line|#define DBG_DEINIT      0x00000020
DECL|macro|DBG_INTERRUPT
mdefine_line|#define DBG_INTERRUPT   0x00000010
DECL|macro|DBG_OPEN_CONN
mdefine_line|#define DBG_OPEN_CONN   0x00000008
DECL|macro|DBG_CLOSE_CONN
mdefine_line|#define DBG_CLOSE_CONN  0x00000004
DECL|macro|DBG_RX_DATA
mdefine_line|#define DBG_RX_DATA     0x00000002
DECL|macro|DBG_TX_DATA
mdefine_line|#define DBG_TX_DATA     0x00000001
macro_line|#ifdef DEBUG
DECL|macro|CPRINTK
mdefine_line|#define CPRINTK(args...)   do { if (debug &amp; DBG_CLOSE_CONN) printk(args); } while(0)
DECL|macro|OPRINTK
mdefine_line|#define OPRINTK(args...)   do { if (debug &amp; DBG_OPEN_CONN)  printk(args); } while(0)
DECL|macro|IPRINTK
mdefine_line|#define IPRINTK(args...)   do { if (debug &amp; DBG_INIT)       printk(args); } while(0)
DECL|macro|INTPRINTK
mdefine_line|#define INTPRINTK(args...) do { if (debug &amp; DBG_INTERRUPT)  printk(args); } while(0)
DECL|macro|DIPRINTK
mdefine_line|#define DIPRINTK(args...)  do { if (debug &amp; DBG_DEINIT)     printk(args); } while(0)
DECL|macro|TXPRINTK
mdefine_line|#define TXPRINTK(args...)  do { if (debug &amp; DBG_TX_DATA)    printk(args); } while(0)
DECL|macro|RXPRINTK
mdefine_line|#define RXPRINTK(args...)  do { if (debug &amp; DBG_RX_DATA)    printk(args); } while(0)
DECL|macro|XPRINTK
mdefine_line|#define XPRINTK(args...)   do { if (debug &amp; DBG_XGENERAL)   printk(args); } while(0)
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(args...)   do { if (debug &amp; DBG_GENERAL)    printk(args); } while(0)
DECL|macro|NPRINTK
mdefine_line|#define NPRINTK(args...)   do { if (debug &amp; DBG_TINY)&t;    printk(args); } while(0)
macro_line|#else
DECL|macro|CPRINTK
mdefine_line|#define CPRINTK(args...)&t;do { } while(0)
DECL|macro|OPRINTK
mdefine_line|#define OPRINTK(args...)&t;do { } while(0)
DECL|macro|IPRINTK
mdefine_line|#define IPRINTK(args...)&t;do { } while(0)
DECL|macro|INTPRINTK
mdefine_line|#define INTPRINTK(args...)&t;do { } while(0)
DECL|macro|DIPRINTK
mdefine_line|#define DIPRINTK(args...)&t;do { } while(0)
DECL|macro|TXPRINTK
mdefine_line|#define TXPRINTK(args...)&t;do { } while(0)
DECL|macro|RXPRINTK
mdefine_line|#define RXPRINTK(args...)&t;do { } while(0)
DECL|macro|XPRINTK
mdefine_line|#define XPRINTK(args...)&t;do { } while(0)
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(args...)&t;do { } while(0)
DECL|macro|NPRINTK
mdefine_line|#define NPRINTK(args...)&t;do { } while(0)
macro_line|#endif
DECL|macro|SCHED_UBR0
mdefine_line|#define SCHED_UBR0&t;&t;0
DECL|macro|SCHED_UBR
mdefine_line|#define SCHED_UBR&t;&t;1
DECL|macro|SCHED_VBR
mdefine_line|#define SCHED_VBR&t;&t;2
DECL|macro|SCHED_ABR
mdefine_line|#define SCHED_ABR&t;&t;3
DECL|macro|SCHED_CBR
mdefine_line|#define SCHED_CBR&t;&t;4
DECL|macro|SCQFULL_TIMEOUT
mdefine_line|#define SCQFULL_TIMEOUT&t;&t;HZ
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   Free Buffer Queue Layout                                                */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_FB_SIZE_0
mdefine_line|#define SAR_FB_SIZE_0&t;&t;(2048 - 256)
DECL|macro|SAR_FB_SIZE_1
mdefine_line|#define SAR_FB_SIZE_1&t;&t;(4096 - 256)
DECL|macro|SAR_FB_SIZE_2
mdefine_line|#define SAR_FB_SIZE_2&t;&t;(8192 - 256)
DECL|macro|SAR_FB_SIZE_3
mdefine_line|#define SAR_FB_SIZE_3&t;&t;(16384 - 256)
DECL|macro|SAR_FBQ0_LOW
mdefine_line|#define SAR_FBQ0_LOW&t;&t;4
DECL|macro|SAR_FBQ0_HIGH
mdefine_line|#define SAR_FBQ0_HIGH&t;&t;8
DECL|macro|SAR_FBQ1_LOW
mdefine_line|#define SAR_FBQ1_LOW&t;&t;2
DECL|macro|SAR_FBQ1_HIGH
mdefine_line|#define SAR_FBQ1_HIGH&t;&t;4
DECL|macro|SAR_FBQ2_LOW
mdefine_line|#define SAR_FBQ2_LOW&t;&t;1
DECL|macro|SAR_FBQ2_HIGH
mdefine_line|#define SAR_FBQ2_HIGH&t;&t;2
DECL|macro|SAR_FBQ3_LOW
mdefine_line|#define SAR_FBQ3_LOW&t;&t;1
DECL|macro|SAR_FBQ3_HIGH
mdefine_line|#define SAR_FBQ3_HIGH&t;&t;2
macro_line|#if 0
mdefine_line|#define SAR_TST_RESERVED&t;44&t;/* Num TST reserved for UBR/ABR/VBR */
macro_line|#else
DECL|macro|SAR_TST_RESERVED
mdefine_line|#define SAR_TST_RESERVED&t;0&t;/* Num TST reserved for UBR/ABR/VBR */
macro_line|#endif
DECL|macro|TCT_CBR
mdefine_line|#define TCT_CBR&t;&t;&t;0x00000000
DECL|macro|TCT_UBR
mdefine_line|#define TCT_UBR&t;&t;&t;0x00000000
DECL|macro|TCT_VBR
mdefine_line|#define TCT_VBR&t;&t;&t;0x40000000
DECL|macro|TCT_ABR
mdefine_line|#define TCT_ABR&t;&t;&t;0x80000000
DECL|macro|TCT_TYPE
mdefine_line|#define TCT_TYPE&t;&t;0xc0000000
DECL|macro|TCT_RR
mdefine_line|#define TCT_RR&t;&t;&t;0x20000000
DECL|macro|TCT_LMCR
mdefine_line|#define TCT_LMCR&t;&t;0x08000000
DECL|macro|TCT_SCD_MASK
mdefine_line|#define TCT_SCD_MASK&t;&t;0x0007ffff
DECL|macro|TCT_TSIF
mdefine_line|#define TCT_TSIF&t;&t;0x00004000
DECL|macro|TCT_HALT
mdefine_line|#define TCT_HALT&t;&t;0x80000000
DECL|macro|TCT_IDLE
mdefine_line|#define TCT_IDLE&t;&t;0x40000000
DECL|macro|TCT_FLAG_UBR
mdefine_line|#define TCT_FLAG_UBR&t;&t;0x80000000
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   Structure describing an IDT77252                                        */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|struct|scqe
r_struct
id|scqe
(brace
DECL|member|word_1
id|u32
id|word_1
suffix:semicolon
DECL|member|word_2
id|u32
id|word_2
suffix:semicolon
DECL|member|word_3
id|u32
id|word_3
suffix:semicolon
DECL|member|word_4
id|u32
id|word_4
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SCQ_ENTRIES
mdefine_line|#define SCQ_ENTRIES&t;64
DECL|macro|SCQ_SIZE
mdefine_line|#define SCQ_SIZE&t;(SCQ_ENTRIES * sizeof(struct scqe))
DECL|macro|SCQ_MASK
mdefine_line|#define SCQ_MASK&t;(SCQ_SIZE - 1)
DECL|struct|scq_info
r_struct
id|scq_info
(brace
DECL|member|base
r_struct
id|scqe
op_star
id|base
suffix:semicolon
DECL|member|next
r_struct
id|scqe
op_star
id|next
suffix:semicolon
DECL|member|last
r_struct
id|scqe
op_star
id|last
suffix:semicolon
DECL|member|paddr
id|dma_addr_t
id|paddr
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|used
id|atomic_t
id|used
suffix:semicolon
DECL|member|trans_start
r_int
r_int
id|trans_start
suffix:semicolon
DECL|member|scd
r_int
r_int
id|scd
suffix:semicolon
DECL|member|skblock
id|spinlock_t
id|skblock
suffix:semicolon
DECL|member|transmit
r_struct
id|sk_buff_head
id|transmit
suffix:semicolon
DECL|member|pending
r_struct
id|sk_buff_head
id|pending
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rx_pool
r_struct
id|rx_pool
(brace
DECL|member|first
r_struct
id|sk_buff
op_star
id|first
suffix:semicolon
DECL|member|last
r_struct
id|sk_buff
op_star
op_star
id|last
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aal1
r_struct
id|aal1
(brace
DECL|member|total
r_int
r_int
id|total
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|data
r_struct
id|sk_buff
op_star
id|data
suffix:semicolon
DECL|member|sequence
r_int
r_char
id|sequence
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rate_estimator
r_struct
id|rate_estimator
(brace
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|interval
r_int
r_int
id|interval
suffix:semicolon
DECL|member|ewma_log
r_int
r_int
id|ewma_log
suffix:semicolon
DECL|member|cells
id|u64
id|cells
suffix:semicolon
DECL|member|last_cells
id|u64
id|last_cells
suffix:semicolon
DECL|member|avcps
r_int
id|avcps
suffix:semicolon
DECL|member|cps
id|u32
id|cps
suffix:semicolon
DECL|member|maxcps
id|u32
id|maxcps
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vc_map
r_struct
id|vc_map
(brace
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|VCF_TX
mdefine_line|#define VCF_TX&t;&t;0
DECL|macro|VCF_RX
mdefine_line|#define VCF_RX&t;&t;1
DECL|macro|VCF_IDLE
mdefine_line|#define VCF_IDLE&t;2
DECL|macro|VCF_RSV
mdefine_line|#define VCF_RSV&t;&t;3
DECL|member|class
r_int
r_int
r_class
suffix:semicolon
DECL|member|init_er
id|u8
id|init_er
suffix:semicolon
DECL|member|lacr
id|u8
id|lacr
suffix:semicolon
DECL|member|max_er
id|u8
id|max_er
suffix:semicolon
DECL|member|ntste
r_int
r_int
id|ntste
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|tx_vcc
r_struct
id|atm_vcc
op_star
id|tx_vcc
suffix:semicolon
DECL|member|rx_vcc
r_struct
id|atm_vcc
op_star
id|rx_vcc
suffix:semicolon
DECL|member|card
r_struct
id|idt77252_dev
op_star
id|card
suffix:semicolon
DECL|member|scq
r_struct
id|scq_info
op_star
id|scq
suffix:semicolon
multiline_comment|/* To keep track of the SCQ */
DECL|member|estimator
r_struct
id|rate_estimator
op_star
id|estimator
suffix:semicolon
DECL|member|scd_index
r_int
id|scd_index
suffix:semicolon
r_union
(brace
DECL|member|rx_pool
r_struct
id|rx_pool
id|rx_pool
suffix:semicolon
DECL|member|aal1
r_struct
id|aal1
id|aal1
suffix:semicolon
DECL|member|rcv
)brace
id|rcv
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   RCTE - Receive Connection Table Entry                                   */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|struct|rct_entry
r_struct
id|rct_entry
(brace
DECL|member|word_1
id|u32
id|word_1
suffix:semicolon
DECL|member|buffer_handle
id|u32
id|buffer_handle
suffix:semicolon
DECL|member|dma_address
id|u32
id|dma_address
suffix:semicolon
DECL|member|aal5_crc32
id|u32
id|aal5_crc32
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   RSQ - Receive Status Queue                                              */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_RSQE_VALID
mdefine_line|#define SAR_RSQE_VALID      0x80000000
DECL|macro|SAR_RSQE_IDLE
mdefine_line|#define SAR_RSQE_IDLE       0x40000000
DECL|macro|SAR_RSQE_BUF_MASK
mdefine_line|#define SAR_RSQE_BUF_MASK   0x00030000
DECL|macro|SAR_RSQE_BUF_ASGN
mdefine_line|#define SAR_RSQE_BUF_ASGN   0x00008000
DECL|macro|SAR_RSQE_NZGFC
mdefine_line|#define SAR_RSQE_NZGFC      0x00004000
DECL|macro|SAR_RSQE_EPDU
mdefine_line|#define SAR_RSQE_EPDU       0x00002000
DECL|macro|SAR_RSQE_BUF_CONT
mdefine_line|#define SAR_RSQE_BUF_CONT   0x00001000
DECL|macro|SAR_RSQE_EFCIE
mdefine_line|#define SAR_RSQE_EFCIE      0x00000800
DECL|macro|SAR_RSQE_CLP
mdefine_line|#define SAR_RSQE_CLP        0x00000400
DECL|macro|SAR_RSQE_CRC
mdefine_line|#define SAR_RSQE_CRC        0x00000200
DECL|macro|SAR_RSQE_CELLCNT
mdefine_line|#define SAR_RSQE_CELLCNT    0x000001FF
DECL|macro|RSQSIZE
mdefine_line|#define RSQSIZE            8192
DECL|macro|RSQ_NUM_ENTRIES
mdefine_line|#define RSQ_NUM_ENTRIES    (RSQSIZE / 16)
DECL|macro|RSQ_ALIGNMENT
mdefine_line|#define RSQ_ALIGNMENT      8192
DECL|struct|rsq_entry
r_struct
id|rsq_entry
(brace
DECL|member|word_1
id|u32
id|word_1
suffix:semicolon
DECL|member|word_2
id|u32
id|word_2
suffix:semicolon
DECL|member|word_3
id|u32
id|word_3
suffix:semicolon
DECL|member|word_4
id|u32
id|word_4
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rsq_info
r_struct
id|rsq_info
(brace
DECL|member|base
r_struct
id|rsq_entry
op_star
id|base
suffix:semicolon
DECL|member|next
r_struct
id|rsq_entry
op_star
id|next
suffix:semicolon
DECL|member|last
r_struct
id|rsq_entry
op_star
id|last
suffix:semicolon
DECL|member|paddr
id|dma_addr_t
id|paddr
suffix:semicolon
DECL|variable|rsq_info
)brace
id|rsq_info
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   TSQ - Transmit Status Queue                                             */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_TSQE_INVALID
mdefine_line|#define SAR_TSQE_INVALID         0x80000000
DECL|macro|SAR_TSQE_TIMESTAMP
mdefine_line|#define SAR_TSQE_TIMESTAMP       0x00FFFFFF
DECL|macro|SAR_TSQE_TYPE
mdefine_line|#define SAR_TSQE_TYPE&t;&t; 0x60000000
DECL|macro|SAR_TSQE_TYPE_TIMER
mdefine_line|#define SAR_TSQE_TYPE_TIMER      0x00000000
DECL|macro|SAR_TSQE_TYPE_TSR
mdefine_line|#define SAR_TSQE_TYPE_TSR        0x20000000
DECL|macro|SAR_TSQE_TYPE_IDLE
mdefine_line|#define SAR_TSQE_TYPE_IDLE       0x40000000
DECL|macro|SAR_TSQE_TYPE_TBD_COMP
mdefine_line|#define SAR_TSQE_TYPE_TBD_COMP   0x60000000
DECL|macro|SAR_TSQE_TAG
mdefine_line|#define SAR_TSQE_TAG(stat)&t;(((stat) &gt;&gt; 24) &amp; 0x1f)
DECL|macro|TSQSIZE
mdefine_line|#define TSQSIZE            8192
DECL|macro|TSQ_NUM_ENTRIES
mdefine_line|#define TSQ_NUM_ENTRIES    1024
DECL|macro|TSQ_ALIGNMENT
mdefine_line|#define TSQ_ALIGNMENT      8192
DECL|struct|tsq_entry
r_struct
id|tsq_entry
(brace
DECL|member|word_1
id|u32
id|word_1
suffix:semicolon
DECL|member|word_2
id|u32
id|word_2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tsq_info
r_struct
id|tsq_info
(brace
DECL|member|base
r_struct
id|tsq_entry
op_star
id|base
suffix:semicolon
DECL|member|next
r_struct
id|tsq_entry
op_star
id|next
suffix:semicolon
DECL|member|last
r_struct
id|tsq_entry
op_star
id|last
suffix:semicolon
DECL|member|paddr
id|dma_addr_t
id|paddr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tst_info
r_struct
id|tst_info
(brace
DECL|member|vc
r_struct
id|vc_map
op_star
id|vc
suffix:semicolon
DECL|member|tste
id|u32
id|tste
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TSTE_MASK
mdefine_line|#define TSTE_MASK&t;&t;0x601fffff
DECL|macro|TSTE_OPC_MASK
mdefine_line|#define TSTE_OPC_MASK&t;&t;0x60000000
DECL|macro|TSTE_OPC_NULL
mdefine_line|#define TSTE_OPC_NULL&t;&t;0x00000000
DECL|macro|TSTE_OPC_CBR
mdefine_line|#define TSTE_OPC_CBR&t;&t;0x20000000
DECL|macro|TSTE_OPC_VAR
mdefine_line|#define TSTE_OPC_VAR&t;&t;0x40000000
DECL|macro|TSTE_OPC_JMP
mdefine_line|#define TSTE_OPC_JMP&t;&t;0x60000000
DECL|macro|TSTE_PUSH_IDLE
mdefine_line|#define TSTE_PUSH_IDLE&t;&t;0x01000000
DECL|macro|TSTE_PUSH_ACTIVE
mdefine_line|#define TSTE_PUSH_ACTIVE&t;0x02000000
DECL|macro|TST_SWITCH_DONE
mdefine_line|#define TST_SWITCH_DONE&t;&t;0
DECL|macro|TST_SWITCH_PENDING
mdefine_line|#define TST_SWITCH_PENDING&t;1
DECL|macro|TST_SWITCH_WAIT
mdefine_line|#define TST_SWITCH_WAIT&t;&t;2
DECL|macro|FBQ_SHIFT
mdefine_line|#define FBQ_SHIFT&t;&t;9
DECL|macro|FBQ_SIZE
mdefine_line|#define FBQ_SIZE&t;&t;(1 &lt;&lt; FBQ_SHIFT)
DECL|macro|FBQ_MASK
mdefine_line|#define FBQ_MASK&t;&t;(FBQ_SIZE - 1)
DECL|struct|sb_pool
r_struct
id|sb_pool
(brace
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
(braket
id|FBQ_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|POOL_HANDLE
mdefine_line|#define POOL_HANDLE(queue, index)&t;(((queue + 1) &lt;&lt; 16) | (index))
DECL|macro|POOL_QUEUE
mdefine_line|#define POOL_QUEUE(handle)&t;&t;(((handle) &gt;&gt; 16) - 1)
DECL|macro|POOL_INDEX
mdefine_line|#define POOL_INDEX(handle)&t;&t;((handle) &amp; 0xffff)
DECL|struct|idt77252_dev
r_struct
id|idt77252_dev
(brace
DECL|member|tsq
r_struct
id|tsq_info
id|tsq
suffix:semicolon
multiline_comment|/* Transmit Status Queue */
DECL|member|rsq
r_struct
id|rsq_info
id|rsq
suffix:semicolon
multiline_comment|/* Receive Status Queue */
DECL|member|pcidev
r_struct
id|pci_dev
op_star
id|pcidev
suffix:semicolon
multiline_comment|/* PCI handle (desriptor) */
DECL|member|atmdev
r_struct
id|atm_dev
op_star
id|atmdev
suffix:semicolon
multiline_comment|/* ATM device desriptor */
DECL|member|membase
r_int
r_int
id|membase
suffix:semicolon
multiline_comment|/* SAR&squot;s memory base address */
DECL|member|srambase
r_int
r_int
id|srambase
suffix:semicolon
multiline_comment|/* SAR&squot;s sram  base address */
DECL|member|fbq
r_int
r_int
id|fbq
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* FBQ fill addresses */
DECL|member|mutex
r_struct
id|semaphore
id|mutex
suffix:semicolon
DECL|member|cmd_lock
id|spinlock_t
id|cmd_lock
suffix:semicolon
multiline_comment|/* for r/w utility/sram */
DECL|member|softstat
r_int
r_int
id|softstat
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* see blow */
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|tct_base
r_int
r_int
id|tct_base
suffix:semicolon
multiline_comment|/* TCT base address in SRAM */
DECL|member|rct_base
r_int
r_int
id|rct_base
suffix:semicolon
multiline_comment|/* RCT base address in SRAM */
DECL|member|rt_base
r_int
r_int
id|rt_base
suffix:semicolon
multiline_comment|/* Rate Table base in SRAM */
DECL|member|scd_base
r_int
r_int
id|scd_base
suffix:semicolon
multiline_comment|/* SCD base address in SRAM */
DECL|member|tst
r_int
r_int
id|tst
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* TST base address in SRAM */
DECL|member|abrst_base
r_int
r_int
id|abrst_base
suffix:semicolon
multiline_comment|/* ABRST base address in SRAM */
DECL|member|fifo_base
r_int
r_int
id|fifo_base
suffix:semicolon
multiline_comment|/* RX FIFO base in SRAM */
DECL|member|irqstat
r_int
r_int
id|irqstat
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sramsize
r_int
r_int
id|sramsize
suffix:semicolon
multiline_comment|/* SAR&squot;s sram size */
DECL|member|tct_size
r_int
r_int
id|tct_size
suffix:semicolon
multiline_comment|/* total TCT entries */
DECL|member|rct_size
r_int
r_int
id|rct_size
suffix:semicolon
multiline_comment|/* total RCT entries */
DECL|member|scd_size
r_int
r_int
id|scd_size
suffix:semicolon
multiline_comment|/* length of SCD */
DECL|member|tst_size
r_int
r_int
id|tst_size
suffix:semicolon
multiline_comment|/* total TST entries */
DECL|member|tst_free
r_int
r_int
id|tst_free
suffix:semicolon
multiline_comment|/* free TSTEs in TST */
DECL|member|abrst_size
r_int
r_int
id|abrst_size
suffix:semicolon
multiline_comment|/* size of ABRST in words */
DECL|member|fifo_size
r_int
r_int
id|fifo_size
suffix:semicolon
multiline_comment|/* size of RX FIFO in words */
DECL|member|vpibits
r_int
r_int
id|vpibits
suffix:semicolon
multiline_comment|/* Bits used for VPI index */
DECL|member|vcibits
r_int
r_int
id|vcibits
suffix:semicolon
multiline_comment|/* Bits used for VCI index */
DECL|member|vcimask
r_int
r_int
id|vcimask
suffix:semicolon
multiline_comment|/* Mask for VCI index */
DECL|member|utopia_pcr
r_int
r_int
id|utopia_pcr
suffix:semicolon
multiline_comment|/* Utopia Itf&squot;s Cell Rate */
DECL|member|link_pcr
r_int
r_int
id|link_pcr
suffix:semicolon
multiline_comment|/* PHY&squot;s Peek Cell Rate */
DECL|member|vcs
r_struct
id|vc_map
op_star
op_star
id|vcs
suffix:semicolon
multiline_comment|/* Open Connections */
DECL|member|scd2vc
r_struct
id|vc_map
op_star
op_star
id|scd2vc
suffix:semicolon
multiline_comment|/* SCD to Connection map */
DECL|member|soft_tst
r_struct
id|tst_info
op_star
id|soft_tst
suffix:semicolon
multiline_comment|/* TST to Connection map */
DECL|member|tst_index
r_int
r_int
id|tst_index
suffix:semicolon
multiline_comment|/* Current TST in use */
DECL|member|tst_timer
r_struct
id|timer_list
id|tst_timer
suffix:semicolon
DECL|member|tst_lock
id|spinlock_t
id|tst_lock
suffix:semicolon
DECL|member|tst_state
r_int
r_int
id|tst_state
suffix:semicolon
DECL|member|sbpool
r_struct
id|sb_pool
id|sbpool
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Pool of RX skbuffs */
DECL|member|raw_cell_head
r_struct
id|sk_buff
op_star
id|raw_cell_head
suffix:semicolon
multiline_comment|/* Pointer to raw cell queue */
DECL|member|raw_cell_hnd
id|u32
op_star
id|raw_cell_hnd
suffix:semicolon
multiline_comment|/* Pointer to RCQ handle */
DECL|member|raw_cell_paddr
id|dma_addr_t
id|raw_cell_paddr
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* SAR&squot;s ID */
DECL|member|revision
r_int
id|revision
suffix:semicolon
multiline_comment|/* chip revision */
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Device name */
DECL|member|next
r_struct
id|idt77252_dev
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* definition for flag field above */
DECL|macro|IDT77252_BIT_INIT
mdefine_line|#define IDT77252_BIT_INIT&t;&t;1
DECL|macro|IDT77252_BIT_INTERRUPT
mdefine_line|#define IDT77252_BIT_INTERRUPT&t;&t;2
DECL|macro|ATM_CELL_PAYLOAD
mdefine_line|#define ATM_CELL_PAYLOAD         48
DECL|macro|FREEBUF_ALIGNMENT
mdefine_line|#define FREEBUF_ALIGNMENT        16
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/* Makros                                                                    */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|ALIGN_ADDRESS
mdefine_line|#define ALIGN_ADDRESS(addr, alignment) &bslash;&n;        ((((u32)(addr)) + (((u32)(alignment))-1)) &amp; ~(((u32)(alignment)) - 1))
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   ABR SAR Network operation Register                                      */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_REG_DR0
mdefine_line|#define SAR_REG_DR0&t;(card-&gt;membase + 0x00)
DECL|macro|SAR_REG_DR1
mdefine_line|#define SAR_REG_DR1&t;(card-&gt;membase + 0x04)
DECL|macro|SAR_REG_DR2
mdefine_line|#define SAR_REG_DR2&t;(card-&gt;membase + 0x08)
DECL|macro|SAR_REG_DR3
mdefine_line|#define SAR_REG_DR3&t;(card-&gt;membase + 0x0C)
DECL|macro|SAR_REG_CMD
mdefine_line|#define SAR_REG_CMD&t;(card-&gt;membase + 0x10)
DECL|macro|SAR_REG_CFG
mdefine_line|#define SAR_REG_CFG&t;(card-&gt;membase + 0x14)
DECL|macro|SAR_REG_STAT
mdefine_line|#define SAR_REG_STAT&t;(card-&gt;membase + 0x18)
DECL|macro|SAR_REG_RSQB
mdefine_line|#define SAR_REG_RSQB&t;(card-&gt;membase + 0x1C)
DECL|macro|SAR_REG_RSQT
mdefine_line|#define SAR_REG_RSQT&t;(card-&gt;membase + 0x20)
DECL|macro|SAR_REG_RSQH
mdefine_line|#define SAR_REG_RSQH&t;(card-&gt;membase + 0x24)
DECL|macro|SAR_REG_CDC
mdefine_line|#define SAR_REG_CDC&t;(card-&gt;membase + 0x28)
DECL|macro|SAR_REG_VPEC
mdefine_line|#define SAR_REG_VPEC&t;(card-&gt;membase + 0x2C)
DECL|macro|SAR_REG_ICC
mdefine_line|#define SAR_REG_ICC&t;(card-&gt;membase + 0x30)
DECL|macro|SAR_REG_RAWCT
mdefine_line|#define SAR_REG_RAWCT&t;(card-&gt;membase + 0x34)
DECL|macro|SAR_REG_TMR
mdefine_line|#define SAR_REG_TMR&t;(card-&gt;membase + 0x38)
DECL|macro|SAR_REG_TSTB
mdefine_line|#define SAR_REG_TSTB&t;(card-&gt;membase + 0x3C)
DECL|macro|SAR_REG_TSQB
mdefine_line|#define SAR_REG_TSQB&t;(card-&gt;membase + 0x40)
DECL|macro|SAR_REG_TSQT
mdefine_line|#define SAR_REG_TSQT&t;(card-&gt;membase + 0x44)
DECL|macro|SAR_REG_TSQH
mdefine_line|#define SAR_REG_TSQH&t;(card-&gt;membase + 0x48)
DECL|macro|SAR_REG_GP
mdefine_line|#define SAR_REG_GP&t;(card-&gt;membase + 0x4C)
DECL|macro|SAR_REG_VPM
mdefine_line|#define SAR_REG_VPM&t;(card-&gt;membase + 0x50)
DECL|macro|SAR_REG_RXFD
mdefine_line|#define SAR_REG_RXFD&t;(card-&gt;membase + 0x54)
DECL|macro|SAR_REG_RXFT
mdefine_line|#define SAR_REG_RXFT&t;(card-&gt;membase + 0x58)
DECL|macro|SAR_REG_RXFH
mdefine_line|#define SAR_REG_RXFH&t;(card-&gt;membase + 0x5C)
DECL|macro|SAR_REG_RAWHND
mdefine_line|#define SAR_REG_RAWHND&t;(card-&gt;membase + 0x60)
DECL|macro|SAR_REG_RXSTAT
mdefine_line|#define SAR_REG_RXSTAT&t;(card-&gt;membase + 0x64)
DECL|macro|SAR_REG_ABRSTD
mdefine_line|#define SAR_REG_ABRSTD&t;(card-&gt;membase + 0x68)
DECL|macro|SAR_REG_ABRRQ
mdefine_line|#define SAR_REG_ABRRQ&t;(card-&gt;membase + 0x6C)
DECL|macro|SAR_REG_VBRRQ
mdefine_line|#define SAR_REG_VBRRQ&t;(card-&gt;membase + 0x70)
DECL|macro|SAR_REG_RTBL
mdefine_line|#define SAR_REG_RTBL&t;(card-&gt;membase + 0x74)
DECL|macro|SAR_REG_MDFCT
mdefine_line|#define SAR_REG_MDFCT&t;(card-&gt;membase + 0x78)
DECL|macro|SAR_REG_TXSTAT
mdefine_line|#define SAR_REG_TXSTAT&t;(card-&gt;membase + 0x7C)
DECL|macro|SAR_REG_TCMDQ
mdefine_line|#define SAR_REG_TCMDQ&t;(card-&gt;membase + 0x80)
DECL|macro|SAR_REG_IRCP
mdefine_line|#define SAR_REG_IRCP&t;(card-&gt;membase + 0x84)
DECL|macro|SAR_REG_FBQP0
mdefine_line|#define SAR_REG_FBQP0&t;(card-&gt;membase + 0x88)
DECL|macro|SAR_REG_FBQP1
mdefine_line|#define SAR_REG_FBQP1&t;(card-&gt;membase + 0x8C)
DECL|macro|SAR_REG_FBQP2
mdefine_line|#define SAR_REG_FBQP2&t;(card-&gt;membase + 0x90)
DECL|macro|SAR_REG_FBQP3
mdefine_line|#define SAR_REG_FBQP3&t;(card-&gt;membase + 0x94)
DECL|macro|SAR_REG_FBQS0
mdefine_line|#define SAR_REG_FBQS0&t;(card-&gt;membase + 0x98)
DECL|macro|SAR_REG_FBQS1
mdefine_line|#define SAR_REG_FBQS1&t;(card-&gt;membase + 0x9C)
DECL|macro|SAR_REG_FBQS2
mdefine_line|#define SAR_REG_FBQS2&t;(card-&gt;membase + 0xA0)
DECL|macro|SAR_REG_FBQS3
mdefine_line|#define SAR_REG_FBQS3&t;(card-&gt;membase + 0xA4)
DECL|macro|SAR_REG_FBQWP0
mdefine_line|#define SAR_REG_FBQWP0&t;(card-&gt;membase + 0xA8)
DECL|macro|SAR_REG_FBQWP1
mdefine_line|#define SAR_REG_FBQWP1&t;(card-&gt;membase + 0xAC)
DECL|macro|SAR_REG_FBQWP2
mdefine_line|#define SAR_REG_FBQWP2&t;(card-&gt;membase + 0xB0)
DECL|macro|SAR_REG_FBQWP3
mdefine_line|#define SAR_REG_FBQWP3&t;(card-&gt;membase + 0xB4)
DECL|macro|SAR_REG_NOW
mdefine_line|#define SAR_REG_NOW&t;(card-&gt;membase + 0xB8)
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   Commands                                                                */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_CMD_NO_OPERATION
mdefine_line|#define SAR_CMD_NO_OPERATION         0x00000000
DECL|macro|SAR_CMD_OPENCLOSE_CONNECTION
mdefine_line|#define SAR_CMD_OPENCLOSE_CONNECTION 0x20000000
DECL|macro|SAR_CMD_WRITE_SRAM
mdefine_line|#define SAR_CMD_WRITE_SRAM           0x40000000
DECL|macro|SAR_CMD_READ_SRAM
mdefine_line|#define SAR_CMD_READ_SRAM            0x50000000
DECL|macro|SAR_CMD_READ_UTILITY
mdefine_line|#define SAR_CMD_READ_UTILITY         0x80000000
DECL|macro|SAR_CMD_WRITE_UTILITY
mdefine_line|#define SAR_CMD_WRITE_UTILITY        0x90000000
DECL|macro|SAR_CMD_OPEN_CONNECTION
mdefine_line|#define SAR_CMD_OPEN_CONNECTION     (SAR_CMD_OPENCLOSE_CONNECTION | 0x00080000)
DECL|macro|SAR_CMD_CLOSE_CONNECTION
mdefine_line|#define SAR_CMD_CLOSE_CONNECTION     SAR_CMD_OPENCLOSE_CONNECTION
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   Configuration Register bits                                             */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_CFG_SWRST
mdefine_line|#define SAR_CFG_SWRST          0x80000000  /* Software reset                 */
DECL|macro|SAR_CFG_LOOP
mdefine_line|#define SAR_CFG_LOOP           0x40000000  /* Internal Loopback              */
DECL|macro|SAR_CFG_RXPTH
mdefine_line|#define SAR_CFG_RXPTH          0x20000000  /* Receive Path Enable            */
DECL|macro|SAR_CFG_IDLE_CLP
mdefine_line|#define SAR_CFG_IDLE_CLP       0x10000000  /* SAR set CLP Bits of Null Cells */
DECL|macro|SAR_CFG_TX_FIFO_SIZE_1
mdefine_line|#define SAR_CFG_TX_FIFO_SIZE_1 0x04000000  /* TX FIFO Size = 1 cell          */
DECL|macro|SAR_CFG_TX_FIFO_SIZE_2
mdefine_line|#define SAR_CFG_TX_FIFO_SIZE_2 0x08000000  /* TX FIFO Size = 2 cells         */
DECL|macro|SAR_CFG_TX_FIFO_SIZE_4
mdefine_line|#define SAR_CFG_TX_FIFO_SIZE_4 0x0C000000  /* TX FIFO Size = 4 cells         */
DECL|macro|SAR_CFG_TX_FIFO_SIZE_9
mdefine_line|#define SAR_CFG_TX_FIFO_SIZE_9 0x00000000  /* TX FIFO Size = 9 cells (full)  */
DECL|macro|SAR_CFG_NO_IDLE
mdefine_line|#define SAR_CFG_NO_IDLE        0x02000000  /* SAR sends no Null Cells        */
DECL|macro|SAR_CFG_RSVD1
mdefine_line|#define SAR_CFG_RSVD1          0x01000000  /* Reserved                       */
DECL|macro|SAR_CFG_RXSTQ_SIZE_2k
mdefine_line|#define SAR_CFG_RXSTQ_SIZE_2k  0x00000000  /* RX Stat Queue Size = 2048 byte */
DECL|macro|SAR_CFG_RXSTQ_SIZE_4k
mdefine_line|#define SAR_CFG_RXSTQ_SIZE_4k  0x00400000  /* RX Stat Queue Size = 4096 byte */
DECL|macro|SAR_CFG_RXSTQ_SIZE_8k
mdefine_line|#define SAR_CFG_RXSTQ_SIZE_8k  0x00800000  /* RX Stat Queue Size = 8192 byte */
DECL|macro|SAR_CFG_RXSTQ_SIZE_R
mdefine_line|#define SAR_CFG_RXSTQ_SIZE_R   0x00C00000  /* RX Stat Queue Size = reserved  */
DECL|macro|SAR_CFG_ICAPT
mdefine_line|#define SAR_CFG_ICAPT          0x00200000  /* accept Invalid Cells           */
DECL|macro|SAR_CFG_IGGFC
mdefine_line|#define SAR_CFG_IGGFC          0x00100000  /* Ignore GFC                     */
DECL|macro|SAR_CFG_VPVCS_0
mdefine_line|#define SAR_CFG_VPVCS_0        0x00000000  /* VPI/VCI Select bit range       */
DECL|macro|SAR_CFG_VPVCS_1
mdefine_line|#define SAR_CFG_VPVCS_1        0x00040000  /* VPI/VCI Select bit range       */
DECL|macro|SAR_CFG_VPVCS_2
mdefine_line|#define SAR_CFG_VPVCS_2        0x00080000  /* VPI/VCI Select bit range       */
DECL|macro|SAR_CFG_VPVCS_8
mdefine_line|#define SAR_CFG_VPVCS_8        0x000C0000  /* VPI/VCI Select bit range       */
DECL|macro|SAR_CFG_CNTBL_1k
mdefine_line|#define SAR_CFG_CNTBL_1k       0x00000000  /* Connection Table Size          */
DECL|macro|SAR_CFG_CNTBL_4k
mdefine_line|#define SAR_CFG_CNTBL_4k       0x00010000  /* Connection Table Size          */
DECL|macro|SAR_CFG_CNTBL_16k
mdefine_line|#define SAR_CFG_CNTBL_16k      0x00020000  /* Connection Table Size          */
DECL|macro|SAR_CFG_CNTBL_512
mdefine_line|#define SAR_CFG_CNTBL_512      0x00030000  /* Connection Table Size          */
DECL|macro|SAR_CFG_VPECA
mdefine_line|#define SAR_CFG_VPECA          0x00008000  /* VPI/VCI Error Cell Accept      */
DECL|macro|SAR_CFG_RXINT_NOINT
mdefine_line|#define SAR_CFG_RXINT_NOINT    0x00000000  /* No Interrupt on PDU received   */
DECL|macro|SAR_CFG_RXINT_NODELAY
mdefine_line|#define SAR_CFG_RXINT_NODELAY  0x00001000  /* Interrupt without delay to host*/
DECL|macro|SAR_CFG_RXINT_256US
mdefine_line|#define SAR_CFG_RXINT_256US    0x00002000  /* Interrupt with delay 256 usec  */
DECL|macro|SAR_CFG_RXINT_505US
mdefine_line|#define SAR_CFG_RXINT_505US    0x00003000  /* Interrupt with delay 505 usec  */
DECL|macro|SAR_CFG_RXINT_742US
mdefine_line|#define SAR_CFG_RXINT_742US    0x00004000  /* Interrupt with delay 742 usec  */
DECL|macro|SAR_CFG_RAWIE
mdefine_line|#define SAR_CFG_RAWIE          0x00000800  /* Raw Cell Queue Interrupt Enable*/
DECL|macro|SAR_CFG_RQFIE
mdefine_line|#define SAR_CFG_RQFIE          0x00000400  /* RSQ Almost Full Int Enable     */
DECL|macro|SAR_CFG_RSVD2
mdefine_line|#define SAR_CFG_RSVD2          0x00000200  /* Reserved                       */
DECL|macro|SAR_CFG_CACHE
mdefine_line|#define SAR_CFG_CACHE          0x00000100  /* DMA on Cache Line Boundary     */
DECL|macro|SAR_CFG_TMOIE
mdefine_line|#define SAR_CFG_TMOIE          0x00000080  /* Timer Roll Over Int Enable     */
DECL|macro|SAR_CFG_FBIE
mdefine_line|#define SAR_CFG_FBIE           0x00000040  /* Free Buffer Queue Int Enable   */
DECL|macro|SAR_CFG_TXEN
mdefine_line|#define SAR_CFG_TXEN           0x00000020  /* Transmit Operation Enable      */
DECL|macro|SAR_CFG_TXINT
mdefine_line|#define SAR_CFG_TXINT          0x00000010  /* Transmit status Int Enable     */
DECL|macro|SAR_CFG_TXUIE
mdefine_line|#define SAR_CFG_TXUIE          0x00000008  /* Transmit underrun Int Enable   */
DECL|macro|SAR_CFG_UMODE
mdefine_line|#define SAR_CFG_UMODE          0x00000004  /* Utopia Mode Select             */
DECL|macro|SAR_CFG_TXSFI
mdefine_line|#define SAR_CFG_TXSFI          0x00000002  /* Transmit status Full Int Enable*/
DECL|macro|SAR_CFG_PHYIE
mdefine_line|#define SAR_CFG_PHYIE          0x00000001  /* PHY Interrupt Enable           */
DECL|macro|SAR_CFG_TX_FIFO_SIZE_MASK
mdefine_line|#define SAR_CFG_TX_FIFO_SIZE_MASK 0x0C000000  /* TX FIFO Size Mask           */
DECL|macro|SAR_CFG_RXSTQSIZE_MASK
mdefine_line|#define SAR_CFG_RXSTQSIZE_MASK 0x00C00000
DECL|macro|SAR_CFG_CNTBL_MASK
mdefine_line|#define SAR_CFG_CNTBL_MASK     0x00030000
DECL|macro|SAR_CFG_RXINT_MASK
mdefine_line|#define SAR_CFG_RXINT_MASK     0x00007000
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   Status Register bits                                                    */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_STAT_FRAC_3
mdefine_line|#define SAR_STAT_FRAC_3     0xF0000000 /* Fraction of Free Buffer Queue 3 */
DECL|macro|SAR_STAT_FRAC_2
mdefine_line|#define SAR_STAT_FRAC_2     0x0F000000 /* Fraction of Free Buffer Queue 2 */
DECL|macro|SAR_STAT_FRAC_1
mdefine_line|#define SAR_STAT_FRAC_1     0x00F00000 /* Fraction of Free Buffer Queue 1 */
DECL|macro|SAR_STAT_FRAC_0
mdefine_line|#define SAR_STAT_FRAC_0     0x000F0000 /* Fraction of Free Buffer Queue 0 */
DECL|macro|SAR_STAT_TSIF
mdefine_line|#define SAR_STAT_TSIF       0x00008000 /* Transmit Status Indicator       */
DECL|macro|SAR_STAT_TXICP
mdefine_line|#define SAR_STAT_TXICP      0x00004000 /* Transmit Status Indicator       */
DECL|macro|SAR_STAT_RSVD1
mdefine_line|#define SAR_STAT_RSVD1      0x00002000 /* Reserved                        */
DECL|macro|SAR_STAT_TSQF
mdefine_line|#define SAR_STAT_TSQF       0x00001000 /* Transmit Status Queue full      */
DECL|macro|SAR_STAT_TMROF
mdefine_line|#define SAR_STAT_TMROF      0x00000800 /* Timer overflow                  */
DECL|macro|SAR_STAT_PHYI
mdefine_line|#define SAR_STAT_PHYI       0x00000400 /* PHY device Interrupt flag       */
DECL|macro|SAR_STAT_CMDBZ
mdefine_line|#define SAR_STAT_CMDBZ      0x00000200 /* ABR SAR Comand Busy Flag        */
DECL|macro|SAR_STAT_FBQ3A
mdefine_line|#define SAR_STAT_FBQ3A      0x00000100 /* Free Buffer Queue 3 Attention   */
DECL|macro|SAR_STAT_FBQ2A
mdefine_line|#define SAR_STAT_FBQ2A      0x00000080 /* Free Buffer Queue 2 Attention   */
DECL|macro|SAR_STAT_RSQF
mdefine_line|#define SAR_STAT_RSQF       0x00000040 /* Receive Status Queue full       */
DECL|macro|SAR_STAT_EPDU
mdefine_line|#define SAR_STAT_EPDU       0x00000020 /* End Of PDU Flag                 */
DECL|macro|SAR_STAT_RAWCF
mdefine_line|#define SAR_STAT_RAWCF      0x00000010 /* Raw Cell Flag                   */ 
DECL|macro|SAR_STAT_FBQ1A
mdefine_line|#define SAR_STAT_FBQ1A      0x00000008 /* Free Buffer Queue 1 Attention   */
DECL|macro|SAR_STAT_FBQ0A
mdefine_line|#define SAR_STAT_FBQ0A      0x00000004 /* Free Buffer Queue 0 Attention   */
DECL|macro|SAR_STAT_RSQAF
mdefine_line|#define SAR_STAT_RSQAF      0x00000002 /* Receive Status Queue almost full*/  
DECL|macro|SAR_STAT_RSVD2
mdefine_line|#define SAR_STAT_RSVD2      0x00000001 /* Reserved                        */
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   General Purpose Register bits                                           */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_GP_TXNCC_MASK
mdefine_line|#define SAR_GP_TXNCC_MASK   0xff000000  /* Transmit Negative Credit Count   */
DECL|macro|SAR_GP_EEDI
mdefine_line|#define SAR_GP_EEDI         0x00010000  /* EEPROM Data In                   */
DECL|macro|SAR_GP_BIGE
mdefine_line|#define SAR_GP_BIGE         0x00008000  /* Big Endian Operation             */
DECL|macro|SAR_GP_RM_NORMAL
mdefine_line|#define SAR_GP_RM_NORMAL    0x00000000  /* Normal handling of RM cells      */
DECL|macro|SAR_GP_RM_TO_RCQ
mdefine_line|#define SAR_GP_RM_TO_RCQ    0x00002000  /* put RM cells into Raw Cell Queue */
DECL|macro|SAR_GP_RM_RSVD
mdefine_line|#define SAR_GP_RM_RSVD      0x00004000  /* Reserved                         */
DECL|macro|SAR_GP_RM_INHIBIT
mdefine_line|#define SAR_GP_RM_INHIBIT   0x00006000  /* Inhibit update of Connection tab */
DECL|macro|SAR_GP_PHY_RESET
mdefine_line|#define SAR_GP_PHY_RESET    0x00000008  /* PHY Reset                        */
DECL|macro|SAR_GP_EESCLK
mdefine_line|#define SAR_GP_EESCLK&t;    0x00000004&t;/* EEPROM SCLK&t;&t;&t;    */
DECL|macro|SAR_GP_EECS
mdefine_line|#define SAR_GP_EECS&t;    0x00000002&t;/* EEPROM Chip Select&t;&t;    */
DECL|macro|SAR_GP_EEDO
mdefine_line|#define SAR_GP_EEDO&t;    0x00000001&t;/* EEPROM Data Out&t;&t;    */
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   SAR local SRAM layout for 128k work SRAM                                */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_SRAM_SCD_SIZE
mdefine_line|#define SAR_SRAM_SCD_SIZE        12
DECL|macro|SAR_SRAM_TCT_SIZE
mdefine_line|#define SAR_SRAM_TCT_SIZE         8
DECL|macro|SAR_SRAM_RCT_SIZE
mdefine_line|#define SAR_SRAM_RCT_SIZE         4
DECL|macro|SAR_SRAM_TCT_128_BASE
mdefine_line|#define SAR_SRAM_TCT_128_BASE    0x00000
DECL|macro|SAR_SRAM_TCT_128_TOP
mdefine_line|#define SAR_SRAM_TCT_128_TOP     0x01fff
DECL|macro|SAR_SRAM_RCT_128_BASE
mdefine_line|#define SAR_SRAM_RCT_128_BASE    0x02000
DECL|macro|SAR_SRAM_RCT_128_TOP
mdefine_line|#define SAR_SRAM_RCT_128_TOP     0x02fff
DECL|macro|SAR_SRAM_FB0_128_BASE
mdefine_line|#define SAR_SRAM_FB0_128_BASE    0x03000
DECL|macro|SAR_SRAM_FB0_128_TOP
mdefine_line|#define SAR_SRAM_FB0_128_TOP     0x033ff
DECL|macro|SAR_SRAM_FB1_128_BASE
mdefine_line|#define SAR_SRAM_FB1_128_BASE    0x03400
DECL|macro|SAR_SRAM_FB1_128_TOP
mdefine_line|#define SAR_SRAM_FB1_128_TOP     0x037ff
DECL|macro|SAR_SRAM_FB2_128_BASE
mdefine_line|#define SAR_SRAM_FB2_128_BASE    0x03800
DECL|macro|SAR_SRAM_FB2_128_TOP
mdefine_line|#define SAR_SRAM_FB2_128_TOP     0x03bff
DECL|macro|SAR_SRAM_FB3_128_BASE
mdefine_line|#define SAR_SRAM_FB3_128_BASE    0x03c00
DECL|macro|SAR_SRAM_FB3_128_TOP
mdefine_line|#define SAR_SRAM_FB3_128_TOP     0x03fff
DECL|macro|SAR_SRAM_SCD_128_BASE
mdefine_line|#define SAR_SRAM_SCD_128_BASE    0x04000
DECL|macro|SAR_SRAM_SCD_128_TOP
mdefine_line|#define SAR_SRAM_SCD_128_TOP     0x07fff
DECL|macro|SAR_SRAM_TST1_128_BASE
mdefine_line|#define SAR_SRAM_TST1_128_BASE   0x08000
DECL|macro|SAR_SRAM_TST1_128_TOP
mdefine_line|#define SAR_SRAM_TST1_128_TOP    0x0bfff
DECL|macro|SAR_SRAM_TST2_128_BASE
mdefine_line|#define SAR_SRAM_TST2_128_BASE   0x0c000
DECL|macro|SAR_SRAM_TST2_128_TOP
mdefine_line|#define SAR_SRAM_TST2_128_TOP    0x0ffff
DECL|macro|SAR_SRAM_ABRSTD_128_BASE
mdefine_line|#define SAR_SRAM_ABRSTD_128_BASE 0x10000
DECL|macro|SAR_SRAM_ABRSTD_128_TOP
mdefine_line|#define SAR_SRAM_ABRSTD_128_TOP  0x13fff
DECL|macro|SAR_SRAM_RT_128_BASE
mdefine_line|#define SAR_SRAM_RT_128_BASE     0x14000
DECL|macro|SAR_SRAM_RT_128_TOP
mdefine_line|#define SAR_SRAM_RT_128_TOP      0x15fff
DECL|macro|SAR_SRAM_FIFO_128_BASE
mdefine_line|#define SAR_SRAM_FIFO_128_BASE   0x18000
DECL|macro|SAR_SRAM_FIFO_128_TOP
mdefine_line|#define SAR_SRAM_FIFO_128_TOP    0x1ffff
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   SAR local SRAM layout for 32k work SRAM                                 */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_SRAM_TCT_32_BASE
mdefine_line|#define SAR_SRAM_TCT_32_BASE     0x00000
DECL|macro|SAR_SRAM_TCT_32_TOP
mdefine_line|#define SAR_SRAM_TCT_32_TOP      0x00fff
DECL|macro|SAR_SRAM_RCT_32_BASE
mdefine_line|#define SAR_SRAM_RCT_32_BASE     0x01000
DECL|macro|SAR_SRAM_RCT_32_TOP
mdefine_line|#define SAR_SRAM_RCT_32_TOP      0x017ff
DECL|macro|SAR_SRAM_FB0_32_BASE
mdefine_line|#define SAR_SRAM_FB0_32_BASE     0x01800
DECL|macro|SAR_SRAM_FB0_32_TOP
mdefine_line|#define SAR_SRAM_FB0_32_TOP      0x01bff
DECL|macro|SAR_SRAM_FB1_32_BASE
mdefine_line|#define SAR_SRAM_FB1_32_BASE     0x01c00
DECL|macro|SAR_SRAM_FB1_32_TOP
mdefine_line|#define SAR_SRAM_FB1_32_TOP      0x01fff
DECL|macro|SAR_SRAM_FB2_32_BASE
mdefine_line|#define SAR_SRAM_FB2_32_BASE     0x02000
DECL|macro|SAR_SRAM_FB2_32_TOP
mdefine_line|#define SAR_SRAM_FB2_32_TOP      0x023ff
DECL|macro|SAR_SRAM_FB3_32_BASE
mdefine_line|#define SAR_SRAM_FB3_32_BASE     0x02400
DECL|macro|SAR_SRAM_FB3_32_TOP
mdefine_line|#define SAR_SRAM_FB3_32_TOP      0x027ff
DECL|macro|SAR_SRAM_SCD_32_BASE
mdefine_line|#define SAR_SRAM_SCD_32_BASE     0x02800
DECL|macro|SAR_SRAM_SCD_32_TOP
mdefine_line|#define SAR_SRAM_SCD_32_TOP      0x03fff
DECL|macro|SAR_SRAM_TST1_32_BASE
mdefine_line|#define SAR_SRAM_TST1_32_BASE    0x04000
DECL|macro|SAR_SRAM_TST1_32_TOP
mdefine_line|#define SAR_SRAM_TST1_32_TOP     0x04fff
DECL|macro|SAR_SRAM_TST2_32_BASE
mdefine_line|#define SAR_SRAM_TST2_32_BASE    0x05000
DECL|macro|SAR_SRAM_TST2_32_TOP
mdefine_line|#define SAR_SRAM_TST2_32_TOP     0x05fff
DECL|macro|SAR_SRAM_ABRSTD_32_BASE
mdefine_line|#define SAR_SRAM_ABRSTD_32_BASE  0x06000
DECL|macro|SAR_SRAM_ABRSTD_32_TOP
mdefine_line|#define SAR_SRAM_ABRSTD_32_TOP   0x067ff
DECL|macro|SAR_SRAM_RT_32_BASE
mdefine_line|#define SAR_SRAM_RT_32_BASE      0x06800
DECL|macro|SAR_SRAM_RT_32_TOP
mdefine_line|#define SAR_SRAM_RT_32_TOP       0x06fff
DECL|macro|SAR_SRAM_FIFO_32_BASE
mdefine_line|#define SAR_SRAM_FIFO_32_BASE    0x07000
DECL|macro|SAR_SRAM_FIFO_32_TOP
mdefine_line|#define SAR_SRAM_FIFO_32_TOP     0x07fff
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   TSR - Transmit Status Request                                           */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_TSR_TYPE_TSR
mdefine_line|#define SAR_TSR_TYPE_TSR  0x80000000
DECL|macro|SAR_TSR_TYPE_TBD
mdefine_line|#define SAR_TSR_TYPE_TBD  0x00000000
DECL|macro|SAR_TSR_TSIF
mdefine_line|#define SAR_TSR_TSIF      0x20000000
DECL|macro|SAR_TSR_TAG_MASK
mdefine_line|#define SAR_TSR_TAG_MASK  0x01F00000
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   TBD - Transmit Buffer Descriptor                                        */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_TBD_EPDU
mdefine_line|#define SAR_TBD_EPDU      0x40000000
DECL|macro|SAR_TBD_TSIF
mdefine_line|#define SAR_TBD_TSIF      0x20000000
DECL|macro|SAR_TBD_OAM
mdefine_line|#define SAR_TBD_OAM       0x10000000
DECL|macro|SAR_TBD_AAL0
mdefine_line|#define SAR_TBD_AAL0      0x00000000
DECL|macro|SAR_TBD_AAL34
mdefine_line|#define SAR_TBD_AAL34     0x04000000
DECL|macro|SAR_TBD_AAL5
mdefine_line|#define SAR_TBD_AAL5      0x08000000
DECL|macro|SAR_TBD_GTSI
mdefine_line|#define SAR_TBD_GTSI      0x02000000
DECL|macro|SAR_TBD_TAG_MASK
mdefine_line|#define SAR_TBD_TAG_MASK  0x01F00000
DECL|macro|SAR_TBD_VPI_MASK
mdefine_line|#define SAR_TBD_VPI_MASK  0x0FF00000
DECL|macro|SAR_TBD_VCI_MASK
mdefine_line|#define SAR_TBD_VCI_MASK  0x000FFFF0
DECL|macro|SAR_TBD_VC_MASK
mdefine_line|#define SAR_TBD_VC_MASK   (SAR_TBD_VPI_MASK | SAR_TBD_VCI_MASK)
DECL|macro|SAR_TBD_VPI_SHIFT
mdefine_line|#define SAR_TBD_VPI_SHIFT 20
DECL|macro|SAR_TBD_VCI_SHIFT
mdefine_line|#define SAR_TBD_VCI_SHIFT 4
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   RXFD - Receive FIFO Descriptor                                          */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_RXFD_SIZE_MASK
mdefine_line|#define SAR_RXFD_SIZE_MASK     0x0F000000
DECL|macro|SAR_RXFD_SIZE_512
mdefine_line|#define SAR_RXFD_SIZE_512      0x00000000  /* 512 words                      */
DECL|macro|SAR_RXFD_SIZE_1K
mdefine_line|#define SAR_RXFD_SIZE_1K       0x01000000  /* 1k words                       */
DECL|macro|SAR_RXFD_SIZE_2K
mdefine_line|#define SAR_RXFD_SIZE_2K       0x02000000  /* 2k words                       */
DECL|macro|SAR_RXFD_SIZE_4K
mdefine_line|#define SAR_RXFD_SIZE_4K       0x03000000  /* 4k words                       */
DECL|macro|SAR_RXFD_SIZE_8K
mdefine_line|#define SAR_RXFD_SIZE_8K       0x04000000  /* 8k words                       */
DECL|macro|SAR_RXFD_SIZE_16K
mdefine_line|#define SAR_RXFD_SIZE_16K      0x05000000  /* 16k words                      */
DECL|macro|SAR_RXFD_SIZE_32K
mdefine_line|#define SAR_RXFD_SIZE_32K      0x06000000  /* 32k words                      */
DECL|macro|SAR_RXFD_SIZE_64K
mdefine_line|#define SAR_RXFD_SIZE_64K      0x07000000  /* 64k words                      */
DECL|macro|SAR_RXFD_SIZE_128K
mdefine_line|#define SAR_RXFD_SIZE_128K     0x08000000  /* 128k words                     */
DECL|macro|SAR_RXFD_SIZE_256K
mdefine_line|#define SAR_RXFD_SIZE_256K     0x09000000  /* 256k words                     */
DECL|macro|SAR_RXFD_ADDR_MASK
mdefine_line|#define SAR_RXFD_ADDR_MASK     0x001ffc00
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   ABRSTD - ABR + VBR Schedule Tables                                      */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_ABRSTD_SIZE_MASK
mdefine_line|#define SAR_ABRSTD_SIZE_MASK   0x07000000
DECL|macro|SAR_ABRSTD_SIZE_512
mdefine_line|#define SAR_ABRSTD_SIZE_512    0x00000000  /* 512 words                      */
DECL|macro|SAR_ABRSTD_SIZE_1K
mdefine_line|#define SAR_ABRSTD_SIZE_1K     0x01000000  /* 1k words                       */
DECL|macro|SAR_ABRSTD_SIZE_2K
mdefine_line|#define SAR_ABRSTD_SIZE_2K     0x02000000  /* 2k words                       */
DECL|macro|SAR_ABRSTD_SIZE_4K
mdefine_line|#define SAR_ABRSTD_SIZE_4K     0x03000000  /* 4k words                       */
DECL|macro|SAR_ABRSTD_SIZE_8K
mdefine_line|#define SAR_ABRSTD_SIZE_8K     0x04000000  /* 8k words                       */
DECL|macro|SAR_ABRSTD_SIZE_16K
mdefine_line|#define SAR_ABRSTD_SIZE_16K    0x05000000  /* 16k words                      */
DECL|macro|SAR_ABRSTD_ADDR_MASK
mdefine_line|#define SAR_ABRSTD_ADDR_MASK   0x001ffc00
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   RCTE - Receive Connection Table Entry                                   */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
DECL|macro|SAR_RCTE_IL_MASK
mdefine_line|#define SAR_RCTE_IL_MASK       0xE0000000  /* inactivity limit               */
DECL|macro|SAR_RCTE_IC_MASK
mdefine_line|#define SAR_RCTE_IC_MASK       0x1C000000  /* inactivity count               */
DECL|macro|SAR_RCTE_RSVD
mdefine_line|#define SAR_RCTE_RSVD          0x02000000  /* reserved                       */
DECL|macro|SAR_RCTE_LCD
mdefine_line|#define SAR_RCTE_LCD           0x01000000  /* last cell data                 */
DECL|macro|SAR_RCTE_CI_VC
mdefine_line|#define SAR_RCTE_CI_VC         0x00800000  /* EFCI in previous cell of VC    */
DECL|macro|SAR_RCTE_FBP_01
mdefine_line|#define SAR_RCTE_FBP_01        0x00000000  /* 1. cell-&gt;FBQ0, others-&gt;FBQ1    */
DECL|macro|SAR_RCTE_FBP_1
mdefine_line|#define SAR_RCTE_FBP_1         0x00200000  /* use FBQ 1 for all cells        */
DECL|macro|SAR_RCTE_FBP_2
mdefine_line|#define SAR_RCTE_FBP_2         0x00400000  /* use FBQ 2 for all cells        */
DECL|macro|SAR_RCTE_FBP_3
mdefine_line|#define SAR_RCTE_FBP_3         0x00600000  /* use FBQ 3 for all cells        */
DECL|macro|SAR_RCTE_NZ_GFC
mdefine_line|#define SAR_RCTE_NZ_GFC        0x00100000  /* non zero GFC in all cell of VC */
DECL|macro|SAR_RCTE_CONNECTOPEN
mdefine_line|#define SAR_RCTE_CONNECTOPEN   0x00080000  /* VC is open                     */
DECL|macro|SAR_RCTE_AAL_MASK
mdefine_line|#define SAR_RCTE_AAL_MASK      0x00070000  /* mask for AAL type field s.b.   */
DECL|macro|SAR_RCTE_RAWCELLINTEN
mdefine_line|#define SAR_RCTE_RAWCELLINTEN  0x00008000  /* raw cell interrupt enable      */
DECL|macro|SAR_RCTE_RXCONCELLADDR
mdefine_line|#define SAR_RCTE_RXCONCELLADDR 0x00004000  /* RX constant cell address       */
DECL|macro|SAR_RCTE_BUFFSTAT_MASK
mdefine_line|#define SAR_RCTE_BUFFSTAT_MASK 0x00003000  /* buffer status                  */
DECL|macro|SAR_RCTE_EFCI
mdefine_line|#define SAR_RCTE_EFCI          0x00000800  /* EFCI Congestion flag           */
DECL|macro|SAR_RCTE_CLP
mdefine_line|#define SAR_RCTE_CLP           0x00000400  /* Cell Loss Priority flag        */
DECL|macro|SAR_RCTE_CRC
mdefine_line|#define SAR_RCTE_CRC           0x00000200  /* Recieved CRC Error             */
DECL|macro|SAR_RCTE_CELLCNT_MASK
mdefine_line|#define SAR_RCTE_CELLCNT_MASK  0x000001FF  /* cell Count                     */
DECL|macro|SAR_RCTE_AAL0
mdefine_line|#define SAR_RCTE_AAL0          0x00000000  /* AAL types for ALL field        */
DECL|macro|SAR_RCTE_AAL34
mdefine_line|#define SAR_RCTE_AAL34         0x00010000
DECL|macro|SAR_RCTE_AAL5
mdefine_line|#define SAR_RCTE_AAL5          0x00020000
DECL|macro|SAR_RCTE_RCQ
mdefine_line|#define SAR_RCTE_RCQ           0x00030000
DECL|macro|SAR_RCTE_OAM
mdefine_line|#define SAR_RCTE_OAM           0x00040000
DECL|macro|TCMDQ_START
mdefine_line|#define TCMDQ_START&t;&t;0x01000000
DECL|macro|TCMDQ_LACR
mdefine_line|#define TCMDQ_LACR&t;&t;0x02000000
DECL|macro|TCMDQ_START_LACR
mdefine_line|#define TCMDQ_START_LACR&t;0x03000000
DECL|macro|TCMDQ_INIT_ER
mdefine_line|#define TCMDQ_INIT_ER&t;&t;0x04000000
DECL|macro|TCMDQ_HALT
mdefine_line|#define TCMDQ_HALT&t;&t;0x05000000
DECL|struct|idt77252_skb_prv
r_struct
id|idt77252_skb_prv
(brace
DECL|member|tbd
r_struct
id|scqe
id|tbd
suffix:semicolon
multiline_comment|/* Transmit Buffer Descriptor */
DECL|member|pool
id|u32
id|pool
suffix:semicolon
multiline_comment|/* sb_pool index */
DECL|member|paddr
id|dma_addr_t
id|paddr
suffix:semicolon
multiline_comment|/* DMA handle */
DECL|member|vaddr
r_void
op_star
id|vaddr
suffix:semicolon
multiline_comment|/* DMA virtual address */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* DMA buffer size */
DECL|member|next
r_struct
id|sk_buff
op_star
id|next
suffix:semicolon
multiline_comment|/* next PDU buffer */
)brace
suffix:semicolon
DECL|macro|IDT77252_PRV_TBD
mdefine_line|#define IDT77252_PRV_TBD(skb)&t;&bslash;&n;&t;(((struct idt77252_skb_prv *)(ATM_SKB(skb)+1))-&gt;tbd)
DECL|macro|IDT77252_PRV_POOL
mdefine_line|#define IDT77252_PRV_POOL(skb)&t;&bslash;&n;&t;(((struct idt77252_skb_prv *)(ATM_SKB(skb)+1))-&gt;pool)
DECL|macro|IDT77252_PRV_PADDR
mdefine_line|#define IDT77252_PRV_PADDR(skb)&t;&bslash;&n;&t;(((struct idt77252_skb_prv *)(ATM_SKB(skb)+1))-&gt;paddr)
DECL|macro|IDT77252_PRV_VADDR
mdefine_line|#define IDT77252_PRV_VADDR(skb)&t;&bslash;&n;&t;(((struct idt77252_skb_prv *)(ATM_SKB(skb)+1))-&gt;vaddr)
DECL|macro|IDT77252_PRV_SIZE
mdefine_line|#define IDT77252_PRV_SIZE(skb)&t;&bslash;&n;&t;(((struct idt77252_skb_prv *)(ATM_SKB(skb)+1))-&gt;size)
DECL|macro|IDT77252_PRV_NEXT
mdefine_line|#define IDT77252_PRV_NEXT(skb)&t;&bslash;&n;&t;(((struct idt77252_skb_prv *)(ATM_SKB(skb)+1))-&gt;next)
multiline_comment|/*****************************************************************************/
multiline_comment|/*                                                                           */
multiline_comment|/*   PCI related items                                                       */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
macro_line|#ifndef PCI_VENDOR_ID_IDT
DECL|macro|PCI_VENDOR_ID_IDT
mdefine_line|#define PCI_VENDOR_ID_IDT 0x111D
macro_line|#endif /* PCI_VENDOR_ID_IDT */
macro_line|#ifndef PCI_DEVICE_ID_IDT_IDT77252
DECL|macro|PCI_DEVICE_ID_IDT_IDT77252
mdefine_line|#define PCI_DEVICE_ID_IDT_IDT77252 0x0003
macro_line|#endif /* PCI_DEVICE_ID_IDT_IDT772052 */
macro_line|#endif /* !(_IDT77252_H) */
eof
