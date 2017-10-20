typedef struct{
    typeLexem lexem;
    typeValor valor;
}typeToken;

typedef enum{
    REAL, FUNCT, [...];
}typeLexem;

typedef enum{
    PLUS, MINUS, MULTIP, DIV;
}typeOperator;

typedef enum{
    SIN, COS, TAN, SQRT;
}typeFunction;

typedef union{
    float real;
    typeOperator ope;
    typeFunction funct;
    typeError err;
}typeValor;
