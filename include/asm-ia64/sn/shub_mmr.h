multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001-2004 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SHUB_MMR_H
DECL|macro|_ASM_IA64_SN_SHUB_MMR_H
mdefine_line|#define _ASM_IA64_SN_SHUB_MMR_H
multiline_comment|/* ==================================================================== */
multiline_comment|/*                        Register &quot;SH_IPI_INT&quot;                         */
multiline_comment|/*               SHub Inter-Processor Interrupt Registers               */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_IPI_INT
mdefine_line|#define SH1_IPI_INT                               0x0000000110000380
DECL|macro|SH2_IPI_INT
mdefine_line|#define SH2_IPI_INT                               0x0000000010000380
multiline_comment|/*   SH_IPI_INT_TYPE                                                    */
multiline_comment|/*   Description:  Type of Interrupt: 0=INT, 2=PMI, 4=NMI, 5=INIT       */
DECL|macro|SH_IPI_INT_TYPE_SHFT
mdefine_line|#define SH_IPI_INT_TYPE_SHFT                     0
DECL|macro|SH_IPI_INT_TYPE_MASK
mdefine_line|#define SH_IPI_INT_TYPE_MASK                     0x0000000000000007
multiline_comment|/*   SH_IPI_INT_AGT                                                     */
multiline_comment|/*   Description:  Agent, must be 0 for SHub                            */
DECL|macro|SH_IPI_INT_AGT_SHFT
mdefine_line|#define SH_IPI_INT_AGT_SHFT                      3
DECL|macro|SH_IPI_INT_AGT_MASK
mdefine_line|#define SH_IPI_INT_AGT_MASK                      0x0000000000000008
multiline_comment|/*   SH_IPI_INT_PID                                                     */
multiline_comment|/*   Description:  Processor ID, same setting as on targeted McKinley  */
DECL|macro|SH_IPI_INT_PID_SHFT
mdefine_line|#define SH_IPI_INT_PID_SHFT                      4
DECL|macro|SH_IPI_INT_PID_MASK
mdefine_line|#define SH_IPI_INT_PID_MASK                      0x00000000000ffff0
multiline_comment|/*   SH_IPI_INT_BASE                                                    */
multiline_comment|/*   Description:  Optional interrupt vector area, 2MB aligned          */
DECL|macro|SH_IPI_INT_BASE_SHFT
mdefine_line|#define SH_IPI_INT_BASE_SHFT                     21
DECL|macro|SH_IPI_INT_BASE_MASK
mdefine_line|#define SH_IPI_INT_BASE_MASK                     0x0003ffffffe00000
multiline_comment|/*   SH_IPI_INT_IDX                                                     */
multiline_comment|/*   Description:  Targeted McKinley interrupt vector                   */
DECL|macro|SH_IPI_INT_IDX_SHFT
mdefine_line|#define SH_IPI_INT_IDX_SHFT                      52
DECL|macro|SH_IPI_INT_IDX_MASK
mdefine_line|#define SH_IPI_INT_IDX_MASK                      0x0ff0000000000000
multiline_comment|/*   SH_IPI_INT_SEND                                                    */
multiline_comment|/*   Description:  Send Interrupt Message to PI, This generates a puls  */
DECL|macro|SH_IPI_INT_SEND_SHFT
mdefine_line|#define SH_IPI_INT_SEND_SHFT                     63
DECL|macro|SH_IPI_INT_SEND_MASK
mdefine_line|#define SH_IPI_INT_SEND_MASK                     0x8000000000000000
multiline_comment|/* ==================================================================== */
multiline_comment|/*                     Register &quot;SH_EVENT_OCCURRED&quot;                     */
multiline_comment|/*                    SHub Interrupt Event Occurred                     */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_EVENT_OCCURRED
mdefine_line|#define SH1_EVENT_OCCURRED                        0x0000000110010000
DECL|macro|SH1_EVENT_OCCURRED_ALIAS
mdefine_line|#define SH1_EVENT_OCCURRED_ALIAS                  0x0000000110010008
DECL|macro|SH2_EVENT_OCCURRED
mdefine_line|#define SH2_EVENT_OCCURRED                        0x0000000010010000
DECL|macro|SH2_EVENT_OCCURRED_ALIAS
mdefine_line|#define SH2_EVENT_OCCURRED_ALIAS                  0x0000000010010008
multiline_comment|/* ==================================================================== */
multiline_comment|/*                     Register &quot;SH_PI_CAM_CONTROL&quot;                     */
multiline_comment|/*                      CRB CAM MMR Access Control                      */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_PI_CAM_CONTROL
mdefine_line|#define SH1_PI_CAM_CONTROL                        0x0000000120050300
multiline_comment|/* ==================================================================== */
multiline_comment|/*                        Register &quot;SH_SHUB_ID&quot;                         */
multiline_comment|/*                            SHub ID Number                            */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_SHUB_ID
mdefine_line|#define SH1_SHUB_ID                               0x0000000110060580
DECL|macro|SH1_SHUB_ID_REVISION_SHFT
mdefine_line|#define SH1_SHUB_ID_REVISION_SHFT                 28
DECL|macro|SH1_SHUB_ID_REVISION_MASK
mdefine_line|#define SH1_SHUB_ID_REVISION_MASK                 0x00000000f0000000
multiline_comment|/* ==================================================================== */
multiline_comment|/*                          Register &quot;SH_RTC&quot;                           */
multiline_comment|/*                           Real-time Clock                            */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_RTC
mdefine_line|#define SH1_RTC                                   0x00000001101c0000
DECL|macro|SH2_RTC
mdefine_line|#define SH2_RTC&t;&t;&t;&t;&t;  0x00000002101c0000
DECL|macro|SH_RTC_MASK
mdefine_line|#define SH_RTC_MASK                               0x007fffffffffffff
multiline_comment|/* ==================================================================== */
multiline_comment|/*                   Register &quot;SH_PIO_WRITE_STATUS_0|1&quot;                 */
multiline_comment|/*                      PIO Write Status for CPU 0 &amp; 1                  */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_PIO_WRITE_STATUS_0
mdefine_line|#define SH1_PIO_WRITE_STATUS_0                    0x0000000120070200
DECL|macro|SH1_PIO_WRITE_STATUS_1
mdefine_line|#define SH1_PIO_WRITE_STATUS_1                    0x0000000120070280
DECL|macro|SH2_PIO_WRITE_STATUS_0
mdefine_line|#define SH2_PIO_WRITE_STATUS_0                    0x0000000020070200
DECL|macro|SH2_PIO_WRITE_STATUS_1
mdefine_line|#define SH2_PIO_WRITE_STATUS_1                    0x0000000020070280
DECL|macro|SH2_PIO_WRITE_STATUS_2
mdefine_line|#define SH2_PIO_WRITE_STATUS_2                    0x0000000020070300
DECL|macro|SH2_PIO_WRITE_STATUS_3
mdefine_line|#define SH2_PIO_WRITE_STATUS_3                    0x0000000020070380
multiline_comment|/*   SH_PIO_WRITE_STATUS_0_WRITE_DEADLOCK                               */
multiline_comment|/*   Description:  Deadlock response detected                           */
DECL|macro|SH_PIO_WRITE_STATUS_WRITE_DEADLOCK_SHFT
mdefine_line|#define SH_PIO_WRITE_STATUS_WRITE_DEADLOCK_SHFT 1
DECL|macro|SH_PIO_WRITE_STATUS_WRITE_DEADLOCK_MASK
mdefine_line|#define SH_PIO_WRITE_STATUS_WRITE_DEADLOCK_MASK 0x0000000000000002
multiline_comment|/*   SH_PIO_WRITE_STATUS_0_PENDING_WRITE_COUNT                          */
multiline_comment|/*   Description:  Count of currently pending PIO writes                */
DECL|macro|SH_PIO_WRITE_STATUS_PENDING_WRITE_COUNT_SHFT
mdefine_line|#define SH_PIO_WRITE_STATUS_PENDING_WRITE_COUNT_SHFT 56
DECL|macro|SH_PIO_WRITE_STATUS_PENDING_WRITE_COUNT_MASK
mdefine_line|#define SH_PIO_WRITE_STATUS_PENDING_WRITE_COUNT_MASK 0x3f00000000000000
multiline_comment|/* ==================================================================== */
multiline_comment|/*                Register &quot;SH_PIO_WRITE_STATUS_0_ALIAS&quot;                */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_PIO_WRITE_STATUS_0_ALIAS
mdefine_line|#define SH1_PIO_WRITE_STATUS_0_ALIAS              0x0000000120070208
DECL|macro|SH2_PIO_WRITE_STATUS_0_ALIAS
mdefine_line|#define SH2_PIO_WRITE_STATUS_0_ALIAS              0x0000000020070208
multiline_comment|/* ==================================================================== */
multiline_comment|/*                     Register &quot;SH_EVENT_OCCURRED&quot;                     */
multiline_comment|/*                    SHub Interrupt Event Occurred                     */
multiline_comment|/* ==================================================================== */
multiline_comment|/*   SH_EVENT_OCCURRED_UART_INT                                         */
multiline_comment|/*   Description:  Pending Junk Bus UART Interrupt                      */
DECL|macro|SH_EVENT_OCCURRED_UART_INT_SHFT
mdefine_line|#define SH_EVENT_OCCURRED_UART_INT_SHFT          20
DECL|macro|SH_EVENT_OCCURRED_UART_INT_MASK
mdefine_line|#define SH_EVENT_OCCURRED_UART_INT_MASK          0x0000000000100000
multiline_comment|/*   SH_EVENT_OCCURRED_IPI_INT                                          */
multiline_comment|/*   Description:  Pending IPI Interrupt                                */
DECL|macro|SH_EVENT_OCCURRED_IPI_INT_SHFT
mdefine_line|#define SH_EVENT_OCCURRED_IPI_INT_SHFT           28
DECL|macro|SH_EVENT_OCCURRED_IPI_INT_MASK
mdefine_line|#define SH_EVENT_OCCURRED_IPI_INT_MASK           0x0000000010000000
multiline_comment|/*   SH_EVENT_OCCURRED_II_INT0                                          */
multiline_comment|/*   Description:  Pending II 0 Interrupt                               */
DECL|macro|SH_EVENT_OCCURRED_II_INT0_SHFT
mdefine_line|#define SH_EVENT_OCCURRED_II_INT0_SHFT           29
DECL|macro|SH_EVENT_OCCURRED_II_INT0_MASK
mdefine_line|#define SH_EVENT_OCCURRED_II_INT0_MASK           0x0000000020000000
multiline_comment|/*   SH_EVENT_OCCURRED_II_INT1                                          */
multiline_comment|/*   Description:  Pending II 1 Interrupt                               */
DECL|macro|SH_EVENT_OCCURRED_II_INT1_SHFT
mdefine_line|#define SH_EVENT_OCCURRED_II_INT1_SHFT           30
DECL|macro|SH_EVENT_OCCURRED_II_INT1_MASK
mdefine_line|#define SH_EVENT_OCCURRED_II_INT1_MASK           0x0000000040000000
multiline_comment|/* ==================================================================== */
multiline_comment|/*                         LEDS                                         */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_REAL_JUNK_BUS_LED0
mdefine_line|#define SH1_REAL_JUNK_BUS_LED0&t;&t;&t; 0x7fed00000UL
DECL|macro|SH1_REAL_JUNK_BUS_LED1
mdefine_line|#define SH1_REAL_JUNK_BUS_LED1&t;&t;&t; 0x7fed10000UL
DECL|macro|SH1_REAL_JUNK_BUS_LED2
mdefine_line|#define SH1_REAL_JUNK_BUS_LED2&t;&t;&t; 0x7fed20000UL
DECL|macro|SH1_REAL_JUNK_BUS_LED3
mdefine_line|#define SH1_REAL_JUNK_BUS_LED3&t;&t;&t; 0x7fed30000UL
DECL|macro|SH2_REAL_JUNK_BUS_LED0
mdefine_line|#define SH2_REAL_JUNK_BUS_LED0&t;&t;&t; 0xf0000000UL
DECL|macro|SH2_REAL_JUNK_BUS_LED1
mdefine_line|#define SH2_REAL_JUNK_BUS_LED1&t;&t;&t; 0xf0010000UL
DECL|macro|SH2_REAL_JUNK_BUS_LED2
mdefine_line|#define SH2_REAL_JUNK_BUS_LED2&t;&t;&t; 0xf0020000UL
DECL|macro|SH2_REAL_JUNK_BUS_LED3
mdefine_line|#define SH2_REAL_JUNK_BUS_LED3&t;&t;&t; 0xf0030000UL
multiline_comment|/* ==================================================================== */
multiline_comment|/*                         Register &quot;SH1_PTC_0&quot;                         */
multiline_comment|/*       Puge Translation Cache Message Configuration Information       */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_PTC_0
mdefine_line|#define SH1_PTC_0                                 0x00000001101a0000
multiline_comment|/*   SH1_PTC_0_A                                                        */
multiline_comment|/*   Description:  Type                                                 */
DECL|macro|SH1_PTC_0_A_SHFT
mdefine_line|#define SH1_PTC_0_A_SHFT                          0
multiline_comment|/*   SH1_PTC_0_PS                                                       */
multiline_comment|/*   Description:  Page Size                                            */
DECL|macro|SH1_PTC_0_PS_SHFT
mdefine_line|#define SH1_PTC_0_PS_SHFT                         2
multiline_comment|/*   SH1_PTC_0_RID                                                      */
multiline_comment|/*   Description:  Region ID                                            */
DECL|macro|SH1_PTC_0_RID_SHFT
mdefine_line|#define SH1_PTC_0_RID_SHFT                        8
multiline_comment|/*   SH1_PTC_0_START                                                    */
multiline_comment|/*   Description:  Start                                                */
DECL|macro|SH1_PTC_0_START_SHFT
mdefine_line|#define SH1_PTC_0_START_SHFT                      63
multiline_comment|/* ==================================================================== */
multiline_comment|/*                         Register &quot;SH1_PTC_1&quot;                         */
multiline_comment|/*       Puge Translation Cache Message Configuration Information       */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_PTC_1
mdefine_line|#define SH1_PTC_1                                 0x00000001101a0080
multiline_comment|/*   SH1_PTC_1_START                                                    */
multiline_comment|/*   Description:  PTC_1 Start                                          */
DECL|macro|SH1_PTC_1_START_SHFT
mdefine_line|#define SH1_PTC_1_START_SHFT                      63
multiline_comment|/* ==================================================================== */
multiline_comment|/*                         Register &quot;SH2_PTC&quot;                           */
multiline_comment|/*       Puge Translation Cache Message Configuration Information       */
multiline_comment|/* ==================================================================== */
DECL|macro|SH2_PTC
mdefine_line|#define SH2_PTC                                   0x0000000170000000
multiline_comment|/*   SH2_PTC_A                                                          */
multiline_comment|/*   Description:  Type                                                 */
DECL|macro|SH2_PTC_A_SHFT
mdefine_line|#define SH2_PTC_A_SHFT                            0
multiline_comment|/*   SH2_PTC_PS                                                         */
multiline_comment|/*   Description:  Page Size                                            */
DECL|macro|SH2_PTC_PS_SHFT
mdefine_line|#define SH2_PTC_PS_SHFT                           2
multiline_comment|/*   SH2_PTC_RID                                                      */
multiline_comment|/*   Description:  Region ID                                            */
DECL|macro|SH2_PTC_RID_SHFT
mdefine_line|#define SH2_PTC_RID_SHFT                          4
multiline_comment|/*   SH2_PTC_START                                                      */
multiline_comment|/*   Description:  Start                                                */
DECL|macro|SH2_PTC_START_SHFT
mdefine_line|#define SH2_PTC_START_SHFT                        63
multiline_comment|/*   SH2_PTC_ADDR_RID                                                   */
multiline_comment|/*   Description:  Region ID                                            */
DECL|macro|SH2_PTC_ADDR_SHFT
mdefine_line|#define SH2_PTC_ADDR_SHFT                         4
DECL|macro|SH2_PTC_ADDR_MASK
mdefine_line|#define SH2_PTC_ADDR_MASK                         0x1ffffffffffff000
multiline_comment|/* ==================================================================== */
multiline_comment|/*                    Register &quot;SH_RTC1_INT_CONFIG&quot;                     */
multiline_comment|/*                SHub RTC 1 Interrupt Config Registers                 */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_RTC1_INT_CONFIG
mdefine_line|#define SH1_RTC1_INT_CONFIG                      0x0000000110001480
DECL|macro|SH2_RTC1_INT_CONFIG
mdefine_line|#define SH2_RTC1_INT_CONFIG                      0x0000000010001480
DECL|macro|SH_RTC1_INT_CONFIG_MASK
mdefine_line|#define SH_RTC1_INT_CONFIG_MASK                  0x0ff3ffffffefffff
DECL|macro|SH_RTC1_INT_CONFIG_INIT
mdefine_line|#define SH_RTC1_INT_CONFIG_INIT                  0x0000000000000000
multiline_comment|/*   SH_RTC1_INT_CONFIG_TYPE                                            */
multiline_comment|/*   Description:  Type of Interrupt: 0=INT, 2=PMI, 4=NMI, 5=INIT       */
DECL|macro|SH_RTC1_INT_CONFIG_TYPE_SHFT
mdefine_line|#define SH_RTC1_INT_CONFIG_TYPE_SHFT             0
DECL|macro|SH_RTC1_INT_CONFIG_TYPE_MASK
mdefine_line|#define SH_RTC1_INT_CONFIG_TYPE_MASK             0x0000000000000007
multiline_comment|/*   SH_RTC1_INT_CONFIG_AGT                                             */
multiline_comment|/*   Description:  Agent, must be 0 for SHub                            */
DECL|macro|SH_RTC1_INT_CONFIG_AGT_SHFT
mdefine_line|#define SH_RTC1_INT_CONFIG_AGT_SHFT              3
DECL|macro|SH_RTC1_INT_CONFIG_AGT_MASK
mdefine_line|#define SH_RTC1_INT_CONFIG_AGT_MASK              0x0000000000000008
multiline_comment|/*   SH_RTC1_INT_CONFIG_PID                                             */
multiline_comment|/*   Description:  Processor ID, same setting as on targeted McKinley  */
DECL|macro|SH_RTC1_INT_CONFIG_PID_SHFT
mdefine_line|#define SH_RTC1_INT_CONFIG_PID_SHFT              4
DECL|macro|SH_RTC1_INT_CONFIG_PID_MASK
mdefine_line|#define SH_RTC1_INT_CONFIG_PID_MASK              0x00000000000ffff0
multiline_comment|/*   SH_RTC1_INT_CONFIG_BASE                                            */
multiline_comment|/*   Description:  Optional interrupt vector area, 2MB aligned          */
DECL|macro|SH_RTC1_INT_CONFIG_BASE_SHFT
mdefine_line|#define SH_RTC1_INT_CONFIG_BASE_SHFT             21
DECL|macro|SH_RTC1_INT_CONFIG_BASE_MASK
mdefine_line|#define SH_RTC1_INT_CONFIG_BASE_MASK             0x0003ffffffe00000
multiline_comment|/*   SH_RTC1_INT_CONFIG_IDX                                             */
multiline_comment|/*   Description:  Targeted McKinley interrupt vector                   */
DECL|macro|SH_RTC1_INT_CONFIG_IDX_SHFT
mdefine_line|#define SH_RTC1_INT_CONFIG_IDX_SHFT              52
DECL|macro|SH_RTC1_INT_CONFIG_IDX_MASK
mdefine_line|#define SH_RTC1_INT_CONFIG_IDX_MASK              0x0ff0000000000000
multiline_comment|/* ==================================================================== */
multiline_comment|/*                    Register &quot;SH_RTC1_INT_ENABLE&quot;                     */
multiline_comment|/*                SHub RTC 1 Interrupt Enable Registers                 */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_RTC1_INT_ENABLE
mdefine_line|#define SH1_RTC1_INT_ENABLE                      0x0000000110001500
DECL|macro|SH2_RTC1_INT_ENABLE
mdefine_line|#define SH2_RTC1_INT_ENABLE                      0x0000000010001500
DECL|macro|SH_RTC1_INT_ENABLE_MASK
mdefine_line|#define SH_RTC1_INT_ENABLE_MASK                  0x0000000000000001
DECL|macro|SH_RTC1_INT_ENABLE_INIT
mdefine_line|#define SH_RTC1_INT_ENABLE_INIT                  0x0000000000000000
multiline_comment|/*   SH_RTC1_INT_ENABLE_RTC1_ENABLE                                     */
multiline_comment|/*   Description:  Enable RTC 1 Interrupt                               */
DECL|macro|SH_RTC1_INT_ENABLE_RTC1_ENABLE_SHFT
mdefine_line|#define SH_RTC1_INT_ENABLE_RTC1_ENABLE_SHFT      0
DECL|macro|SH_RTC1_INT_ENABLE_RTC1_ENABLE_MASK
mdefine_line|#define SH_RTC1_INT_ENABLE_RTC1_ENABLE_MASK      0x0000000000000001
multiline_comment|/* ==================================================================== */
multiline_comment|/*                    Register &quot;SH_RTC2_INT_CONFIG&quot;                     */
multiline_comment|/*                SHub RTC 2 Interrupt Config Registers                 */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_RTC2_INT_CONFIG
mdefine_line|#define SH1_RTC2_INT_CONFIG                      0x0000000110001580
DECL|macro|SH2_RTC2_INT_CONFIG
mdefine_line|#define SH2_RTC2_INT_CONFIG                      0x0000000010001580
DECL|macro|SH_RTC2_INT_CONFIG_MASK
mdefine_line|#define SH_RTC2_INT_CONFIG_MASK                  0x0ff3ffffffefffff
DECL|macro|SH_RTC2_INT_CONFIG_INIT
mdefine_line|#define SH_RTC2_INT_CONFIG_INIT                  0x0000000000000000
multiline_comment|/*   SH_RTC2_INT_CONFIG_TYPE                                            */
multiline_comment|/*   Description:  Type of Interrupt: 0=INT, 2=PMI, 4=NMI, 5=INIT       */
DECL|macro|SH_RTC2_INT_CONFIG_TYPE_SHFT
mdefine_line|#define SH_RTC2_INT_CONFIG_TYPE_SHFT             0
DECL|macro|SH_RTC2_INT_CONFIG_TYPE_MASK
mdefine_line|#define SH_RTC2_INT_CONFIG_TYPE_MASK             0x0000000000000007
multiline_comment|/*   SH_RTC2_INT_CONFIG_AGT                                             */
multiline_comment|/*   Description:  Agent, must be 0 for SHub                            */
DECL|macro|SH_RTC2_INT_CONFIG_AGT_SHFT
mdefine_line|#define SH_RTC2_INT_CONFIG_AGT_SHFT              3
DECL|macro|SH_RTC2_INT_CONFIG_AGT_MASK
mdefine_line|#define SH_RTC2_INT_CONFIG_AGT_MASK              0x0000000000000008
multiline_comment|/*   SH_RTC2_INT_CONFIG_PID                                             */
multiline_comment|/*   Description:  Processor ID, same setting as on targeted McKinley  */
DECL|macro|SH_RTC2_INT_CONFIG_PID_SHFT
mdefine_line|#define SH_RTC2_INT_CONFIG_PID_SHFT              4
DECL|macro|SH_RTC2_INT_CONFIG_PID_MASK
mdefine_line|#define SH_RTC2_INT_CONFIG_PID_MASK              0x00000000000ffff0
multiline_comment|/*   SH_RTC2_INT_CONFIG_BASE                                            */
multiline_comment|/*   Description:  Optional interrupt vector area, 2MB aligned          */
DECL|macro|SH_RTC2_INT_CONFIG_BASE_SHFT
mdefine_line|#define SH_RTC2_INT_CONFIG_BASE_SHFT             21
DECL|macro|SH_RTC2_INT_CONFIG_BASE_MASK
mdefine_line|#define SH_RTC2_INT_CONFIG_BASE_MASK             0x0003ffffffe00000
multiline_comment|/*   SH_RTC2_INT_CONFIG_IDX                                             */
multiline_comment|/*   Description:  Targeted McKinley interrupt vector                   */
DECL|macro|SH_RTC2_INT_CONFIG_IDX_SHFT
mdefine_line|#define SH_RTC2_INT_CONFIG_IDX_SHFT              52
DECL|macro|SH_RTC2_INT_CONFIG_IDX_MASK
mdefine_line|#define SH_RTC2_INT_CONFIG_IDX_MASK              0x0ff0000000000000
multiline_comment|/* ==================================================================== */
multiline_comment|/*                    Register &quot;SH_RTC2_INT_ENABLE&quot;                     */
multiline_comment|/*                SHub RTC 2 Interrupt Enable Registers                 */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_RTC2_INT_ENABLE
mdefine_line|#define SH1_RTC2_INT_ENABLE                      0x0000000110001600
DECL|macro|SH2_RTC2_INT_ENABLE
mdefine_line|#define SH2_RTC2_INT_ENABLE                      0x0000000010001600
DECL|macro|SH_RTC2_INT_ENABLE_MASK
mdefine_line|#define SH_RTC2_INT_ENABLE_MASK                  0x0000000000000001
DECL|macro|SH_RTC2_INT_ENABLE_INIT
mdefine_line|#define SH_RTC2_INT_ENABLE_INIT                  0x0000000000000000
multiline_comment|/*   SH_RTC2_INT_ENABLE_RTC2_ENABLE                                     */
multiline_comment|/*   Description:  Enable RTC 2 Interrupt                               */
DECL|macro|SH_RTC2_INT_ENABLE_RTC2_ENABLE_SHFT
mdefine_line|#define SH_RTC2_INT_ENABLE_RTC2_ENABLE_SHFT      0
DECL|macro|SH_RTC2_INT_ENABLE_RTC2_ENABLE_MASK
mdefine_line|#define SH_RTC2_INT_ENABLE_RTC2_ENABLE_MASK      0x0000000000000001
multiline_comment|/* ==================================================================== */
multiline_comment|/*                    Register &quot;SH_RTC3_INT_CONFIG&quot;                     */
multiline_comment|/*                SHub RTC 3 Interrupt Config Registers                 */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_RTC3_INT_CONFIG
mdefine_line|#define SH1_RTC3_INT_CONFIG                      0x0000000110001680
DECL|macro|SH2_RTC3_INT_CONFIG
mdefine_line|#define SH2_RTC3_INT_CONFIG                      0x0000000010001680
DECL|macro|SH_RTC3_INT_CONFIG_MASK
mdefine_line|#define SH_RTC3_INT_CONFIG_MASK                  0x0ff3ffffffefffff
DECL|macro|SH_RTC3_INT_CONFIG_INIT
mdefine_line|#define SH_RTC3_INT_CONFIG_INIT                  0x0000000000000000
multiline_comment|/*   SH_RTC3_INT_CONFIG_TYPE                                            */
multiline_comment|/*   Description:  Type of Interrupt: 0=INT, 2=PMI, 4=NMI, 5=INIT       */
DECL|macro|SH_RTC3_INT_CONFIG_TYPE_SHFT
mdefine_line|#define SH_RTC3_INT_CONFIG_TYPE_SHFT             0
DECL|macro|SH_RTC3_INT_CONFIG_TYPE_MASK
mdefine_line|#define SH_RTC3_INT_CONFIG_TYPE_MASK             0x0000000000000007
multiline_comment|/*   SH_RTC3_INT_CONFIG_AGT                                             */
multiline_comment|/*   Description:  Agent, must be 0 for SHub                            */
DECL|macro|SH_RTC3_INT_CONFIG_AGT_SHFT
mdefine_line|#define SH_RTC3_INT_CONFIG_AGT_SHFT              3
DECL|macro|SH_RTC3_INT_CONFIG_AGT_MASK
mdefine_line|#define SH_RTC3_INT_CONFIG_AGT_MASK              0x0000000000000008
multiline_comment|/*   SH_RTC3_INT_CONFIG_PID                                             */
multiline_comment|/*   Description:  Processor ID, same setting as on targeted McKinley  */
DECL|macro|SH_RTC3_INT_CONFIG_PID_SHFT
mdefine_line|#define SH_RTC3_INT_CONFIG_PID_SHFT              4
DECL|macro|SH_RTC3_INT_CONFIG_PID_MASK
mdefine_line|#define SH_RTC3_INT_CONFIG_PID_MASK              0x00000000000ffff0
multiline_comment|/*   SH_RTC3_INT_CONFIG_BASE                                            */
multiline_comment|/*   Description:  Optional interrupt vector area, 2MB aligned          */
DECL|macro|SH_RTC3_INT_CONFIG_BASE_SHFT
mdefine_line|#define SH_RTC3_INT_CONFIG_BASE_SHFT             21
DECL|macro|SH_RTC3_INT_CONFIG_BASE_MASK
mdefine_line|#define SH_RTC3_INT_CONFIG_BASE_MASK             0x0003ffffffe00000
multiline_comment|/*   SH_RTC3_INT_CONFIG_IDX                                             */
multiline_comment|/*   Description:  Targeted McKinley interrupt vector                   */
DECL|macro|SH_RTC3_INT_CONFIG_IDX_SHFT
mdefine_line|#define SH_RTC3_INT_CONFIG_IDX_SHFT              52
DECL|macro|SH_RTC3_INT_CONFIG_IDX_MASK
mdefine_line|#define SH_RTC3_INT_CONFIG_IDX_MASK              0x0ff0000000000000
multiline_comment|/* ==================================================================== */
multiline_comment|/*                    Register &quot;SH_RTC3_INT_ENABLE&quot;                     */
multiline_comment|/*                SHub RTC 3 Interrupt Enable Registers                 */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_RTC3_INT_ENABLE
mdefine_line|#define SH1_RTC3_INT_ENABLE                      0x0000000110001700
DECL|macro|SH2_RTC3_INT_ENABLE
mdefine_line|#define SH2_RTC3_INT_ENABLE                      0x0000000010001700
DECL|macro|SH_RTC3_INT_ENABLE_MASK
mdefine_line|#define SH_RTC3_INT_ENABLE_MASK                  0x0000000000000001
DECL|macro|SH_RTC3_INT_ENABLE_INIT
mdefine_line|#define SH_RTC3_INT_ENABLE_INIT                  0x0000000000000000
multiline_comment|/*   SH_RTC3_INT_ENABLE_RTC3_ENABLE                                     */
multiline_comment|/*   Description:  Enable RTC 3 Interrupt                               */
DECL|macro|SH_RTC3_INT_ENABLE_RTC3_ENABLE_SHFT
mdefine_line|#define SH_RTC3_INT_ENABLE_RTC3_ENABLE_SHFT      0
DECL|macro|SH_RTC3_INT_ENABLE_RTC3_ENABLE_MASK
mdefine_line|#define SH_RTC3_INT_ENABLE_RTC3_ENABLE_MASK      0x0000000000000001
multiline_comment|/*   SH_EVENT_OCCURRED_RTC1_INT                                         */
multiline_comment|/*   Description:  Pending RTC 1 Interrupt                              */
DECL|macro|SH_EVENT_OCCURRED_RTC1_INT_SHFT
mdefine_line|#define SH_EVENT_OCCURRED_RTC1_INT_SHFT          24
DECL|macro|SH_EVENT_OCCURRED_RTC1_INT_MASK
mdefine_line|#define SH_EVENT_OCCURRED_RTC1_INT_MASK          0x0000000001000000
multiline_comment|/*   SH_EVENT_OCCURRED_RTC2_INT                                         */
multiline_comment|/*   Description:  Pending RTC 2 Interrupt                              */
DECL|macro|SH_EVENT_OCCURRED_RTC2_INT_SHFT
mdefine_line|#define SH_EVENT_OCCURRED_RTC2_INT_SHFT          25
DECL|macro|SH_EVENT_OCCURRED_RTC2_INT_MASK
mdefine_line|#define SH_EVENT_OCCURRED_RTC2_INT_MASK          0x0000000002000000
multiline_comment|/*   SH_EVENT_OCCURRED_RTC3_INT                                         */
multiline_comment|/*   Description:  Pending RTC 3 Interrupt                              */
DECL|macro|SH_EVENT_OCCURRED_RTC3_INT_SHFT
mdefine_line|#define SH_EVENT_OCCURRED_RTC3_INT_SHFT          26
DECL|macro|SH_EVENT_OCCURRED_RTC3_INT_MASK
mdefine_line|#define SH_EVENT_OCCURRED_RTC3_INT_MASK          0x0000000004000000
multiline_comment|/* ==================================================================== */
multiline_comment|/*                        Register &quot;SH_INT_CMPB&quot;                        */
multiline_comment|/*                  RTC Compare Value for Processor B                   */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_INT_CMPB
mdefine_line|#define SH1_INT_CMPB                             0x00000001101b0080
DECL|macro|SH2_INT_CMPB
mdefine_line|#define SH2_INT_CMPB                             0x00000000101b0080
DECL|macro|SH_INT_CMPB_MASK
mdefine_line|#define SH_INT_CMPB_MASK                         0x007fffffffffffff
DECL|macro|SH_INT_CMPB_INIT
mdefine_line|#define SH_INT_CMPB_INIT                         0x0000000000000000
multiline_comment|/*   SH_INT_CMPB_REAL_TIME_CMPB                                         */
multiline_comment|/*   Description:  Real Time Clock Compare                              */
DECL|macro|SH_INT_CMPB_REAL_TIME_CMPB_SHFT
mdefine_line|#define SH_INT_CMPB_REAL_TIME_CMPB_SHFT          0
DECL|macro|SH_INT_CMPB_REAL_TIME_CMPB_MASK
mdefine_line|#define SH_INT_CMPB_REAL_TIME_CMPB_MASK          0x007fffffffffffff
multiline_comment|/* ==================================================================== */
multiline_comment|/*                        Register &quot;SH_INT_CMPC&quot;                        */
multiline_comment|/*                  RTC Compare Value for Processor C                   */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_INT_CMPC
mdefine_line|#define SH1_INT_CMPC                             0x00000001101b0100
DECL|macro|SH2_INT_CMPC
mdefine_line|#define SH2_INT_CMPC                             0x00000000101b0100
DECL|macro|SH_INT_CMPC_MASK
mdefine_line|#define SH_INT_CMPC_MASK                         0x007fffffffffffff
DECL|macro|SH_INT_CMPC_INIT
mdefine_line|#define SH_INT_CMPC_INIT                         0x0000000000000000
multiline_comment|/*   SH_INT_CMPC_REAL_TIME_CMPC                                         */
multiline_comment|/*   Description:  Real Time Clock Compare                              */
DECL|macro|SH_INT_CMPC_REAL_TIME_CMPC_SHFT
mdefine_line|#define SH_INT_CMPC_REAL_TIME_CMPC_SHFT          0
DECL|macro|SH_INT_CMPC_REAL_TIME_CMPC_MASK
mdefine_line|#define SH_INT_CMPC_REAL_TIME_CMPC_MASK          0x007fffffffffffff
multiline_comment|/* ==================================================================== */
multiline_comment|/*                        Register &quot;SH_INT_CMPD&quot;                        */
multiline_comment|/*                  RTC Compare Value for Processor D                   */
multiline_comment|/* ==================================================================== */
DECL|macro|SH1_INT_CMPD
mdefine_line|#define SH1_INT_CMPD                             0x00000001101b0180
DECL|macro|SH2_INT_CMPD
mdefine_line|#define SH2_INT_CMPD                             0x00000000101b0180
DECL|macro|SH_INT_CMPD_MASK
mdefine_line|#define SH_INT_CMPD_MASK                         0x007fffffffffffff
DECL|macro|SH_INT_CMPD_INIT
mdefine_line|#define SH_INT_CMPD_INIT                         0x0000000000000000
multiline_comment|/*   SH_INT_CMPD_REAL_TIME_CMPD                                         */
multiline_comment|/*   Description:  Real Time Clock Compare                              */
DECL|macro|SH_INT_CMPD_REAL_TIME_CMPD_SHFT
mdefine_line|#define SH_INT_CMPD_REAL_TIME_CMPD_SHFT          0
DECL|macro|SH_INT_CMPD_REAL_TIME_CMPD_MASK
mdefine_line|#define SH_INT_CMPD_REAL_TIME_CMPD_MASK          0x007fffffffffffff
multiline_comment|/* ==================================================================== */
multiline_comment|/* Some MMRs are functionally identical (or close enough) on both SHUB1 */
multiline_comment|/* and SHUB2 that it makes sense to define a geberic name for the MMR.  */
multiline_comment|/* It is acceptible to use (for example) SH_IPI_INT to reference the    */
multiline_comment|/* the IPI MMR. The value of SH_IPI_INT is determined at runtime based  */
multiline_comment|/* on the type of the SHUB. Do not use these #defines in performance    */
multiline_comment|/* critical code  or loops - there is a small performance penalty.      */
multiline_comment|/* ==================================================================== */
DECL|macro|shubmmr
mdefine_line|#define shubmmr(a,b) &t;&t;(is_shub2() ? a##2_##b : a##1_##b)
DECL|macro|SH_REAL_JUNK_BUS_LED0
mdefine_line|#define SH_REAL_JUNK_BUS_LED0&t;shubmmr(SH, REAL_JUNK_BUS_LED0)
DECL|macro|SH_IPI_INT
mdefine_line|#define SH_IPI_INT&t;&t;shubmmr(SH, IPI_INT)
DECL|macro|SH_EVENT_OCCURRED
mdefine_line|#define SH_EVENT_OCCURRED&t;shubmmr(SH, EVENT_OCCURRED)
DECL|macro|SH_EVENT_OCCURRED_ALIAS
mdefine_line|#define SH_EVENT_OCCURRED_ALIAS&t;shubmmr(SH, EVENT_OCCURRED_ALIAS)
DECL|macro|SH_RTC
mdefine_line|#define SH_RTC&t;&t;&t;shubmmr(SH, RTC)
DECL|macro|SH_RTC1_INT_CONFIG
mdefine_line|#define SH_RTC1_INT_CONFIG&t;shubmmr(SH, RTC1_INT_CONFIG)
DECL|macro|SH_RTC1_INT_ENABLE
mdefine_line|#define SH_RTC1_INT_ENABLE&t;shubmmr(SH, RTC1_INT_ENABLE)
DECL|macro|SH_RTC2_INT_CONFIG
mdefine_line|#define SH_RTC2_INT_CONFIG&t;shubmmr(SH, RTC2_INT_CONFIG)
DECL|macro|SH_RTC2_INT_ENABLE
mdefine_line|#define SH_RTC2_INT_ENABLE&t;shubmmr(SH, RTC2_INT_ENABLE)
DECL|macro|SH_RTC3_INT_CONFIG
mdefine_line|#define SH_RTC3_INT_CONFIG&t;shubmmr(SH, RTC3_INT_CONFIG)
DECL|macro|SH_RTC3_INT_ENABLE
mdefine_line|#define SH_RTC3_INT_ENABLE&t;shubmmr(SH, RTC3_INT_ENABLE)
DECL|macro|SH_INT_CMPB
mdefine_line|#define SH_INT_CMPB&t;&t;shubmmr(SH, INT_CMPB)
DECL|macro|SH_INT_CMPC
mdefine_line|#define SH_INT_CMPC&t;&t;shubmmr(SH, INT_CMPC)
DECL|macro|SH_INT_CMPD
mdefine_line|#define SH_INT_CMPD&t;&t;shubmmr(SH, INT_CMPD)
macro_line|#endif /* _ASM_IA64_SN_SHUB_MMR_H */
eof
