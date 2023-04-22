package com.itclinical.challenge.Controllers;

import org.springframework.web.bind.annotation.RestController;

import com.itclinical.challenge.Factory.ChallengeFactory;

@RestController
public class Challenge1Controller implements ChallengeFactory {

    //challenge 1

    Input input = null;

    public Challenge1Controller(String[] in){
    }
    

    public String solve (){
        String resp=""; 
    return resp;
    }

}
    