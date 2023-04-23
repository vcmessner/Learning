package com.itclinical.challenge.MyChallenges;

import com.itclinical.MyInputs.Input1;
import com.itclinical.challenge.Factory.InputFactory;

public class Challenge3 implements Challenge {

    private InputFactory input;
    private String output;
    private String MyID="3";

    public Challenge3(String[] in) {
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

    @Override
    public void solve() {

        int caracteres[] = new int[130];
        String resp="";
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
                        caracteres[a]+=1;
                        resp+=a;
                    }
                    pos+=n;
                }
                output=resp;
	        }
        }
        for (int i=0;i<130;++i){
            if(caracteres[i]>0){
                String System_out = Character.toString(i) + " = " + caracteres[i]; // ja que nao dá pra ver sysout no junit vejo o valor da variável
                System.out.println(Character.toString(i) + " = " + caracteres[i]);

            }
        }
    }
}
  