multiline_comment|/*&n; * arch/sh/stboard/setup.c&n; *&n; * Copyright (C) 2001 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * STMicroelectronics ST40STB1 HARP and compatible support.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/harp/harp.h&gt;
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;STB1 Harp&quot;
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the board&n; */
DECL|function|platform_setup
r_int
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SH_STB1_HARP
r_int
r_int
id|ic8_version
comma
id|ic36_version
suffix:semicolon
id|ic8_version
op_assign
id|ctrl_inl
c_func
(paren
id|EPLD_REVID2
)paren
suffix:semicolon
id|ic36_version
op_assign
id|ctrl_inl
c_func
(paren
id|EPLD_REVID1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;STMicroelectronics STB1 HARP initialisaton&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EPLD versions: IC8: %d.%02d, IC36: %d.%02d&bslash;n&quot;
comma
(paren
id|ic8_version
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
comma
id|ic8_version
op_amp
l_int|0xf
comma
(paren
id|ic36_version
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
comma
id|ic36_version
op_amp
l_int|0xf
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_SH_STB1_OVERDRIVE)
r_int
r_int
id|version
suffix:semicolon
id|version
op_assign
id|ctrl_inl
c_func
(paren
id|EPLD_REVID
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;STMicroelectronics STB1 Overdrive initialisaton&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EPLD version: %d.%02d&bslash;n&quot;
comma
(paren
id|version
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
comma
id|version
op_amp
l_int|0xf
)paren
suffix:semicolon
macro_line|#else
macro_line|#error Undefined machine
macro_line|#endif
multiline_comment|/* Currently all STB1 chips have problems with the sleep instruction,&n;         * so disable it here.&n;         */
id|disable_hlt
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * pcibios_map_platform_irq&n; *&n; * This is board specific and returns the IRQ for a given PCI device.&n; * It is used by the PCI code (arch/sh/kernel/st40_pci*)&n; *&n; */
DECL|macro|HARP_PCI_IRQ
mdefine_line|#define HARP_PCI_IRQ    1
DECL|macro|HARP_BRIDGE_IRQ
mdefine_line|#define HARP_BRIDGE_IRQ 2
DECL|macro|OVERDRIVE_SLOT0_IRQ
mdefine_line|#define OVERDRIVE_SLOT0_IRQ 0
DECL|function|pcibios_map_platform_irq
r_int
id|__init
id|pcibios_map_platform_irq
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
eof
