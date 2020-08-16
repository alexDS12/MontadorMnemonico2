#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
int verificar(char cmd[]){
	if(cmd[7]=='R')
		return 1;
	else if(cmd[7]=='#')
		return 2;
	else if(cmd[7]=='@')
		return 3;
	else
		return 4;
}

int decimalBinario(char cmd[]){
	int i, j=0, x, binario;
    char aux[10];
    char temporario[9] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    for(i=8; cmd[i]; i++){
        aux[j++] = cmd[i];
    }
    aux[j] = '\0';
    x = atoi(aux);
    itoa(x, aux, 2);
    x = strlen(aux);
    
    if(x < 9){
    	for(i = x; i < 8; i++){
    		strcat(temporario, "0");
		}
		strcat(temporario, aux);
		binario = atoi(temporario);
		return binario;
	}
	   
}

const char *endRegistradores[] = {
	"00000000", "00011000", 
	"00110000", "01001000", 
	"01100000", "01111000",
	"10010000", "10101000", 
	"11000000", "11011000"
};
 
int main(){
    char cmd[20], res[25], CHAR2[10];
    int valorRegistradores[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, x, i, j;
    int numero = 0, pot = 1, reg1, reg2, binario;
    char continuar, arg1[3], arg2[10], atoi1[2], arg2Temporario[10];
    
    do{
    	puts("Informe o comando a ser realizado: ");
   	 	gets(cmd);
  	  	x = verificar(strupr(cmd));
        arg1[0] = cmd[4];
        arg1[1] = cmd[5];
        arg1[2] = '\0';
        
		j=0;
        
        if(x==1){
       	 for(i=6; cmd[i]; i++){
        		arg2[j] = cmd[i];
       		 	j++;
			}
			arg2[j] = '\0';	
		}
		else if(x==4){
			for(i=7; cmd[i]; i++){
				arg2[j] = cmd[i];
				j++;
			}
			arg2[j] = '\0';
		}
		else{
			for(i=8; cmd[i]; i++){
        		arg2[j] = cmd[i];
       		 	j++;
			}
			arg2[j] = '\0';	
		}
		atoi1[0] = arg1[1];
		atoi1[1] = '\0';
		reg1 = atoi(atoi1);
		if(x==2 || x==3){
			if(x==2)
				strcpy(arg2Temporario, arg2);
			else{
				atoi1[0] = arg2[1];
				atoi1[1] = '\0';
				reg2 = atoi(atoi1);
			}		
		}
				
		else{
			atoi1[0] = arg2[2];
			atoi1[1] = '\0';
			reg2 = atoi(atoi1);
		}
		
		if(x==1){
			printf("\nSera adicionado o valor de %s em %s", arg2, arg1);
       		strcpy(res, "00000000");
       		strcat(res, endRegistradores[reg1]);
    		strcat(res, endRegistradores[reg2]);	
			valorRegistradores[reg1]+= valorRegistradores[reg2];	    	
		}
		
		else if(x==2){
			printf("\nSera adicionado um valor decimal em %s", arg1);
    	    strcpy(res, "00000010");	
			strcat(res, endRegistradores[reg1]);
    	    binario = decimalBinario(cmd);
    	    //CHAR2 = itoa(binario, bin, 10);
			strcat(res, binario);
    	    reg2 = atoi(arg2Temporario);
			valorRegistradores[reg1]+= reg2;
		}
		
		else if(x==3){
			printf("\nSera adicionado o endereco de %s em %s", arg2, arg1);
			strcpy(res, "00000001");
			strcat(res, endRegistradores[reg1]);
			strcat(res, endRegistradores[reg2]);
			binario = atoi(endRegistradores[reg2]);
			
			pot = 1;
			//numero =0;
			
			do{
				numero+= (binario % 10) * pot;
				pot *= 2;
				binario /= 10;
			}while(binario != 0);			
			valorRegistradores[reg1] += numero;
		}
		
		else if(x==4){
			printf("\nSera adicionado um valor binario em %s", arg1);
			reg2 = atoi(arg2);
			sprintf(arg2, "%08d", reg2);
			
			if(strlen(arg2)>8){
				printf("\nSera necessario dois comandos!");
				strcpy(res, "00000011");
				strcpy(res, "00000000");
				strcpy(res, "XXXXXXXX");
				printf("\nO comando realizado foi: %s", res);
				strcpy(res, "0000000000000000");
				strcat(res, arg2);
				//valorRegistradores[reg1]+= ;
				
			}
			
			else{
				strcpy(res, "00000011");
				strcat(res, endRegistradores[reg1]);
				strcat(res, arg2);
				valorRegistradores[reg1]+= reg2; //TRANSFORMAR O BINÁRIO EM DECIMAL
   			}
				
						
		}
		
		printf("\n\nO comando realizado foi: %s", res);
		
		printf("\nValores dos registradores");
		
		for(i=0; i<10; i++){
			printf("\nR%d: %d ", i, valorRegistradores[i]);
		}
		do{
			printf("\nGostaria de continuar? <S/N> ");
    		scanf("%c", &continuar);
			fflush(stdin);
	 	
		 }while(toupper(continuar)!='S' && toupper(continuar)!='N');
    	
	}while(toupper(continuar) == 'S');
	
	return 0;
}
