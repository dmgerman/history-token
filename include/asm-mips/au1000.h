multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Include file for Alchemy Semiconductor&squot;s Au1000 CPU.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _AU1000_H_
DECL|macro|_AU1000_H_
mdefine_line|#define _AU1000_H_
multiline_comment|/* SDRAM Controller */
DECL|macro|CS_MODE_0
mdefine_line|#define CS_MODE_0                0x14000000
DECL|macro|CS_MODE_1
mdefine_line|#define CS_MODE_1                0x14000004
DECL|macro|CS_MODE_2
mdefine_line|#define CS_MODE_2                0x14000008
DECL|macro|CS_CONFIG_0
mdefine_line|#define CS_CONFIG_0              0x1400000C
DECL|macro|CS_CONFIG_1
mdefine_line|#define CS_CONFIG_1              0x14000010
DECL|macro|CS_CONFIG_2
mdefine_line|#define CS_CONFIG_2              0x14000014
DECL|macro|REFRESH_CONFIG
mdefine_line|#define REFRESH_CONFIG           0x14000018
DECL|macro|PRECHARGE_CMD
mdefine_line|#define PRECHARGE_CMD            0x1400001C
DECL|macro|AUTO_REFRESH_CMD
mdefine_line|#define AUTO_REFRESH_CMD         0x14000020
DECL|macro|WRITE_EXTERN_0
mdefine_line|#define WRITE_EXTERN_0           0x14000024
DECL|macro|WRITE_EXTERN_1
mdefine_line|#define WRITE_EXTERN_1           0x14000028
DECL|macro|WRITE_EXTERN_2
mdefine_line|#define WRITE_EXTERN_2           0x1400002C
DECL|macro|SDRAM_SLEEP
mdefine_line|#define SDRAM_SLEEP              0x14000030
DECL|macro|TOGGLE_CKE
mdefine_line|#define TOGGLE_CKE               0x14000034
multiline_comment|/* Static Bus Controller */
DECL|macro|STATIC_CONFIG_0
mdefine_line|#define STATIC_CONFIG_0          0x14001000
DECL|macro|STATIC_TIMING_0
mdefine_line|#define STATIC_TIMING_0          0x14001004
DECL|macro|STATIC_ADDRESS_0
mdefine_line|#define STATIC_ADDRESS_0         0x14001008
DECL|macro|STATIC_CONFIG_1
mdefine_line|#define STATIC_CONFIG_1          0x14001010
DECL|macro|STATIC_TIMING_1
mdefine_line|#define STATIC_TIMING_1          0x14001014
DECL|macro|STATIC_ADDRESS_1
mdefine_line|#define STATIC_ADDRESS_1         0x14001018
DECL|macro|STATIC_CONFIG_2
mdefine_line|#define STATIC_CONFIG_2          0x14001020
DECL|macro|STATIC_TIMING_2
mdefine_line|#define STATIC_TIMING_2          0x14001024
DECL|macro|STATIC_ADDRESS_2
mdefine_line|#define STATIC_ADDRESS_2         0x14001028
DECL|macro|STATIC_CONFIG_3
mdefine_line|#define STATIC_CONFIG_3          0x14001030
DECL|macro|STATIC_TIMING_3
mdefine_line|#define STATIC_TIMING_3          0x14001034
DECL|macro|STATIC_ADDRESS_3
mdefine_line|#define STATIC_ADDRESS_3         0x14001038
multiline_comment|/* DMA Controller 0 */
DECL|macro|DMA0_MODE_SET
mdefine_line|#define DMA0_MODE_SET            0x14002000
DECL|macro|DMA0_MODE_CLEAR
mdefine_line|#define DMA0_MODE_CLEAR          0x14002004
DECL|macro|DMA0_PERIPHERAL_ADDR
mdefine_line|#define DMA0_PERIPHERAL_ADDR     0x14002008
DECL|macro|DMA0_BUFFER0_START
mdefine_line|#define DMA0_BUFFER0_START       0x1400200C
DECL|macro|DMA0_BUFFER0_COUNT
mdefine_line|#define DMA0_BUFFER0_COUNT       0x14002010
DECL|macro|DMA0_BUFFER1_START
mdefine_line|#define DMA0_BUFFER1_START       0x14002014
DECL|macro|DMA0_BUFFER1_COUNT
mdefine_line|#define DMA0_BUFFER1_COUNT       0x14002018
multiline_comment|/* DMA Controller 1 */
DECL|macro|DMA1_MODE_SET
mdefine_line|#define DMA1_MODE_SET            0x14002100
DECL|macro|DMA1_MODE_CLEAR
mdefine_line|#define DMA1_MODE_CLEAR          0x14002104
DECL|macro|DMA1_PERIPHERAL_ADDR
mdefine_line|#define DMA1_PERIPHERAL_ADDR     0x14002108
DECL|macro|DMA1_BUFFER0_START
mdefine_line|#define DMA1_BUFFER0_START       0x1400210C
DECL|macro|DMA1_BUFFER0_COUNT
mdefine_line|#define DMA1_BUFFER0_COUNT       0x14002110
DECL|macro|DMA1_BUFFER1_START
mdefine_line|#define DMA1_BUFFER1_START       0x14002114
DECL|macro|DMA1_BUFFER1_COUNT
mdefine_line|#define DMA1_BUFFER1_COUNT       0x14002118
multiline_comment|/* DMA Controller 2 */
DECL|macro|DMA2_MODE_SET
mdefine_line|#define DMA2_MODE_SET            0x14002200
DECL|macro|DMA2_MODE_CLEAR
mdefine_line|#define DMA2_MODE_CLEAR          0x14002204
DECL|macro|DMA2_PERIPHERAL_ADDR
mdefine_line|#define DMA2_PERIPHERAL_ADDR     0x14002208
DECL|macro|DMA2_BUFFER0_START
mdefine_line|#define DMA2_BUFFER0_START       0x1400220C
DECL|macro|DMA2_BUFFER0_COUNT
mdefine_line|#define DMA2_BUFFER0_COUNT       0x14002210
DECL|macro|DMA2_BUFFER1_START
mdefine_line|#define DMA2_BUFFER1_START       0x14002214
DECL|macro|DMA2_BUFFER1_COUNT
mdefine_line|#define DMA2_BUFFER1_COUNT       0x14002218
multiline_comment|/* DMA Controller 3 */
DECL|macro|DMA3_MODE_SET
mdefine_line|#define DMA3_MODE_SET            0x14002300
DECL|macro|DMA3_MODE_CLEAR
mdefine_line|#define DMA3_MODE_CLEAR          0x14002304
DECL|macro|DMA3_PERIPHERAL_ADDR
mdefine_line|#define DMA3_PERIPHERAL_ADDR     0x14002308
DECL|macro|DMA3_BUFFER0_START
mdefine_line|#define DMA3_BUFFER0_START       0x1400230C
DECL|macro|DMA3_BUFFER0_COUNT
mdefine_line|#define DMA3_BUFFER0_COUNT       0x14002310
DECL|macro|DMA3_BUFFER1_START
mdefine_line|#define DMA3_BUFFER1_START       0x14002314
DECL|macro|DMA3_BUFFER1_COUNT
mdefine_line|#define DMA3_BUFFER1_COUNT       0x14002318
multiline_comment|/* DMA Controller 4 */
DECL|macro|DMA4_MODE_SET
mdefine_line|#define DMA4_MODE_SET            0x14002400
DECL|macro|DMA4_MODE_CLEAR
mdefine_line|#define DMA4_MODE_CLEAR          0x14002404
DECL|macro|DMA4_PERIPHERAL_ADDR
mdefine_line|#define DMA4_PERIPHERAL_ADDR     0x14002408
DECL|macro|DMA4_BUFFER0_START
mdefine_line|#define DMA4_BUFFER0_START       0x1400240C
DECL|macro|DMA4_BUFFER0_COUNT
mdefine_line|#define DMA4_BUFFER0_COUNT       0x14002410
DECL|macro|DMA4_BUFFER1_START
mdefine_line|#define DMA4_BUFFER1_START       0x14002414
DECL|macro|DMA4_BUFFER1_COUNT
mdefine_line|#define DMA4_BUFFER1_COUNT       0x14002418
multiline_comment|/* DMA Controller 5 */
DECL|macro|DMA5_MODE_SET
mdefine_line|#define DMA5_MODE_SET            0x14002500
DECL|macro|DMA5_MODE_CLEAR
mdefine_line|#define DMA5_MODE_CLEAR          0x14002504
DECL|macro|DMA5_PERIPHERAL_ADDR
mdefine_line|#define DMA5_PERIPHERAL_ADDR     0x14002508
DECL|macro|DMA5_BUFFER0_START
mdefine_line|#define DMA5_BUFFER0_START       0x1400250C
DECL|macro|DMA5_BUFFER0_COUNT
mdefine_line|#define DMA5_BUFFER0_COUNT       0x14002510
DECL|macro|DMA5_BUFFER1_START
mdefine_line|#define DMA5_BUFFER1_START       0x14002514
DECL|macro|DMA5_BUFFER1_COUNT
mdefine_line|#define DMA5_BUFFER1_COUNT       0x14002518
multiline_comment|/* DMA Controller 6 */
DECL|macro|DMA6_MODE_SET
mdefine_line|#define DMA6_MODE_SET            0x14002600
DECL|macro|DMA6_MODE_CLEAR
mdefine_line|#define DMA6_MODE_CLEAR          0x14002604
DECL|macro|DMA6_PERIPHERAL_ADDR
mdefine_line|#define DMA6_PERIPHERAL_ADDR     0x14002608
DECL|macro|DMA6_BUFFER0_START
mdefine_line|#define DMA6_BUFFER0_START       0x1400260C
DECL|macro|DMA6_BUFFER0_COUNT
mdefine_line|#define DMA6_BUFFER0_COUNT       0x14002610
DECL|macro|DMA6_BUFFER1_START
mdefine_line|#define DMA6_BUFFER1_START       0x14002614
DECL|macro|DMA6_BUFFER1_COUNT
mdefine_line|#define DMA6_BUFFER1_COUNT       0x14002618
multiline_comment|/* DMA Controller 7 */
DECL|macro|DMA7_MODE_SET
mdefine_line|#define DMA7_MODE_SET            0x14002700
DECL|macro|DMA7_MODE_CLEAR
mdefine_line|#define DMA7_MODE_CLEAR          0x14002704
DECL|macro|DMA7_PERIPHERAL_ADDR
mdefine_line|#define DMA7_PERIPHERAL_ADDR     0x14002708
DECL|macro|DMA7_BUFFER0_START
mdefine_line|#define DMA7_BUFFER0_START       0x1400270C
DECL|macro|DMA7_BUFFER0_COUNT
mdefine_line|#define DMA7_BUFFER0_COUNT       0x14002710
DECL|macro|DMA7_BUFFER1_START
mdefine_line|#define DMA7_BUFFER1_START       0x14002714
DECL|macro|DMA7_BUFFER1_COUNT
mdefine_line|#define DMA7_BUFFER1_COUNT       0x14002718
multiline_comment|/* Interrupt Controller 0 */
DECL|macro|INTC0_CONFIG0_READ
mdefine_line|#define INTC0_CONFIG0_READ        0x10400040
DECL|macro|INTC0_CONFIG0_SET
mdefine_line|#define INTC0_CONFIG0_SET         0x10400040
DECL|macro|INTC0_CONFIG0_CLEAR
mdefine_line|#define INTC0_CONFIG0_CLEAR       0x10400044
DECL|macro|INTC0_CONFIG1_READ
mdefine_line|#define INTC0_CONFIG1_READ        0x10400048
DECL|macro|INTC0_CONFIG1_SET
mdefine_line|#define INTC0_CONFIG1_SET         0x10400048
DECL|macro|INTC0_CONFIG1_CLEAR
mdefine_line|#define INTC0_CONFIG1_CLEAR       0x1040004C
DECL|macro|INTC0_CONFIG2_READ
mdefine_line|#define INTC0_CONFIG2_READ        0x10400050
DECL|macro|INTC0_CONFIG2_SET
mdefine_line|#define INTC0_CONFIG2_SET         0x10400050
DECL|macro|INTC0_CONFIG2_CLEAR
mdefine_line|#define INTC0_CONFIG2_CLEAR       0x10400054
DECL|macro|INTC0_REQ0_INT
mdefine_line|#define INTC0_REQ0_INT            0x10400054
DECL|macro|INTC0_SOURCE_READ
mdefine_line|#define INTC0_SOURCE_READ         0x10400058
DECL|macro|INTC0_SOURCE_SET
mdefine_line|#define INTC0_SOURCE_SET          0x10400058
DECL|macro|INTC0_SOURCE_CLEAR
mdefine_line|#define INTC0_SOURCE_CLEAR        0x1040005C
DECL|macro|INTC0_REQ1_INT
mdefine_line|#define INTC0_REQ1_INT            0x1040005C
DECL|macro|INTC0_ASSIGN_REQ_READ
mdefine_line|#define INTC0_ASSIGN_REQ_READ     0x10400060
DECL|macro|INTC0_ASSIGN_REQ_SET
mdefine_line|#define INTC0_ASSIGN_REQ_SET      0x10400060
DECL|macro|INTC0_ASSIGN_REQ_CLEAR
mdefine_line|#define INTC0_ASSIGN_REQ_CLEAR    0x10400064
DECL|macro|INTC0_WAKEUP_READ
mdefine_line|#define INTC0_WAKEUP_READ         0x10400068
DECL|macro|INTC0_WAKEUP_SET
mdefine_line|#define INTC0_WAKEUP_SET          0x10400068
DECL|macro|INTC0_WAKEUP_CLEAR
mdefine_line|#define INTC0_WAKEUP_CLEAR        0x1040006C
DECL|macro|INTC0_MASK_READ
mdefine_line|#define INTC0_MASK_READ           0x10400070
DECL|macro|INTC0_MASK_SET
mdefine_line|#define INTC0_MASK_SET            0x10400070
DECL|macro|INTC0_MASK_CLEAR
mdefine_line|#define INTC0_MASK_CLEAR          0x10400074
DECL|macro|INTC0_R_EDGE_DETECT
mdefine_line|#define INTC0_R_EDGE_DETECT       0x10400078
DECL|macro|INTC0_R_EDGE_DETECT_CLEAR
mdefine_line|#define INTC0_R_EDGE_DETECT_CLEAR 0x10400078
DECL|macro|INTC0_F_EDGE_DETECT_CLEAR
mdefine_line|#define INTC0_F_EDGE_DETECT_CLEAR 0x1040007C
DECL|macro|INTC0_TEST_BIT
mdefine_line|#define INTC0_TEST_BIT            0x10400080
multiline_comment|/* Interrupt Controller 1 */
DECL|macro|INTC1_CONFIG0_READ
mdefine_line|#define INTC1_CONFIG0_READ        0x11800040
DECL|macro|INTC1_CONFIG0_SET
mdefine_line|#define INTC1_CONFIG0_SET         0x11800040
DECL|macro|INTC1_CONFIG0_CLEAR
mdefine_line|#define INTC1_CONFIG0_CLEAR       0x11800044
DECL|macro|INTC1_CONFIG1_READ
mdefine_line|#define INTC1_CONFIG1_READ        0x11800048
DECL|macro|INTC1_CONFIG1_SET
mdefine_line|#define INTC1_CONFIG1_SET         0x11800048
DECL|macro|INTC1_CONFIG1_CLEAR
mdefine_line|#define INTC1_CONFIG1_CLEAR       0x1180004C
DECL|macro|INTC1_CONFIG2_READ
mdefine_line|#define INTC1_CONFIG2_READ        0x11800050
DECL|macro|INTC1_CONFIG2_SET
mdefine_line|#define INTC1_CONFIG2_SET         0x11800050
DECL|macro|INTC1_CONFIG2_CLEAR
mdefine_line|#define INTC1_CONFIG2_CLEAR       0x11800054
DECL|macro|INTC1_REQ0_INT
mdefine_line|#define INTC1_REQ0_INT            0x11800054
DECL|macro|INTC1_SOURCE_READ
mdefine_line|#define INTC1_SOURCE_READ         0x11800058
DECL|macro|INTC1_SOURCE_SET
mdefine_line|#define INTC1_SOURCE_SET          0x11800058
DECL|macro|INTC1_SOURCE_CLEAR
mdefine_line|#define INTC1_SOURCE_CLEAR        0x1180005C
DECL|macro|INTC1_REQ1_INT
mdefine_line|#define INTC1_REQ1_INT            0x1180005C
DECL|macro|INTC1_ASSIGN_REQ_READ
mdefine_line|#define INTC1_ASSIGN_REQ_READ     0x11800060
DECL|macro|INTC1_ASSIGN_REQ_SET
mdefine_line|#define INTC1_ASSIGN_REQ_SET      0x11800060
DECL|macro|INTC1_ASSIGN_REQ_CLEAR
mdefine_line|#define INTC1_ASSIGN_REQ_CLEAR    0x11800064
DECL|macro|INTC1_WAKEUP_READ
mdefine_line|#define INTC1_WAKEUP_READ         0x11800068
DECL|macro|INTC1_WAKEUP_SET
mdefine_line|#define INTC1_WAKEUP_SET          0x11800068
DECL|macro|INTC1_WAKEUP_CLEAR
mdefine_line|#define INTC1_WAKEUP_CLEAR        0x1180006C
DECL|macro|INTC1_MASK_READ
mdefine_line|#define INTC1_MASK_READ           0x11800070
DECL|macro|INTC1_MASK_SET
mdefine_line|#define INTC1_MASK_SET            0x11800070
DECL|macro|INTC1_MASK_CLEAR
mdefine_line|#define INTC1_MASK_CLEAR          0x11800074
DECL|macro|INTC1_R_EDGE_DETECT
mdefine_line|#define INTC1_R_EDGE_DETECT       0x11800078
DECL|macro|INTC1_R_EDGE_DETECT_CLEAR
mdefine_line|#define INTC1_R_EDGE_DETECT_CLEAR 0x11800078
DECL|macro|INTC1_F_EDGE_DETECT_CLEAR
mdefine_line|#define INTC1_F_EDGE_DETECT_CLEAR 0x1180007C
DECL|macro|INTC1_TEST_BIT
mdefine_line|#define INTC1_TEST_BIT            0x11800080
multiline_comment|/* Interrupt Configuration Modes */
DECL|macro|INTC_INT_DISABLED
mdefine_line|#define INTC_INT_DISABLED                0
DECL|macro|INTC_INT_RISE_EDGE
mdefine_line|#define INTC_INT_RISE_EDGE             0x1
DECL|macro|INTC_INT_FALL_EDGE
mdefine_line|#define INTC_INT_FALL_EDGE             0x2
DECL|macro|INTC_INT_RISE_AND_FALL_EDGE
mdefine_line|#define INTC_INT_RISE_AND_FALL_EDGE    0x3
DECL|macro|INTC_INT_HIGH_LEVEL
mdefine_line|#define INTC_INT_HIGH_LEVEL            0x5
DECL|macro|INTC_INT_LOW_LEVEL
mdefine_line|#define INTC_INT_LOW_LEVEL             0x6
DECL|macro|INTC_INT_HIGH_AND_LOW_LEVEL
mdefine_line|#define INTC_INT_HIGH_AND_LOW_LEVEL    0x7
multiline_comment|/* Interrupt Numbers */
DECL|macro|AU1000_UART0_INT
mdefine_line|#define AU1000_UART0_INT          0
DECL|macro|AU1000_UART1_INT
mdefine_line|#define AU1000_UART1_INT          1
DECL|macro|AU1000_UART2_INT
mdefine_line|#define AU1000_UART2_INT          2
DECL|macro|AU1000_UART3_INT
mdefine_line|#define AU1000_UART3_INT          3
DECL|macro|AU1000_SSI0_INT
mdefine_line|#define AU1000_SSI0_INT           4
DECL|macro|AU1000_SSI1_INT
mdefine_line|#define AU1000_SSI1_INT           5
DECL|macro|AU1000_DMA0_INT
mdefine_line|#define AU1000_DMA0_INT           6
DECL|macro|AU1000_DMA1_INT
mdefine_line|#define AU1000_DMA1_INT           7
DECL|macro|AU1000_DMA2_INT
mdefine_line|#define AU1000_DMA2_INT           8
DECL|macro|AU1000_DMA3_INT
mdefine_line|#define AU1000_DMA3_INT           9
DECL|macro|AU1000_DMA4_INT
mdefine_line|#define AU1000_DMA4_INT           10
DECL|macro|AU1000_DMA5_INT
mdefine_line|#define AU1000_DMA5_INT           11
DECL|macro|AU1000_DMA6_INT
mdefine_line|#define AU1000_DMA6_INT           12
DECL|macro|AU1000_DMA7_INT
mdefine_line|#define AU1000_DMA7_INT           13
DECL|macro|AU1000_PC0_INT
mdefine_line|#define AU1000_PC0_INT            14
DECL|macro|AU1000_PC0_MATCH0_INT
mdefine_line|#define AU1000_PC0_MATCH0_INT     15
DECL|macro|AU1000_PC0_MATCH1_INT
mdefine_line|#define AU1000_PC0_MATCH1_INT     16
DECL|macro|AU1000_PC0_MATCH2_INT
mdefine_line|#define AU1000_PC0_MATCH2_INT     17
DECL|macro|AU1000_PC1_INT
mdefine_line|#define AU1000_PC1_INT            18
DECL|macro|AU1000_PC1_MATCH0_INT
mdefine_line|#define AU1000_PC1_MATCH0_INT     19
DECL|macro|AU1000_PC1_MATCH1_INT
mdefine_line|#define AU1000_PC1_MATCH1_INT     20
DECL|macro|AU1000_PC1_MATCH2_INT
mdefine_line|#define AU1000_PC1_MATCH2_INT     21
DECL|macro|AU1000_IRDA_TX_INT
mdefine_line|#define AU1000_IRDA_TX_INT        22
DECL|macro|AU1000_IRDA_RX_INT
mdefine_line|#define AU1000_IRDA_RX_INT        23
DECL|macro|AU1000_USB_DEV_REQ_INT
mdefine_line|#define AU1000_USB_DEV_REQ_INT    24
DECL|macro|AU1000_USB_DEV_SUS_INT
mdefine_line|#define AU1000_USB_DEV_SUS_INT    25
DECL|macro|AU1000_USB_HOST_INT
mdefine_line|#define AU1000_USB_HOST_INT       26
DECL|macro|AU1000_ACSYNC_INT
mdefine_line|#define AU1000_ACSYNC_INT         27
DECL|macro|AU1000_MAC0_DMA_INT
mdefine_line|#define AU1000_MAC0_DMA_INT       28
DECL|macro|AU1000_MAC1_DMA_INT
mdefine_line|#define AU1000_MAC1_DMA_INT       29
DECL|macro|AU1000_ETH0_IRQ
mdefine_line|#define AU1000_ETH0_IRQ           AU1000_MAC0_DMA_INT
DECL|macro|AU1000_ETH1_IRQ
mdefine_line|#define AU1000_ETH1_IRQ           AU1000_MAC1_DMA_INT
DECL|macro|AU1000_I2S_UO_INT
mdefine_line|#define AU1000_I2S_UO_INT         30
DECL|macro|AU1000_AC97_INT
mdefine_line|#define AU1000_AC97_INT           31
DECL|macro|AU1000_LAST_INTC0_INT
mdefine_line|#define AU1000_LAST_INTC0_INT     AU1000_AC97_INT
DECL|macro|AU1000_GPIO_0
mdefine_line|#define AU1000_GPIO_0             32
DECL|macro|AU1000_GPIO_1
mdefine_line|#define AU1000_GPIO_1             33
DECL|macro|AU1000_GPIO_2
mdefine_line|#define AU1000_GPIO_2             34
DECL|macro|AU1000_GPIO_3
mdefine_line|#define AU1000_GPIO_3             35
DECL|macro|AU1000_GPIO_4
mdefine_line|#define AU1000_GPIO_4             36
DECL|macro|AU1000_GPIO_5
mdefine_line|#define AU1000_GPIO_5             37
DECL|macro|AU1000_GPIO_6
mdefine_line|#define AU1000_GPIO_6             38
DECL|macro|AU1000_GPIO_7
mdefine_line|#define AU1000_GPIO_7             39
DECL|macro|AU1000_GPIO_8
mdefine_line|#define AU1000_GPIO_8             40
DECL|macro|AU1000_GPIO_9
mdefine_line|#define AU1000_GPIO_9             41
DECL|macro|AU1000_GPIO_10
mdefine_line|#define AU1000_GPIO_10            42
DECL|macro|AU1000_GPIO_11
mdefine_line|#define AU1000_GPIO_11            43
DECL|macro|AU1000_GPIO_12
mdefine_line|#define AU1000_GPIO_12            44
DECL|macro|AU1000_GPIO_13
mdefine_line|#define AU1000_GPIO_13            45
DECL|macro|AU1000_GPIO_14
mdefine_line|#define AU1000_GPIO_14            46
DECL|macro|AU1000_GPIO_15
mdefine_line|#define AU1000_GPIO_15            47
DECL|macro|AU1000_GPIO_16
mdefine_line|#define AU1000_GPIO_16            48
DECL|macro|AU1000_GPIO_17
mdefine_line|#define AU1000_GPIO_17            49
DECL|macro|AU1000_GPIO_18
mdefine_line|#define AU1000_GPIO_18            50
DECL|macro|AU1000_GPIO_19
mdefine_line|#define AU1000_GPIO_19            51
DECL|macro|AU1000_GPIO_20
mdefine_line|#define AU1000_GPIO_20            52
DECL|macro|AU1000_GPIO_21
mdefine_line|#define AU1000_GPIO_21            53
DECL|macro|AU1000_GPIO_22
mdefine_line|#define AU1000_GPIO_22            54
DECL|macro|AU1000_GPIO_23
mdefine_line|#define AU1000_GPIO_23            55
DECL|macro|AU1000_GPIO_24
mdefine_line|#define AU1000_GPIO_24            56
DECL|macro|AU1000_GPIO_25
mdefine_line|#define AU1000_GPIO_25            57
DECL|macro|AU1000_GPIO_26
mdefine_line|#define AU1000_GPIO_26            58
DECL|macro|AU1000_GPIO_27
mdefine_line|#define AU1000_GPIO_27            59
DECL|macro|AU1000_GPIO_28
mdefine_line|#define AU1000_GPIO_28            60
DECL|macro|AU1000_GPIO_29
mdefine_line|#define AU1000_GPIO_29            61
DECL|macro|AU1000_GPIO_30
mdefine_line|#define AU1000_GPIO_30            62
DECL|macro|AU1000_GPIO_31
mdefine_line|#define AU1000_GPIO_31            63
multiline_comment|/* Programmable Counters 0 and 1 */
DECL|macro|PC_BASE
mdefine_line|#define PC_BASE                   0x11900000
DECL|macro|PC_COUNTER_CNTRL
mdefine_line|#define PC_COUNTER_CNTRL          (PC_BASE + 0x14)
DECL|macro|PC_CNTRL_E1S
mdefine_line|#define PC_CNTRL_E1S            (1&lt;&lt;23)
DECL|macro|PC_CNTRL_T1S
mdefine_line|#define PC_CNTRL_T1S            (1&lt;&lt;20)
DECL|macro|PC_CNTRL_M21
mdefine_line|#define PC_CNTRL_M21            (1&lt;&lt;19)
DECL|macro|PC_CNTRL_M11
mdefine_line|#define PC_CNTRL_M11            (1&lt;&lt;18)
DECL|macro|PC_CNTRL_M01
mdefine_line|#define PC_CNTRL_M01            (1&lt;&lt;17)
DECL|macro|PC_CNTRL_C1S
mdefine_line|#define PC_CNTRL_C1S            (1&lt;&lt;16)
DECL|macro|PC_CNTRL_BP
mdefine_line|#define PC_CNTRL_BP             (1&lt;&lt;14)
DECL|macro|PC_CNTRL_EN1
mdefine_line|#define PC_CNTRL_EN1            (1&lt;&lt;13)
DECL|macro|PC_CNTRL_BT1
mdefine_line|#define PC_CNTRL_BT1            (1&lt;&lt;12)
DECL|macro|PC_CNTRL_EN0
mdefine_line|#define PC_CNTRL_EN0            (1&lt;&lt;11)
DECL|macro|PC_CNTRL_BT0
mdefine_line|#define PC_CNTRL_BT0            (1&lt;&lt;10)
DECL|macro|PC_CNTRL_E0
mdefine_line|#define PC_CNTRL_E0             (1&lt;&lt;8)
DECL|macro|PC_CNTRL_E0S
mdefine_line|#define PC_CNTRL_E0S            (1&lt;&lt;7)
DECL|macro|PC_CNTRL_32S
mdefine_line|#define PC_CNTRL_32S            (1&lt;&lt;5)
DECL|macro|PC_CNTRL_T0S
mdefine_line|#define PC_CNTRL_T0S            (1&lt;&lt;4)
DECL|macro|PC_CNTRL_M20
mdefine_line|#define PC_CNTRL_M20            (1&lt;&lt;3)
DECL|macro|PC_CNTRL_M10
mdefine_line|#define PC_CNTRL_M10            (1&lt;&lt;2)
DECL|macro|PC_CNTRL_M00
mdefine_line|#define PC_CNTRL_M00            (1&lt;&lt;1)
DECL|macro|PC_CNTRL_C0S
mdefine_line|#define PC_CNTRL_C0S            (1&lt;&lt;0)
multiline_comment|/* Programmable Counter 0 Registers */
DECL|macro|PC0_TRIM
mdefine_line|#define PC0_TRIM                  (PC_BASE + 0)
DECL|macro|PC0_COUNTER_WRITE
mdefine_line|#define PC0_COUNTER_WRITE         (PC_BASE + 4)
DECL|macro|PC0_MATCH0
mdefine_line|#define PC0_MATCH0                (PC_BASE + 8)
DECL|macro|PC0_MATCH1
mdefine_line|#define PC0_MATCH1                (PC_BASE + 0xC)
DECL|macro|PC0_MATCH2
mdefine_line|#define PC0_MATCH2                (PC_BASE + 0x10)
DECL|macro|PC0_COUNTER_READ
mdefine_line|#define PC0_COUNTER_READ          (PC_BASE + 0x40)
multiline_comment|/* Programmable Counter 1 Registers */
DECL|macro|PC1_TRIM
mdefine_line|#define PC1_TRIM                  (PC_BASE + 0x44)
DECL|macro|PC1_COUNTER_WRITE
mdefine_line|#define PC1_COUNTER_WRITE         (PC_BASE + 0x48)
DECL|macro|PC1_MATCH0
mdefine_line|#define PC1_MATCH0                (PC_BASE + 0x4C)
DECL|macro|PC1_MATCH1
mdefine_line|#define PC1_MATCH1                (PC_BASE + 0x50)
DECL|macro|PC1_MATCH2
mdefine_line|#define PC1_MATCH2                (PC_BASE + 0x54)
DECL|macro|PC1_COUNTER_READ
mdefine_line|#define PC1_COUNTER_READ          (PC_BASE + 0x58)
multiline_comment|/* I2S Controller */
DECL|macro|I2S_DATA
mdefine_line|#define I2S_DATA                  0x11000000
DECL|macro|I2S_CONFIG_STATUS
mdefine_line|#define I2S_CONFIG_STATUS         0x11000001
DECL|macro|I2S_CONTROL
mdefine_line|#define I2S_CONTROL               0x11000002
multiline_comment|/* Ethernet Controllers  */
DECL|macro|AU1000_ETH0_BASE
mdefine_line|#define AU1000_ETH0_BASE          0x10500000
DECL|macro|AU1000_ETH1_BASE
mdefine_line|#define AU1000_ETH1_BASE          0x10510000
multiline_comment|/* 4 byte offsets from AU1000_ETH_BASE */
DECL|macro|MAC_CONTROL
mdefine_line|#define MAC_CONTROL                     0x0
DECL|macro|MAC_RX_ENABLE
mdefine_line|#define MAC_RX_ENABLE               (1&lt;&lt;2) 
DECL|macro|MAC_TX_ENABLE
mdefine_line|#define MAC_TX_ENABLE               (1&lt;&lt;3)
DECL|macro|MAC_DEF_CHECK
mdefine_line|#define MAC_DEF_CHECK               (1&lt;&lt;5) 
DECL|macro|MAC_SET_BL
mdefine_line|#define MAC_SET_BL(X)       (((X)&amp;0x3)&lt;&lt;6)
DECL|macro|MAC_AUTO_PAD
mdefine_line|#define MAC_AUTO_PAD                (1&lt;&lt;8)
DECL|macro|MAC_DISABLE_RETRY
mdefine_line|#define MAC_DISABLE_RETRY          (1&lt;&lt;10)
DECL|macro|MAC_DISABLE_BCAST
mdefine_line|#define MAC_DISABLE_BCAST          (1&lt;&lt;11)
DECL|macro|MAC_LATE_COL
mdefine_line|#define MAC_LATE_COL               (1&lt;&lt;12)
DECL|macro|MAC_HASH_MODE
mdefine_line|#define MAC_HASH_MODE              (1&lt;&lt;13)
DECL|macro|MAC_HASH_ONLY
mdefine_line|#define MAC_HASH_ONLY              (1&lt;&lt;15)
DECL|macro|MAC_PASS_ALL
mdefine_line|#define MAC_PASS_ALL               (1&lt;&lt;16)
DECL|macro|MAC_INVERSE_FILTER
mdefine_line|#define MAC_INVERSE_FILTER         (1&lt;&lt;17)
DECL|macro|MAC_PROMISCUOUS
mdefine_line|#define MAC_PROMISCUOUS            (1&lt;&lt;18)
DECL|macro|MAC_PASS_ALL_MULTI
mdefine_line|#define MAC_PASS_ALL_MULTI         (1&lt;&lt;19)
DECL|macro|MAC_FULL_DUPLEX
mdefine_line|#define MAC_FULL_DUPLEX            (1&lt;&lt;20)
DECL|macro|MAC_NORMAL_MODE
mdefine_line|#define MAC_NORMAL_MODE                 0
DECL|macro|MAC_INT_LOOPBACK
mdefine_line|#define MAC_INT_LOOPBACK           (1&lt;&lt;21)
DECL|macro|MAC_EXT_LOOPBACK
mdefine_line|#define MAC_EXT_LOOPBACK           (1&lt;&lt;22)
DECL|macro|MAC_DISABLE_RX_OWN
mdefine_line|#define MAC_DISABLE_RX_OWN         (1&lt;&lt;23)
DECL|macro|MAC_BIG_ENDIAN
mdefine_line|#define MAC_BIG_ENDIAN             (1&lt;&lt;30)
DECL|macro|MAC_RX_ALL
mdefine_line|#define MAC_RX_ALL                 (1&lt;&lt;31)
DECL|macro|MAC_ADDRESS_HIGH
mdefine_line|#define MAC_ADDRESS_HIGH                0x4
DECL|macro|MAC_ADDRESS_LOW
mdefine_line|#define MAC_ADDRESS_LOW                 0x8
DECL|macro|MAC_MCAST_HIGH
mdefine_line|#define MAC_MCAST_HIGH                  0xC
DECL|macro|MAC_MCAST_LOW
mdefine_line|#define MAC_MCAST_LOW                  0x10
DECL|macro|MAC_MII_CNTRL
mdefine_line|#define MAC_MII_CNTRL                  0x14
DECL|macro|MAC_MII_BUSY
mdefine_line|#define MAC_MII_BUSY                (1&lt;&lt;0)
DECL|macro|MAC_MII_READ
mdefine_line|#define MAC_MII_READ                     0 
DECL|macro|MAC_MII_WRITE
mdefine_line|#define MAC_MII_WRITE               (1&lt;&lt;1)
DECL|macro|MAC_SET_MII_SELECT_REG
mdefine_line|#define MAC_SET_MII_SELECT_REG(X)   (((X)&amp;0x1f)&lt;&lt;6)
DECL|macro|MAC_SET_MII_SELECT_PHY
mdefine_line|#define MAC_SET_MII_SELECT_PHY(X)   (((X)&amp;0x1f)&lt;&lt;11)
DECL|macro|MAC_MII_DATA
mdefine_line|#define MAC_MII_DATA                   0x18
DECL|macro|MAC_FLOW_CNTRL
mdefine_line|#define MAC_FLOW_CNTRL                 0x1C
DECL|macro|MAC_FLOW_CNTRL_BUSY
mdefine_line|#define MAC_FLOW_CNTRL_BUSY         (1&lt;&lt;0)
DECL|macro|MAC_FLOW_CNTRL_ENABLE
mdefine_line|#define MAC_FLOW_CNTRL_ENABLE       (1&lt;&lt;1)
DECL|macro|MAC_PASS_CONTROL
mdefine_line|#define MAC_PASS_CONTROL            (1&lt;&lt;2)
DECL|macro|MAC_SET_PAUSE
mdefine_line|#define MAC_SET_PAUSE(X)        (((X)&amp;0xffff)&lt;&lt;16)
DECL|macro|MAC_VLAN1_TAG
mdefine_line|#define MAC_VLAN1_TAG                  0x20
DECL|macro|MAC_VLAN2_TAG
mdefine_line|#define MAC_VLAN2_TAG                  0x24
multiline_comment|/* Ethernet Controller Enable */
DECL|macro|MAC0_ENABLE
mdefine_line|#define MAC0_ENABLE               0x10520000
DECL|macro|MAC1_ENABLE
mdefine_line|#define MAC1_ENABLE               0x10520004
DECL|macro|MAC_EN_CLOCK_ENABLE
mdefine_line|#define MAC_EN_CLOCK_ENABLE         (1&lt;&lt;0)
DECL|macro|MAC_EN_RESET0
mdefine_line|#define MAC_EN_RESET0               (1&lt;&lt;1)
DECL|macro|MAC_EN_TOSS
mdefine_line|#define MAC_EN_TOSS                 (1&lt;&lt;2)
DECL|macro|MAC_EN_CACHEABLE
mdefine_line|#define MAC_EN_CACHEABLE            (1&lt;&lt;3)
DECL|macro|MAC_EN_RESET1
mdefine_line|#define MAC_EN_RESET1               (1&lt;&lt;4)
DECL|macro|MAC_EN_RESET2
mdefine_line|#define MAC_EN_RESET2               (1&lt;&lt;5)
DECL|macro|MAC_DMA_RESET
mdefine_line|#define MAC_DMA_RESET               (1&lt;&lt;6)
multiline_comment|/* Ethernet Controller DMA Channels */
DECL|macro|MAC0_TX_DMA_ADDR
mdefine_line|#define MAC0_TX_DMA_ADDR         0x14004000
DECL|macro|MAC1_TX_DMA_ADDR
mdefine_line|#define MAC1_TX_DMA_ADDR         0x14004200
multiline_comment|/* offsets from MAC_TX_RING_ADDR address */
DECL|macro|MAC_TX_BUFF0_STATUS
mdefine_line|#define MAC_TX_BUFF0_STATUS             0x0
DECL|macro|TX_FRAME_ABORTED
mdefine_line|#define TX_FRAME_ABORTED            (1&lt;&lt;0)
DECL|macro|TX_JAB_TIMEOUT
mdefine_line|#define TX_JAB_TIMEOUT              (1&lt;&lt;1)
DECL|macro|TX_NO_CARRIER
mdefine_line|#define TX_NO_CARRIER               (1&lt;&lt;2)
DECL|macro|TX_LOSS_CARRIER
mdefine_line|#define TX_LOSS_CARRIER             (1&lt;&lt;3)
DECL|macro|TX_EXC_DEF
mdefine_line|#define TX_EXC_DEF                  (1&lt;&lt;4)
DECL|macro|TX_LATE_COLL_ABORT
mdefine_line|#define TX_LATE_COLL_ABORT          (1&lt;&lt;5)
DECL|macro|TX_EXC_COLL
mdefine_line|#define TX_EXC_COLL                 (1&lt;&lt;6)
DECL|macro|TX_UNDERRUN
mdefine_line|#define TX_UNDERRUN                 (1&lt;&lt;7)
DECL|macro|TX_DEFERRED
mdefine_line|#define TX_DEFERRED                 (1&lt;&lt;8)
DECL|macro|TX_LATE_COLL
mdefine_line|#define TX_LATE_COLL                (1&lt;&lt;9)
DECL|macro|TX_COLL_CNT_MASK
mdefine_line|#define TX_COLL_CNT_MASK         (0xF&lt;&lt;10)
DECL|macro|TX_PKT_RETRY
mdefine_line|#define TX_PKT_RETRY               (1&lt;&lt;31)
DECL|macro|MAC_TX_BUFF0_ADDR
mdefine_line|#define MAC_TX_BUFF0_ADDR                0x4
DECL|macro|TX_DMA_ENABLE
mdefine_line|#define TX_DMA_ENABLE               (1&lt;&lt;0)
DECL|macro|TX_T_DONE
mdefine_line|#define TX_T_DONE                   (1&lt;&lt;1)
DECL|macro|TX_GET_DMA_BUFFER
mdefine_line|#define TX_GET_DMA_BUFFER(X)    (((X)&gt;&gt;2)&amp;0x3)
DECL|macro|MAC_TX_BUFF0_LEN
mdefine_line|#define MAC_TX_BUFF0_LEN                 0x8
DECL|macro|MAC_TX_BUFF1_STATUS
mdefine_line|#define MAC_TX_BUFF1_STATUS             0x10
DECL|macro|MAC_TX_BUFF1_ADDR
mdefine_line|#define MAC_TX_BUFF1_ADDR               0x14
DECL|macro|MAC_TX_BUFF1_LEN
mdefine_line|#define MAC_TX_BUFF1_LEN                0x18
DECL|macro|MAC_TX_BUFF2_STATUS
mdefine_line|#define MAC_TX_BUFF2_STATUS             0x20
DECL|macro|MAC_TX_BUFF2_ADDR
mdefine_line|#define MAC_TX_BUFF2_ADDR               0x24
DECL|macro|MAC_TX_BUFF2_LEN
mdefine_line|#define MAC_TX_BUFF2_LEN                0x28
DECL|macro|MAC_TX_BUFF3_STATUS
mdefine_line|#define MAC_TX_BUFF3_STATUS             0x30
DECL|macro|MAC_TX_BUFF3_ADDR
mdefine_line|#define MAC_TX_BUFF3_ADDR               0x34
DECL|macro|MAC_TX_BUFF3_LEN
mdefine_line|#define MAC_TX_BUFF3_LEN                0x38
DECL|macro|MAC0_RX_DMA_ADDR
mdefine_line|#define MAC0_RX_DMA_ADDR         0x14004100
DECL|macro|MAC1_RX_DMA_ADDR
mdefine_line|#define MAC1_RX_DMA_ADDR         0x14004300
multiline_comment|/* offsets from MAC_RX_RING_ADDR */
DECL|macro|MAC_RX_BUFF0_STATUS
mdefine_line|#define MAC_RX_BUFF0_STATUS              0x0
DECL|macro|RX_FRAME_LEN_MASK
mdefine_line|#define RX_FRAME_LEN_MASK           0x3fff
DECL|macro|RX_WDOG_TIMER
mdefine_line|#define RX_WDOG_TIMER              (1&lt;&lt;14)
DECL|macro|RX_RUNT
mdefine_line|#define RX_RUNT                    (1&lt;&lt;15)
DECL|macro|RX_OVERLEN
mdefine_line|#define RX_OVERLEN                 (1&lt;&lt;16)
DECL|macro|RX_COLL
mdefine_line|#define RX_COLL                    (1&lt;&lt;17)
DECL|macro|RX_ETHER
mdefine_line|#define RX_ETHER                   (1&lt;&lt;18)
DECL|macro|RX_MII_ERROR
mdefine_line|#define RX_MII_ERROR               (1&lt;&lt;19)
DECL|macro|RX_DRIBBLING
mdefine_line|#define RX_DRIBBLING               (1&lt;&lt;20)
DECL|macro|RX_CRC_ERROR
mdefine_line|#define RX_CRC_ERROR               (1&lt;&lt;21)
DECL|macro|RX_VLAN1
mdefine_line|#define RX_VLAN1                   (1&lt;&lt;22)
DECL|macro|RX_VLAN2
mdefine_line|#define RX_VLAN2                   (1&lt;&lt;23)
DECL|macro|RX_LEN_ERROR
mdefine_line|#define RX_LEN_ERROR               (1&lt;&lt;24)
DECL|macro|RX_CNTRL_FRAME
mdefine_line|#define RX_CNTRL_FRAME             (1&lt;&lt;25)
DECL|macro|RX_U_CNTRL_FRAME
mdefine_line|#define RX_U_CNTRL_FRAME           (1&lt;&lt;26)
DECL|macro|RX_MCAST_FRAME
mdefine_line|#define RX_MCAST_FRAME             (1&lt;&lt;27)
DECL|macro|RX_BCAST_FRAME
mdefine_line|#define RX_BCAST_FRAME             (1&lt;&lt;28)
DECL|macro|RX_FILTER_FAIL
mdefine_line|#define RX_FILTER_FAIL             (1&lt;&lt;29)
DECL|macro|RX_PACKET_FILTER
mdefine_line|#define RX_PACKET_FILTER           (1&lt;&lt;30)
DECL|macro|RX_MISSED_FRAME
mdefine_line|#define RX_MISSED_FRAME            (1&lt;&lt;31)
DECL|macro|RX_ERROR
mdefine_line|#define RX_ERROR (RX_WDOG_TIMER | RX_RUNT | RX_OVERLEN |  &bslash;&n;                    RX_COLL | RX_MII_ERROR | RX_CRC_ERROR | &bslash;&n;                    RX_LEN_ERROR | RX_U_CNTRL_FRAME | RX_MISSED_FRAME)
DECL|macro|MAC_RX_BUFF0_ADDR
mdefine_line|#define MAC_RX_BUFF0_ADDR                0x4
DECL|macro|RX_DMA_ENABLE
mdefine_line|#define RX_DMA_ENABLE               (1&lt;&lt;0)
DECL|macro|RX_T_DONE
mdefine_line|#define RX_T_DONE                   (1&lt;&lt;1)
DECL|macro|RX_GET_DMA_BUFFER
mdefine_line|#define RX_GET_DMA_BUFFER(X)    (((X)&gt;&gt;2)&amp;0x3)
DECL|macro|RX_SET_BUFF_ADDR
mdefine_line|#define RX_SET_BUFF_ADDR(X)     ((X)&amp;0xffffffc0)
DECL|macro|MAC_RX_BUFF1_STATUS
mdefine_line|#define MAC_RX_BUFF1_STATUS              0x10
DECL|macro|MAC_RX_BUFF1_ADDR
mdefine_line|#define MAC_RX_BUFF1_ADDR                0x14
DECL|macro|MAC_RX_BUFF2_STATUS
mdefine_line|#define MAC_RX_BUFF2_STATUS              0x20
DECL|macro|MAC_RX_BUFF2_ADDR
mdefine_line|#define MAC_RX_BUFF2_ADDR                0x24
DECL|macro|MAC_RX_BUFF3_STATUS
mdefine_line|#define MAC_RX_BUFF3_STATUS              0x30
DECL|macro|MAC_RX_BUFF3_ADDR
mdefine_line|#define MAC_RX_BUFF3_ADDR                0x34
multiline_comment|/* UARTS 0-3 */
DECL|macro|UART0_ADDR
mdefine_line|#define UART0_ADDR                0x11100000
DECL|macro|UART1_ADDR
mdefine_line|#define UART1_ADDR                0x11200000
DECL|macro|UART2_ADDR
mdefine_line|#define UART2_ADDR                0x11300000
DECL|macro|UART3_ADDR
mdefine_line|#define UART3_ADDR                0x11400000
DECL|macro|UART_RX
mdefine_line|#define UART_RX&t;&t;0&t;/* Receive buffer */
DECL|macro|UART_TX
mdefine_line|#define UART_TX&t;&t;4&t;/* Transmit buffer */
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;8&t;/* Interrupt Enable Register */
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;0xC&t;/* Interrupt ID Register */
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR&t;0x10&t;/* FIFO Control Register */
DECL|macro|UART_LCR
mdefine_line|#define UART_LCR&t;0x14&t;/* Line Control Register */
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR&t;0x18&t;/* Modem Control Register */
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;0x1C&t;/* Line Status Register */
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR&t;0x20&t;/* Modem Status Register */
DECL|macro|UART_CLK
mdefine_line|#define UART_CLK&t;0x28&t;/* Baud Rat4e Clock Divider */
DECL|macro|UART_MOD_CNTRL
mdefine_line|#define UART_MOD_CNTRL&t;0x100&t;/* Module Control */
DECL|macro|UART_FCR_ENABLE_FIFO
mdefine_line|#define UART_FCR_ENABLE_FIFO&t;0x01 /* Enable the FIFO */
DECL|macro|UART_FCR_CLEAR_RCVR
mdefine_line|#define UART_FCR_CLEAR_RCVR&t;0x02 /* Clear the RCVR FIFO */
DECL|macro|UART_FCR_CLEAR_XMIT
mdefine_line|#define UART_FCR_CLEAR_XMIT&t;0x04 /* Clear the XMIT FIFO */
DECL|macro|UART_FCR_DMA_SELECT
mdefine_line|#define UART_FCR_DMA_SELECT&t;0x08 /* For DMA applications */
DECL|macro|UART_FCR_TRIGGER_MASK
mdefine_line|#define UART_FCR_TRIGGER_MASK&t;0xF0 /* Mask for the FIFO trigger range */
DECL|macro|UART_FCR_R_TRIGGER_1
mdefine_line|#define UART_FCR_R_TRIGGER_1&t;0x00 /* Mask for receive trigger set at 1 */
DECL|macro|UART_FCR_R_TRIGGER_4
mdefine_line|#define UART_FCR_R_TRIGGER_4&t;0x40 /* Mask for receive trigger set at 4 */
DECL|macro|UART_FCR_R_TRIGGER_8
mdefine_line|#define UART_FCR_R_TRIGGER_8&t;0x80 /* Mask for receive trigger set at 8 */
DECL|macro|UART_FCR_R_TRIGGER_14
mdefine_line|#define UART_FCR_R_TRIGGER_14   0xA0 /* Mask for receive trigger set at 14 */
DECL|macro|UART_FCR_T_TRIGGER_0
mdefine_line|#define UART_FCR_T_TRIGGER_0&t;0x00 /* Mask for transmit trigger set at 0 */
DECL|macro|UART_FCR_T_TRIGGER_4
mdefine_line|#define UART_FCR_T_TRIGGER_4&t;0x10 /* Mask for transmit trigger set at 4 */
DECL|macro|UART_FCR_T_TRIGGER_8
mdefine_line|#define UART_FCR_T_TRIGGER_8    0x20 /* Mask for transmit trigger set at 8 */
DECL|macro|UART_FCR_T_TRIGGER_12
mdefine_line|#define UART_FCR_T_TRIGGER_12&t;0x30 /* Mask for transmit trigger set at 12 */
multiline_comment|/*&n; * These are the definitions for the Line Control Register&n; */
DECL|macro|UART_LCR_SBC
mdefine_line|#define UART_LCR_SBC&t;0x40&t;/* Set break control */
DECL|macro|UART_LCR_SPAR
mdefine_line|#define UART_LCR_SPAR&t;0x20&t;/* Stick parity (?) */
DECL|macro|UART_LCR_EPAR
mdefine_line|#define UART_LCR_EPAR&t;0x10&t;/* Even parity select */
DECL|macro|UART_LCR_PARITY
mdefine_line|#define UART_LCR_PARITY&t;0x08&t;/* Parity Enable */
DECL|macro|UART_LCR_STOP
mdefine_line|#define UART_LCR_STOP&t;0x04&t;/* Stop bits: 0=1 stop bit, 1= 2 stop bits */
DECL|macro|UART_LCR_WLEN5
mdefine_line|#define UART_LCR_WLEN5  0x00&t;/* Wordlength: 5 bits */
DECL|macro|UART_LCR_WLEN6
mdefine_line|#define UART_LCR_WLEN6  0x01&t;/* Wordlength: 6 bits */
DECL|macro|UART_LCR_WLEN7
mdefine_line|#define UART_LCR_WLEN7  0x02&t;/* Wordlength: 7 bits */
DECL|macro|UART_LCR_WLEN8
mdefine_line|#define UART_LCR_WLEN8  0x03&t;/* Wordlength: 8 bits */
multiline_comment|/*&n; * These are the definitions for the Line Status Register&n; */
DECL|macro|UART_LSR_TEMT
mdefine_line|#define UART_LSR_TEMT&t;0x40&t;/* Transmitter empty */
DECL|macro|UART_LSR_THRE
mdefine_line|#define UART_LSR_THRE&t;0x20&t;/* Transmit-hold-register empty */
DECL|macro|UART_LSR_BI
mdefine_line|#define UART_LSR_BI&t;0x10&t;/* Break interrupt indicator */
DECL|macro|UART_LSR_FE
mdefine_line|#define UART_LSR_FE&t;0x08&t;/* Frame error indicator */
DECL|macro|UART_LSR_PE
mdefine_line|#define UART_LSR_PE&t;0x04&t;/* Parity error indicator */
DECL|macro|UART_LSR_OE
mdefine_line|#define UART_LSR_OE&t;0x02&t;/* Overrun error indicator */
DECL|macro|UART_LSR_DR
mdefine_line|#define UART_LSR_DR&t;0x01&t;/* Receiver data ready */
multiline_comment|/*&n; * These are the definitions for the Interrupt Identification Register&n; */
DECL|macro|UART_IIR_NO_INT
mdefine_line|#define UART_IIR_NO_INT&t;0x01&t;/* No interrupts pending */
DECL|macro|UART_IIR_ID
mdefine_line|#define UART_IIR_ID&t;0x06&t;/* Mask for the interrupt ID */
DECL|macro|UART_IIR_MSI
mdefine_line|#define UART_IIR_MSI&t;0x00&t;/* Modem status interrupt */
DECL|macro|UART_IIR_THRI
mdefine_line|#define UART_IIR_THRI&t;0x02&t;/* Transmitter holding register empty */
DECL|macro|UART_IIR_RDI
mdefine_line|#define UART_IIR_RDI&t;0x04&t;/* Receiver data interrupt */
DECL|macro|UART_IIR_RLSI
mdefine_line|#define UART_IIR_RLSI&t;0x06&t;/* Receiver line status interrupt */
multiline_comment|/*&n; * These are the definitions for the Interrupt Enable Register&n; */
DECL|macro|UART_IER_MSI
mdefine_line|#define UART_IER_MSI&t;0x08&t;/* Enable Modem status interrupt */
DECL|macro|UART_IER_RLSI
mdefine_line|#define UART_IER_RLSI&t;0x04&t;/* Enable receiver line status interrupt */
DECL|macro|UART_IER_THRI
mdefine_line|#define UART_IER_THRI&t;0x02&t;/* Enable Transmitter holding register int. */
DECL|macro|UART_IER_RDI
mdefine_line|#define UART_IER_RDI&t;0x01&t;/* Enable receiver data interrupt */
multiline_comment|/*&n; * These are the definitions for the Modem Control Register&n; */
DECL|macro|UART_MCR_LOOP
mdefine_line|#define UART_MCR_LOOP&t;0x10&t;/* Enable loopback test mode */
DECL|macro|UART_MCR_OUT2
mdefine_line|#define UART_MCR_OUT2&t;0x08&t;/* Out2 complement */
DECL|macro|UART_MCR_OUT1
mdefine_line|#define UART_MCR_OUT1&t;0x04&t;/* Out1 complement */
DECL|macro|UART_MCR_RTS
mdefine_line|#define UART_MCR_RTS&t;0x02&t;/* RTS complement */
DECL|macro|UART_MCR_DTR
mdefine_line|#define UART_MCR_DTR&t;0x01&t;/* DTR complement */
multiline_comment|/*&n; * These are the definitions for the Modem Status Register&n; */
DECL|macro|UART_MSR_DCD
mdefine_line|#define UART_MSR_DCD&t;0x80&t;/* Data Carrier Detect */
DECL|macro|UART_MSR_RI
mdefine_line|#define UART_MSR_RI&t;0x40&t;/* Ring Indicator */
DECL|macro|UART_MSR_DSR
mdefine_line|#define UART_MSR_DSR&t;0x20&t;/* Data Set Ready */
DECL|macro|UART_MSR_CTS
mdefine_line|#define UART_MSR_CTS&t;0x10&t;/* Clear to Send */
DECL|macro|UART_MSR_DDCD
mdefine_line|#define UART_MSR_DDCD&t;0x08&t;/* Delta DCD */
DECL|macro|UART_MSR_TERI
mdefine_line|#define UART_MSR_TERI&t;0x04&t;/* Trailing edge ring indicator */
DECL|macro|UART_MSR_DDSR
mdefine_line|#define UART_MSR_DDSR&t;0x02&t;/* Delta DSR */
DECL|macro|UART_MSR_DCTS
mdefine_line|#define UART_MSR_DCTS&t;0x01&t;/* Delta CTS */
DECL|macro|UART_MSR_ANY_DELTA
mdefine_line|#define UART_MSR_ANY_DELTA 0x0F&t;/* Any of the delta bits! */
multiline_comment|/* SSIO */
DECL|macro|SSI0_STATUS
mdefine_line|#define SSI0_STATUS                0x11600000
DECL|macro|SSI0_INT
mdefine_line|#define SSI0_INT                   0x11600004
DECL|macro|SSI0_INT_ENABLE
mdefine_line|#define SSI0_INT_ENABLE            0x11600008
DECL|macro|SSI0_CONFIG
mdefine_line|#define SSI0_CONFIG                0x11600020
DECL|macro|SSI0_ADATA
mdefine_line|#define SSI0_ADATA                 0x11600024
DECL|macro|SSI0_CLKDIV
mdefine_line|#define SSI0_CLKDIV                0x11600028
DECL|macro|SSI0_CONTROL
mdefine_line|#define SSI0_CONTROL               0x11600100
multiline_comment|/* SSI1 */
DECL|macro|SSI1_STATUS
mdefine_line|#define SSI1_STATUS                0x11680000
DECL|macro|SSI1_INT
mdefine_line|#define SSI1_INT                   0x11680004
DECL|macro|SSI1_INT_ENABLE
mdefine_line|#define SSI1_INT_ENABLE            0x11680008
DECL|macro|SSI1_CONFIG
mdefine_line|#define SSI1_CONFIG                0x11680020
DECL|macro|SSI1_ADATA
mdefine_line|#define SSI1_ADATA                 0x11680024
DECL|macro|SSI1_CLKDIV
mdefine_line|#define SSI1_CLKDIV                0x11680028
DECL|macro|SSI1_CONTROL
mdefine_line|#define SSI1_CONTROL               0x11680100
multiline_comment|/* IrDA Controller */
DECL|macro|IR_RING_PTR_STATUS
mdefine_line|#define IR_RING_PTR_STATUS        0x11500000
DECL|macro|IR_RING_BASE_ADDR_H
mdefine_line|#define IR_RING_BASE_ADDR_H       0x11500004
DECL|macro|IR_RING_BASE_ADDR_L
mdefine_line|#define IR_RING_BASE_ADDR_L       0x11500008
DECL|macro|IR_RING_SIZE
mdefine_line|#define IR_RING_SIZE              0x1150000C
DECL|macro|IR_RING_PROMPT
mdefine_line|#define IR_RING_PROMPT            0x11500010
DECL|macro|IR_RING_ADDR_CMPR
mdefine_line|#define IR_RING_ADDR_CMPR         0x11500014
DECL|macro|IR_CONFIG_1
mdefine_line|#define IR_CONFIG_1               0x11500020
DECL|macro|IR_SIR_FLAGS
mdefine_line|#define IR_SIR_FLAGS              0x11500024
DECL|macro|IR_ENABLE
mdefine_line|#define IR_ENABLE                 0x11500028
DECL|macro|IR_READ_PHY_CONFIG
mdefine_line|#define IR_READ_PHY_CONFIG        0x1150002C
DECL|macro|IR_WRITE_PHY_CONFIG
mdefine_line|#define IR_WRITE_PHY_CONFIG       0x11500030
DECL|macro|IR_MAX_PKT_LEN
mdefine_line|#define IR_MAX_PKT_LEN            0x11500034
DECL|macro|IR_RX_BYTE_CNT
mdefine_line|#define IR_RX_BYTE_CNT            0x11500038
DECL|macro|IR_CONFIG_2
mdefine_line|#define IR_CONFIG_2               0x1150003C
DECL|macro|IR_INTERFACE_CONFIG
mdefine_line|#define IR_INTERFACE_CONFIG       0x11500040
multiline_comment|/* GPIO */
DECL|macro|TSTATE_STATE_READ
mdefine_line|#define TSTATE_STATE_READ         0x11900100
DECL|macro|TSTATE_STATE_SET
mdefine_line|#define TSTATE_STATE_SET          0x11900100
DECL|macro|OUTPUT_STATE_READ
mdefine_line|#define OUTPUT_STATE_READ         0x11900108
DECL|macro|OUTPUT_STATE_SET
mdefine_line|#define OUTPUT_STATE_SET          0x11900108
DECL|macro|OUTPUT_STATE_CLEAR
mdefine_line|#define OUTPUT_STATE_CLEAR        0x1190010C
DECL|macro|PIN_STATE
mdefine_line|#define PIN_STATE                 0x11900110
multiline_comment|/* Power Management */
DECL|macro|PM_SCRATCH_0
mdefine_line|#define PM_SCRATCH_0                 0x11900018
DECL|macro|PM_SCRATCH_1
mdefine_line|#define PM_SCRATCH_1                 0x1190001C
DECL|macro|PM_WAKEUP_SOURCE_MASK
mdefine_line|#define PM_WAKEUP_SOURCE_MASK        0x11900034
DECL|macro|PM_ENDIANESS
mdefine_line|#define PM_ENDIANESS                 0x11900038
DECL|macro|PM_POWERUP_CONTROL
mdefine_line|#define PM_POWERUP_CONTROL           0x1190003C
DECL|macro|PM_WAKEUP_CAUSE
mdefine_line|#define PM_WAKEUP_CAUSE              0x1190005C
DECL|macro|PM_SLEEP_POWER
mdefine_line|#define PM_SLEEP_POWER               0x11900078
DECL|macro|PM_SLEEP
mdefine_line|#define PM_SLEEP                     0x1190007C
multiline_comment|/* Clock Controller */
DECL|macro|FQ_CNTRL_1
mdefine_line|#define FQ_CNTRL_1                0x11900020
DECL|macro|FQ_CNTRL_2
mdefine_line|#define FQ_CNTRL_2                0x11900024
DECL|macro|CLOCK_SOURCE_CNTRL
mdefine_line|#define CLOCK_SOURCE_CNTRL        0x11900028
DECL|macro|CPU_PLL_CNTRL
mdefine_line|#define CPU_PLL_CNTRL             0x11900060
DECL|macro|AUX_PLL_CNTRL
mdefine_line|#define AUX_PLL_CNTRL             0x11900064
multiline_comment|/* AC97 Controller */
DECL|macro|AC97_CONFIG
mdefine_line|#define AC97_CONFIG               0x10000000
DECL|macro|AC97_STATUS
mdefine_line|#define AC97_STATUS               0x10000004
DECL|macro|AC97_DATA
mdefine_line|#define AC97_DATA                 0x10000008
DECL|macro|AC97_CMD
mdefine_line|#define AC97_CMD                  0x1000000C
DECL|macro|AC97_CNTRL
mdefine_line|#define AC97_CNTRL                0x10000010
macro_line|#endif
eof
