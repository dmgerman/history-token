multiline_comment|/*&n; * Copyright (c) 1991, 1993&n; *&t;The Regents of the University of California.  All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; *&t;@(#)queue.h&t;8.5 (Berkeley) 8/20/94&n; * $FreeBSD: src/sys/sys/queue.h,v 1.38 2000/05/26 02:06:56 jake Exp $&n; */
macro_line|#ifndef _SYS_QUEUE_H_
DECL|macro|_SYS_QUEUE_H_
mdefine_line|#define&t;_SYS_QUEUE_H_
multiline_comment|/*&n; * This file defines five types of data structures: singly-linked lists,&n; * singly-linked tail queues, lists, tail queues, and circular queues.&n; *&n; * A singly-linked list is headed by a single forward pointer. The elements&n; * are singly linked for minimum space and pointer manipulation overhead at&n; * the expense of O(n) removal for arbitrary elements. New elements can be&n; * added to the list after an existing element or at the head of the list.&n; * Elements being removed from the head of the list should use the explicit&n; * macro for this purpose for optimum efficiency. A singly-linked list may&n; * only be traversed in the forward direction.  Singly-linked lists are ideal&n; * for applications with large datasets and few or no removals or for&n; * implementing a LIFO queue.&n; *&n; * A singly-linked tail queue is headed by a pair of pointers, one to the&n; * head of the list and the other to the tail of the list. The elements are&n; * singly linked for minimum space and pointer manipulation overhead at the&n; * expense of O(n) removal for arbitrary elements. New elements can be added&n; * to the list after an existing element, at the head of the list, or at the&n; * end of the list. Elements being removed from the head of the tail queue&n; * should use the explicit macro for this purpose for optimum efficiency.&n; * A singly-linked tail queue may only be traversed in the forward direction.&n; * Singly-linked tail queues are ideal for applications with large datasets&n; * and few or no removals or for implementing a FIFO queue.&n; *&n; * A list is headed by a single forward pointer (or an array of forward&n; * pointers for a hash table header). The elements are doubly linked&n; * so that an arbitrary element can be removed without a need to&n; * traverse the list. New elements can be added to the list before&n; * or after an existing element or at the head of the list. A list&n; * may only be traversed in the forward direction.&n; *&n; * A tail queue is headed by a pair of pointers, one to the head of the&n; * list and the other to the tail of the list. The elements are doubly&n; * linked so that an arbitrary element can be removed without a need to&n; * traverse the list. New elements can be added to the list before or&n; * after an existing element, at the head of the list, or at the end of&n; * the list. A tail queue may be traversed in either direction.&n; *&n; * A circle queue is headed by a pair of pointers, one to the head of the&n; * list and the other to the tail of the list. The elements are doubly&n; * linked so that an arbitrary element can be removed without a need to&n; * traverse the list. New elements can be added to the list before or after&n; * an existing element, at the head of the list, or at the end of the list.&n; * A circle queue may be traversed in either direction, but has a more&n; * complex end of list detection.&n; *&n; * For details on the use of these macros, see the queue(3) manual page.&n; *&n; *&n; *&t;&t;&t;SLIST&t;LIST&t;STAILQ&t;TAILQ&t;CIRCLEQ&n; * _HEAD&t;&t;+&t;+&t;+&t;+&t;+&n; * _HEAD_INITIALIZER&t;+&t;+&t;+&t;+&t;+&n; * _ENTRY&t;&t;+&t;+&t;+&t;+&t;+&n; * _INIT&t;&t;+&t;+&t;+&t;+&t;+&n; * _EMPTY&t;&t;+&t;+&t;+&t;+&t;+&n; * _FIRST&t;&t;+&t;+&t;+&t;+&t;+&n; * _NEXT&t;&t;+&t;+&t;+&t;+&t;+&n; * _PREV&t;&t;-&t;-&t;-&t;+&t;+&n; * _LAST&t;&t;-&t;-&t;+&t;+&t;+&n; * _FOREACH&t;&t;+&t;+&t;+&t;+&t;+&n; * _FOREACH_REVERSE&t;-&t;-&t;-&t;+&t;+&n; * _INSERT_HEAD&t;&t;+&t;+&t;+&t;+&t;+&n; * _INSERT_BEFORE&t;-&t;+&t;-&t;+&t;+&n; * _INSERT_AFTER&t;+&t;+&t;+&t;+&t;+&n; * _INSERT_TAIL&t;&t;-&t;-&t;+&t;+&t;+&n; * _REMOVE_HEAD&t;&t;+&t;-&t;+&t;-&t;-&n; * _REMOVE&t;&t;+&t;+&t;+&t;+&t;+&n; *&n; */
multiline_comment|/*&n; * Singly-linked List declarations.&n; */
DECL|macro|SLIST_HEAD
mdefine_line|#define&t;SLIST_HEAD(name, type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct name {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *slh_first;&t;/* first element */&t;&t;&t;&bslash;&n;}
DECL|macro|SLIST_HEAD_INITIALIZER
mdefine_line|#define&t;SLIST_HEAD_INITIALIZER(head)&t;&t;&t;&t;&t;&bslash;&n;&t;{ NULL }
DECL|macro|SLIST_ENTRY
mdefine_line|#define&t;SLIST_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *sle_next;&t;/* next element */&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Singly-linked List functions.&n; */
DECL|macro|SLIST_EMPTY
mdefine_line|#define&t;SLIST_EMPTY(head)&t;((head)-&gt;slh_first == NULL)
DECL|macro|SLIST_FIRST
mdefine_line|#define&t;SLIST_FIRST(head)&t;((head)-&gt;slh_first)
DECL|macro|SLIST_FOREACH
mdefine_line|#define&t;SLIST_FOREACH(var, head, field)&t;&t;&t;&t;&t;&bslash;&n;&t;for ((var) = SLIST_FIRST((head));&t;&t;&t;&t;&bslash;&n;&t;    (var);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    (var) = SLIST_NEXT((var), field))
DECL|macro|SLIST_INIT
mdefine_line|#define&t;SLIST_INIT(head) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SLIST_FIRST((head)) = NULL;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|SLIST_INSERT_AFTER
mdefine_line|#define&t;SLIST_INSERT_AFTER(slistelm, elm, field) do {&t;&t;&t;&bslash;&n;&t;SLIST_NEXT((elm), field) = SLIST_NEXT((slistelm), field);&t;&bslash;&n;&t;SLIST_NEXT((slistelm), field) = (elm);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|SLIST_INSERT_HEAD
mdefine_line|#define&t;SLIST_INSERT_HEAD(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;SLIST_NEXT((elm), field) = SLIST_FIRST((head));&t;&t;&t;&bslash;&n;&t;SLIST_FIRST((head)) = (elm);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|SLIST_NEXT
mdefine_line|#define&t;SLIST_NEXT(elm, field)&t;((elm)-&gt;field.sle_next)
DECL|macro|SLIST_REMOVE
mdefine_line|#define&t;SLIST_REMOVE(head, elm, type, field) do {&t;&t;&t;&bslash;&n;&t;if (SLIST_FIRST((head)) == (elm)) {&t;&t;&t;&t;&bslash;&n;&t;&t;SLIST_REMOVE_HEAD((head), field);&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;struct type *curelm = SLIST_FIRST((head));&t;&t;&bslash;&n;&t;&t;while (SLIST_NEXT(curelm, field) != (elm))&t;&t;&bslash;&n;&t;&t;&t;curelm = SLIST_NEXT(curelm, field);&t;&t;&bslash;&n;&t;&t;SLIST_NEXT(curelm, field) =&t;&t;&t;&t;&bslash;&n;&t;&t;    SLIST_NEXT(SLIST_NEXT(curelm, field), field);&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|SLIST_REMOVE_HEAD
mdefine_line|#define&t;SLIST_REMOVE_HEAD(head, field) do {&t;&t;&t;&t;&bslash;&n;&t;SLIST_FIRST((head)) = SLIST_NEXT(SLIST_FIRST((head)), field);&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Singly-linked Tail queue declarations.&n; */
DECL|macro|STAILQ_HEAD
mdefine_line|#define&t;STAILQ_HEAD(name, type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct name {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *stqh_first;/* first element */&t;&t;&t;&bslash;&n;&t;struct type **stqh_last;/* addr of last next element */&t;&t;&bslash;&n;}
DECL|macro|STAILQ_HEAD_INITIALIZER
mdefine_line|#define&t;STAILQ_HEAD_INITIALIZER(head)&t;&t;&t;&t;&t;&bslash;&n;&t;{ NULL, &amp;(head).stqh_first }
DECL|macro|STAILQ_ENTRY
mdefine_line|#define&t;STAILQ_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *stqe_next;&t;/* next element */&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Singly-linked Tail queue functions.&n; */
DECL|macro|STAILQ_EMPTY
mdefine_line|#define&t;STAILQ_EMPTY(head)&t;((head)-&gt;stqh_first == NULL)
DECL|macro|STAILQ_FIRST
mdefine_line|#define&t;STAILQ_FIRST(head)&t;((head)-&gt;stqh_first)
DECL|macro|STAILQ_FOREACH
mdefine_line|#define&t;STAILQ_FOREACH(var, head, field)&t;&t;&t;&t;&bslash;&n;&t;for((var) = STAILQ_FIRST((head));&t;&t;&t;&t;&bslash;&n;&t;   (var);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   (var) = STAILQ_NEXT((var), field))
DECL|macro|STAILQ_INIT
mdefine_line|#define&t;STAILQ_INIT(head) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;STAILQ_FIRST((head)) = NULL;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;stqh_last = &amp;STAILQ_FIRST((head));&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|STAILQ_INSERT_AFTER
mdefine_line|#define&t;STAILQ_INSERT_AFTER(head, tqelm, elm, field) do {&t;&t;&bslash;&n;&t;if ((STAILQ_NEXT((elm), field) = STAILQ_NEXT((tqelm), field)) == NULL)&bslash;&n;&t;&t;(head)-&gt;stqh_last = &amp;STAILQ_NEXT((elm), field);&t;&t;&bslash;&n;&t;STAILQ_NEXT((tqelm), field) = (elm);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|STAILQ_INSERT_HEAD
mdefine_line|#define&t;STAILQ_INSERT_HEAD(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;if ((STAILQ_NEXT((elm), field) = STAILQ_FIRST((head))) == NULL)&t;&bslash;&n;&t;&t;(head)-&gt;stqh_last = &amp;STAILQ_NEXT((elm), field);&t;&t;&bslash;&n;&t;STAILQ_FIRST((head)) = (elm);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|STAILQ_INSERT_TAIL
mdefine_line|#define&t;STAILQ_INSERT_TAIL(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;STAILQ_NEXT((elm), field) = NULL;&t;&t;&t;&t;&bslash;&n;&t;STAILQ_LAST((head)) = (elm);&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;stqh_last = &amp;STAILQ_NEXT((elm), field);&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|STAILQ_LAST
mdefine_line|#define&t;STAILQ_LAST(head)&t;(*(head)-&gt;stqh_last)
DECL|macro|STAILQ_NEXT
mdefine_line|#define&t;STAILQ_NEXT(elm, field)&t;((elm)-&gt;field.stqe_next)
DECL|macro|STAILQ_REMOVE
mdefine_line|#define&t;STAILQ_REMOVE(head, elm, type, field) do {&t;&t;&t;&bslash;&n;&t;if (STAILQ_FIRST((head)) == (elm)) {&t;&t;&t;&t;&bslash;&n;&t;&t;STAILQ_REMOVE_HEAD(head, field);&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;struct type *curelm = STAILQ_FIRST((head));&t;&t;&bslash;&n;&t;&t;while (STAILQ_NEXT(curelm, field) != (elm))&t;&t;&bslash;&n;&t;&t;&t;curelm = STAILQ_NEXT(curelm, field);&t;&t;&bslash;&n;&t;&t;if ((STAILQ_NEXT(curelm, field) =&t;&t;&t;&bslash;&n;&t;&t;     STAILQ_NEXT(STAILQ_NEXT(curelm, field), field)) == NULL)&bslash;&n;&t;&t;&t;(head)-&gt;stqh_last = &amp;STAILQ_NEXT((curelm), field);&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|STAILQ_REMOVE_HEAD
mdefine_line|#define&t;STAILQ_REMOVE_HEAD(head, field) do {&t;&t;&t;&t;&bslash;&n;&t;if ((STAILQ_FIRST((head)) =&t;&t;&t;&t;&t;&bslash;&n;&t;     STAILQ_NEXT(STAILQ_FIRST((head)), field)) == NULL)&t;&t;&bslash;&n;&t;&t;(head)-&gt;stqh_last = &amp;STAILQ_FIRST((head));&t;&t;&bslash;&n;} while (0)
DECL|macro|STAILQ_REMOVE_HEAD_UNTIL
mdefine_line|#define&t;STAILQ_REMOVE_HEAD_UNTIL(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;if ((STAILQ_FIRST((head)) = STAILQ_NEXT((elm), field)) == NULL)&t;&bslash;&n;&t;&t;(head)-&gt;stqh_last = &amp;STAILQ_FIRST((head));&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * List declarations.&n; */
DECL|macro|LIST_HEAD
mdefine_line|#define&t;LIST_HEAD(name, type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct name {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *lh_first;&t;/* first element */&t;&t;&t;&bslash;&n;}
DECL|macro|LIST_HEAD_INITIALIZER
mdefine_line|#define&t;LIST_HEAD_INITIALIZER(head)&t;&t;&t;&t;&t;&bslash;&n;&t;{ NULL }
DECL|macro|LIST_ENTRY
mdefine_line|#define&t;LIST_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *le_next;&t;/* next element */&t;&t;&t;&bslash;&n;&t;struct type **le_prev;&t;/* address of previous next element */&t;&bslash;&n;}
multiline_comment|/*&n; * List functions.&n; */
DECL|macro|LIST_EMPTY
mdefine_line|#define&t;LIST_EMPTY(head)&t;((head)-&gt;lh_first == NULL)
DECL|macro|LIST_FIRST
mdefine_line|#define&t;LIST_FIRST(head)&t;((head)-&gt;lh_first)
DECL|macro|LIST_FOREACH
mdefine_line|#define&t;LIST_FOREACH(var, head, field)&t;&t;&t;&t;&t;&bslash;&n;&t;for ((var) = LIST_FIRST((head));&t;&t;&t;&t;&bslash;&n;&t;    (var);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    (var) = LIST_NEXT((var), field))
DECL|macro|LIST_INIT
mdefine_line|#define&t;LIST_INIT(head) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;LIST_FIRST((head)) = NULL;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|LIST_INSERT_AFTER
mdefine_line|#define&t;LIST_INSERT_AFTER(listelm, elm, field) do {&t;&t;&t;&bslash;&n;&t;if ((LIST_NEXT((elm), field) = LIST_NEXT((listelm), field)) != NULL)&bslash;&n;&t;&t;LIST_NEXT((listelm), field)-&gt;field.le_prev =&t;&t;&bslash;&n;&t;&t;    &amp;LIST_NEXT((elm), field);&t;&t;&t;&t;&bslash;&n;&t;LIST_NEXT((listelm), field) = (elm);&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.le_prev = &amp;LIST_NEXT((listelm), field);&t;&t;&bslash;&n;} while (0)
DECL|macro|LIST_INSERT_BEFORE
mdefine_line|#define&t;LIST_INSERT_BEFORE(listelm, elm, field) do {&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.le_prev = (listelm)-&gt;field.le_prev;&t;&t;&bslash;&n;&t;LIST_NEXT((elm), field) = (listelm);&t;&t;&t;&t;&bslash;&n;&t;*(listelm)-&gt;field.le_prev = (elm);&t;&t;&t;&t;&bslash;&n;&t;(listelm)-&gt;field.le_prev = &amp;LIST_NEXT((elm), field);&t;&t;&bslash;&n;} while (0)
DECL|macro|LIST_INSERT_HEAD
mdefine_line|#define&t;LIST_INSERT_HEAD(head, elm, field) do {&t;&t;&t;&t;&bslash;&n;&t;if ((LIST_NEXT((elm), field) = LIST_FIRST((head))) != NULL)&t;&bslash;&n;&t;&t;LIST_FIRST((head))-&gt;field.le_prev = &amp;LIST_NEXT((elm), field);&bslash;&n;&t;LIST_FIRST((head)) = (elm);&t;&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.le_prev = &amp;LIST_FIRST((head));&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|LIST_NEXT
mdefine_line|#define&t;LIST_NEXT(elm, field)&t;((elm)-&gt;field.le_next)
DECL|macro|LIST_REMOVE
mdefine_line|#define&t;LIST_REMOVE(elm, field) do {&t;&t;&t;&t;&t;&bslash;&n;&t;if (LIST_NEXT((elm), field) != NULL)&t;&t;&t;&t;&bslash;&n;&t;&t;LIST_NEXT((elm), field)-&gt;field.le_prev = &t;&t;&bslash;&n;&t;&t;    (elm)-&gt;field.le_prev;&t;&t;&t;&t;&bslash;&n;&t;*(elm)-&gt;field.le_prev = LIST_NEXT((elm), field);&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Tail queue declarations.&n; */
DECL|macro|TAILQ_HEAD
mdefine_line|#define&t;TAILQ_HEAD(name, type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct name {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *tqh_first;&t;/* first element */&t;&t;&t;&bslash;&n;&t;struct type **tqh_last;&t;/* addr of last next element */&t;&t;&bslash;&n;}
DECL|macro|TAILQ_HEAD_INITIALIZER
mdefine_line|#define&t;TAILQ_HEAD_INITIALIZER(head)&t;&t;&t;&t;&t;&bslash;&n;&t;{ NULL, &amp;(head).tqh_first }
DECL|macro|TAILQ_ENTRY
mdefine_line|#define&t;TAILQ_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *tqe_next;&t;/* next element */&t;&t;&t;&bslash;&n;&t;struct type **tqe_prev;&t;/* address of previous next element */&t;&bslash;&n;}
multiline_comment|/*&n; * Tail queue functions.&n; */
DECL|macro|TAILQ_EMPTY
mdefine_line|#define&t;TAILQ_EMPTY(head)&t;((head)-&gt;tqh_first == NULL)
DECL|macro|TAILQ_FIRST
mdefine_line|#define&t;TAILQ_FIRST(head)&t;((head)-&gt;tqh_first)
DECL|macro|TAILQ_FOREACH
mdefine_line|#define&t;TAILQ_FOREACH(var, head, field)&t;&t;&t;&t;&t;&bslash;&n;&t;for ((var) = TAILQ_FIRST((head));&t;&t;&t;&t;&bslash;&n;&t;    (var);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    (var) = TAILQ_NEXT((var), field))
DECL|macro|TAILQ_FOREACH_REVERSE
mdefine_line|#define&t;TAILQ_FOREACH_REVERSE(var, head, headname, field)&t;&t;&bslash;&n;&t;for ((var) = TAILQ_LAST((head), headname);&t;&t;&t;&bslash;&n;&t;    (var);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    (var) = TAILQ_PREV((var), headname, field))
DECL|macro|TAILQ_INIT
mdefine_line|#define&t;TAILQ_INIT(head) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;TAILQ_FIRST((head)) = NULL;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;tqh_last = &amp;TAILQ_FIRST((head));&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|TAILQ_INSERT_AFTER
mdefine_line|#define&t;TAILQ_INSERT_AFTER(head, listelm, elm, field) do {&t;&t;&bslash;&n;&t;if ((TAILQ_NEXT((elm), field) = TAILQ_NEXT((listelm), field)) != NULL)&bslash;&n;&t;&t;TAILQ_NEXT((elm), field)-&gt;field.tqe_prev = &t;&t;&bslash;&n;&t;&t;    &amp;TAILQ_NEXT((elm), field);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;tqh_last = &amp;TAILQ_NEXT((elm), field);&t;&t;&bslash;&n;&t;TAILQ_NEXT((listelm), field) = (elm);&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.tqe_prev = &amp;TAILQ_NEXT((listelm), field);&t;&t;&bslash;&n;} while (0)
DECL|macro|TAILQ_INSERT_BEFORE
mdefine_line|#define&t;TAILQ_INSERT_BEFORE(listelm, elm, field) do {&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.tqe_prev = (listelm)-&gt;field.tqe_prev;&t;&t;&bslash;&n;&t;TAILQ_NEXT((elm), field) = (listelm);&t;&t;&t;&t;&bslash;&n;&t;*(listelm)-&gt;field.tqe_prev = (elm);&t;&t;&t;&t;&bslash;&n;&t;(listelm)-&gt;field.tqe_prev = &amp;TAILQ_NEXT((elm), field);&t;&t;&bslash;&n;} while (0)
DECL|macro|TAILQ_INSERT_HEAD
mdefine_line|#define&t;TAILQ_INSERT_HEAD(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;if ((TAILQ_NEXT((elm), field) = TAILQ_FIRST((head))) != NULL)&t;&bslash;&n;&t;&t;TAILQ_FIRST((head))-&gt;field.tqe_prev =&t;&t;&t;&bslash;&n;&t;&t;    &amp;TAILQ_NEXT((elm), field);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;tqh_last = &amp;TAILQ_NEXT((elm), field);&t;&t;&bslash;&n;&t;TAILQ_FIRST((head)) = (elm);&t;&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.tqe_prev = &amp;TAILQ_FIRST((head));&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|TAILQ_INSERT_TAIL
mdefine_line|#define&t;TAILQ_INSERT_TAIL(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;TAILQ_NEXT((elm), field) = NULL;&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.tqe_prev = (head)-&gt;tqh_last;&t;&t;&t;&bslash;&n;&t;*(head)-&gt;tqh_last = (elm);&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;tqh_last = &amp;TAILQ_NEXT((elm), field);&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|TAILQ_LAST
mdefine_line|#define&t;TAILQ_LAST(head, headname)&t;&t;&t;&t;&t;&bslash;&n;&t;(*(((struct headname *)((head)-&gt;tqh_last))-&gt;tqh_last))
DECL|macro|TAILQ_NEXT
mdefine_line|#define&t;TAILQ_NEXT(elm, field) ((elm)-&gt;field.tqe_next)
DECL|macro|TAILQ_PREV
mdefine_line|#define&t;TAILQ_PREV(elm, headname, field)&t;&t;&t;&t;&bslash;&n;&t;(*(((struct headname *)((elm)-&gt;field.tqe_prev))-&gt;tqh_last))
DECL|macro|TAILQ_REMOVE
mdefine_line|#define&t;TAILQ_REMOVE(head, elm, field) do {&t;&t;&t;&t;&bslash;&n;&t;if ((TAILQ_NEXT((elm), field)) != NULL)&t;&t;&t;&t;&bslash;&n;&t;&t;TAILQ_NEXT((elm), field)-&gt;field.tqe_prev = &t;&t;&bslash;&n;&t;&t;    (elm)-&gt;field.tqe_prev;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;tqh_last = (elm)-&gt;field.tqe_prev;&t;&t;&bslash;&n;&t;*(elm)-&gt;field.tqe_prev = TAILQ_NEXT((elm), field);&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Circular queue declarations.&n; */
DECL|macro|CIRCLEQ_HEAD
mdefine_line|#define&t;CIRCLEQ_HEAD(name, type)&t;&t;&t;&t;&t;&bslash;&n;struct name {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *cqh_first;&t;&t;/* first element */&t;&t;&bslash;&n;&t;struct type *cqh_last;&t;&t;/* last element */&t;&t;&bslash;&n;}
DECL|macro|CIRCLEQ_HEAD_INITIALIZER
mdefine_line|#define&t;CIRCLEQ_HEAD_INITIALIZER(head)&t;&t;&t;&t;&t;&bslash;&n;&t;{ (void *)&amp;(head), (void *)&amp;(head) }
DECL|macro|CIRCLEQ_ENTRY
mdefine_line|#define&t;CIRCLEQ_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *cqe_next;&t;&t;/* next element */&t;&t;&bslash;&n;&t;struct type *cqe_prev;&t;&t;/* previous element */&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Circular queue functions.&n; */
DECL|macro|CIRCLEQ_EMPTY
mdefine_line|#define&t;CIRCLEQ_EMPTY(head)&t;((head)-&gt;cqh_first == (void *)(head))
DECL|macro|CIRCLEQ_FIRST
mdefine_line|#define&t;CIRCLEQ_FIRST(head)&t;((head)-&gt;cqh_first)
DECL|macro|CIRCLEQ_FOREACH
mdefine_line|#define&t;CIRCLEQ_FOREACH(var, head, field)&t;&t;&t;&t;&bslash;&n;&t;for ((var) = CIRCLEQ_FIRST((head));&t;&t;&t;&t;&bslash;&n;&t;    (var) != (void *)(head);&t;&t;&t;&t;&t;&bslash;&n;&t;    (var) = CIRCLEQ_NEXT((var), field))
DECL|macro|CIRCLEQ_FOREACH_REVERSE
mdefine_line|#define&t;CIRCLEQ_FOREACH_REVERSE(var, head, field)&t;&t;&t;&bslash;&n;&t;for ((var) = CIRCLEQ_LAST((head));&t;&t;&t;&t;&bslash;&n;&t;    (var) != (void *)(head);&t;&t;&t;&t;&t;&bslash;&n;&t;    (var) = CIRCLEQ_PREV((var), field))
DECL|macro|CIRCLEQ_INIT
mdefine_line|#define&t;CIRCLEQ_INIT(head) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;CIRCLEQ_FIRST((head)) = (void *)(head);&t;&t;&t;&t;&bslash;&n;&t;CIRCLEQ_LAST((head)) = (void *)(head);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|CIRCLEQ_INSERT_AFTER
mdefine_line|#define&t;CIRCLEQ_INSERT_AFTER(head, listelm, elm, field) do {&t;&t;&bslash;&n;&t;CIRCLEQ_NEXT((elm), field) = CIRCLEQ_NEXT((listelm), field);&t;&bslash;&n;&t;CIRCLEQ_PREV((elm), field) = (listelm);&t;&t;&t;&t;&bslash;&n;&t;if (CIRCLEQ_NEXT((listelm), field) == (void *)(head))&t;&t;&bslash;&n;&t;&t;CIRCLEQ_LAST((head)) = (elm);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;CIRCLEQ_PREV(CIRCLEQ_NEXT((listelm), field), field) = (elm);&bslash;&n;&t;CIRCLEQ_NEXT((listelm), field) = (elm);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|CIRCLEQ_INSERT_BEFORE
mdefine_line|#define&t;CIRCLEQ_INSERT_BEFORE(head, listelm, elm, field) do {&t;&t;&bslash;&n;&t;CIRCLEQ_NEXT((elm), field) = (listelm);&t;&t;&t;&t;&bslash;&n;&t;CIRCLEQ_PREV((elm), field) = CIRCLEQ_PREV((listelm), field);&t;&bslash;&n;&t;if (CIRCLEQ_PREV((listelm), field) == (void *)(head))&t;&t;&bslash;&n;&t;&t;CIRCLEQ_FIRST((head)) = (elm);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;CIRCLEQ_NEXT(CIRCLEQ_PREV((listelm), field), field) = (elm);&bslash;&n;&t;CIRCLEQ_PREV((listelm), field) = (elm);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|CIRCLEQ_INSERT_HEAD
mdefine_line|#define&t;CIRCLEQ_INSERT_HEAD(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;CIRCLEQ_NEXT((elm), field) = CIRCLEQ_FIRST((head));&t;&t;&bslash;&n;&t;CIRCLEQ_PREV((elm), field) = (void *)(head);&t;&t;&t;&bslash;&n;&t;if (CIRCLEQ_LAST((head)) == (void *)(head))&t;&t;&t;&bslash;&n;&t;&t;CIRCLEQ_LAST((head)) = (elm);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;CIRCLEQ_PREV(CIRCLEQ_FIRST((head)), field) = (elm);&t;&bslash;&n;&t;CIRCLEQ_FIRST((head)) = (elm);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|CIRCLEQ_INSERT_TAIL
mdefine_line|#define&t;CIRCLEQ_INSERT_TAIL(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;CIRCLEQ_NEXT((elm), field) = (void *)(head);&t;&t;&t;&bslash;&n;&t;CIRCLEQ_PREV((elm), field) = CIRCLEQ_LAST((head));&t;&t;&bslash;&n;&t;if (CIRCLEQ_FIRST((head)) == (void *)(head))&t;&t;&t;&bslash;&n;&t;&t;CIRCLEQ_FIRST((head)) = (elm);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;CIRCLEQ_NEXT(CIRCLEQ_LAST((head)), field) = (elm);&t;&bslash;&n;&t;CIRCLEQ_LAST((head)) = (elm);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|CIRCLEQ_LAST
mdefine_line|#define&t;CIRCLEQ_LAST(head)&t;((head)-&gt;cqh_last)
DECL|macro|CIRCLEQ_NEXT
mdefine_line|#define&t;CIRCLEQ_NEXT(elm,field)&t;((elm)-&gt;field.cqe_next)
DECL|macro|CIRCLEQ_PREV
mdefine_line|#define&t;CIRCLEQ_PREV(elm,field)&t;((elm)-&gt;field.cqe_prev)
DECL|macro|CIRCLEQ_REMOVE
mdefine_line|#define&t;CIRCLEQ_REMOVE(head, elm, field) do {&t;&t;&t;&t;&bslash;&n;&t;if (CIRCLEQ_NEXT((elm), field) == (void *)(head))&t;&t;&bslash;&n;&t;&t;CIRCLEQ_LAST((head)) = CIRCLEQ_PREV((elm), field);&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;CIRCLEQ_PREV(CIRCLEQ_NEXT((elm), field), field) =&t;&bslash;&n;&t;&t;    CIRCLEQ_PREV((elm), field);&t;&t;&t;&t;&bslash;&n;&t;if (CIRCLEQ_PREV((elm), field) == (void *)(head))&t;&t;&bslash;&n;&t;&t;CIRCLEQ_FIRST((head)) = CIRCLEQ_NEXT((elm), field);&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;CIRCLEQ_NEXT(CIRCLEQ_PREV((elm), field), field) =&t;&bslash;&n;&t;&t;    CIRCLEQ_NEXT((elm), field);&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* !_SYS_QUEUE_H_ */
eof
