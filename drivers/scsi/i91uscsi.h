multiline_comment|/**************************************************************************&n; * Initio 9100 device driver for Linux.&n; *&n; * Copyright (c) 1994-1998 Initio Corporation&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * --------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification, immediately at the beginning of the file.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; * 3. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; **************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|ULONG
mdefine_line|#define ULONG   unsigned long
DECL|macro|USHORT
mdefine_line|#define USHORT  unsigned short
DECL|macro|UCHAR
mdefine_line|#define UCHAR   unsigned char
DECL|macro|BYTE
mdefine_line|#define BYTE    unsigned char
DECL|macro|WORD
mdefine_line|#define WORD    unsigned short
DECL|macro|DWORD
mdefine_line|#define DWORD   unsigned long
DECL|macro|UBYTE
mdefine_line|#define UBYTE   unsigned char
DECL|macro|UWORD
mdefine_line|#define UWORD   unsigned short
DECL|macro|UDWORD
mdefine_line|#define UDWORD  unsigned long
macro_line|#ifdef ALPHA
DECL|macro|U32
mdefine_line|#define U32     unsigned int
macro_line|#else
DECL|macro|U32
mdefine_line|#define U32     unsigned long
macro_line|#endif
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL     0&t;&t;/* zero          */
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE     (1)&t;&t;/* boolean true  */
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE    (0)&t;&t;/* boolean false */
macro_line|#endif
macro_line|#ifndef FAILURE
DECL|macro|FAILURE
mdefine_line|#define FAILURE  (-1)
macro_line|#endif
DECL|macro|TOTAL_SG_ENTRY
mdefine_line|#define TOTAL_SG_ENTRY&t;&t;32
DECL|macro|MAX_SUPPORTED_ADAPTERS
mdefine_line|#define MAX_SUPPORTED_ADAPTERS  8
DECL|macro|MAX_OFFSET
mdefine_line|#define MAX_OFFSET&t;&t;15
DECL|macro|MAX_TARGETS
mdefine_line|#define MAX_TARGETS&t;&t;16
DECL|macro|INI_VENDOR_ID
mdefine_line|#define INI_VENDOR_ID   0x1101&t;/* Initio&squot;s PCI vendor ID       */
DECL|macro|I950_DEVICE_ID
mdefine_line|#define I950_DEVICE_ID&t;0x9500&t;/* Initio&squot;s inic-950 product ID   */
DECL|macro|I940_DEVICE_ID
mdefine_line|#define I940_DEVICE_ID&t;0x9400&t;/* Initio&squot;s inic-940 product ID   */
DECL|macro|I935_DEVICE_ID
mdefine_line|#define I935_DEVICE_ID&t;0x9401&t;/* Initio&squot;s inic-935 product ID   */
DECL|macro|_I91USCSI_H
mdefine_line|#define&t;_I91USCSI_H
r_typedef
r_struct
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|vec
r_int
r_int
id|vec
suffix:semicolon
DECL|typedef|i91u_config
)brace
id|i91u_config
suffix:semicolon
multiline_comment|/***************************************/
multiline_comment|/*  Tulip Configuration Register Set */
multiline_comment|/***************************************/
DECL|macro|TUL_PVID
mdefine_line|#define TUL_PVID        0x00&t;/* Vendor ID                    */
DECL|macro|TUL_PDID
mdefine_line|#define TUL_PDID        0x02&t;/* Device ID                    */
DECL|macro|TUL_PCMD
mdefine_line|#define TUL_PCMD        0x04&t;/* Command                      */
DECL|macro|TUL_PSTUS
mdefine_line|#define TUL_PSTUS       0x06&t;/* Status                       */
DECL|macro|TUL_PRID
mdefine_line|#define TUL_PRID        0x08&t;/* Revision number              */
DECL|macro|TUL_PPI
mdefine_line|#define TUL_PPI         0x09&t;/* Programming interface        */
DECL|macro|TUL_PSC
mdefine_line|#define TUL_PSC         0x0A&t;/* Sub Class                    */
DECL|macro|TUL_PBC
mdefine_line|#define TUL_PBC         0x0B&t;/* Base Class                   */
DECL|macro|TUL_PCLS
mdefine_line|#define TUL_PCLS        0x0C&t;/* Cache line size              */
DECL|macro|TUL_PLTR
mdefine_line|#define TUL_PLTR        0x0D&t;/* Latency timer                */
DECL|macro|TUL_PHDT
mdefine_line|#define TUL_PHDT        0x0E&t;/* Header type                  */
DECL|macro|TUL_PBIST
mdefine_line|#define TUL_PBIST       0x0F&t;/* BIST                         */
DECL|macro|TUL_PBAD
mdefine_line|#define TUL_PBAD        0x10&t;/* Base address                 */
DECL|macro|TUL_PBAD1
mdefine_line|#define TUL_PBAD1       0x14&t;/* Base address                 */
DECL|macro|TUL_PBAD2
mdefine_line|#define TUL_PBAD2       0x18&t;/* Base address                 */
DECL|macro|TUL_PBAD3
mdefine_line|#define TUL_PBAD3       0x1C&t;/* Base address                 */
DECL|macro|TUL_PBAD4
mdefine_line|#define TUL_PBAD4       0x20&t;/* Base address                 */
DECL|macro|TUL_PBAD5
mdefine_line|#define TUL_PBAD5       0x24&t;/* Base address                 */
DECL|macro|TUL_PRSVD
mdefine_line|#define TUL_PRSVD       0x28&t;/* Reserved                     */
DECL|macro|TUL_PRSVD1
mdefine_line|#define TUL_PRSVD1      0x2C&t;/* Reserved                     */
DECL|macro|TUL_PRAD
mdefine_line|#define TUL_PRAD        0x30&t;/* Expansion ROM base address   */
DECL|macro|TUL_PRSVD2
mdefine_line|#define TUL_PRSVD2      0x34&t;/* Reserved                     */
DECL|macro|TUL_PRSVD3
mdefine_line|#define TUL_PRSVD3      0x38&t;/* Reserved                     */
DECL|macro|TUL_PINTL
mdefine_line|#define TUL_PINTL       0x3C&t;/* Interrupt line               */
DECL|macro|TUL_PINTP
mdefine_line|#define TUL_PINTP       0x3D&t;/* Interrupt pin                */
DECL|macro|TUL_PIGNT
mdefine_line|#define TUL_PIGNT       0x3E&t;/* MIN_GNT                      */
DECL|macro|TUL_PMGNT
mdefine_line|#define TUL_PMGNT       0x3F&t;/* MAX_GNT                      */
multiline_comment|/************************/
multiline_comment|/*  Jasmin Register Set */
multiline_comment|/************************/
DECL|macro|TUL_HACFG0
mdefine_line|#define TUL_HACFG0      0x40&t;/* H/A Configuration Register 0         */
DECL|macro|TUL_HACFG1
mdefine_line|#define TUL_HACFG1      0x41&t;/* H/A Configuration Register 1         */
DECL|macro|TUL_HACFG2
mdefine_line|#define TUL_HACFG2      0x42&t;/* H/A Configuration Register 2         */
DECL|macro|TUL_SDCFG0
mdefine_line|#define TUL_SDCFG0      0x44&t;/* SCSI Device Configuration 0          */
DECL|macro|TUL_SDCFG1
mdefine_line|#define TUL_SDCFG1      0x45&t;/* SCSI Device Configuration 1          */
DECL|macro|TUL_SDCFG2
mdefine_line|#define TUL_SDCFG2      0x46&t;/* SCSI Device Configuration 2          */
DECL|macro|TUL_SDCFG3
mdefine_line|#define TUL_SDCFG3      0x47&t;/* SCSI Device Configuration 3          */
DECL|macro|TUL_GINTS
mdefine_line|#define TUL_GINTS       0x50&t;/* Global Interrupt Status Register     */
DECL|macro|TUL_GIMSK
mdefine_line|#define TUL_GIMSK       0x52&t;/* Global Interrupt MASK Register       */
DECL|macro|TUL_GCTRL
mdefine_line|#define TUL_GCTRL       0x54&t;/* Global Control Register              */
DECL|macro|TUL_GCTRL_EEPROM_BIT
mdefine_line|#define TUL_GCTRL_EEPROM_BIT    0x04
DECL|macro|TUL_GCTRL1
mdefine_line|#define TUL_GCTRL1      0x55&t;/* Global Control Register              */
DECL|macro|TUL_DMACFG
mdefine_line|#define TUL_DMACFG      0x5B&t;/* DMA configuration                    */
DECL|macro|TUL_NVRAM
mdefine_line|#define TUL_NVRAM       0x5D&t;/* Non-volatile RAM port                */
DECL|macro|TUL_SCnt0
mdefine_line|#define TUL_SCnt0       0x80&t;/* 00 R/W Transfer Counter Low          */
DECL|macro|TUL_SCnt1
mdefine_line|#define TUL_SCnt1       0x81&t;/* 01 R/W Transfer Counter Mid          */
DECL|macro|TUL_SCnt2
mdefine_line|#define TUL_SCnt2       0x82&t;/* 02 R/W Transfer Count High           */
DECL|macro|TUL_SFifoCnt
mdefine_line|#define TUL_SFifoCnt    0x83&t;/* 03 R   FIFO counter                  */
DECL|macro|TUL_SIntEnable
mdefine_line|#define TUL_SIntEnable  0x84&t;/* 03 W   Interrupt enble               */
DECL|macro|TUL_SInt
mdefine_line|#define TUL_SInt        0x84&t;/* 04 R   Interrupt Register            */
DECL|macro|TUL_SCtrl0
mdefine_line|#define TUL_SCtrl0      0x85&t;/* 05 W   Control 0                     */
DECL|macro|TUL_SStatus0
mdefine_line|#define TUL_SStatus0    0x85&t;/* 05 R   Status 0                      */
DECL|macro|TUL_SCtrl1
mdefine_line|#define TUL_SCtrl1      0x86&t;/* 06 W   Control 1                     */
DECL|macro|TUL_SStatus1
mdefine_line|#define TUL_SStatus1    0x86&t;/* 06 R   Status 1                      */
DECL|macro|TUL_SConfig
mdefine_line|#define TUL_SConfig     0x87&t;/* 07 W   Configuration                 */
DECL|macro|TUL_SStatus2
mdefine_line|#define TUL_SStatus2    0x87&t;/* 07 R   Status 2                      */
DECL|macro|TUL_SPeriod
mdefine_line|#define TUL_SPeriod     0x88&t;/* 08 W   Sync. Transfer Period &amp; Offset */
DECL|macro|TUL_SOffset
mdefine_line|#define TUL_SOffset     0x88&t;/* 08 R   Offset                        */
DECL|macro|TUL_SScsiId
mdefine_line|#define TUL_SScsiId     0x89&t;/* 09 W   SCSI ID                       */
DECL|macro|TUL_SBusId
mdefine_line|#define TUL_SBusId      0x89&t;/* 09 R   SCSI BUS ID                   */
DECL|macro|TUL_STimeOut
mdefine_line|#define TUL_STimeOut    0x8A&t;/* 0A W   Sel/Resel Time Out Register   */
DECL|macro|TUL_SIdent
mdefine_line|#define TUL_SIdent      0x8A&t;/* 0A R   Identify Message Register     */
DECL|macro|TUL_SAvail
mdefine_line|#define TUL_SAvail      0x8A&t;/* 0A R   Availiable Counter Register   */
DECL|macro|TUL_SData
mdefine_line|#define TUL_SData       0x8B&t;/* 0B R/W SCSI data in/out              */
DECL|macro|TUL_SFifo
mdefine_line|#define TUL_SFifo       0x8C&t;/* 0C R/W FIFO                          */
DECL|macro|TUL_SSignal
mdefine_line|#define TUL_SSignal     0x90&t;/* 10 R/W SCSI signal in/out            */
DECL|macro|TUL_SCmd
mdefine_line|#define TUL_SCmd        0x91&t;/* 11 R/W Command                       */
DECL|macro|TUL_STest0
mdefine_line|#define TUL_STest0      0x92&t;/* 12 R/W Test0                         */
DECL|macro|TUL_STest1
mdefine_line|#define TUL_STest1      0x93&t;/* 13 R/W Test1                         */
DECL|macro|TUL_SCFG1
mdefine_line|#define TUL_SCFG1&t;0x94&t;/* 14 R/W Configuration                 */
DECL|macro|TUL_XAddH
mdefine_line|#define TUL_XAddH       0xC0&t;/*DMA Transfer Physical Address         */
DECL|macro|TUL_XAddW
mdefine_line|#define TUL_XAddW       0xC8&t;/*DMA Current Transfer Physical Address */
DECL|macro|TUL_XCntH
mdefine_line|#define TUL_XCntH       0xD0&t;/*DMA Transfer Counter                  */
DECL|macro|TUL_XCntW
mdefine_line|#define TUL_XCntW       0xD4&t;/*DMA Current Transfer Counter          */
DECL|macro|TUL_XCmd
mdefine_line|#define TUL_XCmd        0xD8&t;/*DMA Command Register                  */
DECL|macro|TUL_Int
mdefine_line|#define TUL_Int         0xDC&t;/*Interrupt Register                    */
DECL|macro|TUL_XStatus
mdefine_line|#define TUL_XStatus     0xDD&t;/*DMA status Register                   */
DECL|macro|TUL_Mask
mdefine_line|#define TUL_Mask        0xE0&t;/*Interrupt Mask Register               */
DECL|macro|TUL_XCtrl
mdefine_line|#define TUL_XCtrl       0xE4&t;/*DMA Control Register                  */
DECL|macro|TUL_XCtrl1
mdefine_line|#define TUL_XCtrl1      0xE5&t;/*DMA Control Register 1                */
DECL|macro|TUL_XFifo
mdefine_line|#define TUL_XFifo       0xE8&t;/*DMA FIFO                              */
DECL|macro|TUL_WCtrl
mdefine_line|#define TUL_WCtrl       0xF7&t;/*Bus master wait state control         */
DECL|macro|TUL_DCtrl
mdefine_line|#define TUL_DCtrl       0xFB&t;/*DMA delay control                     */
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/*   bit definition for Command register of Configuration Space Header  */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|BUSMS
mdefine_line|#define BUSMS           0x04&t;/* BUS MASTER Enable                    */
DECL|macro|IOSPA
mdefine_line|#define IOSPA           0x01&t;/* IO Space Enable                      */
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* Command Codes of Tulip SCSI Command register                         */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|TSC_EN_RESEL
mdefine_line|#define TSC_EN_RESEL    0x80&t;/* Enable Reselection                   */
DECL|macro|TSC_CMD_COMP
mdefine_line|#define TSC_CMD_COMP    0x84&t;/* Command Complete Sequence            */
DECL|macro|TSC_SEL
mdefine_line|#define TSC_SEL         0x01&t;/* Select Without ATN Sequence          */
DECL|macro|TSC_SEL_ATN
mdefine_line|#define TSC_SEL_ATN     0x11&t;/* Select With ATN Sequence             */
DECL|macro|TSC_SEL_ATN_DMA
mdefine_line|#define TSC_SEL_ATN_DMA 0x51&t;/* Select With ATN Sequence with DMA    */
DECL|macro|TSC_SEL_ATN3
mdefine_line|#define TSC_SEL_ATN3    0x31&t;/* Select With ATN3 Sequence            */
DECL|macro|TSC_SEL_ATNSTOP
mdefine_line|#define TSC_SEL_ATNSTOP 0x12&t;/* Select With ATN and Stop Sequence    */
DECL|macro|TSC_SELATNSTOP
mdefine_line|#define TSC_SELATNSTOP  0x1E&t;/* Select With ATN and Stop Sequence    */
DECL|macro|TSC_SEL_ATN_DIRECT_IN
mdefine_line|#define TSC_SEL_ATN_DIRECT_IN   0x95&t;/* Select With ATN Sequence     */
DECL|macro|TSC_SEL_ATN_DIRECT_OUT
mdefine_line|#define TSC_SEL_ATN_DIRECT_OUT  0x15&t;/* Select With ATN Sequence     */
DECL|macro|TSC_SEL_ATN3_DIRECT_IN
mdefine_line|#define TSC_SEL_ATN3_DIRECT_IN  0xB5&t;/* Select With ATN3 Sequence    */
DECL|macro|TSC_SEL_ATN3_DIRECT_OUT
mdefine_line|#define TSC_SEL_ATN3_DIRECT_OUT 0x35&t;/* Select With ATN3 Sequence    */
DECL|macro|TSC_XF_DMA_OUT_DIRECT
mdefine_line|#define TSC_XF_DMA_OUT_DIRECT   0x06&t;/* DMA Xfer Infomation out      */
DECL|macro|TSC_XF_DMA_IN_DIRECT
mdefine_line|#define TSC_XF_DMA_IN_DIRECT    0x86&t;/* DMA Xfer Infomation in       */
DECL|macro|TSC_XF_DMA_OUT
mdefine_line|#define TSC_XF_DMA_OUT  0x43&t;/* DMA Xfer Infomation out              */
DECL|macro|TSC_XF_DMA_IN
mdefine_line|#define TSC_XF_DMA_IN   0xC3&t;/* DMA Xfer Infomation in               */
DECL|macro|TSC_XF_FIFO_OUT
mdefine_line|#define TSC_XF_FIFO_OUT 0x03&t;/* FIFO Xfer Infomation out             */
DECL|macro|TSC_XF_FIFO_IN
mdefine_line|#define TSC_XF_FIFO_IN  0x83&t;/* FIFO Xfer Infomation in              */
DECL|macro|TSC_MSG_ACCEPT
mdefine_line|#define TSC_MSG_ACCEPT  0x0F&t;/* Message Accept                       */
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* bit definition for Tulip SCSI Control 0 Register                     */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|TSC_RST_SEQ
mdefine_line|#define TSC_RST_SEQ     0x20&t;/* Reset sequence counter               */
DECL|macro|TSC_FLUSH_FIFO
mdefine_line|#define TSC_FLUSH_FIFO  0x10&t;/* Flush FIFO                           */
DECL|macro|TSC_ABT_CMD
mdefine_line|#define TSC_ABT_CMD     0x04&t;/* Abort command (sequence)             */
DECL|macro|TSC_RST_CHIP
mdefine_line|#define TSC_RST_CHIP    0x02&t;/* Reset SCSI Chip                      */
DECL|macro|TSC_RST_BUS
mdefine_line|#define TSC_RST_BUS     0x01&t;/* Reset SCSI Bus                       */
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* bit definition for Tulip SCSI Control 1 Register                     */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|TSC_EN_SCAM
mdefine_line|#define TSC_EN_SCAM     0x80&t;/* Enable SCAM                          */
DECL|macro|TSC_TIMER
mdefine_line|#define TSC_TIMER       0x40&t;/* Select timeout unit                  */
DECL|macro|TSC_EN_SCSI2
mdefine_line|#define TSC_EN_SCSI2    0x20&t;/* SCSI-2 mode                          */
DECL|macro|TSC_PWDN
mdefine_line|#define TSC_PWDN        0x10&t;/* Power down mode                      */
DECL|macro|TSC_WIDE_CPU
mdefine_line|#define TSC_WIDE_CPU    0x08&t;/* Wide CPU                             */
DECL|macro|TSC_HW_RESELECT
mdefine_line|#define TSC_HW_RESELECT 0x04&t;/* Enable HW reselect                   */
DECL|macro|TSC_EN_BUS_OUT
mdefine_line|#define TSC_EN_BUS_OUT  0x02&t;/* Enable SCSI data bus out latch       */
DECL|macro|TSC_EN_BUS_IN
mdefine_line|#define TSC_EN_BUS_IN   0x01&t;/* Enable SCSI data bus in latch        */
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* bit definition for Tulip SCSI Configuration Register                 */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|TSC_EN_LATCH
mdefine_line|#define TSC_EN_LATCH    0x80&t;/* Enable phase latch                   */
DECL|macro|TSC_INITIATOR
mdefine_line|#define TSC_INITIATOR   0x40&t;/* Initiator mode                       */
DECL|macro|TSC_EN_SCSI_PAR
mdefine_line|#define TSC_EN_SCSI_PAR 0x20&t;/* Enable SCSI parity                   */
DECL|macro|TSC_DMA_8BIT
mdefine_line|#define TSC_DMA_8BIT    0x10&t;/* Alternate dma 8-bits mode            */
DECL|macro|TSC_DMA_16BIT
mdefine_line|#define TSC_DMA_16BIT   0x08&t;/* Alternate dma 16-bits mode           */
DECL|macro|TSC_EN_WDACK
mdefine_line|#define TSC_EN_WDACK    0x04&t;/* Enable DACK while wide SCSI xfer     */
DECL|macro|TSC_ALT_PERIOD
mdefine_line|#define TSC_ALT_PERIOD  0x02&t;/* Alternate sync period mode           */
DECL|macro|TSC_DIS_SCSIRST
mdefine_line|#define TSC_DIS_SCSIRST 0x01&t;/* Disable SCSI bus reset us            */
DECL|macro|TSC_INITDEFAULT
mdefine_line|#define TSC_INITDEFAULT (TSC_INITIATOR | TSC_EN_LATCH | TSC_ALT_PERIOD | TSC_DIS_SCSIRST)
DECL|macro|TSC_WIDE_SCSI
mdefine_line|#define TSC_WIDE_SCSI   0x80&t;/* Enable Wide SCSI                     */
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* bit definition for Tulip SCSI signal Register                        */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|TSC_RST_ACK
mdefine_line|#define TSC_RST_ACK     0x00&t;/* Release ACK signal                   */
DECL|macro|TSC_RST_ATN
mdefine_line|#define TSC_RST_ATN     0x00&t;/* Release ATN signal                   */
DECL|macro|TSC_RST_BSY
mdefine_line|#define TSC_RST_BSY     0x00&t;/* Release BSY signal                   */
DECL|macro|TSC_SET_ACK
mdefine_line|#define TSC_SET_ACK     0x40&t;/* ACK signal                           */
DECL|macro|TSC_SET_ATN
mdefine_line|#define TSC_SET_ATN     0x08&t;/* ATN signal                           */
DECL|macro|TSC_REQI
mdefine_line|#define TSC_REQI        0x80&t;/* REQ signal                           */
DECL|macro|TSC_ACKI
mdefine_line|#define TSC_ACKI        0x40&t;/* ACK signal                           */
DECL|macro|TSC_BSYI
mdefine_line|#define TSC_BSYI        0x20&t;/* BSY signal                           */
DECL|macro|TSC_SELI
mdefine_line|#define TSC_SELI        0x10&t;/* SEL signal                           */
DECL|macro|TSC_ATNI
mdefine_line|#define TSC_ATNI        0x08&t;/* ATN signal                           */
DECL|macro|TSC_MSGI
mdefine_line|#define TSC_MSGI        0x04&t;/* MSG signal                           */
DECL|macro|TSC_CDI
mdefine_line|#define TSC_CDI         0x02&t;/* C/D signal                           */
DECL|macro|TSC_IOI
mdefine_line|#define TSC_IOI         0x01&t;/* I/O signal                           */
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* bit definition for Tulip SCSI Status 0 Register                      */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|TSS_INT_PENDING
mdefine_line|#define TSS_INT_PENDING 0x80&t;/* Interrupt pending            */
DECL|macro|TSS_SEQ_ACTIVE
mdefine_line|#define TSS_SEQ_ACTIVE  0x40&t;/* Sequencer active             */
DECL|macro|TSS_XFER_CNT
mdefine_line|#define TSS_XFER_CNT    0x20&t;/* Transfer counter zero        */
DECL|macro|TSS_FIFO_EMPTY
mdefine_line|#define TSS_FIFO_EMPTY  0x10&t;/* FIFO empty                   */
DECL|macro|TSS_PAR_ERROR
mdefine_line|#define TSS_PAR_ERROR   0x08&t;/* SCSI parity error            */
DECL|macro|TSS_PH_MASK
mdefine_line|#define TSS_PH_MASK     0x07&t;/* SCSI phase mask              */
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* bit definition for Tulip SCSI Status 1 Register                      */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|TSS_STATUS_RCV
mdefine_line|#define TSS_STATUS_RCV  0x08&t;/* Status received              */
DECL|macro|TSS_MSG_SEND
mdefine_line|#define TSS_MSG_SEND    0x40&t;/* Message sent                 */
DECL|macro|TSS_CMD_PH_CMP
mdefine_line|#define TSS_CMD_PH_CMP  0x20&t;/* command phase done              */
DECL|macro|TSS_DATA_PH_CMP
mdefine_line|#define TSS_DATA_PH_CMP 0x10&t;/* Data phase done              */
DECL|macro|TSS_STATUS_SEND
mdefine_line|#define TSS_STATUS_SEND 0x08&t;/* Status sent                  */
DECL|macro|TSS_XFER_CMP
mdefine_line|#define TSS_XFER_CMP    0x04&t;/* Transfer completed           */
DECL|macro|TSS_SEL_CMP
mdefine_line|#define TSS_SEL_CMP     0x02&t;/* Selection completed          */
DECL|macro|TSS_ARB_CMP
mdefine_line|#define TSS_ARB_CMP     0x01&t;/* Arbitration completed        */
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* bit definition for Tulip SCSI Status 2 Register                      */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|TSS_CMD_ABTED
mdefine_line|#define TSS_CMD_ABTED   0x80&t;/* Command aborted              */
DECL|macro|TSS_OFFSET_0
mdefine_line|#define TSS_OFFSET_0    0x40&t;/* Offset counter zero          */
DECL|macro|TSS_FIFO_FULL
mdefine_line|#define TSS_FIFO_FULL   0x20&t;/* FIFO full                    */
DECL|macro|TSS_TIMEOUT_0
mdefine_line|#define TSS_TIMEOUT_0   0x10&t;/* Timeout counter zero         */
DECL|macro|TSS_BUSY_RLS
mdefine_line|#define TSS_BUSY_RLS    0x08&t;/* Busy release                 */
DECL|macro|TSS_PH_MISMATCH
mdefine_line|#define TSS_PH_MISMATCH 0x04&t;/* Phase mismatch               */
DECL|macro|TSS_SCSI_BUS_EN
mdefine_line|#define TSS_SCSI_BUS_EN 0x02&t;/* SCSI data bus enable         */
DECL|macro|TSS_SCSIRST
mdefine_line|#define TSS_SCSIRST     0x01&t;/* SCSI bus reset in progress   */
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* bit definition for Tulip SCSI Interrupt Register                     */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|TSS_RESEL_INT
mdefine_line|#define TSS_RESEL_INT   0x80&t;/* Reselected interrupt         */
DECL|macro|TSS_SEL_TIMEOUT
mdefine_line|#define TSS_SEL_TIMEOUT 0x40&t;/* Selected/reselected timeout  */
DECL|macro|TSS_BUS_SERV
mdefine_line|#define TSS_BUS_SERV    0x20
DECL|macro|TSS_SCSIRST_INT
mdefine_line|#define TSS_SCSIRST_INT 0x10&t;/* SCSI bus reset detected      */
DECL|macro|TSS_DISC_INT
mdefine_line|#define TSS_DISC_INT    0x08&t;/* Disconnected interrupt       */
DECL|macro|TSS_SEL_INT
mdefine_line|#define TSS_SEL_INT     0x04&t;/* Select interrupt             */
DECL|macro|TSS_SCAM_SEL
mdefine_line|#define TSS_SCAM_SEL    0x02&t;/* SCAM selected                */
DECL|macro|TSS_FUNC_COMP
mdefine_line|#define TSS_FUNC_COMP   0x01
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* SCSI Phase Codes.                                                    */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|DATA_OUT
mdefine_line|#define DATA_OUT        0
DECL|macro|DATA_IN
mdefine_line|#define DATA_IN         1&t;/* 4                            */
DECL|macro|CMD_OUT
mdefine_line|#define CMD_OUT         2
DECL|macro|STATUS_IN
mdefine_line|#define STATUS_IN       3&t;/* 6                            */
DECL|macro|MSG_OUT
mdefine_line|#define MSG_OUT         6&t;/* 3                            */
DECL|macro|MSG_IN
mdefine_line|#define MSG_IN          7
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* Command Codes of Tulip xfer Command register                         */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|TAX_X_FORC
mdefine_line|#define TAX_X_FORC      0x02
DECL|macro|TAX_X_ABT
mdefine_line|#define TAX_X_ABT       0x04
DECL|macro|TAX_X_CLR_FIFO
mdefine_line|#define TAX_X_CLR_FIFO  0x08
DECL|macro|TAX_X_IN
mdefine_line|#define TAX_X_IN        0x21
DECL|macro|TAX_X_OUT
mdefine_line|#define TAX_X_OUT       0x01
DECL|macro|TAX_SG_IN
mdefine_line|#define TAX_SG_IN       0xA1
DECL|macro|TAX_SG_OUT
mdefine_line|#define TAX_SG_OUT      0x81
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* Tulip Interrupt Register                                             */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|XCMP
mdefine_line|#define XCMP            0x01
DECL|macro|FCMP
mdefine_line|#define FCMP            0x02
DECL|macro|XABT
mdefine_line|#define XABT            0x04
DECL|macro|XERR
mdefine_line|#define XERR            0x08
DECL|macro|SCMP
mdefine_line|#define SCMP            0x10
DECL|macro|IPEND
mdefine_line|#define IPEND           0x80
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* Tulip DMA Status Register                                            */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|XPEND
mdefine_line|#define XPEND           0x01&t;/* Transfer pending             */
DECL|macro|FEMPTY
mdefine_line|#define FEMPTY          0x02&t;/* FIFO empty                   */
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* bit definition for TUL_GCTRL                                         */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|EXTSG
mdefine_line|#define EXTSG           0x80
DECL|macro|EXTAD
mdefine_line|#define EXTAD           0x60
DECL|macro|SEG4K
mdefine_line|#define SEG4K           0x08
DECL|macro|EEPRG
mdefine_line|#define EEPRG           0x04
DECL|macro|MRMUL
mdefine_line|#define MRMUL           0x02
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/* bit definition for TUL_NVRAM                                         */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|SE2CS
mdefine_line|#define SE2CS           0x08
DECL|macro|SE2CLK
mdefine_line|#define SE2CLK          0x04
DECL|macro|SE2DO
mdefine_line|#define SE2DO           0x02
DECL|macro|SE2DI
mdefine_line|#define SE2DI           0x01
multiline_comment|/************************************************************************/
multiline_comment|/*              Scatter-Gather Element Structure                        */
multiline_comment|/************************************************************************/
DECL|struct|SG_Struc
r_typedef
r_struct
id|SG_Struc
(brace
DECL|member|SG_Ptr
id|U32
id|SG_Ptr
suffix:semicolon
multiline_comment|/* Data Pointer */
DECL|member|SG_Len
id|U32
id|SG_Len
suffix:semicolon
multiline_comment|/* Data Length */
DECL|typedef|SG
)brace
id|SG
suffix:semicolon
multiline_comment|/***********************************************************************&n;&t;&t;SCSI Control Block&n;************************************************************************/
DECL|struct|Scsi_Ctrl_Blk
r_typedef
r_struct
id|Scsi_Ctrl_Blk
(brace
DECL|member|SCB_NxtScb
r_struct
id|Scsi_Ctrl_Blk
op_star
id|SCB_NxtScb
suffix:semicolon
DECL|member|SCB_Status
id|UBYTE
id|SCB_Status
suffix:semicolon
multiline_comment|/*4 */
DECL|member|SCB_NxtStat
id|UBYTE
id|SCB_NxtStat
suffix:semicolon
multiline_comment|/*5 */
DECL|member|SCB_Mode
id|UBYTE
id|SCB_Mode
suffix:semicolon
multiline_comment|/*6 */
DECL|member|SCB_Msgin
id|UBYTE
id|SCB_Msgin
suffix:semicolon
multiline_comment|/*7 SCB_Res0 */
DECL|member|SCB_SGIdx
id|UWORD
id|SCB_SGIdx
suffix:semicolon
multiline_comment|/*8 */
DECL|member|SCB_SGMax
id|UWORD
id|SCB_SGMax
suffix:semicolon
multiline_comment|/*A */
macro_line|#ifdef ALPHA
DECL|member|SCB_Reserved
id|U32
id|SCB_Reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*C */
macro_line|#else
DECL|member|SCB_Reserved
id|U32
id|SCB_Reserved
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/*C */
macro_line|#endif
DECL|member|SCB_XferLen
id|U32
id|SCB_XferLen
suffix:semicolon
multiline_comment|/*18 Current xfer len           */
DECL|member|SCB_TotXLen
id|U32
id|SCB_TotXLen
suffix:semicolon
multiline_comment|/*1C Total xfer len             */
DECL|member|SCB_PAddr
id|U32
id|SCB_PAddr
suffix:semicolon
multiline_comment|/*20 SCB phy. Addr. */
DECL|member|SCB_Opcode
id|UBYTE
id|SCB_Opcode
suffix:semicolon
multiline_comment|/*24 SCB command code */
DECL|member|SCB_Flags
id|UBYTE
id|SCB_Flags
suffix:semicolon
multiline_comment|/*25 SCB Flags */
DECL|member|SCB_Target
id|UBYTE
id|SCB_Target
suffix:semicolon
multiline_comment|/*26 Target Id */
DECL|member|SCB_Lun
id|UBYTE
id|SCB_Lun
suffix:semicolon
multiline_comment|/*27 Lun */
DECL|member|SCB_BufPtr
id|U32
id|SCB_BufPtr
suffix:semicolon
multiline_comment|/*28 Data Buffer Pointer */
DECL|member|SCB_BufLen
id|U32
id|SCB_BufLen
suffix:semicolon
multiline_comment|/*2C Data Allocation Length */
DECL|member|SCB_SGLen
id|UBYTE
id|SCB_SGLen
suffix:semicolon
multiline_comment|/*30 SG list # */
DECL|member|SCB_SenseLen
id|UBYTE
id|SCB_SenseLen
suffix:semicolon
multiline_comment|/*31 Sense Allocation Length */
DECL|member|SCB_HaStat
id|UBYTE
id|SCB_HaStat
suffix:semicolon
multiline_comment|/*32 */
DECL|member|SCB_TaStat
id|UBYTE
id|SCB_TaStat
suffix:semicolon
multiline_comment|/*33 */
DECL|member|SCB_CDBLen
id|UBYTE
id|SCB_CDBLen
suffix:semicolon
multiline_comment|/*34 CDB Length */
DECL|member|SCB_Ident
id|UBYTE
id|SCB_Ident
suffix:semicolon
multiline_comment|/*35 Identify */
DECL|member|SCB_TagMsg
id|UBYTE
id|SCB_TagMsg
suffix:semicolon
multiline_comment|/*36 Tag Message */
DECL|member|SCB_TagId
id|UBYTE
id|SCB_TagId
suffix:semicolon
multiline_comment|/*37 Queue Tag */
DECL|member|SCB_CDB
id|UBYTE
id|SCB_CDB
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/*38 */
DECL|member|SCB_SGPAddr
id|U32
id|SCB_SGPAddr
suffix:semicolon
multiline_comment|/*44 SG List/Sense Buf phy. Addr. */
DECL|member|SCB_SensePtr
id|U32
id|SCB_SensePtr
suffix:semicolon
multiline_comment|/*48 Sense data pointer */
DECL|member|SCB_Post
r_void
(paren
op_star
id|SCB_Post
)paren
(paren
id|BYTE
op_star
comma
id|BYTE
op_star
)paren
suffix:semicolon
multiline_comment|/*4C POST routine */
DECL|member|SCB_Srb
r_int
r_char
op_star
id|SCB_Srb
suffix:semicolon
multiline_comment|/*50 SRB Pointer */
DECL|member|SCB_SGList
id|SG
id|SCB_SGList
(braket
id|TOTAL_SG_ENTRY
)braket
suffix:semicolon
multiline_comment|/*54 Start of SG list */
DECL|typedef|SCB
)brace
id|SCB
suffix:semicolon
multiline_comment|/* Bit Definition for SCB_Status */
DECL|macro|SCB_RENT
mdefine_line|#define SCB_RENT        0x01
DECL|macro|SCB_PEND
mdefine_line|#define SCB_PEND        0x02
DECL|macro|SCB_CONTIG
mdefine_line|#define SCB_CONTIG      0x04&t;/* Contigent Allegiance */
DECL|macro|SCB_SELECT
mdefine_line|#define SCB_SELECT      0x08
DECL|macro|SCB_BUSY
mdefine_line|#define SCB_BUSY        0x10
DECL|macro|SCB_DONE
mdefine_line|#define SCB_DONE        0x20
multiline_comment|/* Opcodes of SCB_Opcode */
DECL|macro|ExecSCSI
mdefine_line|#define ExecSCSI        0x1
DECL|macro|BusDevRst
mdefine_line|#define BusDevRst       0x2
DECL|macro|AbortCmd
mdefine_line|#define AbortCmd        0x3
multiline_comment|/* Bit Definition for SCB_Mode */
DECL|macro|SCM_RSENS
mdefine_line|#define SCM_RSENS       0x01&t;/* request sense mode */
multiline_comment|/* Bit Definition for SCB_Flags */
DECL|macro|SCF_DONE
mdefine_line|#define SCF_DONE        0x01
DECL|macro|SCF_POST
mdefine_line|#define SCF_POST        0x02
DECL|macro|SCF_SENSE
mdefine_line|#define SCF_SENSE       0x04
DECL|macro|SCF_DIR
mdefine_line|#define SCF_DIR         0x18
DECL|macro|SCF_NO_DCHK
mdefine_line|#define SCF_NO_DCHK     0x00
DECL|macro|SCF_DIN
mdefine_line|#define SCF_DIN         0x08
DECL|macro|SCF_DOUT
mdefine_line|#define SCF_DOUT        0x10
DECL|macro|SCF_NO_XF
mdefine_line|#define SCF_NO_XF       0x18
DECL|macro|SCF_WR_VF
mdefine_line|#define SCF_WR_VF       0x20&t;/* Write verify turn on         */
DECL|macro|SCF_POLL
mdefine_line|#define SCF_POLL        0x40
DECL|macro|SCF_SG
mdefine_line|#define SCF_SG          0x80
multiline_comment|/* Error Codes for SCB_HaStat */
DECL|macro|HOST_SEL_TOUT
mdefine_line|#define HOST_SEL_TOUT   0x11
DECL|macro|HOST_DO_DU
mdefine_line|#define HOST_DO_DU      0x12
DECL|macro|HOST_BUS_FREE
mdefine_line|#define HOST_BUS_FREE   0x13
DECL|macro|HOST_BAD_PHAS
mdefine_line|#define HOST_BAD_PHAS   0x14
DECL|macro|HOST_INV_CMD
mdefine_line|#define HOST_INV_CMD    0x16
DECL|macro|HOST_ABORTED
mdefine_line|#define HOST_ABORTED    0x1A&t;/* 07/21/98 */
DECL|macro|HOST_SCSI_RST
mdefine_line|#define HOST_SCSI_RST   0x1B
DECL|macro|HOST_DEV_RST
mdefine_line|#define HOST_DEV_RST    0x1C
multiline_comment|/* Error Codes for SCB_TaStat */
DECL|macro|TARGET_CHKCOND
mdefine_line|#define TARGET_CHKCOND  0x02
DECL|macro|TARGET_BUSY
mdefine_line|#define TARGET_BUSY     0x08
DECL|macro|QUEUE_FULL
mdefine_line|#define QUEUE_FULL&t;0x28
multiline_comment|/* SCSI MESSAGE */
DECL|macro|MSG_COMP
mdefine_line|#define MSG_COMP        0x00
DECL|macro|MSG_EXTEND
mdefine_line|#define MSG_EXTEND      0x01
DECL|macro|MSG_SDP
mdefine_line|#define MSG_SDP         0x02
DECL|macro|MSG_RESTORE
mdefine_line|#define MSG_RESTORE     0x03
DECL|macro|MSG_DISC
mdefine_line|#define MSG_DISC        0x04
DECL|macro|MSG_IDE
mdefine_line|#define MSG_IDE         0x05
DECL|macro|MSG_ABORT
mdefine_line|#define MSG_ABORT       0x06
DECL|macro|MSG_REJ
mdefine_line|#define MSG_REJ         0x07
DECL|macro|MSG_NOP
mdefine_line|#define MSG_NOP         0x08
DECL|macro|MSG_PARITY
mdefine_line|#define MSG_PARITY      0x09
DECL|macro|MSG_LINK_COMP
mdefine_line|#define MSG_LINK_COMP   0x0A
DECL|macro|MSG_LINK_FLAG
mdefine_line|#define MSG_LINK_FLAG   0x0B
DECL|macro|MSG_DEVRST
mdefine_line|#define MSG_DEVRST      0x0C
DECL|macro|MSG_ABORT_TAG
mdefine_line|#define MSG_ABORT_TAG   0x0D
multiline_comment|/* Queue tag msg: Simple_quque_tag, Head_of_queue_tag, Ordered_queue_tag */
DECL|macro|MSG_STAG
mdefine_line|#define MSG_STAG        0x20
DECL|macro|MSG_HTAG
mdefine_line|#define MSG_HTAG        0x21
DECL|macro|MSG_OTAG
mdefine_line|#define MSG_OTAG        0x22
DECL|macro|MSG_IGNOREWIDE
mdefine_line|#define MSG_IGNOREWIDE  0x23
DECL|macro|MSG_IDENT
mdefine_line|#define MSG_IDENT   0x80
multiline_comment|/***********************************************************************&n;&t;&t;Target Device Control Structure&n;**********************************************************************/
DECL|struct|Tar_Ctrl_Struc
r_typedef
r_struct
id|Tar_Ctrl_Struc
(brace
DECL|member|TCS_Flags
id|UWORD
id|TCS_Flags
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|TCS_JS_Period
id|UBYTE
id|TCS_JS_Period
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|TCS_SConfig0
id|UBYTE
id|TCS_SConfig0
suffix:semicolon
multiline_comment|/* 3 */
DECL|member|TCS_DrvFlags
id|UWORD
id|TCS_DrvFlags
suffix:semicolon
multiline_comment|/* 4 */
DECL|member|TCS_DrvHead
id|UBYTE
id|TCS_DrvHead
suffix:semicolon
multiline_comment|/* 6 */
DECL|member|TCS_DrvSector
id|UBYTE
id|TCS_DrvSector
suffix:semicolon
multiline_comment|/* 7 */
DECL|typedef|TCS
)brace
id|TCS
suffix:semicolon
multiline_comment|/***********************************************************************&n;&t;&t;Target Device Control Structure&n;**********************************************************************/
multiline_comment|/* Bit Definition for TCF_Flags */
DECL|macro|TCF_SCSI_RATE
mdefine_line|#define TCF_SCSI_RATE           0x0007
DECL|macro|TCF_EN_DISC
mdefine_line|#define TCF_EN_DISC             0x0008
DECL|macro|TCF_NO_SYNC_NEGO
mdefine_line|#define TCF_NO_SYNC_NEGO        0x0010
DECL|macro|TCF_NO_WDTR
mdefine_line|#define TCF_NO_WDTR             0x0020
DECL|macro|TCF_EN_255
mdefine_line|#define TCF_EN_255              0x0040
DECL|macro|TCF_EN_START
mdefine_line|#define TCF_EN_START            0x0080
DECL|macro|TCF_WDTR_DONE
mdefine_line|#define TCF_WDTR_DONE           0x0100
DECL|macro|TCF_SYNC_DONE
mdefine_line|#define TCF_SYNC_DONE           0x0200
DECL|macro|TCF_BUSY
mdefine_line|#define TCF_BUSY                0x0400
multiline_comment|/* Bit Definition for TCF_DrvFlags */
DECL|macro|TCF_DRV_BUSY
mdefine_line|#define TCF_DRV_BUSY            0x01&t;/* Indicate target busy(driver) */
DECL|macro|TCF_DRV_EN_TAG
mdefine_line|#define TCF_DRV_EN_TAG          0x0800
DECL|macro|TCF_DRV_255_63
mdefine_line|#define TCF_DRV_255_63          0x0400
DECL|struct|I91u_Adpt_Struc
r_typedef
r_struct
id|I91u_Adpt_Struc
(brace
DECL|member|ADPT_BIOS
id|UWORD
id|ADPT_BIOS
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|ADPT_BASE
id|UWORD
id|ADPT_BASE
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|ADPT_Bus
id|UBYTE
id|ADPT_Bus
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|ADPT_Device
id|UBYTE
id|ADPT_Device
suffix:semicolon
multiline_comment|/* 3 */
DECL|member|ADPT_INTR
id|UBYTE
id|ADPT_INTR
suffix:semicolon
multiline_comment|/* 4 */
DECL|typedef|INI_ADPT_STRUCT
)brace
id|INI_ADPT_STRUCT
suffix:semicolon
multiline_comment|/***********************************************************************&n;&t;      Host Adapter Control Structure&n;************************************************************************/
DECL|struct|Ha_Ctrl_Struc
r_typedef
r_struct
id|Ha_Ctrl_Struc
(brace
DECL|member|HCS_Base
id|UWORD
id|HCS_Base
suffix:semicolon
multiline_comment|/* 00 */
DECL|member|HCS_BIOS
id|UWORD
id|HCS_BIOS
suffix:semicolon
multiline_comment|/* 02 */
DECL|member|HCS_Intr
id|UBYTE
id|HCS_Intr
suffix:semicolon
multiline_comment|/* 04 */
DECL|member|HCS_SCSI_ID
id|UBYTE
id|HCS_SCSI_ID
suffix:semicolon
multiline_comment|/* 05 */
DECL|member|HCS_MaxTar
id|UBYTE
id|HCS_MaxTar
suffix:semicolon
multiline_comment|/* 06 */
DECL|member|HCS_NumScbs
id|UBYTE
id|HCS_NumScbs
suffix:semicolon
multiline_comment|/* 07 */
DECL|member|HCS_Flags
id|UBYTE
id|HCS_Flags
suffix:semicolon
multiline_comment|/* 08 */
DECL|member|HCS_Index
id|UBYTE
id|HCS_Index
suffix:semicolon
multiline_comment|/* 09 */
DECL|member|HCS_HaId
id|UBYTE
id|HCS_HaId
suffix:semicolon
multiline_comment|/* 0A */
DECL|member|HCS_Config
id|UBYTE
id|HCS_Config
suffix:semicolon
multiline_comment|/* 0B */
DECL|member|HCS_IdMask
id|UWORD
id|HCS_IdMask
suffix:semicolon
multiline_comment|/* 0C */
DECL|member|HCS_Semaph
id|UBYTE
id|HCS_Semaph
suffix:semicolon
multiline_comment|/* 0E */
DECL|member|HCS_Phase
id|UBYTE
id|HCS_Phase
suffix:semicolon
multiline_comment|/* 0F */
DECL|member|HCS_JSStatus0
id|UBYTE
id|HCS_JSStatus0
suffix:semicolon
multiline_comment|/* 10 */
DECL|member|HCS_JSInt
id|UBYTE
id|HCS_JSInt
suffix:semicolon
multiline_comment|/* 11 */
DECL|member|HCS_JSStatus1
id|UBYTE
id|HCS_JSStatus1
suffix:semicolon
multiline_comment|/* 12 */
DECL|member|HCS_SConf1
id|UBYTE
id|HCS_SConf1
suffix:semicolon
multiline_comment|/* 13 */
DECL|member|HCS_Msg
id|UBYTE
id|HCS_Msg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 14 */
DECL|member|HCS_NxtAvail
id|SCB
op_star
id|HCS_NxtAvail
suffix:semicolon
multiline_comment|/* 1C */
DECL|member|HCS_Scb
id|SCB
op_star
id|HCS_Scb
suffix:semicolon
multiline_comment|/* 20 */
DECL|member|HCS_ScbEnd
id|SCB
op_star
id|HCS_ScbEnd
suffix:semicolon
multiline_comment|/* 24 */
DECL|member|HCS_NxtPend
id|SCB
op_star
id|HCS_NxtPend
suffix:semicolon
multiline_comment|/* 28 */
DECL|member|HCS_NxtContig
id|SCB
op_star
id|HCS_NxtContig
suffix:semicolon
multiline_comment|/* 2C */
DECL|member|HCS_ActScb
id|SCB
op_star
id|HCS_ActScb
suffix:semicolon
multiline_comment|/* 30 */
DECL|member|HCS_ActTcs
id|TCS
op_star
id|HCS_ActTcs
suffix:semicolon
multiline_comment|/* 34 */
DECL|member|HCS_FirstAvail
id|SCB
op_star
id|HCS_FirstAvail
suffix:semicolon
multiline_comment|/* 38 */
DECL|member|HCS_LastAvail
id|SCB
op_star
id|HCS_LastAvail
suffix:semicolon
multiline_comment|/* 3C */
DECL|member|HCS_FirstPend
id|SCB
op_star
id|HCS_FirstPend
suffix:semicolon
multiline_comment|/* 40 */
DECL|member|HCS_LastPend
id|SCB
op_star
id|HCS_LastPend
suffix:semicolon
multiline_comment|/* 44 */
DECL|member|HCS_FirstBusy
id|SCB
op_star
id|HCS_FirstBusy
suffix:semicolon
multiline_comment|/* 48 */
DECL|member|HCS_LastBusy
id|SCB
op_star
id|HCS_LastBusy
suffix:semicolon
multiline_comment|/* 4C */
DECL|member|HCS_FirstDone
id|SCB
op_star
id|HCS_FirstDone
suffix:semicolon
multiline_comment|/* 50 */
DECL|member|HCS_LastDone
id|SCB
op_star
id|HCS_LastDone
suffix:semicolon
multiline_comment|/* 54 */
DECL|member|HCS_MaxTags
id|UBYTE
id|HCS_MaxTags
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 58 */
DECL|member|HCS_ActTags
id|UBYTE
id|HCS_ActTags
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 68 */
DECL|member|HCS_Tcs
id|TCS
id|HCS_Tcs
(braket
id|MAX_TARGETS
)braket
suffix:semicolon
multiline_comment|/* 78 */
DECL|member|pSRB_head
id|ULONG
id|pSRB_head
suffix:semicolon
multiline_comment|/* SRB save queue header     */
DECL|member|pSRB_tail
id|ULONG
id|pSRB_tail
suffix:semicolon
multiline_comment|/* SRB save queue tail       */
macro_line|#if LINUX_VERSION_CODE &gt;= CVT_LINUX_VERSION(2,1,95)
DECL|member|HCS_AvailLock
id|spinlock_t
id|HCS_AvailLock
suffix:semicolon
DECL|member|HCS_SemaphLock
id|spinlock_t
id|HCS_SemaphLock
suffix:semicolon
DECL|member|pSRB_lock
id|spinlock_t
id|pSRB_lock
suffix:semicolon
multiline_comment|/* SRB queue lock            */
macro_line|#endif
DECL|typedef|HCS
)brace
id|HCS
suffix:semicolon
multiline_comment|/* Bit Definition for HCB_Config */
DECL|macro|HCC_SCSI_RESET
mdefine_line|#define HCC_SCSI_RESET          0x01
DECL|macro|HCC_EN_PAR
mdefine_line|#define HCC_EN_PAR              0x02
DECL|macro|HCC_ACT_TERM1
mdefine_line|#define HCC_ACT_TERM1           0x04
DECL|macro|HCC_ACT_TERM2
mdefine_line|#define HCC_ACT_TERM2           0x08
DECL|macro|HCC_AUTO_TERM
mdefine_line|#define HCC_AUTO_TERM           0x10
DECL|macro|HCC_EN_PWR
mdefine_line|#define HCC_EN_PWR              0x80
multiline_comment|/* Bit Definition for HCB_Flags */
DECL|macro|HCF_EXPECT_DISC
mdefine_line|#define HCF_EXPECT_DISC         0x01
DECL|macro|HCF_EXPECT_SELECT
mdefine_line|#define HCF_EXPECT_SELECT       0x02
DECL|macro|HCF_EXPECT_RESET
mdefine_line|#define HCF_EXPECT_RESET        0x10
DECL|macro|HCF_EXPECT_DONE_DISC
mdefine_line|#define HCF_EXPECT_DONE_DISC    0x20
multiline_comment|/******************************************************************&n;&t;Serial EEProm&n;*******************************************************************/
DECL|struct|_NVRAM_SCSI
r_typedef
r_struct
id|_NVRAM_SCSI
(brace
multiline_comment|/* SCSI channel configuration   */
DECL|member|NVM_ChSCSIID
id|UCHAR
id|NVM_ChSCSIID
suffix:semicolon
multiline_comment|/* 0Ch -&gt; Channel SCSI ID       */
DECL|member|NVM_ChConfig1
id|UCHAR
id|NVM_ChConfig1
suffix:semicolon
multiline_comment|/* 0Dh -&gt; Channel config 1      */
DECL|member|NVM_ChConfig2
id|UCHAR
id|NVM_ChConfig2
suffix:semicolon
multiline_comment|/* 0Eh -&gt; Channel config 2      */
DECL|member|NVM_NumOfTarg
id|UCHAR
id|NVM_NumOfTarg
suffix:semicolon
multiline_comment|/* 0Fh -&gt; Number of SCSI target */
multiline_comment|/* SCSI target configuration    */
DECL|member|NVM_Targ0Config
id|UCHAR
id|NVM_Targ0Config
suffix:semicolon
multiline_comment|/* 10h -&gt; Target 0 configuration */
DECL|member|NVM_Targ1Config
id|UCHAR
id|NVM_Targ1Config
suffix:semicolon
multiline_comment|/* 11h -&gt; Target 1 configuration */
DECL|member|NVM_Targ2Config
id|UCHAR
id|NVM_Targ2Config
suffix:semicolon
multiline_comment|/* 12h -&gt; Target 2 configuration */
DECL|member|NVM_Targ3Config
id|UCHAR
id|NVM_Targ3Config
suffix:semicolon
multiline_comment|/* 13h -&gt; Target 3 configuration */
DECL|member|NVM_Targ4Config
id|UCHAR
id|NVM_Targ4Config
suffix:semicolon
multiline_comment|/* 14h -&gt; Target 4 configuration */
DECL|member|NVM_Targ5Config
id|UCHAR
id|NVM_Targ5Config
suffix:semicolon
multiline_comment|/* 15h -&gt; Target 5 configuration */
DECL|member|NVM_Targ6Config
id|UCHAR
id|NVM_Targ6Config
suffix:semicolon
multiline_comment|/* 16h -&gt; Target 6 configuration */
DECL|member|NVM_Targ7Config
id|UCHAR
id|NVM_Targ7Config
suffix:semicolon
multiline_comment|/* 17h -&gt; Target 7 configuration */
DECL|member|NVM_Targ8Config
id|UCHAR
id|NVM_Targ8Config
suffix:semicolon
multiline_comment|/* 18h -&gt; Target 8 configuration */
DECL|member|NVM_Targ9Config
id|UCHAR
id|NVM_Targ9Config
suffix:semicolon
multiline_comment|/* 19h -&gt; Target 9 configuration */
DECL|member|NVM_TargAConfig
id|UCHAR
id|NVM_TargAConfig
suffix:semicolon
multiline_comment|/* 1Ah -&gt; Target A configuration */
DECL|member|NVM_TargBConfig
id|UCHAR
id|NVM_TargBConfig
suffix:semicolon
multiline_comment|/* 1Bh -&gt; Target B configuration */
DECL|member|NVM_TargCConfig
id|UCHAR
id|NVM_TargCConfig
suffix:semicolon
multiline_comment|/* 1Ch -&gt; Target C configuration */
DECL|member|NVM_TargDConfig
id|UCHAR
id|NVM_TargDConfig
suffix:semicolon
multiline_comment|/* 1Dh -&gt; Target D configuration */
DECL|member|NVM_TargEConfig
id|UCHAR
id|NVM_TargEConfig
suffix:semicolon
multiline_comment|/* 1Eh -&gt; Target E configuration */
DECL|member|NVM_TargFConfig
id|UCHAR
id|NVM_TargFConfig
suffix:semicolon
multiline_comment|/* 1Fh -&gt; Target F configuration */
DECL|typedef|NVRAM_SCSI
)brace
id|NVRAM_SCSI
suffix:semicolon
DECL|struct|_NVRAM
r_typedef
r_struct
id|_NVRAM
(brace
multiline_comment|/*----------header ---------------*/
DECL|member|NVM_Signature
id|USHORT
id|NVM_Signature
suffix:semicolon
multiline_comment|/* 0,1: Signature */
DECL|member|NVM_Size
id|UCHAR
id|NVM_Size
suffix:semicolon
multiline_comment|/* 2:   Size of data structure */
DECL|member|NVM_Revision
id|UCHAR
id|NVM_Revision
suffix:semicolon
multiline_comment|/* 3:   Revision of data structure */
multiline_comment|/* ----Host Adapter Structure ---- */
DECL|member|NVM_ModelByte0
id|UCHAR
id|NVM_ModelByte0
suffix:semicolon
multiline_comment|/* 4:   Model number (byte 0) */
DECL|member|NVM_ModelByte1
id|UCHAR
id|NVM_ModelByte1
suffix:semicolon
multiline_comment|/* 5:   Model number (byte 1) */
DECL|member|NVM_ModelInfo
id|UCHAR
id|NVM_ModelInfo
suffix:semicolon
multiline_comment|/* 6:   Model information         */
DECL|member|NVM_NumOfCh
id|UCHAR
id|NVM_NumOfCh
suffix:semicolon
multiline_comment|/* 7:   Number of SCSI channel */
DECL|member|NVM_BIOSConfig1
id|UCHAR
id|NVM_BIOSConfig1
suffix:semicolon
multiline_comment|/* 8:   BIOS configuration 1  */
DECL|member|NVM_BIOSConfig2
id|UCHAR
id|NVM_BIOSConfig2
suffix:semicolon
multiline_comment|/* 9:   BIOS configuration 2  */
DECL|member|NVM_HAConfig1
id|UCHAR
id|NVM_HAConfig1
suffix:semicolon
multiline_comment|/* A:   Hoat adapter configuration 1 */
DECL|member|NVM_HAConfig2
id|UCHAR
id|NVM_HAConfig2
suffix:semicolon
multiline_comment|/* B:   Hoat adapter configuration 2 */
DECL|member|NVM_SCSIInfo
id|NVRAM_SCSI
id|NVM_SCSIInfo
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|NVM_reserved
id|UCHAR
id|NVM_reserved
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* ---------- CheckSum ----------       */
DECL|member|NVM_CheckSum
id|USHORT
id|NVM_CheckSum
suffix:semicolon
multiline_comment|/* 0x3E, 0x3F: Checksum of NVRam        */
DECL|typedef|NVRAM
DECL|typedef|PNVRAM
)brace
id|NVRAM
comma
op_star
id|PNVRAM
suffix:semicolon
multiline_comment|/* Bios Configuration for nvram-&gt;BIOSConfig1                            */
DECL|macro|NBC1_ENABLE
mdefine_line|#define NBC1_ENABLE             0x01&t;/* BIOS enable                  */
DECL|macro|NBC1_8DRIVE
mdefine_line|#define NBC1_8DRIVE             0x02&t;/* Support more than 2 drives   */
DECL|macro|NBC1_REMOVABLE
mdefine_line|#define NBC1_REMOVABLE          0x04&t;/* Support removable drive      */
DECL|macro|NBC1_INT19
mdefine_line|#define NBC1_INT19              0x08&t;/* Intercept int 19h            */
DECL|macro|NBC1_BIOSSCAN
mdefine_line|#define NBC1_BIOSSCAN           0x10&t;/* Dynamic BIOS scan            */
DECL|macro|NBC1_LUNSUPPORT
mdefine_line|#define NBC1_LUNSUPPORT         0x40&t;/* Support LUN                  */
multiline_comment|/* HA Configuration Byte 1                                              */
DECL|macro|NHC1_BOOTIDMASK
mdefine_line|#define NHC1_BOOTIDMASK 0x0F&t;/* Boot ID number               */
DECL|macro|NHC1_LUNMASK
mdefine_line|#define NHC1_LUNMASK    0x70&t;/* Boot LUN number              */
DECL|macro|NHC1_CHANMASK
mdefine_line|#define NHC1_CHANMASK   0x80&t;/* Boot Channel number          */
multiline_comment|/* Bit definition for nvram-&gt;SCSIconfig1                                */
DECL|macro|NCC1_BUSRESET
mdefine_line|#define NCC1_BUSRESET           0x01&t;/* Reset SCSI bus at power up   */
DECL|macro|NCC1_PARITYCHK
mdefine_line|#define NCC1_PARITYCHK          0x02&t;/* SCSI parity enable           */
DECL|macro|NCC1_ACTTERM1
mdefine_line|#define NCC1_ACTTERM1           0x04&t;/* Enable active terminator 1   */
DECL|macro|NCC1_ACTTERM2
mdefine_line|#define NCC1_ACTTERM2           0x08&t;/* Enable active terminator 2   */
DECL|macro|NCC1_AUTOTERM
mdefine_line|#define NCC1_AUTOTERM           0x10&t;/* Enable auto terminator       */
DECL|macro|NCC1_PWRMGR
mdefine_line|#define NCC1_PWRMGR             0x80&t;/* Enable power management      */
multiline_comment|/* Bit definition for SCSI Target configuration byte                    */
DECL|macro|NTC_DISCONNECT
mdefine_line|#define NTC_DISCONNECT          0x08&t;/* Enable SCSI disconnect       */
DECL|macro|NTC_SYNC
mdefine_line|#define NTC_SYNC                0x10&t;/* SYNC_NEGO                    */
DECL|macro|NTC_NO_WDTR
mdefine_line|#define NTC_NO_WDTR             0x20&t;/* SYNC_NEGO                    */
DECL|macro|NTC_1GIGA
mdefine_line|#define NTC_1GIGA               0x40&t;/* 255 head / 63 sectors (64/32) */
DECL|macro|NTC_SPINUP
mdefine_line|#define NTC_SPINUP              0x80&t;/* Start disk drive             */
multiline_comment|/*      Default NVRam values                                            */
DECL|macro|INI_SIGNATURE
mdefine_line|#define INI_SIGNATURE           0xC925
DECL|macro|NBC1_DEFAULT
mdefine_line|#define NBC1_DEFAULT            (NBC1_ENABLE)
DECL|macro|NCC1_DEFAULT
mdefine_line|#define NCC1_DEFAULT            (NCC1_BUSRESET | NCC1_AUTOTERM | NCC1_PARITYCHK)
DECL|macro|NTC_DEFAULT
mdefine_line|#define NTC_DEFAULT             (NTC_NO_WDTR | NTC_1GIGA | NTC_DISCONNECT)
multiline_comment|/* SCSI related definition                                              */
DECL|macro|DISC_NOT_ALLOW
mdefine_line|#define DISC_NOT_ALLOW          0x80&t;/* Disconnect is not allowed    */
DECL|macro|DISC_ALLOW
mdefine_line|#define DISC_ALLOW              0xC0&t;/* Disconnect is allowed        */
DECL|macro|SCSICMD_RequestSense
mdefine_line|#define SCSICMD_RequestSense    0x03
multiline_comment|/*----------------------------------------------------------------------*/
multiline_comment|/*                              PCI                                     */
multiline_comment|/*----------------------------------------------------------------------*/
DECL|macro|PCI_FUNCTION_ID
mdefine_line|#define PCI_FUNCTION_ID         0xB1
DECL|macro|PCI_BIOS_PRESENT
mdefine_line|#define PCI_BIOS_PRESENT        0x01
DECL|macro|FIND_PCI_DEVICE
mdefine_line|#define FIND_PCI_DEVICE         0x02
DECL|macro|FIND_PCI_CLASS_CODE
mdefine_line|#define FIND_PCI_CLASS_CODE     0x03
DECL|macro|GENERATE_SPECIAL_CYCLE
mdefine_line|#define GENERATE_SPECIAL_CYCLE  0x06
DECL|macro|READ_CONFIG_BYTE
mdefine_line|#define READ_CONFIG_BYTE        0x08
DECL|macro|READ_CONFIG_WORD
mdefine_line|#define READ_CONFIG_WORD        0x09
DECL|macro|READ_CONFIG_DWORD
mdefine_line|#define READ_CONFIG_DWORD       0x0A
DECL|macro|WRITE_CONFIG_BYTE
mdefine_line|#define WRITE_CONFIG_BYTE       0x0B
DECL|macro|WRITE_CONFIG_WORD
mdefine_line|#define WRITE_CONFIG_WORD       0x0C
DECL|macro|WRITE_CONFIG_DWORD
mdefine_line|#define WRITE_CONFIG_DWORD      0x0D
DECL|macro|SUCCESSFUL
mdefine_line|#define SUCCESSFUL              0x00
DECL|macro|FUNC_NOT_SUPPORTED
mdefine_line|#define FUNC_NOT_SUPPORTED      0x81
DECL|macro|BAD_VENDOR_ID
mdefine_line|#define BAD_VENDOR_ID           0x83&t;/* Bad vendor ID                */
DECL|macro|DEVICE_NOT_FOUND
mdefine_line|#define DEVICE_NOT_FOUND        0x86&t;/* PCI device not found         */
DECL|macro|BAD_REGISTER_NUMBER
mdefine_line|#define BAD_REGISTER_NUMBER     0x87
DECL|macro|MAX_PCI_DEVICES
mdefine_line|#define MAX_PCI_DEVICES         21&t;/* Maximum devices supportted   */
DECL|macro|MAX_PCI_CHANL
mdefine_line|#define MAX_PCI_CHANL           4
DECL|struct|_BIOS32_ENTRY_STRUCTURE
r_typedef
r_struct
id|_BIOS32_ENTRY_STRUCTURE
(brace
DECL|member|Signatures
id|DWORD
id|Signatures
suffix:semicolon
multiline_comment|/* Should be &quot;_32_&quot;             */
DECL|member|BIOS32Entry
id|DWORD
id|BIOS32Entry
suffix:semicolon
multiline_comment|/* 32-bit physical address      */
DECL|member|Revision
id|BYTE
id|Revision
suffix:semicolon
multiline_comment|/* Revision level, should be 0  */
DECL|member|Length
id|BYTE
id|Length
suffix:semicolon
multiline_comment|/* Multiply of 16, should be 1  */
DECL|member|CheckSum
id|BYTE
id|CheckSum
suffix:semicolon
multiline_comment|/* Checksum of whole structure  */
DECL|member|Reserved
id|BYTE
id|Reserved
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Reserved                     */
DECL|typedef|BIOS32_ENTRY_STRUCTURE
DECL|typedef|PBIOS32_ENTRY_STRUCTURE
)brace
id|BIOS32_ENTRY_STRUCTURE
comma
op_star
id|PBIOS32_ENTRY_STRUCTURE
suffix:semicolon
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|eax
r_int
r_int
id|eax
suffix:semicolon
r_struct
(brace
DECL|member|ax
r_int
r_int
id|ax
suffix:semicolon
DECL|member|word
)brace
id|word
suffix:semicolon
r_struct
(brace
DECL|member|al
r_int
r_char
id|al
suffix:semicolon
DECL|member|ah
r_int
r_char
id|ah
suffix:semicolon
DECL|member|byte
)brace
id|byte
suffix:semicolon
DECL|member|eax
)brace
id|eax
suffix:semicolon
r_union
(brace
DECL|member|ebx
r_int
r_int
id|ebx
suffix:semicolon
r_struct
(brace
DECL|member|bx
r_int
r_int
id|bx
suffix:semicolon
DECL|member|word
)brace
id|word
suffix:semicolon
r_struct
(brace
DECL|member|bl
r_int
r_char
id|bl
suffix:semicolon
DECL|member|bh
r_int
r_char
id|bh
suffix:semicolon
DECL|member|byte
)brace
id|byte
suffix:semicolon
DECL|member|ebx
)brace
id|ebx
suffix:semicolon
r_union
(brace
DECL|member|ecx
r_int
r_int
id|ecx
suffix:semicolon
r_struct
(brace
DECL|member|cx
r_int
r_int
id|cx
suffix:semicolon
DECL|member|word
)brace
id|word
suffix:semicolon
r_struct
(brace
DECL|member|cl
r_int
r_char
id|cl
suffix:semicolon
DECL|member|ch
r_int
r_char
id|ch
suffix:semicolon
DECL|member|byte
)brace
id|byte
suffix:semicolon
DECL|member|ecx
)brace
id|ecx
suffix:semicolon
r_union
(brace
DECL|member|edx
r_int
r_int
id|edx
suffix:semicolon
r_struct
(brace
DECL|member|dx
r_int
r_int
id|dx
suffix:semicolon
DECL|member|word
)brace
id|word
suffix:semicolon
r_struct
(brace
DECL|member|dl
r_int
r_char
id|dl
suffix:semicolon
DECL|member|dh
r_int
r_char
id|dh
suffix:semicolon
DECL|member|byte
)brace
id|byte
suffix:semicolon
DECL|member|edx
)brace
id|edx
suffix:semicolon
r_union
(brace
DECL|member|edi
r_int
r_int
id|edi
suffix:semicolon
r_struct
(brace
DECL|member|di
r_int
r_int
id|di
suffix:semicolon
DECL|member|word
)brace
id|word
suffix:semicolon
DECL|member|edi
)brace
id|edi
suffix:semicolon
r_union
(brace
DECL|member|esi
r_int
r_int
id|esi
suffix:semicolon
r_struct
(brace
DECL|member|si
r_int
r_int
id|si
suffix:semicolon
DECL|member|word
)brace
id|word
suffix:semicolon
DECL|member|esi
)brace
id|esi
suffix:semicolon
DECL|typedef|REGS
)brace
id|REGS
suffix:semicolon
r_typedef
r_union
(brace
multiline_comment|/* Union define for mechanism 1 */
r_struct
(brace
DECL|member|RegNum
r_int
r_char
id|RegNum
suffix:semicolon
DECL|member|FcnNum
r_int
r_char
id|FcnNum
suffix:colon
l_int|3
suffix:semicolon
DECL|member|DeviceNum
r_int
r_char
id|DeviceNum
suffix:colon
l_int|5
suffix:semicolon
DECL|member|BusNum
r_int
r_char
id|BusNum
suffix:semicolon
DECL|member|Reserved
r_int
r_char
id|Reserved
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Enable
r_int
r_char
id|Enable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sConfigAdr
)brace
id|sConfigAdr
suffix:semicolon
DECL|member|lConfigAdr
r_int
r_int
id|lConfigAdr
suffix:semicolon
DECL|typedef|CONFIG_ADR
)brace
id|CONFIG_ADR
suffix:semicolon
r_typedef
r_union
(brace
multiline_comment|/* Union define for mechanism 2 */
r_struct
(brace
DECL|member|RegNum
r_int
r_char
id|RegNum
suffix:semicolon
DECL|member|DeviceNum
r_int
r_char
id|DeviceNum
suffix:semicolon
DECL|member|Reserved
r_int
r_int
id|Reserved
suffix:semicolon
DECL|member|sHostAdr
)brace
id|sHostAdr
suffix:semicolon
DECL|member|lHostAdr
r_int
r_int
id|lHostAdr
suffix:semicolon
DECL|typedef|HOST_ADR
)brace
id|HOST_ADR
suffix:semicolon
DECL|struct|_HCSinfo
r_typedef
r_struct
id|_HCSinfo
(brace
DECL|member|base
id|ULONG
id|base
suffix:semicolon
DECL|member|vec
id|UCHAR
id|vec
suffix:semicolon
DECL|member|bios
id|UCHAR
id|bios
suffix:semicolon
multiline_comment|/* High byte of BIOS address */
DECL|member|BaseAndBios
id|USHORT
id|BaseAndBios
suffix:semicolon
multiline_comment|/* high byte: pHcsInfo-&gt;bios,low byte:pHcsInfo-&gt;base */
DECL|typedef|HCSINFO
)brace
id|HCSINFO
suffix:semicolon
DECL|macro|TUL_RD
mdefine_line|#define TUL_RD(x,y)             (UCHAR)(inb(  (int)((ULONG)(x+y)) ))
DECL|macro|TUL_RDLONG
mdefine_line|#define TUL_RDLONG(x,y)         (ULONG)(inl((int)((ULONG)(x+y)) ))
DECL|macro|TUL_WR
mdefine_line|#define TUL_WR(     adr,data)   outb( (UCHAR)(data), (int)(adr))
DECL|macro|TUL_WRSHORT
mdefine_line|#define TUL_WRSHORT(adr,data)   outw( (UWORD)(data), (int)(adr))
DECL|macro|TUL_WRLONG
mdefine_line|#define TUL_WRLONG( adr,data)   outl( (ULONG)(data), (int)(adr))
DECL|macro|SCSI_ABORT_SNOOZE
mdefine_line|#define SCSI_ABORT_SNOOZE 0
DECL|macro|SCSI_ABORT_SUCCESS
mdefine_line|#define SCSI_ABORT_SUCCESS 1
DECL|macro|SCSI_ABORT_PENDING
mdefine_line|#define SCSI_ABORT_PENDING 2
DECL|macro|SCSI_ABORT_BUSY
mdefine_line|#define SCSI_ABORT_BUSY 3
DECL|macro|SCSI_ABORT_NOT_RUNNING
mdefine_line|#define SCSI_ABORT_NOT_RUNNING 4
DECL|macro|SCSI_ABORT_ERROR
mdefine_line|#define SCSI_ABORT_ERROR 5
DECL|macro|SCSI_RESET_SNOOZE
mdefine_line|#define SCSI_RESET_SNOOZE 0
DECL|macro|SCSI_RESET_PUNT
mdefine_line|#define SCSI_RESET_PUNT 1
DECL|macro|SCSI_RESET_SUCCESS
mdefine_line|#define SCSI_RESET_SUCCESS 2
DECL|macro|SCSI_RESET_PENDING
mdefine_line|#define SCSI_RESET_PENDING 3
DECL|macro|SCSI_RESET_WAKEUP
mdefine_line|#define SCSI_RESET_WAKEUP 4
DECL|macro|SCSI_RESET_NOT_RUNNING
mdefine_line|#define SCSI_RESET_NOT_RUNNING 5
DECL|macro|SCSI_RESET_ERROR
mdefine_line|#define SCSI_RESET_ERROR 6
DECL|macro|SCSI_RESET_SYNCHRONOUS
mdefine_line|#define SCSI_RESET_SYNCHRONOUS&t;&t;0x01
DECL|macro|SCSI_RESET_ASYNCHRONOUS
mdefine_line|#define SCSI_RESET_ASYNCHRONOUS&t;&t;0x02
DECL|macro|SCSI_RESET_SUGGEST_BUS_RESET
mdefine_line|#define SCSI_RESET_SUGGEST_BUS_RESET&t;0x04
DECL|macro|SCSI_RESET_SUGGEST_HOST_RESET
mdefine_line|#define SCSI_RESET_SUGGEST_HOST_RESET&t;0x08
DECL|macro|SCSI_RESET_BUS_RESET
mdefine_line|#define SCSI_RESET_BUS_RESET 0x100
DECL|macro|SCSI_RESET_HOST_RESET
mdefine_line|#define SCSI_RESET_HOST_RESET 0x200
DECL|macro|SCSI_RESET_ACTION
mdefine_line|#define SCSI_RESET_ACTION   0xff
eof
