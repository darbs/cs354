#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20101229

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "bvh.y"
	#include <iostream>
	#include <cstring>
	#include <cstdio>
	#include <stdint.h>
	#include "joint_info.h"
	#include "bvh_cb_info.h"
	#include "bvh_defs.h"
	using namespace std;
	void yyerror(const char * s);
	char endsitestr[]="_end_site_";
	int lb=0, rb=0,numframes=0,frameidx=0,framecnt=0;
	uint32_t framesz=0;
	extern "C"
	{
		extern int yylex(void);
	}	
	extern void BEGIN_FL(void);
	extern bvh_cb_info * bci;
	float * frameflt=0;
#line 28 "bvh.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	int ival;
	float fval;
	char * sval;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 52 "y.tab.c"
/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#define YYERROR_DECL() yyerror(const char *s)
#define YYERROR_CALL(msg) yyerror(msg)

extern int YYPARSE_DECL();

#define HIERARCHY 257
#define ROOT 258
#define JOINT 259
#define OFFSET 260
#define CHANNELS 261
#define MOTION 262
#define FRAMES 263
#define FRAME 264
#define TIME 265
#define END 266
#define SITE 267
#define LBRACK 268
#define RBRACK 269
#define COLON 270
#define NEWLINE 271
#define INT 272
#define FLOAT 273
#define ID 274
#define PARAM 275
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    2,    3,    8,    6,    7,    7,   11,   11,   11,
   12,   14,   14,    5,    9,   17,   10,   13,   15,    1,
    1,   16,   18,   19,   19,   20,    4,   21,   22,   23,
   24,   24,   25,   26,   26,   27,
};
static const short yylen[] = {                            2,
    3,    1,    3,    3,    1,    4,    4,    2,    2,    1,
    4,    1,    2,    1,    1,    2,    1,    1,    4,    1,
    1,    3,    1,    1,    2,    1,    4,    2,    4,    5,
    1,    2,    2,    1,    2,    1,
};
static const short yydefred[] = {                         0,
    2,    0,    0,   14,    0,    0,    0,    1,    0,    5,
    0,   28,    0,    0,   17,    3,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   21,   20,   36,
    0,   31,    0,   34,    0,   23,    0,   15,    0,   12,
    0,    0,    0,    0,    8,    9,   29,    0,   32,   33,
   35,    0,   26,    0,   24,   16,    0,   18,    6,   13,
    7,    0,    0,   19,   25,    4,    0,   30,   11,
};
static const short yydgoto[] = {                          2,
   30,    3,    5,    8,    6,   11,   16,   40,   41,   17,
   23,   42,   59,   43,   24,   25,   44,   37,   54,   55,
    9,   14,   20,   31,   32,   33,   34,
};
static const short yysindex[] = {                      -251,
    0,    0, -248,    0, -237, -266, -259,    0, -241,    0,
 -239,    0, -243, -234,    0,    0, -240, -238, -232, -249,
 -249, -236, -252, -230, -225, -233, -231,    0,    0,    0,
 -249,    0, -254,    0, -249,    0, -235,    0, -226,    0,
 -266, -227, -256, -239,    0,    0,    0, -249,    0,    0,
    0, -249,    0, -235,    0,    0, -239,    0,    0,    0,
    0, -225, -228,    0,    0,    0, -227,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -250,    0,    0,    0,    0,    0,    0,
   44,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -255,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
  -20,    0,    0,    0,    0,    4,  -11,    5,    0,    3,
    0,    0,  -41,    0,  -25,   25,    0,    0,    0,   -4,
    0,    0,    0,    0,   20,    0,   19,
};
#define YYTABLESIZE 52
static const short yytable[] = {                         46,
   35,   61,   38,   22,   22,    1,   38,   10,   10,    4,
   22,   12,   58,   39,   52,   10,   50,   28,   29,   21,
   22,   13,   28,   29,    7,   69,   18,   63,   15,   19,
   22,   64,   27,   26,   21,   36,   67,   47,   48,   53,
   56,   58,   68,   27,   57,   66,   62,   60,   45,   65,
   49,   51,
};
static const short yycheck[] = {                         25,
   21,   43,  259,  259,  260,  257,  259,  274,  259,  258,
  266,  271,  269,  266,   35,  266,  271,  272,  273,  260,
  261,  263,  272,  273,  262,   67,  270,   48,  268,  264,
  261,   52,  265,  272,  260,  272,   62,  271,  270,  275,
  267,  269,  271,    0,   41,   57,   44,   43,   24,   54,
   31,   33,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 275
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"HIERARCHY","ROOT","JOINT",
"OFFSET","CHANNELS","MOTION","FRAMES","FRAME","TIME","END","SITE","LBRACK",
"RBRACK","COLON","NEWLINE","INT","FLOAT","ID","PARAM",
};
static const char *yyrule[] = {
"$accept : bvh",
"bvh : header root motion",
"header : HIERARCHY",
"root : root_tag id joint_post",
"joint : joint_tag id joint_post",
"id : ID",
"joint_post : lbrack joint_info end_site rbrack",
"joint_post : lbrack joint_info joints rbrack",
"joint_info : offset channels",
"joint_info : channels offset",
"joint_info : offset",
"end_site : end_site_tag lbrack offset rbrack",
"joints : joint",
"joints : joints joint",
"root_tag : ROOT",
"joint_tag : JOINT",
"end_site_tag : END SITE",
"lbrack : LBRACK",
"rbrack : RBRACK",
"offset : OFFSET num num num",
"num : FLOAT",
"num : INT",
"channels : CHANNELS numchans params",
"numchans : INT",
"params : param",
"params : params param",
"param : PARAM",
"motion : motion_header frames frame_time frame_info",
"motion_header : MOTION NEWLINE",
"frames : FRAMES COLON INT NEWLINE",
"frame_time : FRAME TIME COLON num NEWLINE",
"frame_info : frame_line",
"frame_info : frame_info frame_line",
"frame_line : frame_body NEWLINE",
"frame_body : frame_float",
"frame_body : frame_body frame_float",
"frame_float : num",

};
#endif
/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 188 "bvh.y"
#include <stdio.h>
#include <iostream>
using namespace std;

extern "C"
{
	extern FILE * yyin;
	extern int yylex(void);
	extern int yylineno;
}

void yyerror(const char * s);

int load_bvh(const char * filename)
{
	FILE * file = fopen(filename,"r");
	if(!file)
	{
		cout << "can't open file"<<endl;
		return -1;
	}
	yyin=file;
	yylineno=1;
	do
	{
		yyparse();
	}
	while(!feof(yyin));
	return 0;
}

void yyerror(const char * s)
{
	cout <<"Parse error:"<<s<<" line:"<<yylineno<<endl;
	//exit(-1);
}

#line 296 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 2:
#line 42 "bvh.y"
	{
	joints.clear();
	last_id=0;
	jcnt=0;
}
break;
case 5:
#line 52 "bvh.y"
	{
	curr.name=yylval.sval;
	curr.id=last_id++;
}
break;
case 14:
#line 65 "bvh.y"
	{curr.type=BVH_ROOT;jcnt++;}
break;
case 15:
#line 67 "bvh.y"
	{curr.type=BVH_JOINT;jcnt++;}
break;
case 16:
#line 70 "bvh.y"
	{curr.id=last_id++;curr.type=BVH_END_SITE;strcpy((curr.name=new char[strlen(endsitestr)+1]),endsitestr);jcnt++;}
break;
case 17:
#line 72 "bvh.y"
	{
	lb++;
	if(bci) {
		void (*create_fn)(const char *,unsigned int)=0;
		switch(curr.type)
		{
			case BVH_ROOT: create_fn=bci->create_root; break;
			case BVH_JOINT: create_fn=bci->create_joint; break;
			case BVH_END_SITE: create_fn=bci->create_end_site; break;
		}
		if(create_fn)
			create_fn(curr.name,curr.id);
	}
	delete [] curr.name;
	if(curr.type!=BVH_ROOT) {
		curr.parent=joints.back().id;
		if(bci && bci->set_child)
			bci->set_child(curr.parent,curr.id);
	}
	joints.push_back(curr);
	curr.chanflags=0;
}
break;
case 18:
#line 95 "bvh.y"
	{
	rb++;
	if(joints.size()>0) 
		joints.pop_back();
	else 
		yyerror("Unmatched bracket");
}
break;
case 19:
#line 103 "bvh.y"
	{
	curr.offset[0]=yystack.l_mark[-2].fval;
	curr.offset[1]=yystack.l_mark[-1].fval;
	curr.offset[2]=yystack.l_mark[0].fval;
	if(bci && bci->set_offset)
		bci->set_offset(curr.id,curr.offset);
}
break;
case 21:
#line 111 "bvh.y"
	{
	yyval.fval=(float)yystack.l_mark[0].ival;
}
break;
case 22:
#line 114 "bvh.y"
	{
	if(paramcount!=curr.numchans) 
		yyerror("Number of params and actual number parsed do not match.");
	if(bci && bci->set_channel_flags)
		bci->set_channel_flags(curr.id,curr.chanflags);
	if(bci && bci->set_frame_index)
		bci->set_frame_index(curr.id,framesz);
	if(bci && bci->set_channel_order)
		bci->set_channel_order(curr.id,curr.order);
	framesz+=curr.numchans;
}
break;
case 23:
#line 126 "bvh.y"
	{
	if(yystack.l_mark[0].ival<0) yyerror("Negative argument not allowed for numchans.");
	curr.numchans=yystack.l_mark[0].ival;
	memset(curr.order,BVH_CHAN_INVALID,BVH_MAX_CHANS*sizeof(int));
	paramcount=0;
	if(bci && bci->set_num_channels)
		bci->set_num_channels(curr.id,curr.numchans);
		if (curr.numchans>BVH_MAX_CHANS) 
			yyerror("Number of declared channels exceeds maximum number of allowed channels.");
}
break;
case 26:
#line 139 "bvh.y"
	{
	if(((0x1<<(yylval.ival)) & curr.chanflags) != 0) yyerror("Chanel flag already set.");
	curr.chanflags |= (0x1<<(yylval.ival));
	curr.order[paramcount]=yylval.ival;
	paramcount++;
}
break;
case 27:
#line 146 "bvh.y"
	{
	if(framecnt<numframes) yyerror("Not enough frames read.");
}
break;
case 29:
#line 152 "bvh.y"
	{
	frameflt=new float[framesz];
	numframes=yylval.ival;
	if(numframes<1) yyerror("Bad argument for number of frames.");
	if(bci && bci->set_num_frames) bci->set_num_frames(numframes);
}
break;
case 30:
#line 159 "bvh.y"
	{
	if(bci && bci->set_frame_time)
		bci->set_frame_time(yystack.l_mark[-1].fval);
	BEGIN_FL();
}
break;
case 33:
#line 167 "bvh.y"
	{
	if(framecnt==numframes) yyerror("Too many frames read.");
	framecnt++;
	if(frameidx<framesz) yyerror("Not enough values for frame.");
	if(framecnt==1&&bci&&bci->set_frame_size)
		bci->set_frame_size(framesz);
	if(bci&&bci->add_frame) 
		bci->add_frame(frameflt);
	if(numframes==framecnt) 
		delete [] frameflt;
	frameidx=0;
}
break;
case 36:
#line 182 "bvh.y"
	{
	if(frameidx>framesz) yyerror("Too many values for frame.");
	frameflt[frameidx++]=yystack.l_mark[0].fval;
}
break;
#line 661 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
