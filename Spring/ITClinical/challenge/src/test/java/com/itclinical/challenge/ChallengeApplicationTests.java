package com.itclinical.challenge;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class ChallengeApplicationTests {

	final int max_wrong_input_size = 10;
	final int min_wrong_input_size = 3;

	void teste_tamanho_random(int myint){
		Boolean valid_myint = myint>=min_wrong_input_size && myint<=max_wrong_input_size;
		System.out.println(valid_myint);
		assertTrue(valid_myint); 
	}

	@Test	
	void teste_NumerodeInputs(){		
		//verifica se a entrada possui de fato dois inputs
		String [] Right_input ={"ITClinical","1"};
		double random = Math.random() * (max_wrong_input_size - min_wrong_input_size + 1) + min_wrong_input_size;
		int myint = (int) random;
		System.out.println(myint);
		teste_tamanho_random(myint);

		//assertTrue(valid_myint); 
		System.out.println(random);
		//double random_int = Math.floor(Math.random() * (max_test_size - min_test_size + 1) + min_test_size);
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

	@Test
	void test_Texto_isalpha(){
		String [] in ={"ITClinical","1"};
		String [] in2 ={"1","a"};
		String [] in3 ={"",""};
		String [] in4 ={"ITClinical2023","a1"};
		String [] in5 ={"IT Clinical","1a"};

		assertTrue(in[0].matches("[a-zA-Z]+"));
		assertFalse(in2[0].matches("[a-zA-Z]+"));
		assertFalse(in3[0].matches("[a-zA-Z]+"));
		assertFalse(in4[0].matches("[a-zA-Z]+"));
		assertFalse(in5[0].matches("[a-zA-Z]+"));
	}

	@Test
	void test_N_isnumber(){
		String [] in ={"ITClinical","1111238545467134"};
		String [] in2 ={"1","a"};
		String [] in3 ={"",""};
		String [] in4 ={"ITClinical2023","a1"};
		String [] in5 ={"IT Clinical","1a"};

		assertTrue(in[1].matches("[0-9]+"));
		assertFalse(in2[1].matches("[0-9]+"));
		assertFalse(in3[1].matches("[0-9]+"));
		assertFalse(in4[1].matches("[0-9]+"));
		assertFalse(in5[1].matches("[0-9]+"));
	}

	void test_N_geq1(){
		/*melhor colocar simplemente como retorno da aplicação
		 não faz sentido como teste
		 */

	}

	void test_result(){
		String [] in ={"ITClinical","1"};
		Challenge1Controller mycontroller = new Challenge1Controller(in);

		/* verifica se o resultado de acordo com os 
		 exemplos fornecidos pelo problema */
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









	
	void contextLoads() {
	}

}
