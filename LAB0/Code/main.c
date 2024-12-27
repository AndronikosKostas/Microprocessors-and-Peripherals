#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <uart.h>

int main(){
	
	
	uart_init(115200);
	uart_enable();
	
	char AEM[4];
	char ar[15] = "hello world";
	char vas[4] = "9755";
	char andr[4] = "9754";
	printf("Enter AEM: ");
	
	scanf("%s", AEM);
	
		
	if(strcmp(vas,AEM) == 1 || strcmp(andr,AEM) == 1 ){
		uart_print(ar);
		
	}
	

	return 0;
	
}