multiline_comment|/* $Id: adapter.h,v 1.1.2.2 2002/10/02 14:38:37 armin Exp $ */
macro_line|#ifndef __DIVA_USER_MODE_IDI_ADAPTER_H__
DECL|macro|__DIVA_USER_MODE_IDI_ADAPTER_H__
mdefine_line|#define __DIVA_USER_MODE_IDI_ADAPTER_H__
DECL|macro|DIVA_UM_IDI_ADAPTER_REMOVED
mdefine_line|#define DIVA_UM_IDI_ADAPTER_REMOVED 0x00000001
DECL|struct|_diva_um_idi_adapter
r_typedef
r_struct
id|_diva_um_idi_adapter
(brace
DECL|member|link
id|diva_entity_link_t
id|link
suffix:semicolon
DECL|member|d
id|DESCRIPTOR
id|d
suffix:semicolon
DECL|member|adapter_nr
r_int
id|adapter_nr
suffix:semicolon
DECL|member|entity_q
id|diva_entity_queue_t
id|entity_q
suffix:semicolon
multiline_comment|/* entities linked to this adapter */
DECL|member|status
id|dword
id|status
suffix:semicolon
DECL|typedef|diva_um_idi_adapter_t
)brace
id|diva_um_idi_adapter_t
suffix:semicolon
macro_line|#endif
eof
