multiline_comment|/*&n; * ocp_ids.h&n; *&n; * OCP device ids based on the ideas from PCI&n; *&n; * The numbers below are almost completely arbitrary, and in fact&n; * strings might work better.  -- paulus&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
multiline_comment|/*&n; * Vender  device&n; * [xxxx]  [xxxx]&n; *&n; *  Keep in order, please&n; */
multiline_comment|/* Vendor IDs 0x0001 - 0xFFFF copied from pci_ids.h */
DECL|macro|OCP_VENDOR_INVALID
mdefine_line|#define&t;OCP_VENDOR_INVALID&t;0x0000
DECL|macro|OCP_VENDOR_ARM
mdefine_line|#define&t;OCP_VENDOR_ARM&t;&t;0x0004
DECL|macro|OCP_VENDOR_FREESCALE
mdefine_line|#define OCP_VENDOR_FREESCALE&t;0x1057
DECL|macro|OCP_VENDOR_IBM
mdefine_line|#define OCP_VENDOR_IBM&t;&t;0x1014
DECL|macro|OCP_VENDOR_MOTOROLA
mdefine_line|#define OCP_VENDOR_MOTOROLA&t;OCP_VENDOR_FREESCALE
DECL|macro|OCP_VENDOR_XILINX
mdefine_line|#define&t;OCP_VENDOR_XILINX&t;0x10ee
DECL|macro|OCP_VENDOR_UNKNOWN
mdefine_line|#define&t;OCP_VENDOR_UNKNOWN&t;0xFFFF
multiline_comment|/* device identification */
multiline_comment|/* define type */
DECL|macro|OCP_FUNC_INVALID
mdefine_line|#define OCP_FUNC_INVALID&t;0x0000
multiline_comment|/* system 0x0001 - 0x001F */
multiline_comment|/* Timers 0x0020 - 0x002F */
multiline_comment|/* Serial 0x0030 - 0x006F*/
DECL|macro|OCP_FUNC_16550
mdefine_line|#define OCP_FUNC_16550&t;&t;0x0031
DECL|macro|OCP_FUNC_IIC
mdefine_line|#define OCP_FUNC_IIC&t;&t;0x0032
DECL|macro|OCP_FUNC_USB
mdefine_line|#define OCP_FUNC_USB&t;&t;0x0033
DECL|macro|OCP_FUNC_PSC_UART
mdefine_line|#define OCP_FUNC_PSC_UART&t;0x0034
multiline_comment|/* Memory devices 0x0090 - 0x009F */
DECL|macro|OCP_FUNC_MAL
mdefine_line|#define OCP_FUNC_MAL&t;&t;0x0090
DECL|macro|OCP_FUNC_DMA
mdefine_line|#define OCP_FUNC_DMA&t;&t;0x0091
multiline_comment|/* Display 0x00A0 - 0x00AF */
multiline_comment|/* Sound 0x00B0 - 0x00BF */
multiline_comment|/* Mass Storage 0x00C0 - 0xxCF */
DECL|macro|OCP_FUNC_IDE
mdefine_line|#define OCP_FUNC_IDE&t;&t;0x00C0
multiline_comment|/* Misc 0x00D0 - 0x00DF*/
DECL|macro|OCP_FUNC_GPIO
mdefine_line|#define OCP_FUNC_GPIO&t;&t;0x00D0
DECL|macro|OCP_FUNC_ZMII
mdefine_line|#define OCP_FUNC_ZMII&t;&t;0x00D1
DECL|macro|OCP_FUNC_PERFMON
mdefine_line|#define OCP_FUNC_PERFMON&t;0x00D2&t;/* Performance Monitor */
DECL|macro|OCP_FUNC_RGMII
mdefine_line|#define OCP_FUNC_RGMII&t;&t;0x00D3
DECL|macro|OCP_FUNC_TAH
mdefine_line|#define OCP_FUNC_TAH&t;&t;0x00D4
DECL|macro|OCP_FUNC_SEC2
mdefine_line|#define OCP_FUNC_SEC2&t;&t;0x00D5&t;/* Crypto/Security 2.0 */
multiline_comment|/* Network 0x0200 - 0x02FF */
DECL|macro|OCP_FUNC_EMAC
mdefine_line|#define OCP_FUNC_EMAC&t;&t;0x0200
DECL|macro|OCP_FUNC_GFAR
mdefine_line|#define OCP_FUNC_GFAR&t;&t;0x0201&t;/* TSEC &amp; FEC */
multiline_comment|/* Bridge devices 0xE00 - 0xEFF */
DECL|macro|OCP_FUNC_OPB
mdefine_line|#define OCP_FUNC_OPB&t;&t;0x0E00
DECL|macro|OCP_FUNC_UNKNOWN
mdefine_line|#define OCP_FUNC_UNKNOWN&t;0xFFFF
eof
