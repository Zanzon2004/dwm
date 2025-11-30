/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int smartgaps    = 0;        /* 1 means no outer gap when there is only one window */

static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
// static const int splitstatus        = 0;        /* 1 for split status items */
// static const char *splitdelim        = ";";       /* Character used for separating status */
static char font[]          = "monospace:size=14";
static char dmenufont[]       = "monospace:size=14";

static unsigned int baralpha        = 0xE6U;
static unsigned int borderalpha     = 0x99U;

static const char *fonts[]          = { font };

// static const char norm_fg[] = "#cacaca";
// static const char norm_bg[] = "#121110";
// static const char norm_border[] = "#8d8d8d";
//
// static const char sel_fg[] = "#cacaca";
// static const char sel_bg[] = "#504F4E";
// static const char sel_border[] = "#cacaca";
//
// static const char urg_fg[] = "#cacaca";
// static const char urg_bg[] = "#3F4040";
// static const char urg_border[] = "#3F4040";
//
#include "/home/zanzon/.cache/wal/colors-wal-dwm.h"
// static const char *colors[][3]      = {
//     /*               fg           bg         border                         */
//     [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
//     [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
//     [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
// };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },

	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	
    { "H[]",      deck },
	{ "[M]",      monocle },
	
    { "===",      bstackhoriz },
	{ "HHH",      grid },
    { "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	
    { "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	
    { "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_border, "-sf", sel_fg, NULL };
static const char *termcmd[]  = { "st", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    { "font",               STRING,  &font },
    { "dmenufont",          STRING,  &dmenufont },
    { "norm_bg",        STRING,  &norm_bg },
    { "norm_border",    STRING,  &norm_border },
    { "norm_fg",        STRING,  &norm_fg },
    { "sel_bg",         STRING,  &sel_bg },
    { "sel_border",     STRING,  &sel_border },
    { "sel_fg",         STRING,  &sel_fg },
    { "borderpx",          	INTEGER, &borderpx },
    { "snap",          		INTEGER, &snap },
    { "showbar",          	INTEGER, &showbar },
    { "topbar",          	INTEGER, &topbar },
    { "nmaster",          	INTEGER, &nmaster },
    { "resizehints",       	INTEGER, &resizehints },
    { "mfact",      	 	FLOAT,   &mfact },
};

static const Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
    { MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
    { MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_space,  zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* tile */
    { MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} }, /* bstack */
    { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[2]} }, /* spiral */
    { MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[3]} }, /* dwindle */
    { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} }, /* deck */
    { MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[5]} }, /* monocle */
    { MODKEY,                       XK_i,      setlayout,      {.v = &layouts[11]} }, /* centeredmaster */
    { MODKEY|ShiftMask,             XK_i,      setlayout,      {.v = &layouts[12]} }, /* centeredfloatingmaster */
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,                       XK_f,      togglefullscr,  {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    /* Vanity gabs */
    { MODKEY,                       XK_z,      incrgaps,       {.i = +3 } },
    { MODKEY,                       XK_x,      incrgaps,       {.i = -3 } },
    /*{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
    { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
    { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
    { MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
    { MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
    { MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
    { MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
    { MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
    { MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
    { MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
    { MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
    { MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
    { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },*/
    { MODKEY,                       XK_a,      togglegaps,     {0} },

    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

