multiline_comment|/*&n; *  linux/net/netsyms.c&n; *&n; *  Symbol table for the linux networking subsystem. Moved here to&n; *  make life simpler in ksyms.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#ifdef CONFIG_INET
macro_line|#if defined(CONFIG_INET_AH) || defined(CONFIG_INET_AH_MODULE) || defined(CONFIG_INET6_AH) || defined(CONFIG_INET6_AH_MODULE)
macro_line|#include &lt;net/ah.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_INET_ESP) || defined(CONFIG_INET_ESP_MODULE) || defined(CONFIG_INET6_ESP) || defined(CONFIG_INET6_ESP_MODULE)
macro_line|#include &lt;net/esp.h&gt;
macro_line|#endif
macro_line|#endif
multiline_comment|/* Needed by unix.o */
DECL|variable|files_stat
id|EXPORT_SYMBOL
c_func
(paren
id|files_stat
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_INET
macro_line|#if defined(CONFIG_INET_ESP) || defined(CONFIG_INET_ESP_MODULE) || defined(CONFIG_INET6_ESP) || defined(CONFIG_INET6_ESP_MODULE)
DECL|variable|skb_cow_data
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|skb_cow_data
)paren
suffix:semicolon
DECL|variable|pskb_put
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|pskb_put
)paren
suffix:semicolon
DECL|variable|skb_to_sgvec
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|skb_to_sgvec
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif  /* CONFIG_INET */
multiline_comment|/* support for loadable net drivers */
macro_line|#ifdef CONFIG_NET
DECL|variable|loopback_dev
id|EXPORT_SYMBOL
c_func
(paren
id|loopback_dev
)paren
suffix:semicolon
DECL|variable|dev_base
id|EXPORT_SYMBOL
c_func
(paren
id|dev_base
)paren
suffix:semicolon
DECL|variable|dev_base_lock
id|EXPORT_SYMBOL
c_func
(paren
id|dev_base_lock
)paren
suffix:semicolon
DECL|variable|__kill_fasync
id|EXPORT_SYMBOL
c_func
(paren
id|__kill_fasync
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_NET */
eof
