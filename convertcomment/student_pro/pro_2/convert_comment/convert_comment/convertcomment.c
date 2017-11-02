
/**********************************************************
*    > File Name: convertcomment.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月23日 星期六 16时57分04秒
**********************************************************/

#include"convertcomment.h"

//定义状态
typedef enum
{
    NO_COMMENT_STATE,
    C_COMMENT_STATE,
    CPP_COMMENT_STATE,
    STR_STATE,
    END_STATE
}enum_state;

//定义状态机
typedef struct 
{
    FILE *inputfile;
    FILE *outputfile;
    enum_state ulstate;
}state_machine;

/////////////////////////////////////////////////////
FILE* open_file(char *filename, char *mode)
{
    FILE *fp = fopen(filename, mode);
    if(fp == NULL)
    {
        printf("open %s fail.\n",filename);
        exit(1);
    }
    return fp;
}
void close_file(FILE *fp)
{
    fclose(fp);
}

char read_ch(FILE *fp)
{
    assert(fp != NULL);
    return fgetc(fp);
}
void write_ch(char ch, FILE *fp)
{
    assert(fp != NULL);
    fputc(ch, fp);
}
void write_double_ch(char ch1, char ch2, FILE *fp)
{
    assert(fp != NULL);
    fputc(ch1, fp);
    fputc(ch2, fp);
}

/////////////////////////////////////////////////////
state_machine g_state;

int convertcomment(FILE *inputfile, FILE *outputfile)
{
    if(inputfile==NULL || outputfile==NULL)
    {
        printf("argument is invalid.\n");
        return -1;
    }

    //初始化状态机
    g_state.inputfile = inputfile;
    g_state.outputfile = outputfile;
    g_state.ulstate = NO_COMMENT_STATE; 

    char ch;
    while(g_state.ulstate != END_STATE)
    {
        ch = fgetc(g_state.inputfile);
        eventpro(ch);
    }
    
    return 0;
}

void eventpro(char ch)
{
    switch(g_state.ulstate)
    {
    case NO_COMMENT_STATE:
        eventpro_no(ch);
        break;
    case C_COMMENT_STATE:
        eventpro_c(ch);
        break;
    case CPP_COMMENT_STATE:
        eventpro_cpp(ch);
        break;
    case STR_STATE:
	eventpro_str(ch);
	break; 
    case END_STATE:
        break;
    }
}

void eventpro_no(char ch)
{
    char nextch;
    switch(ch)
    {
    case '/':
    {
		nextch = read_ch(g_state.inputfile);
        if(nextch == '/')   //C++ Comment
        {
            write_double_ch('/','*', g_state.outputfile);
            g_state.ulstate = CPP_COMMENT_STATE;
        }
		else if(nextch == '*')
		{
			write_double_ch(ch,nextch,g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;
		}
		else 
		{
			write_double_ch(ch,nextch,g_state.outputfile);
			g_state.ulstate = NO_COMMENT_STATE;
		}
        break;
    }
	case '"':
		fputc(ch,g_state.outputfile);
		g_state.ulstate = STR_STATE;
		break;
	case EOF:
		g_state.ulstate = END_STATE;
		break;
	default :
		fputc(ch,g_state.outputfile);
		break;
	}
}

void eventpro_c(char ch)
{
	char nextch;
    switch(ch)
	{
	case '/':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/' || nextch == '*')
		{
			write_double_ch(' ',' ',g_state.outputfile);		
		}
		break;
	case '*':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/')
		{
			write_double_ch(ch,nextch,g_state.outputfile);
			g_state.ulstate = NO_COMMENT_STATE;
		}
		break;
	case '"':
		fputc(ch,g_state.outputfile);
		g_state.ulstate = STR_STATE;
	break;

	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
void eventpro_cpp(char ch)
{
    char nextch;
    switch(ch)
    {
    case EOF:
        fputc('*', g_state.outputfile);
        fputc('/', g_state.outputfile);
        g_state.ulstate = END_STATE;
        break;
    case '\n':
        fputc('*', g_state.outputfile);
        fputc('/', g_state.outputfile);
        fputc('\n',g_state.outputfile);
        g_state.ulstate = NO_COMMENT_STATE;
        break;
    case '/':
        nextch = fgetc(g_state.inputfile);
        if(nextch=='/' || nextch=='*') // 123  //456  or /*abc
        {
            fputc(' ',g_state.outputfile);
            fputc(' ',g_state.outputfile);
        }
        break;
    case '*':
        nextch = fgetc(g_state.inputfile);
        if(nextch == '/')
        {
            fputc(' ',g_state.outputfile);
            fputc(' ',g_state.outputfile);
        }
        break;
    default:
        fputc(ch, g_state.outputfile);
        break;
    }
}

void eventpro_str(char ch)
{
	char nextch;
	switch(ch)
	{
	case '\0':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '"')
		{
			write_double_ch(ch,nextch,g_state.outputfile);
			g_state.ulstate = NO_COMMENT_STATE;
		}
		break;
	case '"':
		fputc(ch,g_state.outputfile);
		g_state.ulstate = NO_COMMENT_STATE;
		break;
	case EOF:
		g_state.ulstate = END_STATE;
		break;
	default :
		fputc(ch,g_state.outputfile);
		break;
	}
}




















