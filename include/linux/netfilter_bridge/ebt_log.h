macro_line|#ifndef __LINUX_BRIDGE_EBT_LOG_H
DECL|macro|__LINUX_BRIDGE_EBT_LOG_H
mdefine_line|#define __LINUX_BRIDGE_EBT_LOG_H
DECL|macro|EBT_LOG_IP
mdefine_line|#define EBT_LOG_IP 0x01 /* if the frame is made by ip, log the ip information */
DECL|macro|EBT_LOG_ARP
mdefine_line|#define EBT_LOG_ARP 0x02
DECL|macro|EBT_LOG_MASK
mdefine_line|#define EBT_LOG_MASK (EBT_LOG_IP | EBT_LOG_ARP)
DECL|macro|EBT_LOG_PREFIX_SIZE
mdefine_line|#define EBT_LOG_PREFIX_SIZE 30
DECL|macro|EBT_LOG_WATCHER
mdefine_line|#define EBT_LOG_WATCHER &quot;log&quot;
DECL|struct|ebt_log_info
r_struct
id|ebt_log_info
(brace
DECL|member|loglevel
r_uint8
id|loglevel
suffix:semicolon
DECL|member|prefix
r_uint8
id|prefix
(braket
id|EBT_LOG_PREFIX_SIZE
)braket
suffix:semicolon
DECL|member|bitmask
r_uint32
id|bitmask
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
