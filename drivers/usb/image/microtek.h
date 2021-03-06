multiline_comment|/*&n; * Driver for Microtek Scanmaker X6 USB scanner and possibly others.&n; * &n; * (C) Copyright 2000 John Fremlin &lt;vii@penguinpowered.com&gt;&n; * (C) Copyright 2000 Oliver Neukum &lt;Oliver.Neukum@lrz.uni-muenchen.de&gt;&n; *&n; * See microtek.c for history&n; *&n; */
DECL|typedef|mts_scsi_cmnd_callback
r_typedef
r_void
(paren
op_star
id|mts_scsi_cmnd_callback
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
DECL|struct|mts_transfer_context
r_struct
id|mts_transfer_context
(brace
DECL|member|instance
r_struct
id|mts_desc
op_star
id|instance
suffix:semicolon
DECL|member|final_callback
id|mts_scsi_cmnd_callback
id|final_callback
suffix:semicolon
DECL|member|srb
id|Scsi_Cmnd
op_star
id|srb
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|data_length
r_int
id|data_length
suffix:semicolon
DECL|member|data_pipe
r_int
id|data_pipe
suffix:semicolon
DECL|member|fragment
r_int
id|fragment
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
multiline_comment|/* status returned from ep_response after command completion */
)brace
suffix:semicolon
DECL|struct|mts_desc
r_struct
id|mts_desc
(brace
DECL|member|next
r_struct
id|mts_desc
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|mts_desc
op_star
id|prev
suffix:semicolon
DECL|member|usb_dev
r_struct
id|usb_device
op_star
id|usb_dev
suffix:semicolon
DECL|member|usb_intf
r_struct
id|usb_interface
op_star
id|usb_intf
suffix:semicolon
multiline_comment|/* Endpoint addresses */
DECL|member|ep_out
id|u8
id|ep_out
suffix:semicolon
DECL|member|ep_response
id|u8
id|ep_response
suffix:semicolon
DECL|member|ep_image
id|u8
id|ep_image
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
DECL|member|context
r_struct
id|mts_transfer_context
id|context
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MTS_EP_OUT
mdefine_line|#define MTS_EP_OUT&t;0x1
DECL|macro|MTS_EP_RESPONSE
mdefine_line|#define MTS_EP_RESPONSE&t;0x2
DECL|macro|MTS_EP_IMAGE
mdefine_line|#define MTS_EP_IMAGE&t;0x3
DECL|macro|MTS_EP_TOTAL
mdefine_line|#define MTS_EP_TOTAL&t;0x3
DECL|macro|MTS_SCSI_ERR_MASK
mdefine_line|#define MTS_SCSI_ERR_MASK ~0x3fu
eof
