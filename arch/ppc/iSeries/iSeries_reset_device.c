multiline_comment|/************************************************************************/
multiline_comment|/* File iSeries_reset_device.c created by Allan Trautman on Mar 21 2001.*/
multiline_comment|/************************************************************************/
multiline_comment|/* This code supports the pci interface on the IBM iSeries systems.     */
multiline_comment|/* Copyright (C) 20yy  &lt;Allan H Trautman&gt; &lt;IBM Corp&gt;                    */
multiline_comment|/*                                                                      */
multiline_comment|/* This program is free software; you can redistribute it and/or modify */
multiline_comment|/* it under the terms of the GNU General Public License as published by */
multiline_comment|/* the Free Software Foundation; either version 2 of the License, or    */
multiline_comment|/* (at your option) any later version.                                  */
multiline_comment|/*                                                                      */
multiline_comment|/* This program is distributed in the hope that it will be useful,      */
multiline_comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
multiline_comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
multiline_comment|/* GNU General Public License for more details.                         */
multiline_comment|/*                                                                      */
multiline_comment|/* You should have received a copy of the GNU General Public License    */
multiline_comment|/* along with this program; if not, write to the:                       */
multiline_comment|/* Free Software Foundation, Inc.,                                      */
multiline_comment|/* 59 Temple Place, Suite 330,                                          */
multiline_comment|/* Boston, MA  02111-1307  USA                                          */
multiline_comment|/************************************************************************/
multiline_comment|/* Change Activity:                                                     */
multiline_comment|/*   Created, March 20, 2001                                            */
multiline_comment|/*   April 30, 2001, Added return codes on functions.                   */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
multiline_comment|/************************************************************************/
multiline_comment|/* Arch specific&squot;s                                                      */
multiline_comment|/************************************************************************/
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#include &lt;asm/iSeries/mf.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_FlightRecorder.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_pci.h&gt;
macro_line|#include &quot;iSeries_pci.h&quot;
multiline_comment|/************************************************************************/
multiline_comment|/* Interface to Reset Device, see .h for parms and flavors.             */
multiline_comment|/************************************************************************/
DECL|function|iSeries_Device_Reset_NoIrq
r_int
id|iSeries_Device_Reset_NoIrq
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
)paren
(brace
r_return
id|iSeries_Device_Reset
c_func
(paren
id|PciDev
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|iSeries_Device_Reset_Generic
r_int
id|iSeries_Device_Reset_Generic
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
)paren
(brace
r_return
id|iSeries_Device_Reset
c_func
(paren
id|PciDev
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|iSeries_Device_Reset
r_int
id|iSeries_Device_Reset
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
comma
r_int
id|AssertTime
comma
r_int
id|DelayTime
comma
r_int
id|IrqState
)paren
(brace
r_int
id|RCode
op_assign
l_int|0
suffix:semicolon
id|PciReqsSaveArea
op_star
id|RegSaveArea
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|PciDev
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|IrqState
op_eq
l_int|0
)paren
(brace
id|disable_irq
c_func
(paren
id|PciDev-&gt;irq
)paren
suffix:semicolon
)brace
id|RegSaveArea
op_assign
id|iSeries_Device_SaveConfigRegs
c_func
(paren
id|PciDev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|RegSaveArea
op_ne
l_int|NULL
)paren
(brace
id|RCode
op_assign
id|iSeries_Device_ToggleReset
c_func
(paren
id|PciDev
comma
id|AssertTime
comma
id|DelayTime
)paren
suffix:semicolon
r_if
c_cond
(paren
id|RCode
op_eq
l_int|0
)paren
(brace
id|RCode
op_assign
id|iSeries_Device_RestoreConfigRegs
c_func
(paren
id|RegSaveArea
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|RCode
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IrqState
op_eq
l_int|0
)paren
(brace
id|enable_irq
c_func
(paren
id|PciDev-&gt;irq
)paren
suffix:semicolon
)brace
)brace
r_return
id|RCode
suffix:semicolon
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Interface to toggle the reset line                                   */
multiline_comment|/* Time is in .1 seconds, need for seconds.                             */
multiline_comment|/************************************************************************/
DECL|function|iSeries_Device_ToggleReset
r_int
id|iSeries_Device_ToggleReset
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
comma
r_int
id|AssertTime
comma
r_int
id|DelayTime
)paren
(brace
r_int
r_int
id|AssertDelay
op_assign
id|AssertTime
suffix:semicolon
r_int
r_int
id|WaitDelay
op_assign
id|DelayTime
suffix:semicolon
id|u16
id|Bus
op_assign
id|ISERIES_GET_LPAR_BUS
c_func
(paren
id|PciDev-&gt;bus-&gt;number
)paren
suffix:semicolon
id|u8
id|Slot
op_assign
id|ISERIES_DECODE_DEVICE
c_func
(paren
id|PciDev-&gt;devfn
)paren
suffix:semicolon
r_int
id|RCode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set defaults                                                     */
r_if
c_cond
(paren
id|AssertTime
OL
l_int|5
)paren
(brace
id|AssertDelay
op_assign
l_int|5
suffix:semicolon
)brace
multiline_comment|/* Default is .5 second  */
r_if
c_cond
(paren
id|WaitDelay
OL
l_int|30
)paren
(brace
id|WaitDelay
op_assign
l_int|30
suffix:semicolon
)brace
multiline_comment|/* Default is 3 seconds  */
multiline_comment|/* Assert reset for time specified                                  */
id|AssertDelay
op_mul_assign
id|HZ
suffix:semicolon
multiline_comment|/* Convert to ticks.      */
id|AssertDelay
op_div_assign
l_int|10
suffix:semicolon
multiline_comment|/* Adjust to whole count  */
id|RCode
op_assign
id|HvCallPci_setSlotReset
c_func
(paren
id|Bus
comma
l_int|0x00
comma
id|Slot
comma
l_int|1
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
multiline_comment|/* Only Wait.             */
id|schedule_timeout
c_func
(paren
id|AssertDelay
)paren
suffix:semicolon
multiline_comment|/* Sleep for the time     */
id|RCode
op_add_assign
id|HvCallPci_setSlotReset
c_func
(paren
id|Bus
comma
l_int|0x00
comma
id|Slot
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Wait for device to reset                                         */
id|WaitDelay
op_mul_assign
id|HZ
suffix:semicolon
multiline_comment|/* Ticks                  */
id|WaitDelay
op_div_assign
l_int|10
suffix:semicolon
multiline_comment|/* Whole count            */
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
multiline_comment|/* Only Wait.             */
id|schedule_timeout
c_func
(paren
id|WaitDelay
)paren
suffix:semicolon
multiline_comment|/* Sleep for the time     */
r_if
c_cond
(paren
id|RCode
op_eq
l_int|0
)paren
(brace
id|sprintf
c_func
(paren
id|PciFrBuffer
comma
l_string|&quot;Slot Reset on Bus%3d, Device%3d!&bslash;n&quot;
comma
id|Bus
comma
id|Slot
)paren
suffix:semicolon
)brace
r_else
(brace
id|sprintf
c_func
(paren
id|PciFrBuffer
comma
l_string|&quot;Slot Reset on Bus%3d, Device%3d Failed!  RCode: %04X&bslash;n&quot;
comma
id|Bus
comma
id|Slot
comma
id|RCode
)paren
suffix:semicolon
)brace
id|ISERIES_PCI_FR_TIME
c_func
(paren
id|PciFrBuffer
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: %s&bslash;n&quot;
comma
id|PciFrBuffer
)paren
suffix:semicolon
r_return
id|RCode
suffix:semicolon
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Allocates space and save the config registers for a device.          */
multiline_comment|/************************************************************************/
multiline_comment|/* Note: This does byte reads so the data may appear byte swapped       */
multiline_comment|/* when compared to read word or dword.                                 */
multiline_comment|/* The data returned is a structure and will be freed automatically on  */
multiline_comment|/* the restore of the data.  The is checking so if the save fails, the  */
multiline_comment|/* data will not be restore.  Yes I know, you are most likey toast.     */
multiline_comment|/************************************************************************/
DECL|function|iSeries_Device_SaveConfigRegs
id|PciReqsSaveArea
op_star
id|iSeries_Device_SaveConfigRegs
c_func
(paren
r_struct
id|pci_dev
op_star
id|DevPtr
)paren
(brace
r_int
id|Register
op_assign
l_int|0
suffix:semicolon
r_struct
id|pci_dev
op_star
id|PciDev
op_assign
id|DevPtr
suffix:semicolon
id|PciReqsSaveArea
op_star
id|RegSaveArea
op_assign
(paren
id|PciReqsSaveArea
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|PciReqsSaveArea
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/*printk(&quot;PCI: Save Configuration Registers. 0x%08X&bslash;n&quot;,(int)RegSaveArea); */
r_if
c_cond
(paren
id|RegSaveArea
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Allocation failure in Save Configuration Registers.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/********************************************************************/
multiline_comment|/* Initialize Area.                                                 */
multiline_comment|/********************************************************************/
r_else
(brace
id|RegSaveArea-&gt;PciDev
op_assign
id|DevPtr
suffix:semicolon
id|RegSaveArea-&gt;Flags
op_assign
l_int|0x01
suffix:semicolon
id|RegSaveArea-&gt;ByteCount
op_assign
id|PCI_MAX_LAT
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Number of Bytes  */
id|RegSaveArea-&gt;RCode
op_assign
l_int|0
suffix:semicolon
id|RegSaveArea-&gt;FailReg
op_assign
l_int|0
suffix:semicolon
multiline_comment|/****************************************************************/
multiline_comment|/* Save All the Regs,  NOTE: restore skips the first 16 bytes.  */
multiline_comment|/****************************************************************/
r_for
c_loop
(paren
id|Register
op_assign
l_int|0
suffix:semicolon
id|Register
OL
id|RegSaveArea-&gt;ByteCount
op_logical_and
id|RegSaveArea-&gt;RCode
op_eq
l_int|0
suffix:semicolon
op_increment
id|Register
)paren
(brace
id|RegSaveArea-&gt;RCode
op_assign
id|pci_read_config_byte
c_func
(paren
id|PciDev
comma
id|Register
comma
op_amp
id|RegSaveArea-&gt;Regs
(braket
id|Register
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Check for error during the save.                             */
r_if
c_cond
(paren
id|RegSaveArea-&gt;RCode
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: I/O Failure in Save Configuration Registers. 0x%02X, 0x%04X&bslash;n&quot;
comma
id|Register
comma
id|RegSaveArea-&gt;RCode
)paren
suffix:semicolon
id|RegSaveArea-&gt;Flags
op_or_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* Ouch Flag.           */
id|RegSaveArea-&gt;FailReg
op_assign
id|Register
suffix:semicolon
multiline_comment|/* Stuff this way       */
)brace
)brace
r_return
id|RegSaveArea
suffix:semicolon
)brace
multiline_comment|/************************************************************************/
multiline_comment|/* Restores the registers saved via the save function.  See the save    */
multiline_comment|/* function for details.                                                */
multiline_comment|/************************************************************************/
DECL|function|iSeries_Device_RestoreConfigRegs
r_int
id|iSeries_Device_RestoreConfigRegs
c_func
(paren
id|PciReqsSaveArea
op_star
id|SaveArea
)paren
(brace
r_int
id|RCode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|SaveArea
op_eq
l_int|0
op_logical_or
id|SaveArea-&gt;PciDev
op_eq
l_int|0
op_logical_or
(paren
id|SaveArea-&gt;Flags
op_amp
l_int|0x80
)paren
op_eq
l_int|0x80
op_logical_or
id|SaveArea-&gt;RCode
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Invalid SaveArea passed to Restore Configuration Registers. 0x%08X&bslash;n&quot;
comma
(paren
r_int
)paren
id|SaveArea
)paren
suffix:semicolon
id|RCode
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_int
id|Register
suffix:semicolon
r_struct
id|pci_dev
op_star
id|PciDev
op_assign
id|SaveArea-&gt;PciDev
suffix:semicolon
multiline_comment|/***************************************************************/
multiline_comment|/* Don&squot;t touch the Cmd or BIST regs, user must restore those.  */
multiline_comment|/* Restore PCI_CACHE_LINE_SIZE &amp; PCI_LATENCY_TIMER             */
multiline_comment|/* Restore Saved Regs from 0x10 to 0x3F                        */
multiline_comment|/***************************************************************/
id|pci_write_config_byte
c_func
(paren
id|PciDev
comma
id|PCI_CACHE_LINE_SIZE
comma
id|SaveArea-&gt;Regs
(braket
id|PCI_CACHE_LINE_SIZE
)braket
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|PciDev
comma
id|PCI_LATENCY_TIMER
comma
id|SaveArea-&gt;Regs
(braket
id|PCI_LATENCY_TIMER
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|Register
op_assign
id|PCI_BASE_ADDRESS_0
suffix:semicolon
id|Register
OL
id|SaveArea-&gt;ByteCount
op_logical_and
id|SaveArea-&gt;RCode
op_eq
l_int|0
suffix:semicolon
op_increment
id|Register
)paren
(brace
id|SaveArea-&gt;RCode
op_assign
id|pci_write_config_byte
c_func
(paren
id|PciDev
comma
id|Register
comma
id|SaveArea-&gt;Regs
(braket
id|Register
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|SaveArea-&gt;RCode
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: I/O Failure in Restore Configuration Registers %d, %02X&bslash;n&quot;
comma
id|Register
comma
id|SaveArea-&gt;RCode
)paren
suffix:semicolon
id|SaveArea-&gt;FailReg
op_assign
id|Register
suffix:semicolon
id|RCode
op_assign
id|SaveArea-&gt;RCode
suffix:semicolon
)brace
r_else
(brace
id|RCode
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/***************************************************************/
multiline_comment|/* Is the Auto Free Flag on                                    */
multiline_comment|/***************************************************************/
r_if
c_cond
(paren
id|SaveArea-&gt;Flags
op_logical_and
l_int|0x01
op_eq
l_int|0x01
)paren
(brace
multiline_comment|/* printk(&quot;PCI: Auto Free Register Save Area.  0x%08X&bslash;n&quot;,(int)SaveArea); */
id|kfree
c_func
(paren
id|SaveArea
)paren
suffix:semicolon
)brace
)brace
r_return
id|RCode
suffix:semicolon
)brace
eof