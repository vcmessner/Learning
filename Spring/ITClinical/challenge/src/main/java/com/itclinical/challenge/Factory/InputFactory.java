package com.itclinical.challenge.Factory;

public abstract class InputFactory {
    /*TODO  DOCUMENTATION*/
    
    protected Boolean Validate_isNum(String n){ 
        if(n.matches("[0-9]+")){
            return true;           
        }
        else{        
            return false;}
    }

    protected Boolean Validate_isAlpha(String text){
        if(text.matches("[a-zA-Z]+")){
            return true;
        }
        else{
            return false;
        }
    }    
}
