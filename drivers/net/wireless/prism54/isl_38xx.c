multiline_comment|/*  $Header: /var/lib/cvs/prism54-ng/ksrc/isl_38xx.c,v 1.22 2004/02/28 03:06:07 mcgrof Exp $&n; *  &n; *  Copyright (C) 2002 Intersil Americas Inc.&n; *  Copyright (C) 2003-2004 Luis R. Rodriguez &lt;mcgrof@ruslug.rutgers.edu&gt;_&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;isl_38xx.h&quot;
macro_line|#include &lt;linux/firmware.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if !defined(CONFIG_FW_LOADER) &amp;&amp; !defined(CONFIG_FW_LOADER_MODULE)
macro_line|#error No Firmware Loading configured in the kernel !
macro_line|#endif
macro_line|#include &quot;islpci_dev.h&quot;
macro_line|#include &quot;islpci_mgt.h&quot;
multiline_comment|/******************************************************************************&n;    Device Interface &amp; Control functions&n;******************************************************************************/
multiline_comment|/**&n; * isl38xx_disable_interrupts - disable all interrupts&n; * @device: pci memory base address&n; *&n; *  Instructs the device to disable all interrupt reporting by asserting &n; *  the IRQ line. New events may still show up in the interrupt identification&n; *  register located at offset %ISL38XX_INT_IDENT_REG.&n; */
r_void
DECL|function|isl38xx_disable_interrupts
id|isl38xx_disable_interrupts
c_func
(paren
r_void
op_star
id|device
)paren
(brace
id|isl38xx_w32_flush
c_func
(paren
id|device
comma
l_int|0x00000000
comma
id|ISL38XX_INT_EN_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
)brace
r_void
DECL|function|isl38xx_handle_sleep_request
id|isl38xx_handle_sleep_request
c_func
(paren
id|isl38xx_control_block
op_star
id|control_block
comma
r_int
op_star
id|powerstate
comma
r_void
op_star
id|device_base
)paren
(brace
multiline_comment|/* device requests to go into sleep mode&n;&t; * check whether the transmit queues for data and management are empty */
r_if
c_cond
(paren
id|isl38xx_in_queue
c_func
(paren
id|control_block
comma
id|ISL38XX_CB_TX_DATA_LQ
)paren
)paren
multiline_comment|/* data tx queue not empty */
r_return
suffix:semicolon
r_if
c_cond
(paren
id|isl38xx_in_queue
c_func
(paren
id|control_block
comma
id|ISL38XX_CB_TX_MGMTQ
)paren
)paren
multiline_comment|/* management tx queue not empty */
r_return
suffix:semicolon
multiline_comment|/* check also whether received frames are pending */
r_if
c_cond
(paren
id|isl38xx_in_queue
c_func
(paren
id|control_block
comma
id|ISL38XX_CB_RX_DATA_LQ
)paren
)paren
multiline_comment|/* data rx queue not empty */
r_return
suffix:semicolon
r_if
c_cond
(paren
id|isl38xx_in_queue
c_func
(paren
id|control_block
comma
id|ISL38XX_CB_RX_MGMTQ
)paren
)paren
multiline_comment|/* management rx queue not empty */
r_return
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;Device going to sleep mode&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* all queues are empty, allow the device to go into sleep mode */
op_star
id|powerstate
op_assign
id|ISL38XX_PSM_POWERSAVE_STATE
suffix:semicolon
multiline_comment|/* assert the Sleep interrupt in the Device Interrupt Register */
id|isl38xx_w32_flush
c_func
(paren
id|device_base
comma
id|ISL38XX_DEV_INT_SLEEP
comma
id|ISL38XX_DEV_INT_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
)brace
r_void
DECL|function|isl38xx_handle_wakeup
id|isl38xx_handle_wakeup
c_func
(paren
id|isl38xx_control_block
op_star
id|control_block
comma
r_int
op_star
id|powerstate
comma
r_void
op_star
id|device_base
)paren
(brace
multiline_comment|/* device is in active state, update the powerstate flag */
op_star
id|powerstate
op_assign
id|ISL38XX_PSM_ACTIVE_STATE
suffix:semicolon
multiline_comment|/* now check whether there are frames pending for the card */
r_if
c_cond
(paren
op_logical_neg
id|isl38xx_in_queue
c_func
(paren
id|control_block
comma
id|ISL38XX_CB_TX_DATA_LQ
)paren
op_logical_and
op_logical_neg
id|isl38xx_in_queue
c_func
(paren
id|control_block
comma
id|ISL38XX_CB_TX_MGMTQ
)paren
)paren
r_return
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_ANYTHING
comma
l_string|&quot;Wake up handler trigger the device&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* either data or management transmit queue has a frame pending&n;&t; * trigger the device by setting the Update bit in the Device Int reg */
id|isl38xx_w32_flush
c_func
(paren
id|device_base
comma
id|ISL38XX_DEV_INT_UPDATE
comma
id|ISL38XX_DEV_INT_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
)brace
r_void
DECL|function|isl38xx_trigger_device
id|isl38xx_trigger_device
c_func
(paren
r_int
id|asleep
comma
r_void
op_star
id|device_base
)paren
(brace
r_struct
id|timeval
id|current_time
suffix:semicolon
id|u32
id|reg
comma
id|counter
op_assign
l_int|0
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_FUNCTION_CALLS
comma
l_string|&quot;isl38xx trigger device&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* check whether the device is in power save mode */
r_if
c_cond
(paren
id|asleep
)paren
(brace
multiline_comment|/* device is in powersave, trigger the device for wakeup */
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|do_gettimeofday
c_func
(paren
op_amp
id|current_time
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;%08li.%08li Device wakeup triggered&bslash;n&quot;
comma
id|current_time.tv_sec
comma
id|current_time.tv_usec
)paren
suffix:semicolon
macro_line|#endif
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;%08li.%08li Device register read %08x&bslash;n&quot;
comma
id|current_time.tv_sec
comma
id|current_time.tv_usec
comma
id|readl
c_func
(paren
id|device_base
op_plus
id|ISL38XX_CTRL_STAT_REG
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_assign
id|readl
c_func
(paren
id|device_base
op_plus
id|ISL38XX_INT_IDENT_REG
)paren
comma
id|reg
op_eq
l_int|0xabadface
)paren
(brace
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|do_gettimeofday
c_func
(paren
op_amp
id|current_time
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;%08li.%08li Device register abadface&bslash;n&quot;
comma
id|current_time.tv_sec
comma
id|current_time.tv_usec
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* read the Device Status Register until Sleepmode bit is set */
r_while
c_loop
(paren
id|reg
op_assign
id|readl
c_func
(paren
id|device_base
op_plus
id|ISL38XX_CTRL_STAT_REG
)paren
comma
(paren
id|reg
op_amp
id|ISL38XX_CTRL_STAT_SLEEPMODE
)paren
op_eq
l_int|0
)paren
(brace
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
id|counter
op_increment
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;%08li.%08li Device register read %08x&bslash;n&quot;
comma
id|current_time.tv_sec
comma
id|current_time.tv_usec
comma
id|readl
c_func
(paren
id|device_base
op_plus
id|ISL38XX_CTRL_STAT_REG
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|do_gettimeofday
c_func
(paren
op_amp
id|current_time
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;%08li.%08li Device asleep counter %i&bslash;n&quot;
comma
id|current_time.tv_sec
comma
id|current_time.tv_usec
comma
id|counter
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* assert the Wakeup interrupt in the Device Interrupt Register */
id|isl38xx_w32_flush
c_func
(paren
id|device_base
comma
id|ISL38XX_DEV_INT_WAKEUP
comma
id|ISL38XX_DEV_INT_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
multiline_comment|/* perform another read on the Device Status Register */
id|reg
op_assign
id|readl
c_func
(paren
id|device_base
op_plus
id|ISL38XX_CTRL_STAT_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|do_gettimeofday
c_func
(paren
op_amp
id|current_time
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;%08li.%08li Device register read %08x&bslash;n&quot;
comma
id|current_time.tv_sec
comma
id|current_time.tv_usec
comma
id|reg
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
multiline_comment|/* device is (still) awake  */
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;Device is in active state&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* trigger the device by setting the Update bit in the Device Int reg */
id|isl38xx_w32_flush
c_func
(paren
id|device_base
comma
id|ISL38XX_DEV_INT_UPDATE
comma
id|ISL38XX_DEV_INT_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|isl38xx_interface_reset
id|isl38xx_interface_reset
c_func
(paren
r_void
op_star
id|device_base
comma
id|dma_addr_t
id|host_address
)paren
(brace
id|u32
id|reg
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_FUNCTION_CALLS
comma
l_string|&quot;isl38xx_interface_reset &bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* load the address of the control block in the device */
id|isl38xx_w32_flush
c_func
(paren
id|device_base
comma
id|host_address
comma
id|ISL38XX_CTRL_BLK_BASE_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
multiline_comment|/* set the reset bit in the Device Interrupt Register */
id|isl38xx_w32_flush
c_func
(paren
id|device_base
comma
id|ISL38XX_DEV_INT_RESET
comma
id|ISL38XX_DEV_INT_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
multiline_comment|/* enable the interrupt for detecting initialization */
multiline_comment|/* Note: Do not enable other interrupts here. We want the&n;&t; * device to have come up first 100% before allowing any other &n;&t; * interrupts. */
id|reg
op_assign
id|ISL38XX_INT_IDENT_INIT
suffix:semicolon
id|isl38xx_w32_flush
c_func
(paren
id|device_base
comma
id|reg
comma
id|ISL38XX_INT_EN_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
multiline_comment|/* allow complete full reset */
)brace
r_void
DECL|function|isl38xx_enable_common_interrupts
id|isl38xx_enable_common_interrupts
c_func
(paren
r_void
op_star
id|device_base
)paren
(brace
id|u32
id|reg
suffix:semicolon
id|reg
op_assign
(paren
id|ISL38XX_INT_IDENT_UPDATE
op_or
id|ISL38XX_INT_IDENT_SLEEP
op_or
id|ISL38XX_INT_IDENT_WAKEUP
)paren
suffix:semicolon
id|isl38xx_w32_flush
c_func
(paren
id|device_base
comma
id|reg
comma
id|ISL38XX_INT_EN_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
)brace
r_int
DECL|function|isl38xx_upload_firmware
id|isl38xx_upload_firmware
c_func
(paren
r_char
op_star
id|fw_id
comma
id|_REQ_FW_DEV_T
id|dev
comma
r_void
op_star
id|device_base
comma
id|dma_addr_t
id|host_address
)paren
(brace
id|u32
id|reg
comma
id|rc
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_ERROR_MESSAGES
comma
l_string|&quot;isl38xx_upload_firmware(0x%lx, 0x%lx)&bslash;n&quot;
comma
(paren
r_int
)paren
id|device_base
comma
(paren
r_int
)paren
id|host_address
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* clear the RAMBoot and the Reset bit */
id|reg
op_assign
id|readl
c_func
(paren
id|device_base
op_plus
id|ISL38XX_CTRL_STAT_REG
)paren
suffix:semicolon
id|reg
op_and_assign
op_complement
id|ISL38XX_CTRL_STAT_RESET
suffix:semicolon
id|reg
op_and_assign
op_complement
id|ISL38XX_CTRL_STAT_RAMBOOT
suffix:semicolon
id|writel
c_func
(paren
id|reg
comma
id|device_base
op_plus
id|ISL38XX_CTRL_STAT_REG
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
multiline_comment|/* set the Reset bit without reading the register ! */
id|reg
op_or_assign
id|ISL38XX_CTRL_STAT_RESET
suffix:semicolon
id|writel
c_func
(paren
id|reg
comma
id|device_base
op_plus
id|ISL38XX_CTRL_STAT_REG
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
multiline_comment|/* clear the Reset bit */
id|reg
op_and_assign
op_complement
id|ISL38XX_CTRL_STAT_RESET
suffix:semicolon
id|writel
c_func
(paren
id|reg
comma
id|device_base
op_plus
id|ISL38XX_CTRL_STAT_REG
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* wait a while for the device to reboot */
id|mdelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
(brace
r_const
r_struct
id|firmware
op_star
id|fw_entry
op_assign
l_int|0
suffix:semicolon
r_int
id|fw_len
suffix:semicolon
r_const
id|u32
op_star
id|fw_ptr
suffix:semicolon
id|rc
op_assign
id|request_firmware
c_func
(paren
op_amp
id|fw_entry
comma
id|fw_id
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: request_firmware() failed for &squot;%s&squot;&bslash;n&quot;
comma
l_string|&quot;prism54&quot;
comma
id|fw_id
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* prepare the Direct Memory Base register */
id|reg
op_assign
id|ISL38XX_DEV_FIRMWARE_ADDRES
suffix:semicolon
id|fw_ptr
op_assign
(paren
id|u32
op_star
)paren
id|fw_entry-&gt;data
suffix:semicolon
id|fw_len
op_assign
id|fw_entry-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|fw_len
op_mod
l_int|4
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: firmware &squot;%s&squot; size is not multiple of 32bit, aborting!&bslash;n&quot;
comma
l_string|&quot;prism54&quot;
comma
id|fw_id
)paren
suffix:semicolon
id|release_firmware
c_func
(paren
id|fw_entry
)paren
suffix:semicolon
r_return
id|EILSEQ
suffix:semicolon
multiline_comment|/* Illegal byte sequence  */
suffix:semicolon
)brace
r_while
c_loop
(paren
id|fw_len
OG
l_int|0
)paren
(brace
r_int
id|_fw_len
op_assign
(paren
id|fw_len
OG
id|ISL38XX_MEMORY_WINDOW_SIZE
)paren
ques
c_cond
id|ISL38XX_MEMORY_WINDOW_SIZE
suffix:colon
id|fw_len
suffix:semicolon
id|u32
op_star
id|dev_fw_ptr
op_assign
id|device_base
op_plus
id|ISL38XX_DIRECT_MEM_WIN
suffix:semicolon
multiline_comment|/* set the cards base address for writting the data */
id|isl38xx_w32_flush
c_func
(paren
id|device_base
comma
id|reg
comma
id|ISL38XX_DIR_MEM_BASE_REG
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* be paranoid */
multiline_comment|/* increment the write address for next iteration */
id|reg
op_add_assign
id|_fw_len
suffix:semicolon
id|fw_len
op_sub_assign
id|_fw_len
suffix:semicolon
multiline_comment|/* write the data to the Direct Memory Window 32bit-wise */
multiline_comment|/* memcpy_toio() doesn&squot;t guarantee 32bit writes :-| */
r_while
c_loop
(paren
id|_fw_len
OG
l_int|0
)paren
(brace
multiline_comment|/* use non-swapping writel() */
id|__raw_writel
c_func
(paren
op_star
id|fw_ptr
comma
id|dev_fw_ptr
)paren
suffix:semicolon
id|fw_ptr
op_increment
comma
id|dev_fw_ptr
op_increment
suffix:semicolon
id|_fw_len
op_sub_assign
l_int|4
suffix:semicolon
)brace
multiline_comment|/* flush PCI posting */
(paren
r_void
)paren
id|readl
c_func
(paren
id|device_base
op_plus
id|ISL38XX_PCI_POSTING_FLUSH
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* be paranoid again */
id|BUG_ON
c_func
(paren
id|_fw_len
op_ne
l_int|0
)paren
suffix:semicolon
)brace
id|BUG_ON
c_func
(paren
id|fw_len
op_ne
l_int|0
)paren
suffix:semicolon
id|release_firmware
c_func
(paren
id|fw_entry
)paren
suffix:semicolon
)brace
multiline_comment|/* now reset the device&n;&t; * clear the Reset &amp; ClkRun bit, set the RAMBoot bit */
id|reg
op_assign
id|readl
c_func
(paren
id|device_base
op_plus
id|ISL38XX_CTRL_STAT_REG
)paren
suffix:semicolon
id|reg
op_and_assign
op_complement
id|ISL38XX_CTRL_STAT_CLKRUN
suffix:semicolon
id|reg
op_and_assign
op_complement
id|ISL38XX_CTRL_STAT_RESET
suffix:semicolon
id|reg
op_or_assign
id|ISL38XX_CTRL_STAT_RAMBOOT
suffix:semicolon
id|isl38xx_w32_flush
c_func
(paren
id|device_base
comma
id|reg
comma
id|ISL38XX_CTRL_STAT_REG
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
multiline_comment|/* set the reset bit latches the host override and RAMBoot bits&n;&t; * into the device for operation when the reset bit is reset */
id|reg
op_or_assign
id|ISL38XX_CTRL_STAT_RESET
suffix:semicolon
id|writel
c_func
(paren
id|reg
comma
id|device_base
op_plus
id|ISL38XX_CTRL_STAT_REG
)paren
suffix:semicolon
multiline_comment|/* don&squot;t do flush PCI posting here! */
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
multiline_comment|/* clear the reset bit should start the whole circus */
id|reg
op_and_assign
op_complement
id|ISL38XX_CTRL_STAT_RESET
suffix:semicolon
id|writel
c_func
(paren
id|reg
comma
id|device_base
op_plus
id|ISL38XX_CTRL_STAT_REG
)paren
suffix:semicolon
multiline_comment|/* don&squot;t do flush PCI posting here! */
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|isl38xx_in_queue
id|isl38xx_in_queue
c_func
(paren
id|isl38xx_control_block
op_star
id|cb
comma
r_int
id|queue
)paren
(brace
r_const
id|s32
id|delta
op_assign
(paren
id|le32_to_cpu
c_func
(paren
id|cb-&gt;driver_curr_frag
(braket
id|queue
)braket
)paren
op_minus
id|le32_to_cpu
c_func
(paren
id|cb-&gt;device_curr_frag
(braket
id|queue
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* determine the amount of fragments in the queue depending on the type&n;&t; * of the queue, either transmit or receive */
id|BUG_ON
c_func
(paren
id|delta
OL
l_int|0
)paren
suffix:semicolon
multiline_comment|/* driver ptr must be ahead of device ptr */
r_switch
c_cond
(paren
id|queue
)paren
(brace
multiline_comment|/* send queues */
r_case
id|ISL38XX_CB_TX_MGMTQ
suffix:colon
id|BUG_ON
c_func
(paren
id|delta
OG
id|ISL38XX_CB_MGMT_QSIZE
)paren
suffix:semicolon
r_case
id|ISL38XX_CB_TX_DATA_LQ
suffix:colon
r_case
id|ISL38XX_CB_TX_DATA_HQ
suffix:colon
id|BUG_ON
c_func
(paren
id|delta
OG
id|ISL38XX_CB_TX_QSIZE
)paren
suffix:semicolon
r_return
id|delta
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* receive queues */
r_case
id|ISL38XX_CB_RX_MGMTQ
suffix:colon
id|BUG_ON
c_func
(paren
id|delta
OG
id|ISL38XX_CB_MGMT_QSIZE
)paren
suffix:semicolon
r_return
id|ISL38XX_CB_MGMT_QSIZE
op_minus
id|delta
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ISL38XX_CB_RX_DATA_LQ
suffix:colon
r_case
id|ISL38XX_CB_RX_DATA_HQ
suffix:colon
id|BUG_ON
c_func
(paren
id|delta
OG
id|ISL38XX_CB_RX_QSIZE
)paren
suffix:semicolon
r_return
id|ISL38XX_CB_RX_QSIZE
op_minus
id|delta
suffix:semicolon
r_break
suffix:semicolon
)brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
