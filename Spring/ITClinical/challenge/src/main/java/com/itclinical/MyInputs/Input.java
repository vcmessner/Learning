package com.itclinical.MyInputs;

import java.util.Random;

import com.itclinical.AuxiliaryString.StringChecker;

public abstract class Input {
    /*TODO  DOCUMENTATION*/

	protected String str_values="";
    protected StringChecker stringCheck = new StringChecker();

    protected int Generate_Number(int maxint){
		Random ran = new Random();	
        return ran.nextInt(maxint);//[0,maxint[
    }

	protected void set_strValues(String[] in) {
        int tam = in.length;
        for (int i=0; i<tam; ++i){
            str_values+=(in[i]+"\n");
        }
    }
	
	protected int Str_to_Pos_Int(String in){
		if(stringCheck.Validate_is_Pos_Num(in)){
            return Integer.parseInt(in);
        }
		else{
			return -1;
		}
	}

	public abstract String getStrValues();


    /* TODO dar um jeito de remover getTexto e getN. Não faz sentido eles estarem aqui.*/

        
       
   
    
    




}
