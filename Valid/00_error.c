#include "fix.h"

int		print_error(int error)
{
	if (error == NO_ARG)
		printf("Error : Argument does not exists.\n");
	else if (error == WRONG_NAME)
		printf("Error : Wrong file name. Please check your file name.\n");
	else if (error == WRONG_OPT)
		printf("Error : Unacceptable option. Using '--save' option.\n");
	else if (error == PARSING_ERR)
		printf("Error : Parsing error. Please check your map file.\n");
	else if (error == OPEN_ERR)
		printf("Error : Can't open file. Please check your file name or directory.\n");
	return (-1);
}
