//
//  Calculator.hpp
//  Calculator - App
//
//  Created by Oleksandr Danchenko on 06.11.2022.
//

#ifndef Calculator_hpp
#define Calculator_hpp

#include <stdio.h>
#include <iostream>

using namespace::std;

class OperationManager
{
    struct node
    {
        char operation = '|';
        double value;
        node *left = NULL;
        node *right = NULL;
    };

    private:
        node *root;
        string originalExpression;
        static void createTree(node *root, string expression);
        static double performOperation(char operation, double num1, double num2);
        static double calculate(node *root);
        static int findLowestOperation(string &s);
        static bool noOperations(string s);
        static bool validator(string s);
        static string find_word(string S, int &start_idx, string separators);
        static bool areNumbersCorrect(string s);
        static bool isNumberCorrect(string s);
        static bool areBracesCorrect(string s);
        static bool isConfigurationCorrect(string s);
        static bool isOperator(char a);
        static bool areOperationsNonEmpty(string s);
        static string trim(string s);
        static void deleteTree(node *root);
    public:
        void readExpression(string expression);
        OperationManager();
        string returnValue();
};

#endif /* Calculator_hpp */
