package com.itclinical.AuxiliaryString;

public class StringChecker {

    public Boolean Validate_is_Pos_Num(String n){ 
        if(n.matches("[0-9]+")){
            return true;           
        }
        else{        
            return false;
        }
    }

    public Boolean Validate_is_Num(String n){ 
        if (n.matches("^-?[0-9]+")){
            return true;
        }
        else{
            return false;
        }
    }

    public Boolean Validate_isAlpha(String text){
        if(text.matches("[a-zA-Z]+")){
            return true;
        }
        else{
            return false;
        }
    }

    public Boolean Validate_isAlNum(String text){
        if(text.matches("[A-Za-z0-9]+")){
            return true;
        }
        else{
            return false;
        }    
    }




}
