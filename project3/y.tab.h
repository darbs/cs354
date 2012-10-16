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
extern YYSTYPE yylval;
