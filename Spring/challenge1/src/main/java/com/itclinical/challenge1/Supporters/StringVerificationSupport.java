package com.itclinical.challenge1.Supporters;

public class StringVerificationSupport {
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

    public Boolean Validate_isUpperCaseAlpha(String text){
        if(text.matches("[A-Z]+")){
            return true;
        }
        else{
            return false;
        }
    }

    public Boolean Validate_isLowerCaseAlpha(String text){
        if(text.matches("[a-z]+")){
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

    public Boolean Validate_isUpperCaseAlNum(String text){
        if(text.matches("[A-Z0-9]+")){
            return true;
        }
        else{
            return false;
        }    
    }

    public Boolean Validate_isLowerCaseAlNum(String text){
        if(text.matches("[a-z0-9]+")){
            return true;
        }
        else{
            return false;
        }    
    }
}
