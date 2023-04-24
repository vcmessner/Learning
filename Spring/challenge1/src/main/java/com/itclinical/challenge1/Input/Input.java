package com.itclinical.challenge1.Input;

public class Input {
    String text = "";
    String N = "";

    public Input(String string, String string2) {
        text=string;
        N=string2;
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
