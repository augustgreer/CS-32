//
//  eval.cpp
//  HW2
//
//  Created by August Greer on 2/2/18.
//  Copyright © 2018 August Greer. All rights reserved.
//

#include "map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>

std::string convert(std::string infix, int &errorCode);



bool allInMap(std::string infix,const Map& map)
{
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] >= 'a' && infix[i] <= 'z' && !map.contains(infix[i]))
            return false;
    }
    return true;
}

bool precedenceLessOrEqual(char a, char b)
{
    if ((a == '/' || a == '*') && (b == '+' || b == '-'))
        return false; //check
    else
        return true; //check
}

int evaluate(std::string infix, const Map& values, std::string& postfix, int& result)
{
    std::stack<int> operandStack;
    int errorCode = 0;
    postfix = (convert(infix, errorCode));
    if (errorCode == 1)
        return 1;
    if(!allInMap(infix, values))
        return 2;
    int currentResult = 0;

    for (int i = 0; i < postfix.size(); i++)
    {
        if (isalpha(postfix[i]))
        {
            int value = 0;
            values.get(postfix[i], value);
            operandStack.push(value);
        }
        else
        {
            int operator2 = operandStack.top();
            operandStack.pop();
            int operator1 = operandStack.top();
            operandStack.pop();
            
            if (postfix[i] == '/')
            {
                if (operator2 == 0)
                    return 3;
                currentResult = operator1 / operator2;
            }
            else if (postfix[i] == '*')
                currentResult = operator1 * operator2;
            else if (postfix[i] == '+')
                currentResult = operator1 + operator2;
            else if (postfix[i] == '-')
                currentResult = operator1 - operator2;
        operandStack.push(currentResult);
        }
    }
    result = operandStack.top();
    return 0;
}


std::string convert(std::string infix, int &errorCode)
{
    errorCode = 0;
    int leftParantheses = 0;
    int rightParantheses = 0;
    int chars = 0;
    uint operators = 0;
    
    std::string postfix = "";
    std::stack<char> operatorStack;
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] >= 'a' && infix[i] <= 'z')
        {
            postfix += infix[i];
            chars++;
        }
        else
            switch (infix[i]) {
                case '(':
                    operatorStack.push(infix[i]);
                    leftParantheses++;
                    break;
                case ')':
                {
                    while (operatorStack.top() != '(') //check
                           {
                               postfix += operatorStack.top();
                               operatorStack.pop();
                           }
                    operatorStack.pop();
                    rightParantheses++;
                    break;
                }
                case '*':
                case '/':
                case '+':
                case '-':
                {
                    while (operatorStack.size() > 0 && operatorStack.top() != '(' && precedenceLessOrEqual(infix[i], operatorStack.top()))
                    {
                        postfix += operatorStack.top();
                        operatorStack.pop();
                    }
                    operatorStack.push(infix[i]);
                    operators++;
                    break;
                }
                case ' ':
                    break; //check
                default:
                    errorCode = 1;
                    break;
        }
    }
    while (operatorStack.size() > 0)
    {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    if ((leftParantheses != rightParantheses) || (chars == 0 && (leftParantheses > 0 || rightParantheses > 0)) || chars - operators != 1)
        errorCode = 1;
        
    return postfix;
}

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    std::string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  && pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
           pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
           pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
           pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    std::cout << "Passed all tests" << std::endl;
}
