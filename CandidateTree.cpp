
#include "Globals.h"
#include "CandidateTree.h"

CCandidateTree::CCandidateTree(){
	_root = _current = new Node(NULL, 0);

	_root->SetChildren(wstring(L"¹ÅÇÙÆ×ÎÄ×Ö±à¼­Èí¼þ"));
}

CCandidateTree::~CCandidateTree(){
	delete _root;
}

CCandidateTree::Node *CCandidateTree::GetCurrent(){
	return _current;
}

void CCandidateTree::ToRoot(){
	_current = _root;
}

void CCandidateTree::ForwardTo(wchar_t child){
	if(_current->GetChildren().find(child) >= 0){
		_current = _current->GetChild(child);
	}
}

CCandidateTree::Node::Node(CCandidateTree::Node *parent, wchar_t value){
	_parent = parent;
	_value = value;
}

CCandidateTree::Node::~Node(){
	ClearChildren();
}

wchar_t CCandidateTree::Node::GetValue() const{
	return _value;
}

void CCandidateTree::Node::AddChild(wchar_t word){
	_children.push_back(word);
	_childrenNodes.push_back(new Node(this, word));
}

CCandidateTree::Node *CCandidateTree::Node::GetChild(wchar_t word){
	int pos = _children.find(word);
	return _childrenNodes[pos];
}

void CCandidateTree::Node::RemoveChild(wchar_t word){
	int pos = _children.find(word);
	if(pos >= 0){
		_children.erase(pos);
		delete _childrenNodes[pos];
		_childrenNodes.erase(_childrenNodes.begin() + pos);
	}
}

void CCandidateTree::Node::SetChildren(const wstring &children){
	ClearChildren();

	_children = children;
	for(unsigned i = 0; i < _children.size(); i++){
		_childrenNodes.push_back(new Node(this, _children.at(i)));
	}
}

wstring CCandidateTree::Node::GetChildren() const{
	return _children;
}

void CCandidateTree::Node::ClearChildren(){
	for(vector<Node *>::iterator iter = _childrenNodes.begin(); iter != _childrenNodes.end(); iter++){
		(*iter)->ClearChildren();
		delete *iter;
	}

	_children.clear();
	_childrenNodes.clear();
}

CCandidateTree *CandidateTree = new CCandidateTree();