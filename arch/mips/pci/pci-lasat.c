macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/lasat/lasat.h&gt;
macro_line|#include &lt;asm/gt64120.h&gt;
macro_line|#include &lt;asm/nile4.h&gt;
DECL|macro|PCI_ACCESS_READ
mdefine_line|#define PCI_ACCESS_READ  0
DECL|macro|PCI_ACCESS_WRITE
mdefine_line|#define PCI_ACCESS_WRITE 1
DECL|macro|DEBUG_PCI
macro_line|#undef DEBUG_PCI
macro_line|#ifdef DEBUG_PCI
DECL|macro|Dprintk
mdefine_line|#define Dprintk(fmt...) printk(fmt)
macro_line|#else
DECL|macro|Dprintk
mdefine_line|#define Dprintk(fmt...)
macro_line|#endif
DECL|variable|lasat_pcibios_config_access
r_static
r_int
(paren
op_star
id|lasat_pcibios_config_access
)paren
(paren
r_int
r_char
id|access_type
comma
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
id|u32
op_star
id|val
)paren
suffix:semicolon
multiline_comment|/*&n; * Because of an error/peculiarity in the Galileo chip, we need to swap the &n; * bytes when running bigendian.&n; */
DECL|macro|GT_WRITE
mdefine_line|#define GT_WRITE(ofs, data)  &bslash;&n;             *(volatile u32 *)(LASAT_GT_BASE+ofs) = cpu_to_le32(data)
DECL|macro|GT_READ
mdefine_line|#define GT_READ(ofs, data)   &bslash;&n;             data = le32_to_cpu(*(volatile u32 *)(LASAT_GT_BASE+ofs))
DECL|function|lasat_pcibios_config_access_100
r_static
r_int
id|lasat_pcibios_config_access_100
c_func
(paren
r_int
r_char
id|access_type
comma
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
id|u32
op_star
id|val
)paren
(brace
r_int
r_char
id|busnum
op_assign
id|bus-&gt;number
suffix:semicolon
id|u32
id|intr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|busnum
op_eq
l_int|0
)paren
op_logical_and
(paren
id|devfn
op_ge
id|PCI_DEVFN
c_func
(paren
l_int|31
comma
l_int|0
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Because of a bug in the Galileo (for slot 31). */
multiline_comment|/* Clear cause register bits */
id|GT_WRITE
c_func
(paren
id|GT_INTRCAUSE_OFS
comma
op_complement
(paren
id|GT_INTRCAUSE_MASABORT0_BIT
op_or
id|GT_INTRCAUSE_TARABORT0_BIT
)paren
)paren
suffix:semicolon
multiline_comment|/* Setup address */
id|GT_WRITE
c_func
(paren
id|GT_PCI0_CFGADDR_OFS
comma
(paren
id|busnum
op_lshift
id|GT_PCI0_CFGADDR_BUSNUM_SHF
)paren
op_or
(paren
id|devfn
op_lshift
id|GT_PCI0_CFGADDR_FUNCTNUM_SHF
)paren
op_or
(paren
(paren
id|where
op_div
l_int|4
)paren
op_lshift
id|GT_PCI0_CFGADDR_REGNUM_SHF
)paren
op_or
id|GT_PCI0_CFGADDR_CONFIGEN_BIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access_type
op_eq
id|PCI_ACCESS_WRITE
)paren
(brace
id|GT_WRITE
c_func
(paren
id|GT_PCI0_CFGDATA_OFS
comma
op_star
id|val
)paren
suffix:semicolon
)brace
r_else
(brace
id|GT_READ
c_func
(paren
id|GT_PCI0_CFGDATA_OFS
comma
op_star
id|val
)paren
suffix:semicolon
)brace
multiline_comment|/* Check for master or target abort */
id|GT_READ
c_func
(paren
id|GT_INTRCAUSE_OFS
comma
id|intr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr
op_amp
(paren
id|GT_INTRCAUSE_MASABORT0_BIT
op_or
id|GT_INTRCAUSE_TARABORT0_BIT
)paren
)paren
(brace
multiline_comment|/* Error occurred */
multiline_comment|/* Clear bits */
id|GT_WRITE
c_func
(paren
id|GT_INTRCAUSE_OFS
comma
op_complement
(paren
id|GT_INTRCAUSE_MASABORT0_BIT
op_or
id|GT_INTRCAUSE_TARABORT0_BIT
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|LO
mdefine_line|#define LO(reg) (reg / 4)
DECL|macro|HI
mdefine_line|#define HI(reg) (reg / 4 + 1)
DECL|variable|vrc_pciregs
r_volatile
r_int
r_int
op_star
r_const
id|vrc_pciregs
op_assign
(paren
r_void
op_star
)paren
id|Vrc5074_BASE
suffix:semicolon
DECL|function|lasat_pcibios_config_access_200
r_static
r_int
id|lasat_pcibios_config_access_200
c_func
(paren
r_int
r_char
id|access_type
comma
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
id|u32
op_star
id|val
)paren
(brace
r_int
r_char
id|busnum
op_assign
id|bus-&gt;number
suffix:semicolon
id|u32
id|adr
comma
id|mask
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|busnum
op_eq
l_int|0
)paren
op_logical_and
(paren
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
OG
l_int|8
)paren
)paren
multiline_comment|/* The addressing scheme chosen leaves room for just&n;&t;&t; * 8 devices on the first busnum (besides the PCI&n;&t;&t; * controller itself) */
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|busnum
op_eq
l_int|0
)paren
op_logical_and
(paren
id|devfn
op_eq
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
)paren
)paren
(brace
multiline_comment|/* Access controller registers directly */
r_if
c_cond
(paren
id|access_type
op_eq
id|PCI_ACCESS_WRITE
)paren
(brace
id|vrc_pciregs
(braket
(paren
l_int|0x200
op_plus
id|where
)paren
op_rshift
l_int|2
)braket
op_assign
op_star
id|val
suffix:semicolon
)brace
r_else
(brace
op_star
id|val
op_assign
id|vrc_pciregs
(braket
(paren
l_int|0x200
op_plus
id|where
)paren
op_rshift
l_int|2
)braket
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Temporarily map PCI Window 1 to config space */
id|mask
op_assign
id|vrc_pciregs
(braket
id|LO
c_func
(paren
id|NILE4_PCIINIT1
)paren
)braket
suffix:semicolon
id|vrc_pciregs
(braket
id|LO
c_func
(paren
id|NILE4_PCIINIT1
)paren
)braket
op_assign
l_int|0x0000001a
op_or
(paren
id|busnum
ques
c_cond
l_int|0x200
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Clear PCI Error register. This also clears the Error Type&n;&t; * bits in the Control register */
id|vrc_pciregs
(braket
id|LO
c_func
(paren
id|NILE4_PCIERR
)paren
)braket
op_assign
l_int|0
suffix:semicolon
id|vrc_pciregs
(braket
id|HI
c_func
(paren
id|NILE4_PCIERR
)paren
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Setup address */
r_if
c_cond
(paren
id|busnum
op_eq
l_int|0
)paren
id|adr
op_assign
id|KSEG1ADDR
c_func
(paren
id|PCI_WINDOW1
)paren
op_plus
(paren
(paren
l_int|1
op_lshift
(paren
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
op_plus
l_int|15
)paren
)paren
op_or
(paren
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|where
op_amp
op_complement
l_int|3
)paren
)paren
suffix:semicolon
r_else
id|adr
op_assign
id|KSEG1ADDR
c_func
(paren
id|PCI_WINDOW1
)paren
op_or
(paren
id|busnum
op_lshift
l_int|16
)paren
op_or
(paren
id|devfn
op_lshift
l_int|8
)paren
op_or
(paren
id|where
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_PCI
id|printk
c_func
(paren
l_string|&quot;PCI config %s: adr %x&quot;
comma
id|access_type
op_eq
id|PCI_ACCESS_WRITE
ques
c_cond
l_string|&quot;write&quot;
suffix:colon
l_string|&quot;read&quot;
comma
id|adr
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|access_type
op_eq
id|PCI_ACCESS_WRITE
)paren
(brace
op_star
(paren
id|u32
op_star
)paren
id|adr
op_assign
op_star
id|val
suffix:semicolon
)brace
r_else
(brace
op_star
id|val
op_assign
op_star
(paren
id|u32
op_star
)paren
id|adr
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_PCI
id|printk
c_func
(paren
l_string|&quot; value = %x&bslash;n&quot;
comma
op_star
id|val
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Check for master or target abort */
id|err
op_assign
(paren
id|vrc_pciregs
(braket
id|HI
c_func
(paren
id|NILE4_PCICTRL
)paren
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x7
suffix:semicolon
multiline_comment|/* Restore PCI Window 1 */
id|vrc_pciregs
(braket
id|LO
c_func
(paren
id|NILE4_PCIINIT1
)paren
)braket
op_assign
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
multiline_comment|/* Error occured */
macro_line|#ifdef DEBUG_PCI
id|printk
c_func
(paren
l_string|&quot;&bslash;terror %x at adr %x&bslash;n&quot;
comma
id|err
comma
id|vrc_pciregs
(braket
id|LO
c_func
(paren
id|NILE4_PCIERR
)paren
)braket
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lasat_pcibios_read
r_static
r_int
id|lasat_pcibios_read
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|val
)paren
(brace
id|u32
id|data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
op_eq
l_int|2
)paren
op_logical_and
(paren
id|where
op_amp
l_int|1
)paren
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|size
op_eq
l_int|4
)paren
op_logical_and
(paren
id|where
op_amp
l_int|3
)paren
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
r_if
c_cond
(paren
id|lasat_pcibios_config_access
c_func
(paren
id|PCI_ACCESS_READ
comma
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|1
)paren
op_star
id|val
op_assign
(paren
id|data
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
r_else
r_if
c_cond
(paren
id|size
op_eq
l_int|2
)paren
op_star
id|val
op_assign
(paren
id|data
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xffff
suffix:semicolon
r_else
op_star
id|val
op_assign
id|data
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|lasat_pcibios_write
r_static
r_int
id|lasat_pcibios_write
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|val
)paren
(brace
id|u32
id|data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
op_eq
l_int|2
)paren
op_logical_and
(paren
id|where
op_amp
l_int|1
)paren
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|size
op_eq
l_int|4
)paren
op_logical_and
(paren
id|where
op_amp
l_int|3
)paren
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
r_if
c_cond
(paren
id|lasat_pcibios_config_access
c_func
(paren
id|PCI_ACCESS_READ
comma
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|1
)paren
id|data
op_assign
(paren
id|data
op_amp
op_complement
(paren
l_int|0xff
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
)paren
op_or
(paren
id|val
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|size
op_eq
l_int|2
)paren
id|data
op_assign
(paren
id|data
op_amp
op_complement
(paren
l_int|0xffff
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
)paren
op_or
(paren
id|val
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_else
id|data
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
id|lasat_pcibios_config_access
(paren
id|PCI_ACCESS_WRITE
comma
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|lasat_pci_ops
r_struct
id|pci_ops
id|lasat_pci_ops
op_assign
(brace
dot
id|read
op_assign
id|lasat_pcibios_read
comma
dot
id|write
op_assign
id|lasat_pcibios_write
comma
)brace
suffix:semicolon
DECL|function|pcibios_init
r_static
r_int
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|mips_machtype
)paren
(brace
r_case
id|MACH_LASAT_100
suffix:colon
id|lasat_pcibios_config_access
op_assign
op_amp
id|lasat_pcibios_config_access_100
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MACH_LASAT_200
suffix:colon
id|lasat_pcibios_config_access
op_assign
op_amp
id|lasat_pcibios_config_access_200
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;pcibios_init: mips_machtype incorrect&quot;
)paren
suffix:semicolon
)brace
id|Dprintk
c_func
(paren
l_string|&quot;pcibios_init()&bslash;n&quot;
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
l_int|0
comma
op_amp
id|lasat_pci_ops
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pcibios_init
id|subsys_initcall
c_func
(paren
id|pcibios_init
)paren
suffix:semicolon
eof
