#include <stdlib.h>
#include "String.h"

#define MAX_STRING 50

/*
 * The _STRING array will be used to store the output from functions
 * This has been used to avoid the problems involved in dynamic allocation of strings -
 * 1. every time allocation of new memory will consume too much time
 * 2. C does not support automatic garbage collection which may lead to over growth of heap segment and thus, freezing of micro controller
 */
static char _STRING[MAX_STRING]={0};


/*
 * DESCRIPTION - performs dynamic memory allocation for a character string of length 'l'.
 * The function allocates l+1 memory spaces, l for the actual string and 1 for the end character '\0'.
 * The function also initializes all the elements with decimal 1.
 * The function also places the end character '\0' at the last position of the memory
 *
 * PARAMETER-
 * 1. 'l' the length of required string. This length is the number of actual characters required for
 * in string. The function automatically increases the allocation to one more than this to accommodate the end character.
 *
 * RETURNS-
 * The pointer to the first position of the string.
 *
 * NOTE-
 * The function returns a dynamically allocated string. C will not perform automatic garbage collection for it.
 */
char * createString(uint8_t l)
{
	// memory for l+1 elements is requested
	char * _string=(char *)malloc(sizeof(char)*(l+1));
	if(_string==NULL) return NULL;
	for(uint8_t x=0;x<l;x++)
	{
		*(_string+x)=1;
	}
	*(_string+l)='\0';
	return _string;
}

/*
 * DESCRIPTION - This function counts the number of characters in a string excluding the end character.
 *
 * PARAMETERS-
 * 1. STR - the pointer to the first position of the string
 *
 * RETURNS-
 * the length of the string
 *
 * NOTE:
 * YOU MAY PASS A CONSTAN STRING AS THE PARAMETER AS THE FUNCTION DOES NOT NEED WRITE PERMISSIONS ON IT
 * _STRING MAY BE PASSED AS THE PARAMETER
 */
long lengthOf(char * STR)
{
	long length=0;
	while( (*STR) != '\0' )
	{
		length+=1;
		STR+=1;
	}
	return length;
}

/*
 * DESCRIPTION - This function performs a deep between tow string str1 and str2.
 * In shallow copy operation the pointers are copied which leads two pointer to the same memory location.
 * In deep copy the actual characters are copied from str1 string to str2 string.
 * If the source string is larger than the target string then, only a part of it is copied into the target.
 *
 * PARAMETERS-
 * 1. str1 - pointer to source string
 * 2. str2 - pointer to target string
 * 3. num_chars - number of character entries in the second string except the end character
 *
 * RETURNS-
 * NOTHING
 *
 * NOTE:
 * YOU MUST NOT PASS A CONSTANT STRING AS THE SECOND PARAMETER AS THE FUNCTION NEEEDS WRITE PERMISSIONS ON IT
 * _STRING MAY BE PASSED TO THE FUNCTION AS ANY ONE THE PARAMETERS
 */
void deepCopyString(char * str1, char * str2, uint8_t num_chars)
{

	char flag=0;
	for(unsigned int x=0;x<num_chars;x++)
	{
		if( *(str1+x) != '\0')
			*(str2+x)=*(str1+x);
		else
		{
			*(str2+x)='\0';
			flag=1;
			break;
		}

	}
	if(!flag)
		*(str2+num_chars)='\0';
}


/*
 * DESCRIPTION : This functions finds a character in a passed string
 *
 * PARAMETERS:
 * 1. STR : this is the pointer to the input string
 * 2. ch: this the character that has to searched for
 *
 * RETURNS:
 * the index of FIRST OCCURENCE OF THE CHARACTER
 * OTHERWISE IT RETURNS -1
 *
 * NOTE:
 * YOU MAY PASS A CONSTANT STRING AS THE FIRST PARAMETER AS THE FUNCTION DOES NOT NEED WRITE PERMISSION ON THE STRING
 * _STRING MAY BE PASSED TO THE FUNCTION IF REQUIRED
 */
int find(char *STR, char ch)
{
	int index=0;
	while(*(STR+index)!='\0')
	{
		if(*(STR+index)==ch)
			break;
		index++;
	}
	// return -1 error code is character is not found
	if(index==lengthOf(STR)) return -1;
	// if character is found then, return its index
	else return index;
}

/*
 * DESCRIPTION - This function is used to obtain a part from the original string. If the substring cannot be obtained
 * due to incorrect starting and ending index then, an empty string will be returned.
 *
 * PARAMETERS-
 * 1. STR: input string
 * 2. start: starting index
 * 3. end: ending index
 *
 * RETURNS
 * the substring as a character pointer
 *
 * NOTE:
 * YOU MAY PASS A STRING CONSTANT AS THE INPUT STRING AS THE FUNCTION DOES NOT NEED WRITE PERMISSIONS FOR ITS OPERATION
 * DO NOT PASS _STRING AS THE INPUT STRING, IT WILL LEAD TO UNEXPECTED BEHAVIOUR
 */
char * substring(char *STR, unsigned int start, unsigned int end)
{
		uint8_t _index=0;
        if( end>start && (end-start)<=lengthOf(STR) )
        {
                _index=0;
                while((_index+start)<end)
                {
                        _STRING[_index]=*(STR+_index+start);
                        _index++;
                }
                _STRING[_index]='\0';
                return _STRING;
        }
        else
        {
        	_STRING[0]='\0';
        	return _STRING;
        }
}

/*
 * DESCRIPTION: This function reverses a given string and stores the reversed string in the global variable _STRING
 *
 * PARAMETERS:
 * 1. STR: the string to be reversed
 *
 * RETURNS:
 * pointer to the _STRING array
 *
 * NOTE:
 * YOU MAY PASS A CONSTANT STRING TO THE FUNCTION AS IT DOES NOT NEED WRITE PERMISSIONS ON IT
 * DO NOT PASS _STRING AS THE INPUT AS IT WILL LEAD TO INCORRECT OUTPUT
 */
char * reverseString(char * STR)
{
	unsigned int length=lengthOf(STR);
	for( unsigned int x=0 ; x<=length-1 ; x++)
	{
		_STRING[x]=*(STR+(length-(x+1)));
	}
	_STRING[length]='\0';
	return _STRING;
}

/*
 * DESCRIPTION: This function reverses a given string and save it back in the same memory location
 *
 * PARAMETERS:
 * 1. STR: the string to be reversed
 *
 * RETURNS:
 * NOTHING
 *
 * NOTE:
 * DO NOT PASS A CONSTANT STRING AS THE PARAMTER AS WRITE PERMISSIONS ARE REQUIRED BY THE PROGRAM
 * DO NOT PASS _STRING AS THE INPUT, IT WILL LEAD TO ERRORS ANS INCORRECT OUTPUT
 */
void reverseStringSame(char * STR)
{
	reverseString(STR);
	deepCopyString(_STRING,STR,lengthOf(STR));
}

/*
 * DESCRIPTION: This function joins two character strings and saves it in the _STRING array. If the sum of number
 * of characters in both the strings is more than MAX_STRING size then, the function will return an empty string
 *
 * PARAMETERS:
 * 1. str1 : first string
 * 2. str2 : second string
 *
 * RETURNS:
 * THE POINTER TO THE _STRING ARRAY THAT CONTAINS THE JOINED STRING. IT MAY ALSO BE EMPTY IN CASE OF ANAMOLY.
 *
 * NOTE:
 * YOU MAY PASS CONTANT STRING AS INPUT AS THE FUNCTION DOES NOT NEED WRITE PERMISSIONS ON THEM
 * DO NOT PASS _STRING AS ANY OF THE INPUT
 */
char * join(char * str1, char * str2)
{
        unsigned int length= lengthOf(str1) + lengthOf(str2);

        if(length>MAX_STRING)
        {
        	_STRING[0]='\0';
        	return _STRING;
        }

        unsigned int l1=lengthOf(str1);
        for(unsigned int x=0;x<l1;x++)
        {
                _STRING[x]=*(str1+x);
        }
        for(unsigned int x=0;x<lengthOf(str2);x++)
        {
                _STRING[l1+x]=*(str2+x);
        }
        _STRING[l1+lengthOf(str2)]='\0';
        return _STRING;
}

/*
 * DESCRIPTION- This function counts the number of occurrence of a given character in a given character string.
 *
 * PARAMETERS -
 * 1. _STR : the character string
 * 2. ch : the character to be tested for
 *
 * RETURNS -
 * The number of occurrence of the character in the passed string
 *
 * NOTE-
 * YOU MAY PASS A CONSTANT STRING AS THE STRING PARAMETER AS THE FUNCTION DOES NOT NEED WRITE ACCESS TO TH STRING
 * YOU MAY PASS _STRING AS THE STRING PARAMETER, IT WILL CAUSE NO PROBLEMS
 */
uint8_t countChar(char * _STR, char ch)
{
	uint8_t count=0;
	for(uint8_t x=0; x<lengthOf(_STR); x++)
	{
		if(*(_STR+x) ==ch)
		{
			count++;
		}
	}
	return count;
}

// internal assisting function
static long multiplier(int base, unsigned int exp)
{
	long long res=1;
	for(;exp>0;exp--)
	{
		res*=base;
	}
	return res;
}

// function to check whether the passed character is an Alphabet
unsigned char isAlphabet(char ch)
{
	if( (ch>=65 && ch<=90) || (ch>=97 && ch<=122) )
		return 1;
	else
		return 0;
}

// function to check whether the passed character is a Digit
unsigned char isDigit(char ch)
{
	if( ch>=48 && ch<=57 )
		return 1;
	else
		return 0;
}

// function to check whether the passed character is an Upper Case Alphabet
unsigned char isUpper(char ch)
{
	if( ch>=65 && ch<=90 )
		return 1;
	else
		return 0;
}

// function to check whether the passed character is a Lower Case Alphabet
unsigned char isLower(char ch)
{
	if( ch>=97 && ch<=122 )
		return 1;
	else
		return 0;
}

// function to check whether the passed character is a Special Character
unsigned char isSpecial(char ch)
{
	if( isAlphabet(ch) || isDigit(ch) )
		return 0;
	else
		return 1;
}

// function to check whether the passed character is a WhiteSpace Character
unsigned char isWhiteSpace(char ch)
{
	if(ch==' ' || ch=='\n' || ch=='\t')
		return 1;
	else
		return 0;
}

// function to check whether the passed character is a space
unsigned char isSpace(char ch)
{
	if(ch==' ')
		return 1;
	else
		return 0;
}

// function to check whether the passed character is a newline character
unsigned char isNewline(char ch)
{
	if(ch=='\n')
		return 1;
	else
		return 0;
}

/*
 * DESCRIPTION: This functions test the equality of two input strings.
 *
 * PARAMETERS:
 * 1. str1: first string
 * 2. str2: second string
 *
 * RETURNS:
 * 1 if the strings are exactly same and 0 otherwise
 *
 * NOTE:
 * YOU MAY PASS CONSTANT STRINGS AS PARAMETERS AS THE FUNCTION DOES NOT NEED WRITE PERMISSIONS OVER IT
 * _STRING CAN BE PASSED AS ONE OF THE STRINGS
 */
unsigned char equals(char *str1, char*str2)
{
	if( lengthOf(str1) != lengthOf(str2) )
		return 0;
	while( (*str1) != '\0' )
	{
		if( (*str1) != (*str2) )
			return 0;
		str1+=1;
		str2+=1;
	}
	return 1;
}

/*
 * DESCRIPTION : This function converts an integer to a string and stores it in _STRING variable
 *
 * PARAMETERS:
 * 1. STR: the string to be converted to integer
 *
 * RETURNS:
 * THE CONVERTED INTEGER
 *
 * NOTE:
 * YOU MAY PASS A CONSTANT STRING
 * DO NOT PASS _STRING AS THE PARAMETER , IT WILL GIVE INCORRECT RESULTS
 */
long long stringToInteger(char * STR)
{
	unsigned int length=lengthOf(STR);
	// the reversed string will automatically saved int _STRING VARIABLE
	reverseString(STR);
	long long num=0;
	char flag=0;

	char ch;
	for(unsigned int x=0; x<=length-1; x++)
	{
		if(x>20) break;

		ch=_STRING[x];
		if(isDigit(ch))
		{
			flag=1;
			//getting the original number from ascii digit
			ch=ch-48;
			num=num+ch*multiplier(10,x);
		}
		else if(ch=='-' && flag)
		{	num*=-1;
			break;
		}
		else
			break;

	}
	// return the formed number 'num'
	return num;
}

/*
 * DESCRIPTION: this function converts a integer to string.
 *
 * PARAMETERS:
 * 1. num : the number to converted to string
 *
 * RETURNS:
 * The _STRING containing the integer string
 */
char * integerToString(long long num)
{
	char sign=0;
	if(num==0)
	{
		_STRING[0]='0';
		_STRING[1]='\0';
		return _STRING;
	}
	if(num<0)
	{
		sign=1;
		num*=-1;
	}

	uint8_t _index=0;
	char digit;

	while(num>0)
	{
		digit= (num%10) + 48;
		_STRING[_index++]=digit;
		num/=10;
	}
	if(sign)
	{
		_STRING[_index++]='-';
	}
	_STRING[_index]='\0';

	char * _temp=createString(lengthOf(_STRING));
	deepCopyString(_STRING,_temp,lengthOf(_STRING));

	reverseString(_temp);

	free(_temp);

	return _STRING;
}

/*
 * DESCRIPTION; this function converts to floating point number to a character string
 *
 * PARAMETERS:
 * 1. num - the floating point number
 * 2. precision - the number of digits after the decimal point to be included in the string output
 *
 * RETURNS:
 * The string containing the floating point number
 *
 */
char * floatToString(double num, unsigned int precision)
{
		// obtaining the integer part of the floating point number
        if(precision>20) precision=20;
        long long n=(long long)num;

        // converting the integer part to string and storing it in _STRING variable
        integerToString( n );
        // copy the integer part of floating point number to ipart string
        char * ipart=createString(lengthOf(_STRING)+1);

        deepCopyString(_STRING,ipart,lengthOf(_STRING)+1);
        *(ipart+lengthOf(_STRING))='.';

        // obtaining the fractional part of the floating point number upto the given precision
        long long fraction=(long long)((num - n)*(multiplier(10,precision)));
        if(fraction<0)  fraction*=-1;

        // converting the fractional part to string and storing it _STRING variable
        integerToString(fraction);
        // copy the fraction part of floating part number to fpart string
        char * fpart=createString(lengthOf(_STRING));

        deepCopyString(_STRING,fpart,lengthOf(_STRING));

        // joining the integer part and fraction part strings and storing them in _STRING variable
        join(ipart,fpart);

        // release the dynamically allocated memory
        free(ipart);
        free(fpart);

        // return the _STRING pointer
        return _STRING;
}

/*
 * DESCRIPTION: This function converts a floating point string to floating point number of double precision
 *
 * PARAMETRS:
 * 1. num : pointer to the floating point string
 *
 * RETURNS:
 * The floating point number obtained from the string.
 *
 * NOTE:
 * YOU MAY PASS A STRING CONSTABNT AS THE PARAMETER AS NO WRITE PERMISSION ARE REQUIRED OVER IT.
 * DO NOT PASS _STRING AS THE INTPUT STRING.
 */
double stringToFloat(char * num)
{
        int index=find(num,'.');

        if(index==-1)
                return (double)stringToInteger(num);
        else
        {
                double n=0.0;
                char flag=0;
                // integer part
                substring(num,0,index);

                char *_temp=createString(lengthOf(_STRING));
                deepCopyString(_STRING,_temp,lengthOf(_STRING));

                long long part= stringToInteger(_temp);

                if(part<0) { part*=-1; flag=1; }
                n+=(double)part;
                // fraction part
                substring(num,index+1,lengthOf(num));

                free(_temp);

                char * _temp1=createString(lengthOf(_STRING));
                deepCopyString(_STRING,_temp1,lengthOf(_STRING));

                n+= ( (double)stringToInteger(_temp1) / (double)multiplier(10,lengthOf(_temp1)) );
                if(flag) n*=-1;

                free(_temp1);

                // returning the floating point number
                return n;
        }
}

/*
 * DESCRIPTION - This function splits a given string at a given character. The break character
 * is not included in any of the child strings. The string is split at first occurrence of break
 * character.
 *
 * PARAMETERS -
 * 1. STR - pointer to string that is to be split
 * 2. ch - the break character
 *
 * RETURNS -
 * The pointer to second string obtained after splitting
 *
 * NOTE :
 * DO NOT PASS A CONSTANT STRING AS THE ORIGINAL STRING BECAUSE THE FUNCTION NEEDS WRITE ACCESS ON THE STRING
 * DO NOT PASS _STRING AS ORIGIINAL STRING OTHERWISE UNEXPECTED THINGS MAY OCCUR
 */
char * splitByCharacter(char * STR,char ch)
{
	// determining the index of first occurrence of the breaking character
	uint8_t index=find(STR,ch);
	if(find(STR,ch)==-1)
	{
		// return an empty string if the break character is not present in the passed string
		_STRING[0]='\0';
		return _STRING;
	}

	// storing the second part in _STRING variable
	substring(STR,index+1,lengthOf(STR));

	// cutting the original string
	*(STR+index)='\0';

	return _STRING;
}


/*
 * DESCRIPTION - This function determines whether the first string contains the second string in it. If
 * it does then, it returns the index at which the second string starts within the first string.
 *
 * PARAMETERS-
 * 1. STR1 - pointer to first string
 * 2. STR2 - Pointer to second string
 *
 * RETURNS -
 * <index> if the second string is contained in the first one
 * -1 otherwise
 *
 * NOTE -
 * YOU MAY PASS CONSTANT STRINGS FOR BOTH THE PARAMTERS
 * YOU MAY PASS _STRING AS ANY ONE OF THE PARAMETERS
 */
char searchString(char * STR1, char * STR2)
{
	// DETERMINE THE LENGTHS OF BOTH OF THE STRINGS
	uint8_t length1=lengthOf(STR1);
	uint8_t length2=lengthOf(STR2);

	if(length2>length1) return -1;

	for(uint8_t x=0; x<=(length1-length2); x++)
	{
		if( *(STR1+x) == *(STR2+0) )
		{
			for(uint8_t y=1; y<length2; y++)
			{
				if( *(STR1+x+y) != *(STR2+y) )
					break;
				else if(y==(length2-1))
					return x;
			}
		}
	}

	return -1;
}
