

#ifndef _MENU_H
#define _MENU_H

#include "u8g2.h"


typedef struct _menu_struct menu_t;
typedef struct _me_struct me_t;

typedef int (*me_cb)(menu_t *menu, const me_t *me, uint8_t msg);

struct _me_struct
{
  me_cb cb;
  void *arg;
  u8g2_uint_t x;
  u8g2_uint_t y;  
};


/* return 1, if this element can have focus */
#define ME_MSG_IS_FOCUS 1

/* request to fill x, y, w, h args of the menu struct */
#define ME_MSG_GET_BBX 2

/* user has pressed the select key */
#define ME_MSG_SELECT 3

/* advice for drawing */
#define ME_MSG_DRAW 4


struct _menu_struct
{
  u8g2_t *u8g2;
  
  volatile uint16_t current_index;	/* element which is processed right now */
  uint16_t focus_index;	/* element which has the focus at the moment */
  uint16_t radio_index;	/* if elements for a radio selection, then this is set by the cb */
  uint16_t me_count;	/* total number of elements in the list */
  
  /* this is the bounding box returned by ME_MSG_GET_BBX */
  u8g2_uint_t x;
  u8g2_uint_t y;
  u8g2_uint_t w;
  u8g2_uint_t h;
  
  /* pointer to the list of menu elements */
  const me_t *me_list;
  
};

void menu_Init(menu_t *menu, u8g2_t *u8g2);
void menu_SetMEList(menu_t *menu, const me_t *me_list, uint16_t initial_focus);
void menu_Draw(menu_t *menu);
void menu_NextFocus(menu_t *menu);
void menu_Select(menu_t *menu);


int me_cb_null(menu_t *menu, const me_t *me, uint8_t msg);
int me_cb_0_9(menu_t *menu, const me_t *me, uint8_t msg);

#endif
