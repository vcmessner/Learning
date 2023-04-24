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

    void test_Assert_String_as_LowerCaseAlpha(){
        /*               TODO 
            Generate a random lowercase alpha String
            Granted WrongInput for later
            AssertTrue

        */

		//String a = randomLowerCaseAlpha();
        String LowerCaseAlpha = "asdfg";
        assertTrue(LowerCaseAlpha.matches("[a-z]+"));
        assertFalse(LowerCaseAlpha.matches("[A-Z]+"));
        assertFalse(LowerCaseAlpha.matches("[A-Z]+"));
    }

    void test_Assert_String_as_LowerCaseAlphaNum(){
        /*               TODO 
            Generate a random lowercase Alphanum String
            Granted WrongInput for later
            AssertTrue
        */
		String LowerCaseAlphaNum = "123454";
        assertTrue(LowerCaseAlphaNum.matches("[a-z0-9]+"));
    }


    void test_Assert_String_as_UpperCaseAlpha(){
         /*               TODO 
            Generate a random UpperCase String
            Granted correct Input for later
            AssertTrue
        */
		String UpperCaseAlpha = "ABCD";
        assertFalse(UpperCaseAlpha.matches("[A-Z]+"));
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
