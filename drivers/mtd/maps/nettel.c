multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *      nettel.c -- mappings for NETtel/SecureEdge/SnapGear (x86) boards.&n; *&n; *      (C) Copyright 2000-2001, Greg Ungerer (gerg@snapgear.com)&n; *      (C) Copyright 2001-2002, SnapGear (www.snapgear.com)&n; *&n; *&t;$Id: nettel.c,v 1.5 2004/07/12 21:59:44 dwmw2 Exp $&n; */
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;linux/mtd/cfi.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/****************************************************************************/
DECL|macro|INTEL_BUSWIDTH
mdefine_line|#define INTEL_BUSWIDTH&t;&t;1
DECL|macro|AMD_WINDOW_MAXSIZE
mdefine_line|#define AMD_WINDOW_MAXSIZE&t;0x00200000
DECL|macro|AMD_BUSWIDTH
mdefine_line|#define AMD_BUSWIDTH&t; &t;1
multiline_comment|/*&n; *&t;PAR masks and shifts, assuming 64K pages.&n; */
DECL|macro|SC520_PAR_ADDR_MASK
mdefine_line|#define SC520_PAR_ADDR_MASK&t;0x00003fff
DECL|macro|SC520_PAR_ADDR_SHIFT
mdefine_line|#define SC520_PAR_ADDR_SHIFT&t;16
DECL|macro|SC520_PAR_TO_ADDR
mdefine_line|#define SC520_PAR_TO_ADDR(par) &bslash;&n;&t;(((par)&amp;SC520_PAR_ADDR_MASK) &lt;&lt; SC520_PAR_ADDR_SHIFT)
DECL|macro|SC520_PAR_SIZE_MASK
mdefine_line|#define SC520_PAR_SIZE_MASK&t;0x01ffc000
DECL|macro|SC520_PAR_SIZE_SHIFT
mdefine_line|#define SC520_PAR_SIZE_SHIFT&t;2
DECL|macro|SC520_PAR_TO_SIZE
mdefine_line|#define SC520_PAR_TO_SIZE(par) &bslash;&n;&t;((((par)&amp;SC520_PAR_SIZE_MASK) &lt;&lt; SC520_PAR_SIZE_SHIFT) + (64*1024))
DECL|macro|SC520_PAR
mdefine_line|#define SC520_PAR(cs, addr, size) &bslash;&n;&t;((cs) | &bslash;&n;&t;((((size)-(64*1024)) &gt;&gt; SC520_PAR_SIZE_SHIFT) &amp; SC520_PAR_SIZE_MASK) | &bslash;&n;&t;(((addr) &gt;&gt; SC520_PAR_ADDR_SHIFT) &amp; SC520_PAR_ADDR_MASK))
DECL|macro|SC520_PAR_BOOTCS
mdefine_line|#define SC520_PAR_BOOTCS&t;0x8a000000
DECL|macro|SC520_PAR_ROMCS1
mdefine_line|#define&t;SC520_PAR_ROMCS1&t;0xaa000000
DECL|macro|SC520_PAR_ROMCS2
mdefine_line|#define SC520_PAR_ROMCS2&t;0xca000000&t;/* Cache disabled, 64K page */
DECL|variable|nettel_mmcrp
r_static
r_void
op_star
id|nettel_mmcrp
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_MTD_CFI_INTELEXT
DECL|variable|intel_mtd
r_static
r_struct
id|mtd_info
op_star
id|intel_mtd
suffix:semicolon
macro_line|#endif
DECL|variable|amd_mtd
r_static
r_struct
id|mtd_info
op_star
id|amd_mtd
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/****************************************************************************/
macro_line|#ifdef CONFIG_MTD_CFI_INTELEXT
DECL|variable|nettel_intel_map
r_static
r_struct
id|map_info
id|nettel_intel_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear Intel&quot;
comma
dot
id|size
op_assign
l_int|0
comma
dot
id|bankwidth
op_assign
id|INTEL_BUSWIDTH
comma
)brace
suffix:semicolon
DECL|variable|nettel_intel_partitions
r_static
r_struct
id|mtd_partition
id|nettel_intel_partitions
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear kernel&quot;
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|size
op_assign
l_int|0x000e0000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear filesystem&quot;
comma
dot
id|offset
op_assign
l_int|0x00100000
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear config&quot;
comma
dot
id|offset
op_assign
l_int|0x000e0000
comma
dot
id|size
op_assign
l_int|0x00020000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear Intel&quot;
comma
dot
id|offset
op_assign
l_int|0
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear BIOS Config&quot;
comma
dot
id|offset
op_assign
l_int|0x007e0000
comma
dot
id|size
op_assign
l_int|0x00020000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear BIOS&quot;
comma
dot
id|offset
op_assign
l_int|0x007e0000
comma
dot
id|size
op_assign
l_int|0x00020000
)brace
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|nettel_amd_map
r_static
r_struct
id|map_info
id|nettel_amd_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear AMD&quot;
comma
dot
id|size
op_assign
id|AMD_WINDOW_MAXSIZE
comma
dot
id|bankwidth
op_assign
id|AMD_BUSWIDTH
comma
)brace
suffix:semicolon
DECL|variable|nettel_amd_partitions
r_static
r_struct
id|mtd_partition
id|nettel_amd_partitions
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear BIOS config&quot;
comma
dot
id|offset
op_assign
l_int|0x000e0000
comma
dot
id|size
op_assign
l_int|0x00010000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear BIOS&quot;
comma
dot
id|offset
op_assign
l_int|0x000f0000
comma
dot
id|size
op_assign
l_int|0x00010000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear AMD&quot;
comma
dot
id|offset
op_assign
l_int|0
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;SnapGear high BIOS&quot;
comma
dot
id|offset
op_assign
l_int|0x001f0000
comma
dot
id|size
op_assign
l_int|0x00010000
)brace
)brace
suffix:semicolon
DECL|macro|NUM_AMD_PARTITIONS
mdefine_line|#define NUM_AMD_PARTITIONS &bslash;&n;&t;(sizeof(nettel_amd_partitions)/sizeof(nettel_amd_partitions[0]))
multiline_comment|/****************************************************************************/
macro_line|#ifdef CONFIG_MTD_CFI_INTELEXT
multiline_comment|/*&n; *&t;Set the Intel flash back to read mode since some old boot&n; *&t;loaders don&squot;t.&n; */
DECL|function|nettel_reboot_notifier
r_static
r_int
id|nettel_reboot_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
comma
r_int
r_int
id|val
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|cfi_private
op_star
id|cfi
op_assign
id|nettel_intel_map.fldrv_priv
suffix:semicolon
r_int
r_int
id|b
suffix:semicolon
multiline_comment|/* Make sure all FLASH chips are put back into read mode */
r_for
c_loop
(paren
id|b
op_assign
l_int|0
suffix:semicolon
(paren
id|b
OL
id|nettel_intel_partitions
(braket
l_int|3
)braket
dot
id|size
)paren
suffix:semicolon
id|b
op_add_assign
l_int|0x100000
)paren
(brace
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xff
comma
l_int|0x55
comma
id|b
comma
op_amp
id|nettel_intel_map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_OK
suffix:semicolon
)brace
DECL|variable|nettel_notifier_block
r_static
r_struct
id|notifier_block
id|nettel_notifier_block
op_assign
(brace
id|nettel_reboot_notifier
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Erase the configuration file system.&n; *&t;Used to support the software reset button.&n; */
DECL|function|nettel_erasecallback
r_static
r_void
id|nettel_erasecallback
c_func
(paren
r_struct
id|erase_info
op_star
id|done
)paren
(brace
id|wait_queue_head_t
op_star
id|wait_q
op_assign
(paren
id|wait_queue_head_t
op_star
)paren
id|done-&gt;priv
suffix:semicolon
id|wake_up
c_func
(paren
id|wait_q
)paren
suffix:semicolon
)brace
DECL|variable|nettel_erase
r_static
r_struct
id|erase_info
id|nettel_erase
suffix:semicolon
DECL|function|nettel_eraseconfig
r_int
id|nettel_eraseconfig
c_func
(paren
r_void
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|wait_queue_head_t
id|wait_q
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|wait_q
)paren
suffix:semicolon
id|mtd
op_assign
id|get_mtd_device
c_func
(paren
l_int|NULL
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtd
)paren
(brace
id|nettel_erase.mtd
op_assign
id|mtd
suffix:semicolon
id|nettel_erase.callback
op_assign
id|nettel_erasecallback
suffix:semicolon
id|nettel_erase.callback
op_assign
l_int|0
suffix:semicolon
id|nettel_erase.addr
op_assign
l_int|0
suffix:semicolon
id|nettel_erase.len
op_assign
id|mtd-&gt;size
suffix:semicolon
id|nettel_erase.priv
op_assign
(paren
id|u_long
)paren
op_amp
id|wait_q
suffix:semicolon
id|nettel_erase.priv
op_assign
l_int|0
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|wait_q
comma
op_amp
id|wait
)paren
suffix:semicolon
id|ret
op_assign
id|MTD_ERASE
c_func
(paren
id|mtd
comma
op_amp
id|nettel_erase
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|wait_q
comma
op_amp
id|wait
)paren
suffix:semicolon
id|put_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Wait for erase to finish. */
id|remove_wait_queue
c_func
(paren
op_amp
id|wait_q
comma
op_amp
id|wait
)paren
suffix:semicolon
id|put_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|function|nettel_eraseconfig
r_int
id|nettel_eraseconfig
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/****************************************************************************/
DECL|function|nettel_init
r_int
id|__init
id|nettel_init
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
op_star
id|amdpar
suffix:semicolon
r_int
r_int
id|amdaddr
comma
id|maxsize
suffix:semicolon
r_int
id|num_amd_partitions
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_MTD_CFI_INTELEXT
r_volatile
r_int
r_int
op_star
id|intel0par
comma
op_star
id|intel1par
suffix:semicolon
r_int
r_int
id|orig_bootcspar
comma
id|orig_romcs1par
suffix:semicolon
r_int
r_int
id|intel0addr
comma
id|intel0size
suffix:semicolon
r_int
r_int
id|intel1addr
comma
id|intel1size
suffix:semicolon
r_int
id|intelboot
comma
id|intel0cs
comma
id|intel1cs
suffix:semicolon
r_int
id|num_intel_partitions
suffix:semicolon
macro_line|#endif
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|nettel_mmcrp
op_assign
(paren
r_void
op_star
)paren
id|ioremap_nocache
c_func
(paren
l_int|0xfffef000
comma
l_int|4096
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nettel_mmcrp
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SNAPGEAR: failed to disable MMCR cache??&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* Set CPU clock to be 33.000MHz */
op_star
(paren
(paren
r_int
r_char
op_star
)paren
(paren
id|nettel_mmcrp
op_plus
l_int|0xc64
)paren
)paren
op_assign
l_int|0x01
suffix:semicolon
id|amdpar
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|nettel_mmcrp
op_plus
l_int|0xc4
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MTD_CFI_INTELEXT
id|intelboot
op_assign
l_int|0
suffix:semicolon
id|intel0cs
op_assign
id|SC520_PAR_ROMCS1
suffix:semicolon
id|intel0par
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|nettel_mmcrp
op_plus
l_int|0xc0
)paren
suffix:semicolon
id|intel1cs
op_assign
id|SC520_PAR_ROMCS2
suffix:semicolon
id|intel1par
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|nettel_mmcrp
op_plus
l_int|0xbc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Save the CS settings then ensure ROMCS1 and ROMCS2 are off,&n;&t; *&t;otherwise they might clash with where we try to map BOOTCS.&n;&t; */
id|orig_bootcspar
op_assign
op_star
id|amdpar
suffix:semicolon
id|orig_romcs1par
op_assign
op_star
id|intel0par
suffix:semicolon
op_star
id|intel0par
op_assign
l_int|0
suffix:semicolon
op_star
id|intel1par
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *&t;The first thing to do is determine if we have a separate&n;&t; *&t;boot FLASH device. Typically this is a small (1 to 2MB)&n;&t; *&t;AMD FLASH part. It seems that device size is about the&n;&t; *&t;only way to tell if this is the case...&n;&t; */
id|amdaddr
op_assign
l_int|0x20000000
suffix:semicolon
id|maxsize
op_assign
id|AMD_WINDOW_MAXSIZE
suffix:semicolon
op_star
id|amdpar
op_assign
id|SC520_PAR
c_func
(paren
id|SC520_PAR_BOOTCS
comma
id|amdaddr
comma
id|maxsize
)paren
suffix:semicolon
id|__asm__
(paren
l_string|&quot;wbinvd&quot;
)paren
suffix:semicolon
id|nettel_amd_map.phys
op_assign
id|amdaddr
suffix:semicolon
id|nettel_amd_map.virt
op_assign
(paren
r_int
r_int
)paren
id|ioremap_nocache
c_func
(paren
id|amdaddr
comma
id|maxsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nettel_amd_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SNAPGEAR: failed to ioremap() BOOTCS&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|simple_map_init
c_func
(paren
op_amp
id|nettel_amd_map
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|amd_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;jedec_probe&quot;
comma
op_amp
id|nettel_amd_map
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;SNAPGEAR: AMD flash device size = %dK&bslash;n&quot;
comma
id|amd_mtd-&gt;size
op_rshift
l_int|10
)paren
suffix:semicolon
id|amd_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/* The high BIOS partition is only present for 2MB units */
id|num_amd_partitions
op_assign
id|NUM_AMD_PARTITIONS
suffix:semicolon
r_if
c_cond
(paren
id|amd_mtd-&gt;size
OL
id|AMD_WINDOW_MAXSIZE
)paren
id|num_amd_partitions
op_decrement
suffix:semicolon
multiline_comment|/* Don&squot;t add the partition until after the primary INTEL&squot;s */
macro_line|#ifdef CONFIG_MTD_CFI_INTELEXT
multiline_comment|/*&n;&t;&t; *&t;Map the Intel flash into memory after the AMD&n;&t;&t; *&t;It has to start on a multiple of maxsize.&n;&t;&t; */
id|maxsize
op_assign
id|SC520_PAR_TO_SIZE
c_func
(paren
id|orig_romcs1par
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maxsize
OL
(paren
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
)paren
id|maxsize
op_assign
(paren
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|intel0addr
op_assign
id|amdaddr
op_plus
id|maxsize
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
macro_line|#ifdef CONFIG_MTD_CFI_INTELEXT
multiline_comment|/* INTEL boot FLASH */
id|intelboot
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|orig_romcs1par
)paren
(brace
id|intel0cs
op_assign
id|SC520_PAR_BOOTCS
suffix:semicolon
id|intel0par
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|nettel_mmcrp
op_plus
l_int|0xc4
)paren
suffix:semicolon
id|intel1cs
op_assign
id|SC520_PAR_ROMCS1
suffix:semicolon
id|intel1par
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|nettel_mmcrp
op_plus
l_int|0xc0
)paren
suffix:semicolon
id|intel0addr
op_assign
id|SC520_PAR_TO_ADDR
c_func
(paren
id|orig_bootcspar
)paren
suffix:semicolon
id|maxsize
op_assign
id|SC520_PAR_TO_SIZE
c_func
(paren
id|orig_bootcspar
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Kernel base is on ROMCS1, not BOOTCS */
id|intel0cs
op_assign
id|SC520_PAR_ROMCS1
suffix:semicolon
id|intel0par
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|nettel_mmcrp
op_plus
l_int|0xc0
)paren
suffix:semicolon
id|intel1cs
op_assign
id|SC520_PAR_BOOTCS
suffix:semicolon
id|intel1par
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|nettel_mmcrp
op_plus
l_int|0xc4
)paren
suffix:semicolon
id|intel0addr
op_assign
id|SC520_PAR_TO_ADDR
c_func
(paren
id|orig_romcs1par
)paren
suffix:semicolon
id|maxsize
op_assign
id|SC520_PAR_TO_SIZE
c_func
(paren
id|orig_romcs1par
)paren
suffix:semicolon
)brace
multiline_comment|/* Destroy useless AMD MTD mapping */
id|amd_mtd
op_assign
l_int|NULL
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|nettel_amd_map.virt
)paren
suffix:semicolon
id|nettel_amd_map.virt
op_assign
(paren
r_int
r_int
)paren
l_int|NULL
suffix:semicolon
macro_line|#else
multiline_comment|/* Only AMD flash supported */
r_return
op_minus
id|ENXIO
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_MTD_CFI_INTELEXT
multiline_comment|/*&n;&t; *&t;We have determined the INTEL FLASH configuration, so lets&n;&t; *&t;go ahead and probe for them now.&n;&t; */
multiline_comment|/* Set PAR to the maximum size */
r_if
c_cond
(paren
id|maxsize
OL
(paren
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
)paren
id|maxsize
op_assign
(paren
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
op_star
id|intel0par
op_assign
id|SC520_PAR
c_func
(paren
id|intel0cs
comma
id|intel0addr
comma
id|maxsize
)paren
suffix:semicolon
multiline_comment|/* Turn other PAR off so the first probe doesn&squot;t find it */
op_star
id|intel1par
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Probe for the the size of the first Intel flash */
id|nettel_intel_map.size
op_assign
id|maxsize
suffix:semicolon
id|nettel_intel_map.phys
op_assign
id|intel0addr
suffix:semicolon
id|nettel_intel_map.virt
op_assign
(paren
r_int
r_int
)paren
id|ioremap_nocache
c_func
(paren
id|intel0addr
comma
id|maxsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nettel_intel_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SNAPGEAR: failed to ioremap() ROMCS1&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|simple_map_init
c_func
(paren
op_amp
id|nettel_intel_map
)paren
suffix:semicolon
id|intel_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|nettel_intel_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|intel_mtd
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|nettel_intel_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* Set PAR to the detected size */
id|intel0size
op_assign
id|intel_mtd-&gt;size
suffix:semicolon
op_star
id|intel0par
op_assign
id|SC520_PAR
c_func
(paren
id|intel0cs
comma
id|intel0addr
comma
id|intel0size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Map second Intel FLASH right after first. Set its size to the&n;&t; *&t;same maxsize used for the first Intel FLASH.&n;&t; */
id|intel1addr
op_assign
id|intel0addr
op_plus
id|intel0size
suffix:semicolon
op_star
id|intel1par
op_assign
id|SC520_PAR
c_func
(paren
id|intel1cs
comma
id|intel1addr
comma
id|maxsize
)paren
suffix:semicolon
id|__asm__
(paren
l_string|&quot;wbinvd&quot;
)paren
suffix:semicolon
id|maxsize
op_add_assign
id|intel0size
suffix:semicolon
multiline_comment|/* Delete the old map and probe again to do both chips */
id|map_destroy
c_func
(paren
id|intel_mtd
)paren
suffix:semicolon
id|intel_mtd
op_assign
l_int|NULL
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|nettel_intel_map.virt
)paren
suffix:semicolon
id|nettel_intel_map.size
op_assign
id|maxsize
suffix:semicolon
id|nettel_intel_map.virt
op_assign
(paren
r_int
r_int
)paren
id|ioremap_nocache
c_func
(paren
id|intel0addr
comma
id|maxsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nettel_intel_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SNAPGEAR: failed to ioremap() ROMCS1/2&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|intel_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|nettel_intel_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|intel_mtd
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|nettel_intel_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|intel1size
op_assign
id|intel_mtd-&gt;size
op_minus
id|intel0size
suffix:semicolon
r_if
c_cond
(paren
id|intel1size
OG
l_int|0
)paren
(brace
op_star
id|intel1par
op_assign
id|SC520_PAR
c_func
(paren
id|intel1cs
comma
id|intel1addr
comma
id|intel1size
)paren
suffix:semicolon
id|__asm__
(paren
l_string|&quot;wbinvd&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|intel1par
op_assign
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;SNAPGEAR: Intel flash device size = %dK&bslash;n&quot;
comma
(paren
id|intel_mtd-&gt;size
op_rshift
l_int|10
)paren
)paren
suffix:semicolon
id|intel_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
macro_line|#ifndef CONFIG_BLK_DEV_INITRD
id|ROOT_DEV
op_assign
id|MKDEV
c_func
(paren
id|MTD_BLOCK_MAJOR
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
id|num_intel_partitions
op_assign
r_sizeof
(paren
id|nettel_intel_partitions
)paren
op_div
r_sizeof
(paren
id|nettel_intel_partitions
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intelboot
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Adjust offset and size of last boot partition.&n;&t;&t; *&t;Must allow for BIOS region at end of FLASH.&n;&t;&t; */
id|nettel_intel_partitions
(braket
l_int|1
)braket
dot
id|size
op_assign
(paren
id|intel0size
op_plus
id|intel1size
)paren
op_minus
(paren
l_int|1024
op_star
l_int|1024
op_plus
id|intel_mtd-&gt;erasesize
)paren
suffix:semicolon
id|nettel_intel_partitions
(braket
l_int|3
)braket
dot
id|size
op_assign
id|intel0size
op_plus
id|intel1size
suffix:semicolon
id|nettel_intel_partitions
(braket
l_int|4
)braket
dot
id|offset
op_assign
(paren
id|intel0size
op_plus
id|intel1size
)paren
op_minus
id|intel_mtd-&gt;erasesize
suffix:semicolon
id|nettel_intel_partitions
(braket
l_int|4
)braket
dot
id|size
op_assign
id|intel_mtd-&gt;erasesize
suffix:semicolon
id|nettel_intel_partitions
(braket
l_int|5
)braket
dot
id|offset
op_assign
id|nettel_intel_partitions
(braket
l_int|4
)braket
dot
id|offset
suffix:semicolon
id|nettel_intel_partitions
(braket
l_int|5
)braket
dot
id|size
op_assign
id|nettel_intel_partitions
(braket
l_int|4
)braket
dot
id|size
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* No BIOS regions when AMD boot */
id|num_intel_partitions
op_sub_assign
l_int|2
suffix:semicolon
)brace
id|rc
op_assign
id|add_mtd_partitions
c_func
(paren
id|intel_mtd
comma
id|nettel_intel_partitions
comma
id|num_intel_partitions
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|amd_mtd
)paren
(brace
id|rc
op_assign
id|add_mtd_partitions
c_func
(paren
id|amd_mtd
comma
id|nettel_amd_partitions
comma
id|num_amd_partitions
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MTD_CFI_INTELEXT
id|register_reboot_notifier
c_func
(paren
op_amp
id|nettel_notifier_block
)paren
suffix:semicolon
macro_line|#endif
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/****************************************************************************/
DECL|function|nettel_cleanup
r_void
id|__exit
id|nettel_cleanup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_MTD_CFI_INTELEXT
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|nettel_notifier_block
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|amd_mtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|amd_mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|amd_mtd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nettel_amd_map.virt
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|nettel_amd_map.virt
)paren
suffix:semicolon
id|nettel_amd_map.virt
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MTD_CFI_INTELEXT
r_if
c_cond
(paren
id|intel_mtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|intel_mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|intel_mtd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nettel_intel_map.virt
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|nettel_intel_map.virt
)paren
suffix:semicolon
id|nettel_intel_map.virt
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/****************************************************************************/
DECL|variable|nettel_init
id|module_init
c_func
(paren
id|nettel_init
)paren
suffix:semicolon
DECL|variable|nettel_cleanup
id|module_exit
c_func
(paren
id|nettel_cleanup
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
l_string|&quot;Greg Ungerer &lt;gerg@snapgear.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SnapGear/SecureEdge FLASH support&quot;
)paren
suffix:semicolon
multiline_comment|/****************************************************************************/
eof
