multiline_comment|/* &n; * Copyright (C) 2001 David J. Mckay (david.mckay@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.                            &n; *&n; * Support functions for the ST40 PCI hardware.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &quot;pci_st40.h&quot;
multiline_comment|/* This is in P2 of course */
DECL|macro|ST40PCI_BASE_ADDRESS
mdefine_line|#define ST40PCI_BASE_ADDRESS     (0xb0000000)
DECL|macro|ST40PCI_MEM_ADDRESS
mdefine_line|#define ST40PCI_MEM_ADDRESS      (ST40PCI_BASE_ADDRESS+0x0)
DECL|macro|ST40PCI_IO_ADDRESS
mdefine_line|#define ST40PCI_IO_ADDRESS       (ST40PCI_BASE_ADDRESS+0x06000000)
DECL|macro|ST40PCI_REG_ADDRESS
mdefine_line|#define ST40PCI_REG_ADDRESS      (ST40PCI_BASE_ADDRESS+0x07000000)
DECL|macro|ST40PCI_REG
mdefine_line|#define ST40PCI_REG(x) (ST40PCI_REG_ADDRESS+(ST40PCI_##x))
DECL|macro|ST40PCI_WRITE
mdefine_line|#define ST40PCI_WRITE(reg,val) writel((val),ST40PCI_REG(reg))
DECL|macro|ST40PCI_WRITE_SHORT
mdefine_line|#define ST40PCI_WRITE_SHORT(reg,val) writew((val),ST40PCI_REG(reg))
DECL|macro|ST40PCI_WRITE_BYTE
mdefine_line|#define ST40PCI_WRITE_BYTE(reg,val) writeb((val),ST40PCI_REG(reg))
DECL|macro|ST40PCI_READ
mdefine_line|#define ST40PCI_READ(reg) readl(ST40PCI_REG(reg))
DECL|macro|ST40PCI_READ_SHORT
mdefine_line|#define ST40PCI_READ_SHORT(reg) readw(ST40PCI_REG(reg))
DECL|macro|ST40PCI_READ_BYTE
mdefine_line|#define ST40PCI_READ_BYTE(reg) readb(ST40PCI_REG(reg))
DECL|macro|ST40PCI_SERR_IRQ
mdefine_line|#define ST40PCI_SERR_IRQ        64
DECL|macro|ST40PCI_SERR_INT_GROUP
mdefine_line|#define ST40PCI_SERR_INT_GROUP  0
DECL|macro|ST40PCI_SERR_INT_POS
mdefine_line|#define ST40PCI_SERR_INT_POS    0
DECL|macro|ST40PCI_SERR_INT_PRI
mdefine_line|#define ST40PCI_SERR_INT_PRI    15
DECL|macro|ST40PCI_ERR_IRQ
mdefine_line|#define ST40PCI_ERR_IRQ        65
DECL|macro|ST40PCI_ERR_INT_GROUP
mdefine_line|#define ST40PCI_ERR_INT_GROUP   1
DECL|macro|ST40PCI_ERR_INT_POS
mdefine_line|#define ST40PCI_ERR_INT_POS     1
DECL|macro|ST40PCI_ERR_INT_PRI
mdefine_line|#define ST40PCI_ERR_INT_PRI     14
multiline_comment|/* Macros to extract PLL params */
DECL|macro|PLL_MDIV
mdefine_line|#define PLL_MDIV(reg)  ( ((unsigned)reg) &amp; 0xff )
DECL|macro|PLL_NDIV
mdefine_line|#define PLL_NDIV(reg) ( (((unsigned)reg)&gt;&gt;8) &amp; 0xff )
DECL|macro|PLL_PDIV
mdefine_line|#define PLL_PDIV(reg) ( (((unsigned)reg)&gt;&gt;16) &amp; 0x3 )
DECL|macro|PLL_SETUP
mdefine_line|#define PLL_SETUP(reg) ( (((unsigned)reg)&gt;&gt;19) &amp; 0x1ff )
multiline_comment|/* Build up the appropriate settings */
DECL|macro|PLL_SET
mdefine_line|#define PLL_SET(mdiv,ndiv,pdiv,setup) &bslash;&n;( ((mdiv)&amp;0xff) | (((ndiv)&amp;0xff)&lt;&lt;8) | (((pdiv)&amp;3)&lt;&lt;16)| (((setup)&amp;0x1ff)&lt;&lt;19))
DECL|macro|PLLPCICR
mdefine_line|#define PLLPCICR (0xbb040000+0x10)
DECL|macro|PLLPCICR_POWERON
mdefine_line|#define PLLPCICR_POWERON (1&lt;&lt;28)
DECL|macro|PLLPCICR_OUT_EN
mdefine_line|#define PLLPCICR_OUT_EN (1&lt;&lt;29)
DECL|macro|PLLPCICR_LOCKSELECT
mdefine_line|#define PLLPCICR_LOCKSELECT (1&lt;&lt;30)
DECL|macro|PLLPCICR_LOCK
mdefine_line|#define PLLPCICR_LOCK (1&lt;&lt;31)
DECL|macro|PLL_25MHZ
mdefine_line|#define PLL_25MHZ 0x793c8512
DECL|macro|PLL_33MHZ
mdefine_line|#define PLL_33MHZ PLL_SET(18,88,3,295)
DECL|function|SetPCIPLL
r_static
id|__init
r_void
id|SetPCIPLL
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Stop the PLL */
id|writel
c_func
(paren
l_int|0
comma
id|PLLPCICR
)paren
suffix:semicolon
multiline_comment|/* Always run at 33Mhz. The PCI clock is totally async &n;&t; * to the rest of the system&n;&t; */
id|writel
c_func
(paren
id|PLL_33MHZ
op_or
id|PLLPCICR_POWERON
comma
id|PLLPCICR
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ST40PCI: Waiting for PCI PLL to lock&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|readl
c_func
(paren
id|PLLPCICR
)paren
op_amp
id|PLLPCICR_LOCK
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|writel
c_func
(paren
id|readl
c_func
(paren
id|PLLPCICR
)paren
op_or
id|PLLPCICR_OUT_EN
comma
id|PLLPCICR
)paren
suffix:semicolon
)brace
DECL|function|st40_pci_irq
r_static
r_void
id|st40_pci_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_instance
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|pci_int
comma
id|pci_air
comma
id|pci_cir
comma
id|pci_aint
suffix:semicolon
id|pci_int
op_assign
id|ST40PCI_READ
c_func
(paren
id|INT
)paren
suffix:semicolon
id|pci_cir
op_assign
id|ST40PCI_READ
c_func
(paren
id|CIR
)paren
suffix:semicolon
id|pci_air
op_assign
id|ST40PCI_READ
c_func
(paren
id|AIR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_int
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI INTERRUPT!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI INT -&gt; 0x%x&bslash;n&quot;
comma
id|pci_int
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI AIR -&gt; 0x%x&bslash;n&quot;
comma
id|pci_air
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI CIR -&gt; 0x%x&bslash;n&quot;
comma
id|pci_cir
)paren
suffix:semicolon
id|ST40PCI_WRITE
c_func
(paren
id|INT
comma
op_complement
l_int|0
)paren
suffix:semicolon
)brace
id|pci_aint
op_assign
id|ST40PCI_READ
c_func
(paren
id|AINT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_aint
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI ARB INTERRUPT!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI AINT -&gt; 0x%x&bslash;n&quot;
comma
id|pci_aint
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI AIR -&gt; 0x%x&bslash;n&quot;
comma
id|pci_air
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI CIR -&gt; 0x%x&bslash;n&quot;
comma
id|pci_cir
)paren
suffix:semicolon
id|ST40PCI_WRITE
c_func
(paren
id|AINT
comma
op_complement
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Rounds a number UP to the nearest power of two. Used for&n; * sizing the PCI window.&n; */
DECL|function|r2p2
r_static
id|u32
id|__init
id|r2p2
c_func
(paren
id|u32
id|num
)paren
(brace
r_int
id|i
op_assign
l_int|31
suffix:semicolon
id|u32
id|tmp
op_assign
id|num
suffix:semicolon
r_if
c_cond
(paren
id|num
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|tmp
op_amp
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
r_break
suffix:semicolon
id|i
op_decrement
suffix:semicolon
id|tmp
op_lshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
op_ge
l_int|0
)paren
suffix:semicolon
id|tmp
op_assign
l_int|1
op_lshift
id|i
suffix:semicolon
multiline_comment|/* If the original number isn&squot;t a power of 2, round it up */
r_if
c_cond
(paren
id|tmp
op_ne
id|num
)paren
id|tmp
op_lshift_assign
l_int|1
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|pci_fixup_ide_bases
r_static
r_void
id|__init
id|pci_fixup_ide_bases
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * PCI IDE controllers use non-standard I/O port decoding, respect it.&n;&t; */
r_if
c_cond
(paren
(paren
id|d
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_STORAGE_IDE
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: IDE base address fixup for %s&bslash;n&quot;
comma
id|d-&gt;slot_name
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|d-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r-&gt;start
op_amp
op_complement
l_int|0x80
)paren
op_eq
l_int|0x374
)paren
(brace
id|r-&gt;start
op_or_assign
l_int|2
suffix:semicolon
id|r-&gt;end
op_assign
id|r-&gt;start
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Add future fixups here... */
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|pci_fixup_ide_bases
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|st40pci_init
r_int
id|__init
id|st40pci_init
c_func
(paren
r_int
id|memStart
comma
r_int
id|memSize
)paren
(brace
id|u32
id|lsr0
suffix:semicolon
id|SetPCIPLL
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Initialises the ST40 pci subsystem, performing a reset, then programming&n;&t; * up the address space decoders appropriately&n;&t; */
multiline_comment|/* Should reset core here as well methink */
id|ST40PCI_WRITE
c_func
(paren
id|CR
comma
id|CR_LOCK_MASK
op_or
id|CR_SOFT_RESET
)paren
suffix:semicolon
multiline_comment|/* Loop while core resets */
r_while
c_loop
(paren
id|ST40PCI_READ
c_func
(paren
id|CR
)paren
op_amp
id|CR_SOFT_RESET
)paren
suffix:semicolon
multiline_comment|/* Now, lets reset all the cards on the bus with extreme prejudice */
id|ST40PCI_WRITE
c_func
(paren
id|CR
comma
id|CR_LOCK_MASK
op_or
id|CR_RSTCTL
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|250
)paren
suffix:semicolon
multiline_comment|/* Set bus active, take it out of reset */
id|ST40PCI_WRITE
c_func
(paren
id|CR
comma
id|CR_LOCK_MASK
op_or
id|CR_CFINT
op_or
id|CR_PFCS
op_or
id|CR_PFE
)paren
suffix:semicolon
multiline_comment|/* The PCI spec says that no access must be made to the bus until 1 second&n;&t; * after reset. This seem ludicrously long, but some delay is needed here&n;&t; */
id|mdelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Switch off interrupts */
id|ST40PCI_WRITE
c_func
(paren
id|INTM
comma
l_int|0
)paren
suffix:semicolon
id|ST40PCI_WRITE
c_func
(paren
id|AINT
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Allow it to be a master */
id|ST40PCI_WRITE_SHORT
c_func
(paren
id|CSR_CMD
comma
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
op_or
id|PCI_COMMAND_IO
)paren
suffix:semicolon
multiline_comment|/* Accesse to the 0xb0000000 -&gt; 0xb6000000 area will go through to 0x10000000 -&gt; 0x16000000&n;&t; * on the PCI bus. This allows a nice 1-1 bus to phys mapping.&n;&t; */
id|ST40PCI_WRITE
c_func
(paren
id|MBR
comma
l_int|0x10000000
)paren
suffix:semicolon
multiline_comment|/* Always set the max size 128M (actually, it is only 96MB wide) */
id|ST40PCI_WRITE
c_func
(paren
id|MBMR
comma
l_int|0x07ff0000
)paren
suffix:semicolon
multiline_comment|/* I/O addresses are mapped at 0xb6000000 -&gt; 0xb7000000. These are changed to 0, to &n;&t; * allow cards that have legacy io such as vga to function correctly. This gives a &n;&t; * maximum of 64K of io/space as only the bottom 16 bits of the address are copied &n;&t; * over to the bus  when the transaction is made. 64K of io space is more than enough&n;&t; */
id|ST40PCI_WRITE
c_func
(paren
id|IOBR
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* Set up the 64K window */
id|ST40PCI_WRITE
c_func
(paren
id|IOBMR
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* Now we set up the mbars so the PCI bus can see the memory of the machine */
r_if
c_cond
(paren
id|memSize
OL
(paren
l_int|64
op_star
l_int|1024
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Ridiculous memory size of 0x%x?&bslash;n&quot;
comma
id|memSize
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|lsr0
op_assign
(paren
id|memSize
OG
(paren
l_int|512
op_star
l_int|1024
op_star
l_int|1024
)paren
)paren
ques
c_cond
l_int|0x1fff0001
suffix:colon
(paren
(paren
id|r2p2
c_func
(paren
id|memSize
)paren
op_minus
l_int|0x10000
)paren
op_or
l_int|0x1
)paren
suffix:semicolon
id|ST40PCI_WRITE
c_func
(paren
id|LSR0
comma
id|lsr0
)paren
suffix:semicolon
id|ST40PCI_WRITE
c_func
(paren
id|CSR_MBAR0
comma
id|memStart
)paren
suffix:semicolon
id|ST40PCI_WRITE
c_func
(paren
id|LAR0
comma
id|memStart
)paren
suffix:semicolon
multiline_comment|/* Maximise timeout values */
id|ST40PCI_WRITE_BYTE
c_func
(paren
id|CSR_TRDY
comma
l_int|0xff
)paren
suffix:semicolon
id|ST40PCI_WRITE_BYTE
c_func
(paren
id|CSR_RETRY
comma
l_int|0xff
)paren
suffix:semicolon
id|ST40PCI_WRITE_BYTE
c_func
(paren
id|CSR_MIT
comma
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* Install the pci interrupt handlers */
id|make_intc2_irq
c_func
(paren
id|ST40PCI_SERR_IRQ
comma
id|INTC2_BASE0
comma
id|ST40PCI_SERR_INT_GROUP
comma
id|ST40PCI_SERR_INT_POS
comma
id|ST40PCI_SERR_INT_PRI
)paren
suffix:semicolon
id|make_intc2_irq
c_func
(paren
id|ST40PCI_ERR_IRQ
comma
id|INTC2_BASE0
comma
id|ST40PCI_ERR_INT_GROUP
comma
id|ST40PCI_ERR_INT_POS
comma
id|ST40PCI_ERR_INT_PRI
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pcibios_setup
r_char
op_star
id|__init
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|str
suffix:semicolon
)brace
DECL|macro|SET_CONFIG_BITS
mdefine_line|#define SET_CONFIG_BITS(bus,devfn,where)&bslash;&n;  (((bus) &lt;&lt; 16) | ((devfn) &lt;&lt; 8) | ((where) &amp; ~3) | (bus!=0))
DECL|macro|CONFIG_CMD
mdefine_line|#define CONFIG_CMD(bus, devfn, where) SET_CONFIG_BITS(bus-&gt;number,devfn,where)
DECL|function|CheckForMasterAbort
r_static
r_int
id|CheckForMasterAbort
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ST40PCI_READ
c_func
(paren
id|INT
)paren
op_amp
id|INT_MADIM
)paren
(brace
multiline_comment|/* Should we clear config space version as well ??? */
id|ST40PCI_WRITE
c_func
(paren
id|INT
comma
id|INT_MADIM
)paren
suffix:semicolon
id|ST40PCI_WRITE_SHORT
c_func
(paren
id|CSR_STATUS
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Write to config register */
DECL|function|st40pci_read
r_static
r_int
id|st40pci_read
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
id|ST40PCI_WRITE
c_func
(paren
id|PAR
comma
id|CONFIG_CMD
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
)paren
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
op_star
id|val
op_assign
(paren
id|u8
)paren
id|ST40PCI_READ_BYTE
c_func
(paren
id|PDR
op_plus
(paren
id|where
op_amp
l_int|3
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|val
op_assign
(paren
id|u16
)paren
id|ST40PCI_READ_SHORT
c_func
(paren
id|PDR
op_plus
(paren
id|where
op_amp
l_int|2
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|val
op_assign
id|ST40PCI_READ
c_func
(paren
id|PDR
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|CheckForMasterAbort
c_func
(paren
)paren
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
op_star
id|val
op_assign
(paren
id|u8
)paren
l_int|0xff
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|val
op_assign
(paren
id|u16
)paren
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|val
op_assign
l_int|0xffffffff
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|st40pci_write
r_static
r_int
id|st40pci_write
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
suffix:semicolon
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
id|ST40PCI_WRITE
c_func
(paren
id|PAR
comma
id|CONFIG_CMD
c_func
(paren
id|dev
comma
id|where
)paren
)paren
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
id|ST40PCI_WRITE_BYTE
c_func
(paren
id|PDR
op_plus
(paren
id|where
op_amp
l_int|3
)paren
comma
(paren
id|u8
)paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|ST40PCI_WRITE_SHORT
c_func
(paren
id|PDR
op_plus
(paren
id|where
op_amp
l_int|2
)paren
comma
(paren
id|u16
)paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|ST40PCI_WRITE
c_func
(paren
id|PDR
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|CheckForMasterAbort
c_func
(paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|pci_config_ops
r_static
r_struct
id|pci_ops
id|pci_config_ops
op_assign
(brace
dot
id|read
op_assign
id|st40pci_read
comma
dot
id|write
op_assign
id|st40pci_write
comma
)brace
suffix:semicolon
multiline_comment|/* Everything hangs off this */
DECL|variable|pci_root_bus
r_static
r_struct
id|pci_bus
op_star
id|pci_root_bus
suffix:semicolon
DECL|function|no_swizzle
r_static
id|u8
id|__init
id|no_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pin
)paren
(brace
r_return
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
multiline_comment|/* This needs to be shunted out of here into the board specific bit */
DECL|macro|HARP_PCI_IRQ
mdefine_line|#define HARP_PCI_IRQ    1
DECL|macro|HARP_BRIDGE_IRQ
mdefine_line|#define HARP_BRIDGE_IRQ 2
DECL|macro|OVERDRIVE_SLOT0_IRQ
mdefine_line|#define OVERDRIVE_SLOT0_IRQ 0
DECL|function|map_harp_irq
r_static
r_int
id|__init
id|map_harp_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_switch
c_cond
(paren
id|slot
)paren
(brace
macro_line|#ifdef CONFIG_SH_STB1_HARP
r_case
l_int|2
suffix:colon
multiline_comment|/*This is the PCI slot on the */
r_return
id|HARP_PCI_IRQ
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* this is the bridge */
r_return
id|HARP_BRIDGE_IRQ
suffix:semicolon
macro_line|#elif defined(CONFIG_SH_STB1_OVERDRIVE)
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
r_case
l_int|3
suffix:colon
r_return
id|slot
op_minus
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error Unknown board
macro_line|#endif
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_void
id|__devinit
DECL|function|pcibios_fixup_pbus_ranges
id|pcibios_fixup_pbus_ranges
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|pbus_set_ranges_data
op_star
id|ranges
)paren
(brace
)brace
DECL|function|pcibios_init
r_void
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
r_int
id|memory_start
comma
id|memory_end
suffix:semicolon
r_if
c_cond
(paren
id|sh_mv.mv_init_pci
op_ne
l_int|NULL
)paren
(brace
id|sh_mv
dot
id|mv_init_pci
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* The pci subsytem needs to know where memory is and how much &n;&t; * of it there is. I&squot;ve simply made these globals. A better mechanism&n;&t; * is probably needed.&n;&t; */
id|st40pci_init
c_func
(paren
id|PHYSADDR
c_func
(paren
id|memory_start
)paren
comma
id|PHYSADDR
c_func
(paren
id|memory_end
)paren
op_minus
id|PHYSADDR
c_func
(paren
id|memory_start
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|ST40PCI_ERR_IRQ
comma
id|st40_pci_irq
comma
id|SA_INTERRUPT
comma
l_string|&quot;st40pci&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;st40pci: Cannot hook interrupt&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Enable the PCI interrupts on the device */
id|ST40PCI_WRITE
c_func
(paren
id|INTM
comma
op_complement
l_int|0
)paren
suffix:semicolon
id|ST40PCI_WRITE
c_func
(paren
id|AINT
comma
op_complement
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Map the io address apprioately */
macro_line|#ifdef CONFIG_HD64465
id|hd64465_port_map
c_func
(paren
id|PCIBIOS_MIN_IO
comma
(paren
l_int|64
op_star
l_int|1024
)paren
op_minus
id|PCIBIOS_MIN_IO
op_plus
l_int|1
comma
id|ST40_IO_ADDR
op_plus
id|PCIBIOS_MIN_IO
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* ok, do the scan man */
id|pci_root_bus
op_assign
id|pci_scan_bus
c_func
(paren
l_int|0
comma
op_amp
id|pci_config_ops
comma
l_int|NULL
)paren
suffix:semicolon
id|pci_assign_unassigned_resources
c_func
(paren
)paren
suffix:semicolon
id|pci_fixup_irqs
c_func
(paren
id|no_swizzle
comma
id|map_harp_irq
)paren
suffix:semicolon
)brace
DECL|function|pcibios_fixup_bus
r_void
id|__init
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
)brace
eof
