multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/byteorder/swab.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
macro_line|#include &lt;asm/sn/pci/bridge.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/pci/pci_defs.h&gt;
macro_line|#include &lt;asm/sn/prio.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xbow.h&gt;
macro_line|#include &lt;asm/sn/ioc3.h&gt;
macro_line|#include &lt;asm/sn/eeprom.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
r_extern
id|pcibr_info_t
id|pcibr_info_get
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_uint64
id|pcibr_config_get
c_func
(paren
id|devfs_handle_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_uint64
id|do_pcibr_config_get
c_func
(paren
r_int
comma
id|cfg_p
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|pcibr_config_set
c_func
(paren
id|devfs_handle_t
comma
r_int
comma
r_int
comma
r_uint64
)paren
suffix:semicolon
r_void
id|do_pcibr_config_set
c_func
(paren
r_int
comma
id|cfg_p
comma
r_int
comma
r_int
comma
r_uint64
)paren
suffix:semicolon
r_static
r_void
id|swap_do_pcibr_config_set
c_func
(paren
id|cfg_p
comma
r_int
comma
r_int
comma
r_uint64
)paren
suffix:semicolon
macro_line|#ifdef LITTLE_ENDIAN
multiline_comment|/*&n; * on sn-ia we need to twiddle the the addresses going out&n; * the pci bus because we use the unswizzled synergy space&n; * (the alternative is to use the swizzled synergy space&n; * and byte swap the data)&n; */
DECL|macro|CB
mdefine_line|#define CB(b,r) (((volatile uint8_t *) b)[((r)^4)])
DECL|macro|CS
mdefine_line|#define CS(b,r) (((volatile uint16_t *) b)[((r^4)/2)])
DECL|macro|CW
mdefine_line|#define CW(b,r) (((volatile uint32_t *) b)[((r^4)/4)])
DECL|macro|CBP
mdefine_line|#define&t;CBP(b,r) (((volatile uint8_t *) b)[(r)^3])
DECL|macro|CSP
mdefine_line|#define&t;CSP(b,r) (((volatile uint16_t *) b)[((r)/2)^1])
DECL|macro|CWP
mdefine_line|#define&t;CWP(b,r) (((volatile uint32_t *) b)[(r)/4])
DECL|macro|SCB
mdefine_line|#define SCB(b,r) (((volatile uint8_t *) b)[((r)^3)])
DECL|macro|SCS
mdefine_line|#define SCS(b,r) (((volatile uint16_t *) b)[((r^2)/2)])
DECL|macro|SCW
mdefine_line|#define SCW(b,r) (((volatile uint32_t *) b)[((r)/4)])
macro_line|#else
DECL|macro|CB
mdefine_line|#define&t;CB(b,r)&t;(((volatile uint8_t *) cfgbase)[(r)^3])
DECL|macro|CS
mdefine_line|#define&t;CS(b,r)&t;(((volatile uint16_t *) cfgbase)[((r)/2)^1])
DECL|macro|CW
mdefine_line|#define&t;CW(b,r)&t;(((volatile uint32_t *) cfgbase)[(r)/4])
macro_line|#endif
multiline_comment|/*&n; * Return a config space address for given slot / func / offset.  Note the&n; * returned pointer is a 32bit word (ie. cfg_p) aligned pointer pointing to&n; * the 32bit word that contains the &quot;offset&quot; byte.&n; */
id|cfg_p
DECL|function|pcibr_func_config_addr
id|pcibr_func_config_addr
c_func
(paren
id|bridge_t
op_star
id|bridge
comma
id|pciio_bus_t
id|bus
comma
id|pciio_slot_t
id|slot
comma
id|pciio_function_t
id|func
comma
r_int
id|offset
)paren
(brace
multiline_comment|/*&n;&t; * Type 1 config space&n;&t; */
r_if
c_cond
(paren
id|bus
OG
l_int|0
)paren
(brace
id|bridge-&gt;b_pci_cfg
op_assign
(paren
(paren
id|bus
op_lshift
l_int|16
)paren
op_or
(paren
id|slot
op_lshift
l_int|11
)paren
)paren
suffix:semicolon
r_return
op_amp
id|bridge-&gt;b_type1_cfg.f
(braket
id|func
)braket
dot
id|l
(braket
(paren
id|offset
)paren
)braket
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Type 0 config space&n;&t; */
r_if
c_cond
(paren
id|is_pic
c_func
(paren
id|bridge
)paren
)paren
id|slot
op_increment
suffix:semicolon
r_return
op_amp
id|bridge-&gt;b_type0_cfg_dev
(braket
id|slot
)braket
dot
id|f
(braket
id|func
)braket
dot
id|l
(braket
id|offset
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Return config space address for given slot / offset.  Note the returned&n; * pointer is a 32bit word (ie. cfg_p) aligned pointer pointing to the&n; * 32bit word that contains the &quot;offset&quot; byte.&n; */
id|cfg_p
DECL|function|pcibr_slot_config_addr
id|pcibr_slot_config_addr
c_func
(paren
id|bridge_t
op_star
id|bridge
comma
id|pciio_slot_t
id|slot
comma
r_int
id|offset
)paren
(brace
r_return
id|pcibr_func_config_addr
c_func
(paren
id|bridge
comma
l_int|0
comma
id|slot
comma
l_int|0
comma
id|offset
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return config space data for given slot / offset&n; */
r_int
DECL|function|pcibr_slot_config_get
id|pcibr_slot_config_get
c_func
(paren
id|bridge_t
op_star
id|bridge
comma
id|pciio_slot_t
id|slot
comma
r_int
id|offset
)paren
(brace
id|cfg_p
id|cfg_base
suffix:semicolon
id|cfg_base
op_assign
id|pcibr_slot_config_addr
c_func
(paren
id|bridge
comma
id|slot
comma
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|do_pcibr_config_get
c_func
(paren
id|is_pic
c_func
(paren
id|bridge
)paren
comma
id|cfg_base
comma
id|offset
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return config space data for given slot / func / offset&n; */
r_int
DECL|function|pcibr_func_config_get
id|pcibr_func_config_get
c_func
(paren
id|bridge_t
op_star
id|bridge
comma
id|pciio_slot_t
id|slot
comma
id|pciio_function_t
id|func
comma
r_int
id|offset
)paren
(brace
id|cfg_p
id|cfg_base
suffix:semicolon
id|cfg_base
op_assign
id|pcibr_func_config_addr
c_func
(paren
id|bridge
comma
l_int|0
comma
id|slot
comma
id|func
comma
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|do_pcibr_config_get
c_func
(paren
id|is_pic
c_func
(paren
id|bridge
)paren
comma
id|cfg_base
comma
id|offset
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set config space data for given slot / offset&n; */
r_void
DECL|function|pcibr_slot_config_set
id|pcibr_slot_config_set
c_func
(paren
id|bridge_t
op_star
id|bridge
comma
id|pciio_slot_t
id|slot
comma
r_int
id|offset
comma
r_int
id|val
)paren
(brace
id|cfg_p
id|cfg_base
suffix:semicolon
id|cfg_base
op_assign
id|pcibr_slot_config_addr
c_func
(paren
id|bridge
comma
id|slot
comma
l_int|0
)paren
suffix:semicolon
id|do_pcibr_config_set
c_func
(paren
id|is_pic
c_func
(paren
id|bridge
)paren
comma
id|cfg_base
comma
id|offset
comma
r_sizeof
(paren
r_int
)paren
comma
id|val
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set config space data for given slot / func / offset&n; */
r_void
DECL|function|pcibr_func_config_set
id|pcibr_func_config_set
c_func
(paren
id|bridge_t
op_star
id|bridge
comma
id|pciio_slot_t
id|slot
comma
id|pciio_function_t
id|func
comma
r_int
id|offset
comma
r_int
id|val
)paren
(brace
id|cfg_p
id|cfg_base
suffix:semicolon
id|cfg_base
op_assign
id|pcibr_func_config_addr
c_func
(paren
id|bridge
comma
l_int|0
comma
id|slot
comma
id|func
comma
l_int|0
)paren
suffix:semicolon
id|do_pcibr_config_set
c_func
(paren
id|is_pic
c_func
(paren
id|bridge
)paren
comma
id|cfg_base
comma
id|offset
comma
r_sizeof
(paren
r_int
)paren
comma
id|val
)paren
suffix:semicolon
)brace
DECL|variable|pcibr_config_debug
r_int
id|pcibr_config_debug
op_assign
l_int|0
suffix:semicolon
id|cfg_p
DECL|function|pcibr_config_addr
id|pcibr_config_addr
c_func
(paren
id|devfs_handle_t
id|conn
comma
r_int
id|reg
)paren
(brace
id|pcibr_info_t
id|pcibr_info
suffix:semicolon
id|pciio_bus_t
id|pciio_bus
suffix:semicolon
id|pciio_slot_t
id|pciio_slot
suffix:semicolon
id|pciio_function_t
id|pciio_func
suffix:semicolon
id|pcibr_soft_t
id|pcibr_soft
suffix:semicolon
id|bridge_t
op_star
id|bridge
suffix:semicolon
id|cfg_p
id|cfgbase
op_assign
(paren
id|cfg_p
)paren
l_int|0
suffix:semicolon
id|pciio_info_t
id|pciio_info
suffix:semicolon
id|pciio_info
op_assign
id|pciio_info_get
c_func
(paren
id|conn
)paren
suffix:semicolon
id|pcibr_info
op_assign
id|pcibr_info_get
c_func
(paren
id|conn
)paren
suffix:semicolon
multiline_comment|/*&n;     * Determine the PCI bus/slot/func to generate a config address for.&n;     */
r_if
c_cond
(paren
id|pciio_info_type1_get
c_func
(paren
id|pciio_info
)paren
)paren
(brace
multiline_comment|/*&n;&t; * Conn is a vhdl which uses TYPE 1 addressing explicitly passed &n;&t; * in reg.&n;&t; */
id|pciio_bus
op_assign
id|PCI_TYPE1_BUS
c_func
(paren
id|reg
)paren
suffix:semicolon
id|pciio_slot
op_assign
id|PCI_TYPE1_SLOT
c_func
(paren
id|reg
)paren
suffix:semicolon
id|pciio_func
op_assign
id|PCI_TYPE1_FUNC
c_func
(paren
id|reg
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|pciio_bus
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#if 0
)brace
r_else
r_if
c_cond
(paren
id|conn
op_ne
id|pciio_info_hostdev_get
c_func
(paren
id|pciio_info
)paren
)paren
(brace
multiline_comment|/*&n;&t; * Conn is on a subordinate bus, so get bus/slot/func directly from&n;&t; * its pciio_info_t structure.&n;&t; */
id|pciio_bus
op_assign
id|pciio_info-&gt;c_bus
suffix:semicolon
id|pciio_slot
op_assign
id|pciio_info-&gt;c_slot
suffix:semicolon
id|pciio_func
op_assign
id|pciio_info-&gt;c_func
suffix:semicolon
r_if
c_cond
(paren
id|pciio_func
op_eq
id|PCIIO_FUNC_NONE
)paren
(brace
id|pciio_func
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
multiline_comment|/*&n;&t; * Conn is directly connected to the host bus.  PCI bus number is&n;&t; * hardcoded to 0 (even though it may have a logical bus number != 0)&n;&t; * and slot/function are derived from the pcibr_info_t associated&n;&t; * with the device.&n;&t; */
id|pciio_bus
op_assign
l_int|0
suffix:semicolon
id|pciio_slot
op_assign
id|PCIBR_INFO_SLOT_GET_INT
c_func
(paren
id|pcibr_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pciio_slot
op_eq
id|PCIIO_SLOT_NONE
)paren
id|pciio_slot
op_assign
id|PCI_TYPE1_SLOT
c_func
(paren
id|reg
)paren
suffix:semicolon
id|pciio_func
op_assign
id|pcibr_info-&gt;f_func
suffix:semicolon
r_if
c_cond
(paren
id|pciio_func
op_eq
id|PCIIO_FUNC_NONE
)paren
id|pciio_func
op_assign
id|PCI_TYPE1_FUNC
c_func
(paren
id|reg
)paren
suffix:semicolon
)brace
id|pcibr_soft
op_assign
(paren
id|pcibr_soft_t
)paren
id|pcibr_info-&gt;f_mfast
suffix:semicolon
id|bridge
op_assign
id|pcibr_soft-&gt;bs_base
suffix:semicolon
id|cfgbase
op_assign
id|pcibr_func_config_addr
c_func
(paren
id|bridge
comma
id|pciio_bus
comma
id|pciio_slot
comma
id|pciio_func
comma
l_int|0
)paren
suffix:semicolon
r_return
id|cfgbase
suffix:semicolon
)brace
r_extern
r_int
r_char
id|Is_pic_on_this_nasid
(braket
)braket
suffix:semicolon
r_uint64
DECL|function|pcibr_config_get
id|pcibr_config_get
c_func
(paren
id|devfs_handle_t
id|conn
comma
r_int
id|reg
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|Is_pic_on_this_nasid
(braket
id|NASID_GET
c_func
(paren
(paren
id|pcibr_config_addr
c_func
(paren
id|conn
comma
id|reg
)paren
)paren
)paren
)braket
)paren
r_return
id|do_pcibr_config_get
c_func
(paren
l_int|0
comma
id|pcibr_config_addr
c_func
(paren
id|conn
comma
id|reg
)paren
comma
id|PCI_TYPE1_REG
c_func
(paren
id|reg
)paren
comma
id|size
)paren
suffix:semicolon
r_else
r_return
id|do_pcibr_config_get
c_func
(paren
l_int|1
comma
id|pcibr_config_addr
c_func
(paren
id|conn
comma
id|reg
)paren
comma
id|PCI_TYPE1_REG
c_func
(paren
id|reg
)paren
comma
id|size
)paren
suffix:semicolon
)brace
r_uint64
DECL|function|do_pcibr_config_get
id|do_pcibr_config_get
c_func
(paren
r_int
id|pic
comma
id|cfg_p
id|cfgbase
comma
r_int
id|reg
comma
r_int
id|size
)paren
(brace
r_int
id|value
suffix:semicolon
r_if
c_cond
(paren
id|pic
)paren
(brace
id|value
op_assign
id|CWP
c_func
(paren
id|cfgbase
comma
id|reg
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|io_get_sh_swapper
c_func
(paren
id|NASID_GET
c_func
(paren
id|cfgbase
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;     * Shub Swapper on - 0 returns PCI Offset 0 but byte swapped!&n;&t;     * Do not swizzle address and byte swap the result.&n;&t;     */
id|value
op_assign
id|SCW
c_func
(paren
id|cfgbase
comma
id|reg
)paren
suffix:semicolon
id|value
op_assign
id|__swab32
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_else
(brace
id|value
op_assign
id|CW
c_func
(paren
id|cfgbase
comma
id|reg
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|reg
op_amp
l_int|3
)paren
id|value
op_rshift_assign
l_int|8
op_star
(paren
id|reg
op_amp
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|4
)paren
id|value
op_and_assign
(paren
l_int|1
op_lshift
(paren
l_int|8
op_star
id|size
)paren
)paren
op_minus
l_int|1
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
r_void
DECL|function|pcibr_config_set
id|pcibr_config_set
c_func
(paren
id|devfs_handle_t
id|conn
comma
r_int
id|reg
comma
r_int
id|size
comma
r_uint64
id|value
)paren
(brace
r_if
c_cond
(paren
id|Is_pic_on_this_nasid
(braket
id|NASID_GET
c_func
(paren
(paren
id|pcibr_config_addr
c_func
(paren
id|conn
comma
id|reg
)paren
)paren
)paren
)braket
)paren
id|do_pcibr_config_set
c_func
(paren
l_int|1
comma
id|pcibr_config_addr
c_func
(paren
id|conn
comma
id|reg
)paren
comma
id|PCI_TYPE1_REG
c_func
(paren
id|reg
)paren
comma
id|size
comma
id|value
)paren
suffix:semicolon
r_else
id|swap_do_pcibr_config_set
c_func
(paren
id|pcibr_config_addr
c_func
(paren
id|conn
comma
id|reg
)paren
comma
id|PCI_TYPE1_REG
c_func
(paren
id|reg
)paren
comma
id|size
comma
id|value
)paren
suffix:semicolon
)brace
r_void
DECL|function|do_pcibr_config_set
id|do_pcibr_config_set
c_func
(paren
r_int
id|pic
comma
id|cfg_p
id|cfgbase
comma
r_int
id|reg
comma
r_int
id|size
comma
r_uint64
id|value
)paren
(brace
r_if
c_cond
(paren
id|pic
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|CBP
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|reg
op_amp
l_int|1
)paren
(brace
id|CBP
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
id|CBP
c_func
(paren
id|cfgbase
comma
id|reg
op_plus
l_int|1
)paren
op_assign
id|value
op_rshift
l_int|8
suffix:semicolon
)brace
r_else
id|CSP
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
id|reg
op_amp
l_int|1
)paren
(brace
id|CBP
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
id|CSP
c_func
(paren
id|cfgbase
comma
(paren
id|reg
op_plus
l_int|1
)paren
)paren
op_assign
id|value
op_rshift
l_int|8
suffix:semicolon
)brace
r_else
(brace
id|CSP
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
id|CBP
c_func
(paren
id|cfgbase
comma
id|reg
op_plus
l_int|2
)paren
op_assign
id|value
op_rshift
l_int|16
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|CWP
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|CB
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|reg
op_amp
l_int|1
)paren
(brace
id|CB
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
id|CB
c_func
(paren
id|cfgbase
comma
id|reg
op_plus
l_int|1
)paren
op_assign
id|value
op_rshift
l_int|8
suffix:semicolon
)brace
r_else
id|CS
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
id|reg
op_amp
l_int|1
)paren
(brace
id|CB
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
id|CS
c_func
(paren
id|cfgbase
comma
(paren
id|reg
op_plus
l_int|1
)paren
)paren
op_assign
id|value
op_rshift
l_int|8
suffix:semicolon
)brace
r_else
(brace
id|CS
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
id|CB
c_func
(paren
id|cfgbase
comma
id|reg
op_plus
l_int|2
)paren
op_assign
id|value
op_rshift
l_int|16
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|CW
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_void
DECL|function|swap_do_pcibr_config_set
id|swap_do_pcibr_config_set
c_func
(paren
id|cfg_p
id|cfgbase
comma
r_int
id|reg
comma
r_int
id|size
comma
r_uint64
id|value
)paren
(brace
r_uint64
id|temp_value
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|SCB
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|temp_value
op_assign
id|__swab16
c_func
(paren
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
l_int|1
)paren
(brace
id|SCB
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|temp_value
suffix:semicolon
id|SCB
c_func
(paren
id|cfgbase
comma
id|reg
op_plus
l_int|1
)paren
op_assign
id|temp_value
op_rshift
l_int|8
suffix:semicolon
)brace
r_else
id|SCS
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|temp_value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|temp_value
op_assign
id|__swab32
c_func
(paren
id|value
)paren
suffix:semicolon
id|SCW
c_func
(paren
id|cfgbase
comma
id|reg
)paren
op_assign
id|temp_value
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
eof
