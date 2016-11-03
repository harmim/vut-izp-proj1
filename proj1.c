/**
 * @name proj1
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define PRINT_ERR(s, ...) fprintf(stderr,  s "\n", __VA_ARGS__)

/**
 * constant string - help
 */
const char usage_string[] =
	"  Converting binary input to text:\n"
	"	proj1 [-s M] [-n N] (the output format is a sequence of lines,\n"
	"		where each line describes a series of 16 bytes from the input)\n"
	"		[-s M]	(defines which address should begin listing)\n"
	"		[-n N]	(the maximum length of input bytes for processing)\n"
	"	proj1 -x	(input data are converted into hexa form to one line)\n"
	"	proj1 -S N	(print a sequence of binary input, which look like a\n"
	"			string of lenght greater than or equal to N)\n"
	"\n"
	"  Convert text input to binary:\n"
	"	proj1 -r	(expects the input sequence of hexadecimal digits\n"
	"			and convert these into a binary format)";


/**
 * compare two strings if they are equal
 *
 * @param s1 first string
 * @param s2 second string
 * @return true if s1 and s2 are equal, flase otherwise
 */
bool str_eq(const char *s1, const char *s2)
{
	// check if s1 and s2 are not NULL pointers and if theire values are equal
	while (s1 != NULL && s2 != NULL && *s1 == *s2) {
		// or *s2 == '\0' - end of string, s1 and s2 are equal
		if (*s1 == '\0') {
			return true;
		}
		s1++;
		s2++;
	}

	return false;
}


/**
 * print one line describeing a series of 16 bytes
 * format of this line is described in annotation of function binary_to_text whence it is called
 *
 * @see binary_to_text
 * @param char_values array of last 16 chars
 * @param address address of last byte
 * @param skip number of chars that was skipped or -1 for undefined 
 */
void print_binary_to_text_line(int *char_values, const int address, const int skip)
{
	// print this line only if address is not 0 and if first char is not empty
	if (address != 0 && char_values[0] != 0) {
		int rm16 = address % 16, i = 0;
		// print address of first byte in this line to stdout
		printf("%08x  ", address + (skip != -1 ? skip : 0) - (rm16 == 0 ? 16 : rm16));

		// print hexa value of each byte or space if there is no one to stdout
		for (i = 0; i < 16; i++) {
			if (char_values[i] == 0) {
				printf("   ");
			} else {
				printf("%02x ", char_values[i]);
			}

			// two spaces after 8. char
			if (i == 7) {
				putchar(' ');
			}
		}

		// print printable from of each byte or . (dot) if it is no printale or space if there is no one to stdout
		// at last erase array for last 16 chars (char_values)
		printf(" |");
		for (i = 0; i < 16; i++) {
			if (isprint(char_values[i])) {
				putchar(char_values[i]);
			} else if (char_values[i] == 0) {
				putchar(' ');
			} else {
				putchar('.');
			}
			char_values[i] = 0;
		}
		printf("|\n");
	}
}


/**
 * process input binary data from stdin (without arguments)
 * the output format is a sequence of lines where where each line describes a series of 16 bytes from the input
 * each line is in format: AAAAAAAA  xx xx xx xx xx xx xx xx  xx xx xx xx xx xx xx xx  |bbbbbbbbbbbbbbbb|
 * - AAAAAAAA address of first byte in each series (it is hexa number, first byte is 00000000)
 * - xx is hexa value of each byte
 * - b is printable form of each byte, if byte is not printable, prints . (dot)
 * if series contains less then 16 bytes, instandof missing xx values it prints spaces
 *
 * @param skip number of chars to skip or -1 when it is undefined (-s)
 * @param number_of_chars maximum length of input bytes to process or -1 when it is undefined (-n)
 * @return true if input data was processed successfully, false otherwise
 */
bool binary_to_text(const int skip, const int number_of_chars)
{
	int char_value, address = 0, char_values[16] = {0};
	bool skipped = false;

	while ((char_value = getchar()) != EOF) {
		// check if it was already skipped or skip is undefined argument or address is equal skip
		if (skipped || skip == -1 || address == skip) {
			// if address is equal skip then skip all previous bytes, set address to 0 and flag skipped to true
			if (address == skip) {
				address = 0;
				skipped = true;
			}

			// array for 16 bytes is full, so print this line to stdout
			if (address % 16 == 0) {
				print_binary_to_text_line(char_values, address, skip);
			}

			// add char from stdin to array for actual row to index 0-15
			char_values[address % 16] = char_value;

			// if argument number_of_chars is defined and its value is greater than or equal to position of last
			// byte, stop read from stdin
			if (number_of_chars != -1 && address + 1 >= number_of_chars) {
				break;
			}
		}
		address++;
	}
	// print last series to stdout, if there are any chars
	print_binary_to_text_line(char_values, address, skip);

	return true;
}


/**
 * process input binary data from stdin (-x)
 * input data are converted into hexadecimal form to one line
 * each output byte is two digits hexadeciaml number
 *
 * @return true if input data was processed successfully, false otherwise
 */
bool binary_to_text_one_line()
{
	int char_value;

	// print each byte as two digits hexadecimal number to stdout
	while ((char_value = getchar()) != EOF) {
		printf("%02x", char_value);
	}
	putchar('\n');

	return true;
}


/**
 * process input binary data from stdin (-S)
 * prints a sequence of binary input, which look like a string
 * each string is print to new line
 * string is sequence of printable and blank chars
 *
 * @param lenght output string must be greater than or equal to this lenght
 * @return true if input data was processed successfully, false otherwise
 */
bool binary_to_text_string(const int lenght)
{
	bool print_new_line = false;
	// inicialize array of lenght from argument and fill it with zeros
	int char_values[lenght], char_value, i, j;
	for (i = 0; i < lenght; i++) {
		char_values[i] = 0;
	}

	// iterate overs chars from stdin and count them with i
	for (i = 0; (char_value = getchar()) != EOF; i++) {
		// at first n chars (lenght) are stored to array char_values if in array there are
		// enough chars, then we can print it to stdout and then print other chars one by one
		// if not, we can throw away chars for this line and continue with next line
		if (i + 1 < lenght) {
			// if char is print or is blank, store it to array
			// otherwise erase the array and set index to -1, so next iteration starts with the new line
			if (isprint(char_value) || isblank(char_value)) {
				char_values[i] = char_value;
			} else {
				for (j = 0; j < lenght; j++) {
					char_values[j] = 0;
				}
				i = -1;
			}
			print_new_line = false;
		} else {
			// now we have crowded array with previous chars, from now we can print everything on this line
			// if is print or if it is blank
			if (isprint(char_value) || isblank(char_value)) {
				// print everything previous chars from array to stdout and erase this array
				for (j = 0; j < lenght; j++) {
					if (char_values[j] == 0) {
						break;
					}
					putchar(char_values[j]);
					char_values[j] = 0;
				}
				// print current char from stdin to stdout
				putchar(char_value);
				print_new_line = true;
			} else {
				if (print_new_line) {
					putchar('\n');
				}

				// erase the array and set index to -1, so next iteration starts with the new line
				for (j = 0; j < lenght; j++) {
					char_values[j] = 0;
				}
				i = -1;
			}
		}
	}

	return true;
}


/**
 * process input text data from stdin (-r)
 * expects the input sequence of hexadecimal digits and convert these into a binary format
 * whiite-space chars are ignored
 *
 * @return true if input data was processed successfully, false otherwise
 */
bool text_to_binary()
{
	int char_value, i = 0, first_byte = -1;
	char byte_string[3] = {'\0'};

	while ((char_value = getchar()) != EOF) {
		// whiite-space chars are ignored
		if (isspace(char_value)) {
			continue;
		}
		// if current char is not hexadigit, print error to stderr and return false
		if ( ! isxdigit(char_value)) {
			PRINT_ERR("Char %c is not hexadecimal digit.", char_value);
			return false;
		}
		// if number of processed chars is odd (find out using bitwise AND operator)
		// then store char to first_byte
		if (++i & 1) {
			first_byte = char_value;
		} else {
			// if number of processed chars is even then, print whole byte to stdout converted from hexadecimal
			// then set -1 to first_byte variable
			byte_string[0] = first_byte;
			byte_string[1] = char_value;
			putchar(strtol(byte_string, (char **) NULL, 16));
			first_byte = -1;
		}
	}

	// if there is last or first single byte, print it to stdout converted from hexadecimal
	if (first_byte != -1) {
		byte_string[0] = first_byte;
		byte_string[1] = '\0';
		putchar(strtol(byte_string, (char **) NULL, 16));
	}

	return true;
}


/**
 * converts value of argument in string format to int
 * if in value there is non-convertible part, print it to stderr
 *
 * @param value value of argument in string format (from argv)
 * @param arg name of argument that value belongs to
 * @return converted int value or -1 if in value there is non-convertible part
 */
int value_of_argument_to_int(const char *value, const char arg) 
{
	char *endptr = NULL;
	int number = strtol(value, &endptr, 10);
	if (*endptr) {
		PRINT_ERR("Value of argument -%c must be number but there is non-convertible part: %s.", arg, endptr);
		return -1;
	}

	return number;
}


/**
 * process intput data from stdin according to input arguments
 *
 * @param argc count of program arguments
 * @param argv program arguments
 * @param help true if usage string should be listed, false otherwise
 * @return true if input data was processed successfully, false otherwise
 */
bool process_input_data(const int argc, const char *argv[], bool *help)
{
	if (argc > 1) {
		bool option_r = str_eq(argv[1], "-r"), option_x = str_eq(argv[1], "-x");
		// option -r or -x
		if (option_r || option_x) {
			// if any other arguments after -r or -x are passed, it is incorrect
			if (argc != 2) {
				*help = true;
				return true;
			}

			return option_r ? text_to_binary() : binary_to_text_one_line();
		}

		// option -S
		if (str_eq(argv[1], "-S")) {
			// argument -S must be followed by number N
			if (argc != 3) {
				*help = true;
				return true;
			}

			// convert argument to int and do validation
			int number;
			if ((number = value_of_argument_to_int(argv[2], 'S')) == -1) {
				return false;
			}
			if (number <= 0 || number >= 200) {
				PRINT_ERR("Vlue of argument -S must be number in range (0;200), given %i.", number);
				return false;
			}

			return binary_to_text_string(number);
		}

		bool option_s = str_eq(argv[1], "-s"), option_n = str_eq(argv[1], "-n");
		// optional arguments -s or -n or both
		if (option_s || option_n) {
			// argument -s and -n must be followed by number
			if (argc == 2) {
				*help = true;
				return true;
			}

			// convert argument to int and do validation
			int number;
			if ((number = value_of_argument_to_int(argv[2], option_s ? 's' : 'n')) == -1) {
				return false;
			}
			if (number < 0) {
				PRINT_ERR("Value of argument -%c must be number greater than 0, given %i.", option_s ? 's' : 'n', number);
				return false;
			}

			// there is not other arguments
			if (argc == 3) {
				return binary_to_text(option_s ? number : -1, option_n ? number : -1);
			}

			bool option2_s = str_eq(argv[3], "-s"), option2_n = str_eq(argv[3], "-n");
			// one of arguments -s or -n was entered twice or there is any other unknown argument
			// second argument -s or -n must be followed by number too
			if ((option_s && option2_s) || (option_n && option2_n) || argc != 5 || ! (option2_n || option2_s)) {
				*help = true;
				return true;
			}

			// convert argument to int and do validation
			int number2;
			if ((number2 = value_of_argument_to_int(argv[4], option2_s ? 's' : 'n')) == -1) {
				return false;
			}
			if (number2 < 0) {
				PRINT_ERR("Value of argument -%c must be number greater than 0, given %i.", option2_s ? 's' : 'n', number2);
				return false;
			}

			return binary_to_text(
					option_s ? number : option2_s ? number2 : -1,
					option_n ? number : option2_n ? number2 : -1
				);
		}

		// unknown option
		*help = true;
		return true;
	}

	// without arguments
	return binary_to_text(-1, -1);
}


int main(const int argc, const char *argv[])
{
	// start processing input data
	bool help = false, result = process_input_data(argc, argv, &help);
	if (help) {
		// to be listed help/usage string
		printf("usage:\n%s\n", usage_string);
	}
	// return value of this program (of this main function)
	// depends on return value of function process_input_data
	return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
