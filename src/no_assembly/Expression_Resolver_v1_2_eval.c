   /******************************************************************************
      Expression Resolver v1.2 (Expression evaluation only)
        Designed by Daipayan Bhowal
       Using Priority linked list to solve expression evaluation
*******************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define OPERAND 255
#define OPERATOR -255
//#define INT 33
#define INIT_PRIORITY -1

long long bitwise_div(long long dividend, long long int divisor)
{
    long long sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
    dividend = abs(dividend);
    divisor = abs(divisor);
    long long quotient = 0;
    while (dividend >= divisor)
    {
        dividend -= divisor;
        ++quotient;
    }
    return quotient * sign;
}

int bitwise_multi(int a, int b)
{
   int result = 0;
   while (b > 0) {
      if (b & 1) {
         result += a;
         }
      a = a << 1;
      b = b >> 1;
   }
   return result;
}


int bitwise_sub(int x, int y)
{
    while (y != 0)
    {
        int borrow = (~x) & y;
        x = x ^ y;
        y = borrow << 1;
    }
    return x;
}

int bitwise_add(int x, int y)
{
    while (y != 0)
    {
        int carry = x & y;
        x = x ^ y;
        y = carry << 1;
    }
    return x;
}

enum Ty
{
    INT,
    FLOAT,
    CHAR,
    STRING
};

enum Priority  
{
    ZERO_OP,
    SUB_OP,
    ADD_OP,
    DIV_OP,
    MUL_OP,
    MOD_OP,
    LAST_OP
};
struct Symbol
{
   char *symbol;
   char type;
   char *value;
   char qual;
};
struct Symbol symtbl[256];
int max_sym=0;
void Symbol_insert(char *sym,char typ,char *val)
{
    symtbl[max_sym].symbol =(char*) malloc(sizeof(char)*strlen(sym));
    strncpy(symtbl[max_sym].symbol,sym,strlen(sym));
    symtbl[max_sym].type = typ;
    symtbl[max_sym].value = (char*)malloc(sizeof(char)*strlen(val));
    strncpy(symtbl[max_sym].value,val, strlen(sym));
    max_sym++;
}
int Symbol_search(char *sym)
{
    for(int i=0; i<max_sym; i++)
    {
        if(strcmp(sym,symtbl[i].symbol)==0)
        {
            
            return i;
        }
    }
   return -1;
}
struct ListNode
{
    struct ListNode* prev;
    int isOperatorOrOperand;
    int priority;
    struct Symbol *str;
    char op;
    enum Ty type;
    struct ListNode* next;
};
struct ListNode *tail,*head ; // Priority Queue
int size =0;
void printll()
{
    struct ListNode *ptr = head;

    while(ptr != NULL)
    {
        if(ptr->isOperatorOrOperand == OPERAND)
        {
           // printf("Symbol is %s priority is %d\n", ptr->str->value, ptr->priority);
        }
        if(ptr->isOperatorOrOperand == OPERATOR)
        {
          //  printf("Symbol is %c priority is %d\n", ptr->op, ptr->priority);
        }
        ptr = ptr->next;
    }
    
  //  printf("\n");
}

struct ListNode* maximum()
{
    int i=size - 1;
    int max = -1;
    struct ListNode* ptr = head;
    struct ListNode* max_ptr= NULL;
   // printll();
    while(ptr != NULL)
    {
        if(max < ptr->priority && ptr->isOperatorOrOperand == OPERATOR)
        {  max = ptr->priority;
           max_ptr = ptr;
           //printf("maximum value hit ! %c %d\n", ptr->op, ptr->priority);
        }
        
        ptr = ptr->next;
    }
   // printf("\noperator is %c\n", max_ptr->op);
    return max_ptr;
}

void fill(int isType,int pr, struct Symbol *s, char op)
{
  struct ListNode *ptr = (struct ListNode*)malloc(sizeof(struct ListNode));
  ptr->isOperatorOrOperand = isType;
  ptr->priority = pr;
  ptr->next = NULL;
  ptr->prev = NULL;
  if(isType ==  OPERAND)
  {
    ptr->str = s;
    ptr->type = INT;
    ptr->isOperatorOrOperand = OPERAND;
  }
  else
  {  ptr->op = op;
     ptr->isOperatorOrOperand = OPERATOR;
  }
 
  if(tail == NULL)
  {
      tail = ptr;
      head = ptr;
  }
  else
  {
      tail->next =ptr;
      ptr->prev = tail;
      tail = tail->next;
  }
  size++;
}

void expr_resolver()
{  int sum;
    char buffer[64];
    struct ListNode* new_ptr;
    
   // char *reg[] = { "r0" ,"r1" ,"r2" , "r3" , "r4"}; // for register/temp variable insertion
   //    static int rcount =0;
    do
    {
        
        struct ListNode* p = maximum();
       if(p== NULL) // operation is completed successfully
         return;
       //  printf("p->priority is %d!\n", p->priority);
        struct ListNode* left_op = p->prev;
        struct ListNode* right_op = p->next;
        
        // start the reduce functionality
        if(left_op == NULL && right_op == NULL)
         return ;
        if((left_op == NULL && right_op != NULL) || (left_op != NULL && right_op == NULL))
        {
            printf("Expression string is wrong !\n");
        }
      //  printf("p->op is %c %s %s!\n", p->op, left_op->str->value, right_op->str->value);
        switch(p->op)
        {
            case '-':
            {
             sum  = bitwise_sub(atoi(left_op->str->value), atoi(right_op->str->value));
             printf("%s-%s=%d\n", left_op->str->symbol,right_op->str->symbol,sum);
            }
            break;
            case '+':
            {
             sum  = bitwise_add(atoi(left_op->str->value),atoi(right_op->str->value));
             printf("%s+%s=%d\n", left_op->str->symbol,right_op->str->symbol,sum);
            }
            break;
            case '/':
            {
             sum  = bitwise_div(atoi(left_op->str->value), atoi(right_op->str->value));
             printf("%s/%s=%d\n", left_op->str->symbol,right_op->str->symbol,sum);
            }
            break;
            case '*':
            {
             sum  = bitwise_multi(atoi(left_op->str->value),atoi(right_op->str->value));
             printf("%s*%s=%d\n", left_op->str->symbol,right_op->str->symbol,sum);
            }
            break;
            case '%':
            {
             sum  = atoi(left_op->str->value) % atoi(right_op->str->value);
             printf("%s %% %s=%d\n", left_op->str->symbol,right_op->str->symbol,sum);
            }
            break;
            
        }
       //  printf("sum is %d!\n", sum);
        sprintf(buffer, "%d", sum);
 
       
     //   Symbol_insert(reg[rcount++],INT ,buffer); // for register/temp variable insertion
        
        // printll();
        // make left_op as the temporary variable which will store the result of left_op + right_op
        left_op->next = right_op->next;
        if(right_op->next != NULL)
         right_op->next->prev = left_op;

        strcpy(left_op->str->value, buffer);
        
        // Assign the neighbour node priority to out result node left_op
        if(left_op->prev != NULL && right_op->next != NULL)
        {
          if(left_op->prev->priority > right_op->next->priority)
          {
             left_op->priority = left_op->prev->priority;
          }
          else
          {
             left_op->priority = right_op->next->priority;
          }
        } else if(left_op->prev != NULL)
        {
            left_op->priority = left_op->prev->priority;
        } else if(right_op->next != NULL )
        {
            left_op->priority = right_op->next->priority;
        }
        free(right_op);
        free(p);
        
       //  printll();
        //printf("maximum() pr is %d!\n", maximum());

        
    } while(1);
    
    
}

int getNextPriority(char* str)
{
    int pr=0;
      char *s =str;
      //printf(" forward looking char is %c\n", *s);
    while(*s != '+' && *s != '-' && *s != '/' && *s != '*')
     s++;
    // printf(" forward looking char is %c\n", *s);
    switch(*s)
    {
      case '+':
      pr=ADD_OP;
      break;
      case '-':
      pr=SUB_OP;
      break;
      case '/':
      pr=DIV_OP;
      break;
      case '*':
      pr=MUL_OP;
      break;
      case '%':
      pr=MOD_OP;
      break;
    }
    return pr;
}
int mapBlocklevel(int blocklevel)
{
    return 5*blocklevel;
}
int insert(char *str)
{
    static int blocklevel = 0;
   static int priority =INIT_PRIORITY;
   char *s;
   char string_c[100];
   struct Symbol *sym_ptr;
   if(*str == '*')
   {
       priority = MUL_OP;
       if(blocklevel > 0)
       { //  printf("Symbol founded is %c, priority is %d\n !",*str , priority+mapBlocklevel(blocklevel));
              fill(OPERATOR,priority + mapBlocklevel(blocklevel),NULL ,'*');
       } else
       {
         fill(OPERATOR,priority,NULL, '*');
       }
       
       return 1;
   }
   else if(*str == '/')
   {
       priority = DIV_OP;
       if(blocklevel > 0)
       { // printf("Symbol founded is %c, priority is %d\n !",*str , priority+mapBlocklevel(blocklevel));
              fill(OPERATOR,priority + mapBlocklevel(blocklevel),NULL ,'/');
       } else
       {
         fill(OPERATOR,priority,NULL, '/' );
       }
       return 1;
   }
   else if(*str == '+')
   {
       priority = ADD_OP;
       
          if(blocklevel > 0)
           { // printf("Symbol founded is %c, priority is %d\n !",*str , priority+mapBlocklevel(blocklevel));
              fill(OPERATOR,priority + mapBlocklevel(blocklevel),NULL ,'+');
           } else
           {
             //  printf("Symbol founded is %c, priority is %d\n !", *str , priority);
               fill(OPERATOR,priority,NULL ,'+');
           }
       
       return 1;
   }
   else if(*str == '-')
   {
       priority = SUB_OP;
          if(blocklevel > 0)
           { // printf("Symbol founded is %c, priority is %d\n !",*str , priority+mapBlocklevel(blocklevel));
              fill(OPERATOR,priority + mapBlocklevel(blocklevel),NULL ,'-');
           } else
           {
              fill(OPERATOR,priority,NULL, '-' );
           }
       return 1;
   }
   else if(*str == '%')
   {
       priority = MOD_OP;
          if(blocklevel > 0)
           { // printf("Symbol founded is %c, priority is %d\n !",*str , priority+mapBlocklevel(blocklevel));
              fill(OPERATOR,priority + mapBlocklevel(blocklevel),NULL ,'%');
           } else
           {
              fill(OPERATOR,priority,NULL, '%' );
           }
       return 1;
   }
   else if(*str == '(')
   {
       blocklevel++;
       priority = getNextPriority(str+1);
       return 1;
   }
   else if(*str == ')')
   {
       blocklevel--;
       priority = getNextPriority(str+1);
       return 1;
   }
   else if(isalpha(*str))
   {   int i=0,index=-1;
       s = str;
       
       while(isalpha(*str) || isdigit(*str))
       {  str++;
           i++;
       }
       strncpy(string_c,s,i);
       string_c[i]='\0';
       // printf("Symbol inserted is %s\n !",string_c );
       string_c[i+1]='\0';
       index=Symbol_search(string_c);
       if(index != -1)
       {
           if(priority == INIT_PRIORITY)
              priority = getNextPriority(str);
           else if(  *(str+1) != '\0'   && priority < getNextPriority(str) )
             priority = getNextPriority(str);

              
          /*   sym_ptr = (struct Symbol*) malloc (sizeof(struct Symbol));
             sym_ptr->symbol = (char*) malloc (strlen()) */
           if(blocklevel > 0)
           { // printf("Symbol founded is %s, priority is %d\n !",string_c , priority+mapBlocklevel(blocklevel));
              
              fill(OPERAND,priority + mapBlocklevel(blocklevel),&symtbl[index] ,'\0');
           } else
           {
             //  printf("Symbol founded is %s, priority is %d\n !",string_c , priority);
               fill(OPERAND,priority,&symtbl[index] ,'\0');
           }
           
       }
       else
       {
         // printf("[ERROR] Unknown Symbol %s not found !",string_c );
       }
       
       return i;
   }
return 0;        
}
int main()
{
    int i;
    char arr[] = "a+b-c*c-d";
    char a[]="a";
    char b[]="b";
    char c[]="c";
    char d[]="d";
    char a_value[] ="9";
    char b_value[] ="3";
    char c_value[] ="2";
    char d_value[] ="1";
    Symbol_insert(a,INT , a_value);
    Symbol_insert(b,INT ,b_value);
    Symbol_insert(c,INT ,c_value);
    Symbol_insert(d,INT ,d_value);
    for( i=0; i< strlen(arr); )
    {
       // printf("insert is %s\n",arr );
        insert(arr+i);
        i++;
    }
   // printf("\nmaximum value is %d\n", maximum()->priority);
    expr_resolver();
    return 0;
}