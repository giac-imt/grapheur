typedef enum{
    REAL, OPERATOR, FUNCT, ERROR, END, PAR_OP, PAR_CL, VAR, BAR_OP, BAR_CL, ABSOLUTE
}typeLexem;


typedef enum{
    PLUS, MINUS, MULTIP, DIV, POW
}typeOperator;


typedef enum{
    SIN, COS, TAN, SQRT, ABS, LOG, EXP, INT, VAL_NEG, SINC
}typeFunction;

typedef struct{
    int code;
    char message[100];
}typeError;

typedef union{
    float real;
    typeFunction funct;
    typeOperator ope;
    typeError err;
}typeValor;


typedef struct{
    typeLexem lexem;
    typeValor value;
}typeToken;


// Tree's declaration
typedef struct Node{
    typeToken tok;
    struct Node *pTokBfor;
    struct Node *pTokNext;
}Node;


typedef Node *Tree;


typedef struct Result{
    float value;
    typeError err;
}Result;