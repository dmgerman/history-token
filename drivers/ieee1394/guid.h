macro_line|#ifndef _IEEE1394_GUID_H
DECL|macro|_IEEE1394_GUID_H
mdefine_line|#define _IEEE1394_GUID_H
multiline_comment|/*&n; * General information: Finding out which GUID belongs to which node is done by&n; * sending packets and therefore waiting for the answers.  Wherever it is&n; * mentioned that a node is inaccessible this could just as well mean that we&n; * just don&squot;t know yet (usually, bus reset handlers can&squot;t rely on GUIDs being&n; * associated with current nodes).&n; */
r_struct
id|guid_entry
suffix:semicolon
DECL|typedef|hpsb_guid_t
r_typedef
r_struct
id|guid_entry
op_star
id|hpsb_guid_t
suffix:semicolon
multiline_comment|/*&n; * Returns a guid handle (which has its reference count incremented) or NULL if&n; * there is the GUID in question is not known of.  Getting a valid handle does&n; * not mean that the node with this GUID is currently accessible (might not be&n; * plugged in or powered down).&n; */
id|hpsb_guid_t
id|hpsb_guid_get_handle
c_func
(paren
id|u64
id|guid
)paren
suffix:semicolon
multiline_comment|/*&n; * If the handle refers to a local host, this function will return the pointer&n; * to the hpsb_host structure.  It will return NULL otherwise.  Once you have&n; * established it is a local host, you can use that knowledge from then on (the&n; * GUID won&squot;t wander to an external node).&n; *&n; * Note that the local GUID currently isn&squot;t collected, so this will always&n; * return NULL.&n; */
r_struct
id|hpsb_host
op_star
id|hpsb_guid_localhost
c_func
(paren
id|hpsb_guid_t
id|handle
)paren
suffix:semicolon
multiline_comment|/*&n; * This will fill in the given, pre-initialised hpsb_packet with the current&n; * information from the GUID handle (host, node ID, generation number).  It will&n; * return false if the node owning the GUID is not accessible (and not modify the &n; * hpsb_packet) and return true otherwise.&n; *&n; * Note that packet sending may still fail in hpsb_send_packet if a bus reset&n; * happens while you are trying to set up the packet (due to obsolete generation&n; * number).  It will at least reliably fail so that you don&squot;t accidentally and&n; * unknowingly send your packet to the wrong node.&n; */
r_int
id|hpsb_guid_fill_packet
c_func
(paren
id|hpsb_guid_t
id|handle
comma
r_struct
id|hpsb_packet
op_star
id|pkt
)paren
suffix:semicolon
r_void
id|init_ieee1394_guid
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _IEEE1394_GUID_H */
eof
