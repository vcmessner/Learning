package com.itclinical.challenge.Controllers;

import com.itclinical.challenge.Factory.InputFactory;

public class Input extends InputFactory {
    private String texto="";
    private int n=-1;

    public Input(String[] in) {
        if(Validate_isAlpha(in[0])){
            this.setTexto(in[0]);            
        }
        if(Validate_isNum(in[1])){
            this.setN(Integer.parseInt(in[1]));
        }        
    }
        
    public void setTexto(String texto) {
        this.texto = texto;
    }

    public void setN(int n) {
        this.n = n;
    }

    public String getTexto() {
        return texto;
    }

    public int getN() {
        return n;
    }


    


}
