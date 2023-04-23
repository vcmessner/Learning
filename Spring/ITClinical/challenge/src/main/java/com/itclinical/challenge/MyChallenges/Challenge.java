package com.itclinical.challenge.MyChallenges;

import com.itclinical.MyInputs.Input1;

public interface Challenge {    
    public void setInput(Input1 input);
    public Input1 getInput();
    public String getOutput();
    public void setOutput(String output);
    public void solve();
}
