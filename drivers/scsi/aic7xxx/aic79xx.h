multiline_comment|/*&n; * Core definitions and data structures shareable across OS platforms.&n; *&n; * Copyright (c) 1994-2002 Justin T. Gibbs.&n; * Copyright (c) 2000-2002 Adaptec Inc.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; *&n; * $Id: //depot/aic7xxx/aic7xxx/aic79xx.h#76 $&n; *&n; * $FreeBSD$&n; */
macro_line|#ifndef _AIC79XX_H_
DECL|macro|_AIC79XX_H_
mdefine_line|#define _AIC79XX_H_
multiline_comment|/* Register Definitions */
macro_line|#include &quot;aic79xx_reg.h&quot;
multiline_comment|/************************* Forward Declarations *******************************/
r_struct
id|ahd_platform_data
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
DECL|macro|SCB_LIST_NULL
mdefine_line|#define&t;SCB_LIST_NULL&t;&t;0xFF00
DECL|macro|SCB_LIST_NULL_LE
mdefine_line|#define&t;SCB_LIST_NULL_LE&t;(ahd_htole16(SCB_LIST_NULL))
DECL|macro|QOUTFIFO_ENTRY_VALID
mdefine_line|#define QOUTFIFO_ENTRY_VALID 0x8000
DECL|macro|QOUTFIFO_ENTRY_VALID_LE
mdefine_line|#define QOUTFIFO_ENTRY_VALID_LE (ahd_htole16(0x8000))
DECL|macro|SCBID_IS_NULL
mdefine_line|#define SCBID_IS_NULL(scbid) (((scbid) &amp; 0xFF00 ) == SCB_LIST_NULL)
DECL|macro|SCSIID_TARGET
mdefine_line|#define SCSIID_TARGET(ahd, scsiid)&t;&bslash;&n;&t;(((scsiid) &amp; TID) &gt;&gt; TID_SHIFT)
DECL|macro|SCSIID_OUR_ID
mdefine_line|#define SCSIID_OUR_ID(scsiid)&t;&t;&bslash;&n;&t;((scsiid) &amp; OID)
DECL|macro|SCSIID_CHANNEL
mdefine_line|#define SCSIID_CHANNEL(ahd, scsiid) (&squot;A&squot;)
DECL|macro|SCB_IS_SCSIBUS_B
mdefine_line|#define&t;SCB_IS_SCSIBUS_B(ahd, scb) (0)
DECL|macro|SCB_GET_OUR_ID
mdefine_line|#define&t;SCB_GET_OUR_ID(scb) &bslash;&n;&t;SCSIID_OUR_ID((scb)-&gt;hscb-&gt;scsiid)
DECL|macro|SCB_GET_TARGET
mdefine_line|#define&t;SCB_GET_TARGET(ahd, scb) &bslash;&n;&t;SCSIID_TARGET((ahd), (scb)-&gt;hscb-&gt;scsiid)
DECL|macro|SCB_GET_CHANNEL
mdefine_line|#define&t;SCB_GET_CHANNEL(ahd, scb) &bslash;&n;&t;SCSIID_CHANNEL(ahd, (scb)-&gt;hscb-&gt;scsiid)
DECL|macro|SCB_GET_LUN
mdefine_line|#define&t;SCB_GET_LUN(scb) &bslash;&n;&t;((scb)-&gt;hscb-&gt;lun)
DECL|macro|SCB_GET_TARGET_OFFSET
mdefine_line|#define SCB_GET_TARGET_OFFSET(ahd, scb)&t;&bslash;&n;&t;SCB_GET_TARGET(ahd, scb)
DECL|macro|SCB_GET_TARGET_MASK
mdefine_line|#define SCB_GET_TARGET_MASK(ahd, scb) &bslash;&n;&t;(0x01 &lt;&lt; (SCB_GET_TARGET_OFFSET(ahd, scb)))
macro_line|#ifdef AHD_DEBUG
DECL|macro|SCB_IS_SILENT
mdefine_line|#define SCB_IS_SILENT(scb)&t;&t;&t;&t;&t;&bslash;&n;&t;((ahd_debug &amp; AHD_SHOW_MASKED_ERRORS) == 0&t;&t;&bslash;&n;      &amp;&amp; (((scb)-&gt;flags &amp; SCB_SILENT) != 0))
macro_line|#else
DECL|macro|SCB_IS_SILENT
mdefine_line|#define SCB_IS_SILENT(scb)&t;&t;&t;&t;&t;&bslash;&n;&t;(((scb)-&gt;flags &amp; SCB_SILENT) != 0)
macro_line|#endif
multiline_comment|/*&n; * TCLs have the following format: TTTTLLLLLLLL&n; */
DECL|macro|TCL_TARGET_OFFSET
mdefine_line|#define TCL_TARGET_OFFSET(tcl) &bslash;&n;&t;((((tcl) &gt;&gt; 4) &amp; TID) &gt;&gt; 4)
DECL|macro|TCL_LUN
mdefine_line|#define TCL_LUN(tcl) &bslash;&n;&t;(tcl &amp; (AHD_NUM_LUNS - 1))
DECL|macro|BUILD_TCL
mdefine_line|#define BUILD_TCL(scsiid, lun) &bslash;&n;&t;((lun) | (((scsiid) &amp; TID) &lt;&lt; 4))
DECL|macro|BUILD_TCL_RAW
mdefine_line|#define BUILD_TCL_RAW(target, channel, lun) &bslash;&n;&t;((lun) | ((target) &lt;&lt; 8))
DECL|macro|SCB_GET_TAG
mdefine_line|#define SCB_GET_TAG(scb) &bslash;&n;&t;ahd_le16toh(scb-&gt;hscb-&gt;tag)
macro_line|#ifndef&t;AHD_TARGET_MODE
DECL|macro|AHD_TMODE_ENABLE
macro_line|#undef&t;AHD_TMODE_ENABLE
DECL|macro|AHD_TMODE_ENABLE
mdefine_line|#define&t;AHD_TMODE_ENABLE 0
macro_line|#endif
DECL|macro|AHD_BUILD_COL_IDX
mdefine_line|#define AHD_BUILD_COL_IDX(target, lun)&t;&t;&t;&t;&bslash;&n;&t;(((lun) &lt;&lt; 4) | target)
DECL|macro|AHD_GET_SCB_COL_IDX
mdefine_line|#define AHD_GET_SCB_COL_IDX(ahd, scb)&t;&t;&t;&t;&bslash;&n;&t;((SCB_GET_LUN(scb) &lt;&lt; 4) | SCB_GET_TARGET(ahd, scb))
DECL|macro|AHD_SET_SCB_COL_IDX
mdefine_line|#define AHD_SET_SCB_COL_IDX(scb, col_idx)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(scb)-&gt;hscb-&gt;scsiid = ((col_idx) &lt;&lt; TID_SHIFT) &amp; TID;&t;&t;&bslash;&n;&t;(scb)-&gt;hscb-&gt;lun = ((col_idx) &gt;&gt; 4) &amp; (AHD_NUM_LUNS_NONPKT-1);&t;&bslash;&n;} while (0)
DECL|macro|AHD_COPY_SCB_COL_IDX
mdefine_line|#define AHD_COPY_SCB_COL_IDX(dst, src)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;dst-&gt;hscb-&gt;scsiid = src-&gt;hscb-&gt;scsiid;&t;&t;&t;&bslash;&n;&t;dst-&gt;hscb-&gt;lun = src-&gt;hscb-&gt;lun;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|AHD_NEVER_COL_IDX
mdefine_line|#define&t;AHD_NEVER_COL_IDX 0xFFFF
multiline_comment|/**************************** Driver Constants ********************************/
multiline_comment|/*&n; * The maximum number of supported targets.&n; */
DECL|macro|AHD_NUM_TARGETS
mdefine_line|#define AHD_NUM_TARGETS 16
multiline_comment|/*&n; * The maximum number of supported luns.&n; * The identify message only supports 64 luns in non-packetized transfers.&n; * You can have 2^64 luns when information unit transfers are enabled,&n; * but until we see a need to support that many, we support 256.&n; */
DECL|macro|AHD_NUM_LUNS_NONPKT
mdefine_line|#define AHD_NUM_LUNS_NONPKT 64
DECL|macro|AHD_NUM_LUNS
mdefine_line|#define AHD_NUM_LUNS 256
multiline_comment|/*&n; * The maximum transfer per S/G segment.&n; */
DECL|macro|AHD_MAXTRANSFER_SIZE
mdefine_line|#define AHD_MAXTRANSFER_SIZE&t; 0x00ffffff&t;/* limited by 24bit counter */
multiline_comment|/*&n; * The maximum amount of SCB storage in hardware on a controller.&n; * This value represents an upper bound.  Due to software design,&n; * we may not be able to use this number.&n; */
DECL|macro|AHD_SCB_MAX
mdefine_line|#define AHD_SCB_MAX&t;512
multiline_comment|/*&n; * The maximum number of concurrent transactions supported per driver instance.&n; * Sequencer Control Blocks (SCBs) store per-transaction information.&n; */
DECL|macro|AHD_MAX_QUEUE
mdefine_line|#define AHD_MAX_QUEUE&t;AHD_SCB_MAX
multiline_comment|/*&n; * Define the size of our QIN and QOUT FIFOs.  They must be a power of 2&n; * in size and accomodate as many transactions as can be queued concurrently.&n; */
DECL|macro|AHD_QIN_SIZE
mdefine_line|#define&t;AHD_QIN_SIZE&t;AHD_MAX_QUEUE
DECL|macro|AHD_QOUT_SIZE
mdefine_line|#define&t;AHD_QOUT_SIZE&t;AHD_MAX_QUEUE
DECL|macro|AHD_QIN_WRAP
mdefine_line|#define AHD_QIN_WRAP(x) ((x) &amp; (AHD_QIN_SIZE-1))
multiline_comment|/*&n; * The maximum amount of SCB storage we allocate in host memory.&n; */
DECL|macro|AHD_SCB_MAX_ALLOC
mdefine_line|#define AHD_SCB_MAX_ALLOC AHD_MAX_QUEUE
multiline_comment|/*&n; * Ring Buffer of incoming target commands.&n; * We allocate 256 to simplify the logic in the sequencer&n; * by using the natural wrap point of an 8bit counter.&n; */
DECL|macro|AHD_TMODE_CMDS
mdefine_line|#define AHD_TMODE_CMDS&t;256
multiline_comment|/* Reset line assertion time in us */
DECL|macro|AHD_BUSRESET_DELAY
mdefine_line|#define AHD_BUSRESET_DELAY&t;25
multiline_comment|/******************* Chip Characteristics/Operating Settings  *****************/
multiline_comment|/*&n; * Chip Type&n; * The chip order is from least sophisticated to most sophisticated.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AHD_NONE
id|AHD_NONE
op_assign
l_int|0x0000
comma
DECL|enumerator|AHD_CHIPID_MASK
id|AHD_CHIPID_MASK
op_assign
l_int|0x00FF
comma
DECL|enumerator|AHD_AIC7901
id|AHD_AIC7901
op_assign
l_int|0x0001
comma
DECL|enumerator|AHD_AIC7902
id|AHD_AIC7902
op_assign
l_int|0x0002
comma
DECL|enumerator|AHD_AIC7901A
id|AHD_AIC7901A
op_assign
l_int|0x0003
comma
DECL|enumerator|AHD_PCI
id|AHD_PCI
op_assign
l_int|0x0100
comma
multiline_comment|/* Bus type PCI */
DECL|enumerator|AHD_PCIX
id|AHD_PCIX
op_assign
l_int|0x0200
comma
multiline_comment|/* Bus type PCIX */
DECL|enumerator|AHD_BUS_MASK
id|AHD_BUS_MASK
op_assign
l_int|0x0F00
DECL|typedef|ahd_chip
)brace
id|ahd_chip
suffix:semicolon
multiline_comment|/*&n; * Features available in each chip type.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AHD_FENONE
id|AHD_FENONE
op_assign
l_int|0x00000
comma
DECL|enumerator|AHD_WIDE
id|AHD_WIDE
op_assign
l_int|0x00001
comma
multiline_comment|/* Wide Channel */
DECL|enumerator|AHD_MULTI_FUNC
id|AHD_MULTI_FUNC
op_assign
l_int|0x00100
comma
multiline_comment|/* Multi-Function/Channel Device */
DECL|enumerator|AHD_TARGETMODE
id|AHD_TARGETMODE
op_assign
l_int|0x01000
comma
multiline_comment|/* Has tested target mode support */
DECL|enumerator|AHD_MULTIROLE
id|AHD_MULTIROLE
op_assign
l_int|0x02000
comma
multiline_comment|/* Space for two roles at a time */
DECL|enumerator|AHD_RTI
id|AHD_RTI
op_assign
l_int|0x04000
comma
multiline_comment|/* Retained Training Support */
DECL|enumerator|AHD_NEW_IOCELL_OPTS
id|AHD_NEW_IOCELL_OPTS
op_assign
l_int|0x08000
comma
multiline_comment|/* More Signal knobs in the IOCELL */
DECL|enumerator|AHD_NEW_DFCNTRL_OPTS
id|AHD_NEW_DFCNTRL_OPTS
op_assign
l_int|0x10000
comma
multiline_comment|/* SCSIENWRDIS bit */
DECL|enumerator|AHD_REMOVABLE
id|AHD_REMOVABLE
op_assign
l_int|0x00000
comma
multiline_comment|/* Hot-Swap supported - None so far*/
DECL|enumerator|AHD_AIC7901_FE
id|AHD_AIC7901_FE
op_assign
id|AHD_FENONE
comma
DECL|enumerator|AHD_AIC7902_FE
id|AHD_AIC7902_FE
op_assign
id|AHD_MULTI_FUNC
DECL|typedef|ahd_feature
)brace
id|ahd_feature
suffix:semicolon
multiline_comment|/*&n; * Bugs in the silicon that we work around in software.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AHD_BUGNONE
id|AHD_BUGNONE
op_assign
l_int|0x0000
comma
multiline_comment|/*&n;&t; * Rev A hardware fails to update LAST/CURR/NEXTSCB&n;&t; * correctly in certain packetized selection cases.&n;&t; */
DECL|enumerator|AHD_SENT_SCB_UPDATE_BUG
id|AHD_SENT_SCB_UPDATE_BUG
op_assign
l_int|0x0001
comma
multiline_comment|/* The wrong SCB is accessed to check the abort pending bit. */
DECL|enumerator|AHD_ABORT_LQI_BUG
id|AHD_ABORT_LQI_BUG
op_assign
l_int|0x0002
comma
multiline_comment|/* Packetized bitbucket crosses packet boundaries. */
DECL|enumerator|AHD_PKT_BITBUCKET_BUG
id|AHD_PKT_BITBUCKET_BUG
op_assign
l_int|0x0004
comma
multiline_comment|/* The selection timer runs twice as long as its setting. */
DECL|enumerator|AHD_LONG_SETIMO_BUG
id|AHD_LONG_SETIMO_BUG
op_assign
l_int|0x0008
comma
multiline_comment|/* The Non-LQ CRC error status is delayed until phase change. */
DECL|enumerator|AHD_NLQICRC_DELAYED_BUG
id|AHD_NLQICRC_DELAYED_BUG
op_assign
l_int|0x0010
comma
multiline_comment|/* The chip must be reset for all outgoing bus resets.  */
DECL|enumerator|AHD_SCSIRST_BUG
id|AHD_SCSIRST_BUG
op_assign
l_int|0x0020
comma
multiline_comment|/* Some PCIX fields must be saved and restored across chip reset. */
DECL|enumerator|AHD_PCIX_CHIPRST_BUG
id|AHD_PCIX_CHIPRST_BUG
op_assign
l_int|0x0040
comma
multiline_comment|/* MMAPIO is not functional in PCI-X mode.  */
DECL|enumerator|AHD_PCIX_MMAPIO_BUG
id|AHD_PCIX_MMAPIO_BUG
op_assign
l_int|0x0080
comma
multiline_comment|/* Bug workarounds that can be disabled on non-PCIX busses. */
DECL|enumerator|AHD_PCIX_BUG_MASK
id|AHD_PCIX_BUG_MASK
op_assign
id|AHD_PCIX_CHIPRST_BUG
op_or
id|AHD_PCIX_MMAPIO_BUG
comma
multiline_comment|/*&n;&t; * LQOSTOP0 status set even for forced selections with ATN&n;&t; * to perform non-packetized message delivery.&n;&t; */
DECL|enumerator|AHD_LQO_ATNO_BUG
id|AHD_LQO_ATNO_BUG
op_assign
l_int|0x0100
comma
multiline_comment|/* FIFO auto-flush does not always trigger.  */
DECL|enumerator|AHD_AUTOFLUSH_BUG
id|AHD_AUTOFLUSH_BUG
op_assign
l_int|0x0200
comma
multiline_comment|/* The CLRLQO registers are not self-clearing. */
DECL|enumerator|AHD_CLRLQO_AUTOCLR_BUG
id|AHD_CLRLQO_AUTOCLR_BUG
op_assign
l_int|0x0400
comma
multiline_comment|/* The PACKETIZED status bit refers to the previous connection. */
DECL|enumerator|AHD_PKTIZED_STATUS_BUG
id|AHD_PKTIZED_STATUS_BUG
op_assign
l_int|0x0800
comma
multiline_comment|/* &quot;Short Luns&quot; are not placed into outgoing LQ packets correctly. */
DECL|enumerator|AHD_PKT_LUN_BUG
id|AHD_PKT_LUN_BUG
op_assign
l_int|0x1000
comma
multiline_comment|/*&n;&t; * Only the FIFO allocated to the non-packetized connection may&n;&t; * be in use during a non-packetzied connection.&n;&t; */
DECL|enumerator|AHD_NONPACKFIFO_BUG
id|AHD_NONPACKFIFO_BUG
op_assign
l_int|0x2000
comma
multiline_comment|/*&n;&t; * Writing to a DFF SCBPTR register may fail if concurent with&n;&t; * a hardware write to the other DFF SCBPTR register.  This is&n;&t; * not currently a concern in our sequencer since all chips with&n;&t; * this bug have the AHD_NONPACKFIFO_BUG and all writes of concern&n;&t; * occur in non-packetized connections.&n;&t; */
DECL|enumerator|AHD_MDFF_WSCBPTR_BUG
id|AHD_MDFF_WSCBPTR_BUG
op_assign
l_int|0x4000
comma
multiline_comment|/* SGHADDR updates are slow. */
DECL|enumerator|AHD_REG_SLOW_SETTLE_BUG
id|AHD_REG_SLOW_SETTLE_BUG
op_assign
l_int|0x8000
comma
multiline_comment|/*&n;&t; * Changing the MODE_PTR coincident with an interrupt that&n;&t; * switches to a different mode will cause the interrupt to&n;&t; * be in the mode written outside of interrupt context.&n;&t; */
DECL|enumerator|AHD_SET_MODE_BUG
id|AHD_SET_MODE_BUG
op_assign
l_int|0x10000
comma
multiline_comment|/* Non-packetized busfree revision does not work. */
DECL|enumerator|AHD_BUSFREEREV_BUG
id|AHD_BUSFREEREV_BUG
op_assign
l_int|0x20000
comma
multiline_comment|/*&n;&t; * Paced transfers are indicated with a non-standard PPR&n;&t; * option bit in the neg table, 160MHz is indicated by&n;&t; * sync factor 0x7, and the offset if off by a factor of 2.&n;&t; */
DECL|enumerator|AHD_PACED_NEGTABLE_BUG
id|AHD_PACED_NEGTABLE_BUG
op_assign
l_int|0x40000
comma
multiline_comment|/* LQOOVERRUN false positives. */
DECL|enumerator|AHD_LQOOVERRUN_BUG
id|AHD_LQOOVERRUN_BUG
op_assign
l_int|0x80000
comma
multiline_comment|/*&n;&t; * Controller write to INTSTAT will lose to a host&n;&t; * write to CLRINT.&n;&t; */
DECL|enumerator|AHD_INTCOLLISION_BUG
id|AHD_INTCOLLISION_BUG
op_assign
l_int|0x100000
DECL|typedef|ahd_bug
)brace
id|ahd_bug
suffix:semicolon
multiline_comment|/*&n; * Configuration specific settings.&n; * The driver determines these settings by probing the&n; * chip/controller&squot;s configuration.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AHD_FNONE
id|AHD_FNONE
op_assign
l_int|0x00000
comma
DECL|enumerator|AHD_PRIMARY_CHANNEL
id|AHD_PRIMARY_CHANNEL
op_assign
l_int|0x00003
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t; * The channel that should&n;&t;&t;&t;&t;&t; * be probed first.&n;&t;&t;&t;&t;&t; */
DECL|enumerator|AHD_USEDEFAULTS
id|AHD_USEDEFAULTS
op_assign
l_int|0x00004
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t; * For cards without an seeprom&n;&t;&t;&t;&t;&t; * or a BIOS to initialize the chip&squot;s&n;&t;&t;&t;&t;&t; * SRAM, we use the default target&n;&t;&t;&t;&t;&t; * settings.&n;&t;&t;&t;&t;&t; */
DECL|enumerator|AHD_SEQUENCER_DEBUG
id|AHD_SEQUENCER_DEBUG
op_assign
l_int|0x00008
comma
DECL|enumerator|AHD_RESET_BUS_A
id|AHD_RESET_BUS_A
op_assign
l_int|0x00010
comma
DECL|enumerator|AHD_EXTENDED_TRANS_A
id|AHD_EXTENDED_TRANS_A
op_assign
l_int|0x00020
comma
DECL|enumerator|AHD_TERM_ENB_A
id|AHD_TERM_ENB_A
op_assign
l_int|0x00040
comma
DECL|enumerator|AHD_SPCHK_ENB_A
id|AHD_SPCHK_ENB_A
op_assign
l_int|0x00080
comma
DECL|enumerator|AHD_STPWLEVEL_A
id|AHD_STPWLEVEL_A
op_assign
l_int|0x00100
comma
DECL|enumerator|AHD_INITIATORROLE
id|AHD_INITIATORROLE
op_assign
l_int|0x00200
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Allow initiator operations on&n;&t;&t;&t;&t;&t; * this controller.&n;&t;&t;&t;&t;&t; */
DECL|enumerator|AHD_TARGETROLE
id|AHD_TARGETROLE
op_assign
l_int|0x00400
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Allow target operations on this&n;&t;&t;&t;&t;&t; * controller.&n;&t;&t;&t;&t;&t; */
DECL|enumerator|AHD_RESOURCE_SHORTAGE
id|AHD_RESOURCE_SHORTAGE
op_assign
l_int|0x00800
comma
DECL|enumerator|AHD_TQINFIFO_BLOCKED
id|AHD_TQINFIFO_BLOCKED
op_assign
l_int|0x01000
comma
multiline_comment|/* Blocked waiting for ATIOs */
DECL|enumerator|AHD_INT50_SPEEDFLEX
id|AHD_INT50_SPEEDFLEX
op_assign
l_int|0x02000
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Internal 50pin connector&n;&t;&t;&t;&t;&t; * sits behind an aic3860&n;&t;&t;&t;&t;&t; */
DECL|enumerator|AHD_BIOS_ENABLED
id|AHD_BIOS_ENABLED
op_assign
l_int|0x04000
comma
DECL|enumerator|AHD_ALL_INTERRUPTS
id|AHD_ALL_INTERRUPTS
op_assign
l_int|0x08000
comma
DECL|enumerator|AHD_39BIT_ADDRESSING
id|AHD_39BIT_ADDRESSING
op_assign
l_int|0x10000
comma
multiline_comment|/* Use 39 bit addressing scheme. */
DECL|enumerator|AHD_64BIT_ADDRESSING
id|AHD_64BIT_ADDRESSING
op_assign
l_int|0x20000
comma
multiline_comment|/* Use 64 bit addressing scheme. */
DECL|enumerator|AHD_CURRENT_SENSING
id|AHD_CURRENT_SENSING
op_assign
l_int|0x40000
comma
DECL|enumerator|AHD_SCB_CONFIG_USED
id|AHD_SCB_CONFIG_USED
op_assign
l_int|0x80000
comma
multiline_comment|/* No SEEPROM but SCB had info. */
DECL|enumerator|AHD_HP_BOARD
id|AHD_HP_BOARD
op_assign
l_int|0x100000
comma
DECL|enumerator|AHD_RESET_POLL_ACTIVE
id|AHD_RESET_POLL_ACTIVE
op_assign
l_int|0x200000
DECL|typedef|ahd_flag
)brace
id|ahd_flag
suffix:semicolon
multiline_comment|/************************* Hardware  SCB Definition ***************************/
multiline_comment|/*&n; * The driver keeps up to MAX_SCB scb structures per card in memory.  The SCB&n; * consists of a &quot;hardware SCB&quot; mirroring the fields availible on the card&n; * and additional information the kernel stores for each transaction.&n; *&n; * To minimize space utilization, a portion of the hardware scb stores&n; * different data during different portions of a SCSI transaction.&n; * As initialized by the host driver for the initiator role, this area&n; * contains the SCSI cdb (or a pointer to the  cdb) to be executed.  After&n; * the cdb has been presented to the target, this area serves to store&n; * residual transfer information and the SCSI status byte.&n; * For the target role, the contents of this area do not change, but&n; * still serve a different purpose than for the initiator role.  See&n; * struct target_data for details.&n; */
multiline_comment|/*&n; * Status information embedded in the shared poriton of&n; * an SCB after passing the cdb to the target.  The kernel&n; * driver will only read this data for transactions that&n; * complete abnormally.&n; */
DECL|struct|initiator_status
r_struct
id|initiator_status
(brace
DECL|member|residual_datacnt
r_uint32
id|residual_datacnt
suffix:semicolon
multiline_comment|/* Residual in the current S/G seg */
DECL|member|residual_sgptr
r_uint32
id|residual_sgptr
suffix:semicolon
multiline_comment|/* The next S/G for this transfer */
DECL|member|scsi_status
r_uint8
id|scsi_status
suffix:semicolon
multiline_comment|/* Standard SCSI status byte */
)brace
suffix:semicolon
DECL|struct|target_status
r_struct
id|target_status
(brace
DECL|member|residual_datacnt
r_uint32
id|residual_datacnt
suffix:semicolon
multiline_comment|/* Residual in the current S/G seg */
DECL|member|residual_sgptr
r_uint32
id|residual_sgptr
suffix:semicolon
multiline_comment|/* The next S/G for this transfer */
DECL|member|scsi_status
r_uint8
id|scsi_status
suffix:semicolon
multiline_comment|/* SCSI status to give to initiator */
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
DECL|member|initiator_tag
r_uint8
id|initiator_tag
suffix:semicolon
multiline_comment|/* Initiator&squot;s transaction tag */
)brace
suffix:semicolon
multiline_comment|/*&n; * Initiator mode SCB shared data area.&n; * If the embedded CDB is 12 bytes or less, we embed&n; * the sense buffer address in the SCB.  This allows&n; * us to retrieve sense information without interupting&n; * the host in packetized mode.&n; */
DECL|typedef|sense_addr_t
r_typedef
r_uint32
id|sense_addr_t
suffix:semicolon
DECL|macro|MAX_CDB_LEN
mdefine_line|#define MAX_CDB_LEN 16
DECL|macro|MAX_CDB_LEN_WITH_SENSE_ADDR
mdefine_line|#define MAX_CDB_LEN_WITH_SENSE_ADDR (MAX_CDB_LEN - sizeof(sense_addr_t))
DECL|union|initiator_data
r_union
id|initiator_data
(brace
DECL|member|cdbptr
r_uint64
id|cdbptr
suffix:semicolon
DECL|member|cdb
r_uint8
id|cdb
(braket
id|MAX_CDB_LEN
)braket
suffix:semicolon
r_struct
(brace
DECL|member|cdb
r_uint8
id|cdb
(braket
id|MAX_CDB_LEN_WITH_SENSE_ADDR
)braket
suffix:semicolon
DECL|member|sense_addr
id|sense_addr_t
id|sense_addr
suffix:semicolon
DECL|member|cdb_plus_saddr
)brace
id|cdb_plus_saddr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Target mode version of the shared data SCB segment.&n; */
DECL|struct|target_data
r_struct
id|target_data
(brace
DECL|member|spare
r_uint32
id|spare
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|scsi_status
r_uint8
id|scsi_status
suffix:semicolon
multiline_comment|/* SCSI status to give to initiator */
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
DECL|member|idata
r_union
id|initiator_data
id|idata
suffix:semicolon
DECL|member|tdata
r_struct
id|target_data
id|tdata
suffix:semicolon
DECL|member|istatus
r_struct
id|initiator_status
id|istatus
suffix:semicolon
DECL|member|tstatus
r_struct
id|target_status
id|tstatus
suffix:semicolon
DECL|member|shared_data
)brace
id|shared_data
suffix:semicolon
multiline_comment|/*&n; * A word about residuals.&n; * The scb is presented to the sequencer with the dataptr and datacnt&n; * fields initialized to the contents of the first S/G element to&n; * transfer.  The sgptr field is initialized to the bus address for&n; * the S/G element that follows the first in the in core S/G array&n; * or&squot;ed with the SG_FULL_RESID flag.  Sgptr may point to an invalid&n; * S/G entry for this transfer (single S/G element transfer with the&n; * first elements address and length preloaded in the dataptr/datacnt&n; * fields).  If no transfer is to occur, sgptr is set to SG_LIST_NULL.&n; * The SG_FULL_RESID flag ensures that the residual will be correctly&n; * noted even if no data transfers occur.  Once the data phase is entered,&n; * the residual sgptr and datacnt are loaded from the sgptr and the&n; * datacnt fields.  After each S/G element&squot;s dataptr and length are&n; * loaded into the hardware, the residual sgptr is advanced.  After&n; * each S/G element is expired, its datacnt field is checked to see&n; * if the LAST_SEG flag is set.  If so, SG_LIST_NULL is set in the&n; * residual sg ptr and the transfer is considered complete.  If the&n; * sequencer determines that there is a residual in the tranfer, or&n; * there is non-zero status, it will set the SG_STATUS_VALID flag in&n; * sgptr and dma the scb back into host memory.  To sumarize:&n; *&n; * Sequencer:&n; *&t;o A residual has occurred if SG_FULL_RESID is set in sgptr,&n; *&t;  or residual_sgptr does not have SG_LIST_NULL set.&n; *&n; *&t;o We are transfering the last segment if residual_datacnt has&n; *&t;  the SG_LAST_SEG flag set.&n; *&n; * Host:&n; *&t;o A residual can only have occurred if a completed scb has the&n; *&t;  SG_STATUS_VALID flag set.  Inspection of the SCSI status field,&n; *&t;  the residual_datacnt, and the residual_sgptr field will tell&n; *&t;  for sure.&n; *&n; *&t;o residual_sgptr and sgptr refer to the &quot;next&quot; sg entry&n; *&t;  and so may point beyond the last valid sg entry for the&n; *&t;  transfer.&n; */
DECL|macro|SG_PTR_MASK
mdefine_line|#define SG_PTR_MASK&t;0xFFFFFFF8
DECL|member|tag
multiline_comment|/*16*/
r_uint16
id|tag
suffix:semicolon
DECL|member|cdb_len
multiline_comment|/*18*/
r_uint8
id|cdb_len
suffix:semicolon
DECL|member|task_management
multiline_comment|/*19*/
r_uint8
id|task_management
suffix:semicolon
DECL|member|next_hscb_busaddr
multiline_comment|/*20*/
r_uint32
id|next_hscb_busaddr
suffix:semicolon
DECL|member|dataptr
multiline_comment|/*24*/
r_uint64
id|dataptr
suffix:semicolon
DECL|member|datacnt
multiline_comment|/*32*/
r_uint32
id|datacnt
suffix:semicolon
multiline_comment|/* Byte 3 is spare. */
DECL|member|sgptr
multiline_comment|/*36*/
r_uint32
id|sgptr
suffix:semicolon
DECL|member|control
multiline_comment|/*40*/
r_uint8
id|control
suffix:semicolon
multiline_comment|/* See SCB_CONTROL in aic79xx.reg for details */
DECL|member|scsiid
multiline_comment|/*41*/
r_uint8
id|scsiid
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Selection out Id&n;&t;&t;&t;&t; * Our Id (bits 0-3) Their ID (bits 4-7)&n;&t;&t;&t;&t; */
DECL|member|lun
multiline_comment|/*42*/
r_uint8
id|lun
suffix:semicolon
DECL|member|task_attribute
multiline_comment|/*43*/
r_uint8
id|task_attribute
suffix:semicolon
DECL|member|hscb_busaddr
multiline_comment|/*44*/
r_uint32
id|hscb_busaddr
suffix:semicolon
multiline_comment|/******* Long lun field only downloaded for full 8 byte lun support *******/
DECL|member|pkt_long_lun
multiline_comment|/*48*/
r_uint8
id|pkt_long_lun
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/******* Fields below are not Downloaded (Sequencer may use for scratch) ******/
DECL|member|spare
multiline_comment|/*56*/
r_uint8
id|spare
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/************************ Kernel SCB Definitions ******************************/
multiline_comment|/*&n; * Some fields of the SCB are OS dependent.  Here we collect the&n; * definitions for elements that all OS platforms need to include&n; * in there SCB definition.&n; */
multiline_comment|/*&n; * Definition of a scatter/gather element as transfered to the controller.&n; * The aic7xxx chips only support a 24bit length.  We use the top byte of&n; * the length to store additional address bits and a flag to indicate&n; * that a given segment terminates the transfer.  This gives us an&n; * addressable range of 512GB on machines with 64bit PCI or with chips&n; * that can support dual address cycles on 32bit PCI busses.&n; */
DECL|struct|ahd_dma_seg
r_struct
id|ahd_dma_seg
(brace
DECL|member|addr
r_uint32
id|addr
suffix:semicolon
DECL|member|len
r_uint32
id|len
suffix:semicolon
DECL|macro|AHD_DMA_LAST_SEG
mdefine_line|#define&t;AHD_DMA_LAST_SEG&t;0x80000000
DECL|macro|AHD_SG_HIGH_ADDR_MASK
mdefine_line|#define&t;AHD_SG_HIGH_ADDR_MASK&t;0x7F000000
DECL|macro|AHD_SG_LEN_MASK
mdefine_line|#define&t;AHD_SG_LEN_MASK&t;&t;0x00FFFFFF
)brace
suffix:semicolon
DECL|struct|ahd_dma64_seg
r_struct
id|ahd_dma64_seg
(brace
DECL|member|addr
r_uint64
id|addr
suffix:semicolon
DECL|member|len
r_uint32
id|len
suffix:semicolon
DECL|member|pad
r_uint32
id|pad
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|map_node
r_struct
id|map_node
(brace
DECL|member|dmamap
id|bus_dmamap_t
id|dmamap
suffix:semicolon
DECL|member|physaddr
id|bus_addr_t
id|physaddr
suffix:semicolon
DECL|member|vaddr
r_uint8
op_star
id|vaddr
suffix:semicolon
id|SLIST_ENTRY
c_func
(paren
id|map_node
)paren
id|links
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The current state of this SCB.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SCB_FLAG_NONE
id|SCB_FLAG_NONE
op_assign
l_int|0x00000
comma
DECL|enumerator|SCB_TRANSMISSION_ERROR
id|SCB_TRANSMISSION_ERROR
op_assign
l_int|0x00001
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t;   * We detected a parity or CRC&n;&t;&t;&t;&t;&t;   * error that has effected the&n;&t;&t;&t;&t;&t;   * payload of the command.  This&n;&t;&t;&t;&t;&t;   * flag is checked when normal&n;&t;&t;&t;&t;&t;   * status is returned to catch&n;&t;&t;&t;&t;&t;   * the case of a target not&n;&t;&t;&t;&t;&t;   * responding to our attempt&n;&t;&t;&t;&t;&t;   * to report the error.&n;&t;&t;&t;&t;&t;   */
DECL|enumerator|SCB_OTHERTCL_TIMEOUT
id|SCB_OTHERTCL_TIMEOUT
op_assign
l_int|0x00002
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t;   * Another device was active&n;&t;&t;&t;&t;&t;   * during the first timeout for&n;&t;&t;&t;&t;&t;   * this SCB so we gave ourselves&n;&t;&t;&t;&t;&t;   * an additional timeout period&n;&t;&t;&t;&t;&t;   * in case it was hogging the&n;&t;&t;&t;&t;&t;   * bus.&n;&t;&t;&t;&t;           */
DECL|enumerator|SCB_DEVICE_RESET
id|SCB_DEVICE_RESET
op_assign
l_int|0x00004
comma
DECL|enumerator|SCB_SENSE
id|SCB_SENSE
op_assign
l_int|0x00008
comma
DECL|enumerator|SCB_CDB32_PTR
id|SCB_CDB32_PTR
op_assign
l_int|0x00010
comma
DECL|enumerator|SCB_RECOVERY_SCB
id|SCB_RECOVERY_SCB
op_assign
l_int|0x00020
comma
DECL|enumerator|SCB_AUTO_NEGOTIATE
id|SCB_AUTO_NEGOTIATE
op_assign
l_int|0x00040
comma
multiline_comment|/* Negotiate to achieve goal. */
DECL|enumerator|SCB_NEGOTIATE
id|SCB_NEGOTIATE
op_assign
l_int|0x00080
comma
multiline_comment|/* Negotiation forced for command. */
DECL|enumerator|SCB_ABORT
id|SCB_ABORT
op_assign
l_int|0x00100
comma
DECL|enumerator|SCB_ACTIVE
id|SCB_ACTIVE
op_assign
l_int|0x00200
comma
DECL|enumerator|SCB_TARGET_IMMEDIATE
id|SCB_TARGET_IMMEDIATE
op_assign
l_int|0x00400
comma
DECL|enumerator|SCB_PACKETIZED
id|SCB_PACKETIZED
op_assign
l_int|0x00800
comma
DECL|enumerator|SCB_EXPECT_PPR_BUSFREE
id|SCB_EXPECT_PPR_BUSFREE
op_assign
l_int|0x01000
comma
DECL|enumerator|SCB_PKT_SENSE
id|SCB_PKT_SENSE
op_assign
l_int|0x02000
comma
DECL|enumerator|SCB_CMDPHASE_ABORT
id|SCB_CMDPHASE_ABORT
op_assign
l_int|0x04000
comma
DECL|enumerator|SCB_ON_COL_LIST
id|SCB_ON_COL_LIST
op_assign
l_int|0x08000
comma
DECL|enumerator|SCB_SILENT
id|SCB_SILENT
op_assign
l_int|0x10000
multiline_comment|/*&n;&t;&t;&t;&t;&t;   * Be quiet about transmission type&n;&t;&t;&t;&t;&t;   * errors.  They are expected and we&n;&t;&t;&t;&t;&t;   * don&squot;t want to upset the user.  This&n;&t;&t;&t;&t;&t;   * flag is typically used during DV.&n;&t;&t;&t;&t;&t;   */
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
id|LIST_ENTRY
c_func
(paren
id|scb
)paren
id|le
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
r_union
(brace
id|SLIST_ENTRY
c_func
(paren
id|scb
)paren
id|sle
suffix:semicolon
id|LIST_ENTRY
c_func
(paren
id|scb
)paren
id|le
suffix:semicolon
id|TAILQ_ENTRY
c_func
(paren
id|scb
)paren
id|tqe
suffix:semicolon
DECL|member|links2
)brace
id|links2
suffix:semicolon
DECL|macro|pending_links
mdefine_line|#define pending_links links2.le
DECL|macro|collision_links
mdefine_line|#define collision_links links2.le
DECL|member|col_scb
r_struct
id|scb
op_star
id|col_scb
suffix:semicolon
DECL|member|io_ctx
id|ahd_io_ctx_t
id|io_ctx
suffix:semicolon
DECL|member|ahd_softc
r_struct
id|ahd_softc
op_star
id|ahd_softc
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
DECL|member|hscb_map
r_struct
id|map_node
op_star
id|hscb_map
suffix:semicolon
DECL|member|sg_map
r_struct
id|map_node
op_star
id|sg_map
suffix:semicolon
DECL|member|sense_map
r_struct
id|map_node
op_star
id|sense_map
suffix:semicolon
DECL|member|sg_list
r_void
op_star
id|sg_list
suffix:semicolon
DECL|member|sense_data
r_uint8
op_star
id|sense_data
suffix:semicolon
DECL|member|sg_list_busaddr
id|bus_addr_t
id|sg_list_busaddr
suffix:semicolon
DECL|member|sense_busaddr
id|bus_addr_t
id|sense_busaddr
suffix:semicolon
DECL|member|sg_count
id|u_int
id|sg_count
suffix:semicolon
multiline_comment|/* How full ahd_dma_seg is */
DECL|macro|AHD_MAX_LQ_CRC_ERRORS
mdefine_line|#define&t;AHD_MAX_LQ_CRC_ERRORS 5
DECL|member|crc_retry_count
id|u_int
id|crc_retry_count
suffix:semicolon
)brace
suffix:semicolon
id|TAILQ_HEAD
c_func
(paren
id|scb_tailq
comma
id|scb
)paren
suffix:semicolon
id|LIST_HEAD
c_func
(paren
id|scb_list
comma
id|scb
)paren
suffix:semicolon
DECL|struct|scb_data
r_struct
id|scb_data
(brace
multiline_comment|/*&n;&t; * TAILQ of lists of free SCBs grouped by device&n;&t; * collision domains.&n;&t; */
DECL|member|free_scbs
r_struct
id|scb_tailq
id|free_scbs
suffix:semicolon
multiline_comment|/*&n;&t; * Per-device lists of SCBs whose tag ID would collide&n;&t; * with an already active tag on the device.&n;&t; */
DECL|member|free_scb_lists
r_struct
id|scb_list
id|free_scb_lists
(braket
id|AHD_NUM_TARGETS
op_star
id|AHD_NUM_LUNS_NONPKT
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * SCBs that will not collide with any active device.&n;&t; */
DECL|member|any_dev_free_scb_list
r_struct
id|scb_list
id|any_dev_free_scb_list
suffix:semicolon
multiline_comment|/*&n;&t; * Mapping from tag to SCB.&n;&t; */
DECL|member|scbindex
r_struct
id|scb
op_star
id|scbindex
(braket
id|AHD_SCB_MAX
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * &quot;Bus&quot; addresses of our data structures.&n;&t; */
DECL|member|hscb_dmat
id|bus_dma_tag_t
id|hscb_dmat
suffix:semicolon
multiline_comment|/* dmat for our hardware SCB array */
DECL|member|sg_dmat
id|bus_dma_tag_t
id|sg_dmat
suffix:semicolon
multiline_comment|/* dmat for our sg segments */
DECL|member|sense_dmat
id|bus_dma_tag_t
id|sense_dmat
suffix:semicolon
multiline_comment|/* dmat for our sense buffers */
id|SLIST_HEAD
c_func
(paren
comma
id|map_node
)paren
id|hscb_maps
suffix:semicolon
id|SLIST_HEAD
c_func
(paren
comma
id|map_node
)paren
id|sg_maps
suffix:semicolon
id|SLIST_HEAD
c_func
(paren
comma
id|map_node
)paren
id|sense_maps
suffix:semicolon
DECL|member|scbs_left
r_int
id|scbs_left
suffix:semicolon
multiline_comment|/* unallocated scbs in head map_node */
DECL|member|sgs_left
r_int
id|sgs_left
suffix:semicolon
multiline_comment|/* unallocated sgs in head map_node */
DECL|member|sense_left
r_int
id|sense_left
suffix:semicolon
multiline_comment|/* unallocated sense in head map_node */
DECL|member|numscbs
r_uint16
id|numscbs
suffix:semicolon
DECL|member|maxhscbs
r_uint16
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
DECL|macro|AHD_TMODE_EVENT_BUFFER_SIZE
mdefine_line|#define AHD_TMODE_EVENT_BUFFER_SIZE 8
DECL|struct|ahd_tmode_event
r_struct
id|ahd_tmode_event
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
macro_line|#ifdef AHD_TARGET_MODE 
DECL|struct|ahd_tmode_lstate
r_struct
id|ahd_tmode_lstate
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
id|ahd_tmode_event
id|event_buffer
(braket
id|AHD_TMODE_EVENT_BUFFER_SIZE
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
id|ahd_tmode_lstate
suffix:semicolon
macro_line|#endif
multiline_comment|/******************** Transfer Negotiation Datastructures *********************/
DECL|macro|AHD_TRANS_CUR
mdefine_line|#define AHD_TRANS_CUR&t;&t;0x01&t;/* Modify current neogtiation status */
DECL|macro|AHD_TRANS_ACTIVE
mdefine_line|#define AHD_TRANS_ACTIVE&t;0x03&t;/* Assume this target is on the bus */
DECL|macro|AHD_TRANS_GOAL
mdefine_line|#define AHD_TRANS_GOAL&t;&t;0x04&t;/* Modify negotiation goal */
DECL|macro|AHD_TRANS_USER
mdefine_line|#define AHD_TRANS_USER&t;&t;0x08&t;/* Modify user negotiation settings */
DECL|macro|AHD_PERIOD_10MHz
mdefine_line|#define AHD_PERIOD_10MHz&t;0x19
DECL|macro|AHD_WIDTH_UNKNOWN
mdefine_line|#define AHD_WIDTH_UNKNOWN&t;0xFF
DECL|macro|AHD_PERIOD_UNKNOWN
mdefine_line|#define AHD_PERIOD_UNKNOWN&t;0xFF
DECL|macro|AHD_OFFSET_UNKNOWN
mdefine_line|#define AHD_OFFSET_UNKNOWN&t;0x0
DECL|macro|AHD_PPR_OPTS_UNKNOWN
mdefine_line|#define AHD_PPR_OPTS_UNKNOWN&t;0xFF
multiline_comment|/*&n; * Transfer Negotiation Information.&n; */
DECL|struct|ahd_transinfo
r_struct
id|ahd_transinfo
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
DECL|struct|ahd_initiator_tinfo
r_struct
id|ahd_initiator_tinfo
(brace
DECL|member|curr
r_struct
id|ahd_transinfo
id|curr
suffix:semicolon
DECL|member|goal
r_struct
id|ahd_transinfo
id|goal
suffix:semicolon
DECL|member|user
r_struct
id|ahd_transinfo
id|user
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Per enabled target ID state.&n; * Pointers to lun target state as well as sync/wide negotiation information&n; * for each initiator&lt;-&gt;target mapping.  For the initiator role we pretend&n; * that we are the target and the targets are the initiators since the&n; * negotiation is the same regardless of role.&n; */
DECL|struct|ahd_tmode_tstate
r_struct
id|ahd_tmode_tstate
(brace
DECL|member|enabled_luns
r_struct
id|ahd_tmode_lstate
op_star
id|enabled_luns
(braket
id|AHD_NUM_LUNS
)braket
suffix:semicolon
DECL|member|transinfo
r_struct
id|ahd_initiator_tinfo
id|transinfo
(braket
id|AHD_NUM_TARGETS
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Per initiator state bitmasks.&n;&t; */
DECL|member|auto_negotiate
r_uint16
id|auto_negotiate
suffix:semicolon
multiline_comment|/* Auto Negotiation Required */
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
multiline_comment|/*&n; * Points of interest along the negotiated transfer scale.&n; */
DECL|macro|AHD_SYNCRATE_160
mdefine_line|#define AHD_SYNCRATE_160&t;0x8
DECL|macro|AHD_SYNCRATE_PACED
mdefine_line|#define AHD_SYNCRATE_PACED&t;0x8
DECL|macro|AHD_SYNCRATE_DT
mdefine_line|#define AHD_SYNCRATE_DT&t;&t;0x9
DECL|macro|AHD_SYNCRATE_ULTRA2
mdefine_line|#define AHD_SYNCRATE_ULTRA2&t;0xa
DECL|macro|AHD_SYNCRATE_ULTRA
mdefine_line|#define AHD_SYNCRATE_ULTRA&t;0xc
DECL|macro|AHD_SYNCRATE_FAST
mdefine_line|#define AHD_SYNCRATE_FAST&t;0x19
DECL|macro|AHD_SYNCRATE_MIN_DT
mdefine_line|#define AHD_SYNCRATE_MIN_DT&t;AHD_SYNCRATE_FAST
DECL|macro|AHD_SYNCRATE_SYNC
mdefine_line|#define AHD_SYNCRATE_SYNC&t;0x32
DECL|macro|AHD_SYNCRATE_MIN
mdefine_line|#define AHD_SYNCRATE_MIN&t;0x60
DECL|macro|AHD_SYNCRATE_ASYNC
mdefine_line|#define&t;AHD_SYNCRATE_ASYNC&t;0xFF
DECL|macro|AHD_SYNCRATE_MAX
mdefine_line|#define AHD_SYNCRATE_MAX&t;AHD_SYNCRATE_160
multiline_comment|/* Safe and valid period for async negotiations. */
DECL|macro|AHD_ASYNC_XFER_PERIOD
mdefine_line|#define&t;AHD_ASYNC_XFER_PERIOD&t;0x44
multiline_comment|/*&n; * In RevA, the synctable uses a 120MHz rate for the period&n; * factor 8 and 160MHz for the period factor 7.  The 120MHz&n; * rate never made it into the official SCSI spec, so we must&n; * compensate when setting the negotiation table for Rev A&n; * parts.&n; */
DECL|macro|AHD_SYNCRATE_REVA_120
mdefine_line|#define AHD_SYNCRATE_REVA_120&t;0x8
DECL|macro|AHD_SYNCRATE_REVA_160
mdefine_line|#define AHD_SYNCRATE_REVA_160&t;0x7
multiline_comment|/***************************** Lookup Tables **********************************/
multiline_comment|/*&n; * Phase -&gt; name and message out response&n; * to parity errors in each phase table. &n; */
DECL|struct|ahd_phase_table_entry
r_struct
id|ahd_phase_table_entry
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
mdefine_line|#define&t;&t;CFXFER&t;&t;0x003F&t;/* synchronous transfer rate */
DECL|macro|CFXFER_ASYNC
mdefine_line|#define&t;&t;&t;CFXFER_ASYNC&t;0x3F
DECL|macro|CFQAS
mdefine_line|#define&t;&t;CFQAS&t;&t;0x0040&t;/* Negotiate QAS */
DECL|macro|CFPACKETIZED
mdefine_line|#define&t;&t;CFPACKETIZED&t;0x0080&t;/* Negotiate Packetized Transfers */
DECL|macro|CFSTART
mdefine_line|#define&t;&t;CFSTART&t;&t;0x0100&t;/* send start unit SCSI command */
DECL|macro|CFINCBIOS
mdefine_line|#define&t;&t;CFINCBIOS&t;0x0200&t;/* include in BIOS scan */
DECL|macro|CFDISC
mdefine_line|#define&t;&t;CFDISC&t;&t;0x0400&t;/* enable disconnection */
DECL|macro|CFMULTILUNDEV
mdefine_line|#define&t;&t;CFMULTILUNDEV&t;0x0800&t;/* Probe multiple luns in BIOS scan */
DECL|macro|CFWIDEB
mdefine_line|#define&t;&t;CFWIDEB&t;&t;0x1000&t;/* wide bus device */
DECL|macro|CFHOSTMANAGED
mdefine_line|#define&t;&t;CFHOSTMANAGED&t;0x8000&t;/* Managed by a RAID controller */
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
DECL|macro|CFBIOSSTATE
mdefine_line|#define&t;&t;CFBIOSSTATE&t;0x000C&t;/* BIOS Action State */
DECL|macro|CFBS_DISABLED
mdefine_line|#define&t;&t;    CFBS_DISABLED&t;0x00
DECL|macro|CFBS_ENABLED
mdefine_line|#define&t;&t;    CFBS_ENABLED&t;0x04
DECL|macro|CFBS_DISABLED_SCAN
mdefine_line|#define&t;&t;    CFBS_DISABLED_SCAN&t;0x08
DECL|macro|CFENABLEDV
mdefine_line|#define&t;&t;CFENABLEDV&t;0x0010&t;/* Perform Domain Validation */
DECL|macro|CFCTRL_A
mdefine_line|#define&t;&t;CFCTRL_A&t;0x0020&t;/* BIOS displays Ctrl-A message */&t;
DECL|macro|CFSPARITY
mdefine_line|#define&t;&t;CFSPARITY&t;0x0040&t;/* SCSI parity */
DECL|macro|CFEXTEND
mdefine_line|#define&t;&t;CFEXTEND&t;0x0080&t;/* extended translation enabled */
DECL|macro|CFBOOTCD
mdefine_line|#define&t;&t;CFBOOTCD&t;0x0100  /* Support Bootable CD-ROM */
DECL|macro|CFMSG_LEVEL
mdefine_line|#define&t;&t;CFMSG_LEVEL&t;0x0600&t;/* BIOS Message Level */
DECL|macro|CFMSG_VERBOSE
mdefine_line|#define&t;&t;&t;CFMSG_VERBOSE&t;0x0000
DECL|macro|CFMSG_SILENT
mdefine_line|#define&t;&t;&t;CFMSG_SILENT&t;0x0200
DECL|macro|CFMSG_DIAG
mdefine_line|#define&t;&t;&t;CFMSG_DIAG&t;0x0400
DECL|macro|CFRESETB
mdefine_line|#define&t;&t;CFRESETB&t;0x0800&t;/* reset SCSI bus at boot */
multiline_comment|/*&t;&t;UNUSED&t;&t;0xf000&t;*/
multiline_comment|/*&n; * Host Adapter Control Bits&n; */
DECL|member|adapter_control
r_uint16
id|adapter_control
suffix:semicolon
multiline_comment|/* word 17 */
DECL|macro|CFAUTOTERM
mdefine_line|#define&t;&t;CFAUTOTERM&t;0x0001&t;/* Perform Auto termination */
DECL|macro|CFSTERM
mdefine_line|#define&t;&t;CFSTERM&t;&t;0x0002&t;/* SCSI low byte termination */
DECL|macro|CFWSTERM
mdefine_line|#define&t;&t;CFWSTERM&t;0x0004&t;/* SCSI high byte termination */
DECL|macro|CFSEAUTOTERM
mdefine_line|#define&t;&t;CFSEAUTOTERM&t;0x0008&t;/* Ultra2 Perform secondary Auto Term*/
DECL|macro|CFSELOWTERM
mdefine_line|#define&t;&t;CFSELOWTERM&t;0x0010&t;/* Ultra2 secondary low term */
DECL|macro|CFSEHIGHTERM
mdefine_line|#define&t;&t;CFSEHIGHTERM&t;0x0020&t;/* Ultra2 secondary high term */
DECL|macro|CFSTPWLEVEL
mdefine_line|#define&t;&t;CFSTPWLEVEL&t;0x0040&t;/* Termination level control */
DECL|macro|CFBIOSAUTOTERM
mdefine_line|#define&t;&t;CFBIOSAUTOTERM&t;0x0080&t;/* Perform Auto termination */
DECL|macro|CFTERM_MENU
mdefine_line|#define&t;&t;CFTERM_MENU&t;0x0100&t;/* BIOS displays termination menu */&t;
DECL|macro|CFCLUSTERENB
mdefine_line|#define&t;&t;CFCLUSTERENB&t;0x8000&t;/* Cluster Enable */
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
mdefine_line|#define&t;&t;CFBRTIME&t;0xff00&t;/* bus release time/PCI Latency Time */
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
multiline_comment|/* BIOS Signature */
DECL|macro|CFSIGNATURE
mdefine_line|#define&t;&t;CFSIGNATURE&t;0x400
DECL|member|checksum
r_uint16
id|checksum
suffix:semicolon
multiline_comment|/* word 31 */
)brace
suffix:semicolon
multiline_comment|/****************************** Flexport Logic ********************************/
DECL|macro|FLXADDR_TERMCTL
mdefine_line|#define FLXADDR_TERMCTL&t;&t;&t;0x0
DECL|macro|FLX_TERMCTL_ENSECHIGH
mdefine_line|#define&t;&t;FLX_TERMCTL_ENSECHIGH&t;0x8
DECL|macro|FLX_TERMCTL_ENSECLOW
mdefine_line|#define&t;&t;FLX_TERMCTL_ENSECLOW&t;0x4
DECL|macro|FLX_TERMCTL_ENPRIHIGH
mdefine_line|#define&t;&t;FLX_TERMCTL_ENPRIHIGH&t;0x2
DECL|macro|FLX_TERMCTL_ENPRILOW
mdefine_line|#define&t;&t;FLX_TERMCTL_ENPRILOW&t;0x1
DECL|macro|FLXADDR_ROMSTAT_CURSENSECTL
mdefine_line|#define FLXADDR_ROMSTAT_CURSENSECTL&t;0x1
DECL|macro|FLX_ROMSTAT_SEECFG
mdefine_line|#define&t;&t;FLX_ROMSTAT_SEECFG&t;0xF0
DECL|macro|FLX_ROMSTAT_EECFG
mdefine_line|#define&t;&t;FLX_ROMSTAT_EECFG&t;0x0F
DECL|macro|FLX_ROMSTAT_SEE_93C66
mdefine_line|#define&t;&t;FLX_ROMSTAT_SEE_93C66&t;0x00
DECL|macro|FLX_ROMSTAT_SEE_NONE
mdefine_line|#define&t;&t;FLX_ROMSTAT_SEE_NONE&t;0xF0
DECL|macro|FLX_ROMSTAT_EE_512x8
mdefine_line|#define&t;&t;FLX_ROMSTAT_EE_512x8&t;0x0
DECL|macro|FLX_ROMSTAT_EE_1MBx8
mdefine_line|#define&t;&t;FLX_ROMSTAT_EE_1MBx8&t;0x1
DECL|macro|FLX_ROMSTAT_EE_2MBx8
mdefine_line|#define&t;&t;FLX_ROMSTAT_EE_2MBx8&t;0x2
DECL|macro|FLX_ROMSTAT_EE_4MBx8
mdefine_line|#define&t;&t;FLX_ROMSTAT_EE_4MBx8&t;0x3
DECL|macro|FLX_ROMSTAT_EE_16MBx8
mdefine_line|#define&t;&t;FLX_ROMSTAT_EE_16MBx8&t;0x4
DECL|macro|CURSENSE_ENB
mdefine_line|#define &t;&t;CURSENSE_ENB&t;0x1
DECL|macro|FLXADDR_FLEXSTAT
mdefine_line|#define&t;FLXADDR_FLEXSTAT&t;&t;0x2
DECL|macro|FLX_FSTAT_BUSY
mdefine_line|#define&t;&t;FLX_FSTAT_BUSY&t;&t;0x1
DECL|macro|FLXADDR_CURRENT_STAT
mdefine_line|#define FLXADDR_CURRENT_STAT&t;&t;0x4
DECL|macro|FLX_CSTAT_SEC_HIGH
mdefine_line|#define&t;&t;FLX_CSTAT_SEC_HIGH&t;0xC0
DECL|macro|FLX_CSTAT_SEC_LOW
mdefine_line|#define&t;&t;FLX_CSTAT_SEC_LOW&t;0x30
DECL|macro|FLX_CSTAT_PRI_HIGH
mdefine_line|#define&t;&t;FLX_CSTAT_PRI_HIGH&t;0x0C
DECL|macro|FLX_CSTAT_PRI_LOW
mdefine_line|#define&t;&t;FLX_CSTAT_PRI_LOW&t;0x03
DECL|macro|FLX_CSTAT_MASK
mdefine_line|#define&t;&t;FLX_CSTAT_MASK&t;&t;0x03
DECL|macro|FLX_CSTAT_SHIFT
mdefine_line|#define&t;&t;FLX_CSTAT_SHIFT&t;&t;2
DECL|macro|FLX_CSTAT_OKAY
mdefine_line|#define&t;&t;FLX_CSTAT_OKAY&t;&t;0x0
DECL|macro|FLX_CSTAT_OVER
mdefine_line|#define&t;&t;FLX_CSTAT_OVER&t;&t;0x1
DECL|macro|FLX_CSTAT_UNDER
mdefine_line|#define&t;&t;FLX_CSTAT_UNDER&t;&t;0x2
DECL|macro|FLX_CSTAT_INVALID
mdefine_line|#define&t;&t;FLX_CSTAT_INVALID&t;0x3
r_int
id|ahd_read_seeprom
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_uint16
op_star
id|buf
comma
id|u_int
id|start_addr
comma
id|u_int
id|count
)paren
suffix:semicolon
r_int
id|ahd_write_seeprom
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_uint16
op_star
id|buf
comma
id|u_int
id|start_addr
comma
id|u_int
id|count
)paren
suffix:semicolon
r_int
id|ahd_wait_seeprom
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_int
id|ahd_verify_cksum
c_func
(paren
r_struct
id|seeprom_config
op_star
id|sc
)paren
suffix:semicolon
r_int
id|ahd_acquire_seeprom
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_void
id|ahd_release_seeprom
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
multiline_comment|/****************************  Message Buffer *********************************/
r_typedef
r_enum
(brace
DECL|enumerator|MSG_FLAG_NONE
id|MSG_FLAG_NONE
op_assign
l_int|0x00
comma
DECL|enumerator|MSG_FLAG_EXPECT_PPR_BUSFREE
id|MSG_FLAG_EXPECT_PPR_BUSFREE
op_assign
l_int|0x01
comma
DECL|enumerator|MSG_FLAG_IU_REQ_CHANGED
id|MSG_FLAG_IU_REQ_CHANGED
op_assign
l_int|0x02
comma
DECL|enumerator|MSG_FLAG_EXPECT_IDE_BUSFREE
id|MSG_FLAG_EXPECT_IDE_BUSFREE
op_assign
l_int|0x04
comma
DECL|enumerator|MSG_FLAG_EXPECT_QASREJ_BUSFREE
id|MSG_FLAG_EXPECT_QASREJ_BUSFREE
op_assign
l_int|0x08
comma
DECL|enumerator|MSG_FLAG_PACKETIZED
id|MSG_FLAG_PACKETIZED
op_assign
l_int|0x10
DECL|typedef|ahd_msg_flags
)brace
id|ahd_msg_flags
suffix:semicolon
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
DECL|typedef|ahd_msg_type
)brace
id|ahd_msg_type
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
DECL|struct|ahd_suspend_channel_state
r_struct
id|ahd_suspend_channel_state
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
DECL|struct|ahd_suspend_state
r_struct
id|ahd_suspend_state
(brace
DECL|member|channel
r_struct
id|ahd_suspend_channel_state
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
DECL|typedef|ahd_bus_intr_t
r_typedef
r_void
(paren
op_star
id|ahd_bus_intr_t
)paren
(paren
r_struct
id|ahd_softc
op_star
)paren
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|AHD_MODE_DFF0
id|AHD_MODE_DFF0
comma
DECL|enumerator|AHD_MODE_DFF1
id|AHD_MODE_DFF1
comma
DECL|enumerator|AHD_MODE_CCHAN
id|AHD_MODE_CCHAN
comma
DECL|enumerator|AHD_MODE_SCSI
id|AHD_MODE_SCSI
comma
DECL|enumerator|AHD_MODE_CFG
id|AHD_MODE_CFG
comma
DECL|enumerator|AHD_MODE_UNKNOWN
id|AHD_MODE_UNKNOWN
DECL|typedef|ahd_mode
)brace
id|ahd_mode
suffix:semicolon
DECL|macro|AHD_MK_MSK
mdefine_line|#define AHD_MK_MSK(x) (0x01 &lt;&lt; (x))
DECL|macro|AHD_MODE_DFF0_MSK
mdefine_line|#define AHD_MODE_DFF0_MSK&t;AHD_MK_MSK(AHD_MODE_DFF0)
DECL|macro|AHD_MODE_DFF1_MSK
mdefine_line|#define AHD_MODE_DFF1_MSK&t;AHD_MK_MSK(AHD_MODE_DFF1)
DECL|macro|AHD_MODE_CCHAN_MSK
mdefine_line|#define AHD_MODE_CCHAN_MSK&t;AHD_MK_MSK(AHD_MODE_CCHAN)
DECL|macro|AHD_MODE_SCSI_MSK
mdefine_line|#define AHD_MODE_SCSI_MSK&t;AHD_MK_MSK(AHD_MODE_SCSI)
DECL|macro|AHD_MODE_CFG_MSK
mdefine_line|#define AHD_MODE_CFG_MSK&t;AHD_MK_MSK(AHD_MODE_CFG)
DECL|macro|AHD_MODE_UNKNOWN_MSK
mdefine_line|#define AHD_MODE_UNKNOWN_MSK&t;AHD_MK_MSK(AHD_MODE_UNKNOWN)
DECL|macro|AHD_MODE_ANY_MSK
mdefine_line|#define AHD_MODE_ANY_MSK (~0)
DECL|typedef|ahd_mode_state
r_typedef
r_uint8
id|ahd_mode_state
suffix:semicolon
DECL|typedef|ahd_callback_t
r_typedef
r_void
id|ahd_callback_t
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|struct|ahd_softc
r_struct
id|ahd_softc
(brace
DECL|member|tags
id|bus_space_tag_t
id|tags
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|bshs
id|bus_space_handle_t
id|bshs
(braket
l_int|2
)braket
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
id|scb_data
suffix:semicolon
DECL|member|next_queued_hscb
r_struct
id|hardware_scb
op_star
id|next_queued_hscb
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
multiline_comment|/*&n;&t; * Current register window mode information.&n;&t; */
DECL|member|dst_mode
id|ahd_mode
id|dst_mode
suffix:semicolon
DECL|member|src_mode
id|ahd_mode
id|src_mode
suffix:semicolon
multiline_comment|/*&n;&t; * Saved register window mode information&n;&t; * used for restore on next unpause.&n;&t; */
DECL|member|saved_dst_mode
id|ahd_mode
id|saved_dst_mode
suffix:semicolon
DECL|member|saved_src_mode
id|ahd_mode
id|saved_src_mode
suffix:semicolon
multiline_comment|/*&n;&t; * Platform specific data.&n;&t; */
DECL|member|platform_data
r_struct
id|ahd_platform_data
op_star
id|platform_data
suffix:semicolon
multiline_comment|/*&n;&t; * Platform specific device information.&n;&t; */
DECL|member|dev_softc
id|ahd_dev_softc_t
id|dev_softc
suffix:semicolon
multiline_comment|/*&n;&t; * Bus specific device information.&n;&t; */
DECL|member|bus_intr
id|ahd_bus_intr_t
id|bus_intr
suffix:semicolon
multiline_comment|/*&n;&t; * Target mode related state kept on a per enabled lun basis.&n;&t; * Targets that are not enabled will have null entries.&n;&t; * As an initiator, we keep one target entry for our initiator&n;&t; * ID to store our sync/wide transfer settings.&n;&t; */
DECL|member|enabled_targets
r_struct
id|ahd_tmode_tstate
op_star
id|enabled_targets
(braket
id|AHD_NUM_TARGETS
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * The black hole device responsible for handling requests for&n;&t; * disabled luns on enabled targets.&n;&t; */
DECL|member|black_hole
r_struct
id|ahd_tmode_lstate
op_star
id|black_hole
suffix:semicolon
multiline_comment|/*&n;&t; * Device instance currently on the bus awaiting a continue TIO&n;&t; * for a command that was not given the disconnect priveledge.&n;&t; */
DECL|member|pending_device
r_struct
id|ahd_tmode_lstate
op_star
id|pending_device
suffix:semicolon
multiline_comment|/*&n;&t; * Timer handles for timer driven callbacks.&n;&t; */
DECL|member|reset_timer
id|ahd_timer_t
id|reset_timer
suffix:semicolon
multiline_comment|/*&n;&t; * Card characteristics&n;&t; */
DECL|member|chip
id|ahd_chip
id|chip
suffix:semicolon
DECL|member|features
id|ahd_feature
id|features
suffix:semicolon
DECL|member|bugs
id|ahd_bug
id|bugs
suffix:semicolon
DECL|member|flags
id|ahd_flag
id|flags
suffix:semicolon
DECL|member|seep_config
r_struct
id|seeprom_config
op_star
id|seep_config
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
r_uint16
id|qoutfifonext
suffix:semicolon
DECL|member|qoutfifonext_valid_tag
r_uint16
id|qoutfifonext_valid_tag
suffix:semicolon
DECL|member|qinfifonext
r_uint16
id|qinfifonext
suffix:semicolon
DECL|member|qinfifo
r_uint16
id|qinfifo
(braket
id|AHD_SCB_MAX
)braket
suffix:semicolon
DECL|member|qoutfifo
r_uint16
op_star
id|qoutfifo
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
multiline_comment|/* Buffer for handling packetized bitbucket. */
DECL|member|overrun_buf
r_uint8
op_star
id|overrun_buf
suffix:semicolon
multiline_comment|/* Links for chaining softcs */
id|TAILQ_ENTRY
c_func
(paren
id|ahd_softc
)paren
id|links
suffix:semicolon
multiline_comment|/* Channel Names (&squot;A&squot;, &squot;B&squot;, etc.) */
DECL|member|channel
r_char
id|channel
suffix:semicolon
multiline_comment|/* Initiator Bus ID */
DECL|member|our_id
r_uint8
id|our_id
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
DECL|member|msg_flags
id|ahd_msg_flags
id|msg_flags
suffix:semicolon
DECL|member|msg_type
id|ahd_msg_type
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
multiline_comment|/* Information saved through suspend/resume cycles */
DECL|member|suspend_state
r_struct
id|ahd_suspend_state
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
multiline_comment|/* IO Cell Parameters */
DECL|member|iocell_opts
r_uint8
id|iocell_opts
(braket
id|AHD_NUM_PER_DEV_ANNEXCOLS
)braket
suffix:semicolon
DECL|member|stack_size
id|u_int
id|stack_size
suffix:semicolon
DECL|member|saved_stack
r_uint16
op_star
id|saved_stack
suffix:semicolon
multiline_comment|/* Per-Unit descriptive information */
DECL|member|description
r_const
r_char
op_star
id|description
suffix:semicolon
DECL|member|bus_description
r_const
r_char
op_star
id|bus_description
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
id|ahd_softc_tailq
comma
id|ahd_softc
)paren
suffix:semicolon
r_extern
r_struct
id|ahd_softc_tailq
id|ahd_tailq
suffix:semicolon
multiline_comment|/*************************** IO Cell Configuration ****************************/
DECL|macro|AHD_PRECOMP_SLEW_INDEX
mdefine_line|#define&t;AHD_PRECOMP_SLEW_INDEX&t;&t;&t;&t;&t;&t;&bslash;&n;    (AHD_ANNEXCOL_PRECOMP_SLEW - AHD_ANNEXCOL_PER_DEV0)
DECL|macro|AHD_AMPLITUDE_INDEX
mdefine_line|#define&t;AHD_AMPLITUDE_INDEX&t;&t;&t;&t;&t;&t;&bslash;&n;    (AHD_ANNEXCOL_AMPLITUDE - AHD_ANNEXCOL_PER_DEV0)
DECL|macro|AHD_SET_SLEWRATE
mdefine_line|#define AHD_SET_SLEWRATE(ahd, new_slew)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (ahd)-&gt;iocell_opts[AHD_PRECOMP_SLEW_INDEX] &amp;= ~AHD_SLEWRATE_MASK;&t;&bslash;&n;    (ahd)-&gt;iocell_opts[AHD_PRECOMP_SLEW_INDEX] |=&t;&t;&t;&bslash;&n;&t;(((new_slew) &lt;&lt; AHD_SLEWRATE_SHIFT) &amp; AHD_SLEWRATE_MASK);&t;&bslash;&n;} while (0)
DECL|macro|AHD_SET_PRECOMP
mdefine_line|#define AHD_SET_PRECOMP(ahd, new_pcomp)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (ahd)-&gt;iocell_opts[AHD_PRECOMP_SLEW_INDEX] &amp;= ~AHD_PRECOMP_MASK;&t;&bslash;&n;    (ahd)-&gt;iocell_opts[AHD_PRECOMP_SLEW_INDEX] |=&t;&t;&t;&bslash;&n;&t;(((new_pcomp) &lt;&lt; AHD_PRECOMP_SHIFT) &amp; AHD_PRECOMP_MASK);&t;&bslash;&n;} while (0)
DECL|macro|AHD_SET_AMPLITUDE
mdefine_line|#define AHD_SET_AMPLITUDE(ahd, new_amp)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (ahd)-&gt;iocell_opts[AHD_AMPLITUDE_INDEX] &amp;= ~AHD_AMPLITUDE_MASK;&t;&bslash;&n;    (ahd)-&gt;iocell_opts[AHD_AMPLITUDE_INDEX] |=&t;&t;&t;&t;&bslash;&n;&t;(((new_amp) &lt;&lt; AHD_AMPLITUDE_SHIFT) &amp; AHD_AMPLITUDE_MASK);&t;&bslash;&n;} while (0)
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
DECL|struct|ahd_devinfo
r_struct
id|ahd_devinfo
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
DECL|macro|AHD_PCI_IOADDR0
mdefine_line|#define AHD_PCI_IOADDR0&t;PCIR_MAPS&t;/* I/O BAR*/
DECL|macro|AHD_PCI_MEMADDR
mdefine_line|#define AHD_PCI_MEMADDR&t;(PCIR_MAPS + 4)&t;/* Memory BAR */
DECL|macro|AHD_PCI_IOADDR1
mdefine_line|#define AHD_PCI_IOADDR1&t;(PCIR_MAPS + 12)/* Second I/O BAR */
DECL|typedef|ahd_device_setup_t
r_typedef
r_int
(paren
id|ahd_device_setup_t
)paren
(paren
r_struct
id|ahd_softc
op_star
)paren
suffix:semicolon
DECL|struct|ahd_pci_identity
r_struct
id|ahd_pci_identity
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
id|ahd_device_setup_t
op_star
id|setup
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ahd_pci_identity
id|ahd_pci_ident_table
(braket
)braket
suffix:semicolon
r_extern
r_const
id|u_int
id|ahd_num_pci_devs
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
id|ahd_device_setup_t
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
id|ahd_num_aic7770_devs
suffix:semicolon
DECL|macro|AHD_EISA_SLOT_OFFSET
mdefine_line|#define AHD_EISA_SLOT_OFFSET&t;0xc00
DECL|macro|AHD_EISA_IOSIZE
mdefine_line|#define AHD_EISA_IOSIZE&t;&t;0x100
multiline_comment|/*************************** Function Declarations ****************************/
multiline_comment|/******************************************************************************/
id|u_int
id|ahd_find_busy_tcl
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_int
id|tcl
)paren
suffix:semicolon
r_void
id|ahd_busy_tcl
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_int
id|tcl
comma
id|u_int
id|busyid
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahd_unbusy_tcl
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_int
id|tcl
)paren
suffix:semicolon
r_static
id|__inline
r_void
DECL|function|ahd_unbusy_tcl
id|ahd_unbusy_tcl
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_int
id|tcl
)paren
(brace
id|ahd_busy_tcl
c_func
(paren
id|ahd
comma
id|tcl
comma
id|SCB_LIST_NULL
)paren
suffix:semicolon
)brace
multiline_comment|/***************************** PCI Front End *********************************/
r_struct
id|ahd_pci_identity
op_star
id|ahd_find_pci_device
c_func
(paren
id|ahd_dev_softc_t
)paren
suffix:semicolon
r_int
id|ahd_pci_config
c_func
(paren
r_struct
id|ahd_softc
op_star
comma
r_struct
id|ahd_pci_identity
op_star
)paren
suffix:semicolon
r_int
id|ahd_pci_test_register_access
c_func
(paren
r_struct
id|ahd_softc
op_star
)paren
suffix:semicolon
multiline_comment|/************************** SCB and SCB queue management **********************/
r_int
id|ahd_probe_scbs
c_func
(paren
r_struct
id|ahd_softc
op_star
)paren
suffix:semicolon
r_void
id|ahd_qinfifo_requeue_tail
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_int
id|ahd_match_scb
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
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
id|ahd_softc
op_star
id|ahd_alloc
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
id|ahd_softc_init
c_func
(paren
r_struct
id|ahd_softc
op_star
)paren
suffix:semicolon
r_void
id|ahd_controller_info
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
r_int
id|ahd_init
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_int
id|ahd_default_config
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_int
id|ahd_parse_cfgdata
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|seeprom_config
op_star
id|sc
)paren
suffix:semicolon
r_void
id|ahd_intr_enable
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_int
id|enable
)paren
suffix:semicolon
r_void
id|ahd_pause_and_flushwork
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_int
id|ahd_suspend
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_int
id|ahd_resume
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_void
id|ahd_softc_insert
c_func
(paren
r_struct
id|ahd_softc
op_star
)paren
suffix:semicolon
r_struct
id|ahd_softc
op_star
id|ahd_find_softc
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_void
id|ahd_set_unit
c_func
(paren
r_struct
id|ahd_softc
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|ahd_set_name
c_func
(paren
r_struct
id|ahd_softc
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_struct
id|scb
op_star
id|ahd_get_scb
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_int
id|col_idx
)paren
suffix:semicolon
r_void
id|ahd_free_scb
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_void
id|ahd_alloc_scbs
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_void
id|ahd_free
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_int
id|ahd_reset
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_void
id|ahd_shutdown
c_func
(paren
r_void
op_star
id|arg
)paren
suffix:semicolon
r_int
id|ahd_write_flexport
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_int
id|addr
comma
id|u_int
id|value
)paren
suffix:semicolon
r_int
id|ahd_read_flexport
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_int
id|addr
comma
r_uint8
op_star
id|value
)paren
suffix:semicolon
r_int
id|ahd_wait_flexport
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
multiline_comment|/*************************** Interrupt Services *******************************/
r_void
id|ahd_pci_intr
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_void
id|ahd_clear_intstat
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_void
id|ahd_run_qoutfifo
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
macro_line|#ifdef AHD_TARGET_MODE
r_void
id|ahd_run_tqinfifo
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_int
id|paused
)paren
suffix:semicolon
macro_line|#endif
r_void
id|ahd_handle_hwerrint
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_void
id|ahd_handle_seqint
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_int
id|intstat
)paren
suffix:semicolon
r_void
id|ahd_handle_scsiint
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_int
id|intstat
)paren
suffix:semicolon
r_void
id|ahd_clear_critical_section
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
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
comma
DECL|enumerator|SEARCH_PRINT
id|SEARCH_PRINT
DECL|typedef|ahd_search_action
)brace
id|ahd_search_action
suffix:semicolon
r_int
id|ahd_search_qinfifo
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
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
id|ahd_search_action
id|action
)paren
suffix:semicolon
r_int
id|ahd_search_disc_list
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
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
id|ahd_freeze_devq
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_int
id|ahd_reset_channel
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_char
id|channel
comma
r_int
id|initiate_reset
)paren
suffix:semicolon
r_int
id|ahd_abort_scbs
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
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
)paren
suffix:semicolon
r_void
id|ahd_restart
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_void
id|ahd_clear_fifo
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_int
id|fifo
)paren
suffix:semicolon
r_void
id|ahd_handle_scb_status
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_void
id|ahd_handle_scsi_status
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_void
id|ahd_calc_residual
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
multiline_comment|/*************************** Utility Functions ********************************/
r_struct
id|ahd_phase_table_entry
op_star
id|ahd_lookup_phase_entry
c_func
(paren
r_int
id|phase
)paren
suffix:semicolon
r_void
id|ahd_compile_devinfo
c_func
(paren
r_struct
id|ahd_devinfo
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
r_void
id|ahd_find_syncrate
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
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
r_void
id|ahd_validate_offset
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|ahd_initiator_tinfo
op_star
id|tinfo
comma
id|u_int
id|period
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
id|ahd_validate_width
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|ahd_initiator_tinfo
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
multiline_comment|/*&n; * Negotiation types.  These are used to qualify if we should renegotiate&n; * even if our goal and current transport parameters are identical.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AHD_NEG_TO_GOAL
id|AHD_NEG_TO_GOAL
comma
multiline_comment|/* Renegotiate only if goal and curr differ. */
DECL|enumerator|AHD_NEG_IF_NON_ASYNC
id|AHD_NEG_IF_NON_ASYNC
comma
multiline_comment|/* Renegotiate so long as goal is non-async. */
DECL|enumerator|AHD_NEG_ALWAYS
id|AHD_NEG_ALWAYS
multiline_comment|/* Renegotiat even if goal is async. */
DECL|typedef|ahd_neg_type
)brace
id|ahd_neg_type
suffix:semicolon
r_int
id|ahd_update_neg_request
c_func
(paren
r_struct
id|ahd_softc
op_star
comma
r_struct
id|ahd_devinfo
op_star
comma
r_struct
id|ahd_tmode_tstate
op_star
comma
r_struct
id|ahd_initiator_tinfo
op_star
comma
id|ahd_neg_type
)paren
suffix:semicolon
r_void
id|ahd_set_width
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|ahd_devinfo
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
id|ahd_set_syncrate
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|ahd_devinfo
op_star
id|devinfo
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
DECL|enumerator|AHD_QUEUE_NONE
id|AHD_QUEUE_NONE
comma
DECL|enumerator|AHD_QUEUE_BASIC
id|AHD_QUEUE_BASIC
comma
DECL|enumerator|AHD_QUEUE_TAGGED
id|AHD_QUEUE_TAGGED
DECL|typedef|ahd_queue_alg
)brace
id|ahd_queue_alg
suffix:semicolon
r_void
id|ahd_set_tags
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|ahd_devinfo
op_star
id|devinfo
comma
id|ahd_queue_alg
id|alg
)paren
suffix:semicolon
multiline_comment|/**************************** Target Mode *************************************/
macro_line|#ifdef AHD_TARGET_MODE
r_void
id|ahd_send_lstate_events
c_func
(paren
r_struct
id|ahd_softc
op_star
comma
r_struct
id|ahd_tmode_lstate
op_star
)paren
suffix:semicolon
r_void
id|ahd_handle_en_lun
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
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
id|ahd_find_tmode_devs
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
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
id|ahd_tmode_tstate
op_star
op_star
id|tstate
comma
r_struct
id|ahd_tmode_lstate
op_star
op_star
id|lstate
comma
r_int
id|notfound_failure
)paren
suffix:semicolon
macro_line|#ifndef AHD_TMODE_ENABLE
DECL|macro|AHD_TMODE_ENABLE
mdefine_line|#define AHD_TMODE_ENABLE 0
macro_line|#endif
macro_line|#endif
multiline_comment|/******************************* Debug ***************************************/
macro_line|#ifdef AHD_DEBUG
r_extern
r_uint32
id|ahd_debug
suffix:semicolon
DECL|macro|AHD_SHOW_MISC
mdefine_line|#define AHD_SHOW_MISC&t;&t;0x00001
DECL|macro|AHD_SHOW_SENSE
mdefine_line|#define AHD_SHOW_SENSE&t;&t;0x00002
DECL|macro|AHD_SHOW_RECOVERY
mdefine_line|#define AHD_SHOW_RECOVERY&t;0x00004
DECL|macro|AHD_DUMP_SEEPROM
mdefine_line|#define AHD_DUMP_SEEPROM&t;0x00008
DECL|macro|AHD_SHOW_TERMCTL
mdefine_line|#define AHD_SHOW_TERMCTL&t;0x00010
DECL|macro|AHD_SHOW_MEMORY
mdefine_line|#define AHD_SHOW_MEMORY&t;&t;0x00020
DECL|macro|AHD_SHOW_MESSAGES
mdefine_line|#define AHD_SHOW_MESSAGES&t;0x00040
DECL|macro|AHD_SHOW_MODEPTR
mdefine_line|#define AHD_SHOW_MODEPTR&t;0x00080
DECL|macro|AHD_SHOW_SELTO
mdefine_line|#define AHD_SHOW_SELTO&t;&t;0x00100
DECL|macro|AHD_SHOW_FIFOS
mdefine_line|#define AHD_SHOW_FIFOS&t;&t;0x00200
DECL|macro|AHD_SHOW_QFULL
mdefine_line|#define AHD_SHOW_QFULL&t;&t;0x00400
DECL|macro|AHD_SHOW_DV
mdefine_line|#define&t;AHD_SHOW_DV&t;&t;0x00800
DECL|macro|AHD_SHOW_MASKED_ERRORS
mdefine_line|#define AHD_SHOW_MASKED_ERRORS&t;0x01000
DECL|macro|AHD_SHOW_QUEUE
mdefine_line|#define AHD_SHOW_QUEUE&t;&t;0x02000
DECL|macro|AHD_SHOW_TQIN
mdefine_line|#define AHD_SHOW_TQIN&t;&t;0x04000
DECL|macro|AHD_SHOW_SG
mdefine_line|#define AHD_SHOW_SG&t;&t;0x08000
DECL|macro|AHD_DEBUG_SEQUENCER
mdefine_line|#define AHD_DEBUG_SEQUENCER&t;0x10000
macro_line|#endif
r_void
id|ahd_print_scb
c_func
(paren
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_void
id|ahd_print_devinfo
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
r_struct
id|ahd_devinfo
op_star
id|devinfo
)paren
suffix:semicolon
r_void
id|ahd_dump_sglist
c_func
(paren
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_void
id|ahd_dump_all_cards_state
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ahd_dump_card_state
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
r_int
id|ahd_print_register
c_func
(paren
id|ahd_reg_parse_entry_t
op_star
id|table
comma
id|u_int
id|num_entries
comma
r_const
r_char
op_star
id|name
comma
id|u_int
id|address
comma
id|u_int
id|value
comma
id|u_int
op_star
id|cur_column
comma
id|u_int
id|wrap_point
)paren
suffix:semicolon
r_void
id|ahd_dump_scbs
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
suffix:semicolon
macro_line|#endif /* _AIC79XX_H_ */
eof
