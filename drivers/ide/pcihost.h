multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; * Copyright (C) 2002 Marcin Dalecki &lt;martin@dalecki.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful, but WITHOUT&n; * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for&n; * more details.&n; */
multiline_comment|/*&n; * Declarations needed for the handling of PCI (mostly) based host chip set&n; * interfaces.&n; */
macro_line|#ifdef CONFIG_BLK_DEV_PIIX
r_extern
r_int
id|init_piix
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_VIA82CXXX
r_extern
r_int
id|init_via82cxxx
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_PDC202XX
r_extern
r_int
id|init_pdc202xx
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_RZ1000
r_extern
r_int
id|init_rz1000
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_SIS5513
r_extern
r_int
id|init_sis5513
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_CMD64X
r_extern
r_int
id|init_cmd64x
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_OPTI621
r_extern
r_int
id|init_opti621
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_TRM290
r_extern
r_int
id|init_trm290
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_NS87415
r_extern
r_int
id|init_ns87415
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_AEC62XX
r_extern
r_int
id|init_aec62xx
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_SL82C105
r_extern
r_int
id|init_sl82c105
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_HPT34X
r_extern
r_int
id|init_hpt34x
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_HPT366
r_extern
r_int
id|init_hpt366
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_ALI15X3
r_extern
r_int
id|init_ali15x3
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_CY82C693
r_extern
r_int
id|init_cy82c693
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_CS5530
r_extern
r_int
id|init_cs5530
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_AMD74XX
r_extern
r_int
id|init_amd74xx
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_SVWKS
r_extern
r_int
id|init_svwks
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IT8172
r_extern
r_int
id|init_it8172
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|init_ata_pci_misc
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Some combi chips, which can be used on the PCI bus or the VL bus can be in&n; * some systems acessed either through the PCI config space or through the&n; * hosts IO bus.  If the corresponding initialization driver is using the host&n; * IO space to deal with them please define the following.&n; */
DECL|macro|ATA_PCI_IGNORE
mdefine_line|#define&t;ATA_PCI_IGNORE&t;((void *)-1)
multiline_comment|/*&n; * Just to prevent us from having too many tinny headers we have consolidated&n; * all those declarations here.&n; */
macro_line|#ifdef CONFIG_BLK_DEV_RZ1000
r_extern
r_void
id|ide_probe_for_rz100x
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|struct|ide_pci_enablebit_s
r_typedef
r_struct
id|ide_pci_enablebit_s
(brace
DECL|member|reg
id|u8
id|reg
suffix:semicolon
multiline_comment|/* pci configuration register holding the enable-bit */
DECL|member|mask
id|u8
id|mask
suffix:semicolon
multiline_comment|/* mask used to isolate the enable-bit */
DECL|member|val
id|u8
id|val
suffix:semicolon
multiline_comment|/* expected value of masked register when &quot;enabled&quot; */
DECL|typedef|ide_pci_enablebit_t
)brace
id|ide_pci_enablebit_t
suffix:semicolon
multiline_comment|/* Flags used to untangle quirk handling.&n; */
DECL|macro|ATA_F_DMA
mdefine_line|#define ATA_F_DMA&t;0x001
DECL|macro|ATA_F_NODMA
mdefine_line|#define ATA_F_NODMA&t;0x002&t;/* no DMA mode supported at all */
DECL|macro|ATA_F_NOADMA
mdefine_line|#define ATA_F_NOADMA&t;0x004&t;/* DMA has to be enabled explicitely */
DECL|macro|ATA_F_FDMA
mdefine_line|#define ATA_F_FDMA&t;0x008&t;/* force autodma */
DECL|macro|ATA_F_FIXIRQ
mdefine_line|#define ATA_F_FIXIRQ&t;0x010&t;/* fixed irq wiring */
DECL|macro|ATA_F_SER
mdefine_line|#define ATA_F_SER&t;0x020&t;/* serialize on first and second channel interrupts */
DECL|macro|ATA_F_IRQ
mdefine_line|#define ATA_F_IRQ&t;0x040&t;/* trust IRQ information from config */
DECL|macro|ATA_F_PHACK
mdefine_line|#define ATA_F_PHACK&t;0x080&t;/* apply PROMISE hacks */
DECL|macro|ATA_F_HPTHACK
mdefine_line|#define ATA_F_HPTHACK&t;0x100&t;/* apply HPT366 hacks */
DECL|macro|ATA_F_SIMPLEX
mdefine_line|#define ATA_F_SIMPLEX&t;0x200&t;/* force treatment as simple device */
DECL|struct|ata_pci_device
r_struct
id|ata_pci_device
(brace
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
DECL|member|init_chipset
r_int
r_int
(paren
op_star
id|init_chipset
)paren
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
DECL|member|ata66_check
r_int
r_int
(paren
op_star
id|ata66_check
)paren
(paren
r_struct
id|ata_channel
op_star
)paren
suffix:semicolon
DECL|member|init_channel
r_void
(paren
op_star
id|init_channel
)paren
(paren
r_struct
id|ata_channel
op_star
)paren
suffix:semicolon
DECL|member|init_dma
r_void
(paren
op_star
id|init_dma
)paren
(paren
r_struct
id|ata_channel
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|enablebits
id|ide_pci_enablebit_t
id|enablebits
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|bootable
r_int
r_int
id|bootable
suffix:semicolon
DECL|member|extra
r_int
r_int
id|extra
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|next
r_struct
id|ata_pci_device
op_star
id|next
suffix:semicolon
multiline_comment|/* beware we link the netries in pleace */
)brace
suffix:semicolon
r_extern
r_void
id|ata_register_chipset
c_func
(paren
r_struct
id|ata_pci_device
op_star
id|d
)paren
suffix:semicolon
eof
