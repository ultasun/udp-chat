/*
| readline(), writebuffer copied/modified from R. Stevens & Paul Griffiths.
| see http://www.paulgriffiths.net/program/c/srcs/echoservsrc.html
\*-------------------------------------------------------------------*/
#include "process.h"

/*
| Make a reversed copy of a source string.
| Return a pointer to the end of the reversed string.
*/
char *strrev(char *t, char *s)
{
    char *r = s;
    char *p = t;
    while (*r++ != '\0')
        ;
    r -= 2;
    while (r >= s)
        *p++ = *r--;
    *p = '\0';
    return p;
}
//--------------------------------------------------------------------


char *back_words(char *tgt, char *src, size_t bufsize)
{
    char *work = malloc(bufsize);
    char *sp, *tp, *wp;
    char ch;

    wp = work;
    sp = src;
    tp = tgt;

    do {
        ch = *sp++;
        switch (ch) {
          case ' ':
          case '\t':
          case '\n':
          case '\r':
            *wp = '\0';
            *tp++ = ' ';
            tp = strrev(tp, work);
            wp = work;
            break;

          default:
            *wp++ = ch;
        }
    } while (ch != '\0' && tp < (tgt + bufsize-2));
    *tp++ = '\n';
    *tp = '\0';

    free(work);
    return tp;
}
//--------------------------------------------------------------------
