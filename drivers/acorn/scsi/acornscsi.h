multiline_comment|/*&n; *  linux/drivers/acorn/scsi/acornscsi.h&n; *&n; *  Copyright (C) 1997 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Acorn SCSI driver&n; */
macro_line|#ifndef ACORNSCSI_H
DECL|macro|ACORNSCSI_H
mdefine_line|#define ACORNSCSI_H
multiline_comment|/* SBIC registers */
DECL|macro|OWNID
mdefine_line|#define OWNID&t;&t;&t;0
DECL|macro|OWNID_FS1
mdefine_line|#define OWNID_FS1&t;&t;(1&lt;&lt;7)
DECL|macro|OWNID_FS2
mdefine_line|#define OWNID_FS2&t;&t;(1&lt;&lt;6)
DECL|macro|OWNID_EHP
mdefine_line|#define OWNID_EHP&t;&t;(1&lt;&lt;4)
DECL|macro|OWNID_EAF
mdefine_line|#define OWNID_EAF&t;&t;(1&lt;&lt;3)
DECL|macro|CTRL
mdefine_line|#define CTRL&t;&t;&t;1
DECL|macro|CTRL_DMAMODE
mdefine_line|#define CTRL_DMAMODE&t;&t;(1&lt;&lt;7)
DECL|macro|CTRL_DMADBAMODE
mdefine_line|#define CTRL_DMADBAMODE&t;&t;(1&lt;&lt;6)
DECL|macro|CTRL_DMABURST
mdefine_line|#define CTRL_DMABURST&t;&t;(1&lt;&lt;5)
DECL|macro|CTRL_DMAPOLLED
mdefine_line|#define CTRL_DMAPOLLED&t;&t;0
DECL|macro|CTRL_HHP
mdefine_line|#define CTRL_HHP&t;&t;(1&lt;&lt;4)
DECL|macro|CTRL_EDI
mdefine_line|#define CTRL_EDI&t;&t;(1&lt;&lt;3)
DECL|macro|CTRL_IDI
mdefine_line|#define CTRL_IDI&t;&t;(1&lt;&lt;2)
DECL|macro|CTRL_HA
mdefine_line|#define CTRL_HA&t;&t;&t;(1&lt;&lt;1)
DECL|macro|CTRL_HSP
mdefine_line|#define CTRL_HSP&t;&t;(1&lt;&lt;0)
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT&t;&t;&t;2
DECL|macro|TOTSECTS
mdefine_line|#define TOTSECTS&t;&t;3
DECL|macro|TOTHEADS
mdefine_line|#define TOTHEADS&t;&t;4
DECL|macro|TOTCYLH
mdefine_line|#define TOTCYLH&t;&t;&t;5
DECL|macro|TOTCYLL
mdefine_line|#define TOTCYLL&t;&t;&t;6
DECL|macro|LOGADDRH
mdefine_line|#define LOGADDRH&t;&t;7
DECL|macro|LOGADDRM2
mdefine_line|#define LOGADDRM2&t;&t;8
DECL|macro|LOGADDRM1
mdefine_line|#define LOGADDRM1&t;&t;9
DECL|macro|LOGADDRL
mdefine_line|#define LOGADDRL&t;&t;10
DECL|macro|SECTORNUM
mdefine_line|#define SECTORNUM&t;&t;11
DECL|macro|HEADNUM
mdefine_line|#define HEADNUM&t;&t;&t;12
DECL|macro|CYLH
mdefine_line|#define CYLH&t;&t;&t;13
DECL|macro|CYLL
mdefine_line|#define CYLL&t;&t;&t;14
DECL|macro|TARGETLUN
mdefine_line|#define TARGETLUN&t;&t;15
DECL|macro|TARGETLUN_TLV
mdefine_line|#define TARGETLUN_TLV&t;&t;(1&lt;&lt;7)
DECL|macro|TARGETLUN_DOK
mdefine_line|#define TARGETLUN_DOK&t;&t;(1&lt;&lt;6)
DECL|macro|CMNDPHASE
mdefine_line|#define CMNDPHASE&t;&t;16
DECL|macro|SYNCHTRANSFER
mdefine_line|#define SYNCHTRANSFER&t;&t;17
DECL|macro|SYNCHTRANSFER_OF0
mdefine_line|#define SYNCHTRANSFER_OF0&t;0x00
DECL|macro|SYNCHTRANSFER_OF1
mdefine_line|#define SYNCHTRANSFER_OF1&t;0x01
DECL|macro|SYNCHTRANSFER_OF2
mdefine_line|#define SYNCHTRANSFER_OF2&t;0x02
DECL|macro|SYNCHTRANSFER_OF3
mdefine_line|#define SYNCHTRANSFER_OF3&t;0x03
DECL|macro|SYNCHTRANSFER_OF4
mdefine_line|#define SYNCHTRANSFER_OF4&t;0x04
DECL|macro|SYNCHTRANSFER_OF5
mdefine_line|#define SYNCHTRANSFER_OF5&t;0x05
DECL|macro|SYNCHTRANSFER_OF6
mdefine_line|#define SYNCHTRANSFER_OF6&t;0x06
DECL|macro|SYNCHTRANSFER_OF7
mdefine_line|#define SYNCHTRANSFER_OF7&t;0x07
DECL|macro|SYNCHTRANSFER_OF8
mdefine_line|#define SYNCHTRANSFER_OF8&t;0x08
DECL|macro|SYNCHTRANSFER_OF9
mdefine_line|#define SYNCHTRANSFER_OF9&t;0x09
DECL|macro|SYNCHTRANSFER_OF10
mdefine_line|#define SYNCHTRANSFER_OF10&t;0x0A
DECL|macro|SYNCHTRANSFER_OF11
mdefine_line|#define SYNCHTRANSFER_OF11&t;0x0B
DECL|macro|SYNCHTRANSFER_OF12
mdefine_line|#define SYNCHTRANSFER_OF12&t;0x0C
DECL|macro|SYNCHTRANSFER_8DBA
mdefine_line|#define SYNCHTRANSFER_8DBA&t;0x00
DECL|macro|SYNCHTRANSFER_2DBA
mdefine_line|#define SYNCHTRANSFER_2DBA&t;0x20
DECL|macro|SYNCHTRANSFER_3DBA
mdefine_line|#define SYNCHTRANSFER_3DBA&t;0x30
DECL|macro|SYNCHTRANSFER_4DBA
mdefine_line|#define SYNCHTRANSFER_4DBA&t;0x40
DECL|macro|SYNCHTRANSFER_5DBA
mdefine_line|#define SYNCHTRANSFER_5DBA&t;0x50
DECL|macro|SYNCHTRANSFER_6DBA
mdefine_line|#define SYNCHTRANSFER_6DBA&t;0x60
DECL|macro|SYNCHTRANSFER_7DBA
mdefine_line|#define SYNCHTRANSFER_7DBA&t;0x70
DECL|macro|TRANSCNTH
mdefine_line|#define TRANSCNTH&t;&t;18
DECL|macro|TRANSCNTM
mdefine_line|#define TRANSCNTM&t;&t;19
DECL|macro|TRANSCNTL
mdefine_line|#define TRANSCNTL&t;&t;20
DECL|macro|DESTID
mdefine_line|#define DESTID&t;&t;&t;21
DECL|macro|DESTID_SCC
mdefine_line|#define DESTID_SCC&t;&t;(1&lt;&lt;7)
DECL|macro|DESTID_DPD
mdefine_line|#define DESTID_DPD&t;&t;(1&lt;&lt;6)
DECL|macro|SOURCEID
mdefine_line|#define SOURCEID&t;&t;22
DECL|macro|SOURCEID_ER
mdefine_line|#define SOURCEID_ER&t;&t;(1&lt;&lt;7)
DECL|macro|SOURCEID_ES
mdefine_line|#define SOURCEID_ES&t;&t;(1&lt;&lt;6)
DECL|macro|SOURCEID_DSP
mdefine_line|#define SOURCEID_DSP&t;&t;(1&lt;&lt;5)
DECL|macro|SOURCEID_SIV
mdefine_line|#define SOURCEID_SIV&t;&t;(1&lt;&lt;4)
DECL|macro|SSR
mdefine_line|#define SSR&t;&t;&t;23
DECL|macro|CMND
mdefine_line|#define CMND&t;&t;&t;24
DECL|macro|CMND_RESET
mdefine_line|#define CMND_RESET&t;&t;0x00
DECL|macro|CMND_ABORT
mdefine_line|#define CMND_ABORT&t;&t;0x01
DECL|macro|CMND_ASSERTATN
mdefine_line|#define CMND_ASSERTATN&t;&t;0x02
DECL|macro|CMND_NEGATEACK
mdefine_line|#define CMND_NEGATEACK&t;&t;0x03
DECL|macro|CMND_DISCONNECT
mdefine_line|#define CMND_DISCONNECT&t;&t;0x04
DECL|macro|CMND_RESELECT
mdefine_line|#define CMND_RESELECT&t;&t;0x05
DECL|macro|CMND_SELWITHATN
mdefine_line|#define CMND_SELWITHATN&t;&t;0x06
DECL|macro|CMND_SELECT
mdefine_line|#define CMND_SELECT&t;&t;0x07
DECL|macro|CMND_SELECTATNTRANSFER
mdefine_line|#define CMND_SELECTATNTRANSFER&t;0x08
DECL|macro|CMND_SELECTTRANSFER
mdefine_line|#define CMND_SELECTTRANSFER&t;0x09
DECL|macro|CMND_RESELECTRXDATA
mdefine_line|#define CMND_RESELECTRXDATA&t;0x0A
DECL|macro|CMND_RESELECTTXDATA
mdefine_line|#define CMND_RESELECTTXDATA&t;0x0B
DECL|macro|CMND_WAITFORSELRECV
mdefine_line|#define CMND_WAITFORSELRECV&t;0x0C
DECL|macro|CMND_SENDSTATCMD
mdefine_line|#define CMND_SENDSTATCMD&t;0x0D
DECL|macro|CMND_SENDDISCONNECT
mdefine_line|#define CMND_SENDDISCONNECT&t;0x0E
DECL|macro|CMND_SETIDI
mdefine_line|#define CMND_SETIDI&t;&t;0x0F
DECL|macro|CMND_RECEIVECMD
mdefine_line|#define CMND_RECEIVECMD&t;&t;0x10
DECL|macro|CMND_RECEIVEDTA
mdefine_line|#define CMND_RECEIVEDTA&t;&t;0x11
DECL|macro|CMND_RECEIVEMSG
mdefine_line|#define CMND_RECEIVEMSG&t;&t;0x12
DECL|macro|CMND_RECEIVEUSP
mdefine_line|#define CMND_RECEIVEUSP&t;&t;0x13
DECL|macro|CMND_SENDCMD
mdefine_line|#define CMND_SENDCMD&t;&t;0x14
DECL|macro|CMND_SENDDATA
mdefine_line|#define CMND_SENDDATA&t;&t;0x15
DECL|macro|CMND_SENDMSG
mdefine_line|#define CMND_SENDMSG&t;&t;0x16
DECL|macro|CMND_SENDUSP
mdefine_line|#define CMND_SENDUSP&t;&t;0x17
DECL|macro|CMND_TRANSLATEADDR
mdefine_line|#define CMND_TRANSLATEADDR&t;0x18
DECL|macro|CMND_XFERINFO
mdefine_line|#define CMND_XFERINFO&t;&t;0x20
DECL|macro|CMND_SBT
mdefine_line|#define CMND_SBT&t;&t;(1&lt;&lt;7)
DECL|macro|DATA
mdefine_line|#define DATA&t;&t;&t;25
DECL|macro|ASR
mdefine_line|#define ASR&t;&t;&t;26
DECL|macro|ASR_INT
mdefine_line|#define ASR_INT&t;&t;&t;(1&lt;&lt;7)
DECL|macro|ASR_LCI
mdefine_line|#define ASR_LCI&t;&t;&t;(1&lt;&lt;6)
DECL|macro|ASR_BSY
mdefine_line|#define ASR_BSY&t;&t;&t;(1&lt;&lt;5)
DECL|macro|ASR_CIP
mdefine_line|#define ASR_CIP&t;&t;&t;(1&lt;&lt;4)
DECL|macro|ASR_PE
mdefine_line|#define ASR_PE&t;&t;&t;(1&lt;&lt;1)
DECL|macro|ASR_DBR
mdefine_line|#define ASR_DBR&t;&t;&t;(1&lt;&lt;0)
multiline_comment|/* DMAC registers */
DECL|macro|INIT
mdefine_line|#define INIT&t;&t;&t;0x00
DECL|macro|INIT_8BIT
mdefine_line|#define INIT_8BIT&t;&t;(1)
DECL|macro|CHANNEL
mdefine_line|#define CHANNEL&t;&t;&t;0x80
DECL|macro|CHANNEL_0
mdefine_line|#define CHANNEL_0&t;&t;0x00
DECL|macro|CHANNEL_1
mdefine_line|#define CHANNEL_1&t;&t;0x01
DECL|macro|CHANNEL_2
mdefine_line|#define CHANNEL_2&t;&t;0x02
DECL|macro|CHANNEL_3
mdefine_line|#define CHANNEL_3&t;&t;0x03
DECL|macro|TXCNTLO
mdefine_line|#define TXCNTLO&t;&t;&t;0x01
DECL|macro|TXCNTHI
mdefine_line|#define TXCNTHI&t;&t;&t;0x81
DECL|macro|TXADRLO
mdefine_line|#define TXADRLO&t;&t;&t;0x02
DECL|macro|TXADRMD
mdefine_line|#define TXADRMD&t;&t;&t;0x82
DECL|macro|TXADRHI
mdefine_line|#define TXADRHI&t;&t;&t;0x03
DECL|macro|DEVCON0
mdefine_line|#define DEVCON0&t;&t;&t;0x04
DECL|macro|DEVCON0_AKL
mdefine_line|#define DEVCON0_AKL&t;&t;(1&lt;&lt;7)
DECL|macro|DEVCON0_RQL
mdefine_line|#define DEVCON0_RQL&t;&t;(1&lt;&lt;6)
DECL|macro|DEVCON0_EXW
mdefine_line|#define DEVCON0_EXW&t;&t;(1&lt;&lt;5)
DECL|macro|DEVCON0_ROT
mdefine_line|#define DEVCON0_ROT&t;&t;(1&lt;&lt;4)
DECL|macro|DEVCON0_CMP
mdefine_line|#define DEVCON0_CMP&t;&t;(1&lt;&lt;3)
DECL|macro|DEVCON0_DDMA
mdefine_line|#define DEVCON0_DDMA&t;&t;(1&lt;&lt;2)
DECL|macro|DEVCON0_AHLD
mdefine_line|#define DEVCON0_AHLD&t;&t;(1&lt;&lt;1)
DECL|macro|DEVCON0_MTM
mdefine_line|#define DEVCON0_MTM&t;&t;(1&lt;&lt;0)
DECL|macro|DEVCON1
mdefine_line|#define DEVCON1&t;&t;&t;0x84
DECL|macro|DEVCON1_WEV
mdefine_line|#define DEVCON1_WEV&t;&t;(1&lt;&lt;1)
DECL|macro|DEVCON1_BHLD
mdefine_line|#define DEVCON1_BHLD&t;&t;(1&lt;&lt;0)
DECL|macro|MODECON
mdefine_line|#define MODECON&t;&t;&t;0x05
DECL|macro|MODECON_WOED
mdefine_line|#define MODECON_WOED&t;&t;0x01
DECL|macro|MODECON_VERIFY
mdefine_line|#define MODECON_VERIFY&t;&t;0x00
DECL|macro|MODECON_READ
mdefine_line|#define MODECON_READ&t;&t;0x04
DECL|macro|MODECON_WRITE
mdefine_line|#define MODECON_WRITE&t;&t;0x08
DECL|macro|MODECON_AUTOINIT
mdefine_line|#define MODECON_AUTOINIT&t;0x10
DECL|macro|MODECON_ADDRDIR
mdefine_line|#define MODECON_ADDRDIR&t;&t;0x20
DECL|macro|MODECON_DEMAND
mdefine_line|#define MODECON_DEMAND&t;&t;0x00
DECL|macro|MODECON_SINGLE
mdefine_line|#define MODECON_SINGLE&t;&t;0x40
DECL|macro|MODECON_BLOCK
mdefine_line|#define MODECON_BLOCK&t;&t;0x80
DECL|macro|MODECON_CASCADE
mdefine_line|#define MODECON_CASCADE&t;&t;0xC0
DECL|macro|STATUS
mdefine_line|#define STATUS&t;&t;&t;0x85
DECL|macro|STATUS_TC0
mdefine_line|#define STATUS_TC0&t;&t;(1&lt;&lt;0)
DECL|macro|STATUS_RQ0
mdefine_line|#define STATUS_RQ0&t;&t;(1&lt;&lt;4)
DECL|macro|TEMPLO
mdefine_line|#define TEMPLO&t;&t;&t;0x06
DECL|macro|TEMPHI
mdefine_line|#define TEMPHI&t;&t;&t;0x86
DECL|macro|REQREG
mdefine_line|#define REQREG&t;&t;&t;0x07
DECL|macro|MASKREG
mdefine_line|#define MASKREG&t;&t;&t;0x87
DECL|macro|MASKREG_M0
mdefine_line|#define MASKREG_M0&t;&t;0x01
DECL|macro|MASKREG_M1
mdefine_line|#define MASKREG_M1&t;&t;0x02
DECL|macro|MASKREG_M2
mdefine_line|#define MASKREG_M2&t;&t;0x04
DECL|macro|MASKREG_M3
mdefine_line|#define MASKREG_M3&t;&t;0x08
multiline_comment|/* miscellaneous internal variables */
DECL|macro|POD_SPACE
mdefine_line|#define POD_SPACE(x)&t;((x) + 0xd0000)
DECL|macro|MASK_ON
mdefine_line|#define MASK_ON&t;&t;(MASKREG_M3|MASKREG_M2|MASKREG_M1|MASKREG_M0)
DECL|macro|MASK_OFF
mdefine_line|#define MASK_OFF&t;(MASKREG_M3|MASKREG_M2|MASKREG_M1)
DECL|macro|min
mdefine_line|#define min(x,y) ((x) &lt; (y) ? (x) : (y))
DECL|macro|max
mdefine_line|#define max(x,y) ((x) &lt; (y) ? (y) : (x))
multiline_comment|/*&n; * SCSI driver phases&n; */
r_typedef
r_enum
(brace
DECL|enumerator|PHASE_IDLE
id|PHASE_IDLE
comma
multiline_comment|/* we&squot;re not planning on doing anything&t; */
DECL|enumerator|PHASE_CONNECTING
id|PHASE_CONNECTING
comma
multiline_comment|/* connecting to a target&t;&t; */
DECL|enumerator|PHASE_CONNECTED
id|PHASE_CONNECTED
comma
multiline_comment|/* connected to a target&t;&t; */
DECL|enumerator|PHASE_MSGOUT
id|PHASE_MSGOUT
comma
multiline_comment|/* message out to device&t;&t; */
DECL|enumerator|PHASE_RECONNECTED
id|PHASE_RECONNECTED
comma
multiline_comment|/* reconnected&t;&t;&t;&t; */
DECL|enumerator|PHASE_COMMANDPAUSED
id|PHASE_COMMANDPAUSED
comma
multiline_comment|/* command partly sent&t;&t;&t; */
DECL|enumerator|PHASE_COMMAND
id|PHASE_COMMAND
comma
multiline_comment|/* command all sent&t;&t;&t; */
DECL|enumerator|PHASE_DATAOUT
id|PHASE_DATAOUT
comma
multiline_comment|/* data out to device&t;&t;&t; */
DECL|enumerator|PHASE_DATAIN
id|PHASE_DATAIN
comma
multiline_comment|/* data in from device&t;&t;&t; */
DECL|enumerator|PHASE_STATUSIN
id|PHASE_STATUSIN
comma
multiline_comment|/* status in from device&t;&t; */
DECL|enumerator|PHASE_MSGIN
id|PHASE_MSGIN
comma
multiline_comment|/* message in from device&t;&t; */
DECL|enumerator|PHASE_DONE
id|PHASE_DONE
comma
multiline_comment|/* finished&t;&t;&t;&t; */
DECL|enumerator|PHASE_ABORTED
id|PHASE_ABORTED
comma
multiline_comment|/* aborted&t;&t;&t;&t; */
DECL|enumerator|PHASE_DISCONNECT
id|PHASE_DISCONNECT
comma
multiline_comment|/* disconnecting&t;&t;&t; */
DECL|typedef|phase_t
)brace
id|phase_t
suffix:semicolon
multiline_comment|/*&n; * After interrupt, what to do now&n; */
r_typedef
r_enum
(brace
DECL|enumerator|INTR_IDLE
id|INTR_IDLE
comma
multiline_comment|/* not expecting another IRQ&t;&t; */
DECL|enumerator|INTR_NEXT_COMMAND
id|INTR_NEXT_COMMAND
comma
multiline_comment|/* start next command&t;&t;&t; */
DECL|enumerator|INTR_PROCESSING
id|INTR_PROCESSING
comma
multiline_comment|/* interrupt routine still processing&t; */
DECL|typedef|intr_ret_t
)brace
id|intr_ret_t
suffix:semicolon
multiline_comment|/*&n; * DMA direction&n; */
r_typedef
r_enum
(brace
DECL|enumerator|DMA_OUT
id|DMA_OUT
comma
multiline_comment|/* DMA from memory to chip&t;&t;*/
DECL|enumerator|DMA_IN
id|DMA_IN
multiline_comment|/* DMA from chip to memory&t;&t;*/
DECL|typedef|dmadir_t
)brace
id|dmadir_t
suffix:semicolon
multiline_comment|/*&n; * Synchronous transfer state&n; */
r_typedef
r_enum
(brace
multiline_comment|/* Synchronous transfer state&t;&t;*/
DECL|enumerator|SYNC_ASYNCHRONOUS
id|SYNC_ASYNCHRONOUS
comma
multiline_comment|/* don&squot;t negociate synchronous transfers*/
DECL|enumerator|SYNC_NEGOCIATE
id|SYNC_NEGOCIATE
comma
multiline_comment|/* start negociation&t;&t;&t;*/
DECL|enumerator|SYNC_SENT_REQUEST
id|SYNC_SENT_REQUEST
comma
multiline_comment|/* sent SDTR message&t;&t;&t;*/
DECL|enumerator|SYNC_COMPLETED
id|SYNC_COMPLETED
comma
multiline_comment|/* received SDTR reply&t;&t;&t;*/
DECL|typedef|syncxfer_t
)brace
id|syncxfer_t
suffix:semicolon
multiline_comment|/*&n; * Command type&n; */
r_typedef
r_enum
(brace
multiline_comment|/* command type&t;&t;&t;&t;*/
DECL|enumerator|CMD_READ
id|CMD_READ
comma
multiline_comment|/* READ_6, READ_10, READ_12&t;&t;*/
DECL|enumerator|CMD_WRITE
id|CMD_WRITE
comma
multiline_comment|/* WRITE_6, WRITE_10, WRITE_12&t;&t;*/
DECL|enumerator|CMD_MISC
id|CMD_MISC
comma
multiline_comment|/* Others&t;&t;&t;&t;*/
DECL|typedef|cmdtype_t
)brace
id|cmdtype_t
suffix:semicolon
multiline_comment|/*&n; * Data phase direction&n; */
r_typedef
r_enum
(brace
multiline_comment|/* Data direction&t;&t;&t;*/
DECL|enumerator|DATADIR_IN
id|DATADIR_IN
comma
multiline_comment|/* Data in phase expected&t;&t;*/
DECL|enumerator|DATADIR_OUT
id|DATADIR_OUT
multiline_comment|/* Data out phase expected&t;&t;*/
DECL|typedef|datadir_t
)brace
id|datadir_t
suffix:semicolon
macro_line|#include &quot;queue.h&quot;
macro_line|#include &quot;msgqueue.h&quot;
DECL|macro|STATUS_BUFFER_SIZE
mdefine_line|#define STATUS_BUFFER_SIZE&t;32
multiline_comment|/*&n; * This is used to dump the previous states of the SBIC&n; */
DECL|struct|status_entry
r_struct
id|status_entry
(brace
DECL|member|when
r_int
r_int
id|when
suffix:semicolon
DECL|member|ssr
r_int
r_char
id|ssr
suffix:semicolon
DECL|member|ph
r_int
r_char
id|ph
suffix:semicolon
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
DECL|member|unused
r_int
r_char
id|unused
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ADD_STATUS
mdefine_line|#define ADD_STATUS(_q,_ssr,_ph,_irq) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;host-&gt;status[(_q)][host-&gt;status_ptr[(_q)]].when = jiffies;&t;&bslash;&n;&t;host-&gt;status[(_q)][host-&gt;status_ptr[(_q)]].ssr  = (_ssr);&t;&bslash;&n;&t;host-&gt;status[(_q)][host-&gt;status_ptr[(_q)]].ph   = (_ph);&t;&bslash;&n;&t;host-&gt;status[(_q)][host-&gt;status_ptr[(_q)]].irq  = (_irq);&t;&bslash;&n;&t;host-&gt;status_ptr[(_q)] = (host-&gt;status_ptr[(_q)] + 1) &amp; (STATUS_BUFFER_SIZE - 1); &bslash;&n;})
multiline_comment|/*&n; * AcornSCSI host specific data&n; */
DECL|struct|acornscsi_hostdata
r_typedef
r_struct
id|acornscsi_hostdata
(brace
multiline_comment|/* miscellaneous */
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
multiline_comment|/* host&t;&t;&t;&t;&t;*/
DECL|member|SCpnt
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
multiline_comment|/* currently processing command&t;&t;*/
DECL|member|origSCpnt
id|Scsi_Cmnd
op_star
id|origSCpnt
suffix:semicolon
multiline_comment|/* original connecting command&t;&t;*/
multiline_comment|/* driver information */
r_struct
(brace
DECL|member|io_port
r_int
r_int
id|io_port
suffix:semicolon
multiline_comment|/* base address of WD33C93&t;&t;*/
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* interrupt&t;&t;&t;&t;*/
DECL|member|phase
id|phase_t
id|phase
suffix:semicolon
multiline_comment|/* current phase&t;&t;&t;*/
r_struct
(brace
DECL|member|target
r_int
r_char
id|target
suffix:semicolon
multiline_comment|/* reconnected target&t;&t;&t;*/
DECL|member|lun
r_int
r_char
id|lun
suffix:semicolon
multiline_comment|/* reconnected lun&t;&t;&t;*/
DECL|member|tag
r_int
r_char
id|tag
suffix:semicolon
multiline_comment|/* reconnected tag&t;&t;&t;*/
DECL|member|reconnected
)brace
id|reconnected
suffix:semicolon
DECL|member|SCp
id|Scsi_Pointer
id|SCp
suffix:semicolon
multiline_comment|/* current commands data pointer&t;*/
DECL|member|msgs
id|MsgQueue_t
id|msgs
suffix:semicolon
DECL|member|last_message
r_int
r_int
id|last_message
suffix:semicolon
multiline_comment|/* last message to be sent&t;&t;*/
DECL|member|disconnectable
r_int
r_char
id|disconnectable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* this command can be disconnected&t;*/
DECL|member|interrupt
r_int
r_char
id|interrupt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* interrupt active&t;&t;&t;*/
DECL|member|scsi
)brace
id|scsi
suffix:semicolon
multiline_comment|/* statistics information */
r_struct
(brace
DECL|member|queues
r_int
r_int
id|queues
suffix:semicolon
DECL|member|removes
r_int
r_int
id|removes
suffix:semicolon
DECL|member|fins
r_int
r_int
id|fins
suffix:semicolon
DECL|member|reads
r_int
r_int
id|reads
suffix:semicolon
DECL|member|writes
r_int
r_int
id|writes
suffix:semicolon
DECL|member|miscs
r_int
r_int
id|miscs
suffix:semicolon
DECL|member|disconnects
r_int
r_int
id|disconnects
suffix:semicolon
DECL|member|aborts
r_int
r_int
id|aborts
suffix:semicolon
DECL|member|resets
r_int
r_int
id|resets
suffix:semicolon
DECL|member|stats
)brace
id|stats
suffix:semicolon
multiline_comment|/* queue handling */
r_struct
(brace
DECL|member|issue
id|Queue_t
id|issue
suffix:semicolon
multiline_comment|/* issue queue&t;&t;&t;&t;*/
DECL|member|disconnected
id|Queue_t
id|disconnected
suffix:semicolon
multiline_comment|/* disconnected command queue&t;&t;*/
DECL|member|queues
)brace
id|queues
suffix:semicolon
multiline_comment|/* per-device info */
r_struct
(brace
DECL|member|sync_xfer
r_int
r_char
id|sync_xfer
suffix:semicolon
multiline_comment|/* synchronous transfer (SBIC value)&t;*/
DECL|member|sync_state
id|syncxfer_t
id|sync_state
suffix:semicolon
multiline_comment|/* sync xfer negociation state&t;&t;*/
DECL|member|disconnect_ok
r_int
r_char
id|disconnect_ok
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device can disconnect&t;&t;*/
DECL|member|device
)brace
id|device
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|busyluns
r_int
r_char
id|busyluns
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* array of bits indicating LUNs busy&t;*/
multiline_comment|/* DMA info */
r_struct
(brace
DECL|member|io_port
r_int
r_int
id|io_port
suffix:semicolon
multiline_comment|/* base address of DMA controller&t;*/
DECL|member|io_intr_clear
r_int
r_int
id|io_intr_clear
suffix:semicolon
multiline_comment|/* address of DMA interrupt clear&t;*/
DECL|member|free_addr
r_int
r_int
id|free_addr
suffix:semicolon
multiline_comment|/* next free address&t;&t;&t;*/
DECL|member|start_addr
r_int
r_int
id|start_addr
suffix:semicolon
multiline_comment|/* start address of current transfer&t;*/
DECL|member|direction
id|dmadir_t
id|direction
suffix:semicolon
multiline_comment|/* dma direction&t;&t;&t;*/
DECL|member|transferred
r_int
r_int
id|transferred
suffix:semicolon
multiline_comment|/* number of bytes transferred&t;&t;*/
DECL|member|xfer_start
r_int
r_int
id|xfer_start
suffix:semicolon
multiline_comment|/* scheduled DMA transfer start&t;&t;*/
DECL|member|xfer_length
r_int
r_int
id|xfer_length
suffix:semicolon
multiline_comment|/* scheduled DMA transfer length&t;*/
DECL|member|xfer_ptr
r_char
op_star
id|xfer_ptr
suffix:semicolon
multiline_comment|/* pointer to area&t;&t;&t;*/
DECL|member|xfer_required
r_int
r_char
id|xfer_required
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set if we need to transfer something&t;*/
DECL|member|xfer_setup
r_int
r_char
id|xfer_setup
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set if DMA is setup&t;&t;&t;*/
DECL|member|xfer_done
r_int
r_char
id|xfer_done
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set if DMA reached end of BH list&t;*/
DECL|member|dma
)brace
id|dma
suffix:semicolon
multiline_comment|/* card info */
r_struct
(brace
DECL|member|io_intr
r_int
r_int
id|io_intr
suffix:semicolon
multiline_comment|/* base address of interrupt id reg&t;*/
DECL|member|io_page
r_int
r_int
id|io_page
suffix:semicolon
multiline_comment|/* base address of page reg&t;&t;*/
DECL|member|io_ram
r_int
r_int
id|io_ram
suffix:semicolon
multiline_comment|/* base address of RAM access&t;&t;*/
DECL|member|page_reg
r_int
r_char
id|page_reg
suffix:semicolon
multiline_comment|/* current setting of page reg&t;&t;*/
DECL|member|card
)brace
id|card
suffix:semicolon
DECL|member|status_ptr
r_int
r_char
id|status_ptr
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|status
r_struct
id|status_entry
id|status
(braket
l_int|9
)braket
(braket
id|STATUS_BUFFER_SIZE
)braket
suffix:semicolon
DECL|typedef|AS_Host
)brace
id|AS_Host
suffix:semicolon
macro_line|#endif /* ACORNSCSI_H */
eof
