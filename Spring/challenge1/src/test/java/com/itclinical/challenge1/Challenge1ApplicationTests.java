package com.itclinical.challenge1;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

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
        /*               TODO 
            Generate a random number A
            Convert A to String
            AssertTrue
            Generate a random number string
            Assert true 
            */
            int a=0;
            String c="1";
           // int a = generateRandomnumber();
            String b = Integer.toString(a);
            assertTrue(b.matches("^-?[0-9]+"));
		    assertFalse(b.matches("[A-Z]+"));
		    assertFalse(b.matches("[a-z]+"));
          //  String c = RandomNumericStringGen();
            assertTrue(c.matches("^-?[0-9]+"));
		    assertFalse(c.matches("[A-Z]+"));
		    assertFalse(c.matches("[a-z]+"));


    }

    @Test 
    void test_Assert_N_as_Integer(){
        /*               TODO 
            Get Input Parameter N
            Check if N is a Integer
            AssertTrue

        */

    }

    void test_Assert_String_as_LowerCaseAlpha(){
        /*               TODO 
            Generate a random lowercase alpha String
            Granted WrongInput for later
            AssertTrue

        */
    }

    void test_Assert_String_as_LowerCaseAlphaNum(){
        /*               TODO 
            Generate a random lowercase Alphanum String
            Granted WrongInput for later
            AssertTrue

        */
    }


    void test_Assert_String_as_UpperCaseAlpha(){
         /*               TODO 
            Generate a random UpperCase String
            Granted correct Input for later
            AssertTrue

        */
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
