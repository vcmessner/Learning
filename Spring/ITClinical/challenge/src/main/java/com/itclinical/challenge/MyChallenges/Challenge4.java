package com.itclinical.challenge.MyChallenges;
import com.itclinical.challenge.Factory.InputFactory;

public class Challenge4 implements Challenge{
    private InputFactory input;
    private String output;
    private String MyID="4";

    public Challenge4(String[] in) {
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
		int cont=0;
        String[] prefixo= {"","","it"};
        output = "";

        for(int i = 1;i<101;++i){
            if((i%3)==0 || (i%5)==0){
                if((i%3==0) && (i%5!=0)){
                    output+="it";
                }
                else{
                    output+=(prefixo[cont]+"clinical");
                    cont+=1;
                    cont=cont%3;
                }
            }
            else{
                output+=i;
            }
        }
    //System.out.println(output);
    }
}

