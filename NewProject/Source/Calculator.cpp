#include "Calculator.hpp"
#include <iostream>

using namespace::std;

bool OperationManager::areOperationsNonEmpty(string s)
{
    string separators = "+=*/()";
    string numbers = "0123456789";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '*' || s[i] == '/')
        {
            if (s.find_first_of(numbers) == -1 || s.find_first_of(numbers) > i) return false;
            if (s.find_first_of(numbers, i) == -1) return false;
        }
        if (s[i] == '+' || s[i] == '-')
        {
            if (s.find_first_of(numbers, i) == -1) return false;
        }
    }
    
    return true;
}

bool OperationManager::isOperator(char a)
{
    return (a == '+' || a == '-' || a == '/' || a == '*');
}

bool OperationManager::isConfigurationCorrect(string s)
{
    for(int i = 0; i < s.size() - 1; i++)
    {
        if (s[i] == ')' && s[i + 1] == '(') return false;
        if (isOperator(s[i]) && isOperator(s[i + 1])) return false;
        if (isdigit(s[i]) && s[i + 1] == '(') return false;
        if (s[i] == ')' &&  isdigit(s[i + 1])) return false;
    }
    
    return true;
}

bool OperationManager::areBracesCorrect(string s)
{
    int cnt = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if (cnt < 0) return false;
        if (s[i] == '(') cnt++;
        if (s[i] == ')') cnt--;
    }
    
    return cnt == 0;
}

string OperationManager::find_word(string S, int &start_idx, string separators)
{
    int start = (int)S.find_first_not_of(separators, start_idx);
    int finish = (int)S.find_first_of(separators, start);
    
    if (start == -1) start_idx = -1;
    else start_idx = finish;
    
    if (start == -1 || start > S.size()) return "";
    if (finish == -1 || finish > S.size()) return S.substr(start);
    
    return S.substr(start, finish - start);
}

bool OperationManager::isNumberCorrect(string s)
{
    int cnt = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if (s[i] == '.') cnt++;
    }
    
    return (cnt <= 1) && (s.front() != '.') && (s.back() != '.');
}

bool OperationManager::areNumbersCorrect(string s)
{
    string separators = "+=*/()";
    int start_idx = 0;
    while(start_idx != -1)
    {
        string sub;
        sub = find_word(s, start_idx, separators);
        if(not(isNumberCorrect(sub))) return false;
    }
    
    return true;
}

bool OperationManager::validator(string s)
{
    bool ans = true;
    ans = ans && areNumbersCorrect(s);
    ans = ans && areBracesCorrect(s);
    ans = ans && areOperationsNonEmpty(s);
    
    return ans;
}

bool OperationManager::noOperations(string s)
{
    string operations = "+_*/";
    return s.find_first_of(operations) == -1;
}

int OperationManager::findLowestOperation(string &s)
{
    int braces = 0;
    int ansIdx = -1;
    
    while(ansIdx == -1)
    {
        for (int i = 0; i < s.size(); i++)
        {
            if(s[i] == '(') braces++;
            if(s[i] == ')') braces--;
        
            if((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && braces == 0)
            {
                if ((s[i] == '+' || s[i] == '-') && i > 0) return i;
                else ansIdx = i;
            }
        }
        
        if (ansIdx == -1)
        {
            s.erase(s.begin() + s.find_first_of('('));
            s.erase(s.begin() + s.find_last_of(')'));
        }
    }
    
    
    return ansIdx;
}

OperationManager::OperationManager()
{
    node *root = new node;
    this->root = root;
}

void OperationManager::createTree(node *root, string expression)
{
    if (noOperations(expression))
    {
        while(expression.front() == '(')
        {
            expression.erase(expression.begin() + 0);
            expression.pop_back();
        }
        root->value = stod(expression);
    }
    else
    {
        int lowestIdx = findLowestOperation(expression);
        node *left = new node();
        node *right = new node();
        root->left = left;
        root->right = right;
        
        if (lowestIdx == 0)
        {
            root->operation = expression[0];
            
            root->left->value = 0;
            createTree(root->right, expression.substr(1));
        }
        else
        {
            if(expression[lowestIdx] == '-')
            {
                root->operation = '+';
                createTree(root->left, expression.substr(0, lowestIdx));
                createTree(root->right, expression.substr(lowestIdx));
            }
            else
            {
                root->operation = expression[lowestIdx];
            
                createTree(root->left, expression.substr(0, lowestIdx));
                createTree(root->right, expression.substr(lowestIdx + 1));
            }
        }
    }
}

double OperationManager::performOperation(char operation, double num1, double num2)
{
    if (operation == '+') return num1 + num2;
    if (operation == '-') return num1 - num2;
    if (operation == '*') return num1 * num2;
    return num1 / num2;
}

double OperationManager::calculate(node *root)
{
    if (root->operation == '|') return root->value;
    
    return performOperation(root->operation, calculate(root->left), calculate(root->right));
}

void OperationManager::readExpression(string expression)
{
    this->root = new node;
    originalExpression = expression;
}

void OperationManager::deleteTree(node *root)
{
    if (root == NULL) return;
    
    deleteTree(root->left);
    deleteTree(root->right);
    
    delete root;
}

string OperationManager::trim(string s)
{
    while(s.back() == '0' || s.back() == '.')
    {
        if (s.back() == '.')
        {
            s.pop_back();
            return s;
        }
        else s.pop_back();
    }
    return s;
}

string OperationManager::returnValue()
{
    if (not(validator(originalExpression))) return "wrong input";
    
    createTree(root, originalExpression);
    string ans = trim(to_string(calculate(root)));
    deleteTree(root);
    return ans;
}
