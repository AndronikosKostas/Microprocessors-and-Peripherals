/*
 * input:
 *	dob -> date of birth
 *	i_str -> initial string
 *	f_str -> final string (output)
 *
 * restrictions:
 *	- the max length of the output is 100 chars (including the string termination character)
*/
__asm void transform_str( const char* dob, const char* i_str, const char* f_str )
{
	// Define names for used registers
	dob RN R0
	input_str RN R1
	output_str RN R2
	curr_char RN R3
	day RN R4
	month_str RN R5
	year_str RN R6

	// Initial setup
	// Split dob to parts
	LDRM R4, [dob] // Load first digit of day
	SUB R4, R4, #'0' // Cast char to int
	LDRM R5, [dob, #1] // Load second digit of day
	SUB R5, R5, #'0'
	MOV R6, #10
	MULA day, R4, R6, R5 // 10 * first_digit + second_digit

	ADD month_str,  dob, 4
	ADD year_str, dob, 6

	// Start looping over the characters of the input string
char_loop
	LDRB curr_char, [input_str]
	CMP curr_char, #'0' - 1
	STR curr_charr, [output_str]
	BLS next_char // Character is lower than '0' in ASCII

	CMP curr_charr, #'9'
	BLS handle_num // char lower or equal to 9 in ASCII

	CMP curr_char, #'A' - 1
	STR curr_char, [output_str]
	BLS next_char // lower than A

   CMP curr_cahr, #'Z'
   BLS handle_caps // <= to Z

	CMP curr_char, #'a' - 1
	STR curr_char, [output_str]
	BLS next_char // lower than a

	CMP curr_char, #'z'
	STR curr_char, [output_str]
	BHI next_char // >z

	B handle_low // a <= char <= z

handle_num
	SUB R7, curr_char, #'0'
	ADD R7, R7, day
	CMP R7, #10
	BGE two_digit_res

	// Is < 10
	ADD R7, R7, #'0'
	STR R7, [output_str]
	B next_char

two_digit_res
	MOV R8, #10
	UDIV R8, R7, R8 // integer divide by 10 (hopefully)
	ADD R9, R8, #'0' // cast to str
	STR R9, [output_str]
	SUB R7, R7, R8 // gets second digit
	ADD R7, R7, #'0' // cast to str
	STR R7, [output_str]
	B next_char

handle_caps
	LDRB R7, [year]
	STR R7, [output_str]
	ADD output_str, output_str, #1
	LDRB R7, [year, #1]
	STR R7, [output_str]
	B next_char

handle_low
	LDRB R7, [month]
	STR R7, [output_str]
	ADD output_str, output_str, #1
	LDRB R7, [month, #1]
	STR R7, [output_str]
	B next_char

next_char
	ADD input_str, input_str, #1 // inc input char pointer
	ADD output_str, output_str, #1 // and output
	CMP curr_charr, #0
	BNE char_loop // has more chars
	MOV R7, #0
	STR R7, [output_str] // terminate string
	BX lr
}

int main( void )
{
	static const char DOB[] = "01-01-01";
	static const INPUT_STRING[] = "!@asdf ASDF 12345{;";
	char output_string[100] = "";

	printf("%s", output_string);

	return 0;
}