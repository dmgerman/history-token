macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/ip32/ip32_ints.h&gt;
multiline_comment|/*&n; * O2 has up to 5 PCI devices connected into the MACE bridge.  The device&n; * map looks like this:&n; *&n; * 0  aic7xxx 0&n; * 1  aic7xxx 1&n; * 2  expansion slot&n; * 3  N/C&n; * 4  N/C&n; */
DECL|macro|SCSI0
mdefine_line|#define SCSI0  MACEPCI_SCSI0_IRQ
DECL|macro|SCSI1
mdefine_line|#define SCSI1  MACEPCI_SCSI1_IRQ
DECL|macro|INTA0
mdefine_line|#define INTA0  MACEPCI_SLOT0_IRQ
DECL|macro|INTA1
mdefine_line|#define INTA1  MACEPCI_SLOT1_IRQ
DECL|macro|INTA2
mdefine_line|#define INTA2  MACEPCI_SLOT2_IRQ
DECL|macro|INTB
mdefine_line|#define INTB   MACEPCI_SHARED0_IRQ
DECL|macro|INTC
mdefine_line|#define INTC   MACEPCI_SHARED1_IRQ
DECL|macro|INTD
mdefine_line|#define INTD   MACEPCI_SHARED2_IRQ
DECL|variable|__initdata
r_static
r_char
id|irq_tab_mace
(braket
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* Dummy  INT#A  INT#B  INT#C  INT#D */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* This is placeholder row - never used */
(brace
l_int|0
comma
id|SCSI0
comma
id|SCSI0
comma
id|SCSI0
comma
id|SCSI0
)brace
comma
(brace
l_int|0
comma
id|SCSI1
comma
id|SCSI1
comma
id|SCSI1
comma
id|SCSI1
)brace
comma
(brace
l_int|0
comma
id|INTA0
comma
id|INTB
comma
id|INTC
comma
id|INTD
)brace
comma
(brace
l_int|0
comma
id|INTA1
comma
id|INTC
comma
id|INTD
comma
id|INTB
)brace
comma
(brace
l_int|0
comma
id|INTA2
comma
id|INTD
comma
id|INTB
comma
id|INTC
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Given a PCI slot number (a la PCI_SLOT(...)) and the interrupt pin of&n; * the device (1-4 =&gt; A-D), tell what irq to use.  Note that we don&squot;t&n; * in theory have slots 4 and 5, and we never normally use the shared&n; * irqs.  I suppose a device without a pin A will thank us for doing it&n; * right if there exists such a broken piece of crap.&n; */
DECL|function|pcibios_map_irq
r_int
id|__init
id|pcibios_map_irq
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
r_return
id|irq_tab_mace
(braket
id|slot
)braket
(braket
id|pin
)braket
suffix:semicolon
)brace
multiline_comment|/* Do platform specific device initialization at pci_enable_device() time */
DECL|function|pcibios_plat_dev_init
r_int
id|pcibios_plat_dev_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
