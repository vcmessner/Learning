package com.itclinical.challenge.MyChallenges;
import com.itclinical.challenge.Factory.InputFactory;

public interface Challenge {    
    public void setInput(InputFactory input);
    public InputFactory getInput();
    public String getOutput();
    public void setOutput(String output);
    public void solve();
}
