multiline_comment|/* $Id: bkm_ax.h,v 1.5.6.3 2001/09/23 22:24:46 kai Exp $&n; *&n; * low level decls for T-Berkom cards A4T and Scitel Quadro (4*S0, passive)&n; *&n; * Author       Roland Klabunde&n; * Copyright    by Roland Klabunde   &lt;R.Klabunde@Berkom.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef&t;__BKM_AX_H__
DECL|macro|__BKM_AX_H__
mdefine_line|#define&t;__BKM_AX_H__
multiline_comment|/* Supported boards&t;(subtypes) */
DECL|macro|SCT_1
mdefine_line|#define SCT_1&t;&t;1
DECL|macro|SCT_2
mdefine_line|#define&t;SCT_2&t;&t;2
DECL|macro|SCT_3
mdefine_line|#define&t;SCT_3&t;&t;3
DECL|macro|SCT_4
mdefine_line|#define&t;SCT_4&t;&t;4
DECL|macro|BKM_A4T
mdefine_line|#define BKM_A4T&t;&t;5
DECL|macro|PLX_ADDR_PLX
mdefine_line|#define&t;PLX_ADDR_PLX&t;&t;0x14&t;/* Addr PLX configuration */
DECL|macro|PLX_ADDR_ISAC
mdefine_line|#define&t;PLX_ADDR_ISAC&t;&t;0x18&t;/* Addr ISAC */
DECL|macro|PLX_ADDR_HSCX
mdefine_line|#define&t;PLX_ADDR_HSCX&t;&t;0x1C&t;/* Addr HSCX */
DECL|macro|PLX_ADDR_ALE
mdefine_line|#define&t;PLX_ADDR_ALE&t;&t;0x20&t;/* Addr ALE */
DECL|macro|PLX_ADDR_ALEPLUS
mdefine_line|#define&t;PLX_ADDR_ALEPLUS&t;0x24&t;/* Next Addr behind ALE */
DECL|macro|PLX_SUBVEN
mdefine_line|#define&t;PLX_SUBVEN&t;&t;0x2C&t;/* Offset SubVendor */
DECL|macro|PLX_SUBSYS
mdefine_line|#define&t;PLX_SUBSYS&t;&t;0x2E&t;/* Offset SubSystem */
multiline_comment|/* Application specific registers I20 (Siemens SZB6120H) */
r_typedef
r_struct
(brace
multiline_comment|/* Video front end horizontal configuration register */
DECL|member|i20VFEHorzCfg
r_volatile
id|u_int
id|i20VFEHorzCfg
suffix:semicolon
multiline_comment|/* Offset 00 */
multiline_comment|/* Video front end vertical configuration register */
DECL|member|i20VFEVertCfg
r_volatile
id|u_int
id|i20VFEVertCfg
suffix:semicolon
multiline_comment|/* Offset 04 */
multiline_comment|/* Video front end scaler and pixel format register */
DECL|member|i20VFEScaler
r_volatile
id|u_int
id|i20VFEScaler
suffix:semicolon
multiline_comment|/* Offset 08 */
multiline_comment|/* Video display top register */
DECL|member|i20VDispTop
r_volatile
id|u_int
id|i20VDispTop
suffix:semicolon
multiline_comment|/* Offset 0C */
multiline_comment|/* Video display bottom register */
DECL|member|i20VDispBottom
r_volatile
id|u_int
id|i20VDispBottom
suffix:semicolon
multiline_comment|/* Offset 10 */
multiline_comment|/* Video stride, status and frame grab register */
DECL|member|i20VidFrameGrab
r_volatile
id|u_int
id|i20VidFrameGrab
suffix:semicolon
multiline_comment|/* Offset 14 */
multiline_comment|/* Video display configuration register */
DECL|member|i20VDispCfg
r_volatile
id|u_int
id|i20VDispCfg
suffix:semicolon
multiline_comment|/* Offset 18 */
multiline_comment|/* Video masking map top */
DECL|member|i20VMaskTop
r_volatile
id|u_int
id|i20VMaskTop
suffix:semicolon
multiline_comment|/* Offset 1C */
multiline_comment|/* Video masking map bottom */
DECL|member|i20VMaskBottom
r_volatile
id|u_int
id|i20VMaskBottom
suffix:semicolon
multiline_comment|/* Offset 20 */
multiline_comment|/* Overlay control register */
DECL|member|i20OvlyControl
r_volatile
id|u_int
id|i20OvlyControl
suffix:semicolon
multiline_comment|/* Offset 24 */
multiline_comment|/* System, PCI and general purpose pins control register */
DECL|member|i20SysControl
r_volatile
id|u_int
id|i20SysControl
suffix:semicolon
multiline_comment|/* Offset 28 */
DECL|macro|sysRESET
mdefine_line|#define&t;sysRESET&t;&t;0x01000000&t;/* bit 24:Softreset (Low)&t;&t;*/
multiline_comment|/* GPIO 4...0: Output fixed for our cfg! */
DECL|macro|sysCFG
mdefine_line|#define&t;sysCFG&t;&t;&t;0x000000E0&t;/* GPIO 7,6,5: Input */
multiline_comment|/* General purpose pins and guest bus control register */
DECL|member|i20GuestControl
r_volatile
id|u_int
id|i20GuestControl
suffix:semicolon
multiline_comment|/* Offset 2C */
DECL|macro|guestWAIT_CFG
mdefine_line|#define&t;guestWAIT_CFG&t;0x00005555&t;/* 4 PCI waits for all */
DECL|macro|guestISDN_INT_E
mdefine_line|#define&t;guestISDN_INT_E&t;0x01000000&t;/* ISDN Int en (low) */
DECL|macro|guestVID_INT_E
mdefine_line|#define&t;guestVID_INT_E &t;0x02000000&t;/* Video interrupt en (low) */
DECL|macro|guestADI1_INT_R
mdefine_line|#define&t;guestADI1_INT_R&t;0x04000000&t;/* ADI #1 int req (low) */
DECL|macro|guestADI2_INT_R
mdefine_line|#define&t;guestADI2_INT_R&t;0x08000000&t;/* ADI #2 int req (low) */
DECL|macro|guestISDN_RES
mdefine_line|#define&t;guestISDN_RES&t;0x10000000&t;/* ISDN reset bit (high) */
DECL|macro|guestADI1_INT_S
mdefine_line|#define&t;guestADI1_INT_S&t;0x20000000&t;/* ADI #1 int pending (low) */
DECL|macro|guestADI2_INT_S
mdefine_line|#define&t;guestADI2_INT_S&t;0x40000000&t;/* ADI #2 int pending (low) */
DECL|macro|guestISDN_INT_S
mdefine_line|#define&t;guestISDN_INT_S&t;0x80000000&t;/* ISAC int pending (low) */
DECL|macro|g_A4T_JADE_RES
mdefine_line|#define&t;g_A4T_JADE_RES&t;0x01000000&t;/* JADE Reset (High) */
DECL|macro|g_A4T_ISAR_RES
mdefine_line|#define&t;g_A4T_ISAR_RES&t;0x02000000&t;/* ISAR Reset (High) */
DECL|macro|g_A4T_ISAC_RES
mdefine_line|#define&t;g_A4T_ISAC_RES&t;0x04000000&t;/* ISAC Reset (High) */
DECL|macro|g_A4T_JADE_BOOTR
mdefine_line|#define&t;g_A4T_JADE_BOOTR 0x08000000&t;/* JADE enable boot SRAM (Low) NOT USED */
DECL|macro|g_A4T_ISAR_BOOTR
mdefine_line|#define&t;g_A4T_ISAR_BOOTR 0x10000000&t;/* ISAR enable boot SRAM (Low) NOT USED */
DECL|macro|g_A4T_JADE_INT_S
mdefine_line|#define&t;g_A4T_JADE_INT_S 0x20000000&t;/* JADE interrupt pnd (Low) */
DECL|macro|g_A4T_ISAR_INT_S
mdefine_line|#define&t;g_A4T_ISAR_INT_S 0x40000000&t;/* ISAR interrupt pnd (Low) */
DECL|macro|g_A4T_ISAC_INT_S
mdefine_line|#define&t;g_A4T_ISAC_INT_S 0x80000000&t;/* ISAC interrupt pnd (Low) */
DECL|member|i20CodeSource
r_volatile
id|u_int
id|i20CodeSource
suffix:semicolon
multiline_comment|/* Offset 30 */
DECL|member|i20CodeXferCtrl
r_volatile
id|u_int
id|i20CodeXferCtrl
suffix:semicolon
multiline_comment|/* Offset 34 */
DECL|member|i20CodeMemPtr
r_volatile
id|u_int
id|i20CodeMemPtr
suffix:semicolon
multiline_comment|/* Offset 38 */
DECL|member|i20IntStatus
r_volatile
id|u_int
id|i20IntStatus
suffix:semicolon
multiline_comment|/* Offset 3C */
DECL|member|i20IntCtrl
r_volatile
id|u_int
id|i20IntCtrl
suffix:semicolon
multiline_comment|/* Offset 40 */
DECL|macro|intISDN
mdefine_line|#define&t;intISDN&t;&t;0x40000000&t;/* GIRQ1En (ISAC/ADI) (High) */
DECL|macro|intVID
mdefine_line|#define&t;intVID&t;&t;0x20000000&t;/* GIRQ0En (VSYNC)    (High) */
DECL|macro|intCOD
mdefine_line|#define&t;intCOD&t;&t;0x10000000&t;/* CodRepIrqEn        (High) */
DECL|macro|intPCI
mdefine_line|#define&t;intPCI &t;&t;0x01000000&t;/* PCI IntA enable    (High) */
DECL|member|i20I2CCtrl
r_volatile
id|u_int
id|i20I2CCtrl
suffix:semicolon
multiline_comment|/* Offset 44&t;&t;&t;&t;&t;*/
DECL|typedef|I20_REGISTER_FILE
DECL|typedef|PI20_REGISTER_FILE
)brace
id|I20_REGISTER_FILE
comma
op_star
id|PI20_REGISTER_FILE
suffix:semicolon
multiline_comment|/*&n; * Postoffice structure for A4T&n; *&n; */
DECL|macro|PO_OFFSET
mdefine_line|#define&t;PO_OFFSET&t;0x00000200&t;/* Postoffice offset from base */
DECL|macro|GCS_0
mdefine_line|#define&t;GCS_0&t;&t;0x00000000 &t;/* Guest bus chip selects */
DECL|macro|GCS_1
mdefine_line|#define&t;GCS_1&t;&t;0x00100000
DECL|macro|GCS_2
mdefine_line|#define&t;GCS_2&t;&t;0x00200000
DECL|macro|GCS_3
mdefine_line|#define&t;GCS_3&t;&t;0x00300000
DECL|macro|PO_READ
mdefine_line|#define&t;PO_READ&t;&t;0x00000000&t;/* R/W from/to guest bus */
DECL|macro|PO_WRITE
mdefine_line|#define&t;PO_WRITE&t;0x00800000
DECL|macro|PO_PEND
mdefine_line|#define&t;PO_PEND&t;&t;0x02000000
DECL|macro|POSTOFFICE
mdefine_line|#define POSTOFFICE(postoffice) *(volatile unsigned int*)(postoffice)
multiline_comment|/* Wait unlimited (don&squot;t worry)&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|__WAITI20__
mdefine_line|#define&t;__WAITI20__(postoffice)&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;   &t; &t;&t;   &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;while ((POSTOFFICE(postoffice) &amp; PO_PEND)) ;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif&t;/* __BKM_AX_H__ */
eof
