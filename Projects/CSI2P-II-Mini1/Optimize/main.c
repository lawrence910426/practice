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
	ASSIGN, ADD, SUB, MUL, DIV, REM, PREINC, PREDEC, POSTINC, POSTDEC, IDENTIFIER, CONSTANT, LPAR, RPAR, PLUS, MINUS
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
#define DEBUG 1
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
void codegen(AST *root);
// Free the whole AST.
void freeAST(AST *now);
// Optimize ASM code.
void Optimize();
// Output the ASM code.
void Output();

/// debug interfaces

// Print token array.
void token_print(Token *in, size_t len);
// Print AST tree.
void AST_print(AST *head);

char input[MAX_LENGTH];

int main() {
	while (fgets(input, MAX_LENGTH, stdin) != NULL) {
		Token *content = lexer(input);
		size_t len = token_list_to_arr(&content);
		AST *ast_root = parser(content, len);
		semantic_check(ast_root);
		codegen(ast_root);
		//AST_print(ast_root);
		free(content);
		freeAST(ast_root);
		if(DEBUG) break;
	}
    Optimize();
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
struct Vector *raw_asm = NULL, *opt_asm = NULL;
struct Data *reg[256], *mem[3];

#pragma region Vector
struct Vector { 
	void *storage; 
	struct Vector *next;
};
struct Vector* Append(struct Vector* last, void* item) {
	struct Vector* object = (struct Vector*)calloc(1, sizeof(struct Vector));
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
enum Operation { Op_LOAD, Op_STORE, Op_ADD, Op_SUB, Op_MUL, Op_DIV, Op_REM, Op_CPY };
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

#pragma region DAG
struct Data;
struct Function {
	struct Data *in[2], *out[2];
	enum Operation Op;
	int generated;
};
struct Data {
	struct Function *prev, *next;
	enum ValueType vtype;
	int val, id;
	int used, leaf;
};
void Show_Data(struct Data *item) {
	char* type[] = { "Val_CONST", "Val_REG", "Val_MEM", "Val_NUL" };
	printf("%s val:%d id:%d used:%d pos:%p\n", type[item->vtype], item->val, item->id, item->used, item);
}
void Show_Function(struct Function *item) {
	char* type[] = { "Op_LOAD", "Op_STORE", "Op_ADD", "Op_SUB", "Op_MUL", "Op_DIV", "Op_REM", "Op_CPY" };
	printf("%s\n", type[item->Op]);
	for(int i = 0;i < 2;i++) { printf("in:  %d -> ", i); Show_Data(item->in[i]); }
	for(int i = 0;i < 2;i++) { printf("out: %d -> ", i); Show_Data(item->out[i]); }
}
#pragma endregion DAG

#pragma region CodeGen
int reg_code = 3;
struct Symbol Build_ASM(AST *root) {
	// TODO: Implement your codegen in your own way.
	// You may modify the function parameter or the return type, even the whole structure as you wish.
	struct Symbol one = { .vtype = Val_CONST, .value = 1 },
			zero = { .vtype = Val_CONST, .value = 0 };

	switch(root->kind) {
		case ASSIGN: ;
		{
			struct Symbol target = Build_ASM(root->lhs), 
					value = Build_ASM(root->rhs),
					ans = { .vtype = Val_REG, .value = reg_code++ };
			raw_asm = Append(raw_asm, Gen_ASM(target, zero, value, Op_ADD));
			raw_asm = Append(raw_asm, Gen_ASM(ans, zero, value, Op_ADD));
			return ans;
		}
		case ADD: ;
 		case SUB: ;
		case MUL: ;
		case DIV: ;
		case REM: ;
		{
			struct Symbol l = Build_ASM(root->lhs), 
					r = Build_ASM(root->rhs), 
					ans = { .vtype = Val_REG, .value = reg_code++ };
			raw_asm = Append(raw_asm, Gen_ASM(ans, l, r, Op_ADD + root->kind - ADD));
			return ans;
		}
		case PREINC: ;
		case PREDEC: ;
		{
			struct Symbol major = Build_ASM(root->mid);
			raw_asm = Append(raw_asm, Gen_ASM(major, major, one, Op_ADD + root->kind - PREINC));
			return major;
		}
		case POSTINC: ;
		case POSTDEC: ;
		{
			struct Symbol major = Build_ASM(root->mid),
					ans = { .vtype = Val_REG, .value = reg_code++ };
			raw_asm = Append(raw_asm, Gen_ASM(ans, zero, major, Op_ADD));
			raw_asm = Append(raw_asm, Gen_ASM(major, major, one, Op_ADD + root->kind - POSTINC));
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
			struct Symbol ans = { .vtype = Val_REG, .value = reg_code++ },
					major = Build_ASM(root->mid);
			raw_asm = Append(raw_asm, Gen_ASM(ans, zero, major, Op_SUB));
			return ans;
		}
		default: ;
			err("Unkown AST type");
	}
}

void codegen(AST* root) { 
	struct Symbol sym[3][2], dummy = { .value = 0, .vtype = Val_NUL };	
	for(int i = 0;i < 3;i++) for(int j = 0;j < 2;j++) { sym[i][j].value = (j == 0 ? i : i * 4); sym[i][j].vtype = Val_REG + j; }
	/* Load stuff to register */
	for(int i = 0;i < 3;i++) raw_asm = Append(raw_asm, Gen_ASM(sym[i][0], sym[i][1], dummy, Op_LOAD));
	/* Compute the values */
	Build_ASM(root); 
	/* Load stuff back to memory */
	for(int i = 0;i < 3;i++) raw_asm = Append(raw_asm, Gen_ASM(sym[i][1], sym[i][0], dummy, Op_STORE));
}
#pragma endregion CodeGen

#pragma region BuildDAG
#define SHOW_DAG_ASM 0
int lowbit(int i) { return i & (-i); }
void Initialize_Function(struct Function* node) {
	for(int i = 0;i < 2;i++) {
		node->in[i] = calloc(1, sizeof(struct Data));
		node->in[i]->vtype = Val_NUL;
		node->in[i]->next = node;
	}
	for(int i = 0;i < 2;i++) {
		node->out[i] = calloc(1, sizeof(struct Data));
		node->out[i]->vtype = Val_NUL;
		node->out[i]->prev = node;
	}
}
struct Function* Gen_CPY(struct Data *in) {
	struct Function *clone = (struct Function*)calloc(1, sizeof(struct Function));
	Initialize_Function(clone);
	clone->Op = Op_CPY;
	for(int i = 0;i < 2;i++) clone->out[i]->vtype = Val_REG;
	return clone;
}
void Build_DAG() {
	for(int i = 0;i < 3;i++) {
		mem[i] = calloc(1, sizeof(struct Data));
		mem[i]->vtype = Val_MEM;
		mem[i]->id = i;
	}

	struct Vector* dummy = Append(raw_asm, NULL);
	for(struct Vector* it = dummy->next;it != dummy;it = it->next) {
		struct ASM *line = (struct ASM*)it->storage;
		struct Function *node = (struct Function*)calloc(1, sizeof(struct Function));
		node->Op = line->op;
		Initialize_Function(node);
		if(DEBUG && SHOW_DAG_ASM) { printf("Begin\n"); Show_Function(node); }

		/* If one of the inputs is 0 and one of the inputs is a register, then we may encode this line to a `CPY` node. */
		int pos = -1;
		for(int i = 0;i < 2;i++) if(line->op == Op_ADD && line->in[i].vtype == Val_REG && line->in[i ^ 1].vtype == Val_CONST && line->in[i ^ 1].value == 0) pos = i;
		if(pos != -1) {
			node = Gen_CPY(reg[line->in[pos].value]);
			node->in[0] = reg[line->in[pos].value];
			node->in[0]->next = node;
			reg[line->in[pos].value] = node->out[0];
			reg[line->out.value] = node->out[1];
		} else {
			for(int i = 0;i < 2;i++) {
				if(line->in[i].vtype == Val_REG) {
					if(reg[line->in[i].value]->next != NULL) {
						struct Function *clone = Gen_CPY(reg[line->in[i].value]);
						clone->in[0] = reg[line->in[i].value];
						for(int j = 0;j < 2;j++) 
							if(reg[line->in[i].value]->next->in[j] == reg[line->in[i].value])
								reg[line->in[i].value]->next->in[j] = clone->out[0];
						clone->in[0]->next = clone;
						clone->out[0]->next = reg[line->in[i].value]->next;
						reg[line->in[i].value] = clone->out[1];
						if(DEBUG) { printf("Clone\n"); Show_Function(clone); }
					}
					reg[line->in[i].value]->next = node;
					node->in[i] = reg[line->in[i].value];
				} else if(line->in[i].vtype == Val_MEM) {
					mem[line->in[i].value / 3]->next = node;
					node->in[i] = mem[line->in[i].value / 3];
				} else if(line->in[i].vtype == Val_CONST) {
					node->in[i]->val = line->in[i].value;
				}
				node->in[i]->vtype = line->in[i].vtype;
			}
		}		

		if(line->out.vtype == Val_REG) reg[line->out.value] = node->out[0];
		else if(line->out.vtype == Val_MEM) {
			mem[line->out.value / 3] = node->out[0];
			node->out[0]->id = line->out.value / 3;
		}
		node->out[0]->vtype = line->out.vtype;

		if(DEBUG) { printf("END\n"); Show_Function(node); }
	}
	EraseNext(raw_asm);
}
#pragma endregion BuildDAG

#pragma region ConstantOptimize
int Run(struct Data *target, int in[3], int *err) {
	if(target->vtype == Val_MEM) return in[target->val];
	if(target->vtype == Val_CONST) return target->val;
	if(target->vtype == Val_REG) {
		struct Function *Oper = target->prev;
		int temp;
		switch(Oper->Op) {
			case Op_ADD:
			return Run(Oper->in[0], in, err) + Run(Oper->in[1], in, err);
			case Op_SUB:			
			return Run(Oper->in[0], in, err) - Run(Oper->in[1], in, err);
            case Op_MUL:
			return Run(Oper->in[0], in, err) * Run(Oper->in[1], in, err);
            case Op_CPY:
            return Run(Oper->in[0], in, err);
			case Op_DIV:
			case Op_REM:
			temp = Run(Oper->in[1], in, err);
			if(temp == 0) *err = 1;
			else return (Oper->Op == Op_DIV ? Run(Oper->in[0], in, err) / temp : Run(Oper->in[0], in, err) % temp);
        }
	}
}
void Constant_Optimize(struct Data* target) {
	if(target == NULL || target->vtype == Val_NUL) return;
	if(target->vtype != Val_REG) goto done;
	int in[3];
	int value, has_run = 0, err;
	for(int x = -128;x <= 128;x++) for(int y = -128;y <= 128;y++) for(int z = -128;z <= 128;z++) {
		in[0] = x; in[1] = y; in[2] = z;
		err = 0;
		if(!has_run) {
			value = Run(target, in, &err);
			if(err) has_run = 1;
		} else {
			if(value != Run(target, in, &err) || err) goto done;
		}
	}
	target->vtype = Val_CONST;
	target->prev = NULL;
	target->val = value;
	Show_Data(target);
done: ;
	struct Function *Oper = target->prev;
	if(Oper == NULL) return;
	for(int i = 0;i < 2;i++) Constant_Optimize(Oper->in[i]);
}
#pragma endregion ConstantOptimize

#pragma region BranchCutOptimize
void Mark_Used(struct Data* on) {
	if(on == NULL || on->vtype == Val_NUL) return;
	on->used = 1;
	struct Function* Oper = on->prev;
	if(Oper == NULL || Oper->Op == Val_CONST) return;
	for(int i = 0;i < 2;i++) Mark_Used(Oper->in[i]);
}
void Cut_Branch(struct Data* on) {
	struct Function* Oper = on->prev;
	if(Oper == NULL || Oper->Op != Op_CPY) return;
	for(int i = 0;i < 2;i++) if(Oper->out[i] != NULL && Oper->out[i]->used == 0) Oper->out[i] = NULL;
	for(int i = 0;i < 2;i++) Cut_Branch(Oper->in[i]);
}
void Branch_Cut_Optimize() {
	for(int i = 0;i < 3;i++) Mark_Used(mem[i]);
	for(int i = 0;i < 3;i++) Cut_Branch(mem[i]);
}
#pragma endregion BranchCutOptimize

#pragma region SymbolicSubstitute
int Subsitute_Symbol(struct Data* on) {
	if(on == NULL || on->vtype == Val_NUL) return 0;
	struct Function* Oper = on->prev;
	if(Oper == NULL) return 0;
	switch(Oper->Op) {
		case Op_STORE: ;
		struct Data* reg = Oper->in[0];
		if(reg->prev == NULL) return 0;
		if(reg->prev->Op == Op_LOAD && reg->prev->in[0]->val == on->val) {
			on->prev = NULL;
			return 1;
		} else return 0;

		case Op_CPY: ;
		int flag = 0;
		for(int i = 0;i < 2;i++) flag |= (Oper->out[i] != NULL ? 1 : 0) << i;
		if(flag == 3) return 0;
		else {
			*on = *Oper->in[0];
			return 1;
		}

		case Op_LOAD: ;
		break;
	}
	for(int i = 0;i < 2;i++) if(Subsitute_Symbol(Oper->in[i]) == 1) return 1;
}
void Symbolic_Substitute_Optimize() {
	for(int i = 0;i < 3;i++) while(Subsitute_Symbol(mem[i]) == 1) ;
}
#pragma endregion SymbolicSubstitute

#pragma region RegisterOptimize
void Initialize_Data_ID(struct Data* on) {
	if(on == NULL || on->vtype == Val_NUL) return;
	struct Function* Oper = on->prev;
	if(Oper == NULL) return;
	for(int i = 0;i < 2;i++) Initialize_Data_ID(Oper->in[i]);
	if(on->vtype == Val_REG) on->id = -1;
}
int used_regs[256] = {0};
int Get_Minimal_Unused() {
	int ans = 0;
	while(used_regs[ans] != 0) ans += 1;
	return ans;
}
void Assign_Reg_Id(struct Data* on) {
	struct Function *Oper = on->prev;
	if(Oper == NULL) return;
	for(int i = 0;i < 2;i++) Assign_Reg_Id(Oper->in[i]);
	if(on->id == -1) {
		if(Oper->Op == Op_CPY) {
			Oper->out[0]->id = Oper->in[0]->id;
			used_regs[Oper->out[1]->id = Get_Minimal_Unused()] = 1;
		} else {
			for(int i = 0;i < 2;i++) if(Oper->in[i]->vtype == Val_REG) used_regs[Oper->in[i]->id] = 0;
			for(int i = 0;i < 2;i++) if(Oper->out[i]->vtype == Val_REG) used_regs[Oper->out[i]->id = Get_Minimal_Unused()] = 1;
		}
	}
}
void Register_Optimize() {
	for(int i = 0;i < 3;i++) Initialize_Data_ID(mem[i]);
	for(int i = 0;i < 3;i++) Assign_Reg_Id(mem[i]);
}
#pragma endregion RegisterOptimize

#pragma region ExportASM
struct Symbol Data_To_Symbol(struct Data item) {
	switch(item.vtype) {
		case Val_REG: ;
		struct Symbol reg = { .vtype = Val_REG, .value = item.id };
		return reg;
		case Val_CONST: ;
		struct Symbol con = { .vtype = Val_CONST, .value = item.val };
		return con;
		case Val_MEM: ;
		struct Symbol mem = { .vtype = Val_MEM, .value = item.id * 4 };
		return mem;
		case Val_NUL: ;
		struct Symbol nul = { .vtype = Val_CONST, .value = 0 };
		return nul;
	}
}
void Export_ASM(struct Data* on) {
	if(on == NULL) return;
	struct Function *Oper = on->prev;
	if(Oper == NULL || Oper->generated) return;
	Oper->generated = 1;
	for(int i = 0;i < 2;i++) Export_ASM(Oper->in[i]);
	enum Operation Op = Oper->Op;
	switch(Oper->Op) {
		case Op_CPY:
		opt_asm = Append(
			opt_asm, 
			Gen_ASM(
				Data_To_Symbol(*Oper->out[1]), 
				Data_To_Symbol(*Oper->in[1]), 
				Data_To_Symbol(*Oper->in[0]),
				Op_ADD
			)
		);
		break;

		case Op_ADD: ;
		case Op_SUB: ;
		case Op_MUL: ;
		case Op_DIV: ;
		case Op_REM: ;
		case Op_LOAD: ;
		case Op_STORE: ;
		opt_asm = Append(
			opt_asm, 
			Gen_ASM(
				Data_To_Symbol(*Oper->out[0]), 
				Data_To_Symbol(*Oper->in[0]), 
				Data_To_Symbol(*Oper->in[1]),
				Oper->Op
			)
		);
		break;
	}
}
#pragma endregion ExportASM

void Optimize() {
	Build_DAG();
	/* for(int i = 0;i < 3;i++) Constant_Optimize(mem[i]);	
	Branch_Cut_Optimize();
	Symbolic_Substitute_Optimize(); */
	Register_Optimize();
	for(int i = 0;i < 3;i++) Export_ASM(mem[i]);
	// opt_asm = raw_asm;
}

#pragma region Output
int SymbolOutput(struct Symbol item) {
	switch(item.vtype) {
		case Val_CONST:
			printf("%d", item.value);
			return 1;
		case Val_MEM:
			printf("[%d]", item.value);
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
