multiline_comment|/* Functions local to drivers/usb/core/ */
r_extern
r_void
id|usb_create_driverfs_dev_files
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usb_create_driverfs_intf_files
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
eof
