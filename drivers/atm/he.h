multiline_comment|/* $Id: he.h,v 1.4 2003/05/06 22:48:00 chas Exp $ */
multiline_comment|/*&n;&n;  he.h&n;&n;  ForeRunnerHE ATM Adapter driver for ATM on Linux&n;  Copyright (C) 1999-2001  Naval Research Laboratory&n;&n;  This library is free software; you can redistribute it and/or&n;  modify it under the terms of the GNU Lesser General Public&n;  License as published by the Free Software Foundation; either&n;  version 2.1 of the License, or (at your option) any later version.&n;&n;  This library is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;  Lesser General Public License for more details.&n;&n;  You should have received a copy of the GNU Lesser General Public&n;  License along with this library; if not, write to the Free Software&n;  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;&n;*/
multiline_comment|/*&n;&n;  he.h&n;&n;  ForeRunnerHE ATM Adapter driver for ATM on Linux&n;  Copyright (C) 1999-2000  Naval Research Laboratory&n;&n;  Permission to use, copy, modify and distribute this software and its&n;  documentation is hereby granted, provided that both the copyright&n;  notice and this permission notice appear in all copies of the software,&n;  derivative works or modified versions, and any portions thereof, and&n;  that both notices appear in supporting documentation.&n;&n;  NRL ALLOWS FREE USE OF THIS SOFTWARE IN ITS &quot;AS IS&quot; CONDITION AND&n;  DISCLAIMS ANY LIABILITY OF ANY KIND FOR ANY DAMAGES WHATSOEVER&n;  RESULTING FROM THE USE OF THIS SOFTWARE.&n;&n; */
macro_line|#ifndef _HE_H_
DECL|macro|_HE_H_
mdefine_line|#define _HE_H_
DECL|macro|DEV_LABEL
mdefine_line|#define DEV_LABEL       &quot;he&quot;
DECL|macro|CONFIG_DEFAULT_VCIBITS
mdefine_line|#define CONFIG_DEFAULT_VCIBITS&t;12
DECL|macro|CONFIG_DEFAULT_VPIBITS
mdefine_line|#define CONFIG_DEFAULT_VPIBITS&t;0
DECL|macro|CONFIG_IRQ_SIZE
mdefine_line|#define CONFIG_IRQ_SIZE&t;&t;128
DECL|macro|CONFIG_IRQ_THRESH
mdefine_line|#define CONFIG_IRQ_THRESH&t;(CONFIG_IRQ_SIZE/2)
DECL|macro|CONFIG_NUMTPDS
mdefine_line|#define CONFIG_NUMTPDS&t;&t;256
DECL|macro|CONFIG_TPDRQ_SIZE
mdefine_line|#define CONFIG_TPDRQ_SIZE&t;512
DECL|macro|TPDRQ_MASK
mdefine_line|#define TPDRQ_MASK(x)&t;&t;(((unsigned long)(x))&amp;((CONFIG_TPDRQ_SIZE&lt;&lt;3)-1))
DECL|macro|CONFIG_RBRQ_SIZE
mdefine_line|#define CONFIG_RBRQ_SIZE&t;512
DECL|macro|CONFIG_RBRQ_THRESH
mdefine_line|#define CONFIG_RBRQ_THRESH&t;400
DECL|macro|RBRQ_MASK
mdefine_line|#define RBRQ_MASK(x)&t;&t;(((unsigned long)(x))&amp;((CONFIG_RBRQ_SIZE&lt;&lt;3)-1))
DECL|macro|CONFIG_TBRQ_SIZE
mdefine_line|#define CONFIG_TBRQ_SIZE&t;512
DECL|macro|CONFIG_TBRQ_THRESH
mdefine_line|#define CONFIG_TBRQ_THRESH&t;400
DECL|macro|TBRQ_MASK
mdefine_line|#define TBRQ_MASK(x)&t;&t;(((unsigned long)(x))&amp;((CONFIG_TBRQ_SIZE&lt;&lt;2)-1))
DECL|macro|CONFIG_RBPL_SIZE
mdefine_line|#define CONFIG_RBPL_SIZE&t;512
DECL|macro|CONFIG_RBPL_THRESH
mdefine_line|#define CONFIG_RBPL_THRESH&t;64
DECL|macro|CONFIG_RBPL_BUFSIZE
mdefine_line|#define CONFIG_RBPL_BUFSIZE&t;4096
DECL|macro|RBPL_MASK
mdefine_line|#define RBPL_MASK(x)&t;&t;(((unsigned long)(x))&amp;((CONFIG_RBPL_SIZE&lt;&lt;3)-1))
DECL|macro|CONFIG_RBPS_SIZE
mdefine_line|#define CONFIG_RBPS_SIZE&t;1024
DECL|macro|CONFIG_RBPS_THRESH
mdefine_line|#define CONFIG_RBPS_THRESH&t;64
DECL|macro|CONFIG_RBPS_BUFSIZE
mdefine_line|#define CONFIG_RBPS_BUFSIZE&t;128
DECL|macro|RBPS_MASK
mdefine_line|#define RBPS_MASK(x)&t;&t;(((unsigned long)(x))&amp;((CONFIG_RBPS_SIZE&lt;&lt;3)-1))
multiline_comment|/* 5.1.3 initialize connection memory */
DECL|macro|CONFIG_RSRA
mdefine_line|#define CONFIG_RSRA&t;&t;0x00000
DECL|macro|CONFIG_RCMLBM
mdefine_line|#define CONFIG_RCMLBM&t;&t;0x08000
DECL|macro|CONFIG_RCMABR
mdefine_line|#define CONFIG_RCMABR&t;&t;0x0d800
DECL|macro|CONFIG_RSRB
mdefine_line|#define CONFIG_RSRB&t;&t;0x0e000
DECL|macro|CONFIG_TSRA
mdefine_line|#define CONFIG_TSRA&t;&t;0x00000
DECL|macro|CONFIG_TSRB
mdefine_line|#define CONFIG_TSRB&t;&t;0x08000
DECL|macro|CONFIG_TSRC
mdefine_line|#define CONFIG_TSRC&t;&t;0x0c000
DECL|macro|CONFIG_TSRD
mdefine_line|#define CONFIG_TSRD&t;&t;0x0e000
DECL|macro|CONFIG_TMABR
mdefine_line|#define CONFIG_TMABR&t;&t;0x0f000
DECL|macro|CONFIG_TPDBA
mdefine_line|#define CONFIG_TPDBA&t;&t;0x10000
DECL|macro|HE_MAXCIDBITS
mdefine_line|#define HE_MAXCIDBITS&t;&t;12
multiline_comment|/* 2.9.3.3 interrupt encodings */
DECL|struct|he_irq
r_struct
id|he_irq
(brace
DECL|member|isw
r_volatile
id|u32
id|isw
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IRQ_ALIGNMENT
mdefine_line|#define IRQ_ALIGNMENT&t;&t;0x1000
DECL|macro|NEXT_ENTRY
mdefine_line|#define NEXT_ENTRY(base, tail, mask) &bslash;&n;&t;&t;&t;&t;(((unsigned long)base)|(((unsigned long)(tail+1))&amp;mask))
DECL|macro|ITYPE_INVALID
mdefine_line|#define ITYPE_INVALID&t;&t;0xffffffff
DECL|macro|ITYPE_TBRQ_THRESH
mdefine_line|#define ITYPE_TBRQ_THRESH&t;(0&lt;&lt;3)
DECL|macro|ITYPE_TPD_COMPLETE
mdefine_line|#define ITYPE_TPD_COMPLETE&t;(1&lt;&lt;3)
DECL|macro|ITYPE_RBPS_THRESH
mdefine_line|#define ITYPE_RBPS_THRESH&t;(2&lt;&lt;3)
DECL|macro|ITYPE_RBPL_THRESH
mdefine_line|#define ITYPE_RBPL_THRESH&t;(3&lt;&lt;3)
DECL|macro|ITYPE_RBRQ_THRESH
mdefine_line|#define ITYPE_RBRQ_THRESH&t;(4&lt;&lt;3)
DECL|macro|ITYPE_RBRQ_TIMER
mdefine_line|#define ITYPE_RBRQ_TIMER&t;(5&lt;&lt;3)
DECL|macro|ITYPE_PHY
mdefine_line|#define ITYPE_PHY&t;&t;(6&lt;&lt;3)
DECL|macro|ITYPE_OTHER
mdefine_line|#define ITYPE_OTHER&t;&t;0x80
DECL|macro|ITYPE_PARITY
mdefine_line|#define ITYPE_PARITY&t;&t;0x81
DECL|macro|ITYPE_ABORT
mdefine_line|#define ITYPE_ABORT&t;&t;0x82
DECL|macro|ITYPE_GROUP
mdefine_line|#define ITYPE_GROUP(x)&t;&t;(x &amp; 0x7)
DECL|macro|ITYPE_TYPE
mdefine_line|#define ITYPE_TYPE(x)&t;&t;(x &amp; 0xf8)
DECL|macro|HE_NUM_GROUPS
mdefine_line|#define HE_NUM_GROUPS 8
multiline_comment|/* 2.1.4 transmit packet descriptor */
DECL|struct|he_tpd
r_struct
id|he_tpd
(brace
multiline_comment|/* read by the adapter */
DECL|member|status
r_volatile
id|u32
id|status
suffix:semicolon
DECL|member|reserved
r_volatile
id|u32
id|reserved
suffix:semicolon
DECL|macro|TPD_MAXIOV
mdefine_line|#define TPD_MAXIOV&t;3
r_struct
(brace
DECL|member|addr
DECL|member|len
id|u32
id|addr
comma
id|len
suffix:semicolon
DECL|member|iovec
)brace
id|iovec
(braket
id|TPD_MAXIOV
)braket
suffix:semicolon
DECL|macro|address0
mdefine_line|#define address0 iovec[0].addr
DECL|macro|length0
mdefine_line|#define length0 iovec[0].len
multiline_comment|/* linux-atm extensions */
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|vcc
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
macro_line|#ifdef USE_TPD_POOL
DECL|member|entry
r_struct
id|list_head
id|entry
suffix:semicolon
macro_line|#else
DECL|member|inuse
id|u32
id|inuse
suffix:semicolon
DECL|member|padding
r_char
id|padding
(braket
l_int|32
op_minus
r_sizeof
(paren
id|u32
)paren
op_minus
(paren
l_int|2
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
)braket
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|TPD_ALIGNMENT
mdefine_line|#define TPD_ALIGNMENT&t;64
DECL|macro|TPD_LEN_MASK
mdefine_line|#define TPD_LEN_MASK&t;0xffff
DECL|macro|TPD_ADDR_SHIFT
mdefine_line|#define TPD_ADDR_SHIFT  6
DECL|macro|TPD_MASK
mdefine_line|#define TPD_MASK&t;0xffffffc0
DECL|macro|TPD_ADDR
mdefine_line|#define TPD_ADDR(x)&t;((x) &amp; TPD_MASK)
DECL|macro|TPD_INDEX
mdefine_line|#define TPD_INDEX(x)&t;(TPD_ADDR(x) &gt;&gt; TPD_ADDR_SHIFT)
multiline_comment|/* table 2.3 transmit buffer return elements */
DECL|struct|he_tbrq
r_struct
id|he_tbrq
(brace
DECL|member|tbre
r_volatile
id|u32
id|tbre
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TBRQ_ALIGNMENT
mdefine_line|#define TBRQ_ALIGNMENT&t;CONFIG_TBRQ_SIZE
DECL|macro|TBRQ_TPD
mdefine_line|#define TBRQ_TPD(tbrq)&t;&t;((tbrq)-&gt;tbre &amp; 0xffffffc0)
DECL|macro|TBRQ_EOS
mdefine_line|#define TBRQ_EOS(tbrq)&t;&t;((tbrq)-&gt;tbre &amp; (1&lt;&lt;3))
DECL|macro|TBRQ_MULTIPLE
mdefine_line|#define TBRQ_MULTIPLE(tbrq)&t;((tbrq)-&gt;tbre &amp; (1))
multiline_comment|/* table 2.21 receive buffer return queue element field organization */
DECL|struct|he_rbrq
r_struct
id|he_rbrq
(brace
DECL|member|addr
r_volatile
id|u32
id|addr
suffix:semicolon
DECL|member|cidlen
r_volatile
id|u32
id|cidlen
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RBRQ_ALIGNMENT
mdefine_line|#define RBRQ_ALIGNMENT&t;CONFIG_RBRQ_SIZE
DECL|macro|RBRQ_ADDR
mdefine_line|#define RBRQ_ADDR(rbrq)&t;&t;((rbrq)-&gt;addr &amp; 0xffffffc0)
DECL|macro|RBRQ_CRC_ERR
mdefine_line|#define RBRQ_CRC_ERR(rbrq)&t;((rbrq)-&gt;addr &amp; (1&lt;&lt;5))
DECL|macro|RBRQ_LEN_ERR
mdefine_line|#define RBRQ_LEN_ERR(rbrq)&t;((rbrq)-&gt;addr &amp; (1&lt;&lt;4))
DECL|macro|RBRQ_END_PDU
mdefine_line|#define RBRQ_END_PDU(rbrq)&t;((rbrq)-&gt;addr &amp; (1&lt;&lt;3))
DECL|macro|RBRQ_AAL5_PROT
mdefine_line|#define RBRQ_AAL5_PROT(rbrq)&t;((rbrq)-&gt;addr &amp; (1&lt;&lt;2))
DECL|macro|RBRQ_CON_CLOSED
mdefine_line|#define RBRQ_CON_CLOSED(rbrq)&t;((rbrq)-&gt;addr &amp; (1&lt;&lt;1))
DECL|macro|RBRQ_HBUF_ERR
mdefine_line|#define RBRQ_HBUF_ERR(rbrq)&t;((rbrq)-&gt;addr &amp; 1)
DECL|macro|RBRQ_CID
mdefine_line|#define RBRQ_CID(rbrq)&t;&t;(((rbrq)-&gt;cidlen &gt;&gt; 16) &amp; 0x1fff)
DECL|macro|RBRQ_BUFLEN
mdefine_line|#define RBRQ_BUFLEN(rbrq)&t;((rbrq)-&gt;cidlen &amp; 0xffff)
multiline_comment|/* figure 2.3 transmit packet descriptor ready queue */
DECL|struct|he_tpdrq
r_struct
id|he_tpdrq
(brace
DECL|member|tpd
r_volatile
id|u32
id|tpd
suffix:semicolon
DECL|member|cid
r_volatile
id|u32
id|cid
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TPDRQ_ALIGNMENT
mdefine_line|#define TPDRQ_ALIGNMENT CONFIG_TPDRQ_SIZE
multiline_comment|/* table 2.30 host status page detail */
DECL|macro|HSP_ALIGNMENT
mdefine_line|#define HSP_ALIGNMENT&t;0x400&t;&t;/* must align on 1k boundary */
DECL|struct|he_hsp
r_struct
id|he_hsp
(brace
DECL|struct|he_hsp_entry
r_struct
id|he_hsp_entry
(brace
DECL|member|tbrq_tail
r_volatile
id|u32
id|tbrq_tail
suffix:semicolon
DECL|member|reserved1
r_volatile
id|u32
id|reserved1
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|rbrq_tail
r_volatile
id|u32
id|rbrq_tail
suffix:semicolon
DECL|member|reserved2
r_volatile
id|u32
id|reserved2
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|group
)brace
id|group
(braket
id|HE_NUM_GROUPS
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* figure 2.9 receive buffer pools */
DECL|struct|he_rbp
r_struct
id|he_rbp
(brace
DECL|member|phys
r_volatile
id|u32
id|phys
suffix:semicolon
DECL|member|status
r_volatile
id|u32
id|status
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* NOTE: it is suggested that virt be the virtual address of the host&n;   buffer.  on a 64-bit machine, this would not work.  Instead, we&n;   store the real virtual address in another list, and store an index&n;   (and buffer status) in the virt member.&n;*/
DECL|macro|RBP_INDEX_OFF
mdefine_line|#define RBP_INDEX_OFF&t;6
DECL|macro|RBP_INDEX
mdefine_line|#define RBP_INDEX(x)&t;(((long)(x) &gt;&gt; RBP_INDEX_OFF) &amp; 0xffff)
DECL|macro|RBP_LOANED
mdefine_line|#define RBP_LOANED&t;0x80000000
DECL|macro|RBP_SMALLBUF
mdefine_line|#define RBP_SMALLBUF&t;0x40000000
DECL|struct|he_virt
r_struct
id|he_virt
(brace
DECL|member|virt
r_void
op_star
id|virt
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RBPL_ALIGNMENT
mdefine_line|#define RBPL_ALIGNMENT CONFIG_RBPL_SIZE
DECL|macro|RBPS_ALIGNMENT
mdefine_line|#define RBPS_ALIGNMENT CONFIG_RBPS_SIZE
macro_line|#ifdef notyet
DECL|struct|he_group
r_struct
id|he_group
(brace
DECL|member|rpbs_size
DECL|member|rpbs_qsize
id|u32
id|rpbs_size
comma
id|rpbs_qsize
suffix:semicolon
DECL|member|rbps_ba
r_struct
id|he_rbp
id|rbps_ba
suffix:semicolon
DECL|member|rpbl_size
DECL|member|rpbl_qsize
id|u32
id|rpbl_size
comma
id|rpbl_qsize
suffix:semicolon
DECL|member|rbpl_ba
r_struct
id|he_rpb_entry
op_star
id|rbpl_ba
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|macro|HE_LOOKUP_VCC
mdefine_line|#define HE_LOOKUP_VCC(dev, cid) ((dev)-&gt;he_vcc_table[(cid)].vcc)
DECL|struct|he_vcc_table
r_struct
id|he_vcc_table
(brace
DECL|member|vcc
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|he_cs_stper
r_struct
id|he_cs_stper
(brace
DECL|member|pcr
r_int
id|pcr
suffix:semicolon
DECL|member|inuse
r_int
id|inuse
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HE_NUM_CS_STPER
mdefine_line|#define HE_NUM_CS_STPER&t;&t;16
DECL|struct|he_dev
r_struct
id|he_dev
(brace
DECL|member|number
r_int
r_int
id|number
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|membase
r_void
id|__iomem
op_star
id|membase
suffix:semicolon
DECL|member|prod_id
r_char
id|prod_id
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|mac_addr
r_char
id|mac_addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|media
r_int
id|media
suffix:semicolon
multiline_comment|/*  &n;&t;&t;&t;&t;&t; *  0x26 = HE155 MM &n;&t;&t;&t;&t;&t; *  0x27 = HE622 MM &n;&t;&t;&t;&t;&t; *  0x46 = HE155 SM &n;&t;&t;&t;&t;&t; *  0x47 = HE622 SM &n;&t;&t;&t;&t;&t; */
DECL|member|vcibits
DECL|member|vpibits
r_int
r_int
id|vcibits
comma
id|vpibits
suffix:semicolon
DECL|member|cells_per_row
r_int
r_int
id|cells_per_row
suffix:semicolon
DECL|member|bytes_per_row
r_int
r_int
id|bytes_per_row
suffix:semicolon
DECL|member|cells_per_lbuf
r_int
r_int
id|cells_per_lbuf
suffix:semicolon
DECL|member|r0_numrows
DECL|member|r0_startrow
DECL|member|r0_numbuffs
r_int
r_int
id|r0_numrows
comma
id|r0_startrow
comma
id|r0_numbuffs
suffix:semicolon
DECL|member|r1_numrows
DECL|member|r1_startrow
DECL|member|r1_numbuffs
r_int
r_int
id|r1_numrows
comma
id|r1_startrow
comma
id|r1_numbuffs
suffix:semicolon
DECL|member|tx_numrows
DECL|member|tx_startrow
DECL|member|tx_numbuffs
r_int
r_int
id|tx_numrows
comma
id|tx_startrow
comma
id|tx_numbuffs
suffix:semicolon
DECL|member|buffer_limit
r_int
r_int
id|buffer_limit
suffix:semicolon
DECL|member|he_vcc_table
r_struct
id|he_vcc_table
op_star
id|he_vcc_table
suffix:semicolon
macro_line|#ifdef notyet
DECL|member|group
r_struct
id|he_group
id|group
(braket
id|HE_NUM_GROUPS
)braket
suffix:semicolon
macro_line|#endif
DECL|member|cs_stper
r_struct
id|he_cs_stper
id|cs_stper
(braket
id|HE_NUM_CS_STPER
)braket
suffix:semicolon
DECL|member|total_bw
r_int
id|total_bw
suffix:semicolon
DECL|member|irq_phys
id|dma_addr_t
id|irq_phys
suffix:semicolon
DECL|member|irq_base
DECL|member|irq_head
DECL|member|irq_tail
r_struct
id|he_irq
op_star
id|irq_base
comma
op_star
id|irq_head
comma
op_star
id|irq_tail
suffix:semicolon
DECL|member|irq_tailoffset
r_volatile
r_int
op_star
id|irq_tailoffset
suffix:semicolon
DECL|member|irq_peak
r_int
id|irq_peak
suffix:semicolon
macro_line|#ifdef USE_TASKLET
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
macro_line|#endif
macro_line|#ifdef USE_TPD_POOL
DECL|member|tpd_pool
r_struct
id|pci_pool
op_star
id|tpd_pool
suffix:semicolon
DECL|member|outstanding_tpds
r_struct
id|list_head
id|outstanding_tpds
suffix:semicolon
macro_line|#else
DECL|member|tpd_head
DECL|member|tpd_base
DECL|member|tpd_end
r_struct
id|he_tpd
op_star
id|tpd_head
comma
op_star
id|tpd_base
comma
op_star
id|tpd_end
suffix:semicolon
DECL|member|tpd_base_phys
id|dma_addr_t
id|tpd_base_phys
suffix:semicolon
macro_line|#endif
DECL|member|tpdrq_phys
id|dma_addr_t
id|tpdrq_phys
suffix:semicolon
DECL|member|tpdrq_base
DECL|member|tpdrq_tail
DECL|member|tpdrq_head
r_struct
id|he_tpdrq
op_star
id|tpdrq_base
comma
op_star
id|tpdrq_tail
comma
op_star
id|tpdrq_head
suffix:semicolon
DECL|member|global_lock
id|spinlock_t
id|global_lock
suffix:semicolon
multiline_comment|/* 8.1.5 pci transaction ordering&n;&t;&t;&t;&t;&t;  error problem */
DECL|member|rbrq_phys
id|dma_addr_t
id|rbrq_phys
suffix:semicolon
DECL|member|rbrq_base
DECL|member|rbrq_head
r_struct
id|he_rbrq
op_star
id|rbrq_base
comma
op_star
id|rbrq_head
suffix:semicolon
DECL|member|rbrq_peak
r_int
id|rbrq_peak
suffix:semicolon
macro_line|#ifdef USE_RBPL_POOL
DECL|member|rbpl_pool
r_struct
id|pci_pool
op_star
id|rbpl_pool
suffix:semicolon
macro_line|#else
DECL|member|rbpl_pages
r_void
op_star
id|rbpl_pages
suffix:semicolon
DECL|member|rbpl_pages_phys
id|dma_addr_t
id|rbpl_pages_phys
suffix:semicolon
macro_line|#endif
DECL|member|rbpl_phys
id|dma_addr_t
id|rbpl_phys
suffix:semicolon
DECL|member|rbpl_base
DECL|member|rbpl_tail
r_struct
id|he_rbp
op_star
id|rbpl_base
comma
op_star
id|rbpl_tail
suffix:semicolon
DECL|member|rbpl_virt
r_struct
id|he_virt
op_star
id|rbpl_virt
suffix:semicolon
DECL|member|rbpl_peak
r_int
id|rbpl_peak
suffix:semicolon
macro_line|#ifdef USE_RBPS
macro_line|#ifdef USE_RBPS_POOL
DECL|member|rbps_pool
r_struct
id|pci_pool
op_star
id|rbps_pool
suffix:semicolon
macro_line|#else
DECL|member|rbps_pages
r_void
op_star
id|rbps_pages
suffix:semicolon
DECL|member|rbps_pages_phys
id|dma_addr_t
id|rbps_pages_phys
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|member|rbps_phys
id|dma_addr_t
id|rbps_phys
suffix:semicolon
DECL|member|rbps_base
DECL|member|rbps_tail
r_struct
id|he_rbp
op_star
id|rbps_base
comma
op_star
id|rbps_tail
suffix:semicolon
DECL|member|rbps_virt
r_struct
id|he_virt
op_star
id|rbps_virt
suffix:semicolon
DECL|member|rbps_peak
r_int
id|rbps_peak
suffix:semicolon
DECL|member|tbrq_phys
id|dma_addr_t
id|tbrq_phys
suffix:semicolon
DECL|member|tbrq_base
DECL|member|tbrq_head
r_struct
id|he_tbrq
op_star
id|tbrq_base
comma
op_star
id|tbrq_head
suffix:semicolon
DECL|member|tbrq_peak
r_int
id|tbrq_peak
suffix:semicolon
DECL|member|hsp_phys
id|dma_addr_t
id|hsp_phys
suffix:semicolon
DECL|member|hsp
r_struct
id|he_hsp
op_star
id|hsp
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|atm_dev
r_struct
id|atm_dev
op_star
id|atm_dev
suffix:semicolon
DECL|member|next
r_struct
id|he_dev
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|he_iovec
r_struct
id|he_iovec
(brace
DECL|member|iov_base
id|u32
id|iov_base
suffix:semicolon
DECL|member|iov_len
id|u32
id|iov_len
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HE_MAXIOV
mdefine_line|#define HE_MAXIOV 20
DECL|struct|he_vcc
r_struct
id|he_vcc
(brace
DECL|member|iov_head
r_struct
id|he_iovec
id|iov_head
(braket
id|HE_MAXIOV
)braket
suffix:semicolon
DECL|member|iov_tail
r_struct
id|he_iovec
op_star
id|iov_tail
suffix:semicolon
DECL|member|pdu_len
r_int
id|pdu_len
suffix:semicolon
DECL|member|rc_index
r_int
id|rc_index
suffix:semicolon
DECL|member|rx_waitq
id|wait_queue_head_t
id|rx_waitq
suffix:semicolon
DECL|member|tx_waitq
id|wait_queue_head_t
id|tx_waitq
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HE_VCC
mdefine_line|#define HE_VCC(vcc)&t;((struct he_vcc *)(vcc-&gt;dev_data))
DECL|macro|PCI_VENDOR_ID_FORE
mdefine_line|#define PCI_VENDOR_ID_FORE&t;0x1127
DECL|macro|PCI_DEVICE_ID_FORE_HE
mdefine_line|#define PCI_DEVICE_ID_FORE_HE&t;0x400
DECL|macro|HE_DMA_MASK
mdefine_line|#define HE_DMA_MASK&t;&t;0xffffffff
DECL|macro|GEN_CNTL_0
mdefine_line|#define GEN_CNTL_0&t;&t;&t;&t;0x40
DECL|macro|INT_PROC_ENBL
mdefine_line|#define  INT_PROC_ENBL&t;&t;(1&lt;&lt;25)
DECL|macro|SLAVE_ENDIAN_MODE
mdefine_line|#define  SLAVE_ENDIAN_MODE&t;(1&lt;&lt;16)
DECL|macro|MRL_ENB
mdefine_line|#define  MRL_ENB&t;&t;(1&lt;&lt;5)
DECL|macro|MRM_ENB
mdefine_line|#define  MRM_ENB&t;&t;(1&lt;&lt;4)
DECL|macro|INIT_ENB
mdefine_line|#define  INIT_ENB&t;&t;(1&lt;&lt;2)
DECL|macro|IGNORE_TIMEOUT
mdefine_line|#define  IGNORE_TIMEOUT&t;&t;(1&lt;&lt;1)
DECL|macro|ENBL_64
mdefine_line|#define  ENBL_64&t;&t;(1&lt;&lt;0)
DECL|macro|MIN_PCI_LATENCY
mdefine_line|#define MIN_PCI_LATENCY&t;&t;32&t;/* errata 8.1.3 */
DECL|macro|HE_DEV
mdefine_line|#define HE_DEV(dev) ((struct he_dev *) (dev)-&gt;dev_data)
DECL|macro|he_is622
mdefine_line|#define he_is622(dev)&t;((dev)-&gt;media &amp; 0x1)
DECL|macro|HE_REGMAP_SIZE
mdefine_line|#define HE_REGMAP_SIZE&t;0x100000
DECL|macro|RESET_CNTL
mdefine_line|#define RESET_CNTL&t;0x80000
DECL|macro|BOARD_RST_STATUS
mdefine_line|#define  BOARD_RST_STATUS&t;(1&lt;&lt;6)
DECL|macro|HOST_CNTL
mdefine_line|#define HOST_CNTL&t;0x80004
DECL|macro|PCI_BUS_SIZE64
mdefine_line|#define  PCI_BUS_SIZE64&t;&t;&t;(1&lt;&lt;27)
DECL|macro|DESC_RD_STATIC_64
mdefine_line|#define  DESC_RD_STATIC_64&t;&t;(1&lt;&lt;26)
DECL|macro|DATA_RD_STATIC_64
mdefine_line|#define  DATA_RD_STATIC_64&t;&t;(1&lt;&lt;25)
DECL|macro|DATA_WR_STATIC_64
mdefine_line|#define  DATA_WR_STATIC_64&t;&t;(1&lt;&lt;24)
DECL|macro|ID_CS
mdefine_line|#define  ID_CS&t;&t;&t;&t;(1&lt;&lt;12)
DECL|macro|ID_WREN
mdefine_line|#define  ID_WREN&t;&t;&t;(1&lt;&lt;11)
DECL|macro|ID_DOUT
mdefine_line|#define  ID_DOUT&t;&t;&t;(1&lt;&lt;10)
DECL|macro|ID_DOFFSET
mdefine_line|#define   ID_DOFFSET&t;&t;&t;10
DECL|macro|ID_DIN
mdefine_line|#define  ID_DIN&t;&t;&t;&t;(1&lt;&lt;9)
DECL|macro|ID_CLOCK
mdefine_line|#define  ID_CLOCK&t;&t;&t;(1&lt;&lt;8)
DECL|macro|QUICK_RD_RETRY
mdefine_line|#define  QUICK_RD_RETRY&t;&t;&t;(1&lt;&lt;7)
DECL|macro|QUICK_WR_RETRY
mdefine_line|#define  QUICK_WR_RETRY&t;&t;&t;(1&lt;&lt;6)
DECL|macro|OUTFF_ENB
mdefine_line|#define  OUTFF_ENB&t;&t;&t;(1&lt;&lt;5)
DECL|macro|CMDFF_ENB
mdefine_line|#define  CMDFF_ENB&t;&t;&t;(1&lt;&lt;4)
DECL|macro|PERR_INT_ENB
mdefine_line|#define  PERR_INT_ENB&t;&t;&t;(1&lt;&lt;2)
DECL|macro|IGNORE_INTR
mdefine_line|#define  IGNORE_INTR&t;&t;&t;(1&lt;&lt;0)
DECL|macro|LB_SWAP
mdefine_line|#define LB_SWAP&t;&t;0x80008
DECL|macro|SWAP_RNUM_MAX
mdefine_line|#define  SWAP_RNUM_MAX(x)&t;(x&lt;&lt;27)
DECL|macro|DATA_WR_SWAP
mdefine_line|#define  DATA_WR_SWAP&t;&t;(1&lt;&lt;20)
DECL|macro|DESC_RD_SWAP
mdefine_line|#define  DESC_RD_SWAP&t;&t;(1&lt;&lt;19)
DECL|macro|DATA_RD_SWAP
mdefine_line|#define  DATA_RD_SWAP&t;&t;(1&lt;&lt;18)
DECL|macro|INTR_SWAP
mdefine_line|#define  INTR_SWAP&t;&t;(1&lt;&lt;17)
DECL|macro|DESC_WR_SWAP
mdefine_line|#define  DESC_WR_SWAP&t;&t;(1&lt;&lt;16)
DECL|macro|SDRAM_INIT
mdefine_line|#define  SDRAM_INIT&t;&t;(1&lt;&lt;15)
DECL|macro|BIG_ENDIAN_HOST
mdefine_line|#define  BIG_ENDIAN_HOST&t;(1&lt;&lt;14)
DECL|macro|XFER_SIZE
mdefine_line|#define  XFER_SIZE&t;&t;(1&lt;&lt;7)
DECL|macro|LB_MEM_ADDR
mdefine_line|#define LB_MEM_ADDR&t;0x8000c
DECL|macro|LB_MEM_DATA
mdefine_line|#define LB_MEM_DATA&t;0x80010
DECL|macro|LB_MEM_ACCESS
mdefine_line|#define LB_MEM_ACCESS&t;0x80014
DECL|macro|LB_MEM_HNDSHK
mdefine_line|#define  LB_MEM_HNDSHK&t;&t;(1&lt;&lt;30)
DECL|macro|LM_MEM_WRITE
mdefine_line|#define  LM_MEM_WRITE&t;&t;(0x7)
DECL|macro|LM_MEM_READ
mdefine_line|#define  LM_MEM_READ&t;&t;(0x3)
DECL|macro|SDRAM_CTL
mdefine_line|#define SDRAM_CTL&t;0x80018
DECL|macro|LB_64_ENB
mdefine_line|#define  LB_64_ENB&t;&t;(1&lt;&lt;3)
DECL|macro|LB_TWR
mdefine_line|#define  LB_TWR&t;&t;&t;(1&lt;&lt;2)
DECL|macro|LB_TRP
mdefine_line|#define  LB_TRP&t;&t;&t;(1&lt;&lt;1)
DECL|macro|LB_TRAS
mdefine_line|#define  LB_TRAS&t;&t;(1&lt;&lt;0)
DECL|macro|INT_FIFO
mdefine_line|#define INT_FIFO&t;0x8001c
DECL|macro|INT_MASK_D
mdefine_line|#define  INT_MASK_D&t;&t;(1&lt;&lt;15)
DECL|macro|INT_MASK_C
mdefine_line|#define  INT_MASK_C&t;&t;(1&lt;&lt;14)
DECL|macro|INT_MASK_B
mdefine_line|#define  INT_MASK_B&t;&t;(1&lt;&lt;13)
DECL|macro|INT_MASK_A
mdefine_line|#define  INT_MASK_A&t;&t;(1&lt;&lt;12)
DECL|macro|INT_CLEAR_D
mdefine_line|#define  INT_CLEAR_D&t;&t;(1&lt;&lt;11)
DECL|macro|INT_CLEAR_C
mdefine_line|#define  INT_CLEAR_C&t;&t;(1&lt;&lt;10)
DECL|macro|INT_CLEAR_B
mdefine_line|#define  INT_CLEAR_B&t;&t;(1&lt;&lt;9)
DECL|macro|INT_CLEAR_A
mdefine_line|#define  INT_CLEAR_A&t;&t;(1&lt;&lt;8)
DECL|macro|ABORT_ADDR
mdefine_line|#define ABORT_ADDR&t;0x80020
DECL|macro|IRQ0_BASE
mdefine_line|#define IRQ0_BASE&t;0x80080
DECL|macro|IRQ_BASE
mdefine_line|#define  IRQ_BASE(x)&t;&t;(x&lt;&lt;12)
DECL|macro|IRQ_MASK
mdefine_line|#define  IRQ_MASK&t;&t;((CONFIG_IRQ_SIZE&lt;&lt;2)-1)&t;/* was 0x3ff */
DECL|macro|IRQ_TAIL
mdefine_line|#define  IRQ_TAIL(x)&t;&t;(((unsigned long)(x)) &amp; IRQ_MASK)
DECL|macro|IRQ0_HEAD
mdefine_line|#define IRQ0_HEAD&t;0x80084
DECL|macro|IRQ_SIZE
mdefine_line|#define  IRQ_SIZE(x)&t;&t;(x&lt;&lt;22)
DECL|macro|IRQ_THRESH
mdefine_line|#define  IRQ_THRESH(x)&t;&t;(x&lt;&lt;12)
DECL|macro|IRQ_HEAD
mdefine_line|#define  IRQ_HEAD(x)&t;&t;(x&lt;&lt;2)
multiline_comment|/* #define  IRQ_PENDING&t;&t;(1) &t;&t;conflict with linux/irq.h */
DECL|macro|IRQ0_CNTL
mdefine_line|#define IRQ0_CNTL&t;0x80088
DECL|macro|IRQ_ADDRSEL
mdefine_line|#define  IRQ_ADDRSEL(x)&t;&t;(x&lt;&lt;2)
DECL|macro|IRQ_INT_A
mdefine_line|#define  IRQ_INT_A&t;&t;(0&lt;&lt;2)
DECL|macro|IRQ_INT_B
mdefine_line|#define  IRQ_INT_B&t;&t;(1&lt;&lt;2)
DECL|macro|IRQ_INT_C
mdefine_line|#define  IRQ_INT_C&t;&t;(2&lt;&lt;2)
DECL|macro|IRQ_INT_D
mdefine_line|#define  IRQ_INT_D&t;&t;(3&lt;&lt;2)
DECL|macro|IRQ_TYPE_ADDR
mdefine_line|#define  IRQ_TYPE_ADDR&t;&t;0x1
DECL|macro|IRQ_TYPE_LINE
mdefine_line|#define  IRQ_TYPE_LINE&t;&t;0x0
DECL|macro|IRQ0_DATA
mdefine_line|#define IRQ0_DATA&t;0x8008c
DECL|macro|IRQ1_BASE
mdefine_line|#define IRQ1_BASE&t;0x80090
DECL|macro|IRQ1_HEAD
mdefine_line|#define IRQ1_HEAD&t;0x80094
DECL|macro|IRQ1_CNTL
mdefine_line|#define IRQ1_CNTL&t;0x80098
DECL|macro|IRQ1_DATA
mdefine_line|#define IRQ1_DATA&t;0x8009c
DECL|macro|IRQ2_BASE
mdefine_line|#define IRQ2_BASE&t;0x800a0
DECL|macro|IRQ2_HEAD
mdefine_line|#define IRQ2_HEAD&t;0x800a4
DECL|macro|IRQ2_CNTL
mdefine_line|#define IRQ2_CNTL&t;0x800a8
DECL|macro|IRQ2_DATA
mdefine_line|#define IRQ2_DATA&t;0x800ac
DECL|macro|IRQ3_BASE
mdefine_line|#define IRQ3_BASE&t;0x800b0
DECL|macro|IRQ3_HEAD
mdefine_line|#define IRQ3_HEAD&t;0x800b4
DECL|macro|IRQ3_CNTL
mdefine_line|#define IRQ3_CNTL&t;0x800b8
DECL|macro|IRQ3_DATA
mdefine_line|#define IRQ3_DATA&t;0x800bc
DECL|macro|GRP_10_MAP
mdefine_line|#define GRP_10_MAP&t;0x800c0
DECL|macro|GRP_32_MAP
mdefine_line|#define GRP_32_MAP&t;0x800c4
DECL|macro|GRP_54_MAP
mdefine_line|#define GRP_54_MAP&t;0x800c8
DECL|macro|GRP_76_MAP
mdefine_line|#define GRP_76_MAP&t;0x800cc
DECL|macro|G0_RBPS_S
mdefine_line|#define&t;G0_RBPS_S&t;0x80400
DECL|macro|G0_RBPS_T
mdefine_line|#define G0_RBPS_T&t;0x80404
DECL|macro|RBP_TAIL
mdefine_line|#define  RBP_TAIL(x)&t;&t;((x)&lt;&lt;3)
DECL|macro|RBP_MASK
mdefine_line|#define  RBP_MASK(x)&t;&t;((x)|0x1fff)
DECL|macro|G0_RBPS_QI
mdefine_line|#define G0_RBPS_QI&t;0x80408
DECL|macro|RBP_QSIZE
mdefine_line|#define  RBP_QSIZE(x)&t;&t;((x)&lt;&lt;14)
DECL|macro|RBP_INT_ENB
mdefine_line|#define  RBP_INT_ENB&t;&t;(1&lt;&lt;13)
DECL|macro|RBP_THRESH
mdefine_line|#define  RBP_THRESH(x)&t;&t;(x)
DECL|macro|G0_RBPS_BS
mdefine_line|#define G0_RBPS_BS&t;0x8040c
DECL|macro|G0_RBPL_S
mdefine_line|#define G0_RBPL_S&t;0x80410
DECL|macro|G0_RBPL_T
mdefine_line|#define G0_RBPL_T&t;0x80414
DECL|macro|G0_RBPL_QI
mdefine_line|#define G0_RBPL_QI&t;0x80418 
DECL|macro|G0_RBPL_BS
mdefine_line|#define G0_RBPL_BS&t;0x8041c
DECL|macro|G1_RBPS_S
mdefine_line|#define&t;G1_RBPS_S&t;0x80420
DECL|macro|G1_RBPS_T
mdefine_line|#define G1_RBPS_T&t;0x80424
DECL|macro|G1_RBPS_QI
mdefine_line|#define G1_RBPS_QI&t;0x80428
DECL|macro|G1_RBPS_BS
mdefine_line|#define G1_RBPS_BS&t;0x8042c
DECL|macro|G1_RBPL_S
mdefine_line|#define G1_RBPL_S&t;0x80430
DECL|macro|G1_RBPL_T
mdefine_line|#define G1_RBPL_T&t;0x80434
DECL|macro|G1_RBPL_QI
mdefine_line|#define G1_RBPL_QI&t;0x80438
DECL|macro|G1_RBPL_BS
mdefine_line|#define G1_RBPL_BS&t;0x8043c
DECL|macro|G2_RBPS_S
mdefine_line|#define&t;G2_RBPS_S&t;0x80440
DECL|macro|G2_RBPS_T
mdefine_line|#define G2_RBPS_T&t;0x80444
DECL|macro|G2_RBPS_QI
mdefine_line|#define G2_RBPS_QI&t;0x80448
DECL|macro|G2_RBPS_BS
mdefine_line|#define G2_RBPS_BS&t;0x8044c
DECL|macro|G2_RBPL_S
mdefine_line|#define G2_RBPL_S&t;0x80450
DECL|macro|G2_RBPL_T
mdefine_line|#define G2_RBPL_T&t;0x80454
DECL|macro|G2_RBPL_QI
mdefine_line|#define G2_RBPL_QI&t;0x80458
DECL|macro|G2_RBPL_BS
mdefine_line|#define G2_RBPL_BS&t;0x8045c
DECL|macro|G3_RBPS_S
mdefine_line|#define&t;G3_RBPS_S&t;0x80460
DECL|macro|G3_RBPS_T
mdefine_line|#define G3_RBPS_T&t;0x80464
DECL|macro|G3_RBPS_QI
mdefine_line|#define G3_RBPS_QI&t;0x80468
DECL|macro|G3_RBPS_BS
mdefine_line|#define G3_RBPS_BS&t;0x8046c
DECL|macro|G3_RBPL_S
mdefine_line|#define G3_RBPL_S&t;0x80470
DECL|macro|G3_RBPL_T
mdefine_line|#define G3_RBPL_T&t;0x80474
DECL|macro|G3_RBPL_QI
mdefine_line|#define G3_RBPL_QI&t;0x80478
DECL|macro|G3_RBPL_BS
mdefine_line|#define G3_RBPL_BS&t;0x8047c
DECL|macro|G4_RBPS_S
mdefine_line|#define&t;G4_RBPS_S&t;0x80480
DECL|macro|G4_RBPS_T
mdefine_line|#define G4_RBPS_T&t;0x80484
DECL|macro|G4_RBPS_QI
mdefine_line|#define G4_RBPS_QI&t;0x80488
DECL|macro|G4_RBPS_BS
mdefine_line|#define G4_RBPS_BS&t;0x8048c
DECL|macro|G4_RBPL_S
mdefine_line|#define G4_RBPL_S&t;0x80490
DECL|macro|G4_RBPL_T
mdefine_line|#define G4_RBPL_T&t;0x80494
DECL|macro|G4_RBPL_QI
mdefine_line|#define G4_RBPL_QI&t;0x80498
DECL|macro|G4_RBPL_BS
mdefine_line|#define G4_RBPL_BS&t;0x8049c
DECL|macro|G5_RBPS_S
mdefine_line|#define&t;G5_RBPS_S&t;0x804a0
DECL|macro|G5_RBPS_T
mdefine_line|#define G5_RBPS_T&t;0x804a4
DECL|macro|G5_RBPS_QI
mdefine_line|#define G5_RBPS_QI&t;0x804a8
DECL|macro|G5_RBPS_BS
mdefine_line|#define G5_RBPS_BS&t;0x804ac
DECL|macro|G5_RBPL_S
mdefine_line|#define G5_RBPL_S&t;0x804b0
DECL|macro|G5_RBPL_T
mdefine_line|#define G5_RBPL_T&t;0x804b4
DECL|macro|G5_RBPL_QI
mdefine_line|#define G5_RBPL_QI&t;0x804b8
DECL|macro|G5_RBPL_BS
mdefine_line|#define G5_RBPL_BS&t;0x804bc
DECL|macro|G6_RBPS_S
mdefine_line|#define&t;G6_RBPS_S&t;0x804c0
DECL|macro|G6_RBPS_T
mdefine_line|#define G6_RBPS_T&t;0x804c4
DECL|macro|G6_RBPS_QI
mdefine_line|#define G6_RBPS_QI&t;0x804c8
DECL|macro|G6_RBPS_BS
mdefine_line|#define G6_RBPS_BS&t;0x804cc
DECL|macro|G6_RBPL_S
mdefine_line|#define G6_RBPL_S&t;0x804d0
DECL|macro|G6_RBPL_T
mdefine_line|#define G6_RBPL_T&t;0x804d4
DECL|macro|G6_RBPL_QI
mdefine_line|#define G6_RBPL_QI&t;0x804d8
DECL|macro|G6_RBPL_BS
mdefine_line|#define G6_RBPL_BS&t;0x804dc
DECL|macro|G7_RBPS_S
mdefine_line|#define&t;G7_RBPS_S&t;0x804e0
DECL|macro|G7_RBPS_T
mdefine_line|#define G7_RBPS_T&t;0x804e4
DECL|macro|G7_RBPS_QI
mdefine_line|#define G7_RBPS_QI&t;0x804e8
DECL|macro|G7_RBPS_BS
mdefine_line|#define G7_RBPS_BS&t;0x804ec
DECL|macro|G7_RBPL_S
mdefine_line|#define G7_RBPL_S&t;0x804f0
DECL|macro|G7_RBPL_T
mdefine_line|#define G7_RBPL_T&t;0x804f4
DECL|macro|G7_RBPL_QI
mdefine_line|#define G7_RBPL_QI&t;0x804f8
DECL|macro|G7_RBPL_BS
mdefine_line|#define G7_RBPL_BS&t;0x804fc
DECL|macro|G0_RBRQ_ST
mdefine_line|#define G0_RBRQ_ST&t;0x80500
DECL|macro|G0_RBRQ_H
mdefine_line|#define G0_RBRQ_H&t;0x80504
DECL|macro|G0_RBRQ_Q
mdefine_line|#define G0_RBRQ_Q&t;0x80508
DECL|macro|RBRQ_THRESH
mdefine_line|#define  RBRQ_THRESH(x)&t;&t;((x)&lt;&lt;13)
DECL|macro|RBRQ_SIZE
mdefine_line|#define  RBRQ_SIZE(x)&t;&t;(x)
DECL|macro|G0_RBRQ_I
mdefine_line|#define G0_RBRQ_I&t;0x8050c
DECL|macro|RBRQ_TIME
mdefine_line|#define  RBRQ_TIME(x)&t;&t;((x)&lt;&lt;8)
DECL|macro|RBRQ_COUNT
mdefine_line|#define  RBRQ_COUNT(x)&t;&t;(x)
multiline_comment|/* fill in 1 ... 7 later */
DECL|macro|G0_TBRQ_B_T
mdefine_line|#define G0_TBRQ_B_T&t;0x80600
DECL|macro|G0_TBRQ_H
mdefine_line|#define G0_TBRQ_H&t;0x80604
DECL|macro|G0_TBRQ_S
mdefine_line|#define G0_TBRQ_S&t;0x80608
DECL|macro|G0_TBRQ_THRESH
mdefine_line|#define G0_TBRQ_THRESH&t;0x8060c
DECL|macro|TBRQ_THRESH
mdefine_line|#define  TBRQ_THRESH(x)&t;&t;(x)
multiline_comment|/* fill in 1 ... 7 later */
DECL|macro|RH_CONFIG
mdefine_line|#define RH_CONFIG&t;0x805c0
DECL|macro|PHY_INT_ENB
mdefine_line|#define  PHY_INT_ENB&t;(1&lt;&lt;10)
DECL|macro|OAM_GID
mdefine_line|#define  OAM_GID(x)&t;(x&lt;&lt;7)
DECL|macro|PTMR_PRE
mdefine_line|#define  PTMR_PRE(x)&t;(x)
DECL|macro|G0_INMQ_S
mdefine_line|#define G0_INMQ_S&t;0x80580
DECL|macro|G0_INMQ_L
mdefine_line|#define G0_INMQ_L&t;0x80584
DECL|macro|G1_INMQ_S
mdefine_line|#define G1_INMQ_S&t;0x80588
DECL|macro|G1_INMQ_L
mdefine_line|#define G1_INMQ_L&t;0x8058c
DECL|macro|G2_INMQ_S
mdefine_line|#define G2_INMQ_S&t;0x80590
DECL|macro|G2_INMQ_L
mdefine_line|#define G2_INMQ_L&t;0x80594
DECL|macro|G3_INMQ_S
mdefine_line|#define G3_INMQ_S&t;0x80598
DECL|macro|G3_INMQ_L
mdefine_line|#define G3_INMQ_L&t;0x8059c
DECL|macro|G4_INMQ_S
mdefine_line|#define G4_INMQ_S&t;0x805a0
DECL|macro|G4_INMQ_L
mdefine_line|#define G4_INMQ_L&t;0x805a4
DECL|macro|G5_INMQ_S
mdefine_line|#define G5_INMQ_S&t;0x805a8
DECL|macro|G5_INMQ_L
mdefine_line|#define G5_INMQ_L&t;0x805ac
DECL|macro|G6_INMQ_S
mdefine_line|#define G6_INMQ_S&t;0x805b0
DECL|macro|G6_INMQ_L
mdefine_line|#define G6_INMQ_L&t;0x805b4
DECL|macro|G7_INMQ_S
mdefine_line|#define G7_INMQ_S&t;0x805b8
DECL|macro|G7_INMQ_L
mdefine_line|#define G7_INMQ_L&t;0x805bc
DECL|macro|TPDRQ_B_H
mdefine_line|#define TPDRQ_B_H&t;0x80680
DECL|macro|TPDRQ_T
mdefine_line|#define TPDRQ_T&t;&t;0x80684
DECL|macro|TPDRQ_S
mdefine_line|#define TPDRQ_S&t;&t;0x80688
DECL|macro|UBUFF_BA
mdefine_line|#define UBUFF_BA&t;0x8068c
DECL|macro|RLBF0_H
mdefine_line|#define RLBF0_H&t;&t;0x806c0
DECL|macro|RLBF0_T
mdefine_line|#define RLBF0_T&t;&t;0x806c4
DECL|macro|RLBF1_H
mdefine_line|#define RLBF1_H&t;&t;0x806c8
DECL|macro|RLBF1_T
mdefine_line|#define RLBF1_T&t;&t;0x806cc
DECL|macro|RLBC_H
mdefine_line|#define RLBC_H&t;&t;0x806d0
DECL|macro|RLBC_T
mdefine_line|#define RLBC_T&t;&t;0x806d4
DECL|macro|RLBC_H2
mdefine_line|#define RLBC_H2&t;&t;0x806d8
DECL|macro|TLBF_H
mdefine_line|#define TLBF_H&t;&t;0x806e0
DECL|macro|TLBF_T
mdefine_line|#define TLBF_T&t;&t;0x806e4
DECL|macro|RLBF0_C
mdefine_line|#define RLBF0_C&t;&t;0x806e8
DECL|macro|RLBF1_C
mdefine_line|#define RLBF1_C&t;&t;0x806ec
DECL|macro|RXTHRSH
mdefine_line|#define RXTHRSH&t;&t;0x806f0
DECL|macro|LITHRSH
mdefine_line|#define LITHRSH&t;&t;0x806f4
DECL|macro|LBARB
mdefine_line|#define LBARB&t;&t;0x80700
DECL|macro|SLICE_X
mdefine_line|#define  SLICE_X(x)&t;&t; (x&lt;&lt;28)
DECL|macro|ARB_RNUM_MAX
mdefine_line|#define  ARB_RNUM_MAX(x)&t; (x&lt;&lt;23)
DECL|macro|TH_PRTY
mdefine_line|#define  TH_PRTY(x)&t;&t; (x&lt;&lt;21)
DECL|macro|RH_PRTY
mdefine_line|#define  RH_PRTY(x)&t;&t; (x&lt;&lt;19)
DECL|macro|TL_PRTY
mdefine_line|#define  TL_PRTY(x)&t;&t; (x&lt;&lt;17)
DECL|macro|RL_PRTY
mdefine_line|#define  RL_PRTY(x)&t;&t; (x&lt;&lt;15)
DECL|macro|BUS_MULTI
mdefine_line|#define  BUS_MULTI(x)&t;&t; (x&lt;&lt;8)
DECL|macro|NET_PREF
mdefine_line|#define  NET_PREF(x)&t;&t; (x)
DECL|macro|SDRAMCON
mdefine_line|#define SDRAMCON&t;0x80704
DECL|macro|BANK_ON
mdefine_line|#define&t; BANK_ON&t;&t;(1&lt;&lt;14)
DECL|macro|WIDE_DATA
mdefine_line|#define&t; WIDE_DATA&t;&t;(1&lt;&lt;13)
DECL|macro|TWR_WAIT
mdefine_line|#define&t; TWR_WAIT&t;&t;(1&lt;&lt;12)
DECL|macro|TRP_WAIT
mdefine_line|#define&t; TRP_WAIT&t;&t;(1&lt;&lt;11)
DECL|macro|TRAS_WAIT
mdefine_line|#define&t; TRAS_WAIT&t;&t;(1&lt;&lt;10)
DECL|macro|REF_RATE
mdefine_line|#define&t; REF_RATE(x)&t;&t;(x)
DECL|macro|LBSTAT
mdefine_line|#define LBSTAT&t;&t;0x80708
DECL|macro|RCC_STAT
mdefine_line|#define RCC_STAT&t;0x8070c
DECL|macro|RCC_BUSY
mdefine_line|#define  RCC_BUSY&t;&t;(1)
DECL|macro|TCMCONFIG
mdefine_line|#define TCMCONFIG&t;0x80740
DECL|macro|TM_DESL2
mdefine_line|#define  TM_DESL2&t;&t;(1&lt;&lt;10)
DECL|macro|TM_BANK_WAIT
mdefine_line|#define&t; TM_BANK_WAIT(x)&t;(x&lt;&lt;6)
DECL|macro|TM_ADD_BANK4
mdefine_line|#define&t; TM_ADD_BANK4(x)&t;(x&lt;&lt;4)
DECL|macro|TM_PAR_CHECK
mdefine_line|#define  TM_PAR_CHECK(x)&t;(x&lt;&lt;3)
DECL|macro|TM_RW_WAIT
mdefine_line|#define  TM_RW_WAIT(x)&t;&t;(x&lt;&lt;2)
DECL|macro|TM_SRAM_TYPE
mdefine_line|#define  TM_SRAM_TYPE(x)&t;(x)
DECL|macro|TSRB_BA
mdefine_line|#define TSRB_BA&t;&t;0x80744&t;
DECL|macro|TSRC_BA
mdefine_line|#define TSRC_BA&t;&t;0x80748&t;
DECL|macro|TMABR_BA
mdefine_line|#define TMABR_BA&t;0x8074c&t;
DECL|macro|TPD_BA
mdefine_line|#define TPD_BA&t;&t;0x80750&t;
DECL|macro|TSRD_BA
mdefine_line|#define TSRD_BA&t;&t;0x80758&t;
DECL|macro|TX_CONFIG
mdefine_line|#define TX_CONFIG&t;0x80760
DECL|macro|DRF_THRESH
mdefine_line|#define  DRF_THRESH(x)&t;&t;(x&lt;&lt;22)
DECL|macro|TX_UT_MODE
mdefine_line|#define  TX_UT_MODE(x)&t;&t;(x&lt;&lt;21)
DECL|macro|TX_VCI_MASK
mdefine_line|#define  TX_VCI_MASK(x)&t;&t;(x&lt;&lt;17)
DECL|macro|LBFREE_CNT
mdefine_line|#define  LBFREE_CNT(x)&t;&t;(x)
DECL|macro|TXAAL5_PROTO
mdefine_line|#define TXAAL5_PROTO&t;0x80764
DECL|macro|CPCS_UU
mdefine_line|#define  CPCS_UU(x)&t;&t;(x&lt;&lt;8)
DECL|macro|CPI
mdefine_line|#define  CPI(x)&t;&t;&t;(x)
DECL|macro|RCMCONFIG
mdefine_line|#define RCMCONFIG&t;0x80780
DECL|macro|RM_DESL2
mdefine_line|#define  RM_DESL2(x)&t;&t;(x&lt;&lt;10)
DECL|macro|RM_BANK_WAIT
mdefine_line|#define  RM_BANK_WAIT(x)&t;(x&lt;&lt;6)
DECL|macro|RM_ADD_BANK
mdefine_line|#define  RM_ADD_BANK(x)&t;&t;(x&lt;&lt;4)
DECL|macro|RM_PAR_CHECK
mdefine_line|#define  RM_PAR_CHECK(x)&t;(x&lt;&lt;3)
DECL|macro|RM_RW_WAIT
mdefine_line|#define  RM_RW_WAIT(x)&t;&t;(x&lt;&lt;2)
DECL|macro|RM_SRAM_TYPE
mdefine_line|#define  RM_SRAM_TYPE(x)&t;(x)
DECL|macro|RCMRSRB_BA
mdefine_line|#define RCMRSRB_BA&t;0x80784
DECL|macro|RCMLBM_BA
mdefine_line|#define RCMLBM_BA&t;0x80788
DECL|macro|RCMABR_BA
mdefine_line|#define RCMABR_BA&t;0x8078c
DECL|macro|RC_CONFIG
mdefine_line|#define RC_CONFIG&t;0x807c0
DECL|macro|UT_RD_DELAY
mdefine_line|#define  UT_RD_DELAY(x)&t;&t;(x&lt;&lt;11)
DECL|macro|WRAP_MODE
mdefine_line|#define  WRAP_MODE(x)&t;&t;(x&lt;&lt;10)
DECL|macro|RC_UT_MODE
mdefine_line|#define  RC_UT_MODE(x)&t;&t;(x&lt;&lt;9)
DECL|macro|RX_ENABLE
mdefine_line|#define  RX_ENABLE&t;&t;(1&lt;&lt;8)
DECL|macro|RX_VALVP
mdefine_line|#define  RX_VALVP(x)&t;&t;(x&lt;&lt;4)
DECL|macro|RX_VALVC
mdefine_line|#define  RX_VALVC(x)&t;&t;(x)
DECL|macro|MCC
mdefine_line|#define MCC&t;&t;0x807c4
DECL|macro|OEC
mdefine_line|#define OEC&t;&t;0x807c8
DECL|macro|DCC
mdefine_line|#define DCC&t;&t;0x807cc
DECL|macro|CEC
mdefine_line|#define CEC&t;&t;0x807d0
DECL|macro|HSP_BA
mdefine_line|#define HSP_BA&t;&t;0x807f0
DECL|macro|LB_CONFIG
mdefine_line|#define LB_CONFIG&t;0x807f4
DECL|macro|LB_SIZE
mdefine_line|#define  LB_SIZE(x)&t;&t;(x)
DECL|macro|CON_DAT
mdefine_line|#define CON_DAT&t;&t;0x807f8
DECL|macro|CON_CTL
mdefine_line|#define CON_CTL&t;&t;0x807fc
DECL|macro|CON_CTL_MBOX
mdefine_line|#define  CON_CTL_MBOX&t;&t;(2&lt;&lt;30)
DECL|macro|CON_CTL_TCM
mdefine_line|#define  CON_CTL_TCM&t;&t;(1&lt;&lt;30)
DECL|macro|CON_CTL_RCM
mdefine_line|#define  CON_CTL_RCM&t;&t;(0&lt;&lt;30)
DECL|macro|CON_CTL_WRITE
mdefine_line|#define  CON_CTL_WRITE&t;&t;(1&lt;&lt;29)
DECL|macro|CON_CTL_READ
mdefine_line|#define  CON_CTL_READ&t;&t;(0&lt;&lt;29)
DECL|macro|CON_CTL_BUSY
mdefine_line|#define  CON_CTL_BUSY&t;&t;(1&lt;&lt;28)
DECL|macro|CON_BYTE_DISABLE_3
mdefine_line|#define  CON_BYTE_DISABLE_3&t;(1&lt;&lt;22)&t;&t;/* 24..31 */
DECL|macro|CON_BYTE_DISABLE_2
mdefine_line|#define  CON_BYTE_DISABLE_2&t;(1&lt;&lt;21)&t;&t;/* 16..23 */
DECL|macro|CON_BYTE_DISABLE_1
mdefine_line|#define  CON_BYTE_DISABLE_1&t;(1&lt;&lt;20)&t;&t;/* 8..15 */
DECL|macro|CON_BYTE_DISABLE_0
mdefine_line|#define  CON_BYTE_DISABLE_0&t;(1&lt;&lt;19)&t;&t;/* 0..7 */
DECL|macro|CON_CTL_ADDR
mdefine_line|#define  CON_CTL_ADDR(x)&t;(x)
DECL|macro|FRAMER
mdefine_line|#define FRAMER&t;&t;0x80800&t;&t;/* to 0x80bfc */
multiline_comment|/* 3.3 network controller (internal) mailbox registers */
DECL|macro|CS_STPER0
mdefine_line|#define CS_STPER0&t;0x0
multiline_comment|/* ... */
DECL|macro|CS_STPER31
mdefine_line|#define CS_STPER31&t;0x01f
DECL|macro|CS_STTIM0
mdefine_line|#define CS_STTIM0&t;0x020
multiline_comment|/* ... */
DECL|macro|CS_STTIM31
mdefine_line|#define CS_STTIM31&t;0x03f
DECL|macro|CS_TGRLD0
mdefine_line|#define CS_TGRLD0&t;0x040
multiline_comment|/* ... */
DECL|macro|CS_TGRLD15
mdefine_line|#define CS_TGRLD15&t;0x04f
DECL|macro|CS_ERTHR0
mdefine_line|#define CS_ERTHR0&t;0x050
DECL|macro|CS_ERTHR1
mdefine_line|#define CS_ERTHR1&t;0x051
DECL|macro|CS_ERTHR2
mdefine_line|#define CS_ERTHR2&t;0x052
DECL|macro|CS_ERTHR3
mdefine_line|#define CS_ERTHR3&t;0x053
DECL|macro|CS_ERTHR4
mdefine_line|#define CS_ERTHR4&t;0x054
DECL|macro|CS_ERCTL0
mdefine_line|#define CS_ERCTL0&t;0x055
DECL|macro|TX_ENABLE
mdefine_line|#define  TX_ENABLE&t;&t;(1&lt;&lt;28)
DECL|macro|ER_ENABLE
mdefine_line|#define  ER_ENABLE&t;&t;(1&lt;&lt;27)
DECL|macro|CS_ERCTL1
mdefine_line|#define CS_ERCTL1&t;0x056
DECL|macro|CS_ERCTL2
mdefine_line|#define CS_ERCTL2&t;0x057
DECL|macro|CS_ERSTAT0
mdefine_line|#define CS_ERSTAT0&t;0x058
DECL|macro|CS_ERSTAT1
mdefine_line|#define CS_ERSTAT1&t;0x059
DECL|macro|CS_RTCCT
mdefine_line|#define CS_RTCCT&t;0x060
DECL|macro|CS_RTFWC
mdefine_line|#define CS_RTFWC&t;0x061
DECL|macro|CS_RTFWR
mdefine_line|#define CS_RTFWR&t;0x062
DECL|macro|CS_RTFTC
mdefine_line|#define CS_RTFTC&t;0x063
DECL|macro|CS_RTATR
mdefine_line|#define CS_RTATR&t;0x064
DECL|macro|CS_TFBSET
mdefine_line|#define CS_TFBSET&t;0x070
DECL|macro|CS_TFBADD
mdefine_line|#define CS_TFBADD&t;0x071
DECL|macro|CS_TFBSUB
mdefine_line|#define CS_TFBSUB&t;0x072
DECL|macro|CS_WCRMAX
mdefine_line|#define CS_WCRMAX&t;0x073
DECL|macro|CS_WCRMIN
mdefine_line|#define CS_WCRMIN&t;0x074
DECL|macro|CS_WCRINC
mdefine_line|#define CS_WCRINC&t;0x075
DECL|macro|CS_WCRDEC
mdefine_line|#define CS_WCRDEC&t;0x076
DECL|macro|CS_WCRCEIL
mdefine_line|#define CS_WCRCEIL&t;0x077
DECL|macro|CS_BWDCNT
mdefine_line|#define CS_BWDCNT&t;0x078
DECL|macro|CS_OTPPER
mdefine_line|#define CS_OTPPER&t;0x080
DECL|macro|CS_OTWPER
mdefine_line|#define CS_OTWPER&t;0x081
DECL|macro|CS_OTTLIM
mdefine_line|#define CS_OTTLIM&t;0x082
DECL|macro|CS_OTTCNT
mdefine_line|#define CS_OTTCNT&t;0x083
DECL|macro|CS_HGRRT0
mdefine_line|#define CS_HGRRT0&t;0x090
multiline_comment|/* ... */
DECL|macro|CS_HGRRT7
mdefine_line|#define CS_HGRRT7&t;0x097
DECL|macro|CS_ORPTRS
mdefine_line|#define CS_ORPTRS&t;0x0a0
DECL|macro|RXCON_CLOSE
mdefine_line|#define RXCON_CLOSE&t;0x100
DECL|macro|RCM_MEM_SIZE
mdefine_line|#define RCM_MEM_SIZE&t;0x10000&t;&t;/* 1M of 32-bit registers */
DECL|macro|TCM_MEM_SIZE
mdefine_line|#define TCM_MEM_SIZE&t;0x20000&t;&t;/* 2M of 32-bit registers */
multiline_comment|/* 2.5 transmit connection memory registers */
DECL|macro|TSR0_CONN_STATE
mdefine_line|#define TSR0_CONN_STATE(x)&t;((x&gt;&gt;28) &amp; 0x7)
DECL|macro|TSR0_USE_WMIN
mdefine_line|#define TSR0_USE_WMIN&t;&t;(1&lt;&lt;23)
DECL|macro|TSR0_GROUP
mdefine_line|#define TSR0_GROUP(x)&t;&t;((x &amp; 0x7)&lt;&lt;18)
DECL|macro|TSR0_ABR
mdefine_line|#define TSR0_ABR&t;&t;(2&lt;&lt;16)
DECL|macro|TSR0_UBR
mdefine_line|#define TSR0_UBR&t;&t;(1&lt;&lt;16)
DECL|macro|TSR0_CBR
mdefine_line|#define TSR0_CBR&t;&t;(0&lt;&lt;16)
DECL|macro|TSR0_PROT
mdefine_line|#define TSR0_PROT&t;&t;(1&lt;&lt;15)
DECL|macro|TSR0_AAL0_SDU
mdefine_line|#define TSR0_AAL0_SDU&t;&t;(2&lt;&lt;12)
DECL|macro|TSR0_AAL0
mdefine_line|#define TSR0_AAL0&t;&t;(1&lt;&lt;12)
DECL|macro|TSR0_AAL5
mdefine_line|#define TSR0_AAL5&t;&t;(0&lt;&lt;12)
DECL|macro|TSR0_HALT_ER
mdefine_line|#define TSR0_HALT_ER&t;&t;(1&lt;&lt;11)
DECL|macro|TSR0_MARK_CI
mdefine_line|#define TSR0_MARK_CI&t;&t;(1&lt;&lt;10)
DECL|macro|TSR0_MARK_ER
mdefine_line|#define TSR0_MARK_ER&t;&t;(1&lt;&lt;9)
DECL|macro|TSR0_UPDATE_GER
mdefine_line|#define TSR0_UPDATE_GER&t;&t;(1&lt;&lt;8)
DECL|macro|TSR0_RC_INDEX
mdefine_line|#define TSR0_RC_INDEX(x)&t;(x &amp; 0x1F)
DECL|macro|TSR1_PCR
mdefine_line|#define TSR1_PCR(x)&t;&t;((x &amp; 0x7FFF)&lt;&lt;16)
DECL|macro|TSR1_MCR
mdefine_line|#define TSR1_MCR(x)&t;&t;(x &amp; 0x7FFF)
DECL|macro|TSR2_ACR
mdefine_line|#define TSR2_ACR(x)&t;&t;((x &amp; 0x7FFF)&lt;&lt;16)
DECL|macro|TSR3_NRM_CNT
mdefine_line|#define TSR3_NRM_CNT(x)&t;&t;((x &amp; 0xFF)&lt;&lt;24)
DECL|macro|TSR3_CRM_CNT
mdefine_line|#define TSR3_CRM_CNT(x)&t;&t;(x &amp; 0xFFFF)
DECL|macro|TSR4_FLUSH_CONN
mdefine_line|#define TSR4_FLUSH_CONN&t;&t;(1&lt;&lt;31)
DECL|macro|TSR4_SESSION_ENDED
mdefine_line|#define TSR4_SESSION_ENDED&t;(1&lt;&lt;30)
DECL|macro|TSR4_CRC10
mdefine_line|#define TSR4_CRC10&t;&t;(1&lt;&lt;28)
DECL|macro|TSR4_NULL_CRC10
mdefine_line|#define TSR4_NULL_CRC10&t;&t;(1&lt;&lt;27)
DECL|macro|TSR4_PROT
mdefine_line|#define TSR4_PROT&t;&t;(1&lt;&lt;26)
DECL|macro|TSR4_AAL0_SDU
mdefine_line|#define TSR4_AAL0_SDU&t;&t;(2&lt;&lt;23)
DECL|macro|TSR4_AAL0
mdefine_line|#define TSR4_AAL0&t;&t;(1&lt;&lt;23)
DECL|macro|TSR4_AAL5
mdefine_line|#define TSR4_AAL5&t;&t;(0&lt;&lt;23)
DECL|macro|TSR9_OPEN_CONN
mdefine_line|#define TSR9_OPEN_CONN&t;&t;(1&lt;&lt;20)
DECL|macro|TSR11_ICR
mdefine_line|#define TSR11_ICR(x)&t;&t;((x &amp; 0x7FFF)&lt;&lt;16)
DECL|macro|TSR11_TRM
mdefine_line|#define TSR11_TRM(x)&t;&t;((x &amp; 0x7)&lt;&lt;13)
DECL|macro|TSR11_NRM
mdefine_line|#define TSR11_NRM(x)&t;&t;((x &amp; 0x7)&lt;&lt;10)
DECL|macro|TSR11_ADTF
mdefine_line|#define TSR11_ADTF(x)&t;&t;(x &amp; 0x3FF)
DECL|macro|TSR13_RDF
mdefine_line|#define TSR13_RDF(x)&t;&t;((x &amp; 0xF)&lt;&lt;23)
DECL|macro|TSR13_RIF
mdefine_line|#define TSR13_RIF(x)&t;&t;((x &amp; 0xF)&lt;&lt;19)
DECL|macro|TSR13_CDF
mdefine_line|#define TSR13_CDF(x)&t;&t;((x &amp; 0x7)&lt;&lt;16)
DECL|macro|TSR13_CRM
mdefine_line|#define TSR13_CRM(x)&t;&t;(x &amp; 0xFFFF)
DECL|macro|TSR14_DELETE
mdefine_line|#define TSR14_DELETE&t;&t;(1&lt;&lt;31)
DECL|macro|TSR14_ABR_CLOSE
mdefine_line|#define TSR14_ABR_CLOSE&t;&t;(1&lt;&lt;16)
multiline_comment|/* 2.7.1 per connection receieve state registers */
DECL|macro|RSR0_START_PDU
mdefine_line|#define RSR0_START_PDU&t;(1&lt;&lt;10)
DECL|macro|RSR0_OPEN_CONN
mdefine_line|#define RSR0_OPEN_CONN&t;(1&lt;&lt;6)
DECL|macro|RSR0_CLOSE_CONN
mdefine_line|#define RSR0_CLOSE_CONN&t;(0&lt;&lt;6)
DECL|macro|RSR0_PPD_ENABLE
mdefine_line|#define RSR0_PPD_ENABLE&t;(1&lt;&lt;5)
DECL|macro|RSR0_EPD_ENABLE
mdefine_line|#define RSR0_EPD_ENABLE&t;(1&lt;&lt;4)
DECL|macro|RSR0_TCP_CKSUM
mdefine_line|#define RSR0_TCP_CKSUM&t;(1&lt;&lt;3)
DECL|macro|RSR0_AAL5
mdefine_line|#define RSR0_AAL5&t;&t;(0)
DECL|macro|RSR0_AAL0
mdefine_line|#define RSR0_AAL0&t;&t;(1)
DECL|macro|RSR0_AAL0_SDU
mdefine_line|#define RSR0_AAL0_SDU&t;&t;(2)
DECL|macro|RSR0_RAWCELL
mdefine_line|#define RSR0_RAWCELL&t;&t;(3)
DECL|macro|RSR0_RAWCELL_CRC10
mdefine_line|#define RSR0_RAWCELL_CRC10&t;(4)
DECL|macro|RSR1_AQI_ENABLE
mdefine_line|#define RSR1_AQI_ENABLE&t;(1&lt;&lt;20)
DECL|macro|RSR1_RBPL_ONLY
mdefine_line|#define RSR1_RBPL_ONLY&t;(1&lt;&lt;19)
DECL|macro|RSR1_GROUP
mdefine_line|#define RSR1_GROUP(x)&t;((x)&lt;&lt;16)
DECL|macro|RSR4_AQI_ENABLE
mdefine_line|#define RSR4_AQI_ENABLE (1&lt;&lt;30)
DECL|macro|RSR4_GROUP
mdefine_line|#define RSR4_GROUP(x)&t;((x)&lt;&lt;27)
DECL|macro|RSR4_RBPL_ONLY
mdefine_line|#define RSR4_RBPL_ONLY&t;(1&lt;&lt;26)
multiline_comment|/* 2.1.4 transmit packet descriptor */
DECL|macro|TPD_USERCELL
mdefine_line|#define&t;TPD_USERCELL&t;&t;0x0
DECL|macro|TPD_SEGMENT_OAMF5
mdefine_line|#define&t;TPD_SEGMENT_OAMF5&t;0x4
DECL|macro|TPD_END2END_OAMF5
mdefine_line|#define&t;TPD_END2END_OAMF5&t;0x5
DECL|macro|TPD_RMCELL
mdefine_line|#define&t;TPD_RMCELL&t;&t;0x6
DECL|macro|TPD_CELLTYPE
mdefine_line|#define TPD_CELLTYPE(x)&t;&t;(x&lt;&lt;3)
DECL|macro|TPD_EOS
mdefine_line|#define TPD_EOS&t;&t;&t;(1&lt;&lt;2)
DECL|macro|TPD_CLP
mdefine_line|#define TPD_CLP&t;&t;&t;(1&lt;&lt;1)
DECL|macro|TPD_INT
mdefine_line|#define TPD_INT&t;&t;&t;(1&lt;&lt;0)
DECL|macro|TPD_LST
mdefine_line|#define TPD_LST&t;&t;(1&lt;&lt;31)
multiline_comment|/* table 4.3 serial eeprom information */
DECL|macro|PROD_ID
mdefine_line|#define PROD_ID&t;&t;0x08&t;/* char[] */
DECL|macro|PROD_ID_LEN
mdefine_line|#define  PROD_ID_LEN&t;30
DECL|macro|HW_REV
mdefine_line|#define HW_REV&t;&t;0x26&t;/* char[] */
DECL|macro|M_SN
mdefine_line|#define M_SN&t;&t;0x3a&t;/* integer */
DECL|macro|MEDIA
mdefine_line|#define MEDIA&t;&t;0x3e&t;/* integer */
DECL|macro|HE155MM
mdefine_line|#define  HE155MM&t;0x26
DECL|macro|HE155SM
mdefine_line|#define  HE155SM&t;0x27
DECL|macro|HE622MM
mdefine_line|#define  HE622MM&t;0x46
DECL|macro|HE622SM
mdefine_line|#define  HE622SM&t;0x47
DECL|macro|MAC_ADDR
mdefine_line|#define MAC_ADDR&t;0x42&t;/* char[] */
DECL|macro|CS_LOW
mdefine_line|#define CS_LOW&t;&t;0x0
DECL|macro|CS_HIGH
mdefine_line|#define CS_HIGH&t;&t;ID_CS /* HOST_CNTL_ID_PROM_SEL */
DECL|macro|CLK_LOW
mdefine_line|#define CLK_LOW&t;&t;0x0
DECL|macro|CLK_HIGH
mdefine_line|#define CLK_HIGH&t;ID_CLOCK /* HOST_CNTL_ID_PROM_CLOCK */
DECL|macro|SI_HIGH
mdefine_line|#define SI_HIGH&t;&t;ID_DIN /* HOST_CNTL_ID_PROM_DATA_IN */
DECL|macro|EEPROM_DELAY
mdefine_line|#define EEPROM_DELAY&t;400 /* microseconds */
macro_line|#endif /* _HE_H_ */
eof
