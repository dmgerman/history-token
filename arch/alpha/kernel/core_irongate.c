multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/core_irongate.c&n; *&n; * Based on code written by David A. Rusling (david.rusling@reo.mts.dec.com).&n; *&n; *&t;Copyright (C) 1999 Alpha Processor, Inc.,&n; *&t;&t;(David Daniel, Stig Telfer, Soohoon Lee)&n; *&n; * Code common to all IRONGATE core logic chips.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE inline
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/core_irongate.h&gt;
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
DECL|macro|DEBUG_IRONGATE
macro_line|#undef DEBUG_IRONGATE &t;&t;/* define to enable verbose Irongate debug */
DECL|macro|IRONGATE_DEFAULT_AGP_APER_SIZE
mdefine_line|#define IRONGATE_DEFAULT_AGP_APER_SIZE&t;(256*1024*1024) /* 256MB */
multiline_comment|/*&n; * BIOS32-style PCI interface:&n; */
DECL|macro|DEBUG_CONFIG
mdefine_line|#define DEBUG_CONFIG 0
macro_line|#if DEBUG_CONFIG
DECL|macro|DBG_CFG
macro_line|# define DBG_CFG(args)&t;printk args
macro_line|#else
DECL|macro|DBG_CFG
macro_line|# define DBG_CFG(args)
macro_line|#endif
multiline_comment|/*&n; * Given a bus, device, and function number, compute resulting&n; * configuration space address accordingly.  It is therefore not safe&n; * to have concurrent invocations to configuration space access&n; * routines, but there really shouldn&squot;t be any need for this.&n; *&n; *&t;addr[31:24]&t;&t;reserved&n; *&t;addr[23:16]&t;&t;bus number (8 bits = 128 possible buses)&n; *&t;addr[15:11]&t;&t;Device number (5 bits)&n; *&t;addr[10: 8]&t;&t;function number&n; *&t;addr[ 7: 2]&t;&t;register number&n; *&n; * For IRONGATE:&n; *    if (bus = addr[23:16]) == 0&n; *    then&n; *&t;  type 0 config cycle:&n; *&t;      addr_on_pci[31:11] = id selection for device = addr[15:11]&n; *&t;      addr_on_pci[10: 2] = addr[10: 2] ???&n; *&t;      addr_on_pci[ 1: 0] = 00&n; *    else&n; *&t;  type 1 config cycle (pass on with no decoding):&n; *&t;      addr_on_pci[31:24] = 0&n; *&t;      addr_on_pci[23: 2] = addr[23: 2]&n; *&t;      addr_on_pci[ 1: 0] = 01&n; *    fi&n; *&n; * Notes:&n; *&t;The function number selects which function of a multi-function device&n; *&t;(e.g., SCSI and Ethernet).&n; *&n; *&t;The register selects a DWORD (32 bit) register offset.&t;Hence it&n; *&t;doesn&squot;t get shifted by 2 bits as we want to &quot;drop&quot; the bottom two&n; *&t;bits.&n; */
r_static
r_int
DECL|function|mk_conf_addr
id|mk_conf_addr
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
r_int
r_int
op_star
id|pci_addr
comma
r_int
r_char
op_star
id|type1
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|u8
id|bus
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
id|u8
id|device_fn
op_assign
id|dev-&gt;devfn
suffix:semicolon
id|DBG_CFG
c_func
(paren
(paren
l_string|&quot;mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x, &quot;
l_string|&quot;pci_addr=0x%p, type1=0x%p)&bslash;n&quot;
comma
id|bus
comma
id|device_fn
comma
id|where
comma
id|pci_addr
comma
id|type1
)paren
)paren
suffix:semicolon
op_star
id|type1
op_assign
(paren
id|bus
op_ne
l_int|0
)paren
suffix:semicolon
id|addr
op_assign
(paren
id|bus
op_lshift
l_int|16
)paren
op_or
(paren
id|device_fn
op_lshift
l_int|8
)paren
op_or
id|where
suffix:semicolon
id|addr
op_or_assign
id|IRONGATE_CONF
suffix:semicolon
op_star
id|pci_addr
op_assign
id|addr
suffix:semicolon
id|DBG_CFG
c_func
(paren
(paren
l_string|&quot;mk_conf_addr: returning pci_addr 0x%lx&bslash;n&quot;
comma
id|addr
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_read_config_byte
id|irongate_read_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
op_star
id|value
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|value
op_assign
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_read_config_word
id|irongate_read_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
op_star
id|value
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|value
op_assign
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_read_config_dword
id|irongate_read_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
op_star
id|value
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|value
op_assign
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_write_config_byte
id|irongate_write_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
id|value
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|__kernel_stb
c_func
(paren
id|value
comma
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_write_config_word
id|irongate_write_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
id|value
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|__kernel_stw
c_func
(paren
id|value
comma
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_write_config_dword
id|irongate_write_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
id|value
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|value
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|irongate_pci_ops
r_struct
id|pci_ops
id|irongate_pci_ops
op_assign
(brace
id|read_byte
suffix:colon
id|irongate_read_config_byte
comma
id|read_word
suffix:colon
id|irongate_read_config_word
comma
id|read_dword
suffix:colon
id|irongate_read_config_dword
comma
id|write_byte
suffix:colon
id|irongate_write_config_byte
comma
id|write_word
suffix:colon
id|irongate_write_config_word
comma
id|write_dword
suffix:colon
id|irongate_write_config_dword
)brace
suffix:semicolon
"&f;"
macro_line|#ifdef DEBUG_IRONGATE
r_static
r_void
DECL|function|irongate_register_dump
id|irongate_register_dump
c_func
(paren
r_const
r_char
op_star
id|function_name
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Irongate registers:&bslash;n&quot;
l_string|&quot;&bslash;tFunction 0:&bslash;n&quot;
l_string|&quot;&bslash;tdev_vendor&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tstat_cmd&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tclass&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tlatency&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbar0&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbar1&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbar2&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[1]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[2]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[3]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[4]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[5]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tcapptr&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd1[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd1[1]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbacsr10&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbacsr32&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbacsr54&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd2[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tdrammap&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tdramtm&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tdramms&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd3[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbiu0&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbiusip&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd4[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd4[1]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tmro&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd5[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd5[1]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd5[2]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;twhami&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tpciarb&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tpcicfg&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd6[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd6[1]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd6[2]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd6[3]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd6[4]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tagpcap&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tagpstat&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tagpcmd&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tagpva&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tagpmode&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;n&bslash;tFunction 1:&bslash;n&quot;
l_string|&quot;&bslash;tdev_vendor:&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tcmd_status:&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trevid_etc :&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;thtype_etc :&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[0] :&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[1] :&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbus_nmbers:&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tio_baselim:&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tmem_bselim:&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tpf_baselib:&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd1[0] :&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd1[1] :&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tio_baselim:&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd2[0] :&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd2[1] :&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tinterrupt :&bslash;t0x%08x&bslash;n&quot;
comma
id|function_name
comma
id|IRONGATE0-&gt;dev_vendor
comma
id|IRONGATE0-&gt;stat_cmd
comma
id|IRONGATE0
op_member_access_from_pointer
r_class
comma
id|IRONGATE0-&gt;latency
comma
id|IRONGATE0-&gt;bar0
comma
id|IRONGATE0-&gt;bar1
comma
id|IRONGATE0-&gt;bar2
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|1
)braket
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|2
)braket
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|3
)braket
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|4
)braket
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|5
)braket
comma
id|IRONGATE0-&gt;capptr
comma
id|IRONGATE0-&gt;rsrvd1
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;rsrvd1
(braket
l_int|1
)braket
comma
id|IRONGATE0-&gt;bacsr10
comma
id|IRONGATE0-&gt;bacsr32
comma
id|IRONGATE0-&gt;bacsr54
comma
id|IRONGATE0-&gt;rsrvd2
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;drammap
comma
id|IRONGATE0-&gt;dramtm
comma
id|IRONGATE0-&gt;dramms
comma
id|IRONGATE0-&gt;rsrvd3
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;biu0
comma
id|IRONGATE0-&gt;biusip
comma
id|IRONGATE0-&gt;rsrvd4
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;rsrvd4
(braket
l_int|1
)braket
comma
id|IRONGATE0-&gt;mro
comma
id|IRONGATE0-&gt;rsrvd5
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;rsrvd5
(braket
l_int|1
)braket
comma
id|IRONGATE0-&gt;rsrvd5
(braket
l_int|2
)braket
comma
id|IRONGATE0-&gt;whami
comma
id|IRONGATE0-&gt;pciarb
comma
id|IRONGATE0-&gt;pcicfg
comma
id|IRONGATE0-&gt;rsrvd6
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;rsrvd6
(braket
l_int|1
)braket
comma
id|IRONGATE0-&gt;rsrvd6
(braket
l_int|2
)braket
comma
id|IRONGATE0-&gt;rsrvd6
(braket
l_int|3
)braket
comma
id|IRONGATE0-&gt;rsrvd6
(braket
l_int|4
)braket
comma
id|IRONGATE0-&gt;agpcap
comma
id|IRONGATE0-&gt;agpstat
comma
id|IRONGATE0-&gt;agpcmd
comma
id|IRONGATE0-&gt;agpva
comma
id|IRONGATE0-&gt;agpmode
comma
id|IRONGATE1-&gt;dev_vendor
comma
id|IRONGATE1-&gt;stat_cmd
comma
id|IRONGATE1
op_member_access_from_pointer
r_class
comma
id|IRONGATE1-&gt;htype
comma
id|IRONGATE1-&gt;rsrvd0
(braket
l_int|0
)braket
comma
id|IRONGATE1-&gt;rsrvd0
(braket
l_int|1
)braket
comma
id|IRONGATE1-&gt;busnos
comma
id|IRONGATE1-&gt;io_baselim_regs
comma
id|IRONGATE1-&gt;mem_baselim
comma
id|IRONGATE1-&gt;pfmem_baselim
comma
id|IRONGATE1-&gt;rsrvd1
(braket
l_int|0
)braket
comma
id|IRONGATE1-&gt;rsrvd1
(braket
l_int|1
)braket
comma
id|IRONGATE1-&gt;io_baselim
comma
id|IRONGATE1-&gt;rsrvd2
(braket
l_int|0
)braket
comma
id|IRONGATE1-&gt;rsrvd2
(braket
l_int|1
)braket
comma
id|IRONGATE1-&gt;interrupt
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|irongate_register_dump
mdefine_line|#define irongate_register_dump(x)
macro_line|#endif
r_int
DECL|function|irongate_pci_clr_err
id|irongate_pci_clr_err
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|nmi_ctl
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|IRONGATE_jd
suffix:semicolon
id|again
suffix:colon
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;stat_cmd
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Iron stat_cmd %x&bslash;n&quot;
comma
id|IRONGATE_jd
)paren
suffix:semicolon
id|IRONGATE0-&gt;stat_cmd
op_assign
id|IRONGATE_jd
suffix:semicolon
multiline_comment|/* write again clears error bits */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;stat_cmd
suffix:semicolon
multiline_comment|/* re-read to force write */
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;dramms
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Iron dramms %x&bslash;n&quot;
comma
id|IRONGATE_jd
)paren
suffix:semicolon
id|IRONGATE0-&gt;dramms
op_assign
id|IRONGATE_jd
suffix:semicolon
multiline_comment|/* write again clears error bits */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;dramms
suffix:semicolon
multiline_comment|/* re-read to force write */
multiline_comment|/* Clear ALI NMI */
id|nmi_ctl
op_assign
id|inb
c_func
(paren
l_int|0x61
)paren
suffix:semicolon
id|nmi_ctl
op_or_assign
l_int|0x0c
suffix:semicolon
id|outb
c_func
(paren
id|nmi_ctl
comma
l_int|0x61
)paren
suffix:semicolon
id|nmi_ctl
op_and_assign
op_complement
l_int|0x0c
suffix:semicolon
id|outb
c_func
(paren
id|nmi_ctl
comma
l_int|0x61
)paren
suffix:semicolon
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;dramms
suffix:semicolon
r_if
c_cond
(paren
id|IRONGATE_jd
op_amp
l_int|0x300
)paren
r_goto
id|again
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|irongate_init_arch
id|irongate_init_arch
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
id|IRONGATE0-&gt;stat_cmd
op_assign
id|IRONGATE0-&gt;stat_cmd
op_amp
op_complement
l_int|0x100
suffix:semicolon
id|irongate_pci_clr_err
c_func
(paren
)paren
suffix:semicolon
id|irongate_register_dump
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * HACK: set AGP aperture size to 256MB.&n;&t; * This should really be changed during PCI probe, when the&n;&t; * size of the aperture the AGP card wants is known.&n;&t; */
id|printk
c_func
(paren
l_string|&quot;irongate_init_arch: AGPVA was 0x%x&bslash;n&quot;
comma
id|IRONGATE0-&gt;agpva
)paren
suffix:semicolon
id|IRONGATE0-&gt;agpva
op_assign
(paren
id|IRONGATE0-&gt;agpva
op_amp
op_complement
l_int|0x0000000f
)paren
op_or
l_int|0x00000007
suffix:semicolon
multiline_comment|/*&n;&t; * Create our single hose.&n;&t; */
id|pci_isa_hose
op_assign
id|hose
op_assign
id|alloc_pci_controller
c_func
(paren
)paren
suffix:semicolon
id|hose-&gt;io_space
op_assign
op_amp
id|ioport_resource
suffix:semicolon
id|hose-&gt;mem_space
op_assign
op_amp
id|iomem_resource
suffix:semicolon
id|hose-&gt;index
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This is for userland consumption.  For some reason, the 40-bit&n;&t;   PIO bias that we use in the kernel through KSEG didn&squot;t work for&n;&t;   the page table based user mappings.  So make sure we get the&n;&t;   43-bit PIO bias.  */
id|hose-&gt;sparse_mem_base
op_assign
l_int|0
suffix:semicolon
id|hose-&gt;sparse_io_base
op_assign
l_int|0
suffix:semicolon
id|hose-&gt;dense_mem_base
op_assign
(paren
id|IRONGATE_MEM
op_amp
l_int|0xffffffffff
)paren
op_or
l_int|0x80000000000
suffix:semicolon
id|hose-&gt;dense_io_base
op_assign
(paren
id|IRONGATE_IO
op_amp
l_int|0xffffffffff
)paren
op_or
l_int|0x80000000000
suffix:semicolon
id|hose-&gt;sg_isa
op_assign
id|hose-&gt;sg_pci
op_assign
l_int|NULL
suffix:semicolon
id|__direct_map_base
op_assign
l_int|0
suffix:semicolon
id|__direct_map_size
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
multiline_comment|/*&n; * IO map and AGP support&n; */
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
r_static
r_inline
r_void
DECL|function|irongate_remap_area_pte
id|irongate_remap_area_pte
c_func
(paren
id|pte_t
op_star
id|pte
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|flags
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
r_int
r_int
id|pfn
suffix:semicolon
id|address
op_and_assign
op_complement
id|PMD_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PMD_SIZE
)paren
id|end
op_assign
id|PMD_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|address
op_ge
id|end
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|pfn
op_assign
id|phys_addr
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;irongate_remap_area_pte: page already exists&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_pte
c_func
(paren
id|pte
comma
id|pfn_pte
c_func
(paren
id|pfn
comma
id|__pgprot
c_func
(paren
id|_PAGE_VALID
op_or
id|_PAGE_ASM
op_or
id|_PAGE_KRE
op_or
id|_PAGE_KWE
op_or
id|flags
)paren
)paren
)paren
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pfn
op_increment
suffix:semicolon
id|pte
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
op_logical_and
(paren
id|address
OL
id|end
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|irongate_remap_area_pmd
id|irongate_remap_area_pmd
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|flags
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
id|address
op_and_assign
op_complement
id|PGDIR_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PGDIR_SIZE
)paren
id|end
op_assign
id|PGDIR_SIZE
suffix:semicolon
id|phys_addr
op_sub_assign
id|address
suffix:semicolon
r_if
c_cond
(paren
id|address
op_ge
id|end
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|pte_t
op_star
id|pte
op_assign
id|pte_alloc_kernel
c_func
(paren
op_amp
id|init_mm
comma
id|pmd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|irongate_remap_area_pte
c_func
(paren
id|pte
comma
id|address
comma
id|end
op_minus
id|address
comma
id|address
op_plus
id|phys_addr
comma
id|flags
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
op_logical_and
(paren
id|address
OL
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_remap_area_pages
id|irongate_remap_area_pages
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
r_int
r_int
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
id|phys_addr
op_sub_assign
id|address
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
id|address
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|address
op_ge
id|end
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
op_amp
id|init_mm
comma
id|dir
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|irongate_remap_area_pmd
c_func
(paren
id|pmd
comma
id|address
comma
id|end
op_minus
id|address
comma
id|phys_addr
op_plus
id|address
comma
id|flags
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|dir
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
op_logical_and
(paren
id|address
OL
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/agpgart.h&gt;
DECL|macro|GET_PAGE_DIR_OFF
mdefine_line|#define GET_PAGE_DIR_OFF(addr) (addr &gt;&gt; 22)
DECL|macro|GET_PAGE_DIR_IDX
mdefine_line|#define GET_PAGE_DIR_IDX(addr) (GET_PAGE_DIR_OFF(addr))
DECL|macro|GET_GATT_OFF
mdefine_line|#define GET_GATT_OFF(addr) ((addr &amp; 0x003ff000) &gt;&gt; 12) 
DECL|macro|GET_GATT
mdefine_line|#define GET_GATT(addr) (gatt_pages[GET_PAGE_DIR_IDX(addr)])
r_int
r_int
DECL|function|irongate_ioremap
id|irongate_ioremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
r_int
r_int
id|baddr
comma
id|last
suffix:semicolon
id|u32
op_star
id|mmio_regs
comma
op_star
id|gatt_pages
comma
op_star
id|cur_gatt
comma
id|pte
suffix:semicolon
r_int
r_int
id|gart_bus_addr
comma
id|gart_aper_size
suffix:semicolon
id|gart_bus_addr
op_assign
(paren
r_int
r_int
)paren
id|IRONGATE0-&gt;bar0
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gart_bus_addr
)paren
multiline_comment|/* FIXME - there must be a better way!!! */
r_return
id|addr
op_plus
id|IRONGATE_MEM
suffix:semicolon
id|gart_aper_size
op_assign
id|IRONGATE_DEFAULT_AGP_APER_SIZE
suffix:semicolon
multiline_comment|/* FIXME */
multiline_comment|/* &n;&t; * Check for within the AGP aperture...&n;&t; */
r_do
(brace
multiline_comment|/*&n;&t;&t; * Check the AGP area&n;&t;&t; */
r_if
c_cond
(paren
id|addr
op_ge
id|gart_bus_addr
op_logical_and
id|addr
op_plus
id|size
op_minus
l_int|1
OL
id|gart_bus_addr
op_plus
id|gart_aper_size
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Not found - assume legacy ioremap&n;&t;&t; */
r_return
id|addr
op_plus
id|IRONGATE_MEM
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|mmio_regs
op_assign
(paren
id|u32
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|IRONGATE0-&gt;bar1
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
op_plus
id|IRONGATE_MEM
)paren
suffix:semicolon
id|gatt_pages
op_assign
(paren
id|u32
op_star
)paren
(paren
id|phys_to_virt
c_func
(paren
id|mmio_regs
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* FIXME */
multiline_comment|/*&n;&t; * Adjust the limits (mappings must be page aligned)&n;&t; */
r_if
c_cond
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;AGP ioremap failed... addr not page aligned (0x%lx)&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
id|addr
op_plus
id|IRONGATE_MEM
suffix:semicolon
)brace
id|last
op_assign
id|addr
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|last
)paren
op_minus
id|addr
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap(0x%lx, 0x%lx)&bslash;n&quot;
comma
id|addr
comma
id|size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap:  gart_bus_addr  0x%lx&bslash;n&quot;
comma
id|gart_bus_addr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap:  gart_aper_size 0x%lx&bslash;n&quot;
comma
id|gart_aper_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap:  mmio_regs      %p&bslash;n&quot;
comma
id|mmio_regs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap:  gatt_pages     %p&bslash;n&quot;
comma
id|gatt_pages
)paren
suffix:semicolon
r_for
c_loop
(paren
id|baddr
op_assign
id|addr
suffix:semicolon
id|baddr
op_le
id|last
suffix:semicolon
id|baddr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|cur_gatt
op_assign
id|phys_to_virt
c_func
(paren
id|GET_GATT
c_func
(paren
id|baddr
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
id|pte
op_assign
id|cur_gatt
(braket
id|GET_GATT_OFF
c_func
(paren
id|baddr
)paren
)braket
op_amp
op_complement
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap:  cur_gatt %p pte 0x%x&bslash;n&quot;
comma
id|cur_gatt
comma
id|pte
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Map it&n;&t; */
id|area
op_assign
id|get_vm_area
c_func
(paren
id|size
comma
id|VM_IOREMAP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_return
(paren
r_int
r_int
)paren
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|baddr
op_assign
id|addr
comma
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|area-&gt;addr
suffix:semicolon
id|baddr
op_le
id|last
suffix:semicolon
id|baddr
op_add_assign
id|PAGE_SIZE
comma
id|vaddr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|cur_gatt
op_assign
id|phys_to_virt
c_func
(paren
id|GET_GATT
c_func
(paren
id|baddr
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
id|pte
op_assign
id|cur_gatt
(braket
id|GET_GATT_OFF
c_func
(paren
id|baddr
)paren
)braket
op_amp
op_complement
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|irongate_remap_area_pages
c_func
(paren
id|VMALLOC_VMADDR
c_func
(paren
id|vaddr
)paren
comma
id|pte
comma
id|PAGE_SIZE
comma
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;AGP ioremap: FAILED to map...&bslash;n&quot;
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|area-&gt;addr
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
l_int|NULL
suffix:semicolon
)brace
)brace
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|area-&gt;addr
op_plus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap(0x%lx, 0x%lx) returning 0x%lx&bslash;n&quot;
comma
id|addr
comma
id|size
comma
id|vaddr
)paren
suffix:semicolon
macro_line|#endif
r_return
id|vaddr
suffix:semicolon
)brace
r_void
DECL|function|irongate_iounmap
id|irongate_iounmap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|addr
op_rshift
l_int|41
)paren
op_eq
op_minus
l_int|2
)paren
r_return
suffix:semicolon
multiline_comment|/* kseg map, nothing to do */
r_if
c_cond
(paren
id|addr
)paren
r_return
id|vfree
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|PAGE_MASK
op_amp
id|addr
)paren
)paren
suffix:semicolon
)brace
eof
