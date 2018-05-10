//Nicholas Seifert
//Compiler Design - Spring 2018
//Code Skeleton Created by Dr. Andrew Sutton

#include "codegen.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "decl.hpp"
#include "stmt.hpp"

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>

#include <cassert>
#include <iostream>
#include <sstream>
#include <unordered_map>

/// Associates declarations with values.
using variable_map = std::unordered_map<const Decl*, llvm::Value*>;

// -------------------------------------------------------------------------- //
// Root context

/// The root code generation context. This provides facilities for 
/// translating Beaker types and constants into LLVM types and constants.
struct cg_context {
	cg_context()
	: ll(new llvm::LLVMContext())
	{ }

	/// Destroys the codegen context.
	~cg_context() { delete ll; }

	/// Returns the LLVM context.
	llvm::LLVMContext *get_context() const { return ll; }

	// Names

	/// Returns a name for the declaration.
	std::string get_name(const Decl* d);

	// Types

	/// Generate the corresponding type for `t`.
	llvm::Type* get_type(const Type* t);
	llvm::Type* get_bool_type(const BoolType* t);
	llvm::Type* get_char_type(const CharType* t);
	llvm::Type* get_int_type(const IntType* t);
	llvm::Type* get_float_type(const FloatType* t);
	llvm::Type* get_ref_type(const ReferenceType* t);
	llvm::Type* get_fn_type(const FunctionType* t);

	/// Returns the corresponding type for the declaration `d`.
	llvm::Type* get_type(const TypedDecl* d);

	/// The underlying LLVM context.
	llvm::LLVMContext* ll;
};

// -------------------------------------------------------------------------- //
// Module context

/// The module generation context provides facilities for generating 
/// and referencing module-level declarations.
struct cg_module {
	cg_module(cg_context& cxt, const ProgramDecl* prog);

	/// Returns the LLVM context.
	llvm::LLVMContext* get_context() const { return parent->get_context(); }

	/// Returns the underlying LLVM module.
	llvm::Module* get_module() const { return mod; }

	//  Names

	/// Generates a declaration name for `d`.
	std::string get_name(const Decl* d) { return parent->get_name(d); }

	// Types

	/// Generate a corresponding type to `t`.
	llvm::Type* get_type(const Type* t) { return parent->get_type(t); }

	/// Generates a type corresponding to the type `d`.
	llvm::Type* get_type(const TypedDecl* d) { return parent->get_type(d); }

	// Global values

	/// Associate the value `v` with the global declaration `d`.
	void declare(const Decl* d, llvm::GlobalValue* v);

	/// Returns the global value corresponding to `d` or nullptr.
	llvm::GlobalValue* lookup(const Decl* d) const;

	// Declaration generation

	/// Process expressions as top-level declarations.
	void generate();
	void generate(const Decl* d);
	void generate_var_decl(const VariableDefinitionDecl* d);
	void generate_fn_decl(const FunctionDefinitionDecl* d);

	/// The parent context.
	cg_context* parent; 

	/// The corresponding translation unit.
	const ProgramDecl* prog;  

	/// The underlying LLVM module.
	llvm::Module* mod; 

	/// A lookup table for global modules.
	variable_map globals;
};

// -------------------------------------------------------------------------- //
// Function context

/// Provides the codegen context for expressions.
struct cg_function {
	cg_function(cg_module& m, const FunctionDefinitionDecl* d);

	// Context

	/// Returns the LLVM context.
	llvm::LLVMContext* get_context() const { return parent->get_context(); }

	/// Returns the owning LLVM module.
	llvm::Module* get_module() const { return parent->get_module(); }

	/// Returns the underlying LLVM Function.
	llvm::Function* get_function() const { return fn; }

	// Names

	/// Returns the name for the declaration `d`.
	std::string get_name(const Decl* d) { return parent->get_name(d); }

	// Types

	/// Generates the type corresponding to the expression `e`.
	llvm::Type* get_type(const Type* t) { return parent->get_type(t); }

	/// Generates the type corresponding to the expression `e`.
	llvm::Type* get_type(const Expr* e) { return get_type(e->mType); }

	/// Generate the corresponding type for `t`.
	llvm::Type* get_type(const TypedDecl* t) { return parent->get_type(t); }

	// Local variables

	/// Declare a new local value.
	void declare(const Decl* x, llvm::Value* v);

	/// Lookup a value. This may return a global value.
	llvm::Value* lookup(const Decl* x) const;

	// Function definition

	void define();

	// Block management

	/// Returns the entry block. This is where local variables are allocated.
	llvm::BasicBlock* get_entry_block() const { return entry; }

	/// Returns the current block.
	llvm::BasicBlock* get_current_block() const { return curr; }

	/// Returns a new block with the given name. The block is unlinked until
	/// it is emitted.
	llvm::BasicBlock* make_block(const char* label);

	/// Emits a new block, making it active.
	void emit_block(llvm::BasicBlock* bb);

	// Instruction generation

	/// Generate a list of instructions to compute the value of e.
	llvm::Value* generate_expr(const Expr* e);
	llvm::Value* generate_bool_expr(const BooleanLiteralExpr* e);
	llvm::Value* generate_int_expr(const IntegerLiteralExpr* e);
	llvm::Value* generate_float_expr(const FloatLiteralExpr* e);
	llvm::Value* generate_id_expr(const IdentifierExpr* e);
	llvm::Value* generate_unop_expr(const UnaryOperatorExpr* e);
	llvm::Value* generate_arithmetic_expr(const UnaryOperatorExpr* e);
	llvm::Value* generate_int_expr(const UnaryOperatorExpr* e);
	llvm::Value* generate_float_expr(const UnaryOperatorExpr* e);
	llvm::Value* generate_bitwise_expr(const UnaryOperatorExpr* e);
	llvm::Value* generate_logical_expr(const UnaryOperatorExpr* e);
	llvm::Value* generate_address_expr(const UnaryOperatorExpr* e);
	llvm::Value* generate_deref_expr(const UnaryOperatorExpr* e);
	llvm::Value* generate_binop_expr(const BinaryOperatorExpr* e);
	llvm::Value* generate_arithmetic_expr(const BinaryOperatorExpr* e);
	llvm::Value* generate_int_expr(const BinaryOperatorExpr* e);
	llvm::Value* generate_float_expr(const BinaryOperatorExpr* e);
	llvm::Value* generate_bitwise_expr(const BinaryOperatorExpr* e);
	llvm::Value* generate_logical_expr(const BinaryOperatorExpr* e);
	llvm::Value* generate_and_expr(const BinaryOperatorExpr* e);
	llvm::Value* generate_or_expr(const BinaryOperatorExpr* e);
	llvm::Value* generate_relational_expr(const BinaryOperatorExpr* e);
	llvm::Value* generate_call_expr(const CallExpr* e);
	llvm::Value* generate_index_expr(const IndexExpr* e);
	llvm::Value* generate_cast_expr(const CastExpr* e);
	llvm::Value* generate_cond_expr(const ConditionalExpr* e);
	llvm::Value* generate_assign_expr(const AssignmentExpr* e);
	llvm::Value* generate_conv_expr(const ConvExpr* e);

	// Statements
	void generate_stmt(const Stmt* s);
	void generate_block_stmt(const BlockStmt* s);
	void generate_when_stmt(const WhenStmt* s);
	void generate_if_stmt(const IfStmt* s);
	void generate_while_stmt(const WhileStmt* s);
	void generate_break_stmt(const BreakStmt* s);
	void generate_cont_stmt(const ContinueStmt* s);
	void generate_ret_stmt(const ReturnStmt* s);
	void generate_decl_stmt(const DeclarationStmt* s);
	void generate_expr_stmt(const ExpressionStmt* s);

	// Local declarations
	void generate_decl(const Decl* d);
	void generate_var_decl(const VariableDefinitionDecl* d);

	void make_variable(const VariableDefinitionDecl* d);
	void make_reference(const VariableDefinitionDecl* d);

	/// The parent module context.
	cg_module* parent;

	/// The function original function
	const FunctionDefinitionDecl* src;

	/// The underlying function being defined
	llvm::Function* fn;

	/// The entry block.
	llvm::BasicBlock* entry;

	/// The current block.
	llvm::BasicBlock* curr; 

	/// Local variables.
	variable_map locals;
};

// -------------------------------------------------------------------------- //
// Context implementation

std::string cg_context::get_name(const Decl* d) {
	assert(d->name);
	return *d->name;
}

/// Generate the corresponding type.
llvm::Type*  cg_context::get_type(const Type* t) {
	// Make sure we're looking at the semantic, not lexical type.
	switch (t->mWhatType) {
		case tBool:
			return get_bool_type(static_cast<const BoolType*>(t));
		case tChar:
			return get_char_type(static_cast<const CharType*>(t));
		case tInt:
			return get_int_type(static_cast<const IntType*>(t));
		case tFloat:
			return get_float_type(static_cast<const FloatType*>(t));
		case reference:
			return get_ref_type(static_cast<const ReferenceType*>(t));
		case tFunction:
			return get_fn_type(static_cast<const FunctionType*>(t));
		default:
			throw std::logic_error("invalid type");
	}
}

/// The corresponding type is i1.
llvm::Type* cg_context::get_bool_type(const BoolType* t) {
	return llvm::Type::getInt1Ty(*ll);
}

/// The corresponding type is i8.
llvm::Type* cg_context::get_char_type(const CharType* t) {
	return llvm::Type::getInt8Ty(*ll);
}

/// The corresponding type is i32.
llvm::Type* cg_context::get_int_type(const IntType* t) {
	return llvm::Type::getInt32Ty(*ll);
}

/// The corresponding type is float.
llvm::Type* cg_context::get_float_type(const FloatType* t) {
	return llvm::Type::getFloatTy(*ll);
}

/// Returns a pointer to the object type.
llvm::Type* cg_context::get_ref_type(const ReferenceType* t) {
	llvm::Type* obj = get_type(t->baseType);
	return obj->getPointerTo();
}

/// Generate the type as a pointer. The actual function type can extracted
/// as needed for creating functions.
llvm::Type* cg_context::get_fn_type(const FunctionType* t) {
	const TypeList& ps = t->parameterType;
	std::vector<llvm::Type*> parms(ps.size());
	std::transform(ps.begin(), ps.end(), parms.begin(), [this](const Type* p) {
		return get_type(p);
	});
	llvm::Type* ret = get_type(t->returnType);
	llvm::Type* base = llvm::FunctionType::get(ret, parms, false);
	return base->getPointerTo();
}

llvm::Type* cg_context::get_type(const TypedDecl* d) {
	return get_type(d->type);
}

// -------------------------------------------------------------------------- //
// Module implementation

/// \todo Derive the name of the output file from compiler options.
cg_module::cg_module(cg_context& cxt, const ProgramDecl* prog)
  : parent(&cxt), 
    prog(prog), 
    mod(new llvm::Module("a.ll", *get_context()))
{ }

void cg_module::declare(const Decl* d, llvm::GlobalValue* v) {
	assert(globals.count(d) == 0);
	globals.emplace(d, v);
}

llvm::GlobalValue* cg_module::lookup(const Decl* d) const
{
	auto iter = globals.find(d);
	if (iter != globals.end()) {
		return llvm::cast<llvm::GlobalValue>(iter->second);
	}
	else {
		return nullptr;
	}
}

/// Process top-level declarations.
void cg_module::generate() {
	for (const Decl* d : prog->declarations) {
		generate(d);
	}
}

void cg_module::generate(const Decl* d) {
	switch (d->mWhatDecl) {
		case variableDefinition:
			return generate_var_decl(static_cast<const VariableDefinitionDecl*>(d));
		case functionDefinition:
			return generate_fn_decl(static_cast<const FunctionDefinitionDecl*>(d));
		default: 
			throw std::logic_error("invalid declaration");
	}
}


void cg_module::generate_var_decl(const VariableDefinitionDecl* d) {
	std::string n = get_name(d);
	llvm::Type* t = get_type(d->type);
	llvm::Constant* c = llvm::Constant::getNullValue(t);
	llvm::GlobalVariable* var = new llvm::GlobalVariable(*mod, t, false, llvm::GlobalVariable::ExternalLinkage, c, n);
	// Create the binding.
	declare(d, var);
}

/// Generate a function from the fn expression.
void cg_module::generate_fn_decl(const FunctionDefinitionDecl* d) {
	cg_function fn(*this, d);
	fn.define();
}

// -------------------------------------------------------------------------- //
// Function implementation

static llvm::FunctionType* get_fn_type(llvm::Type* t) {
	assert(llvm::isa<llvm::PointerType>(t));
	return llvm::cast<llvm::FunctionType>(t->getPointerElementType());
}

cg_function::cg_function(cg_module& m, const FunctionDefinitionDecl* d)
  : parent(&m), src(d), fn(), entry(), curr() {
	std::string n = get_name(d);
	llvm::Type* t = get_type(d);
	fn = llvm::Function::Create(get_fn_type(t), llvm::Function::ExternalLinkage, n, get_module());

	// Create a binding in the module.
	parent->declare(d, fn);

	// Build and emit the entry block.
	entry = make_block("entry");
	emit_block(entry);

	llvm::IRBuilder<> ir(get_current_block());

	// Configure function parameters and declare them as locals.
	assert(d->parameters.size() == fn->arg_size());
	auto pi = d->parameters.begin();
	auto ai = fn->arg_begin();
	
	while (ai != fn->arg_end()) {
		const ParameterDecl* parm = static_cast<const ParameterDecl*>(*pi);
		llvm::Argument& arg = *ai;

		// Configure each parameter.
		arg.setName(get_name(parm));

		// Declare local variable for each parameter and initialize it
		// with wits corresponding value.
		llvm::Value* var = ir.CreateAlloca(arg.getType(), nullptr, arg.getName());
		declare(parm, var);

		// Initialize with the value of the argument.
		ir.CreateStore(&arg, var);

		++ai;
		++pi;
	}
}

void cg_function::declare(const Decl* d, llvm::Value* v) {
	assert(locals.count(d) == 0);
	locals.emplace(d, v);
}

llvm::Value* cg_function::lookup(const Decl* d) const {
	auto iter = locals.find(d);
	if (iter != locals.end()) {
		return iter->second;
	}
	else {
		return parent->lookup(d);
	}
}

llvm::BasicBlock* cg_function::make_block(const char* label) {
	return llvm::BasicBlock::Create(*get_context(), label);
}

void cg_function::emit_block(llvm::BasicBlock* bb) {
	bb->insertInto(get_function());
	curr = bb;
}

/// Creates a return instruction for the expression.
void cg_function::define() {
	generate_stmt(src->body);
}

llvm::Value* cg_function::generate_expr(const Expr* e) {
	switch (e->mWhatExpr) {
		case booleanLiteral:
			return generate_bool_expr(static_cast<const BooleanLiteralExpr*>(e));
		case integerLiteral:
			return generate_int_expr(static_cast<const IntegerLiteralExpr*>(e));
		case floatLiteral:
			return generate_float_expr(static_cast<const FloatLiteralExpr*>(e));
		case identifier:
			return generate_id_expr(static_cast<const IdentifierExpr*>(e));
		case unaryExpression:
			return generate_unop_expr(static_cast<const UnaryOperatorExpr*>(e));
		case binaryExpression:
			return generate_binop_expr(static_cast<const BinaryOperatorExpr*>(e));
		case callExpression:
			return generate_call_expr(static_cast<const CallExpr*>(e));
		case indexExpression:
			return generate_index_expr(static_cast<const IndexExpr*>(e));
		case conditionalExpression:
			return generate_cond_expr(static_cast<const ConditionalExpr*>(e));
		case assignmentExpression:
			return generate_assign_expr(static_cast<const AssignmentExpr*>(e));
		case convExpression:
			return generate_conv_expr(static_cast<const ConvExpr*>(e));
		default: 
			throw std::runtime_error("invalid expression");
	}
}

llvm::Value* cg_function::generate_bool_expr(const BooleanLiteralExpr* e) {
	return llvm::ConstantInt::get(get_type(e), e->boolValue, false);
}

llvm::Value* cg_function::generate_int_expr(const IntegerLiteralExpr* e) {
	return llvm::ConstantInt::get(get_type(e), e->intValue, true);
}

llvm::Value* cg_function::generate_float_expr(const FloatLiteralExpr* e) {
	return llvm::ConstantFP::get(get_type(e), e->floatValue);
}

llvm::Value* cg_function::generate_id_expr(const IdentifierExpr* e) {
	return nullptr;
}

llvm::Value* cg_function::generate_unop_expr(const UnaryOperatorExpr* e) {
	return nullptr;
}

// Note that &e is equivalent to e. This is because e is already an address.
llvm::Value* cg_function::generate_address_expr(const UnaryOperatorExpr* e) {
	return nullptr;
}

// Note that *e is equivalent to e. This is because e is already an address.
llvm::Value* cg_function::generate_deref_expr(const UnaryOperatorExpr* e) {
	return nullptr;
}

llvm::Value* cg_function::generate_binop_expr(const BinaryOperatorExpr* e) {
	return nullptr;
}

llvm::Value* cg_function::generate_relational_expr(const BinaryOperatorExpr* e) {
	// llvm::Value* lhs = generate_expr(e->get_lhs());
	// llvm::Value* rhs = generate_expr(e->get_rhs());
	// llvm::IRBuilder<> ir(get_current_block());
	// switch (e->get_operator()) {
	// case op_eq:
	//   return ir.CreateICmpEQ(lhs, rhs);
	// case op_ne:
	//   return ir.CreateICmpNE(lhs, rhs);
	// case op_lt:
	//   return ir.CreateICmpSLT(lhs, rhs);
	// case op_gt:
	//   return ir.CreateICmpSGT(lhs, rhs);
	// case op_le:
	//   return ir.CreateICmpSLE(lhs, rhs);
	// case op_ge:
	//   return ir.CreateICmpSGE(lhs, rhs);
	// default:
	//   throw std::logic_error("invalid operator");
	// }
	return nullptr;
}

llvm::Value* cg_function::generate_call_expr(const CallExpr* e) {
	return nullptr;
}

llvm::Value* cg_function::generate_index_expr(const IndexExpr* e) {
	return nullptr;
}

llvm::Value* cg_function::generate_assign_expr(const AssignmentExpr* e) {
	return nullptr;
}

llvm::Value* cg_function::generate_cond_expr(const ConditionalExpr* e) {
	return nullptr;
}

// FIXME: Clean this up.
llvm::Value* cg_function::generate_conv_expr(const ConvExpr* c) {
	return nullptr;
}

void cg_function::generate_stmt(const Stmt* s) {
	switch (s->mWhatStmt) {
		case blockStatement:
			return generate_block_stmt(static_cast<const BlockStmt*>(s));
		case whenStatement:
			return generate_when_stmt(static_cast<const WhenStmt*>(s));
		case ifStatement:
			return generate_if_stmt(static_cast<const IfStmt*>(s));
		case whileStatement:
			return generate_while_stmt(static_cast<const WhileStmt*>(s));
		case breakStatement:
			return generate_break_stmt(static_cast<const BreakStmt*>(s));
		case continueStatement:
			return generate_cont_stmt(static_cast<const ContinueStmt*>(s));
		case returnStatement:
			return generate_ret_stmt(static_cast<const ReturnStmt*>(s));
		case declarationStatement:
			return generate_decl_stmt(static_cast<const DeclarationStmt*>(s));
		case expressionStatement:
			return generate_expr_stmt(static_cast<const ExpressionStmt*>(s));
  }
}

void cg_function::generate_block_stmt(const BlockStmt* s) {
	for (const Stmt* st : s->sequence)
		generate_stmt(st);
}

void cg_function::generate_when_stmt(const WhenStmt* s) {
}

void cg_function::generate_if_stmt(const IfStmt* s) {
	generate_cond_expr(s->condition);
	
}

void cg_function::generate_while_stmt(const WhileStmt* s) {
	
}

void cg_function::generate_break_stmt(const BreakStmt* e) {
	
}

void cg_function::generate_cont_stmt(const ContinueStmt* e) {
	
}

void cg_function::generate_ret_stmt(const ReturnStmt* e) {
	
}

void cg_function::generate_decl_stmt(const DeclarationStmt* e) {
	generate(e->declaration);
}

void cg_function::generate_expr_stmt(const ExpressionStmt* e) {
	generate_expr(e->expression);
}

void generate(const Decl* d) {
	assert(d->mWhatDecl == program);

	// Establish the translation context.
	cg_context cg;

	// Create the module, and generate its declarations.
	cg_module mod(cg, static_cast<const ProgramDecl*>(d));
	mod.generate();

	// Dump the generated module to 
	llvm::outs() << *mod.get_module();
}
