multiline_comment|/*&n; * Used to synchronize global power management operations.&n; */
r_extern
r_struct
id|semaphore
id|dpm_sem
suffix:semicolon
multiline_comment|/* &n; * The PM lists.&n; */
r_extern
r_struct
id|list_head
id|dpm_active
suffix:semicolon
r_extern
r_struct
id|list_head
id|dpm_suspended
suffix:semicolon
r_extern
r_struct
id|list_head
id|dpm_off
suffix:semicolon
r_extern
r_struct
id|list_head
id|dpm_off_irq
suffix:semicolon
DECL|function|to_pm_info
r_static
r_inline
r_struct
id|dev_pm_info
op_star
id|to_pm_info
c_func
(paren
r_struct
id|list_head
op_star
id|entry
)paren
(brace
r_return
id|container_of
c_func
(paren
id|entry
comma
r_struct
id|dev_pm_info
comma
id|entry
)paren
suffix:semicolon
)brace
DECL|function|to_device
r_static
r_inline
r_struct
id|device
op_star
id|to_device
c_func
(paren
r_struct
id|list_head
op_star
id|entry
)paren
(brace
r_return
id|container_of
c_func
(paren
id|to_pm_info
c_func
(paren
id|entry
)paren
comma
r_struct
id|device
comma
id|power
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * resume.c &n; */
r_extern
r_int
id|dpm_resume
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dpm_power_up
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dpm_power_up_irq
c_func
(paren
r_void
)paren
suffix:semicolon
eof
