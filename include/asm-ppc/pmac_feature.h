multiline_comment|/*&n; * Definition of platform feature hooks for PowerMacs&n; * &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998 Paul Mackerras &amp;&n; *                    Ben. Herrenschmidt.&n; *                    &n; *                    &n; * Note: I removed media-bay details from the feature stuff, I beleive it&squot;s&n; *       not worth it, the media-bay driver can directly use the mac-io&n; *       ASIC registers.&n; *       &n; * Implementation note: Currently, none of these functions will block.&n; * However, they may internally protect themselves with a spinlock&n; * for way too long. Be prepared for at least some of these to block&n; * in the future.&n; * &n; * Unless specifically defined, the result code is assumed to be an&n; * error when negative, 0 is the default success result. Some functions&n; * may return additional positive result values.&n; * &n; * To keep implementation simple, all feature calls are assumed to have&n; * the prototype parameters (struct device_node* node, int value).&n; * When either is not used, pass 0.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_ASM_PMAC_FEATURE_H
DECL|macro|__PPC_ASM_PMAC_FEATURE_H
mdefine_line|#define __PPC_ASM_PMAC_FEATURE_H
multiline_comment|/*&n; * Known Mac motherboard models&n; * &n; * Please, report any error here to benh@kernel.crashing.org, thanks !&n; */
multiline_comment|/* PowerSurge are the first generation of PCI Pmacs. This include&n; * all of the Grand-Central based machines&n; */
DECL|macro|PMAC_TYPE_PSURGE
mdefine_line|#define PMAC_TYPE_PSURGE&t;&t;0x10&t;/* PowerSurge */
multiline_comment|/* Here is the infamous serie of OHare based machines&n; */
DECL|macro|PMAC_TYPE_COMET
mdefine_line|#define PMAC_TYPE_COMET&t;&t;&t;0x20&t;/* Beleived to be PowerBook 2400 */
DECL|macro|PMAC_TYPE_HOOPER
mdefine_line|#define PMAC_TYPE_HOOPER&t;&t;0x21&t;/* Beleived to be PowerBook 3400 */
DECL|macro|PMAC_TYPE_KANGA
mdefine_line|#define PMAC_TYPE_KANGA&t;&t;&t;0x22&t;/* PowerBook 3500 (first G3) */
DECL|macro|PMAC_TYPE_ALCHEMY
mdefine_line|#define PMAC_TYPE_ALCHEMY&t;&t;0x23&t;/* Alchemy motherboard base */
DECL|macro|PMAC_TYPE_GAZELLE
mdefine_line|#define PMAC_TYPE_GAZELLE&t;&t;0x24&t;/* Spartacus, some 5xxx/6xxx */
DECL|macro|PMAC_TYPE_UNKNOWN_OHARE
mdefine_line|#define PMAC_TYPE_UNKNOWN_OHARE&t;&t;0x2f&t;/* Unknown, but OHare based */
multiline_comment|/* Here are the Heathrow based machines&n; * FIXME: Differenciate wallstreet,mainstreet,wallstreetII&n; */
DECL|macro|PMAC_TYPE_GOSSAMER
mdefine_line|#define PMAC_TYPE_GOSSAMER&t;&t;0x30&t;/* Gossamer motherboard */
DECL|macro|PMAC_TYPE_SILK
mdefine_line|#define PMAC_TYPE_SILK&t;&t;&t;0x31&t;/* Desktop PowerMac G3 */
DECL|macro|PMAC_TYPE_WALLSTREET
mdefine_line|#define PMAC_TYPE_WALLSTREET&t;&t;0x32&t;/* Wallstreet/Mainstreet PowerBook*/
DECL|macro|PMAC_TYPE_UNKNOWN_HEATHROW
mdefine_line|#define PMAC_TYPE_UNKNOWN_HEATHROW&t;0x3f&t;/* Unknown but heathrow based */
multiline_comment|/* Here are newworld machines based on Paddington (heathrow derivative)&n; */
DECL|macro|PMAC_TYPE_101_PBOOK
mdefine_line|#define PMAC_TYPE_101_PBOOK&t;&t;0x40&t;/* 101 PowerBook (aka Lombard) */
DECL|macro|PMAC_TYPE_ORIG_IMAC
mdefine_line|#define PMAC_TYPE_ORIG_IMAC&t;&t;0x41&t;/* First generation iMac */
DECL|macro|PMAC_TYPE_YOSEMITE
mdefine_line|#define PMAC_TYPE_YOSEMITE&t;&t;0x42&t;/* B&amp;W G3 */
DECL|macro|PMAC_TYPE_YIKES
mdefine_line|#define PMAC_TYPE_YIKES&t;&t;&t;0x43&t;/* Yikes G4 (PCI graphics) */
DECL|macro|PMAC_TYPE_UNKNOWN_PADDINGTON
mdefine_line|#define PMAC_TYPE_UNKNOWN_PADDINGTON&t;0x4f&t;/* Unknown but paddington based */
multiline_comment|/* Core99 machines based on UniNorth 1.0 and 1.5&n; * &n; * Note: A single entry here may cover several actual models according&n; * to the device-tree. (Sawtooth is most tower G4s, FW_IMAC is most&n; * FireWire based iMacs, etc...). Those machines are too similar to be&n; * distinguished here, when they need to be differencied, use the&n; * device-tree &quot;model&quot; or &quot;compatible&quot; property.&n; */
DECL|macro|PMAC_TYPE_ORIG_IBOOK
mdefine_line|#define PMAC_TYPE_ORIG_IBOOK&t;&t;0x40&t;/* First iBook model (no firewire) */
DECL|macro|PMAC_TYPE_SAWTOOTH
mdefine_line|#define PMAC_TYPE_SAWTOOTH&t;&t;0x41&t;/* Desktop G4s */
DECL|macro|PMAC_TYPE_FW_IMAC
mdefine_line|#define PMAC_TYPE_FW_IMAC&t;&t;0x42&t;/* FireWire iMacs (except Pangea based) */
DECL|macro|PMAC_TYPE_FW_IBOOK
mdefine_line|#define PMAC_TYPE_FW_IBOOK&t;&t;0x43&t;/* FireWire iBooks (except iBook2) */
DECL|macro|PMAC_TYPE_CUBE
mdefine_line|#define PMAC_TYPE_CUBE&t;&t;&t;0x44&t;/* Cube PowerMac */
DECL|macro|PMAC_TYPE_QUICKSILVER
mdefine_line|#define PMAC_TYPE_QUICKSILVER&t;&t;0x45&t;/* QuickSilver G4s */
DECL|macro|PMAC_TYPE_PISMO
mdefine_line|#define PMAC_TYPE_PISMO&t;&t;&t;0x46&t;/* Pismo PowerBook */
DECL|macro|PMAC_TYPE_TITANIUM
mdefine_line|#define PMAC_TYPE_TITANIUM&t;&t;0x47&t;/* Titanium PowerBook */
DECL|macro|PMAC_TYPE_TITANIUM2
mdefine_line|#define PMAC_TYPE_TITANIUM2&t;&t;0x48&t;/* Titanium II PowerBook */
DECL|macro|PMAC_TYPE_UNKNOWN_CORE99
mdefine_line|#define PMAC_TYPE_UNKNOWN_CORE99&t;0x5f
multiline_comment|/* MacRISC2 machines based on the Pangea chipset&n; */
DECL|macro|PMAC_TYPE_PANGEA_IMAC
mdefine_line|#define PMAC_TYPE_PANGEA_IMAC&t;&t;0x100&t;/* Flower Power iMac */
DECL|macro|PMAC_TYPE_IBOOK2
mdefine_line|#define PMAC_TYPE_IBOOK2&t;&t;0x101&t;/* iBook2 (polycarbonate) */
DECL|macro|PMAC_TYPE_FLAT_PANEL_IMAC
mdefine_line|#define PMAC_TYPE_FLAT_PANEL_IMAC&t;0x102&t;/* Flat panel iMac */
DECL|macro|PMAC_TYPE_UNKNOWN_PANGEA
mdefine_line|#define PMAC_TYPE_UNKNOWN_PANGEA&t;0x10f
multiline_comment|/*&n; * Motherboard flags&n; */
DECL|macro|PMAC_MB_CAN_SLEEP
mdefine_line|#define PMAC_MB_CAN_SLEEP&t;&t;0x00000001
DECL|macro|PMAC_MB_HAS_FW_POWER
mdefine_line|#define PMAC_MB_HAS_FW_POWER&t;&t;0x00000002
multiline_comment|/*&n; * Feature calls supported on pmac&n; * &t;&n; */
multiline_comment|/*&n; * Use this inline wrapper&n; */
r_struct
id|device_node
suffix:semicolon
DECL|function|pmac_call_feature
r_static
r_inline
r_int
id|pmac_call_feature
c_func
(paren
r_int
id|selector
comma
r_struct
id|device_node
op_star
id|node
comma
r_int
id|param
comma
r_int
id|value
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ppc_md.feature_call
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|ppc_md
dot
id|feature_call
c_func
(paren
id|selector
comma
id|node
comma
id|param
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/* PMAC_FTR_SERIAL_ENABLE&t;(struct device_node* node, int param, int value)&n; * enable/disable an SCC side. Pass the node corresponding to the&n; * channel side as a parameter.&n; * param is the type of port&n; * if param is ored with PMAC_SCC_FLAG_XMON, then the SCC is locked enabled&n; * for use by xmon.&n; */
DECL|macro|PMAC_FTR_SCC_ENABLE
mdefine_line|#define PMAC_FTR_SCC_ENABLE&t;&t;PMAC_FTR_DEF(0)
DECL|macro|PMAC_SCC_ASYNC
mdefine_line|#define PMAC_SCC_ASYNC&t;&t;0
DECL|macro|PMAC_SCC_IRDA
mdefine_line|#define PMAC_SCC_IRDA&t;&t;1
DECL|macro|PMAC_SCC_I2S1
mdefine_line|#define PMAC_SCC_I2S1&t;&t;2
DECL|macro|PMAC_SCC_FLAG_XMON
mdefine_line|#define PMAC_SCC_FLAG_XMON&t;0x00001000
multiline_comment|/* PMAC_FTR_MODEM_ENABLE&t;(struct device_node* node, 0, int value)&n; * enable/disable the internal modem.&n; */
DECL|macro|PMAC_FTR_MODEM_ENABLE
mdefine_line|#define PMAC_FTR_MODEM_ENABLE&t;&t;PMAC_FTR_DEF(1)
multiline_comment|/* PMAC_FTR_SWIM3_ENABLE&t;(struct device_node* node, 0,int value)&n; * enable/disable the swim3 (floppy) cell of a mac-io ASIC&n; */
DECL|macro|PMAC_FTR_SWIM3_ENABLE
mdefine_line|#define PMAC_FTR_SWIM3_ENABLE&t;&t;PMAC_FTR_DEF(2)
multiline_comment|/* PMAC_FTR_MESH_ENABLE&t;&t;(struct device_node* node, 0, int value)&n; * enable/disable the mesh (scsi) cell of a mac-io ASIC&n; */
DECL|macro|PMAC_FTR_MESH_ENABLE
mdefine_line|#define PMAC_FTR_MESH_ENABLE&t;&t;PMAC_FTR_DEF(3)
multiline_comment|/* PMAC_FTR_IDE_ENABLE&t;&t;(struct device_node* node, int busID, int value)&n; * enable/disable an IDE port of a mac-io ASIC&n; * pass the busID parameter&n; */
DECL|macro|PMAC_FTR_IDE_ENABLE
mdefine_line|#define PMAC_FTR_IDE_ENABLE&t;&t;PMAC_FTR_DEF(4)
multiline_comment|/* PMAC_FTR_IDE_RESET&t;&t;(struct device_node* node, int busID, int value)&n; * assert(1)/release(0) an IDE reset line (mac-io IDE only)&n; */
DECL|macro|PMAC_FTR_IDE_RESET
mdefine_line|#define PMAC_FTR_IDE_RESET&t;&t;PMAC_FTR_DEF(5)
multiline_comment|/* PMAC_FTR_BMAC_ENABLE&t;&t;(struct device_node* node, 0, int value)&n; * enable/disable the bmac (ethernet) cell of a mac-io ASIC, also drive&n; * it&squot;s reset line&n; */
DECL|macro|PMAC_FTR_BMAC_ENABLE
mdefine_line|#define PMAC_FTR_BMAC_ENABLE&t;&t;PMAC_FTR_DEF(6)
multiline_comment|/* PMAC_FTR_GMAC_ENABLE&t;&t;(struct device_node* node, 0, int value)&n; * enable/disable the gmac (ethernet) cell of an uninorth ASIC. This&n; * control the cell&squot;s clock.&n; */
DECL|macro|PMAC_FTR_GMAC_ENABLE
mdefine_line|#define PMAC_FTR_GMAC_ENABLE&t;&t;PMAC_FTR_DEF(7)
multiline_comment|/* PMAC_FTR_GMAC_PHY_RESET&t;(struct device_node* node, 0, 0)&n; * Perform a HW reset of the PHY connected to a gmac controller.&n; * Pass the gmac device node, not the PHY node.&n; */
DECL|macro|PMAC_FTR_GMAC_PHY_RESET
mdefine_line|#define PMAC_FTR_GMAC_PHY_RESET&t;&t;PMAC_FTR_DEF(8)
multiline_comment|/* PMAC_FTR_SOUND_CHIP_ENABLE&t;(struct device_node* node, 0, int value)&n; * enable/disable the sound chip, whatever it is and provided it can&n; * acually be controlled&n; */
DECL|macro|PMAC_FTR_SOUND_CHIP_ENABLE
mdefine_line|#define PMAC_FTR_SOUND_CHIP_ENABLE&t;PMAC_FTR_DEF(9)
multiline_comment|/* -- add various tweaks related to sound routing -- */
multiline_comment|/* PMAC_FTR_AIRPORT_ENABLE&t;(struct device_node* node, 0, int value)&n; * enable/disable the airport card&n; */
DECL|macro|PMAC_FTR_AIRPORT_ENABLE
mdefine_line|#define PMAC_FTR_AIRPORT_ENABLE&t;&t;PMAC_FTR_DEF(10)
multiline_comment|/* PMAC_FTR_RESET_CPU&t;&t;(NULL, int cpu_nr, 0)&n; * toggle the reset line of a CPU on an uninorth-based SMP machine&n; */
DECL|macro|PMAC_FTR_RESET_CPU
mdefine_line|#define PMAC_FTR_RESET_CPU&t;&t;PMAC_FTR_DEF(11)
multiline_comment|/* PMAC_FTR_USB_ENABLE&t;&t;(struct device_node* node, 0, int value)&n; * enable/disable an USB cell, along with the power of the USB &quot;pad&quot;&n; * on keylargo based machines&n; */
DECL|macro|PMAC_FTR_USB_ENABLE
mdefine_line|#define PMAC_FTR_USB_ENABLE&t;&t;PMAC_FTR_DEF(12)
multiline_comment|/* PMAC_FTR_1394_ENABLE&t;&t;(struct device_node* node, 0, int value)&n; * enable/disable the firewire cell of an uninorth ASIC.&n; */
DECL|macro|PMAC_FTR_1394_ENABLE
mdefine_line|#define PMAC_FTR_1394_ENABLE&t;&t;PMAC_FTR_DEF(13)
multiline_comment|/* PMAC_FTR_1394_CABLE_POWER&t;(struct device_node* node, 0, int value)&n; * enable/disable the firewire cable power supply of the uninorth&n; * firewire cell&n; */
DECL|macro|PMAC_FTR_1394_CABLE_POWER
mdefine_line|#define PMAC_FTR_1394_CABLE_POWER&t;PMAC_FTR_DEF(14)
multiline_comment|/* PMAC_FTR_SLEEP_STATE&t;&t;(struct device_node* node, 0, int value)&n; * set the sleep state of the motherboard.&n; * Pass -1 as value to query for sleep capability&n; */
DECL|macro|PMAC_FTR_SLEEP_STATE
mdefine_line|#define PMAC_FTR_SLEEP_STATE&t;&t;PMAC_FTR_DEF(15)
multiline_comment|/* PMAC_FTR_GET_MB_INFO&t;&t;(NULL, selector, 0)&n; * &n; * returns some motherboard infos.&n; * selector: 0  - model id&n; *           1  - model flags (capabilities)&n; *           2  - model name (cast to const char *)&n; */
DECL|macro|PMAC_FTR_GET_MB_INFO
mdefine_line|#define PMAC_FTR_GET_MB_INFO&t;&t;PMAC_FTR_DEF(16)
DECL|macro|PMAC_MB_INFO_MODEL
mdefine_line|#define   PMAC_MB_INFO_MODEL&t;0
DECL|macro|PMAC_MB_INFO_FLAGS
mdefine_line|#define   PMAC_MB_INFO_FLAGS&t;1
DECL|macro|PMAC_MB_INFO_NAME
mdefine_line|#define   PMAC_MB_INFO_NAME&t;2
multiline_comment|/* PMAC_FTR_READ_GPIO&t;&t;(NULL, int index, 0)&n; *&n; * read a GPIO from a mac-io controller of type KeyLargo or Pangea.&n; * the value returned is a byte (positive), or a negative error code&n; */
DECL|macro|PMAC_FTR_READ_GPIO
mdefine_line|#define PMAC_FTR_READ_GPIO&t;&t;PMAC_FTR_DEF(17)
multiline_comment|/* PMAC_FTR_WRITE_GPIO&t;&t;(NULL, int index, int value)&n; *&n; * write a GPIO of a mac-io controller of type KeyLargo or Pangea.&n; */
DECL|macro|PMAC_FTR_WRITE_GPIO
mdefine_line|#define PMAC_FTR_WRITE_GPIO&t;&t;PMAC_FTR_DEF(18)
multiline_comment|/* Don&squot;t use those directly, they are for the sake of pmac_setup.c */
r_extern
r_int
id|pmac_do_feature_call
c_func
(paren
r_int
r_int
id|selector
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|pmac_feature_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pmac_feature_late_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|PMAC_FTR_DEF
mdefine_line|#define PMAC_FTR_DEF(x) ((_MACH_Pmac &lt;&lt; 16) | (x))
macro_line|#endif /* __PPC_ASM_PMAC_FEATURE_H */
macro_line|#endif /* __KERNEL__ */
eof
