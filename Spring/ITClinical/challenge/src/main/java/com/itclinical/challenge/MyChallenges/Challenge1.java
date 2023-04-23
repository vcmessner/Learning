package com.itclinical.challenge.MyChallenges;

import com.itclinical.MyInputs.Input1;

public class Challenge1 implements Challenge {
    private Input1 input;
    public Input1 getInput() {
        return input;
    }

    public void setInput(Input1 input) {
        this.input = input;
    }

    private String output;

    public Challenge1(String[] in){
        this.input=new Input1(in);
    }

    public String getOutput() {
        return output;
    }

    public void setOutput(String output) {
        this.output = output;
    }


    public void solve(){
		String resp="";
		//Input myInput = new Input(in);
        String texto = input.getTexto();
        int tamanho = input.getTexto().length();
        int n = input.getN();
        if(n<1){
            output= resp; 
        }       
        else{
            if(tamanho<n){
                output= resp;
            }
            else{
                int pos = n-1; // começando na posição 0
                char a;
                while(pos<tamanho){
                    a = texto.charAt(pos);
                    if(Character.isUpperCase(a))
                    resp+=a;
                    pos+=n;
                }
                output=resp;
	        }
        }
    }    
}
