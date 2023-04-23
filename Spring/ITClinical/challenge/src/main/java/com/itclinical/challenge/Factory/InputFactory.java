package com.itclinical.challenge.Factory;

import com.itclinical.MyInputs.Input;
import com.itclinical.MyInputs.Input1;
import com.itclinical.MyInputs.Input2;

public class InputFactory {
    
    public Input myInput = null; 

   
    //public abstract Challenge createChallenge(String[] in);

    public InputFactory(String[] in, String Num){
        myInput = createInput(in,Num);
    }

    public InputFactory(int tam, int prob, int modo, String tipo){
        myInput = createInput(tam,prob,modo,tipo);
    }

    public Input createInput(String[] in, String Num){
        switch(Num) {
            case "1":
                return  new Input1(in); 
            case "2":
                return  new Input2(in);
            case "3":
                return  new Input2(in);
            case "4":
                return  null;
            default:
                return null;
          }
    } 

    public Input createInput(int tam, int prob, int modo, String tipo){
        switch(tipo) {
            case "1":
                return  new Input1(tam,prob,modo); 
            case "2":
                return  new Input2(tam,prob,modo); 
            case "3":
                return  new Input2(tam,prob,modo); 
            case "4":
                return  new Input2(tam,prob,modo);
            default:
                return null;
          }
    } 

    public String getTexto(String tipo){
        switch(tipo) {
            case "1":
                return  ((Input1) myInput).getTexto(); 
            case "2":
                return  ((Input2) myInput).getTexto(); 
            case "3":
                return  ((Input2) myInput).getTexto();
            case "4":
                return  ((Input2) myInput).getTexto();
            default:
                return null;
          }
    }
	
	public int getN(String tipo){
        switch(tipo) {
            case "1":
                return  ((Input1) myInput).getN(); 
            case "2":
                return  ((Input2) myInput).getN();
            case "3":
                return  ((Input2) myInput).getN(); 
            case "4":
                return  ((Input2) myInput).getN();
            default:
                return -1;
          }
    }
}
