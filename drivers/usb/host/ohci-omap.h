multiline_comment|/*&n; * linux/drivers/usb/host/ohci-omap.h&n; *&n; * OMAP OHCI USB controller specific defines&n; */
multiline_comment|/* OMAP USB OHCI common defines */
DECL|macro|OMAP_OHCI_NAME
mdefine_line|#define OMAP_OHCI_NAME&t;&t;&quot;omap-ohci&quot;
DECL|macro|OMAP_OHCI_BASE
mdefine_line|#define OMAP_OHCI_BASE&t;&t;0xfffba000
DECL|macro|OMAP_OHCI_SIZE
mdefine_line|#define OMAP_OHCI_SIZE&t;&t;4096
DECL|macro|HMC_CLEAR
mdefine_line|#define HMC_CLEAR&t;&t;(0x3f &lt;&lt; 1)
DECL|macro|APLL_NDPLL_SWITCH
mdefine_line|#define APLL_NDPLL_SWITCH&t;0x0001
DECL|macro|DPLL_PLL_ENABLE
mdefine_line|#define DPLL_PLL_ENABLE&t;&t;0x0010
DECL|macro|DPLL_LOCK
mdefine_line|#define DPLL_LOCK&t;&t;0x0001
DECL|macro|SOFT_REQ_REG_REQ
mdefine_line|#define SOFT_REQ_REG_REQ&t;0x0001
DECL|macro|USB_MCLK_EN
mdefine_line|#define USB_MCLK_EN&t;&t;0x0010
DECL|macro|USB_HOST_HHC_UHOST_EN
mdefine_line|#define USB_HOST_HHC_UHOST_EN&t;0x00000200
DECL|macro|SOFT_USB_OTG_REQ
mdefine_line|#define SOFT_USB_OTG_REQ&t;(1 &lt;&lt; 8)
DECL|macro|SOFT_USB_REQ
mdefine_line|#define SOFT_USB_REQ&t;&t;(1 &lt;&lt; 3)
DECL|macro|STATUS_REQ_REG
mdefine_line|#define STATUS_REQ_REG&t;&t;0xfffe0840
DECL|macro|USB_HOST_DPLL_REQ
mdefine_line|#define USB_HOST_DPLL_REQ&t;(1 &lt;&lt; 8)
DECL|macro|SOFT_DPLL_REQ
mdefine_line|#define SOFT_DPLL_REQ&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* OMAP-1510 USB OHCI defines */
DECL|macro|OMAP1510_LB_MEMSIZE
mdefine_line|#define OMAP1510_LB_MEMSIZE&t;32&t;&t;/* Should be same as SDRAM size */
DECL|macro|OMAP1510_LB_CLOCK_DIV
mdefine_line|#define OMAP1510_LB_CLOCK_DIV&t;0xfffec10c
DECL|macro|OMAP1510_LB_MMU_CTL
mdefine_line|#define OMAP1510_LB_MMU_CTL&t;0xfffec208&t;
DECL|macro|OMAP1510_LB_MMU_LCK
mdefine_line|#define OMAP1510_LB_MMU_LCK&t;0xfffec224
DECL|macro|OMAP1510_LB_MMU_LD_TLB
mdefine_line|#define OMAP1510_LB_MMU_LD_TLB&t;0xfffec228
DECL|macro|OMAP1510_LB_MMU_CAM_H
mdefine_line|#define OMAP1510_LB_MMU_CAM_H&t;0xfffec22c
DECL|macro|OMAP1510_LB_MMU_CAM_L
mdefine_line|#define OMAP1510_LB_MMU_CAM_L&t;0xfffec230
DECL|macro|OMAP1510_LB_MMU_RAM_H
mdefine_line|#define OMAP1510_LB_MMU_RAM_H&t;0xfffec234
DECL|macro|OMAP1510_LB_MMU_RAM_L
mdefine_line|#define OMAP1510_LB_MMU_RAM_L&t;0xfffec238
multiline_comment|/* OMAP-1610 USB OHCI defines */
DECL|macro|USB_TRANSCEIVER_CTRL
mdefine_line|#define USB_TRANSCEIVER_CTRL&t;0xfffe1064
DECL|macro|OTG_REV
mdefine_line|#define OTG_REV&t;&t;&t;0xfffb0400
DECL|macro|OTG_SYSCON_1
mdefine_line|#define OTG_SYSCON_1&t;&t;0xfffb0404
DECL|macro|OTG_IDLE_EN
mdefine_line|#define OTG_IDLE_EN&t;&t;(1 &lt;&lt; 15)
DECL|macro|DEV_IDLE_EN
mdefine_line|#define DEV_IDLE_EN&t;&t;(1 &lt;&lt; 13)
DECL|macro|OTG_SYSCON_2
mdefine_line|#define OTG_SYSCON_2&t;&t;0xfffb0408
DECL|macro|OTG_CTRL
mdefine_line|#define OTG_CTRL&t;&t;0xfffb040c
DECL|macro|OTG_IRQ_EN
mdefine_line|#define OTG_IRQ_EN&t;&t;0xfffb0410
DECL|macro|OTG_IRQ_SRC
mdefine_line|#define OTG_IRQ_SRC&t;&t;0xfffb0414
DECL|macro|OTG_EN
mdefine_line|#define OTG_EN&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|USBX_SYNCHRO
mdefine_line|#define USBX_SYNCHRO&t;&t;(1 &lt;&lt; 30)
DECL|macro|SRP_VBUS
mdefine_line|#define SRP_VBUS&t;&t;(1 &lt;&lt; 12)
DECL|macro|OTG_PADEN
mdefine_line|#define OTG_PADEN&t;&t;(1 &lt;&lt; 10)
DECL|macro|HMC_PADEN
mdefine_line|#define HMC_PADEN&t;&t;(1 &lt;&lt; 9)
DECL|macro|UHOST_EN
mdefine_line|#define UHOST_EN&t;&t;(1 &lt;&lt; 8)
multiline_comment|/* Hardware specific defines */
DECL|macro|OMAP1510_FPGA_HOST_CTRL
mdefine_line|#define OMAP1510_FPGA_HOST_CTRL&t;0xe800020c
eof
