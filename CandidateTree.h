
#ifndef CANDIDATETREE_H
#define CANDIDATETREE_H

class CCandidateTree{
public:
	class Node{
	public:
		Node(Node *parent, wchar_t value);
		~Node();

		wchar_t GetValue() const;

		void AddChild(wchar_t word);
		Node *GetChild(wchar_t word);
		void RemoveChild(wchar_t word);
		
		void SetChildren(const wstring &children);
		wstring GetChildren() const;
		void ClearChildren();

	private:
		Node *_parent;
		wchar_t _value;

		wstring _children;
		vector<Node *> _childrenNodes;
	};

	CCandidateTree();
	~CCandidateTree();

	CCandidateTree::Node *GetCurrent();

	void ForwardTo(wchar_t child);
	void ToRoot();

private:
	Node *_root, *_current;
};

extern CCandidateTree *CandidateTree;

#endif