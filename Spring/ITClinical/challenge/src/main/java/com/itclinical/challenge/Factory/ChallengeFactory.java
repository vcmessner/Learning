package com.itclinical.challenge.Factory;

import com.itclinical.challenge.MyChallenges.Challenge;
import com.itclinical.challenge.MyChallenges.Challenge1;
import com.itclinical.challenge.MyChallenges.Challenge2;
import com.itclinical.challenge.MyChallenges.Challenge3;
import com.itclinical.challenge.MyChallenges.Challenge4;




public class ChallengeFactory {

    Challenge myChallenge = null; 

    public  String SolveChallenge(String[] in){
            myChallenge.solve();
            return myChallenge.getOutput();        
        }   
    

    public ChallengeFactory(String[] in, String Num){
        myChallenge = createChallenge(in,Num);
    }

    public Challenge createChallenge(String[] in, String Num){
        switch(Num) {
            case "1":
                return  new Challenge1(in); 
            case "2":
                return  new Challenge2(in);
            case "3":
                return  new Challenge3(in);
            case "4":
                return  new Challenge4(in);
            default:
                return null;
          }
    }
    
}
