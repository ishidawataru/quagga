/* BGP Community list.
   Copyright (C) 1999 Kunihiro Ishiguro

This file is part of GNU Zebra.

GNU Zebra is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

GNU Zebra is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Zebra; see the file COPYING.  If not, write to the Free
Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

#ifndef _QUAGGA_BGP_CLIST_H
#define _QUAGGA_BGP_CLIST_H

#include "symtab.h"

/* Master Community-list. */
#define COMMUNITY_LIST_MASTER          0
#define EXTCOMMUNITY_LIST_MASTER       1

/* Community-list deny and permit.  */
#define COMMUNITY_DENY                 0
#define COMMUNITY_PERMIT               1

/* Number and string based community-list name.  */
//#define COMMUNITY_LIST_STRING          0
//#define COMMUNITY_LIST_NUMBER          1

/* Community-list entry types.  */
#define COMMUNITY_LIST_STANDARD        0 /* Standard community-list.  */
#define COMMUNITY_LIST_EXPANDED        1 /* Expanded community-list.  */
#define EXTCOMMUNITY_LIST_STANDARD     2 /* Standard extcommunity-list.  */
#define EXTCOMMUNITY_LIST_EXPANDED     3 /* Expanded extcommunity-list.  */

/* Community-list.  */
struct community_list
{
  /* Pointer to symbol entry of the community-list.     */
  symbol sym ;

  /* String or number.  */
//int sort;

  /* Community-list entry in this community-list.       */
  struct community_entry *head;
  struct community_entry *tail;

  /* Name of community-list                             */
  char  name[] ;
};

/* Each entry in community-list.  */
struct community_entry
{
  struct community_entry *next;
  struct community_entry *prev;

  /* Permit or deny.  */
  u_char direct;

  /* Standard or expanded.  */
  u_char style;

  /* Any match.  */
  u_char any;

  /* Community structure.  */
  union
  {
    struct community *com;
    struct ecommunity *ecom;
  } u;

  /* Configuration string.  */
  char *config;

  /* Expanded community-list regular expression.  */
  regex_t *reg;
};

/* Community-list handler.
 * community_list_init() returns this structure as handler -- contains a
 * distinct set of community-list and extcommunity-list filters.
 */
struct community_list_handler ;

/* Error code of community-list.  */
#define COMMUNITY_LIST_ERR_CANT_FIND_LIST        -1
#define COMMUNITY_LIST_ERR_MALFORMED_VAL         -2
#define COMMUNITY_LIST_ERR_STANDARD_CONFLICT     -3
#define COMMUNITY_LIST_ERR_EXPANDED_CONFLICT     -4

/* Handler.  */
extern struct community_list_handler *bgp_clist;

/* Prototypes.  */
extern struct community_list_handler *community_list_init (void);
extern void community_list_terminate (struct community_list_handler *);

extern int community_list_set (struct community_list_handler *ch,
                               const char *name, const char *str, int direct,
                               int style);
extern int community_list_unset (struct community_list_handler *ch,
                                 const char *name, const char *str,
                                 int direct, int style);
extern int extcommunity_list_set (struct community_list_handler *ch,
                                  const char *name, const char *str,
                                  int direct, int style);
extern int extcommunity_list_unset (struct community_list_handler *ch,
                                    const char *name, const char *str,
                                    int direct, int style);

extern struct symbol_table*
community_list_master_lookup (struct community_list_handler *, int);

extern struct community_list *
community_list_lookup (struct community_list_handler *, const char *, int);

extern int community_list_match (struct community *, struct community_list *);
extern int ecommunity_list_match (struct ecommunity *, struct community_list *);
extern int community_list_exact_match (struct community *,
                                       struct community_list *);
extern struct community *
community_list_match_delete (struct community *, struct community_list *);

#endif /* _QUAGGA_BGP_CLIST_H */
