/*
Input char from Keypad 4*4
{
{1,2,3,A},
{4,5,6,B},
{7,8,9,C},
{*,0,#,D}
}
A: valeur canal
B: set canal
C: clear all
D/E: mettre à une valeur plusieurs canaux conjoints/selection de plusieurs canaux disjoints(jusqu'à 16)
*/
#include <stdio.h>
#include <stdlib.h>


// gestion caractère reçus

char c = '0';
char x = '0';
int value = 0;
int channel = 0;
typedef enum {normal, thru, add} mode;
mode state = normal;

int i, j = 0;

//Def fonction
void gestionChar(char c);


//déclarations pour modes Add et thru
		int tab[16] = {0}; // contient des n° de canal
		int iAdd = 0; // increment pour tableau
		int jAdd = 0; // increment pour boucles
		int iThru = 0;
		int jThru = 0;

int main(){
	while(c!='X'){
		scanf("%c", &c);
		gestionChar(c);
	}
}


void gestionChar(char c){
	/* code */
	//gestion des chiffres
	if ((c>='0') && (c<='9')) {
        value = 10*value + c - '0';
    }

    //fonction clear all
	else if (c=='C'){
		state = normal;
		//DmxSimple.clear();
		printf("clear all");
		for(i=0; i<5; ++i){
			printf("channel %d value 0\n", i);
		}
		channel = 0;
		value = 0;
		for(i=0; i<16; ++i){
			tab[i] =0;
		}
	}

	// set state THRU
	else if (c=='D'){
		printf("state THRU\n");
		state = thru;
		iThru = 0;
		value = 0;
	}

	//set state ADD
	else if (c=='E'){
		printf("state ADD\n");
		state = add;
		iAdd = 0;
		value = 0;
	}

    else{
 	switch(state){
		//state normal
		case normal :
			if(c=='A'){
				channel = value;
				value = 0;
			}
			else if (c=='B'){
				//DmxSimple.write(channel, value);
				printf("channel %d value %d\n", channel, value);
				value = 0;
			}
			else if (c=='+'){
				//DmxSimple.write(channel, 0);
				printf("channel %d value 0\n", channel);
				channel += 1;
				//DmxSimple.write(channel, 255);
				printf("channel %d value 255\n", channel);
			}
			else if (c=='-'){
				//DmxSimple.write(channel, 0);
				printf("channel %d value 0\n", channel);
				channel -= 1;
				//DmxSimple.write(channel, 255);
				printf("channel %d value 255\n", channel);
			}
			break;

		//state thru
		case thru :
			if(c=='A'){
				tab[1] = value;
				value = 0;
			}
			else if (c=='B'){
				if (tab[0]<=tab[1]){
					for(iThru = tab[0]; iThru<= tab[1]; ++iThru){
						///!!!! à modifier pour que le DMX envoi aussi aux premiers canaux et
						///pas seulement à partir de tab[0]
						//DmxSimple.write(iThru, value);
						printf("channel %d value %d\n", iThru, value);
					}
				}
				else{
					for(iThru = tab[1]; iThru < tab[0]; ++iThru){
						///!!!! à modifier pour que le DMX envoi aussi aux premiers canaux et
						///pas seulement à partir de tab[1]
						//DmxSimple.write(iThru, value);
						printf("channel %d value %d\n", iThru, value);
					}
				}
			}

			else if (c =='+'){
				tab[0] = value;
				value = 0;
			}
			else if (c =='-'){
			/* code */
			}
			break;

		/*Mode ADD : permet d'Affecter une valeur à plusieurs canaux
		procédure : E - n° canal - +/A - n° canal - +/A - valeur - B
		*/
		case add :

			if(c=='A'){
				tab[iAdd] = value;
				value = 0;
				if(iAdd<16){
					++iAdd;
				}
			}
			else if (c=='B'){
				for(jAdd=0; jAdd<iAdd; ++jAdd){
					//DmxSimple.write(tab[jAdd], value);
					printf("channel %d value %d\n", tab[jAdd], value);
				}
				value = 0;
			}
			else if (c=='+'){
				tab[iAdd] = value;
				value = 0;
				if(iAdd<16){
					++iAdd;
				}
			}
			else if (c=='-'){
				/* code */
			}
			break;   	
    			}
    }
}
