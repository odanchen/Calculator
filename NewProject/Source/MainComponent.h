#pragma once

#include <JuceHeader.h>
#include "Calculator.hpp"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    std::string expression = "0";
    OperationManager calculator;
    // Calculator buttons
    juce::TextButton btn_0 { "0" };
    juce::TextButton btn_1 { "1" };
    juce::TextButton btn_2 { "2" };
    juce::TextButton btn_3 { "3" };
    juce::TextButton btn_4 { "4" };
    juce::TextButton btn_5 { "5" };
    juce::TextButton btn_6 { "6" };
    juce::TextButton btn_7 { "7" };
    juce::TextButton btn_8 { "8" };
    juce::TextButton btn_9 { "9" };
        
    juce::TextButton btn_plus { "+" };
    juce::TextButton btn_minus { "-" };
    juce::TextButton btn_mult { "*" };
    juce::TextButton btn_div  { "/" };
    
    juce::TextButton btn_left_brace { "(" };
    juce::TextButton btn_right_brace { ")" };
    juce::TextButton btn_dot  { "." };
        
    juce::TextButton btn_calc { "=" };
    juce::TextButton btn_clear { "C" };
    
    juce::TextEditor display;
    
    void updateDisplay();
    void addDigit(std::string digit);
    bool isOperator(char a);
    bool isBrace(char a);
    int countBraceBalance(string s);
    bool validateBrace(string s, char a);
    bool validateOperator(string s, char digit);
    bool validateDigit(string s, char digit);
    bool validateDot(string s, char digit);
    bool isOnlyDot(string s);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
