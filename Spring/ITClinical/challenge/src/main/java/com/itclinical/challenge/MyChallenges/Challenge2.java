package com.itclinical.challenge.MyChallenges;

import com.itclinical.challenge.Factory.InputFactory;

public class Challenge2 implements Challenge {
    private InputFactory input;
    private String output;
    private String MyID="2";

    public Challenge2(String[] in) {
        this.input=new InputFactory(in,MyID);
    }

    public InputFactory getInput() {
        return input;
    }

    public void setInput(InputFactory input) {
        this.input = input;
    }

    public String getOutput() {
        return output;
    }

    public void setOutput(String output) {
        this.output = output;
    }

    public void solve(){
		String resp="";
		//InputFactory myInput = new Input(in);
        String texto = input.getTexto(MyID);
        int tamanho = texto.length();
        int n = input.getN(MyID);
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
                    if((a<97) || (a>122)){ // melhor do que um and com um não para delimitar o intervalo. 
                        resp+=a;
                    }
                    pos+=n;
                }
                output=resp;
	        }
        }
    }

}
