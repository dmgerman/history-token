multiline_comment|/* New Hydra driver using generic 8390 core */
multiline_comment|/* Based on old hydra driver by Topi Kanerva (topi@susanna.oulu.fi) */
multiline_comment|/* This file is subject to the terms and conditions of the GNU General      */
multiline_comment|/* Public License.  See the file COPYING in the main directory of the       */
multiline_comment|/* Linux distribution for more details.                                     */
multiline_comment|/* Peter De Schrijver (p2@mind.be) */
multiline_comment|/* Oldenburg 2000 */
multiline_comment|/* The Amiganet is a Zorro-II board made by Hydra Systems. It contains a    */
multiline_comment|/* NS8390 NIC (network interface controller) clone, 16 or 64K on-board RAM  */
multiline_comment|/* and 10BASE-2 (thin coax) and AUI connectors.                             */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &quot;8390.h&quot;
DECL|macro|NE_EN0_DCFG
mdefine_line|#define NE_EN0_DCFG     (0x0e*2)
DECL|macro|NESM_START_PG
mdefine_line|#define NESM_START_PG   0x0    /* First page of TX buffer */
DECL|macro|NESM_STOP_PG
mdefine_line|#define NESM_STOP_PG    0x40    /* Last page +1 of RX ring */
DECL|macro|HYDRA_NIC_BASE
mdefine_line|#define HYDRA_NIC_BASE 0xffe1
DECL|macro|HYDRA_ADDRPROM
mdefine_line|#define HYDRA_ADDRPROM 0xffc0
DECL|macro|HYDRA_VERSION
mdefine_line|#define HYDRA_VERSION &quot;v3.0alpha&quot;
DECL|macro|WORDSWAP
mdefine_line|#define WORDSWAP(a)     ((((a)&gt;&gt;8)&amp;0xff) | ((a)&lt;&lt;8))
r_static
r_int
id|__devinit
id|hydra_init_one
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
comma
r_const
r_struct
id|zorro_device_id
op_star
id|ent
)paren
suffix:semicolon
r_static
r_int
id|__devinit
id|hydra_init
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
)paren
suffix:semicolon
r_static
r_int
id|hydra_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|hydra_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|hydra_reset_8390
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|hydra_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
suffix:semicolon
r_static
r_void
id|hydra_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
suffix:semicolon
r_static
r_void
id|hydra_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|start_page
)paren
suffix:semicolon
r_static
r_void
id|__devexit
id|hydra_remove_one
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|zorro_device_id
id|hydra_zorro_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|ZORRO_PROD_HYDRA_SYSTEMS_AMIGANET
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|hydra_driver
r_static
r_struct
id|zorro_driver
id|hydra_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;hydra&quot;
comma
dot
id|id_table
op_assign
id|hydra_zorro_tbl
comma
dot
id|probe
op_assign
id|hydra_init_one
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|hydra_remove_one
)paren
comma
)brace
suffix:semicolon
DECL|function|hydra_init_one
r_static
r_int
id|__devinit
id|hydra_init_one
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
comma
r_const
r_struct
id|zorro_device_id
op_star
id|ent
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|z-&gt;resource.start
comma
l_int|0x10000
comma
l_string|&quot;Hydra&quot;
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|hydra_init
c_func
(paren
id|z
)paren
)paren
)paren
(brace
id|release_mem_region
c_func
(paren
id|z-&gt;resource.start
comma
l_int|0x10000
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hydra_init
r_static
r_int
id|__devinit
id|hydra_init
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
r_int
id|board
op_assign
id|ZTWO_VADDR
c_func
(paren
id|z-&gt;resource.start
)paren
suffix:semicolon
r_int
r_int
id|ioaddr
op_assign
id|board
op_plus
id|HYDRA_NIC_BASE
suffix:semicolon
r_const
r_char
id|name
(braket
)braket
op_assign
l_string|&quot;NE2000&quot;
suffix:semicolon
r_int
id|start_page
comma
id|stop_page
suffix:semicolon
r_int
id|j
suffix:semicolon
r_int
id|err
suffix:semicolon
r_static
id|u32
id|hydra_offsets
(braket
l_int|16
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x02
comma
l_int|0x04
comma
l_int|0x06
comma
l_int|0x08
comma
l_int|0x0a
comma
l_int|0x0c
comma
l_int|0x0e
comma
l_int|0x10
comma
l_int|0x12
comma
l_int|0x14
comma
l_int|0x16
comma
l_int|0x18
comma
l_int|0x1a
comma
l_int|0x1c
comma
l_int|0x1e
comma
)brace
suffix:semicolon
id|dev
op_assign
id|alloc_ei_netdev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|ETHER_ADDR_LEN
suffix:semicolon
id|j
op_increment
)paren
(brace
id|dev-&gt;dev_addr
(braket
id|j
)braket
op_assign
op_star
(paren
(paren
id|u8
op_star
)paren
(paren
id|board
op_plus
id|HYDRA_ADDRPROM
op_plus
l_int|2
op_star
id|j
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* We must set the 8390 for word mode. */
id|z_writeb
c_func
(paren
l_int|0x4b
comma
id|ioaddr
op_plus
id|NE_EN0_DCFG
)paren
suffix:semicolon
id|start_page
op_assign
id|NESM_START_PG
suffix:semicolon
id|stop_page
op_assign
id|NESM_STOP_PG
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|dev-&gt;irq
op_assign
id|IRQ_AMIGA_PORTS
suffix:semicolon
multiline_comment|/* Install the Interrupt handler */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|ei_interrupt
comma
id|SA_SHIRQ
comma
l_string|&quot;Hydra Ethernet&quot;
comma
id|dev
)paren
)paren
(brace
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|ei_status.name
op_assign
id|name
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|start_page
suffix:semicolon
id|ei_status.stop_page
op_assign
id|stop_page
suffix:semicolon
id|ei_status.word16
op_assign
l_int|1
suffix:semicolon
id|ei_status.bigendian
op_assign
l_int|1
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|start_page
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|hydra_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|hydra_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|hydra_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|hydra_get_8390_hdr
suffix:semicolon
id|ei_status.reg_offset
op_assign
id|hydra_offsets
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|hydra_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|hydra_close
suffix:semicolon
macro_line|#ifdef CONFIG_NET_POLL_CONTROLLER
id|dev-&gt;poll_controller
op_assign
id|ei_poll
suffix:semicolon
macro_line|#endif
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|free_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|dev
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|zorro_set_drvdata
c_func
(paren
id|z
comma
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Hydra at 0x%08lx, address %02x:%02x:%02x:%02x:%02x:%02x &quot;
l_string|&quot;(hydra.c &quot;
id|HYDRA_VERSION
l_string|&quot;)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|z-&gt;resource.start
comma
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|1
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|3
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|4
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hydra_open
r_static
r_int
id|hydra_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ei_open
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hydra_close
r_static
r_int
id|hydra_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|ei_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Shutting down ethercard.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|ei_close
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hydra_reset_8390
r_static
r_void
id|hydra_reset_8390
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Hydra hw reset not there&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|hydra_get_8390_hdr
r_static
r_void
id|hydra_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
(brace
r_int
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
op_star
id|ptrs
suffix:semicolon
r_int
r_int
id|hdr_start
op_assign
(paren
id|nic_base
op_minus
id|HYDRA_NIC_BASE
)paren
op_plus
(paren
(paren
id|ring_page
op_minus
id|NESM_START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|ptrs
op_assign
(paren
r_int
op_star
)paren
id|hdr
suffix:semicolon
op_star
(paren
id|ptrs
op_increment
)paren
op_assign
id|z_readw
c_func
(paren
id|hdr_start
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|hdr
)paren
op_assign
id|WORDSWAP
c_func
(paren
op_star
(paren
(paren
r_int
op_star
)paren
id|hdr
)paren
)paren
suffix:semicolon
id|hdr_start
op_add_assign
l_int|2
suffix:semicolon
op_star
(paren
id|ptrs
op_increment
)paren
op_assign
id|z_readw
c_func
(paren
id|hdr_start
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|hdr
op_plus
l_int|1
)paren
op_assign
id|WORDSWAP
c_func
(paren
op_star
(paren
(paren
r_int
op_star
)paren
id|hdr
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|function|hydra_block_input
r_static
r_void
id|hydra_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
(brace
r_int
r_int
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
r_int
id|mem_base
op_assign
id|nic_base
op_minus
id|HYDRA_NIC_BASE
suffix:semicolon
r_int
r_int
id|xfer_start
op_assign
id|mem_base
op_plus
id|ring_offset
op_minus
(paren
id|NESM_START_PG
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|1
)paren
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|xfer_start
op_plus
id|count
OG
id|mem_base
op_plus
(paren
id|NESM_STOP_PG
op_lshift
l_int|8
)paren
)paren
(brace
r_int
id|semi_count
op_assign
(paren
id|mem_base
op_plus
(paren
id|NESM_STOP_PG
op_lshift
l_int|8
)paren
)paren
op_minus
id|xfer_start
suffix:semicolon
id|z_memcpy_fromio
c_func
(paren
id|skb-&gt;data
comma
id|xfer_start
comma
id|semi_count
)paren
suffix:semicolon
id|count
op_sub_assign
id|semi_count
suffix:semicolon
id|z_memcpy_fromio
c_func
(paren
id|skb-&gt;data
op_plus
id|semi_count
comma
id|mem_base
comma
id|count
)paren
suffix:semicolon
)brace
r_else
id|z_memcpy_fromio
c_func
(paren
id|skb-&gt;data
comma
id|xfer_start
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|hydra_block_output
r_static
r_void
id|hydra_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|start_page
)paren
(brace
r_int
r_int
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
r_int
id|mem_base
op_assign
id|nic_base
op_minus
id|HYDRA_NIC_BASE
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|1
)paren
id|count
op_increment
suffix:semicolon
id|z_memcpy_toio
c_func
(paren
id|mem_base
op_plus
(paren
(paren
id|start_page
op_minus
id|NESM_START_PG
)paren
op_lshift
l_int|8
)paren
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|hydra_remove_one
r_static
r_void
id|__devexit
id|hydra_remove_one
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|zorro_get_drvdata
c_func
(paren
id|z
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|dev
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|ZTWO_PADDR
c_func
(paren
id|dev-&gt;base_addr
)paren
op_minus
id|HYDRA_NIC_BASE
comma
l_int|0x10000
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|hydra_init_module
r_static
r_int
id|__init
id|hydra_init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|zorro_module_init
c_func
(paren
op_amp
id|hydra_driver
)paren
suffix:semicolon
)brace
DECL|function|hydra_cleanup_module
r_static
r_void
id|__exit
id|hydra_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|zorro_unregister_driver
c_func
(paren
op_amp
id|hydra_driver
)paren
suffix:semicolon
)brace
DECL|variable|hydra_init_module
id|module_init
c_func
(paren
id|hydra_init_module
)paren
suffix:semicolon
DECL|variable|hydra_cleanup_module
id|module_exit
c_func
(paren
id|hydra_cleanup_module
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
