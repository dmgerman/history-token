multiline_comment|/*&n; * NetChip 2280 high/full speed USB device controller.&n; * Unlike many such controllers, this one talks PCI.&n; */
multiline_comment|/*&n; * Copyright (C) 2002 NetChip Technology, Inc. (http://www.netchip.com)&n; * Copyright (C) 2003 David Brownell&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* NET2280 MEMORY MAPPED REGISTERS&n; *&n; * The register layout came from the chip documentation, and the bit&n; * number definitions were extracted from chip specification.&n; *&n; * Use the shift operator (&squot;&lt;&lt;&squot;) to build bit masks, with readl/writel&n; * to access the registers through PCI.&n; */
multiline_comment|/* main registers, BAR0 + 0x0000 */
DECL|struct|net2280_regs
r_struct
id|net2280_regs
(brace
singleline_comment|// offset 0x0000
DECL|member|devinit
id|u32
id|devinit
suffix:semicolon
DECL|macro|LOCAL_CLOCK_FREQUENCY
mdefine_line|#define     LOCAL_CLOCK_FREQUENCY                               8
DECL|macro|FORCE_PCI_RESET
mdefine_line|#define     FORCE_PCI_RESET                                     7
DECL|macro|PCI_ID
mdefine_line|#define     PCI_ID                                              6
DECL|macro|PCI_ENABLE
mdefine_line|#define     PCI_ENABLE                                          5
DECL|macro|FIFO_SOFT_RESET
mdefine_line|#define     FIFO_SOFT_RESET                                     4
DECL|macro|CFG_SOFT_RESET
mdefine_line|#define     CFG_SOFT_RESET                                      3
DECL|macro|PCI_SOFT_RESET
mdefine_line|#define     PCI_SOFT_RESET                                      2
DECL|macro|USB_SOFT_RESET
mdefine_line|#define     USB_SOFT_RESET                                      1
DECL|macro|M8051_RESET
mdefine_line|#define     M8051_RESET                                         0
DECL|member|eectl
id|u32
id|eectl
suffix:semicolon
DECL|macro|EEPROM_ADDRESS_WIDTH
mdefine_line|#define     EEPROM_ADDRESS_WIDTH                                23
DECL|macro|EEPROM_CHIP_SELECT_ACTIVE
mdefine_line|#define     EEPROM_CHIP_SELECT_ACTIVE                           22
DECL|macro|EEPROM_PRESENT
mdefine_line|#define     EEPROM_PRESENT                                      21
DECL|macro|EEPROM_VALID
mdefine_line|#define     EEPROM_VALID                                        20
DECL|macro|EEPROM_BUSY
mdefine_line|#define     EEPROM_BUSY                                         19
DECL|macro|EEPROM_CHIP_SELECT_ENABLE
mdefine_line|#define     EEPROM_CHIP_SELECT_ENABLE                           18
DECL|macro|EEPROM_BYTE_READ_START
mdefine_line|#define     EEPROM_BYTE_READ_START                              17
DECL|macro|EEPROM_BYTE_WRITE_START
mdefine_line|#define     EEPROM_BYTE_WRITE_START                             16
DECL|macro|EEPROM_READ_DATA
mdefine_line|#define     EEPROM_READ_DATA                                    8
DECL|macro|EEPROM_WRITE_DATA
mdefine_line|#define     EEPROM_WRITE_DATA                                   0
DECL|member|eeclkfreq
id|u32
id|eeclkfreq
suffix:semicolon
DECL|member|_unused0
id|u32
id|_unused0
suffix:semicolon
singleline_comment|// offset 0x0010
DECL|member|pciirqenb0
id|u32
id|pciirqenb0
suffix:semicolon
multiline_comment|/* interrupt PCI master ... */
DECL|macro|SETUP_PACKET_INTERRUPT_ENABLE
mdefine_line|#define     SETUP_PACKET_INTERRUPT_ENABLE                       7
DECL|macro|ENDPOINT_F_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_F_INTERRUPT_ENABLE                         6
DECL|macro|ENDPOINT_E_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_E_INTERRUPT_ENABLE                         5
DECL|macro|ENDPOINT_D_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_D_INTERRUPT_ENABLE                         4
DECL|macro|ENDPOINT_C_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_C_INTERRUPT_ENABLE                         3
DECL|macro|ENDPOINT_B_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_B_INTERRUPT_ENABLE                         2
DECL|macro|ENDPOINT_A_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_A_INTERRUPT_ENABLE                         1
DECL|macro|ENDPOINT_0_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_0_INTERRUPT_ENABLE                         0
DECL|member|pciirqenb1
id|u32
id|pciirqenb1
suffix:semicolon
DECL|macro|PCI_INTERRUPT_ENABLE
mdefine_line|#define     PCI_INTERRUPT_ENABLE                                31
DECL|macro|POWER_STATE_CHANGE_INTERRUPT_ENABLE
mdefine_line|#define     POWER_STATE_CHANGE_INTERRUPT_ENABLE                 27
DECL|macro|PCI_ARBITER_TIMEOUT_INTERRUPT_ENABLE
mdefine_line|#define     PCI_ARBITER_TIMEOUT_INTERRUPT_ENABLE                26
DECL|macro|PCI_PARITY_ERROR_INTERRUPT_ENABLE
mdefine_line|#define     PCI_PARITY_ERROR_INTERRUPT_ENABLE                   25
DECL|macro|PCI_MASTER_ABORT_RECEIVED_INTERRUPT_ENABLE
mdefine_line|#define     PCI_MASTER_ABORT_RECEIVED_INTERRUPT_ENABLE          20
DECL|macro|PCI_TARGET_ABORT_RECEIVED_INTERRUPT_ENABLE
mdefine_line|#define     PCI_TARGET_ABORT_RECEIVED_INTERRUPT_ENABLE          19
DECL|macro|PCI_TARGET_ABORT_ASSERTED_INTERRUPT_ENABLE
mdefine_line|#define     PCI_TARGET_ABORT_ASSERTED_INTERRUPT_ENABLE          18
DECL|macro|PCI_RETRY_ABORT_INTERRUPT_ENABLE
mdefine_line|#define     PCI_RETRY_ABORT_INTERRUPT_ENABLE                    17
DECL|macro|PCI_MASTER_CYCLE_DONE_INTERRUPT_ENABLE
mdefine_line|#define     PCI_MASTER_CYCLE_DONE_INTERRUPT_ENABLE              16
DECL|macro|GPIO_INTERRUPT_ENABLE
mdefine_line|#define     GPIO_INTERRUPT_ENABLE                               13
DECL|macro|DMA_D_INTERRUPT_ENABLE
mdefine_line|#define     DMA_D_INTERRUPT_ENABLE                              12
DECL|macro|DMA_C_INTERRUPT_ENABLE
mdefine_line|#define     DMA_C_INTERRUPT_ENABLE                              11
DECL|macro|DMA_B_INTERRUPT_ENABLE
mdefine_line|#define     DMA_B_INTERRUPT_ENABLE                              10
DECL|macro|DMA_A_INTERRUPT_ENABLE
mdefine_line|#define     DMA_A_INTERRUPT_ENABLE                              9
DECL|macro|EEPROM_DONE_INTERRUPT_ENABLE
mdefine_line|#define     EEPROM_DONE_INTERRUPT_ENABLE                        8
DECL|macro|VBUS_INTERRUPT_ENABLE
mdefine_line|#define     VBUS_INTERRUPT_ENABLE                               7
DECL|macro|CONTROL_STATUS_INTERRUPT_ENABLE
mdefine_line|#define     CONTROL_STATUS_INTERRUPT_ENABLE                     6
DECL|macro|ROOT_PORT_RESET_INTERRUPT_ENABLE
mdefine_line|#define     ROOT_PORT_RESET_INTERRUPT_ENABLE                    4
DECL|macro|SUSPEND_REQUEST_INTERRUPT_ENABLE
mdefine_line|#define     SUSPEND_REQUEST_INTERRUPT_ENABLE                    3
DECL|macro|SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE
mdefine_line|#define     SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE             2
DECL|macro|RESUME_INTERRUPT_ENABLE
mdefine_line|#define     RESUME_INTERRUPT_ENABLE                             1
DECL|macro|SOF_INTERRUPT_ENABLE
mdefine_line|#define     SOF_INTERRUPT_ENABLE                                0
DECL|member|cpu_irqenb0
id|u32
id|cpu_irqenb0
suffix:semicolon
multiline_comment|/* ... or onboard 8051 */
DECL|macro|SETUP_PACKET_INTERRUPT_ENABLE
mdefine_line|#define     SETUP_PACKET_INTERRUPT_ENABLE                       7
DECL|macro|ENDPOINT_F_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_F_INTERRUPT_ENABLE                         6
DECL|macro|ENDPOINT_E_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_E_INTERRUPT_ENABLE                         5
DECL|macro|ENDPOINT_D_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_D_INTERRUPT_ENABLE                         4
DECL|macro|ENDPOINT_C_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_C_INTERRUPT_ENABLE                         3
DECL|macro|ENDPOINT_B_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_B_INTERRUPT_ENABLE                         2
DECL|macro|ENDPOINT_A_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_A_INTERRUPT_ENABLE                         1
DECL|macro|ENDPOINT_0_INTERRUPT_ENABLE
mdefine_line|#define     ENDPOINT_0_INTERRUPT_ENABLE                         0
DECL|member|cpu_irqenb1
id|u32
id|cpu_irqenb1
suffix:semicolon
DECL|macro|CPU_INTERRUPT_ENABLE
mdefine_line|#define     CPU_INTERRUPT_ENABLE                                31
DECL|macro|POWER_STATE_CHANGE_INTERRUPT_ENABLE
mdefine_line|#define     POWER_STATE_CHANGE_INTERRUPT_ENABLE                 27
DECL|macro|PCI_ARBITER_TIMEOUT_INTERRUPT_ENABLE
mdefine_line|#define     PCI_ARBITER_TIMEOUT_INTERRUPT_ENABLE                26
DECL|macro|PCI_PARITY_ERROR_INTERRUPT_ENABLE
mdefine_line|#define     PCI_PARITY_ERROR_INTERRUPT_ENABLE                   25
DECL|macro|PCI_INTA_INTERRUPT_ENABLE
mdefine_line|#define     PCI_INTA_INTERRUPT_ENABLE                           24
DECL|macro|PCI_PME_INTERRUPT_ENABLE
mdefine_line|#define     PCI_PME_INTERRUPT_ENABLE                            23
DECL|macro|PCI_SERR_INTERRUPT_ENABLE
mdefine_line|#define     PCI_SERR_INTERRUPT_ENABLE                           22
DECL|macro|PCI_PERR_INTERRUPT_ENABLE
mdefine_line|#define     PCI_PERR_INTERRUPT_ENABLE                           21
DECL|macro|PCI_MASTER_ABORT_RECEIVED_INTERRUPT_ENABLE
mdefine_line|#define     PCI_MASTER_ABORT_RECEIVED_INTERRUPT_ENABLE          20
DECL|macro|PCI_TARGET_ABORT_RECEIVED_INTERRUPT_ENABLE
mdefine_line|#define     PCI_TARGET_ABORT_RECEIVED_INTERRUPT_ENABLE          19
DECL|macro|PCI_RETRY_ABORT_INTERRUPT_ENABLE
mdefine_line|#define     PCI_RETRY_ABORT_INTERRUPT_ENABLE                    17
DECL|macro|PCI_MASTER_CYCLE_DONE_INTERRUPT_ENABLE
mdefine_line|#define     PCI_MASTER_CYCLE_DONE_INTERRUPT_ENABLE              16
DECL|macro|GPIO_INTERRUPT_ENABLE
mdefine_line|#define     GPIO_INTERRUPT_ENABLE                               13
DECL|macro|DMA_D_INTERRUPT_ENABLE
mdefine_line|#define     DMA_D_INTERRUPT_ENABLE                              12
DECL|macro|DMA_C_INTERRUPT_ENABLE
mdefine_line|#define     DMA_C_INTERRUPT_ENABLE                              11
DECL|macro|DMA_B_INTERRUPT_ENABLE
mdefine_line|#define     DMA_B_INTERRUPT_ENABLE                              10
DECL|macro|DMA_A_INTERRUPT_ENABLE
mdefine_line|#define     DMA_A_INTERRUPT_ENABLE                              9
DECL|macro|EEPROM_DONE_INTERRUPT_ENABLE
mdefine_line|#define     EEPROM_DONE_INTERRUPT_ENABLE                        8
DECL|macro|VBUS_INTERRUPT_ENABLE
mdefine_line|#define     VBUS_INTERRUPT_ENABLE                               7
DECL|macro|CONTROL_STATUS_INTERRUPT_ENABLE
mdefine_line|#define     CONTROL_STATUS_INTERRUPT_ENABLE                     6
DECL|macro|ROOT_PORT_RESET_INTERRUPT_ENABLE
mdefine_line|#define     ROOT_PORT_RESET_INTERRUPT_ENABLE                    4
DECL|macro|SUSPEND_REQUEST_INTERRUPT_ENABLE
mdefine_line|#define     SUSPEND_REQUEST_INTERRUPT_ENABLE                    3
DECL|macro|SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE
mdefine_line|#define     SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE             2
DECL|macro|RESUME_INTERRUPT_ENABLE
mdefine_line|#define     RESUME_INTERRUPT_ENABLE                             1
DECL|macro|SOF_INTERRUPT_ENABLE
mdefine_line|#define     SOF_INTERRUPT_ENABLE                                0
singleline_comment|// offset 0x0020
DECL|member|_unused1
id|u32
id|_unused1
suffix:semicolon
DECL|member|usbirqenb1
id|u32
id|usbirqenb1
suffix:semicolon
DECL|macro|USB_INTERRUPT_ENABLE
mdefine_line|#define     USB_INTERRUPT_ENABLE                                31
DECL|macro|POWER_STATE_CHANGE_INTERRUPT_ENABLE
mdefine_line|#define     POWER_STATE_CHANGE_INTERRUPT_ENABLE                 27
DECL|macro|PCI_ARBITER_TIMEOUT_INTERRUPT_ENABLE
mdefine_line|#define     PCI_ARBITER_TIMEOUT_INTERRUPT_ENABLE                26
DECL|macro|PCI_PARITY_ERROR_INTERRUPT_ENABLE
mdefine_line|#define     PCI_PARITY_ERROR_INTERRUPT_ENABLE                   25
DECL|macro|PCI_INTA_INTERRUPT_ENABLE
mdefine_line|#define     PCI_INTA_INTERRUPT_ENABLE                           24
DECL|macro|PCI_PME_INTERRUPT_ENABLE
mdefine_line|#define     PCI_PME_INTERRUPT_ENABLE                            23
DECL|macro|PCI_SERR_INTERRUPT_ENABLE
mdefine_line|#define     PCI_SERR_INTERRUPT_ENABLE                           22
DECL|macro|PCI_PERR_INTERRUPT_ENABLE
mdefine_line|#define     PCI_PERR_INTERRUPT_ENABLE                           21
DECL|macro|PCI_MASTER_ABORT_RECEIVED_INTERRUPT_ENABLE
mdefine_line|#define     PCI_MASTER_ABORT_RECEIVED_INTERRUPT_ENABLE          20
DECL|macro|PCI_TARGET_ABORT_RECEIVED_INTERRUPT_ENABLE
mdefine_line|#define     PCI_TARGET_ABORT_RECEIVED_INTERRUPT_ENABLE          19
DECL|macro|PCI_RETRY_ABORT_INTERRUPT_ENABLE
mdefine_line|#define     PCI_RETRY_ABORT_INTERRUPT_ENABLE                    17
DECL|macro|PCI_MASTER_CYCLE_DONE_INTERRUPT_ENABLE
mdefine_line|#define     PCI_MASTER_CYCLE_DONE_INTERRUPT_ENABLE              16
DECL|macro|GPIO_INTERRUPT_ENABLE
mdefine_line|#define     GPIO_INTERRUPT_ENABLE                               13
DECL|macro|DMA_D_INTERRUPT_ENABLE
mdefine_line|#define     DMA_D_INTERRUPT_ENABLE                              12
DECL|macro|DMA_C_INTERRUPT_ENABLE
mdefine_line|#define     DMA_C_INTERRUPT_ENABLE                              11
DECL|macro|DMA_B_INTERRUPT_ENABLE
mdefine_line|#define     DMA_B_INTERRUPT_ENABLE                              10
DECL|macro|DMA_A_INTERRUPT_ENABLE
mdefine_line|#define     DMA_A_INTERRUPT_ENABLE                              9
DECL|macro|EEPROM_DONE_INTERRUPT_ENABLE
mdefine_line|#define     EEPROM_DONE_INTERRUPT_ENABLE                        8
DECL|macro|VBUS_INTERRUPT_ENABLE
mdefine_line|#define     VBUS_INTERRUPT_ENABLE                               7
DECL|macro|CONTROL_STATUS_INTERRUPT_ENABLE
mdefine_line|#define     CONTROL_STATUS_INTERRUPT_ENABLE                     6
DECL|macro|ROOT_PORT_RESET_INTERRUPT_ENABLE
mdefine_line|#define     ROOT_PORT_RESET_INTERRUPT_ENABLE                    4
DECL|macro|SUSPEND_REQUEST_INTERRUPT_ENABLE
mdefine_line|#define     SUSPEND_REQUEST_INTERRUPT_ENABLE                    3
DECL|macro|SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE
mdefine_line|#define     SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE             2
DECL|macro|RESUME_INTERRUPT_ENABLE
mdefine_line|#define     RESUME_INTERRUPT_ENABLE                             1
DECL|macro|SOF_INTERRUPT_ENABLE
mdefine_line|#define     SOF_INTERRUPT_ENABLE                                0
DECL|member|irqstat0
id|u32
id|irqstat0
suffix:semicolon
DECL|macro|INTA_ASSERTED
mdefine_line|#define     INTA_ASSERTED                                       12
DECL|macro|SETUP_PACKET_INTERRUPT
mdefine_line|#define     SETUP_PACKET_INTERRUPT                              7
DECL|macro|ENDPOINT_F_INTERRUPT
mdefine_line|#define     ENDPOINT_F_INTERRUPT                                6
DECL|macro|ENDPOINT_E_INTERRUPT
mdefine_line|#define     ENDPOINT_E_INTERRUPT                                5
DECL|macro|ENDPOINT_D_INTERRUPT
mdefine_line|#define     ENDPOINT_D_INTERRUPT                                4
DECL|macro|ENDPOINT_C_INTERRUPT
mdefine_line|#define     ENDPOINT_C_INTERRUPT                                3
DECL|macro|ENDPOINT_B_INTERRUPT
mdefine_line|#define     ENDPOINT_B_INTERRUPT                                2
DECL|macro|ENDPOINT_A_INTERRUPT
mdefine_line|#define     ENDPOINT_A_INTERRUPT                                1
DECL|macro|ENDPOINT_0_INTERRUPT
mdefine_line|#define     ENDPOINT_0_INTERRUPT                                0
DECL|member|irqstat1
id|u32
id|irqstat1
suffix:semicolon
DECL|macro|POWER_STATE_CHANGE_INTERRUPT
mdefine_line|#define     POWER_STATE_CHANGE_INTERRUPT                        27
DECL|macro|PCI_ARBITER_TIMEOUT_INTERRUPT
mdefine_line|#define     PCI_ARBITER_TIMEOUT_INTERRUPT                       26
DECL|macro|PCI_PARITY_ERROR_INTERRUPT
mdefine_line|#define     PCI_PARITY_ERROR_INTERRUPT                          25
DECL|macro|PCI_INTA_INTERRUPT
mdefine_line|#define     PCI_INTA_INTERRUPT                                  24
DECL|macro|PCI_PME_INTERRUPT
mdefine_line|#define     PCI_PME_INTERRUPT                                   23
DECL|macro|PCI_SERR_INTERRUPT
mdefine_line|#define     PCI_SERR_INTERRUPT                                  22
DECL|macro|PCI_PERR_INTERRUPT
mdefine_line|#define     PCI_PERR_INTERRUPT                                  21
DECL|macro|PCI_MASTER_ABORT_RECEIVED_INTERRUPT
mdefine_line|#define     PCI_MASTER_ABORT_RECEIVED_INTERRUPT                 20
DECL|macro|PCI_TARGET_ABORT_RECEIVED_INTERRUPT
mdefine_line|#define     PCI_TARGET_ABORT_RECEIVED_INTERRUPT                 19
DECL|macro|PCI_RETRY_ABORT_INTERRUPT
mdefine_line|#define     PCI_RETRY_ABORT_INTERRUPT                           17
DECL|macro|PCI_MASTER_CYCLE_DONE_INTERRUPT
mdefine_line|#define     PCI_MASTER_CYCLE_DONE_INTERRUPT                     16
DECL|macro|GPIO_INTERRUPT
mdefine_line|#define     GPIO_INTERRUPT                                      13
DECL|macro|DMA_D_INTERRUPT
mdefine_line|#define     DMA_D_INTERRUPT                                     12
DECL|macro|DMA_C_INTERRUPT
mdefine_line|#define     DMA_C_INTERRUPT                                     11
DECL|macro|DMA_B_INTERRUPT
mdefine_line|#define     DMA_B_INTERRUPT                                     10
DECL|macro|DMA_A_INTERRUPT
mdefine_line|#define     DMA_A_INTERRUPT                                     9
DECL|macro|EEPROM_DONE_INTERRUPT
mdefine_line|#define     EEPROM_DONE_INTERRUPT                               8
DECL|macro|VBUS_INTERRUPT
mdefine_line|#define     VBUS_INTERRUPT                                      7
DECL|macro|CONTROL_STATUS_INTERRUPT
mdefine_line|#define     CONTROL_STATUS_INTERRUPT                            6
DECL|macro|ROOT_PORT_RESET_INTERRUPT
mdefine_line|#define     ROOT_PORT_RESET_INTERRUPT                           4
DECL|macro|SUSPEND_REQUEST_INTERRUPT
mdefine_line|#define     SUSPEND_REQUEST_INTERRUPT                           3
DECL|macro|SUSPEND_REQUEST_CHANGE_INTERRUPT
mdefine_line|#define     SUSPEND_REQUEST_CHANGE_INTERRUPT                    2
DECL|macro|RESUME_INTERRUPT
mdefine_line|#define     RESUME_INTERRUPT                                    1
DECL|macro|SOF_INTERRUPT
mdefine_line|#define     SOF_INTERRUPT                                       0
singleline_comment|// offset 0x0030
DECL|member|idxaddr
id|u32
id|idxaddr
suffix:semicolon
DECL|member|idxdata
id|u32
id|idxdata
suffix:semicolon
DECL|member|fifoctl
id|u32
id|fifoctl
suffix:semicolon
DECL|macro|PCI_BASE2_RANGE
mdefine_line|#define     PCI_BASE2_RANGE                                     16
DECL|macro|IGNORE_FIFO_AVAILABILITY
mdefine_line|#define     IGNORE_FIFO_AVAILABILITY                            3
DECL|macro|PCI_BASE2_SELECT
mdefine_line|#define     PCI_BASE2_SELECT                                    2
DECL|macro|FIFO_CONFIGURATION_SELECT
mdefine_line|#define     FIFO_CONFIGURATION_SELECT                           0
DECL|member|_unused2
id|u32
id|_unused2
suffix:semicolon
singleline_comment|// offset 0x0040
DECL|member|memaddr
id|u32
id|memaddr
suffix:semicolon
DECL|macro|START
mdefine_line|#define     START                                               28
DECL|macro|DIRECTION
mdefine_line|#define     DIRECTION                                           27
DECL|macro|FIFO_DIAGNOSTIC_SELECT
mdefine_line|#define     FIFO_DIAGNOSTIC_SELECT                              24
DECL|macro|MEMORY_ADDRESS
mdefine_line|#define     MEMORY_ADDRESS                                      0
DECL|member|memdata0
id|u32
id|memdata0
suffix:semicolon
DECL|member|memdata1
id|u32
id|memdata1
suffix:semicolon
DECL|member|_unused3
id|u32
id|_unused3
suffix:semicolon
singleline_comment|// offset 0x0050
DECL|member|gpioctl
id|u32
id|gpioctl
suffix:semicolon
DECL|macro|GPIO3_LED_SELECT
mdefine_line|#define     GPIO3_LED_SELECT                                    12
DECL|macro|GPIO3_INTERRUPT_ENABLE
mdefine_line|#define     GPIO3_INTERRUPT_ENABLE                              11
DECL|macro|GPIO2_INTERRUPT_ENABLE
mdefine_line|#define     GPIO2_INTERRUPT_ENABLE                              10
DECL|macro|GPIO1_INTERRUPT_ENABLE
mdefine_line|#define     GPIO1_INTERRUPT_ENABLE                              9
DECL|macro|GPIO0_INTERRUPT_ENABLE
mdefine_line|#define     GPIO0_INTERRUPT_ENABLE                              8
DECL|macro|GPIO3_OUTPUT_ENABLE
mdefine_line|#define     GPIO3_OUTPUT_ENABLE                                 7
DECL|macro|GPIO2_OUTPUT_ENABLE
mdefine_line|#define     GPIO2_OUTPUT_ENABLE                                 6
DECL|macro|GPIO1_OUTPUT_ENABLE
mdefine_line|#define     GPIO1_OUTPUT_ENABLE                                 5
DECL|macro|GPIO0_OUTPUT_ENABLE
mdefine_line|#define     GPIO0_OUTPUT_ENABLE                                 4
DECL|macro|GPIO3_DATA
mdefine_line|#define     GPIO3_DATA                                          3
DECL|macro|GPIO2_DATA
mdefine_line|#define     GPIO2_DATA                                          2
DECL|macro|GPIO1_DATA
mdefine_line|#define     GPIO1_DATA                                          1
DECL|macro|GPIO0_DATA
mdefine_line|#define     GPIO0_DATA                                          0
DECL|member|gpiostat
id|u32
id|gpiostat
suffix:semicolon
DECL|macro|GPIO3_INTERRUPT
mdefine_line|#define     GPIO3_INTERRUPT                                     3
DECL|macro|GPIO2_INTERRUPT
mdefine_line|#define     GPIO2_INTERRUPT                                     2
DECL|macro|GPIO1_INTERRUPT
mdefine_line|#define     GPIO1_INTERRUPT                                     1
DECL|macro|GPIO0_INTERRUPT
mdefine_line|#define     GPIO0_INTERRUPT                                     0
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* usb control, BAR0 + 0x0080 */
DECL|struct|net2280_usb_regs
r_struct
id|net2280_usb_regs
(brace
singleline_comment|// offset 0x0080
DECL|member|stdrsp
id|u32
id|stdrsp
suffix:semicolon
DECL|macro|STALL_UNSUPPORTED_REQUESTS
mdefine_line|#define     STALL_UNSUPPORTED_REQUESTS                          31
DECL|macro|SET_TEST_MODE
mdefine_line|#define     SET_TEST_MODE                                       16
DECL|macro|GET_OTHER_SPEED_CONFIGURATION
mdefine_line|#define     GET_OTHER_SPEED_CONFIGURATION                       15
DECL|macro|GET_DEVICE_QUALIFIER
mdefine_line|#define     GET_DEVICE_QUALIFIER                                14
DECL|macro|SET_ADDRESS
mdefine_line|#define     SET_ADDRESS                                         13
DECL|macro|ENDPOINT_SET_CLEAR_HALT
mdefine_line|#define     ENDPOINT_SET_CLEAR_HALT                             12
DECL|macro|DEVICE_SET_CLEAR_DEVICE_REMOTE_WAKEUP
mdefine_line|#define     DEVICE_SET_CLEAR_DEVICE_REMOTE_WAKEUP               11
DECL|macro|GET_STRING_DESCRIPTOR_2
mdefine_line|#define     GET_STRING_DESCRIPTOR_2                             10
DECL|macro|GET_STRING_DESCRIPTOR_1
mdefine_line|#define     GET_STRING_DESCRIPTOR_1                             9
DECL|macro|GET_STRING_DESCRIPTOR_0
mdefine_line|#define     GET_STRING_DESCRIPTOR_0                             8
DECL|macro|GET_SET_INTERFACE
mdefine_line|#define     GET_SET_INTERFACE                                   6
DECL|macro|GET_SET_CONFIGURATION
mdefine_line|#define     GET_SET_CONFIGURATION                               5
DECL|macro|GET_CONFIGURATION_DESCRIPTOR
mdefine_line|#define     GET_CONFIGURATION_DESCRIPTOR                        4
DECL|macro|GET_DEVICE_DESCRIPTOR
mdefine_line|#define     GET_DEVICE_DESCRIPTOR                               3
DECL|macro|GET_ENDPOINT_STATUS
mdefine_line|#define     GET_ENDPOINT_STATUS                                 2
DECL|macro|GET_INTERFACE_STATUS
mdefine_line|#define     GET_INTERFACE_STATUS                                1
DECL|macro|GET_DEVICE_STATUS
mdefine_line|#define     GET_DEVICE_STATUS                                   0
DECL|member|prodvendid
id|u32
id|prodvendid
suffix:semicolon
DECL|macro|PRODUCT_ID
mdefine_line|#define     PRODUCT_ID                                          16
DECL|macro|VENDOR_ID
mdefine_line|#define     VENDOR_ID                                           0
DECL|member|relnum
id|u32
id|relnum
suffix:semicolon
DECL|member|usbctl
id|u32
id|usbctl
suffix:semicolon
DECL|macro|SERIAL_NUMBER_INDEX
mdefine_line|#define     SERIAL_NUMBER_INDEX                                 16
DECL|macro|PRODUCT_ID_STRING_ENABLE
mdefine_line|#define     PRODUCT_ID_STRING_ENABLE                            13
DECL|macro|VENDOR_ID_STRING_ENABLE
mdefine_line|#define     VENDOR_ID_STRING_ENABLE                             12
DECL|macro|USB_ROOT_PORT_WAKEUP_ENABLE
mdefine_line|#define     USB_ROOT_PORT_WAKEUP_ENABLE                         11
DECL|macro|VBUS_PIN
mdefine_line|#define     VBUS_PIN                                            10
DECL|macro|TIMED_DISCONNECT
mdefine_line|#define     TIMED_DISCONNECT                                    9
DECL|macro|SUSPEND_IMMEDIATELY
mdefine_line|#define     SUSPEND_IMMEDIATELY                                 7
DECL|macro|SELF_POWERED_USB_DEVICE
mdefine_line|#define     SELF_POWERED_USB_DEVICE                             6
DECL|macro|REMOTE_WAKEUP_SUPPORT
mdefine_line|#define     REMOTE_WAKEUP_SUPPORT                               5
DECL|macro|PME_POLARITY
mdefine_line|#define     PME_POLARITY                                        4
DECL|macro|USB_DETECT_ENABLE
mdefine_line|#define     USB_DETECT_ENABLE                                   3
DECL|macro|PME_WAKEUP_ENABLE
mdefine_line|#define     PME_WAKEUP_ENABLE                                   2
DECL|macro|DEVICE_REMOTE_WAKEUP_ENABLE
mdefine_line|#define     DEVICE_REMOTE_WAKEUP_ENABLE                         1
DECL|macro|SELF_POWERED_STATUS
mdefine_line|#define     SELF_POWERED_STATUS                                 0
singleline_comment|// offset 0x0090
DECL|member|usbstat
id|u32
id|usbstat
suffix:semicolon
DECL|macro|HIGH_SPEED
mdefine_line|#define     HIGH_SPEED                                          7
DECL|macro|FULL_SPEED
mdefine_line|#define     FULL_SPEED                                          6
DECL|macro|GENERATE_RESUME
mdefine_line|#define     GENERATE_RESUME                                     5
DECL|macro|GENERATE_DEVICE_REMOTE_WAKEUP
mdefine_line|#define     GENERATE_DEVICE_REMOTE_WAKEUP                       4
DECL|member|xcvrdiag
id|u32
id|xcvrdiag
suffix:semicolon
DECL|macro|FORCE_HIGH_SPEED_MODE
mdefine_line|#define     FORCE_HIGH_SPEED_MODE                               31
DECL|macro|FORCE_FULL_SPEED_MODE
mdefine_line|#define     FORCE_FULL_SPEED_MODE                               30
DECL|macro|USB_TEST_MODE
mdefine_line|#define     USB_TEST_MODE                                       24
DECL|macro|LINE_STATE
mdefine_line|#define     LINE_STATE                                          16
DECL|macro|TRANSCEIVER_OPERATION_MODE
mdefine_line|#define     TRANSCEIVER_OPERATION_MODE                          2
DECL|macro|TRANSCEIVER_SELECT
mdefine_line|#define     TRANSCEIVER_SELECT                                  1
DECL|macro|TERMINATION_SELECT
mdefine_line|#define     TERMINATION_SELECT                                  0
DECL|member|setup0123
id|u32
id|setup0123
suffix:semicolon
DECL|member|setup4567
id|u32
id|setup4567
suffix:semicolon
singleline_comment|// offset 0x0090
DECL|member|_unused0
id|u32
id|_unused0
suffix:semicolon
DECL|member|ouraddr
id|u32
id|ouraddr
suffix:semicolon
DECL|macro|FORCE_IMMEDIATE
mdefine_line|#define     FORCE_IMMEDIATE                                     7
DECL|macro|OUR_USB_ADDRESS
mdefine_line|#define     OUR_USB_ADDRESS                                     0
DECL|member|ourconfig
id|u32
id|ourconfig
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* pci control, BAR0 + 0x0100 */
DECL|struct|net2280_pci_regs
r_struct
id|net2280_pci_regs
(brace
singleline_comment|// offset 0x0100
DECL|member|pcimstctl
id|u32
id|pcimstctl
suffix:semicolon
DECL|macro|PCI_ARBITER_PARK_SELECT
mdefine_line|#define     PCI_ARBITER_PARK_SELECT                             13
DECL|macro|PCI_MULTI
mdefine_line|#define     PCI_MULTI LEVEL_ARBITER                             12
DECL|macro|PCI_RETRY_ABORT_ENABLE
mdefine_line|#define     PCI_RETRY_ABORT_ENABLE                              11
DECL|macro|DMA_MEMORY_WRITE_AND_INVALIDATE_ENABLE
mdefine_line|#define     DMA_MEMORY_WRITE_AND_INVALIDATE_ENABLE              10
DECL|macro|DMA_READ_MULTIPLE_ENABLE
mdefine_line|#define     DMA_READ_MULTIPLE_ENABLE                            9
DECL|macro|DMA_READ_LINE_ENABLE
mdefine_line|#define     DMA_READ_LINE_ENABLE                                8
DECL|macro|PCI_MASTER_COMMAND_SELECT
mdefine_line|#define     PCI_MASTER_COMMAND_SELECT                           6
DECL|macro|MEM_READ_OR_WRITE
mdefine_line|#define         MEM_READ_OR_WRITE                                   0
DECL|macro|IO_READ_OR_WRITE
mdefine_line|#define         IO_READ_OR_WRITE                                    1
DECL|macro|CFG_READ_OR_WRITE
mdefine_line|#define         CFG_READ_OR_WRITE                                   2
DECL|macro|PCI_MASTER_START
mdefine_line|#define     PCI_MASTER_START                                    5
DECL|macro|PCI_MASTER_READ_WRITE
mdefine_line|#define     PCI_MASTER_READ_WRITE                               4
DECL|macro|PCI_MASTER_WRITE
mdefine_line|#define         PCI_MASTER_WRITE                                    0
DECL|macro|PCI_MASTER_READ
mdefine_line|#define         PCI_MASTER_READ                                     1
DECL|macro|PCI_MASTER_BYTE_WRITE_ENABLES
mdefine_line|#define     PCI_MASTER_BYTE_WRITE_ENABLES                       0
DECL|member|pcimstaddr
id|u32
id|pcimstaddr
suffix:semicolon
DECL|member|pcimstdata
id|u32
id|pcimstdata
suffix:semicolon
DECL|member|pcimststat
id|u32
id|pcimststat
suffix:semicolon
DECL|macro|PCI_ARBITER_CLEAR
mdefine_line|#define     PCI_ARBITER_CLEAR                                   2
DECL|macro|PCI_EXTERNAL_ARBITER
mdefine_line|#define     PCI_EXTERNAL_ARBITER                                1
DECL|macro|PCI_HOST_MODE
mdefine_line|#define     PCI_HOST_MODE                                       0
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* dma control, BAR0 + 0x0180 ... array of four structs like this,&n; * for channels 0..3.  see also struct net2280_dma:  descriptor&n; * that can be loaded into some of these registers.&n; */
DECL|struct|net2280_dma_regs
r_struct
id|net2280_dma_regs
(brace
multiline_comment|/* [11.7] */
singleline_comment|// offset 0x0180, 0x01a0, 0x01c0, 0x01e0, 
DECL|member|dmactl
id|u32
id|dmactl
suffix:semicolon
DECL|macro|DMA_SCATTER_GATHER_DONE_INTERRUPT_ENABLE
mdefine_line|#define     DMA_SCATTER_GATHER_DONE_INTERRUPT_ENABLE            25
DECL|macro|DMA_CLEAR_COUNT_ENABLE
mdefine_line|#define     DMA_CLEAR_COUNT_ENABLE                              21
DECL|macro|DESCRIPTOR_POLLING_RATE
mdefine_line|#define     DESCRIPTOR_POLLING_RATE                             19
DECL|macro|POLL_CONTINUOUS
mdefine_line|#define         POLL_CONTINUOUS                                     0
DECL|macro|POLL_1_USEC
mdefine_line|#define         POLL_1_USEC                                         1
DECL|macro|POLL_100_USEC
mdefine_line|#define         POLL_100_USEC                                       2
DECL|macro|POLL_1_MSEC
mdefine_line|#define         POLL_1_MSEC                                         3
DECL|macro|DMA_VALID_BIT_POLLING_ENABLE
mdefine_line|#define     DMA_VALID_BIT_POLLING_ENABLE                        18
DECL|macro|DMA_VALID_BIT_ENABLE
mdefine_line|#define     DMA_VALID_BIT_ENABLE                                17
DECL|macro|DMA_SCATTER_GATHER_ENABLE
mdefine_line|#define     DMA_SCATTER_GATHER_ENABLE                           16
DECL|macro|DMA_OUT_AUTO_START_ENABLE
mdefine_line|#define     DMA_OUT_AUTO_START_ENABLE                           4
DECL|macro|DMA_PREEMPT_ENABLE
mdefine_line|#define     DMA_PREEMPT_ENABLE                                  3
DECL|macro|DMA_FIFO_VALIDATE
mdefine_line|#define     DMA_FIFO_VALIDATE                                   2
DECL|macro|DMA_ENABLE
mdefine_line|#define     DMA_ENABLE                                          1
DECL|macro|DMA_ADDRESS_HOLD
mdefine_line|#define     DMA_ADDRESS_HOLD                                    0
DECL|member|dmastat
id|u32
id|dmastat
suffix:semicolon
DECL|macro|DMA_SCATTER_GATHER_DONE_INTERRUPT
mdefine_line|#define     DMA_SCATTER_GATHER_DONE_INTERRUPT                   25
DECL|macro|DMA_TRANSACTION_DONE_INTERRUPT
mdefine_line|#define     DMA_TRANSACTION_DONE_INTERRUPT                      24
DECL|macro|DMA_ABORT
mdefine_line|#define     DMA_ABORT                                           1
DECL|macro|DMA_START
mdefine_line|#define     DMA_START                                           0
DECL|member|_unused0
id|u32
id|_unused0
(braket
l_int|2
)braket
suffix:semicolon
singleline_comment|// offset 0x0190, 0x01b0, 0x01d0, 0x01f0, 
DECL|member|dmacount
id|u32
id|dmacount
suffix:semicolon
DECL|macro|VALID_BIT
mdefine_line|#define     VALID_BIT                                           31
DECL|macro|DMA_DIRECTION
mdefine_line|#define     DMA_DIRECTION                                       30
DECL|macro|DMA_DONE_INTERRUPT_ENABLE
mdefine_line|#define     DMA_DONE_INTERRUPT_ENABLE                           29
DECL|macro|END_OF_CHAIN
mdefine_line|#define     END_OF_CHAIN                                        28
DECL|macro|DMA_BYTE_COUNT_MASK
mdefine_line|#define         DMA_BYTE_COUNT_MASK                                 ((1&lt;&lt;24)-1)
DECL|macro|DMA_BYTE_COUNT
mdefine_line|#define     DMA_BYTE_COUNT                                      0
DECL|member|dmaaddr
id|u32
id|dmaaddr
suffix:semicolon
DECL|member|dmadesc
id|u32
id|dmadesc
suffix:semicolon
DECL|member|_unused1
id|u32
id|_unused1
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* dedicated endpoint registers, BAR0 + 0x0200 */
DECL|struct|net2280_dep_regs
r_struct
id|net2280_dep_regs
(brace
multiline_comment|/* [11.8] */
singleline_comment|// offset 0x0200, 0x0210, 0x220, 0x230, 0x240
DECL|member|dep_cfg
id|u32
id|dep_cfg
suffix:semicolon
singleline_comment|// offset 0x0204, 0x0214, 0x224, 0x234, 0x244
DECL|member|dep_rsp
id|u32
id|dep_rsp
suffix:semicolon
DECL|member|_unused
id|u32
id|_unused
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* configurable endpoint registers, BAR0 + 0x0300 ... array of seven structs&n; * like this, for ep0 then the configurable endpoints A..F&n; * ep0 reserved for control; E and F have only 64 bytes of fifo&n; */
DECL|struct|net2280_ep_regs
r_struct
id|net2280_ep_regs
(brace
multiline_comment|/* [11.9] */
singleline_comment|// offset 0x0300, 0x0320, 0x0340, 0x0360, 0x0380, 0x03a0, 0x03c0
DECL|member|ep_cfg
id|u32
id|ep_cfg
suffix:semicolon
DECL|macro|ENDPOINT_BYTE_COUNT
mdefine_line|#define     ENDPOINT_BYTE_COUNT                                 16
DECL|macro|ENDPOINT_ENABLE
mdefine_line|#define     ENDPOINT_ENABLE                                     10
DECL|macro|ENDPOINT_TYPE
mdefine_line|#define     ENDPOINT_TYPE                                       8
DECL|macro|ENDPOINT_DIRECTION
mdefine_line|#define     ENDPOINT_DIRECTION                                  7
DECL|macro|ENDPOINT_NUMBER
mdefine_line|#define     ENDPOINT_NUMBER                                     0
DECL|member|ep_rsp
id|u32
id|ep_rsp
suffix:semicolon
DECL|macro|SET_NAK_OUT_PACKETS
mdefine_line|#define     SET_NAK_OUT_PACKETS                                 15
DECL|macro|SET_EP_HIDE_STATUS_PHASE
mdefine_line|#define     SET_EP_HIDE_STATUS_PHASE                            14
DECL|macro|SET_INTERRUPT_MODE
mdefine_line|#define     SET_INTERRUPT_MODE                                  12
DECL|macro|SET_CONTROL_STATUS_PHASE_HANDSHAKE
mdefine_line|#define     SET_CONTROL_STATUS_PHASE_HANDSHAKE                  11
DECL|macro|SET_NAK_OUT_PACKETS_MODE
mdefine_line|#define     SET_NAK_OUT_PACKETS_MODE                            10
DECL|macro|SET_ENDPOINT_TOGGLE
mdefine_line|#define     SET_ENDPOINT_TOGGLE                                 9
DECL|macro|SET_ENDPOINT_HALT
mdefine_line|#define     SET_ENDPOINT_HALT                                   8
DECL|macro|CLEAR_NAK_OUT_PACKETS
mdefine_line|#define     CLEAR_NAK_OUT_PACKETS                               7
DECL|macro|CLEAR_EP_HIDE_STATUS_PHASE
mdefine_line|#define     CLEAR_EP_HIDE_STATUS_PHASE                          6
DECL|macro|CLEAR_INTERRUPT_MODE
mdefine_line|#define     CLEAR_INTERRUPT_MODE                                4
DECL|macro|CLEAR_CONTROL_STATUS_PHASE_HANDSHAKE
mdefine_line|#define     CLEAR_CONTROL_STATUS_PHASE_HANDSHAKE                3
DECL|macro|CLEAR_NAK_OUT_PACKETS_MODE
mdefine_line|#define     CLEAR_NAK_OUT_PACKETS_MODE                          2
DECL|macro|CLEAR_ENDPOINT_TOGGLE
mdefine_line|#define     CLEAR_ENDPOINT_TOGGLE                               1
DECL|macro|CLEAR_ENDPOINT_HALT
mdefine_line|#define     CLEAR_ENDPOINT_HALT                                 0
DECL|member|ep_irqenb
id|u32
id|ep_irqenb
suffix:semicolon
DECL|macro|SHORT_PACKET_OUT_DONE_INTERRUPT_ENABLE
mdefine_line|#define     SHORT_PACKET_OUT_DONE_INTERRUPT_ENABLE              6
DECL|macro|SHORT_PACKET_TRANSFERRED_INTERRUPT_ENABLE
mdefine_line|#define     SHORT_PACKET_TRANSFERRED_INTERRUPT_ENABLE           5
DECL|macro|DATA_PACKET_RECEIVED_INTERRUPT_ENABLE
mdefine_line|#define     DATA_PACKET_RECEIVED_INTERRUPT_ENABLE               3
DECL|macro|DATA_PACKET_TRANSMITTED_INTERRUPT_ENABLE
mdefine_line|#define     DATA_PACKET_TRANSMITTED_INTERRUPT_ENABLE            2
DECL|macro|DATA_OUT_PING_TOKEN_INTERRUPT_ENABLE
mdefine_line|#define     DATA_OUT_PING_TOKEN_INTERRUPT_ENABLE                1
DECL|macro|DATA_IN_TOKEN_INTERRUPT_ENABLE
mdefine_line|#define     DATA_IN_TOKEN_INTERRUPT_ENABLE                      0
DECL|member|ep_stat
id|u32
id|ep_stat
suffix:semicolon
DECL|macro|FIFO_VALID_COUNT
mdefine_line|#define     FIFO_VALID_COUNT                                    24
DECL|macro|HIGH_BANDWIDTH_OUT_TRANSACTION_PID
mdefine_line|#define     HIGH_BANDWIDTH_OUT_TRANSACTION_PID                  22
DECL|macro|TIMEOUT
mdefine_line|#define     TIMEOUT                                             21
DECL|macro|USB_STALL_SENT
mdefine_line|#define     USB_STALL_SENT                                      20
DECL|macro|USB_IN_NAK_SENT
mdefine_line|#define     USB_IN_NAK_SENT                                     19
DECL|macro|USB_IN_ACK_RCVD
mdefine_line|#define     USB_IN_ACK_RCVD                                     18
DECL|macro|USB_OUT_PING_NAK_SENT
mdefine_line|#define     USB_OUT_PING_NAK_SENT                               17
DECL|macro|USB_OUT_ACK_SENT
mdefine_line|#define     USB_OUT_ACK_SENT                                    16
DECL|macro|FIFO_OVERFLOW
mdefine_line|#define     FIFO_OVERFLOW                                       13
DECL|macro|FIFO_UNDERFLOW
mdefine_line|#define     FIFO_UNDERFLOW                                      12
DECL|macro|FIFO_FULL
mdefine_line|#define     FIFO_FULL                                           11
DECL|macro|FIFO_EMPTY
mdefine_line|#define     FIFO_EMPTY                                          10
DECL|macro|FIFO_FLUSH
mdefine_line|#define     FIFO_FLUSH                                          9
DECL|macro|SHORT_PACKET_OUT_DONE_INTERRUPT
mdefine_line|#define     SHORT_PACKET_OUT_DONE_INTERRUPT                     6
DECL|macro|SHORT_PACKET_TRANSFERRED_INTERRUPT
mdefine_line|#define     SHORT_PACKET_TRANSFERRED_INTERRUPT                  5
DECL|macro|NAK_OUT_PACKETS
mdefine_line|#define     NAK_OUT_PACKETS                                     4
DECL|macro|DATA_PACKET_RECEIVED_INTERRUPT
mdefine_line|#define     DATA_PACKET_RECEIVED_INTERRUPT                      3
DECL|macro|DATA_PACKET_TRANSMITTED_INTERRUPT
mdefine_line|#define     DATA_PACKET_TRANSMITTED_INTERRUPT                   2
DECL|macro|DATA_OUT_PING_TOKEN_INTERRUPT
mdefine_line|#define     DATA_OUT_PING_TOKEN_INTERRUPT                       1
DECL|macro|DATA_IN_TOKEN_INTERRUPT
mdefine_line|#define     DATA_IN_TOKEN_INTERRUPT                             0
singleline_comment|// offset 0x0310, 0x0330, 0x0350, 0x0370, 0x0390, 0x03b0, 0x03d0
DECL|member|ep_avail
id|u32
id|ep_avail
suffix:semicolon
DECL|member|ep_data
id|u32
id|ep_data
suffix:semicolon
DECL|member|_unused0
id|u32
id|_unused0
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#ifdef&t;__KERNEL__
multiline_comment|/* indexed registers [11.10] are accessed indirectly&n; * caller must own the device lock.&n; */
r_static
r_inline
id|u32
DECL|function|get_idx_reg
id|get_idx_reg
(paren
r_struct
id|net2280_regs
op_star
id|regs
comma
id|u32
id|index
)paren
(brace
id|writel
(paren
id|index
comma
op_amp
id|regs-&gt;idxaddr
)paren
suffix:semicolon
multiline_comment|/* NOTE:  synchs device/cpu memory views */
r_return
id|readl
(paren
op_amp
id|regs-&gt;idxdata
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|set_idx_reg
id|set_idx_reg
(paren
r_struct
id|net2280_regs
op_star
id|regs
comma
id|u32
id|index
comma
id|u32
id|value
)paren
(brace
id|writel
(paren
id|index
comma
op_amp
id|regs-&gt;idxaddr
)paren
suffix:semicolon
id|writel
(paren
id|value
comma
op_amp
id|regs-&gt;idxdata
)paren
suffix:semicolon
multiline_comment|/* posted, may not be visible yet */
)brace
macro_line|#endif&t;/* __KERNEL__ */
DECL|macro|REG_DIAG
mdefine_line|#define REG_DIAG&t;&t;0x0
DECL|macro|RETRY_COUNTER
mdefine_line|#define     RETRY_COUNTER                                       16
DECL|macro|FORCE_PCI_SERR
mdefine_line|#define     FORCE_PCI_SERR                                      11
DECL|macro|FORCE_PCI_INTERRUPT
mdefine_line|#define     FORCE_PCI_INTERRUPT                                 10
DECL|macro|FORCE_USB_INTERRUPT
mdefine_line|#define     FORCE_USB_INTERRUPT                                 9
DECL|macro|FORCE_CPU_INTERRUPT
mdefine_line|#define     FORCE_CPU_INTERRUPT                                 8
DECL|macro|ILLEGAL_BYTE_ENABLES
mdefine_line|#define     ILLEGAL_BYTE_ENABLES                                5
DECL|macro|FAST_TIMES
mdefine_line|#define     FAST_TIMES                                          4
DECL|macro|FORCE_RECEIVE_ERROR
mdefine_line|#define     FORCE_RECEIVE_ERROR                                 2
DECL|macro|FORCE_TRANSMIT_CRC_ERROR
mdefine_line|#define     FORCE_TRANSMIT_CRC_ERROR                            0
DECL|macro|REG_FRAME
mdefine_line|#define REG_FRAME&t;&t;0x02&t;/* from last sof */
DECL|macro|REG_CHIPREV
mdefine_line|#define REG_CHIPREV&t;&t;0x03&t;/* in bcd */
DECL|macro|REG_HS_NAK_RATE
mdefine_line|#define&t;REG_HS_NAK_RATE&t;&t;0x0a&t;/* NAK per N uframes */
macro_line|#ifdef&t;__KERNEL__
multiline_comment|/* ep a-f highspeed and fullspeed maxpacket, addresses&n; * computed from ep-&gt;num&n; */
DECL|macro|REG_EP_MAXPKT
mdefine_line|#define REG_EP_MAXPKT(dev,num) (((num) + 1) * 0x10 + &bslash;&n;&t;&t;(((dev)-&gt;gadget.speed == USB_SPEED_HIGH) ? 0 : 1))
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* [8.3] for scatter/gather i/o&n; * use struct net2280_dma_regs bitfields&n; */
DECL|struct|net2280_dma
r_struct
id|net2280_dma
(brace
DECL|member|dmacount
id|u32
id|dmacount
suffix:semicolon
DECL|member|dmaaddr
id|u32
id|dmaaddr
suffix:semicolon
multiline_comment|/* the buffer */
DECL|member|dmadesc
id|u32
id|dmadesc
suffix:semicolon
multiline_comment|/* next dma descriptor */
DECL|member|_reserved
id|u32
id|_reserved
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* DRIVER DATA STRUCTURES and UTILITIES */
DECL|struct|net2280_ep
r_struct
id|net2280_ep
(brace
DECL|member|ep
r_struct
id|usb_ep
id|ep
suffix:semicolon
DECL|member|regs
r_struct
id|net2280_ep_regs
op_star
id|regs
suffix:semicolon
DECL|member|dma
r_struct
id|net2280_dma_regs
op_star
id|dma
suffix:semicolon
DECL|member|dummy
r_struct
id|net2280_dma
op_star
id|dummy
suffix:semicolon
DECL|member|td_dma
id|dma_addr_t
id|td_dma
suffix:semicolon
multiline_comment|/* of dummy */
DECL|member|dev
r_struct
id|net2280
op_star
id|dev
suffix:semicolon
DECL|member|irqs
r_int
r_int
id|irqs
suffix:semicolon
multiline_comment|/* analogous to a host-side qh */
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|desc
r_const
r_struct
id|usb_endpoint_descriptor
op_star
id|desc
suffix:semicolon
DECL|member|num
r_int
id|num
suffix:colon
l_int|8
comma
DECL|member|fifo_size
id|fifo_size
suffix:colon
l_int|12
comma
DECL|member|in_fifo_validate
id|in_fifo_validate
suffix:colon
l_int|1
comma
DECL|member|stopped
id|stopped
suffix:colon
l_int|1
comma
DECL|member|is_in
id|is_in
suffix:colon
l_int|1
comma
DECL|member|is_iso
id|is_iso
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|function|allow_status
r_static
r_inline
r_void
id|allow_status
(paren
r_struct
id|net2280_ep
op_star
id|ep
)paren
(brace
multiline_comment|/* ep0 only */
id|writel
(paren
(paren
l_int|1
op_lshift
id|CLEAR_CONTROL_STATUS_PHASE_HANDSHAKE
)paren
op_or
(paren
l_int|1
op_lshift
id|CLEAR_NAK_OUT_PACKETS_MODE
)paren
comma
op_amp
id|ep-&gt;regs-&gt;ep_rsp
)paren
suffix:semicolon
id|ep-&gt;stopped
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|set_halt
r_static
r_inline
r_void
id|set_halt
(paren
r_struct
id|net2280_ep
op_star
id|ep
)paren
(brace
multiline_comment|/* ep0 and bulk/intr endpoints */
id|writel
(paren
(paren
l_int|1
op_lshift
id|CLEAR_CONTROL_STATUS_PHASE_HANDSHAKE
)paren
multiline_comment|/* set NAK_OUT for erratum 0114 */
op_or
(paren
l_int|1
op_lshift
id|SET_NAK_OUT_PACKETS
)paren
op_or
(paren
l_int|1
op_lshift
id|SET_ENDPOINT_HALT
)paren
comma
op_amp
id|ep-&gt;regs-&gt;ep_rsp
)paren
suffix:semicolon
)brace
DECL|function|clear_halt
r_static
r_inline
r_void
id|clear_halt
(paren
r_struct
id|net2280_ep
op_star
id|ep
)paren
(brace
multiline_comment|/* bulk/intr endpoints */
id|writel
(paren
(paren
l_int|1
op_lshift
id|CLEAR_ENDPOINT_HALT
)paren
op_or
(paren
l_int|1
op_lshift
id|CLEAR_ENDPOINT_TOGGLE
)paren
comma
op_amp
id|ep-&gt;regs-&gt;ep_rsp
)paren
suffix:semicolon
)brace
multiline_comment|/* count (&lt;= 4) bytes in the next fifo write will be valid */
DECL|function|set_fifo_bytecount
r_static
r_inline
r_void
id|set_fifo_bytecount
(paren
r_struct
id|net2280_ep
op_star
id|ep
comma
r_int
id|count
)paren
(brace
id|writeb
(paren
id|count
comma
l_int|2
op_plus
(paren
id|u8
op_star
)paren
op_amp
id|ep-&gt;regs-&gt;ep_cfg
)paren
suffix:semicolon
)brace
DECL|struct|net2280_request
r_struct
id|net2280_request
(brace
DECL|member|req
r_struct
id|usb_request
id|req
suffix:semicolon
DECL|member|td
r_struct
id|net2280_dma
op_star
id|td
suffix:semicolon
DECL|member|td_dma
id|dma_addr_t
id|td_dma
suffix:semicolon
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|mapped
r_int
id|mapped
suffix:colon
l_int|1
comma
DECL|member|dma_done
id|dma_done
suffix:colon
l_int|1
comma
DECL|member|valid
id|valid
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|net2280
r_struct
id|net2280
(brace
multiline_comment|/* each pci device provides one gadget, several endpoints */
DECL|member|gadget
r_struct
id|usb_gadget
id|gadget
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ep
r_struct
id|net2280_ep
id|ep
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|driver
r_struct
id|usb_gadget_driver
op_star
id|driver
suffix:semicolon
DECL|member|enabled
r_int
id|enabled
suffix:colon
l_int|1
comma
DECL|member|protocol_stall
id|protocol_stall
suffix:colon
l_int|1
comma
DECL|member|got_irq
id|got_irq
suffix:colon
l_int|1
comma
DECL|member|region
id|region
suffix:colon
l_int|1
comma
DECL|member|selfpowered
id|selfpowered
suffix:colon
l_int|1
suffix:semicolon
DECL|member|chiprev
id|u16
id|chiprev
suffix:semicolon
multiline_comment|/* pci state used to access those endpoints */
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|regs
r_struct
id|net2280_regs
op_star
id|regs
suffix:semicolon
DECL|member|usb
r_struct
id|net2280_usb_regs
op_star
id|usb
suffix:semicolon
DECL|member|pci
r_struct
id|net2280_pci_regs
op_star
id|pci
suffix:semicolon
DECL|member|dma
r_struct
id|net2280_dma_regs
op_star
id|dma
suffix:semicolon
DECL|member|dep
r_struct
id|net2280_dep_regs
op_star
id|dep
suffix:semicolon
DECL|member|epregs
r_struct
id|net2280_ep_regs
op_star
id|epregs
suffix:semicolon
DECL|member|requests
r_struct
id|pci_pool
op_star
id|requests
suffix:semicolon
singleline_comment|// statistics...
)brace
suffix:semicolon
macro_line|#ifdef USE_RDK_LEDS
DECL|function|net2280_led_init
r_static
r_inline
r_void
id|net2280_led_init
(paren
r_struct
id|net2280
op_star
id|dev
)paren
(brace
multiline_comment|/* LED3 (green) is on during USB activity. note erratum 0113. */
id|writel
(paren
(paren
l_int|1
op_lshift
id|GPIO3_LED_SELECT
)paren
op_or
(paren
l_int|1
op_lshift
id|GPIO3_OUTPUT_ENABLE
)paren
op_or
(paren
l_int|1
op_lshift
id|GPIO2_OUTPUT_ENABLE
)paren
op_or
(paren
l_int|1
op_lshift
id|GPIO1_OUTPUT_ENABLE
)paren
op_or
(paren
l_int|1
op_lshift
id|GPIO0_OUTPUT_ENABLE
)paren
comma
op_amp
id|dev-&gt;regs-&gt;gpioctl
)paren
suffix:semicolon
)brace
multiline_comment|/* indicate speed with bi-color LED 0/1 */
r_static
r_inline
DECL|function|net2280_led_speed
r_void
id|net2280_led_speed
(paren
r_struct
id|net2280
op_star
id|dev
comma
r_enum
id|usb_device_speed
id|speed
)paren
(brace
id|u32
id|val
op_assign
id|readl
(paren
op_amp
id|dev-&gt;regs-&gt;gpioctl
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_case
id|USB_SPEED_HIGH
suffix:colon
multiline_comment|/* green */
id|val
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|GPIO0_DATA
)paren
suffix:semicolon
id|val
op_or_assign
(paren
l_int|1
op_lshift
id|GPIO1_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_SPEED_FULL
suffix:colon
multiline_comment|/* red */
id|val
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|GPIO1_DATA
)paren
suffix:semicolon
id|val
op_or_assign
(paren
l_int|1
op_lshift
id|GPIO0_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* (off/black) */
id|val
op_and_assign
op_complement
(paren
(paren
l_int|1
op_lshift
id|GPIO1_DATA
)paren
op_or
(paren
l_int|1
op_lshift
id|GPIO0_DATA
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|writel
(paren
id|val
comma
op_amp
id|dev-&gt;regs-&gt;gpioctl
)paren
suffix:semicolon
)brace
multiline_comment|/* indicate power with LED 2 */
DECL|function|net2280_led_active
r_static
r_inline
r_void
id|net2280_led_active
(paren
r_struct
id|net2280
op_star
id|dev
comma
r_int
id|is_active
)paren
(brace
id|u32
id|val
op_assign
id|readl
(paren
op_amp
id|dev-&gt;regs-&gt;gpioctl
)paren
suffix:semicolon
singleline_comment|// FIXME this LED never seems to turn on.
r_if
c_cond
(paren
id|is_active
)paren
id|val
op_or_assign
id|GPIO2_DATA
suffix:semicolon
r_else
id|val
op_and_assign
op_complement
id|GPIO2_DATA
suffix:semicolon
id|writel
(paren
id|val
comma
op_amp
id|dev-&gt;regs-&gt;gpioctl
)paren
suffix:semicolon
)brace
DECL|function|net2280_led_shutdown
r_static
r_inline
r_void
id|net2280_led_shutdown
(paren
r_struct
id|net2280
op_star
id|dev
)paren
(brace
multiline_comment|/* turn off all four GPIO*_DATA bits */
id|writel
(paren
id|readl
(paren
op_amp
id|dev-&gt;regs-&gt;gpioctl
)paren
op_amp
op_complement
l_int|0x0f
comma
op_amp
id|dev-&gt;regs-&gt;gpioctl
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|net2280_led_init
mdefine_line|#define net2280_led_init(dev)&t;&t;do { } while (0)
DECL|macro|net2280_led_speed
mdefine_line|#define net2280_led_speed(dev, speed)&t;do { } while (0)
DECL|macro|net2280_led_shutdown
mdefine_line|#define net2280_led_shutdown(dev)&t;do { } while (0)
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|macro|xprintk
mdefine_line|#define xprintk(dev,level,fmt,args...) &bslash;&n;&t;printk(level &quot;%s %s: &quot; fmt , driver_name , &bslash;&n;&t;&t;&t;pci_name(dev-&gt;pdev) , ## args)
macro_line|#ifdef DEBUG
DECL|macro|DEBUG
macro_line|#undef DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG(dev,fmt,args...) &bslash;&n;&t;xprintk(dev , KERN_DEBUG , fmt , ## args)
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(dev,fmt,args...) &bslash;&n;&t;do { } while (0)
macro_line|#endif /* DEBUG */
macro_line|#ifdef VERBOSE
DECL|macro|VDEBUG
mdefine_line|#define VDEBUG DEBUG
macro_line|#else
DECL|macro|VDEBUG
mdefine_line|#define VDEBUG(dev,fmt,args...) &bslash;&n;&t;do { } while (0)
macro_line|#endif&t;/* VERBOSE */
DECL|macro|ERROR
mdefine_line|#define ERROR(dev,fmt,args...) &bslash;&n;&t;xprintk(dev , KERN_ERR , fmt , ## args)
DECL|macro|WARN
mdefine_line|#define WARN(dev,fmt,args...) &bslash;&n;&t;xprintk(dev , KERN_WARNING , fmt , ## args)
DECL|macro|INFO
mdefine_line|#define INFO(dev,fmt,args...) &bslash;&n;&t;xprintk(dev , KERN_INFO , fmt , ## args)
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|start_out_naking
r_static
r_inline
r_void
id|start_out_naking
(paren
r_struct
id|net2280_ep
op_star
id|ep
)paren
(brace
multiline_comment|/* NOTE:  hardware races lurk here, and PING protocol issues */
id|writel
(paren
(paren
l_int|1
op_lshift
id|SET_NAK_OUT_PACKETS
)paren
comma
op_amp
id|ep-&gt;regs-&gt;ep_rsp
)paren
suffix:semicolon
multiline_comment|/* synch with device */
id|readl
(paren
op_amp
id|ep-&gt;regs-&gt;ep_rsp
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
DECL|function|assert_out_naking
r_static
r_inline
r_void
id|assert_out_naking
(paren
r_struct
id|net2280_ep
op_star
id|ep
comma
r_const
r_char
op_star
id|where
)paren
(brace
id|u32
id|tmp
op_assign
id|readl
(paren
op_amp
id|ep-&gt;regs-&gt;ep_stat
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp
op_amp
(paren
l_int|1
op_lshift
id|NAK_OUT_PACKETS
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|DEBUG
(paren
id|ep-&gt;dev
comma
l_string|&quot;%s %s %08x !NAK&bslash;n&quot;
comma
id|ep-&gt;ep.name
comma
id|where
comma
id|tmp
)paren
suffix:semicolon
id|writel
(paren
(paren
l_int|1
op_lshift
id|SET_NAK_OUT_PACKETS
)paren
comma
op_amp
id|ep-&gt;regs-&gt;ep_rsp
)paren
suffix:semicolon
)brace
)brace
DECL|macro|ASSERT_OUT_NAKING
mdefine_line|#define ASSERT_OUT_NAKING(ep) assert_out_naking(ep,__FUNCTION__)
macro_line|#else
DECL|macro|ASSERT_OUT_NAKING
mdefine_line|#define ASSERT_OUT_NAKING(ep) do {} while (0)
macro_line|#endif
DECL|function|stop_out_naking
r_static
r_inline
r_void
id|stop_out_naking
(paren
r_struct
id|net2280_ep
op_star
id|ep
)paren
(brace
id|u32
id|tmp
suffix:semicolon
id|tmp
op_assign
id|readl
(paren
op_amp
id|ep-&gt;regs-&gt;ep_stat
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp
op_amp
(paren
l_int|1
op_lshift
id|NAK_OUT_PACKETS
)paren
)paren
op_ne
l_int|0
)paren
id|writel
(paren
(paren
l_int|1
op_lshift
id|CLEAR_NAK_OUT_PACKETS
)paren
comma
op_amp
id|ep-&gt;regs-&gt;ep_rsp
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* __KERNEL__ */
eof
