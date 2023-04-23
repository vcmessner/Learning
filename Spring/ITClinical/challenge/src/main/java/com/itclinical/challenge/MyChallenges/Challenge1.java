package com.itclinical.challenge.MyChallenges;
import com.itclinical.challenge.Factory.InputFactory;

public class Challenge1 implements Challenge {
    private InputFactory input;
    private String output;
    private String MyID="1";
    
    public InputFactory getInput() {
        return input;
    }

    public void setInput(InputFactory input) {
        this.input = input;
    }

    public Challenge1(String[] in){
        this.input=new InputFactory(in,"1");
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
                    if(Character.isUpperCase(a))
                    resp+=a;
                    pos+=n;
                }
                output=resp;
	        }
        }
    }
}
