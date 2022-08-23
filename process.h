#ifndef _PROCESS_
#define _PROCESS_
#include<unistd.h>
#include<stdlib.h>

char *strrev(char *tgt, char *src);
char *back_words(char *tgt, char *src, size_t bufsize);

#define process back_words

#endif /*_PROCESS_ */
