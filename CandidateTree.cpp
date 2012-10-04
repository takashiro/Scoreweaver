
#include "Globals.h"
#include "CandidateTree.h"

CCandidateTree::CCandidateTree(){
	_root = _current = new Node(NULL, 0);

	_root->SetChildren(L"QWERTYUIO", L"古琴谱文字编辑软件");
	_root->GetChild(0)->SetChildren(L"123456", L"这是一个测试");
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

void CCandidateTree::ForwardTo(wchar_t child_key){
	Node *n = _current->GetChild(child_key);
	if(n != NULL){
		_current = n;
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

void CCandidateTree::Node::AddChild(wchar_t key, wchar_t value){
	_childrenKeys.push_back(key);
	_childrenNodes.push_back(new Node(this, value));
}

CCandidateTree::Node *CCandidateTree::Node::GetChild(int key){
	return _childrenNodes.at(key);
}

CCandidateTree::Node *CCandidateTree::Node::GetChild(wchar_t key){
	int pos = _childrenKeys.find(key);
	if(pos >= 0){
		return _childrenNodes.at(pos);
	}else{
		return NULL;
	}
}

void CCandidateTree::Node::RemoveChild(wchar_t key){
	int pos = _childrenKeys.find(key);
	if(pos >= 0){
		_childrenKeys.erase(pos);
		delete _childrenNodes.at(pos);
		_childrenNodes.erase(_childrenNodes.begin() + pos);
	}
}

void CCandidateTree::Node::SetChildren(const wstring &keys, const wstring &values){
	ClearChildren();

	_childrenKeys = keys;
	_childrenValues = values;

	unsigned max = keys.size() <= values.size() ? keys.size() : values.size();
	for(unsigned i = 0; i < max; i++){
		_childrenNodes.push_back(new Node(this, values.at(i)));
	}
}

wstring CCandidateTree::Node::GetChildren() const{
	return _childrenValues;
}

void CCandidateTree::Node::ClearChildren(){
	for(vector<Node *>::iterator iter = _childrenNodes.begin(); iter != _childrenNodes.end(); iter++){
		(*iter)->ClearChildren();
		delete *iter;
	}

	_childrenKeys.clear();
	_childrenValues.clear();
	_childrenNodes.clear();
}

bool CCandidateTree::Node::IsEnd() const{
	return _childrenKeys.empty();
}

bool CCandidateTree::Node::HasChildren() const{
	return !_childrenKeys.empty();
}

CCandidateTree *CandidateTree = new CCandidateTree();