multiline_comment|/*&n; *&t;PCI sound skeleton example&n; *&n; *&t;(c) 1998 Red Hat Software&n; *&n; *&t;This software may be used and distributed according to the &n; *&t;terms of the GNU General Public License, incorporated herein by &n; *&t;reference.&n; *&n; *&t;This example is designed to be built in the linux/drivers/sound&n; *&t;directory as part of a kernel build. The example is modular only&n; *&t;drop me a note once you have a working modular driver and want&n; *&t;to integrate it with the main code.&n; *&t;&t;-- Alan &lt;alan@redhat.com&gt;&n; *&n; *&t;This is a first draft. Please report any errors, corrections or&n; *&t;improvements to me.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;sound_config.h&quot;
multiline_comment|/*&n; *&t;Define our PCI vendor ID here&n; */
macro_line|#ifndef PCI_VENDOR_MYIDENT
DECL|macro|PCI_VENDOR_MYIDENT
mdefine_line|#define PCI_VENDOR_MYIDENT&t;&t;&t;0x125D
multiline_comment|/*&n; *&t;PCI identity for the card.&n; */
DECL|macro|PCI_DEVICE_ID_MYIDENT_MYCARD1
mdefine_line|#define PCI_DEVICE_ID_MYIDENT_MYCARD1&t;&t;0x1969
macro_line|#endif
DECL|macro|CARD_NAME
mdefine_line|#define CARD_NAME&t;&quot;ExampleWave 3D Pro Ultra ThingyWotsit&quot;
DECL|macro|MAX_CARDS
mdefine_line|#define MAX_CARDS&t;8
multiline_comment|/*&n; *&t;Each address_info object holds the information about one of&n; *&t;our card resources. In this case the MSS emulation of our&n; *&t;ficticious card. Its used to manage and attach things.&n; */
DECL|variable|mss_data
r_static
r_struct
id|address_info
id|mss_data
(braket
id|MAX_CARDS
)braket
suffix:semicolon
DECL|variable|cards
r_static
r_int
id|cards
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; *&t;Install the actual card. This is an example&n; */
DECL|function|mycard_install
r_static
r_int
id|mycard_install
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
)paren
(brace
r_int
id|iobase
suffix:semicolon
r_int
id|mssbase
suffix:semicolon
r_int
id|mpubase
suffix:semicolon
id|u8
id|x
suffix:semicolon
id|u16
id|w
suffix:semicolon
id|u32
id|v
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|dma
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Our imaginary code has its I/O on PCI address 0, a&n;&t; *&t;MSS on PCI address 1 and an MPU on address 2&n;&t; *&n;&t; *&t;For the example we will only initialise the MSS&n;&t; */
id|iobase
op_assign
id|pci_resource_start
c_func
(paren
id|pcidev
comma
l_int|0
)paren
suffix:semicolon
id|mssbase
op_assign
id|pci_resource_start
c_func
(paren
id|pcidev
comma
l_int|1
)paren
suffix:semicolon
id|mpubase
op_assign
id|pci_resource_start
c_func
(paren
id|pcidev
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Reset the board&n;&t; */
multiline_comment|/*&n;&t; *&t;Wait for completion. udelay() waits in microseconds&n;&t; */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Ok card ready. Begin setup proper. You might for example&n;&t; *&t;load the firmware here&n;&t; */
id|dma
op_assign
id|card_specific_magic
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Turn on legacy mode (example), There are also byte and&n;&t; *&t;dword (32bit) PCI configuration function calls&n;&t; */
id|pci_read_config_word
c_func
(paren
id|pcidev
comma
l_int|0x40
comma
op_amp
id|w
)paren
suffix:semicolon
id|w
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|15
)paren
suffix:semicolon
multiline_comment|/* legacy decode on */
id|w
op_or_assign
(paren
l_int|1
op_lshift
l_int|14
)paren
suffix:semicolon
multiline_comment|/* Reserved write as 1 in this case */
id|w
op_or_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
op_or
(paren
l_int|1
op_lshift
l_int|1
)paren
op_or
(paren
l_int|1
op_lshift
l_int|0
)paren
suffix:semicolon
multiline_comment|/* SB on , FM on, MPU on */
id|pci_write_config_word
c_func
(paren
id|pcidev
comma
l_int|0x40
comma
id|w
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Let the user know we found his toy.&n;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Programmed &quot;
id|CARD_NAME
l_string|&quot; at 0x%X to legacy mode.&bslash;n&quot;
comma
id|iobase
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Now set it up the description of the card&n;&t; */
id|mss_data
(braket
id|cards
)braket
dot
id|io_base
op_assign
id|mssbase
suffix:semicolon
id|mss_data
(braket
id|cards
)braket
dot
id|irq
op_assign
id|pcidev-&gt;irq
suffix:semicolon
id|mss_data
(braket
id|cards
)braket
dot
id|dma
op_assign
id|dma
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check there is an MSS present&n;&t; */
r_if
c_cond
(paren
id|ad1848_detect
c_func
(paren
id|mssbase
comma
l_int|NULL
comma
id|mss_data
(braket
id|cards
)braket
dot
id|osp
)paren
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Initialize it&n;&t; */
id|mss_data
(braket
id|cards
)braket
dot
id|slots
(braket
l_int|3
)braket
op_assign
id|ad1848_init
c_func
(paren
l_string|&quot;MyCard MSS 16bit&quot;
comma
id|mssbase
comma
id|mss_data
(braket
id|cards
)braket
dot
id|irq
comma
id|mss_data
(braket
id|cards
)braket
dot
id|dma
comma
id|mss_data
(braket
id|cards
)braket
dot
id|dma
comma
l_int|0
comma
l_int|0
comma
id|THIS_MODULE
)paren
suffix:semicolon
id|cards
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * &t;This loop walks the PCI configuration database and finds where&n; *&t;the sound cards are.&n; */
DECL|function|init_mycard
r_int
id|init_mycard
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|pcidev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_present
c_func
(paren
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|pcidev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_MYIDENT
comma
id|PCI_DEVICE_ID_MYIDENT_MYCARD1
comma
id|pcidev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|pcidev
)paren
)paren
r_continue
suffix:semicolon
id|count
op_add_assign
id|mycard_install
c_func
(paren
id|pcidev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_eq
id|MAX_CARDS
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This function is called when the user or kernel loads the &n; *&t;module into memory.&n; */
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|init_mycard
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;No &quot;
id|CARD_NAME
l_string|&quot; cards found.&bslash;n&quot;
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
multiline_comment|/*&n; *&t;This is called when it is removed. It will only be removed &n; *&t;when its use count is 0.&n; */
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
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
id|cards
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Free attached resources&n;&t;&t; */
id|ad1848_unload
c_func
(paren
id|mss_data
(braket
id|i
)braket
dot
id|io_base
comma
id|mss_data
(braket
id|i
)braket
dot
id|irq
comma
id|mss_data
(braket
id|i
)braket
dot
id|dma
comma
id|mss_data
(braket
id|i
)braket
dot
id|dma
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;And disconnect the device from the kernel&n;&t;&t; */
id|sound_unload_audiodevice
c_func
(paren
id|mss_data
(braket
id|i
)braket
dot
id|slots
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
)brace
eof