multiline_comment|/*&n;&t;The all defines and part of code (such as cs461x_*) are &n;&t;contributed from ALSA 0.5.8 sources. &n;&t;See http://www.alsa-project.org/ for sources&n;&t;&n;&t;Tested on Linux 686 2.4.0-test9, ALSA 0.5.8a and CS4610&n;*/
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Victor Krapivin &lt;vik@belcaf.minsk.by&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;These options are experimental&n;&n;#define CS461X_FULL_MAP&n;*/
macro_line|#ifndef PCI_VENDOR_ID_CIRRUS
DECL|macro|PCI_VENDOR_ID_CIRRUS
mdefine_line|#define PCI_VENDOR_ID_CIRRUS            0x1013
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_CIRRUS_4610
DECL|macro|PCI_DEVICE_ID_CIRRUS_4610
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_4610       0x6001
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_CIRRUS_4612
DECL|macro|PCI_DEVICE_ID_CIRRUS_4612
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_4612       0x6003
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_CIRRUS_4615
DECL|macro|PCI_DEVICE_ID_CIRRUS_4615
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_4615       0x6004
macro_line|#endif
multiline_comment|/* Registers */
DECL|macro|BA0_JSPT
mdefine_line|#define BA0_JSPT                                0x00000480
DECL|macro|BA0_JSCTL
mdefine_line|#define BA0_JSCTL                               0x00000484
DECL|macro|BA0_JSC1
mdefine_line|#define BA0_JSC1                                0x00000488
DECL|macro|BA0_JSC2
mdefine_line|#define BA0_JSC2                                0x0000048C
DECL|macro|BA0_JSIO
mdefine_line|#define BA0_JSIO                                0x000004A0
multiline_comment|/* Bits for JSPT */
DECL|macro|JSPT_CAX
mdefine_line|#define JSPT_CAX                                0x00000001
DECL|macro|JSPT_CAY
mdefine_line|#define JSPT_CAY                                0x00000002
DECL|macro|JSPT_CBX
mdefine_line|#define JSPT_CBX                                0x00000004
DECL|macro|JSPT_CBY
mdefine_line|#define JSPT_CBY                                0x00000008
DECL|macro|JSPT_BA1
mdefine_line|#define JSPT_BA1                                0x00000010
DECL|macro|JSPT_BA2
mdefine_line|#define JSPT_BA2                                0x00000020
DECL|macro|JSPT_BB1
mdefine_line|#define JSPT_BB1                                0x00000040
DECL|macro|JSPT_BB2
mdefine_line|#define JSPT_BB2                                0x00000080
multiline_comment|/* Bits for JSCTL */
DECL|macro|JSCTL_SP_MASK
mdefine_line|#define JSCTL_SP_MASK                           0x00000003
DECL|macro|JSCTL_SP_SLOW
mdefine_line|#define JSCTL_SP_SLOW                           0x00000000
DECL|macro|JSCTL_SP_MEDIUM_SLOW
mdefine_line|#define JSCTL_SP_MEDIUM_SLOW                    0x00000001
DECL|macro|JSCTL_SP_MEDIUM_FAST
mdefine_line|#define JSCTL_SP_MEDIUM_FAST                    0x00000002
DECL|macro|JSCTL_SP_FAST
mdefine_line|#define JSCTL_SP_FAST                           0x00000003
DECL|macro|JSCTL_ARE
mdefine_line|#define JSCTL_ARE                               0x00000004
multiline_comment|/* Data register pairs masks */
DECL|macro|JSC1_Y1V_MASK
mdefine_line|#define JSC1_Y1V_MASK                           0x0000FFFF
DECL|macro|JSC1_X1V_MASK
mdefine_line|#define JSC1_X1V_MASK                           0xFFFF0000
DECL|macro|JSC1_Y1V_SHIFT
mdefine_line|#define JSC1_Y1V_SHIFT                          0
DECL|macro|JSC1_X1V_SHIFT
mdefine_line|#define JSC1_X1V_SHIFT                          16
DECL|macro|JSC2_Y2V_MASK
mdefine_line|#define JSC2_Y2V_MASK                           0x0000FFFF
DECL|macro|JSC2_X2V_MASK
mdefine_line|#define JSC2_X2V_MASK                           0xFFFF0000
DECL|macro|JSC2_Y2V_SHIFT
mdefine_line|#define JSC2_Y2V_SHIFT                          0
DECL|macro|JSC2_X2V_SHIFT
mdefine_line|#define JSC2_X2V_SHIFT                          16
multiline_comment|/* JS GPIO */
DECL|macro|JSIO_DAX
mdefine_line|#define JSIO_DAX                                0x00000001
DECL|macro|JSIO_DAY
mdefine_line|#define JSIO_DAY                                0x00000002
DECL|macro|JSIO_DBX
mdefine_line|#define JSIO_DBX                                0x00000004
DECL|macro|JSIO_DBY
mdefine_line|#define JSIO_DBY                                0x00000008
DECL|macro|JSIO_AXOE
mdefine_line|#define JSIO_AXOE                               0x00000010
DECL|macro|JSIO_AYOE
mdefine_line|#define JSIO_AYOE                               0x00000020
DECL|macro|JSIO_BXOE
mdefine_line|#define JSIO_BXOE                               0x00000040
DECL|macro|JSIO_BYOE
mdefine_line|#define JSIO_BYOE                               0x00000080
multiline_comment|/* &n;   The card initialization code is obfuscated; the module cs461x &n;   need to be loaded after ALSA modules initialized and something&n;   played on the CS 4610 chip (see sources for details of CS4610&n;   initialization code from ALSA)&n;*/
multiline_comment|/* Card specific definitions */
DECL|macro|CS461X_BA0_SIZE
mdefine_line|#define CS461X_BA0_SIZE         0x2000
DECL|macro|CS461X_BA1_DATA0_SIZE
mdefine_line|#define CS461X_BA1_DATA0_SIZE   0x3000
DECL|macro|CS461X_BA1_DATA1_SIZE
mdefine_line|#define CS461X_BA1_DATA1_SIZE   0x3800
DECL|macro|CS461X_BA1_PRG_SIZE
mdefine_line|#define CS461X_BA1_PRG_SIZE     0x7000
DECL|macro|CS461X_BA1_REG_SIZE
mdefine_line|#define CS461X_BA1_REG_SIZE     0x0100
DECL|macro|BA1_SP_DMEM0
mdefine_line|#define BA1_SP_DMEM0                            0x00000000
DECL|macro|BA1_SP_DMEM1
mdefine_line|#define BA1_SP_DMEM1                            0x00010000
DECL|macro|BA1_SP_PMEM
mdefine_line|#define BA1_SP_PMEM                             0x00020000
DECL|macro|BA1_SP_REG
mdefine_line|#define BA1_SP_REG                              0x00030000
DECL|macro|BA1_DWORD_SIZE
mdefine_line|#define BA1_DWORD_SIZE          (13 * 1024 + 512)
DECL|macro|BA1_MEMORY_COUNT
mdefine_line|#define BA1_MEMORY_COUNT        3
multiline_comment|/* &n;   Only one CS461x card is still suppoted; the code requires&n;   redesign to avoid this limitatuion.&n;*/
DECL|variable|ba0_addr
r_static
r_int
r_int
id|ba0_addr
suffix:semicolon
DECL|variable|ba0
r_static
r_int
r_int
op_star
id|ba0
suffix:semicolon
DECL|variable|phys
r_static
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
DECL|variable|name
r_static
r_char
id|name
(braket
)braket
op_assign
l_string|&quot;CS416x Gameport&quot;
suffix:semicolon
macro_line|#ifdef CS461X_FULL_MAP
DECL|variable|ba1_addr
r_static
r_int
r_int
id|ba1_addr
suffix:semicolon
DECL|union|ba1_t
r_static
r_union
id|ba1_t
(brace
r_struct
(brace
DECL|member|data0
r_int
r_int
op_star
id|data0
suffix:semicolon
DECL|member|data1
r_int
r_int
op_star
id|data1
suffix:semicolon
DECL|member|pmem
r_int
r_int
op_star
id|pmem
suffix:semicolon
DECL|member|reg
r_int
r_int
op_star
id|reg
suffix:semicolon
DECL|member|name
)brace
id|name
suffix:semicolon
DECL|member|idx
r_int
r_int
op_star
id|idx
(braket
l_int|4
)braket
suffix:semicolon
DECL|variable|ba1
)brace
id|ba1
suffix:semicolon
DECL|function|cs461x_poke
r_static
r_void
id|cs461x_poke
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|val
)paren
(brace
id|ba1.idx
(braket
(paren
id|reg
op_rshift
l_int|16
)paren
op_amp
l_int|3
)braket
(braket
(paren
id|reg
op_rshift
l_int|2
)paren
op_amp
l_int|0x3fff
)braket
op_assign
id|val
suffix:semicolon
)brace
DECL|function|cs461x_peek
r_static
r_int
r_int
id|cs461x_peek
c_func
(paren
r_int
r_int
id|reg
)paren
(brace
r_return
id|ba1.idx
(braket
(paren
id|reg
op_rshift
l_int|16
)paren
op_amp
l_int|3
)braket
(braket
(paren
id|reg
op_rshift
l_int|2
)paren
op_amp
l_int|0x3fff
)braket
suffix:semicolon
)brace
macro_line|#endif
DECL|function|cs461x_pokeBA0
r_static
r_void
id|cs461x_pokeBA0
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|val
)paren
(brace
id|ba0
(braket
id|reg
op_rshift
l_int|2
)braket
op_assign
id|val
suffix:semicolon
)brace
DECL|function|cs461x_peekBA0
r_static
r_int
r_int
id|cs461x_peekBA0
c_func
(paren
r_int
r_int
id|reg
)paren
(brace
r_return
id|ba0
(braket
id|reg
op_rshift
l_int|2
)braket
suffix:semicolon
)brace
DECL|function|cs461x_free
r_static
r_int
id|cs461x_free
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|gameport
op_star
id|port
op_assign
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port
)paren
(brace
id|gameport_unregister_port
c_func
(paren
id|port
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ba0
)paren
id|iounmap
c_func
(paren
id|ba0
)paren
suffix:semicolon
macro_line|#ifdef CS461X_FULL_MAP
r_if
c_cond
(paren
id|ba1.name.data0
)paren
id|iounmap
c_func
(paren
id|ba1.name.data0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ba1.name.data1
)paren
id|iounmap
c_func
(paren
id|ba1.name.data1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ba1.name.pmem
)paren
id|iounmap
c_func
(paren
id|ba1.name.pmem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ba1.name.reg
)paren
id|iounmap
c_func
(paren
id|ba1.name.reg
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cs461x_gameport_trigger
r_static
r_void
id|cs461x_gameport_trigger
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
id|cs461x_pokeBA0
c_func
(paren
id|BA0_JSPT
comma
l_int|0xFF
)paren
suffix:semicolon
singleline_comment|//outb(gameport-&gt;io, 0xFF);
)brace
DECL|function|cs461x_gameport_read
r_static
r_int
r_char
id|cs461x_gameport_read
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_return
id|cs461x_peekBA0
c_func
(paren
id|BA0_JSPT
)paren
suffix:semicolon
singleline_comment|//inb(gameport-&gt;io);
)brace
DECL|function|cs461x_gameport_cooked_read
r_static
r_int
id|cs461x_gameport_cooked_read
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
op_star
id|axes
comma
r_int
op_star
id|buttons
)paren
(brace
r_int
id|js1
comma
id|js2
comma
id|jst
suffix:semicolon
id|js1
op_assign
id|cs461x_peekBA0
c_func
(paren
id|BA0_JSC1
)paren
suffix:semicolon
id|js2
op_assign
id|cs461x_peekBA0
c_func
(paren
id|BA0_JSC2
)paren
suffix:semicolon
id|jst
op_assign
id|cs461x_peekBA0
c_func
(paren
id|BA0_JSPT
)paren
suffix:semicolon
op_star
id|buttons
op_assign
(paren
op_complement
id|jst
op_rshift
l_int|4
)paren
op_amp
l_int|0x0F
suffix:semicolon
id|axes
(braket
l_int|0
)braket
op_assign
(paren
(paren
id|js1
op_amp
id|JSC1_Y1V_MASK
)paren
op_rshift
id|JSC1_Y1V_SHIFT
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
id|axes
(braket
l_int|1
)braket
op_assign
(paren
(paren
id|js1
op_amp
id|JSC1_X1V_MASK
)paren
op_rshift
id|JSC1_X1V_SHIFT
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
id|axes
(braket
l_int|2
)braket
op_assign
(paren
(paren
id|js2
op_amp
id|JSC2_Y2V_MASK
)paren
op_rshift
id|JSC2_Y2V_SHIFT
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
id|axes
(braket
l_int|3
)braket
op_assign
(paren
(paren
id|js2
op_amp
id|JSC2_X2V_MASK
)paren
op_rshift
id|JSC2_X2V_SHIFT
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
r_for
c_loop
(paren
id|jst
op_assign
l_int|0
suffix:semicolon
id|jst
OL
l_int|4
suffix:semicolon
op_increment
id|jst
)paren
r_if
c_cond
(paren
id|axes
(braket
id|jst
)braket
op_eq
l_int|0xFFFF
)paren
(brace
id|axes
(braket
id|jst
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cs461x_gameport_open
r_static
r_int
id|cs461x_gameport_open
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
id|mode
)paren
(brace
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|GAMEPORT_MODE_COOKED
suffix:colon
r_case
id|GAMEPORT_MODE_RAW
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cs461x_pci_tbl
r_static
r_struct
id|pci_device_id
id|cs461x_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_CIRRUS
comma
l_int|0x6001
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Cirrus CS4610 */
(brace
id|PCI_VENDOR_ID_CIRRUS
comma
l_int|0x6003
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Cirrus CS4612 */
(brace
id|PCI_VENDOR_ID_CIRRUS
comma
l_int|0x6005
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Cirrus CS4615 */
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|cs461x_pci_tbl
)paren
suffix:semicolon
DECL|function|cs461x_pci_probe
r_static
r_int
id|__devinit
id|cs461x_pci_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|gameport
op_star
id|port
suffix:semicolon
id|rc
op_assign
id|pci_enable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cs461x: Cannot enable PCI gameport (bus %d, devfn %d) error=%d&bslash;n&quot;
comma
id|pdev-&gt;bus-&gt;number
comma
id|pdev-&gt;devfn
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|ba0_addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CS461X_FULL_MAP
id|ba1_addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ba0_addr
op_eq
l_int|0
op_logical_or
id|ba0_addr
op_eq
op_complement
l_int|0
macro_line|#ifdef CS461X_FULL_MAP
op_logical_or
id|ba1_addr
op_eq
l_int|0
op_logical_or
id|ba1_addr
op_eq
op_complement
l_int|0
macro_line|#endif
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cs461x: wrong address - ba0 = 0x%lx&bslash;n&quot;
comma
id|ba0_addr
)paren
suffix:semicolon
macro_line|#ifdef CS461X_FULL_MAP
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cs461x: wrong address - ba1 = 0x%lx&bslash;n&quot;
comma
id|ba1_addr
)paren
suffix:semicolon
macro_line|#endif
id|cs461x_free
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ba0
op_assign
id|ioremap
c_func
(paren
id|ba0_addr
comma
id|CS461X_BA0_SIZE
)paren
suffix:semicolon
macro_line|#ifdef CS461X_FULL_MAP
id|ba1.name.data0
op_assign
id|ioremap
c_func
(paren
id|ba1_addr
op_plus
id|BA1_SP_DMEM0
comma
id|CS461X_BA1_DATA0_SIZE
)paren
suffix:semicolon
id|ba1.name.data1
op_assign
id|ioremap
c_func
(paren
id|ba1_addr
op_plus
id|BA1_SP_DMEM1
comma
id|CS461X_BA1_DATA1_SIZE
)paren
suffix:semicolon
id|ba1.name.pmem
op_assign
id|ioremap
c_func
(paren
id|ba1_addr
op_plus
id|BA1_SP_PMEM
comma
id|CS461X_BA1_PRG_SIZE
)paren
suffix:semicolon
id|ba1.name.reg
op_assign
id|ioremap
c_func
(paren
id|ba1_addr
op_plus
id|BA1_SP_REG
comma
id|CS461X_BA1_REG_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ba0
op_eq
l_int|NULL
op_logical_or
id|ba1.name.data0
op_eq
l_int|NULL
op_logical_or
id|ba1.name.data1
op_eq
l_int|NULL
op_logical_or
id|ba1.name.pmem
op_eq
l_int|NULL
op_logical_or
id|ba1.name.reg
op_eq
l_int|NULL
)paren
(brace
id|cs461x_free
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|ba0
op_eq
l_int|NULL
)paren
(brace
id|cs461x_free
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|port
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|gameport
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Memory allocation failed.&bslash;n&quot;
)paren
suffix:semicolon
id|cs461x_free
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|port
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|gameport
)paren
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|port
)paren
suffix:semicolon
id|port-&gt;open
op_assign
id|cs461x_gameport_open
suffix:semicolon
id|port-&gt;trigger
op_assign
id|cs461x_gameport_trigger
suffix:semicolon
id|port-&gt;read
op_assign
id|cs461x_gameport_read
suffix:semicolon
id|port-&gt;cooked_read
op_assign
id|cs461x_gameport_cooked_read
suffix:semicolon
id|sprintf
c_func
(paren
id|phys
comma
l_string|&quot;pci%s/gameport0&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
)paren
suffix:semicolon
id|port-&gt;name
op_assign
id|name
suffix:semicolon
id|port-&gt;phys
op_assign
id|phys
suffix:semicolon
id|port-&gt;id.bustype
op_assign
id|BUS_PCI
suffix:semicolon
id|port-&gt;id.vendor
op_assign
id|pdev-&gt;vendor
suffix:semicolon
id|port-&gt;id.product
op_assign
id|pdev-&gt;device
suffix:semicolon
id|cs461x_pokeBA0
c_func
(paren
id|BA0_JSIO
comma
l_int|0xFF
)paren
suffix:semicolon
singleline_comment|// ?
id|cs461x_pokeBA0
c_func
(paren
id|BA0_JSCTL
comma
id|JSCTL_SP_MEDIUM_SLOW
)paren
suffix:semicolon
id|gameport_register_port
c_func
(paren
id|port
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;gameport: %s on pci%s speed %d kHz&bslash;n&quot;
comma
id|name
comma
id|pci_name
c_func
(paren
id|pdev
)paren
comma
id|port-&gt;speed
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cs461x_pci_remove
r_static
r_void
id|__devexit
id|cs461x_pci_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|cs461x_free
c_func
(paren
id|pdev
)paren
suffix:semicolon
)brace
DECL|variable|cs461x_pci_driver
r_static
r_struct
id|pci_driver
id|cs461x_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;CS461x Gameport&quot;
comma
dot
id|id_table
op_assign
id|cs461x_pci_tbl
comma
dot
id|probe
op_assign
id|cs461x_pci_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|cs461x_pci_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|cs461x_init
r_int
id|__init
id|cs461x_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
c_func
(paren
op_amp
id|cs461x_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|cs461x_exit
r_void
id|__exit
id|cs461x_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|cs461x_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|cs461x_init
id|module_init
c_func
(paren
id|cs461x_init
)paren
suffix:semicolon
DECL|variable|cs461x_exit
id|module_exit
c_func
(paren
id|cs461x_exit
)paren
suffix:semicolon
eof
