multiline_comment|/*&n; * Support for common PCI multi-I/O cards (which is most of them)&n; *&n; * Copyright (C) 2001  Tim Waugh &lt;twaugh@redhat.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; *&n; * Multi-function PCI cards are supposed to present separate logical&n; * devices on the bus.  A common thing to do seems to be to just use&n; * one logical device with lots of base address registers for both&n; * parallel ports and serial ports.  This driver is for dealing with&n; * that.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/parport_pc.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
DECL|enum|parport_pc_pci_cards
r_enum
id|parport_pc_pci_cards
(brace
DECL|enumerator|titan_110l
id|titan_110l
op_assign
l_int|0
comma
DECL|enumerator|titan_210l
id|titan_210l
comma
DECL|enumerator|avlab_1s1p
id|avlab_1s1p
comma
DECL|enumerator|avlab_1s1p_650
id|avlab_1s1p_650
comma
DECL|enumerator|avlab_1s1p_850
id|avlab_1s1p_850
comma
DECL|enumerator|avlab_1s2p
id|avlab_1s2p
comma
DECL|enumerator|avlab_1s2p_650
id|avlab_1s2p_650
comma
DECL|enumerator|avlab_1s2p_850
id|avlab_1s2p_850
comma
DECL|enumerator|avlab_2s1p
id|avlab_2s1p
comma
DECL|enumerator|avlab_2s1p_650
id|avlab_2s1p_650
comma
DECL|enumerator|avlab_2s1p_850
id|avlab_2s1p_850
comma
)brace
suffix:semicolon
multiline_comment|/* each element directly indexed from enum list, above */
DECL|struct|parport_pc_pci
r_static
r_struct
id|parport_pc_pci
(brace
DECL|member|numports
r_int
id|numports
suffix:semicolon
r_struct
(brace
multiline_comment|/* BAR (base address registers) numbers in the config&n;                    space header */
DECL|member|lo
r_int
id|lo
suffix:semicolon
DECL|member|hi
r_int
id|hi
suffix:semicolon
multiline_comment|/* -1 if not there, &gt;6 for offset-method (max&n;                           BAR is 6) */
DECL|member|addr
)brace
id|addr
(braket
l_int|4
)braket
suffix:semicolon
DECL|variable|__devinitdata
)brace
id|cards
(braket
)braket
id|__devinitdata
op_assign
(brace
multiline_comment|/* titan_110l */
(brace
l_int|1
comma
(brace
(brace
l_int|3
comma
op_minus
l_int|1
)brace
comma
)brace
)brace
comma
multiline_comment|/* titan_210l */
(brace
l_int|1
comma
(brace
(brace
l_int|3
comma
op_minus
l_int|1
)brace
comma
)brace
)brace
comma
multiline_comment|/* avlab_1s1p     */
(brace
l_int|1
comma
(brace
(brace
l_int|1
comma
l_int|2
)brace
comma
)brace
)brace
comma
multiline_comment|/* avlab_1s1p_650 */
(brace
l_int|1
comma
(brace
(brace
l_int|1
comma
l_int|2
)brace
comma
)brace
)brace
comma
multiline_comment|/* avlab_1s1p_850 */
(brace
l_int|1
comma
(brace
(brace
l_int|1
comma
l_int|2
)brace
comma
)brace
)brace
comma
multiline_comment|/* avlab_1s2p     */
(brace
l_int|2
comma
(brace
(brace
l_int|1
comma
l_int|2
)brace
comma
(brace
l_int|3
comma
l_int|4
)brace
comma
)brace
)brace
comma
multiline_comment|/* avlab_1s2p_650 */
(brace
l_int|2
comma
(brace
(brace
l_int|1
comma
l_int|2
)brace
comma
(brace
l_int|3
comma
l_int|4
)brace
comma
)brace
)brace
comma
multiline_comment|/* avlab_1s2p_850 */
(brace
l_int|2
comma
(brace
(brace
l_int|1
comma
l_int|2
)brace
comma
(brace
l_int|3
comma
l_int|4
)brace
comma
)brace
)brace
comma
multiline_comment|/* avlab_2s1p     */
(brace
l_int|1
comma
(brace
(brace
l_int|2
comma
l_int|3
)brace
comma
)brace
)brace
comma
multiline_comment|/* avlab_2s1p_650 */
(brace
l_int|1
comma
(brace
(brace
l_int|2
comma
l_int|3
)brace
comma
)brace
)brace
comma
multiline_comment|/* avlab_2s1p_850 */
(brace
l_int|1
comma
(brace
(brace
l_int|2
comma
l_int|3
)brace
comma
)brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|parport_serial_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
multiline_comment|/* PCI cards */
(brace
id|PCI_VENDOR_ID_TITAN
comma
id|PCI_DEVICE_ID_TITAN_110L
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|titan_110l
)brace
comma
(brace
id|PCI_VENDOR_ID_TITAN
comma
id|PCI_DEVICE_ID_TITAN_210L
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|titan_210l
)brace
comma
multiline_comment|/* PCI_VENDOR_ID_AVLAB/Intek21 has another bunch of cards ...*/
(brace
l_int|0x14db
comma
l_int|0x2110
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|avlab_1s1p
)brace
comma
(brace
l_int|0x14db
comma
l_int|0x2111
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|avlab_1s1p_650
)brace
comma
(brace
l_int|0x14db
comma
l_int|0x2112
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|avlab_1s1p_850
)brace
comma
(brace
l_int|0x14db
comma
l_int|0x2140
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|avlab_1s2p
)brace
comma
(brace
l_int|0x14db
comma
l_int|0x2141
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|avlab_1s2p_650
)brace
comma
(brace
l_int|0x14db
comma
l_int|0x2142
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|avlab_1s2p_850
)brace
comma
(brace
l_int|0x14db
comma
l_int|0x2160
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|avlab_2s1p
)brace
comma
(brace
l_int|0x14db
comma
l_int|0x2161
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|avlab_2s1p_650
)brace
comma
(brace
l_int|0x14db
comma
l_int|0x2162
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|avlab_2s1p_850
)brace
comma
(brace
l_int|0
comma
)brace
multiline_comment|/* terminate list */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|parport_serial_pci_tbl
)paren
suffix:semicolon
DECL|struct|pci_board_no_ids
r_struct
id|pci_board_no_ids
(brace
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|num_ports
r_int
id|num_ports
suffix:semicolon
DECL|member|base_baud
r_int
id|base_baud
suffix:semicolon
DECL|member|uart_offset
r_int
id|uart_offset
suffix:semicolon
DECL|member|reg_shift
r_int
id|reg_shift
suffix:semicolon
DECL|member|init_fn
r_int
(paren
op_star
id|init_fn
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_board_no_ids
op_star
id|board
comma
r_int
id|enable
)paren
suffix:semicolon
DECL|member|first_uart_offset
r_int
id|first_uart_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pci_board_no_ids
id|pci_boards
(braket
)braket
id|__devinitdata
op_assign
(brace
multiline_comment|/*&n;&t; * PCI Flags, Number of Ports, Base (Maximum) Baud Rate,&n;&t; * Offset to get to next UART&squot;s registers,&n;&t; * Register shift to use for memory-mapped I/O,&n;&t; * Initialization function, first UART offset&n;&t; */
singleline_comment|// Cards not tested are marked n/t
singleline_comment|// If you have one of these cards and it works for you, please tell me..
multiline_comment|/* titan_110l */
(brace
id|SPCI_FL_BASE1
op_or
id|SPCI_FL_BASE_TABLE
comma
l_int|1
comma
l_int|921600
)brace
comma
multiline_comment|/* titan_210l */
(brace
id|SPCI_FL_BASE1
op_or
id|SPCI_FL_BASE_TABLE
comma
l_int|2
comma
l_int|921600
)brace
comma
multiline_comment|/* avlab_1s1p (n/t) */
(brace
id|SPCI_FL_BASE0
op_or
id|SPCI_FL_BASE_TABLE
comma
l_int|1
comma
l_int|115200
)brace
comma
multiline_comment|/* avlab_1s1p_650 (nt)*/
(brace
id|SPCI_FL_BASE0
op_or
id|SPCI_FL_BASE_TABLE
comma
l_int|1
comma
l_int|115200
)brace
comma
multiline_comment|/* avlab_1s1p_850 (nt)*/
(brace
id|SPCI_FL_BASE0
op_or
id|SPCI_FL_BASE_TABLE
comma
l_int|1
comma
l_int|115200
)brace
comma
multiline_comment|/* avlab_1s2p (n/t) */
(brace
id|SPCI_FL_BASE0
op_or
id|SPCI_FL_BASE_TABLE
comma
l_int|1
comma
l_int|115200
)brace
comma
multiline_comment|/* avlab_1s2p_650 (nt)*/
(brace
id|SPCI_FL_BASE0
op_or
id|SPCI_FL_BASE_TABLE
comma
l_int|1
comma
l_int|115200
)brace
comma
multiline_comment|/* avlab_1s2p_850 (nt)*/
(brace
id|SPCI_FL_BASE0
op_or
id|SPCI_FL_BASE_TABLE
comma
l_int|1
comma
l_int|115200
)brace
comma
multiline_comment|/* avlab_2s1p (n/t) */
(brace
id|SPCI_FL_BASE0
op_or
id|SPCI_FL_BASE_TABLE
comma
l_int|2
comma
l_int|115200
)brace
comma
multiline_comment|/* avlab_2s1p_650 (nt)*/
(brace
id|SPCI_FL_BASE0
op_or
id|SPCI_FL_BASE_TABLE
comma
l_int|2
comma
l_int|115200
)brace
comma
multiline_comment|/* avlab_2s1p_850 (nt)*/
(brace
id|SPCI_FL_BASE0
op_or
id|SPCI_FL_BASE_TABLE
comma
l_int|2
comma
l_int|115200
)brace
comma
)brace
suffix:semicolon
DECL|struct|parport_serial_private
r_struct
id|parport_serial_private
(brace
DECL|member|num_ser
r_int
id|num_ser
suffix:semicolon
DECL|member|line
r_int
id|line
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|ser
r_struct
id|pci_board_no_ids
id|ser
suffix:semicolon
DECL|member|num_par
r_int
id|num_par
suffix:semicolon
DECL|member|port
r_struct
id|parport
op_star
id|port
(braket
id|PARPORT_MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|get_pci_port
r_static
r_int
id|__devinit
id|get_pci_port
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_board_no_ids
op_star
id|board
comma
r_struct
id|serial_struct
op_star
id|req
comma
r_int
id|idx
)paren
(brace
r_int
r_int
id|port
suffix:semicolon
r_int
id|base_idx
suffix:semicolon
r_int
id|max_port
suffix:semicolon
r_int
id|offset
suffix:semicolon
id|base_idx
op_assign
id|SPCI_FL_GET_BASE
c_func
(paren
id|board-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|board-&gt;flags
op_amp
id|SPCI_FL_BASE_TABLE
)paren
id|base_idx
op_add_assign
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|board-&gt;flags
op_amp
id|SPCI_FL_REGION_SZ_CAP
)paren
(brace
id|max_port
op_assign
id|pci_resource_len
c_func
(paren
id|dev
comma
id|base_idx
)paren
op_div
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|max_port
)paren
r_return
l_int|1
suffix:semicolon
)brace
id|offset
op_assign
id|board-&gt;first_uart_offset
suffix:semicolon
multiline_comment|/* Timedia/SUNIX uses a mixture of BARs and offsets */
multiline_comment|/* Ugh, this is ugly as all hell --- TYT */
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_TIMEDIA
)paren
multiline_comment|/* 0x1409 */
r_switch
c_cond
(paren
id|idx
)paren
(brace
r_case
l_int|0
suffix:colon
id|base_idx
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|base_idx
op_assign
l_int|0
suffix:semicolon
id|offset
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|base_idx
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|base_idx
op_assign
l_int|1
suffix:semicolon
id|offset
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* BAR 2*/
r_case
l_int|5
suffix:colon
multiline_comment|/* BAR 3 */
r_case
l_int|6
suffix:colon
multiline_comment|/* BAR 4*/
r_case
l_int|7
suffix:colon
id|base_idx
op_assign
id|idx
op_minus
l_int|2
suffix:semicolon
multiline_comment|/* BAR 5*/
)brace
id|port
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
id|base_idx
)paren
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
(paren
id|board-&gt;flags
op_amp
id|SPCI_FL_BASE_TABLE
)paren
op_eq
l_int|0
)paren
id|port
op_add_assign
id|idx
op_star
(paren
id|board-&gt;uart_offset
ques
c_cond
id|board-&gt;uart_offset
suffix:colon
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_resource_flags
(paren
id|dev
comma
id|base_idx
)paren
op_amp
id|IORESOURCE_IO
)paren
(brace
r_int
id|high_bits_offset
op_assign
(paren
(paren
r_sizeof
(paren
r_int
)paren
op_minus
r_sizeof
(paren
r_int
)paren
)paren
op_star
l_int|8
)paren
suffix:semicolon
id|req-&gt;port
op_assign
id|port
suffix:semicolon
r_if
c_cond
(paren
id|high_bits_offset
)paren
id|req-&gt;port_high
op_assign
id|port
op_rshift
id|high_bits_offset
suffix:semicolon
r_else
id|req-&gt;port_high
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|req-&gt;io_type
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
id|req-&gt;iomem_base
op_assign
id|ioremap
c_func
(paren
id|port
comma
id|board-&gt;uart_offset
)paren
suffix:semicolon
id|req-&gt;iomem_reg_shift
op_assign
id|board-&gt;reg_shift
suffix:semicolon
id|req-&gt;port
op_assign
l_int|0
suffix:semicolon
r_return
id|req-&gt;iomem_base
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Register the serial port(s) of a PCI card. */
DECL|function|serial_register
r_static
r_int
id|__devinit
id|serial_register
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_struct
id|pci_board_no_ids
op_star
id|board
op_assign
op_amp
id|pci_boards
(braket
id|id-&gt;driver_data
)braket
suffix:semicolon
r_struct
id|parport_serial_private
op_star
id|priv
op_assign
id|pci_get_drvdata
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|serial_struct
id|serial_req
suffix:semicolon
r_int
id|base_baud
suffix:semicolon
r_int
id|k
suffix:semicolon
r_int
id|success
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;ser
op_assign
op_star
id|board
suffix:semicolon
r_if
c_cond
(paren
id|board-&gt;init_fn
op_logical_and
(paren
(paren
id|board-&gt;init_fn
)paren
(paren
id|dev
comma
id|board
comma
l_int|1
)paren
op_ne
l_int|0
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|base_baud
op_assign
id|board-&gt;base_baud
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base_baud
)paren
id|base_baud
op_assign
id|BASE_BAUD
suffix:semicolon
id|memset
(paren
op_amp
id|serial_req
comma
l_int|0
comma
r_sizeof
(paren
id|serial_req
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|board-&gt;num_ports
suffix:semicolon
id|k
op_increment
)paren
(brace
r_int
id|line
suffix:semicolon
id|serial_req.irq
op_assign
id|dev-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|get_pci_port
(paren
id|dev
comma
id|board
comma
op_amp
id|serial_req
comma
id|k
)paren
)paren
r_break
suffix:semicolon
id|serial_req.flags
op_assign
id|ASYNC_SKIP_TEST
op_or
id|ASYNC_AUTOPROBE
suffix:semicolon
id|line
op_assign
id|register_serial
(paren
op_amp
id|serial_req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
OL
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;parport_serial: register_serial failed&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|priv-&gt;line
(braket
id|priv-&gt;num_ser
op_increment
)braket
op_assign
id|line
suffix:semicolon
id|success
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|success
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Register the parallel port(s) of a PCI card. */
DECL|function|parport_register
r_static
r_int
id|__devinit
id|parport_register
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_struct
id|parport_serial_private
op_star
id|priv
op_assign
id|pci_get_drvdata
(paren
id|dev
)paren
suffix:semicolon
r_int
id|i
op_assign
id|id-&gt;driver_data
comma
id|n
suffix:semicolon
r_int
id|success
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|cards
(braket
id|i
)braket
dot
id|numports
suffix:semicolon
id|n
op_increment
)paren
(brace
r_struct
id|parport
op_star
id|port
suffix:semicolon
r_int
id|lo
op_assign
id|cards
(braket
id|i
)braket
dot
id|addr
(braket
id|n
)braket
dot
id|lo
suffix:semicolon
r_int
id|hi
op_assign
id|cards
(braket
id|i
)braket
dot
id|addr
(braket
id|n
)braket
dot
id|hi
suffix:semicolon
r_int
r_int
id|io_lo
comma
id|io_hi
suffix:semicolon
id|io_lo
op_assign
id|pci_resource_start
(paren
id|dev
comma
id|lo
)paren
suffix:semicolon
id|io_hi
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hi
op_ge
l_int|0
)paren
op_logical_and
(paren
id|hi
op_le
l_int|6
)paren
)paren
id|io_hi
op_assign
id|pci_resource_start
(paren
id|dev
comma
id|hi
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|hi
OG
l_int|6
)paren
id|io_lo
op_add_assign
id|hi
suffix:semicolon
multiline_comment|/* Reinterpret the meaning of&n;                                        &quot;hi&quot; as an offset (see SYBA&n;                                        def.) */
multiline_comment|/* TODO: test if sharing interrupts works */
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;PCI parallel port detected: %04x:%04x, &quot;
l_string|&quot;I/O at %#lx(%#lx)&bslash;n&quot;
comma
id|parport_serial_pci_tbl
(braket
id|i
)braket
dot
id|vendor
comma
id|parport_serial_pci_tbl
(braket
id|i
)braket
dot
id|device
comma
id|io_lo
comma
id|io_hi
)paren
suffix:semicolon
id|port
op_assign
id|parport_pc_probe_port
(paren
id|io_lo
comma
id|io_hi
comma
id|PARPORT_IRQ_NONE
comma
id|PARPORT_DMA_NONE
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port
)paren
(brace
id|priv-&gt;port
(braket
id|priv-&gt;num_par
op_increment
)braket
op_assign
id|port
suffix:semicolon
id|success
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|success
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|parport_serial_pci_probe
r_static
r_int
id|__devinit
id|parport_serial_pci_probe
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_struct
id|parport_serial_private
op_star
id|priv
suffix:semicolon
r_int
id|err
suffix:semicolon
id|priv
op_assign
id|kmalloc
(paren
r_sizeof
op_star
id|priv
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|priv-&gt;num_ser
op_assign
id|priv-&gt;num_par
op_assign
l_int|0
suffix:semicolon
id|pci_set_drvdata
(paren
id|dev
comma
id|priv
)paren
suffix:semicolon
id|err
op_assign
id|pci_enable_device
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
id|pci_set_drvdata
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
(paren
id|priv
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|parport_register
(paren
id|dev
comma
id|id
)paren
)paren
(brace
id|pci_set_drvdata
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
(paren
id|priv
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serial_register
(paren
id|dev
comma
id|id
)paren
)paren
(brace
r_int
id|i
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
id|priv-&gt;num_par
suffix:semicolon
id|i
op_increment
)paren
id|parport_pc_unregister_port
(paren
id|priv-&gt;port
(braket
id|i
)braket
)paren
suffix:semicolon
id|pci_set_drvdata
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
(paren
id|priv
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parport_serial_pci_remove
r_static
r_void
id|__devexit
id|parport_serial_pci_remove
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|parport_serial_private
op_star
id|priv
op_assign
id|pci_get_drvdata
(paren
id|dev
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
singleline_comment|// Serial ports
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|priv-&gt;num_ser
suffix:semicolon
id|i
op_increment
)paren
(brace
id|unregister_serial
(paren
id|priv-&gt;line
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;ser.init_fn
)paren
(paren
id|priv-&gt;ser.init_fn
)paren
(paren
id|dev
comma
op_amp
id|priv-&gt;ser
comma
l_int|0
)paren
suffix:semicolon
)brace
id|pci_set_drvdata
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// Parallel ports
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|priv-&gt;num_par
suffix:semicolon
id|i
op_increment
)paren
id|parport_pc_unregister_port
(paren
id|priv-&gt;port
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
(paren
id|priv
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|parport_serial_pci_driver
r_static
r_struct
id|pci_driver
id|parport_serial_pci_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;parport_serial&quot;
comma
id|id_table
suffix:colon
id|parport_serial_pci_tbl
comma
id|probe
suffix:colon
id|parport_serial_pci_probe
comma
id|remove
suffix:colon
id|parport_serial_pci_remove
comma
)brace
suffix:semicolon
DECL|function|parport_serial_init
r_static
r_int
id|__init
id|parport_serial_init
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
(paren
op_amp
id|parport_serial_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|parport_serial_exit
r_static
r_void
id|__exit
id|parport_serial_exit
(paren
r_void
)paren
(brace
id|pci_unregister_driver
(paren
op_amp
id|parport_serial_pci_driver
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Tim Waugh &lt;twaugh@redhat.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for common parallel+serial multi-I/O PCI cards&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|parport_serial_init
id|module_init
c_func
(paren
id|parport_serial_init
)paren
suffix:semicolon
DECL|variable|parport_serial_exit
id|module_exit
c_func
(paren
id|parport_serial_exit
)paren
suffix:semicolon
eof
