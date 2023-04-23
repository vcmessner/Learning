package com.itclinical.challenge;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Random;

import org.junit.jupiter.api.RepeatedTest;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;
import org.springframework.boot.test.context.SpringBootTest;

import com.itclinical.AuxiliaryString.StringChecker;
import com.itclinical.MyInputs.Input1;
import com.itclinical.challenge.Factory.ChallengeFactory;
import com.itclinical.challenge.Factory.InputFactory;

@SpringBootTest
class ChallengeApplicationTests {

	final int max_wrong_input_size = 10;
	final int min_wrong_input_size = 3;
	final int max_letter = 90;
	final int min_letter = 65;

	void teste_tamanho_random(int myint){
		Boolean valid_myint = myint>=min_wrong_input_size && myint<=max_wrong_input_size;
		assertTrue(valid_myint); 
	}

	@Test	
	void teste_NumerodeInputs(){		
		//verifica se a entrada possui de fato dois inputs
		String [] Right_input ={"ITClinical","1"};
		Random ran = new Random();
		int myint = ran.nextInt(7)+3; //numero
		teste_tamanho_random(myint);
		String [] geq_input = new String[myint];
		String [] leq_input = new String[1];
		String empty_input = "";
		int Right_L=Right_input.length;
		int geq_L = geq_input.length;
		int leq_L = leq_input.length;
		assertEquals(Right_L,2);
		assertNotEquals(geq_L,2);
		assertNotEquals(leq_L,2);
		assertNotEquals(empty_input,2);
	}

	@RepeatedTest (1000)
	void test_random_input(){
		InputFactory alpha_correct_Input=new InputFactory(10,50,1,"1");
		InputFactory num_correct_Input=new InputFactory(10,50,2,"1");
		InputFactory alphanum_correct_Input=new InputFactory(10,50,3,"1");
		InputFactory alpha_incorrect_Input=new InputFactory(10,50,-1,"1");
		InputFactory num_incorrect_Input=new InputFactory(10,50,-2,"1");
		InputFactory alphanum_incorrect_Input=new InputFactory(10,50,-3,"1");
		StringChecker Checker = new StringChecker();
		assertTrue(Checker.Validate_isAlpha(alpha_correct_Input.getTexto("1")));
		assertTrue(Checker.Validate_isAlpha(alpha_incorrect_Input.getTexto("1")));
		assertFalse(Checker.Validate_isAlpha(num_correct_Input.getTexto("1")));
		assertFalse(Checker.Validate_isAlpha(num_incorrect_Input.getTexto("1")));
		assertTrue(Integer.class.isInstance(alphanum_correct_Input.getN("1")));
		assertTrue(Integer.class.isInstance(alphanum_incorrect_Input.getN("1")));
		assertTrue(Integer.class.isInstance(alpha_correct_Input.getN("1")));
		assertTrue(Integer.class.isInstance(alpha_incorrect_Input.getN("1")));
		assertTrue(Integer.class.isInstance(num_incorrect_Input.getN("1")));
		assertTrue(Integer.class.isInstance(num_correct_Input.getN("1")));
	}

	@Test 
	void test_String_isalpha(){
		String [] in ={"ITClinical","1"};		
		String [] in2 ={"1","a"};
		String [] in3 ={"",""};
		String [] in4 ={"ITClinical2023","a1"};
		String [] in5 ={"IT Clinical","1a"};
		Input1 Ok_Input = new Input1(in);
		assertTrue(Ok_Input.getTexto().matches("[a-zA-Z]+"));
		assertFalse(in2[0].matches("[a-zA-Z]+"));
		assertFalse(in3[0].matches("[a-zA-Z]+"));
		assertFalse(in4[0].matches("[a-zA-Z]+"));
		assertFalse(in5[0].matches("[a-zA-Z]+"));
	}

	@Test
	void test_String_is_positive_number(){
		String [] in ={"ITClinical","1111238545467134"};
		String [] in2 ={"1","a"};
		String [] in3 ={"",""};
		String [] in4 ={"ITClinical2023","a1"};
		String [] in5 ={"-1","1a"};
		assertTrue(in[1].matches("[0-9]+"));
		assertFalse(in2[1].matches("[0-9]+"));
		assertFalse(in3[1].matches("[0-9]+"));
		assertFalse(in4[1].matches("[0-9]+"));
		assertFalse(in5[1].matches("[0-9]+"));
	}

	@Test
	void test_String_is_number(){
		String [] in ={"ITClinical","1111238545467134"};
		String [] in2 ={"1","a"};
		String [] in3 ={"",""};
		String [] in4 ={"ITClinical2023","a1"};
		String [] in5 ={"-1","1a"};
		assertTrue(in[1].matches("^-?[0-9]+"));
		assertFalse(in2[1].matches("^-?[0-9]+"));
		assertFalse(in3[1].matches("^-?[0-9]+"));
		assertFalse(in4[1].matches("^-?[0-9]+"));
		assertFalse(in5[1].matches("^-?[0-9]+"));
	}	

	@ParameterizedTest
	@ValueSource(strings  = {"1", "2", "3", "100", "-1" , "0", "a"}) // six numbers
	void test_my_Challenge1(String n){
		String text = "ITCLiNicAl";
		String[] in = {text,n};
		ChallengeFactory challenge = new ChallengeFactory(in,"1");		
		String resp = challenge.SolveChallenge(in);
		switch(n){
			case"1":
				assertEquals(resp, "ITCLNA");
				break; 

			case"2":
				assertEquals(resp, "TLN");
			break;

			case"3":
				assertEquals(resp, "CNA");
			break;

			case"100":
				assertEquals(resp,"");
			break;

			case"-1":
				assertEquals(resp,"");
			break;

			case"0":
				assertEquals(resp,"");
			
			case"a":
				assertEquals(resp,"");
			break;
			default:
				break;
		}	
	}

	@Test
	void test_lowercase_regex(){
		int i =0;
		char c = (char) i;		
		for(i=0;i<128;++i){			
			c = (char) i;
			if(i>96 && i<123){
				assertTrue(Character.toString(c).matches("[a-z]+"));
			}
			else{
				assertFalse(Character.toString(c).matches("[a-z]+"));
			}
		}
	}

	@ParameterizedTest
	@ValueSource(strings  = {"1"})
	void test_my_Challenge2(String n){

		// deve retornar qualquer caracter não minusculo
		String text = "!tCL1Nical";
		String[] in = {text,n};
		ChallengeFactory challenge = new ChallengeFactory(in,"2");		
		String resp = challenge.SolveChallenge(in);
		switch(n){
			case"1":
				assertEquals(resp, "!CL1N");
				break; 
			default:
				break;
		}	
	}





	void test_N_geq1(){
		/*melhor colocar simplemente como retorno da aplicação
		 não faz sentido como teste
		 */

	}


	
	void test_Text_output_format(){
		/*verifica se o output fornecido usa "" ou não */
	}



	void teste_TamanhoInput(){
		/* verifica se o tamanho do input não 
		comprometerá a aplicação*/
		/* TODO verificar se existem limitações para tamanhos
		de campos no JSON ou no recebimento pelo springboot*/
	}

	void test_Text_input_format(){
		/* verifica se o input fornecido usa "" ou não */
	}

	void test_generate_test_vector(){
		// verifica a formação de inputs dos testvectors aleatorios
	}












	
	void contextLoads() {
	}

}
