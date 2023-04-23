package com.itclinical.MyInputs;

import com.itclinical.AuxiliaryString.StringGenerator;

public class Input2 extends Input{


    private String texto="";
    private int n=-1;
    

    public Input2(String[] in) {
                
    }

    public Input2(int tamanho, int probabilidade, int modo){
        StringGenerator Generator = new StringGenerator();
        // TODO documentar
        switch (modo) {
            case 1:
                this.setTexto(Generator.Generate_Alpha_String(tamanho, probabilidade));
                this.setN(Generate_Number(tamanho));                    
            break;            
            case 2:            
                this.setTexto(Generator.Generate_Num_String(tamanho));
                this.setN(Generate_Number(tamanho));          
            break;            
            case 3:            
                this.setTexto(Generator.Generate_AlphaNum_String(tamanho, probabilidade));  
                this.setN(Generate_Number(tamanho));              
            break;
            case -1:
                this.setTexto(Generator.Generate_Alpha_String(tamanho, probabilidade));   
                this.setN(Generate_Number(tamanho)+tamanho);               
            break;            
            case -2:            
                this.setTexto(Generator.Generate_Num_String(tamanho)); 
                this.setN(Generate_Number(tamanho)+tamanho);         
            break;            
            case -3:            
                this.setTexto(Generator.Generate_AlphaNum_String(tamanho, probabilidade));
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

    @Override
    public String getStrValues() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'getStrValues'");
    }


    


}
