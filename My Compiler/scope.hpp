#ifndef SCOPE_HPP
#defince SCOPE_HPP



class Scope {
	Scope(Scope* par)
		: parent(par) { 
	}

	Scope* parent;
};

class GlobalScope :  public Scope {

};

struct BlockScope : public Scope {

};

class FunctionParameterScope : public Scope {

};

#endif