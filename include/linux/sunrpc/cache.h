multiline_comment|/*&n; * include/linux/sunrpc/cache.h&n; *&n; * Generic code for various authentication-related caches&n; * used by sunrpc clients and servers.&n; *&n; * Copyright (C) 2002 Neil Brown &lt;neilb@cse.unsw.edu.au&gt;&n; *&n; * Released under terms in GPL version 2.  See COPYING.&n; *&n; */
macro_line|#ifndef _LINUX_SUNRPC_CACHE_H_
DECL|macro|_LINUX_SUNRPC_CACHE_H_
mdefine_line|#define _LINUX_SUNRPC_CACHE_H_
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
multiline_comment|/*&n; * Each cache requires:&n; *  - A &squot;struct cache_detail&squot; which contains information specific to the cache&n; *    for common code to use.&n; *  - An item structure that must contain a &quot;struct cache_head&quot;&n; *  - A lookup function defined using DefineCacheLookup&n; *  - A &squot;put&squot; function that can release a cache item. It will only&n; *    be called after cache_put has succeed, so there are guarantee&n; *    to be no references.&n; *  - A function to calculate a hash of an item&squot;s key.&n; *&n; * as well as assorted code fragments (e.g. compare keys) and numbers&n; * (e.g. hash size, goal_age, etc).&n; *&n; * Each cache must be registered so that it can be cleaned regularly.&n; * When the cache is unregistered, it is flushed completely.&n; *&n; * Entries have a ref count and a &squot;hashed&squot; flag which counts the existance&n; * in the hash table.&n; * We only expire entries when refcount is zero.&n; * Existance in the cache is not measured in refcount but rather in&n; * CACHE_HASHED flag.&n; */
multiline_comment|/* Every cache item has a common header that is used&n; * for expiring and refreshing entries.&n; * &n; */
DECL|struct|cache_head
r_struct
id|cache_head
(brace
DECL|member|next
r_struct
id|cache_head
op_star
id|next
suffix:semicolon
DECL|member|expiry_time
id|time_t
id|expiry_time
suffix:semicolon
multiline_comment|/* After time time, don&squot;t use the data */
DECL|member|last_refresh
id|time_t
id|last_refresh
suffix:semicolon
multiline_comment|/* If CACHE_PENDING, this is when upcall &n;&t;&t;&t;&t;&t; * was sent, else this is when update was received&n;&t;&t;&t;&t;&t; */
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CACHE_VALID
mdefine_line|#define&t;CACHE_VALID&t;0&t;/* Entry contains valid data */
DECL|macro|CACHE_NEGATIVE
mdefine_line|#define&t;CACHE_NEGATIVE&t;1&t;/* Negative entry - there is no match for the key */
DECL|macro|CACHE_PENDING
mdefine_line|#define&t;CACHE_PENDING&t;2&t;/* An upcall has been sent but no reply received yet*/
DECL|macro|CACHE_HASHED
mdefine_line|#define&t;CACHE_HASHED&t;3&t;/* Entry is in a hash table */
DECL|macro|CACHE_NEW_EXPIRY
mdefine_line|#define&t;CACHE_NEW_EXPIRY 120&t;/* keep new things pending confirmation for 120 seconds */
DECL|struct|cache_detail
r_struct
id|cache_detail
(brace
DECL|member|hash_size
r_int
id|hash_size
suffix:semicolon
DECL|member|hash_table
r_struct
id|cache_head
op_star
op_star
id|hash_table
suffix:semicolon
DECL|member|hash_lock
id|rwlock_t
id|hash_lock
suffix:semicolon
DECL|member|inuse
id|atomic_t
id|inuse
suffix:semicolon
multiline_comment|/* active user-space update or lookup */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|cache_put
r_void
(paren
op_star
id|cache_put
)paren
(paren
r_struct
id|cache_head
op_star
comma
r_struct
id|cache_detail
op_star
)paren
suffix:semicolon
DECL|member|cache_request
r_void
(paren
op_star
id|cache_request
)paren
(paren
r_struct
id|cache_detail
op_star
id|cd
comma
r_struct
id|cache_head
op_star
id|h
comma
r_char
op_star
op_star
id|bpp
comma
r_int
op_star
id|blen
)paren
suffix:semicolon
DECL|member|cache_parse
r_int
(paren
op_star
id|cache_parse
)paren
(paren
r_struct
id|cache_detail
op_star
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|cache_show
r_int
(paren
op_star
id|cache_show
)paren
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_struct
id|cache_detail
op_star
id|cd
comma
r_struct
id|cache_head
op_star
id|h
)paren
suffix:semicolon
multiline_comment|/* fields below this comment are for internal use&n;&t; * and should not be touched by cache owners&n;&t; */
DECL|member|flush_time
id|time_t
id|flush_time
suffix:semicolon
multiline_comment|/* flush all cache items with last_refresh&n;&t;&t;&t;&t;&t;&t;&t; * earlier than this */
DECL|member|others
r_struct
id|list_head
id|others
suffix:semicolon
DECL|member|nextcheck
id|time_t
id|nextcheck
suffix:semicolon
DECL|member|entries
r_int
id|entries
suffix:semicolon
multiline_comment|/* fields for communication over channel */
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|proc_ent
r_struct
id|proc_dir_entry
op_star
id|proc_ent
suffix:semicolon
DECL|member|flush_ent
DECL|member|channel_ent
DECL|member|content_ent
r_struct
id|proc_dir_entry
op_star
id|flush_ent
comma
op_star
id|channel_ent
comma
op_star
id|content_ent
suffix:semicolon
DECL|member|readers
id|atomic_t
id|readers
suffix:semicolon
multiline_comment|/* how many time is /chennel open */
DECL|member|last_close
id|time_t
id|last_close
suffix:semicolon
multiline_comment|/* it no readers, when did last close */
)brace
suffix:semicolon
multiline_comment|/* this must be embedded in any request structure that&n; * identifies an object that will want a callback on&n; * a cache fill&n; */
DECL|struct|cache_req
r_struct
id|cache_req
(brace
DECL|member|defer
r_struct
id|cache_deferred_req
op_star
(paren
op_star
id|defer
)paren
(paren
r_struct
id|cache_req
op_star
id|req
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* this must be embedded in a deferred_request that is being&n; * delayed awaiting cache-fill&n; */
DECL|struct|cache_deferred_req
r_struct
id|cache_deferred_req
(brace
DECL|member|hash
r_struct
id|list_head
id|hash
suffix:semicolon
multiline_comment|/* on hash chain */
DECL|member|recent
r_struct
id|list_head
id|recent
suffix:semicolon
multiline_comment|/* on fifo */
DECL|member|item
r_struct
id|cache_head
op_star
id|item
suffix:semicolon
multiline_comment|/* cache item we wait on */
DECL|member|recv_time
id|time_t
id|recv_time
suffix:semicolon
DECL|member|owner
r_void
op_star
id|owner
suffix:semicolon
multiline_comment|/* we might need to discard all defered requests&n;&t;&t;&t;&t;&t; * owned by someone */
DECL|member|revisit
r_void
(paren
op_star
id|revisit
)paren
(paren
r_struct
id|cache_deferred_req
op_star
id|req
comma
r_int
id|too_many
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * just like a template in C++, this macro does cache lookup&n; * for us.&n; * The function is passed some sort of HANDLE from which a cache_detail&n; * structure can be determined (via SETUP, DETAIL), a template&n; * cache entry (type RTN*), and a &quot;set&quot; flag.  Using the HASHFN and the &n; * TEST, the function will try to find a matching cache entry in the cache.&n; * If &quot;set&quot; == 0 :&n; *    If an entry is found, it is returned&n; *    If no entry is found, a new non-VALID entry is created.&n; * If &quot;set&quot; == 1 and INPLACE == 0 :&n; *    If no entry is found a new one is inserted with data from &quot;template&quot;&n; *    If a non-CACHE_VALID entry is found, it is updated from template using UPDATE&n; *    If a CACHE_VALID entry is found, a new entry is swapped in with data&n; *       from &quot;template&quot;&n; * If set == 1, and INPLACE == 1 :&n; *    As above, except that if a CACHE_VALID entry is found, we UPDATE in place&n; *       instead of swapping in a new entry.&n; *&n; * If the passed handle has the CACHE_NEGATIVE flag set, then UPDATE is not&n; * run but insteead CACHE_NEGATIVE is set in any new item.&n;&n; *  In any case, the new entry is returned with a reference count.&n; *&n; *    &n; * RTN is a struct type for a cache entry&n; * MEMBER is the member of the cache which is cache_head, which must be first&n; * FNAME is the name for the function&t;&n; * ARGS are arguments to function and must contain RTN *item, int set.  May&n; *   also contain something to be usedby SETUP or DETAIL to find cache_detail.&n; * SETUP  locates the cache detail and makes it available as...&n; * DETAIL identifies the cache detail, possibly set up by SETUP&n; * HASHFN returns a hash value of the cache entry &quot;item&quot;&n; * TEST  tests if &quot;tmp&quot; matches &quot;item&quot;&n; * INIT copies key information from &quot;item&quot; to &quot;new&quot;&n; * UPDATE copies content information from &quot;item&quot; to &quot;tmp&quot;&n; * INPLACE is true if updates can happen inplace rather than allocating a new structure&n; */
DECL|macro|DefineCacheLookup
mdefine_line|#define DefineCacheLookup(RTN,MEMBER,FNAME,ARGS,SETUP,DETAIL,HASHFN,TEST,INIT,UPDATE,INPLACE)&t;&bslash;&n;RTN *FNAME ARGS&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;RTN *tmp, *new=NULL;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct cache_head **hp, **head;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SETUP;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;head = &amp;(DETAIL)-&gt;hash_table[HASHFN];&t;&t;&t;&t;&t;&t;&bslash;&n; retry:&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (set||new) write_lock(&amp;(DETAIL)-&gt;hash_lock);&t;&t;&t;&t;&t;&bslash;&n;&t;else read_lock(&amp;(DETAIL)-&gt;hash_lock);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for(hp=head; *hp != NULL; hp = &amp;tmp-&gt;MEMBER.next) {&t;&t;&t;&t;&bslash;&n;&t;&t;tmp = container_of(*hp, RTN, MEMBER);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (TEST) { /* found a match */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (set &amp;&amp; !INPLACE &amp;&amp; test_bit(CACHE_VALID, &amp;tmp-&gt;MEMBER.flags) &amp;&amp; !new) &bslash;&n;&t;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (new)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;{INIT;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;cache_get(&amp;tmp-&gt;MEMBER);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (set) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;if (!INPLACE &amp;&amp; test_bit(CACHE_VALID, &amp;tmp-&gt;MEMBER.flags))&bslash;&n;&t;&t;&t;&t;{ /* need to swap in new */&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;RTN *t2;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;new-&gt;MEMBER.next = tmp-&gt;MEMBER.next;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;*hp = &amp;new-&gt;MEMBER;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;tmp-&gt;MEMBER.next = NULL;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;set_bit(CACHE_HASHED, &amp;new-&gt;MEMBER.flags);&t;&bslash;&n;&t;&t;&t;&t;&t;clear_bit(CACHE_HASHED, &amp;tmp-&gt;MEMBER.flags);&t;&bslash;&n;&t;&t;&t;&t;&t;t2 = tmp; tmp = new; new = t2;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;if (test_bit(CACHE_NEGATIVE,  &amp;item-&gt;MEMBER.flags))&t;&bslash;&n;&t;&t;&t;&t;&t; set_bit(CACHE_NEGATIVE, &amp;tmp-&gt;MEMBER.flags);&t;&bslash;&n;&t;&t;&t;&t;else {UPDATE;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (set||new) write_unlock(&amp;(DETAIL)-&gt;hash_lock);&t;&t;&bslash;&n;&t;&t;&t;else read_unlock(&amp;(DETAIL)-&gt;hash_lock);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (set)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;cache_fresh(DETAIL, &amp;tmp-&gt;MEMBER, item-&gt;MEMBER.expiry_time); &bslash;&n;&t;&t;&t;if (set &amp;&amp; !INPLACE &amp;&amp; new) cache_fresh(DETAIL, &amp;new-&gt;MEMBER, 0);&t;&bslash;&n;&t;&t;&t;if (new) (DETAIL)-&gt;cache_put(&amp;new-&gt;MEMBER, DETAIL);&t;&t;&bslash;&n;&t;&t;&t;return tmp;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Didn&squot;t find anything */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (new) {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;INIT;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;new-&gt;MEMBER.next = *head;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*head = &amp;new-&gt;MEMBER;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(DETAIL)-&gt;entries ++;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_bit(CACHE_HASHED, &amp;new-&gt;MEMBER.flags);&t;&t;&t;&t;&bslash;&n;&t;&t;if (set) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;tmp = new;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (test_bit(CACHE_NEGATIVE, &amp;item-&gt;MEMBER.flags))&t;&t;&bslash;&n;&t;&t;&t;&t;set_bit(CACHE_NEGATIVE, &amp;tmp-&gt;MEMBER.flags);&t;&t;&bslash;&n;&t;&t;&t;else {UPDATE;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (set||new) write_unlock(&amp;(DETAIL)-&gt;hash_lock);&t;&t;&t;&t;&bslash;&n;&t;else read_unlock(&amp;(DETAIL)-&gt;hash_lock);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (new &amp;&amp; set)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cache_fresh(DETAIL, &amp;new-&gt;MEMBER, item-&gt;MEMBER.expiry_time);&t;&t;&bslash;&n;&t;if (new)&t;&t;&t;&t;       &t;&t;&t;&t;&t;&bslash;&n;&t;&t;return new;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;new = kmalloc(sizeof(*new), GFP_KERNEL);&t;&t;&t;&t;&t;&bslash;&n;&t;if (new) {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cache_init(&amp;new-&gt;MEMBER);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cache_get(&amp;new-&gt;MEMBER);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;goto retry;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return NULL;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|DefineSimpleCacheLookup
mdefine_line|#define DefineSimpleCacheLookup(STRUCT,INPLACE)&t;&bslash;&n;&t;DefineCacheLookup(struct STRUCT, h, STRUCT##_lookup, (struct STRUCT *item, int set), /*no setup */,&t;&bslash;&n;&t;&t;&t;  &amp; STRUCT##_cache, STRUCT##_hash(item), STRUCT##_match(item, tmp),&bslash;&n;&t;&t;&t;  STRUCT##_init(new, item), STRUCT##_update(tmp, item),INPLACE)
DECL|macro|cache_for_each
mdefine_line|#define cache_for_each(pos, detail, index, member) &t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (({read_lock(&amp;(detail)-&gt;hash_lock); index = (detail)-&gt;hash_size;}) ;&t;&t;&bslash;&n;&t;     ({if (index==0)read_unlock(&amp;(detail)-&gt;hash_lock); index--;});&t;&t;&t;&bslash;&n;&t;&t;)&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;for (pos = container_of((detail)-&gt;hash_table[index], typeof(*pos), member);&t;&bslash;&n;&t;&t;     &amp;pos-&gt;member;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     pos = container_of(pos-&gt;member.next, typeof(*pos), member))
r_extern
r_void
id|cache_defer_req
c_func
(paren
r_struct
id|cache_req
op_star
id|req
comma
r_struct
id|cache_head
op_star
id|item
)paren
suffix:semicolon
r_extern
r_void
id|cache_revisit_request
c_func
(paren
r_struct
id|cache_head
op_star
id|item
)paren
suffix:semicolon
r_extern
r_void
id|cache_clean_deferred
c_func
(paren
r_void
op_star
id|owner
)paren
suffix:semicolon
DECL|function|cache_get
r_static
r_inline
r_struct
id|cache_head
op_star
id|cache_get
c_func
(paren
r_struct
id|cache_head
op_star
id|h
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|h-&gt;refcnt
)paren
suffix:semicolon
r_return
id|h
suffix:semicolon
)brace
DECL|function|cache_put
r_static
r_inline
r_int
id|cache_put
c_func
(paren
r_struct
id|cache_head
op_star
id|h
comma
r_struct
id|cache_detail
op_star
id|cd
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|h-&gt;refcnt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|h-&gt;refcnt
)paren
op_logical_and
id|h-&gt;expiry_time
OL
id|cd-&gt;nextcheck
)paren
id|cd-&gt;nextcheck
op_assign
id|h-&gt;expiry_time
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|CACHE_HASHED
comma
op_amp
id|h-&gt;flags
)paren
op_logical_and
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|h-&gt;refcnt
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_void
id|cache_init
c_func
(paren
r_struct
id|cache_head
op_star
id|h
)paren
suffix:semicolon
r_extern
r_void
id|cache_fresh
c_func
(paren
r_struct
id|cache_detail
op_star
id|detail
comma
r_struct
id|cache_head
op_star
id|head
comma
id|time_t
id|expiry
)paren
suffix:semicolon
r_extern
r_int
id|cache_check
c_func
(paren
r_struct
id|cache_detail
op_star
id|detail
comma
r_struct
id|cache_head
op_star
id|h
comma
r_struct
id|cache_req
op_star
id|rqstp
)paren
suffix:semicolon
r_extern
r_int
id|cache_clean
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cache_flush
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cache_purge
c_func
(paren
r_struct
id|cache_detail
op_star
id|detail
)paren
suffix:semicolon
DECL|macro|NEVER
mdefine_line|#define NEVER (0x7FFFFFFF)
r_extern
r_void
id|cache_register
c_func
(paren
r_struct
id|cache_detail
op_star
id|cd
)paren
suffix:semicolon
r_extern
r_int
id|cache_unregister
c_func
(paren
r_struct
id|cache_detail
op_star
id|cd
)paren
suffix:semicolon
r_extern
r_struct
id|cache_detail
op_star
id|cache_find
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|cache_drop
c_func
(paren
r_struct
id|cache_detail
op_star
id|detail
)paren
suffix:semicolon
r_extern
r_void
id|qword_add
c_func
(paren
r_char
op_star
op_star
id|bpp
comma
r_int
op_star
id|lp
comma
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_void
id|qword_addhex
c_func
(paren
r_char
op_star
op_star
id|bpp
comma
r_int
op_star
id|lp
comma
r_char
op_star
id|buf
comma
r_int
id|blen
)paren
suffix:semicolon
r_extern
r_int
id|qword_get
c_func
(paren
r_char
op_star
op_star
id|bpp
comma
r_char
op_star
id|dest
comma
r_int
id|bufsize
)paren
suffix:semicolon
DECL|function|get_int
r_static
r_inline
r_int
id|get_int
c_func
(paren
r_char
op_star
op_star
id|bpp
comma
r_int
op_star
id|anint
)paren
(brace
r_char
id|buf
(braket
l_int|50
)braket
suffix:semicolon
r_char
op_star
id|ep
suffix:semicolon
r_int
id|rv
suffix:semicolon
r_int
id|len
op_assign
id|qword_get
c_func
(paren
id|bpp
comma
id|buf
comma
l_int|50
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|rv
op_assign
id|simple_strtol
c_func
(paren
id|buf
comma
op_amp
id|ep
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ep
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|anint
op_assign
id|rv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_expiry
r_static
r_inline
id|time_t
id|get_expiry
c_func
(paren
r_char
op_star
op_star
id|bpp
)paren
(brace
r_int
id|rv
suffix:semicolon
r_if
c_cond
(paren
id|get_int
c_func
(paren
id|bpp
comma
op_amp
id|rv
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rv
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
macro_line|#endif /*  _LINUX_SUNRPC_CACHE_H_ */
eof
