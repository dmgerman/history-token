macro_line|#ifndef _WRAPPER_H_
DECL|macro|_WRAPPER_H_
mdefine_line|#define _WRAPPER_H_
DECL|macro|mem_map_reserve
mdefine_line|#define mem_map_reserve(p)&t;set_bit(PG_reserved, &amp;((p)-&gt;flags))
DECL|macro|mem_map_unreserve
mdefine_line|#define mem_map_unreserve(p)&t;clear_bit(PG_reserved, &amp;((p)-&gt;flags))
macro_line|#endif /* _WRAPPER_H_ */
eof
