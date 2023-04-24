package com.itclinical.challenge.MyChallenges;
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
        int order[] = new int[130];
        String resp="";
        String texto = input.getTexto(MyID);
        int tamanho = texto.length();
        int n = input.getN(MyID);
        int order_count =0;
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
                        if(caracteres[a]==0){ // evitar duplicatas
                            order[order_count] = a;
                            ++order_count;
                        }
                        caracteres[a]+=1;
                        resp+=a;
                    }
                    pos+=n;
                }
                output=resp;
	        }
        }
        int i=0;
        while(order[i]>0){
            String System_out = Character.toString(order[i]) + " = " + caracteres[order[i]]; // ja que nao dá pra ver sysout no junit vejo o valor da variável
            //System.out.println(Character.toString(i) + " = " + caracteres[i]);
            ++i;
        }
        }
    }
  