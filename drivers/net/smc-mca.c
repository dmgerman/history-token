multiline_comment|/* smc-mca.c: A SMC Ultra ethernet driver for linux. */
multiline_comment|/*&n;    Most of this driver, except for ultramca_probe is nearly&n;    verbatim from smc-ultra.c by Donald Becker. The rest is&n;    written and copyright 1996 by David Weis, weisd3458@uni.edu&n;&n;    This is a driver for the SMC Ultra and SMC EtherEZ ethercards.&n;&n;    This driver uses the cards in the 8390-compatible, shared memory mode.&n;    Most of the run-time complexity is handled by the generic code in&n;    8390.c.&n;&n;    This driver enables the shared memory only when doing the actual data&n;    transfers to avoid a bug in early version of the card that corrupted&n;    data transferred by a AHA1542.&n;&n;    This driver does not support the programmed-I/O data transfer mode of&n;    the EtherEZ.  That support (if available) is smc-ez.c.  Nor does it&n;    use the non-8390-compatible &quot;Altego&quot; mode. (No support currently planned.)&n;&n;    Changelog:&n;&n;    Paul Gortmaker&t; : multiple card support for module users.&n;    David Weis&t;&t; : Micro Channel-ized it.&n;    Tom Sightler&t; : Added support for IBM PS/2 Ethernet Adapter/A&n;    Christopher Turcksin : Changed MCA-probe so that multiple adapters are&n;&t;&t;&t;   found correctly (Jul 16, 1997)&n;    Chris Beauregard&t; : Tried to merge the two changes above (Dec 15, 1997)&n;    Tom Sightler&t; : Fixed minor detection bug caused by above merge&n;    Tom Sightler&t; : Added support for three more Western Digital&n;&t;&t;&t;   MCA-adapters&n;    Tom Sightler&t; : Added support for 2.2.x mca_find_unused_adapter&n;    Hartmut Schmidt&t; : - Modified parameter detection to handle each&n;&t;&t;&t;     card differently depending on a switch-list&n;&t;&t;&t;   - &squot;card_ver&squot; removed from the adapter list&n;&t;&t;&t;   - Some minor bug fixes&n;*/
macro_line|#include &lt;linux/mca.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;8390.h&quot;
macro_line|#include &quot;smc-mca.h&quot;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME &quot;smc-mca&quot;
r_static
r_int
id|ultramca_open
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
id|ultramca_reset_8390
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
id|ultramca_get_8390_hdr
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
id|ultramca_block_input
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
id|ultramca_block_output
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
r_const
r_int
id|start_page
)paren
suffix:semicolon
r_static
r_int
id|ultramca_close_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|macro|START_PG
mdefine_line|#define START_PG        0x00    /* First page of TX buffer */
DECL|macro|ULTRA_CMDREG
mdefine_line|#define ULTRA_CMDREG 0      /* Offset to ASIC command register. */
DECL|macro|ULTRA_RESET
mdefine_line|#define ULTRA_RESET  0x80   /* Board reset, in ULTRA_CMDREG. */
DECL|macro|ULTRA_MEMENB
mdefine_line|#define ULTRA_MEMENB 0x40   /* Enable the shared memory. */
DECL|macro|ULTRA_NIC_OFFSET
mdefine_line|#define ULTRA_NIC_OFFSET 16 /* NIC register offset from the base_addr. */
DECL|macro|ULTRA_IO_EXTENT
mdefine_line|#define ULTRA_IO_EXTENT 32
DECL|macro|EN0_ERWCNT
mdefine_line|#define EN0_ERWCNT      0x08  /* Early receive warning count. */
DECL|macro|_61c8_SMC_Ethercard_PLUS_Elite_A_BNC_AUI_WD8013EP_A
mdefine_line|#define _61c8_SMC_Ethercard_PLUS_Elite_A_BNC_AUI_WD8013EP_A            0
DECL|macro|_61c9_SMC_Ethercard_PLUS_Elite_A_UTP_AUI_WD8013EP_A
mdefine_line|#define _61c9_SMC_Ethercard_PLUS_Elite_A_UTP_AUI_WD8013EP_A            1
DECL|macro|_6fc0_WD_Ethercard_PLUS_A_WD8003E_A_OR_WD8003ET_A
mdefine_line|#define _6fc0_WD_Ethercard_PLUS_A_WD8003E_A_OR_WD8003ET_A              2
DECL|macro|_6fc1_WD_Starcard_PLUS_A_WD8003ST_A
mdefine_line|#define _6fc1_WD_Starcard_PLUS_A_WD8003ST_A                            3
DECL|macro|_6fc2_WD_Ethercard_PLUS_10T_A_WD8003W_A
mdefine_line|#define _6fc2_WD_Ethercard_PLUS_10T_A_WD8003W_A                        4
DECL|macro|_efd4_IBM_PS2_Adapter_A_for_Ethernet_UTP_AUI_WD8013WP_A
mdefine_line|#define _efd4_IBM_PS2_Adapter_A_for_Ethernet_UTP_AUI_WD8013WP_A        5
DECL|macro|_efd5_IBM_PS2_Adapter_A_for_Ethernet_BNC_AUI_WD8013WP_A
mdefine_line|#define _efd5_IBM_PS2_Adapter_A_for_Ethernet_BNC_AUI_WD8013WP_A        6
DECL|macro|_efe5_IBM_PS2_Adapter_A_for_Ethernet
mdefine_line|#define _efe5_IBM_PS2_Adapter_A_for_Ethernet                           7
DECL|struct|smc_mca_adapters_t
r_struct
id|smc_mca_adapters_t
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAX_ULTRAMCA_CARDS
mdefine_line|#define MAX_ULTRAMCA_CARDS 4&t;/* Max number of Ultra cards per module */
DECL|variable|ultra_io
r_static
r_int
id|ultra_io
(braket
id|MAX_ULTRAMCA_CARDS
)braket
suffix:semicolon
DECL|variable|ultra_irq
r_static
r_int
id|ultra_irq
(braket
id|MAX_ULTRAMCA_CARDS
)braket
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|ultra_io
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_ULTRAMCA_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|ultra_irq
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_ULTRAMCA_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ultra_io
comma
l_string|&quot;SMC Ultra/EtherEZ MCA I/O base address(es)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ultra_irq
comma
l_string|&quot;SMC Ultra/EtherEZ MCA IRQ number(s)&quot;
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|smc_mca_adapter_ids
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x61c8
comma
l_int|0x61c9
comma
l_int|0x6fc0
comma
l_int|0x6fc1
comma
l_int|0x6fc2
comma
l_int|0xefd4
comma
l_int|0xefd5
comma
l_int|0xefe5
comma
l_int|0x0000
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
op_star
id|smc_mca_adapter_names
(braket
)braket
id|__initdata
op_assign
(brace
l_string|&quot;SMC Ethercard PLUS Elite/A BNC/AUI (WD8013EP/A)&quot;
comma
l_string|&quot;SMC Ethercard PLUS Elite/A UTP/AUI (WD8013WP/A)&quot;
comma
l_string|&quot;WD Ethercard PLUS/A (WD8003E/A or WD8003ET/A)&quot;
comma
l_string|&quot;WD Starcard PLUS/A (WD8003ST/A)&quot;
comma
l_string|&quot;WD Ethercard PLUS 10T/A (WD8003W/A)&quot;
comma
l_string|&quot;IBM PS/2 Adapter/A for Ethernet UTP/AUI (WD8013WP/A)&quot;
comma
l_string|&quot;IBM PS/2 Adapter/A for Ethernet BNC/AUI (WD8013EP/A)&quot;
comma
l_string|&quot;IBM PS/2 Adapter/A for Ethernet&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|ultra_found
r_static
r_int
id|ultra_found
op_assign
l_int|0
suffix:semicolon
DECL|function|ultramca_probe
r_int
id|__init
id|ultramca_probe
c_func
(paren
r_struct
id|device
op_star
id|gen_dev
)paren
(brace
r_int
r_int
id|ioaddr
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
r_char
id|reg4
comma
id|num_pages
suffix:semicolon
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|to_mca_device
c_func
(paren
id|gen_dev
)paren
suffix:semicolon
r_char
id|slot
op_assign
id|mca_dev-&gt;slot
suffix:semicolon
r_int
r_char
id|pos2
op_assign
l_int|0xff
comma
id|pos3
op_assign
l_int|0xff
comma
id|pos4
op_assign
l_int|0xff
comma
id|pos5
op_assign
l_int|0xff
suffix:semicolon
r_int
id|i
comma
id|rc
suffix:semicolon
r_int
id|adapter
op_assign
id|mca_dev-&gt;index
suffix:semicolon
r_int
id|tbase
op_assign
l_int|0
suffix:semicolon
r_int
id|tirq
op_assign
l_int|0
suffix:semicolon
r_int
id|base_addr
op_assign
id|ultra_io
(braket
id|ultra_found
)braket
suffix:semicolon
r_int
id|irq
op_assign
id|ultra_irq
(braket
id|ultra_found
)braket
suffix:semicolon
r_if
c_cond
(paren
id|base_addr
op_logical_or
id|irq
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Probing for SMC MCA adapter&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base_addr
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; at I/O address 0x%04x%c&quot;
comma
id|base_addr
comma
id|irq
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;using irq %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
)brace
id|tirq
op_assign
l_int|0
suffix:semicolon
id|tbase
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* If we&squot;re trying to match a specificied irq or io address,&n;&t; * we&squot;ll reject the adapter found unless it&squot;s the one we&squot;re&n;&t; * looking for */
id|pos2
op_assign
id|mca_device_read_stored_pos
c_func
(paren
id|mca_dev
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* io_addr */
id|pos3
op_assign
id|mca_device_read_stored_pos
c_func
(paren
id|mca_dev
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* shared mem */
id|pos4
op_assign
id|mca_device_read_stored_pos
c_func
(paren
id|mca_dev
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* ROM bios addr range */
id|pos5
op_assign
id|mca_device_read_stored_pos
c_func
(paren
id|mca_dev
comma
l_int|5
)paren
suffix:semicolon
multiline_comment|/* irq, media and RIPL */
multiline_comment|/* Test the following conditions:&n;&t; * - If an irq parameter is supplied, compare it&n;&t; *   with the irq of the adapter we found&n;&t; * - If a base_addr paramater is given, compare it&n;&t; *   with the base_addr of the adapter we found&n;&t; * - Check that the irq and the base_addr of the&n;&t; *   adapter we found is not already in use by&n;&t; *   this driver&n;&t; */
r_switch
c_cond
(paren
id|mca_dev-&gt;index
)paren
(brace
r_case
id|_61c8_SMC_Ethercard_PLUS_Elite_A_BNC_AUI_WD8013EP_A
suffix:colon
r_case
id|_61c9_SMC_Ethercard_PLUS_Elite_A_UTP_AUI_WD8013EP_A
suffix:colon
r_case
id|_efd4_IBM_PS2_Adapter_A_for_Ethernet_UTP_AUI_WD8013WP_A
suffix:colon
r_case
id|_efd5_IBM_PS2_Adapter_A_for_Ethernet_BNC_AUI_WD8013WP_A
suffix:colon
(brace
id|tbase
op_assign
id|addr_table
(braket
(paren
id|pos2
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
)braket
dot
id|base_addr
suffix:semicolon
id|tirq
op_assign
id|irq_table
(braket
(paren
id|pos5
op_amp
l_int|0xc
)paren
op_rshift
l_int|2
)braket
dot
id|new_irq
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|_6fc0_WD_Ethercard_PLUS_A_WD8003E_A_OR_WD8003ET_A
suffix:colon
r_case
id|_6fc1_WD_Starcard_PLUS_A_WD8003ST_A
suffix:colon
r_case
id|_6fc2_WD_Ethercard_PLUS_10T_A_WD8003W_A
suffix:colon
r_case
id|_efe5_IBM_PS2_Adapter_A_for_Ethernet
suffix:colon
(brace
id|tbase
op_assign
(paren
(paren
id|pos2
op_amp
l_int|0x0fe
)paren
op_star
l_int|0x10
)paren
suffix:semicolon
id|tirq
op_assign
id|irq_table
(braket
(paren
id|pos5
op_amp
l_int|3
)paren
)braket
dot
id|old_irq
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|tirq
op_logical_or
op_logical_neg
id|tbase
op_logical_or
(paren
id|irq
op_logical_and
id|irq
op_ne
id|tirq
)paren
op_logical_or
(paren
id|base_addr
op_logical_and
id|tbase
op_ne
id|base_addr
)paren
)paren
(brace
multiline_comment|/* FIXME: we&squot;re trying to force the ordering of the&n;&t;&t; * devices here, there should be a way of getting this&n;&t;&t; * to happen */
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* Adapter found. */
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
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|SET_NETDEV_DEV
c_func
(paren
id|dev
comma
id|gen_dev
)paren
suffix:semicolon
id|mca_device_set_name
c_func
(paren
id|mca_dev
comma
id|smc_mca_adapter_names
(braket
id|adapter
)braket
)paren
suffix:semicolon
id|mca_device_set_claim
c_func
(paren
id|mca_dev
comma
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;smc_mca: %s found in slot %d&bslash;n&quot;
comma
id|smc_mca_adapter_names
(braket
id|adapter
)braket
comma
id|slot
op_plus
l_int|1
)paren
suffix:semicolon
id|ultra_found
op_increment
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|ioaddr
op_assign
id|mca_device_transform_ioport
c_func
(paren
id|mca_dev
comma
id|tbase
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|mca_device_transform_irq
c_func
(paren
id|mca_dev
comma
id|tirq
)paren
suffix:semicolon
id|dev-&gt;mem_start
op_assign
l_int|0
suffix:semicolon
id|num_pages
op_assign
l_int|40
suffix:semicolon
r_switch
c_cond
(paren
id|adapter
)paren
(brace
multiline_comment|/* card-# in const array above [hs] */
r_case
id|_61c8_SMC_Ethercard_PLUS_Elite_A_BNC_AUI_WD8013EP_A
suffix:colon
r_case
id|_61c9_SMC_Ethercard_PLUS_Elite_A_UTP_AUI_WD8013EP_A
suffix:colon
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* taking 16 counts&n;&t;&t;&t;&t;&t;&t;    * up to 15 [hs] */
r_if
c_cond
(paren
id|mem_table
(braket
id|i
)braket
dot
id|mem_index
op_eq
(paren
id|pos3
op_amp
op_complement
id|MEM_MASK
)paren
)paren
(brace
id|dev-&gt;mem_start
op_assign
(paren
r_int
r_int
)paren
id|mca_device_transform_memory
c_func
(paren
id|mca_dev
comma
(paren
r_void
op_star
)paren
id|mem_table
(braket
id|i
)braket
dot
id|mem_start
)paren
suffix:semicolon
id|num_pages
op_assign
id|mem_table
(braket
id|i
)braket
dot
id|num_pages
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_case
id|_6fc0_WD_Ethercard_PLUS_A_WD8003E_A_OR_WD8003ET_A
suffix:colon
r_case
id|_6fc1_WD_Starcard_PLUS_A_WD8003ST_A
suffix:colon
r_case
id|_6fc2_WD_Ethercard_PLUS_10T_A_WD8003W_A
suffix:colon
r_case
id|_efe5_IBM_PS2_Adapter_A_for_Ethernet
suffix:colon
(brace
id|dev-&gt;mem_start
op_assign
(paren
r_int
r_int
)paren
id|mca_device_transform_memory
c_func
(paren
id|mca_dev
comma
(paren
r_void
op_star
)paren
(paren
(paren
id|pos3
op_amp
l_int|0xfc
)paren
op_star
l_int|0x1000
)paren
)paren
suffix:semicolon
id|num_pages
op_assign
l_int|0x40
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|_efd4_IBM_PS2_Adapter_A_for_Ethernet_UTP_AUI_WD8013WP_A
suffix:colon
r_case
id|_efd5_IBM_PS2_Adapter_A_for_Ethernet_BNC_AUI_WD8013WP_A
suffix:colon
(brace
multiline_comment|/* courtesy of gamera@quartz.ocn.ne.jp, pos3 indicates&n;&t;&t;&t; * the index of the 0x2000 step.&n;&t;&t;&t; * beware different number of pages [hs]&n;&t;&t;&t; */
id|dev-&gt;mem_start
op_assign
(paren
r_int
r_int
)paren
id|mca_device_transform_memory
c_func
(paren
id|mca_dev
comma
(paren
r_void
op_star
)paren
(paren
l_int|0xc0000
op_plus
(paren
l_int|0x2000
op_star
(paren
id|pos3
op_amp
l_int|0xf
)paren
)paren
)paren
)paren
suffix:semicolon
id|num_pages
op_assign
l_int|0x20
op_plus
(paren
l_int|2
op_star
(paren
id|pos3
op_amp
l_int|0x10
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* sanity check, shouldn&squot;t happen */
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_eq
l_int|0
)paren
(brace
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err_unclaim
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ioaddr
comma
id|ULTRA_IO_EXTENT
comma
id|DRV_NAME
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err_unclaim
suffix:semicolon
)brace
id|reg4
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|4
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|outb
c_func
(paren
id|reg4
comma
id|ioaddr
op_plus
l_int|4
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;smc_mca[%d]: Parameters: %#3x,&quot;
comma
id|slot
op_plus
l_int|1
comma
id|ioaddr
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; %2.2X&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|8
op_plus
id|i
)paren
)paren
suffix:semicolon
multiline_comment|/* Switch from the station address to the alternate register set&n;&t; * and read the useful registers there.&n;&t; */
id|outb
c_func
(paren
l_int|0x80
op_or
id|reg4
comma
id|ioaddr
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Enable FINE16 mode to avoid BIOS ROM width mismatches @ reboot.&n;&t; */
id|outb
c_func
(paren
l_int|0x80
op_or
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0x0c
)paren
comma
id|ioaddr
op_plus
l_int|0x0c
)paren
suffix:semicolon
multiline_comment|/* Switch back to the station address register set so that&n;&t; * the MS-DOS driver can find the card after a warm boot.&n;&t; */
id|outb
c_func
(paren
id|reg4
comma
id|ioaddr
op_plus
l_int|4
)paren
suffix:semicolon
id|gen_dev-&gt;driver_data
op_assign
id|dev
suffix:semicolon
multiline_comment|/* The 8390 isn&squot;t at the base address, so fake the offset&n;&t; */
id|dev-&gt;base_addr
op_assign
id|ioaddr
op_plus
id|ULTRA_NIC_OFFSET
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;SMC Ultra MCA&quot;
suffix:semicolon
id|ei_status.word16
op_assign
l_int|1
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|START_PG
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.stop_page
op_assign
id|num_pages
suffix:semicolon
id|ei_status.mem
op_assign
id|ioremap
c_func
(paren
id|dev-&gt;mem_start
comma
(paren
id|ei_status.stop_page
op_minus
id|START_PG
)paren
op_star
l_int|256
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ei_status.mem
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_release_region
suffix:semicolon
)brace
id|dev-&gt;mem_end
op_assign
id|dev-&gt;mem_start
op_plus
(paren
id|ei_status.stop_page
op_minus
id|START_PG
)paren
op_star
l_int|256
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, IRQ %d memory %#lx-%#lx.&bslash;n&quot;
comma
id|dev-&gt;irq
comma
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_end
op_minus
l_int|1
)paren
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|ultramca_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|ultramca_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|ultramca_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|ultramca_get_8390_hdr
suffix:semicolon
id|ei_status.priv
op_assign
id|slot
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|ultramca_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|ultramca_close_card
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
id|rc
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
id|rc
)paren
r_goto
id|err_unmap
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_unmap
suffix:colon
id|iounmap
c_func
(paren
id|ei_status.mem
)paren
suffix:semicolon
id|err_release_region
suffix:colon
id|release_region
c_func
(paren
id|ioaddr
comma
id|ULTRA_IO_EXTENT
)paren
suffix:semicolon
id|err_unclaim
suffix:colon
id|mca_device_set_claim
c_func
(paren
id|mca_dev
comma
l_int|0
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|ultramca_open
r_static
r_int
id|ultramca_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC addr */
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|ei_interrupt
comma
l_int|0
comma
id|dev-&gt;name
comma
id|dev
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
id|outb
c_func
(paren
id|ULTRA_MEMENB
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Enable memory */
id|outb
c_func
(paren
l_int|0x80
comma
id|ioaddr
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* ??? */
id|outb
c_func
(paren
l_int|0x01
comma
id|ioaddr
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts and memory. */
id|outb
c_func
(paren
l_int|0x04
comma
id|ioaddr
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* ??? */
multiline_comment|/* Set the early receive warning level in window 0 high enough not&n;&t; * to receive ERW interrupts.&n;&t; */
multiline_comment|/* outb_p(E8390_NODMA + E8390_PAGE0, dev-&gt;base_addr);&n;&t; * outb(0xff, dev-&gt;base_addr + EN0_ERWCNT);&n;&t; */
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
DECL|function|ultramca_reset_8390
r_static
r_void
id|ultramca_reset_8390
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC addr */
id|outb
c_func
(paren
id|ULTRA_RESET
comma
id|ioaddr
)paren
suffix:semicolon
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
l_string|&quot;resetting Ultra, t=%ld...&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
l_int|0x80
comma
id|ioaddr
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* ??? */
id|outb
c_func
(paren
l_int|0x01
comma
id|ioaddr
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts and memory. */
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
l_string|&quot;reset done&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Grab the 8390 specific header. Similar to the block_input routine, but&n; * we don&squot;t need to be concerned with ring wrap as the header will be at&n; * the start of a page, so we optimize accordingly.&n; */
DECL|function|ultramca_get_8390_hdr
r_static
r_void
id|ultramca_get_8390_hdr
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
r_void
id|__iomem
op_star
id|hdr_start
op_assign
id|ei_status.mem
op_plus
(paren
(paren
id|ring_page
op_minus
id|START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
macro_line|#ifdef notdef
multiline_comment|/* Officially this is what we are doing, but the readl() is faster */
id|memcpy_fromio
c_func
(paren
id|hdr
comma
id|hdr_start
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
)paren
suffix:semicolon
macro_line|#else
(paren
(paren
r_int
r_int
op_star
)paren
id|hdr
)paren
(braket
l_int|0
)braket
op_assign
id|readl
c_func
(paren
id|hdr_start
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Block input and output are easy on shared memory ethercards, the only&n; * complication is when the ring buffer wraps.&n; */
DECL|function|ultramca_block_input
r_static
r_void
id|ultramca_block_input
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
r_void
id|__iomem
op_star
id|xfer_start
op_assign
id|ei_status.mem
op_plus
id|ring_offset
op_minus
id|START_PG
op_star
l_int|256
suffix:semicolon
r_if
c_cond
(paren
id|ring_offset
op_plus
id|count
OG
id|ei_status.stop_page
op_star
l_int|256
)paren
(brace
multiline_comment|/* We must wrap the input move. */
r_int
id|semi_count
op_assign
id|ei_status.stop_page
op_star
l_int|256
op_minus
id|ring_offset
suffix:semicolon
id|memcpy_fromio
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
id|memcpy_fromio
c_func
(paren
id|skb-&gt;data
op_plus
id|semi_count
comma
id|ei_status.mem
op_plus
id|TX_PAGES
op_star
l_int|256
comma
id|count
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Packet is in one chunk -- we can copy + cksum. */
id|eth_io_copy_and_sum
c_func
(paren
id|skb
comma
id|xfer_start
comma
id|count
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|ultramca_block_output
r_static
r_void
id|ultramca_block_output
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
r_void
id|__iomem
op_star
id|shmem
op_assign
id|ei_status.mem
op_plus
(paren
(paren
id|start_page
op_minus
id|START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|memcpy_toio
c_func
(paren
id|shmem
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|ultramca_close_card
r_static
r_int
id|ultramca_close_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC addr */
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
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
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Disable interrupts. */
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* We should someday disable shared memory and change to 8-bit mode&n;         * &quot;just in case&quot;...&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ultramca_remove
r_static
r_int
id|ultramca_remove
c_func
(paren
r_struct
id|device
op_star
id|gen_dev
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|to_mca_device
c_func
(paren
id|gen_dev
)paren
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|gen_dev-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
multiline_comment|/* NB: ultra_close_card() does free_irq */
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|mca_device_set_claim
c_func
(paren
id|mca_dev
comma
l_int|0
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ioaddr
comma
id|ULTRA_IO_EXTENT
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|ei_status.mem
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ultra_driver
r_static
r_struct
id|mca_driver
id|ultra_driver
op_assign
(brace
dot
id|id_table
op_assign
id|smc_mca_adapter_ids
comma
dot
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;smc-mca&quot;
comma
dot
id|bus
op_assign
op_amp
id|mca_bus_type
comma
dot
id|probe
op_assign
id|ultramca_probe
comma
dot
id|remove
op_assign
id|ultramca_remove
comma
)brace
)brace
suffix:semicolon
DECL|function|ultramca_init_module
r_static
r_int
id|__init
id|ultramca_init_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|MCA_bus
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|mca_register_driver
c_func
(paren
op_amp
id|ultra_driver
)paren
suffix:semicolon
r_return
id|ultra_found
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|ultramca_cleanup_module
r_static
r_void
id|__exit
id|ultramca_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|mca_unregister_driver
c_func
(paren
op_amp
id|ultra_driver
)paren
suffix:semicolon
)brace
DECL|variable|ultramca_init_module
id|module_init
c_func
(paren
id|ultramca_init_module
)paren
suffix:semicolon
DECL|variable|ultramca_cleanup_module
id|module_exit
c_func
(paren
id|ultramca_cleanup_module
)paren
suffix:semicolon
eof
