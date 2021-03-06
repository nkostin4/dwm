/* See LICENSE file for copyright and license details. */

/* Authentic signature from N. Kostin 2021-04-04 20:00:00 Moskva */

// #define TERMINAL "urxvt"
// #define TERMCLASS "URxvt"
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "inconsolata:size=10" };
static const char dmenufont[]       = "inconsolata:size=10";
// background color (bar almost black)
static const char col_gray1[]       = "#111111";
// inactive window border color
static const char col_gray2[]       = "#444444";
// font color
static const char col_gray3[]       = "#bbbbbb";
// current tag and current window font color
static const char col_gray4[]       = "#eeeeee";
// active window border color
static const char col_cyan[]        = "#cc3333";
// static const char col_cyan[]        = "#bf00bf";
static const unsigned int baralpha = 0x00;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
// static const char *tags[] = { "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	// { "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ TERMCLASS, NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
// volume controls
static const char *upvol[] = { "amixer", "-q", "set", "Master", "1%+", "unmute", NULL };
static const char *downvol[] = { "amixer", "-q", "set", "Master", "1%-", "unmute", NULL };
static const char *mutevol[] = { "amixer", "-q", "set", "Master", "toggle", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	// { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	// { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	// { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	// { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,         {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,    {0} },
	{ MODKEY|ControlMask,           XK_space,  togglealwaysontop, {0} },
    { MODKEY,                       XK_s,      togglesticky,      {0} },
	{ MODKEY,                       XK_u,      moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_i,      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_o,      moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_y,      moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_u,      moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_i,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_o,      moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_y,      moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_i,      moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_u,      moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_y,      moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_o,      moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_i,      moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_u,      moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_y,      moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_o,      moveresizeedge, {.v = "R"} },
	// { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
	// { MODKEY,                       XK_r,      spawn,          SHCMD("pcmanfm") },
	// { MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD(TERMINAL " -e htop") },
	// { MODKEY,                       XK_F3,     spawn,          {.v = upvol }   },
	// { MODKEY,                       XK_F2,     spawn,          {.v = downvol } },
	// { MODKEY,                       XK_F1,     spawn,          {.v = mutevol } },
	{ MODKEY,                       XF86XK_AudioRaiseVolume,     spawn,          {.v = upvol }   },
	{ MODKEY,                       XF86XK_AudioLowerVolume,     spawn,          {.v = downvol } },
	{ MODKEY,                       XF86XK_AudioMute,            spawn,          {.v = mutevol } },
	{ MODKEY,                       XF86XK_AudioPlay,            spawn,          SHCMD("mpc toggle") },
	{ MODKEY,                       XF86XK_AudioPrev,            spawn,          SHCMD("mpc prev") },
	{ MODKEY,                       XF86XK_AudioNext,            spawn,          SHCMD("mpc next") },
	// { MODKEY,                       XF86XK_MonBrightnessUp,      spawn,          SHCMD("xbacklight -inc 15")  },
	// { MODKEY,                       XF86XK_MonBrightnessDown,    spawn,          SHCMD("xbacklight -dec 15")  },
	{ MODKEY,                       XF86XK_MonBrightnessUp,      spawn,          SHCMD("backlight_control +10")  },
	{ MODKEY,                       XF86XK_MonBrightnessDown,    spawn,          SHCMD("backlight_control -10")  },
	{ 0,                            XK_Print,                    spawn,          SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,                    XK_Print,                    spawn,          SHCMD("maimpick") },
	{ MODKEY,                       XK_Print,                    spawn,          SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,             XK_Print,                    spawn,          SHCMD("dmenurecord kill") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

