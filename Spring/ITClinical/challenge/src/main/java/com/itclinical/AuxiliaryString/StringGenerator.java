package com.itclinical.AuxiliaryString;

import java.util.Random;

public class StringGenerator {
    
    
    public String Generate_Alpha_String(int tamanho, int probabilidade){
        String resp ="";
		Random ran = new Random();		
		for(int i=0;i<tamanho;++i){
        	char mychar = (char) ran.nextInt(26); //26 letras [0,26[
			mychar +=65; // estou na tabela ascii com letra maiuscula
			if(ran.nextInt(101)>probabilidade){
				mychar = Character.toLowerCase(mychar);
			}
			resp+=Character.toString(mychar);
		}
        return resp;
    }


    public String Generate_Num_String(int tamanho){
		String resp ="";
		Random ran = new Random();		
		for(int i=0;i<tamanho;++i){
        	resp+=Integer.toString(ran.nextInt(10)); //[0,9[
		}
        return resp;
	}


    public String Generate_AlphaNum_String(int tamanho, int probabilidade){
		String resp ="";
		Random ran = new Random();		
		for(int i=0;i<tamanho;++i){
        	char mychar = (char) ran.nextInt(36); //26 letras [0,26[ +10 [0,9[
			if(mychar>25){ // numero
				resp+=Integer.toString(35-mychar);
			}
			else{ //letra
				mychar +=65; // estou na tabela ascii com letra maiuscula
				if(ran.nextInt(101)>probabilidade){
					mychar = Character.toLowerCase(mychar);
				}
				resp+=Character.toString(mychar);
			}
		}
        return resp;
	}
    
}
