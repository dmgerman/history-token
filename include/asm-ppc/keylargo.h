multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * keylargo.h: definitions for using the &quot;KeyLargo&quot; I/O controller chip.&n; *&n; */
multiline_comment|/* &quot;Pangea&quot; chipset has keylargo device-id 0x25 while core99&n; * has device-id 0x22. The rev. of the pangea one is 0, so we&n; * fake an artificial rev. in keylargo_rev by oring 0x100&n; */
DECL|macro|KL_PANGEA_REV
mdefine_line|#define KL_PANGEA_REV&t;&t;0x100
multiline_comment|/* offset from base for feature control registers */
DECL|macro|KEYLARGO_MBCR
mdefine_line|#define KEYLARGO_MBCR&t;&t;0x34&t;/* Media bay control/status */
DECL|macro|KEYLARGO_FCR0
mdefine_line|#define KEYLARGO_FCR0&t;&t;0x38
DECL|macro|KEYLARGO_FCR1
mdefine_line|#define KEYLARGO_FCR1&t;&t;0x3c
DECL|macro|KEYLARGO_FCR2
mdefine_line|#define KEYLARGO_FCR2&t;&t;0x40
DECL|macro|KEYLARGO_FCR3
mdefine_line|#define KEYLARGO_FCR3&t;&t;0x44
DECL|macro|KEYLARGO_FCR4
mdefine_line|#define KEYLARGO_FCR4&t;&t;0x48
multiline_comment|/* GPIO registers */
DECL|macro|KEYLARGO_GPIO_LEVELS0
mdefine_line|#define KEYLARGO_GPIO_LEVELS0&t;&t;0x50
DECL|macro|KEYLARGO_GPIO_LEVELS1
mdefine_line|#define KEYLARGO_GPIO_LEVELS1&t;&t;0x54
DECL|macro|KEYLARGO_GPIO_EXTINT_0
mdefine_line|#define KEYLARGO_GPIO_EXTINT_0&t;&t;0x58
DECL|macro|KEYLARGO_GPIO_EXTINT_CNT
mdefine_line|#define KEYLARGO_GPIO_EXTINT_CNT&t;18
DECL|macro|KEYLARGO_GPIO_0
mdefine_line|#define KEYLARGO_GPIO_0&t;&t;&t;0x6A
DECL|macro|KEYLARGO_GPIO_CNT
mdefine_line|#define KEYLARGO_GPIO_CNT&t;&t;17
DECL|macro|KEYLARGO_GPIO_EXTINT_DUAL_EDGE
mdefine_line|#define KEYLARGO_GPIO_EXTINT_DUAL_EDGE&t;0x80
DECL|macro|KEYLARGO_GPIO_OUTPUT_ENABLE
mdefine_line|#define KEYLARGO_GPIO_OUTPUT_ENABLE&t;0x04
DECL|macro|KEYLARGO_GPIO_OUTOUT_DATA
mdefine_line|#define KEYLARGO_GPIO_OUTOUT_DATA&t;0x01
DECL|macro|KEYLARGO_GPIO_INPUT_DATA
mdefine_line|#define KEYLARGO_GPIO_INPUT_DATA&t;0x02
multiline_comment|/* Specific GPIO regs */
DECL|macro|KL_GPIO_MODEM_RESET
mdefine_line|#define KL_GPIO_MODEM_RESET&t;&t;(KEYLARGO_GPIO_0+0x03)
DECL|macro|KL_GPIO_MODEM_POWER
mdefine_line|#define KL_GPIO_MODEM_POWER&t;&t;(KEYLARGO_GPIO_0+0x02) /* Pangea */
DECL|macro|KL_GPIO_SOUND_POWER
mdefine_line|#define KL_GPIO_SOUND_POWER&t;&t;(KEYLARGO_GPIO_0+0x05)
multiline_comment|/* Hrm... this one is only to be used on Pismo. It seeem to also&n; * control the timebase enable on other machines. Still to be&n; * experimented... --BenH.&n; */
DECL|macro|KL_GPIO_FW_CABLE_POWER
mdefine_line|#define KL_GPIO_FW_CABLE_POWER&t;&t;(KEYLARGO_GPIO_0+0x09)
DECL|macro|KL_GPIO_TB_ENABLE
mdefine_line|#define KL_GPIO_TB_ENABLE&t;&t;(KEYLARGO_GPIO_0+0x09)
DECL|macro|KL_GPIO_ETH_PHY_RESET
mdefine_line|#define KL_GPIO_ETH_PHY_RESET&t;&t;(KEYLARGO_GPIO_0+0x10)
DECL|macro|KL_GPIO_EXTINT_CPU1
mdefine_line|#define KL_GPIO_EXTINT_CPU1&t;&t;(KEYLARGO_GPIO_0+0x0a)
DECL|macro|KL_GPIO_EXTINT_CPU1_ASSERT
mdefine_line|#define KL_GPIO_EXTINT_CPU1_ASSERT&t;0x04
DECL|macro|KL_GPIO_EXTINT_CPU1_RELEASE
mdefine_line|#define KL_GPIO_EXTINT_CPU1_RELEASE&t;0x38
DECL|macro|KL_GPIO_RESET_CPU0
mdefine_line|#define KL_GPIO_RESET_CPU0&t;&t;(KEYLARGO_GPIO_EXTINT_0+0x03)
DECL|macro|KL_GPIO_RESET_CPU1
mdefine_line|#define KL_GPIO_RESET_CPU1&t;&t;(KEYLARGO_GPIO_EXTINT_0+0x04)
DECL|macro|KL_GPIO_RESET_CPU2
mdefine_line|#define KL_GPIO_RESET_CPU2&t;&t;(KEYLARGO_GPIO_EXTINT_0+0x0f)
DECL|macro|KL_GPIO_RESET_CPU3
mdefine_line|#define KL_GPIO_RESET_CPU3&t;&t;(KEYLARGO_GPIO_EXTINT_0+0x10)
DECL|macro|KL_GPIO_PMU_MESSAGE_IRQ
mdefine_line|#define KL_GPIO_PMU_MESSAGE_IRQ&t;&t;(KEYLARGO_GPIO_EXTINT_0+0x09)
DECL|macro|KL_GPIO_PMU_MESSAGE_BIT
mdefine_line|#define KL_GPIO_PMU_MESSAGE_BIT&t;&t;KEYLARGO_GPIO_INPUT_DATA
DECL|macro|KL_GPIO_MEDIABAY_IRQ
mdefine_line|#define KL_GPIO_MEDIABAY_IRQ&t;&t;(KEYLARGO_GPIO_EXTINT_0+0x0e)
DECL|macro|KL_GPIO_AIRPORT_0
mdefine_line|#define KL_GPIO_AIRPORT_0&t;&t;(KEYLARGO_GPIO_EXTINT_0+0x0a)
DECL|macro|KL_GPIO_AIRPORT_1
mdefine_line|#define KL_GPIO_AIRPORT_1&t;&t;(KEYLARGO_GPIO_EXTINT_0+0x0d)
DECL|macro|KL_GPIO_AIRPORT_2
mdefine_line|#define KL_GPIO_AIRPORT_2&t;&t;(KEYLARGO_GPIO_0+0x0d)
DECL|macro|KL_GPIO_AIRPORT_3
mdefine_line|#define KL_GPIO_AIRPORT_3&t;&t;(KEYLARGO_GPIO_0+0x0e)
DECL|macro|KL_GPIO_AIRPORT_4
mdefine_line|#define KL_GPIO_AIRPORT_4&t;&t;(KEYLARGO_GPIO_0+0x0f)
multiline_comment|/*&n; * Bits in feature control register&n; */
DECL|macro|KL_MBCR_MB0_PCI_ENABLE
mdefine_line|#define KL_MBCR_MB0_PCI_ENABLE&t;&t;0x00000800&t;/* exist ? */
DECL|macro|KL_MBCR_MB0_IDE_ENABLE
mdefine_line|#define KL_MBCR_MB0_IDE_ENABLE&t;&t;0x00001000
DECL|macro|KL_MBCR_MB0_FLOPPY_ENABLE
mdefine_line|#define KL_MBCR_MB0_FLOPPY_ENABLE&t;0x00002000&t;/* exist ? */
DECL|macro|KL_MBCR_MB0_SOUND_ENABLE
mdefine_line|#define KL_MBCR_MB0_SOUND_ENABLE&t;0x00004000&t;/* hrm... */
DECL|macro|KL_MBCR_MB0_DEV_MASK
mdefine_line|#define KL_MBCR_MB0_DEV_MASK&t;&t;0x00007800
DECL|macro|KL_MBCR_MB0_DEV_POWER
mdefine_line|#define KL_MBCR_MB0_DEV_POWER&t;&t;0x00000400
DECL|macro|KL_MBCR_MB0_DEV_RESET
mdefine_line|#define KL_MBCR_MB0_DEV_RESET&t;&t;0x00000200
DECL|macro|KL_MBCR_MB0_ENABLE
mdefine_line|#define KL_MBCR_MB0_ENABLE&t;&t;0x00000100
DECL|macro|KL_MBCR_MB1_PCI_ENABLE
mdefine_line|#define KL_MBCR_MB1_PCI_ENABLE&t;&t;0x08000000&t;/* exist ? */
DECL|macro|KL_MBCR_MB1_IDE_ENABLE
mdefine_line|#define KL_MBCR_MB1_IDE_ENABLE&t;&t;0x10000000
DECL|macro|KL_MBCR_MB1_FLOPPY_ENABLE
mdefine_line|#define KL_MBCR_MB1_FLOPPY_ENABLE&t;0x20000000&t;/* exist ? */
DECL|macro|KL_MBCR_MB1_SOUND_ENABLE
mdefine_line|#define KL_MBCR_MB1_SOUND_ENABLE&t;0x40000000&t;/* hrm... */
DECL|macro|KL_MBCR_MB1_DEV_MASK
mdefine_line|#define KL_MBCR_MB1_DEV_MASK&t;&t;0x78000000
DECL|macro|KL_MBCR_MB1_DEV_POWER
mdefine_line|#define KL_MBCR_MB1_DEV_POWER&t;&t;0x04000000
DECL|macro|KL_MBCR_MB1_DEV_RESET
mdefine_line|#define KL_MBCR_MB1_DEV_RESET&t;&t;0x02000000
DECL|macro|KL_MBCR_MB1_ENABLE
mdefine_line|#define KL_MBCR_MB1_ENABLE&t;&t;0x01000000
DECL|macro|KL0_SCC_B_INTF_ENABLE
mdefine_line|#define KL0_SCC_B_INTF_ENABLE&t;&t;0x00000001
DECL|macro|KL0_SCC_A_INTF_ENABLE
mdefine_line|#define KL0_SCC_A_INTF_ENABLE&t;&t;0x00000002
DECL|macro|KL0_SCC_SLOWPCLK
mdefine_line|#define KL0_SCC_SLOWPCLK&t;&t;0x00000004
DECL|macro|KL0_SCC_RESET
mdefine_line|#define KL0_SCC_RESET&t;&t;&t;0x00000008
DECL|macro|KL0_SCCA_ENABLE
mdefine_line|#define KL0_SCCA_ENABLE&t;&t;&t;0x00000010
DECL|macro|KL0_SCCB_ENABLE
mdefine_line|#define KL0_SCCB_ENABLE&t;&t;&t;0x00000020
DECL|macro|KL0_SCC_CELL_ENABLE
mdefine_line|#define KL0_SCC_CELL_ENABLE&t;&t;0x00000040
DECL|macro|KL0_IRDA_HIGH_BAND
mdefine_line|#define KL0_IRDA_HIGH_BAND&t;&t;0x00000100
DECL|macro|KL0_IRDA_SOURCE2_SEL
mdefine_line|#define KL0_IRDA_SOURCE2_SEL&t;&t;0x00000200
DECL|macro|KL0_IRDA_SOURCE1_SEL
mdefine_line|#define KL0_IRDA_SOURCE1_SEL&t;&t;0x00000400
DECL|macro|KL0_IRDA_RESET
mdefine_line|#define KL0_IRDA_RESET&t;&t;&t;0x00000800
DECL|macro|KL0_IRDA_DEFAULT1
mdefine_line|#define KL0_IRDA_DEFAULT1&t;&t;0x00001000
DECL|macro|KL0_IRDA_DEFAULT0
mdefine_line|#define KL0_IRDA_DEFAULT0&t;&t;0x00002000
DECL|macro|KL0_IRDA_FAST_CONNECT
mdefine_line|#define KL0_IRDA_FAST_CONNECT&t;&t;0x00004000
DECL|macro|KL0_IRDA_ENABLE
mdefine_line|#define KL0_IRDA_ENABLE&t;&t;&t;0x00008000
DECL|macro|KL0_IRDA_CLK32_ENABLE
mdefine_line|#define KL0_IRDA_CLK32_ENABLE&t;&t;0x00010000
DECL|macro|KL0_IRDA_CLK19_ENABLE
mdefine_line|#define KL0_IRDA_CLK19_ENABLE&t;&t;0x00020000
DECL|macro|KL0_USB0_PAD_SUSPEND0
mdefine_line|#define KL0_USB0_PAD_SUSPEND0&t;&t;0x00040000
DECL|macro|KL0_USB0_PAD_SUSPEND1
mdefine_line|#define KL0_USB0_PAD_SUSPEND1&t;&t;0x00080000
DECL|macro|KL0_USB0_CELL_ENABLE
mdefine_line|#define KL0_USB0_CELL_ENABLE&t;&t;0x00100000
DECL|macro|KL0_USB1_PAD_SUSPEND0
mdefine_line|#define KL0_USB1_PAD_SUSPEND0&t;&t;0x00400000
DECL|macro|KL0_USB1_PAD_SUSPEND1
mdefine_line|#define KL0_USB1_PAD_SUSPEND1&t;&t;0x00800000
DECL|macro|KL0_USB1_CELL_ENABLE
mdefine_line|#define KL0_USB1_CELL_ENABLE&t;&t;0x01000000
DECL|macro|KL0_USB_REF_SUSPEND
mdefine_line|#define KL0_USB_REF_SUSPEND&t;&t;0x10000000
DECL|macro|KL0_SERIAL_ENABLE
mdefine_line|#define KL0_SERIAL_ENABLE&t;&t;(KL0_SCC_B_INTF_ENABLE | &bslash;&n;&t;&t;&t;&t;&t;KL0_SCC_SLOWPCLK | &bslash;&n;&t;&t;&t;&t;&t;KL0_SCC_CELL_ENABLE | KL0_SCCA_ENABLE)
DECL|macro|KL1_AUDIO_SEL_22MCLK
mdefine_line|#define KL1_AUDIO_SEL_22MCLK&t;&t;0x00000002
DECL|macro|KL1_AUDIO_CLK_ENABLE_BIT
mdefine_line|#define KL1_AUDIO_CLK_ENABLE_BIT&t;0x00000008
DECL|macro|KL1_AUDIO_CLK_OUT_ENABLE
mdefine_line|#define KL1_AUDIO_CLK_OUT_ENABLE&t;0x00000020&t;/* Burgundy only ? */
DECL|macro|KL1_AUDIO_CELL_ENABLE
mdefine_line|#define KL1_AUDIO_CELL_ENABLE&t;&t;0x00000040
DECL|macro|KL1_AUDIO_CHOOSE
mdefine_line|#define KL1_AUDIO_CHOOSE&t;&t;0x00000080&t;/* Burgundy only ? */
DECL|macro|KL1_I2S0_CELL_ENABLE
mdefine_line|#define KL1_I2S0_CELL_ENABLE&t;&t;0x00000400
DECL|macro|KL1_I2S0_CLK_ENABLE_BIT
mdefine_line|#define KL1_I2S0_CLK_ENABLE_BIT&t;&t;0x00001000
DECL|macro|KL1_I2S0_ENABLE
mdefine_line|#define KL1_I2S0_ENABLE&t;&t;&t;0x00002000
DECL|macro|KL1_I2S1_CELL_ENABLE
mdefine_line|#define KL1_I2S1_CELL_ENABLE&t;&t;0x00020000
DECL|macro|KL1_I2S1_CLK_ENABLE_BIT
mdefine_line|#define KL1_I2S1_CLK_ENABLE_BIT&t;&t;0x00080000
DECL|macro|KL1_I2S1_ENABLE
mdefine_line|#define KL1_I2S1_ENABLE&t;&t;&t;0x00100000
DECL|macro|KL1_EIDE0_ENABLE
mdefine_line|#define KL1_EIDE0_ENABLE&t;&t;0x00800000
DECL|macro|KL1_EIDE0_RESET_N
mdefine_line|#define KL1_EIDE0_RESET_N&t;&t;0x01000000
DECL|macro|KL1_EIDE1_ENABLE
mdefine_line|#define KL1_EIDE1_ENABLE&t;&t;0x04000000
DECL|macro|KL1_EIDE1_RESET_N
mdefine_line|#define KL1_EIDE1_RESET_N&t;&t;0x08000000
DECL|macro|KL1_UIDE_ENABLE
mdefine_line|#define KL1_UIDE_ENABLE&t;&t;&t;0x20000000
DECL|macro|KL1_UIDE_RESET_N
mdefine_line|#define KL1_UIDE_RESET_N&t;&t;0x40000000
DECL|macro|KL2_IOBUS_ENABLE
mdefine_line|#define KL2_IOBUS_ENABLE&t;&t;0x00000002
DECL|macro|KL2_SLEEP_STATE_BIT
mdefine_line|#define KL2_SLEEP_STATE_BIT&t;&t;0x00000100
DECL|macro|KL2_MPIC_ENABLE
mdefine_line|#define KL2_MPIC_ENABLE&t;&t;&t;0x00020000
DECL|macro|KL2_ALT_DATA_OUT
mdefine_line|#define KL2_ALT_DATA_OUT&t;&t;0x02000000
DECL|macro|KL2_MEM_IS_BIG
mdefine_line|#define KL2_MEM_IS_BIG&t;&t;&t;0x04000000
DECL|macro|KL2_CARDSEL_16
mdefine_line|#define KL2_CARDSEL_16&t;&t;&t;0x08000000
DECL|macro|KL3_SHUTDOWN_PLL_TOTAL
mdefine_line|#define KL3_SHUTDOWN_PLL_TOTAL&t;&t;0x00000001
DECL|macro|KL3_SHUTDOWN_PLLKW6
mdefine_line|#define KL3_SHUTDOWN_PLLKW6&t;&t;0x00000002
DECL|macro|KL3_SHUTDOWN_PLLKW4
mdefine_line|#define KL3_SHUTDOWN_PLLKW4&t;&t;0x00000004
DECL|macro|KL3_SHUTDOWN_PLLKW35
mdefine_line|#define KL3_SHUTDOWN_PLLKW35&t;&t;0x00000008
DECL|macro|KL3_SHUTDOWN_PLLKW12
mdefine_line|#define KL3_SHUTDOWN_PLLKW12&t;&t;0x00000010
DECL|macro|KL3_PLL_RESET
mdefine_line|#define KL3_PLL_RESET&t;&t;&t;0x00000020
DECL|macro|KL3_SHUTDOWN_PLL2X
mdefine_line|#define KL3_SHUTDOWN_PLL2X&t;&t;0x00000080
DECL|macro|KL3_CLK66_ENABLE
mdefine_line|#define KL3_CLK66_ENABLE&t;&t;0x00000100
DECL|macro|KL3_CLK49_ENABLE
mdefine_line|#define KL3_CLK49_ENABLE&t;&t;0x00000200
DECL|macro|KL3_CLK45_ENABLE
mdefine_line|#define KL3_CLK45_ENABLE&t;&t;0x00000400
DECL|macro|KL3_CLK31_ENABLE
mdefine_line|#define KL3_CLK31_ENABLE&t;&t;0x00000800
DECL|macro|KL3_TIMER_CLK18_ENABLE
mdefine_line|#define KL3_TIMER_CLK18_ENABLE&t;&t;0x00001000
DECL|macro|KL3_I2S1_CLK18_ENABLE
mdefine_line|#define KL3_I2S1_CLK18_ENABLE&t;&t;0x00002000
DECL|macro|KL3_I2S0_CLK18_ENABLE
mdefine_line|#define KL3_I2S0_CLK18_ENABLE&t;&t;0x00004000
DECL|macro|KL3_VIA_CLK16_ENABLE
mdefine_line|#define KL3_VIA_CLK16_ENABLE&t;&t;0x00008000
DECL|macro|KL3_STOPPING33_ENABLED
mdefine_line|#define KL3_STOPPING33_ENABLED&t;&t;0x00080000
multiline_comment|/* Port 0,1 : bus 0, port 2,3 : bus 1 */
DECL|macro|KL4_PORT_WAKEUP_ENABLE
mdefine_line|#define KL4_PORT_WAKEUP_ENABLE(p)&t;(0x00000008 &lt;&lt; ((p)&lt;&lt;3))
DECL|macro|KL4_PORT_RESUME_WAKE_EN
mdefine_line|#define KL4_PORT_RESUME_WAKE_EN(p)&t;(0x00000004 &lt;&lt; ((p)&lt;&lt;3))
DECL|macro|KL4_PORT_CONNECT_WAKE_EN
mdefine_line|#define KL4_PORT_CONNECT_WAKE_EN(p)&t;(0x00000002 &lt;&lt; ((p)&lt;&lt;3))
DECL|macro|KL4_PORT_DISCONNECT_WAKE_EN
mdefine_line|#define KL4_PORT_DISCONNECT_WAKE_EN(p)&t;(0x00000001 &lt;&lt; ((p)&lt;&lt;3))
DECL|macro|KL4_PORT_RESUME_STAT
mdefine_line|#define KL4_PORT_RESUME_STAT(p)&t;&t;(0x00000040 &lt;&lt; ((p)&lt;&lt;3))
DECL|macro|KL4_PORT_CONNECT_STAT
mdefine_line|#define KL4_PORT_CONNECT_STAT(p)&t;(0x00000020 &lt;&lt; ((p)&lt;&lt;3))
DECL|macro|KL4_PORT_DISCONNECT_STAT
mdefine_line|#define KL4_PORT_DISCONNECT_STAT(p)&t;(0x00000010 &lt;&lt; ((p)&lt;&lt;3))
eof
