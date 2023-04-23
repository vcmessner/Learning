package com;

import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Random;

import org.junit.jupiter.api.RepeatedTest;

public class DeprecatedTests {

    /* tests that Shouldn't be in the commom test factory anymore
     * this class exists for documentation and for regression
     */
    

     @RepeatedTest (1000)
	void generate_random_alphanum_string(){
		int probabilidade = 50; // probabilidade de ser maiuscula
		int tamanho =10;
		String resp ="";
		Random ran = new Random();		
		for(int i=0;i<tamanho;++i){
        	char mychar = (char) ran.nextInt(36); //26 letras [0,26[ +10 [0,9[]
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
		assertTrue(resp.matches("[A-Za-z0-9]+"));
	}

    @RepeatedTest (1000)
	void generate_random_num_string(){
		int probabilidade =50;
		int tamanho =10;
		String resp ="";
		Random ran = new Random();
		if(ran.nextInt(101)>probabilidade){
			resp+="-";
		}
		for(int i=0;i<tamanho;++i){
        	resp+=Integer.toString(ran.nextInt(10)); //[0,9[		
		}
		assertTrue(resp.matches("^-?[0-9]+"));
	}

    @RepeatedTest (1000)
	void generate_random_alpha_string(){
		int probabilidade = 50; // probabilidade de ser maiuscula
		int tamanho =10;
		String resp ="";
		Random ran = new Random();		
		for(int i=0;i<tamanho;++i){
        	char mychar = (char) ran.nextInt(26); //26 letras [0,26[
			mychar +=65; // estou na tabela ascii com letra maiuscula
			if(ran.nextInt(101)>probabilidade){
				mychar = Character.toLowerCase(mychar);
			}
			resp+=Character.toString(mychar);
			//resp+= String.valueOf(mychar);
		}
		assertTrue(resp.matches("[a-zA-Z]+"));
		}


    
}
