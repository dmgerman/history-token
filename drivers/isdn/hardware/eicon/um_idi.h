multiline_comment|/* $Id: um_idi.h,v 1.6 2004/03/21 17:26:01 armin Exp $ */
macro_line|#ifndef __DIVA_USER_MODE_IDI_CORE_H__
DECL|macro|__DIVA_USER_MODE_IDI_CORE_H__
mdefine_line|#define __DIVA_USER_MODE_IDI_CORE_H__
multiline_comment|/*&n;  interface between UM IDI core and OS dependent part&n;  */
r_int
id|diva_user_mode_idi_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|diva_user_mode_idi_finit
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
op_star
id|divas_um_idi_create_entity
c_func
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
c_func
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
c_func
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
c_func
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
c_func
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
c_func
(paren
r_void
op_star
id|entity
)paren
suffix:semicolon
r_int
id|diva_os_get_context_size
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|divas_um_idi_entity_assigned
c_func
(paren
r_void
op_star
id|entity
)paren
suffix:semicolon
r_int
id|divas_um_idi_entity_start_remove
c_func
(paren
r_void
op_star
id|entity
)paren
suffix:semicolon
r_void
id|diva_um_idi_start_wdog
c_func
(paren
r_void
op_star
id|entity
)paren
suffix:semicolon
r_void
id|diva_um_idi_stop_wdog
c_func
(paren
r_void
op_star
id|entity
)paren
suffix:semicolon
macro_line|#endif
eof
