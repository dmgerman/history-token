macro_line|#ifndef SIIMAGE_H
DECL|macro|SIIMAGE_H
mdefine_line|#define SIIMAGE_H
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|SIIMAGE_VIRTUAL_DMAPIO
macro_line|#undef SIIMAGE_VIRTUAL_DMAPIO
DECL|macro|SIIMAGE_BUFFERED_TASKFILE
macro_line|#undef SIIMAGE_BUFFERED_TASKFILE
DECL|macro|SIIMAGE_LARGE_DMA
macro_line|#undef SIIMAGE_LARGE_DMA
DECL|macro|SII_DEBUG
mdefine_line|#define SII_DEBUG 0
macro_line|#if SII_DEBUG
DECL|macro|siiprintk
mdefine_line|#define siiprintk(x...)&t;printk(x)
macro_line|#else
DECL|macro|siiprintk
mdefine_line|#define siiprintk(x...)
macro_line|#endif
r_static
r_int
r_int
id|init_chipset_siimage
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_iops_siimage
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_hwif_siimage
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|siimage_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
dot
id|name
op_assign
l_string|&quot;SiI680&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_siimage
comma
dot
id|init_iops
op_assign
id|init_iops_siimage
comma
dot
id|init_hwif
op_assign
id|init_hwif_siimage
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
dot
id|bootable
op_assign
id|ON_BOARD
comma
)brace
comma
(brace
multiline_comment|/* 1 */
dot
id|name
op_assign
l_string|&quot;SiI3112 Serial ATA&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_siimage
comma
dot
id|init_iops
op_assign
id|init_iops_siimage
comma
dot
id|init_hwif
op_assign
id|init_hwif_siimage
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
dot
id|bootable
op_assign
id|ON_BOARD
comma
)brace
comma
(brace
multiline_comment|/* 2 */
dot
id|name
op_assign
l_string|&quot;Adaptec AAR-1210SA&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_siimage
comma
dot
id|init_iops
op_assign
id|init_iops_siimage
comma
dot
id|init_hwif
op_assign
id|init_hwif_siimage
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
dot
id|bootable
op_assign
id|ON_BOARD
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* SIIMAGE_H */
eof
