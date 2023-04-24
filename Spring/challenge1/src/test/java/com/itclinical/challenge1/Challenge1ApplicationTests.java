package com.itclinical.challenge1;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Random;

import org.junit.jupiter.api.RepeatedTest;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class Challenge1ApplicationTests {

	 @Test 
	void test_Send_Input_To_Service(){
        /*               TODO 
            Basic communication
            */
	}

    @RepeatedTest(1000)
    void test_Assert_Number_as_Integer(){
		int probabilidade =50;
		int tamanho =10;
		String resp ="";
		Random ran = new Random();
        int mynumber = ran.nextInt(1000);
		if(ran.nextInt(100)+1>probabilidade){
			resp+="-";
		}
		for(int i=0;i<tamanho;++i){
        	resp+=Integer.toString(ran.nextInt(10)); //[0,9[		
		}
		assertTrue(resp.matches("^-?[0-9]+"));
		assertFalse(resp.matches("[A-Z]+"));
		assertFalse(resp.matches("[a-z]+"));
        assertTrue(Integer.toString(mynumber).matches("^-?[0-9]+"));
        assertFalse(Integer.toString(mynumber).matches("[A-Z]+"));
		assertFalse(Integer.toString(mynumber).matches("[a-z]+"));
	}

    @Test 
    void test_Assert_N_as_Integer(){
        /*               TODO 
            Get Input Parameter N
        */

		String N="1";
        assertTrue(N.matches("^-?[0-9]+"));
		assertFalse(N.matches("[A-Z]+"));
		assertFalse(N.matches("[a-z]+"));


    }


	@RepeatedTest(1000)
    void test_Assert_String_as_LowerCaseAlpha(){
        int probabilidade = 0; // probabilidade de ser maiuscula
		int tamanho =10;
		String resp ="";
		Random ran = new Random();		
		for(int i=0;i<tamanho;++i){
			char mychar = (char) ran.nextInt(26); //26 letras [0,26[
			mychar +=65; // estou na tabela ascii com letra maiuscula
			if(ran.nextInt(100)+1>probabilidade){ //1 ao 100
				mychar = Character.toLowerCase(mychar);
			}
			resp+=Character.toString(mychar);
		}
		assertTrue(resp.matches("[a-z]+"));
		assertFalse(resp.matches("[A-Z]+"));
	}

	@RepeatedTest(1000)
    void test_Assert_String_as_LowerCaseAlphaNum(){
        int probabilidade = 0; // probabilidade de ser maiuscula
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
				if(ran.nextInt(100)+1>probabilidade){
					mychar = Character.toLowerCase(mychar);
				}
				resp+=Character.toString(mychar);
			}
		}
		assertFalse(resp.matches("[A-Z]+"));
		assertTrue(resp.matches("[a-z0-9]+"));
	}

	@RepeatedTest(1000)
    void test_Assert_String_as_UpperCaseAlpha(){
		int probabilidade = 100; // probabilidade de ser maiuscula
		int tamanho =10;
		String resp ="";
		Random ran = new Random();		
		for(int i=0;i<tamanho;++i){
			char mychar = (char) ran.nextInt(26); //26 letras [0,26[
			mychar +=65; // estou na tabela ascii com letra maiuscula
			if(ran.nextInt(100)+1>probabilidade){ //1 ao 100
				mychar = Character.toLowerCase(mychar);
			}
			resp+=Character.toString(mychar);
		}
		assertFalse(resp.matches("[a-z]+"));
		assertTrue(resp.matches("[A-Z]+"));
	}


    @RepeatedTest(1000)
    void test_Solve_Invalid_Input_Challenge(){
        /*               TODO 
            Automate Incorrect input generation 
            All lowercase, Lowercase Alphanum and num inputs
            assert false with the problem solver
            */
    }

    @Test 
    void test_Solve_Valid_Input_Challenge(){
        /*               TODO 
            Automate valid input generation 
            All upercase, Upercase Alphanum
            assert true with the problem solver
            */
    }

    @Test 
    void test_Solve_Custom_Input_Challenge(){
        /*               TODO 
            Solve given custom problem inputs 
            assert true with the expected outputs
            */
    }






    
    
}
