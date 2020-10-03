#ifndef STRING
#define STRING


char * createString(uint8_t );

long lengthOf(char *);

void deepCopyString(char *, char *, uint8_t );

int find(char *, char);

char * substring(char *, unsigned int, unsigned int);

char * reverseString(char *);

void reverseStringSame(char *);

unsigned char isAlphabet(char );

unsigned char isDigit(char );

unsigned char isUpper(char );

unsigned char isLower(char );

unsigned char isSpecial(char );

unsigned char isWhiteSpace(char );

unsigned char isSpace(char );

unsigned char isNewline(char );

unsigned char equals(char *, char *);

long long stringToInteger(char *);

char * integerToString(long long );

char * join(char *, char *);

char * floatToString(double ,unsigned int );

double stringToFloat(char *);

char * splitByCharacter(char *, char);

char searchString(char *,char *);

#endif
