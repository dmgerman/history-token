multiline_comment|/* Functions local to drivers/usb/core/ */
r_extern
r_void
id|usb_create_sysfs_dev_files
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usb_remove_sysfs_dev_files
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usb_create_sysfs_intf_files
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
suffix:semicolon
r_extern
r_void
id|usb_remove_sysfs_intf_files
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
suffix:semicolon
r_extern
r_int
id|usb_probe_interface
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|usb_unbind_interface
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usb_disable_endpoint
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|epaddr
)paren
suffix:semicolon
r_extern
r_void
id|usb_disable_interface
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_struct
id|usb_interface
op_star
id|intf
)paren
suffix:semicolon
r_extern
r_void
id|usb_release_interface_cache
c_func
(paren
r_struct
id|kref
op_star
id|ref
)paren
suffix:semicolon
r_extern
r_void
id|usb_disable_device
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|skip_ep0
)paren
suffix:semicolon
r_extern
r_void
id|usb_enable_endpoint
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_struct
id|usb_endpoint_descriptor
op_star
id|epd
)paren
suffix:semicolon
r_extern
r_void
id|usb_enable_interface
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_struct
id|usb_interface
op_star
id|intf
)paren
suffix:semicolon
r_extern
r_int
id|usb_get_device_descriptor
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|usb_set_configuration
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|configuration
)paren
suffix:semicolon
r_extern
r_void
id|usb_lock_all_devices
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|usb_unlock_all_devices
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* for labeling diagnostics */
r_extern
r_const
r_char
op_star
id|usbcore_name
suffix:semicolon
multiline_comment|/* usbfs stuff */
r_extern
r_struct
id|usb_driver
id|usbfs_driver
suffix:semicolon
r_extern
r_struct
id|file_operations
id|usbfs_devices_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|usbfs_device_file_operations
suffix:semicolon
r_extern
r_void
id|usbfs_conn_disc_event
c_func
(paren
r_void
)paren
suffix:semicolon
eof
