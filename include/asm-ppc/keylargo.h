multiline_comment|/*&n; * keylargo.h: definitions for using the &quot;KeyLargo&quot; I/O controller chip.&n; *&n; */
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
multiline_comment|/* Specific GPIO regs */
DECL|macro|KL_GPIO_ETH_PHY_RESET
mdefine_line|#define KL_GPIO_ETH_PHY_RESET&t;&t;(KEYLARGO_GPIO_0+0x10)
DECL|macro|KL_GPIO_ETH_PHY_RESET_ASSERT
mdefine_line|#define KL_GPIO_ETH_PHY_RESET_ASSERT&t;0x04
DECL|macro|KL_GPIO_ETH_PHY_RESET_RELEASE
mdefine_line|#define KL_GPIO_ETH_PHY_RESET_RELEASE&t;0x05
DECL|macro|KL_GPIO_ETH_PHY_RESET_TRISTATE
mdefine_line|#define KL_GPIO_ETH_PHY_RESET_TRISTATE&t;0x00
multiline_comment|/*&n; * Bits in feature control register&n; */
DECL|macro|KL_MBCR_MBDEV_ENABLE
mdefine_line|#define KL_MBCR_MBDEV_ENABLE&t;&t;0x00001000
DECL|macro|KL0_SCC_B_INTF_ENABLE
mdefine_line|#define KL0_SCC_B_INTF_ENABLE&t;&t;0x00000001&t;/* ??? */
DECL|macro|KL0_SCC_A_INTF_ENABLE
mdefine_line|#define KL0_SCC_A_INTF_ENABLE&t;&t;0x00000002&t;/* ??? */
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
DECL|macro|KL2_MODEM_POWER_N
mdefine_line|#define KL2_MODEM_POWER_N&t;&t;0x02000000
DECL|macro|KL2_AIRPORT_RESET_N
mdefine_line|#define KL2_AIRPORT_RESET_N&t;&t;0x08000000&t;/* Or power ? */
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
DECL|macro|KL4_SET_PORT_ENABLE
mdefine_line|#define KL4_SET_PORT_ENABLE(p)&t;&t;(0x00000008 &lt;&lt; (p&lt;&lt;3))
DECL|macro|KL4_SET_PORT_RESUME
mdefine_line|#define KL4_SET_PORT_RESUME(p)&t;&t;(0x00000004 &lt;&lt; (p&lt;&lt;3))
DECL|macro|KL4_SET_PORT_CONNECT
mdefine_line|#define KL4_SET_PORT_CONNECT(p)&t;&t;(0x00000002 &lt;&lt; (p&lt;&lt;3))
DECL|macro|KL4_SET_PORT_DISCONNECT
mdefine_line|#define KL4_SET_PORT_DISCONNECT(p)&t;(0x00000001 &lt;&lt; (p&lt;&lt;3))
DECL|macro|KL4_GET_PORT_RESUME
mdefine_line|#define KL4_GET_PORT_RESUME(p)&t;&t;(0x00000040 &lt;&lt; (p&lt;&lt;3))
DECL|macro|KL4_GET_PORT_CONNECT
mdefine_line|#define KL4_GET_PORT_CONNECT(p)&t;&t;(0x00000020 &lt;&lt; (p&lt;&lt;3))
DECL|macro|KL4_GET_PORT_DISCONNECT
mdefine_line|#define KL4_GET_PORT_DISCONNECT(p)&t;(0x00000010 &lt;&lt; (p&lt;&lt;3))
eof
