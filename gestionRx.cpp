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
D: mettre à une valeur plusieurs canaux conjoints/selection de plusieurs canaux disjoints(jusqu'à 16)
*/



// gestion caractère reçus

int c =0;
char x = '0';
int value = 0;
int channel = 0;
enum mode {normal, thru, add};
mode state == normal;

int i, j = 0;


//déclarations pour modes Add et thru
		int t[16] = {0}; // contient des n° de canal
		int iAdd = 0; // increment pour tableau
		int jAdd = 0; // increment pour boucles
		int iThru = 0;
		int jThru = 0;

int int main(int argc, char const *argv[])
{
	/* code */
	//gestion des chiffres
	if ((c>='0') && (c<='9')) {
        value = 10*value + c - '0';
    }

    //fonction clear all
	else if (c=='C'){
		mode = normal;
		DmxSimple.clear();
		channel = 0;
		value = 0;
		for(i=0; i<=16; ++i){
			t[i] =0;
		}
	}

	// set mode THRU
	else if (c=='D'){
		mode = thru;
		iThru = 0;
	}

	//set mode ADD
	else if (c=='E'){
		mode = add;
		iAdd = 0;
	}

    else{
 	switch(mode):
		//mode normal
		case normal :
			if(c=='A'){
				channel = value;
			}
			else if (c=='B'){
				DmxSimple.write(channel, value);
			}
			else if (c=='+'){
				DmxSimple.write(channel, 0);
				channel += 1;
				DmxSimple.write(channel, 255);
			}
			else if (c=='-'){
				DmxSimple.write(channel, 0);
				channel -= 1;
				DmxSimple.write(channel, 255);
			}
			break;

		//mode thru
		case thru :
			if(c=='A'){
				tab[1] = value;
			}
			else if (c=='B'){
				if (tab[0]<=tab[1]){
					for(iThru = tab[0]; iThru<= tab[1]; ++iThru){
						///!!!! à modifier pour que le DMX envoi aussi aux premiers canaux et
						///pas seulement à partir de tab[0]
						DmxSimple.write(iThru, value);
					}
				}
				else{
					for(iThru = tab[1]; iThru < tab[0]; ++iThru){
						///!!!! à modifier pour que le DMX envoi aussi aux premiers canaux et
						///pas seulement à partir de tab[1]
						DmxSimple.write(iThru, value);
				}
			}

			else if (c=='+'){
				tab[0] = value;
			}
			else if (c=='-'){
			/* code */
			}
			break;

/*Mode ADD : permet d'Affecter une valeur à plusieurs canaux
procédure : E - n° canal - +/A - n° canal - +/A - valeur - B

*/
		case add :

			if(c=='A'){
				tab[iAdd] = value;
				if(iAdd<16){
					++iAdd;
				}
			}
			else if (c=='B'){
				for(jAdd=0; jAdd<=iAdd; ++jAdd){
					DmxSimple.write(tab[jAdd], value);
				}
			}
			else if (c=='+'){
				tab[iAdd] = value;
				if(iAdd<16){
					++iAdd;
				}
			}
			else if (c=='-'){
				/* code */
			}
			break;   	
    			}

	return 0;
}
