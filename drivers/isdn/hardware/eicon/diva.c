multiline_comment|/* $Id: diva.c,v 1.21.4.1 2004/05/08 14:33:43 armin Exp $ */
DECL|macro|CARDTYPE_H_WANT_DATA
mdefine_line|#define CARDTYPE_H_WANT_DATA            1
DECL|macro|CARDTYPE_H_WANT_IDI_DATA
mdefine_line|#define CARDTYPE_H_WANT_IDI_DATA        0
DECL|macro|CARDTYPE_H_WANT_RESOURCE_DATA
mdefine_line|#define CARDTYPE_H_WANT_RESOURCE_DATA   0
DECL|macro|CARDTYPE_H_WANT_FILE_DATA
mdefine_line|#define CARDTYPE_H_WANT_FILE_DATA       0
macro_line|#include &quot;platform.h&quot;
macro_line|#include &quot;debuglib.h&quot;
macro_line|#include &quot;cardtype.h&quot;
macro_line|#include &quot;pc.h&quot;
macro_line|#include &quot;di_defs.h&quot;
macro_line|#include &quot;di.h&quot;
macro_line|#include &quot;io.h&quot;
macro_line|#include &quot;pc_maint.h&quot;
macro_line|#include &quot;xdi_msg.h&quot;
macro_line|#include &quot;xdi_adapter.h&quot;
macro_line|#include &quot;diva_pci.h&quot;
macro_line|#include &quot;diva.h&quot;
macro_line|#ifdef CONFIG_ISDN_DIVAS_PRIPCI
macro_line|#include &quot;os_pri.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DIVAS_BRIPCI
macro_line|#include &quot;os_bri.h&quot;
macro_line|#include &quot;os_4bri.h&quot;
macro_line|#endif
DECL|variable|IoAdapters
id|PISDN_ADAPTER
id|IoAdapters
(braket
id|MAX_ADAPTER
)braket
suffix:semicolon
r_extern
id|IDI_CALL
id|Requests
(braket
id|MAX_ADAPTER
)braket
suffix:semicolon
r_extern
r_int
id|create_adapter_proc
c_func
(paren
id|diva_os_xdi_adapter_t
op_star
id|a
)paren
suffix:semicolon
r_extern
r_void
id|remove_adapter_proc
c_func
(paren
id|diva_os_xdi_adapter_t
op_star
id|a
)paren
suffix:semicolon
DECL|macro|DivaIdiReqFunc
mdefine_line|#define DivaIdiReqFunc(N) &bslash;&n;static void DivaIdiRequest##N(ENTITY *e) &bslash;&n;{ if ( IoAdapters[N] ) (* IoAdapters[N]-&gt;DIRequest)(IoAdapters[N], e) ; }
multiline_comment|/*&n;**  Create own 32 Adapters&n;*/
id|DivaIdiReqFunc
c_func
(paren
l_int|0
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|1
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|2
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|3
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|4
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|5
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|6
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|7
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|8
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|9
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|10
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|11
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|12
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|13
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|14
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|15
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|16
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|17
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|18
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|19
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|20
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|21
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|22
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|23
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|24
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|25
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|26
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|27
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|28
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|29
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|30
)paren
id|DivaIdiReqFunc
c_func
(paren
l_int|31
)paren
r_struct
id|pt_regs
suffix:semicolon
multiline_comment|/*&n;**  LOCALS&n;*/
r_static
id|LIST_HEAD
c_func
(paren
id|adapter_queue
)paren
suffix:semicolon
DECL|struct|_diva_get_xlog
r_typedef
r_struct
id|_diva_get_xlog
(brace
DECL|member|command
id|word
id|command
suffix:semicolon
DECL|member|req
id|byte
id|req
suffix:semicolon
DECL|member|rc
id|byte
id|rc
suffix:semicolon
DECL|member|data
id|byte
id|data
(braket
r_sizeof
(paren
r_struct
id|mi_pc_maint
)paren
)braket
suffix:semicolon
DECL|typedef|diva_get_xlog_t
)brace
id|diva_get_xlog_t
suffix:semicolon
DECL|struct|_diva_supported_cards_info
r_typedef
r_struct
id|_diva_supported_cards_info
(brace
DECL|member|CardOrdinal
r_int
id|CardOrdinal
suffix:semicolon
DECL|member|init_card
id|diva_init_card_proc_t
id|init_card
suffix:semicolon
DECL|typedef|diva_supported_cards_info_t
)brace
id|diva_supported_cards_info_t
suffix:semicolon
DECL|variable|divas_supported_cards
r_static
id|diva_supported_cards_info_t
id|divas_supported_cards
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_ISDN_DIVAS_PRIPCI
multiline_comment|/*&n;&t;   PRI Cards&n;&t; */
(brace
id|CARDTYPE_DIVASRV_P_30M_PCI
comma
id|diva_pri_init_card
)brace
comma
multiline_comment|/*&n;&t;   PRI Rev.2 Cards&n;&t; */
(brace
id|CARDTYPE_DIVASRV_P_30M_V2_PCI
comma
id|diva_pri_init_card
)brace
comma
multiline_comment|/*&n;&t;   PRI Rev.2 VoIP Cards&n;&t; */
(brace
id|CARDTYPE_DIVASRV_VOICE_P_30M_V2_PCI
comma
id|diva_pri_init_card
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DIVAS_BRIPCI
multiline_comment|/*&n;&t;   4BRI Rev 1 Cards&n;&t; */
(brace
id|CARDTYPE_DIVASRV_Q_8M_PCI
comma
id|diva_4bri_init_card
)brace
comma
(brace
id|CARDTYPE_DIVASRV_VOICE_Q_8M_PCI
comma
id|diva_4bri_init_card
)brace
comma
multiline_comment|/*&n;&t;   4BRI Rev 2 Cards&n;&t; */
(brace
id|CARDTYPE_DIVASRV_Q_8M_V2_PCI
comma
id|diva_4bri_init_card
)brace
comma
(brace
id|CARDTYPE_DIVASRV_VOICE_Q_8M_V2_PCI
comma
id|diva_4bri_init_card
)brace
comma
multiline_comment|/*&n;&t;   4BRI Based BRI Rev 2 Cards&n;&t; */
(brace
id|CARDTYPE_DIVASRV_B_2M_V2_PCI
comma
id|diva_4bri_init_card
)brace
comma
(brace
id|CARDTYPE_DIVASRV_B_2F_PCI
comma
id|diva_4bri_init_card
)brace
comma
(brace
id|CARDTYPE_DIVASRV_VOICE_B_2M_V2_PCI
comma
id|diva_4bri_init_card
)brace
comma
multiline_comment|/*&n;&t;   BRI&n;&t; */
(brace
id|CARDTYPE_MAESTRA_PCI
comma
id|diva_bri_init_card
)brace
comma
macro_line|#endif
multiline_comment|/*&n;&t;   EOL&n;&t; */
(brace
op_minus
l_int|1
comma
l_int|0
)brace
)brace
suffix:semicolon
r_static
r_void
id|diva_init_request_array
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
op_star
id|divas_create_pci_card
c_func
(paren
r_int
id|handle
comma
r_void
op_star
id|pci_dev_handle
)paren
suffix:semicolon
DECL|variable|adapter_lock
r_static
id|diva_os_spin_lock_t
id|adapter_lock
suffix:semicolon
DECL|function|diva_find_free_adapters
r_static
r_int
id|diva_find_free_adapters
c_func
(paren
r_int
id|base
comma
r_int
id|nr
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|IoAdapters
(braket
id|base
op_plus
id|i
)braket
)paren
(brace
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|diva_q_get_next
r_static
id|diva_os_xdi_adapter_t
op_star
id|diva_q_get_next
c_func
(paren
r_struct
id|list_head
op_star
id|what
)paren
(brace
id|diva_os_xdi_adapter_t
op_star
id|a
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|what
op_logical_and
(paren
id|what-&gt;next
op_ne
op_amp
id|adapter_queue
)paren
)paren
id|a
op_assign
id|list_entry
c_func
(paren
id|what-&gt;next
comma
id|diva_os_xdi_adapter_t
comma
id|link
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;    Add card to the card list&n;   -------------------------------------------------------------------------- */
DECL|function|diva_driver_add_card
r_void
op_star
id|diva_driver_add_card
c_func
(paren
r_void
op_star
id|pdev
comma
r_int
r_int
id|CardOrdinal
)paren
(brace
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
id|diva_os_xdi_adapter_t
op_star
id|pdiva
comma
op_star
id|pa
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|max
comma
id|nr
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|divas_supported_cards
(braket
id|i
)braket
dot
id|CardOrdinal
op_ne
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|divas_supported_cards
(braket
id|i
)braket
dot
id|CardOrdinal
op_eq
id|CardOrdinal
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pdiva
op_assign
id|divas_create_pci_card
c_func
(paren
id|i
comma
id|pdev
)paren
)paren
)paren
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|CardOrdinal
)paren
(brace
r_case
id|CARDTYPE_DIVASRV_Q_8M_PCI
suffix:colon
r_case
id|CARDTYPE_DIVASRV_VOICE_Q_8M_PCI
suffix:colon
r_case
id|CARDTYPE_DIVASRV_Q_8M_V2_PCI
suffix:colon
r_case
id|CARDTYPE_DIVASRV_VOICE_Q_8M_V2_PCI
suffix:colon
id|max
op_assign
id|MAX_ADAPTER
op_minus
l_int|4
suffix:semicolon
id|nr
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|max
op_assign
id|MAX_ADAPTER
suffix:semicolon
id|nr
op_assign
l_int|1
suffix:semicolon
)brace
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;add card&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|diva_find_free_adapters
c_func
(paren
id|i
comma
id|nr
)paren
)paren
(brace
id|pdiva-&gt;controller
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|pdiva-&gt;xdi_adapter.ANum
op_assign
id|pdiva-&gt;controller
suffix:semicolon
id|IoAdapters
(braket
id|i
)braket
op_assign
op_amp
id|pdiva-&gt;xdi_adapter
suffix:semicolon
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;add card&quot;
)paren
suffix:semicolon
id|create_adapter_proc
c_func
(paren
id|pdiva
)paren
suffix:semicolon
multiline_comment|/* add adapter to proc file system */
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot;add %s:%d&quot;
comma
id|CardProperties
(braket
id|CardOrdinal
)braket
dot
id|Name
comma
id|pdiva-&gt;controller
)paren
)paren
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;add card&quot;
)paren
suffix:semicolon
id|pa
op_assign
id|pdiva
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|nr
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/* slave adapters, if any */
id|pa
op_assign
id|diva_q_get_next
c_func
(paren
op_amp
id|pa-&gt;link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pa
op_logical_and
op_logical_neg
id|pa-&gt;interface.cleanup_adapter_proc
)paren
(brace
id|pa-&gt;controller
op_assign
id|i
op_plus
l_int|1
op_plus
id|j
suffix:semicolon
id|pa-&gt;xdi_adapter.ANum
op_assign
id|pa-&gt;controller
suffix:semicolon
id|IoAdapters
(braket
id|i
op_plus
id|j
)braket
op_assign
op_amp
id|pa-&gt;xdi_adapter
suffix:semicolon
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;add card&quot;
)paren
suffix:semicolon
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot;add slave adapter (%d)&quot;
comma
id|pa-&gt;controller
)paren
)paren
id|create_adapter_proc
c_func
(paren
id|pa
)paren
suffix:semicolon
multiline_comment|/* add adapter to proc file system */
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;add card&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;slave adapter problem&quot;
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;add card&quot;
)paren
suffix:semicolon
r_return
(paren
id|pdiva
)paren
suffix:semicolon
)brace
)brace
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;add card&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;   Not able to add adapter - remove it and return error&n;&t;&t;&t; */
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;can not alloc request array&quot;
)paren
)paren
id|diva_driver_remove_card
c_func
(paren
id|pdiva
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;    Called on driver load, MAIN, main, DriverEntry&n;   -------------------------------------------------------------------------- */
DECL|function|divasa_xdi_driver_entry
r_int
id|divasa_xdi_driver_entry
c_func
(paren
r_void
)paren
(brace
id|diva_os_initialize_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
l_string|&quot;adapter&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|IoAdapters
(braket
l_int|0
)braket
comma
l_int|0x00
comma
r_sizeof
(paren
id|IoAdapters
)paren
)paren
suffix:semicolon
id|diva_init_request_array
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;    Remove adapter from list&n;   -------------------------------------------------------------------------- */
DECL|function|get_and_remove_from_queue
r_static
id|diva_os_xdi_adapter_t
op_star
id|get_and_remove_from_queue
c_func
(paren
r_void
)paren
(brace
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
id|diva_os_xdi_adapter_t
op_star
id|a
op_assign
l_int|NULL
suffix:semicolon
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;driver_unload&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|adapter_queue
)paren
)paren
(brace
id|a
op_assign
id|list_entry
c_func
(paren
id|adapter_queue.next
comma
id|diva_os_xdi_adapter_t
comma
id|link
)paren
suffix:semicolon
id|list_del
c_func
(paren
id|adapter_queue.next
)paren
suffix:semicolon
)brace
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;driver_unload&quot;
)paren
suffix:semicolon
r_return
(paren
id|a
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;    Remove card from the card list&n;   -------------------------------------------------------------------------- */
DECL|function|diva_driver_remove_card
r_void
id|diva_driver_remove_card
c_func
(paren
r_void
op_star
id|pdiva
)paren
(brace
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
id|diva_os_xdi_adapter_t
op_star
id|a
(braket
l_int|4
)braket
suffix:semicolon
id|diva_os_xdi_adapter_t
op_star
id|pa
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pa
op_assign
id|a
(braket
l_int|0
)braket
op_assign
(paren
id|diva_os_xdi_adapter_t
op_star
)paren
id|pdiva
suffix:semicolon
id|a
(braket
l_int|1
)braket
op_assign
id|a
(braket
l_int|2
)braket
op_assign
id|a
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;remode adapter&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|pa
op_assign
id|diva_q_get_next
c_func
(paren
op_amp
id|pa-&gt;link
)paren
)paren
op_logical_and
op_logical_neg
id|pa-&gt;interface.cleanup_adapter_proc
)paren
(brace
id|a
(braket
id|i
)braket
op_assign
id|pa
suffix:semicolon
)brace
r_else
(brace
r_break
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
(paren
id|i
OL
l_int|4
)paren
op_logical_and
id|a
(braket
id|i
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|a
(braket
id|i
)braket
op_member_access_from_pointer
id|link
)paren
suffix:semicolon
)brace
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;driver_unload&quot;
)paren
suffix:semicolon
(paren
op_star
(paren
id|a
(braket
l_int|0
)braket
op_member_access_from_pointer
id|interface.cleanup_adapter_proc
)paren
)paren
(paren
id|a
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|a
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
id|a
(braket
id|i
)braket
op_member_access_from_pointer
id|controller
)paren
(brace
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot;remove adapter (%d)&quot;
comma
id|a
(braket
id|i
)braket
op_member_access_from_pointer
id|controller
)paren
)paren
id|IoAdapters
(braket
id|a
(braket
id|i
)braket
op_member_access_from_pointer
id|controller
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|remove_adapter_proc
c_func
(paren
id|a
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|a
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;    Create diva PCI adapter and init internal adapter structures&n;   -------------------------------------------------------------------------- */
DECL|function|divas_create_pci_card
r_static
r_void
op_star
id|divas_create_pci_card
c_func
(paren
r_int
id|handle
comma
r_void
op_star
id|pci_dev_handle
)paren
(brace
id|diva_supported_cards_info_t
op_star
id|pI
op_assign
op_amp
id|divas_supported_cards
(braket
id|handle
)braket
suffix:semicolon
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
id|diva_os_xdi_adapter_t
op_star
id|a
suffix:semicolon
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot;found %d-%s&quot;
comma
id|pI-&gt;CardOrdinal
comma
id|CardProperties
(braket
id|pI-&gt;CardOrdinal
)braket
dot
id|Name
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|a
op_assign
(paren
id|diva_os_xdi_adapter_t
op_star
)paren
id|diva_os_malloc
c_func
(paren
l_int|0
comma
r_sizeof
(paren
op_star
id|a
)paren
)paren
)paren
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: can&squot;t alloc adapter&quot;
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|a
comma
l_int|0x00
comma
r_sizeof
(paren
op_star
id|a
)paren
)paren
suffix:semicolon
id|a-&gt;CardIndex
op_assign
id|handle
suffix:semicolon
id|a-&gt;CardOrdinal
op_assign
id|pI-&gt;CardOrdinal
suffix:semicolon
id|a-&gt;Bus
op_assign
id|DIVAS_XDI_ADAPTER_BUS_PCI
suffix:semicolon
id|a-&gt;xdi_adapter.cardType
op_assign
id|a-&gt;CardOrdinal
suffix:semicolon
id|a-&gt;resources.pci.bus
op_assign
id|diva_os_get_pci_bus
c_func
(paren
id|pci_dev_handle
)paren
suffix:semicolon
id|a-&gt;resources.pci.func
op_assign
id|diva_os_get_pci_func
c_func
(paren
id|pci_dev_handle
)paren
suffix:semicolon
id|a-&gt;resources.pci.hdev
op_assign
id|pci_dev_handle
suffix:semicolon
multiline_comment|/*&n;&t;   Add master adapter first, so slave adapters will receive higher&n;&t;   numbers as master adapter&n;&t; */
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;found_pci_card&quot;
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|a-&gt;link
comma
op_amp
id|adapter_queue
)paren
suffix:semicolon
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;found_pci_card&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
(paren
id|pI-&gt;init_card
)paren
)paren
(paren
id|a
)paren
)paren
(brace
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;found_pci_card&quot;
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|a-&gt;link
)paren
suffix:semicolon
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;found_pci_card&quot;
)paren
suffix:semicolon
id|diva_os_free
c_func
(paren
l_int|0
comma
id|a
)paren
suffix:semicolon
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: can&squot;t get adapter resources&quot;
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
id|a
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;    Called on driver unload FINIT, finit, Unload&n;   -------------------------------------------------------------------------- */
DECL|function|divasa_xdi_driver_unload
r_void
id|divasa_xdi_driver_unload
c_func
(paren
r_void
)paren
(brace
id|diva_os_xdi_adapter_t
op_star
id|a
suffix:semicolon
r_while
c_loop
(paren
(paren
id|a
op_assign
id|get_and_remove_from_queue
c_func
(paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|a-&gt;interface.cleanup_adapter_proc
)paren
(brace
(paren
op_star
(paren
id|a-&gt;interface.cleanup_adapter_proc
)paren
)paren
(paren
id|a
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|a-&gt;controller
)paren
(brace
id|IoAdapters
(braket
id|a-&gt;controller
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|remove_adapter_proc
c_func
(paren
id|a
)paren
suffix:semicolon
)brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|a
)paren
suffix:semicolon
)brace
id|diva_os_destroy_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
l_string|&quot;adapter&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;**  Receive and process command from user mode utility&n;*/
DECL|function|diva_xdi_open_adapter
r_void
op_star
id|diva_xdi_open_adapter
c_func
(paren
r_void
op_star
id|os_handle
comma
r_const
r_void
op_star
id|src
comma
r_int
id|length
comma
id|divas_xdi_copy_from_user_fn_t
id|cp_fn
)paren
(brace
id|diva_xdi_um_cfg_cmd_t
id|msg
suffix:semicolon
id|diva_os_xdi_adapter_t
op_star
id|a
op_assign
l_int|NULL
suffix:semicolon
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|length
OL
r_sizeof
(paren
id|diva_xdi_um_cfg_cmd_t
)paren
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: A(?) open, msg too small (%d &lt; %d)&quot;
comma
id|length
comma
r_sizeof
(paren
id|diva_xdi_um_cfg_cmd_t
)paren
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|cp_fn
)paren
(paren
id|os_handle
comma
op_amp
id|msg
comma
id|src
comma
r_sizeof
(paren
id|msg
)paren
)paren
op_le
l_int|0
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: A(?) open, write error&quot;
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;open_adapter&quot;
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|adapter_queue
)paren
(brace
id|a
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
id|diva_os_xdi_adapter_t
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;controller
op_eq
(paren
r_int
)paren
id|msg.adapter
)paren
r_break
suffix:semicolon
id|a
op_assign
l_int|NULL
suffix:semicolon
)brace
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;open_adapter&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: A(%d) open, adapter not found&quot;
comma
id|msg.adapter
)paren
)paren
)brace
r_return
(paren
id|a
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;**  Easy cleanup mailbox status&n;*/
DECL|function|diva_xdi_close_adapter
r_void
id|diva_xdi_close_adapter
c_func
(paren
r_void
op_star
id|adapter
comma
r_void
op_star
id|os_handle
)paren
(brace
id|diva_os_xdi_adapter_t
op_star
id|a
op_assign
(paren
id|diva_os_xdi_adapter_t
op_star
)paren
id|adapter
suffix:semicolon
id|a-&gt;xdi_mbox.status
op_and_assign
op_complement
id|DIVA_XDI_MBOX_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;xdi_mbox.data
)paren
(brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|a-&gt;xdi_mbox.data
)paren
suffix:semicolon
id|a-&gt;xdi_mbox.data
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_int
DECL|function|diva_xdi_write
id|diva_xdi_write
c_func
(paren
r_void
op_star
id|adapter
comma
r_void
op_star
id|os_handle
comma
r_const
r_void
op_star
id|src
comma
r_int
id|length
comma
id|divas_xdi_copy_from_user_fn_t
id|cp_fn
)paren
(brace
id|diva_os_xdi_adapter_t
op_star
id|a
op_assign
(paren
id|diva_os_xdi_adapter_t
op_star
)paren
id|adapter
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;xdi_mbox.status
op_amp
id|DIVA_XDI_MBOX_BUSY
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: A(%d) write, mbox busy&quot;
comma
id|a-&gt;controller
)paren
)paren
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|length
OL
r_sizeof
(paren
id|diva_xdi_um_cfg_cmd_t
)paren
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: A(%d) write, message too small (%d &lt; %d)&quot;
comma
id|a-&gt;controller
comma
id|length
comma
r_sizeof
(paren
id|diva_xdi_um_cfg_cmd_t
)paren
)paren
)paren
r_return
(paren
op_minus
l_int|3
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
op_assign
id|diva_os_malloc
c_func
(paren
l_int|0
comma
id|length
)paren
)paren
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: A(%d) write, ENOMEM&quot;
comma
id|a-&gt;controller
)paren
)paren
r_return
(paren
op_minus
l_int|2
)paren
suffix:semicolon
)brace
id|length
op_assign
(paren
op_star
id|cp_fn
)paren
(paren
id|os_handle
comma
id|data
comma
id|src
comma
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
(paren
id|a-&gt;interface.cmd_proc
)paren
)paren
(paren
id|a
comma
(paren
id|diva_xdi_um_cfg_cmd_t
op_star
)paren
id|data
comma
id|length
)paren
)paren
(brace
id|length
op_assign
op_minus
l_int|3
suffix:semicolon
)brace
)brace
r_else
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: A(%d) write error (%d)&quot;
comma
id|a-&gt;controller
comma
id|length
)paren
)paren
)brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|data
)paren
suffix:semicolon
r_return
(paren
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;**  Write answers to user mode utility, if any&n;*/
r_int
DECL|function|diva_xdi_read
id|diva_xdi_read
c_func
(paren
r_void
op_star
id|adapter
comma
r_void
op_star
id|os_handle
comma
r_void
op_star
id|dst
comma
r_int
id|max_length
comma
id|divas_xdi_copy_to_user_fn_t
id|cp_fn
)paren
(brace
id|diva_os_xdi_adapter_t
op_star
id|a
op_assign
(paren
id|diva_os_xdi_adapter_t
op_star
)paren
id|adapter
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|a-&gt;xdi_mbox.status
op_amp
id|DIVA_XDI_MBOX_BUSY
)paren
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: A(%d) rx mbox empty&quot;
comma
id|a-&gt;controller
)paren
)paren
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|a-&gt;xdi_mbox.data
)paren
(brace
id|a-&gt;xdi_mbox.status
op_and_assign
op_complement
id|DIVA_XDI_MBOX_BUSY
suffix:semicolon
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: A(%d) rx ENOMEM&quot;
comma
id|a-&gt;controller
)paren
)paren
r_return
(paren
op_minus
l_int|2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|max_length
OL
id|a-&gt;xdi_mbox.data_length
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;A: A(%d) rx buffer too short(%d &lt; %d)&quot;
comma
id|a-&gt;controller
comma
id|max_length
comma
id|a-&gt;xdi_mbox.data_length
)paren
)paren
r_return
(paren
op_minus
l_int|3
)paren
suffix:semicolon
)brace
id|ret
op_assign
(paren
op_star
id|cp_fn
)paren
(paren
id|os_handle
comma
id|dst
comma
id|a-&gt;xdi_mbox.data
comma
id|a-&gt;xdi_mbox.data_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
(brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|a-&gt;xdi_mbox.data
)paren
suffix:semicolon
id|a-&gt;xdi_mbox.data
op_assign
l_int|0
suffix:semicolon
id|a-&gt;xdi_mbox.status
op_and_assign
op_complement
id|DIVA_XDI_MBOX_BUSY
suffix:semicolon
)brace
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
DECL|function|diva_os_irq_wrapper
id|irqreturn_t
id|diva_os_irq_wrapper
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|context
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|diva_os_xdi_adapter_t
op_star
id|a
op_assign
(paren
id|diva_os_xdi_adapter_t
op_star
)paren
id|context
suffix:semicolon
id|diva_xdi_clear_interrupts_proc_t
id|clear_int_proc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a
op_logical_or
op_logical_neg
id|a-&gt;xdi_adapter.diva_isr_handler
)paren
(brace
r_return
id|IRQ_NONE
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|clear_int_proc
op_assign
id|a-&gt;clear_interrupts_proc
)paren
)paren
(brace
(paren
op_star
id|clear_int_proc
)paren
(paren
id|a
)paren
suffix:semicolon
id|a-&gt;clear_interrupts_proc
op_assign
l_int|0
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
(paren
op_star
(paren
id|a-&gt;xdi_adapter.diva_isr_handler
)paren
)paren
(paren
op_amp
id|a-&gt;xdi_adapter
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|diva_init_request_array
r_static
r_void
id|diva_init_request_array
c_func
(paren
r_void
)paren
(brace
id|Requests
(braket
l_int|0
)braket
op_assign
id|DivaIdiRequest0
suffix:semicolon
id|Requests
(braket
l_int|1
)braket
op_assign
id|DivaIdiRequest1
suffix:semicolon
id|Requests
(braket
l_int|2
)braket
op_assign
id|DivaIdiRequest2
suffix:semicolon
id|Requests
(braket
l_int|3
)braket
op_assign
id|DivaIdiRequest3
suffix:semicolon
id|Requests
(braket
l_int|4
)braket
op_assign
id|DivaIdiRequest4
suffix:semicolon
id|Requests
(braket
l_int|5
)braket
op_assign
id|DivaIdiRequest5
suffix:semicolon
id|Requests
(braket
l_int|6
)braket
op_assign
id|DivaIdiRequest6
suffix:semicolon
id|Requests
(braket
l_int|7
)braket
op_assign
id|DivaIdiRequest7
suffix:semicolon
id|Requests
(braket
l_int|8
)braket
op_assign
id|DivaIdiRequest8
suffix:semicolon
id|Requests
(braket
l_int|9
)braket
op_assign
id|DivaIdiRequest9
suffix:semicolon
id|Requests
(braket
l_int|10
)braket
op_assign
id|DivaIdiRequest10
suffix:semicolon
id|Requests
(braket
l_int|11
)braket
op_assign
id|DivaIdiRequest11
suffix:semicolon
id|Requests
(braket
l_int|12
)braket
op_assign
id|DivaIdiRequest12
suffix:semicolon
id|Requests
(braket
l_int|13
)braket
op_assign
id|DivaIdiRequest13
suffix:semicolon
id|Requests
(braket
l_int|14
)braket
op_assign
id|DivaIdiRequest14
suffix:semicolon
id|Requests
(braket
l_int|15
)braket
op_assign
id|DivaIdiRequest15
suffix:semicolon
id|Requests
(braket
l_int|16
)braket
op_assign
id|DivaIdiRequest16
suffix:semicolon
id|Requests
(braket
l_int|17
)braket
op_assign
id|DivaIdiRequest17
suffix:semicolon
id|Requests
(braket
l_int|18
)braket
op_assign
id|DivaIdiRequest18
suffix:semicolon
id|Requests
(braket
l_int|19
)braket
op_assign
id|DivaIdiRequest19
suffix:semicolon
id|Requests
(braket
l_int|20
)braket
op_assign
id|DivaIdiRequest20
suffix:semicolon
id|Requests
(braket
l_int|21
)braket
op_assign
id|DivaIdiRequest21
suffix:semicolon
id|Requests
(braket
l_int|22
)braket
op_assign
id|DivaIdiRequest22
suffix:semicolon
id|Requests
(braket
l_int|23
)braket
op_assign
id|DivaIdiRequest23
suffix:semicolon
id|Requests
(braket
l_int|24
)braket
op_assign
id|DivaIdiRequest24
suffix:semicolon
id|Requests
(braket
l_int|25
)braket
op_assign
id|DivaIdiRequest25
suffix:semicolon
id|Requests
(braket
l_int|26
)braket
op_assign
id|DivaIdiRequest26
suffix:semicolon
id|Requests
(braket
l_int|27
)braket
op_assign
id|DivaIdiRequest27
suffix:semicolon
id|Requests
(braket
l_int|28
)braket
op_assign
id|DivaIdiRequest28
suffix:semicolon
id|Requests
(braket
l_int|29
)braket
op_assign
id|DivaIdiRequest29
suffix:semicolon
id|Requests
(braket
l_int|30
)braket
op_assign
id|DivaIdiRequest30
suffix:semicolon
id|Requests
(braket
l_int|31
)braket
op_assign
id|DivaIdiRequest31
suffix:semicolon
)brace
DECL|function|diva_xdi_display_adapter_features
r_void
id|diva_xdi_display_adapter_features
c_func
(paren
r_int
id|card
)paren
(brace
id|dword
id|features
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
op_logical_or
(paren
(paren
id|card
op_minus
l_int|1
)paren
op_ge
id|MAX_ADAPTER
)paren
op_logical_or
op_logical_neg
id|IoAdapters
(braket
id|card
op_minus
l_int|1
)braket
)paren
(brace
r_return
suffix:semicolon
)brace
id|card
op_decrement
suffix:semicolon
id|features
op_assign
id|IoAdapters
(braket
id|card
)braket
op_member_access_from_pointer
id|Properties.Features
suffix:semicolon
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot;FEATURES FOR ADAPTER: %d&quot;
comma
id|card
op_plus
l_int|1
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_FAX3          :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_FAX3
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_MODEM         :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_MODEM
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_POST          :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_POST
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_V110          :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_V110
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_V120          :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_V120
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_POTS          :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_POTS
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_CODEC         :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_CODEC
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_MANAGE        :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_MANAGE
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_V_42          :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_V_42
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_EXTD_FAX      :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_EXTD_FAX
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_AT_PARSER     :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_AT_PARSER
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot; DI_VOICE_OVER_IP :  %s&quot;
comma
(paren
id|features
op_amp
id|DI_VOICE_OVER_IP
)paren
ques
c_cond
l_string|&quot;Y&quot;
suffix:colon
l_string|&quot;N&quot;
)paren
)paren
)brace
DECL|function|diva_add_slave_adapter
r_void
id|diva_add_slave_adapter
c_func
(paren
id|diva_os_xdi_adapter_t
op_star
id|a
)paren
(brace
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;add_slave&quot;
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|a-&gt;link
comma
op_amp
id|adapter_queue
)paren
suffix:semicolon
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|adapter_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;add_slave&quot;
)paren
suffix:semicolon
)brace
DECL|function|diva_card_read_xlog
r_int
id|diva_card_read_xlog
c_func
(paren
id|diva_os_xdi_adapter_t
op_star
id|a
)paren
(brace
id|diva_get_xlog_t
op_star
id|req
suffix:semicolon
id|byte
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a-&gt;xdi_adapter.Initialized
op_logical_or
op_logical_neg
id|a-&gt;xdi_adapter.DIRequest
)paren
(brace
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
op_assign
id|diva_os_malloc
c_func
(paren
l_int|0
comma
r_sizeof
(paren
r_struct
id|mi_pc_maint
)paren
)paren
)paren
)paren
(brace
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|data
comma
l_int|0x00
comma
r_sizeof
(paren
r_struct
id|mi_pc_maint
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|req
op_assign
id|diva_os_malloc
c_func
(paren
l_int|0
comma
r_sizeof
(paren
op_star
id|req
)paren
)paren
)paren
)paren
(brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|data
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|req-&gt;command
op_assign
l_int|0x0400
suffix:semicolon
id|req-&gt;req
op_assign
id|LOG
suffix:semicolon
id|req-&gt;rc
op_assign
l_int|0x00
suffix:semicolon
(paren
op_star
(paren
id|a-&gt;xdi_adapter.DIRequest
)paren
)paren
(paren
op_amp
id|a-&gt;xdi_adapter
comma
(paren
id|ENTITY
op_star
)paren
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req-&gt;rc
op_logical_or
id|req-&gt;req
)paren
(brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|data
)paren
suffix:semicolon
id|diva_os_free
c_func
(paren
l_int|0
comma
id|req
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|data
comma
op_amp
id|req-&gt;req
comma
r_sizeof
(paren
r_struct
id|mi_pc_maint
)paren
)paren
suffix:semicolon
id|diva_os_free
c_func
(paren
l_int|0
comma
id|req
)paren
suffix:semicolon
id|a-&gt;xdi_mbox.data_length
op_assign
r_sizeof
(paren
r_struct
id|mi_pc_maint
)paren
suffix:semicolon
id|a-&gt;xdi_mbox.data
op_assign
id|data
suffix:semicolon
id|a-&gt;xdi_mbox.status
op_assign
id|DIVA_XDI_MBOX_BUSY
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|xdiFreeFile
r_void
id|xdiFreeFile
c_func
(paren
r_void
op_star
id|handle
)paren
(brace
)brace
eof
