package com.itclinical.challenge1.Input;

import com.itclinical.challenge1.Supporters.StringVerificationSupport;

public class Input {
    String text = "";
    String N = "";
    int number=0;

    public int getNumber() {
        return number;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    public Input(String string, String string2) {
        text=string;
        N=string2;
        StringVerificationSupport sup = new StringVerificationSupport();
        if(sup.Validate_is_Num(string2)){
            number=Integer.parseInt(string2);
        }
    }

    public String getText() {
        return text;
    }
    public void setText(String text) {
        this.text = text;
    }
    public String getN() {
        return N;
    }
    public void setN(String n) {
        this.N = n;
    }
    
}
