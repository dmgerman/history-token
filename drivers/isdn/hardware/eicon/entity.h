multiline_comment|/* $Id: entity.h,v 1.1.2.2 2002/10/02 14:38:37 armin Exp $ */
macro_line|#ifndef __DIVAS_USER_MODE_IDI_ENTITY__
DECL|macro|__DIVAS_USER_MODE_IDI_ENTITY__
mdefine_line|#define __DIVAS_USER_MODE_IDI_ENTITY__
DECL|macro|DIVA_UM_IDI_RC_PENDING
mdefine_line|#define DIVA_UM_IDI_RC_PENDING      0x00000001
DECL|macro|DIVA_UM_IDI_REMOVE_PENDING
mdefine_line|#define DIVA_UM_IDI_REMOVE_PENDING  0x00000002
DECL|macro|DIVA_UM_IDI_TX_FLOW_CONTROL
mdefine_line|#define DIVA_UM_IDI_TX_FLOW_CONTROL 0x00000004
DECL|macro|DIVA_UM_IDI_REMOVED
mdefine_line|#define DIVA_UM_IDI_REMOVED         0x00000008
DECL|macro|DIVA_UM_IDI_ASSIGN_PENDING
mdefine_line|#define DIVA_UM_IDI_ASSIGN_PENDING  0x00000010
DECL|struct|_divas_um_idi_entity
r_typedef
r_struct
id|_divas_um_idi_entity
(brace
DECL|member|link
id|diva_entity_link_t
id|link
suffix:semicolon
multiline_comment|/* should be first */
DECL|member|adapter
id|diva_um_idi_adapter_t
op_star
id|adapter
suffix:semicolon
multiline_comment|/* Back to adapter */
DECL|member|e
id|ENTITY
id|e
suffix:semicolon
DECL|member|os_ref
r_void
op_star
id|os_ref
suffix:semicolon
DECL|member|status
id|dword
id|status
suffix:semicolon
DECL|member|os_context
r_void
op_star
id|os_context
suffix:semicolon
DECL|member|rc_count
r_int
id|rc_count
suffix:semicolon
DECL|member|data
id|diva_um_idi_data_queue_t
id|data
suffix:semicolon
multiline_comment|/* definad by user 1 ... MAX */
DECL|member|rc
id|diva_um_idi_data_queue_t
id|rc
suffix:semicolon
multiline_comment|/* two entries */
DECL|member|XData
id|BUFFERS
id|XData
suffix:semicolon
DECL|member|RData
id|BUFFERS
id|RData
suffix:semicolon
DECL|member|buffer
id|byte
id|buffer
(braket
l_int|2048
op_plus
l_int|512
)braket
suffix:semicolon
DECL|typedef|divas_um_idi_entity_t
)brace
id|divas_um_idi_entity_t
suffix:semicolon
macro_line|#endif
eof
