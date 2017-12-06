/*INSTRUCTION TO RUN
./compile expression1 filename.s     -->   Generates Assembly code for expression1 into filename.s
				or
./compile filename.s   -->   Generates Assembly code for a default expression into filename.s
				or
./compile   -->   Generates Assembly code for a default expression into file with name "asm_code.s"
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 256
#define MEM 0x20000000

void unary_operator(void);
FILE *fp;
char stack[max];
int stack_top=-1;
char *input_str;
typedef struct{
	double var;
	int type;
}element;
element input_ele[max],output_ele[max],*temp;
int total_input,total_output,temp_size;
int priority[256]={0},given[]={'(','*','/','%','+','-','&','^','|'};
char *opcode[]={"DUMMY_BRAC","VMUL.F32","VDIV.F32","DUMMY_MOD"
				,"VADD.F32","VSUB.F32","DUMMY_AND","DUMMY_XOR","DUMMY_OR"};

/*Assign precedence to each operator*/
void precedence_init(){
	int i,size = sizeof(given)/sizeof(given[0]);
	for(i=0;i<size;i++) priority[given[i]]=i+1;
}

/*Takes input expression as a string and
 produce a array of structures (input_ele[]).
 Each Element in the array represents either
 operand operator*/
void generate_elements(){
	int i,size = strlen(input_str),flag=0,pt_check=0;
	double prev=0,mul=1;

	for(i=0;i<size;i++){
		if(input_str[i]<=57&&input_str[i]>=48||input_str[i]==46){
                if(input_str[i]==46) pt_check=1;
                else{
                    if(pt_check){
                        mul = mul*0.1;
                        prev = prev+(input_str[i]-48)*mul;
                    }
                    else prev = prev*10 + input_str[i]-48;
                }
                flag=1;
		}
		else if(input_str[i]!='\0'&& input_str[i]!=' '){
            mul=1; pt_check=0;
			if(prev||flag==1){
				input_ele[total_input].var = prev; input_ele[total_input].type = 1;
				total_input++;
				flag=0;
			}
			input_ele[total_input].var = input_str[i]; input_ele[total_input].type = 0;
			total_input++;
			prev=0;
		}
	}
	if(prev||flag==1) {
		input_ele[total_input].var = prev; input_ele[total_input].type = 1;
		total_input++;
	}
	unary_operator();
}

/*Unary Operator Check*/
void unary_operator(){
    int i,j,count;
    temp = (element *)malloc(max*sizeof(element));
    j=0;
    for(i=0;i<total_input;i++){
        if(((char)input_ele[i].var=='-'||(char)input_ele[i].var=='+')&&((i-1)==-1||(input_ele[i-1].type==0&&(char)input_ele[i-1].var!=')'))){
            temp[j].var = '('; temp[j].type=0; j++;
            temp[j].var = 0; temp[j].type=1; j++;
            temp[j].var = input_ele[i].var; temp[j].type = 0; j++; i++;
            if(input_ele[i].var=='('){
                temp[j]=input_ele[i]; j++;
                count=1;
                while(count!=0){
                    i++;
                    if((char)input_ele[i].var=='(') count++;
                    else if ((char)input_ele[i].var==')') count--;
                    temp[j]=input_ele[i]; j++;
                }
                temp[j].var=')'; temp[j].type = 0; j++;
            }
            else{
                temp[j] = input_ele[i]; j++;
                temp[j].var = ')'; temp[j].type=0; j++;
            }
        }
        else temp[j++] = input_ele[i];
    }
    temp_size = j; j=0;
    printf("Temp Infix:\n");
    for(i=0;i<temp_size;i++)
        input_ele[j++] = temp[i];
    total_input = i;
}
/*Check if stack is empty*/
int stack_empty(){
	if(stack_top==-1) return 1;
	else if(stack[stack_top]=='(') return 1;
	else return 0;
}

/*Takes infix expression from input_ele[]
and generate equivalent postfix expression
in output_ele[]*/
void infix_to_postfix(){
	int i;
	for(i=0;i<total_input;i++){
		if(input_ele[i].type==1){
			output_ele[total_output]=input_ele[i];
			total_output++;
		}
		else{
			if(input_ele[i].var=='('){
				stack_top++; stack[stack_top] = (char)input_ele[i].var;
			}
			else if(input_ele[i].var==')'){
				while(stack[stack_top]!='('){
					output_ele[total_output].var = stack[stack_top]; output_ele[total_output].type=0;
					total_output++; stack_top--;
				}
				stack_top--;
			}
			else{
				while(!stack_empty()&&priority[(char)input_ele[i].var]>=priority[stack[stack_top]]){
				output_ele[total_output].var = stack[stack_top]; output_ele[total_output].type=0;
				total_output++; stack_top--;
				}
				stack_top++; stack[stack_top] = (char)input_ele[i].var;
			}
		}
	}
	while(!stack_empty()){
		output_ele[total_output].var = stack[stack_top]; output_ele[total_output].type=0;
		total_output++; stack_top--;
	}
}

/*Takes the postfix expression generated
 in output_ele[](Array of structures) and spawn
 Assembly code for expression evaluation */
void postfix_eval(){
	int i,temp_mem=MEM;
	fprintf(fp,"\tPRESERVE8\n\tTHUMB\n\tAREA\tappcode,\tCODE,\tREADONLY\n\tEXPORT __main\n\tENTRY\n__main  FUNCTION\n");
	fprintf(fp,"\tMOV r0, #0x%x 	;r0--> start address of stack in memory\n",MEM);
	temp_mem -= 4;
	fprintf(fp,"\tSUB r1, r0, #4 		;r1--> stack top in the memory	\n\n");
	for(i=0;i<total_output;i++){
		if(output_ele[i].type==1){
			temp_mem += 4;
			fprintf(fp,"\t;Push Data On to stack\n\tADD r1, #4     ;r1=%x\n",temp_mem);
			fprintf(fp,"\tVLDR.F32 s0, =%f\n",output_ele[i].var);
			fprintf(fp,"\tVSTR.F32 s0, [r1]\n\n");
		}
		else{
			fprintf(fp,"\t;arithmetic Operation\n\tVLDR.F32 s0, [r1]\n\tSUB r1, #4\n\tVLDR.F32 s1, [r1]\n");
			if((char)output_ele[i].var=='/'){
			    fprintf(fp,"\t;Div by 0 Check\n\tVMOV r4, s0\n\tCMP r4, #0\n\tMOVEQ r3, #1\n\tBEQ stop\n");
			}
            fprintf(fp,"\t%s s1, s0\n\tVSTR.F32 s1, [r1]\n\n",opcode[priority[(char)output_ele[i].var]-1]);
		}
	}
	fprintf(fp,"stop B stop\t\t; Infinite Loop at the end\n\tENDFUNC\n\tEND\n");
}

/*To Check for the validity of number of and
sequence of Opening and
closing brackets in the expression*/
int para_check(){
    int i,count=0,size=strlen(input_str);
    for(i=0;i<size;i++){
        if(input_str[i]=='(') count++;
        else if(input_str[i]==')') count--;
    }
    return count;
}

int main(int argc, char **argv)
{
	int i;
	char str[100];
	FILE *ip;
	ip = fopen("expression.txt","r");
	fscanf(ip,"%[^\n]s ",str);
	fclose(ip);
	input_str = str;
	if(argc==3){
            input_str = argv[1];
            fp = fopen(argv[2],"w");
	}
	else if(argc==2) fp = fopen(argv[1],"w");
	else fp = fopen("asm_code.s","w");
	precedence_init();
	printf("Operator Precedence\n");
	for(i=0;i<256;i++) if(priority[i]) printf("Char=%c ASCII=%d Precedance=%d\n",i,i,priority[i]);
	if(para_check()){printf("Incorrect Parenthesis\n");return 0;}
	generate_elements();
	printf("\nInfix:\n");
	for(i=0;i<total_input;i++){
		if(input_ele[i].type==0) printf("%c ",(char)input_ele[i].var);
		else printf("%.2f ",input_ele[i].var);
	}
	printf("\n");
	printf("\n");
	infix_to_postfix();
	printf("\nPostfix:\n");
	for(i=0;i<total_output;i++){
			if(output_ele[i].type==0) printf("%c ",(char)output_ele[i].var);
			else printf("%.2f ",output_ele[i].var);
	}
	printf("\n");
	postfix_eval();
	fclose(fp);
	if(argc==1)
        printf("\nAssembly code Generated with FileName: asm_code.s\n");
	else
        printf("\nAssembly code Generated with FileName: %s\n",argv[argc-1]);
	return 0;
}
