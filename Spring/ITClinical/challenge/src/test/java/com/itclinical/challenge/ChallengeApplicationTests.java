package com.itclinical.challenge;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

@SpringBootTest
class ChallengeApplicationTests {

	@Test	
	void teste_NumerodeInputs(){
		//verifica se a chamada possui de fato dois inputs
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

	void test_Texto_isalpha(){
		/* verifica se o texto de entrada possui 
		   somente caracteres alfabéticos*/
	}

	void test_N_isnumber(){
		/*verifica se o parametro de entrada N é de fato
		 Numérico */
	}

	void test_N_geq1(){
		/*verifica se N é maior que 1 */

	}

	void test_result(){
		/* verifica se o resultado de acordo com os 
		 exemplos fornecidos pelo problema */
	}
	
	void test_Text_output_format(){
		/*verifica se o output fornecido usa "" ou não */
	}

	










	
	void contextLoads() {
	}

}
