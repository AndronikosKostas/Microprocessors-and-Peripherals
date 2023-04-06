#include <stdio.h>
#include <stdlib.h>
#include <uart.h>


static char input[100] = {'\0'};

static uint8_t table[26] = {10, 42, 12, 21, 7, 5, 67, 48, 69, 2, 36, 3, 19, 1, 14, 51, 71, 8, 26, 54, 75, 15, 6, 59, 13, 25};
static char hash_string[9];


extern int hash(char *s, uint8_t *table);
extern int factorial(char *s);


	

int main()
{
	printf("enter string : ");
	//
	scanf("%s", input);
	//
	
	int hash_num = 0;
	hash_num = hash(input, table);
	printf("hash number = %u\n",hash_num);
	// convert hash_number to string
	sprintf(hash_string, "%d", hash_num);
	
	printf("factorial = %d", factorial(hash_string));
	
	return 0;
}




/*
int hash(char *s, uint8_t *t)
{
	int hashResult = 0;
	int i = 0;
	while(s[i] != '\0')
	{
		if(s[i] >= 97 && s[i] <= 122)  // a - z
		{
			hashResult += t[s[i] - 97]; 
		}
		else if(s[i] >= 48 && s[i] <= 57)
		{
			hashResult -= s[i] - 48;
		}
		
		i++;

	}
	
	return hashResult;
}

*/


/*
int factorial_(char *s)
{
	int sum = 0;
	int i = 0;
	int sd = 0 ; 
	int factorial = 1; 
	while(s[i] != '\0')
	{
		sum += s[i] - 48 ; // convert from ascii
		if(sum >= 10)    
		{  
			// sum belongs to [10,18]
			// first digit is always 1
			sd = sum - 10; // calculate the second digit
			sum = 1 + sd;  // calculate the sum
		}
		i++;
	}
	  
    if(sum < 0)
		{
			factorial = 0;
		}
		// we will calculate the factorial of the sum
    while(sum > 1){
        factorial *= sum; // (1*n)(n-1)....
        sum -= 1;
    }
	return factorial;
}



////////  SECOND IMPLEMENTATION /////////////////


int findFactorial(int x){
    
    int new_hash = x;
    // counter finds the number of hash digits
		// by dividing with 10
    while (new_hash >= 10){
        new_hash = 0;
        int counter = 0;
       
				int temp = x; // temp = hashNum

        while(x >= 1){
            x = x/10;
            counter ++;
        }

        // find the max divider
				int divider = 1;
        for(int j = 0; j < counter ; j++)
            divider *= 10;
				
        while(divider >= 1){
            new_hash += temp / divider; // add the integral part // 127 / 100 = 1, 27 / 10 = 2 ...
            temp = temp % divider;			// 127 % 100 = 27 , 27 % 10 = 7 ... 
            divider /= 10;
        }
        x = new_hash;
    }
		printf("\n");
    printf("New hash: %d", new_hash);
		
		int factorial = 1;
		// if new_hash < 0 factorial does not exist... 
    if (new_hash <= 0)
        factorial = 0;
	
		
    while(new_hash >= 1){
        factorial *= new_hash; // (1 * n)(n-1)....
        new_hash -= 1;
    }
    return factorial;
}


*/




