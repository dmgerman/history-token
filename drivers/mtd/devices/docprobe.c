multiline_comment|/* Linux driver for Disk-On-Chip devices&t;&t;&t;*/
multiline_comment|/* Probe routines common to all DoC devices&t;&t;&t;*/
multiline_comment|/* (C) 1999 Machine Vision Holdings, Inc.&t;&t;&t;*/
multiline_comment|/* (C) 1999-2003 David Woodhouse &lt;dwmw2@infradead.org&gt;&t;&t;*/
multiline_comment|/* $Id: docprobe.c,v 1.44 2005/01/05 12:40:36 dwmw2 Exp $&t;*/
multiline_comment|/* DOC_PASSIVE_PROBE:&n;   In order to ensure that the BIOS checksum is correct at boot time, and &n;   hence that the onboard BIOS extension gets executed, the DiskOnChip &n;   goes into reset mode when it is read sequentially: all registers &n;   return 0xff until the chip is woken up again by writing to the &n;   DOCControl register. &n;&n;   Unfortunately, this means that the probe for the DiskOnChip is unsafe, &n;   because one of the first things it does is write to where it thinks &n;   the DOCControl register should be - which may well be shared memory &n;   for another device. I&squot;ve had machines which lock up when this is &n;   attempted. Hence the possibility to do a passive probe, which will fail &n;   to detect a chip in reset mode, but is at least guaranteed not to lock&n;   the machine.&n;&n;   If you have this problem, uncomment the following line:&n;#define DOC_PASSIVE_PROBE&n;*/
multiline_comment|/* DOC_SINGLE_DRIVER:&n;   Millennium driver has been merged into DOC2000 driver.&n;&n;   The old Millennium-only driver has been retained just in case there&n;   are problems with the new code. If the combined driver doesn&squot;t work&n;   for you, you can try the old one by undefining DOC_SINGLE_DRIVER &n;   below and also enabling it in your configuration. If this fixes the&n;   problems, please send a report to the MTD mailing list at &n;   &lt;linux-mtd@lists.infradead.org&gt;.&n;*/
DECL|macro|DOC_SINGLE_DRIVER
mdefine_line|#define DOC_SINGLE_DRIVER
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/nand.h&gt;
macro_line|#include &lt;linux/mtd/doc2000.h&gt;
macro_line|#include &lt;linux/mtd/compatmac.h&gt;
multiline_comment|/* Where to look for the devices? */
macro_line|#ifndef CONFIG_MTD_DOCPROBE_ADDRESS
DECL|macro|CONFIG_MTD_DOCPROBE_ADDRESS
mdefine_line|#define CONFIG_MTD_DOCPROBE_ADDRESS 0
macro_line|#endif
DECL|variable|doc_config_location
r_static
r_int
r_int
id|doc_config_location
op_assign
id|CONFIG_MTD_DOCPROBE_ADDRESS
suffix:semicolon
id|module_param
c_func
(paren
id|doc_config_location
comma
id|ulong
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|doc_config_location
comma
l_string|&quot;Physical memory address at which to probe for DiskOnChip&quot;
)paren
suffix:semicolon
DECL|variable|doc_locations
r_static
r_int
r_int
id|__initdata
id|doc_locations
(braket
)braket
op_assign
(brace
macro_line|#if defined (__alpha__) || defined(__i386__) || defined(__x86_64__)
macro_line|#ifdef CONFIG_MTD_DOCPROBE_HIGH
l_int|0xfffc8000
comma
l_int|0xfffca000
comma
l_int|0xfffcc000
comma
l_int|0xfffce000
comma
l_int|0xfffd0000
comma
l_int|0xfffd2000
comma
l_int|0xfffd4000
comma
l_int|0xfffd6000
comma
l_int|0xfffd8000
comma
l_int|0xfffda000
comma
l_int|0xfffdc000
comma
l_int|0xfffde000
comma
l_int|0xfffe0000
comma
l_int|0xfffe2000
comma
l_int|0xfffe4000
comma
l_int|0xfffe6000
comma
l_int|0xfffe8000
comma
l_int|0xfffea000
comma
l_int|0xfffec000
comma
l_int|0xfffee000
comma
macro_line|#else /*  CONFIG_MTD_DOCPROBE_HIGH */
l_int|0xc8000
comma
l_int|0xca000
comma
l_int|0xcc000
comma
l_int|0xce000
comma
l_int|0xd0000
comma
l_int|0xd2000
comma
l_int|0xd4000
comma
l_int|0xd6000
comma
l_int|0xd8000
comma
l_int|0xda000
comma
l_int|0xdc000
comma
l_int|0xde000
comma
l_int|0xe0000
comma
l_int|0xe2000
comma
l_int|0xe4000
comma
l_int|0xe6000
comma
l_int|0xe8000
comma
l_int|0xea000
comma
l_int|0xec000
comma
l_int|0xee000
comma
macro_line|#endif /*  CONFIG_MTD_DOCPROBE_HIGH */
macro_line|#elif defined(__PPC__)
l_int|0xe4000000
comma
macro_line|#elif defined(CONFIG_MOMENCO_OCELOT)
l_int|0x2f000000
comma
l_int|0xff000000
comma
macro_line|#elif defined(CONFIG_MOMENCO_OCELOT_G) || defined (CONFIG_MOMENCO_OCELOT_C)
l_int|0xff000000
comma
macro_line|##else
macro_line|#warning Unknown architecture for DiskOnChip. No default probe locations defined
macro_line|#endif
l_int|0xffffffff
)brace
suffix:semicolon
multiline_comment|/* doccheck: Probe a given memory window to see if there&squot;s a DiskOnChip present */
DECL|function|doccheck
r_static
r_inline
r_int
id|__init
id|doccheck
c_func
(paren
r_void
id|__iomem
op_star
id|potential
comma
r_int
r_int
id|physadr
)paren
(brace
r_void
id|__iomem
op_star
id|window
op_assign
id|potential
suffix:semicolon
r_int
r_char
id|tmp
comma
id|tmpb
comma
id|tmpc
comma
id|ChipID
suffix:semicolon
macro_line|#ifndef DOC_PASSIVE_PROBE
r_int
r_char
id|tmp2
suffix:semicolon
macro_line|#endif
multiline_comment|/* Routine copied from the Linux DOC driver */
macro_line|#ifdef CONFIG_MTD_DOCPROBE_55AA
multiline_comment|/* Check for 0x55 0xAA signature at beginning of window,&n;&t;   this is no longer true once we remove the IPL (for Millennium */
r_if
c_cond
(paren
id|ReadDOC
c_func
(paren
id|window
comma
id|Sig1
)paren
op_ne
l_int|0x55
op_logical_or
id|ReadDOC
c_func
(paren
id|window
comma
id|Sig2
)paren
op_ne
l_int|0xaa
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_MTD_DOCPROBE_55AA */
macro_line|#ifndef DOC_PASSIVE_PROBE&t;
multiline_comment|/* It&squot;s not possible to cleanly detect the DiskOnChip - the&n;&t; * bootup procedure will put the device into reset mode, and&n;&t; * it&squot;s not possible to talk to it without actually writing&n;&t; * to the DOCControl register. So we store the current contents&n;&t; * of the DOCControl register&squot;s location, in case we later decide&n;&t; * that it&squot;s not a DiskOnChip, and want to put it back how we&n;&t; * found it. &n;&t; */
id|tmp2
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
id|DOCControl
)paren
suffix:semicolon
multiline_comment|/* Reset the DiskOnChip ASIC */
id|WriteDOC
c_func
(paren
id|DOC_MODE_CLR_ERR
op_or
id|DOC_MODE_MDWREN
op_or
id|DOC_MODE_RESET
comma
id|window
comma
id|DOCControl
)paren
suffix:semicolon
id|WriteDOC
c_func
(paren
id|DOC_MODE_CLR_ERR
op_or
id|DOC_MODE_MDWREN
op_or
id|DOC_MODE_RESET
comma
id|window
comma
id|DOCControl
)paren
suffix:semicolon
multiline_comment|/* Enable the DiskOnChip ASIC */
id|WriteDOC
c_func
(paren
id|DOC_MODE_CLR_ERR
op_or
id|DOC_MODE_MDWREN
op_or
id|DOC_MODE_NORMAL
comma
id|window
comma
id|DOCControl
)paren
suffix:semicolon
id|WriteDOC
c_func
(paren
id|DOC_MODE_CLR_ERR
op_or
id|DOC_MODE_MDWREN
op_or
id|DOC_MODE_NORMAL
comma
id|window
comma
id|DOCControl
)paren
suffix:semicolon
macro_line|#endif /* !DOC_PASSIVE_PROBE */&t;
multiline_comment|/* We need to read the ChipID register four times. For some&n;&t;   newer DiskOnChip 2000 units, the first three reads will&n;&t;   return the DiskOnChip Millennium ident. Don&squot;t ask. */
id|ChipID
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
id|ChipID
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ChipID
)paren
(brace
r_case
id|DOC_ChipID_Doc2k
suffix:colon
multiline_comment|/* Check the TOGGLE bit in the ECC register */
id|tmp
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
l_int|2
id|k_ECCStatus
)paren
op_amp
id|DOC_TOGGLE_BIT
suffix:semicolon
id|tmpb
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
l_int|2
id|k_ECCStatus
)paren
op_amp
id|DOC_TOGGLE_BIT
suffix:semicolon
id|tmpc
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
l_int|2
id|k_ECCStatus
)paren
op_amp
id|DOC_TOGGLE_BIT
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
id|tmpb
op_logical_and
id|tmp
op_eq
id|tmpc
)paren
r_return
id|ChipID
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DOC_ChipID_DocMil
suffix:colon
multiline_comment|/* Check for the new 2000 with Millennium ASIC */
id|ReadDOC
c_func
(paren
id|window
comma
id|ChipID
)paren
suffix:semicolon
id|ReadDOC
c_func
(paren
id|window
comma
id|ChipID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ReadDOC
c_func
(paren
id|window
comma
id|ChipID
)paren
op_ne
id|DOC_ChipID_DocMil
)paren
id|ChipID
op_assign
id|DOC_ChipID_Doc2kTSOP
suffix:semicolon
multiline_comment|/* Check the TOGGLE bit in the ECC register */
id|tmp
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
id|ECCConf
)paren
op_amp
id|DOC_TOGGLE_BIT
suffix:semicolon
id|tmpb
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
id|ECCConf
)paren
op_amp
id|DOC_TOGGLE_BIT
suffix:semicolon
id|tmpc
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
id|ECCConf
)paren
op_amp
id|DOC_TOGGLE_BIT
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
id|tmpb
op_logical_and
id|tmp
op_eq
id|tmpc
)paren
r_return
id|ChipID
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DOC_ChipID_DocMilPlus16
suffix:colon
r_case
id|DOC_ChipID_DocMilPlus32
suffix:colon
r_case
l_int|0
suffix:colon
multiline_comment|/* Possible Millennium+, need to do more checks */
macro_line|#ifndef DOC_PASSIVE_PROBE
multiline_comment|/* Possibly release from power down mode */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
(paren
id|tmp
OL
l_int|4
)paren
suffix:semicolon
id|tmp
op_increment
)paren
id|ReadDOC
c_func
(paren
id|window
comma
id|Mplus_Power
)paren
suffix:semicolon
multiline_comment|/* Reset the DiskOnChip ASIC */
id|tmp
op_assign
id|DOC_MODE_RESET
op_or
id|DOC_MODE_MDWREN
op_or
id|DOC_MODE_RST_LAT
op_or
id|DOC_MODE_BDECT
suffix:semicolon
id|WriteDOC
c_func
(paren
id|tmp
comma
id|window
comma
id|Mplus_DOCControl
)paren
suffix:semicolon
id|WriteDOC
c_func
(paren
op_complement
id|tmp
comma
id|window
comma
id|Mplus_CtrlConfirm
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Enable the DiskOnChip ASIC */
id|tmp
op_assign
id|DOC_MODE_NORMAL
op_or
id|DOC_MODE_MDWREN
op_or
id|DOC_MODE_RST_LAT
op_or
id|DOC_MODE_BDECT
suffix:semicolon
id|WriteDOC
c_func
(paren
id|tmp
comma
id|window
comma
id|Mplus_DOCControl
)paren
suffix:semicolon
id|WriteDOC
c_func
(paren
op_complement
id|tmp
comma
id|window
comma
id|Mplus_CtrlConfirm
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
macro_line|#endif /* !DOC_PASSIVE_PROBE */&t;
id|ChipID
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
id|ChipID
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ChipID
)paren
(brace
r_case
id|DOC_ChipID_DocMilPlus16
suffix:colon
r_case
id|DOC_ChipID_DocMilPlus32
suffix:colon
multiline_comment|/* Check the TOGGLE bit in the toggle register */
id|tmp
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
id|Mplus_Toggle
)paren
op_amp
id|DOC_TOGGLE_BIT
suffix:semicolon
id|tmpb
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
id|Mplus_Toggle
)paren
op_amp
id|DOC_TOGGLE_BIT
suffix:semicolon
id|tmpc
op_assign
id|ReadDOC
c_func
(paren
id|window
comma
id|Mplus_Toggle
)paren
op_amp
id|DOC_TOGGLE_BIT
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
id|tmpb
op_logical_and
id|tmp
op_eq
id|tmpc
)paren
r_return
id|ChipID
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* FALL TRHU */
r_default
suffix:colon
macro_line|#ifdef CONFIG_MTD_DOCPROBE_55AA
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Possible DiskOnChip with unknown ChipID %2.2X found at 0x%lx&bslash;n&quot;
comma
id|ChipID
comma
id|physadr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef DOC_PASSIVE_PROBE
multiline_comment|/* Put back the contents of the DOCControl register, in case it&squot;s not&n;&t;&t; * actually a DiskOnChip.&n;&t;&t; */
id|WriteDOC
c_func
(paren
id|tmp2
comma
id|window
comma
id|DOCControl
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;DiskOnChip failed TOGGLE test, dropping.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifndef DOC_PASSIVE_PROBE
multiline_comment|/* Put back the contents of the DOCControl register: it&squot;s not a DiskOnChip */
id|WriteDOC
c_func
(paren
id|tmp2
comma
id|window
comma
id|DOCControl
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|docfound
r_static
r_int
id|docfound
suffix:semicolon
DECL|function|DoC_Probe
r_static
r_void
id|__init
id|DoC_Probe
c_func
(paren
r_int
r_int
id|physadr
)paren
(brace
r_void
id|__iomem
op_star
id|docptr
suffix:semicolon
r_struct
id|DiskOnChip
op_star
id|this
suffix:semicolon
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
r_int
id|ChipID
suffix:semicolon
r_char
id|namebuf
(braket
l_int|15
)braket
suffix:semicolon
r_char
op_star
id|name
op_assign
id|namebuf
suffix:semicolon
r_char
op_star
id|im_funcname
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|im_modname
op_assign
l_int|NULL
suffix:semicolon
r_void
(paren
op_star
id|initroutine
)paren
(paren
r_struct
id|mtd_info
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
id|docptr
op_assign
id|ioremap
c_func
(paren
id|physadr
comma
id|DOC_IOREMAP_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|docptr
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ChipID
op_assign
id|doccheck
c_func
(paren
id|docptr
comma
id|physadr
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|ChipID
op_eq
id|DOC_ChipID_Doc2kTSOP
)paren
(brace
multiline_comment|/* Remove this at your own peril. The hardware driver works but nothing prevents you from erasing bad blocks */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Refusing to drive DiskOnChip 2000 TSOP until Bad Block Table is correctly supported by INFTL&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|docptr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|docfound
op_assign
l_int|1
suffix:semicolon
id|mtd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|DiskOnChip
)paren
op_plus
r_sizeof
(paren
r_struct
id|mtd_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Cannot allocate memory for data structures. Dropping.&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|docptr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|this
op_assign
(paren
r_struct
id|DiskOnChip
op_star
)paren
(paren
op_amp
id|mtd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|mtd
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mtd_info
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|this
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|DiskOnChip
)paren
)paren
suffix:semicolon
id|mtd-&gt;priv
op_assign
id|this
suffix:semicolon
id|this-&gt;virtadr
op_assign
id|docptr
suffix:semicolon
id|this-&gt;physadr
op_assign
id|physadr
suffix:semicolon
id|this-&gt;ChipID
op_assign
id|ChipID
suffix:semicolon
id|sprintf
c_func
(paren
id|namebuf
comma
l_string|&quot;with ChipID %2.2X&quot;
comma
id|ChipID
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ChipID
)paren
(brace
r_case
id|DOC_ChipID_Doc2kTSOP
suffix:colon
id|name
op_assign
l_string|&quot;2000 TSOP&quot;
suffix:semicolon
id|im_funcname
op_assign
l_string|&quot;DoC2k_init&quot;
suffix:semicolon
id|im_modname
op_assign
l_string|&quot;doc2000&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DOC_ChipID_Doc2k
suffix:colon
id|name
op_assign
l_string|&quot;2000&quot;
suffix:semicolon
id|im_funcname
op_assign
l_string|&quot;DoC2k_init&quot;
suffix:semicolon
id|im_modname
op_assign
l_string|&quot;doc2000&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DOC_ChipID_DocMil
suffix:colon
id|name
op_assign
l_string|&quot;Millennium&quot;
suffix:semicolon
macro_line|#ifdef DOC_SINGLE_DRIVER
id|im_funcname
op_assign
l_string|&quot;DoC2k_init&quot;
suffix:semicolon
id|im_modname
op_assign
l_string|&quot;doc2000&quot;
suffix:semicolon
macro_line|#else
id|im_funcname
op_assign
l_string|&quot;DoCMil_init&quot;
suffix:semicolon
id|im_modname
op_assign
l_string|&quot;doc2001&quot;
suffix:semicolon
macro_line|#endif /* DOC_SINGLE_DRIVER */
r_break
suffix:semicolon
r_case
id|DOC_ChipID_DocMilPlus16
suffix:colon
r_case
id|DOC_ChipID_DocMilPlus32
suffix:colon
id|name
op_assign
l_string|&quot;MillenniumPlus&quot;
suffix:semicolon
id|im_funcname
op_assign
l_string|&quot;DoCMilPlus_init&quot;
suffix:semicolon
id|im_modname
op_assign
l_string|&quot;doc2001plus&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|im_funcname
)paren
id|initroutine
op_assign
id|inter_module_get_request
c_func
(paren
id|im_funcname
comma
id|im_modname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initroutine
)paren
(brace
(paren
op_star
id|initroutine
)paren
(paren
id|mtd
)paren
suffix:semicolon
id|inter_module_put
c_func
(paren
id|im_funcname
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Cannot find driver for DiskOnChip %s at 0x%lX&bslash;n&quot;
comma
id|name
comma
id|physadr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mtd
)paren
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|docptr
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * Module stuff&n; *&n; ****************************************************************************/
DECL|function|init_doc
r_static
r_int
id|__init
id|init_doc
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|doc_config_location
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Using configured DiskOnChip probe address 0x%lx&bslash;n&quot;
comma
id|doc_config_location
)paren
suffix:semicolon
id|DoC_Probe
c_func
(paren
id|doc_config_location
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|doc_locations
(braket
id|i
)braket
op_ne
l_int|0xffffffff
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|DoC_Probe
c_func
(paren
id|doc_locations
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* No banner message any more. Print a message if no DiskOnChip&n;&t;   found, so the user knows we at least tried. */
r_if
c_cond
(paren
op_logical_neg
id|docfound
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;No recognised DiskOnChip devices found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
DECL|variable|init_doc
id|module_init
c_func
(paren
id|init_doc
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Woodhouse &lt;dwmw2@infradead.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Probe code for DiskOnChip 2000 and Millennium devices&quot;
)paren
suffix:semicolon
eof
