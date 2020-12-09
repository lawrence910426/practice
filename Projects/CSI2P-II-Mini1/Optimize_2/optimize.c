#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*
For the language grammar, please refer to Grammar section on the github page:
  https://github.com/lightbulb12294/CSI2P-II-Mini1#grammar
*/

#define MAX_LENGTH 200
typedef enum {
	ASSIGN, ADD, SUB, MUL, DIV, REM, PREINC, PREDEC, POSTINC, POSTDEC, IDENTIFIER, CONSTANT, LPAR, RPAR, PLUS, MINUS, LOAD, STORE
} Kind;
typedef enum {
	STMT, EXPR, ASSIGN_EXPR, ADD_EXPR, MUL_EXPR, UNARY_EXPR, POSTFIX_EXPR, PRI_EXPR
} GrammarState;
typedef struct TokenUnit {
	Kind kind;
	int val; // record the integer value or variable name
	struct TokenUnit *next;
} Token;
typedef struct ASTUnit {
	Kind kind;
	int val; // record the integer value or variable name
	struct ASTUnit *lhs, *mid, *rhs;
	int used, yield_reg;
} AST;

/// utility interfaces

// err marco should be used when a expression error occurs.
#define err(x) {\
	puts("Compile Error!");\
	if(DEBUG) {\
		fprintf(stderr, "Error at line: %d\n", __LINE__);\
		fprintf(stderr, "Error message: %s\n", x);\
	}\
	exit(0);\
}
// You may set DEBUG=1 to debug. Remember setting back to 0 before submit.
#define DEBUG 0
// Split the input char array into token linked list.
Token *lexer(const char *in);
// Create a new token.
Token *new_token(Kind kind, int val);
// Translate a token linked list into array, return its length.
size_t token_list_to_arr(Token **head);
// Parse the token array. Return the constructed AST.
AST *parser(Token *arr, size_t len);
// Parse the token array. Return the constructed AST.
AST *parse(Token *arr, int l, int r, GrammarState S);
// Create a new AST node.
AST *new_AST(Kind kind, int val);
// Find the location of next token that fits the condition(cond). Return -1 if not found. Search direction from start to end.
int findNextSection(Token *arr, int start, int end, int (*cond)(Kind));
// Return 1 if kind is ASSIGN.
int condASSIGN(Kind kind);
// Return 1 if kind is ADD or SUB.
int condADD(Kind kind);
// Return 1 if kind is MUL, DIV, or REM.
int condMUL(Kind kind);
// Return 1 if kind is RPAR.
int condRPAR(Kind kind);
// Check if the AST is semantically right. This function will call err() automatically if check failed.
void semantic_check(AST *now);
// Generate ASM code.
void codegen();
// Free the whole AST.
void freeAST(AST *now);
// Output the ASM code.
void Output();


/// debug interfaces

// Print token array.
void token_print(Token *in, size_t len);
// Print AST tree.
void AST_print(AST *head);

char input[MAX_LENGTH];
AST *ast[MAX_LENGTH]; 
int N = 0;

int main() {
	for(int i = 0;i < 3;i++) ast[N++] = new_AST(LOAD, i);
	while (fgets(input, MAX_LENGTH, stdin) != NULL) {
		Token *content = lexer(input);
		size_t len = token_list_to_arr(&content);
		ast[N] = parser(content, len);
		semantic_check(ast[N]);
		//AST_print(ast_root);
		free(content);
        N += 1;
	}
	for(int i = 0;i < 3;i++) ast[N++] = new_AST(STORE, i);
    codegen();
    for(int i = 0;i < N;i++) freeAST(ast[i]);
    Output();
	return 0;
}

Token *lexer(const char *in) {
	Token *head = NULL;
	Token **now = &head;
	for (int i = 0; in[i]; i++) {
		if (in[i] == ' ' || in[i] == '\n') // ignore space and newline
			continue;
		else if (isdigit(in[i])) {
			(*now) = new_token(CONSTANT, atoi(in + i));
			while (in[i+1] && isdigit(in[i+1])) i++;
		}
		else if ('x' <= in[i] && in[i] <= 'z') // variable
			(*now) = new_token(IDENTIFIER, in[i]);
		else switch (in[i]) {
			case '=':
				(*now) = new_token(ASSIGN, 0);
				break;
			case '+':
				if (in[i+1] && in[i+1] == '+') {
					i++;
					// In lexer scope, all "++" will be labeled as PREINC.
					(*now) = new_token(PREINC, 0);
				}
				// In lexer scope, all single "+" will be labeled as PLUS.
				else (*now) = new_token(PLUS, 0);
				break;
			case '-':
				if (in[i+1] && in[i+1] == '-') {
					i++;
					// In lexer scope, all "--" will be labeled as PREDEC.
					(*now) = new_token(PREDEC, 0);
				}
				// In lexer scope, all single "-" will be labeled as MINUS.
				else (*now) = new_token(MINUS, 0);
				break;
			case '*':
				(*now) = new_token(MUL, 0);
				break;
			case '/':
				(*now) = new_token(DIV, 0);
				break;
			case '%':
				(*now) = new_token(REM, 0);
				break;
			case '(':
				(*now) = new_token(LPAR, 0);
				break;
			case ')':
				(*now) = new_token(RPAR, 0);
				break;
			default:
				err("Unexpected character.");
		}
		now = &((*now)->next);
	}
	return head;
}

Token *new_token(Kind kind, int val) {
	Token *res = (Token*)malloc(sizeof(Token));
	res->kind = kind;
	res->val = val;
	res->next = NULL;
	return res;
}

size_t token_list_to_arr(Token **head) {
	size_t res;
	Token *now = (*head), *del;
	for (res = 0; now != NULL; res++) now = now->next;
	now = (*head);
	if (res != 0) (*head) = (Token*)malloc(sizeof(Token) * res);
	for (int i = 0; i < res; i++) {
		(*head)[i] = (*now);
		del = now;
		now = now->next;
		free(del);
	}
	return res;
}

AST *parser(Token *arr, size_t len) {
	for (int i = 1; i < len; i++) {
		// correctly identify "ADD" and "SUB"
		if (arr[i].kind == PLUS || arr[i].kind == MINUS) {
			switch (arr[i - 1].kind) {
				case PREINC:
				case PREDEC:
				case IDENTIFIER:
				case CONSTANT:
				case RPAR:
					arr[i].kind = arr[i].kind - PLUS + ADD;
				default: break;
			}
		}
	}
	return parse(arr, 0, len - 1, STMT);
}

AST *parse(Token *arr, int l, int r, GrammarState S) {
	AST *now = NULL;
	int nxt;
	switch (S) {
		case STMT:
			if (l > r) return now;
			else return parse(arr, l, r, EXPR);
		case EXPR:
			return parse(arr, l, r, ASSIGN_EXPR);
		case ASSIGN_EXPR:
			if ((nxt = findNextSection(arr, l, r, condASSIGN)) != -1) {
				now = new_AST(arr[nxt].kind, 0);
				now->lhs = parse(arr, l, nxt - 1, UNARY_EXPR);
				now->rhs = parse(arr, nxt + 1, r, ASSIGN_EXPR);
				return now;
			}
			return parse(arr, l, r, ADD_EXPR);
		case ADD_EXPR:
			if((nxt = findNextSection(arr, r, l, condADD)) != -1) {
				now = new_AST(arr[nxt].kind, 0);
				now->lhs = parse(arr, l, nxt - 1, ADD_EXPR);
				now->rhs = parse(arr, nxt + 1, r, MUL_EXPR);
				return now;
			}
			return parse(arr, l, r, MUL_EXPR);
		case MUL_EXPR:
			if((nxt = findNextSection(arr, r, l, condMUL)) != -1) {
				now = new_AST(arr[nxt].kind, 0);
				now->lhs = parse(arr, l, nxt - 1, MUL_EXPR);
				now->rhs = parse(arr, nxt + 1, r, UNARY_EXPR);
				return now;
			}
			return parse(arr, l, r, UNARY_EXPR);
			// TODO: Implement MUL_EXPR.
			// hint: Take ADD_EXPR as reference.
            /* -- Finished -- */
		case UNARY_EXPR:
			if (arr[l].kind == PREINC || arr[l].kind == PREDEC || arr[l].kind == PLUS || arr[l].kind == MINUS) {
				now = new_AST(arr[l].kind, 0);
				now->mid = parse(arr, l + 1, r, UNARY_EXPR);
				return now;
			}
			return parse(arr, l, r, POSTFIX_EXPR);
			// TODO: Implement UNARY_EXPR.
			// hint: Take POSTFIX_EXPR as reference.
            /* -- Finished -- */
		case POSTFIX_EXPR:
			if (arr[r].kind == PREINC || arr[r].kind == PREDEC) {
				// translate "PREINC", "PREDEC" into "POSTINC", "POSTDEC"
				now = new_AST(arr[r].kind - PREINC + POSTINC, 0);
				now->mid = parse(arr, l, r - 1, POSTFIX_EXPR);
				return now;
			}
			return parse(arr, l, r, PRI_EXPR);
		case PRI_EXPR:
			if (findNextSection(arr, l, r, condRPAR) == r) {
				now = new_AST(LPAR, 0);
				now->mid = parse(arr, l + 1, r - 1, EXPR);
				return now;
			}
			if (l == r) {
				if (arr[l].kind == IDENTIFIER || arr[l].kind == CONSTANT)
					return new_AST(arr[l].kind, arr[l].val);
				err("Unexpected token during parsing.");
			}
			err("No token left for parsing.");
		default:
			err("Unexpected grammar state.");
	}
}

AST *new_AST(Kind kind, int val) {
	AST *res = (AST*)malloc(sizeof(AST));
	res->kind = kind;
	res->val = val;
	res->lhs = res->mid = res->rhs = NULL;
	return res;
}

int findNextSection(Token *arr, int start, int end, int (*cond)(Kind)) {
	int par = 0;
	int d = (start < end) ? 1 : -1;
	for (int i = start; (start < end) ? (i <= end) : (i >= end); i += d) {
		if (arr[i].kind == LPAR) par++;
		if (arr[i].kind == RPAR) par--;
		if (par == 0 && cond(arr[i].kind) == 1) return i;
	}
	return -1;
}

int condASSIGN(Kind kind) {
	return kind == ASSIGN;
}

int condADD(Kind kind) {
	return kind == ADD || kind == SUB;
}

int condMUL(Kind kind) {
	return kind == MUL || kind == DIV || kind == REM;
}

int condRPAR(Kind kind) {
	return kind == RPAR;
}

void semantic_check(AST *now) {
	if (now == NULL) return;
	// Left operand of '=' must be an identifier or identifier with one or more parentheses.
	if (now->kind == ASSIGN) {
		AST *tmp = now->lhs;
		while (tmp->kind == LPAR) tmp = tmp->mid;
		if (tmp->kind != IDENTIFIER)
			err("Lvalue is required as left operand of assignment.");
	}
    
	// Operand of INC/DEC must be an identifier or identifier with one or more parentheses.
	// TODO: Implement the remaining semantic_check code.
	// hint: Follow the instruction above and ASSIGN-part code to implement.
	// hint: Semantic of each node needs to be checked recursively (from the current node to lhs/mid/rhs node).

	if (PREINC <= now->kind && now->kind <= POSTDEC) {
		AST *tmp = now->mid;
		while (tmp->kind == LPAR) tmp = tmp->mid;
		if (tmp->kind != IDENTIFIER)
			err("INC/DEC must be an identifier or identifier with one or more parentheses.");
	}
	semantic_check(now->lhs);
	semantic_check(now->rhs);
	semantic_check(now->mid);
}

void freeAST(AST *now) {
	if (now == NULL) return;
	freeAST(now->lhs);
	freeAST(now->mid);
	freeAST(now->rhs);
	free(now);
}

void token_print(Token *in, size_t len) {
	const static char KindName[][20] = {
		"Assign", "Add", "Sub", "Mul", "Div", "Rem", "Inc", "Dec", "Inc", "Dec", "Identifier", "Constant", "LPar", "RPar", "Plus", "Minus"
	};
	const static char KindSymbol[][20] = {
		"'='", "'+'", "'-'", "'*'", "'/'", "'%'", "\"++\"", "\"--\"", "\"++\"", "\"--\"", "", "", "'('", "')'", "'+'", "'-'"
	};
	const static char format_str[] = "<Index = %3d>: %-10s, %-6s = %s\n";
	const static char format_int[] = "<Index = %3d>: %-10s, %-6s = %d\n";
	for(int i = 0; i < len; i++) {
		switch(in[i].kind) {
			case LPAR:
			case RPAR:
			case PREINC:
			case PREDEC:
			case ADD:
			case SUB:
			case MUL:
			case DIV:
			case REM:
			case ASSIGN:
			case PLUS:
			case MINUS:
				printf(format_str,i , KindName[in[i].kind], "symbol", KindSymbol[in[i].kind]);
				break;
			case CONSTANT:
				printf(format_int,i , KindName[in[i].kind], "value", in[i].val);
				break;
			case IDENTIFIER:
				printf(format_str,i , KindName[in[i].kind], "name", (char*)(&(in[i].val)));
				break;
			default:
				puts("=== unknown token ===");
		}
	}
}

void AST_print(AST *head) {
	static char indent_str[MAX_LENGTH] = "";
	static int indent = 0;
	char *indent_now = indent_str + indent;
	const static char KindName[][20] = {
		"Assign", "Add", "Sub", "Mul", "Div", "Rem", "PreInc", "PreDec", "PostInc", "PostDec", "Identifier", "Constant", "Parentheses", "Parentheses", "Plus", "Minus"
	};
	const static char format[] = "%s\n";
	const static char format_str[] = "%s, <%s = %s>\n";
	const static char format_val[] = "%s, <%s = %d>\n";
	if (head == NULL) return;
	indent_str[indent - 1] = '-';
	printf("%s", indent_str);
	indent_str[indent - 1] = ' ';
	if (indent_str[indent - 2] == '`')
		indent_str[indent - 2] = ' ';
	switch (head->kind) {
		case ASSIGN:
		case ADD:
		case SUB:
		case MUL:
		case DIV:
		case REM:
		case PREINC:
		case PREDEC:
		case POSTINC:
		case POSTDEC:
		case LPAR:
		case RPAR:
		case PLUS:
		case MINUS:
			printf(format, KindName[head->kind]);
			break;
		case IDENTIFIER:
			printf(format_str, KindName[head->kind], "name", (char*)&(head->val));
			break;
		case CONSTANT:
			printf(format_val, KindName[head->kind], "value", head->val);
			break;
		default:
			puts("=== unknown AST type ===");
	}
	indent += 2;
	strcpy(indent_now, "| ");
	AST_print(head->lhs);
	strcpy(indent_now, "` ");
	AST_print(head->mid);
	AST_print(head->rhs);
	indent -= 2;
	(*indent_now) = '\0';
}

/* -------------------------------------------------------------------------------------------------------------------------- */
/* Homework part */
#pragma region Vector
struct Vector { 
	void *storage; 
	struct Vector *next;
} *opt_asm;
struct Vector* Append(struct Vector* last, void* item) {
	struct Vector* object = (struct Vector*)malloc(sizeof(struct Vector));
	object->storage = item;
	if(last == NULL) {
		object->next = object;
	} else {
		object->next = last->next;
		last->next = object;
	}
	return object;
}
void EraseNext(struct Vector* node) {
	struct Vector* temp = node->next;
	node->next = temp->next;
	free(temp);
}
#pragma endregion Vector

#pragma region ASM
enum Operation { Op_LOAD, Op_STORE, Op_ADD, Op_SUB, Op_MUL, Op_DIV, Op_REM };
enum ValueType { Val_CONST, Val_REG, Val_MEM, Val_NUL };
struct Symbol { 
	enum ValueType vtype; 
	int value; 
}; 
struct ASM { 
	enum Operation op; 
	struct Symbol out, in[2]; 
};
struct ASM* Gen_ASM(struct Symbol out, struct Symbol l, struct Symbol r, enum Operation op) {
	struct ASM *line = calloc(1, sizeof(struct ASM));
	line->in[0] = l;
	line->in[1] = r;
	line->out = out;
	line->op = op;
	return line;
}
#pragma endregion ASM

#pragma region ConstantOptimize
int Run(AST* on, int in[3], int out[3], int *ans) {
	if(on == NULL) return 0;
	int lans, rans, mans;
	switch(on->kind) {
		case ADD: ;
		case SUB: ;
		case MUL: ;
		case DIV: ;
		case REM: ;
		{
			if(Run(on->lhs, in, out, &lans) || Run(on->rhs, in, out, &rans)) return 1;
			if(on->kind == ADD) *ans = lans + rans;
			if(on->kind == SUB) *ans = lans - rans;
			if(on->kind == MUL) *ans = lans * rans;
			if(on->kind == DIV || on->kind == REM) {
				if(rans == 0) return 1;
				*ans = (on->kind == DIV ? lans / rans : lans % rans);
			}
			break;
		}
		case LPAR: ;
		case RPAR: ;
		case PLUS: ;
		case MINUS: ;
		{
			if(Run(on->mid, in, out, &mans)) return 1;
			*ans = (on->kind == MINUS ? -mans : mans);
			break;
		}
		case IDENTIFIER: ;
		case CONSTANT: ;
		{
			*ans = (on->kind == CONSTANT ? on->val : in[on->val]);
			break;
		}
		case ASSIGN: ;
		{
			if(Run(on->rhs, in, out, &rans)) return 1;
			AST* target = on->lhs;
			while(target->kind != IDENTIFIER) target = target->mid;
			out[target->val] = rans;
			*ans = rans;
			break;
		}
		case PREINC: ;
		case PREDEC: ;
		case POSTINC: ;
		case POSTDEC: ;
		{
			AST* target = on->mid;
			while(target->kind != IDENTIFIER) target = target->mid;
			if(on->kind == PREINC) *ans = ++out[target->val];
			if(on->kind == PREDEC) *ans = --out[target->val];
			if(on->kind == POSTINC) *ans = out[target->val]++;
			if(on->kind == POSTDEC) *ans = out[target->val]--;
			break;
		}
		case LOAD: ;
		case STORE: ;
		return 1;
	}
	return 0;
}
#define MAXC 130
void Enumerate_Constant_Optimize(AST* on) {
	if(on == NULL) return;
	switch(on->kind) {
		case ADD: ;
		case SUB: ;
		case MUL: ;
		case DIV: ;
		case REM: ;
		case LPAR: ;
		case RPAR: ;
		case PLUS: ;
		case MINUS: ;
		int ans, prev, has_run = 0, in[3], out[3], identical[3] = {1, 1, 1};
		for(in[0] = -MAXC;in[0] <= MAXC;in[0]++) for(in[1] = -MAXC;in[1] <= MAXC;in[1]++) for(in[2] = -MAXC;in[2] <= MAXC;in[2]++) {
			if(Run(on, in, out, &ans) == 1) break;
			for(int i = 0;i < 3;i++) identical[i] &= (in[i] == ans);
			if(has_run) {
				if(ans != prev) break;	
			} else has_run = 1;
			prev = ans;
		}
		if(in[0] == MAXC + 1 && in[1] == MAXC + 1 && in[2] == MAXC + 1) {
			on->kind = CONSTANT;
			on->val = ans;
			on->lhs = on->rhs = on->mid = NULL;
		}
		for(int i = 0;i < 3;i++) if(identical[i]) {
			on->kind = IDENTIFIER;
			on->val = i + 'x';
			on->lhs = on->rhs = on->mid = NULL;
			break;
		}
		break;
		/* No need for optimize */
		case IDENTIFIER: ;
		case CONSTANT: ;

		/* Side effect, no optimize */
		case ASSIGN: ;
		case LOAD: ;
		case STORE: ;
		case PREINC: ;
		case PREDEC: ;
		case POSTINC: ;
		case POSTDEC: ;

		/* Other wtf stuff */
		default: ;
	}
	Enumerate_Constant_Optimize(on->lhs); Enumerate_Constant_Optimize(on->rhs); Enumerate_Constant_Optimize(on->mid);
}
void Constant_Optimize() {
	//printf("---------\n");
	for(int i = 0;i < N;i++) Enumerate_Constant_Optimize(ast[i]);
	//printf("---------\n");
}
#pragma endregion ConstantOptimize

#pragma region ReferenceOptimize

#pragma endregion ReferenceOptimize

#pragma region BuildASM
int used_regs[300] = {0};
int Get_Minimum_Reg() {
	int ans = 3;
	while(used_regs[ans]) ans += 1;
	return ans;
}
struct Symbol Build_ASM(AST *root) {
	struct Symbol one = { .vtype = Val_CONST, .value = 1 },
			zero = { .vtype = Val_CONST, .value = 0 };
	switch(root->kind) {
		case ASSIGN: ;
		{
			struct Symbol target = Build_ASM(root->lhs), value = Build_ASM(root->rhs);
			opt_asm = Append(opt_asm, Gen_ASM(target, zero, value, Op_ADD));
			return value;
		}
		case ADD: ;
 		case SUB: ;
		case MUL: ;
		case DIV: ;
		case REM: ;
		{
			struct Symbol l = Build_ASM(root->lhs), r = Build_ASM(root->rhs), ans = { .vtype = Val_REG };
			if(l.vtype == Val_REG) used_regs[l.value] = 0;
			if(r.vtype == Val_REG) used_regs[r.value] = 0;
			used_regs[ans.value = Get_Minimum_Reg()] = 1;
			opt_asm = Append(opt_asm, Gen_ASM(ans, l, r, Op_ADD + root->kind - ADD));
			return ans;
		}
		case PREINC: ;
		case PREDEC: ;
		{
			struct Symbol major = Build_ASM(root->mid);
			opt_asm = Append(opt_asm, Gen_ASM(major, major, one, Op_ADD + root->kind - PREINC));
			return major;
		}
		case POSTINC: ;
		case POSTDEC: ;
		{
			struct Symbol major = Build_ASM(root->mid), ans = { .vtype = Val_REG };
			used_regs[ans.value = Get_Minimum_Reg()] = 1;
			opt_asm = Append(opt_asm, Gen_ASM(ans, zero, major, Op_ADD));
			opt_asm = Append(opt_asm, Gen_ASM(major, major, one, Op_ADD + root->kind - POSTINC));
			return ans;
		}
		case IDENTIFIER: ;
		{ 
			struct Symbol ans = { .vtype = Val_REG, .value = root->val - 'x' }; 
			return ans; 
		}
		case CONSTANT: ;
		{
			struct Symbol ans = { .vtype = Val_CONST, .value = root->val };
			return ans;
		}
		case LPAR: ;
		case RPAR: ;
		case PLUS: ;
		{ 
			return Build_ASM(root->mid); 
		}
		case MINUS: ;
		{
			struct Symbol ans = { .vtype = Val_REG }, major = Build_ASM(root->mid);
			used_regs[major.value] = 0;
			used_regs[ans.value = Get_Minimum_Reg()] = 1;
			opt_asm = Append(opt_asm, Gen_ASM(ans, zero, major, Op_SUB));
			return ans;
		}
		case LOAD: ;
		{
			struct Symbol reg = { .vtype = Val_REG, .value = root->val }, mem = { .vtype = Val_MEM, .value = root->val };
			opt_asm = Append(opt_asm, Gen_ASM(reg, mem ,zero, Op_LOAD));
			return zero;
		}
		case STORE: ;
		{
			struct Symbol reg = { .vtype = Val_REG, .value = root->val }, mem = { .vtype = Val_MEM, .value = root->val };
			opt_asm = Append(opt_asm, Gen_ASM(mem, reg ,zero, Op_STORE));
			return zero;
		}
		default: ;
			err("Unkown AST type");
	}
}
void Generate_ASM() {
	for(int i = 0;i < N;i++) {
		struct Symbol ans = Build_ASM(ast[i]);
		//if(ans.vtype == Val_REG) used_regs[ans.value] = 0;
		/* for(int z = 0;z < 3;z++) printf("%d ", regs[z]);
		printf("\n"); */
	}
}
#pragma endregion BuildASM

void codegen() { 
	Constant_Optimize();
	Generate_ASM();
}

#pragma region Output
int SymbolOutput(struct Symbol item) {
	switch(item.vtype) {
		case Val_CONST:
			printf("%d", item.value);
			return 1;
		case Val_MEM:
			printf("[%d]", item.value * 4);
			return 1;
		case Val_REG:
			printf("r%d", item.value);
			return 1;
		case Val_NUL: ;
		default: ;
			return 0;
	}
}

void Output() {
	struct Vector* dummy = Append(opt_asm, NULL);
	char* Op[] = {"load", "store", "add", "sub", "mul", "div", "rem"};
	for(struct Vector* it = dummy->next;it != dummy;it = it->next) {
		struct ASM temp = *(struct ASM*)it->storage;
		printf("%s ", Op[temp.op]);
		SymbolOutput(temp.out); printf(" "); 
		SymbolOutput(temp.in[0]); 
		if(!(temp.op == Op_STORE || temp.op == Op_LOAD)) {
			printf(" "); 
			SymbolOutput(temp.in[1]); 
		}
		printf("\n");
	}
	EraseNext(opt_asm);
}
#pragma endregion Output