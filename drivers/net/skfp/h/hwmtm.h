multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
macro_line|#ifndef&t;_HWM_
DECL|macro|_HWM_
mdefine_line|#define&t;_HWM_
macro_line|#include &quot;h/mbuf.h&quot;
multiline_comment|/*&n; * MACRO for DMA synchronization:&n; *&t;The descriptor &squot;desc&squot; is flushed for the device &squot;flag&squot;.&n; *&t;Devices are the CPU (DDI_DMA_SYNC_FORCPU) and the&n; *&t;adapter (DDI_DMA_SYNC_FORDEV).&n; *&n; *&t;&squot;desc&squot;&t;Pointer to a Rx or Tx descriptor.&n; *&t;&squot;flag&squot;&t;Flag for direction (view for CPU or DEVICE) that&n; *&t;&t;should be synchronized.&n; *&n; *&t;Empty macros and defines are specified here. The real macro&n; *&t;is os-specific and should be defined in osdef1st.h.&n; */
macro_line|#ifndef DRV_BUF_FLUSH
DECL|macro|DRV_BUF_FLUSH
mdefine_line|#define DRV_BUF_FLUSH(desc,flag)
DECL|macro|DDI_DMA_SYNC_FORCPU
mdefine_line|#define DDI_DMA_SYNC_FORCPU
DECL|macro|DDI_DMA_SYNC_FORDEV
mdefine_line|#define DDI_DMA_SYNC_FORDEV
macro_line|#endif
multiline_comment|/*&n;&t; * hardware modul dependent receive modes&n;&t; */
DECL|macro|RX_ENABLE_PASS_SMT
mdefine_line|#define&t;RX_ENABLE_PASS_SMT&t;21
DECL|macro|RX_DISABLE_PASS_SMT
mdefine_line|#define&t;RX_DISABLE_PASS_SMT&t;22
DECL|macro|RX_ENABLE_PASS_NSA
mdefine_line|#define&t;RX_ENABLE_PASS_NSA&t;23
DECL|macro|RX_DISABLE_PASS_NSA
mdefine_line|#define&t;RX_DISABLE_PASS_NSA&t;24
DECL|macro|RX_ENABLE_PASS_DB
mdefine_line|#define&t;RX_ENABLE_PASS_DB&t;25
DECL|macro|RX_DISABLE_PASS_DB
mdefine_line|#define&t;RX_DISABLE_PASS_DB&t;26
DECL|macro|RX_DISABLE_PASS_ALL
mdefine_line|#define&t;RX_DISABLE_PASS_ALL&t;27
DECL|macro|RX_DISABLE_LLC_PROMISC
mdefine_line|#define&t;RX_DISABLE_LLC_PROMISC&t;28
DECL|macro|RX_ENABLE_LLC_PROMISC
mdefine_line|#define&t;RX_ENABLE_LLC_PROMISC&t;29
macro_line|#ifndef&t;DMA_RD
DECL|macro|DMA_RD
mdefine_line|#define DMA_RD&t;&t;1&t;/* memory -&gt; hw */
macro_line|#endif
macro_line|#ifndef DMA_WR
DECL|macro|DMA_WR
mdefine_line|#define DMA_WR&t;&t;2&t;/* hw -&gt; memory */
macro_line|#endif
DECL|macro|SMT_BUF
mdefine_line|#define SMT_BUF&t;&t;0x80
multiline_comment|/*&n;&t; * bits of the frame status byte&n;&t; */
DECL|macro|EN_IRQ_EOF
mdefine_line|#define EN_IRQ_EOF&t;0x02&t;/* get IRQ after end of frame transmission */
DECL|macro|LOC_TX
mdefine_line|#define&t;LOC_TX&t;&t;0x04&t;/* send frame to the local SMT */
DECL|macro|LAST_FRAG
mdefine_line|#define LAST_FRAG&t;0x08&t;/* last TxD of the frame */
DECL|macro|FIRST_FRAG
mdefine_line|#define&t;FIRST_FRAG&t;0x10&t;/* first TxD of the frame */
DECL|macro|LAN_TX
mdefine_line|#define&t;LAN_TX&t;&t;0x20&t;/* send frame to network if set */
DECL|macro|RING_DOWN
mdefine_line|#define RING_DOWN&t;0x40&t;/* error: unable to send, ring down */
DECL|macro|OUT_OF_TXD
mdefine_line|#define OUT_OF_TXD&t;0x80&t;/* error: not enough TxDs available */
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL &t;&t;0
macro_line|#endif
macro_line|#ifdef&t;LITTLE_ENDIAN
DECL|macro|HWM_REVERSE
mdefine_line|#define HWM_REVERSE(x)&t;(x)
macro_line|#else
DECL|macro|HWM_REVERSE
mdefine_line|#define&t;HWM_REVERSE(x)&t;&t;((((x)&lt;&lt;24L)&amp;0xff000000L)&t;+&t;&bslash;&n;&t;&t;&t;&t; (((x)&lt;&lt; 8L)&amp;0x00ff0000L)&t;+&t;&bslash;&n;&t;&t;&t;&t; (((x)&gt;&gt; 8L)&amp;0x0000ff00L)&t;+&t;&bslash;&n;&t;&t;&t;&t; (((x)&gt;&gt;24L)&amp;0x000000ffL))
macro_line|#endif
DECL|macro|C_INDIC
mdefine_line|#define C_INDIC&t;&t;(1L&lt;&lt;25)
DECL|macro|A_INDIC
mdefine_line|#define A_INDIC&t;&t;(1L&lt;&lt;26)
DECL|macro|RD_FS_LOCAL
mdefine_line|#define&t;RD_FS_LOCAL&t;0x80
multiline_comment|/*&n;&t; * DEBUG FLAGS&n;&t; */
DECL|macro|DEBUG_SMTF
mdefine_line|#define&t;DEBUG_SMTF&t;1
DECL|macro|DEBUG_SMT
mdefine_line|#define&t;DEBUG_SMT&t;2
DECL|macro|DEBUG_ECM
mdefine_line|#define&t;DEBUG_ECM&t;3
DECL|macro|DEBUG_RMT
mdefine_line|#define&t;DEBUG_RMT&t;4
DECL|macro|DEBUG_CFM
mdefine_line|#define&t;DEBUG_CFM&t;5
DECL|macro|DEBUG_PCM
mdefine_line|#define&t;DEBUG_PCM&t;6
DECL|macro|DEBUG_SBA
mdefine_line|#define&t;DEBUG_SBA&t;7
DECL|macro|DEBUG_ESS
mdefine_line|#define&t;DEBUG_ESS&t;8
DECL|macro|DB_HWM_RX
mdefine_line|#define&t;DB_HWM_RX&t;10
DECL|macro|DB_HWM_TX
mdefine_line|#define&t;DB_HWM_TX&t;11
DECL|macro|DB_HWM_GEN
mdefine_line|#define DB_HWM_GEN&t;12
DECL|struct|s_mbuf_pool
r_struct
id|s_mbuf_pool
(brace
macro_line|#ifndef&t;MB_OUTSIDE_SMC
DECL|member|mb
id|SMbuf
id|mb
(braket
id|MAX_MBUF
)braket
suffix:semicolon
multiline_comment|/* mbuf pool */
macro_line|#endif
DECL|member|mb_start
id|SMbuf
op_star
id|mb_start
suffix:semicolon
multiline_comment|/* points to the first mb */
DECL|member|mb_free
id|SMbuf
op_star
id|mb_free
suffix:semicolon
multiline_comment|/* free queue */
)brace
suffix:semicolon
DECL|struct|hwm_r
r_struct
id|hwm_r
(brace
multiline_comment|/*&n;&t; * hardware modul specific receive variables&n;&t; */
DECL|member|len
id|u_int
id|len
suffix:semicolon
multiline_comment|/* length of the whole frame */
DECL|member|mb_pos
r_char
op_star
id|mb_pos
suffix:semicolon
multiline_comment|/* SMbuf receive position */
)brace
suffix:semicolon
DECL|struct|hw_modul
r_struct
id|hw_modul
(brace
multiline_comment|/*&n;&t; * All hardware modul specific variables&n;&t; */
DECL|member|mbuf_pool
r_struct
id|s_mbuf_pool
id|mbuf_pool
suffix:semicolon
DECL|member|r
r_struct
id|hwm_r
id|r
suffix:semicolon
DECL|member|descr_p
r_union
id|s_fp_descr
r_volatile
op_star
id|descr_p
suffix:semicolon
multiline_comment|/* points to the desriptor area */
DECL|member|pass_SMT
id|u_short
id|pass_SMT
suffix:semicolon
multiline_comment|/* pass SMT frames */
DECL|member|pass_NSA
id|u_short
id|pass_NSA
suffix:semicolon
multiline_comment|/* pass all NSA frames */
DECL|member|pass_DB
id|u_short
id|pass_DB
suffix:semicolon
multiline_comment|/* pass Direct Beacon Frames */
DECL|member|pass_llc_promisc
id|u_short
id|pass_llc_promisc
suffix:semicolon
multiline_comment|/* pass all llc frames (default ON) */
DECL|member|llc_rx_pipe
id|SMbuf
op_star
id|llc_rx_pipe
suffix:semicolon
multiline_comment|/* points to the first queued llc fr */
DECL|member|llc_rx_tail
id|SMbuf
op_star
id|llc_rx_tail
suffix:semicolon
multiline_comment|/* points to the last queued llc fr */
DECL|member|queued_rx_frames
r_int
id|queued_rx_frames
suffix:semicolon
multiline_comment|/* number of queued frames */
DECL|member|txd_tx_pipe
id|SMbuf
op_star
id|txd_tx_pipe
suffix:semicolon
multiline_comment|/* points to first mb in the txd ring */
DECL|member|txd_tx_tail
id|SMbuf
op_star
id|txd_tx_tail
suffix:semicolon
multiline_comment|/* points to last mb in the txd ring */
DECL|member|queued_txd_mb
r_int
id|queued_txd_mb
suffix:semicolon
multiline_comment|/* number of SMT MBufs in txd ring */
DECL|member|rx_break
r_int
id|rx_break
suffix:semicolon
multiline_comment|/* rev. was breaked because ind. off */
DECL|member|leave_isr
r_int
id|leave_isr
suffix:semicolon
multiline_comment|/* leave fddi_isr immedeately if set */
DECL|member|isr_flag
r_int
id|isr_flag
suffix:semicolon
multiline_comment|/* set, when HWM is entered from isr */
multiline_comment|/*&n;&t; * varaibles for the current transmit frame&n;&t; */
DECL|member|tx_p
r_struct
id|s_smt_tx_queue
op_star
id|tx_p
suffix:semicolon
multiline_comment|/* pointer to the transmit queue */
DECL|member|tx_descr
id|u_long
id|tx_descr
suffix:semicolon
multiline_comment|/* tx descriptor for FORMAC+ */
DECL|member|tx_len
r_int
id|tx_len
suffix:semicolon
multiline_comment|/* tx frame length */
DECL|member|tx_mb
id|SMbuf
op_star
id|tx_mb
suffix:semicolon
multiline_comment|/* SMT tx MBuf pointer */
DECL|member|tx_data
r_char
op_star
id|tx_data
suffix:semicolon
multiline_comment|/* data pointer to the SMT tx Mbuf */
DECL|member|detec_count
r_int
id|detec_count
suffix:semicolon
multiline_comment|/* counter for out of RxD condition */
DECL|member|rx_len_error
id|u_long
id|rx_len_error
suffix:semicolon
multiline_comment|/* rx len FORMAC != sum of fragments */
)brace
suffix:semicolon
multiline_comment|/*&n; * DEBUG structs and macros&n; */
macro_line|#ifdef&t;DEBUG
DECL|struct|os_debug
r_struct
id|os_debug
(brace
DECL|member|hwm_rx
r_int
id|hwm_rx
suffix:semicolon
DECL|member|hwm_tx
r_int
id|hwm_tx
suffix:semicolon
DECL|member|hwm_gen
r_int
id|hwm_gen
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;DEBUG
macro_line|#ifdef&t;DEBUG_BRD
DECL|macro|DB_P
mdefine_line|#define&t;DB_P&t;smc-&gt;debug
macro_line|#else
DECL|macro|DB_P
mdefine_line|#define DB_P&t;debug
macro_line|#endif
DECL|macro|DB_RX
mdefine_line|#define DB_RX(a,b,c,lev) if (DB_P.d_os.hwm_rx &gt;= (lev))&t;printf(a,b,c)
DECL|macro|DB_TX
mdefine_line|#define DB_TX(a,b,c,lev) if (DB_P.d_os.hwm_tx &gt;= (lev))&t;printf(a,b,c)
DECL|macro|DB_GEN
mdefine_line|#define DB_GEN(a,b,c,lev) if (DB_P.d_os.hwm_gen &gt;= (lev)) printf(a,b,c)
macro_line|#else&t;/* DEBUG */
DECL|macro|DB_RX
mdefine_line|#define DB_RX(a,b,c,lev)
DECL|macro|DB_TX
mdefine_line|#define DB_TX(a,b,c,lev)
DECL|macro|DB_GEN
mdefine_line|#define DB_GEN(a,b,c,lev)
macro_line|#endif&t;/* DEBUG */
macro_line|#ifndef&t;SK_BREAK
DECL|macro|SK_BREAK
mdefine_line|#define&t;SK_BREAK()
macro_line|#endif
multiline_comment|/*&n; * HWM Macros&n; */
multiline_comment|/*&n; *&t;BEGIN_MANUAL_ENTRY(HWM_GET_TX_PHYS)&n; *&t;u_long HWM_GET_TX_PHYS(txd)&n; *&n; * function&t;MACRO&t;&t;(hardware module, hwmtm.h)&n; *&t;&t;This macro may be invoked by the OS-specific module to read&n; *&t;&t;the physical address of the specified TxD.&n; *&n; * para&t;txd&t;pointer to the TxD&n; *&n; *&t;END_MANUAL_ENTRY&n; */
DECL|macro|HWM_GET_TX_PHYS
mdefine_line|#define&t;HWM_GET_TX_PHYS(txd)&t;&t;(u_long)AIX_REVERSE((txd)-&gt;txd_tbadr)
multiline_comment|/*&n; *&t;BEGIN_MANUAL_ENTRY(HWM_GET_TX_LEN)&n; *&t;int HWM_GET_TX_LEN(txd)&n; *&n; * function&t;MACRO&t;&t;(hardware module, hwmtm.h)&n; *&t;&t;This macro may be invoked by the OS-specific module to read&n; *&t;&t;the fragment length of the specified TxD&n; *&n; * para&t;rxd&t;pointer to the TxD&n; *&n; * return&t;the length of the fragment in bytes&n; *&n; *&t;END_MANUAL_ENTRY&n; */
DECL|macro|HWM_GET_TX_LEN
mdefine_line|#define&t;HWM_GET_TX_LEN(txd)&t;((int)AIX_REVERSE((txd)-&gt;txd_tbctrl)&amp; RD_LENGTH)
multiline_comment|/*&n; *&t;BEGIN_MANUAL_ENTRY(HWM_GET_TX_USED)&n; *&t;txd *HWM_GET_TX_USED(smc,queue)&n; *&n; * function&t;MACRO&t;&t;(hardware module, hwmtm.h)&n; *&t;&t;This macro may be invoked by the OS-specific module to get the&n; *&t;&t;number of used TxDs for the queue, specified by the index.&n; *&n; * para&t;queue&t;the number of the send queue: Can be specified by&n; *&t;&t;QUEUE_A0, QUEUE_S or (frame_status &amp; QUEUE_A0)&n; *&n; * return&t;number of used TxDs for this send queue&n; *&n; *&t;END_MANUAL_ENTRY&n; */
DECL|macro|HWM_GET_TX_USED
mdefine_line|#define&t;HWM_GET_TX_USED(smc,queue)&t;(int) (smc)-&gt;hw.fp.tx_q[queue].tx_used
multiline_comment|/*&n; *&t;BEGIN_MANUAL_ENTRY(HWM_GET_CURR_TXD)&n; *&t;txd *HWM_GET_CURR_TXD(smc,queue)&n; *&n; * function&t;MACRO&t;&t;(hardware module, hwmtm.h)&n; *&t;&t;This macro may be invoked by the OS-specific module to get the&n; *&t;&t;pointer to the TxD which points to the current queue put&n; *&t;&t;position.&n; *&n; * para&t;queue&t;the number of the send queue: Can be specified by&n; *&t;&t;QUEUE_A0, QUEUE_S or (frame_status &amp; QUEUE_A0)&n; *&n; * return&t;pointer to the current TxD&n; *&n; *&t;END_MANUAL_ENTRY&n; */
DECL|macro|HWM_GET_CURR_TXD
mdefine_line|#define&t;HWM_GET_CURR_TXD(smc,queue)&t;(struct s_smt_fp_txd volatile *)&bslash;&n;&t;&t;&t;&t;&t;(smc)-&gt;hw.fp.tx_q[queue].tx_curr_put
multiline_comment|/*&n; *&t;BEGIN_MANUAL_ENTRY(HWM_TX_CHECK)&n; *&t;void HWM_TX_CHECK(smc,frame_status,low_water)&n; *&n; * function&t;MACRO&t;&t;(hardware module, hwmtm.h)&n; *&t;&t;This macro is invoked by the OS-specific before it left it&squot;s&n; *&t;&t;driver_send function. This macro calls mac_drv_clear_txd&n; *&t;&t;if the free TxDs of the current transmit queue is equal or&n; *&t;&t;lower than the given low water mark.&n; *&n; * para&t;frame_status&t;status of the frame, see design description&n; *&t;low_water&t;low water mark of free TxD&squot;s&n; *&n; *&t;END_MANUAL_ENTRY&n; */
macro_line|#ifndef HWM_NO_FLOW_CTL
DECL|macro|HWM_TX_CHECK
mdefine_line|#define&t;HWM_TX_CHECK(smc,frame_status,low_water) {&bslash;&n;&t;if ((low_water)&gt;=(smc)-&gt;hw.fp.tx_q[(frame_status)&amp;QUEUE_A0].tx_free) {&bslash;&n;&t;&t;mac_drv_clear_txd(smc) ;&bslash;&n;&t;}&bslash;&n;}
macro_line|#else
DECL|macro|HWM_TX_CHECK
mdefine_line|#define&t;HWM_TX_CHECK(smc,frame_status,low_water)&t;mac_drv_clear_txd(smc)
macro_line|#endif
multiline_comment|/*&n; *&t;BEGIN_MANUAL_ENTRY(HWM_GET_RX_FRAG_LEN)&n; *&t;int HWM_GET_RX_FRAG_LEN(rxd)&n; *&n; * function&t;MACRO&t;&t;(hardware module, hwmtm.h)&n; *&t;&t;This macro may be invoked by the OS-specific module to read&n; *&t;&t;the fragment length of the specified RxD&n; *&n; * para&t;rxd&t;pointer to the RxD&n; *&n; * return&t;the length of the fragment in bytes&n; *&n; *&t;END_MANUAL_ENTRY&n; */
DECL|macro|HWM_GET_RX_FRAG_LEN
mdefine_line|#define&t;HWM_GET_RX_FRAG_LEN(rxd)&t;((int)AIX_REVERSE((rxd)-&gt;rxd_rbctrl)&amp; &bslash;&n;&t;&t;&t;&t;RD_LENGTH)
multiline_comment|/*&n; *&t;BEGIN_MANUAL_ENTRY(HWM_GET_RX_PHYS)&n; *&t;u_long HWM_GET_RX_PHYS(rxd)&n; *&n; * function&t;MACRO&t;&t;(hardware module, hwmtm.h)&n; *&t;&t;This macro may be invoked by the OS-specific module to read&n; *&t;&t;the physical address of the specified RxD.&n; *&n; * para&t;rxd&t;pointer to the RxD&n; *&n; * return&t;the RxD&squot;s physical pointer to the data fragment&n; *&n; *&t;END_MANUAL_ENTRY&n; */
DECL|macro|HWM_GET_RX_PHYS
mdefine_line|#define&t;HWM_GET_RX_PHYS(rxd)&t;(u_long)AIX_REVERSE((rxd)-&gt;rxd_rbadr)
multiline_comment|/*&n; *&t;BEGIN_MANUAL_ENTRY(HWM_GET_RX_USED)&n; *&t;int HWM_GET_RX_USED(smc)&n; *&n; * function&t;MACRO&t;&t;(hardware module, hwmtm.h)&n; *&t;&t;This macro may be invoked by the OS-specific module to get&n; *&t;&t;the count of used RXDs in receive queue 1.&n; *&n; * return&t;the used RXD count of receive queue 1&n; *&n; * NOTE: Remember, because of an ASIC bug at least one RXD should be unused&n; *&t; in the descriptor ring !&n; *&n; *&t;END_MANUAL_ENTRY&n; */
DECL|macro|HWM_GET_RX_USED
mdefine_line|#define&t;HWM_GET_RX_USED(smc)&t;((int)(smc)-&gt;hw.fp.rx_q[QUEUE_R1].rx_used)
multiline_comment|/*&n; *&t;BEGIN_MANUAL_ENTRY(HWM_GET_RX_FREE)&n; *&t;int HWM_GET_RX_FREE(smc)&n; *&n; * function&t;MACRO&t;&t;(hardware module, hwmtm.h)&n; *&t;&t;This macro may be invoked by the OS-specific module to get&n; *&t;&t;the rxd_free count of receive queue 1.&n; *&n; * return&t;the rxd_free count of receive queue 1&n; *&n; *&t;END_MANUAL_ENTRY&n; */
DECL|macro|HWM_GET_RX_FREE
mdefine_line|#define&t;HWM_GET_RX_FREE(smc)&t;((int)(smc)-&gt;hw.fp.rx_q[QUEUE_R1].rx_free-1)
multiline_comment|/*&n; *&t;BEGIN_MANUAL_ENTRY(HWM_GET_CURR_RXD)&n; *&t;rxd *HWM_GET_CURR_RXD(smc)&n; *&n; * function&t;MACRO&t;&t;(hardware module, hwmtm.h)&n; *&t;&t;This macro may be invoked by the OS-specific module to get the&n; *&t;&t;pointer to the RxD which points to the current queue put&n; *&t;&t;position.&n; *&n; * return&t;pointer to the current RxD&n; *&n; *&t;END_MANUAL_ENTRY&n; */
DECL|macro|HWM_GET_CURR_RXD
mdefine_line|#define&t;HWM_GET_CURR_RXD(smc)&t;(struct s_smt_fp_rxd volatile *)&bslash;&n;&t;&t;&t;&t;(smc)-&gt;hw.fp.rx_q[QUEUE_R1].rx_curr_put
multiline_comment|/*&n; *&t;BEGIN_MANUAL_ENTRY(HWM_RX_CHECK)&n; *&t;void HWM_RX_CHECK(smc,low_water)&n; *&n; * function&t;MACRO&t;&t;(hardware module, hwmtm.h)&n; *&t;&t;This macro is invoked by the OS-specific before it left the&n; *&t;&t;function mac_drv_rx_complete. This macro calls mac_drv_fill_rxd&n; *&t;&t;if the number of used RxDs is equal or lower than the&n; *&t;&t;the given low water mark.&n; *&n; * para&t;low_water&t;low water mark of used RxD&squot;s&n; *&n; *&t;END_MANUAL_ENTRY&n; */
macro_line|#ifndef HWM_NO_FLOW_CTL
DECL|macro|HWM_RX_CHECK
mdefine_line|#define&t;HWM_RX_CHECK(smc,low_water) {&bslash;&n;&t;if ((low_water) &gt;= (smc)-&gt;hw.fp.rx_q[QUEUE_R1].rx_used) {&bslash;&n;&t;&t;mac_drv_fill_rxd(smc) ;&bslash;&n;&t;}&bslash;&n;}
macro_line|#else
DECL|macro|HWM_RX_CHECK
mdefine_line|#define&t;HWM_RX_CHECK(smc,low_water)&t;&t;mac_drv_fill_rxd(smc)
macro_line|#endif
macro_line|#ifndef&t;HWM_EBASE
DECL|macro|HWM_EBASE
mdefine_line|#define&t;HWM_EBASE&t;500
macro_line|#endif
DECL|macro|HWM_E0001
mdefine_line|#define&t;HWM_E0001&t;HWM_EBASE + 1
DECL|macro|HWM_E0001_MSG
mdefine_line|#define&t;HWM_E0001_MSG&t;&quot;HWM: Wrong size of s_rxd_os struct&quot;
DECL|macro|HWM_E0002
mdefine_line|#define&t;HWM_E0002&t;HWM_EBASE + 2
DECL|macro|HWM_E0002_MSG
mdefine_line|#define&t;HWM_E0002_MSG&t;&quot;HWM: Wrong size of s_txd_os struct&quot;
DECL|macro|HWM_E0003
mdefine_line|#define&t;HWM_E0003&t;HWM_EBASE + 3
DECL|macro|HWM_E0003_MSG
mdefine_line|#define&t;HWM_E0003_MSG&t;&quot;HWM: smt_free_mbuf() called with NULL pointer&quot;
DECL|macro|HWM_E0004
mdefine_line|#define&t;HWM_E0004&t;HWM_EBASE + 4
DECL|macro|HWM_E0004_MSG
mdefine_line|#define&t;HWM_E0004_MSG&t;&quot;HWM: Parity error rx queue 1&quot;
DECL|macro|HWM_E0005
mdefine_line|#define&t;HWM_E0005&t;HWM_EBASE + 5
DECL|macro|HWM_E0005_MSG
mdefine_line|#define&t;HWM_E0005_MSG&t;&quot;HWM: Encoding error rx queue 1&quot;
DECL|macro|HWM_E0006
mdefine_line|#define&t;HWM_E0006&t;HWM_EBASE + 6
DECL|macro|HWM_E0006_MSG
mdefine_line|#define&t;HWM_E0006_MSG&t;&quot;HWM: Encoding error async tx queue&quot;
DECL|macro|HWM_E0007
mdefine_line|#define&t;HWM_E0007&t;HWM_EBASE + 7
DECL|macro|HWM_E0007_MSG
mdefine_line|#define&t;HWM_E0007_MSG&t;&quot;HWM: Encoding error sync tx queue&quot;
DECL|macro|HWM_E0008
mdefine_line|#define&t;HWM_E0008&t;HWM_EBASE + 8
DECL|macro|HWM_E0008_MSG
mdefine_line|#define&t;HWM_E0008_MSG&t;&quot;&quot;
DECL|macro|HWM_E0009
mdefine_line|#define&t;HWM_E0009&t;HWM_EBASE + 9
DECL|macro|HWM_E0009_MSG
mdefine_line|#define&t;HWM_E0009_MSG&t;&quot;HWM: Out of RxD condition detected&quot;
DECL|macro|HWM_E0010
mdefine_line|#define&t;HWM_E0010&t;HWM_EBASE + 10
DECL|macro|HWM_E0010_MSG
mdefine_line|#define&t;HWM_E0010_MSG&t;&quot;HWM: A protocol layer has tried to send a frame with an invalid frame control&quot;
DECL|macro|HWM_E0011
mdefine_line|#define HWM_E0011&t;HWM_EBASE + 11
DECL|macro|HWM_E0011_MSG
mdefine_line|#define HWM_E0011_MSG&t;&quot;HWM: mac_drv_clear_tx_queue was called although the hardware wasn&squot;t stopped&quot;
DECL|macro|HWM_E0012
mdefine_line|#define HWM_E0012&t;HWM_EBASE + 12
DECL|macro|HWM_E0012_MSG
mdefine_line|#define HWM_E0012_MSG&t;&quot;HWM: mac_drv_clear_rx_queue was called although the hardware wasn&squot;t stopped&quot;
DECL|macro|HWM_E0013
mdefine_line|#define HWM_E0013&t;HWM_EBASE + 13
DECL|macro|HWM_E0013_MSG
mdefine_line|#define HWM_E0013_MSG&t;&quot;HWM: mac_drv_repair_descr was called although the hardware wasn&squot;t stopped&quot;
macro_line|#endif
eof
