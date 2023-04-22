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

    public Input(int tamanho, int probabilidade, int modo){
        // TODO documentar
        switch (modo) {
            case 1:
                this.setTexto(Generate_Alpha_String(tamanho, probabilidade));
                this.setN(Generate_Number(tamanho));                    
            break;            
            case 2:            
                this.setTexto(Generate_Num_String(tamanho));
                this.setN(Generate_Number(tamanho));          
            break;            
            case 3:            
                this.setTexto(Generate_AlphaNum_String(tamanho, probabilidade));  
                this.setN(Generate_Number(tamanho));              
            break;
            case -1:
                this.setTexto(Generate_Alpha_String(tamanho, probabilidade));   
                this.setN(Generate_Number(tamanho)+tamanho);               
            break;            
            case -2:            
                this.setTexto(Generate_Num_String(tamanho)); 
                this.setN(Generate_Number(tamanho)+tamanho);         
            break;            
            case -3:            
                this.setTexto(Generate_AlphaNum_String(tamanho, probabilidade));
                this.setN(Generate_Number(tamanho)+tamanho);                
            break;
            default:            
                this.setTexto("");
                n=1;           
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
