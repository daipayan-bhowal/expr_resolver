# expr_resolver
Expression Resolver(Expression evaluation using Priority Linked List)
 
 For now register storage/temporary variable has been commented out

It solves the expression "a+b-c*c-d"

 For a=9, b=3, c=2 and d=1 so expression becomes as below:-
9+3-2*2-1

Each linked list node which contains operator/operand will contain a priority field
based on priority field we will apply BODMAS rule for calculation

Final answer is:-
9+3-2*2-1 = 7


Output Text for the code is given below:-
----------------------------------------
insert is a+b-c*c-d
Symbol inserted is a
 ! forward looking char is +
 forward looking char is +
Symbol founded is a, priority is 2
 !insert is a+b-c*c-d
Symbol founded is +, priority is 2
 !insert is a+b-c*c-d
Symbol inserted is b
 ! forward looking char is -
 forward looking char is -
Symbol founded is b, priority is 2
 !insert is a+b-c*c-d
insert is a+b-c*c-d
Symbol inserted is c
 ! forward looking char is *
 forward looking char is *
 forward looking char is *
 forward looking char is *
Symbol founded is c, priority is 4
 !insert is a+b-c*c-d
insert is a+b-c*c-d
Symbol inserted is c
 ! forward looking char is -
 forward looking char is -
Symbol founded is c, priority is 4
 !insert is a+b-c*c-d
insert is a+b-c*c-d
Symbol inserted is d
 ! forward looking char is 
 forward looking char is *
Symbol founded is d, priority is 1
 !Symbol is 9 priority is 2
Symbol is + priority is 2
Symbol is 3 priority is 2
Symbol is - priority is 1
Symbol is 2 priority is 4
Symbol is * priority is 4
Symbol is 2 priority is 4
Symbol is - priority is 1
Symbol is 1 priority is 1

maximum value hit ! + 2
maximum value hit ! * 4

operator is *

maximum value is 4
Symbol is 9 priority is 2
Symbol is + priority is 2
Symbol is 3 priority is 2
Symbol is - priority is 1
Symbol is 2 priority is 4
Symbol is * priority is 4
Symbol is 2 priority is 4
Symbol is - priority is 1
Symbol is 1 priority is 1

maximum value hit ! + 2
maximum value hit ! * 4

operator is *
p->priority is 4!
p->op is * 2 2!
sum is 4!
Symbol is 9 priority is 2
Symbol is + priority is 2
Symbol is 3 priority is 2
Symbol is - priority is 1
Symbol is 4 priority is 1
Symbol is - priority is 1
Symbol is 1 priority is 1

Symbol is 9 priority is 2
Symbol is + priority is 2
Symbol is 3 priority is 2
Symbol is - priority is 1
Symbol is 4 priority is 1
Symbol is - priority is 1
Symbol is 1 priority is 1

maximum value hit ! + 2

operator is +
p->priority is 2!
p->op is + 9 3!
sum is 12!
Symbol is 12 priority is 1
Symbol is - priority is 1
Symbol is 4 priority is 1
Symbol is - priority is 1
Symbol is 1 priority is 1

Symbol is 12 priority is 1
Symbol is - priority is 1
Symbol is 4 priority is 1
Symbol is - priority is 1
Symbol is 1 priority is 1

maximum value hit ! - 1

operator is -
p->priority is 1!
p->op is - 12 4!
sum is 8!
Symbol is 8 priority is 1
Symbol is - priority is 1
Symbol is 1 priority is 1

Symbol is 8 priority is 1
Symbol is - priority is 1
Symbol is 1 priority is 1

maximum value hit ! - 1

operator is -
p->priority is 1!
p->op is - 8 1!
sum is 7!
Symbol is 7 priority is 1

Symbol is 7 priority is 1

