multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Au1000 IrDA driver.&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef AU1000_IRCC_H
DECL|macro|AU1000_IRCC_H
mdefine_line|#define AU1000_IRCC_H
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|NUM_IR_IFF
mdefine_line|#define NUM_IR_IFF          1
DECL|macro|NUM_IR_DESC
mdefine_line|#define NUM_IR_DESC        64
DECL|macro|RING_SIZE_4
mdefine_line|#define RING_SIZE_4       0x0
DECL|macro|RING_SIZE_16
mdefine_line|#define RING_SIZE_16      0x3
DECL|macro|RING_SIZE_64
mdefine_line|#define RING_SIZE_64      0xF
DECL|macro|MAX_NUM_IR_DESC
mdefine_line|#define MAX_NUM_IR_DESC    64
DECL|macro|MAX_BUF_SIZE
mdefine_line|#define MAX_BUF_SIZE     2048
DECL|macro|BPS_115200
mdefine_line|#define BPS_115200          0
DECL|macro|BPS_57600
mdefine_line|#define BPS_57600           1
DECL|macro|BPS_38400
mdefine_line|#define BPS_38400           2
DECL|macro|BPS_19200
mdefine_line|#define BPS_19200           5
DECL|macro|BPS_9600
mdefine_line|#define BPS_9600           11
DECL|macro|BPS_2400
mdefine_line|#define BPS_2400           47
multiline_comment|/* Ring descriptor flags */
DECL|macro|AU_OWN
mdefine_line|#define AU_OWN           (1&lt;&lt;7) /* tx,rx */
DECL|macro|IR_DIS_CRC
mdefine_line|#define IR_DIS_CRC       (1&lt;&lt;6) /* tx */
DECL|macro|IR_BAD_CRC
mdefine_line|#define IR_BAD_CRC       (1&lt;&lt;5) /* tx */
DECL|macro|IR_NEED_PULSE
mdefine_line|#define IR_NEED_PULSE    (1&lt;&lt;4) /* tx */
DECL|macro|IR_FORCE_UNDER
mdefine_line|#define IR_FORCE_UNDER   (1&lt;&lt;3) /* tx */
DECL|macro|IR_DISABLE_TX
mdefine_line|#define IR_DISABLE_TX    (1&lt;&lt;2) /* tx */
DECL|macro|IR_HW_UNDER
mdefine_line|#define IR_HW_UNDER      (1&lt;&lt;0) /* tx */
DECL|macro|IR_TX_ERROR
mdefine_line|#define IR_TX_ERROR      (IR_DIS_CRC|IR_BAD_CRC|IR_HW_UNDER)
DECL|macro|IR_PHY_ERROR
mdefine_line|#define IR_PHY_ERROR     (1&lt;&lt;6) /* rx */
DECL|macro|IR_CRC_ERROR
mdefine_line|#define IR_CRC_ERROR     (1&lt;&lt;5) /* rx */
DECL|macro|IR_MAX_LEN
mdefine_line|#define IR_MAX_LEN       (1&lt;&lt;4) /* rx */
DECL|macro|IR_FIFO_OVER
mdefine_line|#define IR_FIFO_OVER     (1&lt;&lt;3) /* rx */
DECL|macro|IR_SIR_ERROR
mdefine_line|#define IR_SIR_ERROR     (1&lt;&lt;2) /* rx */
DECL|macro|IR_RX_ERROR
mdefine_line|#define IR_RX_ERROR      (IR_PHY_ERROR|IR_CRC_ERROR| &bslash;&n;&t;&t;IR_MAX_LEN|IR_FIFO_OVER|IR_SIR_ERROR)
DECL|struct|db_dest
r_typedef
r_struct
id|db_dest
(brace
DECL|member|pnext
r_struct
id|db_dest
op_star
id|pnext
suffix:semicolon
DECL|member|vaddr
r_volatile
id|u32
op_star
id|vaddr
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
DECL|typedef|db_dest_t
)brace
id|db_dest_t
suffix:semicolon
DECL|struct|ring_desc
r_typedef
r_struct
id|ring_desc
(brace
DECL|member|count_0
id|u8
id|count_0
suffix:semicolon
multiline_comment|/* 7:0  */
DECL|member|count_1
id|u8
id|count_1
suffix:semicolon
multiline_comment|/* 12:8 */
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|addr_0
id|u8
id|addr_0
suffix:semicolon
multiline_comment|/* 7:0   */
DECL|member|addr_1
id|u8
id|addr_1
suffix:semicolon
multiline_comment|/* 15:8  */
DECL|member|addr_2
id|u8
id|addr_2
suffix:semicolon
multiline_comment|/* 23:16 */
DECL|member|addr_3
id|u8
id|addr_3
suffix:semicolon
multiline_comment|/* 31:24 */
DECL|typedef|ring_dest_t
)brace
id|ring_dest_t
suffix:semicolon
multiline_comment|/* Private data for each instance */
DECL|struct|au1k_private
r_struct
id|au1k_private
(brace
DECL|member|pDBfree
id|db_dest_t
op_star
id|pDBfree
suffix:semicolon
DECL|member|db
id|db_dest_t
id|db
(braket
l_int|2
op_star
id|NUM_IR_DESC
)braket
suffix:semicolon
DECL|member|rx_ring
r_volatile
id|ring_dest_t
op_star
id|rx_ring
(braket
id|NUM_IR_DESC
)braket
suffix:semicolon
DECL|member|tx_ring
r_volatile
id|ring_dest_t
op_star
id|tx_ring
(braket
id|NUM_IR_DESC
)braket
suffix:semicolon
DECL|member|rx_db_inuse
id|db_dest_t
op_star
id|rx_db_inuse
(braket
id|NUM_IR_DESC
)braket
suffix:semicolon
DECL|member|tx_db_inuse
id|db_dest_t
op_star
id|tx_db_inuse
(braket
id|NUM_IR_DESC
)braket
suffix:semicolon
DECL|member|rx_head
id|u32
id|rx_head
suffix:semicolon
DECL|member|tx_head
id|u32
id|tx_head
suffix:semicolon
DECL|member|tx_tail
id|u32
id|tx_tail
suffix:semicolon
DECL|member|tx_full
id|u32
id|tx_full
suffix:semicolon
DECL|member|rx_buff
id|iobuff_t
id|rx_buff
suffix:semicolon
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|stamp
r_struct
id|timeval
id|stamp
suffix:semicolon
DECL|member|now
r_struct
id|timeval
id|now
suffix:semicolon
DECL|member|qos
r_struct
id|qos_info
id|qos
suffix:semicolon
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
DECL|member|open
id|u8
id|open
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* Interface flags */
DECL|member|speed
id|u32
id|speed
suffix:semicolon
DECL|member|newspeed
id|u32
id|newspeed
suffix:semicolon
DECL|member|intr_work_done
id|u32
id|intr_work_done
suffix:semicolon
multiline_comment|/* number of Rx and Tx pkts processed in the isr */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* For serializing operations */
DECL|member|dev
r_struct
id|pm_dev
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* AU1000_IRCC_H */
eof
