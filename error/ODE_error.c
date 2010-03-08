#include "ODE_error.h"

/* TODO:
 * [ ] error identifiers
 * [ ] error mesages
 * [ ] exiting the program
 */


/** 
 * This function prints the reason for the error and the file and
 * line number.
 * 
 * @param msg the reason for the error message
 * @param file file in which error has occured
 * @param line line number of error occurence
 * @param errno error identifier
 */
void ODE_error ( const char * msg, const char * file, int line, const int errno )
{
  printf(" ERROR: %s \n in file %s on line %d\n Error no. %d\n",
         msg,  file, line, errno);
}

