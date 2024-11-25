#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int precedence(char op) {
    return (op == '*' || op == '/') ? 2 : (op == '+' || op == '-') ? 1 : 0;
}

int perform(int a, int b, char op, int *error) {
    if (op == '/' && b == 0) {
        *error = 1; 
        return 0;
    }
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: return 0; 
}

}
int evaluate(const char *exp,int *result){
    int values[100],top=-1,error=0;
    char operators[100] ,opTop=-1;
    for(int i=0;exp[i];i++){
        if(isspace(exp[i])) continue;

        if(isdigit(exp[i])){
            int num=0;
              while (isdigit(exp[i])) num = num * 10 + (exp[i++] - '0');
              values[++top]=num;
              i--;


        }else if (strchr("+-*/", exp[i])){
            while (opTop >= 0 && precedence(exp[i]) <= precedence(operators[opTop]))
            {
                int b=values[top--];
                int a=values[top--];
                values[++top]=perform(a,b,operators[opTop--],&error);
                if(error) return 0;
            }
            operators[++opTop]=exp[i];
        } else  return 0;
    }
    while(opTop>=0){
        int b=values[top--];
        int a=values[top--];

        values[++top] =perform(a,b,operators[opTop--],&error);
        if (error) return 0;
    }
     
     *result=values[top];
     return 1;

}
int main(){
    char input[100];
    int result;
    printf("Enter an expression: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input,"\n")]='\0';

    if(evaluate(input, &result)){
        printf("%d\n",result);
    }else {
        printf("Error:Invalid exxpression or division by zero.\n");
    }
    return 0;
}