#pragma once

#include "kyleterry.h"

enum {
  /* tap dance for raise and lower layer switching */
  TD_RL = 0,
  /* tap dance for common cording */
  TD_C  = 1,
  /* tap dance for media keys */
  TD_MD = 2,
  /* tap dance for paren matching */
  TD_PN = 3,
  /* tap dance for square bracket matching */
  TD_SB = 4,
  /* tap dance for curly brace matching */
  TD_CB = 5,
};

#define T_C         TD(TD_C)
#define T_MD        TD(TD_MD)
#define T_PN        TD(TD_PN)
#define T_SB        TD(TD_SB)
#define T_CB        TD(TD_CB)
