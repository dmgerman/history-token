r_enum
(brace
DECL|enumerator|DEVICE_PM_ON
id|DEVICE_PM_ON
comma
DECL|enumerator|DEVICE_PM1
id|DEVICE_PM1
comma
DECL|enumerator|DEVICE_PM2
id|DEVICE_PM2
comma
DECL|enumerator|DEVICE_PM3
id|DEVICE_PM3
comma
DECL|enumerator|DEVICE_PM_OFF
id|DEVICE_PM_OFF
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * shutdown.c&n; */
r_extern
r_int
id|device_detach_shutdown
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|device_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
multiline_comment|/*&n; * main.c&n; */
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
r_extern
r_int
id|device_pm_add
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|device_pm_remove
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * sysfs.c&n; */
r_extern
r_int
id|dpm_sysfs_add
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|dpm_sysfs_remove
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
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
r_int
id|resume_device
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * suspend.c&n; */
r_extern
r_int
id|suspend_device
c_func
(paren
r_struct
id|device
op_star
comma
id|u32
)paren
suffix:semicolon
multiline_comment|/*&n; * runtime.c&n; */
r_extern
r_int
id|dpm_runtime_suspend
c_func
(paren
r_struct
id|device
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_void
id|dpm_runtime_resume
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
macro_line|#else /* CONFIG_PM */
DECL|function|device_pm_add
r_static
r_inline
r_int
id|device_pm_add
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|device_pm_remove
r_static
r_inline
r_void
id|device_pm_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
)brace
DECL|function|dpm_runtime_suspend
r_static
r_inline
r_int
id|dpm_runtime_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dpm_runtime_resume
r_static
r_inline
r_void
id|dpm_runtime_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
)brace
macro_line|#endif
eof
