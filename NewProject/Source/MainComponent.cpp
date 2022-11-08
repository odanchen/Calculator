#include "MainComponent.h"

const int BTN_SIZE = 50;

//==============================================================================
MainComponent::MainComponent()
{
    setSize (290, 400); // window size
   
    btn_7.setBounds(30,  155, BTN_SIZE, BTN_SIZE);
    btn_7.onClick = [this] { addDigit("7"); };
   
    btn_8.setBounds(85,  155, BTN_SIZE, BTN_SIZE);
    btn_8.onClick = [this] { addDigit("8"); };
   
    btn_9.setBounds(140, 155, BTN_SIZE, BTN_SIZE);
    btn_9.onClick = [this] { addDigit("9"); };
   
    btn_4.setBounds(30,  210, BTN_SIZE, BTN_SIZE);
    btn_4.onClick = [this] { addDigit("4"); };
   
    btn_5.setBounds(85,  210, BTN_SIZE, BTN_SIZE);
    btn_5.onClick = [this] { addDigit("5"); };
   
    btn_6.setBounds(140, 210, BTN_SIZE, BTN_SIZE);
    btn_6.onClick = [this] { addDigit("6"); };
   
    btn_1.setBounds(30,  265, BTN_SIZE, BTN_SIZE);
    btn_1.onClick = [this] { addDigit("1"); };
   
    btn_2.setBounds(85,  265, BTN_SIZE, BTN_SIZE);
    btn_2.onClick = [this] { addDigit("2"); };
   
    btn_3.setBounds(140, 265, BTN_SIZE, BTN_SIZE);
    btn_3.onClick = [this] { addDigit("3"); };
   
    btn_0.setBounds(85,  320, BTN_SIZE * 2 + 5, BTN_SIZE);
    btn_0.onClick = [this] { addDigit("0"); };
   
    // clear button
    btn_clear.setBounds(30, 100, BTN_SIZE, BTN_SIZE);
    btn_clear.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    btn_clear.onClick = [this] {
        expression = "0";
        updateDisplay();
    };
   
    btn_div.setBounds(215, 100, BTN_SIZE, BTN_SIZE);
    btn_div.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    btn_div.onClick = [this] { addDigit("/"); };
   
    btn_mult.setBounds(215, 155, BTN_SIZE, BTN_SIZE);
    btn_mult.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    btn_mult.onClick = [this] { addDigit("*"); };
   
    btn_minus.setBounds(215, 210, BTN_SIZE, BTN_SIZE);
    btn_minus.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    btn_minus.onClick = [this] { addDigit("-"); };
   
    btn_plus.setBounds(215, 265, BTN_SIZE, BTN_SIZE);
    btn_plus.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    btn_plus.onClick = [this] { addDigit("+"); };
   
    btn_calc.setBounds(215, 320, BTN_SIZE, BTN_SIZE);
    btn_calc.onClick = [this] {
        calculator.readExpression(expression);
        expression = calculator.returnValue();
        updateDisplay();
    };
   
    btn_left_brace.setBounds(85, 100, BTN_SIZE, BTN_SIZE);
    btn_left_brace.onClick = [this] { addDigit("("); };
   
    btn_right_brace.setBounds(140, 100, BTN_SIZE, BTN_SIZE);
    btn_right_brace.onClick = [this] { addDigit(")"); };
    
    btn_dot.setBounds(30, 320, BTN_SIZE, BTN_SIZE);
    btn_dot.onClick = [this] { addDigit("."); };
   
    display.setText("0");
    display.setMultiLine(false);
    display.setReadOnly(true);
    display.setJustification(juce::Justification::centredRight);
    display.setBounds(30, 20, 235, 60);
   
    addAndMakeVisible(btn_0);
    addAndMakeVisible(btn_1);
    addAndMakeVisible(btn_2);
    addAndMakeVisible(btn_3);
    addAndMakeVisible(btn_4);
    addAndMakeVisible(btn_5);
    addAndMakeVisible(btn_6);
    addAndMakeVisible(btn_7);
    addAndMakeVisible(btn_8);
    addAndMakeVisible(btn_9);
   
    addAndMakeVisible(btn_plus);
    addAndMakeVisible(btn_minus);
    addAndMakeVisible(btn_mult);
    addAndMakeVisible(btn_div);
    addAndMakeVisible(btn_calc);
    addAndMakeVisible(btn_clear);
    addAndMakeVisible(btn_left_brace);
    addAndMakeVisible(btn_right_brace);
    addAndMakeVisible(btn_dot);
    
    addAndMakeVisible(display);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::updateDisplay() {
   display.setText(expression);
}

bool MainComponent::isOperator(char a)
{
    return (a == '+' || a == '-' || a == '/' || a == '*');
}

bool MainComponent::validateOperator(string s, char digit)
{
    if (isOperator(s.back())) return false;
    if (s.back() == '.') return false;
    if ((digit == '*' || digit =='/') && s.back() == '(') return false;
    if ((digit == '/' || digit == '*') && s.empty()) return false;
    
    return true;
}

bool MainComponent::isBrace(char a)
{
    return a == '(' || a == ')';
}

int MainComponent::countBraceBalance(string s)
{
    int cnt = 0;
    
    for(char digit : s)
    {
        if (digit == '(') cnt++;
        if (digit == ')') cnt--;
    }
    
    return cnt;
}

bool MainComponent::validateBrace(string s, char digit)
{
    if (isBrace(s.back()))
    {
        if (digit != s.back()) return false;
    }
    
    if (digit == ')')
    {
        if (isOperator(s.back())) return false;
        if (s.back() == '.') return false;
        if (countBraceBalance(s) <= 0) return false;
    }
    
    if (digit == '(')
    {
        if (s.back() == '.') return false;
        if (isdigit(s.back())) return false;
    }
    
    return true;
}

bool MainComponent::isOnlyDot(string s)
{
    int i = (int)s.size() - 1;
    while(i >= 0 && isdigit(s[i])) i--;
    
    if(s[i] >= 0 && s[i] == '.') return false;
    return true;
}

bool MainComponent::validateDot(string s, char digit)
{
    if(not(isdigit(s.back()))) return false;
    if(not(isOnlyDot(s))) return false;
    
    return true;
}

bool MainComponent::validateDigit(string s, char digit)
{
    if (isOperator(digit)) return validateOperator(s, digit);
    if (isBrace(digit)) return validateBrace(s, digit);
    if (isdigit(digit)) return s.back() != ')';
    if (digit == '.') return validateDot(s, digit);
    
    return true;
}

void MainComponent::addDigit(std::string digit) {
    if (expression == "wrong input") expression = "0";
    if (expression == "0" && (digit == "." || digit == "*" || digit == "/")) {
       expression += digit;
   }
    else {
        if (expression == "0")
        {
            if (validateDigit("", digit.front())) expression = digit;
        }
        else if (validateDigit(expression, digit.front())) expression += digit;
   }
   updateDisplay();
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
