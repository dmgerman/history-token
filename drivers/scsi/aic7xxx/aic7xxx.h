multiline_comment|/*&n; * Core definitions and data structures shareable across OS platforms.&n; *&n; * Copyright (c) 1994-2001 Justin T. Gibbs.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; * $Id: //depot/src/aic7xxx/aic7xxx.h#29 $&n; *&n; * $FreeBSD: src/sys/dev/aic7xxx/aic7xxx.h,v 1.30 2000/11/10 20:13:40 gibbs Exp $&n; */
macro_line|#ifndef _AIC7XXX_H_
DECL|macro|_AIC7XXX_H_
mdefine_line|#define _AIC7XXX_H_
multiline_comment|/* Register Definitions */
macro_line|#include &quot;aic7xxx_reg.h&quot;
multiline_comment|/************************* Forward Declarations *******************************/
r_struct
id|ahc_platform_data
suffix:semicolon
r_struct
id|scb_platform_data
suffix:semicolon
multiline_comment|/****************************** Useful Macros *********************************/
macro_line|#ifndef MAX
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a) &gt; (b)) ? (a) : (b))
macro_line|#endif
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a) &lt; (b)) ? (a) : (b))
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
DECL|macro|NUM_ELEMENTS
mdefine_line|#define NUM_ELEMENTS(array) (sizeof(array) / sizeof(*array))
DECL|macro|ALL_CHANNELS
mdefine_line|#define ALL_CHANNELS &squot;&bslash;0&squot;
DECL|macro|ALL_TARGETS_MASK
mdefine_line|#define ALL_TARGETS_MASK 0xFFFF
DECL|macro|INITIATOR_WILDCARD
mdefine_line|#define INITIATOR_WILDCARD&t;(~0)
DECL|macro|SCSIID_TARGET
mdefine_line|#define SCSIID_TARGET(ahc, scsiid) &bslash;&n;&t;(((scsiid) &amp; ((((ahc)-&gt;features &amp; AHC_TWIN) != 0) ? TWIN_TID : TID)) &bslash;&n;&t;&gt;&gt; TID_SHIFT)
DECL|macro|SCSIID_OUR_ID
mdefine_line|#define SCSIID_OUR_ID(scsiid) &bslash;&n;&t;((scsiid) &amp; OID)
DECL|macro|SCSIID_CHANNEL
mdefine_line|#define SCSIID_CHANNEL(ahc, scsiid) &bslash;&n;&t;((((ahc)-&gt;features &amp; AHC_TWIN) != 0) &bslash;&n;        ? ((((scsiid) &amp; TWIN_CHNLB) != 0) ? &squot;B&squot; : &squot;A&squot;) &bslash;&n;       : &squot;A&squot;)
DECL|macro|SCB_IS_SCSIBUS_B
mdefine_line|#define&t;SCB_IS_SCSIBUS_B(ahc, scb) &bslash;&n;&t;(SCSIID_CHANNEL(ahc, (scb)-&gt;hscb-&gt;scsiid) == &squot;B&squot;)
DECL|macro|SCB_GET_OUR_ID
mdefine_line|#define&t;SCB_GET_OUR_ID(scb) &bslash;&n;&t;SCSIID_OUR_ID((scb)-&gt;hscb-&gt;scsiid)
DECL|macro|SCB_GET_TARGET
mdefine_line|#define&t;SCB_GET_TARGET(ahc, scb) &bslash;&n;&t;SCSIID_TARGET((ahc), (scb)-&gt;hscb-&gt;scsiid)
DECL|macro|SCB_GET_CHANNEL
mdefine_line|#define&t;SCB_GET_CHANNEL(ahc, scb) &bslash;&n;&t;SCSIID_CHANNEL(ahc, (scb)-&gt;hscb-&gt;scsiid)
DECL|macro|SCB_GET_LUN
mdefine_line|#define&t;SCB_GET_LUN(scb) &bslash;&n;&t;((scb)-&gt;hscb-&gt;lun)
DECL|macro|SCB_GET_TARGET_OFFSET
mdefine_line|#define SCB_GET_TARGET_OFFSET(ahc, scb)&t;&bslash;&n;&t;(SCB_GET_TARGET(ahc, scb) + (SCB_IS_SCSIBUS_B(ahc, scb) ? 8 : 0))
DECL|macro|SCB_GET_TARGET_MASK
mdefine_line|#define SCB_GET_TARGET_MASK(ahc, scb) &bslash;&n;&t;(0x01 &lt;&lt; (SCB_GET_TARGET_OFFSET(ahc, scb)))
DECL|macro|TCL_TARGET_OFFSET
mdefine_line|#define TCL_TARGET_OFFSET(tcl) &bslash;&n;&t;((((tcl) &gt;&gt; 4) &amp; TID) &gt;&gt; 4)
DECL|macro|TCL_LUN
mdefine_line|#define TCL_LUN(tcl) &bslash;&n;&t;(tcl &amp; (AHC_NUM_LUNS - 1))
DECL|macro|BUILD_TCL
mdefine_line|#define BUILD_TCL(scsiid, lun) &bslash;&n;&t;((lun) | (((scsiid) &amp; TID) &lt;&lt; 4))
macro_line|#ifndef&t;AHC_TARGET_MODE
DECL|macro|AHC_TMODE_ENABLE
macro_line|#undef&t;AHC_TMODE_ENABLE
DECL|macro|AHC_TMODE_ENABLE
mdefine_line|#define&t;AHC_TMODE_ENABLE 0
macro_line|#endif
multiline_comment|/**************************** Driver Constants ********************************/
multiline_comment|/*&n; * The maximum number of supported targets.&n; */
DECL|macro|AHC_NUM_TARGETS
mdefine_line|#define AHC_NUM_TARGETS 16
multiline_comment|/*&n; * The maximum number of supported luns.&n; * The identify message only supports 64 luns in SPI3.&n; * You can have 2^64 luns when information unit transfers are enabled,&n; * but it is doubtful this driver will ever support IUTs.&n; */
DECL|macro|AHC_NUM_LUNS
mdefine_line|#define AHC_NUM_LUNS 64
multiline_comment|/*&n; * The maximum transfer per S/G segment.&n; */
DECL|macro|AHC_MAXTRANSFER_SIZE
mdefine_line|#define AHC_MAXTRANSFER_SIZE&t; 0x00ffffff&t;/* limited by 24bit counter */
multiline_comment|/*&n; * The maximum amount of SCB storage in hardware on a controller.&n; * This value represents an upper bound.  Controllers vary in the number&n; * they actually support.&n; */
DECL|macro|AHC_SCB_MAX
mdefine_line|#define AHC_SCB_MAX&t;255
multiline_comment|/*&n; * The maximum number of concurrent transactions supported per driver instance.&n; * Sequencer Control Blocks (SCBs) store per-transaction information.  Although&n; * the space for SCBs on the host adapter varies by model, the driver will&n; * page the SCBs between host and controller memory as needed.  We are limited&n; * to 253 because:&n; * &t;1) The 8bit nature of the RISC engine holds us to an 8bit value.&n; * &t;2) We reserve one value, 255, to represent the invalid element.&n; *&t;3) Our input queue scheme requires one SCB to always be reserved&n; *&t;   in advance of queuing any SCBs.  This takes us down to 254.&n; *&t;4) To handle our output queue correctly on machines that only&n; * &t;   support 32bit stores, we must clear the array 4 bytes at a&n; *&t;   time.  To avoid colliding with a DMA write from the sequencer,&n; *&t;   we must be sure that 4 slots are empty when we write to clear&n; *&t;   the queue.  This reduces us to 253 SCBs: 1 that just completed&n; *&t;   and the known three additional empty slots in the queue that&n; *&t;   precede it.&n; */
DECL|macro|AHC_MAX_QUEUE
mdefine_line|#define AHC_MAX_QUEUE&t;253
multiline_comment|/*&n; * Ring Buffer of incoming target commands.&n; * We allocate 256 to simplify the logic in the sequencer&n; * by using the natural wrap point of an 8bit counter.&n; */
DECL|macro|AHC_TMODE_CMDS
mdefine_line|#define AHC_TMODE_CMDS&t;256
multiline_comment|/* Reset line assertion time in us */
DECL|macro|AHC_BUSRESET_DELAY
mdefine_line|#define AHC_BUSRESET_DELAY&t;250
multiline_comment|/******************* Chip Characteristics/Operating Settings  *****************/
multiline_comment|/*&n; * Chip Type&n; * The chip order is from least sophisticated to most sophisticated.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AHC_NONE
id|AHC_NONE
op_assign
l_int|0x0000
comma
DECL|enumerator|AHC_CHIPID_MASK
id|AHC_CHIPID_MASK
op_assign
l_int|0x00FF
comma
DECL|enumerator|AHC_AIC7770
id|AHC_AIC7770
op_assign
l_int|0x0001
comma
DECL|enumerator|AHC_AIC7850
id|AHC_AIC7850
op_assign
l_int|0x0002
comma
DECL|enumerator|AHC_AIC7855
id|AHC_AIC7855
op_assign
l_int|0x0003
comma
DECL|enumerator|AHC_AIC7859
id|AHC_AIC7859
op_assign
l_int|0x0004
comma
DECL|enumerator|AHC_AIC7860
id|AHC_AIC7860
op_assign
l_int|0x0005
comma
DECL|enumerator|AHC_AIC7870
id|AHC_AIC7870
op_assign
l_int|0x0006
comma
DECL|enumerator|AHC_AIC7880
id|AHC_AIC7880
op_assign
l_int|0x0007
comma
DECL|enumerator|AHC_AIC7895
id|AHC_AIC7895
op_assign
l_int|0x0008
comma
DECL|enumerator|AHC_AIC7895C
id|AHC_AIC7895C
op_assign
l_int|0x0009
comma
DECL|enumerator|AHC_AIC7890
id|AHC_AIC7890
op_assign
l_int|0x000a
comma
DECL|enumerator|AHC_AIC7896
id|AHC_AIC7896
op_assign
l_int|0x000b
comma
DECL|enumerator|AHC_AIC7892
id|AHC_AIC7892
op_assign
l_int|0x000c
comma
DECL|enumerator|AHC_AIC7899
id|AHC_AIC7899
op_assign
l_int|0x000d
comma
DECL|enumerator|AHC_VL
id|AHC_VL
op_assign
l_int|0x0100
comma
multiline_comment|/* Bus type VL */
DECL|enumerator|AHC_EISA
id|AHC_EISA
op_assign
l_int|0x0200
comma
multiline_comment|/* Bus type EISA */
DECL|enumerator|AHC_PCI
id|AHC_PCI
op_assign
l_int|0x0400
comma
multiline_comment|/* Bus type PCI */
DECL|enumerator|AHC_BUS_MASK
id|AHC_BUS_MASK
op_assign
l_int|0x0F00
DECL|typedef|ahc_chip
)brace
id|ahc_chip
suffix:semicolon
multiline_comment|/*&n; * Features available in each chip type.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AHC_FENONE
id|AHC_FENONE
op_assign
l_int|0x00000
comma
DECL|enumerator|AHC_ULTRA
id|AHC_ULTRA
op_assign
l_int|0x00001
comma
multiline_comment|/* Supports 20MHz Transfers */
DECL|enumerator|AHC_ULTRA2
id|AHC_ULTRA2
op_assign
l_int|0x00002
comma
multiline_comment|/* Supports 40MHz Transfers */
DECL|enumerator|AHC_WIDE
id|AHC_WIDE
op_assign
l_int|0x00004
comma
multiline_comment|/* Wide Channel */
DECL|enumerator|AHC_TWIN
id|AHC_TWIN
op_assign
l_int|0x00008
comma
multiline_comment|/* Twin Channel */
DECL|enumerator|AHC_MORE_SRAM
id|AHC_MORE_SRAM
op_assign
l_int|0x00010
comma
multiline_comment|/* 80 bytes instead of 64 */
DECL|enumerator|AHC_CMD_CHAN
id|AHC_CMD_CHAN
op_assign
l_int|0x00020
comma
multiline_comment|/* Has a Command DMA Channel */
DECL|enumerator|AHC_QUEUE_REGS
id|AHC_QUEUE_REGS
op_assign
l_int|0x00040
comma
multiline_comment|/* Has Queue management registers */
DECL|enumerator|AHC_SG_PRELOAD
id|AHC_SG_PRELOAD
op_assign
l_int|0x00080
comma
multiline_comment|/* Can perform auto-SG preload */
DECL|enumerator|AHC_SPIOCAP
id|AHC_SPIOCAP
op_assign
l_int|0x00100
comma
multiline_comment|/* Has a Serial Port I/O Cap Register */
DECL|enumerator|AHC_MULTI_TID
id|AHC_MULTI_TID
op_assign
l_int|0x00200
comma
multiline_comment|/* Has bitmask of TIDs for select-in */
DECL|enumerator|AHC_HS_MAILBOX
id|AHC_HS_MAILBOX
op_assign
l_int|0x00400
comma
multiline_comment|/* Has HS_MAILBOX register */
DECL|enumerator|AHC_DT
id|AHC_DT
op_assign
l_int|0x00800
comma
multiline_comment|/* Double Transition transfers */
DECL|enumerator|AHC_NEW_TERMCTL
id|AHC_NEW_TERMCTL
op_assign
l_int|0x01000
comma
multiline_comment|/* Newer termination scheme */
DECL|enumerator|AHC_MULTI_FUNC
id|AHC_MULTI_FUNC
op_assign
l_int|0x02000
comma
multiline_comment|/* Multi-Function Twin Channel Device */
DECL|enumerator|AHC_LARGE_SCBS
id|AHC_LARGE_SCBS
op_assign
l_int|0x04000
comma
multiline_comment|/* 64byte SCBs */
DECL|enumerator|AHC_AUTORATE
id|AHC_AUTORATE
op_assign
l_int|0x08000
comma
multiline_comment|/* Automatic update of SCSIRATE/OFFSET*/
DECL|enumerator|AHC_AUTOPAUSE
id|AHC_AUTOPAUSE
op_assign
l_int|0x10000
comma
multiline_comment|/* Automatic pause on register access */
DECL|enumerator|AHC_TARGETMODE
id|AHC_TARGETMODE
op_assign
l_int|0x20000
comma
multiline_comment|/* Has tested target mode support */
DECL|enumerator|AHC_MULTIROLE
id|AHC_MULTIROLE
op_assign
l_int|0x40000
comma
multiline_comment|/* Space for two roles at a time */
DECL|enumerator|AHC_REMOVABLE
id|AHC_REMOVABLE
op_assign
l_int|0x80000
comma
multiline_comment|/* Hot-Swap supported */
DECL|enumerator|AHC_AIC7770_FE
id|AHC_AIC7770_FE
op_assign
id|AHC_FENONE
comma
multiline_comment|/*&n;&t; * The real 7850 does not support Ultra modes, but there are&n;&t; * several cards that use the generic 7850 PCI ID even though&n;&t; * they are using an Ultra capable chip (7859/7860).  We start&n;&t; * out with the AHC_ULTRA feature set and then check the DEVSTATUS&n;&t; * register to determine if the capability is really present.&n;&t; */
DECL|enumerator|AHC_AIC7850_FE
id|AHC_AIC7850_FE
op_assign
id|AHC_SPIOCAP
op_or
id|AHC_AUTOPAUSE
op_or
id|AHC_TARGETMODE
op_or
id|AHC_ULTRA
comma
DECL|enumerator|AHC_AIC7860_FE
id|AHC_AIC7860_FE
op_assign
id|AHC_AIC7850_FE
comma
DECL|enumerator|AHC_AIC7870_FE
id|AHC_AIC7870_FE
op_assign
id|AHC_TARGETMODE
comma
DECL|enumerator|AHC_AIC7880_FE
id|AHC_AIC7880_FE
op_assign
id|AHC_AIC7870_FE
op_or
id|AHC_ULTRA
comma
multiline_comment|/*&n;&t; * Although we have space for both the initiator and&n;&t; * target roles on ULTRA2 chips, we currently disable&n;&t; * the initiator role to allow multi-scsi-id target mode&n;&t; * configurations.  We can only respond on the same SCSI&n;&t; * ID as our initiator role if we allow initiator operation.&n;&t; * At some point, we should add a configuration knob to&n;&t; * allow both roles to be loaded.&n;&t; */
DECL|enumerator|AHC_AIC7890_FE
id|AHC_AIC7890_FE
op_assign
id|AHC_MORE_SRAM
op_or
id|AHC_CMD_CHAN
op_or
id|AHC_ULTRA2
op_or
id|AHC_QUEUE_REGS
op_or
id|AHC_SG_PRELOAD
op_or
id|AHC_MULTI_TID
op_or
id|AHC_HS_MAILBOX
op_or
id|AHC_NEW_TERMCTL
op_or
id|AHC_LARGE_SCBS
op_or
id|AHC_TARGETMODE
comma
DECL|enumerator|AHC_AIC7892_FE
id|AHC_AIC7892_FE
op_assign
id|AHC_AIC7890_FE
op_or
id|AHC_DT
op_or
id|AHC_AUTORATE
op_or
id|AHC_AUTOPAUSE
comma
DECL|enumerator|AHC_AIC7895_FE
id|AHC_AIC7895_FE
op_assign
id|AHC_AIC7880_FE
op_or
id|AHC_MORE_SRAM
op_or
id|AHC_AUTOPAUSE
op_or
id|AHC_CMD_CHAN
op_or
id|AHC_MULTI_FUNC
op_or
id|AHC_LARGE_SCBS
comma
DECL|enumerator|AHC_AIC7895C_FE
id|AHC_AIC7895C_FE
op_assign
id|AHC_AIC7895_FE
op_or
id|AHC_MULTI_TID
comma
DECL|enumerator|AHC_AIC7896_FE
id|AHC_AIC7896_FE
op_assign
id|AHC_AIC7890_FE
op_or
id|AHC_MULTI_FUNC
comma
DECL|enumerator|AHC_AIC7899_FE
id|AHC_AIC7899_FE
op_assign
id|AHC_AIC7892_FE
op_or
id|AHC_MULTI_FUNC
DECL|typedef|ahc_feature
)brace
id|ahc_feature
suffix:semicolon
multiline_comment|/*&n; * Bugs in the silicon that we work around in software.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AHC_BUGNONE
id|AHC_BUGNONE
op_assign
l_int|0x00
comma
multiline_comment|/*&n;&t; * On all chips prior to the U2 product line,&n;&t; * the WIDEODD S/G segment feature does not&n;&t; * work during scsi-&gt;HostBus transfers.&n;&t; */
DECL|enumerator|AHC_TMODE_WIDEODD_BUG
id|AHC_TMODE_WIDEODD_BUG
op_assign
l_int|0x01
comma
multiline_comment|/*&n;&t; * On the aic7890/91 Rev 0 chips, the autoflush&n;&t; * feature does not work.  A manual flush of&n;&t; * the DMA FIFO is required.&n;&t; */
DECL|enumerator|AHC_AUTOFLUSH_BUG
id|AHC_AUTOFLUSH_BUG
op_assign
l_int|0x02
comma
multiline_comment|/*&n;&t; * On many chips, cacheline streaming does not work.&n;&t; */
DECL|enumerator|AHC_CACHETHEN_BUG
id|AHC_CACHETHEN_BUG
op_assign
l_int|0x04
comma
multiline_comment|/*&n;&t; * On the aic7896/97 chips, cacheline&n;&t; * streaming must be enabled.&n;&t; */
DECL|enumerator|AHC_CACHETHEN_DIS_BUG
id|AHC_CACHETHEN_DIS_BUG
op_assign
l_int|0x08
comma
multiline_comment|/*&n;&t; * PCI 2.1 Retry failure on non-empty data fifo.&n;&t; */
DECL|enumerator|AHC_PCI_2_1_RETRY_BUG
id|AHC_PCI_2_1_RETRY_BUG
op_assign
l_int|0x10
comma
multiline_comment|/*&n;&t; * Controller does not handle cacheline residuals&n;&t; * properly on S/G segments if PCI MWI instructions&n;&t; * are allowed.&n;&t; */
DECL|enumerator|AHC_PCI_MWI_BUG
id|AHC_PCI_MWI_BUG
op_assign
l_int|0x20
comma
multiline_comment|/*&n;&t; * An SCB upload using the SCB channel&squot;s&n;&t; * auto array entry copy feature may &n;&t; * corrupt data.  This appears to only&n;&t; * occur on 66MHz systems.&n;&t; */
DECL|enumerator|AHC_SCBCHAN_UPLOAD_BUG
id|AHC_SCBCHAN_UPLOAD_BUG
op_assign
l_int|0x40
DECL|typedef|ahc_bug
)brace
id|ahc_bug
suffix:semicolon
multiline_comment|/*&n; * Configuration specific settings.&n; * The driver determines these settings by probing the&n; * chip/controller&squot;s configuration.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AHC_FNONE
id|AHC_FNONE
op_assign
l_int|0x000
comma
DECL|enumerator|AHC_PRIMARY_CHANNEL
id|AHC_PRIMARY_CHANNEL
op_assign
l_int|0x003
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t; * The channel that should&n;&t;&t;&t;&t;&t; * be probed first.&n;&t;&t;&t;&t;&t; */
DECL|enumerator|AHC_USEDEFAULTS
id|AHC_USEDEFAULTS
op_assign
l_int|0x004
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t; * For cards without an seeprom&n;&t;&t;&t;&t;&t; * or a BIOS to initialize the chip&squot;s&n;&t;&t;&t;&t;&t; * SRAM, we use the default target&n;&t;&t;&t;&t;&t; * settings.&n;&t;&t;&t;&t;&t; */
DECL|enumerator|AHC_SEQUENCER_DEBUG
id|AHC_SEQUENCER_DEBUG
op_assign
l_int|0x008
comma
DECL|enumerator|AHC_SHARED_SRAM
id|AHC_SHARED_SRAM
op_assign
l_int|0x010
comma
DECL|enumerator|AHC_LARGE_SEEPROM
id|AHC_LARGE_SEEPROM
op_assign
l_int|0x020
comma
multiline_comment|/* Uses C56_66 not C46 */
DECL|enumerator|AHC_RESET_BUS_A
id|AHC_RESET_BUS_A
op_assign
l_int|0x040
comma
DECL|enumerator|AHC_RESET_BUS_B
id|AHC_RESET_BUS_B
op_assign
l_int|0x080
comma
DECL|enumerator|AHC_EXTENDED_TRANS_A
id|AHC_EXTENDED_TRANS_A
op_assign
l_int|0x100
comma
DECL|enumerator|AHC_EXTENDED_TRANS_B
id|AHC_EXTENDED_TRANS_B
op_assign
l_int|0x200
comma
DECL|enumerator|AHC_TERM_ENB_A
id|AHC_TERM_ENB_A
op_assign
l_int|0x400
comma
DECL|enumerator|AHC_TERM_ENB_B
id|AHC_TERM_ENB_B
op_assign
l_int|0x800
comma
DECL|enumerator|AHC_INITIATORROLE
id|AHC_INITIATORROLE
op_assign
l_int|0x1000
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t;  * Allow initiator operations on&n;&t;&t;&t;&t;&t;  * this controller.&n;&t;&t;&t;&t;&t;  */
DECL|enumerator|AHC_TARGETROLE
id|AHC_TARGETROLE
op_assign
l_int|0x2000
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t;  * Allow target operations on this&n;&t;&t;&t;&t;&t;  * controller.&n;&t;&t;&t;&t;&t;  */
DECL|enumerator|AHC_NEWEEPROM_FMT
id|AHC_NEWEEPROM_FMT
op_assign
l_int|0x4000
comma
DECL|enumerator|AHC_RESOURCE_SHORTAGE
id|AHC_RESOURCE_SHORTAGE
op_assign
l_int|0x8000
comma
DECL|enumerator|AHC_TQINFIFO_BLOCKED
id|AHC_TQINFIFO_BLOCKED
op_assign
l_int|0x10000
comma
multiline_comment|/* Blocked waiting for ATIOs */
DECL|enumerator|AHC_INT50_SPEEDFLEX
id|AHC_INT50_SPEEDFLEX
op_assign
l_int|0x20000
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t;   * Internal 50pin connector&n;&t;&t;&t;&t;&t;   * sits behind an aic3860&n;&t;&t;&t;&t;&t;   */
DECL|enumerator|AHC_SCB_BTT
id|AHC_SCB_BTT
op_assign
l_int|0x40000
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t;   * The busy targets table is&n;&t;&t;&t;&t;&t;   * stored in SCB space rather&n;&t;&t;&t;&t;&t;   * than SRAM.&n;&t;&t;&t;&t;&t;   */
DECL|enumerator|AHC_BIOS_ENABLED
id|AHC_BIOS_ENABLED
op_assign
l_int|0x80000
comma
DECL|enumerator|AHC_ALL_INTERRUPTS
id|AHC_ALL_INTERRUPTS
op_assign
l_int|0x100000
comma
DECL|enumerator|AHC_PAGESCBS
id|AHC_PAGESCBS
op_assign
l_int|0x400000
comma
multiline_comment|/* Enable SCB paging */
DECL|enumerator|AHC_EDGE_INTERRUPT
id|AHC_EDGE_INTERRUPT
op_assign
l_int|0x800000
comma
multiline_comment|/* Device uses edge triggered ints */
DECL|enumerator|AHC_39BIT_ADDRESSING
id|AHC_39BIT_ADDRESSING
op_assign
l_int|0x1000000
multiline_comment|/* Use 39 bit addressing scheme. */
DECL|typedef|ahc_flag
)brace
id|ahc_flag
suffix:semicolon
multiline_comment|/************************* Hardware  SCB Definition ***************************/
multiline_comment|/*&n; * The driver keeps up to MAX_SCB scb structures per card in memory.  The SCB&n; * consists of a &quot;hardware SCB&quot; mirroring the fields availible on the card&n; * and additional information the kernel stores for each transaction.&n; *&n; * To minimize space utilization, a portion of the hardware scb stores&n; * different data during different portions of a SCSI transaction.&n; * As initialized by the host driver for the initiator role, this area&n; * contains the SCSI cdb (or a pointer to the  cdb) to be executed.  After&n; * the cdb has been presented to the target, this area serves to store&n; * residual transfer information and the SCSI status byte.&n; * For the target role, the contents of this area do not change, but&n; * still serve a different purpose than for the initiator role.  See&n; * struct target_data for details.&n; */
multiline_comment|/*&n; * Status information embedded in the shared poriton of&n; * an SCB after passing the cdb to the target.  The kernel&n; * driver will only read this data for transactions that&n; * complete abnormally (non-zero status byte).&n; */
DECL|struct|status_pkt
r_struct
id|status_pkt
(brace
DECL|member|residual_datacnt
r_uint32
id|residual_datacnt
suffix:semicolon
multiline_comment|/* Residual in the current S/G seg */
DECL|member|residual_sg_ptr
r_uint32
id|residual_sg_ptr
suffix:semicolon
multiline_comment|/* The next S/G for this transfer */
DECL|member|scsi_status
r_uint8
id|scsi_status
suffix:semicolon
multiline_comment|/* Standard SCSI status byte */
)brace
suffix:semicolon
multiline_comment|/*&n; * Target mode version of the shared data SCB segment.&n; */
DECL|struct|target_data
r_struct
id|target_data
(brace
DECL|member|target_phases
r_uint8
id|target_phases
suffix:semicolon
multiline_comment|/* Bitmap of phases to execute */
DECL|member|data_phase
r_uint8
id|data_phase
suffix:semicolon
multiline_comment|/* Data-In or Data-Out */
DECL|member|scsi_status
r_uint8
id|scsi_status
suffix:semicolon
multiline_comment|/* SCSI status to give to initiator */
DECL|member|initiator_tag
r_uint8
id|initiator_tag
suffix:semicolon
multiline_comment|/* Initiator&squot;s transaction tag */
)brace
suffix:semicolon
DECL|struct|hardware_scb
r_struct
id|hardware_scb
(brace
multiline_comment|/*0*/
r_union
(brace
multiline_comment|/*&n;&t;&t; * If the cdb is 12 bytes or less, we embed it directly&n;&t;&t; * in the SCB.  For longer cdbs, we embed the address&n;&t;&t; * of the cdb payload as seen by the chip and a DMA&n;&t;&t; * is used to pull it in.&n;&t;&t; */
DECL|member|cdb
r_uint8
id|cdb
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|cdb_ptr
r_uint32
id|cdb_ptr
suffix:semicolon
DECL|member|status
r_struct
id|status_pkt
id|status
suffix:semicolon
DECL|member|tdata
r_struct
id|target_data
id|tdata
suffix:semicolon
DECL|member|shared_data
)brace
id|shared_data
suffix:semicolon
multiline_comment|/*&n; * A word about residuals.&n; * The scb is presented to the sequencer with the dataptr and datacnt&n; * fields initialized to the contents of the first S/G element to&n; * transfer.  The sgptr field is initialized to the bus address for&n; * the S/G element that follows the first in the in core S/G array&n; * or&squot;ed with the SG_FULL_RESID flag.  Sgptr may point to an invalid&n; * S/G entry for this transfer (single S/G element transfer with the&n; * first elements address and length preloaded in the dataptr/datacnt&n; * fields).  If no transfer is to occur, sgptr is set to SG_LIST_NULL.&n; * The SG_FULL_RESID flag ensures that the residual will be correctly&n; * noted even if no data transfers occur.  Once the data phase is entered,&n; * the residual sgptr and datacnt are loaded from the sgptr and the&n; * datacnt fields.  After each S/G element&squot;s dataptr and length are&n; * loaded into the hardware, the residual sgptr is advanced.  After&n; * each S/G element is expired, its datacnt field is checked to see&n; * if the LAST_SEG flag is set.  If so, SG_LIST_NULL is set in the&n; * residual sg ptr and the transfer is considered complete.  If the&n; * sequencer determines that there is a residual in the tranfer, it&n; * will set the SG_RESID_VALID flag in sgptr and dma the scb back into&n; * host memory.  To sumarize:&n; *&n; * Sequencer:&n; *&t;o A residual has occurred if SG_FULL_RESID is set in sgptr,&n; *&t;  or residual_sgptr does not have SG_LIST_NULL set.&n; *&n; *&t;o We are transfering the last segment if residual_datacnt has&n; *&t;  the SG_LAST_SEG flag set.&n; *&n; * Host:&n; *&t;o A residual has occurred if a completed scb has the&n; *&t;  SG_RESID_VALID flag set.&n; *&n; *&t;o residual_sgptr and sgptr refer to the &quot;next&quot; sg entry&n; *&t;  and so may point beyond the last valid sg entry for the&n; *&t;  transfer.&n; */
DECL|member|dataptr
multiline_comment|/*12*/
r_uint32
id|dataptr
suffix:semicolon
DECL|member|datacnt
multiline_comment|/*16*/
r_uint32
id|datacnt
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Byte 3 (numbered from 0) of&n;&t;&t;&t;&t;&t; * the datacnt is really the&n;&t;&t;&t;&t;&t; * 4th byte in that data address.&n;&t;&t;&t;&t;&t; */
DECL|member|sgptr
multiline_comment|/*20*/
r_uint32
id|sgptr
suffix:semicolon
DECL|macro|SG_PTR_MASK
mdefine_line|#define SG_PTR_MASK&t;0xFFFFFFF8
DECL|member|control
multiline_comment|/*24*/
r_uint8
id|control
suffix:semicolon
multiline_comment|/* See SCB_CONTROL in aic7xxx.reg for details */
DECL|member|scsiid
multiline_comment|/*25*/
r_uint8
id|scsiid
suffix:semicolon
multiline_comment|/* what to load in the SCSIID register */
DECL|member|lun
multiline_comment|/*26*/
r_uint8
id|lun
suffix:semicolon
DECL|member|tag
multiline_comment|/*27*/
r_uint8
id|tag
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Index into our kernel SCB array.&n;&t;&t;&t;&t;&t; * Also used as the tag for tagged I/O&n;&t;&t;&t;&t;&t; */
DECL|member|cdb_len
multiline_comment|/*28*/
r_uint8
id|cdb_len
suffix:semicolon
DECL|member|scsirate
multiline_comment|/*29*/
r_uint8
id|scsirate
suffix:semicolon
multiline_comment|/* Value for SCSIRATE register */
DECL|member|scsioffset
multiline_comment|/*30*/
r_uint8
id|scsioffset
suffix:semicolon
multiline_comment|/* Value for SCSIOFFSET register */
DECL|member|next
multiline_comment|/*31*/
r_uint8
id|next
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Used for threading SCBs in the&n;&t;&t;&t;&t;&t; * &quot;Waiting for Selection&quot; and&n;&t;&t;&t;&t;&t; * &quot;Disconnected SCB&quot; lists down&n;&t;&t;&t;&t;&t; * in the sequencer.&n;&t;&t;&t;&t;&t; */
DECL|member|cdb32
multiline_comment|/*32*/
r_uint8
id|cdb32
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * CDB storage for cdbs of size&n;&t;&t;&t;&t;&t; * 13-&gt;32.  We store them here&n;&t;&t;&t;&t;&t; * because hardware scbs are&n;&t;&t;&t;&t;&t; * allocated from DMA safe&n;&t;&t;&t;&t;&t; * memory so we are guaranteed&n;&t;&t;&t;&t;&t; * the controller can access&n;&t;&t;&t;&t;&t; * this data.&n;&t;&t;&t;&t;&t; */
)brace
suffix:semicolon
multiline_comment|/************************ Kernel SCB Definitions ******************************/
multiline_comment|/*&n; * Some fields of the SCB are OS dependent.  Here we collect the&n; * definitions for elements that all OS platforms need to include&n; * in there SCB definition.&n; */
multiline_comment|/*&n; * Definition of a scatter/gather element as transfered to the controller.&n; * The aic7xxx chips only support a 24bit length.  We use the top byte of&n; * the length to store additional address bits and a flag to indicate&n; * that a given segment terminates the transfer.  This gives us an&n; * addressable range of 512GB on machines with 64bit PCI or with chips&n; * that can support dual address cycles on 32bit PCI busses.&n; */
DECL|struct|ahc_dma_seg
r_struct
id|ahc_dma_seg
(brace
DECL|member|addr
r_uint32
id|addr
suffix:semicolon
DECL|member|len
r_uint32
id|len
suffix:semicolon
DECL|macro|AHC_DMA_LAST_SEG
mdefine_line|#define&t;AHC_DMA_LAST_SEG&t;0x80000000
DECL|macro|AHC_SG_HIGH_ADDR_MASK
mdefine_line|#define&t;AHC_SG_HIGH_ADDR_MASK&t;0x7F000000
DECL|macro|AHC_SG_LEN_MASK
mdefine_line|#define&t;AHC_SG_LEN_MASK&t;&t;0x00FFFFFF
)brace
suffix:semicolon
DECL|struct|sg_map_node
r_struct
id|sg_map_node
(brace
DECL|member|sg_dmamap
id|bus_dmamap_t
id|sg_dmamap
suffix:semicolon
DECL|member|sg_physaddr
id|bus_addr_t
id|sg_physaddr
suffix:semicolon
DECL|member|sg_vaddr
r_struct
id|ahc_dma_seg
op_star
id|sg_vaddr
suffix:semicolon
id|SLIST_ENTRY
c_func
(paren
id|sg_map_node
)paren
id|links
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The current state of this SCB.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SCB_FREE
id|SCB_FREE
op_assign
l_int|0x0000
comma
DECL|enumerator|SCB_OTHERTCL_TIMEOUT
id|SCB_OTHERTCL_TIMEOUT
op_assign
l_int|0x0002
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t;  * Another device was active&n;&t;&t;&t;&t;&t;  * during the first timeout for&n;&t;&t;&t;&t;&t;  * this SCB so we gave ourselves&n;&t;&t;&t;&t;&t;  * an additional timeout period&n;&t;&t;&t;&t;&t;  * in case it was hogging the&n;&t;&t;&t;&t;&t;  * bus.&n;&t;&t;&t;&t;          */
DECL|enumerator|SCB_DEVICE_RESET
id|SCB_DEVICE_RESET
op_assign
l_int|0x0004
comma
DECL|enumerator|SCB_SENSE
id|SCB_SENSE
op_assign
l_int|0x0008
comma
DECL|enumerator|SCB_CDB32_PTR
id|SCB_CDB32_PTR
op_assign
l_int|0x0010
comma
DECL|enumerator|SCB_RECOVERY_SCB
id|SCB_RECOVERY_SCB
op_assign
l_int|0x0020
comma
DECL|enumerator|SCB_AUTO_NEGOTIATE
id|SCB_AUTO_NEGOTIATE
op_assign
l_int|0x0040
comma
multiline_comment|/* Negotiate to achieve goal. */
DECL|enumerator|SCB_NEGOTIATE
id|SCB_NEGOTIATE
op_assign
l_int|0x0080
comma
multiline_comment|/* Negotiation forced for command. */
DECL|enumerator|SCB_ABORT
id|SCB_ABORT
op_assign
l_int|0x1000
comma
DECL|enumerator|SCB_UNTAGGEDQ
id|SCB_UNTAGGEDQ
op_assign
l_int|0x2000
comma
DECL|enumerator|SCB_ACTIVE
id|SCB_ACTIVE
op_assign
l_int|0x4000
comma
DECL|enumerator|SCB_TARGET_IMMEDIATE
id|SCB_TARGET_IMMEDIATE
op_assign
l_int|0x8000
DECL|typedef|scb_flag
)brace
id|scb_flag
suffix:semicolon
DECL|struct|scb
r_struct
id|scb
(brace
DECL|member|hscb
r_struct
id|hardware_scb
op_star
id|hscb
suffix:semicolon
r_union
(brace
id|SLIST_ENTRY
c_func
(paren
id|scb
)paren
id|sle
suffix:semicolon
id|TAILQ_ENTRY
c_func
(paren
id|scb
)paren
id|tqe
suffix:semicolon
DECL|member|links
)brace
id|links
suffix:semicolon
id|LIST_ENTRY
c_func
(paren
id|scb
)paren
id|pending_links
suffix:semicolon
DECL|member|io_ctx
id|ahc_io_ctx_t
id|io_ctx
suffix:semicolon
DECL|member|ahc_softc
r_struct
id|ahc_softc
op_star
id|ahc_softc
suffix:semicolon
DECL|member|flags
id|scb_flag
id|flags
suffix:semicolon
macro_line|#ifndef __linux__
DECL|member|dmamap
id|bus_dmamap_t
id|dmamap
suffix:semicolon
macro_line|#endif
DECL|member|platform_data
r_struct
id|scb_platform_data
op_star
id|platform_data
suffix:semicolon
DECL|member|sg_map
r_struct
id|sg_map_node
op_star
id|sg_map
suffix:semicolon
DECL|member|sg_list
r_struct
id|ahc_dma_seg
op_star
id|sg_list
suffix:semicolon
DECL|member|sg_list_phys
id|bus_addr_t
id|sg_list_phys
suffix:semicolon
DECL|member|sg_count
id|u_int
id|sg_count
suffix:semicolon
multiline_comment|/* How full ahc_dma_seg is */
)brace
suffix:semicolon
DECL|struct|scb_data
r_struct
id|scb_data
(brace
id|SLIST_HEAD
c_func
(paren
comma
id|scb
)paren
id|free_scbs
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Pool of SCBs ready to be assigned&n;&t;&t;&t;&t;&t; * commands to execute.&n;&t;&t;&t;&t;&t; */
DECL|member|scbindex
r_struct
id|scb
op_star
id|scbindex
(braket
id|AHC_SCB_MAX
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Mapping from tag to SCB */
DECL|member|hscbs
r_struct
id|hardware_scb
op_star
id|hscbs
suffix:semicolon
multiline_comment|/* Array of hardware SCBs */
DECL|member|scbarray
r_struct
id|scb
op_star
id|scbarray
suffix:semicolon
multiline_comment|/* Array of kernel SCBs */
DECL|member|sense
r_struct
id|scsi_sense_data
op_star
id|sense
suffix:semicolon
multiline_comment|/* Per SCB sense data */
multiline_comment|/*&n;&t; * &quot;Bus&quot; addresses of our data structures.&n;&t; */
DECL|member|hscb_dmat
id|bus_dma_tag_t
id|hscb_dmat
suffix:semicolon
multiline_comment|/* dmat for our hardware SCB array */
DECL|member|hscb_dmamap
id|bus_dmamap_t
id|hscb_dmamap
suffix:semicolon
DECL|member|hscb_busaddr
id|bus_addr_t
id|hscb_busaddr
suffix:semicolon
DECL|member|sense_dmat
id|bus_dma_tag_t
id|sense_dmat
suffix:semicolon
DECL|member|sense_dmamap
id|bus_dmamap_t
id|sense_dmamap
suffix:semicolon
DECL|member|sense_busaddr
id|bus_addr_t
id|sense_busaddr
suffix:semicolon
DECL|member|sg_dmat
id|bus_dma_tag_t
id|sg_dmat
suffix:semicolon
multiline_comment|/* dmat for our sg segments */
id|SLIST_HEAD
c_func
(paren
comma
id|sg_map_node
)paren
id|sg_maps
suffix:semicolon
DECL|member|numscbs
r_uint8
id|numscbs
suffix:semicolon
DECL|member|maxhscbs
r_uint8
id|maxhscbs
suffix:semicolon
multiline_comment|/* Number of SCBs on the card */
DECL|member|init_level
r_uint8
id|init_level
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * How far we&squot;ve initialized&n;&t;&t;&t;&t;&t; * this structure.&n;&t;&t;&t;&t;&t; */
)brace
suffix:semicolon
multiline_comment|/************************ Target Mode Definitions *****************************/
multiline_comment|/*&n; * Connection desciptor for select-in requests in target mode.&n; */
DECL|struct|target_cmd
r_struct
id|target_cmd
(brace
DECL|member|scsiid
r_uint8
id|scsiid
suffix:semicolon
multiline_comment|/* Our ID and the initiator&squot;s ID */
DECL|member|identify
r_uint8
id|identify
suffix:semicolon
multiline_comment|/* Identify message */
DECL|member|bytes
r_uint8
id|bytes
(braket
l_int|22
)braket
suffix:semicolon
multiline_comment|/* &n;&t;&t;&t;&t; * Bytes contains any additional message&n;&t;&t;&t;&t; * bytes terminated by 0xFF.  The remainder&n;&t;&t;&t;&t; * is the cdb to execute.&n;&t;&t;&t;&t; */
DECL|member|cmd_valid
r_uint8
id|cmd_valid
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * When a command is complete, the firmware&n;&t;&t;&t;&t; * will set cmd_valid to all bits set.&n;&t;&t;&t;&t; * After the host has seen the command,&n;&t;&t;&t;&t; * the bits are cleared.  This allows us&n;&t;&t;&t;&t; * to just peek at host memory to determine&n;&t;&t;&t;&t; * if more work is complete. cmd_valid is on&n;&t;&t;&t;&t; * an 8 byte boundary to simplify setting&n;&t;&t;&t;&t; * it on aic7880 hardware which only has&n;&t;&t;&t;&t; * limited direct access to the DMA FIFO.&n;&t;&t;&t;&t; */
DECL|member|pad
r_uint8
id|pad
(braket
l_int|7
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Number of events we can buffer up if we run out&n; * of immediate notify ccbs.&n; */
DECL|macro|AHC_TMODE_EVENT_BUFFER_SIZE
mdefine_line|#define AHC_TMODE_EVENT_BUFFER_SIZE 8
DECL|struct|ahc_tmode_event
r_struct
id|ahc_tmode_event
(brace
DECL|member|initiator_id
r_uint8
id|initiator_id
suffix:semicolon
DECL|member|event_type
r_uint8
id|event_type
suffix:semicolon
multiline_comment|/* MSG type or EVENT_TYPE_BUS_RESET */
DECL|macro|EVENT_TYPE_BUS_RESET
mdefine_line|#define&t;EVENT_TYPE_BUS_RESET 0xFF
DECL|member|event_arg
r_uint8
id|event_arg
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Per enabled lun target mode state.&n; * As this state is directly influenced by the host OS&squot;es target mode&n; * environment, we let the OS module define it.  Forward declare the&n; * structure here so we can store arrays of them, etc. in OS neutral&n; * data structures.&n; */
macro_line|#ifdef AHC_TARGET_MODE 
DECL|struct|ahc_tmode_lstate
r_struct
id|ahc_tmode_lstate
(brace
DECL|member|path
r_struct
id|cam_path
op_star
id|path
suffix:semicolon
DECL|member|accept_tios
r_struct
id|ccb_hdr_slist
id|accept_tios
suffix:semicolon
DECL|member|immed_notifies
r_struct
id|ccb_hdr_slist
id|immed_notifies
suffix:semicolon
DECL|member|event_buffer
r_struct
id|ahc_tmode_event
id|event_buffer
(braket
id|AHC_TMODE_EVENT_BUFFER_SIZE
)braket
suffix:semicolon
DECL|member|event_r_idx
r_uint8
id|event_r_idx
suffix:semicolon
DECL|member|event_w_idx
r_uint8
id|event_w_idx
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else
r_struct
id|ahc_tmode_lstate
suffix:semicolon
macro_line|#endif
multiline_comment|/******************** Transfer Negotiation Datastructures *********************/
DECL|macro|AHC_TRANS_CUR
mdefine_line|#define AHC_TRANS_CUR&t;&t;0x01&t;/* Modify current neogtiation status */
DECL|macro|AHC_TRANS_ACTIVE
mdefine_line|#define AHC_TRANS_ACTIVE&t;0x03&t;/* Assume this target is on the bus */
DECL|macro|AHC_TRANS_GOAL
mdefine_line|#define AHC_TRANS_GOAL&t;&t;0x04&t;/* Modify negotiation goal */
DECL|macro|AHC_TRANS_USER
mdefine_line|#define AHC_TRANS_USER&t;&t;0x08&t;/* Modify user negotiation settings */
multiline_comment|/*&n; * Transfer Negotiation Information.&n; */
DECL|struct|ahc_transinfo
r_struct
id|ahc_transinfo
(brace
DECL|member|protocol_version
r_uint8
id|protocol_version
suffix:semicolon
multiline_comment|/* SCSI Revision level */
DECL|member|transport_version
r_uint8
id|transport_version
suffix:semicolon
multiline_comment|/* SPI Revision level */
DECL|member|width
r_uint8
id|width
suffix:semicolon
multiline_comment|/* Bus width */
DECL|member|period
r_uint8
id|period
suffix:semicolon
multiline_comment|/* Sync rate factor */
DECL|member|offset
r_uint8
id|offset
suffix:semicolon
multiline_comment|/* Sync offset */
DECL|member|ppr_options
r_uint8
id|ppr_options
suffix:semicolon
multiline_comment|/* Parallel Protocol Request options */
)brace
suffix:semicolon
multiline_comment|/*&n; * Per-initiator current, goal and user transfer negotiation information. */
DECL|struct|ahc_initiator_tinfo
r_struct
id|ahc_initiator_tinfo
(brace
DECL|member|scsirate
r_uint8
id|scsirate
suffix:semicolon
multiline_comment|/* Computed value for SCSIRATE reg */
DECL|member|curr
r_struct
id|ahc_transinfo
id|curr
suffix:semicolon
DECL|member|goal
r_struct
id|ahc_transinfo
id|goal
suffix:semicolon
DECL|member|user
r_struct
id|ahc_transinfo
id|user
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Per enabled target ID state.&n; * Pointers to lun target state as well as sync/wide negotiation information&n; * for each initiator&lt;-&gt;target mapping.  For the initiator role we pretend&n; * that we are the target and the targets are the initiators since the&n; * negotiation is the same regardless of role.&n; */
DECL|struct|ahc_tmode_tstate
r_struct
id|ahc_tmode_tstate
(brace
DECL|member|enabled_luns
r_struct
id|ahc_tmode_lstate
op_star
id|enabled_luns
(braket
id|AHC_NUM_LUNS
)braket
suffix:semicolon
DECL|member|transinfo
r_struct
id|ahc_initiator_tinfo
id|transinfo
(braket
id|AHC_NUM_TARGETS
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Per initiator state bitmasks.&n;&t; */
DECL|member|auto_negotiate
r_uint16
id|auto_negotiate
suffix:semicolon
multiline_comment|/* Auto Negotiation Required */
DECL|member|ultraenb
r_uint16
id|ultraenb
suffix:semicolon
multiline_comment|/* Using ultra sync rate  */
DECL|member|discenable
r_uint16
id|discenable
suffix:semicolon
multiline_comment|/* Disconnection allowed  */
DECL|member|tagenable
r_uint16
id|tagenable
suffix:semicolon
multiline_comment|/* Tagged Queuing allowed */
)brace
suffix:semicolon
multiline_comment|/*&n; * Data structure for our table of allowed synchronous transfer rates.&n; */
DECL|struct|ahc_syncrate
r_struct
id|ahc_syncrate
(brace
DECL|member|sxfr_u2
id|u_int
id|sxfr_u2
suffix:semicolon
multiline_comment|/* Value of the SXFR parameter for Ultra2+ Chips */
DECL|member|sxfr
id|u_int
id|sxfr
suffix:semicolon
multiline_comment|/* Value of the SXFR parameter for &lt;= Ultra Chips */
DECL|macro|ULTRA_SXFR
mdefine_line|#define&t;&t;ULTRA_SXFR 0x100&t;/* Rate Requires Ultra Mode set */
DECL|macro|ST_SXFR
mdefine_line|#define&t;&t;ST_SXFR&t;   0x010&t;/* Rate Single Transition Only */
DECL|macro|DT_SXFR
mdefine_line|#define&t;&t;DT_SXFR&t;   0x040&t;/* Rate Double Transition Only */
DECL|member|period
r_uint8
id|period
suffix:semicolon
multiline_comment|/* Period to send to SCSI target */
DECL|member|rate
r_char
op_star
id|rate
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The synchronouse transfer rate table.&n; */
r_extern
r_struct
id|ahc_syncrate
id|ahc_syncrates
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Indexes into our table of syncronous transfer rates.&n; */
DECL|macro|AHC_SYNCRATE_DT
mdefine_line|#define AHC_SYNCRATE_DT&t;&t;0
DECL|macro|AHC_SYNCRATE_ULTRA2
mdefine_line|#define AHC_SYNCRATE_ULTRA2&t;1
DECL|macro|AHC_SYNCRATE_ULTRA
mdefine_line|#define AHC_SYNCRATE_ULTRA&t;3
DECL|macro|AHC_SYNCRATE_FAST
mdefine_line|#define AHC_SYNCRATE_FAST&t;6
multiline_comment|/***************************** Lookup Tables **********************************/
multiline_comment|/*&n; * Phase -&gt; name and message out response&n; * to parity errors in each phase table. &n; */
DECL|struct|ahc_phase_table_entry
r_struct
id|ahc_phase_table_entry
(brace
DECL|member|phase
r_uint8
id|phase
suffix:semicolon
DECL|member|mesg_out
r_uint8
id|mesg_out
suffix:semicolon
multiline_comment|/* Message response to parity errors */
DECL|member|phasemsg
r_char
op_star
id|phasemsg
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/************************** Serial EEPROM Format ******************************/
DECL|struct|seeprom_config
r_struct
id|seeprom_config
(brace
multiline_comment|/*&n; * Per SCSI ID Configuration Flags&n; */
DECL|member|device_flags
r_uint16
id|device_flags
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* words 0-15 */
DECL|macro|CFXFER
mdefine_line|#define&t;&t;CFXFER&t;&t;0x0007&t;/* synchronous transfer rate */
DECL|macro|CFSYNCH
mdefine_line|#define&t;&t;CFSYNCH&t;&t;0x0008&t;/* enable synchronous transfer */
DECL|macro|CFDISC
mdefine_line|#define&t;&t;CFDISC&t;&t;0x0010&t;/* enable disconnection */
DECL|macro|CFWIDEB
mdefine_line|#define&t;&t;CFWIDEB&t;&t;0x0020&t;/* wide bus device */
DECL|macro|CFSYNCHISULTRA
mdefine_line|#define&t;&t;CFSYNCHISULTRA&t;0x0040&t;/* CFSYNCH is an ultra offset (2940AU)*/
DECL|macro|CFSYNCSINGLE
mdefine_line|#define&t;&t;CFSYNCSINGLE&t;0x0080&t;/* Single-Transition signalling */
DECL|macro|CFSTART
mdefine_line|#define&t;&t;CFSTART&t;&t;0x0100&t;/* send start unit SCSI command */
DECL|macro|CFINCBIOS
mdefine_line|#define&t;&t;CFINCBIOS&t;0x0200&t;/* include in BIOS scan */
DECL|macro|CFRNFOUND
mdefine_line|#define&t;&t;CFRNFOUND&t;0x0400&t;/* report even if not found */
DECL|macro|CFMULTILUNDEV
mdefine_line|#define&t;&t;CFMULTILUNDEV&t;0x0800&t;/* Probe multiple luns in BIOS scan */
DECL|macro|CFWBCACHEENB
mdefine_line|#define&t;&t;CFWBCACHEENB&t;0x4000&t;/* Enable W-Behind Cache on disks */
DECL|macro|CFWBCACHENOP
mdefine_line|#define&t;&t;CFWBCACHENOP&t;0xc000&t;/* Don&squot;t touch W-Behind Cache */
multiline_comment|/*&n; * BIOS Control Bits&n; */
DECL|member|bios_control
r_uint16
id|bios_control
suffix:semicolon
multiline_comment|/* word 16 */
DECL|macro|CFSUPREM
mdefine_line|#define&t;&t;CFSUPREM&t;0x0001&t;/* support all removeable drives */
DECL|macro|CFSUPREMB
mdefine_line|#define&t;&t;CFSUPREMB&t;0x0002&t;/* support removeable boot drives */
DECL|macro|CFBIOSEN
mdefine_line|#define&t;&t;CFBIOSEN&t;0x0004&t;/* BIOS enabled */
DECL|macro|CFBIOS_BUSSCAN
mdefine_line|#define&t;&t;CFBIOS_BUSSCAN&t;0x0008&t;/* Have the BIOS Scan the Bus */
DECL|macro|CFSM2DRV
mdefine_line|#define&t;&t;CFSM2DRV&t;0x0010&t;/* support more than two drives */
DECL|macro|CFSTPWLEVEL
mdefine_line|#define&t;&t;CFSTPWLEVEL&t;0x0010&t;/* Termination level control */
DECL|macro|CF284XEXTEND
mdefine_line|#define&t;&t;CF284XEXTEND&t;0x0020&t;/* extended translation (284x cards) */&t;
DECL|macro|CFCTRL_A
mdefine_line|#define&t;&t;CFCTRL_A&t;0x0020&t;/* BIOS displays Ctrl-A message */&t;
DECL|macro|CFTERM_MENU
mdefine_line|#define&t;&t;CFTERM_MENU&t;0x0040&t;/* BIOS displays termination menu */&t;
DECL|macro|CFEXTEND
mdefine_line|#define&t;&t;CFEXTEND&t;0x0080&t;/* extended translation enabled */
DECL|macro|CFSCAMEN
mdefine_line|#define&t;&t;CFSCAMEN&t;0x0100&t;/* SCAM enable */
DECL|macro|CFMSG_LEVEL
mdefine_line|#define&t;&t;CFMSG_LEVEL&t;0x0600&t;/* BIOS Message Level */
DECL|macro|CFMSG_VERBOSE
mdefine_line|#define&t;&t;&t;CFMSG_VERBOSE&t;0x0000
DECL|macro|CFMSG_SILENT
mdefine_line|#define&t;&t;&t;CFMSG_SILENT&t;0x0200
DECL|macro|CFMSG_DIAG
mdefine_line|#define&t;&t;&t;CFMSG_DIAG&t;0x0400
DECL|macro|CFBOOTCD
mdefine_line|#define&t;&t;CFBOOTCD&t;0x0800  /* Support Bootable CD-ROM */
multiline_comment|/*&t;&t;UNUSED&t;&t;0xff00&t;*/
multiline_comment|/*&n; * Host Adapter Control Bits&n; */
DECL|member|adapter_control
r_uint16
id|adapter_control
suffix:semicolon
multiline_comment|/* word 17 */
DECL|macro|CFAUTOTERM
mdefine_line|#define&t;&t;CFAUTOTERM&t;0x0001&t;/* Perform Auto termination */
DECL|macro|CFULTRAEN
mdefine_line|#define&t;&t;CFULTRAEN&t;0x0002&t;/* Ultra SCSI speed enable */
DECL|macro|CF284XSELTO
mdefine_line|#define&t;&t;CF284XSELTO     0x0003&t;/* Selection timeout (284x cards) */
DECL|macro|CF284XFIFO
mdefine_line|#define&t;&t;CF284XFIFO      0x000C&t;/* FIFO Threshold (284x cards) */
DECL|macro|CFSTERM
mdefine_line|#define&t;&t;CFSTERM&t;&t;0x0004&t;/* SCSI low byte termination */
DECL|macro|CFWSTERM
mdefine_line|#define&t;&t;CFWSTERM&t;0x0008&t;/* SCSI high byte termination */
DECL|macro|CFSPARITY
mdefine_line|#define&t;&t;CFSPARITY&t;0x0010&t;/* SCSI parity */
DECL|macro|CF284XSTERM
mdefine_line|#define&t;&t;CF284XSTERM     0x0020&t;/* SCSI low byte term (284x cards) */&t;
DECL|macro|CFMULTILUN
mdefine_line|#define&t;&t;CFMULTILUN&t;0x0020
DECL|macro|CFRESETB
mdefine_line|#define&t;&t;CFRESETB&t;0x0040&t;/* reset SCSI bus at boot */
DECL|macro|CFCLUSTERENB
mdefine_line|#define&t;&t;CFCLUSTERENB&t;0x0080&t;/* Cluster Enable */
DECL|macro|CFBOOTCHAN
mdefine_line|#define&t;&t;CFBOOTCHAN&t;0x0300&t;/* probe this channel first */
DECL|macro|CFBOOTCHANSHIFT
mdefine_line|#define&t;&t;CFBOOTCHANSHIFT 8
DECL|macro|CFSEAUTOTERM
mdefine_line|#define&t;&t;CFSEAUTOTERM&t;0x0400&t;/* Ultra2 Perform secondary Auto Term*/
DECL|macro|CFSELOWTERM
mdefine_line|#define&t;&t;CFSELOWTERM&t;0x0800&t;/* Ultra2 secondary low term */
DECL|macro|CFSEHIGHTERM
mdefine_line|#define&t;&t;CFSEHIGHTERM&t;0x1000&t;/* Ultra2 secondary high term */
DECL|macro|CFDOMAINVAL
mdefine_line|#define&t;&t;CFDOMAINVAL&t;0x4000&t;/* Perform Domain Validation*/
multiline_comment|/*&n; * Bus Release Time, Host Adapter ID&n; */
DECL|member|brtime_id
r_uint16
id|brtime_id
suffix:semicolon
multiline_comment|/* word 18 */
DECL|macro|CFSCSIID
mdefine_line|#define&t;&t;CFSCSIID&t;0x000f&t;/* host adapter SCSI ID */
multiline_comment|/*&t;&t;UNUSED&t;&t;0x00f0&t;*/
DECL|macro|CFBRTIME
mdefine_line|#define&t;&t;CFBRTIME&t;0xff00&t;/* bus release time */
multiline_comment|/*&n; * Maximum targets&n; */
DECL|member|max_targets
r_uint16
id|max_targets
suffix:semicolon
multiline_comment|/* word 19 */
DECL|macro|CFMAXTARG
mdefine_line|#define&t;&t;CFMAXTARG&t;0x00ff&t;/* maximum targets */
DECL|macro|CFBOOTLUN
mdefine_line|#define&t;&t;CFBOOTLUN&t;0x0f00&t;/* Lun to boot from */
DECL|macro|CFBOOTID
mdefine_line|#define&t;&t;CFBOOTID&t;0xf000&t;/* Target to boot from */
DECL|member|res_1
r_uint16
id|res_1
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* words 20-29 */
DECL|member|signature
r_uint16
id|signature
suffix:semicolon
multiline_comment|/* Signature == 0x250 */
DECL|macro|CFSIGNATURE
mdefine_line|#define&t;&t;CFSIGNATURE&t;0x250
DECL|macro|CFSIGNATURE2
mdefine_line|#define&t;&t;CFSIGNATURE2&t;0x300
DECL|member|checksum
r_uint16
id|checksum
suffix:semicolon
multiline_comment|/* word 31 */
)brace
suffix:semicolon
multiline_comment|/****************************  Message Buffer *********************************/
r_typedef
r_enum
(brace
DECL|enumerator|MSG_TYPE_NONE
id|MSG_TYPE_NONE
op_assign
l_int|0x00
comma
DECL|enumerator|MSG_TYPE_INITIATOR_MSGOUT
id|MSG_TYPE_INITIATOR_MSGOUT
op_assign
l_int|0x01
comma
DECL|enumerator|MSG_TYPE_INITIATOR_MSGIN
id|MSG_TYPE_INITIATOR_MSGIN
op_assign
l_int|0x02
comma
DECL|enumerator|MSG_TYPE_TARGET_MSGOUT
id|MSG_TYPE_TARGET_MSGOUT
op_assign
l_int|0x03
comma
DECL|enumerator|MSG_TYPE_TARGET_MSGIN
id|MSG_TYPE_TARGET_MSGIN
op_assign
l_int|0x04
DECL|typedef|ahc_msg_type
)brace
id|ahc_msg_type
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|MSGLOOP_IN_PROG
id|MSGLOOP_IN_PROG
comma
DECL|enumerator|MSGLOOP_MSGCOMPLETE
id|MSGLOOP_MSGCOMPLETE
comma
DECL|enumerator|MSGLOOP_TERMINATED
id|MSGLOOP_TERMINATED
DECL|typedef|msg_loop_stat
)brace
id|msg_loop_stat
suffix:semicolon
multiline_comment|/*********************** Software Configuration Structure *********************/
id|TAILQ_HEAD
c_func
(paren
id|scb_tailq
comma
id|scb
)paren
suffix:semicolon
DECL|struct|ahc_suspend_channel_state
r_struct
id|ahc_suspend_channel_state
(brace
DECL|member|scsiseq
r_uint8
id|scsiseq
suffix:semicolon
DECL|member|sxfrctl0
r_uint8
id|sxfrctl0
suffix:semicolon
DECL|member|sxfrctl1
r_uint8
id|sxfrctl1
suffix:semicolon
DECL|member|simode0
r_uint8
id|simode0
suffix:semicolon
DECL|member|simode1
r_uint8
id|simode1
suffix:semicolon
DECL|member|seltimer
r_uint8
id|seltimer
suffix:semicolon
DECL|member|seqctl
r_uint8
id|seqctl
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ahc_suspend_state
r_struct
id|ahc_suspend_state
(brace
DECL|member|channel
r_struct
id|ahc_suspend_channel_state
id|channel
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|optionmode
r_uint8
id|optionmode
suffix:semicolon
DECL|member|dscommand0
r_uint8
id|dscommand0
suffix:semicolon
DECL|member|dspcistatus
r_uint8
id|dspcistatus
suffix:semicolon
multiline_comment|/* hsmailbox */
DECL|member|crccontrol1
r_uint8
id|crccontrol1
suffix:semicolon
DECL|member|scbbaddr
r_uint8
id|scbbaddr
suffix:semicolon
multiline_comment|/* Host and sequencer SCB counts */
DECL|member|dff_thrsh
r_uint8
id|dff_thrsh
suffix:semicolon
DECL|member|scratch_ram
r_uint8
op_star
id|scratch_ram
suffix:semicolon
DECL|member|btt
r_uint8
op_star
id|btt
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|ahc_bus_intr_t
r_typedef
r_void
(paren
op_star
id|ahc_bus_intr_t
)paren
(paren
r_struct
id|ahc_softc
op_star
)paren
suffix:semicolon
DECL|struct|ahc_softc
r_struct
id|ahc_softc
(brace
DECL|member|tag
id|bus_space_tag_t
id|tag
suffix:semicolon
DECL|member|bsh
id|bus_space_handle_t
id|bsh
suffix:semicolon
macro_line|#ifndef __linux__
DECL|member|buffer_dmat
id|bus_dma_tag_t
id|buffer_dmat
suffix:semicolon
multiline_comment|/* dmat for buffer I/O */
macro_line|#endif
DECL|member|scb_data
r_struct
id|scb_data
op_star
id|scb_data
suffix:semicolon
DECL|member|next_queued_scb
r_struct
id|scb
op_star
id|next_queued_scb
suffix:semicolon
multiline_comment|/*&n;&t; * SCBs that have been sent to the controller&n;&t; */
id|LIST_HEAD
c_func
(paren
comma
id|scb
)paren
id|pending_scbs
suffix:semicolon
multiline_comment|/*&n;&t; * Counting lock for deferring the release of additional&n;&t; * untagged transactions from the untagged_queues.  When&n;&t; * the lock is decremented to 0, all queues in the&n;&t; * untagged_queues array are run.&n;&t; */
DECL|member|untagged_queue_lock
id|u_int
id|untagged_queue_lock
suffix:semicolon
multiline_comment|/*&n;&t; * Per-target queue of untagged-transactions.  The&n;&t; * transaction at the head of the queue is the&n;&t; * currently pending untagged transaction for the&n;&t; * target.  The driver only allows a single untagged&n;&t; * transaction per target.&n;&t; */
DECL|member|untagged_queues
r_struct
id|scb_tailq
id|untagged_queues
(braket
id|AHC_NUM_TARGETS
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Platform specific data.&n;&t; */
DECL|member|platform_data
r_struct
id|ahc_platform_data
op_star
id|platform_data
suffix:semicolon
multiline_comment|/*&n;&t; * Platform specific device information.&n;&t; */
DECL|member|dev_softc
id|ahc_dev_softc_t
id|dev_softc
suffix:semicolon
multiline_comment|/*&n;&t; * Bus specific device information.&n;&t; */
DECL|member|bus_intr
id|ahc_bus_intr_t
id|bus_intr
suffix:semicolon
multiline_comment|/*&n;&t; * Target mode related state kept on a per enabled lun basis.&n;&t; * Targets that are not enabled will have null entries.&n;&t; * As an initiator, we keep one target entry for our initiator&n;&t; * ID to store our sync/wide transfer settings.&n;&t; */
DECL|member|enabled_targets
r_struct
id|ahc_tmode_tstate
op_star
id|enabled_targets
(braket
id|AHC_NUM_TARGETS
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * The black hole device responsible for handling requests for&n;&t; * disabled luns on enabled targets.&n;&t; */
DECL|member|black_hole
r_struct
id|ahc_tmode_lstate
op_star
id|black_hole
suffix:semicolon
multiline_comment|/*&n;&t; * Device instance currently on the bus awaiting a continue TIO&n;&t; * for a command that was not given the disconnect priveledge.&n;&t; */
DECL|member|pending_device
r_struct
id|ahc_tmode_lstate
op_star
id|pending_device
suffix:semicolon
multiline_comment|/*&n;&t; * Card characteristics&n;&t; */
DECL|member|chip
id|ahc_chip
id|chip
suffix:semicolon
DECL|member|features
id|ahc_feature
id|features
suffix:semicolon
DECL|member|bugs
id|ahc_bug
id|bugs
suffix:semicolon
DECL|member|flags
id|ahc_flag
id|flags
suffix:semicolon
multiline_comment|/* Values to store in the SEQCTL register for pause and unpause */
DECL|member|unpause
r_uint8
id|unpause
suffix:semicolon
DECL|member|pause
r_uint8
id|pause
suffix:semicolon
multiline_comment|/* Command Queues */
DECL|member|qoutfifonext
r_uint8
id|qoutfifonext
suffix:semicolon
DECL|member|qinfifonext
r_uint8
id|qinfifonext
suffix:semicolon
DECL|member|qoutfifo
r_uint8
op_star
id|qoutfifo
suffix:semicolon
DECL|member|qinfifo
r_uint8
op_star
id|qinfifo
suffix:semicolon
multiline_comment|/* Critical Section Data */
DECL|member|critical_sections
r_struct
id|cs
op_star
id|critical_sections
suffix:semicolon
DECL|member|num_critical_sections
id|u_int
id|num_critical_sections
suffix:semicolon
multiline_comment|/* Links for chaining softcs */
id|TAILQ_ENTRY
c_func
(paren
id|ahc_softc
)paren
id|links
suffix:semicolon
multiline_comment|/* Channel Names (&squot;A&squot;, &squot;B&squot;, etc.) */
DECL|member|channel
r_char
id|channel
suffix:semicolon
DECL|member|channel_b
r_char
id|channel_b
suffix:semicolon
multiline_comment|/* Initiator Bus ID */
DECL|member|our_id
r_uint8
id|our_id
suffix:semicolon
DECL|member|our_id_b
r_uint8
id|our_id_b
suffix:semicolon
multiline_comment|/*&n;&t; * PCI error detection.&n;&t; */
DECL|member|unsolicited_ints
r_int
id|unsolicited_ints
suffix:semicolon
multiline_comment|/*&n;&t; * Target incoming command FIFO.&n;&t; */
DECL|member|targetcmds
r_struct
id|target_cmd
op_star
id|targetcmds
suffix:semicolon
DECL|member|tqinfifonext
r_uint8
id|tqinfifonext
suffix:semicolon
multiline_comment|/*&n;&t; * Incoming and outgoing message handling.&n;&t; */
DECL|member|send_msg_perror
r_uint8
id|send_msg_perror
suffix:semicolon
DECL|member|msg_type
id|ahc_msg_type
id|msg_type
suffix:semicolon
DECL|member|msgout_buf
r_uint8
id|msgout_buf
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* Message we are sending */
DECL|member|msgin_buf
r_uint8
id|msgin_buf
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* Message we are receiving */
DECL|member|msgout_len
id|u_int
id|msgout_len
suffix:semicolon
multiline_comment|/* Length of message to send */
DECL|member|msgout_index
id|u_int
id|msgout_index
suffix:semicolon
multiline_comment|/* Current index in msgout */
DECL|member|msgin_index
id|u_int
id|msgin_index
suffix:semicolon
multiline_comment|/* Current index in msgin */
multiline_comment|/*&n;&t; * Mapping information for data structures shared&n;&t; * between the sequencer and kernel.&n;&t; */
DECL|member|parent_dmat
id|bus_dma_tag_t
id|parent_dmat
suffix:semicolon
DECL|member|shared_data_dmat
id|bus_dma_tag_t
id|shared_data_dmat
suffix:semicolon
DECL|member|shared_data_dmamap
id|bus_dmamap_t
id|shared_data_dmamap
suffix:semicolon
DECL|member|shared_data_busaddr
id|bus_addr_t
id|shared_data_busaddr
suffix:semicolon
multiline_comment|/*&n;&t; * Bus address of the one byte buffer used to&n;&t; * work-around a DMA bug for chips &lt;= aic7880&n;&t; * in target mode.&n;&t; */
DECL|member|dma_bug_buf
id|bus_addr_t
id|dma_bug_buf
suffix:semicolon
multiline_comment|/* Information saved through suspend/resume cycles */
DECL|member|suspend_state
r_struct
id|ahc_suspend_state
id|suspend_state
suffix:semicolon
multiline_comment|/* Number of enabled target mode device on this card */
DECL|member|enabled_luns
id|u_int
id|enabled_luns
suffix:semicolon
multiline_comment|/* Initialization level of this data structure */
DECL|member|init_level
id|u_int
id|init_level
suffix:semicolon
multiline_comment|/* PCI cacheline size. */
DECL|member|pci_cachesize
id|u_int
id|pci_cachesize
suffix:semicolon
multiline_comment|/* Per-Unit descriptive information */
DECL|member|description
r_const
r_char
op_star
id|description
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|unit
r_int
id|unit
suffix:semicolon
multiline_comment|/* Selection Timer settings */
DECL|member|seltime
r_int
id|seltime
suffix:semicolon
DECL|member|seltime_b
r_int
id|seltime_b
suffix:semicolon
DECL|member|user_discenable
r_uint16
id|user_discenable
suffix:semicolon
multiline_comment|/* Disconnection allowed  */
DECL|member|user_tagenable
r_uint16
id|user_tagenable
suffix:semicolon
multiline_comment|/* Tagged Queuing allowed */
)brace
suffix:semicolon
id|TAILQ_HEAD
c_func
(paren
id|ahc_softc_tailq
comma
id|ahc_softc
)paren
suffix:semicolon
r_extern
r_struct
id|ahc_softc_tailq
id|ahc_tailq
suffix:semicolon
multiline_comment|/************************ Active Device Information ***************************/
r_typedef
r_enum
(brace
DECL|enumerator|ROLE_UNKNOWN
id|ROLE_UNKNOWN
comma
DECL|enumerator|ROLE_INITIATOR
id|ROLE_INITIATOR
comma
DECL|enumerator|ROLE_TARGET
id|ROLE_TARGET
DECL|typedef|role_t
)brace
id|role_t
suffix:semicolon
DECL|struct|ahc_devinfo
r_struct
id|ahc_devinfo
(brace
DECL|member|our_scsiid
r_int
id|our_scsiid
suffix:semicolon
DECL|member|target_offset
r_int
id|target_offset
suffix:semicolon
DECL|member|target_mask
r_uint16
id|target_mask
suffix:semicolon
DECL|member|target
id|u_int
id|target
suffix:semicolon
DECL|member|lun
id|u_int
id|lun
suffix:semicolon
DECL|member|channel
r_char
id|channel
suffix:semicolon
DECL|member|role
id|role_t
id|role
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Only guaranteed to be correct if not&n;&t;&t;&t;&t; * in the busfree state.&n;&t;&t;&t;&t; */
)brace
suffix:semicolon
multiline_comment|/****************************** PCI Structures ********************************/
DECL|typedef|ahc_device_setup_t
r_typedef
r_int
(paren
id|ahc_device_setup_t
)paren
(paren
r_struct
id|ahc_softc
op_star
)paren
suffix:semicolon
DECL|struct|ahc_pci_identity
r_struct
id|ahc_pci_identity
(brace
DECL|member|full_id
r_uint64
id|full_id
suffix:semicolon
DECL|member|id_mask
r_uint64
id|id_mask
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|setup
id|ahc_device_setup_t
op_star
id|setup
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ahc_pci_identity
id|ahc_pci_ident_table
(braket
)braket
suffix:semicolon
r_extern
r_const
id|u_int
id|ahc_num_pci_devs
suffix:semicolon
multiline_comment|/***************************** VL/EISA Declarations ***************************/
DECL|struct|aic7770_identity
r_struct
id|aic7770_identity
(brace
DECL|member|full_id
r_uint32
id|full_id
suffix:semicolon
DECL|member|id_mask
r_uint32
id|id_mask
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|setup
id|ahc_device_setup_t
op_star
id|setup
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|aic7770_identity
id|aic7770_ident_table
(braket
)braket
suffix:semicolon
r_extern
r_const
r_int
id|ahc_num_aic7770_devs
suffix:semicolon
DECL|macro|AHC_EISA_SLOT_OFFSET
mdefine_line|#define AHC_EISA_SLOT_OFFSET&t;0xc00
DECL|macro|AHC_EISA_IOSIZE
mdefine_line|#define AHC_EISA_IOSIZE&t;&t;0x100
multiline_comment|/*************************** Function Declarations ****************************/
multiline_comment|/******************************************************************************/
id|u_int
id|ahc_index_busy_tcl
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|tcl
)paren
suffix:semicolon
r_void
id|ahc_unbusy_tcl
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|tcl
)paren
suffix:semicolon
r_void
id|ahc_busy_tcl
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|tcl
comma
id|u_int
id|busyid
)paren
suffix:semicolon
multiline_comment|/***************************** PCI Front End *********************************/
r_struct
id|ahc_pci_identity
op_star
id|ahc_find_pci_device
c_func
(paren
id|ahc_dev_softc_t
)paren
suffix:semicolon
r_int
id|ahc_pci_config
c_func
(paren
r_struct
id|ahc_softc
op_star
comma
r_struct
id|ahc_pci_identity
op_star
)paren
suffix:semicolon
multiline_comment|/*************************** EISA/VL Front End ********************************/
r_struct
id|aic7770_identity
op_star
id|aic7770_find_device
c_func
(paren
r_uint32
)paren
suffix:semicolon
r_int
id|aic7770_config
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|aic7770_identity
op_star
)paren
suffix:semicolon
multiline_comment|/************************** SCB and SCB queue management **********************/
r_int
id|ahc_probe_scbs
c_func
(paren
r_struct
id|ahc_softc
op_star
)paren
suffix:semicolon
r_void
id|ahc_run_untagged_queues
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_void
id|ahc_run_untagged_queue
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb_tailq
op_star
id|queue
)paren
suffix:semicolon
r_void
id|ahc_qinfifo_requeue_tail
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_int
id|ahc_match_scb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
comma
r_int
id|target
comma
r_char
id|channel
comma
r_int
id|lun
comma
id|u_int
id|tag
comma
id|role_t
id|role
)paren
suffix:semicolon
multiline_comment|/****************************** Initialization ********************************/
r_struct
id|ahc_softc
op_star
id|ahc_alloc
c_func
(paren
r_void
op_star
id|platform_arg
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|ahc_softc_init
c_func
(paren
r_struct
id|ahc_softc
op_star
)paren
suffix:semicolon
r_void
id|ahc_controller_info
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
r_int
id|ahc_init
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_void
id|ahc_intr_enable
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_int
id|enable
)paren
suffix:semicolon
r_void
id|ahc_pause_and_flushwork
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_int
id|ahc_suspend
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_int
id|ahc_resume
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_void
id|ahc_softc_insert
c_func
(paren
r_struct
id|ahc_softc
op_star
)paren
suffix:semicolon
r_void
id|ahc_set_unit
c_func
(paren
r_struct
id|ahc_softc
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|ahc_set_name
c_func
(paren
r_struct
id|ahc_softc
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_void
id|ahc_alloc_scbs
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_void
id|ahc_free
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_int
id|ahc_reset
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_void
id|ahc_shutdown
c_func
(paren
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/*************************** Interrupt Services *******************************/
r_void
id|ahc_pci_intr
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_void
id|ahc_clear_intstat
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_void
id|ahc_run_qoutfifo
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
macro_line|#ifdef AHC_TARGET_MODE
r_void
id|ahc_run_tqinfifo
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_int
id|paused
)paren
suffix:semicolon
macro_line|#endif
r_void
id|ahc_handle_brkadrint
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_void
id|ahc_handle_seqint
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|intstat
)paren
suffix:semicolon
r_void
id|ahc_handle_scsiint
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|intstat
)paren
suffix:semicolon
r_void
id|ahc_clear_critical_section
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
multiline_comment|/***************************** Error Recovery *********************************/
r_typedef
r_enum
(brace
DECL|enumerator|SEARCH_COMPLETE
id|SEARCH_COMPLETE
comma
DECL|enumerator|SEARCH_COUNT
id|SEARCH_COUNT
comma
DECL|enumerator|SEARCH_REMOVE
id|SEARCH_REMOVE
DECL|typedef|ahc_search_action
)brace
id|ahc_search_action
suffix:semicolon
r_int
id|ahc_search_qinfifo
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_int
id|target
comma
r_char
id|channel
comma
r_int
id|lun
comma
id|u_int
id|tag
comma
id|role_t
id|role
comma
r_uint32
id|status
comma
id|ahc_search_action
id|action
)paren
suffix:semicolon
r_int
id|ahc_search_disc_list
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_int
id|target
comma
r_char
id|channel
comma
r_int
id|lun
comma
id|u_int
id|tag
comma
r_int
id|stop_on_first
comma
r_int
id|remove
comma
r_int
id|save_state
)paren
suffix:semicolon
r_void
id|ahc_freeze_devq
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_int
id|ahc_reset_channel
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_char
id|channel
comma
r_int
id|initiate_reset
)paren
suffix:semicolon
r_void
id|ahc_restart
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_void
id|ahc_calc_residual
c_func
(paren
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
multiline_comment|/*************************** Utility Functions ********************************/
r_struct
id|ahc_phase_table_entry
op_star
id|ahc_lookup_phase_entry
c_func
(paren
r_int
id|phase
)paren
suffix:semicolon
r_void
id|ahc_compile_devinfo
c_func
(paren
r_struct
id|ahc_devinfo
op_star
id|devinfo
comma
id|u_int
id|our_id
comma
id|u_int
id|target
comma
id|u_int
id|lun
comma
r_char
id|channel
comma
id|role_t
id|role
)paren
suffix:semicolon
multiline_comment|/************************** Transfer Negotiation ******************************/
r_struct
id|ahc_syncrate
op_star
id|ahc_find_syncrate
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
op_star
id|period
comma
id|u_int
op_star
id|ppr_options
comma
id|u_int
id|maxsync
)paren
suffix:semicolon
id|u_int
id|ahc_find_period
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|scsirate
comma
id|u_int
id|maxsync
)paren
suffix:semicolon
r_void
id|ahc_validate_offset
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|ahc_initiator_tinfo
op_star
id|tinfo
comma
r_struct
id|ahc_syncrate
op_star
id|syncrate
comma
id|u_int
op_star
id|offset
comma
r_int
id|wide
comma
id|role_t
id|role
)paren
suffix:semicolon
r_void
id|ahc_validate_width
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|ahc_initiator_tinfo
op_star
id|tinfo
comma
id|u_int
op_star
id|bus_width
comma
id|role_t
id|role
)paren
suffix:semicolon
r_int
id|ahc_update_neg_request
c_func
(paren
r_struct
id|ahc_softc
op_star
comma
r_struct
id|ahc_devinfo
op_star
comma
r_struct
id|ahc_tmode_tstate
op_star
comma
r_struct
id|ahc_initiator_tinfo
op_star
comma
r_int
multiline_comment|/*force*/
)paren
suffix:semicolon
r_void
id|ahc_set_width
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|ahc_devinfo
op_star
id|devinfo
comma
id|u_int
id|width
comma
id|u_int
id|type
comma
r_int
id|paused
)paren
suffix:semicolon
r_void
id|ahc_set_syncrate
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|ahc_devinfo
op_star
id|devinfo
comma
r_struct
id|ahc_syncrate
op_star
id|syncrate
comma
id|u_int
id|period
comma
id|u_int
id|offset
comma
id|u_int
id|ppr_options
comma
id|u_int
id|type
comma
r_int
id|paused
)paren
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|AHC_QUEUE_NONE
id|AHC_QUEUE_NONE
comma
DECL|enumerator|AHC_QUEUE_BASIC
id|AHC_QUEUE_BASIC
comma
DECL|enumerator|AHC_QUEUE_TAGGED
id|AHC_QUEUE_TAGGED
DECL|typedef|ahc_queue_alg
)brace
id|ahc_queue_alg
suffix:semicolon
r_void
id|ahc_set_tags
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|ahc_devinfo
op_star
id|devinfo
comma
id|ahc_queue_alg
id|alg
)paren
suffix:semicolon
multiline_comment|/**************************** Target Mode *************************************/
macro_line|#ifdef AHC_TARGET_MODE
r_void
id|ahc_send_lstate_events
c_func
(paren
r_struct
id|ahc_softc
op_star
comma
r_struct
id|ahc_tmode_lstate
op_star
)paren
suffix:semicolon
r_void
id|ahc_handle_en_lun
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|cam_sim
op_star
id|sim
comma
r_union
id|ccb
op_star
id|ccb
)paren
suffix:semicolon
id|cam_status
id|ahc_find_tmode_devs
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|cam_sim
op_star
id|sim
comma
r_union
id|ccb
op_star
id|ccb
comma
r_struct
id|ahc_tmode_tstate
op_star
op_star
id|tstate
comma
r_struct
id|ahc_tmode_lstate
op_star
op_star
id|lstate
comma
r_int
id|notfound_failure
)paren
suffix:semicolon
macro_line|#ifndef AHC_TMODE_ENABLE
DECL|macro|AHC_TMODE_ENABLE
mdefine_line|#define AHC_TMODE_ENABLE 0
macro_line|#endif
macro_line|#endif
multiline_comment|/******************************* Debug ***************************************/
r_void
id|ahc_print_scb
c_func
(paren
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_void
id|ahc_dump_card_state
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
macro_line|#endif /* _AIC7XXX_H_ */
eof
