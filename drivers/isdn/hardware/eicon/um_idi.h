multiline_comment|/* $Id: um_idi.h,v 1.1.2.2 2002/10/02 14:38:38 armin Exp $ */
macro_line|#ifndef __DIVA_USER_MODE_IDI_CORE_H__
DECL|macro|__DIVA_USER_MODE_IDI_CORE_H__
mdefine_line|#define __DIVA_USER_MODE_IDI_CORE_H__
multiline_comment|/*&n;  interface between UM IDI core and OS dependent part&n;  */
r_int
id|diva_user_mode_idi_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|diva_user_mode_idi_finit
(paren
r_void
)paren
suffix:semicolon
r_int
id|diva_um_idi_nr_of_adapters
(paren
r_void
)paren
suffix:semicolon
r_void
op_star
id|divas_um_idi_create_entity
(paren
id|dword
id|adapter_nr
comma
r_void
op_star
id|file
)paren
suffix:semicolon
r_int
id|divas_um_idi_delete_entity
(paren
r_int
id|adapter_nr
comma
r_void
op_star
id|entity
)paren
suffix:semicolon
DECL|typedef|divas_um_idi_copy_to_user_fn_t
r_typedef
r_int
(paren
op_star
id|divas_um_idi_copy_to_user_fn_t
)paren
(paren
r_void
op_star
id|os_handle
comma
r_void
op_star
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|length
)paren
suffix:semicolon
DECL|typedef|divas_um_idi_copy_from_user_fn_t
r_typedef
r_int
(paren
op_star
id|divas_um_idi_copy_from_user_fn_t
)paren
(paren
r_void
op_star
id|os_handle
comma
r_void
op_star
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|length
)paren
suffix:semicolon
r_int
id|diva_um_idi_read
(paren
r_void
op_star
id|entity
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
id|divas_um_idi_copy_to_user_fn_t
id|cp_fn
)paren
suffix:semicolon
r_int
id|diva_um_idi_write
(paren
r_void
op_star
id|entity
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
id|divas_um_idi_copy_from_user_fn_t
id|cp_fn
)paren
suffix:semicolon
r_int
id|diva_user_mode_idi_ind_ready
(paren
r_void
op_star
id|entity
comma
r_void
op_star
id|os_handle
)paren
suffix:semicolon
r_void
op_star
id|diva_um_id_get_os_context
(paren
r_void
op_star
id|entity
)paren
suffix:semicolon
r_int
id|diva_os_get_context_size
(paren
r_void
)paren
suffix:semicolon
r_int
id|divas_um_idi_entity_assigned
(paren
r_void
op_star
id|entity
)paren
suffix:semicolon
r_int
id|divas_um_idi_entity_start_remove
(paren
r_void
op_star
id|entity
)paren
suffix:semicolon
r_void
id|diva_um_idi_start_wdog
(paren
r_void
op_star
id|entity
)paren
suffix:semicolon
r_void
id|diva_um_idi_stop_wdog
(paren
r_void
op_star
id|entity
)paren
suffix:semicolon
macro_line|#endif
eof
